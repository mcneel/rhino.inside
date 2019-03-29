import clr
clr.AddReference('System.Core')
clr.AddReference('RhinoInside.Revit')
clr.AddReference('RevitAPI') 
clr.AddReference('RevitAPIUI')

from System import Action, Func
from System.Linq import Enumerable
from Autodesk.Revit.DB import *
from Rhino.Geometry import *
from RhinoInside.Revit import Revit, Convert

def CommitToDocument(doc):
    sphere = Sphere(Point3d.Origin, 12 * Revit.ModelUnits)
    brep = sphere.ToBrep()
    meshes = Mesh.CreateFromBrep(brep, MeshingParameters.Default)

    category = ElementId(BuiltInCategory.OST_GenericModel)
    ds = DirectShape.CreateElement(doc, category)
    
    for geometry in Enumerable.ToList(Convert.ToHost(meshes)):
        ds.AppendShape(geometry)

Revit.EnqueueAction(Action[Document](CommitToDocument))
