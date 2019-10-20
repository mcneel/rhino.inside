using System;
using System.Collections.Generic;
using System.Linq;
using Grasshopper.Kernel;
using Rhino.Geometry;
using Rhino.PlugIns;
using Rhino.Runtime.InProcess;
using UnrealEngine.Engine;
using UnrealEngine.Runtime;

namespace Sample3
{
  [UClass, BlueprintType, Blueprintable]
  class ASample3Actor : AActor
  {
    static RhinoCore rhinoCore;
    static readonly Guid GrasshopperGuid = new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF);
    static GH_Document definition;
    static Mesh mesh;

    /// <summary>
    /// Resolve the local Rhino related assemblies.
    /// </summary>
    static ASample3Actor()
    {
      RhinoInside.Resolver.Initialize();
    }

    /// <summary>
    /// Start Rhino if it has not already been started.
    /// We start Rhino without a spash screen and with a hidden `WindowStyle`.
    /// We could use the `NoWindow` display, since we don't need the Rhino UI.
    /// </summary>
    [UFunction, BlueprintCallable]
    public void LaunchRhino()
    {
      if (rhinoCore == null)
        rhinoCore = new RhinoCore(new string[] { "/NOSPLASH" }, WindowStyle.Hidden);
    }

    #region Grasshopper

    [UFunction, BlueprintCallable]
    public void LoadGH()
    {
      if (!PlugIn.LoadPlugIn(GrasshopperGuid))
        return;

      var script = new Grasshopper.Plugin.GH_RhinoScriptInterface();

      if (!script.IsEditorLoaded())
        script.LoadEditor();

      script.ShowEditor();

      if (definition == null)
        Grasshopper.Instances.DocumentServer.DocumentAdded += DocumentServer_DocumentAdded;
    }

    private void DocumentServer_DocumentAdded(GH_DocumentServer sender, GH_Document doc)
    {
      doc.SolutionEnd += Definition_SolutionEnd;
      definition = doc;
    }

    /// <summary>
    /// When Grasshopper stops solving, get the preview objects.
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void Definition_SolutionEnd(object sender, GH_SolutionEventArgs e)
    {
      FMessage.Log(ELogVerbosity.Warning, "Solution End");
      if (definition != e.Document)
        return;

      mesh = GetDocumentPreview(e.Document);

      if (mesh == null)
        return;

      mesh.Faces.ConvertQuadsToTriangles();
      mesh.Flip(true, true, true);

    }

    /// <summary>
    /// Go through definition and get the component or param outputs that are BREPs or Meshes.
    /// </summary>
    /// <param name="document"></param>
    /// <returns></returns>
    Rhino.Geometry.Mesh GetDocumentPreview(GH_Document document)
    {
      var meshPreview = new Rhino.Geometry.Mesh();

      var meshes = new List<Rhino.Geometry.Mesh>();

      foreach (var obj in document.Objects.OfType<IGH_ActiveObject>())
      {
        if (obj.Locked)
          continue;

        if (obj is IGH_PreviewObject previewObject)
        {
          if (previewObject.IsPreviewCapable)
          {
            if (obj is IGH_Component component)
            {
              if (!component.Hidden)
                foreach (var param in component.Params.Output)
                  meshes.AddRange(GetParamMeshes(param));
            }
            else if (obj is IGH_Param param)
            {
              meshes.AddRange(GetParamMeshes(param));
            }
          }
        }
      }

      if (meshes.Count > 0)
      {
        meshPreview.Append(meshes);
        return meshPreview;
      }
      else return null;
    }

    /// <summary>
    /// Return the meshes from params.
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    public List<Rhino.Geometry.Mesh> GetParamMeshes(IGH_Param param)
    {
      var meshes = new List<Rhino.Geometry.Mesh>();
      foreach (var value in param.VolatileData.AllData(true))
      {
        if (value is IGH_PreviewData)
        {
          switch (value.ScriptVariable())
          {
            case Rhino.Geometry.Mesh mesh:
              meshes.Add(mesh);
              break;
            case Rhino.Geometry.Brep brep:
              var previewMesh = new Rhino.Geometry.Mesh();
              previewMesh.Append(Rhino.Geometry.Mesh.CreateFromBrep(brep, Rhino.Geometry.MeshingParameters.Default));
              meshes.Add(previewMesh);
              break;
          }
        }
      }
      return meshes;
    }

    #endregion

    /// <summary>
    /// Build a list of vertices from the static mesh.
    /// </summary>
    /// <returns></returns>
    [UFunction, BlueprintCallable]
    public List<FVector> GetVertices()
    {
      var list = new List<FVector>();
      foreach (var vert in mesh.Vertices)
        list.Add(new FVector(vert.X, vert.Y, vert.Z));
      return list;
    }

    /// <summary>
    /// Build a list of face ids from the static mesh.
    /// </summary>
    /// <returns></returns>
    [UFunction, BlueprintCallable]
    public List<int> GetFaceIds()
    {
      var list = new List<int>();
      foreach (var face in mesh.Faces)
      {
        list.Add(face.A);
        list.Add(face.B);
        list.Add(face.C);
      }
      return list;
    }

    
  }
}
