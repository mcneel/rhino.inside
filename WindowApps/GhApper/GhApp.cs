using System.IO;

namespace GhApper
{
  class GhApp
  {
    string _tempPath;
    const string ghname = "HumanUI_Example.gh";
    Rhino.Runtime.InProcess.RhinoCore _rhinoCore;

    public void Unpack()
    {
      using (var resource = typeof(GhApp).Assembly.GetManifestResourceStream($"GhApper.{ghname}"))
      {
        string dir = Path.GetDirectoryName(typeof(GhApp).Assembly.Location);
        _tempPath = Path.Combine(Path.GetTempPath(), ghname);
        using (var file = new FileStream(_tempPath, FileMode.Create, FileAccess.Write))
        {
          resource.CopyTo(file);
        }
      }
    }

    public void Launch()
    {
      _rhinoCore = new Rhino.Runtime.InProcess.RhinoCore(new string[] { "/NOSPLASH" }, Rhino.Runtime.InProcess.WindowStyle.Hidden);//, Rhino.Runtime.InProcess.WindowStyle.NoWindow);

      if (Rhino.RhinoApp.GetPlugInObject("Grasshopper") is Grasshopper.Plugin.GH_RhinoScriptInterface gh)
      {
        Grasshopper.Instances.AutoShowBanner = false;
        gh.LoadEditor();
        var doc = Grasshopper.Instances.DocumentServer.AddDocument(_tempPath, true);
        doc.NewSolution(true);
      }
    }

    public void Shutdown()
    {
      System.Windows.Forms.Application.Exit();
      File.Delete(_tempPath);
    }
  }
}
