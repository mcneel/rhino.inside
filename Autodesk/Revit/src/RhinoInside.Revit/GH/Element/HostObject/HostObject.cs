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
