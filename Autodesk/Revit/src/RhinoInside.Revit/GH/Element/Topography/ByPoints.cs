using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using Autodesk.Revit.DB;
using Autodesk.Revit.DB.Architecture;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Components
{
  public class TopographyByPoints : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("E8D8D05A-8703-4F75-B106-12B40EC9DF7B");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public TopographyByPoints() : base
    (
      "AddTopography.ByPoints", "ByPoints",
      "Given a set of Points, it adds a Topography surface to the active Revit document",
      "Revit", "Site"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Topography", "T", "New Topography", GH_ParamAccess.item);
    }

    void ReconstructTopographyByPoints
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      IList<Rhino.Geometry.Point3d> points,
      [Optional] IList<Rhino.Geometry.Curve> regions
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      var xyz = points.Select(x => x.ChangeUnits(scaleFactor).ToHost()).ToArray();

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
        ReplaceElement(ref element, TopographySurface.Create(doc, xyz));
      }

      if (element is object && regions?.Count > 0)
      {
        var curveLoops = regions.Select(region => CurveLoop.Create(region.ChangeUnits(scaleFactor).ToHost().ToArray())).ToArray();
        SiteSubRegion.Create(doc, curveLoops, element.Id);
      }
    }
  }
}
