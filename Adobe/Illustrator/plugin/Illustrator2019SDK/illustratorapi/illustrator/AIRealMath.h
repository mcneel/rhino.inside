#ifndef __AIRealMath__
#define __AIRealMath__

/*
 *        Name:	AIRealMath.h
 *   $Revision: 28 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator AIReal Math Suite.
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

#include <math.h>	// for floor and ceil
#include <float.h>

#include "AIHeaderBegin.h"

/** @file AIRealMath.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIRealMathSuite			"AI Real Math Suite"
#define kAIRealMathSuiteVersion		AIAPI_VERSION(4)
#define kAIRealMathVersion			kAIRealMathSuiteVersion

// Most of this stuff is completely unnecessary, and is just here to ease the
// transition between Fixed and AIReal.  We should probably make a later pass
// to clean the unnecessary stuff out.

// common AIReal constants
#define	kAIRealMax					((AIReal)(DBL_MAX / 10.0F))
#define	kAIRealMin					((AIReal)-(DBL_MAX / 10.0F))
#define	kAIRealUnknown				((AIReal)DBL_MAX)

#define	kAIFloatUnknown				((AIFloat)FLT_MAX)

#ifndef kAIRealOne
#define kAIRealOne					((AIReal) 1.0)
#endif
#ifndef kAIRealZero
#define kAIRealZero					((AIReal) 0.0)
#endif

#ifndef kAIFloatOne
#define kAIFloatOne					(1.0f)
#endif

#ifndef kAIFloatZero
#define kAIFloatZero					(0.0f)
#endif

#define kAIRealHundredth			((AIReal) 0.01)
#define kAIRealSixteenth			((AIReal) (1.0/16.0))
#define kAIRealTenth				((AIReal) 0.1)
#define kAIRealEighth				((AIReal) 0.125)

#ifndef kAIRealQuarter
#define kAIRealQuarter 				((AIReal) 0.25)
#endif

#ifndef kAIRealHalf
#define kAIRealHalf 				((AIReal) 0.5)
#endif

#define kAIRealSevenEighths			((AIReal) 0.875)
#define kAIRealOneThird				((AIReal) (1.0/3.0))
#define kAIRealTwoThirds			((AIReal) (2.0/3.0))
#define kAIRealFourThirds			((AIReal) (4.0/3.0))
#define kAIRealThreeHalves			((AIReal) 1.5)

#define kAIPi						3.141592653589793238462643383279502884197169399375
#define kAIDoublePi					((double) kAIPi)
#define kAIRealPi					((AIReal) kAIPi)
#define kAIRealPi4 					((AIReal) (kAIPi/4.0))
#define kAIRealPi2 					((AIReal) (kAIPi/2.0))
#define kAIReal3PiOver2				((AIReal) (kAIRealThreeHalves*kAIPi))
#define kAIRealTwoPi 				((AIReal) (kAIPi*2.0))

#define kAIRealSquareRootOfTwo		((AIReal) 1.4142135623)								/* 2^(1/2) */
#define kAIRealSquareRootOfThree	((AIReal) 1.7320508075688772935274463415059)		/* 3^(1/2) */
#define kAIRealAvogadrosOther		((AIReal) 0.5522847498)								/* (4/3) [2^(1/2) - 1] */
#define kAIRealGolden 				((AIReal) 1.6180339888)								/* [1 + 5^(1/2)]/2 */

#define kSmallestFixedNumberEquivalent_Tolerance		((AIReal) (1.0 / (1 << 16)) )	// 1 / 2^16
#define kAIRealTolerance								kSmallestFixedNumberEquivalent_Tolerance


/*******************************************************************************
 **
 **	Macros
 **
 **/

#if __BUILD_PLUGIN__

// This code used to depend on WIN_ENV.  But fmin, round, and floor are not ANSI,
// and they don't seem to be available on the Mac.

#define	_AIRealMIN(x, y)	((x) > (y) ? (y) : (x))
#define	_AIRealMAX(x, y)	((x) > (y) ? (x) : (y))
#define _AIRealAbs(x)		((x) >= kAIRealZero ? (x) : -(x))

#define _AIRealRound( x)		(AIReal)( (x) > 0 ? floor((x) + 0.5) : ceil((x) - 0.5))
// NOTE:  Trunc() trunc toward 0
#define	_AIRealTrunc( x)		(AIReal)( (x) > 0 ? floor((x)) : ceil((x)))
#define _AIRealFloor( x)		(AIReal)floor( x)

#if 0		// Formerly #ifndef WIN_ENV
	#define	_AIRealMIN( x, y)	fmin( (x), (y))
	#define	_AIRealMAX( x, y)	fmax( (x), (y))

	#define _AIRealRound( x)		(AIReal)round( x)
	#define _AIRealFloor( x)		(AIReal)floor( x)
	#define	_AIRealTrunc( x)		(AIReal)trunc( x)
#endif

// type conversion macros
#define _ShortToAIReal(a)		((AIReal) (a))
#define _AIRealRoundToShort(a)	((ai::int16) _AIRealRound(a))
#define _AIRealTruncToShort(a)	((ai::int16) _AIRealTrunc(a))

// other macros

#define _AIRealFraction(a)		((AIReal) ((a) - _AIRealTrunc(a)))
#define _AIRealAverage(a, b) 	((AIReal) (((a) + (b)) / 2.0))
#define _AIRealHalf(a) 			((AIReal) ((a) / 2.0))
#define _AIRealOverflow(a)		((a) == kAIRealMax || (a) == kAIRealMin)

#define _AIRealSign(a)			((AIReal) ((a) > 0 ? +1 : ((a) < 0 ? -1 : 0)))

//FIXME: Removed AIRealCeiling, because the definition of its fixed counterpart
//implies that it's meaningless for floats.
//#define _AIRealCeiling(a)		_AIRealFloor((a) + kAIRealOne1)


#endif


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions for working with the \c #AIReal values that
	Illustrator uses for coordinates. (An \c #AIReal is a C \c float type.)
	You can work with \c #AIReal values directly,
	with those contained in position structures for points and rectangles,
	and with those contained in transformation matrices.

	The functions in this suite do not return \c #AIErr values. For the most part,
	they return nothing, or return the result of the operation.

	@note Adobe Illustrator 8.0 changed all coordinate measurements from
		\c #AIFixed to \c #AIReal data types. This change affected many suites;
		in particular, the \c #AIFixedMathSuite was superseded by this suite.
		For backward compatibility, this suite provides functions that convert
		between \c #AIReal and \c #AIFixed numbers.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIRealMathSuite and \c #kAIRealMathVersion.
 */
typedef struct {

	/** Adds two real numbers.
			@param a The first number.
			@param b The second number.
			@return The result. In case of overflow or underflow,
				returns the system-defined maximum or minimum constant.
		*/
	AIAPI AIReal (*AIRealAdd) ( AIReal a, AIReal b );

	/** Multiplies two real numbers.
			@param a The first number.
			@param b The second number.
			@return The result. In case of overflow or underflow,
				returns the system-defined maximum or minimum constant.
		*/
	AIAPI AIReal (*AIRealMul) ( AIReal a, AIReal b );

	/** Divides two real numbers (a/b).
			@param a The first number.
			@param b The second number.
			@return The result. In case of overflow, underflow, or divide by 0,
				returns the system-defined maximum or minimum constant.
		*/
	AIAPI AIReal (*AIRealDiv) ( AIReal a, AIReal b );

	/** Divides two integers (a/b).
			@param a The first number.
			@param b The second number.
			@return The result. In case of overflow or underflow,
				returns the system-defined maximum or minimum constant.
		*/
	AIAPI AIReal (*ShortRatio) ( ai::int16 a, ai::int16 b );

	/** Divides two real numbers (a/b). This is the same as \c #AIRealDiv().
			@param a The first number.
			@param b The second number.
			@return The result. In case of overflow, underflow, or divide by 0,
				returns the system-defined maximum or minimum constant.
		*/
	AIAPI AIReal (*AIRealRatio) ( AIReal a, AIReal b );

	/** Multiplies two sets of numbers and then adds them together: (a * b) + (c * d).
			@param a The first number of the first pair.
			@param b The second number of the first pair.
			@param c The first number of the second pair.
			@param d The second number of the second pair.
			@return The result. In case of overflow or underflow,
				returns the system-defined maximum or minimum constant.
		*/
	AIAPI AIReal (*AIRealMulAdd) ( AIReal a, AIReal b, AIReal c, AIReal d );

	/** Rounds a real number to a given multiple.
			@param a The number.
			@param multiple The multiple; for example, 0.01 to round
				to the nearest hundredth, or 0.05 to round to the
				nearest twentieth. Must not be 0.
			@param ceiling When true, round up. When false, round down.
				(Up and down are signed-- that is, floor -0.5 is -1
				 and ceiling -0.5 is 0, not the other way around.)
			@note When working with decimals, the result is subject to general
				\c #AIReal accuracy problems.
		*/
	AIAPI AIReal (*AIRealMultiple) (AIReal a, AIReal multiple, AIBoolean ceiling );

	/** Computes the sine of a real number in radians.
			@param a The number.
			@return The result.
		*/
	AIAPI AIReal (*AIRealSin) ( AIReal a );

	/** Computes the cosine of a real number in radians.
			@param a The number.
			@return The result.
		*/
	AIAPI AIReal (*AIRealCos) ( AIReal a );

	/** Computes the arctangent of an angle  in radians, where a and b
		are two real numbers such that a/b is the tangent of the angle
			@param a The first number.
			@param b The second number.
			@return The result.
		*/
	AIAPI AIReal (*AIRealATan) ( AIReal a, AIReal b );

	/** Converts an angle expressed in degrees to radians.
			@param degree The number of degrees in the angle.
			@return The number of radians in the angle.
		*/
	AIAPI AIReal (*DegreeToRadian) ( AIReal degree );

	/** Converts an angle expressed in radians to degrees.
			@param radian The number of radians in the angle.
			@return The number of degrees in the angle.
		*/
    AIAPI AIReal (*RadianToDegree) ( AIReal radian );

	/** Computes the square root of a real number.
			@param a The number.
			@return The result.
		*/
	AIAPI AIReal (*AIRealSqrt) ( AIReal a );

	/** Computes the length of a vector starting at (0,0) and ending at (a,b).
		This is the same as <code>AIRealSqrt(a*a + b*b)</code>.
			@param a The X coordinate of the endpoint.
			@param b The Y coordinate of the endpoint.
			@return The result.
		*/
	AIAPI AIReal (*AIRealLength) ( AIReal a, AIReal b );

	/** Computes a value between two real numbers by interpolating
		from \c b at \c t=0 to \c a at \c t=1.	For example, if t=0.5,
		the function returns the average of a and b. If a = 0, b = 1,
		and t = 0.25, the function returns 0.75.
			@param a The first number.
			@param b The second number.
			@param t A percentage of (b-a), expressed as a number between 0 and 1.
			@return The result.
		*/
	AIAPI AIReal (*AIRealInterpolate) ( AIReal a, AIReal b, AIReal t );

	/** Adds two points by adding the two X values and the two Y values.
		No overflow checking is done.
			@param a The first point.
			@param b The second point.
			@param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIRealPointAdd) ( const AIRealPoint *a, const AIRealPoint *b, AIRealPoint *result );

	/** Subtracts point a from point b by subtracting the corresponding component values.
		No overflow checking is done.
			@param a The first point.
			@param b The second point.
			@param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIRealPointSubtract) ( const AIRealPoint *a, const AIRealPoint *b, AIRealPoint *result );

	/** Tests for exact equality of two points.
			@param a The first point.
			@param b The second point.
			@param result [out] A buffer in which to return true if the points have the same
				coordinate values.
		 */
	AIAPI AIBoolean (*AIRealPointEqual) ( const AIRealPoint *a, const AIRealPoint *b );

	/** Tests whether two points are within a specified square proximity of each other.
		This is true if an axis-aligned, closed rectangle of a given tolerance
		can be placed such that it can contain the two points.
			@param a The first point.
			@param b The second point.
			@param tolerance The proximity value, the maximum allowed distance between
				the X and Y coordinates of the points.
			@param result [out] A buffer in which to return true if the points can be
				contained.
		*/
	AIAPI AIBoolean (*AIRealPointClose) ( const AIRealPoint *a, const AIRealPoint *b, AIReal tolerance );

	/** Computes the angle made by the vector \c ab with the X-axis.
			@param a The first point.
			@param b The second point.
			@return The result, in radians.
		*/
	AIAPI AIReal (*AIRealPointAngle) ( const AIRealPoint *a, const AIRealPoint *b );

	/** Computes the length of the vector \c ab. The result is always positive.
			@param a The first point.
			@param b The second point.
			@return The result.
		*/
	AIAPI AIReal (*AIRealPointLength) ( const AIRealPoint *a, const AIRealPoint *b );

	/** Computes the location of a point a given distance and angle from the page origin.
			@param length The distance.
			@param angle The angle in radians, counter-clockwise with respect to the X axis.
			@param result [out] A buffer in which to return the result.
	 */
	AIAPI void (*AIRealPointLengthAngle) ( AIReal length, AIReal angle, AIRealPoint *result );

	/** Computes the location of a point between two points by interpolating new
		coordinate values between the corresponding coordinates of the points.
		The result is <code>a * t + b * (1-t)</code>
			@param a The first point.
			@param b The second point.
			@param t A percentage of (b-a), expressed as a number between 0 and 1.
			@param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIRealPointInterpolate) ( const AIRealPoint *a, const AIRealPoint *b, AIReal t, AIRealPoint *result );

	/** Sets the coordinate values in a rectangle.  (In the Illustrator
		art coordinate system, the origin, (0, 0), is at the bottom left corner
		of a page. X and Y values increase upward and to the right.)
			@param a The rectangle object.
			@param left The left side location..
			@param top The top side location.
			@param right The right side location.
			@param bottom The bottom side location.
		*/
	AIAPI void (*AIRealRectSet) ( AIRealRect *a, AIReal left, AIReal top, AIReal right, AIReal bottom );

	/** Tests whether two rectangles equal (have the same coordinate values).
		Uses an inexact equality test to account for floating-point errors.
			@param a The first rectangle.
			@param b The second rectangle.
		    @return True if the rectangles are equal.
		*/
	AIAPI AIBoolean (*AIRealRectEqual) ( const AIRealRect *a, const AIRealRect *b );

	/** Tests whether a rectangle is empty (invalid).
		A rectangle is invalid if the right edge is equal to or
		less than the left edge, or the top edge is equal to or
		less than the bottom edge.
			@param a The rectangle.
			@return True if the rectangle is empty.
		*/
	AIAPI AIBoolean (*AIRealRectEmpty) ( const AIRealRect *a );

	/**	Moves the edges of a rectangle in or out by a uniform amount.
		Positive values for \c h or \c v move the corresponding sides in,
		negative values move the sides out.
			@param a The rectangle.
			@param h The number of document points to move the edges in or out horizontally.
			@param v The number of document points to move the edges in or out vertically.
		*/
	AIAPI void (*AIRealRectInset) ( AIRealRect *a, AIReal h, AIReal v );

	/**	Moves a rectangle by adding given values to the sides. Positive values
		for \c h or \c v move the corresponding rectangle up or right,
		negative values move it down or left.
			@param a The rectangle.
			@param h The number of document points to move the rectangle horizontally.
			@param v The number of document points to move the rectangle vertically.
		*/
	AIAPI void (*AIRealRectOffset) ( AIRealRect *a, AIReal h, AIReal v );

	/** Creates a new rectangle that is the union of two rectangles.
			@param a The first rectangle.
			@param b The second rectangle.
		    @param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIRealRectUnion) ( const AIRealRect *a, const AIRealRect *b, AIRealRect *result );

	/** Creates a new rectangle by enlarging a given rectangle to enclose a given point.
			@param a The point.
			@param b The rectangle.
		    @param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIRealPointUnion) ( const AIRealPoint *a, const AIRealRect *b, AIRealRect *result );

	/** Tests whether two rectangles overlap (have any points in common).
			@param a The first rectangle.
			@param b The second rectangle.
		    @return True if the rectangles overlap.
		*/
	AIAPI AIBoolean (*AIRealRectOverlap) ( const AIRealRect *a, const AIRealRect *b );

	/** Creates a new rectangle that is the intersection of two rectangles.
			@param a The first rectangle.
			@param b The second rectangle.
		    @param result [out] A buffer in which to return the result.
			@return False if the result is an empty (invalid) rectangle, true otherwise.
		*/
	AIAPI AIBoolean (*AIRealRectIntersect) ( const AIRealRect *a, const AIRealRect *b, AIRealRect *result );

	/** Tests whether one rectangle is inside (entirely contained in) another rectangle.
		Both must be open or both closed.
			@param a The first rectangle.
			@param b The second rectangle.
			@return True if the set of points contained by \c a is also contained by \c b.
		*/
	AIAPI AIBoolean (*AIRealRectInAIRealRect) ( const AIRealRect *a, const AIRealRect *b );

	/** Tests whether a point is inside a rectangle. The point is considered
		inside if it is on one of the rectangle’s sides.
			@param a The point.
			@param b The closed rectangle.
			@return True if the point is contained in the closed rectangle.
		*/
	AIAPI AIBoolean (*AIRealPointInAIRealRect) ( const AIRealPoint *a, const AIRealRect *b );

	/** Rounds rectangle coordinates to integer values such that the result
		rectangle contains the original. Does not necessarily return the smallest such
		rectangle; takes the floor of the coordinates and adds 1 to the top
		and right.
			@param a The rectangle.
		    @param result [out] A buffer in which to return the result.
	 */
	AIAPI void (*AIRealRectAlign) ( const AIRealRect *a, AIRealRect *result );

	/** Sets the scale, rotation, and translation values of a transformation matrix.
			@param m The matrix object.
			@param a New a value.
			@param b New b value.
			@param c New c value.
			@param d New d value.
			@param tx New horizontal translation value.
			@param ty New vertical translation value.
		*/
	AIAPI void (*AIRealMatrixSet) ( AIRealMatrix *m, AIReal a, AIReal b, AIReal c, AIReal d, AIReal tx, AIReal ty );

	/** Sets a transformation matrix to the identity matrix.
			@param m The matrix object.
		*/
	AIAPI void (*AIRealMatrixSetIdentity) ( AIRealMatrix *m );

	/** Tests two matrices for exact equality.
			@param m The first matrix.
			@param n The second matrix.
		    @return True if the matrices are equal.
		*/
	AIAPI AIBoolean (*AIRealMatrixEqual) ( const AIRealMatrix *m, const AIRealMatrix *n );

	/** Tests whether a transformation matrix is the identity matrix.
			@param m The matrix object.
			@return True if the matrix is the identity matrix.
		*/
	AIAPI AIBoolean (*AIRealMatrixIdentity) ( const AIRealMatrix *m );

	/** Tests whether  a matrix is singular (cannot be inverted).
			@param m The matrix object.
			@return True if the matrix is singular.
		*/
	AIAPI AIBoolean (*AIRealMatrixSingular) ( const AIRealMatrix *m );

    /**	Initializes a transformation matrix to a single translation.
			@param m The matrix object.
			@param tx New horizontal translation value in document points.
			@param ty New vertical translation value in document points.
		*/
	AIAPI void (*AIRealMatrixSetTranslate) ( AIRealMatrix *m, AIReal tx, AIReal ty );

    /**	Initializes scale values for a transformation matrix.
			@param m The matrix object.
			@param h New horizontal scale value, a percentage where 1 is 100%.
			@param v New vertical scale value, a percentage where 1 is 100%.
		*/
	AIAPI void (*AIRealMatrixSetScale) ( AIRealMatrix *m, AIReal h, AIReal v );

    /**	Initializes a transformation matrix to a single rotation.
			@param m The matrix object.
			@param angle New angle value in radians.
		*/
	AIAPI void (*AIRealMatrixSetRotate) ( AIRealMatrix *m, AIReal angle );

	/** Concatenates translation values to the existing translation in a
		transformation matrix. The matrix must be initialized first.
			@param m The matrix object.
			@param tx New horizontal translation value in document points.
			@param ty New vertical translation value in document points.
		*/
	AIAPI void (*AIRealMatrixConcatTranslate) ( AIRealMatrix *m, AIReal tx, AIReal ty );

	/** Concatenates scale values to the existing scale in a
		transformation matrix. The matrix must be initialized first.
			@param m The matrix object.
			@param h New horizontal scale value.
			@param v New vertical scale value.
		*/
	AIAPI void (*AIRealMatrixConcatScale) ( AIRealMatrix *m, AIReal h, AIReal v );

	/** Concatenates a rotation value to the existing rotation in a
		transformation matrix. The matrix must be initialized first.
			@param m The matrix object.
			@param angle New angle value in radians.
		*/
	AIAPI void (*AIRealMatrixConcatRotate) ( AIRealMatrix *m, AIReal angle );

	/** Creates a new transformation matrix by concatenating one matrix to another.
			@param m The first matrix object.
			@param n The second matrix object.
		    @param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIRealMatrixConcat) (const AIRealMatrix *m, const AIRealMatrix *n, AIRealMatrix *result );

	/** Inverts a transformation matrix.
			@param m The matrix object.
			@return 3 if the matrix could not be inverted or kNoErr on success.
		*/
	AIAPI ai::int16 (*AIRealMatrixInvert) (AIRealMatrix *m );

    /**	Transforms a point using a transformation matrix.
			@param m The matrix.
			@param a The point.
		    @param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIRealMatrixXformPoint) ( const AIRealMatrix *m, const AIRealPoint *a, AIRealPoint *result );

    /**	Converts an \c #AIReal value to an \c #AIFixed value.
			@param r The real value.
    		@return The fixed value.
		*/
	AIAPI AIFixed (*AIRealToAIFixed) ( AIReal r );

    /** Converts an \c #AIFixed value to an \c #AIReal value.
			@param f The fixed value.
    		@return The real value.
		*/
	AIAPI AIReal (*AIFixedToAIReal) ( AIFixed f );

    /**	Converts an \c #AIRealPoint value to an \c #AIFixedPoint value.
			@param r The real point.
    		@param f [out] A buffer in which to return the fixed point.
		*/
	AIAPI void (*AIRealPointToAIFixedPoint) ( const AIRealPoint *r, AIFixedPoint *f );

    /**	Converts an \c #AIFixedPoint value to an \c #AIRealPoint value.
			@param f The fixed point.
    		@param r [out] A buffer in which to return the real point.
		*/
	AIAPI void (*AIFixedPointToAIRealPoint) ( const AIFixedPoint *f, AIRealPoint *r );

    /**	Converts an \c #AIRealRect value to an \c #AIFixedRect value.
			@param r The real rectangle.
    		@param f [out] A buffer in which to return the fixed rectangle.
		*/
	AIAPI void (*AIRealRectToAIFixedRect) ( const AIRealRect *r, AIFixedRect *f );

    /**	Converts an \c #AIFixedRect value to an \c #AIRealRect value.
			@param f The fixed rectangle.
    		@param r [out] A buffer in which to return the real rectangle.
		*/
	AIAPI void (*AIFixedRectToAIRealRect) ( const AIFixedRect *f, AIRealRect *r );

    /**	Converts an \c #AIRealMatrix value to an \c #AIFixedMatrix value.
			@param r The real matrix.
    		@param f [out] A buffer in which to return the fixed matrix.
		*/
	AIAPI void (*AIRealMatrixToAIFixedMatrix) ( const AIRealMatrix *r, AIFixedMatrix *f );

    /**	Converts an \c #AIFixedMatrix value to an \c #AIRealMatrix value.
			@param f The fixed matrix.
    		@param r [out] A buffer in which to return the real matrix.
		*/
	AIAPI void (*AIFixedMatrixToAIRealMatrix) ( const AIFixedMatrix *f, AIRealMatrix *r );


//	AIAPI void (*AIFloatMatrixToAIRealMatrix) ( const AIFloatMatrix *f, AIRealMatrix *r );

	AIAPI void (*AIFloatMatrixToAIRealMatrix) ( const AIFloatMatrix *f, AIRealMatrix *r );

	
	AIAPI void (*AIFloatPointToAIRealPoint) ( const AIFloatPoint *f, AIRealPoint *r );
	
	
	
	/** Tests whether an \c #AIReal value is \c #kAIRealUnknown,
		the special value Illustrator uses to represent unknown quantities.
		This is sometimes used as a parameter to signal
		a special condition; for example, use of a default value.
			@param r The real number.
			@return True if the value is equal to  \c #kAIRealUnknown.
		*/


	AIAPI AIBoolean (*IsAIRealUnknown) ( AIReal r );

	/** Tests whether an \c #AIReal value is \c #kAIRealUnknown ("not a number").
		This constant is used for mathematically undefined values such as 0/0.
			@param r The real number.
			@return True if the value is equal to \c #kAIRealUnknown.
		*/
	AIAPI AIBoolean (*AIRealIsNAN) ( AIReal r );

	/** Tests whether two real numbers are within a percentage of one another.
			@param a The first number.
			@param b The second number.
			@param percent A number between 0 and 1, where 1.0 is 100%.
			@return For <code>a > b</code>, true if <code>abs(a) - abs(b) < abs(b) * percent</code>.
				<br>For <code>b > a</code>, true if <code>abs(a) < abs(b) * percent</code>.
		*/
	AIAPI AIBoolean (*AlmostEqual) (const AIReal a, const AIReal b, const AIReal percent);

	/** Tests whether two real numbers are within a tolerance of one another.
			@param a The first number.
			@param b The second number.
			@param tolerance The tolerance.
			@return True if <code>abs(a-b) <= tolerance</code>
		*/
	AIAPI AIBoolean (*EqualWithinTol) (const AIReal a, const AIReal b, const AIReal tolerance);

    /**	Retrieves the translation values from a transformation matrix.
			@param m The matrix.
			@param tx [out] A buffer in which to return the horizontal translation value.
			@param ty [out] A buffer in which to return the vertical translation value.
		*/
	AIAPI void (*AIRealMatrixGetTranslate) ( const AIRealMatrix *m, AIReal *tx, AIReal *ty );

    /**	Retrieves the scaling values from a transformation matrix.
			@param m The matrix.
			@param h [out] A buffer in which to return the horizontal scaling value.
			@param v [out] A buffer in which to return the vertical scaling value.
		*/
	AIAPI void (*AIRealMatrixGetScale) ( const AIRealMatrix *m, AIReal *h, AIReal *v );

    /**	Retrieves the angle of rotation from a transformation matrix.
			@param m The matrix.
			@param angle [out] A buffer in which to return the angle in radians.
		*/
	AIAPI void (*AIRealMatrixGetRotate) ( const AIRealMatrix *m, AIReal *angle );

	/** Creates a new \c #AIDoubleRect rectangle that is the union
		of two \c #AIDoubleRect rectangles.
			@param a The first rectangle.
			@param b The second rectangle.
		    @param result [out] A buffer in which to return the result.
		*/
	AIAPI void (*AIDoubleRectUnion) ( const AIDoubleRect *a, const AIDoubleRect *b, AIDoubleRect *result );

	/** Restricts an angle to a given range.
		@param angle		The angle to be restricted in radians.
		@param startAngle	The beginning of the range in radians.
							For startAngle=n, the range is [n, (n + 2 * pi)).
		@return The restricted angle.
	*/
	AIAPI AIReal(*RestrictAngleToRange)(AIReal angle, AIReal startAngle);
} AIRealMathSuite;


#include "AIHeaderEnd.h"


#endif
