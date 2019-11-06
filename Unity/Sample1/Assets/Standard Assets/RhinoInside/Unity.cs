using System;
using System.Reflection;
using System.IO;

using UnityEngine;
using UnityEditor;

using Rhino;
using Rhino.Runtime.InProcess;
using Microsoft.Win32;

namespace RhinoInside.Unity
{
  [InitializeOnLoad]
  static class Startup
  {
    static readonly string RhinoSystemDir = Registry.GetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\McNeel\Rhinoceros\7.0\Install", "Path", null) as string ?? string.Empty;

    static bool isLoaded = !string.IsNullOrEmpty(RhinoSystemDir) && Environment.GetEnvironmentVariable("PATH").Contains(RhinoSystemDir);

    static Startup()
    {
      if (!isLoaded)
      {
        if (string.IsNullOrEmpty(RhinoSystemDir))
        {
          if (EditorUtility.DisplayDialog("Rhino.Inside", "Unable to found Rhino 7 WIP installed on this computer.\n\nDo you want to download it now?", "Yes", "No"))
            Application.OpenURL("https://www.rhino3d.com/download/rhino/wip");
        }
        else
        {
          var PATH = Environment.GetEnvironmentVariable("PATH");
          Environment.SetEnvironmentVariable("PATH", PATH + ";" + RhinoSystemDir);
          GC.SuppressFinalize
          (
            new RhinoCore
            (
              new string[]
              {
                "/nosplash",
                "/notemplate",
                "/scheme=Inside-Unity"
              },
              WindowStyle.Hidden
            )
          );

          isLoaded = true;
        }
      }
    }
  }

  public class Unity
  {
    #region Public Properties
    public static IntPtr MainWindowHandle => System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle;
    public static UnityEngine.SceneManagement.Scene ActiveScene => UnityEngine.SceneManagement.SceneManager.GetActiveScene();

    private const double AbsoluteTolerance = UnityEngine.Vector3.kEpsilon;
    public const Rhino.UnitSystem ModelUnitSystem = Rhino.UnitSystem.Meters; // Always meter
    public static double ModelUnits => RhinoDoc.ActiveDoc == null ? double.NaN : RhinoMath.UnitScale(ModelUnitSystem, RhinoDoc.ActiveDoc.ModelUnitSystem); // 1 m. in Rhino units
    #endregion

    static readonly Rhino.Geometry.Transform ToRhinoModel = Rhino.Geometry.Transform.ChangeBasis
    (
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.YAxis, Rhino.Geometry.Vector3d.ZAxis,
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.ZAxis, Rhino.Geometry.Vector3d.YAxis
    );

    static readonly Rhino.Geometry.Transform FromRhinoModel = Rhino.Geometry.Transform.ChangeBasis
    (
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.ZAxis, Rhino.Geometry.Vector3d.YAxis,
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.YAxis, Rhino.Geometry.Vector3d.ZAxis
    );
  }
}
