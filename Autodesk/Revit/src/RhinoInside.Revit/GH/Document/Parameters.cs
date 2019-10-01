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
  public class DocumentParameters : GH_Component
  {
    public override Guid ComponentGuid => new Guid("189F0A94-D077-4B96-8A92-6D5334EF7157");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{K}");

    public DocumentParameters() : base
    (
      "Document.Parameters", "Parameters",
      "Gets a list of valid parameters for the specified category that can be used in a table view",
      "Revit", "Document"
    )
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterKey(), "ParameterKeys", "ParameterKeys", "Parameter definitions list", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      var parameterKeys = TableView.GetAvailableParameters(Revit.ActiveDBDocument, category.Id);
      DA.SetDataList("ParameterKeys", parameterKeys);
    }
  }
}
