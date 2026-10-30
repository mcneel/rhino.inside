using System;
using System.Runtime.InteropServices;

namespace RhinoInside.EtoTestApp;

/// <summary>
/// The host's own app object, for <c>--host-app</c>.
/// </summary>
/// <remarks>
/// On Mac it is a plain NSApplication made through the Objective-C runtime: Eto's Mac platform
/// cannot run until Rhino has started .NET's macOS support, so the host cannot use Eto for it.
/// On Windows it is an Eto WPF application, which Rhino then uses rather than making its own.
/// </remarks>
static class HostApplication
{
  /// <summary>
  /// Title of the host's menu bar on Mac, to tell it from Rhino's.
  /// </summary>
  public const string MenuTitle = "Rhino.Inside Test Host";

  const string StartTitle = "Start Rhino";

  static IntPtr s_delegate;
  static IntPtr s_startWindow;
  static Action s_start;

  // Kept alive for as long as the Objective-C runtime may call them.
  static readonly ActionCallback s_startClicked = StartClicked;
  static readonly ActionCallback s_startWindowClosed = (self, selector, notification) => Quit();

  /// <summary>
  /// Creates the host's app object. Call before starting Rhino.
  /// </summary>
  public static void Create()
  {
    if (OperatingSystem.IsWindows())
    {
      _ = new Eto.Forms.Application(Eto.Platforms.Wpf);
      return;
    }

    if (!OperatingSystem.IsMacOS())
      return;

    var app = SharedApplication();
    SendLong(app, "setActivationPolicy:", 0); // NSApplicationActivationPolicyRegular

    // The delegate is weak, so this one is never released.
    s_delegate = Send(Send(Class("NSObject"), "alloc"), "init");
    Send(app, "setDelegate:", s_delegate);

    var mainMenu = NewMenu(MenuTitle);
    var appItem = Send(Send(Class("NSMenuItem"), "alloc"), "init");
    var appMenu = NewMenu(MenuTitle);
    var quit = Send(Send(Class("NSMenuItem"), "alloc"), "initWithTitle:action:keyEquivalent:",
      String("Quit " + MenuTitle), Selector("terminate:"), String("q"));
    Send(appMenu, "addItem:", quit);
    Send(appItem, "setSubmenu:", appMenu);
    Send(mainMenu, "addItem:", appItem);
    Send(app, "setMainMenu:", mainMenu);
  }

  /// <summary>
  /// Lets the process show windows and a Dock icon on Mac.
  /// </summary>
  public static void ShowInDock()
  {
    if (OperatingSystem.IsMacOS())
      SendLong(SharedApplication(), "setActivationPolicy:", 0);
  }

  /// <summary>
  /// Brings the app to the front on Mac; started from a terminal, it would open behind it.
  /// </summary>
  public static void Activate()
  {
    if (OperatingSystem.IsMacOS())
      SendBool(SharedApplication(), "activateIgnoringOtherApps:", true);
  }

  /// <summary>
  /// Shows a window whose button calls <paramref name="start"/>, then runs the host's app until it quits.
  /// Call after <see cref="Create"/>.
  /// </summary>
  public static void RunStartWindow(Action start)
  {
    if (OperatingSystem.IsWindows())
      RunEtoStartWindow(start);
    else if (OperatingSystem.IsMacOS())
      RunMacStartWindow(start);
    else
      throw new PlatformNotSupportedException();
  }

  /// <summary>
  /// Quits the host's app.
  /// </summary>
  public static void Quit()
  {
    if (OperatingSystem.IsMacOS())
      Send(SharedApplication(), "terminate:", IntPtr.Zero);
    else
      Eto.Forms.Application.Instance.Quit();
  }

  static void RunEtoStartWindow(Action start)
  {
    var started = false;
    var button = new Eto.Forms.Button { Text = StartTitle };
    var window = new Eto.Forms.Form { Title = MenuTitle, Padding = 20, Resizable = false, Content = button };
    button.Click += (sender, e) =>
    {
      started = true;
      start();
      window.Close();
    };
    window.Closed += (sender, e) =>
    {
      if (!started)
        Quit();
    };
    window.Show();
    Eto.Forms.Application.Instance.Run();
  }

  static void RunMacStartWindow(Action start)
  {
    s_start = start;
    var target = Send(Send(RegisterStartTarget(), "alloc"), "init");

    // Titled and closable, buffered.
    s_startWindow = objc_msgSend_initWindow(Send(Class("NSWindow"), "alloc"), Selector("initWithContentRect:styleMask:backing:defer:"),
      new CGRect(0, 0, 240, 80), 3, 2, false);
    SendBool(s_startWindow, "setReleasedWhenClosed:", false);
    Send(s_startWindow, "setTitle:", String(MenuTitle));
    Send(s_startWindow, "setDelegate:", target);

    var button = Send(Class("NSButton"), "buttonWithTitle:target:action:", String(StartTitle), target, Selector("start:"));
    objc_msgSend_rect(button, Selector("setFrame:"), new CGRect(60, 24, 120, 32));
    Send(Send(s_startWindow, "contentView"), "addSubview:", button);

    Send(s_startWindow, "center");
    Send(s_startWindow, "makeKeyAndOrderFront:", IntPtr.Zero);
    Activate();
    Send(SharedApplication(), "run");
  }

  static void StartClicked(IntPtr self, IntPtr selector, IntPtr sender)
  {
    s_start();
    // Hidden, not closed, so the window's delegate does not quit.
    Send(s_startWindow, "orderOut:", IntPtr.Zero);
  }

  static IntPtr RegisterStartTarget()
  {
    var cls = objc_allocateClassPair(Class("NSObject"), "RhinoInsideTestHostStartTarget", 0);
    class_addMethod(cls, Selector("start:"), Marshal.GetFunctionPointerForDelegate(s_startClicked), "v@:@");
    class_addMethod(cls, Selector("windowWillClose:"), Marshal.GetFunctionPointerForDelegate(s_startWindowClosed), "v@:@");
    objc_registerClassPair(cls);
    return cls;
  }

  static IntPtr SharedApplication() => Send(Class("NSApplication"), "sharedApplication");

  static IntPtr NewMenu(string title) => Send(Send(Class("NSMenu"), "alloc"), "initWithTitle:", String(title));

  static IntPtr String(string value)
  {
    var utf8 = Marshal.StringToCoTaskMemUTF8(value);
    try
    {
      return Send(Class("NSString"), "stringWithUTF8String:", utf8);
    }
    finally
    {
      Marshal.FreeCoTaskMem(utf8);
    }
  }

  static IntPtr Class(string name) => objc_getClass(name);

  static IntPtr Selector(string name) => sel_registerName(name);

  static IntPtr Send(IntPtr receiver, string selector) => objc_msgSend(receiver, Selector(selector));

  static IntPtr Send(IntPtr receiver, string selector, IntPtr arg) => objc_msgSend(receiver, Selector(selector), arg);

  static IntPtr Send(IntPtr receiver, string selector, IntPtr arg1, IntPtr arg2, IntPtr arg3) => objc_msgSend(receiver, Selector(selector), arg1, arg2, arg3);

  static void SendLong(IntPtr receiver, string selector, long arg) => objc_msgSend_long(receiver, Selector(selector), arg);

  static void SendBool(IntPtr receiver, string selector, bool arg) => objc_msgSend_bool(receiver, Selector(selector), arg);

  delegate void ActionCallback(IntPtr self, IntPtr selector, IntPtr sender);

  [StructLayout(LayoutKind.Sequential)]
  readonly struct CGRect
  {
    readonly double X, Y, Width, Height;

    public CGRect(double x, double y, double width, double height)
    {
      X = x;
      Y = y;
      Width = width;
      Height = height;
    }
  }

  const string ObjC = "/usr/lib/libobjc.A.dylib";

  [DllImport(ObjC)]
  static extern IntPtr objc_getClass(string name);

  [DllImport(ObjC)]
  static extern IntPtr sel_registerName(string name);

  [DllImport(ObjC)]
  static extern IntPtr objc_allocateClassPair(IntPtr superclass, string name, nint extraBytes);

  [DllImport(ObjC)]
  static extern void objc_registerClassPair(IntPtr cls);

  [DllImport(ObjC)]
  [return: MarshalAs(UnmanagedType.I1)]
  static extern bool class_addMethod(IntPtr cls, IntPtr selector, IntPtr implementation, string types);

  [DllImport(ObjC)]
  static extern IntPtr objc_msgSend(IntPtr receiver, IntPtr selector);

  [DllImport(ObjC)]
  static extern IntPtr objc_msgSend(IntPtr receiver, IntPtr selector, IntPtr arg);

  [DllImport(ObjC)]
  static extern IntPtr objc_msgSend(IntPtr receiver, IntPtr selector, IntPtr arg1, IntPtr arg2, IntPtr arg3);

  [DllImport(ObjC, EntryPoint = "objc_msgSend")]
  static extern IntPtr objc_msgSend_initWindow(IntPtr receiver, IntPtr selector, CGRect rect, nuint styleMask, nuint backing, [MarshalAs(UnmanagedType.I1)] bool defer);

  [DllImport(ObjC, EntryPoint = "objc_msgSend")]
  static extern void objc_msgSend_rect(IntPtr receiver, IntPtr selector, CGRect rect);

  [DllImport(ObjC, EntryPoint = "objc_msgSend")]
  static extern void objc_msgSend_long(IntPtr receiver, IntPtr selector, long arg);

  [DllImport(ObjC, EntryPoint = "objc_msgSend")]
  static extern void objc_msgSend_bool(IntPtr receiver, IntPtr selector, [MarshalAs(UnmanagedType.I1)] bool arg);
}
