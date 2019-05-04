#ifndef __OverrideColorConversion__
#define __OverrideColorConversion__

/*
 *        Name:	AIOverrideColorConversion.h
 *   $Revision: 13 $
 *     Purpose:	Adobe Illustrator Suite to replace internal color
 *              conversion functionality.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2002-2007 Adobe Systems Incorporated.
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
#include "AITypes.h"          /* Include Adobe Standard Types */
#endif

#include "AIHeaderBegin.h"

/** @file AIOverrideColorConversion.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIOverrideColorConversionSuite			"Override AI Color Conversion Suite"
#define kAIOverrideColorConversionSuiteVersion7	AIAPI_VERSION(7)
#define kAIOverrideColorConversionSuiteVersion	kAIOverrideColorConversionSuiteVersion7
#define kAIOverrideColorConversionVersion		kAIOverrideColorConversionSuiteVersion


// JM - must synch with those in picasso.h
/** Working colorspace types */
enum AIWorkingColorSpace {
	/** Grayscale */
	kGrayWS		= 0,
	/** RGB */
	kRGBWS		= 1,
	/** CMYK */
	kCMYKWS		= 2
};


/** RGB image formats */
enum AIRGBPixelFormat {
	/** With alpha channel */
	kARGB               = 0,
	/** Without alpha channel */
	kRGB                = 1
};


/* CMYK separations/channels */

#ifndef kCyan
#define kCyan                   0x00000001
#endif

#ifndef kMagenta
#define kMagenta                0x00000002
#endif

#ifndef kYellow
#define kYellow                 0x00000004
#endif

#ifndef kBlack
#define kBlack                  0x00000008
#endif

#ifndef kCMYK
#define kCMYK                   0x0000000f
#endif

/** Rendering intents */
enum AIRenderingIntent {
	kICPerceptual				= 0,
	kICRelativeColorimetric	    = 1,
	kICSaturation				= 2,
	kICAbsoluteColorimetric   	= 3
};

/** Policies on what to do with a document's color profile when it is opened */
enum AIFileOpenColorProfilePolicy {
	/** Convert document to working space */
	kConvert	= 0,
	/** Remove profile from doc */
	kUntag		= 1,
	/** Preserve the documents profile */
	kPreserve	= 2,
	/** User decided to cancel the open */
	kCancel		= 3
};

/** Policies on what to do with a document's color profile when it is saved */
enum AIFileSaveColorProfilePolicy {
	/** Do not save a profile */
	kNoProfile	= 0,
	/** Save with the working space profile */
	kWSProfile	= 1,
	/** Save with the document profile */
	kDocProfile	= 2
};

/** Color conversion policies inferred from the color settings dialog,
	on whether to do color conversions within the same
	colorspace family (such as RGB to RGB, or CMYK to CMYK) */
typedef enum ColorConvPolicy
{
	/** Do conversion to maintain color appearance */
	kPreserveAppearance,
	/** Do not convert colors, instead maintain numerical values */
	kPreserveNumbers
} ColorConvPolicy;

/** Constants identifying predefined color transforms (when retrieving
	an internal transform) or transform types (when creating a new
	internal transform, or applying any transform).
<br>See<br>
	\c #AIOverrideColorConversionSuite::GetInternalTransform() <br>
	\c #AIOverrideColorConversionSuite::CreateInternalTransform()  <br>
	\c #AIOverrideColorConversionSuite::CreateInternalTransform_16Bit()  <br>
	\c #AIOverrideColorConversionSuite::ApplyXformSample() <br>
	\c #AIOverrideColorConversionSuite::ApplyXformImage()
	*/
typedef enum InternalColorTransformType
{
	kRGB2RGB=0,
	kRGB2CMYK,
	kCMYK2CMYK,
	kCMYK2RGB,
	kRGB2sRGB,
	kCMYK2sRGB,
	kLAB2RGB,

	// The types below are new for AI 11
	// New for JPEG 2000.
	ksGray2RGB,
	ksYCC8_2RGB,
	kesRGB2RGB,
	kROMMRGB2RGB,
	kesYCC8_2RGB,

	// Same as above with 8 < BPC <= 16. Only used by Jpeg2000.
	kCIELab_16Bit2RGB, //Also for CIELab 8 bit.
	ksGray_16Bit2RGB,
	ksYCC8_16Bit2RGB,
	kesRGB_16Bit2RGB,
	kROMMRGB_16Bit2RGB,
	kesYCC8_16Bit2RGB,

	kNumTransforms
} InternalColorTransformType;

/** Parameters for color conversion type \c #kCIELab_16Bit2RGB */
typedef struct {
	/** Native byte-order versions of the three JPX channel Range and Offset parameters from the EP field
		see JPEG2000 spec, Annex M, sec M.11.7.4 */
	ASUInt32 Range1;
	ASUInt32 Offset1;
	ASUInt32 Range2;
	ASUInt32 Offset2;
	ASUInt32 Range3;
	ASUInt32 Offset3;
	/** Native byte-order version of IL parameter from EP field. Ignored for CIEJab. */
	ASUInt32 Illuminant;
} JPXLabParams;

/**	Ranges for color values */
typedef struct {
	/** Usual value -128 */
	AIReal		min;
	/** Usual value +127 */
	AIReal		max;
} AIRange;


/**	Floating point CIE XYZ color value */
typedef struct  {
	AIReal		X;
	AIReal		Y;
	AIReal		Z;
} AIXYZColor;


/**	Calibration information for constructing a grayscale profile. */
typedef struct {
	AIXYZColor		whitePoint;
	AIXYZColor		blackPoint;
	AIReal		gamma;
} AIGrayCal;

/**	Calibration information for constructing an RGB profile. */
typedef struct {
	AIXYZColor		whitePoint;
	AIXYZColor		blackPoint;
	AIXYZColor		red;
	AIXYZColor		green;
	AIXYZColor		blue;
	AIReal		redGamma;
	AIReal		greenGamma;
	AIReal		blueGamma;
} AIRGBCal;

/** Tone curve definition */
typedef struct  {
	ASUInt32		bytesPerValue;
	ASUInt32		count;
	void			*data;
} AIToneCurve;

/**	Calibration information for constructing a CMYK profile. */
typedef struct {
	AIXYZColor		whitePoint;
	AIXYZColor		blackPoint;
	AIXYZColor		w;
	AIXYZColor		c;
	AIXYZColor		m;
	AIXYZColor		y;
	AIXYZColor		k;
	AIXYZColor		cm;
	AIXYZColor		cy;
	AIXYZColor		ck;
	AIXYZColor		my;
	AIXYZColor		mk;
	AIXYZColor		yk;
	AIXYZColor		cmy;
	AIXYZColor		cmk;
	AIXYZColor		cyk;
	AIXYZColor		myk;
	AIXYZColor		cmyk;

	AIToneCurve	cTRC;
	AIToneCurve	mTRC;
	AIToneCurve	yTRC;
	AIToneCurve	kTRC;

	AIReal		opticalGamma;

} AICMYKCal;

/*******************************************************************************
 **
 **	Suite
 **
 **
 */

/** @ingroup Suites
	This suite provides functions that allow you to manage color profiles and
	perform color conversions between profiles. Typically, you will use
	\c #CreateInternalTransform() for a source and destination colorspace.
	After calling \c #AIColorConversionSuite functions with those colorspaces,
	use \c #FreeAllInternalTransforms() to free the transform memory.

	For example, to do a calibrated CMYK to RGB conversion of a single sample:
	\verbatim
	CreateInternalTransform(CMYK2RGB, cmykProfile, rgbProfile)
	AIColorConversionSuite::ConvertSampleColor(kAICMYKColorSpace, cmykSample, kAIRGBColorSpace, rgbSample)
	FreeAllInternalTransforms()
	\endverbatim

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIOverrideColorConversionSuite and \c #kAIOverrideColorConversionVersion.
 */
typedef struct {

	/** Converts RGB image samples into CMYK to determine if any of the samples
		were out of gamut.
			@param srcBuf A	pointer to the sample data, which must have 8 bits per
				component.
			@param numSamples The number of samples in the source buffer.
			@param rgbFormat The RGB format used in the samples, an
				\c #AIRGBPixelFormat value.
			@param inGamut [out] A buffer in which to return true if all of
				the samples are in gamut.
		*/
	AIAPI AIErr ( *GamutRGBToCMYKImage )( void *srcBuf, const ASUInt32 numSamples,
 										const ASUInt32 rgbFormat, ASBoolean *inGamut );

	/** Creates a transformation from one profile to another, using the render intent
		set in the Color Settings dialog.
			@param srcProfile The source color profile.
			@param destProfile The destination profile.
			@param xform [out] A buffer in which to return the transformation. Free
				the memory with \c #FreeXform() when it is no longer needed.
			@see \c #CreateProfileFromTag()
		 */
	AIAPI AIErr ( *CreateXform )(const AIColorProfile srcProfile, const AIColorProfile destProfile, ai::uintptr *xform );

	/** Frees memory for a transformation when it is no longer needed.
		(Note that this function does not return an error code.)
			@param xform The transformation, as created with \c #CreateXform().
		*/
	AIAPI void  ( *FreeXform )( const ai::uintptr xform );

	/** Applies a transformation to a single color value.
			@param xform The transformation, as created with \c #CreateXform().
			@param inColor A pointer to the color value.
			@param outColor [out] A buffer in which to return the transformed color value.
			@param convType The type of the specified transformation.
			@param isLAB Not used.
		*/
	AIAPI AIErr ( *ApplyXformSample )( const ai::uintptr xform, ASFixed *inColor, ASFixed *outColor,
			const InternalColorTransformType convType, ASBoolean isLAB );

	/** Applies a transformation to a buffer of image data.
			@param xform The transformation, as created with \c #CreateXform().
			@param inBuffer A pointer to the input image data.
			@param outBuffer [out] A buffer in which to return the transformed color data.
			@param numPixels The number of pixels in the input data. The output buffer
				must be big enough to hold this many pixels in the new format.
			@param convType The type of the specified transformation..
			@param isLAB Not used.
			@param format The output data format to use when converting to RGB,
				an \c #AIRGBPixelFormat value.
		*/
	AIAPI AIErr ( *ApplyXformImage )( const ai::uintptr xform, void *inBuffer, void *outBuffer, const ASUInt32 numPixels,
			const InternalColorTransformType convType, ASBoolean isLAB , ASInt16 format);

	/** Converts an ICC tag into a color profile. When you create a profile this way, you must
		free it with \c #FreeProfile() when you no longer need it.
			@param buffer The buffer containing the raw ICC tag data.
			@param size The number of bytes in the input buffer.
			@param profile [out] A buffer in which to return the color profile object.
		*/
	AIAPI AIErr ( *CreateProfileFromTag )( void *buffer, const ASUInt32 size, AIColorProfile *profile );

	/** Creates a current working color profile. When you create a profile this way, you must
		free it with \c #FreeProfile() when you no longer need it.
			@param whichProfile  The colorspace for the profile, an \c #AIWorkingColorSpace value.
			@param profile [out] A buffer in which to return the color profile.
		*/
	AIAPI AIErr ( *GetWSProfile )( const ASUInt32 whichProfile, AIColorProfile *profile );

	/** Frees the memory associated with a color profile that is no longer needed.
		You can do this after creating the transform with \c #CreateXform().
		(Note that this function does not return an error code.)
			@param profile The profile. Upon return, the reference is no longer valid.
		*/
	AIAPI void  ( *FreeProfile )( AIColorProfile profile );

	/** Retrieves the current color management policy for how to treat
		color profiles when opening documents. Also gets a valid profile
		for the current document, according to that policy.
		Queries user if needed to determine what profile should be used.
		(Note that this function returns a constant value, not an error code.)
			@param profile [in, out] The embedded color profile for the current document,
				or \c NULL if the document has no embedded profile or has multiple profiles.
				If \c NULL, and if the policy indicates that a
				profile should be assigned, returns that profile assigned by current policy,
				or by user interaction. Can be \c NULL if color management is turned off,
				or if the user discards the embedded profile.
			@param colorModel The color model of the current document, an
				\c #AIDocumentColorModelValue.
			@param isLink When true, get the policy for placing file formats that
				contain profiles, instead of the open policy.
	 		@param linkHasMultipleProfiles When true, the linked file has more
				than one profile for a given colorspace. If the linked file contains
				both RGB and CMYK, call the function once for each colorspace,
				as the policies can be different.
			@return A #AIFileOpenColorProfilePolicy value.
		*/
	AIAPI ASUInt32  ( *GetOpenPolicy )(AIColorProfile *profile, ASUInt32 colorModel, ASBoolean isLink,
		ASBoolean linkHasMultipleProfiles);

	/** Retrieves the current color management policy for how to treat
		color profiles when saving documents; that is, which profile, if any,
		should be saved with the document. Also reports what profile would be embedded,
		if any, for the current document, according to that policy.
		(Note that this function does not return an error code.)
			@param whichSpace The working colorspace corresponding to the document color model,
				an \c #AIWorkingColorSpace value.
			@param policy [out] A buffer in which to return the policy, an
				\c #AIFileSaveColorProfilePolicy value.
			@param defaultState [out] A buffer in which to return the default state
				of the "Embed profile?" checkbox
			@param profName [out] A buffer in which to return the name of the profile to
				be embedded, if any.
		 */
	AIAPI void  ( *GetSavePolicy )( const ASUInt32 whichSpace, ASUInt32 *policy, ASUInt32 *defaultState, ai::UnicodeString& profName);

	/** Retrieves the tag data for a color profile.
			@param profile The color profile.
			@param size [out] A buffer in which to return the number of bytes returned
				in the data buffer, or, if \c data is \c NULL, the size of the buffer needed.
			@param data [in, out] \c NULL to retrieve the size of buffer needed, or a buffer in
				which to return the tag data.
		*/
	AIAPI AIErr ( *GetProfileData ) (const AIColorProfile profile, ASUInt32 *size, void *data );

	/** Retrieves the description name of a color profile.
			@param profile The color profile.
			@param profileName [out] A buffer in which to return the descriptive name string.
		*/
	AIAPI AIErr ( *GetProfileName) (const AIColorProfile profile, ai::UnicodeString& profileName ) ;

	/** Creates and caches transforms to be used for all internal color conversions and those
		performed with the \c #AIColorConversionSuite.

		\li Supply the source and destination profiles
			for these basic color transform types:
		<br>\c #kRGB2RGB
		<br>\c #kRGB2CMYK
        <br>\c #kCMYK2CMYK
        <br>\c #kCMYK2RGB

		\li For other 8-bit transforms to RGB, if the source profile is \c NULL,
			the profile of the top document is used, or if that is \c NULL, the
			corresponding working space. The destination profile is ignored and
			is set internally to \c sRGB.
		\li For a transform from LAB to RGB, the source RGB data is interpreted as LAB.
			The source profile is ignored and is set internally to \c LAB. If the
			destination profile is \c NULL, the profile of the
			top document is used, or if that is \c NULL, the RGB working space.

		For example, to convert a sample in the top document from RGB to sRGB:
		\verbatim
	CreateInternalTransform(RGB2sRGB, NULL, NULL)
	ConvertSampleColor(kAIRGBColorSpace, rgbSample, kAIRGBColorSpace, sRGBSample)
	FreeAllInternalTransforms()
		\endverbatim

		To convert from LAB to RGB:
		\verbatim
	CreateInternalTransform(LAB2RGB, NULL, NULL)
	ConvertSampleColor(kAIRGBColorSpace, labSample, kAIRGBColorSpace, rgbSample)
	FreeAllInternalTransforms()
		\endverbatim

			@param whichOne The predefined 8-bit transform type.
			@param srcProfile The source color profile.
			@param destProfile The destination profile.
			@see \c #CreateInternalTransform_16Bit()
		*/
	AIAPI AIErr ( *CreateInternalTransform) (const InternalColorTransformType whichOne, AIColorProfile scrProfile, AIColorProfile destProfile);

	/** Frees memory for all cached transforms. Subsequent color conversion is done
		using the default transformation.
		(Note that this function does not return an error code.)
		*/
	AIAPI void  ( *FreeAllInternalTransforms) (void);

	/** Reports whether two profiles are the same.
		(Note that this function does not return an error code.)
			@param srcProfile The first profile.
			@param destProfile The second profile.
			@param match [out] A buffer in which to return true (non-zero) if the two profiles are the same,
				false (0) if different or if either is not a valid profile.  */
	AIAPI void  ( *ProfsEqual) (const AIColorProfile srcProfile, const AIColorProfile destProfile, ASUInt32 *match);

	/** Retrieves a transform created by \c #CreateInternalTransform(),
		to use with \c #ApplyXformSample() or \c #ApplyXformImage(). For example:
		\verbatim
	CreateInternalTranform(LAB2RGB, NULL, NULL)
	GetInternalTransform(LAB2RGB, &xform);
	ApplyXformSample(xform, incolor, outcolor, KLAB2RGB. false);
	FreeAllInternalTransforms()
		\endverbatim
			@note For LAB data, the L value must be scaled from [0..100] to [0..255],
				and the A and B values must be scaled from [-128..127] to [0..255].

			@param whichOne	The predefined transform type.
			@param xform [out] A buffer in which to return the transform.
	*/
	AIAPI	void  ( *GetInternalTransform)(const InternalColorTransformType whichOne,  ai::uintptr *xform);

	/** Turns on Black Point Compensation for all subsequent color transform operations.
		This should be used for ADM drawing operations.
		(Note that this function does not return an error code.)
		*/
	AIAPI void  ( *BPCOn ) (void) ;

	/** Restores the previous Black Point Compensation setting, after using \c #BPCOn().
		(Note that this function does not return an error code.)
		*/
	AIAPI void  ( *RestoreBPC )(void);

	// New in Illustrator 11.0

	/** Constructs a color profile from grayscale calibration information.
			@param grayCal A pointer to the calibration information.
			@param profile [out] A buffer in which to return the color profile.
		*/
	AIAPI AIErr ( *MakeProfileFromCalGray)(AIGrayCal *grayCal, AIColorProfile *profile);
	/** Constructs a color profile from RGB calibration information.
			@param rgbCal A pointer to the calibration information.
			@param profile [out] A buffer in which to return the color profile.
		*/
	AIAPI AIErr ( *MakeProfileFromCalRGB)(AIRGBCal *rgbCal, AIColorProfile *profile);

	/** Constructs a color profile from CMYK calibration information.
			@param cmykCal A pointer to the calibration information.
			@param profile [out] A buffer in which to return the color profile.
		*/
	AIAPI AIErr ( *MakeProfileFromCalCMYK)(AICMYKCal *cmykCal, AIColorProfile *profile);

	/**	Creates and caches transforms to be used for all internal color conversions and those
		performed with the \c #AIColorConversionSuite. Use when the source has more than 8 bits
		per channel, to a maximum of 16 bits per channel. If source has more than 16 bits, you must
		truncate the data to 16 bits, then use this function.

			@param whichOne The predefined 16-bit transform type.
			@param srcProfile The source 16-bit color profile.
				For \c kCIELab_16Bit2RGB color conversion only,	can be an 8-bit or 16-bit profile.
			@param dstProfile The destination profile.
			@param bitDepth An array the size of the number of channels, with the bit depth of each channel.
			@param jpxLabParams For \c kCIELab_16Bit2RGB color conversion only, additional parameters
				required for LAB conversion.  \c NULL for other transform types.
			@see \c #CreateInternalTransform()
		*/
	AIAPI AIErr  ( *CreateInternalTransform_16Bit)(const InternalColorTransformType whichOne, AIColorProfile srcProfile, AIColorProfile dstProfile,
			ASUInt8* bitDepth, JPXLabParams* jpxLabParams);

	/** Retrieves the color conversion policies and the AI6 mode from the Color Settings dialog.
		(Note that this function does not return an error code.)
			@param A16Mode [out] A buffer in which to return the A16 mode
			@param rgbPolicy [out] A buffer in which to return the RGB color conversion policy.
			@param cmykPolicy [out] A buffer in which to return the	CMYK color conversion policy.
		*/
	AIAPI void   ( *GetColorSettingsPolicies)(ASBoolean *AI6Mode, ColorConvPolicy *rgbPolicy, ColorConvPolicy *cmykPolicy);

	/** Retrieves the render intent from the Color Settings dialog
		(Note that this function returns a constant value, not an error code.)
		@return The rendering-intent constant.
		*/
	AIAPI AIRenderingIntent ( *GetColorSettingsRenderIntent)(void);


	// New in Illustrator 16.0
	/** Reports whether Black Point Compensation is currently enabled.
		(Note that this function returns a Boolean value, not an error code.)
		@return True if BPC is currently enabled, false otherwise.
		@see \c #BPCOn()
	*/
	AIAPI AIBoolean   ( *IsBPCOn)();

} AIOverrideColorConversionSuite;


#include "AIHeaderEnd.h"


#endif
