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
  public class GridByCurve : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("CEC2B3DF-C6BA-414F-BECE-E3DAEE2A3F2C");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public GridByCurve() : base
    (
      "AddGrid.ByElevation", "ByCurve",
      "Given its Axis, it adds a Grid element to the active Revit document",
      "Revit", "Datum"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Curve", "C", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.ElementType(), "Type", "T", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Grid", "G", "New Grid", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Curve axis = null;
      DA.GetData("Curve", ref axis);

      GridType gridType = null;
      if (!DA.GetData("Type", ref gridType) && Params.Input[1].Sources.Count == 0)
        gridType = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultElementTypeId(ElementTypeGroup.GridType)) as GridType;

      if (gridType == null)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' There is no default level type loaded.", Params.Input[1].Name));
        DA.AbortComponentSolution();
        return;
      }

      string name = null;
      DA.GetData("Name", ref name);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, axis, gridType));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Curve axis,
      GridType gridType
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
          axis.Scale(scaleFactor);
        }

        {
          if (axis is Rhino.Geometry.PolyCurve polycurve && polycurve.SegmentCount == 1)
              axis = polycurve.SegmentCurve(0);

          if (axis is Rhino.Geometry.LineCurve line)
            element = CopyParametersFrom(Grid.Create(doc, line.ToHost()), element);
          else if (axis is Rhino.Geometry.ArcCurve arc)
            element = CopyParametersFrom(Grid.Create(doc, arc.ToHost()), element);
          else using (var curveLoop = new CurveLoop())
               using (var polyline = axis.ToArcsAndLines(Revit.VertexTolerance * 10.0, Revit.AngleTolerance, Revit.ShortCurveTolerance, double.PositiveInfinity))
          {
            int count = polyline.SegmentCount;
            for(int s = 0; s < count; ++s)
            {
              var segment = polyline.SegmentCurve(s);

              if (segment is Rhino.Geometry.LineCurve l)
                curveLoop.Append(l.ToHost());
              else if (segment is Rhino.Geometry.ArcCurve a)
                curveLoop.Append(a.ToHost());
              else
                throw new ArgumentException();
            }

            axis.TryGetPlane(out var plane);
            var sketchPlane = SketchPlane.Create(doc, plane.ToHost());

            element = CopyParametersFrom(doc.GetElement(MultiSegmentGrid.Create(doc, gridType.Id, curveLoop, sketchPlane.Id)), element);
          }
        }

        if (gridType.Id != element.GetTypeId())
        {
          var newElmentId = element.ChangeTypeId(gridType.Id);
          if (newElmentId != ElementId.InvalidElementId)
            element = doc.GetElement(newElmentId);
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
