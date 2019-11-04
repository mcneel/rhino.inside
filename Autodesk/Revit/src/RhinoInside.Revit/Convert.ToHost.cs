using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using Rhino;
using Rhino.Geometry;
using Rhino.Geometry.Collections;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit
{
  public static partial class Convert
  {
    #region ToHost
    public static DB.Color ToHost(this System.Drawing.Color c)
    {
      return new DB.Color(c.R, c.G, c.B);
    }

    public static DB.XYZ ToHost(this Point3f p)
    {
      return new DB.XYZ(p.X, p.Y, p.Z);
    }

    public static DB.XYZ ToHost(this Point3d p)
    {
      return new DB.XYZ(p.X, p.Y, p.Z);
    }

    public static DB.XYZ ToHost(this Vector3f p)
    {
      return new DB.XYZ(p.X, p.Y, p.Z);
    }

    public static DB.XYZ ToHost(this Vector3d p)
    {
      return new DB.XYZ(p.X, p.Y, p.Z);
    }

    public static DB.Line ToHost(this Line line)
    {
      return DB.Line.CreateBound(line.From.ToHost(), line.To.ToHost());
    }

    public static IEnumerable<DB.Line> ToHostMultiple(this Polyline polyline)
    {
      polyline.ReduceSegments(Revit.ShortCurveTolerance);

      foreach (var segment in polyline.GetSegments())
        yield return DB.Line.CreateBound(segment.From.ToHost(), segment.To.ToHost());
    }

    public static DB.Arc ToHost(this Arc arc)
    {
      if (arc.IsCircle)
        return DB.Arc.Create(arc.Plane.ToHost(), arc.Radius, 0.0, 2.0 * Math.PI);
      else
        return DB.Arc.Create(arc.StartPoint.ToHost(), arc.EndPoint.ToHost(), arc.MidPoint.ToHost());
    }

    public static DB.Arc ToHost(this Circle circle)
    {
      return DB.Arc.Create(circle.Plane.ToHost(), circle.Radius, 0.0, 2.0 * Math.PI);
    }

    public static DB.Curve ToHost(this Ellipse ellipse) => ellipse.ToHost(new Interval(0.0, 2.0 * Math.PI * 2.0));
    public static DB.Curve ToHost(this Ellipse ellipse, Interval interval)
    {
#if REVIT_2018
      return DB.Ellipse.CreateCurve(ellipse.Plane.Origin.ToHost(), ellipse.Radius1, ellipse.Radius2, ellipse.Plane.XAxis.ToHost(), ellipse.Plane.YAxis.ToHost(), interval.Min, interval.Max);
#else
      return DB.Ellipse.Create(ellipse.Plane.Origin.ToHost(), ellipse.Radius1, ellipse.Radius2, ellipse.Plane.XAxis.ToHost(), ellipse.Plane.YAxis.ToHost(), interval.Min, interval.Max);
#endif
    }

    public static DB.Plane ToHost(this Plane plane)
    {
      return DB.Plane.CreateByOriginAndBasis(plane.Origin.ToHost(), plane.XAxis.ToHost(), plane.YAxis.ToHost());
    }

    public static DB.Transform ToHost(this Transform transform)
    {
      Debug.Assert(transform.IsAffine);

      var value = DB.Transform.CreateTranslation(new DB.XYZ(transform.M03, transform.M13, transform.M23));
      value.BasisX = new DB.XYZ(transform.M00, transform.M10, transform.M20);
      value.BasisY = new DB.XYZ(transform.M01, transform.M11, transform.M21);
      value.BasisZ = new DB.XYZ(transform.M02, transform.M12, transform.M22);
      return value;
    }

    public static IEnumerable<DB.XYZ> ToHost(this IEnumerable<Point3d> points)
    {
      return points.Select(p => p.ToHost());
    }

    internal static IList<double> ToHost(this NurbsCurveKnotList knotList)
    {
      var knotListCount = knotList.Count;
      if (knotListCount > 0)
      {
        var knots = new List<double>(knotListCount + 2);

        knots.Add(knotList[0]);
        foreach (var k in knotList)
          knots.Add(k);
        knots.Add(knotList[knotListCount - 1]);

        return knots;
      }

      return new List<double>();
    }

    internal static IList<double> ToHost(this NurbsSurfaceKnotList knotList)
    {
      var knotListCount = knotList.Count;
      if (knotListCount > 0)
      {
        var knots = new List<double>(knotListCount + 2);

        knots.Add(knotList[0]);
        foreach (var k in knotList)
          knots.Add(k);
        knots.Add(knotList[knotListCount - 1]);

        return knots;
      }

      return new List<double>();
    }

    public static DB.Point ToHost(this Point point)
    {
      return DB.Point.Create(ToHost(point.Location));
    }

    public static IEnumerable<DB.Point> ToHostMultiple(this PointCloud pointCloud)
    {
      foreach(var p in pointCloud)
        yield return DB.Point.Create(ToHost(p.Location));
    }

    public static DB.Line ToHost(this LineCurve curve)
    {
      return curve.Line.ToHost();
    }

    public static DB.Arc ToHost(this ArcCurve curve)
    {
      return curve.Arc.ToHost();
    }

    public static DB.Curve ToHost(this NurbsCurve curve)
    {
      if (curve.TryGetArc(out var arc, Revit.VertexTolerance))
        return arc.ToHost();

      if(curve.IsClosed)
      {
        var gap = Revit.ShortCurveTolerance * 1.01;
        var length = curve.GetLength();
        if
        (
          length > gap &&
          curve.LengthParameter(         (gap / 2.0), out var t0) &&
          curve.LengthParameter(length - (gap / 2.0), out var t1)
        )
        {
          var segments = curve.Split(new double[] { t0, t1 });
          curve = segments[0] as NurbsCurve ?? curve;
        }
        else return null;
      }

      curve.Knots.RemoveMultipleKnots(1, curve.Degree, Revit.VertexTolerance);

      var curve_Degree = curve.Degree;
      var knots = curve.Knots.ToHost();
      var controlPoints = curve.Points.Select(p => p.Location.ToHost()).ToArray();

      Debug.Assert(curve_Degree >= 1);
      Debug.Assert(controlPoints.Length > curve_Degree);
      Debug.Assert(knots.Count == curve_Degree + controlPoints.Length + 1);

      if (curve.IsRational)
      {
        var weights = curve.Points.Select(p => p.Weight).ToArray();
        return DB.NurbSpline.CreateCurve(curve.Degree, knots, controlPoints, weights);
      }

      return DB.NurbSpline.CreateCurve(curve.Degree, knots, controlPoints);
    }

    public static DB.Curve ToHost(this Curve curve)
    {
      switch (curve)
      {
        case LineCurve line:

          return line.Line.ToHost();

        case ArcCurve arc:

          return arc.Arc.ToHost();

        case PolylineCurve polyline:

          curve = curve.Simplify
          (
            CurveSimplifyOptions.RebuildLines |
            CurveSimplifyOptions.Merge,
            Revit.VertexTolerance,
            Revit.AngleTolerance
          )
          ?? curve;

          return curve.ToNurbsCurve().ToHost();

        case PolyCurve polyCurve:

          curve = curve.Simplify
          (
            CurveSimplifyOptions.AdjustG1 |
            CurveSimplifyOptions.Merge,
            Revit.VertexTolerance,
            Revit.AngleTolerance
          )
          ?? curve;

          return curve is PolyCurve ? curve.ToNurbsCurve().ToHost() : curve.ToHost();

        case NurbsCurve nurbsCurve:

          if (curve.TryGetEllipse(out var ellipse, out var interval, Revit.VertexTolerance) && ellipse.Radius1 <= 30000 && ellipse.Radius2 <= 30000)
            return ellipse.ToHost(interval);

          return nurbsCurve.ToHost();

        default:
          return curve.ToNurbsCurve().ToHost();
      }
    }

    public static IEnumerable<DB.Curve> ToHostMultiple(this Curve curve)
    {
      switch (curve)
      {
        case LineCurve line:

          yield return line.Line.ToHost();
          yield break;

        case PolylineCurve polyline:

          for (int p = 1; p < polyline.PointCount; ++p)
            yield return DB.Line.CreateBound(polyline.Point(p - 1).ToHost(), polyline.Point(p).ToHost());
          yield break;

        case ArcCurve arc:

          yield return arc.Arc.ToHost();
          yield break;

        case PolyCurve polyCurve:

          polyCurve.RemoveNesting();
          polyCurve.RemoveShortSegments(Revit.ShortCurveTolerance);
          for (int s = 0; s < polyCurve.SegmentCount; ++s)
          {
            foreach (var segment in polyCurve.SegmentCurve(s).ToHostMultiple())
              yield return segment;
          }
          yield break;

        case NurbsCurve nurbsCurve:

          if (nurbsCurve.TryGetLine(out var lineSegment, Revit.VertexTolerance))
          {
            yield return lineSegment.ToHost();
            yield break;
          }

          if (nurbsCurve.TryGetPolyline(out var polylineSegment))
          {
            foreach (var line in polylineSegment.ToHostMultiple())
              yield return line;
            yield break;
          }

          if (nurbsCurve.TryGetEllipse(out var ellipse, out var interval, Revit.VertexTolerance) && ellipse.Radius1 <= 30000 && ellipse.Radius2 <= 30000)
          {
            yield return ellipse.ToHost(interval);
            yield break;
          }

          var simplifiedCurve = curve.Simplify(CurveSimplifyOptions.SplitAtFullyMultipleKnots, Revit.VertexTolerance, Revit.AngleTolerance);
          if (simplifiedCurve is object)
          {
            foreach(var simpleCurve in simplifiedCurve.ToHostMultiple())
              yield return simpleCurve;
            yield break;
          }

          if (nurbsCurve.IsClosed)
          {
            foreach (var segment in nurbsCurve.Split(nurbsCurve.Domain.Mid))
              foreach (var c in segment.ToHostMultiple())
                yield return c;
            yield break;
          }
          else
          {
            nurbsCurve.Knots.RemoveMultipleKnots(1, nurbsCurve.Degree, Revit.VertexTolerance);

            var degree = nurbsCurve.Degree;
            var knots = nurbsCurve.Knots.ToHost();
            var controlPoints = nurbsCurve.Points.Select(p => p.Location.ToHost()).ToArray();

            Debug.Assert(degree >= 1);
            Debug.Assert(controlPoints.Length > nurbsCurve.Degree);
            Debug.Assert(knots.Count == nurbsCurve.Degree + controlPoints.Length + 1);

            DB.Curve nurbSpline = null;

            if (nurbsCurve.IsRational)
            {
              var weights = nurbsCurve.Points.Select(p => p.Weight).ToArray();
              nurbSpline = DB.NurbSpline.CreateCurve(nurbsCurve.Degree, knots, controlPoints, weights);
            }
            else
            {
              nurbSpline = DB.NurbSpline.CreateCurve(nurbsCurve.Degree, knots, controlPoints);
            }

            yield return nurbSpline;
            yield break;
          }

        default:
          foreach (var c in curve.ToNurbsCurve().ToHostMultiple())
            yield return c;
          yield break;
      }
    }

    public static IEnumerable<DB.BRepBuilderEdgeGeometry> ToHostMultiple(this BrepEdge edge)
    {
      var curve = default(DB.Curve);
      switch (edge.EdgeCurve)
      {
        case LineCurve line:   curve = line.Line.ToHost(); break;
        case ArcCurve arc:     curve = arc.Arc.ToHost();   break;
        case NurbsCurve nurbs: curve = nurbs.ToHost();     break;
        default: throw new NotImplementedException("Unsuported curve type for DB.BRepBuilderEdgeGeometry");
      }

      if (edge.ProxyCurveIsReversed)
        curve = curve.CreateReversed();

      return curve.ToBoundedCurves().Select(x => DB.BRepBuilderEdgeGeometry.Create(x));
    }

    static DB.BRepBuilderSurfaceGeometry ToHost(this BrepFace faceSurface)
    {
      using (var nurbsSurface = faceSurface.ToNurbsSurface())
      {
        {
          var domainU = nurbsSurface.Domain(0);
          Debug.Assert(!nurbsSurface.GetNextDiscontinuity(0, Continuity.C2_continuous, domainU.Min, domainU.Max, out var tU));
          var domainV = nurbsSurface.Domain(1);
          Debug.Assert(!nurbsSurface.GetNextDiscontinuity(1, Continuity.C2_continuous, domainV.Min, domainV.Max, out var tV));
        }

        var degreeU = nurbsSurface.Degree(0);
        var degreeV = nurbsSurface.Degree(1);
        var knotsU = nurbsSurface.KnotsU.ToHost();
        var knotsV = nurbsSurface.KnotsV.ToHost();
        var controlPoints = nurbsSurface.Points.Select(p => p.Location.ToHost()).ToList();

        Debug.Assert(degreeU >= 1);
        Debug.Assert(degreeV >= 1);
        Debug.Assert(knotsU.Count >= 2 * (degreeU + 1));
        Debug.Assert(knotsV.Count >= 2 * (degreeV + 1));
        Debug.Assert(controlPoints.Count == (knotsU.Count - degreeU - 1) * (knotsV.Count - degreeV - 1));

        if (nurbsSurface.IsRational)
        {
          var weights = nurbsSurface.Points.Select(p => p.Weight).ToList();

          return DB.BRepBuilderSurfaceGeometry.CreateNURBSSurface
          (
            degreeU, degreeV, knotsU, knotsV, controlPoints, weights, false, null
          );
        }
        else
        {
          return DB.BRepBuilderSurfaceGeometry.CreateNURBSSurface
          (
            degreeU, degreeV, knotsU, knotsV, controlPoints, false, null
          );
        }
      }
    }

    static Brep SplitClosedFaces(Brep brep)
    {
      Brep brepToSplit = null;

      while (brepToSplit != brep && brep is object)
      {
        brep.Standardize();
        brepToSplit = brep;
        foreach (var face in brepToSplit.Faces)
        {
          face.ShrinkFace(BrepFace.ShrinkDisableSide.ShrinkAllSides);

          var face_IsClosed = new bool[2];

          var splitters = new List<Curve>();

          // Compute splitters at C2
          for (int d = 0; d < 2; d++)
          {
            face_IsClosed[d] = face.IsClosed(d);
            var domain = face.Domain(d);
            var t = domain.Min;
            while (face.GetNextDiscontinuity(d, Continuity.C2_continuous, t, domain.Max, out t))
            {
              splitters.AddRange(face.TrimAwareIsoCurve((d == 0) ? 1 : 0, t));
              face_IsClosed[d] = false;
            }
          }

          if (face_IsClosed[0])
            splitters.AddRange(face.TrimAwareIsoCurve(1, face.Domain(0).Mid));

          if (face_IsClosed[1])
            splitters.AddRange(face.TrimAwareIsoCurve(0, face.Domain(1).Mid));

          if (splitters.Count > 0)
          {
            brep = face.Split(splitters, Revit.ShortCurveTolerance);

            if (brep is null)
              return null;

            if(brep.Faces.Count != brepToSplit.Faces.Count)
              break;  // try again until no face is splitted

            // Split was ok but no new faces were created for tolerance reasons
            // Too near from the limits.
            brep = brepToSplit;
          }
        }
      }

      return brep;
    }

    public static DB.Solid ToHost(this Brep brep)
    {
      DB.Solid solid = null;

      // MakeValidForV2 converts everything inside brep to NURBS
      if (brep.MakeValidForV2())
      {
        var splittedBrep = SplitClosedFaces(brep);
        if (splittedBrep is object)
        {
          brep = splittedBrep;

          var brepBuilderOutcome = DB.BRepBuilderOutcome.Failure;

          try
          {
            var brepType = DB.BRepType.OpenShell;
            switch (brep.SolidOrientation)
            {
              case BrepSolidOrientation.Inward: brepType = DB.BRepType.Void; break;
              case BrepSolidOrientation.Outward:brepType = DB.BRepType.Solid; break;
            }

            using (var builder = new DB.BRepBuilder(brepType))
            {
#if REVIT_2018
              builder.AllowRemovalOfProblematicFaces();
              builder.SetAllowShortEdges();
#endif

              var brepEdges = new List<DB.BRepBuilderGeometryId>[brep.Edges.Count];
              foreach (var face in brep.Faces)
              {
                var faceId = builder.AddFace(face.ToHost(), face.OrientationIsReversed);
                builder.SetFaceMaterialId(faceId, Context.Peek.MaterialId);

                foreach (var loop in face.Loops)
                {
                  var loopId = builder.AddLoop(faceId);

                  foreach (var trim in loop.Trims)
                  {
                    if (trim.TrimType != BrepTrimType.Boundary && trim.TrimType != BrepTrimType.Mated)
                      continue;

                    var edge = trim.Edge;
                    if (edge is null)
                      continue;

                    var edgeIds = brepEdges[edge.EdgeIndex];
                    if (edgeIds is null)
                    {
                      edgeIds = brepEdges[edge.EdgeIndex] = new List<DB.BRepBuilderGeometryId>();
                      foreach (var e in edge.ToHostMultiple())
                        edgeIds.Add(builder.AddEdge(e));
                    }

                    if (trim.IsReversed())
                    {
                      for (int e = edgeIds.Count - 1; e >= 0; --e)
                        builder.AddCoEdge(loopId, edgeIds[e], true);
                    }
                    else
                    {
                      for (int e = 0; e < edgeIds.Count; ++e)
                        builder.AddCoEdge(loopId, edgeIds[e], false);
                    }
                  }

                  builder.FinishLoop(loopId);
                }

                builder.FinishFace(faceId);
              }

              brepBuilderOutcome = builder.Finish();
              if (builder.IsResultAvailable())
                solid = builder.GetResult();
            }
          }
          catch (Autodesk.Revit.Exceptions.ApplicationException e)
          {
            // TODO: Fix cases with singularities and uncomment this line
            //Debug.Fail(e.Source, e.Message);
            Debug.WriteLine(e.Message, e.Source);
          }
        }
        else
        {
          Debug.Fail("SplitClosedFaces", "SplitClosedFaces failed to split a closed surface.");
        }
      }

      return solid;
    }

    static IEnumerable<DB.GeometryObject> ToHostMultiple(this Brep brep)
    {
      var solid = brep.ToHost();
      if (solid is object)
      {
        yield return solid;
        yield break;
      }

      if (brep.Faces.Count > 1)
      {
        Debug.WriteLine("Try exploding the brep and converting face by face.", "RhinoInside.Revit.Convert");

        var breps = brep.UnjoinEdges(brep.Edges.Select(x => x.EdgeIndex));
        foreach (var face in breps.SelectMany(x => x.ToHostMultiple()))
          yield return face;
      }
      else
      {
        Debug.WriteLine("Try meshing the brep.", "RhinoInside.Revit.Convert");

        // Emergency result as a mesh
        var mp = MeshingParameters.Default;
        mp.MinimumEdgeLength = Revit.VertexTolerance;
        mp.ClosedObjectPostProcess = true;
        mp.JaggedSeams = false;

        var brepMesh = new Mesh();
        brepMesh.Append(Mesh.CreateFromBrep(brep, mp));

        foreach(var g in brepMesh.ToHostMultiple())
          yield return g;
      }
    }

    public static IEnumerable<DB.GeometryObject> ToHostMultiple(this Mesh mesh)
    {
      var faceVertices = new List<DB.XYZ>(4);

      try
      {
        using
        (
          var builder = new DB.TessellatedShapeBuilder()
          {
            GraphicsStyleId = Context.Peek.GraphicsStyleId,
            Target = DB.TessellatedShapeBuilderTarget.Mesh,
            Fallback = DB.TessellatedShapeBuilderFallback.Salvage
          }
        )
        {
          var pieces = mesh.DisjointMeshCount > 1 ?
                       mesh.SplitDisjointPieces() :
                       new Mesh[] { mesh };

          foreach (var piece in pieces)
          {
            piece.Faces.ConvertNonPlanarQuadsToTriangles(Revit.VertexTolerance, RhinoMath.UnsetValue, 5);

            var vertices = piece.Vertices.ToPoint3dArray();

            builder.OpenConnectedFaceSet(piece.SolidOrientation() != 0);
            foreach (var face in piece.Faces)
            {
              faceVertices.Add(vertices[face.A].ToHost());
              faceVertices.Add(vertices[face.B].ToHost());
              faceVertices.Add(vertices[face.C].ToHost());
              if (face.IsQuad)
                faceVertices.Add(vertices[face.D].ToHost());

              builder.AddFace(new DB.TessellatedFace(faceVertices, Context.Peek.MaterialId));
              faceVertices.Clear();
            }
            builder.CloseConnectedFaceSet();
          }

          builder.Build();
          using (var result = builder.GetBuildResult())
          {
            if (result.Outcome != DB.TessellatedShapeBuilderOutcome.Nothing)
              return result.GetGeometricalObjects();
          }
        }
      }
      catch (Autodesk.Revit.Exceptions.ApplicationException e)
      {
        Debug.Fail(e.Source, e.Message);
      }

      return Enumerable.Empty<DB.GeometryObject>();
    }

    public static IEnumerable<DB.GeometryObject> ToHostMultiple(this GeometryBase geometry, double scaleFactor)
    {
      switch (geometry)
      {
        case Point point:
          point = point.ChangeUnits(scaleFactor);

          return Enumerable.Repeat(point.ToHost(), 1);
        case PointCloud pointCloud:
          pointCloud = pointCloud.ChangeUnits(scaleFactor);

          return pointCloud.ToHostMultiple();
        case Curve curve:
          curve = curve.ChangeUnits(scaleFactor);

          return curve.ToHostMultiple();
        case Brep brep:
          brep = brep.ChangeUnits(scaleFactor);

          return brep.ToHostMultiple();
        case Mesh mesh:
          mesh = mesh.ChangeUnits(scaleFactor);

          while (mesh.CollapseFacesByEdgeLength(false, Revit.VertexTolerance) > 0) ;

          return mesh.ToHostMultiple();
        case Extrusion extrusion:

          return extrusion.ToBrep().ToHostMultiple(scaleFactor);
        case SubD subD:

          return subD.ToBrep().ToHostMultiple(scaleFactor);
        default:
          return Enumerable.Empty<DB.GeometryObject>();
      }
    }

    public static IEnumerable<IList<DB.GeometryObject>> ToHost(this IEnumerable<GeometryBase> geometries)
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      return geometries.Select(x => x.ToHostMultiple(scaleFactor)).Where(x => x.Any()).Select(x => x.ToList());
    }
    #endregion

    #region ToCurveArray
    public static DB.CurveArray ToCurveArray(this IEnumerable<DB.Curve> curves)
    {
      var curveArray = new DB.CurveArray();
      foreach (var curve in curves)
        curveArray.Append(curve);

      return curveArray;
    }

    public static DB.CurveLoop ToCurveLoop(this IEnumerable<DB.Curve> curves)
    {
      var curveLoop = new DB.CurveLoop();
      foreach (var curve in curves)
        curveLoop.Append(curve);

      return curveLoop;
    }
    #endregion
  };
}
