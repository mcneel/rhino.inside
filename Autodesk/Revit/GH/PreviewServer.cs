using System;
using System.Diagnostics;
using System.Collections.Generic;

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
    public override bool UseInTransparentPass(Autodesk.Revit.DB.View dBView) => true;

    public override bool CanExecute(Autodesk.Revit.DB.View dBView)
    {
      var definition = Instances.ActiveCanvas?.Document;
      if (definition != activeDefinition)
      {
        if (activeDefinition != null)
          activeDefinition.SolutionEnd -= Document_SolutionEnd;

        Clear();
        activeDefinition = definition;

        if (activeDefinition != null)
          activeDefinition.SolutionEnd += Document_SolutionEnd;
      }

      return activeDefinition != null;
    }

    void Document_SolutionEnd(object sender, GH_SolutionEventArgs e)
    {
      Clear();
      Revit.RefreshActiveView();
    }

    protected class ParamPrimitive : Primitive
    {
      readonly IGH_Attributes attributes;
      public ParamPrimitive(IGH_Attributes a, Rhino.Geometry.Mesh m) : base(m) { attributes = a; }

      public override EffectInstance EffectInstance(DisplayStyle displayStyle)
      {
        var ei = base.EffectInstance(displayStyle);

        var color = attributes.Selected ? activeDefinition.PreviewColourSelected : activeDefinition.PreviewColour;
        ei.SetTransparency((255 - color.A) / 255.0);
        ei.SetEmissiveColor(new Color(color.R, color.G, color.B));

        return ei;
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
              case Rhino.Geometry.Mesh mesh: primitives.Add(new ParamPrimitive(attributes, mesh)); break;
              case Rhino.Geometry.Brep brep:
                foreach (var m in Rhino.Geometry.Mesh.CreateFromBrep(brep, Rhino.Geometry.MeshingParameters.Default))
                  primitives.Add(new ParamPrimitive(attributes, m));
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

    public override Outline GetBoundingBox(Autodesk.Revit.DB.View dBView)
    {
      var bbox = DrawScene(dBView).Scale(1.0 / Revit.ModelUnits);
      return new Outline(bbox.Min.ToHost(), bbox.Max.ToHost());
    }

    public override void RenderScene(Autodesk.Revit.DB.View dBView, DisplayStyle displayStyle)
    {
      if (!DrawContext.IsTransparentPass())
        return;

      try
      {
        DrawScene(dBView);

        DrawContext.SetWorldTransform(Transform.Identity.ScaleBasis(1.0 / Revit.ModelUnits));

        if (dBView.CropBoxActive)
        {
          var CropBox = new Rhino.Geometry.BoundingBox(dBView.CropBox.Min.ToRhino(), dBView.CropBox.Max.ToRhino());

          foreach (var primitive in primitives)
          {
            if (Rhino.Geometry.BoundingBox.Intersection(CropBox, primitive.ClippingBox.Scale(1.0 / Revit.ModelUnits)).IsValid)
              primitive.Draw(displayStyle);
          }
        }
        else
        {
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
