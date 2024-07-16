using System;
using System.IO;
using System.Reflection;

using Rhino.Runtime.InProcess;
using Rhino.Geometry;
using RhinoInside;

namespace HelloWorld
{
  static class TestClient
  {
    static TestClient()
    {
      string rhinoPath = Environment.GetEnvironmentVariable("RHINOINSIDE_RHINOPATH");

#if NET7_0_OR_GREATER
      Resolver.Initialize(rhinoPath);
#else
      Resolver.RhinoSystemDirectory = rhinoPath;
      Resolver.Initialize();
#endif
    }

    [System.STAThread]
    static void Main(string[] args)
    {
      try
      {
        string arg = args[0];
        switch (arg)
        {
          case "mesh-test":
            Environment.Exit(TestCases.RunMeshABrep());
            break;
        }
      }
      catch (Exception ex)
      {
        Environment.Exit(1);
      }
    }
  }

  static class TestCases
  {
    public static int RunMeshABrep()
    {
      using (new RhinoCore())
      {
        return MeshABrep() ? 0 : 1;
      }
    }

    static bool MeshABrep()
    {
      var sphere = new Sphere(Point3d.Origin, 12);
      var brep = sphere.ToBrep();
      var mp = new MeshingParameters(0.5);
      var mesh = Mesh.CreateFromBrep(brep, mp);
      return mesh[0].Vertices.Count > 0;
    }
  }
}
