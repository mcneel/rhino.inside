using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Grasshopper.Kernel;

using Autodesk.Revit.DB;

namespace RhinoInside.Revit.GH.Components
{
  public class FamilyInstanceByPointAtHost : GH_TransactionalComponentItem
  {
    public override Guid ComponentGuid => new Guid("0C642D7D-897B-479E-8668-91E09222D7B9");
    public override GH_Exposure Exposure => GH_Exposure.primary;
    protected override System.Drawing.Bitmap Icon => ImageBuilder.BuildIcon("MF");

    public FamilyInstanceByPointAtHost() : base
    (
      "AddFamilyInstance.ByPointAtHost", "ByPointAtHost",
      "Given its Position, it adds a FamilyInstance element to the active Revit document in a host element",
      "Revit", "Build"
    )
    { }

    protected override void RegisterInputParams(GH_InputParamManager manager)
    {
      manager.AddPlaneParameter("Position", "P", string.Empty, GH_ParamAccess.item);
      manager.AddParameter(new Parameters.ElementType(), "Type", "T", string.Empty, GH_ParamAccess.item);
      manager[manager.AddParameter(new Parameters.Element(), "Level", "L", string.Empty, GH_ParamAccess.item)].Optional = true;
      manager[manager.AddParameter(new Parameters.Element(), "Host", "H", string.Empty, GH_ParamAccess.item)].Optional = true;
    }

    protected override void RegisterOutputParams(GH_OutputParamManager manager)
    {
      manager.AddParameter(new Parameters.Element(), "Element", "E", "New Instance Element", GH_ParamAccess.item);
    }

    protected override void SolveInstance(IGH_DataAccess DA)
    {
      var location = new Rhino.Geometry.Plane(new Rhino.Geometry.Point3d(double.NaN, double.NaN, double.NaN), new Rhino.Geometry.Vector3d(double.NaN, double.NaN, double.NaN));
      DA.GetData("Position", ref location);

      FamilySymbol familySymbol = null;
      DA.GetData("Type", ref familySymbol);

      Autodesk.Revit.DB.Level level = null;
      DA.GetData("Level", ref level);
      if (level == null)
      {
        level = Revit.ActiveDBDocument.FindLevelByElevation(location.Origin.Z / Revit.ModelUnits);
      }

      Autodesk.Revit.DB.HostObject host = null;
      DA.GetData("Host", ref host);

      DA.DisableGapLogic();
      int Iteration = DA.Iteration;
      Revit.EnqueueAction((doc) => CommitInstance(doc, DA, Iteration, location, familySymbol, host, level));
    }

    void CommitInstance
    (
      Document doc, IGH_DataAccess DA, int Iteration,
      Rhino.Geometry.Plane location,
      Autodesk.Revit.DB.FamilySymbol familySymbol,
      Autodesk.Revit.DB.HostObject host,
      Autodesk.Revit.DB.Level level
    )
    {
      var element = PreviousElement(doc, Iteration);
      if (!element?.Pinned ?? false)
      {
        ReplaceElement(doc, DA, Iteration, element);
      }
      else try
      {
        var scaleFactor = 1.0 / Revit.ModelUnits;
        if (scaleFactor != 1.0)
        {
          location = location.Scale(scaleFactor);
        }

        if (!location.IsValid)
          throw new Exception(string.Format("Parameter '{0}' must be a valid point.", Params.Input[0].Name));

        if (familySymbol == null)
          throw new Exception(string.Format("Parameter '{0}' must be a FamilySymbol point.", Params.Input[1].Name));

        if (level == null)
          throw new Exception(string.Format("Parameter '{0}' must be a valid Level.", Params.Input[2].Name));

        if(host == null && familySymbol.Family.FamilyPlacementType == FamilyPlacementType.OneLevelBasedHosted)
          AddRuntimeMessage(GH_RuntimeMessageLevel.Warning, string.Format("Parameter '{0}' must be a valid HostObject.", Params.Input[3].Name));

        if (!familySymbol.IsActive)
          familySymbol.Activate();

        if (element is FamilyInstance && familySymbol.Id != element.GetTypeId())
        {
          var newElmentId = element.ChangeTypeId(familySymbol.Id);
          if (newElmentId != ElementId.InvalidElementId)
            element = doc.GetElement(newElmentId);
        }

        bool hasSameHost = false;
        if (element is FamilyInstance familyInstance)
        {
          hasSameHost = (familyInstance.Host?.Id ?? ElementId.InvalidElementId) == (host?.Id ?? ElementId.InvalidElementId);
          if (familyInstance.Host == null)
          {
            if (element?.get_Parameter(BuiltInParameter.INSTANCE_FREE_HOST_PARAM) is Parameter freeHostParam)
            {
              var freeHostName = freeHostParam.AsString();
              hasSameHost = freeHostName.EndsWith(host?.Name ?? level.Name);
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
          if (levelParam.AsElementId() != level.Id)
          {
            levelParam.Set(level.Id);
            doc.Regenerate();
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
          var creationDataList = new List<Autodesk.Revit.Creation.FamilyInstanceCreationData>()
          {
            new Autodesk.Revit.Creation.FamilyInstanceCreationData(location.Origin.ToHost(), familySymbol, host, level, Autodesk.Revit.DB.Structure.StructuralType.NonStructural)
          };

          ICollection<ElementId> newElementIds = null;

          if (doc.IsFamilyDocument)
            newElementIds = doc.FamilyCreate.NewFamilyInstances2(creationDataList);
          else
            newElementIds = doc.Create.NewFamilyInstances2(creationDataList);

          if (newElementIds.Count == 1)
          {
            element = CopyParametersFrom(doc.GetElement(newElementIds.First()), element);
            element?.get_Parameter(BuiltInParameter.FAMILY_LEVEL_PARAM).Set(level.Id);
          }
          else
            element = null;
        }

        if (element is FamilyInstance instance && instance.Host == null)
        {
          element.Pinned = false;
          SetTransform(instance, location.Origin.ToHost(), location.XAxis.ToHost(), location.YAxis.ToHost());
          element.Pinned = true;
        }

        ReplaceElement(doc, DA, Iteration, element);
      }
      catch (Exception e)
      {
        AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
        ReplaceElement(doc, DA, Iteration, null);
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

        //{
        //  var trans = (newOrigin / Revit.ModelUnits) - (current.Origin / Revit.ModelUnits);
        //  if (!trans.IsZeroLength())
        //    ElementTransformUtils.MoveElement(element.Document, element.Id, trans);
        //}
      }
    }
  }
}
