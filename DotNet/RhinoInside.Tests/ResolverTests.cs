using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

using NUnit.Framework;

namespace RhinoInside.Tests
{
  [TestFixture]
  public class ResolverTests
  {
    [Test]
    public void TestRhinoCore()
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
      };

      if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        pinfo.UseShellExecute = false;

      var p = Process.Start(pinfo);
      p.WaitForExit();
      return p;
    }
  }
}
