using System;
using Rhino.Geometry;

namespace HelloWorld
{
  class Program
  {
    static void Main(string[] args)
    {
      try
      {
        RhinoLib.LaunchInProcess(RhinoLib.LoadMode.Headless, 0);
        MeshABrep();
      }
      catch (Exception ex)
      {
        Console.WriteLine(ex.Message);
      }
      Console.WriteLine("press any key to exit");
      Console.ReadKey();
      RhinoLib.ExitInProcess();
    }

    // Place calls to RhinoCommon in a separate function from main so the jit doesn't
    // try to load RhinoCommon until after RhinoLib.LaunchInProcess is called
    static void MeshABrep()
    {
      var sphere = new Sphere(Point3d.Origin, 12);
      var brep = sphere.ToBrep();
      var mp = new MeshingParameters(0.5);
      var mesh = Mesh.CreateFromBrep(brep, mp);
      Console.WriteLine($"Mesh with {mesh[0].Vertices.Count} vertices created");
    }
  }
}
