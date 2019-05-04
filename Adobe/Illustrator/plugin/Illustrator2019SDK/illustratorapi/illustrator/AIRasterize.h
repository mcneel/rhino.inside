#ifndef __AIRasterize__
#define __AIRasterize__

/*
 *        Name:	AIRasterize.h
 *   $Revision: 8 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Rasterize Suite.
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

#ifndef __AIArtSet__
#include "AIArtSet.h"
#endif

#ifndef __AIColorConversion__
#include "AIColorConversion.h"
#endif

#ifndef __AIFixedMath__
#include "AIFixedMath.h"
#endif

#ifndef __AIRaster__
#include "AIRaster.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIRasterize.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIRasterizeSuite				"AI Rasterize Suite"
#define kAIRasterizeSuiteVersion11		AIAPI_VERSION(11)

/* Latest version */
#define kAIRasterizeSuiteVersion		kAIRasterizeSuiteVersion11
#define kAIRasterizeVersion				kAIRasterizeSuiteVersion

/** The default anti-aliasing factor when rasterizing with anti-aliasing. */
#define kAIRasterizeDefaultAntialiasing	2


/** @ingroup DictKeys
	Key for the Live Effect rasterization parameter
	dictionary, stored in the document dictionary. Provides
	default settings for automatic rasterization that is part
	of a Live Effect.*/
#define kAIAutoRasterSettingsKey		"AI Auto Rasterize"
/** @ingroup DictKeys
	Default setting	for automatic rasterization.
	Entry value is an \c #AIRasterizeType. An integer. */
#define kDefaultRasterizeType			"colr"
/**  @ingroup DictKeys
	Default setting for automatic rasterization.
	An integer, a dots-per-inch resolution value.  */
#define kDefaultRasterizeDPI			"dpi."
/**  @ingroup DictKeys
	Default setting for automatic rasterization.
	A boolean, whether to use anti-aliasing. */
#define kDefaultRasterizeAlias			"alis"
/** @ingroup DictKeys
	Default setting	for automatic rasterization.
	A boolean, whether to preserve spot colors. If undefined, consider as false.  */
#define kDefaultRasterizePreserveSpot	"spot"
/**  @ingroup DictKeys
	Default setting for automatic rasterization.
	A boolean, whether to create a mask. */
#define kDefaultRasterizeMask			"mask"
/**  @ingroup DictKeys
	Default setting for automatic rasterization.
	An \c AIReal, a number of document points for padding. */
#define kDefaultRasterizePadding		"padd"


/** If the document does not have auto-rasterize settings specified in the
	document dictionary (see \c #kAIAutoRasterSettingsKey),
	use the values stored in the application preferences under this key. */
#define kRasterizePrefPrefix			"Rasterize/Defaults"


/**	@ingroup Errors
	Returned when attempting to rasterize artwork with settings
	that exceed the maximum width. The maximum width is affected
	by the antialiasing factor and by the color	model of the
	target raster.  See \c #AIRasterizeSuite. */
#define kAIRasterizeTooWideErr			'R2Wd'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** The desired color model and opacity of generated raster art.
	See \c #AIRasterizeSuite. */
enum AIRasterizeType {
	/** RGB no alpha */
	kRasterizeRGB = 0,
	/** CMYK no alpha */
	kRasterizeCMYK,
	/** Grayscale no alpha */
	kRasterizeGrayscale,
	/** opaque bitmap */
	kRasterizeBitmap,
	/** RGB with alpha */
	kRasterizeARGB,
	/** CMYK with alpha */
	kRasterizeACMYK,
	/** Grayscale with alpha */
	kRasterizeAGrayscale,
	/** Bitmap with transparent 0-pixels */
	kRasterizeABitmap,
	/** Separation no alpha */
	kRasterizeSeparation,
	/** Separation with alpha */
	kRasterizeASeparation,
	/** NChannel no alpha */
	kRasterizeNChannel,
	/** NChannel with alpha */
	kRasterizeANChannel
};

/** Options for how to perform rasterization. Bit flags can
	be combined with logical OR. */
enum AIRasterizeOptions {
	/** Clear all options */
	kRasterizeOptionsNone = 0,
	/** When set, incorporates layer attributes (such as opacity and blend mode)
		into the raster result. Otherwise, ignores layers in the input set. */
	kRasterizeOptionsDoLayers = 1<<0,
	/** When set, rasterize against a black background, rather than white. */
	kRasterizeOptionsAgainstBlack = 1<<1,
	/** When set, does not align 72 dpi images to the pixel grid. */
	kRasterizeOptionsDontAlign = 1<<2,
	/** When set, converts text to outlines before rasterizing it. */
	kRasterizeOptionsOutlineText = 1<<3,
	/** When set, does not supersamples; preserves type hinting. */
	kRasterizeOptionsHinted = 1<<4,
	/** When set, uses the Document Raster Effects Settings resolution. */
	kRasterizeOptionsUseEffectsRes = 1<<5,
	/** When set, uses a minimum of 5 tiles when rasterizing with
		anti-alias on (useful for better user feedback on progress bars). */
	kRasterizeOptionsUseMinTiles = 1<<6,
	/** When set, matte transparency with CMYK white. */
	kRasterizeOptionsCMYKWhiteMatting = 1<<7,
	/** When set, rasterizes to spot-color raster when a single separation channel is sufficient. */
	kRasterizeOptionsSpotColorRasterOk = 1<<8,
	/** When set, rasterization to NChannel image is allowed. */
	kRasterizeOptionsNChannelOk = 1<<9
};

/** Rasterization settings are collected into a single structure
	describing the type of raster desired, resolution, amount of
	anti-aliasing, and other options. */
struct AIRasterizeSettings {
	AIRasterizeSettings () :
		type(kRasterizeGrayscale),
		resolution(0),
		antialiasing(1),
		options(kRasterizeOptionsNone),
		ccoptions(AIColorConvertOptions::kDefault),
		preserveSpotColors(false)
	{
	}
	AIRasterizeSettings ( AIRasterizeType iType,
			AIReal iResolution,
			short iAntialiasing,
			AIRasterizeOptions iOptions,
			AIColorConvertOptions iCcoptions,
			AIBoolean iPreserveSpotColors) :
		type(iType),
		resolution(iResolution),
		antialiasing(iAntialiasing),
		options(iOptions),
		ccoptions(iCcoptions),
		preserveSpotColors(iPreserveSpotColors)
	{
	}
	AIRasterizeSettings (const AIRasterizeSettings& src) :
		type(src.type),
		resolution(src.resolution),
		antialiasing(src.antialiasing),
		options(src.options),
		ccoptions(src.ccoptions),
		preserveSpotColors(src.preserveSpotColors)
	{
	}
	AIRasterizeSettings& operator= (const AIRasterizeSettings& src)
	{
		type = src.type;
		resolution = src.resolution;
		antialiasing = src.antialiasing;
		options = src.options;
		ccoptions = src.ccoptions;
		preserveSpotColors = src.preserveSpotColors;
		return *this;
	}

	/** Color model and bit depth of raster to be produced */
	AIRasterizeType type;
	/** The resolution in dots-per-inch. Use 0 or 72 for 72 dpi */
	AIReal resolution;
	/** The supersampling factor, less than 2 for none, 2 or more
		for anti-aliasing.  */
 	short antialiasing;
	/** Additional options for how rasterization is performed,
		a logical OR of \c #AIRasterizeOptions. */
	AIRasterizeOptions options;
	/** Color conversion options, a logical OR of \c #AIColorConvertOptions. */
	AIColorConvertOptions ccoptions;
	/** When true, preserve spot colors wherever possible. */
	AIBoolean preserveSpotColors;
};

/** The image resampling method for \c #AIRasterizeSuite::ImageResample(). */
enum AIResamplingType {
	/** Default (anti-aliasing off). Fast, lowest quality */
	kSubsample = 0,
	/** Averaging sample (anti-aliasing on). Slower, better quality */
	kDownsample,
	/** Weighted average sample. Slowest, best quality */
	kBicubicDownsample

};

/** Progress callback function prototype for rasterization. You can supply
	this procedure to display a progress bar during a lengthy operation.
		@param current The index of the current tile being rasterized.
		@param total The total number of tiles to be rasterized.
		@return False to cancel the operation; otherwise true.
	*/
typedef AIAPI AIBoolean (*AIRasterizeProgressProc)(ai::int32 current, ai::int32 total);


/*******************************************************************************
 **
 **	Suite
 **
 **/


/**	@ingroup Suites
	This suite provides functions that allow you to convert any art
	set (see \c #AIArtSetSuite) into a single image, represented by
	a standard raster art object (an art object of type \c #kRasterArt).

	You can specify the bounds of rasterization, the destination color space,
	the image resolution, and whether the image will be anti-aliased.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIRasterizeSuite and \c #kAIRasterizeSuiteVersion.
 */
typedef struct {

/**	Retrieves the bounds for an entire art set.
		@param artSet The art set object.
		@param artBounds [out] A buffer in which to return the bounding rectangle.
		@param honorCropBox When true, and if cropping has been set, \c artBounds
			returns the crop box for the art. If false, or if no crop
			box has been set, \c artBounds returns the entire bounding box.
	*/
	AIAPI AIErr (*ComputeArtBounds) ( AIArtSet artSet,
									  AIRealRect *artBounds,
									  AIBoolean honorCropBox );

/** Creates a raster art object from an art set.
		@param artSet The art set object.
		@param settings Settings that describe the type of raster desired,
			resolution, amount of anti-aliasing, and other options.
		@param artBounds The bounding rectangle for the art
			to rasterize, which can be the one returned by \c #ComputeArtBounds().
		@param paintOrder The paint order, relative to the \c prep object,
			for the placement of the new object, an \c #AITypes::AIPaintOrder value.
		@param prep The prepositional art object for the paint order.
		@param raster [out] A buffer in which to return the new raster art object.
		@param progressProc	A callback function that presents a progress dialog
			during a lengthy operation.
	*/
	AIAPI AIErr (*Rasterize) ( AIArtSet artSet,
							   AIRasterizeSettings *settings,
							   AIRealRect *artBounds,
							   short paintOrder,
							   AIArtHandle prepArt,
							   AIArtHandle *raster,
							   AIRasterizeProgressProc progressProc );

/**	Creates a clipping mask from the result of rasterization of an art set.
	The function creates a clip group, places it in a new mask group,
	and returns the mask group. The clip group contains a union of all
	art objects in the art set, and an additional raster art object.
	This is the same as setting "Create Clipping Mask" when using
	the Object > Rasterize menu command.
		@param artSet The art set object. The function disposes of the art
			objects contained in this set, but does not dispose off this variable.
		@param paintOrder The paint order, which determines how the
			new mask group is placed relative to the raster art.
			Must be \c #kPlaceAbove or \c #kPlaceBelow.
		@param rasterArt A raster art object to be included in the clip group.
			The result of a call to \c #Rasterize() on the supplied art set.
		@param maskGroup [out] A buffer in which to return the new mask object.
	*/
	AIAPI AIErr (*CreateMask) ( AIArtSet artSet,
								short paintOrder,
								AIArtHandle rasterArt,
								AIArtHandle *maskGroup );

/**	Creates a raster art object from an art set, adding padding
	in both the horizontal and vertical dimensions.
		@param artSet The art set object.
		@param settings Settings that describe the type of raster desired,
			resolution, amount of anti-aliasing, and other options.
			If the setting specify an alpha channel, the padding pixels
			are fully transparent. Otherwise, they are white.
		@param artBounds The bounding rectangle for the art
			to rasterize, which can be the one returned by \c #ComputeArtBounds().
		@param paintOrder The paint order, relative to the \c prep object,
			for the placement of the new object, an \c #AITypes::AIPaintOrder value.
		@param prep The prepositional art object for the paint order.
		@param raster [out] A buffer in which to return the new raster art object.
		@param progressProc	A callback function that presents a progress dialog
			during a lengthy operation.
		@param padding The amount of padding to add to the resulting raster image,
			a number of document points.
	*/
	AIAPI AIErr (*RasterizeWithPadding) ( AIArtSet artSet,
										  AIRasterizeSettings *settings,
										  AIRealRect *artBounds,
										  short paintOrder,
										  AIArtHandle prepArt,
										  AIArtHandle *raster,
										  AIRasterizeProgressProc progressProc,
										  AIReal padding );

/**	Creates a raster art object from all of the art in the current document.
		@param settings Settings that describe the type of raster desired,
			resolution, amount of anti-aliasing and other options.
		@param artBounds The bounding rectangle for the art
			to rasterize, which can be the one returned by \c #ComputeArtBounds().
		@param paintOrder The paint order, relative to the \c prep object,
			for the placement of the new object, an \c #AITypes::AIPaintOrder value.
		@param prep The prepositional art object for the paint order.
		@param raster [out] A buffer in which to return the new raster art object.
		@param progressProc	A callback function that presents a progress dialog
			during a lengthy operation.
		@param options A set of option flags that control how the rasterization is performed.
			A logical OR of \c #AIRasterizeOptions.
	*/
	AIAPI AIErr (*RasterizeDocument) ( AIRasterizeSettings *settings,
							   short paintOrder,
							   AIArtHandle prepArt,
							   AIArtHandle *raster,
							   AIRasterizeProgressProc progressProc,
							   ai::int32 options );

/** Creates a new raster object by downsampling an existing raster object.
		@param rasterArt The raster art object.
		@param flag The type of sampling to perform, trading off speed and quality.
		@param resolution The resolution for the resulting image, in dots-per-inch (dpi) 
			or equivalently displayed as pixels-per-inch (ppi) in the UI.
		@param paintOrder The paint order, relative to the \c prep object,
			for the placement of the new object, an \c #AITypes::AIPaintOrder value.
		@param prep The prepositional art object for the paint order.
		@param newRasterArt [out] A buffer in which to return the new raster art object.
	*/

	AIAPI AIErr (*ImageResample) (AIArtHandle rasterArt,
									const AIResamplingType flag,
									const AIReal resolution,
									const short paintOrder,
									AIArtHandle prepArt,
									AIArtHandle *newRasterArt);

/** Reports whether rasterization can preserve spot colors for an art set.
		@param artSet The art set object.
		@param canPreserveSpotColor [out] A buffer in which to return true
			if spot colors can be preserved.
	*/

	AIAPI AIErr (*CheckSpotColorPreservation) (AIArtSet artSet,
									AIBoolean *canPreserveSpotColor);

	AIAPI void (*SnapRasterRectToPixelGrid)(AIRealRect &rect, AIReal ppi);


} AIRasterizeSuite;

#include "AIHeaderEnd.h"


#endif
