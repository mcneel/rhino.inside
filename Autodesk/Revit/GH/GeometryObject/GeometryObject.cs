using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Autodesk.Revit.DB;
using GH_IO.Serialization;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;

namespace RhinoInside.Revit.GH.Types
{
  public interface IGH_GeometricGoo : Grasshopper.Kernel.Types.IGH_GeometricGoo
  {
    Reference Reference     { get; }
    string UniqueID         { get; }
    bool LoadGeometry(Document doc);
  }

  public abstract class GH_GeometricGoo<X> : Grasshopper.Kernel.Types.GH_GeometricGoo<X>, IGH_GeometricGoo where X : GeometryObject
  {
    public override string TypeName => "Revit GeometryObject";
    public override string TypeDescription => "Represents a Revit GeometryObject";
    public override bool IsValid => Value != null;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();
    protected virtual Type ScriptVariableType => typeof(X);

    #region IGH_GeometricGoo
    Guid Grasshopper.Kernel.Types.IGH_GeometricGoo.ReferenceID
    {
      // TODO: Generate a Guid using the Reference.ElementReferenceType and its index
      // get => Reference == null ? Guid.Empty : new Guid(Reference.ElementId == ElementId.InvalidElementId ? 0 : Reference.ElementId.IntegerValue, Reference.ElementIndex(), Reference.ElementReferenceType, 0, 0, 0, 0, 0, 0, 0, 0);
      get => Guid.Empty;
      set => throw new InvalidOperationException();
    }
    public Reference Reference { get; private set; }
    public string UniqueID { get; protected set; } = string.Empty;
    public override bool IsReferencedGeometry => !string.IsNullOrEmpty(UniqueID);
    public override bool IsGeometryLoaded => Value != null;
    public override bool LoadGeometry() => LoadGeometry(Revit.ActiveDBDocument);
    public virtual bool LoadGeometry(Document doc)
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
      catch(ArgumentException) { Reference = null; }

      return IsValid;
    }

    public override sealed Grasshopper.Kernel.Types.IGH_GeometricGoo DuplicateGeometry() => (IGH_GeometricGoo) MemberwiseClone();
    public override BoundingBox Boundingbox => GetBoundingBox(Rhino.Geometry.Transform.Identity);
    public override Grasshopper.Kernel.Types.IGH_GeometricGoo Transform(Rhino.Geometry.Transform xform) => null;
    public override Grasshopper.Kernel.Types.IGH_GeometricGoo Morph(Rhino.Geometry.SpaceMorph xmorph) => null;
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
          typeName = IsReferencedGeometry ? "Referenced " : string.Empty;
          switch (Reference.ElementReferenceType)
          {
            case ElementReferenceType.REFERENCE_TYPE_NONE: typeName += "geometry"; break;
            case ElementReferenceType.REFERENCE_TYPE_LINEAR: typeName += "edge"; break;
            case ElementReferenceType.REFERENCE_TYPE_SURFACE: typeName += "face"; break;
            case ElementReferenceType.REFERENCE_TYPE_FOREIGN: typeName += "external geometry"; break;
            case ElementReferenceType.REFERENCE_TYPE_INSTANCE: typeName += "instance"; break;
            case ElementReferenceType.REFERENCE_TYPE_CUT_EDGE: typeName += "trim"; break;
            case ElementReferenceType.REFERENCE_TYPE_MESH: typeName += "mesh"; break;
            case ElementReferenceType.REFERENCE_TYPE_SUBELEMENT: typeName += "subelement"; break;

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

    protected GH_GeometricGoo() { }
    protected GH_GeometricGoo(X data) : base(data) { }
    protected GH_GeometricGoo(Reference reference, Document doc) { Reference = reference; UniqueID = reference.ConvertToStableRepresentation(doc); }
  }

  public class Vertex : GH_GeometricGoo<Autodesk.Revit.DB.Point>
  {
    public override string TypeName => "Revit Vertex";
    public override string TypeDescription => "Represents a Revit Vertex";

    int VertexIndex = -1;
    public override bool LoadGeometry(Document doc)
    {
      Value = null;

      var reference = Autodesk.Revit.DB.Reference.ParseFromStableRepresentation(doc, UniqueID);
      var element = doc.GetElement(reference);
      var geometry = element?.GetGeometryObjectFromReference(reference);
      if (geometry is Autodesk.Revit.DB.Edge edge)
      {
        var curve = edge.AsCurve();
        var points = new XYZ[] { curve.GetEndPoint(0), curve.GetEndPoint(1) };
        Value = Autodesk.Revit.DB.Point.Create(points[VertexIndex]);
      }

      return IsValid;
    }

    public Vertex() { }
    public Vertex(Autodesk.Revit.DB.Point data) : base(data) { }
    public Vertex(Reference reference, Document doc) : base(reference, doc) { }
    public Vertex(int index, Reference reference, Document doc) : base(reference, doc) { VertexIndex = index; }

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
      if (typeof(Q).IsAssignableFrom(typeof(GH_Point)))
      {
        var point = Value.Coord.ToRhino();
        point = point.Scale(Revit.ModelUnits);
        target = (Q) (object) new GH_Point(point);
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public override BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform)
    {
      if (Value == null)
        return BoundingBox.Empty;

      bool IsIdentity = xform == Rhino.Geometry.Transform.Identity;
      var point = new Rhino.Geometry.Point(Value.Coord.ToRhino());
      point.Scale(Revit.ModelUnits);
      var bbox = IsIdentity ? point.GetBoundingBox(true) : point.GetBoundingBox(xform);
      return bbox;
    }
  }

  public class Edge : GH_GeometricGoo<Autodesk.Revit.DB.Edge>
  {
    public override string TypeName => "Revit Edge";
    public override string TypeDescription => "Represents a Revit Edge";

    public Edge() { }
    public Edge(Autodesk.Revit.DB.Edge edge) : base(edge) { }
    public Edge(Reference reference, Document doc) : base(reference, doc) { }

    public override bool CastTo<Q>(ref Q target)
    {
      if (Value != null)
      {
        if (typeof(Q).IsAssignableFrom(typeof(GH_Curve)))
        {
          var curve = Value.AsCurve().ToRhino();
          curve.Scale(Revit.ModelUnits);
          target = (Q) (object) new GH_Curve(curve);
          return true;
        }
      }

      return base.CastTo<Q>(ref target);
    }

    public override BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform)
    {
      if (Value == null)
        return BoundingBox.Empty;

      bool IsIdentity = xform == Rhino.Geometry.Transform.Identity;
      var curve = Value.AsCurve().ToRhino();
      curve.Scale(Revit.ModelUnits);
      var bbox = IsIdentity ? curve.GetBoundingBox(true) : curve.GetBoundingBox(xform);
      return bbox;
    }
  }
  public class Face : GH_GeometricGoo<Autodesk.Revit.DB.Face>
  {
    public override string TypeName => "Revit Face";
    public override string TypeDescription => "Represents a Revit Face";

    public Face() { }
    public Face(Autodesk.Revit.DB.Face face) : base(face) { }
    public Face(Reference reference, Document doc) : base(reference, doc) { }
    public override BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform)
    {
      if (Value == null)
        return BoundingBox.Empty;

      bool IsIdentity = xform == Rhino.Geometry.Transform.Identity;
      var bbox = BoundingBox.Empty;
      foreach(var loop in Value.EdgeLoops.OfType<Autodesk.Revit.DB.EdgeArray>())
      {
        foreach (var edge in loop.OfType<Autodesk.Revit.DB.Edge>())
        {
          var curve = edge.AsCurve().ToRhino();
          curve.Scale(Revit.ModelUnits);
          bbox.Union(IsIdentity ? curve.GetBoundingBox(true) : curve.GetBoundingBox(xform));
        }
      }

      return bbox;
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public interface IGH_PersistentGeometryParam
  {
    bool NeedsToBeExpired(Document doc, ICollection<ElementId> added, ICollection<ElementId> deleted, ICollection<ElementId> modified);
  }

  public abstract class GH_PersistentGeometryParam<X> :
  Grasshopper.Kernel.GH_PersistentGeometryParam<X>,
  IGH_PreviewObject,
  IGH_PersistentGeometryParam
  where X : class, Types.IGH_GeometricGoo
  {
    protected GH_PersistentGeometryParam(string name, string nickname, string description, string category, string subcategory) :
    base(new GH_InstanceDescription(name, nickname, description, category, subcategory)) { }

    #region UI methods
    struct Prompt
    {
      bool mainWindowVisible;
      bool mainWindowEnabled;

      public void PrepareForPrompt()
      {
        var mainWindowExtents = Revit.ActiveUIApplication.MainWindowExtents;
        var mainWindowRectangle = new System.Drawing.Rectangle(mainWindowExtents.Left, mainWindowExtents.Top, mainWindowExtents.Right - mainWindowExtents.Left, mainWindowExtents.Bottom - mainWindowExtents.Top);
        mainWindowRectangle.Inflate(-64, -64);

        // Grasshopper Window
        {
          Grasshopper.Instances.DocumentEditor.Enabled = false;
          if (Grasshopper.Instances.DocumentEditor.DesktopBounds.IntersectsWith(mainWindowRectangle))
            Grasshopper.Instances.DocumentEditor.Hide();
        }

        // Rhino Window
        {
          var rhinoWindowBounds = Rhino.UI.RhinoEtoApp.MainWindow.Bounds;
          var rhinoWindowRectangle = new System.Drawing.Rectangle(rhinoWindowBounds.Left, rhinoWindowBounds.Top, rhinoWindowBounds.Width, rhinoWindowBounds.Height);

          mainWindowEnabled = Rhino.UI.RhinoEtoApp.MainWindow.Enabled;
          mainWindowVisible = Rhino.UI.RhinoEtoApp.MainWindow.Visible;
          Rhino.UI.RhinoEtoApp.MainWindow.Enabled = false;
          if (rhinoWindowRectangle.IntersectsWith(mainWindowRectangle))
            Rhino.UI.RhinoEtoApp.MainWindow.Visible = false;
        }
      }

      public void RecoverFromPrompt()
      {
        // Rhino Window
        {
          Rhino.UI.RhinoEtoApp.MainWindow.Visible = mainWindowVisible;
          Rhino.UI.RhinoEtoApp.MainWindow.Enabled = mainWindowEnabled;
          mainWindowVisible = false;
          mainWindowEnabled = false;
        }

        // Grasshopper Window
        {
          Grasshopper.Instances.DocumentEditor.Show();
          Grasshopper.Instances.DocumentEditor.Enabled = true;
        }

        Revit.RefreshActiveView();
      }
    }
    Prompt prompt;
    protected override void PrepareForPrompt() => prompt.PrepareForPrompt();
    protected override void RecoverFromPrompt() => prompt.RecoverFromPrompt();

    public override void AppendAdditionalMenuItems(System.Windows.Forms.ToolStripDropDown menu)
    {
      base.AppendAdditionalMenuItems(menu);
      Menu_AppendSeparator(menu);
      Menu_AppendItem(menu, "Highlight elements", Menu_HighlightElements, !VolatileData.IsEmpty, false);
    }

    void Menu_HighlightElements(object sender, EventArgs e)
    {
      var elements = VolatileData.AllData(true).
                     OfType<Types.IGH_GeometricGoo>().
                     SkipWhile((x) => !x.IsReferencedGeometry).
                     Select((x) => x.Reference).
                     SkipWhile((x) => x == null).
                     Select((x) => x.ElementId).
                     ToArray();

      if (elements?.Length > 0)
      {
        Revit.ActiveUIDocument.Selection.SetElementIds(elements);
        Revit.ActiveUIDocument.ShowElements(elements);
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
    bool IGH_PersistentGeometryParam.NeedsToBeExpired(Document doc, ICollection<ElementId> added, ICollection<ElementId> deleted, ICollection<ElementId> modified)
    {
      foreach (var data in VolatileData.AllData(true).Cast<Types.IGH_GeometricGoo>())
      {
        if (!data.IsReferencedGeometry)
          continue;

        var reference = data.Reference;
        if (reference == null)
          continue;

        if (modified.Contains(reference.ElementId))
          return true;

        if (deleted.Contains(reference.ElementId))
          return true;
      }

      return false;
    }
    #endregion
  }

  public class Vertex : GH_PersistentGeometryParam<Types.Vertex>
  {
    public Vertex() : base("Vertex", "Vertex", "Represents a Revit vertex.", "Revit", "Geometry") { }
    public override Guid ComponentGuid => new Guid("BC1B160A-DC04-4139-AB7D-1AECBDE7FF88");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("V");

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
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.accept;
    }
    #endregion
  }

  public class Edge : GH_PersistentGeometryParam<Types.Edge>
  {
    public Edge() : base("Edge", "Edge", "Represents a Revit edge.", "Revit", "Geometry") { }
    public override Guid ComponentGuid => new Guid("B79FD0FD-63AE-4776-A0A7-6392A3A58B0D");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("E");

    #region UI methods
    protected override GH_GetterResult Prompt_Plural(ref List<Types.Edge> value)
    {
      try
      {
        var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Edge);
        if (references?.Count > 0)
        {
          value = references.Select((x) => new Types.Edge(x, Revit.ActiveDBDocument)).ToList();
          return GH_GetterResult.success;
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.accept;
    }
    protected override GH_GetterResult Prompt_Singular(ref Types.Edge value)
    {
      try
      {
        var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Edge);
        if (reference == null)
          return GH_GetterResult.accept;

        value = new Types.Edge(reference, Revit.ActiveDBDocument);
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.success;
    }
    #endregion
  }

  public class Face : GH_PersistentGeometryParam<Types.Face>
  {
    public Face() : base("Face", "Face", "Represents a Revit face.", "Revit", "Geometry") { }
    public override Guid ComponentGuid => new Guid("759700ED-BC79-4986-A6AB-84921A7C9293");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("F");

    #region UI methods
    protected override GH_GetterResult Prompt_Plural(ref List<Types.Face> value)
    {
      try
      {
        var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Face);
        if (references?.Count > 0)
        {
          value = references.Select((x) => new Types.Face(x, Revit.ActiveDBDocument)).ToList();
          return GH_GetterResult.success;
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.accept;
    }
    protected override GH_GetterResult Prompt_Singular(ref Types.Face value)
    {
      try
      {
        var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Face);
        if (reference == null)
          return GH_GetterResult.accept;

        value = new Types.Face(reference, Revit.ActiveDBDocument);
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.success;
    }
    #endregion
  }
}
