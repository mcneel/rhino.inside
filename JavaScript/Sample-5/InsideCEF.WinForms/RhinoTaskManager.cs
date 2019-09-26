using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;
using Rhino;
using Rhino.PlugIns;
using Rhino.Runtime.InProcess;
using Grasshopper;
using Newtonsoft.Json;
using System.Runtime.Serialization;
using Newtonsoft.Json.Serialization;
using Grasshopper.Kernel;
using System.Linq;
using System.Diagnostics;

namespace InsideCEF
{
  /// <summary>
  /// Custom task manager inspired by https://www.infoworld.com/article/3063560/building-your-own-task-scheduler-in-c.html.
  /// </summary>
  public sealed class RhinoInsideTaskManager : TaskScheduler, IDisposable
  {
    private ConcurrentQueue<Task> tasksCollection = new ConcurrentQueue<Task>();
    //private BlockingCollection<Task> tasksCollection = new BlockingCollection<Task>();
    private readonly Thread mainThread = null;
    RhinoCore rhinoCore;
    string rhinoSystemDir;
    Func<object, Task<object>> cb;
    bool RhinoInitialized = false;
    Interop Interop;

    GH_Document definition;

    static readonly Guid GrasshopperGuid = new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF);

    public RhinoInsideTaskManager()
    {
      rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");

      ResolveEventHandler OnRhinoCommonResolve = null;
      ResolveEventHandler OnGrasshopperCommonResolve = null;

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


      AppDomain.CurrentDomain.AssemblyResolve += OnGrasshopperCommonResolve = (sender, args) =>
      {
        const string grasshopperAssemblyName = "Grasshopper";
        var assemblyName = new AssemblyName(args.Name).Name;

        if (assemblyName != grasshopperAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnGrasshopperCommonResolve;

        string rhinoGHDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", @"Plug-ins\Grasshopper");
        return Assembly.LoadFrom(Path.Combine(rhinoGHDir, grasshopperAssemblyName + ".dll"));
      };


      Debug.WriteLine(System.Threading.Thread.CurrentThread.GetApartmentState());
      mainThread = new Thread(new ThreadStart(Execute));
      mainThread.TrySetApartmentState(ApartmentState.STA);
      if (!mainThread.IsAlive)
        mainThread.Start();

      mainThread.Name = "RhinoTaskManagerThread";

    }

    public RhinoInsideTaskManager(Interop interop): this()
    {
      Interop = interop;
    }

    async Task<object> StartRhino(dynamic input)
    {
      // WindowStyle.Hidden: OK, with threaded solution.
      // WindowStyle.Normal: OK, with threaded solution.
      // WindowStyle.NoWindow: OK

      try
      {
        // Start Rhino
        // TODO: use input argument variables here
        //var PATH = Environment.GetEnvironmentVariable("PATH");
        //Environment.SetEnvironmentVariable("PATH", PATH + ";" + rhinoSystemDir);
        rhinoCore = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.Hidden);

        // Subscribe to events
        RhinoApp.Idle += RhinoApp_Idle;
        RhinoApp.Initialized += RhinoApp_Initialized;

        return null;
      }
      catch (Exception ex)
      {
        Debug.Fail(ex.Message, ex.Source);
        return ex;
      }
    }


    async Task<object> StartGrasshopper(dynamic input)
    {
      if (!PlugIn.LoadPlugIn(GrasshopperGuid))
        return null;

      var ghInit = Rhino.RhinoApp.RunScript("!_-Grasshopper _W _T ENTER", false) ? true : false;

      Debug.WriteLine("Grasshopper Initialized.");

      // Subscribe to events
      Grasshopper.Instances.ActiveCanvas.Document_ObjectsAdded += Document_ObjectsAdded;
      Grasshopper.Instances.ActiveCanvas.DocumentChanged += ActiveCanvas_DocumentChanged;

      // input.cb is a callback function in JavaScript.
      // This is to be called whenever there is an added object in the GH canvas.
      if(input.cb != null)
        cb = (Func<object, Task<object>>) input.cb;

      return null;

    }

    /// <summary>
    /// Task to start Rhino.
    /// </summary>
    /// <param name="input"></param>
    /// <returns>TODO: Add more meaningful return object.</returns>
    public async Task<object> StartRhinoTask(dynamic input)
    {
      await Task.Factory.StartNew(() => StartRhino(null), CancellationToken.None, TaskCreationOptions.None, this);
      return null;
    }

    /// <summary>
    /// Task to start Grasshopper.
    /// </summary>
    /// <param name="input"></param>
    /// <returns>TODO: Add more meaningful return object.</returns>
    public async Task<object> StartGrasshopperTask(dynamic input)
    {
      await Task.Factory.StartNew(() => StartGrasshopper(input), CancellationToken.None, TaskCreationOptions.None, this);
      return null;
    }

    public async Task<object> DoSomethingTask(dynamic input)
    {
      await Task.Factory.StartNew(() => DoSomething(input), CancellationToken.None, TaskCreationOptions.None, this);
      return null;
    }

    async Task<object> DoSomething(dynamic input)
    {
      var sphere = new Rhino.Geometry.Sphere(Rhino.Geometry.Point3d.Origin, 2.00);
      var sphereMesh = Rhino.Geometry.Mesh.CreateFromBrep(sphere.ToBrep(), Rhino.Geometry.MeshingParameters.Default)[0];
      cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(sphereMesh, GeometryResolver.Settings));
      return null;
    }

    // Controls the main Rhino message loop.
    private void Execute()
    {
      if (rhinoCore == null)
        StartRhino(null);

      rhinoCore.Run();
    }

    // Event Handlers

    private void ActiveCanvas_DocumentChanged(Grasshopper.GUI.Canvas.GH_Canvas sender, Grasshopper.GUI.Canvas.GH_CanvasDocumentChangedEventArgs e)
    {
      Debug.WriteLine("GH: Doc Changed");
      definition = e.NewDocument;
      definition.SolutionEnd += Definition_SolutionEnd;
    }

    private void Definition_SolutionEnd(object sender, GH_SolutionEventArgs e)
    {
      Debug.WriteLine("GH: Solution End.");

      // Process Meshes
      var mesh = GetDocumentPreview(e.Document);
      cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));

      Interop.PushPreview(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));

    }

    Rhino.Geometry.Mesh GetDocumentPreview(GH_Document document)
    {
      var meshPreview = new Rhino.Geometry.Mesh();

      foreach (var obj in document.Objects.OfType<IGH_ActiveObject>())
      {
        if (obj.Locked)
          continue;

        if (obj is IGH_PreviewObject previewObject)
        {
          if (previewObject.IsPreviewCapable)
          {
            //primitivesBoundingBox = Rhino.Geometry.BoundingBox.Union(primitivesBoundingBox, previewObject.ClippingBox);

            if (obj is IGH_Component component)
            {
              if (!component.Hidden)
                foreach (var param in component.Params.Output)
                  foreach (var value in param.VolatileData.AllData(true))
                  {
                    if (value is IGH_PreviewData)
                    {
                      switch (value.ScriptVariable())
                      {
                        case Rhino.Geometry.Mesh mesh:
                          //Console.WriteLine(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));
                          // cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));
                          meshPreview.Append(mesh);
                          break;
                        case Rhino.Geometry.Brep brep:
                          var previewMesh = new Rhino.Geometry.Mesh();
                          previewMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, Rhino.Geometry.MeshingParameters.Default));
                          //Console.WriteLine(Newtonsoft.Json.JsonConvert.SerializeObject(previewMesh, GeometryResolver.Settings));
                          // cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(previewMesh, GeometryResolver.Settings));
                          meshPreview.Append(previewMesh);
                          break;
                      }
                    }
                  }
            }
            else if (obj is IGH_Param param)
            {
              foreach (var value in param.VolatileData.AllData(true))
              {
                if (value is IGH_PreviewData)
                {
                  switch (value.ScriptVariable())
                  {
                    case Rhino.Geometry.Mesh mesh:
                      // Console.WriteLine(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));
                      // cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));
                      meshPreview.Append(mesh);
                      break;
                    case Rhino.Geometry.Brep brep:
                      var previewMesh = new Rhino.Geometry.Mesh();
                      previewMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, Rhino.Geometry.MeshingParameters.Default));
                      // Console.WriteLine(Newtonsoft.Json.JsonConvert.SerializeObject(previewMesh, GeometryResolver.Settings));
                      // cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(previewMesh, GeometryResolver.Settings));
                      meshPreview.Append(previewMesh);
                      break;
                  }
                }
              }
            }
          }
        }
      }

      return meshPreview;
    }

    private void Document_ObjectsAdded(object sender, Grasshopper.Kernel.GH_DocObjectEventArgs e)
    {
      Debug.WriteLine("GH: Added object to document.");
      //Console.WriteLine(e.Objects[0].Name);

      var activeDefinition = Grasshopper.Instances.ActiveCanvas.Document;







      /*

      var component = e.Objects[0] as Grasshopper.Kernel.GH_Component;

      foreach (var o in component.Params.Output)
      {
        foreach (var value in o.VolatileData.AllData(true))
        {
          if (value is IGH_PreviewData)
          {
            switch (value.ScriptVariable())
            {
              case Rhino.Geometry.Mesh mesh:
                Console.WriteLine(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));
                cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(mesh, GeometryResolver.Settings));
                break;
              case Rhino.Geometry.Brep brep:
                var previewMesh = new Rhino.Geometry.Mesh();
                previewMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, Rhino.Geometry.MeshingParameters.Default));
                Console.WriteLine(Newtonsoft.Json.JsonConvert.SerializeObject(previewMesh, GeometryResolver.Settings));
                cb?.Invoke(Newtonsoft.Json.JsonConvert.SerializeObject(previewMesh, GeometryResolver.Settings));
                break;
            }
          }
        }
      }
      */
      //send data back to Node.js / Electron
      //cb?.Invoke(e.Objects[0].Name);
    }

    private void RhinoApp_Idle(object sender, EventArgs e)
    {
      while (tasksCollection.TryDequeue(out var t))
      {
        TryExecuteTask(t);
      }
    }

    private void RhinoApp_Initialized(object sender, EventArgs e)
    {
      Debug.WriteLine("Rhino Initialized.");
      RhinoInitialized = true;
    }

    //Other methods

    protected override IEnumerable<Task> GetScheduledTasks()
    {
      return tasksCollection.ToArray();
    }

    protected override void QueueTask(Task task)
    {
      if (task != null)
        tasksCollection.Enqueue(task);
    }

    protected override bool TryExecuteTaskInline(Task task, bool taskWasPreviouslyQueued)
    {
      return false;
    }

    private void Dispose(bool disposing)
    {
      if (!disposing) return;
      //tasksCollection.CompleteAdding();
      //tasksCollection.Dispose();
    }

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }


    // from Compute: https://github.com/mcneel/compute.rhino3d/blob/master/src/compute.geometry/GeometryEndPoint.cs#L568-L671
    class ArchivableDictionaryResolver : JsonConverter
    {
      public override bool CanConvert(Type objectType)
      {
        return objectType == typeof(Rhino.Collections.ArchivableDictionary);
      }

      public override bool CanRead => true;
      public override bool CanWrite => true;

      public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
      {
        string encoded = (string) reader.Value;
        var dh = JsonConvert.DeserializeObject<DictHelper>(encoded);
        return dh.SerializedDictionary;
      }

      public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
      {
        string json = JsonConvert.SerializeObject(new DictHelper((Rhino.Collections.ArchivableDictionary) value));
        writer.WriteValue(json);
      }


      [Serializable]
      class DictHelper : ISerializable
      {
        public Rhino.Collections.ArchivableDictionary SerializedDictionary { get; set; }
        public DictHelper(Rhino.Collections.ArchivableDictionary d) { SerializedDictionary = d; }
        public virtual void GetObjectData(SerializationInfo info, StreamingContext context)
        {
          SerializedDictionary.GetObjectData(info, context);
        }
        protected DictHelper(SerializationInfo info, StreamingContext context)
        {
          Type t = typeof(Rhino.Collections.ArchivableDictionary);
          var constructor = t.GetConstructor(System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance,
            null, new Type[] { typeof(SerializationInfo), typeof(StreamingContext) }, null);
          SerializedDictionary = constructor.Invoke(new object[] { info, context }) as Rhino.Collections.ArchivableDictionary;
        }
      }
    }

    public class GeometryResolver : DefaultContractResolver
    {
      static JsonSerializerSettings _settings;
      public static JsonSerializerSettings Settings
      {
        get
        {
          if (_settings == null)
          {
            _settings = new JsonSerializerSettings { ContractResolver = new GeometryResolver() };
            // return V6 ON_Objects for now
            var options = new Rhino.FileIO.SerializationOptions();
            options.RhinoVersion = 6;
            options.WriteUserData = true;
            _settings.Context = new System.Runtime.Serialization.StreamingContext(System.Runtime.Serialization.StreamingContextStates.All, options);
            _settings.Converters.Add(new ArchivableDictionaryResolver());
          }
          return _settings;
        }
      }

      protected override JsonProperty CreateProperty(MemberInfo member, MemberSerialization memberSerialization)
      {
        JsonProperty property = base.CreateProperty(member, memberSerialization);
        if (property.DeclaringType == typeof(Rhino.Geometry.Circle))
        {
          property.ShouldSerialize = _ =>
          {
            return property.PropertyName != "IsValid" && property.PropertyName != "BoundingBox" && property.PropertyName != "Diameter" && property.PropertyName != "Circumference";
          };

        }
        if (property.DeclaringType == typeof(Rhino.Geometry.Plane))
        {
          property.ShouldSerialize = _ =>
          {
            return property.PropertyName != "IsValid" && property.PropertyName != "OriginX" && property.PropertyName != "OriginY" && property.PropertyName != "OriginZ";
          };
        }

        if (property.DeclaringType == typeof(Rhino.Geometry.Point3f) ||
            property.DeclaringType == typeof(Rhino.Geometry.Point2f) ||
            property.DeclaringType == typeof(Rhino.Geometry.Vector2f) ||
            property.DeclaringType == typeof(Rhino.Geometry.Vector3f))
        {
          property.ShouldSerialize = _ =>
          {
            return property.PropertyName == "X" || property.PropertyName == "Y" || property.PropertyName == "Z";
          };
        }

        if (property.DeclaringType == typeof(Rhino.Geometry.MeshFace))
        {
          property.ShouldSerialize = _ =>
          {
            return property.PropertyName != "IsTriangle" && property.PropertyName != "IsQuad";
          };
        }
        return property;
      }
    }

  }
}
