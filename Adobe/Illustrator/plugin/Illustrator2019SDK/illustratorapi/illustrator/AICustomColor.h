#ifndef __AICustomColor__
#define __AICustomColor__

/*
 *        Name:	AICustomColor.h
 *   $Revision: 10 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Custom Color Fill Suite.
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIColorConversion__
#include "AIColorConversion.h"
#endif

#include "IAIUnicodeString.h"


#include "AIHeaderBegin.h"

/** @file AICustomColor.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAICustomColorSuite					"AI Custom Color Suite"
#define kAICustomColorSuiteVersion			AIAPI_VERSION(8)
#define kAICustomColorVersion				kAICustomColorSuiteVersion

/** @ingroup Notifiers
	Sent when there is a change to custom colors, including adding a new color or
	deleting an existing one. No is data sent with the notifier, so the plug-in
	must determine what change occurred using the \c #AICustomColorSuite functions. */
#define kAIArtCustomColorChangedNotifier	"AI Art Custom Color Changed Notifier"


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Use the functions in this suite to access, create, delete, and modify
	custom colors. Custom colors represent both spot colors and global process colors.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICustomColorSuite and \c #kAICustomColorVersion.
	*/
typedef struct {

	/** Creates a new custom color. The color is not added to the swatch list.
			@param color The color specification.
			@param name The color name. The PostScript/PDF language reserves the names
				\c All, \c None, \c Cyan, \c Magenta, \c Yellow and \c Black.
				These names cannot be used for spot colors.
			@param customColor [out] A buffer in which to return the new custom color reference.
		*/
	AIAPI AIErr (*NewCustomColor) ( AICustomColor *color, const ai::UnicodeString& name, AICustomColorHandle *customColor );

	/** Deletes a custom color. Deletes it from the swatches palette if present
		and replaces any usages by the process equivalent.
			@param customColor The custom color reference. Upon return, this reference is invalid.
		*/
	AIAPI AIErr (*DeleteCustomColor) ( AICustomColorHandle customColor );

	/** Retrieves the color specification from a custom color, which includes the CMYK or
		RGB values.
			@param customColor The custom color reference.
			@param color [out] A buffer in which to return the color information.
		*/
	AIAPI AIErr (*GetCustomColor) ( AICustomColorHandle customColor, AICustomColor *color );
	/** Sets the color specification for a custom color, which includes the CMYK or
		RGB values.
			@param customColor The custom color reference.
			@param color The new color information.
	*/
	AIAPI AIErr (*SetCustomColor) ( AICustomColorHandle customColor, AICustomColor *color );

	/** Retrieves the unique name of a custom color.
				@param customColor The custom color reference.
				@param name [out] A buffer in which to return the color name.
		*/
	AIAPI AIErr (*GetCustomColorName) ( AICustomColorHandle customColor, ai::UnicodeString& name );

	/** Sets the name of a custom color.
				@param customColor The custom color reference.
				@param name The new name. The PostScript/PDF language reserves the names
				\c All, \c None, \c Cyan, \c Magenta, \c Yellow and \c Black.
				These names cannot be used for spot colors.
	*/
	AIAPI AIErr (*SetCustomColorName) ( AICustomColorHandle customColor, const ai::UnicodeString& name );

	/**  Gets the number  of defined custom colors currently available.
		Use with \c #GetNthCustomColor() to iterate through the list of custom colors.
				@param count [out] A buffer in which to return the number of custom colors.
		*/
	AIAPI AIErr (*CountCustomColors) ( ai::int32 *count );

	/**  Retrieves a custom color by position index.
		 Use with \c #CountCustomColors() to iterate through the list of custom colors.
				@param n The position index, in the range <code>[0..numColors-1]</code>.
				@param customColor [out] A buffer in which to return the custom color reference.
		*/
	AIAPI AIErr (*GetNthCustomColor) ( ai::int32 n, AICustomColorHandle *customColor );

	/**  Retrieves a custom color by name.
			@param name The name.
			@param customColor [out] A buffer in which to return the custom color reference.
		*/
	AIAPI AIErr (*GetCustomColorByName) ( const ai::UnicodeString& name,  AICustomColorHandle *customColor );

	/** Generates a unique name for a custom color If the specified base name does not already exist,
		it is returned. If the base name already exists, the function concatenates the string
		\c "\nxxx", where \c xxx is an integer, starting at 000 and incrementing as necessary
		to create a unique name. This allows you to keep track of multiple versions of the
		same color name..
			@param name [in, out] A string containing the base name. The string is modified
				in place if needed.
		*/
	AIAPI AIErr (*NewCustomColorName) ( ai::UnicodeString& name );

	/** @deprecated This function is now a no-op. An earlier version of Illustrator
		stored unique internal names for custom colors different from those displayed in the UI. */
	AIAPI AIErr (*GetCustomColorDisplayName) ( ai::UnicodeString& name );

	/**  Retrieves the custom color currently used as the registration color.
			@param customColor [out] A buffer in which to return the custom color reference.
		*/
	AIAPI AIErr (*GetCurrentRegistrationColor) ( AICustomColorHandle *customColor );

	/** Retrieves the registration color for the current document, or
		creates a new registration color if needed, using default values.
		Ignores the color and kind input parameters.
			@param customColor [out] A buffer in which to return the
				current registration color, or the new registration color.
		*/
	AIAPI AIErr (*NewRegistrationColor)(AICustomColorHandle *customColor, AIReal cyan /*red*/,
		AIReal magenta /*green*/,AIReal yellow/*blue*/, AIReal black, AICustomColorTag kind);

	/** Reports whether a custom color handle represents a valid custom
		color in the current document. (Note that this function returns a
		boolean value, not an error code.)
			@param customColor The custom color reference.
			@return True if the reference is valid.
		*/
	AIAPI AIBoolean (*ValidateCustomColor)(AICustomColorHandle customColor);
	/** Reports whether a custom color is a spot color that is used by a linked file.
		If this is the case it cannot be modified. (Note that this function returns a
		boolean value, not an error code.)
			@param customColor The custom color reference.
			@return True if the custom color is used externally.
		*/
	AIAPI AIBoolean (*HasExternalUses)(AICustomColorHandle customColor);

	/** Converts a tint of a custom color to its closest non-global approximation
		that is consistent with the document color model. For example,
		in a CMYK document, Lab and RGB based spot colors are converted
		to CMYK.
		\li If the custom color is a global process color, the returned color
		is the process
		equivalent.
		\li If the custom color is a spot color, the returned color
		is the process approximation
		of the appearance of the spot color.
		\li If the custom color is a registration color, the returned color
		is the process color used to represent the registration color.

			@param customColor  The custom color reference.
			@param tint The amount of the color used in paint, a percentage value
				in the range [0..1], where 0 is full tint and 1 is white.
			@param color [out] A buffer in which to return the converted color.
		*/
	AIAPI AIErr (*ConvertToNonGlobal)(AICustomColorHandle customColor, AIReal tint, AIColor* color);

	/** Converts a tint of a custom color to its best appearance approximation,
		a color that approximates the way the custom color looks.
			\li For global process colors, returns the process color with the given tint.
			\li For spot colors, returns a color that approximates the appearance of the
				tint of the spot ink.

		This differs from \c #ConvertToNonGlobal() in that the resulting color
		need not be consistent with the document color model.
			@param customColor  The custom color reference.
			@param tint The amount of the color used in paint, a percentage value
				in the range [[0..1], where 0 is full tint and 1 is white.
			@param space [out] A buffer in which to return the color space, a
				\c #AIColorConversionSpaceValue.
			@param color [out] A buffer in which to return the converted color.
		*/
	AIAPI AIErr (*GetAppearanceApproximation)(AICustomColorHandle customColor, AIReal tint,
			ai::int32* space, AIFloatSampleComponent* values);

	/** Sets the book id for global spot color. If color is not spot then this method 
		returns an error.
			@param customColor  The custom color reference.
			@param bookid The custom color source book id.
	*/	
	AIAPI AIErr (*SetCustomColorBookID)(AICustomColorHandle customColor, ai::int32 bookid);


	/** Gets the source book id for global spot color. If color is not spot then this 
		method returns -1 
			@param customColor  The custom color reference.
	*/
	AIAPI ai::int32 (*GetCustomColorBookID)(AICustomColorHandle customColor);


} AICustomColorSuite;


#include "AIHeaderEnd.h"


#endif
