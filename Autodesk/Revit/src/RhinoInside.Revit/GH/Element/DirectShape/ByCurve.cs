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
  public class DirectShapeByCurve : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("77F4FBDD-8A05-44A3-AC54-E52A79CF3E5A");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public DirectShapeByCurve() : base
    (
      "AddDirectShape.ByCurve", "ByCurve",
      "Given a Curve, it adds a Curve shape to the active Revit document",
      "Revit", "Geometry"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Curve", "C", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Curve", "C", "New CurveShape", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Curve curve = null;
      if (!DA.GetData("Curve", ref curve))
        return;

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, (Rhino.Geometry.Curve) curve?.DuplicateShallow()));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Curve curve
    )
    {
      var element = PreviousElement(doc, Iteration);
      try
      {
        if (curve == null)
          throw new NullReferenceException($"Parameter '{Params.Input[0].Name}' not set to an instance of a Curve.");

        if (!curve.IsValidWithLog(out var log))
        {
          foreach (var line in log.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries))
            AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, line);

          throw new Exception($"Parameter '{Params.Input[0].Name}' not set to a valid Curve.");
        }

        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
          curve.Scale(scaleFactor);

        var shape = new List<GeometryObject>();

        foreach (var c in curve.ToHost().SelectMany(x => x.ToDirectShapeGeometry()))
          shape.Add(c);

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
