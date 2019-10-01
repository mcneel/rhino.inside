using System;

using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class Category : ID
  {
    public override string TypeName => "Revit Category";
    public override string TypeDescription => "Represents a Revit category";
    override public object ScriptVariable() => (Autodesk.Revit.DB.Category) this;
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Category);
    public static explicit operator Autodesk.Revit.DB.Category(Category self) => GetCategory(Revit.ActiveDBDocument, self.Value);

    public  static Category Make(Autodesk.Revit.DB.Category category) => Make(category?.Id);
    private static new Category Make(ElementId id) => new Category(id);

    static Autodesk.Revit.DB.Category GetCategory(Document doc, ElementId id)
    {
      if (doc is null || id is null)
        return null;

      try
      {
        var category = Autodesk.Revit.DB.Category.GetCategory(doc, id);
        if (category != null)
          return category;
      }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

      if (TryGetBuiltInCategory(id.IntegerValue, out var builtInCategory))
      {
        using (var collector = new FilteredElementCollector(doc))
        {
          var element = collector.OfCategory(builtInCategory).FirstElement();
          return element?.Category;
        }
      }

      return null;
    }
    static bool TryGetBuiltInCategory(int id, out BuiltInCategory builtInCategory)
    {
      if (-3000000 < id && id < -2000000 && Enum.IsDefined(typeof(BuiltInCategory), id))
      {
        builtInCategory = (BuiltInCategory) id;
        return true;
      }

      builtInCategory = BuiltInCategory.INVALID;
      return false;
    }

    #region IGH_ElementId
    public override bool LoadElement(Document doc)
    {
      if (TryParseUniqueID(UniqueID, out var _, out var index))
      {
        Value = new ElementId(index);
        if (Value.IsCategoryId(Revit.ActiveDBDocument))
          return true;
      }

      Value = ElementId.InvalidElementId;
      return false;
    }
    #endregion

    public Category() : base() { }
    public Category(Autodesk.Revit.DB.Category category) : base(category.Id) { }
    protected Category(ElementId categoryId) : base(categoryId) { }

    public override sealed bool CastFrom(object source)
    {
      var categoryId = ElementId.InvalidElementId;
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      switch (source)
      {
        case Autodesk.Revit.DB.Category c:   categoryId = c.Id; break;
        case Autodesk.Revit.DB.ElementId id: categoryId = id; break;
        case int integer:                    categoryId = new ElementId(integer); break;
        case string uniqueId:                categoryId = TryParseUniqueID(uniqueId, out var _, out var index) ? new ElementId(index) : ElementId.InvalidElementId; break;
      }

      if (categoryId.IsCategoryId(Revit.ActiveDBDocument))
      {
        SetValue(Revit.ActiveDBDocument, categoryId);
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.Category)))
      {
        if (!IsValid)
        {
          target = (Q) (object) null;
          return true;
        }

        var category = (Autodesk.Revit.DB.Category) this;
        if (category is null)
          return false;

        target = (Q) (object) category;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    class Proxy : IGH_GooProxy
    {
      public Proxy(Category owner) { proxyOwner = owner; (this as IGH_GooProxy).UserString = FormatInstance(); }

      public void Construct() { }
      public string MutateString(string str) => str.Trim();
      public string FormatInstance()
      {
        int value = proxyOwner.Value?.IntegerValue ?? -1;
        if (Enum.IsDefined(typeof(Autodesk.Revit.DB.BuiltInCategory), value))
          return ((BuiltInCategory)value).ToString();

        return value.ToString();
      }
      public bool FromString(string str)
      {
        if (Enum.TryParse(str, out Autodesk.Revit.DB.BuiltInCategory builtInCategory))
        {
          proxyOwner.Value = new ElementId(builtInCategory);
          return true;
        }

        return false;
      }

      readonly Category proxyOwner;
      IGH_Goo IGH_GooProxy.ProxyOwner => proxyOwner;
      bool IGH_GooProxy.IsParsable => true;
      string IGH_GooProxy.UserString { get; set; }

      Autodesk.Revit.DB.Category category => proxyOwner.Value != null ? (Autodesk.Revit.DB.Category) proxyOwner : null;

      public bool Valid => category != null;
      [System.ComponentModel.Description("The category identifier in this session.")]
      public int Id => proxyOwner.Value.IntegerValue;
      [System.ComponentModel.Description("The category Name.")]
      public string Name => category?.Name;

      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Parent category of this category.")]
      public string Parent => category?.Parent?.Name;
      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Category can have project parameters.")]
      public bool AllowsParameters => category?.AllowsBoundParameters ?? false;
      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Identifies if the category is associated with a type of tag for a different category.")]
      public bool IsTag => category?.IsTagCategory ?? false;

      [System.ComponentModel.Category("Material"), System.ComponentModel.Description("Material of the category.")]
      public string Material => category?.Material?.Name;
      [System.ComponentModel.Category("Material"), System.ComponentModel.Description("Identifies if elements of the category are able to report what materials they contain in what quantities.")]
      public bool HasMaterialQuantities => category?.HasMaterialQuantities ?? false;

      [System.ComponentModel.Category("Geometry"), System.ComponentModel.Description("Category type of this category.")]
      public CategoryType CategoryType => category?.CategoryType ?? CategoryType.Invalid;
      [System.ComponentModel.Category("Geometry"), System.ComponentModel.Description("Indicates if the category is cuttable or not.")]
      public bool IsCuttable => category?.IsCuttable ?? false;

      [System.ComponentModel.Category("Display"), System.ComponentModel.Description("The color of lines shown for elements of this category.")]
      public System.Drawing.Color LineColor => category?.LineColor.ToRhino() ?? System.Drawing.Color.Empty;
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public override sealed string ToString()
    {
      if (IsValid)
      {
        var category = (Autodesk.Revit.DB.Category) this;
        if (category is object)
          return category.Parent is null ? category.Name : $"{category.Parent.Name} : {category.Name}";
#if REVIT_2020
        else if (Enum.IsDefined(typeof(BuiltInCategory), Value.IntegerValue))
          return LabelUtils.GetLabelFor((BuiltInCategory) Value.IntegerValue);
#endif
        else
          return "Revit Category \"" + ((BuiltInCategory) Value.IntegerValue).ToString() + "\"";
      }

      return base.ToString();
    }
  }

  public class GraphicsStyle : Element
  {
    public override string TypeName => "Revit Graphics Style";
    public override string TypeDescription => "Represents a Revit graphics style";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.GraphicsStyle);
    public static explicit operator Autodesk.Revit.DB.GraphicsStyle(GraphicsStyle self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.GraphicsStyle;

    public GraphicsStyle() { }
    public GraphicsStyle(Autodesk.Revit.DB.GraphicsStyle graphicsStyle) : base(graphicsStyle) { }

    public override string ToString()
    {
      if (IsValid)
      {
        var graphicsStyle = (Autodesk.Revit.DB.GraphicsStyle) this;
        if (graphicsStyle is object)
        {
          var ToolTip = string.Empty;
          if (graphicsStyle.GraphicsStyleCategory is Autodesk.Revit.DB.Category graphicsStyleCategory)
          {
            if(graphicsStyleCategory.Parent is Autodesk.Revit.DB.Category parentCategory)
              ToolTip += $"{parentCategory.Name} : ";

            ToolTip += $"{graphicsStyleCategory.Name} : ";
          }

          switch(graphicsStyle.GraphicsStyleType)
          {
            case GraphicsStyleType.Projection: ToolTip += "[projection]"; break;
            case GraphicsStyleType.Cut:        ToolTip += "[cut]"; break;
          }

          return ToolTip;
        }

        return $"{TypeName} : id {Value.IntegerValue}";
      }

      return base.ToString();
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Category : ElementIdNonGeometryParam<Types.Category, Autodesk.Revit.DB.Category>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    public override Guid ComponentGuid => new Guid("6722C7A5-EFD3-4119-A7FD-6C8BE892FD04");

    public Category() : base("Category", "Category", "Represents a Revit document category.", "Params", "Revit") { }
  }

  public class GraphicsStyle : ElementIdNonGeometryParam<Types.GraphicsStyle, Autodesk.Revit.DB.GraphicsStyle>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    public override Guid ComponentGuid => new Guid("833E6207-BA60-4C6B-AB8B-96FDA0F91822");

    public GraphicsStyle() : base("Graphics Style", "Graphics Style", "Represents a Revit graphics style.", "Params", "Revit") { }
  }
}
