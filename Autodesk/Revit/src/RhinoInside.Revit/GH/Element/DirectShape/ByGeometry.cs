using System;
using System.Collections.Generic;
using System.Linq;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;
using Grasshopper.Kernel.Types;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Parameters
{
  public class DirectShapeCategories : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("7BAFE137-332B-481A-BE22-09E8BD4C86FC");
    public override GH_Exposure Exposure => GH_Exposure.secondary;

    public DirectShapeCategories()
    {
      Category = "Revit";
      SubCategory = "Build";
      Name = "DirectShape.Categories";
      NickName = "Categories";
      Description = "Provides a picker of a valid DirectShape category";

      ListItems.Clear();

      var ActiveDBDocument = Revit.ActiveDBDocument;
      if (ActiveDBDocument == null)
        return;

      var genericModel = Autodesk.Revit.DB.Category.GetCategory(ActiveDBDocument, BuiltInCategory.OST_GenericModel);

      var directShapeCategories = ActiveDBDocument.Settings.Categories.Cast<Autodesk.Revit.DB.Category>().Where((x) => DirectShape.IsValidCategoryId(x.Id, ActiveDBDocument));
      foreach (var group in directShapeCategories.GroupBy((x) => x.CategoryType).OrderBy((x) => x.Key))
      {
        foreach (var category in group.OrderBy(x => x.Name))
        {
          ListItems.Add(new GH_ValueListItem(category.Name, category.Id.IntegerValue.ToString()));
          if (category.Id.IntegerValue == (int) BuiltInCategory.OST_GenericModel)
            SelectItem(ListItems.Count - 1);
        }
      }
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class DirectShapeByGeometry : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("0bfbda45-49cc-4ac6-8d6d-ecd2cfed062a");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public DirectShapeByGeometry() : base
    (
      "AddDirectShape.ByGeometry", "ByGeometry",
      "Given its Geometry, it adds a DirectShape element to the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "DirectShape", "DS", "New DirectShape", GH_ParamAccess.item);
    }

    void ReconstructDirectShapeByGeometry
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      IList<IGH_GeometricGoo> geometry,
      Optional<Autodesk.Revit.DB.Category> category,
      Optional<string> name
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;

      SolveOptionalCategory(ref category, doc, BuiltInCategory.OST_GenericModel, nameof(geometry));

      if(name == Optional.Nothig && geometry.Count == 1 && (geometry[0]?.IsReferencedGeometry ?? false))
        name = Rhino.RhinoDoc.ActiveDoc.Objects.FindId(geometry[0].ReferenceID)?.Name;

      if (element is DirectShape ds && ds.Category.Id == category.Value.Id) { }
      else ds = DirectShape.CreateElement(doc, new ElementId(BuiltInCategory.OST_GenericModel));

      var shape = geometry.
                  Select(x => AsGeometryBase(x)).
                  Select(x => { ThrowIfNotValid(nameof(geometry), x); return x; }).
                  SelectMany(x => x.ToHost(scaleFactor)).
                  SelectMany(x => x.ToDirectShapeGeometry());

      ds.SetShape(shape.ToList());

      ds.Name = name.IsNullOrNothing ? string.Empty : name.Value;

      ReplaceElement(ref element, ds);
    }

    Rhino.Geometry.GeometryBase AsGeometryBase(IGH_GeometricGoo obj)
    {
      var scriptVariable = obj.ScriptVariable();
      switch (scriptVariable)
      {
        case Rhino.Geometry.Point3d point: return new Rhino.Geometry.Point(point);
        case Rhino.Geometry.Line line: return new Rhino.Geometry.LineCurve(line);
        case Rhino.Geometry.Rectangle3d rect: return rect.ToNurbsCurve();
        case Rhino.Geometry.Arc arc: return new Rhino.Geometry.ArcCurve(arc);
        case Rhino.Geometry.Circle circle: return new Rhino.Geometry.ArcCurve(circle);
        case Rhino.Geometry.Ellipse ellipse: return ellipse.ToNurbsCurve();
        case Rhino.Geometry.Box box: return box.ToBrep();
      }

      return scriptVariable as Rhino.Geometry.GeometryBase;
    }
  }
}
