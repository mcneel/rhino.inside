#ifndef __AIPathfinder__
#define __AIPathfinder__

/*
 *        Name:	AIPathfinder.h
 *   $Revision: 7 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Pathfinder Suite.
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

#ifndef __AIFilter__
#include "AIFilter.h"
#endif

#ifndef __AIMenu__
#include "AIMenu.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif


#include "AIHeaderBegin.h"


/** @file AIPathfinder.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/
/** Pathfinder suite name */
#define kAIPathfinderSuite			"AI Pathfinder Suite"
/** Pathfinder suite version */
#define kAIPathfinderSuiteVersion6	AIAPI_VERSION(6)
/** Pathfinder suite name */
#define kAIPathfinderSuiteVersion	kAIPathfinderSuiteVersion6
/** Pathfinder suite version */
#define kAIPathfinderVersion		kAIPathfinderSuiteVersion

/** The default value for \c #AIOptions::ipmPrecision */
#define kDefaultPrecision				10.0
/** The default value for \c #AIOptions::removeRedundantPoints */
#define kRemoveRedundantPointsDefault	0
/** The default value for \c #AIOptions::flags \c #kExtractUnpaintedArtwork flag */
#define kExtractUnpaintedArtworkDefault	0
/** The default value for the \c #AIOptions::flags \c #kAllowEmptyOutput flag */
#define kAllowEmptyOutputDefault		0
/** The default value for the \c #AIOptions::flags #kIgnoreEvenOddFillRule flag */
#define kIgnoreEvenOddFillRuleDefault	0

/** The default value for \c #AIMixParameters::softRate */
#define kSoftRateDefault 				0.5
/** The default value for \c #AIMixParameters::convertCustomColors */
#define kMixConvertCustomColorsDefault 	1

// Trap parameters
/** The default value for \c #AITrapParameters::trapThickness */
#define kTrapThicknessDefault			0.25
/** The default value for \c #AITrapParameters::heightWidthAspectRatio */
#define kHeightWidthAspectRatioDefault 	1.0
/** The default value for \c #AITrapParameters::trapTint */
#define kTrapTintDefault 				0.4
/** The default value for \c #AITrapParameters::maximumTint */
#define kMaximumTintDefault 			1.0
/** The default value for \c #AITrapParameters::tintTolerance  */
#define kTintToleranceDefault 			0.05
/** The default value for \c #AITrapParameters::reverseTrap  */
#define kReverseTrapDefault				0
/** The default value for \c #AITrapParameters::convertCustomColors  */
#define kTrapConvertCustomColorsDefault	0


/** The number of points in a micron. */
#define pointsPerMicron (72.0 / 25400.0)

/** Flag values for \c #AIOptions::flags */
enum AIOptionsFlagValues {
	/** When set, remove unpainted artwork from the result of processing. */
	kExtractUnpaintedArtwork	= 0x00001,
	/** When set, these functions can produce empty output: <br>
		\c #AIPathfinderSuite::DoBackMinusFrontEffect(),
		\c #AIPathfinderSuite::DoFrontMinusBackEffect(),
		\c #AIPathfinderSuite::DoIntersectEffect(),
		\c #AIPathfinderSuite::DoExcludeEffect() */
	kAllowEmptyOutput			= 0x10000,
	/** When set, assume that all paths use the non-zero fill rule rather
		than the even-odd fill rule.  */
	kIgnoreEvenOddFillRule		= 0x20000,
	/** When set, suppresses the progress report during a pathfinder operation.
		Available in AI 13 and later. */
	kSuppressProgressDialog		= 0x40000,
	/** When set, result objects are deselected.
		Available in AI 13 and later. */
	kDeselectResultArts			= 0x80000

};

/*******************************************************************************
 **
 ** Types
 **
 **/

/** Convenience type definition. */
typedef double			dbl;

/** Options that control how pathfinder operations are performed. */
typedef struct {
	/** Pathfinding precision, in microns.
		The number of microns in a point is given by \c #pointsPerMicron.
		Default value is \c #kDefaultPrecision */
	double				ipmPrecision;
	/** Nonzero to remove redundant points. Default value is \c #kRemoveRedundantPointsDefault */
	ai::int32				removeRedundantPoints;
	/** Option flags, a logical OR of \c #AIOptionsFlagValues. */
	ai::int32			flags;
} AIOptions;

/** Mixing parameters for \c #AIParameters */
typedef struct {
	/** The percentage of visibility in overlapping colors.
		Default value is \c #kSoftRateDefault */
	double				softRate;
	/** Nonzero to convert custom colors when mixing.
		Default value is \c #kMixConvertCustomColorsDefault */
	ai::int32				convertCustomColors;
} AIMixParameters;

/** Trapping parameters for \c #AIParameters.
	These correspond to UI values offered in the Pathfinder
	palette's Trap dialog; see user documentation for
	explanations. */
typedef struct {
	/** Trap thickness, in points.
		Default value is \c #kTrapThicknessDefault */
	double				trapThickness;
	/** Height to width aspect ratio. 1.0 is 1:1, 2.0 is 2:1.
		Default value is \c  #kHeightWidthAspectRatioDefault */
	double				heightWidthAspectRatio;
	/** Tint.
		Default value is \c  #kTrapTintDefault */
	double				trapTint;
	/** Maximum tint (default is recommended).
		Default value is \c  #kMaximumTintDefault */
	double				maximumTint;
	/** Tint tolerance (default is recommended).
		Default value is \c  #kTintToleranceDefault */
	double				tintTolerance;
	/** Nonzero to reverse trap.
		Default value is \c #kReverseTrapDefault */
	ai::int32				reverseTrap;
	/** Nonzero to convert custom colors.
		Default value is \c #kTrapConvertCustomColorsDefault */
	ai::int32				convertCustomColors;
} AITrapParameters;

/** Mixing and trapping parameters for \c #AIPathfinderData::parameters */
typedef struct {
	/** Parameters for mixing operations. */
	AIMixParameters		mixParameters;
	/** Parameters for trapping operations. */
	AITrapParameters		trapParameters;
} AIParameters;

/** Defines how to perform a pathfinder operation. */
typedef struct {
	/** Options that control how pathfinder operations are performed. */
	AIOptions				options;
	/** Parameters for mixing and trapping operations. */
	AIParameters			parameters;
	/** A pointer to an array of selected art objects on which to perform
		the operation.  */
	AIArtHandle					*fSelectedArt;
	/** The number of members of the \c fSelectedArt array. */
	ai::int32						fSelectedArtCount;
	/** Not used. Pass 0. */
	ai::int32					fAlertInfoID;
} AIPathfinderData;


/** The contents of a Pathfinder message. */
typedef struct {
	/** The message data. */
	SPMessageData				d;
	/** How to perform the pathfinder operation. */
	AIPathfinderData			pathfinderData;
} AIPathfinderMessage;

/** Compound shape modes. These control how objects inside a compound
	shape group interact with each other.  Shapes are drawn from the bottom
	object up. See \c #AIPathfinderSuite::SetShapeMode(). */
typedef enum AIShapeMode
{
	/** Applies the Unite effect to each succeeding object and the previous shape. */
	kAIShapeModeAdd = 0,
	/**  Applies the Back-minus-front effect to each succeeding object and the previous shape. */
	kAIShapeModeSubtract,
	/** Applies the Intersect effect to each succeeding object and the previous shape. */
	kAIShapeModeIntersect,
	/** Applies the Exclude effect to each succeeding object and the previous shape. */
	kAIShapeModeExclude
} AIShapeMode;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that perform operations on \e paths (art objects
	of type \c #kPathArt), which apply various effects to selected path art.
	The operations correspond to those available in the Pathfinder palette and Effect menu.

	Additional functions allow manipulation of \e compound \e shapes, plug-in groups to
	which you can apply effects. See \c #AIPluginGroupSuite. In a compound shape group,
	the bottom object in the group is drawn, then modified by the next object above it
	according to the interaction mode (\c #AIShapeMode). Each succeeding object can be added to,
	subtracted from, intersected with, or excluded from the drawing.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPathfinderSuite and \c #kAIPathfinderVersion.
	*/
typedef struct {

	/** Applies a Unite effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoUniteEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies an Intersect effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
				*/
	AIAPI AIErr (*DoIntersectEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies an Exclude effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoExcludeEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Back-minus-front effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoBackMinusFrontEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Front-minus-back effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoFrontMinusBackEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Divide effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoDivideEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Outline effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoOutlineEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Trim effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoTrimEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Merge effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoMergeEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Crop effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoCropEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Hard effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoHardEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Soft effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoSoftEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Applies a Trap effect to selected art.
			@param data The structure containing the selected art and operation parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*DoTrapEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Retrieves the parameters for the Hard effect pathfinder operation.
			@param data [out] A structure in which to return the relevant parameters.
			@param message  Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*GetHardEffectParameters) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Retrieves the parameters for the Soft effect pathfinder operation.
			@param data [out] A structure in which to return the relevant parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*GetSoftEffectParameters) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Retrieves the parameters for the Trap effect pathfinder operation.
			@param data [out] A structure in which to return the relevant parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*GetTrapEffectParameters) ( AIPathfinderData *data, AIFilterMessage *message );

	/**	Retrieves the global options for Pathfinder and Effect operations.
			@param data [out] A structure in which to return the relevant parameters.
			@param message Not used. Pass an object in which all fields are \c NULL.
		*/
	AIAPI AIErr (*GetGlobalOptions) ( AIPathfinderData *data, AIFilterMessage *message );

	// New in AI 10.0: Compound Shapes
	/** Retrieves the compound shape mode for an art plug-in group object.
		(Note that this function returns a constant value, not an error code.)
			@param art The art object, a plug-in group.
			@return The shape mode value.
		*/
	AIAPI AIShapeMode (*GetShapeMode) ( AIArtHandle art );

	/** Sets the compound shape mode for an art plug-in group object. This controls what
		effects are applied as successive objects are drawn.
			@param art The art object of type \c #kPluginArt.
 			@param The new shape mode value.
		*/
	AIAPI AIErr (*SetShapeMode) ( AIArtHandle art, AIShapeMode mode );

	/** Creates a new, empty, compound shape at a specified position in the paint order
		of the current document's art tree. Use the \c #AIPluginGroupSuite
		to add objects to the group.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] A buffer in which to return the new art object of type \c #kPluginArt.
		*/
	AIAPI AIErr (*NewCompoundShape) ( ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Reports whether an art object is a compound shape.
			@param art The art object.
			@param isCompoundShape A buffer	in which to return true if the art is a compound shape.
		*/
	AIAPI AIErr (*IsCompoundShape) ( AIArtHandle art, AIBoolean *isCompoundShape );

	/** Expands a shape into a single path or compound path, by applying the Unite effect to
		each component art object.
			@param inOutArt [in, out] A buffer containing the shape art object,
				in which to return the path object.
		*/
	AIAPI AIErr (*FlattenArt) ( AIArtHandle *inOutArt );

} AIPathfinderSuite;


#include "AIHeaderEnd.h"

#endif
