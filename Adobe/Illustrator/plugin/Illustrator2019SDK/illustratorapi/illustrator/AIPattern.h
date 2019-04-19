#ifndef __AIPattern__
#define __AIPattern__

/*
 *        Name:	AIPattern.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Pattern Fill Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2010 Adobe Systems Incorporated.
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


/** @file AIPattern.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIPatternSuite				"AI Pattern Suite"
#define kAIPatternSuiteVersion10		AIAPI_VERSION(10)
#define kAIPatternSuiteVersion		kAIPatternSuiteVersion10
#define kAIPatternVersion			kAIPatternSuiteVersion

/** @ingroup Notifiers
	See \c #AIPatternSuite */
#define kAIArtPatternChangedNotifier		"AI Art Pattern Changed Notifier"


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Prototype for an iteration callback function.
	See \c #AIPatternSuite::IteratePattern().
		@param art The current generated art object.
		@return Nothing.
	*/
typedef void (*AIPatternProcPtr)(AIArtHandle art);

/** Pointer to a user-defined iteration callback procedure. */
typedef AIPatternProcPtr AIPatternUPP;

/** Convenience macro  to invokes a developer-defined routine for an art object.   */
#define CallAIPatternProc(userRoutine, art)		\
		(*(userRoutine))((art))
/** Convenience macro to cast a developer-defined routine
	to a pattern callback procedure. For example:
	@verbatim
void MyUserProc(AIArtHandle art);
AIArtHandle group;

AIPatternUPP myUserProcUPP = NewAIPatternProc(MyUserProc);
CallAIPatternProc(myUserProcUPP, group);
	@endverbatim
*/
#define NewAIPatternProc(userRoutine)		\
		(AIPatternUPP)(userRoutine)


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides functions that allow you to create, delete, and modify
	\e patterns. Illustrator uses patterns to fill or stroke with a repeating tile
	of art objects, which can be transformed before painting.

	\li A pattern \e definition is the artwork that defines the pattern tile.
		It is a	group of art objects where the backmost object is a square
		that defines the size of the tile. The square must be parallel
		to the X and Y axes.

	\li Instance parameters, in an \c #AIPatternStyle structure, define
		how a pattern is used to paint a particular instance of a fill or stroke.
		A transformation matrix is used to position the pattern for the
		painting operation.

	Each document keeps a list of associated patterns.	To copy a pattern from another
	document into the current document, put the pattern object into an \c AIColor structure
	and use \c #AIPathStyleSuite::RetargetForCurrentDoc().

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPatternSuite and \c #kAIPatternVersion.
 */
typedef struct {

	/** Creates and initialized a new pattern object. Pass the returned reference
		to \c #SetPatternName() and \c #SetPatternArt() to set the name and source art.
			@param newPattern [out] A buffer in which to return the new pattern object.
		*/
	AIAPI AIErr (*NewPattern) ( AIPatternHandle *newPattern );

	/** Deletes a pattern from the current document. If the pattern is used
		for an objectís fill, the fill becomes black.
			@param pattern The pattern object.
		*/
	AIAPI AIErr (*DeletePattern) ( AIPatternHandle pattern );

	/** Creates a copy of the pattern source artwork and places it
		into the current document at the center of the current view,
		in the current layer and insertion group. This is the equivalent
		of using the Paste command.
			@param pattern The pattern object.
			@return The error \c #kUntouchableLayerErr if the current layer or
				current insertion group is locked or hidden.
		*/
	AIAPI AIErr (*GetPattern) ( AIPatternHandle pattern );

	/** Collects the selected artwork in the current document and makes it the
		source art for a pattern.

		The selected artwork must be usable as a pattern.
		It can be any art object whose type is \c kGroupArt, as long as the
		bottom object is a bounding rectangle with no fill and no stroke,
		the size of the tile, parallel to the X and Y axes.
			@param pattern The pattern object.
			@return An error (non-zero) if the current selection is not usable as a pattern.
		*/
	AIAPI AIErr (*SetPattern) ( AIPatternHandle pattern );

	/** Gets the number of patterns available to the current document.
		Use with \c #GetNthPattern() to iterate through all patterns.
			@param count [out] A buffer in which to return the number of patterns.
		*/
	AIAPI AIErr (*CountPatterns) ( ai::int32 *count );

	/** Retrieves a pattern reference by index position.
		Use with \c #CountPatterns() to iterate through all patterns.
			@param n The 0-based position index.
			@param pattern [out] A buffer in which to return the pattern object.
			@return The error \c #kBadParameterErr if the index is out of range.
		*/
	AIAPI AIErr (*GetNthPattern) ( ai::int32 n, AIPatternHandle *pattern );

	/** Retrieves the art object (of type \c #kGroupArt) that defines
		the source art for a pattern.
			@param pattern The pattern object.
			@param art [out] A buffer in which to return the art object.
		*/
	AIAPI AIErr (*GetPatternArt) ( AIPatternHandle pattern, AIArtHandle *art );

	/** Sets the source art for a pattern.
			@param pattern The pattern object.
			@param art The new source art, of type \c #kGroupArt. The backmost
				object of the group must be a bounding rectangle with no fill and
				no stroke, to be used in tiling the pattern.
			@return An error (non-zero) if the specified art is not usable as a pattern.
		*/
	AIAPI AIErr (*SetPatternArt) ( AIPatternHandle pattern, AIArtHandle art );

	/** Retrieves the name of a pattern.
			@param pattern The pattern object.
			@param name [out] A buffer in which to return the name string.
		*/
	AIAPI AIErr (*GetPatternName) ( AIPatternHandle pattern, ai::UnicodeString& name );

	/** Sets the name of a pattern. Pattern names must be unique within the
		global pattern list.
			@param pattern The pattern object.
			@param name	The new name.
			@see \c #NewPatternName()
		*/
	AIAPI AIErr (*SetPatternName) ( AIPatternHandle pattern, const ai::UnicodeString& name );

	/** Retrieves a pattern by name.
			@param name The name.
			@param pattern [out] A buffer in which to return the pattern object.
			@return The error \c #kNameNotFoundErr if there is no pattern
				with the given name.
		*/
	AIAPI AIErr (*GetPatternByName) ( const ai::UnicodeString& name, AIPatternHandle *pattern );

	/**	Renders a path filled with a pattern. Breaks up the specified artwork into tiles
		the size of its pattern, and, for each tile, generates any artwork needed to draw
		that tile on the page. Passes the generated artwork to a procedure that you define
		for further processing.
		   @param art The path art object.
		   @param style	 A path style with a pattern fill.
		   @param proc The developer-defined callback procedure.
		*/
	AIAPI AIErr (*IteratePattern) ( AIArtHandle art, AIPathStyle *style, AIPatternProcPtr proc );

	/** Creates a unique name for a pattern, which can be passed to \c #SetPatternName().
			@param newName The base name. The string is modified in place to create a unique name.
				\li If no existing pattern has this name, it is returned.
				\li If a pattern already has this name, appends a numeric value to the string
					or increments the current numeric end value to make the name unique.
		*/
	AIAPI AIErr (*NewPatternName) ( ai::UnicodeString& newName );

	/** Retrieves the tile bounds for a pattern.
			@param pattern The pattern object.
			@param bounds [out] A buffer in which to return the bounding rectangle.
		*/
	AIAPI AIErr (*GetPatternTileBounds) ( AIPatternHandle pattern, AIRealRectPtr bounds );

	/** Reports whether a pattern object references a valid pattern in the
		current document.
		(Note that this function returns a boolean value, not an error code.)
			@param pattern The pattern object.
			@return True if the pattern object is valid.
		*/
	AIAPI AIBoolean (*ValidatePattern) ( AIPatternHandle pattern );

	AIAPI AIErr (*EnterPatternEditMode) (AIPatternHandle pattern);

	AIAPI AIErr (*EndPatternEditMode) ( AIPatternHandle pattern, AIBoolean updatePattern );

	/** Reports whether PatternEditMode is currently active, either globally or on a specified pattern.
		(Note that this function returns a boolean value, not an error code.)
		@param patternUnderEdit [optional, in/out] if non-null and pointing to a non-null value on input, then
									the function returns true only if that pattern is being edited
									if null on input or pointing to a null value on input, then this
									function returns true if ANY pattern is being edited, and returns
									that pattern in this pointer
		@param isolatedPatternArt [optional, out] if non-null, returns the art object that will be used to
									create the new pattern definition upon exit from PatternEditMode
									(May be either a plugin group or a group. If it is a plugin group,
									the plugin group is responsible for knowing how to redefine the
									pattern. If it is a group, the group will become the new pattern art.)
	 */
	AIAPI AIBoolean (*GetPatternEditMode) ( AIPatternHandle *patternUnderEdit, AIArtHandle *isolatedPatternArt );
	
	
} AIPatternSuite;


#include "AIHeaderEnd.h"


#endif
