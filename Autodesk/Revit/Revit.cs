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
using Autodesk.Revit.UI;
using Autodesk.Revit.UI.Events;
using Autodesk.Revit.ApplicationServices;

using Rhino;
using Rhino.Runtime.InProcess;

namespace RhinoInside.Revit
{
    //These are "attributes", not sure what that means yet
    [Autodesk.Revit.Attributes.Transaction(Autodesk.Revit.Attributes.TransactionMode.Manual)]
    [Autodesk.Revit.Attributes.Regeneration(Autodesk.Revit.Attributes.RegenerationOption.Manual)]
    [Autodesk.Revit.Attributes.Journaling(Autodesk.Revit.Attributes.JournalingMode.NoCommandData)]


    public class Revit : IExternalApplication
    {
        // Revit static constructor
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

                string rhinoSystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
                return Assembly.LoadFrom(Path.Combine(rhinoSystemDir, rhinoCommonAssemblyName + ".dll"));
            };
        }
     
        #region IExternalApplication Members

        internal static BitmapImage RhinoLogo = LoadImage("RhinoInside.Resources.Rhino.png");

        internal static BitmapImage GrasshopperLogo = LoadImage("RhinoInside.Resources.Grasshopper.png");

        private RhinoCore rhinoCore;

        public Autodesk.Revit.UI.Result OnStartup(UIControlledApplication applicationUI)
        {
            ApplicationUI = applicationUI;


            //this is actually testing the release configuration
            #if REVIT_2019
            MainWindowHandle = ApplicationUI.MainWindowHandle;
            #else
            MainWindowHandle = Process.GetCurrentProcess().MainWindowHandle;
            #endif


            // Load Rhino
            try
            {
                var schemeName = ApplicationUI.ControlledApplication.VersionName.Replace(' ', '-');
                rhinoCore = new RhinoCore(new string[] { $"/scheme={schemeName}", "/nosplash" }, WindowStyle.Normal, MainWindowHandle);
            }
            catch (Exception e)
            {
                Debug.Fail(e.Source, e.Message);
                return Autodesk.Revit.UI.Result.Failed;
            }


            // Register UI
            {
                RibbonPanel ribbonPanel = ApplicationUI.CreateRibbonPanel("Rhinoceros");

                Sample1.CreateUI(ribbonPanel);
                Sample4.CreateUI(ribbonPanel);
            }


            // Add an Idling event handler to notify Rhino when the process is idle
            ApplicationUI.Idling += new EventHandler<IdlingEventArgs>(OnIdle);

            return Autodesk.Revit.UI.Result.Succeeded;
        }

        public Autodesk.Revit.UI.Result OnShutdown(UIControlledApplication applicationUI)
        {
            // Remove the Idling event handler
            ApplicationUI.Idling -= new EventHandler<IdlingEventArgs>(OnIdle);

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

        public void OnIdle(object sender, IdlingEventArgs args)
        {
            // 1. Do Rhino pending OnIdle tasks
            if (rhinoCore.OnIdle())
            {
                args.SetRaiseWithoutDelay();
                return;
            }

            // Document dependant tasks need a document
            var doc = (sender as UIApplication)?.ActiveUIDocument?.Document;
            if (doc == null)
                return;

            // 2. Do all BakeGeometry pending tasks
            //lock statement stops other threads from making modifications to the passed object (bakeQueue) until this statement is done
            lock (bakeRecipeQueue)
            {
                if (bakeRecipeQueue.Count > 0)
                {
                    using (var trans = new Transaction(doc))
                    {
                        if (trans.Start("BakeGeometry") == TransactionStatus.Started)
                        {

                            while (bakeRecipeQueue.Count > 0)
                            {
                                //dequeue returns the first item on the list, and removes that item from that list
                                //var geometryList = bakeQueueGeom.Dequeue(); //OLD - KEEP FOR REFERENCE

                                BakeRecipe recipe = bakeRecipeQueue.Dequeue();

                                string revitCategoryType = recipe.categoryToBakeInto;
                                ElementId genericModelId;
                                switch (revitCategoryType)
                                {
                                    case "OST_Columns":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Columns);
                                        break;
                                    case "OST_CurtainWallPanels":
                                        genericModelId = new ElementId(BuiltInCategory.OST_CurtainWallPanels);
                                        break;
                                    case "OST_DataDevices":
                                        genericModelId = new ElementId(BuiltInCategory.OST_DataDevices);
                                        break;
                                    case "OST_Furniture":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Furniture);
                                        break;
                                    case "OST_Floors":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Floors);
                                        break;
                                    case "OST_Massing":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Massing);
                                        break;
                                    case "OST_Railings":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Railings);
                                        break;
                                    case "OST_Stairs":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Stairs);
                                        break;
                                    case "OST_Topography":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Topography);
                                        break;
                                    case "OST_Walls":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Walls);
                                        break;
                                    case "OST_Windows":
                                        genericModelId = new ElementId(BuiltInCategory.OST_Windows);
                                        break;
                                    default:
                                        genericModelId = new ElementId(BuiltInCategory.OST_GenericModel);
                                        break;
                                }



                                var geometryList = recipe.geometryToBake;
                                if (geometryList != null)
                                {
                                    try
                                    {
                                        var genericModelList = new List<GeometryObject>();

                                        // DirectShape only accepts those types and no nulls
                                        foreach (var g in geometryList)
                                        {
                                            switch (g)
                                            {
                                                case Point p: genericModelList.Add(p); break;
                                                case Curve c: genericModelList.Add(c); break;
                                                case Solid s: genericModelList.Add(s); break;
                                                case Mesh m: genericModelList.Add(m); break;
                                            }
                                        }

                                        if (genericModelList.Count > 0)
                                        {
                                            var ds = DirectShape.CreateElement(doc, genericModelId);
                                            ds.SetShape(genericModelList);
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
                    using (var trans = new Transaction(doc))
                    {
                        var action = documentActions.Peek();
                        if (trans.Start(action.GetMethodInfo().Name) == TransactionStatus.Started)
                        {
                            try
                            {
                                documentActions.Dequeue().Invoke(doc);
                                trans.Commit();
                            }
                            catch (Exception e)
                            {
                                Debug.Fail(e.Source, e.Message);
                                trans.RollBack();
                            }
                        }
                    }
                }

                if (documentActions.Count > 0)
                    args.SetRaiseWithoutDelay();
            }
        }

        #endregion
        //the bakeQueue is a private property of the class
        //its type is "Queue" which holds lists of geometry objects (for baking)
        //Queue is a system class
        private static Queue<BakeRecipe> bakeRecipeQueue = new Queue<BakeRecipe>();

        // private static Queue<IList<GeometryObject>> bakeQueueGeom = new Queue<IList<GeometryObject>>(); //OLD - keep for reference


        //updated - done
        public static void BakeGeometry(IEnumerable<Rhino.Geometry.GeometryBase> geometries, string revitGenericCategory)
        {
            lock (bakeRecipeQueue)
            {
                foreach (var list in geometries.ToHost())
                {
                    BakeRecipe recipe = new BakeRecipe(list, revitGenericCategory);
                    bakeRecipeQueue.Enqueue(recipe);
                }
            }
        }


        //no need to update
        private static Queue<Action<Document>> documentActions = new Queue<Action<Document>>();


        //no need to update
        public static void EnqueueAction(Action<Document> action)
        {
            lock (documentActions)
                documentActions.Enqueue(action);
        }


        //No need to mess with anything in here, they are just helper methods related to scaling and such
        #region Public Methods
        public static IntPtr MainWindowHandle { get; private set; }
        public static UIControlledApplication ApplicationUI { get; private set; }
        public const double ModelAbsoluteTolerance = (1.0 / 12.0) / 16.0; // 1/16 inch in feet
        public const double ModelAbsolutePlanarTolerance = Revit.ModelAbsoluteTolerance / 10; // in feet
        public const Rhino.UnitSystem ModelUnitSystem = Rhino.UnitSystem.Feet; // Always feet
        public static double RhinoToRevitModelScaleFactor => RhinoDoc.ActiveDoc == null ? Double.NaN : RhinoMath.UnitScale(RhinoDoc.ActiveDoc.ModelUnitSystem, Revit.ModelUnitSystem);
        internal static double RhinoModelAbsoluteTolerance => ModelAbsoluteTolerance / RhinoToRevitModelScaleFactor; // in Rhino model units
        #endregion

        //No need to mess with anything in here, its just providing an icon
        #region Private Methods
        static private BitmapImage LoadImage(string name)
        {
            var bmi = new BitmapImage();
            bmi.BeginInit();
            bmi.StreamSource = Assembly.GetExecutingAssembly().GetManifestResourceStream(name);
            bmi.EndInit();
            return bmi;
        }
        #endregion
    }



    public class BakeRecipe
    {
        public IList<GeometryObject> geometryToBake;
        public string categoryToBakeInto;

        public BakeRecipe(IList<GeometryObject> geometryToBake, string categoryToBakeInto)
        {
            this.geometryToBake = geometryToBake;
            this.categoryToBakeInto = categoryToBakeInto;
        }

    }

}
