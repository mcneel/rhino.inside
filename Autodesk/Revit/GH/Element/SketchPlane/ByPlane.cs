using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class SketchPlane : Element
  {
    public override string TypeName => "Revit SketchPlane";
    public override string TypeDescription => "Represents a Revit sketch plane";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.SketchPlane);
    public static explicit operator Autodesk.Revit.DB.SketchPlane(SketchPlane self)
    {
      return Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.SketchPlane;
    }

    public SketchPlane() : base() { }
    public SketchPlane(Autodesk.Revit.DB.SketchPlane sketchPlane) : base(sketchPlane) { }

    #region Location
    public override Rhino.Geometry.Point3d Location => Plane.Origin;
    public override Rhino.Geometry.Vector3d XAxis => Plane.XAxis;
    public override Rhino.Geometry.Vector3d YAxis => Plane.YAxis;
    public override Rhino.Geometry.Vector3d ZAxis => Plane.ZAxis;
    public override Rhino.Geometry.Plane Plane
    {
      get
      {
        var element = (Autodesk.Revit.DB.SketchPlane) this;
        if (element != null)
          return element.GetPlane().ToRhino().Scale(Revit.ModelUnits);

        return new Rhino.Geometry.Plane(new Rhino.Geometry.Point3d(double.NaN, double.NaN, double.NaN), Rhino.Geometry.Vector3d.Zero, Rhino.Geometry.Vector3d.Zero);
      }
    }
    #endregion
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class SketchPlane : GH_Param<Types.SketchPlane>
  {
    public override Guid ComponentGuid => new Guid("93BF1F61-69AD-433F-A202-352C14E4CED8");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("SP");

    public SketchPlane() : base("SketchPlane", "SketchPlane", "Represents a Revit document sketch plane.", "Revit", "Model", GH_ParamAccess.item) { }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class SketchPlaneByPlane : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("1FA679E4-1821-483A-99F8-DC166B0595F4");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("SP");

    public SketchPlaneByPlane() : base
    (
      "AddSketchPlane.ByPlane", "ByPlane",
      "Given a Plane, it adds a SketchPlane element to the active Revit document",
      "Revit", "Model"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddPlaneParameter("Plane", "P", string.Empty, GH_ParamAccess.item, Rhino.Geometry.Plane.WorldXY);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.SketchPlane(), "SketchPlane", "C", "New SketchPlane", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var plane = default(Rhino.Geometry.Plane);
      DA.GetData("Plane", ref plane);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, plane));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Plane plane
    )
    {
      var element = PreviousElement(doc, Iteration);
      try
      {
        if (!plane.IsValid)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' is not valid.", Params.Input[0].Name));
        }
        else
        {
          var scaleFactor = 1.0 / Revit.ModelUnits;
          if (scaleFactor != 1.0)
            plane = plane.Scale(scaleFactor);

          element = SketchPlane.Create(doc, plane.ToHost());
        }
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
      }
      finally
      {
        ReplaceElement(doc, DA, Iteration, element);
      }
    }
  }
}
