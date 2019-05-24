using System;
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;

using Rhino.Geometry;

using RhinoInside.Revit.UI;

namespace RhinoInside.Revit.Samples
{
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  public class Sample1 : RhinoCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      var buttonData = NewPushButtonData<Sample1, Availability>("Sample 1");

      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Creates a mesh sphere";
        pushButton.Image = ImageBuilder.BuildImage("1");
        pushButton.LargeImage = ImageBuilder.BuildLargeImage("1");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://github.com/mcneel/rhino.inside/blob/master/Autodesk/Revit/README.md#sample-1"));
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      // RhinoCommon code
      var sphere = new Sphere(Point3d.Origin, 12 * Revit.ModelUnits);
      var brep = sphere.ToBrep();
      var mp = MeshingParameters.Default;
      mp.MinimumEdgeLength = Revit.VertexTolerance;
      var meshes = Rhino.Geometry.Mesh.CreateFromBrep(brep, mp);

      // Revit code
      var uiApp = data.Application;
      var doc = uiApp.ActiveUIDocument.Document;

      using (var trans = new Transaction(doc))
      {
        if (trans.Start(MethodBase.GetCurrentMethod().DeclaringType.FullName) == TransactionStatus.Started)
        {
          var categoryId = new ElementId(BuiltInCategory.OST_GenericModel);

          var ds = DirectShape.CreateElement(doc, categoryId);
          ds.Name = "Sphere";
          foreach (var geometryList in meshes.ToHost().ToList())
            ds.AppendShape(geometryList);

          trans.Commit();
        }
      }

      return Result.Succeeded;
    }
  }
}
