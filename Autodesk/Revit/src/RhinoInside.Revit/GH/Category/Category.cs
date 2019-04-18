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
    public static explicit operator Autodesk.Revit.DB.Category(Category self) => Revit.ActiveDBDocument == null ? null : Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, self);

    static public Category Make(Autodesk.Revit.DB.Category category)
    {
      if (category == null)
        return null;

      return new Category(category);
    }

    static public new Category Make(ElementId Id) => Make(Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, Id));

    public Category() : base() { }
    protected Category(Autodesk.Revit.DB.Category category) : base(category.Id, Enum.GetName(typeof(BuiltInCategory), category.Id.IntegerValue) ?? string.Empty) { }

    public override sealed bool CastFrom(object source)
    {
      Autodesk.Revit.DB.Category category = null;
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      switch (source)
      {
        case Autodesk.Revit.DB.Category c:   category = c; break;
        case Autodesk.Revit.DB.ElementId id: category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, id); break;
        case int integer:                    category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, new ElementId(integer)); break;
        case string uniqueId:
          try
          {
            var id = new ElementId((BuiltInCategory) Enum.Parse(typeof(BuiltInCategory), uniqueId, false));
            category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, id);
          }
          catch (ArgumentException) { }
          break;
      }

      if (ScriptVariableType.IsInstanceOfType(category))
      {
        Value = category.Id;
        UniqueID = Enum.GetName(typeof(BuiltInCategory), Value.IntegerValue) ?? string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      var category = (Autodesk.Revit.DB.Category) this;
      if (category == null)
        return false;

      if (typeof(Q).IsSubclassOf(typeof(Autodesk.Revit.DB.Category)))
      {
        target = (Q) (object) category;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.Category)))
      {
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
        int value = proxyOwner.Value.IntegerValue;
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

      Autodesk.Revit.DB.Category category => proxyOwner.Value != null && Revit.ActiveDBDocument != null ? Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, proxyOwner.Value) : null;

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
        if (category != null)
          return "Revit " + category.GetType().Name + " \"" + category.Name + "\"";
        else if(Enum.IsDefined(typeof(BuiltInCategory), Value.IntegerValue))
          return "Revit BuiltIn Category \"" + ((BuiltInCategory) Value.IntegerValue).ToString() + "\"";
      }

      return base.ToString();
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Category : GH_PersistentParam<Types.Category>
  {
    public override Guid ComponentGuid => new Guid("6722C7A5-EFD3-4119-A7FD-6C8BE892FD04");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("C");

    public Category() : base("Category", "Category", "Represents a Revit document category.", "Revit", "Category") { }

    protected override GH_GetterResult Prompt_Plural(ref List<Types.Category> values) => GH_GetterResult.cancel;
    protected override GH_GetterResult Prompt_Singular(ref Types.Category value) => GH_GetterResult.cancel;
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class CategoryTypes : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("5FFB1339-8521-44A1-9075-2984637725E9");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("CT");

    public CategoryTypes()
    {
      Category = "Revit";
      SubCategory = "Category";
      Name = "CategoryTypes";
      NickName = "CategoryTypes";
      Description = "Provides a picker of a CategoryType";

      ListItems.Clear();
      ListItems.Add(new GH_ValueListItem("Model",      ((int) Autodesk.Revit.DB.CategoryType.Model).ToString()));
      ListItems.Add(new GH_ValueListItem("Annotation", ((int) Autodesk.Revit.DB.CategoryType.Annotation).ToString()));
      ListItems.Add(new GH_ValueListItem("Analytical", ((int) Autodesk.Revit.DB.CategoryType.AnalyticalModel).ToString()));
    }
  }

  public class CategoryDecompose : GH_Component
  {
    public override Guid ComponentGuid => new Guid("D794361E-DE8C-4D0A-BC77-52293F27D3AA");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("C{");

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
}
