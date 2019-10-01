using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class DocumentElementTypes : GH_Component
  {
    public override Guid ComponentGuid => new Guid("7B00F940-4C6E-4F3F-AB81-C3EED430DE96");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{T}");

    public DocumentElementTypes() : base(
      "Document.ElementTypes", "ElementTypes",
      "Get active document element types list",
      "Revit", "Document")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager[manager.AddParameter(new Parameters.Category(), "FamilyCategory", "C", "Category of the requested element type", GH_ParamAccess.item)].Optional = true;
      manager[manager.AddTextParameter("FamilyName", "F", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddTextParameter("TypeName", "N", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "ElementTypes", "T", "Requested element type", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      DA.GetData("FamilyCategory", ref category);

      string familyName = null;
      DA.GetData("FamilyName", ref familyName);

      string name = null;
      DA.GetData("TypeName", ref name);

      var elementTypes = new List<ElementType>();

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        if (category != null)
        {
          using (var familyCollector = new FilteredElementCollector(Revit.ActiveDBDocument))
          {
            var familiesSet = new HashSet<string>
            (
              familyCollector.OfClass(typeof(Family)).
              Cast<Family>().
              Where((x) => x.FamilyCategory.Id == category.Id).
              Select((x) => x.Name)
            );

            foreach (var elementType in collector.WhereElementIsElementType().Cast<ElementType>())
            {
              if (elementType.Category?.Id != category.Id && !familiesSet.Contains(elementType.FamilyName))
                continue;

              if (familyName != null && elementType.FamilyName != familyName)
                continue;

              if (name != null && elementType.Name != name)
                continue;

              elementTypes.Add(elementType);
            }
          }
        }
        else
        {
          foreach (var elementType in collector.WhereElementIsElementType().ToElements().OfType<ElementType>())
          {
            if (familyName != null && elementType.FamilyName != familyName)
              continue;

            if (name != null && elementType.Name != name)
              continue;

            elementTypes.Add(elementType);
          }
        }
      }

      DA.SetDataList("ElementTypes", elementTypes);
    }
  }

  public class DocumentFamiliesPicker : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("45CEE087-4194-4E55-AA20-9CC5D2193CE0");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("F*");

    public DocumentFamiliesPicker()
    {
      Category = "Revit";
      SubCategory = "Input";
      Name = "Document.FamiliesPicker";
      MutableNickName = false;
      Description = "Provides a Family picker";

      ListMode = GH_ValueListMode.DropDown;
    }

    void RefreshList()
    {
      var selectedItems = ListItems.Where(x => x.Selected).Select(x => x.Expression).ToList();
      ListItems.Clear();

      if (Revit.ActiveDBDocument != null)
      {
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          foreach (var family in collector.OfClass(typeof(Family)).Cast<Family>().OrderBy((x) => x.Name))
          {
            var item = new GH_ValueListItem(family.Name, family.Id.IntegerValue.ToString());
            item.Selected = selectedItems.Contains(item.Expression);
            ListItems.Add(item);
          }
        }
      }
    }

    protected override void CollectVolatileData_Custom()
    {
      NickName = "Family";
      RefreshList();
      base.CollectVolatileData_Custom();
    }
  }

}
