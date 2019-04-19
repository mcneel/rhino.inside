#ifndef __AIRaster__
#define __AIRaster__

/*
 *        Name:	AIRaster.h
 *   $Revision: 24 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Raster Object Suite.
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

#include "IAIFilePath.hpp"
#include "IAIColorSpace.hpp"

#include "AIHeaderBegin.h"

/** @file AIRaster.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIRasterSuite			"AI Raster Suite"
#define kAIRasterSuiteVersion10	AIAPI_VERSION(10)
#define kAIRasterSuiteVersion	kAIRasterSuiteVersion10
#define kAIRasterVersion		kAIRasterSuiteVersion


/** Options for raster data, bit flags for \c #AIRasterRecord::flags. */
enum AIRasterFlags {
	/** Used only for 1-bit gray images. When set, the 1-bit data
		is to be used as a mask. In this case the path style of the image indicates
		the color that the bits of the image with a value of 1 are painted. */
	kRasterMaskImageType		= 0x0002,
	/** Used only for 1-bit gray images. Reverses the sense of the component
		values so that for a gray image 0=white and 1=black and for an image mask
		the 0 value pixels are painted. */
	kRasterInvertBits			= 0x0004,
	/** Used only for 8-bit spot color rasters, or 16-bit if there is an extra
	    alpha channel. When set, the gray component values are interpreted in
		the subtractive color spaces. */
	kRasterGraySubtractive		= 0x0008
};

/** Maximum number of channels per image pixel */
#define kMaxChannels		32

/** Maximum number of spot color channels per image pixel */
#define kMaxSpotChannels	27

/** Color models for raster data */
enum AIRasterColorSpace {
	/** Flag indicating that the color model has an alpha channel. The alpha
		component appears after the color components. */
	kColorSpaceHasAlpha			= 0x10,

	/** Each pixel value for a gray color space has a single component
		describing a grayscale value. The gray color space is additive so the minimum
		value represents black and the maximum represents white. */
	kGrayColorSpace				= 0,
	/** Each pixel value for a RGB color space has three components which
		represent red, green and blue respectively. The RGB color space is additive. */
	kRGBColorSpace				= 1,
	/** Each pixel value for a CMYK color space has four components which
		represent cyan, magenta, yellow and black respectively. The CMYK color space
		is subtractive. */
	kCMYKColorSpace				= 2,
	/** Not valid as an image type; can occur only in placed linked
		files. See \c #AIPlacedSuite::GetRasterInfo(). */
	kLabColorSpace				= 3,
	/** Each pixel value for a separation color space has a single component
		describing a tint value. The separation color space is subtractive so the minimum
		value represents white and the maximum represents black. */
	kSeparationColorSpace		= 4,
	/** Each pixel value for an NChannel color space has of a variable number of
		components which represent individual channels in the NChannel color space.
		The process components of the color space could be either additive or subtractive.
		The spot components of the color space are subtractive. */
	kNChannelColorSpace			= 5,
	/** Each pixel value for an indexed color space has a single component
		describing an index value into a color lookup table. The number of components
		in the color lookup table depends on the base color space of the indexed
		color space. */
	kIndexedColorSpace			= 6,

	/** A gray color space with an alpha channel. */
	kAlphaGrayColorSpace		= (kGrayColorSpace | kColorSpaceHasAlpha),
	/** An RGB color space with an alpha channel. */
	kAlphaRGBColorSpace			= (kRGBColorSpace  | kColorSpaceHasAlpha),
	/** A CMYK color space with an alpha channel. */
	kAlphaCMYKColorSpace		= (kCMYKColorSpace | kColorSpaceHasAlpha),
	/** A LAB color space with an alpha channel. */
	kAlphaLabColorSpace			= (kLabColorSpace | kColorSpaceHasAlpha),
	/** A separation color space with an alpha channel. */
	kAlphaSeparationColorSpace	= (kSeparationColorSpace | kColorSpaceHasAlpha),
	/** An NChannel color space with an alpha channel. */
	kAlphaNChannelColorSpace	= (kNChannelColorSpace | kColorSpaceHasAlpha),
	/** An indexed color space with an alpha channel. */
	kAlphaIndexedColorSpace		= (kIndexedColorSpace | kColorSpaceHasAlpha),

	kInvalidColorSpace			= 0xFF
};

/** @ingroup Errors
	See \c #AIRasterSuite */
#define kRasterTypeNotSupportedErr			'RTYP'
/** @ingroup Errors
	Raster has already been specified. See \c #AIRasterSuite  */
#define kRasterSpecifiedErr					'RSPE'
/** @ingroup Errors
	Raster bits-per-pixel not supported. See \c #AIRasterSuite  */
#define kRasterBitsPerPixelsNotSupportedErr	'RBIT'
/** @ingroup Errors
	See \c #AIRasterSuite */
#define kRasterLinkFileNotFoundErr			'RFNF'
/** @ingroup Errors
	See \c #AIRasterSuite */
#define kRasterLinkPluginNotFoundErr		'RPNF'
/** @ingroup Errors
	See \c #AIRasterSuite */
#define kRasterScratchDiskFullErr			'RFUL'


/** Link states for \c #AIRasterLink::linkstate. Direct linking of images is deprecated
	(although still supported). Create linked objects using the \c #AIPlacedSuite. */
enum AIRasterLinkState {
	/** The image is linked; when saving native round-trip information,
		image data is not saved into the file. */
	kAIRasterLinked				= 0,
	/** The image is embedded; when saving native round-trip information,
		image data is saved with the file. */
	kAIRasterEmbedded			= 1
};

/** Data states for \c #AIRasterLink::datastate. Direct linking of images is deprecated
	(although still supported). Create linked objects using the \c #AIPlacedSuite. */
enum AIRasterDataState {
	/** No data is available for the image (for example, when a
		document is opened and the linked file cannot be found). */
	kAIRasterNoData				= 0,
	/** Data is available and is the same data that was read from
		the linked file (that is, it has not been modified since being read). */
	kAIRasterLinkData			= 1,
	/** Data is available and it has been modified since it was read from
		the file (for example, a Photoshop filter might have been run on the image). */
	kAIRasterEditedData			= 2
};

/** Flags for \c #AIRasterSuite::ResolveRasterLink(). Direct linking of images is deprecated
	(although still supported). Create linked objects using the \c #AIPlacedSuite. */
enum AIResolveRasterLinkFlags {
	/** Only update if the data is not embedded */
	kAIResolveCheckExternal		= (1<<0),
	/** Only update if the file has changed */
	kAIResolveCheckFile			= (1<<1),
	/** Report errors to user and show progress */
	kAIResolveVerbose			= (1<<2),
	/** Allow a replacement file to be selected in case of error */
	kAIResolveReplace			= (1<<3),
	/** Do automatic searching for a replacement */
	kAIResolveSearch			= (1<<4)
};

/** Flags for \c #AIRasterSuite::SplitChannels() */
 enum AISplitRasterFlags {
 	/** Decompose the original raster into an array of rasters specified in the standard
 	    color spaces (Gray, RGB, CMYK and spot Separation). If
 	    the original raster contains a partial set of CMYK process colors,
 		it is expanded to the full process colors. */
 	kAISplitRasterStandard			= 0x0000,
 	/** Decompose the CMYK process channels of the original raster
 		into individual process Separation color spaces. If
 	    the original raster contains a partial set of CMYK process colors,
 	    is \e not expanded to the full process channels. */
 	kAISplitRasterSeparateProcess	= 0x0001
};


/*******************************************************************************
 **
 **	Types
 **
 **/

/**	A slice, which defines a subset of a raster data to be copied or
	replaced, in \c #AITile::bounds. The slice of the source and
	destination are of equal dimensions, but differ in location.

	The \c top, \c bottom, \c left, and \c right values specify
	the rectangle containing the pixel data. As you iterate through a
	raster object accessing slices of pixels, these values change,
	controlling which section of the pixel map is being processed.

	The slice values for local pixel data are typically the same as
	the bounding rectangle of the tile (although you can also iterate
	through slices in a tile).

	The \c front and \c back, together with the \c #AITile::channelInterleave
	value, the control which of the pixel channels should be copied.
	The \c front value specifies the first channel to be affected, and the
	\c back value specifies the last channel + 1. See @ref ChannelInterleaving.
 */
typedef struct AISlice {
	ai::int32 top, left, bottom, right, front, back;
	void Init()
	{
		top = left = bottom = right = front = back = 0;
	}
} AISlice;


/** A tile, which describes local storage for copying image data to and from.
	Use with \c #AIRasterSuite::GetRasterTile() and \c #AIRasterSuite::SetRasterTile().
	*/
typedef struct AITile {
	/** A pointer to the memory containing the local copy of the pixels. Can be
		a generic block of memory or a platform-specific data structure.
		Must be allocated by the plug-in. */
	void		*data;
	/** The slice that defines the tile (a subset of the pixel map to
		be copied in one iteration), a rectangular area plus depth
		information that controls how interleaving occurs.
		See  @ref ChannelInterleaving.  */
	AISlice		bounds;
	/** The number of bytes in a row of pixel data. */
	ai::int32		rowBytes;
	/** The number of bytes used to specify a single pixel. For a raw RGB pixel,
		for example, it is 3. */
	ai::int32		colBytes;
	/** When 0, the tile receives all color data for a single pixel together.
		<br>When non-zero, the tile receives all data for a color together
		(in a planar form). In this case, the value is the number of bytes
		making up a single plane. For instance if the pixel map is
		80 by 80 pixels and the RGB data is in a planar form, the
		value is 6400. */
	ai::int32		planeBytes;
	/** Together with the slice information, this array specifies how to change
		the order of bytes making up a pixel when transferring between
		a raster art object and the tile data. See @ref ChannelInterleaving.*/
	ai::int16		channelInterleave[kMaxChannels];
	void			Init()
	{
		data = nullptr;
		bounds.Init();
		rowBytes = colBytes = planeBytes = 0;
		for (size_t i = 0; (i < kMaxChannels); ++i)
		{
			channelInterleave[i] = 0;
		}
	}
} AITile;


/** An RGB color table. */
typedef struct AIRGBColorRec	{
	ai::uint8	mustBeZero;		// MUST BE ZERO!!!!
	ai::uint8	red;
	ai::uint8	green;
	ai::uint8	blue;
} AIRGBColorRec;

/** An extended (16-bit) RGB color table. */
typedef struct AIExtendedRGBColorRec {
	ai::uint16	mustBeZero;		// MUST BE ZERO!!!!
	ai::uint16	red;
	ai::uint16	green;
	ai::uint16	blue;
} AIExtendedRGBColorRec;

/** A CMYK color table. */
typedef struct AICMYKColorRec	{
	ai::uint8	cyan;
	ai::uint8	magenta;
	ai::uint8	yellow;
	ai::uint8	black;
} AICMYKColorRec;


/** Configuration information for the raster image data associated with an art
	object of type \c #kRasterArt. Use with \c #AIRasterSuite::GetRasterInfo()
	and \c #AIRasterSuite::SetRasterInfo(). */
typedef struct AIRasterRecord	{
	/** Flags defining additional options for the image. A logical
		OR of \c #AIRasterFlags. */
	ai::uint16			flags;
	/** The width and height of the image data in pixels. The top left value of
		the bounds must be zero. The right value gives the width and the bottom
		value the height. (The coordinate system for a raster object is inverted
		on the vertical axis with respect to the Illustrator artboard coordinate
		system.) */
	AIRect			bounds;
	/** The number of bytes in a single row of pixel data. Not needed
		for \c #AIRasterSuite::SetRasterInfo(). 1-bit data is packed so
		that there are 8 pixels per byte.
		 \li If \c bitsPerPixel is 1 (for a black-and-white bitmap), the value is:
				<code>rasterRecord.bounds.right / 8 + 1</code>
		 \li For all other \c bitsPerPixel values, the value is:
				<code>rasterRecord.bounds.right * (rasterRecord.bitsPerPixel / 8)</code> */
	ai::int32			byteWidth;
	/** The color model of the pixel data, which can include an alpha channel,
		an \c #AIRasterColorSpace constant. */
	ai::int16			colorSpace;
	/** The number of bits used to define each pixel in the pixel map.
		Valid values depend on the color space:
			Gray: 1 (black and white) or 8 (gray)
			RGB: 24 (8 bits for each color)	or 48 (16 bits for each color)
			CMYK: 32 (8 bits for each color)
		*/
	ai::int16			bitsPerPixel;
	/** For an image that has been converted from one color space to another,
		the original color space, an \c #AIRasterColorSpace constant.
		<br>If the image has not been converted, the value is -1. */
	ai::int16			originalColorSpace;

	/** Default ctor */
	AIRasterRecord()
		:	flags(0), byteWidth(0), bitsPerPixel(0),
			colorSpace(kInvalidColorSpace), originalColorSpace(kInvalidColorSpace)			
	{
		bounds.left = bounds.top = bounds.right = bounds.bottom = 0;
	}
} AIRasterRecord;


/** Link information about an image. Direct linking of images is deprecated
	(although still supported). Create linked objects using the \c #AIPlacedSuite. */
struct AIRasterLink {
	/** The source file for the image data (the linked file). */
	ai::FilePath file;
	/** The link state, an \c #AIRasterLinkState constant. */
	ai::int32			linkstate;
	/** The data state, an \c #AIRasterDataState constant. */
	ai::int32			datastate;
};


/** Parameters for controlling the curve fitting used when outlining a raster.
	Keep parameters within valid ranges to avoid excessive performance impact.
	To reduce performance impact, try increasing smoothness and fidelity tolerance.
	See \c AIRasterSuite::ExtractOutline() */
typedef struct AIRasterOutlineParams {
	/** Valid range [0 to 5] inclusive. */
	ai::int32 noiseFilterDegree;
	/** Valid range [-1 to 1] inclusive. */
	double cornerAngleTolerance;
	/** Valid range [0 to 100] inclusive. */
	double smoothnessTolerance;
	/** Valid range greater than 0. */
	double fidelityTolerance;
} AIRasterOutlineParams;

/** When extracting an outline from a raster, the curves are enumerated to
	these callbacks. See \c AIRasterSuite::ExtractOutline() */
typedef struct AIRasterOutlineConsumer {
	/** Called at the beginning of the enumeration, use to initialize processing.
			@param self The current curve.
			@param knots The number of knots in the curve.
		*/
	AIAPI AIErr (*BeginComponent) ( void* self, ai::int32 knots );
	/** Called for each knot in each curve.
			@param self The current curve.
			@param in The in-point for the current knot.
			@param p The p-point for the current knot.
			@param out The out-point for the current knot.
		*/
	AIAPI AIErr (*PutKnot) ( void* self, AIRealPoint in, AIRealPoint p, AIRealPoint out);
	/** Called at the end of the enumeration, use to terminate processing.
			@param self The current curve.
		*/
	AIAPI AIErr (*EndComponent) ( void* self );
} AIRasterOutlineConsumer;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions with which to access and modify the
	data associated with an art object of type \c #kRasterArt.
	(Use \c #AIArtSuite, \c #AIMatchingArtSuite, or \c #AIArtSetSuite
	to create or access	the raster art object itself.)

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIRasterSuite and \c #kAIRasterVersion.

	The art associated with a raster object is defined by its pixel data
	and a matrix that positions the pixel data in the document. This information
	is kept in an \c #AIRasterRecord associated with the raster art object.
	This suite allows you to work with the raster data as whole, for instance by
	getting and setting its transformation matrix; or at a pixel level, using
	the tile functions.

	All values in the associated raster record are initialized to zero
	when you create a raster art object	with \c #AIArtSuite::NewArt().
	Retrieve the structure from the new art object using \c #GetRasterInfo(),
	and use \c #SetRasterInfo() to update the object.

	Set to the rectangle containing the pixel map using \c #SetRasterInfo().
	This is not the same rectangle as the artwork bounds, which Illustrator
	calculates and provides. The origin of a raster art object is in the top
	left corner; the coordinate system for a raster object is inverted on the
	vertical axis with respect to the Illustrator artboard coordinate system.

	All pixel data in a raster object uses a base resolution of	72 pixels
	per inch (PPI). You cannot directly specify the resolution; it is set
	from the bounds and the raster matrix. For a one inch square image
	at 72 PPI, the scale component of the raster matrix is set to 1.0 and
	the bounds would be 72 x 72. To create a one inch square image at 300 PPI,
	set the bounds to 300 x 300; the scale becomes 0.24 (72/300).

	Keep your local pixel data in a \e tile (\c #AITile). Use \c #GetRasterTile()
	to retrieve pixels from the pixel map and create a tile, and
	\c #SetRasterTile() to copy pixel information from the tile to the pixel map.

	When copying or replacing image data between a raster art object
	and a local data buffer (tile), it can be impractical to work with
	all the information at one time. You can define and work with a more
	practical subset of the data called a \e slice. Slices are defined in
	parameters of the functions that copy the data, \c #GetRasterTile and
	\c #SetRasterTile().

	A slice in the \c #AITile structure defines the tile (the area to be copied or replaced),
	and additional slices are defined for both the raster art object (\c artSlice) and
	for the local data buffer (\c workSlice). The one for the source controls
	how the transfer occurs:
		\li When copying from the raster art object to local data, \c #GetRasterTile()
			iterates over art slices.
		\li When copying from the local data to the raster art object,
			\c #SetRasterTile() iterates over work slices.

	@section ChannelInterleaving Channel Interleaving

	Together with the slice information (see \c #AISlice), the
	\c #AITile::channelInterleave array specifies how to change the order of
	bytes making up a pixel when transferring between a raster art object and
	the tile data buffer. This is useful when translating between similar
	but not identical color formats.

	The array contains a value for each channel, or color byte to be transferred.
	The array index of a value specifies the source, for bytes read in order from
	the internal bitmap. The array value maps the corresponding byte to a
	destination position.

	If there is no change in the data order, the array would be:
	\verbatim
myTile.channelInterleave[0] = 0;
myTile.channelInterleave[1] = 1;
myTile.channelInterleave[2] = 2;
myTile.channelInterleave[3] = 3;
	\endverbatim
	...
	An example of using the channel interleave is transferring from the internal
	RGB format to a Mac OS GWorld PixMap. The internal format uses 3 bytes in
	the order R G B to define a pixel. The GWorld uses 4 bytes in the order
	A R G B, where the A byte is the alpha channel information.

	When transferring between the raster art object and the GWorld,
	the channel interleave specifies the mapping between the two
	incompatible forms. To transfer from the raster object to the
	GWorld this mapping would be used:
	\verbatim
GWorldTile.channelInterleave[0] = 1; // Map 24-bit red value to 32-bit red value
GWorldTile.channelInterleave[1] = 2; // Map 24-bit green value to 32bit green value
GWorldTile.channelInterleave[2] = 3; // Map 24-bit blue value to 32-bit blue value
GWorldTile.channelInterleave[3] = 0; // Unused, handled by the slice definition
	\endverbatim

	Only three channels are mapped. The alpha channel of the GWorld receives
	no information. To transfer from the GWorld back to the raster object,
	this mapping would be used:
	\verbatim
GWorldTile.channelInterleave[0] = 0; // Alpha channel ignored, handled by slice definition
GWorldTile.channelInterleave[1] = 0; // Map 32-bit red value to 24-bit red value
GWorldTile.channelInterleave[2] = 1; // Map 32-bit green value to 24bit green value
GWorldTile.channelInterleave[3] = 2; // Map 32-bit blue value to 24-bit blue value
	\endverbatim

	Here the data in the alpha channel of the GWorld is not transferred
	back to the raster object.

	This example sets the art-object slice’s \c front and \c back values
	to limit the \c channelInterleave array:
	\verbatim
GWorldTile.channelInterleave[0] = 1; // Map 24-bit red value to 32-bit red value
GWorldTile.channelInterleave[1] = 2; // Map 24-bit green value to 32bit green value
GWorldTile.channelInterleave[2] = 3; // Map 24-bit blue value to 32-bit blue value
GWorldTile.channelInterleave[3] = 0; // Unused, handled by the slice definition
artSlice.front = 0;
artSlice.back = 3;
	\endverbatim

	Because \c artSlice.back is set to 3, only the color information for
	the first three channels is copied. When transferring data from the
	GWorld back to the raster art object, the GWorld’s slice controls the
	channel interleave. To skip the alpha channel, \c GWorldSlice.front is
	set to channel 1, causing channel 0 to be ignored.

	\verbatim
GWorldTile.channelInterleave[0] = 0; // Alpha channel is ignored, handled by the slice definition
GWorldTile.channelInterleave[1] = 0; // Map 32-bit red value to 24-bit red value
GWorldTile.channelInterleave[2] = 1; // Map 32-bit green value to 24bit green value
GWorldTile.channelInterleave[3] = 2; // Map 32-bit blue value to 24-bit blue value
GWorldSlice.front = 1;
GWorldSlice.back = 4;
	\endverbatim
 */
typedef struct AIRasterSuite {

	/** Retrieves the raster record associated with a raster art object.
			@param raster An art object of type \c #kRasterArt.
			@param info [out] A buffer in which to return the raster record.
		*/
	AIAPI AIErr (*GetRasterInfo) ( AIArtHandle raster, AIRasterRecord *info );

	/** Associates a raster record with a raster art object. After setting
		the record, use other functions such as \c #SetColorSpaceInfo() to
		specify the image data configuration.
			@param raster An art object of type \c #kRasterArt.
			@param info The raster record.
	 */
	AIAPI AIErr (*SetRasterInfo) ( AIArtHandle raster, AIRasterRecord *info );

	/** Retrieves the file information associated with a raster art object
		for a link. (Direct linking of images is deprecated, although still supported.
		Create linked objects using the \c #AIPlacedSuite.)
			@param raster An art object of type \c #kRasterArt.
			@param file [out] A buffer in which to return the file specification.
	 */
	AIAPI AIErr (*GetRasterFileSpecification) ( AIArtHandle raster, ai::FilePath& file );

	/** Not implemented. Returns \c #kNotImplementedErr. */
	AIAPI AIErr (*SetRasterFileSpecification) ( AIArtHandle raster, const ai::FilePath& );

	/** Retrieves the transformation matrix for a raster art object. This is the
		concatenation of all transforms applied to the image after it was created.
		It typically contains at least the initial translation and a scale;
		see \c #SetRasterMatrix().
			@param raster An art object of type \c #kRasterArt.
			@param matrix [out] A buffer in which to return the matrix.
		*/
	AIAPI AIErr (*GetRasterMatrix) ( AIArtHandle raster, AIRealMatrix *matrix );

	/** Sets the transformation matrix for a raster art object.
		All raster data is internally kept at 72 PPI and uses the object’s
		scale to set a resolution.
			@param raster An art object of type \c #kRasterArt.
			@param matrix The new matrix.
	 	*/
	AIAPI AIErr (*SetRasterMatrix) ( AIArtHandle raster, AIRealMatrix *matrix );

	/** Retrieves the raster image bounding box of a raster art object.
			@param raster An art object of type \c #kRasterArt.
			@param bbox [out] A buffer in which to return the bounding rectangle.
			@note The raster bounding box, as specified for \c #SetRasterInfo()
				or \c #SetRasterBoundingBox(), is not the same rectangle
				as the artwork bounds, which Illustrator calculates
				and provides for any art object. To do transformations,
				use \c #AIArtSuite::GetArtBounds().
		*/
	AIAPI AIErr (*GetRasterBoundingBox) ( AIArtHandle raster, AIRealRect *bbox );

	/** Sets the raster image bounding box of a raster art object.
			@param raster An art object of type \c #kRasterArt.
			@param bbox The bounding rectangle for the raster image.
				The top left value must be zero. The right value gives
				the width and the bottom value the height. (The coordinate
				system for a raster object is inverted on the vertical
				axis with respect to the Illustrator artboard coordinate
				system.)
			@see \c #GetRasterBoundingBox(), \c #AIRasterRecord::bounds
		*/
	AIAPI AIErr (*SetRasterBoundingBox) ( AIArtHandle raster, AIRealRect *bbox );

	/** Copies all or part of the pixel data for a raster art object into a
		local buffer (a tile). Use with \c #SetRasterTile() to filter raster data.
			@param raster An art object of type \c #kRasterArt.
			@param artSlice	The slice that defines a subset of the pixel map to be copied.
			@param workTile	The tile, which defines the data buffer in which
				pixel data is returned, and parameters for the transfer operation.
			@param workSlice The slice that defines a subset of the local data buffer
				to which to copy data. Typically, the bounds are the same as those
				of the work tile.
		*/
	AIAPI AIErr (*GetRasterTile) ( AIArtHandle raster, AISlice *artSlice, AITile *workTile, AISlice *workSlice );

	/** Copies pixel data in a local buffer (a tile) to all or part of
		a raster art object’s pixel map. This can be used, for instance,
		when reading a raster file format into a new raster art object.
			@param raster An art object of type \c #kRasterArt.
			@param artSlice	The slice that defines a subset of the pixel map to be replaced.
			@param workTile	The tile, which defines the data buffer in which
				pixel data is returned, and parameters for the transfer operation.
			@param workSlice The slice that defines a subset of the local data buffer
				from which to copy data. Typically, the bounds are the same as those
				of the work tile.
		*/
	AIAPI AIErr (*SetRasterTile) ( AIArtHandle raster, AISlice *artSlice, AITile *workTile, AISlice *workSlice );

	/** Retrieves the link information for a raster object that is a link.
		(Direct linking of images is deprecated, although still supported.
		Create linked objects using the \c #AIPlacedSuite.)
			@param raster An art object of type \c #kRasterArt.
			@param link [out] A buffer in which to return the link information.
		*/
	AIAPI AIErr (*GetRasterLink) ( AIArtHandle raster, AIRasterLink &link );

	/** Sets link information for a raster object.
		(Direct linking of images is deprecated, although still supported.
		Create linked objects using the \c #AIPlacedSuite.)
			@param raster An art object of type \c #kRasterArt.
			@param link The link information.
		 */
	AIAPI AIErr (*SetRasterLink) ( AIArtHandle raster, const AIRasterLink &link );

	/** Retrieves the link information for a raster art object, and reloads
		the raster data if needed. Marks the data as unmodified, but does not
		change the embedded state.

		Depending on the option flags, this can force reload, regardless of
		the embedded or modified state. If the flags do not specify that
		resolution should be forced, it is done only if the linked to data
		is more recent than the current copy.

		Attempting to resolve a link can fail for any of the following reasons:
			\li No link source is specified
			\li The link source is not found (\c #kRasterLinkFileNotFoundErr)
			\li A plug-in that can load the link source data is not found
				(\c #kRasterLinkPluginNotFoundErr)
			\li The link source data cannot be read
			\li Out of memory

		(Direct linking of images is deprecated, although still supported.
		Create linked objects using the \c #AIPlacedSuite.)
			@param raster An art object of type \c #kRasterArt.
			@param flags Option flags for how the operation is performed.
				A logical OR of \c #AIResolveRasterLinkFlags.
		*/
	AIAPI AIErr (*ResolveRasterLink) ( AIArtHandle raster, ai::int32 flags );

	/** Retrieves the file information associated with a raster art object
		that is a link, such as the time the file was created and last modified.
		This information is stored with the object from when the file
		was last read; compare to the current file information to check
		if the file has changed.<br>
		(Direct linking of images is deprecated, although still supported.
		Create linked objects using the \c #AIPlacedSuite.)
			@param raster An art object of type \c #kRasterArt.
			@param pSPFileInfo [out] A buffer in which to return the file information,
			@see \c #GetRasterFileInfoFromFile()
		*/
	AIAPI AIErr (*GetRasterFileInfoFromArt) ( AIArtHandle raster, SPPlatformFileInfo *pSPFileInfo );

	/** Retrieves the file information for the file associated with a raster art object
		that is a link, such as the time the file was created and last modified.
		Compare to the file information stored with the object to check
		if the file has changed since it was last read.<br>
		(Direct linking of images is deprecated, although still supported.
		Create linked objects using the \c #AIPlacedSuite.)
			@param raster An art object of type \c #kRasterArt.
			@param pSPFileInfo [out] A buffer in which to return the file information,
			@see \c #GetRasterFileInfoFromArt()
		*/
	AIAPI AIErr (*GetRasterFileInfoFromFile) ( AIArtHandle raster, SPPlatformFileInfo *pSPFileInfo );

	/** Retrieves the path for the file associated with a raster art object that is a link.
		<br> (Direct linking of images is deprecated, although still supported.
		Create linked objects using the \c #AIPlacedSuite.)
			@param raster An art object of type \c #kRasterArt.
			@param path [out] A buffer in which to return the platform-specific path.
		*/
	AIAPI AIErr (*GetRasterFilePathFromArt) ( AIArtHandle raster, ai::UnicodeString &path );

	/** Retrieves the number of levels in the MIP map that stores the raster data
		for a raster art object.
			@param raster An art object of type \c #kRasterArt.
			@param count [out] A buffer in which to return the number of levels
				(Currently always 6.)
		*/
	AIAPI AIErr (*CountLevels) ( AIArtHandle raster, ai::int32* count );

	/** Retrieves the bitmap format information for a level in the MIP map for
		a raster art object. Use with \c #CountLevels() to iterate through levels.
			@param raster An art object of type \c #kRasterArt.
			@param level The 0-based level index.
			@param info [out] A buffer in which to return the bitmap information.
			@note In the returned raster record:
				\li The \c flags are those you would get by querying the image
					as a whole.
				\li The \c bounds are those of the image at the given level of
					the MIP map. Each level is a power of two less than the
					previous one, with odd dimensions rounded up. For example,
					<code>levelWidth = (prevLevelWidth + 1) / 2 </code>
					<br>Do not rely on this algorithm, however. The only important
					property maintained is that any rectangle contained within the base
					image is contained within an image at a given level after
					scaling to that	level, even if its dimensions are rounded up.
				\li The \c byteWidth is ignored.
				\li The \c colorSpace and \c bitsPerPixel describe the format of
					the pixel data at the given level of the MIP map (currently
					always the same as that of the base image). The	subsampled
					levels of a bitmap's MIP map are bitmaps; random sampling is
					used to avoid aliasing.
		*/
	AIAPI AIErr (*GetLevelInfo) ( AIArtHandle raster, ai::int32 level, AIRasterRecord *info );

	/** Retrieves the tile information for a level in the MIP map for a
		raster art object. Use with \c #CountLevels() to iterate through levels.
			@param raster An art object of type \c #kRasterArt.
  			@param level The 0-based level index.
 			@param artSlice	The slice that defines a subset of the pixel map to be copied.
			@param workTile	The tile, which defines the data buffer in which
				pixel data is returned, and parameters for the transfer operation.
			@param workSlice The slice that defines a subset of the local data buffer
				to which to copy data. Typically, the bounds are the same as those
				of the work tile.
			@see \c #GetRasterTile()
		*/
	AIAPI AIErr (*GetLevelTile) ( AIArtHandle raster, ai::int32 level, AISlice *artSlice,
			AITile *workTile, AISlice *workSlice );

	/** Extracts an outline path from the image data, and enumerates the curves
		to the supplied callback functions.
			@param raster An art object of type \c #kRasterArt.
			@param params Parameters that control the curve fitting, or \c NULL
			to use defaults. Keep parameters within valid ranges to
			avoid excessive performance impact.
			@param consumer The developer-defined callbacks.
	*/
	AIAPI AIErr (*ExtractOutline) ( AIArtHandle raster, const AIRasterOutlineParams* params,
		AIRasterOutlineConsumer* consumer );

	/** Post-concatenate a transformation onto the matrix applied to a raster object.
			@param raster An art object of type \c #kRasterArt.
			@param concat The new transformation matrix information.
		*/
	AIAPI AIErr (*ConcatRasterMatrix) ( AIArtHandle raster, AIRealMatrix *concat );

	/** Attaches additional color space information to a raster art object,
		required for non-standard color spaces  (Separation, NChannel, and Indexed).
		 	@param raster An art object of type \c #kRasterArt.
			@param cs The color space information, with the same number of
				colors and channels as the color space specified in
				the \c #AIRasterRecord::colorSpace.
		*/
    AIAPI AIErr (*SetColorSpaceInfo) ( AIArtHandle raster, const ai::ColorSpace &cs);

	/** Retrieves the additional color space information from a raster art object,
		which is required for non-standard color spaces  (Separation, NChannel, and Indexed).
		 	@param raster An art object of type \c #kRasterArt.
			@param cs [out] A buffer in which to return the color space information
	   		@note If the raster is a colorized grayscale image, returns the actual color space
				used for the colorization. <br>
				If the color space info for non-standard color space has not been specified,
				returns an error code and an invalid color space.
		*/
    AIAPI AIErr (*GetColorSpaceInfo) ( AIArtHandle raster, ai::ColorSpace &cs);

	/** Enables or disables overprinting for a raster object.
			@param raster An art object of type \c #kRasterArt.
			@param enable True to enable overprint, false to disable it.
		*/
    AIAPI AIErr (*SetOverprint) ( AIArtHandle raster, AIBoolean enable);

	/** Retrieves the overprint status for a raster object.
			@param raster An art object of type \c #kRasterArt.
			@param enable [out] A buffer in which to return true if
				overprint is enabled, false if it is disabled.
		*/
    AIAPI AIErr (*GetOverprint) ( AIArtHandle raster, AIBoolean *status );

 	/** Reports whether a raster object is a colorized grayscale or bitmap image.
			@param raster An art object of type \c #kRasterArt.
 			@param isColorized [out] A buffer in which to return true if the raster
 				is a colorized grayscale or bitmap image.
 			@param isAdditive [out] Optional. A buffer in which to return true if the
				raster should be interpreted as additive.
 		*/
     AIAPI AIErr (*IsColorized) ( AIArtHandle raster, AIBoolean *isColorized, AIBoolean *isAdditive );

 	/** Clears the colorization on a colorized grayscale or bitmap image.
			@param raster An art object of type \c #kRasterArt.
 		*/
 	AIAPI AIErr (*ClearColorization) ( AIArtHandle raster );
 	/** Converts the colors in a raster object to a non-indexed color space.
  			@param raster [in, out] An art object of type \c #kRasterArt, which is modified in place.
 			@param dstCS The destination color space, which must not be indexed.
 		*/
     AIAPI AIErr (*ConvertColors) ( AIArtHandle *raster, const ai::ColorSpace &dstCS );
 	/** Inverts the colors in a raster object.
  			@param raster [in, out] An art object of type \c #kRasterArt, which is modified in place.
 		*/
     AIAPI AIErr (*InvertColors) ( AIArtHandle *raster );

 	/** Decomposes a raster object into an array of rasters specified in the standard
 	    color spaces (Gray, RGB, CMYK and spot Separation).
 	    The alpha channel from the original raster is duplicated among all the
 		output rasters.
			@param raster An art object of type \c #kRasterArt.
 			@param rasterArray [out] A buffer in which to return a pointer to a
 				block of memory containing the array of new raster art objects.
 				You must release the memory block when it is no longer
 				needed using \c #SPBasicSuite::FreeBlock().
 			@param numRasters [out] A buffer in which to return the number of objects
 				in the raster array, 0 if no rasters are constructed.
 			@param flag How to treat CMYK process channels, one of the constants
 				\c #kAISplitRasterStandard or \c #kAISplitRasterSeparateProcess.
			@see \c #InterleaveChannels()
 		*/
	 AIAPI AIErr (*SplitChannels) ( AIArtHandle raster, AIArtHandle **rasterArray, ai::int32 *numRasters, ai::uint32 flags );

 	/** Interleaves the color channels from an array of raster objects and
 		recombines them into a single raster.
 	    The source rasters and the destination raster must have the same width and height. 1-bit bitmap rasters are
 		not allowed in the input raster array. The alpha channel of the output raster is the average of all the alpha
 		channels in the input raster array (if there are any). It is ok that not all the input rasters have alpha
 		channels.
 			@param rasterArray A pointer to a block of memory containing the array of raster art objects
 				to be interleaved.
 			@param numRasters The number of objects in the raster array.
 			@param raster [out] A buffer in which to return the combined raster, an
 				art object of type \c #kRasterArt.
 			@param flag Not used. Pass \c NULL.
			@see \c #SplitChannels()
 		*/
	 AIAPI AIErr (*InterleaveChannels) ( AIArtHandle *rasterArray, ai::int32 numRasters, AIArtHandle *raster, ai::uint32 flags );

} AIRasterSuite;


#include "AIHeaderEnd.h"


#endif
