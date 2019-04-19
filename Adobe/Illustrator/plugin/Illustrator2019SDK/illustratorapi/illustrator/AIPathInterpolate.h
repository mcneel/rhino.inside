#ifndef __AIPathInterp__
#define __AIPathInterp__

/*
 *      Name:		AIPathInterpolate.h
 * 		Purpose:	Adobe Illustrator Path Interpolation Suite.
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

#include "AIHeaderBegin.h"

/** @file AIPathInterpolate.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPathInterpolateSuite				"AI Path Interpolate Suite"
#define kAIPathInterpolateSuiteVersion4		AIAPI_VERSION(4)
#define kAIPathInterpolateSuiteVersion		kAIPathInterpolateSuiteVersion4
#define kAIPathInterpolateVersion			kAIPathInterpolateSuiteVersion



/*******************************************************************************
 **
 **	Types
 **
 **/


/** A knot in an \c #AIFlattenedPath.  */
typedef struct {
	/** The distance in points from the previous knot. */
	AIReal lengthFromLastKnot;
	/** The distance of this knot from the beginning of the path, expressed as a
		 fractional value from [0.0..1.0]. */
	AIReal fractionalLengthAlongPath;
} AIKnot;


/** Represents a path after flattening. */
typedef struct {
	/** The length of the flattened path in document points.   */
	AIReal		totalPathLength;
	/** The number of knots in flattened path.  */
	ai::int16		ctKnots;
	/** The knots in the flattened path, an array of size \c ctKnots. */
	AIKnot		knots[1];
} AIFlattenedPath;


/** Identifies a specific point along a path, in two different ways.
	Used to keep track of the point selections on a partially selected path,
	if they will be needed after the path is modified. These values
	(along with the number of points the path had before modification)
	can be used to match a point value to its corresponding point after
	the modification. Depending on the type of modification, one of the
	representations changes, but the other remains invariant.

	\li If the number of points after an edit is the same as when the match
		was specified, use \c segmentOffset. Use for transformations or distortions of
		the whole path, as well as edits that move some or all of the points.
	\li If the number of points after an edit is different from	when the match
		was specified, use \c flattenedOffset. Use for edits that add or delete
		points without changing the geometry of the path.
*/
typedef struct {
	/** An \c #AIReal in which the integer part is an anchor point
		index into the \c #AIPathSegment list of a path, and the fractional part
		is a t-value along the bezier between that anchor
		point and the next one (usually 0). This is the same as the \e offset.
		See AITextPathSuite::GetTextPathOffset().

		This can change after points are inserted or deleted in the path.
		*/
	AIReal segmentOffset;
	/** An \c #AIReal in which only the fractional part is significant,
		and represents the t-value along the entire flattened path length.

		This can change if anchor or control points are moved.
		*/
	AIReal fractionalOffset;
} AIAnchorIdentifier;


/** Installation data for \c #AIPathInterpolateSuite::InsertInterpolants():

	Initialize the \c parent, \c paintOrder and \c refChild
	to describe where to install the first interpolated path.

		\li If \c refChild is non-null, it must be a child of \c parent,
			and the \c paintOrder must be \c #kPlaceBelow or \c #kPlaceAbove.
		\li If \c refChild is \c NULL, \c paintOrder must be \c #kPlaceInsideOnTop
			or \c #kPlaceInsideOnBottom.


*/
typedef struct
{
	/** The parent art object in the paint order of the current document's art tree. */
	AIArtHandle		parent;
	/** The prepositional object if \c paintOrder is \c #kPlaceBelow or \c #kPlaceAbove,
		otherwise \c NULL. */
	AIArtHandle		refChild;
	/** The paint order position of the new path, relative to the \c refChild object,
		an \c #AITypes::AIPaintOrder value. */
	ai::int16			paintOrder;
	/** For default interpolation (when the post-install callback is \c NULL); ignored otherwise.
		\li When true, each path is linked as the sibling of the previous one,
		so that the last created path, the one most like the supplied end path,
		is on the bottom.
		\li When false, the previous path becomes the sibling of the next one created,
		so that the last created path, the one most like the supplied end path,
		is on the top.*/
	AIBoolean		endOnBottom;
	/** Developer-defined data to pass to the developer-defined post-install callback. */
	void			*clientData;
} AIPathInstallData;

/** Callback function for \c #AIPathInterpolateSuite::InsertInterpolants(),
	called after each new path is created and interpolated.
	Use to determine how the next path should be installed.
	You can also use it to abort the interpolation
	(for a user interruption, for example) or to do other post-processing.
		@param art The new path object.
		@param installData [in, out] A structure that describes how the path
			was installed in the paint order. Update this to describe how
			the next path should be installed.
	*/
typedef ASErr (*PostInstallCB)( AIArtHandle art, AIPathInstallData *installData );


/** Opaque reference to a style-interpolation object.
	See \c #AIPathInterpolateSuite::NewStyleInterpolator() */
typedef struct _t_AIStyleInterpolator* AIStyleInterpolator;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that allow you to interpolate paths and styles,
	creating a smooth blend between two existing art objects.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPathInterpolateSuite and \c #kAIPathInterpolateVersion.
*/
typedef struct {

	/**	Calculates the default number of steps for a smooth blend between two paths or compound
    	paths, based primarily on the maximum distance in any color channel between the two paint
    	styles, and assuming that the interpolated step objects will be placed with their
    	centers on a straight line between the centers of the two blended objects.
 	   		@note If the objects are not appropriate for shading, either because there is
    			no color channel difference (the objects are painted with the same color),
    			or because they are painted with multiple colors (such as gradients
				and patterns), or because they have effects or their outline is too complex
				for shading (such as type objects, groups and symbols), the calculation
				is based on the separation between objects instead, so that the space
				between them is filled with objects that almost overlap or barely overlap.
				See \c #AppropriateForSmoothColor() to determine whether this function
				will base the step calculation on a color difference or the spacial separation.
    		@param startPath The starting art object. Usually a path or compound path.
    		@param endPath The ending art object. Usually a path or compound path.
			@param densityLimit When positive, calculates the maximum distance from a bounding
    			box edge of one path to the corresponding bounding box edge of the other path,
    			and takes the \c densityLimit value as the minimum separation (in document points)
    			between consecutive interpolated edges within that span. Another way to think of
    			this is that 1/densityLimit is the maximum number of interpolated path edges to
    			place in a point of separation between bounding box edges.

   				For example, if the maximum bounding box edge distance between the two blended
   				paths is 4 points, and the density limit is 0.125 (1/8), then steps are at most
   				32 no matter how different the colors are.

   				Use to avoid many paths crowded into a tiny distance, when the blend would look
   				the same with a much smaller number of paths.

 				If the blend is intended for print, a value of about 1/4 to 1/8 point will give
 				smooth color. If it is intended for screen only, a value of 1 pt may be sufficient.

				Ignored if zero, negative, or greater than 4.0.
			@param steps [out] A buffer in which to return the number of steps.
			@see  \c #SmoothColorBlendStepsAlongPath() for calculating an appropriate number
				of steps when the interpolated objects will not be placed along a straight line
				between the centers of the \c startPath and the \c endPath.
		*/
	AIAPI AIErr (*SmoothColorBlendSteps) ( AIArtHandle startPath, AIArtHandle endPath,
										AIReal densityLimit, ai::int16 *steps );

	/** Counts the number of segments of a path that are in \c #kSegmentPointSelected state.
			@param path The path object.
			@param count [out] A buffer in which to return the number of selected segments.
		*/
	AIAPI AIErr (*GetPathSelectedSegmentCount) ( AIArtHandle path, ai::int16 *count );

	/** Translates from a partially selected path to arrays recording which points are
    	selected, in the form of offsets. Ignores non-p0 selections.
		Use to store points across events that may insert or delete anchor points.
			@param path The path object.
			@param count The number of members allocated for the anchor-ID array. If less
				than the number of selected points, only this number are translated.
				If both paths are partially selected and the number of points differs,
				uses the lowest point count.
			@param anchorIDs [out] A buffer in which to return an array of anchor ID values.
				All fractional parts of the \c segmentOffset values are zero.
				If fewer than \c count points are selected, the remaining members are filled
				with anchor IDs whose values are all 0.
				You must allocate memory for this array, and free it when no longer needed.
			@see PathSelectionSegNumbers()	(use to communicate with \c #InsertInterpolants()
				when the number of segments is known.)
		*/
	AIAPI AIErr (*PathSelectionToAnchorIDs) ( AIArtHandle path, ai::int16 count, AIAnchorIdentifier *anchorIDs );

	/** Translates from a partially selected path to an array of selected points.
		Ignores non-p0 selections.
		Use to communicate with \c #InsertInterpolants() when the number of segments is known.
			@param path The path object.
			@param count The number of members allocated for the point array. If less
				than the number of selected points, only this number are translated.
				If both paths are partially selected and the number of points differs,
				uses the lowest point count.
			@param selectedPoints [out] A buffer in which to return an array of point values.
				If fewer than \c count points are selected, the remaining members are filled
				with points whose values are all 0.
				You must allocate memory for this array, and free it when no longer needed.
			@see PathSelectionToAnchorIDs()	(use to store points across events that may insert or
    			delete anchor points.)
		*/
	AIAPI AIErr (*PathSelectionToSegNumbers) ( AIArtHandle path, ai::int16 count, ai::int16 *selectedPoints );

	/**	Selects a set of anchor points in a path.
			@param path The path object.
 			@param count The number of members allocated for the point array.
 			@param selectPoints A set of point values, an array of size \c count.
				You must allocate memory for this array, and free it when no longer needed.
		*/
	AIAPI AIErr (*SelectAnchorPoints) ( AIArtHandle path, ai::int16 count, ai::int16 *selectPoints );

	/** Creates and installs the paths that represent an interpolation between two existing	paths.
		/li If both paths are fully selected, or if either path is not selected at all, then
			the selection state of the anchor points is ignored, and both paths are entirely
			flattened to get the point correspondences for interpolation.

		/li If one path is partially selected, and the other is fully or partially selected,
			the function builds anchor-point arrays corresponding to the partial selections
			and specified matches.

			@param startPath The starting path. Can be \c NULL if end path is given.
			@param endPath The ending path. Can be \c NULL if start path is given.
			@param substituteCenter A point where all points gather at one end, if the
				path for that end is \c NULL. Ignored if both paths are specified.
			@param useStyleFromPath If one of the two paths is \c NULL and the
				other is part of a compound path (an "extra hole"),
                this is the backmost object in the compound path for the other end.
			@param steps The number of steps between the two paths.
        	@param numMatchPairs The number of values in the matches arrays.
				\li When positive, the corresponding values in the two match arrays specify pairs.
				\li When 0 or negative, the matches arrays are ignored, and
					matching starts at the top left corner of both paths
					for a closed path, or the leftmost endpoint for an open path,
					and proceeds clockwise.
			@param matches1	An array of match values of size \c numMatchPairs.
			@param matches2 An array of match values of size \c numMatchPairs.
			@param clientCallback A developer-defined callback to call after each new path is installed.
				Can determine how the next path is installed, provide information for the insertion operation,
				or perform other post-processing on the new paths.

			    If \c NULL, the default behavior is to link each path to the
				previously created one. See \c #AIPathInstallData.
		*/
	AIAPI AIErr (*InsertInterpolants) ( AIArtHandle startPath,
										AIArtHandle endPath,
										AIRealPoint	*substituteCenter,
										AIArtHandle useStyleFromPath,
										ai::int16 steps,
										ai::int16 numMatchPairs, ai::int16 *matches1, ai::int16 *matches2,
										AIPathInstallData *installData,
										PostInstallCB clientCallback);

	/** Calculates the length of a set of path segments.
			@param path The path object.
			@param ixStart The starting point.
			@param count [in, out] The number of members allocated for the segment-length array.
				Returns the number of segment lengths calculated.
			@param segLengths [out] A buffer in which to return an array of segment length values.
				You must allocate memory for this array, and free it when no longer needed.
			@param flatness	 An upper bound on the error between the line segments
				and the true curve.
		*/
	AIAPI AIErr (*MeasurePathSegments) ( AIArtHandle path,
										ai::int16 ixStart, ai::int16 count,
										AIReal *segLengths,
										AIReal flatness );

	// New in AI 9:

	/** Allocates and initializes a style interpolation object for use with
		\c #ApplyInterpolatedStyle(). Not needed with \c #InsertInterpolants(),
		which automatically applies interpolated styles to the paths it creates.
		Use when you create the intermediate objects yourself--for example,
		to apply interpolated styles to group objects or text objects, or to
		interpolate path outlines using a different technique.

		This version includes object-specific data about how the style is
		applied to a particular object (random seeds, scale factors,
		gradient matrices, and so on) that is not encapsulated in the
		\c #AIArtStyleHandle. For a version that creates an interpolation
		object from the styles themselves, see \c #NewArtStyleInterpolator().

		One, but not both of the source objects can be \c NULL. In this case,
		the interpolator applies a copy of the other art style. This avoids the
		need to interpolate down to nothing.

			@param styleSource0 The source art object for the first style.
			@param styleSource1	The source art object for the second style.
		*/
	AIAPI AIErr (*NewStyleInterpolator) ( AIStyleInterpolator* interpolator, AIArtHandle styleSource0, AIArtHandle styleSource1 );

	/** Frees memory for a style interpolator that is no longer needed.
			@param interpolator The style interpolation object. Upon return, this reference is invalid.
		*/
	AIAPI AIErr (*DisposeStyleInterpolator) ( AIStyleInterpolator interpolator );

	/** Uses a style interpolator to create and apply an interpolated style to an
		interpolated art object.
			@param interpolator The interpolation object, as returned by \c #NewStyleInterpolator
				or \c #NewArtStyleInterpolator.
			@param targetArt The intermediate object to which to apply the style.
			@param fraction The distance from the source objects. 0 to apply the style from the
				first source object, 1 to apply the style from the second source object,
				or an interpolation point between the two.
			@note If the art styles are not comparable, the function ignores the
				 \c fraction value and applies the style of the first source object.
		*/
	AIAPI AIErr (*ApplyInterpolatedStyle) ( AIStyleInterpolator interpolator, AIArtHandle targetArt, AIReal fraction );

	/** Allocates and initializes a style interpolation object for use with
		\c #ApplyInterpolatedStyle(). This version uses the style objects directly,
		and does not include object-specific data about how the style is
		applied to a particular object (random seeds, scale factors,
		gradient matrices, and so on) that is not encapsulated in the
		\c #AIArtStyleHandle.

		One, but not both of the source objects can be \c NULL. In this case,
		the interpolator applies a copy of the other art style. This avoids the
		need to interpolate down to nothing.
			@param interpolator [out] A buffer in which to return the new interpolation object.
			@param style0 The first art style object.
			@param style1	The second art style object.
			@see \c #NewStyleInterpolator()
		*/
	AIAPI AIErr (*NewArtStyleInterpolator) ( AIStyleInterpolator* interpolator, AIArtStyleHandle style0, AIArtStyleHandle style1 );

	/** Retrieves an intermediate art style created by a style interpolation object
		that would be applied for a specific call to \c #ApplyInterpolatedStyle().
			@param interpolator The interpolation object, as returned by \c #NewStyleInterpolator
				or \c #NewArtStyleInterpolator.
			@param fraction The distance from the source objects. 0 for the style from the
				first source object, 1 for the style from the second source object,
				or an interpolation point between the two.
			@param result [out]	A buffer in which to return the new art style.
		*/
	AIAPI AIErr (*GetInterpolatedArtStyle) ( AIStyleInterpolator interpolator, AIReal fraction, AIArtStyleHandle* result );

	// New in AI 11:

	/** Reports whether two art objects are suitable for smooth color blending. To be suitable,
		both must be either paths or compound paths, and be painted with different, simple solid colors
		(not gradients, patterns, or active styles).  One or both objects can have transparency.
		(Note that this function returns a boolean value, not an error code.)
			@param art1 The first art object.
			@param art2 The second art object.
			@return True if the two objects are suitable for smooth color blending.
		*/
	AIAPI AIBoolean (*AppropriateForSmoothColor) ( AIArtHandle art1, AIArtHandle art2 );

	/**	Calculates the default number of steps for a smooth blend between two paths or compound
		paths, based primarily on the maximum distance in any color channel between the two paint
    	styles, and assuming that the interpolated step objects will be placed with their
    	centers on an arbitrary path of length \c pathDistance.

		Specifically intended for blends along non-default spine paths.

 	   		@note If the objects are not appropriate for shading, either because there is
    			no color channel difference (the objects are painted with the same color),
    			or because they are painted with multiple colors (such as gradients
				and patterns), or because they have effects or their outline is too complex
				for shading (such as type objects, groups and symbols), the calculation
				is based on the spacial separation between objects instead, so that the space
				between objects placed along a path of length \c pathDistance will be filled
				with objects that almost overlap or barely overlap.
				See \c #AppropriateForSmoothColor() to determine whether this function
				will base the step calculation on the color difference or the separation along
				the spine path.

     		@param startPath The starting art object, usually a path or compound path.
     		@param endPath The ending art object, usually a path or compound path.
 			@param densityLimit When positive (and less than or equal to 4.0), calculates the
 				maximum of \c pathDistance and of the maximum distance between corresponding bounding
 				box edges of the two input objects, and takes the \c densityLimit value as the minimum
				distance between consecutive interpolated step centers placed along that distance.
				Another way to think of this is that 1/densityLimit is the maximum number of interpolated
				step centers to place within each point of the \c pathDistance.

   				For example, if the \c pathDistance is 10 pts, and the maximum bounding box edge
   				separation is less than 10 pts, and the density limit is 0.125 (1/8), then the
   				calculated steps will be at most 80 no matter how different the colors are.

   				Use to avoid many blend steps crowded into a short distance, when the blend would
   				look as smooth with a much smaller number of steps.
 
				Ignored if zero, negative, or greater than 4.0.
			@param steps [out] A buffer in which to return the number of steps.
			@param pathDistance Used to calculate the separation between the start and end objects,
				instead of the object bounds, when the distance is needed either for objects that
				are not appropriate for smooth color or to perform the density limit calculations.
				If the maximum bounding box edge separation is greater than this value, the
				bounding box edge separation is used instead.

				If the objects are appropriate for smooth color, and the density limit is zero,
				this parameter is ignored, and the function returns the same number of
				steps as \c #SmoothColorBlendSteps().
		*/
	AIAPI AIErr (*SmoothColorBlendStepsAlongPath) ( AIArtHandle startPath, AIArtHandle endPath,
													AIReal densityLimit, ai::int16 *steps, AIReal pathDistance );

} AIPathInterpolateSuite;


#include "AIHeaderEnd.h"


#endif
