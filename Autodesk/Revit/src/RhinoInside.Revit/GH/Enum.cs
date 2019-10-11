using System;
using System.Collections.Generic;
using System.Windows.Forms;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Types
{
  public abstract class GH_Enumerate : GH_Integer
  {
    protected GH_Enumerate() { }
    protected GH_Enumerate(int value) : base(value) { }
  }

  public class GH_Enum<T> : GH_Enumerate
    where T : struct, IComparable, IFormattable, IConvertible
    //where T : Enum - C# 7.3 syntax
  {
    public static implicit operator T(GH_Enum<T> self) => (T) (object) self.Value;
    public GH_Enum() { }
    public GH_Enum(int value) : base(value) { }

    public override bool IsValid => Enum.IsDefined(typeof(T), Value);
    public override string TypeName => typeof(T).Name;
    public override string TypeDescription => $"{typeof(T).Module.Name} {TypeName}";

    public override bool CastFrom(object source)
    {
      if (source is IGH_Goo goo)
        source = goo.ScriptVariable();

      switch (source)
      {
        case int integer:
          if (Enum.IsDefined(typeof(T), integer))
          {
            Value = integer;
            return true;
          }
          break;
        case T value:
          Value = (int) (object) value;
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

      if (typeof(Q) == typeof(GH_Integer))
      {
        target = (Q) (object) new GH_Integer(Value);
        return true;
      }

      return base.CastTo<Q>(ref target);
    }
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();

    public override object ScriptVariable() => (T) (object) Value;

    class Proxy : IGH_GooProxy
    {
      readonly GH_Enum<T> owner;
      IGH_Goo IGH_GooProxy.ProxyOwner => owner;
      bool IGH_GooProxy.IsParsable => true;
      string IGH_GooProxy.UserString { get; set; }

      public Proxy(GH_Enum<T> o) { owner = o; (this as IGH_GooProxy).UserString = FormatInstance(); }
      public void Construct() { }
      public string FormatInstance() => Enum.Format(typeof(T), owner.Value, "G");
      public bool FromString(string str)
      {
        if (Enum.TryParse(str, out T value))
        {
          owner.Value = (int) (object) value;
          return true;
        }

        return false;
      }
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
  public abstract class Param_Enum<T> : GH_PersistentParam<T>
    where T : Types.GH_Enumerate
  {
    protected Param_Enum(string name, string abbreviation, string description, string category, string subcategory) :
      base(name, abbreviation, description, category, subcategory)
    { }

    protected override void Menu_AppendPromptOne(ToolStripDropDown menu) { }
    protected override void Menu_AppendPromptMore(ToolStripDropDown menu) { }

    protected override GH_GetterResult Prompt_Plural(ref List<T> values) => GH_GetterResult.cancel;
    protected override GH_GetterResult Prompt_Singular(ref T value) => GH_GetterResult.cancel;
  }
}
