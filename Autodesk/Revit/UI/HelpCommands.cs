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
  abstract class HelpCommand : Command
  {
    internal static void CreateUI(RibbonPanel ribbonPanel)
    {
      if (ribbonPanel.AddItem(new PulldownButtonData("cmdRhinoInside.Help", "Help")) is PulldownButton pullDownButton)
      {
        pullDownButton.LargeImage = ImageBuilder.BuildLargeImage("?");

        pullDownButton.AddPushButton(typeof(APIDocsCommand),           "APIDocs",           "Opens revitapidocs.com website",             typeof(AllwaysAvailable));
        pullDownButton.AddPushButton(typeof(TheBuildingCoderCommand),  "TheBuildingCoder",  "Opens thebuildingcoder.typepad.com website", typeof(AllwaysAvailable));
        pullDownButton.AddSeparator();
        pullDownButton.AddPushButton(typeof(RhinoDevDocsCommand),      "Rhino Dev Docs",    "Opens developer.rhino3d.com website",        typeof(AllwaysAvailable));
        pullDownButton.AddPushButton(typeof(DiscourseCommand),         "McNeel Discourse",  "Opens discourse.mcneel.com website",         typeof(AllwaysAvailable));
        pullDownButton.AddPushButton(typeof(AboutCommand),             "About",             "Opens GitHub Repo website",                  typeof(AllwaysAvailable));
      }
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

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class AboutCommand : HelpCommand
  {
    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      using (System.Diagnostics.Process.Start("https://github.com/mcneel/rhino.inside/blob/master/Autodesk/Revit/README.md")) { }

      return Result.Succeeded;
    }
  }
  
}
