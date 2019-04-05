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
  public class FormByGeometry : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("D2FDF2A0-1E48-4075-814A-685D91A6CD94");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("FF");

    public FormByGeometry() : base
    (
      "Form.ByGeometry", "ByGeometry",
      "Create a FreeForm element from geometry",
      "Revit", "Family"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Form", "F", "New Form", GH_ParamAccess.item);
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
      var element = PreviousElement(doc, Iteration);
      try
      {
        if (element?.Pinned ?? true)
        {
          if (brep == null)
          {
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' must be valid Brep.", Params.Input[0].Name));
          }
          else
          {
            var scaleFactor = 1.0 / Revit.ModelUnits;
            if (scaleFactor != 1.0)
              brep.Scale(scaleFactor);

            if (brep.TryGetExtrusion(out var extrusion))
            {
              var sketchPlane = SketchPlane.Create(doc, extrusion.GetProfilePlane(0.0).ToHost());

              var referenceArray = new ReferenceArray();
              foreach (var curve in extrusion.Profile3d(new Rhino.Geometry.ComponentIndex(Rhino.Geometry.ComponentIndexType.ExtrusionBottomProfile, 0)).ToHost())
                referenceArray.Append(new Reference(doc.FamilyCreate.NewModelCurve(curve, sketchPlane)));

              element = doc.FamilyCreate.NewExtrusionForm
              (
                brep.SolidOrientation != Rhino.Geometry.BrepSolidOrientation.Inward,
                referenceArray, extrusion.PathLineCurve().Line.Direction.ToHost()
              );
            }
            else
            {
              var solids = brep.ToHost().ToArray();
              if (solids.Length == 1 && (solids[0] is Solid solid))
              {
                if (element is FreeFormElement freeFormElement)
                  freeFormElement.UpdateSolidGeometry(solid);
                else
                  element = Autodesk.Revit.DB.FreeFormElement.Create(doc, solid);
              }
            }
          }
        }
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
      }
      finally
      {
        ReplaceElement(doc, DA, Iteration, element);
      }
    }
  }
}
