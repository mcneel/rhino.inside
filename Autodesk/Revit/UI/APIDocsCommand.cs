using System;
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
  abstract class HelpCommand : IExternalCommand
  {
    internal static void CreateUI(RibbonPanel ribbonPanel)
    {
      if (ribbonPanel.AddItem(new PulldownButtonData("cmdRhinoInside.Help", "Help")) is PulldownButton pullDownButton)
      {
        pullDownButton.LargeImage = ImageBuilder.BuildImage("?");

        AddPushButton(pullDownButton, typeof(APIDocsCommand),           "APIDocs", "Opens revitapidocs.com website");
        AddPushButton(pullDownButton, typeof(TheBuildingCoderCommand),  "TheBuildingCoder", "Opens thebuildingcoder.typepad.com website");
        pullDownButton.AddSeparator();
        AddPushButton(pullDownButton, typeof(RhinoDevDocsCommand),      "Rhino Dev Docs", "Opens developer.rhino3d.com website");
        AddPushButton(pullDownButton, typeof(DiscourseCommand),         "McNeel Discourse", "Opens discourse.mcneel.com website");
      }
    }

    private static void AddPushButton(PulldownButton pullDownButton, Type commandType,string text, string tooltip = default(string))
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var thisAssembly = Assembly.GetExecutingAssembly();
      var buttonData = new PushButtonData("cmdRhinoInside." + commandType.Name, text, thisAssembly.Location, commandType.FullName);

      if (pullDownButton.AddPushButton(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = tooltip;
        pushButton.AvailabilityClassName = typeof(CommandAvailability).FullName;
      }
    }

    public abstract Result Execute(ExternalCommandData data, ref string message, ElementSet elements);

    class CommandAvailability : IExternalCommandAvailability
    {
      bool IExternalCommandAvailability.IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories) => true;
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class APIDocsCommand : HelpCommand
  {
    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      using (System.Diagnostics.Process.Start("http://www.revitapidocs.com/")) { }

      return Result.Succeeded;
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class TheBuildingCoderCommand : HelpCommand
  {
    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      using (System.Diagnostics.Process.Start("https://thebuildingcoder.typepad.com/")) { }

      return Result.Succeeded;
    }
  }
  
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class RhinoDevDocsCommand : HelpCommand
  {
    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      using (System.Diagnostics.Process.Start("https://developer.rhino3d.com/")) { }

      return Result.Succeeded;
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class DiscourseCommand : HelpCommand
  {
    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      using (System.Diagnostics.Process.Start("https://discourse.mcneel.com/c/serengeti/inside")) { }

      return Result.Succeeded;
    }
  }
}
