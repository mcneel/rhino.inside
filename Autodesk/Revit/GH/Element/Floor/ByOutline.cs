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
  public class FloorByOutline : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("DC8DAF4F-CC93-43E2-A871-3A01A920A722");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("F");

    public FloorByOutline() : base
    (
      "AddFloor.ByOutline", "ByOutline",
      "Given its outline curve, it adds a Floor element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Boundary", "B", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.ElementType(), "Type", "FT", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Level", "L", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager.AddBooleanParameter("Structural", "S", string.Empty, GH_ParamAccess.item, true);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Floor", "F", "New Floor", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Curve boundary = null;
      DA.GetData("Boundary", ref boundary);

      Autodesk.Revit.DB.FloorType floorType = null;
      if (!DA.GetData("Type", ref floorType) && Params.Input[1].Sources.Count == 0)
        floorType = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultElementTypeId(ElementTypeGroup.FloorType)) as FloorType;

      Autodesk.Revit.DB.Level level = null;
      DA.GetData("Level", ref level);
      if (level == null && boundary != null)
      {
        var boundaryBBox = boundary.GetBoundingBox(true);
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          foreach (var levelN in collector.OfClass(typeof(Level)).ToElements().Cast<Level>().OrderBy(c => c.Elevation))
          {
            if (level == null)
              level = levelN;
            else if (boundaryBBox.Min.Z >= levelN.Elevation)
              level = levelN;
          }
        }
      }

      bool structural = true;
      DA.GetData("Structural", ref structural);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, boundary, floorType, level, structural));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Curve boundary,
      Autodesk.Revit.DB.FloorType floorType,
      Autodesk.Revit.DB.Level level,
      bool structural
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

        if (floorType.IsFoundationSlab)
          element = CopyParametersFrom(doc.Create.NewFoundationSlab(curveArray, floorType, level, structural, XYZ.BasisZ), element);
        else
          element = CopyParametersFrom(doc.Create.NewFloor(curveArray, floorType, level, structural, XYZ.BasisZ), element);

        if (element != null)
        {
          var boundaryBBox = boundary.GetBoundingBox(true);
          element.get_Parameter(BuiltInParameter.LEVEL_PARAM).Set(level.Id);
          element.get_Parameter(BuiltInParameter.FLOOR_HEIGHTABOVELEVEL_PARAM).Set(boundaryBBox.Min.Z - level.Elevation);
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
