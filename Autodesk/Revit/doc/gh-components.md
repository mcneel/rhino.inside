# Grasshopper components for Revit
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within Revit.

It is important to have a basic understanding to the [Revit Data Hierarchy](https://www.modelical.com/en/gdocs/revit-data-hierarchy/) of Category -> Family -> Type -> Instance/Element to create and select elements.

This guide documents the Grasshopper components that support Revit interaction.

## Components

#### Build Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/BeamByCurve.png" alt="AddBeamByCurve" width="32"></td>
    <td>Add Beam By Curve</td>
    <td>Create a Revit Beam Object using a 2d or 3d curve for an axis</td>
  </tr>
  <tr>
    <td><img src="GH/ColumnByCurve.png" alt="AddColumnByCurve" width="32"></td>
    <td>Add Column By Curve</td>
    <td>Create a Revit Column Object using an axial curve</td>
  </tr>
  <tr>
    <td><img src="GH/FamilyInstanceByPointAtHost.png" alt="AddFamilyInstanceByPoint" width="32"></td>
    <td>Add Family Instance by Point at Host</td>
    <td>Given a position, add a FamilyInstance element to the active Revit document in a host element.</td>
  </tr>
  <tr>
    <td><img src="GH/FloorByOutline.png" alt="AddFloorByOutline" width="32"></td>
    <td>Add Floor By Outline</td>
    <td>Create a Revit Floor using a plan curve</td>
  </tr>
  <tr>
    <td><img src="GH/RoofByOutline.png" alt="RoofByOutline" width="32"></td>
    <td>Add Roof By Outline</td>
    <td>Create a Revit Roof by using a boundary curve, type and level.</td>
  </tr>
  <tr>
    <td><img src="GH/WallByCurve.png" alt="ColumnByCurve" width="32"></td>
    <td>Wall By Curve</td>
    <td>Create a Revit Wall Object using a plan curve</td>
  </tr>
  <tr>
    <td><img src="GH/DirectShapeByGeometry.png" alt="AddDirectShapeByGeometry" width="32"></td>
    <td>Add DirectShape Geometry</td>
    <td>Create a Directshape Element using a plan curve. This is the most generic way to import Geometry.</td>
  </tr>
  <tr>
    <td><img src="GH/DirectShapeCategories.png" alt="DirectShapeCategories" width="32"></td>
    <td>DirectShape Category Selector</td>
    <td>Select a category for using with the DirectShape Component</td>
  </tr>
</table>



#### Category Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/CategoryDecompose.png" alt="BeamByCurve" width="32"></td>
    <td>Category Decompose</td>
    <td>Break a Revit Category into its component parts.  Name, Parent, Line-Color, Material, Allow Bounds and Material Quantities</td>
  </tr>
  <tr>
    <td><img src="GH/Category.png" alt="BeamByCurve" width="32"></td>
    <td>Category</td>
    <td>Revit Category Param used for selecting persistent Category (future)</td>
  </tr>
  <tr>
    <td><img src="GH/CategoryTypes.png" alt="ColumnByCurve" width="32"></td>
    <td>Category Types</td>
    <td>A pick list of category types in Revit.</td>
  </tr>
</table>

#### Document Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/DocumentCategories.png" alt="BeamByCurve" width="32"></td>
    <td>Document Categories</td>
    <td>Get Active Document Category list Using the Type, and HasMaterial filter.</td>
  </tr>
  <tr>
    <td><img src="GH/DocumentElements.png" alt="BeamByCurve" width="32"></td>
    <td>Document Elements</td>
    <td>Get Active Document Elements list using a Category filter</td>
  </tr>
  <tr>
    <td><img src="GH/DocumentElementTypes.png" alt="ColumnByCurve" width="32"></td>
    <td>Document Element Types</td>
    <td>Get Active Document Element Types using the Category, Family and Type filter</td>
  </tr>
  <tr>
    <td><img src="GH/DocumentLevels.png" alt="BeamByCurve" width="32"></td>
    <td>Document Levels</td>
    <td>Get Active Document levels list from Revit</td>
  </tr>
  <tr>
    <td><img src="GH/DocumentParameters.png" alt="ColumnByCurve" width="32"></td>
    <td>Document Parameters</td>
    <td>Get Active Document Parameters attached to a specific category from Revit</td>
  </tr>
</table>


#### Elements Components


<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/ElementDecompose.png" alt="BeamByCurve" width="32"></td>
    <td>Element Decompose</td>
    <td>Decompose an Element into it's associated data including Constraints, Dimensions, Identity Data, Category, Family, Type, ID, etc...</td>
  </tr>
  <tr>
    <td><img src="GH/ElementGeometry.png" alt="BeamByCurve" width="32"></td>
    <td>Element Geometry</td>
    <td>Returns one or more Rhino Breps(s) form a Revit Element</td>
  </tr>
  <tr>
    <td><img src="GH/ElementIdentity.png" alt="ColumnByCurve" width="32"></td>
    <td>Element Identity</td>
    <td>Returns Element's Name, Category, Type and UUID</td>
  </tr>
  <tr>
    <td><img src="GH/ElementParameterGet.png" alt="BeamByCurve" width="32"></td>
    <td>Element Parameter Get</td>
    <td>Get Element's Parameter Value based on a Parameter Name</td>
  </tr>
  <tr>
    <td><img src="GH/ElementParameters.png" alt="ColumnByCurve" width="32"></td>
    <td>Element Parameters</td>
    <td>Get Element's Parameter names attached to a specific Element</td>
  </tr>
  <tr>
    <td><img src="GH/ElementParametersSet.png" alt="BeamByCurve" width="32"></td>
    <td>Element Parameters Set</td>
    <td>Set an Element's Parameter Value by Element, Key and Value</td>
  </tr>
  <tr>
    <td><img src="GH/ElementPreview.png" alt="ColumnByCurve" width="32"></td>
    <td>Element Preview</td>
    <td>Create a mesh from an Element using the LOD and the Mesh quality settings</td>
  </tr>
  <tr>
    <td><img src="GH/Element.png" alt="BeamByCurve" width="32"></td>
    <td>Element</td>
    <td>Select one or more persistent Element(s) in Revit to be used in Grasshopper. Also can be used to convert a sub-part to the parent element</td>
  </tr>
  <tr>
    <td><img src="GH/ElementType.png" alt="ColumnByCurve" width="32"></td>
    <td>Element Type</td>
    <td>Get Element type from the Element(s) input</td>
  </tr>
</table>

#### Geometry Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/DirectShapeByBrep.png" alt="DirectShapeByBrep" width="32"></td>
    <td>Add Brep by Shape</td>
    <td>Given a Brep, it adds a Brep element to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/DirectShapeByCurve.png" alt="DirectShapeByCurve" width="32"></td>
    <td>Add Curve Shape</td>
    <td>Given a Curve, it adds a Curve shape to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/DirectShapeByMesh.png" alt="DirectShapeByMesh" width="32"></td>
    <td>Add Mesh Shape</td>
    <td>Given a Mesh, it adds a Mesh element to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/DirectShapeByPoint.png" alt="DirectShapeByPoint" width="32"></td>
    <td>Add Point Shape</td>
    <td>Given a Point, it adds a Point element to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/Edge.png" alt="ColumnByCurve" width="32"></td>
    <td>Edge Element</td>
    <td>Select a Revit Element Edge(s)</td>
  </tr>
  <tr>
    <td><img src="GH/Face.png" alt="BeamByCurve" width="32"></td>
    <td>Face Element</td>
    <td>Select a Revit Element Face(s)</td>
  </tr>
  <tr>
    <td><img src="GH/Vertex.png" alt="ColumnByCurve" width="32"></td>
    <td>Vertex Element</td>
    <td>Select a Revit Element Vertex(s)</td>
  </tr>
</table>


#### Revit Input Components


<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/BuiltInParameterByName.png" alt="BeamByCurve" width="32"></td>
    <td>Select a built-in Parameter by Name</td>
    <td>Use a checklist, dropdown, scroll sequence or cycle interface to select a Parameter Key from Revit</td>
  </tr>
  <tr>
    <td><img src="GH/DocumentCategoriesPicker.png" alt="BeamByCurve" width="32"></td>
    <td>Select a Document Category</td>
    <td>Use a checklist, dropdown, scroll sequence or cycle interface to select a document category from Revit</td>
  </tr>
  <tr>
    <td><img src="GH/DocumentFamiliesPicker.png" alt="ColumnByCurve" width="32"></td>
    <td>Select a Family</td>
    <td>Use a checklist, dropdown, scroll sequence or cycle interface to select a family from Revit</td>
  </tr>
  <tr>
    <td><img src="GH/DocumentLevelsPicker.png" alt="BeamByCurve" width="32"></td>
    <td>Select a Level</td>
    <td>Use a checklist, dropdown, scroll sequence or cycle interface to select a level from Revit</td>
  </tr>
  <tr>
    <td><img src="GH/ElementTypeByName.png" alt="ColumnByCurve" width="32"></td>
    <td>Select an Element Type</td>
    <td>Use a checklist, dropdown, scroll sequence or cycle interface to select a Element Type from Revit</td>
  </tr>
</table>

#### Massing Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/FormByCurves.png" alt="BeamByCurve" width="32"></td>
    <td>Add form by Curve</td>
    <td>Given a list of curves, it adds a Form element to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/FormByGeometry.png" alt="BeamByCurve" width="32"></td>
    <td>Add form by Geometry</td>
    <td>Given its Geometry, it adds a Form element to the active Revit document</td>
  </tr>
</table>


#### Modeling Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/ModelLineByCurve.png" alt="BeamByCurve" width="32"></td>
    <td>Add Model Line by Curve</td>
    <td>Given a Curve, it adds a Curve element to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/SketchPlaneByPlane.png" alt="BeamByCurve" width="32"></td>
    <td>Add Sketchplane by Plane</td>
    <td>Given a Rhino Plane, it adds a SketchPlane element to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/SketchPlane.png" alt="BeamByCurve" width="32"></td>
    <td>Revit SketchPlane</td>
    <td>Represents a Revit document sketch plane. (Selector in the future)</td>
  </tr>
</table>

#### Parameter Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/ParameterByName.png" alt="BeamByCurve" width="32"></td>
    <td>Add Document Parameter by Name</td>
    <td>Given its Name, it adds a Parameter definition to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/ParameterKeyDecompose.png" alt="BeamByCurve" width="32"></td>
    <td>Decompose a Parameter Key</td>
    <td>Decompose a parameter key into Name, Value Type, Visible Property and ID</td>
  </tr>
  <tr>
    <td><img src="GH/ParameterValueDecompose.png" alt="BeamByCurve" width="32"></td>
    <td>Decompose a Parameter Value</td>
    <td>Decompose a parameter value into Name, Value Type, Visible Property and ID</td>
  </tr>
  <tr>
    <td width="48px"><img src="GH/BuiltInParameterGroup.png" alt="BeamByCurve" width="32"></td>
    <td>Parameter Group</td>
    <td>Represent Revit Paramter Group</td>
  </tr>
  <tr>
    <td><img src="GH/BuiltInParameterGroups.png" alt="BeamByCurve" width="32"></td>
    <td>Selector for a Parameter group</td>
    <td>Use a checklist, dropdown, scroll sequence or cycle interface to select a Parameter Group from Revit</td>
  </tr>
  <tr>
    <td><img src="GH/ParameterKey.png" alt="BeamByCurve" width="32"></td>
    <td>Parameter Key</td>
    <td>Represents a Revit Parameter Key. (Selector in the future)</td>
  </tr>
</table>


#### Site Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/BuildingPadByOutline.png" alt="BeamByCurve" width="32"></td>
    <td>Add Building Pad by Outline</td>
    <td>Given a set of contour Curves, it adds a BuildingPad element to the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/TopographyByPoints.png" alt="BeamByCurve" width="32"></td>
    <td>Add Topography Element by Points</td>
    <td>Given a set of Points, it adds a Topography surface to the active Revit document</td>
  </tr>
</table>
