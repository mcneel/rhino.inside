using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

using Autodesk;
using Autodesk.Revit;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;
using Autodesk.Revit.UI.Events;
using Autodesk.Revit.ApplicationServices;

using Rhino;
using Rhino.Runtime.InProcess;
using Rhino.Geometry;

namespace RhinoInside
{
  [Autodesk.Revit.Attributes.Transaction(Autodesk.Revit.Attributes.TransactionMode.Manual)]
  [Autodesk.Revit.Attributes.Regeneration(Autodesk.Revit.Attributes.RegenerationOption.Manual)]
  [Autodesk.Revit.Attributes.Journaling(Autodesk.Revit.Attributes.JournalingMode.NoCommandData)]
  public class Revit : IExternalApplication
  {
    #region Revit static constructor
    static Revit()
    {
      ResolveEventHandler OnRhinoCommonResolve = null;
      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhinoCommonAssemblyName = "RhinoCommon";
        var assemblyName = new AssemblyName(args.Name).Name;

        if (assemblyName != rhinoCommonAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

        string rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
        return Assembly.LoadFrom(Path.Combine(rhinoSystemDir, rhinoCommonAssemblyName + ".dll"));
      };
    }
    #endregion

    #region IExternalApplication Members

    internal static BitmapImage _rhinoLogo = LoadImage("RhinoInside.Resources.Rhino.png");

    private RhinoCore _rhinoCore;

    public Autodesk.Revit.UI.Result OnStartup(UIControlledApplication applicationUI)
    {
      ApplicationUI = applicationUI;

#if REVIT_2019
      MainWindowHandle = ApplicationUI.MainWindowHandle;
#else
      MainWindowHandle = Process.GetCurrentProcess().MainWindowHandle;
#endif

      // Load Rhino
      try
      {
        var schemeName = ApplicationUI.ControlledApplication.VersionName.Replace(' ', '-');
        _rhinoCore = new RhinoCore(new string[] { $"/scheme={schemeName}", "/nosplash" }, WindowStyle.Normal, MainWindowHandle);
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
        return Autodesk.Revit.UI.Result.Failed;
      }

      // Register UI
      {
        RibbonPanel ribbonPanel = ApplicationUI.CreateRibbonPanel("Rhinoceros");

        Sample1.CreateUI(ribbonPanel);
      }

      // Add an Idling event handler to notify Rhino when the process is idle
      ApplicationUI.Idling += new EventHandler<IdlingEventArgs>(OnIdle);

      return Autodesk.Revit.UI.Result.Succeeded;
    }

    public Autodesk.Revit.UI.Result OnShutdown(UIControlledApplication applicationUI)
    {
      // Remove the Idling event handler
      ApplicationUI.Idling -= new EventHandler<IdlingEventArgs>(OnIdle);

      // Unload Rhino
      try
      {
        _rhinoCore.Dispose();
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
        return Autodesk.Revit.UI.Result.Failed;
      }

      ApplicationUI = null;
      return Autodesk.Revit.UI.Result.Succeeded;
    }

    public void OnIdle(object sender, IdlingEventArgs args)
    {
      // 1. Do Rhino pending OnIdle tasks
      if (_rhinoCore.OnIdle())
      {
        args.SetRaiseWithoutDelay();
        return;
      }

      // Document dependant tasks need a document
      var doc = (sender as UIApplication)?.ActiveUIDocument?.Document;
      if (doc == null)
        return;

      // 2. Do all BakeGeometry pending tasks
      lock (_bakeQueue)
      {
        if (_bakeQueue.Count > 0)
        {
          using (var trans = new Transaction(doc))
          {
            if (trans.Start("BakeGeometry") == TransactionStatus.Started)
            {
              var categoryId = new ElementId(BuiltInCategory.OST_GenericModel);
              while (_bakeQueue.Count > 0)
              {
                var geometryList = _bakeQueue.Dequeue();
                if (geometryList != null)
                {
                  var ds = DirectShape.CreateElement(doc, categoryId);
                  ds.SetShape(geometryList);
                }
              }
            }

            trans.Commit();
          }
        }
      }

      // 3. Do all document actions
      lock (_documentActions)
      {
        if (_documentActions.Count > 0)
        {
          using (var trans = new Transaction(doc))
          {
            var a = _documentActions.Peek();
            var name = a.GetMethodInfo().Name;
            var s = trans.Start(name);
            if (s == TransactionStatus.Started)
            {
              try
              {
                _documentActions.Dequeue().Invoke(doc);
                trans.Commit();
              }
              catch (Exception e)
              {
                Debug.Fail(e.Source, e.Message);
                trans.RollBack();
              }
            }
          }
        }

        if (_documentActions.Count > 0)
          args.SetRaiseWithoutDelay();
      }
    }

    private static Queue<IList<GeometryObject>> _bakeQueue = new Queue<IList<GeometryObject>>();
    public static void BakeGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      lock (_bakeQueue)
      {
        foreach (var list in Convert(geometries))
          _bakeQueue.Enqueue(list);
      }
    }

    private static Queue<Action<Document>> _documentActions = new Queue<Action<Document>>();
    public static void EnqueueAction(Action<Document> action)
    {
      lock (_documentActions)
        _documentActions.Enqueue(action);
    }

    #endregion

    #region Public SDK
    public static IntPtr MainWindowHandle { get; private set; }
    public static UIControlledApplication ApplicationUI { get; private set; }

    public static double RhinoToRevitModelScaleFactor => RhinoDoc.ActiveDoc == null ? Double.NaN : RhinoMath.UnitScale(RhinoDoc.ActiveDoc.ModelUnitSystem, Rhino.UnitSystem.Feet);
    public const double ModelAbsoluteTolerance = (1.0 / 12.0) / 16.0; // 1/16 inch in feets
    internal static double RhinoModelAbsoluteTolerance => ModelAbsoluteTolerance / RhinoToRevitModelScaleFactor; // in Rhino model units

    static private BitmapImage LoadImage(string name)
    {
      var bmi = new BitmapImage();
      bmi.BeginInit();
      bmi.StreamSource = Assembly.GetExecutingAssembly().GetManifestResourceStream(name);
      bmi.EndInit();
      return bmi;
    }

    static internal XYZ Convert(Point3d p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    static internal IList<XYZ> Convert(IList<Point3d> points)
    {
      var xyz = new List<XYZ>(points.Count);
      foreach (var p in points)
        xyz.Add(Convert(p));

      return xyz;
    }

    static internal IList<XYZ> Convert(IEnumerable<ControlPoint> points)
    {
      var xyz = new List<XYZ>();
      foreach (var p in points)
        xyz.Add(Convert(p.Location));

      return xyz;
    }

    static internal IList<double> Convert(Rhino.Geometry.Collections.NurbsCurveKnotList knotList)
    {
      int knotListCount = knotList.Count;
      if(knotListCount > 0)
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

    static internal IList<double> Convert(Rhino.Geometry.Collections.NurbsSurfaceKnotList knotList)
    {
      int knotListCount = knotList.Count;
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

    static internal IEnumerable<GeometryObject> Convert(IEnumerable<Rhino.Geometry.Mesh> meshes)
    {
      List<XYZ> faceVertices = new List<XYZ>(4);

      var builder = new TessellatedShapeBuilder();
      builder.Target = TessellatedShapeBuilderTarget.AnyGeometry;
      builder.Fallback = TessellatedShapeBuilderFallback.Mesh;

      foreach (var mesh in meshes)
      {
        Rhino.Geometry.Mesh[] pieces = mesh.DisjointMeshCount > 1 ?
                                       mesh.SplitDisjointPieces() :
                                       new Rhino.Geometry.Mesh[] { mesh };

        foreach (var piece in pieces)
        {
          // Meshes with edges smaller than AbsoluteRevitTolerance (1/16 inch) are not welcome in Revit
          while (piece.CollapseFacesByEdgeLength(false, ModelAbsoluteTolerance) > 0) ;

          piece.Faces.ConvertNonPlanarQuadsToTriangles(RhinoMath.ZeroTolerance, RhinoMath.UnsetValue, 5);

          bool isOriented = false;
          bool hasBoundary = false;
          bool isSolid = piece.IsClosed && piece.IsManifold(true, out isOriented, out hasBoundary) && isOriented;
          var vertices = piece.Vertices;

          builder.OpenConnectedFaceSet(isSolid);
          foreach (var face in piece.Faces)
          {
            faceVertices.Add(Convert(vertices[face.A]));
            faceVertices.Add(Convert(vertices[face.B]));
            faceVertices.Add(Convert(vertices[face.C]));
            if (face.IsQuad)
              faceVertices.Add(Convert(vertices[face.D]));

            builder.AddFace(new TessellatedFace(faceVertices, ElementId.InvalidElementId));
            faceVertices.Clear();
          }
          builder.CloseConnectedFaceSet();
        }
      }

      try
      {
        builder.Build();
      }
      catch (Autodesk.Revit.Exceptions.ApplicationException e)
      {
        Debug.Fail(e.Source, e.Message);
        return null;
      }

      TessellatedShapeBuilderResult result = builder.GetBuildResult();
      return result.GetGeometricalObjects();
    }

    static internal IEnumerable<Autodesk.Revit.DB.Curve> Convert(Rhino.Geometry.Curve curve)
    {
      var simplifiedCurve = curve.Simplify(CurveSimplifyOptions.SplitAtFullyMultipleKnots, ModelAbsoluteTolerance, Math.PI / 1800.0);
      if (simplifiedCurve != null)
        curve = simplifiedCurve;

      switch (curve)
      {
        case Rhino.Geometry.PolyCurve polyCurve:

          polyCurve.RemoveNesting();
          for (int s = 0; s < polyCurve.SegmentCount; ++s)
          {
            foreach (var segment in Convert(polyCurve.SegmentCurve(s)))
              yield return segment;
          }
          break;

        case Rhino.Geometry.NurbsCurve nurbsCurve:

          nurbsCurve.Knots.RemoveMultipleKnots(1, nurbsCurve.Degree, ModelAbsoluteTolerance);

          var degree = nurbsCurve.Degree;
          var knots = Convert(nurbsCurve.Knots);
          var controlPoints = Convert(nurbsCurve.Points);

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
          break;

        default:
          foreach (var c in Convert(curve.ToNurbsCurve()))
            yield return c;
          break;
      }
    }

    static internal BRepBuilderSurfaceGeometry Convert(Rhino.Geometry.Surface faceSurface)
    {
      switch (faceSurface)
      {
        case Rhino.Geometry.NurbsSurface nurbsSurface:

          var degreeU = nurbsSurface.Degree(0);
          var degreeV = nurbsSurface.Degree(1);
          var knotsU = Convert(nurbsSurface.KnotsU);
          var knotsV = Convert(nurbsSurface.KnotsV);
          var controlPoints = Convert(nurbsSurface.Points);

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
            return null;
          }
      }

      return Convert(faceSurface.ToNurbsSurface());
    }

    static private Rhino.Geometry.Brep SplitClosedFaces(Rhino.Geometry.Brep brep, double tolerance)
    {
      Brep brepToSplit;
      do
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
            brep = face.Split(splitters, tolerance);
            break;
          }
        }
      } while (brepToSplit != brep);

      return brep;
    }

    static internal IEnumerable<GeometryObject> Convert(Rhino.Geometry.Brep brep)
    {
      // Convert everything inside brep to NURBS
      if (false && brep.MakeValidForV2())
      {
        brep = SplitClosedFaces(brep, ModelAbsoluteTolerance);

        foreach (var face in brep.Faces)
        {
          var builder = new BRepBuilder(face.IsSolid ? BRepType.Solid : BRepType.OpenShell);
          //builder.AllowRemovalOfProblematicFaces();
          //builder.SetAllowShortEdges();

          var brepSurface = Convert(face.UnderlyingSurface());
          var brepEdges = new List<BRepBuilderGeometryId>[brep.Edges.Count];

          var faceId = builder.AddFace(brepSurface, face.OrientationIsReversed);
          foreach (var loop in face.Loops)
          {
            var loopId = builder.AddLoop(faceId);
            foreach (var trim in loop.Trims)
            {
              if (trim.TrimType != BrepTrimType.Boundary)
                continue;

              var edge = trim.Edge;
              if (edge == null)
                continue;

              var edgeIds = brepEdges[edge.EdgeIndex];
              if (edgeIds == null)
              {
                edgeIds = brepEdges[edge.EdgeIndex] = new List<BRepBuilderGeometryId>();
                foreach (var c in Convert(edge.EdgeCurve))
                  edgeIds.Add(builder.AddEdge(BRepBuilderEdgeGeometry.Create(c)));
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
          builder.Finish();

          if (!builder.IsResultAvailable())
            continue;

          yield return builder.GetResult();
        }
      }
      else
      {
        // Emergency code
        var mp = MeshingParameters.Default;
        mp.MinimumEdgeLength = ModelAbsoluteTolerance;
        foreach (var m in Convert(Rhino.Geometry.Mesh.CreateFromBrep(brep, mp)))
          yield return m;
      }
    }

    static internal IEnumerable<IList<GeometryObject>> Convert(IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      double scaleFactor = RhinoToRevitModelScaleFactor;
      foreach (var geometry in geometries)
      {
        switch (geometry)
        {
          case Rhino.Geometry.Curve curve:
            curve = curve.DuplicateCurve();

            if (scaleFactor != 1.0)
              curve.Scale(scaleFactor);

            yield return ((IEnumerable<GeometryObject>)Convert(curve)).ToList();
            break;
          case Rhino.Geometry.Brep brep:
            brep = brep.DuplicateBrep();

            if (scaleFactor != 1.0)
              brep.Scale(scaleFactor);

            yield return Convert(brep).ToList();
            break;
          case Rhino.Geometry.Mesh mesh:
            mesh = mesh.DuplicateMesh();

            if (scaleFactor != 1.0)
              mesh.Scale(scaleFactor);

            yield return Convert(new Rhino.Geometry.Mesh[] { mesh }).ToList();
            break;
        }

        yield return null;
      }
    }
    #endregion
  }

}
