using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class DocumentCategories : GH_Component
  {
    public override Guid ComponentGuid => new Guid("D150E40E-0970-4683-B517-038F8BA8B0D8");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{C}");

    public DocumentCategories() : base(
      "Document.Categories", "Categories",
      "Get active document categories list",
      "Revit", "Document")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      var type = manager[manager.AddIntegerParameter("Type", "T", "Category type", GH_ParamAccess.item, (int) Autodesk.Revit.DB.CategoryType.Model)] as Grasshopper.Kernel.Parameters.Param_Integer;
      type.AddNamedValue("Model", 1);
      type.AddNamedValue("Annotation", 2);
      type.AddNamedValue("Analytical", 4);
      type.Optional = true;
      manager[manager.AddBooleanParameter("AllowsParameters", "A", "Allows bound parameters", GH_ParamAccess.item, true)].Optional = true;
      manager[manager.AddBooleanParameter("HasMaterialQuantities", "M", "Has material quantities", GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Categories", "Categories", "Categories list", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var categoryType = Autodesk.Revit.DB.CategoryType.Invalid;
      {
        var categoryValue = (int) categoryType;
        DA.GetData("Type", ref categoryValue);
        categoryType = (Autodesk.Revit.DB.CategoryType) categoryValue;
      }

      bool AllowsParameters = false;
      bool nofilterParams = (!DA.GetData("AllowsParameters", ref AllowsParameters) && Params.Input[1].Sources.Count == 0);

      bool HasMaterialQuantities = false;
      bool nofilterMaterials = (!DA.GetData("HasMaterialQuantities", ref HasMaterialQuantities) && Params.Input[2].Sources.Count == 0);

      var categories = Revit.ActiveDBDocument.Settings.Categories.Cast<Category>();

      if(categoryType != Autodesk.Revit.DB.CategoryType.Invalid)
        categories = categories.Where((x) => x.CategoryType == categoryType);

      if (!nofilterParams)
        categories = categories.Where((x) => x.AllowsBoundParameters == AllowsParameters);

      if (!nofilterMaterials)
        categories = categories.Where((x) => x.HasMaterialQuantities == HasMaterialQuantities);

      IEnumerable<Category> list = null;
      foreach (var group in categories.GroupBy((x) => x.CategoryType).OrderBy((x) => x.Key))
      {
        var orderedGroup = group.OrderBy((x) => x.Name);
        list = list?.Concat(orderedGroup) ?? orderedGroup;
      }

      DA.SetDataList("Categories", list);
    }
  }

  public class DocumentCategoriesPicker : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("EB266925-F1AA-4729-B5C0-B978937F51A3");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("C*");

    public DocumentCategoriesPicker()
    {
      Category = "Revit";
      SubCategory = "Input";
      Name = "Document.CategoriesPicker";
      MutableNickName = false;
      Description = "Provides a Category picker";

      ListMode = GH_ValueListMode.DropDown;
    }

    void RefreshList()
    {
      var selectedItems = new List<string>();
      {
        foreach (var item in ListItems)
          if (item.Selected)
            selectedItems.Add(item.Expression);
      }

      ListItems.Clear();

      if (Revit.ActiveDBDocument != null)
      {
        foreach (var group in Revit.ActiveDBDocument.Settings.Categories.Cast<Category>().GroupBy((x) => x.CategoryType).OrderBy((x) => x.Key))
        {
          foreach (var category in group.OrderBy((x) => x.Name))
          {
            var item = new GH_ValueListItem(category.Name, category.Id.IntegerValue.ToString());
            item.Selected = selectedItems.Contains(item.Expression);
            ListItems.Add(item);
          }
        }

        // Preselect OST_GenericModel category by default
        if (selectedItems.Count == 0 && ListMode != GH_ValueListMode.CheckList)
        {
          foreach (var item in ListItems)
            item.Selected = item.Expression == ((int) BuiltInCategory.OST_GenericModel).ToString();
        }
      }
    }

    protected override void CollectVolatileData_Custom()
    {
      NickName = "Category";
      RefreshList();
      base.CollectVolatileData_Custom();
    }
  }
}
