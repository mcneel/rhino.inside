using System;
using System.Collections.Generic;
using System.Linq;
using Autodesk.Revit.DB;

namespace RhinoInside.Revit
{
  public static partial class Extension
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
    #endregion

    #region ElementId
    public static bool IsValid(this ElementId id) => id?.IntegerValue != ElementId.InvalidElementId.IntegerValue;
    public static bool IsBuiltInId(this ElementId id) => id.IntegerValue < 0;

    public static bool TryGetBuiltInParameter(this ElementId id, out BuiltInParameter builtInParameter)
    {
      if (Enum.IsDefined(typeof(BuiltInParameter), id.IntegerValue))
      {
        builtInParameter = (BuiltInParameter) id.IntegerValue;
        return true;
      }
      else
      {
        builtInParameter = BuiltInParameter.INVALID;
        return true;
      }
    }
    public static bool TryGetBuiltInCategory(this ElementId id, out BuiltInCategory builtInParameter)
    {
      if (Enum.IsDefined(typeof(BuiltInCategory), id.IntegerValue))
      {
        builtInParameter = (BuiltInCategory) id.IntegerValue;
        return true;
      }
      else
      {
        builtInParameter = BuiltInCategory.INVALID;
        return true;
      }
    }

    public static bool IsParameterId(this ElementId id, Document doc)
    {
      if (-2000000 < id.IntegerValue && id.IntegerValue < -1000000)
        return Enum.IsDefined(typeof(BuiltInParameter), id.IntegerValue);

      try { return doc.GetElement(id) is ParameterElement; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { return false; }
    }
    public static bool IsCategoryId(this ElementId id, Document doc)
    {
      if (-3000000 < id.IntegerValue && id.IntegerValue < -2000000)
        return Enum.IsDefined(typeof(BuiltInCategory), id.IntegerValue);

      try { return Category.GetCategory(doc, id) != null; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { return false; }
    }
    #endregion

    #region Levels
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

    #region Parameters
    public enum ParameterSource
    {
      Any,
      BuiltIn,
      Project,
      Shared
    }

    public static IEnumerable<Parameter> GetParameters(this Element element, ParameterSource parameterSource)
    {
      switch (parameterSource)
      {
        case ParameterSource.Any:
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
            Union(element.Parameters.Cast<Parameter>()).
            GroupBy(x => x.Id).
            Select(x => x.First());
        case ParameterSource.BuiltIn:
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
        case ParameterSource.Project:
          return element.Parameters.Cast<Parameter>().
            Where(p => !p.IsShared);
        case ParameterSource.Shared:
          return element.Parameters.Cast<Parameter>().
            Where(p => p.IsShared);
      }

      return Enumerable.Empty<Parameter>();
    }

    public static void CopyParametersFrom(this Element to, Element from, ICollection<BuiltInParameter> parametersMask = null)
    {
      if (from != null && to != null)
      {
        foreach (var previousParameter in from.GetParameters(ParameterSource.Any))
          using (previousParameter)
          using (var param = to.get_Parameter(previousParameter.Definition))
          {
            if (param == null || param.IsReadOnly)
              continue;

            if (parametersMask != null)
              if (param.Definition is InternalDefinition internalDefinition)
              {
                if (parametersMask.Contains(internalDefinition.BuiltInParameter))
                  continue;
              }

            switch (previousParameter.StorageType)
            {
              case StorageType.Integer: param.Set(previousParameter.AsInteger()); break;
              case StorageType.Double: param.Set(previousParameter.AsDouble()); break;
              case StorageType.String: param.Set(previousParameter.AsString()); break;
              case StorageType.ElementId: param.Set(previousParameter.AsElementId()); break;
            }
          }
      }
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

    #region Application
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
    #endregion
  }
}
