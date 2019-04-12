using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

using Autodesk.Revit.DB;
using Grasshopper.Kernel.Special;

namespace RhinoInside.Revit.GH.Components
{
  public class FormByCurves : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("42631B6E-505E-4091-981A-E7605AE5A1FF");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("SF");

    public FormByCurves() : base
    (
      "AddForm.ByCurves", "ByCurves",
      "Given a list of curves, it adds a Form element to the active Revit document",
      "Revit", "Mass"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Profiles", "P", string.Empty, GH_ParamAccess.list);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Form", "F", "New Form", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var profiles = new List<Rhino.Geometry.Curve>();
      if (!DA.GetDataList("Profiles", profiles))
        return;

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, profiles));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      List<Rhino.Geometry.Curve> profiles
    )
    {
      var element = PreviousElement(doc, Iteration);
      try
      {
        if (element?.Pinned ?? true)
        {
          if (!Revit.ActiveDBDocument.IsFamilyDocument || !Revit.ActiveDBDocument.OwnerFamily.IsConceptualMassFamily)
          {
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "This component can only run in Conceptual Mass Family editor");
          }
          else if (profiles == null || profiles.Count == 0)
          {
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' must be valid curve list.", Params.Input[0].Name));
          }
          else
          {
            var scaleFactor = 1.0 / Revit.ModelUnits;
            var planes = new List<Rhino.Geometry.Plane>();
            foreach (var profile in profiles)
            {
              if (scaleFactor != 1.0)
                profile.Scale(scaleFactor);

              if (!profile.TryGetPlane(out var plane))
                continue;

              plane.Origin = profile.IsClosed ? Rhino.Geometry.AreaMassProperties.Compute(profile).Centroid : profile.PointAt(profile.Domain.Mid);
              planes.Add(plane);
            }

            if (profiles.Count != planes.Count)
            {
              AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("All curves in '{0}' must be planar.", Params.Input[0].Name));
              element = null;
            }
            else if (profiles.Count == 1)
            {
              var profile = profiles[0];
              var plane = planes[0];

              var sketchPlane = SketchPlane.Create(doc, plane.ToHost());

              var referenceArray = new ReferenceArray();
              foreach (var curve in profile.ToHost())
                referenceArray.Append(new Reference(doc.FamilyCreate.NewModelCurve(curve, sketchPlane)));

              element = doc.FamilyCreate.NewFormByCap
              (
                true,
                referenceArray
              );
            }
            else
            {
              var referenceArrayArray = new ReferenceArrayArray();
              int index = 0;
              foreach (var profile in profiles)
              {
                var sketchPlane = SketchPlane.Create(doc, planes[index++].ToHost());

                var referenceArray = new ReferenceArray();
                foreach (var curve in profile.ToHost())
                  referenceArray.Append(new Reference(doc.FamilyCreate.NewModelCurve(curve, sketchPlane)));

                referenceArrayArray.Append(referenceArray);
              }

              element = doc.FamilyCreate.NewLoftForm(true, referenceArrayArray);
            }
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
