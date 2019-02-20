using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

using Autodesk;
using Autodesk.Revit;
using Autodesk.Revit.DB;
using Autodesk.Revit.DB.Events;
using Autodesk.Revit.UI;
using Autodesk.Revit.UI.Events;
using Autodesk.Revit.DB.DirectContext3D;
using Autodesk.Revit.DB.ExternalService;

using Rhino;
using Rhino.Runtime.InProcess;
using Rhino.PlugIns;

using Grasshopper;
using Grasshopper.Kernel;
using Grasshopper.GUI.Canvas;

namespace RhinoInside.Revit
{
  [Autodesk.Revit.Attributes.Transaction(Autodesk.Revit.Attributes.TransactionMode.Manual)]
  [Autodesk.Revit.Attributes.Regeneration(Autodesk.Revit.Attributes.RegenerationOption.Manual)]
  [Autodesk.Revit.Attributes.Journaling(Autodesk.Revit.Attributes.JournalingMode.NoCommandData)]
  public partial class Revit : IExternalApplication
  {
    #region Revit static constructor
    static Revit()
    {
      ResolveEventHandler OnRhinoCommonResolve = null;
      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhinoCommonAssemblyName = "RhinoCommon";
        var assemblyName = new AssemblyName(args.Name).Name;

        if (assemblyName != rhinoCommonAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

        var rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
        return Assembly.LoadFrom(Path.Combine(rhinoSystemDir, rhinoCommonAssemblyName + ".dll"));
      };
    }
    #endregion

    #region IExternalApplication Members
    RhinoCore rhinoCore;
    //DocumentPreviewServer documentPreviewServer;
    GrasshopperPreviewServer grasshopperPreviewServer;

    public Result OnStartup(UIControlledApplication applicationUI)
    {
      ApplicationUI = applicationUI;

#if REVIT_2019
      MainWindowHandle = ApplicationUI.MainWindowHandle;
#else
      MainWindowHandle = Process.GetCurrentProcess().MainWindowHandle;
#endif

      // Load Rhino
      try
      {
        var schemeName = ApplicationUI.ControlledApplication.VersionName.Replace(' ', '-');
        rhinoCore = new RhinoCore(new string[] { $"/scheme={schemeName}", "/nosplash" }, WindowStyle.Hidden, MainWindowHandle);
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
        return Result.Failed;
      }

      // Reset document units
      UI.RhinoCommand.ResetDocumentUnits(Rhino.RhinoDoc.ActiveDoc);

      // Register UI on Revit
      {
        var ribbonPanel = ApplicationUI.CreateRibbonPanel("Rhinoceros");

        UI.RhinoCommand.CreateUI(ribbonPanel);
        UI.GrasshopperCommand.CreateUI(ribbonPanel);
        ribbonPanel.AddSeparator();
        Sample1.CreateUI(ribbonPanel);
        Sample4.CreateUI(ribbonPanel);
        ribbonPanel.AddSeparator();
        UI.APIDocsCommand.CreateUI(ribbonPanel);
      }

      // Register some events
      ApplicationUI.Idling += OnIdle;
      ApplicationUI.ControlledApplication.DocumentChanged += OnDocumentChanged;

      // Register as a DirectContext3DServer
      //documentPreviewServer = new DocumentPreviewServer();
      //documentPreviewServer.Register();

      grasshopperPreviewServer = new GrasshopperPreviewServer();
      grasshopperPreviewServer.Register();

      return Result.Succeeded;
    }

    public Result OnShutdown(UIControlledApplication applicationUI)
    {
      // Unregister as a DirectContext3DServer
      grasshopperPreviewServer?.Unregister();
      grasshopperPreviewServer = null;

      //documentPreviewServer?.Unregister();
      //documentPreviewServer = null;

      // Unregister some events
      ApplicationUI.ControlledApplication.DocumentChanged -= OnDocumentChanged;
      ApplicationUI.Idling -= OnIdle;

      // Unload Rhino
      try
      {
        rhinoCore.Dispose();
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
        return Result.Failed;
      }

      ApplicationUI = null;
      return Result.Succeeded;
    }

    public static bool Committing = false;
    static bool LoadGrasshopperComponents()
    {
      var LoadGHAProc = Instances.ComponentServer.GetType().GetMethod("LoadGHA", BindingFlags.NonPublic | BindingFlags.Instance);
      if (LoadGHAProc == null)
        return false;

      var bCoff = Instances.Settings.GetValue("Assemblies:COFF", true);
      Instances.Settings.SetValue("Assemblies:COFF", false);

      var rc = (bool) LoadGHAProc.Invoke
      (
        Instances.ComponentServer,
        new object[] { new GH_ExternalFile(Assembly.GetExecutingAssembly().Location), false }
      );

      Instances.Settings.SetValue("Assemblies:COFF", bCoff);

      if (rc)
        GH_ComponentServer.UpdateRibbonUI();

      return rc;
    }

    static bool LoadedAsGHA = false;
    void OnIdle(object sender, IdlingEventArgs args)
    {
      // 1. Do Rhino pending OnIdle tasks
      if (rhinoCore.OnIdle())
      {
        args.SetRaiseWithoutDelay();
        return;
      }

      // Load this assembly as a Grasshopper assembly
      if (!LoadedAsGHA && PlugIn.GetPlugInInfo(new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF)).IsLoaded)
        LoadedAsGHA = LoadGrasshopperComponents();

      // Document dependant tasks need a document
      ActiveUIApplication = (sender as UIApplication);
      if (ActiveDBDocument != null)
      {
        // 1. Do all document read actions
        if (ProcessReadActions())
        {
          args.SetRaiseWithoutDelay();
          return;
        }

        // 2. Do all document write actions
        if (!ActiveDBDocument.IsReadOnly)
          ProcessWriteActions();
      }
    }

    private void OnDocumentChanged(object sender, DocumentChangedEventArgs e)
    {
      if (Committing)
        return;

      var document = e.GetDocument();
      if (!document.Equals(ActiveDBDocument))
        return;

      ProcessReadActions(true);

      var materialsChanged = e.GetModifiedElementIds().Select((x) => document.GetElement(x)).OfType<Material>().Any();

      foreach (GH_Document definition in Grasshopper.Instances.DocumentServer)
      {
        foreach (var obj in definition.Objects)
        {
          if (obj is GH.Parameters.Element element)
          {
            if (element.SourceCount > 0)
              continue;

            if (element.Phase == GH_SolutionPhase.Blank)
              continue;

            element.ExpireSolution(false);
          }
          else if (obj is GH_Component component)
          {
            if (component is GH.Components.DocumentElements)
            {
              component.ExpireSolution(false);
            }
            else foreach (var param in component.Params.Output)
            {
              if (param is GH.Parameters.Element outElement)
              {
                if (materialsChanged)
                {
                  foreach (var goo in param.VolatileData.AllData(true))
                  {
                    if (goo is IGH_PreviewMeshData previewMeshData)
                      previewMeshData.DestroyPreviewMeshes();
                  }
                }

                foreach (var r in param.Recipients)
                  r.ExpireSolution(false);
              }
            }
          }
        }

        if (definition.Enabled)
          definition.NewSolution(false);
      }
    }
    #endregion

    #region Bake Recipe
    public static void BakeGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries, BuiltInCategory categoryToBakeInto = BuiltInCategory.OST_GenericModel)
    {
      if (categoryToBakeInto == BuiltInCategory.INVALID)
        return;

      EnqueueAction
      (
        (doc) =>
        {
          foreach (var geometryToBake in geometries.ToHost())
          {
            if (geometryToBake == null)
              continue;

            BakeGeometry(doc, geometryToBake, categoryToBakeInto);
          }
        }
      );
    }

    static partial void TraceGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries);
#if DEBUG
    static partial void TraceGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      EnqueueAction
      (
        (doc) =>
        {
          using (var attributes = Convert.GraphicAttributes.Push())
          {
            using (var collector = new FilteredElementCollector(ActiveDBDocument))
            {
              var materials = collector.OfClass(typeof(Material)).Cast<Material>();
              attributes.MaterialId = (materials.Where((x) => x.Name == "Debug").FirstOrDefault()?.Id) ?? ElementId.InvalidElementId;
            }

            foreach (var geometryToBake in geometries.ToHost())
            {
              if (geometryToBake == null)
                continue;

              BakeGeometry(doc, geometryToBake, BuiltInCategory.OST_GenericModel);
            }
          }
        }
      );
    }
#endif

    static void BakeGeometry(Document doc, IEnumerable<GeometryObject> geometryToBake, BuiltInCategory categoryToBakeInto)
    {
      try
      {
        var geometryList = new List<GeometryObject>();

        // DirectShape only accepts those types and no nulls
        foreach (var g in geometryToBake)
        {
          switch (g)
          {
            case Point p: geometryList.Add(p); break;
            case Curve c: geometryList.Add(c); break;
            case Solid s: geometryList.Add(s); break;
            case Mesh m: geometryList.Add(m); break;
          }
        }

        if (geometryList.Count > 0)
        {
          var category = new ElementId(categoryToBakeInto);
          if (!DirectShape.IsValidCategoryId(category, doc))
            category = new ElementId(BuiltInCategory.OST_GenericModel);

          var ds = DirectShape.CreateElement(doc, category);
          ds.SetShape(geometryList);
        }
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
      }
    }
    #endregion

    #region Document Actions
    private static Queue<Action<Document>> docWriteActions = new Queue<Action<Document>>();
    public static void EnqueueAction(Action<Document> action)
    {
      lock (docWriteActions)
        docWriteActions.Enqueue(action);
    }

    void ProcessWriteActions()
    {
      lock (docWriteActions)
      {
        if (docWriteActions.Count > 0)
        {
          using (var trans = new Transaction(ActiveDBDocument))
          {
            try
            {
              if (trans.Start("RhinoInside") == TransactionStatus.Started)
              {
                while (docWriteActions.Count > 0)
                  docWriteActions.Dequeue().Invoke(ActiveDBDocument);

                Committing = true;
                var options = trans.GetFailureHandlingOptions();
                trans.Commit(options.SetDelayedMiniWarnings(true).SetForcedModalHandling(false).SetFailuresPreprocessor(new FailuresPreprocessor()));
                Committing = false;

                foreach (GH_Document definition in Grasshopper.Instances.DocumentServer)
                {
                  if (definition.Enabled)
                    definition.NewSolution(false);
                }
              }
            }
            catch (Exception e)
            {
              Debug.Fail(e.Source, e.Message);

              if (trans.HasStarted())
                trans.RollBack();
            }
            finally
            {
              docWriteActions.Clear();
            }
          }
        }
      }
    }

    private static Queue<Action<Document, bool>> docReadActions = new Queue<Action<Document, bool>>();
    public static void EnqueueReadAction(Action<Document, bool> action)
    {
      lock (docReadActions)
        docReadActions.Enqueue(action);
    }

    bool ProcessReadActions(bool cancel = false)
    {
      lock (docReadActions)
      {
        if (docReadActions.Count > 0)
        {
          var stopWatch = new Stopwatch();

          while (docReadActions.Count > 0)
          {
            // We will do as much work as possible in 150 ms on each OnIdle event
            if (!cancel && stopWatch.ElapsedMilliseconds > 150)
              return true; // there is pending work to do

            stopWatch.Start();
            try { docReadActions.Dequeue().Invoke(ActiveDBDocument, cancel); }
            catch (Exception e) { Debug.Fail(e.Source, e.Message); }
            stopWatch.Stop();
          }
        }
      }

      // there is no more work to do
      return false;
    }
    #endregion

    #region Public Properties
    public static IntPtr MainWindowHandle { get; private set; }
    public static Autodesk.Revit.UI.UIControlledApplication ApplicationUI { get; private set; }
    public static Autodesk.Revit.UI.UIApplication ActiveUIApplication { get; private set; }
    public static Autodesk.Revit.ApplicationServices.Application Services => ActiveUIApplication?.Application;

    public static Autodesk.Revit.UI.UIDocument ActiveUIDocument => ActiveUIApplication?.ActiveUIDocument;
    public static Autodesk.Revit.DB.Document   ActiveDBDocument => ActiveUIDocument?.Document;

    private const double AbsoluteTolerance = (1.0 / 12.0) / 16.0; // 1/16 inch in feet
    public static double AngleTolerance => Services != null ? Services.AngleTolerance : Math.PI / 180.0; // in rad
    public static double ShortCurveTolerance => Services != null ? Services.ShortCurveTolerance : AbsoluteTolerance / 2.0;
    public static double VertexTolerance => Services != null ? Services.VertexTolerance : AbsoluteTolerance / 10.0;
    public const Rhino.UnitSystem ModelUnitSystem = Rhino.UnitSystem.Feet; // Always feet
    public static double ModelUnits => RhinoDoc.ActiveDoc == null ? double.NaN : RhinoMath.UnitScale(ModelUnitSystem, RhinoDoc.ActiveDoc.ModelUnitSystem); // 1 feet in Rhino units
    #endregion
  }

  public abstract class DirectContext3DServer : IDirectContext3DServer
  {
    #region IExternalServer
    public abstract string GetDescription();
    public abstract string GetName();
    string IExternalServer.GetVendorId() => "RMA";
    ExternalServiceId IExternalServer.GetServiceId() => ExternalServices.BuiltInExternalServices.DirectContext3DService;
    public abstract Guid GetServerId();
    #endregion

    #region IDirectContext3DServer
    string IDirectContext3DServer.GetApplicationId() => string.Empty;
    string IDirectContext3DServer.GetSourceId() => string.Empty;
    bool IDirectContext3DServer.UsesHandles() => false;
    public virtual bool UseInTransparentPass(Autodesk.Revit.DB.View dBView) => false;
    public abstract bool CanExecute(Autodesk.Revit.DB.View dBView);
    public abstract Outline GetBoundingBox(Autodesk.Revit.DB.View dBView);
    public abstract void RenderScene(Autodesk.Revit.DB.View dBView, DisplayStyle displayStyle);
    #endregion

    virtual public void Register()
    {
      using (var service = ExternalServiceRegistry.GetService(ExternalServices.BuiltInExternalServices.DirectContext3DService) as MultiServerService)
      {
        service.AddServer(this);

        var activeServerIds = service.GetActiveServerIds();
        activeServerIds.Add(GetServerId());
        service.SetActiveServers(activeServerIds);
      }
    }

    virtual public void Unregister()
    {
      using (var service = ExternalServiceRegistry.GetService(ExternalServices.BuiltInExternalServices.DirectContext3DService) as MultiServerService)
      {
        var activeServerIds = service.GetActiveServerIds();
        activeServerIds.Remove(GetServerId());
        service.SetActiveServers(activeServerIds);

        service.RemoveServer(GetServerId());
      }
    }

    protected static VertexBuffer ToVertexBuffer(Rhino.Geometry.Mesh mesh, out VertexFormatBits vertexFormatBits)
    {
      int verticesCount = mesh.Vertices.Count;
      int normalCount = mesh.Normals.Count;
      int colorsCount = mesh.VertexColors.Count;
      bool hasVertices = verticesCount > 0;
      bool hasNormals = normalCount == verticesCount;
      bool hasColors = colorsCount == verticesCount;
      int floatCount = verticesCount + (hasNormals ? normalCount : 0) + (hasColors ? normalCount : 0);

      if (hasVertices)
      {
        var vertices = mesh.Vertices;
        if (hasNormals)
        {
          var normals = mesh.Normals;
          if (hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionNormalColored;
            var colors = mesh.VertexColors;
            var vb = new VertexBuffer(verticesCount * VertexPositionNormalColored.GetSizeInFloats());
            vb.Map(verticesCount * VertexPositionNormalColored.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPositionNormalColored())
            {
              for (int v = 0; v < verticesCount; ++v)
              {
                var c = colors[v];
                stream.AddVertex(new VertexPositionNormalColored(vertices[v].ToHost(), normals[v].ToHost(), new ColorWithTransparency(c.R, c.G, c.B, 255u - c.A)));
              }
            }
            vb.Unmap();
            return vb;
          }
          else
          {
            vertexFormatBits = VertexFormatBits.PositionNormal;
            var vb = new VertexBuffer(verticesCount * VertexPositionNormal.GetSizeInFloats());
            vb.Map(verticesCount * VertexPositionNormal.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPositionNormal())
            {
              for (int v = 0; v < verticesCount; ++v)
                stream.AddVertex(new VertexPositionNormal(vertices[v].ToHost(), normals[v].ToHost()));
            }
            vb.Unmap();
            return vb;
          }
        }
        else
        {
          if (hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionColored;
            var colors = mesh.VertexColors;
            var vb = new VertexBuffer(verticesCount * VertexPositionColored.GetSizeInFloats());
            vb.Map(verticesCount * VertexPositionColored.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPositionColored())
            {
              for (int v = 0; v < verticesCount; ++v)
              {
                var c = colors[v];
                stream.AddVertex(new VertexPositionColored(vertices[v].ToHost(), new ColorWithTransparency(c.R, c.G, c.B, 255u - c.A)));
              }
            }
            vb.Unmap();
            return vb;
          }
          else
          {
            vertexFormatBits = VertexFormatBits.Position;
            var vb = new VertexBuffer(verticesCount * VertexPosition.GetSizeInFloats());
            vb.Map(verticesCount * VertexPosition.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPosition())
            {
              for (int v = 0; v < verticesCount; ++v)
                stream.AddVertex(new VertexPosition(vertices[v].ToHost()));
            }
            vb.Unmap();
            return vb;
          }
        }
      }

      vertexFormatBits = 0;
      return null;
    }

    protected static IndexBuffer ToLinesBuffer(Rhino.Geometry.Mesh mesh, out int linesCount)
    {
      linesCount = (mesh.Faces.Count * 3) + mesh.Faces.QuadCount;
      if (linesCount > 0)
      {
        var ib = new IndexBuffer(linesCount * 2);

        ib.Map(linesCount * 2);
        using (var istream = ib.GetIndexStreamLine())
        {
          foreach (var face in mesh.Faces)
          {
            istream.AddLine(new IndexLine(face.A, face.B));
            istream.AddLine(new IndexLine(face.B, face.C));
            istream.AddLine(new IndexLine(face.C, face.D));
            if (face.IsQuad)
              istream.AddLine(new IndexLine(face.D, face.A));
          }
        }

        ib.Unmap();
        return ib;
      }

      return null;
    }

    protected static IndexBuffer ToTrianglesBuffer(Rhino.Geometry.Mesh mesh, out int triangleCount)
    {
      triangleCount = mesh.Faces.Count + mesh.Faces.QuadCount;
      if (triangleCount > 0)
      {
        var ib = new IndexBuffer(triangleCount * 3);

        ib.Map(triangleCount * 3);
        using (var istream = ib.GetIndexStreamTriangle())
        {
          foreach (var face in mesh.Faces)
          {
            istream.AddTriangle(new IndexTriangle(face.A, face.B, face.C));
            if (face.IsQuad)
              istream.AddTriangle(new IndexTriangle(face.C, face.D, face.A));
          }
        }

        ib.Unmap();
        return ib;
      }

      return null;
    }

    #region Primitive
    protected class Primitive : IDisposable
    {
      VertexFormatBits vertexFormatBits;
      VertexBuffer vertexBuffer;
      int vertexCount;
      IndexBuffer triangleBuffer;
      int triangleCount;
      VertexFormat vertexFormat;
      EffectInstance effectInstance;
      Rhino.Geometry.Mesh mesh;
      System.Drawing.Color color;

      public Primitive(Rhino.Geometry.Mesh m, System.Drawing.Color c)
      {
        mesh = m;
        color = c;
      }

      void IDisposable.Dispose()
      {
        effectInstance?.Dispose(); effectInstance = null;
        vertexFormat?.Dispose(); vertexFormat = null;
        triangleBuffer?.Dispose(); triangleBuffer = null; triangleCount = 0;
        vertexBuffer?.Dispose(); vertexBuffer = null; vertexCount = 0;
      }

      public void Draw(Autodesk.Revit.DB.View dBView, DisplayStyle displayStyle)
      {
        // TODO : Use dBView.CropBox to check if the object is visible

        if (vertexBuffer == null)
        {
          vertexBuffer = ToVertexBuffer(mesh, out vertexFormatBits);
          vertexCount = mesh.Vertices.Count;
          triangleBuffer = ToTrianglesBuffer(mesh, out triangleCount);
          vertexFormat = new VertexFormat(vertexFormatBits);
          effectInstance = new EffectInstance(vertexFormatBits);
          effectInstance.SetTransparency((255 - color.A) / 255.0);
          effectInstance.SetEmissiveColor(new Color(color.R, color.G, color.B));

          mesh = null;
        }

        DrawContext.FlushBuffer
        (
          vertexBuffer, vertexCount,
          triangleBuffer, triangleCount * 3,
          vertexFormat, effectInstance,
          PrimitiveType.TriangleList,
          0, triangleCount
        );
      }
    }
    #endregion
  }

  class DocumentPreviewServer : DirectContext3DServer
  {
    #region IExternalServer
    public override string GetName() => Rhino.RhinoApp.Name;
    public override string GetDescription() => Rhino.RhinoApp.Name + " document previews server";
    public override Guid GetServerId() => Rhino.RhinoApp.CurrentRhinoId;
    #endregion

    #region IDirectContext3DServer
    public override bool CanExecute(Autodesk.Revit.DB.View dBView) => RhinoDoc.ActiveDoc != null;

    public override Outline GetBoundingBox(Autodesk.Revit.DB.View dBView)
    {
      var bbox = RhinoDoc.ActiveDoc.Objects.BoundingBox;
      return new Outline(bbox.Min.ToHost(), bbox.Max.ToHost());
    }

    public override void RenderScene(Autodesk.Revit.DB.View dBView, DisplayStyle displayStyle)
    {
      try
      {
        DrawContext.SetWorldTransform(Transform.Identity.ScaleBasis(1.0 / Revit.ModelUnits));

        var activeDoc = RhinoDoc.ActiveDoc;
        foreach (var o in activeDoc.Objects)
        {
          var drawColor = o.Attributes.DrawColor(activeDoc);
          foreach (var m in o.GetMeshes(Rhino.Geometry.MeshType.Render))
          {
            using (var vb = ToVertexBuffer(m, out var vertexFormatBits))
            {
              using (var vf = new VertexFormat(vertexFormatBits))
              using (var ei = new EffectInstance(vertexFormatBits))
              {
                if (displayStyle >= DisplayStyle.Shading)
                {
                  using (var ib = ToTrianglesBuffer(m, out var triangleCount))
                  {
                    ei.SetDiffuseColor(drawColor.ToHost());

                    DrawContext.FlushBuffer
                    (
                      vb, m.Vertices.Count,
                      ib, triangleCount * 3,
                      vf, ei,
                      PrimitiveType.TriangleList,
                      0, triangleCount
                    );
                  }
                }
                else
                {
                  using (var ib = ToLinesBuffer(m, out var linesCount))
                  {
                    DrawContext.FlushBuffer
                    (
                      vb, m.Vertices.Count,
                      ib, linesCount * 2,
                      vf, ei,
                      PrimitiveType.LineList,
                      0, linesCount
                    );
                  }
                }
              }
            }
          }
        }
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
      }
    }
    #endregion
  }

  public class GrasshopperPreviewServer : DirectContext3DServer
  {
    GH_Document activeDefinition = null;
    List<Primitive> primitives = new List<Primitive>();
    Rhino.Geometry.BoundingBox primitivesBoundingBox = Rhino.Geometry.BoundingBox.Empty;

    public override void Register()
    {
      base.Register();
    }

    public override void Unregister()
    {
      Clear();
      base.Unregister();
    }

    public void Clear()
    {
      foreach (var buffer in primitives)
        ((IDisposable) buffer).Dispose();
      primitives.Clear();

      primitivesBoundingBox = Rhino.Geometry.BoundingBox.Empty;
    }

    public void DrawShadedMesh(Rhino.Geometry.Mesh mesh, System.Drawing.Color color)
    {
      primitives.Add(new Primitive(mesh, color));
    }

    #region IExternalServer
    public override string GetName() => "Grasshopper";
    public override string GetDescription() => "Grasshopper previews server";
    public override Guid GetServerId() => Grasshopper.Instances.GrasshopperPluginId;
    #endregion

    #region IDirectContext3DServer
    public override bool UseInTransparentPass(Autodesk.Revit.DB.View dBView) => true;

    public override bool CanExecute(Autodesk.Revit.DB.View dBView)
    {
      var definition = Grasshopper.Instances.ActiveCanvas?.Document;
      if (definition != activeDefinition)
      {
        if(activeDefinition != null)
          activeDefinition.SolutionEnd -= Document_SolutionEnd;

        Clear();
        activeDefinition = definition;

        if (activeDefinition != null)
          activeDefinition.SolutionEnd += Document_SolutionEnd;
      }

      return activeDefinition != null;
    }

    private void Document_SolutionEnd(object sender, GH_SolutionEventArgs e)
    {
      Clear();
      Revit.ActiveUIApplication.ActiveUIDocument?.RefreshActiveView();
    }

    void DrawParam(IGH_Param param, System.Drawing.Color color)
    {
      if (param.VolatileDataCount > 0)
      {
        foreach (var value in param.VolatileData.AllData(true))
        {
          //if (value is IGH_PreviewMeshData meshData)
          //{
          //  var meshes = meshData.GetPreviewMeshes();
          //  if (meshes != null)
          //  {
          //    foreach (var mesh in meshes ?? Enumerable.Empty<Rhino.Geometry.Mesh>())
          //      DrawShadedMesh(mesh, color);

          //    return;
          //  }
          //}

          // First check for IGH_PreviewData to discard no graphic elements like strings, doubles, vectors...
          if (value is IGH_PreviewData)
          {
            switch (value.ScriptVariable())
            {
              case Rhino.Geometry.Mesh mesh: DrawShadedMesh(mesh, color); break;
              case Rhino.Geometry.Brep brep:
                foreach (var m in Rhino.Geometry.Mesh.CreateFromBrep(brep, Rhino.Geometry.MeshingParameters.Default))
                  DrawShadedMesh(m, color);
                break;
            }
          }
        }
      }
    }

    Rhino.Geometry.BoundingBox DrawScene(Autodesk.Revit.DB.View dBView)
    {
      if (!primitivesBoundingBox.IsValid)
      {
        var previewColour = activeDefinition.PreviewColour;
        var previewColourSelected = activeDefinition.PreviewColourSelected;

        foreach (var obj in activeDefinition.Objects)
        {
          bool selected = obj.Attributes.Selected;

          if (obj is IGH_Component component)
          {
            if (component.IsPreviewCapable && !component.Locked && !component.Hidden)
            {
              primitivesBoundingBox = Rhino.Geometry.BoundingBox.Union(primitivesBoundingBox, component.ClippingBox);

              foreach (var param in component.Params.Output)
                DrawParam(param, selected ? previewColourSelected : previewColour);
            }
          }
          else if(obj is IGH_Param param)
          {
            if (!param.Locked)
            {
              if (param is IGH_PreviewObject previewObject)
              {
                primitivesBoundingBox = Rhino.Geometry.BoundingBox.Union(primitivesBoundingBox, previewObject.ClippingBox);

                if (previewObject.IsPreviewCapable && !previewObject.Hidden)
                  DrawParam(param, selected ? previewColourSelected : previewColour);
              }
            }
          }
        }
      }

      return primitivesBoundingBox;
    }

    public override Outline GetBoundingBox(Autodesk.Revit.DB.View dBView)
    {
      DrawScene(dBView);
      return new Outline(primitivesBoundingBox.Min.ToHost(), primitivesBoundingBox.Max.ToHost());
    }

    public override void RenderScene(Autodesk.Revit.DB.View dBView, DisplayStyle displayStyle)
    {
      if (!DrawContext.IsTransparentPass())
        return;

      try
      {
        DrawScene(dBView);

        DrawContext.SetWorldTransform(Transform.Identity.ScaleBasis(1.0 / Revit.ModelUnits));

        foreach (var primitive in primitives)
          primitive.Draw(dBView, displayStyle);
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
      }
    }
    #endregion
  }
}
