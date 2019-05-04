#ifndef __AICursorSnap__
#define __AICursorSnap__

/*
 *        Name:	AICursorSnap.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Cursor Snapping Suite.
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
#ifndef __AIDocumentView__
#include "AIDocumentView.h"
#endif
#ifndef __AITool__
#include "AITool.h"
#endif

#include "AIHeaderBegin.h"

/** @file AICursorSnap.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAICursorSnapSuite				"AI Cursor Snap Suite"
#define kAICursorSnapSuiteVersion16		AIAPI_VERSION(16)
#define kAICursorSnapSuiteVersion		kAICursorSnapSuiteVersion16
#define kAICursorSnapVersion			kAICursorSnapSuiteVersion


/**
	Kinds of custom constraints for \c #AICursorSnapSuite.
 */
enum {
	/** Single point */
	kPointConstraint = 1,
	/** A line whose angle is relative to the page coordinates */
	kLinearConstraintAbs,
	/**	A line whose angle is relative to the constraint angle	*/
	kLinearConstraintRel
};


/**  Flags for custom constraints:
  See \c #AICursorSnapSuite. */
/* Snap to constraint when shift key is down. */
#define kShiftConstraint			(1<<0L)
/* Override drawing the default annotation when a custom constraint is hit,
 * and draw custom constraints based on the callback
 */
#define kDrawCustomAnnotations		(1<<1L)


/** Boundary editors for the transformation tools.
See \c #AICursorSnapSuite. */
enum {
	kTranslateBoundaryEditor = 1
};


/*******************************************************************************
 **
 ** Types
 **
 **/
/*
 * AICustomAnnotationLine 
 * represents a line segment by a start and end point which 
*/
struct AICustomAnnotationLine
{
	AIRealPoint startPoint;
	AIRealPoint endPoint;
};

typedef AICustomAnnotationLine* AICustomAnnotationLinePtr;

/** Function pointer type to retrieve details of custom annotations
* to be drawn (if kDrawCustomAnnotations flag is set).
* The function pointer is set in AICursorConstraint struct during constraint addition.
* When the custom constraint is hit and annotations are ready to be drawn, the callback is invoked.
*		@param	inId				ConstraintId of the custom constraint hit
*		@param	inSnappedPt			The point we snapped to
*		@param  outNumberOfLines	Number Of Annotation Lines to be drawn (To be Filled by the callback)
*		@param	outAnnotationLines	An array of custom annotation lines to be drawn (To be Filled by the callback)
* The calling function is responsible to destroy the array of points.
*/
typedef AIErr(*CustomAnnotationsCallback)(ai::uint32 inId, const AIRealPoint& inSnappedPt, size_t* outNumberOfLines, AICustomAnnotationLine** outAnnotationLines);

/**
	Structure describing a custom constraint for \c #AICursorSnapSuite..
 */
struct AICursorConstraint {
	/** Type of constraint, one of:
		\li \c kPointConstraint: A single point.
		\li \c kLinearConstraintAbs: A line whose angle is relative to
			the page coordinates.
		\li \c kLinearConstraintRel: A line whose angle is relative
			to the constraint \c angle.
	*/
	ai::int32					kind;
	/** Flags for the constraint. The only flag is \c #kShiftConstraint,
	 which means snap to the constraint when the shift key is down.*/
	ai::int32					flags;
	/** Origin point for the constraint. */
	AIRealPoint					point;
	/** When \c kind is \c kLinearConstraintRel, the angle of the line. */
	AIReal						angle;
	/** Label for the constraint presented to the user. Keep the maximum size to be 256 bytes */
	ai::UnicodeString			label;
	/** Callback function registered by client to retrieve details for drawing custom annotations. */
	CustomAnnotationsCallback	getCustomAnnotationDetails;

	/* Constructors */
	AICursorConstraint(const ai::int32 inKind,
		const ai::int32 inFlags,
		const AIRealPoint& inPoint,
		const AIReal inAngle,
		const ai::UnicodeString& inLabel,
		const CustomAnnotationsCallback inCustomAnnotationsCallback) :
			kind(inKind),
			flags(inFlags),
			point(inPoint),
			angle(inAngle),
			label(inLabel),
			getCustomAnnotationDetails(inCustomAnnotationsCallback)
	{}

	AICursorConstraint() :
		kind(0),
		flags(0),
		angle(kAIRealZero),
		getCustomAnnotationDetails(NULL)
	{
		point.h = kAIRealZero;
		point.v = kAIRealZero;
	}

	/* Destructor */
	~AICursorConstraint() 
	{}
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Tools that use the Smart Guides snapping facility use these
	functions in the cursor-tracking code. The suite provides functions
	for snapping the cursor to various things, called \e constraints.
	Constraints include art objects, page boundaries,
	and automatically generated guide lines. You can also define your own
	constraints, using \c #SetCustom(), although most tools do not do so.

	@note Turning on the grid turns smart guides off, so you never use
	this facility to snap to the grid.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICursorSnapSuite and \c #kAICursorSnapVersion.

	Snap the cursor using the \c #Track() function, which
	takes a current cursor location and returns the snapped location.
	A control string contains a series of Smart Guide commands
	that control how the snap is performed; that is, what kind of
	object is snapped to and what kind of location to look for in
	each kind of object.

	You can find out what object is under the snapped location:
@code
AIHitRef hit;
long option = <<whatever options>>
result = sAIHitTest->HitTest(NULL, &p, option, &hit);
if (result)
	throw ai::Error(result);
@endcode

	These are the control strings used by various tools built
	into Illustrator, as saved in the preferences file.
	The first entry in each line is the key used in preferences. The second
	is the control string for the time when the mouse is up. The third is the control
	string for the time when the mouse is down.

	- "Blend",			"A v",				"A v",
	- "Select",			"A v o f",			"ATFGPLM v i o f", 
	- "RangeSelect",	"",					"",
	- "Zoom",			"",					"",
	- "Page",			"ATFGP v i o",		"ATFGP v i o",
	- "Ruler",			"ATFGPX v i o",		"ATFGPMX v i o",
	- "Guide",			"ATFGPX v i o",		"ATFGPX v i o",
	- "Scissor",		"ATFL v i o",		"ATFGPL v i o", 
	- "SquareCircle",	"ATFGP v i o",		"ATFGP v i o",
	- "Pen",			"ATFGPLMSU v i o",	"ATF v i o",
	- "Translate",		"ATFGP v i o",		"ATFGPBLM v i o",
	- "Scale",			"ATFGPXY v i o",	"ATFGPBLMXY v i o",
	- "Rotate",			"ATFGPXY v i o",	"ATFGPLMXY v i o",
	- "Reflect",		"ATFGPXY v i o",	"ATFGPLMXY v i o",
	- "Shear",			"ATFGP v i o",		"ATFGPLM v i o",
	- "Eyebucket",		"A v o f",			"A v o f",
*/

struct AICursorSnapSuite {

	/** Reports whether Smart Guides should be used to snap the
		cursor in a given view. (Note that this function returns
		a Boolean value, not an error code.)
			@param view The document view.
			@return True if Smart Guides should be used.
	 */
	AIAPI AIBoolean		(*UseSmartGuides)		(AIDocumentViewHandle view);

	/** Resets the Smart Guides snapping engine. This clears all custom constraints
		and all automatically generated constraint lines.
	 */
	AIAPI AIErr			(*Reset)				(void);

	/** Clears all custom constraints without clearing automatically
		generated constraint lines.
	 */
	AIAPI AIErr			(*ClearCustom)			(void);

	/** Replaces the current set of custom constraints with the specified set.
			@param count The number of constraints being defined.
			@param constraints An array of custom constraints. The function makes a
				copy, so the caller can free this memory after making the call.
	 */
	AIAPI AIErr(*SetCustom)			(const ai::AutoBuffer<AICursorConstraint>& constraints);

	/** Snaps the cursor to a specified constraint, using a specified technique, using
		the "Snap To Point" application preference.
			@param view The document view in which to snap the cursor.
			@param srcpoint The actual cursor location in artwork coordinates.
				Typically passed in the \c #AIToolMessage member \c cursor.
			@param event The state of modifier keys.
			@param control How snapping is performed, a string containing
				a sequence of uppercase and lowercase characters, and spaces.
				Each character in the string is a command to the snapping engine.
				They are processed sequentially from left to right.
				\li An uppercase character enables a constraint:
					- A: Enable snapping to art objects (if the "Snap To Point" application
						 preference is set). Uses the Snapping tolerance preference
						 (rather than the Selection tolerance).
					- T: Enable snapping to custom constraints defined by the current tool.
					- F: Enable snapping to automatically generated guidelines.
					- P: Enable snapping to the page boundaries.
					- L: Enable snapping to automatically generated guidelines along the center and the edges
						 of geometric box of all visible art objects in view.
					- M: Enable snapping to automatically generated guidelines along the center and the edges
						 of all artboards in the view.
					- S: Enable snapping to automatically generated Perspective guidelines.
					- U: Enable snapping to Perspective Grid visible in the current document.
					- X: Enable snapping to pixel grid (if "snap to pixel" document preference is set)
					- Y: Enable snapping to sub-pixel grid (if "snap to pixel" document preference is set)
					- Z: Enable snapping to pixel/sub-pixel grid in a stroke-aware fashion (if "snap to pixel" document preference is set)

				\li A lower case character is an instruction to look for the best snap location.
					of a particular type among the currently enabled constraints.
						- i: Look for intersections of two or more constraints.
						- o: Try to snap onto a constraint line.
						- v: Try to snap to a point (vertex).
						- f: Look for filled objects.
				\li A space character is an instruction to return the best snap location found
					so far. If no snap location has been found, the search continues.

			@param dstpoint [out] A buffer in which to return the snapped cursor position.
	*/
	AIAPI AIErr			(*Track)				(AIDocumentViewHandle view, const AIRealPoint& srcpoint,
												const AIEvent* event, const char* control,
												AIRealPoint* dstpoint);

	/**	Snaps the cursor to a specified constraint, using a specified technique. Does not
		consider the "Snap To Point" application preference, and uses the Selection
		tolerance to identify hits on art objects. This function is used for direct
		selection of anchor points.
			@param view The document view in which to snap the cursor.
			@param srcpoint The actual cursor location in artwork coordinates.
				Typically passed in the \c #AIToolMessage member \c cursor.
			@param event The state of modifier keys.
			@param control How snapping is performed, a string containing
				a sequence of uppercase and lowercase characters, and spaces.
				Each character in the string is a command to the snapping engine.
				They are processed sequentially from left to right.
				\li An uppercase character enables a constraint:
					- A: Enable snapping to art objects (without regard to the
						"Snap To Point" application preference). Uses the Selection
						tolerance preference (rather than the Snapping tolerance).
					- T: Enable snapping to custom constraints defined by the current tool.
					- F: Enable snapping to automatically generated guidelines.
					- P: Enable snapping to the page boundaries.
					- X: Enable snapping to pixel grid (if "snap to pixel" document preference is set)
					- Y: Enable snapping to sub-pixel grid (if "snap to pixel" document preference is set)
					- Z: Enable snapping to pixel/sub-pixel grid in a stroke-aware fashion (if "snap to pixel" document preference is set)

				\li A lower case character is an instruction to look for the best snap location
					of a particular type among the currently enabled constraints.
						- i: Look for intersections of two or more constraints.
						- o: Try to snap onto a constraint line.
						- v: Try to snap to a point (vertex).
						- f: Look for filled objects.
				\li A space character is an instruction to return the best snap location found
					so far. If no snap location has been found, the search continues.

			@param dstpoint [out] A buffer in which to return the snapped cursor position.
			@param magnifyAnchorPoint [in] True to magnify an anchor point whose hotspot is under the
				mouse cursor, as the direct selection tool does.
	*/
	AIAPI AIErr			(*HitTrack)				(AIDocumentViewHandle view, const AIRealPoint &srcpoint,
												const AIEvent* event, const char* control,
												AIRealPoint* dstpoint, AIBoolean magnifyAnchorPoint);


	/** Snaps the rectangle supplied to a specified constraint, using a specified technique and
	the "Snap To Point" application preference. This method returns the new snapped rectangle and
	new mouse location. If no snapping is done, then the returned point and the rectangle would be same as
	the passed values for source point and rectangle.

		@param view The document view in which to snap the cursor.
		@param srcpoint The actual cursor location in artwork coordinates.
			Typically passed in the \c #AIToolMessage member \c cursor.
		@param event The state of modifier keys.
		@param control How snapping is performed, a string containing
			a sequence of uppercase and lowercase characters, and spaces.
			Each character in the string is a command to the snapping engine.
			They are processed sequentially from left to right.
			\li An uppercase character enables a constraint:
				- A: Enable snapping to art objects (if the "Snap To Point" application
					preference is set). Uses the Snapping tolerance preference
					(rather than the Selection tolerance).
				- T: Enable snapping to custom constraints defined by the current tool.
				- F: Enable snapping to automatically generated guidelines.
				- P: Enable snapping to the page boundaries.
				- L: Enable snapping to automatically generated guidelines along the center and the edges
					 of geometric box of all visible art objects in view.
				- M: Enable snapping to automatically generated guidelines along the center and the edges
					 of all artboards in the view.
				- S: Enable snapping to automatically generated Perspective guidelines.
				- U: Enable snapping to Perspective Grid visible in the current document.
				- X: Enable snapping to pixel grid (if "snap to pixel" document preference is set)
				- Y: Enable snapping to sub-pixel grid (if "snap to pixel" document preference is set)
				- Z: Enable snapping to pixel/sub-pixel grid in a stroke-aware fashion (if "snap to pixel" document preference is set)

			\li A lower case character is an instruction to look for the best snap location.
				of a particular type among the currently enabled constraints.
					- i: Look for intersections of two or more constraints.
					- o: Try to snap onto a constraint line
					- v: Try to snap to a point (vertex).
					- f: Look for filled objects.
			\li A space character is an instruction to return the best snap location found
				so far. If no snap location has been found, the search continues.

		@param dstpoint [out] A buffer in which to return the snapped cursor position.
		@param srcRect The rectangle to be snapped.
		@param dstRect [out] A buffer in which to return the new snapped rectangle bounds.
	*/
	AIAPI AIErr			(*TrackInRect)				(AIDocumentViewHandle view, const AIRealPoint& srcpoint,
													const AIEvent* event, const char* control,
													AIRealPoint* dstpoint, const AIRealRect* srcrect,
													AIRealRect* dstrect);
};


#include "AIHeaderEnd.h"


#endif
