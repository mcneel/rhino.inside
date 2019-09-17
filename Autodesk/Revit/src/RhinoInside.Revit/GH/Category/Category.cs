using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;
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
        var category = (Autodesk.Revit.DB.Category) this;
        if (category == null)
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
        else if (Enum.IsDefined(typeof(BuiltInCategory), Value.IntegerValue))
          return LabelUtils.GetLabelFor((BuiltInCategory) Value.IntegerValue);
        else
          return "Revit Category \"" + ((BuiltInCategory) Value.IntegerValue).ToString() + "\"";
      }

      return base.ToString();
    }
  }

  public class GraphicsStyle : Element
  {
    public override string TypeName => "Revit GraphicsStyle";
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
            case GraphicsStyleType.Cut: ToolTip += "[cut]"; break;
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
  public class Category : ElementIdNonGeometryParam<Types.Category>
  {
    public override Guid ComponentGuid => new Guid("6722C7A5-EFD3-4119-A7FD-6C8BE892FD04");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public Category() : base("Category", "Category", "Represents a Revit document category.", "Params", "Revit") { }
  }

  public class GraphicsStyle : ElementIdNonGeometryParam<Types.GraphicsStyle>
  {
    public override Guid ComponentGuid => new Guid("833E6207-BA60-4C6B-AB8B-96FDA0F91822");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public GraphicsStyle() : base("GraphicsStyle", "GraphicsStyle", "Represents a Revit graphics style.", "Params", "Revit") { }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class CategoryTypes : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("5FFB1339-8521-44A1-9075-2984637725E9");
    public override GH_Exposure Exposure => GH_Exposure.secondary;

    public CategoryTypes()
    {
      Category = "Revit";
      SubCategory = "Category";
      Name = "CategoryTypes";
      NickName = "CategoryTypes";
      Description = "Provides a picker of a CategoryType";

      ListItems.Clear();
      ListItems.Add(new GH_ValueListItem("Model", ((int) Autodesk.Revit.DB.CategoryType.Model).ToString()));
      ListItems.Add(new GH_ValueListItem("Annotation", ((int) Autodesk.Revit.DB.CategoryType.Annotation).ToString()));
      ListItems.Add(new GH_ValueListItem("Analytical", ((int) Autodesk.Revit.DB.CategoryType.AnalyticalModel).ToString()));
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class CategoryDecompose : Component
  {
    public override Guid ComponentGuid => new Guid("D794361E-DE8C-4D0A-BC77-52293F27D3AA");

    public CategoryDecompose()
    : base("Category.Decompose", "Category.Decompose", "Decompose a category", "Revit", "Category")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", "Category name", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Category(), "Parent", "P", "Category parent category", GH_ParamAccess.item);
      manager.AddColourParameter("LineColor", "LC", "Category line color", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Element(), "Material", "M", "Category material", GH_ParamAccess.item);
      manager.AddBooleanParameter("AllowsParameters", "A", "Category allows bound parameters", GH_ParamAccess.item);
      manager.AddBooleanParameter("HasMaterialQuantities", "M", "Category has material quantities", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      DA.SetData("Name", category?.Name);
      DA.SetData("Parent", category?.Parent);
      DA.SetData("LineColor", category?.LineColor.ToRhino());
      DA.SetData("Material", category?.Material);
      DA.SetData("AllowsParameters", category?.AllowsBoundParameters);
      DA.SetData("HasMaterialQuantities", category?.HasMaterialQuantities);
    }
  }

  public class CategorySubCategories : Component
  {
    public override Guid ComponentGuid => new Guid("4915AB87-0BD5-4541-AC43-3FBC450DD883");

    public CategorySubCategories()
    : base("Category.SubCategories", "Category.SubCategories", "Returns a list of all the subcategories of Category", "Revit", "Category")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "SubCategories", "S", string.Empty, GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      using (var subCategories = category.SubCategories)
        DA.SetDataList("SubCategories", subCategories.Cast<Autodesk.Revit.DB.Category>());
    }
  }

  public class CategoryGraphicsStyle : Component
  {
    public override Guid ComponentGuid => new Guid("46139967-74FC-4820-BA20-B1DC7F30ABDE");
    protected override string IconTag => "G";

    public CategoryGraphicsStyle()
    : base("Category.GraphicsStyle", "Category.GraphicsStyle", string.Empty, "Revit", "Category")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GraphicsStyle(), "Projection", "P", string.Empty, GH_ParamAccess.list);
      manager.AddParameter(new Parameters.GraphicsStyle(), "Cut", "C", string.Empty, GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      DA.SetData("Projection", category?.GetGraphicsStyle(GraphicsStyleType.Projection));
      DA.SetData("Cut", category?.GetGraphicsStyle(GraphicsStyleType.Cut));
    }
  }
}
