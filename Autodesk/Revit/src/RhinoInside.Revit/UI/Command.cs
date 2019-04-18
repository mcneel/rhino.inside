using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;

namespace RhinoInside.Revit.UI
{
  static class Extension
  {
    internal static PushButton AddPushButton(this PulldownButton pullDownButton, Type commandType, string text = default(string), string tooltip = default(string), Type availability = null)
    {
      // Create a push button to trigger a command and add it to the pull down button.
      var thisAssembly = Assembly.GetExecutingAssembly();
      var buttonData = new PushButtonData("cmdRhinoInside." + commandType.Name, text ?? commandType.Name, thisAssembly.Location, commandType.FullName);

      if (pullDownButton.AddPushButton(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = tooltip;
        if (availability != null)
          pushButton.AvailabilityClassName = availability.FullName;

        return pushButton;
      }

      return null;
    }
  }

  abstract public class Command : IExternalCommand
  {
    internal class AllwaysAvailable : IExternalCommandAvailability
    {
      bool IExternalCommandAvailability.IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories) => true;
    }

    public abstract Result Execute(ExternalCommandData data, ref string message, ElementSet elements);
  }
}
