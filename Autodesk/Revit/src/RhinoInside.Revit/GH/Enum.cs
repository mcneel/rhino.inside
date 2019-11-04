using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;
using Grasshopper.GUI;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Types
{
  public abstract class GH_Enumerate : GH_Integer
  {
    protected GH_Enumerate() { }
    protected GH_Enumerate(int value) : base(value) { }
    public abstract Type UnderlyingEnumType { get; }
    public override IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    static Dictionary<Type, Tuple<Type, Type>> LookForEnums(Assembly assembly)
    {
      var result = new Dictionary<Type, Tuple<Type, Type>>();

      foreach (var type in assembly.ExportedTypes.Where(x => x.IsSubclassOf(typeof(GH_Enumerate))))
      {
        bool typeFound = false;
        var gooType = type;
        while (gooType != typeof(GH_Enumerate))
        {
          if (gooType.IsConstructedGenericType && gooType.GetGenericTypeDefinition() == typeof(GH_Enum<>))
          {
            var valueType = gooType.GetGenericArguments()[0];
            foreach (var param in assembly.ExportedTypes.Where(x => x.GetInterfaces().Contains(typeof(IGH_Param))))
            {
              if (!param.IsClass)
                continue;

              var paramType = param;
              while (paramType != typeof(GH_ActiveObject))
              {
                if (paramType.IsConstructedGenericType && paramType.GetGenericTypeDefinition() == typeof(Parameters.Param_Enum<>))
                {
                  if (paramType.GetGenericArguments()[0] == type)
                  {
                    result.Add(valueType, Tuple.Create(param.GetType(), type));
                    typeFound = true;
                    break;
                  }
                }

                paramType = paramType.BaseType;
              }

              if (typeFound)
                break;
            }

            if (!typeFound)
            {
              result.Add(valueType, Tuple.Create(typeof(Parameters.Param_Enum<>).MakeGenericType(type), type));
              typeFound = true;
            }
          }

          if (typeFound)
            break;

          gooType = gooType.BaseType;
        }
      }

      return result;
    }

    static readonly Dictionary<Type, Tuple<Type, Type>> EnumTypes = LookForEnums(Assembly.GetCallingAssembly());
    public static bool TryGetParamTypes(Type type, out Tuple<Type, Type> paramTypes) =>
      EnumTypes.TryGetValue(type, out paramTypes);

    public virtual Array GetEnumValues() => Enum.GetValues(UnderlyingEnumType);
  }

  public abstract class GH_Enum<T> : GH_Enumerate
    where T : Enum
  {
    public GH_Enum() { }
    public GH_Enum(T value) =>  m_value = (int) (object) value;
    public new T Value { get => (T) (object) base.Value; set => base.Value = (int) (object) value; }

    public override bool IsValid => Enum.IsDefined(typeof(T), Value);
    public override string TypeName
    {
      get
      {
        var value = GetType().GetTypeInfo().GetCustomAttribute(typeof(DisplayNameAttribute)) as DisplayNameAttribute;
        return value?.DisplayName ?? typeof(T).Name;
      }
    }
    public override string TypeDescription
    {
      get
      {
        var value = GetType().GetTypeInfo().GetCustomAttribute(typeof(DescriptionAttribute)) as DescriptionAttribute;
        return value?.Description ?? $"{typeof(T).Module.Name} {TypeName}";
      }
    }
    public override Type UnderlyingEnumType => typeof(T);

    public override bool CastFrom(object source)
    {
      switch (source)
      {
        case GH_Integer integer:
          if (Enum.IsDefined(typeof(T), integer.Value))
          {
            base.Value = integer.Value;
            return true;
          }
          break;
        case T value:
          Value = value;
          return true;
      }
      return false;
    }
    public override bool CastTo<Q>(ref Q target)
    {
      if (typeof(Q) == typeof(T))
      {
        target = (Q) (object) Value;
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public override object ScriptVariable() => Value;

    class Proxy : IGH_GooProxy
    {
      readonly GH_Enum<T> owner;
      IGH_Goo IGH_GooProxy.ProxyOwner => owner;
      bool IGH_GooProxy.IsParsable => true;
      string IGH_GooProxy.UserString { get; set; }

      public Proxy(GH_Enum<T> o) { owner = o; (this as IGH_GooProxy).UserString = FormatInstance(); }
      public void Construct() { }
      public string FormatInstance() => Enum.Format(typeof(T), owner.Value, "G");
      public bool FromString(string str) => Enum.TryParse(str, out owner.m_value);
      public string MutateString(string str) => str.Trim();

      public bool Valid => owner.IsValid;
      public Type Type => typeof(T);
      public string Name => owner.ToString();
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);
    public override string ToString() => Value.ToString();
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class Param_Enum<T> : GH_PersistentParam<T>
    where T : Types.GH_Enumerate
  {
    protected Param_Enum(string name, string abbreviation, string description, string category, string subcategory) :
      base(name, abbreviation, description, category, subcategory)
    { }

    public Param_Enum() :
    base
    (
      typeof(T).Name,
      typeof(T).Name.Substring(0, 1),
      string.Empty,
      string.Empty,
      string.Empty
    )
    {
      if (GetType().GetTypeInfo().GetCustomAttribute(typeof(DisplayNameAttribute)) is DisplayNameAttribute name)
      {
        Name = name.DisplayName;
        NickName = name.DisplayName.Substring(0, 1);
      }

      if (GetType().GetTypeInfo().GetCustomAttribute(typeof(NickNameAttribute)) is NickNameAttribute nick)
        NickName = nick.NickName;

      if (GetType().GetTypeInfo().GetCustomAttribute(typeof(DescriptionAttribute)) is DescriptionAttribute description)
        Description = description.Description;
    }

    public override Guid ComponentGuid => typeof(T).GUID;
    public override GH_Exposure Exposure
    {
      get
      {
        if (GetType().GetTypeInfo().GetCustomAttribute(typeof(ExposureAttribute)) is ExposureAttribute exposure)
          return exposure.Exposure;

        return GH_Exposure.hidden;
      }
    }
    protected override void Menu_AppendPromptOne(ToolStripDropDown menu) { }
    protected override void Menu_AppendPromptMore(ToolStripDropDown menu) { }

    protected override GH_GetterResult Prompt_Plural(ref List<T> values) => GH_GetterResult.cancel;
    protected override GH_GetterResult Prompt_Singular(ref T value) => GH_GetterResult.cancel;

    public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
    {
      if (Kind > GH_ParamKind.input || DataType == GH_ParamData.remote)
      {
        base.AppendAdditionalMenuItems(menu);
        return;
      }

      Menu_AppendWireDisplay(menu);
      Menu_AppendDisconnectWires(menu);

      Menu_AppendReverseParameter(menu);
      Menu_AppendFlattenParameter(menu);
      Menu_AppendGraftParameter(menu);
      Menu_AppendSimplifyParameter(menu);

      var current = InstantiateT();
      if (SourceCount == 0 && PersistentDataCount == 1)
      {
        if(PersistentData.get_FirstItem(true) is T firstValue)
          current.Value = firstValue.Value;
      }

      var values = current.GetEnumValues();
      if (values.Length < 7)
      {
        Menu_AppendSeparator(menu);
        foreach (var e in values)
        {
          var tag = InstantiateT(); tag.Value = (int) e;
          var item = Menu_AppendItem(menu, tag.ToString(), Menu_NamedValueClicked, SourceCount == 0, (int) e == current.Value);
          item.Tag = tag;
        }
        Menu_AppendSeparator(menu);
      }
      else
      {
        var listBox = new ListBox();
        foreach (var e in values)
        {
          var tag = InstantiateT(); tag.Value = (int) e;
          int index = listBox.Items.Add(tag);
          if ((int) e == current.Value)
            listBox.SelectedIndex = index;
        }

        listBox.BorderStyle = BorderStyle.FixedSingle;

        listBox.SelectedIndexChanged += ListBox_SelectedIndexChanged;

        listBox.Width = (int) (200 * GH_GraphicsUtil.UiScale);
        listBox.Height = (int) (100 * GH_GraphicsUtil.UiScale);
        Menu_AppendCustomItem(menu, listBox);
      }

      Menu_AppendDestroyPersistent(menu);
      Menu_AppendInternaliseData(menu);

      if(Exposure != GH_Exposure.hidden)
        Menu_AppendExtractParameter(menu);
    }

    private void ListBox_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (sender is ListBox listBox)
      {
        if (listBox.SelectedIndex != -1)
        {
          if (listBox.Items[listBox.SelectedIndex] is T value)
          {
            RecordUndoEvent($"Set: {value}");
            PersistentData.Clear();
            PersistentData.Append(value.Duplicate() as T);
          }
        }

        ExpireSolution(true);
      }
    }

    private void Menu_NamedValueClicked(object sender, EventArgs e)
    {
      if (sender is ToolStripMenuItem item)
      {
        if (item.Tag is T value)
        {
          RecordUndoEvent($"Set: {value}");
          PersistentData.Clear();
          PersistentData.Append(value.Duplicate() as T);

          ExpireSolution(true);
        }
      }
    }
  }
}
