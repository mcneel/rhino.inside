using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using GH_IO.Serialization;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class ID : GH_Goo<ElementId>
  {
    public override string TypeName => "Revit Model Object";
    public override string TypeDescription => "Represents a Revit model object";
    public override bool IsValid => Value != ElementId.InvalidElementId;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();
    protected virtual Type ScriptVariableType => typeof(Autodesk.Revit.DB.ElementId);
    public static implicit operator ElementId(ID self) { return self.Value; }

    public string UniqueID { get; protected set; }
    public bool IsReferencedObject => IsValid; // All objects are referenced to Revit model if are valid

    public ID() { Value = ElementId.InvalidElementId; UniqueID = string.Empty; }
    protected ID(ElementId id, string uniqueId = null) { Value = id; UniqueID = uniqueId ?? string.Empty; }

    public override bool CastFrom(object source)
    {
      if (source is GH_Integer integer)
      {
        Value = new ElementId(integer.Value);
        UniqueID = string.Empty;
        return true;
      }
      if (source is ElementId id)
      {
        Value = id;
        UniqueID = string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
      {
        target = (Q) (object) new GH_Integer(Value.IntegerValue);
        return true;
      }
      if (typeof(Q).IsAssignableFrom(typeof(GH_String)))
      {
        target = (Q) (object) new GH_String(UniqueID);
        return true;
      }
      if (target is ElementId)
      {
        target = (Q) (object) Value;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public override sealed string ToString()
    {
      if (Value == ElementId.InvalidElementId)
        return "Null " + TypeName;

      string typeName = TypeName;
      if (Revit.ActiveDBDocument != null)
      {
        var element = Revit.ActiveDBDocument.GetElement(Value);
        if (element != null)
        {
          typeName = "Revit " + element.GetType().Name;
          typeName = typeName + " \"" + element.Name + "\"";
        }
        else
        {
          var category = Autodesk.Revit.DB.Category.GetCategory(Revit.ActiveDBDocument, Value);
          if (category != null)
            typeName = typeName + " \"" + category.Name + "\"";
        }
      }

      // All elements are referenced
      //if (IsReferencedObject)
      //  return "Referenced " + typeName;

#if DEBUG
      return string.Format("{0} (#{1})", typeName, Value.IntegerValue);
#else
      return typeName;
#endif
    }

    public override sealed bool Read(GH_IReader reader)
    {
      UniqueID = reader.GetString("UniqueID");
      return true;
    }

    public override sealed bool Write(GH_IWriter writer)
    {
      writer.SetString("UniqueID", UniqueID);
      return true;
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public abstract class GH_TransactionalComponent : GH_Component
  {
    protected GH_TransactionalComponent(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    public override Rhino.Geometry.BoundingBox ClippingBox
    {
      get
      {
        var clippingBox = Rhino.Geometry.BoundingBox.Empty;

        foreach (var param in Params)
        {
          if (param.SourceCount > 0)
            continue;

          if (param is IGH_PreviewObject previewObject)
          {
            if (!previewObject.Hidden && previewObject.IsPreviewCapable)
              clippingBox.Union(previewObject.ClippingBox);
          }
        }

        return clippingBox;
      }
    }

    static protected void ReplaceElement(Document doc, List<ElementId> list, int index, Element element)
    {
      var id = element?.Id ?? ElementId.InvalidElementId;

      if (index < list.Count)
      {
        if (id != list[index])
        {
          if (doc.GetElement(list[index]) != null)
            doc.Delete(list[index]);

          list[index] = id;
          if (element != null) element.Pinned = true;
        }
      }
      else
      {
        for (int e = list.Count; e <= index; e++)
          list.Add(ElementId.InvalidElementId);

        list[index] = id;
        if (null != element) element.Pinned = true;
      }
    }

    static protected void TrimExcess<T>(List<T> list, int begin = 0)
    {
      int end = list.Count;
      if (begin < end)
      {
        list.RemoveRange(begin, end - begin);
        list.TrimExcess();
      }
    }

    static protected void TrimExcess(Document doc, List<ElementId> list, int begin = 0)
    {
      foreach(var id in list.Skip(begin))
      {
        if (doc.GetElement(id) != null)
        {
          try { doc.Delete(id); }
          catch (Autodesk.Revit.Exceptions.ApplicationException) { }
        }
      }

      TrimExcess(list, begin);
    }
  }

  public abstract class GH_TransactionalComponentItem : GH_TransactionalComponent
  {
    protected GH_TransactionalComponentItem(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    List<ElementId> PreviousElementValues = new List<ElementId>();
    protected Element PreviousElement(Document doc, int Iteration)
    {
      if (Iteration < PreviousElementValues.Count)
        return doc.GetElement(PreviousElementValues[Iteration]);

      return null;
    }

    protected void ReplaceElement(Document doc, IGH_DataAccess DA, int Iteration, Element element)
    {
      DA.SetData(0, element, Iteration);
      ReplaceElement(doc, PreviousElementValues, Iteration, element);

      if (Iteration == DA.Iteration)
      {
        TrimExcess(doc, PreviousElementValues, Iteration + 1);

        // Notify Grasshopper continue evaluating the definition from this component
        if (RuntimeMessageLevel < GH_RuntimeMessageLevel.Error)
        {
          foreach (var param in Params.Output)
          {
            foreach (var recipient in param.Recipients)
              recipient.ExpireSolution(false);
          }
        }
      }
    }
  }

  public abstract class GH_TransactionalComponentList : GH_TransactionalComponent
  {
    protected GH_TransactionalComponentList(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    List<List<ElementId>> PreviousElementValues = new List<List<ElementId>>();
    protected IEnumerable<Element> PreviousElements(Document doc, int Iteration)
    {
      if (Iteration < PreviousElementValues.Count)
      {
        foreach (var id in PreviousElementValues[Iteration])
          yield return doc.GetElement(id);
      }
    }

    protected void ReplaceElements(Document doc, IGH_DataAccess DA, int Iteration, IEnumerable<Element> elements)
    {
      DA.SetDataList(0, elements, Iteration);

      // Update PreviousElementValues
      {
        for (int e = PreviousElementValues.Count; e <= Iteration; e++)
          PreviousElementValues.Add(null);

        var previousElementValues = PreviousElementValues[Iteration];
        if (previousElementValues == null)
          previousElementValues = PreviousElementValues[Iteration] = new List<ElementId>();

        int index = 0;
        foreach (var element in elements)
          ReplaceElement(doc, previousElementValues, index++, element);

        // Remove extra elements in PreviousElementValues
        TrimExcess(doc, previousElementValues, index);
      }

      if (Iteration == DA.Iteration)
      {
        foreach (var list in PreviousElementValues.Skip(Iteration + 1))
          TrimExcess(doc, list);

        TrimExcess(PreviousElementValues, Iteration + 1);

        // Notify Grasshopper continue evaluating the definition from this component
        if (RuntimeMessageLevel < GH_RuntimeMessageLevel.Error)
        {
          foreach (var param in Params.Output)
          {
            foreach (var recipient in param.Recipients)
              recipient.ExpireSolution(false);
          }
        }
      }
    }
  }
}
