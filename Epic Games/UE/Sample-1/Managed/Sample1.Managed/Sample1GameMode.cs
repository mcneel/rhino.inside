using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnrealEngine.Runtime;
using UnrealEngine.Engine;
using System.Reflection;
using System.IO;
using Rhino.Runtime.InProcess;

namespace Sample1
{
  [UClass, BlueprintType, Blueprintable]
  class ASample1GameMode : AGameMode
  {
    RhinoCore rhinoCore;

    static ASample1GameMode()
    {
      // Resolve RhinoCommon assembly reference
      RhinoInside.Resolver.Initialize();
    }

    protected override void BeginPlay()
    {
      base.BeginPlay();

      FMessage.Log(ELogVerbosity.Warning, "Hello from C# (" + this.GetType().ToString() + ":BeginPlay)");

      //Run Rhino.Inside no UI
      if (rhinoCore == null)
      {
        rhinoCore = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.NoWindow);
        FMessage.Log(ELogVerbosity.Warning, DoSomething());
      }
    }

    public string DoSomething()
    {
      var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 10.00);
      var sphereMesh = Rhino.Geometry.Mesh.CreateFromBrep(sphere.ToBrep(), Rhino.Geometry.MeshingParameters.Default);
      return "The mesh has " + sphereMesh[0].Vertices.Count + " vertices and " + sphereMesh[0].Faces.Count + " faces.";
    }

  }
}
