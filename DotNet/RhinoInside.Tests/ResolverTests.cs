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
    [OneTimeSetUp]
    public void OneTimeSetUpRhinoCore()
    {
      string rhinoPath = Environment.GetEnvironmentVariable("RHINOINSIDE_RHINOPATH");
      Resolver.Initialize(rhinoPath);
    }

    [Test]
    public void TestRhinoCore()
    {
      RhinoCoreUtils.RunRhinoCore();
    }

    [Test]
    public void TestMeshFromBrep()
    {
      Assert.Ignore();
      var p = RunRhinoInsideTest("test_MeshFromBrep");
      Assert.AreEqual(0, p.ExitCode);
    }

    static Process RunRhinoInsideTest(string args)
    {
      var pinfo = new ProcessStartInfo
      {
        FileName = "rhinoinside-testclient",
        Arguments = args
      };

      if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        pinfo.UseShellExecute = false;

      var p = Process.Start(pinfo);
      p.WaitForExit();
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
