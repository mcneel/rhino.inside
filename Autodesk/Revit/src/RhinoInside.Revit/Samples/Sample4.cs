using System;
using System.Reflection;
using System.Diagnostics;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Globalization;
using System.Windows.Forms;
using System.Windows.Input;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;
using Autodesk.Revit.UI.Selection;

using Rhino.Geometry;
using Rhino.PlugIns;
using GH_IO.Serialization;

using Grasshopper;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Parameters;
using Grasshopper.Kernel.Types;

using Cursor = System.Windows.Forms.Cursor;
using Cursors = System.Windows.Forms.Cursors;

using RhinoInside.Revit.UI;
using Autodesk.Revit.UI.Events;

namespace RhinoInside.Revit.Samples
{
  public abstract class Sample4 : GrasshopperCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      var items = ribbonPanel.AddStackedItems
      (
        new ComboBoxData("Category"),
        new PulldownButtonData("cmdRhinoInside.GrasshopperPlayer", "Grasshopper Player")
      );

      categoriesComboBox = items[0] as Autodesk.Revit.UI.ComboBox;
      if (categoriesComboBox != null)
      {
        categoriesComboBox.ToolTip = "Category where Grasshopper Player will place geometry.";
      }

      mruPullDownButton = items[1] as Autodesk.Revit.UI.PulldownButton;
      if (mruPullDownButton != null)
      {
        mruPullDownButton.ToolTip = "Loads and evals a Grasshopper definition";
        mruPullDownButton.Image = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GrasshopperPlayer.png", true);
        mruPullDownButton.LargeImage = ImageBuilder.LoadBitmapImage("RhinoInside.Resources.GrasshopperPlayer.png");
        mruPullDownButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://github.com/mcneel/rhino.inside/blob/master/Autodesk/Revit/README.md#sample-4"));

        mruPullDownButton.AddPushButton(typeof(Browse), "Browse...", "Browse for a Grasshopper definition to evaluate", typeof(Availability));
      }

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

    public static BuiltInCategory ActiveBuiltInCategory
    {
      get => Enum.TryParse(categoriesComboBox.Current.Name, out BuiltInCategory builtInCategory) ?
             builtInCategory :
             BuiltInCategory.OST_GenericModel;
    }

    static Autodesk.Revit.UI.ComboBox categoriesComboBox = null;
    static PulldownButton mruPullDownButton = null;
    static PushButton[] mruPushPuttons = null;

    const ObjectSnapTypes DefaultSnapTypes =
      ObjectSnapTypes.Endpoints |
      ObjectSnapTypes.Midpoints |
      ObjectSnapTypes.Nearest |
      ObjectSnapTypes.WorkPlaneGrid |
      //ObjectSnapTypes.Intersections |
      ObjectSnapTypes.Centers |
      ObjectSnapTypes.Perpendicular |
      ObjectSnapTypes.Tangents |
      ObjectSnapTypes.Quadrants |
      ObjectSnapTypes.Points;

    bool PickPointOnFace(UIDocument doc, string prompt, out XYZ point, ObjectSnapTypes snapSettings = DefaultSnapTypes)
    {
      point = null;

      if (doc.ActiveView.ViewType != ViewType.ThreeD)
      {
        try { point = doc.Selection.PickPoint(snapSettings, prompt + "Please pick a point on the current work plane"); }
        catch (OperationCanceledException) { }
      }
      else
      {
        var reference = doc.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Face, prompt + "Please select a face to define a work plane");
        if (doc.Document.GetElement(reference.ElementId) is Element element)
        {
          if (element.GetGeometryObjectFromReference(reference) is Face face)
          {
            if (Keyboard.IsKeyDown(Key.LeftCtrl))
            {
              point = face.Evaluate(reference.UVPoint);
            }
            else
            {
              var plane = Autodesk.Revit.DB.Plane.CreateByNormalAndOrigin(face.ComputeNormal(reference.UVPoint), face.Evaluate(reference.UVPoint));

              using (var transaction = new Transaction(doc.Document))
              {
                transaction.Start("PickPointOnFace");

                doc.ActiveView.SketchPlane = SketchPlane.Create(doc.Document, plane);
                doc.ActiveView.ShowActiveWorkPlane();

                try { point = doc.Selection.PickPoint(snapSettings, prompt + "Please pick a point on the defined work plane"); }
                catch (OperationCanceledException) { }

                transaction.RollBack();
              }
            }
          }
        }
      }

      return null != point;
    }

    IEnumerable<IGH_Goo> PromptBox(UIDocument doc, string prompt)
    {
      IGH_Goo goo = null;

      if
      (
        PickPointOnFace(doc, prompt + " : First box corner - ", out var from) &&
        PickPointOnFace(doc, prompt + " : Second box corner - ", out var to)
      )
      {
        var min = new Point3d(Math.Min(from.X, to.X), Math.Min(from.Y, to.Y), Math.Min(from.Z, to.Z));
        var max = new Point3d(Math.Max(from.X, to.X), Math.Max(from.Y, to.Y), Math.Max(from.Z, to.Z));

        goo = new GH_Box(new BoundingBox(min.Scale(Revit.ModelUnits), max.Scale(Revit.ModelUnits)));
      }

      yield return goo;
    }

    IEnumerable<IGH_Goo> PromptPoint(UIDocument doc, string prompt)
    {
      IGH_Goo goo = null;

      if (PickPointOnFace(doc, prompt + " : ", out var point))
        goo = new GH_Point(point.ToRhino().Scale(Revit.ModelUnits));

      yield return goo;
    }

    IEnumerable<IGH_Goo> PromptEdge(UIDocument doc, string prompt)
    {
      IGH_Goo goo = null;

      try
      {
        var reference = doc.Selection.PickObject(ObjectType.Edge, prompt);
        if (reference != null)
        {
          var element = doc.Document.GetElement(reference);
          var edge = element.GetGeometryObjectFromReference(reference) as Edge;
          var curve = edge.AsCurve().ToRhino();
          curve.Scale(Revit.ModelUnits);
          goo = new GH_Curve(curve);
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { }

      yield return goo;
    }

    IEnumerable<IGH_Goo> PromptSurface(UIDocument doc, string prompt)
    {
      try
      {
        var reference = doc.Selection.PickObject(ObjectType.Face, prompt);
        if (reference != null)
        {
          var element = doc.Document.GetElement(reference);
          var face = element.GetGeometryObjectFromReference(reference) as Face;
          var surface = face.ToRhino();
          surface.Scale(Revit.ModelUnits);
          return new GH_Surface[] { new GH_Surface(surface) };
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { }

      return null;
    }

    IEnumerable<IGH_Goo> PromptBrep(UIDocument doc, string prompt)
    {
      try
      {
        var reference = doc.Selection.PickObject(ObjectType.Element, prompt);
        if (reference != null)
        {
          var element = doc.Document.GetElement(reference);

          Options options = null;
          using (var geometry = element.GetGeometry(ViewDetailLevel.Fine, out options)) using (options)
            return geometry.ToRhino().OfType<Brep>().Select((x) => new GH_Brep(x));
        }
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException) { }

      return null;
    }

    bool AddFileToMru(string filePath)
    {
      if (!File.Exists(filePath))
        return false;

      if(mruPushPuttons == null)
      {
        mruPullDownButton.AddSeparator();
        mruPushPuttons = new Type[] { typeof(Mru0), typeof(Mru1), typeof(Mru2), typeof(Mru3), typeof(Mru4), typeof(Mru5) }.
                         Select(x => mruPullDownButton.AddPushButton(x)).ToArray();
        foreach (var mru in mruPushPuttons)
        {
          mru.Visible = false;
          mru.Enabled = false;
        }
      }

      int lastItemToMove = 0;
      for (int m = 0; m < mruPushPuttons.Length; ++m)
      {
        lastItemToMove++;

        if (mruPushPuttons[m].ToolTip == filePath)
          break;
      }

      int itemsToMove = lastItemToMove - 1;
      if (itemsToMove > 0)
      {
        for (int m = lastItemToMove - 1; m > 0; --m)
        {
          mruPushPuttons[m].Visible = mruPushPuttons[m - 1].Visible;
          mruPushPuttons[m].Enabled = mruPushPuttons[m - 1].Enabled;
          mruPushPuttons[m].ToolTipImage = mruPushPuttons[m - 1].ToolTipImage;
          mruPushPuttons[m].LongDescription = mruPushPuttons[m - 1].LongDescription;
          mruPushPuttons[m].ToolTip = mruPushPuttons[m - 1].ToolTip;
          mruPushPuttons[m].ItemText = mruPushPuttons[m - 1].ItemText;
          mruPushPuttons[m].Image = mruPushPuttons[m - 1].Image;
          mruPushPuttons[m].LargeImage = mruPushPuttons[m - 1].LargeImage;
        }

        mruPushPuttons[0].Visible = true;
        mruPushPuttons[0].Enabled = true;
        mruPushPuttons[0].ToolTipImage = null;
        mruPushPuttons[0].LongDescription = string.Empty;
        mruPushPuttons[0].ToolTip = filePath;
        mruPushPuttons[0].ItemText = Path.GetFileNameWithoutExtension(filePath);
        mruPushPuttons[0].Image = ImageBuilder.BuildImage(Path.GetExtension(filePath).Substring(1));
        mruPushPuttons[0].LargeImage = ImageBuilder.BuildLargeImage(Path.GetExtension(filePath).Substring(1));
      }

      return true;
    }

    Result Execute(ExternalCommandData data, ref string message, ElementSet elements, string filePath)
    {
      if (!AddFileToMru(filePath))
        return Result.Failed;

      var application = data.Application;
      var transactionName = string.Empty;
      var outputs = new List<KeyValuePair<string, List<GeometryBase>>>();

      var CurrentCulture = Thread.CurrentThread.CurrentCulture;
      try
      {
        Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;

        var archive = new GH_Archive();
        if (!archive.ReadFromFile(filePath))
          return Result.Failed;

        using (var definition = new GH_Document())
        {
          if (!archive.ExtractObject(definition, "Definition"))
            return Result.Failed;

          // Update Most recet used item extended ToolTip information
          {
            mruPushPuttons[0].LongDescription = definition.Properties.Description;

            if (archive.GetRootNode.FindChunk("Thumbnail")?.GetDrawingBitmap("Thumbnail") is System.Drawing.Bitmap bitmap)
              mruPushPuttons[0].ToolTipImage = bitmap.ToBitmapImage(Math.Min(bitmap.Width, 355), Math.Min(bitmap.Height, 355));
          }

          transactionName = Path.GetFileNameWithoutExtension(definition.Properties.ProjectFileName);

          var inputs = new List<IGH_Param>();

          // Collect input params
          foreach (var obj in definition.Objects)
          {
            if (!(obj is IGH_Param param))
              continue;

            if (param.Sources.Count != 0 || param.Recipients.Count == 0)
              continue;

            if (param.VolatileDataCount > 0)
              continue;

            if (param.Locked)
              continue;

            inputs.Add(param);
          }

          // Prompt for input values
          Thread.CurrentThread.CurrentCulture = CurrentCulture;
          var values = new Dictionary<IGH_Param, IEnumerable<IGH_Goo>>();
          foreach (var input in inputs.OrderBy((x) => x.Attributes.Pivot.Y))
          {
            switch (input)
            {
              case Param_Box box:
                var boxes = PromptBox(application.ActiveUIDocument, input.NickName);
                if (boxes == null)
                  return Result.Cancelled;
                values.Add(input, boxes);
                break;
              case Param_Point point:
                var points = PromptPoint(application.ActiveUIDocument, input.NickName);
                if (points == null)
                  return Result.Cancelled;
                values.Add(input, points);
                break;
              case Param_Curve curve:
                var curves = PromptEdge(application.ActiveUIDocument, input.NickName);
                if (curves == null)
                  return Result.Cancelled;
                values.Add(input, curves);
                break;
              case Param_Surface surface:
                var surfaces = PromptSurface(application.ActiveUIDocument, input.NickName);
                if (surfaces == null)
                  return Result.Cancelled;
                values.Add(input, surfaces);
                break;
              case Param_Brep brep:
                var breps = PromptBrep(application.ActiveUIDocument, input.NickName);
                if (breps == null)
                  return Result.Cancelled;
                values.Add(input, breps);
                break;
            }
          }

          Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;
          try
          {
            Cursor.Current = Cursors.WaitCursor;

            // Update input volatile data values
            foreach (var value in values)
              value.Key.AddVolatileDataList(new Grasshopper.Kernel.Data.GH_Path(0), value.Value);

            // Collect output values
            foreach (var obj in definition.Objects)
            {
              if (!(obj is IGH_Param param))
                continue;

              if (param.Sources.Count == 0 || param.Recipients.Count != 0)
                continue;

              if (param.Locked)
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
              if (volatileData.PathCount > 0)
              {
                foreach (var value in param.VolatileData.AllData(true).Select(x => x.ScriptVariable()))
                {
                  switch (value)
                  {
                    case Rhino.Geometry.Point3d point:          output.Add(new Rhino.Geometry.Point(point)); break;
                    case Rhino.Geometry.GeometryBase geometry:  output.Add(geometry); break;
                  }
                }
              }

              if (output.Count > 0)
                outputs.Add(new KeyValuePair<string, List<GeometryBase>>(param.NickName, output));
            }
          }
          finally
          {
            Cursor.Current = Cursors.Default;
          }
        }
      }
      catch (Exception)
      {
        return Result.Failed;
      }
      finally
      {
        Thread.CurrentThread.CurrentCulture = CurrentCulture;
      }

      // Bake output geometry
      if (outputs.Count > 0)
      {
        var doc = application.ActiveUIDocument.Document;

        using (var trans = new Transaction(doc, transactionName))
        {
          if (trans.Start(MethodBase.GetCurrentMethod().DeclaringType.Name) == TransactionStatus.Started)
          {
            var categoryId = new ElementId(ActiveBuiltInCategory);

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

    [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
    public class Browse : Sample4
    {
      public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
      {
        string filePath;
        using (var openFileDialog = new OpenFileDialog())
        {
          openFileDialog.Filter = "Grasshopper Binary (*.gh)|*.gh|Grasshopper Xml (*.ghx)|*.ghx";
#if DEBUG
          openFileDialog.FilterIndex = 2;
#else
        openFileDialog.FilterIndex = 1;
#endif
          openFileDialog.RestoreDirectory = true;

          switch (openFileDialog.ShowDialog(ModalForm.OwnerWindow))
          {
            case DialogResult.OK: filePath = openFileDialog.FileName; break;
            case DialogResult.Cancel: return Result.Cancelled;
            default: return Result.Failed;
          }
        }

        return Execute(data, ref message, elements, filePath);
      }
    }

    [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
    public class Mru0 : Sample4 { public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements) => Execute(data, ref message, elements, mruPushPuttons[0].ToolTip); }

    [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
    public class Mru1 : Sample4 { public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements) => Execute(data, ref message, elements, mruPushPuttons[1].ToolTip); }

    [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
    public class Mru2 : Sample4 { public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements) => Execute(data, ref message, elements, mruPushPuttons[2].ToolTip); }

    [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
    public class Mru3 : Sample4 { public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements) => Execute(data, ref message, elements, mruPushPuttons[3].ToolTip); }

    [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
    public class Mru4 : Sample4 { public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements) => Execute(data, ref message, elements, mruPushPuttons[4].ToolTip); }

    [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
    public class Mru5 : Sample4 { public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements) => Execute(data, ref message, elements, mruPushPuttons[5].ToolTip); }
  }
}
