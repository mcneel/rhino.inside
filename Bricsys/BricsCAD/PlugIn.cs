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

    static PlugIn()
    {
      // Add an assembly resolver for RhinoCommon.dll
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

    #endregion // Plugin static constructor

    #region IExtensionApplication Members

    public void Initialize()
    {
      // Load Rhino
      try
      {
        var scheme_name = string.Format("BricsCAD.{0}", Application.Version);
        m_rhino_core = new Rhino.Runtime.InProcess.RhinoCore(new[] { $"/scheme={scheme_name}" });
      }
      catch
      {
        // ignored
      }
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
