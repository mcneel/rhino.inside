using System;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class RoofByOutline : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("198E152B-6636-4D90-9443-AE77B8B1475E");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public RoofByOutline() : base
    (
      "AddRoof.ByOutline", "ByOutline",
      "Given its outline curve, it adds a Roof element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Roof", "R", "New Roof", GH_ParamAccess.item);
    }

    void ReconstructRoofByOutline
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Curve boundary,
      Optional<Autodesk.Revit.DB.RoofType> type,
      Optional<Autodesk.Revit.DB.Level> level
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      if
      (
        ((boundary = boundary.ChangeUnits(scaleFactor)) is null) ||
        boundary.IsShort(Revit.ShortCurveTolerance) ||
        !boundary.IsClosed ||
        !boundary.TryGetPlane(out var boundaryPlane, Revit.VertexTolerance) ||
        boundaryPlane.ZAxis.IsParallelTo(Rhino.Geometry.Vector3d.ZAxis) == 0
      )
        ThrowArgumentException(nameof(boundary), "Boundary must be an horizontal planar closed curve.");

      SolveOptionalType(ref type, doc, ElementTypeGroup.RoofType, nameof(type));

      double minZ = boundary.GetBoundingBox(true).Min.Z;
      SolveOptionalLevel(ref level, doc, minZ, nameof(level));

      var parametersMask = new BuiltInParameter[]
      {
        BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
        BuiltInParameter.ELEM_FAMILY_PARAM,
        BuiltInParameter.ELEM_TYPE_PARAM,
        BuiltInParameter.LEVEL_PARAM,
        BuiltInParameter.ROOF_LEVEL_OFFSET_PARAM
      };

      using (var curveArray = boundary.ToHostMultiple().ToCurveArray())
      {
        var modelCurveArray = new ModelCurveArray();
        ReplaceElement(ref element, doc.Create.NewFootPrintRoof(curveArray, level.Value, type.Value, out modelCurveArray), parametersMask);
      }

      if (element != null)
      {
        element.get_Parameter(BuiltInParameter.ROOF_LEVEL_OFFSET_PARAM).Set(minZ - level.Value.Elevation);
      }
    }
  }
}
