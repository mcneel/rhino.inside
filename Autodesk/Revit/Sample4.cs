using System;
using System.Reflection;
using System.Diagnostics;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;

using Rhino.Geometry;
using Rhino.PlugIns;
using GH_IO.Serialization;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Parameters;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit
{
  [Transaction(TransactionMode.Manual)]
  [Regeneration(RegenerationOption.Manual)]
  public class Sample4 : IExternalCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var thisAssembly = Assembly.GetExecutingAssembly();

      var buttonData = new PushButtonData("cmdRhinoInsideSample4", "Sample 4", thisAssembly.Location, MethodBase.GetCurrentMethod().DeclaringType.FullName);
      PushButton pushButton = ribbonPanel.AddItem(buttonData) as PushButton;
      pushButton.ToolTip = "Eval a Grasshopper definition";
      pushButton.LargeImage = Revit.GrasshopperLogo;
    }

    public Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      // Load Grasshopper
      PlugIn.LoadPlugIn(new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF));

      string filePath;
      using (OpenFileDialog openFileDialog = new OpenFileDialog())
      {
        openFileDialog.Filter = "Grasshopper Binary (*.gh)|*.gh|Grasshopper Xml (*.ghx)|*.ghx";
        openFileDialog.FilterIndex = 1;
        openFileDialog.RestoreDirectory = true;

        switch(openFileDialog.ShowDialog())
        {
          case DialogResult.OK:     filePath = openFileDialog.FileName; break;
          case DialogResult.Cancel: return Result.Cancelled;
          default:                  return Result.Failed;
        }
      }

      var archive = new GH_Archive();
      if (!archive.ReadFromFile(filePath))
        return Result.Failed;

      var outputs = new List<KeyValuePair<string, List<GeometryBase>>>();
      using (var definition = new GH_Document())
      {
        if (!archive.ExtractObject(definition, "Definition"))
          return Result.Failed;

        foreach (var obj in definition.Objects)
        {
          var param = obj as IGH_Param;
          if (param == null)
            continue;

          if (param.Sources.Count == 0 || param.Recipients.Count != 0)
            continue;

          try
          {
            param.CollectData();
            param.ComputeData();
          }
          catch (Exception e)
          {
            Debug.Fail(e.Source, e.Message);
            param.Phase = GH_SolutionPhase.Failed;
          }

          if (param.Phase == GH_SolutionPhase.Failed)
            return Result.Failed;

          var output = new List<GeometryBase>();
          var volatileData = param.VolatileData;
          for (int p = 0; p < volatileData.PathCount; ++p)
          {
            foreach (var goo in volatileData.get_Branch(p))
            {
              switch (goo)
              {
                case GH_Point point: output.Add(new Rhino.Geometry.Point(point.Value)); break;
                case GH_Curve curve: output.Add(curve.Value); break;
                case GH_Brep brep:   output.Add(brep.Value); break;
                case GH_Mesh mesh:   output.Add(mesh.Value); break;
              }
            }
          }

          if(output.Count > 0)
            outputs.Add(new KeyValuePair<string, List<GeometryBase>>(param.Name, output));
        }
      }

      if (outputs.Count > 0)
      {
        var uiApp = data.Application;
        var doc = uiApp.ActiveUIDocument.Document;

        using (var trans = new Transaction(doc))
        {
          if (trans.Start(MethodBase.GetCurrentMethod().DeclaringType.Name) == TransactionStatus.Started)
          {
            var categoryId = new ElementId(BuiltInCategory.OST_GenericModel);

            foreach (var output in outputs)
            {
              var ds = DirectShape.CreateElement(doc, categoryId);
              ds.Name = output.Key;

              foreach (var geometries in output.Value.ToHost())
              {
                if (geometries != null)
                  ds.AppendShape(geometries);
              }
            }

            trans.Commit();
          }
        }
      }

      return Result.Succeeded;
    }
  }
}
