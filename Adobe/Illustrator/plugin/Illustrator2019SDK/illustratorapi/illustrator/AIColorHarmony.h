#ifndef __AIColorHarmony__
#define __AIColorHarmony__
/*
 *        Name:	AIColorHarmony.h
 *      Author:
 *        Date:
 *     Purpose:	Suite for other plug-ins to access Adobe Illustrator Color Harmony dialogs and functionality.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1990-2007 Adobe Systems Incorporated.
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

#ifndef __AISwatchList__
#include "AISwatchList.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIColorHarmony.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIColorHarmonySuite			"AI Color Harmony Suite"
#define kAIColorHarmonySuiteVersion3	AIAPI_VERSION(3)
#define kAIColorHarmonySuiteVersion		kAIColorHarmonySuiteVersion3
#define kAIColorHarmonyVersion			kAIColorHarmonySuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

// New in Illustrator 13.0

/** @ingroup Suites
	These functions allow you to use the three Color Harmony dialogs:
		\li The Color Guide, a floating dialog (palette) that displays a single color scheme.
		\li The Color Harmony modal dialog that allows a user to modify color schemes and
			harmony rules and to recolorize art.
		\li The Variations modal dialog that applies variations of a single color scheme
			 to the selected art (and provides access to the Color Harmony dialog.)
			 The Variations dialog is currently an unsupported engineering prototype and
			 should not be displayed.  

	These dialogs share the concept of a current \e color \e scheme, which is a set of colors with
	various rules controlling how the other colors in the set are adjusted when one of the colors
	is changed. A color scheme can be associated with a swatch group, so that when the color
	scheme is changed, the swatch group is redefined (see the #AISwatchGroupSuite.)

	The Color Harmony dialog has two panels that can be displayed side-by-side, a primary panel
	on the left side that is always open, and a storage panel on the right that can be closed.
	The left side can show the Edit panel, which allows you to edit multiple colors in parallel,
	or the Assign panel (when artwork containing colors is selected), which allows precise control
	over how the colors of the scheme are used to replace the original colors of the selected artwork.

	The modal dialogs can modify the document art and the contents of the swatches palette.
	Upon return from invoking one of these dialogs, you must not assume that the art or swatch
	content is unchanged. Although you can control some of the initial state of the dialog,
	it is possible for the user to make changes to state that you initialized.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIColorHarmonySuite and \c #kAIColorHarmonyVersion.
*/
typedef struct
{
	/** Retrieves the swatch group for the current document that is currently
		associated with the Color Harmony dialogs, if any.
		(Note that this function returns an object value, not an error code.)
			@return The swatch group object, or \c NULL if there is no active
				document.
		*/
	AIAPI AISwatchGroupRef (*GetCurrentSwatchGroup) ( void );

	/** Associates the current color scheme with a swatch group, setting the scheme's colors
		to those in the swatch group. Does not show any dialogs or modify any art, but if the
		Color Guide palette is visible,	it is refreshed.
			@param swatchGroup The swatch group object.
			@return The error \c #kBadParameterErr if the swatch group
				 does not belong to the current document's swatch list.
		*/
	AIAPI AIErr (*SetCurrentSwatchGroup) ( AISwatchGroupRef swatchGroup );

	/** Shows the Color Guide palette, displaying the current color scheme. */
	AIAPI AIErr (*ShowColorGuide) ( void );

	/** Reports whether the Color Guide palette is currently shown, that is,
		the palette has been created and the containing dialog is visible. 
		(Note that this function returns a boolean value, not an error code.)
			@return True if the palette is shown, false otherwise.
			@see \c #ADMDialogSuite10::IsVisible(). 
		*/
	AIAPI AIBoolean (*IsColorGuideVisible) ( void );

	/** Shows the Color Harmony modal dialog with default settings (typically
		what was last shown). The current color scheme is whatever colors
		are currently or were last shown in the Color Guide palette.
			@param loadAllDocumentColorGroups When true, loads and displays color
				schemes for all swatch groups in the current document.
				When false, loads and displays only the swatch groups that are
				selected in the Swatches palette. If this is true and there are
				no color groups in the current document, or if it is false and
				no swatch groups are selected, then the Storage panel is empty.
		*/
	AIAPI AIErr (*ShowHarmonyDialog) ( ASBoolean loadAllDocumentColorGroups );

	/** Shows the Color Harmony modal dialog with a given swatch group loaded as the only color scheme.
			@param swatchGroup The swatch group object.
			@param forRecolor When true, if some art is selected, the Assign panel is active,
				the Recolor Art option is checked, and the original colors are reduced
				to the number of colors in the swatch group.
				<br>When false, The Edit panel is active (in most recent state),
					and the Storage panel is closed.
			@note Upon return, the swatch group may have been redefined, renamed, or otherwise modified.
		*/
	AIAPI AIErr (*ShowWithColorGroup) ( AISwatchGroupRef swatchGroup, ASBoolean forRecolor );

	/** Shows the Color Harmony modal dialog, loading schemes for specific swatch groups.
			@param swatchGroupIndices Pointer to an array of 0-based index positions for
				the swatch groups. See \c  #AISwatchGroupSuite::GetNthSwatchGroup().
			@param ctSwatchGroups The size of the index array.
			@param makeCurrent A 0-based index position in the index array. The color scheme
				for that swatch group becomes current. In the range <code>[0..ctSwatchGroups]</code>.
				Note that this is an index into the array of indices, \e not an index into the swatch list.
			@param showStorage True to open the Storage panel.
		*/
	AIAPI AIErr (*ShowWithMultipleColorGroups) ( int *swatchGroupIndices, int ctSwatchGroups, int makeCurrent, ASBoolean showStorage );

	/** Shows the Color Harmony modal dialog with the Assign panel active, the Recolor Art option checked,
		all the colors collected into the same bucket (row), and a given color loaded into the new color.
		The mapping method is initialized to Scale Tints.
			@param tintColor The initial new color.
			@param includeWhite When true, includes process white. (Always includes black and grays.)
		 */
	AIAPI AIErr (*ShowToTintArt) ( const AIColor &tintColor, ASBoolean includeWhite );

	/** Shows the Color Harmony modal dialog with the Assign panel active,
		the Recolor Art option checked, each color from the original art
		in its own bucket (color row), all the buckets active, and all the new colors
		set to the same as the original color and loaded into one scheme.
 		If the user saves the scheme immediately to the Swatches palette, it
 		will create a color group containing all the colors in the selected art.
 		This can also be used as a starting point for fine-tuning individual art colors.
			@param combineTints True to load all tints of the same global or spot color into the
				same bucket, and set the mapping method to Scale Tints. False to load each tint into
				its own bucket and set the mapping method to Exact Colors.
		*/
	AIAPI AIErr (*ShowToExtractArtColors) ( ASBoolean combineTints );

	/** Sets the base color of the Color Guide palette. The base color is the color from
		which the displayed harmony colors are derived. The harmony rule display and
		color grid update to reflect the new base color.
		
		Generally, if you set the current path style you should also set the base color.
		The Swatches palette, Color palette, and Color Picker all set both the current path style and
		the Color Guide's base color. Selection changes do not change the base color.
			@param color The new base color.
		*/
	AIAPI AIErr (*SetColorGuideBaseColor) ( const AIColor *color );

} AIColorHarmonySuite;


#include "AIHeaderEnd.h"

#endif
