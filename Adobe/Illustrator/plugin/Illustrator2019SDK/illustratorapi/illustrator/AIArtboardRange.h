/*************************************************************************
*
*ADOBE SYSTEMS INCORPORATED
* Copyright 2007 Adobe Systems Incorporated
* All Rights Reserved.
*
*NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
*terms of the Adobe license agreement accompanying it.  If you have received this file from a 
*source other than Adobe, then your use, modification, or distribution of it requires the prior 
*written permission of Adobe.
*
**************************************************************************/

#ifndef _AI_ARTBOARD_RANGE_H_
#define _AI_ARTBOARD_RANGE_H_

/*******************************************************************************
**
**	Imports
**
**/
#include "ASTypes.h"
#include "AIPlugin.h"

#include "AIHeaderBegin.h"

/** @file AIArtboardRange.h */

#define kAIArtboardRangeSuite			"AI Artboard Range Suite"
#define kAIArtboardRangeSuiteVersion4		AIAPI_VERSION(4)

/* Latest version */
#define kAIArtboardRangeSuiteVersion		kAIArtboardRangeSuiteVersion4
#define kAIArtboardRangeVersion			kAIArtboardRangeSuiteVersion


/** @ingroup Errors
See \c #AIArtboardRangeSuite */
#define kStdExceptionCaughtError ('SECE')
/** @ingroup Errors
Returned by \c #AIArtboardRangeSuite iteration functions if the end of a
range has been reached. */
#define kEndOfRangeErr			 ('ECRG')


/** Opaque artboard range reference. See \c #AIArtboardRangeSuite */
typedef struct _t_Opaque_ArtboardRange* AIArtboardRangeHandle;
/** Opaque artboard range iteration object. See \c #AIArtboardRangeSuite */
typedef struct _t_Opaque_ArtboardRangeIterator* AIArtboardRangeIterator;

/** @ingroup Suites
This suite allows you to validate a string containing a range of artboard indices and
sequentially iterate over the range. A range of artboards
is typically provided by the user in the Print, Save and Export dialogs.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIArtboardRangeSuite and \c #kAIArtboardRangeSuiteVersion.
*/
typedef struct
{
	/**  Creates an artboard range reference.

	@param allArtboards True to include all defined artboards in the range. False to use a range string.
	@param rangeStr A valid artboard range string. Ignored if \c allArtboards is true.
	@param range [out] A buffer in which to return the new artboard range reference.
	@see \c #ValidateString()
	*/
	AIAPI AIErr (*Create)(ASBoolean allArtboards, const ai::UnicodeString *rangeStr, AIArtboardRangeHandle* range);

	/**
	Retrieves the number of artboards in an artboard range.

	@param range An artboard range reference.
	@param count [out] A buffer in which to return the number of artboards.
	*/
	AIAPI AIErr (*GetCount)(AIArtboardRangeHandle range, ASInt32 *count);

	/**
	Creates a bi-directional iterator for an artboard range.

	@param range An artboard range reference.
	@param rangeItr [out] A buffer in which to return the iterator, which initially
	points to the first element of the artboard range.
	@see \c #DisposeIterator()
	*/
	AIAPI AIErr (*Begin)(AIArtboardRangeHandle range, AIArtboardRangeIterator *rangeItr);

	/**
	Retrieves the next element in an artboard range and increments the iterator.

	@param rangeItr The artboard range iterator.
	@param artboardNumber [out] A buffer in which to return the 0-based index of the next artboard.
	@return The error \c #kEndOfRangeErr if the iterator has reached the end of the range.
	*/
	AIAPI AIErr (*Next)(AIArtboardRangeIterator rangeItr, ASInt32 *artboardNumber);

	/**
	Retrieves the previous element in an artboard range and decrements the iterator.

	@param rangeItr The artboard range iterator.
	@param artboardNumber [out] A buffer in which to return the 0-based index of the previous artboard.
	@return The error \c #kEndOfRangeErr if the iterator has reached the beginning of the range.
	*/
	AIAPI AIErr (*Previous)(AIArtboardRangeIterator rangeItr, ASInt32 *artboardNumber);

	/**
	Sets the iterator to the last element in an artboard range.

	@param rangeItr The artboard range iterator.
	*/
	AIAPI AIErr(*Back)(AIArtboardRangeIterator rangeItr);

	/**
	Disposes of an artboard range iterator created by \c #Begin().

	@param rangeItr An artboard range iterator.
	*/
	AIAPI AIErr (*DisposeIterator)(AIArtboardRangeIterator rangeItr);

	/**
	Disposes of an artboard range handle created by \c #Create().

	@param range An artboard range reference.
	*/
	AIAPI AIErr (*Dispose) (AIArtboardRangeHandle);

	/**
	Validates an artboard range string. A valid range string contains a comma-separated
	list of artboard index numbers and index ranges (n-m). The index is 0-based.
	A valid string could be, for example, "1,2,3-5,8".

	@param rangeStr The string containing the artboard range.
	@return The error \c #kBadParameterErr if the range string is invalid.
	*/
	AIAPI AIErr (*ValidateString)(const ai::UnicodeString *rangeStr);

	/**
	Reports whether an artboard range includes all defined artboards.
	@param range An artboard range reference.
	@param result [out] A buffer in which to return the output as true if the range includes all artboards, false otherwise.
	@return The error \c #kBadParameterErr if any parameter is NULL.
	*/
	AIAPI AIErr (*IsAllSelected)(AIArtboardRangeHandle range,ASBoolean * result);

	/**
	Removes duplicate crop areas from an artboard range. This call re-sorts the range
	and invalidates all iterators for this range.
	@param range An artboard range reference.
	@return The error \c #kBadParameterErr if any parameter is NULL.
	*/
	AIAPI AIErr (*RemoveDuplicate)(AIArtboardRangeHandle range);

} AIArtboardRangeSuite;

#include "AIHeaderEnd.h"

#endif // _AI_ARTBOARD_RANGE_H_
