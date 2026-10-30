using System;
using System.IO;
using System.Linq;

namespace RhinoInside.EtoTestApp;

/// <summary>
/// An Eto app for trying Rhino.Inside by hand.
/// </summary>
/// <remarks>
/// Usage: rhinoinside-etotestapp [--headless] [--host-app] [--late-start] [--rhino &lt;dir&gt;]
/// <list type="bullet">
/// <item>--headless: start Rhino without its own UI.</item>
/// <item>--host-app: create the app object before Rhino starts, as a host with a UI of its own does.</item>
/// <item>--late-start: run the host's app first and start Rhino from a button in its window. Implies --host-app.</item>
/// <item>--rhino: Rhino's system directory. Defaults to $RHINOINSIDE_RHINOPATH, then the rhino9 dev build next to this repo.</item>
/// </list>
/// </remarks>
static class Program
{
  const string Usage = "Usage: rhinoinside-etotestapp [--headless] [--host-app] [--late-start] [--rhino <dir>]";

  [STAThread]
  static int Main(string[] args)
  {
    var options = Options.Parse(args);
    if (options == null)
    {
      Console.Error.WriteLine(Usage);
      return 2;
    }

    var rhinoDirectory = options.RhinoDirectory
      ?? Environment.GetEnvironmentVariable("RHINOINSIDE_RHINOPATH")
      ?? DevBuild.FindRhinoDirectory();
    if (rhinoDirectory == null || !Directory.Exists(rhinoDirectory))
    {
      Console.Error.WriteLine($"Could not find Rhino (got '{rhinoDirectory}'). Pass --rhino <dir> or set RHINOINSIDE_RHINOPATH.");
      return 2;
    }

    // Before anything touches a Rhino or Eto type - they load from Rhino's directory.
    Resolver.Initialize(rhinoDirectory);
    Console.WriteLine($"Loading Rhino @ {Resolver.RhinoSystemDirectory}");

    return TestApp.Run(options);
  }
}

/// <summary>
/// Command-line options.
/// </summary>
sealed class Options
{
  public bool Headless { get; private set; }

  public bool HostApp { get; private set; }

  public bool LateStart { get; private set; }

  public string RhinoDirectory { get; private set; }

  /// <summary>
  /// The options in <paramref name="args"/>, or null if they are not valid.
  /// </summary>
  public static Options Parse(string[] args)
  {
    var options = new Options();
    for (int i = 0; i < args.Length; i++)
    {
      switch (args[i])
      {
        case "--headless":
          options.Headless = true;
          break;
        case "--host-app":
          options.HostApp = true;
          break;
        case "--late-start":
          options.LateStart = true;
          options.HostApp = true;
          break;
        case "--rhino" when i + 1 < args.Length:
          options.RhinoDirectory = args[++i];
          break;
        default:
          return null;
      }
    }
    return options;
  }
}

/// <summary>
/// Finds the Rhino built from a rhino9 checkout next to this repo.
/// </summary>
static class DevBuild
{
  /// <summary>
  /// The dev build's Rhino system directory, or null if there is none.
  /// </summary>
  public static string FindRhinoDirectory()
  {
    var rhino9 = FindRhino9Checkout();
    if (rhino9 == null)
      return null;

    if (OperatingSystem.IsWindows())
      return Path.Combine(rhino9, "src4", "bin", "Debug");

    if (OperatingSystem.IsMacOS())
      return FindMacBuild(rhino9);

    return null;
  }

  static string FindRhino9Checkout()
  {
    for (var dir = new DirectoryInfo(AppContext.BaseDirectory); dir != null; dir = dir.Parent)
    {
      if (File.Exists(Path.Combine(dir.FullName, "src", "RhinoInside.sln")))
      {
        var rhino9 = Path.Combine(dir.Parent?.FullName ?? "", "rhino9");
        return Directory.Exists(rhino9) ? rhino9 : null;
      }
    }
    return null;
  }

  // Xcode builds into DerivedData, not the checkout; its info.plist names the workspace it built.
  static string FindMacBuild(string rhino9)
  {
    var derivedData = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Library", "Developer", "Xcode", "DerivedData");
    if (!Directory.Exists(derivedData))
      return null;

    var workspace = Path.Combine(rhino9, "src4", "rhino4", "MacRhino.xcworkspace");
    return Directory.GetDirectories(derivedData, "MacRhino-*")
      .Where(dir => File.Exists(Path.Combine(dir, "info.plist")) && File.ReadAllText(Path.Combine(dir, "info.plist")).Contains(workspace))
      .Select(dir => Path.Combine(dir, "Build", "Products", "Debug", "Rhinoceros.app", "Contents", "Frameworks"))
      .FirstOrDefault(Directory.Exists);
  }
}
