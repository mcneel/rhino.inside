using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Rhino;
using Rhino.Runtime.InProcess;

namespace RhinoPaint
{
  public sealed class RhinoTaskManager : TaskScheduler, IDisposable
  {

    private ConcurrentQueue<Task> tasksCollection = new ConcurrentQueue<Task>();

    private readonly Thread mainThread = null;

    RhinoCore rhinoCore;

    string rhinoSystemDir;

    public RhinoTaskManager()
    {
      rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
      ResolveEventHandler OnRhinoCommonResolve = null;

      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhinoCommonAssemblyName = "RhinoCommon";
        var assemblyName = new AssemblyName(args.Name).Name;

        if (assemblyName != rhinoCommonAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

        //rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
        return Assembly.LoadFrom(Path.Combine(rhinoSystemDir, rhinoCommonAssemblyName + ".dll"));
      };

      mainThread = new Thread(new ThreadStart(Execute));
      mainThread.TrySetApartmentState(ApartmentState.STA);
      if (!mainThread.IsAlive)
        mainThread.Start();

      mainThread.Name = "RhinoTaskManagerThread";

    }

    private void Execute()
    {
      if (rhinoCore == null)
        StartRhino(null);

      rhinoCore.Run();
    }

    public async Task<object> StartRhino(dynamic input)
    {
      // WindowStyle.Hidden: OK, with threaded solution.
      // WindowStyle.Normal: OK, with threaded solution.
      // WindowStyle.NoWindow: OK

      try
      {
        // Start Rhino
        // TODO: use input argument variables here

        rhinoCore = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.Normal);

        // Subscribe to events
        RhinoApp.Idle += RhinoApp_Idle;
        RhinoApp.Initialized += RhinoApp_Initialized;

        return "Rhino Started";
      }
      catch (Exception ex)
      {
        return ex;
      }
    }

    public async Task<string> DoSomething(dynamic input)
    {
      var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 2.00);
      var sphereMesh = Rhino.Geometry.Mesh.CreateFromBrep(sphere.ToBrep(), Rhino.Geometry.MeshingParameters.Default)[0];
      return "Ran Do Something";
    }

    public async Task<Bitmap> GetViewport(dynamic input)
    {
      var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 2.00);
      var sphereMesh = Rhino.Geometry.Mesh.CreateFromBrep(sphere.ToBrep(), Rhino.Geometry.MeshingParameters.Default)[0];
      RhinoDoc.ActiveDoc.Objects.AddMesh(sphereMesh);
      RhinoDoc.ActiveDoc.Views.Redraw();
      var bm = RhinoDoc.ActiveDoc.Views.ActiveView.CaptureToBitmap();
      return bm;
    }

    public async Task<string> DoSomethingTask(dynamic input)
    {
      return await Task.Factory.StartNew(() => DoSomething(input), CancellationToken.None, TaskCreationOptions.None, this);
    }

    private void RhinoApp_Idle(object sender, EventArgs e)
    {
      ExecuteTasks();
    }

    private void RhinoApp_Initialized(object sender, EventArgs e)
    {
      Debug.WriteLine("Rhino Initialized.");
    }

    protected override void QueueTask(Task task)
    {
      if (task != null)
      {
        tasksCollection.Enqueue(task);
      }
    }

    private void ExecuteTasks()
    {
      while (tasksCollection.TryDequeue(out var t))
      {
        TryExecuteTask(t);
      }
    }

    protected override bool TryExecuteTaskInline(Task task, bool taskWasPreviouslyQueued)
    {
      return false;
    }

    protected override IEnumerable<Task> GetScheduledTasks()
    {
      return tasksCollection.ToArray();
    }

    private void Dispose(bool disposing)
    {
      if (!disposing) return;
    }

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }
  }
}
