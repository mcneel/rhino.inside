using System;
using System.Collections.Generic;
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
      catch (Exception)
      {
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
      catch (Exception)
      {
        return Autodesk.Revit.UI.Result.Failed;
      }

      ApplicationUI = null;
      return Autodesk.Revit.UI.Result.Succeeded;
    }

    public void OnIdle(object sender, IdlingEventArgs e)
    {
      if (_rhinoCore.OnIdle())
        e.SetRaiseWithoutDelay();

      lock (_bakeQueue)
      {
        var uiApp = sender as UIApplication;
        var doc = uiApp?.ActiveUIDocument?.Document;

        if (_bakeQueue.Count > 0 && doc != null)
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
    }

    private static Queue<IList<GeometryObject>> _bakeQueue = new Queue<IList<GeometryObject>>();
    public static void BakeGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      lock(_bakeQueue)
      {
        foreach (var list in Convert(geometries))
          _bakeQueue.Enqueue(list);
      }
    }

    #endregion

    #region Public SDK
    public static IntPtr MainWindowHandle { get; private set; }
    public static UIControlledApplication ApplicationUI { get; private set; }

    public static double RhinoToRevitModelScaleFactor => RhinoDoc.ActiveDoc == null ? Double.NaN : RhinoMath.UnitScale(RhinoDoc.ActiveDoc.ModelUnitSystem, Rhino.UnitSystem.Feet);
    public const double AbsoluteRevitTolerance = (1.0 / 12.0) / 16.0; // 1/16 inch in feets
    public static double AbsoluteTolerance => AbsoluteRevitTolerance / RhinoToRevitModelScaleFactor; // in Rhino model units

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

    static internal IList<GeometryObject> Convert(IEnumerable<Rhino.Geometry.Mesh> meshes)
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
          if(RhinoToRevitModelScaleFactor != 1.0)
            piece.Scale(RhinoToRevitModelScaleFactor);

          // Meshes with edges smaller than AbsoluteRevitTolerance (1/16 inch) are not welcome in Revit
          while (piece.CollapseFacesByEdgeLength(false, AbsoluteRevitTolerance) > 0) ;

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
      catch(Autodesk.Revit.Exceptions.InternalException)
      {
        return null;
      }

      TessellatedShapeBuilderResult result = builder.GetBuildResult();
      return result.GetGeometricalObjects();
    }

    static internal IEnumerable<IList<GeometryObject>> Convert(IEnumerable<Rhino.Geometry.Brep> breps)
    {
      // TODO: Use Autodesk.Revit.DB.BRepBuilder meanwile we mesh the BREP

      var mp = MeshingParameters.Default;
      mp.MinimumEdgeLength = AbsoluteTolerance;

      foreach (var brep in breps)
        yield return Convert(Rhino.Geometry.Mesh.CreateFromBrep(brep, mp));
    }

    static internal IEnumerable<IList<GeometryObject>> Convert(IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      var mp = MeshingParameters.Default;
      mp.MinimumEdgeLength = AbsoluteTolerance;

      foreach (var geometry in geometries)
      {
        switch (geometry)
        {
          case Rhino.Geometry.Brep brep:
            yield return Convert(Rhino.Geometry.Mesh.CreateFromBrep(brep, mp));
            break;
          case Rhino.Geometry.Mesh mesh:
            yield return Convert(new Rhino.Geometry.Mesh[] { mesh.DuplicateMesh() });
            break;
        }

        yield return null;
      }
    }
    #endregion
  }

}
