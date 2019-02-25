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
  public class ColumnByCurve : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("47B560AC-1E1D-4576-9F17-BCCF612974D8");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("C");

    public ColumnByCurve() : base
    (
      "Column.ByCurve", "ByCurve",
      "Create a structural Column from a curve",
      "Revit", "Build"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddLineParameter("Axis", "A", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.ElementType(), "Type", "T", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Level", "L", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Column", "C", "New Column", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var axis = Rhino.Geometry.Line.Unset;
      if (DA.GetData("Axis", ref axis))
      {
        if (axis.FromZ > axis.ToZ)
          axis.Flip();
      }

      FamilySymbol familySymbol = null;
      if (!DA.GetData("Type", ref familySymbol) && Params.Input[1].Sources.Count == 0)
        familySymbol = Revit.ActiveDBDocument.GetElement(Revit.ActiveDBDocument.GetDefaultFamilyTypeId(new ElementId(BuiltInCategory.OST_StructuralColumns))) as FamilySymbol;

      if (!familySymbol.IsActive)
        familySymbol.Activate();

      Autodesk.Revit.DB.Level level = null;
      DA.GetData("Level", ref level);
      if (level == null)
      {
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          foreach (var levelN in collector.OfClass(typeof(Level)).ToElements().Cast<Level>().OrderBy(c => c.Elevation))
          {
            if (level == null)
              level = levelN;
            else if (axis.FromZ > levelN.Elevation)
              level = levelN;
          }
        }
      }

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, axis, familySymbol, level));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Line line,
      Autodesk.Revit.DB.FamilySymbol familySymbol,
      Autodesk.Revit.DB.Level level
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
            line = line.Scale(scaleFactor);
          }

          if (line.Length < Revit.ShortCurveTolerance)
          {
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' is too short.", Params.Input[0].Name));
          }
          else if (level == null)
          {
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' is mandatory.", Params.Input[2].Name));
          }
          else
          {
            element = doc.Create.NewFamilyInstance(line.ToHost(), familySymbol, level, Autodesk.Revit.DB.Structure.StructuralType.Column);
          }
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
