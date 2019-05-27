using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Input;
using Autodesk.Revit.Attributes;
using Autodesk.Revit.UI;

namespace RhinoInside.Revit
{
  [Transaction(TransactionMode.Manual)]
  [Regeneration(RegenerationOption.Manual)]
  [Journaling(JournalingMode.NoCommandData)]
  public class Addin : IExternalApplication
  {
    #region Static constructor
    static readonly string SystemDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System");
    internal static readonly string RhinoExePath = Path.Combine(SystemDir, "Rhino.exe");
    internal static readonly FileVersionInfo RhinoVersionInfo = File.Exists(RhinoExePath) ? FileVersionInfo.GetVersionInfo(RhinoExePath) : null ;
    static readonly Version MinimumRhinoVersion = new Version(7, 0, 19141);
    static readonly Version RhinoVersion = new Version
    (
      RhinoVersionInfo?.FileMajorPart ?? 0,
      RhinoVersionInfo?.FileMinorPart ?? 0,
      RhinoVersionInfo?.FileBuildPart ?? 0,
      RhinoVersionInfo?.FilePrivatePart ?? 0
    );

    static Addin()
    {
      ResolveEventHandler OnRhinoCommonResolve = null;
      AppDomain.CurrentDomain.AssemblyResolve += OnRhinoCommonResolve = (sender, args) =>
      {
        const string rhinoCommonAssemblyName = "RhinoCommon";
        var assemblyName = new AssemblyName(args.Name).Name;

        if (assemblyName != rhinoCommonAssemblyName)
          return null;

        AppDomain.CurrentDomain.AssemblyResolve -= OnRhinoCommonResolve;
        return Assembly.LoadFrom(Path.Combine(SystemDir, rhinoCommonAssemblyName + ".dll"));
      };
    }
    #endregion

    #region IExternalApplication Members
    Result IExternalApplication.OnStartup(UIControlledApplication applicationUI)
    {
      ApplicationUI = applicationUI;

      // Add launch RhinoInside push button
      UI.CommandRhinoInside.CreateUI(applicationUI.CreateRibbonPanel("Rhinoceros"));

      return Result.Succeeded;
    }

    Result IExternalApplication.OnShutdown(UIControlledApplication applicationUI)
    {
      try
      {
        return Revit.OnShutdown(applicationUI);
      }
      catch (Exception)
      {
        return Result.Failed;
      }
      finally
      {
        ApplicationUI = null;
      }
    }
    #endregion

    #region Version
    public static bool IsExpired(bool quiet = true)
    {
      if (DaysUntilExpiration > 0 && quiet)
        return false;

      using
      (
        var taskDialog = new TaskDialog(MethodBase.GetCurrentMethod().DeclaringType.FullName)
        {
          Title = "Days left",
#if REVIT_2018
          MainIcon = TaskDialogIcon.TaskDialogIconInformation,
#else
          MainIcon = TaskDialogIcon.TaskDialogIconWarning,
#endif
          TitleAutoPrefix = true,
          AllowCancellation = true,
          MainInstruction = DaysUntilExpiration < 1 ?
          "This WIP build has expired" :
          $"This WIP build expires in {DaysUntilExpiration} days",
          FooterText = "Current version: " + DisplayVersion
        }
      )
      {
        taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink1, "Check for updates...");
        if (taskDialog.Show() == TaskDialogResult.CommandLink1)
        {
          using (Process.Start(@"https://github.com/mcneel/rhino.inside/releases/latest")) { }
        }
      }

      return DaysUntilExpiration < 1;
    }
    internal static Result CheckSetup()
    {
      if (RhinoVersion >= MinimumRhinoVersion)
        return IsExpired() ? Result.Cancelled : Result.Succeeded;

      using
      (
        var taskDialog = new TaskDialog(MethodBase.GetCurrentMethod().DeclaringType.FullName)
        {
          Title = "Update Rhino",
#if REVIT_2018
          MainIcon = TaskDialogIcon.TaskDialogIconInformation,
#else
          MainIcon = TaskDialogIcon.TaskDialogIconWarning,
#endif
          TitleAutoPrefix = true,
          AllowCancellation = true,
          MainInstruction = "Unsupported Rhino WIP version",
          MainContent = $"Expected Rhino version is ({MinimumRhinoVersion}) or above",
          FooterText = $"Current Rhino WIP version: {RhinoVersion}"
        }
      )
      {
        taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink1, "Download latest Rhino WIP...");
        if (taskDialog.Show() == TaskDialogResult.CommandLink1)
        {
          using (Process.Start(@"https://www.rhino3d.com/download/rhino/wip")) { }
        }
      }

      return Result.Failed;
    }

    static string CallerFilePath([System.Runtime.CompilerServices.CallerFilePath] string CallerFilePath = "") => CallerFilePath;
    public static string SourceCodePath => Path.GetDirectoryName(CallerFilePath());
    public static int DaysUntilExpiration => Math.Max(0, 45 - (DateTime.Now - BuildDate).Days);

    public static Version Version => Assembly.GetExecutingAssembly().GetName().Version;
    public static DateTime BuildDate => new DateTime(2000, 1, 1).AddDays(Version.Build).AddSeconds(Version.Revision * 2);
    public static string DisplayVersion => $"{Version} ({BuildDate})";
    #endregion

    internal static UIControlledApplication ApplicationUI { get; private set; }
  }
}

namespace RhinoInside.Revit.UI
{
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandRhinoInside : ExternalCommand
  {
    static PushButton Button;
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      const string CommandName = "Rhino";
      string CommandId = $"CustomCtrl_%CustomCtrl_%Add-Ins%{ribbonPanel.Name}%{typeof(CommandRhinoInside).Name}";
      const string Shortcuts = "R#Ctrl+R";

      var buttonData = NewPushButtonData<CommandRhinoInside, AllwaysAvailable>(CommandName);
      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        Button = pushButton;

        if (Addin.RhinoVersionInfo == null)
        {
          pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://www.rhino3d.com/download/rhino/wip"));
          pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Rhino-logo.png", true);
          pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Rhino-logo.png");
        }
        else
        {
          pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://www.rhino3d.com/inside"));
          using (var icon = System.Drawing.Icon.ExtractAssociatedIcon(Addin.RhinoExePath))
          {
            pushButton.Image = icon.ToBitmapSource(true);
            pushButton.LargeImage = icon.ToBitmapSource();
          }

          try
          {
            var versionInfo = Addin.RhinoVersionInfo;
            pushButton.ToolTip = $"Loads {versionInfo.ProductName} inside this Revit session";
            pushButton.LongDescription = $"{versionInfo.FileDescription} ({versionInfo.ProductVersion})\n{versionInfo.LegalCopyright}";
          }
          catch (Exception) { }
        }

        // Register keyboard shortcut
        {
          string keyboardShortcutsPath = Path.Combine(Revit.ApplicationUI.ControlledApplication.CurrentUsersDataFolderPath, "KeyboardShortcuts.xml");

          Revit.KeyboardShortcuts.ShortcutItem shortcutItem = null;
          if (Revit.KeyboardShortcuts.LoadFrom(keyboardShortcutsPath, out var shortcuts))
          {
            foreach (var shortcut in shortcuts.Where(x => x.CommandId == CommandId))
            {
              shortcutItem = shortcut;
              break;
            }
          }

          if (shortcutItem == null)
          {
            var item = new Revit.KeyboardShortcuts.ShortcutItem()
            {
              CommandName = CommandName,
              CommandId = CommandId,
              Shortcuts = Shortcuts,
              Paths = $"Add-Ins>{ribbonPanel.Name}"
            };
            shortcuts.Add(item);
          }
          else
          {
            if (shortcutItem.Shortcuts == null)
              shortcutItem.Shortcuts = Shortcuts;
          }

          Revit.KeyboardShortcuts.SaveAs(shortcuts, keyboardShortcutsPath);
        }
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, Autodesk.Revit.DB.ElementSet elements)
    {
      if (RhinoCommand.Availability.Available)
        return Rhinoceros.RunModal(!Keyboard.IsKeyDown(Key.LeftCtrl), true);

      if (Addin.CheckSetup() is Result result && result != Result.Succeeded)
        return result;

      {
        string rhinoTab = Addin.RhinoVersionInfo?.ProductName ?? "Rhinoceros";

        result = Revit.OnStartup(Revit.ApplicationUI);
        if (RhinoCommand.Availability.Available = result == Result.Succeeded)
        {
          // Update Rhino button Tooltip
          Button.ToolTip = $"Shows all Rhino windows on top of Revit window";
          Button.LongDescription = $"Use CTRL key to just retore tool windows but not Rhino itself";

          // Register UI on Revit
          data.Application.CreateRibbonTab(rhinoTab);

          var RhinocerosPanel = data.Application.CreateRibbonPanel(rhinoTab, "Rhinoceros");
          HelpCommand.CreateUI(RhinocerosPanel);
          RhinocerosPanel.AddSeparator();
          CommandRhino.CreateUI(RhinocerosPanel);
          CommandGrasshopper.CreateUI(RhinocerosPanel);
          CommandPython.CreateUI(RhinocerosPanel);

          var SamplesPanel = data.Application.CreateRibbonPanel(rhinoTab, "Samples");
          Samples.Sample1.CreateUI(SamplesPanel);
          Samples.Sample4.CreateUI(SamplesPanel);
          Samples.Sample6.CreateUI(SamplesPanel);
        }

        // Show Rhinoceros Tab
        if (result == Result.Succeeded)
        {
          var ribbon = Autodesk.Windows.ComponentManager.Ribbon;
          foreach (var tab in ribbon.Tabs)
          {
            if (tab.Name == rhinoTab)
            {
              tab.IsActive = true;
              break;
            }
          }
        }
        else
        {
          // No more loads in this session
          Button.Enabled = false;
        }

        return result;
      }
    }
  }
}
