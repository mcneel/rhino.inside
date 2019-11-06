using System;
using System.Collections.Generic;
using System.Linq;
using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;
using Autodesk.Revit.UI.Events;
using Grasshopper;
using Grasshopper.Kernel;
using Rhino.PlugIns;

namespace RhinoInside.Revit.UI
{
  abstract public class GrasshopperCommand : RhinoCommand
  {
    protected static readonly Guid PluginId = new Guid(0xB45A29B1, 0x4343, 0x4035, 0x98, 0x9E, 0x04, 0x4E, 0x85, 0x80, 0xD9, 0xCF);
    public GrasshopperCommand()
    {
      if (!PlugIn.LoadPlugIn(PluginId, true, true))
        throw new Exception("Failed to load Grasshopper");

      GH.Guest.Script.LoadEditor();
      if(!GH.Guest.Script.IsEditorLoaded())
        throw new Exception("Failed to startup Grasshopper");
    }

    public new class Availability : RhinoCommand.Availability
    {
      public override bool IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories) =>
        base.IsCommandAvailable(applicationData, selectedCategories) &&
        (PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected) & (loaded | !loadProtected));
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopper : GrasshopperCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var buttonData = NewPushButtonData<CommandGrasshopper, Availability>("Grasshopper");
      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Shows Grasshopper window";
        pushButton.LongDescription = $"Use CTRL key to open only Grasshopper window without restoring other tool windows";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Grasshopper.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.Grasshopper.png");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://www.grasshopper3d.com/"));
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      using (var modal = new Rhinoceros.ModalScope())
      {
        GH.Guest.Script.ShowEditor();

        if(!GH.Guest.Script.IsEditorLoaded())
          return Result.Failed;

        return modal.Run(false);
      }
    }
  }

  #region Solver
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperRecompute : GrasshopperCommand
  {
    public new class Availability : GrasshopperCommand.Availability
    {
      public override bool IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories) =>
        base.IsCommandAvailable(applicationData, selectedCategories) &&
        Instances.ActiveCanvas?.Document != null;
    }

    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      // Create a push button to trigger a command add it to the ribbon panel.
      var buttonData = NewPushButtonData<CommandGrasshopperRecompute, Availability>("Recompute");
      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Force a complete recompute of all objects";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Recompute_24x24.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Recompute_24x24.png");
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      if (Instances.ActiveCanvas?.Document is GH_Document definition)
      {
        using (var modal = new Rhinoceros.ModalScope())
        {
          if(GH_Document.EnableSolutions) definition.NewSolution(true);
          else
          {
            GH_Document.EnableSolutions = true;
            try { definition.NewSolution(false); }
            finally { GH_Document.EnableSolutions = false; }
          }

          do
          {
            var result = modal.Run(false, false);
            if (result == Result.Failed)
              return result;

          } while (definition.ScheduleDelay >= GH_Document.ScheduleRecursive);

          if (definition.SolutionState == GH_ProcessStep.PostProcess)
            return Result.Succeeded;
        }
      }

      return Result.Failed;
    }
  }

  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperBake : GrasshopperCommand
  {
    public new class Availability : GrasshopperCommand.Availability
    {
      public override bool IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories) =>
        base.IsCommandAvailable(applicationData, selectedCategories) &&
        Instances.ActiveCanvas?.Document != null &&
        Instances.ActiveCanvas.Document.SelectedCount > 0;
    }

    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      var items = ribbonPanel.AddStackedItems
      (
        new ComboBoxData("Category"),
        NewPushButtonData<CommandGrasshopperBake, Availability>("Bake Selected")
      );

      if(items[0] is ComboBox comboBox)
      {
        categoriesComboBox = comboBox;
      
        EventHandler<IdlingEventArgs> BuildDirectShapeCategoryList = null;
        Revit.ApplicationUI.Idling += BuildDirectShapeCategoryList = (sender, args) =>
        {
          var doc = (sender as UIApplication)?.ActiveUIDocument.Document;
          if (doc == null)
            return;

          var directShapeCategories = Enum.GetValues(typeof(BuiltInCategory)).Cast<BuiltInCategory>().
          Where(categoryId => DirectShape.IsValidCategoryId(new ElementId(categoryId), doc)).
          Select(categoryId => Autodesk.Revit.DB.Category.GetCategory(doc, categoryId));

          foreach (var group in directShapeCategories.GroupBy(x => x.CategoryType).OrderBy(x => x.Key.ToString()))
          {
            foreach (var category in group.OrderBy(x => x.Name))
            {
              var comboBoxMemberData = new ComboBoxMemberData(((BuiltInCategory) category.Id.IntegerValue).ToString(), category.Name)
              {
                GroupName = group.Key.ToString()
              };
              var item = categoriesComboBox.AddItem(comboBoxMemberData);

              if ((BuiltInCategory) category.Id.IntegerValue == BuiltInCategory.OST_GenericModel)
                categoriesComboBox.Current = item;
            }
          }

          Revit.ApplicationUI.Idling -= BuildDirectShapeCategoryList;
        };
      }

      if (items[1] is PushButton bakeButton)
      {
        bakeButton.ToolTip = "Bake geometry in all selected objects";
        bakeButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Bake_24x24.png", true);
        bakeButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Bake_24x24.png");
        bakeButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);
      }
    }

    static ComboBox categoriesComboBox = null;
    public static BuiltInCategory ActiveBuiltInCategory
    {
      get => Enum.TryParse(categoriesComboBox.Current.Name, out BuiltInCategory builtInCategory) ?
             builtInCategory :
             BuiltInCategory.OST_GenericModel;
    }

    public static void Bake(Document doc, string transactionName, List<KeyValuePair<string, List<Rhino.Geometry.GeometryBase>>> geometryToBake)
    {
      if (geometryToBake.Count > 0)
      {
        using (var trans = new Transaction(doc, transactionName))
        {
          if (trans.Start() == TransactionStatus.Started)
          {
            var categoryId = new ElementId(ActiveBuiltInCategory);

            foreach (var geometry in geometryToBake)
            {
              var ds = DirectShape.CreateElement(doc, categoryId);
              ds.Name = geometry.Key;

              foreach (var geometries in geometry.Value.ToHost())
              {
                if (geometries != null)
                  ds.AppendShape(geometries);
              }
            }

            trans.Commit();
          }
        }
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      if (Instances.ActiveCanvas?.Document is GH_Document definition)
      {
        var paramsToBake =
        definition.SelectedObjects().
        OfType<IGH_ActiveObject>().
        Where(x => !x.Locked && ((x as IGH_BakeAwareObject)?.IsBakeCapable ?? false)).
        SelectMany(x =>
        {
          switch (x)
          {
            case IGH_Component component: return component.Params.Output;
            case IGH_Param param: return Enumerable.Repeat(x, 1);
          }
          return null;
        }).
        OfType<IGH_Param>().
        Where(x => x.VolatileDataCount > 0);

        var geometryToBake = new List<KeyValuePair<string, List<Rhino.Geometry.GeometryBase>>>();

        foreach (var param in paramsToBake)
        {
          var geometryList = new List<Rhino.Geometry.GeometryBase>();
          foreach (var value in param.VolatileData.AllData(true).Select(x => x.ScriptVariable()))
          {
            switch (value)
            {
              case Rhino.Geometry.Point3d point: geometryList.Add(new Rhino.Geometry.Point(point)); break;
              case Rhino.Geometry.GeometryBase geometry: geometryList.Add(geometry); break;
            }
          }

          if (geometryList.Count > 0)
            geometryToBake.Add(new KeyValuePair<string, List<Rhino.Geometry.GeometryBase>>(param.NickName, geometryList));
        }

        Bake(data.Application.ActiveUIDocument.Document, "Grasshopper.Bake", geometryToBake);
      }

      return Result.Succeeded;
    }
  }
  #endregion

  #region Preview
  abstract class CommandGrasshopperPreview : GrasshopperCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
#if REVIT_2018
      var radioData = new RadioButtonGroupData("GrasshopperPreview");

      if (ribbonPanel.AddItem(radioData) is RadioButtonGroup radioButton)
      {
        CommandGrasshopperPreviewOff.CreateUI(radioButton);
        CommandGrasshopperPreviewWireframe.CreateUI(radioButton);
        CommandGrasshopperPreviewShaded.CreateUI(radioButton);
      }
#endif
    }

    public new class Availability : RhinoCommand.Availability
    {
      public override bool IsCommandAvailable(UIApplication applicationData, CategorySet selectedCategories)
      {
        return base.IsCommandAvailable(applicationData, selectedCategories) &&
               !applicationData.ActiveUIDocument.Document.IsFamilyDocument;
      }
    }
  }

#if REVIT_2018
  [Transaction(TransactionMode.ReadOnly), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperPreviewOff : CommandGrasshopperPreview
  {
    public static void CreateUI(RadioButtonGroup radioButtonGroup)
    {
      var buttonData = NewToggleButtonData<CommandGrasshopperPreviewOff, Availability>("Off");

      if (radioButtonGroup.AddItem(buttonData) is ToggleButton pushButton)
      {
        pushButton.ToolTip = "Don't draw any preview geometry";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Off_24x24.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Off_24x24.png");
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);

        if (GH.PreviewServer.PreviewMode == GH_PreviewMode.Disabled)
          radioButtonGroup.Current = pushButton;
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      GH.PreviewServer.PreviewMode = GH_PreviewMode.Disabled;
      data.Application.ActiveUIDocument.RefreshActiveView();
      return Result.Succeeded;
    }
  }

  [Transaction(TransactionMode.ReadOnly), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperPreviewWireframe : CommandGrasshopperPreview
  {
    public static void CreateUI(RadioButtonGroup radioButtonGroup)
    {
      var buttonData = NewToggleButtonData<CommandGrasshopperPreviewWireframe, Availability>("Wireframe");

      if (radioButtonGroup.AddItem(buttonData) is ToggleButton pushButton)
      {
        pushButton.ToolTip = "Draw wireframe preview geometry";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Wireframe_24x24.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Wireframe_24x24.png");
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);

        if (GH.PreviewServer.PreviewMode == GH_PreviewMode.Wireframe)
          radioButtonGroup.Current = pushButton;
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      GH.PreviewServer.PreviewMode = GH_PreviewMode.Wireframe;
      data.Application.ActiveUIDocument.RefreshActiveView();
      return Result.Succeeded;
    }
  }

  [Transaction(TransactionMode.ReadOnly), Regeneration(RegenerationOption.Manual)]
  class CommandGrasshopperPreviewShaded : CommandGrasshopperPreview
  {
    public static void CreateUI(RadioButtonGroup radioButtonGroup)
    {
      var buttonData = NewToggleButtonData<CommandGrasshopperPreviewShaded, Availability>("Shaded");

      if (radioButtonGroup.AddItem(buttonData) is ToggleButton pushButton)
      {
        pushButton.ToolTip = "Draw shaded preview geometry";
        pushButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Shaded_24x24.png", true);
        pushButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GH.Toolbar.Preview_Shaded_24x24.png");
        pushButton.Visible = PlugIn.PlugInExists(PluginId, out bool loaded, out bool loadProtected);

        if(GH.PreviewServer.PreviewMode == GH_PreviewMode.Shaded)
          radioButtonGroup.Current = pushButton;
      }
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      GH.PreviewServer.PreviewMode = GH_PreviewMode.Shaded;
      data.Application.ActiveUIDocument.RefreshActiveView();
      return Result.Succeeded;
    }
  }
#endif
  #endregion
}
