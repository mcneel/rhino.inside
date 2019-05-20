using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;

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
    internal static FileVersionInfo RhinoVersionInfo = FileVersionInfo.GetVersionInfo(RhinoExePath);

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
      var RhinoVersion = new Version
      (
        RhinoVersionInfo.FileMajorPart,
        RhinoVersionInfo.FileMinorPart,
        RhinoVersionInfo.FileBuildPart,
        RhinoVersionInfo.FilePrivatePart
      );
      var MinimumRhinoVersion = new Version(7, 0, 19127);

      if (RhinoVersion < MinimumRhinoVersion)
        return Result.Failed;

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
        taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink1, "Check for updates now...");
        if (taskDialog.Show() == TaskDialogResult.CommandLink1)
        {
          using (System.Diagnostics.Process.Start("https://github.com/mcneel/rhino.inside/releases/latest")) { }
        }
      }

      return DaysUntilExpiration < 1;
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
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      var buttonData = NewPushButtonData<CommandRhinoInside, AllwaysAvailable>("Rhino");
      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
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
    }

    public override Result Execute(ExternalCommandData data, ref string message, Autodesk.Revit.DB.ElementSet elements)
    {
      if (Addin.IsExpired())
        return Result.Cancelled;

      string rhinoTab = Addin.RhinoVersionInfo.ProductName ?? "Rhinoceros";

      var result = Result.Failed;
      if (RhinoCommand.Availability.Available)
      {
        result = Rhinoceros.RunCommandAbout();
      }
      else
      {
        result = Revit.OnStartup(Revit.ApplicationUI);
        if (RhinoCommand.Availability.Available = result == Result.Succeeded)
        {
          // Register UI on Revit
          data.Application.CreateRibbonTab(rhinoTab);
          var ribbonPanel = data.Application.CreateRibbonPanel(rhinoTab, "Rhinoceros");

          HelpCommand.CreateUI(ribbonPanel);
          ribbonPanel.AddSeparator();
          CommandRhino.CreateUI(ribbonPanel);
          CommandGrasshopper.CreateUI(ribbonPanel);
          CommandPython.CreateUI(ribbonPanel);
          ribbonPanel.AddSeparator();
          Samples.Sample1.CreateUI(ribbonPanel);
          Samples.Sample4.CreateUI(ribbonPanel);
          Samples.Sample6.CreateUI(ribbonPanel);
        }
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

      return result;
    }
  }
}
