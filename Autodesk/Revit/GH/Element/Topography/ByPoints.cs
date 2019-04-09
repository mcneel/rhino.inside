using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;
using Autodesk.Revit.DB.Architecture;

namespace RhinoInside.Revit.GH.Components
{
  public class TopographyByPoints : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("E8D8D05A-8703-4F75-B106-12B40EC9DF7B");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("T");

    public TopographyByPoints() : base
    (
      "AddTopography.ByPoints", "ByPoints",
      "Given a set of Points, it adds a Topography surface to the active Revit document",
      "Revit", "Model Site"
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
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, points));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      IList<Rhino.Geometry.Point3d> points
    )
    {
      var element = PreviousElement(doc, Iteration);
      try
      {
        if (element?.Pinned ?? true)
        {
          var scaleFactor = 1.0 / Revit.ModelUnits;
          if (scaleFactor != 1.0)
          {
            for (int p = 0; p < points.Count; ++p)
              points[p] = points[p].Scale(scaleFactor);
          }

          element = TopographySurface.Create(doc, points.ToHost());
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
