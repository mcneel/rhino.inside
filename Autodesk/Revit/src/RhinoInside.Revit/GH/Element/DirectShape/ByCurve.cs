using System;
using System.Linq;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Components
{
  public class DirectShapeByCurve : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("77F4FBDD-8A05-44A3-AC54-E52A79CF3E5A");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public DirectShapeByCurve() : base
    (
      "AddDirectShape.ByCurve", "ByCurve",
      "Given a Curve, it adds a Curve shape to the active Revit document",
      "Revit", "Geometry"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Curve", "C", "New CurveShape", GH_ParamAccess.item);
    }

    void ReconstructDirectShapeByCurve
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Curve curve
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      ThrowIfNotValid(nameof(curve), curve);

      if (element is DirectShape ds) { }
      else ds = DirectShape.CreateElement(doc, new ElementId(BuiltInCategory.OST_GenericModel));

      var shape = curve.
                  ToHost(scaleFactor).
                  SelectMany(x => x.ToDirectShapeGeometry());

      ds.SetShape(shape.ToList());

      ReplaceElement(ref element, ds);
    }
  }
}
