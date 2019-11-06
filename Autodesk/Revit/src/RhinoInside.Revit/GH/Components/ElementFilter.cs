using System;
using System.Collections.Generic;
using System.Linq;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class ElementFilter : GH_Goo<DB.ElementFilter>
  {
    public override string TypeName => "Revit Element Filter";
    public override string TypeDescription => "Represents a Revit element filter";
    public override bool IsValid => Value?.IsValidObject ?? false;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    public ElementFilter() { }
    public ElementFilter(DB.ElementFilter filter) : base(filter) { }

    public override bool CastFrom(object source)
    {
      if (source is DB.ElementFilter filter)
      {
        Value = filter;
        return true;
      }

      return base.CastFrom(source);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(DB.ElementFilter)))
      {
        target = (Q) (object) Value;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public override string ToString()
    {
      if (!IsValid)
        return $"Invalid {TypeName}";

      return $"{Value.GetType().Name}";
    }
  }

  public class FilterRule : GH_Goo<DB.FilterRule>
  {
    public override string TypeName => "Revit Filter Rule";
    public override string TypeDescription => "Represents a Revit filter rule";
    public override bool IsValid => Value?.IsValidObject ?? false;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    public FilterRule() { }
    public FilterRule(DB.FilterRule filter) : base(filter) { }

    public override bool CastFrom(object source)
    {
      if (source is DB.FilterRule rule)
      {
        Value = rule;
        return true;
      }

      return base.CastFrom(source);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(DB.FilterRule)))
      {
        target = (Q) (object) Value;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public override string ToString()
    {
      if (!IsValid)
        return $"Invalid {TypeName}";

      return $"{Value.GetType().Name}";
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

  public class FilterRule : GH_Param<Types.FilterRule>
  {
    public override Guid ComponentGuid => new Guid("F08E1292-F855-48C7-9921-BD12EF0F67D2");
    public override GH_Exposure Exposure => GH_Exposure.hidden;
    protected override System.Drawing.Bitmap Icon => ((System.Drawing.Bitmap) Properties.Resources.ResourceManager.GetObject(GetType().Name)) ??
                                                     ImageBuilder.BuildIcon("R");

    public FilterRule() : base("FilterRule", "FilterRule", "Represents a Revit filter rule.", "Params", "Revit", GH_ParamAccess.item) { }
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
      var elementIds = new List<DB.ElementId>();
      if (!DA.GetDataList("Elements", elementIds))
        return;

      var ids = elementIds.Where(x => x is object).ToArray();
      if (ids.Length > 0)
        DA.SetData("Filter", new DB.ExclusionFilter(ids));
      else
        DA.DisableGapLogic();
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
      var filters = new List<DB.ElementFilter>();
      if (!DA.GetDataList("Filters", filters))
        return;

      DA.SetData("Filter", new DB.LogicalAndFilter(filters));
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
      var filters = new List<DB.ElementFilter>();
      if (!DA.GetDataList("Filters", filters))
        return;

      DA.SetData("Filter", new DB.LogicalOrFilter(filters));
    }
  }
  #endregion

  #region Secondary
  public class ElementExcludeElementTypeFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("F69D485F-B262-4297-A496-93F5653F5D19");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override string IconTag => "T";

    public ElementExcludeElementTypeFilter()
    : base("Element.ExcludeElementType", "Exclude ElementType Filter", "Filter used to exclude element types", "Revit", "Filter")
    { }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new DB.ElementIsElementTypeFilter(!inverted));
    }
  }

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
          DA.SetData("Filter", new DB.ElementClassFilter(classes[0], inverted));
        else
          DA.SetData("Filter", new DB.ElementMulticlassFilter(classes, inverted));
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
      var categoryIds = new List<DB.ElementId>();
      if (!DA.GetDataList("Categories", categoryIds))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      var ids = categoryIds.Select(x => x is null ? DB.ElementId.InvalidElementId : x).ToArray();
      if (ids.Length > 0)
      {
        if (ids.Length == 1)
          DA.SetData("Filter", new DB.ElementCategoryFilter(ids[0], inverted));
        else
          DA.SetData("Filter", new DB.ElementMulticategoryFilter(ids, inverted));
      }
      else DA.DisableGapLogic();
    }
  }

  public class ElementTypeFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("4434C470-4CAF-4178-929D-284C3B5A24B5");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override string IconTag => "T";

    public ElementTypeFilter()
    : base("Element.TypeFilter", "Type Filter", "Filter used to match elements by their type", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "Types", "T", "Types to match", GH_ParamAccess.list);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var typeIds = new List<DB.ElementId>();
      if (!DA.GetDataList("Types", typeIds))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      var provider = new DB.ParameterValueProvider(new DB.ElementId(DB.BuiltInParameter.ELEM_TYPE_PARAM));
      if (typeIds.Count == 1)
      {
        var rule = new DB.FilterElementIdRule(provider, new DB.FilterNumericEquals(), typeIds[0]);
        DA.SetData("Filter", new DB.ElementParameterFilter(rule, inverted));
      }
      else
      {
        if (inverted)
        {
          var rules = typeIds.Select(x => new DB.FilterInverseRule(new DB.FilterElementIdRule(provider, new DB.FilterNumericEquals(), x))).ToArray();
          DA.SetData("Filter", new DB.ElementParameterFilter(rules));
        }
        else
        {
          var filters = typeIds.Select(x => new DB.FilterElementIdRule(provider, new DB.FilterNumericEquals(), x)).Select(x => new DB.ElementParameterFilter(x)).ToArray();
          DA.SetData("Filter", new DB.LogicalOrFilter(filters));
        }
      }
    }
  }
  #endregion

  #region Tertiary
  public class ElementBoundingBoxFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("F5A32842-B18E-470F-8BD3-BAE1373AD982");
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
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
      DB.ElementFilter filter = null;

      if (boundingBox)
      {
        var pointsBBox = new Rhino.Geometry.BoundingBox(points);
        {
          var box = new Rhino.Geometry.Box(pointsBBox);
          box.Inflate(tolerance);
          targets.Add(box);
        }

        pointsBBox = pointsBBox.ChangeUnits(scaleFactor);
        var outline = new DB.Outline(pointsBBox.Min.ToHost(), pointsBBox.Max.ToHost());

        if (strict)
          filter = new DB.BoundingBoxIsInsideFilter(outline, tolerance * scaleFactor, inverted);
        else
          filter = new DB.BoundingBoxIntersectsFilter(outline, tolerance * scaleFactor, inverted);
      }
      else
      {
        var filters = points.Select<Rhino.Geometry.Point3d, DB.ElementFilter>
                     (x =>
                     {
                       var pointsBBox = new Rhino.Geometry.BoundingBox(x, x);
                       {
                         var box = new Rhino.Geometry.Box(pointsBBox);
                         box.Inflate(tolerance);
                         targets.Add(box);
                       }

                       x = x.ChangeUnits(scaleFactor);

                       if (strict)
                       {
                         var outline = new DB.Outline(x.ToHost(), x.ToHost());
                         return new DB.BoundingBoxIsInsideFilter(outline, tolerance * scaleFactor, inverted);
                       }
                       else
                       {
                         return new DB.BoundingBoxContainsPointFilter(x.ToHost(), tolerance * scaleFactor, inverted);
                       }
                     });

        var filterList = filters.ToArray();
        filter = filterList.Length == 1 ?
                 filterList[0] :
                 new DB.LogicalOrFilter(filterList);
      }

      DA.SetData("Filter", filter);
      DA.SetDataList("Target", targets);
    }
  }

  public class ElementIntersectsElementFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("D1E4C98D-E550-4F25-991A-5061EF845C37");
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    protected override string IconTag => "I";

    public ElementIntersectsElementFilter()
    : base("Element.IntersectsElementFilter", "Intersects element Filter", "Filter used to match elements that intersect to the given element", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to match", GH_ParamAccess.item);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new DB.ElementIntersectsElementFilter(element, inverted));
    }
  }

  public class ElementIntersectsBrepFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("A8889824-F607-4465-B84F-16DF79DD08AB");
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    protected override string IconTag => "I";

    public ElementIntersectsBrepFilter()
    : base("Element.IntersectsBrepFilter", "Intersects brep Filter", "Filter used to match elements that intersect to the given brep", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", "Brep to match", GH_ParamAccess.item);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Brep brep = null;
      if (!DA.GetData("Brep", ref brep))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      var scaleFactor = 1.0 / Revit.ModelUnits;
      DA.SetData("Filter", new DB.ElementIntersectsSolidFilter(brep.ChangeUnits(scaleFactor).ToHost(), inverted));
    }
  }

  public class ElementIntersectsMeshFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("09F9E451-F6C9-42FB-90E3-85E9923998A2");
    public override GH_Exposure Exposure => GH_Exposure.tertiary;
    protected override string IconTag => "I";

    public ElementIntersectsMeshFilter()
    : base("Element.IntersectsMeshFilter", "Intersects mesh Filter", "Filter used to match elements that intersect to the given mesh", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddMeshParameter("Mesh", "B", "Mesh to match", GH_ParamAccess.item);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Rhino.Geometry.Mesh mesh = null;
      if (!DA.GetData("Mesh", ref mesh))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      var scaleFactor = 1.0 / Revit.ModelUnits;
      DA.SetData("Filter", new DB.ElementIntersectsSolidFilter(Rhino.Geometry.Brep.CreateFromMesh(mesh.ChangeUnits(scaleFactor), true).ToHost(), inverted));
    }
  }
  #endregion

  #region Quarternary
  public class ElementLevelFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("B534489B-1367-4ACA-8FD8-D4B365CEEE0D");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;
    protected override string IconTag => "L";

    public ElementLevelFilter()
    : base("Element.LevelFilter", "Level Filter", "Filter used to match elements associated to the given level", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Level(), "Level", "L", "Level to match", GH_ParamAccess.item);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var levelId = DB.ElementId.InvalidElementId;
      if (!DA.GetData("Level", ref levelId))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new DB.ElementLevelFilter(levelId, inverted));
    }
  }

  public class ElementDesignOptionFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("1B197E82-3A65-43D4-AE47-FD25E4E6F2E5");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;
    protected override string IconTag => "D";

    public ElementDesignOptionFilter()
    : base("Element.DesignOptionFilter", "Design Option Filter", "Filter used to match elements associated to the given Design Option", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager[manager.AddParameter(new Parameters.Element(), "Design Option", "D", "Design Option to match", GH_ParamAccess.item)].Optional = true;
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var doc = Revit.ActiveDBDocument;
      var designOptionId = DB.DesignOption.GetActiveDesignOptionId(doc);

      var designOption = default(DB.DesignOption);
      if (DA.GetData("Design Option", ref designOption))
      {
        doc = designOption?.Document;
        designOptionId = designOption?.Id;
      }

      if (doc is null || designOptionId is null)
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new DB.ElementDesignOptionFilter(designOptionId, inverted));
    }
  }

  public class ElementOwnerViewFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("CFB42D90-F9D4-4601-9EEF-C624E92A424D");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;
    protected override string IconTag => "V";

    public ElementOwnerViewFilter()
    : base("Element.OwnerViewFilter", "Owner View Filter", "Filter used to match elements associated to the given View", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager[manager.AddParameter(new Parameters.Element(), "View", "V", "View to match", GH_ParamAccess.item)].Optional = true;
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var viewId = DB.ElementId.InvalidElementId;
      DA.GetData("View", ref viewId);

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new DB.ElementOwnerViewFilter(viewId, inverted));
    }
  }

  public class ElementSelectableInViewFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("AC546F16-C917-4CD1-9F8A-FBDD6330EB80");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;
    protected override string IconTag => "S";

    public ElementSelectableInViewFilter()
    : base("Element.SelectableInViewFilter", "Selectable in View Filter", "Filter used to match seletable elements into the given View", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager[manager.AddParameter(new Parameters.Element(), "View", "V", "View to match", GH_ParamAccess.item)].Optional = true;
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var doc = Revit.ActiveDBDocument;
      var viewId = doc.ActiveView.Id;

      DB.View view = null;
      if (DA.GetData("View", ref view))
      {
        doc = view?.Document;
        viewId = view?.Id;
      }

      if (doc is null || viewId is null)
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new Autodesk.Revit.UI.Selection.SelectableInViewFilter(doc, viewId, inverted));
    }
  }
  #endregion

  #region
  public class ElementParameterFilter : ElementFilterComponent
  {
    public override Guid ComponentGuid => new Guid("E6A1F501-BDA4-4B78-8828-084B5EDA926F");
    public override GH_Exposure Exposure => GH_Exposure.quinary;
    protected override string IconTag => "#";

    public ElementParameterFilter()
    : base("Element.ParameterFilter", "Parameter Filter", "Filter used to match elements by the value of a parameter", "Revit", "Filter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.FilterRule(), "Rules", "R", "Rules to check", GH_ParamAccess.list);
      base.RegisterInputParams(manager);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var rules = new List<DB.FilterRule>();
      if (!DA.GetDataList("Rules", rules))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new DB.ElementParameterFilter(rules, inverted));
    }
  }

  public abstract class ElementFilterRule : GH_Component
  {
    public override GH_Exposure Exposure => GH_Exposure.quinary;
    public override bool IsPreviewCapable => false;

    protected ElementFilterRule(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterKey(), "ParameterKey", "K", "Parameter to check", GH_ParamAccess.item);
      manager.AddGenericParameter("Value", "V", "Value to check with", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.FilterRule(), "Rule", "R", string.Empty, GH_ParamAccess.item);
    }

    static double ToHost(double value, DB.ParameterType parameterType)
    {
      switch (parameterType)
      {
        case DB.ParameterType.Length:  return value / Math.Pow(Revit.ModelUnits, 1.0);
        case DB.ParameterType.Area:    return value / Math.Pow(Revit.ModelUnits, 2.0);
        case DB.ParameterType.Volume:  return value / Math.Pow(Revit.ModelUnits, 3.0);
      }

      return value;
    }

    static readonly Dictionary<DB.BuiltInParameter, DB.ParameterType> BuiltInParametersTypes = new Dictionary<DB.BuiltInParameter, DB.ParameterType>();

    static bool TryGetParameterDefinition(DB.Document doc, DB.ElementId id, out DB.StorageType storageType, out DB.ParameterType parameterType)
    {
      if (id.TryGetBuiltInParameter(out var builtInParameter))
      {
        storageType = doc.get_TypeOfStorage(builtInParameter);

        if (storageType == DB.StorageType.ElementId)
        {
          if (builtInParameter == DB.BuiltInParameter.ELEM_TYPE_PARAM)
          {
            parameterType = DB.ParameterType.FamilyType;
            return true;
          }

          if (builtInParameter == DB.BuiltInParameter.ELEM_CATEGORY_PARAM || builtInParameter == DB.BuiltInParameter.ELEM_CATEGORY_PARAM_MT)
          {
            parameterType = (DB.ParameterType) int.MaxValue;
            return true;
          }
        }

        if (storageType == DB.StorageType.Double)
        {
          if (BuiltInParametersTypes.TryGetValue(builtInParameter, out parameterType))
            return true;

          var categoriesWhereDefined = doc.GetBuiltInCategoriesWithParameters().
            Select(bic => new DB.ElementId(bic)).
            Where(cid => DB.TableView.GetAvailableParameters(doc, cid).Contains(id)).
            ToArray();

          using (var collector = new DB.FilteredElementCollector(doc))
          {
            using
            (
              var filteredCollector = categoriesWhereDefined.Length == 0 ?
              collector.WherePasses(new DB.ElementClassFilter(typeof(DB.ParameterElement), false)) :
              categoriesWhereDefined.Length > 1 ?
                collector.WherePasses(new DB.ElementMulticategoryFilter(categoriesWhereDefined)) :
                collector.WherePasses(new DB.ElementCategoryFilter(categoriesWhereDefined[0]))
            )
            {
              foreach (var element in filteredCollector)
              {
                var parameter = element.get_Parameter(builtInParameter);
                if (parameter is null)
                  continue;

                parameterType = parameter.Definition.ParameterType;
                BuiltInParametersTypes.Add(builtInParameter, parameterType);
                return true;
              }
            }
          }

          parameterType = DB.ParameterType.Invalid;
          return false;
        }

        parameterType = DB.ParameterType.Invalid;
        return true;
      }
      else
      {
        try
        {
          if (doc.GetElement(id) is DB.ParameterElement parameter)
          {
            storageType = parameter.GetDefinition().ParameterType.ToStorageType();
            parameterType = parameter.GetDefinition().ParameterType;
            return true;
          }
        }
        catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }
      }

      storageType = DB.StorageType.None;
      parameterType = DB.ParameterType.Invalid;
      return false;
    }

    protected enum ConditionType
    {
      NotEquals,
      Equals,
      Greater,
      GreaterOrEqual,
      Less,
      LessOrEqual
    }

    protected abstract ConditionType Condition { get; }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var parameterKey = default(Types.ParameterKey);
      if (!DA.GetData("ParameterKey", ref parameterKey))
        return;

      DA.DisableGapLogic();

      if (!TryGetParameterDefinition(parameterKey.Document, parameterKey.Id, out var storageType, out var parameterType))
      {
        if (parameterKey.Id.TryGetBuiltInParameter(out var builtInParameter))
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Failed to found parameter '{DB.LabelUtils.GetLabelFor(builtInParameter)}' in Revit document.");
        else
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Failed to found parameter '{parameterKey.Id.IntegerValue}' in Revit document.");

        return;
      }

      var provider = new DB.ParameterValueProvider(parameterKey);

      DB.FilterRule rule = null;
      if (storageType == DB.StorageType.String)
      {
        DB.FilterStringRuleEvaluator ruleEvaluator = null;
        switch (Condition)
        {
          case ConditionType.NotEquals:
          case ConditionType.Equals:          ruleEvaluator = new DB.FilterStringEquals(); break;
          case ConditionType.Greater:         ruleEvaluator = new DB.FilterStringGreater(); break;
          case ConditionType.GreaterOrEqual:  ruleEvaluator = new DB.FilterStringGreaterOrEqual(); break;
          case ConditionType.Less:            ruleEvaluator = new DB.FilterStringLess(); break;
          case ConditionType.LessOrEqual:     ruleEvaluator = new DB.FilterStringLessOrEqual(); break;
        }

        var goo = default(GH_String);
        if (DA.GetData("Value", ref goo))
          rule = new DB.FilterStringRule(provider, ruleEvaluator, goo.Value, true);
      }
      else
      {
        DB.FilterNumericRuleEvaluator ruleEvaluator = null;
        switch (Condition)
        {
          case ConditionType.NotEquals:
          case ConditionType.Equals:          ruleEvaluator = new DB.FilterNumericEquals(); break;
          case ConditionType.Greater:         ruleEvaluator = new DB.FilterNumericGreater(); break;
          case ConditionType.GreaterOrEqual:  ruleEvaluator = new DB.FilterNumericGreaterOrEqual(); break;
          case ConditionType.Less:            ruleEvaluator = new DB.FilterNumericLess(); break;
          case ConditionType.LessOrEqual:     ruleEvaluator = new DB.FilterNumericLessOrEqual(); break;
        }

        switch (storageType)
        {
          case DB.StorageType.Integer:
            {
              var goo = default(GH_Integer);
              if (DA.GetData("Value", ref goo))
                rule = new DB.FilterIntegerRule(provider, ruleEvaluator, goo.Value);
            }
            break;
          case DB.StorageType.Double:
            {
              var goo = default(GH_Number);
              if (DA.GetData("Value", ref goo))
              {
                if (Condition == ConditionType.Equals || Condition == ConditionType.NotEquals)
                {
                  if (parameterType == DB.ParameterType.Length || parameterType == DB.ParameterType.Area || parameterType == DB.ParameterType.Volume)
                    rule = new DB.FilterDoubleRule(provider, ruleEvaluator, ToHost(goo.Value, parameterType), ToHost(Revit.VertexTolerance, parameterType));
                  else
                    rule = new DB.FilterDoubleRule(provider, ruleEvaluator, ToHost(goo.Value, parameterType), 1e-6);
                }
                else
                  rule = new DB.FilterDoubleRule(provider, ruleEvaluator, ToHost(goo.Value, parameterType), 0.0);
              }
            }
            break;
          case DB.StorageType.ElementId:
            {
              switch(parameterType)
              {
                case (DB.ParameterType) int.MaxValue: // Category
                  {
                    var value = default(Types.Category);
                    if (DA.GetData("Value", ref value))
                      rule = new DB.FilterElementIdRule(provider, ruleEvaluator, value);
                  }
                  break;
                case DB.ParameterType.Material:
                  {
                    var value = default(Types.Material);
                    if (DA.GetData("Value", ref value))
                      rule = new DB.FilterElementIdRule(provider, ruleEvaluator, value);
                  }
                  break;
                case DB.ParameterType.FamilyType:
                  {
                    var value = default(Types.ElementType);
                    if (DA.GetData("Value", ref value))
                      rule = new DB.FilterElementIdRule(provider, ruleEvaluator, value);
                  }
                  break;
                default:
                  {
                    var value = default(Types.Element);
                    if (DA.GetData("Value", ref value))
                      rule = new DB.FilterElementIdRule(provider, ruleEvaluator, value);
                  }
                  break;
              }
            }
            break;
        }
      }

      if (rule is object)
      {
        if(Condition == ConditionType.NotEquals)
          DA.SetData("Rule", new DB.FilterInverseRule(rule));
        else
          DA.SetData("Rule", rule);
      }
    }
  }

  public class ElementFilterRuleNotEquals : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("6BBE9731-EF71-42E8-A880-1D2ADFEB9F79");
    protected override string IconTag => "≠";
    protected override ConditionType Condition => ConditionType.NotEquals;

    public ElementFilterRuleNotEquals()
    : base("Element.RuleNotEquals", "Not Equals", "Filter used to match elements if value of a parameter are not equals to Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterRuleEquals : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("0F9139AC-2A21-474C-9C5B-6864B2F2313C");
    protected override string IconTag => "=";
    protected override ConditionType Condition => ConditionType.Equals;

    public ElementFilterRuleEquals()
    : base("Element.RuleEquals", "Equals", "Filter used to match elements if value of a parameter equals to Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterRuleGreater : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("BB7D39DA-97AD-4277-82C7-010AF857FF03");
    protected override string IconTag => ">";
    protected override ConditionType Condition => ConditionType.Greater;

    public ElementFilterRuleGreater()
    : base("Element.RuleGreater", "Greater", "Filter used to match elements if value of a parameter greater than Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterRuleGreaterOrEqual : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("05BBAEDD-027B-40DA-8390-F826B63FD100");
    protected override string IconTag => "≥";
    protected override ConditionType Condition => ConditionType.GreaterOrEqual;

    public ElementFilterRuleGreaterOrEqual()
    : base("Element.RuleGreaterOrEqual", "Greater or Equal", "Filter used to match elements if value of a parameter greater or equal than Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterRuleLess : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("BE2C5AFE-7D56-4F63-9A23-20560E3675B9");
    protected override string IconTag => "<";
    protected override ConditionType Condition => ConditionType.Less;

    public ElementFilterRuleLess()
    : base("Element.RuleLess", "Less", "Filter used to match elements if value of a parameter less than Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterRuleLessOrEqual : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("BB69852F-6A39-4ADC-B9B8-D16A8862B4C7");
    protected override string IconTag => "≤";
    protected override ConditionType Condition => ConditionType.LessOrEqual;

    public ElementFilterRuleLessOrEqual()
    : base("Element.RuleLessOrEqual", "Less or Equal", "Filter used to match elements if value of a parameter less or equal than Value", "Revit", "Filter")
    { }
  }
  #endregion
}
