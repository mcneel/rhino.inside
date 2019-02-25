using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;

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
      manager.AddIntegerParameter("Type", "T", "Category type", GH_ParamAccess.item, (int) Autodesk.Revit.DB.CategoryType.Model);
      manager[manager.AddBooleanParameter("HasMaterialQuantities", "M", "Has Material Quantities", GH_ParamAccess.item, true)].Optional = true;
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

      bool HasMaterialQuantities = false;
      bool nofilter = (!DA.GetData("HasMaterialQuantities", ref HasMaterialQuantities) && Params.Input[1].Sources.Count == 0);

      var list = new List<Category>();

      foreach (var category in Revit.ActiveDBDocument.Settings.Categories.Cast<Category>())
      {
        if (categoryType != Autodesk.Revit.DB.CategoryType.Invalid && category.CategoryType != categoryType)
          continue;

        if (!nofilter && HasMaterialQuantities != category.HasMaterialQuantities)
          continue;

        list.Add(category);
      }

      DA.SetDataList("Categories", list);
    }
  }
}
