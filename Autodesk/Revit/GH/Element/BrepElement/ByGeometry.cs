using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

using Autodesk.Revit.DB;
using Grasshopper.Kernel.Special;

namespace RhinoInside.Revit.GH.Components
{
  public class BrepElementByGeometry : GH_TransactionalComponentList
  {
    public override Guid ComponentGuid => new Guid("5ADE9AE3-588C-4285-ABC5-09DEB92C6660");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("B");

    public BrepElementByGeometry() : base
    (
      "AddBrepElement.ByGeometry", "ByGeometry",
      "Given a Brep, it adds a Brep element to the active Revit document",
      "Revit", "Geometry"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "BrepElement", "B", "New BrepElement", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Brep brep = null;
      if (!DA.GetData("Brep", ref brep))
        return;

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, (Rhino.Geometry.Brep) brep?.DuplicateShallow()));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Brep brep
    )
    {
      var elements = PreviousElements(doc, Iteration).ToList();
      try
      {
        if (brep == null)
          throw new Exception(string.Format("Parameter '{0}' must be valid Brep.", Params.Input[0].Name));

        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
          brep.Scale(scaleFactor);

        var newElements = new List<Element>();
        {
          int index = 0;
          foreach (var s in brep.ToHost().Cast<Autodesk.Revit.DB.Solid>() ?? Enumerable.Empty<Autodesk.Revit.DB.Solid>())
          {
            var element = index < elements.Count ? elements[index] : null;
            index++;

            if (element?.Pinned ?? true)
            {
              if (doc.IsFamilyDocument && doc.OwnerFamily.IsConceptualMassFamily)
              {
                if (element is FreeFormElement freeFormElement)
                  freeFormElement.UpdateSolidGeometry(s);
                else
                {
                  element = CopyParametersFrom(FreeFormElement.Create(doc, s), element);
                  element.get_Parameter(BuiltInParameter.FAMILY_ELEM_SUBCATEGORY).Set(new ElementId(BuiltInCategory.OST_MassForm));
                }

                element.get_Parameter(BuiltInParameter.ELEMENT_IS_CUTTING)?.Set
                (
                  brep.SolidOrientation == Rhino.Geometry.BrepSolidOrientation.Inward ?
                  1 /*VOID*/ :
                  0 /*SOLID*/
                );
              }
              else
              {
                var ds = element as DirectShape ?? DirectShape.CreateElement(doc, new ElementId(BuiltInCategory.OST_GenericModel));
                ds.SetShape(new Solid[] { s });
                element = ds;
              }
            }

            newElements.Add(element);
          }
        }

        ReplaceElements(doc, DA, Iteration, newElements);
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
        ReplaceElements(doc, DA, Iteration, null);
      }
    }
  }
}
