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
    GH.PreviewServer grasshopperPreviewServer;

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
        Sample6.CreateUI(ribbonPanel);
        ribbonPanel.AddSeparator();
        UI.APIDocsCommand.CreateUI(ribbonPanel);
      }

      // Register some events
      ApplicationUI.Idling += OnIdle;
      ApplicationUI.ControlledApplication.DocumentChanged += OnDocumentChanged;

      // Register GrasshopperPreviewServer
      grasshopperPreviewServer = new GH.PreviewServer();
      grasshopperPreviewServer.Register();

      return Result.Succeeded;
    }

    public Result OnShutdown(UIControlledApplication applicationUI)
    {
      // Unregister GrasshopperPreviewServer
      grasshopperPreviewServer?.Unregister();
      grasshopperPreviewServer = null;

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

    static bool pendingRefreshActiveView = false;
    public static void RefreshActiveView() { pendingRefreshActiveView = true; }

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

        // 3. Refresh Active View if necesary
        bool regenComplete = DirectContext3DServer.RegenComplete();
        if (pendingRefreshActiveView || !regenComplete || GH.PreviewServer.PreviewChanged())
        {
          pendingRefreshActiveView = false;

          var RefreshTime = new Stopwatch();
          RefreshTime.Start();
          ActiveUIApplication.ActiveUIDocument.RefreshActiveView();
          RefreshTime.Stop();
          DirectContext3DServer.RegenThreshold = Math.Min(RefreshTime.ElapsedMilliseconds, 200);
        }

        if (!regenComplete)
          args.SetRaiseWithoutDelay();
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

    public const int VertexThreshold = ushort.MaxValue + 1;

    static IndexBuffer indexPointsBuffer;
    static IndexBuffer IndexPointsBuffer(int pointsCount)
    {
      Debug.Assert(pointsCount <= VertexThreshold);

      if (indexPointsBuffer == null)
      {
        indexPointsBuffer = new IndexBuffer(VertexThreshold * IndexPoint.GetSizeInShortInts());
        indexPointsBuffer.Map(VertexThreshold * IndexPoint.GetSizeInShortInts());
        using (var istream = indexPointsBuffer.GetIndexStreamPoint())
        {
          for (int vi = 0; vi < VertexThreshold; ++vi)
            istream.AddPoint(new IndexPoint(vi));
        }
        indexPointsBuffer.Unmap();
      }

      Debug.Assert(indexPointsBuffer.IsValid());
      return indexPointsBuffer;
    }

    static IndexBuffer indexLinesBuffer;
    static IndexBuffer IndexLinesBuffer(int pointsCount)
    {
      Debug.Assert(pointsCount <= VertexThreshold);

      if (indexLinesBuffer == null)
      {
        indexLinesBuffer = new IndexBuffer(VertexThreshold * IndexLine.GetSizeInShortInts());
        indexLinesBuffer.Map(VertexThreshold * IndexLine.GetSizeInShortInts());
        using (var istream = indexLinesBuffer.GetIndexStreamLine())
        {
          for (int vi = 0; vi < VertexThreshold - 1; ++vi)
            istream.AddLine(new IndexLine(vi, vi + 1));
        }
        indexLinesBuffer.Unmap();
      }

      Debug.Assert(indexLinesBuffer.IsValid());
      return indexLinesBuffer;
    }

    protected static VertexBuffer ToVertexBuffer
    (
      Rhino.Geometry.Mesh mesh,
      Primitive.Part part,
      out VertexFormatBits vertexFormatBits,
      System.Drawing.Color color = default(System.Drawing.Color)
    )
    {
      int verticesCount = part.EndVertexIndex - part.StartVertexIndex;
      int normalCount = mesh.Normals.Count == mesh.Vertices.Count ? verticesCount : 0;
      int colorsCount = color.IsEmpty ? (mesh.VertexColors.Count == mesh.Vertices.Count ? verticesCount : 0) : verticesCount;

      bool hasVertices = verticesCount > 0;
      bool hasNormals  = normalCount > 0;
      bool hasColors   = colorsCount > 0;

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
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
              {
                var c = !color.IsEmpty ? color : colors[v];
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
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
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
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
              {
                var c = !color.IsEmpty ? color : colors[v];
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
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
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

    protected static IndexBuffer ToTrianglesBuffer
    (
      Rhino.Geometry.Mesh mesh, Primitive.Part part,
      out int triangleCount
      )
    {
      triangleCount = part.FaceCount;
      {
        var faces = mesh.Faces;
        for (int f = part.StartFaceIndex; f < part.EndFaceIndex; ++f)
        {
          if (faces[f].IsQuad)
            triangleCount++;
        }
      }

      if (triangleCount > 0)
      {
        var ib = new IndexBuffer(triangleCount * IndexTriangle.GetSizeInShortInts());
        ib.Map(triangleCount * IndexTriangle.GetSizeInShortInts());

        using (var istream = ib.GetIndexStreamTriangle())
        {
          var faces = mesh.Faces;
          for (int f = part.StartFaceIndex; f < part.EndFaceIndex; ++f)
          {
            var face = faces[f];

            istream.AddTriangle(new IndexTriangle(face.A - part.StartVertexIndex, face.B - part.StartVertexIndex, face.C - part.StartVertexIndex));
            if (face.IsQuad)
              istream.AddTriangle(new IndexTriangle(face.C - part.StartVertexIndex, face.D - part.StartVertexIndex, face.A - part.StartVertexIndex));
          }
        }

        ib.Unmap();
        return ib;
      }

      return null;
    }

    protected static IndexBuffer ToWireframeBuffer(Rhino.Geometry.Mesh mesh, out int linesCount)
    {
      linesCount = (mesh.Faces.Count * 3) + mesh.Faces.QuadCount;
      if (linesCount > 0)
      {
        var ib = new IndexBuffer(linesCount * IndexLine.GetSizeInShortInts());
        ib.Map(linesCount * IndexLine.GetSizeInShortInts());

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

    protected static IndexBuffer ToEdgeBuffer
    (
      Rhino.Geometry.Mesh mesh,
      Primitive.Part part,
      out int linesCount
    )
    {
      if (part.VertexCount != mesh.Vertices.Count)
      {
        if (part.VertexCount > 0)
        {
          linesCount = -part.VertexCount;
          return IndexPointsBuffer(part.VertexCount);
        }

        linesCount = 0;
      }
      else
      {
        var edgeIndices = new List<IndexPair>();
        if (mesh.Ngons.Count > 0)
        {
          foreach (var ngon in mesh.Ngons)
          {
            var boundary = ngon.BoundaryVertexIndexList();
            if ((boundary?.Length ?? 0) > 1)
            {
              for (int b = 0; b < boundary.Length - 1; ++b)
                edgeIndices.Add(new IndexPair((int) boundary[b], (int) boundary[b + 1]));

              edgeIndices.Add(new IndexPair((int) boundary[boundary.Length - 1], (int) boundary[0]));
            }
          }
        }
        else
        {
          var vertices = mesh.TopologyVertices;
          var edges = mesh.TopologyEdges;
          var edgeCount = edges.Count;
          for (int e = 0; e < edgeCount; ++e)
          {
            if (edges.IsEdgeUnwelded(e) || edges.GetConnectedFaces(e).Length < 2)
            {
              var pair = edges.GetTopologyVertices(e);
              pair.I = vertices.MeshVertexIndices(pair.I)[0];
              pair.J = vertices.MeshVertexIndices(pair.J)[0];
              edgeIndices.Add(pair);
            }
          }
        }

        linesCount = edgeIndices.Count;
        if (linesCount > 0)
        {
          var ib = new IndexBuffer(linesCount * IndexLine.GetSizeInShortInts());
          ib.Map(linesCount * IndexLine.GetSizeInShortInts());
          using (var istream = ib.GetIndexStreamLine())
          {
            foreach (var edge in edgeIndices)
            {
              Debug.Assert(0 <= edge.I && edge.I < part.VertexCount);
              Debug.Assert(0 <= edge.J && edge.J < part.VertexCount);
              istream.AddLine(new IndexLine(edge.I, edge.J));
            }
          }
          ib.Unmap();

          return ib;
        }
      }

      return null;
    }

    protected static int ToPolylineBuffer
    (
      Rhino.Geometry.Polyline polyline,
      out VertexFormatBits vertexFormatBits,
      out VertexBuffer vb, out int vertexCount,
      out IndexBuffer ib
    )
    {
      int linesCount = 0;

      if (polyline.SegmentCount > 0)
      {
        linesCount = polyline.SegmentCount;
        vertexCount = polyline.Count;

        vertexFormatBits = VertexFormatBits.Position;
        vb = new VertexBuffer(vertexCount * VertexPosition.GetSizeInFloats());
        vb.Map(vertexCount * VertexPosition.GetSizeInFloats());
        using (var vstream = vb.GetVertexStreamPosition())
        {
          foreach (var v in polyline)
            vstream.AddVertex(new VertexPosition(v.ToHost()));
        }
        vb.Unmap();

        ib = IndexLinesBuffer(vertexCount);
      }
      else
      {
        vertexFormatBits = 0;
        vb = null; vertexCount = 0;
        ib = null;
      }

      return linesCount;
    }

    protected static int ToPointsBuffer
    (
      Rhino.Geometry.Point point,
      out VertexFormatBits vertexFormatBits,
      out VertexBuffer vb, out int vertexCount,
      out IndexBuffer ib
    )
    {
      int pointsCount = 0;

      if (point.Location.IsValid)
      {
        pointsCount = 1;
        vertexCount = 1;

        vertexFormatBits = VertexFormatBits.Position;
        vb = new VertexBuffer(pointsCount * VertexPosition.GetSizeInFloats());
        vb.Map(pointsCount * VertexPosition.GetSizeInFloats());
        using (var vstream = vb.GetVertexStreamPosition())
        {
          vstream.AddVertex(new VertexPosition(point.Location.ToHost()));
        }
        vb.Unmap();

        ib = IndexPointsBuffer(pointsCount);
      }
      else
      {
        vertexFormatBits = 0;
        vb = null; vertexCount = 0;
        ib = null;
      }

      return pointsCount;
    }

    protected static int ToPointsBuffer
    (
      Rhino.Geometry.PointCloud pointCloud,
      Primitive.Part part,
      out VertexFormatBits vertexFormatBits,
      out VertexBuffer vb, out int vertexCount,
      out IndexBuffer ib
    )
    {
      int pointsCount = part.VertexCount;
      int normalCount = pointCloud.ContainsNormals ? pointsCount : 0;
      int colorsCount = pointCloud.ContainsColors  ? pointsCount : 0;

      bool hasPoints  = pointsCount > 0;
      bool hasNormals = normalCount == pointsCount;
      bool hasColors  = colorsCount == pointsCount;

      if (hasPoints)
      {
        if (hasNormals)
        {
          if(hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionNormalColored;
            vb = new VertexBuffer(pointsCount * VertexPositionNormalColored.GetSizeInFloats());
            vb.Map(pointsCount * VertexPositionNormalColored.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPositionNormalColored())
            {
              for(int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                var c = new ColorWithTransparency(point.Color.R, point.Color.G, point.Color.B, 255u - point.Color.A);
                vstream.AddVertex(new VertexPositionNormalColored(point.Location.ToHost(), point.Normal.ToHost(), c));
              }
            }

            vb.Unmap();
          }
          else
          {
            vertexFormatBits = VertexFormatBits.PositionNormal;
            vb = new VertexBuffer(pointsCount * VertexPositionNormal.GetSizeInFloats());
            vb.Map(pointsCount * VertexPositionNormal.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPositionNormal())
            {
              for (int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                vstream.AddVertex(new VertexPositionNormal(point.Location.ToHost(), point.Normal.ToHost()));
              }
            }

            vb.Unmap();
          }
        }
        else
        {
          if (hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionColored;
            vb = new VertexBuffer(pointsCount * VertexPositionColored.GetSizeInFloats());
            vb.Map(pointsCount * VertexPositionColored.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPositionColored())
            {
              for (int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                var c = new ColorWithTransparency(point.Color.R, point.Color.G, point.Color.B, 255u - point.Color.A);
                vstream.AddVertex(new VertexPositionColored(point.Location.ToHost(), c));
              }
            }

            vb.Unmap();
          }
          else
          {
            vertexFormatBits = VertexFormatBits.Position;
            vb = new VertexBuffer(pointsCount * VertexPosition.GetSizeInFloats());
            vb.Map(pointsCount * VertexPosition.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPosition())
            {
              for (int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                vstream.AddVertex(new VertexPosition(point.Location.ToHost()));
              }
            }

            vb.Unmap();
          }
        }

        ib = IndexPointsBuffer(pointsCount);
      }
      else
      {
        vertexFormatBits = 0;
        vb = null;
        ib = null;
      }

      vertexCount = pointsCount;
      return pointsCount;
    }

    #region Primitive
    protected class Primitive : IDisposable
    {
      protected VertexFormatBits vertexFormatBits;
      protected int vertexCount;
      protected VertexBuffer vertexBuffer;
      protected VertexFormat vertexFormat;

      protected int triangleCount;
      protected IndexBuffer triangleBuffer;

      protected int linesCount;
      protected IndexBuffer linesBuffer;

      protected EffectInstance effectInstance;
      protected Rhino.Geometry.GeometryBase geometry;
      public struct Part
      {
        public readonly int StartVertexIndex;
        public readonly int EndVertexIndex;
        public readonly int StartFaceIndex;
        public readonly int EndFaceIndex;

        public int VertexCount => EndVertexIndex - StartVertexIndex;
        public int FaceCount   => EndFaceIndex - StartFaceIndex;

        public Part(int startVertexIndex, int endVertexIndex, int startFaceIndex, int endFaceIndex)
        {
          StartVertexIndex = startVertexIndex;
          EndVertexIndex   = endVertexIndex;
          StartFaceIndex   = startFaceIndex;
          EndFaceIndex     = endFaceIndex;
        }

        public Part(int startVertexIndex, int endVertexIndex) : this(startVertexIndex, endVertexIndex, 0, -1) { }

        public static implicit operator Part(Rhino.Geometry.PointCloud pc)
        {
          return new Part(0, pc.Count);
        }
        public static implicit operator Part(Rhino.Geometry.Mesh m)
        {
          return new Part(0, m.Vertices.Count, 0, m.Faces.Count);
        }
        public static implicit operator Part(Rhino.Geometry.MeshPart p)
        {
          return new Part(p.StartVertexIndex, p.EndVertexIndex, p.StartFaceIndex, p.EndFaceIndex);
        }
      }
      protected Part part;

      public Rhino.Geometry.BoundingBox ClippingBox => geometry.GetBoundingBox(false);

      public Primitive(Rhino.Geometry.Point p)               { geometry = p; }
      public Primitive(Rhino.Geometry.PointCloud pc)         { geometry = pc; part = pc; }
      public Primitive(Rhino.Geometry.PointCloud pc, Part p) { geometry = pc; part = p; }
      public Primitive(Rhino.Geometry.Curve c)               { geometry = c; }
      public Primitive(Rhino.Geometry.Mesh m)                { geometry = m; part = m; }
      public Primitive(Rhino.Geometry.Mesh m, Part p)        { geometry = m; part = p; }

      void IDisposable.Dispose()
      {
        effectInstance?.Dispose(); effectInstance = null;
        if(linesBuffer != indexLinesBuffer && linesBuffer != indexPointsBuffer)
        linesBuffer?.Dispose();    linesBuffer = null; linesCount = 0;
        triangleBuffer?.Dispose(); triangleBuffer = null; triangleCount = 0;
        vertexFormat?.Dispose();   vertexFormat = null;
        vertexBuffer?.Dispose();   vertexBuffer = null; vertexCount = 0;
      }

      public virtual EffectInstance EffectInstance(DisplayStyle displayStyle, bool IsShadingPass)
      {
        if (effectInstance == null)
          effectInstance = new EffectInstance(vertexFormatBits);

        return effectInstance;
      }

      public virtual bool Regen()
      {
        if (geometry != null)
        {
          if (!BeginRegen())
            return false;

          if (geometry is Rhino.Geometry.Mesh mesh)
          {
            vertexBuffer = ToVertexBuffer(mesh, part, out vertexFormatBits);
            vertexCount = part.VertexCount;

            triangleBuffer = ToTrianglesBuffer(mesh, part, out triangleCount);
            linesBuffer = ToEdgeBuffer(mesh, part, out linesCount);
          }
          else if (geometry is Rhino.Geometry.Curve curve)
          {
            using (var polyline = curve.ToPolyline(Revit.VertexTolerance * Revit.ModelUnits, Revit.AngleTolerance, Revit.ShortCurveTolerance * Revit.ModelUnits, 0.0))
              linesCount = ToPolylineBuffer(polyline.ToPolyline(), out vertexFormatBits, out vertexBuffer, out vertexCount, out linesBuffer);
          }
          else if (geometry is Rhino.Geometry.Point point)
          {
            linesCount = -ToPointsBuffer(point, out vertexFormatBits, out vertexBuffer, out vertexCount, out linesBuffer);
          }
          else if (geometry is Rhino.Geometry.PointCloud pointCloud)
          {
            linesCount = -ToPointsBuffer(pointCloud, part, out vertexFormatBits, out vertexBuffer, out vertexCount, out linesBuffer);
          }

          vertexFormat = new VertexFormat(vertexFormatBits);
          geometry = null;

          EndRegen();
        }

        return true;
      }

      public virtual void Draw(DisplayStyle displayStyle)
      {
        if (!Regen())
          return;

        if (DrawContext.IsTransparentPass())
        {
          if (vertexCount > 0)
          {
            var ei = EffectInstance(displayStyle, true);

            if (triangleCount > 0)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                triangleBuffer, triangleCount * 3,
                vertexFormat, ei,
                PrimitiveType.TriangleList,
                0, triangleCount
              );
            }
            else if (linesBuffer != null)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                linesBuffer, vertexCount,
                vertexFormat, ei,
                PrimitiveType.PointList,
                0, vertexCount
              );
            }
          }
        }
        else
        {
          if (linesCount != 0)
          {
            if (triangleBuffer != null)
            {
              bool edges = displayStyle == DisplayStyle.Wireframe ||
                           displayStyle == DisplayStyle.HLR ||
                           displayStyle == DisplayStyle.ShadingWithEdges ||
                           displayStyle == DisplayStyle.FlatColors ||
                           displayStyle == DisplayStyle.RealisticWithEdges;

              if (!edges)
                return;
            }

            if (linesCount > 0)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                linesBuffer, linesCount * 2,
                vertexFormat, EffectInstance(displayStyle, false),
                PrimitiveType.LineList,
                0, linesCount
              );
            }
            else if(triangleCount == 0)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                linesBuffer, vertexCount,
                vertexFormat, EffectInstance(displayStyle, false),
                PrimitiveType.PointList,
                0, vertexCount
              );
            }
          }
        }
      }
    }

    static Stopwatch RegenTime = new Stopwatch();
    public static long RegenThreshold = 200;

    static bool BeginRegen()
    {
      if (RegenTime.ElapsedMilliseconds > RegenThreshold)
        return false;

      RegenTime.Start();
      return true;
    }
    static void EndRegen()
    {
      RegenTime.Stop();
    }

    public static bool RegenComplete()
    {
      var ms = RegenTime.ElapsedMilliseconds;
      RegenTime.Reset();
      return ms == 0;
    }
    #endregion
  }
}
