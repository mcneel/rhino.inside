using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Windows.Forms;

using GH_IO.Serialization;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Data;
using Grasshopper.Kernel.Types;
using Grasshopper.Kernel.Special;
using Grasshopper.GUI;
using Grasshopper.GUI.Canvas;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class ID : GH_Goo<ElementId>
  {
    public override string TypeName => "Revit Model Object";
    public override string TypeDescription => "Represents a Revit model object";
    public override bool IsValid => Value != null && Value != ElementId.InvalidElementId;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();
    protected virtual Type ScriptVariableType => typeof(Autodesk.Revit.DB.ElementId);
    public static implicit operator ElementId(ID self) { return self.Value; }

    static public ID Make(ElementId Id)
    {
      if (Id == ElementId.InvalidElementId)
        return null;

      ID id = Element.Make(Id);

      return id ?? Category.Make(Id);
    }

    #region IGH_PersitentGoo
    public virtual Guid ReferenceID
    {
      get => Guid.Empty;
      set { if (value != Guid.Empty) throw new InvalidOperationException(); }
    }
    public string UniqueID { get; protected set; }
    public bool IsReferencedGeometry => UniqueID.Length > 0;
    public bool IsGeometryLoaded => Value != null;
    public /*abstract*/ bool LoadElement(Document doc) => false;
    #endregion

    public ID() { Value = ElementId.InvalidElementId; UniqueID = string.Empty; }
    protected ID(ElementId id, string uniqueId = null) { Value = id; UniqueID = uniqueId ?? string.Empty; }

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
      if (typeof(Q).IsAssignableFrom(typeof(GH_Guid)))
      {
        target = (Q) (object) new GH_Guid(ReferenceID);
        return true;
      }
      if (typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
      {
        target = (Q) (object) new GH_Integer(Value.IntegerValue);
        return true;
      }
      if (typeof(Q).IsAssignableFrom(typeof(GH_String)))
      {
        target = (Q) (object) new GH_String(UniqueID);
        return true;
      }
      if (target is ElementId)
      {
        target = (Q) (object) Value;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public override string ToString()
    {
      if (!IsValid)
        return "Null " + TypeName;

      return string.Format("{0} {1}", TypeName, Value.IntegerValue);
    }

    public override sealed bool Read(GH_IReader reader)
    {
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
  public abstract class ValueListPicker : GH_ValueList, IGH_InitCodeAware
  {
    public override GH_ParamData DataType => GH_ParamData.remote;
    public override GH_ParamKind Kind => GH_ParamKind.floating;

    void IGH_InitCodeAware.SetInitCode(string code) => NickName = code;

    public ValueListPicker()
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
      var nTopic = new Grasshopper.GUI.HTML.GH_HtmlFormatter(this);
      nTopic.Title = Name;
      nTopic.Description =
      @"<p>Double click on it and use the name input box to enter a name, alternativelly you can enter a name patter. " +
      @"If a pattern is used, this param list will be filled up with all the objects that match it.</p>" +
      @"<p>Several kind of patterns are supported, the method used depends on the first pattern character:</p>" +
      @"<dl>" +
      @"<dt><b>></b></dt><dd>Starts with</dd>" +
      @"<dt><b><</b></dt><dd>Ends with</dd>" +
      @"<dt><b>?</b></dt><dd>Contains, same as a regular search</dd>" +
      @"<dt><b>:</b></dt><dd>Wildcards, see Microsoft.VisualBasic " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/visual-basic/language-reference/operators/like-operator#pattern-options\">LikeOperator</a></dd>" +
      @"<dt><b>;</b></dt><dd>Regular expresion, see " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference\">here</a> as reference</dd>" +
      @"</dl>";
      nTopic.ContactURI = @"https://discourse.mcneel.com/c/serengeti/inside";

      return nTopic.HtmlFormat();
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public abstract class GH_Component : Grasshopper.Kernel.GH_Component
  {
    protected GH_Component(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    // Grasshopper default implementation has a bug, it checks inputs instead of outputs
    public override bool IsBakeCapable => Params?.Output.OfType<IGH_BakeAwareObject>().Where(x => x.IsBakeCapable).Any() ?? false;
  }

  public abstract class GH_TransactionalComponent : GH_Component
  {
    protected GH_TransactionalComponent(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    public override Rhino.Geometry.BoundingBox ClippingBox
    {
      get
      {
        var clippingBox = Rhino.Geometry.BoundingBox.Empty;

        foreach (var param in Params)
        {
          if (param.SourceCount > 0)
            continue;

          if (param is IGH_PreviewObject previewObject)
          {
            if (!previewObject.Hidden && previewObject.IsPreviewCapable)
              clippingBox.Union(previewObject.ClippingBox);
          }
        }

        return clippingBox;
      }
    }

    static protected T CopyParametersFrom<T>(T to, Element from) where T : Element
    {
      if (from != null && to != null)
      {
        foreach (var previousParameter in from.Parameters.Cast<Parameter>())
        {
          var param = to.get_Parameter(previousParameter.Definition);
          if (param == null || param.IsReadOnly)
            continue;

          switch (previousParameter.StorageType)
          {
            case StorageType.Integer:   param.Set(previousParameter.AsInteger()); break;
            case StorageType.Double:    param.Set(previousParameter.AsDouble()); break;
            case StorageType.String:    param.Set(previousParameter.AsString()); break;
            case StorageType.ElementId: param.Set(previousParameter.AsElementId()); break;
          }
        }
      }

      return to;
    }

    static protected void ReplaceElement(Document doc, List<ElementId> list, int index, Element element)
    {
      var id = element?.Id ?? ElementId.InvalidElementId;

      if (index < list.Count)
      {
        if (id != list[index])
        {
          if (doc.GetElement(list[index]) != null)
            doc.Delete(list[index]);

          list[index] = id;
          if (element != null) element.Pinned = true;
        }
      }
      else
      {
        for (int e = list.Count; e <= index; e++)
          list.Add(ElementId.InvalidElementId);

        list[index] = id;
        if (null != element) element.Pinned = true;
      }
    }

    static protected void TrimExcess<T>(List<T> list, int begin = 0)
    {
      int end = list.Count;
      if (begin < end)
      {
        list.RemoveRange(begin, end - begin);
        list.TrimExcess();
      }
    }

    static protected void TrimExcess(Document doc, List<ElementId> list, int begin = 0)
    {
      foreach(var id in list.Skip(begin))
      {
        if (doc.GetElement(id) != null)
        {
          try { doc.Delete(id); }
          catch (Autodesk.Revit.Exceptions.ApplicationException) { }
        }
      }

      TrimExcess(list, begin);
    }
    protected static double LiteralLengthValue(double meters)
    {
      switch (Rhino.RhinoDoc.ActiveDoc?.ModelUnitSystem)
      {
        case Rhino.UnitSystem.None:
        case Rhino.UnitSystem.Inches:
        case Rhino.UnitSystem.Feet:
          return Math.Round(meters * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Meters, Rhino.UnitSystem.Feet))
                 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Feet, Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem);
        default:
          return meters * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Meters, Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem);
      }
    }
  }

  public abstract class GH_TransactionalComponentItem : GH_TransactionalComponent
  {
    protected GH_TransactionalComponentItem(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    List<ElementId> PreviousElementValues = new List<ElementId>();
    protected Element PreviousElement(Document doc, int Iteration)
    {
      if (Iteration < PreviousElementValues.Count)
        return doc.GetElement(PreviousElementValues[Iteration]);

      return null;
    }

    protected void ReplaceElement(Document doc, IGH_DataAccess DA, int Iteration, Element element)
    {
      DA.SetData(0, element, Iteration);
      ReplaceElement(doc, PreviousElementValues, Iteration, element);

      if (Iteration == DA.Iteration)
      {
        TrimExcess(doc, PreviousElementValues, Iteration + 1);

        // Notify Grasshopper continue evaluating the definition from this component
        if (RuntimeMessageLevel < GH_RuntimeMessageLevel.Error)
        {
          foreach (var param in Params.Output)
          {
            foreach (var recipient in param.Recipients)
              recipient.ExpireSolution(false);
          }
        }
      }
    }
  }

  public abstract class GH_TransactionalComponentList : GH_TransactionalComponent
  {
    protected GH_TransactionalComponentList(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    List<List<ElementId>> PreviousElementValues = new List<List<ElementId>>();
    protected IEnumerable<Element> PreviousElements(Document doc, int Iteration)
    {
      if (Iteration < PreviousElementValues.Count)
      {
        foreach (var id in PreviousElementValues[Iteration])
          yield return doc.GetElement(id);
      }
    }

    protected void ReplaceElements(Document doc, IGH_DataAccess DA, int Iteration, IEnumerable<Element> elements)
    {
      DA.SetDataList(0, elements, Iteration);

      // Update PreviousElementValues
      {
        for (int e = PreviousElementValues.Count; e <= Iteration; e++)
          PreviousElementValues.Add(null);

        var previousElementValues = PreviousElementValues[Iteration];
        if (previousElementValues == null)
          previousElementValues = PreviousElementValues[Iteration] = new List<ElementId>();

        int index = 0;
        foreach (var element in elements)
          ReplaceElement(doc, previousElementValues, index++, element);

        // Remove extra elements in PreviousElementValues
        TrimExcess(doc, previousElementValues, index);
      }

      if (Iteration == DA.Iteration)
      {
        foreach (var list in PreviousElementValues.Skip(Iteration + 1))
          TrimExcess(doc, list);

        TrimExcess(PreviousElementValues, Iteration + 1);

        // Notify Grasshopper continue evaluating the definition from this component
        if (RuntimeMessageLevel < GH_RuntimeMessageLevel.Error)
        {
          foreach (var param in Params.Output)
          {
            foreach (var recipient in param.Recipients)
              recipient.ExpireSolution(false);
          }
        }
      }
    }
  }
}
