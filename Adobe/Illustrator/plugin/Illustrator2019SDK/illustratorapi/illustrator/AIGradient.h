#ifndef __AIGradient__
#define __AIGradient__

/*
 *        Name:	AIGradient.h
 *   $Revision: 11 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Gradient Fill Suite.
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

#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIGradient.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/
/** Gradient suite name */
#define kAIGradientSuite			"AI Gradient Suite"
/** Gradient suite version */
#define kAIGradientSuiteVersion9	AIAPI_VERSION(9)
/** Gradient suite version */
#define kAIGradientSuiteVersion		kAIGradientSuiteVersion9
/** Gradient suite version */
#define kAIGradientVersion			kAIGradientSuiteVersion

/** @ingroup Notifiers
	Sent when a gradient (blend) has changed. See \c #AIGradientSuite.*/
#define kAIArtGradientChangedNotifier		"AI Art Gradient Changed Notifier"

/** @ingroup Error Codes
	*/
#define kMaxSpotChannelsExceededErr	'xSPT'

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Prototype for \c setGray callback; see \c #AIGradientSuite::IterateGradient().
	Your implementation can use this to modify gray values in a generated
	intermediate path object.
		@param g The grayscale color value of this segment. */
typedef void (*AIGradientSetGrayProcPtr)(AIReal g);
/**  Value type for the \c #AIGradientProcs::setGray iteration callback. */
typedef AIGradientSetGrayProcPtr AIGradientSetGrayUPP;
/**  A convenience macro for the \c #AIGradientProcs::setGray iteration callback. */
#define CallAIGradientSetGrayProc(userRoutine, g)		\
		(*(userRoutine))((g))
/** A convenience macro for the \c #AIGradientProcs::setGray iteration callback. */
#define NewAIGradientSetGrayProc(userRoutine)		\
		(AIGradientSetGrayUPP)(userRoutine)

/** Prototype for \c #AIGradientProcs::setCMYK callback; see \c #AIGradientSuite::IterateGradient().
	Your implementation can use this to modify CMYK color values in a generated
	intermediate path object.
		@param c The cyan color value of this segment.
		@param m The magenta color value of this segment.
		@param y The yellow color value of this segment.
		@param k The black color value of this segment.
	*/
typedef void (*AIGradientSetCMYKProcPtr)(AIReal c, AIReal m, AIReal y, AIReal k);
/**  Value type for the \c #AIGradientProcs::setCMYK iteration callback. */
typedef AIGradientSetCMYKProcPtr AIGradientSetCMYKUPP;
/**  A convenience macro for the \c #AIGradientProcs::setCMYK iteration callback. */
#define CallAIGradientSetCMYKProc(userRoutine, c, m, y, k)		\
		(*(userRoutine))((c), (m), (y), (k))
/** A convenience macro for the \c #AIGradientProcs::setCMYK iteration callback. */
#define NewAIGradientSetCMYKProc(userRoutine)		\
		(AIGradientSetCMYKUPP)(userRoutine)

/** Prototype for \c #AIGradientProcs::setColor callback; see \c #AIGradientSuite::IterateGradient().
	Your implementation can use this to modify color values in a generated
	intermediate path object.
		@param c A pointer to the color of this segment.
	*/
typedef void (*AIGradientSetColorProcPtr)(AIColor* c);
/** Value type for the \c #AIGradientProcs::setColor iteration callback.  */
typedef AIGradientSetColorProcPtr AIGradientSetColorUPP;
/** A convenience macro for the \c #AIGradientProcs::setColor iteration callback. */
#define CallAIGradientSetColorProc(userRoutine, c)		\
		(*(userRoutine))((c))
/** A convenience macro for the \c #AIGradientProcs::setColor iteration callback.*/
#define NewAIGradientSetColorProc(userRoutine)		\
		(AIGradientSetColorUPP)(userRoutine)

/**  Prototype for \c #AIGradientProcs::beginFill callback; see \c #AIGradientSuite::IterateGradient().
	This is called before each path-creation iteration. */
typedef void (*AIGradientBeginFillProcPtr)(void);
/** Value type for the \c #AIGradientProcs::beginFill iteration callback. */
typedef AIGradientBeginFillProcPtr AIGradientBeginFillUPP;
/** A convenience macro for the \c #AIGradientProcs::beginFill iteration callback. */
#define CallAIGradientBeginFillProc(userRoutine)		\
		(*(userRoutine))()
/**  A convenience macro for the \c #AIGradientProcs::beginFill iteration callback. */
#define NewAIGradientBeginFillProc(userRoutine)		\
		(AIGradientBeginFillUPP)(userRoutine)

/** Prototype for \c #AIGradientProcs::endFill callback; see \c #AIGradientSuite::IterateGradient().
	This is called after each path-creation iteration. */
typedef void (*AIGradientEndFillProcPtr)(void);
/** Pointer to \c #AIGradientEndFillProcPtr for \c endFill iteration callback. */
typedef AIGradientEndFillProcPtr AIGradientEndFillUPP;
/** A convenience macro for the \c #AIGradientProcs::endFill iteration callback. */
#define CallAIGradientEndFillProc(userRoutine)		\
		(*(userRoutine))()
/** A convenience macro for the \c #AIGradientProcs::endFill iteration callback. */
#define NewAIGradientEndFillProc(userRoutine)		\
		(AIGradientEndFillUPP)(userRoutine)

/** Prototype for \c #AIGradientProcs::moveTo callback; see \c #AIGradientSuite::IterateGradient().
	Your implementation can use this to modify position values for the first point in a
	segment of a generated intermediate path object.
		@param x The horizontal coordinate value of the start point for this segment.
		@param y The vertical coordinate value of the start point for this segment.
	*/
typedef void (*AIGradientMoveToProcPtr)(AIReal x, AIReal y);
/** Value type for the \c #AIGradientProcs::moveTo iteration callback. */
typedef AIGradientMoveToProcPtr AIGradientMoveToUPP;
/** A convenience macro for the \c #AIGradientProcs::moveTo iteration callback. */
#define CallAIGradientMoveToProc(userRoutine, x, y)		\
		(*(userRoutine))((x), (y))
/** A convenience macro for the \c #AIGradientProcs::moveTo iteration callback. */
#define NewAIGradientMoveToProc(userRoutine)		\
		(AIGradientMoveToUPP)(userRoutine)

/** Prototype for the \c #AIGradientProcs::lineTo callback; see \c #AIGradientSuite::IterateGradient().
	Your implementation can use this to modify position values for the end point in a
	segment of a generated intermediate path object.
		@param x The horizontal coordinate value of the endpoint for this segment.
 		@param y The vertical coordinate value of the endpoint for this segment.
	*/
typedef void (*AIGradientLineToProcPtr)(AIReal x, AIReal y);
/** Value type for the \c #AIGradientProcs::lineTo iteration callback. */
typedef AIGradientLineToProcPtr AIGradientLineToUPP;
/** A convenience macro for the \c #AIGradientProcs::lineTo iteration callback. */
#define CallAIGradientLineToProc(userRoutine, x, y)		\
		(*(userRoutine))((x), (y))
/** A convenience macro for the \c #AIGradientProcs::lineTo iteration callback. */
#define NewAIGradientLineToProc(userRoutine)		\
		(AIGradientLineToUPP)(userRoutine)

/** Prototype for the \c #AIGradientProcs::curveTo callback; see \c #AIGradientSuite::IterateGradient().
	Your implementation can use this to modify position values for the set of point that defines
	the curve between endpoints of a segment in a generated intermediate path object.
		@param x1 The horizontal coordinate value of the first point of this curve.
		@param y1 The vertical coordinate value of the first point of this curve.
		@param x2 The horizontal coordinate value of the second point of this curve.
		@param y2 The vertical coordinate value of the second point of this curve.
		@param x3 The horizontal coordinate value of the third point of this curve.
		@param y3 The vertical coordinate value of the third point of this curve.
    */
typedef void (*AIGradientCurveToProcPtr)(AIReal x1, AIReal y1, AIReal x2, AIReal y2, AIReal x3, AIReal y3);
/** Value type for the \c #AIGradientProcs::curveTo iteration callback. */
typedef AIGradientCurveToProcPtr AIGradientCurveToUPP;
/** A convenience macro for the \c #AIGradientProcs::curveTo iteration callback. */
#define CallAIGradientCurveToProc(userRoutine, x1, y1, x2, y2, x3, y3)		\
		(*(userRoutine))((x1), (y1), (x2), (y2), (x3), (y3))
/** A convenience macro for the \c #AIGradientProcs::curveTo iteration callback. */
#define NewAIGradientCurveToProc(userRoutine)		\
		(AIGradientCurveToUPP)(userRoutine)

/** Callback functions for \c #AIGradientSuite::IterateGradient().
	The specified callbacks are invoked with information for each
	iteration segment of the gradient.

	For example, if you select a gradient object and choose Object>Expand,
	and specify 10 paths, the plug-in uses this function to create the
	10 paths that simulate the gradient. For each of the paths:
		\li The \c setColor procedure is first called to set the color state.
		\li Then, \c beginFill is called to let the plug-in know that a new path is about to be created.
		\li Then, \c moveTo is called to let the plug-in know where the first point is.
		\li Then, a sequence of calls to either \c lineTo or \li curveTo
			builds up the path.
		\li Finally, \c endFill is called to let the plug-in know that the path is finished.

	*/
typedef struct {
	/** A procedure for modifying grayscale values in a gradient.
		Receives the grayscale color value of each iteration segment. */
	AIGradientSetGrayUPP setGray;
	/** A procedure for modifying CMYK values in a gradient.
		Receives the CMYK color values of each iteration segment*/
	AIGradientSetCMYKUPP setCMYK;
	/** A procedure for initializing the gradient iteration.
		Called at the beginning of the iteration. */
	AIGradientBeginFillUPP beginFill;
	/** A procedure for terminating the gradient iteration.
		Called at the end of the iteration. */
	AIGradientEndFillUPP endFill;
	/** A procedure to modify position values for the first point in a
	segment of a generated intermediate path object. */
	AIGradientMoveToUPP moveTo;
	/** A procedure to modify position values for the end point in a
	segment of a generated intermediate path object. */
	AIGradientLineToUPP lineTo;
	/** A procedure to modify position values for the set of point that defines
	the curve between endpoints of a segment in a generated intermediate path object. */
	AIGradientCurveToUPP curveTo;
	/** A generic procedure for modifying colors in a gradient.
		Set to \c NULL to use the more specific  \c setGray and \c setCMYK
		procedures. */
	AIGradientSetColorUPP setColor;

} AIGradientProcs;



/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides the basic definition of the \e gradient,
	a graduated blend between two or more colors. The functions
	allow you to examine or modify existing gradients, create new
	gradients, or delete existing ones.

	The gradient attributes correspond to the settings in the Gradient palette.
	A gradient has:
		\li A unique name, which is required and is used when an object
			with a gradient is saved in a file.
		\li A type, linear (\c  #kLinearGradient) or radial (\c #kRadialGradient).
		\li A gradient \e ramp, defined by a set of color \e stops. A stop is
			a point at which a color change occurs, within the ramp range of [0..100].
			The number of gradient stops is equal to the number of colors specified.
			There must be at least two. The actual colors and their positions on the
			ramp are defined with the \c #AIGradientStop structure.

	When a gradient is applied to an object, the gradient ramp is scaled to
	the length of the gradient vector. The gradient stops are from 0 to 100% of
	the length needed to fully create the gradient along the vector.

	A gradient instance applied to an art object is further defined by an
	\c #AIGradientStyle, which is part of an object's fill or stroke style.

	@see  \c #AIPathStyleSuite, \c #AIPatternSuite, \c #AICustomColorSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIGradientSuite and \c #kAIGradientVersion.
*/
typedef struct {

	/** Creates a new gradient, initializing it as a linear gradient with two stops,
		white and black. Use \c #SetGradientName() to set its name, and
		other functions such as \c #InsertGradientStop() to customize it after creation.
			@param gradient [out] A buffer in which to return the new gradient object.
	 */
	AIAPI AIErr (*NewGradient) ( AIGradientHandle *gradient );

	/** Frees the memory associated with a gradient object that is no longer needed.
		If an art object uses this gradient for its fill value, the fill color is set to black.
			@param gradient The gradient. Upon return, this reference is invalid.
	*/
	AIAPI AIErr (*DeleteGradient) ( AIGradientHandle gradient );

	/** Gets the number of available gradients . Use with \c #GetNthGradient()
		to iterate through all gradients defined in the current document.
		This can exceed the number of defined gradient swatches, as shown in
		the Swatches palette.
			@param count [out] A buffer in which to return the number of gradients.
		*/
	AIAPI AIErr (*CountGradients) ( ai::int32 *count );

	/** Retrieves a gradient by position index. Use with \c #CountGradients()
		to iterate through all available gradients.
			@param n The position index, in the range <code>[0..numGradients -1]</code>.
			@param gradient [out] A buffer in which to return the gradient object.
		*/
	AIAPI AIErr (*GetNthGradient) ( ai::int32 n, AIGradientHandle *gradient );

	/** Retrieves a gradient by its unique name.
			@param name The name.
			@param gradient [out] A buffer in which to return the gradient object.
			@return The error \c #kNameNotFoundErr if a gradient with the specified
				name is not found.
		*/
	AIAPI AIErr (*GetGradientByName) ( const ai::UnicodeString& name, AIGradientHandle *gradient );

	/** Retrieves the unique name of a gradient.
			 @param gradient The gradient object.
			 @param name [out] A buffer in which to return the name string.
		*/
	AIAPI AIErr (*GetGradientName) ( AIGradientHandle gradient, ai::UnicodeString& name );

	/** Sets the name of a gradient. You can create a unique name string using
		\c #NewGradientName().
			 @param gradient The gradient object.
			 @param name The new name string.
			 @return The error \c #kNameNotFoundErr if a gradient with the specified
				name already exists.
	 */
	AIAPI AIErr (*SetGradientName) ( AIGradientHandle gradient, const ai::UnicodeString& name );

	/**  Retrieves the type of a gradient, linear or radial.
			 @param gradient The gradient object.
			 @param type [out] A buffer in which to return the type constant, either
			 	.\c #kLinearGradient or \c #kRadialGradient.
		*/
	AIAPI AIErr (*GetGradientType) ( AIGradientHandle gradient, ai::int16 *type );

	/** Sets the type of a gradient, linear or radial.
			 @param gradient The gradient object.
			 @param type The type constant, \c #kLinearGradient or \c #kRadialGradient.
		*/
	AIAPI AIErr (*SetGradientType) ( AIGradientHandle gradient, ai::int16 type );

	/** Gets the number of stops (color transition or ramp points) in a gradient.
		There are always at least two. Use with \c #GetNthGradientStop() to iterate
		through the stops.
			@param gradient The gradient object.
			@param count [out] A buffer in which to return the number of stops.
		*/
	AIAPI AIErr (*GetGradientStopCount) ( AIGradientHandle gradient, ai::int16 *count );

	/** Retrieves a stop (color transition or ramp point) from a gradient
		by position index. Use with \c #GetGradientStopCount() to iterate through
		all stops in a gradient.
			 @param gradient The gradient object.
			 @param n The position index, in the range <code>[0..numStops -1]</code>.
			 @param stop [out] A buffer in which to return the gradient stop object.
 	*/
	AIAPI AIErr (*GetNthGradientStop) ( AIGradientHandle gradient, ai::int16 n, AIGradientStop *stop );

	/** Updates an existing stop (color transition or ramp point) in a gradient. The stop
		is specified by position index. To create a new stop, use \c #InsertGradientStop().
			 @param gradient The gradient object.
			 @param n The position index, in the range <code>[0..numStops -1]</code>.
			 @param stop A pointer to the new gradient stop object. You must retrieve this
			 	structure with \c #GetNthGradientStop() and modify it before making the call.
		*/
	AIAPI AIErr (*SetNthGradientStop) ( AIGradientHandle gradient, ai::int16 n, AIGradientStop *stop );

	/** Creates a new stop (color transition or ramp point) in a gradient.
		To modify an existing gradient stop, use \c #SetNthGradientStop().
			@param gradient The gradient object.
			@param n The position index at which to add this stop, in the range
				<code>[0..numStops]</code>. The new stop has this index, and
				the index of all later stops is incremented.
			@param stop [out] A buffer in which to return the new gradient stop object.
		*/
	AIAPI AIErr (*InsertGradientStop) ( AIGradientHandle gradient, ai::int16 n, AIGradientStop *stop );

	/** Removes a stop (color transition or ramp point) from a gradient.
		There must always be at least two stops.
			 @param gradient The gradient object.
			 @param n The position index of the stop to remove, in the range <code>[0..numStops -1]</code>.
			 @param stop [out] A buffer in which to return the gradient stop object that was removed.
 	*/
	AIAPI AIErr (*DeleteGradientStop) ( AIGradientHandle gradient, ai::int16 n, AIGradientStop *stop );

	/** Iterates over a gradient in an art object applying a set of
		developer-defined drawing routines, in order to break the gradient
		into a set of discrete paths containing solid colors, which together
		approximate the gradient.

		The artwork is broken into iteration sections along the gradient’s vector.
		Each section is a region filled with a single color, represented by a path object.

		For each section, the function generates any artwork needed to draw the object on
		the page, including a fill color, then passes the elements of the generated
		artwork to the supplied drawing procedures for further processing.
		These functions might, for example, write the information to a file
		in a particular format, or create artwork in Illustrator with the data.

			@param art The art object.
			@param style A pointer to the path style information.
			@param procs A pointer to a set of drawing procedures.
				You must create and fill this with procedures you have defined
				before making the call.
			@param iterations The number of iteration sections. Pass 0 to use
				the minimum number of iterations needed to produce a smooth
				color appearance.
		*/
	AIAPI AIErr (*IterateGradient) ( AIArtHandle art, AIPathStyle *style, AIGradientProcs *procs, ai::int16 iterations );

	/** Creates a unique name for a gradient, which can be passed to \c #SetGradientName().
			@param name The base name. The string is modified in place to create a unique name.
				\li If no existing gradient has this name, it is returned.
				\li If a gradient already has this name, a numeric value is appended
					to the string (or the existing numeric value is incremented) to make it unique.
	  */
	AIAPI AIErr (*NewGradientName) ( ai::UnicodeString& name );

	/** Reports whether a gradient uses a particular color in any stop.
			@param gradient The gradient object.
			@param color The color.
			@param matchTint When false, and if the color is a custom color,
				returns true for any tint of that color.
			@param usesColor [out] A buffer in which to return true if the color is used
				in any stop.
		*/
	AIAPI AIErr (*GradientUsesAIColor) (AIGradientHandle gradient, const AIColor *color,
										AIBoolean matchTint, AIBoolean *usesColor);

	/** Reports whether a gradient is defined for the current document.
		(Note that this function returns a boolean value, not an error code.)
			@param gradient The gradient object.
			@return True if the gradient is defined for the current document.
		*/
	AIAPI AIBoolean (*ValidateGradient) ( AIGradientHandle gradient );

	/* New in Illustrator 11.0 */

	/** Retrieves the color at a given point on a gradient ramp. If the point is
		a stop, returns the color of that stop. Otherwise, the returns an interpolated
		color between stops.
			@param gradient The gradient object.
			@param percent The point on the ramp, a percentage value in the range [0..100].
			@param color [out] A buffer in which to return the color.
		*/
	AIAPI AIErr (*GetGradientColor) ( AIGradientHandle gradient, AIReal percent, AIColor *color );

	/* New in Illustrator 14.0 */

	/** Reports whether a gradient has any transparency. 
	    This is the case if any stops have an opacity other than 1.0.
	
	    @param gradient 	The gradient object.
	    @param useAlpha [out] A buffer in which to return the result, true if the gradient has transparency, false otherwise. 
		*/
	AIAPI AIErr (*IsGradientAlphaRequired)(AIGradientHandle gradient, AIBoolean *useAlpha);
} AIGradientSuite;



#include "AIHeaderEnd.h"


#endif
