/*
 *        Name:	IAIColorSpace.hpp
 *   $Revision: 1 $
 *      Author:	Simon Chen
 *        Date:
 *     Purpose:	C++ interface class for the ai::ColorSpace and ai::ColorSpaceList objects.
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


#ifndef _IAICOLORSPACE_H_
#define _IAICOLORSPACE_H_

#include "AITypes.h"
#include "AIColor.h"
#include "IAIUnicodeString.h"

/** @file IAIColorSpace.hpp */

/** @ingroup Errors 
	An out-of-range index for a color space was used.
	See \c #ai::ColorSpace.*/
#define kColorSpaceBadIndex				'CS!I'

/** @ingroup Errors  
	See \c #ai::ColorSpace. */
#define kColorSpaceInvalid				'!VAL'

class CAIColorSpaceImpl;
class CAIColorSpaceListImpl;

namespace ai {

class ColorSpace;
class ColorSpaceList;

/** This class represents an Illustrator color space. */
class ColorSpace {
	friend class ColorSpaceList;

public:
	enum Family {
		kAIColorSpaceFamilyUnknown,
		kAIColorSpaceFamilyGray,
		kAIColorSpaceFamilyRGB,
		kAIColorSpaceFamilyLab,
		kAIColorSpaceFamilyCMYK,
		kAIColorSpaceFamilySeparation,
		kAIColorSpaceFamilyNChannel,
		kAIColorSpaceFamilyIndexed
	};

public:
	//----------------------------------------------------------------------
	/** @name Constructors & Destructors */
	//----------------------------------------------------------------------
	//@{
	/** Constructs an empty, invalid color space object. Throws no exceptions.  */
	explicit ColorSpace (void) AINOTHROW;
	/** Constructs a standard color space object.
			@param family The color space family (Gray, RGB, CMYK, or LAB).
			@param hasAlpha True if alpha channel is present.
			@return The new color space object.
		*/
	explicit ColorSpace (ai::ColorSpace::Family family, bool hasAlpha = false);
	/** Constructs a process separation color space.
			@param separationNum Process-separation plate number of the base CMYK color space.
				<br>0: Cyan
				<br>1: Magenta
				<br>2: Yellow
				<br>3: Black
			@param hasAlpha True if alpha channel is present.
			@return The new color space object.
		*/
	explicit ColorSpace (int separationNum, bool hasAlpha = false);
	/** Constructs a color space based on the global custom color.
			@param customColor The global custom color object.
			@param hasAlpha True if alpha channel is present.
			@return The new global process color space object, or, if the custom color is a spot color,
	    		a spot separation color space object.
		*/
	explicit ColorSpace (const AICustomColorHandle customColor, bool hasAlpha = false);
	/** Constructs an n-channel color space using a fully specified color space list.
			@param csList The list of component color spaces, which must conform to all
				requirements of an n-channel color space, including at most one process
				color space and no duplicate channels, with all RGB or Lab channels present
				and in order.
			@param hasAlpha True if alpha channel is present.
			@param promoteToProcess True to construct an equivalent process color space instead 
                   of a NChannel color space if it is possible. For example, if the input color
                   space list contains the full process components and has no spot components, 
				   an equivalent process color space representation exists and is returned.
			@return The new color space object.
		*/
	explicit ColorSpace (const ai::ColorSpaceList &csList, bool hasAlpha = false, bool promoteToProcess = false);
	/** Constructs an indexed color space.
			@param baseCs The base color space of the indexed color space.
			@param numComponents The number of components in the color lookup table.
				For an RGB indexed table, can be 3 or 4.
			@param numEntries number of entries in the color lookup table.
			@param lookup The color lookup table, \c numComponents rows by
				\c numEntries columns.  A 4-component RGB table must
				be in 0RGB byte order.
			@return The new color space object.
		*/
	explicit ColorSpace (const ai::ColorSpace &baseCs, int numComponents, int numEntries, const ASUInt8 *lookup);
	/** Constructs a color space based on another color space. The alpha channel, if present,
		is ignored in constructing the new color space.
			@param baseCs The input color space.
			@param hasAlpha True if alpha channel is to be present in the new color space.
			@return The new color space object.
	*/
	explicit ColorSpace (const ai::ColorSpace &baseCs, bool hasAlpha);
	/** Copy constructor.
			@param cs the color space to copy.
			@return The new color space object.
		*/
	ColorSpace (const ai::ColorSpace &cs);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move constructor.
			@param rhs the color space to move from.
			@return The new color space object.
		*/
	ColorSpace (ColorSpace&& rhs) AINOEXCEPT;
#endif

	/** Destructor */
	~ColorSpace ();
	//@}

	/** Swaps the contents of this ColorSpace with another ColorSpace.
			@param rhs The ColorSpace to swap.
			@return Nothing.
		*/
	void swap(ColorSpace& rhs) AINOEXCEPT;

	/** Copy assignment operator */
	ai::ColorSpace& operator= (const ai::ColorSpace& rhs);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move assignment operator */
	ai::ColorSpace& operator= (ColorSpace&& rhs) AINOEXCEPT;
#endif

	/** Equality operator */
	bool operator== (const ai::ColorSpace& rhs) const;

	/** Inequality operator */
	bool operator!= (const ai::ColorSpace& rhs) const;

	/* Color Space Methods */

	/** Reports whether this color space is valid.
			@return True if the color space is valid, false otherwise.
		*/
	bool IsValid(void) const;
	/** Retrieves the family of this color space.
			@return The color space family constant.
		*/
	ai::ColorSpace::Family GetFamily(void) const;
	/** Reports whether this color space has an alpha channel.
		An indexed color space has an alpha channel if and only if
		its base color space has an alpha channel.
			@return True if the color space has an alpha channel, false otherwise.
		*/
	bool HasAlpha(void) const;
	/** Retrieves the number of components in this color space, including the alpha channel
		if present. An indexed color space has only one component in addition to the
		possible alpha component (not the number of color components in the base color space).
			@return The number of components.
		*/
    int NumComponents(void) const;
	/** Retrieves the number of color components in this color space, excluding the alpha channel
		if present. For an indexed color space, this is the number of color components
		in its base color space.
			@return The number of color components.
		*/
    int NumColorComponents(void) const;
	/** Retrieves the number of spot components in this color space. Ignores
	   	the alpha channel, if present.
	  		 @return 0 for CMYK, RGB, Gray, Lab, and process separations.
	  			<br> 1 for  spot separations
				<br> For an Indexed color space, the number of spot color components in its base color space.
		*/
	int NumSpotComponents(void) const;
	/** Retrieves the number of process components in this color space,
		which is the number of color components, minus the number of spot components.
			@return The number of process components.
	*/
	int NumProcessComponents(void) const;
	/** Retrieves the base color space for this indexed color space, or
		the alternate color space for this separation or n-channel color space.
		 	@return The base or alternate color space, or, for a standard
				color space, this color space itself.
		*/
	ai::ColorSpace BaseColorSpace(void) const;
	/** Retrieves the number of components in the index color table of this
		indexed color space.
		Throws bad-parameter error for non-indexed color spaces.
			@return The number of color table components.
		*/
	int IndexedNumComponents(void) const;
	/** Retrieves the number of entries in the index color table of this
		indexed color space.
		Throws bad-parameter error for non-indexed color spaces.
			@return The number of color table entries.
		*/
	int IndexedNumEntries(void) const;
	/** Retrieves the color table of this indexed color space.
		Throws bad-parameter error for non-indexed color spaces.
			@return A pointer to the color table.
		*/
	const ASUInt8* IndexedTable(void) const;
	/** Retrieves an entry from the color table of this indexed color space.
			@param index The 0-based index position of the entry.
			@return A pointer to the entry, or \c NULL if the index is out of range.
		*/
	const ASUInt8* IndexedColors(ASUInt8 index) const;
	/**	Retrieves the alternate color values in the alternate color space
		for this separation color space.
		Throws bad-parameter error for non-separation color spaces.
			@return A pointer to the array of color values.
		*/
	const AIFloat* SeparationAltColors(void) const;
	/** Retrieves the fully-specified color space list for this color space.
		Throws bad-parameter error if this is an indexed color space.
			@return The color space list object.
	*/
	ai::ColorSpaceList GetColorSpaceList(void) const;
	/** Retrieves the name of a colorant for this color space.
		Throws bad-parameter error if index is out of range.
			@param n The 0-based index of the colorant, less than \c NumColorComponents().
			@return  "Gray" for Gray color spaces.
					<br> "Red","Green", or "Blue" for RGB color spaces.
					<br> "Cyan","Magenta","Yellow", or "Black" for CMYK color spaces.
					<br> Empty strings for LAB color spaces.
		*/
	ai::UnicodeString NthColorant(ai::int32 n) const;
	/** Reports whether this color space has all process components.
	  		 @return True if the color space has all process components
	  			<br> False if the color space has no process components, or
	  				for  spot, separation, or process separation color spaces.
		*/
	bool HasFullSetOfProcessComponents(void) const;

public:	// internal core use only
	void deleteImpl(void);
	const CAIColorSpaceImpl *getImpl(void) const;
	explicit ColorSpace (CAIColorSpaceImpl *impl);

private:
	CAIColorSpaceImpl *fImpl;
};

/**
Inline implementations
*/

/** swap function */
inline void ColorSpace::swap(ColorSpace& rhs) AINOEXCEPT
{
	std::swap(fImpl, rhs.fImpl);
}

#ifdef AI_HAS_RVALUE_REFERENCES

/** Move constructor */
inline ColorSpace::ColorSpace(ColorSpace&& rhs) AINOEXCEPT : fImpl{rhs.fImpl}
{
	rhs.fImpl = nullptr;
}

/** Move assignment operator */
inline ColorSpace& ColorSpace::operator=(ColorSpace&& rhs) AINOEXCEPT
{
	swap(rhs);
	return *this;
}

#endif // AI_HAS_RVALUE_REFERENCES

/**	This class represents a list of color spaces for Illustrator.
*/
class ColorSpaceList {
	friend class ColorSpace;

public:
	//----------------------------------------------------------------------
	/** @name Constructors & Destructor */
	//----------------------------------------------------------------------
	//@{
	/** Default color space list constructor.
		Creates an invalid color space list.
	    Throws no exceptions.
	    	@return The new list object.
		*/
	explicit ColorSpaceList (void) AINOTHROW;
	/** Creates a color space list containing an initial color space entry.
			@param cs The initial color space object.
			@return The new list object.
		*/
	explicit ColorSpaceList (const ai::ColorSpace& cs);
	/** Copy constructor.
			@param csList The color-space list object to copy.
			@return The new list object.
		*/
	ColorSpaceList (const ai::ColorSpaceList &csList);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move constructor.
			@param rhs The color-space list object to move from.
			@return The new list object.
		*/
	ColorSpaceList (ColorSpaceList&& rhs) AINOEXCEPT;
#endif

	/** Destructor */
	~ColorSpaceList ();
	//@}

	/** Swaps the contents of this ColorSpaceList with another ColorSpaceList.
		@param rhs The ColorSpaceList to swap.
		@return Nothing.
	*/
	void swap(ColorSpaceList& rhs) AINOEXCEPT;

	/** Copy assignment operator */
	ai::ColorSpaceList& operator= (const ai::ColorSpaceList& rhs);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move assignment operator */
	ColorSpaceList& operator= (ColorSpaceList&& rhs) AINOEXCEPT;
#endif

	/* Color Space List Methods */

	/** Reports whether this color-space list is valid.
			@return True if the list is valid.
		*/
	bool IsValid(void) const;
	/** Adds a color-space entry to this color-space list.
			@param cs The color-space list object to add.
			@return Nothing.
		*/
	void AddColorSpace(const ai::ColorSpace &cs);
	/** Reports the number of color-space entries in this list.
			@return The number of entries.
		*/
	int NumColorSpaces(void) const;
	/** Retrieves a color space from this list.
		Throws bad-parameter error if index is out of range.
			@param n The 0-based index of the color-space entry.
			@return The color-space object.
		*/
	ai::ColorSpace NthColorSpace(int n) const;
	/** Normalizes this color-space list by flattening any n-channel color-spaces,
		removing duplicates, compacting 4-process separation color spaces
		into a single CMYK process color space, and sorting the color spaces.
		The order of the spot-separation color spaces is preserved.
			@param docColorModel The document color model, an \c #AIDocumentColorModelValue.
			@param convertGrayToFullProcess Optional. When false (the default), if the document
				 color model is CMYK, a gray color space is converted to separation Black.
				 Otherwise, a gray color space is converted to the full process color in the
				 document color space.
			@return Nothing.
		*/
	void Normalize(short docColorModel, bool convertGrayToFullProcess = false);

public:
	/** Internal */
	void deleteImpl(void);

private:
	CAIColorSpaceListImpl *fImpl;
};

/**
Inline implementations
*/

/** swap function */
inline void ColorSpaceList::swap(ColorSpaceList& rhs) AINOEXCEPT
{
	std::swap(fImpl, rhs.fImpl);
}

#ifdef AI_HAS_RVALUE_REFERENCES

/** Move constructor */
inline ColorSpaceList::ColorSpaceList(ColorSpaceList&& rhs) AINOEXCEPT : fImpl{rhs.fImpl}
{
	rhs.fImpl = nullptr;
}

/** Move assignment operator */
inline ColorSpaceList& ColorSpaceList::operator=(ColorSpaceList&& rhs) AINOEXCEPT
{
	swap(rhs);
	return *this;
}

#endif // AI_HAS_RVALUE_REFERENCES

} // end of namespace ai

#endif	// _IAICOLORSPACE_H_
