using System;
using System.Runtime.InteropServices;

using UnityEngine;
using UnityEditor;

using Rhino;
using Rhino.PlugIns;

namespace RhinoInside.Unity.UI
{
  [InitializeOnLoad]
  public static class Menu
  {
    [DllImport("USER32", SetLastError = true)]
    static extern IntPtr BringWindowToTop(IntPtr hWnd);

    [DllImport("USER32", SetLastError = true)]
    static extern int ShowWindow(IntPtr hWnd, int nCmdShow);

    [MenuItem("Window/Rhino")]
    public static void ShowRhinoWindow()
    {
      ShowWindow(RhinoApp.MainWindowHandle(), 1);
      BringWindowToTop(RhinoApp.MainWindowHandle());
    }
  }
}
