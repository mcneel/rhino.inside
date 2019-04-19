# Grasshopper components for Revit
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within Revit.

It is important to have a basic understanding to the [Revit Data Hierarchy](https://www.modelical.com/en/gdocs/revit-data-hierarchy/) of Category -> Family -> Type -> Instance/Element to create and select elements.

This guide documents the Grasshopper components that support Revit interaction.

## Components

#### Build Components

| Icon | Name | Description |
| --- | --- | --- |
| ![Rhino sending geometry to Revit](GH/BeamByCurve.png) | Beam By Curve | Create a Revit Beam Object using a 2d or 3d curve for an axis |
| ![Rhino sending geometry to Revit](GH/FloorByOutline.png) | Floor By Outline | Create a Revit Floor Object using a 2d curve |
| ![Rhino sending geometry to Revit](GH/ColumnByCurve.png) | Column By Curve | Create a Revit Column Object using an axial curve|
| ![Rhino sending geometry to Revit](GH/WallByCurve.png) | Wall By Curve | Create a Revit Wall Object using a plan curve|
| ![Rhino sending geometry to Revit](GH/DirectShapeByGeometry.png) | DirectShape | Create a Directshape Element using a plan curve. This is the most generic way to import Geometry. |
| ![Rhino sending geometry to Revit](GH/DirectShapeCategories.png) | DirectShape Category | Create a Directshape category For using with the DirectShape Component |

#### Category Components

| Icon | Name | Description |
| --- | --- | --- |
| <img src="GH/CategoryDecompose.png"> | Category Decompose | Break a Revit Category into its component parts.  Name, Parent, Line-Color, Material, Allow Bounds and Material Quantities |
| ![Rhino sending geometry to Revit](GH/Category.png) | Category | Revit Category Param used for selecting persistent Category (future)|
| ![Rhino sending geometry to Revit](GH/CategoryTypes.png) | Category Types | A pick list of category types in Revit. |

#### Document Components

| Icon | Name | Description |
| --- | --- | --- |
| ![Rhino sending geometry to Revit](GH/DocumentCategories.png) | Document Categories | Get Active Document Category list Using the Type, and HasMaterial filter. |
| ![Rhino sending geometry to Revit](GH/DocumentElements.png) | Document Elements | Get Active Document Elements list using a Category filter|
| ![Rhino sending geometry to Revit](GH/DocumentElementTypes.png) | Document Element Types | Get Active Document Element Types using the Category, Family and Type filter|
| ![Rhino sending geometry to Revit](GH/DocumentLevels.png) | Document Levels | Get Active Document levels list from Revit|
| ![Rhino sending geometry to Revit](GH/DocumentParameters.png) | Document Parameters | Get Active Document Parameters attached to a specific category from Revit |

#### Elements Components

| Icon | Name | Description |
| --- | --- | --- |
| ![](GH/ElementDecompose.png) | Element Decompose | Decompose an Element into it's associated data including Constraints, Dimensions, Identity Data, Category, Family, Type, ID, etc...|
| ![](GH/ElementGeometry.png) | Element Geometry | Returns one or more Rhino Breps(s) form a Revit Element|
| ![](GH/ElementIdentity.png) | Element Identity | Returns Element's Name, Category, Type and UUID|
| ![](GH/ElementParameterGet.png) | Element Parameter Get | Get Element's Parameter Value based on a Parameter Name.|
| ![](GH/ElementParameters.png) | Element Parameters | Get Element's Parameter names attached to a specific Element |
| ![](GH/ElementParameterSet.png) | Element Parameters Set | Set an Element's Parameter Value by Element, Key and Value|
| ![](GH/ElementPreview.png) | Element Preview | Create a mesh from an Element using the LOD and the Mesh quality settings |
| ![](GH/Element.png) | Element| Select one or more persistent Element(s) in Revit to be used in Grasshopper. Also can be used to convert a sub-part to the parent element.|
| ![](GH/ElementType.png) | Element Type | Get Element type from the Element(s) input |

#### Geometry Components

| Icon | Name | Description |
| --- | --- | --- |
| ![](GH/BrepShapeByBrep.png) | Add Brep by Shape | Given a Brep, it adds a Brep element to the active Revit document|
| ![](GH/CurveShapeByCurve.png) | Add Curve Shape | Given a Curve, it adds a Curve shape to the active Revit document |
| ![](GH/MeshShapeByMesh.png) | Add Mesh Shape | Given a Mesh, it adds a Mesh element to the active Revit document |
| ![](GH/PointShapeByCurve.png) | Add Point Shape | Get Element's Parameter Value based on a Parameter Name.|
| ![](GH/Edge.png) | Edge Element | Select a Revit Element Edge(s) |
| ![](GH/Face.png) | Face Element | Select a Revit Element Face(s) |
| ![](GH/Vertex.png) | Vertex Element | Select a Revit Element Vertex(s) |

#### Revit Input Components

| Icon | Name | Description |
| --- | --- | --- |
| ![](GH/BuiltInParameterByName.png) | Select a built-in Parmeter by Name | Use a checklist, dropdown, scroll sequence or cycle interface to select a Parameter Key from Revit|
| ![](GH/DocumentCategoriesPicker.png) | Select a Document Category |  Use a checklist, dropdown, scroll sequence or cycle interface to select a document category from Revit |
| ![](GH/DocumentFamiliesPicker.png) | Select a Family | Use a checklist, dropdown, scroll sequence or cycle interface to select a document category from Revit |
| ![](GH/DocumentLevelsPicker.png) | Select a Level |  Use a checklist, dropdown, scroll sequence or cycle interface to select a level from Revit|
| ![](ElementTypeByName.png) | Select and Element Type |   Use a checklist, dropdown, scroll sequence or cycle interface to select a Element Type from Revit |

#### Massing Components

| Icon | Name | Description |
| --- | --- | --- |
| ![](GH/FormByCurves.png) | Add form by Curve | Given a list of curves, it adds a Form element to the active Revit document|
| ![](GH/FormByGeometry.png) | Add form by Geometry |  Given its Geometry, it adds a Form element to the active Revit document |

#### Modeling Components

| Icon | Name | Description |
| --- | --- | --- |
| ![](GH/ModelLineByCurve.png) | Add Model Line by Curve | Given a Curve, it adds a Curve element to the active Revit document|
| ![](GH/SketchPlaneByPlane.png) | Add Sketchplane by Plane |  Given a Rhino Plane, it adds a SketchPlane element to the active Revit document |
| ![](GH/SketchPlane.png) | Revit SketchPlane | Represents a Revit document sketch plane. (Selector in the future) |

#### Parameter Components

| Icon | Name | Description |
| --- | --- | --- |
| ![](GH/AddParameterByName.png) | Add Document Parameter by Name | Given its Name, it adds a Parameter definition to the active Revit document|
| ![](GH/ParameterKeyDecompose.png) | Decompose a Parameter Key|  Decompose a parameter definition into Name, Value Type, Visible Property and ID |
| ![](GH/ParameterValueDecompose.png) | Decompose a Parameter Value | Represents a Revit document sketch plane. (Selector in the future) |
| ![](GH/BuiltInParameterGroup.png) | Parameter Group | Represent Revit Paramter Group|
| ![](GH/BuiltInParameterGroups.png) | Selector for a Parameter group |   Use a checklist, dropdown, scroll sequence or cycle interface to select a Parameter Group from Revit |
| ![](GH/ParameterKey.png) | Parameter Key | Represents a Revit Paramter Key. (Selector in the future) |

#### Site Components

| Icon | Name | Description |
| --- | --- | --- |
| ![](GH/BuildingPadByOutline.png) | Add Building Pad by Outline | Given a set of contour Curves, it adds a BuildingPad element to the active Revit document|
| ![](GH/TopographyByPoints.png) | Add Topography Element by Points |  Given a set of Points, it adds a Topography surface to the active Revit document |





