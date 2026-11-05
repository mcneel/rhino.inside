using System;
using Eto.Drawing;
using Eto.Forms;
using Rhino;
using Rhino.UI;

namespace RhinoInside.EtoTestApp;

/// <summary>
/// The host's window: runs Rhino commands and opens Rhino's own UI from outside Rhino.
/// </summary>
sealed class HostForm : Form
{
  readonly TextBox _command = new TextBox { PlaceholderText = "Command or script, e.g. _Circle 0 10" };
  readonly TextArea _output = new TextArea { ReadOnly = true, Font = Eto.Drawing.Fonts.Monospace(SystemFonts.Default().Size) };
  RhinoDoc _headlessDoc;

  public HostForm(Options options)
  {
    Title = HostApplication.MenuTitle;
    ClientSize = new Size(640, 420);

    // What Rhino did, not what was asked for: it falls back to headless when it cannot show its UI.
    var ui = RhinoApp.IsRunningHeadless
      ? (options.Headless ? "headless" : "headless (full UI was asked for)")
      : "full UI";
    var mode = $"Rhino {RhinoApp.Version}, {ui}, "
      + (options.HostApp ? "the host owns the app" : "Rhino owns the app")
      + (options.LateStart ? ", started after the host" : "");

    var run = new Button { Text = "Run" };
    run.Click += (sender, e) => RunScript(_command.Text);
    _command.KeyDown += (sender, e) =>
    {
      if (e.KeyData == Keys.Enter)
      {
        e.Handled = true;
        RunScript(_command.Text);
      }
    };

    Content = new TableLayout
    {
      Padding = 10,
      Spacing = new Size(5, 5),
      Rows =
      {
        new Label { Text = mode },
        new TableLayout(new TableRow(new TableCell(_command, true), run)) { Spacing = new Size(5, 5) },
        new TableRow(_output) { ScaleHeight = true },
        new StackLayout
        {
          Orientation = Orientation.Horizontal,
          Spacing = 5,
          Items =
          {
            PanelButton("Layers", PanelIds.Layers),
            PanelButton("Properties", PanelIds.ObjectProperties),
            CommandButton("Options", "_Options"),
            ActionButton("Message box", () => Dialogs.ShowMessage("Shown by Rhino, from the host's window.", Title)),
          }
        },
      }
    };

    RhinoApp.CommandWindowCaptureEnabled = true;
  }

  // A headless Rhino has no document of its own to run commands in.
  uint DocumentSerialNumber
  {
    get
    {
      var doc = RhinoDoc.ActiveDoc;
      if (doc == null)
        doc = _headlessDoc ??= RhinoDoc.CreateHeadless(null);
      return doc.RuntimeSerialNumber;
    }
  }

  void RunScript(string script)
  {
    if (string.IsNullOrWhiteSpace(script))
      return;

    bool ok;
    try
    {
      ok = RhinoApp.RunScript(DocumentSerialNumber, script, true);
    }
    catch (Exception ex)
    {
      Log($"{script}: {ex}");
      return;
    }

    foreach (var line in RhinoApp.CapturedCommandWindowStrings(true))
      Log(line.TrimEnd());
    Log($"{script}: {(ok ? "ran" : "failed")}, document has {RhinoDoc.FromRuntimeSerialNumber(DocumentSerialNumber)?.Objects.Count ?? 0} objects");
  }

  void Log(string text) => _output.Append(text + Environment.NewLine, true);

  Button PanelButton(string text, Guid panelId) => ActionButton(text, () => Panels.OpenPanel(panelId));

  Button CommandButton(string text, string script) => ActionButton(text, () => RunScript(script));

  Button ActionButton(string text, Action action)
  {
    var button = new Button { Text = text };
    button.Click += (sender, e) =>
    {
      try
      {
        action();
      }
      catch (Exception ex)
      {
        Log($"{text}: {ex}");
      }
    };
    return button;
  }
}
