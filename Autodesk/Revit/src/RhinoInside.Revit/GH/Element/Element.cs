using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Windows.Forms;
using Autodesk.Revit.DB;
using Grasshopper.GUI;
using Grasshopper.GUI.Canvas;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Attributes;
using Grasshopper.Kernel.Types;
using Control = System.Windows.Forms.Control;

namespace RhinoInside.Revit.GH.Types
{
  public class Element :
    ID,
    IGH_GeometricGoo,
    IGH_PreviewData,
    IGH_PreviewMeshData
  {
    public override string TypeName => "Revit Element";
    public override string TypeDescription => "Represents a Revit element";
    override public object ScriptVariable() => (Autodesk.Revit.DB.Element) this;
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Element);
    public static explicit operator Autodesk.Revit.DB.Element(Element self) => self.IsValid ? Revit.ActiveDBDocument?.GetElement(self) : null;

    public static Element Make(Autodesk.Revit.DB.Element element)
    {
      if (element is null)
        return null;

      if (element is Autodesk.Revit.DB.ParameterElement parameterElement)
        return new ParameterKey(parameterElement);

      if (element is Autodesk.Revit.DB.Material material)
        return new Material(material);

      if (element is Autodesk.Revit.DB.SketchPlane sketchPlane)
        return new SketchPlane(sketchPlane);

      if (element is Autodesk.Revit.DB.HostObject host)
        return new HostObject(host);

      if (element is Autodesk.Revit.DB.Level level)
        return new Level(level);

      if (element is Autodesk.Revit.DB.ElementType elementType)
        return new ElementType(elementType);

      return new Element(element);
    }

    public static new Element Make(ElementId Id)    => Make(Revit.ActiveDBDocument.GetElement(Id));
    public static     Element Make(string uniqueId) => Make(Revit.ActiveDBDocument.GetElement(uniqueId));

    public Element() : base() { }
    protected Element(Autodesk.Revit.DB.Element element)     : base(element.Id, element.UniqueId) { }
    protected Element(Autodesk.Revit.DB.ElementId elementId) : base(elementId) { }

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
        SetValue(element);
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (base.CastTo<Q>(ref target))
        return true;

      var element = (Autodesk.Revit.DB.Element) this;
      if (!(element is null))
      {
        if (typeof(Q).IsAssignableFrom(element.GetType()))
        {
          target = (Q) (object) element;
          return true;
        }

        if (element.Category?.HasMaterialQuantities ?? false)
        {
          if (typeof(Q).IsAssignableFrom(typeof(GH_Mesh)))
          {
            Options options = null;
            using (var geometry = element.GetGeometry(ViewDetailLevel.Fine, out options)) using (options)
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
      }

      return false;
    }

    [TypeConverter(typeof(Proxy.ObjectConverter))]
    class Proxy : IGH_GooProxy
    {
      public Proxy(Element owner) { proxyOwner = owner; (this as IGH_GooProxy).UserString = FormatInstance(); }

      public void Construct() { }
      public string MutateString(string str) => str.Trim();
      public string FormatInstance() => element is object ? string.Format("{0}:{1}", proxyOwner.Value.IntegerValue, element.Name) : string.Empty;
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

      Autodesk.Revit.DB.Element element => proxyOwner.Value is null ? null : Revit.ActiveDBDocument?.GetElement(proxyOwner.Value);

      public bool Valid => proxyOwner.IsValid;
      [System.ComponentModel.Description("The element identifier in this session.")]
      public int Id => proxyOwner.Value?.IntegerValue ?? -1;
      [System.ComponentModel.Description("A stable unique identifier for an element within the document.")]
      public string UniqueID => proxyOwner.UniqueID;
      [System.ComponentModel.Description("A human readable name for the Element.")]
      public string Name => element?.Name;
      [System.ComponentModel.Description(".NET Object Type.")]
      public string Object => element?.GetType().FullName;

      class ObjectConverter : ExpandableObjectConverter
      {
        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
          var properties = base.GetProperties(context, value, attributes);
          if (value is Proxy proxy)
          {
            var element = proxy.element;
            if (element is object)
            {
              var builtInParameters = element.GetParameters(Extension.ParameterSource.Any).
                Select(p => new ParameterPropertyDescriptor(p)).
                ToArray();

              var descriptors = new PropertyDescriptor[properties.Count + builtInParameters.Length];
              properties.CopyTo(descriptors, 0);
              builtInParameters.CopyTo(descriptors, properties.Count);

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

            if (parameter.IsReadOnly)
              description = "Read only " + description;

            description += "\nParameterId : " + parameter.Id.IntegerValue.ToParameterIdString();
            return description;
          }
        }
        public override bool Equals(object obj)
        {
          if (obj is ParameterPropertyDescriptor other)
            return other.parameter.Id == parameter.Id;

          return false;
        }
        public override int GetHashCode() => parameter.Id.IntegerValue;
        public override bool ShouldSerializeValue(object component) { return false; }
        public override void ResetValue(object component) { }
        public override bool CanResetValue(object component) { return false; }
        public override void SetValue(object component, object value) { }
        public override Type PropertyType   => typeof(string);
        public override object GetValue(object component) => parameter.Element is object ? (parameter.StorageType == StorageType.String ? parameter.AsString() : parameter.AsValueString()) : null;
      }
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public override string ToString()
    {
      if (IsValid)
      {
        var element = (Autodesk.Revit.DB.Element) this;
        if (element is object)
        {
          var ToolTip = string.Empty;
          if(element.Category is object)
            ToolTip += $"{element.Category.Name} : ";

          if (element.Document.GetElement(element.GetTypeId()) is Autodesk.Revit.DB.ElementType elementType)
          {
            if(!string.IsNullOrEmpty(elementType.FamilyName))
              ToolTip += $"{elementType.FamilyName} : ";

            ToolTip += $"{elementType.Name} : ";
          }
          else if (!string.IsNullOrEmpty(element.Name))
          {
            ToolTip += $"{element.Name} : ";
          }

          return $"{ToolTip}id {element.Id}";
        }
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
      Options options = null;
      using (var geometry = element?.GetGeometry(DetailLevel == ViewDetailLevel.Undefined ? ViewDetailLevel.Medium : DetailLevel, out options)) using (options)
      {
        if (geometry is null)
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

            meshes = geometry.GetPreviewMeshes().Where(x => x is object).ToArray();
            wires = geometry.GetPreviewWires().Where(x => x is object).ToArray();
            materials = geometry.GetPreviewMaterials(elementMaterial).Where(x => x is object).ToArray();

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
        if ((meshes is null && wires is null && materials is null))
        {
          var element = document.GetElement(elementId);
          if (element is null)
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

        if (previewsQueue is null)
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
      if (geometryPreview is object)
      {
        var newMeshingParameters = Convert.GraphicAttributes.Peek.MeshingParameters;
        if (newMeshingParameters is object)
        {
          var currentMeshingParameters = geometryPreview.MeshingParameters;
          if (currentMeshingParameters != newMeshingParameters)
          {
            if (currentMeshingParameters is null || currentMeshingParameters.RelativeTolerance != newMeshingParameters.RelativeTolerance)
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
    public Rhino.Geometry.BoundingBox Boundingbox => ClippingBox;
    Guid IGH_GeometricGoo.ReferenceID
    {
      get => Guid.Empty;
      set { if (value != Guid.Empty) throw new InvalidOperationException(); }
    }
    bool IGH_GeometricGoo.IsReferencedGeometry => IsReferencedElement;
    bool IGH_GeometricGoo.IsGeometryLoaded => IsElementLoaded;

    void IGH_GeometricGoo.ClearCaches() => UnloadElement();
    IGH_GeometricGoo IGH_GeometricGoo.DuplicateGeometry() => (IGH_GeometricGoo) MemberwiseClone();
    public Rhino.Geometry.BoundingBox GetBoundingBox(Rhino.Geometry.Transform xform) => ClippingBox;
    bool IGH_GeometricGoo.LoadGeometry(                  ) => IsElementLoaded || LoadElement(Revit.ActiveDBDocument);
    bool IGH_GeometricGoo.LoadGeometry(Rhino.RhinoDoc doc) => IsElementLoaded || LoadElement(Revit.ActiveDBDocument);
    IGH_GeometricGoo IGH_GeometricGoo.Transform(Rhino.Geometry.Transform xform) => null;
    IGH_GeometricGoo IGH_GeometricGoo.Morph(Rhino.Geometry.SpaceMorph xmorph) => null;
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
          if (element is object)
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
        if (meshes is null)
          return;

        var material = args.Material;
        var element = Revit.ActiveDBDocument?.GetElement(this);
        if (element is null)
        {
          const int factor = 3;

          // Erased element
          material = new Rhino.Display.DisplayMaterial(material)
          {
            Diffuse = System.Drawing.Color.FromArgb(20, 20, 20),
            Emission = System.Drawing.Color.FromArgb(material.Emission.R / factor, material.Emission.G / factor, material.Emission.B / factor),
            Shine = 0.0,
          };
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
              material = new Rhino.Display.DisplayMaterial(material)
              {
                Diffuse = element.Category?.LineColor.ToRhino() ?? System.Drawing.Color.White,
                Transparency = 0.0
              };

              if (material.Diffuse == System.Drawing.Color.Black)
                material.Diffuse = System.Drawing.Color.White;
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
      if (element is null)
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
      if (wires is object && wires.Length > 0)
      {
        foreach (var wire in wires)
          args.Pipeline.DrawCurve(wire, color, thickness);
      }
      else
      {
        var meshes = TryGetPreviewMeshes();
        if (meshes is object)
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
        if (element is object)
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
        if (element is object)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            p = instance.GetTransform().Origin.ToRhino();
          else switch (element.Location)
          {
            case Autodesk.Revit.DB.LocationPoint pointLocation: p = pointLocation.Point.ToRhino(); break;
            case Autodesk.Revit.DB.LocationCurve curveLocation: p = curveLocation.Curve.GetEndPoint(0).ToRhino(); break;
            default:
                var bbox = element.get_BoundingBox(null);
                if(bbox is object)
                  p = bbox.Min.ToRhino(); break;
          }

          if (!p.IsValid && element is Autodesk.Revit.DB.Level level)
          {
            p = new Rhino.Geometry.Point3d(0.0, 0.0, level.Elevation);
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
        if (element is object)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            x = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisX.ToRhino();
          else if (element.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            x = c.TangentAt(c.Domain.Min);
          }
          else if (element.Location is Autodesk.Revit.DB.LocationPoint pointLocation)
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

        var element = (Autodesk.Revit.DB.Element) this;
        if (element is object)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            y = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisY.ToRhino();
          else if (element.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            y = c.CurvatureAt(c.Domain.Min);
          }
          else if (element.Location is Autodesk.Revit.DB.LocationPoint pointLocation)
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

        var element = (Autodesk.Revit.DB.Element) this;
        if (element is object)
        {
          if (element is Autodesk.Revit.DB.Instance instance)
            z = (Rhino.Geometry.Vector3d) instance.GetTransform().BasisZ.ToRhino();
          else if (element.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          {
            var c = curveLocation.Curve.ToRhino();
            z = Rhino.Geometry.Vector3d.CrossProduct(c.TangentAt(c.Domain.Min), c.CurvatureAt(c.Domain.Min));
          }
          else if (element.Location is Autodesk.Revit.DB.LocationPoint pointLocation)
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

    public Rhino.Geometry.Curve Axis
    {
      get
      {
        var element = (Autodesk.Revit.DB.Element) this;
        Rhino.Geometry.Curve c = null;

        if(element?.Location is Autodesk.Revit.DB.LocationCurve curveLocation)
          c = curveLocation.Curve.ToRhino();

        if (c is null && element is Grid grid)
        {
          c = grid.Curve.ToRhino();
        }

        if (c is object)
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
  public class Element : ElementIdNonGeometryParam<Types.Element>
  {
    public override GH_Exposure Exposure => GH_Exposure.tertiary | GH_Exposure.obscure;
    public override Guid ComponentGuid => new Guid("F3EA4A9C-B24F-4587-A358-6A7E6D8C028B");

    public Element() : base("Element", "Element", "Represents a Revit document element.", "Params", "Revit") { }
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
      manager.AddTextParameter("UniqueID", "UUID", "A stable unique identifier for the Element within the document", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      DA.SetData("Category", element is Family family ? family.FamilyCategory : element?.Category);
      DA.SetData("Type", element?.GetTypeId());
      DA.SetData("Name", element?.Name);
      DA.SetData("UniqueID", element?.UniqueId);
    }
  }

  public class ElementDelete : TransactionalComponent
  {
    public override Guid ComponentGuid => new Guid("213C1F14-A827-40E2-957E-BA079ECCE700");
    public override GH_Exposure Exposure => GH_Exposure.septenary | GH_Exposure.obscure;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;
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

      var elementsToDelete = Parameters.Element.ToElementIds(elementsTree).ToArray();

      try
      {
        var deletedElements = Revit.ActiveDBDocument.Delete(elementsToDelete);

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
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      Options options = null;
      using (var geometry = element?.GetGeometry(ViewDetailLevel.Fine, out options)) using (options)
      {
        var list = geometry?.ToRhino().Where(x => x is object).ToList();

        switch (element.get_Parameter(BuiltInParameter.ELEMENT_IS_CUTTING)?.AsInteger())
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
      manager.AddParameter(new Parameters.ParameterKey(), "Parameters", "K", "Element parameters", GH_ParamAccess.list);
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
      if (element is object)
      {
        paramIds = new List<ElementId>(element.Parameters.Size);
        foreach (var group in element.GetParameters(Extension.ParameterSource.Any).GroupBy((x) => x.Definition.ParameterGroup).OrderBy((x) => x.Key))
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
        if (element is null)
          continue;

        foreach (var param in element.Parameters.OfType<Parameter>())
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
      var definitions = new Dictionary<int, Parameter>();

      foreach (var goo in Params.Input[0].VolatileData.AllData(true).OfType<Types.Element>())
      {
        var element = (Autodesk.Revit.DB.Element) goo;
        if (element is null)
          continue;

        foreach (var param in element.Parameters.OfType<Parameter>())
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
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      IGH_Goo parameterKey = null;
      if (!DA.GetData("ParameterKey", ref parameterKey))
        return;

      Autodesk.Revit.DB.Parameter parameter = null;
      switch (parameterKey.ScriptVariable())
      {
        case Parameter param:
          parameter = param;
          break;

        case string parameterName:
          parameter = element.LookupParameter(parameterName);
          if (parameter is null)
            AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{parameterName}' not defined in 'Element'");
          break;

        case int parameterId:
          if (Enum.IsDefined(typeof(BuiltInParameter), parameterId))
          {
            parameter = element.get_Parameter((BuiltInParameter) parameterId);
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{LabelUtils.GetLabelFor((BuiltInParameter) parameterId)}' not defined in 'Element'");
          }
          else if (Revit.ActiveDBDocument.GetElement(new ElementId(parameterId)) is ParameterElement parameterElement)
          {
            parameter = element.get_Parameter(parameterElement.GetDefinition());
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{parameterElement.Name}' not defined in 'Element'");
          }
          else
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Data conversion failed from {parameterKey.TypeName} to Revit Parameter element");
          break;

        case ElementId parameterElementId:
          if (Enum.IsDefined(typeof(BuiltInParameter), parameterElementId.IntegerValue))
          {
            parameter = element.get_Parameter((BuiltInParameter) parameterElementId.IntegerValue);
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{LabelUtils.GetLabelFor((BuiltInParameter) parameterElementId.IntegerValue)}' not defined in 'Element'");
          }
          else if (Revit.ActiveDBDocument.GetElement(parameterElementId) is ParameterElement parameterElement)
          {
            parameter = element.get_Parameter(parameterElement.GetDefinition());
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"Parameter '{parameterElement.Name}' not defined in 'Element'");
          }
          else
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Data conversion failed from {parameterKey.TypeName} to Revit Parameter element");
          break;

        default:
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Data conversion failed from {0} to Revit Parameter element");
          break;
      }

      DA.SetData("ParameterValue", parameter);
    }
  }

  public class ElementParameterSet : Component
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
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      IGH_Goo parameterKey = null;
      if (!DA.GetData("ParameterKey", ref parameterKey))
        return;

      IGH_Goo goo = null;
      if (!DA.GetData("ParameterValue", ref goo))
        return;

      Autodesk.Revit.DB.Parameter parameter = null;
      switch (parameterKey.ScriptVariable())
      {
        case Parameter param:
          parameter = param;
          break;

        case string parameterName:
          parameter = element.LookupParameter(parameterName);
          if (parameter is null)
            AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("Parameter '{0}' not defined in 'Element'", parameterName));
          break;

        case int parameterId:
          if (Enum.IsDefined(typeof(BuiltInParameter), parameterId))
          {
            parameter = element.get_Parameter((BuiltInParameter) parameterId);
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("Parameter '{0}' not defined in 'Element'", LabelUtils.GetLabelFor((BuiltInParameter) parameterId)));
          }
          else if (Revit.ActiveDBDocument.GetElement(new ElementId(parameterId)) is ParameterElement parameterElement)
          {
            parameter = element.get_Parameter(parameterElement.GetDefinition());
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("Parameter '{0}' not defined in 'Element'", parameterElement.Name));
          }
          else
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Data conversion failed from {0} to Revit Parameter element", parameterKey.TypeName));
          break;

        case ElementId parameterElementId:
          if (Enum.IsDefined(typeof(BuiltInParameter), parameterElementId.IntegerValue))
          {
            parameter = element.get_Parameter((BuiltInParameter) parameterElementId.IntegerValue);
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("Parameter '{0}' not defined in 'Element'", LabelUtils.GetLabelFor((BuiltInParameter) parameterElementId.IntegerValue)));
          }
          else if (Revit.ActiveDBDocument.GetElement(parameterElementId) is ParameterElement parameterElement)
          {
            parameter = element.get_Parameter(parameterElement.GetDefinition());
            if (parameter is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("Parameter '{0}' not defined in 'Element'", parameterElement.Name));
          }
          else
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Data conversion failed from {0} to Revit Parameter element", parameterKey.TypeName));
          break;

        default:
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Data conversion failed from {0} to Revit Parameter element", parameterKey.TypeName));
          break;
      }

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, element, parameter, goo));
    }

    double ToHost(double value, ParameterType type)
    {
      switch (type)
      {
        case ParameterType.Length:  return value / Math.Pow(Revit.ModelUnits, 1.0);
        case ParameterType.Area:    return value / Math.Pow(Revit.ModelUnits, 2.0);
        case ParameterType.Volume:  return value / Math.Pow(Revit.ModelUnits, 3.0);
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
      try
      {
        var value = goo.ScriptVariable();
        switch (parameter?.StorageType)
        {
          case StorageType.Integer:
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
          case StorageType.Double:
            {
              switch (value)
              {
                case int integer: parameter.Set((double) integer); break;
                case double real: parameter.Set(ToHost(real, parameter.Definition.ParameterType)); break;
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
          case StorageType.ElementId:
          {
            switch (value)
            {
              case Autodesk.Revit.DB.Element  ele: parameter.Set(ele.Id); break;
              case Autodesk.Revit.DB.Category cat: parameter.Set(cat.Id); break;
              case int integer: parameter.Set(new ElementId(integer)); break;
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
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Unable to cast 'Value' from {0} to {1}.", value.GetType().Name, parameter.StorageType.ToString()));

        DA.SetData(0, element, Iteration);
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, string.Format("Unable to set 'Value' to parameter {0} : {1}", parameter.Definition.Name, e.Message));
      }

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
