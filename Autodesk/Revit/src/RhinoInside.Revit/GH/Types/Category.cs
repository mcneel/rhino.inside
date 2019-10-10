using System;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class Category : Element
  {
    public override string TypeName => "Revit Category";
    public override string TypeDescription => "Represents a Revit category";
    override public object ScriptVariable() => (DB.Category) this;
    protected override Type ScriptVariableType => typeof(DB.Category);
    public static explicit operator DB.Category(Category self) => self.Document?.GetCategory(self.Value);

    #region IGH_ElementId
    public override bool LoadElement()
    {
      if (Document is null)
      {
        Value = null;
        if (!Revit.ActiveUIApplication.TryGetDocument(DocumentGUID, out var doc))
        {
          Document = null;
          return false;
        }

        Document = doc;
      }
      else if (IsElementLoaded)
        return true;

      if (Document is object)
        return Document.TryGetCategoryId(UniqueID, out m_value);

      return false;
    }
    #endregion

    public Category() : base() { }
    public Category(DB.Document doc, DB.ElementId id) : base(doc, id) { }
    public Category(DB.Category category)             : base(category.Document(), category.Id) { }

    new public static Category FromValue(object data)
    {
      if (data is DB.Element element)
        data = DB.Category.GetCategory(element.Document, element.Id);

      return FromCategory(data as DB.Category);
    }

    public static Category FromCategory(DB.Category category)
    {
      if (category is null)
        return null;

      return new Category(category);
    }

    new public static Category FromElementId(DB.Document doc, DB.ElementId id)
    {
      if (id.IsCategoryId(doc))
        return new Category(doc, id);

      return null;
    }

    public override sealed bool CastFrom(object source)
    {
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      var categoryId = DB.ElementId.InvalidElementId;
      switch (source)
      {
        case DB.Category c:   SetValue(c.Document(), c.Id); return true;
        case DB.ElementId id: categoryId = id; break;
        case int integer:     categoryId = new DB.ElementId(integer); break;
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
      if (typeof(Q).IsAssignableFrom(typeof(DB.Category)))
      {
        if (!IsValid)
        {
          target = (Q) (object) null;
          return true;
        }

        var category = (DB.Category) this;
        if (category is null)
          return false;

        target = (Q) (object) category;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    new class Proxy : ID.Proxy
    {
      public Proxy(Category c) : base(c) { (this as IGH_GooProxy).UserString = FormatInstance(); }

      public override bool IsParsable() => true;
      public override string FormatInstance()
      {
        int value = owner.Value?.IntegerValue ?? -1;
        if (Enum.IsDefined(typeof(DB.BuiltInCategory), value))
          return ((DB.BuiltInCategory)value).ToString();

        return value.ToString();
      }
      public override bool FromString(string str)
      {
        if (Enum.TryParse(str, out DB.BuiltInCategory builtInCategory))
        {
          owner.Value = new DB.ElementId(builtInCategory);
          return true;
        }

        return false;
      }

      DB.Category category => owner.IsElementLoaded ? owner.Document?.GetCategory(owner.Id) : null;

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
      public DB.CategoryType CategoryType => category?.CategoryType ?? DB.CategoryType.Invalid;
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
        var category = (DB.Category) this;
        if (category is object)
          return category.Parent is null ? category.Name : $"{category.Parent.Name} : {category.Name}";
#if REVIT_2020
        else if (Enum.IsDefined(typeof(DB.BuiltInCategory), Value.IntegerValue))
          return DB.LabelUtils.GetLabelFor((DB.BuiltInCategory) Value.IntegerValue);
#endif
        else
          return "Revit Category \"" + ((DB.BuiltInCategory) Value.IntegerValue).ToString() + "\"";
      }

      return base.ToString();
    }
  }

  public class GraphicsStyle : Element
  {
    public override string TypeName => "Revit Graphics Style";
    public override string TypeDescription => "Represents a Revit graphics style";
    protected override Type ScriptVariableType => typeof(DB.GraphicsStyle);
    public static explicit operator DB.GraphicsStyle(GraphicsStyle self) =>
      self.Document?.GetElement(self) as DB.GraphicsStyle;

    public GraphicsStyle() { }
    public GraphicsStyle(DB.GraphicsStyle graphicsStyle) : base(graphicsStyle) { }

    public override string ToString()
    {
      if (IsValid)
      {
        var graphicsStyle = (DB.GraphicsStyle) this;
        if (graphicsStyle is object)
        {
          var ToolTip = string.Empty;
          if (graphicsStyle.GraphicsStyleCategory is DB.Category graphicsStyleCategory)
          {
            if(graphicsStyleCategory.Parent is DB.Category parentCategory)
              ToolTip += $"{parentCategory.Name} : ";

            ToolTip += $"{graphicsStyleCategory.Name} : ";
          }

          switch(graphicsStyle.GraphicsStyleType)
          {
            case DB.GraphicsStyleType.Projection: ToolTip += "[projection]"; break;
            case DB.GraphicsStyleType.Cut:        ToolTip += "[cut]"; break;
          }

          return ToolTip;
        }
      }

      return base.ToString();
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Category : ElementIdNonGeometryParam<Types.Category, DB.Category>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    public override Guid ComponentGuid => new Guid("6722C7A5-EFD3-4119-A7FD-6C8BE892FD04");

    public Category() : base("Category", "Category", "Represents a Revit document category.", "Params", "Revit") { }

    protected override Types.Category PreferredCast(object data) => Types.Category.FromValue(data);
  }

  public class GraphicsStyle : ElementIdNonGeometryParam<Types.GraphicsStyle, DB.GraphicsStyle>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    public override Guid ComponentGuid => new Guid("833E6207-BA60-4C6B-AB8B-96FDA0F91822");

    public GraphicsStyle() : base("Graphics Style", "Graphics Style", "Represents a Revit graphics style.", "Params", "Revit") { }
  }
}
