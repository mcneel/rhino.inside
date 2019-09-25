using System;
using System.Collections.Generic;
using System.Linq;
using Grasshopper.Kernel;

namespace RhinoInside.Revit
{
  public static partial class Extension
  {
    #region Grasshopper
    public static IGH_DocumentObject ConnectNewObject(this IGH_Param self, Guid componentGuid)
    {
      var document = self.OnPingDocument();
      if (document is null)
        return null;

      var obj = Grasshopper.Instances.ComponentServer.EmitObject(componentGuid) as IGH_ActiveObject;
      if (obj is null)
        return null;

      obj.CreateAttributes();
      if (Grasshopper.CentralSettings.CanvasFullNames)
      {
        var atts = new List<IGH_Attributes>();
        obj.Attributes.AppendToAttributeTree(atts);
        foreach (var att in atts)
          att.DocObject.NickName = att.DocObject.Name;
      }

      obj.NewInstanceGuid();
      obj.Attributes.Pivot = new System.Drawing.PointF();
      obj.Attributes.PerformLayout();

      if (obj is IGH_Param)
        obj.Attributes.Pivot = new System.Drawing.PointF(self.Attributes.Pivot.X + 120, self.Attributes.Pivot.Y - obj.Attributes.Bounds.Height / 2);
      else if (obj is IGH_Component)
        obj.Attributes.Pivot = new System.Drawing.PointF(self.Attributes.Pivot.X + 120, self.Attributes.Pivot.Y);

      obj.Attributes.ExpireLayout();

      document.AddObject(obj, false);
      document.UndoUtil.RecordAddObjectEvent($"Add {obj.Name}", obj);

      if (obj is IGH_Param param)
      {
        param.AddSource(self);
      }
      else if (obj is IGH_Component component)
      {
        var selfType = self.Type;
        foreach (var input in component.Params.Input.Where(i => typeof(GH.Types.IGH_ElementId).IsAssignableFrom(i.Type)))
        {
          if (input.GetType() == self.GetType() || input.Type.IsAssignableFrom(selfType))
          {
            input.AddSource(self);
            break;
          }
        }
      }

      return obj;
    }

    public static void Menu_AppendConnect(this IGH_Param param, System.Windows.Forms.ToolStripDropDown menu, EventHandler eventHandler)
    {
      if ((param.Kind == GH_ParamKind.floating || param.Kind == GH_ParamKind.output) && param.Recipients.Count == 0)
      {
        var components = new List<IGH_Component>();
        var paramType = param.Type;

        foreach (var proxy in Grasshopper.Instances.ComponentServer.ObjectProxies.Where(x => !x.Obsolete && x.Exposure != GH_Exposure.hidden && x.Exposure < GH_Exposure.tertiary))
        {
          if (typeof(IGH_Component).IsAssignableFrom(proxy.Type))
          {
            var obj = proxy.CreateInstance() as IGH_Component;
            foreach (var input in obj.Params.Input.Where(i => typeof(GH.Types.IGH_ElementId).IsAssignableFrom(i.Type)))
            {
              if (input.GetType() == param.GetType() || input.Type.IsAssignableFrom(paramType))
              {
                components.Add(obj);
                break;
              }
            }
          }
        }

        GH_DocumentObject.Menu_AppendSeparator(menu);
        var connect = GH_DocumentObject.Menu_AppendItem(menu, "Connect") as System.Windows.Forms.ToolStripMenuItem;

        var panedComponentId = new Guid("{59E0B89A-E487-49f8-BAB8-B5BAB16BE14C}");
        var panel = GH_DocumentObject.Menu_AppendItem(connect.DropDown, "Panel", eventHandler, Grasshopper.Instances.ComponentServer.EmitObjectIcon(panedComponentId));
        panel.Tag = panedComponentId;

        var picker = GH_DocumentObject.Menu_AppendItem(connect.DropDown, "Value Set Picker", eventHandler, Grasshopper.Instances.ComponentServer.EmitObjectIcon(GH.Parameters.ValueSetPicker.ComponentClassGuid));
        picker.Tag = GH.Parameters.ValueSetPicker.ComponentClassGuid;

        if (components.Count > 0)
        {
          GH_DocumentObject.Menu_AppendSeparator(connect.DropDown);
          var maxComponents = Grasshopper.CentralSettings.CanvasMaxSearchResults;
          maxComponents = Math.Min(maxComponents, 30);
          maxComponents = Math.Max(maxComponents, 3);

          int count = 0;
          foreach (var componentGroup in components.GroupBy(x => x.Exposure).OrderBy(x => x.Key))
          {
            foreach (var component in componentGroup.OrderBy(x => x.Category).OrderBy(x => x.SubCategory).OrderBy(x => x.Name))
            {
              var item = GH_DocumentObject.Menu_AppendItem(connect.DropDown, component.Name, eventHandler, component.Icon_24x24);
              item.Tag = component.ComponentGuid;

              if (count >= maxComponents)
                break;
            }

            if (count >= maxComponents)
              break;
          }
        }
      }
    }
    #endregion
  }
}
