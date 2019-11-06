using System;
using System.Reflection;
using System.IO;

using UnityEngine;
using UnityEditor;

using Rhino;
using Rhino.Runtime.InProcess;

public class RhinoInside
{
  static System.IDisposable _rhinoCore;
  public static void Launch()
  {
    if( _rhinoCore == null )
    {
      string rhinoSystemDir = (string)Microsoft.Win32.Registry.GetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\McNeel\Rhinoceros\7.0\Install",
        "Path",
        System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System")
        );

      if (!Environment.GetEnvironmentVariable("PATH").Contains(rhinoSystemDir))
      {
        var PATH = Environment.GetEnvironmentVariable("PATH");
        Environment.SetEnvironmentVariable("PATH", PATH + ";" + rhinoSystemDir);
        IntPtr hParent = System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle;
        _rhinoCore = new RhinoCore(new string[] { "/scheme=Unity", "/nosplash" }, WindowStyle.Minimized, hParent);
      }
    }
  }
}
