using System;
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI;

using Rhino;
using Rhino.Geometry;
using Rhino.FileIO;
using Rhino.DocObjects;
using RhinoInside.Revit.UI;
#if REVIT_2018
using Autodesk.Revit.DB.Visual;
#else
using Autodesk.Revit.Utility;
#endif

namespace RhinoInside.Revit.Samples
{
  [Transaction(TransactionMode.Manual), Regeneration(RegenerationOption.Manual)]
  public class Sample8 : RhinoCommand
  {
    public static void CreateUI(RibbonPanel ribbonPanel)
    {
      var buttonData = NewPushButtonData<Sample8, Availability>("Sample 8");

      if (ribbonPanel.AddItem(buttonData) is PushButton pushButton)
      {
        pushButton.ToolTip = "Imports geometry from 3dm file to a Revit model or family";
        pushButton.Image = ImageBuilder.BuildImage("8");
        pushButton.LargeImage = ImageBuilder.BuildLargeImage("8");
        pushButton.SetContextualHelp(new ContextualHelp(ContextualHelpType.Url, "https://github.com/mcneel/rhino.inside/blob/master/Autodesk/Revit/README.md#sample-8"));
      }
    }

    static string ByteArrayToString(byte[] data)
    {
      var hex = new StringBuilder(data.Length * 2);

      for (int i = 0; i < data.Length; i++)
        hex.Append(data[i].ToString("X2"));

      return hex.ToString();
    }

    public static Dictionary<string, Autodesk.Revit.DB.Material> GetMaterialsByName(Document doc)
    {
      var collector = new FilteredElementCollector(doc);
      return collector.OfClass(typeof(Autodesk.Revit.DB.Material)).OfType<Autodesk.Revit.DB.Material>().
        GroupBy(x => x.Name).
        ToDictionary(x => x.Key, x => x.First());
    }

    static string GenericAssetName(Autodesk.Revit.ApplicationServices.LanguageType language)
    {
      switch (language)
      {
        case Autodesk.Revit.ApplicationServices.LanguageType.English_USA:           return "Generic";
        case Autodesk.Revit.ApplicationServices.LanguageType.German:                return "Generisch";
        case Autodesk.Revit.ApplicationServices.LanguageType.Spanish:               return "Genérico";
        case Autodesk.Revit.ApplicationServices.LanguageType.French:                return "Générique";
        case Autodesk.Revit.ApplicationServices.LanguageType.Italian:               return "Generico";
        case Autodesk.Revit.ApplicationServices.LanguageType.Dutch:                 return "Allgemeine";
        case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Simplified:    return "常规";
        case Autodesk.Revit.ApplicationServices.LanguageType.Chinese_Traditional:   return "常規";
        case Autodesk.Revit.ApplicationServices.LanguageType.Japanese:              return "一般";
        case Autodesk.Revit.ApplicationServices.LanguageType.Korean:                return "일반";
        case Autodesk.Revit.ApplicationServices.LanguageType.Russian:               return "общий";
        case Autodesk.Revit.ApplicationServices.LanguageType.Czech:                 return "Obecný";
        case Autodesk.Revit.ApplicationServices.LanguageType.Polish:                return "Rodzajowy";
        case Autodesk.Revit.ApplicationServices.LanguageType.Hungarian:             return "Generikus";
        case Autodesk.Revit.ApplicationServices.LanguageType.Brazilian_Portuguese:  return "Genérico";
        #if REVIT_2018
        case Autodesk.Revit.ApplicationServices.LanguageType.English_GB:            return "Generic";
        #endif
      }

      return null;
    }

    static string GenericAssetName() => GenericAssetName(Revit.ActiveUIApplication.Application.Language) ?? "Generic";

    public static AppearanceAssetElement GetGenericAppearanceAssetElement(Document doc)
    {
      var applicationLanguage = Revit.ActiveUIApplication.Application.Language;
      var languages = Enumerable.Repeat(applicationLanguage, 1).
      Concat
      (
        Enum.GetValues(typeof(Autodesk.Revit.ApplicationServices.LanguageType)).
        Cast<Autodesk.Revit.ApplicationServices.LanguageType>().
        Where(lang => lang != applicationLanguage && lang != Autodesk.Revit.ApplicationServices.LanguageType.Unknown)
      );

      foreach (var lang in languages)
      {
        if (AppearanceAssetElement.GetAppearanceAssetElementByName(doc, GenericAssetName(lang)) is AppearanceAssetElement assetElement)
          return assetElement;
      }

      return null;
    }

    static ElementId ToHost(Rhino.Render.RenderMaterial mat, Document doc, string name)
    {
      var appearanceAssetId = ElementId.InvalidElementId;

#if REVIT_2019
      if (AppearanceAssetElement.GetAppearanceAssetElementByName(doc, name) is AppearanceAssetElement appearanceAssetElement)
        appearanceAssetId = appearanceAssetElement.Id;
      else
      {
        appearanceAssetElement = GetGenericAppearanceAssetElement(doc);
        if (appearanceAssetElement is null)
        {
          var assets = Revit.ActiveUIApplication.Application.GetAssets(AssetType.Appearance);
          foreach (var asset in assets)
          {
            if (asset.Name == GenericAssetName())
            {
              appearanceAssetElement = AppearanceAssetElement.Create(doc, name, asset);
              appearanceAssetId = appearanceAssetElement.Id;
              break;
            }
          }
        }
        else
        {
          appearanceAssetElement = appearanceAssetElement.Duplicate(name);
          appearanceAssetId = appearanceAssetElement.Id;
        }

        if (appearanceAssetId != ElementId.InvalidElementId)
        {
          using (var editScope = new AppearanceAssetEditScope(doc))
          {
            var editableAsset = editScope.Start(appearanceAssetId);

            //var category = editableAsset.FindByName("category") as AssetPropertyString;
            //category.Value = $":{mat.Category.FirstCharUpper()}";

            var description = editableAsset.FindByName("description") as AssetPropertyString;
            description.Value = mat.Notes ?? string.Empty;

            var keyword = editableAsset.FindByName("keyword") as AssetPropertyString;
            {
              string tags = string.Empty;
              foreach (var tag in (mat.Tags ?? string.Empty).Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries))
                tags += $":{tag.Replace(':', ';')}";
              keyword.Value = tags;
            }

            if (mat.SmellsLikeMetal || mat.SmellsLikeTexturedMetal)
            {
              var generic_self_illum_luminance = editableAsset.FindByName(Generic.GenericIsMetal) as AssetPropertyBoolean;
              generic_self_illum_luminance.Value = true;
            }

            if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.Diffuse, out Rhino.Display.Color4f diffuse))
            {
              var generic_diffuse = editableAsset.FindByName(Generic.GenericDiffuse) as AssetPropertyDoubleArray4d;
              generic_diffuse.SetValueAsDoubles(new double[] { diffuse.R, diffuse.G, diffuse.B, diffuse.A });
            }

            if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.Transparency, out double transparency))
            {
              var generic_transparency = editableAsset.FindByName(Generic.GenericTransparency) as AssetPropertyDouble;
              generic_transparency.Value = transparency;

              if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.TransparencyColor, out Rhino.Display.Color4f transparencyColor))
              {
                diffuse = diffuse.BlendTo((float) transparency, transparencyColor);

                var generic_diffuse = editableAsset.FindByName(Generic.GenericDiffuse) as AssetPropertyDoubleArray4d;
                generic_diffuse.SetValueAsDoubles(new double[] { diffuse.R, diffuse.G, diffuse.B, diffuse.A });
              }
            }

            if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.Ior, out double ior))
            {
              var generic_refraction_index = editableAsset.FindByName(Generic.GenericRefractionIndex) as AssetPropertyDouble;
              generic_refraction_index.Value = ior;
            }

            if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.Shine, out double shine))
            {
              if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.Specular, out Rhino.Display.Color4f specularColor))
              {
                var generic_reflectivity_at_0deg = editableAsset.FindByName(Generic.GenericReflectivityAt0deg) as AssetPropertyDouble;
                generic_reflectivity_at_0deg.Value = shine * specularColor.L;
              }
            }

            if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.Reflectivity, out double reflectivity))
            {
              if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.ReflectivityColor, out Rhino.Display.Color4f reflectivityColor))
              {
                var generic_reflectivity_at_90deg = editableAsset.FindByName(Generic.GenericReflectivityAt90deg) as AssetPropertyDouble;
                generic_reflectivity_at_90deg.Value = reflectivity * reflectivityColor.L;

                if (mat.Fields.TryGetValue("fresnel-enabled", out bool fresnel_enabled) && !fresnel_enabled)
                {
                  diffuse = diffuse.BlendTo((float) reflectivity, reflectivityColor);
                  var generic_diffuse = editableAsset.FindByName(Generic.GenericDiffuse) as AssetPropertyDoubleArray4d;
                  generic_diffuse.SetValueAsDoubles(new double[] { diffuse.R, diffuse.G, diffuse.B, diffuse.A });
                }
              }
            }

            if (mat.Fields.TryGetValue("polish-amount", out double polish_amount))
            {
              var generic_glossiness = editableAsset.FindByName(Generic.GenericGlossiness) as AssetPropertyDouble;
              generic_glossiness.Value = polish_amount;
            }

            if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.Emission, out Rhino.Display.Color4f emission))
            {
              var generic_self_illum_filter_map = editableAsset.FindByName(Generic.GenericSelfIllumFilterMap) as AssetPropertyDoubleArray4d;
              generic_self_illum_filter_map.SetValueAsDoubles(new double[] { emission.R, emission.G, emission.B, emission.A });
            }

            if (mat.Fields.TryGetValue(Rhino.Render.RenderMaterial.BasicMaterialParameterNames.DisableLighting, out bool self_illum))
            {
              var generic_self_illum_luminance = editableAsset.FindByName(Generic.GenericSelfIllumLuminance) as AssetPropertyDouble;
              generic_self_illum_luminance.Value = self_illum ? 200000 : 0.0;
            }

            editScope.Commit(false);
          }
        }
      }
#endif

      return appearanceAssetId;
    }

    static ElementId ToHost(Rhino.DocObjects.Material mat, Document doc, Dictionary<string, Autodesk.Revit.DB.Material> materials)
    {
      var id = ElementId.InvalidElementId;

      if(mat.HasName)
      {
        var matName = mat.Name;
        if (materials.TryGetValue(matName, out var material)) id = material.Id;
        else
        {
          id = Autodesk.Revit.DB.Material.Create(doc, matName);
          var newMaterial = doc.GetElement(id) as Autodesk.Revit.DB.Material;

          newMaterial.Color         = mat.PreviewColor.ToHost();
          newMaterial.Shininess     = (int) Math.Round(mat.Shine / Rhino.DocObjects.Material.MaxShine * 128.0);
          newMaterial.Smoothness    = (int) Math.Round(mat.Reflectivity * 100.0);
          newMaterial.Transparency  = (int) Math.Round(mat.Transparency * 100.0);
          newMaterial.AppearanceAssetId = ToHost(mat.RenderMaterial, doc, matName);

          materials.Add(matName, newMaterial);
        }
      }

      return id;
    }

    static IList<GeometryObject> ImportObject(File3dm model, GeometryBase geometry, ObjectAttributes attributes, Document doc, Dictionary<string, Autodesk.Revit.DB.Material> materials, double scaleFactor)
    {
      var layer = model.AllLayers.FindIndex(attributes.LayerIndex);
      if (layer?.IsVisible ?? false)
      {
        using (var ctx = Convert.Context.Push())
        {
          switch (attributes.MaterialSource)
          {
            case ObjectMaterialSource.MaterialFromObject:
              {
                var modelMaterial = attributes.MaterialIndex < 0 ? Rhino.DocObjects.Material.DefaultMaterial : model.AllMaterials.FindIndex(attributes.MaterialIndex);
                ctx.MaterialId = ToHost(modelMaterial, doc, materials);
                break;
              }
            case ObjectMaterialSource.MaterialFromLayer:
              {
                var modelLayer = model.AllLayers.FindIndex(attributes.LayerIndex);
                var modelMaterial = modelLayer.RenderMaterialIndex < 0 ? Rhino.DocObjects.Material.DefaultMaterial : model.AllMaterials.FindIndex(modelLayer.RenderMaterialIndex);
                ctx.MaterialId = ToHost(modelMaterial, doc, materials);
                break;
              }
          }

          if (geometry is InstanceReferenceGeometry instance)
          {
            if (model.AllInstanceDefinitions.FindId(instance.ParentIdefId) is InstanceDefinitionGeometry definition)
            {
              var definitionId = definition.Id.ToString();
              var library = DirectShapeLibrary.GetDirectShapeLibrary(doc);
              if (!library.Contains(definitionId))
              {
                var objectIds = definition.GetObjectIds();
                var GNodes = objectIds.
                  Select(x => model.Objects.FindId(x)).
                  Cast<File3dmObject>().
                  SelectMany(x => ImportObject(model, x.Geometry, x.Attributes, doc, materials, scaleFactor));

                library.AddDefinition(definitionId, GNodes.ToArray());
              }

              var xform = instance.Xform.ChangeUnits(scaleFactor);
              return DirectShape.CreateGeometryInstance(doc, definitionId, xform.ToHost());
            }
          }
          else return geometry.ToHostMultiple(scaleFactor).ToList();
        }
      }

      return new GeometryObject[0];
    }

    public static Result Import3DMFile(string filePath, Document doc, BuiltInCategory builtInCategory)
    {
      try
      {
        DirectShapeLibrary.GetDirectShapeLibrary(doc).Reset();

        using (var model = File3dm.Read(filePath))
        {
          var scaleFactor = RhinoMath.UnitScale(model.Settings.ModelUnitSystem, Revit.ModelUnitSystem);

          using (var trans = new Transaction(doc, "Import 3D Model"))
          {
            if (trans.Start() == TransactionStatus.Started)
            {
              var categoryId = new ElementId(builtInCategory);
              var materials = GetMaterialsByName(doc);

              var type = DirectShapeType.Create(doc, Path.GetFileName(filePath), categoryId);

              foreach (var obj in model.Objects.Where(x => !x.Attributes.IsInstanceDefinitionObject && x.Attributes.Space == ActiveSpace.ModelSpace))
              {
                if (!obj.Attributes.Visible)
                  continue;

                var geometryList = ImportObject(model, obj.Geometry, obj.Attributes, doc, materials, scaleFactor).ToArray();
                if (geometryList == null)
                  continue;

                try { type.AppendShape(geometryList); }
                catch (Autodesk.Revit.Exceptions.ArgumentException) { }
              }

              var ds = DirectShape.CreateElement(doc, type.Category.Id);
              ds.SetTypeId(type.Id);

              var library = DirectShapeLibrary.GetDirectShapeLibrary(doc);
              if (!library.ContainsType(type.UniqueId))
                library.AddDefinitionType(type.UniqueId, type.Id);

              ds.SetShape(DirectShape.CreateGeometryInstance(doc, type.UniqueId, Autodesk.Revit.DB.Transform.Identity));

              if (trans.Commit() == TransactionStatus.Committed)
              {
                var elements = new ElementId[] { ds.Id };
                Revit.ActiveUIDocument.Selection.SetElementIds(elements);
                Revit.ActiveUIDocument.ShowElements(elements);

                return Result.Succeeded;
              }
            }
          }
        }
      }
      finally
      {
        DirectShapeLibrary.GetDirectShapeLibrary(doc).Reset();
      }

      return Result.Failed;
    }

    public override Result Execute(ExternalCommandData data, ref string message, ElementSet elements)
    {
      if(!DirectShape.IsSupportedDocument(data.Application.ActiveUIDocument.Document))
      {
        message = "Active document can't support DirectShape functionality.";
        return Result.Failed;
      }

      using
      (
        var openFileDialog = new OpenFileDialog()
        {
          Filter = "Rhino 3D models (*.3dm)|*.3dm",
          FilterIndex = 1,
          RestoreDirectory = true
        }
      )
      {
        switch (openFileDialog.ShowDialog(ModalForm.OwnerWindow))
        {
          case DialogResult.OK:
            return Import3DMFile
            (
              openFileDialog.FileName,
              data.Application.ActiveUIDocument.Document,
              CommandGrasshopperBake.ActiveBuiltInCategory
            );
          case DialogResult.Cancel: return Result.Cancelled;
        }
      }

      return Result.Failed;
    }
  }
}
