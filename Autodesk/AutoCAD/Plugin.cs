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

    static Plugin()
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

    #endregion // Plugin static constructor

    #region IExtensionApplication Members

    void IExtensionApplication.Initialize()
    {
      // Load Rhino
      try
      {
        var scheme_name = ProductName().Replace(' ', '_');
        m_rhino_core = new Rhino.Runtime.InProcess.RhinoCore(new[] { $"/scheme={scheme_name}" });
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

    #region Static Functions

    private static string ProductName()
    {
      var root_key = HostApplicationServices.Current.MachineRegistryProductRootKey;
      string product_name = null;
      using (var key = Registry.LocalMachine.OpenSubKey(root_key, false))
      {
        product_name = key.GetValue("ProductName") as string;
      }
      return product_name;
    }

    #endregion // Static Functions
  }
}
