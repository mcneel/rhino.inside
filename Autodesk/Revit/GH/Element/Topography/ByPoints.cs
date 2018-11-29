using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class TopographyByPoints : GH_TransactionalComponent
  {
    public override Guid ComponentGuid => new Guid("E8D8D05A-8703-4F75-B106-12B40EC9DF7B");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("T");

    public TopographyByPoints() : base
    (
      "Topography.ByPoints", "ByPoints",
      "Create a Topography surface from points",
      "Revit", "Topography"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddPointParameter("Points", "P", string.Empty, GH_ParamAccess.list);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Topography", "T", "New Topography", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var points = new List<Rhino.Geometry.Point3d>();
      if (!DA.GetDataList("Points", points))
        return;

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, points.ToHost()));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      IList<XYZ> xyz
    )
    {
      var topography = Autodesk.Revit.DB.Architecture.TopographySurface.Create(doc, xyz);

      ReplaceElement(doc, DA, Iteration, topography);
    }
  }
}
