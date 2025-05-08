using System;
using System.IO;
using System.Reflection;

using Rhino.Runtime.InProcess;
using Rhino.Geometry;

namespace RhinoInside.TestClient
{
  static class TestClient
  {
    static TestClient()
    {
      string rhinoPath = Environment.GetEnvironmentVariable("RHINOINSIDE_RHINOPATH");
      Resolver.Initialize(rhinoPath);
      Console.WriteLine($"Loading Rhino @ {Resolver.RhinoSystemDirectory}");
    }

    [System.STAThread]
    static void Main(string[] args)
    {
      try
      {
        string arg = args[0];
        switch (arg)
        {
          case "test_MeshFromBrep":
            Environment.Exit(TestCases.RunMeshFromBrep());
            break;
        }
      }
      catch (Exception ex)
      {
        Console.Error.WriteLine(ex.ToString());
        Environment.Exit(1);
      }
    }
  }

  static class TestCases
  {
    public static int RunMeshFromBrep()
    {
      using (new RhinoCore())
      {
        Console.WriteLine("Running Mesh From Brep Test");
        var sphere = new Sphere(Point3d.Origin, 12);
        var brep = sphere.ToBrep();
        var mp = new MeshingParameters(0.5);
        var mesh = Mesh.CreateFromBrep(brep, mp);
        Console.WriteLine($"Mesh Vertices: {mesh[0].Vertices.Count}");
        return mesh[0].Vertices.Count > 0 ? 0 : 1;
      }
    }
  }
}
