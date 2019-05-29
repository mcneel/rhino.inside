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

using Grasshopper;

namespace RhinoInside.Revit.UI
{
  abstract public class GrasshopperCommand : RhinoCommand
  {
    protected static readonly Guid PluginId = new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF);
    public GrasshopperCommand()
    {
      if (!PlugIn.LoadPlugIn(PluginId, true, true))
        throw new Exception("Failed to startup Grasshopper");
    }

    public new class Availability : RhinoCommand.Availability
    {
      public override bool IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories)
      {
        return base.IsCommandAvailable(applicationData, selectedCategories) &&
              (PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected) & (loaded | !loadProtected));
      }
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopper : GrasshopperCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var buttonData = NewPushButtonData<CommandGrasshopper, Availability>("Grasshopper");
      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Shows Grasshopper window";
        pushButton.LongDescription = $"Use CTRL key to open only Grasshopper window without restoring other tool windows";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Grasshopper.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Grasshopper.png");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://www.grasshopper3d.com/"));
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      using (var modal = new Rhinoceros.ModalScope())
      {
        if (!Rhino.RhinoApp.RunScript("!_-Grasshopper _W _S ENTER", false))
          return Result.Failed;

        return modal.Run(false);
      }
    }
  }
}
