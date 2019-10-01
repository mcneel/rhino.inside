using System;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public class ParameterKey : Element
  {
    public override string TypeName => "Revit ParameterKey";
    public override string TypeDescription => "Represents a Revit parameter definition";
    override public object ScriptVariable() => Value;
    protected override Type ScriptVariableType => typeof(ElementId);

    public static explicit operator Autodesk.Revit.DB.ParameterElement(ParameterKey self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.ParameterElement;

    #region IGH_ElementId
    public override bool LoadElement(Document doc)
    {
      if (TryParseUniqueID(UniqueID, out var _, out var index))
      {
        Value = new ElementId(index);
        if (Value.IsParameterId(Revit.ActiveDBDocument))
          return true;
      }

      Value = ElementId.InvalidElementId;
      return false;
    }
    #endregion

    public ParameterKey() { }
    public ParameterKey(Autodesk.Revit.DB.ParameterElement parameterElement) : base(parameterElement) { }

    public override sealed bool CastFrom(object source)
    {
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      var parameterId = ElementId.InvalidElementId;
      switch (source)
      {
        case Autodesk.Revit.DB.ParameterElement parameterElement: SetValue(parameterElement); return true;
        case Autodesk.Revit.DB.Parameter parameter: parameterId = parameter.Id; break;
        case Autodesk.Revit.DB.ElementId id:        parameterId = id; break;
        case int integer:                           parameterId = new ElementId(integer); break;
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
        var element = (Autodesk.Revit.DB.SharedParameterElement) this;
        target = (Q) (object) new GH_Guid(element?.GuidValue ?? Guid.Empty);
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    class Proxy : IGH_GooProxy
    {
      public Proxy(ParameterKey owner) { proxyOwner = owner; (this as IGH_GooProxy).UserString = FormatInstance(); }

      public void Construct() { }
      public string MutateString(string str) => str.Trim();
      public string FormatInstance()
      {
        int value = proxyOwner.Value.IntegerValue;
        if (Enum.IsDefined(typeof(Autodesk.Revit.DB.BuiltInParameter), value))
          return value.ToParameterIdString();

        return value.ToString();
      }
      public bool FromString(string str)
      {
        if (Enum.TryParse(str, out Autodesk.Revit.DB.BuiltInParameter builtInParameter))
        {
          proxyOwner.Value = new ElementId(builtInParameter);
          return true;
        }

        return false;
      }

      readonly ParameterKey proxyOwner;
      IGH_Goo IGH_GooProxy.ProxyOwner => proxyOwner;
      bool    IGH_GooProxy.IsParsable => true;
      string  IGH_GooProxy.UserString { get; set; }

      Autodesk.Revit.DB.BuiltInParameter builtInParameter => proxyOwner.Value.TryGetBuiltInParameter(out var bip) ? bip : BuiltInParameter.INVALID;
      Autodesk.Revit.DB.ParameterElement parameter => IsBuiltIn ? null : Revit.ActiveDBDocument?.GetElement(proxyOwner.Value) as Autodesk.Revit.DB.ParameterElement;

      public bool Valid => proxyOwner.IsValid;
      [System.ComponentModel.Description("The parameter identifier in this session.")]
      public int Id => proxyOwner.Value.IntegerValue;
      [System.ComponentModel.Description("A stable unique identifier for this parameter within the document.")]
      public string UniqueID => proxyOwner.UniqueID;
      [System.ComponentModel.Description("The Guid that identifies this parameter as a shared parameter.")]
      public Guid Guid => (parameter as SharedParameterElement)?.GuidValue ?? Guid.Empty;
      [System.ComponentModel.Description("The user-visible name for the parameter.")]
      public string Name => IsBuiltIn ? LabelUtils.GetLabelFor(builtInParameter) : parameter?.GetDefinition().Name ?? string.Empty;
      [System.ComponentModel.Description(".NET Object Type.")]
      public string Object => IsBuiltIn ? typeof(BuiltInParameter).FullName : parameter?.GetType().FullName;

      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Parameter is built in Revit.")]
      public bool IsBuiltIn => builtInParameter != BuiltInParameter.INVALID;
      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Internal parameter data storage type.")]
      public StorageType StorageType => IsBuiltIn ? Revit.ActiveDBDocument.get_TypeOfStorage(builtInParameter) : parameter.GetDefinition().ParameterType.ToStorageType();
      [System.ComponentModel.Category("Other"), System.ComponentModel.Description("Visible in UI.")]
      public bool Visible => IsBuiltIn ? true : parameter?.GetDefinition().Visible ?? false;
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public override string ToString()
    {
      if (IsValid)
      {
        var element = (Autodesk.Revit.DB.ParameterElement) this;
        if (element != null)
          return element.Name;

        try
        {
          var builtInParameterLabel = LabelUtils.GetLabelFor((BuiltInParameter) Value.IntegerValue);
          return builtInParameterLabel ?? string.Empty;
        }
        catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }
      }

      return base.ToString();
    }
  }

  public class ParameterValue : GH_Goo<Autodesk.Revit.DB.Parameter>
  {
    public override string TypeName => "Revit ParameterValue";
    public override string TypeDescription => "Represents a Revit parameter value on an element";
    protected Type ScriptVariableType => typeof(Autodesk.Revit.DB.Parameter);
    public override bool IsValid => Value != null;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    double ToRhino(double value, ParameterType type)
    {
      switch (type)
      {
        case ParameterType.Length: return value * Math.Pow(Revit.ModelUnits, 1.0);
        case ParameterType.Area:   return value * Math.Pow(Revit.ModelUnits, 2.0);
        case ParameterType.Volume: return value * Math.Pow(Revit.ModelUnits, 3.0);
      }

      return value;
    }

    public override bool CastFrom(object source)
    {
      if (source is Autodesk.Revit.DB.Parameter parameter)
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
        case StorageType.Integer:
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
        case StorageType.Double:
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
        case StorageType.String:
          if (typeof(Q).IsAssignableFrom(typeof(GH_String)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) new GH_String(Value.AsString());
            return true;
          }
          break;
        case StorageType.ElementId:
          if (typeof(Q).IsSubclassOf(typeof(ID)))
          {
            target = Value.Element is null ? (Q) (object) null :
                     (Q) (object) ID.Make(Value.AsElementId());
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
            case StorageType.None:    return true;
            case StorageType.Integer: return paramValue.Value.AsInteger() == Value.AsInteger();
            case StorageType.Double:  return paramValue.Value.AsDouble() == Value.AsDouble();
            case StorageType.String:   return paramValue.Value.AsString() == Value.AsString();
            case StorageType.ElementId: return paramValue.Value.AsElementId().IntegerValue == Value.AsElementId().IntegerValue;
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
                case StorageType.Integer: value = Value.AsInteger().ToString(); break;
                case StorageType.Double: value = Value.AsDouble().ToString(); break;
                case StorageType.String: value = Value.AsString(); break;
                case StorageType.ElementId:
                  var id = Value.AsElementId();
                  var e = Revit.ActiveDBDocument.GetElement(id);
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

  public class BuiltInParameterGroup : GH_Goo<Autodesk.Revit.DB.BuiltInParameterGroup>
  {
    public override string TypeName => "Revit BuiltInParameterGroup";
    public override string TypeDescription => "Represents a Revit Parameter group";
    protected Type ScriptVariableType => typeof(Autodesk.Revit.DB.BuiltInParameterGroup);
    public override bool IsValid => Enum.IsDefined(typeof(Autodesk.Revit.DB.BuiltInParameterGroup), Value);
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    public BuiltInParameterGroup() { Value = Autodesk.Revit.DB.BuiltInParameterGroup.INVALID; }

    public override bool CastFrom(object source)
    {
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      switch(source)
      {
        case int integer:
          if (Enum.IsDefined(typeof(Autodesk.Revit.DB.BuiltInParameterGroup), integer))
          {
            Value = (Autodesk.Revit.DB.BuiltInParameterGroup) integer;
            return true;
          }
          break;
        case Autodesk.Revit.DB.BuiltInParameterGroup builtInParameterGroup:
          Value = builtInParameterGroup;
          return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q).IsAssignableFrom(ScriptVariableType))
      {
        target = (Q) (object) Value;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
      {
        target = (Q) (object) new GH_Integer((int) Value);
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    class Proxy : IGH_GooProxy
    {
      readonly BuiltInParameterGroup proxyOwner;
      public Proxy(BuiltInParameterGroup owner) { proxyOwner = owner; UserString = FormatInstance(); }
      public IGH_Goo ProxyOwner => proxyOwner;
      public bool Valid => proxyOwner.IsValid;
      public bool IsParsable => true;
      public string UserString { get; set; }
      public void Construct() { }
      public string FormatInstance() => proxyOwner.Value.ToString();
      public bool FromString(string str)
      {
        if (Enum.TryParse(str, out Autodesk.Revit.DB.BuiltInParameterGroup builtInParameterGroup))
        {
          proxyOwner.Value = builtInParameterGroup;
          return true;
        }

        return false;
      }
      public string MutateString(string str) => str.Trim();
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public override string ToString() => LabelUtils.GetLabelFor(Value);
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class ParameterKey : ElementIdNonGeometryParam<Types.ParameterKey, Autodesk.Revit.DB.ParameterElement>
  {
    public override Guid ComponentGuid => new Guid("A550F532-8C68-460B-91F3-DA0A5A0D42B5");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;

    public ParameterKey() : base("Parameter Key", "Parameter Key", "Represents a Revit parameter definition.", "Params", "Revit") { }
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

    int parameterId = (int) BuiltInParameter.INVALID;
    public int ParameterId
    {
      get
      {
        if (parameterId == (int) BuiltInParameter.INVALID)
        {
          if (Enum.TryParse(Name, out BuiltInParameter builtInParameter))
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
    public ParameterParam(Autodesk.Revit.DB.Parameter p) : this()
    {
      MutableNickName = false;
      ParameterId = p.Id.IntegerValue;

      try { NickName = LabelUtils.GetLabelFor(p.Definition.ParameterGroup) + " : " + p.Definition.Name; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { NickName = p.Definition.Name; }

      try { Description = p.StorageType == StorageType.ElementId ? "ElementId" : LabelUtils.GetLabelFor(p.Definition.ParameterType); }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException)
      { Description = p.Definition.UnitType == UnitType.UT_Number ? "Enumerate" : LabelUtils.GetLabelFor(p.Definition.UnitType); }
    }
  }

  public class BuiltInParameterGroup : GH_PersistentParam<Types.BuiltInParameterGroup>
  {
    public override Guid ComponentGuid => new Guid("3D9979B4-65C8-447F-BCEA-3705249DF3B6");
    public override GH_Exposure Exposure => GH_Exposure.quarternary;

    public BuiltInParameterGroup() : base("Parameter Group", "Parameter Group", "Represents a Revit parameter group.", "Params", "Revit") { }
  }
}
