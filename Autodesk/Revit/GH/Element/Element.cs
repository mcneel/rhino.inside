using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using GH_IO.Serialization;

using RhinoInside.Revit;
using Autodesk.Revit.DB;
using System.Windows.Forms;

namespace RhinoInside.Revit.GH.Types
{
  public class Element : ID
  {
    public override string TypeName => "Revit Element";
    public override string TypeDescription => "Represents a Revit element";

    public Element() : base() { }
    public Element(string uniqueId) : base(uniqueId) {}
    public Element(ElementId elementId) : base(elementId.IntegerValue) {}
    public Element(Autodesk.Revit.DB.Element element) : base(element != null ? element.Id.IntegerValue : ElementId.InvalidElementId.IntegerValue) {}
    public static explicit operator Autodesk.Revit.DB.Element(Element self)
    {
      return Revit.ActiveDBDocument.GetElement(self);
    }

    public override bool CastFrom(object source)
    {
      if (source is Autodesk.Revit.DB.Element element)
      {
        Value = element.Id;
        UniqueID = string.Empty;
        return true;
      }

      return base.CastFrom(source);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsSubclassOf(typeof(Autodesk.Revit.DB.Element)))
      {
        target = (Q) (object) (Autodesk.Revit.DB.Element) this;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.Element)))
      {
        target = (Q) (object) (Autodesk.Revit.DB.Element) this;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Element : GH_Param<Types.Element> //GH_PersistentParam<Types.Element>
  {
    public override Guid ComponentGuid => new Guid("F3EA4A9C-B24F-4587-A358-6A7E6D8C028B");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("E");

    public Element() : base("Element", "Element", "Represents a Revit document element.", "Revit", "Element", GH_ParamAccess.item) { }

    #region UI methods
    bool mainWindowVisible = false;
    protected /*override*/ void PrepareForPrompt()
    {
      Grasshopper.Instances.DocumentEditor.FadeOut();
      mainWindowVisible = Rhino.UI.RhinoEtoApp.MainWindow.Visible;
      Rhino.UI.RhinoEtoApp.MainWindow.Visible = false;
    }

    protected /*override*/ void RecoverFromPrompt()
    {
      Rhino.UI.RhinoEtoApp.MainWindow.Visible = mainWindowVisible;
      mainWindowVisible = false;
      Grasshopper.Instances.DocumentEditor.FadeIn();
    }

    protected /*override*/ GH_GetterResult Prompt_Singular(out Types.Element element)
    {
      element = null;

      try
      {
        var reference = Revit.ActiveUIDocument.Selection.PickObject(Autodesk.Revit.UI.Selection.ObjectType.Element);
        if (reference != null)
          element = new Types.Element(reference.ElementId);
      }
      catch (Autodesk.Revit.Exceptions.OperationCanceledException)
      {
        return GH_GetterResult.cancel;
      }

      return GH_GetterResult.success;
    }

    protected /*override*/ GH_GetterResult Prompt_Plural(out List<Types.Element> elements)
    {
      elements = null;

      var selection = Revit.ActiveUIDocument.Selection.GetElementIds();
      if (selection?.Count > 0)
      {
        elements = new List<Types.Element>();
        foreach (var elementId in selection)
          elements.Add(new Types.Element(elementId));
      }
      else
      {
        try
        {
          var references = Revit.ActiveUIDocument.Selection.PickObjects(Autodesk.Revit.UI.Selection.ObjectType.Element);
          if (references?.Count > 0)
          {
            elements = new List<Types.Element>();
            foreach (var reference in references)
              elements.Add(new Types.Element(reference.ElementId));
          }
        }
        catch (Autodesk.Revit.Exceptions.OperationCanceledException)
        {
          return GH_GetterResult.cancel;
        }
      }
      return GH_GetterResult.success;
    }

    private void Menu_PromptSingular(object sender, EventArgs e)
    {
      try
      {
        PrepareForPrompt();

        if (Prompt_Singular(out var element) == GH_GetterResult.success)
          selection = new List<Types.Element>() { element };
      }
      finally
      {
        RecoverFromPrompt();
      }

      ExpireSolution(true);
    }

    private void Menu_PromptPlural(object sender, EventArgs e)
    {
      try
      {
        PrepareForPrompt();

        if (Prompt_Plural(out var elements) == GH_GetterResult.success)
          selection = elements;
      }
      finally
      {
        RecoverFromPrompt();
      }
      ExpireSolution(true);
    }

    private void Menu_ClearValues(object sender, EventArgs e)
    {
      selection = null;
      ExpireSolution(true);
    }

    public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
    {
      base.AppendAdditionalMenuItems(menu);
      if (Kind == GH_ParamKind.output)
        return;

      Menu_AppendItem(menu, string.Format("Set one {0}", TypeName), Menu_PromptSingular, SourceCount == 0, false);
      Menu_AppendItem(menu, string.Format("Set Multiple {0}", TypeName), Menu_PromptPlural, SourceCount == 0, false);
      Menu_AppendSeparator(menu);
      Menu_AppendItem(menu, "Clear values", Menu_ClearValues, SourceCount == 0, false);
      Menu_AppendSeparator(menu);
    }

    List<Types.Element> selection;
    protected sealed override void CollectVolatileData_Custom()
    {
      if (selection != null && selection.Count > 0)
      {
        ClearData();
        AddVolatileDataList(new Grasshopper.Kernel.Data.GH_Path(0), selection);
      }
    }
    #endregion
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public abstract class ElementGetter : GH_Component
  {
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected static readonly Type ObjectType = typeof(Types.Element);
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon(ObjectType.Name.Substring(0, 1));

    protected ElementGetter(string propertyName)
      : base(ObjectType.Name + "." + propertyName, propertyName, "Get the " + propertyName + " of the specified " + ObjectType.Name, "Revit", ObjectType.Name)
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), ObjectType.Name, ObjectType.Name.Substring(0, 1), ObjectType.Name + " to query", GH_ParamAccess.item);
    }
  }

  public class ElementName : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("287A772F-6700-4A67-9E93-CD8B0A60F773");
    static readonly string PropertyName = "Name";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("ABC");

    public ElementName() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter(PropertyName, PropertyName.Substring(0, 1), ObjectType.Name + " " + PropertyName.ToLower(), GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      DA.SetData(PropertyName, element?.Name);
    }
  }

  public class ElementCategory : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("B7BA88B6-672E-4E26-BEEB-ABC069EF6D74");
    static readonly string PropertyName = "Category";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("<>");

    public ElementCategory() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter(PropertyName, PropertyName.Substring(0, 1), ObjectType.Name + " " + PropertyName.ToLower(), GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      DA.SetData(PropertyName, element?.Category.Name);
    }
  }

  public class ElementParameters : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("44515A6B-84EE-4DBD-8241-17EDBE07C5B6");
    static readonly string PropertyName = "Parameters";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{");

    public ElementParameters() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Names", "N", ObjectType.Name + " parameter names", GH_ParamAccess.list);
      manager.AddTextParameter("Values", "V", ObjectType.Name + " parameter values", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      List<string> paramNames = null;
      List<string> paramValues = null;

      if (element != null)
      {
        paramNames  = new List<string>(element.Parameters.Size);
        paramValues = new List<string>(element.Parameters.Size);

        foreach (var param in element.Parameters.Cast<Parameter>())
        {
          paramNames.Add(param.Definition.Name);
          paramValues.Add(param.AsValueString());
        }
      }

      DA.SetDataList("Names", paramNames);
      DA.SetDataList("Values", paramValues);
    }
  }

  public class ElementLocation : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("8E129C01-602B-4A3D-8DFD-F1B590F024AD");
    static readonly string PropertyName = "Location";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("L");

    public ElementLocation() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddGeometryParameter("Location", "L", ObjectType.Name + " parameter names", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      var scaleFactor = Revit.ModelUnits;

      switch (element.Location)
      {
        case Autodesk.Revit.DB.LocationPoint pointLocation:
          var p = pointLocation.Point.ToRhino();

          if (scaleFactor != 1.0)
            p.Scale(scaleFactor);

          DA.SetData("Location", p);
          break;
        case Autodesk.Revit.DB.LocationCurve curveLocation:
          var c = curveLocation.Curve.ToRhino();

          if (scaleFactor != 1.0)
            c.Scale(scaleFactor);

          DA.SetData("Location", c);
          break;
      }
    }
  }

  public class ElementGeometry : ElementGetter
  {
    public override Guid ComponentGuid => new Guid("B7E6A82F-684F-4045-A634-A4AA9F7427A8");
    static readonly string PropertyName = "Geometry";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("G");

    public ElementGeometry() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddGeometryParameter("Geometry", "G", ObjectType.Name + " parameter names", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData(ObjectType.Name, ref element))
        return;

      var options = new Options { ComputeReferences = true };

      using (var geometry = element.get_Geometry(options))
      {
        var list = geometry.ToRhino().Where(x => x != null).ToList();
        DA.SetDataList("Geometry", list);
      }
    }
  }
}
