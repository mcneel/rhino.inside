using System;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Types
{
  public class Family : Element
  {
    public override string TypeName => "Revit Family";
    public override string TypeDescription => "Represents a Revit family";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Family);
    public static explicit operator Autodesk.Revit.DB.Family(Family self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.Family;

    public Family() { }
    public Family(Autodesk.Revit.DB.Family family) : base(family) { }

    public override string ToString()
    {
      if (IsValid)
      {
        var family = (Autodesk.Revit.DB.Family) this;
        if (family is object)
        {
          var ToolTip = string.Empty;
          if (family.FamilyCategory is object)
            ToolTip += $"{family.FamilyCategory.Name} : ";

          if (!string.IsNullOrEmpty(family.Name))
            ToolTip += $"{family.Name} : ";

          return $"{ToolTip}id {family.Id}";
        }
      }

      return base.ToString();
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Family : ElementIdNonGeometryParam<Types.Family, Autodesk.Revit.DB.Family>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    public override Guid ComponentGuid => new Guid("3966ADD8-07C0-43E7-874B-6EFF95598EB0");

    public Family() : base("Family", "Family", "Represents a Revit document family.", "Params", "Revit") { }
  }
}
