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
  public class DocumentLevels : GH_Component
  {
    public override Guid ComponentGuid => new Guid("87715CAF-92A9-4B14-99E5-F8CCB2CC19BD");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{L}");

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
