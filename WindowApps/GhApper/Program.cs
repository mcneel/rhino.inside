using System;
using System.IO;
using System.Reflection;

namespace GhApper
{
  static class Program
  {
    /// <summary> main entry point for the application. </summary>
    [STAThread]
    static void Main()
    {
      AppDomain.CurrentDomain.AssemblyResolve += (sender, args) =>
      {
        string SystemDir = @"C:\Program Files\Rhino WIP\System";
        //string SystemDir = @"C:\dev\github\mcneel\rhino\src4\bin\Debug";

        var assemblyName = new AssemblyName(args.Name).Name;
        if (assemblyName == "RhinoCommon")
        {
          return Assembly.LoadFrom(Path.Combine(SystemDir, "RhinoCommon.dll"));
        }
        if (assemblyName == "Grasshopper")
        {
          string path = SystemDir;
          if (path.EndsWith("System"))
            path = Directory.GetParent(path).FullName;
          path = Path.Combine(path, "Plug-ins", "Grasshopper", "Grasshopper.dll");
          return Assembly.LoadFrom(path);
        }
        return null;
      };

      var app = new GhApp();
      app.Unpack();
      app.Launch();
      for (int i = 0; i < System.Windows.Application.Current.Windows.Count; i++)
      {
        var window = System.Windows.Application.Current.Windows[i];
        if (window.IsVisible)
        {
          window.Closed += (s, e) => app.Shutdown();;
          break;
        }
      }
      System.Windows.Forms.Application.Run();
    }
  }
}
