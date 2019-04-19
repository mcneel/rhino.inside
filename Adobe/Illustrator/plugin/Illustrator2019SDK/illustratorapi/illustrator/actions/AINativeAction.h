#ifndef _AINATIVEACTION_H_
#define _AINATIVEACTION_H_

/*
 *        Name:	AINativeAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Native File Format Action Parameters.
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

#ifndef __AITypes__
#include "AITypes.h"
#endif

// -----------------------------------------------------------------------------
//	Types.
// -----------------------------------------------------------------------------

/** Dictionary key values for \c #kAINativeScriptKey and
   	\c #kAIEPSScriptKey. */
typedef enum _AIFileFormatScriptCompatibility {
	kAIFileFormatScriptCompatibleEnglish = 0,
	kAIFileFormatScriptCompatibleCJK
} AIFileFormatScriptCompatibility;

/** Dictionary key values for \c #kAINativeFlatteningOptionKey
	and \c #kAIEPSFlatteningOptionKey. */
typedef enum _AIFileFormatFlattening {
	kAIFileFormatFlatteningPreservePaths = 0,
	kAIFileFormatFlatteningPreserveAppearance = 1,
	kAIFileFormatFlatteningPreserveAppearanceAndOverprints = 2
} AIFileFormatFlattening;

/** Dictionary key values for \c #kAIEPSFormatKey. */
typedef enum _AIEPSFilePreview {
	kAIEPSFilePreviewNone = 1,
	kAIEPSFilePreviewBWPICT,
	kAIEPSFilePreviewColorPICT,
	kAIEPSFilePreviewBWTIFF,
	kAIEPSFilePreviewColorTIFF,
	kAIEPSFilePreviewSimpleColor
} AIEPSFilePreview;

/** Dictionary key values for \c #kAIEPSOverprintsKey. */
typedef enum _AIEPSOverprints {
	kAIEPSFileOverprints_Preserve = 1,
	kAIEPSFileOverprints_Discard,
	kAIEPSFileOverprints_Simulate
} AIEPSOverprints;


/** File format for saving as a native file in \c #kAISaveDocumentAsAction.	*/
#define kAINativeFileFormat								"Adobe Illustrator Any Format Writer"
/** File extension for saving as a native file in \c #kAISaveDocumentAsAction.	*/
#define kAINativeFileFormatExtension					"ai"

/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Integer: the file format version to use when saving. an \c #AIVersion value. */
const ActionParamKeyID kAINativeVersionKey				= 'crtr';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	 Integer, language script compatibility of the saved file, an
	 \c #AIFileFormatScriptCompatibility value. */
const ActionParamKeyID kAINativeScriptKey				= 'ext.';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Integer, whether to embed any linked images when saving. Non-zero causes
	images to be embedded. zero does not change the embedded/linked status of images. */
const ActionParamKeyID kAINativeIncludeImagesKey		= 'incl';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Integer: whether to embed all fonts. Non-zero causes all fonts to be embedded.*/
const ActionParamKeyID kAINativeEmbedAllFontsKey		= 'embd';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Boolean: when true, fonts using less than the percentage of characters
	specified by \c #kAINativeSubsetFontsRatioKey are subsetted.*/
const ActionParamKeyID kAINativeSubsetFontsBelowKey		= 'sbst';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Integer, [0..100]: Threshold percentage of character usage for font subsetting.
	See \c #kAINativeSubsetFontsBelowKey. */
const ActionParamKeyID kAINativeSubsetFontsRatioKey		= 'rato';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Integer: non-zero value causes the document color profile to be embedded in the file.*/
const ActionParamKeyID kAINativeEmbedProfileKey			= 'prfl';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Integer: whether to flatten layers when saving a document with transparency
	to a version that does not support transparency. An \c #AIFileFormatFlattening value. */
const ActionParamKeyID kAINativeFlatteningOptionKey		= 'flat';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Boolean: when true, the file contents are compressed, when false they are not. */
const ActionParamKeyID kAINativeCompressionKey			= 'cmpr';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	Boolean: when true, a PDF rendition of the document is saved together with
	native roundtrip information. When false, only roundtrip information is saved. */
const ActionParamKeyID kAINativePDFCompatibilityKey		= 'pdf ';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	When true, export multiple artboards specified in  \c # kAINativeSaveAllKey or 
	\c #kAINativeSaveRangeKey. When false,export all the artboards.*/
	const ActionParamKeyID kAINativeSaveMultipleArtboardsKey	= 'smab'; // boolean
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	When true, export all artboards. when false,export the artbaords in  \c #kAINativeSaveRangeKey specified */
    const ActionParamKeyID kAINativeSaveAllKey	= 'sall'; // boolean
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as a native file.
	The artboards range string. Optional when   \c # kAINativeSaveAllKey is true or  
	\c #kAINativeSaveMultipleArtboardsKey	is false*/
    const ActionParamKeyID kAINativeSaveRangeKey	= 'sran'; // string




//** File format for saving as an EPS file in \c #kAISaveDocumentAsAction.	*/
#define kAIEPSFileFormat								"Adobe Illustrator EPSF"
/** File extension for saving as an EPS file in \c #kAISaveDocumentAsAction.	*/
#define kAIEPSFileFormatExtension						"eps"

/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	The file format for EPS is \c #kAIEPSFileFormat. */
const ActionParamKeyID kAIEPSFormatKey					= 'wfmt';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Integer: the file format version to use when saving. an \c #AIVersion value. */
const ActionParamKeyID kAIEPSVersionKey					= 'crtr';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Integer, language script compatibility of the saved file, an
	 \c #AIFileFormatScriptCompatibility value.  */
const ActionParamKeyID kAIEPSScriptKey					= 'ext.';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Boolean: when true, embed linked images and EPS files when saving.
	When false, do not change the embedded/linked status of images. */
const ActionParamKeyID kAIEPSIncludePlacedKey			= 'iplc';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Boolean: when true, include a thumbnail image of the artwork that
	is displayed in the File Open dialog in Windows. When false, do not include
	the thumbnail image. */
const ActionParamKeyID kAIEPSIncludeThumbnailKey		= 'ithm';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Boolean: when true, rasterize gradients in the document or convert them to the type
	of gradients supported by the target device. It is equivalent to selecting the 
	"Compatible Gradient and Gradient Mesh Printing" check box in the EPS Save Options
	or Print dialog. */
const ActionParamKeyID kAIEPSCompatibleGradientPrintKey	= 'cgpt';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Integer: the format for writing raster image data in the EPS.
	When 0, use ASCII hex, when 1, use binary. Applies only when the
	version is AI8 or earlier.*/
const ActionParamKeyID kAIEPSImageFormatKey				= 'ifmt';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Boolean: when true, convert RGB values to CMYK in the EPS,
	using the current color settings. When false, send RGB values
	to the printer unconverted. */
const ActionParamKeyID kAIEPSCMYKPostScriptKey			= 'cmyk';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Boolean: when true, include CJK fonts in the PostScript stream.
	When false, do not include CJK fonts (they must be present on
	the printer to avoid substitution). */
const ActionParamKeyID kAIEPSIncludeCJKFontsKey			= 'icjk';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Integer: The PostScript level with which the EPS must be compatible. 1, 2 or 3. */
const ActionParamKeyID kAIEPSPostScriptLevelKey			= 'pslv';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Integer: whether to flatten layers when saving a document with transparency
	to a version that does not support transparency. An \c #AIFileFormatFlattening value. */
const ActionParamKeyID kAIEPSFlatteningOptionKey		= 'flat';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Boolean: when true, Illustrator includes its own halftone screens in the
	generated EPS. Applies only to AI8 and earlier. */
const ActionParamKeyID kAIEPSUseDefaultScreensKey		= 'dfsc';
/** Additional parameter for \c #kAISaveDocumentAsAction when saving as an EPS file.
	Integer: how to handle overprints in the EPS file. An \c #AIEPSOverprints value.  */
const ActionParamKeyID kAIEPSOverprintsKey				= 'eopt';


#endif
