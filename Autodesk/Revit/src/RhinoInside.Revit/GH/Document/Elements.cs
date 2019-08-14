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
  public class DocumentElements : GH_Component
  {
    public override Guid ComponentGuid => new Guid("0F7DA57E-6C05-4DD0-AABF-69E42DF38859");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public DocumentElements() : base(
      "Document.Elements", "Elements",
      "Get active document model elements list",
      "Revit", "Document")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager[manager.AddParameter(new Parameters.ElementFilter(), "Filter", "F", "Filter", GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Elements", "Elements", "Elements list", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.ElementFilter filter = null;
      DA.GetData("Filter", ref filter);

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        if (filter == null)
        {
          DA.SetDataList
          (
            "Elements",
            collector.WhereElementIsNotElementType().
            GetElementIdIterator().
            Select(x => Types.Element.Make(x))
          );
        }
        else
        {
          DA.SetDataList
          (
            "Elements",
            collector.WhereElementIsNotElementType().
            WherePasses(filter).
            GetElementIdIterator().
            Select(x => Types.Element.Make(x))
          );
        }
      }
    }
  }
}
