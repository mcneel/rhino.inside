#ifndef __AILegacyTextConversion__
#define __AILegacyTextConversion__

/*
 *        Name:	AILegacyTextConversion.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Text Frame Object Suite.
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

#include "AIHeaderBegin.h"

/** @file AILegacyTextConversion.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAILegacyTextConversionSuite			"AI Legacy Text Conversion Suite"
#define kAILegacyTextConversionSuiteVersion3	AIAPI_VERSION(3)
#define kAILegacyTextConversionSuiteVersion		kAILegacyTextConversionSuiteVersion3
#define kAILegacyTextConversionVersion			kAILegacyTextConversionSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions to convert legacy text objects (from earlier
	versions of Illustrator) to native text objects.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAILegacyTextConversionSuite and \c #kAILegacyTextConversionVersion.
*/
typedef struct {

	/** Converts a legacy text object to native Illustrator text art objects.
			@param art The legacy text object. This function does not dispose of the object.
			@param paintOrder The position for the new artwork in the
				paint order, relative to the \c prep object.
				See \c AITypes::AIPaintOrder.
			@param prep	The prepositional art object.
			@param ret [out] A buffer in which to return a group art object containing art objects
				of type \c #kTextFrameArt.
	 */
	AIAPI AIErr (*ConvertToNative)(AIArtHandle art, ai::int16 paintOrder, AIArtHandle prep, AIArtHandle* ret);

	/** Traverses the artwork tree of the current document and converts every
		art object of type \c #kLegacyTextArt to an object of type \c #kTextFrameArt.
			@param foundAnyLegacy [out] A buffer in which to return true if any
				legacy text objects were found the document. May be \c NULL.
		*/
	AIAPI AIErr (*ConvertAllToNative)(AIBoolean* foundAnyLegacy);

	/** Reports whether a legacy art object is a copy--that is, the result
		of executing the "Copy text object" command, which converts to native art,
		and retains the legacy art behind it, with 40% transparency.
			@param LegacyArt The legacy art object.
			@param aCopy  [out] A buffer in which to return true if	the art is a copy.
		*/
	AIAPI AIErr (*IsACopy)( AIArtHandle LegacyArt , AIBoolean *aCopy);

} AILegacyTextConversionSuite;


#include "AIHeaderEnd.h"


#endif
