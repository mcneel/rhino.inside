using System;
using System.Collections.Generic;
using System.Linq;
using Autodesk.Revit.DB;
using Autodesk.Revit.DB.Architecture;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class BuildingPadByOutline : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("ADE71474-5F00-4BD5-9D1E-D518B42137F2");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public BuildingPadByOutline() : base
    (
      "AddBuildingPad.ByOutline", "ByOutline",
      "Given a set of contour Curves, it adds a BuildingPad element to the active Revit document",
      "Revit", "Site"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "BuildingPad", "BP", "New BuildingPad", GH_ParamAccess.item);
    }

    void ReconstructBuildingPadByOutline
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      IList<Rhino.Geometry.Curve> boundaries,
      Optional<Autodesk.Revit.DB.BuildingPadType> type,
      Optional<Autodesk.Revit.DB.Level> level
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      if (scaleFactor != 1.0)
      {
        foreach (var boundary in boundaries)
          boundary.Scale(scaleFactor);
      }

      var boundaryBBox = Rhino.Geometry.BoundingBox.Empty;
      foreach (var boundary in boundaries)
        boundaryBBox.Union(boundary.GetBoundingBox(true));

      SolveOptionalType(ref type, doc, ElementTypeGroup.BuildingPadType, (document, param) => BuildingPadType.CreateDefault(document), nameof(type));

      SolveOptionalLevel(ref level, doc, boundaryBBox.Min.Z, nameof(level));

      var curveLoops = boundaries.Select(region => CurveLoop.Create(region.ToHost().SelectMany(x => x.ToBoundedCurves()).ToList()));

      // Type
      ChangeElementTypeId(ref element, type.Value.Id);

      if (element is BuildingPad buildingPad)
      {
        buildingPad.SetBoundary(curveLoops.ToList());
      }
      else
      {
        ReplaceElement(ref element, BuildingPad.Create(doc, type.Value.Id, level.Value.Id, curveLoops.ToList()));
      }

      if (element != null)
      {
        element.get_Parameter(BuiltInParameter.TYPE_WALL_CLOSURE).Set(level.Value.Id);
        element.get_Parameter(BuiltInParameter.LEVEL_PARAM).Set(level.Value.Id);
        element.get_Parameter(BuiltInParameter.BUILDINGPAD_HEIGHTABOVELEVEL_PARAM).Set(boundaryBBox.Min.Z - level.Value.Elevation);
      }
    }
  }
}
