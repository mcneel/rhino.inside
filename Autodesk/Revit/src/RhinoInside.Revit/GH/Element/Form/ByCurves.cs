using System;
using System.Linq;
using System.Collections.Generic;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Components
{
  public class FormByCurves : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("42631B6E-505E-4091-981A-E7605AE5A1FF");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public FormByCurves() : base
    (
      "AddForm.ByCurves", "ByCurves",
      "Given a list of curves, it adds a Form element to the active Revit document",
      "Revit", "Mass"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Form", "F", "New Form", GH_ParamAccess.item);
    }

    void ReconstructFormByCurves
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      IList<Rhino.Geometry.Curve> profiles
    )
    {
      if (!doc.IsFamilyDocument)
        throw new InvalidOperationException("This component can only run in Family editor");

      var scaleFactor = 1.0 / Revit.ModelUnits;
      profiles = profiles.Select(x => x.ChangeUnits(scaleFactor)).ToArray();

      var planes = new List<Rhino.Geometry.Plane>();
      foreach (var profile in profiles)
      {
        if (!profile.TryGetPlane(out var plane))
          ThrowArgumentException(nameof(profiles), "All profiles must be planar");

        plane.Origin = profile.IsClosed ? Rhino.Geometry.AreaMassProperties.Compute(profile).Centroid : profile.PointAtNormalizedLength(0.5);
        planes.Add(plane);
      }

      if (profiles.Count == 1)
      {
        var profile = profiles[0];
        var plane = planes[0];

        using (var sketchPlane = SketchPlane.Create(doc, plane.ToHost()))
        using (var referenceArray = new ReferenceArray())
        {
          foreach (var curve in profile.ToHostMultiple())
            referenceArray.Append(new Reference(doc.FamilyCreate.NewModelCurve(curve, sketchPlane)));

          ReplaceElement(ref element, doc.FamilyCreate.NewFormByCap(true, referenceArray));
        }
      }
      else
      {
        using (var referenceArrayArray = new ReferenceArrayArray())
        {
          int index = 0;
          foreach (var profile in profiles)
          {
            using (var sketchPlane = SketchPlane.Create(doc, planes[index++].ToHost()))
            {
              var referenceArray = new ReferenceArray();

              foreach (var curve in profile.ToHostMultiple())
                referenceArray.Append(new Reference(doc.FamilyCreate.NewModelCurve(curve, sketchPlane)));

              referenceArrayArray.Append(referenceArray);
            }
          }

          ReplaceElement(ref element, doc.FamilyCreate.NewLoftForm(true, referenceArrayArray));
        }
      }
    }
  }
}
