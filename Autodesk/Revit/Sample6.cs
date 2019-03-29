using System;
using System.Diagnostics;
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Linq;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;

namespace RhinoInside.Revit.Samples
{
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  public class Sample6 : IExternalCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var thisAssembly = Assembly.GetExecutingAssembly();

      var buttonData = new PushButtonData
      (
        "cmdRhinoInsideSample6", "Sample 6",
        thisAssembly.Location,
        MethodBase.GetCurrentMethod().DeclaringType.FullName
      );

      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
#if REVIT_2018
        pushButton.ToolTip = "Toggle Rhino model preview visibility";
#else
        pushButton.ToolTip = "Toggle Rhino model preview visibility (Revit 2018 or above)";
#endif
        pushButton.LargeImage = ImageBuilder.BuildLargeImage("6");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://github.com/mcneel/rhino.inside/blob/master/Autodesk/Revit/README.md#sample-6"));
      }
    }

    public Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
#if REVIT_2018
      DocumentPreviewServer.Toggle();
      return Result.Succeeded;
#else
      return Result.Failed;
#endif
    }
  }
}
