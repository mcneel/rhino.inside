using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Input;
using Autodesk.Revit.Attributes;
using Autodesk.Revit.UI;
using Microsoft.Win32;

namespace RhinoInside.Revit
{
  [Transaction(TransactionMode.Manual)]
  [Regeneration(RegenerationOption.Manual)]
  [Journaling(JournalingMode.NoCommandData)]
  public class Addin : IExternalApplication
  {
    #region Static constructor
    static readonly string SystemDir = (string) Registry.GetValue
    (
      @"HKEY_LOCAL_MACHINE\SOFTWARE\McNeel\Rhinoceros\7.0\Install", "Path",
      Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Rhino WIP", "System")
    );
    internal static readonly string RhinoExePath = Path.Combine(SystemDir, "Rhino.exe");
    internal static readonly FileVersionInfo RhinoVersionInfo = File.Exists(RhinoExePath) ? FileVersionInfo.GetVersionInfo(RhinoExePath) : null ;
    static readonly Version MinimumRhinoVersion = new Version(7, 0, 19183);
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
          MainIcon = TaskDialogIcons.IconInformation,
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
          MainIcon = TaskDialogIcons.IconInformation,
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

  static class TaskDialogIcons
  {
    public const TaskDialogIcon IconNone = TaskDialogIcon.TaskDialogIconNone;
#if REVIT_2018
    public const TaskDialogIcon IconShield = TaskDialogIcon.TaskDialogIconShield;
    public const TaskDialogIcon IconInformation = TaskDialogIcon.TaskDialogIconInformation;
    public const TaskDialogIcon IconError = TaskDialogIcon.TaskDialogIconError;
#else
    public const TaskDialogIcon IconShield = TaskDialogIcon.TaskDialogIconWarning;
    public const TaskDialogIcon IconInformation = TaskDialogIcon.TaskDialogIconWarning;
    public const TaskDialogIcon IconError = TaskDialogIcon.TaskDialogIconWarning;
#endif
    public const TaskDialogIcon IconWarning = TaskDialogIcon.TaskDialogIconWarning;
  }
}

namespace RhinoInside.Revit.UI
{
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandRhinoInside : ExternalCommand
  {
    const char ShortcutAssigned = 'R';
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
          string keyboardShortcutsPath = Path.Combine(Revit.CurrentUsersDataFolderPath, "KeyboardShortcuts.xml");
          if (!File.Exists(keyboardShortcutsPath))
            keyboardShortcutsPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData), "Autodesk", $"RVT {Revit.ApplicationUI.ControlledApplication.VersionNumber}", "UserDataCache", "KeyboardShortcuts.xml");

          if (!Revit.KeyboardShortcuts.LoadFrom(keyboardShortcutsPath, out var shortcuts))
            Revit.KeyboardShortcuts.LoadFromResources($"RhinoInside.Resources.RVT{Revit.ApplicationUI.ControlledApplication.VersionNumber}.KeyboardShortcuts.xml", out shortcuts);

#if DEBUG
          // Those lines generate the KeyboardShortcuts.xml template file when new Revit version is supported
          string keyboardShortcutsTemplatePath = Path.Combine(Addin.SourceCodePath, "Resources", $"RVT{Revit.ApplicationUI.ControlledApplication.VersionNumber}", "KeyboardShortcuts.xml");
          var info = new FileInfo(keyboardShortcutsTemplatePath);
          if (info.Length == 0)
          {
            var shortcutsSummary = new Revit.KeyboardShortcuts.Shortcuts();
            foreach (var shortcut in shortcuts.OrderBy(x => x.CommandId))
            {
              if (!string.IsNullOrEmpty(shortcut.Shortcuts))
              {
                var shortcutDefinition = new Revit.KeyboardShortcuts.ShortcutItem
                {
                  CommandId = shortcut.CommandId,
                  Shortcuts = shortcut.Shortcuts
                };
                shortcutsSummary.Add(shortcutDefinition);
              }
            }

            Revit.KeyboardShortcuts.SaveAs(shortcutsSummary, keyboardShortcutsTemplatePath);
          }
#endif

          try
          {
            var shortcutItem = shortcuts.Where(x => x.CommandId == CommandId).First();
            if (shortcutItem.Shortcuts == null)
            {
              shortcutItem.Shortcuts = Shortcuts;
              Rhinoceros.ModalScope.Exit += ModalScope_Exit;
            }
          }
          catch (InvalidOperationException)
          {
            var shortcutItem = new Revit.KeyboardShortcuts.ShortcutItem()
            {
              CommandName = CommandName,
              CommandId = CommandId,
              Shortcuts = Shortcuts,
              Paths = $"Add-Ins>{ribbonPanel.Name}"
            };
            shortcuts.Add(shortcutItem);
            Rhinoceros.ModalScope.Exit += ModalScope_Exit;
          }

          Revit.KeyboardShortcuts.SaveAs(shortcuts, Path.Combine(Revit.CurrentUsersDataFolderPath, "KeyboardShortcuts.xml"));
        }
      }
    }

    static void ShowShortcutHelp()
    {
      using
      (
        var taskDialog = new TaskDialog(MethodBase.GetCurrentMethod().DeclaringType.FullName)
        {
          Title = "New Shortcut",
          MainIcon = TaskDialogIcons.IconInformation,
          TitleAutoPrefix = true,
          AllowCancellation = true,
          MainInstruction = $"Keyboard shortcut '{ShortcutAssigned}' is now assigned to Rhino",
          MainContent = $"You can use {ShortcutAssigned} key to restore previously visible Rhino windows over Revit window every time you need them.",
          FooterText = "This is a one time message",
        }
      )
      {
        taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink1, "Customize keyboard shortcuts...");
        if (taskDialog.Show() == TaskDialogResult.CommandLink1)
        {
          Revit.ActiveUIApplication.PostCommand(RevitCommandId.LookupPostableCommandId(PostableCommand.KeyboardShortcuts));
        }
      }
    }

    static void ModalScope_Exit(object sender, EventArgs e)
    {
      Rhinoceros.ModalScope.Exit -= ModalScope_Exit;
      ShowShortcutHelp();
    }

    public override Result Execute(ExternalCommandData data, ref string message, Autodesk.Revit.DB.ElementSet elements)
    {
      var result = Result.Failed;
      string rhinoTab = Addin.RhinoVersionInfo?.ProductName ?? "Rhinoceros";

      if (RhinoCommand.Availability.Available)
      {
        if(Keyboard.IsKeyDown(Key.LeftCtrl))
          return Rhinoceros.RunCommandAbout();

        using(var modal = new Rhinoceros.ModalScope())
          result = modal.Run(false, true);

        // If no windows are visible we show the Ribbon tab
        if (result == Result.Cancelled)
          result = data.Application.ActivateRibbonTab(rhinoTab) ? Result.Succeeded : Result.Failed;

        return result;
      }

      result = Addin.CheckSetup();
      if (result != Result.Succeeded)
        return result;

      result = Revit.OnStartup(Revit.ApplicationUI);
      if (RhinoCommand.Availability.Available = result == Result.Succeeded)
      {
        // Update Rhino button Tooltip
        Button.ToolTip = $"Restores previously visible Rhino windows on top of Revit window";
        Button.LongDescription = $"Use CTRL key to open a Rhino model";

        // Register UI on Revit
        data.Application.CreateRibbonTab(rhinoTab);

        var RhinocerosPanel = data.Application.CreateRibbonPanel(rhinoTab, "Rhinoceros");
        HelpCommand.CreateUI(RhinocerosPanel);
        RhinocerosPanel.AddSeparator();
        CommandRhino.CreateUI(RhinocerosPanel);
        CommandPython.CreateUI(RhinocerosPanel);

        var GrasshopperPanel = data.Application.CreateRibbonPanel(rhinoTab, "Grasshopper");
        CommandGrasshopper.CreateUI(GrasshopperPanel);
        Samples.Sample4.CreateUI(GrasshopperPanel);
        CommandGrasshopperPreview.CreateUI(GrasshopperPanel);
        CommandGrasshopperRecompute.CreateUI(GrasshopperPanel);
        CommandGrasshopperBake.CreateUI(GrasshopperPanel);

        var SamplesPanel = data.Application.CreateRibbonPanel(rhinoTab, "Samples");
        Samples.Sample1.CreateUI(SamplesPanel);
        Samples.Sample6.CreateUI(SamplesPanel);
        Samples.Sample8.CreateUI(SamplesPanel);
      }

      if (result == Result.Succeeded)
      {
        // Activate Rhinoceros Tab
        result = data.Application.ActivateRibbonTab(rhinoTab) ? Result.Succeeded : Result.Failed;
      }
      else
      {
        // No more loads in this session
        Button.Enabled = false;
        Button.ToolTip = "Failed to load.";
      }

      return result;
    }
  }
}
