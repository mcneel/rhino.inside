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
    public static Grasshopper.Plugin.GH_RhinoScriptInterface Script = new Grasshopper.Plugin.GH_RhinoScriptInterface();
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
      Revit.ApplicationUI.Idling += OnIdle;

      return LoadReturnCode.Success;
    }

    void IGuest.OnCheckOut()
    {
      Revit.ApplicationUI.Idling -= OnIdle;
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

    void OnDocumentChanged(object sender, DocumentChangedEventArgs e)
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
          (e.Operation == UndoOperation.TransactionCommitted || e.Operation == UndoOperation.TransactionUndone || e.Operation == UndoOperation.TransactionRedone) &&
          GH_Document.EnableSolutions &&
          Instances.ActiveCanvas.Document == definition &&
          definition.Enabled &&
          definition.SolutionState != GH_ProcessStep.Process;

          var change = new DocumentChangedEvent()
          {
            Operation = e.Operation,
            Document = document,
            Definition = definition
          };

          foreach (var obj in definition.Objects)
          {
            if (obj is Parameters.IGH_ElementIdParam persistentParam)
            {
              if (persistentParam.DataType == GH_ParamData.remote)
                continue;

              if (persistentParam.Phase == GH_SolutionPhase.Blank)
                continue;

              if (persistentParam.NeedsToBeExpired(document, added, deleted, modified))
              {
                if (expireNow)
                  persistentParam.ExpireSolution(false);
                else
                  change.ExpiredObjects.Add(persistentParam);
              }
            }
            else if (obj is Components.IGH_ElementIdComponent persistentComponent)
            {
              if (persistentComponent.NeedsToBeExpired(e))
              {
                if (expireNow)
                  persistentComponent.ExpireSolution(false);
                else
                  change.ExpiredObjects.Add(persistentComponent);
              }
            }
          }

          if (definition.SolutionState != GH_ProcessStep.Process)
          {
            changeQuque.Enqueue(change);
          }
          else if (definition == Instances.ActiveCanvas.Document)
          {
            if (change.ExpiredObjects.Count > 0)
            {
              foreach (var obj in change.ExpiredObjects)
              {
                obj.ClearData();
                obj.AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"This object was expired because it contained obsolete Revit elements.");
              }

              Instances.DocumentEditor.SetStatusBarEvent
              (
                new GH_RuntimeMessage
                (
                  change.ExpiredObjects.Count == 1 ?
                  $"An object was expired because it contained obsolete Revit elements." :
                  $"{change.ExpiredObjects.Count} objects were expired because them contained obsolete Revit elements.",
                  GH_RuntimeMessageLevel.Remark,
                  "Document"
                )
              );
            }
          }
        }
      }
    }

    class DocumentChangedEvent
    {
      public UndoOperation Operation;
      public Document Document = null;
      public GH_Document Definition = null;
      public readonly List<IGH_ActiveObject> ExpiredObjects = new List<IGH_ActiveObject>();
      public void Apply()
      {
        foreach (var obj in ExpiredObjects)
          obj.ExpireSolution(false);

        if (Operation == UndoOperation.TransactionCommitted)
        {
          Definition.NewSolution(false);
        }
        else
        {
          // We create a transaction to avoid new changes while undoing or redoing
          using (var transaction = new Transaction(Document))
          {
            transaction.Start(Operation.ToString());
            Definition.NewSolution(false);
          }
        }
      }
    }

    Queue<DocumentChangedEvent> changeQuque = new Queue<DocumentChangedEvent>();

    void OnIdle(object sender, Autodesk.Revit.UI.Events.IdlingEventArgs e)
    {
      while (changeQuque.Count > 0)
        changeQuque.Dequeue().Apply();
    }
  }
}
