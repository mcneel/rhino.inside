using System;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Types
{
  public class DatumPlane : Element
  {
    public override string TypeName => "Revit DatumPlane";
    public override string TypeDescription => "Represents a Revit DatumPlane";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.DatumPlane);
    public static explicit operator Autodesk.Revit.DB.DatumPlane(DatumPlane self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.DatumPlane;

    public DatumPlane() { }
    public DatumPlane(Autodesk.Revit.DB.DatumPlane plane) : base(plane) { }
  }

  public class Level : DatumPlane
  {
    public override string TypeName => "Revit Level";
    public override string TypeDescription => "Represents a Revit level";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Level);
    public static explicit operator Autodesk.Revit.DB.Level(Level self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.Level;

    public Level() { }
    public Level(Autodesk.Revit.DB.Level level) : base(level) { }

    public override Rhino.Geometry.Point3d Location
    {
      get
      {
        var level = (Autodesk.Revit.DB.Level) this;
        if (level is object)
        {
          var p = new Rhino.Geometry.Point3d(0.0, 0.0, level.Elevation);
          return p.ChangeUnits(Revit.ModelUnits);
        }

        return new Rhino.Geometry.Point3d(double.NaN, double.NaN, double.NaN);
      }
    }
  }

  public class Grid : DatumPlane
  {
    public override string TypeName => "Revit Level";
    public override string TypeDescription => "Represents a Revit level";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Grid);
    public static explicit operator Autodesk.Revit.DB.Grid(Grid self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.Grid;

    public Grid() { }
    public Grid(Autodesk.Revit.DB.Grid grid) : base(grid) { }

    public override Rhino.Geometry.Curve Axis
    {
      get
      {
        var grid = (Autodesk.Revit.DB.Grid) this;
        if(grid is object)
          return grid.Curve.ToRhino().ChangeUnits(Revit.ModelUnits);

        return null;
      }
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Level : GeometricElementT<Types.Level, Autodesk.Revit.DB.Level>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    public override Guid ComponentGuid => new Guid("3238F8BC-8483-4584-B47C-48B4933E478E");

    public Level() : base("Level", "Level", "Represents a Revit document level.", "Params", "Revit") { }
  }

  public class Grid : GeometricElementT<Types.Grid, Autodesk.Revit.DB.Grid>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    public override Guid ComponentGuid => new Guid("7D2FB886-A184-41B8-A7D6-A6FDB85CF4E4");

    public Grid() : base("Grid", "Grid", "Represents a Revit document grid.", "Params", "Revit") { }
  }
}
