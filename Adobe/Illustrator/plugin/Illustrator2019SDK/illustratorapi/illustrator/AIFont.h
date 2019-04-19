/*
 *        Name:	AIFont.h
 *   $Revision: 1 $
 *      Author:	Adam Lane
 *        Date:	7/10/2002
 *     Purpose:	Adobe Illustrator Font Suite.
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

#ifndef __AIFont__
#define __AIFont__

/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "ATETypesDef.h"
#include "IAIFilePath.hpp"

#include "ATETypes.h"


#ifdef __cplusplus
using ATE::FontRef;
#endif

#include "AIHeaderBegin.h"

/** @file AIFont.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIFontSuite			"AI Font Suite"
#define kAIFontSuiteVersion6	AIAPI_VERSION(6)
#define kAIFontSuiteVersion		kAIFontSuiteVersion6
#define kAIFontVersion			kAIFontSuiteVersion


/** @ingroup Notifiers
	Sent before a font import operation is executed. See \c #AIFontSuite. */
#define kAIBeginImportCompFontNotifier "AI Begin Import CompFont Notifier"
/** @ingroup Notifiers
	Sent after a font import operation is executed. See \c #AIFontSuite.*/
#define kAIEndImportCompFontNotifier "AI End Import CompFont Notifier"

/** @ingroup Errors
	Cannot import a font. See \c #AIFontSuite. */
#define kCantImportCompFont		'!ICF'
/** @ingroup Errors
 	Glyph is not defined. See \c #AIFontSuite. */
#define kGlyphNotDefinedErr		'!Gly'

// Opaque data types
/** Opaque font key; see \c #AIFontSuite */
typedef struct __AIFontKey* AIFontKey;
/** Opaque typeface (font family) key; see \c #AIFontSuite */
typedef struct _t_AITypefaceKey* AITypefaceKey;
/** Opaque glyph set; see \c #AIFontSuite */
typedef struct _t_AIGlyphSet* AIGlyphSet;
/** Opaque glyph information; see \c #AIFontSuite */
typedef struct _t_AIGlyphInfo* AIGlyphInfo;
/** Opaque font instance; see \c #AIFontSuite */
typedef struct _t_AIFontInst* AIFontInst;
/** Opaque glyph identifier; see \c #AIFontSuite */
typedef int AIGlyphID;
/** Opaque byte code; see \c #AIFontSuite */
typedef unsigned char  AIByteCode;
/** Opaque character code; see \c #AIFontSuite */
typedef ai::uint16 AICharCode;
/** Opaque font face metrics; see \c #AIFontSuite */
typedef struct _t_AIFaceMetrics* AIFaceMetrics;
/** Not used. */
typedef struct _t_LOGFONTA* AILOGFONTA;

typedef ai::uint32 AIMacFontRef;

// Public data types
/** Font family format types */
typedef enum AIFaceFormat {
	kUnknownFormat = -1,
	kTypeOneFormat,
	kTrueTypeFormat
} AIFaceFormat;

/** Type face encodings */
typedef enum AIFaceEncoding {
	kUnknownEncoding = -1,
	kDontCareEncoding,
	kStandardEncoding,
	kSpecialEncoding
} AIFaceEncoding;

/** Type face language scripts */
typedef enum AIFaceScript {
	kNativeAIScript = -2,
	kUnknownAIScript = -1,
	kRomanAIScript = 0,
	kJapaneseAIScript = 1,
	kTraditionalChineseAIScript = 2,
	kKoreanAIScript = 3,

	kArabicAIScript = 4,
	kHebrewAIScript = 5,

	kGreekAIScript = 6,
	kCyrillicAIScript = 7,

	// the script number should be same as in Cool type Script Enum
	kDevanagariAIScript = 9,
	kGurmukhiAIScript = 10,
	kGujaratiAIScript = 11,
	kOriyaAIScript = 12,
	kBengaliAIScript = 13,
	kTamilAIScript = 14,
	kTeluguAIScript = 15,
	kKannadaAIScript = 16,
	kMalayalamAIScript = 17,
	
	kSinhaleseAIScript = 18,
	kBurmeseAIScript = 19,
	kKhmerAIScript = 20,
	kThaiAIScript = 21,
	kLaotianAIScript = 22,

	kSimplifiedChineseAIScript = 25,
	kEastEuropeanRomanAIScript = 29,
	kSymbolAIScript = 32,
	kEmojiAIScript,
	kTurkishAIScript = 81,
	kBalticAIScript = 85
} AIFaceScript;

/** MojiZume types */
enum AIMojiZumeType {
	kMojiZumeNone,
	kMojiZumeGXTrueType,
	kMojiZumePageMakerJ,
	kMojiZumeSfntATM
};

/** Font style */
struct AIFontStyle {
	/** Font retrieval key */
	AIFontKey fontKey;
	/** Font family format */
	enum AIFaceFormat format;
	/** Font face encoding */
	enum AIFaceEncoding encoding;
	/** Font face script */
	enum AIFaceScript script;
	/** When true, this is the original encoding */
	AIBoolean originalEncoding;
	/** When true, the font family is installed */
	AIBoolean familyInstalled;
	/** Not used. */
	AIBoolean strikeInstalled;
	/** When true, the font is fauxed for a missing font */
	AIBoolean fauxedInstalled;
	/** When true, the font is a Character ID-keyed font */
	AIBoolean isCID;
	/** The MojiZume type of the font */
	enum AIMojiZumeType	mojiZumeType;
	/** When true, this is an Open Type font */
	AIBoolean isOTF;
	/** When true, this is a bitmap font */
	AIBoolean isBitmapFont;
	/**  When true, this is an Original Composite Format font*/
	AIBoolean isOCF;
	/**  When true, this is an Adobe Type Composer font*/
	AIBoolean isATC;
	/**  When true, this is an Adobe Multiple Master font*/
	AIBoolean isMultipleMaster;
};

/** Font orientations (writing directions). */
enum AIMetricOrientation {
	kAIUnknownMetricOrientation = 0,
	kAIHorizontalMetricOrientation,
	kAIVerticalMetricOrientation
};

/** Font metrics */
struct AIFontMetrics {
	/** Leading space in points */
	AIReal leading;
	/** Ascent in points */
	AIReal ascent;
	/** descent in points */
	AIReal descent;
	/** Character bounding box */
	AIRealRect bbox;
};

/** Text orientation */
typedef enum AITextOrientation {
	kHorizontalTextOrientation,
	kVerticalTextOrientation
} AITextOrientation;


/** Font technologies. */
enum AIFontTechnology {
	kAIUnknownFontTechnology = 0,
	kAIAnyFontTechnology,

	kAIAdobeFontTechnology = 100,
	kAITrueTypeFontTechnology
};


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite provides functions to access the set of fonts that is
	available to Illustrator documents, and provide information about
	individual fonts.

	The set of available fonts includes those from the operating
	system, those installed with Illustrator, and substitute fonts for
	missing fonts in open documents. The set of fonts can change during
	a session as fonts are activated or deleted, and as documents are
	opened or closed.

	There are several different types of font names:
	\li The PostScript name is a unique, ASCII name that can
		be stored in files to identify a font. For multiple master
		instances, it includes the specific design axis values.
	\li The Illustrator PostScript name is the PostScript name with
		a suffix identifying the encoding. It can also be stored in
		a file to identify a font.
	\li A user name is a display name, which can be in ASCII or
		a localized encoding. There can be several such names; for
		example a full name describing the font, and the font family name.

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIFontSuite and \c #kAIFontVersion.

*/
struct AIFontSuite {

	/** Gets the total number of available fonts. Variations, such as
		"Times Roman Regular" and "Times Roman Italic" are counted as
		distinct fonts. Use with \c #IndexFontList() to iterate through
		available fonts.
			@param count [out] A buffer in which to return the number of fonts.
		*/
	AIAPI AIErr (*CountFonts)( ai::int32 *count );

	/** Retrieves a font by index position. Use with \c #CountFonts() to
		iterate through available fonts. Font indices can change as
		fonts are added and removed.
			@param index The 0-based position index.
			@param fontKey [out] A buffer in which to return the font key.
		*/
	AIAPI AIErr (*IndexFontList)( ai::int32 index, AIFontKey *fontKey );

	/** Gets the total number of font families. Variants, such as italic
		and bold, are counted as a single family. Use with \c #IndexTypefaceList() to
		iterate through available font families.
			@param count [out] A buffer in which to return the number of font families.
		*/
	AIAPI AIErr (*CountTypefaces)( ai::int32 *count );

	/** Retrieves a font family by index position. Use with \c #CountTypefaces() to
		iterate through available font families. Indices can change as
		fonts are added and removed.
			@param index The 0-based position index.
			@param typeFaceKey [out] A buffer in which to return the font family key.
		*/
	AIAPI AIErr (*IndexTypefaceList)( ai::int32 index, AITypefaceKey *typeFaceKey );
	
	/** Gets the total number of variants (such as bold and italic) of a font family.
		Use with \c #IndexTypefaceStyleList() to iterate through variants.
			@param typeface The font family, as returned by \c #IndexTypefaceList().
			@param count [out] A buffer in which to return the number of variants.
		 */
	AIAPI AIErr (*CountTypefaceStyles)( AITypefaceKey typeface, ai::int32 *count );

	/** Retrieves a variant of a font family by index position. Use with
		\c #CountTypefaceStyles() to iterate through variants.
			@param typeface The font family, as returned by \c #IndexTypefaceList().
			@param index The 0-based position index.
			@param fontKey [out] A buffer in which to return the font key.
		 */
	AIAPI AIErr (*IndexTypefaceStyleList)( AITypefaceKey typeface, ai::int32 index, AIFontKey *fontKey );

	/** Retrieves the family and variant of a font.
			@param theKey The font key.
			@param typefaceResult [out] A buffer in which to return the font family key.
			@param styleResult [out] A buffer in which to return the index position
				of the family variant (such as bold or italic).
		*/
	AIAPI AIErr (*TypefaceAndStyleFromFontKey)(AIFontKey theKey, AITypefaceKey *typefaceResult, ai::int16 *styleResult);

	/** Finds a font matching specific criteria.
			@param postscriptName The PostScript font name, such as "Times-Roman",
				or Illustrator PostScript font name.
			@param fontTechnology The font type, such as Adobe or TrueType, an \c #AIFontTechnology value.
			@param script The language for which the font was designed; an \c #AIFaceScript value.
			@param substituteFlag When true, returns a substitute if an exact match is not found.
			@param result [out] A buffer in which to return the font key.
		*/
	AIAPI AIErr (*FindFont)(const char *postscriptName, enum AIFontTechnology fontTechnology, AIFaceScript script,
			AIBoolean substituteFlag, AIFontKey *result);
	
	/** Finds an Illustrator font matching a Mac OS system font.
			@param fontRef The Mac OS ATS font ref
			@param result [out] A buffer in which to return the font key.
		*/
	AIAPI AIErr (*FindMacFontFromMacFontRef)(AIMacFontRef macFontRef, AIFontKey *result);

	/** Not implemented. */
	AIAPI AIErr (*FindWinFont)(AILOGFONTA *logFont, AIFontKey *result);
	
	/** Retrieves the Mac OS ATS font ref for an Illustrator font. If the given font does not
			correspond to a system font, gets the default system font.
			@param fontKey The font key.
			@param macFontRef [out] A buffer in which to return the Mac OS ATS font ref.
		*/
	AIAPI AIErr (*GetMacFontRef)(AIFontKey fontKey, AIMacFontRef& macFontRef);

	/** Retrieves typeface name of a font, or the system name for a system font in Windows.
			@param fontKey The font key.
			@param result [out] A buffer in which to return the typeface name, or,
				in Windows only, the face name of the WindowsLogFont if the font is a system font..
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetSystemFontName)(AIFontKey fontKey, char *result, ai::int16 maxName);

	/** Sets the character widths for a fauxed, single-byte, horizontal font.
			@param fontKey The font key.
			@param charWidths A pointer to the new array of width values, in points.
				This is an array of 256 values where each entry is the advance override
				for the corresponding glyph.
		*/
	AIAPI AIErr (*SetCharWidths)(AIFontKey fontKey, AIReal *charWidths);

	// Accessing various attributes of a font...except the name...that's different

	/** Retrieves the font information for a font.
			@param theKey The font key.
			@param result [out] A buffer in which to return the font information structure.
		*/
	AIAPI AIErr (*GetFontInfo)( AIFontKey font, struct AIFontStyle *result);

	/** Retrieves the font metrics for a font.
	 		@param theKey The font key.
	 		@param result [out] A buffer in which to return the font metrics structure.
		*/
	AIAPI AIErr (*GetFontMetrics)( AIFontKey font, struct AIFontMetrics *result);

	/** Retrieves the default pen displacement for a glyph in a given orientation,
		for a 1-point font.
			@param font The font key.
			@param glyphID The glyph identifier.
			@param orientation The text orientation (horizontal or vertical).
			@param hResult  [out] A buffer in which to return the horizontal displacement, in points,
				or \c NULL if the orientation is vertical.
			@param vResult  [out] A buffer in which to return the vertical displacement, in points,
				or \c NULL if the orientation is horizontal.
		*/
	AIAPI AIErr (*GetGlyphDimensions)( AIFontKey font, AIGlyphID glyphID, enum AIMetricOrientation orientation,
			AIReal *hResult, AIReal *vResult);

	/** Retrieves the default pen displacement for a UTF8-encoded character
		in a given orientation, for a 1-point font.
			 @param font The font key.
			 @param charPtr A pointer to the platform-encoded character.
			 @param orientation The text orientation (horizontal or vertical).
			@param hResult  [out] A buffer in which to return the horizontal displacement, in points,
				or 0 if the orientation is vertical.
			@param vResult  [out] A buffer in which to return the vertical displacement, in points,
				or 0 if the orientation is horizontal.
		*/
	AIAPI AIErr (*GetCharDimensions)( AIFontKey font, const char *charPtr, enum AIMetricOrientation orientation,
			AIReal *hResult, AIReal *vResult);

	/** Retrieves the default font for a language script.
			@param script The language script.
			@param result [out] A buffer in which to return the font key.
		*/
	AIAPI AIErr (*GetDefaultFont)( AIFaceScript script, AIFontKey *result);

	// Various ways to get the name of a font

	/** Retrieves the PostScript name of a font, with the encoding
		information that Illustrator appends. This name is always encoded in ASCII.
			@param font The font key.
			@param fontName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetFullFontName)( AIFontKey font, char *fontName, ai::int16 maxName );

	/** Retrieves the Illustrator PostScript name of a font (with encoding information
		appended). This uniquely identifies a font, for example, in a file.
		This name is always encoded in ASCII.
			@param font The font key.
			@param postScriptFontName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetPostScriptFontName)( AIFontKey fontKey, char* postScriptFontName, ai::int16 maxName );

	/** Retrieves the ASCII-encoded name for the variant of a font (for example, "Bold Italic")
			@param font The font key.
			@param styleName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetFontStyleName)( AIFontKey font, char *styleName, ai::int16 maxName );

	/** Retrieves the display name for the family of a font (for example, "Times Roman").
		The name is encoded either in ASCII or in the encoding of the font,
		depending on the preference setting for using English font names.
			@param font The font key.
			@param familyName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetFontFamilyUIName)( AIFontKey font, char *familyName, ai::int16 maxName );

	/** Retrieves the display name for the variant of a font (for example, "Bold Italic").
		The name is encoded either in ASCII or in the encoding of the font,
		depending on the preference setting for using English font names.
			@param font The font key.
			@param styleName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetFontStyleUIName)( AIFontKey font, char *styleName, ai::int16 maxName );

	/** Retrieves the ASCII-encoded name for a font family (for example, "Times Roman").
			@param typeface The font family key.
			@param name [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
	 */
	AIAPI AIErr (*GetTypefaceName)( AITypefaceKey typeface, char *name, ai::int16 maxName );

	/** Retrieves the full ASCII-encoded name for a font (for example, "Times Roman Bold Italic").
		The name is always encoded in ASCII.
			@param font The font key.
			@param userfontName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetUserFontName)( AIFontKey font, char *userfontName, ai::int16 maxName );

	/** Retrieves the full display name for a font (for example, "Times Roman Bold Italic")
		The name is encoded either in ASCII or in the encoding of the font,
		depending on the preference setting for using English font names.
			@param font The font key.
			@param userfontName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetUserFontUIName)( AIFontKey font, char *userfontName, ai::int16 maxName );


	/** Converts an Illustrator font key to an Adobe Text Engine (ATE)
		font reference, for use with ATE functions.
			@param font The font key.
			@param result [out] A buffer in which to return the ATE font reference.
			@see \c ATETypes.h
		*/
	AIAPI AIErr (*FontFromFontKey)(AIFontKey font, FontRef *result);

	/** Converts an Adobe Text Engine (ATE) font reference to an Illustrator font key.
			@param font The ATE font reference.
			@param result [out] A buffer in which to return the font key.
			@see \c ATETypes.h
		*/
	AIAPI AIErr (*FontKeyFromFont)(FontRef font, AIFontKey *result);

		/** Retrieves whether a font is substituted or not.
			@param fontKey The font key.
			@param outIsSubstituted [out] A buffer in which to return the boolean value.
		*/
	AIAPI AIErr (*GetFontIsSubstituted)(AIFontKey fontKey, AIBoolean& outIsSubstituted);

	// The following methods deal with accessing alternate glyph information

	/** Retrieves a glyph set, which contains information about alternate
		glyphs within an OpenType font.
			@param theFont An OpenType font.
			@param otFeature When zero, gets information about all glyphs. Otherwise,
				specify the feature of interest, as a 4-byte character sequence (in a \c ai::int32)
				for	an OpenType feature tag.
			@param result [out] A buffer in which to return the glyph set. You must release
				this object using \c #ReleaseGlyphSet() when it is no longer needed.
			@see For the set of registered features tags,
				\c  https://docs.microsoft.com/en-us/typography/opentype/spec/featuretags 
		 */
	AIAPI AIErr (*GetGlyphSet)(AIFontKey theFont, ai::int32 otFeature, AIGlyphSet *result);

	/** Disposes of a glyph set object.
			@param theSet The object, as returned by \c #GetGlyphSet(). */
	AIAPI AIErr (*ReleaseGlyphSet)(AIGlyphSet theSet);

	/** Gets the number of glyphs within a glyph set. Use with \c #GetGlyphInfo() to iterate
		through glyphs.
			@param theSet The glyph set object.
			@param glyphCountResult [out] A buffer in which to return the number of glyphs.
		*/
	AIAPI AIErr (*CountGlyphs)(AIGlyphSet theSet, int *glyphCountResult);

	/** Retrieves information about a specific glyph. Use with \c #CountGlyphs() to iterate
		through glyphs.
			@param theSet The glyph set object.
			@param glyphIndex The index position of the glyph, in the range <code>[1..numGlyphs]</code>.
			@param glyphInfoResult [out] A buffer in which to return the glyph information.
		*/
	AIAPI AIErr (*GetGlyphInfo)(AIGlyphSet theSet, ai::int32 glyphIndex, AIGlyphInfo *glyphInfoResult);

	/** Gets the ordinal position of a given glyph within a glyph set.
			@param theSet The glyph set object.
			@param glyphID The unique identifier of the glyph.
			@param glyphIndex [out] A buffer in which to return the index position
				of the glyph, in the range <code>[1..numGlyphs]</code>.
		*/
	AIAPI AIErr (*GlyphIDToIndex)(AIGlyphSet theSet, AIGlyphID glyphID, int *glyphIndexResult);

	/** Retrieves all OpenType features supported by a particular font.
			@param theFont The font key.
			@param featureList [in, out] An array of OpenType features of length \c featureCount.
				Each value is a 4-byte character sequence (in a \c ai::int32) representing
				an OpenType feature tag.
				Caller must provide the array. Pass NULL to obtain the size of the array required.
			@param featureCount [out] A buffer in which to return the size of array required for
				\c featureList.
			@see For the set of registered features tags,
				\c  https://docs.microsoft.com/en-us/typography/opentype/spec/featuretags 
		*/
	AIAPI AIErr (*GetOTFeatures)(AIFontKey theFont, ai::int32 *featureList, ai::int32 *featureCount);

	/** Reports whether there are any glyphs for a given Open Type feature in a given font, or retrieves
		the glyph set containing the glyphs, if any.
		(Note that this function returns a numeric value, not an error code.)
			@param theFeature The feature, a 4-byte character sequence (in a \c ai::int32) representing
				an OpenType feature tag.
			@param fontKey The font key.
			@param existFlag When true, the function reports on whether the font contains any glyphs
				for the feature. A font can define an OpenType feature, but assign no
				glyphs to that feature. Use this assure that at least one glyph is present.
				<br>When false, the function retrieves the glyph set
				containing the glyphs (if any). This is the same as using \c #GetGlyphSet().
			@param result [out] A buffer in which to return the glyph set. You must release
				this object using \c #ReleaseGlyphSet() when it is no longer needed.
			@return Non-zero (true) if the font contains at least one glyph for the given feature,
				zero (false) otherwise.
			@see For the set of registered features tags,
				\c  https://docs.microsoft.com/en-us/typography/opentype/spec/featuretags 
		*/
	AIAPI ai::int32  (*GetGlyphsForFeatureAccessInfo)(ai::int32 theFeature, AIFontKey fontKey, AIBoolean existFlag,
			AIGlyphSet *glyphSet);

	/** Retrieves the font that contains a glyph set.
			@param glyphSetOpaque The glyph set.
			@param result [out] A buffer in which to return the font object.
		*/
	AIAPI AIErr (*GetFontInstance)(AIGlyphSet glyphSetOpaque, AIFontInst **result);

	/** Retrieves the unique identifier of a glyph.
			@param glyphInfo The glyph information, as returned by \c #GetGlyphInfo().
			@param result [out] A buffer in which to return the glyph identifier.
		*/
	AIAPI AIErr (*GetGlyphID)(AIGlyphInfo glyphInfo, AIGlyphID *result);

	/** Retrieves the set of alternate glyphs for a given glyph.
			@param glyphInfo The glyph information, as returned by \c #GetGlyphInfo().
			@param result [out] A buffer in which to return the alternative glyph set.
		*/
	AIAPI AIErr (*GetAlternateGlyphs)(AIGlyphInfo glyphInfo, AIGlyphSet *result);

	/** Retrieves the OpenType features associated with a given glyph.
			@param glyphInfo The glyph information, as returned by \c #GetGlyphInfo().
			@param otFeatures [out] A buffer in which to return the features. Do not modify the returned
				character array (which is not a null-terminated string). The array contains
				a set of 4-character feature codes; for example	"vertswsh" for a glyph
				to which 'vert' and 'swsh' features can be applied.
			@param otFeatureCount [out] A buffer in which to return the number of features in \c otFeatures.
			@param otFeatureIndex [out] A buffer in which to return an array of length
				\c otFeatureCount containing the number of alternates available for each
				feature listed in the \c otFeatures array.
		*/
	AIAPI AIErr (*GetGlyphOTFeatures)(AIGlyphInfo glyphInfo, const char **otFeatures, ai::int32 *otFeatureCount,
			ai::int32 **otFeatureIndex);

	/** Retrieves the Unicode character for a given glyph in a given font, with information about
		what OpenType features were applied.
			@param mGlyphID The glyph identifier.
			@param fontKey The font key.
			@param desiredOTFeature	A string containing the OpenType features of interest. See
				\c #GetGlyphOTFeatures(). The mapping of glyphs and feature sets to characters
				is not 1:1, so the returned character can have a different set of features than those
				requested.
			@param theChar [out] A buffer in which to return the Unicode character.
			@param resultLength [out] A buffer in which to return the number of features in \c theChar.
			@param otFeatures [out] A buffer in which to return the	OpenType features set that was
				applied to \c theChar. See \c #GetGlyphOTFeatures(). You must release this memory with
				\c #SPBasicSuite::FreeBlock() when it is no longer needed.
			@param otFeatureCount [out] A buffer in which to return the	number of features in \c otFeatures.
			@param otFeatureIndex [out] A buffer in which to return an array of length
				\c otFeatureCount containing the number of alternates available for each
				feature listed in the \c otFeatures array.
				You must release this memory with \c #SPBasicSuite::FreeBlock() when it is no longer needed.
		*/
	AIAPI AIErr (*GetGlyphUnicodeValue)(AIGlyphID mGlyphID, AIFontKey fontKey, const char *desiredOTFeature,
			ASUnicode *theChar, int *resultLength, char **otFeatures, ai::int32 *otFeatureCount, ai::int32 **otFeatureIndex);

	/** Retrieves the font for a glyph.
			@param theGlyphInfo	The glyph information, as returned by \c #GetGlyphInfo().
			@param result [out] A buffer in which to return the font key.
		*/
	AIAPI AIErr (*GetGlyphFontKey)(AIGlyphInfo theGlyphInfo, AIFontKey *result);

	/** Retrieves the number of alternate glyphs for a given glyph.
			@param theGlyphInfo	The glyph information, as returned by \c #GetGlyphInfo().
			@param result [out] A buffer in which to return the number of alternative glyphs.
		*/
	AIAPI AIErr (*GetGlyphAlternateCount)(AIGlyphInfo theGlyphInfo, int *result);

	/** Retrieves the \e undefined glyph for a glyph set. Each font has one undefined glyph, but not every
		glyph set contains one. Use \c #HasUndefinedGlyph() to check.
			@param theSet The glyph set.
			@param undefinedGlyphIDResult [out] A buffer in which to return the glyph identifier.
		*/
	AIAPI AIErr (*GetUndefinedGlyphID)(AIGlyphSet theSet, AIGlyphID *undefinedGlyphIDResult);

	/** Reports whether a glyph set contains an undefined glyph. Each font has one undefined glyph,
		but not every glyph set contains one. Use \c #GetUndefinedGlyphID to retrieve it if there is one.
		(Note that this function returns a boolean value, not an error code.)
			@param theSet The glyph set.
			@return True if the set contains an undefined glyph.
		*/
	AIAPI AIBoolean (*HasUndefinedGlyph)(AIGlyphSet theSet);

	/** Imports composite fonts from an AI or ATC file into the current document.
			@param source The AI or ATC file path.
		*/
	AIAPI AIErr (*ImportCompositeFonts)(const ai::FilePath &source);

	/** Translates a character value to a single glyph in a given font.
			@param fontKey The font key.
			@param ch A string containing the character. Extracts at most
				one glyph, using as many bytes as needed to form one glyph,
				starting with the first byte pointed to by \c ch.
				Derives the encoding from the font.
			@param srcLen The number of bytes in \c ch.
			@param orientation The text orientation, vertical or horizontal.
			@param glyphID [out] A buffer in which to return the glyph identifier, or
				undefined glyph for the font if a glyph is not defined for this character.
			@return The error \c #kGlyphNotDefinedErr if a glyph is not defined for
				this character.
		*/
	AIAPI AIErr (*ConvertCharacterToGlyphID) ( AIFontKey fontKey, const char* ch, ai::int32 srcLen,
											   enum AIMetricOrientation orientation, AIGlyphID* glyphID );

	/** Translates a Unicode character value to a single glyph in a given font.
			@param fontKey The font key.
			@param ch A UTF16-encoded string containing the character. Extracts at most
				one glyph, using as many characters as needed to form one glyph,
				starting with the first character pointed to by \c ch.
			@param srcLen The number of \c ASUnicode characters (not bytes) in \c ch.
			@param orientation The text orientation, vertical or horizontal.
			@param glyphID [out] A buffer in which to return the glyph identifier, or
				undefined glyph for the font if a glyph is not defined for this character.
			@return The error \c #kGlyphNotDefinedErr if a glyph is not defined for
					this character.
		 */
	AIAPI AIErr (*ConvertUnicodeToGlyphID) ( AIFontKey fontKey, const ASUnicode* ch, ai::int32 srcLen,
											 enum AIMetricOrientation orientation, AIGlyphID* glyphID );

	/** Retrieves the full display name for a font (for example, "Times Roman Bold Italic")
		in Unicode (UTF16).
		The name is either in English or the native language of the font depending on the
		setting of the preference to use English font names.
			@param fontKey The font key.
			@param userfontName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetUserFontUINameUnicode)( AIFontKey fontKey, ASUnicode* userfontName, ai::int32 maxName );

	/** Retrieves the display name for the family of a font (for example, "Times Roman")
		in Unicode (UTF16).
		The name is either in English or the native language of the font depending on the
		setting of the preference to use English font names.
			@param fontKey The font key.
			@param familyName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetFontFamilyUINameUnicode)( AIFontKey fontKey, ASUnicode* familyName, ai::int32 maxName );

	/** Retrieves the display name for the variant of a font (for example, "Bold Italic")
		in Unicode (UTF16).
		The name is either in English or the native language of the font depending on the
		setting of the preference to use English font names.
			@param fontKey The font key.
			@param styleName [out] A buffer in which to return the name.
			@param maxName The number of characters in the name string buffer. The name string,
				including the \c NULL terminator, is truncated to this size if necessary.
		*/
	AIAPI AIErr (*GetFontStyleUINameUnicode)( AIFontKey fontKey, ASUnicode* styleName, ai::int32 maxName );

	// New for Illustrator 12.0

	/** Retrieves the ideographic character face (IFC) bounds of a font.
		The ICF-box is the maximum bounding box of the ideographic portion of a CJK font,
		usually centered within the em-box. The value is also defined also for non-CJK fonts.
		The coordinate values are relative to the font coordinate system's origin.
		X values increase to the right and Y values increase downward.
			@param fontKey The font key.
			@param icfBox [out] A buffer in which to return the bounding box
			@see Baseline tags \c icfb and \c icft in the OpenType tag registry.
		*/
	AIAPI AIErr (*GetICFBox) ( AIFontKey fontKey, AIRealRect& icfBox );

	// New for Illustrator 13.0

	/** Retrieves the version string for a font file. If the font object is fauxed,
		gets version information for the underlying font.
		You can check whether the font is fauxed using \c #GetFontInfo().
			@param fontKey The font key.
			@param versionString [out] A buffer in which to return the version string.
		 */
	AIAPI AIErr (*GetVersionString) ( AIFontKey fontKey, ai::UnicodeString& versionString );

	/** Reports how many files constitute a font. For example, a Windows Type 1 font has a PFB
		and a PFM file, and a Mac Type 1 font has a suitcase and an outline file, but an OpenType
		font has only a single file. Use with \c #GetNthFilePath() to access the files.

		If the font is fauxed, returns the information for the underlying font used to faux
		the missing font. Check whether the font is fauxed using \c #GetFontInfo().
			@param fontKey The font key.
			@param count [out] A buffer in which to return the number of files.
				This can be 0 for some fonts; see \c #GetNthFilePath().
			@note This function does not distinguish between two identical font files
				and two different files for the same font.
		*/
	AIAPI AIErr (*GetFontFilePathCount) ( AIFontKey fontKey, ai::uint32& count );

	/** Retrieves a file path associated with a font. Use with \c #GetFontFilePathCount()
		to access font files.

		This method does not work for fonts whose paths Illustrator does not know,
		such as Windows bitmap fonts, and Mac OS bitmap-only fonts. For an ATC font,
		gets the location of the top-level rearrangement file only.
		To get the paths of component fonts, iterate over the component dictionaries.

		If the font is fauxed, returns the information for the underlying font used to faux
		the missing font. Check whether the font is fauxed using \c #GetFontInfo().

			@param fontKey The font key.
			@param n The position index of the file path, the range <code>[0..pathCount-1]</code>.
			@param filePath [out] A buffer in which to return the path.
		 */
	AIAPI AIErr (*GetNthFilePath) ( AIFontKey fontKey, ai::uint32 n, ai::FilePath& filePath );

	/** Gets the number of ATC components for a font. If the font is fauxed,
		returns the information for the underlying font used to faux
		the missing font. Check whether the font is fauxed, and that it
		is an ATC font, using \c #GetFontInfo().
			@param fontKey The font key.
			@param count [out] A buffer in which to return the number of ATC components.
				This is 0 for a non-ATC font.
			*/
	AIAPI AIErr (*GetNumATCComponents) ( AIFontKey fontKey, ai::uint32& count );

	/** Retrieves a component for an ATC font, by position index. Use with
		\c #GetNumATCComponents() to access font components.

		If the font is fauxed, returns the information for the underlying font used to faux
		the missing font. Check whether the font is fauxed, and that it
		is an ATC font, using \c #GetFontInfo().

			@param fontKey The font key.
			@param n The position index of the component, the range <code>[0..numATCComponents-1]</code>.
			@param componentFontKey [out] A buffer in which to return the component font key.
		*/
	AIAPI AIErr (*GetNthATCComponent) ( AIFontKey fontKey, ai::uint32 n, AIFontKey& componentFontKey );

	/** Retrieves the full user name for a font (for example, "Times Roman Bold Italic").
		This might not be the same as the display name; retrieve the display name with
		\c #GetUserFontUINameUnicode().
			@param fontKey The font key.
			@param name [out] A buffer in which to return the name string.
			@param native True to get the name in the native language of the font, false
				to get the name in English, regardless of the font's language.
		*/
	AIAPI AIErr (*GetUserFontNameUnicode) (AIFontKey fontKey, ai::UnicodeString& name,
		AIBoolean native);

	/** Retrieves the user name for the family of a font (for example, "Times Roman").
		This might not be the same as the display name; retrieve the display name with
		\c #GetFontFamilyUINameUnicode().
			@param fontKey The font key.
			@param name [out] A buffer in which to return the name string.
			@param native True to get the name in the native language of the font, false
				to get the name in English, regardless of the font's language.
 		*/
	AIAPI AIErr (*GetFontFamilyNameUnicode) (AIFontKey fontKey, ai::UnicodeString& name,
		AIBoolean native);

	/** Retrieves the user name for the style of a font (for example, "Bold Italic").
		This might not be the same as the display name; retrieve the display name with
		\c #GetFontStyleUINameUnicode().
			@param fontKey The font key.
			@param name [out] A buffer in which to return the name string.
			@param native True to get the name in the native language of the font, false
				to get the name in English, regardless of the font's language.
 		*/
	AIAPI AIErr (*GetFontStyleNameUnicode) (AIFontKey fontKey, ai::UnicodeString& name,
		AIBoolean native);

	/** Retrieves the ideographic em-box of a font, also known as an ideographic font's design space.
		This defines a standard monospaced escapement around the glyphs of the font, for both horizontal and
		vertical writing modes. It is one em high and one em wide unless the vendor explicitly indicates
		otherwise in the font. The OpenType specification strongly recommends against this being other than an
		em wide, but there are legitimate reasons for it to be other than one em high: some fonts used in
		Japanese newspaper layout, for example, have a vertically compressed ideographic em-box.

		The returned value, an array with the left, top, right, and bottom edges
		(in horizontal writing mode) of the ideographic em-box of a 1-unit-em font,
		is defined for every font (including non-CJK fonts, where it can be used to em-box-align
		these fonts alongside CJK fonts).

		The coordinate values are relative to the font coordinate system's origin.
		X values increase to the right and Y values increase downward.
			@param fontKey The font key.
			@param ideoEmBox [out] A buffer in which to return the bounding box,
			@see Baseline tag \c ideo in the OpenType tag registry for more information.
		*/
	AIAPI AIErr (*GetIdeoEmBox) ( AIFontKey fontKey, AIRealRect& ideoEmBox );

	/** Retrieves a font from a given family that is the closest match for a given font from
	another family. If the same style is present in the new family, it is selected; otherwise,
	selects the closest match from the new family.
		@param old_Family The typeface of a previously selected font family.
		@param old_style The 0-based index of the font style to match within the old family.
		@param new_Family The typeface of a new font family, in which to find a match.
		
		@param new_style [out] A bufffer in which to return the 0-based index of the best-match font in the new family.
	*/

	AIAPI AIErr (*GetCloselyMatchingFontStyle) (AITypefaceKey old_Family, short* old_Style, AITypefaceKey new_Family, short* new_Style);

	/** Retrieves a font family by index position, from the list of all available font families.
		Use with \c #CountTypefaces() to iterate through available font families. Indices can change as fonts are added and removed.
			@param index The 0-based position index.
			@param typeFaceKey [out] A buffer in which to return the font family key.
	*/
		
	AIAPI AIErr (*IndexTypefaceListSortedByDefaultScript)(AITypefaceKey* typeface, ai::int32 index);

	AIAPI AIErr (*GetTypefaceUnicodeMenuName)(AITypefaceKey typeface, ai::UnicodeString& typefaceName);
};


/** @ingroup Notifiers
	Sent when the system language has changed. See \c #AIMEFontSuite. */
#define kAICurrentLanguageChangedNotifier    "AI Current Language Changed Notifier"

#define kAIMEFontSuite			"AI ME Font Suite"
#define kAIMEFontSuiteVersion1	AIAPI_VERSION(1)
#define kAIMEFontSuiteVersion		kAIMEFontSuiteVersion1
#define kAIMEFontVersion			kAIMEFontSuiteVersion

typedef struct {

			/** Retrieves a glyph set, which contains information about alternate
				glyphs within an OpenType font.
					@param theFont An OpenType font.
					@param AILanguage The language code for the current system language.
					@param otFeature When zero, gets information about all glyphs. Otherwise,
						specify the feature of interest, as a 4-byte character sequence (in a \c ai::int32)
						for	an OpenType feature tag.
					@param result [out] A buffer in which to return the glyph set. You must release
						this object using \c #ReleaseGlyphSet() when it is no longer needed.
					@see For the set of registered features tags,
						\c  https://docs.microsoft.com/en-us/typography/opentype/spec/featuretags 
			 */
			AIAPI AIErr (*GetGlyphSet)(AIFontKey theFont, int AILanguage, ai::int32 otFeature, AIGlyphSet *result);
			/** Retrieves all OpenType features supported by a particular font.
				@param theFont The font key.
				@param AILanguage The language code for the current system language.
				@param featureList [in, out] An array of OpenType features of length \c featureCount.
					Each value is a 4-byte character sequence (in a \c ai::int32) representing
					an OpenType feature tag.
					Caller must provide the array. Pass NULL to obtain the size of the array required.
				@param featureCount [out] A buffer in which to return the size of array required for
					\c featureList.
				@see For the set of registered features tags,
					\c  https://docs.microsoft.com/en-us/typography/opentype/spec/featuretags 
			*/
			AIAPI AIErr (*GetOTFeatures)(AIFontKey theFont, int AILanguage, ai::int32 *featureList, ai::int32 *featureCount);

		   /** Reports whether there are any glyphs for a given Open Type feature in a given font, or retrieves
			   the glyph set containing the glyphs, if any.
			   (Note that this function returns a numeric value, not an error code.)
				@param theFeature The feature, a 4-byte character sequence (in a \c ai::int32) representing
					an OpenType feature tag.
				@param fontKey The font key.
				@param AILanguage The language code for the current system language.
				@param existFlag When true, the function reports on whether the font contains any glyphs
					for the feature. A font can define an OpenType feature, but assign no
					glyphs to that feature. Use this assure that at least one glyph is present.
					<br>When false, the function retrieves the glyph set
					containing the glyphs (if any). This is the same as using \c #GetGlyphSet().
				@param result [out] A buffer in which to return the glyph set. You must release
					this object using \c #ReleaseGlyphSet() when it is no longer needed.
				@return Non-zero (true) if the font contains at least one glyph for the given feature,
					zero (false) otherwise.
				@see For the set of registered features tags,
					\c  https://docs.microsoft.com/en-us/typography/opentype/spec/featuretags 
			*/
			AIAPI ai::int32  (*GetGlyphsForFeatureAccessInfo)(ai::int32 theFeature, AIFontKey fontKey, int AILanguage, AIBoolean existFlag,
					AIGlyphSet *glyphSet);
			/** Retrieves the Unicode character for a given glyph in a given font, with information about
				what OpenType features were applied.
				@param mGlyphID The glyph identifier.
				@param fontKey The font key.
				@param AILanguage The language code for the current system language.
				@param desiredOTFeature	A string containing the OpenType features of interest. See
					\c #GetGlyphOTFeatures(). The mapping of glyphs and feature sets to characters
					is not 1:1, so the returned character can have a different set of features than those
					requested.
				@param theChar [out] A buffer in which to return the Unicode character.
				@param resultLength [out] A buffer in which to return the number of features in \c theChar.
				@param otFeatures [out] A buffer in which to return the	OpenType features set that was
					applied to \c theChar. See \c #GetGlyphOTFeatures(). You must release this memory with
					\c #SPBasicSuite::FreeBlock() when it is no longer needed.
				@param otFeatureCount [out] A buffer in which to return the	number of features in \c otFeatures.
				@param otFeatureIndex [out] A buffer in which to return an array of length
					\c otFeatureCount containing the number of alternates available for each
					feature listed in the \c otFeatures array.
					You must release this memory with \c #SPBasicSuite::FreeBlock() when it is no longer needed.
			*/
			AIAPI AIErr (*GetGlyphUnicodeValue)(AIGlyphID mGlyphID, AIFontKey fontKey, int AILanguage, const char *desiredOTFeature,
					ASUnicode *theChar, int *resultLength, char **otFeatures, ai::int32 *otFeatureCount, ai::int32 **otFeatureIndex);
			/** Retrieves the language code for the current system language.
				(Note that this function returns a numeric value, not an error code.)
				@return The language code.
			*/
			AIAPI int (*GetCurrentLanguage)();

			/** Converts an Adobe Text Engine language object to an Illustrator language code.
			 	(Note that this function returns a numeric value, not an error code.)
				@param sloLang The Adobe Text Engine language object.
				@return The language code.
			*/
			AIAPI int (*SLOLanguageToAILanguage)(ATE::Language sloLang);

			/**  Retrieves the language from a glyph-information structure.
				@param glyphInfo The glyph-information structure.
				@param result [out] A buffer in which to return the language code.

			*/
			AIAPI AIErr (*GetGlyphLanguage)(AIGlyphInfo glyphInfo, int *result);
} AIMEFontSuite;

#include "AIHeaderEnd.h"

#endif // __AIFont__
