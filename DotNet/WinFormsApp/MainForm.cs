using System;
using System.Windows.Forms;

namespace WinFormsApp
{
  public partial class MainForm : Form
  {
    Rhino.Runtime.InProcess.RhinoCore _rhinoCore;
    public MainForm()
    {
      InitializeComponent();
    }

    protected override void OnHandleCreated(EventArgs e)
    {
      // This is a good spot to start Rhino.Inside as we now have a
      // handle to the top level parent window for Rhino
      _rhinoCore = new Rhino.Runtime.InProcess.RhinoCore(new string[] { "-appmode" }, Rhino.Runtime.InProcess.WindowStyle.Hidden, Handle);
      base.OnHandleCreated(e);
    }

    protected override void OnHandleDestroyed(EventArgs e)
    {
      _rhinoCore.Dispose();
      _rhinoCore = null;
      base.OnHandleDestroyed(e);
    }

    protected override void OnLoad(EventArgs e)
    {
      base.OnLoad(e);
      var displayModes = Rhino.Display.DisplayModeDescription.GetDisplayModes();
      foreach (var mode in displayModes)
      {
        var item = viewToolStripMenuItem.DropDownItems.Add(mode.EnglishName);
        item.Click += (s, evt) =>
        {
          viewportControl1.Viewport.DisplayMode = mode;
          viewportControl1.Invalidate();
        };
      }
    }

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      var ofd = new OpenFileDialog();
      ofd.Filter = "Rhino file (*.3dm) | *.3dm";
      if (ofd.ShowDialog(this) == DialogResult.OK)
      {
        UseWaitCursor = true;
        // Set the document modified flag to false so an invisible
        // Rhino doesn't try to prompt the user to save the document.
        Rhino.RhinoDoc.ActiveDoc.Modified = false;
        // Open the 3dm file
        Rhino.RhinoDoc.Open(ofd.FileName, out bool alreadyOpen);
        Text = $"Rhino.Inside ({ofd.FileName})";
        // By now the viewport control lost it connection to the previous document.
        // So rebuild the viewport control.
        RebuildViewportControl();
        // Zoom and refresh.
        viewportControl1.Viewport.ZoomExtents();
        viewportControl1.Refresh();
        UseWaitCursor = false;
      }
    }

    private void RebuildViewportControl()
    {
      // There is probably a more elegant way of doing this...

      SuspendLayout();
      Controls.Remove(viewportControl1);

      viewportControl1 = new RhinoWindows.Forms.Controls.ViewportControl();
      viewportControl1.Anchor = ((System.Windows.Forms.AnchorStyles) ((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
         | System.Windows.Forms.AnchorStyles.Left)
         | System.Windows.Forms.AnchorStyles.Right)));
      viewportControl1.Location = new System.Drawing.Point(12, 27);
      viewportControl1.Name = "viewportControl1";
      viewportControl1.Size = new System.Drawing.Size(776, 411);
      viewportControl1.TabIndex = 0;
      viewportControl1.Text = "viewportControl1";

      Controls.Add(viewportControl1);

      ResumeLayout(false);
      PerformLayout();

      viewportControl1.Invalidate();
    }
  }
}
