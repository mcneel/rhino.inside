using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Management.Automation;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;
using System.IO;

namespace RhinoInside.Revit.UI
{
  abstract class HelpCommand : Command
  {
    static protected PulldownButton helpButton = null;
    internal static void CreateUI(RibbonPanel ribbonPanel)
    {
      if (ribbonPanel.AddItem(new PulldownButtonData("cmdRhinoInside.Help", "Help")) is PulldownButton pullDownButton)
      {
        helpButton = pullDownButton;
        helpButton.LargeImage = ImageBuilder.BuildLargeImage("?");

        helpButton.AddPushButton(typeof(APIDocsCommand),           "APIDocs",           "Opens revitapidocs.com website",             typeof(AllwaysAvailable));
        helpButton.AddPushButton(typeof(TheBuildingCoderCommand),  "TheBuildingCoder",  "Opens thebuildingcoder.typepad.com website", typeof(AllwaysAvailable));
        helpButton.AddSeparator();
        helpButton.AddPushButton(typeof(RhinoDevDocsCommand),      "Rhino Dev Docs",    "Opens developer.rhino3d.com website",        typeof(AllwaysAvailable));
        helpButton.AddPushButton(typeof(DiscourseCommand),         "McNeel Discourse",  "Opens discourse.mcneel.com website",         typeof(AllwaysAvailable));
        helpButton.AddSeparator();
#if DEBUG
        helpButton.AddPushButton(typeof(CheckForUpdatesCommand),    "Check for updates", "Checks if there are updates in GitHub",      typeof(AllwaysAvailable));
#endif
        helpButton.AddPushButton(typeof(AboutCommand),              "About",             "Opens GitHub Repo website",                  typeof(AllwaysAvailable));
      }

      CheckForUpdatesCommand.CheckUpdates();
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
  class CheckForUpdatesCommand : HelpCommand
  {
    static public int CheckUpdates(bool quiet = true, bool forceFetch = false)
    {
#if DEBUG
      int retCode = -1;
      using (var powerShell = PowerShell.Create())
      {
        powerShell.AddScript(string.Format(@"Set-Location {0}", Revit.SourceCodePath));
        powerShell.AddScript(@"git rev-parse --absolute-git-dir");
        var gitdir = powerShell.Invoke();
        if (powerShell.HadErrors)
          return -1;

        powerShell.AddScript(@"git rev-parse --abbrev-ref HEAD");
        var currentBranch = powerShell.Invoke();
        if (currentBranch.Count == 1)
        {
          using
          (
            var taskDialog = new TaskDialog("RhinoInside.Revit.CheckForUpdates")
            {
              Title = "Updates",
              MainIcon = TaskDialogIcon.TaskDialogIconInformation,
              TitleAutoPrefix = true,
              AllowCancellation = true,
              FooterText = Revit.SourceCodePath
            }
          )
          {
            // In quiet mode fetch just once per hour.
            // if not in quiet mode forceFetch it's OK since the TaskDialog will stop execution for some time.
            {
              powerShell.Streams.Error.Clear();
              string gitPath = Path.GetFullPath(Path.Combine(gitdir[0].ToString(), "FETCH_HEAD"));

              if ((!quiet && forceFetch) || (DateTime.UtcNow - File.GetLastWriteTimeUtc(gitPath)).Hours > 0)
              {
                powerShell.AddScript(@"git fetch");
                powerShell.Invoke();
              }
            }

            if (forceFetch && powerShell.HadErrors)
            {
              taskDialog.MainIcon = TaskDialogIcon.TaskDialogIconError;
              taskDialog.MainInstruction = "Failed to fetch changes from the repository";

              foreach (var f in powerShell.Streams.Error)
              {
                var line = f.ToString();
                taskDialog.ExpandedContent += line + "\n";
              }
            }
            else
            {
              powerShell.AddScript(string.Format(@"git log HEAD..origin/{0} --oneline .", currentBranch[0].ToString()));
              var results = powerShell.Invoke();

              retCode = results.Count;
              if (retCode == 0)
              {
                taskDialog.MainInstruction = "You are up to date!!";
              }
              else
              {
                taskDialog.MainInstruction = string.Format("There are {0} changes in the repository", results.Count);

                foreach (var result in results.Take(12))
                {
                  var line = result.ToString();
                  var comment = line.Substring(line.IndexOf(' ') + 1);
                  taskDialog.ExpandedContent += "- " + comment + "\n";
                }
              }
            }


            if (!quiet)
              taskDialog.Show();
          }
        }
      }

      if (helpButton != null)
      {
        helpButton.LargeImage = retCode > 0 ? ImageBuilder.BuildLargeImage(retCode.ToString(), System.Drawing.Color.DarkRed) : ImageBuilder.BuildLargeImage("?");
        helpButton.ToolTip = retCode > 0 ? string.Format("There are {0} changes in the repository", retCode) : string.Empty;
      }

      return retCode;
#else
      return 0;
#endif
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      return CheckUpdates(false, true) < 0 ? Result.Failed : Result.Succeeded;
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
