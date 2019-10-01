using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Runtime;
using System;
using System.IO;
using System.Reflection;

// This line is not mandatory, but improves loading performances
[assembly: ExtensionApplication(typeof(RhinoInside.AutoCAD.Plugin))]

namespace RhinoInside.AutoCAD
{
  // This class is instantiated by AutoCAD once and kept alive for the 
  // duration of the session. If you don't do any one time initialization 
  // then you should remove this class.
  public class Plugin : IExtensionApplication
  {
    private Rhino.Runtime.InProcess.RhinoCore m_rhino_core;

    #region Plugin static constructor
    static readonly string SystemDir = (string) Microsoft.Win32.Registry.GetValue
    (
      @"HKEY_LOCAL_MACHINE\SOFTWARE\McNeel\Rhinoceros\7.0\Install", "Path",
      Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System")
    );

    static Plugin()
    {
      ResolveEventHandler OnRhinoCommonResolve = null;
      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhinoCommonAssemblyName = "RhinoCommon";
        var assembly_name = new AssemblyName(args.Name).Name;

        if (assembly_name != rhinoCommonAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;
        return Assembly.LoadFrom(Path.Combine(SystemDir, rhinoCommonAssemblyName + ".dll"));
      };
    }
    #endregion // Plugin static constructor

    #region IExtensionApplication Members

    void IExtensionApplication.Initialize()
    {
      // Load Rhino
      try
      {
        string SchemeName = $"Inside-{HostApplicationServices.Current.Product}-{HostApplicationServices.Current.releaseMarketVersion}";
        m_rhino_core = new Rhino.Runtime.InProcess.RhinoCore(new[] { $"/scheme={SchemeName}" });
      }
      catch
      {
        // ignored
      }

    }

    void IExtensionApplication.Terminate()
    {
      try
      {
        m_rhino_core?.Dispose();
      }
      catch
      {
        // ignored
      }
    }

    #endregion // IExtensionApplication Members
  }
}
