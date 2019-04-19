#ifndef __AIPerspectiveTransform__
#define __AIPerspectiveTransform__

/*
*		 Name:	AIPerspectiveTransform.h
*        Date:	Started 2009
*     Purpose:	Adobe Illustrator Perspective Transform suite. This suite lets
*				clients project/reverse project point/arts in the currently defined
*				perspective grid in the document.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2009 Adobe Systems Incorporated.
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

#include "AIHeaderBegin.h"

/** @file AIPerspectiveTransform.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIPerspectiveTransformSuite			"AI Perspective Transform Suite"
#define kAIPerspectiveTransformSuiteVersion		AIAPI_VERSION(3)
#define kAIPerspectiveTransformVersion			kAIPerspectiveTransformSuiteVersion

/*******************************************************************************
 **
 ** Types
 **
 **/

/** Type constants for perspective grid plane. */
enum GridPlaneType{
	kInvalidGridPlane = -2,		///< Invalid grid plane
	kCurrentlyActivePlane = -1,	///< Currently active grid plane
	kGridLeftPlane = 0,			///< Left plane
	kGridRightPlane,			///< Right plane
	kGridFloorPlane,			///< Floor plane
	kGridNoPlane				///< No active plane
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite allows you to project or reverse-project points and art objects
	using the currently defined perspective grid in the current document.
*/

typedef struct {

	/** Projects an art object into perspective, using the currently defined
		perspective grid in the current document.
	 	Breaks down the object into segments, and projects each of the points of
	 	each segment into perspective.
		(Note that this method returns a Boolean value, not an error code.)
			@param art [in, out] The art object, modified in place on success.
			@param activePlane The plane in which to project the art.
			@param planeOffset A pointer to the plane offset, or NULL to use the current plane offset.
			@return True on success.
	*/
	AIAPI AIBoolean		(*PutInPerspective) (AIArtHandle art, GridPlaneType activePlane, AIReal* planeOffset);

	/** Reverse-projects art from perspective. Replaces the passed object handle with
		the handle to the original art object that was projected into perspective.
		(Note that this method returns a Boolean value, not an error code.)
		@param art [in, out] The art object, modified in place on success.
		@return True on success.
	*/
	AIAPI AIBoolean		(*GetOriginalArt)(AIArtHandle art);

	/**	Reverse-projects a point from perspective.  Replaces the passed point with
		the original point on the canvas that was projected into perspective.
		(Note that this method returns a Boolean value, not an error code.)
			@param point [in, out] A buffer that supplies the original point, and that returns the modified point.
			@param activePlane The plane on which the point was projected.
			@param planeOffset A pointer to the plane offset, or NULL to use the current plane offset.
		    @return True on success.
	*/
	AIAPI AIBoolean		(*GetOriginalPoint) (AIRealPoint& point, GridPlaneType activePlane, AIReal* planeOffset);

	/**	Projects a point into perspective.  Replaces the passed point, which is assumed to be in
	    normal 2D space, with the point projected onto the given plane in the current perspective grid
	    of the current document.
		(Note that this method returns a Boolean value, not an error code.)
			@param point [in, out] A buffer that supplies the original point, and that returns the modified point.
			@param activePlane The plane onto which to project the point.
			@param planeOffset A pointer to the plane offset, or NULL to use the current plane offset.
		    @return True on success.
 	*/
	AIAPI AIBoolean		(*GetPerspectivePoint) (AIRealPoint& point, GridPlaneType activePlane, AIReal* planeOffset);

	/**	Transforms art into perspective on the current perspective grid
	    of the current document, using the supplied transformation matrix.
		(Note that this method returns a Boolean value, not an error code.)
			@param art The art object.
			@param transform The transformation matrix to be applied to the original dimensions of the art.
			@return True on success.
	*/
	AIAPI AIBoolean		(*ApplyTransformInPerspective) (AIArtHandle art, AIRealMatrix transform);

	/**	Reports whether art is currently in perspective.
		(Note that this method returns a Boolean value, not an error code.)
			@param art  The art object.
			@return True if the art is in perspective.
	*/
	AIAPI AIBoolean		(*IsArtInPerspective) (AIArtHandle art);

	/**	Releases art from the perspective grid, preserving the appearance.
		<ul><li>For perspective plug-in objects (created for putting text and symbols in perspective),
		replaces the plug-in art with the result art, and deletes the plug-in art from the artwork tree.
		You will no longer be able to edit text or symbols associated with this perspective plug-in object.</li>
		<li>For a group or container, the group and all its children are released from the perspective grid recursively. </li></ul>
			@param art The art object, or NULL to operate on current selection.
	*/
	AIAPI AIErr			(*ReleaseArtFromPerspective) (AIArtHandle art);

	/**	Attaches art to the perspective grid, preserving the appearance.
		For a group or container, the group and all its children are recursively attached to the current active
		plane of the perspective grid.
			@param art The art object, or NULL to operate on current selection.
	*/
	AIAPI AIErr			(*AttachArtToPerspective) (AIArtHandle art);

	/**	Reports whether art can be attached to the perspective grid.
		(Note that this method returns a Boolean value, not an error code.)
			@param art The art object, or NULL to operate on current selection.
			@return True if the art can be attached to the perspective grid.
	*/
	AIAPI AIBoolean			(*CanAttachToPerspective) (AIArtHandle art);

	/**	Reports whether art can be released from the perspective grid.
		(Note that this method returns a Boolean value, not an error code.)
			@param art The art object, or NULL to operate on current selection.
			@return True if the art can be released from the perspective grid.
	*/
	AIAPI AIBoolean			(*CanReleaseFromPerspective) (AIArtHandle art);

	/**	Reports whether art is a perspective plug-in group object, created for putting
		text and symbols in perspective.
		(Note that this method returns a Boolean value, not an error code.)
			@param art The art object.
			@return True if the art is a perspective plug-in group object
	*/
	AIAPI AIBoolean		(*IsPerspectivePluginObject) (AIArtHandle art);

	/**	Retrieves the type of art contained in a given perspective plug-in object.
		Currently, only Text and Symbol art objects can be placed in a perspective plug-in object.
			@param art  The perspective plug-in object.
			@param type [out] A buffer in which to return the type of perspective object,
					one of \c #kTextFrameArt or \c #kSymbolArt.
	*/
	AIAPI AIErr			(*GetTypeOfPerspectiveObject)(AIArtHandle art, ai::int16 &type);

	/**	Reports whether user is currently editing the original art (text or symbol)
		of a given perspective plug-in object.
		(Note that this method returns a Boolean value, not an error code.)
			@param art The perspective plug-in art object.
			@return True if the original art is being edited.
	*/
	AIAPI AIBoolean		(*IsPerspectiveObjectEditingOriginal)(AIArtHandle art);

	/**	Places art in a given perspective plane at a given position.
			@param art The art object.
			@param startPoint  Start point of a placement drag operation.
			@param endPoint  End point of a placement drag operation.
			@param plane The plane in which to place the art object.
	*/
	AIAPI AIErr			(*PlaceArtInPerspective) (AIArtHandle art, AIRealPoint startPoint, AIRealPoint endPoint, GridPlaneType plane);

	/** Retrieves the offset of art on the perspective plane on which it is placed.
		(Note that this method returns a numeric value, not an error code.)
			@param art The art object in perspective.
			@return The offset value.
	*/
	AIAPI AIReal		(*GetObjectPlaneOffset) (AIArtHandle art);

	/** Retrieves the perspective plane for art that is currently in perspective.
			@param art The art object in perspective.
			@param objectPlane [out] A buffer in which to return the plane on which the art object is placed.
	*/
	AIAPI AIErr			(*GetObjectPlane) (AIArtHandle art, GridPlaneType *objectPlane);


	/** This method places two points into perspective with one another on a given plane.
	    If needed, modifies the point values in place; for example, if the end point goes
	    beyond the vanishing point. You can choose to return the offset used to perform
	    the transformation, which reflects the depth of the plane.
			@param startPt [in/out] Document coordinates of start point. Modified in place if necessary.
			@param endPt [in/out] Document coordinates of end point. Modified in place if necessary.
			@param gridPlane [in] The grid plane.
			@param offset [optional, out] A buffer in which to return the offset used for the transformation.
	*/
	AIAPI AIErr	(*ConstrainPtsInPlane)(AIRealPoint& startPt, AIRealPoint& endPt, GridPlaneType& gridPlane, AIReal *offset);

	/** Reports whether selected objects are at different offsets on the perspective grid plane.
			@param isMultiOffsetSelection [out] A buffer in which to return true if selected objects are at different offsets.
	*/
	AIAPI AIErr	(*IsSelectionInMultipleOffset)(AIBoolean* isMultiOffsetSelection);

	/** Retrieves the perspective bounds from a perspective art object. The perspective grid
		scale is not considered in the returned bounds.
	@param art The perspective art object.
	@param flags Bit flags that specify which bounds to return, a logical OR of \c #AIArtBoundsOptions constants.
	@param bounds [out] A buffer in which to return the perspective art bounds.
	*/
	AIAPI AIErr (*GetOriginalArtBounds) (AIArtHandle art, ai::int32 flags, AIRealRect& bounds);

} AIPerspectiveTransformSuite;

#include "AIHeaderEnd.h"

#endif // __AIPerspectiveTransform__
