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

    public string UniqueID { get; protected set; }
    public bool IsReferencedObject => UniqueID != string.Empty;

    public ID() { Value = ElementId.InvalidElementId; UniqueID = string.Empty; }
    public ID(string uniqueId) { Value = ElementId.InvalidElementId; UniqueID = uniqueId; }
    public ID(int id) { Value = new ElementId(id); UniqueID = string.Empty; }
    public static implicit operator ElementId(ID self) { return self.Value; }

    public override sealed IGH_Goo Duplicate()
    {
      if (System.Activator.CreateInstance(GetType()) is ID dup)
      {
        dup.Value = Value;
        dup.UniqueID = UniqueID;
        return dup;
      }

      return null;
    }

    public override bool CastFrom(object source)
    {
      if (source is Autodesk.Revit.DB.ElementId id)
      {
        Value = id;
        UniqueID = string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
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
          typeName = "Revit " + element.GetType().Name;
      }

      if (IsReferencedObject)
        return "Referenced " + typeName;

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
      var id = element?.Id ?? ElementId.InvalidElementId;

      // Update PreviousElementValues
      if (Iteration < PreviousElementValues.Count)
      {
        if (id != PreviousElementValues[Iteration])
        {
          if (doc.GetElement(PreviousElementValues[Iteration]) != null)
            doc.Delete(PreviousElementValues[Iteration]);

          PreviousElementValues[Iteration] = id;
          if(null != element) element.Pinned = true;
        }
      }
      else
      {
        for (int e = PreviousElementValues.Count; e <= Iteration; e++)
          PreviousElementValues.Add(ElementId.InvalidElementId);

        PreviousElementValues[Iteration] = id;
        if (null != element) element.Pinned = true;
      }

      if (Iteration == DA.Iteration)
      {
        int begin = Iteration + 1;
        int end = PreviousElementValues.Count;

        // Remove extra elements in PreviousElementValues
        if (begin < end)
        {
          for (int e = begin; e < end; e++)
          {
            if (doc.GetElement(PreviousElementValues[e]) != null)
              try { doc.Delete(PreviousElementValues[e]); }
              catch (Autodesk.Revit.Exceptions.ApplicationException) { }
          }

          PreviousElementValues.RemoveRange(begin, end - begin);
        }

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
