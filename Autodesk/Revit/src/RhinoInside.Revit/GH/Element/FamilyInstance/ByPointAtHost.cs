using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using DB = Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class FamilyInstanceByLocation : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("0C642D7D-897B-479E-8668-91E09222D7B9");
    public override GH_Exposure Exposure => GH_Exposure.primary;

    public FamilyInstanceByLocation () : base
    (
      "AddFamilyInstance.ByLocation", "ByLocation",
      "Given its location, it reconstructs a FamilyInstance element into the active Revit document",
      "Revit", "Build"
    )
    { }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.GeometricElement(), "Instance", "I", "New Instance Element", GH_ParamAccess.item);
    }

    void ReconstructFamilyInstanceByLocation
    (
      DB.Document doc,
      ref DB.Element element,

      [Description("Location where to place the element. Point or plane is accepted.")]
      Rhino.Geometry.Plane location,
      DB.FamilySymbol type,
      Optional<DB.Level> level,
      [Optional] DB.Element host
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      location = location.ChangeUnits(scaleFactor);

      if (!location.IsValid)
        ThrowArgumentException(nameof(location), "Should be a valid point or plane.");

      SolveOptionalLevel(ref level, doc, location.Origin.Z, nameof(level));

      if (host == null && type.Family.FamilyPlacementType == DB.FamilyPlacementType.OneLevelBasedHosted)
        ThrowArgumentException(nameof(host), $"This family requires a host.");

      if (!type.IsActive)
        type.Activate();

      ChangeElementTypeId(ref element, type.Id);

      bool hasSameHost = false;
      if (element is DB.FamilyInstance familyInstance)
      {
        hasSameHost = (familyInstance.Host?.Id ?? DB.ElementId.InvalidElementId) == (host?.Id ?? DB.ElementId.InvalidElementId);
        if (familyInstance.Host == null)
        {
          if (element?.get_Parameter(DB.BuiltInParameter.INSTANCE_FREE_HOST_PARAM) is DB.Parameter freeHostParam)
          {
            var freeHostName = freeHostParam.AsString();
            hasSameHost = freeHostName.EndsWith(host?.Name ?? level.Value.Name);
          }
        }
      }

      if
      (
        hasSameHost &&
        element is DB.FamilyInstance &&
        element.Location is DB.LocationPoint locationPoint
      )
      {
        using (var levelParam = element.get_Parameter(DB.BuiltInParameter.FAMILY_LEVEL_PARAM))
        {
          if (levelParam.AsElementId() != level.Value.Id)
          {
            levelParam.Set(level.Value.Id);
            doc.Regenerate();
          }
        }

        if (host is object)
        {
          var newOrigin = location.Origin.ToHost();
          if (!newOrigin.IsAlmostEqualTo(locationPoint.Point))
          {
            element.Pinned = false;
            locationPoint.Point = newOrigin;
            element.Pinned = true;
          }
        }
      }
      else
      {
        var creationData = new List<Autodesk.Revit.Creation.FamilyInstanceCreationData>()
        {
          new Autodesk.Revit.Creation.FamilyInstanceCreationData(location.Origin.ToHost(), type, host, level.Value, DB.Structure.StructuralType.NonStructural)
        };

        var newElementIds = doc.IsFamilyDocument ?
                            doc.FamilyCreate.NewFamilyInstances2(creationData) :
                            doc.Create.NewFamilyInstances2(creationData);

        if (newElementIds.Count != 1)
        {
          doc.Delete(newElementIds);
          throw new InvalidOperationException();
        }

        var parametersMask = new DB.BuiltInParameter[]
        {
          DB.BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
          DB.BuiltInParameter.ELEM_FAMILY_PARAM,
          DB.BuiltInParameter.ELEM_TYPE_PARAM,
          DB.BuiltInParameter.FAMILY_LEVEL_PARAM
        };

        ReplaceElement(ref element, doc.GetElement(newElementIds.First()), parametersMask);
        doc.Regenerate();
      }

      if (element is DB.FamilyInstance instance && instance.Host is null)
      {
        element.Pinned = false;
        instance.SetTransform(location.Origin.ToHost(), location.XAxis.ToHost(), location.YAxis.ToHost());
        element.Pinned = true;
      }
    }
  }
}
