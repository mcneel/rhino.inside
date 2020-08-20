using System;
using System.IO;
using System.Reflection;

using Rhino.Runtime.InProcess;
using Rhino.Geometry;

namespace HelloWorld
{
  static class Sample
  {
    public static void Run(string[] args)
    {
      try
      {
        using (new RhinoCore(args))
        {
          MeshABrep();
          Console.WriteLine("press any key to exit");
          Console.ReadKey();
        }
      }
      catch (Exception ex)
      {
        Console.Error.WriteLine(ex.Message);
      }
    }

    static void MeshABrep()
    {
      var sphere = new Sphere(Point3d.Origin, 12);
      var brep = sphere.ToBrep();
      var mp = new MeshingParameters(0.5);
      var mesh = Mesh.CreateFromBrep(brep, mp);
      Console.WriteLine($"Mesh with {mesh[0].Vertices.Count} vertices created");
    }

  }

  class Program
  {
    #region Program static constructor
    static readonly string SystemDir = (string) Microsoft.Win32.Registry.GetValue
    (
      @"HKEY_LOCAL_MACHINE\SOFTWARE\McNeel\Rhinoceros\7.0\Install", "Path",
      Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System")
    );

    static Program()
    {
      ResolveEventHandler OnRhinoCommonResolve = null;
      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhinoCommonAssemblyName = "RhinoCommon";
        var assemblyName = new AssemblyName(args.Name).Name;

        if (assemblyName != rhinoCommonAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;
        string rhinocommonPath = Path.Combine(SystemDir, rhinoCommonAssemblyName + ".dll");
#if DEBUG
        // used internally for debugging core rhino code
        if (File.Exists(@"C:\dev\github\mcneel\rhino\src4\bin\Debug\RhinoCommon.dll"))
        {
          rhinocommonPath = @"C:\dev\github\mcneel\rhino\src4\bin\Debug\RhinoCommon.dll";
        }
#endif
        return Assembly.LoadFrom(rhinocommonPath);
      };
    }
    #endregion

    [System.STAThread]
    static void Main(string[] args)
    {
      Sample.Run(args);
    }
  }
}
