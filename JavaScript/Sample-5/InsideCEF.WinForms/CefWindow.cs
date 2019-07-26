using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using CefSharp;
using CefSharp.WinForms;

namespace InsideCEF.WinForms
{
  public partial class CefWindow : Form
  {

    public static ChromiumWebBrowser Browser;
    public Interop Interop;

    public CefWindow()
    {
      InitializeComponent();

      if (!Cef.IsInitialized)
        InitializeCef();

      // initialise one browser instance
      InitializeBrowser();

      Controls.Add(Browser);

    }

    private void InitializeCef()
    {
      Cef.EnableHighDPISupport();

      var assemblyLocation = Assembly.GetExecutingAssembly().Location;
      var assemblyPath = Path.GetDirectoryName(assemblyLocation);
      var pathSubprocess = Path.Combine(assemblyPath, "CefSharp.BrowserSubprocess.exe");
      CefSharpSettings.LegacyJavascriptBindingEnabled = true;
      var settings = new CefSettings
      {
        LogSeverity = LogSeverity.Verbose,
        LogFile = "ceflog.txt",
        BrowserSubprocessPath = pathSubprocess,

      };

      settings.CefCommandLineArgs.Add("allow-file-access-from-files", "1");
      settings.CefCommandLineArgs.Add("disable-web-security", "1");
      Cef.Initialize(settings);

    }

    private void InitializeBrowser()
    {

      var exePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
      var projectRootDir = Directory.GetParent(exePath).Parent.Parent.Parent.FullName;
      var indexPath = Path.Combine(projectRootDir, "InsideCEF.WebApp", "index.html");

      Browser = new ChromiumWebBrowser(indexPath);

      // Allow the use of local resources in the browser
      Browser.BrowserSettings = new BrowserSettings
      {
        FileAccessFromFileUrls = CefState.Enabled,
        UniversalAccessFromFileUrls = CefState.Enabled
      };

      Browser.Dock = System.Windows.Forms.DockStyle.Fill;

      Interop = new Interop(Browser);
      Browser.RegisterAsyncJsObject("Interop", Interop);

      Browser.IsBrowserInitializedChanged += Browser_IsBrowserInitializedChanged;

      Browser.LoadingStateChanged += Browser_LoadingStateChanged;
    }

    private void Browser_IsBrowserInitializedChanged(object sender, IsBrowserInitializedChangedEventArgs e)
    {
      Debug.WriteLine("Browser Initialized");
    }

    private void Browser_LoadingStateChanged(object sender, LoadingStateChangedEventArgs e)
    {
      //Wait for the Page to finish loading
      if (e.IsLoading == false)
      {

        Browser.ShowDevTools();

        Interop.StartGrasshopper(null);
      }
    }

    protected override void OnClosing(CancelEventArgs e)
    {
      Browser.Dispose();
      Cef.Shutdown();

      base.OnClosing(e);
    }
  }
}
