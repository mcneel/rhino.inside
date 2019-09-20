using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI.Events;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Parameters;
using Grasshopper.Kernel.Types;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Runtime.InteropServices
{
  public enum Optional { Nothig = -1 }

  public struct Optional<T>
  {
    private readonly T value;
    public readonly bool HasValue;

    public Optional(T value)
    {
      this.value = value;
      HasValue = true;
    }

    public T Value
    {
      get
      {
        if (HasValue) return value;
        throw new InvalidCastException();
      }
    }

    public bool IsNullOrNothing => !HasValue || value == null;

    public override bool Equals(object other)
    {
      return (other is Optional<T> otherEmpty) ? this == otherEmpty : false;
    }

    public override int GetHashCode() => HasValue ? value.GetHashCode() : (int) Optional.Nothig;
    public override string ToString() => HasValue ? value.ToString() : "";

    public static implicit operator Optional<T>(Optional _) => new Optional<T>();
    public static bool operator ==(Optional<T> value, Optional _) => !value.HasValue;
    public static bool operator !=(Optional<T> value, Optional _) => value.HasValue;

    public static implicit operator Optional<T>(T value) => new Optional<T>(value);
    public static bool operator ==(Optional<T> value, T other) => value.HasValue ? value == other : false;
    public static bool operator !=(Optional<T> value, T other) => value.HasValue ? value != other : false;

    public static explicit operator T(Optional<T> value) => value.Value;
    public static bool operator ==(Optional<T> value, Optional<T> other) => value.HasValue == other.HasValue && Equals(value.value, other.value);
    public static bool operator !=(Optional<T> value, Optional<T> other) => value.HasValue != other.HasValue || !Equals(value.value, other.value);
  }

  [AttributeUsage(AttributeTargets.Parameter, AllowMultiple = false, Inherited = false)]
  public class NickNameAttribute : Attribute
  {
    public readonly string NickName;
    public NickNameAttribute(string nickName) => NickName = nickName;
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public abstract class TransactionalComponent : Component, ITransactionFinalizer, IFailuresPreprocessor
  {
    protected TransactionalComponent(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    protected static double LiteralLengthValue(double meters)
    {
      switch (Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem)
      {
        case Rhino.UnitSystem.None:
        case Rhino.UnitSystem.Inches:
        case Rhino.UnitSystem.Feet:
          return Math.Round(meters * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Meters, Rhino.UnitSystem.Feet))
                 * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Feet, Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem);
        default:
          return meters * Rhino.RhinoMath.UnitScale(Rhino.UnitSystem.Meters, Rhino.RhinoDoc.ActiveDoc.ModelUnitSystem);
      }
    }

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

    protected static T CopyParametersFrom<T>(T to, Element from) where T : Element
    {
      to.CopyParametersFrom(from);
      return to;
    }

    protected static void ReplaceElement<T>(ref T previous, T next, ICollection<BuiltInParameter> parametersMask = null) where T : Element
    {
      if (previous != null && previous != next)
      {
        next.CopyParametersFrom(previous, parametersMask);
        previous.Document.Delete(previous.Id);
      }

      previous = next;
    }

    protected static void ChangeElementTypeId(ref Element element, ElementId elementTypeId)
    {
      if (element != null && elementTypeId != element.GetTypeId())
      {
        var doc = element.Document;
        if (element.IsValidType(elementTypeId))
        {
          var newElmentId = element.ChangeTypeId(elementTypeId);
          if (newElmentId != ElementId.InvalidElementId)
            element = doc.GetElement(newElmentId);
        }
        else element = null;
      }
    }

    public bool SolveOptionalCategory(ref Optional<Category> category, Document doc, BuiltInCategory builtInCategory, string paramName)
    {
      bool wasOptional = category == Optional.Nothig;

      if (wasOptional)
        category = Autodesk.Revit.DB.Category.GetCategory(doc, builtInCategory) ??
        throw new ArgumentException($"No suitable Category is been found.", paramName);

      else if (category.Value == null)
        throw new ArgumentNullException(paramName);

      return wasOptional;
    }

    public bool SolveOptionalType<T>(ref Optional<T> type, Document doc, ElementTypeGroup group, string paramName) where T : ElementType
    {
      return SolveOptionalType(ref type, doc, group, (document, name) => throw new ArgumentNullException(paramName), paramName);
    }

    public bool SolveOptionalType<T>(ref Optional<T> type, Document doc, ElementTypeGroup group, Func<Document, string, T> recoveryAction, string paramName) where T : ElementType
    {
      bool wasOptional = type == Optional.Nothig;

      if (wasOptional)
        type = (T) doc.GetElement(doc.GetDefaultElementTypeId(group)) ??
        throw new ArgumentException($"No suitable {group} is been found.", paramName);

      else if (type.Value == null)
        type = (T) recoveryAction.Invoke(doc, paramName);

      return wasOptional;
    }

    public bool SolveOptionalType(ref Optional<FamilySymbol> type, Document doc, BuiltInCategory category, string paramName)
    {
      bool wasOptional = type == Optional.Nothig;

      if (wasOptional)
        type = doc.GetElement(doc.GetDefaultFamilyTypeId(new ElementId(category))) as FamilySymbol ??
               throw new ArgumentException("No suitable type is been found.", paramName);

      else if (type.Value == null)
        throw new ArgumentNullException(paramName);

      return wasOptional;
    }

    public bool SolveOptionalLevel(ref Optional<Level> level, Document doc, double elevation, string paramName)
    {
      bool wasOptional = level == Optional.Nothig;

      if (wasOptional)
        level = doc.FindLevelByElevation(elevation) ??
                throw new ArgumentException("No suitable level is been found.", paramName);

      else if (level.Value == null)
        throw new ArgumentNullException(paramName);

      return wasOptional;
    }

    public bool SolveOptionalLevel(ref Optional<Level> level, Document doc, Rhino.Geometry.Curve curve, string paramName)
    {
      return SolveOptionalLevel(ref level, doc, Math.Min(curve.PointAtStart.Z, curve.PointAtEnd.Z), paramName);
    }

    #region Reflection
    static Dictionary<Type, Tuple<Type, Type>> ParamTypes = new Dictionary<Type, Tuple<Type, Type>>()
    {
      { typeof(bool),                           Tuple.Create(typeof(Param_Boolean),           typeof(GH_Boolean))         },
      { typeof(int),                            Tuple.Create(typeof(Param_Integer),           typeof(GH_Integer))         },
      { typeof(double),                         Tuple.Create(typeof(Param_Number),            typeof(GH_Number))          },
      { typeof(string),                         Tuple.Create(typeof(Param_String),            typeof(GH_String))          },
      { typeof(Guid),                           Tuple.Create(typeof(Param_Guid),              typeof(GH_Guid))            },
      { typeof(DateTime),                       Tuple.Create(typeof(Param_Time),              typeof(GH_Time))            },

      { typeof(Rhino.Geometry.Transform),       Tuple.Create(typeof(Param_Transform),         typeof(GH_Transform))       },
      { typeof(Rhino.Geometry.Point3d),         Tuple.Create(typeof(Param_Point),             typeof(GH_Point))           },
      { typeof(Rhino.Geometry.Vector3d),        Tuple.Create(typeof(Param_Vector),            typeof(GH_Vector))          },
      { typeof(Rhino.Geometry.Plane),           Tuple.Create(typeof(Param_Plane),             typeof(GH_Plane))          },
      { typeof(Rhino.Geometry.Line),            Tuple.Create(typeof(Param_Line),              typeof(GH_Line))            },
      { typeof(Rhino.Geometry.Arc),             Tuple.Create(typeof(Param_Arc),               typeof(GH_Arc))             },
      { typeof(Rhino.Geometry.Circle),          Tuple.Create(typeof(Param_Circle),            typeof(GH_Circle))          },
      { typeof(Rhino.Geometry.Curve),           Tuple.Create(typeof(Param_Curve),             typeof(GH_Curve))           },
      { typeof(Rhino.Geometry.Surface),         Tuple.Create(typeof(Param_Surface),           typeof(GH_Surface))         },
      { typeof(Rhino.Geometry.Brep),            Tuple.Create(typeof(Param_Brep),              typeof(GH_Brep))            },
//    { typeof(Rhino.Geometry.Extrusion),       Tuple.Create(typeof(Param_Extrusion),         typeof(GH_Extrusion))       },
      { typeof(Rhino.Geometry.Mesh),            Tuple.Create(typeof(Param_Mesh),              typeof(GH_Mesh))            },
      { typeof(Rhino.Geometry.SubD),            Tuple.Create(typeof(Param_SubD),              typeof(GH_SubD))            },

      { typeof(IGH_Goo),                        Tuple.Create(typeof(Param_GenericObject),     typeof(IGH_Goo))            },
      { typeof(IGH_GeometricGoo),               Tuple.Create(typeof(Param_Geometry),          typeof(IGH_GeometricGoo))   },

      { typeof(Autodesk.Revit.DB.Category),     Tuple.Create(typeof(Parameters.Category),     typeof(Types.Category))     },
      { typeof(Autodesk.Revit.DB.Element),      Tuple.Create(typeof(Parameters.Element),      typeof(Types.Element))      },
      { typeof(Autodesk.Revit.DB.ElementType),  Tuple.Create(typeof(Parameters.ElementType),  typeof(Types.ElementType))  },
      { typeof(Autodesk.Revit.DB.Material),     Tuple.Create(typeof(Parameters.Material),     typeof(Types.Material))     },
      { typeof(Autodesk.Revit.DB.SketchPlane),  Tuple.Create(typeof(Parameters.SketchPlane),  typeof(Types.SketchPlane))  },
      { typeof(Autodesk.Revit.DB.Level),        Tuple.Create(typeof(Parameters.Level),        typeof(Types.Level))        },
    };

    protected virtual bool TryGetParamTypes(Type type, out Tuple<Type, Type> paramTypes)
    {
      if (type.IsEnum)
      {
        paramTypes = Tuple.Create(typeof(Param_Integer), typeof(GH_Integer));
        return true;
      }

      if (!ParamTypes.TryGetValue(type, out paramTypes))
      {
        if (typeof(Autodesk.Revit.DB.ElementType).IsAssignableFrom(type))
        {
          paramTypes = Tuple.Create(typeof(Parameters.ElementType), typeof(Types.ElementType));
          return true;
        }

        if (typeof(Autodesk.Revit.DB.Element).IsAssignableFrom(type))
        {
          paramTypes = Tuple.Create(typeof(Parameters.Element), typeof(Types.Element));
          return true;
        }

        return false;
      }

      return true;
    }

    IGH_Param CreateParam(Type argumentType)
    {
      if (!TryGetParamTypes(argumentType, out var paramTypes))
        return new Param_GenericObject();

      return (IGH_Param) Activator.CreateInstance(paramTypes.Item1);
    }

    IGH_Goo CreateGoo(Type argumentType, object value)
    {
      if (!TryGetParamTypes(argumentType, out var paramTypes))
        return null;

      return (IGH_Goo) Activator.CreateInstance(paramTypes.Item2, new object[] { value });
    }

    protected Type GetParameterType(ParameterInfo parameter, out GH_ParamAccess access, out bool optional)
    {
      var parameterType = parameter.ParameterType;
      optional = parameter.IsDefined(typeof(OptionalAttribute), false);
      access = GH_ParamAccess.item;

      var genericType = parameterType.IsGenericType ? parameterType.GetGenericTypeDefinition() : null;

      if (genericType != null && genericType == typeof(Optional<>))
      {
        optional = true;
        parameterType = parameterType.GetGenericArguments()[0];
        genericType = parameterType.IsGenericType ? parameterType.GetGenericTypeDefinition() : null;
      }

      if (genericType != null && genericType == typeof(IList<>))
      {
        access = GH_ParamAccess.list;
        parameterType = parameterType.GetGenericArguments()[0];
        genericType = parameterType.IsGenericType ? parameterType.GetGenericTypeDefinition() : null;
      }

      return parameterType;
    }

    ElementFilter elementFilter = null;
    protected override ElementFilter ElementFilter => elementFilter;

    protected void RegisterInputParams(GH_InputParamManager manager, MethodInfo methodInfo)
    {
      var elementFilterClasses = new List<Type>();

      foreach (var parameter in methodInfo.GetParameters())
      {
        if (parameter.Position < 2)
          continue;

        if (parameter.IsOut || parameter.ParameterType.IsByRef)
          throw new NotImplementedException();

        var parameterType = GetParameterType(parameter, out var access, out var optional);
        var nickname = parameter.Name.First().ToString().ToUpperInvariant();
        var name = nickname + parameter.Name.Substring(1);

        foreach (var nickNameAttribte in parameter.GetCustomAttributes(typeof(NickNameAttribute), false).Cast<NickNameAttribute>())
          nickname = nickNameAttribte.NickName;

        var description = string.Empty;
        foreach (var descriptionAttribute in parameter.GetCustomAttributes(typeof(DescriptionAttribute), false).Cast<DescriptionAttribute>())
          description = (description.Length > 0) ? $"{description}\r\n{descriptionAttribute.Description}" : descriptionAttribute.Description;

        var param = manager[manager.AddParameter(CreateParam(parameterType), name, nickname, description, access)];

        param.Optional = optional;

        if (parameterType.IsEnum && param is Param_Integer integerParam)
        {
          foreach (var e in Enum.GetValues(parameterType))
            integerParam.AddNamedValue(Enum.GetName(parameterType, e), (int) e);
        }
        else if (parameterType == typeof(Autodesk.Revit.DB.Element) || parameterType.IsSubclassOf(typeof(Autodesk.Revit.DB.Element)))
        {
          elementFilterClasses.Add(parameterType);
        }
        else if (parameterType == typeof(Autodesk.Revit.DB.Category))
        {
          elementFilterClasses.Add(typeof(Autodesk.Revit.DB.Element));
        }
      }

      if (elementFilterClasses.Count > 0 && !elementFilterClasses.Contains(typeof(Autodesk.Revit.DB.Element)))
      {
        elementFilter = (elementFilterClasses.Count == 1) ?
         (ElementFilter) new Autodesk.Revit.DB.ElementClassFilter(elementFilterClasses[0]) :
         (ElementFilter) new Autodesk.Revit.DB.LogicalOrFilter(elementFilterClasses.Select(x => new Autodesk.Revit.DB.ElementClassFilter(x)).ToArray());
      }
    }

    bool GetInputOptionalData<T>(IGH_DataAccess DA, int index, out Optional<T> optional)
    {
      if (GetInputData(DA, index, out T value))
      {
        optional = new Optional<T>(value);
        return true;
      }

      optional = Optional.Nothig;
      return false;
    }
    static readonly MethodInfo GetInputOptionalDataInfo = typeof(TransactionalComponent).GetMethod("GetInputOptionalData", BindingFlags.Instance | BindingFlags.NonPublic);

    protected bool GetInputData<T>(IGH_DataAccess DA, int index, out T value)
    {
      if (typeof(T).IsEnum)
      {
        int enumValue = 0;
        if (!DA.GetData(index, ref enumValue))
        {
          var param = Params.Input[index];

          if (param.Optional && param.SourceCount == 0)
          {
            value = default(T);
            return false;
          }

          throw new ArgumentNullException(param.Name);
        }

        if (!typeof(T).IsEnumDefined(enumValue))
        {
          var param = Params.Input[index];
          throw new InvalidEnumArgumentException(param.Name, enumValue, typeof(T));
        }

        value = (T) Enum.ToObject(typeof(T), enumValue);
      }
      else if (typeof(T).IsGenericType && (typeof(T).GetGenericTypeDefinition() == typeof(Optional<>)))
      {
        var args = new object[] { DA, index, null };

        try { return (bool) GetInputOptionalDataInfo.MakeGenericMethod(typeof(T).GetGenericArguments()[0]).Invoke(this, args); }
        catch (TargetInvocationException e) { throw e.InnerException; }
        finally { value = args[2] != null ? (T) args[2] : default(T); }
      }
      else
      {
        value = default(T);
        if (!DA.GetData(index, ref value))
        {
          var param = Params.Input[index];
          if (param.Optional && param.SourceCount == 0)
            return false;

          throw new ArgumentNullException(param.Name);
        }
      }

      return true;
    }
    protected static readonly MethodInfo GetInputDataInfo = typeof(TransactionalComponent).GetMethod("GetInputData", BindingFlags.Instance | BindingFlags.NonPublic);

    protected bool GetInputDataList<T>(IGH_DataAccess DA, int index, out IList<T> value)
    {
      var list = new List<T>();
      if (DA.GetDataList(index, list))
      {
        value = list;
        return true;
      }
      else
      {
        value = default(IList<T>);
        return false;
      }
    }
    protected static readonly MethodInfo GetInputDataListInfo = typeof(TransactionalComponent).GetMethod("GetInputDataList", BindingFlags.Instance | BindingFlags.NonPublic);

    protected void ThrowArgumentNullException(string paramName, string description = null) => throw new ArgumentNullException(paramName.FirstCharUpper(), description ?? string.Empty);
    protected void ThrowArgumentException(string paramName, string description = null) => throw new ArgumentException(description ?? "Invalid value.", paramName.FirstCharUpper());
    protected void ThrowIfNotValid(string paramName, Rhino.Geometry.Point3d value)
    {
      if (!value.IsValid) ThrowArgumentException(paramName);
    }
    protected void ThrowIfNotValid(string paramName, Rhino.Geometry.GeometryBase value)
    {
      if (!value.IsValidWithLog(out var log)) ThrowArgumentException(paramName, log);
    }
    #endregion

    #region Autodesk.Revit.DB.Transacion support
    protected enum TransactionStrategy
    {
      PerSolution,
      PerComponent
    }
    protected virtual TransactionStrategy TransactionalStrategy => TransactionStrategy.PerSolution;

    protected Transaction CurrentTransaction;
    protected TransactionStatus TransactionStatus => CurrentTransaction?.GetStatus() ?? TransactionStatus.Uninitialized;

    protected void BeginTransaction(Document document)
    {
      CurrentTransaction = new Transaction(document, Name);
      if (CurrentTransaction.Start() != TransactionStatus.Started)
      {
        CurrentTransaction.Dispose();
        CurrentTransaction = null;
        throw new InvalidOperationException($"Unable to start Transaction '{Name}'");
      }
    }

    protected void CommitTransaction()
    {
      var options = CurrentTransaction.GetFailureHandlingOptions();
#if !DEBUG
      options = options.SetClearAfterRollback(true);
#endif
      options = options.SetDelayedMiniWarnings(true);
      options = options.SetForcedModalHandling(true);
      options = options.SetFailuresPreprocessor(this);
      options = options.SetTransactionFinalizer(this);

      // Disable Rhino UI if any warning-error dialog popup
      {
        ModalForm.EditScope editScope = null;
        EventHandler<DialogBoxShowingEventArgs> _ = null;
        try
        {
          Revit.ApplicationUI.DialogBoxShowing += _ = (sender, args) =>
          {
            if (editScope is null)
              editScope = new ModalForm.EditScope();
          };

          if (TransactionStatus == TransactionStatus.Started)
          {
            OnBeforeCommit(Revit.ActiveDBDocument, CurrentTransaction.GetName());

            CurrentTransaction.Commit(options);
          }
          else CurrentTransaction.RollBack(options);
        }
        finally
        {
          Revit.ApplicationUI.DialogBoxShowing -= _;

          if (editScope is IDisposable disposable)
            disposable.Dispose();
        }
      }
    }

    // Step 1.
    protected override void BeforeSolveInstance()
    {
      if (TransactionalStrategy != TransactionStrategy.PerComponent)
        return;

      BeginTransaction(Revit.ActiveDBDocument);

      OnAfterStart(Revit.ActiveDBDocument, CurrentTransaction.GetName());
    }

    // Step 2.
    protected virtual void OnAfterStart(Document document, string strTransactionName) { }

    // Step 3.
    //protected override void SolveInstance(IGH_DataAccess DA) { }

    // Step 4.
    protected virtual void OnBeforeCommit(Document document, string strTransactionName) { }

    void AddRuntimeMessage(FailureMessageAccessor error, bool? solved = null)
    {
      var level = GH_RuntimeMessageLevel.Remark;
      switch (error.GetSeverity())
      {
        case FailureSeverity.Warning: level = GH_RuntimeMessageLevel.Warning; break;
        case FailureSeverity.Error: level = GH_RuntimeMessageLevel.Error; break;
      }

      string solvedMark = string.Empty;
      if (error.GetSeverity() > FailureSeverity.Warning)
      {
        switch (solved)
        {
          case false: solvedMark = "❌ "; break;
          case true: solvedMark = "✔ "; break;
        }
      }

      var description = error.GetDescriptionText();
      var text = string.IsNullOrEmpty(description) ?
        $"{solvedMark}{level} {{{error.GetFailureDefinitionId().Guid}}}" :
        $"{solvedMark}{description}";

      int idsCount = 0;
      foreach (var id in error.GetFailingElementIds())
        text += idsCount++ == 0 ? $" {{{id.IntegerValue}" : $", {id.IntegerValue}";
      if (idsCount > 0) text += "} ";

      AddRuntimeMessage(level, text);
    }

    // Override to add handled failures to your component (Order is important).
    protected virtual IEnumerable<FailureDefinitionId> FailureDefinitionIdsToFix => null;

    FailureProcessingResult FixFailures(FailuresAccessor failuresAccessor, IEnumerable<FailureDefinitionId> failureIds)
    {
      foreach (var failureId in failureIds)
      {
        int solvedErrors = 0;

        foreach (var error in failuresAccessor.GetFailureMessages().Where(x => x.GetFailureDefinitionId() == failureId))
        {
          if (!failuresAccessor.IsFailureResolutionPermitted(error))
            continue;

          // Don't try to fix two times same issue
          if (failuresAccessor.GetAttemptedResolutionTypes(error).Any())
            continue;

          AddRuntimeMessage(error, true);

          failuresAccessor.ResolveFailure(error);
          solvedErrors++;
        }

        if (solvedErrors > 0)
          return FailureProcessingResult.ProceedWithCommit;
      }

      return FailureProcessingResult.Continue;
    }

    // Step 4.
    FailureProcessingResult IFailuresPreprocessor.PreprocessFailures(FailuresAccessor failuresAccessor)
    {
      if (!failuresAccessor.IsTransactionBeingCommitted())
        return FailureProcessingResult.Continue;

      if (failuresAccessor.GetSeverity() >= FailureSeverity.DocumentCorruption)
        return FailureProcessingResult.ProceedWithRollBack;

      if (failuresAccessor.GetSeverity() >= FailureSeverity.Error)
      {
        // Handled failures in order
        {
          var failureDefinitionIdsToFix = FailureDefinitionIdsToFix;
          if (failureDefinitionIdsToFix != null)
          {
            var result = FixFailures(failuresAccessor, failureDefinitionIdsToFix);
            if (result != FailureProcessingResult.Continue)
              return result;
          }
        }

        // Unhandled failures in incomming order
        {
          var failureDefinitionIdsToFix = failuresAccessor.GetFailureMessages().GroupBy(x => x.GetFailureDefinitionId()).Select(x => x.Key);
          var result = FixFailures(failuresAccessor, failureDefinitionIdsToFix);
          if (result != FailureProcessingResult.Continue)
            return result;
        }
      }

      if (failuresAccessor.GetSeverity() >= FailureSeverity.Warning)
      {
        // Unsolved failures or warnings
        foreach (var error in failuresAccessor.GetFailureMessages().OrderBy(error => error.GetSeverity()))
          AddRuntimeMessage(error, false);

        failuresAccessor.DeleteAllWarnings();
      }

      return FailureProcessingResult.Continue;
    }

    // Step 6.
    protected override void AfterSolveInstance()
    {
      if (TransactionalStrategy != TransactionStrategy.PerComponent)
        return;

      try
      {
        if (RunCount <= 0)
          return;

        if (TransactionStatus == TransactionStatus.Uninitialized)
          return;

        if (Phase != GH_SolutionPhase.Failed)
        {
          CommitTransaction();
        }
      }
      finally
      {
        switch (TransactionStatus)
        {
          case TransactionStatus.Uninitialized:
          case TransactionStatus.Started:
          case TransactionStatus.Committed:
            break;
          default:
            AddRuntimeMessage(GH_RuntimeMessageLevel.Error, $"Transaction {TransactionStatus} and aborted.");
            break;
        }

        CurrentTransaction?.Dispose();
        CurrentTransaction = null;
      }
    }

    // Step 6.A
    public virtual void OnCommitted(Document document, string strTransactionName)
    {
    }

    // Step 6.B
    public virtual void OnRolledBack(Document document, string strTransactionName)
    {
      Params.Output[0].Phase = GH_SolutionPhase.Failed;
    }
    #endregion
  }

  public abstract class ReconstructElementComponent : TransactionalComponent
  {
    protected IGH_Goo[] PreviousStructure;
    System.Collections.IEnumerator PreviousStructureEnumerator;

    protected ReconstructElementComponent(string name, string nickname, string description, string category, string subCategory)
    : base(name, nickname, description, category, subCategory) { }

    protected override sealed void RegisterInputParams(GH_InputParamManager manager)
    {
      var type = GetType();
      var SolveInstanceInfo = type.GetMethod($"Reconstruct{type.Name}", BindingFlags.Instance | BindingFlags.NonPublic);
      RegisterInputParams(manager, SolveInstanceInfo);
    }

    // Step 2.
    protected override void OnAfterStart(Document document, string strTransactionName)
    {
      PreviousStructureEnumerator = PreviousStructure?.GetEnumerator();
    }

    // Step 3.
    protected override sealed void SolveInstance(IGH_DataAccess DA)
    {
      var ActiveDBDocument = Revit.ActiveDBDocument;

      Iterate(DA, ActiveDBDocument, (doc, element) =>
      {
        SolveInstance(DA, doc, ref element);

        if (element != null) element.Pinned = true;
        DA.SetData(0, element);
      });
    }

    void Iterate(IGH_DataAccess DA, Document doc, Action<Document, Element> action)
    {
      var element = PreviousStructureEnumerator?.MoveNext() ?? false ?
                    doc.GetElement(PreviousStructureEnumerator.Current as Types.Element ?? ElementId.InvalidElementId) :
                    null;

      if (element?.Pinned ?? true)
      {
        try
        {
          action(doc, element);
        }
        catch (System.ComponentModel.WarningException e)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, e.Message.Replace("\r\n", " "));
          element?.Document.Delete(element.Id);
          element = null;
        }
        catch (System.ArgumentNullException)
        {
          // Grasshopper components use to send a Null when they receive a Null without throwing any error
          element?.Document.Delete(element.Id);
          element = null;
        }
        catch (System.ArgumentException e)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message.Replace("\r\n", " "));
          element?.Document.Delete(element.Id);
          element = null;
        }
        catch (Autodesk.Revit.Exceptions.ArgumentException e)
        {
          var message = e.Message.Split("\r\n".ToCharArray()).First().Replace("Application.ShortCurveTolerance", "Revit.ShortCurveTolerance");
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, message);
          element?.Document.Delete(element.Id);
          element = null;
        }
        catch (System.Exception e)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
          DA.AbortComponentSolution();
        }
      }
      else DA.SetData(0, element);
    }

    void SolveInstance
    (
      IGH_DataAccess DA,
      Autodesk.Revit.DB.Document doc,
      ref Autodesk.Revit.DB.Element element
    )
    {
      var type = GetType();
      var SolveInstanceInfo = type.GetMethod($"Reconstruct{type.Name}", BindingFlags.Instance | BindingFlags.NonPublic);
      var parameters = SolveInstanceInfo.GetParameters();

      var arguments = new object[parameters.Length];
      try
      {
        arguments[0] = doc;
        arguments[1] = element;

        var args = new object[] { DA, null, null };
        foreach (var parameter in parameters)
        {
          var paramIndex = parameter.Position - 2;

          if (paramIndex < 0)
            continue;

          args[1] = paramIndex;

          try
          {
            switch (Params.Input[paramIndex].Access)
            {
              case GH_ParamAccess.item: GetInputDataInfo.MakeGenericMethod(parameter.ParameterType).Invoke(this, args); break;
              case GH_ParamAccess.list: GetInputDataListInfo.MakeGenericMethod(parameter.ParameterType.GetGenericArguments()[0]).Invoke(this, args); break;
              default: throw new NotImplementedException();
            }
          }
          catch (TargetInvocationException e) { throw e.InnerException; }
          finally { arguments[parameter.Position] = args[2]; args[2] = null; }
        }

        SolveInstanceInfo.Invoke(this, arguments);
      }
      catch (TargetInvocationException e) { throw e.InnerException; }
      finally { element = (Autodesk.Revit.DB.Element) arguments[1]; }
    }

    // Step 4.
    protected override void OnBeforeCommit(Document document, string strTransactionName)
    {
      // Remove extra unused elements
      while (PreviousStructureEnumerator?.MoveNext() ?? false)
      {
        if (PreviousStructureEnumerator.Current is Types.Element elementId)
        {
          if (document.GetElement(elementId) is Element element)
          {
            try { document.Delete(element.Id); }
            catch (Autodesk.Revit.Exceptions.ApplicationException) { }
          }
        }
      }
    }

    // Step 6.
    protected override void AfterSolveInstance()
    {
      try { base.AfterSolveInstance(); }
      finally { PreviousStructureEnumerator = null; }
    }

    // Step 6.A
    public override void OnCommitted(Document document, string strTransactionName)
    {
      // Update previous elements
      PreviousStructure = Params.Output[0].VolatileData.AllData(false).ToArray();
    }
  }
}
