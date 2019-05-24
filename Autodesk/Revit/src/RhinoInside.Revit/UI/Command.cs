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
    internal static PushButton AddPushButton(this RibbonPanel ribbonPanel, Type commandType, string text = null, string tooltip = null, Type availability = null)
    {
      var buttonData = new PushButtonData
      (
        commandType.Name,
        text ?? commandType.Name,
        commandType.Assembly.Location,
        commandType.FullName
      );

      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = tooltip;
        if (availability != null)
          pushButton.AvailabilityClassName = availability.FullName;

        return pushButton;
      }

      return null;
    }

    internal static PushButton AddPushButton(this PulldownButton pullDownButton, Type commandType, string text = null, string tooltip = null, Type availability = null)
    {
      var buttonData = new PushButtonData
      (
        commandType.Name,
        text ?? commandType.Name,
        commandType.Assembly.Location,
        commandType.FullName
      );

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

  abstract public class ExternalCommand : IExternalCommand
  {
    public static PushButtonData NewPushButtonData<CommandType>(string text = null)
    where CommandType : IExternalCommand
    {
      return new PushButtonData
      (
        typeof(CommandType).Name,
        text ?? typeof(CommandType).Name,
        typeof(CommandType).Assembly.Location,
        typeof(CommandType).FullName
      );
    }

    public static PushButtonData NewPushButtonData<CommandType, AvailabilityType>(string text = null)
    where CommandType : IExternalCommand where AvailabilityType : IExternalCommandAvailability
    {
      return new PushButtonData
      (
        typeof(CommandType).Name,
        text ?? typeof(CommandType).Name,
        typeof(CommandType).Assembly.Location,
        typeof(CommandType).FullName
      )
      {
        AvailabilityClassName = typeof(AvailabilityType).FullName
      };
    }

    internal class AllwaysAvailable : IExternalCommandAvailability
    {
      bool IExternalCommandAvailability.IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories) => true;
    }

    public class Availability : IExternalCommandAvailability
    {
      public virtual bool IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories)
      {
        return applicationData?.ActiveUIDocument?.Document?.IsValidObject ?? false;
      }
    }

    public abstract Result Execute(ExternalCommandData data, ref string message, ElementSet elements);
  }
}
