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
using Autodesk.Revit.ApplicationServices;

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

    private RhinoCore rhinoCore;

    static private BitmapImage LoadImage(string name)
    {
      var bmi = new BitmapImage();
      bmi.BeginInit();
      bmi.StreamSource = Assembly.GetExecutingAssembly().GetManifestResourceStream(name);
      bmi.EndInit();
      return bmi;
    }
    internal static BitmapImage rhinoLogo = LoadImage("RhinoInside.Resources.Rhino.png");

    public Autodesk.Revit.UI.Result OnStartup(UIControlledApplication application)
    {
      // Load Rhino
      try
      {
        var schemeName = application.ControlledApplication.VersionName.Replace(' ', '-');
        rhinoCore = new RhinoCore(new string[] { $"/scheme={schemeName}" });
      }
      catch (Exception )
      {
        return Autodesk.Revit.UI.Result.Failed;
      }

      // Add a new ribbon panel
      RibbonPanel ribbonPanel = application.CreateRibbonPanel("Rhinoceros");

      Sample1.CreateUI(ribbonPanel);

      return Autodesk.Revit.UI.Result.Succeeded;
    }

    public Autodesk.Revit.UI.Result OnShutdown(UIControlledApplication application)
    {
      // Unload Rhino
      try
      {
        rhinoCore.Dispose();
      }
      catch (Exception)
      {
        return Autodesk.Revit.UI.Result.Failed;
      }

      return Autodesk.Revit.UI.Result.Succeeded;
    }

    #endregion

    #region Utility methods
    static internal XYZ Convert(Point3d p)
    {
      return new XYZ(p.X, p.Y, p.Z);
    }

    static internal IList<GeometryObject> Convert(Rhino.Geometry.Mesh[] meshes)
    {
      List<XYZ> vertexs = new List<XYZ>(4);

      var builder = new TessellatedShapeBuilder();
      builder.OpenConnectedFaceSet(false);
      foreach (var mesh in meshes)
      {
        var vertices = mesh.Vertices;
        foreach (var face in mesh.Faces)
        {
          var v = new Point3d[] { vertices[face.A], vertices[face.B], vertices[face.C], vertices[face.D] };

          vertexs.Add(Convert(v[0]));
          vertexs.Add(Convert(v[1]));
          vertexs.Add(Convert(v[2]));
          if (face.IsQuad)
            vertexs.Add(Convert(v[3]));

          builder.AddFace(new TessellatedFace(vertexs, ElementId.InvalidElementId));
          vertexs.Clear();
        }
      }
      builder.CloseConnectedFaceSet();
      builder.Target = TessellatedShapeBuilderTarget.AnyGeometry;
      builder.Fallback = TessellatedShapeBuilderFallback.Mesh;
      builder.Build();

      TessellatedShapeBuilderResult result = builder.GetBuildResult();
      return result.GetGeometricalObjects();
    }

    #endregion
  }

}
