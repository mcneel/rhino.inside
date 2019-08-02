#if REVIT_2018
using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;

using Autodesk.Revit.DB;
using Autodesk.Revit.DB.DirectContext3D;
using Autodesk.Revit.DB.ExternalService;

using Grasshopper;
using Grasshopper.Kernel;
using System.Threading;

namespace RhinoInside.Revit.GH
{
  public class PreviewServer : DirectContext3DServer
  {
    static GH_Document activeDefinition = null;
    List<ParamPrimitive> primitives = new List<ParamPrimitive>();
    Rhino.Geometry.BoundingBox primitivesBoundingBox = Rhino.Geometry.BoundingBox.Empty;
    int RebuildPrimitives = 1;

    public static GH_PreviewMode PreviewMode = GH_PreviewMode.Shaded;

    #region IExternalServer
    public override string GetName() => "Grasshopper";
    public override string GetDescription() => "Grasshopper previews server";
    public override Guid GetServerId() => Instances.GrasshopperPluginId;
    #endregion

    #region IDirectContext3DServer
    public override bool UseInTransparentPass(View dBView) => ((activeDefinition != null ? PreviewMode : GH_PreviewMode.Disabled) == GH_PreviewMode.Shaded);

    public override bool CanExecute(View dBView)
    {
      var editor = Instances.DocumentEditor;
      var canvas = Instances.ActiveCanvas;
      var definition = canvas?.Document;

      if (definition != activeDefinition)
      {
        if (activeDefinition != null)
        {
          activeDefinition.SolutionEnd                    -= ActiveDefinition_SolutionEnd;
          activeDefinition.SettingsChanged                -= ActiveDefinition_SettingsChanged;
          GH_Document.DefaultSelectedPreviewColourChanged -= Document_DefaultPreviewColourChanged;
          GH_Document.DefaultPreviewColourChanged         -= Document_DefaultPreviewColourChanged;
        }

        RebuildPrimitives = 1;
        activeDefinition = definition;

        if (activeDefinition != null)
        {
          GH_Document.DefaultPreviewColourChanged         += Document_DefaultPreviewColourChanged;
          GH_Document.DefaultSelectedPreviewColourChanged += Document_DefaultPreviewColourChanged;
          activeDefinition.SettingsChanged                += ActiveDefinition_SettingsChanged;
          activeDefinition.SolutionEnd                    += ActiveDefinition_SolutionEnd;
        }
      }

      return
      PreviewMode != GH_PreviewMode.Disabled &&
      IsModelView(dBView) &&
      activeDefinition != null;
    }

    static List<IGH_DocumentObject> lastSelection = new List<IGH_DocumentObject>();
    public static bool PreviewChanged()
    {
      if (Instances.ActiveCanvas?.Document != activeDefinition)
        return true;

      if (activeDefinition != null)
      {
        var newSelection = activeDefinition.SelectedObjects();
        if (lastSelection.Count != newSelection.Count || lastSelection.Except(newSelection).Any())
        {
          lastSelection = newSelection;
          return true;
        }
      }

      return false;
    }

    static void Document_DefaultPreviewColourChanged(System.Drawing.Color colour) => Revit.RefreshActiveView();

    void ActiveDefinition_SettingsChanged(object sender, GH_DocSettingsEventArgs e)
    {
      if (e.Kind == GH_DocumentSettings.Properties)
        RebuildPrimitives = 1;

      Revit.RefreshActiveView();
    }

    void ActiveDefinition_SolutionEnd(object sender, GH_SolutionEventArgs e)
    {
      RebuildPrimitives = 1;
      Revit.RefreshActiveView();
    }

    protected class ParamPrimitive : Primitive
    {
      readonly IGH_DocumentObject docObject;
      public ParamPrimitive(IGH_DocumentObject o, Rhino.Geometry.Point p) : base(p) { docObject = o; o.ObjectChanged += ObjectChanged; }
      public ParamPrimitive(IGH_DocumentObject o, Rhino.Geometry.Curve c) : base(c) { docObject = o; o.ObjectChanged += ObjectChanged; }
      public ParamPrimitive(IGH_DocumentObject o, Rhino.Geometry.Mesh m)  : base(m) { docObject = o; o.ObjectChanged += ObjectChanged; }

      void ObjectChanged(IGH_DocumentObject sender, GH_ObjectChangedEventArgs e)
      {
        if (e.Type == GH_ObjectEventType.Preview)
          Revit.RefreshActiveView();
      }

      public override EffectInstance EffectInstance(DisplayStyle displayStyle, bool IsShadingPass)
      {
        var ei = base.EffectInstance(displayStyle, IsShadingPass);
        var color = docObject.Attributes.Selected ? activeDefinition.PreviewColourSelected : activeDefinition.PreviewColour;

        if (IsShadingPass)
        {
          ei.SetTransparency((255 - color.A) / 255.0);
          ei.SetEmissiveColor(new Color(color.R, color.G, color.B));
        }
        else ei.SetColor(new Color(color.R, color.G, color.B));

        return ei;
      }

      public override void Draw(DisplayStyle displayStyle)
      {
        if (docObject is IGH_PreviewObject preview)
        {
          if (preview.Hidden)
            return;
        }

        if (activeDefinition.PreviewFilter == GH_PreviewFilter.Selected && !docObject.Attributes.Selected)
          return;

        base.Draw(displayStyle);
      }
    }

    void DrawData(Grasshopper.Kernel.Data.IGH_Structure volatileData, IGH_DocumentObject docObject)
    {
      if (!volatileData.IsEmpty)
      {
        foreach (var value in volatileData.AllData(true))
        {
          // First check for IGH_PreviewData to discard no graphic elements like strings, doubles, vectors...
          if (value is IGH_PreviewData)
          {
            switch (value.ScriptVariable())
            {
              case Rhino.Geometry.Point3d point:    primitives.Add(new ParamPrimitive(docObject, new Rhino.Geometry.Point(point))); break;
              case Rhino.Geometry.Line line:        primitives.Add(new ParamPrimitive(docObject, new Rhino.Geometry.LineCurve(line))); break;
              case Rhino.Geometry.Rectangle3d rect: primitives.Add(new ParamPrimitive(docObject, rect.ToNurbsCurve())); break;
              case Rhino.Geometry.Arc arc:          primitives.Add(new ParamPrimitive(docObject, new Rhino.Geometry.ArcCurve(arc))); break;
              case Rhino.Geometry.Circle circle:    primitives.Add(new ParamPrimitive(docObject, new Rhino.Geometry.ArcCurve(circle))); break;
              case Rhino.Geometry.Ellipse ellipse:  primitives.Add(new ParamPrimitive(docObject, ellipse.ToNurbsCurve())); break;
              case Rhino.Geometry.Curve curve:      primitives.Add(new ParamPrimitive(docObject, curve)); break;
              case Rhino.Geometry.Mesh mesh:        primitives.Add(new ParamPrimitive(docObject, mesh)); break;
              case Rhino.Geometry.Box box:          primitives.Add(new ParamPrimitive(docObject, Rhino.Geometry.Mesh.CreateFromBox(box, 1, 1, 1))); break;
              case Rhino.Geometry.Brep brep:
              {
                var previewMesh = new Rhino.Geometry.Mesh();
                previewMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, activeDefinition.PreviewCurrentMeshParameters()));
                //previewMesh.Weld(Rhino.RhinoMath.ToRadians(10.0));

                primitives.Add(new ParamPrimitive(docObject, previewMesh));
              }
              break;
            }
          }
        }
      }
    }

    Rhino.Geometry.BoundingBox BuildScene(View dBView)
    {
      if (Interlocked.Exchange(ref RebuildPrimitives, 0) != 0)
      {
        primitivesBoundingBox = Rhino.Geometry.BoundingBox.Empty;

        // Dispose previous primitives
        {
          foreach (var primitive in primitives)
            ((IDisposable) primitive).Dispose();

          primitives.Clear();
        }

        var previewColour = activeDefinition.PreviewColour;
        var previewColourSelected = activeDefinition.PreviewColourSelected;

        foreach (var obj in activeDefinition.Objects.OfType<IGH_ActiveObject>())
        {
          if (obj.Locked)
            continue;

          if (obj is IGH_PreviewObject previewObject)
          {
            if (previewObject.IsPreviewCapable)
            {
              primitivesBoundingBox = Rhino.Geometry.BoundingBox.Union(primitivesBoundingBox, previewObject.ClippingBox);

              if (obj is IGH_Component component)
              {
                foreach (var param in component.Params.Output)
                  DrawData(param.VolatileData, obj);
              }
              else if (obj is IGH_Param param)
              {
                DrawData(param.VolatileData, obj);
              }
            }
          }
        }
      }

      return primitivesBoundingBox;
    }

    public override Outline GetBoundingBox(View dBView)
    {
      var bbox = primitivesBoundingBox.Scale(1.0 / Revit.ModelUnits);
      return new Outline(bbox.Min.ToHost(), bbox.Max.ToHost());
    }

    public override void RenderScene(View dBView, DisplayStyle displayStyle)
    {
      try
      {
        BuildScene(dBView);

        DrawContext.SetWorldTransform(Transform.Identity.ScaleBasis(1.0 / Revit.ModelUnits));

        var CropBox = new Rhino.Geometry.BoundingBox(dBView.CropBox.Min.ToRhino(), dBView.CropBox.Max.ToRhino()).Scale(Revit.ModelUnits);

        foreach (var primitive in primitives)
        {
          if (DrawContext.IsInterrupted())
            break;

          if (dBView.CropBoxActive && !Rhino.Geometry.BoundingBox.Intersection(CropBox, primitive.ClippingBox).IsValid)
            continue;

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
#else
namespace RhinoInside.Revit.GH
{
  public class PreviewServer
  {
    public void Register() { }

    public void Unregister() { }

    public static bool PreviewChanged() => false;
  }
}
#endif
