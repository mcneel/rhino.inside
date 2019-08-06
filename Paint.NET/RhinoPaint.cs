using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using PaintDotNet;
using PaintDotNet.Core;
using PaintDotNet.Effects;
using Rhino.Runtime.InProcess;

namespace RhinoPaint
{
    public class RhinoPaint : PaintDotNet.Effects.Effect
    {

        public static string StaticName
        {
            get
            {
                return "RhinoPaint";
            }
        }
           
        public RhinoPaint(): base(StaticName, Properties.Resources.RhinoPaintTmp.ToBitmap(), "Rhinoceros", new EffectOptions())
        {
            ResolveEventHandler OnRhinoCommonResolve = null;
            AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
            {
                const string rhinoCommonAssemblyName = "RhinoCommon";
                var assemblyName = new AssemblyName(args.Name).Name;

                if (assemblyName != rhinoCommonAssemblyName)
                    return null;

                AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

                string rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
                return Assembly.LoadFrom(Path.Combine(rhinoSystemDir, rhinoCommonAssemblyName + ".dll"));
            };
        }
        public override void Render(EffectConfigToken parameters, RenderArgs dstArgs, RenderArgs srcArgs, Rectangle[] rois, int startIndex, int length)
        {
            try
            {
                using (new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.NoWindow))
                {
                    var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 10.00);
                    var sphereMesh = Rhino.Geometry.Mesh.CreateFromBrep(sphere.ToBrep(), Rhino.Geometry.MeshingParameters.Default);
                    Debug.WriteLine("The mesh has " + sphereMesh[0].Vertices.Count + " vertices and " + sphereMesh[0].Faces.Count + " faces.");
                }

            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                //return ex.Message;
            }
            /*

            PdnRegion selectionRegion = EnvironmentParameters.GetSelection(srcArgs.Bounds);

            for (int i = startIndex; i < startIndex + length; ++i)
            {
                Rectangle rect = rois[i];

                for (int y = rect.Top; y < rect.Bottom; ++y)
                {
                    for (int x = rect.Left; x < rect.Right; ++x)
                    {
                        // Render Code Here
                    }
                }
            }
            ^*/

        }

        
    }
}
