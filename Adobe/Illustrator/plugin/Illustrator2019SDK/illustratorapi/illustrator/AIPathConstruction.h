#ifndef __AIPathConstruction__
#define __AIPathConstruction__

/*
 *        Name:	AIPathConstruction.h
 *   $Revision: 11 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Path Construction Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2013 Adobe Systems Incorporated.
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

#ifndef __AIPath__
#include "AIPath.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIPathConstruction.h */


/*******************************************************************************
 **
 **	Types
 **
 **/

/** A vertex point for a path segment. Used in \c #AIPathConstructionSuite. */
typedef struct {
	/** The point location */
	AIRealPoint point;
	/** True if the point was generated from a corner point of a path,
		or if it should result in a corner point when producing an
		interpolating path. */
	AIBoolean corner;
} AIPathConstructionPoint;


/** Developer-defined memory management routines for
	use in \c #AIPathConstructionSuite.
	The routines must conform to the semantics of C standard library
	functions \c malloc and \c free. Typically, call the
	corresponding \c #SPBlocksSuite function. */
typedef struct {
	/** Allocate a block of memory.
			@param size The number of bytes to allocate.
			@return A pointer to the memory block.
		*/
	void *(*allocate)( size_t size );
	/** Free allocated memory.
			@param pointer The pointer to the block, as returned from
				the \c allocate() call.
		*/
	void (*dispose)( void *pointer );
} AIPathConstructionMemoryObject;


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPathConstructionSuite			"AI PathConstruction Suite"
#define kAIPathConstructionSuiteVersion5	AIAPI_VERSION(5)
#define kAIPathConstructionSuiteVersion		kAIPathConstructionSuiteVersion5
#define kAIPathConstructionVersion			kAIPathConstructionSuiteVersion

/*******************************************************************************
 **
 ** Suite
 **
 **/

/**	@ingroup Suites
	Utilities to convert paths to and from line segments.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPathConstructionSuite and \c #kAIPathConstructionVersion.
 */
typedef struct {

	/** Converts a sequence of path segments describing a single open path
		to a sequence of points that describe an open polygon approximating the path.

		A corner segment corresponds to a corner point. For intermediate
		points, the corner state depends on how your memory allocator fills
		the block that it allocates.

			@param segmentCount The number of segments in the path.
			@param segments The segments, an array of size \c segmentCount.
			@param pointCount [out] A buffer in which to return the number
				of points in the polygon.
			@param points [out] A buffer in which to return a pointer to the
				point set, an array of size \c pointCount.
			@param maxPointDistance An upper bound on the distance
				between successive point samples.
			@param flatness An upper bound on the error between the line segments
				and the true curve.
			@param memory A developer-defined memory management object to use for the conversion.
		*/
	AIAPI AIErr (*CurvesToPoints) ( ai::int32 segmentCount, AIPathSegment *segments,
		ai::int32 *pointCount, AIPathConstructionPoint **points,
					  AIReal maxPointDistance, AIReal flatness,
					  AIPathConstructionMemoryObject *memory );

/** Converts a single curve to a sequence of points and corresponding T values that describe an open polygon approximating the curve.

		A corner segment corresponds to a corner point. For intermediate
		points, the corner state depends on how your memory allocator fills
		the block that it allocates.

			@param startSegment The pointer to first segment of the curve.
			@param endSegment The pointer to second segment of the curve.
			@param pointCount [out] A buffer in which to return the number
				of points in the polygon.
			@param points [out] A buffer in which to return a pointer to the
				point set, an array of size \c pointCount.
			@param tArray [out] A buffer in which to return a pointer to the T values
				corresponding to each point in \c points, an array of size \c pointCount.
			@param maxPointDistance An upper bound on the distance
				between successive point samples.
			@param flatness An upper bound on the error between the line segments
				and the true curve.
			@param memory A developer-defined memory management object to use for the conversion.
		*/

	AIAPI AIErr (*CurveToPointsT) (AIPathSegment *startSegment, AIPathSegment *endSegment, 
		ai::int32 *pointCount, AIPathConstructionPoint **points, AIReal **tArray,
		AIReal maxPointDistance, AIReal flatness,
		AIPathConstructionMemoryObject *memory );

	/** Converts a sequence of points describing a single open polygon
		to a sequence of path segments describing an open path approximating
		the polygon.

		The algorithm used is best suited to generating
		curves from points that were produced by sampling a path. It is not well
		suited for samples of hand drawn points.
			@param pointCount The number of points in the polygon.
			@param points  The point set, an array of size \c pointCount.
			@param segmentCount [out] A buffer in which to return the number of segments in the path.
			@param segments [out] A buffer in which to return a pointer to the segments,
				an array of size \c segmentCount.
			@param tolerance [in] Optional. A pointer to the fit factor. Default is 1.0.
				A smaller factor gives a more exact fit and more segments, a larger factor
				gives a less exact fit and fewer segments.
			@param threshold Not used. Pass \c NULL.
			@param cornerRadius [in] Optional. A pointer to the corner radius value. Default is 4.
				If, at any point in the fitted curve, the radius of an inscribed circle
				that has the same tangent and curvature is less than this radius,
				a corner point is generated there; otherwise the path is smooth at that point.
				Note that this is not the same as the corner-or-smooth attribute that controls whether
				direction handles are permanently linked together when they are later edited. Rather,
				it is whether the direction handles are allowed to differ in the generated curve.
				For an illustration of the radius of curvature of a path at a point, see
				\c http://mathworld.wolfram.com/OsculatingCircle.html
			@param scale [in] Optional. A pointer to the scale factor. Default is 1.0. Input points
				and other input units (such as the corner radius) are multiplied by this factor.
			@param memory A developer-defined memory management object to use for the conversion.
		*/
	AIAPI AIErr (*PointsToCurves) ( ai::int32 *pointCount, AIPathConstructionPoint *points,
		ai::int32 *segmentCount, AIPathSegment **segments,
					  AIReal *tolerance,
					  AIReal *threshold,
					  ai::int16 *cornerRadius,
					  AIReal *scale,
					  AIPathConstructionMemoryObject *memory );

	/** Modifies the segments of a path by converting them to a series
		of points and then re-fitting curves to the points. In some cases
		this can reduce the total number of path segments, especially if
		many are redundant. Any corner segments are preserved.
			@param path The path object.
			@param flatness An upper bound on the error between the line segments
				and the true curve.
			@param memory A developer-defined memory management object to use for the conversion.
		*/
	AIAPI AIErr (*ReducePathSegments) ( AIArtHandle path, AIReal flatness,
					  AIPathConstructionMemoryObject *memory );

} AIPathConstructionSuite;


#include "AIHeaderEnd.h"


#endif
