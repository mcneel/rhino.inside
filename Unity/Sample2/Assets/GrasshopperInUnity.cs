using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[ExecuteInEditMode]
public class GrasshopperInUnity : MonoBehaviour
{
  static bool _firstRun = true;

  [MenuItem("Grasshopper/Show...")]
  public static void ShowGrasshopperWindow()
  {
    string script = "!_-Grasshopper _W _T ENTER";
    if (_firstRun)
    {
      _firstRun = false;
      RhinoInside.Launch();
      var ghWatcher = new GameObject("Grasshopper Geometry");
      ghWatcher.AddComponent<GrasshopperInUnity>();

    }
    Rhino.RhinoApp.RunScript(script, false);
  }

  public GrasshopperInUnity()
  {
    Rhino.Runtime.HostUtils.RegisterNamedCallback("Unity:FromGrasshopper", FromGrasshopper);
  }

  // This function will be called from a component in Grasshopper
  void FromGrasshopper(object sender, Rhino.Runtime.NamedParametersEventArgs args)
  {
    Rhino.Geometry.GeometryBase[] values;
    if (args.TryGetGeometry("mesh", out values))
      _mesh = values[0] as Rhino.Geometry.Mesh;
    if (_mesh != null)
      gameObject.GetComponent<MeshFilter>().mesh = _mesh.ToHost();
  }

  Rhino.Geometry.Mesh _mesh;

  // Start is called before the first frame update
  void Start()
  {
    gameObject.AddComponent<MeshFilter>();

    gameObject.AddComponent<MeshRenderer>().material = new Material(Shader.Find("Standard"))
    {
      color = new Color(1.0f, 0.0f, 0.0f, 1f)
    };

  }

  // Update is called once per frame
  void Update()
  {
    var pt = Camera.main.gameObject.transform.position.ToRhino();
    using (var args = new Rhino.Runtime.NamedParametersEventArgs())
    {
      args.Set("point", new Rhino.Geometry.Point(pt));
      Rhino.Runtime.HostUtils.ExecuteNamedCallback("ToGrasshopper", args);
    }

  }

}

