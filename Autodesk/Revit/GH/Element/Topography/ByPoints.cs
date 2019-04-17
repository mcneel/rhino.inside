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
      "Revit", "Site"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddPointParameter("Points", "P", string.Empty, GH_ParamAccess.list);
      manager[manager.AddCurveParameter("Regions", "R", string.Empty, GH_ParamAccess.list)].Optional = true;
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

      var regions = new List<Rhino.Geometry.Curve>();
      DA.GetDataList("Regions", regions);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, points, regions));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      IEnumerable<Rhino.Geometry.Point3d> points,
      IEnumerable<Rhino.Geometry.Curve> regions
    )
    {
      var element = PreviousElement(doc, Iteration);

      if (!element?.Pinned ?? false)
      {
        ReplaceElement(doc, DA, Iteration, element);
      }
      else try
      {
        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
        {
          points = points.Select(p => p * scaleFactor);

          foreach (var region in regions)
            region.Scale(scaleFactor);
        }

        TopographySurface topography = null;
        //if (element is TopographySurface topography)
        //{
        //  using (var editScope = new TopographyEditScope(doc, "TopographyByPoints"))
        //  {
        //    editScope.Start(element.Id);
        //    topography.DeletePoints(topography.GetPoints());
        //    topography.AddPoints(points.ToHost().ToList());

        //    foreach (var subRegionId in topography.GetHostedSubRegionIds())
        //      doc.Delete(subRegionId);

        //    editScope.Commit(new Revit.FailuresPreprocessor());
        //  }
        //}
        //else
        {
          topography = CopyParametersFrom(TopographySurface.Create(doc, points.ToHost().ToList()), element);
          element = topography;
        }

        if (topography != null && regions.Any())
        {
          var curveLoops = regions.Select(region => CurveLoop.Create(region.ToHost().ToList())).ToList();
          SiteSubRegion.Create(doc, curveLoops, topography.Id);
        }

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
