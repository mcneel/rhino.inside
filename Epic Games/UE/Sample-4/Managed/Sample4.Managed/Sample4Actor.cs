using System;
using System.Collections.Generic;
using Rhino.Runtime;
using Rhino.Runtime.InProcess;
using UnrealEngine.Engine;
using UnrealEngine.Runtime;

namespace Sample4
{
  [UClass, BlueprintType, Blueprintable]
  class ASample4Actor : AActor
  {
    static RhinoCore rhinoCore;
    static Rhino.Geometry.Mesh mesh;

    static ASample4Actor()
    {
      RhinoInside.Resolver.Initialize();
    }

    /// <summary>
    /// Launch Rhino.
    /// </summary>
    [UFunction, BlueprintCallable]
    public void LaunchRhino()
    {
      if (rhinoCore == null)
      {
        rhinoCore = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.Normal);
        Rhino.Runtime.HostUtils.RegisterNamedCallback("MeshFromGrasshopper", FromGrasshopper);
      }
    }

    [UFunction, BlueprintCallable]
    public void LaunchGH()
    {
      string script = "!_-Grasshopper _W _T ENTER";
      if (rhinoCore != null)
        Rhino.RhinoApp.RunScript(script, false);

    }



    // This function will be called from a component in Grasshopper
    void FromGrasshopper(object sender, Rhino.Runtime.NamedParametersEventArgs args)
    {
      Rhino.Geometry.GeometryBase[] values;
      if (args.TryGetGeometry("mesh", out values))
      {
        mesh = values[0] as Rhino.Geometry.Mesh;
        mesh.Faces.ConvertQuadsToTriangles();
        mesh.Flip(true, true, true);
      }
    }


    /// <summary>
    /// Build a list of vertices from the static mesh.
    /// </summary>
    /// <returns></returns>
    [UFunction, BlueprintCallable]
    public List<FVector> GetVertices()
    {
      if (mesh == null) return null;
      var list = new List<FVector>();
      foreach (var vert in mesh.Vertices)
        list.Add(new FVector(vert.X, vert.Y, vert.Z));
      return list;
    }

    /// <summary>
    /// Build a list of face ids from the static mesh.
    /// </summary>
    /// <returns></returns>
    [UFunction, BlueprintCallable]
    public List<int> GetFaceIds()
    {
      if (mesh == null) return null;
      var list = new List<int>();
      foreach (var face in mesh.Faces)
      {
        list.Add(face.A);
        list.Add(face.B);
        list.Add(face.C);
      }
      return list;
    }

    [UFunction, BlueprintCallable]
    public void CameraToGH(FVector vector)
    {
      var pt = vector.ToRhino();
      using (var args = new Rhino.Runtime.NamedParametersEventArgs())
      {
        args.Set("point", new Rhino.Geometry.Point(pt));
        Rhino.Runtime.HostUtils.ExecuteNamedCallback("ToGrasshopper", args);
      }
    }

  }
}
