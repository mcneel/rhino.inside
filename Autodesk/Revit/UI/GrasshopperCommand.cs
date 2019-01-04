using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;
using Rhino.PlugIns;

namespace RhinoInside.Revit.UI
{
  [Transaction(TransactionMode.Manual)]
  [Regeneration(RegenerationOption.Manual)]
  class GrasshopperCommand : IExternalCommand
  {
    static readonly Guid GrasshopperGuid = new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF);
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      if (!PlugIn.PlugInExists(GrasshopperGuid, out bool loaded, out bool loadProtected))
        return;

      // Create a push button to trigger a command add it to the ribbon panel.
      var thisAssembly = Assembly.GetExecutingAssembly();

      var buttonData = new PushButtonData
      (
        "cmdRhinoInside.Grasshopper", "Grasshopper",
        thisAssembly.Location,
        MethodBase.GetCurrentMethod().DeclaringType.FullName
      );

      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Toggle Grasshopper  window visibility";
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Grasshopper.png");
        pushButton.Enabled = !loadProtected;
      }
    }

    public Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      if(!PlugIn.LoadPlugIn(GrasshopperGuid))
        return Result.Failed;

      return Rhino.RhinoApp.RunScript("!_-Grasshopper _W _T ENTER", false) ? Result.Succeeded : Result.Failed;
    }
  }
}
