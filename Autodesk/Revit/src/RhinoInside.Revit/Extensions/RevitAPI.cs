using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;

namespace RhinoInside.Revit
{
  static class TaskDialogIcons
  {
    public const TaskDialogIcon IconNone        = TaskDialogIcon.TaskDialogIconNone;
#if REVIT_2018
    public const TaskDialogIcon IconShield      = TaskDialogIcon.TaskDialogIconShield;
    public const TaskDialogIcon IconInformation = TaskDialogIcon.TaskDialogIconInformation;
    public const TaskDialogIcon IconError       = TaskDialogIcon.TaskDialogIconError;
#else
    public const TaskDialogIcon IconShield      = TaskDialogIcon.TaskDialogIconWarning;
    public const TaskDialogIcon IconInformation = TaskDialogIcon.TaskDialogIconWarning;
    public const TaskDialogIcon IconError       = TaskDialogIcon.TaskDialogIconWarning;
#endif
    public const TaskDialogIcon IconWarning     = TaskDialogIcon.TaskDialogIconWarning;
  }

  public static class RevitAPI
  {
    #region XYZ
    public static bool IsParallelTo(this XYZ a, XYZ b)
    {
      return a.IsAlmostEqualTo(a.DotProduct(b) < 0.0 ? -b : b);
    }
    #endregion

    #region Curves
    public static bool IsSameKindAs(this Curve self, Curve other)
    {
      return self.IsBound == other.IsBound && self.GetType() == other.GetType();
    }
    #endregion

    #region Geometry
    public static GeometryElement GetGeometry(this Element element, ViewDetailLevel viewDetailLevel, out Options options)
    {
      options = new Options { ComputeReferences = true, DetailLevel = viewDetailLevel };
      var geometry = element.get_Geometry(options);

      if (!(geometry?.Any() ?? false) && element is GenericForm form && !form.Combinations.IsEmpty)
      {
        geometry.Dispose();

        options.IncludeNonVisibleObjects = true;
        return element.get_Geometry(options);
      }

      return geometry;
    }

#if !REVIT_2018
    public static Surface GetSurface(this Face face)
    {
      switch(face)
      {
        case PlanarFace planarFace:
          return Plane.CreateByOriginAndBasis(planarFace.Origin, planarFace.XVector, planarFace.YVector);

        case ConicalFace conicalFace:
        {
          var basisX = conicalFace.get_Radius(0).Normalize();
          var basisY = conicalFace.get_Radius(1).Normalize();
          var basisZ = conicalFace.Axis.Normalize();
          return ConicalSurface.Create(new Frame(conicalFace.Origin, basisX, basisY, basisZ), conicalFace.HalfAngle);
        }

        case CylindricalFace cylindricalFace:
        {
          double radius = cylindricalFace.get_Radius(0).GetLength();
          var basisX = cylindricalFace.get_Radius(0).Normalize();
          var basisY = cylindricalFace.get_Radius(1).Normalize();
          var basisZ = cylindricalFace.Axis.Normalize();
          return CylindricalSurface.Create(new Frame(cylindricalFace.Origin, basisX, basisY, basisZ), radius);
        }

        case RevolvedFace revolvedFace:
        {
          var ECStoWCS = new Transform(Transform.Identity)
          {
            Origin = revolvedFace.Origin,
            BasisX = revolvedFace.get_Radius(0).Normalize(),
            BasisY = revolvedFace.get_Radius(1).Normalize(),
            BasisZ = revolvedFace.Axis.Normalize()
          };

          var profileInWCS = revolvedFace.Curve.CreateTransformed(ECStoWCS);

          return RevolvedSurface.Create(new Frame(ECStoWCS.Origin, ECStoWCS.BasisX, ECStoWCS.BasisY, ECStoWCS.BasisZ), profileInWCS);
        }
        case RuledFace ruledFace:
        {
          var profileCurve0 = ruledFace.get_Curve(0);
          var profileCurve1 = ruledFace.get_Curve(1);
          return RuledSurface.Create(profileCurve0, profileCurve1);
        }
      }

      return null;
    }

    public static Curve GetProfileCurveInWorldCoordinates(this RevolvedSurface revolvedSurface)
    {
      var profileCurve = revolvedSurface.GetProfileCurve();
      var ECStoWCS = new Transform(Transform.Identity)
      {
        Origin = revolvedSurface.Origin,
        BasisX = revolvedSurface.XDir.Normalize(),
        BasisY = revolvedSurface.YDir.Normalize(),
        BasisZ = revolvedSurface.Axis.Normalize()
      };

      return profileCurve.CreateTransformed(ECStoWCS);
    }

    public static bool HasFirstProfilePoint(this RuledSurface ruledSurface)
    {
      return ruledSurface.GetFirstProfilePoint() is object;
    }

    public static bool HasSecondProfilePoint(this RuledSurface ruledSurface)
    {
      return ruledSurface.GetSecondProfilePoint() is object;
    }
#endif

    public static IEnumerable<GeometryObject> ToDirectShapeGeometry(this GeometryObject geometry)
    {
      switch (geometry)
      {
        case Point p: yield return p; yield break;
        case Curve c:
          foreach (var unbounded in ToBoundedCurves(c))
            yield return unbounded;
          yield break;
        case Solid s: yield return s; yield break;
        case Mesh m: yield return m; yield break;
        case GeometryInstance i: yield return i; yield break;
        default: throw new ArgumentException("DirectShape only supports Point, Curve, Solid, Mesh and GeometryInstance.");
      }
    }

    public static IEnumerable<Curve> ToBoundedCurves(this Curve curve)
    {
      switch (curve)
      {
        case Arc arc:
          if (!arc.IsBound)
          {
            yield return Arc.Create(arc.Center, arc.Radius, 0.0, Math.PI, arc.XDirection, arc.YDirection);
            yield return Arc.Create(arc.Center, arc.Radius, Math.PI, Math.PI * 2.0, arc.XDirection, arc.YDirection);
          }
          else yield return arc;
          yield break;
        case Ellipse ellipse:
          if (!ellipse.IsBound)
          {
#if REVIT_2018
            yield return Ellipse.CreateCurve(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, 0.0, Math.PI);
            yield return Ellipse.CreateCurve(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, Math.PI, Math.PI * 2.0);
#else
            yield return Ellipse.Create(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, 0.0, Math.PI);
            yield return Ellipse.Create(ellipse.Center, ellipse.RadiusX, ellipse.RadiusY, ellipse.XDirection, ellipse.YDirection, Math.PI, Math.PI * 2.0);
#endif
          }
          else yield return ellipse;
          yield break;
        case Curve c: yield return c; yield break;
      }
    }
    #endregion

    #region ElementId
    public static bool IsValid(this ElementId id)     => id is object && id != ElementId.InvalidElementId;
    public static bool IsBuiltInId(this ElementId id) => id is object && id <= ElementId.InvalidElementId;

    public static bool IsCategoryId(this ElementId id, Document doc)
    {
      if (-3000000 < id.IntegerValue && id.IntegerValue < -2000000)
        return Enum.IsDefined(typeof(BuiltInCategory), id.IntegerValue);

      try { return Category.GetCategory(doc, id) is object; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { return false; }
    }

    public static bool IsParameterId(this ElementId id, Document doc)
    {
      if (-2000000 < id.IntegerValue && id.IntegerValue < -1000000)
        return Enum.IsDefined(typeof(BuiltInParameter), id.IntegerValue);

      try { return doc.GetElement(id) is ParameterElement; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { return false; }
    }

    public static bool TryGetBuiltInCategory(this ElementId id, out BuiltInCategory builtInParameter)
    {
      var IntegerValue = id.IntegerValue;
      if
      (
        -3000000 < IntegerValue && IntegerValue < -2000000 &&
        Enum.IsDefined(typeof(BuiltInCategory), IntegerValue)
      )
      {
        builtInParameter = (BuiltInCategory) IntegerValue;
        return true;
      }

      builtInParameter = BuiltInCategory.INVALID;
      return false;
    }

    public static bool TryGetBuiltInParameter(this ElementId id, out BuiltInParameter builtInParameter)
    {
      var IntegerValue = id.IntegerValue;
      if
      (
        -2000000 < IntegerValue && IntegerValue < -1000000 &&
        Enum.IsDefined(typeof(BuiltInParameter), IntegerValue)
      )
      {
        builtInParameter = (BuiltInParameter) IntegerValue;
        return true;
      }

      builtInParameter = BuiltInParameter.INVALID;
      return false;
    }
    #endregion

    #region Category
    public static bool IsHidden(this Category category)
    {
      return !category.CanAddSubcategory;
    }

    public static bool IsBuiltInCategoryValid(this BuiltInCategory category)
    {
      if (-3000000 < (int) category && (int) category < -2000000)
        return Enum.IsDefined(typeof(BuiltInCategory), (int) category);

      return false;
    }

    public static Document Document(this Category category)
    {
      return category?.GetGraphicsStyle(GraphicsStyleType.Projection).Document;
    }
    #endregion

    #region Parameters
    public enum ParameterSet
    {
      Any,
      BuiltIn,
      Project,
      Shared
    }

    public static IEnumerable<Parameter> GetParameters(this Element element, ParameterSet set)
    {
      switch (set)
      {
        case ParameterSet.Any:
          return Enum.GetValues(typeof(BuiltInParameter)).
            Cast<BuiltInParameter>().
            Select
            (
              x =>
              {
                try { return element.get_Parameter(x); }
                catch (Autodesk.Revit.Exceptions.InternalException) { return null; }
              }
            ).
            Where(x => x is object).
            Union(element.Parameters.Cast<Parameter>().OrderBy(x => x.Id.IntegerValue)).
            GroupBy(x => x.Id).
            Select(x => x.First());
        case ParameterSet.BuiltIn:
          return Enum.GetValues(typeof(BuiltInParameter)).
            Cast<BuiltInParameter>().
            GroupBy(x => x).
            Select(x => x.First()).
            Select
            (
              x =>
              {
                try { return element.get_Parameter(x); }
                catch (Autodesk.Revit.Exceptions.InternalException) { return null; }
              }
            ).
            Where(x => x is object);
        case ParameterSet.Project:
          return element.Parameters.Cast<Parameter>().
            Where(p => !p.IsShared && p.Id.IntegerValue > 0).
            OrderBy(x => x.Id.IntegerValue);
        case ParameterSet.Shared:
          return element.Parameters.Cast<Parameter>().
            Where(p => p.IsShared).
            OrderBy(x => x.Id.IntegerValue);
      }

      return Enumerable.Empty<Parameter>();
    }

    public static Parameter GetParameter(this Element element, string name, ParameterSet set)
    {
      var parameters = element.
        GetParameters(set).
        Where(x => x.Definition.Name == name);

      return parameters.FirstOrDefault(x => !x.IsReadOnly) ?? parameters.FirstOrDefault();
    }

    public static Parameter GetParameter(this Element element, string name, ParameterType type, ParameterSet set)
    {
      var parameters = element.
        GetParameters(set).
        Where(x => x.Definition.ParameterType == type && x.Definition.Name == name);

      return parameters.FirstOrDefault(x => !x.IsReadOnly) ?? parameters.FirstOrDefault();
    }

    public static void CopyParametersFrom(this Element to, Element from, ICollection<BuiltInParameter> parametersMask = null)
    {
      if (ReferenceEquals(to, from) || from is null || to is null)
        return;

      if(!from.Document.Equals(to.Document))
        throw new InvalidOperationException();

      foreach (var previousParameter in from.GetParameters(ParameterSet.Any))
        using (previousParameter)
        using (var param = to.get_Parameter(previousParameter.Definition))
        {
          if (param is null || param.IsReadOnly)
            continue;

          if
          (
            parametersMask is object &&
            param.Definition is InternalDefinition internalDefinition &&
            parametersMask.Contains(internalDefinition.BuiltInParameter)
          )
            continue;

          switch (previousParameter.StorageType)
          {
            case StorageType.Integer:   param.Set(previousParameter.AsInteger());   break;
            case StorageType.Double:    param.Set(previousParameter.AsDouble());    break;
            case StorageType.String:    param.Set(previousParameter.AsString());    break;
            case StorageType.ElementId: param.Set(previousParameter.AsElementId()); break;
          }
        }
    }

    public static StorageType ToStorageType(this ParameterType parameterType)
    {
      switch (parameterType)
      {
        case ParameterType.Invalid:
          return StorageType.None;
        case ParameterType.Text:
        case ParameterType.MultilineText:
        case ParameterType.URL:
          return StorageType.String;
        case ParameterType.YesNo:
        case ParameterType.Integer:
        case ParameterType.LoadClassification:
          return StorageType.Integer;
        case ParameterType.Material:
        case ParameterType.FamilyType:
        case ParameterType.Image:
          return StorageType.ElementId;
        case ParameterType.Number:
        default:
          return StorageType.Double;
      }
    }

    public static string ToParameterIdString(this int value)
    {
      switch (value)
      {
        case (int) BuiltInParameter.GENERIC_THICKNESS:          return "GENERIC_THICKNESS";
        case (int) BuiltInParameter.GENERIC_WIDTH:              return "GENERIC_WIDTH";
        case (int) BuiltInParameter.GENERIC_HEIGHT:             return "GENERIC_HEIGHT";
        case (int) BuiltInParameter.GENERIC_DEPTH:              return "GENERIC_DEPTH";
        case (int) BuiltInParameter.GENERIC_FINISH:             return "GENERIC_FINISH";
        case (int) BuiltInParameter.GENERIC_CONSTRUCTION_TYPE:  return "GENERIC_CONSTRUCTION_TYPE";
        case (int) BuiltInParameter.FIRE_RATING:                return "FIRE_RATING";
        case (int) BuiltInParameter.ALL_MODEL_COST:             return "ALL_MODEL_COST";
        case (int) BuiltInParameter.ALL_MODEL_MARK:             return "ALL_MODEL_MARK";
        case (int) BuiltInParameter.ALL_MODEL_FAMILY_NAME:      return "ALL_MODEL_FAMILY_NAME";
        case (int) BuiltInParameter.ALL_MODEL_TYPE_NAME:        return "ALL_MODEL_TYPE_NAME";
        case (int) BuiltInParameter.ALL_MODEL_TYPE_MARK:        return "ALL_MODEL_TYPE_MARK";
      }

      return ((BuiltInParameter) value).ToString();
    }
    #endregion

    #region Element
    public static void SetTransform(this Instance element, XYZ newOrigin, XYZ newBasisX, XYZ newBasisY)
    {
      var current = element.GetTransform();
      var BasisZ = newBasisX.CrossProduct(newBasisY);
      {
        if (!current.BasisZ.IsParallelTo(BasisZ))
        {
          var axisDirection = current.BasisZ.CrossProduct(BasisZ);
          double angle = current.BasisZ.AngleTo(BasisZ);

          using (var axis = Line.CreateUnbound(current.Origin, axisDirection))
            ElementTransformUtils.RotateElement(element.Document, element.Id, axis, angle);

          current = element.GetTransform();
        }

        if (!current.BasisX.IsAlmostEqualTo(newBasisX))
        {
          double angle = current.BasisX.AngleOnPlaneTo(newBasisX, BasisZ);
          using (var axis = Line.CreateUnbound(current.Origin, BasisZ))
            ElementTransformUtils.RotateElement(element.Document, element.Id, axis, angle);
        }

        {
          var trans = newOrigin - current.Origin;
          if (!trans.IsZeroLength())
            ElementTransformUtils.MoveElement(element.Document, element.Id, trans);
        }
      }
    }
    #endregion

    #region Document

    public static string GetFilePath(this Document doc)
    {
      if (doc is null)
        return string.Empty;

      if(string.IsNullOrEmpty(doc.PathName))
        return (doc.Title + (doc.IsFamilyDocument ? ".rfa" : ".rvt"));

      return doc.PathName;
    }

    public static Guid GetFingerprintGUID(this Document doc)
    {
      if (doc?.IsValidObject != true)
        return Guid.Empty;
      
      return ExportUtils.GetGBXMLDocumentId(doc);
    }

    private static bool TryGetDocument(this IEnumerable<Document> set, Guid guid, out Document document, Document activeDBDocument = default(Document))
    {
      if (guid != Guid.Empty)
      {
        // For performance reasons and also in case of conflict the ActiveDBDocument will have priority
        if (ExportUtils.GetGBXMLDocumentId(activeDBDocument) == guid)
        {
          document = activeDBDocument;
          return true;
        }

        foreach (var doc in set.Where(x => ExportUtils.GetGBXMLDocumentId(x) == guid))
        {
          document = doc;
          return true;
        }
      }

      document = default(Document);
      return false;
    }

    public static bool TryGetDocument(this Autodesk.Revit.UI.UIApplication app, Guid guid, out Document document) =>
      TryGetDocument(app.Application.Documents.Cast<Document>(), guid, out document, app.ActiveUIDocument.Document);

    public static bool TryGetCategoryId(this Document doc, string uniqueId, out ElementId categoryId)
    {
      categoryId = default(ElementId);

      if (UniqueId.TryParse(uniqueId, out var EpisodeId, out var id))
      {
        if (EpisodeId == Guid.Empty)
        {
          if (-3000000 < id && id < -2000000 && Enum.IsDefined(typeof(BuiltInCategory), id))
            categoryId = new ElementId((BuiltInCategory) id);
        }
        else
        {
          if (doc.GetElement(uniqueId) is Element category)
          {
            try{ categoryId = Category.GetCategory(doc, category.Id)?.Id; }
            catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }
          }
        }
      }

      return categoryId is object;
    }

    public static bool TryGetParameterId(this Document doc, string uniqueId, out ElementId parameterId)
    {
      parameterId = default(ElementId);

      if (UniqueId.TryParse(uniqueId, out var EpisodeId, out var id))
      {
        if (EpisodeId == Guid.Empty)
        {
          if (-2000000 < id && id < -1000000 && Enum.IsDefined(typeof(BuiltInParameter), id))
            parameterId = new ElementId((BuiltInParameter) id);
        }
        else
        {
          if (doc.GetElement(uniqueId) is ParameterElement parameter)
            parameterId = parameter.Id;
        }
      }

      return parameterId is object;
    }

    public static bool TryGetElementId(this Document doc, string uniqueId, out ElementId elementId)
    {
      elementId = default(ElementId);

      try
      {
        if (Reference.ParseFromStableRepresentation(doc, uniqueId) is Reference reference)
          elementId = reference.ElementId;
      }
      catch (Autodesk.Revit.Exceptions.ArgumentException) { }

      return elementId is object;
    }

    public static Category GetCategory(this Document doc, string uniqueId)
    {
      if (doc is null || string.IsNullOrEmpty(uniqueId))
        return null;

      if (UniqueId.TryParse(uniqueId, out var EpisodeId, out var id))
      {
        if (EpisodeId == Guid.Empty)
        {
          if (-3000000 < id && id < -2000000 && Enum.IsDefined(typeof(BuiltInCategory), id))
          {
            try { return Category.GetCategory(doc, (BuiltInCategory) id); }
            catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

            // Some categories like BuiltInCategory.OST_StackedWalls produce that exception
            // Here we look for an element that is in that Category and return it.
            using (var collector = new FilteredElementCollector(doc))
            {
              var element = collector.OfCategory((BuiltInCategory) id).FirstElement();
              return element?.Category;
            }
          }
        }
        else
        {
          if (doc.GetElement(uniqueId) is Element category)
          {
            try { return Category.GetCategory(doc, category.Id); }
            catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }
          }
        }
      }

      return null;
    }

    public static Category GetCategory(this Document doc, ElementId id)
    {
      if (doc is null || id is null)
        return null;

      try
      {
        var category = Category.GetCategory(doc, id);
        if (category is object)
          return category;
      }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

      if (id.TryGetBuiltInCategory(out var builtInCategory))
      {
        using (var collector = new FilteredElementCollector(doc))
        {
          var element = collector.OfCategory(builtInCategory).FirstElement();
          return element?.Category;
        }
      }

      return null;
    }

    public static IEnumerable<BuiltInCategory> GetBuiltInCategories() =>
      Enum.GetValues(typeof(BuiltInCategory)).
      Cast<BuiltInCategory>().
      Where(x => x.IsBuiltInCategoryValid());

    static BuiltInCategory[] BuiltInCategoriesWithParameters;
    static Document BuiltInCategoriesWithParametersDocument;
    internal static ICollection<BuiltInCategory> GetBuiltInCategoriesWithParameters(this Document doc)
    {
      if (BuiltInCategoriesWithParameters is null && !BuiltInCategoriesWithParametersDocument.Equals(doc))
      {
        BuiltInCategoriesWithParametersDocument = doc;
        BuiltInCategoriesWithParameters =
          GetBuiltInCategories().
          Where
          (
            bic =>
            {
              try { return Category.GetCategory(doc, bic)?.AllowsBoundParameters == true; }
              catch (Autodesk.Revit.Exceptions.InvalidOperationException) { return false; }
            }
          ).
          ToArray();
      }

      return BuiltInCategoriesWithParameters;
    }

    public static Level FindLevelByElevation(this Document doc, double elevation)
    {
      Level level = null;
      using (var collector = new FilteredElementCollector(doc))
      {
        foreach (var levelN in collector.OfClass(typeof(Level)).ToElements().Cast<Level>().OrderBy(c => c.Elevation))
        {
          if (level == null)
            level = levelN;
          else if (elevation >= levelN.Elevation)
            level = levelN;
        }
      }
      return level;
    }
    #endregion

    #region Application
    public static DefinitionFile CreateSharedParameterFile(this Autodesk.Revit.ApplicationServices.Application app)
    {
      string sharedParametersFilename = app.SharedParametersFilename;
      try
      {
        // Create Temp Shared Parameters File
        app.SharedParametersFilename = Path.GetTempFileName();
        return app.OpenSharedParameterFile();
      }
      finally
      {
        // Restore User Shared Parameters File
        try { File.Delete(app.SharedParametersFilename); }
        finally { app.SharedParametersFilename = sharedParametersFilename; }
      }
    }

#if !REVIT_2018
    public static IList<Autodesk.Revit.Utility.Asset> GetAssets(this Autodesk.Revit.ApplicationServices.Application app, Autodesk.Revit.Utility.AssetType assetType)
    {
      return new Autodesk.Revit.Utility.Asset[0];
    }

    public static AppearanceAssetElement Duplicate(this AppearanceAssetElement element, string name)
    {
      return AppearanceAssetElement.Create(element.Document, name, element.GetRenderingAsset());
    }
#endif

    public static int ToLCID(this Autodesk.Revit.ApplicationServices.LanguageType value)
    {
      switch (value)
      {
        case Autodesk.Revit.ApplicationServices.LanguageType.English_USA:   return 1033;
        case Autodesk.Revit.ApplicationServices.LanguageType.German:        return 1031;
        case Autodesk.Revit.ApplicationServices.LanguageType.Spanish:       return 1034;
        case Autodesk.Revit.ApplicationServices.LanguageType.French:        return 1036;
        case Autodesk.Revit.ApplicationServices.LanguageType.Italian:       return 1040;
        case Autodesk.Revit.ApplicationServices.LanguageType.Dutch:         return 1043;
        case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Simplified: return 2052;
        case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Traditional: return 1028;
        case Autodesk.Revit.ApplicationServices.LanguageType.Japanese:      return 1041;
        case Autodesk.Revit.ApplicationServices.LanguageType.Korean:        return 1042;
        case Autodesk.Revit.ApplicationServices.LanguageType.Russian:       return 1049;
        case Autodesk.Revit.ApplicationServices.LanguageType.Czech:         return 1029;
        case Autodesk.Revit.ApplicationServices.LanguageType.Polish:        return 1045;
        case Autodesk.Revit.ApplicationServices.LanguageType.Hungarian:     return 1038;
        case Autodesk.Revit.ApplicationServices.LanguageType.Brazilian_Portuguese: return 1046;
#if REVIT_2018
        case Autodesk.Revit.ApplicationServices.LanguageType.English_GB: return 2057;
#endif
      }

      return 1033;
    }

    #endregion
  }

  public static class UniqueId
  {
    public static string Format(Guid episodeId, int index) => $"{episodeId:D}-{index,8:x}";
    public static bool TryParse(string s, out Guid episodeId, out int id)
    {
      episodeId = Guid.Empty;
      id = -1;
      if (s.Length != 36 + 1 + 8)
        return false;

      return Guid.TryParseExact(s.Substring(0, 36), "D", out episodeId) &&
             s[36] == '-' &&
             int.TryParse(s.Substring(36 + 1, 8), System.Globalization.NumberStyles.AllowHexSpecifier, null, out id);
    }
  }
}
