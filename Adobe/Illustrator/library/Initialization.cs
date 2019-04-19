using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.IO;

using Rhino.Geometry;
using Rhino.Runtime.InProcess;

namespace RhinoInside.Illustrator
{
  public static class TestCurvePreview
  {
    public static void UpdateCurvePreview(Curve crv)
    {
      Point2d[] verts = new Point2d[100];
      for (int i = 0; i < verts.Length; i++)
      {
        double t = (double) i / 100.0;
        var pt = crv.PointAtNormalizedLength(t);
        verts[i] = new Point2d(pt.X, pt.Y);
      }

      UnsafeNativeMethods.RhDrawShape(100, verts, crv.IsClosed);
    }
  }

  public static class Initialization
  {
    static RhinoLoader _loader;
    static Initialization()
    {
      ResolveEventHandler OnRhinoCommonResolve = null;
      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhino_common_assembly_name = "RhinoCommon";
        var assembly_name = new AssemblyName(args.Name).Name;

        if (assembly_name != rhino_common_assembly_name)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

        var rhino_system_dir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
        return Assembly.LoadFrom(Path.Combine(rhino_system_dir, rhino_common_assembly_name + ".dll"));
      };
    }

    public static int Start(string s)
    {
      bool firstTime = null == _loader;
      if( null == _loader )
      {
        _loader = new RhinoLoader();
        _loader.Bootstrap();
      }

      if( !firstTime)
      {
        Rhino.DocObjects.ObjRef[] objrefs;
        if( Rhino.Input.RhinoGet.GetMultipleObjects("Select curves", false, Rhino.DocObjects.ObjectType.Curve, out objrefs) == Rhino.Commands.Result.Success)
        {
          foreach(var objref in objrefs)
          {
            var crv = objref.Curve();
            Point2d[] verts = new Point2d[100];
            for (int i = 0; i < verts.Length; i++)
            {
              double t = (double) i / 100.0;
              var pt = crv.PointAtNormalizedLength(t);
              verts[i] = new Point2d(pt.X, pt.Y);
            }

            UnsafeNativeMethods.RhDrawShape(100, verts, crv.IsClosed);
          }
        }
      }
      return 1;
    }
  }

  class RhinoLoader
  {
    RhinoCore _rhinoCore;

    public void Bootstrap()
    {
      const string schemeName = "Illustrator";
      IntPtr mainWindowHandle = System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle;
      _rhinoCore = new RhinoCore(new string[] { $"/scheme={schemeName}", "/nosplash" }, WindowStyle.Normal, mainWindowHandle);
    }
  }

  static class UnsafeNativeMethods
  {
    [DllImport("RhinoInside.Illustrator.PlugIn.aip", CallingConvention = CallingConvention.Cdecl)]
    internal static extern void RhDrawShape(int count, Point2d[] locations, [MarshalAs(UnmanagedType.U1)]bool closed);

  }
}
