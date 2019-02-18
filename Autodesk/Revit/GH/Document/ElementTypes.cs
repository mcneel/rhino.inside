using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class ElementTypeByName : GH_Component
  {
    public override Guid ComponentGuid => new Guid("7B00F940-4C6E-4F3F-AB81-C3EED430DE96");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("{T}");

    public ElementTypeByName() : base(
      "Document.ElementTypes", "ElementTypes",
      "Get active document element types list",
      "Revit", "Document")
    {
    }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager[manager.AddParameter(new Parameters.Category(), "Category", "C", "Category of the requested element type", GH_ParamAccess.item)].Optional = true;
      manager[manager.AddTextParameter("FamilyName", "F", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddTextParameter("TypeName", "N", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "ElementTypes", "T", "Requested element type", GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Category category = null;
      DA.GetData("Category", ref category);

      string familyName = null;
      DA.GetData("FamilyName", ref familyName);

      string name = null;
      DA.GetData("TypeName", ref name);

      var elementTypes = new List<ElementType>();

      using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
      {
        if (category != null)
        {
          foreach (var elementType in collector.WhereElementIsElementType().OfCategoryId(category.Id).ToElements().Cast<ElementType>())
          {
            if (familyName != null && elementType.FamilyName != familyName)
              continue;

            if (name != null && elementType.Name != name)
              continue;

            elementTypes.Add(elementType);
          }
        }
        else
        {
          foreach (var elementType in collector.WhereElementIsElementType().ToElements().Cast<ElementType>())
          {
            if (familyName != null && elementType.FamilyName != familyName)
              continue;

            if (name != null && elementType.Name != name)
              continue;

            elementTypes.Add(elementType);
          }
        }
      }

      DA.SetDataList("ElementTypes", elementTypes);
    }
  }
}
