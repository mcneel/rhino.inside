# Grasshopper components for Revit
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within Revit.

This guide documents the Grasshopper components that support Revit interaction.

## Components

#### Build Components

 | Icon | Name | Description |
 | --- | --- | --- |
 | ![Rhino sending geometry to Revit](gh-beambycurve.jpg) | Beam By Curve | Create a Revit Beam Object using a 2d or 3d curve for an axis |
 | ![Rhino sending geometry to Revit](gh-floorbycurve.jpg) | Floor By Curve | Create a Revit Floor Object using a 2d curve |
 | ![Rhino sending geometry to Revit](gh-columnbycurve.jpg) | Column By Curve | Create a Revit Column Object using an axial curve|
 | ![Rhino sending geometry to Revit](gh-wallbycurve.jpg) | Wall By Curve | Create a Revit Wall Object using a plan curve|
 | ![Rhino sending geometry to Revit](gh-directshape.jpg) | DirectShape | Create a Directshape Element using a plan curve. This is the most generic way to import Geometry. |
 | ![Rhino sending geometry to Revit](gh-directshapecategory.jpg) | DirectShape Category | Create a Directshape category For using with the DirectShape Component |

 #### Category Components

  | Icon | Name | Description |
  | --- | --- | --- |
  | ![Rhino sending geometry to Revit](gh-categorydecompose.jpg) | Category Decompose | Break a Revit Category into its component parts.  Name, Parent, Line-Color, Material, Allow Bounds and Material Quantities |
  | ![Rhino sending geometry to Revit](gh-categorydecompose.jpg) | Category | Revit Category Param |
  | ![Rhino sending geometry to Revit](gh-categorydecompose.jpg) | Category Types | A pick list of category types in Revit. |

  #### Document Components

   | Icon | Name | Description |
   | --- | --- | --- |
   | ![Rhino sending geometry to Revit](gh-categorydecompose.jpg) | Document Categories | Get Active Revit Document Category list |
   | ![Rhino sending geometry to Revit](gh-categorydecompose.jpg) | Document Element Types | Get Active Revit Document Elements list |
   | ![Rhino sending geometry to Revit](gh-categorydecompose.jpg) | Document Categories | Get Active Revit Document Category list |
