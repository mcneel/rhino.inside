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

    public DocumentCategories() : base("Document.Categories", "Categories",
      "Get active document categories list",
      "Revit", "Document")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Categories", "Categories", "Categories list", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var list = new List<Category>();

      foreach (var item in Revit.ActiveDBDocument.Settings.Categories)
      {
        if (item is Category category)
        {
          if (!DirectShape.IsValidCategoryId(category.Id, Revit.ActiveDBDocument))
            continue;

          list.Add(category);
        }
      }

      DA.SetDataList("Categories", list);
    }
  }
}
