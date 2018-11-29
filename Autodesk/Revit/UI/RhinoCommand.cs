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
      }
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
        newDoc.ModelUnitSystem = Rhino.UnitSystem.None;
      }
      else
      {
        MainWindow.Visible = true;
        try { MainWindow.WindowState = Eto.Forms.WindowState.Normal; }
        catch (NotImplementedException) { }
      }

      return Result.Succeeded;
    }
  }
}
