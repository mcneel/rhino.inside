#ifndef __AIStringFormatUtils__
#define __AIStringFormatUtils__

/*
 *        Name:	AIStringFormatUtils.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator String Format Utilities Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2007 Adobe Systems Incorporated.
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

#include "IAIStringFormatUtils.h"

#include "AIHeaderBegin.h"

/** @file AIStringFormatUtils.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIStringFormatUtilsSuite			"AI String Format Utils Suite"
#define kAIStringFormatUtilsSuiteVersion	AIAPI_VERSION(3)
#define kAIStringFormatUtilsVersion			kAIStringFormatUtilsSuiteVersion

/*******************************************************************************
 **
 ** Types
 **
 **/

/** @ingroup Errors
	The input string could not be parsed into a number. */
#define kCannotParseStringError			'NF!P'


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides support for the \c ai::NumberFormat and
	\c ai::Locale classes in plug-ins.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIStringFormatUtilsSuite and \c #kAIStringFormatUtilsVersion.
*/
struct AIStringFormatUtilsSuite {

	/* Locale class support */

	/** Retrieves the language and region code string for a locale object.
		    @param id		The locale identifier.
			@param locale	[out] A buffer in which to return the result string.
	  	*/
	AIAPI AIErr (*GetLocaleString)(const ai::LocaleID id, ai::AutoBuffer<char>& locale);

	/** Retrieves the locale object identifier for a language and region code string.
			@param locale	The language and region code string.
	    	@param id		[out] A buffer in which to return the locale identifier.
 	  	*/
	AIAPI AIErr (*GetLocaleID)(const char* locale, ai::LocaleID& id );


	/* Number format creation & destruction */

	/** Initializes a \c ai::NumberFormat object for a locale.
	  		@param format	The number format object.
	   		@param locale	The locale object identifier.
     	*/
	AIAPI AIErr (*Initialize) (ai::NumberFormat& format, const ai::LocaleID locale);

	/** Initializes \c #ai::NumberFormat object with the default system setting
 		for number formatting, using the factory method \c #ai::NumberFormat::getFormat.
			@param format	The number format object.
 		*/
	AIAPI AIErr (*InitializeDefaultInstance) (ai::NumberFormat& format);

	/** Copies one number format object into another.
		If the source format object is empty or uninitialized, empties
		the destination format object.
			@param format	The destination format object.
			@param format2	The source format object.
 		*/
	AIAPI AIErr (*Copy) (ai::NumberFormat& format, const ai::NumberFormat& format2);

	/** Deletes the contents of a number format object.
	  		@param format	The format object.
   		*/
	AIAPI AIErr (*Destroy) (ai::NumberFormat& format);

	/* Basic operations */

	/** Formats a float value into a string using a \c ai::NumberFormat object.
			@param format	The number format object.
			@param value	The numeric value to be formatted.
			@param precision	The maximum number of digits allowed after the decimal point. If the
				precision of \c value is bigger than this, applies input rounding.
			@param padToPrecision	If true, and if the precision of the input value is less
				than \c precision, pad with zeroes after the decimal place so that the
				number of digits after the decimal in the formatted string matches the precision.
			@param str		[out] A buffer in which to return the formatted string.
		*/
	AIAPI AIErr (*RealToString) (ai::NumberFormat& format, const float value, const ai::int32 precision,
									AIBoolean padToPrecision, ai::UnicodeString& str);

	/** Formats an integer value into a string using a \c ai::NumberFormat object.
			@param format	The number format object.
			@param value	The numeric value to be formatted.
			@param str		[out] A buffer in which to return the formatted string.
		*/
	AIAPI AIErr (*IntegerToString) (ai::NumberFormat& format, const ai::int32 value, ai::UnicodeString& str);

	/** Formats a double value into a string using a \c #ai::NumberFormat object.
			@param format	The number format object.
			@param value	The numeric value to be formatted.
			@param precision The maximum number of digits allowed after the decimal point. If the
					precision of \c value is bigger than this, applies input rounding.
				@param padToPrecision If true, and if the precision of the input value is less
					than \c precision, pad with zeroes after the decimal place so that the
				number of digits after the decimal in the formatted string matches the precision.
			@param str		[out] A buffer in which to return the formatted string.
		*/
	AIAPI AIErr (*DoubleToString) (ai::NumberFormat& format, const double value, const ai::int32 precision,
									AIBoolean padToPrecision, ai::UnicodeString& str);

	/** Parses a string into a float value using a \c ai::NumberFormat object.
			@param format	The number format object.
			@param str		The string to be converted.
			@param value	[out] A buffer in which to return the numeric value.
			@returns \c #kBadParameterErr error if the string cannot be parsed
				into a valid numeric value.
		*/
	AIAPI AIErr (*StringToReal) (ai::NumberFormat& format, const ai::UnicodeString& str, float& value);

	/** Parses a string into an integer value using a \c ai::NumberFormat object.
			@param format	The number format object.
			@param str		The string to be converted.
			@param value	[out] A buffer in which to return the numeric value.
			@returns \c #kBadParameterErr error if the string cannot be parsed
				into a valid numeric value.
		*/
	AIAPI AIErr (*StringToInteger) (ai::NumberFormat& format, const ai::UnicodeString& str, ai::int32& value);

	/** Parses a input string into a double value. using a \c ai::NumberFormat object.
			@param format	The number format object.
			@param str		The string to be converted.
			@param value	[out] A buffer in which to return the numeric value.
			@returns \c #kBadParameterErr error if the string cannot be parsed
				into a valid numeric value.
		*/
	AIAPI AIErr (*StringToDouble) (ai::NumberFormat& format, const ai::UnicodeString& str, double& value);

	/** Retrieves the decimal separator character used by the locale of a \c ai::NumberFormat object.
			@param format	The number format object.
			@param str		[out] A buffer in which to return the decimal separator character.
		*/
	AIAPI AIErr (*GetDecimalSeparator) (ai::NumberFormat& format, ai::UnicodeString& str);

	/** Retrieves the thousands separator character used by the locale of a \c ai::NumberFormat object.
			@param format	The number format object.
			@param str		[out] A buffer in which to return the thousands separator character.
		*/
	AIAPI AIErr (*GetThousandsSeparator) (ai::NumberFormat& format, ai::UnicodeString& str);
};


#include "AIHeaderEnd.h"



#endif // __AIStringFormatUtils__
