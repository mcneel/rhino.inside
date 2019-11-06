# Grasshopper components for Revit
The Rhino Inside® technology allows Rhino and Grasshopper to be embedded within Revit.

It is important to have a basic understanding to the [Revit Data Hierarchy](https://www.modelical.com/en/gdocs/revit-data-hierarchy/) of Category -> Family -> Type -> Instance/Element to create and select elements. There is a good guide at [Revit Families: A Step-By-Step Introduction](https://www.autodesk.com/autodesk-university/article/Revit-Families-Step-Step-Introduction-2018)

This guide documents the Grasshopper components that support Revit interaction.

## Components

#### Parameter Components (Params tab)

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td><img src="GH/GeometricElement.png" alt="Geometric by Element" width="32"></td>
    <td>Geometric Element</td>
    <td>Select one or more persistent Element(s) in Revit to be used in Grasshopper. Also can be used to convert a sub-part to the parent element</td>
  </tr>
  <tr>
    <td><img src="GH/Host.png" alt="Host" width="32"></td>
    <td>Host</td>
    <td>Represents a Revit document host element.</td>
  </tr>
  <tr>
      <td><img src="GH/Edge.png" alt="Edge" width="32"></td>
      <td>Edge</td>
      <td>Represents a Revit edge from an element.</td>
  </tr>
  <tr>
      <td><img src="GH/Face.png" alt="Face" width="32"></td>
      <td>Face</td>
      <td>Select a Revit Element Face(s)</td>
  </tr>
  <tr>
      <td><img src="GH/SketchPlane.png" alt="SketchPlane" width="32"></td>
      <td>Sketch Plane</td>
      <td>Represents a Revit document sketch plane. (Selector in the future)</td>
   </tr>
  <tr>
      <td><img src="GH/Vertex.png" alt="Vertex" width="32"></td>
      <td>Vertex</td>
      <td>Select a Revit Element Vertex(s)</td>
   </tr>
   <tr>
    <td><img src="GH/Category.png" alt="BeamByCurve" width="32"></td>
    <td>Category</td>
    <td>Revit Category Param used for selecting persistent Category (future)</td>
  </tr>
  <tr>
    <td><img src="GH/GeometricElement.png" alt="GeometricElement" width="32"></td>
    <td>Geometric Element</td>
    <td>Select one or more persistent Element(s) in Revit to be used in Grasshopper. Also can be used to convert a sub-part to the parent element</td>
  </tr>
  <tr>
    <td><img src="GH/ElementType.png" alt="ElementType" width="32"></td>
    <td>Element Type</td>
    <td>Get Element type from the Element(s) input</td>
  </tr>
  <tr>
    <td><img src="GH/Family.png" alt="Family" width="32"></td>
    <td>Family</td>
    <td>Represents a Revit document family.</td>
  </tr>
  <tr>
    <td><img src="GH/GraphicStyle.png" alt="GraphicStyle" width="32"></td>
    <td>Graphic Style</td>
    <td>Represents a Revit Graphic Style.</td>
  </tr>
  <tr>
    <td><img src="GH/Level.png" alt="Level" width="32"></td>
    <td>Level</td>
    <td>Represents a Revit Level</td>
  </tr>
  <tr>
    <td><img src="GH/BuiltInParameterGroup.png" alt="BuiltInParameterGroup" width="32"></td>
    <td>Parameter Group</td>
    <td>Represents a Revit Parameter Group</td>
  </tr>
  <tr>
      <td><img src="GH/ParameterKey.png" alt="ParameterKey" width="32"></td>
      <td>Parameter Key</td>
      <td>Represents a Revit Parameter Key</td>
  </tr>
</table>


#### Build Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>    
      <td width="48px"><img src="GH/AdaptiveComponentByPoints.png" alt="AdaptiveComponentByPoints" width="32"></td>    
      <td>Add Adaptive Component by Points</td>    
      <td>Adds an adaptive component instance using a list of points to Revit.  The points must be sorted in the same order as the adaptive component expects.</td>  
    </tr>
    <tr>
    <td width="48px"><img src="GH/BeamByCurve.png" alt="AddBeamByCurve" width="32"></td>
    <td>Add Beam By Curve</td>
    <td>Create a Revit Beam Object using a 2d or 3d curve for an axis/  Also assign a level.</td>
  </tr>
  <tr>
    <td><img src="GH/ColumnByCurve.png" alt="AddColumnByCurve" width="32"></td>
    <td>Add Column By Curve</td>
    <td>Create a Revit Column Object using an axial curve</td>
  </tr>
  <tr>
    <td><img src="GH/FamilyInstanceByLocation.png" alt="FamilyInstanceByLocation" width="32"></td>
    <td>Add Family Instance by Location</td>
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
    <td>Create a Revit Wall Object using a plan curve. The Level, Type, Height and other properties can be specified. See the component help for options.</td>
  </tr>
  <tr>
    <td><img src="GH/DirectShapeByLocation.png" alt="DirectShapeByLocation" width="32"></td>
    <td>Add DirectShape By Location</td>
    <td>Create a Directshape instance from a Directshape Type. Insert a specific DirectShape instance. The input for this component many times will the the Element Type By Name Component.</td>
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
      <td width="48px"><img src="GH/CategoryGraphicStyle.png" alt="CategoryGraphicStyle" width="32"></td>
      <td>Category Graphic Style</td>
      <td>Returns the Projections an Cut of a specifcs categories graphic style.</td>
  </tr>
  <tr>
    <td width="48px"><img src="GH/CategoryIdentity.png" alt="CategoryIdentity" width="32"></td>
    <td>Category Identity</td>
    <td>Break a Revit Category into its component parts.  Name, Parent, Allow Bounds and Material Quantities</td>
  </tr>
  <tr>
    <td width="48px"><img src="GH/CategoryObjectStyles.png" alt="CategoryObjectStyles" width="32"></td>
    <td>Category Object Styles</td>
    <td>Returns category object style attributes like Line-Color, Material…</td>
  </tr>
  <tr>
    <td width="48px"><img src="GH/CategorySubCategories.png" alt="CategorySubCategories" width="32"></td>
    <td>Category SubCategories</td>
    <td>Returns a list of all the subcategories of Category</td>
  </tr>
  <tr>
    <td><img src="GH/CategoryTypes.png" alt="ColumnByCurve" width="32"></td>
    <td>Category Types</td>
    <td>A pick list of category types in Revit.</td>
  </tr>
  <tr>
    <td><img src="GH/DirectShapeCategories.png" alt="DirectShapeCategories" width="32"></td>
    <td>DirectShape Category Selector</td>
    <td>Select a category for using with the DirectShape Component</td>
  </tr>
</table>

#### Datum Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/GridByCurve.png" alt="GridByCurve" width="32"></td>
    <td>Add Grid by Curve</td>
    <td>Add a Revit Grid line through a Rhino curve.</td>
  </tr>
  <tr>
    <td><img src="GH/LevelByElevation.png" alt="LevelByElevation" width="32"></td>
    <td>Add Level by Elevation</td>
    <td>Add level by supplying an elevation height.</td>
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
    <td>Decompose an Element into it's associated data including Constraints, Dimensions, Identity Data, Category, Family, Type, ID, etc... Once the Elemnt is wired into this component, <code>Shift</code> double-click on the component to exapand to all Parameters of that component.  <code>Ctrl</code> double-click on the component then to collapse down to only used outputs.</td>
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
    <td><img src="GH/ElementDelete.png" alt="DeleteElement" width="32"></td>
    <td>Element Delete</td>
    <td>Deletes the specified element out of Revit.</td>
  </tr>
</table>

#### Family Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/FamilyGetType.png" alt="FamilyGetType" width="32"></td>
    <td>Family Get Type</td>
    <td>Obtains a set of types that are owned by Family</td>
  </tr>
  <tr>
    <td><img src="GH/FamilyLoad.png" alt="FamilyLoad" width="32"></td>
    <td>Load Family</td>
    <td>Loads a family into the document using optional overrides</td>
  </tr>
  <tr>
    <td><img src="GH/FamilyNew.png" alt="FamilyNew" width="32"></td>
    <td>Load Family</td>
    <td>Creates a new Family from a template including optional overrides</td>
  </tr>
  <tr>
    <td><img src="GH/FamilySaveAs.png" alt="FamilySaveAs" width="32"></td>
    <td>Family Save As...</td>
    <td>Saves the Family to a given file path.</td>
  </tr>
  <tr>
    <td><img src="GH/AddFamilyElementByBrep.png" alt="AddFamilyElementByBrep" width="32"></td>
    <td>Add Family By Brep</td>
    <td>Add a family using a Brep.</td>
  </tr>
  <tr>
    <td><img src="GH/AddFamilyElementByCurve.png" alt="AddFamilyElementByCurve" width="32"></td>
    <td>Add Family by Curve</td>
    <td>Add a family using curve objects.</td>
  </tr>
  <tr>
      <td><img src="GH/VisibilityConstruct.png" alt="VisibilityConstruct" width="32"></td>
      <td>Visibility Construct</td>
      <td>Create a View Construct for a Family.</td>
  </tr>
</table>


#### Filter Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/ElementExclusionFilter.png" alt="ElementExclusionFilter" width="32"></td>
    <td>Element Exclusion Filter</td>
    <td>Filter used to exclude a set of elements.</td>
  </tr>
  <tr>
    <td><img src="GH/ElementLogicalOrFilter.png" alt="ElementLogicalOrFilter" width="32"></td>
    <td>Element Logical Or Filter</td>
    <td>Filter used to combine a set of filters that pass when any pass</td>
  </tr>
  <tr>
    <td><img src="GH/ElementLogicalAndFilter.png" alt="ElementLogicalAndFilter.png" width="32"></td>
    <td>Element Logical And Filter.png</td>
    <td>Filter used to combine a set of filters that pass when any pass</td>
  </tr>
  <tr>
    <td><img src="GH/ElementCategoryFilter.png" alt="ElementCategoryFilter" width="32"></td>
    <td>Element Category Filter</td>
    <td>Filter used to match elements by their category</td>
  </tr>
  <tr>
    <td><img src="GH/ElementExcludeElementType.png" alt="ElementExcludeElementType" width="32"></td>
    <td>Element Exclude Element Type</td>
    <td>Filter used to exclude element types</td>
  </tr>
  <tr>
      <td><img src="GH/ElementClassFilter.png" alt="EElementClassFilter" width="32"></td>
      <td>Element Class Filter</td>
      <td>Filter used to match elements by their API class</td>
  </tr>
  <tr>
      <td><img src="GH/ElementTypeFilter.png" alt="ElementTypeFilter" width="32"></td>
      <td>Element Type Filter</td>
      <td>Filter used to match elements by their type</td>
  </tr>
  <tr>
      <td><img src="GH/ElementBoundingBoxFilter.png" alt="lementBoundingBoxFilter" width="32"></td>
      <td>Element Bounding Box Filter</td>
      <td>Filter used to match elements by their position and interesction with a bounding area.</td>
  </tr>
  <tr>
      <td><img src="GH/ElementIntersectsElementFilter.png" alt="ElementIntersectsElementFilter" width="32"></td>
      <td>Element Intersects Elements Filter</td>
      <td>Filter used to match elements that intersect to the given element</td>
  </tr>
  <tr>
      <td><img src="GH/ElementIntersectsBrepFilter.png" alt="ElementIntersectsBrepFilter" width="32"></td>
      <td>Element Intersects Brep Filter</td>
      <td>Filter used to match elements that intersect to the given brep</td>
  </tr>
  <tr>
      <td><img src="GH/ElementIntersectsMeshFilter.png" alt="ElementIntersectsMeshFilter" width="32"></td>
      <td>Element Intersects Mesh Filter</td>
      <td>Filter used to match elements that intersect to the given mesh</td>
  </tr>
  <tr>
      <td><img src="GH/ElementDesignOptionFilter.png" alt="ElementDesignOptionFilter" width="32"></td>
      <td>Element Design Option Filter</td>
      <td>Filter used to match elements associated to the given Design Option</td>
  </tr>
  <tr>
      <td><img src="GH/ElementOwnerViewFilter.png" alt="ElementOwnerViewFilter" width="32"></td>
      <td>Element Owner View Filter</td>
      <td>Filter used to match elements associated to the given View</td>
  </tr>
  <tr>
      <td><img src="GH/ElementLevelFilter.png" alt="ElementLevelFilter" width="32"></td>
      <td>Element Level Filter</td>
      <td>Filter used to match elements associated to the given level</td>
  </tr>
  <tr>
      <td><img src="GH/ElementSelectableViewFilter.png" alt="ElementSelectableViewFilter" width="32"></td>
      <td>Element Selectable View Filter</td>
      <td>Filter used to match seletable elements into the given View</td>
  </tr>
  <tr>
      <td><img src="GH/ElementParameterFilter.png" alt="ElementParameterFilter" width="32"></td>
      <td>Element Parameter Filter</td>
      <td>Filter used to match elements by the value of a parameter</td>
  </tr>
  <tr>
      <td><img src="GH/ElementRuleEquals.png" alt="ElementRuleEquals" width="32"></td>
      <td>Element Rule Equals</td>
      <td>Filter used to match elements if value of a parameter equals to Value</td>
  </tr>
  <tr>
      <td><img src="GH/ElementRuleGreater.png" alt="ElementRuleGreater" width="32"></td>
      <td>Element Rule Greater</td>
      <td>Filter used to match elements if value of a parameter greater than Value</td>
  </tr>
  <tr>
      <td><img src="GH/ElementRuleGreaterOrEqual.png" alt="ElementRuleGreaterOrEqual" width="32"></td>
      <td>Element Rule Greater Or Equal</td>
      <td>Filter used to match elements if value of a parameter greater or equal than Value</td>
  </tr>
  <tr>
      <td><img src="GH/ElementRuleLess.png" alt="ElementRuleLess" width="32"></td>
      <td>Element Rule Less</td>
      <td>Filter used to match elements if value of a parameter less than Value</td>
  </tr>
  <tr>
      <td><img src="GH/ElementRuleLessOrEqual.png" alt="ElementRuleLessOrEqual" width="32"></td>
      <td>Element Rule Less Or Equal</td>
      <td>Filter used to match elements if value of a parameter less or equal than Value</td>
  </tr>
  <tr>
      <td><img src="GH/ElementRuleNotEquals.png" alt="ElementRuleNotEquals" width="32"></td>
      <td>Element Rule Not Equals</td>
      <td>Filter used to match elements if value of a parameter less than Value</td>    </tr>
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
      <td><img src="GH/DirectShapeByGeometry.png" alt="AddDirectShapeByGeometry" width="32"></td>    <td>Add DirectShape Geometry</td>    <td>Create a Directshape Element from a Rhino Geometry. This is the most flexible way to import Geometry.</td>  
    </tr>
</table>

#### Host Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/HostObjectGetFaces.png" alt="HostObjectGetFaces" width="32"></td>
    <td>Host Object Get Faces</td>
    <td>Obtains a set of types that are owned by Family.</td>
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
    <td>Select an Element Type by Name</td>
    <td>Select a specific Element type by its name. This component will be blank unless connected in combination with the Select Document Category or the Select a Family component to select a specific element within a Family or Category. Use a checklist, dropdown, scroll sequence or cycle interface to select a Element Type from Revit <img src="images/element-select-alpha.png" alt="ColumnByCurve"></td>
  </tr>
  <tr>
      <td><img src="GH/ModelCategoriesPicker.png" alt="ModelCategoriesPicker" width="32"></td>
      <td>Select a Model Category</td>
      <td>Use a checklist, dropdown, scroll sequence or cycle interface to select a model category from Revit</td>
  </tr>
  <tr>
      <td><img src="GH/AnnotationCategoriesPicker.png" alt="AnnotationCategoriesPicker" width="32"></td>
      <td>Select an Annotation Category</td>
      <td>Use a checklist, dropdown, scroll sequence or cycle interface to select an annotation category from Revit</td>
  </tr>
    <tr>
        <td><img src="GH/AnalyticalCategoriesPicker.png" alt="AnalyticalCategoriesPicker" width="32"></td>
        <td>Select a Analytical Category</td>
        <td>Use a checklist, dropdown, scroll sequence or cycle interface to select an analytical category from Revit</td>
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

#### Type Components

<table style="width:100%">
  <tr>
    <th width="48px">Icon</th>
    <th width="200">Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td width="48px"><img src="GH/ElementTypeDuplicate.png" alt="ElementTypeDuplicate" width="32"></td>
    <td>Duplicate an Element Type.</td>
    <td>Given a Name, it duplicates an ElementType into the active Revit document</td>
  </tr>
  <tr>
    <td><img src="GH/ElementTypeIdentity.png" alt="ElementTypeIdentity" width="32"></td>
    <td>Get the Element Type Identification</td>
    <td>Query type identity information to return Category, Family Name, Name and UUID.</td>
  </tr>
  <tr>
    <td><img src="GH/ElementTypeSimiliar.png" alt="ElementTypeSimiliar" width="32"></td>
    <td>Select Similiar Types</td>
      <td> Selects the types that are Similiar to the input Type.</td>
    </tr>
  <tr>
    <td><img src="GH/AddDirectShapeByType.png" alt="AddDirectShapeType" width="32"></td>
    <td>Create a DirectShape Type</td>
    <td>Given its Geometry, it reconstructs a DirectShapeType to the active Revit document
</td>
  </tr>
</table>

