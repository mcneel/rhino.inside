using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class DocumentElements : GH_Component, IGH_PersistentElementComponent
  {
    public override Guid ComponentGuid => new Guid("0F7DA57E-6C05-4DD0-AABF-69E42DF38859");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    bool IGH_PersistentElementComponent.NeedsToBeExpired(Autodesk.Revit.DB.Events.DocumentChangedEventArgs e)
    {
      var filter = new Autodesk.Revit.DB.ElementIsElementTypeFilter(true);
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

    public DocumentElements() : base(
      "Document.Elements", "Elements",
      "Get active document model elements list",
      "Revit", "Document")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementFilter(), "Filter", "F", "Filter", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Elements", "Elements", "Elements list", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.ElementFilter filter = null;
      if (!DA.GetData("Filter", ref filter))
        return;

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        DA.SetDataList
        (
          "Elements",
          collector.WhereElementIsNotElementType().
          //WherePasses(new Autodesk.Revit.DB.ElementClassFilter(typeof(Autodesk.Revit.DB.ParameterElement), true)).
          WherePasses(filter).
          Select(x => Types.Element.Make(x))
        );
      }
    }
  }
}
