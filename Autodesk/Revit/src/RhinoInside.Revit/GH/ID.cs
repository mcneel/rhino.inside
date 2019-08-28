using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using Autodesk.Revit.DB;
using GH_IO.Serialization;
using Grasshopper.GUI;
using Grasshopper.GUI.Canvas;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Attributes;
using Grasshopper.Kernel.Data;
using Grasshopper.Kernel.Special;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public interface IElementId
  {
    bool IsReferencedElement { get; }
    string UniqueID { get; }
    bool IsElementLoaded { get; }
    bool LoadElement(Document doc);
    void UnloadElement();
  }

  public abstract class ID : GH_Goo<ElementId>, IEquatable<ID>, IElementId
  {
    public override string TypeName => "Revit Model Object";
    public override string TypeDescription => "Represents a Revit model object";
    public override bool IsValid => !(Value is null || Value == ElementId.InvalidElementId);
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();
    protected virtual Type ScriptVariableType => typeof(Autodesk.Revit.DB.ElementId);
    public static implicit operator ElementId(ID self) { return self.Value; }

    public static ID Make(ElementId Id)
    {
      if (Id == ElementId.InvalidElementId)
        return null;

      if (Id.IsCategoryId(Revit.ActiveDBDocument))
        return Category.Make(Id);

      return Element.Make(Id);
    }

    public static bool TryParseUniqueID(string s, out Guid guid, out int id)
    {
      guid = Guid.Empty;
      id = -1;
      if (s.Length == 0)
        return true;

      var index = s.LastIndexOf('-');
      if (index < 0)
        return false;

      return Guid.TryParseExact(s.Substring(0, index), "D", out guid) &&
             int.TryParse(s.Substring(index + 1), System.Globalization.NumberStyles.HexNumber, null, out id);
    }
    public static string FormatUniqueID(Guid guid, int index) => $"{guid:D}-{index,8:x}";

    public void SetValue(Document doc, ElementId id)
    {
      Value = id;
      UniqueID = doc?.GetElement(id)?.UniqueId ??
                 (
                   id.IntegerValue < ElementId.InvalidElementId.IntegerValue ?
                     FormatUniqueID(Guid.Empty, id.IntegerValue) : 
                     string.Empty
                 );
    }
    public void SetValue(Autodesk.Revit.DB.Element element)
    {
      Value = element?.Id;
      UniqueID = element?.UniqueId;
    }

    #region IElementId
    public bool IsReferencedElement => !string.IsNullOrEmpty(UniqueID);
    public string UniqueID { get; private set; }
    public bool IsElementLoaded => !(Value is null);
    public virtual bool LoadElement(Document doc)
    {
      try { Value = doc?.GetElement(UniqueID)?.Id; }
      catch (ArgumentNullException) { Value = null; }

      return IsElementLoaded;
    }

    public void UnloadElement() => Value = null;
    #endregion

    public ID() { Value = ElementId.InvalidElementId; UniqueID = string.Empty; }
    protected ID(ElementId id, string uniqueId) { Value = id; UniqueID = uniqueId; }
    protected ID(ElementId id) => SetValue(Revit.ActiveDBDocument, id);

    public override bool CastFrom(object source)
    {
      if (source is GH_Integer integer)
      {
        Value = new ElementId(integer.Value);
        UniqueID = string.Empty;
        return true;
      }
      if (source is ElementId id)
      {
        Value = id;
        UniqueID = string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.ElementId)))
      {
        target = (Q) (object) Value;
        return true;
      }
      if(typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
      {
        target = (Q) (object) new GH_Integer(Value.IntegerValue);
        return true;
      }
      if(typeof(Q).IsAssignableFrom(typeof(GH_String)))
      {
        target = (Q) (object) new GH_String(UniqueID);
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public bool Equals(ID id) => id?.Value.IntegerValue == Value.IntegerValue && id?.UniqueID == UniqueID;
    public override bool Equals(object obj) => (obj is ID id) ? Equals(id) : base.Equals(obj);
    public override int GetHashCode() => Value?.IntegerValue ?? 0;

    public override string ToString()
    {
      if (!IsValid)
        return $"Null {TypeName}";

      return $"{TypeName} : id {Value.IntegerValue}";
    }

    public override sealed bool Read(GH_IReader reader)
    {
      Value = null;
      UniqueID = reader.GetString("UniqueID");
      return true;
    }

    public override sealed bool Write(GH_IWriter writer)
    {
      writer.SetString("UniqueID", UniqueID);
      return true;
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public abstract class GH_ValueList : Grasshopper.Kernel.Special.GH_ValueList
  {
    protected override Bitmap Icon => ((Bitmap) Properties.Resources.ResourceManager.GetObject(GetType().Name)) ??
                                       ImageBuilder.BuildIcon(GetType().Name.Substring(0, 1));
  }

  public abstract class ValueList : GH_ValueList, IGH_InitCodeAware
  {
    public override GH_ParamData DataType => GH_ParamData.remote;
    public override GH_ParamKind Kind => GH_ParamKind.floating;

    void IGH_InitCodeAware.SetInitCode(string code) => NickName = code;

    public ValueList()
    {
      Category = "Revit";
      SubCategory = "Input";

      ObjectChanged += OnObjectChanged;

      ListMode = GH_ValueListMode.DropDown;
      ListItems.Clear();
    }

    private void OnObjectChanged(IGH_DocumentObject sender, GH_ObjectChangedEventArgs e)
    {
      if (SourceCount == 0)
      {
        if (e.Type == GH_ObjectEventType.Sources)
        {
          //NickName = string.Empty;
          MutableNickName = true;
        }

        if (e.Type == GH_ObjectEventType.NickName)
          ExpireSolution(true);
      }
      else
      {
        if (e.Type == GH_ObjectEventType.Sources)
        {
          NickName = string.Empty;
          MutableNickName = false;
        }
      }
    }

    class ValueListAttributes : GH_ValueListAttributes
    {
      public override bool HasInputGrip => true;
      public override bool AllowMessageBalloon => true;
      public ValueListAttributes(GH_ValueList owner) : base(owner) { }
      protected override void Render(GH_Canvas canvas, Graphics graphics, GH_CanvasChannel channel)
      {
        if (channel == GH_CanvasChannel.Wires)
        {
          if (Owner.SourceCount > 0)
            RenderIncomingWires(canvas.Painter, Owner.Sources, Owner.WireDisplay);
        }

        base.Render(canvas, graphics, channel);
      }
      public override GH_ObjectResponse RespondToMouseDoubleClick(GH_Canvas sender, GH_CanvasMouseEvent e)
      {
        if (Owner.MutableNickName && e.Button == MouseButtons.Left)
        {
          var objectMenu = new ContextMenuStrip();

          Owner.AppendMenuItems(objectMenu);
          if (objectMenu.Items.Count > 0)
          {
            sender.ActiveInteraction = null;
            objectMenu.Show(sender, e.ControlLocation);
          }

          return GH_ObjectResponse.Handled;
        }

        return GH_ObjectResponse.Ignore;
      }
    }

    public override void CreateAttributes() => m_attributes = new ValueListAttributes(this);

    protected abstract void RefreshList(string FamilyName);

    protected abstract void RefreshList(IEnumerable<IGH_Goo> goos);

    public override void PostProcessData()
    {
      base.PostProcessData();

      if (SourceCount == 0)
        RefreshList(NickName);
      else
        RefreshList(VolatileData.AllData(true));

      // Show elements sorted
      ListItems.Sort((x, y) => string.CompareOrdinal(x.Name, y.Name));

      //base.CollectVolatileData_Custom();
      m_data.Clear();

      var path = new GH_Path(0);
      if (SelectedItems.Count == 0)
        m_data.AppendRange(new IGH_Goo[0], path);
      else foreach (var item in SelectedItems)
          m_data.Append(item.Value, path);
    }

    protected override void CollectVolatileData_FromSources()
    {
      base.CollectVolatileData_FromSources();

      NickName = string.Empty;
    }

    protected override void CollectVolatileData_Custom()
    {
      NickName = NickName.Trim();
    }

    protected override string HtmlHelp_Source()
    {
      var nTopic = new Grasshopper.GUI.HTML.GH_HtmlFormatter(this)
      {
        Title = Name,
        Description =
        @"<p>Double click on it and use the name input box to enter a name, alternativelly you can enter a name patter. " +
        @"If a pattern is used, this param list will be filled up with all the objects that match it.</p>" +
        @"<p>Several kind of patterns are supported, the method used depends on the first pattern character:</p>" +
        @"<dl>" +
        @"<dt><b>></b></dt><dd>Starts with</dd>" +
        @"<dt><b><</b></dt><dd>Ends with</dd>" +
        @"<dt><b>?</b></dt><dd>Contains, same as a regular search</dd>" +
        @"<dt><b>:</b></dt><dd>Wildcards, see Microsoft.VisualBasic " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/visual-basic/language-reference/operators/like-operator#pattern-options\">LikeOperator</a></dd>" +
        @"<dt><b>;</b></dt><dd>Regular expresion, see " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference\">here</a> as reference</dd>" +
        @"</dl>",
        ContactURI = @"https://discourse.mcneel.com/c/serengeti/inside"
      };

      return nTopic.HtmlFormat();
    }
  }

  public abstract class ListParam : GH_PersistentParam<IGH_Goo>, IGH_InitCodeAware
  {
    public override GH_ParamKind Kind => GH_ParamKind.floating;
    public override string TypeName => "Data";

    void IGH_InitCodeAware.SetInitCode(string code) => NickName = code;

    public ListParam() : base(new GH_InstanceDescription("ValueListPicker", "", string.Empty, "Revit", "Input"))
    {
      ObjectChanged += OnObjectChanged;
    }

    protected override IGH_Goo InstantiateT() => new GH_ObjectWrapper();

    public class ListItem
    {
      public ListItem(IGH_Goo goo, bool selected = false)
      {
        Value = goo;
        Name = goo.ToString();
        Selected = selected;
      }

      public readonly IGH_Goo Value;
      public readonly string Name;
      public bool Selected;
      public RectangleF BoxName;
    }

    public List<ListItem> ListItems = new List<ListItem>();
    public IEnumerable<ListItem> SelectedItems => ListItems.Where(x => x.Selected);

    private void OnObjectChanged(IGH_DocumentObject sender, GH_ObjectChangedEventArgs e)
    {
      if (e.Type == GH_ObjectEventType.NickName)
        ExpireSolution(true);
    }

    public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
    {
      base.AppendAdditionalMenuItems(menu);
      Menu_AppendItem(menu, "Invert selection", Menu_InvertSelectionClicked, SourceCount > 0);
      Menu_AppendItem(menu, "Select all", Menu_SelectAllClicked, SourceCount > 0);
    }

    protected override void Menu_AppendPromptOne(ToolStripDropDown menu) { }
    protected override void Menu_AppendPromptMore(ToolStripDropDown menu) { }

    protected override void Menu_AppendDestroyPersistent(ToolStripDropDown menu) =>
      Menu_AppendItem(menu, "Clear selection", Menu_DestroyPersistentData, PersistentDataCount > 0);

    private void Menu_DestroyPersistentData(object sender, EventArgs e)
    {
      if (PersistentDataCount == 0) return;

      RecordPersistentDataEvent("Clear selection");
      PersistentData.Clear();
      OnObjectChanged(GH_ObjectEventType.PersistentData);

      OnPingDocument()?.ClearReferenceTable();
      ExpireSolution(true);
    }

    protected override void Menu_AppendInternaliseData(ToolStripDropDown menu) =>
      Menu_AppendItem(menu, "Internalise selection", Menu_InternaliseDataClicked, SourceCount > 0);

    private void Menu_InternaliseDataClicked(object sender, EventArgs e)
    {
      if (SourceCount == 0) return;

      RecordUndoEvent("Internalise selection");

      RemoveAllSources();
      ExpireSolution(true);
    }

    protected override void Menu_AppendExtractParameter(ToolStripDropDown menu) { }

    protected void Menu_InvertSelectionClicked(object sender, EventArgs e)
    {
      RecordUndoEvent("Invert selection");

      foreach (var item in ListItems)
        item.Selected = !item.Selected;

      PersistentData.Clear();
      PersistentData.AppendRange(SelectedItems.Select(x => x.Value), new GH_Path(0));
      OnObjectChanged(GH_ObjectEventType.PersistentData);

      ExpireSolution(true);
    }

    protected void Menu_SelectAllClicked(object sender, EventArgs e)
    {
      RecordUndoEvent("Select all");

      foreach (var item in ListItems)
        item.Selected = true;

      PersistentData.Clear();
      PersistentData.AppendRange(SelectedItems.Select(x => x.Value), new GH_Path(0));
      OnObjectChanged(GH_ObjectEventType.PersistentData);

      ExpireSolution(true);
    }

    new class Attributes : GH_ResizableAttributes<ListParam>
    {
      public override bool HasInputGrip => true;
      public override bool HasOutputGrip => true;
      public override bool AllowMessageBalloon => true;
      protected override Padding SizingBorders => new Padding(4, 6, 4, 6);
      protected override Size MinimumSize => new Size(50, 25 + 18 * 5);

      public Attributes(ListParam owner) : base(owner) { }
      protected override void Layout()
      {
        if (MaximumSize.Width < Bounds.Width || Bounds.Width < MinimumSize.Width)
          Bounds = new RectangleF(Bounds.Location, new SizeF(Bounds.Width < MinimumSize.Width ? MinimumSize.Width : MaximumSize.Width, Bounds.Height));
        if (MaximumSize.Height < Bounds.Height || Bounds.Height < MinimumSize.Height)
          Bounds = new RectangleF(Bounds.Location, new SizeF(Bounds.Width, Bounds.Height < MinimumSize.Height ? MinimumSize.Height : MaximumSize.Height));

        var itemBounds = new RectangleF(Bounds.X + 2, Bounds.Y + 20, Bounds.Width - 4, 18);

        for (int i = 0; i < Owner.ListItems.Count; i++)
        {
          Owner.ListItems[i].BoxName = itemBounds;
          itemBounds = new RectangleF(itemBounds.X, itemBounds.Y + itemBounds.Height, itemBounds.Width, itemBounds.Height);
        }

        base.Layout();
      }

      const int CaptionHeight = 20;
      const int ItemHeight = 18;
      const int FootnoteHeight = 18;
      const int ScrollerWidth = 8;

      float ScrollRatio = 0.0f;

      float Scrolling = float.NaN;
      float ScrollingY = float.NaN;

      int LastItemIndex = 0;

      protected override void Render(GH_Canvas canvas, Graphics graphics, GH_CanvasChannel channel)
      {
        switch (channel)
        {
          case GH_CanvasChannel.Wires:
          {
            if (Owner.SourceCount > 0)
              RenderIncomingWires(canvas.Painter, Owner.Sources, Owner.WireDisplay);
            break;
          }
          case GH_CanvasChannel.Objects:
          {
            var palette = GH_CapsuleRenderEngine.GetImpliedPalette(Owner);
            using (var capsule = GH_Capsule.CreateCapsule(Bounds, palette))
            {
              capsule.AddInputGrip(InputGrip.Y);
              capsule.AddOutputGrip(OutputGrip.Y);
              capsule.Render(canvas.Graphics, Selected, Owner.Locked, false);
            }

            var bounds = Bounds;
            if (!canvas.Viewport.IsVisible(ref bounds, 10))
              return;

            var alpha = GH_Canvas.ZoomFadeLow;
            if (alpha > 0)
            {
              canvas.SetSmartTextRenderingHint();
              var style = GH_CapsuleRenderEngine.GetImpliedStyle(palette, this);
              var textColor = System.Drawing.Color.FromArgb(alpha, style.Text);

              var captionColor = string.IsNullOrEmpty(Owner.NickName) || !Owner.MutableNickName ?
                                 System.Drawing.Color.FromArgb(alpha / 2, style.Text) : textColor;

              using (var nameFill = new SolidBrush(captionColor))
                graphics.DrawString(string.IsNullOrEmpty(Owner.NickName) ? "Filter mask…" : Owner.NickName, GH_FontServer.LargeAdjusted, nameFill, Bounds, GH_TextRenderingConstants.StringFormat(StringAlignment.Center, StringAlignment.Near));

              {
                var clip = ListBounds;
                clip.Inflate(-2, 0);

                Brush alternateBrush = null;
                if (GH_Canvas.ZoomFadeMedium > 0 && Owner.DataType == GH_ParamData.remote)
                {
                  graphics.FillRectangle(Brushes.White, clip);
                  alternateBrush = Brushes.WhiteSmoke;
                }
                else
                {
                  alternateBrush = new SolidBrush(System.Drawing.Color.FromArgb(70, style.Fill));
                }

                graphics.SetClip(clip);

                var transform = graphics.Transform;
                if(!ScrollerBounds.IsEmpty)
                  graphics.TranslateTransform(0.0f, -((Owner.ListItems.Count * ItemHeight) - clip.Height) * ScrollRatio);

                var format = new StringFormat(StringFormatFlags.NoWrap)
                {
                  LineAlignment = StringAlignment.Center
                };

                var itemBounds = new System.Drawing.Rectangle((int) clip.X, (int) clip.Y, (int) clip.Width, (int) 18);
                int index = 0;
                foreach (var item in Owner.ListItems)
                {
                  if (index++ % 2 != 0)
                    graphics.FillRectangle(alternateBrush, itemBounds);

                  if (item.Selected)
                  {
                    if (Owner.DataType == GH_ParamData.remote && GH_Canvas.ZoomFadeMedium > 0)
                    {
                      var highlightBounds = itemBounds;
                      highlightBounds.Inflate(-1, -1);
                      GH_GraphicsUtil.RenderHighlightBox(graphics, highlightBounds, 2, true, true);
                    }

                    var markBounds = new RectangleF(itemBounds.X, itemBounds.Y, 22, itemBounds.Height);
                    RenderCheckMark(canvas, graphics, markBounds, textColor);
                  }

                  var nameBounds = new RectangleF(itemBounds.X + 22, itemBounds.Y, itemBounds.Width - 22, itemBounds.Height);
                  graphics.DrawString(item.Name, GH_FontServer.StandardAdjusted, Brushes.Black, nameBounds, format);
                  itemBounds.Y += itemBounds.Height;
                }

                graphics.Transform = transform;

                RenderScrollBar(canvas, graphics, style.Text);

                graphics.ResetClip();

                if (GH_Canvas.ZoomFadeMedium > 0 && Owner.DataType == GH_ParamData.remote)
                {
                  graphics.DrawRectangle(Pens.Black, clip);
                  GH_GraphicsUtil.ShadowHorizontal(graphics, clip.Left, clip.Right, clip.Top);
                }
                else
                {
                  GH_GraphicsUtil.EtchFadingHorizontal(graphics, (int) bounds.Left, (int) bounds.Right, (int) (bounds.Top + 20), (int) (0.8 * alpha), (int) (0.3 * alpha));
                  GH_GraphicsUtil.EtchFadingHorizontal(graphics, (int) bounds.Left, (int) bounds.Right, (int) (bounds.Bottom - 16), (int) (0.8 * alpha), (int) (0.3 * alpha));
                }

                var footnoteBounds = new RectangleF(bounds.Left, bounds.Bottom - 17, bounds.Width - 3, 17);
                graphics.DrawString($"{Owner.ListItems.Count} items, {Owner.VolatileDataCount} selected.", GH_FontServer.StandardAdjusted, Brushes.Gray, footnoteBounds, GH_TextRenderingConstants.FarCenter);
              }
            }

            return;
          }
        }

        base.Render(canvas, graphics, channel);
      }

      void RenderCheckMark(GH_Canvas canvas, Graphics graphics, RectangleF bounds, System.Drawing.Color color)
      {
        var x = (int) (bounds.X + 0.5F * bounds.Width) - 2;
        var y = (int) (bounds.Y + 0.5F * bounds.Height);
        var corners = new PointF[]
        {
          new PointF(x, y),
          new PointF(x - 3.5F, y - 3.5F),
          new PointF(x - 6.5F, y - 0.5F),
          new PointF(x, y + 6.0F),
          new PointF(x + 9.5F, y - 3.5F),
          new PointF(x + 6.5F, y - 6.5F)
        };

        var edge = new Pen(color, 1.0F);
        edge.LineJoin = System.Drawing.Drawing2D.LineJoin.Round;
        graphics.FillPolygon(new SolidBrush(System.Drawing.Color.FromArgb(150, color)), corners);
        graphics.DrawPolygon(edge, corners);

        //RenderShape(canvas, graphics, corners, color);
      }

      void RenderItemList(GH_Canvas canvas, Graphics graphics, RectangleF bounds)
      {
        bounds.Inflate(-2, -2);
        graphics.SetClip(bounds);

        graphics.ResetClip();
      }

      System.Drawing.Rectangle ListBounds => new System.Drawing.Rectangle
        (
          (int) Bounds.X + 2, (int) Bounds.Y + CaptionHeight,
          (int) Bounds.Width - 4, (int) Bounds.Height - CaptionHeight - FootnoteHeight
        );

      System.Drawing.Rectangle ScrollerBounds
      {
        get
        {
          var total = Owner.ListItems.Count * ItemHeight;
          if (total > 0)
          {
            var scrollerBounds = ListBounds;
            var factor = (double) scrollerBounds.Height / total;
            if (factor < 1.0)
            {
              var scrollSize = Math.Max((scrollerBounds.Height) * factor, ItemHeight);
              var position = ((scrollerBounds.Height - scrollSize) * ScrollRatio);
              return new System.Drawing.Rectangle
              (
                scrollerBounds.Right - ScrollerWidth - 2,
                scrollerBounds.Top + (int) Math.Round(position),
                ScrollerWidth,
                (int) Math.Round(scrollSize)
              );
            }
          }

          return System.Drawing.Rectangle.Empty;
        }
      }

      void RenderScrollBar(GH_Canvas canvas, Graphics graphics, System.Drawing.Color color)
      {
        var total = Owner.ListItems.Count * ItemHeight;
        if (total > 0)
        {
          var scrollerBounds = ScrollerBounds;
          if (!scrollerBounds.IsEmpty)
          {
            var pen = new Pen(System.Drawing.Color.FromArgb(100, color), ScrollerWidth)
            {
              StartCap = System.Drawing.Drawing2D.LineCap.Round,
              EndCap = System.Drawing.Drawing2D.LineCap.Round
            };

            var startPoint = new System.Drawing.Point(scrollerBounds.X + (scrollerBounds.Width / 2), scrollerBounds.Top + 5);
            var endPoint = new System.Drawing.Point(scrollerBounds.X + (scrollerBounds.Width / 2), scrollerBounds.Bottom - 5);

            graphics.DrawLine(pen, startPoint, endPoint);
          }
        }
      }

      public override GH_ObjectResponse RespondToMouseDown(GH_Canvas canvas, GH_CanvasMouseEvent e)
      {
        if (canvas.Viewport.Zoom >= GH_Viewport.ZoomDefault * 0.6f)
        {
          if (e.Button == MouseButtons.Left)
          {
            var clientBounds = new RectangleF(Bounds.X + SizingBorders.Left, Bounds.Y + SizingBorders.Top, Bounds.Width - SizingBorders.Horizontal, Bounds.Height - SizingBorders.Vertical);
            if (clientBounds.Contains(e.CanvasLocation))
            {
              var listBounds = new RectangleF(Bounds.X + 2, Bounds.Y + 20, Bounds.Width - 4, Bounds.Height - 38);
              if (listBounds.Contains(e.CanvasLocation))
              {
                var scrollerBounds = ScrollerBounds;
                var canvasLocation = new System.Drawing.Point((int) e.CanvasLocation.X, (int) e.CanvasLocation.Y);
                if (scrollerBounds.Contains(canvasLocation))
                {
                  ScrollingY = e.CanvasY;
                  Scrolling = ScrollRatio;
                  return GH_ObjectResponse.Handled;
                }
                else if (Owner.DataType == GH_ParamData.remote && canvas.Viewport.Zoom >= GH_Viewport.ZoomDefault * 0.8f)
                {
                  var scrolledCanvasLocation = e.CanvasLocation;
                  if(!ScrollerBounds.IsEmpty)
                    scrolledCanvasLocation.Y += ((Owner.ListItems.Count * ItemHeight) - ListBounds.Height) * ScrollRatio;

                  bool keepSelection = System.Windows.Input.Keyboard.IsKeyDown(System.Windows.Input.Key.LeftCtrl);
                  bool rangeSelection = System.Windows.Input.Keyboard.IsKeyDown(System.Windows.Input.Key.LeftShift);
                  int lastItemIndex = 0;

                  Owner.RecordUndoEvent("Change selection");

                  bool sel = LastItemIndex < Owner.ListItems.Count ? Owner.ListItems[LastItemIndex].Selected : false;
                  for (int i = 0; i < Owner.ListItems.Count; i++)
                  {
                    if (Owner.ListItems[i].BoxName.Contains(scrolledCanvasLocation))
                    {
                      Owner.ListItems[i].Selected ^= true;
                      lastItemIndex = i;
                    }
                    else if (!keepSelection)
                    {
                      Owner.ListItems[i].Selected = false;
                    }
                  }

                  if (rangeSelection)
                  {
                    int min = Math.Min(lastItemIndex, LastItemIndex);
                    int max = Math.Max(lastItemIndex, LastItemIndex);

                    for (int i = min; i <= max; i++)
                      Owner.ListItems[i].Selected = sel;
                  }

                  LastItemIndex = lastItemIndex;

                  Owner.PersistentData.Clear();
                  Owner.PersistentData.AppendRange(Owner.SelectedItems.Select(x => x.Value), new GH_Path(0));
                  Owner.OnObjectChanged(GH_ObjectEventType.PersistentData);

                  Owner.ExpireSolution(true);
                  return GH_ObjectResponse.Handled;
                }
              }
            }
          }
        }
        return base.RespondToMouseDown(canvas, e);
      }

      public override GH_ObjectResponse RespondToMouseUp(GH_Canvas sender, GH_CanvasMouseEvent e)
      {
        Scrolling = float.NaN;
        ScrollingY = float.NaN;

        return base.RespondToMouseUp(sender, e);
      }

      public override GH_ObjectResponse RespondToMouseMove(GH_Canvas sender, GH_CanvasMouseEvent e)
      {
        if (e.Button == MouseButtons.Left && !float.IsNaN(Scrolling))
        {
          var dy = e.CanvasY - ScrollingY;
          var ty = ListBounds.Height - ScrollerBounds.Height;
          var f = dy / ty;

          ScrollRatio = Math.Max(0.0f, Math.Min(Scrolling + f, 1.0f));

          ExpireLayout();
          sender.Refresh();
          return GH_ObjectResponse.Handled;
        }

        return base.RespondToMouseMove(sender, e);
      }

      public override GH_ObjectResponse RespondToMouseDoubleClick(GH_Canvas canvas, GH_CanvasMouseEvent e)
      {
        if (canvas.Viewport.Zoom >= GH_Viewport.ZoomDefault * 0.6f)
        {
          if (e.Button == MouseButtons.Left)
          {
            if (Owner.MutableNickName && e.CanvasLocation.Y < Bounds.Top + 20.0f)
            {
              var objectMenu = new ContextMenuStrip();

              Owner.AppendMenuItems(objectMenu);
              if (objectMenu.Items.Count > 0)
              {
                canvas.ActiveInteraction = null;
                objectMenu.Show(canvas, e.ControlLocation);
              }

              return GH_ObjectResponse.Handled;
            }

            if (Owner.DataType == GH_ParamData.remote && canvas.Viewport.Zoom >= GH_Viewport.ZoomDefault * 0.8f)
            {
              var listBounds = new RectangleF(ListBounds.X, ListBounds.Y, ListBounds.Width, ListBounds.Height);
              if (listBounds.Contains(e.CanvasLocation))
              {
                Owner.RecordUndoEvent("Change selection");

                Owner.PersistentData.Clear();
                Owner.PersistentData.AppendRange(Owner.ListItems.Select(x => x.Value), new GH_Path(0));
                Owner.OnObjectChanged(GH_ObjectEventType.PersistentData);

                Owner.ExpireSolution(true);
                return GH_ObjectResponse.Handled;
              }
            }
          }
        }

        return GH_ObjectResponse.Ignore;
      }
    }

    public override void CreateAttributes() => m_attributes = new Attributes(this);
    public override void AddedToDocument(GH_Document document)
    {
      if (NickName == Name)
        NickName = string.Empty;

      base.AddedToDocument(document);
    }

    protected override GH_GetterResult Prompt_Singular(ref IGH_Goo value) => GH_GetterResult.cancel;
    protected override GH_GetterResult Prompt_Plural(ref List<IGH_Goo> values) => GH_GetterResult.cancel;

    protected override void OnVolatileDataCollected()
    {


      //base.OnVolatileDataCollected();
    }

    public override void ClearData()
    {
      base.ClearData();

      foreach (var goo in PersistentData)
      {
             if (goo is Types.IElementId id)   id.UnloadElement();
        else if (goo is IGH_GeometricGoo geo)     geo.ClearCaches();
      }
    }

    public abstract void ProcessData();
    public override sealed void PostProcessData()
    {
      //if (DataType == GH_ParamData.local)
      {
        foreach (var branch in m_data.Branches)
        {
          for (int i = 0; i < branch.Count; i++)
          {
            var goo = branch[i];

            if (goo is Types.IElementId id && id.IsReferencedElement && !id.IsElementLoaded && !id.LoadElement(Revit.ActiveDBDocument))
            {
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"A referenced element could not be found in the Revit document.");
              branch[i] = null;
            }
            else if (goo is IGH_GeometricGoo geo && geo.IsReferencedGeometry && !geo.IsGeometryLoaded && !geo.LoadGeometry())
            {
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"A referenced {geo.TypeName} could not be found in the Rhino document.");
              branch[i] = null;
            }
          }
        }
      }

      ProcessData();

      // Show elements sorted Alphabetically
      ListItems.Sort((x, y) => string.CompareOrdinal(x.Name, y.Name));

      m_data.Clear();
      m_data.AppendRange(SelectedItems.Select(x => x.Value), new GH_Path(0));

      base.PostProcessData();
    }

    protected override string HtmlHelp_Source()
    {
      var nTopic = new Grasshopper.GUI.HTML.GH_HtmlFormatter(this)
      {
        Title = Name,
        Description =
        @"<p>Double click on it and use the name input box to enter a name, alternativelly you can enter a name patter. " +
        @"If a pattern is used, this param list will be filled up with all the objects that match it.</p>" +
        @"<p>Several kind of patterns are supported, the method used depends on the first pattern character:</p>" +
        @"<dl>" +
        @"<dt><b>></b></dt><dd>Starts with</dd>" +
        @"<dt><b><</b></dt><dd>Ends with</dd>" +
        @"<dt><b>?</b></dt><dd>Contains, same as a regular search</dd>" +
        @"<dt><b>:</b></dt><dd>Wildcards, see Microsoft.VisualBasic " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/visual-basic/language-reference/operators/like-operator#pattern-options\">LikeOperator</a></dd>" +
        @"<dt><b>;</b></dt><dd>Regular expresion, see " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference\">here</a> as reference</dd>" +
        @"</dl>",
        ContactURI = @"https://discourse.mcneel.com/c/serengeti/inside"
      };

      return nTopic.HtmlFormat();
    }

    public override bool Write(GH_IWriter writer)
    {
      if (!base.Write(writer))
        return false;

      return true;
    }

    public override bool Read(GH_IReader reader)
    {
      if (!base.Read(reader))
        return false;

      return true;
    }
  }

  public class ItemSetPicker : ListParam
  {
    public override Guid ComponentGuid => new Guid("AFB12752-3ACB-4ACF-8102-16982A69CDAE");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override Bitmap Icon => ((Bitmap) Properties.Resources.ResourceManager.GetObject(GetType().Name)) ??
                                     ImageBuilder.BuildIcon("*");

    public ItemSetPicker()
    {
      Name = "Item Set Picker";
      Description = "Provides an item picker";
    }

    class GooComparer : IEqualityComparer<IGH_Goo>
    {
      public static bool IsComparable(IGH_Goo goo)
      {
        return
        (goo is Types.ID id && id.IsReferencedElement) ||
        (goo is IGH_GeometricGoo geometry && geometry.IsReferencedGeometry) ||
        goo is IGH_QuickCast ||
        goo is GH_StructurePath ||
        goo is GH_Culture ||
        (
          goo.ScriptVariable() is object obj &&
          (
            obj is ValueType ||
            obj is IComparable
          )
        );
      }

      public bool Equals(IGH_Goo x, IGH_Goo y)
      {
        if (x is Types.IElementId idX && y is Types.IElementId idY)
          return idX.IsReferencedElement && idY.IsReferencedElement && idX.UniqueID == idY.UniqueID;

        if (x is IGH_GeometricGoo geoX && geoX.IsReferencedGeometry && y is IGH_GeometricGoo geoY && geoY.IsReferencedGeometry)
          return geoX.ReferenceID == geoY.ReferenceID;

        if (x is IGH_QuickCast qcX && y is IGH_QuickCast qcY)
          return qcX.QC_CompareTo(qcY) == 0;

        if (x is GH_StructurePath pathX && y is GH_StructurePath pathY)
          return pathX.Value.CompareTo(pathX.Value) == 0;

        if (x is GH_Culture cultureX && y is GH_Culture cultureY)
          return cultureX.Value.LCID == cultureY.Value.LCID;

        if (x.ScriptVariable() is object objX && y.ScriptVariable() is object objY)
        {
          if (objX is ValueType valueX && objY is ValueType valueY)
            return valueX.Equals(valueY);

          if (objX is IComparable comparableX && objY is IComparable comparableY)
            return comparableX.CompareTo(comparableY) == 0;
        }

        return false;
      }

      public int GetHashCode(IGH_Goo obj)
      {
        if (obj is Types.IElementId id)
          return id.UniqueID.GetHashCode();

        if (obj is IGH_GeometricGoo geo && geo.IsReferencedGeometry)
          return geo.ReferenceID.GetHashCode();

        if (obj is IGH_QuickCast qc)
          return qc.QC_Hash();

        if (obj is GH_StructurePath path)
          return path.Value.GetHashCode();

        if (obj is GH_Culture culture)
          return culture.Value.LCID;

        if (obj.ScriptVariable() is object o)
        {
          if (o is ValueType value)
            return value.GetHashCode();

          if(o is IComparable comparable)
            return comparable.GetHashCode();
        }

        return 0;
      }
    }

    public override void ProcessData()
    {
      int dataCount = VolatileDataCount;
      int nonComparableCount = 0;
      var goosSet = new HashSet<IGH_Goo>(VolatileData.AllData(false).
          Where(x =>
          {
            if (GooComparer.IsComparable(x))
              return true;

            nonComparableCount++;
            return false;
          })
          , new GooComparer());

      if (nonComparableCount > 0)
        AddRuntimeMessage(GH_RuntimeMessageLevel.Remark, $"{nonComparableCount} null or non comparable elements filtered.");

      var duplicatedCount = dataCount - nonComparableCount - goosSet.Count;
      if (duplicatedCount > 0)
        AddRuntimeMessage(GH_RuntimeMessageLevel.Remark, $"{duplicatedCount} duplicated elements filtered.");

      if (DataType == GH_ParamData.local)
      {
        ListItems = goosSet.Select(goo => new ListItem(goo, true)).
                    Where(x => string.IsNullOrEmpty(NickName) || x.Name.IsSymbolNameLike(NickName)).
                    ToList();
      }
      else if (DataType == GH_ParamData.remote)
      {
        var selectSet = new HashSet<IGH_Goo>(PersistentData.Where(x => GooComparer.IsComparable(x)), new GooComparer());
        ListItems = goosSet.Select(goo => new ListItem(goo, selectSet.Contains(goo))).
                    Where(x => string.IsNullOrEmpty(NickName) || x.Name.IsSymbolNameLike(NickName)).
                    ToList();
      }
      else
      {
        ListItems.Clear();
      }
    }

    protected override string HtmlHelp_Source()
    {
      var nTopic = new Grasshopper.GUI.HTML.GH_HtmlFormatter(this)
      {
        Title = Name,
        Description =
        @"<p>This component is a special interface object that allows for quick picking an item from a list.</p>" +
        @"<p>Double click on it and use the name input box to enter an exact name, alternativelly you can enter a name patter. " +
        @"If a pattern is used, this param list will be filled up with all the items that match it.</p>" +
        @"<p>Several kind of patterns are supported, the method used depends on the first pattern character:</p>" +
        @"<dl>" +
        @"<dt><b>></b></dt><dd>Starts with</dd>" +
        @"<dt><b><</b></dt><dd>Ends with</dd>" +
        @"<dt><b>?</b></dt><dd>Contains, same as a regular search</dd>" +
        @"<dt><b>:</b></dt><dd>Wildcards, see Microsoft.VisualBasic " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/visual-basic/language-reference/operators/like-operator#pattern-options\">LikeOperator</a></dd>" +
        @"<dt><b>;</b></dt><dd>Regular expresion, see " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference\">here</a> as reference</dd>" +
        @"</dl>",
        ContactURI = @"https://discourse.mcneel.com/c/serengeti/inside"
      };

      return nTopic.HtmlFormat();
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public interface IGH_PersistentElementComponent
  {
    bool NeedsToBeExpired(Autodesk.Revit.DB.Events.DocumentChangedEventArgs args);
  }

  public abstract class GH_Component : Grasshopper.Kernel.GH_Component
  {
    protected GH_Component(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    // Grasshopper default implementation has a bug, it checks inputs instead of outputs
    public override bool IsBakeCapable => Params?.Output.OfType<IGH_BakeAwareObject>().Where(x => x.IsBakeCapable).Any() ?? false;

    protected override Bitmap Icon => ((Bitmap) Properties.Resources.ResourceManager.GetObject(GetType().Name)) ??
                                      ImageBuilder.BuildIcon(IconTag);

    protected virtual string IconTag => GetType().Name.Substring(0, 1);
  }
}
