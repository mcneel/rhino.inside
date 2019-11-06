using Bricscad.ApplicationServices;
using System;
using System.IO;
using System.Reflection;
using Teigha.Runtime;

// This line is not mandatory, but improves loading performances
[assembly: ExtensionApplication(typeof(RhinoInside.BricsCAD.PlugIn))]

namespace RhinoInside.BricsCAD
{
  public class PlugIn : IExtensionApplication
  {
    private Rhino.Runtime.InProcess.RhinoCore m_rhino_core;

    #region Plugin static constructor

    static readonly string SystemDir = (string) Microsoft.Win32.Registry.GetValue
    (
      @"HKEY_LOCAL_MACHINE\SOFTWARE\McNeel\Rhinoceros\7.0\Install", "Path",
      Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System")
    );

    static PlugIn()
    {
      // Add an assembly resolver for RhinoCommon.dll
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

    public void Initialize()
    {
      // Load Rhino
      try
      {
        var scheme_name = string.Format("Inside-BricsCAD-{0}", Application.Version).Replace(' ', '-');
        m_rhino_core = new Rhino.Runtime.InProcess.RhinoCore(new[] { $"/scheme={scheme_name}" });
      }
      catch
      {
        // ignored
      }

      var version = Assembly.GetExecutingAssembly().GetName().Version.ToString();
      var editor = Application.DocumentManager.MdiActiveDocument.Editor;
      editor.WriteMessage($"\nRhinoInside {version}");
    }

    public void Terminate()
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
