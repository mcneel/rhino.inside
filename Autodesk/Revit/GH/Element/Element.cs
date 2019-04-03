using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Windows.Forms;
using Control = System.Windows.Forms.Control;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using Grasshopper.Kernel.Attributes;
using Grasshopper.GUI.Canvas;
using Grasshopper.GUI;

using Autodesk.Revit.DB;
using System.ComponentModel;

namespace RhinoInside.Revit.GH.Types
{
  public class Element : ID, IGH_GeometricGoo, IGH_PreviewData, IGH_PreviewMeshData
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

      if (element is Autodesk.Revit.DB.ParameterElement parameterElement)
        return new ParameterElement(parameterElement);

      if (element is Autodesk.Revit.DB.ElementType elementType)
        return new ElementType(elementType);

      if (element is Autodesk.Revit.DB.SketchPlane sketchPlane)
        return new SketchPlane(sketchPlane);

      return new Element(element);
    }

    static public new Element Make(ElementId Id)    => Make(Revit.ActiveDBDocument.GetElement(Id));
    static public     Element Make(string uniqueId) => Make(Revit.ActiveDBDocument.GetElement(uniqueId));

    public Element() : base() { }
    protected Element(Autodesk.Revit.DB.Element element)     : base(element.Id, element.UniqueId) { }
    protected Element(Autodesk.Revit.DB.ElementId elementId) : base(elementId, Revit.ActiveDBDocument?.GetElement(elementId)?.UniqueId) { }

    public override bool CastFrom(object source)
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

    [TypeConverter(typeof(Proxy.ObjectConverter))]
    class Proxy : IGH_GooProxy
    {
      public Proxy(Element owner) { proxyOwner = owner; (this as IGH_GooProxy).UserString = FormatInstance(); }

      public void Construct() { }
      public string MutateString(string str) => str.Trim();
      public string FormatInstance() => element != null ? string.Format("{0}:{1}", proxyOwner.Value.IntegerValue, element.Name) : string.Empty;
      public bool FromString(string str)
      {
        int index = str.IndexOf(':');
        if(index >= 0)
          str = str.Substring(0, index);

        str = str.Trim();
        if (int.TryParse(str, out int elementId))
        {
          proxyOwner.Value = new ElementId(elementId);
          return true;
        }

        return false;
      }

      readonly Element proxyOwner;
      IGH_Goo IGH_GooProxy.ProxyOwner => proxyOwner;
      bool IGH_GooProxy.IsParsable => true;
      string IGH_GooProxy.UserString { get; set; }

      Autodesk.Revit.DB.Element element => proxyOwner.Value != null ? Revit.ActiveDBDocument?.GetElement(proxyOwner.Value) : null;

      public bool Valid => element != null;
      [System.ComponentModel.Description("The element identifier in this session.")]
      public int Id => proxyOwner.Value.IntegerValue;
      [System.ComponentModel.Description("A human readable name for the Element.")]
      public string Name => element?.Name;
      [System.ComponentModel.Description(".NET Object Type.")]
      public string Object => element?.GetType().FullName;
      [System.ComponentModel.Description("A stable unique identifier for an element within the document.")]
      public string UniqueID => element?.UniqueId;

      class ObjectConverter : ExpandableObjectConverter
      {
        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
          var properties = base.GetProperties(context, value, attributes);
          if (value is Proxy proxy)
          {
            var parameters = proxy.element?.Parameters;
            var parametersSize = parameters?.Size ?? 0;
            var propertiesCount = properties.Count;
            if (parametersSize > 0)
            {
              PropertyDescriptor[] descriptors = new PropertyDescriptor[propertiesCount + parametersSize];
              properties.CopyTo(descriptors, 0);

              foreach (var paramter in parameters.Cast<Autodesk.Revit.DB.Parameter>())
                descriptors[propertiesCount++] = new ParameterPropertyDescriptor(paramter);

              return new PropertyDescriptorCollection(descriptors, true);
            }
          }

          return properties;
        }
      }

      private class ParameterPropertyDescriptor : PropertyDescriptor
      {
        readonly Autodesk.Revit.DB.Parameter parameter;
        public ParameterPropertyDescriptor(Autodesk.Revit.DB.Parameter p) : base(p.Definition.Name, null) { parameter = p; }
        public override Type   ComponentType => typeof(Proxy);
        public override bool   IsReadOnly    => true;
        public override string Name          => parameter.Definition.Name;
        public override string Category      => LabelUtils.GetLabelFor(parameter.Definition.ParameterGroup);
        public override string Description
        {
          get
          {
            var description = string.Empty;
            try { description = parameter.StorageType == StorageType.ElementId ? "ElementId" : LabelUtils.GetLabelFor(parameter.Definition.ParameterType); }
            catch (Autodesk.Revit.Exceptions.InvalidOperationException)
            { description = parameter.Definition.UnitType == UnitType.UT_Number ? "Enumerate" : LabelUtils.GetLabelFor(parameter.Definition.UnitType); }

            return description;
          }
        }
        public override bool ShouldSerializeValue(object component) { return false; }
        public override void ResetValue(object component) { }
        public override bool CanResetValue(object component) { return false; }
        public override void SetValue(object component, object value) { }
        public override Type PropertyType   => typeof(string);
        public override object GetValue(object component) => parameter.Element != null ? (parameter.StorageType == StorageType.String ? parameter.AsString() : parameter.AsValueString()) : null;
      }
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public override string ToString()
    {
      if (IsValid)
      {
        var element = (Autodesk.Revit.DB.Element) this;
        if (element != null)
          return "Revit " + element.GetType().Name + " \"" + element.Name + "\"";
      }

      return base.ToString();
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
          var categoryMaterial = element.Category?.Material.ToRhino(null);
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

      Preview(Element element)
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
      set { if (geometryPreview != value) { ((IDisposable) geometryPreview)?.Dispose(); geometryPreview = value; } }
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

    #region IGH_GeometricGoo
    public Reference Reference { get { var element = (Autodesk.Revit.DB.Element) this; return element != null ? new Reference(element) : null; } }
    public bool LoadGeometry() => LoadGeometry(Revit.ActiveDBDocument);
    public bool LoadGeometry(Rhino.RhinoDoc doc) => LoadGeometry(Revit.ActiveDBDocument);
    public bool LoadGeometry(Document doc)
    {
      Value = ElementId.InvalidElementId;

      try { Value = Revit.ActiveDBDocument?.GetElement(UniqueID)?.Id ?? ElementId.InvalidElementId; }
      catch (ArgumentException) { }

      return IsValid;
    }
    public Grasshopper.Kernel.Types.IGH_GeometricGoo DuplicateGeometry() => (IGH_GeometricGoo) MemberwiseClone();
    public void ClearCaches()
    {
      if (IsReferencedGeometry)
        Value = null;
    }
    public Rhino.Geometry.BoundingBox Boundingbox => ClippingBox;
    public Rhino.Geometry.BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform) => ClippingBox;
    Grasshopper.Kernel.Types.IGH_GeometricGoo Grasshopper.Kernel.Types.IGH_GeometricGoo.Transform(Rhino.Geometry.Transform xform) => null;
    Grasshopper.Kernel.Types.IGH_GeometricGoo Grasshopper.Kernel.Types.IGH_GeometricGoo.Morph(Rhino.Geometry.SpaceMorph xmorph) => null;
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
              material.Diffuse = element.Category != null ? element.Category.LineColor.ToRhino() : System.Drawing.Color.White;
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
  public class Element : GH_PersistentGeometryParam<Types.Element>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("F3EA4A9C-B24F-4587-A358-6A7E6D8C028B");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("E");

    public Element() : base("Element", "Element", "Represents a Revit document element.", "Revit", "Element") { }

    protected override GH_GetterResult Prompt_Singular(ref Types.Element element)
    {
      element = null;

      try
      {
        var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Element);
        if (reference != null)
          element = Types.Element.Make(reference.ElementId);
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }

      return GH_GetterResult.success;
    }

    protected override GH_GetterResult Prompt_Plural(ref List<Types.Element> elements)
    {
      elements = null;

      var selection = Revit.ActiveUIDocument.Selection.GetElementIds();
      if (selection?.Count > 0)
      {
        elements = selection.Select((x) => Types.Element.Make(x)).ToList();
      }
      else
      {
        try
        {
          var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Element);
          if (references != null)
            elements = references.Select((x) => Types.Element.Make(x.ElementId)).ToList();
        }
        catch (Autodesk.Revit.Exceptions.OperationCanceledException) { return GH_GetterResult.cancel; }
      }
      return GH_GetterResult.success;
    }
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

  public class ElementIdentity : GH_Component
  {
    public override Guid ComponentGuid => new Guid("D3917D58-7183-4B3F-9D22-03F0FE93B956");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("ID");

    public ElementIdentity()
    : base("Element.Identity", "Element.Identity", "Query element identity information", "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to decompose", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", "Element name", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Element category", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.ElementType(), "Type", "T", "Element type", GH_ParamAccess.item);
      manager.AddTextParameter("UniqueID", "UUID", "Element UUID", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      DA.SetData("Name", element?.Name);
      DA.SetData("Category", element?.Category);
      DA.SetData("Type", Revit.ActiveDBDocument.GetElement(element?.GetTypeId()));
      DA.SetData("UniqueID", element?.UniqueId);
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

  public class ElementPreview : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("A95C7B73-6F70-46CA-85FC-A4402A3B6971");
    static readonly string PropertyName = "Preview";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("P");

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

  public class ElementParameters : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("44515A6B-84EE-4DBD-8241-17EDBE07C5B6");
    static readonly string PropertyName = "Parameters";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{}");

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
      manager.AddParameter(new Parameters.ParameterElement(), "Parameters", "P", "Element parameters", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      string parameterName = null;
      bool noFilterName = (!DA.GetData("Name", ref parameterName) && Params.Input[1].Sources.Count == 0);

      var builtInParameterGroup = BuiltInParameterGroup.INVALID;
      bool noFilterGroup = (!DA.GetData("Group", ref builtInParameterGroup) && Params.Input[2].Sources.Count == 0);

      bool readOnly = false;
      bool noFilterReadOnly = (!DA.GetData("ReadOnly", ref readOnly) && Params.Input[3].Sources.Count == 0);

      List<ElementId> paramIds = null;
      if (element != null)
      {
        paramIds = new List<ElementId>(element.Parameters.Size);
        foreach (var group in element.Parameters.OfType<Parameter>().GroupBy((x) => x.Definition.ParameterGroup).OrderBy((x) => x.Key))
        {
          foreach (var param in group.OrderBy(x => x.Id.IntegerValue))
          {
            if (!noFilterName && parameterName != param.Definition.Name)
              continue;

            if (!noFilterGroup && builtInParameterGroup != param.Definition.ParameterGroup)
              continue;

            if (!noFilterReadOnly && readOnly != param.IsReadOnly)
              continue;

            paramIds.Add(param.Id);
          }
        }
      }

      DA.SetDataList("Parameters", paramIds);
    }
  }

  public class ElementDecompose : GH_Component, IGH_VariableParameterComponent
  {
    public override Guid ComponentGuid => new Guid("FAD33C4B-A7C3-479B-B309-8F5363B25599");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{");
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
      if (param.Attributes == null)
        param.Attributes = new GH_LinkedParamAttributes(param, Attributes);

      param.Access = GH_ParamAccess.item;
      Params.RegisterOutputParam(param);
    }

    class EqualityComparer : IEqualityComparer<KeyValuePair<int, Parameter>>
    {
      bool IEqualityComparer<KeyValuePair<int, Parameter>>.Equals(KeyValuePair<int, Parameter> x, KeyValuePair<int, Parameter> y) => x.Key == y.Key;
      int IEqualityComparer<KeyValuePair<int, Parameter>>.GetHashCode(KeyValuePair<int, Parameter> obj) => obj.Key;
    }

    void Menu_PopulateOutputsWithCommonParameters(object sender, EventArgs e)
    {
      IEnumerable<KeyValuePair<int, Parameter>> common = null;

      foreach (var goo in Params.Input[0].VolatileData.AllData(true).OfType<Types.Element>())
      {
        var definitions = new Dictionary<int, Parameter>();

        var element = (Autodesk.Revit.DB.Element) goo;
        if (element == null)
          continue;

        foreach (var param in element.Parameters.OfType<Parameter>())
        {
          try { definitions.Add(param.Id.IntegerValue, param); }
          catch (System.ArgumentException) { }
        }

        if (common == null)
          common = definitions;
        else
          common = common.Intersect(definitions, new EqualityComparer());
      }

      if (common != null)
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
      var definitions = new Dictionary<int, Parameter>();

      foreach (var goo in Params.Input[0].VolatileData.AllData(true).OfType<Types.Element>())
      {
        var element = (Autodesk.Revit.DB.Element) goo;
        if (element == null)
          continue;

        foreach (var param in element.Parameters.OfType<Parameter>())
        {
          try { definitions.Add(param.Id.IntegerValue, param); }
          catch (System.ArgumentException) { }
        }
      }

      if (definitions != null)
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
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      for (int p = 0; p < Params.Output.Count; ++p)
      {
        if (Params.Output[p] is Parameters.ParameterParam instance)
        {
          var parameterId = instance.ParameterId;
          if (Enum.IsDefined(typeof(BuiltInParameter), parameterId))
          {
            DA.SetData(p, element.get_Parameter((BuiltInParameter) parameterId));
          }
          else if (Revit.ActiveDBDocument.GetElement(new ElementId(parameterId)) is ParameterElement parameterelement)
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
      var nTopic = new Grasshopper.GUI.HTML.GH_HtmlFormatter(this);
      nTopic.Title = Name;
      nTopic.Description =
      @"<p>This component is a special interface object that allows for quick accessing to Revit Element parameters.</p>" +
      @"<p>It's able to modify itself in order to show any parameter its input element parameter contains. " +
      @"It also allows to remove some output parameters if are not connected to anything else.</p>" +
      @"<p>Under the component contextual menu you would find these options:</p>" +
      @"<dl>" +
      @"<dt><b>Get common parameters</b></dt><dd>Populates the output parameters list with common parameters in all input elements</dd>" +
      @"<dt><b>Get all parameters</b></dt><dd>Populates the output parameters list with all parameters found in all input elements</dd>" +
      @"<dt><b>Remove unconnected parameters</b></dt><dd>Removes the output parameters that are not connected to anything else</dd>" +
      @"</dl>";
      nTopic.ContactURI = @"https://discourse.mcneel.com/c/serengeti/inside";
      nTopic.AddRemark("SHIFT + Double click runs \"Get common parameters\"");
      nTopic.AddRemark("CTRL + Double click runs \"Remove unconnected parameters\".");

      return nTopic.HtmlFormat();
    }
  }

  public class ElementParameterGet : GH_Component
  {
    public override Guid ComponentGuid => new Guid("D86050F2-C774-49B1-9973-FB3AB188DC94");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("GET");

    public ElementParameterGet()
    : base("Element.ParameterGet", "ParameterGet", "Gets the parameter value of a specified Revit Element", "Revit", "Element")
    {}

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to query", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.ParameterElement(), "Parameter", "P", "Element parameter to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Parameter(), "Value", "V", "Element parameter value", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      Types.ParameterElement parameter = null;
      if (!DA.GetData("Parameter", ref parameter))
        return;

      if (Enum.IsDefined(typeof(BuiltInParameter), parameter.Value.IntegerValue))
      {
        DA.SetData("Value", element.get_Parameter((BuiltInParameter) parameter.Value.IntegerValue));
      }
      else if (Revit.ActiveDBDocument.GetElement(parameter.Value) is ParameterElement parameterelement)
      {
        DA.SetData("Value", element.get_Parameter(parameterelement.GetDefinition()));
      }
    }
  }

  public class ElementParameterSet : GH_Component
  {
    public override Guid ComponentGuid => new Guid("8F1EE110-7FDA-49E0-BED4-E8E0227BC021");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("SET");

    public ElementParameterSet()
    : base("Element.ParameterSet", "ParameterSet", "Sets the parameter value of a specified Revit Element", "Revit", "Element")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Element to update", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.ParameterElement(), "Parameter", "P", "Element parameter to query", GH_ParamAccess.item);
      manager.AddGenericParameter("Value", "V", "Element parameter value", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "Updated Element", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      Types.ParameterElement parameterElement = null;
      if (!DA.GetData("Parameter", ref parameterElement))
        return;

      IGH_Goo goo = null;
      if (!DA.GetData("Value", ref goo))
        return;

      Autodesk.Revit.DB.Parameter parameter = null;
      if (Enum.IsDefined(typeof(BuiltInParameter), parameterElement.Value.IntegerValue))
      {
        parameter = element.get_Parameter((BuiltInParameter) parameterElement.Value.IntegerValue);
      }
      else if (Revit.ActiveDBDocument.GetElement(parameterElement.Value) is ParameterElement parameterelement)
      {
        parameter = element.get_Parameter(parameterelement.GetDefinition());
      }

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, element, parameter, goo));
    }

    double ToHost(double value, UnitType unit)
    {
      switch (unit)
      {
        case UnitType.UT_Length:  return value / Math.Pow(Revit.ModelUnits, 1.0);
        case UnitType.UT_Area:    return value / Math.Pow(Revit.ModelUnits, 2.0);
        case UnitType.UT_Volume:  return value / Math.Pow(Revit.ModelUnits, 3.0);
      }

      return value;
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Autodesk.Revit.DB.Element element,
      Autodesk.Revit.DB.Parameter parameter,
      IGH_Goo goo
    )
    {
      var value = goo.ScriptVariable();
      switch (parameter?.StorageType)
      {
        case StorageType.Integer:
          {
            switch(value)
            {
              case bool boolean:    parameter.Set(boolean ? 1 : 0); break;
              case int  integer:    parameter.Set(integer); break;
              case double real:     parameter.Set(Math.Round(ToHost(real, parameter.Definition.UnitType)).Clamp(int.MinValue, int.MaxValue)); break;
              case System.Drawing.Color color: parameter.Set(((int) color.R) | ((int) color.G << 8) | ((int) color.B << 16)); break;
              default: element = null; break;
            }
            break;
          }
        case StorageType.Double:
          {
            switch (value)
            {
              case int integer: parameter.Set((double) integer); break;
              case double real: parameter.Set(ToHost(real, parameter.Definition.UnitType)); break;
              default: element = null; break;
            }
            break;
          }
        case StorageType.String:
          {
            switch (value)
            {
              case string str: parameter.Set(str); break;
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

      if(element == null)
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Unable to cast 'Value' from {0} to {1}.", value.GetType().Name, parameter.StorageType.ToString()));

      DA.SetData(0, element, Iteration);

      if (Iteration == DA.Iteration)
      {
        // Notify Grasshopper continue evaluating the definition from this component
        if (RuntimeMessageLevel < GH_RuntimeMessageLevel.Error)
        {
          foreach (var recipient in Params.Output.SelectMany(x => x.Recipients))
            recipient.ExpireSolution(false);
        }
      }
    }
  }
}
