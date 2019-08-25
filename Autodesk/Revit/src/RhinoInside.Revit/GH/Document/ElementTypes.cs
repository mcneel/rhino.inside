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

namespace RhinoInside.Revit.GH.Parameters
{
  public class DocumentFamiliesPicker : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("45CEE087-4194-4E55-AA20-9CC5D2193CE0");
    public override GH_Exposure Exposure => GH_Exposure.primary;

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

namespace RhinoInside.Revit.GH.Components
{
  public class DocumentElementTypes : GH_Component, IGH_PersistentElementComponent
  {
    public override Guid ComponentGuid => new Guid("7B00F940-4C6E-4F3F-AB81-C3EED430DE96");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    bool IGH_PersistentElementComponent.NeedsToBeExpired(Autodesk.Revit.DB.Events.DocumentChangedEventArgs e)
    {
      var filter = new Autodesk.Revit.DB.ElementIsElementTypeFilter(false);
      var added = e.GetAddedElementIds(filter);
      if (added.Count > 0)
        return true;

      var modified = e.GetModifiedElementIds(filter);
      if (modified.Count > 0)
        return true;

      var deleted = e.GetDeletedElementIds();
      if (deleted.Count > 0)
      {
        var document = e.GetDocument();
        var empty = new ElementId[0];
        foreach (var param in Params.Output.OfType<Parameters.IGH_PersistentElementParam>())
        {
          if (param.NeedsToBeExpired(document, empty, deleted, empty))
            return true;
        }
      }

      return false;
    }

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
      var categoryId = ElementId.InvalidElementId;
      DA.GetData("FamilyCategory", ref categoryId);

      string familyName = null;
      DA.GetData("FamilyName", ref familyName);

      string name = null;
      DA.GetData("TypeName", ref name);

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        var elementCollector = collector.WhereElementIsElementType();

        if (categoryId != ElementId.InvalidElementId)
          elementCollector = elementCollector.OfCategoryId(categoryId);

        var elementTypes = elementCollector.Cast<ElementType>();

        if (familyName != null)
          elementTypes = elementTypes.Where(x => x.FamilyName == familyName);

        if (name != null)
          elementTypes = elementTypes.Where(x => x.Name == name);

        DA.SetDataList("ElementTypes", elementTypes.Select(x => new Types.ElementType(x)));
      }
    }
  }
}
