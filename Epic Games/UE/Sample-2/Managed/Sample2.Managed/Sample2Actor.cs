using System.Collections.Generic;
using Rhino.Runtime.InProcess;
using UnrealEngine.Engine;
using UnrealEngine.Runtime;

namespace Sample2
{
  [UClass, BlueprintType, Blueprintable]
  class ASample2Actor : AActor
  {
    static RhinoCore rhinoCore;
    static Rhino.Geometry.Mesh mesh;

    /// <summary>
    /// Resolve the local Rhino related assemblies.
    /// </summary>
    static ASample2Actor()
    {
      RhinoInside.Resolver.Initialize();
    }

    /// <summary>
    /// Start Rhino if it has not already been started.
    /// We start Rhino without a spash screen and with a hidden `WindowStyle`.
    /// We could use the `NoWindow` display, since we don't need the Rhino UI.
    /// </summary>
    [UFunction, BlueprintCallable]
    public void LaunchRhino()
    {
      if (rhinoCore == null)
        rhinoCore = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.Hidden);
    }

    /// <summary>
    /// Do something with RhinoCommon.
    /// </summary>
    [UFunction, BlueprintCallable]
    public void DoSomething()
    {
      var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 10);
      mesh = Rhino.Geometry.Mesh.CreateFromSphere(sphere, 10, 10);
      mesh.Faces.ConvertQuadsToTriangles();
      mesh.Flip(true, true, true);

      FMessage.Log(ELogVerbosity.Warning, "Created a mesh with " + mesh.Vertices.Count.ToString() + " vertices and " + mesh.Vertices.Count.ToString() + " Faces.");
    }

    [UFunction, BlueprintCallable]
    public List<FVector> GetVertices()
    {
      var list = new List<FVector>();
      foreach (var vert in mesh.Vertices)
        list.Add(new FVector(vert.X, vert.Y, vert.Z));
      return list;
    }

    [UFunction, BlueprintCallable]
    public List<int> GetFaceIds()
    {
      var list = new List<int>();
      foreach (var face in mesh.Faces)
      {
        list.Add(face.A);
        list.Add(face.B);
        list.Add(face.C);
      }
      return list;
    }


  }
}
