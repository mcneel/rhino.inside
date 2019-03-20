#if REVIT_2018
using System;
using System.Diagnostics;
using System.Collections.Generic;

using Autodesk.Revit.DB;
using Autodesk.Revit.DB.ExternalService;
using Autodesk.Revit.DB.DirectContext3D;

using Rhino;

namespace RhinoInside.Revit
{
  public abstract class DirectContext3DServer : IDirectContext3DServer
  {
    #region IExternalServer
    public abstract string GetDescription();
    public abstract string GetName();
    string IExternalServer.GetVendorId() => "RMA";
    ExternalServiceId IExternalServer.GetServiceId() => ExternalServices.BuiltInExternalServices.DirectContext3DService;
    public abstract Guid GetServerId();
    #endregion

    #region IDirectContext3DServer
    string IDirectContext3DServer.GetApplicationId() => string.Empty;
    string IDirectContext3DServer.GetSourceId() => string.Empty;
    bool IDirectContext3DServer.UsesHandles() => false;
    public virtual bool UseInTransparentPass(Autodesk.Revit.DB.View dBView) => false;
    public abstract bool CanExecute(Autodesk.Revit.DB.View dBView);
    public abstract Outline GetBoundingBox(Autodesk.Revit.DB.View dBView);
    public abstract void RenderScene(Autodesk.Revit.DB.View dBView, DisplayStyle displayStyle);
    #endregion

    virtual public void Register()
    {
      using (var service = ExternalServiceRegistry.GetService(ExternalServices.BuiltInExternalServices.DirectContext3DService) as MultiServerService)
      {
        service.AddServer(this);

        var activeServerIds = service.GetActiveServerIds();
        activeServerIds.Add(GetServerId());
        service.SetActiveServers(activeServerIds);
      }
    }

    virtual public void Unregister()
    {
      using (var service = ExternalServiceRegistry.GetService(ExternalServices.BuiltInExternalServices.DirectContext3DService) as MultiServerService)
      {
        var activeServerIds = service.GetActiveServerIds();
        activeServerIds.Remove(GetServerId());
        service.SetActiveServers(activeServerIds);

        service.RemoveServer(GetServerId());
      }
    }

    public const int VertexThreshold = ushort.MaxValue + 1;

    static IndexBuffer indexPointsBuffer;
    static IndexBuffer IndexPointsBuffer(int pointsCount)
    {
      Debug.Assert(pointsCount <= VertexThreshold);

      if (indexPointsBuffer == null)
      {
        indexPointsBuffer = new IndexBuffer(VertexThreshold * IndexPoint.GetSizeInShortInts());
        indexPointsBuffer.Map(VertexThreshold * IndexPoint.GetSizeInShortInts());
        using (var istream = indexPointsBuffer.GetIndexStreamPoint())
        {
          for (int vi = 0; vi < VertexThreshold; ++vi)
            istream.AddPoint(new IndexPoint(vi));
        }
        indexPointsBuffer.Unmap();
      }

      Debug.Assert(indexPointsBuffer.IsValid());
      return indexPointsBuffer;
    }

    static IndexBuffer indexLinesBuffer;
    static IndexBuffer IndexLinesBuffer(int pointsCount)
    {
      Debug.Assert(pointsCount <= VertexThreshold);

      if (indexLinesBuffer == null)
      {
        indexLinesBuffer = new IndexBuffer(VertexThreshold * IndexLine.GetSizeInShortInts());
        indexLinesBuffer.Map(VertexThreshold * IndexLine.GetSizeInShortInts());
        using (var istream = indexLinesBuffer.GetIndexStreamLine())
        {
          for (int vi = 0; vi < VertexThreshold - 1; ++vi)
            istream.AddLine(new IndexLine(vi, vi + 1));
        }
        indexLinesBuffer.Unmap();
      }

      Debug.Assert(indexLinesBuffer.IsValid());
      return indexLinesBuffer;
    }

    protected static VertexBuffer ToVertexBuffer
    (
      Rhino.Geometry.Mesh mesh,
      Primitive.Part part,
      out VertexFormatBits vertexFormatBits,
      System.Drawing.Color color = default(System.Drawing.Color)
    )
    {
      int verticesCount = part.EndVertexIndex - part.StartVertexIndex;
      int normalCount = mesh.Normals.Count == mesh.Vertices.Count ? verticesCount : 0;
      int colorsCount = color.IsEmpty ? (mesh.VertexColors.Count == mesh.Vertices.Count ? verticesCount : 0) : verticesCount;

      bool hasVertices = verticesCount > 0;
      bool hasNormals  = normalCount > 0;
      bool hasColors   = colorsCount > 0;

      if (hasVertices)
      {
        var vertices = mesh.Vertices;
        if (hasNormals)
        {
          var normals = mesh.Normals;
          if (hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionNormalColored;
            var colors = mesh.VertexColors;
            var vb = new VertexBuffer(verticesCount * VertexPositionNormalColored.GetSizeInFloats());
            vb.Map(verticesCount * VertexPositionNormalColored.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPositionNormalColored())
            {
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
              {
                var c = !color.IsEmpty ? color : colors[v];
                stream.AddVertex(new VertexPositionNormalColored(vertices[v].ToHost(), normals[v].ToHost(), new ColorWithTransparency(c.R, c.G, c.B, 255u - c.A)));
              }
            }
            vb.Unmap();
            return vb;
          }
          else
          {
            vertexFormatBits = VertexFormatBits.PositionNormal;
            var vb = new VertexBuffer(verticesCount * VertexPositionNormal.GetSizeInFloats());
            vb.Map(verticesCount * VertexPositionNormal.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPositionNormal())
            {
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
                stream.AddVertex(new VertexPositionNormal(vertices[v].ToHost(), normals[v].ToHost()));
            }
            vb.Unmap();
            return vb;
          }
        }
        else
        {
          if (hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionColored;
            var colors = mesh.VertexColors;
            var vb = new VertexBuffer(verticesCount * VertexPositionColored.GetSizeInFloats());
            vb.Map(verticesCount * VertexPositionColored.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPositionColored())
            {
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
              {
                var c = !color.IsEmpty ? color : colors[v];
                stream.AddVertex(new VertexPositionColored(vertices[v].ToHost(), new ColorWithTransparency(c.R, c.G, c.B, 255u - c.A)));
              }
            }
            vb.Unmap();
            return vb;
          }
          else
          {
            vertexFormatBits = VertexFormatBits.Position;
            var vb = new VertexBuffer(verticesCount * VertexPosition.GetSizeInFloats());
            vb.Map(verticesCount * VertexPosition.GetSizeInFloats());
            using (var stream = vb.GetVertexStreamPosition())
            {
              for (int v = part.StartVertexIndex; v < part.EndVertexIndex; ++v)
                stream.AddVertex(new VertexPosition(vertices[v].ToHost()));
            }
            vb.Unmap();
            return vb;
          }
        }
      }

      vertexFormatBits = 0;
      return null;
    }

    protected static IndexBuffer ToTrianglesBuffer
    (
      Rhino.Geometry.Mesh mesh, Primitive.Part part,
      out int triangleCount
      )
    {
      triangleCount = part.FaceCount;
      {
        var faces = mesh.Faces;
        for (int f = part.StartFaceIndex; f < part.EndFaceIndex; ++f)
        {
          if (faces[f].IsQuad)
            triangleCount++;
        }
      }

      if (triangleCount > 0)
      {
        var ib = new IndexBuffer(triangleCount * IndexTriangle.GetSizeInShortInts());
        ib.Map(triangleCount * IndexTriangle.GetSizeInShortInts());

        using (var istream = ib.GetIndexStreamTriangle())
        {
          var faces = mesh.Faces;
          for (int f = part.StartFaceIndex; f < part.EndFaceIndex; ++f)
          {
            var face = faces[f];

            istream.AddTriangle(new IndexTriangle(face.A - part.StartVertexIndex, face.B - part.StartVertexIndex, face.C - part.StartVertexIndex));
            if (face.IsQuad)
              istream.AddTriangle(new IndexTriangle(face.C - part.StartVertexIndex, face.D - part.StartVertexIndex, face.A - part.StartVertexIndex));
          }
        }

        ib.Unmap();
        return ib;
      }

      return null;
    }

    protected static IndexBuffer ToWireframeBuffer(Rhino.Geometry.Mesh mesh, out int linesCount)
    {
      linesCount = (mesh.Faces.Count * 3) + mesh.Faces.QuadCount;
      if (linesCount > 0)
      {
        var ib = new IndexBuffer(linesCount * IndexLine.GetSizeInShortInts());
        ib.Map(linesCount * IndexLine.GetSizeInShortInts());

        using (var istream = ib.GetIndexStreamLine())
        {
          foreach (var face in mesh.Faces)
          {
            istream.AddLine(new IndexLine(face.A, face.B));
            istream.AddLine(new IndexLine(face.B, face.C));
            istream.AddLine(new IndexLine(face.C, face.D));
            if (face.IsQuad)
              istream.AddLine(new IndexLine(face.D, face.A));
          }
        }

        ib.Unmap();
        return ib;
      }

      return null;
    }

    protected static IndexBuffer ToEdgeBuffer
    (
      Rhino.Geometry.Mesh mesh,
      Primitive.Part part,
      out int linesCount
    )
    {
      if (part.VertexCount != mesh.Vertices.Count)
      {
        if (part.VertexCount > 0)
        {
          linesCount = -part.VertexCount;
          return IndexPointsBuffer(part.VertexCount);
        }

        linesCount = 0;
      }
      else
      {
        var edgeIndices = new List<IndexPair>();
        if (mesh.Ngons.Count > 0)
        {
          foreach (var ngon in mesh.Ngons)
          {
            var boundary = ngon.BoundaryVertexIndexList();
            if ((boundary?.Length ?? 0) > 1)
            {
              for (int b = 0; b < boundary.Length - 1; ++b)
                edgeIndices.Add(new IndexPair((int) boundary[b], (int) boundary[b + 1]));

              edgeIndices.Add(new IndexPair((int) boundary[boundary.Length - 1], (int) boundary[0]));
            }
          }
        }
        else
        {
          var vertices = mesh.TopologyVertices;
          var edges = mesh.TopologyEdges;
          var edgeCount = edges.Count;
          for (int e = 0; e < edgeCount; ++e)
          {
            if (edges.IsEdgeUnwelded(e) || edges.GetConnectedFaces(e).Length < 2)
            {
              var pair = edges.GetTopologyVertices(e);
              pair.I = vertices.MeshVertexIndices(pair.I)[0];
              pair.J = vertices.MeshVertexIndices(pair.J)[0];
              edgeIndices.Add(pair);
            }
          }
        }

        linesCount = edgeIndices.Count;
        if (linesCount > 0)
        {
          var ib = new IndexBuffer(linesCount * IndexLine.GetSizeInShortInts());
          ib.Map(linesCount * IndexLine.GetSizeInShortInts());
          using (var istream = ib.GetIndexStreamLine())
          {
            foreach (var edge in edgeIndices)
            {
              Debug.Assert(0 <= edge.I && edge.I < part.VertexCount);
              Debug.Assert(0 <= edge.J && edge.J < part.VertexCount);
              istream.AddLine(new IndexLine(edge.I, edge.J));
            }
          }
          ib.Unmap();

          return ib;
        }
      }

      return null;
    }

    protected static int ToPolylineBuffer
    (
      Rhino.Geometry.Polyline polyline,
      out VertexFormatBits vertexFormatBits,
      out VertexBuffer vb, out int vertexCount,
      out IndexBuffer ib
    )
    {
      int linesCount = 0;

      if (polyline.SegmentCount > 0)
      {
        linesCount = polyline.SegmentCount;
        vertexCount = polyline.Count;

        vertexFormatBits = VertexFormatBits.Position;
        vb = new VertexBuffer(vertexCount * VertexPosition.GetSizeInFloats());
        vb.Map(vertexCount * VertexPosition.GetSizeInFloats());
        using (var vstream = vb.GetVertexStreamPosition())
        {
          foreach (var v in polyline)
            vstream.AddVertex(new VertexPosition(v.ToHost()));
        }
        vb.Unmap();

        ib = IndexLinesBuffer(vertexCount);
      }
      else
      {
        vertexFormatBits = 0;
        vb = null; vertexCount = 0;
        ib = null;
      }

      return linesCount;
    }

    protected static int ToPointsBuffer
    (
      Rhino.Geometry.Point point,
      out VertexFormatBits vertexFormatBits,
      out VertexBuffer vb, out int vertexCount,
      out IndexBuffer ib
    )
    {
      int pointsCount = 0;

      if (point.Location.IsValid)
      {
        pointsCount = 1;
        vertexCount = 1;

        vertexFormatBits = VertexFormatBits.Position;
        vb = new VertexBuffer(pointsCount * VertexPosition.GetSizeInFloats());
        vb.Map(pointsCount * VertexPosition.GetSizeInFloats());
        using (var vstream = vb.GetVertexStreamPosition())
        {
          vstream.AddVertex(new VertexPosition(point.Location.ToHost()));
        }
        vb.Unmap();

        ib = IndexPointsBuffer(pointsCount);
      }
      else
      {
        vertexFormatBits = 0;
        vb = null; vertexCount = 0;
        ib = null;
      }

      return pointsCount;
    }

    protected static int ToPointsBuffer
    (
      Rhino.Geometry.PointCloud pointCloud,
      Primitive.Part part,
      out VertexFormatBits vertexFormatBits,
      out VertexBuffer vb, out int vertexCount,
      out IndexBuffer ib
    )
    {
      int pointsCount = part.VertexCount;
      int normalCount = pointCloud.ContainsNormals ? pointsCount : 0;
      int colorsCount = pointCloud.ContainsColors  ? pointsCount : 0;

      bool hasPoints  = pointsCount > 0;
      bool hasNormals = normalCount == pointsCount;
      bool hasColors  = colorsCount == pointsCount;

      if (hasPoints)
      {
        if (hasNormals)
        {
          if(hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionNormalColored;
            vb = new VertexBuffer(pointsCount * VertexPositionNormalColored.GetSizeInFloats());
            vb.Map(pointsCount * VertexPositionNormalColored.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPositionNormalColored())
            {
              for(int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                var c = new ColorWithTransparency(point.Color.R, point.Color.G, point.Color.B, 255u - point.Color.A);
                vstream.AddVertex(new VertexPositionNormalColored(point.Location.ToHost(), point.Normal.ToHost(), c));
              }
            }

            vb.Unmap();
          }
          else
          {
            vertexFormatBits = VertexFormatBits.PositionNormal;
            vb = new VertexBuffer(pointsCount * VertexPositionNormal.GetSizeInFloats());
            vb.Map(pointsCount * VertexPositionNormal.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPositionNormal())
            {
              for (int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                vstream.AddVertex(new VertexPositionNormal(point.Location.ToHost(), point.Normal.ToHost()));
              }
            }

            vb.Unmap();
          }
        }
        else
        {
          if (hasColors)
          {
            vertexFormatBits = VertexFormatBits.PositionColored;
            vb = new VertexBuffer(pointsCount * VertexPositionColored.GetSizeInFloats());
            vb.Map(pointsCount * VertexPositionColored.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPositionColored())
            {
              for (int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                var c = new ColorWithTransparency(point.Color.R, point.Color.G, point.Color.B, 255u - point.Color.A);
                vstream.AddVertex(new VertexPositionColored(point.Location.ToHost(), c));
              }
            }

            vb.Unmap();
          }
          else
          {
            vertexFormatBits = VertexFormatBits.Position;
            vb = new VertexBuffer(pointsCount * VertexPosition.GetSizeInFloats());
            vb.Map(pointsCount * VertexPosition.GetSizeInFloats());

            using (var vstream = vb.GetVertexStreamPosition())
            {
              for (int p = part.StartVertexIndex; p < part.EndVertexIndex; ++p)
              {
                var point = pointCloud[p];
                vstream.AddVertex(new VertexPosition(point.Location.ToHost()));
              }
            }

            vb.Unmap();
          }
        }

        ib = IndexPointsBuffer(pointsCount);
      }
      else
      {
        vertexFormatBits = 0;
        vb = null;
        ib = null;
      }

      vertexCount = pointsCount;
      return pointsCount;
    }

    #region Primitive
    protected class Primitive : IDisposable
    {
      protected VertexFormatBits vertexFormatBits;
      protected int vertexCount;
      protected VertexBuffer vertexBuffer;
      protected VertexFormat vertexFormat;

      protected int triangleCount;
      protected IndexBuffer triangleBuffer;

      protected int linesCount;
      protected IndexBuffer linesBuffer;

      protected EffectInstance effectInstance;
      protected Rhino.Geometry.GeometryBase geometry;
      public struct Part
      {
        public readonly int StartVertexIndex;
        public readonly int EndVertexIndex;
        public readonly int StartFaceIndex;
        public readonly int EndFaceIndex;

        public int VertexCount => EndVertexIndex - StartVertexIndex;
        public int FaceCount   => EndFaceIndex - StartFaceIndex;

        public Part(int startVertexIndex, int endVertexIndex, int startFaceIndex, int endFaceIndex)
        {
          StartVertexIndex = startVertexIndex;
          EndVertexIndex   = endVertexIndex;
          StartFaceIndex   = startFaceIndex;
          EndFaceIndex     = endFaceIndex;
        }

        public Part(int startVertexIndex, int endVertexIndex) : this(startVertexIndex, endVertexIndex, 0, -1) { }

        public static implicit operator Part(Rhino.Geometry.PointCloud pc)
        {
          return new Part(0, pc?.Count ?? -1);
        }
        public static implicit operator Part(Rhino.Geometry.Mesh m)
        {
          return new Part(0, m?.Vertices.Count ?? -1, 0, m?.Faces.Count ?? -1);
        }
        public static implicit operator Part(Rhino.Geometry.MeshPart p)
        {
          return new Part(p?.StartVertexIndex ?? 0, p?.EndVertexIndex ?? -1, p?.StartFaceIndex ?? 0, p?.EndFaceIndex ?? -1);
        }
      }
      protected Part part;

      public Rhino.Geometry.BoundingBox ClippingBox => geometry.GetBoundingBox(false);

      public Primitive(Rhino.Geometry.Point p)               { geometry = p; }
      public Primitive(Rhino.Geometry.PointCloud pc)         { geometry = pc; part = pc; }
      public Primitive(Rhino.Geometry.PointCloud pc, Part p) { geometry = pc; part = p; }
      public Primitive(Rhino.Geometry.Curve c)               { geometry = c; }
      public Primitive(Rhino.Geometry.Mesh m)                { geometry = m; part = m; }
      public Primitive(Rhino.Geometry.Mesh m, Part p)        { geometry = m; part = p; }

      void IDisposable.Dispose()
      {
        effectInstance?.Dispose(); effectInstance = null;
        if(linesBuffer != indexLinesBuffer && linesBuffer != indexPointsBuffer)
        linesBuffer?.Dispose();    linesBuffer = null; linesCount = 0;
        triangleBuffer?.Dispose(); triangleBuffer = null; triangleCount = 0;
        vertexFormat?.Dispose();   vertexFormat = null;
        vertexBuffer?.Dispose();   vertexBuffer = null; vertexCount = 0;
      }

      public virtual EffectInstance EffectInstance(DisplayStyle displayStyle, bool IsShadingPass)
      {
        if (effectInstance == null)
          effectInstance = new EffectInstance(vertexFormatBits);

        return effectInstance;
      }

      public virtual bool Regen()
      {
        if (geometry != null)
        {
          if (!BeginRegen())
            return false;

          if (geometry is Rhino.Geometry.Mesh mesh)
          {
            vertexBuffer = ToVertexBuffer(mesh, part, out vertexFormatBits);
            vertexCount = part.VertexCount;

            triangleBuffer = ToTrianglesBuffer(mesh, part, out triangleCount);
            linesBuffer = ToEdgeBuffer(mesh, part, out linesCount);
          }
          else if (geometry is Rhino.Geometry.Curve curve)
          {
            using (var polyline = curve.ToPolyline(Revit.VertexTolerance * Revit.ModelUnits, Revit.AngleTolerance, Revit.ShortCurveTolerance * Revit.ModelUnits, 0.0))
              linesCount = ToPolylineBuffer(polyline.ToPolyline(), out vertexFormatBits, out vertexBuffer, out vertexCount, out linesBuffer);
          }
          else if (geometry is Rhino.Geometry.Point point)
          {
            linesCount = -ToPointsBuffer(point, out vertexFormatBits, out vertexBuffer, out vertexCount, out linesBuffer);
          }
          else if (geometry is Rhino.Geometry.PointCloud pointCloud)
          {
            linesCount = -ToPointsBuffer(pointCloud, part, out vertexFormatBits, out vertexBuffer, out vertexCount, out linesBuffer);
          }

          vertexFormat = new VertexFormat(vertexFormatBits);
          geometry = null;

          EndRegen();
        }

        return true;
      }

      public virtual void Draw(DisplayStyle displayStyle)
      {
        if (!Regen())
          return;

        if (DrawContext.IsTransparentPass())
        {
          if (vertexCount > 0)
          {
            var ei = EffectInstance(displayStyle, true);

            if (triangleCount > 0)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                triangleBuffer, triangleCount * 3,
                vertexFormat, ei,
                PrimitiveType.TriangleList,
                0, triangleCount
              );
            }
            else if (linesBuffer != null)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                linesBuffer, vertexCount,
                vertexFormat, ei,
                PrimitiveType.PointList,
                0, vertexCount
              );
            }
          }
        }
        else
        {
          if (linesCount != 0)
          {
            if (triangleBuffer != null)
            {
              bool edges = displayStyle == DisplayStyle.Wireframe ||
                           displayStyle == DisplayStyle.HLR ||
                           displayStyle == DisplayStyle.ShadingWithEdges ||
                           displayStyle == DisplayStyle.FlatColors ||
                           displayStyle == DisplayStyle.RealisticWithEdges;

              if (!edges)
                return;
            }

            if (linesCount > 0)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                linesBuffer, linesCount * 2,
                vertexFormat, EffectInstance(displayStyle, false),
                PrimitiveType.LineList,
                0, linesCount
              );
            }
            else if(triangleCount == 0)
            {
              DrawContext.FlushBuffer
              (
                vertexBuffer, vertexCount,
                linesBuffer, vertexCount,
                vertexFormat, EffectInstance(displayStyle, false),
                PrimitiveType.PointList,
                0, vertexCount
              );
            }
          }
        }
      }
    }

    static Stopwatch RegenTime = new Stopwatch();
    public static long RegenThreshold = 200;

    static bool BeginRegen()
    {
      if (RegenTime.ElapsedMilliseconds > RegenThreshold)
        return false;

      RegenTime.Start();
      return true;
    }
    static void EndRegen()
    {
      RegenTime.Stop();
    }

    public static bool RegenComplete()
    {
      var ms = RegenTime.ElapsedMilliseconds;
      RegenTime.Reset();
      return ms == 0;
    }
    #endregion
  }
}
#else
namespace RhinoInside.Revit
{
  public abstract class DirectContext3DServer
  {
    public static bool RegenComplete() => true;
    public static long RegenThreshold = 200;
  }
}
#endif
