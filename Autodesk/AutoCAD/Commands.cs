using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Geometry;

// This line is not mandatory, but improves loading performances
[assembly: CommandClass(typeof(RhinoInside.AutoCAD.TestCommands))]

namespace RhinoInside.AutoCAD
{
  // This class is instantiated by AutoCAD for each document when
  // a command is called by the user the first time in the context
  // of a given document
  public class TestCommands
  {
    [CommandMethod("TestRhinoInside")]
    public static void TestRhinoInside()
    {
      // RhinoCommon code
      var plane = Rhino.Geometry.Plane.WorldXY;
      var sphere = new Rhino.Geometry.Sphere(plane, 5.0);
      //var mesh = Rhino.Geometry.Mesh.CreateIcoSphere(sphere, 3);
      var mesh = Rhino.Geometry.Mesh.CreateQuadSphere(sphere, 3);

      // Get the current document and database, and start a transaction
      var document = Application.DocumentManager.MdiActiveDocument;
      var database = document.Database;

      using (var transaction = database.TransactionManager.StartTransaction())
      {
        // Open the Block table record for read
        var block_table = transaction.GetObject(database.BlockTableId, OpenMode.ForRead) as BlockTable;

        // Open the Block table record Model space for write
        var block_table_record = transaction.GetObject(block_table[BlockTableRecord.ModelSpace], OpenMode.ForWrite) as BlockTableRecord;

        // Create a polyface mesh
        using (var poly_face_mesh = new PolyFaceMesh())
        {
          // Add the new object to the block table record and the transaction
          block_table_record.AppendEntity(poly_face_mesh);
          transaction.AddNewlyCreatedDBObject(poly_face_mesh, true);
          
          // Before adding vertexes, the polyline must be in the drawing
          var points_collection = new Point3dCollection();
          foreach (var v in mesh.Vertices)
            points_collection.Add(new Point3d(v.X, v.Y, v.Z));

          // Add mesh vertices
          foreach (Point3d point in points_collection)
          {
            var mesh_vertex = new PolyFaceMeshVertex(point);
            poly_face_mesh.AppendVertex(mesh_vertex);
            transaction.AddNewlyCreatedDBObject(mesh_vertex, true);
          }

          // Add mesh faces. Note, AutoCAD face vertex indices start at 1, not 0.
          foreach (var f in mesh.Faces)
          {
            using (var face_record = new FaceRecord((short)(f.A + 1), (short)(f.B + 1), (short)(f.C + 1), (short)(f.D + 1)))
            {
              poly_face_mesh.AppendFaceRecord(face_record);
              transaction.AddNewlyCreatedDBObject(face_record, true);
            }
          }
        }

        document.Editor.UpdateTiledViewportsFromDatabase();

        transaction.Commit();
      }
    }
  }
}
