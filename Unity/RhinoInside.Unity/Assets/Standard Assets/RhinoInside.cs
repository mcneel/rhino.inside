using System;
using System.Reflection;
using System.IO;

using UnityEngine;
using UnityEditor;

using Rhino.Runtime.InProcess;

[InitializeOnLoad]
public class RhinoInside : MonoBehaviour
{
  public static string RhinoSystemDir => Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
  public static bool IsLoaded
  {
    get { return Environment.GetEnvironmentVariable("RHINO_SYSTEM_DIR") != null; }
    set { Environment.SetEnvironmentVariable("RHINO_SYSTEM_DIR", value ? RhinoSystemDir : null); }
  }

  static RhinoInside()
  {
    var PATH = Environment.GetEnvironmentVariable("PATH");
    Environment.SetEnvironmentVariable("PATH", PATH + RhinoSystemDir + ";");

    ResolveEventHandler OnRhinoCommonResolve = null;
    AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
    {
      const string rhinoCommonAssemblyName = "RhinoCommon";
      var assemblyName = new AssemblyName(args.Name).Name;

      if (assemblyName != rhinoCommonAssemblyName)
        return null;

      AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;
      return Assembly.LoadFrom(Path.Combine(RhinoSystemDir, rhinoCommonAssemblyName + ".dll"));
    };
  }
}

[ExecuteInEditMode]
public class RhinoInsideBehaviour : MonoBehaviour
{
  void Awake()
  {
    if (!RhinoInside.IsLoaded)
    {
      GC.SuppressFinalize(new RhinoCore(new string[] { "/scheme=Unity", "/nosplash" }, WindowStyle.Minimized));
      RhinoInside.IsLoaded = true;
    }
  }
}
