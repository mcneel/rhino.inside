
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

using Autodesk;
using Autodesk.Revit;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;
using Autodesk.Revit.ApplicationServices;

using Rhino;
using Rhino.Geometry;
using Rhino.Geometry.Collections;

namespace RhinoInside.Revit
{
  public static class Convert
  {
    #region Scale
    static internal Point3d Scale(this Point3d p, double factor)
    {
      return new Point3d(p.X * factor, p.Y * factor, p.Z * factor);
    }
    static internal Rhino.Geometry.Line Scale(this Rhino.Geometry.Line l, double factor)
    {
      return new Rhino.Geometry.Line(l.From.Scale(factor), l.To.Scale(factor));
    }
    #endregion

    #region ToRhino
    static public Point3d ToRhino(this XYZ p)
    {
      return new Point3d(p.X, p.Y, p.Z);
    }

    static IEnumerable<Point3d> ToRhino(this IEnumerable<XYZ> points)
    {
      foreach (var p in points)
        yield return p.ToRhino();
    }

    static internal Rhino.Geometry.Curve ToRhino(this Autodesk.Revit.DB.Curve curve)
    {
      switch (curve)
      {
        case Autodesk.Revit.DB.Line line:
          return line.IsBound ? new Rhino.Geometry.LineCurve(line.GetEndPoint(0).ToRhino(), line.GetEndPoint(1).ToRhino()) : null;

        case Autodesk.Revit.DB.Arc arc:
          var plane = new Rhino.Geometry.Plane(arc.Center.ToRhino(), new Vector3d(arc.XDirection.ToRhino()), new Vector3d(arc.YDirection.ToRhino()));
          var c = new Rhino.Geometry.Circle(plane, arc.Radius);
          if (arc.IsBound)
          {
            var a = new Rhino.Geometry.Arc(c, new Interval(arc.GetEndParameter(0), arc.GetEndParameter(1)));
            return new Rhino.Geometry.ArcCurve(a);
          }
          else
          {
            return new Rhino.Geometry.ArcCurve(c);
          }
      }

      return null;
    }

    static Rhino.Geometry.Mesh ToRhino(this Autodesk.Revit.DB.Solid solid)
    {
      var facesMeshes = new List<Rhino.Geometry.Mesh>(solid.Faces.Size);
      foreach (var face in solid.Faces)
      {
        switch (face)
        {
          case Face meshableFace: facesMeshes.Add(meshableFace.Triangulate().ToRhino()); break;
        }
      }

      if (facesMeshes.Count > 0)
      {
        var mesh = new Rhino.Geometry.Mesh();

        mesh.Append(facesMeshes);
        mesh.Vertices.Align(Revit.VertexTolerance);

        return mesh;
      }

      return null;
    }

    static Rhino.Geometry.Mesh ToRhino(this Autodesk.Revit.DB.Mesh mesh)
    {
      var result = new Rhino.Geometry.Mesh();

      result.Vertices.AddVertices(mesh.Vertices.ToRhino());

      for (int t = 0; t < mesh.NumTriangles; ++t)
      {
        var triangle = mesh.get_Triangle(t);

        var meshFace = new MeshFace
        (
          (int) triangle.get_Index(0),
          (int) triangle.get_Index(1),
          (int) triangle.get_Index(2)
        );

        result.Faces.AddFace(meshFace);
      }

      return result;
    }

    static internal IEnumerable<Rhino.Geometry.GeometryBase> ToRhino(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
            foreach (var g in instance.GetInstanceGeometry().ToRhino())
              yield return g;
            break;
          case Autodesk.Revit.DB.Solid solid:
            var mesh = solid.ToRhino();

            if (scaleFactor != 1.0)
              mesh?.Scale(scaleFactor);

            yield return mesh;
            break;
          case Autodesk.Revit.DB.Curve curve:
            var c = curve.ToRhino();

            if (scaleFactor != 1.0)
              c?.Scale(scaleFactor);

            yield return c;
            break;
        }
      }
    }
    #endregion

    #region ToHost
    static public Color ToHost(this System.Drawing.Color c)
    {
      return new Color(c.R, c.G, c.B);
    }

    static public XYZ ToHost(this Point3d p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    static public XYZ ToHost(this Vector3d p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    static public Autodesk.Revit.DB.Line ToHost(this Rhino.Geometry.Line line)
    {
      return Autodesk.Revit.DB.Line.CreateBound(line.From.ToHost(), line.To.ToHost());
    }

    static public Autodesk.Revit.DB.Plane ToHost(this Rhino.Geometry.Plane plane)
    {
      return Autodesk.Revit.DB.Plane.CreateByOriginAndBasis(plane.Origin.ToHost(), plane.XAxis.ToHost(), plane.YAxis.ToHost());
    }

    static public Autodesk.Revit.DB.Transform ToHost(this Rhino.Geometry.Transform transform)
    {
      var value = Autodesk.Revit.DB.Transform.CreateTranslation(new XYZ(transform.M03, transform.M13, transform.M23));
      value.BasisX = new XYZ(transform.M00, transform.M10, transform.M20);
      value.BasisY = new XYZ(transform.M01, transform.M11, transform.M21);
      value.BasisZ = new XYZ(transform.M02, transform.M12, transform.M22);
      return value;
    }

    static internal IList<XYZ> ToHost(this IList<Point3d> points)
    {
      var xyz = new List<XYZ>(points.Count);
      foreach (var p in points)
        xyz.Add(p.ToHost());

      return xyz;
    }

    static internal IList<XYZ> ToHost(this IList<ControlPoint> points)
    {
      var xyz = new List<XYZ>(points.Count);
      foreach (var p in points)
        xyz.Add(p.Location.ToHost());

      return xyz;
    }

    static internal IList<XYZ> ToHost(this IEnumerable<ControlPoint> points)
    {
      var xyz = new List<XYZ>();
      foreach (var p in points)
        xyz.Add(p.Location.ToHost());

      return xyz;
    }

    static internal IList<double> ToHost(this NurbsCurveKnotList knotList)
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

    static internal IList<double> ToHost(this NurbsSurfaceKnotList knotList)
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

    static internal IEnumerable<Autodesk.Revit.DB.Point> ToHost(this Rhino.Geometry.Point point)
    {
      yield return Autodesk.Revit.DB.Point.Create(ToHost(point.Location));
    }

    static internal IEnumerable<Autodesk.Revit.DB.Point> ToHost(this Rhino.Geometry.PointCloud pointCloud)
    {
      foreach(var p in pointCloud)
        yield return Autodesk.Revit.DB.Point.Create(ToHost(p.Location));
    }

    static internal IEnumerable<Autodesk.Revit.DB.Curve> ToHost(this Rhino.Geometry.Curve curve, double curveTolerance = double.PositiveInfinity)
    {
      var simplifiedCurve = curve.Simplify(CurveSimplifyOptions.SplitAtFullyMultipleKnots, Revit.VertexTolerance, Revit.AngleTolerance);
      if (simplifiedCurve != null)
        curve = simplifiedCurve;

      switch (curve)
      {
        case Rhino.Geometry.LineCurve line:

          yield return Autodesk.Revit.DB.Line.CreateBound(line.PointAtStart.ToHost(), line.PointAtEnd.ToHost());
          break;

        case Rhino.Geometry.PolylineCurve polyline:

          for(int p = 1; p < polyline.PointCount; ++p)
            yield return Autodesk.Revit.DB.Line.CreateBound(polyline.Point(p-1).ToHost(), polyline.Point(p).ToHost());
          break;

        case Rhino.Geometry.ArcCurve arc:

          if (arc.IsClosed)
            yield return Autodesk.Revit.DB.Arc.Create(arc.Arc.Plane.ToHost(), arc.Arc.Radius, 0.0, (2.0 * Math.PI) - 2e-8);
          else
            yield return Autodesk.Revit.DB.Arc.Create(arc.Arc.StartPoint.ToHost(), arc.Arc.EndPoint.ToHost(), arc.Arc.MidPoint.ToHost());
          break;

        case Rhino.Geometry.PolyCurve polyCurve:

          polyCurve.RemoveNesting();
          for (int s = 0; s < polyCurve.SegmentCount; ++s)
          {
            foreach (var segment in polyCurve.SegmentCurve(s).ToHost())
              yield return segment;
          }
          break;

        case Rhino.Geometry.NurbsCurve nurbsCurve:

          if (nurbsCurve.IsLinear(Revit.VertexTolerance))
          {
            yield return Autodesk.Revit.DB.Line.CreateBound(nurbsCurve.PointAtStart.ToHost(), nurbsCurve.PointAtEnd.ToHost());
            yield break;
          }

          Rhino.Geometry.Polyline polylineSegment;
          if (nurbsCurve.TryGetPolyline(out polylineSegment))
          {
            polylineSegment.ReduceSegments(Math.Min(Revit.ShortCurveTolerance, Math.Abs(curveTolerance)));
            foreach (var segment in polylineSegment.GetSegments())
              yield return Autodesk.Revit.DB.Line.CreateBound(segment.From.ToHost(), segment.To.ToHost());

            yield break;
          }

          Rhino.Geometry.Arc arcSegment;
          if (nurbsCurve.TryGetArc(out arcSegment, Revit.VertexTolerance))
          {
            yield return Autodesk.Revit.DB.Arc.Create(arcSegment.StartPoint.ToHost(), arcSegment.EndPoint.ToHost(), arcSegment.MidPoint.ToHost());
            yield break;

          }

          if (nurbsCurve.IsClosed)
          {
            Rhino.Geometry.Circle circle;
            if (nurbsCurve.TryGetCircle(out circle, Revit.VertexTolerance))
            {
              yield return Autodesk.Revit.DB.Arc.Create(circle.Plane.ToHost(), circle.Radius, 0.0, 2.0 * (2.0 * Math.PI) - 2e-8);
              yield break;
            }

            Rhino.Geometry.Ellipse ellipse;
            if (nurbsCurve.TryGetEllipse(out ellipse, Revit.VertexTolerance))
            {
              yield return Autodesk.Revit.DB.Ellipse.CreateCurve(ellipse.Plane.Origin.ToHost(), ellipse.Radius1, ellipse.Radius2, ellipse.Plane.XAxis.ToHost(), ellipse.Plane.YAxis.ToHost(), 0.0, (2.0 * Math.PI) - 2e-8);
              yield break;
            }

            foreach (var segment in nurbsCurve.Split(nurbsCurve.Domain.Mid))
              foreach (var c in segment.ToHost())
                yield return c;
          }
          else
          {
            nurbsCurve.Knots.RemoveMultipleKnots(1, nurbsCurve.Degree, Revit.VertexTolerance);

            var degree = nurbsCurve.Degree;
            var knots = nurbsCurve.Knots.ToHost();
            var controlPoints = nurbsCurve.Points.ToHost();

            Debug.Assert(degree >= 1);
            Debug.Assert(controlPoints.Count > nurbsCurve.Degree);
            Debug.Assert(knots.Count == nurbsCurve.Degree + controlPoints.Count + 1);

            Autodesk.Revit.DB.Curve nurbSpline = null;
            try
            {
              if (nurbsCurve.IsRational)
              {
                var weights = new List<double>(controlPoints.Count);
                foreach (var p in nurbsCurve.Points)
                {
                  Debug.Assert(p.Weight > 0.0);
                  weights.Add(p.Weight);
                }

                Debug.Assert(weights.Count == controlPoints.Count);

                nurbSpline = NurbSpline.CreateCurve(nurbsCurve.Degree, knots, controlPoints, weights);
              }
              else
              {
                nurbSpline = NurbSpline.CreateCurve(nurbsCurve.Degree, knots, controlPoints);
              }
            }
            catch (Autodesk.Revit.Exceptions.ApplicationException e)
            {
              Debug.Fail(e.Source, e.Message);
            }

            yield return nurbSpline;
          }
          break;

        default:
          foreach (var c in ToHost(curve.ToNurbsCurve()))
            yield return c;
          break;
      }
    }

    static private BRepBuilderSurfaceGeometry BuildFaceSurface(Rhino.Geometry.BrepFace faceSurface)
    {
      using (var nurbsSurface = faceSurface.ToNurbsSurface())
      {
        var degreeU = nurbsSurface.Degree(0);
        var degreeV = nurbsSurface.Degree(1);
        var knotsU = nurbsSurface.KnotsU.ToHost();
        var knotsV = nurbsSurface.KnotsV.ToHost();
        var controlPoints = nurbsSurface.Points.ToHost();

        Debug.Assert(degreeU >= 1);
        Debug.Assert(degreeV >= 1);
        Debug.Assert(knotsU.Count >= 2 * (degreeU + 1));
        Debug.Assert(knotsV.Count >= 2 * (degreeV + 1));
        Debug.Assert(controlPoints.Count == (knotsU.Count - degreeU - 1) * (knotsV.Count - degreeV - 1));

        try
        {
          if (nurbsSurface.IsRational)
          {
            var weights = new List<double>(controlPoints.Count);
            foreach (var p in nurbsSurface.Points)
            {
              Debug.Assert(p.Weight > 0.0);
              weights.Add(p.Weight);
            }

            return BRepBuilderSurfaceGeometry.CreateNURBSSurface
            (
              degreeU, degreeV, knotsU, knotsV, controlPoints, weights, false, null
            );
          }
          else
          {
            return BRepBuilderSurfaceGeometry.CreateNURBSSurface
            (
              degreeU, degreeV, knotsU, knotsV, controlPoints, false, null
            );
          }
        }
        catch (Autodesk.Revit.Exceptions.ApplicationException e)
        {
          Debug.Fail(e.Source, e.Message);
        }
      }

      return null;
    }

    static private Rhino.Geometry.Brep SplitClosedFaces(Rhino.Geometry.Brep brep)
    {
      Brep brepToSplit = null;

      while (brepToSplit != brep && brep != null)
      {
        brep.Standardize();
        brepToSplit = brep;
        foreach (var face in brepToSplit.Faces)
        {
          face.ShrinkFace(BrepFace.ShrinkDisableSide.ShrinkAllSides);

          var splittersU = face.IsClosed(0) ? face.TrimAwareIsoCurve(1, face.Domain(0).Mid) : null;
          var splittersV = face.IsClosed(1) ? face.TrimAwareIsoCurve(0, face.Domain(1).Mid) : null;

          var splittersULength = (splittersU?.Length).GetValueOrDefault();
          var splittersVLength = (splittersV?.Length).GetValueOrDefault();
          var splittersLength = splittersULength + splittersVLength;
          if (splittersLength > 0)
          {
            var splitters = new Rhino.Geometry.Curve[splittersLength];
            splittersU?.CopyTo(splitters, 0);
            splittersV?.CopyTo(splitters, splittersULength);
            brep = face.Split(splitters, Revit.ShortCurveTolerance);

            if (brep == null || brep.Faces.Count == brepToSplit.Faces.Count)
              return null;
          }
        }
      }

      return brep;
    }

    static internal IEnumerable<GeometryObject> ToHost(this Rhino.Geometry.Brep brep)
    {
      Solid solid = null;

      // MakeValidForV2 converts everything inside brep to NURBS
      if (brep.MakeValidForV2())
      {
        var splittedBrep = SplitClosedFaces(brep);
        if (splittedBrep != null)
        {
          brep = splittedBrep;

          try
          {
            var builder = new BRepBuilder(brep.IsSolid ? BRepType.Solid : BRepType.OpenShell);
            builder.AllowRemovalOfProblematicFaces();
            builder.SetAllowShortEdges();

            var brepEdges = new List<BRepBuilderGeometryId>[brep.Edges.Count];
            foreach (var face in brep.Faces)
            {
              var brepSurface = BuildFaceSurface(face);

              var faceId = builder.AddFace(brepSurface, face.OrientationIsReversed);
              foreach (var loop in face.Loops)
              {
                var loopId = builder.AddLoop(faceId);
                foreach (var trim in loop.Trims)
                {
                  if (trim.TrimType != BrepTrimType.Boundary && trim.TrimType != BrepTrimType.Mated)
                    continue;

                  var edge = trim.Edge;
                  if (edge == null)
                    continue;

                  var edgeIds = brepEdges[edge.EdgeIndex];
                  if (edgeIds == null)
                  {
                    edgeIds = brepEdges[edge.EdgeIndex] = new List<BRepBuilderGeometryId>();
                    foreach (var e in edge.ToHost(Revit.VertexTolerance))
                      edgeIds.Add(builder.AddEdge(BRepBuilderEdgeGeometry.Create(e)));
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
            builder.Finish();

            if (builder.IsResultAvailable())
              solid = builder.GetResult();
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

      if (solid != null)
      {
        yield return solid;
      }
      else
      {
        // Emergency result as a mesh
        var mp = MeshingParameters.Default;
        mp.MinimumEdgeLength = Revit.VertexTolerance;
        mp.ClosedObjectPostProcess = true;
        mp.JaggedSeams = false;

        var brepMesh = new Rhino.Geometry.Mesh();
        brepMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, mp));

        foreach(var g in brepMesh.ToHost())
          yield return g;
      }
    }

    static internal IEnumerable<GeometryObject> ToHost(this Rhino.Geometry.Mesh mesh)
    {
      var faceVertices = new List<XYZ>(4);

      var builder = new TessellatedShapeBuilder()
      {
        Target = TessellatedShapeBuilderTarget.AnyGeometry,
        Fallback = TessellatedShapeBuilderFallback.Mesh
      };

      var pieces = mesh.DisjointMeshCount > 1 ?
                   mesh.SplitDisjointPieces() :
                   new Rhino.Geometry.Mesh[] { mesh };

      foreach (var piece in pieces)
      {
        piece.Faces.ConvertNonPlanarQuadsToTriangles(Revit.VertexTolerance, RhinoMath.UnsetValue, 5);

        var isSolid = piece.IsClosed && piece.IsManifold(true, out var isOriented, out var hasBoundary) && isOriented;
        var vertices = piece.Vertices.ToPoint3dArray();

        builder.OpenConnectedFaceSet(isSolid);
        foreach (var face in piece.Faces)
        {
          faceVertices.Add(vertices[face.A].ToHost());
          faceVertices.Add(vertices[face.B].ToHost());
          faceVertices.Add(vertices[face.C].ToHost());
          if (face.IsQuad)
            faceVertices.Add(vertices[face.D].ToHost());

          builder.AddFace(new TessellatedFace(faceVertices, ElementId.InvalidElementId));
          faceVertices.Clear();
        }
        builder.CloseConnectedFaceSet();
      }

      IList<GeometryObject> objects = null;
      try
      {
        builder.Build();
        objects = builder.GetBuildResult().GetGeometricalObjects();
      }
      catch (Autodesk.Revit.Exceptions.ApplicationException e)
      {
        Debug.Fail(e.Source, e.Message);
        objects = new List<GeometryObject>();
      }

      return objects;
    }

    static internal IEnumerable<IList<GeometryObject>> ToHost(this IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        switch (geometry)
        {
          case Rhino.Geometry.Point point:
            point = (Rhino.Geometry.Point) point.DuplicateShallow();

            if (scaleFactor != 1.0)
              point.Scale(scaleFactor);

            yield return point.ToHost().Cast<GeometryObject>().ToList();
            break;
          case Rhino.Geometry.PointCloud pointCloud:
            pointCloud = (Rhino.Geometry.PointCloud) pointCloud.DuplicateShallow();

            if (scaleFactor != 1.0)
              pointCloud.Scale(scaleFactor);

            yield return pointCloud.ToHost().Cast<GeometryObject>().ToList();
            break;
          case Rhino.Geometry.Curve curve:
            curve = (Rhino.Geometry.Curve) curve.DuplicateShallow();

            if (scaleFactor != 1.0)
              curve.Scale(scaleFactor);

            yield return curve.ToHost().Cast<GeometryObject>().ToList();
            break;
          case Rhino.Geometry.Brep brep:
            brep = (Rhino.Geometry.Brep) brep.DuplicateShallow();

            if (scaleFactor != 1.0)
              brep.Scale(scaleFactor);

            yield return brep.ToHost().Cast<GeometryObject>().ToList();
            break;
          case Rhino.Geometry.Mesh mesh:
            mesh = (Rhino.Geometry.Mesh) mesh.DuplicateShallow();

            if (scaleFactor != 1.0)
              mesh.Scale(scaleFactor);

            while (mesh.CollapseFacesByEdgeLength(false, Revit.VertexTolerance) > 0) ;

            yield return mesh.ToHost().Cast<GeometryObject>().ToList();
            break;
        }
      }
    }
    #endregion
  };
}
