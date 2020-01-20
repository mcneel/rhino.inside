using System;
using System.Reflection;

namespace RhinoInside
{
  public class Resolver
  {
    /// <summary>
    /// Set up an assembly resolver to load RhinoCommon and other Rhino
    /// assemblies from where Rhino is installed
    /// </summary>
    public static void Initialize()
    {
      if (System.IntPtr.Size != 8)
        throw new Exception("Only 64 bit applications can use RhinoInside");
      AppDomain.CurrentDomain.AssemblyResolve += ResolveForRhinoAssemblies;
    }

    static string _rhinoSystemDirectory;

    /// <summary>
    /// Directory used by assembly resolver to attempt load core Rhino assemblies. If not manually set,
    /// this will be determined by inspecting the registry
    /// </summary>
    public static string RhinoSystemDirectory
    {
      get
      {
        if(string.IsNullOrWhiteSpace(_rhinoSystemDirectory))
        {
          string baseName = @"SOFTWARE\McNeel\Rhinoceros";
          using (var baseKey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(baseName))
          {
            string[] children = baseKey.GetSubKeyNames();
            Array.Sort(children);
            string versionName = "";
            for(int i=children.Length-1; i>=0; i--)
            {
              // 20 Jan 2020 S. Baer (https://github.com/mcneel/rhino.inside/issues/248)
              // A generic double.TryParse is failing when run under certain locales.
              if (double.TryParse(children[i], System.Globalization.NumberStyles.Any, System.Globalization.CultureInfo.InvariantCulture, out double d))
              {
                versionName = children[i];
                using (var installKey = baseKey.OpenSubKey($"{versionName}\\Install"))
                {
                  string corePath = installKey.GetValue("CoreDllPath") as string;
                  if( System.IO.File.Exists(corePath))
                  {
                    _rhinoSystemDirectory = System.IO.Path.GetDirectoryName(corePath);
                    break;
                  }
                }
              }
            }
          }
        }
        return _rhinoSystemDirectory;
      }
      set
      {
        _rhinoSystemDirectory = value;
      }
    }

    static Assembly ResolveForRhinoAssemblies(object sender, ResolveEventArgs args)
    {
      var assemblyName = new AssemblyName(args.Name).Name;
      string path = System.IO.Path.Combine(RhinoSystemDirectory, assemblyName + ".dll");
      if (System.IO.File.Exists(path))
        return Assembly.LoadFrom(path);

      return null;
    }
  }
}
