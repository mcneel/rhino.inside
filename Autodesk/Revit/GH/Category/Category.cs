using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class Category : ID
  {
    public override string TypeName => "Revit Category";
    public override string TypeDescription => "Represents a Revit Category";

    public Category() : base() { }
    public Category(string uniqueId) : base(uniqueId) { }
    public Category(ElementId elementId) : base(elementId.IntegerValue) { }
    public Category(Autodesk.Revit.DB.Element element) : base(element != null ? element.Id.IntegerValue : ElementId.InvalidElementId.IntegerValue) { }
    public static explicit operator Autodesk.Revit.DB.Category(Category self)
    {
      return Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, self);
    }

    public override bool CastFrom(object source)
    {
      if (source is Autodesk.Revit.DB.Category category)
      {
        Value = category.Id;
        UniqueID = string.Empty;
        return true;
      }
      if (source is GH_Integer builtInCategoryId)
      {
        Value = new ElementId(builtInCategoryId.Value);
        UniqueID = string.Empty;
        return true;
      }
      if (source is string builtInCategory)
      {
        Value = new ElementId((BuiltInCategory) Enum.Parse(typeof(BuiltInCategory), builtInCategory, false));
        UniqueID = string.Empty;
        return true;
      }

      return base.CastFrom(source);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsSubclassOf(typeof(Autodesk.Revit.DB.Category)))
      {
        target = (Q) (object) (Autodesk.Revit.DB.Category) this;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(Autodesk.Revit.DB.Category)))
      {
        target = (Q) (object) (Autodesk.Revit.DB.Category) this;
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
  public abstract class CategoryGetter : GH_Component
  {
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected static readonly Type ObjectType = typeof(Types.Category);
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon(ObjectType.Name.Substring(0, 1));

    protected CategoryGetter(string propertyName)
      : base(ObjectType.Name + "." + propertyName, propertyName, "Get the " + propertyName + " of the specified " + ObjectType.Name, "Revit", ObjectType.Name)
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), ObjectType.Name, ObjectType.Name.Substring(0, 1), ObjectType.Name + " to query", GH_ParamAccess.item);
    }
  }

  public class CategoryName : CategoryGetter
  {
    public override Guid ComponentGuid => new Guid("D794361E-DE8C-4D0A-BC77-52293F27D3AA");
    static readonly string PropertyName = "Name";
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("ABC");

    public CategoryName() : base(PropertyName) { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter(PropertyName, PropertyName.Substring(0, 1), ObjectType.Name + " " + PropertyName.ToLower(), GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData(ObjectType.Name, ref category))
        return;

      DA.SetData(PropertyName, category?.Name);
    }
  }
}
