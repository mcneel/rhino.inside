using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Parameters
{
  public abstract class DocumentCategoriesPicker : DocumentPicker
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override bool PassesFilter(Document document, ElementId id) => id.IsCategoryId(document);
    protected virtual CategoryType CategoryType => CategoryType.Invalid;
    protected virtual BuiltInCategory DefaultBuiltInCategory => BuiltInCategory.INVALID;

    public DocumentCategoriesPicker()
    {
      Category = "Revit";
      SubCategory = "Input";
      NickName = "Document";
      MutableNickName = false;
      Name = $"{NickName}.CategoriesPicker";
      Description = $"Provides a {NickName} Category picker";

      ListMode = GH_ValueListMode.DropDown;
    }

    protected override void CollectVolatileData_Custom()
    {
      var selectedItems = ListItems.Where(x => x.Selected).Select(x => x.Expression).ToList();
      ListItems.Clear();

      if (Revit.ActiveDBDocument != null)
      {
        foreach (var group in Revit.ActiveDBDocument.Settings.Categories.Cast<Autodesk.Revit.DB.Category>().GroupBy(x => x.CategoryType).OrderBy(x => x.Key))
        {
          foreach (var category in group.OrderBy(x => x.Name).Where(x => !x.IsHidden()))
          {
            if (CategoryType != CategoryType.Invalid && category.CategoryType != CategoryType)
              continue;

            var item = new GH_ValueListItem(category.Name, category.Id.IntegerValue.ToString());
            item.Selected = selectedItems.Contains(item.Expression);
            ListItems.Add(item);
          }
        }

        // Preselect OST_GenericModel category by default
        if (selectedItems.Count == 0 && ListMode != GH_ValueListMode.CheckList)
        {
          foreach (var item in ListItems)
            item.Selected = item.Expression == ((int) DefaultBuiltInCategory).ToString();
        }
      }

      base.CollectVolatileData_Custom();
    }
  }

  public class ModelCategoriesPicker : DocumentCategoriesPicker
  {
    public override Guid ComponentGuid => new Guid("EB266925-F1AA-4729-B5C0-B978937F51A3");
    protected override CategoryType CategoryType => CategoryType.Model;
    protected override BuiltInCategory DefaultBuiltInCategory => BuiltInCategory.OST_GenericModel;
    public override string NickName => MutableNickName ? base.NickName : "Model";
    public ModelCategoriesPicker() { }
  }
  public class AnnotationCategoriesPicker : DocumentCategoriesPicker
  {
    public override Guid ComponentGuid => new Guid("B1D1CA45-3771-49CA-8540-9A916A743C1B");
    protected override CategoryType CategoryType => CategoryType.Annotation;
    protected override BuiltInCategory DefaultBuiltInCategory => BuiltInCategory.OST_GenericAnnotation;
    public override string NickName => MutableNickName ? base.NickName : "Annotation";
    public AnnotationCategoriesPicker() { }
  }
  public class AnalyticalCategoriesPicker : DocumentCategoriesPicker
  {
    public override Guid ComponentGuid => new Guid("4120C5ED-4329-4F42-B8D3-FA518E6E6807");
    protected override CategoryType CategoryType => CategoryType.AnalyticalModel;
    public override string NickName => MutableNickName ? base.NickName : "Analytical";
    public AnalyticalCategoriesPicker() { }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class DocumentCategories : DocumentComponent
  {
    public override Guid ComponentGuid => new Guid("D150E40E-0970-4683-B517-038F8BA8B0D8");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override ElementFilter ElementFilter => null;

    public override bool NeedsToBeExpired(Autodesk.Revit.DB.Events.DocumentChangedEventArgs e)
    {
      var document = e.GetDocument();

      var added = e.GetAddedElementIds().Where(x => x.IsCategoryId(document));
      if (added.Any())
        return true;

      var modified = e.GetModifiedElementIds().Where(x => x.IsCategoryId(document));
      if (modified.Any())
        return true;

      var deleted = e.GetDeletedElementIds();
      if (deleted.Any())
      {
        var empty = new ElementId[0];
        var deletedSet = new HashSet<ElementId>(deleted);
        foreach (var param in Params.Output.OfType<Parameters.IGH_ElementIdParam>())
        {
          if (param.NeedsToBeExpired(document, empty, deletedSet, empty))
            return true;
        }
      }

      return false;
    }

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
      type.AddNamedValue("Analytical", 5);
      type.Optional = true;
      manager[manager.AddBooleanParameter("AllowsParameters", "A", "Allows bound parameters", GH_ParamAccess.item, true)].Optional = true;
      manager[manager.AddBooleanParameter("HasMaterialQuantities", "M", "Has material quantities", GH_ParamAccess.item)].Optional = true;
      manager[manager.AddBooleanParameter("Cuttable", "C", "Has material quantities", GH_ParamAccess.item)].Optional = true;
      manager[manager.AddBooleanParameter("Hidden", "H", "Is hidden category", GH_ParamAccess.item, false)].Optional = true;
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

      bool Cuttable = false;
      bool nofilterCuttable = (!DA.GetData("Cuttable", ref Cuttable) && Params.Input[3].Sources.Count == 0);

      bool Hidden = false;
      bool nofilterHidden = (!DA.GetData("Hidden", ref Hidden) && Params.Input[4].Sources.Count == 0);

      var categories = Revit.ActiveDBDocument.Settings.Categories.Cast<Category>();

      if (categoryType != Autodesk.Revit.DB.CategoryType.Invalid)
        categories = categories.Where((x) => x.CategoryType == categoryType);

      if (!nofilterParams)
        categories = categories.Where((x) => x.AllowsBoundParameters == AllowsParameters);

      if (!nofilterMaterials)
        categories = categories.Where((x) => x.HasMaterialQuantities == HasMaterialQuantities);

      if (!nofilterCuttable)
        categories = categories.Where((x) => x.IsCuttable == Cuttable);

      if (!nofilterHidden)
        categories = categories.Where((x) => x.IsHidden() == Hidden);

      IEnumerable<Category> list = null;
      foreach (var group in categories.GroupBy((x) => x.CategoryType).OrderBy((x) => x.Key))
      {
        var orderedGroup = group.OrderBy((x) => x.Name);
        list = list?.Concat(orderedGroup) ?? orderedGroup;
      }

      if (list is object)
        DA.SetDataList("Categories", list);
      else
        DA.DisableGapLogic();
    }
  }
}
