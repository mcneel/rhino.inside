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

using Eto.Forms;
using Rhino.PlugIns;

namespace RhinoInside.Revit.UI
{
  abstract public class RhinoCommand : ExternalCommand
  {
    public RhinoCommand()
    {
      if (Revit.OnStartup(Revit.ApplicationUI) != Result.Succeeded)
      {
        Availability.Available = false;
        throw new Exception("Failed to startup Rhino");
      }
    }

    public new class Availability : ExternalCommand.Availability
    {
      internal static bool Available = false;

      public override bool IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories) =>
        Available &&
        !Rhino.Commands.Command.InCommand() &&
        base.IsCommandAvailable(applicationData, selectedCategories);
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandRhino : RhinoCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      var buttonData =  NewPushButtonData<CommandRhino, Availability>("Rhino");
      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Toggle Rhino window visibility";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Rhino.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Rhino.png");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://discourse.mcneel.com/"));
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      Rhinoceros.Exposed = !Rhinoceros.Exposed;
      return Result.Succeeded;
    }
  }

  abstract public class IronPyhtonCommand : RhinoCommand
  {
    protected static readonly Guid PluginId = new Guid("814d908a-e25c-493d-97e9-ee3861957f49");
    public IronPyhtonCommand()
    {
      if (!PlugIn.LoadPlugIn(PluginId, true, true))
        throw new Exception("Failed to startup IronPyhton");
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
  class CommandPython : IronPyhtonCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      var buttonData = NewPushButtonData<CommandPython, Availability>("Python");
      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Shows Rhino Python editor window";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Python.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Python.png");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://developer.rhino3d.com/guides/rhinopython/"));
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      return Rhino.RhinoApp.RunScript("!_EditPythonScript", false) ? Result.Succeeded : Result.Failed;
    }
  }
}
