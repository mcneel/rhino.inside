using System;
using System.IO;
using System.Globalization;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace RhinoInside
{
  static class RhinoFinder
  {
    public static bool TryFindRhino_Windows(int minMajor, bool useLatest, out string rhinoPath)
    {
      rhinoPath = default;
      string baseName = @"SOFTWARE\McNeel\Rhinoceros";

      using var baseKey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(baseName);
      string[] children = baseKey.GetSubKeyNames();
      Array.Sort(children);
      string versionName = "";
      for (int i = children.Length - 1; i >= 0; i--)
      {
        // 20 Jan 2020 S. Baer (https://github.com/mcneel/rhino.inside/issues/248)
        // A generic double.TryParse is failing when run under certain locales.
        if (double.TryParse(children[i], NumberStyles.Any, CultureInfo.InvariantCulture, out double d))
        {
          if (d < 8.0)
            continue;

          versionName = children[i];

          if (!useLatest && (int) Math.Floor(d) != minMajor)
            continue;

          using (var installKey = baseKey.OpenSubKey($"{versionName}\\Install"))
          {
            string corePath = installKey.GetValue("CoreDllPath") as string;
            if (System.IO.File.Exists(corePath))
            {
              rhinoPath = System.IO.Path.GetDirectoryName(corePath);
              return true;
            }
          }
        }
      }

      return false;
    }

    public static bool TryFindRhino_macOS(IEnumerable<string> searchPaths, int minMajor, bool useLatest, out string rhinoPath)
    {
      rhinoPath = default;
      var versionFinder = new Regex(@"Rhino (?<ver>\d+)\.app", RegexOptions.IgnoreCase);

      int foundVersion = -1;
      string foundPath = string.Empty;
      foreach (string appPath in searchPaths)
        foreach (string rhPath in Directory.GetDirectories(appPath, "Rhino *.app"))
        {
          var m = versionFinder.Match(rhPath);
          if (m.Success
                && int.TryParse(m.Groups["ver"].Value, NumberStyles.Any, CultureInfo.InvariantCulture, out int d))
          {
            if ((useLatest && d >= (foundVersion > -1 ? foundVersion : minMajor)) ||
                  (d == minMajor && !useLatest))
            {
              foundVersion = d;
              foundPath = rhPath;
            }
          }
        }

      if (foundVersion >= minMajor)
      {
        rhinoPath = Path.Combine(foundPath, "Contents", "Frameworks");
        return true;
      }

      return false;
    }

    public static string PrepareSystemPath(string rhinoPath)
    {
      if (string.IsNullOrWhiteSpace(rhinoPath))
        return FindRhinoSystemDirectory();

      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX)
            && rhinoPath.EndsWith(".app", StringComparison.InvariantCultureIgnoreCase))
      {
        return Path.Combine(rhinoPath, "Contents", "Frameworks");
      }

      if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)
            && !rhinoPath.EndsWith("System", StringComparison.InvariantCultureIgnoreCase)
            && !File.Exists(Path.Combine(rhinoPath, "RhinoLibrary.dll")))
      {
        return Path.Combine(rhinoPath, "System");
      }

      return rhinoPath;
    }

    public static string FindRhinoSystemDirectory(bool useLatest = false)
    {
      int major = typeof(Resolver).Assembly.GetName().Version.Major;

      if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        if (TryFindRhino_Windows(major, useLatest, out string rhinoPath))
        {
          return rhinoPath;
        }
      }

      else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        List<string> appPaths = new() { "/Applications" };
        string userApps = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Applications");
        if (Directory.Exists(userApps))
        {
          appPaths.Add(userApps);
        }

        if (TryFindRhino_macOS(appPaths, major, useLatest, out string rhinoPath))
        {
          return rhinoPath;
        }
      }

      else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
      {
        return "/usr/lib/rhino3d";
      }

      throw new RhinoInsideInitializationException("Can not find Rhino >=8 installation");
    }
  }
}
