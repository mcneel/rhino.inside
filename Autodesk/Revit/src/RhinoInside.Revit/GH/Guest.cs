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
  [GuestPlugInId("B45A29B1-4343-4035-989E-044E8580D9CF")]
  internal class Guest : IGuest
  {
    PreviewServer previewServer;
    public string Name => "Grasshopper";
    LoadReturnCode IGuest.OnCheckIn(ref string errorMessage)
    {
      string message = null;
      try
      {
        if(!LoadComponents())
          message = "Failed to load Revit Grasshopper components.";
      }
      catch(Exception e)
      {
        message = e.Message;
      }

      if (!(message is null))
      {
        errorMessage = message;
        return LoadReturnCode.ErrorShowDialog;
      }

      // Register PreviewServer
      previewServer = new PreviewServer();
      previewServer.Register();

      Revit.DocumentChanged += OnDocumentChanged;

      return LoadReturnCode.Success;
    }

    void IGuest.OnCheckOut()
    {
      Revit.DocumentChanged -= OnDocumentChanged;

      // Unregister PreviewServer
      previewServer?.Unregister();
      previewServer = null;
    }

    static bool LoadGHA(string filePath)
    {
      var LoadGHAProc = typeof(GH_ComponentServer).GetMethod("LoadGHA", BindingFlags.NonPublic | BindingFlags.Instance);
      if (LoadGHAProc == null)
        return false;

      try
      {
        return (bool) LoadGHAProc.Invoke
        (
          Instances.ComponentServer,
          new object[] { new GH_ExternalFile(filePath), false }
        );
      }
      catch(TargetInvocationException e)
      {
        throw e.InnerException;
      }
    }

    bool LoadComponents()
    {
      var bCoff = Instances.Settings.GetValue("Assemblies:COFF", true);
      Instances.Settings.SetValue("Assemblies:COFF", false);

      var rc = LoadGHA(Assembly.GetExecutingAssembly().Location);

      var assemblyFolders = new DirectoryInfo[]
      {
        // %ProgramData%\Grasshopper\Libraries-Inside-Revit-20XX
        new DirectoryInfo(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData), "Grasshopper", $"Libraries-{Rhinoceros.SchemeName}")),

        // %APPDATA%\Grasshopper\Libraries-Inside-Revit-20XX
        new DirectoryInfo(Folders.DefaultAssemblyFolder.Substring(0, Folders.DefaultAssemblyFolder.Length - 1) + '-' + Rhinoceros.SchemeName)
      };

      foreach (var folder in assemblyFolders)
      {
        IEnumerable<FileInfo> assemblyFiles;
        try { assemblyFiles = folder.EnumerateFiles("*.gha");}
        catch (System.IO.DirectoryNotFoundException) { continue; }

        foreach (var assemblyFile in assemblyFiles)
        {
          bool loaded = false;
          string mainContent = string.Empty;
          string expandedContent = string.Empty;

          try
          {
            loaded = LoadGHA(assemblyFile.FullName);
          }
          catch (Exception e)
          {
            mainContent     = e.Message;
            expandedContent = e.Source;
          }

          if (!loaded)
          {
            using
            (
              var taskDialog = new TaskDialog(MethodBase.GetCurrentMethod().DeclaringType.FullName)
              {
                Title = "Grasshopper Assembly Failure",
                MainIcon = TaskDialogIcons.IconError,
                TitleAutoPrefix = false,
                AllowCancellation = false,
                MainInstruction = $"Grasshopper cannot load the external assembly {assemblyFile.Name}. Please contact the provider for assistance.",
                MainContent = mainContent,
                ExpandedContent = expandedContent,
                FooterText = assemblyFile.FullName
              }
            )
            {
              taskDialog.Show();
            }
          }
        }
      }

      Instances.Settings.SetValue("Assemblies:COFF", bCoff);

      if (rc)
        GH_ComponentServer.UpdateRibbonUI();

      return rc;
    }

    static void OnDocumentChanged(object sender, DocumentChangedEventArgs e)
    {
      var document = e.GetDocument();
      var added    = e.GetAddedElementIds();
      var deleted  = e.GetDeletedElementIds();
      var modified = e.GetModifiedElementIds();

      if (added.Count > 0 || deleted.Count > 0 || modified.Count > 0)
      {
        foreach (GH_Document definition in Instances.DocumentServer)
        {
          bool expireNow =
          GH_Document.EnableSolutions &&
          Instances.ActiveCanvas.Document == definition &&
          definition.Enabled &&
          definition.SolutionState != GH_ProcessStep.Process;

          foreach (var obj in definition.Objects)
          {
            if (obj is IGH_Param param)
            {
              if (param.SourceCount > 0)
                continue;

              if (param.Phase == GH_SolutionPhase.Blank)
                continue;

              if (obj is Parameters.IGH_PersistentElementParam persistentParam)
              {
                if (persistentParam.NeedsToBeExpired(document, added, deleted, modified))
                {
                  if (expireNow)
                    param.ExpireSolution(false);
                  else
                    param.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, "This parameter contains expired elements.");
                }
              }
            }
            else if (obj is IGH_Component component)
            {
              if (component is Components.IGH_PersistentElementComponent persistentComponent)
              {
                if (persistentComponent.NeedsToBeExpired(e))
                {
                  if (expireNow)
                    component.ExpireSolution(false);
                  else
                    component.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, "Document has been changed since the last solution.");
                }
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

                  if (inputParam is Parameters.IGH_PersistentElementParam persistentParam)
                  {
                    if (persistentParam.NeedsToBeExpired(document, added, deleted, modified))
                    {
                      needsToBeExpired = true;
                      break;
                    }
                  }
                }

                if (needsToBeExpired)
                {
                  if (expireNow)
                    component.ExpireSolution(false);
                  else
                    component.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, "Some input parameter contains expired elements.");
                }
              }
            }
          }

          if (expireNow)
            Revit.EnqueueAction(doc => definition.NewSolution(false));
        }
      }
    }
  }
}
