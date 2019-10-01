#ifndef __AIImageOptimization__
#define __AIImageOptimization__

/*
 *	Name:	AIImageOptimization.h
 *	Purpose:	Adobe Illustrator Image Optimization Suite
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

/********************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIDataFilter__
#include "AIDataFilter.h"
#endif

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#include "AIRasterize.h"

#include "AIHeaderBegin.h"

/** @file AIImageOptimization.h */

/********************************************************************************
 **
 **	Constants
 **
 **/

#define kAIImageOptSuite			"AI Image Optimization Suite"
#define kAIImageOptSuiteVersion7	AIAPI_VERSION(7)
#define kAIImageOptSuiteVersion		kAIImageOptSuiteVersion7
#define kAIImageOptVersion			kAIImageOptSuiteVersion

/** @ingroup Errors
Generic error for image optimization. See \c #AIImageOptSuite. */
#define kAIImageOptErr 'IMer'

/********************************************************************************
 **
 **	Types
 **
 **/

/** GIF parameters for image optimization. See \c #AIImageOptSuite. */
struct AIImageOptGIFParams{
	/** When true, the input image is interlaced. */
	AIBool8 interlaced;
	/** When true, the input image can use transparency. */
	AIBool8 transparencyAvailable;
	/** The number of colors in the input image, in the range [2..255]. */
	ai::int32 numberOfColors;
	/** The transparency index of the input image, in the range [0..numberOfColors-1]. */
	ai::int32 transparentIndex;
	/** Degree of lossiness for conversion, in the range [0..100]. */
	ai::int32 loss;

	/** The image resolution, in pixels per inch, of the input image. */
	AIFloat resolution;
	/** When true, include an alpha channel in the output image. */
	AIBool8 outAlpha;
	/** The width in pixels of the output image. */
	ai::int32 outWidth;
	/** The height in pixels of the output image.  */
	ai::int32 outHeight;
};

/** JPEG types for image optimization. See \c #AIImageOptSuite. */
enum AIImageOptJPEGKind {
	/** Standard JPEG */
	AIImageOptJPEGStandard,
	/** Optimized JPEG */
	AIImageOptJPEGOptimized,
	/** Progressive JPEG */
	AIImageOptJPEGProgressive
};

/** JPEG parameters for image optimization. See \c #AIImageOptSuite. */
struct AIImageOptJPEGParams{
	/** Degree of quality, in the range [0..100]. */
	ai::int32 quality;
	/** The type of JPEG to create. */
	AIImageOptJPEGKind kind;
	/** The number of scans to use. A number greater than one implies
		a progressive JPEG. Values are defined by the progressive JPEG specification.*/
	ai::int32 scans;
	/** The degree of blur, in the range [0..2]. */
	AIFloat blurAmount;

	/** The image resolution, in pixels per inch, of the input image.  */
	AIFloat resolution;
	/** When true, include an alpha channel in the output image. */
	AIBool8 outAlpha;
	/**  The width in pixels of the output image. */
	ai::int32 outWidth;
	/** The height in pixels of the output image. */
	ai::int32 outHeight;
};

/** PNG parameters for image optimization. See \c #AIImageOptSuite and
additional parameters in \c #AIImageOptPNGParams2. */
struct AIImageOptPNGParams {
	/** When true, the input image is interlaced. */
	AIBool8 interlaced;
	/** The number of colors in the input image, in the range [2..255]. */
	ai::int32 numberOfColors;
	/** The transparency index of the input image, in the range [0..numberOfColors-1]. */
	ai::int32 transparentIndex;

	/** The image resolution, in pixels per inch, of the input image.   */
	AIFloat resolution;
	/** When true, include an alpha channel in the output image. */
	AIBool8 outAlpha;
	/**  The width in pixels of the output image. */
	ai::int32 outWidth;
	/** The height in pixels of the output image. */
	ai::int32 outHeight;
};

/** Preferred type of optimization of ZLIB rasterization. See \c #AIImageOptSuite. */
enum AIImageOptZLIBLevel {
	/** Use the default. */
	AIImageOptZLIBDefault = -1,
	/** Do not optimize. */
	AIImageOptZLIBNone = 0,
	/** Optimize for speed. */
	AIImageOptZLIBFast = 1,
	/** Optimize for size. */
	AIImageOptZLIBSmall = 9
};

/** ZLIB parameters for image optimization. See \c #AIImageOptSuite. */
struct AIImageOptZLIBParams{
	/** Optimization level (no optimization, or optimize for speed or size). */
	AIImageOptZLIBLevel level;
	/** The image resolution, in pixels per inch, of the input image.   */
	AIFloat resolution;
	/** When true, include an alpha channel in the output image. */
	AIBool8 outAlpha;
	/**  The width in pixels of the output image. */
	ai::int32 outWidth;
	/** The height in pixels of the output image. */
	ai::int32 outHeight;
};

/*
 *	AIImageOptSuiteVersion2 Types
 */

/** Additional PNG parametersfor image optimization. See \c #AIImageOptSuite and
additional parameters in \c #AIImageOptPNGParams. */
struct AIImageOptPNGParams2 {
	/** Version 1 parameters */
	AIImageOptPNGParams versionOneSuiteParams;
	/** When 0, do no antialiasing.
		When 1, ignore text antialias settings
		When 2, optimize for text antialiasing when rasterizing.
		*/
	ASInt32 antialias;
	/** A cropping box for the art. If empty or degenerate, do not crop. */
	AIRealRect cropBox;
	/** When true, rasterize against a transparent background,
		applying no matte color. */
	AIBool8 backgroundIsTransparent;
	/** When background is not transparent, rasterize against this
	matte color. */
	AIRGBColor matteColor;

#ifdef __cplusplus
	/** Constructor for \c #AIImageOptPNGParams2. */
	AIImageOptPNGParams2()
		:
			versionOneSuiteParams(),
			antialias(0),	// no text antialiasing
			cropBox(),
			backgroundIsTransparent(true),	// no matte color applied
			matteColor()
	{
		cropBox.top = 0.0; cropBox.left = 0.0; cropBox.bottom = 0.0; cropBox.right = 0.0;
		matteColor.red = 0; matteColor.green = 0; matteColor.blue = 0;
	};
#endif
};




/* Version 3 additions */


/** Opaque reference to a color palette object. Access with \c #AIImageOptSuite. */
typedef struct _t_AIColorPalette *AIColorPaletteHandle;

/** Opaque reference to an inverse color palette object. Access with \c #AIImageOptSuite. */
typedef struct _t_AIInverseColorPalette *AIInverseColorPaletteHandle;


/** Palette construction type options, an \c #AIPaletteTypeValue.*/
typedef short AIPaletteType;
/** \c #AIPaletteType options.*/
enum AIPaletteTypeValue
{
	/** Generate palette automatically, based on the input image. */
	kAIAutomaticPalette,

	/** Create a custom palette, based on predefined palette. */
	kAICustomPalette
};


/** Construction options for the palette used
 	in color reduction (posterization) of an image.
	See \c #AIImageOptSuite
  */
typedef struct AIPaletteOptions
{
	/** Palette type, automatic or custom. */
	AIPaletteType paletteType;

	/** The number of colors to use for automatic palette construction.
		(For a custom palette, use \c #AIImageOptSuite::SetPaletteColor()
		to set the color count.)	*/
	ai::int32 colorCount;

} AIPaletteOptions;


/** Defines a palette color. See \c #AIImageOptSuite */
struct AIPaletteColor
{
	/** Alpha channel value, in the range [0..255].  */
    unsigned char alpha;
	/** Red value, in the range [0..255]. */
    unsigned char r;
	/** Green value, in the range [0..255]. */
    unsigned char g;
	/** Blue value, in the range [0..255]. */
    unsigned char b;
};

/********************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	These functions allow you to rasterize an art object and
	stream the resulting raster to a data filter in various image formats.
	@see \c #AIDataFilterSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIImageOptSuite and \c #kAIImageOptVersion.
	*/
typedef struct {

	// AIImageOptSuiteVersion1 functions
	/** Rasterize art to GIF format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsGIF)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptGIFParams& params);

	/**  Rasterize art to JPEG format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsJPEG)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptJPEGParams& params);

	/**  Rasterize art to PNG24 format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsPNG)(				// as PNG24
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptPNGParams& params);

	/**  Rasterize art to ZLIB format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsZLIB)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptZLIBParams& params);

	// AIImageOptSuiteVersion2 functions

	/**  Rasterize art to PNG24 format. This differs from \c #AsPNG() in that it
		takes additional parameters and allows you to show a progress bar
		for a lengthy operation.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
			@param progressProc The procedure to call periodically during a lengthy operation,
				to provide the current progress status and allow the user to cancel.
		*/
	AIAPI AIErr (*MakePNG24)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptPNGParams2& params,
		AIRasterizeProgressProc progressProc);


	// AIImageOptSuiteVersion3 functions

	/** Creates a color palette for art.
			@param raster The art object.
			@param options The type of palette to create, automatic or custom.
			@param palette [out] A buffer in which to return the palette object.
		*/
	AIAPI AIErr (*CreatePalette) (AIArtHandle raster, const AIPaletteOptions *options, AIColorPaletteHandle *palette);

	/**	Frees the memory associated with a palette object when it is no longer
		needed.
			@param palette The palette object. Upon return, this reference is
				no longer valid.
		*/
	AIAPI AIErr (*DisposePalette) (AIColorPaletteHandle palette);

	/**	Retrieves a color from a color palette.
			@param palette The palette object.
			@param index The position index of the color.
			@param color [out] A buffer in which to return the color object.
		*/
	AIAPI AIErr (*GetPaletteColor) (AIColorPaletteHandle palette, ai::int32 index, AIPaletteColor *color);

	/**	Sets a color in a color palette.
			@param palette The palette object.
			@param index The position index of the color.
			@param color The color object.
		*/
	AIAPI AIErr (*SetPaletteColor) (AIColorPaletteHandle palette, ai::int32 index, AIPaletteColor *color);

	/** Creates an inverse color palette.
			@param palette The palette object.
			@param inverse [out] A buffer in which to return the inverse palette object.
			*/
	AIAPI AIErr (*CreateInversePalette) (AIColorPaletteHandle palette, AIInverseColorPaletteHandle *inverse);

	/**	Frees the memory associated with an inverse palette object when it is
		 no longer needed.
			@param inverse The inverse palette object. Upon return, this reference is
				no longer valid.
		*/
	AIAPI AIErr (*DisposeInversePalette) (AIInverseColorPaletteHandle inverse);

	/**	Retrieves the closest match to a color from an inverse color palette.
			@param palette The inverse palette object.
			@param color A pointer to the color object to match.
			@param index [out] A buffer in which to return the 0-based position
				index of the closest matching color.
		*/
	AIAPI AIErr (*GetPaletteIndex) (AIInverseColorPaletteHandle inverse, const AIPaletteColor *color, ai::int32 *index);

	/** Creates a color palette by posterizing the colors in a list.
			@param colorList The list of colors to be posterized, an array of color objects.
			@param colorListCount The number of color objects in the list.
			@param reduceColorCount The maximum number of colors the resulting palette should contain.
			@param palette [out] A buffer in which to return the palette object.
		*/
	AIAPI AIErr (*CreateReducedPalette) ( AIPaletteColor *colorList, int colorListCount, int reduceColorCount, AIColorPaletteHandle *palette  );
}
AIImageOptSuite;


#include "AIHeaderEnd.h"

#endif	// __AIImageOptimization__
