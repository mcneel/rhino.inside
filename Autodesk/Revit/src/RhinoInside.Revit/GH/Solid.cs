using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Parameters;

namespace RhinoInside.Revit.GH.Components
{
  public class BrepIsSolid : GH_Component
  {
    public override Guid ComponentGuid => new Guid("ACF07D2E-7204-430D-8352-13AF35E08365");
    public override GH_Exposure Exposure => GH_Exposure.secondary | GH_Exposure.obscure;

    public BrepIsSolid()
    : base("Is Solid", "Is Solid", "Test whether a Brep is solid, and it's orientation", "Surface", "Analysis")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", "Brep to check for its solid orientation", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddNumberParameter("Orientation", "O", "None=0, OutWard=1, Inward=-1", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Brep brep = null;
      if (!DA.GetData(0, ref brep))
        return;

      var orientation = brep?.SolidOrientation ?? Rhino.Geometry.BrepSolidOrientation.Unknown;
      if (orientation == Rhino.Geometry.BrepSolidOrientation.Unknown)
        return;

      DA.SetData(0, orientation);
     }
  }

  public class BrepSetOrientation : GH_Component
  {
    public override Guid ComponentGuid => new Guid("9FB0E42C-BF47-418E-8A69-21D1927C66C0");
    public override GH_Exposure Exposure => GH_Exposure.quarternary | GH_Exposure.obscure;

    public BrepSetOrientation()
    : base("Set Orientation", "Set Orientation", "Sets a Brep solid orientation", "Surface", "Util")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", "Brep to set its solid orientation", GH_ParamAccess.item);
      var param = manager[manager.AddIntegerParameter("Orientation", "O", "Outward=1, Inward=-1", GH_ParamAccess.item)];

      if (param is Param_Integer orientation)
      {
        orientation.AddNamedValue("Outward", (int) Rhino.Geometry.BrepSolidOrientation.Outward);
        orientation.AddNamedValue("Inward", (int) Rhino.Geometry.BrepSolidOrientation.Inward);
      }
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", string.Empty, GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Brep brep = null;
      if (!DA.GetData(0, ref brep))
        return;

      var orientationValue = (int) Rhino.Geometry.BrepSolidOrientation.Unknown;
      if (!DA.GetData(1, ref orientationValue))
        return;

      var orientation = (Rhino.Geometry.BrepSolidOrientation) orientationValue;
      if (orientation == Rhino.Geometry.BrepSolidOrientation.Unknown)
        return;

      if (orientation != Rhino.Geometry.BrepSolidOrientation.None)
      {
        if (orientation != brep.SolidOrientation)
          brep.Flip();
      }

      DA.SetData(0, brep);
    }
  }
}
