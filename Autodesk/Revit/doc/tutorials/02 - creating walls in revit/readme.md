# Creating walls in Revit&reg; from a Rhino&reg; Curve
This sample shows how to take normal Rhino curve and create a set of Revit system family walls

This demonstration is meant to show that true native Revit objects can be created from simple Rhino geometry.  Editing the curve in Rhino will update the walls in Revit.

![Creating system family walls in Revit](create_walls_in_revit.jpg)


Open Sample files:
1. Open the [Walls Tutorial.rvt](/walls_tutorial.rvt) in Revit.
1. Start Rhino inside Revit and open the [Wall Model.3dm](/wall_model.3dm) file.
1. Start Grasshopper within Rhino.

The component necessary:
1. Add Wall by Curve component
1. Curve Param component from Grasshopper
1. Curve Split component from Grasshopper
1. Revit Element component
1. Element Decompose component
1. Level Input Selector
1. Slider for Wall Height

![Create Revit walls as system Families](create_walls_grasshopper_canvas.png)
After selecting the curve(s) in Rhino and the typical Wall in Revit for the wall family type, Grasshopper will generate the system family wall types  in Revit.
