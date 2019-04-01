using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.IO;

using Autodesk.Revit.DB;
using Autodesk.Revit.DB.Events;
using Autodesk.Revit.UI;
using Autodesk.Revit.UI.Events;

using Rhino;
using Rhino.Runtime.InProcess;
using Rhino.PlugIns;

using Grasshopper;
using Grasshopper.Kernel;

namespace RhinoInside.Revit
{
  [Autodesk.Revit.Attributes.Transaction(Autodesk.Revit.Attributes.TransactionMode.Manual)]
  [Autodesk.Revit.Attributes.Regeneration(Autodesk.Revit.Attributes.RegenerationOption.Manual)]
  [Autodesk.Revit.Attributes.Journaling(Autodesk.Revit.Attributes.JournalingMode.NoCommandData)]
  public partial class Revit : IExternalApplication
  {
    #region Revit static constructor
    static Revit()
    {
      ResolveEventHandler OnRhinoCommonResolve = null;
      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhinoCommonAssemblyName = "RhinoCommon";
        var assemblyName = new AssemblyName(args.Name).Name;

        if (assemblyName != rhinoCommonAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;

        var rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
        return Assembly.LoadFrom(Path.Combine(rhinoSystemDir, rhinoCommonAssemblyName + ".dll"));
      };
    }
    #endregion

    #region IExternalApplication Members
    RhinoCore rhinoCore;
    GH.PreviewServer grasshopperPreviewServer;

    public Result OnStartup(UIControlledApplication applicationUI)
    {
      ApplicationUI = applicationUI;

#if REVIT_2019
      MainWindowHandle = ApplicationUI.MainWindowHandle;
#else
      MainWindowHandle = Process.GetCurrentProcess().MainWindowHandle;
#endif

      // Load Rhino
      try
      {
        var schemeName = ApplicationUI.ControlledApplication.VersionName.Replace(' ', '-');
        rhinoCore = new RhinoCore(new string[] { $"/scheme={schemeName}", "/nosplash" }, WindowStyle.Hidden, MainWindowHandle);
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
        return Result.Failed;
      }

      // Reset document units
      UI.RhinoCommand.ResetDocumentUnits(Rhino.RhinoDoc.ActiveDoc);

      // Register UI on Revit
      {
        var ribbonPanel = ApplicationUI.CreateRibbonPanel("Rhinoceros");

        UI.RhinoCommand.CreateUI(ribbonPanel);
        UI.GrasshopperCommand.CreateUI(ribbonPanel);
        UI.PythonCommand.CreateUI(ribbonPanel);
        ribbonPanel.AddSeparator();
        Samples.Sample1.CreateUI(ribbonPanel);
        Samples.Sample4.CreateUI(ribbonPanel);
        Samples.Sample6.CreateUI(ribbonPanel);
        ribbonPanel.AddSeparator();
        UI.HelpCommand.CreateUI(ribbonPanel);
      }

      // Register some events
      ApplicationUI.Idling += OnIdle;
      ApplicationUI.ControlledApplication.DocumentChanged += OnDocumentChanged;

      // Register GrasshopperPreviewServer
      grasshopperPreviewServer = new GH.PreviewServer();
      grasshopperPreviewServer.Register();

      return Result.Succeeded;
    }

    public Result OnShutdown(UIControlledApplication applicationUI)
    {
      // Unregister GrasshopperPreviewServer
      grasshopperPreviewServer?.Unregister();
      grasshopperPreviewServer = null;

      // Unregister some events
      ApplicationUI.ControlledApplication.DocumentChanged -= OnDocumentChanged;
      ApplicationUI.Idling -= OnIdle;

      // Unload Rhino
      try
      {
        rhinoCore.Dispose();
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
        return Result.Failed;
      }

      ApplicationUI = null;
      return Result.Succeeded;
    }

    static bool pendingRefreshActiveView = false;
    public static void RefreshActiveView() { pendingRefreshActiveView = true; }

    public static bool Committing = false;
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

      // Load all the gha installed under the %APPDATA%\Grasshopper\Libraries-Autodesk-Revit-20XX
      var schemeName = ApplicationUI.ControlledApplication.VersionName.Replace(' ', '-');
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

    static bool LoadedAsGHA = false;
    void OnIdle(object sender, IdlingEventArgs args)
    {
      // 1. Do Rhino pending OnIdle tasks
      if (rhinoCore.OnIdle())
      {
        args.SetRaiseWithoutDelay();
        return;
      }

      // Load this assembly as a Grasshopper assembly
      if (!LoadedAsGHA && PlugIn.GetPlugInInfo(new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF)).IsLoaded)
        LoadedAsGHA = LoadGrasshopperComponents();

      // Document dependant tasks need a document
      ActiveUIApplication = (sender as UIApplication);
      if (ActiveDBDocument != null)
      {
        // 1. Do all document read actions
        if (ProcessReadActions())
        {
          args.SetRaiseWithoutDelay();
          return;
        }

        // 2. Do all document write actions
        if (!ActiveDBDocument.IsReadOnly)
          ProcessWriteActions();

        // 3. Refresh Active View if necesary
        bool regenComplete = DirectContext3DServer.RegenComplete();
        if (pendingRefreshActiveView || !regenComplete || GH.PreviewServer.PreviewChanged())
        {
          pendingRefreshActiveView = false;

          var RefreshTime = new Stopwatch();
          RefreshTime.Start();
          ActiveUIApplication.ActiveUIDocument.RefreshActiveView();
          RefreshTime.Stop();
          DirectContext3DServer.RegenThreshold = Math.Min(RefreshTime.ElapsedMilliseconds, 200);
        }

        if (!regenComplete)
          args.SetRaiseWithoutDelay();
      }
    }

    private void OnDocumentChanged(object sender, DocumentChangedEventArgs e)
    {
      if (Committing)
        return;

      var document = e.GetDocument();
      if (!document.Equals(ActiveDBDocument))
        return;

      CancelReadActions();

      var added    = e.GetAddedElementIds();
      var deleted  = e.GetDeletedElementIds();
      var modified = e.GetModifiedElementIds();

      if (added.Count > 0 || deleted.Count > 0 || modified.Count > 0)
      {
        var materialsChanged = modified.Select((x) => document.GetElement(x)).OfType<Material>().Any();

        foreach (GH_Document definition in Grasshopper.Instances.DocumentServer)
        {
          foreach (var obj in definition.Objects)
          {
            if (obj is IGH_Param param)
            {
              if (param.SourceCount > 0)
                continue;

              if (param.Phase == GH_SolutionPhase.Blank)
                continue;

              if (obj is GH.Parameters.IGH_PersistentGeometryParam persistent)
              {
                if (persistent.NeedsToBeExpired(document, added, deleted, modified))
                  param.ExpireSolution(false);
              }
            }
            else if (obj is IGH_Component component)
            {
              if (component is GH.Components.DocumentElements)
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

                  if (inputParam is GH.Parameters.IGH_PersistentGeometryParam persistent)
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
                  if (outParam is GH.Parameters.IGH_PersistentGeometryParam persistent)
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
    #endregion

    #region Bake Recipe
    public static void BakeGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries, BuiltInCategory categoryToBakeInto = BuiltInCategory.OST_GenericModel)
    {
      if (categoryToBakeInto == BuiltInCategory.INVALID)
        return;

      EnqueueAction
      (
        (doc) =>
        {
          foreach (var geometryToBake in geometries.ToHost())
          {
            if (geometryToBake == null)
              continue;

            BakeGeometry(doc, geometryToBake, categoryToBakeInto);
          }
        }
      );
    }

    static partial void TraceGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries);
#if DEBUG
    static partial void TraceGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries)
    {
      EnqueueAction
      (
        (doc) =>
        {
          using (var attributes = Convert.GraphicAttributes.Push())
          {
            using (var collector = new FilteredElementCollector(ActiveDBDocument))
            {
              var materials = collector.OfClass(typeof(Material)).Cast<Material>();
              attributes.MaterialId = (materials.Where((x) => x.Name == "Debug").FirstOrDefault()?.Id) ?? ElementId.InvalidElementId;
            }

            foreach (var geometryToBake in geometries.ToHost())
            {
              if (geometryToBake == null)
                continue;

              BakeGeometry(doc, geometryToBake, BuiltInCategory.OST_GenericModel);
            }
          }
        }
      );
    }
#endif

    static void BakeGeometry(Document doc, IEnumerable<GeometryObject> geometryToBake, BuiltInCategory categoryToBakeInto)
    {
      try
      {
        var geometryList = new List<GeometryObject>();

        // DirectShape only accepts those types and no nulls
        foreach (var g in geometryToBake)
        {
          switch (g)
          {
            case Point p: geometryList.Add(p); break;
            case Curve c: geometryList.Add(c); break;
            case Solid s: geometryList.Add(s); break;
            case Mesh m: geometryList.Add(m); break;
          }
        }

        if (geometryList.Count > 0)
        {
          var category = new ElementId(categoryToBakeInto);
          if (!DirectShape.IsValidCategoryId(category, doc))
            category = new ElementId(BuiltInCategory.OST_GenericModel);

          var ds = DirectShape.CreateElement(doc, category);
          ds.SetShape(geometryList);
        }
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
      }
    }
    #endregion

    #region Document Actions
    private static Queue<Action<Document>> docWriteActions = new Queue<Action<Document>>();
    public static void EnqueueAction(Action<Document> action)
    {
      lock (docWriteActions)
        docWriteActions.Enqueue(action);
    }

    void ProcessWriteActions()
    {
      lock (docWriteActions)
      {
        if (docWriteActions.Count > 0)
        {
          using (var trans = new Transaction(ActiveDBDocument))
          {
            try
            {
              if (trans.Start("RhinoInside") == TransactionStatus.Started)
              {
                while (docWriteActions.Count > 0)
                  docWriteActions.Dequeue().Invoke(ActiveDBDocument);

                Committing = true;
                var options = trans.GetFailureHandlingOptions();
                trans.Commit(options.SetDelayedMiniWarnings(true).SetForcedModalHandling(false).SetFailuresPreprocessor(new FailuresPreprocessor()));
                Committing = false;

                foreach (GH_Document definition in Grasshopper.Instances.DocumentServer)
                {
                  if (definition.Enabled)
                    definition.NewSolution(false);
                }
              }
            }
            catch (Exception e)
            {
              Debug.Fail(e.Source, e.Message);

              if (trans.HasStarted())
                trans.RollBack();
            }
            finally
            {
              docWriteActions.Clear();
            }
          }
        }
      }
    }

    static Queue<Action<Document, bool>> docReadActions = new Queue<Action<Document, bool>>();
    public static void EnqueueReadAction(Action<Document, bool> action)
    {
      lock (docReadActions)
        docReadActions.Enqueue(action);
    }

    public static void CancelReadActions() => ProcessReadActions(true);
    static bool ProcessReadActions(bool cancel = false)
    {
      lock (docReadActions)
      {
        if (docReadActions.Count > 0)
        {
          var stopWatch = new Stopwatch();

          while (docReadActions.Count > 0)
          {
            // We will do as much work as possible in 150 ms on each OnIdle event
            if (!cancel && stopWatch.ElapsedMilliseconds > 150)
              return true; // there is pending work to do

            stopWatch.Start();
            try { docReadActions.Dequeue().Invoke(ActiveDBDocument, cancel); }
            catch (Exception e) { Debug.Fail(e.Source, e.Message); }
            stopWatch.Stop();
          }
        }
      }

      // there is no more work to do
      return false;
    }
    #endregion

    #region Public Properties
    public static IntPtr MainWindowHandle { get; private set; }
    public static Autodesk.Revit.UI.UIControlledApplication ApplicationUI { get; private set; }
    public static Autodesk.Revit.UI.UIApplication ActiveUIApplication { get; private set; }
    public static Autodesk.Revit.ApplicationServices.Application Services => ActiveUIApplication?.Application;

    public static Autodesk.Revit.UI.UIDocument ActiveUIDocument => ActiveUIApplication?.ActiveUIDocument;
    public static Autodesk.Revit.DB.Document   ActiveDBDocument => ActiveUIDocument?.Document;

    private const double AbsoluteTolerance = (1.0 / 12.0) / 16.0; // 1/16 inch in feet
    public static double AngleTolerance => Services != null ? Services.AngleTolerance : Math.PI / 180.0; // in rad
    public static double ShortCurveTolerance => Services != null ? Services.ShortCurveTolerance : AbsoluteTolerance / 2.0;
    public static double VertexTolerance => Services != null ? Services.VertexTolerance : AbsoluteTolerance / 10.0;
    public const Rhino.UnitSystem ModelUnitSystem = Rhino.UnitSystem.Feet; // Always feet
    public static double ModelUnits => RhinoDoc.ActiveDoc == null ? double.NaN : RhinoMath.UnitScale(ModelUnitSystem, RhinoDoc.ActiveDoc.ModelUnitSystem); // 1 feet in Rhino units
    #endregion
  }

  public static class Operator
  {
    enum CompareMethod
    {
      Nothing,
      Equals,
      StartsWith, // >
      EndsWith,   // <
      Contains,   // ?
      Wildcard,   // :
      Regex,      // ;
    }

    static CompareMethod CompareMethodFromPattern(ref string pattern, ref bool not)
    {
      if (string.IsNullOrEmpty(pattern))
        return CompareMethod.Nothing;

      switch (pattern[0])
      {
        case '~': not = !not; pattern = pattern.Substring(1); return CompareMethodFromPattern(ref pattern, ref not);
        case '>':             pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.StartsWith;
        case '<':             pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.EndsWith;
        case '?':             pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.Contains;
        case ':':             pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.Wildcard;
        case ';':             pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.Regex;
        default: return CompareMethod.Equals;
      }
    }

    public static bool IsSymbolNameLike(this string source, string pattern)
    {
      if (pattern.Length == 0)
        return false;

      bool not = false;
      switch (CompareMethodFromPattern(ref pattern, ref not))
      {
        case CompareMethod.Nothing:     return not ^ false;
        case CompareMethod.Equals:      return not ^ string.Equals(source, pattern, StringComparison.OrdinalIgnoreCase);
        case CompareMethod.StartsWith:  return not ^ source.StartsWith(pattern, StringComparison.OrdinalIgnoreCase);
        case CompareMethod.EndsWith:    return not ^ source.EndsWith(pattern, StringComparison.OrdinalIgnoreCase);
        case CompareMethod.Contains:    return not ^ (source.IndexOf(pattern, StringComparison.OrdinalIgnoreCase) >= 0);
        case CompareMethod.Wildcard:    return not ^ Microsoft.VisualBasic.CompilerServices.LikeOperator.LikeString(source, pattern, Microsoft.VisualBasic.CompareMethod.Text);
        case CompareMethod.Regex:       var regex = new System.Text.RegularExpressions.Regex(pattern); return not ^ regex.IsMatch(source);
      }

      return false;
    }
  }
}
