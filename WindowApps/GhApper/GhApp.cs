using System.IO;

namespace GhApper
{
  class GhApp
  {
    const string ghname = "HumanUI_Example.gh";
    Rhino.Runtime.InProcess.RhinoCore _rhinoCore;

    public void Unpack()
    {
      using (var resource = typeof(GhApp).Assembly.GetManifestResourceStream($"GhApper.{ghname}"))
      {
        string dir = Path.GetDirectoryName(typeof(GhApp).Assembly.Location);
        string filename = Path.Combine(dir, ghname);
        using (var file = new FileStream(filename, FileMode.Create, FileAccess.Write))
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
        string dir = Path.GetDirectoryName(typeof(GhApp).Assembly.Location);
        string path = Path.Combine(dir, ghname);
        gh.LoadEditor();
        var doc = Grasshopper.Instances.DocumentServer.AddDocument(path, true);
        doc.NewSolution(true);
      }
    }
  }
}
