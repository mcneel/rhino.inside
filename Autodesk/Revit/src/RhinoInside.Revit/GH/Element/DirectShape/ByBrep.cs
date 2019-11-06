using System;
using System.Linq;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Components
{
  public class DirectShapeByBrep : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("5ADE9AE3-588C-4285-ABC5-09DEB92C6660");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public DirectShapeByBrep() : base
    (
      "AddDirectShape.ByBrep", "ByBrep",
      "Given a Brep, it adds a Brep shape to the active Revit document",
      "Revit", "Geometry"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Brep", "B", "New BrepShape", GH_ParamAccess.item);
    }

    void ReconstructDirectShapeByBrep
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      Rhino.Geometry.Brep brep
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      ThrowIfNotValid(nameof(brep), brep);

      if (element is DirectShape ds) { }
      else ds = DirectShape.CreateElement(doc, new ElementId(BuiltInCategory.OST_GenericModel));

      var shape = brep.
                  ToHostMultiple(scaleFactor).
                  SelectMany(x => x.ToDirectShapeGeometry());

      ds.SetShape(shape.ToList());

      ReplaceElement(ref element, ds);
    }
  }
}
