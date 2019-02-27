using System;
using System.Diagnostics;
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Color = System.Drawing.Color;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.DB.DirectContext3D;
using Autodesk.Revit.UI;

using Rhino;
using Rhino.Geometry;
using Autodesk.Revit.DB.ExternalService;

namespace RhinoInside.Revit
{
  [Transaction(TransactionMode.Manual)]
  [Regeneration(RegenerationOption.Manual)]
  public class Sample6 : IExternalCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var thisAssembly = Assembly.GetExecutingAssembly();

      var buttonData = new PushButtonData
      (
        "cmdRhinoInsideSample6", "Sample 6",
        thisAssembly.Location,
        MethodBase.GetCurrentMethod().DeclaringType.FullName
      );

      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Toggle Rhino model preview visibility";
        pushButton.LargeImage = ImageBuilder.BuildImage("6");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://github.com/mcneel/rhino.inside/blob/master/Autodesk/Revit/README.md#sample-6"));
      }
    }

    public Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      ObjectPreviewServer.Toggle();
      return Result.Succeeded;
    }
  }

  class ObjectPreviewServer : DirectContext3DServer
  {
    static ObjectPreviewServer()
    {
      RhinoDoc.CloseDocument += RhinoDoc_CloseDocument;
      RhinoDoc.AddRhinoObject += RhinoDoc_AddRhinoObject;
      RhinoDoc.DeleteRhinoObject += RhinoDoc_DeleteRhinoObject;
      RhinoDoc.UndeleteRhinoObject += RhinoDoc_AddRhinoObject;
      RhinoDoc.ModifyObjectAttributes += RhinoDoc_ModifyObjectAttributes;
      RhinoDoc.LayerTableEvent += RhinoDoc_LayerTableEvent;
      RhinoDoc.MaterialTableEvent += RhinoDoc_MaterialTableEvent;
    }

    static void RhinoDoc_CloseDocument(object sender, DocumentEventArgs e)
    {
      if (e.Document == ActiveDocument)
        ActiveDocument = null;
    }

    static void RhinoDoc_AddRhinoObject(object sender, Rhino.DocObjects.RhinoObjectEventArgs e)
    {
      if (e.TheObject.Document == ActiveDocument && ObjectPrimitive.IsSupportedObject(e.TheObject, true))
      {
        Revit.EnqueueReadAction((doc, canceled) => new ObjectPreviewServer(e.TheObject).Register());
        Revit.RefreshActiveView();
      }
    }

    static void RhinoDoc_DeleteRhinoObject(object sender, Rhino.DocObjects.RhinoObjectEventArgs e)
    {
      if (e.TheObject.Document == ActiveDocument && ObjectPrimitive.IsSupportedObject(e.TheObject, false))
      {
        Revit.EnqueueReadAction((doc, canceled) => objectPreviews[e.TheObject.Id]?.Unregister());
        Revit.RefreshActiveView();
      }
    }

    static void RhinoDoc_ModifyObjectAttributes(object sender, Rhino.DocObjects.RhinoModifyObjectAttributesEventArgs e)
    {
      if (e.Document == ActiveDocument) Revit.RefreshActiveView();
    }

    static void RhinoDoc_MaterialTableEvent(object sender, Rhino.DocObjects.Tables.MaterialTableEventArgs e)
    {
      if (e.Document == ActiveDocument) Revit.RefreshActiveView();
    }

    static void RhinoDoc_LayerTableEvent(object sender, Rhino.DocObjects.Tables.LayerTableEventArgs e)
    {
      if (e.Document == ActiveDocument) Revit.RefreshActiveView();
    }

    static RhinoDoc document;
    public static RhinoDoc ActiveDocument
    {
      get { return document; }
      set
      {
        if(document != value)
        {
          if (document != null) Stop();
          document = value;
          if (value    != null) Start();
        }
      }
    }

    static public void Toggle()
    {
      ActiveDocument = ActiveDocument == null ? RhinoDoc.ActiveDoc : null;
    }

    static Dictionary<Guid, ObjectPreviewServer> objectPreviews;
    readonly Rhino.DocObjects.RhinoObject rhinoObject;
    ObjectPreviewServer(Rhino.DocObjects.RhinoObject o) { rhinoObject = o; }

    override public void Register()
    {
      objectPreviews.Add(rhinoObject.Id, this);
      base.Register();
    }

    override public void Unregister()
    {
      base.Unregister();
      objectPreviews.Remove(rhinoObject.Id);

      ClearPrimitives();
    }

    void ClearPrimitives()
    {
      foreach (var buffer in primitives ?? Enumerable.Empty<Primitive>())
        ((IDisposable) buffer).Dispose();

      primitives = null;
    }

    static void Start()
    {
      objectPreviews = new Dictionary<Guid, ObjectPreviewServer>();

      using (var service = ExternalServiceRegistry.GetService(ExternalServices.BuiltInExternalServices.DirectContext3DService) as MultiServerService)
      {
        var activeServerIds = service.GetActiveServerIds();
        foreach (var o in ActiveDocument.Objects)
        {
          if (!ObjectPrimitive.IsSupportedObject(o, true))
            continue;

          var preview = new ObjectPreviewServer(o);
          var serverId = preview.GetServerId();
          objectPreviews.Add(serverId, preview);
          service.AddServer(preview);
          activeServerIds.Add(serverId);
        }
        service.SetActiveServers(activeServerIds);
      }

      Revit.RefreshActiveView();
    }

    static void Stop()
    {
      using (var service = ExternalServiceRegistry.GetService(ExternalServices.BuiltInExternalServices.DirectContext3DService) as MultiServerService)
      {
        var activeServerIds = service.GetActiveServerIds();
        foreach (var preview in objectPreviews)
          activeServerIds.Remove(preview.Key);
        service.SetActiveServers(activeServerIds);

        foreach (var preview in objectPreviews)
        {
          service.RemoveServer(preview.Key);
          preview.Value.ClearPrimitives();
        }
      }

      objectPreviews = null;

      Revit.RefreshActiveView();
    }

    #region IExternalServer
    public override string GetName() => "Rhino object";
    public override string GetDescription() => "Rhino object preview.";
    public override Guid GetServerId() => rhinoObject.Id;
    #endregion

    #region IDirectContext3DServer
    public override bool UseInTransparentPass(View dBView) => rhinoObject.IsMeshable(MeshType.Render);

    bool collected = false;
    public override bool CanExecute(View dBView)
    {
      if (collected)
        return false;

      try
      {
        if (rhinoObject.Document != ActiveDocument)
          return false;
      }
      catch (Rhino.Runtime.DocumentCollectedException)
      {
        collected = true;
        return false;
      }

      if (!rhinoObject.Visible)
        return false;

      return true;
    }

    public override Outline GetBoundingBox(View dBView)
    {
      var bbox = rhinoObject.Geometry.GetBoundingBox(false);
      bbox = bbox.Scale(1.0 / Revit.ModelUnits);
      return new Outline(bbox.Min.ToHost(), bbox.Max.ToHost());
    }

    class ObjectPrimitive : Primitive
    {
      readonly Rhino.DocObjects.RhinoObject rhinoObject;
      public ObjectPrimitive(Rhino.DocObjects.RhinoObject o, Rhino.Geometry.Point p) : base(p) { rhinoObject = o; }
      public ObjectPrimitive(Rhino.DocObjects.RhinoObject o, Rhino.Geometry.PointCloud pc) : base(pc) { rhinoObject = o; }
      public ObjectPrimitive(Rhino.DocObjects.RhinoObject o, Rhino.Geometry.PointCloud pc, Part p) : base(pc, p) { rhinoObject = o; }
      public ObjectPrimitive(Rhino.DocObjects.RhinoObject o, Rhino.Geometry.Curve c) : base(c) { rhinoObject = o; }
      public ObjectPrimitive(Rhino.DocObjects.RhinoObject o, Rhino.Geometry.Mesh m) : base(m) { rhinoObject = o; }
      public ObjectPrimitive(Rhino.DocObjects.RhinoObject o, Rhino.Geometry.Mesh m, Part p) : base(m, p) { rhinoObject = o; }

      public static bool IsSupportedObject(Rhino.DocObjects.RhinoObject rhinoObject, bool add)
      {
        if (add && !rhinoObject.IsValid)
          return false;

        if (rhinoObject is Rhino.DocObjects.PointObject po)
          return !add || po.PointGeometry.IsValid;

        if (rhinoObject is Rhino.DocObjects.PointCloudObject pco)
          return !add || pco.PointCloudGeometry.Count > 0;

        if (rhinoObject is Rhino.DocObjects.CurveObject co)
          return !add || co.CurveGeometry.GetLength() > Revit.ShortCurveTolerance * Revit.ModelUnits;

        if (rhinoObject is Rhino.DocObjects.MeshObject mo)
          return !add || mo.MeshGeometry.Faces.Count > 0;

        if (rhinoObject is Rhino.DocObjects.BrepObject bo)
          return !add || bo.BrepGeometry.Faces.Count > 0;

        if (rhinoObject.IsMeshable(MeshType.Render))
          return true;

        return false;
      }

      public override EffectInstance EffectInstance(DisplayStyle displayStyle, bool IsShadingPass)
      {
        var ei = base.EffectInstance(displayStyle, IsShadingPass);

        bool hlr = displayStyle == DisplayStyle.HLR;
        bool flatColors = displayStyle == DisplayStyle.FlatColors || displayStyle <= DisplayStyle.HLR;
        bool useMaterials = displayStyle > DisplayStyle.HLR && displayStyle != DisplayStyle.FlatColors;
        bool useTextures = displayStyle > DisplayStyle.Rendering && displayStyle != DisplayStyle.FlatColors;

        var ambient      = Color.Black;
        var color        = Color.Black;
        var diffuse      = Color.Black;
        var emissive     = Color.Black;
        var glossiness   = 1.0;
        var specular     = Color.Black;
        var transparency = 0.0;

        if (IsShadingPass)
        {
          if (DrawContext.IsTransparentPass())
          {
            transparency = displayStyle == DisplayStyle.Wireframe ? 0.8 : 0.5;
            var previewColor = Color.Silver;
            if (flatColors) emissive = previewColor;
            else
            {
              diffuse = previewColor;
              ambient = Color.FromArgb(diffuse.R / 2, diffuse.G / 2, diffuse.B / 2);
              if (useTextures)
              {
                glossiness = 0.5;
                specular = Color.White;
              }
            }
          }
          else
          {
            var drawColor = rhinoObject.IsLocked ?
            Rhino.ApplicationSettings.AppearanceSettings.LockedObjectColor :
            hlr ?
            Color.White :
            useMaterials ?
            Rhino.DocObjects.Material.DefaultMaterial.DiffuseColor :
            rhinoObject.Attributes.DrawColor(ActiveDocument);

            if (drawColor == Color.Black)
              drawColor = Color.Gray;

            if (displayStyle >= DisplayStyle.HLR)
            {
              if (flatColors) emissive = drawColor;
              else
              {
                var material = rhinoObject.GetMaterial(true);
                ambient = Color.FromArgb(material.DiffuseColor.R / 2, material.DiffuseColor.G / 2, material.DiffuseColor.B / 2);
                diffuse = material.DiffuseColor;
                emissive = material.EmissionColor;
                if (material.Shine != 0.0)
                {
                  double s = material.Shine / Rhino.DocObjects.Material.MaxShine;
                  double _s = 1.0 - s;
                  specular = Color.FromArgb
                  (
                    material.SpecularColor.A,
                    (int) (material.SpecularColor.R * s + material.DiffuseColor.R * _s),
                    (int) (material.SpecularColor.G * s + material.DiffuseColor.G * _s),
                    (int) (material.SpecularColor.B * s + material.DiffuseColor.B * _s)
                  );
                  glossiness = s;
                }

                transparency = material.Transparency;
              }
            }
          }
        }
        else
        {
          if(part.FaceCount == -1)
          {
            var previewColor = Color.Silver;
            diffuse = previewColor;
            ambient = Color.FromArgb(diffuse.R / 2, diffuse.G / 2, diffuse.B / 2);
            if (useTextures)
            {
              glossiness = 0.5;
              specular = Color.White;
            }
          }
        }

        ei.SetAmbientColor(ambient.ToHost());
        ei.SetColor(color.ToHost());
        ei.SetDiffuseColor(diffuse.ToHost());
        ei.SetEmissiveColor(emissive.ToHost());
        ei.SetGlossiness(glossiness * 100.0);
        ei.SetSpecularColor(specular.ToHost());
        ei.SetTransparency(transparency);

        return ei;
      }
    }

    Primitive[] primitives;
    const int VertexThreshold = ushort.MaxValue + 1;

    void AddPointCloudPreviews(Rhino.Geometry.PointCloud previewCloud)
    {
      int verticesCount = previewCloud.Count;
      if (verticesCount > VertexThreshold)
      {
        primitives = new Primitive[(verticesCount / VertexThreshold) + ((verticesCount % VertexThreshold) > 0 ? 1 : 0)];
        for (int c = 0; c < verticesCount / VertexThreshold; ++c)
        {
          var part = new Primitive.Part(c * VertexThreshold, (c + 1) * VertexThreshold);
          primitives[c] = new ObjectPrimitive(rhinoObject, previewCloud, part);
        }

        if ((verticesCount % VertexThreshold) > 0)
        {
          var part = new Primitive.Part((primitives.Length - 1) * VertexThreshold, verticesCount);
          primitives[primitives.Length - 1] = new ObjectPrimitive(rhinoObject, previewCloud, part);
        }
      }
      else primitives = new Primitive[] { new ObjectPrimitive(rhinoObject, previewCloud) };
    }

    void AddMeshPreviews(Rhino.Geometry.Mesh previewMesh)
    {
      int verticesCount = previewMesh.Vertices.Count;
      if (verticesCount > VertexThreshold || previewMesh.Faces.Count > VertexThreshold)
      {
        // If it's insane big show as point clouds
        if (previewMesh.Faces.Count > (VertexThreshold - 1) * 16)
        {
          primitives = new Primitive[(verticesCount / VertexThreshold) + ((verticesCount % VertexThreshold) > 0 ? 1 : 0)];
          for (int c = 0; c < verticesCount / VertexThreshold; ++c)
          {
            var part = new Primitive.Part(c * VertexThreshold, (c + 1) * VertexThreshold);
            primitives[c] = new ObjectPrimitive(rhinoObject, previewMesh, part);
          }

          if ((verticesCount % VertexThreshold) > 0)
          {
            var part = new Primitive.Part((primitives.Length - 1) * VertexThreshold, verticesCount);
            primitives[primitives.Length - 1] = new ObjectPrimitive(rhinoObject, previewMesh, part);
          }

          // Mesh.Reduce is slow in this case
          //previewMesh = previewMesh.DuplicateMesh();
          //previewMesh.Reduce((BigMeshThreshold - 1) * 16, true, 5, true);
        }

        // Split the mesh into partitions
        else if (previewMesh.CreatePartitions(VertexThreshold, int.MaxValue))
        {
          int partitionCount = previewMesh.PartitionCount;
          primitives = new Primitive[partitionCount];
          for (int p = 0; p < partitionCount; ++p)
            primitives[p] = new ObjectPrimitive(rhinoObject, previewMesh, previewMesh.GetPartition(p));
        }
      }
      else primitives = new Primitive[] { new ObjectPrimitive(rhinoObject, previewMesh) };
    }

    public override void RenderScene(View dBView, DisplayStyle displayStyle)
    {
      try
      {
        if (primitives == null)
        {
          if (rhinoObject is Rhino.DocObjects.PointObject pointObject)
          {
            primitives = new Primitive[] { new ObjectPrimitive(pointObject, pointObject.PointGeometry) };
          }
          else if (rhinoObject is Rhino.DocObjects.PointCloudObject pointCloudObject)
          {
            AddPointCloudPreviews(pointCloudObject.PointCloudGeometry);
          }
          else if (rhinoObject is Rhino.DocObjects.CurveObject curveObject)
          {
            primitives = new Primitive[] { new ObjectPrimitive(curveObject, curveObject.CurveGeometry) };
          }
          else if (rhinoObject is Rhino.DocObjects.MeshObject meshObject)
          {
            AddMeshPreviews(meshObject.MeshGeometry);
          }
          else if (rhinoObject.IsMeshable(MeshType.Render))
          {
            var meshingParameters = rhinoObject.GetRenderMeshParameters();
            if (rhinoObject.MeshCount(MeshType.Render, meshingParameters) == 0)
              rhinoObject.CreateMeshes(MeshType.Render, meshingParameters, false);

            var renderMeshes = rhinoObject.GetMeshes(MeshType.Render);
            if (renderMeshes?.Length > 0)
            {
              int vertexCount = renderMeshes.Select((x) => x.Vertices.Count).Sum();

              if (vertexCount > VertexThreshold)
              {
                foreach (var m in renderMeshes)
                  AddMeshPreviews(m);
              }
              else
              {
                var previewMesh = renderMeshes.Length == 1 ? renderMeshes[0] : null;
                if (previewMesh == null)
                {
                  previewMesh = new Rhino.Geometry.Mesh();
                  previewMesh.Append(renderMeshes);
                }

                AddMeshPreviews(previewMesh);
              }
            }
          }
        }

        if (primitives != null)
        {
          DrawContext.SetWorldTransform(Autodesk.Revit.DB.Transform.Identity.ScaleBasis(1.0 / Revit.ModelUnits));

          foreach (var primitive in primitives)
          {
            if (DrawContext.IsInterrupted())
              return;

            primitive.Draw(displayStyle);
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
}
