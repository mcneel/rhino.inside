using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class ElementType : Element
  {
    public override string TypeName => "Revit ElementType";
    public override string TypeDescription => "Represents a Revit element type";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.ElementType);
    public static explicit operator Autodesk.Revit.DB.ElementType(ElementType self)
    {
      return Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.ElementType;
    }

    public ElementType() { }
    public ElementType(Autodesk.Revit.DB.ElementType elementType) : base(elementType) { }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class ElementType : GH_Param<Types.ElementType>
  {
    public override Guid ComponentGuid => new Guid("97DD546D-65C3-4D00-A609-3F5FBDA67142");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("T");

    public ElementType() : base("ElementType", "ElementType", "Represents a Revit document element type.", "Revit", "Element", GH_ParamAccess.item) { }
  }
}
