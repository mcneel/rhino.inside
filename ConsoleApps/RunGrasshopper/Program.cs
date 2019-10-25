using System;
using Rhino.Geometry;
using GH_IO.Serialization;

namespace RunGrasshopper
{
  class Program
  {
    static Program()
    {
      RhinoInside.Resolver.Initialize();
      //RhinoInside.Resolver.RhinoSystemDirectory = @"C:\dev\github\mcneel\rhino\src4\bin\Debug\";
    }

    static void Main(string[] args)
    {
      using (var core = new Rhino.Runtime.InProcess.RhinoCore())
      {
        RunHelper();
      }
    }

    // Currently need a separate RunHelper function so the .NET runtime won't attempt to load the
    // Grasshopper assembly until after RhinoCore has been created. This should be "fixable" in a
    // future version of the RhinoInside nuget package
    static void RunHelper()
    {
      // Extract definition to sample location as executable
      var assembly = typeof(Program).Assembly;
      string dir = System.IO.Path.GetDirectoryName(assembly.Location);
      string definitionPath = System.IO.Path.Combine(dir, "simple_def.gh");
      using (var resStream = assembly.GetManifestResourceStream("RunGrasshopper.simple_def.gh"))
      using (var outStream = new System.IO.FileStream(definitionPath, System.IO.FileMode.Create))
      {
        resStream.CopyTo(outStream);
      }


      // Start grasshopper in "headless" mode
      var pluginObject = Rhino.RhinoApp.GetPlugInObject("Grasshopper") as Grasshopper.Plugin.GH_RhinoScriptInterface;
      pluginObject.RunHeadless();

      var archive = new GH_Archive();
      archive.ReadFromFile(definitionPath);

      using (var definition = new Grasshopper.Kernel.GH_Document())
      {
        archive.ExtractObject(definition, "Definition");
        foreach(var obj in definition.Objects)
        {
          if (obj is Grasshopper.Kernel.IGH_Param param)
          {
            if (obj.NickName == "CollectMe")
            {
              param.CollectData();
              param.ComputeData();
              foreach (var item in param.VolatileData.AllData(true))
              {
                Line computedLine = Line.Unset;
                if ( item.CastTo(out computedLine) )
                {
                  Console.WriteLine($"Got a line ... {computedLine}");
                }
              }
            }
          }
        }
      }
      Console.WriteLine("Done... press and key to exit");
      Console.ReadKey();
    }
  }
}
