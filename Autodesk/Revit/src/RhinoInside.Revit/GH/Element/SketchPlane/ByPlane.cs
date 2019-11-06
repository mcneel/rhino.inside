using System;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Components
{
  public class SketchPlaneByPlane : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("1FA679E4-1821-483A-99F8-DC166B0595F4");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public SketchPlaneByPlane() : base
    (
      "AddSketchPlane.ByPlane", "ByPlane",
      "Given a Plane, it adds a SketchPlane element to the active Revit document",
      "Revit", "Model"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.SketchPlane(), "SketchPlane", "P", "New SketchPlane", GH_ParamAccess.item);
    }

    void ReconstructSketchPlaneByPlane
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Plane plane
    )
    {
      if (!plane.IsValid)
        ThrowArgumentException(nameof(plane), "Plane is not valid.");

      var scaleFactor = 1.0 / Revit.ModelUnits;
      plane = plane.ChangeUnits(scaleFactor);

      if (element is SketchPlane sketchPlane)
      {
        bool pinned = element.Pinned;
        element.Pinned = false;

        var plane0 = sketchPlane.GetPlane();
        using (var plane1 = plane.ToHost())
        {
          if (!plane0.Normal.IsParallelTo(plane1.Normal))
          {
            var axisDirection = plane0.Normal.CrossProduct(plane1.Normal);
            double angle = plane0.Normal.AngleTo(plane1.Normal);

            using (var axis = Line.CreateUnbound(plane0.Origin, axisDirection))
              ElementTransformUtils.RotateElement(doc, element.Id, axis, angle);

            plane0 = sketchPlane.GetPlane();
          }

          {
            double angle = plane0.XVec.AngleOnPlaneTo(plane1.XVec, plane1.Normal);
            if (angle != 0.0)
            {
              using (var axis = Line.CreateUnbound(plane0.Origin, plane1.Normal))
                ElementTransformUtils.RotateElement(doc, element.Id, axis, angle);
            }
          }

          var trans = plane1.Origin - plane0.Origin;
          if (!trans.IsZeroLength())
            ElementTransformUtils.MoveElement(doc, element.Id, trans);
        }

        element.Pinned = pinned;
      }
      else
        ReplaceElement(ref element, SketchPlane.Create(doc, plane.ToHost()));
    }
  }
}
