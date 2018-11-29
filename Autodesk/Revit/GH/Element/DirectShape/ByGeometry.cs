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
  public class DirectShapeByGeometry : GH_TransactionalComponent
  {
    public override Guid ComponentGuid => new Guid("0bfbda45-49cc-4ac6-8d6d-ecd2cfed062a");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("DS");

    public DirectShapeByGeometry() : base
    (
      "DirectShape.ByGeometry", "ByGeometry",
      "Create a DirectShape element from geometry",
      "Revit", "DirectShapes"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddGeometryParameter("Geometry", "G", string.Empty, GH_ParamAccess.list);
      manager[manager.AddParameter(new Parameters.Category(), "Category", "C", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddTextParameter("Name", "N", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "DirectShape", "DS", "New DirectShape", GH_ParamAccess.item);
    }

    List<ElementId> elementId = new List<ElementId>();
    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var geometry = new List<Rhino.Geometry.GeometryBase>();
      if (!DA.GetDataList("Geometry", geometry))
        return;

      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData("Category", ref category))
      {
        if (Params.Input[1].Sources.Count == 0)
          category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, BuiltInCategory.OST_GenericModel);
        else
          return;
      }

      string name = string.Empty;
      DA.GetData("Name", ref name);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, geometry, category, name));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      IEnumerable<Rhino.Geometry.GeometryBase> geometries,
      Autodesk.Revit.DB.Category category,
      string name
    )
    {
      DirectShape ds = null;

      if (!DirectShape.IsValidCategoryId(category.Id, Revit.ActiveDBDocument))
        category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, BuiltInCategory.OST_GenericModel);

      if (geometries != null && category != null)
      {
        foreach (var geometry in geometries.ToHost())
        {
          var shape = new List<GeometryObject>(geometry.Count);

          // DirectShape only accepts those types and no nulls
          foreach (var g in geometry)
          {
            switch (g)
            {
              case Point p: shape.Add(p); break;
              case Curve c: shape.Add(c); break;
              case Solid s: shape.Add(s); break;
              case Mesh m: shape.Add(m); break;
            }
          }

          if (shape.Count > 0)
          {
            ds = Autodesk.Revit.DB.DirectShape.CreateElement(doc, category.Id);
            ds.SetShape(shape);
            ds.Name = name ?? string.Empty;
          }
        }
      }

      ReplaceElement(doc, DA, Iteration, ds);
    }
  }

  public class DirectShapeCategories : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("7BAFE137-332B-481A-BE22-09E8BD4C86FC");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("DSC");

    public DirectShapeCategories()
    {
      Category = "Revit";
      SubCategory = "DirectShapes";
      Name = "DirectShape.Categories";
      NickName = "Categories";
      Description = "Provide a picker of a valid DirectShape category";

      ListItems.Clear();

      var categories = new List<Category>();

      foreach (var item in Revit.ActiveDBDocument.Settings.Categories)
      {
        if (item is Category category)
        {
          if (!DirectShape.IsValidCategoryId(category.Id, Revit.ActiveDBDocument))
            continue;

          categories.Add(category);
        }
      }

      categories = categories.OrderBy(c => c.Name).ToList();

      var genericModel = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, BuiltInCategory.OST_GenericModel);
      foreach (var category in categories)
      {
        ListItems.Add(new GH_ValueListItem(category.Name, category.Id.IntegerValue.ToString()));
        if (category.Id.IntegerValue == (int) BuiltInCategory.OST_GenericModel)
          SelectItem(ListItems.Count - 1);
      }
    }
  }
}
