using Rhino;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

namespace RhinoInside.Unity.Sample1
{
  [InitializeOnLoad]
  [ExecuteInEditMode]
  public class LoftSurface : MonoBehaviour
  {
    [MenuItem("Sample1/Create Loft Surface")]
    public static void Create()
    {
      var surface = new GameObject("Loft Surface");
      surface.AddComponent<LoftSurface>() ;
    }

    public static UnityEngine.Mesh CreateLoft(List<List<Vector3>> controlPoints)
    {
      if (controlPoints.Count > 0 )
      {
        var profileCurves = new List<Rhino.Geometry.Curve>();
        foreach(var controlPointsRow in controlPoints)
          profileCurves.Add(Rhino.Geometry.Curve.CreateInterpolatedCurve(controlPointsRow.ToRhino(), 3));

        return Rhino.Geometry.Mesh.CreateFromBrep(
                Rhino.Geometry.Brep.CreateFromLoft(
                    profileCurves,
                    Rhino.Geometry.Point3d.Unset,
                    Rhino.Geometry.Point3d.Unset,
                    Rhino.Geometry.LoftType.Normal,
                    false)[0], Rhino.Geometry.MeshingParameters.Default)[0].ToHost();
      }

      return null;
    }

    const int UCount = 4;
    const int VCount = 4;

    void Start()
    {
      gameObject.AddComponent<MeshFilter>();

      var material = new Material(Shader.Find("Standard"))
      {
        color = new Color(1.0f, 0.0f, 0.0f, 1f)
      };

      gameObject.AddComponent<MeshRenderer>().material = material;

      var cpMaterial = new Material(Shader.Find("Standard"))
      {
        color = new Color(0.2f, 0.2f, 0.8f, 1f)
      };

      for (int i = 0; i < UCount; i++)
      {
        for (int j = 0; j < VCount; j++)
        {
          var controlSphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
          controlSphere.transform.parent = gameObject.transform;
          controlSphere.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
          controlSphere.transform.position = new Vector3(i * 5f, (i + j) % 2 == 0 ? 0f : 2f, j * 5f);
          controlSphere.GetComponent<MeshRenderer>().material = cpMaterial;
        }
      }
    }

    void Update()
    {
      var controlPoints = new List<List<Vector3>>();
      {
        int i = 0;
        List<Vector3> controlPointsRow = null;
        foreach (Transform controlSphere in transform)
        {
          if ((i++ % VCount) == 0)
          {
            controlPointsRow = new List<Vector3>(VCount);
            controlPoints.Add(controlPointsRow);
          }

          controlPointsRow.Add(gameObject.transform.worldToLocalMatrix.MultiplyPoint(controlSphere.gameObject.transform.position));
        }
      }

      gameObject.GetComponent<MeshFilter>().mesh = CreateLoft(controlPoints);
    }
  }
}
