#ifndef __AIColorConversion__
#define __AIColorConversion__

/*
 *        Name:	AIColorConversion.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Color Conversion Suite.
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

#include "IAIColorSpace.hpp"

#include "AIHeaderBegin.h"

/** @file AIColorConversion.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIColorConversionSuite			"AI Color Conversion Suite"
#define kAIColorConversionVersion10		AIAPI_VERSION(10)
#define kAIColorConversionSuiteVersion	kAIColorConversionVersion10
#define kAIColorConversionVersion		kAIColorConversionSuiteVersion

/** Color spaces that are available for conversion. See \c #AIColorConversionSuite::ConvertImageColor
	and \c #AIColorConversionSuite::ConvertSampleColor */
enum AIColorConversionSpaceValue {
	kAIMonoColorSpace	=		0,
	kAIGrayColorSpace	=		1,
	kAIRGBColorSpace	=		2,
	kAIARGBColorSpace	=		3,
	kAICMYKColorSpace	=		4,
	kAIACMYKColorSpace	=		5,
	kAIAGrayColorSpace	=		6,
	kAILabColorSpace	=		7
};


/** @ingroup Errors 
	See \c #AIColorConversionSuite. */
#define kColorConversionErr			'CCER'



/*******************************************************************************
 **
 **	Types
 **
 **/

/** A color sample pixel value. See \c #AIColorConversionSuite::ConvertSampleColorEx(). */
typedef AIReal AISampleComponent;
typedef AIFloat	AIFloatSampleComponent;
/** An image pixel value. See \c #AIColorConversionSuite::ConvertImageColorEx().  */
typedef unsigned char AIImageComponent;

/** Color-space conversion options. When converting CMYK to gray or RGB for
	preview or export, the constructor sets the appropriate black preservation
	value-- that is, whether a CMYK to RGB/Gray color transformation maps
	CMYK 0,0,0,1 to the darkest black:
		\li By default, the operation uses the standard conversion,
			which never uses black preservation.
		\li For export, the operation uses the black-preservation setting
			that is currently configured in the print and export preferences.
		\li For preview, the operation uses the black-preservation setting
			that is currently configured in the screen-display preferences.
	*/
class AIColorConvertOptions {
public:
	/** The purpose for performing a color-space conversion.  */
	enum Purpose {
		/** Do standard conversion, without black preservation.  */
		kDefault,
		/** Use conversion options appropriate to creating an image
			for screen display. */
		kForPreview,
		/** Use conversion options appropriate to creating an image
			for print or export. */
		kForExport,
		kDummy = 0xFFFFFFFF
	};
	/** Default color-space conversion option.
		The operation uses the standard conversion,
		which never uses black preservation. */
	AIColorConvertOptions () :
		purpose(kDefault)
	{
	}

	/** Creates  a color-conversion structure.
			@param _purpose The intended purpose of the conversion.
				When converting CMYK to gray or RGB for preview or export,
				sets the appropriate black preservation value.
			@return A color-conversion structure to pass to conversion
				functions.
			@see \c #AIColorConversionSuite::ConvertImageColor()<br>
				 \c #AIColorConversionSuite::ConvertImageColorEx()<br>
				 \c #AIColorConversionSuite::ConvertSampleColor()<br>
				 \c #AIColorConversionSuite::ConvertSampleColorEx()
		*/
	AIColorConvertOptions (const Purpose& _purpose) :
		purpose(_purpose)
	{
	}
	/** Copy constructor */
	AIColorConvertOptions (const AIColorConvertOptions& src) :
		purpose(src.purpose)
	{
	}

	/** Assignment operator */
	AIColorConvertOptions& operator= (const AIColorConvertOptions& src)
	{
		purpose = src.purpose;
		return *this;
	}
	/** The purpose for performing a color-space conversion.
		\c #kDefault, \c #kForPreview or \c #kForExport */
	Purpose purpose;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Provides functions for converting color values and image sample values
	between color spaces.

	\li If color management is on, the functions use the document profile if it has one,
	otherwise they use the profiles from the Color Settings dialog.
	\li If color management is off, the functions perform device conversions.

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIColorConversionSuite and \c #kAIColorConversionVersion.

*/
typedef struct {

	/** Converts a sample-component color from one color space to another.
		(This version uses colorspace data types.)
			@param srcSpace The source color space.
			@param srcColor The color to convert, a color sample object.
			@param dstSpace The destination color space.
			@param dstColor [out] A buffer in which to return the converted color sample object.
			@param options The options structure appropriate to the purpose
				of the conversion (preview or export). See \c #AIColorConvertOptions.
			@param inGamut [out] A buffer in which to return true if the source color was
				within the gamut of the destination space. Can be \c NULL.
		*/
	AIAPI AIErr (*ConvertSampleColorEx) ( const ai::ColorSpace &srcSpace, AIFloatSampleComponent *srcColor,
		                                  const ai::ColorSpace &dstSpace, AIFloatSampleComponent *dstColor,
										  const AIColorConvertOptions& options,
										  ASBoolean *inGamut);

	/** Converts an array of image pixels from one color space to another.
		(This version uses the colorspace data type and specific bits-per-pixel values.)
			@param srcSpace The source color space.
			@param srcBitsPerPixel The bits-per-pixel in the source color.
			@param srcColor The color to convert, an array containing the number of pixels
				specified by \c pixelCount, using the bits-per-pixel specified by \c srcBitsPerPixel.
			@param dstSpace The destination color space.
			@param dstBitsPerPixel The bits-per-pixel in the destination color.
			@param dstColor [out] A buffer in which to return the converted image, an array big enough
				to contain the number of pixels specified by \c pixelCount, using the bits-per-pixel
				specified by \c dstBitsPerPixel.
			@param pixelCount The number of pixels in the image.
			@param flags To specify that the bits of a 1-bit color space (\c #kAIMonoColorSpace)
				are inverted, pass the constant \c kRasterInvertBits.
			@param options The options structure appropriate to the purpose
				of the conversion (preview or export). See \c #AIColorConvertOptions.
		 */
	AIAPI AIErr (*ConvertImageColorEx)   ( const ai::ColorSpace &srcSpace,
											ai::int32 srcBitsPerPixel,
										   AIImageComponent *srcColor,
		                               	   const ai::ColorSpace &dstSpace,
										   ai::int32 dstBitsPerPixel,
										   AIImageComponent *dstColor,
										   ai::int32 pixelCount, ai::uint16 flags,
										   const AIColorConvertOptions& options);

	/** Converts a sample-component color from one color space to another.
			@param srcSpace The source color space, an \c #AIColorConversionSpaceValue.
			@param srcColor The color to convert, an array containing the number of color
				values appropriate to the source color space.
			@param dstSpace The destination color space, an \c #AIColorConversionSpaceValue.
			@param dstColor [out] A buffer in which to return the converted color, an array big enough
				to hold the number of color values appropriate to the destination color space.
			@param options The options structure appropriate to the purpose
				of the conversion (preview or export). See \c #AIColorConvertOptions.
			@param inGamut [out] A buffer in which to return true if the source color was
				within the gamut of the destination space.
		*/
	AIAPI AIErr (*ConvertSampleColor) ( ai::int32 srcSpace, AIFloatSampleComponent *srcColor,
										ai::int32 dstSpace, AIFloatSampleComponent *dstColor,
										const AIColorConvertOptions& options,
										AIBoolean *inGamut);

	/** Converts an array of image pixels from one color space to another.
			@param srcSpace The source color space, an \c #AIColorConversionSpaceValue.
			@param srcColor The color to convert, an array containing the number of pixels
				specified by \c pixelCount, where each pixel contains the number of color
				values appropriate to the source color space.
			@param dstSpace The destination color space, an \c #AIColorConversionSpaceValue.
			@param dstColor [out] A buffer in which to return the converted color, an array big enough
				to hold \c pixelCount pixels using the number of color values appropriate to the
				destination color space.
			@param pixelCount The number of pixels in the source image.
			@param flags To specify that the bits of a 1-bit color space (\c #kAIMonoColorSpace)
				are inverted, pass the constant \c kRasterInvertBits.
			@param options The options structure appropriate to the purpose
				of the conversion (preview or export). See \c #AIColorConvertOptions.
		 */
	AIAPI AIErr (*ConvertImageColor)   ( ai::int32 srcSpace, AIImageComponent *srcColor,
										ai::int32 dstSpace, AIImageComponent *dstColor,
										ai::int32 pixelCount, ai::uint16 flags,
										 const AIColorConvertOptions& options);
} AIColorConversionSuite;


#include "AIHeaderEnd.h"


#endif
