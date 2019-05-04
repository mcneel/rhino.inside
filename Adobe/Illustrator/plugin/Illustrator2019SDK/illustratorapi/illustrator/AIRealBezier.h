#ifndef __AIRealBezier__
#define __AIRealBezier__

/*
 *        Name:	AIRealBezier.h
 *     Purpose:	Adobe Illustrator bezier suite.
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

#include "AIHeaderBegin.h"

/** @file AIRealBezier.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIRealBezierSuite				"AI Real Bezier Suite"
#define kAIRealBezierSuiteVersion4		AIAPI_VERSION(4)
#define kAIRealBezierSuiteVersion		kAIRealBezierSuiteVersion4
#define kAIRealBezierVersion			kAIRealBezierSuiteVersion

/** Return values for \c #AIRealBezierSuite::AdjustThroughPoint(). */
enum AIAdjustThroughPointResult {
	/** Same slope, but opposite side of p0 */
	kAIBezierAdjustReflectedp1		= 1,
	/** Same slope, but opposite side of p3 */
	kAIBezierAdjustReflectedp2		= 2,
	/** Different slope for p0 to p1  */
	kAIBezierAdjustRotatedp1		= 4,
	/** Different slope for p3 to p2  */
	kAIBezierAdjustRotatedp2		= 8
};

/*******************************************************************************
 **
 **	Typedefs
 **
 **/

/** A cubic Bezier, defined by its four control points. */
typedef struct {
	AIRealPoint	p0;
	AIRealPoint	p1;
	AIRealPoint	p2;
	AIRealPoint	p3;
} AIRealBezier, *AIRealBezierPtr;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides utilities for working with cubic Beziers curves.

	Most of the functions in this suite do not return \c #AIErr values.
	For the most part, they return nothing, or return the result of the operation.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIRealBezierSuite and \c #kAIRealBezierVersion.
	*/
typedef struct {

	/** Sets the four control points that define a cubic Bezier.
			@param b The Bezier object.
			@param p0 The first point.
			@param p1 The second point.
			@param p2 The third point.
			@param p3 The fourth point.
		*/
	AIAPI void		(*Set)			(AIRealBezier* b, AIRealPoint* p0, AIRealPoint* p1,
									AIRealPoint* p2, AIRealPoint* p3);
	/** Translates a cubic Bezier by a vector.
			@param b The Bezier object.
			@param dh The horizontal vector value.
			@param dv The vertical vector value.
		*/
	AIAPI void		(*Offset)		(AIRealBezier* b, AIReal dh, AIReal dv);

	/** Applies a transformation matrix to a cubic Bezier.
			@param b The Bezier object.
			@param m The transformation matrix.
		*/
	AIAPI void		(*Transform)	(AIRealBezier* b, AIRealMatrix* m);

	/** Finds a point for a given input to a cubic Bezier.
			@param b The Bezier object.
			@param t The input value.
			@param p [out] A buffer in which to return the corresponding point.
		*/
	AIAPI void		(*Evaluate)		(AIRealBezier* b, AIReal t, AIRealPoint* p);

	/** Finds a tangent for a given input to a cubic Bezier.
			@param b The Bezier object.
			@param t The input value.
			@param v [out] A buffer in which to return the corresponding tangent.
		*/
	AIAPI void		(*Tangent)		(AIRealBezier* b, AIReal t, AIRealPoint* v);

	/** Finds the normal for a given input to a cubic Bezier.
			@param b The Bezier object.
			@param t The input value.
			@param v [out] A buffer in which to return the corresponding normal.
		*/
	AIAPI void		(*Normal)		(AIRealBezier* b, AIReal t, AIRealPoint* v);

	/** Splits a cubic Bezier at a point that results from a given input value.
		Either \c b1 or \c b2 may be null.
			@param b The Bezier object.
			@param t The input value for the point at which to split.
			@param b1 [out] A buffer in which to return the cubic Bezier for the first half.
			@param b2 [out] A buffer in which to return the cubic Bezier for the second half.
		*/
	AIAPI void		(*Divide)		(AIRealBezier* b, AIReal t, AIRealBezier* b1,
									AIRealBezier* b2);

	/** Reports whether a cubic Bezier intersects a rectangle. Draws the Bezier
		curve into a bitmap, and tests whether any of the marked pixels are
		contained within the supplied rectangle.
		(Note that this function returns a boolean value, not an error code.)
			@param b The Bezier object.
			@param r The rectangle.
			@param scale The scale factor for bitmap resolution, a percentage
				value where 1.0 (100%) is 72 DPI.
			@return True if the bezier intersects the rectangle, false otherwise.
		*/
	AIAPI AIBoolean	(*IntersectsRect)(AIRealBezier* b, AIRealRect* r, AIReal scale);

	// New for AI8.0.

	/** Calculates the length of a cubic Bezier curve.
		(Note that this function returns a numeric value, not an error code.)
			@param b The Bezier object.
			@param flatness The accuracy with which to approximate the curve.
					A number of document points that is the maximum allowed distance
					of any line segment, at its furthest point, from the curve it
					approximates.
			@return The length in document points.
		*/
	AIAPI AIReal	(*Length)			(AIRealBezier* b, AIReal flatness);

	/** Finds the point and tangent for a given input to a cubic Bezier.
		This convenience function is the same as calling both
		\c #Evaluate() and \c #Tangent().
 			@param b The Bezier object.
 			@param t The input value.
			@param p [out] A buffer in which to return the point.
 			@param v [out] A buffer in which to return the tangent.
		*/
	AIAPI void		(*PointAndTangent)	(AIRealBezier* b, AIReal t, AIRealPoint* p, AIRealPoint *v);

	/** Adjusts a cubic Bezier such that it passes through a given input value.
		(Note that this function returns a constant value, not an error code.)
 			@param b The Bezier object.
 			@param p The point.
			@param t The input value.
			@return An \c #AIAdjustThroughPointResult value that indicates
				how the Bezier was adjusted.
		*/
	AIAPI ai::uint16 (*AdjustThroughPoint) (AIRealBezier* b, AIRealPoint* p, AIReal t);

	// New for AI12

	/** Finds the input value to a cubic Bezier that results in a point
		at a given distance along the curve.
 			@param bez The Bezier object.
 			@param length The distance in points, must be less than the total length
				of the curve.
			@param total_length	the total length of the curve. See \c #Length().
			@param flatness The accuracy with which to approximate the curve.
				A value of 1e-2 is suggested.
			@param t [out] A buffer in which to return the input value.
		*/
	AIAPI AIErr 	(*TAtLength) ( AIRealBezier*		bez ,
								   AIReal				length ,
								   AIReal				total_length ,
								   AIReal				flatness,
								   AIReal*				t );
    
} AIRealBezierSuite;


#include "AIHeaderEnd.h"


#endif
