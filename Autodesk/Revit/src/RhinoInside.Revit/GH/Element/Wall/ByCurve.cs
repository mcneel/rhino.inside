using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class WallByCurve : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("37A8C46F-CB5B-49FD-A483-B03D1FE14A22");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public WallByCurve() : base
    (
      "AddWall.ByCurve", "ByCurve",
      "Given a curve, it adds a Wall element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Wall", "W", "New Wall", GH_ParamAccess.item);
    }

    protected override void OnAfterStart(DB.Document document, string strTransactionName)
    {
      base.OnAfterStart(document, strTransactionName);

      // Disable all previous walls joins
      if (PreviousStructure is object)
      {
        var unjoinedWalls = PreviousStructure.OfType<Types.Element>().
                            Select(x => document.GetElement(x)).
                            OfType<DB.Wall>().
                            Where(x => x.Pinned).
                            Select
                            (
                              x => Tuple.Create
                              (
                                x,
                                (x.Location as DB.LocationCurve).get_JoinType(0),
                                (x.Location as DB.LocationCurve).get_JoinType(1)
                              )
                            ).
                            ToArray();

        foreach(var unjoinedWall in unjoinedWalls)
        {
          var location = unjoinedWall.Item1.Location as DB.LocationCurve;
          if (DB.WallUtils.IsWallJoinAllowedAtEnd(unjoinedWall.Item1, 0))
          {
            DB.WallUtils.DisallowWallJoinAtEnd(unjoinedWall.Item1, 0);
            DB.WallUtils.AllowWallJoinAtEnd(unjoinedWall.Item1, 0);
            location.set_JoinType(0, unjoinedWall.Item2);
          }

          if (DB.WallUtils.IsWallJoinAllowedAtEnd(unjoinedWall.Item1, 1))
          {
            DB.WallUtils.DisallowWallJoinAtEnd(unjoinedWall.Item1, 1);
            DB.WallUtils.AllowWallJoinAtEnd(unjoinedWall.Item1, 1);
            location.set_JoinType(1, unjoinedWall.Item3);
          }
        }
      }
    }

    List<DB.Wall> joinedWalls = new List<DB.Wall>();
    protected override void OnBeforeCommit(DB.Document document, string strTransactionName)
    {
      base.OnBeforeCommit(document, strTransactionName);

      // Reenable new joined walls
      foreach (var wallToJoin in joinedWalls)
      {
        DB.WallUtils.AllowWallJoinAtEnd(wallToJoin, 0);
        DB.WallUtils.AllowWallJoinAtEnd(wallToJoin, 1);
      }

      joinedWalls = new List<DB.Wall>();
    }

    static readonly DB.FailureDefinitionId[] failureDefinitionIdsToFix = new DB.FailureDefinitionId[]
    {
      DB.BuiltInFailures.CreationFailures.CannotDrawWallsError,
      DB.BuiltInFailures.JoinElementsFailures.CannotJoinElementsError,
    };
    protected override IEnumerable<DB.FailureDefinitionId> FailureDefinitionIdsToFix => failureDefinitionIdsToFix;

    void ReconstructWallByCurve
    (
      DB.Document doc,
      ref DB.Element element,

      Rhino.Geometry.Curve curve,
      Optional<DB.WallType> type,
      Optional<DB.Level> level,
      [Optional] bool structural,
      [Optional] double height,
      [Optional] DB.WallLocationLine locationLine,
      [Optional] bool flipped,
      [Optional, NickName("J")] bool allowJoins
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

#if REVIT_2020
      if
      (
        ((curve = curve.ChangeUnits(scaleFactor)) is null) ||
        !(curve.IsLinear(Revit.VertexTolerance) || curve.IsArc(Revit.VertexTolerance) || curve.IsEllipse(Revit.VertexTolerance)) ||
        !curve.TryGetPlane(out var axisPlane, Revit.VertexTolerance) ||
        axisPlane.ZAxis.IsParallelTo(Rhino.Geometry.Vector3d.ZAxis) == 0
      )
        ThrowArgumentException(nameof(curve), "Curve must be a horizontal line, arc or ellipse curve.");
#else
      if
      (
        ((curve = curve.ChangeUnits(scaleFactor)) is null) ||
        !(curve.IsLinear(Revit.VertexTolerance) || curve.IsArc(Revit.VertexTolerance)) ||
        !curve.TryGetPlane(out var axisPlane, Revit.VertexTolerance) ||
        axisPlane.ZAxis.IsParallelTo(Rhino.Geometry.Vector3d.ZAxis) == 0
      )
        ThrowArgumentException(nameof(curve), "Curve must be a horizontal line or arc curve.");
#endif

      SolveOptionalType(ref type, doc, DB.ElementTypeGroup.WallType, nameof(type));

      double axisMinZ = Math.Min(curve.PointAtStart.Z, curve.PointAtEnd.Z);
      bool levelIsEmpty = SolveOptionalLevel(ref level, doc, curve, nameof(level));

      height *= scaleFactor;
      if (height < Revit.VertexTolerance)
        height = (type.HasValue ? type.Value : null)?.GetCompoundStructure()?.SampleHeight ?? LiteralLengthValue(6.0) / Revit.ModelUnits;

      // Axis
      var levelPlane = new Rhino.Geometry.Plane(new Rhino.Geometry.Point3d(0.0, 0.0, level.Value.Elevation), Rhino.Geometry.Vector3d.ZAxis);
      curve = Rhino.Geometry.Curve.ProjectToPlane(curve, levelPlane);

      var centerLine = curve.ToHost();

      // LocationLine
      if (locationLine != DB.WallLocationLine.WallCenterline)
      {
        double offsetDist = 0.0;
        var compoundStructure = type.Value.GetCompoundStructure();
        if (compoundStructure == null)
        {
          switch (locationLine)
          {
            case DB.WallLocationLine.WallCenterline:
            case DB.WallLocationLine.CoreCenterline:
              break;
            case DB.WallLocationLine.FinishFaceExterior:
            case DB.WallLocationLine.CoreExterior:
              offsetDist = type.Value.Width / +2.0;
              break;
            case DB.WallLocationLine.FinishFaceInterior:
            case DB.WallLocationLine.CoreInterior:
              offsetDist = type.Value.Width / -2.0;
              break;
          }
        }
        else
        {
          if (!compoundStructure.IsVerticallyHomogeneous())
            compoundStructure = DB.CompoundStructure.CreateSimpleCompoundStructure(compoundStructure.GetLayers());

          offsetDist = compoundStructure.GetOffsetForLocationLine(locationLine);
        }

        if (offsetDist != 0.0)
          centerLine = centerLine.CreateOffset(flipped ? -offsetDist : offsetDist, DB.XYZ.BasisZ);
      }

      // Type
      ChangeElementTypeId(ref element, type.Value.Id);

      DB.Wall newWall = null;
      if (element is DB.Wall previousWall && previousWall.Location is DB.LocationCurve locationCurve && centerLine.IsSameKindAs(locationCurve.Curve))
      {
        newWall = previousWall;

        locationCurve.Curve = centerLine;
      }
      else
      {
        newWall = DB.Wall.Create
        (
          doc,
          centerLine,
          type.Value.Id,
          level.Value.Id,
          height,
          levelIsEmpty ? axisMinZ - level.Value.Elevation : 0.0,
          flipped,
          structural
        );

        // Walls are created with the last LocationLine used in the Revit editor!!
        //newWall.get_Parameter(BuiltInParameter.WALL_KEY_REF_PARAM).Set((int) WallLocationLine.WallCenterline);

        var parametersMask = new DB.BuiltInParameter[]
        {
          DB.BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
          DB.BuiltInParameter.ELEM_FAMILY_PARAM,
          DB.BuiltInParameter.ELEM_TYPE_PARAM,
          DB.BuiltInParameter.WALL_BASE_CONSTRAINT,
          DB.BuiltInParameter.WALL_USER_HEIGHT_PARAM,
          DB.BuiltInParameter.WALL_BASE_OFFSET,
          DB.BuiltInParameter.WALL_STRUCTURAL_SIGNIFICANT,
          DB.BuiltInParameter.WALL_KEY_REF_PARAM
        };

        ReplaceElement(ref element, newWall, parametersMask);
      }

      if (newWall != null)
      {
        newWall.get_Parameter(DB.BuiltInParameter.WALL_BASE_CONSTRAINT).Set(level.Value.Id);
        newWall.get_Parameter(DB.BuiltInParameter.WALL_BASE_OFFSET).Set(levelIsEmpty ? axisMinZ - level.Value.Elevation : 0.0);
        newWall.get_Parameter(DB.BuiltInParameter.WALL_USER_HEIGHT_PARAM).Set(height);
        newWall.get_Parameter(DB.BuiltInParameter.WALL_STRUCTURAL_SIGNIFICANT).Set(structural ? 1 : 0);
        newWall.get_Parameter(DB.BuiltInParameter.WALL_KEY_REF_PARAM).Set((int) locationLine);

        if (newWall.Flipped != flipped)
          newWall.Flip();

        // Setup joins in a last step
        if (allowJoins) joinedWalls.Add(newWall);
        else
        {
          DB.WallUtils.DisallowWallJoinAtEnd(newWall, 0);
          DB.WallUtils.DisallowWallJoinAtEnd(newWall, 1);
        }
      }
    }
  }
}
