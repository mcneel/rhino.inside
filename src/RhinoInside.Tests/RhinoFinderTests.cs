using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using NUnit.Framework;

namespace RhinoInside.Tests
{
  [TestFixture]
  public class RhinoFinderTests
  {
#if NET7_0_OR_GREATER
    readonly string _tempPath = Path.GetTempPath();
    readonly List<string> _searchPaths = new();
    string _finderTests;

    [SetUp]
    public void SetupSearchPaths()
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        _finderTests = Path.Combine(_tempPath, "RhinoFinderTests");
        string systemTests = Path.Combine(_finderTests, "System");
        string userTests = Path.Combine(_finderTests, "User");
        List<string> paths = new()
        {
          _finderTests,
          systemTests,
          Path.Combine(systemTests, "Rhinoceros.app"),
          Path.Combine(systemTests, "Rhino 7.app"),
          Path.Combine(systemTests, "Rhino 8.app"),
          Path.Combine(systemTests, "Rhino 9.app"),
          userTests,
          Path.Combine(userTests, "Rhino 10.app")
        };

        foreach (var path in paths)
          Directory.CreateDirectory(path);

        _searchPaths.Add(systemTests);
        _searchPaths.Add(userTests);
      }
    }

    [TearDown]
    public void TearDownSearchPaths()
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        Directory.Delete(_finderTests, recursive: true);
      }
    }

    [Test, TestCase(8), TestCase(9), TestCase(10)]
    public void TestFindMajorRhino(int minMajor)
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        Assert.IsTrue(RhinoFinder.TryFindRhino_macOS(_searchPaths, minMajor, false, out string rhinoPath));
        Assert.IsTrue(rhinoPath.EndsWith($"Rhino {minMajor}.app/Contents/Frameworks"));
      }
      else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        Assert.Ignore();
      }
    }

    [Test, TestCase(8), TestCase(9), TestCase(10)]
    public void TestFindLatestRhino(int minMajor)
    {
      if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
      {
        Assert.IsTrue(RhinoFinder.TryFindRhino_macOS(_searchPaths, minMajor, true, out string rhinoPath));
        Assert.IsTrue(rhinoPath.EndsWith("User/Rhino 10.app/Contents/Frameworks"));
      }
      else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
      {
        Assert.Ignore();
      }
    }
#endif
  }
}
