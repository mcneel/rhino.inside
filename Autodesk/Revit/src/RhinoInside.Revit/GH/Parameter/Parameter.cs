using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Parameters;
using Grasshopper.Kernel.Special;
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
    public ParameterKey(Autodesk.Revit.DB.ElementId elementId)               : base(elementId) { }

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
  public class ParameterKey : ElementIdNonGeometryParam<Types.ParameterKey>
  {
    public override Guid ComponentGuid => new Guid("A550F532-8C68-460B-91F3-DA0A5A0D42B5");
    public override GH_Exposure Exposure => GH_Exposure.tertiary;

    public ParameterKey() : base("ParameterKey", "ParameterKey", "Represents a Revit parameter definition.", "Params", "Revit") { }
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
    public override GH_Exposure Exposure => GH_Exposure.tertiary;

    public BuiltInParameterGroup() : base("BuiltInParameterGroup", "BuiltInParameterGroup", "Represents a Revit parameter group.", "Params", "Revit") { }
  }

  public class BuiltInParameterGroups : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("5D331B12-DA6C-46A7-AA13-F463E42650D1");
    public override GH_Exposure Exposure => GH_Exposure.tertiary;

    public BuiltInParameterGroups()
    {
      Category = "Revit";
      SubCategory = "Parameter";
      Name = "BuiltInParameterGroups";
      NickName = "BuiltInParameterGroups";
      Description = "Provides a picker of a BuiltInParameterGroup";

      ListItems.Clear();

      foreach (var builtInParameterGroup in Enum.GetValues(typeof(Autodesk.Revit.DB.BuiltInParameterGroup)).Cast<Autodesk.Revit.DB.BuiltInParameterGroup>().OrderBy((x) => LabelUtils.GetLabelFor(x)))
      {
        ListItems.Add(new GH_ValueListItem(LabelUtils.GetLabelFor(builtInParameterGroup), ((int) builtInParameterGroup).ToString()));
        if (builtInParameterGroup == Autodesk.Revit.DB.BuiltInParameterGroup.PG_IDENTITY_DATA)
          SelectItem(ListItems.Count - 1);
      }
    }
  }

  public class BuiltInParameterByName : ValueList
  {
    public override Guid ComponentGuid => new Guid("C1D96F56-F53C-4DFC-8090-EC2050BDBB66");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public BuiltInParameterByName()
    {
      Name = "BuiltInParameter.ByName";
      Description = "Provides a BuiltInParameter picker";
    }

    public override void AddedToDocument(GH_Document document)
    {
      if (NickName == Name)
        NickName = "'Parameter name here…";

      base.AddedToDocument(document);
    }

    protected override void RefreshList(string ParamName)
    {
      var selectedItems = ListItems.Where(x => x.Selected).Select(x => x.Expression).ToList();

      ListItems.Clear();
      if (ParamName.Length == 0 || ParamName[0] == '\'')
        return;

      if (Revit.ActiveDBDocument != null)
      {
        int selectedItemsCount = 0;
        {
          foreach (var builtInParameter in Enum.GetNames(typeof(BuiltInParameter)))
          {
            if (!builtInParameter.IsSymbolNameLike(ParamName))
              continue;

            if (SourceCount == 0)
            {
              // If is a no pattern match update NickName case
              if (string.Equals(builtInParameter, ParamName, StringComparison.OrdinalIgnoreCase))
                ParamName = builtInParameter;
            }

            var builtInParameterValue = (BuiltInParameter) Enum.Parse(typeof(BuiltInParameter), builtInParameter);

            var label = string.Empty;
            try { label = LabelUtils.GetLabelFor(builtInParameterValue); }
            catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }

            var item = new GH_ValueListItem(builtInParameter + " - \"" + label + "\"", ((int) builtInParameterValue).ToString());
            item.Selected = selectedItems.Contains(item.Expression);
            ListItems.Add(item);

            selectedItemsCount += item.Selected ? 1 : 0;
          }
        }

        // If no selection and we are not in CheckList mode try to select default model types
        if (ListItems.Count == 0)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("No ElementType found using pattern \"{0}\"", ParamName));
        }
      }
    }

    protected override void RefreshList(IEnumerable<IGH_Goo> goos)
    {
      ListItems.Clear();
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class ParameterKeyDecompose : Component
  {
    public override Guid ComponentGuid => new Guid("A80F4919-2387-4C78-BE2B-2F35B2E60298");

    public ParameterKeyDecompose()
    : base("ParameterKey.Decompose", "ParameterKey.Decompose", "Decompose a parameter definition", "Revit", "Parameter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterKey(), "ParameterKey", "K", "Parameter key to decompose", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", "Parameter name", GH_ParamAccess.item);
      manager.AddIntegerParameter("StorageType", "T", "Parameter value type", GH_ParamAccess.item);
      manager.AddBooleanParameter("Visible", "V", "Parameter is visible in UI", GH_ParamAccess.item);
      manager.AddParameter(new Param_Guid(), "Guid", "ID", "Shared Parameter global identifier", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Types.ParameterKey parameter = null;
      if (!DA.GetData("ParameterKey", ref parameter))
        return;

      if (Enum.IsDefined(typeof(BuiltInParameter), parameter.Value.IntegerValue))
      {
        var builtInParameter = (BuiltInParameter) parameter.Value.IntegerValue;
        DA.SetData("Name", LabelUtils.GetLabelFor(builtInParameter));
        DA.SetData("StorageType", Revit.ActiveDBDocument.get_TypeOfStorage(builtInParameter));
        DA.SetData("Visible", true);
        DA.SetData("Guid", Guid.Empty);
      }
      else if (Revit.ActiveDBDocument.GetElement(parameter.Value) is ParameterElement parameterElement)
      {
        var definition = parameterElement.GetDefinition();
        DA.SetData("Name", definition?.Name);
        DA.SetData("StorageType", definition?.ParameterType.ToStorageType());
        DA.SetData("Visible", definition?.Visible);
        DA.SetData("Guid", (parameterElement as SharedParameterElement)?.GuidValue ?? Guid.Empty);
      }
    }
  }

  public class ParameterValueDecompose : Component
  {
    public override Guid ComponentGuid => new Guid("3BDE5890-FB80-4AF2-B9AC-373661756BDA");

    public ParameterValueDecompose()
    : base("ParameterValue.Decompose", "ParameterValue.Decompose", "Decompose a parameter value", "Revit", "Parameter")
    { }

    protected override ElementFilter ElementFilter => new Autodesk.Revit.DB.ElementClassFilter(typeof(ParameterElement));
    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterValue(), "ParameterValue", "V", "Parameter value to decompose", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.BuiltInParameterGroup(), "Group", "G", "Parameter group", GH_ParamAccess.item);
      manager.AddIntegerParameter("Type", "T", "Parameter type", GH_ParamAccess.item);
      manager.AddIntegerParameter("Unit", "U", "Unit type", GH_ParamAccess.item);
      manager.AddBooleanParameter("IsReadOnly", "R", "Parameter is Read Only", GH_ParamAccess.item);
      manager.AddBooleanParameter("UserModifiable", "U", "Parameter is UserModifiable ", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Parameter parameter = null;
      if (!DA.GetData("ParameterValue", ref parameter))
        return;

      DA.SetData("Group", parameter?.Definition.ParameterGroup);
      DA.SetData("Type", (int) parameter?.Definition.ParameterType);
      DA.SetData("Unit", (int) parameter?.Definition.UnitType);
      DA.SetData("IsReadOnly", parameter?.IsReadOnly);
      DA.SetData("UserModifiable", parameter?.UserModifiable);
    }
  }

  public class ParameterByName : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("84AB6F3C-BB4B-48E4-9175-B7F40791BB7F");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

    public ParameterByName() : base
    (
      "AddParameterKey.ByName", "ByName",
      "Given its Name, it adds a Parameter definition to the active Revit document",
      "Revit", "Parameter"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterKey(), "ParameterKey", "K", "New Parameter definition", GH_ParamAccess.item);
    }

    void ReconstructParameterByName
    (
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      [Description("Parameter Name")] string name,
      [Description("Overwrite Parameter definition if found"), Optional, DefaultValue(false)] bool overwrite
    )
    {
      var app = Revit.ActiveUIApplication.Application;

      var parameterType = ParameterType.Text;
      var parameterGroup = BuiltInParameterGroup.PG_DATA;
      bool instance = true;
      bool visible = true;

      if (!overwrite)
      {
        using (var bindings = doc.ParameterBindings.ReverseIterator())
        {
          while (bindings.MoveNext())
          {
            if (bindings.Key is InternalDefinition def)
            {
              if
              (
                def.Name == name &&
                def.Visible == visible &&
                def.ParameterType == parameterType &&
                def.ParameterGroup == parameterGroup &&
                bindings.Current is InstanceBinding)
              {
                if (doc.GetElement(def.Id) is ParameterElement parameterElement)
                {
                  ReplaceElement(ref element, parameterElement);
                  throw new WarningException($"A parameter called \"{name}\" is already in the document");
                }
              }
            }
          }
        }
      }

      using (var defOptions = new ExternalDefinitionCreationOptions(name, parameterType) { Visible = visible })
      {
        string sharedParametersFilename = app.SharedParametersFilename;
        string tempParametersFilename = Path.GetTempFileName() + ".txt";

        ExternalDefinition definition = null;
        try
        {
          // Create Temp Shared Parameters File
          {
            using (File.Create(tempParametersFilename)) { }
            app.SharedParametersFilename = tempParametersFilename;
          }
          definition = app.OpenSharedParameterFile().Groups.Create(parameterGroup.ToString()).Definitions.Create(defOptions) as ExternalDefinition;
        }
        finally
        {
          // Restore User Shared Parameters File
          app.SharedParametersFilename = sharedParametersFilename;
          File.Delete(tempParametersFilename);
        }

        if (overwrite || !doc.ParameterBindings.Contains(definition))
        {
          // TODO : Ask for categories
          var categorySet = new CategorySet();
          foreach (var category in doc.Settings.Categories.Cast<Category>().Where(category => category.AllowsBoundParameters))
            categorySet.Insert(category);

          var binding = instance ? (ElementBinding) new InstanceBinding(categorySet) : (ElementBinding) new TypeBinding(categorySet);

          if (!doc.ParameterBindings.Insert(definition, binding, parameterGroup))
            throw new InvalidOperationException("Failed while creating the parameter binding.");
        }

        ReplaceElement(ref element, SharedParameterElement.Lookup(doc, definition.GUID));
      }
    }
  }
}
