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
  public class BeamByCurve : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("26411AA6-8187-49DF-A908-A292A07918F1");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public BeamByCurve() : base
    (
      "AddBeam.ByCurve", "ByCurve",
      "Given its Axis, it adds a Beam element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Axis", "A", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.ElementType(), "Type", "T", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Level", "L", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Beam", "B", "New Beam", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Curve axis = null;
      DA.GetData("Axis", ref axis);

      FamilySymbol familySymbol = null;
      if (!DA.GetData("Type", ref familySymbol) && Params.Input[1].Sources.Count == 0)
        familySymbol = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultFamilyTypeId(new ElementId(BuiltInCategory.OST_StructuralFraming))) as FamilySymbol;

      if (familySymbol == null)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' There is no default structural framing family loaded.", Params.Input[1].Name));
        DA.AbortComponentSolution();
        return;
      }

      Autodesk.Revit.DB.Level level = null;
      DA.GetData("Level", ref level);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, axis, familySymbol, level));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Curve curve,
      Autodesk.Revit.DB.FamilySymbol familySymbol,
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
        if (!familySymbol.IsActive)
          familySymbol.Activate();

        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
        {
          curve?.Scale(scaleFactor);
        }

        if
        (
          curve == null ||
          curve.IsShort(Revit.ShortCurveTolerance) ||
          curve.IsClosed ||
          !curve.TryGetPlane(out var axisPlane, Revit.VertexTolerance) ||
          curve.GetNextDiscontinuity(Rhino.Geometry.Continuity.C1_continuous, curve.Domain.Min, curve.Domain.Max, out double discontinuity)
        )
          throw new Exception(string.Format("Parameter '{0}' must be a C1 continuous planar non closed curve.", Params.Input[0].Name));

        var axisList = curve.ToHost().ToList();
        Debug.Assert(axisList.Count == 1);

        if (element is FamilyInstance && familySymbol.Id != element.GetTypeId())
        {
          var newElmentId = element.ChangeTypeId(familySymbol.Id);
          if (newElmentId != ElementId.InvalidElementId)
            element = doc.GetElement(newElmentId);
        }

        if (element is FamilyInstance familyInstance && element.Location is LocationCurve locationCurve)
        {
          locationCurve.Curve = axisList[0];
        }
        else
        {
          element = CopyParametersFrom(doc.Create.NewFamilyInstance(axisList[0], familySymbol, level, Autodesk.Revit.DB.Structure.StructuralType.Beam), element);
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
