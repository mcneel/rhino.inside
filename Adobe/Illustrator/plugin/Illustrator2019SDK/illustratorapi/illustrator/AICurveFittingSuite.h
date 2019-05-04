#ifndef __AICurveFittingSuite__
#define __AICurveFittingSuite__

/*
 *        Name:	AICurveFittingSuite.h
 *     Purpose:	Adobe Illustrator bezier suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2014 Adobe Systems Incorporated.
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

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAICurveFittingSuite "AI Curve Fitting Suite"
#define kAICurveFittingSuiteVersion AIAPI_VERSION(11)
#define kAICurveFittingVersion	kAICurveFittingSuiteVersion

/** Parameter constants for \c #AICurveFittingSuite::FitTrajectoryWithPreset() */
enum AICurveFittingPreset {
	/** Preset that results in the most accurate fitting of the curve */
	kAICurveFittingAccuraterPreset,

	/** Other presets in order of decreasing accuracy/increasing smoothness */
	kAICurveFittingAccuratePreset,
	kAICurveFittingDefaultPreset,
	kAICurveFittingSmoothPreset,

	/** Preset that results in the most smooth fitting of the curve */
	kAICurveFittingSmootherPreset,

	/** Number of preset constants */
	kAICurveFittingNoOfPresets
};

/** How to enforce cuts for a sample during fitting.
Used only for the more general \c #AICurveFittingSuite::FitTrajectory() function.
Ignored for \c #AICurveFittingSuite::FitTrajectoryWithPreset() */
enum AICurveFittingCutType {
	kAICurveFittingNoCut,
	kAICurveFittingSmoothCut,
	kAICurveFittingCornerCut
};

/*******************************************************************************
 **
 **	Data Structures
 **
 **/

/** Sample consisting of position and cut type */
struct AICurveFittingTrajectorySample {
	AICurveFittingCutType cut;
	AIReal x;
	AIReal y;
};

/** Vector of /c #AICurveFittingTrajectorySample */
struct AICurveFittingTrajectorySampleVector {
	ai::int32 size;
	AICurveFittingTrajectorySample* first;
};

/** Vector of /c #AIPathSegment */
struct AICurveFittingPathSegmentVector {
	AIBoolean open;
	ai::int32 size;
	AIPathSegment* first;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions to fit a vector of sample points to a cubic Bezier
	curve.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICurveFittingSuite and \c #kAICurveFittingVersion.
	*/

struct AICurveFittingSuite {
	/** Fits a vector of sample points to a cubic Bezier curve using a preset, as opposed
	to the more general function FitTrajectory(...) below. Some, and not all, of the
	presets are equivalent to sets of parameters of the general function. There are no
	equivalent sets for presets towards the smoother end of the spectrum that use a different
	algorithm to give better results. Use the general function only when none of the provided
	presets give the required fit.

 			@param trajectory The vector of sample points. It is the client's
			responsibility to manage this vector.

 			@param preset The preset for fitting.

			@param close Whether the fitted path will be closed (true) or open (false).

			@param zoomAware True to take the the zoom factor of the document into
			account during the fitting.

			@param path [out] A buffer in which to return the vector of fitted path segments.
			Memory for this buffer is allocated internally using SPBasic->AllocateBlock. It 
			is the client's responsibility to free it using SPBasic->FreeBlock.
		*/
	AIAPI AIErr (*FitTrajectoryWithPreset)(
		AICurveFittingTrajectorySampleVector* trajectory,
		AICurveFittingPreset preset,
		AIBoolean close,
		AIBoolean zoomAware,
		AICurveFittingPathSegmentVector* path
		);

	/** Fits a vector of sample points to a cubic Bezier curve.

 			@param trajectory The vector of sample points. It is the client's
			responsibility to manage this vector.

 			@param noiseFilterDegree An even integer [0, 2, 4, ...] that determines the
			amount of noise filtering to apply. 4 is typically used, 0 means
			no filtering.

			@param cornerAngleTolerance	A real number [-1 1] equal to
			-cos(angle A in radians) such that if an angle less than A occurs in the
			trajectory, a corner is formed there.

			@param smoothnessTolerance A percentage [0 100] for the amount
			of smoothing to perform on the samples. 0 means no smoothing, 100
			is the maximum amount of smoothing.

			@param fidelityTolerance A positive number for the constant that determines
			the maximum amount by which a fitting is allowed to deviate from the sample points.

			@param path [out] A buffer in which to return the vector of fitted path segments.
			Memory for this buffer is allocated internally
			using SPBasic->AllocateBlock. It is the client's responsibility to free it
			using SPBasic->FreeBlock.
		*/
	AIAPI AIErr (*FitTrajectory)(
		AICurveFittingTrajectorySampleVector* trajectory,
		ai::int32 noiseFilterDegree,
		AIReal cornerAngleTolerance,
		AIReal smoothnessTolerance,
		AIReal fidelityTolerance,
		AICurveFittingPathSegmentVector* path
	);
};

#include "AIHeaderEnd.h"

#endif
