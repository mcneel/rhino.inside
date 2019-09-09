using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Parameters;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class ElementFilter : GH_Goo<Autodesk.Revit.DB.ElementFilter>
  {
    public override string TypeName => "Revit Element Filter";
    public override string TypeDescription => "Represents a Revit element filter";
    public override bool IsValid => Value?.IsValidObject ?? false;
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
        return $"Invalid {TypeName}";

      return $"{Value.GetType().Name}";
    }
  }

  public class FilterRule : GH_Goo<Autodesk.Revit.DB.FilterRule>
  {
    public override string TypeName => "Revit Filter Rule";
    public override string TypeDescription => "Represents a Revit filter rule";
    public override bool IsValid => Value?.IsValidObject ?? false;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    public FilterRule() { }
    public FilterRule(Autodesk.Revit.DB.FilterRule filter) : base(filter) { }

    public override bool CastFrom(object source)
    {
      if (source is Autodesk.Revit.DB.FilterRule rule)
      {
        Value = rule;
        return true;
      }

      return base.CastFrom(source);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.FilterRule)))
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

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementIsElementTypeFilter(!inverted));
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
      var typeIds = new List<Autodesk.Revit.DB.ElementId>();
      if (!DA.GetDataList("Types", typeIds))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      var provider = new ParameterValueProvider(new ElementId(BuiltInParameter.ELEM_TYPE_PARAM));
      if (typeIds.Count == 1)
      {
        var rule = new FilterElementIdRule(provider, new FilterNumericEquals(), typeIds[0]);
        DA.SetData("Filter", new Autodesk.Revit.DB.ElementParameterFilter(rule, inverted));
      }
      else
      {
        if (inverted)
        {
          var rules = typeIds.Select(x => new FilterInverseRule(new FilterElementIdRule(provider, new FilterNumericEquals(), x))).ToArray();
          DA.SetData("Filter", new Autodesk.Revit.DB.ElementParameterFilter(rules));
        }
        else
        {
          var filters = typeIds.Select(x => new FilterElementIdRule(provider, new FilterNumericEquals(), x)).Select(x => new Autodesk.Revit.DB.ElementParameterFilter(x)).ToArray();
          DA.SetData("Filter", new LogicalOrFilter(filters));
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
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementIntersectsElementFilter(element, inverted));
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
      if(scaleFactor != 1.0)
        brep.Scale(scaleFactor);

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementIntersectsSolidFilter(brep.ToHost(), inverted));
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
      if (scaleFactor != 1.0)
        mesh.Scale(scaleFactor);

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementIntersectsSolidFilter(Rhino.Geometry.Brep.CreateFromMesh(mesh, true).ToHost(), inverted));
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
      var designOptionId = Autodesk.Revit.DB.ElementId.InvalidElementId;
      if (!DA.GetData("Design Option", ref designOptionId))
        designOptionId = Autodesk.Revit.DB.DesignOption.GetActiveDesignOptionId(Revit.ActiveDBDocument);

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementDesignOptionFilter(designOptionId, inverted));
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
      var viewId = Autodesk.Revit.DB.ElementId.InvalidElementId;
      DA.GetData("View", ref viewId);

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementOwnerViewFilter(viewId, inverted));
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
      var viewId = Revit.ActiveDBDocument.ActiveView.Id;
      DA.GetData("View", ref viewId);

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new Autodesk.Revit.UI.Selection.SelectableInViewFilter(Revit.ActiveDBDocument, viewId, inverted));
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
      var rules = new List<Autodesk.Revit.DB.FilterRule>();
      if (!DA.GetDataList("Rules", rules))
        return;

      var inverted = false;
      if (!DA.GetData("Inverted", ref inverted))
        return;

      DA.SetData("Filter", new Autodesk.Revit.DB.ElementParameterFilter(rules, inverted));
    }
  }

  public abstract class ElementFilterRule : GH_Component
  {
    public override Guid ComponentGuid => new Guid("0F9139AC-2A21-474C-9C5B-6864B2F2313C");
    public override GH_Exposure Exposure => GH_Exposure.quinary;
    public override bool IsPreviewCapable => false;

    protected ElementFilterRule(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterKey(), "ParameterKey", "K", "Parameter to check", GH_ParamAccess.item);
      //var condition = manager[manager.AddIntegerParameter("Condition", "C", string.Empty, GH_ParamAccess.item, 1)] as Param_Integer;

      //condition.AddNamedValue("Equals", 1);
      //condition.AddNamedValue("Greater", 2);
      //condition.AddNamedValue("Greater or Equal", 3);
      //condition.AddNamedValue("Less", 4);
      //condition.AddNamedValue("Less or Equal", 5);

      manager.AddGenericParameter("Value", "V", "Value to check with", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.FilterRule(), "Rule", "R", string.Empty, GH_ParamAccess.item);
    }

    static double ToHost(double value, ParameterType parameterType)
    {
      switch (parameterType)
      {
        case ParameterType.Length:  return value / Math.Pow(Revit.ModelUnits, 1.0);
        case ParameterType.Area:    return value / Math.Pow(Revit.ModelUnits, 2.0);
        case ParameterType.Volume:  return value / Math.Pow(Revit.ModelUnits, 3.0);
      }

      return value;
    }

    static readonly Dictionary<BuiltInParameter, ParameterType> BuiltInParametersTypes = new Dictionary<BuiltInParameter, ParameterType>();

    static bool TryGetParameterDefinition(Document doc, ElementId id, out StorageType storageType, out ParameterType parameterType)
    {
      if (id.TryGetBuiltInParameter(out var builtInParameter))
      {
        storageType = doc.get_TypeOfStorage(builtInParameter);

        if (storageType == StorageType.ElementId)
        {
          if (builtInParameter == BuiltInParameter.ELEM_TYPE_PARAM)
          {
            parameterType = ParameterType.FamilyType;
            return true;
          }

          if (builtInParameter == BuiltInParameter.ELEM_CATEGORY_PARAM || builtInParameter == BuiltInParameter.ELEM_CATEGORY_PARAM_MT)
          {
            parameterType = (ParameterType) int.MaxValue;
            return true;
          }
        }

        if (storageType == StorageType.Double)
        {
          if (BuiltInParametersTypes.TryGetValue(builtInParameter, out parameterType))
            return true;

          var categoriesWhereDefined = Enum.GetValues(typeof(BuiltInCategory)).
            Cast<BuiltInCategory>().
            Select(bic => new ElementId(bic)).
            Where(cid => TableView.GetAvailableParameters(doc, cid).Contains(id)).
            ToArray();

          using (var collector = new FilteredElementCollector(doc))
          {
            using
            (
              var filteredCollector = categoriesWhereDefined.Length == 0 ?
              collector.WherePasses(new Autodesk.Revit.DB.ElementClassFilter(typeof(ParameterElement), false)) :
              categoriesWhereDefined.Length > 1 ?
                collector.WherePasses(new Autodesk.Revit.DB.ElementMulticategoryFilter(categoriesWhereDefined)) :
                collector.WherePasses(new Autodesk.Revit.DB.ElementCategoryFilter(categoriesWhereDefined[0]))
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

          parameterType = ParameterType.Invalid;
          return false;
        }

        parameterType = ParameterType.Invalid;
        return true;
      }
      else
      {
        try
        {
          if (doc.GetElement(id) is ParameterElement parameter)
          {
            storageType = parameter.GetDefinition().ParameterType.ToStorageType();
            parameterType = parameter.GetDefinition().ParameterType;
            return true;
          }
        }
        catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }
      }

      storageType = StorageType.None;
      parameterType = ParameterType.Invalid;
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
      var parameterId = ElementId.InvalidElementId;
      if (!DA.GetData("ParameterKey", ref parameterId))
        return;

      DA.DisableGapLogic();

      if (!TryGetParameterDefinition(Revit.ActiveDBDocument, parameterId, out var storageType, out var parameterType))
      {
        if (parameterId.TryGetBuiltInParameter(out var builtInParameter))
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Failed to found parameter '{LabelUtils.GetLabelFor(builtInParameter)}' in Revit document.");
        else
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Failed to found parameter '{parameterId.IntegerValue}' in Revit document.");

        return;
      }

      var provider = new ParameterValueProvider(parameterId);

      Autodesk.Revit.DB.FilterRule rule = null;
      if (storageType == StorageType.String)
      {
        FilterStringRuleEvaluator ruleEvaluator = null;
        switch (Condition)
        {
          case ConditionType.NotEquals:
          case ConditionType.Equals:          ruleEvaluator = new FilterStringEquals(); break;
          case ConditionType.Greater:         ruleEvaluator = new FilterStringGreater(); break;
          case ConditionType.GreaterOrEqual:  ruleEvaluator = new FilterStringGreaterOrEqual(); break;
          case ConditionType.Less:            ruleEvaluator = new FilterStringLess(); break;
          case ConditionType.LessOrEqual:     ruleEvaluator = new FilterStringLessOrEqual(); break;
        }

        var goo = default(GH_String);
        if (DA.GetData("Value", ref goo))
          rule = new FilterStringRule(provider, ruleEvaluator, goo.Value, true);
      }
      else
      {
        FilterNumericRuleEvaluator ruleEvaluator = null;
        switch (Condition)
        {
          case ConditionType.NotEquals:
          case ConditionType.Equals:          ruleEvaluator = new FilterNumericEquals(); break;
          case ConditionType.Greater:         ruleEvaluator = new FilterNumericGreater(); break;
          case ConditionType.GreaterOrEqual:  ruleEvaluator = new FilterNumericGreaterOrEqual(); break;
          case ConditionType.Less:            ruleEvaluator = new FilterNumericLess(); break;
          case ConditionType.LessOrEqual:     ruleEvaluator = new FilterNumericLessOrEqual(); break;
        }

        switch (storageType)
        {
          case StorageType.Integer:
            {
              var goo = default(GH_Integer);
              if (DA.GetData("Value", ref goo))
                rule = new FilterIntegerRule(provider, ruleEvaluator, goo.Value);
            }
            break;
          case StorageType.Double:
            {
              var goo = default(GH_Number);
              if (DA.GetData("Value", ref goo))
              {
                if (Condition == ConditionType.Equals || Condition == ConditionType.NotEquals)
                {
                  if (parameterType == ParameterType.Length || parameterType == ParameterType.Area || parameterType == ParameterType.Volume)
                    rule = new FilterDoubleRule(provider, ruleEvaluator, ToHost(goo.Value, parameterType), ToHost(Revit.VertexTolerance, parameterType));
                  else
                    rule = new FilterDoubleRule(provider, ruleEvaluator, ToHost(goo.Value, parameterType), 1e-6);
                }
                else
                  rule = new FilterDoubleRule(provider, ruleEvaluator, ToHost(goo.Value, parameterType), 0.0);
              }
            }
            break;
          case StorageType.ElementId:
            {
              switch(parameterType)
              {
                case (ParameterType) int.MaxValue: // Category
                  {
                    var value = default(Types.Category);
                    if (DA.GetData("Value", ref value))
                      rule = new FilterElementIdRule(provider, ruleEvaluator, value);
                  }
                  break;
                case ParameterType.FamilyType:
                  {
                    var value = default(Types.ElementType);
                    if (DA.GetData("Value", ref value))
                      rule = new FilterElementIdRule(provider, ruleEvaluator, value);
                  }
                  break;
                default:
                  {
                    var value = default(Types.Element);
                    if (DA.GetData("Value", ref value))
                      rule = new FilterElementIdRule(provider, ruleEvaluator, value);
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
          DA.SetData("Rule", new FilterInverseRule(rule));
        else
          DA.SetData("Rule", rule);
      }
    }
  }

  public class ElementFilterNotEquals : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("6BBE9731-EF71-42E8-A880-1D2ADFEB9F79");
    protected override string IconTag => "≠";
    protected override ConditionType Condition => ConditionType.NotEquals;

    public ElementFilterNotEquals()
    : base("Element.ElementFilterNotEquals", "Filter Equals", "Filter used to match elements if value of a parameter are not equals to Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterEquals : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("0F9139AC-2A21-474C-9C5B-6864B2F2313C");
    protected override string IconTag => "=";
    protected override ConditionType Condition => ConditionType.Equals;

    public ElementFilterEquals()
    : base("Element.ElementFilterEquals", "Filter Equals", "Filter used to match elements if value of a parameter equals to Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterGreater : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("BB7D39DA-97AD-4277-82C7-010AF857FF03");
    protected override string IconTag => ">";
    protected override ConditionType Condition => ConditionType.Greater;

    public ElementFilterGreater()
    : base("Element.ElementFilterGreater", "Filter Greater", "Filter used to match elements if value of a parameter greater than Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterGreaterOrEqual : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("05BBAEDD-027B-40DA-8390-F826B63FD100");
    protected override string IconTag => "≥";
    protected override ConditionType Condition => ConditionType.GreaterOrEqual;

    public ElementFilterGreaterOrEqual()
    : base("Element.ElementFilterGreater", "Filter greater or equal", "Filter used to match elements if value of a parameter greater or equal than Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterLess : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("BE2C5AFE-7D56-4F63-9A23-20560E3675B9");
    protected override string IconTag => "<";
    protected override ConditionType Condition => ConditionType.Less;

    public ElementFilterLess()
    : base("Element.ElementFilterLess", "Filter less", "Filter used to match elements if value of a parameter less than Value", "Revit", "Filter")
    { }
  }

  public class ElementFilterLessOrEqual : ElementFilterRule
  {
    public override Guid ComponentGuid => new Guid("BB69852F-6A39-4ADC-B9B8-D16A8862B4C7");
    protected override string IconTag => "≤";
    protected override ConditionType Condition => ConditionType.LessOrEqual;

    public ElementFilterLessOrEqual()
    : base("Element.ElementFilterLessOrEqual", "Filter less or equal", "Filter used to match elements if value of a parameter less or equal than Value", "Revit", "Filter")
    { }
  }
  #endregion
}
