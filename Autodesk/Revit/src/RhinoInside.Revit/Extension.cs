using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Autodesk.Revit.DB;

namespace RhinoInside.Revit
{
  public static class Extension
  {
    #region Curves
    public static bool IsSameKindAs(this Autodesk.Revit.DB.Curve self, Autodesk.Revit.DB.Curve other)
    {
      return self.IsBound == other.IsBound && self.GetType() == other.GetType();
    }
    #endregion

    #region Geometry
    public static Autodesk.Revit.DB.GeometryElement GetGeometry(this Autodesk.Revit.DB.Element element, ViewDetailLevel viewDetailLevel, out Options options)
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
    public static bool IsValid(this ElementId id) => id.IntegerValue != ElementId.InvalidElementId.IntegerValue;
    public static bool IsBuiltInId(this ElementId id) => id.IntegerValue < 0;
    public static bool IsParameterId(this ElementId id, Autodesk.Revit.DB.Document doc)
    {
      if (-2000000 < id.IntegerValue && id.IntegerValue < -1000000)
        return Enum.IsDefined(typeof(BuiltInParameter), id.IntegerValue);

      try { return doc.GetElement(id) is ParameterElement; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { return false; }
    }
    public static bool IsCategoryId(this ElementId id, Autodesk.Revit.DB.Document doc)
    {
      if (-3000000 < id.IntegerValue && id.IntegerValue < -2000000)
        return Enum.IsDefined(typeof(BuiltInCategory), id.IntegerValue);

      try { return Autodesk.Revit.DB.Category.GetCategory(doc, id) != null; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { return false; }
    }
    #endregion

    #region Levels
    public static Autodesk.Revit.DB.Level FindLevelByElevation(this Autodesk.Revit.DB.Document doc, double elevation)
    {
      Autodesk.Revit.DB.Level level = null;
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

    public static IEnumerable<Autodesk.Revit.DB.Parameter> GetParameters(this Autodesk.Revit.DB.Element element, ParameterSource parameterSource)
    {
      switch (parameterSource)
      {
        case ParameterSource.Any:
          return Enum.GetValues(typeof(BuiltInParameter)).
            Cast<BuiltInParameter>().
            Select(x => element.get_Parameter(x)).
            Where(x => x?.HasValue ?? false).
            Union(element.Parameters.Cast<Autodesk.Revit.DB.Parameter>()).
            GroupBy(x => x.Id).
            Select(x => x.First());
        case ParameterSource.BuiltIn:
          return Enum.GetValues(typeof(BuiltInParameter)).
            Cast<BuiltInParameter>().
            GroupBy(x => x).
            Select(x => x.First()).
            Select(x => element.get_Parameter(x)).
            Where(x => x?.HasValue ?? false);
        case ParameterSource.Project:
          return element.Parameters.Cast<Autodesk.Revit.DB.Parameter>().
            Where(p => !p.IsShared);
        case ParameterSource.Shared:
          return element.Parameters.Cast<Autodesk.Revit.DB.Parameter>().
            Where(p => p.IsShared);
      }

      return Enumerable.Empty<Autodesk.Revit.DB.Parameter>();
    }

    public static void CopyParametersFrom(this Autodesk.Revit.DB.Element to, Autodesk.Revit.DB.Element from, ICollection<BuiltInParameter> parametersMask = null)
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
    public static void SetTransform(this Autodesk.Revit.DB.Instance element, XYZ newOrigin, XYZ newBasisX, XYZ newBasisY)
    {
      var current = element.GetTransform();
      var BasisZ = newBasisX.CrossProduct(newBasisY);
      {
        if (!current.BasisZ.IsParallelTo(BasisZ))
        {
          var axisDirection = current.BasisZ.CrossProduct(BasisZ);
          double angle = current.BasisZ.AngleTo(BasisZ);

          using (var axis = Autodesk.Revit.DB.Line.CreateUnbound(current.Origin, axisDirection))
            ElementTransformUtils.RotateElement(element.Document, element.Id, axis, angle);

          current = element.GetTransform();
        }

        if (!current.BasisX.IsAlmostEqualTo(newBasisX))
        {
          double angle = current.BasisX.AngleOnPlaneTo(newBasisX, BasisZ);
          using (var axis = Autodesk.Revit.DB.Line.CreateUnbound(current.Origin, BasisZ))
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

    #region Linq
    public static IEnumerable<K> Select<K, T>(this IEnumerator<T> e, Func<T, K> selector)
    {
      while (e.MoveNext())
        yield return selector(e.Current);
    }
    #endregion
  }
}
