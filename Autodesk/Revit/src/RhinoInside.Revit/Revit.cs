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

using Grasshopper;
using Grasshopper.Kernel;

namespace RhinoInside.Revit
{
  public static partial class Revit
  {
    internal static Result OnStartup(UIControlledApplication applicationUI)
    {
      if (MainWindowHandle == IntPtr.Zero)
      {
#if REVIT_2019
        MainWindowHandle = applicationUI.MainWindowHandle;
#else
        MainWindowHandle = Process.GetCurrentProcess().MainWindowHandle;
#endif

        var result = Rhinoceros.Startup();
        if (result != Result.Succeeded)
        {
          MainWindowHandle = IntPtr.Zero;
          return result;
        }

        // Register some events
        applicationUI.Idling += OnIdle;
        applicationUI.ControlledApplication.DocumentChanged += OnDocumentChanged;
      }

      return Result.Succeeded;
    }

    internal static Result OnShutdown(UIControlledApplication applicationUI)
    {
      if (MainWindowHandle != IntPtr.Zero)
      {
        // Unregister some events
        applicationUI.ControlledApplication.DocumentChanged -= OnDocumentChanged;
        applicationUI.Idling -= OnIdle;

        Rhinoceros.Shutdown();

        MainWindowHandle = IntPtr.Zero;
      }

      return Result.Succeeded;
    }

    static bool isRefreshActiveViewPending = false;
    public static void RefreshActiveView() => isRefreshActiveViewPending = true;

    static void OnIdle(object sender, IdlingEventArgs args) => ActiveUIApplication = (sender as UIApplication);

    public static event EventHandler<DocumentChangedEventArgs> DocumentChanged;
    private static void OnDocumentChanged(object sender, DocumentChangedEventArgs args)
    {
      if (isCommitting)
        return;

      var document = args.GetDocument();
      if (!document.Equals(ActiveDBDocument))
        return;

      CancelReadActions();

      DocumentChanged(sender, args);
    }

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

    #region Actions
    static bool isCommitting = false;
    internal static bool ProcessIdleActions()
    {
      bool pendingIdleActions = false;

      // Document dependant tasks need a document
      if (ActiveDBDocument != null)
      {
        // 1. Do all document read actions
        if (ProcessReadActions())
          pendingIdleActions = true;

        // 2. Do all document write actions
        if (!ActiveDBDocument.IsReadOnly)
          ProcessWriteActions();

        // 3. Refresh Active View if necesary
        bool regenComplete = DirectContext3DServer.RegenComplete();
        if (isRefreshActiveViewPending || !regenComplete || GH.PreviewServer.PreviewChanged())
        {
          isRefreshActiveViewPending = false;

          var RefreshTime = new Stopwatch();
          RefreshTime.Start();
          ActiveUIApplication.ActiveUIDocument.RefreshActiveView();
          RefreshTime.Stop();
          DirectContext3DServer.RegenThreshold = Math.Max(RefreshTime.ElapsedMilliseconds / 3, 100);
        }

        if (!regenComplete)
          pendingIdleActions = true;
      }

      return pendingIdleActions;
    }

    private static Queue<Action<Document>> docWriteActions = new Queue<Action<Document>>();
    public static void EnqueueAction(Action<Document> action)
    {
      lock (docWriteActions)
        docWriteActions.Enqueue(action);
    }

    static void ProcessWriteActions()
    {
      lock (docWriteActions)
      {
        if (docWriteActions.Count > 0)
        {
          using (var trans = new Transaction(ActiveDBDocument))
          {
            try
            {
              isCommitting = true;

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
                  foreach (GH_Document definition in Instances.DocumentServer)
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
              isCommitting = false;
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

#if REVIT_2019
    public static string CurrentUsersDataFolderPath => ApplicationUI.ControlledApplication.CurrentUsersDataFolderPath;
#else
    public static string CurrentUsersDataFolderPath => Path.Combine
    (
      Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
      "Autodesk",
      "Revit",
      ApplicationUI.ControlledApplication.VersionName
    );
#endif

    public static Autodesk.Revit.UI.UIControlledApplication ApplicationUI => Addin.ApplicationUI;
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
