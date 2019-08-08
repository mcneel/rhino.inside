using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using PaintDotNet;
using PaintDotNet.Core;
using PaintDotNet.Effects;
using Rhino;
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


    private readonly Thread rhinoThread = null;

    Bitmap bm;

    //static RhinoTaskManager rhinoTaskManager;

    static RhinoPaint()
    {
      Debug.WriteLine("Static Constructor.");
      //rhinoTaskManager = new RhinoTaskManager();

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

    public RhinoPaint() : base(StaticName, Properties.Resources.RhinoPaintTmp.ToBitmap(), "Rhinoceros", new EffectOptions { Flags = EffectFlags.SingleThreaded, RenderingSchedule = EffectRenderingSchedule.None })
    {
      Debug.WriteLine("Base Constructor.");
      Debug.WriteLine(Thread.CurrentThread.GetApartmentState().ToString());
      rhinoThread = new Thread(new ThreadStart(StartRhino));
      rhinoThread.TrySetApartmentState(ApartmentState.STA);
      rhinoThread.Name = "RhinoTaskManagerThread";
    }

    void StartRhino()
    {
      try
      {
        using (new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.Normal))
        {
          var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 10.00);
          var sphereMesh = Rhino.Geometry.Mesh.CreateFromBrep(sphere.ToBrep(), Rhino.Geometry.MeshingParameters.Default)[0];
          Debug.WriteLine("The mesh has " + sphereMesh.Vertices.Count + " vertices and " + sphereMesh.Faces.Count + " faces.");

          RhinoDoc.ActiveDoc.Objects.AddMesh(sphereMesh);
          RhinoDoc.ActiveDoc.Views.Redraw();
          bm = RhinoDoc.ActiveDoc.Views.ActiveView.CaptureToBitmap();

        }
      }
      catch (Exception ex)
      {
        Debug.WriteLine(ex);
      }
    }

    public override void Render(EffectConfigToken parameters, RenderArgs dstArgs, RenderArgs srcArgs, Rectangle[] rois, int startIndex, int length)
    {
      /*
      var result = rhinoTaskManager.DoSomething(null);
      result.Wait();
      Debug.WriteLine(result.Result);

      var bmRes = rhinoTaskManager.GetViewport(null);
      bmRes.Wait();

      var bm = bmRes.Result;
      */

      rhinoThread.Start();
      while(rhinoThread.ThreadState != System.Threading.ThreadState.Stopped) { }
      

      PdnRegion selectionRegion = EnvironmentParameters.GetSelection(srcArgs.Bounds);

      for (int i = startIndex; i < startIndex + length; ++i)
      {
        Rectangle rect = rois[i];

        //srcArgs.Surface.CopyFromGdipBitmap(bmRes.Result);

        for (int y = rect.Top; y < rect.Bottom; ++y)
        {
          for (int x = rect.Left; x < rect.Right; ++x)
          {
            // Render Code Here
            Color pixel;
            if (x < bm.Width && y < bm.Height)
              pixel = bm.GetPixel(x, y);
            else
              pixel = Color.Black;

            //ColorBgra pixel = srcArgs.Surface[x, y];
            dstArgs.Surface[x, y] = ColorBgra.FromColor(pixel);
          }
        }
      }

    }

  }
}
