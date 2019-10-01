using System;
using System.Collections.Generic;
using System.Linq;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Special;
using Grasshopper.Kernel.Types;

namespace RhinoInside.Revit.GH.Parameters
{
  public class ElementTypeByName : ValueList
  {
    public override Guid ComponentGuid => new Guid("D3FB53D3-9118-4F11-A32D-AECB30AA418D");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public ElementTypeByName()
    {
      Name = "ElementType.ByName";
      Description = "Provides an Element type picker";
    }

    public override void AddedToDocument(GH_Document document)
    {
      if (NickName == Name)
        NickName = "'Family name here…";

      base.AddedToDocument(document);
    }

    protected override void RefreshList(string FamilyName)
    {
      var selectedItems = ListItems.Where(x => x.Selected).Select(x => x.Expression).ToList();
      ListItems.Clear();

      if (FamilyName.Length == 0 || FamilyName[0] == '\'')
        return;

      if (Revit.ActiveDBDocument != null)
      {
        int selectedItemsCount = 0;
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        {
          foreach (var elementType in collector.WhereElementIsElementType().Cast<Autodesk.Revit.DB.ElementType>())
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

    protected override void RefreshList(IEnumerable<IGH_Goo> goos)
    {
      var selectedItems = ListItems.Where(x => x.Selected).Select(x => x.Expression).ToList();
      ListItems.Clear();

      if (Revit.ActiveDBDocument != null)
      {
        int selectedItemsCount = 0;
        using (var collector = new FilteredElementCollector(Revit.ActiveDBDocument))
        using (var elementTypeCollector = collector.WhereElementIsElementType())
        {
          foreach (var goo in goos)
          {
            var e = new Types.Element();
            if (e.CastFrom(goo))
            {
              switch ((Autodesk.Revit.DB.Element) e)
              {
                case Autodesk.Revit.DB.Family family:
                  foreach (var elementType in elementTypeCollector.Cast<Autodesk.Revit.DB.ElementType>())
                  {
                    if (elementType.FamilyName != family.Name)
                      continue;

                    var item = new GH_ValueListItem(elementType.FamilyName + " : " + elementType.Name, elementType.Id.IntegerValue.ToString());
                    item.Selected = selectedItems.Contains(item.Expression);
                    ListItems.Add(item);

                    selectedItemsCount += item.Selected ? 1 : 0;
                  }
                  break;
                case Autodesk.Revit.DB.ElementType elementType:
                {
                  var item = new GH_ValueListItem(elementType.FamilyName + " : " + elementType.Name, elementType.Id.IntegerValue.ToString());
                  item.Selected = selectedItems.Contains(item.Expression);
                  ListItems.Add(item);

                  selectedItemsCount += item.Selected ? 1 : 0;
                }
                break;
                case Autodesk.Revit.DB.Element element:
                {
                  var type = Revit.ActiveDBDocument.GetElement(element.GetTypeId()) as Autodesk.Revit.DB.ElementType;
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
                foreach (var elementType in elementTypeCollector.OfCategoryId(c.Value).Cast<Autodesk.Revit.DB.ElementType>())
                {
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

    protected override string HtmlHelp_Source()
    {
      var nTopic = new Grasshopper.GUI.HTML.GH_HtmlFormatter(this)
      {
        Title = Name,
        Description =
        @"<p>This component is a special interface object that allows for quick picking a Revit ElementType object.</p>" +
        @"<p>Double click on it and use the name input box to enter a family name, alternativelly you can enter a name patter. " +
        @"If a pattern is used, this param list will be filled up with all the element types that match it.</p>" +
        @"<p>Several kind of patterns are supported, the method used depends on the first pattern character:</p>" +
        @"<dl>" +
        @"<dt><b>></b></dt><dd>Starts with</dd>" +
        @"<dt><b><</b></dt><dd>Ends with</dd>" +
        @"<dt><b>?</b></dt><dd>Contains, same as a regular search</dd>" +
        @"<dt><b>:</b></dt><dd>Wildcards, see Microsoft.VisualBasic " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/visual-basic/language-reference/operators/like-operator#pattern-options\">LikeOperator</a></dd>" +
        @"<dt><b>;</b></dt><dd>Regular expresion, see " + "<a target=\"_blank\" href=\"https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference\">here</a> as reference</dd>" +
        @"</dl>",
        ContactURI = @"https://discourse.mcneel.com/c/serengeti/inside"
      };

      nTopic.AddRemark(@"You can also connect a list of categories, families or types at left as an input and this component will be filled up with all types that belong to those objects.");

      return nTopic.HtmlFormat();
    }
  }
}

namespace RhinoInside.Revit.GH.Components
{
  public class ElementTypeIdentity : Component
  {
    public override Guid ComponentGuid => new Guid("7DEA1BA3-D9BC-4E94-9E1C-0E527187C9DC");
    protected override string IconTag => "ID";

    public ElementTypeIdentity()
    : base("ElementType.Identity", "ElementType.Identity", "Query type identity information", "Revit", "Type")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "Type", "T", "ElementType to query for its identity", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Category(), "Category", "C", "Category in which the ElementType resides", GH_ParamAccess.item);
      manager.AddTextParameter("FamilyName", "F", "The family name of the ElementType", GH_ParamAccess.item);
      manager.AddTextParameter("Name", "N", "A human readable name for the ElementType", GH_ParamAccess.item);
      manager.AddTextParameter("UniqueID", "UUID", "A stable unique identifier for the ElementType within the document", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.ElementType elementType = null;
      if (!DA.GetData("Type", ref elementType))
        return;

      DA.SetData("Category", elementType?.Category);
      DA.SetData("FamilyName", elementType?.FamilyName);
      DA.SetData("Name", elementType?.Name);
      DA.SetData("UniqueID", elementType?.UniqueId);
    }
  }

  public class ElementTypeSimilar : Component
  {
    public override Guid ComponentGuid => new Guid("BA9C72C5-EC88-450B-B736-BE6D827FA2F3");
    protected override string IconTag => "S";

    public ElementTypeSimilar()
    : base("ElementType.Similar", "ElementType.Similar", "Obtains a set of types that are similar to Type", "Revit", "Type")
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "Type", "T", "ElementType to query for its similar types", GH_ParamAccess.item);
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "Types", "T", string.Empty, GH_ParamAccess.list);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      Autodesk.Revit.DB.ElementType elementType = null;
      if (!DA.GetData("Type", ref elementType))
        return;

      DA.SetDataList("Types", elementType?.GetSimilarTypes());
    }
  }

  public class ElementTypeDuplicate : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("5ED7E612-E5C6-4F0E-AA69-814CF2478F7E");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;
    protected override string IconTag => "D";

    public ElementTypeDuplicate() : base
    (
      "ElementType.Duplicate", "Duplicate",
      "Given a Name, it duplicates an ElementType into the active Revit document",
      "Revit", "Type"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.ElementType(), "Type", "T", "New ElementType", GH_ParamAccess.item);
    }

    void ReconstructElementTypeDuplicate
    (
      Document doc,
      ref Autodesk.Revit.DB.ElementType elementType,

      Autodesk.Revit.DB.ElementType type,
      string name
    )
    {
      ReplaceElement(ref elementType, type.Duplicate(name));
    }
  }
}
