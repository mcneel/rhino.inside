#ifndef __AIFOConversion__
#define __AIFOConversion__

/*
 *        Name:	AIFOConversion.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Foreign Object Conversion Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2002-2007 Adobe Systems Incorporated.
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

#ifndef __AIForeignObject__
#include "AIForeignObject.h"
#endif

#ifndef __AIFont__
#include "AIFont.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIFOConversion.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIFOConversionSuite				"AI FO Conversion Suite"
#define kAIFOConversionSuiteVersion3		AIAPI_VERSION(3)
#define kAIFOConversionSuiteVersion			kAIFOConversionSuiteVersion3
#define kAIFOConversionVersion				kAIFOConversionSuiteVersion


/** @ingroup Errors
	Error in foreign-object conversion; see \c #AIFOConversionSuite. */
#define kAIFOConversionErr		'!FOc'

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Wrap this \c AGMColorSpace* as a \c CAGMColorSpace
	or some baseclass in order to use it. */
typedef struct _AIAGMColorSpace *AIAGMColorSpaceHandle;


/** Types of errors that can occur during the conversion process,
 	sent to a callback from \c #AIFOConversionSuite::ConvertToNative(),
	Depending on the type, the callback can also receive
	additional information about
	as \c info, a void * which you must
	cast to an appropriate type as specified.
	*/
typedef enum AIFOConversionInfoSelector
{
	/** No problem occurred.
		No \c info is passed; pointer is \c NULL. */
	kAIFOConversionInfoNone,
	/** Conversion encountered a problem with fauxed fonts.
		\c info contains the missing font name, as <code>char *</code>. */
	kAIFOConversionInfoFauxedFont,
	/** Conversion encountered a problem with axial shading.
		No \c info is passed; pointer is \c NULL.*/
	kAIFOConversionInfoUnknownAxialShading,
	/**Conversion encountered a problem with radial shading.
		No \c info is passed; pointer is \c NULL. */
	kAIFOConversionInfoUnknownRadialShading,
	/**  Conversion encountered a problem with an unknown AIM construct.
		No \c info is passed; pointer is \c NULL. */
	kAIFOConversionInfoUnknownAIMConstruct,
	/**  Conversion encountered a problem with outlined text.
		No \c info is passed; pointer is \c NULL. */
	kAIFOConversionInfoTextOutlined,
	/**  Conversion encountered a problem with rasterized text.
		No \c info is passed; pointer is \c NULL. */
	kAIFOConversionInfoTextRasterized

} AIFOConversionInfoSelector;


/** Types of information about the contents of foreign object that can
	be collected and sent to a callback from
	\c #AIFOConversionSuite::EnumerateContents(), */
typedef enum AIFOContentInfoSelector
{
	/** No information is collected.
		No \c info is passed; pointer is \c NULL. */
	kAIFOContentInfoNone,
	/** Passes transparency state of contained art in
		\c info as <code>const AIBoolean*</code> */
	kAIFOContentInfoHasTransparency,
	/** Collects information on marks process plate state of contained art
		in \c info as <code>const AIBoolean*</code>  */
	kAIFOContentInfoMarksProcessPlates,
	/**  Passes marks CMYK plate state of contained art;
		\c info contains the value as
		<code>const AIBoolean  [4] c,m,y,k</code>
	 */
	kAIFOContentInfoMarksCMYKPlates,
	/** Passes overprint state of contained art in \c info as
		<code>const AIBoolean*</code>  */
	kAIFOContentInfoHasOverPrint,
	/** Passes text state of contained art in \c info as
		<code>const AIBoolean*</code>  */
	kAIFOContentInfoHasText,
	/** Passes gradient state of contained art in \c info as
		<code>const AIBoolean*</code>   */
	kAIFOContentInfoHasGradient,
	/** Passes gradient mesh state of contained art in \c info as
		<code>const AIBoolean*</code>   */
	kAIFOContentInfoHasGradientMesh,
	/**  Passes spot colors in contained art in \c info as
		\c #AICustomColorHandle  */
	kAIFOContentInfoSpotColor,
	/** Each time a drawing operation involves an image as the source of color data,
		passes the transformation matrix applied in \c info as \c #AIRealMatrix. */
	kAIFOContentInfoRasterTransform,
	/** Each time a drawing operation involves an image as the source of color data,
		passes image information in \c info as \c #AIRasterRecord.
	 */
	kAIFOContentInfoPaintServerRasterRecord,
	/** Passes true if the object contains anything other
		than images and clipping operations, false otherwise.
		Value passed in \c info as <code>const AIBoolean*</code>
	 */
	kAIFOContentInfoHasNonImage

} AIFOContentInfoSelector;


/** Flags for conversion of a foreign object. A logical OR of
	\c #AIFOConversionFlagValue bit flags. */
typedef ai::int32 AIFOConversionFlags;

/** Flag values that specify how the conversion of a foreign object to
	native artwork is performed. */
enum AIFOConversionFlagValue {
	/** Preserves full visual fidelity and spot colors.
		May create other foreign objects. */
	kAIFOConversionDefault 				= 0,
	/** Performs full, but possibly lossy, conversion,
		converts spot colors to process colors.
		Does not create other foreign objects.
		Rasterizes objects that cannot be represented as native art,
		including objects filled with PDF shading types,
		device-n (spot) rasters, and so on. */
	kAIFOConversionFull					= 1 << 0,
	/** Replaces paths with stroked versions. */
	kAIFOConversionStrokePaths			= 1 << 1,
	/** Simplifies paths so that no subpaths intersect. */
	kAIFOConversionSimplifyPaths		= 1 << 2,
	/** Suppresses object-level attributes, such as visibility, Live Effects,
		transparency, and so on. Use this to convert only the \e contents of
		the foreign object (such as the display list).

		Specify only for  \c #AIFOConversionSuite::ConvertToNative().
		This is the default behavior for \c #AIFOConversionSuite::OutlineLegacyText(). */
	kAIFOConversionSuppressAttributes	= 1 << 3,
	/** Disallows colorized grayscale images in the output from conversion. */
	kAIFOConversionNoColorizedGray		= 1 << 4,
	/** Forces use of Newell mixing to convert spot colors to process colors.
		Newell mixing preserves the numbers of the spot color alternates. */
	kAIFOConversionUseNewellMixing		= 1 << 5,
	/** Disallows NChannel/Separation/Indexed color space images in the output from conversion. */
	kAIFOConversionNoNChannelIndexedImages	= 1 << 6
};


/** The prototype for a callback function from \c #AIFOConversionSuite::ConvertToNative()
	that acts on information about the conversion.
		@param selector Identifies the type of information being supplied.
		@param info A pointer to information specific to the \c selector. To inspect its
			contents, cast it to an appropriate type, according to the \c selector.
		@param data A pointer to developer-defined data, passed back from
			\c #AIFOConversionSuite::ConvertToNative()
	*/
typedef void (*AIConversionInfoProc)(AIFOConversionInfoSelector selector, void *info, void *data);

/** The prototype for a callback function from \c #AIFOConversionSuite::EnumerateFonts()
	that acts on fonts used by a foreign object.
		@param fontkey A font in the enumeration.
		@param data A pointer to developer-defined data, passed back from
			\c #AIFOConversionSuite::EnumerateFonts().
	*/
typedef void (*AIVisitFontProc)(AIFontKey fontkey, void *data);

/** For internal use only. The prototype for a callback function from \c #AIFOConversionSuite::EnumerateEmbeddedFonts()
	that acts on fonts used by a foreign object.
		@param fontkey A font in the enumeration.
		@param wasEmbedded set true if the font is embedded in PDF or EPS
		@param data A pointer to developer-defined data, passed back from
			\c #AIFOConversionSuite::EnumerateFonts().
	*/
typedef void (*AIVisitFontExtendedProc)(AIFontKey fontkey, AIBoolean wasEmbedded, void *data);

/** The prototype for a callback function from \c #AIFOConversionSuite::EnumerateContents()
	that acts on information about the contents of a foreign object.
		@param selector Identifies the type of information being supplied.
		@param info A pointer to information specific to the \c selector. To inspect its
			contents, cast it to an appropriate type according to the \c selector.
		@param data A pointer to developer-defined data, passed back from
			\c #AIFOConversionSuite::EnumerateContents().
	*/
typedef void (*AIVisitContentProc)(AIFOContentInfoSelector selector, void *info, void *data);

/** Specify as the \c info value in the \c #AIFOConversionOptions passed to
	\c #AIFOConversionSuite::ConvertToNative(), to provide information about the
	conversion process to a callback.
	*/
typedef struct AIFOConversionInfoCollector
{
	/** The callback procedure you have defined to act on the collected information.
		\c NULL if no information desired. */
	AIConversionInfoProc proc;
	/** A pointer to developer-defined data that is passed back to the callback. */
	void *data;

} AIFOConversionInfoCollector;

/** Drawing options for \c #AIFOConversionSuite::ConvertToNative() */
typedef struct
{
	/** Controls how the conversion of foreign objects is performed.
		A logical OR of \c #AIFOConversionFlagValue bit flags.*/
	AIFOConversionFlags flags;
	/** Specifies a callback procedure and data to be passed to it. The
		callback can act on information of various types collected during
		the conversion or enumeration process.*/
	AIFOConversionInfoCollector info;

	/** Rasterization resolution for high frequency areas.
		Set to 0 to use document flattener settings.
		@see \c #AIMaskFlattenerSuite.*/
	AIReal rasterResolution;

	/** Rasterization resolution for low frequency areas (smooth shades).
		Set to 0 to use document flattener settings.
		@see \c #AIMaskFlattenerSuite.*/
	AIReal meshResolution;

	/** A custom color space for blending of spot colors upon conversion to process
		colors.  Set to \c NULL to use the default document color space */
	AIAGMColorSpaceHandle conversionCS;

} AIFOConversionOptions;



/*******************************************************************************
 **
 **	Suites
 **
 **/

/** @ingroup Suites
	These functions allows you to convert artwork and collect information about
	its contents. The suite was originally intended for use with
	foreign objects (see \c #AIForeignObjectSuite). However, you can use
	the functions with any type of artwork.	For example, you can use
	\c #AIFOConversionSuite::ConvertToNative() to convert artwork in such a
	way that the resulting art does not contain self-intersecting paths.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIFOConversionSuite and \c #kAIFOConversionVersion.
	*/
typedef struct AIFOConversionSuite {

	/** Creates native Illustrator art objects by drawing a source art
		object to a conversion port. The source art can be any type; however,
		clipping objects (such as clip paths, clipping text, or clipping legacy text)
		have no marking commands, so nothing is drawn.
			@param art The source art object. This object is not deleted.
			@param options Drawing options for the operation.
			@param paintOrder The position for the new artwork in the
				paint order, relative to the \c prep object.
				See \c AITypes::AIPaintOrder.
			@param prep	The prepositional art object.
			@see \c #AIArtSuite::NewArt() for paint order details.
				<br>\c #AILegacyTextConversionSuite for
				converting legacy text clips to native clips.
	*/
	AIAPI AIErr (*ConvertToNative)(AIArtHandle art, AIFOConversionOptions *options, ai::int16 paintOrder, AIArtHandle prep);

	/** Retrieves the conversion port that would be used to perform a specific conversion.
		For AGM clients only.
			@param options Drawing options for the operation.
			@param paintOrder The position for the new artwork in the
					paint order, relative to the \c prep object.
					See \c AITypes::AIPaintOrder.
			@param prep	The prepositional art object.
			@param port [out] A buffer in which to return the port. Caller must release with
				\c #ReleaseConversionPort()
		*/
	AIAPI AIErr (*GetConversionPort)(AIFOConversionOptions *options, ai::int16 paintOrder, AIArtHandle prep, AIDisplayPortHandle *port);

	/** Releases a conversion port.  For AGM clients only.
			@param port The port returned by \c #GetConversionPort()
		*/
	AIAPI AIErr (*ReleaseConversionPort)(AIDisplayPortHandle port);

	/** Enumerates the fonts used to draw an art object, passing them to a callback
		along with developer-defined data.
			@param art The art object.
			@param visitor The callback procedure.
			@param data	The developer-defined data to pass to the callback.
		*/
	AIAPI AIErr (*EnumerateFonts)(AIArtHandle art, AIVisitFontProc visitor, void *data);

	/** Enumerates information about the contents of an art object needed in order
		to draw it, passing it to a callback along with developer-defined data.
			@param art The art object.
			@param visitor The callback procedure.
			@param data	The developer-defined data to pass to the callback.
		*/
	AIAPI AIErr (*EnumerateContents)(AIArtHandle art, AIVisitContentProc visitor, void *data);

	/** Converts a legacy text object to outlines. Attempts to perform the
		conversion in such a way that the result is identical to the result
		that would be obtained by doing the conversion in the legacy version of
		the application. This is intended for use by plug-in groups or
		Live Effects that need to execute against legacy text,
		to ensure that the results of execution are the same as in the legacy
		version.
			@param art The art object.
			@param paintOrder The position for the new artwork in the
					paint order, relative to the \c prep object.
					See \c AITypes::AIPaintOrder.
			@param prep	The prepositional art object.
			@see \c #kAIFOConversionSuppressAttributes flag on application to object-level attributes.
		*/
	AIAPI AIErr (*OutlineLegacyText)(AIArtHandle art, ai::int16 paintOrder, AIArtHandle prep);

	/** For internal use only. Enumerates the fonts used to draw an art object, passing them to a callback
		along with information of whether the font is embedded in PDF or EPSdeveloper-defined data.
			@param art The art object.
			@param visitor The callback procedure.
			@param data	The developer-defined data to pass to the callback.
		*/
	AIAPI AIErr (*EnumerateEmbeddedFonts)(AIArtHandle art, AIVisitFontExtendedProc visitor, void *data);

} AIFOConversionSuite;



#include "AIHeaderEnd.h"


#endif // __AIFOConversion__
