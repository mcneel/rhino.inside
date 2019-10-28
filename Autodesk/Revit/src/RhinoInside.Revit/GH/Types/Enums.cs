using System;
using System.Linq;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class StorageType : GH_Enum<DB.StorageType> { }

  public class ParameterType : GH_Enum<DB.ParameterType> { }

  public class UnitType : GH_Enum<DB.UnitType> { }

  [
    Guid("3D9979B4-65C8-447F-BCEA-3705249DF3B6"),
    DisplayName("Parameter Group"),
    Description("Represents a Revit parameter group."),
    Exposure(GH_Exposure.quarternary),
  ]
  public class BuiltInParameterGroup : GH_Enum<DB.BuiltInParameterGroup>
  {
    public BuiltInParameterGroup() : base(DB.BuiltInParameterGroup.INVALID) { }
    public override string ToString()
    {
      try { return DB.LabelUtils.GetLabelFor(Value); }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

      return base.ToString();
    }

    public override Array GetEnumValues() =>
      Enum.GetValues(typeof(DB.BuiltInParameterGroup)).
      Cast<DB.BuiltInParameterGroup>().
      Where(x => x != DB.BuiltInParameterGroup.INVALID).
      OrderBy(x => DB.LabelUtils.GetLabelFor(x)).
      ToArray();
  }

  [
    Guid("195B9D7E-D4B0-4335-A442-3C2FA40794A2"),
    DisplayName("Category Type"),
    Description("Represents a Revit parameter category type."),
    Exposure(GH_Exposure.septenary),
  ]
  public class CategoryType : GH_Enum<DB.CategoryType>
  {
    public CategoryType() : base(DB.CategoryType.Invalid) { }
    public CategoryType(DB.CategoryType value) : base(value) { }

    public override Array GetEnumValues() =>
      Enum.GetValues(typeof(DB.CategoryType)).
      Cast<DB.CategoryType>().
      Where(x => x != DB.CategoryType.Invalid).
      ToArray();

    public override string ToString()
    {
      if (Value == DB.CategoryType.AnalyticalModel)
        return "Analytical";

      return base.ToString();
    }
  }

  public class ViewDetailLevel : GH_Enum<DB.ViewDetailLevel> { }

  public class WallLocationLine : GH_Enum<DB.WallLocationLine>
  {
    public override string ToString()
    {
      switch (Value)
      {
        case DB.WallLocationLine.WallCenterline:      return "Wall Centerline";
        case DB.WallLocationLine.CoreCenterline:      return "Core Centerline";
        case DB.WallLocationLine.FinishFaceExterior:  return "Finish Face: Exterior";
        case DB.WallLocationLine.FinishFaceInterior:  return "Finish Face: Interior";
        case DB.WallLocationLine.CoreExterior:        return "Core Face: Exterior";
        case DB.WallLocationLine.CoreInterior:        return "Core Face: Interior";
      }

      return base.ToString();
    }
  }
}
