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
  public class RoofByOutline : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("198E152B-6636-4D90-9443-AE77B8B1475E");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("R");

    public RoofByOutline() : base
    (
      "AddRoof.ByOutline", "ByOutline",
      "Given its outline curve, it adds a Roof element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Boundary", "B", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.ElementType(), "Type", "FT", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Level", "L", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Roof", "R", "New Roof", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Curve boundary = null;
      DA.GetData("Boundary", ref boundary);

      Autodesk.Revit.DB.RoofType roofType = null;
      if (!DA.GetData("Type", ref roofType) && Params.Input[1].Sources.Count == 0)
        roofType = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultElementTypeId(ElementTypeGroup.RoofType)) as RoofType;

      Autodesk.Revit.DB.Level level = null;
      DA.GetData("Level", ref level);
      if (level == null && boundary != null)
      {
        var boundaryBBox = boundary.GetBoundingBox(true);
        level = Revit.ActiveDBDocument.FindLevelByElevation(boundaryBBox.Min.Z / Revit.ModelUnits);
      }

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, boundary, roofType, level));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Curve boundary,
      Autodesk.Revit.DB.RoofType roofType,
      Autodesk.Revit.DB.Level level
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
          boundary?.Scale(scaleFactor);
        }

        if
        (
          boundary == null ||
          boundary.IsShort(Revit.ShortCurveTolerance) ||
          !boundary.IsClosed ||
          !boundary.TryGetPlane(out var boundaryPlane, Revit.VertexTolerance) ||
          boundaryPlane.ZAxis.IsParallelTo(Rhino.Geometry.Vector3d.ZAxis) == 0
        )
          throw new Exception(string.Format("Parameter '{0}' must be an horizontal planar closed curve.", Params.Input[0].Name));

        var curveArray = boundary.ToHost().ToCurveArray();
        var footPintToModelCurvesMapping = new ModelCurveArray();
        element = CopyParametersFrom(doc.Create.NewFootPrintRoof(curveArray, level, roofType, out footPintToModelCurvesMapping), element);

        if (element != null)
        {
          var boundaryBBox = boundary.GetBoundingBox(true);
          element.get_Parameter(BuiltInParameter.ROOF_BASE_LEVEL_PARAM).Set(level.Id);
          element.get_Parameter(BuiltInParameter.ROOF_LEVEL_OFFSET_PARAM).Set(boundaryBBox.Min.Z - level.Elevation);
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
