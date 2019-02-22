using System;
using System.Diagnostics;
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
      RhinoDoc.UndeleteRhinoObject += RhinoDoc_UndeleteRhinoObject;
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
      if (e.TheObject.Document == ActiveDocument && e.TheObject.IsMeshable(MeshType.Render))
      {
        Revit.EnqueueReadAction((doc, canceled) => new ObjectPreviewServer(e.TheObject).Register());
        Revit.RefreshActiveView();
      }
    }

    static void RhinoDoc_DeleteRhinoObject(object sender, Rhino.DocObjects.RhinoObjectEventArgs e)
    {
      if (e.TheObject.Document == ActiveDocument && e.TheObject.IsMeshable(MeshType.Render))
      {
        Revit.EnqueueReadAction((doc, canceled) => objectPreviews[e.TheObject.Id]?.Unregister());
        Revit.RefreshActiveView();
      }
    }
    private static void RhinoDoc_UndeleteRhinoObject(object sender, Rhino.DocObjects.RhinoObjectEventArgs e)
    {
      if (e.TheObject.Document == ActiveDocument && e.TheObject.IsMeshable(MeshType.Render))
      {
        Revit.EnqueueReadAction((doc, canceled) => new ObjectPreviewServer(e.TheObject).Register());
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
          if (value != null)    Start();

          document = value;
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

      foreach (var buffer in primitives ?? Enumerable.Empty<Primitive>())
        ((IDisposable) buffer).Dispose();

      primitives = null;
    }

    static void Start()
    {
      objectPreviews = new Dictionary<Guid, ObjectPreviewServer>();

      Revit.EnqueueReadAction
      (
        (doc, canceled) =>
        {
          foreach (var o in RhinoDoc.ActiveDoc.Objects)
            new ObjectPreviewServer(o).Register();
        }
      );

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
          service.RemoveServer(preview.Key);
      }

      Revit.RefreshActiveView();
    }

    #region IExternalServer
    public override string GetName() => "Rhino object";
    public override string GetDescription() => "Rhino object preview.";
    public override Guid GetServerId() => rhinoObject.Id;
    #endregion

    #region IDirectContext3DServer

    public override bool UseInTransparentPass(Autodesk.Revit.DB.View dBView) => !
    (
      dBView.DisplayStyle == DisplayStyle.Realistic ||
      dBView.DisplayStyle == DisplayStyle.Shading ||
      dBView.DisplayStyle == DisplayStyle.Rendering ||
      dBView.DisplayStyle == DisplayStyle.Raytrace
    );

    bool collected = false;
    public override bool CanExecute(Autodesk.Revit.DB.View dBView)
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

    public override Outline GetBoundingBox(Autodesk.Revit.DB.View dBView)
    {
      var bbox = rhinoObject.Geometry.GetBoundingBox(false);
      bbox = bbox.Scale(1.0 / Revit.ModelUnits);
      return new Outline(bbox.Min.ToHost(), bbox.Max.ToHost());
    }

    class ObjectPrimitive : Primitive
    {
      readonly Rhino.DocObjects.RhinoObject rhinoObject;
      public ObjectPrimitive(Rhino.DocObjects.RhinoObject o, Rhino.Geometry.Mesh m) : base(m) { rhinoObject = o; }

      public override EffectInstance EffectInstance(DisplayStyle displayStyle)
      {
        var ei = base.EffectInstance(displayStyle);

        var ambient = System.Drawing.Color.Black;
        var color = System.Drawing.Color.Black;
        var diffuse = System.Drawing.Color.Black;
        var emissive = System.Drawing.Color.Black;
        var glossiness = 1.0;
        var specular = System.Drawing.Color.Black;
        var transparency = 0.0;

        if (DrawContext.IsTransparentPass())
        {
          transparency = 0.2;
          if (displayStyle == DisplayStyle.FlatColors)
            emissive = rhinoObject.Attributes.DrawColor(ActiveDocument);
          else
            emissive = Rhino.ApplicationSettings.AppearanceSettings.LockedObjectColor;

          if (emissive == System.Drawing.Color.Black)
            emissive = System.Drawing.Color.Gray;
        }
        else
        {
          bool hlr = displayStyle == DisplayStyle.HLR;
          bool flatColors = displayStyle == DisplayStyle.FlatColors || displayStyle == DisplayStyle.HLR;
          bool realistic = displayStyle == DisplayStyle.Realistic || displayStyle == DisplayStyle.RealisticWithEdges;

          var drawColor = rhinoObject.IsLocked ?
          Rhino.ApplicationSettings.AppearanceSettings.LockedObjectColor :
          hlr ?
          System.Drawing.Color.White :
          realistic ?
          Rhino.DocObjects.Material.DefaultMaterial.DiffuseColor :
          rhinoObject.Attributes.DrawColor(ActiveDocument);

          if (drawColor == System.Drawing.Color.Black)
            drawColor = System.Drawing.Color.Gray;

          if (displayStyle >= DisplayStyle.HLR)
          {
            if (flatColors) emissive = drawColor;
            else
            {
              var material = ActiveDocument.Materials[rhinoObject.Attributes.MaterialIndex];
              ambient = System.Drawing.Color.FromArgb(material.DiffuseColor.R / 2, material.DiffuseColor.G / 2, material.DiffuseColor.B / 2);
              diffuse = material.DiffuseColor;
              emissive = material.EmissionColor;
              if (material.Shine != 0.0)
              {
                double s = material.Shine / Rhino.DocObjects.Material.MaxShine;
                double _s = 1.0 - s;
                specular = System.Drawing.Color.FromArgb
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

        ei.SetAmbientColor(ambient.ToHost());
        //ei.SetColor(color.ToHost());
        ei.SetDiffuseColor(diffuse.ToHost());
        ei.SetEmissiveColor(emissive.ToHost());
        ei.SetGlossiness(glossiness * 100.0);
        ei.SetSpecularColor(specular.ToHost());
        ei.SetTransparency(transparency);

        return ei;
      }

      protected VertexBuffer linesVertexBuffer;
      protected IndexBuffer linesBuffer;
      protected int linesCount = -1;

      protected static int ToLinesBuffer(Rhino.Geometry.Mesh mesh, out VertexBuffer vb, out IndexBuffer ib)
      {
        int linesCount = 0;
        vb = null;
        ib = null;

        var edges = mesh.GetNakedEdges();
        if (edges?.Length > 0)
        {
          foreach (var polyline in edges)
            linesCount += polyline.SegmentCount;

          vb = new VertexBuffer(linesCount * 2 * VertexPosition.GetSizeInFloats());
          vb.Map(linesCount * 2 * VertexPosition.GetSizeInFloats());

          ib = new IndexBuffer(linesCount * 2);
          ib.Map(linesCount * 2);

          int vi = 0;
          using (var vstream = vb.GetVertexStreamPosition())
          using (var istream = ib.GetIndexStreamLine())
          {
            foreach (var polyline in edges)
            {
              int segmentCount = polyline.SegmentCount;
              for (int s = 0; s < segmentCount; ++s)
              {
                var line = polyline.SegmentAt(s);
                vstream.AddVertex(new VertexPosition(line.From.ToHost()));
                vstream.AddVertex(new VertexPosition(line.To.ToHost()));
                istream.AddLine(new IndexLine(vi++, vi++));
              }
            }
          }

          vb.Unmap();
          ib.Unmap();
        }

        return linesCount;
      }

      public override void Regen()
      {
        base.Regen();

        linesVertexBuffer?.Dispose();
        linesBuffer?.Dispose();

        // TODO::
        //if(rhinoObject.Geometry is Rhino.Geometry.Brep brep)
        //{
        //  foreach (var face in brep.Faces)
        //    face.TrimAwareIsoCurve();
        //}

        linesCount = ToLinesBuffer(mesh, out linesVertexBuffer, out linesBuffer);

        if (linesCount == 0)
          linesBuffer = ToWireframeBuffer(mesh, out linesCount);
      }

      public override void Draw(DisplayStyle displayStyle)
      {
        if (DrawContext.IsTransparentPass())
        {
          if (linesCount < 0)
            Regen();

          bool noWires = displayStyle == DisplayStyle.Realistic || displayStyle == DisplayStyle.Shading || displayStyle == DisplayStyle.Rendering || displayStyle == DisplayStyle.Raytrace;
          if (!noWires && linesCount > 0)
          {
            using (var ei = new EffectInstance(VertexFormatBits.Position))
            {
              if (linesVertexBuffer != null)
              {
                using (var vf = new VertexFormat(VertexFormatBits.Position))
                {
                  DrawContext.FlushBuffer
                  (
                    linesVertexBuffer, linesCount * 2,
                    linesBuffer, linesCount * 2,
                    vf, ei,
                    PrimitiveType.LineList,
                    0, linesCount
                  );
                }
              }
              else
              {
                DrawContext.FlushBuffer
                (
                  vertexBuffer, vertexCount * 2,
                  linesBuffer, linesCount * 2,
                  vertexFormat, ei,
                  PrimitiveType.LineList,
                  0, linesCount
                );
              }
            }
          }
        }

        if (DrawContext.IsTransparentPass() || displayStyle >= DisplayStyle.HLR)
          base.Draw(displayStyle);
      }
    }

    Primitive[] primitives;

    public override void RenderScene(Autodesk.Revit.DB.View dBView, DisplayStyle displayStyle)
    {
      if (UseInTransparentPass(dBView) && !DrawContext.IsTransparentPass())
        return;

      try
      {
        if (primitives == null)
        {
          var renderMeshes = rhinoObject.GetMeshes(Rhino.Geometry.MeshType.Render);
          if(renderMeshes != null)
          {
            primitives = new Primitive[renderMeshes.Length];
            for (int m = 0; m < primitives.Length; ++m)
              primitives[m] = new ObjectPrimitive(rhinoObject, renderMeshes[m]);
          }
        }

        if (primitives != null)
        {
          DrawContext.SetWorldTransform(Autodesk.Revit.DB.Transform.Identity.ScaleBasis(1.0 / Revit.ModelUnits));

          foreach (var primitive in primitives)
            primitive.Draw(displayStyle);
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
