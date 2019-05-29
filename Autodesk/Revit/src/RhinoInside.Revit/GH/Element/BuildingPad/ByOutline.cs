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
  public class BuildingPadByOutline : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("ADE71474-5F00-4BD5-9D1E-D518B42137F2");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public BuildingPadByOutline() : base
    (
      "AddBuildingPad.ByOutline", "ByOutline",
      "Given a set of contour Curves, it adds a BuildingPad element to the active Revit document",
      "Revit", "Site"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Boundaries", "B", string.Empty, GH_ParamAccess.list);
      manager[manager.AddParameter(new Parameters.ElementType(), "Type", "T", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Level", "L", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "BuildingPad", "BP", "New BuildingPad", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var boundaries = new List<Rhino.Geometry.Curve>();
      if (!DA.GetDataList("Boundaries", boundaries))
        return;

      Autodesk.Revit.DB.BuildingPadType buildingPadType = null;
      if (!DA.GetData("Type", ref buildingPadType) && Params.Input[1].Sources.Count == 0)
        buildingPadType = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultElementTypeId(ElementTypeGroup.BuildingPadType)) as BuildingPadType;

      Autodesk.Revit.DB.Level level = null;
      DA.GetData("Level", ref level);
      if (level == null && boundaries.Count != 0)
      {
        var boundaryBBox = Rhino.Geometry.BoundingBox.Empty;
        foreach (var boundary in boundaries.OfType<Rhino.Geometry.Curve>())
          boundaryBBox.Union(boundary.GetBoundingBox(true));

        level = Revit.ActiveDBDocument.FindLevelByElevation(boundaryBBox.Min.Z / Revit.ModelUnits);
      }

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, boundaries, buildingPadType, level));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      IEnumerable<Rhino.Geometry.Curve> boundaries,
      Autodesk.Revit.DB.BuildingPadType buildingPadType,
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
            foreach (var boundary in boundaries)
              boundary.Scale(scaleFactor);
          }

          var curveLoops = boundaries.Select(region => CurveLoop.Create(region.ToHost().SelectMany(x => x.ToBoundedCurves()).ToList()));

          if (buildingPadType == null)
            buildingPadType = BuildingPadType.CreateDefault(Revit.ActiveDBDocument);

          if (element is BuildingPad && buildingPadType.Id != element.GetTypeId())
          {
            var newElmentId = element.ChangeTypeId(buildingPadType.Id);
            if (newElmentId != ElementId.InvalidElementId)
              element = doc.GetElement(newElmentId);
          }

          if (element is BuildingPad buildingPad)
          {
            buildingPad.SetBoundary(curveLoops.ToList());
          }
          else
          {
            element = CopyParametersFrom(BuildingPad.Create(doc, buildingPadType.Id, level.Id, curveLoops.ToList()), element);
          }

          if (element != null)
          {
            var boundaryBBox = Rhino.Geometry.BoundingBox.Empty;
            foreach (var boundary in boundaries)
              boundaryBBox.Union(boundary.GetBoundingBox(true));

            element.get_Parameter(BuiltInParameter.TYPE_WALL_CLOSURE).Set(level.Id);
            element.get_Parameter(BuiltInParameter.LEVEL_PARAM).Set(level.Id);
            element.get_Parameter(BuiltInParameter.BUILDINGPAD_HEIGHTABOVELEVEL_PARAM).Set(boundaryBBox.Min.Z - level.Elevation);
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
