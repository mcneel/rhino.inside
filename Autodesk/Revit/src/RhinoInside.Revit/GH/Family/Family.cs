using System;
using System.Collections.Generic;
using System.Linq;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class Family : Element
  {
    public override string TypeName => "Revit Family";
    public override string TypeDescription => "Represents a Revit family";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.Family);
    public static explicit operator Autodesk.Revit.DB.Family(Family self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.Family;

    public Family() { }
    public Family(Autodesk.Revit.DB.Family family) : base(family) { }

    public override string ToString()
    {
      if (IsValid)
      {
        var family = (Autodesk.Revit.DB.Family) this;
        if (family is object)
        {
          var ToolTip = string.Empty;
          if (family.FamilyCategory is object)
            ToolTip += $"{family.FamilyCategory.Name} : ";

          if (!string.IsNullOrEmpty(family.Name))
            ToolTip += $"{family.Name} : ";

          return $"{ToolTip}id {family.Id}";
        }
      }

      return base.ToString();
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Family : ElementIdNonGeometryParam<Types.Family>
  {
    public override GH_Exposure Exposure => GH_Exposure.primary;
    public override Guid ComponentGuid => new Guid("3966ADD8-07C0-43E7-874B-6EFF95598EB0");

    public Family() : base("Family", "Family", "Represents a Revit document family.", "Params", "Revit") { }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class FamilyGetTypes : Component
  {
    public override Guid ComponentGuid => new Guid("742836D7-01C4-485A-BFA8-6CDA3F121F7B");
    protected override string IconTag => "T";

    public FamilyGetTypes()
    : base("Family.GetTypes", "Family.GetTypes", "Obtains a set of types that are owned by Family", "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Family(), "Family", "F", "Family to query for its types", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "Types", "T", string.Empty, GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Family family = null;
      if (!DA.GetData("Family", ref family))
        return;

      DA.SetDataList("Types", family?.GetFamilySymbolIds());
    }
  }

  public class FamilyByGeometry : Component, Autodesk.Revit.DB.IFamilyLoadOptions
  {
    public override Guid ComponentGuid => new Guid("82523911-309F-4A66-A4B9-CF21E0AC250E");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    protected override string IconTag => "F";

    public FamilyByGeometry()
    : base("AddFamily.ByGeometry", "Family.ByGeometry", string.Empty, "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      var templatePath = new Grasshopper.Kernel.Parameters.Param_FilePath();
      templatePath.FileFilter = "Revit Family Template (*.rft)|*.rft";
      manager[manager.AddParameter(templatePath, "Template", "T", string.Empty, GH_ParamAccess.item)].Optional = true;

      manager.AddTextParameter("Name", "N", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.Category(), "Category", "C", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager.AddGeometryParameter("Geometry", "G", string.Empty, GH_ParamAccess.list);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Family(), "Family", "F", string.Empty, GH_ParamAccess.item);
    }

    #region Autodesk.Revit.DB.IFamilyLoadOptions
    bool IFamilyLoadOptions.OnFamilyFound(bool familyInUse, out bool overwriteParameterValues)
    {
      overwriteParameterValues = true;
      return true;
    }

    bool IFamilyLoadOptions.OnSharedFamilyFound(Family sharedFamily, bool familyInUse, out FamilySource source, out bool overwriteParameterValues)
    {
      source = FamilySource.Family;
      overwriteParameterValues = true;
      return true;
    }
    #endregion

    public static Dictionary<string, ElementId> GetMaterialIdsByName(Document doc)
    {
      var collector = new FilteredElementCollector(doc);
      return collector.OfClass(typeof(Autodesk.Revit.DB.Material)).OfType<Autodesk.Revit.DB.Material>().
        GroupBy(x => x.Name).
        ToDictionary(x => x.Key, x => x.First().Id);
    }

    static Rhino.Geometry.GeometryBase AsGeometryBase(IGH_GeometricGoo obj)
    {
      var scriptVariable = obj.ScriptVariable();
      switch (scriptVariable)
      {
        case Rhino.Geometry.Point3d point: return new Rhino.Geometry.Point(point);
        case Rhino.Geometry.Line line: return new Rhino.Geometry.LineCurve(line);
        case Rhino.Geometry.Rectangle3d rect: return rect.ToNurbsCurve();
        case Rhino.Geometry.Arc arc: return new Rhino.Geometry.ArcCurve(arc);
        case Rhino.Geometry.Circle circle: return new Rhino.Geometry.ArcCurve(circle);
        case Rhino.Geometry.Ellipse ellipse: return ellipse.ToNurbsCurve();
        case Rhino.Geometry.Box box: return box.ToBrep();
      }

      return (scriptVariable as Rhino.Geometry.GeometryBase)?.DuplicateShallow();
    }

    class PlaneComparer : IComparer<KeyValuePair<double[], SketchPlane>>
    {
      public static PlaneComparer Instance = new PlaneComparer();

      int IComparer<KeyValuePair<double[], SketchPlane>>.Compare(KeyValuePair<double[], SketchPlane> x, KeyValuePair<double[], SketchPlane> y)
      {
        var abcdX = x.Key;
        var abcdY = y.Key;

        const double tol = Rhino.RhinoMath.ZeroTolerance;

        var d = abcdX[3] - abcdY[3];
        if (d < -tol) return -1;
        if (d > +tol) return +1;

        var c = abcdX[2] - abcdY[2];
        if (c < -tol) return -1;
        if (c > +tol) return +1;

        var b = abcdX[1] - abcdY[1];
        if (b < -tol) return -1;
        if (b > +tol) return +1;

        var a = abcdX[0] - abcdY[0];
        if (a < -tol) return -1;
        if (a > +tol) return +1;

        return 0;
      }
    }

    Category MapCategory(Document project, Document family, ElementId categoryId, bool createIfNotExist = false)
    {
      if (-3000000 < categoryId.IntegerValue && categoryId.IntegerValue < -2000000)
        return Autodesk.Revit.DB.Category.GetCategory(family, categoryId);

      try
      {
        if (Autodesk.Revit.DB.Category.GetCategory(project, categoryId) is Category category)
        {
          if (family.OwnerFamily.FamilyCategory.SubCategories.Contains(category.Name) && family.OwnerFamily.FamilyCategory.SubCategories.get_Item(category.Name) is Category subCategory)
            return subCategory;

          if(createIfNotExist)
            return family.Settings.Categories.NewSubcategory(family.OwnerFamily.FamilyCategory, category.Name);
        }
      }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

      return null;
    }

    GraphicsStyle MapGraphicsStyle(Document project, Document family, ElementId graphicsStyleId, bool createIfNotExist = false)
    {
      try
      {
        if (project.GetElement(graphicsStyleId) is GraphicsStyle graphicsStyle)
        {
          if (family.OwnerFamily.FamilyCategory.SubCategories.Contains(graphicsStyle.GraphicsStyleCategory.Name) && family.OwnerFamily.FamilyCategory.SubCategories.get_Item(graphicsStyle.GraphicsStyleCategory.Name) is Category subCategory)
            return subCategory.GetGraphicsStyle(graphicsStyle.GraphicsStyleType);

          if (createIfNotExist)
            return family.Settings.Categories.NewSubcategory(family.OwnerFamily.FamilyCategory, graphicsStyle.GraphicsStyleCategory.Name).
                   GetGraphicsStyle(graphicsStyle.GraphicsStyleType);
        }
      }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

      return null;
    }

    static ElementId MapMaterial(Document project, Document family, ElementId materialId, bool createIfNotExist = false)
    {
      if (project.GetElement(materialId) is Material material)
      {
        using (var collector = new FilteredElementCollector(family).OfClass(typeof(Material)))
        {
          if (collector.ToElements().Cast<Material>().Where(x => x.Name == material.Name).FirstOrDefault() is Material familyMaterial)
            return familyMaterial.Id;
        }

        if (createIfNotExist)
          return Material.Create(family, material.Name);
      }

      return ElementId.InvalidElementId;
    }

    bool Add(Document doc, Document familyDoc, Rhino.Geometry.Brep brep)
    {
      bool isCutting = brep.SolidOrientation == Rhino.Geometry.BrepSolidOrientation.Inward;
      if (isCutting)
        brep.Flip();

      if (brep.ToHost() is Solid solid)
      {
        var element = FreeFormElement.Create(familyDoc, solid);

        if (isCutting)
        {
          element.get_Parameter(BuiltInParameter.ELEMENT_IS_CUTTING).Set(1);
          return true;
        }
        else
        {
          Category familySubCategory = null;
          if
          (
            brep.GetUserElementId(BuiltInParameter.FAMILY_ELEM_SUBCATEGORY.ToString(), out var subCategoryId) &&
            Autodesk.Revit.DB.Category.GetCategory(doc, subCategoryId) is Category subCategory
          )
          {
            if (subCategory.Parent.Id == familyDoc.OwnerFamily.FamilyCategory.Id)
            {
              familySubCategory = MapCategory(doc, familyDoc, subCategoryId, true);
            }
            else
            {
              if (subCategory.Parent is null)
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"'{subCategory.Name}' is not subcategory of '{familyDoc.OwnerFamily.FamilyCategory.Name}'");
              else
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"'{subCategory.Parent.Name} : {subCategory.Name}' is not subcategory of '{familyDoc.OwnerFamily.FamilyCategory.Name}'");
            }
          }

          element.Subcategory = familySubCategory;

          if(brep.GetUserBoolean(BuiltInParameter.IS_VISIBLE_PARAM.ToString(), out var visible))
            element.get_Parameter(BuiltInParameter.IS_VISIBLE_PARAM).Set(visible ? 1 : 0);

          if (brep.GetUserInteger(BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), out var visibility))
            element.get_Parameter(BuiltInParameter.GEOM_VISIBILITY_PARAM).Set(visibility);

          if
          (
            brep.GetUserElementId(BuiltInParameter.MATERIAL_ID_PARAM.ToString(), out var materialId) &&
            MapMaterial(doc, familyDoc, materialId, true) is var familyMaterialId
          )
          {
            element.get_Parameter(BuiltInParameter.MATERIAL_ID_PARAM).Set(familyMaterialId);
          }
        }
      }

      return false;
    }

    void Add(Document doc, Document familyDoc, Rhino.Geometry.Curve curve, List<KeyValuePair<double[], SketchPlane>> planesSet)
    {
      if (curve.TryGetPlane(out var plane))
      {
        var abcd = plane.GetPlaneEquation();
        int index = planesSet.BinarySearch(new KeyValuePair<double[], SketchPlane>(abcd, null), PlaneComparer.Instance);
        if (index < 0)
        {
          var entry = new KeyValuePair<double[], SketchPlane>(abcd, SketchPlane.Create(familyDoc, plane.ToHost()));
          index = ~index;
          planesSet.Insert(index, entry);
        }
        var sketchPlane = planesSet[index].Value;

        GraphicsStyle familyGraphicsStyle = null;
        if
        (
          curve.GetUserElementId(BuiltInParameter.FAMILY_CURVE_GSTYLE_PLUS_INVISIBLE.ToString(), out var graphicsStyleId) &&
          doc.GetElement(graphicsStyleId) is GraphicsStyle graphicsStyle
        )
        {
          if (graphicsStyle.GraphicsStyleCategory.Parent.Id == familyDoc.OwnerFamily.FamilyCategory.Id)
          {
            familyGraphicsStyle = MapGraphicsStyle(doc, familyDoc, graphicsStyleId, true);
          }
          else
          {
            if (graphicsStyle.GraphicsStyleCategory.Parent is null)
              AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"'{graphicsStyle.GraphicsStyleCategory.Name}' is not subcategory of '{familyDoc.OwnerFamily.FamilyCategory.Name}'");
            else
              AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"'{graphicsStyle.GraphicsStyleCategory.Parent.Name} : {graphicsStyle.GraphicsStyleCategory.Name}' is not subcategory of '{familyDoc.OwnerFamily.FamilyCategory.Name}'");
          }
        }

        curve.GetUserBoolean(BuiltInParameter.MODEL_OR_SYMBOLIC.ToString(), out var symbolic);
        curve.GetUserBoolean(BuiltInParameter.IS_VISIBLE_PARAM.ToString(), out var visible, true);
        curve.GetUserInteger(BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), out var visibility, -1);

        foreach (var c in curve.ToHost())
        {
          if (symbolic)
          {
            var element = familyDoc.FamilyCreate.NewSymbolicCurve(c, sketchPlane);
            element.get_Parameter(BuiltInParameter.IS_VISIBLE_PARAM).Set(visible ? 1 : 0);

            if (visibility != -1)
              element.get_Parameter(BuiltInParameter.GEOM_VISIBILITY_PARAM).Set(visibility);

            if (familyGraphicsStyle is object)
              element.Subcategory = familyGraphicsStyle;
          }
          else
          {
            var element = familyDoc.FamilyCreate.NewModelCurve(c, sketchPlane);
            element.get_Parameter(BuiltInParameter.IS_VISIBLE_PARAM).Set(visible ? 1 : 0);

            if (visibility != -1)
              element.get_Parameter(BuiltInParameter.GEOM_VISIBILITY_PARAM).Set(visibility);

            if (familyGraphicsStyle is object)
              element.Subcategory = familyGraphicsStyle;
          }
        }
      }
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var doc = Revit.ActiveDBDocument;
      var scaleFactor = 1.0 / Revit.ModelUnits;

      var templatePath = string.Empty;
      if (!DA.GetData("Template", ref templatePath))
      {
        templatePath = doc.Application.FamilyTemplatePath;

        switch(doc.Application.Language)
        {
          case Autodesk.Revit.ApplicationServices.LanguageType.English_USA: templatePath = System.IO.Path.Combine(templatePath, @"Metric Generic Model"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.German:      templatePath = System.IO.Path.Combine(templatePath, @"Allgemeines Modell"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Spanish:     templatePath = System.IO.Path.Combine(templatePath, @"Modelo genérico métrico"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.French:      templatePath = System.IO.Path.Combine(templatePath, @"Modèle générique métrique"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Italian:     templatePath = System.IO.Path.Combine(templatePath, @"Modello generico metrico"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Simplified: templatePath = System.IO.Path.Combine(templatePath, @"公制常规模型"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Traditional: templatePath = System.IO.Path.Combine(templatePath, @"公制常规模型"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Japanese:    templatePath = System.IO.Path.Combine(templatePath, @"一般モデル(メートル単位)"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Korean:      templatePath = System.IO.Path.Combine(templatePath, @"미터법 일반 모델"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Russian:     templatePath = System.IO.Path.Combine(templatePath, @"Метрическая система, типовая модель"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Czech:       templatePath = System.IO.Path.Combine(templatePath, @"Obecný model"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Polish:      templatePath = System.IO.Path.Combine(templatePath, @"Model ogólny (metryczny)"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Hungarian:   templatePath = System.IO.Path.Combine(templatePath, @"Metric Generic Model"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.Brazilian_Portuguese: templatePath = System.IO.Path.Combine(templatePath, @"Metric Generic Model"); break;
          case Autodesk.Revit.ApplicationServices.LanguageType.English_GB:  templatePath = System.IO.Path.Combine(templatePath, @"Generic Model"); break;
        }
      }

      if (!System.IO.Path.HasExtension(templatePath))
        templatePath += ".rft";

      if (!System.IO.Path.IsPathRooted(templatePath))
        templatePath = System.IO.Path.Combine(doc.Application.FamilyTemplatePath, templatePath);

      var name = string.Empty;
      if (!DA.GetData("Name", ref name))
        return;

      var categoryId = ElementId.InvalidElementId;
      DA.GetData("Category", ref categoryId);

      if(categoryId is null)
        categoryId = ElementId.InvalidElementId;

      var geometry = new List<IGH_GeometricGoo>();
      if (!DA.GetDataList("Geometry", geometry))
        return;

      var family = default(Family);
      using (var collector = new FilteredElementCollector(doc).OfClass(typeof(Family)))
        family = collector.ToElements().Cast<Family>().Where(x => x.Name == name).FirstOrDefault();

      if
      (
        (
          family is null ?
          doc.Application.NewFamilyDocument(templatePath) :
          doc.EditFamily(family)
        )
        is var familyDoc
      )
      {
        using (var transaction = new Transaction(familyDoc))
        {
          transaction.Start(Name);

          using (var collector = new FilteredElementCollector(familyDoc).OfClass(typeof(FreeFormElement)))
            familyDoc.Delete(collector.ToElementIds());

          using (var collector = new FilteredElementCollector(familyDoc).OfClass(typeof(CurveElement)))
            familyDoc.Delete(collector.ToElementIds());

          if (categoryId != ElementId.InvalidElementId)
          {
            try { familyDoc.OwnerFamily.FamilyCategoryId = categoryId; }
            catch (Autodesk.Revit.Exceptions.ArgumentException e)
            {
              AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
              return;
            }
          }

          bool hasVoids = false;
          var planesSet = new List<KeyValuePair<double[], SketchPlane>>();
          var planesSetComparer = new PlaneComparer();

          foreach (var geo in geometry.Select(x => AsGeometryBase(x)))
          {
            if (scaleFactor != 1.0)
              geo.Scale(scaleFactor);

            try
            {
              geo.GetUserElementId(BuiltInParameter.FAMILY_CURVE_GSTYLE_PLUS_INVISIBLE.ToString(), out var graphicsStyle);

              switch (geo)
              {
                case Rhino.Geometry.Brep brep:   hasVoids |= Add(doc, familyDoc, brep); break;
                case Rhino.Geometry.Curve curve: Add(doc, familyDoc, curve, planesSet); break;
                default: AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"{geo.GetType().Name} is not supported and will be ignored"); break;
              }
            }
            catch (Autodesk.Revit.Exceptions.InvalidOperationException e)
            {
              AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
            }
          }

          familyDoc.OwnerFamily.get_Parameter(BuiltInParameter.FAMILY_ALLOW_CUT_WITH_VOIDS).Set(hasVoids ? 1 : 0);

          transaction.Commit();
        }

        bool familyIsNew = family is null;

        family = familyDoc.LoadFamily(doc, this);
        familyDoc.Close(false);

        if (familyIsNew)
        {
          using (var transaction = new Transaction(doc))
          {
            transaction.Start(Name);
            try { family.Name = name; }
            catch (Autodesk.Revit.Exceptions.ArgumentException e) { AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, e.Message); }

            if (doc.GetElement(family.GetFamilySymbolIds().First()) is FamilySymbol symbol)
              symbol.Name = name;

            transaction.Commit();
          }
        }
      }

      DA.SetData("Family", family);
    }
  }

  public class FamilyElementByBrep : Component
  {
    public override Guid ComponentGuid => new Guid("8A51D5A1-F463-492B-AE5B-B4F7870D106B");
    public override GH_Exposure Exposure => GH_Exposure.secondary;

    protected override string IconTag => "B";

    public FamilyElementByBrep()
    : base("AddFamilyElement.ByBrep", "FamilyElement.ByBrep", string.Empty, "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", string.Empty, GH_ParamAccess.item);
      manager[manager.AddBooleanParameter("Visible", "V", string.Empty, GH_ParamAccess.item, false)].Optional = true;
      manager[manager.AddParameter(new Parameters.Category(), "Subcategory", "S", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddIntegerParameter("Visibility", "S", string.Empty, GH_ParamAccess.item, -1)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Material", "M", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddBrepParameter("Brep", "B", string.Empty, GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var brep = default(Rhino.Geometry.Brep);
      if (!DA.GetData("Brep", ref brep))
        return;

      var visible = true;
      if (DA.GetData("Visible", ref visible))
        brep.SetUserString(BuiltInParameter.IS_VISIBLE_PARAM.ToString(), visible ? null : "0");

      var subCategoryId = ElementId.InvalidElementId;
      if(DA.GetData("Subcategory", ref subCategoryId))
        brep.SetUserString(BuiltInParameter.FAMILY_ELEM_SUBCATEGORY.ToString(), subCategoryId.IsValid() ? subCategoryId.ToString() : null);

      var visibility = -1;
      if (DA.GetData("Visibility", ref visibility))
        brep.SetUserString(BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), visibility == -1 ? null : visibility.ToString());

      var materialId = ElementId.InvalidElementId;
      if(DA.GetData("Material", ref materialId))
        brep.SetUserString(BuiltInParameter.MATERIAL_ID_PARAM.ToString(), materialId.IsValid() ? materialId.ToString() : null);

      DA.SetData("Brep", brep);
    }
  }

  public class FamilyElementByCurve : Component
  {
    public override Guid ComponentGuid => new Guid("6FBB9200-D725-4A0D-9360-89ACBE5B4D9F");
    public override GH_Exposure Exposure => GH_Exposure.secondary;

    protected override string IconTag => "C";

    public FamilyElementByCurve()
    : base("AddFamilyElement.ByCurve", "FamilyElement.ByCurve", string.Empty, "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddCurveParameter("Curve", "C", string.Empty, GH_ParamAccess.item);
      manager[manager.AddBooleanParameter("Visible", "V", string.Empty, GH_ParamAccess.item, true)].Optional = true;
      manager[manager.AddParameter(new Parameters.GraphicsStyle(), "Subcategory", "S", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddIntegerParameter("Visibility", "S", string.Empty, GH_ParamAccess.item, -1)].Optional = true;
      manager[manager.AddBooleanParameter("Symbolic", "S", string.Empty, GH_ParamAccess.item, false)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddCurveParameter("Curve", "C", string.Empty, GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var curve = default(Rhino.Geometry.Curve);
      if (!DA.GetData("Curve", ref curve))
        return;

      var visible = true;
      if (DA.GetData("Visible", ref visible))
        curve.SetUserString(BuiltInParameter.IS_VISIBLE_PARAM.ToString(), visible ? null : "0");

      var subCategoryId = ElementId.InvalidElementId;
      if(DA.GetData("Subcategory", ref subCategoryId))
        curve.SetUserString(BuiltInParameter.FAMILY_CURVE_GSTYLE_PLUS_INVISIBLE.ToString(), subCategoryId.IsValid() ? subCategoryId.ToString() : null);

      var visibility = -1;
      if (DA.GetData("Visibility", ref visibility))
        curve.SetUserString(BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), visibility == -1 ? null : visibility.ToString());

      var symbolic = false;
      if (DA.GetData("Symbolic", ref symbolic))
        curve.SetUserString(BuiltInParameter.MODEL_OR_SYMBOLIC.ToString(), symbolic ? "1" : null);

      DA.SetData("Curve", curve);
    }
  }
}
