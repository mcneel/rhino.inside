using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

using Autodesk.Revit.DB;
using Autodesk.Revit.DB.Events;
using Autodesk.Revit.UI;

using Rhino;
using Rhino.PlugIns;

using Grasshopper;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH
{
  internal class Addon
  {
    PreviewServer grasshopperPreviewServer;

    internal Result OnStartup(UIControlledApplication applicationUI)
    {
      // Register GrasshopperPreviewServer
      grasshopperPreviewServer = new PreviewServer();
      grasshopperPreviewServer.Register();
      RhinoApp.Idle += TryLoadGrasshopperComponents;

      return Result.Succeeded;
    }

    internal Result OnShutdown(UIControlledApplication applicationUI)
    {
      // Unregister GrasshopperPreviewServer
      grasshopperPreviewServer?.Unregister();
      grasshopperPreviewServer = null;

      return Result.Succeeded;
    }

    static bool LoadGrasshopperComponents()
    {
      var LoadGHAProc = Instances.ComponentServer.GetType().GetMethod("LoadGHA", BindingFlags.NonPublic | BindingFlags.Instance);
      if (LoadGHAProc == null)
        return false;

      var bCoff = Instances.Settings.GetValue("Assemblies:COFF", true);
      Instances.Settings.SetValue("Assemblies:COFF", false);

      var rc = (bool) LoadGHAProc.Invoke
      (
        Instances.ComponentServer,
        new object[] { new GH_ExternalFile(Assembly.GetExecutingAssembly().Location), false }
      );

      // Load all the gha installed under the %APPDATA%\Grasshopper\Libraries-Autodesk_Revit_20XX
      var schemeName = Revit.ApplicationUI.ControlledApplication.VersionName.Replace(' ', '_');
      var revitAssemblyFolder = Grasshopper.Folders.DefaultAssemblyFolder.Substring(0, Grasshopper.Folders.DefaultAssemblyFolder.Length - 1) + '-' + schemeName;
      var assemblyFolder = new DirectoryInfo(revitAssemblyFolder);
      try
      {
        foreach (var file in assemblyFolder.EnumerateFiles("*.gha"))
          LoadGHAProc.Invoke(Instances.ComponentServer, new object[] { new GH_ExternalFile(file.FullName), false });
      }
      catch (System.IO.DirectoryNotFoundException) { }

      Instances.Settings.SetValue("Assemblies:COFF", bCoff);

      if (rc)
        GH_ComponentServer.UpdateRibbonUI();

      return rc;
    }

    void TryLoadGrasshopperComponents(object sender, EventArgs e)
    {
      // Load this assembly as a Grasshopper assembly
      if (PlugIn.GetPlugInInfo(new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF)).IsLoaded)
      {
        if (LoadGrasshopperComponents())
          RhinoApp.Idle -= TryLoadGrasshopperComponents;
      }
    }

    internal void OnDocumentChanged(object sender, DocumentChangedEventArgs e)
    {
      var document = e.GetDocument();
      var added = e.GetAddedElementIds();
      var deleted = e.GetDeletedElementIds();
      var modified = e.GetModifiedElementIds();

      if (added.Count > 0 || deleted.Count > 0 || modified.Count > 0)
      {
        var materialsChanged = modified.Select((x) => document.GetElement(x)).OfType<Material>().Any();

        foreach (GH_Document definition in Instances.DocumentServer)
        {
          foreach (var obj in definition.Objects)
          {
            if (obj is IGH_Param param)
            {
              if (param.SourceCount > 0)
                continue;

              if (param.Phase == GH_SolutionPhase.Blank)
                continue;

              if (obj is Parameters.IGH_PersistentGeometryParam persistent)
              {
                if (persistent.NeedsToBeExpired(document, added, deleted, modified))
                  param.ExpireSolution(false);
              }
            }
            else if (obj is IGH_Component component)
            {
              if (component is Components.DocumentElements)
              {
                component.ExpireSolution(false);
              }
              else
              {
                bool needsToBeExpired = false;
                foreach (var inputParam in component.Params.Input)
                {
                  if (inputParam.SourceCount > 0)
                    continue;

                  if (inputParam.Phase == GH_SolutionPhase.Blank)
                    continue;

                  if (inputParam is Parameters.IGH_PersistentGeometryParam persistent)
                  {
                    if (persistent.NeedsToBeExpired(document, added, deleted, modified))
                    {
                      needsToBeExpired = true;
                      break;
                    }
                  }
                }

                if (needsToBeExpired) component.ExpireSolution(true);
                else foreach (var outParam in component.Params.Output)
                  {
                    if (outParam is Parameters.IGH_PersistentGeometryParam persistent)
                    {
                      if (persistent.NeedsToBeExpired(document, added, deleted, modified))
                      {
                        foreach (var r in outParam.Recipients)
                          r.ExpireSolution(false);
                      }
                      else if (materialsChanged)
                      {
                        foreach (var goo in outParam.VolatileData.AllData(true))
                        {
                          if (goo is IGH_PreviewMeshData previewMeshData)
                            previewMeshData.DestroyPreviewMeshes();
                        }
                      }
                    }
                  }
              }
            }
          }

          if (definition.Enabled)
            definition.NewSolution(false);
        }
      }
    }
  }
}
