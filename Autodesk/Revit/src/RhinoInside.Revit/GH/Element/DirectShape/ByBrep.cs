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
  public class BrepShapeByBrep : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("5ADE9AE3-588C-4285-ABC5-09DEB92C6660");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("B");

    public BrepShapeByBrep() : base
    (
      "AddBrepShape.ByBrep", "ByBrep",
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
      manager.AddParameter(new Parameters.Element(), "Brep", "B", "New BrepShape", GH_ParamAccess.item);
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
        if (brep == null || !brep.IsValid)
          throw new Exception(string.Format("Parameter '{0}' must be valid Brep.", Params.Input[0].Name));

        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
          brep.Scale(scaleFactor);

        var shape = new List<GeometryObject>();

        foreach (var geometry in brep.ToHost().SelectMany(x => x.ToDirectShapeGeometry()))
        {
          // DirectShape only accepts those types and no nulls
          switch (geometry)
          {
            case Point p: shape.Add(p); break;
            case Curve c: shape.Add(c); break;
            case Solid s: shape.Add(s); break;
            case Mesh m: shape.Add(m); break;
          }
        }

        var ds = element as DirectShape ?? CopyParametersFrom(DirectShape.CreateElement(doc, new ElementId(BuiltInCategory.OST_GenericModel)), element);
        ds.SetShape(shape);
        element = ds;

        ReplaceElement(doc, DA, Iteration, element);
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
        ReplaceElement(doc, DA, Iteration, null);
      }
    }
  }
}
