using System;
using System.Collections.Generic;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Components
{
  public class DirectShapeByPoint : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("7A889B89-C423-4ED8-91D9-5CECE1EE803D");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public DirectShapeByPoint() : base
    (
      "AddDirectShape.ByPoint", "ByPoint",
      "Given a Point, it adds a Point shape to the active Revit document",
      "Revit", "Geometry"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Point", "P", "New PointShape", GH_ParamAccess.item);
    }

    void ReconstructDirectShapeByPoint
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Point3d point
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      ThrowIfNotValid(nameof(point), point);

      if (element is DirectShape ds) { }
      else ds = DirectShape.CreateElement(doc, new ElementId(BuiltInCategory.OST_GenericModel));

      ds.SetShape(new List<GeometryObject> { Point.Create((point * scaleFactor).ToHost()) });

      ReplaceElement(ref element, ds);
    }
  }
}
