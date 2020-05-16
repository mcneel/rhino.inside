using Rhino;
using Rhino.Runtime.InProcess;
using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;

namespace InsideNode
{
  public class RhinoMethods
  {

    static RhinoCore rhinoCore;

    static RhinoMethods()
    {
      RhinoInside.Resolver.Initialize();
    }

    public async Task<object> StartRhino(dynamic input)
    {
      try
      {
        rhinoCore = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.NoWindow);
        return "Rhino has started";
      }
      catch (Exception ex)
      {
        return ex.Message;
      }
    }

    public async Task<object> DoSomething(dynamic input)
    {
      var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, input.radius);
      var sphereMesh = Rhino.Geometry.Mesh.CreateFromSphere(sphere, input.countU, input.countV);
      return "The mesh has " + sphereMesh.Vertices.Count + " vertices and " + sphereMesh.Faces.Count + " faces.";
    }

    public async Task<object> ShutdownRhino(dynamic input)
    {
      // Unload Rhino
      try
      {
        rhinoCore.Dispose();
        return "Rhino has shutdown.";
      }
      catch (Exception ex)
      {
        return ex.Message;
      }
    }
  }
}
