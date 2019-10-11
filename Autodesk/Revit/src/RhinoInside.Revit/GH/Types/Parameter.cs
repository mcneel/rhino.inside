using System;
using System.Collections.Generic;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Expressions;
using Grasshopper.Kernel.Parameters;
using Grasshopper.Kernel.Types;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class ParameterKey : Element
  {
    public override string TypeName => "Revit ParameterKey";
    public override string TypeDescription => "Represents a Revit parameter definition";
    override public object ScriptVariable() => null;
    protected override Type ScriptVariableType => typeof(DB.ParameterElement);

    #region IGH_ElementId
    public override bool LoadElement()
    {
      if (Document is null)
      {
        Value = null;
        if (!Revit.ActiveUIApplication.TryGetDocument(DocumentGUID, out var doc))
        {
          Document = null;
          return false;
        }

        Document = doc;
      }
      else if (IsElementLoaded)
        return true;

      if (Document is object)
        return Document.TryGetElementId(UniqueID, out m_value);

      return false;
    }
    #endregion

    public ParameterKey() { }
    public ParameterKey(DB.Document doc, DB.ElementId id) : base(doc, id) { }
    public ParameterKey(DB.ParameterElement element) : base(element) { }

    new public static ParameterKey FromElementId(DB.Document doc, DB.ElementId id)
    {
      if (id.IsParameterId(doc))
        return new ParameterKey(doc, id);

      return null;
    }

    public override sealed bool CastFrom(object source)
    {
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      var parameterId = DB.ElementId.InvalidElementId;
      switch (source)
      {
        case DB.ParameterElement     parameterElement: SetValue(parameterElement.Document, parameterElement.Id); return true;
        case DB.Parameter            parameter:        SetValue(parameter.Element.Document, parameter.Id); return true;
        case DB.ElementId id:        parameterId = id; break;
        case int integer:            parameterId = new DB.ElementId(integer); break;
      }

      if (parameterId.IsParameterId(Revit.ActiveDBDocument))
      {
        SetValue(Revit.ActiveDBDocument, parameterId);
        return true;
      }

      return base.CastFrom(source);
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(typeof(GH_Guid)))
      {
        target = (Q) (object) (Document.GetElement(Value) as DB.SharedParameterElement)?.GuidValue;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    new class Proxy : Element.Proxy
    {
      public Proxy(ParameterKey o) : base(o) { (this as IGH_GooProxy).UserString = FormatInstance(); }

      public override bool IsParsable() => true;
      public override string FormatInstance()
      {
        int value = owner.Value.IntegerValue;
        if (Enum.IsDefined(typeof(DB.BuiltInParameter), value))
          return value.ToParameterIdString();

        return value.ToString();
      }
      public override bool FromString(string str)
      {
        if (Enum.TryParse(str, out DB.BuiltInParameter builtInParameter))
        {
          owner.Value = new DB.ElementId(builtInParameter);
          return true;
        }

        return false;
      }

      DB.BuiltInParameter builtInParameter => owner.Id.TryGetBuiltInParameter(out var bip) ? bip : DB.BuiltInParameter.INVALID;
      DB.ParameterElement parameter => IsBuiltIn ? null : owner.Document?.GetElement(owner.Id) as DB.ParameterElement;

      [System.ComponentModel.Description("The Guid that identifies this parameter as a shared parameter.")]
      public Guid Guid => (parameter as DB.SharedParameterElement)?.GuidValue ?? Guid.Empty;
      [System.ComponentModel.Description("The user-visible name for the parameter.")]
      public string Name => IsBuiltIn ? DB.LabelUtils.GetLabelFor(builtInParameter) : parameter?.GetDefinition().Name ?? string.Empty;
      [System.ComponentModel.Description("API Object Type.")]
      public override Type ObjectType => IsBuiltIn ? typeof(DB.BuiltInParameter) : parameter?.GetType();

      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Internal parameter data storage type.")]
      public DB.StorageType StorageType => IsBuiltIn ? Revit.ActiveDBDocument.get_TypeOfStorage(builtInParameter) : parameter?.GetDefinition().ParameterType.ToStorageType() ?? DB.StorageType.None;
      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Visible in UI.")]
      public bool Visible => IsBuiltIn ? Valid : parameter?.GetDefinition().Visible ?? false;
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public override string ToString()
    {
      if (IsValid)
      {
        if(Document?.GetElement(Id) is DB.ParameterElement element)
          return element.Name;

        try
        {
          var builtInParameterLabel = DB.LabelUtils.GetLabelFor((DB.BuiltInParameter) Value.IntegerValue);
          return builtInParameterLabel ?? string.Empty;
        }
        catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }
      }

      return base.ToString();
    }
  }

  public class ParameterValue : GH_Goo<DB.Parameter>
  {
    public override string TypeName => "Revit ParameterValue";
    public override string TypeDescription => "Represents a Revit parameter value on an element";
    protected Type ScriptVariableType => typeof(DB.Parameter);
    public override bool IsValid => Value != null;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    double ToRhino(double value, DB.ParameterType type)
    {
      switch (type)
      {
        case DB.ParameterType.Length: return value * Math.Pow(Revit.ModelUnits, 1.0);
        case DB.ParameterType.Area:   return value * Math.Pow(Revit.ModelUnits, 2.0);
        case DB.ParameterType.Volume: return value * Math.Pow(Revit.ModelUnits, 3.0);
      }

      return value;
    }

    public override bool CastFrom(object source)
    {
      if (source is DB.Parameter parameter)
      {
        Value = parameter;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsSubclassOf(ScriptVariableType))
      {
        target = (Q) (object) Value;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(ScriptVariableType))
      {
        target = (Q) (object) Value;
        return true;
      }

      switch (Value.StorageType)
      {
        case DB.StorageType.Integer:
          if (typeof(Q).IsAssignableFrom(typeof(GH_Boolean)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) new GH_Boolean(Value.AsInteger() != 0);
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) new GH_Integer(Value.AsInteger());
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Number)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) new GH_Number((double)Value.AsInteger());
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Colour)))
          {
            if (Value.Element is object)
            {
              int value = Value.AsInteger();
              int r = value % 256;
              value /= 256;
              int g = value % 256;
              value /= 256;
              int b = value % 256;

              target = (Q) (object) new GH_Colour(System.Drawing.Color.FromArgb(r, g, b));
            }
            else
              target = (Q) (object) null;
            return true;
          }
          break;
        case DB.StorageType.Double:
          if (typeof(Q).IsAssignableFrom(typeof(GH_Number)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) new GH_Number(ToRhino(Value.AsDouble(), Value.Definition.ParameterType));
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
          {
            if (Value.Element is object)
            {
              var value = Math.Round(ToRhino(Value.AsDouble(), Value.Definition.ParameterType));
              if (int.MinValue <= value && value <= int.MaxValue)
              {
                target = (Q) (object) new GH_Integer((int) value);
                return true;
              }
            }
            else
            {
              target = (Q) (object) null;
              return true;
            }
          }
          break;
        case DB.StorageType.String:
          if (typeof(Q).IsAssignableFrom(typeof(GH_String)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) new GH_String(Value.AsString());
            return true;
          }
          break;
        case DB.StorageType.ElementId:
          if (typeof(Q).IsSubclassOf(typeof(ID)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) ID.FromElementId(Value.Element.Document, Value.AsElementId());
            return true;
          }
          break;
      }

      return base.CastTo<Q>(ref target);
    }

    public override bool Equals(object obj)
    {
      if (obj is ParameterValue paramValue)
      {
        if
        (
          paramValue.Value.Id.IntegerValue == Value.Id.IntegerValue &&
          paramValue.Value.Element.Id.IntegerValue == Value.Element.Id.IntegerValue &&
          paramValue.Value.StorageType == Value.StorageType &&
          paramValue.Value.HasValue == Value.HasValue
        )
        {
          if (!Value.HasValue)
            return true;

          switch (Value.StorageType)
          {
            case DB.StorageType.None:    return true;
            case DB.StorageType.Integer: return paramValue.Value.AsInteger() == Value.AsInteger();
            case DB.StorageType.Double:  return paramValue.Value.AsDouble() == Value.AsDouble();
            case DB.StorageType.String:   return paramValue.Value.AsString() == Value.AsString();
            case DB.StorageType.ElementId: return paramValue.Value.AsElementId().IntegerValue == Value.AsElementId().IntegerValue;
          }
        }
      }

      return base.Equals(obj);
    }

    public override int GetHashCode()
    {
      return Value.Id.IntegerValue;
    }

    public override string ToString()
    {
      if (IsValid)
      {
        string value = null;
        try
        {
          if (Value.HasValue)
          {
            value = Value.AsValueString();
            if (value is null)
            {
              switch (Value.StorageType)
              {
                case DB.StorageType.Integer: value = Value.AsInteger().ToString(); break;
                case DB.StorageType.Double: value = Value.AsDouble().ToString(); break;
                case DB.StorageType.String: value = Value.AsString(); break;
                case DB.StorageType.ElementId:
                  var id = Value.AsElementId();
                  var e = Value.Element.Document.GetElement(id);
                  value = e?.Name; break;
                default: value = null; break;
              }
            }
          }
        }
        catch (Autodesk.Revit.Exceptions.InternalException) { }

        return value;
      }

      return "Null " + TypeName;
    }
  }

  public class BuiltInParameterGroup : GH_Enum<DB.BuiltInParameterGroup>
  {
    public BuiltInParameterGroup() { Value = (int) DB.BuiltInParameterGroup.INVALID; }
    public override string ToString() => DB.LabelUtils.GetLabelFor(this);
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class ParameterKey : ElementIdNonGeometryParam<Types.ParameterKey, DB.ElementId>
  {
    public override Guid ComponentGuid => new Guid("A550F532-8C68-460B-91F3-DA0A5A0D42B5");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;

    public ParameterKey() : base("Parameter Key", "Parameter Key", "Represents a Revit parameter definition.", "Params", "Revit") { }

    protected override Types.ParameterKey PreferredCast(object data) => null;
  }

  public class ParameterValue : GH_Param<Types.ParameterValue>
  {
    public override Guid ComponentGuid => new Guid("3E13D360-4B29-42C7-8F3E-2AB8F74B4EA8");
    public override GH_Exposure Exposure => GH_Exposure.hidden;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("#");

    public ParameterValue() : base("ParameterValue", "ParameterValue", "Represents a Revit parameter value on an element.", "Params", "Revit", GH_ParamAccess.item) { }
    protected ParameterValue(string name, string nickname, string description, string category, string subcategory, GH_ParamAccess access) :
    base(name, nickname, description, category, subcategory, access) { }
  }

  public class ParameterParam : ParameterValue
  {
    public override Guid ComponentGuid => new Guid("43F0E4E9-3DC4-4965-AB80-07E28E203A91");

    int parameterId = (int) DB.BuiltInParameter.INVALID;
    public int ParameterId
    {
      get
      {
        if (parameterId == (int) DB.BuiltInParameter.INVALID)
        {
          if (Enum.TryParse(Name, out DB.BuiltInParameter builtInParameter))
            parameterId = (int) builtInParameter;
        }

        return parameterId;
      }
      set
      {
        parameterId = value;
        Name = parameterId.ToParameterIdString();
      }
    }

    public ParameterParam() : base("INVALID", "Invalid", "Represents a Revit parameter instance.", "Params", "Revit", GH_ParamAccess.item) { }
    public ParameterParam(DB.Parameter p) : this()
    {
      MutableNickName = false;
      ParameterId = p.Id.IntegerValue;

      try { NickName = DB.LabelUtils.GetLabelFor(p.Definition.ParameterGroup) + " : " + p.Definition.Name; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { NickName = p.Definition.Name; }

      try { Description = p.StorageType == DB.StorageType.ElementId ? "ElementId" : DB.LabelUtils.GetLabelFor(p.Definition.ParameterType); }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException)
      { Description = p.Definition.UnitType == DB.UnitType.UT_Number ? "Enumerate" : DB.LabelUtils.GetLabelFor(p.Definition.UnitType); }
    }
  }

  public class BuiltInParameterGroup : Param_Enum<Types.BuiltInParameterGroup>
  {
    public override Guid ComponentGuid => new Guid("3D9979B4-65C8-447F-BCEA-3705249DF3B6");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;

    public BuiltInParameterGroup() : base("Parameter Group", "Parameter Group", "Represents a Revit parameter group.", "Params", "Revit") { }
  }
}
