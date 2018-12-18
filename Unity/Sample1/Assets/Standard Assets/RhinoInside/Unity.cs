using System;
using System.Reflection;
using System.IO;

using UnityEngine;
using UnityEditor;

using Rhino.Runtime.InProcess;

namespace RhinoInside.Unity
{
  [InitializeOnLoad]
  public class Unity
  {
    static string RhinoSystemDir => Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
    internal static bool IsLoaded
    {
      get { return Environment.GetEnvironmentVariable("RHINO_SYSTEM_DIR") != null; }
      set { Environment.SetEnvironmentVariable("RHINO_SYSTEM_DIR", value ? RhinoSystemDir : null); }
    }

    static Unity()
    {
      if (!IsLoaded)
      {
        var PATH = Environment.GetEnvironmentVariable("PATH");
        Environment.SetEnvironmentVariable("PATH", PATH + RhinoSystemDir + ";");
        GC.SuppressFinalize(new RhinoCore(new string[] { "/scheme=Unity", "/nosplash" }, WindowStyle.Minimized));

        IsLoaded = true;
      }
    }

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
