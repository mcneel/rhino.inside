using System;
using System.Diagnostics;
using System.Linq;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class BeamByCurve : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("26411AA6-8187-49DF-A908-A292A07918F1");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public BeamByCurve() : base
    (
      "AddBeam.ByCurve", "ByCurve",
      "Given its Axis, it adds a Beam element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Beam", "B", "New Beam", GH_ParamAccess.item);
    }

    void ReconstructBeamByCurve
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

                 Rhino.Geometry.Curve curve,
      Optional<Autodesk.Revit.DB.FamilySymbol> type,
      Optional<Autodesk.Revit.DB.Level> level
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      if
      (
        ((curve = curve.ChangeUnits(scaleFactor)) is null) ||
        curve.IsClosed ||
        !curve.TryGetPlane(out var axisPlane, Revit.VertexTolerance) ||
        curve.GetNextDiscontinuity(Rhino.Geometry.Continuity.C2_continuous, curve.Domain.Min, curve.Domain.Max, out double discontinuity)
      )
        ThrowArgumentException(nameof(curve), "Curve must be a C2 continuous planar non closed curve.");

      SolveOptionalType(ref type, doc, BuiltInCategory.OST_StructuralFraming, nameof(type));

      if (!type.Value.IsActive)
        type.Value.Activate();

      SolveOptionalLevel(ref level, doc, curve, nameof(level));

      var centerLine = curve.ToHost();

      // Type
      ChangeElementTypeId(ref element, type.Value.Id);

      if (element is FamilyInstance && element.Location is LocationCurve locationCurve && centerLine.IsSameKindAs(locationCurve.Curve))
      {
        locationCurve.Curve = centerLine;
      }
      else
      {
        var newBeam = doc.Create.NewFamilyInstance
        (
          centerLine,
          type.Value,
          level.Value,
          Autodesk.Revit.DB.Structure.StructuralType.Beam
        );

        var parametersMask = new BuiltInParameter[]
        {
          BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
          BuiltInParameter.ELEM_FAMILY_PARAM,
          BuiltInParameter.ELEM_TYPE_PARAM,
          BuiltInParameter.LEVEL_PARAM
        };

        ReplaceElement(ref element, newBeam);
      }
    }
  }
}
