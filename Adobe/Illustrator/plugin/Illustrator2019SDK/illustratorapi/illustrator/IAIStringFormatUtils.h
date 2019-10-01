/*
 *        Name:	IAIStringFormatUtils.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Interface to the wrapper class for AIStringFormatUtilsSuite & the
 *				primary interface for the AI core to the ai::NumberFormat object.
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


#ifndef _IAISTRINGFORMATUTILS_H_
#define _IAISTRINGFORMATUTILS_H_


#include "IAIUnicodeString.h"
#include "IAILocale.h"
#include <sstream>


class CAINumberFormatImpl;

namespace ai {

/** Utility to create std::string using ostringstream.	*/
template<typename T>
std::string to_string(const T& value)
{
	std::ostringstream ostr;
	ostr << value;
	return ostr.str();
}

/** Class used for locale-dependent number formatting. Based on the input locale, this class
	internally handles the conversion between numbers and strings using the appropriate
 	decimal and thousands separator characters. */
class NumberFormat
{
public:

	/** Empty object constructor.  Creates a valid, empty \c NumberFormat instance
		that represents the default system setting for number formatting.  This method is guaranteed
	    to not throw any exceptions.
			@return The new instance.
	  */
	explicit NumberFormat (void) AINOTHROW;

	/** Creates an instance for a given locale.
			@param locale The locale to be used for formatting. Use \c kDefault for the
				current system locale setting.
			@return The new instance.
	  */
	explicit NumberFormat(const ai::LocaleID locale);

	/** Copy constructor.
			@return The new instance.
		*/
	NumberFormat(const NumberFormat& format);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move constructor.
			@return The new instance.
		*/
	NumberFormat(NumberFormat&& format) AINOEXCEPT : fImpl{format.fImpl}
	{
		format.fImpl = nullptr;
	}
#endif

	/** Default destructor  */
	~NumberFormat();

private:
	/**  Constructor that initializes with the static default instance of \c AGL_NumberFormat
	    	@param dummyUseDefaultFormatter Not used.
	    	@return The new instance.
	    */
	NumberFormat(bool dummyUseDefaultFormatter);

public:

	/** Creates or retrieves a \c NumberFormat instance for a given locale.
	   		@param locale The locale. Use \c kDefault for the current system locale setting.
			@return The new instance for the locale, or the static instance that the application
				maintains for the current system locale setting.
			@note If you require a new instance for the system locale setting, use the constructor instead.
	  */
	static NumberFormat getFormat(const ai::LocaleID locale = ai::Locale::kDefault);

	/** Formats a numeric value to a string, using the locale with which this
		instance was created.
			@param value The numeric value.
			@param precision The maximum number of digits allowed after the decimal point. If the input
				value has greater precision, the value is rounded down.
			@param str [out] A buffer in which to return the formatted string.
			@param padToPrecision When true, if the precision of the input value is
				 less than the maximum, pads the result string with zeros after the
				 decimal place. When false, does not pad the string.
			@return The result string (the same string returned in \c str).
	  	*/
	ai::UnicodeString& toString(const float value, const ai::int32 precision, ai::UnicodeString& str, bool padToPrecision = false);

	/** Formats a numeric value to a string, using the locale with which this
		instance was created.
			@param value The numeric value.
			@param str [out] A buffer in which to return the formatted string.
			@return The result string (the same string returned in \c str).
	  	*/
	ai::UnicodeString& toString(const ai::int32 value, ai::UnicodeString& str);

	/** Formats a numeric value to a string, using the locale with which this
		instance was created.
			@param value The numeric value.
			@param precision The maximum number of digits allowed after the decimal point. If the input
				value has greater precision, the value is rounded down.
			@param str [out] A buffer in which to return the formatted string.
			@param padToPrecision When true, if the precision of the input value is
				 less than the maximum, pads the result string with zeros after the
				 decimal place. When false, does not pad the string.
			@return The result string (the same string returned in \c str).
	  	*/
	ai::UnicodeString& toString(const double value, const ai::int32 precision, ai::UnicodeString& str, bool padToPrecision = false);

	/** Converts a string to a numeric floating-point value, if the string contains a
		number formatted according to the locale with which this instance was created.
			@param str	The string.
			@param value [out] A buffer in which to return the numeric value.
			@return	 True if the string could be parsed to a valid numeric value, false otherwise.
	  */
	bool parseString(const ai::UnicodeString& str, float& value);

	/** Converts a string to a numeric integer value, if the string contains a
		number formatted according to the locale with which this instance was created.
			@param str	The string.
			@param value [out] A buffer in which to return the numeric value.
			@return	 True if the string could be parsed to a valid numeric value, false otherwise.
	  */
	bool parseString(const ai::UnicodeString& str, ai::int32& value);

	/** Converts a string to a numeric floating-point value, if the string contains a
		number formatted according to the locale with which this instance was created.
			@param str	The string.
			@param value [out] A buffer in which to return the numeric value.
			@return	 True if the string could be parsed to a valid numeric value, false otherwise.
	  */
	bool parseString(const ai::UnicodeString& str, double& value);

	/** Copy assignment operator.  */
	ai::NumberFormat& operator= (const NumberFormat& rhs);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move assignment operator.  */
	ai::NumberFormat& operator= (NumberFormat&& rhs) AINOEXCEPT
	{
		std::swap(fImpl, rhs.fImpl);
		return *this;
	}
#endif

	/** Retrieves the decimal separator symbol used for the locale with which
		this instance was created.
 			@return The decimal separator character
	  */
	ai::UnicodeString getDecimalSeparator();

	/** Retrieves the thousands separator symbol used for the locale with which
		this instance was created.
 			@return The thousands separator character
	  */
	ai::UnicodeString getThousandsSeparator();

public:	// internal use public interface
	/** Internal */
	void deleteImpl();

	/** Internal */
	NumberFormat& assign (const NumberFormat& format);

private:

	CAINumberFormatImpl* fImpl;

};

} // end of namespace ai

#endif //_IAISTRINGFORMATUTILS_H_
