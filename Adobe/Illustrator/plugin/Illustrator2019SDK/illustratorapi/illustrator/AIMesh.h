#ifndef __AIMesh__
#define __AIMesh__

/*
 *        Name:	AIMesh.h
 *   $Revision: 27 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Mesh Object Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file
 * in accordance with the terms of the Adobe license agreement
 * accompanying it. If you have received this file from a source other
 * than Adobe, then your use, modification, or distribution of it
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIHitTest__
#include "AIHitTest.h"
#endif

#ifndef __AIRealBezier__
#include "AIRealBezier.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIMesh.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIMeshSuite							"AI Mesh Suite"
#define kAIMeshSuiteVersion6					AIAPI_VERSION(6)
#define kAIMeshSuiteVersion						kAIMeshSuiteVersion6
#define kAIMeshVersion							kAIMeshSuiteVersion

#define kAIMeshHitSuite							"AI Mesh Hit Suite"
#define kAIMeshHitSuiteVersion3					AIAPI_VERSION(3)
#define kAIMeshHitSuiteVersion					kAIMeshHitSuiteVersion3
#define kAIMeshHitVersion						kAIMeshHitSuiteVersion

#define kAIMeshSelectionSuite					"AI Mesh Selection Suite"
#define kAIMeshSelectionSuiteVersion3			AIAPI_VERSION(3)
#define kAIMeshSelectionSuiteVersion			kAIMeshSelectionSuiteVersion3
#define kAIMeshSelectionVersion					kAIMeshSelectionSuiteVersion

#define kAIMeshPatchIteratorSuite				"AI Mesh Patch Suite"
#define kAIMeshPatchIteratorSuiteVersion3		AIAPI_VERSION(3)
#define kAIMeshPatchIteratorSuiteVersion		kAIMeshPatchIteratorSuiteVersion3
#define kAIMeshPatchIteratorVersion				kAIMeshPatchIteratorSuiteVersion

#define kAIMeshVertexIteratorSuite				"AI Mesh Vertex Suite"
#define kAIMeshVertexIteratorSuiteVersion4		AIAPI_VERSION(4)
#define kAIMeshVertexIteratorSuiteVersion		kAIMeshVertexIteratorSuiteVersion4
#define kAIMeshVertexIteratorVersion			kAIMeshVertexIteratorSuiteVersion

#define kAIMeshSegmentIteratorSuite				"AI Mesh Segment Suite"
#define kAIMeshSegmentIteratorSuiteVersion3		AIAPI_VERSION(3)
#define kAIMeshSegmentIteratorSuiteVersion		kAIMeshSegmentIteratorSuiteVersion3
#define kAIMeshSegmentIteratorVersion			kAIMeshSegmentIteratorSuiteVersion


/** Kinds of gradient mesh */
enum AIMeshKind {
	/** Cartesian mesh */
	kAICartesianMesh				= 0,
	/** Not implemented */
	kAIPolarMesh					= 1
};

/** Node axes */
enum AIMeshAxis {
	/** The I axis, containing integer values of nodes in a mesh. */
	kAIMeshIAxis					= 0,
	/** The J axis, containing integer values of nodes in a mesh. */
	kAIMeshJAxis					= 1
};

/** Directions along axes */
enum AIMeshAxisSense {
	kAIMeshAxisIncreasing			= 0,
	kAIMeshAxisDecreasing			= 1
};

/** Directions around patches */
enum AIMeshPatchDirection {
	kAIMeshClockwise				= 0,
	kAIMeshCounterClockwise			= 1
};

/** Parts of a mesh that can be hit */
enum AIMeshPart {
	kAIMeshNowhere					= 0,
	kAIMeshVertex					= 1,
	kAIMeshTangent					= 2,
	kAIMeshEdge						= 3,
	kAIMeshPatch					= 4
};

/** Variants for selection bounds */
enum AIMeshSelectionBoundsVariant {
	/** Computes a bounding box of the parts of the mesh that transform rigidly when
		a selection is transformed. Excludes from the bounds those segments that are
		attached to a pair of vertices where one transforms and the other
		remains fixed. */
	kAIMeshSelectionRigidBounds		= 0
};


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference to a mesh selection. See \c #AIMeshSelectionSuite */
typedef struct _AIMeshSelection			*AIMeshSelection;
/** Opaque reference to a mesh patch iterator. See \c #AIMeshPatchIteratorSuite */
typedef struct _AIMeshPatchIterator		*AIMeshPatchIterator;
/** Opaque reference to a mesh vertex iterator. See \c #AIMeshVertexIteratorSuite */
typedef struct _AIMeshVertexIterator	*AIMeshVertexIterator;
/** Opaque reference to a mesh segment iterator. See \c #AIMeshSegmentIteratorSuite */
typedef struct _AIMeshSegmentIterator	*AIMeshSegmentIterator;


/** Transformation function prototype for \c #AIMeshSuite::MapPoints()
	and \c #AIMeshSelectionSuite::MapPoints()
	The function is assumed to have a continuous first derivative.
		@param point The point to be transformed.
		@param userData Developer-defined data passed through from the calling function.
	*/
typedef void (*AIMeshPointMap) (AIRealPoint* point, void* userData);
/** Transformation function prototype for \c #AIMeshSuite::MapColors()
	and \c #AIMeshSelectionSuite::MapColors().
		@param color The color to be transformed.
		@param userData Developer-defined data passed through from the calling function.
	*/
typedef void (*AIMeshColorMap) (AIColor* color, void* userData);

/** Color-query function prototype for \c #AIMeshSuite::QueryColors()
	and \c #AIMeshSelectionSuite::QueryColors().
		@param color The color to be queried.
		@param userData Developer-defined data passed through from the calling function.
	*/
typedef void (*AIMeshColorQuery) (AIColor* color, void* userData);


/*******************************************************************************
 **
 **	Suite
 **
 **/


/**	@ingroup Suites
	This suite and related suites provides functions for creating and
	managing \e mesh objects, which are art object of type \c #kMeshArt.
	A mesh object represents a grid that can be used to apply colors to art,
	or to deform art in an \e envelope; see the \c #AIEnvelopeSuite.

	This suite provides functions for manipulating a mesh as a whole.

	\li Additional suites allow you to traverse and manipulate
		the elements  of a mesh (patches, vertices and segments).
		See @ref meshIterators.
	\li Different sets of elements in a mesh can be selected. The selection
		is represented by a mesh selection object. The \c #AIMeshSelectionSuite
		allows you to manipulate selections	for a mesh.
	\li The \c #AIMeshHitSuite provides functions that operate on the results
		 of hit testing for meshes (see \c #AIHitTestSuite).

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMeshSuite and \c #kAIMeshVersion.

	@section meshTerms Mesh Terminology

	A mesh can be considered an array of patches, where	each patch has
	four sides which it shares with	its neighbors.  The corners of
	a patch are nodes to which color is applied. The colors of the
	corners then blend across the interior of the patch.

	The patches are defined by cubic bezier curves, joined together
 	to form the mesh. The point at which two or more beziers meet is
	called a \e knot. To reduce the visual complexity, only a subset
	of the knots are visible when a mesh is displayed. A visible knot
	is called a \e vertex. The sequence of beziers between two
	vertices is called a \e segment.

	Just as for the beziers describing a path, a user can adjust
	the shape of the curve between two vertices. The points that
	manipulate the shape are called \e controls. Unlike a path,
	the curve might not be a single bezier, so the controls might
	not be coincident with the points of the bezier	control polygon.

	A coordinate system can be imposed on a mesh. For an M by N patch
	mesh, the coordinates range from [0..M] and [0..N]. Integer values
	of the coordinates refer to nodes. Non-integer values refer
	to points in the interior or on the sides of patches. When using
	strictly integer values, the axes are called the I and J axes.
	When using real values, they are called the U and V axes.

	When traversing a mesh, a direction along the axes can be increasing
	or decreasing; this kind of direction is called the \e sense.
	A direction around a patch can be clockwise or
	counterclockwise. The term \e direction is reserved for this usage.

	For example, for the node at (2,2):

	\li (3,1) is the next node increasing along the I axis.
	\li (2,1) is the next node decreasing along the J axis.
	\li (1,2) is the next node counterclockwise around patch (1,1).
	\li (2,1) is the next node clockwise around patch (1,1).

	\section meshIterators Mesh Iterators

	Iterator objects allow you to traverse and manipulate the
	elements of a mesh. There are different iterators for each of
	the types of elements; patches, vertices and segments. There is
	a suite of functions for each type of iterator, the \c #AIMeshPatchIteratorSuite,
	the \c #AIMeshVertexIteratorSuite, and the \c #AIMeshSegmentIteratorSuite.

	Iterator objects are reference counted. The initial reference
	count is one, and you do not typically need to increment it.
	You must, however, use the appropriate \c Release() function
	to decrement the count when you no longer need the object.
	Failure to do so causes memory leaks.

	Each type of iterator has an \c AtEnd method, which
	returns true when an iterator has walked off the mesh.
	After the end, the iterator cannot be reversed; that is you can
	no longer get the previous element.

	An iterator has a set of \c Next and \c Prev methods for
	iteration.

	\li The simple \c Next and \c Prev methods are used with
		iterators obtained from a \c GetStart method. Repeated
		calls to \c Next guarantee that every element is visited
	 	once and only once. The order of traversal is undefined.
	\li The methods \c NextI, \c PrevI, \c NextJ, \c PrevJ are for
		traversing the elements along a given axis.
	\li A segment iterator has an axis and direction, determined by
		the start vertex and end vertex. The \c NextOnPatch and
		\c PrevOnPatch methods for segment iterators
		differ from \c NextOnAxis and \c PrevOnAxis only when they
		encounter a corner of a patch. In this case, they switch to a new
		axis by making a half turn either clockwise or counter clockwise.
*/
typedef struct {

	/** Sets the dimensions of a mesh object.
		The geometric and color data is set to default values.
			@param mesh The mesh object.
			@param i The number of patches along the I axis.
			@param j The number of patches along the J axis.
	  */
	AIAPI AIErr (*InitCartesian) (AIArtHandle mesh, ai::int32 i, ai::int32 j);

	/** Not implemented. */
	AIAPI AIErr (*InitPolar) (AIArtHandle mesh, ai::int32 i, ai::int32 j);

	/** Retrieves the type of the mesh. (Only cartesian meshes are implemented.)
			@param mesh The mesh object.
			@param kind [out] A buffer in which to return the type, a  #AIMeshKind value.
		*/
	AIAPI AIErr (*GetKind) (AIArtHandle mesh, ai::int32 *kind);

	/** Retrieves the size of a mesh (number of patches).
			@param mesh The mesh object.
			@param i [out] A buffer in which to return the number of patches along the I axis.
			@param j [out] A buffer in which to return the number of patches along the J axis.
		*/
	AIAPI AIErr (*GetSize) (AIArtHandle mesh, ai::int32 *i, ai::int32 *j);

	/** Creates a new selection object for a mesh. Use the \c #AIMeshSelectionSuite
		to query and manipulate the selection.
			@param mesh The mesh object.
			@param all When true, include all vertices and segments of the mesh
				in the selection. When false, create an empty selection.
			@param selection [out] A buffer in which to return the selection.
			@see \c #GetSelection()
		*/
	AIAPI AIErr (*NewSelection) (AIArtHandle mesh, AIBoolean all, AIMeshSelection* selection);

	/** Retrieves the visible selection for a mesh; see \c #AIMeshSelectionSuite.
		Changing the returned selection changes what the user sees.
			@param mesh The mesh object.
			@param selection [out] A buffer in which to return the selection.
		*/
	AIAPI AIErr (*GetSelection) (AIArtHandle mesh, AIMeshSelection* selection);

	/** Creates a patch iterator a given patch in a mesh.
			@param mesh The mesh object.
			@param i The 0-based I-axis index of the patch.
			@param j The 0-based J-axis index of the patch.
			@param patch [out] A buffer in which to return the patch iterator.
		*/
	AIAPI AIErr (*GetPatch) (AIArtHandle mesh, ai::int32 i, ai::int32 j, AIMeshPatchIterator* patch);

	/** Creates a patch iterator for which calling \c #AIMeshPatchIteratorSuite::Next()
		repeatedly is guaranteed to visit all patches.
			@param mesh The mesh object.
			@param patch [out] A buffer in which to return the patch iterator.
		*/
	AIAPI AIErr (*GetStartPatch) (AIArtHandle mesh, AIMeshPatchIterator* patch);

	/** Creates a vertex iterator for a given node in a mesh.
			@param mesh The mesh object.
			@param i The 0-based I-axis index of the node.
			@param j The 0-based J-axis index of the node.
			@param vertex [out] A buffer in which to return the vertex iterator.
	    */
	AIAPI AIErr (*GetNode) (AIArtHandle mesh, ai::int32 i, ai::int32 j, AIMeshVertexIterator* vertex);

	/** Creates a vertex iterator for which calling \c #AIMeshVertexIteratorSuite::Next()
		repeatedly is guaranteed to visit all vertices.
			@param mesh The mesh object.
			@param vertex [out] A buffer in which to return the vertex iterator.
		*/
	AIAPI AIErr (*GetStartVertex) (AIArtHandle mesh, AIMeshVertexIterator* vertex);

	/** Creates a segment iterator for which calling \c #AIMeshSegmentIteratorSuite::Next()
		repeatedly is guaranteed to visit all segments.
			@param mesh The mesh object.
			@param segment [out] A buffer in which to return the segment iterator.
		*/
	AIAPI AIErr (*GetStartSegment) (AIArtHandle mesh, AIMeshSegmentIterator* segment);

	/** Retrieves the color space used to render a mesh.
		The colors of the nodes of the mesh can be drawn from different
		color spaces, which are converted to a single color space for
		rendering.
		(Note that this function does not return an error code.)
			@param mesh The mesh object.
			@param kind [out] A buffer in which to return the color type.
			@param custom [out] A buffer in which to return the custom color,
				if \c kind is \c #kCustomColor.
		*/
	AIAPI void (*GetColorSpace) (AIArtHandle mesh, AIColorTag* kind, AICustomColorHandle* custom);

	/** Converts a point in artwork coordinates to the (u,v) coordinates of
		that point within a mesh.
	    (Note that this function returns a boolean value, not an error code.)
			@param mesh The mesh object.
			@param point The pointer to the point in artwork coordinates.
			@param u [out] A buffer in which to return the U coordinate of the converted point.
			@param v [out] A buffer in which to return the V coordinate of the converted point.
			@return True if the point lies inside the mesh (the \c u and \c v values are defined),
				false if it lies outside the mesh (the \c u and \c v values are not defined).

	    */
	AIAPI AIBoolean (*InvertPoint) (AIArtHandle mesh, AIRealPoint* point, AIReal* u, AIReal* v);

	/** Converts a point in the (u,v) coordinates of a mesh to artwork coordinates.
		(Note that this function does not return an error code.)
			@param mesh The mesh object.
			@param u  The U coordinate of the point.
			@param v The V coordinate of the point.
			@param point [out] A buffer in which to return the converted point in artwork coordinates.
		*/
	AIAPI void (*EvalPoint) (AIArtHandle mesh, AIReal u, AIReal v, AIRealPoint* point);

	/** Retrieves the color of a mesh at a given point.
		(Note that this function does not return an error code.)
			@param mesh The mesh object.
			@param u  The U coordinate of the point.
			@param v The V coordinate of the point.
			@param color [out] A buffer in which to return the color.
	*/
	AIAPI void (*EvalColor) (AIArtHandle mesh, AIReal u, AIReal v, AIColor* color);

	/** Retrieves the opacity of a mesh at a given point.
		(Note that this function does not return an error code.)
			@param mesh The mesh object.
			@param u  The U coordinate of the point.
			@param v The V coordinate of the point.
			@param opacity [out] A buffer in which to return the color.
	*/
	AIAPI void (*EvalOpacity) (AIArtHandle mesh, AIReal u, AIReal v, AIReal* opacity);

	/** Transforms the points of a mesh by a transformation matrix.
			@param mesh The mesh object.
			@param matrix A pointer to the transformation matrix.
		*/
	AIAPI AIErr (*Transform) (AIArtHandle mesh, AIRealMatrix* matrix);

	/** Transforms the points of a mesh according to a developer-defined
		mapping function.
			@param mesh The mesh object.
			@param f The point-mapping function.
			@param userData Developer-defined data to pass through to the function.
		 */
	AIAPI AIErr (*MapPoints) (AIArtHandle mesh, AIMeshPointMap f, void* userData);

	/** Transforms the colors of a gradient mesh according to a developer-defined
		mapping function.
			@param mesh The mesh object.
			@param f The color-mapping function.
			@param userData Developer-defined data to pass through to the function.
	 	*/
	AIAPI AIErr (*MapColors) (AIArtHandle mesh, AIMeshColorMap f, void* userData);

	/** Passes the colors of a gradient mesh to a developer-defined
		query function. Does not modify the mesh colors.
		(Note that this function does not return an error code.)
			@param mesh The mesh object.
			@param f The color-querying function.
			@param userData Developer-defined data to pass through to the function.
		*/
	AIAPI void (*QueryColors) (AIArtHandle mesh, AIMeshColorQuery f, void* userData);

	/** Splits a mesh at a point on the U axis and reports the index of the
		resulting grid line.
			@param mesh The mesh object.
			@param u The insertion point on the U axis.
			@param i [out] A buffer in which to return the 0-based index of the new grid line.
		*/
	AIAPI AIErr (*InsertU) (AIArtHandle mesh, AIReal u, ai::int32* i);

	/** Splits a mesh at a point on the V axis and reports the index of the
		resulting grid line.
			@param mesh The mesh object.
			@param v The insertion point on the V axis.
			@param i [out] A buffer in which to return the 0-based index of the new grid line.
		*/
	AIAPI AIErr (*InsertV) (AIArtHandle mesh, AIReal v, ai::int32* j);

	/** Removes those lines of a mesh grid passing through a
		(U,V) point. Drawn grid lines pass through integer values.
		If both U and V are integers, removes both a
		horizontal and a vertical grid line. If only one is an
		integer, removes only one line.
			@param mesh The mesh object.
			@param u The U-axis coordinate.
			@param v The V-axis coordinate.
		*/
	AIAPI AIErr (*DeleteGridLines) (AIArtHandle mesh, AIReal u, AIReal v);

	/** Starts tracking for mouse movement over a mesh.
		(Note that this function does not return an error code.)
			@note  For a tool that manipulates the control points
				of a mesh, call \c #TrackBegin() before moving the
				control points (in response to mouse-down, for example)
				and \c #TrackEnd() when  done (in response to mouse-up).
				This ensures that selection handles are redrawn
				during the operation--otherwise the control points are
				not visible as they are modified.
			@param mesh The mesh object.
		*/
	AIAPI void (*TrackBegin) (AIArtHandle mesh);

	/** Stops tracking for mouse movement over a mesh.
		(Note that this function does not return an error code.)
			@param mesh The mesh object.
			@see \c #TrackBegin()
		*/
	AIAPI void (*TrackEnd) (AIArtHandle mesh);

	/** Stops the recording of selection changes for a mesh in
		the Undo history. Use after a change to selection, so that
		subsequent changes to other properties can be undone without
		undoing the selection.
			@param mesh The mesh object.
			@see \c #AIUndoSuite::UndoChanges()
		*/
	AIAPI AIErr (*EndSelectionChanges) (void);

	/** Drops a color onto an element of a mesh, as if a
		user dragged the color from, for example, the Swatch
		palette.
			@param hit A hit object that identifies the part of
				mesh. See \c #AIHitTestSuite.
			@param color The color.
		*/
	AIAPI AIErr (*DropColor) (AIHitRef hit, const AIColor* color);

	/** Converts an I-axis integer coordinate in a mesh (in the range [0..numPatches])
		to the corresponding U-axis coordinate, in the range [0..1]. See @ref meshTerms.
			@param mesh The mesh object.
			@param i The I-axis coordinate.
			@param u [out] A buffer in which to return the U-axis coordinate.
		*/
	AIAPI AIErr (*GetRelativeU) (AIArtHandle mesh, ai::int32 i, AIReal* u);

	/** Converts a J-axis integer coordinate in a mesh (in the range [0..numPatches])
		to the corresponding V-axis coordinate in the range [0..1].	See @ref meshTerms.
 			@param mesh The mesh object.
 			@param j The J-axis coordinate.
 			@param v [out] A buffer in which to return the V-axis coordinate.
		*/
	AIAPI AIErr (*GetRelativeV) (AIArtHandle mesh, ai::int32 j, AIReal* v);

	/** Retrieves the overprint fill attribute from a mesh object.
		(Note that this function does not return an error code.)
			@param mesh The mesh object.
			@return True if overprint is on, false if it is off.
		*/
	AIAPI AIBoolean (*GetOverprint) (AIArtHandle mesh);

	/** Sets the overprint fill attribute for a mesh object.
			@param mesh The mesh object.
			@param overprint True to turn overprint on, false to turn it off.
		*/
	AIAPI AIErr (*SetOverprint) (AIArtHandle mesh, AIBoolean overprint);

} AIMeshSuite;


/** @ingroup Suites
	This suite provides functions that operate on hit objects obtained
	by \c #AIHitTestSuite functions, when the result of the test is a
	hit on a mesh object.
	They allow you to identify the part of the mesh object that was hit,
	and to change the selection or iterate through elements
	of the mesh based on hit results.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMeshHitSuite and \c #kAIMeshHitVersion.
	*/
typedef struct {

	/** Reports the element of a mesh that was hit.
		(Note that this function returns a constant value, not an error code.)
			@param hit The hit object.
			@return The element that was hit, an #AIMeshPart value.
		*/
	AIAPI ai::int32 (*GetPart) (AIHitRef hit);

	/** Retrieves the (u,v) coordinates of a hit on a mesh object.
		(Note that this function does not return an error code.)
			@param hit The hit object.
			@param u [out] A buffer in which to return the U-axis coordinate,
				in the range [0..M], where M is the number of horizontal patches.
			@param v [out] A buffer in which to return the V-axis coordinate,
				in the range [0..N], where N is the number of vertical patches.
			@see @ref meshTerms.
		*/
	AIAPI void (*GetUV) (AIHitRef hit, AIReal* u, AIReal* v);

	/** Constructs a new selection from a hit, which contains the element
		that was hit.
			@param hit The hit object.
			@param selection [out] A buffer in which to return the new selection object.
		*/
	AIAPI AIErr (*GetSelection) (AIHitRef hit, AIMeshSelection* selection);

	/** If a vertex or tangent was hit, creates an iterator for the vertex.
			@param hit The hit object.
			@param vertex [out] A buffer in which to return the iterator.
	*/
	AIAPI AIErr (*GetVertex) (AIHitRef hit, AIMeshVertexIterator* vertex);

	/** If a tangent was hit, retrieves the tangent index.
			@param hit The hit object.
			@param index [out] A buffer in which to return the 0-based index.
	*/
	AIAPI AIErr (*GetTangentIndex) (AIHitRef hit, ai::int32* index);

	/** If a segment was hit, creates an iterator for the segment.
			@param hit The hit object.
			@param segment [out] A buffer in which to return the iterator.
		*/
	AIAPI AIErr (*GetSegment) (AIHitRef hit, AIMeshSegmentIterator* segment);

	/** If a patch was hit, creates an iterator for the patch.
			@param hit The hit object.
			@param patch [out] A buffer in which to return the	iterator.
		*/
	AIAPI AIErr (*GetPatch) (AIHitRef hit, AIMeshPatchIterator* patch);

} AIMeshHitSuite;


/** @ingroup Suites
	This suite provides functions that allow you to create and manipulate mesh
	selections, which identify a subset of the vertices and segments
	of a mesh. You can create any number of selections for a mesh, using
	\c #AIMeshSuite::NewSelection().

	There is one special selection associated with a mesh object that
	identifies the subset of vertices and segments the user has selected.
	This is the \e visible selection. You can obtain this selection
	with \c #AIMeshSuite::GetSelection(). Making a change to the contents of this
	selection affects what is displayed as selected in the document window.

	Selections are reference counted. When you get a selection
	its initial reference count is 1, so you do not typically need
	to call \c #AddRef().You must call \c #Release() to decrement
	the count of a selection when you are no longer using it.
	Failure to release selections causes memory leaks.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMeshSelectionSuite and \c #kAIMeshSelectionVersion.
*/
typedef struct {

	/** Increments the reference count of a mesh selection.
		The initial reference count is 1, so you do not typically need
		to call this function.
		(Note that this function returns an numeric value, not an error code.)
			@param selection The selection.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*AddRef) (AIMeshSelection selection);

	/** Decrements the reference count of a mesh selection, and frees
		the associated memory when the count reaches 0.
		(Note that this function returns an numeric value, not an error code.)
			@param selection The selection.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) (AIMeshSelection selection);

	/** Copies the contents of a mesh selection into another, existing selection object.
			@param selection The destination selection object.
			@param from The source selection object.
		*/
	AIAPI AIErr (*Copy) (AIMeshSelection selection, AIMeshSelection from);

	/** Duplicates a mesh selection, creating a new selection object.
			@param selection The source selection object.
			@param clone [out] A buffer in which to return the new selection object.
		*/
	AIAPI AIErr (*Clone) (AIMeshSelection selection, AIMeshSelection* clone);

    /** Reports whether a mesh selection does not contain any vertices, segments or patches.
		(Note that this function returns a boolean value, not an error code.)
			@param selection The mesh selection object.
			@return True if the selection is empty.
    	*/
	AIAPI AIBoolean (*IsEmpty) (AIMeshSelection selection);

    /** Reports whether a mesh selection contains every vertex, segment, and patch.
		(Note that this function returns a boolean value, not an error code.)
			@param selection The mesh selection object.
			@return True if the selection is full.
		*/
	AIAPI AIBoolean (*IsFull) (AIMeshSelection selection);

    /** Reports whether two mesh selection objects reference the same selection set.
		(Note that this function returns a boolean value, not an error code.)
			@param selection1 The first mesh selection object.
			@param selection2 The second mesh selection object.
			@return True if the selections are equal.
    	*/
	AIAPI AIBoolean (*IsEqual) (AIMeshSelection selection1, AIMeshSelection selection2);

    /** Reports whether a mesh selection contains all of the objects that are in
    	another selection.
		(Note that this function returns a boolean value, not an error code.)
			@param selection1 The first mesh selection object.
			@param selection2 The second mesh selection object.
			@return True if the second selection is a subset of the first.
    	*/
	AIAPI AIBoolean (*Contains) (AIMeshSelection selection1, AIMeshSelection selection2);

     /** Reports whether a mesh selection contains a specific vertex.
 		(Note that this function returns a boolean value, not an error code.)
 			@param selection The mesh selection object.
 			@param vertex The vertex.
 			@return True if the vertex is in the selection.
    	*/
	AIAPI AIBoolean (*ContainsVertex) (AIMeshSelection selection, AIMeshVertexIterator vertex);

    /** Reports whether a mesh selection contains a specific segment.
 		(Note that this function returns a boolean value, not an error code.)
 			@param selection The mesh selection object.
 			@param segment The segment.
 			@return True if the segment is in the selection.
    	*/
	AIAPI AIBoolean (*ContainsSegment) (AIMeshSelection selection, AIMeshSegmentIterator segment);

	/** Reports whether the reshaping control of a segment would be
		visible in a selection.
 		(Note that this function returns a boolean value, not an error code.)
 			@param selection The mesh selection object.
 			@param segment The segment.
			@return True if the reshaping control would be visible.
		*/
	AIAPI AIBoolean (*RendersControl) (AIMeshSelection selection, AIMeshSegmentIterator segment);

	/** Modifies a selection to be the intersection of itself and another selection.
			@param selection1 The first mesh selection object, which is modified.
			@param selection2 The second mesh selection object.
		*/
	AIAPI AIErr (*Intersect) (AIMeshSelection selection1, AIMeshSelection selection2);

	/** Modifies a selection to be the union of itself and another selection.
			@param selection1 The first mesh selection object, which is modified..
			@param selection2 The second mesh selection object.
		 */
	AIAPI AIErr (*Union) (AIMeshSelection selection1, AIMeshSelection selection2);

	/** Modifies a selection to invert the selection state of parts identified
		by another selection.
			@param selection1 The first mesh selection object, which is modified.
			@param selection2 The second mesh selection object, which identifies the
				parts to toggle.
		 */
	AIAPI AIErr (*Invert) (AIMeshSelection selection1, AIMeshSelection selection2);

	/** Adds a patch to or removes it from a selection.
			@param selection The mesh selection object.
 			@param patch The patch.
			@param select True to add the patch to the selection, false to deselect it.
		*/
	AIAPI AIErr (*SelectPatch) (AIMeshSelection selection, AIMeshPatchIterator patch, AIBoolean select);

	/** Adds a vertex to or removes it from a selection.
			@param selection The mesh selection object.
 			@param vertex The vertex.
			@param select True to add the vertex to the selection, false to deselect it.
		 */
	AIAPI AIErr (*SelectVertex) (AIMeshSelection selection, AIMeshVertexIterator vertex, AIBoolean select);

	/** Adds a segment to or removes it from a selection.
			@param selection The mesh selection object.
 			@param segment The segment.
			@param select True to add the segment to the selection, false to deselect it.
		*/
	AIAPI AIErr (*SelectSegment) (AIMeshSelection selection, AIMeshSegmentIterator segment, AIBoolean select);

	/** Transforms the points of a mesh selection by a transformation matrix.
			@param selection The mesh selection object.
			@param matrix A pointer to the transformation matrix.
		 */
	AIAPI AIErr (*Transform) (AIMeshSelection selection, AIRealMatrix* matrix);

	/** Transforms the points of a mesh selection according to a developer-defined
		mapping function.
			@param selection The mesh selection object.
			@param f The point-mapping function.
			@param userData Developer-defined data to pass through to the function.
		  */
	AIAPI AIErr (*MapPoints) (AIMeshSelection selection, AIMeshPointMap f, void* userData);

	/** Transforms the colors of a gradient mesh selection according to a developer-defined
		mapping function.
			@param selection The mesh selection object.
			@param f The color-mapping function.
			@param userData Developer-defined data to pass through to the function.
	 	 */
	AIAPI AIErr (*MapColors) (AIMeshSelection selection, AIMeshColorMap f, void* userData);

	/** Passes the colors of a gradient mesh selection to a developer-defined
		query function. Does not modify the mesh colors.
		(Note that this function does not return an error code.)
			@param selection The mesh selection object.
			@param f The color-querying function.
			@param userData Developer-defined data to pass through to the function.
		 */
	AIAPI void (*QueryColors) (AIMeshSelection selection, AIMeshColorQuery f, void* userData);

	/** Computes the bounds of the selected pieces of a mesh.
		(Note that this function does not return an error code.)
			@param selection The mesh selection object.
			@param matrix A pointer to a transformation matrix to apply to the selection
				before calculating its bounds. If this argument is \c NULL the
				identity matrix will be used.
			@param variant How the bounds are computed, a
				\c #AIMeshSelectionBoundsVariant value.
			@param bounds [out] A buffer in which to return the bounding box.
		*/
	AIAPI void (*BoundPieces) (AIMeshSelection selection, AIRealMatrix* matrix, ai::int32 variant, AIRealRect* bounds);

} AIMeshSelectionSuite;


/**	@ingroup Suites
	This suite provides functions that allow you to traverse and manipulate
	the patches in a mesh through a reference-counted iterator object.

	See @ref meshIterators.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMeshPatchIteratorSuite and \c #kAIMeshPatchIteratorVersion.
*/
typedef struct {

	/** Increments the reference count of a patch iterator object.
		The initial reference count is 1, so you do not typically
		need to  call this function.
		(Note that this function returns a numeric value, not an error code.)
			@param patch  The iterator object.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*AddRef) (AIMeshPatchIterator patch);

	/** Decrements the reference count of a patch iterator object,
		and frees the associated memory when the count reaches 0.
		(Note that this function returns an numeric value, not an error code.)
			@param patch The iterator object.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) (AIMeshPatchIterator patch);

	/** Copies the contents of a patch iterator into another, existing iterator object.
 			@param patch The destination iterator object.
 			@param from The source iterator object.
 		*/
	AIAPI AIErr (*Copy) (AIMeshPatchIterator patch, AIMeshPatchIterator from);

	/** Duplicates a patch iterator, creating a new iterator object.
 			@param patch The source iterator object.
 			@param clone [out] A buffer in which to return the new iterator object.
 		*/
	AIAPI AIErr (*Clone) (AIMeshPatchIterator patch, AIMeshPatchIterator* clone);

    /** Reports whether two patch iterator objects reference the same patch.
		(Note that this function returns a boolean value, not an error code.)
			@param patch1 The first iterator object.
			@param patch2 The second iterator object.
			@return True if the iterators are equal.
    	*/
	AIAPI AIBoolean (*IsEqual) (AIMeshPatchIterator patch1, AIMeshPatchIterator patch2);

	/** Reports whether a patch iterator has reached the last patch.
		When this function returns true, the iterator no longer contains
		a valid patch, and can no longer be used with the iteration
		functions. Check this before calling \c #Next(), \c #Prev(), or
		related functions if there is a chance of walking off the end of the mesh.
		(Note that this function returns a boolean value, not an error code.)
			@param patch The iterator object.
			@return True when the iterator is past the last patch.
		*/
	AIAPI AIBoolean (*AtEnd) (AIMeshPatchIterator patch);

	/**	Advances a patch iterator, so that it contains the next patch in
		the mesh. Use with an iterator obtained from
		\c #AIMeshSuite::GetStartPatch().
		Repeated calls guarantee that every element is visited
	 	once and only once. The order of traversal is undefined.
		(Note that this function does not return an error code.)
			@param patch The iterator object.
			@see \c #Prev(), \c #AtEnd()
		*/
	AIAPI void (*Next) (AIMeshPatchIterator patch);

	/**	Backs up a patch iterator, so that it contains the previous patch in
		the mesh.
		(Note that this function does not return an error code.)
			@param patch The iterator object.
			@see \c #Next(), \c #AtEnd()
		*/
	AIAPI void (*Prev) (AIMeshPatchIterator patch);

	/**	Advances a patch iterator, so that it contains the next patch in
		the mesh, increasing along the I axis.
		(Note that this function does not return an error code.)
			@param patch The iterator object.
			@see \c #PrevI(), \c #AtEnd()
		*/
	AIAPI void (*NextI) (AIMeshPatchIterator patch);

	/**	Backs up a patch iterator, so that it contains the previous patch in
		the mesh, decreasing along the I axis.
		(Note that this function does not return an error code.)
			@param patch The iterator object.
			@see \c #NextI(), \c #AtEnd()
		*/
	AIAPI void (*PrevI) (AIMeshPatchIterator patch);

	/**	Advances a patch iterator, so that it contains the next patch in
		the mesh, increasing along the J axis.
		(Note that this function does not return an error code.)
			@param patch The iterator object.
			@see \c #PrevJ(), \c #AtEnd()
		*/
	AIAPI void (*NextJ) (AIMeshPatchIterator patch);

	/** Backs up a patch iterator, so that it contains the previous patch in
		the mesh, decreasing along the J axis.
		(Note that this function does not return an error code.)
			@param patch The iterator object.
			@see \c #NextJ(), \c #AtEnd()
		*/
	AIAPI void (*PrevJ) (AIMeshPatchIterator patch);

	/** Retrieves the number of nodes in a patch.
		(Note that this function returns a numeric value, not an error code.)
			@param patch The iterator object.
			@return The number of nodes (currently always 4).
		*/
	AIAPI ai::int32 (*CountNodes) (AIMeshPatchIterator patch);

	/** Creates a vertex iterator for a node of a patch, identified by index
		position. Nodes are numbered from 0 to 3, counter-clockwise	from
		the bottom left of the patch.
			@param patch The patch iterator object.
			@param n The 0-based index of the node.
			@param vertex [out] A buffer in which to return the new vertex iterator.
		*/
	AIAPI AIErr (*GetNodeN) (AIMeshPatchIterator patch, ai::int32 n, AIMeshVertexIterator* vertex);

	/** Creates a vertex iterator for a node of a patch, identified by an (I,J) offset
		relative to the bottom left node of the patch.
			@param patch The patch iterator object.
			@param i The I-axis offset of the node.
			@param J The J-axis offset of the node.
			@param vertex [out] A buffer in which to return the new vertex iterator.
		*/
	AIAPI AIErr (*GetNodeIJ) (AIMeshPatchIterator patch, ai::int32 i, ai::int32 j, AIMeshVertexIterator* vertex);

	/** Creates a segment iterator for one of the two segments adjacent to a patch and
		connected to a node specified by position index. The nodes are numbered from
		0 to 3 counter-clockwise from the bottom left of the patch.
			@param patch The patch iterator object.
			@param n The 0-based index of the node.
			@param direction Whether to make a clockwise or counter-clockwise
				turn at patch corners, an \c #AIMeshPatchDirection value.
				(This indicates which segment to get.)
			@param vertex [out] A buffer in which to return the new segment iterator.
		 */
	AIAPI AIErr (*GetSegmentN) (AIMeshPatchIterator patch, ai::int32 n, ai::int32 direction, AIMeshSegmentIterator* segment);

	/** Creates a segment iterator for one of the two segments adjacent to a patch and
		connected to a node specified by an (I,J) offset relative to the bottom left
		node of the patch.
			@param patch The patch iterator object.
			@param i The I-axis offset of the node.
			@param J The J-axis offset of the node.
			@param direction Whether to make a clockwise or counter-clockwise
				turn at patch corners, an \c #AIMeshPatchDirection value.
				(This indicates which segment to get.)
			@param segment [out] A buffer in which to return the new segment iterator.
		*/
	AIAPI AIErr (*GetSegmentIJ) (AIMeshPatchIterator patch, ai::int32 i, ai::int32 j, ai::int32 direction, AIMeshSegmentIterator* segment);

	/** Reports the number of vertices around a patch, including nodes.
		Use with \c #GetVertexM() and \c #GetSegmentM() to iterate through
		vertices and segments.
		(Note that this function returns a numeric value, not an error code.)
			@param patch The patch iterator object.
			@return The number of vertices.
		*/
	AIAPI ai::int32 (*CountVerticies) (AIMeshPatchIterator patch);

	/** Creates a vertex iterator for a vertex identified by index
		position in a patch.
			@param patch The patch iterator object.
			@param m The 0-based index of the vertex. Use \c #CountVerticies()
				to find the number of vertices in the patch.
			@param vertex [out] A buffer in which to return the new vertex iterator.
		 */
	AIAPI AIErr (*GetVertexM) (AIMeshPatchIterator patch, ai::int32 m, AIMeshVertexIterator* vertex);

	/** Creates a segment iterator for one of the two segments adjacent to a patch and
		connected to a vertex specified by position index.
			@param patch The patch iterator object.
			@param m The 0-based index of the vertex. Use \c #CountVerticies()
				to find the number of vertices in the patch.
			@param direction Whether to make a clockwise or counter-clockwise
				turn at patch corners, an \c #AIMeshPatchDirection value.
				(This indicates which segment to get.)
			@param segment [out] A buffer in which to return the new segment iterator.
		  */
	AIAPI AIErr (*GetSegmentM) (AIMeshPatchIterator patch, ai::int32 m, ai::int32 direction, AIMeshSegmentIterator* segment);

	/** Reports the ordinal position of a vertex around a patch.
			@param patch The patch iterator object.
			@param vertex The vertex iterator object.
			@param m [out] A buffer in which to return the vertex position.
		*/
	AIAPI AIErr (*FindVertex) (AIMeshPatchIterator patch, AIMeshVertexIterator vertex, ai::int32* m);

	/** Retrives the (i,j) coordinate of a patch within the mesh.
			@param patch The patch iterator object.
			@param i [out] A buffer in which to return the I-axis coordinate.
			@param j [out] A buffer in which to return the J-axis coordinate.
		*/
	AIAPI void (*GetIJ) (AIMeshPatchIterator patch, ai::int32* i, ai::int32* j);

} AIMeshPatchIteratorSuite;


/**	@ingroup Suites
	This suite provides functions that allow you to traverse and manipulate
	the vertices in a mesh through a reference-counted iterator object.
	The segments and tangents associated with a vertex are addressed by a
	0-based index.

	See @ref meshIterators.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMeshVertexIteratorSuite and \c #kAIMeshVertexIteratorVersion.
 */
typedef struct {
	/** Increments the reference count of a vertex iterator object.
		The initial reference count is 1, so you do not typically
		need to  call this function.
		(Note that this function returns a numeric value, not an error code.)
			@param vertex  The vertex iterator object.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*AddRef) (AIMeshVertexIterator vertex);

	/** Decrements the reference count of a vertex iterator object,
		and frees the associated memory when the count reaches 0.
		(Note that this function returns an numeric value, not an error code.)
			@param vertex The vertex iterator object.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) (AIMeshVertexIterator vertex);

	/** Copies the contents of a vertex iterator into another, existing iterator object.
 			@param vertex The destination iterator object.
 			@param from The source iterator object.
 		*/
	AIAPI AIErr (*Copy) (AIMeshVertexIterator vertex, AIMeshVertexIterator from);

	/** Duplicates a vertex iterator, creating a new iterator object.
 			@param vertex The source iterator object.
 			@param clone [out] A buffer in which to return the new iterator object.
 		*/
	AIAPI AIErr (*Clone) (AIMeshVertexIterator vertex, AIMeshVertexIterator* clone);

    /** Reports whether two vertex iterator objects reference the same vertex.
		(Note that this function returns a boolean value, not an error code.)
			@param vertex1 The first iterator object.
			@param vertex2 The second iterator object.
			@return True if the iterators are equal.
    	*/
	AIAPI AIBoolean (*IsEqual) (AIMeshVertexIterator vertex1, AIMeshVertexIterator vertex2);

	/** Reports whether a vertex iterator has reached the last vertex.
		When this function returns true, the iterator no longer contains
		a valid vertex, and can no longer be used with the iteration
		functions.  Check this before calling \c #Next(), \c #Prev(), or
		related functions if there is a chance of walking off the end of the mesh.
		(Note that this function returns a boolean value, not an error code.)
			@param vertex The vertex iterator object.
			@return True when the iterator is past the last vertex.
		*/
	AIAPI AIBoolean (*AtEnd) (AIMeshVertexIterator vertex);

	/**	Advances a vertex iterator, so that it contains the next
		vertex in the mesh. Use with an iterator obtained from
		\c #AIMeshSuite::GetStartVertex().
		Repeated calls guarantee that every element is visited
	 	once and only once. The order of traversal is undefined.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@see \c #Prev(), \c #AtEnd()
		*/
	AIAPI void (*Next) (AIMeshVertexIterator vertex);

	/**	Backs up a vertex iterator, so that it contains the previous
		vertex in the mesh.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@see \c #Next(), \c #AtEnd()
		*/
	AIAPI void (*Prev) (AIMeshVertexIterator vertex);

	/**	Advances a vertex iterator, so that it contains the next vertex in
		the mesh, increasing along the I axis.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@see \c #PrevI(), \c #AtEnd()
		*/
	AIAPI void (*NextI) (AIMeshVertexIterator vertex);

	/**	Backs up a vertex iterator, so that it contains the previous vertex in
		the mesh, decreasing along the I axis.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@see \c #NextI(), \c #AtEnd()
		*/
	AIAPI void (*PrevI) (AIMeshVertexIterator vertex);

	/**	Advances a vertex iterator, so that it contains the next vertex in
 		the mesh, increasing along the J axis.
 		(Note that this function does not return an error code.)
 			@param vertex The vertex iterator object.
 			@see \c #PrevJ(), \c #AtEnd()
 		*/
	AIAPI void (*NextJ) (AIMeshVertexIterator vertex);

	/** Backs up a vertex iterator, so that it contains the previous vertex in
		the mesh, decreasing along the J axis.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@see \c #NextJ(), \c #AtEnd()
		*/
	AIAPI void (*PrevJ) (AIMeshVertexIterator vertex);

	/** Reports the number of segments connected to a vertex.
		(Note that this function returns a numeric value, not an error code.)
			@param vertex The vertex iterator object.
			@return The number of connected segments.
		*/
	AIAPI ai::int32 (*CountSegments) (AIMeshVertexIterator vertex);

	/** Reports whether a vertex iterator identifies a node.
		(Note that this function returns a boolean value, not an error code.)
			@param vertex The vertex iterator object.
			@return True if the current vertex is a node.
		*/
	AIAPI AIBoolean (*IsNode) (AIMeshVertexIterator vertex);

	/** Retrieves the index position of a segment in a given
		direction from a connected vertex along a given axis.
		(Note that this function returns a numeric value, not an error code.)
			@param vertex The vertex iterator object.
			@param axis	The axis, an \c #AIMeshAxis value.
			@param sense The direction, an \c #AIMeshAxisSense value.
			@return The index position of the segment.
		*/
	AIAPI ai::int32 (*GetSegmentIndex) (AIMeshVertexIterator vertex, ai::int32 axis, ai::int32 sense);

	/** Retrieves the index position of the segment that is opposite a segment
		identified by index position around a connected vertex.
		(Note that this function returns a numeric value, not an error code.)
			@param vertex The vertex iterator object.
			@param i The index position of a segment connected to the vertex.
			@return The index of the opposite segment, or -1 if there is no opposite segment.
		*/
	AIAPI ai::int32 (*GetSegmentOpposite) (AIMeshVertexIterator vertex, ai::int32 i);

	/** Sets the color of a node.
			@param vertex The vertex iterator object, for which the current vertex is a node.
			@param c A pointer to the new color.
		*/
	AIAPI AIErr (*SetColor) (AIMeshVertexIterator vertex, AIColor* c);

	/** Retrieves the color of a node.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object, for which the current vertex is a node.
			@param c [out] A buffer in which to return the color.
		*/
	AIAPI void (*GetColor) (AIMeshVertexIterator vertex, AIColor* c);

	/** Sets the position of the ends of all segments attached to a vertex.
			@param vertex The vertex iterator object.
			@param point A pointer to the new endpoint.
		*/
	AIAPI AIErr (*SetPoint) (AIMeshVertexIterator vertex, AIRealPoint* point);

	/** Retrieves the position of the ends of all segments attached to a vertex.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@param point [out] A buffer in which to return the endpoint.
		*/
	AIAPI void (*GetPoint) (AIMeshVertexIterator vertex, AIRealPoint* point);

	/** Retrieves the (U,V) coordinates of a vertex.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@param u [out] A buffer in which to return the U coordinate.
			@param v [out] A buffer in which to return the V coordinate.
		*/
	AIAPI void (*GetUV) (AIMeshVertexIterator vertex, AIReal* u, AIReal* v);

	/** Sets the second point of the bezier control polygon of a segment identified
		by index position around a connected vertex.
			@param vertex The vertex iterator object.
			@param i The 0-based index of the segment.
			@param point A pointer to the new tangent point.
		*/
	AIAPI AIErr (*SetTangent) (AIMeshVertexIterator vertex, ai::int32 i, AIRealPoint* point);

	/** Retrieves the second point of the bezier control polygon of a segment identified
		by index position around a connected vertex.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object.
			@param i The 0-based index of the segment.
			@param point [out] A buffer in which to return the tangent point.
		*/
	AIAPI void (*GetTangent) (AIMeshVertexIterator vertex, ai::int32 i, AIRealPoint* point);

	/** Sets the smoothing state of a segment identified
		by index position around a connected vertex.  When smoothing is on,
		adjusting the tangent similarly adjusts that of the opposite segment.
			@param vertex The vertex iterator object.
			@param i The 0-based index of the segment.
			@param smooth True to turn smoothing on, false to turn it off.
		*/
	AIAPI AIErr (*SetSmooth) (AIMeshVertexIterator vertex, ai::int32 i, AIBoolean smooth);

	/** Retrieves the smoothing state of a segment identified
		by index position around a connected vertex. When smoothing is on,
		adjusting the tangent similarly adjusts that of the opposite segment.
		(Note that this function returns a boolean value, not an error code.)
			@param vertex The vertex iterator object.
			@param i The 0-based index of the segment.
			@return True if smoothing is on, false if it is off.
		*/
	AIAPI AIBoolean (*GetSmooth) (AIMeshVertexIterator vertex, ai::int32 i);

	/** Creates an iterator for a segment identified
		by index position around a connected vertex.
			@param vertex The vertex iterator object.
			@param i The 0-based index of the segment.
			@param segment [out] A buffer in which to return the segment iterator.
		*/
	AIAPI AIErr (*GetSegment) (AIMeshVertexIterator vertex, ai::int32 i, AIMeshSegmentIterator* segment);

	/** Creates an iterator for one of the patches adjacent to a segment identified
		by index position around a connected vertex.
			@param vertex The vertex iterator object.
			@param i The 0-based index of the segment.
			@param patch [out] A buffer in which to return the patch iterator.
		*/
	AIAPI AIErr (*GetPatch) (AIMeshVertexIterator vertex, ai::int32 i, AIMeshPatchIterator* patch);

	/** Reports whether a vertex is on the edge of the mesh.
		(Note that this function returns a boolean value, not an error code.)
			@param vertex The vertex iterator object.
			@return True if the vertex is on the edge.
		*/
	AIAPI AIBoolean (*IsOnBoundary) (AIMeshVertexIterator vertex);

	/** Sets the opacity of a node.
			@param vertex The vertex iterator object, for which the current vertex is a node.
			@param o The opacity value (between 0.0 and 1.0).
		*/
	AIAPI AIErr (*SetOpacity) (AIMeshVertexIterator vertex, AIReal o);

	/** Retrieves the opacity of a node.
		(Note that this function does not return an error code.)
			@param vertex The vertex iterator object, for which the current vertex is a node.
			@param o [out] A buffer in which to return the opacity.
	*/
	AIAPI void (*GetOpacity) (AIMeshVertexIterator vertex, AIReal* o);

} AIMeshVertexIteratorSuite;


/**	@ingroup Suites
	This suite provides functions that allow you to traverse and
	manipulate the segments in a mesh through a reference-counted
	iterator object.

	See @ref meshIterators.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMeshSegmentIteratorSuite and \c #kAIMeshSegmentIteratorVersion.
 */
typedef struct {

	/** Increments the reference count of a segment iterator object.
		The initial reference count is 1, so you do not typically
		need to  call this function.
		(Note that this function returns a numeric value, not an error code.)
			@param segment  The iterator object.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*AddRef) (AIMeshSegmentIterator segment);

	/** Decrements the reference count of a segment iterator object,
		and frees the associated memory when the count reaches 0.
		(Note that this function returns an numeric value, not an error code.)
			@param segment The iterator object.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) (AIMeshSegmentIterator segment);

	/** Copies the contents of a segment iterator into another, existing iterator object.
  			@param segment The destination iterator object.
  			@param from The source iterator object.
  		*/
	AIAPI AIErr (*Copy) (AIMeshSegmentIterator segment, AIMeshSegmentIterator from);

	/** Duplicates a segment iterator, creating a new iterator object.
 			@param segment The source iterator object.
 			@param clone [out] A buffer in which to return the new iterator object.
 		*/
	AIAPI AIErr (*Clone) (AIMeshSegmentIterator segment, AIMeshSegmentIterator* clone);

    /** Reports whether two segment iterator objects reference the same segment
    	and have the same direction.
		(Note that this function returns a boolean value, not an error code.)
			@param segment1 The first iterator object.
			@param segment2 The second iterator object.
			@return True if the iterators are equal.
    	*/
	AIAPI AIBoolean (*IsEqual) (AIMeshSegmentIterator segment1, AIMeshSegmentIterator segment2);

	/** Reports whether a segment iterator has reached the last segment.
		When this function returns true, the iterator no longer contains
		a valid segment, and can no longer be used with the iteration
		functions.  Check this before calling \c #Next(), \c #Prev(), or
		related functions if there is a chance of walking off the end of the mesh.
		(Note that this function returns a boolean value, not an error code.)
			@param segment The segment iterator object.
			@return True when the iterator is past the last segment.
		*/
	AIAPI AIBoolean (*AtEnd) (AIMeshSegmentIterator segment);

	/**	Advances a segment iterator, so that it contains the next
		segment in the mesh. Use with an iterator obtained from
		\c #AIMeshSuite::GetStartSegment().
		Repeated calls guarantee that every element is visited
	 	once and only once. The order of traversal is undefined.
		(Note that this function does not return an error code.)
			@param segment The segment iterator object.
			@see \c #Prev(), \c #AtEnd()
		*/
	AIAPI void (*Next) (AIMeshSegmentIterator segment);

	/**	Backs up a segment iterator, so that it contains the previous
		segment in the mesh.
		(Note that this function does not return an error code.)
			@param segment The segment iterator object.
			@see \c #Next(), \c #AtEnd()
		*/
	AIAPI void (*Prev) (AIMeshSegmentIterator segment);

	/**	Advances a segment iterator, so that it contains the next segment in
 		the mesh, increasing along the current axis in the direction of
		this iterator.
 		(Note that this function does not return an error code.)
 			@param segment The segment iterator object.
 			@see \c #PrevOnAxis(), \c #AtEnd()
 		*/
	AIAPI void (*NextOnAxis) (AIMeshSegmentIterator segment);

	/**	Backs up a segment iterator, so that it contains the previous segment in
 		the mesh, decreasing along the current axis in the direction of
		this iterator.
 		(Note that this function does not return an error code.)
 			@param segment The segment iterator object.
 			@see \c #NextOnAxis(), \c #AtEnd()
 		*/
	AIAPI void (*PrevOnAxis) (AIMeshSegmentIterator segment);

	/** Advances a segment iterator, so that it contains the next segment
		around the current patch.
			@param segment The segment iterator object.
			@param direction Whether to make a clockwise or counter-clockwise
				turn at patch corners, an \c #AIMeshPatchDirection value.
				(This indicates which patch to follow.)
 			@see \c #PrevOnPatch(), \c #AtEnd()
		*/
	AIAPI void (*NextOnPatch) (AIMeshSegmentIterator segment, ai::int32 direction);

	/** Backs up a segment iterator, so that it contains the previous segment
		around the current patch.
			@param segment The segment iterator object.
			@param direction Whether to make a clockwise or counter-clockwise
				turn at patch corners, an \c #AIMeshPatchDirection value.
				(This indicates which patch to follow.)
 			@see \c #PrevOnPatch(), \c #AtEnd()
		*/
	AIAPI void (*PrevOnPatch) (AIMeshSegmentIterator segment, ai::int32 direction);

	/** Switches the start and end vertices of a segment.
		(Note that this function does not return an error code.)
			@param segment The segment iterator object.
		*/
	AIAPI void (*Reverse) (AIMeshSegmentIterator segment);

	/** Reports the number of knots forming a segment, excluding the
		start and end knots.
		(Note that this function returns a numeric value, not an error code.)
			@param segment The segment iterator object.
			@return The number of knots.
		*/
	AIAPI ai::int32 (*CountKnots) (AIMeshSegmentIterator segment);

	/** Retrieves the (U,V) coordinates of a knot identified by position
		index in a segment.
		(Note that this function does not return an error code.)
			@param segment The segment iterator object.
			@param n The 0-based index of the knot. Index positions exclude the start
				and end knots.
			@param u [out] A buffer in which to return the U coordinate.
			@param v [out] A buffer in which to return the V coordinate.
		*/
	AIAPI void (*GetKnotUV) (AIMeshSegmentIterator segment, ai::int32 n, AIReal* u, AIReal* v);

	/** Adds one or more knots to a segment.
			@param segment The segment iterator object.
			@param m The 0-based index at which to add the knot or knots.
				Index positions exclude the start and end knots.
			@param n The number of knots to add.
		*/
	AIAPI AIErr (*InsertKnots) (AIMeshSegmentIterator segment, ai::int32 m, ai::int32 n);

	/** Removes one or more knots from a segment.
			@param segment The segment iterator object.
			@param m The 0-based index at which to remove the knot or knots.
				Index positions exclude the start and end knots.
			@param n The number of knots to remove.
		*/
	AIAPI AIErr (*DeleteKnots) (AIMeshSegmentIterator segment, ai::int32 m, ai::int32 n);

	/** Reports the number of points in the control polygon of the beziers
		describing a segment.
		(Note that this function returns a numeric value, not an error code.)
			@param segment The segment iterator object.
			@return The number of points.
		*/
	AIAPI ai::int32 (*CountPoints) (AIMeshSegmentIterator segment);

	/** Sets the position of the point of a bezier control polygon that describes a segment.
			@param segment The segment iterator object.
			@param i The 0-based index of the point. See \c #CountPoints().
			@param point A pointer to the new point value.
	*/
	AIAPI AIErr (*SetPoint) (AIMeshSegmentIterator segment, ai::int32 i, AIRealPoint* point);

	/** Retrieves the point of a bezier control polygon that describes a segment.
		(Note that this function does not return an error code.)
			@param segment The segment iterator object.
			@param i The 0-based index of the point. See \c #CountPoints().
			@param point [out] A buffer in which to return the point.
	*/
	AIAPI void (*GetPoint) (AIMeshSegmentIterator segment, ai::int32 i, AIRealPoint* point);

	/** Creates a vertex iterator for the starting vertex of a segment.
			@param segment The segment iterator object.
			@param vertex [out] A buffer in which to return the vertex iterator.
	*/
	AIAPI AIErr (*GetStart) (AIMeshSegmentIterator segment, AIMeshVertexIterator* vertex);

	/** Creates a vertex iterator for the ending vertex of a segment.
				@param segment The segment iterator object.
				@param vertex [out] A buffer in which to return the vertex iterator.
	*/
	AIAPI AIErr (*GetEnd) (AIMeshSegmentIterator segment, AIMeshVertexIterator* vertex);

	/** Breaks a segment into two segments at a given knot, so that the knot
		becomes a vertex.
			@param segment The segment iterator object. Upon return, this contains
				the initial segment of the two new segments.
			@param n The 0-based index of the knot.
		*/
	AIAPI AIErr (*Split) (AIMeshSegmentIterator segment, ai::int32 n);

	/** Joins a segment with the next segment.
			@param segment The segment iterator object. Upon return, this contains
				the joined segment.
			@param n [out]  A buffer in which to return the 0-based index of
				the knot at the join.
		*/
	AIAPI AIErr (*Join) (AIMeshSegmentIterator segment, ai::int32* n);

	/** Reports the location of the control handle at the segment start.
		which is used to  manipulate its overall shape.
		(Note that this function does not return an error code.)
			@param segment The segment iterator object.
			@param control [out]  A buffer in which to return the control-handle point.
		*/
	AIAPI void (*GetControl) (AIMeshSegmentIterator segment, AIRealPoint* control);

	/** Modifies the control polygon to reshape a segment.
			@param segment The segment iterator object.
			@param point The new position for the start of the segment.
			@param control The control handle of the segment. See \c #GetControl().
		*/
	AIAPI AIErr (*Reshape) (AIMeshSegmentIterator segment, AIRealPoint* point, AIRealPoint* control);

	/** Reports whether a segment is on the edge of the mesh.
		(Note that this function returns a boolean value, not an error code.)
			@param segment The segment iterator object.
			@return True when the segment is on the edge.
	*/
	AIAPI AIBoolean (*IsOnBoundary) (AIMeshSegmentIterator segment);

} AIMeshSegmentIteratorSuite;


#include "AIHeaderEnd.h"


#endif
