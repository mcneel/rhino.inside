using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;
using Autodesk.Revit.UI;
using GH_IO.Serialization;
using Grasshopper.GUI;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Data;
using Grasshopper.Kernel.Types;
using DB = Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public interface IGH_ElementId : IGH_Goo
  {
    DB.Document Document { get; }
    DB.ElementId Id { get; }

    Guid DocumentGUID { get; }
    string UniqueID { get; }

    bool IsReferencedElement { get; }
    bool IsElementLoaded { get; }
    bool LoadElement();
    void UnloadElement();
  }

  public class ID : GH_Goo<DB.ElementId>, IEquatable<ID>, IGH_ElementId
  {
    public override string TypeName => "Revit Model Object";
    public override string TypeDescription => "Represents a Revit model object";
    public override bool IsValid => (!(Value is null || Value == DB.ElementId.InvalidElementId)) && (Document?.IsValidObject ?? false);
    public override sealed IGH_Goo Duplicate() => (IGH_Goo) MemberwiseClone();
    protected virtual Type ScriptVariableType => typeof(DB.ElementId);
    public static implicit operator DB.ElementId(ID self) { return self.Value; }

    public static ID FromElementId(DB.Document doc, DB.ElementId id)
    {
      if (id == DB.ElementId.InvalidElementId)
        return null;

      if (Category.FromElementId(doc, id) is Category c)
        return c;

      if (ParameterKey.FromElementId(doc, id) is ParameterKey p)
        return p;

      return Element.FromElementId(doc, id);
    }

    public void SetValue(DB.Document doc, DB.ElementId id)
    {
      Document = doc;
      DocumentGUID = doc.GetFingerprintGUID();

      Value = id;
      UniqueID = doc?.GetElement(id)?.UniqueId ??
                 (
                   id.IntegerValue < DB.ElementId.InvalidElementId.IntegerValue ?
                     UniqueId.Format(Guid.Empty, id.IntegerValue) : 
                     string.Empty
                 );
    }

    #region IGH_ElementId
    DB.Document document;
    public DB.Document Document { get => document?.IsValidObject != true ? null : document; protected set { document = value; } }
    public DB.ElementId Id => Value;
    public Guid DocumentGUID { get; protected set; } = Guid.Empty;
    public string UniqueID   { get; protected set; } = string.Empty;
    public bool IsReferencedElement => !string.IsNullOrEmpty(UniqueID);
    public bool IsElementLoaded => m_value is object;
    public virtual bool LoadElement()
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
    public void UnloadElement() { m_value = null; Document = null; }
    #endregion

    public ID() { Value = DB.ElementId.InvalidElementId; }
    protected ID(DB.Document doc, DB.ElementId id)    => SetValue(doc, id);

    public override bool CastFrom(object source)
    {
      if (source is GH_Integer integer)
      {
        Value = new DB.ElementId(integer.Value);
        UniqueID = string.Empty;
        return true;
      }
      if (source is DB.ElementId id)
      {
        Value = id;
        UniqueID = string.Empty;
        return true;
      }

      return false;
    }

    public override bool CastTo<Q>(ref Q target)
    {
      if(target is IGH_ElementId)
      {
        target = (Q) (object) null;
        return true;
      }

      if (typeof(Q).IsAssignableFrom(typeof(DB.ElementId)))
      {
        target = (Q) (object) Value;
        return true;
      }
      if(typeof(Q).IsAssignableFrom(typeof(GH_Integer)))
      {
        target = (Q) (object) new GH_Integer(Value.IntegerValue);
        return true;
      }
      if(typeof(Q).IsAssignableFrom(typeof(GH_String)))
      {
        target = (Q) (object) new GH_String(UniqueID);
        return true;
      }

      return base.CastTo<Q>(ref target);
    }

    public bool Equals(ID id) => id?.UniqueID == UniqueID;
    public override bool Equals(object obj) => (obj is ID id) ? Equals(id) : base.Equals(obj);
    public override int GetHashCode() => UniqueID.GetHashCode();

    [TypeConverter(typeof(Proxy.ObjectConverter))]
    protected class Proxy : IGH_GooProxy
    {
      protected readonly ID owner;
      public Proxy(ID o) { owner = o; if(this is IGH_GooProxy proxy) proxy.UserString = proxy.FormatInstance(); }

      IGH_Goo IGH_GooProxy.ProxyOwner => owner;
      string IGH_GooProxy.UserString { get; set; }
      bool IGH_GooProxy.IsParsable => IsParsable();

      public virtual bool IsParsable() => false;
      public virtual void Construct() { }
      public virtual string FormatInstance() => owner.Identity;
      public virtual bool FromString(string str) => throw new NotImplementedException();
      public virtual string MutateString(string str) => str.Trim();

      public bool Valid => owner.IsValid;
      public string TypeName => owner.TypeName;
      public string TypeDescription => owner.TypeDescription;

      [System.ComponentModel.Description("The document this element belongs to.")]
      public string Document => owner.Document.GetFilePath();
      [System.ComponentModel.Description("The Guid of document this element belongs to.")]
      public Guid DocumentGUID => owner.Document.GetFingerprintGUID();
      [System.ComponentModel.Description("The element identifier in this session.")]
      public int Id => owner.Id?.IntegerValue ?? -1;
      [System.ComponentModel.Description("A stable unique identifier for an element within the document.")]
      public string UniqueID => owner.UniqueID;
      [System.ComponentModel.Description("API Object Type.")]
      public virtual Type ObjectType => owner.ScriptVariable()?.GetType() ?? owner.ScriptVariableType;
      [System.ComponentModel.Description("Element is built in Revit.")]
      public bool IsBuiltIn => owner.Id.IsBuiltInId();


      class ObjectConverter : ExpandableObjectConverter
      {
        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
          var properties = base.GetProperties(context, value, attributes);
          if (value is Proxy proxy)
          {
            var element = proxy.owner.Document?.GetElement(proxy.owner.Id);
            if (element is object)
            {
              var parameters = element.GetParameters(RevitAPI.ParameterSet.Any).
                Select(p => new ParameterPropertyDescriptor(p)).
                ToArray();

              var descriptors = new PropertyDescriptor[properties.Count + parameters.Length];
              properties.CopyTo(descriptors, 0);
              parameters.CopyTo(descriptors, properties.Count);

              return new PropertyDescriptorCollection(descriptors, true);
            }
          }

          return properties;
        }
      }

      private class ParameterPropertyDescriptor : PropertyDescriptor
      {
        readonly DB.Parameter parameter;
        public ParameterPropertyDescriptor(DB.Parameter p) : base(p.Definition?.Name ?? p.Id.IntegerValue.ToString(), null) { parameter = p; }
        public override Type ComponentType => typeof(Proxy);
        public override bool IsReadOnly => true;
        public override string Name => parameter.Definition?.Name ?? string.Empty;
        public override string Category => parameter.Definition is null ? string.Empty : DB.LabelUtils.GetLabelFor(parameter.Definition.ParameterGroup);
        public override string Description
        {
          get
          {
            var description = string.Empty;
            if (parameter.Element is object && parameter.Definition is object)
            {
              try { description = parameter.StorageType == DB.StorageType.ElementId ? "ElementId" : DB.LabelUtils.GetLabelFor(parameter.Definition.ParameterType); }
              catch (Autodesk.Revit.Exceptions.InvalidOperationException)
              { description = parameter.Definition.UnitType == DB.UnitType.UT_Number ? "Enumerate" : DB.LabelUtils.GetLabelFor(parameter.Definition.UnitType); }
            }

            if (parameter.IsReadOnly)
              description = "Read only " + description;

            description += "\nParameterId : " + parameter.Id.IntegerValue.ToParameterIdString();
            return description;
          }
        }
        public override bool Equals(object obj)
        {
          if (obj is ParameterPropertyDescriptor other)
            return other.parameter.Id == parameter.Id;

          return false;
        }
        public override int GetHashCode() => parameter.Id.IntegerValue;
        public override bool ShouldSerializeValue(object component) { return false; }
        public override void ResetValue(object component) { }
        public override bool CanResetValue(object component) { return false; }
        public override void SetValue(object component, object value) { }
        public override Type PropertyType => typeof(string);
        public override object GetValue(object component) =>
          parameter.Element is object && parameter.Definition is object ?
          (parameter.StorageType == DB.StorageType.String ? parameter.AsString() :
          parameter.AsValueString()) : null;
      }
    }

    public override IGH_GooProxy EmitProxy() => new Proxy(this);

    public string Identity
    {
      get
      {
        if (Value is null)        return $"{UniqueID}@{DocumentGUID}";
        else if(Document is null) return $"id {Value.IntegerValue}@{DocumentGUID}";
        else if(Revit.ActiveUIApplication.Application.Documents.Size > 1)
                                  return $"id {Value.IntegerValue}@{Document.Title}";
        else                      return $"id {Value.IntegerValue}";
      }
    }

    public override string ToString()
    {
      if (!IsValid)
      {
        if(IsReferencedElement && IsElementLoaded)
          return $"Unresolved {TypeName} : {UniqueID}@{DocumentGUID}";

        return $"Null {TypeName}";
      }

      return $"{TypeName} : {Identity}";
    }

    public override sealed bool Read(GH_IReader reader)
    {
      Value = null;
      Document = null;

      var documentGUID = Guid.Empty;
      reader.TryGetGuid("DocumentGUID", ref documentGUID);
      DocumentGUID = documentGUID;

      string uniqueID = string.Empty;
      reader.TryGetString("UniqueID", ref uniqueID);
      UniqueID = uniqueID;

      return true;
    }

    public override sealed bool Write(GH_IWriter writer)
    {
      if(DocumentGUID != Guid.Empty)
        writer.SetGuid("DocumentGUID", DocumentGUID);

      if(!string.IsNullOrEmpty(UniqueID))
        writer.SetString("UniqueID", UniqueID);

      return true;
    }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public abstract class GH_PersistentParam<T> : Grasshopper.Kernel.GH_PersistentParam<T>
    where T : class, IGH_Goo
  {
    protected override sealed Bitmap Icon => ((Bitmap) Properties.Resources.ResourceManager.GetObject(typeof(T).Name)) ??
                                             ImageBuilder.BuildIcon(IconTag);

    protected virtual string IconTag => typeof(T).Name.Substring(0, 1);

    protected GH_PersistentParam(string name, string nickname, string description, string category, string subcategory) :
      base(name, nickname, description, category, subcategory)
    { }
  }

  public interface IGH_ElementIdParam : IGH_Param
  {
    bool NeedsToBeExpired
    (
      DB.Document doc,
      ICollection<DB.ElementId> added,
      ICollection<DB.ElementId> deleted,
      ICollection<DB.ElementId> modified
    );
  }

  public abstract class ElementIdParam<T, R> : GH_PersistentParam<T>, IGH_ElementIdParam
    where T : class, Types.IGH_ElementId
  {
    public override sealed string TypeName => "Revit " + Name;
    protected ElementIdParam(string name, string nickname, string description, string category, string subcategory) :
      base(name, nickname, description, category, subcategory)
    { }

    internal static IEnumerable<Types.IGH_ElementId> ToElementIds(IGH_Structure data) =>
      data.AllData(true).
      OfType<Types.IGH_ElementId>().
      Where(x => x.IsValid);

    public override void ClearData()
    {
      base.ClearData();

      if (PersistentDataCount == 0)
        return;

      foreach (var goo in PersistentData.OfType<T>())
        goo?.UnloadElement();
    }

    protected override void OnVolatileDataCollected()
    {
      if (SourceCount == 0)
      {
        foreach (var branch in m_data.Branches)
        {
          for (int i = 0; i < branch.Count; i++)
          {
            var item = branch[i];
            if (item?.IsReferencedElement ?? false)
            {
              if (!item.LoadElement())
              {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, $"A referenced {item.TypeName} could not be found in the Revit document.");
                branch[i] = null;
              }
            }
          }
        }
      }

      base.OnVolatileDataCollected();
    }

    protected override T PreferredCast(object data) => data is R ? (T) Activator.CreateInstance(typeof(T), data) : null;

    #region UI
    protected override void PrepareForPrompt() { }
    protected override void RecoverFromPrompt() { }
    public virtual void AppendAdditionalElementMenuItems(ToolStripDropDown menu) { }
    public override void AppendAdditionalMenuItems(ToolStripDropDown menu)
    {
      base.AppendAdditionalMenuItems(menu);
      Menu_AppendSeparator(menu);
      AppendAdditionalElementMenuItems(menu);

      var doc = Revit.ActiveUIDocument.Document;

      if (Kind == GH_ParamKind.output && Attributes.GetTopLevel.DocObject is Components.ReconstructElementComponent)
      {
        var pinned = ToElementIds(VolatileData).
                     Where(x => x.Document.Equals(doc)).
                     Select(x => x.Document.GetElement(x.Id)).
                     Where(x => x.Pinned).Any();

        if (pinned)
          Menu_AppendItem(menu, $"Unpin {GH_Convert.ToPlural(TypeName)}", Menu_UnpinElements, DataType != GH_ParamData.remote, false);

        var unpinned = ToElementIds(VolatileData).
                     Where(x => x.Document.Equals(doc)).
                     Select(x => x.Document.GetElement(x.Id)).
                     Where(x => x.Pinned == false).Any();

        if (unpinned)
          Menu_AppendItem(menu, $"Pin {GH_Convert.ToPlural(TypeName)}", Menu_PinElements, DataType != GH_ParamData.remote, false);
      }

      bool delete = ToElementIds(VolatileData).Where(x => x.Document.Equals(doc)).Any();

      Menu_AppendItem(menu, $"Delete {GH_Convert.ToPlural(TypeName)}", Menu_DeleteElements, delete, false);
      this.Menu_AppendConnect(menu, Menu_Connect);
    }

    void Menu_PinElements(object sender, EventArgs args)
    {
      var doc = Revit.ActiveUIDocument.Document;
      var elements = ToElementIds(VolatileData).
                       Where(x => x.Document.Equals(doc)).
                       Select(x => x.Document.GetElement(x.Id)).
                       Where(x => x.Pinned == false);

      if (elements.Any())
      {
        try
        {
          using (var transaction = new DB.Transaction(doc, "Pin elements"))
          {
            transaction.Start();

            foreach (var element in elements)
              element.Pinned = true;

            transaction.Commit();
          }
        }
        catch (Autodesk.Revit.Exceptions.ArgumentException)
        {
          TaskDialog.Show("Pin elements", $"One or more of the {TypeName} cannot be pinned.");
        }
      }
    }

    void Menu_UnpinElements(object sender, EventArgs args)
    {
      var doc = Revit.ActiveUIDocument.Document;
      var elements = ToElementIds(VolatileData).
                       Where(x => x.Document.Equals(doc)).
                       Select(x => x.Document.GetElement(x.Id)).
                       Where(x => x.Pinned == true);

      if (elements.Any())
      {
        try
        {
          using (var transaction = new DB.Transaction(doc, "Unpin elements"))
          {
            transaction.Start();

            foreach (var element in elements)
              element.Pinned = false;

            transaction.Commit();
          }
        }
        catch (Autodesk.Revit.Exceptions.ArgumentException)
        {
          TaskDialog.Show("Unpin elements", $"One or more of the {TypeName} cannot be unpinned.");
        }
      }
    }

    void Menu_DeleteElements(object sender, EventArgs args)
    {
      var doc = Revit.ActiveUIDocument.Document;
      var elementIds = ToElementIds(VolatileData).
                       Where(x => x.Document.Equals(doc)).
                       Select(x => x.Id);

      if (elementIds.Any())
      {
        using (new ModalForm.EditScope())
        {
          using
          (
            var taskDialog = new TaskDialog(MethodBase.GetCurrentMethod().DeclaringType.FullName)
            {
              MainIcon = TaskDialogIcons.IconWarning,
              TitleAutoPrefix = false,
              Title = "Delete Elements",
              MainInstruction = "Are you sure you want to delete those elements?",
              CommonButtons = TaskDialogCommonButtons.Yes | TaskDialogCommonButtons.No,
              DefaultButton = TaskDialogResult.Yes,
              AllowCancellation = true,
#if REVIT_2020
              EnableMarqueeProgressBar = true
#endif
            }
          )
          {
            taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink1, "Show elements");
            taskDialog.AddCommandLink(TaskDialogCommandLinkId.CommandLink2, "Manage element collection");

            var result = TaskDialogResult.None;
            bool highlight = false;
            do
            {
              var elements = elementIds.ToArray();
              taskDialog.ExpandedContent = $"{elements.Length} elements and its depending elements will be deleted.";

              if (highlight)
                Revit.ActiveUIDocument.Selection.SetElementIds(elements);

              switch (result = taskDialog.Show())
              {
                case TaskDialogResult.CommandLink1:
                  Revit.ActiveUIDocument.ShowElements(elements);
                  highlight = true;
                  break;

                case TaskDialogResult.CommandLink2:
                  using (var dataManager = new GH_PersistentDataEditor())
                  {
                    var elementCollection = new GH_Structure<IGH_Goo>();
                    elementCollection.AppendRange(elementIds.Select(x => Types.Element.FromElementId(doc, x)));
                    dataManager.SetData(elementCollection, new Types.Element());

                    GH_WindowsFormUtil.CenterFormOnCursor(dataManager, true);
                    if (dataManager.ShowDialog(ModalForm.OwnerWindow) == System.Windows.Forms.DialogResult.OK)
                      elementIds = dataManager.GetData<IGH_Goo>().AllData(true).OfType<Types.Element>().Select(x => x.Value);
                  }
                  break;

                case TaskDialogResult.Yes:
                  try
                  {
                    using (var transaction = new DB.Transaction(doc, "Delete elements"))
                    {
                      transaction.Start();
                      doc.Delete(elements);
                      transaction.Commit();
                    }

                    ClearData();
                    ExpireDownStreamObjects();
                    OnPingDocument().NewSolution(false);
                  }
                  catch (Autodesk.Revit.Exceptions.ArgumentException)
                  {
                    TaskDialog.Show("Delete elements", $"One or more of the {TypeName} cannot be deleted.");
                  }
                  break;
              }
            }
            while (result == TaskDialogResult.CommandLink1 || result == TaskDialogResult.CommandLink2);
          }
        }
      }
    }

    void Menu_Connect(object sender, EventArgs e)
    {
      if (sender is ToolStripMenuItem item && item.Tag is Guid componentGuid)
      {
        var obj = this.ConnectNewObject(componentGuid);
        if (obj is null)
          return;

        obj.ExpireSolution(true);
      }
    }

    protected override bool Prompt_ManageCollection(GH_Structure<T> values)
    {
      foreach (var item in values.AllData(true))
      {
        if (item.IsValid)
          continue;

        if (item is Types.IGH_ElementId elementId)
        {
          if (elementId.IsReferencedElement)
            elementId.LoadElement();
        }
      }

      return base.Prompt_ManageCollection(values);
    }
    #endregion

    #region IGH_ElementIdParam
    bool IGH_ElementIdParam.NeedsToBeExpired
    (
      DB.Document doc,
      ICollection<DB.ElementId> added,
      ICollection<DB.ElementId> deleted,
      ICollection<DB.ElementId> modified
    )
    {
      if (DataType == GH_ParamData.remote)
        return false;

      foreach (var data in VolatileData.AllData(true).OfType<Types.IGH_ElementId>())
      {
        if (!data.IsElementLoaded)
          continue;

        if (modified.Contains(data.Id))
          return true;

        if (deleted.Contains(data.Id))
          return true;
      }

      return false;
    }
#endregion
  }

  public abstract class ElementIdNonGeometryParam<T, R> : ElementIdParam<T, R>
    where T : class, Types.IGH_ElementId
  {
    protected ElementIdNonGeometryParam(string name, string nickname, string description, string category, string subcategory) :
      base(name, nickname, description, category, subcategory)
    { }

    protected override void Menu_AppendPromptOne(ToolStripDropDown menu) { }
    protected override void Menu_AppendPromptMore(ToolStripDropDown menu) { }
    protected override GH_GetterResult Prompt_Plural(ref List<T> values) => GH_GetterResult.cancel;
    protected override GH_GetterResult Prompt_Singular(ref T value) => GH_GetterResult.cancel;
  }
}
