
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
    #region Enums
    public static StorageType ToStorageType(this ParameterType parameterType)
    {
      switch (parameterType)
      {
        case ParameterType.Invalid:
          return StorageType.None;
        case ParameterType.Text:
        case ParameterType.MultilineText:
          return StorageType.String;
        case ParameterType.YesNo:
        case ParameterType.Integer:
          return StorageType.Integer;
        case ParameterType.Material:
        case ParameterType.FamilyType:
        case ParameterType.Image:
          return StorageType.ElementId;
        case ParameterType.Number:
        default:
          return StorageType.Double;
      }
    }

    public static BuiltInParameter ToBuiltInParameter(this int value)
    {
      switch (value)
      {
        case (int) BuiltInParameter.GENERIC_THICKNESS:          return BuiltInParameter.GENERIC_THICKNESS;
        case (int) BuiltInParameter.GENERIC_WIDTH:              return BuiltInParameter.GENERIC_WIDTH;
        case (int) BuiltInParameter.GENERIC_HEIGHT:             return BuiltInParameter.GENERIC_HEIGHT;
        case (int) BuiltInParameter.GENERIC_DEPTH:              return BuiltInParameter.GENERIC_DEPTH;
        case (int) BuiltInParameter.GENERIC_FINISH:             return BuiltInParameter.GENERIC_FINISH;
        case (int) BuiltInParameter.GENERIC_CONSTRUCTION_TYPE:  return BuiltInParameter.GENERIC_CONSTRUCTION_TYPE;
        case (int) BuiltInParameter.FIRE_RATING:                return BuiltInParameter.FIRE_RATING;
        case (int) BuiltInParameter.ALL_MODEL_COST:             return BuiltInParameter.ALL_MODEL_COST;
        case (int) BuiltInParameter.ALL_MODEL_MARK:             return BuiltInParameter.ALL_MODEL_MARK;
        case (int) BuiltInParameter.ALL_MODEL_FAMILY_NAME:      return BuiltInParameter.ALL_MODEL_FAMILY_NAME;
        case (int) BuiltInParameter.ALL_MODEL_TYPE_NAME:        return BuiltInParameter.ALL_MODEL_TYPE_NAME;
        case (int) BuiltInParameter.ALL_MODEL_TYPE_MARK:        return BuiltInParameter.ALL_MODEL_TYPE_MARK;
      }

      return (BuiltInParameter) value;
    }

    public static BuiltInParameter AsBuiltInParameter(this int value)
    {
      var builtInParameter = ToBuiltInParameter(value);
      return Enum.IsDefined(typeof(BuiltInParameter), builtInParameter) ? builtInParameter : BuiltInParameter.INVALID;
    }
    #endregion

    #region Math
    public static int Clamp(this int v, int lo, int hi)
    {
      return hi < v ? hi : v < lo ? lo : v;
    }

    public static double Clamp(this double v, double lo, double hi)
    {
      return hi < v ? hi : v < lo ? lo : v;
    }
    #endregion

    #region GraphicAttributes
    public sealed class GraphicAttributes : State<GraphicAttributes>
    {
      public ElementId GraphicsStyleId = ElementId.InvalidElementId;
      public ElementId MaterialId = ElementId.InvalidElementId;
      public Rhino.Geometry.MeshingParameters MeshingParameters = null;
      public double TriangulateLevelOfDetail => MeshingParameters != null ? MeshingParameters.RelativeTolerance : double.NaN;
    }
    #endregion

    #region Scale
    static internal Point3d Scale(this Point3d p, double factor)
    {
      return new Point3d(p.X * factor, p.Y * factor, p.Z * factor);
    }
    static internal Vector3d Scale(this Vector3d p, double factor)
    {
      return new Vector3d(p.X * factor, p.Y * factor, p.Z * factor);
    }
    static internal BoundingBox Scale(this BoundingBox bbox, double factor)
    {
      return new BoundingBox(bbox.Min.Scale(factor), bbox.Max.Scale(factor));
    }
    static internal Rhino.Geometry.Line Scale(this Rhino.Geometry.Line l, double factor)
    {
      return new Rhino.Geometry.Line(l.From.Scale(factor), l.To.Scale(factor));
    }
    static internal Rhino.Geometry.Plane Scale(this Rhino.Geometry.Plane p, double factor)
    {
      return new Rhino.Geometry.Plane(p.Origin.Scale(factor), p.XAxis, p.YAxis);
    }
    #endregion

    #region ToRhino
    static public System.Drawing.Color ToRhino(this Color c)
    {
      return System.Drawing.Color.FromArgb((int) c.Red, (int) c.Green, (int) c.Blue);
    }

    static readonly Rhino.Display.DisplayMaterial defaultMaterial = new Rhino.Display.DisplayMaterial(System.Drawing.Color.WhiteSmoke);
    static internal Rhino.Display.DisplayMaterial ToRhino(this Autodesk.Revit.DB.Material material, Rhino.Display.DisplayMaterial parentMaterial)
    {
      return (material == null) ? parentMaterial ?? defaultMaterial :
        new Rhino.Display.DisplayMaterial()
        {
          Diffuse = material.Color.ToRhino(),
          Transparency = material.Transparency / 100.0,
          Shine = material.Shininess / 128.0
        };
    }

    static public Point3d ToRhino(this XYZ p)
    {
      return new Point3d(p.X, p.Y, p.Z);
    }

    static IEnumerable<Point3d> ToRhino(this IEnumerable<XYZ> points)
    {
      foreach (var p in points)
        yield return p.ToRhino();
    }

    static public Rhino.Geometry.BoundingBox ToRhino(this BoundingBoxXYZ bbox)
    {
      if (bbox?.Enabled ?? false)
      {
        var box = new Rhino.Geometry.BoundingBox(bbox.Min.ToRhino(), bbox.Max.ToRhino());
        return bbox.Transform.ToRhino().TransformBoundingBox(box);
      }

      return Rhino.Geometry.BoundingBox.Empty;
    }

    static public Rhino.Geometry.Transform ToRhino(this Autodesk.Revit.DB.Transform transform)
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

    static public Rhino.Geometry.Plane ToRhino(this Autodesk.Revit.DB.Plane plane)
    {
      return new Rhino.Geometry.Plane(plane.Origin.ToRhino(), (Vector3d) plane.XVec.ToRhino(), (Vector3d) plane.YVec.ToRhino());
    }

    static internal Rhino.Geometry.Curve ToRhino(this Autodesk.Revit.DB.Curve curve)
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
          {
            var t0 = Math.IEEERemainder(ellipse.GetEndParameter(0), 2.0 * Math.PI);
            var t1 = Math.IEEERemainder(ellipse.GetEndParameter(1), 2.0 * Math.PI);
            return n.Trim(t0, t1);
          }

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
              var weights = Weights.OfType<double>().ToArray();
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
            foreach (var w in Knots.OfType<double>().Skip(1).Take(n.Knots.Count))
              n.Knots[index++] = w;
          }

          return n;
        }
        case Autodesk.Revit.DB.CylindricalHelix helix:  // TODO : 
        default:
          return new Rhino.Geometry.PolylineCurve(curve.Tessellate().ToRhino());
      }
    }

    static internal IEnumerable<Rhino.Geometry.Curve> ToRhino(this IEnumerable<CurveLoop> loops)
    {
      foreach (var loop in loops)
      {
        var polycurve = new Rhino.Geometry.PolyCurve();

        foreach (var curve in loop)
          polycurve.Append(curve.ToRhino());

        yield return polycurve;
      }
    }

    static internal Rhino.Geometry.Brep[] ToRhino(this Autodesk.Revit.DB.PlanarFace face)
    {
      var loops = face.GetEdgesAsCurveLoops().ToRhino();
      return Rhino.Geometry.Brep.CreatePlanarBreps(loops, Revit.VertexTolerance);
    }

    static Rhino.Geometry.GeometryBase ToRhino(this Autodesk.Revit.DB.Solid solid)
    {
      bool hasNonPlanarFaces = false;

      foreach (var face in solid.Faces)
      {
        if (hasNonPlanarFaces = !(face is PlanarFace))
          break;
      }

      if (hasNonPlanarFaces)
      {
        // Emergency conversion to mesh
        var triangulateLevelOfDetail = GraphicAttributes.Peek.TriangulateLevelOfDetail;
        var facesMeshes = new List<Rhino.Geometry.Mesh>(solid.Faces.Size);
        foreach (var face in solid.Faces.OfType<Face>())
          facesMeshes.Add((double.IsNaN(triangulateLevelOfDetail) ? face.Triangulate() : face.Triangulate(triangulateLevelOfDetail)).ToRhino());

        if (facesMeshes.Count > 0)
        {
          var mesh = new Rhino.Geometry.Mesh();

          mesh.Append(facesMeshes);
          return mesh;
        }

        return null;
      }
      else
      {
        var faces = new List<Rhino.Geometry.Brep>(solid.Faces.Size);
        foreach (var face in solid.Faces)
        {
          switch (face)
          {
            case PlanarFace planarFace:
              faces.AddRange(planarFace.ToRhino());
              break;
          }
        }

        var breps = Rhino.Geometry.Brep.JoinBreps(faces, Revit.VertexTolerance);
        return Rhino.Geometry.Brep.MergeBreps(breps, Revit.VertexTolerance);
      }
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
          case Autodesk.Revit.DB.Mesh mesh:
            var m = mesh.ToRhino();
            m.Faces.ConvertTrianglesToQuads(Revit.AngleTolerance, 0.0);

            if (scaleFactor != 1.0)
              m?.Scale(scaleFactor);

            yield return m;
            break;
          case Autodesk.Revit.DB.Solid solid:
            var s = solid.ToRhino();

            if (scaleFactor != 1.0)
              s?.Scale(scaleFactor);

            yield return s;
            break;
          case Autodesk.Revit.DB.Curve curve:
            var c = curve.ToRhino();

            if (scaleFactor != 1.0)
              c?.Scale(scaleFactor);

            yield return c;
            break;
          case Autodesk.Revit.DB.PolyLine polyline:
            var p = new Rhino.Geometry.PolylineCurve(polyline.GetCoordinates().ToRhino());

            if (scaleFactor != 1.0)
              p?.Scale(scaleFactor);

            yield return p;
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

    static internal IEnumerable<Rhino.Display.DisplayMaterial> GetPreviewMaterials(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries, Rhino.Display.DisplayMaterial defaultMaterial)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        if (geometry.Visibility != Visibility.Visible)
          continue;

        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
            foreach (var g in instance.GetInstanceGeometry().GetPreviewMaterials(instance.GetInstanceGeometry().MaterialElement.ToRhino(defaultMaterial)))
              yield return g;
            break;
          case Autodesk.Revit.DB.Mesh mesh:
            if (mesh.NumTriangles <= 0)
              continue;

            var sm = Revit.ActiveDBDocument.GetElement(mesh.MaterialElementId) as Material;
            yield return sm.ToRhino(defaultMaterial);
            break;
          case Autodesk.Revit.DB.Solid solid:
            if (solid.Faces.IsEmpty)
              continue;

            var solidFaces = solid.Faces.OfType<Face>();
            bool useMultipleMaterials = solidFaces.HasMultipleMaterials();

            foreach (var face in solidFaces)
            {
              var fm = Revit.ActiveDBDocument.GetElement(face.MaterialElementId) as Material;
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
    static internal IEnumerable<Rhino.Geometry.Mesh> GetPreviewMeshes(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        if (geometry.Visibility != Visibility.Visible)
          continue;

        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
            foreach (var g in instance.GetInstanceGeometry().GetPreviewMeshes())
              yield return g;
            break;
          case Autodesk.Revit.DB.Mesh mesh:
            if (mesh.NumTriangles <= 0)
              continue;

            var m = mesh.ToRhino();
            m.Faces.ConvertTrianglesToQuads(Math.PI / 90.0, 0.0);

            if (scaleFactor != 1.0)
              m?.Scale(scaleFactor);

            yield return m;
            break;
          case Autodesk.Revit.DB.Solid solid:
            if (solid.Faces.IsEmpty)
              continue;

            var meshingParameters = GraphicAttributes.Peek.MeshingParameters;
            var solidFaces = solid.Faces.OfType<Face>();
            bool useMultipleMaterials = solidFaces.HasMultipleMaterials();
            var facesMeshes = useMultipleMaterials ? null : new List<Rhino.Geometry.Mesh>(solid.Faces.Size);
            foreach (var face in solidFaces)
            {
              var f = (meshingParameters == null ? face.Triangulate() : face.Triangulate(meshingParameters.RelativeTolerance)).ToRhino();
              //f.Faces.ConvertTrianglesToQuads(Math.PI / 90.0, 0.0);

              if (scaleFactor != 1.0)
                f?.Scale(scaleFactor);

              if (facesMeshes == null)
                yield return f;
              else
                facesMeshes.Add(f);
            }

            if(facesMeshes != null)
            {
              if (facesMeshes.Count > 0)
              {
                var mesh = new Rhino.Geometry.Mesh();

                mesh.Append(facesMeshes);
                yield return mesh;
              }

              yield return null;
            }
            break;
        }
      }
    }
    #endregion

    #region GetPreviewWires
    static internal IEnumerable<Rhino.Geometry.Curve> GetPreviewWires(this IEnumerable<Autodesk.Revit.DB.GeometryObject> geometries)
    {
      var scaleFactor = Revit.ModelUnits;
      foreach (var geometry in geometries)
      {
        var gs = Revit.ActiveDBDocument.GetElement(geometry.GraphicsStyleId) as GraphicsStyle;

        if (geometry.Visibility != Visibility.Visible)
          continue;

        switch (geometry)
        {
          case Autodesk.Revit.DB.GeometryInstance instance:
            foreach (var g in instance.GetInstanceGeometry().GetPreviewWires())
              yield return g;
            break;
          case Autodesk.Revit.DB.Solid solid:
            if (solid.Faces.IsEmpty)
              continue;

            foreach (var edge in solid.Edges.OfType<Edge>())
            {
              var s = edge.AsCurve().ToRhino();

              if (scaleFactor != 1.0)
                s?.Scale(scaleFactor);

              yield return s;
            }
            break;
          case Autodesk.Revit.DB.Curve curve:
            var c = curve.ToRhino();

            if (scaleFactor != 1.0)
              c?.Scale(scaleFactor);

            yield return c;
            break;
          case Autodesk.Revit.DB.PolyLine polyline:
            if (polyline.NumberOfCoordinates <= 0)
              continue;

            var p = new Rhino.Geometry.PolylineCurve(polyline.GetCoordinates().ToRhino());

            if (scaleFactor != 1.0)
              p?.Scale(scaleFactor);

            yield return p;
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

    static public XYZ ToHost(this Point3f p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    static public XYZ ToHost(this Point3d p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    static public XYZ ToHost(this Vector3f p)
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

    static internal Autodesk.Revit.DB.Point ToHost(this Rhino.Geometry.Point point)
    {
      return Autodesk.Revit.DB.Point.Create(ToHost(point.Location));
    }

    static internal IEnumerable<Autodesk.Revit.DB.Point> ToHost(this Rhino.Geometry.PointCloud pointCloud)
    {
      foreach(var p in pointCloud)
        yield return Autodesk.Revit.DB.Point.Create(ToHost(p.Location));
    }

    static internal IEnumerable<Autodesk.Revit.DB.Curve> ToHost(this Rhino.Geometry.Curve curve, double curveTolerance = double.PositiveInfinity)
    {
      curveTolerance = Math.Min(Revit.ShortCurveTolerance, Math.Abs(curveTolerance));
      Debug.Assert(!curve.IsShort(curveTolerance));

      var simplifiedCurve = curve.Simplify(CurveSimplifyOptions.SplitAtFullyMultipleKnots, curveTolerance, Revit.AngleTolerance);
      if (simplifiedCurve != null)
        curve = simplifiedCurve;

      switch (curve)
      {
        case Rhino.Geometry.LineCurve line:

          yield return Autodesk.Revit.DB.Line.CreateBound(line.PointAtStart.ToHost(), line.PointAtEnd.ToHost());
          break;

        case Rhino.Geometry.PolylineCurve polyline:

          for (int p = 1; p < polyline.PointCount; ++p)
            yield return Autodesk.Revit.DB.Line.CreateBound(polyline.Point(p - 1).ToHost(), polyline.Point(p).ToHost());
          break;

        case Rhino.Geometry.ArcCurve arc:

          if (arc.IsClosed)
            yield return Autodesk.Revit.DB.Arc.Create(arc.Arc.Plane.ToHost(), arc.Arc.Radius, 0.0, (2.0 * Math.PI) - 2e-8);
          else
            yield return Autodesk.Revit.DB.Arc.Create(arc.Arc.StartPoint.ToHost(), arc.Arc.EndPoint.ToHost(), arc.Arc.MidPoint.ToHost());
          break;

        case Rhino.Geometry.PolyCurve polyCurve:

          polyCurve.RemoveNesting();
          polyCurve.RemoveShortSegments(curveTolerance);
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

          if (nurbsCurve.TryGetPolyline(out var polylineSegment))
          {
            polylineSegment.ReduceSegments(curveTolerance);
            foreach (var segment in polylineSegment.GetSegments())
              yield return Autodesk.Revit.DB.Line.CreateBound(segment.From.ToHost(), segment.To.ToHost());

            yield break;
          }

          if (nurbsCurve.TryGetArc(out var arcSegment, Revit.VertexTolerance))
          {
            yield return Autodesk.Revit.DB.Arc.Create(arcSegment.StartPoint.ToHost(), arcSegment.EndPoint.ToHost(), arcSegment.MidPoint.ToHost());
            yield break;

          }

          if (nurbsCurve.IsClosed)
          {
            if (nurbsCurve.TryGetCircle(out var circle, Revit.VertexTolerance))
            {
              yield return Autodesk.Revit.DB.Arc.Create(circle.Plane.ToHost(), circle.Radius, 0.0, 2.0 * (2.0 * Math.PI) - 2e-8);
              yield break;
            }

            if (nurbsCurve.TryGetEllipse(out var ellipse, Revit.VertexTolerance))
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
          foreach (var c in curve.ToNurbsCurve().ToHost())
            yield return c;
          break;
      }
    }

    static internal BRepBuilderSurfaceGeometry ToHost(this Rhino.Geometry.BrepFace faceSurface)
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

            if (brep == null)
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

          //RhinoDoc.ActiveDoc.Objects.Add(brep);

          try
          {
            var builder = new BRepBuilder(brep.IsSolid ? BRepType.Solid : BRepType.OpenShell);
            builder.AllowRemovalOfProblematicFaces();
            builder.SetAllowShortEdges();

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
                  if (edge == null)
                    continue;

                  var edgeIds = brepEdges[edge.EdgeIndex];
                  if (edgeIds == null)
                  {
                    edgeIds = brepEdges[edge.EdgeIndex] = new List<BRepBuilderGeometryId>();
                    foreach (var e in edge.ToHost())
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

          builder.AddFace(new TessellatedFace(faceVertices, GraphicAttributes.Peek.MaterialId));
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

            yield return Enumerable.Repeat(point.ToHost(), 1).Cast<GeometryObject>().ToList();
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
