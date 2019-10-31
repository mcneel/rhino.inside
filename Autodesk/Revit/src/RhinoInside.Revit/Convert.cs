using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using Autodesk.Revit.DB;
using Rhino;
using Rhino.Geometry;
using Rhino.Geometry.Collections;

namespace RhinoInside.Revit
{
  public static class Convert
  {
    #region GraphicAttributes
    public sealed class GraphicAttributes : State<GraphicAttributes>
    {
      public ElementId GraphicsStyleId = ElementId.InvalidElementId;
      public ElementId MaterialId = ElementId.InvalidElementId;
      public Rhino.Geometry.MeshingParameters MeshingParameters = null;
      public double TriangulateLevelOfDetail => MeshingParameters?.RelativeTolerance ?? double.NaN;
    }
    #endregion

    #region ToRhino
    public static System.Drawing.Color ToRhino(this Color c)
    {
      return System.Drawing.Color.FromArgb(c.Red, c.Green, c.Blue);
    }

    static readonly Rhino.Display.DisplayMaterial defaultMaterial = new Rhino.Display.DisplayMaterial(System.Drawing.Color.WhiteSmoke);
    public static Rhino.Display.DisplayMaterial ToRhino(this Autodesk.Revit.DB.Material material, Rhino.Display.DisplayMaterial parentMaterial)
    {
      return (material is null) ? parentMaterial ?? defaultMaterial :
        new Rhino.Display.DisplayMaterial()
        {
          Diffuse = material.Color.ToRhino(),
          Transparency = material.Transparency / 100.0,
          Shine = material.Shininess / 128.0
        };
    }

    public static Point3d ToRhino(this XYZ p)
    {
      return new Point3d(p.X, p.Y, p.Z);
    }

    public static IEnumerable<Point3d> ToRhino(this IEnumerable<XYZ> points)
    {
      foreach (var p in points)
        yield return p.ToRhino();
    }

    public static Rhino.Geometry.BoundingBox ToRhino(this BoundingBoxXYZ bbox)
    {
      if (bbox?.Enabled ?? false)
      {
        var box = new Rhino.Geometry.BoundingBox(bbox.Min.ToRhino(), bbox.Max.ToRhino());
        return bbox.Transform.ToRhino().TransformBoundingBox(box);
      }

      return Rhino.Geometry.BoundingBox.Empty;
    }

    public static Rhino.Geometry.Transform ToRhino(this Autodesk.Revit.DB.Transform transform)
    {
      var value = new Rhino.Geometry.Transform
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

    public static Rhino.Geometry.Point ToRhino(this Autodesk.Revit.DB.Point point)
    {
      return new Rhino.Geometry.Point(point.Coord.ToRhino());
    }

    public static Rhino.Geometry.Plane ToRhino(this Autodesk.Revit.DB.Plane plane)
    {
      return new Rhino.Geometry.Plane(plane.Origin.ToRhino(), (Vector3d) plane.XVec.ToRhino(), (Vector3d) plane.YVec.ToRhino());
    }

    public static Rhino.Geometry.Curve ToRhino(this Autodesk.Revit.DB.Curve curve)
    {
      switch (curve)
      {
        case Autodesk.Revit.DB.Line line:
        {
          return line.IsBound ? new Rhino.Geometry.LineCurve(line.GetEndPoint(0).ToRhino(), line.GetEndPoint(1).ToRhino()) : null;
        }
        case Autodesk.Revit.DB.Arc arc:
        {
          var plane = new Rhino.Geometry.Plane(arc.Center.ToRhino(), new Vector3d(arc.XDirection.ToRhino()), new Vector3d(arc.YDirection.ToRhino()));
          if (arc.IsBound)
          {
            var p0 = arc.GetEndPoint(0).ToRhino();
            var p1 = arc.Evaluate(0.5, true).ToRhino();
            var p2 = arc.GetEndPoint(1).ToRhino();
            return new Rhino.Geometry.ArcCurve(new Rhino.Geometry.Arc(p0, p1, p2));
          }
          else
          {
            return new Rhino.Geometry.ArcCurve(new Rhino.Geometry.Circle(plane, arc.Radius));
          }
        }
        case Autodesk.Revit.DB.Ellipse ellipse:
        {
          var plane = new Rhino.Geometry.Plane(ellipse.Center.ToRhino(), new Vector3d(ellipse.XDirection.ToRhino()), new Vector3d(ellipse.YDirection.ToRhino()));
          var e = new Rhino.Geometry.Ellipse(plane, ellipse.RadiusX, ellipse.RadiusY);
          var n = e.ToNurbsCurve();
          if (ellipse.IsBound)
            return n.Trim(ellipse.GetEndParameter(0), ellipse.GetEndParameter(1));

          return n;
        }

        case Autodesk.Revit.DB.HermiteSpline hermite:
        {
          return NurbSpline.Create(hermite).ToRhino();
        }
        case Autodesk.Revit.DB.NurbSpline nurb:
        {
          var controlPoints = nurb.CtrlPoints;
          var n = new Rhino.Geometry.NurbsCurve(3, nurb.isRational, nurb.Degree + 1, controlPoints.Count);

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
        case Autodesk.Revit.DB.CylindricalHelix helix:  // TODO : 
        default:
          return new Rhino.Geometry.PolylineCurve(curve.Tessellate().ToRhino());
      }
    }

    public static Rhino.Geometry.PolylineCurve ToRhino(this Autodesk.Revit.DB.PolyLine polyline)
    {
      return new Rhino.Geometry.PolylineCurve(polyline.GetCoordinates().ToRhino());
    }

    public static IEnumerable<Rhino.Geometry.Curve> ToRhino(this IEnumerable<CurveLoop> loops)
    {
      foreach (var loop in loops)
      {
        var polycurve = new Rhino.Geometry.PolyCurve();

        foreach (var curve in loop)
          polycurve.AppendSegment(curve.ToRhino());

        yield return polycurve;
      }
    }

    public static Rhino.Geometry.PlaneSurface ToRhino(this Autodesk.Revit.DB.Plane surface, Interval xExtents, Interval yExtents)
    {
      var plane = new Rhino.Geometry.Plane(surface.Origin.ToRhino(), (Vector3d) surface.XVec.ToRhino(), (Vector3d) surface.YVec.ToRhino());
      return new Rhino.Geometry.PlaneSurface(plane, xExtents, yExtents);
    }

    public static Rhino.Geometry.RevSurface ToRhino(this Autodesk.Revit.DB.ConicalSurface surface, Interval interval)
    {
      var plane = new Rhino.Geometry.Plane(surface.Origin.ToRhino(), (Vector3d) surface.XDir.ToRhino(), (Vector3d) surface.YDir.ToRhino());
      double height = Math.Abs(interval.Min) > Math.Abs(interval.Max) ? interval.Min : interval.Max;
      var cone = new Rhino.Geometry.Cone(plane, height, Math.Tan(surface.HalfAngle) * height);

      return cone.ToRevSurface();
    }

    public static Rhino.Geometry.RevSurface ToRhino(this Autodesk.Revit.DB.CylindricalSurface surface, Interval interval)
    {
      var plane = new Rhino.Geometry.Plane(surface.Origin.ToRhino(), (Vector3d) surface.XDir.ToRhino(), (Vector3d) surface.YDir.ToRhino());
      var circle = new Rhino.Geometry.Circle(plane, surface.Radius);
      var cylinder = new Rhino.Geometry.Cylinder(circle)
      {
        Height1 = interval.Min,
        Height2 = interval.Max
      };

      return cylinder.ToRevSurface();
    }

    public static Rhino.Geometry.RevSurface ToRhino(this Autodesk.Revit.DB.RevolvedSurface surface, Interval interval)
    {
      var plane = new Rhino.Geometry.Plane(surface.Origin.ToRhino(), (Vector3d) surface.XDir.ToRhino(), (Vector3d) surface.YDir.ToRhino());
      var curve = surface.GetProfileCurveInWorldCoordinates().ToRhino();
      var axis = new Rhino.Geometry.Line(surface.Origin.ToRhino(), surface.Origin.ToRhino() + (Vector3d) surface.Axis.ToRhino());
      return Rhino.Geometry.RevSurface.Create(curve, axis);
    }

    static Rhino.Geometry.Brep JoinAndMerge(this ICollection<Rhino.Geometry.Brep> brepFaces, double tolerance)
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

    static Rhino.Geometry.Brep SolidOrMerge(this ICollection<Rhino.Geometry.Brep> brepFaces, double tolerance)
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

    static Rhino.Geometry.Brep TrimFaces(this Rhino.Geometry.Brep brep, IEnumerable<Rhino.Geometry.Curve> loops, Autodesk.Revit.DB.Face face)
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

    public static Rhino.Geometry.Brep ToRhino(this Autodesk.Revit.DB.Face face, bool untrimmed = false)
    {
      using (var surface = face.GetSurface())
      {
        Rhino.Geometry.Brep brep = null;
        var loops = face.GetEdgesAsCurveLoops().ToRhino().ToArray();

        switch (surface)
        {
          case Autodesk.Revit.DB.Plane planeSurface:
          {
            var plane = new Rhino.Geometry.Plane(planeSurface.Origin.ToRhino(), (Vector3d) planeSurface.XVec.ToRhino(), (Vector3d) planeSurface.YVec.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Brep.CreateFromSurface(planeSurface.ToRhino(new Interval(bbox.Min.X, bbox.Max.X), new Interval(bbox.Min.Y, bbox.Max.Y)));
            break;
          }
          case Autodesk.Revit.DB.ConicalSurface conicalSurface:
          {
            var plane = new Rhino.Geometry.Plane(conicalSurface.Origin.ToRhino(), (Vector3d) conicalSurface.XDir.ToRhino(), (Vector3d) conicalSurface.YDir.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Rhino.Geometry.Brep.CreateFromRevSurface(conicalSurface.ToRhino(new Interval(bbox.Min.Z, bbox.Max.Z)), false, false);
            break;
          }
          case Autodesk.Revit.DB.CylindricalSurface cylindricalSurface:
          {
            var plane = new Rhino.Geometry.Plane(cylindricalSurface.Origin.ToRhino(), (Vector3d) cylindricalSurface.XDir.ToRhino(), (Vector3d) cylindricalSurface.YDir.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Rhino.Geometry.Brep.CreateFromRevSurface(cylindricalSurface.ToRhino(new Interval(bbox.Min.Z, bbox.Max.Z)), false, false);
            break;
          }
          case Autodesk.Revit.DB.RevolvedSurface revolvedSurface:
          {
            var plane = new Rhino.Geometry.Plane(revolvedSurface.Origin.ToRhino(), (Vector3d) revolvedSurface.XDir.ToRhino(), (Vector3d) revolvedSurface.YDir.ToRhino());

            var bbox = BoundingBox.Empty;
            foreach (var loop in loops)
            {
              var edgeBoundingBox = loop.GetBoundingBox(plane);
              bbox = BoundingBox.Union(bbox, edgeBoundingBox);
            }

            brep = Rhino.Geometry.Brep.CreateFromRevSurface(revolvedSurface.ToRhino(new Interval(bbox.Min.Z, bbox.Max.Z)), false, false);
            break;
          }
          case Autodesk.Revit.DB.RuledSurface ruledSurface:
          {
            var curves = new List<Rhino.Geometry.Curve>();
            Rhino.Geometry.Point3d start = Rhino.Geometry.Point3d.Unset, end = Rhino.Geometry.Point3d.Unset;

            if (ruledSurface.HasFirstProfilePoint())
              start = ruledSurface.GetFirstProfilePoint().ToRhino();
            else
              curves.Add(ruledSurface.GetFirstProfileCurve().ToRhino());

            if (ruledSurface.HasSecondProfilePoint())
              end = ruledSurface.GetSecondProfilePoint().ToRhino();
            else
              curves.Add(ruledSurface.GetSecondProfileCurve().ToRhino());

            var lofts = Rhino.Geometry.Brep.CreateFromLoft(curves, start, end, LoftType.Straight, false);
            if (lofts.Length == 1)
              brep = lofts[0];
            else
              brep = Rhino.Geometry.Brep.MergeBreps(lofts, Revit.VertexTolerance);
            break;
          }
          case Autodesk.Revit.DB.HermiteSurface hermiteSurface:
          {
            try
            {
              using (var nurbsData = ExportUtils.GetNurbsSurfaceDataForFace(face))
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

    public static Rhino.Geometry.Brep ToRhino(this Autodesk.Revit.DB.Solid solid)
    {
      return solid.Faces.
             Cast<Face>().
             Select(x => x.ToRhino()).
             ToArray().
             SolidOrMerge(Revit.VertexTolerance);
    }

    public static Rhino.Geometry.Mesh ToRhino(this Autodesk.Revit.DB.Mesh mesh)
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

    public static IEnumerable<Rhino.Geometry.GeometryBase> ToRhino(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
            var xform = instance.Transform.ToRhino().ChangeUnits(scaleFactor);
            foreach (var g in instance.SymbolGeometry.ToRhino())
            {
              g?.Transform(xform);
              yield return g;
            }
            break;
          case Autodesk.Revit.DB.Mesh mesh:
            var m = mesh.ToRhino();

            yield return m?.ChangeUnits(scaleFactor);
            break;
          case Autodesk.Revit.DB.Solid solid:
            var s = solid.ToRhino();

            yield return s?.ChangeUnits(scaleFactor);
            break;
          case Autodesk.Revit.DB.Curve curve:
            var c = curve.ToRhino();

            yield return c?.ChangeUnits(scaleFactor);
            break;
          case Autodesk.Revit.DB.PolyLine polyline:
            var p = new Rhino.Geometry.PolylineCurve(polyline.GetCoordinates().ToRhino());

            yield return p?.ChangeUnits(scaleFactor);
            break;
        }
      }
    }
    #endregion

    #region GetPreviewMaterials
    static bool HasMultipleMaterials(this IEnumerable<Face> faces)
    {
      if (faces.Any())
      {
        var materialId = faces.First()?.MaterialElementId ?? ElementId.InvalidElementId;
        foreach (var face in faces.Skip(1))
        {
          if (face.MaterialElementId != materialId)
            return true;
        }
      }

      return false;
    }

    internal static IEnumerable<Rhino.Display.DisplayMaterial> GetPreviewMaterials(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries, Document doc, Rhino.Display.DisplayMaterial defaultMaterial)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        if (geometry.Visibility != Visibility.Visible)
          continue;

        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
            foreach (var g in instance.GetInstanceGeometry().GetPreviewMaterials(doc, instance.GetInstanceGeometry().MaterialElement.ToRhino(defaultMaterial)))
              yield return g;
            break;
          case Autodesk.Revit.DB.Mesh mesh:
            if (mesh.NumTriangles <= 0)
              continue;

            var sm = doc.GetElement(mesh.MaterialElementId) as Material;
            yield return sm.ToRhino(defaultMaterial);
            break;
          case Autodesk.Revit.DB.Solid solid:
            if (solid.Faces.IsEmpty)
              continue;

            var solidFaces = solid.Faces.OfType<Face>();
            bool useMultipleMaterials = solidFaces.HasMultipleMaterials();

            foreach (var face in solidFaces)
            {
              var fm = doc.GetElement(face.MaterialElementId) as Material;
              yield return fm.ToRhino(defaultMaterial);

              if (!useMultipleMaterials)
                break;
            }
            break;
        }
      }
    }
    #endregion

    #region GetPreviewMeshes
    internal static IEnumerable<Rhino.Geometry.Mesh> GetPreviewMeshes(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        if (geometry.Visibility != Visibility.Visible)
          continue;

        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
          {
            var xform = instance.Transform.ToRhino().ChangeUnits(scaleFactor);
            foreach (var g in instance.SymbolGeometry.GetPreviewMeshes())
            {
              g?.Transform(xform);
              yield return g;
            }
            break;
          }
          case Autodesk.Revit.DB.Mesh mesh:
          {
            if (mesh.NumTriangles <= 0)
              continue;

            var m = mesh.ToRhino();

            yield return m?.ChangeUnits(scaleFactor);
            break;
          }
          case Autodesk.Revit.DB.Face face:
          {
            var meshingParameters = GraphicAttributes.Peek.MeshingParameters;
            var f = (meshingParameters is null ? face.Triangulate() : face.Triangulate(meshingParameters.RelativeTolerance)).ToRhino();

            yield return f?.ChangeUnits(scaleFactor); ;
            break;
          }
          case Autodesk.Revit.DB.Solid solid:
          {
            if (solid.Faces.IsEmpty)
              continue;

            var meshingParameters = GraphicAttributes.Peek.MeshingParameters;
            var solidFaces = solid.Faces.OfType<Face>();
            bool useMultipleMaterials = solidFaces.HasMultipleMaterials();
            var facesMeshes = useMultipleMaterials ? null : new List<Rhino.Geometry.Mesh>(solid.Faces.Size);
            foreach (var face in solidFaces)
            {
              var faceMesh = (meshingParameters is null ? face.Triangulate() : face.Triangulate(meshingParameters.RelativeTolerance));
              var f = faceMesh?.ToRhino().ChangeUnits(scaleFactor);

              if (facesMeshes is null)
                yield return f;
              else if (f is object)
                facesMeshes.Add(f);
            }

            if (facesMeshes is object)
            {
              if (facesMeshes.Count > 0)
              {
                var mesh = new Rhino.Geometry.Mesh();

                mesh.Append(facesMeshes);
                yield return mesh;
              }
              else yield return null;
            }
            break;
          }
        }
      }
    }
    #endregion

    #region GetPreviewWires
    internal static IEnumerable<Rhino.Geometry.Curve> GetPreviewWires(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        if (geometry.Visibility != Visibility.Visible)
          continue;

        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
          {
            var xform = instance.Transform.ToRhino().ChangeUnits(scaleFactor);
            foreach (var g in instance.SymbolGeometry.GetPreviewWires())
            {
              g?.Transform(xform);
              yield return g;
            }
            break;
          }
          case Autodesk.Revit.DB.Solid solid:
          {
            if (solid.Faces.IsEmpty)
              continue;

            foreach (var wire in solid.Edges.Cast<Edge>().Select(x => x.AsCurve()).GetPreviewWires())
              yield return wire;
            break;
          }
          case Autodesk.Revit.DB.Face face:
          {
            foreach (var wire in face.GetEdgesAsCurveLoops().SelectMany(x => x.GetPreviewWires()))
              yield return wire;
            break;
          }
          case Autodesk.Revit.DB.Edge edge:
          {
            var e = edge.AsCurve().ToRhino();
            yield return e?.ChangeUnits(scaleFactor);
            break;
          }
          case Autodesk.Revit.DB.Curve curve:
          {
            var c = curve.ToRhino();
            yield return c?.ChangeUnits(scaleFactor);
            break;
          }
          case Autodesk.Revit.DB.PolyLine polyline:
          {
            if (polyline.NumberOfCoordinates <= 0)
              continue;

            var p = polyline.ToRhino();
            yield return p?.ChangeUnits(scaleFactor);
            break;
          }
        }
      }
    }
    #endregion

    #region ToHost
    public static Color ToHost(this System.Drawing.Color c)
    {
      return new Color(c.R, c.G, c.B);
    }

    public static XYZ ToHost(this Point3f p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    public static XYZ ToHost(this Point3d p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    public static XYZ ToHost(this Vector3f p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    public static XYZ ToHost(this Vector3d p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    public static Autodesk.Revit.DB.Line ToHost(this Rhino.Geometry.Line line)
    {
      return Autodesk.Revit.DB.Line.CreateBound(line.From.ToHost(), line.To.ToHost());
    }

    public static IEnumerable<Autodesk.Revit.DB.Line> ToHostMultiple(this Rhino.Geometry.Polyline polyline)
    {
      polyline.ReduceSegments(Revit.ShortCurveTolerance);

      foreach (var segment in polyline.GetSegments())
        yield return Autodesk.Revit.DB.Line.CreateBound(segment.From.ToHost(), segment.To.ToHost());
    }

    public static Autodesk.Revit.DB.Arc ToHost(this Rhino.Geometry.Arc arc)
    {
      if (arc.IsCircle)
        return Autodesk.Revit.DB.Arc.Create(arc.Plane.ToHost(), arc.Radius, 0.0, 2.0 * Math.PI);
      else
        return Autodesk.Revit.DB.Arc.Create(arc.StartPoint.ToHost(), arc.EndPoint.ToHost(), arc.MidPoint.ToHost());
    }

    public static Autodesk.Revit.DB.Arc ToHost(this Rhino.Geometry.Circle circle)
    {
      return Autodesk.Revit.DB.Arc.Create(circle.Plane.ToHost(), circle.Radius, 0.0, 2.0 * Math.PI);
    }

    public static Autodesk.Revit.DB.Curve ToHost(this Rhino.Geometry.Ellipse ellipse) => ellipse.ToHost(new Interval(0.0, 2.0 * Math.PI * 2.0));
    public static Autodesk.Revit.DB.Curve ToHost(this Rhino.Geometry.Ellipse ellipse, Interval interval)
    {
#if REVIT_2018
      return Autodesk.Revit.DB.Ellipse.CreateCurve(ellipse.Plane.Origin.ToHost(), ellipse.Radius1, ellipse.Radius2, ellipse.Plane.XAxis.ToHost(), ellipse.Plane.YAxis.ToHost(), interval.Min, interval.Max);
#else
      return Autodesk.Revit.DB.Ellipse.Create(ellipse.Plane.Origin.ToHost(), ellipse.Radius1, ellipse.Radius2, ellipse.Plane.XAxis.ToHost(), ellipse.Plane.YAxis.ToHost(), interval.Min, interval.Max);
#endif
    }

    public static Autodesk.Revit.DB.Plane ToHost(this Rhino.Geometry.Plane plane)
    {
      return Autodesk.Revit.DB.Plane.CreateByOriginAndBasis(plane.Origin.ToHost(), plane.XAxis.ToHost(), plane.YAxis.ToHost());
    }

    public static Autodesk.Revit.DB.Transform ToHost(this Rhino.Geometry.Transform transform)
    {
      Debug.Assert(transform.IsAffine);

      var value = Autodesk.Revit.DB.Transform.CreateTranslation(new XYZ(transform.M03, transform.M13, transform.M23));
      value.BasisX = new XYZ(transform.M00, transform.M10, transform.M20);
      value.BasisY = new XYZ(transform.M01, transform.M11, transform.M21);
      value.BasisZ = new XYZ(transform.M02, transform.M12, transform.M22);
      return value;
    }

    public static IEnumerable<XYZ> ToHost(this IEnumerable<Point3d> points)
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

    public static Autodesk.Revit.DB.Point ToHost(this Rhino.Geometry.Point point)
    {
      return Autodesk.Revit.DB.Point.Create(ToHost(point.Location));
    }

    public static IEnumerable<Autodesk.Revit.DB.Point> ToHostMultiple(this Rhino.Geometry.PointCloud pointCloud)
    {
      foreach(var p in pointCloud)
        yield return Autodesk.Revit.DB.Point.Create(ToHost(p.Location));
    }

    public static Autodesk.Revit.DB.Line ToHost(this Rhino.Geometry.LineCurve curve)
    {
      return curve.Line.ToHost();
    }

    public static Autodesk.Revit.DB.Arc ToHost(this Rhino.Geometry.ArcCurve curve)
    {
      return curve.Arc.ToHost();
    }

    public static Autodesk.Revit.DB.Curve ToHost(this Rhino.Geometry.NurbsCurve curve)
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
        return NurbSpline.CreateCurve(curve.Degree, knots, controlPoints, weights);
      }

      return NurbSpline.CreateCurve(curve.Degree, knots, controlPoints);
    }

    public static Autodesk.Revit.DB.Curve ToHost(this Rhino.Geometry.Curve curve)
    {
      switch (curve)
      {
        case Rhino.Geometry.LineCurve line:

          return line.Line.ToHost();

        case Rhino.Geometry.ArcCurve arc:

          return arc.Arc.ToHost();

        case Rhino.Geometry.PolylineCurve polyline:

          curve = curve.Simplify
          (
            CurveSimplifyOptions.RebuildLines |
            CurveSimplifyOptions.Merge,
            Revit.VertexTolerance,
            Revit.AngleTolerance
          )
          ?? curve;

          return curve.ToNurbsCurve().ToHost();

        case Rhino.Geometry.PolyCurve polyCurve:

          curve = curve.Simplify
          (
            CurveSimplifyOptions.AdjustG1 |
            CurveSimplifyOptions.Merge,
            Revit.VertexTolerance,
            Revit.AngleTolerance
          )
          ?? curve;

          return curve is Rhino.Geometry.PolyCurve ? curve.ToNurbsCurve().ToHost() : curve.ToHost();

        case Rhino.Geometry.NurbsCurve nurbsCurve:

          if (curve.TryGetEllipse(out var ellipse, out var interval, Revit.VertexTolerance) && ellipse.Radius1 <= 30000 && ellipse.Radius2 <= 30000)
            return ellipse.ToHost(interval);

          return nurbsCurve.ToHost();

        default:
          return curve.ToNurbsCurve().ToHost();
      }
    }

    public static IEnumerable<Autodesk.Revit.DB.Curve> ToHostMultiple(this Rhino.Geometry.Curve curve)
    {
      switch (curve)
      {
        case Rhino.Geometry.LineCurve line:

          yield return line.Line.ToHost();
          yield break;

        case Rhino.Geometry.PolylineCurve polyline:

          for (int p = 1; p < polyline.PointCount; ++p)
            yield return Autodesk.Revit.DB.Line.CreateBound(polyline.Point(p - 1).ToHost(), polyline.Point(p).ToHost());
          yield break;

        case Rhino.Geometry.ArcCurve arc:

          yield return arc.Arc.ToHost();
          yield break;

        case Rhino.Geometry.PolyCurve polyCurve:

          polyCurve.RemoveNesting();
          polyCurve.RemoveShortSegments(Revit.ShortCurveTolerance);
          for (int s = 0; s < polyCurve.SegmentCount; ++s)
          {
            foreach (var segment in polyCurve.SegmentCurve(s).ToHostMultiple())
              yield return segment;
          }
          yield break;

        case Rhino.Geometry.NurbsCurve nurbsCurve:

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

            Autodesk.Revit.DB.Curve nurbSpline = null;

            if (nurbsCurve.IsRational)
            {
              var weights = nurbsCurve.Points.Select(p => p.Weight).ToArray();
              nurbSpline = NurbSpline.CreateCurve(nurbsCurve.Degree, knots, controlPoints, weights);
            }
            else
            {
              nurbSpline = NurbSpline.CreateCurve(nurbsCurve.Degree, knots, controlPoints);
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

    public static IEnumerable<BRepBuilderEdgeGeometry> ToHostMultiple(this Rhino.Geometry.BrepEdge edge)
    {
      var curve = default(Autodesk.Revit.DB.Curve);
      switch (edge.EdgeCurve)
      {
        case Rhino.Geometry.LineCurve line:   curve = line.Line.ToHost(); break;
        case Rhino.Geometry.ArcCurve arc:     curve = arc.Arc.ToHost();   break;
        case Rhino.Geometry.NurbsCurve nurbs: curve = nurbs.ToHost();     break;
        default: throw new NotImplementedException("Unsuported curve type for Autodesk.Revit.DB.BRepBuilderEdgeGeometry");
      }

      if (edge.ProxyCurveIsReversed)
        curve = curve.CreateReversed();

      return curve.ToBoundedCurves().Select(x => BRepBuilderEdgeGeometry.Create(x));
    }

    static BRepBuilderSurfaceGeometry ToHost(this Rhino.Geometry.BrepFace faceSurface)
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
    }

    static Rhino.Geometry.Brep SplitClosedFaces(Rhino.Geometry.Brep brep)
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

          var splitters = new List<Rhino.Geometry.Curve>();

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

    public static Autodesk.Revit.DB.Solid ToHost(this Rhino.Geometry.Brep brep)
    {
      Solid solid = null;

      // MakeValidForV2 converts everything inside brep to NURBS
      if (brep.MakeValidForV2())
      {
        var splittedBrep = SplitClosedFaces(brep);
        if (splittedBrep is object)
        {
          brep = splittedBrep;

          var brepBuilderOutcome = BRepBuilderOutcome.Failure;

          try
          {
            var brepType = BRepType.OpenShell;
            switch (brep.SolidOrientation)
            {
              case BrepSolidOrientation.Inward: brepType = BRepType.Void; break;
              case BrepSolidOrientation.Outward:brepType = BRepType.Solid; break;
            }

            var builder = new BRepBuilder(brepType);
#if REVIT_2018
            builder.AllowRemovalOfProblematicFaces();
            builder.SetAllowShortEdges();
#endif

            var brepEdges = new List<BRepBuilderGeometryId>[brep.Edges.Count];
            foreach (var face in brep.Faces)
            {
              var faceId = builder.AddFace(face.ToHost(), face.OrientationIsReversed);
              builder.SetFaceMaterialId(faceId, GraphicAttributes.Peek.MaterialId);

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
                    edgeIds = brepEdges[edge.EdgeIndex] = new List<BRepBuilderGeometryId>();
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

    static IEnumerable<GeometryObject> ToHostMultiple(this Rhino.Geometry.Brep brep)
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

        var brepMesh = new Rhino.Geometry.Mesh();
        brepMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, mp));

        foreach(var g in brepMesh.ToHostMultiple())
          yield return g;
      }
    }

    public static IEnumerable<GeometryObject> ToHostMultiple(this Rhino.Geometry.Mesh mesh)
    {
      var faceVertices = new List<XYZ>(4);

      try
      {
        using
        (
          var builder = new TessellatedShapeBuilder()
          {
            Target = TessellatedShapeBuilderTarget.Mesh,
            Fallback = TessellatedShapeBuilderFallback.Salvage
          }
        )
        {
          var pieces = mesh.DisjointMeshCount > 1 ?
                       mesh.SplitDisjointPieces() :
                       new Rhino.Geometry.Mesh[] { mesh };

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

              builder.AddFace(new TessellatedFace(faceVertices, GraphicAttributes.Peek.MaterialId));
              faceVertices.Clear();
            }
            builder.CloseConnectedFaceSet();
          }

          builder.Build();
          using (var result = builder.GetBuildResult())
          {
            if (result.Outcome != TessellatedShapeBuilderOutcome.Nothing)
              return result.GetGeometricalObjects();
          }
        }
      }
      catch (Autodesk.Revit.Exceptions.ApplicationException e)
      {
        Debug.Fail(e.Source, e.Message);
      }

      return Enumerable.Empty<GeometryObject>();
    }

    public static IEnumerable<GeometryObject> ToHostMultiple(this Rhino.Geometry.GeometryBase geometry, double scaleFactor)
    {
      switch (geometry)
      {
        case Rhino.Geometry.Point point:
          point = (Rhino.Geometry.Point) point.ChangeUnits(scaleFactor);

          return Enumerable.Repeat(point.ToHost(), 1);
        case Rhino.Geometry.PointCloud pointCloud:
          pointCloud = (Rhino.Geometry.PointCloud) pointCloud.ChangeUnits(scaleFactor);

          return pointCloud.ToHostMultiple();
        case Rhino.Geometry.Curve curve:
          curve = (Rhino.Geometry.Curve) curve.ChangeUnits(scaleFactor);

          return curve.ToHostMultiple();
        case Rhino.Geometry.Brep brep:
          brep = (Rhino.Geometry.Brep) brep.ChangeUnits(scaleFactor);

          return brep.ToHostMultiple();
        case Rhino.Geometry.Mesh mesh:
          mesh = (Rhino.Geometry.Mesh) mesh.ChangeUnits(scaleFactor);

          while (mesh.CollapseFacesByEdgeLength(false, Revit.VertexTolerance) > 0) ;

          return mesh.ToHostMultiple();
        case Rhino.Geometry.Extrusion extrusion:

          return extrusion.ToBrep().ToHostMultiple(scaleFactor);
        case Rhino.Geometry.SubD subD:

          return subD.ToBrep().ToHostMultiple(scaleFactor);
        default:
          return Enumerable.Empty<GeometryObject>();
      }
    }

    public static IEnumerable<IList<GeometryObject>> ToHost(this IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      return geometries.Select(x => x.ToHostMultiple(scaleFactor)).Where(x => x.Any()).Select(x => x.ToList());
    }
    #endregion

    #region ToDirectShapeGeometry
    public static IEnumerable<GeometryObject> ToDirectShapeGeometry(this GeometryObject geometry)
    {
      switch (geometry)
      {
        case Autodesk.Revit.DB.Point p:            yield return p; yield break;
        case Autodesk.Revit.DB.Curve c:
          foreach (var unbounded in ToBoundedCurves(c))
            yield return unbounded;
          yield break;
        case Autodesk.Revit.DB.Solid s:            yield return s; yield break;
        case Autodesk.Revit.DB.Mesh m:             yield return m; yield break;
        case Autodesk.Revit.DB.GeometryInstance i: yield return i; yield break;
        default: throw new ArgumentException("DirectShape only supports Point, Curve, Solid, Mesh and GeometryInstance.");
      }
    }

    public static IEnumerable<Autodesk.Revit.DB.Curve> ToBoundedCurves(this Autodesk.Revit.DB.Curve curve)
    {
      switch (curve)
      {
        case Autodesk.Revit.DB.Arc arc:
          if (!arc.IsBound)
          {
            yield return Autodesk.Revit.DB.Arc.Create(arc.Center, arc.Radius, 0.0, Math.PI, arc.XDirection, arc.YDirection);
            yield return Autodesk.Revit.DB.Arc.Create(arc.Center, arc.Radius, Math.PI, Math.PI * 2.0, arc.XDirection, arc.YDirection);
          }
          else yield return arc;
          yield break;
        case Autodesk.Revit.DB.Ellipse ellipse:
          if (!ellipse.IsBound)
          {
#if REVIT_2018
            yield return Autodesk.Revit.DB.Ellipse.CreateCurve(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, 0.0, Math.PI);
            yield return Autodesk.Revit.DB.Ellipse.CreateCurve(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, Math.PI, Math.PI * 2.0);
#else
            yield return Autodesk.Revit.DB.Ellipse.Create(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, 0.0, Math.PI);
            yield return Autodesk.Revit.DB.Ellipse.Create(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, Math.PI, Math.PI * 2.0);
#endif
          }
          else yield return ellipse;
          yield break;
        case Autodesk.Revit.DB.Curve c: yield return c; yield break;
      }
    }
    #endregion

    #region ToCurveArray
    public static Autodesk.Revit.DB.CurveArray ToCurveArray(this IEnumerable<Autodesk.Revit.DB.Curve> curves)
    {
      var curveArray = new CurveArray();
      foreach (var curve in curves)
        curveArray.Append(curve);

      return curveArray;
    }

    public static Autodesk.Revit.DB.CurveLoop ToCurveLoop(this IEnumerable<Autodesk.Revit.DB.Curve> curves)
    {
      var curveLoop = new CurveLoop();
      foreach (var curve in curves)
        curveLoop.Append(curve);

      return curveLoop;
    }
    #endregion
  };
}
