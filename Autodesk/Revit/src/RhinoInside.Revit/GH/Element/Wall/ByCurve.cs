using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class WallByCurve : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("37A8C46F-CB5B-49FD-A483-B03D1FE14A22");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

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

    protected override void OnAfterStart(Document document, string strTransactionName)
    {
      base.OnAfterStart(document, strTransactionName);

      // Disable all previous walls joins
      if (PreviousStructure is object)
      {
        var unjoinedWalls = PreviousStructure.OfType<Types.Element>().
                            Select(x => document.GetElement(x)).
                            OfType<Wall>().
                            Where(x => x.Pinned).
                            Select
                            (
                              x => Tuple.Create
                              (
                                x,
                                (x.Location as LocationCurve).get_JoinType(0),
                                (x.Location as LocationCurve).get_JoinType(1)
                              )
                            ).
                            ToArray();

        foreach(var unjoinedWall in unjoinedWalls)
        {
          var location = unjoinedWall.Item1.Location as LocationCurve;
          if (!WallUtils.IsWallJoinAllowedAtEnd(unjoinedWall.Item1, 0))
          {          
            WallUtils.DisallowWallJoinAtEnd(unjoinedWall.Item1, 0);
            WallUtils.AllowWallJoinAtEnd(unjoinedWall.Item1, 0);
            location.set_JoinType(0, unjoinedWall.Item2);
          }

          if (!WallUtils.IsWallJoinAllowedAtEnd(unjoinedWall.Item1, 0))
          {
            WallUtils.DisallowWallJoinAtEnd(unjoinedWall.Item1, 1);
            WallUtils.AllowWallJoinAtEnd(unjoinedWall.Item1, 1);
            location.set_JoinType(1, unjoinedWall.Item3);
          }
        }

        document.Regenerate();
      }
    }

    List<Wall> joinedWalls = new List<Wall>();
    protected override void OnBeforeCommit(Document document, string strTransactionName)
    {
      base.OnBeforeCommit(document, strTransactionName);

      // Reenable new joined walls
      foreach (var wallToJoin in joinedWalls)
      {
        WallUtils.AllowWallJoinAtEnd(wallToJoin, 0);
        WallUtils.AllowWallJoinAtEnd(wallToJoin, 1);
      }

      joinedWalls = new List<Wall>();
    }

    static readonly FailureDefinitionId[] failureDefinitionIdsToFix = new FailureDefinitionId[]
    {
      BuiltInFailures.CreationFailures.CannotDrawWallsError,
      BuiltInFailures.JoinElementsFailures.CannotJoinElementsError,
    };
    protected override IEnumerable<FailureDefinitionId> FailureDefinitionIdsToFix => failureDefinitionIdsToFix;

    void ReconstructWallByCurve
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Curve curve,
      Optional<Autodesk.Revit.DB.WallType> type,
      Optional<Autodesk.Revit.DB.Level> level,
      [Optional] bool structural,
      [Optional] double height,
      [Optional] WallLocationLine locationLine,
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

      SolveOptionalType(ref type, doc, ElementTypeGroup.WallType, nameof(type));

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
      if (locationLine != WallLocationLine.WallCenterline)
      {
        double offsetDist = 0.0;
        var compoundStructure = type.Value.GetCompoundStructure();
        if (compoundStructure == null)
        {
          switch (locationLine)
          {
            case WallLocationLine.WallCenterline:
            case WallLocationLine.CoreCenterline:
              break;
            case WallLocationLine.FinishFaceExterior:
            case WallLocationLine.CoreExterior:
              offsetDist = type.Value.Width / +2.0;
              break;
            case WallLocationLine.FinishFaceInterior:
            case WallLocationLine.CoreInterior:
              offsetDist = type.Value.Width / -2.0;
              break;
          }
        }
        else
        {
          if (!compoundStructure.IsVerticallyHomogeneous())
            compoundStructure = CompoundStructure.CreateSimpleCompoundStructure(compoundStructure.GetLayers());

          offsetDist = compoundStructure.GetOffsetForLocationLine(locationLine);
        }

        if (offsetDist != 0.0)
          centerLine = centerLine.CreateOffset(flipped ? -offsetDist : offsetDist, XYZ.BasisZ);
      }

      // Type
      ChangeElementTypeId(ref element, type.Value.Id);

      Wall newWall = null;
      if (element is Wall previousWall && previousWall.Location is LocationCurve locationCurve && centerLine.IsSameKindAs(locationCurve.Curve))
      {
        newWall = previousWall;

        locationCurve.Curve = centerLine;
      }
      else
      {
        newWall = Wall.Create
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

        var parametersMask = new BuiltInParameter[]
        {
          BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
          BuiltInParameter.ELEM_FAMILY_PARAM,
          BuiltInParameter.ELEM_TYPE_PARAM,
          BuiltInParameter.WALL_BASE_CONSTRAINT,
          BuiltInParameter.WALL_USER_HEIGHT_PARAM,
          BuiltInParameter.WALL_BASE_OFFSET,
          BuiltInParameter.WALL_STRUCTURAL_SIGNIFICANT,
          BuiltInParameter.WALL_KEY_REF_PARAM
        };

        ReplaceElement(ref element, newWall, parametersMask);
      }

      if (newWall != null)
      {
        newWall.get_Parameter(BuiltInParameter.WALL_BASE_CONSTRAINT).Set(level.Value.Id);
        newWall.get_Parameter(BuiltInParameter.WALL_BASE_OFFSET).Set(levelIsEmpty ? axisMinZ - level.Value.Elevation : 0.0);
        newWall.get_Parameter(BuiltInParameter.WALL_USER_HEIGHT_PARAM).Set(height);
        newWall.get_Parameter(BuiltInParameter.WALL_STRUCTURAL_SIGNIFICANT).Set(structural ? 1 : 0);
        newWall.get_Parameter(BuiltInParameter.WALL_KEY_REF_PARAM).Set((int) locationLine);

        if (newWall.Flipped != flipped)
          newWall.Flip();

        // Setup joins in a last step
        if (allowJoins) joinedWalls.Add(newWall);
        else
        {
          WallUtils.DisallowWallJoinAtEnd(newWall, 0);
          WallUtils.DisallowWallJoinAtEnd(newWall, 1);
        }
      }
    }
  }
}
