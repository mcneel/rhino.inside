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
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://github.com/mcneel/rhino.inside/blob/master/Autodesk/Revit/README.md"));
      }
    }

    public static void ResetDocumentUnits(Rhino.RhinoDoc rhinoDoc, Document revitDoc = null)
    {
      bool docModified = rhinoDoc.Modified;

      if (revitDoc == null)
      {
        rhinoDoc.ModelUnitSystem = Rhino.UnitSystem.None;
        rhinoDoc.ModelAbsoluteTolerance = Revit.VertexTolerance;
        rhinoDoc.ModelAngleToleranceRadians = Revit.AngleTolerance;
      }
      else
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

        // Construction Planes
        {
          var modelPlane = Rhino.Geometry.Plane.WorldXY;

          var modelGridSpacing = imperial ?
          1.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Yards, rhinoDoc.ModelUnitSystem) :
          1.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Meters, rhinoDoc.ModelUnitSystem);

          var modelSnapSpacing = imperial ?
          1 / 16.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Inches, rhinoDoc.ModelUnitSystem) :
          1.0 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Millimeters, rhinoDoc.ModelUnitSystem);

          var modelThickLineFrequency = imperial ? 6 : 5;

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

      rhinoDoc.Modified = docModified;
    }

    public Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      var MainWindow = Rhino.UI.RhinoEtoApp.MainWindow;
      if (MainWindow.Visible)
      {
        var doc = Rhino.RhinoDoc.ActiveDoc;
        if (doc.Modified)
        {
          string docTitle = doc.Name ?? "Untitled";
          switch (Eto.Forms.MessageBox.Show("Save changes to " + docTitle + "?", Rhino.RhinoApp.Name, Eto.Forms.MessageBoxButtons.YesNoCancel))
          {
            case Eto.Forms.DialogResult.Yes:
              var docFileName = doc.Path;
              if (docFileName == null)
              {
                using (var dialog = new Eto.Forms.SaveFileDialog())
                {
                  dialog.FileName = docTitle;
                  dialog.Filters.Add(new Eto.Forms.FileFilter("Rhino 3D Model", new string[] { "3dm" }));
                  if (dialog.ShowDialog(MainWindow) != Eto.Forms.DialogResult.Ok)
                    return Result.Cancelled;

                  if (Path.HasExtension(dialog.FileName))
                    docFileName = dialog.FileName;
                  else
                    docFileName = Path.ChangeExtension(dialog.FileName, dialog.CurrentFilter.Extensions[0]);
                }
              }

              Rhino.RhinoDoc.ActiveDoc.WriteFile(docFileName, new Rhino.FileIO.FileWriteOptions()); break;
            case Eto.Forms.DialogResult.No: break;
            case Eto.Forms.DialogResult.Cancel: return Result.Cancelled;
          }

        }
        // We want to keep Grasshopper visible in this case.
        //try { MainWindow.WindowState = Eto.Forms.WindowState.Minimized; }
        //catch (NotImplementedException) { }
        MainWindow.Visible = false;
        var newDoc = Rhino.RhinoDoc.Create(null);
        ResetDocumentUnits(newDoc, data.Application.ActiveUIDocument?.Document);
      }
      else
      {
        MainWindow.Visible = true;
        try { MainWindow.WindowState = Eto.Forms.WindowState.Normal; }
        catch (NotImplementedException) { }
        ResetDocumentUnits(Rhino.RhinoDoc.ActiveDoc, data.Application.ActiveUIDocument?.Document);
      }

      return Result.Succeeded;
    }
  }
}
