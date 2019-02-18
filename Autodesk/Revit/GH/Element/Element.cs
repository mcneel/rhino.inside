using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

using RhinoInside.Revit;
using Autodesk.Revit.DB;
using System.Windows.Forms;

namespace RhinoInside.Revit.GH.Types
{
  public class Element : ID, IGH_PreviewData, IGH_PreviewMeshData
  {
    public override string TypeName => "Revit Element";
    public override string TypeDescription => "Represents a Revit element";
    override public object ScriptVariable() => (Autodesk.Revit.DB.Element) this;
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Element);
    public static explicit operator Autodesk.Revit.DB.Element(Element self) => Revit.ActiveDBDocument?.GetElement(self);

    static public Element Make(Autodesk.Revit.DB.Element element)
    {
      if (element == null)
        return null;

      if (element is Autodesk.Revit.DB.ElementType elementType)
        return new ElementType(elementType);

      if (element is Autodesk.Revit.DB.SketchPlane sketchPlane)
        return new SketchPlane(sketchPlane);

      return new Element(element);
    }

    static public Element Make(ElementId Id) => Make(Revit.ActiveDBDocument.GetElement(Id));
    static public Element Make(string uniqueId) => Make(Revit.ActiveDBDocument.GetElement(uniqueId));

    public Element() : base() { }
    protected Element(Autodesk.Revit.DB.Element element) : base(element.Id, element.UniqueId) { }

    public override sealed bool CastFrom(object source)
    {
      Autodesk.Revit.DB.Element element = null;
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      switch (source)
      {
        case Autodesk.Revit.DB.Element e:    element = e; break;
        case Autodesk.Revit.DB.ElementId id: element = Revit.ActiveDBDocument.GetElement(id); break;
        case int integer:                    element = Revit.ActiveDBDocument.GetElement(new ElementId(integer)); break;
        case string uniqueId:                element = Revit.ActiveDBDocument.GetElement(uniqueId); break;
      }
      if (ScriptVariableType.IsInstanceOfType(element))
      {
        Value = element.Id;
        UniqueID = element.UniqueId;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      var element = (Autodesk.Revit.DB.Element) this;
      if (element == null)
        return false;

      if (typeof(Q).IsSubclassOf(ScriptVariableType))
      {
        target = (Q) (object) element;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(ScriptVariableType))
      {
        target = (Q) (object) element;
        return true;
      }

      if (element.Category?.HasMaterialQuantities ?? false)
      {
        if (typeof(Q).IsAssignableFrom(typeof(GH_Mesh)))
        {
          var options = new Options { ComputeReferences = true };
          using (var geometry = element.get_Geometry(options))
          {
            if (geometry != null)
            {
              var mesh = new Rhino.Geometry.Mesh();
              mesh.Append(geometry.GetPreviewMeshes().Where(x => x != null));
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
        if (axis == null)
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

        target = (Q) (object) new GH_Transform(Rhino.Geometry.Transform.ChangeBasis(Rhino.Geometry.Plane.WorldXY, plane));
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

      return base.CastTo<Q>(ref target);
    }

    #region Preview
    public static void BuildPreview
    (
      Autodesk.Revit.DB.Element element, Rhino.Geometry.MeshingParameters meshingParameters, ViewDetailLevel DetailLevel,
      out Rhino.Display.DisplayMaterial[] materials, out Rhino.Geometry.Mesh[] meshes, out Rhino.Geometry.Curve[] wires
    )
    {
      var options = new Options { ComputeReferences = true, DetailLevel = DetailLevel };
      using (var geometry = element?.get_Geometry(options))
      {
        if (geometry == null)
        {
          materials = null;
          meshes = null;
          wires = null;
        }
        else
        {
          var categoryMaterial = element.Category.Material.ToRhino(null);
          var elementMaterial = geometry.MaterialElement.ToRhino(categoryMaterial);

          using (var ga = Convert.GraphicAttributes.Push())
          {
            ga.MeshingParameters = meshingParameters;

            meshes = geometry.GetPreviewMeshes().Where(x => x != null).ToArray();
            wires = geometry.GetPreviewWires().Where(x => x != null).ToArray();
            materials = geometry.GetPreviewMaterials(elementMaterial).Where(x => x != null).ToArray();

            foreach (var mesh in meshes)
              mesh.Normals.ComputeNormals();
          }
        }
      }
    }

    class Preview : IDisposable
    {
      readonly ElementId elementId;
      readonly Rhino.Geometry.BoundingBox clippingBox;
      public readonly Rhino.Geometry.MeshingParameters MeshingParameters = Convert.GraphicAttributes.Peek.MeshingParameters;
      public Rhino.Display.DisplayMaterial[] materials;
      public Rhino.Geometry.Mesh[] meshes;
      public Rhino.Geometry.Curve[] wires;

      static List<Preview> previewsQueue;

      void Build(Document document)
      {
        if ((meshes == null && wires == null && materials == null))
        {
          var element = document.GetElement(elementId);
          if (element == null)
            return;

          BuildPreview(element, MeshingParameters, ViewDetailLevel.Undefined, out materials, out meshes, out wires);
        }
      }

      static void BuildPreviews(Document document, bool cancelled)
      {
        var previews = previewsQueue;
        previewsQueue = null;

        if (cancelled)
          return;

        // Sort in reverse order depending on how 'big' is the element on screen.
        // The bigger the more at the end on the list.
        previews.Sort((x, y) => (x.clippingBox.Diagonal.Length < y.clippingBox.Diagonal.Length) ? -1 : +1);
        BuildPreviews(document, cancelled, previews);
      }

      static void BuildPreviews(Document document, bool cancelled, List<Preview> previews)
      {
        if (cancelled)
          return;

        var stopWatch = new Stopwatch();

        int count = 0;
        while ((count = previews.Count) > 0)
        {
          // Draw the biggest elements first.
          // The biggest element ia at the end of previews List, this way no realloc occurs when removing it

          int last = count - 1;
          var preview = previews[last];
          previews.RemoveAt(last);

          stopWatch.Start();
          preview.Build(document);
          stopWatch.Stop();

          // If building those previews take use more than 200 ms we return to Revit, to keep it 'interactive'.
          if (stopWatch.ElapsedMilliseconds > 200)
            break;
        }

        // RhinoDoc.ActiveDoc.Views.Redraw is synchronous :(
        // better use RhinoView.Redraw that just invalidate the view, the OS will update it when possible
        foreach (var view in Rhino.RhinoDoc.ActiveDoc.Views)
          view.Redraw();

        // If there are pending previews to generate enqueue BuildPreviews again
        if (previews.Count > 0)
          Revit.EnqueueReadAction((doc, cancel) => BuildPreviews(doc, cancel, previews));
      }

      public Preview(Element element)
      {
        elementId = element;
        clippingBox = element.ClippingBox;
      }

      public static Preview OrderNew(Element element)
      {
        if (!element.IsValid)
          return null;

        if (previewsQueue == null)
        {
          previewsQueue = new List<Preview>();
          Revit.EnqueueReadAction((doc, cancel) => BuildPreviews(doc, cancel));
        }

        var preview = new Preview(element);
        previewsQueue.Add(preview);
        return preview;
      }

      void IDisposable.Dispose()
      {
        foreach (var mesh in meshes ?? Enumerable.Empty<Rhino.Geometry.Mesh>())
          mesh.Dispose();
        meshes = null;

        foreach (var wire in wires ?? Enumerable.Empty<Rhino.Geometry.Curve>())
          wire.Dispose();
        wires = null;
      }
    }

    Preview geometryPreview;
    Preview GeometryPreview
    {
      get { return geometryPreview ?? (geometryPreview = Preview.OrderNew(this)); }
      set { if (geometryPreview != value) { ((IDisposable)geometryPreview)?.Dispose(); geometryPreview = value; } }
    }

    public Rhino.Display.DisplayMaterial[] TryGetPreviewMaterials()
    {
      return GeometryPreview.materials;
    }

    public Rhino.Geometry.Mesh[] TryGetPreviewMeshes()
    {
      if (geometryPreview != null)
      {
        var newMeshingParameters = Convert.GraphicAttributes.Peek.MeshingParameters;
        if (newMeshingParameters != null)
        {
          var currentMeshingParameters = geometryPreview.MeshingParameters;
          if (currentMeshingParameters != newMeshingParameters)
          {
            if (currentMeshingParameters == null || currentMeshingParameters.RelativeTolerance != newMeshingParameters.RelativeTolerance)
              GeometryPreview = null;
          }
        }
      }

      return GeometryPreview.meshes;
    }

    public Rhino.Geometry.Curve[] TryGetPreviewWires()
    {
      return GeometryPreview.wires;
    }
    #endregion

    #region IGH_PreviewData
    Rhino.Geometry.BoundingBox clippingBox = Rhino.Geometry.BoundingBox.Empty;
    public Rhino.Geometry.BoundingBox ClippingBox
    {
      get
      {
        if (!clippingBox.IsValid)
        {
          var element = (Autodesk.Revit.DB.Element) this;
          if (element != null)
            clippingBox = element.get_BoundingBox(null).ToRhino().Scale(Revit.ModelUnits);
        }

        return clippingBox;
      }
    }

    void IGH_PreviewData.DrawViewportMeshes(GH_PreviewMeshArgs args)
    {
      if (!IsValid)
        return;

      using (var ga = Convert.GraphicAttributes.Push())
      {
        ga.MeshingParameters = args.MeshingParameters;

        var meshes = TryGetPreviewMeshes();
        if (meshes == null)
          return;

        var material = args.Material;
        var element = Revit.ActiveDBDocument?.GetElement(this);
        if (element == null)
        {
          const int factor = 3;

          // Erased element
          material = new Rhino.Display.DisplayMaterial(material);
          material.Diffuse = System.Drawing.Color.FromArgb(20, 20, 20);
          material.Emission = System.Drawing.Color.FromArgb(material.Emission.R / factor, material.Emission.G / factor, material.Emission.B / factor);
          material.Shine = 0.0;
        }
        else if (!element.Pinned)
        {
          if (args.Pipeline.DisplayPipelineAttributes.ShadingEnabled)
          {
            // Unpinned element
            if (args.Pipeline.DisplayPipelineAttributes.UseAssignedObjectMaterial)
            {
              var materials = TryGetPreviewMaterials();

              for (int m = 0; m < meshes.Length; ++m)
                args.Pipeline.DrawMeshShaded(meshes[m], materials[m]);

              return;
            }
            else
            {
              material = new Rhino.Display.DisplayMaterial(material);
              material.Diffuse = element.Category.LineColor.ToRhino();
              if (material.Diffuse == System.Drawing.Color.Black)
                material.Diffuse = System.Drawing.Color.White;
              material.Transparency = 0.0;
            }
          }
        }

        foreach (var mesh in meshes)
          args.Pipeline.DrawMeshShaded(mesh, material);
      }
    }

    void IGH_PreviewData.DrawViewportWires(GH_PreviewWireArgs args)
    {
      if (!IsValid)
        return;

      if (!args.Pipeline.DisplayPipelineAttributes.ShowSurfaceEdges)
        return;

      int thickness = 1; //args.Thickness;
      const int factor = 3;

      var color = args.Color;
      var element = Revit.ActiveDBDocument?.GetElement(this);
      if (element == null)
      {
        // Erased element
        color = System.Drawing.Color.FromArgb(args.Color.R / factor, args.Color.G / factor, args.Color.B / factor);
      }
      else if (!element.Pinned)
      {
        // Unpinned element
        if (args.Thickness <= 1 && args.Pipeline.DisplayPipelineAttributes.UseAssignedObjectMaterial)
          color = System.Drawing.Color.Black;
      }

      var wires = TryGetPreviewWires();
      if (wires != null && wires.Length > 0)
      {
        foreach (var wire in wires)
          args.Pipeline.DrawCurve(wire, color, thickness);
      }
      else
      {
        var meshes = TryGetPreviewMeshes();
        if (meshes != null)
        {
          // Grasshopper does not show mesh wires.
          //foreach (var mesh in meshes)
          //  args.Pipeline.DrawMeshWires(mesh, color, thickness);
        }
        else
        {
          foreach (var edge in ClippingBox.GetEdges() ?? Enumerable.Empty<Rhino.Geometry.Line>())
            args.Pipeline.DrawPatternedLine(edge.From, edge.To, System.Drawing.Color.Black /*color*/, 0x00001111, thickness);
        }
      }
    }
    #endregion

    #region IGH_PreviewMeshData
    void IGH_PreviewMeshData.DestroyPreviewMeshes()
    {
      GeometryPreview = null;
      clippingBox = Rhino.Geometry.BoundingBox.Empty;
    }

    Rhino.Geometry.Mesh[] IGH_PreviewMeshData.GetPreviewMeshes()
    {
      return TryGetPreviewMeshes();
    }
    #endregion

    #region Location
    public Rhino.Geometry.Box Box
    {
      get
      {
        var b = Rhino.Geometry.Box.Empty;

        var element = (Autodesk.Revit.DB.Element) this;
        if (element != null)
        {
          var bbox = element.get_BoundingBox(null);
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

        var element = (Autodesk.Revit.DB.Element) this;
        if (element != null)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            p = instance.GetTransform().Origin.ToRhino();
          else switch (element.Location)
          {
            case Autodesk.Revit.DB.LocationPoint pointLocation: p = pointLocation.Point.ToRhino(); break;
            case Autodesk.Revit.DB.LocationCurve curveLocation: p = curveLocation.Curve.GetEndPoint(0).ToRhino(); break;
            default:
                var bbox = element.get_BoundingBox(null);
                if(bbox != null)
                  p = bbox.Min.ToRhino(); break;
          }

          if (p.IsValid)
          {
            var scaleFactor = Revit.ModelUnits;
            if (scaleFactor != 1.0)
              p = p.Scale(scaleFactor);

            return p;
          }
        }

        return p;
      }
    }

    public virtual Rhino.Geometry.Vector3d XAxis
    {
      get
      {
        var x = Rhino.Geometry.Vector3d.Zero;

        var element = (Autodesk.Revit.DB.Element) this;
        if (element != null)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            x = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisX.ToRhino();
          else if (element.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            x = c.TangentAt(c.Domain.Min);
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

        var element = (Autodesk.Revit.DB.Element) this;
        if (element != null)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            y = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisY.ToRhino();
          else if (element.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            y = c.CurvatureAt(c.Domain.Min);
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
        var v = Rhino.Geometry.Vector3d.Zero;

        var element = (Autodesk.Revit.DB.Element) this;
        if (element != null)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            v = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisZ.ToRhino();
          else if (element.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            v = Rhino.Geometry.Vector3d.CrossProduct(c.TangentAt(c.Domain.Min), c.CurvatureAt(c.Domain.Min));
          }

          if (v.IsZero || !v.Unitize())
            v = Rhino.Geometry.Vector3d.CrossProduct(XAxis, YAxis);

          if (v.IsZero || !v.Unitize())
            v = Rhino.Geometry.Vector3d.ZAxis;
        }

        return v;
      }
    }

    public virtual Rhino.Geometry.Plane Plane => new Rhino.Geometry.Plane(Location, XAxis, YAxis);

    public Rhino.Geometry.Curve Axis
    {
      get
      {
        var element = (Autodesk.Revit.DB.Element) this;
        Rhino.Geometry.Curve c = null;

        if(element?.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          c = curveLocation.Curve.ToRhino();

        if (c != null)
        {
          var scaleFactor = Revit.ModelUnits;
          if (scaleFactor != 1.0)
            c.Scale(scaleFactor);
        }

        return c;
      }
    }
    #endregion
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Element : GH_Param<Types.Element> /*GH_PersistentParam<Types.Element>*/, IGH_PreviewObject
  {
    public override Guid ComponentGuid => new Guid("F3EA4A9C-B24F-4587-A358-6A7E6D8C028B");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("E");

    public Element() : base("Element", "Element", "Represents a Revit document element.", "Revit", "Element", GH_ParamAccess.item) { }

    #region UI methods
    bool mainWindowVisible = false;
    protected /*override*/ void PrepareForPrompt()
    {
      Grasshopper.Instances.DocumentEditor.FadeOut();
      mainWindowVisible = Rhino.UI.RhinoEtoApp.MainWindow.Visible;
      Rhino.UI.RhinoEtoApp.MainWindow.Visible = false;
    }

    protected /*override*/ void RecoverFromPrompt()
    {
      Rhino.UI.RhinoEtoApp.MainWindow.Visible = mainWindowVisible;
      mainWindowVisible = false;
      Grasshopper.Instances.DocumentEditor.FadeIn();
    }

    protected /*override*/ GH_GetterResult Prompt_Singular(out Types.Element element)
    {
      element = null;

      try
      {
        var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Element);
        if (reference != null)
          element = Types.Element.Make(reference.ElementId);
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException)
      {
        return GH_GetterResult.cancel;
      }

      return GH_GetterResult.success;
    }

    protected /*override*/ GH_GetterResult Prompt_Plural(out List<Types.Element> elements)
    {
      elements = null;

      var selection = Revit.ActiveUIDocument.Selection.GetElementIds();
      if (selection?.Count > 0)
      {
        elements = new List<Types.Element>();
        foreach (var elementId in selection)
          elements.Add(Types.Element.Make(elementId));
      }
      else
      {
        try
        {
          var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Element);
          if (references?.Count > 0)
          {
            elements = new List<Types.Element>();
            foreach (var reference in references)
              elements.Add(Types.Element.Make(reference.ElementId));
          }
        }
        catch (Autodesk.Revit.Exceptions.OperationCanceledException)
        {
          return GH_GetterResult.cancel;
        }
      }
      return GH_GetterResult.success;
    }

    private void Menu_PromptSingular(object sender, EventArgs e)
    {
      try
      {
        PrepareForPrompt();

        if (Prompt_Singular(out var element) == GH_GetterResult.success)
          selection = new List<Types.Element>() { element };
      }
      finally
      {
        RecoverFromPrompt();
      }

      ExpireSolution(true);
    }

    private void Menu_PromptPlural(object sender, EventArgs e)
    {
      try
      {
        PrepareForPrompt();

        if (Prompt_Plural(out var elements) == GH_GetterResult.success)
          selection = elements;
      }
      finally
      {
        RecoverFromPrompt();
      }
      ExpireSolution(true);
    }

    private void Menu_ClearValues(object sender, EventArgs e)
    {
      selection = null;
      ExpireSolution(true);
    }

    public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
    {
      base.AppendAdditionalMenuItems(menu);
      if (Kind == GH_ParamKind.output)
        return;

      Menu_AppendItem(menu, string.Format("Set one {0}", TypeName), Menu_PromptSingular, SourceCount == 0, false);
      Menu_AppendItem(menu, string.Format("Set Multiple {0}", TypeName), Menu_PromptPlural, SourceCount == 0, false);
      Menu_AppendSeparator(menu);
      Menu_AppendItem(menu, "Clear values", Menu_ClearValues, SourceCount == 0, false);
      Menu_AppendSeparator(menu);
    }

    List<Types.Element> selection;
    protected sealed override void CollectVolatileData_Custom()
    {
      if (selection != null && selection.Count > 0)
      {
        ClearData();

        var volatileList = new List<IGH_Goo>(selection.Count);
        foreach (var element in selection)
          volatileList.Add(element.Duplicate());

        AddVolatileDataList(new Grasshopper.Kernel.Data.GH_Path(0), volatileList);
      }
    }
    #endregion

    #region IGH_PreviewObject
    public bool Hidden { get; set; }
    public bool IsPreviewCapable => !VolatileData.IsEmpty;
    public Rhino.Geometry.BoundingBox ClippingBox => Preview_ComputeClippingBox();
    public void DrawViewportMeshes(IGH_PreviewArgs args) { Preview_DrawMeshes(args); }
    public void DrawViewportWires(IGH_PreviewArgs args)  { Preview_DrawWires(args);  }
    #endregion
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public abstract class ElementGetter : GH_Component
  {
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected static readonly Type ObjectType = typeof(Types.Element);
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon(ObjectType.Name.Substring(0, 1));

    protected ElementGetter(string propertyName)
      : base(ObjectType.Name + "." + propertyName, propertyName, "Get the " + propertyName + " of the specified " + ObjectType.Name, "Revit", ObjectType.Name)
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), ObjectType.Name, ObjectType.Name.Substring(0, 1), ObjectType.Name + " to query", GH_ParamAccess.item);
    }
  }

  public class ElementDecompose : GH_Component
  {
    public override Guid ComponentGuid => new Guid("D3917D58-7183-4B3F-9D22-03F0FE93B956");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("E{");

    public ElementDecompose()
    : base("Element.Decompose", "Element.Decompose", "Decompose an elemenet", "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to decompose", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", "Element name", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Element category", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.ElementType(), "Type", "C", "Element type", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      DA.SetData("Name", element?.Name);
      DA.SetData("Category", element?.Category);
      DA.SetData("Type", Revit.ActiveDBDocument.GetElement(element?.GetTypeId()));
    }
  }

  public class ElementParameters : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("44515A6B-84EE-4DBD-8241-17EDBE07C5B6");
    static readonly string PropertyName = "Parameters";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{");

    public ElementParameters() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Names", "N", ObjectType.Name + " parameter names", GH_ParamAccess.list);
      manager.AddTextParameter("Values", "V", ObjectType.Name + " parameter values", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      if (element == null)
      {
        DA.SetDataList("Names", null);
        DA.SetDataList("Values", null);
        return;
      }

      var paramNames = new List<string>(element.Parameters.Size);
      var paramValues = new List<string>(element.Parameters.Size);

      foreach (var param in element.Parameters.OfType<Parameter>())
      {
        paramNames.Add(param.Definition.Name);
        paramValues.Add(param.AsValueString());
      }

      DA.SetDataList("Names", paramNames);
      DA.SetDataList("Values", paramValues);
    }
  }

  public class ElementGeometry : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("B7E6A82F-684F-4045-A634-A4AA9F7427A8");
    static readonly string PropertyName = "Geometry";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("G");

    public ElementGeometry() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddGeometryParameter(PropertyName, PropertyName.Substring(0, 1), ObjectType.Name + " parameter names", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      var options = new Options { ComputeReferences = true };

      using (var geometry = element?.get_Geometry(options))
      {
        var list = geometry?.ToRhino().Where(x => x != null).ToList();
        DA.SetDataList(PropertyName, list);
      }
    }
  }

  public class ElementGetPreview : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("A95C7B73-6F70-46CA-85FC-A4402A3B6971");
    static readonly string PropertyName = "Preview";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("P");

    public ElementGetPreview() : base(PropertyName) { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      base.RegisterInputParams(manager);
      manager[manager.AddIntegerParameter("DetailLevel", "LOD", ObjectType.Name + " LOD [1, 3]", GH_ParamAccess.item)].Optional = true;
      manager[manager.AddNumberParameter("Quality", "Q", ObjectType.Name + " meshes quality [0.0, 1.0]", GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddMeshParameter("Geometry", "G", ObjectType.Name + " meshes", GH_ParamAccess.list);
      manager.AddParameter(new Grasshopper.Kernel.Parameters.Param_OGLShader(), "Materials", "M", ObjectType.Name + " materials", GH_ParamAccess.list);
      manager.AddCurveParameter("Wires", "W", ObjectType.Name + " wires", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Types.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      var detailLevel = ViewDetailLevel.Undefined;
      int detailLevelValue = (int) detailLevel;
      if (DA.GetData(1, ref detailLevelValue))
      {
        if ((int) ViewDetailLevel.Coarse > detailLevelValue || detailLevelValue > (int) ViewDetailLevel.Fine)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Parameter '{0}' range is [1, 3].", Params.Input[1].Name));
          return;
        }

        detailLevel = (ViewDetailLevel) detailLevelValue;
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
      Types.Element.BuildPreview((Autodesk.Revit.DB.Element) element, meshingParameters, detailLevel, out var materials, out var meshes, out var wires);

      DA.SetDataList(0, meshes?.Select((x) => new GH_Mesh(x)));
      DA.SetDataList(1, materials?.Select((x) => new GH_Material(x)));
      DA.SetDataList(2, wires?.Select((x) => new GH_Curve(x)));
    }
  }
}
