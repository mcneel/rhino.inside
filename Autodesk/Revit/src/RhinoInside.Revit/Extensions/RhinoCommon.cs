using System;
using System.Collections.Generic;
using System.Linq;
using Rhino;
using Rhino.Geometry;

namespace RhinoInside.Revit
{
  public static partial class Extension
  {
    #region Scale
    public static Point3d ChangeUnits(this Point3d p, double factor)
    {
      return p * factor;
    }
    public static Vector3d ChangeUnits(this Vector3d p, double factor)
    {
      return p * factor;
    }
    public static Transform ChangeUnits(this Transform t, double factor)
    {
      t.M03 *= factor;
      t.M13 *= factor;
      t.M23 *= factor;
      return t;
    }
    public static Line ChangeUnits(this Line l, double factor)
    {
      return new Line(l.From * factor, l.To * factor);
    }
    public static Plane ChangeUnits(this Plane p, double factor)
    {
      return new Plane(p.Origin * factor, p.XAxis, p.YAxis);
    }
    public static BoundingBox ChangeUnits(this BoundingBox bbox, double factor)
    {
      return new BoundingBox(bbox.Min * factor, bbox.Max * factor);
    }
    public static G ChangeUnits<G>(this G geometry, double factor) where G : GeometryBase
    {
      geometry = (G) geometry?.DuplicateShallow();
      return factor != 1.0 && !geometry.Scale(factor) ? null : geometry;
    }
    #endregion

    #region TryGetExtrusion
    public static bool TryGetExtrusion(this Surface surface, out Extrusion extrusion)
    {
      extrusion = null;
      var nurbsSurface = surface as NurbsSurface ?? surface.ToNurbsSurface();

      for (int direction = 1; direction >= 0; --direction)
      {
        var oposite = direction == 0 ? 1 : 0;

        if (surface.IsClosed(direction))
          continue;

        var domain = nurbsSurface.Domain(direction);
        var iso0 = nurbsSurface.IsoCurve(oposite, domain.Min);
        var iso1 = nurbsSurface.IsoCurve(oposite, domain.Max);

        if (iso0.TryGetPlane(out var plane0) && iso1.TryGetPlane(out var plane1))
        {
          if (plane0.Normal.IsParallelTo(plane1.Normal, RhinoMath.DefaultAngleTolerance / 100.0) == 1)
          {
            var rowCount = direction == 0 ? nurbsSurface.Points.CountU : nurbsSurface.Points.CountV;
            var columnCount = direction == 0 ? nurbsSurface.Points.CountV : nurbsSurface.Points.CountU;
            for (int c = 0; c < columnCount; ++c)
            {
              var point = direction == 0 ? nurbsSurface.Points.GetControlPoint(0, c) : nurbsSurface.Points.GetControlPoint(c, 0);
              for (int r = 1; r < rowCount; ++r)
              {
                var pointR = direction == 0 ? nurbsSurface.Points.GetControlPoint(r, c) : nurbsSurface.Points.GetControlPoint(c, r);
                var projectedPointR = plane0.ClosestPoint(pointR.Location);
                if (projectedPointR.DistanceToSquared(point.Location) > RhinoMath.SqrtEpsilon)
                  return false;

                if (Math.Abs(pointR.Weight - point.Weight) > RhinoMath.ZeroTolerance)
                  return false;
              }
            }

            // Extrusion.Create does not work well when 'iso0' is a line-like curve,
            // plane used to extrude is "arbitrary" in this case
            //extrusion = Extrusion.Create(iso0, zAxis.Length, false);

            var axis = new Line(iso0.PointAtStart, iso1.PointAtStart);
            var zAxis = iso1.PointAtStart - iso0.PointAtStart;
            var xAxis = (iso0.IsClosed ? iso0.PointAt(iso0.Domain.Mid) : iso0.PointAtEnd) - iso0.PointAtStart;
            var yAxis = Vector3d.CrossProduct(zAxis, xAxis);

            extrusion = new Extrusion();
            if (!iso0.Transform(Transform.PlaneToPlane(new Plane(iso0.PointAtStart, xAxis, yAxis), Plane.WorldXY)))
              return false;

            return extrusion.SetPathAndUp(axis.From, axis.To, yAxis) && extrusion.SetOuterProfile(iso0, false);
          }
        }
      }

      return false;
    }

    public static bool TryGetExtrusion(this BrepFace face, out Extrusion extrusion)
    {
      if (face.UnderlyingSurface().TryGetExtrusion(out extrusion))
      {
        if (face.OrientationIsReversed)
        {
          var profile = extrusion.Profile3d(new ComponentIndex(ComponentIndexType.ExtrusionBottomProfile, 0));
          profile.Reverse();

          if (!extrusion.GetProfileTransformation(0.0).TryGetInverse(out var WCStoECS))
            return false;

          if (!profile.Transform(WCStoECS))
            return false;

          return extrusion.SetOuterProfile(profile, false);
        }

        return true;
      }

      extrusion = null;
      return false;
    }

    struct PlanarBrepFace
    {
      public PlanarBrepFace(BrepFace f)
      {
        Face = f;
        Face.TryGetPlane(out Plane);
        loop = null;
        area = double.NaN;
        centroid = new Point3d(double.NaN, double.NaN, double.NaN);
      }

      public readonly BrepFace Face;
      public readonly Plane Plane;
      NurbsCurve loop;
      Point3d centroid;
      double area;

      public NurbsCurve Loop
      {
        get { if (loop is null) loop = Face.OuterLoop.To3dCurve().ToNurbsCurve(); return loop; }
      }
      public Point3d Centroid
      {
        get { if (!centroid.IsValid) using (var mp = AreaMassProperties.Compute(Loop)) { area = mp.Area; centroid = mp.Centroid; } return centroid; }
      }
      public double LoopArea
      {
        get { if (double.IsNaN(area)) using (var mp = AreaMassProperties.Compute(Loop)) { area = mp.Area; centroid = mp.Centroid; } return area; }
      }

      public bool ProjectionDegenartesToCurve(Surface surface)
      {
        // This function basically tests if 'surface' projected to 'plane' degenerate to a curve
        // So it can be used with any kind of surface even BrepFace, trims doesn't matter.
        // But if called with a BrepFace using UnderlyingSurface() may avoid one extra surface conversion
        var nurbsSurface = surface as NurbsSurface ?? surface.ToNurbsSurface();

        var domainU = nurbsSurface.Domain(0);
        var domainV = nurbsSurface.Domain(1);
        var isoU = nurbsSurface.IsoCurve(1, domainU.Min);
        var isoV = nurbsSurface.IsoCurve(0, domainV.Min);

        // To avoid problems with lines we test for perpendicularity instead planar parallelism
        // To avoid problems with closed curves we use the mid point instead of PointAtEnd
        // Self intersected curves are not allowed here, isoU and isoV are edges of a face,
        // so PointAt(Domain.Mid) will not be equal to PointAtStart
        int row = -1;
        if (isoU.IsPlanar() && (isoU.PointAtStart - isoU.PointAt(domainU.Mid)).IsPerpendicularTo(Plane.Normal))
          row = 0;
        else if (isoV.IsPlanar() && (isoV.PointAtStart - isoV.PointAt(domainV.Mid)).IsPerpendicularTo(Plane.Normal))
          row = 1;

        // No Edge parallel to plane
        if (row < 0)
          return false;

        var column = row == 0 ? 1 : 0;

        // Test if projection of all rows of control points projected to 'plane' are coincident.
        // This means 'surface' degenerate to a curve if projected to 'plane', so an "extrusion".
        var rowCount = row == 0 ? nurbsSurface.Points.CountU : nurbsSurface.Points.CountV;
        var columnCount = row == 0 ? nurbsSurface.Points.CountV : nurbsSurface.Points.CountU;
        for (int c = 0; c < columnCount; ++c)
        {
          var point = row == 0 ? nurbsSurface.Points.GetControlPoint(0, c) : nurbsSurface.Points.GetControlPoint(c, 0);
          var projectedPoint = Plane.ClosestPoint(point.Location);
          for (int r = 1; r < rowCount; ++r)
          {
            var pointR = row == 0 ? nurbsSurface.Points.GetControlPoint(r, c) : nurbsSurface.Points.GetControlPoint(c, r);
            var projectedPointR = Plane.ClosestPoint(pointR.Location);

            if (projectedPointR.DistanceToSquared(projectedPoint) > RhinoMath.SqrtEpsilon)
              return false;

            if (Math.Abs(pointR.Weight - point.Weight) > RhinoMath.ZeroTolerance)
              return false;
          }
        }

        return true;
      }
    }

    public static bool TryGetExtrusion(this Brep brep, out Extrusion extrusion)
    {
      if (brep.IsSurface)
        return brep.Faces[0].TryGetExtrusion(out extrusion);

      extrusion = null;
      if (brep.Faces.Count < 3)
        return false;

      // Requiere manifold breps
      if (brep.SolidOrientation == BrepSolidOrientation.None || brep.SolidOrientation == BrepSolidOrientation.Unknown)
        return false;

      // If brep has more that 3 faces we should check if there are faces with interior loops
      if (brep.Faces.Count > 3 && brep.Faces.Where(face => face.Loops.Count != 1).Any())
        return false;

      var candidateFaces = new List<int[]>();

      // Array with just planar faces sorted by its area to search for similar faces
      var planarFaces = brep.Faces.
                        Select(face => new PlanarBrepFace(face)).
                        Where(face => face.Plane.IsValid).
                        OrderByDescending(face => face.LoopArea).
                        ToArray();

      // A capped Extrusion converted to Brep has wall surfaces in face[0] to face[N-3], caps are face[N-2] and face[N-1]
      // I iterate in reverse order to be optimisitc, maybe brep comes from an Extrusion.ToBrep() call
      for (int f = planarFaces.Length - 1; f > 0; --f)
      {
        var planeF = planarFaces[f].Plane;
        var loopF = planarFaces[f].Loop;
        var centroidF = planarFaces[f].Centroid;

        // Check if they have same area.
        for (int g = f - 1; g >= 0 && RhinoMath.EpsilonEquals(planarFaces[f].LoopArea, planarFaces[g].LoopArea, RhinoMath.SqrtEpsilon); --g)
        {
          // Planes should be parallel or anti-parallel
          if (planeF.Normal.IsParallelTo(planarFaces[g].Plane.Normal, RhinoMath.DefaultAngleTolerance / 100.0) == 0)
            continue;

          // Here f, ang are perfect candidates to test adjacent faces for perpendicularity to them,
          // but we may try to quick reject some candidates if it's obvious that doesn't match

          // A "perfect" curve overlap match may be a test but is too much in this ocasion

          // We expect same NURBS structure, so point count should match
          if (loopF.Points.Count != planarFaces[g].Loop.Points.Count)
            continue;

          // Since we have computed the area the centroid comes for free.
          // Centroids should also match
          if (planeF.ClosestPoint(planarFaces[g].Centroid).DistanceToSquared(centroidF) > RhinoMath.SqrtEpsilon)
            continue;

          // Add result to candidates List reversing index order to keep extrusion creation direction
          // Breps that come from a Extrusion have the Cap[0] before Cap[1]
          candidateFaces.Add(new int[] { g, f });
        }
      }

      // No twin faces found
      if (candidateFaces.Count == 0)
        return false;

      // Candidates are in 'LoopArea' order, we will find here smaller profiles sooner
      // This is good for beam like objects, bad for slab like objects.

      // On box-like Breps the result could be ambigous for the user so,
      // to give him some control on the result, we will prioritize first and last faces no matter their area.
      // First and Last are "special" because if somebody observe an extrusion-like Brep and sees
      // it as an extrusion he tends to categorize faces in one of the following schemas:
      // { Cap[0], Wall[0] .. Wall[N], Cap[1] }
      // { Cap[0], Cap[1], Wall[0] .. Wall[N] }
      // { Wall[0] .. Wall[N], Cap[0], Cap[1] }
      // So if he is using the join command to create a Brep from surfaces at the model,
      // it's natural to start or end the selection with one of the extrusion caps.
      // On horizontal extrusions, slab-like Breps, the user use to observe the model from above,
      // so probably he will end with the bottom cap.
      // Also Last face is a Cap in Breps that come from Extrusion
      // If caps and walls are interleaved, smallest pair of faces will be used as caps, producing beam-like extrusions.

      //  System.Linq.Enumerable.OrderBy performs a stable sort so only first and last face will be moved if found.
      foreach (var candidate in candidateFaces.OrderBy(pair => (planarFaces[pair[1]].Face.FaceIndex == brep.Faces.Count - 1) ? 0 : // Last,  in case it comes from Extrusion
                                                               (planarFaces[pair[0]].Face.FaceIndex == 0) ? 1 : // First, in case it comes from a JOIN command
                                                                                                                    int.MaxValue)) // Others
      {
        var startFace = planarFaces[candidate[0]];
        var endFace = planarFaces[candidate[1]];

        // If any face, ignorig twins candidates, does not degenrate
        // to a curve when projected to 'planeF', then brep is not an extrusion
        if
        (
          brep.Faces.
          Where(face => face.FaceIndex != startFace.Face.FaceIndex && face.FaceIndex != endFace.Face.FaceIndex).
          Select(face => startFace.ProjectionDegenartesToCurve(face.UnderlyingSurface())).
          Any(degenerateToCurve => degenerateToCurve == false)
        )
          return false;

        // We use the orginal OuterLoop as profile not the NURBS version of it
        // to keep the structure as much as possible
        var profile = startFace.Face.OuterLoop.To3dCurve();

        double height = startFace.Face.OrientationIsReversed ?
                        -startFace.Plane.DistanceTo(endFace.Plane.Origin) :
                        +startFace.Plane.DistanceTo(endFace.Plane.Origin);

        extrusion = Extrusion.Create(profile, height, true);
        return true;
      }

      return false;
    }
    #endregion

    #region TryGetLine
    public static bool TryGetLine(this Curve curve, out Line line, double tolerance)
    {
      if (curve is LineCurve lineCurve)
      {
        line = lineCurve.Line;
        return true;
      }
      else if (curve.IsLinear(tolerance))
      {
        line = new Line(curve.PointAtStart, curve.PointAtEnd);
        return true;
      }

      line = default(Line);
      return false;
    }
    #endregion

    #region GeometryBase
    public static bool GetUserBoolean(this GeometryBase geometry, string key, out bool value, bool def = default(bool))
    {
      if (geometry.GetUserInteger(key, out var idx))
      {
        value = idx != 0;
        return true;
      }

      value = def;
      return false;
    }

    public static bool GetUserInteger(this GeometryBase geometry, string key, out int value, int def = default(int))
    {
      value = def;
      return geometry.GetUserString(key) is string stringValue && int.TryParse(stringValue, out value);
    }

    public static bool GetUserEnum<E>(this GeometryBase geometry, string key, out E value, E def = default(E)) where E : struct
    {
      value = def;
      return geometry.GetUserString(key) is string stringValue && Enum.TryParse<E>(stringValue, out value);
    }

    public static bool GetUserElementId(this GeometryBase geometry, string key, out Autodesk.Revit.DB.ElementId value) =>
      GetUserElementId(geometry, key, out value, Autodesk.Revit.DB.ElementId.InvalidElementId);
    public static bool GetUserElementId(this GeometryBase geometry, string key, out Autodesk.Revit.DB.ElementId value, Autodesk.Revit.DB.ElementId def)
    {
      if (geometry.GetUserInteger(key, out var idx))
      {
        value = new Autodesk.Revit.DB.ElementId(idx);
        return true;
      }

      value = def;
      return false;
    }
    #endregion
  }
}
