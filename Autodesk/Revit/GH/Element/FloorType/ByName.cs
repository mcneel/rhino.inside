using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class FloorTypeByName : GH_Component
  {
    public override Guid ComponentGuid => new Guid("C2676D07-376E-4881-A48F-9103446ED20F");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("FT");

    public FloorTypeByName() : base(
      "FloorType.ByName", "ByName",
      "Select a FloorType from the Revit document",
      "Revit", "Floors")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "FloorType", "FT", "Requested floor type", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      string name = string.Empty;
      if (!DA.GetData("Name", ref name))
        return;

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        foreach (var floorType in collector.OfClass(typeof(FloorType)).ToElements().Cast<FloorType>())
        {
          if (floorType.Name == name)
          {
            DA.SetData("FloorType", new Types.FloorType(floorType));
            return;
          }
        }
      }
    }
  }
}
