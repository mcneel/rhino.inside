#ifndef __AIPlanarObject__
#define __AIPlanarObject__

/*
 *        Name:	AIPlanarObject.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Planar Object Suite.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif
#ifndef __AIPath__
#include "AIPath.h"
#endif
#ifndef __AIArtStyle__
#include "AIArtStyle.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIPlanarObject.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPlanarObjectSuite					"AI Planar Object Suite"
#define kAIPlanarObjectSuiteVersion4			AIAPI_VERSION(4)
#define kAIPlanarObjectSuiteVersion				kAIPlanarObjectSuiteVersion4
#define kAIPlanarObjectVersion					kAIPlanarObjectSuiteVersion


/** The \c #AIPreferenceSuite suffix for whether
	complexity warnings have been disabled. */
#define kLivePaintComplexityWarning				"LivePaintComplexityWarning"

/** Identifies the planar object plug-in as the current plug-in selection */
#define kPlanarObjectPluginSelection "Planar FaceEdgeSelection"


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference for a planar object. This is an intermediate object,
	NOT an art object handle. Use only with the \c #AIPlanarObjectSuite. */
typedef struct _AIPlanarObject*	AIPlanarObjectHandle;

/** Options	for creating a planar object
	with \c #AIPlanarObjectSuite::NewPlanarObject() */
typedef struct
{
	/** The maximum size gap (in points) between real edges to be treated
		as an implied edge for separating faces.*/
	AIReal			gapMax;
	/** True to enable gap detection. Default is false. */
	AIBoolean		gapDetectEnabled;
} AIGapOptions;


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite provides functions for working with \e planar \e objects,
	which are temporary objects used to construct a planar plug-in-group art object.
	Use these functions to create, populate, and query the attributes of
	planar objects, and to create art from planar objects.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPlanarObjectSuite and \c #kAIPlanarObjectVersion.
	*/
typedef struct {

	/** Begins construction of a planar object.	After creation, add paths to the object
		using functions such as \c #AddPath().
			@param matrix A transformation matrix that translates from the art-object
				space into the planar-object space.
			@param gapOptions Creation options for gap detection. Optional; gap detection
				is off by default.
		*/
	AIAPI AIPlanarObjectHandle (*NewPlanarObject) ( const AIRealMatrix* matrix, const AIGapOptions* gapOptions );

	/** Adds a path to a planar object.
			@note Even when consecutive segments share the same stroke and same styles on each side,
				the styles are \e not coalesced into a multi-segment data structure. For example, a
				path that separates only two faces must have the same styles repeated in each style array.

			@param object The planar object.
			@param segmentCount	The number of segments in the path.
			@param segments	The path segments, an array of size \c segmentCount for a
				closed path, or of size \c segmentCount+1 for an open path.	(A path segment
				is an anchor point with	its two handles, and an open path has one more
				anchor point than it has bezier segments.)
			@param leftFill	Style objects containing the paint style for the fill
				to the left of each corresponding segment. An array of size \c segmentCount.
				A \c NULL entry specifies no fill. An entry that refers to the outside of
				the planar object must be \c NULL.
			@param rightFill Style objects containing the paint style for the fill
				to the right of each corresponding segment. An array of size \c segmentCount.
				A \c NULL entry specifies no fill. An entry that refers to the outside of
				the planar object must be \c NULL.
			@param stroke Style objects containing the paint style for the stroke
				of each corresponding segment. An array of size \c segmentCount.
				A \c NULL entry specifies no stroke.
			@param closed True to create a closed path.

			@note  The added paths must, collectively, specify a consistent planar map.
  			in which paths intersect only at endpoints of the Bezier curves
  			(except for intersections that result from rounding and path flattening inaccuracy),
  			Each face of the map must have a consistent style, as defined by the style
  			of each bounding path.

			@return An error if a violation of conditions is detected; however,
				it is not always possible to detect whether conditions have been violated.
				The results of a violation are, in general, undefined.
		*/
	AIAPI AIErr (*AddPath) (
		AIPlanarObjectHandle object, int segmentCount, AIPathSegment *segments,
			AIArtStyleHandle *leftFill, AIArtStyleHandle *rightFill, AIArtStyleHandle *stroke,
			AIBoolean closed );

	/* Adds a path to a planar object, for a path that has uniform stroke style
		and separates only two faces, such as a closed shape surrounded entirely by one
		other face.
			@param object The planar object.
			@param segmentCount	The number of segments in the path.
			@param segments	The path segments, an array of size \c segmentCount for a
				closed path, or of size \c segmentCount+1 for an open path.	(A path segment
				is an anchor point with	its two handles, and an open path has one more
				anchor point than it has bezier segments.)
			@param leftFill	A style object containing the paint style for the fill
				to the left of all segments.
			@param rightFill A style object containing the paint style for the fill
				to the right of all segments.
			@param stroke A style object containing the paint style for the stroke
				of all segments.
			@param closed True to create a closed path.
	*/
	AIAPI AIErr (*AddPathUniform) (
		AIPlanarObjectHandle object, int segmentCount, AIPathSegment *segments,
			AIArtStyleHandle leftFill, AIArtStyleHandle rightFill, AIArtStyleHandle stroke,
			AIBoolean closed );

	/** Abandons the creation of a planar object.
			@param object The planar object. After the call, this handle is no longer valid.
		*/
	AIAPI AIErr (*Abandon) ( AIPlanarObjectHandle object );

	/** Creates a new planar plug-in group art object from a planar object.
		The new edit group contains paths constructed from the segments and styles
		of the paths added to the planar object.There might not be a one-to-one
		correspondence between the number of paths added and the final contents of
		the edit group, as the function can coalesce or split paths to maximize
		editability and preserve validity of the planar map.
			@param object The planar object. After the call, this handle is no longer valid.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object.
			@param newArt [out] A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*CreateArt) ( AIPlanarObjectHandle object, ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Reports whether an art object is a planar plug-in group.
		(Note that this function returns a boolean value, not an error code.)
			@param art The art object.
			@return True if the art is a planar plug-in group.
		*/
	AIAPI AIBoolean (*IsPlanarArtObject) ( AIArtHandle art );

	/** Reports whether a selection can be converted to a planar object,
		based on the amount of memory available. Warns if the complexity
		is too great, and allows the user to choose whether to continue
		or cancel.

		Succeeds if the conversion is simple enough that no
		warning is needed, or if the user chooses to continue.
		If user interaction is disabled (by using \c #ASUserInteractionSuite
		or because you are running a script), the function succeeds, but
		still reports whether the complexity merits a warning.
			@param fromPlanarMap True if \c pathOrEdgeCount specifies the number of
				edges in the planar map. <br> False if \c pathOrEdgeCount specifies
				the number of legacy paths in a selection or in the result art
				of a tracing object.
			@param pathOrEdgeCount The number of edges in the planar map,
				or the number of legacy paths in a selection or in the result art
				of a tracing object.
			@param gapOptions Proposed gap detection options. Can be \c NULL; default is
				no gap detection.
			@param warningDisplayed [out] Optional. A buffer in which to return true if
				the complexity warning was displayed. You might want to check this to prevent
				displaying a redundant warning if complexity checks might be made
				at multiple places.	If user interaction is disabled, returns true
				if the complexity was sufficient to merit the warning.
			@return \c #kNoErr if no warning was necessary,	or if the complexity
				warning was displayed and the user clicked Continue to accept the risk,
				or if user interaction is disabled,
				<br>The error \c #kCanceledErr if the complexity warning was displayed and
					the user clicked Cancel.
		*/
	AIAPI AIErr (*ComplexConversionCanceled) ( AIBoolean fromPlanarMap, ai::int32 pathOrEdgeCount,
											const AIGapOptions* gapOptions, AIBoolean *warningDisplayed /*output*/ );

	// New for AI 13
	/** Erases a shape from a Live Paint planar object.
			@param pathBlob A path or compound path object for the shape to erase. It is always be treated as closed.
				The object is not modified.
			@param planarObject A planar object plug-in group. This object is modified in place.
			@param erasedSomething [out] Optional. A buffer in which to return true if the function
				made any modification  in the planar object.
		*/
	AIAPI AIErr (*EraseBlob)( AIArtHandle pathBlob, AIArtHandle planarObject, AIBoolean* erasedSomething );

 	/** Selects all faces that have the same style (fill color) as the currently
 		selected faces.
 		If the currently selected faces have mixed styles, or if there are
 		no faces selected, does nothing. Use \c #CanSelectSimilarFaceStyle()
 		to check whether this is the case.
 		*/
 	AIAPI AIErr (*SelectSimilarFaceStyle)(void);
	/** Reports whether all faces that have the same style (fill color) as the
		currently selected faces can be selected using \c #SelectSimilarFaceStyle().
		(Note that this function returns a boolean value, not an error code.)
			@return True if similar face styles can be selected, false otherwise.
		*/
 	AIAPI AIBoolean (*CanSelectSimilarFaceStyle)(void);


 	/** Selects all edges that have the same edge weight as the currently
 		selected edges.
 		If the currently selected edges have mixed edge weights, or if there
 		are no edges selected, does nothing. Use \c #CanSelectSimilarEdgeWeights()
 		to check whether this is the case.
 	*/
 	AIAPI AIErr (*SelectSimilarEdgeWeights)(void);
	/** Reports whether all edges that have the same edge weight as the currently
 		selected edges can be selected using \c #SelectSimilarEdgeWeights().
		(Note that this function returns a boolean value, not an error code.)
			@return True if similar edge weights can be selected, false otherwise.
		*/
 	AIAPI AIBoolean (*CanSelectSimilarEdgeWeights)(void);


 	/** Selects all edges that have the same color as the currently
 		selected edges.
 		If the currently selected edges have mixed colors, or if there
 		are no edges selected, does nothing. Use \c #CanSelectSimilarEdgeColors()
 		to check whether this is the case.
 	*/
 	AIAPI AIErr (*SelectSimilarEdgeColors)(void);
	/** Reports whether all edges that have the same color as the currently
 		selected edges can be selected using \c #SelectSimilarEdgeColors().
		(Note that this function returns a boolean value, not an error code.)
			@return True if similar edge colors can be selected, false otherwise.
		*/
 	AIAPI AIBoolean (*CanSelectSimilarEdgeColors)(void);



} AIPlanarObjectSuite;


#include "AIHeaderEnd.h"


#endif	// __AIPlanarObject__
