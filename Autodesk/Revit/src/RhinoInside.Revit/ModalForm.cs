using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using Rhino;

namespace RhinoInside.Revit
{
  class ModalForm : System.Windows.Forms.Form
  {
    [DllImport("USER32", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static extern bool ShowOwnedPopups(IntPtr hWnd, [MarshalAs(UnmanagedType.Bool)] bool fShow);
    internal static bool ShowOwnedPopups(bool fShow) => ShowOwnedPopups(RhinoApp.MainWindowHandle(), fShow);

    [DllImport("USER32", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static extern bool IsWindowEnabled(IntPtr hWnd);

    [DllImport("USER32", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static extern bool EnableWindow(IntPtr hWnd, [MarshalAs(UnmanagedType.Bool)] bool bEnable);

    [DllImport("USER32", SetLastError = true)]
    internal static extern IntPtr GetWindow(IntPtr hWnd, int uCmd);
    internal static IntPtr GetEnabledPopup() => GetWindow(RhinoApp.MainWindowHandle(), 6 /*GW_ENABLEDPOPUP*/);

    [DllImport("USER32", SetLastError = true)]
    internal static extern IntPtr SetActiveWindow(IntPtr hWnd);

    [DllImport("USER32", SetLastError = true)]
    internal static extern IntPtr BringWindowToTop(IntPtr hWnd);

    class RevitMainWindow : IWin32Window { IntPtr IWin32Window.Handle => Revit.MainWindowHandle; }
    public static IWin32Window OwnerWindow = new RevitMainWindow();
    public static new ModalForm ActiveForm { get; private set; }
    readonly bool WasEnabled = IsWindowEnabled(Revit.MainWindowHandle);

    public ModalForm()
    {
      EnableWindow(Revit.MainWindowHandle, false);
      ActiveForm = this;
      ShowIcon = false;
      ShowInTaskbar = false;
      BackColor = System.Drawing.Color.White;
      Opacity = 0.1;
      Show(OwnerWindow);
    }

    protected override void Dispose(bool disposing)
    {
      base.Dispose(disposing);
      ActiveForm = null;
      EnableWindow(Revit.MainWindowHandle, WasEnabled);
    }

    protected override bool ShowWithoutActivation => true;
    protected override CreateParams CreateParams
    {
      get
      {
        var createParams = base.CreateParams;
        createParams.Style = 0x00000000;

        using (var mainWindowExtents = Revit.ActiveUIApplication.MainWindowExtents)
        {
          createParams.X = mainWindowExtents.Left;
          createParams.Y = mainWindowExtents.Top;
          createParams.Width = mainWindowExtents.Right - mainWindowExtents.Left;
          createParams.Height = mainWindowExtents.Bottom - mainWindowExtents.Top;
          createParams.Parent = Revit.MainWindowHandle;
        }

        return createParams;
      }
    }

    public class EditScope : IDisposable
    {
      readonly bool WasExposed = Rhino.UI.RhinoEtoApp.MainWindow.Visible;
      readonly bool WasVisible = ActiveForm?.Visible ?? false;
      readonly bool WasEnabled = IsWindowEnabled(Revit.MainWindowHandle);
      public EditScope()
      {
        if (WasVisible) ShowOwnedPopups(false);
        if (WasExposed) Rhino.UI.RhinoEtoApp.MainWindow.Visible = false;
        if (ActiveForm != null) ActiveForm.Visible = false;
        EnableWindow(Revit.MainWindowHandle, true);
      }
      void IDisposable.Dispose()
      {
        EnableWindow(Revit.MainWindowHandle, WasEnabled);
        if (ActiveForm != null) ActiveForm.Visible = WasVisible;
        if (WasExposed) Rhino.UI.RhinoEtoApp.MainWindow.Visible = WasExposed;
        if (WasVisible) ShowOwnedPopups(true);

        var activePopup = GetEnabledPopup();
        if (activePopup == IntPtr.Zero || WasExposed)
          RhinoApp.SetFocusToMainWindow();
        else
          BringWindowToTop(activePopup);
      }
    }

    public static bool ParentEnabled
    {
      get => ActiveForm?.Enabled ?? false;
      set
      {
        if (value)
        {
          if (ActiveForm != null)
            ActiveForm.Enabled = true;

          EnableWindow(Revit.MainWindowHandle, true);
        }
        else
        {
          EnableWindow(Revit.MainWindowHandle, false);

          if (ActiveForm != null)
            ActiveForm.Enabled = false;
        }
      }
    }
  }
}
