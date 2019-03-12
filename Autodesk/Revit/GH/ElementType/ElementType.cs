using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;
using Grasshopper.GUI.Canvas;
using Grasshopper.GUI;
using Grasshopper.Kernel.Types;
using Grasshopper.Kernel.Data;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Types
{
  public class ElementType : Element
  {
    public override string TypeName => "Revit ElementType";
    public override string TypeDescription => "Represents a Revit element type";
    protected override Type ScriptVariableType => typeof(Autodesk.Revit.DB.ElementType);
    public static explicit operator Autodesk.Revit.DB.ElementType(ElementType self)
    {
      return Revit.ActiveDBDocument?.GetElement(self) as Autodesk.Revit.DB.ElementType;
    }

    public ElementType() { }
    public ElementType(Autodesk.Revit.DB.ElementType elementType) : base(elementType) { }
  }
}

namespace RhinoInside.Revit.GH.Parameters
{
  public class ElementType : GH_Param<Types.ElementType>
  {
    public override GH_Exposure Exposure => GH_Exposure.secondary;
    public override Guid ComponentGuid => new Guid("97DD546D-65C3-4D00-A609-3F5FBDA67142");
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("TYPE");

    public ElementType() : base("ElementType", "ElementType", "Represents a Revit document element type.", "Revit", "Element", GH_ParamAccess.item) { }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class ElementTypeByName : GH_ValueList, IGH_InitCodeAware
  {
    public override Guid ComponentGuid => new Guid("D3FB53D3-9118-4F11-A32D-AECB30AA418D");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("T*");
    public override GH_ParamData DataType => GH_ParamData.remote;
    public override GH_ParamKind Kind => GH_ParamKind.floating;

    void IGH_InitCodeAware.SetInitCode(string code) => NickName = code;

    public ElementTypeByName()
    {
      ObjectChanged += OnObjectChanged;

      Category = "Revit";
      SubCategory = "Input";
      Name = "ElementType.ByName";
      Description = "Provide an Element type picker";

      ListMode = GH_ValueListMode.DropDown;
      ListItems.Clear();
    }

    public override void AddedToDocument(GH_Document document)
    {
      if(NickName == Name)
        NickName = "'ElementType name here…";

      base.AddedToDocument(document);
    }

    private void OnObjectChanged(IGH_DocumentObject sender, GH_ObjectChangedEventArgs e)
    {
      if (SourceCount == 0)
      {
        if (e.Type == GH_ObjectEventType.Sources)
        {
          //NickName = string.Empty;
          MutableNickName = true;
        }

        if (e.Type == GH_ObjectEventType.NickName)
          ExpireSolution(true);
      }
      else
      {
        if (e.Type == GH_ObjectEventType.Sources)
        {
          NickName = string.Empty;
          MutableNickName = false;
        }
      }
    }

    class ValueListAttributes : GH_ValueListAttributes
    {
      public override bool HasInputGrip => true;
      public override bool AllowMessageBalloon => true;
      public ValueListAttributes(GH_ValueList owner) : base(owner) { }
      protected override void Render(GH_Canvas canvas, Graphics graphics, GH_CanvasChannel channel)
      {
        if (channel == GH_CanvasChannel.Wires)
        {
          if (Owner.SourceCount > 0)
            RenderIncomingWires(canvas.Painter, Owner.Sources, Owner.WireDisplay);
        }

        base.Render(canvas, graphics, channel);
      }
      public override GH_ObjectResponse RespondToMouseDoubleClick(GH_Canvas sender, GH_CanvasMouseEvent e)
      {
        if (Owner.MutableNickName && e.Button == MouseButtons.Left)
        {
          var objectMenu = new ContextMenuStrip();

          Owner.AppendMenuItems(objectMenu);
          if (objectMenu.Items.Count > 0)
          {
            sender.ActiveInteraction = null;
            objectMenu.Show(sender, e.ControlLocation);
          }

          return GH_ObjectResponse.Handled;
        }

        return GH_ObjectResponse.Ignore;
      }
    }

    void RefreshList(string FamilyName)
    {
      var selectedItems = new List<string>();
      {
        foreach (var item in ListItems)
          if (item.Selected)
            selectedItems.Add(item.Expression);
      }

      ListItems.Clear();
      if (FamilyName.Length == 0 || FamilyName[0] == '\'')
        return;

      if (Revit.ActiveDBDocument != null)
      {
        int selectedItemsCount = 0;
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          foreach (var elementType in collector.WhereElementIsElementType().Cast<ElementType>())
          {
            if (!elementType.FamilyName.IsSymbolNameLike(FamilyName))
              continue;

            if (SourceCount == 0)
            {
              // If is a no pattern match update NickName case
              if (string.Equals(elementType.FamilyName, FamilyName, StringComparison.OrdinalIgnoreCase))
                FamilyName = elementType.FamilyName;
            }

            var item = new GH_ValueListItem(elementType.FamilyName + " : " + elementType.Name, elementType.Id.IntegerValue.ToString());
            item.Selected = selectedItems.Contains(item.Expression);
            ListItems.Add(item);

            selectedItemsCount += item.Selected ? 1 : 0;
          }
        }

        // If no selection and we are not in CheckList mode try to select default model types
        if (ListItems.Count == 0)
        {
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("No ElementType found using pattern \"{0}\"", FamilyName));
        }
        else if (selectedItemsCount == 0 && ListMode != GH_ValueListMode.CheckList)
        {
          var defaultElementTypeIds = new HashSet<string>();
          foreach (var typeGroup in Enum.GetValues(typeof(ElementTypeGroup)).Cast<ElementTypeGroup>())
          {
            var elementTypeId = Revit.ActiveDBDocument.GetDefaultElementTypeId(typeGroup);
            if (elementTypeId != ElementId.InvalidElementId)
              defaultElementTypeIds.Add(elementTypeId.IntegerValue.ToString());
          }

          foreach (var item in ListItems)
            item.Selected = defaultElementTypeIds.Contains(item.Expression);
        }
      }
    }

    void RefreshList(IEnumerable<IGH_Goo> goos)
    {
      var selectedItems = new List<string>();
      {
        foreach (var item in ListItems)
          if (item.Selected)
            selectedItems.Add(item.Expression);
      }

      ListItems.Clear();

      if (Revit.ActiveDBDocument != null)
      {
        int selectedItemsCount = 0;
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          HashSet<string> familiesSet = null;
          foreach (var goo in goos)
          {
            var e = new Types.Element();
            if (e.CastFrom(goo))
            {
              switch ((Element) e)
              {
                case Family family:
                  foreach (var elementType in collector.WhereElementIsElementType().Cast<ElementType>())
                  {
                    if (elementType.FamilyName != family.Name)
                      continue;

                    var item = new GH_ValueListItem(elementType.FamilyName + " : " + elementType.Name, elementType.Id.IntegerValue.ToString());
                    item.Selected = selectedItems.Contains(item.Expression);
                    ListItems.Add(item);

                    selectedItemsCount += item.Selected ? 1 : 0;
                  }
                  break;
                case ElementType elementType:
                {
                  var item = new GH_ValueListItem(elementType.FamilyName + " : " + elementType.Name, elementType.Id.IntegerValue.ToString());
                  item.Selected = selectedItems.Contains(item.Expression);
                  ListItems.Add(item);

                  selectedItemsCount += item.Selected ? 1 : 0;
                }
                break;
                case Element element:
                {
                  var type = Revit.ActiveDBDocument.GetElement(element.GetTypeId()) as ElementType;
                  var item = new GH_ValueListItem(type.FamilyName + " : " + type.Name, type.Id.IntegerValue.ToString());
                  item.Selected = selectedItems.Contains(item.Expression);
                  ListItems.Add(item);

                  selectedItemsCount += item.Selected ? 1 : 0;
                }
                break;
              }
            }
            else
            {
              var c = new Types.Category();
              if (c.CastFrom(goo))
              {
                var category = (Category) c;

                if (familiesSet == null) using (var familyCollector = new FilteredElementCollector(Revit.ActiveDBDocument))
                  {
                    familiesSet = new HashSet<string>
                    (
                    familyCollector.OfClass(typeof(Family)).
                    Cast<Family>().
                    Where((x) => x.FamilyCategory.Id == category.Id).
                    Select((x) => x.Name)
                    );
                  }

                foreach (var elementType in collector.WhereElementIsElementType().Cast<ElementType>())
                {
                  if (elementType.Category?.Id != category.Id && !familiesSet.Contains(elementType.FamilyName))
                    continue;

                  var item = new GH_ValueListItem(elementType.FamilyName + " : " + elementType.Name, elementType.Id.IntegerValue.ToString());
                  item.Selected = selectedItems.Contains(item.Expression);
                  ListItems.Add(item);

                  selectedItemsCount += item.Selected ? 1 : 0;
                }
              }
              else
              {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, "Unable to convert some input data.");
              }
            }
          }
        }

        // If no selection and we are not in CheckList mode try to select default model types
        if (ListItems.Count > 0 && selectedItemsCount == 0 && ListMode != GH_ValueListMode.CheckList)
        {
          var defaultElementTypeIds = new HashSet<string>();
          foreach (var typeGroup in Enum.GetValues(typeof(ElementTypeGroup)).Cast<ElementTypeGroup>())
          {
            var elementTypeId = Revit.ActiveDBDocument.GetDefaultElementTypeId(typeGroup);
            if (elementTypeId != ElementId.InvalidElementId)
              defaultElementTypeIds.Add(elementTypeId.IntegerValue.ToString());
          }

          foreach (var item in ListItems)
            item.Selected = defaultElementTypeIds.Contains(item.Expression);
        }
      }
    }

    public override void CreateAttributes()
    {
      m_attributes = new ValueListAttributes(this);
    }

    public override void PostProcessData()
    {
      base.PostProcessData();

      if(SourceCount == 0)
        RefreshList(NickName);
      else
        RefreshList(VolatileData.AllData(true));

      // Show elements sorted
      ListItems.Sort((x, y) => string.CompareOrdinal(x.Name, y.Name));

      //base.CollectVolatileData_Custom();
      m_data.Clear();

      var path = new GH_Path(0);
      if(SelectedItems.Count == 0)
        m_data.AppendRange(new IGH_Goo[0], path);
      else foreach (var item in SelectedItems)
        m_data.Append(item.Value, path);
    }

    protected override void CollectVolatileData_FromSources()
    {
      base.CollectVolatileData_FromSources();

      NickName = string.Empty;
    }

    protected override void CollectVolatileData_Custom()
    {
      NickName = NickName.Trim();
    }
  }
}
