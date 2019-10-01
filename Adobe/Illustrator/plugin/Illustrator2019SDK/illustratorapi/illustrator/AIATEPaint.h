/*
 *        Name:	AIATEPaint.h
 *   $Revision:
 *      Author:
 *        Date:
 *     Purpose:	Facilitates access of paint attributes applied to text.
 *				This suite serves as a bridge between ATE::ApplicationPaint
 *				and AIColor
 *
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

#ifndef __AIATEPAINT__
#define __AIATEPAINT__

/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AITypes.h"

#include "AIColor.h"
#include "AIEntry.h"
#include "AIPathStyle.h"

#include "ATESuites.h"


#include "AIHeaderBegin.h"

/** @file AIATEPaint.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIATEPaintSuite			"AIATE Paint Suite"
#define kAIATEPaintSuiteVersion3	AIAPI_VERSION(3)
#define kAIATEPaintSuiteVersion		kAIATEPaintSuiteVersion3
#define kAIATEPaintVersion			kAIATEPaintSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Allows you to convert between ATE and Illustrator types that describe
	color and other text style attributes.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIATEPaintSuite and \c #kAIATEPaintVersion.

	Keep the following in mind:

	\li Illustrator suites and ATE suites use slightly different memory management schemes
		for reference counting. To avoid problems, it is recommended that you use the
		C++ wrapper classes for the ATE suites instead of using the suites directly.
		See the example for \c #CreateATEApplicationPaint().

	\li  Because paint attributes are often partially defined, you \e must use style maps.
	All \c #AIPathStyle instances are treated and returned as partial. If you obtain an
	\c AIPathStyle from this suite, you must check its 	corresponding \c #AIPathStyleMap
	to determine what information in the style is valid.  No guarantees are made for invalid entries.
	Similarly, if you pass in an \c #AIPathStyle and \c #AIPathStyleMap, they must be a correct
	pairing.  Pairs that do not correspond produce undefined results.

	\li You cannot directly instantiate ATE \c ApplicationPaint and ATE \c ArrayReal.
	Instead, pass NULL pointers of type \c ApplicationPaintRef and \c ArrayRealRef,
	which are filled with valid references. See example for \c #CreateATEApplicationPaint().

	\li All methods return \c #kBadParameterErr if a bad parameter is passed in.
	These include NULL pointers or source parameters containing data the method was
	unable to convert; for example, an out-of-range value.

	\b EXAMPLES

	The following examples show how to get and set values for a range of text.

@code
	ATE::TextRangesRef selRef;
	sAIDocument->GetTextSelection(&selRef);
	ITextRanges ranges(selRef);
	ITextRange range = ranges.getFirst( );
	...
	bool isValid = false;
	AIPathStyle style;
	AIPathStyleMap styleMap;

	ICharFeatures features = range->getUniqueLocalCharFeatures( );
	IApplicationPaint paint = features.getStrokeColor( &isValid );

	if ( isValid )
	{
		error = sAIATEPaintSuite->GetAIPathStyleAndMap(
			features.GetRef(), &style, &styleMap
		);
		...
	}
@endcode

	This example starts with an \c #AIPathStyle and \c #AIPathStyleMap,
	and sets corresponding attribute values in an ATE \c CharFeaturesRef
	to create local overrides of text.

@code
	ITextRange range = ...

	// The C++ wrapper takes care of initialization
	ICharFeatures features;

	error = sAIATEPaintSuite->GetCharFeaturesRef(
		&style, &styleMap, features
	);

	if ( kNoErr == error )
	{
		range.setLocalCharFeatures( features );
	}
@endcode
*/

typedef struct {

	// ATE paint types -> Illustrator paint types
	// -------------------------------------------------------------------------

	/** Converts an ATE \c ApplicationPaintRef to \c #AIColor.
			@param src The ATE value.
			@param dst [out] A buffer in which to return the Illustrator value.
		*/
	AIAPI AIErr ( *GetAIColor ) ( ATE::ApplicationPaintRef src, AIColor* dst );

	/** Converts an ATE \c LineCapType to \c #AILineCap
			@param src The ATE value.
			@param dst [out] A buffer in which to return the Illustrator value.
		*/
	AIAPI AIErr ( *GetAILineCap ) ( ATE::LineCapType src, AILineCap* dst );

	/** Converts an ATE \c LineJoinType to \c #AILineJoin.
			@param src The ATE value.
			@param dst [out] A buffer in which to return the Illustrator value.
		*/
	AIAPI AIErr ( *GetAILineJoin ) ( ATE::LineJoinType src, AILineJoin* dst );

	/** Converts an ATE \c ArrayReal to array contained in \c #AIDashStyle
			@param src The ATE value.
			@param dst [out] A buffer in which to return the Illustrator value.
		*/
	AIAPI AIErr ( *GetAIDashStyleArray ) ( ATE::ArrayRealRef srcArray, AIDashStyle* dstStyle );

	// Illustrator paint types -> ATE paint types
	// -------------------------------------------------------------------------

	/** Converts an \c AIColor to an ATE \c ApplicationPaintRef.
		<br>\b Example:
		@code
// ApplicationPaintRef is NULL (an invalid reference).
ATE::ApplicationPaintRef pPaint = NULL;

// After this call, pPaint  is a valid reference
sAIATEPaintSuite->CreateATEApplicationPaint(&srcAIColor, &pPaint);

// Use the C++ wrapper to avoid ref counting.
IApplicationPaint paint(pPaint);
			...
		@endcode
			@param src The Illustrator value.
			@param dst [out] A buffer in which to return the ATE value.

		*/
	AIAPI AIErr ( *CreateATEApplicationPaint ) ( const AIColor* src, ATE::ApplicationPaintRef* dst );

	/** Converts an \c AILineCap to an ATE \c LineCapType.
			@param src The Illustrator value.
			@param dst [out] A buffer in which to return the ATE value.
		*/
	AIAPI AIErr ( *GetATELineCap ) ( AILineCap src, ATE::LineCapType* dst );

	/** Converts an \c AILineJoin to ATE \c LineJoinType.
		See example for \c #CreateATEApplicationPaint().
			@param src The Illustrator value.
			@param dst [out] A buffer in which to return the ATE value.
		*/
	AIAPI AIErr ( *GetATELineJoin ) ( AILineJoin src, ATE::LineJoinType* dst );

	/** Converts an array contained in an \c AIDashStyle to an ATE \c ArrayReal.
		See example for \c #CreateATEApplicationPaint().
			@param src The Illustrator value.
			@param dst [out] A buffer in which to return the ATE value.
		*/
	AIAPI AIErr ( *CreateATELineDashArray ) ( const AIDashStyle* srcStyle, ATE::ArrayRealRef* dst );

	// Convenience Methods
	// -------------------------------------------------------------------------

	/** Sets fields in a path style and path style map  by extracting
		corresponding data contained in an ATE character feature set.
			@param src The ATE character feature set.
			@param pDstPathStyle [out] A buffer in which to return the Illustrator path style.
			@param pDstPathStyleMap [out] A buffer in which to return the Illustrator path style map.
		*/
	AIAPI AIErr ( *GetAIPathStyleAndMap ) ( ATE::CharFeaturesRef src, AIPathStyle* pDstPathStyle, AIPathStyleMap* pDstPathStyleMap );

	/** Set fields in an ATE character feature set by extracting the
		corresponding data in a path style and path style map.
			@param srcPathStyle A pointer to the Illustrator path style.
			@param srcPathStyleMap A pointer to the Illustrator path style map.
			@param dst [out] A structure in which to return the new ATE character feature set.
		*/
	AIAPI AIErr ( *GetCharFeatures ) ( const AIPathStyle* pSrcPathStyle, const AIPathStyleMap* pSrcPathStyleMap, ATE::CharFeaturesRef dst );

	// Transparency Methods
	// -------------------------------------------------------------------------

	/** Extracts blend (transparency) information from an ATE character feature set
		and adds it to an Illustrator dictionary.
			@param pSrc The source ATE character feature set.
			@param pDst [out] The dictionary to modify. If the source contains no blend information,
				the dictionary is not modified.
			@see \c #AIBlendStyleSuite::GetArtAttrs() for a description of the dictionary entries.
		*/
	AIAPI AIErr ( *GetTransparencyAttrs ) ( ATE::CharFeaturesRef pSrc, AIDictionaryRef pDst );

	/** Sets the blend (transparency) attributes in an ATE character feature set
		based on the blend values in an Illustrator dictionary.
		All blend attribute in the dictionary must be known. If any are unknown,
		all blend information for \c pDst is cleared.
			@param pSrc The source dictionary.
			@param pDst [out] The ATE character feature set to modify.
			@see \c #AIBlendStyleSuite::GetArtAttrs() for a description of the dictionary entries.
		*/
	AIAPI AIErr ( *SetTransparencyAttrs ) ( AIDictionaryRef pSrc, ATE::CharFeaturesRef pDst );

} AIATEPaintSuite;

#include "AIHeaderEnd.h"

#endif // __AIATEPAINT__
