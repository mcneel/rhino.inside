using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI.Selection;
using GH_IO.Serialization;
using Grasshopper;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;

namespace RhinoInside.Revit.GH.Types
{
  public class GeometricElement : Element
  {
    public override string TypeName => "Revit Geometric element";
    public override string TypeDescription => "Represents a Revit geometric element";

    public GeometricElement() { }
    public GeometricElement(Autodesk.Revit.DB.Element element) : base(element) { }
    public override bool SetValue(Autodesk.Revit.DB.Element element) => IsValidElement(element) ? base.SetValue(element) : false;
    public static bool IsValidElement(Autodesk.Revit.DB.Element element)
    {
      if (element?.Category is Autodesk.Revit.DB.Category category && !(element is Autodesk.Revit.DB.ElementType))
        return category.Parent is null && category.IsVisibleInUI;

      return false;
    }
  }

  public abstract class GeometryObject<X> :
    GH_Goo<X>,
    IGH_ElementId,
    IGH_GeometricGoo,
    IGH_PreviewMeshData
    where X : Autodesk.Revit.DB.GeometryObject
  {
    public override string TypeName => "Revit GeometryObject";
    public override string TypeDescription => "Represents a Revit GeometryObject";
    public override bool IsValid => !(Value is null);
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();
    protected virtual Type ScriptVariableType => typeof(X);

    #region IPersistentId
    public Reference Reference { get; protected set; }
    public ElementId Id => Reference.ElementId;
    public bool IsReferencedElement => !string.IsNullOrEmpty(UniqueID);
    public string UniqueID { get; protected set; } = string.Empty;
    public bool IsElementLoaded => !(Value is null);
    public virtual bool LoadElement(Document doc)
    {
      Value = null;

      try
      {
        Reference = Reference ?? Reference.ParseFromStableRepresentation(doc, UniqueID);
        var element = doc.GetElement(Reference);
        var geometry = element?.GetGeometryObjectFromReference(Reference);
        if (geometry is X item)
        {
          Value = item;
        }
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException) { }

      return IsElementLoaded;
    }
    public void UnloadElement() => Value = null;
    #endregion

    #region IGH_GeometricGoo
    BoundingBox IGH_GeometricGoo.Boundingbox => GetBoundingBox(Rhino.Geometry.Transform.Identity);
    Guid IGH_GeometricGoo.ReferenceID
    {
      get => Guid.Empty;
      set { if (value != Guid.Empty) throw new InvalidOperationException(); }
    }
    bool IGH_GeometricGoo.IsReferencedGeometry => IsReferencedElement;
    bool IGH_GeometricGoo.IsGeometryLoaded => IsElementLoaded;

    void IGH_GeometricGoo.ClearCaches() => UnloadElement();
    IGH_GeometricGoo IGH_GeometricGoo.DuplicateGeometry() => (IGH_GeometricGoo) MemberwiseClone();
    public abstract BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform);
    bool IGH_GeometricGoo.LoadGeometry(                  ) => IsElementLoaded || LoadElement(Revit.ActiveDBDocument);
    bool IGH_GeometricGoo.LoadGeometry(Rhino.RhinoDoc doc) => IsElementLoaded || LoadElement(Revit.ActiveDBDocument);
    IGH_GeometricGoo IGH_GeometricGoo.Transform(Rhino.Geometry.Transform xform) => null;
    IGH_GeometricGoo IGH_GeometricGoo.Morph(Rhino.Geometry.SpaceMorph xmorph) => null;

    public override sealed string ToString()
    {
      if (!IsValid)
        return "Null " + TypeName;

      try
      {
        string typeName = TypeName;
        var element = Revit.ActiveDBDocument.GetElement(Reference);
        if (element != null)
        {
          typeName = "Referenced ";
          switch (Reference.ElementReferenceType)
          {
            case ElementReferenceType.REFERENCE_TYPE_NONE: typeName += "geometry"; break;
            case ElementReferenceType.REFERENCE_TYPE_LINEAR: typeName += "edge"; break;
            case ElementReferenceType.REFERENCE_TYPE_SURFACE: typeName += "face"; break;
            case ElementReferenceType.REFERENCE_TYPE_FOREIGN: typeName += "external geometry"; break;
            case ElementReferenceType.REFERENCE_TYPE_INSTANCE: typeName += "instance"; break;
            case ElementReferenceType.REFERENCE_TYPE_CUT_EDGE: typeName += "trim"; break;
            case ElementReferenceType.REFERENCE_TYPE_MESH: typeName += "mesh"; break;
#if REVIT_2018
            case ElementReferenceType.REFERENCE_TYPE_SUBELEMENT: typeName += "subelement"; break;
#endif
          }

          typeName += " at Revit " + element.GetType().Name + " \"" + element.Name + "\"";
        }

#if DEBUG
        typeName += " (" + Reference.ConvertToStableRepresentation(Revit.ActiveDBDocument) + ")";
#endif
        return typeName;
      }
      catch (ApplicationException)
      {
        return "Invalid" + TypeName;
      }
    }

    public override sealed bool Read(GH_IReader reader)
    {
      UniqueID = reader.GetString("UniqueID");
      return true;
    }

    public override sealed bool Write(GH_IWriter writer)
    {
      writer.SetString("UniqueID", UniqueID);
      return true;
    }
    #endregion

    #region IGH_PreviewMeshData
    protected Rhino.Geometry.Point   point = null;
    protected Rhino.Geometry.Curve[] wires = null;
    protected Rhino.Geometry.Mesh[]  meshes = null;

    void IGH_PreviewMeshData.DestroyPreviewMeshes()
    {
      point = null;
      wires = null;
      meshes = null;
    }

    Rhino.Geometry.Mesh[] IGH_PreviewMeshData.GetPreviewMeshes() => meshes;
    #endregion

    protected GeometryObject() { }
    protected GeometryObject(X data) : base(data) { }
    protected GeometryObject(Reference reference, Document doc) { Reference = reference; UniqueID = reference.ConvertToStableRepresentation(doc); }
  }

  public class Vertex : GeometryObject<Autodesk.Revit.DB.Point>, IGH_PreviewData
  {
    public override string TypeName => "Revit Vertex";
    public override string TypeDescription => "Represents a Revit Vertex";

    readonly int VertexIndex = -1;
    public override bool LoadElement(Document doc)
    {
      Value = null;

      try
      {
        Reference = Autodesk.Revit.DB.Reference.ParseFromStableRepresentation(doc, UniqueID);
        var element = doc.GetElement(Reference);
        var geometry = element?.GetGeometryObjectFromReference(Reference);
        if (geometry is Autodesk.Revit.DB.Edge edge)
        {
          var curve = edge.AsCurve();
          var points = new XYZ[] { curve.GetEndPoint(0), curve.GetEndPoint(1) };
          Value = Autodesk.Revit.DB.Point.Create(points[VertexIndex]);
        }
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException) { }

      return IsValid;
    }

    public Vertex() { }
    public Vertex(Autodesk.Revit.DB.Point data) : base(data) { }
    public Vertex(Reference reference, Document doc) : base(reference, doc) { }
    public Vertex(int index, Reference reference, Document doc) : base(reference, doc) { VertexIndex = index; }

    Rhino.Geometry.Point Point
    {
      get
      {
        if (point == null)
        {
          point = new Rhino.Geometry.Point(Value.Coord.ToRhino().ChangeUnits(Revit.ModelUnits));

          using
          (
            var element = Reference != null ?
            Revit.ActiveDBDocument.GetElement(Reference) :
            null
          )
          {
            if (element is Instance instance)
            {
              var xform = instance.GetTransform().ToRhino().ChangeUnits(Revit.ModelUnits);
              point.Transform(xform);
            }
          }
        }

        return point;
      }
    }

    public override bool CastFrom(object source)
    {
      if (source is GH_Point point)
      {
        Value = Autodesk.Revit.DB.Point.Create(point.Value.ChangeUnits(1.0 / Revit.ModelUnits).ToHost());
        UniqueID = string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (Value is object)
      {
        if (typeof(Q).IsAssignableFrom(typeof(GH_Point)))
        {
          target = (Q) (object) new GH_Point(Point.Location);
          return true;
        }
        else if (Reference is object && typeof(Q).IsAssignableFrom(typeof(Element)))
        {
          var element = Revit.ActiveDBDocument.GetElement(Reference);
          target = (Q) (object) Element.Make(element);
          return true;
        }
      }

      return base.CastTo(ref target);
    }

    public override BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform)
    {
      if (Value == null)
        return BoundingBox.Empty;

      return xform == Rhino.Geometry.Transform.Identity ?
        Point.GetBoundingBox(true) :
        Point.GetBoundingBox(xform);
    }

    #region IGH_PreviewData
    BoundingBox IGH_PreviewData.ClippingBox => GetBoundingBox(Rhino.Geometry.Transform.Identity);

    void IGH_PreviewData.DrawViewportWires(GH_PreviewWireArgs args)
    {
      if (!IsValid)
        return;

      if (Point is Rhino.Geometry.Point point)
        args.Pipeline.DrawPoint(point.Location, CentralSettings.PreviewPointStyle, CentralSettings.PreviewPointRadius, args.Color);
    }

    void IGH_PreviewData.DrawViewportMeshes(GH_PreviewMeshArgs args) { }
    #endregion
  }

  public class Edge : GeometryObject<Autodesk.Revit.DB.Edge>, IGH_PreviewData
  {
    public override string TypeName => "Revit Edge";
    public override string TypeDescription => "Represents a Revit Edge";

    public Edge() { }
    public Edge(Autodesk.Revit.DB.Edge edge) : base(edge) { }
    public Edge(Reference reference, Document doc) : base(reference, doc) { }

    Rhino.Geometry.Curve Curve
    {
      get
      {
        if (wires == null)
        {
          wires = Enumerable.Repeat(Value, 1).GetPreviewWires().ToArray();

          using
          (
            var element = Reference != null ?
            Revit.ActiveDBDocument.GetElement(Reference) :
            null
          )
          {
            if (element is Instance instance)
            {
              var xform = instance.GetTransform().ToRhino().ChangeUnits(Revit.ModelUnits);
              wires[0]?.Transform(xform);
            }
          }
        }

        return wires.FirstOrDefault();
      }
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (Value is object)
      {
        if (typeof(Q).IsAssignableFrom(typeof(GH_Curve)))
        {
          target = (Q) (object) new GH_Curve(Curve);
          return true;
        }
        else if (Reference is object && typeof(Q).IsAssignableFrom(typeof(Element)))
        {
          var element = Revit.ActiveDBDocument.GetElement(Reference);
          target = (Q) (object) Element.Make(element);
          return true;
        }
      }

      return base.CastTo(ref target);
    }

    public override BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform)
    {
      if (Value == null)
        return BoundingBox.Empty;

      return xform == Rhino.Geometry.Transform.Identity ?
        Curve.GetBoundingBox(true) :
        Curve.GetBoundingBox(xform);
    }

    #region IGH_PreviewData
    BoundingBox IGH_PreviewData.ClippingBox => GetBoundingBox(Rhino.Geometry.Transform.Identity);

    void IGH_PreviewData.DrawViewportWires(GH_PreviewWireArgs args)
    {
      if (!IsValid)
        return;

      if(Curve is Rhino.Geometry.Curve curve)
        args.Pipeline.DrawCurve(curve, args.Color, args.Thickness);
    }

    void IGH_PreviewData.DrawViewportMeshes(GH_PreviewMeshArgs args) { }
    #endregion
  }

  public class Face : GeometryObject<Autodesk.Revit.DB.Face>, IGH_PreviewData
  {
    public override string TypeName => "Revit Face";
    public override string TypeDescription => "Represents a Revit Face";

    public Face() { }
    public Face(Autodesk.Revit.DB.Face face) : base(face) { }
    public Face(Reference reference, Document doc) : base(reference, doc) { }

    Rhino.Geometry.Curve[] Curves
    {
      get
      {
        if (wires == null)
        {
          wires = Value.GetEdgesAsCurveLoops().SelectMany(x => x.GetPreviewWires()).ToArray();

          using
          (
            var element = Reference != null ?
            Revit.ActiveDBDocument.GetElement(Reference) :
            null
          )
          {
            if (element is Instance instance)
            {
              var xform = instance.GetTransform().ToRhino().ChangeUnits(Revit.ModelUnits);

              foreach (var wire in wires)
                wire.Transform(xform);
            }
          }
        }

        return wires;
      }
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (Value is object)
      {
        var element = Reference != null ? Revit.ActiveDBDocument.GetElement(Reference) : null;

        if (typeof(Q).IsAssignableFrom(typeof(GH_Surface)))
        {
          var brep = Value.ToRhino(true);
          if (element is Autodesk.Revit.DB.Instance instance)
            brep.Transform(Rhino.Geometry.Transform.Scale(Point3d.Origin, Revit.ModelUnits) * instance.GetTransform().ToRhino());
          else
            brep.Scale(Revit.ModelUnits);

          target = (Q) (object) new GH_Surface(brep);
          return true;
        }
        else if (typeof(Q).IsAssignableFrom(typeof(GH_Brep)))
        {
          var brep = Value.ToRhino(false);
          if (element is Autodesk.Revit.DB.Instance instance)
            brep.Transform(Rhino.Geometry.Transform.Scale(Point3d.Origin, Revit.ModelUnits) * instance.GetTransform().ToRhino());
          else
            brep.Scale(Revit.ModelUnits);

          target = (Q) (object) new GH_Brep(brep);
          return true;
        }
        else if (element is object && typeof(Q).IsAssignableFrom(typeof(Element)))
        {
          target = (Q) (object) Element.Make(element);
          return true;
        }
      }

      return base.CastTo(ref target);
    }

    public override BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform)
    {
      if (Value == null)
        return BoundingBox.Empty;

      var bbox = BoundingBox.Empty;
      if (xform == Rhino.Geometry.Transform.Identity)
      {
        foreach (var curve in Curves)
          bbox.Union(curve.GetBoundingBox(true));
      }
      else
      {
        foreach (var curve in Curves)
          bbox.Union(curve.GetBoundingBox(xform));
      }

      return bbox;
    }

    #region IGH_PreviewData
    BoundingBox IGH_PreviewData.ClippingBox => GetBoundingBox(Rhino.Geometry.Transform.Identity);

    void IGH_PreviewData.DrawViewportWires(GH_PreviewWireArgs args)
    {
      if (!IsValid)
        return;

      foreach (var curve in Curves ?? Enumerable.Empty<Rhino.Geometry.Curve>())
        args.Pipeline.DrawCurve(curve, args.Color, args.Thickness);
    }

    void IGH_PreviewData.DrawViewportMeshes(GH_PreviewMeshArgs args)
    {
      if (!IsValid)
        return;

      if (meshes == null)
      {
        using (var ga = Convert.GraphicAttributes.Push())
        {
          ga.MeshingParameters = args.MeshingParameters;
          meshes = Enumerable.Repeat(Value, 1).GetPreviewMeshes().ToArray();

          var element = Value.IsElementGeometry ?
            Revit.ActiveDBDocument.GetElement(Reference.ParseFromStableRepresentation(Revit.ActiveDBDocument, UniqueID)) :
            null;

          if (element is Instance instance)
          {
            var transform = instance.GetTransform();
            transform.Origin = transform.Origin.Multiply(Revit.ModelUnits);
            var xform = transform.ToRhino();

            foreach (var mesh in meshes)
              mesh.Transform(xform);
          }

          foreach (var mesh in meshes)
            mesh.Normals.ComputeNormals();
        }
      }

      foreach (var mesh in meshes ?? Enumerable.Empty<Rhino.Geometry.Mesh>())
        args.Pipeline.DrawMeshShaded(mesh, args.Material);
    }
    #endregion
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public abstract class ElementIdGeometryParam<X, R> : ElementIdParam<X, R>, IGH_PreviewObject
    where X : class, Types.IGH_ElementId
  {
    protected ElementIdGeometryParam(string name, string nickname, string description, string category, string subcategory) :
    base(name, nickname, description, category, subcategory) { }

    #region IGH_PreviewObject
    bool IGH_PreviewObject.Hidden { get; set; }
    bool IGH_PreviewObject.IsPreviewCapable => !VolatileData.IsEmpty;
    Rhino.Geometry.BoundingBox IGH_PreviewObject.ClippingBox => Preview_ComputeClippingBox();
    void IGH_PreviewObject.DrawViewportMeshes(IGH_PreviewArgs args) => Preview_DrawMeshes(args);
    void IGH_PreviewObject.DrawViewportWires(IGH_PreviewArgs args) => Preview_DrawWires(args);
    #endregion
  }

  public abstract class GeometricElementT<T, R> : ElementIdGeometryParam<T, R>, ISelectionFilter where T : Types.Element, new()
  {
    protected GeometricElementT(string name, string nickname, string description, string category, string subcategory) :
    base(name, nickname, description, category, subcategory)
    { }

    #region UI methods
    public override void AppendAdditionalElementMenuItems(ToolStripDropDown menu)
    {
      base.AppendAdditionalElementMenuItems(menu);
      Menu_AppendItem(menu, $"Highlight {GH_Convert.ToPlural(TypeName)}", Menu_HighlightElements, !VolatileData.IsEmpty, false);
    }

    void Menu_HighlightElements(object sender, EventArgs e)
    {
      var elementIds = ToElementIds(VolatileData);
      if (elementIds.Any())
      {
        var elements = elementIds.ToArray();
        Revit.ActiveUIDocument.Selection.SetElementIds(elements);
        Revit.ActiveUIDocument.ShowElements(elements);
      }
    }
    #endregion

    public virtual bool AllowElement(Autodesk.Revit.DB.Element elem) => elem is R;
    public bool AllowReference(Reference reference, XYZ position)
    {
      if (reference.ElementReferenceType == ElementReferenceType.REFERENCE_TYPE_NONE)
        return AllowElement(Revit.ActiveUIDocument.Document.GetElement(reference));

      return false;
    }

    protected override GH_GetterResult Prompt_Singular(ref T element)
    {
      element = null;

      try
      {
        using (new ModalForm.EditScope())
        {
#if REVIT_2018
          var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Subelement, this);
#else
          var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Element, this);
#endif
          if (reference is object)
            element = (T) Types.Element.Make(reference.ElementId);
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.success;
    }

    protected override GH_GetterResult Prompt_Plural(ref List<T> elements)
    {
      elements = null;

      var selection = Revit.ActiveUIDocument.Selection.GetElementIds();
      if (selection?.Count > 0)
      {
        var doc = Revit.ActiveUIDocument.Document;
        elements = selection.
          Where(x => AllowElement(doc.GetElement(x))).
          Select((x) => (T) Types.Element.Make(x)).ToList();
      }
      else
      {
        try
        {
          using (new ModalForm.EditScope())
          {
            var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Element, this);
            if (references is object)
              elements = references.Select((x) => (T) Types.Element.Make(x.ElementId)).ToList();
          }
        }
        catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }
      }
      return GH_GetterResult.success;
    }
  }

  public class GeometricElement : GeometricElementT<Types.GeometricElement, Autodesk.Revit.DB.Element>
  {
    public override GH_Exposure Exposure => GH_Exposure.primary;
    public override Guid ComponentGuid => new Guid("EF607C2A-2F44-43F4-9C39-369CE114B51F");

    public GeometricElement() : base("Geometric Element", "Geometric Element", "Represents a Revit document geometric element.", "Params", "Revit") { }

    protected override Types.GeometricElement PreferredCast(object data)
    {
      return data is Autodesk.Revit.DB.Element element && AllowElement(element) ?
             new Types.GeometricElement(element) :
             null;
    }

    public override bool AllowElement(Autodesk.Revit.DB.Element elem) => Types.GeometricElement.IsValidElement(elem);
  }

  public class Vertex : ElementIdGeometryParam<Types.Vertex, Autodesk.Revit.DB.Point>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("BC1B160A-DC04-4139-AB7D-1AECBDE7FF88");
    public Vertex() : base("Vertex", "Vertex", "Represents a Revit vertex.", "Params", "Revit") { }

    #region UI methods
    public override void AppendAdditionalElementMenuItems(ToolStripDropDown menu) { }
    protected override GH_GetterResult Prompt_Plural(ref List<Types.Vertex> value)
    {
      try
      {
        var values = new List<Types.Vertex>();
        Types.Vertex vertex = null;
        while(Prompt_Singular(ref vertex) == GH_GetterResult.success)
        {
          values.Add(vertex);
        }

        if (values.Count > 0)
        {
          value = values;
          return GH_GetterResult.success;
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.accept;
    }
    protected override GH_GetterResult Prompt_Singular(ref Types.Vertex value)
    {
      try
      {
        using (new ModalForm.EditScope())
        {
          var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Edge, "Click on an edge near an end to select a vertex, TAB for alternates, ESC quit.");
          if (reference != null)
          {
            var element = Revit.ActiveDBDocument.GetElement(reference);
            var geometry = element?.GetGeometryObjectFromReference(reference);
            if (geometry is Autodesk.Revit.DB.Edge edge)
            {
              var curve = edge.AsCurve();
              var result = curve.Project(reference.GlobalPoint);
              var points = new XYZ[] { curve.GetEndPoint(0), curve.GetEndPoint(1) };
              int index = result.XYZPoint.DistanceTo(points[0]) < result.XYZPoint.DistanceTo(points[1]) ? 0 : 1;

              value = new Types.Vertex(index, reference, Revit.ActiveDBDocument);
              return GH_GetterResult.success;
            }
          }
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.accept;
    }
    #endregion
  }

  public class Edge : ElementIdGeometryParam<Types.Edge, Autodesk.Revit.DB.Edge>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("B79FD0FD-63AE-4776-A0A7-6392A3A58B0D");
    public Edge() : base("Edge", "Edge", "Represents a Revit edge.", "Params", "Revit") { }

    #region UI methods
    public override void AppendAdditionalElementMenuItems(ToolStripDropDown menu) { }
    protected override GH_GetterResult Prompt_Plural(ref List<Types.Edge> value)
    {
      try
      {
        using (new ModalForm.EditScope())
        {
          var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Edge);
          if (references?.Count > 0)
          {
            value = references.Select((x) => new Types.Edge(x, Revit.ActiveDBDocument)).ToList();
            return GH_GetterResult.success;
          }
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.accept;
    }
    protected override GH_GetterResult Prompt_Singular(ref Types.Edge value)
    {
      try
      {
        using (new ModalForm.EditScope())
        {
          var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Edge);
          if (reference == null)
            return GH_GetterResult.accept;

          value = new Types.Edge(reference, Revit.ActiveDBDocument);
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.success;
    }
    #endregion
  }

  public class Face : ElementIdGeometryParam<Types.Face, Autodesk.Revit.DB.Face>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("759700ED-BC79-4986-A6AB-84921A7C9293");
    public Face() : base("Face", "Face", "Represents a Revit face.", "Params", "Revit") { }

    #region UI methods
    public override void AppendAdditionalElementMenuItems(ToolStripDropDown menu) { }
    protected override GH_GetterResult Prompt_Plural(ref List<Types.Face> value)
    {
      try
      {
        using (new ModalForm.EditScope())
        {
          var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Face);
          if (references?.Count > 0)
          {
            value = references.Select((x) => new Types.Face(x, Revit.ActiveDBDocument)).ToList();
            return GH_GetterResult.success;
          }
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.accept;
    }
    protected override GH_GetterResult Prompt_Singular(ref Types.Face value)
    {
      try
      {
        using (new ModalForm.EditScope())
        {
          var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Face);
          if (reference == null)
            return GH_GetterResult.accept;

          value = new Types.Face(reference, Revit.ActiveDBDocument);
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.success;
    }
    #endregion
  }
}
