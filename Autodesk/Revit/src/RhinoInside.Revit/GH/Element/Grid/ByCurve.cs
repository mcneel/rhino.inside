using System;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class GridByCurve : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("CEC2B3DF-C6BA-414F-BECE-E3DAEE2A3F2C");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public GridByCurve() : base
    (
      "AddGrid.ByCurve", "ByCurve",
      "Given its Axis, it adds a Grid element to the active Revit document",
      "Revit", "Datum"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Grid", "G", "New Grid", GH_ParamAccess.item);
    }

    void ReconstructGridByCurve
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Curve curve,
      Optional<Autodesk.Revit.DB.GridType> type
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      if (scaleFactor != 1.0)
      {
        curve.Scale(scaleFactor);
      }

      SolveOptionalType(ref type, doc, ElementTypeGroup.GridType, nameof(type));

      if (curve.TryGetLine(out var line, Revit.VertexTolerance))
      {
        ReplaceElement(ref element, Grid.Create(doc, line.ToHost()));
        ChangeElementTypeId(ref element, type.Value.Id);
      }
      else if (curve.TryGetArc(out var arc, Revit.VertexTolerance))
      {
        ReplaceElement(ref element, Grid.Create(doc, arc.ToHost()));
        ChangeElementTypeId(ref element, type.Value.Id);
      }
      else
      {
        using (var curveLoop = new CurveLoop())
        using (var polyline = curve.ToArcsAndLines(Revit.VertexTolerance, Revit.AngleTolerance, Revit.ShortCurveTolerance, double.PositiveInfinity))
        {
          int count = polyline.SegmentCount;
          for (int s = 0; s < count; ++s)
          {
            var segment = polyline.SegmentCurve(s);

            if (segment is Rhino.Geometry.LineCurve l)
              curveLoop.Append(l.ToHost());
            else if (segment is Rhino.Geometry.ArcCurve a)
              curveLoop.Append(a.ToHost());
            else
              ThrowArgumentException(nameof(curve), "Invalid curve type.");
          }

          curve.TryGetPlane(out var plane);
          var sketchPlane = SketchPlane.Create(doc, plane.ToHost());

          var parametersMask = new BuiltInParameter[]
          {
            BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
            BuiltInParameter.ELEM_FAMILY_PARAM,
            BuiltInParameter.ELEM_TYPE_PARAM
          };

          ReplaceElement(ref element, doc.GetElement(MultiSegmentGrid.Create(doc, type.Value.Id, curveLoop, sketchPlane.Id)), parametersMask);
        }
      }
    }
  }
}
