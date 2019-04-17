using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

using Autodesk.Revit.DB;
using Grasshopper.Kernel.Special;

namespace RhinoInside.Revit.GH.Components
{
  public class MeshShapeByMesh : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("5542506A-A09E-4EC9-92B4-F2B52417511C");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("M");

    public MeshShapeByMesh() : base
    (
      "AddMeshShape.ByMesh", "ByMesh",
      "Given a Mesh, it adds a Mesh element to the active Revit document",
      "Revit", "Geometry"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddMeshParameter("Mesh", "M", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Mesh", "M", "New MeshShape", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Mesh mesh = null;
      if (!DA.GetData("Mesh", ref mesh))
        return;

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, (Rhino.Geometry.Mesh) mesh?.DuplicateShallow()));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Mesh mesh
    )
    {
      var element = PreviousElement(doc, Iteration);
      try
      {
        if (mesh == null || !mesh.IsValid)
          throw new Exception(string.Format("Parameter '{0}' must be valid Mesh.", Params.Input[0].Name));

        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
          mesh.Scale(scaleFactor);

        var shape = new List<GeometryObject>();

        foreach (var geometry in mesh.ToHost().SelectMany(x => x.ToDirectShapeGeometry()))
        {
          // DirectShape only accepts those types and no nulls
          switch (geometry)
          {
            case Point p: shape.Add(p); break;
            case Curve c: shape.Add(c); break;
            case Solid s: shape.Add(s); break;
            case Mesh m: shape.Add(m); break;
          }
        }

        var ds = element as DirectShape ?? CopyParametersFrom(DirectShape.CreateElement(doc, new ElementId(BuiltInCategory.OST_GenericModel)), element);
        ds.SetShape(shape);
        element = ds;

        ReplaceElement(doc, DA, Iteration, element);
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
        ReplaceElement(doc, DA, Iteration, null);
      }
    }
  }
}
