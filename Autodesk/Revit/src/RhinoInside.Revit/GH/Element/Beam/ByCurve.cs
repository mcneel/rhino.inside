using System;
using System.Linq;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;
using DB = Autodesk.Revit.DB;

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

    protected override void OnAfterStart(DB.Document document, string strTransactionName)
    {
      base.OnAfterStart(document, strTransactionName);

      // Reset all previous beams joins
      if (PreviousStructure is object)
      {
        var beamsToUnjoin = PreviousStructure.OfType<Types.Element>().
                            Select(x => document.GetElement(x)).
                            OfType<DB.FamilyInstance>().
                            Where(x => x.Pinned);

        foreach (var unjoinedBeam in beamsToUnjoin)
        {
          if (DB.Structure.StructuralFramingUtils.IsJoinAllowedAtEnd(unjoinedBeam, 0))
          {
            DB.Structure.StructuralFramingUtils.DisallowJoinAtEnd(unjoinedBeam, 0);
            DB.Structure.StructuralFramingUtils.AllowJoinAtEnd(unjoinedBeam, 0);
          }

          if (DB.Structure.StructuralFramingUtils.IsJoinAllowedAtEnd(unjoinedBeam, 1))
          {
            DB.Structure.StructuralFramingUtils.DisallowJoinAtEnd(unjoinedBeam, 1);
            DB.Structure.StructuralFramingUtils.AllowJoinAtEnd(unjoinedBeam, 1);
          }
        }
      }
    }

    void ReconstructBeamByCurve
    (
      DB.Document doc,
      ref DB.FamilyInstance element,

               Rhino.Geometry.Curve curve,
      Optional<DB.FamilySymbol> type,
      Optional<DB.Level> level
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      if
      (
        ((curve = curve.ChangeUnits(scaleFactor)) is null) ||
        curve.IsClosed ||
        !curve.TryGetPlane(out var axisPlane, Revit.VertexTolerance) ||
        curve.GetNextDiscontinuity(Rhino.Geometry.Continuity.C2_continuous, curve.Domain.Min, curve.Domain.Max, out var _)
      )
        ThrowArgumentException(nameof(curve), "Curve must be a C2 continuous planar non closed curve.");

      SolveOptionalType(ref type, doc, DB.BuiltInCategory.OST_StructuralFraming, nameof(type));

      if (!type.Value.IsActive)
        type.Value.Activate();

      SolveOptionalLevel(ref level, doc, curve, nameof(level));

      var centerLine = curve.ToHost();

      // Type
      ChangeElementTypeId(ref element, type.Value.Id);

      DB.FamilyInstance newBeam = null;
      if (element is DB.FamilyInstance previousBeam && element.Location is DB.LocationCurve locationCurve && centerLine.IsSameKindAs(locationCurve.Curve))
      {
        newBeam = previousBeam;

        locationCurve.Curve = centerLine;
      }
      else
      {
        newBeam = doc.Create.NewFamilyInstance
        (
          centerLine,
          type.Value,
          level.Value,
          DB.Structure.StructuralType.Beam
        );

        newBeam.get_Parameter(DB.BuiltInParameter.Y_JUSTIFICATION).Set((int) DB.Structure.YJustification.Origin);
        newBeam.get_Parameter(DB.BuiltInParameter.Z_JUSTIFICATION).Set((int) DB.Structure.ZJustification.Origin);

        var beam = element as DB.FamilyInstance;

        if(beam is object && DB.Structure.StructuralFramingUtils.IsJoinAllowedAtEnd(beam, 0))
          DB.Structure.StructuralFramingUtils.AllowJoinAtEnd(newBeam, 0);
        else
          DB.Structure.StructuralFramingUtils.DisallowJoinAtEnd(newBeam, 0);

        if (beam is object && DB.Structure.StructuralFramingUtils.IsJoinAllowedAtEnd(beam, 1))
          DB.Structure.StructuralFramingUtils.AllowJoinAtEnd(newBeam, 1);
        else
          DB.Structure.StructuralFramingUtils.DisallowJoinAtEnd(newBeam, 1);

        var parametersMask = new DB.BuiltInParameter[]
        {
          DB.BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
          DB.BuiltInParameter.ELEM_FAMILY_PARAM,
          DB.BuiltInParameter.ELEM_TYPE_PARAM,
          DB.BuiltInParameter.LEVEL_PARAM
        };

        ReplaceElement(ref element, newBeam, parametersMask);
      }
    }
  }
}
