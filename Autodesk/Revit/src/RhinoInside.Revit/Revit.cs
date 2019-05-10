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
    GH.Addon grasshopperAddon;

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
        var schemeName = ApplicationUI.ControlledApplication.VersionName.Replace(' ', '_');
        rhinoCore = new RhinoCore(new string[] { $"/scheme={schemeName}", "/nosplash" }, WindowStyle.Hidden, MainWindowHandle);
      }
      catch (Exception e)
      {
        Debug.Fail(e.Source, e.Message);
        return Result.Failed;
      }

      // Reset document units
      UI.RhinoCommand.UpdateDocumentUnits(Rhino.RhinoDoc.ActiveDoc);

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

      // Initialice Grasshopper Addon
      grasshopperAddon = new GH.Addon();
      grasshopperAddon.OnStartup(applicationUI);

      return Result.Succeeded;
    }

    public Result OnShutdown(UIControlledApplication applicationUI)
    {
      // Shutdown Grasshopper Addon
      grasshopperAddon.OnShutdown(applicationUI);
      grasshopperAddon = null;

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

    void OnIdle(object sender, IdlingEventArgs args)
    {
      ActiveUIApplication = (sender as UIApplication);
      var mainWindowExtents = ActiveUIApplication.MainWindowExtents;
      MainWindowBounds = new System.Drawing.Rectangle(mainWindowExtents.Left, mainWindowExtents.Top, mainWindowExtents.Right - mainWindowExtents.Left, mainWindowExtents.Bottom - mainWindowExtents.Top);

      // 1. Do Rhino pending OnIdle tasks
      if (rhinoCore.DoIdle())
        args.SetRaiseWithoutDelay();

      // Document dependant tasks need a document
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

      grasshopperAddon.OnDocumentChanged(sender, e);
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
              Committing = true;

              if (trans.Start("RhinoInside") == TransactionStatus.Started)
              {
                while (docWriteActions.Count > 0)
                  docWriteActions.Dequeue().Invoke(ActiveDBDocument);

                var options = trans.GetFailureHandlingOptions();
                options = options.SetClearAfterRollback(true);
                options = options.SetDelayedMiniWarnings(true);
                options = options.SetForcedModalHandling(false);
                options = options.SetFailuresPreprocessor(new FailuresPreprocessor());
                var status = trans.Commit(options);

                if (status == TransactionStatus.Committed)
                {
                  foreach (GH_Document definition in Grasshopper.Instances.DocumentServer)
                  {
                    if (definition.Enabled)
                      definition.NewSolution(false);
                  }
                }
              }
            }
            catch (Exception e)
            {
              Debug.Fail(e.Source, e.Message);

              docWriteActions.Clear();

              if (trans.HasStarted())
                trans.RollBack();
            }
            finally
            {
              Committing = false;
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
    static string CallerFilePath([System.Runtime.CompilerServices.CallerFilePath] string CallerFilePath = "") => CallerFilePath;
    static public string SourceCodePath => Path.GetDirectoryName(CallerFilePath());

    public static Version Version => Assembly.GetExecutingAssembly().GetName().Version;
    public static DateTime BuildDate => new DateTime(2000, 1, 1).AddDays(Version.Build).AddSeconds(Version.Revision * 2);
    public static string DisplayVersion => $"{Version} ({BuildDate})";

    public static IntPtr MainWindowHandle { get; private set; }
    public static System.Drawing.Rectangle MainWindowBounds { get; private set; }

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
}
