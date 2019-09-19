using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI.Selection;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class HostObject : Element
  {
    public override string TypeName => "Revit Host element";
    public override string TypeDescription => "Represents a Revit host element";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.HostObject);
    public static explicit operator Autodesk.Revit.DB.HostObject(HostObject self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.HostObject;

    public HostObject() { }
    public HostObject(Autodesk.Revit.DB.HostObject host) : base(host) { }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class HostObject : GeometricElementT<Types.HostObject>
  {
    public override GH_Exposure Exposure => GH_Exposure.primary;
    public override Guid ComponentGuid => new Guid("E3462915-3C4D-4864-9DD4-5A73F91C6543");

    public HostObject() : base("Host", "Host", "Represents a Revit document host element.", "Params", "Revit") { }

    public override bool AllowElement(Autodesk.Revit.DB.Element elem) => elem is Autodesk.Revit.DB.HostObject;
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class HostObjectGetFaces : Component
  {
    public override Guid ComponentGuid => new Guid("032AD3F7-9E55-44B6-BE79-3DBF67D98F14");
    protected override string IconTag => "F";

    public HostObjectGetFaces()
    : base("HostObject.GetFaces", "HostObject.GetFaces", "Obtains a set of types that are owned by Family", "Revit", "Host")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.HostObject(), "Host", "H", "Host object to query for its faces", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Face(), "Bottom", "B", string.Empty, GH_ParamAccess.list);
      manager.AddParameter(new Parameters.Face(), "Top", "T", string.Empty, GH_ParamAccess.list);
      manager.AddParameter(new Parameters.Face(), "Interior", "I", string.Empty, GH_ParamAccess.list);
      manager.AddParameter(new Parameters.Face(), "Exterior", "E", string.Empty, GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.HostObject host = null;
      if (!DA.GetData("Host", ref host) || host is null)
        return;

      var doc = Revit.ActiveDBDocument;
      try
      {
        var bottom = HostObjectUtils.GetBottomFaces(host).Select(reference => new Types.Face(reference, doc));
        DA.SetDataList("Bottom", bottom);
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException) { }

      try
      {
        var top = HostObjectUtils.GetTopFaces(host).Select(reference => new Types.Face(reference, doc));
        DA.SetDataList("Top", top);
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException) { }

      try
      {
        var interior = HostObjectUtils.GetSideFaces(host, ShellLayerType.Interior).Select(reference => new Types.Face(reference, doc));
        DA.SetDataList("Interior", interior);
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException) { }

      try
      {
        var exterior = HostObjectUtils.GetSideFaces(host, ShellLayerType.Exterior).Select(reference => new Types.Face(reference, doc));
        DA.SetDataList("Exterior", exterior);
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException) { }
    }
  }
}
