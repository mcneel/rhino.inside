using System;
using System.Runtime.InteropServices;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class FloorByOutline : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("DC8DAF4F-CC93-43E2-A871-3A01A920A722");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public FloorByOutline() : base
    (
      "AddFloor.ByOutline", "ByOutline",
      "Given its outline curve, it adds a Floor element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Floor", "F", "New Floor", GH_ParamAccess.item);
    }

    void ReconstructFloorByOutline
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Curve boundary,
      Optional<Autodesk.Revit.DB.FloorType> type,
      Optional<Autodesk.Revit.DB.Level> level,
      [Optional] bool structural
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      if
      (
        scaleFactor != 1.0 ? !boundary.Scale(scaleFactor) : true &&
        !boundary.IsClosed ||
        !boundary.TryGetPlane(out var boundaryPlane, Revit.VertexTolerance) ||
        boundaryPlane.ZAxis.IsParallelTo(Rhino.Geometry.Vector3d.ZAxis) == 0
      )
        ThrowArgumentException(nameof(boundary), "Boundary must be an horizontal planar closed curve.");

      SolveOptionalType(ref type, doc, ElementTypeGroup.FloorType, nameof(type));

      SolveOptionalLevel(ref level, doc, boundary, nameof(level));

      var curveArray = boundary.ToHost().ToCurveArray();

      var parametersMask = new BuiltInParameter[]
      {
        BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
        BuiltInParameter.ELEM_FAMILY_PARAM,
        BuiltInParameter.ELEM_TYPE_PARAM,
        BuiltInParameter.LEVEL_PARAM,
        BuiltInParameter.FLOOR_PARAM_IS_STRUCTURAL
      };

      if (type.Value.IsFoundationSlab)
        ReplaceElement(ref element, doc.Create.NewFoundationSlab(curveArray, type.Value, level.Value, structural, XYZ.BasisZ), parametersMask);
      else
        ReplaceElement(ref element, doc.Create.NewFloor(curveArray, type.Value, level.Value, structural, XYZ.BasisZ), parametersMask);

      if (element != null)
      {
        var boundaryBBox = boundary.GetBoundingBox(true);
        element.get_Parameter(BuiltInParameter.FLOOR_HEIGHTABOVELEVEL_PARAM).Set(boundaryBBox.Min.Z - level.Value.Elevation);
      }
    }
  }
}
