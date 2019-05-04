using System;

using UnityEngine;
using UnityEditor;

using Rhino;
using Rhino.PlugIns;

namespace RhinoInside.Unity.UI
{
  [InitializeOnLoad]
  public static class Menu
  {
    static readonly Guid GrasshopperGuid = new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF);

    [MenuItem("Window/Grasshopper")]
    public static void ToggleGrasshopperWindow()
    {
      PlugIn.LoadPlugIn(GrasshopperGuid);

      RhinoApp.RunScript("!_-Grasshopper _W _T ENTER", false);
    }
  }
}
