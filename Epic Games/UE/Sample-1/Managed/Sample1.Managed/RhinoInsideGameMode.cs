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
    class ARhinoInsideGameMode : AGameMode
    {

        Rhino.Runtime.InProcess.RhinoCore m_rhino_core;

        static ARhinoInsideGameMode()
        {
            FMessage.Log(ELogVerbosity.Warning, "Hello from C# ARhinoInsideGameMode:Static Constructor)");

            // Resolve RhinoCommon assembly reference

            ResolveEventHandler OnRhinoCommonResolve = null;
            AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
            {
                const string rhino_common_assembly_name = "RhinoCommon";
                var assembly_name = new AssemblyName(args.Name).Name;

                if (assembly_name != rhino_common_assembly_name)
                    return null;

                AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

                var rhino_system_dir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
                return Assembly.LoadFrom(Path.Combine(rhino_system_dir, rhino_common_assembly_name + ".dll"));
            };

        }
        public override void Initialize(FObjectInitializer initializer)
        {
            base.Initialize(initializer);

            FMessage.Log(ELogVerbosity.Warning, "Hello from C# (" + this.GetType().ToString() + ":Initialize)");

            // Load Rhino
            try
            {
                //Run Rhino.Inside no UI
                m_rhino_core = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.NoWindow);

                FMessage.Log(ELogVerbosity.Warning, DoSomething());
            }
            catch (Exception ex)
            {
                FMessage.Log(ELogVerbosity.Error, "Cannot load Rhino Inside");
                FMessage.Log(ELogVerbosity.Error, ex.Message);
                FMessage.Log(ELogVerbosity.Error, ex.InnerException.ToString());
                FMessage.Log(ELogVerbosity.Error, ex.InnerException.Source);
            }
        }
        protected override void BeginPlay()
        {
            base.BeginPlay();
            
            FMessage.Log(ELogVerbosity.Warning, "Hello from C# (" + this.GetType().ToString() + ":BeginPlay)");
        }

        public string DoSomething()
        {
            var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 10.00);
            var sphereMesh = Rhino.Geometry.Mesh.CreateFromBrep(sphere.ToBrep(), Rhino.Geometry.MeshingParameters.Default);
            return "The mesh has " + sphereMesh[0].Vertices.Count + " vertices and " + sphereMesh[0].Faces.Count + " faces.";
        }

    }
}
