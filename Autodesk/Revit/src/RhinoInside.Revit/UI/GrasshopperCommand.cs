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

  static class CommandGrasshopperPreview
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
#if REVIT_2018
      var radioData = new RadioButtonGroupData("GrasshopperPreview");

      if (ribbonPanel.AddItem(radioData) is RadioButtonGroup radioButton)
      {
        CommandGrasshopperPreviewOff.CreateUI(radioButton);
        CommandGrasshopperPreviewWireframe.CreateUI(radioButton);
        CommandGrasshopperPreviewShaded.CreateUI(radioButton);
      }
#endif
    }
  }

#if REVIT_2018
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperPreviewOff : GrasshopperCommand
  {
    public static void CreateUI(RadioButtonGroup radioButtonGroup)
    {
      var buttonData = NewToggleButtonData<CommandGrasshopperPreviewOff, Availability>("Off");

      if (radioButtonGroup.AddItem(buttonData) is ToggleButton pushButton)
      {
        pushButton.ToolTip = "Don't draw any preview geometry";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Off_24x24.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Off_24x24.png");
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      GH.PreviewServer.PreviewMode = Grasshopper.Kernel.GH_PreviewMode.Disabled;
      Revit.RefreshActiveView();
      return Result.Succeeded;
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperPreviewWireframe : GrasshopperCommand
  {
    public static void CreateUI(RadioButtonGroup radioButtonGroup)
    {
      var buttonData = NewToggleButtonData<CommandGrasshopperPreviewWireframe, Availability>("Wireframe");

      if (radioButtonGroup.AddItem(buttonData) is ToggleButton pushButton)
      {
        pushButton.ToolTip = "Draw wireframe preview geometry";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Wireframe_24x24.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Wireframe_24x24.png");
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      GH.PreviewServer.PreviewMode = Grasshopper.Kernel.GH_PreviewMode.Wireframe;
      Revit.RefreshActiveView();
      return Result.Succeeded;
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperPreviewShaded : GrasshopperCommand
  {
    public static void CreateUI(RadioButtonGroup radioButtonGroup)
    {
      var buttonData = NewToggleButtonData<CommandGrasshopperPreviewShaded, Availability>("Shaded");

      if (radioButtonGroup.AddItem(buttonData) is ToggleButton pushButton)
      {
        pushButton.ToolTip = "Draw shaded preview geometry";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Shaded_24x24.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Shaded_24x24.png");
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      GH.PreviewServer.PreviewMode = Grasshopper.Kernel.GH_PreviewMode.Shaded;
      Revit.RefreshActiveView();
      return Result.Succeeded;
    }
  }
#endif
}
