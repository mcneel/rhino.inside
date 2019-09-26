using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using Autodesk.Revit.DB;
using Grasshopper.Kernel;
using RhinoInside.Runtime.InteropServices;

namespace RhinoInside.Revit.GH.Components
{
  public class FamilyInstanceByLocation : ReconstructElementComponent
  {
    public override Guid ComponentGuid => new Guid("0C642D7D-897B-479E-8668-91E09222D7B9");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override TransactionStrategy TransactionalStrategy => TransactionStrategy.PerComponent;

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
      Document doc,
      ref Autodesk.Revit.DB.Element element,

      [Description("Location where to place the element. Point or plane is accepted.")]
      Rhino.Geometry.Plane location,
      Autodesk.Revit.DB.FamilySymbol type,
      Optional<Autodesk.Revit.DB.Level> level,
      [Optional] Autodesk.Revit.DB.Element host
    )
    {
      var scaleFactor = 1.0 / Revit.ModelUnits;
      location = location.ChangeUnits(scaleFactor);

      if (!location.IsValid)
        ThrowArgumentException(nameof(location), "Should be a valid point or plane.");

      SolveOptionalLevel(ref level, doc, location.Origin.Z, nameof(level));

      if (host == null && type.Family.FamilyPlacementType == FamilyPlacementType.OneLevelBasedHosted)
        ThrowArgumentNullException(nameof(host), $"This family requires a host.");

      if (!type.IsActive)
        type.Activate();

      ChangeElementTypeId(ref element, type.Id);

      bool hasSameHost = false;
      if (element is FamilyInstance familyInstance)
      {
        hasSameHost = (familyInstance.Host?.Id ?? ElementId.InvalidElementId) == (host?.Id ?? ElementId.InvalidElementId);
        if (familyInstance.Host == null)
        {
          if (element?.get_Parameter(BuiltInParameter.INSTANCE_FREE_HOST_PARAM) is Parameter freeHostParam)
          {
            var freeHostName = freeHostParam.AsString();
            hasSameHost = freeHostName.EndsWith(host?.Name ?? level.Value.Name);
          }
        }
      }

      if
      (
        hasSameHost &&
        element is FamilyInstance &&
        element.Location is LocationPoint locationPoint
      )
      {
        using (var levelParam = element.get_Parameter(BuiltInParameter.FAMILY_LEVEL_PARAM))
        {
          if (levelParam.AsElementId() != level.Value.Id)
          {
            levelParam.Set(level.Value.Id);
            doc.Regenerate();
          }
        }

        var newOrigin = location.Origin.ToHost();
        if (!newOrigin.IsAlmostEqualTo(locationPoint.Point))
        {
          element.Pinned = false;
          locationPoint.Point = newOrigin;
          element.Pinned = true;
        }
      }
      else
      {
        var creationData = new List<Autodesk.Revit.Creation.FamilyInstanceCreationData>()
        {
          new Autodesk.Revit.Creation.FamilyInstanceCreationData(location.Origin.ToHost(), type, host, level.Value, Autodesk.Revit.DB.Structure.StructuralType.NonStructural)
        };

        var newElementIds = doc.IsFamilyDocument ?
                            doc.FamilyCreate.NewFamilyInstances2(creationData) :
                            doc.Create.NewFamilyInstances2(creationData);

        if (newElementIds.Count != 1)
        {
          doc.Delete(newElementIds);
          throw new InvalidOperationException();
        }

        var parametersMask = new BuiltInParameter[]
        {
          BuiltInParameter.ELEM_FAMILY_AND_TYPE_PARAM,
          BuiltInParameter.ELEM_FAMILY_PARAM,
          BuiltInParameter.ELEM_TYPE_PARAM,
          BuiltInParameter.FAMILY_LEVEL_PARAM
        };

        ReplaceElement(ref element, doc.GetElement(newElementIds.First()), parametersMask);
      }

      if (element is FamilyInstance instance && instance.Host == null)
      {
        element.Pinned = false;
        SetTransform(instance, location.Origin.ToHost(), location.XAxis.ToHost(), location.YAxis.ToHost());
        element.Pinned = true;
      }
    }

    static void SetTransform(Autodesk.Revit.DB.Instance element, XYZ newOrigin, XYZ newBasisX, XYZ newBasisY)
    {
      var current = element.GetTransform();
      var BasisZ = newBasisX.CrossProduct(newBasisY);
      {
        if (!current.BasisZ.IsParallelTo(BasisZ))
        {
          var axisDirection = current.BasisZ.CrossProduct(BasisZ);
          double angle = current.BasisZ.AngleTo(BasisZ);

          using (var axis = Line.CreateUnbound((current.Origin / Revit.ModelUnits), axisDirection))
            ElementTransformUtils.RotateElement(element.Document, element.Id, axis, angle);

          current = element.GetTransform();
        }

        if (!current.BasisX.IsAlmostEqualTo(newBasisX))
        {
          double angle = current.BasisX.AngleOnPlaneTo(newBasisX, BasisZ);
          using (var axis = Line.CreateUnbound((current.Origin / Revit.ModelUnits), BasisZ))
            ElementTransformUtils.RotateElement(element.Document, element.Id, axis, angle);
        }

        {
          var trans = (newOrigin / Revit.ModelUnits) - (current.Origin / Revit.ModelUnits);
          if (!trans.IsZeroLength())
            ElementTransformUtils.MoveElement(element.Document, element.Id, trans);
        }
      }
    }
  }
}
