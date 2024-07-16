using System;

using NUnit.Framework;
using System.Diagnostics;

namespace RhinoInside.Tests
{
  [TestFixture]
  public class ResolverTests
  {
    [Test]
    public void TestRhinoCore()
    {
      var p = RunRhinoInsideTest("mesh-test");
      Assert.AreEqual(0, p.ExitCode);
    }

    static Process RunRhinoInsideTest(string args)
    {
      var pinfo = new ProcessStartInfo
      {
        FileName = "rhinoinside-testclient",
        Arguments = args
      };

      var p = Process.Start(pinfo);
      p.WaitForExit();
      return p;
    }
  }
}
