#ifndef __AIVectorize__
#define __AIVectorize__

/*
 *        Name:	AIVectorize.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Vectorize Suite.
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

#ifndef __AIRaster__
#include "AIRaster.h"
#endif

#ifndef __AIDictionary__
#include "AIDictionary.h"
#endif

#ifndef __AIImageOptimization__
#include "AIImageOptimization.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIVectorize.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIVectorizeSuite				"AI Vectorize Suite"
#define kAIVectorizeSuiteVersion		AIAPI_VERSION(1)
#define kAIVectorizeVersion			kAIVectorizeSuiteVersion




/** @ingroup Notifiers
	Sent after an Update call is made and completed.
  	Message data contains the Vectorize object being updated.
  	See \c #AIVectorizeSuite. */
#define kAIVectorizeUpdateNotifier			"AI Vectorize Update Notifier"



/*******************************************************************************
 **
 ** Catalog Keys - Presets
 **
 **/

/** Catalog key for tracing presets. See \c #AIVectorizeSuite. */
#define kAITracingPresetsCatalogName 		"Adobe Vectorize Presets"

/*******************************************************************************
 **
 ** Dictionary Keys - Options
 **
 **/

/** @ingroup DictKeys
	Internal. The document dictionary key for the most recently used preset, a string.
	If the key is missing or \c NULL, the "Custom" global preset is assumed. */
#define kTracingGlobalPresetKey				"-adobe/vectorize/options/global/preset"
/** @ingroup DictKeys
	Key for the main options dictionary for tracing. See \c #AIVectorizeSuite. */
#define kTracingOptionsKey					"adobe/vectorize/options"
/** @ingroup DictKeys
	Internal. Key for the old options dictionary for tracing. */
#define kTracingOptionsOldKey				"-adobe/vectorize/options/old"
/** @ingroup DictKeys
	Internal. Key for the artwork cache dictionary for tracing. */
#define kTracingCacheKey					"-adobe/vectorize/cache"
/** @ingroup DictKeys
	Key for the tracing statistics dictionary. Includes the path count, color count, PPI, and so on. */
#define kTracingStatisticsKey				"adobe/vectorize/statistics"

// options contents
/** @ingroup DictKeys
	Tracing option key for preset . String. */
#define kTracingPresetKey					"adobe/vectorize/preset"

/** @ingroup DictKeys
	Tracing option key for mode. an \c #AITracingMode constant. */
#define kTracingModeKey						"adobe/vectorize/mode"

/** @ingroup DictKeys
	Tracing option key for threshold. Long. */
#define kTracingThresholdKey				"adobe/vectorize/ip/threshold"

/** @ingroup DictKeys
	Tracing option key for grayscale tracing . Integer. */
#define kTracingGrayscaleKey				"adobe/vectorize/ip/grayscale"

/** @ingroup DictKeys
	Tracing option key for path fidelity. Float. */
#define kTracingPathFidelityKey				"adobe/vectorize/ip/PathFidelity"

/** @ingroup DictKeys
	Tracing option key for corner fidelity. Float. */
#define kTracingCornerFidelityKey			"adobe/vectorize/ip/CornerFidelity"

/** @ingroup DictKeys
	Tracing option key for noise fidelity. Integer. */
#define kTracingNoiseFidelityKey			"adobe/vectorize/ip/NoiseFidelity"

/** @ingroup DictKeys
	Tracing option key for path fidelity. Bool. */
#define kTracingOverlappingOrAbuttingKey	"adobe/vectorize/ip/OverlappingOrAbutting"

/** @ingroup DictKeys
	Tracing option key to to decide which color range is currently selected out of the below 2 color ranges i.e. Limited Color Range or Full color range. */
#define kTracingTypeColorKey				"adobe/vectorize/ip/typecolor"

/** @ingroup DictKeys
	Tracing option key for fetching Limited color slider value. Integer */
#define kTracingLimitedColorsKey			"adobe/vectorize/ip/Limitedcolors"
/** @ingroup DictKeys
	Tracing option key for fetching Full color slider value. Float*/
#define kTracingFullColorsFidelityKey		"adobe/vectorize/ip/FullcolorsFidelity"

/** @ingroup DictKeys
	Tracing option key for fetching automatic color slider value. Float*/
#define kTracingAutomaticColorsFidelityKey	"adobe/vectorize/ip/AutomaticcolorsFidelity"

/** @ingroup DictKeys
	Tracing option key for palette swatch library name. String*/
#define kTracingLibraryName					"adobe/vectorize/ip/LibraryName"

/** @ingroup DictKeys
	Tracing option key for color group name of palette swatch library. String*/
#define kTracingColorGroupName				"adobe/vectorize/ip/ColorGroupName"

/** @ingroup DictKeys
	Tracing option key for whether to trace fills. Boolean. */
#define kTracingFillsKey					"adobe/vectorize/tracing/fills"

/** @ingroup DictKeys
	Tracing option key for whether to trace strokes. Boolean. */
#define kTracingStrokesKey					"adobe/vectorize/tracing/strokes"

/** @ingroup DictKeys
	Tracing option key for stroke weight. Float. */
#define kTracingMaxStrokeWeightKey			"adobe/vectorize/tracing/maxstrokeweight"

/** @ingroup DictKeys
	Tracing option key for how to visualize vectors. An \c #AITracingVisualizeVectorType constant.  */
#define kTracingVisualizeKey			"adobe/vectorize/visualize"


/** @ingroup DictKeys
	Tracing option key for whether to output "white" background or not.  Boolean.  New for CS3. */
#define kTracingIgnoreWhiteKey				"adobe/vectorize/output/ignorewhite"

#define kTracingSnapCurvesToLinesKey		"adobe/vectorize/output/snapcurvestolines"

// cache contents
/** @ingroup DictKeys
	Tracing cache key for tracing art. Art object. */
#define kTracingTracingArtKey				"adobe/vectorize/tracing/art"
/** @ingroup DictKeys
	Tracing cache key for preprocessed images. Raster art object. */
#define kTracingPreprocessedImageKey		"adobe/vectorize/preprocessed/image"
/** @ingroup DictKeys
	Tracing cache key for whether source art has changed
	(used to optimize art regeneration). Boolean. */
#define kTracingSourceArtChangedKey			"adobe/vectorize/src/changed"
/** @ingroup DictKeys
	Internal. Tracing cache key for scratch group. Group art object. */
#define kTracingScratchGroupKey				"adobe/vectorize/scratch/group"
/** @ingroup DictKeys
	Tracing cache key for the adjusted raster transformation matrix. Matrix. */
#define kTracingAdjustedRasterMatrixKey		"adobe/vectorize/raster/matrix"
/** @ingroup DictKeys
	Tracing cache key for the adjusted raster checksum. Integer. */
#define kTracingAdjustedRasterChecksumKey	"adobe/vectorize/raster/checksum"

// statistics contents
/** @ingroup DictKeys
	Tracing statistics key for number of paths generated. Long.  */
#define kTracingPathCountKey				"adobe/vectorize/statistics/pathcount"
/** @ingroup DictKeys
	Tracing statistics key for number of anchors generated. Long.  */
#define kTracingAnchorCountKey				"adobe/vectorize/statistics/anchorcount"
/** @ingroup DictKeys
	Tracing statistics key for number of colors used. Long.  */
#define kTracingColorCountKey				"adobe/vectorize/statistics/colorcount"


#define kTracingResampleDefault				(false)
/** Internal */
#define kTracingModeDefault					(0)
#define kTracingThresholdDefault			(128)
#define kTracingGrayscaleDefault			(50)
/** Empty string means Automatic. */
#define kTracingPresetStringNameDefault		("$$$/Tracing/Str/Options/DefaultPreset00=[Default]")
#define kLibraryNameDefault					("$$$/VectorizePanel/ColorGroupSelection/NoLibrary=NoLib")
#define kColorGroupNameDefault				("$$$/VectorizePanel/ColorGroupSelection/All=All")
#define kTracingLimitedMaxColorsDefault		(30)
#define kTracingFullToneMaxFidelityDefault	(100.0f)
#define kTracingAutomaticMaxFidelityDefault	(100.0f)
#define kTracingColorTypeDefault			(0)
#define kTracingColorGroupDefault			(0)
#define kTracingFidelityDefault				(50)
#define kTracingPathFidelityDefault			(50.0)
#define kTracingCornerFidelityDefault		(50.0)
#define kTracingNoiseFidelityDefault		(50)
#define kTracingFillsDefault				(true)
#define kTracingStrokesDefault				(false)
#define kTracingDetectShapesDefault			(true)
#define kTracingMaxStrokeWeightDefault		(10.0f)

/** Default is \c #kAIVectorizedResult */
#define kTracingVisualizeVectorDefault		(0)
/** Default is \c #kAITracingVisualizeRasterNone */
#define kTracingIgnoreWhiteDefault			(false)
#define kTracingSnapCurvesToLinesDefault	(false)

/** Internal */
#define kTracingSourceArtChangedDefault		(true)



/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a tracing state object, never dereferenced.
	Access with \c #AIVectorizeSuite. */
typedef struct _t_AITracingState *AITracingStateHandle;

/** Opaque reference to a view options object, never dereferenced.
	Access with \c #AIVectorizeSuite.  */
typedef struct _t_AITracingViewOptions *AITracingViewOptionsHandle;



/** Color models to which an image processing code can be reduced,
	an \c #AITracingModeValue. */
typedef ai::int32 AITracingMode;

enum ColorType
{
	kAIAutomaticTracingColors,
	kAILimitedTracingColors,
	kAIFullToneTracingColors,
};

/** Color models for \c #AITracingMode  */
enum VectorizeModes
{
	/** Color, either RGB or CMYK depending on source image.  */
	kAIVectorizeModeColor,
	/** Grayscale. */
	kAIVectorizeModeGray,
	/** Monochrome bitmap. */
	kAIVectorizeModeBlackAndWhite
};

enum OverlappingAbuttingValue
{
	kAIAbutting,
	kAIOverlapping,
};

typedef ai::int32 AIVectorizeVisualizeType;
/** Vector modes for tracing output in \c #AITracingVisualizeVectorType. */
enum AIVectorizeVisualizeVectorValue
{
	//The vector output only
	kAIVectorizedResult = 0,
	//Displays the vectors along with the path outline
	kAIVectorizedObjectWithOutline,
	//Displays the traced vectors in outline.
	kAIVectorizeOutline,
	//The vector outline is displayed along with 50% transparent source image.
	kAIVectorWithTransparentImage,
	//Displays the source image only
	kAISourceImage
};




/*******************************************************************************
 **
 **	Suite Record
 **
 **/


/**	@ingroup Suites
	This suite gives you access to the object model for the \e tracing art type,
	a plug-in group containing:
		\li A source image.
		\li A posterized/preprocessed version of the source image, called the tracing result or result group.
		\li The options used for tracing.
		\li The internal tracing state kept by the vectorization engine.
		\li The view options that determine which elements of the group to display during update.

	A tracing \e preset is a named collection of state information that can be used to recreate
	a commonly used tracing configuration. It includes parameters specific to the
	various tracing tasks such as color tracing, black and white tracing, high resolution
	tracing, low resolution tracing, and so on.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIVectorizeSuite and \c #kAIVectorizeVersion.
 */
typedef struct {

	/** Creates a tracing group whose source art is the specified raster or foreign object art.
		Use \c #Update() to create the result group.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object for the paint order.
			@param art A raster art object or a foreign object.
			@param tracing [out] A buffer in which to return the tracing plug-in group
	 */
	AIAPI AIErr (*CreateTracing) (ai::int16 paintOrder, AIArtHandle prep, AIArtHandle art, AIArtHandle *tracing);

	/** Reports whether an art object is a tracing group.
		(Note that this function returns a boolean value, not an error code.)
			@param tracing The art object.
			@return True if the art is a tracing group.
		*/
	AIAPI AIBoolean (*IsTracing) (AIArtHandle tracing);

	/** Retrieves the source art of a tracing group.
			@param tracing The tracing group object.
				@param raster [out] A buffer in which to return the source art,
					a raster art object or foreign object.
		*/
	AIAPI AIErr (*GetSourceImage) (AIArtHandle tracing, AIArtHandle *raster);

	/** Copies the tracing result art of a tracing group into the current document.
			@param tracing The tracing group object.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object for the paint order.
			@param art [out] A buffer in which to return the copied result group.
			@param copyAsViewed True to copy the tracing result as viewed; that is, maintaining the
				visual appearance of viewing modes currently in effect. False to copy
				as if in the Show-No-Image/Show-Tracing-Result mode.
		*/
	AIAPI AIErr (*CopyTracingArt) (AIArtHandle tracing, ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *art, AIBool8 copyAsViewed);

	/** Retrieves the tracing options dictionary of a tracing group.
			@param tracing The tracing group object.
			@param options [out] A buffer in which to return the options dictionary.
				This is a counted object (see \c AICountedObject.h).
				Use the \c Ref class to access it. See \c IAIRef.h.
				@see \c #kTracingOptionsKey
		 */
	AIAPI AIErr (*AcquireTracingOptions) (AIArtHandle tracing, AIDictionaryRef *options);

	/** Retrieves the tracing statistics dictionary of a tracing group.	This is a read-only dictionary.
			@param tracing The tracing group object.
			@param options [out] A buffer in which to return the statistics dictionary.
				This is a counted object (see \c AICountedObject.h).
				Use the \c Ref class to access it. See \c IAIRef.h.
				@see \c #kTracingStatisticsKey
		*/
	AIAPI AIErr (*AcquireTracingStatistics) (AIArtHandle tracing, AIDictionaryRef *options);

 	/** Embeds swatches in the tracing result.  Call after changing
 		the \c #kTracingPaletteKey option value.
			@param tracing The tracing group object.
	 */
	AIAPI AIErr (*EmbedSwatches) (AIArtHandle tracing);

	/** Creates the tracing result from the source art of a tracing group.
		Vectorizes the preprocessed image based on the input options.
			@param tracing The tracing group object.
	  */
	AIAPI AIErr (*Update) (AIArtHandle tracing);


	/** Retrieves the native resolution (if any) of an art object.
			@param art The art object, typically a tracing group, raster, or foreign object.
			@param dpi [out] A buffer in which to return the native resolution in DPI,
				if strictly uniform scaling	has been applied to the source art.
				or 0 if no native resolution is available.
	 	*/
	AIAPI AIErr (*GetNativeResolution) (AIArtHandle art, AIReal *dpi);

	/** Retrieves the effective resolution of a tracing object.
			@param art The tracing art object.
			@param dpi [out] A buffer in which to return:
				\li The resampling DPI if resampling is turned on
				\li The effective resolution in DPI	if strictly uniform scaling has been applied to the source art.
				\li The average of x/y DPI if non-uniform scaling has been applied.
		 */
	AIAPI AIErr (*GetEffectiveResolution) (AIArtHandle art, AIReal *dpi);

	/** Marks or unmarks a tracing art object as changed. Changed art is reprocessed.
			@param tracing The tracing art object.
			@param changed True to reprocess the source art, false to mark it as unchanged.
		*/
	AIAPI AIErr (*SetSourceArtChanged) (AIArtHandle tracing, AIBoolean changed);

} AIVectorizeSuite;







#include "AIHeaderEnd.h"


#endif
