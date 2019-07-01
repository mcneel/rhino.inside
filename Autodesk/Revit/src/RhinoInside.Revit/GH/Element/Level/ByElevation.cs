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
  public class LevelByElevation : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("C6DEC111-EAC6-4047-8618-28EE144D55C5");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public LevelByElevation() : base
    (
      "AddLevel.ByElevation", "ByElevation",
      "Given its Elevation, it adds a Level to the active Revit document",
      "Revit", "Datum"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddNumberParameter("Elevation", "E", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.ElementType(), "Type", "T", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Level", "L", "New Level", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      LevelType levelType = null;
      if (!DA.GetData("Type", ref levelType) && Params.Input[1].Sources.Count == 0)
        levelType = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultElementTypeId(ElementTypeGroup.LevelType)) as LevelType;

      if (levelType == null)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' There is no default level type loaded.", Params.Input[1].Name));
        DA.AbortComponentSolution();
        return;
      }

      double elevation = 0.0;
      DA.GetData("Elevation", ref elevation);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, elevation, levelType));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      double elevation,
      LevelType levelType
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
          elevation *= scaleFactor;
        }

        if (element is Level level)
        {
          level.Elevation = elevation;
        }
        else
        {
          element = CopyParametersFrom(Level.Create(doc, elevation), element);
        }

        if (levelType.Id != element.GetTypeId())
        {
          var newElmentId = element.ChangeTypeId(levelType.Id);
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
