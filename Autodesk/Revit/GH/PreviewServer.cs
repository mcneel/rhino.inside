using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;

using Autodesk.Revit.DB;
using Autodesk.Revit.DB.DirectContext3D;
using Autodesk.Revit.DB.ExternalService;

using Grasshopper;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH
{
  public class PreviewServer : DirectContext3DServer
  {
    static GH_Document activeDefinition = null;
    List<ParamPrimitive> primitives = new List<ParamPrimitive>();
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

    #region IExternalServer
    public override string GetName() => "Grasshopper";
    public override string GetDescription() => "Grasshopper previews server";
    public override Guid GetServerId() => Instances.GrasshopperPluginId;
    #endregion

    #region IDirectContext3DServer
    public override bool UseInTransparentPass(View dBView) => ((activeDefinition?.PreviewMode ?? GH_PreviewMode.Disabled) == GH_PreviewMode.Shaded);

    public override bool CanExecute(View dBView)
    {
      var editor = Instances.DocumentEditor;
      var canvas = Instances.ActiveCanvas;
      var definition = canvas?.Document;

      if (definition != activeDefinition)
      {
        if (activeDefinition != null)
        {
          if (editor != null) editor.VisibleChanged       -= Editor_VisibleChanged;
          activeDefinition.SolutionEnd                    -= Document_SolutionEnd;
          activeDefinition.SettingsChanged                -= Document_SettingsChanged;
          GH_Document.DefaultSelectedPreviewColourChanged -= Document_DefaultPreviewColourChanged;
          GH_Document.DefaultPreviewColourChanged         -= Document_DefaultPreviewColourChanged;
        }

        Clear();
        activeDefinition = definition;

        if (activeDefinition != null)
        {
          GH_Document.DefaultPreviewColourChanged         += Document_DefaultPreviewColourChanged;
          GH_Document.DefaultSelectedPreviewColourChanged += Document_DefaultPreviewColourChanged;
          activeDefinition.SettingsChanged                += Document_SettingsChanged;
          activeDefinition.SolutionEnd                    += Document_SolutionEnd;
          if (editor != null) editor.VisibleChanged       += Editor_VisibleChanged;
        }
      }

      return
      activeDefinition != null &&
      ((definition?.PreviewMode ?? GH_PreviewMode.Disabled) != GH_PreviewMode.Disabled) &&
      (editor?.Visible ?? false);
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

    static void Document_DefaultPreviewColourChanged(System.Drawing.Color colour) { Revit.RefreshActiveView(); }

    void Document_SettingsChanged(object sender, GH_DocSettingsEventArgs e)
    {
      if (e.Kind == GH_DocumentSettings.Properties)
        Clear();

      Revit.RefreshActiveView();
    }

    void Document_SolutionEnd(object sender, GH_SolutionEventArgs e)
    {
      Clear();
      Revit.RefreshActiveView();
    }

    static void Editor_VisibleChanged(object sender, EventArgs e) => Revit.RefreshActiveView();

    protected class ParamPrimitive : Primitive
    {
      readonly IGH_Attributes attributes;
      public ParamPrimitive(IGH_Attributes a, Rhino.Geometry.Point p) : base(p) { attributes = a; }
      public ParamPrimitive(IGH_Attributes a, Rhino.Geometry.Curve c) : base(c) { attributes = a; }
      public ParamPrimitive(IGH_Attributes a, Rhino.Geometry.Mesh m) : base(m) { attributes = a; }

      public override EffectInstance EffectInstance(DisplayStyle displayStyle, bool IsShadingPass)
      {
        var ei = base.EffectInstance(displayStyle, IsShadingPass);
        var color = attributes.Selected ? activeDefinition.PreviewColourSelected : activeDefinition.PreviewColour;

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
        if (activeDefinition.PreviewFilter == GH_PreviewFilter.Selected && !attributes.Selected)
          return;

        base.Draw(displayStyle);
      }
    }

    void DrawParam(IGH_Param param, IGH_Attributes attributes)
    {
      if (param.VolatileDataCount > 0)
      {
        foreach (var value in param.VolatileData.AllData(true))
        {
          // First check for IGH_PreviewData to discard no graphic elements like strings, doubles, vectors...
          if (value is IGH_PreviewData)
          {
            switch (value.ScriptVariable())
            {
              case Rhino.Geometry.Point3d point:    primitives.Add(new ParamPrimitive(attributes, new Rhino.Geometry.Point(point))); break;
              case Rhino.Geometry.Line line:        primitives.Add(new ParamPrimitive(attributes, new Rhino.Geometry.LineCurve(line))); break;
              case Rhino.Geometry.Rectangle3d rect: primitives.Add(new ParamPrimitive(attributes, rect.ToNurbsCurve())); break;
              case Rhino.Geometry.Arc arc:          primitives.Add(new ParamPrimitive(attributes, new Rhino.Geometry.ArcCurve(arc))); break;
              case Rhino.Geometry.Circle circle:    primitives.Add(new ParamPrimitive(attributes, new Rhino.Geometry.ArcCurve(circle))); break;
              case Rhino.Geometry.Ellipse ellipse:  primitives.Add(new ParamPrimitive(attributes, ellipse.ToNurbsCurve())); break;
              case Rhino.Geometry.Curve curve:      primitives.Add(new ParamPrimitive(attributes, curve)); break;
              case Rhino.Geometry.Mesh mesh:        primitives.Add(new ParamPrimitive(attributes, mesh)); break;
              case Rhino.Geometry.Box box:          primitives.Add(new ParamPrimitive(attributes, Rhino.Geometry.Mesh.CreateFromBox(box, 1, 1, 1))); break;
              case Rhino.Geometry.Brep brep:
              {
                var previewMesh = new Rhino.Geometry.Mesh();
                previewMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, activeDefinition.PreviewCurrentMeshParameters()));
                //previewMesh.Weld(Rhino.RhinoMath.ToRadians(10.0));

                primitives.Add(new ParamPrimitive(attributes, previewMesh));
              }
              break;
            }
          }
        }
      }
    }

    Rhino.Geometry.BoundingBox DrawScene(View dBView)
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
                DrawParam(param, obj.Attributes);
            }
          }
          else if (obj is IGH_Param param)
          {
            if (!param.Locked)
            {
              if (param is IGH_PreviewObject previewObject)
              {
                primitivesBoundingBox = Rhino.Geometry.BoundingBox.Union(primitivesBoundingBox, previewObject.ClippingBox);

                if (previewObject.IsPreviewCapable && !previewObject.Hidden)
                  DrawParam(param, obj.Attributes);
              }
            }
          }
        }
      }

      return primitivesBoundingBox;
    }

    public override Outline GetBoundingBox(View dBView)
    {
      var bbox = activeDefinition.PreviewBoundingBox.Scale(1.0 / Revit.ModelUnits);
      return new Outline(bbox.Min.ToHost(), bbox.Max.ToHost());
    }

    public override void RenderScene(View dBView, DisplayStyle displayStyle)
    {
      try
      {
        DrawScene(dBView);

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
