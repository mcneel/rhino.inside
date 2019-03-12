using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class Category : ID
  {
    public override string TypeName => "Revit Category";
    public override string TypeDescription => "Represents a Revit category";
    override public object ScriptVariable() => (Autodesk.Revit.DB.Category) this;
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Category);
    public static explicit operator Autodesk.Revit.DB.Category(Category self) => Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, self);

    public Category() : base() { }

    public override sealed bool CastFrom(object source)
    {
      Autodesk.Revit.DB.Category category = null;
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      switch (source)
      {
        case Autodesk.Revit.DB.Category c:   category = c; break;
        case Autodesk.Revit.DB.ElementId id: category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, id); break;
        case int integer:                    category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, new ElementId(integer)); break;
        case string uniqueId:
          try
          {
            var id = new ElementId((BuiltInCategory) Enum.Parse(typeof(BuiltInCategory), uniqueId, false));
            category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, id);
          }
          catch (ArgumentException) { }
          break;
      }

      if (ScriptVariableType.IsInstanceOfType(category))
      {
        Value = category.Id;
        UniqueID = Enum.GetName(typeof(BuiltInCategory), Value.IntegerValue) ?? string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      var category = (Autodesk.Revit.DB.Category) this;
      if (category == null)
        return false;

      if (typeof(Q).IsSubclassOf(typeof(Autodesk.Revit.DB.Category)))
      {
        target = (Q) (object) category;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.Category)))
      {
        target = (Q) (object) category;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Category : GH_Param<Types.Category>
  {
    public override Guid ComponentGuid => new Guid("6722C7A5-EFD3-4119-A7FD-6C8BE892FD04");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("C");

    public Category() : base("Category", "Category", "Represents a Revit document category.", "Revit", "Category", GH_ParamAccess.item) { }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class CategoryTypes : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("5FFB1339-8521-44A1-9075-2984637725E9");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("CT");

    public CategoryTypes()
    {
      Category = "Revit";
      SubCategory = "Category";
      Name = "CategoryTypes";
      NickName = "CategoryTypes";
      Description = "Provides a picker of a CategoryType";

      ListItems.Clear();
      ListItems.Add(new GH_ValueListItem("Model",      ((int) Autodesk.Revit.DB.CategoryType.Model).ToString()));
      ListItems.Add(new GH_ValueListItem("Annotation", ((int) Autodesk.Revit.DB.CategoryType.Annotation).ToString()));
      ListItems.Add(new GH_ValueListItem("Analytical", ((int) Autodesk.Revit.DB.CategoryType.AnalyticalModel).ToString()));
    }
  }

  public class CategoryDecompose : GH_Component
  {
    public override Guid ComponentGuid => new Guid("D794361E-DE8C-4D0A-BC77-52293F27D3AA");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("C{");

    public CategoryDecompose()
    : base("Category.Decompose", "Category.Decompose", "Decompose a category", "Revit", "Category")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category to query", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", "Category name", GH_ParamAccess.item);
      manager.AddColourParameter("LineColor", "LC", "Category line color", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Element(), "Material", "M", "Category material", GH_ParamAccess.item);
      manager.AddParameter(new Parameters.Category(), "Parent", "P", "Category parent category", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      DA.SetData("Name", category?.Name);
      DA.SetData("LineColor", category?.LineColor.ToRhino());
      DA.SetData("Material", category?.Material);
      DA.SetData("Parent", category?.Parent);
    }
  }
}
