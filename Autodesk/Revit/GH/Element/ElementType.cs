using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  class ElementType : Element
  {
    public override string TypeName => "Revit ElementType";
    public override string TypeDescription => "Represents a Revit element type";

    public ElementType(Autodesk.Revit.DB.ElementType elementType) : base(elementType) { }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class ElementTypeByName : GH_Component
  {
    public override Guid ComponentGuid => new Guid("7B00F940-4C6E-4F3F-AB81-C3EED430DE96");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("TYPE");

    public ElementTypeByName() : base(
      "ElementType.ByName", "ByName",
      "Select an ElementType from the Revit document",
      "Revit", "Element")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category of the requested element type", GH_ParamAccess.item);
      manager.AddTextParameter("FamilyName", "FN", string.Empty, GH_ParamAccess.item);
      manager.AddTextParameter("Name", "N", string.Empty, GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "ElementType", "ET", "Requested element type", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      if (!DA.GetData("Category", ref category))
        return;

      string familyName = string.Empty;
      DA.GetData("FamilyName", ref familyName);

      string name = string.Empty;
      DA.GetData("Name", ref name);

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        foreach (var elementType in collector.OfClass(typeof(ElementType)).OfCategoryId(category.Id).ToElements().Cast<ElementType>())
        {
          if (elementType.FamilyName == familyName)
          {
            if (elementType.Name == name)
            {
              DA.SetData("ElementType", new Types.ElementType(elementType));
              return;
            }
          }
        }
      }
    }
  }
}
