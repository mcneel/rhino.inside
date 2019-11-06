using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class ElementPassport : Component
  {
    public override Guid ComponentGuid => new Guid("BD534A54-B7ED-4D56-AA53-1F446D445DF6");
    public override GH_Exposure Exposure => GH_Exposure.secondary | GH_Exposure.obscure;
    protected override string IconTag => "ID";

    public ElementPassport()
    : base("Element.Passport", "Element.Passport", string.Empty, "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Grasshopper.Kernel.Parameters.Param_Guid(), "DocumentGUID", "GUID", "A unique identifier for the document the Element resides", GH_ParamAccess.item);
      manager.AddParameter(new Grasshopper.Kernel.Parameters.Param_FilePath(), "DocumentPath", "Path", "The path of the document's disk file", GH_ParamAccess.item);
      manager.AddTextParameter("UniqueID", "UUID", "A stable across upgrades and workset operations unique identifier for the Element", GH_ParamAccess.item);
      manager.AddIntegerParameter("Id", "ID", "A unique identifier for an Element within the document that contains it", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var reference = default(Types.ID);
      if (!DA.GetData("Element", ref reference))
        return;

      DA.SetData("DocumentGUID", reference?.DocumentGUID);
      DA.SetData("DocumentPath", reference?.Document.GetFilePath());
      DA.SetData("UniqueID", reference?.UniqueID);
      DA.SetData("Id", reference?.Id.IntegerValue);
    }
  }
}
