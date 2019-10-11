using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using Grasshopper.GUI;
using Grasshopper.GUI.Canvas;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Attributes;
using Grasshopper.Kernel.Types;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class Element : ID
  {
    public override string TypeName => "Revit Element";
    public override string TypeDescription => "Represents a Revit element";
    override public object ScriptVariable() => (DB.Element) this;
    protected override Type ScriptVariableType => typeof(DB.Element);
    public static explicit operator DB.Element(Element self) => self.IsValid ? self.Document.GetElement(self) : null;

    public static Element FromValue(object data)
    {
      switch (data)
      {
        case DB.Category category: return Category.FromCategory(category);
        case DB.Element  element:  return Element.FromElement(element);
      }

      return null;
    }

    public static Element FromElement(DB.Element element)
    {
      if (element is null)
        return null;

      if (element.GetType() == typeof(DB.Element))
      {
        try
        {
          if (DB.Category.GetCategory(element.Document, element.Id) is DB.Category category)
            return new Category(category);
        }
        catch (Autodesk.Revit.Exceptions.InternalException) { }
      }
      else
      {
        if (element is DB.ParameterElement parameter)
          return new ParameterKey(parameter);

        if (element is DB.Material material)
          return new Material(material);

        if (element is DB.ElementType elementType)
          return new ElementType(elementType);

        if (element is DB.SketchPlane sketchPlane)
          return new SketchPlane(sketchPlane);

        if (element is DB.HostObject host)
          return new HostObject(host);

        if (element is DB.DatumPlane datumPlane)
        {
          if (element is DB.Level level)
            return new Level(level);

          if (element is DB.Grid grid)
            return new Grid(grid);

          return new DatumPlane(datumPlane);
        }
      }

      if (GeometricElement.IsValidElement(element))
        return new GeometricElement(element);

      return new Element(element);
    }

    new public static Element FromElementId(DB.Document doc, DB.ElementId Id)
    {
      if (doc.GetElement(Id) is DB.Element value)
        return FromElement(value);

      return null;
    }

    protected virtual bool SetValue(DB.Element element)
    {
      if (ScriptVariableType.IsInstanceOfType(element))
      {
        Document     = element.Document;
        DocumentGUID = Document.GetFingerprintGUID();
        Value        = element.Id;
        UniqueID     = element.UniqueId;
        return true;
      }

      return false;
    }

    public Element() : base() { }
    protected Element(DB.Document doc, DB.ElementId id) : base(doc, id) { }
    protected Element(DB.Element element)               : base(element.Document, element.Id) { }

    public override bool CastFrom(object source)
    {
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      var element = default(DB.Element);
      switch (source)
      {
        case DB.Element e:    element = e; break;
        case DB.ElementId id: element = Revit.ActiveDBDocument.GetElement(id); break;
        case int integer:     element = Revit.ActiveDBDocument.GetElement(new DB.ElementId(integer)); break;
        default:              return false;
      }

      return SetValue(element);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (base.CastTo<Q>(ref target))
        return true;

      var element = (DB.Element) this;
      if (typeof(DB.Element).IsAssignableFrom(typeof(Q)))
      {
        if (element is null)
        {
          if (IsValid)
            return false;
        }
        else if (!typeof(Q).IsAssignableFrom(element.GetType()))
          return false;

        target = (Q) (object) element;
        return true;
      }

      if (element is null)
        return false;

      if (element.Category?.HasMaterialQuantities ?? false)
      {
        if (typeof(Q).IsAssignableFrom(typeof(GH_Mesh)))
        {
          DB.Options options = null;
          using (var geometry = element.GetGeometry(DB.ViewDetailLevel.Fine, out options)) using (options)
          {
            if (geometry is object)
            {
              var mesh = new Rhino.Geometry.Mesh();
              mesh.Append(geometry.GetPreviewMeshes().Where(x => x is object));
              mesh.Normals.ComputeNormals();
              if (mesh.Faces.Count > 0)
              {
                target = (Q) (object) new GH_Mesh(mesh);
                return true;
              }
            }
          }
        }
      }

      if (typeof(Q).IsAssignableFrom(typeof(GH_Curve)))
      {
        var axis = Axis;
        if (axis is null)
          return false;

        target = (Q) (object) new GH_Curve(axis);
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(GH_Plane)))
      {
        var plane = Plane;
        if (!plane.IsValid || !plane.Origin.IsValid)
          return false;

        target = (Q) (object) new GH_Plane(plane);
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(GH_Point)))
      {
        var location = Location;
        if (!location.IsValid)
          return false;

        target = (Q) (object) new GH_Point(location);
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(GH_Vector)))
      {
        var normal = ZAxis;
        if (!normal.IsValid)
          return false;

        target = (Q) (object) new GH_Vector(normal);
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(GH_Transform)))
      {
        var plane = Plane;
        if (!plane.IsValid || !plane.Origin.IsValid)
          return false;

        target = (Q) (object) new GH_Transform(Rhino.Geometry.Transform.PlaneToPlane(Rhino.Geometry.Plane.WorldXY, plane));
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(GH_Box)))
      {
        var box = Box;
        if (!box.IsValid)
          return false;

        target = (Q) (object) new GH_Box(box);
        return true;
      }

      return false;
    }

    new class Proxy : ID.Proxy
    {
      public Proxy(Element e) : base(e) { (this as IGH_GooProxy).UserString = FormatInstance(); }

      public override bool IsParsable() => true;
      public override string FormatInstance() => $"{owner.Value.IntegerValue}:{element?.Name ?? string.Empty}";
      public override bool FromString(string str)
      {
        int index = str.IndexOf(':');
        if(index >= 0)
          str = str.Substring(0, index);

        str = str.Trim();
        if (int.TryParse(str, out int elementId))
        {
          owner.Value = new DB.ElementId(elementId);
          return true;
        }

        return false;
      }

      DB.Element element => owner.IsElementLoaded ? owner.Document?.GetElement(owner.Id) : null;

      [System.ComponentModel.Description("A human readable name for the Element.")]
      public string Name => element?.Name;
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public override string ToString()
    {
      if (IsValid)
      {
        var element = (DB.Element) this;
        if (element is object)
        {
          var ToolTip = string.Empty;

          if (element.Category is object)
            ToolTip += $"{element.Category.Name} : ";
          else
            ToolTip += $"{element.GetType().Name} : ";

          if (element.Document.GetElement(element.GetTypeId()) is DB.ElementType elementType)
          {
            if(!string.IsNullOrEmpty(elementType.FamilyName))
              ToolTip += $"{elementType.FamilyName} : ";

            ToolTip += $"{elementType.Name} : ";
          }
          else if (!string.IsNullOrEmpty(element.Name))
          {
            ToolTip += $"{element.Name} : ";
          }

          return $"{ToolTip}{Identity}";
        }
      }

      return base.ToString();
    }

    #region Location
    protected Rhino.Geometry.BoundingBox clippingBox = Rhino.Geometry.BoundingBox.Empty;
    public Rhino.Geometry.BoundingBox ClippingBox
    {
      get
      {
        if (!clippingBox.IsValid)
        {
          var element = (DB.Element) this;
          if (element is object)
            clippingBox = element.get_BoundingBox(null).ToRhino().ChangeUnits(Revit.ModelUnits);
        }

        return clippingBox;
      }
    }

    public Rhino.Geometry.Box Box
    {
      get
      {
        var b = Rhino.Geometry.Box.Empty;

        var element = (DB.Element) this;
        if (element?.get_BoundingBox(null) is DB.BoundingBoxXYZ bbox)
        {
          b = new Rhino.Geometry.Box(new Rhino.Geometry.BoundingBox(bbox.Min.ToRhino(), bbox.Max.ToRhino()));
          if (!b.Transform(Rhino.Geometry.Transform.Scale(Rhino.Geometry.Point3d.Origin, Revit.ModelUnits) * bbox.Transform.ToRhino()))
            b = new Rhino.Geometry.Box(ClippingBox);
        }

        return b;
      }
    }

    public virtual Rhino.Geometry.Point3d Location
    {
      get
      {
        var p = new Rhino.Geometry.Point3d(double.NaN, double.NaN, double.NaN);

        var element = (DB.Element) this;
        if (element is object)
        {
          if (element is DB.Instance instance)
            p = instance.GetTransform().Origin.ToRhino();
          else switch (element.Location)
          {
            case DB.LocationPoint pointLocation: p = pointLocation.Point.ToRhino(); break;
            case DB.LocationCurve curveLocation: p = curveLocation.Curve.Evaluate(0.0, curveLocation.Curve.IsBound).ToRhino(); break;
            default:
                var bbox = element.get_BoundingBox(null);
                if(bbox is object)
                  p = bbox.Min.ToRhino(); break;
          }

          if (p.IsValid)
            return p.ChangeUnits(Revit.ModelUnits);
        }

        return p;
      }
    }

    public virtual Rhino.Geometry.Vector3d XAxis
    {
      get
      {
        var x = Rhino.Geometry.Vector3d.Zero;

        var element = (DB.Element) this;
        if (element is object)
        {
          if (element is DB.Instance instance)
            x = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisX.ToRhino();
          else if (element.Location is DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            x = c.TangentAt(c.Domain.Min);
          }
          else if (element.Location is DB.LocationPoint pointLocation)
          {
            x = Rhino.Geometry.Vector3d.XAxis;
            x.Rotate(pointLocation.Rotation, Rhino.Geometry.Vector3d.ZAxis);
          }

          if (x.IsZero || !x.Unitize())
            x = Rhino.Geometry.Vector3d.XAxis;
        }

        return x;
      }
    }

    public virtual Rhino.Geometry.Vector3d YAxis
    {
      get
      {
        var y = Rhino.Geometry.Vector3d.Zero;

        var element = (DB.Element) this;
        if (element is object)
        {
          if (element is DB.Instance instance)
            y = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisY.ToRhino();
          else if (element.Location is DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            y = c.CurvatureAt(c.Domain.Min);
          }
          else if (element.Location is DB.LocationPoint pointLocation)
          {
            y = Rhino.Geometry.Vector3d.YAxis;
            y.Rotate(pointLocation.Rotation, Rhino.Geometry.Vector3d.ZAxis);
          }

          if (y.IsZero || !y.Unitize())
          {
            var axis = XAxis;
            if (new Rhino.Geometry.Vector3d(axis.X, axis.Y, 0.0).IsZero)
              y = new Rhino.Geometry.Vector3d(axis.Z, 0.0, -axis.X);
            else
              y = new Rhino.Geometry.Vector3d(-axis.Y, axis.X, 0.0);
          }

          if (y.IsZero || !y.Unitize())
            y = Rhino.Geometry.Vector3d.YAxis;
        }

        return y;
      }
    }

    public virtual Rhino.Geometry.Vector3d ZAxis
    {
      get
      {
        var z = Rhino.Geometry.Vector3d.Zero;

        var element = (DB.Element) this;
        if (element is object)
        {
          if (element is DB.Instance instance)
            z = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisZ.ToRhino();
          else if (element.Location is DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            z = Rhino.Geometry.Vector3d.CrossProduct(c.TangentAt(c.Domain.Min), c.CurvatureAt(c.Domain.Min));
          }
          else if (element.Location is DB.LocationPoint pointLocation)
          {
            z = Rhino.Geometry.Vector3d.ZAxis;
          }

          if (z.IsZero || !z.Unitize())
            z = Rhino.Geometry.Vector3d.CrossProduct(XAxis, YAxis);

          if (z.IsZero || !z.Unitize())
            z = Rhino.Geometry.Vector3d.ZAxis;
        }

        return z;
      }
    }

    public virtual Rhino.Geometry.Plane Plane => new Rhino.Geometry.Plane(Location, XAxis, YAxis);

    public virtual Rhino.Geometry.Curve Axis
    {
      get
      {
        var element = (DB.Element) this;
        Rhino.Geometry.Curve c = null;

        if(element?.Location is DB.LocationCurve curveLocation)
          c = curveLocation.Curve.ToRhino();

        return c?.ChangeUnits(Revit.ModelUnits);
      }
    }
    #endregion
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Element : ElementIdNonGeometryParam<Types.Element, object>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary | GH_Exposure.obscure;
    public override Guid ComponentGuid => new Guid("F3EA4A9C-B24F-4587-A358-6A7E6D8C028B");

    public Element() : base("Element", "Element", "Represents a Revit document element.", "Params", "Revit") { }

    protected override Types.Element PreferredCast(object data) => Types.Element.FromValue(data);
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public abstract class ElementGetter : Component
  {
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected static readonly Type ObjectType = typeof(Types.Element);

    protected ElementGetter(string propertyName)
      : base(ObjectType.Name + "." + propertyName, propertyName, "Get the " + propertyName + " of the specified " + ObjectType.Name, "Revit", ObjectType.Name)
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), ObjectType.Name, ObjectType.Name.Substring(0, 1), ObjectType.Name + " to query", GH_ParamAccess.item);
    }
  }

  public class ElementIdentity : Component
  {
    public override Guid ComponentGuid => new Guid("D3917D58-7183-4B3F-9D22-03F0FE93B956");

    public ElementIdentity()
    : base("Element.Identity", "Element.Identity", "Query element identity information", "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to query for its identity", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category in which the Element resides", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.ElementType(), "Type", "T", "ElementType of the Element", GH_ParamAccess.item);
      manager.AddTextParameter("Name", "N", "A human readable name for the Element", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      DA.SetData("Category", element?.Category);
      DA.SetData("Type", element?.Document.GetElement(element.GetTypeId()));
      DA.SetData("Name", element?.Name);
    }
  }

  public class ElementMaterials : Component
  {
    public override Guid ComponentGuid => new Guid("93C18DFD-FAAB-4CF1-A681-C11754C2495D");

    public ElementMaterials()
    : base("Element.Materials", "Element.Materials", "Query element used materials", "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to query for its materials", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Material(), "Materials", "M", "Materials this Element is made of", GH_ParamAccess.list);
      manager.AddParameter(new Parameters.Material(), "Paint", "P", "Materials used to paint this Element", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      DA.SetDataList("Materials", element?.GetMaterialIds(false).Select(x => element.Document.GetElement(x)));
      DA.SetDataList("Paint",     element?.GetMaterialIds( true).Select(x => element.Document.GetElement(x)));
    }
  }

  public class ElementDelete : TransactionsComponent
  {
    public override Guid ComponentGuid => new Guid("213C1F14-A827-40E2-957E-BA079ECCE700");
    public override GH_Exposure Exposure => GH_Exposure.septenary | GH_Exposure.obscure;
    protected override string IconTag => "X";

    public ElementDelete()
    : base("Element.Delete", "Delete", "Deletes elements from Revit document", "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Elements", "E", "Elements to delete", GH_ParamAccess.tree);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager) { }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      if (!DA.GetDataTree<Types.Element>("Elements", out var elementsTree))
        return;

      var elementsToDelete = Parameters.Element.
                             ToElementIds(elementsTree).
                             GroupBy(x => x.Document).
                             ToArray();

      foreach (var group in elementsToDelete)
      {
        BeginTransaction(group.Key);

        try
        {
          var deletedElements = group.Key.Delete(group.Select(x => x.Id).ToArray());

          if (deletedElements.Count == 0)
            AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, "No elements were deleted");
          else
            AddRuntimeMessage(GH_RuntimeMessageLevel.Remark, $"{elementsToDelete.Length} elements and {deletedElements.Count - elementsToDelete.Length} dependant elements were deleted.");
        }
        catch (Autodesk.Revit.Exceptions.ArgumentException)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "One or more of the elements cannot be deleted.");
        }
      }
    }
  }

  public class ElementGeometry : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("B7E6A82F-684F-4045-A634-A4AA9F7427A8");
    static readonly string PropertyName = "Geometry";

    public ElementGeometry() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddGeometryParameter(PropertyName, PropertyName.Substring(0, 1), ObjectType.Name + " parameter names", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      DB.Options options = null;
      using (var geometry = element?.GetGeometry(DB.ViewDetailLevel.Fine, out options)) using (options)
      {
        var list = geometry?.ToRhino().Where(x => x is object).ToList();

        switch (element.get_Parameter(DB.BuiltInParameter.ELEMENT_IS_CUTTING)?.AsInteger())
        {
          case 0: // SOLID
            foreach (var geo in list.OfType<Rhino.Geometry.Brep>().Where(x => x.SolidOrientation == Rhino.Geometry.BrepSolidOrientation.Inward))
              geo.Flip();
            break;
          case 1: // VOID
            foreach (var geo in list.OfType<Rhino.Geometry.Brep>().Where(x => x.SolidOrientation == Rhino.Geometry.BrepSolidOrientation.Outward))
              geo.Flip();
            break;
        }

        DA.SetDataList(PropertyName, list);
      }
    }
  }

  public class ElementPreview : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("A95C7B73-6F70-46CA-85FC-A4402A3B6971");
    static readonly string PropertyName = "Preview";

    public ElementPreview() : base(PropertyName) { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      base.RegisterInputParams(manager);
      var detail = manager[manager.AddIntegerParameter("DetailLevel", "LOD", ObjectType.Name + " LOD [1, 3]", GH_ParamAccess.item)] as Grasshopper.Kernel.Parameters.Param_Integer;
      detail.Optional = true;
      detail.AddNamedValue("Coarse", 1);
      detail.AddNamedValue("Medium", 2);
      detail.AddNamedValue("Fine",   3);
      manager[manager.AddNumberParameter("Quality", "Q", ObjectType.Name + " meshes quality [0.0, 1.0]", GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddMeshParameter("Meshes", "M", ObjectType.Name + " meshes", GH_ParamAccess.list);
      manager.AddParameter(new Grasshopper.Kernel.Parameters.Param_OGLShader(), "Materials", "M", ObjectType.Name + " materials", GH_ParamAccess.list);
      manager.AddCurveParameter("Wires", "W", ObjectType.Name + " wires", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Types.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      var detailLevel = DB.ViewDetailLevel.Undefined;
      int detailLevelValue = (int) detailLevel;
      if (DA.GetData(1, ref detailLevelValue))
      {
        if ((int) DB.ViewDetailLevel.Coarse > detailLevelValue || detailLevelValue > (int) DB.ViewDetailLevel.Fine)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' range is [1, 3].", Params.Input[1].Name));
          return;
        }

        detailLevel = (DB.ViewDetailLevel) detailLevelValue;
      }

      double RelativeTolerance = double.NaN;
      if (DA.GetData(2, ref RelativeTolerance))
      {
        if(0.0 > RelativeTolerance || RelativeTolerance > 1.0)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' range is [0.0, 1.0].", Params.Input[2].Name));
          return;
        }
      }

      var meshingParameters = !double.IsNaN(RelativeTolerance) ? new Rhino.Geometry.MeshingParameters(RelativeTolerance, Revit.VertexTolerance) : null;
      Types.GeometricElement.BuildPreview((DB.Element) element, meshingParameters, detailLevel, out var materials, out var meshes, out var wires);

      DA.SetDataList(0, meshes?.Select((x) => new GH_Mesh(x)));
      DA.SetDataList(1, materials?.Select((x) => new GH_Material(x)));
      DA.SetDataList(2, wires?.Select((x) => new GH_Curve(x)));
    }
  }

  public class ElementParameters : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("44515A6B-84EE-4DBD-8241-17EDBE07C5B6");
    static readonly string PropertyName = "Parameters";

    public ElementParameters() : base(PropertyName) { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      base.RegisterInputParams(manager);
      manager[manager.AddTextParameter("Name", "N", "Filter params by Name", GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.BuiltInParameterGroup(), "Group", "G", "Filter params by the group they belong", GH_ParamAccess.item)].Optional = true;
      manager[manager.AddBooleanParameter("ReadOnly", "R", "Filter params by its ReadOnly property", GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterKey(), "Parameters", "P", "Element parameters", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      string parameterName = null;
      bool noFilterName = (!DA.GetData("Name", ref parameterName) && Params.Input[1].Sources.Count == 0);

      var builtInParameterGroup = DB.BuiltInParameterGroup.INVALID;
      bool noFilterGroup = (!DA.GetData("Group", ref builtInParameterGroup) && Params.Input[2].Sources.Count == 0);

      bool readOnly = false;
      bool noFilterReadOnly = (!DA.GetData("ReadOnly", ref readOnly) && Params.Input[3].Sources.Count == 0);

      List<DB.Parameter> parameters = null;
      if (element is object)
      {
        parameters = new List<DB.Parameter>(element.Parameters.Size);
        foreach (var group in element.GetParameters(RevitAPI.ParameterSource.Any).GroupBy((x) => x.Definition?.ParameterGroup ?? DB.BuiltInParameterGroup.INVALID).OrderBy((x) => x.Key))
        {
          foreach (var param in group.OrderBy(x => x.Id.IntegerValue))
          {
            if (!noFilterName && parameterName != param.Definition?.Name)
              continue;

            if (!noFilterGroup && builtInParameterGroup != (param.Definition?.ParameterGroup ?? DB.BuiltInParameterGroup.INVALID))
              continue;

            if (!noFilterReadOnly && readOnly != param.IsReadOnly)
              continue;

            parameters.Add(param);
          }
        }
      }

      DA.SetDataList("Parameters", parameters);
    }
  }

  public class ElementDecompose : Component, IGH_VariableParameterComponent
  {
    public override Guid ComponentGuid => new Guid("FAD33C4B-A7C3-479B-B309-8F5363B25599");
    public ElementDecompose() : base("Element.Decompose", "Decompose", "Decomposes an Element into its parameters", "Revit", "Element") { }

    public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
    {
      base.AppendAdditionalMenuItems(menu);

      bool hasInputData = !Params.Input[0].VolatileData.IsEmpty;
      bool hasOutputParameters = Params.Output.Count > 0;

      Menu_AppendSeparator(menu);
      Menu_AppendItem(menu, "Get common parameters", Menu_PopulateOutputsWithCommonParameters, hasInputData, false);
      Menu_AppendItem(menu, "Get all parameters", Menu_PopulateOutputsWithAllParameters, hasInputData, false);
      Menu_AppendItem(menu, "Remove unconnected parameters", Menu_RemoveUnconnectedParameters, hasOutputParameters, false);
    }

    class ComponentAttributes : GH_ComponentAttributes
    {
      public ComponentAttributes(IGH_Component component) : base(component) { }

      public override GH_ObjectResponse RespondToMouseDoubleClick(GH_Canvas sender, GH_CanvasMouseEvent e)
      {
        bool ctrl  = Control.ModifierKeys == Keys.Control;
        bool shift = Control.ModifierKeys == Keys.Shift;

        if (e.Button == MouseButtons.Left && (ctrl || shift))
        {
          if (!Owner.Params.Input[0].VolatileData.IsEmpty)
          {
            if (Owner is ElementDecompose elementDecompose)
            {
              sender.ActiveInteraction = null;
              if (shift)
                elementDecompose.Menu_PopulateOutputsWithCommonParameters(sender, e);
              else if (ctrl)
                elementDecompose.Menu_RemoveUnconnectedParameters(sender, e);

              return GH_ObjectResponse.Handled;
            }
          }
        }

        return GH_ObjectResponse.Ignore;
      }
    }

    public override void CreateAttributes() => m_attributes = new ComponentAttributes(this);

    void AddOutputParameter(IGH_Param param)
    {
      if (param.Attributes is null)
        param.Attributes = new GH_LinkedParamAttributes(param, Attributes);

      param.Access = GH_ParamAccess.item;
      Params.RegisterOutputParam(param);
    }

    class EqualityComparer : IEqualityComparer<KeyValuePair<int, DB.Parameter>>
    {
      bool IEqualityComparer<KeyValuePair<int, DB.Parameter>>.Equals(KeyValuePair<int, DB.Parameter> x, KeyValuePair<int, DB.Parameter> y) => x.Key == y.Key;
      int IEqualityComparer<KeyValuePair<int, DB.Parameter>>.GetHashCode(KeyValuePair<int, DB.Parameter> obj) => obj.Key;
    }

    void Menu_PopulateOutputsWithCommonParameters(object sender, EventArgs e)
    {
      IEnumerable<KeyValuePair<int, DB.Parameter>> common = null;

      foreach (var goo in Params.Input[0].VolatileData.AllData(true).OfType<Types.Element>())
      {
        var definitions = new Dictionary<int, DB.Parameter>();

        var element = (DB.Element) goo;
        if (element is null)
          continue;

        foreach (var param in element.Parameters.OfType<DB.Parameter>())
        {
          try { definitions.Add(param.Id.IntegerValue, param); }
          catch (System.ArgumentException) { }
        }

        if (common is null)
          common = definitions;
        else
          common = common.Intersect(definitions, new EqualityComparer());
      }

      if (common is object)
      {
        RecordUndoEvent("Get Common Parameters");

        foreach (var output in Params.Output.ToArray())
          Params.UnregisterOutputParameter(output);

        foreach (var group in common.GroupBy((x) => x.Value.Definition.ParameterGroup).OrderBy((x) => x.Key))
        {
          foreach (var pair in group.OrderBy(x => x.Value.Id.IntegerValue))
            AddOutputParameter(new Parameters.ParameterParam(pair.Value));
        }

        Params.OnParametersChanged();
        ExpireSolution(true);
      }
    }

    void Menu_PopulateOutputsWithAllParameters(object sender, EventArgs e)
    {
      var definitions = new Dictionary<int, DB.Parameter>();

      foreach (var goo in Params.Input[0].VolatileData.AllData(true).OfType<Types.Element>())
      {
        var element = (DB.Element) goo;
        if (element is null)
          continue;

        foreach (var param in element.Parameters.OfType<DB.Parameter>())
        {
          try { definitions.Add(param.Id.IntegerValue, param); }
          catch (System.ArgumentException) { }
        }
      }

      if (definitions is object)
      {
        RecordUndoEvent("Get All Parameters");

        foreach (var output in Params.Output.ToArray())
          Params.UnregisterOutputParameter(output);

        foreach (var group in definitions.GroupBy((x) => x.Value.Definition.ParameterGroup).OrderBy((x) => x.Key))
        {
          foreach (var definition in group.OrderBy(x => x.Value.Id.IntegerValue))
            AddOutputParameter(new Parameters.ParameterParam(definition.Value));
        }

        Params.OnParametersChanged();
        ExpireSolution(true);
      }
    }

    void Menu_RemoveUnconnectedParameters(object sender, EventArgs e)
    {
      RecordUndoEvent("Remove Unconnected Outputs");

      foreach (var output in Params.Output.ToArray())
      {
        if (output.Recipients.Count > 0)
          continue;

        Params.UnregisterOutputParameter(output);
      }

      Params.OnParametersChanged();
      OnDisplayExpired(false);
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to inspect", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager) { }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      for (int p = 0; p < Params.Output.Count; ++p)
      {
        if (Params.Output[p] is Parameters.ParameterParam instance)
        {
          var parameterId = instance.ParameterId;
          if (Enum.IsDefined(typeof(DB.BuiltInParameter), parameterId))
          {
            DA.SetData(p, element.get_Parameter((DB.BuiltInParameter) parameterId));
          }
          else if (element.Document.GetElement(new DB.ElementId(parameterId)) is DB.ParameterElement parameterelement)
          {
            DA.SetData(p, element.get_Parameter(parameterelement.GetDefinition()));
          }
        }
      }
    }

    bool IGH_VariableParameterComponent.CanInsertParameter(GH_ParameterSide side, int index) => false;
    bool IGH_VariableParameterComponent.CanRemoveParameter(GH_ParameterSide side, int index) => side == GH_ParameterSide.Output;
    IGH_Param IGH_VariableParameterComponent.CreateParameter(GH_ParameterSide side, int index) => null;
    bool IGH_VariableParameterComponent.DestroyParameter(GH_ParameterSide side, int index) => true;
    void IGH_VariableParameterComponent.VariableParameterMaintenance() { }

    protected override string HtmlHelp_Source()
    {
      var nTopic = new Grasshopper.GUI.HTML.GH_HtmlFormatter(this)
      {
        Title = Name,
        Description =
        @"<p>This component is a special interface object that allows for quick accessing to Revit Element parameters.</p>" +
        @"<p>It's able to modify itself in order to show any parameter its input element parameter contains. " +
        @"It also allows to remove some output parameters if are not connected to anything else.</p>" +
        @"<p>Under the component contextual menu you would find these options:</p>" +
        @"<dl>" +
        @"<dt><b>Get common parameters</b></dt><dd>Populates the output parameters list with common parameters in all input elements</dd>" +
        @"<dt><b>Get all parameters</b></dt><dd>Populates the output parameters list with all parameters found in all input elements</dd>" +
        @"<dt><b>Remove unconnected parameters</b></dt><dd>Removes the output parameters that are not connected to anything else</dd>" +
        @"</dl>",
        ContactURI = @"https://discourse.mcneel.com/c/serengeti/inside"
      };

      nTopic.AddRemark("SHIFT + Double click runs \"Get common parameters\"");
      nTopic.AddRemark("CTRL + Double click runs \"Remove unconnected parameters\".");

      return nTopic.HtmlFormat();
    }
  }

  static class ParameterUtils
  {
    public static DB.Parameter GetParameter(IGH_ActiveObject obj, DB.Element element, IGH_Goo key)
    {
      DB.Parameter parameter = null;
      switch (key as Types.ParameterKey ?? key.ScriptVariable())
      {
        case Types.ParameterKey parameterKey:
          if (parameterKey.Document.Equals(element.Document))
          {
            if (Enum.IsDefined(typeof(DB.BuiltInParameter), parameterKey.Id.IntegerValue))
            {
              parameter = element.get_Parameter((DB.BuiltInParameter) parameterKey.Id.IntegerValue);
              if (parameter is null)
                obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{DB.LabelUtils.GetLabelFor((DB.BuiltInParameter) parameterKey.Id.IntegerValue)}' not defined in 'Element'");
            }
            else if (element.Document.GetElement(parameterKey.Id) is DB.ParameterElement parameterElement)
            {
              parameter = element.get_Parameter(parameterElement.GetDefinition());
              if (parameter is null)
                obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{parameterElement.Name}' not defined in 'Element'");
            }
            else
              obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Data conversion failed from {key.TypeName} to Revit Parameter element");
          }
          else
            obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"'ParameterKey' doesn't belong same document as 'Element'");

          break;

        case DB.Parameter param:
          if (param.Element.Document.Equals(element.Document) && param.Element.Id == element.Id)
            parameter = param;
          else
            obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Parameter '{param.Definition.Name}' doesn't belong to 'Element'");

          break;

        case string parameterName:
          parameter = element.LookupParameter(parameterName);
          if (parameter is null)
            obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{parameterName}' not defined in 'Element'");
          break;

        case int parameterId:
          if (Enum.IsDefined(typeof(DB.BuiltInParameter), parameterId))
          {
            parameter = element.get_Parameter((DB.BuiltInParameter) parameterId);
            if (parameter is null)
              obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{DB.LabelUtils.GetLabelFor((DB.BuiltInParameter) parameterId)}' not defined in 'Element'");
          }
          else if (element.Document.GetElement(new DB.ElementId(parameterId)) is DB.ParameterElement parameterElement)
          {
            parameter = element.get_Parameter(parameterElement.GetDefinition());
            if (parameter is null)
              obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{parameterElement.Name}' not defined in 'Element'");
          }
          else
            obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Data conversion failed from {key.TypeName} to Revit Parameter element");
          break;

        case DB.ElementId parameterElementId:
          if (Enum.IsDefined(typeof(DB.BuiltInParameter), parameterElementId.IntegerValue))
          {
            parameter = element.get_Parameter((DB.BuiltInParameter) parameterElementId.IntegerValue);
            if (parameter is null)
              obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{DB.LabelUtils.GetLabelFor((DB.BuiltInParameter) parameterElementId.IntegerValue)}' not defined in 'Element'");
          }
          else if (element.Document.GetElement(parameterElementId) is DB.ParameterElement parameterElement)
          {
            parameter = element.get_Parameter(parameterElement.GetDefinition());
            if (parameter is null)
              obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{parameterElement.Name}' not defined in 'Element'");
          }
          else
            obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Data conversion failed from {key.TypeName} to Revit Parameter element");
          break;

        default:
          obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Data conversion failed from {key.TypeName} to Revit Parameter element");
          break;
      }

      return parameter;
    }

    public static bool SetParameter(IGH_ActiveObject obj, DB.Element element, DB.Parameter parameter, IGH_Goo goo)
    {
      try
      {
        var value = goo.ScriptVariable();
        switch (parameter?.StorageType)
        {
          case DB.StorageType.Integer:
          {
            switch (value)
            {
              case bool boolean: parameter.Set(boolean ? 1 : 0); break;
              case int integer: parameter.Set(integer); break;
              case double real: parameter.Set(Math.Round(ToHost(real, parameter.Definition.ParameterType)).Clamp(int.MinValue, int.MaxValue)); break;
              case System.Drawing.Color color: parameter.Set(((int) color.R) | ((int) color.G << 8) | ((int) color.B << 16)); break;
              default: element = null; break;
            }
            break;
          }
          case DB.StorageType.Double:
          {
            switch (value)
            {
              case int integer: parameter.Set((double) integer); break;
              case double real: parameter.Set(ToHost(real, parameter.Definition.ParameterType)); break;
              default: element = null; break;
            }
            break;
          }
          case DB.StorageType.String:
          {
            switch (value)
            {
              case string str: parameter.Set(str); break;
              default: element = null; break;
            }
            break;
          }
          case DB.StorageType.ElementId:
          {
            switch (value)
            {
              case DB.Element ele: parameter.Set(ele.Id); break;
              case DB.Category cat: parameter.Set(cat.Id); break;
              case int integer: parameter.Set(new DB.ElementId(integer)); break;
              default: element = null; break;
            }
            break;
          }
          default:
          {
            element = null;
            break;
          }
        }

        if (element is null && parameter is object)
          obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Unable to cast 'Value' from {0} to {1}.", value.GetType().Name, parameter.StorageType.ToString()));

        return true;
      }
      catch (Exception e)
      {
        obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Unable to set 'Value' to parameter {0} : {1}", parameter.Definition.Name, e.Message));
      }

      return false;
    }

    static double ToHost(double value, DB.ParameterType type)
    {
      switch (type)
      {
        case DB.ParameterType.Length: return value / Math.Pow(Revit.ModelUnits, 1.0);
        case DB.ParameterType.Area:   return value / Math.Pow(Revit.ModelUnits, 2.0);
        case DB.ParameterType.Volume: return value / Math.Pow(Revit.ModelUnits, 3.0);
      }

      return value;
    }
  }

  public class ElementParameterGet : Component
  {
    public override Guid ComponentGuid => new Guid("D86050F2-C774-49B1-9973-FB3AB188DC94");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public ElementParameterGet()
    : base("Element.ParameterGet", "ParameterGet", "Gets the parameter value of a specified Revit Element", "Revit", "Element")
    {}

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to query", GH_ParamAccess.item);
      manager.AddGenericParameter("ParameterKey", "K", "Element parameter to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterValue(), "ParameterValue", "V", "Element parameter value", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      IGH_Goo parameterKey = null;
      if (!DA.GetData("ParameterKey", ref parameterKey))
        return;

      var parameter = ParameterUtils.GetParameter(this, element, parameterKey);
      DA.SetData("ParameterValue", parameter);
    }
  }

  public class ElementParameterSet : TransactionsComponent
  {
    public override Guid ComponentGuid => new Guid("8F1EE110-7FDA-49E0-BED4-E8E0227BC021");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public ElementParameterSet()
    : base("Element.ParameterSet", "ParameterSet", "Sets the parameter value of a specified Revit Element", "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to update", GH_ParamAccess.item);
      manager.AddGenericParameter("ParameterKey", "K", "Element parameter to modify", GH_ParamAccess.item);
      manager.AddGenericParameter("ParameterValue", "V", "Element parameter value", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Updated Element", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      IGH_Goo key = null;
      if (!DA.GetData("ParameterKey", ref key))
        return;

      IGH_Goo value = null;
      if (!DA.GetData("ParameterValue", ref value))
        return;

      var parameter = ParameterUtils.GetParameter(this, element, key);
      if (parameter is null)
        return;

      BeginTransaction(element.Document);

      if (ParameterUtils.SetParameter(this, element, parameter, value))
        DA.SetData("Element", element);
    }
  }
}
