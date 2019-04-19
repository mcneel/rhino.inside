#ifndef _AISVGTYPES_H_
#define _AISVGTYPES_H_

/*
 *        Name:	AISVGTypes.h
 *     Purpose:	Adobe Illustrator SVG Types.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2014 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include "AIHeaderBegin.h"

// -----------------------------------------------------------------------------
//	Types.
// -----------------------------------------------------------------------------

/** The format for images within an SVG file.*/
typedef enum _AISVGImageFormats
{
	kAISVGFormatDefault  = 1,
	kAISVGFormatJPEG,
	kAISVGFormatGIF,
	kAISVGFormatPNG
} AISVGImageFormats;

/** The number of digits of precision after the decimal when rounding numbers. */
typedef enum _AISVGCoordinatePrecision
{
	kAISVGPrecision_1 = 1,
	kAISVGPrecision_2,
	kAISVGPrecision_3,
	kAISVGPrecision_4,
	kAISVGPrecision_5,
	kAISVGPrecision_6,
	kAISVGPrecision_7

} AISVGCoordinatePrecision;

/** The type of SVG rendering.  */
typedef enum _AISVGRendering
{
	kAISVGRenderingProgressive = 1,
	kAISVGRenderingBatched
} AISVGRendering;

/** How to subset fonts in the SVG. */
typedef enum _AISVGFontSubsetting
{
	kAISVGSubsettingNone = 1,
	kAISVGSubsettingGlyphsOnly,
	kAISVGSubsettingCommonEnglishOnly,
	kAISVGSubsettingGlyphsPlusEnglish,
	kAISVGSubsettingCommonRomanOnly,
	kAISVGSubsettingGlyphsPlusRoman,
	kAISVGSubsettingOutputEntireFont
} AISVGFontSubsetting;

/** Whether to embed fonts or create separate, linked files. */
typedef enum _AISVGFileLocation
{
	kAISVGLocationEmbed = 1,
	kAISVGLocationLink
} AISVGFileLocation;

/** The character set to use for the SVG file. */
typedef enum _AISVGDocumentEncoding
{
	/** ASCII */
	kAISVGISO8859Encoding = 1,
	/** UTF 8 */
	kAISVGUTF8Encoding,
	/** UTF 16 */
	kAISVGUTF16Encoding
} AISVGDocumentEncoding;

/** The compression to use for the SVG file. */
typedef enum _AISVGFileCompression
{
	kAISVGCompressionNone = 1,
	kAISVGCompressionGZIP

} AISVGFileCompression;

/** How style information should be exported. */
typedef enum _AISVGStyle
{
	kAISVGInLineStyle = 1,			// 'style' attributes on the SVG elements
	kAISVGEntityStyle,				// 'style' attributes that contain entity references
	kAISVGCSSStyle,					// 'class' attributes with corresponding CSS styles
	kAISVGPresentationAttrsStyle	// presentation attributes on the SVG elements
} AISVGStyle;

/** Units to use for dimensions and positions */
typedef enum _AISVGUnits
{
	kAISVGUnitCentimeters = 0,
	kAISVGUnitEms,
	kAISVGUnitInches,
	kAISVGUnitPicas,
	kAISVGUnitPixels,
	kAISVGUnitPoints,
	kAISVGUnitMillimeters
} AISVGUnits;

/** The resolution measurement unit. */
typedef enum _AISVGResolution
{
	kAISVGPixelsPerInch = 0,
	kAISVGPixelsPerCentimeter
} AISVGResolution;

/** What types of fonts to embed. */
typedef enum _AISVGEmbedFontFormats
{
	kAISVGEmbedFontTrueType = 0,
	kAISVGEmbedFontType1 ,
	kAISVGEmbedFontBoth
} AISVGEmbedFontFormats;

/** Whether images are embedded or saved as separate files. */
typedef enum _AISVGRasterLocation
{
	kAISVGImageEmbed = 1,
	kAISVGImagelink,
	kAISVGImagePreserve
} AISVGRasterLocation;

//** The SVG DTD type. */
typedef enum _AISVGDTD
{
	kAISVGDTD10 = -1,
	kAISVGDTD11,
	kAISVGDTDTiny11,
	kAISVGDTDTiny11Plus,
	kAISVGDTDBasic11,
	kAISVGDTDTiny12
} AISVGDTD;

/** What type of font to use. */
typedef enum _AISVGFontType
{
	kAISVGFontCEF = 0,
	kAISVGFontSVG,
	kAISVGFontOutline
} AISVGFontType;

/** How to treat text in paths. */
typedef enum _AISVGTextOnPath
{
	kAISVGTextOnPathSVG = 0,
	kAISVGTextOnPathIllustrator
} AISVGTextOnPath;

/** Rectangle, defined by upper left corner point, width and height */
typedef struct _AISVGRect
{
	float x;
	float y;
	float width;
	float height;
} AISVGRect;

/** Id/Class type to be used in svg to be exported */
typedef enum _AISVGIdType
{
	kAISVGIdMinimal = 0,
	kAISVGIdRegular,
	kAISVGIdUnique
} AISVGIdType;

#include "AIHeaderEnd.h"

#endif // _AISVGTYPES_H_
