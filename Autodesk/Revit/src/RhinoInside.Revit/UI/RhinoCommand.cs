using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;

namespace RhinoInside.Revit.UI
{
  [Transaction(TransactionMode.Manual)]
  [Regeneration(RegenerationOption.Manual)]
  class RhinoCommand : IExternalCommand
  {
    static RhinoCommand()
    {
      Rhino.RhinoDoc.NewDocument += RhinoDoc_NewDocument;
    }

    private static void RhinoDoc_NewDocument(object sender, Rhino.DocumentEventArgs e)
    {
      // If a new document is created without template it is updated from Revit.ActiveDBDocument
      System.Diagnostics.Debug.Assert(string.IsNullOrEmpty(e.Document.TemplateFileUsed));
      UpdateDocumentUnits(e.Document);
      UpdateDocumentUnits(e.Document, Revit.ActiveDBDocument);
    }

    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var thisAssembly = Assembly.GetExecutingAssembly();

      var buttonData = new PushButtonData
      (
        "cmdRhinoInside.Rhino", "Rhino",
        thisAssembly.Location,
        MethodBase.GetCurrentMethod().DeclaringType.FullName
      );

      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Toggle Rhino window visibility";
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Rhino.png");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://discourse.mcneel.com/"));
      }
    }

    public static void UpdateDocumentUnits(Rhino.RhinoDoc rhinoDoc, Document revitDoc = null)
    {
      bool docModified = rhinoDoc.Modified;

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

        UpdateViewConstructionPlanes(rhinoDoc, revitDoc);
      }

      rhinoDoc.Modified = docModified;
    }

    private static void UpdateViewConstructionPlanes(Rhino.RhinoDoc rhinoDoc, Document revitDoc)
    {
      if (!string.IsNullOrEmpty(rhinoDoc.TemplateFileUsed))
        return;

      if (rhinoDoc.IsCreating)
      {
        Revit.EnqueueAction(doc => UpdateViewConstructionPlanes(rhinoDoc, doc));
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

    public Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      var MainWindow = Rhino.UI.RhinoEtoApp.MainWindow;
      if (MainWindow.Visible && MainWindow.WindowState == Eto.Forms.WindowState.Normal)
      {
        // We want to keep Grasshopper visible in this case.
        //MainWindow.WindowState = Eto.Forms.WindowState.Minimized;
        MainWindow.Visible = false;
      }
      else
      {
        // Reset document units
        UpdateDocumentUnits(Rhino.RhinoDoc.ActiveDoc, data.Application.ActiveUIDocument?.Document);

        MainWindow.Visible = true;
        MainWindow.WindowState = Eto.Forms.WindowState.Normal;
      }

      return Result.Succeeded;
    }
  }
}
