#ifndef __AIDrawArt__
#define __AIDrawArt__

/*
 *        Name:	AIDrawArt.h
 *   $Revision: $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Draw Art Suite.
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIColorConversion__
#include "AIColorConversion.h"
#endif

#ifndef __AIRaster__
#include "AIRaster.h"
#endif

#include "AIAGMTypes.h"

#include "AIHeaderBegin.h"

/** @file AIDrawArt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDrawArtSuite				"AI Draw Art Suite"
#define kAIDrawArtSuiteVersion11		AIAPI_VERSION(11)
#define kAIDrawArtSuiteVersion		kAIDrawArtSuiteVersion11
#define kAIDrawArtVersion			kAIDrawArtSuiteVersion

/** Flag bits for \c #AIDrawArtFlags. */
enum AIDrawArtFlagBitPos {
	/** When set, draws in the preview mode, otherwise draws in the outline mode. */
	kAIDrawArtPreviewBit						= 0,
	/** Obsolete. */
	kAIDrawArtPreviewImagesBit					= 1,
	/** When set, draws dimmed images if \c #kAIDrawArtPreviewBit is set.
		Dimmed images have colors shifted towards white. */
	kAIDrawArtPreviewDimmedImagesBit			= 2,
	/** Obsolete. */
	kAIDrawArtPreviewPatternsBit				= 3,
	/** Obsolete.  */
	kAIDrawArtSelectObjectsBit					= 4,
	/** When set, draws guides.  */
	kAIDrawArtShowGuidesBit						= 5,
	/** (Not recommended.) When set, if drawing a single art object of type
		\c #kPlacedArt or \c #kRasterArt, the transformation
		applied to the object is set to identity before drawing.
		A better way to achieve the same effect is to use
		\c #AIDrawArtSuite::DrawThumbnail().
 	*/
	kAIDrawArtIgnoreArtTransformBit				= 6,
	/** Obsolete.  */
	kAIDrawArtPreviewCropBit					= 7,
	/** When set, a lengthy drawing operation can be interrupted
		in response to user activity.  If previewing is interrupted,
		\c #AIDrawArtSuite::DrawArt() returns \c #kDrawArtInterruptedErr
		and the \c interruptedArt member of the \c #AIDrawArtData is
		set to the object where drawing stopped.
	*/
	kAIDrawArtPreviewInterrupt					= 8,
	/** When set, continues an interrupted drawing operation from the
		point at which it was stopped. */
	kAIDrawArtPreviewContinue					= 9,
	/** (Not recommended.) When set, ignores dashes on strokes when
		drawing. */
	kAIDrawArtIgnoreDashedLines					= 10,
	/** Obsolete.  */
	kAIDrawArtDontColorCalibration				= 11,
	/** When set, the artwork is in an isolated transparency group that uses the
		document color space. A plug-in that draws into a dialog or palette must
		isolate the artwork to ensure that transparency blending is in the document
		color space. */
	kAIDrawArtIsolate							= 12,
	/** When set, ignores the transparency aspects (blend mode, opacity, and opacity mask)
		of the object being drawn. Does not ignore knockout and alpha in shape setting.
		If the object is an image, does not ignore the opacity of pixels. */
	kAIDrawArtIgnoreTopLevelTransparency		= 13,
	/** When set, modifies the color as if the image were printed
		on colored paper. The paper color is specified in the transparency
		panel of the document setup dialog. In that panel, there are two color
		swatches that normally define the colors for the transparency grid.
		The topmost swatch also defines the color that is used when simulating
		colored paper. 	 */
	kAIDrawArtSimulateColoredPaper				= 14,
	/** When set, any overprint specification on objects is ignored,
		so that colors do not overprint. */
	kAIDrawArtIgnoreOverprint					= 15,
	/** When set, placed EPS files are drawn by  parsing and rendering their
		PostScript contents instead of drawing their low resolution image proxies.
		The result is the same as turning off the preference "Use Low Resolution
		Proxy for Linked EPS".  */
	kAIDrawArtPlayEPS							= 16,
	/** When set, color conversion uses a faster but possibly less accurate
		algorithm. Use for interactive display but not for rasterization. */
	kAIDrawArtFastColorTransform				= 17,
	/** When set, disposes off cached patterns and regenerates them when rendering.
		Converting patterns into a renderable form for display takes time, so
		Illustrator normally caches the converted results. However, the results
		of conversion can depend on current application or document settings, such as
		color settings and document profile.  */
	kAIDrawArtDontCachePatterns					= 18,
	/** When set, draws the specified object regardless of whether it is hidden.  */
	kAIDrawArtIgnoreTopLevelInvisibility		= 19,
	/** When set, the initial state (that is, the state of the topmost object)
		for inherited knockout states is assumed to be on, rather than the default state of off.
		To use this flag, you must start a knockout transparency group before calling
		\c #AIDrawArtSuite::DrawArt(). */
	kAIDrawArtKnockoutAlreadyOn					= 20,
	/** Not used. */
	kAIDrawArtRunInBackground					= 21,
	/** When set, does not attempt to continue an interrupted render.
		Allows for more interruptability. */
	kAIDrawArtPreviewCannotContinue				= 22,
	/** When set, draws the object only if it is a clipping object,
		in order to establish a clip in the target port.
	 	By default, a clipping object passed to AIDrawArtSuite::DrawArt()
	 	is not drawn. */
	kAIDrawArtClipOnly							= 23,
	/** When set, draws to OPP port, simulating the appearance of spot colors.
		As with #kAIDrawArtIsolate, this isolates any blending modes
		from the backdrop.
		If the objects drawn should not be isolated from one another,
		and if multiple calls to \c #AIDrawArtSuite::DrawArt() are required,
		use \c #AIDrawArtSuite::BeginDrawArt().
		The spot plates needed are determined from the artwork
		that is to be drawn. */
	kAIDrawArtOPP								= 24,
	/** When set, ingnores overprint attribute applied to white objects.
		This works only for process colors and document model CMYK.
	*/
	kAISuppressWhiteOP							= 25,
	/** When set, text characters over which any SVG font is applied 
		will be drawn as outline
	*/
	kAIDrawSVGTextAsOutline						= 26,
	/** When set, text characters over which any color font is applied
		will be drawn as Image, this will be used for color fonts other
		than SVG color fonts 
	*/
	kAIDrawColorTextAsImage						= 27
};

/** Flag masks for #AIDrawArtFlags. See #AIDrawArtFlagBitPos. */
enum AIDrawArtFlagsValue {
	kAIDrawArtPreviewMask						= (1 << kAIDrawArtPreviewBit),
	kAIDrawArtPreviewImagesMask					= (1 << kAIDrawArtPreviewImagesBit),
	kAIDrawArtPreviewDimmedImagesMask			= (1 << kAIDrawArtPreviewDimmedImagesBit),
	kAIDrawArtPreviewImageOrDimImageMask		= (kAIDrawArtPreviewImagesMask | kAIDrawArtPreviewDimmedImagesMask),
	kAIDrawArtPreviewPatternsMask				= (1 << kAIDrawArtPreviewPatternsBit),
	kAIDrawArtSelectObjectsMask					= (1 << kAIDrawArtSelectObjectsBit),
	kAIDrawArtShowGuidesMask					= (1 << kAIDrawArtShowGuidesBit),
	kAIDrawArtIgnoreArtTransformMask			= (1 << kAIDrawArtIgnoreArtTransformBit),
	kAIDrawArtPreviewCropMask					= (1 << kAIDrawArtPreviewCropBit),
	kAIDrawArtPreviewInterruptMask				= (1 << kAIDrawArtPreviewInterrupt),
	kAIDrawArtPreviewContinueMask				= (1 << kAIDrawArtPreviewContinue),
	kAIDrawArtIgnoreDashedLinesMask				= (1 << kAIDrawArtIgnoreDashedLines),
	kAIDrawArtDontColorCalibrationMask			= (1 << kAIDrawArtDontColorCalibration),
	kAIDrawArtIsolateMask						= (1 << kAIDrawArtIsolate),
	kAIDrawArtIgnoreTopLevelTransparencyMask	= (1 << kAIDrawArtIgnoreTopLevelTransparency),
	kAIDrawArtSimulateColoredPaperMask			= (1 << kAIDrawArtSimulateColoredPaper),
	kAIDrawArtIgnoreOverprintMask				= (1 << kAIDrawArtIgnoreOverprint),
	kAIDrawArtPlayEPSMask						= (1 << kAIDrawArtPlayEPS),
	kAIDrawArtFastColorTransformMask			= (1 << kAIDrawArtFastColorTransform),
	kAIDrawArtDontCachePatternsMask				= (1 << kAIDrawArtDontCachePatterns),
	kAIDrawArtIgnoreTopLevelInvisibilityMask	= (1 << kAIDrawArtIgnoreTopLevelInvisibility),
	kAIDrawArtKnockoutAlreadyOnMask				= (1 << kAIDrawArtKnockoutAlreadyOn),
	kAIDrawArtRunInBackgroundMask				= (1 << kAIDrawArtRunInBackground),
	kAIDrawArtPreviewCannotContinueMask			= (1 << kAIDrawArtPreviewCannotContinue),
	kAIDrawArtClipOnlyMask						= (1 << kAIDrawArtClipOnly),
	kAIDrawArtOPPMask							= (1 << kAIDrawArtOPP),
	kAISuppressWhiteOPMask						= (1 << kAISuppressWhiteOP),
	kAIDrawSVGTextAsOutlineMask					= (1 << kAIDrawSVGTextAsOutline),
	kAIDrawColorTextAsImageMask					= (1 << kAIDrawColorTextAsImage)
};


/** Values for \c #AIDrawArtOutputType, specified in the \c type field
	of \c #AIDrawArtData structure. <br>Indicates the type of port
	that is specified as \c output, using an \c #AIDrawArtOutputUnion structure. */
enum AIDrawArtOutputTypeValue {
	kAIDrawArtUnknownOutput						= 0,
	/** Draw destination is a Mac OS GWorld in the \c gWorld member.
	 This type is no longer supported and returns error*/
	kAIDrawArtGWorldOutput						= 1,
	/** Draw destination is an \c AGMPort* in the \c port member.*/
	kAIDrawArtAGMPortOutput						= 2,
	/** Draw destination is an \c AGMPort* in the \c portV6 member. */
	kAIDrawArtAGMPortOutputV6					= 3,
	/** Draw destination is an \c AIStructuredPort* in the \c structPort member */
	kAIDrawArtStructuredPortOutput				= 4
};

/** Values for #AIDrawColorStyle */
enum AIDrawColorStyleValue {
	/** Fill style */
	kAIDrawColorStyleFill						= 0,
	/** Frame style */
	kAIDrawColorStyleFrame						= 1
};


/** Values for #AIDrawColorOptions */
enum AIDrawColorOptionsValue {
	/** Draws gradients as linear, even if they are radial. */
	kAIDrawArtGradientForceLinear				= (1 << 0),
	/** Does not convert colors to the document color model prior to drawing them.
		This allows drawing of out of gamut RGB colors when the current document
		color space is CMYK. */
	kAIDrawColorNoDocCsConversion				= (1 << 1)
};


/** @ingroup Errors */
#define	kUnknownDrawArtErr					'DHUH'
/** @ingroup Errors */
#define KUnknownDrawArtOutputTypeErr		'DOUT'
/** @ingroup Errors */
#define	kBadDrawArtPreviewMatrixErr			'DMTX'
/** @ingroup Errors */
#define kDrawArtInterruptedErr				'DITR'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** See \c #AIDrawArtFlagsValue for possible values. */
typedef ai::uint32 AIDrawArtFlags;
/** See \c #AIDrawArtOutputTypeValue for possible values. */
typedef ai::int32 AIDrawArtOutputType;

/** Information needed for drawing into a GWorld in Mac OS. */
typedef struct AIDrawArtGWorld {
	void *worldPointer;
} AIDrawArtGWorld;

/** Information needed for drawing into an AGM port. */
typedef struct AIDrawArtAGMPort {
	AIAGMPort *port;
	AIRect portBounds;
} AIDrawArtAGMPort;

/**  Information needed for drawing into an AGM version 6 port. */
typedef struct AIDrawArtAGMPortV6 {
	void *port;
	AIRect portBounds;
} AIDrawArtAGMPortV6;

/** The possible output targets for drawing art. */
typedef union {

	AIDrawArtGWorld gWorld;
	AIDrawArtAGMPort port;
	AIDrawArtAGMPortV6 portV6;
	struct AIStructuredPort* structPort;
} AIDrawArtOutputUnion;

/** Drawing data, defines an art object to be drawn, the object it is
	to be drawn into, and parameters affecting how it is to be
	drawn. See \c #AIDrawArtSuite::DrawArt(), \c #AIDrawArtSuite::BeginDrawArt() */
typedef struct AIDrawArtData {
	/** The version of \c #AIDrawArtSuite in use, a \c #kAIDrawArtVersion value. */
	ai::int16 version;
	/** Flags that modify drawing behavior, a logical OR of
		\c #AIDrawArtFlagBitPos values. */
	AIDrawArtFlags flags;
	/** The type of port that is the destination for the draw operation. */
	AIDrawArtOutputType type;
	/** The point in the source artwork coordinates that is mapped to (0,0) in
	 	the destination port.*/
	AIRealPoint origin;
	/** The transformation matrix to be applied after placement
		at the origin. */
	AIRealMatrix matrix;
	/** The art object to be drawn. */
	AIArtHandle art;
	/** The destination clipping bounds. */
	AIRealRect destClipRect;
	/** When true, \c destClipRect is erased before the art is drawn. */
 	AIBoolean eraseDestClipRect;
	/** The art object that was being drawn when the operation was
		interrupted. See \c #kAIDrawArtPreviewInterrupt and \c #kAIDrawArtPreviewContinue. */
	AIArtHandle interruptedArt;
	 /** The greeking threshold. If the point size of text,
	 	after transformation to the coordinate system of the
		destination port, is smaller than this value, the text
		is greeked. Use -1 to indicate no greeking. */
	AIReal greekThreshold;
	/** Not used */
	AIExtendedRGBColorRec selectionColor;
	/** The port that is the destination for the draw operation.*/
	AIDrawArtOutputUnion output;
	/** When true, draws only art overlapping \c #srcClipRect on the port */
	AIBoolean doSrcClip;
	/** If doSrcClip is true, draws only art having an overlap between srcClipRect
		and visual bound of the art.*/
	AIRealRect srcClipRect;
public:
	/** Default constructor. It initializes only doSrcClip. Rest of the initialization to be done by client*/
	AIDrawArtData():doSrcClip(false) // This ensures no porting effort for the change
	{
	}
} AIDrawArtData;


/** See #AIDrawColorStyleValue for possible values. */
typedef ai::int32 AIDrawColorStyle;
/** See #AIDrawColorOptionsValue for possible values. */
typedef ai::int32 AIDrawColorOptions;

/** Structure defining a color to draw the object, it is
	to be drawn into and parameters affecting how it is to be
	drawn. */
typedef struct AIDrawColorData {
	AIDrawArtOutputType type;

	AIDrawColorStyle style;
	AIDrawColorOptions options;
	AIColor color;
	AIRealRect rect;
	AIReal width;							// when style is frame

	union {
		AIDrawArtGWorld gWorld;
		AIDrawArtAGMPort port;
		AIDrawArtAGMPortV6 portV6;
	} output;
} AIDrawColorData;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	These functions draw Illustrator artwork to an \e output \e port
	(drawing surface). The port can be a screen window, or it can be
	an offscreen drawing surface used to rasterize artwork.

	The drawing options are controlled by values in an \c #AIDrawArtData
	structure and related option structures \c #AIColorConvertOptions and
	\c #AIDrawArtFlags.

	When drawing to a port whose color space does not match the
	document color space, bracket a sequence of calls
	to \c #DrawArt() with calls to.\c #BeginDrawArt() and \c #EndDrawArt().
	Examples are drawing a CMYK document to an RGB window,
	or an RGB document to a window with a different profile.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDrawArtSuite and \c #kAIDrawArtVersion.
 */
typedef struct {

	/** Draws artwork as specified
			@param data A pointer to the structure that specifies an art object
				to be drawn, the object it is to be drawn into, and
				parameters affecting how it is to be drawn.
			@param options An \c #AIColorConvertOptions object that sets
				the appropriate black preservation value--that is, whether
				a CMYK to RGB/Gray color transformation maps CMYK 0,0,0,1
				to the darkest black:
					\li By default, the operation uses the standard conversion,
						which never uses black preservation.
					\li For export, the operation uses the black-preservation setting
						that is currently configured in the print and export preferences.
					\li For preview, the operation uses the black-preservation setting
						that is currently configured in the screen-display preferences.
	*/
	AIAPI AIErr (*DrawArt)(AIDrawArtData *data, const AIColorConvertOptions& options );

	/** Establishes a temporary drawing surface whose color space matches the
		document space. Must be paired with a call to \c #EndDrawArt() at the end
		of a sequence of calls \c #DrawArt().
			@param data A pointer to the structure that specifies an art object
				to be drawn, the object it is to be drawn into, and
				parameters affecting how it is to be drawn. Can be \c NULL.
			@param options An \c #AIColorConvertOptions object; see \c #DrawArt().
			@param flags A set of options that modify drawing behavior, a logical
				OR of \c #AIDrawArtFlagBitPos values.
				@note If you set the \c #kAIDrawArtOPP flag to draw to an OPP port,
					the "begin" call temporarily changes the target port in the \c data
					structure. The call to \c #EndDrawArt() restores the
					original port. In this case, the set of spot colors needed for the
					OPP port are determined from the art object specified in \c data, or
					from the entire document if no art object is specified.

		*/
	AIAPI AIErr (*BeginDrawArt)(AIDrawArtData * data, const AIColorConvertOptions& options, AIDrawArtFlags flags );

	/** Copies the contents of the temporary drawing surface to the final destination.
			@param data A pointer to the drawing data structure that was passed to
				the corresponding call to \c #BeginDrawArt().
			@param options The \c #AIColorConvertOptions object that was passed to
				the corresponding call to \c #BeginDrawArt().
		*/
	AIAPI AIErr (*EndDrawArt)(AIDrawArtData *data, const AIColorConvertOptions& options );

	/** Draws a color swatch. Color swatches are always assumed to be drawn for the
		purpose of screen display.
			@param data A pointer to the structure that specifies an art object
				to be drawn, the object it is to be drawn into, and
				parameters affecting how it is to be drawn.
		*/
	AIAPI AIErr (*DrawColorSwatch)( AIDrawColorData *data );

	/** Draws the highlighting annotations for an art object. Call only in the response
		to an annotator's Draw Annotations message.
			@param art The art object.
			@param color The highlight color.
			@param lineWidth The stroke width.
	*/
	AIAPI AIErr (*DrawHilite)( AIArtHandle art, AIRGBColor* color, float lineWidth );

	/** Draws a thumbnail of an art object to the AGM port. Thumbnails are always assumed
		to be drawn for the purpose of screen display. No transformations are applied, and
		the image is drawn to fit into the destination rectangle.
			@param art The art object, of type \c #kRasterArt or \c #kPlacedArt.
			@param port A pointer to the AGM port.
			@param dstrect The destination rectangle, a bounding box for the thumbnail image.
		*/
	AIAPI AIErr (*DrawThumbnail) ( AIArtHandle art, void* port, AIRealRect* dstrect );

	/** Creates an AGM port for an image of given dimensions.
			@param width Width of the image.
			@param height Height of the image.
			@param outRport [out] A buffer in which to return the new raster port.
		*/
	AIAPI AIErr	(*CreateImagePort) (ai::uint32 width, ai::uint32 height, AIAGMPort **outRport);

	/** Retrieves the pixel data corresponding to the image created through \c #CreateImagePort().
		This is the read-only pixel data owned by the implementation;
		the caller should not allocate memory for the data. This pixel data
		is valid until you call \c #DestroyImagePort() (see example).
		Data of a particular pixel is in the form of ARGB (alpha, red, green and blue). The total length of pixel data
		is equal to 4 * width * height.

		@code
			//Example on how to call this method.
			size_t length = 0;
			const ai::uint8* pixelData = NULL;
			AIErr error = sAIDrawArt->GetImagePixelData(rport, &pixelData, &length, NULL, NULL);
		@endcode

			@param rport A pointer to the AGM port.
			@param outPixedData [out] A buffer in which to return a pointer to the pixel data bytes.
			@param outLength [out] A buffer in which to return the length of the pixel data in bytes.
			@param outWidth [out] A buffer in which to return the width of the image, or NULL if this information is not required.
			@param outHeight [out] A buffer in which to return the height of the image, or NULL if this information is not required.
		*/
	AIAPI AIErr	(*GetImagePixelData) (AIAGMPort *rport, const ai::uint8** outPixedData, size_t* outLength, ai::uint32* outWidth, ai::uint32* outHeight);

	/** Destroys the supplied AIAGMPort.
			@param rport A pointer to the AGM port.
		*/
	AIAPI AIErr	(*DestroyImagePort) (AIAGMPort *rport);

} AIDrawArtSuite;


#include "AIHeaderEnd.h"


#endif
