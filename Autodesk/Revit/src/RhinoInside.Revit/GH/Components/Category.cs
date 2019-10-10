using System;
using System.Linq;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;
using DB = Autodesk.Revit.DB;

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
      ListItems.Add(new GH_ValueListItem("Model", ((int) DB.CategoryType.Model).ToString()));
      ListItems.Add(new GH_ValueListItem("Annotation", ((int) DB.CategoryType.Annotation).ToString()));
      ListItems.Add(new GH_ValueListItem("Analytical", ((int) DB.CategoryType.AnalyticalModel).ToString()));
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class CategoryIdentity : Component
  {
    public override Guid ComponentGuid => new Guid("D794361E-DE8C-4D0A-BC77-52293F27D3AA");

    public CategoryIdentity()
    : base("Category.Identity", "Category.Identity", "Query category identity information", "Revit", "Category")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", "Category name", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Category(), "Parent", "P", "Category parent category", GH_ParamAccess.item);
      manager.AddIntegerParameter("Type", "T", "Category type", GH_ParamAccess.item);
      manager.AddBooleanParameter("AllowsSubcategories", "A", "Category allows subcategories to be added", GH_ParamAccess.item);
      manager.AddBooleanParameter("AllowsParameters", "A", "Category allows bound parameters", GH_ParamAccess.item);
      manager.AddBooleanParameter("HasMaterialQuantities", "M", "Category has material quantities", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      DA.SetData("Name", category?.Name);
      DA.SetData("Parent", category?.Parent);
      DA.SetData("Type", category?.CategoryType);
      DA.SetData("AllowsSubcategories", category?.CanAddSubcategory);
      DA.SetData("AllowsParameters", category?.AllowsBoundParameters);
      DA.SetData("HasMaterialQuantities", category?.HasMaterialQuantities);
    }
  }

  public class CategoryObjectStyle : Component
  {
    public override Guid ComponentGuid => new Guid("1DD8AE78-F7DA-4F26-8353-4CCE6B925DC6");

    public CategoryObjectStyle()
    : base("Category.ObjectStyle", "Category.ObjectStyle", string.Empty, "Revit", "Category")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddIntegerParameter("LineWeight [projection]", "LWP", "Category line weight [projection]", GH_ParamAccess.item);
      manager.AddIntegerParameter("LineWeight [cut]", "LWC", "Category line weigth [cut]", GH_ParamAccess.item);
      manager.AddColourParameter("LineColor", "LC", "Category line color", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Element(), "LinePattern [projection]", "LPP", "Category line pattern [projection]", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Element(), "LinePattern [cut]", "LPC", "Category line pattern [cut]", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Material(), "Material", "M", "Category material", GH_ParamAccess.item);
      manager.AddBooleanParameter("Cuttable", "C", "Indicates if the category is cuttable or not", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      var doc = category?.Document();

      DA.SetData("LineWeight [projection]", category?.GetLineWeight(DB.GraphicsStyleType.Projection));
      DA.SetData("LineWeight [cut]", category?.GetLineWeight(DB.GraphicsStyleType.Cut));
      DA.SetData("LineColor", category?.LineColor.ToRhino());
      DA.SetData("LinePattern [projection]", doc?.GetElement(category.GetLinePatternId(DB.GraphicsStyleType.Projection)));
      DA.SetData("LinePattern [cut]", doc?.GetElement(category.GetLinePatternId(DB.GraphicsStyleType.Cut)));
      DA.SetData("Material", category?.Material);
      DA.SetData("Cuttable", category?.IsCuttable);
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
      DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      using (var subCategories = category.SubCategories)
        DA.SetDataList("SubCategories", subCategories.Cast<DB.Category>());
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
      DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      DA.SetData("Projection", category?.GetGraphicsStyle(DB.GraphicsStyleType.Projection));
      DA.SetData("Cut", category?.GetGraphicsStyle(DB.GraphicsStyleType.Cut));
    }
  }
}
