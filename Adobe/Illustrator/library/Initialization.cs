using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.IO;

using Rhino.Geometry;
using Rhino.Runtime.InProcess;

namespace RhinoInside.Illustrator
{
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
        Rhino.DocObjects.ObjRef objref;
        Rhino.Input.RhinoGet.GetOneObject("Select curve", false, Rhino.DocObjects.ObjectType.Curve, out objref);
        //Point3d[] points = new Point3d[]
        //{
        //  new Point3d(0,0,0),
        //  new Point3d(100, 0,0),
        //  new Point3d(0,100, 0),
        //  new Point3d(100,100,0)
        //};
        //var crv = Curve.CreateControlPointCurve(points);
        var crv = objref.Curve();
        double[] verts = new double[100 * 2];
        for( int i=0; i<100; i++ )
        {
          double t = (double) i / 100.0;
          var pt = crv.PointAtNormalizedLength(t);
          verts[2*i] = pt.X;
          verts[2*i + 1] = pt.Y;
        }

        UnsafeNativeMethods.RhDrawShape(100, verts);
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
    internal static extern void RhDrawShape(int count, double[] locations);

  }
}
