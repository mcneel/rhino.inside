using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

using Rhino.Runtime.InProcess;
using NUnit.Framework;

namespace RhinoInside.Tests
{
  [TestFixture]
  public class ResolverTests
  {
    [Test]
    public void TestRhinoCore()
    {
      // ensures this error is detected:
      // Microsoft.macOS: Aborting due to unhandled Objective-C exception: NSWindow should only be instantiated on the main thread!
      string rhinoPath = Environment.GetEnvironmentVariable("RHINOINSIDE_RHINOPATH");
      TestContext.WriteLine($"Testing Load Rhino @ {rhinoPath}");
      Resolver.Initialize(rhinoPath);
      RhinoCoreUtils.RunRhinoCore();
    }

    [Test]
    public void TestMeshFromBrep()
    {
      var p = RunRhinoInsideTest("test_MeshFromBrep");
      Assert.AreEqual(0, p.ExitCode);
    }

    static Process RunRhinoInsideTest(string args)
    {
      var pinfo = new ProcessStartInfo
      {
        FileName = "rhinoinside-testclient",
        Arguments = args
        // RedirectStandardError = true,
      };

      string rhinoPath = Environment.GetEnvironmentVariable("RHINOINSIDE_RHINOPATH");
      pinfo.Environment.Add("RHINOINSIDE_RHINOPATH", rhinoPath);

      if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        pinfo.UseShellExecute = false;

      var p = Process.Start(pinfo);
      p.WaitForExit();

      // if (p.ExitCode > 0)
      // {
      //   TestContext.WriteLine(p.StandardError.ReadToEnd());
      // }

      return p;
    }
  }

  static class RhinoCoreUtils
  {
    public static void RunRhinoCore()
    {
      using (new RhinoCore())
      {
      }
    }
  }
}
