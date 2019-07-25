using System;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class ColumnByCurve : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("47B560AC-1E1D-4576-9F17-BCCF612974D8");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public ColumnByCurve() : base
    (
      "AddColumn.ByCurve", "ByCurve",
      "Given its Axis, it adds a structural Column to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Column", "C", "New Column", GH_ParamAccess.item);
    }

    void ReconstructColumnByCurve
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Line curve,
      Optional<Autodesk.Revit.DB.FamilySymbol> type,
      Optional<Autodesk.Revit.DB.Level> level
    )
    {
      if (curve.FromZ > curve.ToZ)
        curve.Flip();

      var scaleFactor = 1.0 / Revit.ModelUnits;
      if (scaleFactor != 1.0)
        curve = curve.Scale(scaleFactor);

      if (curve.Length < Revit.ShortCurveTolerance)
        ThrowArgumentException(nameof(curve), "Curve is too short.");

      SolveOptionalType(ref type, doc, BuiltInCategory.OST_StructuralColumns, nameof(type));

      if (!type.Value.IsActive)
        type.Value.Activate();

      SolveOptionalLevel(ref level, doc, curve.FromZ, nameof(level));

      // Type
      ChangeElementTypeId(ref element, type.Value.Id);

      if (element is FamilyInstance familyInstance && element.Location is LocationCurve locationCurve)
      {
        locationCurve.Curve = curve.ToHost();
      }
      else
      {
        var newColumn = doc.Create.NewFamilyInstance
        (
          curve.ToHost(),
          type.Value,
          level.Value,
          Autodesk.Revit.DB.Structure.StructuralType.Column
        );

        var parametersMask = new BuiltInParameter[]
        {
          BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
          BuiltInParameter.ELEM_FAMILY_PARAM,
          BuiltInParameter.ELEM_TYPE_PARAM,
          BuiltInParameter.LEVEL_PARAM
        };

        ReplaceElement(ref element, newColumn);
      }
    }
  }
}
