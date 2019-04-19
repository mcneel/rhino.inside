
#ifndef __AIColorSpace__
#define __AIColorSpace__

/*
 *        Name:	AIColorSpace.h
 *   $Revision: 1 $
 *      Author:	Simon Chen
 *        Date:
 *     Purpose:	Adobe Illustrator Color Space Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2007 Adobe Systems Incorporated.
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

#include "IAIColorSpace.hpp"
#include "AITypes.h"

#include "AIHeaderBegin.h"

/** @file AIColorSpace.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/
/** Color space suite name */
#define kAIColorSpaceSuite				"AI Color Space Suite"
/** Color space suite version */
#define kAIColorSpaceSuiteVersion		AIAPI_VERSION(7)
/** Color space suite version */
#define kAIColorSpaceVersion			kAIColorSpaceSuiteVersion

/*******************************************************************************
 **
 ** Types
 **
 **/

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	These function allow you to manipulate color-space objects and the
	application's global list of color spaces.
	@see ai::ColorSpace class, \c AIColor,h, \c #AIColorConversionSuite

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIColorSpaceSuite and \c #kAIColorSpaceVersion.

*/
typedef struct {
	/* Color Space List related APIs */

	/** Creates a new color-space list containing a given color space.
			@param csList [out] A buffer in which to return the new color-space list object.
			@param The color space object.
		*/
	AIAPI AIErr (*NewColorSpaceList) (ai::ColorSpaceList &csList, const ai::ColorSpace &cs);
	/** Adds a color space to a color-space list.
			@param csList The color-space list object.
			@param The color space object.
		*/
	AIAPI AIErr (*AddColorSpace) (ai::ColorSpaceList &csList, const ai::ColorSpace &cs);
	/** Reports the number of color space objects in a color-space list.
		Use with \c #GetNthColorSpace() to iterate through the list.
		(Note that this function returns an integer value, not an error code.)
			@param csList The color-space list object.
			@return The number of color space objects.
		*/
	AIAPI ai::int32 (*GetNumColorSpaces) (const ai::ColorSpaceList &csList);
	/**	Retrieves a color space object from a color-space list.
		Use with \c #GetNumColorSpaces() to iterate through the list.
			@param csList The color-space list object.
			@param n The 0-based position index of the color space object.
			@param cs [out] A buffer in which to return the color-space object.
				This is an invalid object if the index is out of range.
		*/
	AIAPI AIErr (*GetNthColorSpace) (const ai::ColorSpaceList &csList, ai::int32 n, ai::ColorSpace &cs);
	/** Duplicates a color space list.
	  	  @param out [out] A buffer in which to return the new color-space list object.
		  @param in The color-space list object to duplicate.
   		 */
	AIAPI AIErr (*CopyColorSpaceList) (ai::ColorSpaceList &out, const ai::ColorSpaceList &in);
	/**	Frees a color-space list object.
			@param csList The color-space list object. Upon return, this is an invalid object.
    	*/
	AIAPI AIErr (*DeleteColorSpaceList) (ai::ColorSpaceList& csList);

	/** Normalizes a color space list by flattening any NChannel color space,
		removing duplicates, compacting 4-process separation color spaces
		into a single CMYK-process color space, and sorting the color spaces.
		The order of the spot-separation color spaces in the original list is preserved.
			@param csList [in, out] The color-space list object.
			@param docColorModel The document color model, an \c #AIDocumentSuite::AIDocumentColorModelValue.
			@param convertGrayToFullProcess When false, if the color model is
				\c #kDocCMYKColor, a gray color space is converted to separation Black.
				Otherwise, a gray color space is converted to the full process
				in the document color space.
		*/
	AIAPI AIErr (*Normalize)(ai::ColorSpaceList& csList, ai::int16 docColorModel, AIBoolean convertGrayToFullProcess);

	/* Color Space related APIs */

	/** Creates a standard color space (Gray, RGB, CMYK, or LAB) with optional alpha channel.
			@param cs [out] A buffer in which to return the new color-space object.
			@param family The color family constant, Gray, RGB, CMYK, or LAB.
			@param hasAlpha True to create a color space with an alpha channel, false otherwise.
		*/
	AIAPI AIErr (*NewSimpleColorSpace) (ai::ColorSpace &cs, ai::ColorSpace::Family family, AIBoolean hasAlpha);
	/** Creates a process-separation CMYK color space.
			@param cs [out] A buffer in which to return the new color-space object.
			@param separationNum The process-separation plate of the base color space.
				The separation is never a spot color plate.
			@param hasAlpha True to create a color space with an alpha channel, false otherwise.
		*/
	AIAPI AIErr (*NewProcessSeparationColorSpace) (ai::ColorSpace &cs, ai::int32 separationNum, AIBoolean hasAlpha);
	/** Creates a color space based on a global custom color. This can be a spot color.
		or a global process color.
			@param cs [out] A buffer in which to return the new color-space object.
			@param customColor The custom color.
			@param hasAlpha True to create a color space with an alpha channel, false otherwise.
 	*/
	AIAPI AIErr (*NewGlobalColorSpace) (ai::ColorSpace &cs, const AICustomColorHandle customColor, AIBoolean hasAlpha);
	/** Creates an NChannel color space using a fully specified color space list.
		The list must conform to all requirements of an NChannel color space,
		including at most one process color space and no duplicate channels,
		with all RGB and Lab channels present and in order.
			@param cs [out] A buffer in which to return the new color-space object.
			@param csList The color-space list.
			@param hasAlpha True to create a color space with an alpha channel, false otherwise.
			@param promoteToProcess True to construct an equivalent process color space instead
                   of an NChannel color space, if possible. For example, if the input color
                   space list contains the full process components and has no spot components,
				   an equivalent process color space representation exists and is returned.
		*/
	AIAPI AIErr (*NewNChannelColorSpace) (ai::ColorSpace &cs, const ai::ColorSpaceList &csList, AIBoolean hasAlpha, AIBoolean promoteToProcess);
	/** Creates an indexed color space from a base color space, which can be any valid color space
		except indexed, including Separation and NChannel.
			@param cs [out] A buffer in which to return the new color-space object.
			@param baseCs The base color-space object.
			@param numComponents The number of components in the base color space, 3 or 4.
				A 4-component RGB table is in 0RGB order.
			@param numEntries The number of entries in the lookup table.
			@param lookup [out] A buffer in which to return the lookup table. The table size
				must be <code>numEntries * numComponents</code>.
	*/
	AIAPI AIErr (*NewIndexedColorSpace) (ai::ColorSpace &cs, const ai::ColorSpace &baseCs, ai::int32 numComponents,
		ai::int32 numEntries, const ASUInt8 *lookup);
	/** Creates a color space based on another color space, ignoring the alpha channel if present.
			@param cs [out] A buffer in which to return the new color-space object.
			@param baseCs The color-space objectto copy.
			@param hasAlpha True to create a color space with an alpha channel, false otherwise.
		*/
	AIAPI AIErr (*NewColorSpace) (ai::ColorSpace &cs, const ai::ColorSpace &baseCs, AIBoolean hasAlpha);
	/** Duplicates a color space.
			@param out [out] A buffer in which to return the new color-space object.
			@param in The color-space object to copy.
    */
	AIAPI AIErr (*CopyColorSpace) (ai::ColorSpace& out, const ai::ColorSpace& in);
	/** Frees a color-space object.
 			@param cs The color-space object. Upon return, this is an invalid object.
  	 	 */
	AIAPI AIErr (*DeleteColorSpace) (ai::ColorSpace& cs);
	/** Retrieves the family of a color space (Gray, RGB, CMYK, or LAB).
		(Note that this function returns a constant value, not an error code.)
			@param cs The color-space object.
			@return The color-space family constant.
		*/
	AIAPI ai::ColorSpace::Family (*GetFamily) (const ai::ColorSpace &cs);
	/**	Reports whether a color space has an alpha component.
		An Indexed color space has an alpha component if and only if
		its base color space has an alpha component.
		(Note that this function returns a boolean value, not an error code.)
			@param cs The color-space object.
			@return True if the color space has an alpha component.
	*/
	AIAPI AIBoolean (*HasAlpha) (const ai::ColorSpace &cs);
	/** Reports the number of components in a color space, including the alpha channel if it exists.
		An Indexed color space is considered to have only one component in addition to the
		possible alpha component (\e not the number of color components in the base color space).
		(Note that this function returns an integer value, not an error code.)
			@param cs The color-space object.
			@return The number of components.
			@see \c #GetNumColorComponents()
	*/
	AIAPI ai::int32 (*GetNumComponents) (const ai::ColorSpace &cs);
	/** Reports the number of color components in a color space. Does not count the alpha channel, if any.
		For the Indexed color space, this is the number of color components in its base color space.
		(Note that this function returns an integer value, not an error code.)
			@param cs The color-space object.
			@return The number of color components.
			@see \c #GetNumComponents()
		*/
	AIAPI ai::int32 (*GetNumColorComponents) (const ai::ColorSpace &cs);
	/** Reports the number of spot components in a color space. Does not count the alpha channel, if any.
		This is 0 for CMYK, RGB, Gray, Lab, and for "process" separations.
		It is  1 for "spot" separations. For the Indexed color space, this is the
		number of spot color components in its base color space.
		(Note that this function returns an integer value, not an error code.)
			@param cs The color-space object.
			@return The number of spot components.
		*/
	AIAPI ai::int32 (*GetNumSpotComponents) (const ai::ColorSpace &cs);
	/** Returns the base color space for an Indexed color space,
		or the alternate color space for a Separation/NChannel color space.
		For a standard color space, returns the color space itself.
			@param cs The color-space object.
			@param baseCs [out] A buffer in which to return the base color-space object.
		*/
	AIAPI AIErr (*GetBaseColorSpace) (const ai::ColorSpace &cs, ai::ColorSpace &baseCs);
	/** Reports the number of components in an indexed color table.
		(Note that this function returns an integer value, not an error code.)
			@param cs The color-space object.
			@return The number of components, or 0 for non-indexed color spaces.
		*/
	AIAPI ai::int32 (*GetIndexedNumComponents) (const ai::ColorSpace &cs);
	/** Reports the number of color table entries in an indexed color table.
		(Note that this function returns an integer value, not an error code.)
			@param cs The color-space object.
			@return The number of entries, or 0 for non-indexed color spaces.
	*/
	AIAPI ai::int32 (*GetIndexedNumEntries) (const ai::ColorSpace &cs);
	/** Retrieves the color table of an indexed color space.
		(Note that this function returns an numeric value, not an error code.)
			@param cs The color-space object.
			@return The number of entries, or \c NULL for non-indexed color spaces.
		*/
	AIAPI const ASUInt8* (*GetIndexedTable) (const ai::ColorSpace &cs);
	/** Retrieves the alternate color values in the alternate color space for a separation color space.
		(Note that this function returns an numeric array value, not an error code.)
			@param cs The color-space object.
			@return A pointer to an array of color values, or \c NULL for non-separation color spaces.
		*/
	AIAPI const AIFloat* (*GetSeparationAltColors) (const ai::ColorSpace &cs);
	/** Retrieves the fully-specified color-space list that contains a non-indexed color space.
			@param cs The color-space object.
			@param csList [out] A buffer in which to return the color-space list object.
				This is an invalid object if the color space is indexed.
	*/
	AIAPI AIErr (*GetColorSpaceList) (const ai::ColorSpace &cs, ai::ColorSpaceList &csList);
	/** Retrieves the colorant name of a component of a color space. Use with
		\c #GetNumColorComponents() to iterate through components.
			@param cs The color-space object.
			@param n The 0-based position index of the color component.
			@param name	[out] A buffer in which to return the name string, or the empty string
				if the index is out of range. The names are:
					\li "Gray" for Gray colorspaces
					\li "Red","Green","Blue" for RGB colorspaces
					\li "Cyan","Magenta","Yellow","Black" for CMYK colorspaces
					\li  Empty for LAB colorspaces
		*/
	AIAPI AIErr (*GetNthColorant) (const ai::ColorSpace &cs, ai::int32 n, ai::UnicodeString& name);
	/** Reports whether a color space has all process components.
		(Note that this function returns an boolean value, not an error code.)
			@param cs The color-space object.
			@return True if the CMYK, RGB, Gray, or Lab color space has all process components.
	 				False if the color space has no process components, or the
	 				color space is a spot or process separation.
		*/
	AIAPI AIBoolean (*HasFullSetOfProcessComponents) (const ai::ColorSpace &cs);
	/** Reports whether two color spaces are identical.
		(Note that this function returns an boolean value, not an error code.)
			@param cs1 The first color-space object.
			@param cs2 The second color-space object.
			@return True if the objects are identical, false otherwise.
	*/
	AIAPI AIBoolean (*Equal) (const ai::ColorSpace &cs1, const ai::ColorSpace &cs2);
} AIColorSpaceSuite;


#include "AIHeaderEnd.h"



#endif // __AIColorSpace__
