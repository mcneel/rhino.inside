using System.Diagnostics;
using System.Threading.Tasks;
using CefSharp;
#if WPF
using CefSharp.Wpf;
#else
using CefSharp.WinForms;
#endif

namespace InsideCEF
{
  /// <summary>
  /// Object which is used to interoperate between Rhino and CEF
  /// </summary>
  public class Interop
  {
    public ChromiumWebBrowser Browser { get; private set; }
    static RhinoInsideTaskManager rhinoInsideTaskManager;

    // default ctor
    public Interop()
    {
      rhinoInsideTaskManager = new RhinoInsideTaskManager(this);
    }

    public Interop(ChromiumWebBrowser browser) : this()
    {
      Browser = browser;
    }

    public void ShowDev()
    {
      Browser.ShowDevTools();
    }

#region To UI (Generic)

    // from https://github.com/speckleworks/SpeckleRhino/blob/dev/SpeckleRhinoPlugin/src/Interop.cs#L340

    public void NotifyFrame(string EventType, string EventInfo)
    {

      var script = string.Format("window.EventBus.$emit('{0}', '{1}')", EventType, EventInfo);
      try
      {
        Browser.GetMainFrame().EvaluateScriptAsync(script);
      }
      catch
      {
        Debug.WriteLine("For some reason, this browser was not initialised.");
      }
    }

#endregion

#region To UI

    public void PushPreview(string data)
    {
      //NotifyFrame("push-preview", data);
      Browser?.GetMainFrame().EvaluateScriptAsync("onGhObjectAdded("+data+");");
    }

#endregion

#region To Rhino

    public async Task<object> StartRhino(dynamic input)
    {
      return await rhinoInsideTaskManager.StartRhinoTask(input);
    }

    public async Task<object> StartGrasshopper(dynamic input)
    {
      return await rhinoInsideTaskManager.StartGrasshopperTask(input);
    }

#endregion

  }
}
