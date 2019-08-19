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
  public class DocumentLevelsPicker : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("BD6A74F3-8C46-4506-87D9-B34BD96747DA");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public DocumentLevelsPicker()
    {
      Category = "Revit";
      SubCategory = "Input";
      Name = "Document.LevelsPicker";
      MutableNickName = false;
      Description = "Provides a Level picker";

      ListMode = GH_ValueListMode.CheckList;
    }

    void RefreshList()
    {
      var selectedItems = ListItems.Where(x => x.Selected).Select(x => x.Expression).ToList();
      ListItems.Clear();

      if (Revit.ActiveDBDocument != null)
      {
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          foreach (var level in collector.OfClass(typeof(Level)).ToElements().Cast<Level>().OrderByDescending((x) => x.Elevation))
          {
            var item = new GH_ValueListItem(level.Name, level.Id.IntegerValue.ToString());
            item.Selected = selectedItems.Contains(item.Expression);
            ListItems.Add(item);
          }
        }
      }
    }

    protected override void CollectVolatileData_Custom()
    {
      NickName = "Level";
      RefreshList();
      base.CollectVolatileData_Custom();
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class DocumentLevels : GH_Component, IGH_PersistentElementComponent
  {
    public override Guid ComponentGuid => new Guid("87715CAF-92A9-4B14-99E5-F8CCB2CC19BD");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    bool IGH_PersistentElementComponent.NeedsToBeExpired(Autodesk.Revit.DB.Events.DocumentChangedEventArgs e)
    {
      var filter = new Autodesk.Revit.DB.ElementClassFilter(typeof(Level));
      var added = e.GetAddedElementIds(filter);
      if (added.Count > 0)
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

    public DocumentLevels() : base(
      "Document.Levels", "Levels",
      "Get active document levels list",
      "Revit", "Document")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Levels", "Levels", "Levels list", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var levels = new List<Level>();

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        foreach (var level in collector.OfClass(typeof(Level)).ToElements().Cast<Level>())
          levels.Add(level);
      }

      DA.SetDataList("Levels", levels);
    }
  }
}
