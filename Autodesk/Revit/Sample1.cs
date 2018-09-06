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

namespace RhinoInside
{
  [Transaction(TransactionMode.Manual)]
  [Regeneration(RegenerationOption.Manual)]
  public class Sample1 : IExternalCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var thisAssembly = Assembly.GetExecutingAssembly();

      var buttonData = new PushButtonData("cmdRhinoInsideSample1", "Sample 1", thisAssembly.Location, MethodBase.GetCurrentMethod().DeclaringType.FullName);
      PushButton pushButton = ribbonPanel.AddItem(buttonData) as PushButton;
      pushButton.ToolTip = "Creates a mesh sphere";
      pushButton.LargeImage = Revit._rhinoLogo;
    }
    public Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      // RhinoCommon code
      var sphere = new Sphere(Point3d.Origin, 12);
      var brep = sphere.ToBrep();
      var mp = new MeshingParameters(0.5);
      var meshes = Rhino.Geometry.Mesh.CreateFromBrep(brep, mp);

      // Revit code
      var uiApp = data.Application;
      var doc = uiApp.ActiveUIDocument.Document;

      using (var trans = new Transaction(doc))
      {
        if (trans.Start(MethodBase.GetCurrentMethod().DeclaringType.Name) == TransactionStatus.Started)
        {
          var categoryId = new ElementId(BuiltInCategory.OST_GenericModel);

          var ds = DirectShape.CreateElement(doc, categoryId);
          ds.Name = "Sphere";
          ds.SetShape(Revit.Convert(meshes).ToList());

          trans.Commit();
        }
      }

      return Result.Succeeded;
    }
  }
}
