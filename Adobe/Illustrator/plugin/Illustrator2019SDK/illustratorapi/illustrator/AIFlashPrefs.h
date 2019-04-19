/*
 *        Name:	AIFlashPrefs.h
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1999-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

//-----------------------------------------------------------------------------

#ifndef	AIFLASHPREFS_H
#define	AIFLASHPREFS_H

#include "AIUnicodeString.h"
#include "AIHeaderBegin.h"

/** @file AIFlashPrefs.h */

/** Export options for layers */
typedef enum _FlashExportOption
{
	/** Export file to SWF file */
	exportAIFileToSWFFile = 1,
	/** Export layers to SWF frames */
	exportAILayersToSWFFrames,
	/** Export layers to SWF file */
	exportAILayersToSWFFiles,
  	/** Export layers to SWF symbols */
  	exportAILayersToSWFSymbols,
	/** Multiple Artboards */
	exportMultipleArtboards
} FlashExportOption;

 /** The version for the exported SWF File */
 typedef enum _FlashExportVersion
 {
 	swfVersion1 = 1,
 	swfVersion2,
 	swfVersion3,
 	swfVersion4,
 	swfVersion5,
 	swfVersion6,
 	swfVersion7,
 	swfVersion8,
	swfVersion9
 } FlashExportVersion;

/** Output area */
typedef enum _FlashOutputSize
{
	/** Entire art bounds */
	outputArtBounds = 1,
	/** Bounds of crop area contents */
	outputCropAreaBounds,
	/** Bounds of art board contents */
	outputArtboardBounds
} FlashOutputSize;

/** Image format */
typedef enum _FlashImageFormat
{
	/** ZLIB */
	formatZLIB = 1,
	/** JPEG (trailing underscore to distinguish from SVG value). */
	formatJPEG_
} FlashImageFormat;

/** JPEG image quality options */
typedef enum _FlashJPEGQuality
{
	qualityLow = 1,
	qualityMedium,
	qualityHigh,
	qualityMaximum
} FlashJPEGQuality;

/** JPEG rasterization method */
typedef enum _FlashJPEGMethod
{
	methodBaseline = 1,
	methodOptimized
} FlashJPEGMethod;

/** Flash local-playback security  level */
typedef enum _FlashPlaybackSecurity
{
 	methodLocalFilesOnly = 1,
 	methodNetworkFilesOnly
} FlashPlaybackSecurity;


/** Whether and how to overwrite an existing file. */
typedef enum _FlashOverwriteOption
{
	kAskBeforeReplacingFile = 1,
	kAlwaysReplaceExistingFile,
	kNeverReplaceExistingFile
} FlashOverwriteOption;

/** Animation blending options */
typedef enum _FlashAnimateBlendOption {
	kAnimateBlendNone = 0,
	kAnimateBlendInSequence = 1,
	kAnimateBlendInBuild
} FlashAnimateBlendOption ;

/** Conversion and export options */
typedef struct _FlashOptions
{
 	/** SWF preset name. Set to empty string to use [Default] */
	ASUnicode				m_presetName[256];
	/** Export options */
	FlashExportOption		m_exportOption;
 	/** Version of the exported SWF file*/
 	FlashExportVersion		m_exportVersion;
	/** The number of frames per second that the player will use in rendering
		the SWF file. In the range [0.01..120] */
	AIReal					m_frameRate;
	/** When true, make a loop. */
	AIBoolean				m_looping;
	/** When true, write an SWF file that cannot be imported by other
		applications, but only read by the flash player for rendering.
		Corresponds to "Protect from Import" in the UI.*/
	AIBoolean				m_readOnly;
	/** Output area (artboard or page) */
	FlashOutputSize			m_outputSize;
	/** Curve quality, a value in the range [0..10], which controls the tolerance as
		cubic bezier curves are converted to quadratic curves. 0 is the highest tolerance
		resulting in lowest quality, 10 is the lowest tolerance resulting in highest quality.*/
	int				m_curveQuality;
	/** Image format (JPEG or ZLIB)  */
	FlashImageFormat		m_imageFormat;
	/** Image quality for JPEG */
	FlashJPEGQuality		m_jpegQuality;
	/** Rasterization method for JPEG */
	FlashJPEGMethod			m_jpegMethod;
	/** Image resolution in pixels per inch */
	AIReal					m_imageResolution;
	/** Whether and how to overwrite an existing file */
	FlashOverwriteOption	m_overwriteOption;
	/** When true, flatten layers before conversion */
	AIBoolean				m_flattenArtwork;
	/** When true, \c m_bgLayerIndex specifies a list of layers to use as
		static contents  in the animated SWF file. The contents of those layers
		is included in every SWF frame. */
	AIBoolean				m_useBackground;
	/** Pointer to an array of layers to use as static contents in the animated SWF file
		if \c m_useBackground is true.
		The contents of those layers is included in every SWF frame. */
	ai::int32				*m_bgLayerIndex;
	/** When animating blends, the animation method. Default is \c #kAnimateBlendNone. */
	FlashAnimateBlendOption m_animateBlendOption;
	/** When true, convert layers from the top down */
	AIBoolean				m_orderLayersTopDown;
	/** The background color */
	AIRGBColor				m_backgoundColor;
	/** When true, export text as outlines */
	AIBoolean				m_exportTextAsOutlines;
	/** When true, compress the output file */
	AIBoolean				m_compressFile;
 	/** When true, export all symbols in Symbols palette to the SWF File */
 	AIBoolean				m_exportArtboardSymbols;
 	/** When true, ignore kerning in the text objects */
 	AIBoolean				m_ignoreTextKerning;
 	/** Whether the SWF file can access local files only, or network files only */
 	FlashPlaybackSecurity	m_playbackSecurity;
 	/** When true, include some metadata information for the SWF file
		(such as Author, Title, Description). */
 	AIBoolean				m_includeMetadata;
} FlashOptions;

//-----------------------------------------------------------------------------

#define	kFlashPrefPrefix					"FlashFormat"

#define kFlashPrefPresetName				"FlashExportPreset"

#define kFlashPrefAdvancedOptions			"FlashAdvancedOptions"
#define kFlashPrefDefaultAdvancedOptions	false

#define	kFlashPrefExportOption				"FlashExportOption"
#define	kFlashPrefDefaultExportOption		exportAIFileToSWFFile

#define kFlashPrefExportVersion				"FlashExportVersion"
#define kFlashPrefDefaultExportVersion		swfVersion9

#define	kFlashPrefFrameRate					"FlashFrameRate"
#define	kFlashPrefDefaultFrameRate			12.0

#define	kFlashPrefLooping					"FlashLooping"
#define	kFlashPrefDefaultLooping			false

#define	kFlashPrefReadOnly					"FlashReadOnly"
#define	kFlashPrefDefaultReadOnly			false

#define	kFlashPrefOutputSize				"FlashOutputSize"
#define	kFlashPrefDefaultOutputSize			outputArtBounds

#define	kFlashPrefCurveQuality				"FlashCurveQuality"
#define	kFlashPrefDefaultCurveQuality		7

#define	kFlashPrefImageFormat				"FlashImageFormat"
#define	kFlashPrefDefaultImageFormat		formatZLIB

#define kFlashPrefJPEGQuality				"FlashJPEGQuality"
#define	kFlashPrefDefaultJPEGQuality		(FlashJPEGQuality)3

#define	kFlashPrefJPEGMethod				"FlashJPEGMethod"
#define	kFlashPrefDefaultJPEGMethod			methodBaseline

#define	kFlashPrefImageResolution			"FlashImageResolution"
#define	kFlashPrefDefaultImageResolution	72.0

#define	kFlashPrefOverwriteOption			"FlashOverwriteOption"
#define	kFlashPrefDefaultOverwriteOption	kAskBeforeReplacingFile

#define	kFlashPrefPreserveAppearance		"FlashPreserveAppearance"
#define	kFlashPrefDefaultPreserveAppearance	false

#define kFlashPrefUseBackground				"FlashUseBackground"
#define kFlashPrefDefaultUseBackground		false

#define kFlashPrefAnimateBlendOption		"FlashAnimateBlendOption"
#define kFlashPrefDefaultAnimateBlendOption kAnimateBlendNone

#define kFlashPrefOrderLayersOption			"FlashOrderLayersTopDown"
#define kFlashPrefDefaultOrderLayersOption	false

#define kFlashPrefTextAsOutlines			"FlashTextAsOutlines"
#define kFlashPrefDefaultTextAsOutlines		true

#define	kFlashPrefBackgroundColorRed		"FlashBackgroundColorRed"
#define kFlashPrefDefaultBackGroundRed		0xFFFF

#define	kFlashPrefBackgroundColorGreen		"FlashBackgroundColorGreen"
#define kFlashPrefDefaultBackGroundGreen	0xFFFF

#define	kFlashPrefBackgroundColorBlue		"FlashBackgroundColorBlue"
#define kFlashPrefDefaultBackGroundBlue		0xFFFF

#define kFlashPrefCompressFile				"FlashCompressFile"
#define kFlashPrefDefaultCompressFile		false


#define kFlashPrefExportArtboardSymbols		"FlashArtboardSymbols"
#define kFlashPrefDefaultExportArtboardSymbols false

#define kFlashPrefIgnoreTextKerning			"FlashIgnoreTextKerning"
#define kFlashPrefDefaultIgnoreTextKerning	false

#define kFlashPrefPlaybackSecurity			"FlashLocalPlaybackSecurity"
#define kFlashPrefDefaultPlaybackSecurity	methodLocalFilesOnly

#define kFlashPrefIncludeMetadata			"FlashXMPMetadata"
#define kFlashPrefDefaultIncludeMetadata	false


#include "AIHeaderEnd.h" // __cplusplus

#endif
