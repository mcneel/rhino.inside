using System;
using Eto.Forms;
using Rhino.Runtime.InProcess;
using WindowStyle = Rhino.Runtime.InProcess.WindowStyle;

namespace RhinoInside.EtoTestApp;

/// <summary>
/// Starts Rhino and the host window.
/// </summary>
static class TestApp
{
  public static int Run(Options options)
  {
    if (options.HostApp)
      HostApplication.Create();

    if (options.LateStart)
    {
      RhinoCore lateCore = null;
      HostApplication.RunStartWindow(() => lateCore = Start(options, () =>
      {
        // Nothing returns to dispose it: the host's own loop is still the one running.
        lateCore.Dispose();
        HostApplication.Quit();
      }));
      return 0;
    }

    using var core = Start(options, () => Application.Instance.Quit());
    return core.Run();
  }

  static RhinoCore Start(Options options, Action closed)
  {
    var windowStyle = options.Headless ? WindowStyle.NoWindow : WindowStyle.Normal;
    var core = new RhinoCore(new[] { "/nosplash" }, windowStyle);

    // Headless Rhino keeps the process out of the Dock on Mac, but this host has a window to show.
    HostApplication.ShowInDock();

    var form = new HostForm(options);
    form.Closed += (sender, e) => closed();
    form.Show();
    HostApplication.Activate();

    return core;
  }
}
