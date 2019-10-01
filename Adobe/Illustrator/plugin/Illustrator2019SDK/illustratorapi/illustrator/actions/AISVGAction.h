#ifndef _AISVGACTION_H_
#define _AISVGACTION_H_

/*
 *        Name:	AISVGAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator SVG Action Parameters.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2014 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include "AIDocumentAction.h"
#include "AISVGTypes.h"


// -----------------------------------------------------------------------------
// The following parameters can be specified when saving to SVG. To save a file
// as SVG issue an export action (kAISaveDocumentAsAction). Specify one of the
// formats and extensions below for the format key.
// -----------------------------------------------------------------------------

/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentFormatKey The format to write, \c #kAISVGFileFormat
			to export an uncompressed SVG file. */
#define  kAISVGFileFormat								"svg file format"
/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentExtensionKey The file extension,
			\c #kAISVGFileFormatExtension for uncompressed SVG.	*/
#define kAISVGFileFormatExtension						"svg"

/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentFormatKey The format to write, \c #kAISVGCompressedFileFormat
			to export a compressed SVG file. */
#define kAISVGCompressedFileFormat						"svg compressed file format"
/** SVG-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentExtensionKey The file extension,
			\c #kAISVGCompressedFileFormatExtension for compressed SVG.	*/
#define kAISVGCompressedFileFormatExtension				"svgz"

// Standard SVG Options
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The format for images in the SVG, an \c #AISVGImageFormats value */
const ActionParamKeyID kAISVGImageFormatKey				= 'iFmt'; // enum AIImageFormats
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The precision for number rounding, an \c #AISVGCoordinatePrecision value */
const ActionParamKeyID kAISVGPrecisionKey				= 'Prcs'; // enum AISVGCoordinatePrecision
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The type of SVG rendering, an \c #AISVGRendering value */
const ActionParamKeyID kAISVGRenderingKey				= 'Rndr'; // enum AISVGRendering
/** Parameter to \c #kAIExportDocumentAction for SVG. True to zoom. */
const ActionParamKeyID kAISVGZoomKey					= 'ZooM'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG. True to use the system font. */
const ActionParamKeyID kAISVGSystemFontKey				= 'SYFt'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Whether to subset fonts, an \c #AISVGFontSubsetting value */
const ActionParamKeyID kAISVGFontSubsettingKey			= 'FSbs'; // enum AISVGFontSubsetting
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Whether to embed fonts or create separate, linked files, an \c #AISVGFileLocation value */
const ActionParamKeyID kAISVGFontLocationKey			= 'FLct'; // enum AISVGFileLocation
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The character encoding, an \c #AISVGDocumentEncoding value */
const ActionParamKeyID kAISVGEncodingKey				= 'Encd'; // enum AISVGDocumentEncoding
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The file compression, an \c #AISVGFileCompression value */
const ActionParamKeyID kAISVGCompressionKey				= 'Cmzn'; // enum AISVGFileCompression
/** Parameter to \c #kAIExportDocumentAction for SVG.
	How style information should be exported, an \c #AISVGStyle value */
const ActionParamKeyID kAISVGStyleTypeKey				= 'StTp'; // enum AISVGStyle
/** Parameter to \c #kAIExportDocumentAction for SVG.
	What type of fonts to use, an \c #AISVGFontType value  */
const ActionParamKeyID kAISVGFontFormatKey				= 'fFmt'; // enum AISVGFontType



// Illustrator-specific SVG Options

/** Parameter to \c #kAIExportDocumentAction for SVG.
	Width unit, an \c #AISVGUnits value */
const ActionParamKeyID kAISVGWidthUnitKey				= 'WunT'; // enum AISVGUnits
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Height unit, an \c #AISVGUnits value */
const ActionParamKeyID kAISVGHeightUnitKey				= 'HunT'; // enum AISVGUnits
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Resolution unit, an \c #AISVGResolution value */
const ActionParamKeyID kAISVGResolutionUnitKey			= 'RzUt'; // enum AISVGResolution
/** Parameter to \c #kAIExportDocumentAction for SVG.
	What types of fonts to embed, an \c #AISVGEmbedFontFormats value */
const ActionParamKeyID kAISVGEmbedFontFormatsKey		= 'EFFt'; // enum AISVGEmbedFontFormats
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Whether to embed or link images, an \c #AISVGRasterLocation value */
const ActionParamKeyID kAISVGEmbedRasterLocationKey		= 'RLoc'; // enum AISVGRasterLocation
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Resolution for images (in the unit specified by \c #kAISVGResolutionUnitKey) */
const ActionParamKeyID kAISVGRasterResolutionKey		= 'RsRl'; // integer
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Gradient tolerance. */
const ActionParamKeyID kAISVGGradientTolerenceKey		= 'GrTl'; // real
/** Parameter to \c #kAIExportDocumentAction for SVG.
	How to treat text in paths, an \c #AISVGTextOnPath value */
const ActionParamKeyID kAISVGTextOnPathKey				= 'ToPt'; // enum AISVGTextOnPath
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to constrain proportions. */
const ActionParamKeyID kAISVGExportConstrainProportionsKey = 'Cstp'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to clip to the artboard. */
const ActionParamKeyID kAISVGExportClipToArtboardKey	= 'CTab'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to round-trip. */
const ActionParamKeyID kAISVGExportRoundTripKey			= 'Rrtr'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include the Adobe namespace. */
const ActionParamKeyID kAISVGIncludeAdobeNameSpaceKey	= 'Anxp'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include a template. */
const ActionParamKeyID kAISVGIncludeTemplateKey			= 'Temt'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The rectangle to use as the viewing box, an \c #AISVGRect. */
const ActionParamKeyID kAISVGViewBoxKey					= 'VieW'; // data AISVGRect
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include round-trip data.   */
const ActionParamKeyID kAISVGIncludePGFKey				= 'Ipgf'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include XMP metadata.  */
const ActionParamKeyID kAISVGIncludeXAPKey				= 'IXAP'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include slicing information.  */
const ActionParamKeyID kAISVGIncludeSlicesKey			= 'ISlc'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The SVG DTD to use, an \c #AISVGDTD value */
const ActionParamKeyID kAISVGDTDKey						= 'DTDt'; // enum AISVGDTD
/** Parameter to \c #kAIExportDocumentAction for SVG.
	The font type to use, an \c #AISVGFontType value. */
const ActionParamKeyID kAISVGFontTypeKey				= 'FTKt'; // enum AISVGFontType
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include automatic kerning data.  */
const ActionParamKeyID kAISVGDisbleAutoKerningKey		= 'IDAK'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to SVG Text On Path, false to write each character separately.  */
const ActionParamKeyID kAISVGUseSVGTextOnPathKey		= 'ITOP'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True when a component is being copied onto the clipboard, false when complete design being exported.  */
const ActionParamKeyID kCopyingSVG						= 'Copy'; //bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to include unused styles also.  */
const ActionParamKeyID kAISVGIncludeUnusedStylesKey		= 'IUSt'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	True to generate responsive SVG.  */
const ActionParamKeyID kAISVGGenerateResponsiveSVGKey		= 'GRSv'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
	Object names (IDs) to use, an \c #AISVGIdType value.  */
const ActionParamKeyID kAISVGIdTypeKey					= 'IdTK'; // enum AISVGIdType
/** Parameter to \c #kAIExportDocumentAction for SVG.
True to create minified SVG */
const ActionParamKeyID kAISVGMinifyKey					= 'mnfy'; // bool
/** Parameter to \c #kAIExportDocumentAction for SVG.
True to create responsive SVG */
const ActionParamKeyID kAISVGResponsiveKey = 'rpsv'; // bool
/**  Parameter to \c #kAIExportDocumentAction for SVG.
True to identify the action as export */
const ActionParamKeyID kAISVGExportActionKey = 'SiEK'; //bool

#endif	// _AISVGACTION_H_
