using System;
using System.Collections.Generic;
using System.Linq;
using Rhino.Geometry;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit
{
  public static partial class Convert
  {
    #region ToRhino
    public static System.Drawing.Color ToRhino(this DB.Color c)
    {
      return System.Drawing.Color.FromArgb(c.Red, c.Green, c.Blue);
    }

    static readonly Rhino.Display.DisplayMaterial defaultMaterial = new Rhino.Display.DisplayMaterial(System.Drawing.Color.WhiteSmoke);
    public static Rhino.Display.DisplayMaterial ToRhino(this DB.Material material, Rhino.Display.DisplayMaterial parentMaterial)
    {
      return (material is null) ? parentMaterial ?? defaultMaterial :
        new Rhino.Display.DisplayMaterial()
        {
          Diffuse = material.Color.ToRhino(),
          Transparency = material.Transparency / 100.0,
          Shine = material.Shininess / 128.0
        };
    }

    public static Point3d ToRhino(this DB.XYZ p)
    {
      return new Point3d(p.X, p.Y, p.Z);
    }

    public static IEnumerable<Point3d> ToRhino(this IEnumerable<DB.XYZ> points)
    {
      foreach (var p in points)
        yield return p.ToRhino();
    }

    public static BoundingBox ToRhino(this DB.BoundingBoxXYZ bbox)
    {
      if (bbox?.Enabled ?? false)
      {
        var box = new BoundingBox(bbox.Min.ToRhino(), bbox.Max.ToRhino());
        return bbox.Transform.ToRhino().TransformBoundingBox(box);
      }

      return BoundingBox.Empty;
    }

    public static Transform ToRhino(this DB.Transform transform)
    {
      var value = new Transform
      {
        M00 = transform.BasisX.X,
        M10 = transform.BasisX.Y,
        M20 = transform.BasisX.Z,
        M30 = 0.0,

        M01 = transform.BasisY.X,
        M11 = transform.BasisY.Y,
        M21 = transform.BasisY.Z,
        M31 = 0.0,

        M02 = transform.BasisZ.X,
        M12 = transform.BasisZ.Y,
        M22 = transform.BasisZ.Z,
        M32 = 0.0,

        M03 = transform.Origin.X,
        M13 = transform.Origin.Y,
        M23 = transform.Origin.Z,
        M33 = 1.0
      };

      return value;
    }

    public static Point ToRhino(this DB.Point point)
    {
      return new Point(point.Coord.ToRhino());
    }

    public static Plane ToRhino(this DB.Plane plane)
    {
      return new Plane(plane.Origin.ToRhino(), (Vector3d) plane.XVec.ToRhino(), (Vector3d) plane.YVec.ToRhino());
    }

    public static Curve ToRhino(this DB.Curve curve)
    {
      switch (curve)
      {
        case DB.Line line:
        {
          return line.IsBound ? new LineCurve(line.GetEndPoint(0).ToRhino(), line.GetEndPoint(1).ToRhino()) : null;
        }
        case DB.Arc arc:
        {
          var plane = new Plane(arc.Center.ToRhino(), new Vector3d(arc.XDirection.ToRhino()), new Vector3d(arc.YDirection.ToRhino()));
          if (arc.IsBound)
          {
            var p0 = arc.GetEndPoint(0).ToRhino();
            var p1 = arc.Evaluate(0.5, true).ToRhino();
            var p2 = arc.GetEndPoint(1).ToRhino();
            return new ArcCurve(new Arc(p0, p1, p2));
          }

          return new ArcCurve(new Circle(plane, arc.Radius));
        }
        case DB.Ellipse ellipse:
        {
          var plane = new Plane(ellipse.Center.ToRhino(), new Vector3d(ellipse.XDirection.ToRhino()), new Vector3d(ellipse.YDirection.ToRhino()));
          var e = new Ellipse(plane, ellipse.RadiusX, ellipse.RadiusY);
          var n = e.ToNurbsCurve();
          if (ellipse.IsBound)
            return n.Trim(ellipse.GetEndParameter(0), ellipse.GetEndParameter(1));

          return n;
        }

        case DB.HermiteSpline hermite:
        {
          return DB.NurbSpline.Create(hermite).ToRhino();
        }
        case DB.NurbSpline nurb:
        {
          var controlPoints = nurb.CtrlPoints;
          var n = new NurbsCurve(3, nurb.isRational, nurb.Degree + 1, controlPoints.Count);

          if (nurb.isRational)
          {
            using (var Weights = nurb.Weights)
            {
              var weights = Weights.Cast<double>().ToArray();
              int index = 0;
              foreach (var pt in controlPoints)
              {
                var w = weights[index];
                n.Points.SetPoint(index++, pt.X * w, pt.Y * w, pt.Z * w, w);
              }
            }
          }
          else
          {
            int index = 0;
            foreach (var pt in controlPoints)
              n.Points.SetPoint(index++, pt.X, pt.Y, pt.Z);
          }

          using (var Knots = nurb.Knots)
          {
            int index = 0;
            foreach (var w in Knots.Cast<double>().Skip(1).Take(n.Knots.Count))
              n.Knots[index++] = w;
          }

          return n;
        }
        case DB.CylindricalHelix helix:  // TODO : 
        default:
          return new PolylineCurve(curve.Tessellate().ToRhino());
      }
    }

    public static PolylineCurve ToRhino(this DB.PolyLine polyline)
    {
      return new PolylineCurve(polyline.GetCoordinates().ToRhino());
    }

    public static IEnumerable<Curve> ToRhino(this IEnumerable<DB.CurveLoop> loops)
    {
      foreach (var loop in loops)
      {
        var polycurve = new PolyCurve();

        foreach (var curve in loop)
          polycurve.AppendSegment(curve.ToRhino());

        yield return polycurve;
      }
    }

    public static PlaneSurface ToRhino(this DB.Plane surface, Interval xExtents, Interval yExtents)
    {
      var plane = new Plane(surface.Origin.ToRhino(), (Vector3d) surface.XVec.ToRhino(), (Vector3d) surface.YVec.ToRhino());
      return new PlaneSurface(plane, xExtents, yExtents);
    }

    public static RevSurface ToRhino(this DB.ConicalSurface surface, Interval interval)
    {
      var plane = new Plane(surface.Origin.ToRhino(), (Vector3d) surface.XDir.ToRhino(), (Vector3d) surface.YDir.ToRhino());
      double height = Math.Abs(interval.Min) > Math.Abs(interval.Max) ? interval.Min : interval.Max;
      var cone = new Cone(plane, height, Math.Tan(surface.HalfAngle) * height);

      return cone.ToRevSurface();
    }

    public static RevSurface ToRhino(this DB.CylindricalSurface surface, Interval interval)
    {
      var plane = new Plane(surface.Origin.ToRhino(), (Vector3d) surface.XDir.ToRhino(), (Vector3d) surface.YDir.ToRhino());
      var circle = new Circle(plane, surface.Radius);
      var cylinder = new Cylinder(circle)
      {
        Height1 = interval.Min,
        Height2 = interval.Max
      };

      return cylinder.ToRevSurface();
    }

    public static RevSurface ToRhino(this DB.RevolvedSurface surface, Interval interval)
    {
      var plane = new Plane(surface.Origin.ToRhino(), (Vector3d) surface.XDir.ToRhino(), (Vector3d) surface.YDir.ToRhino());
      var curve = surface.GetProfileCurveInWorldCoordinates().ToRhino();
      var axis = new Line(surface.Origin.ToRhino(), surface.Origin.ToRhino() + (Vector3d) surface.Axis.ToRhino());
      return RevSurface.Create(curve, axis);
    }

    static Brep JoinAndMerge(this ICollection<Brep> brepFaces, double tolerance)
    {
      if (brepFaces.Count == 0)
        return null;

      if (brepFaces.Count == 1)
        return brepFaces.First();

      ICollection<Brep> joinedBreps = Brep.JoinBreps(brepFaces, tolerance);
      if (joinedBreps is null)
        joinedBreps = brepFaces;
      else if (joinedBreps.Count == 1)
        return joinedBreps.First();

      return Brep.MergeBreps(joinedBreps, tolerance);
    }

    static Brep SolidOrMerge(this ICollection<Brep> brepFaces, double tolerance)
    {
      if (brepFaces.Count == 0)
        return null;

      if (brepFaces.Count == 1)
        return brepFaces.First();

      var solidBreps = Brep.CreateSolid(brepFaces, tolerance);
      if ((solidBreps?.Length ?? 0) == 0)
        return JoinAndMerge(brepFaces, tolerance);

      return solidBreps.Length == 1 ? solidBreps[0] : Brep.MergeBreps(solidBreps, tolerance);
    }

    static Brep TrimFaces(this Brep brep, IEnumerable<Curve> loops, DB.Face face)
    {
      var brepFaces = new List<Brep>();

      foreach (var brepFace in brep?.Faces ?? Enumerable.Empty<BrepFace>())
      {
#if REVIT_2018
        brepFace.OrientationIsReversed = !face.OrientationMatchesSurfaceOrientation;
#endif
        var trimmedBrep = brepFace.Split(loops, Revit.VertexTolerance / 10.0);

        if (trimmedBrep is object)
        {
          foreach (var trimmedFace in trimmedBrep.Faces.OrderByDescending(x => x.FaceIndex))
          {
            // Remove holes, faces with only interior edges
            if (!trimmedFace.Loops.SelectMany(loop => loop.Trims).Where(trim => trim.TrimType != BrepTrimType.Singular && trim.Edge.Valence != EdgeAdjacency.Interior).Any())
            {
              trimmedBrep.Faces.RemoveAt(trimmedFace.FaceIndex);
              continue;
            }

            // Remove ears, faces with edges not in the boundary
            foreach (var trim in trimmedFace.Loops.SelectMany(loop => loop.Trims).Where(trim => trim.TrimType != BrepTrimType.Singular && trim.Edge.Valence == EdgeAdjacency.Naked))
            {
              var midPoint = trim.Edge.PointAt(trim.Edge.Domain.Mid);

              var intersectionResult = face.Project(midPoint.ToHost());
              if (intersectionResult is null || !face.IsInside(intersectionResult.UVPoint))
              {
                trimmedBrep.Faces.RemoveAt(trimmedFace.FaceIndex);
                break;
              }
            }
          }

          brepFaces.Add(trimmedBrep);
        }
      }

      return brepFaces.Count == 0 ?
             brep.DuplicateBrep() :
             brepFaces.JoinAndMerge(Revit.VertexTolerance);
    }

    public static Brep ToRhino(this DB.Face face, bool untrimmed = false)
    {
      using (var surface = face.GetSurface())
      {
        Brep brep = null;
        var loops = face.GetEdgesAsCurveLoops().ToRhino().ToArray();

        switch (surface)
        {
          case DB.Plane planeSurface:
          {
            var plane = new Plane(planeSurface.Origin.ToRhino(), (Vector3d) planeSurface.XVec.ToRhino(), (Vector3d) planeSurface.YVec.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Brep.CreateFromSurface(planeSurface.ToRhino(new Interval(bbox.Min.X, bbox.Max.X), new Interval(bbox.Min.Y, bbox.Max.Y)));
            break;
          }
          case DB.ConicalSurface conicalSurface:
          {
            var plane = new Plane(conicalSurface.Origin.ToRhino(), (Vector3d) conicalSurface.XDir.ToRhino(), (Vector3d) conicalSurface.YDir.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Brep.CreateFromRevSurface(conicalSurface.ToRhino(new Interval(bbox.Min.Z, bbox.Max.Z)), false, false);
            break;
          }
          case DB.CylindricalSurface cylindricalSurface:
          {
            var plane = new Plane(cylindricalSurface.Origin.ToRhino(), (Vector3d) cylindricalSurface.XDir.ToRhino(), (Vector3d) cylindricalSurface.YDir.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Brep.CreateFromRevSurface(cylindricalSurface.ToRhino(new Interval(bbox.Min.Z, bbox.Max.Z)), false, false);
            break;
          }
          case DB.RevolvedSurface revolvedSurface:
          {
            var plane = new Plane(revolvedSurface.Origin.ToRhino(), (Vector3d) revolvedSurface.XDir.ToRhino(), (Vector3d) revolvedSurface.YDir.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Brep.CreateFromRevSurface(revolvedSurface.ToRhino(new Interval(bbox.Min.Z, bbox.Max.Z)), false, false);
            break;
          }
          case DB.RuledSurface ruledSurface:
          {
            var curves = new List<Curve>();
            Point3d start = Point3d.Unset, end = Point3d.Unset;

            if (ruledSurface.HasFirstProfilePoint())
              start = ruledSurface.GetFirstProfilePoint().ToRhino();
            else
              curves.Add(ruledSurface.GetFirstProfileCurve().ToRhino());

            if (ruledSurface.HasSecondProfilePoint())
              end = ruledSurface.GetSecondProfilePoint().ToRhino();
            else
              curves.Add(ruledSurface.GetSecondProfileCurve().ToRhino());

            var lofts = Brep.CreateFromLoft(curves, start, end, LoftType.Straight, false);
            if (lofts.Length == 1)
              brep = lofts[0];
            else
              brep = Brep.MergeBreps(lofts, Revit.VertexTolerance);
            break;
          }
          case DB.HermiteSurface hermiteSurface:
          {
            try
            {
              using (var nurbsData = DB.ExportUtils.GetNurbsSurfaceDataForFace(face))
              {
                var degreeU = nurbsData.DegreeU;
                var degreeV = nurbsData.DegreeV;

                var knotsU = nurbsData.GetKnotsU();
                var knotsV = nurbsData.GetKnotsV();

                int controlPointCountU = knotsU.Count - degreeU - 1;
                int controlPointCountV = knotsV.Count - degreeV - 1;

                var nurbsSurface = NurbsSurface.Create(3, nurbsData.IsRational, degreeU + 1, degreeV + 1, controlPointCountU, controlPointCountV);

                var controlPoints = nurbsData.GetControlPoints();
                var weights = nurbsData.GetWeights();

                var points = nurbsSurface.Points;
                for (int u = 0; u < controlPointCountU; u++)
                {
                  int u_offset = u * controlPointCountV;
                  for (int v = 0; v < controlPointCountV; v++)
                  {
                    var pt = controlPoints[u_offset + v];
                    if (nurbsData.IsRational)
                    {
                      double w = weights[u_offset + v];
                      points.SetPoint(u, v, pt.X * w, pt.Y * w, pt.Z * w, w);
                    }
                    else
                    {
                      points.SetPoint(u, v, pt.X, pt.Y, pt.Z);
                    }
                  }
                }

                {
                  var knots = nurbsSurface.KnotsU;
                  int index = 0;
                  foreach (var w in knotsU.Skip(1).Take(knots.Count))
                    knots[index++] = w;
                }

                {
                  var knots = nurbsSurface.KnotsV;
                  int index = 0;
                  foreach (var w in knotsV.Skip(1).Take(knots.Count))
                    knots[index++] = w;
                }

                brep = Brep.CreateFromSurface(nurbsSurface);
              }
            }
            catch (Autodesk.Revit.Exceptions.ArgumentException) { }
            break;
          }
          default: throw new NotImplementedException();
        }

        if (untrimmed)
          return brep;

        try { return brep?.TrimFaces(loops, face); }
        finally { brep?.Dispose(); }
      }
    }

    public static Brep ToRhino(this DB.Solid solid)
    {
      return solid.Faces.
             Cast<DB.Face>().
             Select(x => x.ToRhino()).
             ToArray().
             SolidOrMerge(Revit.VertexTolerance);
    }

    public static Mesh ToRhino(this DB.Mesh mesh)
    {
      var result = new Mesh();

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

    public static IEnumerable<GeometryBase> ToRhino(this IEnumerable<DB.GeometryObject> geometries)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        switch (geometry)
        {
          case DB.GeometryInstance instance:
            var xform = instance.Transform.ToRhino().ChangeUnits(scaleFactor);
            foreach (var g in instance.SymbolGeometry.ToRhino())
            {
              g?.Transform(xform);
              yield return g;
            }
            break;
          case DB.Mesh mesh:
            var m = mesh.ToRhino();

            yield return m?.ChangeUnits(scaleFactor);
            break;
          case DB.Solid solid:
            var s = solid.ToRhino();

            yield return s?.ChangeUnits(scaleFactor);
            break;
          case DB.Curve curve:
            var c = curve.ToRhino();

            yield return c?.ChangeUnits(scaleFactor);
            break;
          case DB.PolyLine polyline:
            var p = new PolylineCurve(polyline.GetCoordinates().ToRhino());

            yield return p?.ChangeUnits(scaleFactor);
            break;
        }
      }
    }
    #endregion
  };
}
