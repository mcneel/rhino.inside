using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;
using GH_IO.Serialization;
using Grasshopper;
using Grasshopper.GUI;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Data;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;

namespace RhinoInside.Revit.GH.Types
{
  public abstract class GeometryObject<X> :
    GH_Goo<X>,
    IElementId,
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
    bool IGH_GeometricGoo.IsReferencedGeometry => false;
    bool IGH_GeometricGoo.IsGeometryLoaded => IsElementLoaded;

    void IGH_GeometricGoo.ClearCaches() { }
    IGH_GeometricGoo IGH_GeometricGoo.DuplicateGeometry() => (IGH_GeometricGoo) MemberwiseClone();
    public abstract BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform);
    bool IGH_GeometricGoo.LoadGeometry() => false;
    bool IGH_GeometricGoo.LoadGeometry(Rhino.RhinoDoc doc) => false;
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
          point = new Rhino.Geometry.Point(Value.Coord.ToRhino());
          point.Scale(Revit.ModelUnits);

          using
          (
            var element = Reference != null ?
            Revit.ActiveDBDocument.GetElement(Reference) :
            null
          )
          {
            if (element is Instance instance)
            {
              var transform = instance.GetTransform();
              transform.Origin = transform.Origin.Multiply(Revit.ModelUnits);
              var xform = transform.ToRhino();

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
        Value = Autodesk.Revit.DB.Point.Create(point.Value.Scale(1.0 / Revit.ModelUnits).ToHost());
        UniqueID = string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (Value != null)
      {
        if (typeof(Q).IsAssignableFrom(typeof(GH_Point)))
        {
          target = (Q) (object) new GH_Point(Point.Location);
          return true;
        }
        else if (Reference != null && typeof(Q).IsAssignableFrom(typeof(Element)))
        {
          var element = Revit.ActiveDBDocument.GetElement(Reference);
          target = (Q) (object) Element.Make(element);
          return true;
        }
      }

      return base.CastTo<Q>(ref target);
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
              var transform = instance.GetTransform();
              transform.Origin = transform.Origin.Multiply(Revit.ModelUnits);
              var xform = transform.ToRhino();

              wires[0]?.Transform(xform);
            }
          }
        }

        return wires.FirstOrDefault();
      }
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (Value != null)
      {
        if (typeof(Q).IsAssignableFrom(typeof(GH_Curve)))
        {
          target = (Q) (object) new GH_Curve(Curve);
          return true;
        }
        else if (Reference != null && typeof(Q).IsAssignableFrom(typeof(Element)))
        {
          var element = Revit.ActiveDBDocument.GetElement(Reference);
          target = (Q) (object) Element.Make(element);
          return true;
        }
      }

      return base.CastTo<Q>(ref target);
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
              var transform = instance.GetTransform();
              transform.Origin = transform.Origin.Multiply(Revit.ModelUnits);
              var xform = transform.ToRhino();

              foreach(var wire in wires)
                wire.Transform(xform);
            }
          }
        }

        return wires;
      }
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (Value != null)
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
        else if (element != null && typeof(Q).IsAssignableFrom(typeof(Element)))
        {
          target = (Q) (object) Element.Make(element);
          return true;
        }
      }

      return base.CastTo<Q>(ref target);
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
  public interface IGH_PersistentElementParam
  {
    bool NeedsToBeExpired(Document doc, ICollection<ElementId> added, ICollection<ElementId> deleted, ICollection<ElementId> modified);
  }

  public abstract class GH_PersistentGeometryParam<X> :
  Grasshopper.Kernel.GH_PersistentGeometryParam<X>,
  IGH_PreviewObject,
  IGH_PersistentElementParam
  where X : class, IGH_GeometricGoo
  {
    protected GH_PersistentGeometryParam(string name, string nickname, string description, string category, string subcategory) :
    base(new GH_InstanceDescription(name, nickname, description, category, subcategory)) { }
    protected override System.Drawing.Bitmap Icon => ((System.Drawing.Bitmap) Properties.Resources.ResourceManager.GetObject(GetType().Name));

    #region UI methods
    protected override void PrepareForPrompt()  { }
    protected override void RecoverFromPrompt() { }

    public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
    {
      base.AppendAdditionalMenuItems(menu);
      Menu_AppendSeparator(menu);
      Menu_AppendItem(menu, "Highlight elements", Menu_HighlightElements, !VolatileData.IsEmpty, false);
      Menu_AppendItem(menu, "Delete elements", Menu_DeleteElements, DataType != GH_ParamData.remote && !VolatileData.IsEmpty, false);
      this.Menu_AppendConnect(menu, Menu_Connect);
    }

    private void Menu_Connect(object sender, EventArgs e)
    {
      if (sender is ToolStripMenuItem item && item.Tag is Guid componentGuid)
      {
        var obj = this.ConnectNewObject(componentGuid);
        if (obj is null)
          return;

        obj.ExpireSolution(true);
      }
    }

    internal static IEnumerable<ElementId> ToElementIds(IGH_Structure data) =>
      data.AllData(true).
      OfType<Types.Element>().
      Where(x => x != null).
      Select(x => x.Value);

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

    void Menu_DeleteElements(object sender, EventArgs e)
    {
      var elementIds = ToElementIds(VolatileData);
      if (elementIds.Any())
      {
        using (new ModalForm.EditScope())
        {
          using
          (
            var taskDialog = new TaskDialog(MethodBase.GetCurrentMethod().DeclaringType.FullName)
            {
              MainIcon = TaskDialogIcons.IconWarning,
              TitleAutoPrefix = false,
              Title = "Delete Elements",
              MainInstruction = "Are you sure you want to delete those elements?",
              CommonButtons = TaskDialogCommonButtons.Yes | TaskDialogCommonButtons.No,
              DefaultButton = TaskDialogResult.Yes,
              AllowCancellation = true,
#if REVIT_2020
              EnableMarqueeProgressBar = true
#endif
            }
          )
          {
            taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink1, "Show elements");
            taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink2, "Manage element collection");

            var result = TaskDialogResult.None;
            bool highlight = false;
            do
            {
              var elements = elementIds.ToArray();
              taskDialog.ExpandedContent = $"{elements.Length} elements and its depending elements will be deleted.";

              if(highlight)
                Revit.ActiveUIDocument.Selection.SetElementIds(elements);

              switch (result = taskDialog.Show())
              {
                case TaskDialogResult.CommandLink1:
                  Revit.ActiveUIDocument.ShowElements(elements);
                  highlight = true;
                  break;

                case TaskDialogResult.CommandLink2:
                  using (var dataManager = new GH_PersistentDataEditor())
                  {
                    var elementCollection = new GH_Structure<IGH_Goo>();
                    elementCollection.AppendRange(elementIds.Select(x => Types.Element.Make(x)));
                    dataManager.SetData(elementCollection, new Types.Element());

                    GH_WindowsFormUtil.CenterFormOnCursor(dataManager, true);
                    if (dataManager.ShowDialog(ModalForm.OwnerWindow) == System.Windows.Forms.DialogResult.OK)
                      elementIds = dataManager.GetData<IGH_Goo>().AllData(true).OfType<Types.Element>().Select(x => x.Value);
                  }
                  break;

                case TaskDialogResult.Yes:
                  using (var transaction = new Transaction(Revit.ActiveDBDocument, "Delete elements"))
                  {
                    transaction.Start();
                    Revit.ActiveDBDocument.Delete(elements);
                    transaction.Commit();
                  }

                  ExpireDownStreamObjects();
                  OnPingDocument().NewSolution(false);
                  break;
              }
            }
            while (result == TaskDialogResult.CommandLink1 || result == TaskDialogResult.CommandLink2);
          }
        }
      }
    }
#endregion

#region IGH_PreviewObject
    bool IGH_PreviewObject.Hidden { get; set; }
    bool IGH_PreviewObject.IsPreviewCapable => !VolatileData.IsEmpty;
    Rhino.Geometry.BoundingBox IGH_PreviewObject.ClippingBox => Preview_ComputeClippingBox();
    void IGH_PreviewObject.DrawViewportMeshes(IGH_PreviewArgs args) => Preview_DrawMeshes(args);
    void IGH_PreviewObject.DrawViewportWires(IGH_PreviewArgs args) => Preview_DrawWires(args);
#endregion

#region IGH_PersistentGeometryParam
    bool IGH_PersistentElementParam.NeedsToBeExpired(Document doc, ICollection<ElementId> added, ICollection<ElementId> deleted, ICollection<ElementId> modified)
    {
      foreach (var data in VolatileData.AllData(true).OfType<Types.Element>())
      {
        if (!data.IsElementLoaded)
          continue;

        if (modified.Contains(data.Value))
          return true;

        if (deleted.Contains(data.Value))
          return true;
      }

      return false;
    }
#endregion
  }

  public class Vertex : GH_PersistentGeometryParam<Types.Vertex>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("BC1B160A-DC04-4139-AB7D-1AECBDE7FF88");
    public Vertex() : base("Vertex", "Vertex", "Represents a Revit vertex.", "Params", "Revit") { }

#region UI methods
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

  public class Edge : GH_PersistentGeometryParam<Types.Edge>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("B79FD0FD-63AE-4776-A0A7-6392A3A58B0D");
    public Edge() : base("Edge", "Edge", "Represents a Revit edge.", "Params", "Revit") { }

#region UI methods
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

  public class Face : GH_PersistentGeometryParam<Types.Face>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("759700ED-BC79-4986-A6AB-84921A7C9293");
    public Face() : base("Face", "Face", "Represents a Revit face.", "Params", "Revit") { }

#region UI methods
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
