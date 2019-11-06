using System;
using System.Collections.Generic;
using System.Linq;
using Grasshopper.Kernel;

namespace RhinoInside.Revit.GH.Components
{
  public class MaterialQuanitiesByElement : Component
  {
    public override Guid ComponentGuid => new Guid("8A162EE6-812E-459B-9123-8F7735AAAC0C");

    public MaterialQuanitiesByElement()
    : base("MaterialQuanities.ByElement", "MaterialQuanities", "Query element material information", "Revit", "Materials")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(),  "Element",   "E", "Element to query for its material info", GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.Material(), "Materials", "M", "Materials used to build this element", GH_ParamAccess.list)].Optional = true;
      manager[manager.AddParameter(new Parameters.Material(), "Paint",     "P", "Material used to paint this element",  GH_ParamAccess.list)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddNumberParameter("Volume",   "V", "Material Volume", GH_ParamAccess.list);
      manager.AddNumberParameter("Area",     "A", "Material Area",   GH_ParamAccess.list);
      manager.AddNumberParameter("Painting", "P", "Painting Area",   GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Element element = null;
      if (!DA.GetData("Element", ref element))
        return;

      var materialIds = new List<Autodesk.Revit.DB.ElementId>();
      if (DA.GetDataList("Materials", materialIds))
      {
        DA.SetDataList("Volume", materialIds.Select(x => (element?.GetMaterialVolume(x)).GetValueOrDefault() * Math.Pow(Revit.ModelUnits, 3.0)));
        DA.SetDataList("Area",   materialIds.Select(x => (element?.GetMaterialArea(x, false)).GetValueOrDefault() * Math.Pow(Revit.ModelUnits, 2.0)));
      }

      var paintIds = new List<Autodesk.Revit.DB.ElementId>();
      if (DA.GetDataList("Paint", paintIds))
      {
        try { DA.SetDataList("Painting", paintIds.Select(x => (element?.GetMaterialArea(x, true)).GetValueOrDefault() * Math.Pow(Revit.ModelUnits, 2.0))); }
        catch (Autodesk.Revit.Exceptions.InvalidOperationException e) { AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, e.Message); }
      }
    }
  }

}
