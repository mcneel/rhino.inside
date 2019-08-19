using System;
using System.Runtime.InteropServices;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class LevelByElevation : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("C6DEC111-EAC6-4047-8618-28EE144D55C5");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public LevelByElevation() : base
    (
      "AddLevel.ByElevation", "ByElevation",
      "Given its Elevation, it adds a Level to the active Revit document",
      "Revit", "Datum"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Level", "L", "New Level", GH_ParamAccess.item);
    }

    void ReconstructLevelByElevation
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      double elevation,
      Optional<Autodesk.Revit.DB.LevelType> type,
      Optional<string> name
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      elevation *= scaleFactor;

      SolveOptionalType(ref type, doc, ElementTypeGroup.LevelType, nameof(type));

      if (element is Level level)
      {
        level.Elevation = elevation;
      }
      else
      {
        var newLevel = Level.Create
        (
          doc,
          elevation
        );

        var parametersMask = name == Optional.Nothig ?
          new BuiltInParameter[]
          {
            BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
            BuiltInParameter.ELEM_FAMILY_PARAM,
            BuiltInParameter.ELEM_TYPE_PARAM
          } :
          new BuiltInParameter[]
          {
            BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
            BuiltInParameter.ELEM_FAMILY_PARAM,
            BuiltInParameter.ELEM_TYPE_PARAM,
            BuiltInParameter.DATUM_TEXT
          };

        ReplaceElement(ref element, newLevel, parametersMask);
      }

      ChangeElementTypeId(ref element, type.Value.Id);

      if (name != Optional.Nothig && element != null)
      {
        try { element.Name = name.Value; }
        catch (Autodesk.Revit.Exceptions.ArgumentException e)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Remark, $"{e.Message.Replace($".{Environment.NewLine}", ". ")}");
        }
      }
    }
  }
}
