using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class ElementFilter : GH_Goo<Autodesk.Revit.DB.ElementFilter>
  {
    public override string TypeName => "Revit Element Filter";
    public override string TypeDescription => "Represents a Revit element filter";
    public override bool IsValid => Value != null;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    public ElementFilter() { }
    public ElementFilter(Autodesk.Revit.DB.ElementFilter filter) : base(filter) { }

    public override bool CastFrom(object source)
    {
      if (source is Autodesk.Revit.DB.ElementFilter filter)
      {
        Value = filter;
        return true;
      }

      return base.CastFrom(source);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.ElementFilter)))
      {
        target = (Q) (object) Value;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public override string ToString()
    {
      if (!IsValid)
        return $"Null {TypeName}";

      return $"Revit {Value.GetType().Name}";
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class ElementFilter : GH_Param<Types.ElementFilter>
  {
    public override Guid ComponentGuid => new Guid("BFCFC49C-747E-40D9-AAEE-93CE06EAAF2B");
    public override GH_Exposure Exposure => GH_Exposure.hidden;
    protected override System.Drawing.Bitmap Icon => ((System.Drawing.Bitmap) Properties.Resources.ResourceManager.GetObject(GetType().Name)) ??
                                                     ImageBuilder.BuildIcon("Y");

    public ElementFilter() : base("ElementFilter", "ElementFilter", "Represents a Revit element filter.", "Params", "Revit", GH_ParamAccess.item) { }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public abstract class ElementFilterComponent : GH_Component
  {
    protected ElementFilterComponent(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBooleanParameter("Inverted", "I", "True if the results of the filter should be inverted", GH_ParamAccess.item, false);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementFilter(), "Filter", "F", string.Empty, GH_ParamAccess.item);
    }
  }

  #region Primary
  public class ElementExclusionFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("396F7E91-7F08-4A3D-9B9B-B6AA91AC0A2B");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override string IconTag => "⊄";

    public ElementExclusionFilter()
    : base("Element.ExclusionFilter", "Exclusion Filter", "Filter used to exclude a set of elements", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Elements", "E", "Elements to exclude", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var elementIds = new List<Autodesk.Revit.DB.ElementId>();
      if (!DA.GetDataList("Elements", elementIds))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.ExclusionFilter(elementIds));
    }
  }

  public class ElementLogicalAndFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("754C40D7-5AE8-4027-921C-0210BBDFAB37");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override string IconTag => "∧";

    public ElementLogicalAndFilter()
    : base("Element.LogicalAndFilter", " Logical And Filter", "Filter used to combine a set of filters that pass when any pass", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementFilter(), "Filters", "F", "Filters to combine", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var filters = new List<Autodesk.Revit.DB.ElementFilter>();
      if (!DA.GetDataList("Filters", filters))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.LogicalAndFilter(filters));
    }
  }

  public class ElementLogicalOrFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("61F75DE1-EE65-4AA8-B9F8-40516BE46C8D");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override string IconTag => "∨";

    public ElementLogicalOrFilter()
    : base("Element.LogicalOrFilter", " Logical Or Filter", "Filter used to combine a set of filters that pass when any pass", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementFilter(), "Filters", "F", "Filters to combine", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var filters = new List<Autodesk.Revit.DB.ElementFilter>();
      if (!DA.GetDataList("Filters", filters))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.LogicalOrFilter(filters));
    }
  }
  #endregion

  #region Secondary
  public class ElementClassFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("6BD34014-CD73-42D8-94DB-658BE8F42254");
    public override GH_Exposure Exposure => GH_Exposure.secondary | GH_Exposure.obscure;
    protected override string IconTag => "C";

    public ElementClassFilter()
    : base("Element.ClassFilter", "Class Filter", "Filter used to match elements by their API class", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddTextParameter("Classes", "C", "Classes to match", GH_ParamAccess.list);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var classNames = new List<string>();
      if (!DA.GetDataList("Classes", classNames))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      try
      {
        var classes = classNames.Select(x => Type.GetType($"{x},RevitAPI", true)).ToList();

        if (classes.Count == 1)
          DA.SetData("Filter", new Autodesk.Revit.DB.ElementClassFilter(classes[0], inverted));
        else
          DA.SetData("Filter", new Autodesk.Revit.DB.ElementMulticlassFilter(classes, inverted));
      }
      catch (System.TypeLoadException e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message.Replace(". ", $".{Environment.NewLine}"));
      }
    }
  }

  public class ElementCategoryFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("D08F7AB1-BE36-45FA-B006-0078022DB140");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override string IconTag => "C";

    public ElementCategoryFilter()
    : base("Element.CategoryFilter", "Category Filter", "Filter used to match elements by their category", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Categories", "C", "Categories to match", GH_ParamAccess.list);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var categoryIds = new List<Autodesk.Revit.DB.ElementId>();
      if (!DA.GetDataList("Categories", categoryIds))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      if (categoryIds.Count == 1)
        DA.SetData("Filter", new Autodesk.Revit.DB.ElementCategoryFilter(categoryIds[0], inverted));
      else
        DA.SetData("Filter", new Autodesk.Revit.DB.ElementMulticategoryFilter(categoryIds, inverted));
    }
  }

  public class ElementLevelFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("B534489B-1367-4ACA-8FD8-D4B365CEEE0D");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override string IconTag => "L";

    public ElementLevelFilter()
    : base("Element.LevelFilter", "Level Filter", "Filter used to match elements associated to the given level", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Level", "L", "Level to match", GH_ParamAccess.item);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var levelId = Autodesk.Revit.DB.ElementId.InvalidElementId;
      if (!DA.GetData("Level", ref levelId))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementLevelFilter(levelId, inverted));
    }
  }

  public class ElementBoundingBoxFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("F5A32842-B18E-470F-8BD3-BAE1373AD982");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override string IconTag => "B";

    public ElementBoundingBoxFilter()
    : base("Element.BoundingBoxFilter", "BoundingBox Filter", "Filter used to match elements by their BoundingBox", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddPointParameter("Points", "C", "Points to query", GH_ParamAccess.list);
      manager.AddNumberParameter("Tolerance", "T", "Tolerance used to query", GH_ParamAccess.item, 0.0);
      manager.AddBooleanParameter("BoundingBox", "B", "Query as a BoundingBox", GH_ParamAccess.item, true);
      manager.AddBooleanParameter("Strict", "S", "True means element should be strictly contained", GH_ParamAccess.item, false);
      base.RegisterInputParams(manager);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      base.RegisterOutputParams(manager);
      manager.AddBoxParameter("Target", "T", string.Empty, GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var points = new List<Rhino.Geometry.Point3d>();
      if (!DA.GetDataList("Points", points))
        return;

      var tolerance = 0.0;
      if (!DA.GetData("Tolerance", ref tolerance))
        return;

      var boundingBox = true;
      if (!DA.GetData("BoundingBox", ref boundingBox))
        return;

      var strict = true;
      if (!DA.GetData("Strict", ref strict))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      var scaleFactor = 1.0 / Revit.ModelUnits;

      var targets = new List<Rhino.Geometry.Box>();
      Autodesk.Revit.DB.ElementFilter filter = null;

      if (boundingBox)
      {
        var pointsBBox = new Rhino.Geometry.BoundingBox(points);
        {
          var box = new Rhino.Geometry.Box(pointsBBox);
          box.Inflate(tolerance);
          targets.Add(box);
        }

        pointsBBox = pointsBBox.Scale(scaleFactor);
        var outline = new Autodesk.Revit.DB.Outline(pointsBBox.Min.ToHost(), pointsBBox.Max.ToHost());

        if (strict)
          filter = new Autodesk.Revit.DB.BoundingBoxIsInsideFilter(outline, tolerance * scaleFactor, inverted);
        else
          filter = new Autodesk.Revit.DB.BoundingBoxIntersectsFilter(outline, tolerance * scaleFactor, inverted);
      }
      else
      {
        var filters = points.Select<Rhino.Geometry.Point3d, Autodesk.Revit.DB.ElementFilter>
                     (x =>
                     {
                        var pointsBBox = new Rhino.Geometry.BoundingBox(x, x);
                        {
                          var box = new Rhino.Geometry.Box(pointsBBox);
                          box.Inflate(tolerance);
                          targets.Add(box);
                        }

                        x = x.Scale(scaleFactor);

                       if (strict)
                       {
                         var outline = new Autodesk.Revit.DB.Outline(x.ToHost(), x.ToHost());
                         return new Autodesk.Revit.DB.BoundingBoxIsInsideFilter(outline, tolerance * scaleFactor, inverted);
                       }
                       else
                       {
                         return new Autodesk.Revit.DB.BoundingBoxContainsPointFilter(x.ToHost(), tolerance * scaleFactor, inverted);
                       }
                     });

        var filterList = filters.ToArray();
        filter = filterList.Length == 1 ?
                 filterList[0] :
                 new Autodesk.Revit.DB.LogicalOrFilter(filterList);
      }

      DA.SetData("Filter", filter);
      DA.SetDataList("Target", targets);
    }
  }
  #endregion
}
