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
  public class PointShapeByCurve : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("7A889B89-C423-4ED8-91D9-5CECE1EE803D");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("P");

    public PointShapeByCurve() : base
    (
      "AddPointShape.ByCurve", "ByPoint",
      "Given a Point, it adds a Point shape to the active Revit document",
      "Revit", "Geometry"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddPointParameter("Point", "P", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Point", "P", "New PointShape", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var point = new Rhino.Geometry.Point3d(double.NaN, double.NaN, double.NaN);
      if (!DA.GetData("Point", ref point))
        return;

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, point));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Point3d point
    )
    {
      var element = PreviousElement(doc, Iteration);
      try
      {
        if (!point.IsValid)
          throw new Exception($"Parameter '{Params.Input[0].Name}' must be valid Point.");

        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
          point = point.Scale(scaleFactor);

        var shape = new List<GeometryObject> { Point.Create(point.ToHost()) };

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
