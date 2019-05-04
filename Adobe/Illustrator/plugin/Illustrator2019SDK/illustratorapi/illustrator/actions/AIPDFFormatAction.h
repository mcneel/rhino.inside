#ifndef _AIPDFFORMATACTION_H_
#define _AIPDFFORMATACTION_H_

/*
 *        Name:	AIPDFFormatAction.h
 *   $Revision: 1 $
 *      Author:	Hiromi M. Watanabe
 *        Date:	7/24/2002
 *     Purpose:	Adobe Illustrator PDF Action Parameters.
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

#ifndef __AIActionManager_h__
#include "AIActionManager.h"
#endif

// -----------------------------------------------------------------------------
//	Types.
// -----------------------------------------------------------------------------

/** Export to PDF action: option set */
typedef enum _AIPDFOptionSet
{
	kAIPDFOptionSetCustom  = 0

} AIPDFOptionSet;

/** Export to PDF action: flattening style */
typedef enum _AIPDFFlattenStyle
{
	kAIPDFFlattenStyleCustom  = 0

} AIPDFFlattenStyle;



/** Export to PDF action: version compatibility */
typedef enum _AIPDFCompatibility
{
	kAIPDFCompatibility13  = 0x0013, // Acrobat 4, PDF 1.3
	kAIPDFCompatibility14  = 0x0014,  // Acrobat 5, PDF 1.4
	kAIPDFCompatibility15  = 0x0015,  // Acrobat 6, PDF 1.5
	kAIPDFCompatibility16  = 0x0016,  // Acrobat 7, PDF 1.6
	kAIPDFCompatibility17  = 0x0017  // Acrobat 8, PDF 1.7
} AIPDFCompatibility;


/** Export to PDF action: color image compression */
typedef enum _AIPDFImageCompression
{
	kAIPDFImageNoCompression = 0,
	kAIPDFImageCompressionAutomaticJPEGMinimum,
	kAIPDFImageCompressionAutomaticJPEGLow,
	kAIPDFImageCompressionAutomaticJPEGMedium,
	kAIPDFImageCompressionAutomaticJPEGHigh,
	kAIPDFImageCompressionAutomaticJPEGMaximum,
	kAIPDFImageCompressionJPEGMinimum,
	kAIPDFImageCompressionJPEGLow,
	kAIPDFImageCompressionJPEGMedium,
	kAIPDFImageCompressionJPEGHigh,
	kAIPDFImageCompressionJPEGMaximum,
	kAIPDFImageCompressionAutomaticJPEG2000Minimum,
	kAIPDFImageCompressionAutomaticJPEG2000Low,
	kAIPDFImageCompressionAutomaticJPEG2000Medium,
	kAIPDFImageCompressionAutomaticJPEG2000High,
	kAIPDFImageCompressionAutomaticJPEG2000Maximum,
	kAIPDFImageCompressionAutomaticJPEG2000Lossless,
	kAIPDFImageCompressionJPEG2000Minimum,
	kAIPDFImageCompressionJPEG2000Low,
	kAIPDFImageCompressionJPEG2000Medium,
	kAIPDFImageCompressionJPEG2000High,
	kAIPDFImageCompressionJPEG2000Maximum,
	kAIPDFImageCompressionJPEG2000Lossless,
	kAIPDFImageCompressionZIP8bit,
	kAIPDFImageCompressionZIP4bit

} AIPDFImageCompression;



/** Export to PDF action: monochrome image compression */
typedef enum _AIPDFMonochromeImageCompression
{
	kAIPDFMonochromeImageNoCompression = 0,
	kAIPDFMonochromeImageCompressionCCITTG3,
	kAIPDFMonochromeImageCompressionCCITTG4,
	kAIPDFMonochromeImageCompressionZIP,
	kAIPDFMonochromeImageCompressionRunLength

} AIPDFMonochromeImageCompression;



/** Export to PDF action: downsampling technique */
typedef enum _AIPDFDownsampling
{
	kAIPDFNoDownsampling = 1,
	kAIPDFAverageDownsampling,
	kAIPDFSubsampling,
	kAIPDFBicubicsampling

} AIPDFDownsampling;

/** Export to PDF action: encryption level */
typedef enum _AIPDFEncryptionLevel
{
	kAIPDF40bitEncryption = 1,
	kAIPDF128bitEncryption

} AIPDFEncryptionLevel;

/** Export to PDF action: overprint options */
typedef enum _AIPDFOverprintOptions
{
	kAIPDFOPPreserve = 1,
	kAIPDFOPDiscard

} AIPDFOverprintOptions;

/** Export to PDF action: printer mark type */
typedef enum _AIPDFPrinterType
{
	kAIPDFPrintMarksStandard = 1,
	kAIPDFPrintMarksJapanese

} AIPDFPrinterType;

/** Export to PDF action: printer mark weight */
typedef enum _AIPDFPrinterMarkWeight
{
	kAIPDFPrintMarksWeight0125 = 1,
	kAIPDFPrintMarksWeight025,
	kAIPDFPrintMarksWeight05

} AIPDFPrinterMarkWeight;

/** Export to PDF action: print resolution allowed for document */
typedef enum _AIPDFPrintingPermit
{
	kAIPDFPrint128NoneIndex = 1,
	kAIPDFPrint128LowResIndex,
	kAIPDFPrint128HighResIndex,
	kAIPDFPrint40NoneIndex,
	kAIPDFPrint40HighResIndex

} AIPDFPrintingPermit;

/** Export to PDF action: allowed changes to document */
typedef enum _AIPDFChangesPermit
{
	kAIPDFChanges128NoneIndex = 1,
	kAIPDFChanges128EditPageIndex,
	kAIPDFChanges128FillFormIndex,
	kAIPDFChanges128CommentIndex,
	kAIPDFChanges128AnyIndex,
	kAIPDFChanges40NoneIndex,
	kAIPDFChanges40CommentIndex,
	kAIPDFChanges40PageLayoutIndex,
	kAIPDFChanges40AnyIndex

} AIPDFChangesPermit;

/** Export to PDF action: various settings for cropping. */
typedef ai::int32 AIPDFBoxType;
enum {
	kAIPDFArtBox,
	kAIPDFCropBox,
	kAIPDFTrimBox,
	kAIPDFBleedBox,
	kAIPDFMediaBox,
	kAIPDFBoundingBox
};


/** PDF-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentFormatKey The format to write, \c #kAIPDFFileFormat
			to export PDF. */
#define kAIPDFFileFormat									"PDF File Format"
/** PDF-format parameter value for \c #kAIExportDocumentAction.
		@param #kAIExportDocumentExtensionKey The file extension,
			\c #kAIPDFFileFormatExtension for PDF.	*/
#define kAIPDFFileFormatExtension							"pdf"

/** Parameter to \c #kAIExportDocumentAction for PDF. The page index. */
const ActionParamKeyID kAIPDFPageIndexKey					= 'page'; // integer, page index
/** Parameter to \c #kAIExportDocumentAction for PDF.  The form of cropping to be used, an \c #AIPDFBoxType value. */
const ActionParamKeyID kAIPDFCropToKey						= 'crop'; // enum, AIPDFBoxType

/** Parameter to \c #kAIExportDocumentAction for PDF. The page count. */
const ActionParamKeyID kAIPDFPageCountKey					= 'pgct'; // integer, page count

/** Parameter to \c #kAIExportDocumentAction for PDF. The option set index. */
const ActionParamKeyID kAIPDFOptionSetKey					= 'optn'; // integer, option set index.
/** Parameter to \c #kAIExportDocumentAction for PDF. The option set entry name. */
const ActionParamKeyID kAIPDFOptionSetNameKey				= 'opnm'; // string, option set entry name

/** Parameter to \c #kAIExportDocumentAction for PDF. The PDF version compatibility, an \c #AIPDFCompatibility value. */
const ActionParamKeyID kAIPDFCompatibilityKey				= 'comp'; // enum AIPDFCompatibility, compatibility
/** Parameter to \c #kAIExportDocumentAction for PDF. True to round-trip information (also called PGF). */
const ActionParamKeyID kAIPDFRoundTripKey					= 'rdtr'; // bool, include round trip information, aka PGF
/** Parameter to \c #kAIExportDocumentAction for PDF. True to generate thumbnails. */
const ActionParamKeyID kAIPDFGenerateThumbnailsKey			= 'thum'; // bool, generate thumbnails
/** Parameter to \c #kAIExportDocumentAction for PDF. True to view the PDF file after save. */
const ActionParamKeyID kAIPDFViewPDFFileKey					= 'vpdf'; // bool, view PDF file after saving
/** Parameter to \c #kAIExportDocumentAction for PDF. True to optimize for fast Web viewing. */
const ActionParamKeyID kAIPDFFastWebViewKey					= 'fwev'; // bool, optimize for fast web view

/** Parameter to \c #kAIExportDocumentAction for PDF. The type of color compression to use, an \c #AIPDFImageCompression value. */
const ActionParamKeyID kAIPDFColorImageCompressionKindKey	= 'cknd'; // enum AIPDFImageCompression, color image compression kind
/** Parameter to \c #kAIExportDocumentAction for PDF. The color image tile size. */
const ActionParamKeyID kAIPDFColorImageTileKey				= 'ctil'; // int, color image tile size
/** Parameter to \c #kAIExportDocumentAction for PDF. The color image resampling method, an \c #AIPDFDownsampling value. */
const ActionParamKeyID kAIPDFColorImageResampleKindKey		= 'crsl'; // enum, color image resample kind
/** Parameter to \c #kAIExportDocumentAction for PDF. The color image resolution (DPI). */
const ActionParamKeyID kAIPDFColorImageResolutionKey		= 'cres'; // int, color image resolution (dpi)
/** Parameter to \c #kAIExportDocumentAction for PDF. The color image resolution above which to resample (DPI). */
const ActionParamKeyID kAIPDFColorImageResampleAboveKey		= 'crab'; // int, resample color image above resolution (dpi)

/** Parameter to \c #kAIExportDocumentAction for PDF. The type of grayscale compression to use, an \c #AIPDFImageCompression value. */
const ActionParamKeyID kAIPDFGrayscaleImageCompressionKindKey = 'gknd'; // enum AIPDFImageCompression, gray scale image compression kind
/** Parameter to \c #kAIExportDocumentAction for PDF. The grayscale image tile size. */
const ActionParamKeyID kAIPDFGrayscaleImageTileKey			= 'gtil'; // int, grayscale image tile size
/** Parameter to \c #kAIExportDocumentAction for PDF. The grayscale image resampling method, an \c #AIPDFDownsampling value. */
const ActionParamKeyID kAIPDFGrayscaleImageResampleKindKey	= 'grsl'; // enum, grayscale image resample
/** Parameter to \c #kAIExportDocumentAction for PDF. The grayscale image resolution (DPI). */
const ActionParamKeyID kAIPDFGrayscaleImageResolutionKey 	= 'gres'; // int, grayscale image resolution
/** Parameter to \c #kAIExportDocumentAction for PDF. The grayscale image resolution above which to resample (DPI). */
const ActionParamKeyID kAIPDFGrayImageResampleAboveKey		= 'grab'; // int, resample grayscale image above resolution (dpi)

/** Parameter to \c #kAIExportDocumentAction for PDF. The monochrome image type, an \c #AIPDFMonochromeImageCompression value. */
const ActionParamKeyID kAIPDFMonochromeImageCompressionKindKey 	= 'mknd'; // enum AIPDFMonochromeImageCompression, monochrome image kind
/** Parameter to \c #kAIExportDocumentAction for PDF. The monochrome image resampling method, an \c #AIPDFDownsampling value.  */
const ActionParamKeyID kAIPDFMonochromeImageResampleKindKey	= 'mrsl'; // enum, monochrome image resample
/** Parameter to \c #kAIExportDocumentAction for PDF. The monochrome image resolution (DPI). */
const ActionParamKeyID kAIPDFMonochromeImageResolutionKey	= 'mres'; // int, monochrome image resolution
/** Parameter to \c #kAIExportDocumentAction for PDF. The monochrome image resolution above which to resample (DPI). */
const ActionParamKeyID kAIPDFMonochromeImageResampleAboveKey= 'mrab'; // int, resample monochrome image above resolution (dpi)

/** Parameter to \c #kAIExportDocumentAction for PDF. True to compress art. */
const ActionParamKeyID kAIPDFCompressArtKey					= 'cart'; // bool, compress art

/** Parameter to \c #kAIExportDocumentAction for PDF. True to print trim marks. */
const ActionParamKeyID kAIPDFTrimMarksKey					= 'ptrm'; // bool, Trim Marks
/** Parameter to \c #kAIExportDocumentAction for PDF. True to print registration marks. */
const ActionParamKeyID kAIPDFRegMarksKey					= 'preg'; // bool, Registration Marks
/** Parameter to \c #kAIExportDocumentAction for PDF. True to print color bars. */
const ActionParamKeyID kAIPDFColorBarsKey					= 'pclb'; // bool, Color Bars
/** Parameter to \c #kAIExportDocumentAction for PDF. True to print page information. */
const ActionParamKeyID kAIPDFPageInfoKey					= 'ppgi'; // bool, Page Info
/** Parameter to \c #kAIExportDocumentAction for PDF. The printer mark type, an \c #AIPDFPrinterType value. */
const ActionParamKeyID kAIPDFPrinterMarkTypeKey				= 'pmtp'; // enum, printer mark type
/** Parameter to \c #kAIExportDocumentAction for PDF. The trim mark weight, an \c #AIPDFPrinterMarkWeight value. */
const ActionParamKeyID kAIPDFTrimMarkWeightKey				= 'ptmw'; // enum, Trim Marks weight
/** Parameter to \c #kAIExportDocumentAction for PDF. The page offset from artwork, in document points. */
const ActionParamKeyID kAIPDFOffsetFromArtworkKey			= 'post'; // int, offset from artwork
/** Parameter to \c #kAIExportDocumentAction for PDF. The bleed top, in document points. */
const ActionParamKeyID kAIPDFBleedTopKey					= 'btop'; // int, bleed top
/** Parameter to \c #kAIExportDocumentAction for PDF. The bleed bottom, in document points. */
const ActionParamKeyID kAIPDFBleedBottomKey					= 'bbtm'; // int, bleed bottom
/** Parameter to \c #kAIExportDocumentAction for PDF. The bleed left, in document points. */
const ActionParamKeyID kAIPDFBleedLeftKey					= 'blft'; // int, bleed left
/** Parameter to \c #kAIExportDocumentAction for PDF. The bleed right, in document points. */
const ActionParamKeyID kAIPDFBleedRightKey					= 'brht'; // int, bleed right
/** Parameter to \c #kAIExportDocumentAction for PDF. True when bleed top, bottom, left and right are linked together.
	Corresponds to the link icon button in the Bleeds subsection of the Mark and Bleeds section of the PDF Export dialog. */
const ActionParamKeyID kAIPDFBleedLinkKey					= 'blnk'; // bool, bleed link
/** Parameter to \c #kAIExportDocumentAction for PDF. True when document bleeds are used. */
const ActionParamKeyID kAIPDFDocBleedKey					= 'bdoc'; // bool, doc bleed

/** Parameter to \c #kAIExportDocumentAction for PDF. True to embed ICC color profiles. */
const ActionParamKeyID kAIPDFEmbedICCProfilesKey			= 'emic'; // bool, embed ICC profiles
/** Parameter to \c #kAIExportDocumentAction for PDF. True to embed fonts. */
const ActionParamKeyID kAIPDFEmbedFontsKey					= 'embd'; // bool, embed fonts  **TO BE REMOVED**
/** Parameter to \c #kAIExportDocumentAction for PDF. True to subset fonts. */
const ActionParamKeyID kAIPDFSubsetFontsKey					= 'sbst'; // bool, subset fonts **TO BE REMOVED**
/** Parameter to \c #kAIExportDocumentAction for PDF. The ratio for font subsets. */
const ActionParamKeyID kAIPDFSubsetFontsRatioKey			= 'rato'; // real, subset fonts ratio

/** Parameter to \c #kAIExportDocumentAction for PDF. True to generate Acrobat layers. */
const ActionParamKeyID kAIPDFGenerateAcrobatLayersKey		= 'aclr'; // bool, generate Acrobat layers
/** Parameter to \c #kAIExportDocumentAction for PDF. The overprint style, an \c #AIPDFOverprintOptions value. */
const ActionParamKeyID kAIPDFOverprintKey					= 'pvop'; // enum, overprint
/** Parameter to \c #kAIExportDocumentAction for PDF. The flattening style, an \c #AIPDFFlattenStyle value. */
const ActionParamKeyID kAIPDFFlatteningStyleKey 			= 'flsy'; // enum, AIPDFFlatteningStyle
/** Parameter to \c #kAIExportDocumentAction for PDF. The flattening style name, a descriptive string.*/
const ActionParamKeyID kAIPDFFlatteningStyleNameKey 		= 'flsn'; // string, descriptive

/** Parameter to \c #kAIExportDocumentAction for PDF. The maximum resolution for flattening (DPI). */
const ActionParamKeyID kAIPDFFlattenMaxResolutionKey		= 'fmax'; // real, flattening style max resolution
/** Parameter to \c #kAIExportDocumentAction for PDF. The minimum resolution for flattening (DPI). */
const ActionParamKeyID kAIPDFFlattenMinResolutionKey		= 'fmin'; // real, flattening style min resolution
/** Parameter to \c #kAIExportDocumentAction for PDF. The vector balance for flattening. */
const ActionParamKeyID kAIPDFFlattenVectorBalanceKey		= 'fvba'; // int, flattening style vector balance
/** Parameter to \c #kAIExportDocumentAction for PDF. True to clip complex regions when flattening. */
const ActionParamKeyID kAIPDFFlattenClipComplexRegionsKey	= 'fccr'; // bool, flattening style clip complex regions
/** Parameter to \c #kAIExportDocumentAction for PDF. True to anti alias rasters when flattening. */
const ActionParamKeyID kAIPDFFlattenAntiAliasKey			= 'fcaa'; // bool, flattening style anti alias option
/** Parameter to \c #kAIExportDocumentAction for PDF. True to outline strokes when flattening. */
const ActionParamKeyID kAIPDFFlattenOutlineStrokesKey		= 'fosk'; // bool, flattening style outline strokes
/** Parameter to \c #kAIExportDocumentAction for PDF. True to outline text when flattening. */
const ActionParamKeyID kAIPDFFlattenOutlineTextKey			= 'fotx'; // bool, flattening style outline text
/** Parameter to \c #kAIExportDocumentAction for PDF. The printer resolution for flattening (DPI). */
const ActionParamKeyID kAIPDFFlattenPrinterResolutionKey	= 'fprs'; // real, flattening style printer resolution

/** Parameter to \c #kAIExportDocumentAction for PDF. True to include user password protection. */
const ActionParamKeyID kAIPDFUserPasswordRequiredKey		= 'usrq'; // bool, user password
/** Parameter to \c #kAIExportDocumentAction for PDF. The user password string. */
const ActionParamKeyID kAIPDFUserPasswordKey				= 'usps'; // string, user password
/** Parameter to \c #kAIExportDocumentAction for PDF. The to include master password protection. */
const ActionParamKeyID kAIPDFMasterPasswordRequiredKey		= 'msrq'; // bool, master password
/** Parameter to \c #kAIExportDocumentAction for PDF. The master password string. */
const ActionParamKeyID kAIPDFMasterPasswordKey				= 'msps'; // string, master password

/** Parameter to \c #kAIExportDocumentAction for PDF. The type of printing allowed, an \c #AIPDFPrintingPermit value. */
const ActionParamKeyID kAIPDFPrintingPermKey 				= 'pmpr'; // enum, Printing Allowed
/** Parameter to \c #kAIExportDocumentAction for PDF. The type of editing allowed, an \c #AIPDFChangesPermit value. */
const ActionParamKeyID kAIPDFChangesPermKey 				= 'pmch'; // enum, Changes Allowed

/** Parameter to \c #kAIExportDocumentAction for PDF. True to allow copying (with 128-bit encryption). */
const ActionParamKeyID kAIPDFEnableCopyKey					= 'ebcp'; // bool, Enable copying  (128-bit)
/** Parameter to \c #kAIExportDocumentAction for PDF. True to allow access (with 128-bit encryption). */
const ActionParamKeyID kAIPDFEnableAccessKey				= 'ebac'; // bool, Enable access  (128-bit)
/** Parameter to \c #kAIExportDocumentAction for PDF. True to allow copying and access (with 40-bit encryption). */
const ActionParamKeyID kAIPDFEnableCopyAccessKey			= 'ebca'; // bool, Enable copying and access  (40-bit)
/** Parameter to \c #kAIExportDocumentAction for PDF. True to allow plaintext metadata for an encrypted document. */
const ActionParamKeyID kAIPDFEnablePlaintextMetaKey			= 'ebpt'; // bool, Enable Plaintext Metadata

/** Parameter to \c #kAIExportDocumentAction for PDF. True to include linked files. */
const ActionParamKeyID kAIPDFIncludeLinkedFilesKey			= 'link'; // bool, include linked files


#endif //_AIPDFFORMATACTION_H_
