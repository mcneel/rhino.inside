using System;
using System.Reflection;
using System.IO;

using UnityEngine;
using UnityEditor;

using Rhino;
using Rhino.Runtime.InProcess;


namespace RhinoInside.Unity
{
  [InitializeOnLoad]
  static class Startup
  {
    private static string rhinoSystempDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino 7 WIP", "System");
    private static bool isLoaded = Environment.GetEnvironmentVariable("PATH").Contains(rhinoSystempDir);

    static Startup()
    {
      if (!isLoaded)
      {
        Environment.SetEnvironmentVariable("PATH", Environment.GetEnvironmentVariable("PATH") + ";" + rhinoSystempDir);
        GC.SuppressFinalize(new RhinoCore(new string[] {"/scheme=Unity", "/nosplash"}, WindowStyle.Minimized));
        isLoaded = true;
      }
    }
  }


  public class Unity
  {
    #region Public Properties

    public static IntPtr MainWindowHandle => System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle;
    public static UnityEngine.SceneManagement.Scene ActiveScene => UnityEngine.SceneManagement.SceneManager.GetActiveScene();

    internal const double AbsoluteTolerance = UnityEngine.Vector3.kEpsilon;
    public const Rhino.UnitSystem ModelUnitSystem = Rhino.UnitSystem.Meters; // Always meter
    public static double ModelUnits => RhinoDoc.ActiveDoc == null ? double.NaN : RhinoMath.UnitScale(ModelUnitSystem, RhinoDoc.ActiveDoc.ModelUnitSystem); // 1 m. in Rhino units

    #endregion


    internal static readonly Rhino.Geometry.Transform ToRhinoModel = Rhino.Geometry.Transform.ChangeBasis
    (
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.YAxis, Rhino.Geometry.Vector3d.ZAxis,
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.ZAxis, Rhino.Geometry.Vector3d.YAxis
    );


    internal static readonly Rhino.Geometry.Transform FromRhinoModel = Rhino.Geometry.Transform.ChangeBasis
    (
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.ZAxis, Rhino.Geometry.Vector3d.YAxis,
      Rhino.Geometry.Vector3d.XAxis, Rhino.Geometry.Vector3d.YAxis, Rhino.Geometry.Vector3d.ZAxis
    );
  }
}
