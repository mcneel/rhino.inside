using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class WallByCurve : GH_TransactionalComponent
  {
    public override Guid ComponentGuid => new Guid("37A8C46F-CB5B-49FD-A483-B03D1FE14A22");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("W");

    public WallByCurve() : base
    (
      "Wall.ByCurve", "ByCurve",
      "Create a Wall element from a curve",
      "Revit", "Wall"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Axis", "A", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.Element(), "FamilyType", "F", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Level", "L", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager.AddBooleanParameter("Structural", "S", string.Empty, GH_ParamAccess.item, true);
      manager[manager.AddNumberParameter("Height", "H", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Wall", "W", "New Wall", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Curve axis = null;
      DA.GetData("Axis", ref axis);

      WallType wallType = null;
      if (!DA.GetData("FamilyType", ref wallType) && Params.Input[1].Sources.Count == 0)
        wallType = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultElementTypeId(ElementTypeGroup.WallType)) as WallType;

      Autodesk.Revit.DB.Level level = null;
      DA.GetData("Level", ref level);
      if (level == null && axis != null)
      {
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          foreach (var levelN in collector.OfClass(typeof(Level)).ToElements().Cast<Level>().OrderBy(c => c.Elevation))
          {
            if (level == null)
              level = levelN;
            else if (axis.PointAtStart.Z >= levelN.Elevation)
              level = levelN;
          }
        }
      }

      bool structural = true;
      DA.GetData("Structural", ref structural);

      double height = 0.0;
      if (!DA.GetData("Height", ref height))
      {
        switch (Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem)
        {
          case Rhino.UnitSystem.None:
          case Rhino.UnitSystem.Inches:
          case Rhino.UnitSystem.Feet:
            height = 10.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Feet, Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem);
            break;
          default:
            height = 3.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Meters, Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem);
            break;
        }
      }

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, axis, wallType, level, structural, height));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Curve curve,
      Autodesk.Revit.DB.WallType wallType,
      Autodesk.Revit.DB.Level level,
      bool structural,
      double height
    )
    {
      Autodesk.Revit.DB.Wall wall = null;
      try
      {
        height /= Revit.ModelUnits;

        if
        (
          curve == null ||
          curve.IsShort(Revit.ShortCurveTolerance) ||
          !(curve.IsArc(Revit.VertexTolerance) || curve.IsLinear(Revit.VertexTolerance)) ||
          !curve.TryGetPlane(out var axisPlane, Revit.VertexTolerance) ||
          axisPlane.ZAxis.IsParallelTo(Rhino.Geometry.Vector3d.ZAxis) == 0
        )
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' must be a horizontal line or arc curve.", Params.Input[0].Name));
        }
        else if (level == null)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' no suitable level is been found.", Params.Input[3].Name));
        }
        else if (height < Revit.VertexTolerance)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' is too small.", Params.Input[5].Name));
        }
        else
        {
          var axisList = curve.ToHost().ToList();
          Debug.Assert(axisList.Count == 1);

          wall = Autodesk.Revit.DB.Wall.Create(doc, axisList[0], wallType.Id, level.Id, height, axisPlane.Origin.Z - level.Elevation, false, structural);
        }
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
      }
      finally
      {
        ReplaceElement(doc, DA, Iteration, wall);
      }
    }
  }
}
