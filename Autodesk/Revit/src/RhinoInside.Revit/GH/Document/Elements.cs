using System;
using System.Linq;
using Grasshopper.Kernel;
using DB = Autodesk.Revit.DB;
namespace RhinoInside.Revit.GH.Components
{
  public class DocumentElements : DocumentComponent
  {
    public override Guid ComponentGuid => new Guid("0F7DA57E-6C05-4DD0-AABF-69E42DF38859");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override DB.ElementFilter ElementFilter => new Autodesk.Revit.DB.ElementIsElementTypeFilter(true);

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
      DA.DisableGapLogic();

      Autodesk.Revit.DB.ElementFilter filter = null;
      if (!DA.GetData("Filter", ref filter))
        return;

      using (var collector = new DB.FilteredElementCollector(Revit.ActiveDBDocument))
      {
        DA.SetDataList
        (
          "Elements",
          collector.
          WherePasses(ElementFilter).
          WherePasses(filter).
          Select(x => Types.Element.FromElement(x))
        );
      }
    }
  }
}
