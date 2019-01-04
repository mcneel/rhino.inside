using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Media.Imaging;

using Autodesk;
using Autodesk.Revit;
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
  public class Revit : IExternalApplication
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
    private RhinoCore rhinoCore;

    public Autodesk.Revit.UI.Result OnStartup(UIControlledApplication applicationUI)
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
        return Autodesk.Revit.UI.Result.Failed;
      }

      // Register UI on Revit
      {
        var ribbonPanel = ApplicationUI.CreateRibbonPanel("Rhinoceros");

        UI.RhinoCommand.CreateUI(ribbonPanel);
        UI.GrasshopperCommand.CreateUI(ribbonPanel);
        ribbonPanel.AddSeparator();
        Sample1.CreateUI(ribbonPanel);
        Sample4.CreateUI(ribbonPanel);
        ribbonPanel.AddSeparator();
        UI.APIDocsCommand.CreateUI(ribbonPanel);
      }

      // Register some events
      ApplicationUI.Idling += OnIdle;
      ApplicationUI.ControlledApplication.DocumentChanged += OnDocumentChanged;

      return Autodesk.Revit.UI.Result.Succeeded;
    }

    public Autodesk.Revit.UI.Result OnShutdown(UIControlledApplication applicationUI)
    {
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
        return Autodesk.Revit.UI.Result.Failed;
      }

      ApplicationUI = null;
      return Autodesk.Revit.UI.Result.Succeeded;
    }

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
        new object[] { new Grasshopper.Kernel.GH_ExternalFile(Assembly.GetExecutingAssembly().Location), false }
      );

      Instances.Settings.SetValue("Assemblies:COFF", bCoff);

      if(rc)
        Grasshopper.Kernel.GH_ComponentServer.UpdateRibbonUI();

      return rc;
    }
    static bool LoadedAsGHA = false;
    public void OnIdle(object sender, IdlingEventArgs args)
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
        // 2. Do all BakeGeometry pending tasks
        lock (bakeRecipeQueue)
        {
          if (bakeRecipeQueue.Count > 0)
          {
            using (var trans = new Transaction(ActiveDBDocument))
            {
              if (trans.Start("BakeGeometry") == TransactionStatus.Started)
              {
                while (bakeRecipeQueue.Count > 0)
                {
                  var recipe = bakeRecipeQueue.Dequeue();

                  if (recipe.geometryToBake != null && recipe.categoryToBakeInto != BuiltInCategory.INVALID)
                  {
                    try
                    {
                      var geometryList = new List<GeometryObject>();

                      // DirectShape only accepts those types and no nulls
                      foreach (var g in recipe.geometryToBake)
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
                        var ds = DirectShape.CreateElement(ActiveDBDocument, new ElementId(recipe.categoryToBakeInto));
                        ds.SetShape(geometryList);
                      }
                    }
                    catch (Exception e)
                    {
                      Debug.Fail(e.Source, e.Message);
                    }
                  }
                }
              }

              trans.Commit();
            }
          }
        }

        // 3. Do all document actions
        lock (documentActions)
        {
          if (documentActions.Count > 0)
          {
            using (var trans = new Transaction(ActiveDBDocument))
            {
              try
              {
                if (trans.Start("RhinoInside") == TransactionStatus.Started)
                {
                  while (documentActions.Count > 0)
                    documentActions.Dequeue().Invoke(ActiveDBDocument);

                  Committing = true;
                  trans.Commit();
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
                documentActions.Clear();
              }
            }
          }
        }
      }
    }
    private void OnDocumentChanged(object sender, DocumentChangedEventArgs e)
    {
      if (Committing)
        return;

      if (!ActiveDBDocument.Equals(e.GetDocument()))
        return;

      foreach (GH_Document definition in Grasshopper.Instances.DocumentServer)
      {
        foreach (var obj in definition.Objects)
        {
          if (obj is RhinoInside.Revit.GH.Parameters.Element element)
          {
            if (element.SourceCount > 0)
              continue;

            if (element.Phase == GH_SolutionPhase.Blank)
              continue;

            element.ExpireSolution(false);
          }
          else if (obj is GH_Component component)
          {
            foreach (var param in component.Params.Output)
            {
              if (param is RhinoInside.Revit.GH.Parameters.Element outElement)
              {
                foreach (var goo in param.VolatileData.AllData(true))
                {
                  if (goo is IGH_PreviewMeshData previewMeshData)
                    previewMeshData.DestroyPreviewMeshes();
                }

                foreach (var r in param.Recipients)
                  r.ExpireSolution(false);
              }
            }
          }
        }

        if (definition.Enabled)
          definition.NewSolution(false);
      }
    }

    #endregion

    #region Bake Recipe
    class BakeRecipe
    {
      public IList<GeometryObject> geometryToBake;
      public BuiltInCategory categoryToBakeInto;

      public BakeRecipe(IList<GeometryObject> geometryToBake, BuiltInCategory categoryToBakeInto)
      {
        this.geometryToBake = geometryToBake;
        this.categoryToBakeInto = categoryToBakeInto;
      }
    }

    private static Queue<BakeRecipe> bakeRecipeQueue = new Queue<BakeRecipe>();
    public static void BakeGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries, BuiltInCategory builtInCategory = BuiltInCategory.OST_GenericModel)
    {
      lock (bakeRecipeQueue)
      {
        foreach (var list in geometries.ToHost())
          bakeRecipeQueue.Enqueue(new BakeRecipe(list, builtInCategory));
      }
    }
    #endregion

    #region Document Actions
    private static Queue<Action<Document>> documentActions = new Queue<Action<Document>>();
    public static void EnqueueAction(Action<Document> action)
    {
      lock (documentActions)
        documentActions.Enqueue(action);
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
}
