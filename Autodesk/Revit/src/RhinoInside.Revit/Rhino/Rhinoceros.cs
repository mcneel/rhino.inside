using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Autodesk.Revit.DB;
using Autodesk.Revit.DB.Events;
using Autodesk.Revit.UI;
using Autodesk.Revit.UI.Events;

using Rhino;
using Rhino.Input;
using Rhino.PlugIns;
using Rhino.Runtime.InProcess;

namespace RhinoInside
{
  #region Guest
  [AttributeUsage(AttributeTargets.Class, AllowMultiple = true, Inherited = false)]
  public class GuestPlugInIdAttribute : Attribute
  {
    public readonly Guid PlugInId;
    public GuestPlugInIdAttribute(string plugInId) => PlugInId = Guid.Parse(plugInId);
  }

  public interface IGuest
  {
    string Name { get; }

    LoadReturnCode OnCheckIn(ref string complainMessage);
    void OnCheckOut();
  }
  #endregion
}

namespace RhinoInside.Revit
{
  public static class Rhinoceros
  {
    #region Revit Interface
    static RhinoCore core;
    public static string SchemeName = $"Inside-Revit-{Revit.ApplicationUI.ControlledApplication.VersionNumber}";

    internal static Result Startup()
    {
      if (core == null)
      {
        // Load RhinoCore
        try
        {
          core = new RhinoCore(new string[] { $"/scheme={SchemeName}", "/nosplash" }, WindowStyle.Hidden, Revit.MainWindowHandle);
        }
        catch (Exception /*e*/)
        {
          //Debug.Fail(e.Source, e.Message);
          return Result.Failed;
        }

        // Look for Guests
        guests = Assembly.GetCallingAssembly().GetTypes().
          Where(x => typeof(IGuest).IsAssignableFrom(x)).
          Where(x => !x.IsInterface).
          Select(x => new GuestInfo(x)).
          ToList();

        Revit.ApplicationUI.ApplicationClosing += OnApplicationClosing;
        RhinoDoc.NewDocument += OnNewDocument;
        Rhino.Commands.Command.BeginCommand += BeginCommand;
        Rhino.Commands.Command.EndCommand += EndCommand;
        RhinoApp.MainLoop += MainLoop;
        RhinoApp.Idle += OnIdle;
        timer.Tick += Timer_Tick;

        // Reset document units
        UpdateDocumentUnits(RhinoDoc.ActiveDoc);

        CheckInGuests();
      }

      UpdateDocumentUnits(RhinoDoc.ActiveDoc, Revit.ActiveDBDocument);
      return Result.Succeeded;
    }

    internal static Result Shutdown()
    {
      if (core != null)
      {
        timer.Tick -= Timer_Tick;
        RhinoApp.Idle -= OnIdle;
        RhinoApp.MainLoop -= MainLoop;
        RhinoDoc.NewDocument -= OnNewDocument;
        Revit.ApplicationUI.ApplicationClosing -= OnApplicationClosing;

        // Unload Guests
        CheckOutGuests();

        // Unload RhinoCore
        try
        {
          core.Dispose();
          core = null;
        }
        catch (Exception /*e*/)
        {
          //Debug.Fail(e.Source, e.Message);
          return Result.Failed;
        }
      }

      return Result.Succeeded;
    }

    static bool idlePending = true;
    static bool Run()
    {
      if (idlePending)
        idlePending = core.DoIdle();

      var active = core.DoEvents();
      if (active)
        idlePending = true;

      return active;
    }

    internal static void OnApplicationClosing(object sender, ApplicationClosingEventArgs e)
    {
      //var doc = RhinoDoc.ActiveDoc;
      //if (doc?.Modified ?? false)
      //{
      //  string docTitle = doc.Name ?? "Untitled";
      //  switch (Eto.Forms.MessageBox.Show
      //  (
      //    "Save changes to " + docTitle + "?",
      //    RhinoApp.Name,
      //    e.Cancellable ? Eto.Forms.MessageBoxButtons.YesNoCancel : Eto.Forms.MessageBoxButtons.YesNo,
      //    Eto.Forms.MessageBoxType.Question
      //  ))
      //  {
      //    case Eto.Forms.DialogResult.Yes:
      //      var docFileName = doc.Path;
      //      if (docFileName == null)
      //      {
      //        using (var dialog = new Eto.Forms.SaveFileDialog())
      //        {
      //          dialog.FileName = docTitle;
      //          dialog.Filters.Add(new Eto.Forms.FileFilter("Rhino 3D Model", new string[] { "3dm" }));
      //          if (dialog.ShowDialog(MainWindow) != Eto.Forms.DialogResult.Ok)
      //            return /*Result.Cancelled*/;

      //          if (Path.HasExtension(dialog.FileName))
      //            docFileName = dialog.FileName;
      //          else
      //            docFileName = Path.ChangeExtension(dialog.FileName, dialog.CurrentFilter.Extensions[0]);
      //        }
      //      }

      //      doc.WriteFile(docFileName, new Rhino.FileIO.FileWriteOptions()); break;
      //    case Eto.Forms.DialogResult.No: break;
      //    case Eto.Forms.DialogResult.Cancel: e.Cancel(); return/* Result.Cancelled*/;
      //  }
      //}
    }
    #endregion

    #region Guests
    class GuestInfo
    {
      public readonly Type ClassType;
      public IGuest Guest;
      public LoadReturnCode LoadReturnCode;

      public GuestInfo(Type type) => ClassType = type;
    }
    static List<GuestInfo> guests;

    static void CheckInGuests()
    {
      foreach (var guestInfo in guests)
      {
        if (guestInfo.Guest != null)
          continue;

        bool load = true;
        foreach (var guestPlugIn in guestInfo.ClassType.GetCustomAttributes(typeof(GuestPlugInIdAttribute), false).Cast<GuestPlugInIdAttribute>())
          load |= PlugIn.GetPlugInInfo(guestPlugIn.PlugInId).IsLoaded;

        if (!load)
          continue;

        guestInfo.Guest = Activator.CreateInstance(guestInfo.ClassType) as IGuest;

        string complainMessage = string.Empty;
        try { guestInfo.LoadReturnCode = guestInfo.Guest.OnCheckIn(ref complainMessage); }
        catch (Exception e)
        {
          guestInfo.LoadReturnCode = LoadReturnCode.ErrorShowDialog;
          complainMessage = e.Message;
        }

        if (guestInfo.LoadReturnCode == LoadReturnCode.ErrorShowDialog)
        {
          using
          (
            var taskDialog = new TaskDialog(MethodBase.GetCurrentMethod().DeclaringType.FullName)
            {
              Title = guestInfo.Guest.Name,
#if REVIT_2018
              MainIcon = TaskDialogIcon.TaskDialogIconError,
#else
              MainIcon = TaskDialogIcon.TaskDialogIconWarning,
#endif
              TitleAutoPrefix = false,
              AllowCancellation = false,
              MainInstruction = $"{guestInfo.Guest.Name} failed to load",
              MainContent = complainMessage
            }
          )
          {
            taskDialog.Show();
          }
        }
      }
    }

    static void CheckOutGuests()
    {
      foreach (var guestInfo in Enumerable.Reverse(guests))
      {
        if (guestInfo.Guest == null)
          continue;

        if (guestInfo.LoadReturnCode == LoadReturnCode.Success)
          continue;

        try { guestInfo.Guest.OnCheckOut(); guestInfo.LoadReturnCode = LoadReturnCode.ErrorNoDialog; }
        catch (Exception) { }
      }
    }
    #endregion

    #region Rhino Interface
    [DllImport("USER32", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool ShowOwnedPopups(IntPtr hWnd, [MarshalAs(UnmanagedType.Bool)] bool fShow);
    public static bool ShowOwnedPopups(bool fShow) => ShowOwnedPopups(RhinoApp.MainWindowHandle(), fShow);

    [DllImport("USER32", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool EnableWindow(IntPtr hWnd, [MarshalAs(UnmanagedType.Bool)] bool bEnable);

    [DllImport("USER32", SetLastError = true)]
    static extern IntPtr GetWindow(IntPtr hWnd, int uCmd);
    static IntPtr GetEnabledPopup() => GetWindow(RhinoApp.MainWindowHandle(), 6 /*GW_ENABLEDPOPUP*/);

    [DllImport("USER32", SetLastError = true)]
    static extern IntPtr SetActiveWindow(IntPtr hWnd);

    [DllImport("USER32", SetLastError = true)]
    static extern IntPtr BringWindowToTop(IntPtr hWnd);


    public class PauseTimerScope : IDisposable
    {
      public PauseTimerScope() => timer.Stop();
      void IDisposable.Dispose() => timer.Start();
    }

    static System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer() { Interval = 100 };
    static void Timer_Tick(object sender, EventArgs e)
    {
      if (!IsRunning)
      {
        ShowOwnedPopups(false);
        Exposed = false;
      }
    }

    static Eto.Forms.Window MainWindow => Rhino.UI.RhinoEtoApp.MainWindow;
    public static bool Exposed
    {
      get => MainWindow.Visible && MainWindow.WindowState != Eto.Forms.WindowState.Minimized;
      set
      {
        if (value)
        {
          MainWindow.Visible = true;

          if (MainWindow.WindowState == Eto.Forms.WindowState.Minimized)
            MainWindow.WindowState = Eto.Forms.WindowState.Normal;
        }
        else
        {
          MainWindow.Visible = false;
        }
      }
    }

    class ExposureSnapshot
    {
      readonly bool Visible                      = MainWindow.Visible;
      readonly Eto.Forms.WindowState WindowState = MainWindow.WindowState;
      public void Restore()
      {
        MainWindow.WindowState = WindowState;
        MainWindow.Visible     = Visible;
      }
    }
    static ExposureSnapshot QuiescentExposure;

    static void BeginCommand(object sender, Rhino.Commands.CommandEventArgs e)
    {
      if (!Rhino.Commands.Command.InScriptRunnerCommand())
      {
        // Capture Rhino Main Window exposure to restore it when user ends picking
        try { QuiescentExposure = new ExposureSnapshot(); }
        catch (Exception) { }

        // Disable Revit Main Window while in Command
        if (Modal != null)
        {
          EnableWindow(Revit.MainWindowHandle, false);
          Modal.Enabled = false;
          Modal.Opacity = 0.3;
        }
      }
    }

    static void EndCommand(object sender, Rhino.Commands.CommandEventArgs e)
    {
      if (!Rhino.Commands.Command.InScriptRunnerCommand())
      {
        if (Modal != null)
        {
          Modal.Opacity = 0.1;
          Modal.Enabled = true;
          EnableWindow(Revit.MainWindowHandle, true);
        }

        if (MainWindow.WindowState != Eto.Forms.WindowState.Maximized)
        {
          // Restore Rhino Main Window exposure
          QuiescentExposure?.Restore();
          QuiescentExposure = null;
          RhinoApp.SetFocusToMainWindow();
        }
      }
    }

    static void MainLoop(object sender, EventArgs e)
    {
      if (!Rhino.Commands.Command.InScriptRunnerCommand())
      {
        // Keep Rhino window exposed to user while in a get operation
        if (RhinoGet.InGet(RhinoDoc.ActiveDoc))
        {
          // if there is no floating viewport visible...
          if (!RhinoDoc.ActiveDoc.Views.Where(x => x.Floating).Any())
          {
            if (!Exposed)
              Exposed = true;
          }
        }
      }
    }

    static void OnIdle(object sender, EventArgs e)
    {
      CheckInGuests();

      Revit.ProcessIdleActions();
    }

    static void OnNewDocument(object sender, DocumentEventArgs e)
    {
      // If a new document is created without template it is updated from Revit.ActiveDBDocument
      Debug.Assert(string.IsNullOrEmpty(e.Document.TemplateFileUsed));

      UpdateDocumentUnits(e.Document);
      UpdateDocumentUnits(e.Document, Revit.ActiveDBDocument);
    }

    internal static void UpdateDocumentUnits(RhinoDoc rhinoDoc, Document revitDoc = null)
    {
      bool docModified = rhinoDoc.Modified;
      try
      {
        if (revitDoc == null)
        {
          rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.None;
          rhinoDoc.ModelAbsoluteTolerance = Revit.VertexTolerance;
          rhinoDoc.ModelAngleToleranceRadians = Revit.AngleTolerance;
        }
        else if (rhinoDoc.ModelUnitSystem == Rhino.UnitSystem.None)
        {
          var units = revitDoc.GetUnits();
          var lengthFormatoptions = units.GetFormatOptions(UnitType.UT_Length);
          switch (lengthFormatoptions.DisplayUnits)
          {
            case DisplayUnitType.DUT_METERS: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Meters; break;
            case DisplayUnitType.DUT_METERS_CENTIMETERS: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Meters; break;
            case DisplayUnitType.DUT_DECIMETERS: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Decimeters; break;
            case DisplayUnitType.DUT_CENTIMETERS: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Centimeters; break;
            case DisplayUnitType.DUT_MILLIMETERS: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Millimeters; break;

            case DisplayUnitType.DUT_FRACTIONAL_INCHES: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Inches; break;
            case DisplayUnitType.DUT_DECIMAL_INCHES: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Inches; break;
            case DisplayUnitType.DUT_FEET_FRACTIONAL_INCHES: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Feet; break;
            case DisplayUnitType.DUT_DECIMAL_FEET: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.Feet; break;
            default: rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.None; break;
          }

          bool imperial = rhinoDoc.ModelUnitSystem == Rhino.UnitSystem.Feet || rhinoDoc.ModelUnitSystem == Rhino.UnitSystem.Inches;

          rhinoDoc.ModelAngleToleranceRadians = Revit.AngleTolerance;
          rhinoDoc.ModelDistanceDisplayPrecision = ((int) -Math.Log10(lengthFormatoptions.Accuracy)).Clamp(0, 7);
          rhinoDoc.ModelAbsoluteTolerance = Revit.VertexTolerance * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Feet, rhinoDoc.ModelUnitSystem);
          //switch (rhinoDoc.ModelUnitSystem)
          //{
          //  case Rhino.UnitSystem.None: break;
          //  case Rhino.UnitSystem.Feet:
          //  case Rhino.UnitSystem.Inches:
          //    newDoc.ModelAbsoluteTolerance = (1.0 / 160.0) * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Inches, newDoc.ModelUnitSystem);
          //    break;
          //  default:
          //    newDoc.ModelAbsoluteTolerance = 0.1 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Millimeters, newDoc.ModelUnitSystem);
          //    break;
          //}

          UpdateViewConstructionPlanesFrom(rhinoDoc, revitDoc);
        }
      }
      finally
      {
        rhinoDoc.Modified = docModified;
      }
    }

    static void UpdateViewConstructionPlanesFrom(RhinoDoc rhinoDoc, Document revitDoc)
    {
      if (!string.IsNullOrEmpty(rhinoDoc.TemplateFileUsed))
        return;

      if (rhinoDoc.IsCreating)
      {
        Revit.EnqueueAction(doc => UpdateViewConstructionPlanesFrom(rhinoDoc, doc));
        return;
      }

      bool imperial = rhinoDoc.ModelUnitSystem == Rhino.UnitSystem.Feet || rhinoDoc.ModelUnitSystem == Rhino.UnitSystem.Inches;

      var modelGridSpacing = imperial ?
      1.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Yards, rhinoDoc.ModelUnitSystem) :
      1.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Meters, rhinoDoc.ModelUnitSystem);

      var modelSnapSpacing = imperial ?
      1 / 16.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Inches, rhinoDoc.ModelUnitSystem) :
      1.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Millimeters, rhinoDoc.ModelUnitSystem);

      var modelThickLineFrequency = imperial ? 6 : 5;

      // Views
      {
        foreach (var view in rhinoDoc.Views)
        {
          var cplane = view.MainViewport.GetConstructionPlane();

          cplane.GridSpacing = modelGridSpacing;
          cplane.SnapSpacing = modelSnapSpacing;
          cplane.ThickLineFrequency = modelThickLineFrequency;

          view.MainViewport.SetConstructionPlane(cplane);

          var min = cplane.Plane.PointAt(-cplane.GridSpacing * cplane.GridLineCount, -cplane.GridSpacing * cplane.GridLineCount, 0.0);
          var max = cplane.Plane.PointAt(+cplane.GridSpacing * cplane.GridLineCount, +cplane.GridSpacing * cplane.GridLineCount, 0.0);
          var bbox = new Rhino.Geometry.BoundingBox(min, max);

          // Zoom to grid
          view.MainViewport.ZoomBoundingBox(bbox);

          // Adjust to extens in case There is anything in the viewports like Grasshopper previews.
          view.MainViewport.ZoomExtents();
        }
      }
    }


    class ModalForm : System.Windows.Forms.Form
    {
      public class RevitMainWindow : IWin32Window { IntPtr IWin32Window.Handle => Revit.MainWindowHandle; }
      static IWin32Window MainWidow = new RevitMainWindow();

      public ModalForm()
      {
        BackColor = System.Drawing.Color.White;
        Opacity = 0.1;
        Show(MainWidow);
      }

      protected override bool ShowWithoutActivation => true;
      protected override CreateParams CreateParams
      {
        get
        {
          var createParams = base.CreateParams;
          createParams.Style = 0x00000000;

          using (var mainWindowExtents = Revit.ActiveUIApplication.MainWindowExtents)
          {
            createParams.X = mainWindowExtents.Left;
            createParams.Y = mainWindowExtents.Top;
            createParams.Width = mainWindowExtents.Right - mainWindowExtents.Left;
            createParams.Height = mainWindowExtents.Bottom - mainWindowExtents.Top;
            createParams.Parent = Revit.MainWindowHandle;
          }

          return createParams;
        }
      }
    }


    // Visible in Rhino time
    static bool Visible = false;
    public static bool IsRunning { get; private set; }
    static ModalForm Modal;
    public static Result RunModal(bool exposeMainWindow = true, bool restorePopups = false)
    {
      using (Modal = new ModalForm())
      {
        try
        {
          timer.Stop();
          IsRunning = true;

          if (exposeMainWindow) Exposed = true;
          else if (restorePopups) Exposed = Visible || MainWindow.WindowState == Eto.Forms.WindowState.Minimized;

          if (restorePopups)
            ShowOwnedPopups(true);

          // Activate a Rhino window to keep the loop running
          var activePopup = GetEnabledPopup();
          if (activePopup == IntPtr.Zero)
          {
            if (!Exposed)
              return Result.Cancelled;

            RhinoApp.SetFocusToMainWindow();
          }
          else
          {
            BringWindowToTop(activePopup);
          }

          do
          {
            while (Run())
            {
              if (!Exposed && GetEnabledPopup() == IntPtr.Zero)
                break;
            }
          }
          // Keep window active while Maximized
          while (MainWindow.Visible && MainWindow.WindowState == Eto.Forms.WindowState.Maximized);

          return Result.Succeeded;
        }
        finally
        {
          Visible = Exposed;

          EnableWindow(Revit.MainWindowHandle, true);
          SetActiveWindow(Revit.MainWindowHandle);
          ShowOwnedPopups(false);
          Exposed = false;

          Modal = null;

          IsRunning = false;
          timer.Start();

          UI.CommandRhinoInside.ShowShortcutHelp();
        }
      }
    }

    public static Result RunCommandAbout()
    {
      using (new Rhinoceros.PauseTimerScope())
      {
        var docSerial = RhinoDoc.ActiveDoc.RuntimeSerialNumber;
        var result = RhinoApp.RunScript("!_About", false) ? Result.Succeeded : Result.Failed;

        if (result == Result.Succeeded && docSerial != RhinoDoc.ActiveDoc.RuntimeSerialNumber)
          return RunModal();

        return Result.Cancelled;
      }
    }
    #endregion
  }
}
