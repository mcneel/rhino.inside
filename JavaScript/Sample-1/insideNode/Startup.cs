using Rhino;
using Rhino.Runtime.InProcess;
using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;

namespace insideNode
{
    public class Startup
    {

        static Startup()
        {
          RhinoInside.Resolver.Initialize();
        }

        public async Task<object> Invoke(dynamic input)
        {
      
            try
            {
                using (new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.NoWindow))
                {
                    var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 10.00);
                    var sphereMesh = Rhino.Geometry.Mesh.CreateFromSphere(sphere, input, input);
                    return "The mesh has " + sphereMesh.Vertices.Count + " vertices and " + sphereMesh.Faces.Count + " faces.";
                }

            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                return ex.Message;
            }

        }
    }
}
