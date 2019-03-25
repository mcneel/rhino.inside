using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using Grasshopper.Kernel.Parameters;
using Grasshopper.Kernel.Special;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class ParameterElement : Element
  {
    public override string TypeName => "Revit Parameter element";
    public override string TypeDescription => "Represents a Revit parameter element";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.ParameterElement);
    public static explicit operator Autodesk.Revit.DB.ParameterElement(ParameterElement self) => Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.ParameterElement;

    #region IGH_PersitentGoo
    public override Guid ReferenceID
    {
      get => (Revit.ActiveDBDocument?.GetElement(this) as SharedParameterElement)?.GuidValue ?? base.ReferenceID;
      set => Value = SharedParameterElement.Lookup(Revit.ActiveDBDocument, value)?.Id ?? ElementId.InvalidElementId;
    }
    #endregion

    public ParameterElement() { }
    public ParameterElement(Autodesk.Revit.DB.ParameterElement parameterElement) : base(parameterElement) { }
    public ParameterElement(Autodesk.Revit.DB.ElementId elementId)               : base(elementId) { }

    public override sealed bool CastFrom(object source)
    {
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      switch (source)
      {
        case Autodesk.Revit.DB.Parameter parameter:
          if(parameter.Id != ElementId.InvalidElementId)
          {
            Value = parameter.Id;
            UniqueID = string.Empty;
            return true;
          }
          break;
        case Autodesk.Revit.DB.ElementId id:
          if (Enum.IsDefined(typeof(BuiltInParameter), id.IntegerValue))
          {
            Value = new ElementId(id.IntegerValue);
            UniqueID = string.Empty;
            return true;
          }
          break;
        case int integer:
          if (Enum.IsDefined(typeof(BuiltInParameter), integer))
          {
            Value = new ElementId(integer);
            UniqueID = string.Empty;
            return true;
          }
          break;
      }

      return base.CastFrom(source);
    }

    public override string ToString()
    {
      if (IsValid)
      {
        var element = (Autodesk.Revit.DB.ParameterElement) this;
        if (element != null)
          return "Revit " + element.GetType().Name + " \"" + element.Name + "\"";

        try
        {
          var builtInParameterLabel = LabelUtils.GetLabelFor((BuiltInParameter) Value.IntegerValue);
          if (builtInParameterLabel != null)
            return "Revit BuiltInParameter \"" + builtInParameterLabel + "\"";
        }
        catch (Autodesk.Revit.Exceptions.InvalidOperationException) { }
      }

      return base.ToString();
    }
  }

  public class Parameter : GH_Goo<Autodesk.Revit.DB.Parameter>
  {
    public override string TypeName => "Revit Parameter";
    public override string TypeDescription => "Represents a Revit Parameter";
    protected Type ScriptVariableType => typeof(Autodesk.Revit.DB.Parameter);
    public override bool IsValid => Value != null;
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    double ToRhino(double value, UnitType unit)
    {
      switch (unit)
      {
        case UnitType.UT_Length: return value * Math.Pow(Revit.ModelUnits, 1.0);
        case UnitType.UT_Area:   return value * Math.Pow(Revit.ModelUnits, 2.0);
        case UnitType.UT_Volume: return value * Math.Pow(Revit.ModelUnits, 3.0);
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
            target = (Q) (object) new GH_Boolean(Value.AsInteger() != 0);
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
          {
            target = (Q) (object) new GH_Integer(Value.AsInteger());
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Number)))
          {
            target = (Q) (object) new GH_Number((double)Value.AsInteger());
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Colour)))
          {
            int value = Value.AsInteger();
            int r = value % 256;
            value /= 256;
            int g = value % 256;
            value /= 256;
            int b = value % 256;

            target = (Q) (object) new GH_Colour(System.Drawing.Color.FromArgb(r, g, b));
            return true;
          }
          break;
        case StorageType.Double:
          if (typeof(Q).IsAssignableFrom(typeof(GH_Number)))
          {
            target = (Q) (object) new GH_Number(ToRhino(Value.AsDouble(), Value.Definition.UnitType));
            return true;
          }
          else if (typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
          {
            var value = Math.Round(ToRhino(Value.AsDouble(), Value.Definition.UnitType));
            if (int.MinValue <= value && value <= int.MaxValue)
            {
              target = (Q) (object) new GH_Integer((int) value);
              return true;
            }
          }
          break;
        case StorageType.String:
          if (typeof(Q).IsAssignableFrom(typeof(GH_String)))
          {
            target = (Q) (object) new GH_String(Value.AsString());
            return true;
          }
          break;
        case StorageType.ElementId:
          if (typeof(Q).IsSubclassOf(typeof(ID)))
          {
            target = (Q) (object) ID.Make(Value.AsElementId());
            return true;
          }
          break;
      }

      return base.CastTo<Q>(ref target);
    }

    public override string ToString()
    {
      if (IsValid)
      {
        string value = null;
        if (Value.HasValue)
        {
          value = Value.AsValueString();
          if (value == null)
          {
            switch (Value.StorageType)
            {
              case StorageType.Integer: value = Value.AsInteger().ToString(); break;
              case StorageType.Double:  value = Value.AsDouble().ToString(); break;
              case StorageType.String:  value = Value.AsString(); break;
              case StorageType.ElementId:
                var id = Value.AsElementId();
                var e = Revit.ActiveDBDocument.GetElement(id);
                value = e?.Name; break;
              default: value = null; break;
            }
          }
        }
        return value;
      }

      return "Null " + TypeName;
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class ParameterElement : GH_Param<Types.ParameterElement>
  {
    public override Guid ComponentGuid => new Guid("A550F532-8C68-460B-91F3-DA0A5A0D42B5");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("P");

    public ParameterElement() : base("ParameterElement", "ParameterElement", "Represents a Revit parameter definition.", "Revit", "Parameter", GH_ParamAccess.item) { }
  }

  public class Parameter : GH_Param<Types.Parameter>
  {
    public override Guid ComponentGuid => new Guid("3E13D360-4B29-42C7-8F3E-2AB8F74B4EA8");
    public override GH_Exposure Exposure => GH_Exposure.hidden;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon(".");

    public Parameter() : base("Parameter", "Parameter", "Represents a Revit parameter.", "Revit", "Parameter", GH_ParamAccess.item) { }
    protected Parameter(string name, string nickname, string description, string category, string subcategory, GH_ParamAccess access) :
    base(name, nickname, description, category, subcategory, access) { }
  }

  public class ParameterParam : Parameter
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
        Name = parameterId.ToBuiltInParameter().ToString();
      }
    }

    public ParameterParam() : base("INVALID", "Invalid", "Represents a Revit parameter instance.", "Revit", "Parameter", GH_ParamAccess.item) { }
    public ParameterParam(Autodesk.Revit.DB.Parameter p) : this()
    {
      ParameterId = p.Id.IntegerValue;

      try { NickName = LabelUtils.GetLabelFor(p.Definition.ParameterGroup) + " : " + p.Definition.Name; }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException) { NickName = p.Definition.Name; }

      try { Description = p.StorageType == StorageType.ElementId ? "ElementId" : LabelUtils.GetLabelFor(p.Definition.ParameterType); }
      catch (Autodesk.Revit.Exceptions.InvalidOperationException)
      { Description = p.Definition.UnitType == UnitType.UT_Number ? "Enumerate" : LabelUtils.GetLabelFor(p.Definition.UnitType); }
    }
  }
  public class BuiltInParameterGroups : GH_ValueList
  {
    public override Guid ComponentGuid => new Guid("5D331B12-DA6C-46A7-AA13-F463E42650D1");
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("G");

    public BuiltInParameterGroups()
    {
      Category = "Revit";
      SubCategory = "Parameter";
      Name = "BuiltInParameterGroup";
      NickName = "BuiltInParameterGroup";
      Description = "Provides a picker of a BuiltInParameterGroup";

      ListItems.Clear();

      foreach (var builtInParameterGroup in Enum.GetValues(typeof(BuiltInParameterGroup)).Cast<BuiltInParameterGroup>().OrderBy((x) => LabelUtils.GetLabelFor(x)))
      {
        ListItems.Add(new GH_ValueListItem(LabelUtils.GetLabelFor(builtInParameterGroup), ((int) builtInParameterGroup).ToString()));
        if (builtInParameterGroup == BuiltInParameterGroup.PG_IDENTITY_DATA)
          SelectItem(ListItems.Count - 1);
      }
    }
  }

  public class BuiltInParameterByName : ValueListPicker
  {
    public override Guid ComponentGuid => new Guid("C1D96F56-F53C-4DFC-8090-EC2050BDBB66");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("P*");

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
      var selectedItems = new List<string>();
      {
        foreach (var item in ListItems)
          if (item.Selected)
            selectedItems.Add(item.Expression);
      }

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
  public class ParameterDecompose : GH_Component
  {
    public override Guid ComponentGuid => new Guid("3BDE5890-FB80-4AF2-B9AC-373661756BDA");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("V{");

    public ParameterDecompose()
    : base("Parameter.Decompose", "Parameter.Decompose", "Decompose a parameter value", "Revit", "Parameter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.Parameter(), "Value", "V", "Parameter value to decompose", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddIntegerParameter("Group", "G", "Parameter group", GH_ParamAccess.item);
      manager.AddIntegerParameter("Type", "T", "Parameter type", GH_ParamAccess.item);
      manager.AddIntegerParameter("Unit", "U", "Unit type", GH_ParamAccess.item);
      manager.AddBooleanParameter("IsReadOnly", "R", "Parameter is Read Only", GH_ParamAccess.item);
      manager.AddBooleanParameter("UserModifiable", "U", "Parameter is UserModifiable ", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.Parameter parameter = null;
      if (!DA.GetData("Value", ref parameter))
        return;

      DA.SetData("Group", (int) parameter?.Definition.ParameterGroup);
      DA.SetData("Type", (int) parameter?.Definition.ParameterType);
      DA.SetData("Unit", (int) parameter?.Definition.UnitType);
      DA.SetData("IsReadOnly", parameter?.IsReadOnly);
      DA.SetData("UserModifiable", parameter?.UserModifiable);
    }
  }

  public class ParameterElementDecompose : GH_Component
  {
    public override Guid ComponentGuid => new Guid("A80F4919-2387-4C78-BE2B-2F35B2E60298");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("P{");

    public ParameterElementDecompose()
    : base("ParameterElement.Decompose", "ParameterElement.Decompose", "Decompose a parameter definition", "Revit", "Parameter")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ParameterElement(), "Parameter", "P", "Parameter to decompose", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddTextParameter("Name", "N", "Parameter name", GH_ParamAccess.item);
      manager.AddIntegerParameter("StorageType", "T", "Parameter value type", GH_ParamAccess.item);
      manager.AddBooleanParameter("Visible", "V", "Parameter is visible in UI", GH_ParamAccess.item);
      manager.AddParameter(new Param_Guid(), "Guid", "ID", "Parameter BuiltInParameter id", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Types.ParameterElement parameter = null;
      if (!DA.GetData("Parameter", ref parameter))
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
        //var storageType = StorageType.None;
        DA.SetData("Name", definition?.Name);
        DA.SetData("StorageType", definition?.ParameterType.ToStorageType());
        DA.SetData("Visible", definition?.Visible);
        DA.SetData("Guid", (parameterElement as SharedParameterElement)?.GuidValue ?? Guid.Empty);
      }
    }
  }
}
