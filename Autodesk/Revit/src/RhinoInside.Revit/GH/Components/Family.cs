using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using DB = Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

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
      DB.Family family = null;
      if (!DA.GetData("Family", ref family))
        return;

      DA.SetDataList("Types", family?.GetFamilySymbolIds());
    }
  }

  #region FamilyLoadOptions
  class FamilyLoadOptions : DB.IFamilyLoadOptions
  {
    public FamilyLoadOptions(bool overrideFamily, bool overrideParameters)
    {
      OverrideFamily = overrideFamily;
      OverrideParameters = overrideParameters;
    }

    readonly bool OverrideFamily;
    readonly bool OverrideParameters;

    bool DB.IFamilyLoadOptions.OnFamilyFound(bool familyInUse, out bool overwriteParameterValues)
    {
      overwriteParameterValues = !familyInUse | OverrideParameters;
      return !familyInUse | OverrideFamily;
    }

    bool DB.IFamilyLoadOptions.OnSharedFamilyFound(DB.Family sharedFamily, bool familyInUse, out DB.FamilySource source, out bool overwriteParameterValues)
    {
      source = DB.FamilySource.Family;
      overwriteParameterValues = !familyInUse | OverrideParameters;
      return !familyInUse | OverrideFamily;
    }
  }
  #endregion

  public class FamilyNew : Component
  {
    public override Guid ComponentGuid => new Guid("82523911-309F-4A66-A4B9-CF21E0AC250E");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    protected override string IconTag => "N";

    public FamilyNew()
    : base("Family.New", "Family.New", "Creates a new Family from a template.", "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      var templatePath = new Grasshopper.Kernel.Parameters.Param_FilePath();
      templatePath.FileFilter = "Family Template Files (*.rft)|*.rft";
      manager[manager.AddParameter(templatePath, "Template", "T", string.Empty, GH_ParamAccess.item)].Optional = true;

      manager.AddBooleanParameter("OverrideFamily", "O", "Override Family", GH_ParamAccess.item, false);
      manager.AddBooleanParameter("OverrideParameters", "O", "Override Parameters", GH_ParamAccess.item, false);

      manager.AddTextParameter("Name", "N", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.Category(), "Category", "C", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddGeometryParameter("Geometry", "G", string.Empty, GH_ParamAccess.list)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Family(), "Family", "F", string.Empty, GH_ParamAccess.item);
    }

    public static Dictionary<string, DB.ElementId> GetMaterialIdsByName(DB.Document doc)
    {
      var collector = new DB.FilteredElementCollector(doc);
      return collector.OfClass(typeof(DB.Material)).OfType<DB.Material>().
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

    class PlaneComparer : IComparer<KeyValuePair<double[], DB.SketchPlane>>
    {
      public static PlaneComparer Instance = new PlaneComparer();

      int IComparer<KeyValuePair<double[], DB.SketchPlane>>.Compare(KeyValuePair<double[], DB.SketchPlane> x, KeyValuePair<double[], DB.SketchPlane> y)
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

    DB.Category MapCategory(DB.Document project, DB.Document family, DB.ElementId categoryId, bool createIfNotExist = false)
    {
      if (-3000000 < categoryId.IntegerValue && categoryId.IntegerValue < -2000000)
        return DB.Category.GetCategory(family, categoryId);

      try
      {
        if (DB.Category.GetCategory(project, categoryId) is DB.Category category)
        {
          if (family.OwnerFamily.FamilyCategory.SubCategories.Contains(category.Name) && family.OwnerFamily.FamilyCategory.SubCategories.get_Item(category.Name) is DB.Category subCategory)
            return subCategory;

          if(createIfNotExist)
            return family.Settings.Categories.NewSubcategory(family.OwnerFamily.FamilyCategory, category.Name);
        }
      }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

      return null;
    }

    DB.GraphicsStyle MapGraphicsStyle(DB.Document project, DB.Document family, DB.ElementId graphicsStyleId, bool createIfNotExist = false)
    {
      try
      {
        if (project.GetElement(graphicsStyleId) is DB.GraphicsStyle graphicsStyle)
        {
          if (family.OwnerFamily.FamilyCategory.SubCategories.Contains(graphicsStyle.GraphicsStyleCategory.Name) && family.OwnerFamily.FamilyCategory.SubCategories.get_Item(graphicsStyle.GraphicsStyleCategory.Name) is DB.Category subCategory)
            return subCategory.GetGraphicsStyle(graphicsStyle.GraphicsStyleType);

          if (createIfNotExist)
            return family.Settings.Categories.NewSubcategory(family.OwnerFamily.FamilyCategory, graphicsStyle.GraphicsStyleCategory.Name).
                   GetGraphicsStyle(graphicsStyle.GraphicsStyleType);
        }
      }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

      return null;
    }

    static DB.ElementId MapMaterial(DB.Document project, DB.Document family, DB.ElementId materialId, bool createIfNotExist = false)
    {
      if (project.GetElement(materialId) is DB.Material material)
      {
        using (var collector = new DB.FilteredElementCollector(family).OfClass(typeof(DB.Material)))
        {
          if (collector.ToElements().Cast<DB.Material>().Where(x => x.Name == material.Name).FirstOrDefault() is DB.Material familyMaterial)
            return familyMaterial.Id;
        }

        if (createIfNotExist)
          return DB.Material.Create(family, material.Name);
      }

      return DB.ElementId.InvalidElementId;
    }

    class DeleteElementEnumerator<T> : IEnumerator<T> where T : DB.Element
    {
      readonly IEnumerator<T> enumerator;
      public DeleteElementEnumerator(IEnumerable<T> e) { enumerator = e.GetEnumerator(); }
      readonly List<DB.Element> elementsToDelete = new List<DB.Element>();

      public void Dispose()
      {
        while (MoveNext()) ;

        foreach (var element in elementsToDelete)
          element.Document.Delete(element.Id);

        enumerator.Dispose();
        DeleteCurrent = false;
      }

      public bool DeleteCurrent;
      public T Current => DeleteCurrent ? enumerator.Current : null;
      object IEnumerator.Current => Current;
      void IEnumerator.Reset() { enumerator.Reset(); DeleteCurrent = false; }
      public bool MoveNext()
      {
        if (DeleteCurrent)
          elementsToDelete.Add(Current);

        return DeleteCurrent = enumerator.MoveNext();
      }
    }

    bool Add
    (
      DB.Document doc,
      DB.Document familyDoc,
      Rhino.Geometry.Brep brep,
      DeleteElementEnumerator<DB.GenericForm> forms
    )
    {
      bool isCutting = brep.SolidOrientation == Rhino.Geometry.BrepSolidOrientation.Inward;
      if (isCutting)
        brep.Flip();

      forms.MoveNext();
      if (brep.ToHost() is DB.Solid solid)
      {
        if (forms.Current is DB.FreeFormElement freeForm)
        {
          freeForm.UpdateSolidGeometry(solid);
          forms.DeleteCurrent = false;
        }
        else freeForm = DB.FreeFormElement.Create(familyDoc, solid);

        if (isCutting)
        {
          freeForm.get_Parameter(DB.BuiltInParameter.ELEMENT_IS_CUTTING).Set(1);
          return true;
        }
        else
        {
          DB.Category familySubCategory = null;
          if
          (
            brep.GetUserElementId(DB.BuiltInParameter.FAMILY_ELEM_SUBCATEGORY.ToString(), out var subCategoryId) &&
            DB.Category.GetCategory(doc, subCategoryId) is DB.Category subCategory
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

          if(familySubCategory is object)
            freeForm.Subcategory = familySubCategory;

          if(brep.GetUserBoolean(DB.BuiltInParameter.IS_VISIBLE_PARAM.ToString(), out var visible))
            freeForm.get_Parameter(DB.BuiltInParameter.IS_VISIBLE_PARAM).Set(visible ? 1 : 0);

          if (brep.GetUserInteger(DB.BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), out var visibility))
            freeForm.get_Parameter(DB.BuiltInParameter.GEOM_VISIBILITY_PARAM).Set(visibility);

          if
          (
            brep.GetUserElementId(DB.BuiltInParameter.MATERIAL_ID_PARAM.ToString(), out var materialId) &&
            MapMaterial(doc, familyDoc, materialId, true) is var familyMaterialId
          )
          {
            freeForm.get_Parameter(DB.BuiltInParameter.MATERIAL_ID_PARAM).Set(familyMaterialId);
          }
        }
      }

      return false;
    }

    void Add
    (
      DB.Document doc,
      DB.Document familyDoc,
      Rhino.Geometry.Curve curve,
      List<KeyValuePair<double[], DB.SketchPlane>> planesSet,
      DeleteElementEnumerator<DB.CurveElement> curves
    )
    {
      if (curve.TryGetPlane(out var plane))
      {
        var abcd = plane.GetPlaneEquation();
        int index = planesSet.BinarySearch(new KeyValuePair<double[], DB.SketchPlane>(abcd, null), PlaneComparer.Instance);
        if (index < 0)
        {
          var entry = new KeyValuePair<double[], DB.SketchPlane>(abcd, DB.SketchPlane.Create(familyDoc, plane.ToHost()));
          index = ~index;
          planesSet.Insert(index, entry);
        }
        var sketchPlane = planesSet[index].Value;

        DB.GraphicsStyle familyGraphicsStyle = null;
        if
        (
          curve.GetUserElementId(DB.BuiltInParameter.FAMILY_CURVE_GSTYLE_PLUS_INVISIBLE.ToString(), out var graphicsStyleId) &&
          doc.GetElement(graphicsStyleId) is DB.GraphicsStyle graphicsStyle
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

        curve.GetUserBoolean(DB.BuiltInParameter.MODEL_OR_SYMBOLIC.ToString(), out var symbolic);
        curve.GetUserBoolean(DB.BuiltInParameter.IS_VISIBLE_PARAM.ToString(), out var visible, true);
        curve.GetUserInteger(DB.BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), out var visibility, -1);

        foreach (var c in curve.ToHostMultiple())
        {
          curves.MoveNext();

          if (symbolic)
          {
            if (curves.Current is DB.SymbolicCurve symbolicCurve && symbolicCurve.GeometryCurve.IsSameKindAs(c))
            {
              symbolicCurve.SetSketchPlaneAndCurve(sketchPlane, c);
              curves.DeleteCurrent = false;
            }
            else symbolicCurve = familyDoc.FamilyCreate.NewSymbolicCurve(c, sketchPlane);

            symbolicCurve.get_Parameter(DB.BuiltInParameter.IS_VISIBLE_PARAM).Set(visible ? 1 : 0);

            if (visibility != -1)
              symbolicCurve.get_Parameter(DB.BuiltInParameter.GEOM_VISIBILITY_PARAM).Set(visibility);

            if (familyGraphicsStyle is object)
              symbolicCurve.Subcategory = familyGraphicsStyle;
          }
          else
          {
            if (curves.Current is DB.ModelCurve modelCurve && modelCurve.GeometryCurve.IsSameKindAs(c))
            {
              modelCurve.SetSketchPlaneAndCurve(sketchPlane, c);
              curves.DeleteCurrent = false;
            }
            else modelCurve = familyDoc.FamilyCreate.NewModelCurve(c, sketchPlane);

            modelCurve.get_Parameter(DB.BuiltInParameter.IS_VISIBLE_PARAM).Set(visible ? 1 : 0);

            if (visibility != -1)
              modelCurve.get_Parameter(DB.BuiltInParameter.GEOM_VISIBILITY_PARAM).Set(visibility);

            if (familyGraphicsStyle is object)
              modelCurve.Subcategory = familyGraphicsStyle;
          }
        }
      }
    }

    static string GetFamilyTemplateFileName(DB.ElementId categoryId, Autodesk.Revit.ApplicationServices.LanguageType language)
    {
      if(categoryId.TryGetBuiltInCategory(out var builtInCategory))
      {
        if(builtInCategory == DB.BuiltInCategory.OST_Mass)
        {
          switch (language)
          {
            case Autodesk.Revit.ApplicationServices.LanguageType.English_USA:           return @"Conceptual Mass\Metric Mass";
            case Autodesk.Revit.ApplicationServices.LanguageType.German:                return @"Entwurfskörper\M_Körper";
            case Autodesk.Revit.ApplicationServices.LanguageType.Spanish:               return @"Masas conceptuales\Masa métrica";
            case Autodesk.Revit.ApplicationServices.LanguageType.French:                return @"Volume conceptuel\Volume métrique";
            case Autodesk.Revit.ApplicationServices.LanguageType.Italian:               return @"Massa concettuale\Massa metrica";
            case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Simplified:    return @"概念体量\公制体量";
            case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Traditional:   return @"概念量體\公制量體";
            case Autodesk.Revit.ApplicationServices.LanguageType.Japanese:              return @"コンセプト マス\マス(メートル単位)";
            case Autodesk.Revit.ApplicationServices.LanguageType.Korean:                return @"개념 질량\미터법 질량";
            case Autodesk.Revit.ApplicationServices.LanguageType.Russian:               return @"Концептуальный формообразующий элемент\Метрическая система, формообразующий элемент";
            case Autodesk.Revit.ApplicationServices.LanguageType.Czech:                 return null;
            case Autodesk.Revit.ApplicationServices.LanguageType.Polish:                return @"Bryła koncepcyjna\Bryła (metryczna)";
            case Autodesk.Revit.ApplicationServices.LanguageType.Hungarian:             return null;
            case Autodesk.Revit.ApplicationServices.LanguageType.Brazilian_Portuguese:  return @"Massa conceitual\Massa métrica";
#if REVIT_2018
            case Autodesk.Revit.ApplicationServices.LanguageType.English_GB:            return @"Conceptual Mass\Mass";
#endif
          }

          return null;
        }
      }

      switch (language)
      {
        case Autodesk.Revit.ApplicationServices.LanguageType.English_USA:         return @"Metric Generic Model";
        case Autodesk.Revit.ApplicationServices.LanguageType.German:              return @"Allgemeines Modell";
        case Autodesk.Revit.ApplicationServices.LanguageType.Spanish:             return @"Modelo genérico métrico";
        case Autodesk.Revit.ApplicationServices.LanguageType.French:              return @"Modèle générique métrique";
        case Autodesk.Revit.ApplicationServices.LanguageType.Italian:             return @"Modello generico metrico";
        case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Simplified:  return @"公制常规模型";
        case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Traditional: return @"公制常规模型";
        case Autodesk.Revit.ApplicationServices.LanguageType.Japanese:            return @"一般モデル(メートル単位)";
        case Autodesk.Revit.ApplicationServices.LanguageType.Korean:              return @"미터법 일반 모델";
        case Autodesk.Revit.ApplicationServices.LanguageType.Russian:             return @"Метрическая система, типовая модель";
        case Autodesk.Revit.ApplicationServices.LanguageType.Czech:               return @"Obecný model";
        case Autodesk.Revit.ApplicationServices.LanguageType.Polish:              return @"Model ogólny (metryczny)";
        case Autodesk.Revit.ApplicationServices.LanguageType.Hungarian:           return null;
        case Autodesk.Revit.ApplicationServices.LanguageType.Brazilian_Portuguese: return @"Modelo genérico métrico";
#if REVIT_2018
        case Autodesk.Revit.ApplicationServices.LanguageType.English_GB:          return @"Generic Model";
#endif
      }

      return null;
    }

    static string GetFamilyTemplateFilePath(DB.ElementId categoryId, Autodesk.Revit.ApplicationServices.Application app)
    {
      string fileName = GetFamilyTemplateFileName(categoryId, app.Language);
      var templateFilePath = fileName is null ? string.Empty : Path.Combine(app.FamilyTemplatePath, $"{fileName}.rft");

      if (File.Exists(templateFilePath))
        return templateFilePath;

      // Emergency template file path
      fileName = GetFamilyTemplateFileName(categoryId, Autodesk.Revit.ApplicationServices.LanguageType.English_USA);
      return Path.Combine
      (
        Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData)),
        "Autodesk",
        $"RVT {app.VersionNumber}",
        "Family Templates",
        "English",
        $"{fileName}.rft"
      );
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var doc = Revit.ActiveDBDocument;
      var scaleFactor = 1.0 / Revit.ModelUnits;

      var overrideFamily = false;
      if (!DA.GetData("OverrideFamily", ref overrideFamily))
        return;

      var overrideParameters = false;
      if (!DA.GetData("OverrideParameters", ref overrideParameters))
        return;

      var name = string.Empty;
      if (!DA.GetData("Name", ref name))
        return;

      var categoryId = DB.ElementId.InvalidElementId;
      DA.GetData("Category", ref categoryId);
      var updateCategory = categoryId != DB.ElementId.InvalidElementId;

      var geometry = new List<IGH_GeometricGoo>();
      var updateGeometry = !(!DA.GetDataList("Geometry", geometry) && Params.Input[Params.IndexOfInputParam("Geometry")].SourceCount == 0);

      var family = default(DB.Family);
      using (var collector = new DB.FilteredElementCollector(doc).OfClass(typeof(DB.Family)))
        family = collector.ToElements().Cast<DB.Family>().Where(x => x.Name == name).FirstOrDefault();

      bool familyIsNew = family is null;

      var templatePath = string.Empty;
      if (familyIsNew)
      {
        if (!DA.GetData("Template", ref templatePath))
          templatePath = GetFamilyTemplateFilePath(categoryId, doc.Application);

        if (!Path.HasExtension(templatePath))
          templatePath += ".rft";

        if (!Path.IsPathRooted(templatePath))
          templatePath = Path.Combine(doc.Application.FamilyTemplatePath, templatePath);
      }
      else
      {
        updateCategory &= family.FamilyCategory.Id != categoryId;
      }

      if (familyIsNew || (overrideFamily && (updateCategory || updateGeometry)))
      {
        try
        {
          if
          (
            (
              familyIsNew ?
              doc.Application.NewFamilyDocument(templatePath) :
              doc.EditFamily(family)
            )
            is var familyDoc
          )
          {
            try
            {
              using (var transaction = new DB.Transaction(familyDoc))
              {
                transaction.Start(Name);

                if (updateCategory && familyDoc.OwnerFamily.FamilyCategoryId != categoryId)
                {
                  try { familyDoc.OwnerFamily.FamilyCategoryId = categoryId; }
                  catch (Autodesk.Revit.Exceptions.ArgumentException e)
                  {
                    AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
                    return;
                  }
                }

                if (updateGeometry)
                {
                  using (var forms = new DeleteElementEnumerator<DB.GenericForm>(new DB.FilteredElementCollector(familyDoc).OfClass(typeof(DB.GenericForm)).Cast<DB.GenericForm>()))
                  using (var curves = new DeleteElementEnumerator<DB.CurveElement>(new DB.FilteredElementCollector(familyDoc).OfClass(typeof(DB.CurveElement)).Cast<DB.CurveElement>()))
                  {
                    bool hasVoids = false;
                    var planesSet = new List<KeyValuePair<double[], DB.SketchPlane>>();
                    var planesSetComparer = new PlaneComparer();

                    foreach (var geo in geometry.Select(x => AsGeometryBase(x).ChangeUnits(scaleFactor)))
                    {
                      try
                      {
                        switch (geo)
                        {
                          case Rhino.Geometry.Brep brep: hasVoids |= Add(doc, familyDoc, brep, forms); break;
                          case Rhino.Geometry.Curve curve: Add(doc, familyDoc, curve, planesSet, curves); break;
                          default: AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"{geo.GetType().Name} is not supported and will be ignored"); break;
                        }
                      }
                      catch (Autodesk.Revit.Exceptions.InvalidOperationException e)
                      {
                        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
                      }
                    }

                    familyDoc.OwnerFamily.get_Parameter(DB.BuiltInParameter.FAMILY_ALLOW_CUT_WITH_VOIDS).Set(hasVoids ? 1 : 0);
                  }
                }

                transaction.Commit();
              }

              family = familyDoc.LoadFamily(doc, new FamilyLoadOptions(overrideFamily, overrideParameters));
            }
            finally
            {
              familyDoc.Close(false);
            }

            if (familyIsNew)
            {
              using (var transaction = new DB.Transaction(doc))
              {
                transaction.Start(Name);
                try { family.Name = name; }
                catch (Autodesk.Revit.Exceptions.ArgumentException e) { AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, e.Message); }

                if (doc.GetElement(family.GetFamilySymbolIds().First()) is DB.FamilySymbol symbol)
                  symbol.Name = name;

                transaction.Commit();
              }
            }
          }
        }
        catch (Autodesk.Revit.Exceptions.ArgumentException e)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
        }
      }
      else if (!overrideFamily)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Remark, $"Family '{name}' already loaded!");
      }

      DA.SetData("Family", family);
    }
  }

  public class FamilyLoad : Component
  {
    public override Guid ComponentGuid => new Guid("0E244846-95AE-4B0E-8218-CB24FD4D34D1");
    protected override string IconTag => "L";

    public FamilyLoad()
    : base("Family.Load", "Family.Load", "Loads a family into the document", "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      var path = new Grasshopper.Kernel.Parameters.Param_FilePath();
      path.FileFilter = "Family File (*.rfa)|*.rfa";
      manager.AddParameter(path, "Path", "P", string.Empty, GH_ParamAccess.item);

      manager.AddBooleanParameter("OverrideFamily", "O", "Override Family", GH_ParamAccess.item, false);
      manager.AddBooleanParameter("OverrideParameters", "O", "Override Parameters", GH_ParamAccess.item, false);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Family(), "Family", "F", string.Empty, GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var filePath = string.Empty;
      if (!DA.GetData("Path", ref filePath))
        return;

      var overrideFamily = false;
      if (!DA.GetData("OverrideFamily", ref overrideFamily))
        return;

      var overrideParameters = false;
      if (!DA.GetData("OverrideParameters", ref overrideParameters))
        return;

      using (var transaction = new DB.Transaction(Revit.ActiveDBDocument))
      {
        transaction.Start(Name);

        if (Revit.ActiveDBDocument.LoadFamily(filePath, new FamilyLoadOptions(overrideFamily, overrideParameters), out var family))
        {
          transaction.Commit();
        }
        else
        {
          var name = Path.GetFileNameWithoutExtension(filePath);
          using (var collector = new DB.FilteredElementCollector(Revit.ActiveDBDocument).OfClass(typeof(DB.Family)))
            family = collector.ToElements().Cast<DB.Family>().Where(x => x.Name == name).FirstOrDefault();

          if (family is object && overrideFamily == false)
            AddRuntimeMessage(GH_RuntimeMessageLevel.Remark, $"Family '{name}' already loaded!");
        }

        DA.SetData("Family", family);
      }
    }
  }

  public class FamilySaveAs : Component
  {
    public override Guid ComponentGuid => new Guid("C2B9B045-8FD2-4124-9294-D9BA809B44B1");
    protected override string IconTag => "S";

    public FamilySaveAs()
    : base("Family.SaveAs", "Family.SaveAs", "Saves the Family to a given file path.", "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Family(), "Family", "F", "Family to save", GH_ParamAccess.item);

      var path = new Grasshopper.Kernel.Parameters.Param_FilePath();
      path.FileFilter = "Family File (*.rfa)|*.rfa";
      manager[manager.AddParameter(path, "Path", "P", string.Empty, GH_ParamAccess.item)].Optional = true;

      manager.AddBooleanParameter("OverrideFile", "O", "Override file on disk", GH_ParamAccess.item, false);
      manager.AddBooleanParameter("Compact", "C", "Compact the file", GH_ParamAccess.item, false);
      manager.AddIntegerParameter("Backups", "B", "The maximum number of backups to keep on disk", GH_ParamAccess.item, -1);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Family(), "Family", "F", string.Empty, GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      DB.Family family = null;
      if (!DA.GetData("Family", ref family))
        return;

      var filePath = string.Empty;
      DA.GetData("Path", ref filePath);

      var overrideFile = false;
      if (!DA.GetData("OverrideFile", ref overrideFile))
        return;

      var compact = false;
      if (!DA.GetData("Compact", ref compact))
        return;

      var backups = -1;
      if (!DA.GetData("Backups", ref backups))
        return;

      if (Revit.ActiveDBDocument.EditFamily(family) is DB.Document familyDoc) using (familyDoc)
      {
        try
        {
          var options = new DB.SaveAsOptions() { OverwriteExistingFile = overrideFile, Compact = compact };
          if (backups > -1)
            options.MaximumBackups = backups;

          if(string.IsNullOrEmpty(filePath))
            filePath = familyDoc.PathName;

          if(string.IsNullOrEmpty(filePath))
            filePath = familyDoc.Title;

          if(Directory.Exists(filePath))
            filePath = Path.Combine(filePath, filePath);

          if (!Path.HasExtension(filePath))
            filePath += ".rfa";

          if(Path.IsPathRooted(filePath))
          {
            familyDoc.SaveAs(filePath, options);
            DA.SetData("Family", family);
          }
          else
          {
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "Path should be absolute.");
          }
        }
        catch(Autodesk.Revit.Exceptions.InvalidOperationException e) { AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message); }
        finally { familyDoc.Close(false); }
      }
      else
      {
        DA.SetData("Family", null);
      }
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
      manager[manager.AddBooleanParameter("Visible", "V", string.Empty, GH_ParamAccess.item, true)].Optional = true;
      manager[manager.AddParameter(new Parameters.Category(), "Subcategory", "S", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddIntegerParameter("Visibility", "S", string.Empty, GH_ParamAccess.item, -1)].Optional = true;
      manager[manager.AddParameter(new Parameters.Material(), "Material", "M", string.Empty, GH_ParamAccess.item)].Optional = true;
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
        brep.SetUserString(DB.BuiltInParameter.IS_VISIBLE_PARAM.ToString(), visible ? null : "0");

      var subCategoryId = DB.ElementId.InvalidElementId;
      if(DA.GetData("Subcategory", ref subCategoryId))
        brep.SetUserString(DB.BuiltInParameter.FAMILY_ELEM_SUBCATEGORY.ToString(), subCategoryId.IsValid() ? subCategoryId.ToString() : null);

      var visibility = -1;
      if (DA.GetData("Visibility", ref visibility))
        brep.SetUserString(DB.BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), visibility == -1 ? null : visibility.ToString());

      var materialId = DB.ElementId.InvalidElementId;
      if(DA.GetData("Material", ref materialId))
        brep.SetUserString(DB.BuiltInParameter.MATERIAL_ID_PARAM.ToString(), materialId.IsValid() ? materialId.ToString() : null);

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
        curve.SetUserString(DB.BuiltInParameter.IS_VISIBLE_PARAM.ToString(), visible ? null : "0");

      var subCategoryId = DB.ElementId.InvalidElementId;
      if(DA.GetData("Subcategory", ref subCategoryId))
        curve.SetUserString(DB.BuiltInParameter.FAMILY_CURVE_GSTYLE_PLUS_INVISIBLE.ToString(), subCategoryId.IsValid() ? subCategoryId.ToString() : null);

      var visibility = -1;
      if (DA.GetData("Visibility", ref visibility))
        curve.SetUserString(DB.BuiltInParameter.GEOM_VISIBILITY_PARAM.ToString(), visibility == -1 ? null : visibility.ToString());

      var symbolic = false;
      if (DA.GetData("Symbolic", ref symbolic))
        curve.SetUserString(DB.BuiltInParameter.MODEL_OR_SYMBOLIC.ToString(), symbolic ? "1" : null);

      DA.SetData("Curve", curve);
    }
  }

  public class VisibilityConstruct : Component
  {
    public override Guid ComponentGuid => new Guid("10EA29D4-16AF-4060-89CE-F467F0069675");
    public override GH_Exposure Exposure => GH_Exposure.secondary;

    protected override string IconTag => "V";

    public VisibilityConstruct()
    : base("Visibility.Construct", "Visibility.Construct", string.Empty, "Revit", "Family")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddBooleanParameter("ViewSpecific", "V", string.Empty, GH_ParamAccess.item, false);
      manager.AddBooleanParameter("PlanRCPCut", "RCP", string.Empty, GH_ParamAccess.item, true);
      manager.AddBooleanParameter("TopBottom", "Z", string.Empty, GH_ParamAccess.item, true);
      manager.AddBooleanParameter("FrontBack", "Y", string.Empty, GH_ParamAccess.item, true);
      manager.AddBooleanParameter("LeftRight", "X", string.Empty, GH_ParamAccess.item, true);
      manager.AddBooleanParameter("OnlyWhenCut", "CUT", string.Empty, GH_ParamAccess.item, false);

      manager.AddBooleanParameter("Coarse", "C", string.Empty, GH_ParamAccess.item, true);
      manager.AddBooleanParameter("Medium", "M", string.Empty, GH_ParamAccess.item, true);
      manager.AddBooleanParameter("Fine", "F", string.Empty, GH_ParamAccess.item, true);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddIntegerParameter("Visibility", "V", string.Empty, GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var viewSpecific = false; if (!DA.GetData("ViewSpecific", ref viewSpecific)) return;

      var planRCPCut = false;   if (!DA.GetData("PlanRCPCut", ref planRCPCut)) return;
      var topBottom = false;    if (!DA.GetData("TopBottom", ref topBottom)) return;
      var frontBack = false;    if (!DA.GetData("FrontBack", ref frontBack)) return;
      var leftRight = false;    if (!DA.GetData("LeftRight", ref leftRight)) return;
      var onlyWhenCut = false;  if (!DA.GetData("OnlyWhenCut", ref onlyWhenCut)) return;

      var coarse = false;       if (!DA.GetData("Coarse", ref coarse)) return;
      var medium = false;       if (!DA.GetData("Medium", ref medium)) return;
      var fine = false;         if (!DA.GetData("Fine", ref fine)) return;

      int value = 0;
      if (viewSpecific) value |= 1 << 1;

      if (planRCPCut)   value |= 1 << 2;
      if (topBottom)    value |= 1 << 3;
      if (frontBack)    value |= 1 << 4;
      if (leftRight)    value |= 1 << 5;
      if (onlyWhenCut)  value |= 1 << 6;

      if (coarse)       value |= 1 << 13;
      if (medium)       value |= 1 << 14;
      if (fine)         value |= 1 << 15;

      DA.SetData("Visibility", value);
    }
  }
}
