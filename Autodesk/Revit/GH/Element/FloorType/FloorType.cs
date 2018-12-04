using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using GH_IO.Serialization;

using RhinoInside.Revit;
using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  class FloorType : Element
  {
    public override string TypeName => "Revit FloorType";
    public override string TypeDescription => "Represents a Revit floor type";

    public FloorType(Autodesk.Revit.DB.FloorType floorType) : base(floorType) { }
  }
}
