/*
 *        Name:	IAIStringFormatUtils.cpp
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Plug-in side implementation of the
 *				ai::Locale and ai::NumberFormat object interface.
 *				This file should NOT be included in the 
 *				core application.
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

#include "IAIStringFormatUtils.h"
#include "AIStringFormatUtils.h"
#include "SPBlocks.h"

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIStringFormatUtils)
#elif defined(_IAISTRINGFORMATUTILS_SUITE_INCLUDE_H_)
    #include _IAISTRINGFORMATUTILS_SUITE_INCLUDE_H_
#else
    #ifndef _IAISTRINGFORMATUTILS_SUITE_USE_C_LINKAGE_
	    #define _IAISTRINGFORMATUTILS_SUITE_USE_C_LINKAGE_ 1
    #endif
    #if _IAISTRINGFORMATUTILS_SUITE_USE_C_LINKAGE_
    extern "C"
    {
    #endif
	/** The plug-in using the ai::Locale or the ai::NumberFormat class is required to provide
		these global suite pointers.  These pointers must be valid prior
		to any call to ai::Locale and ai::NumberFormat methods.
	*/
	extern AIStringFormatUtilsSuite* sAIStringFormatUtils;
	extern SPBlocksSuite *sSPBlocks;

    #if _IAISTRINGFORMATUTILS_SUITE_USE_C_LINKAGE_
    }
    #endif // _IAISTRINGFORMATUTILS_SUITE_USE_C_LINKAGE_
#endif

/** Checks the result.  If @a result indicates an error, it is
	thrown as an ai::Error exception.  If result does not indicate
	an error, this function simply returns.
	@param result result code to check. */
static void check_result(AIErr result)
{
	if ( result != kNoErr )
	{
		throw ai::Error(result);
	}
}

/* ai::Locale methods */
 
std::string ai::Locale::getLocale(const ai::LocaleID id)
{
	ai::AutoBuffer<char> locale;

	sAIStringFormatUtils->GetLocaleString(id, locale);

	if ( locale.GetCount() > 0 )
	{
		return std::string(locale.GetBuffer(), locale.GetCount());
	}
	else
	{
		return std::string();
	}
}

ai::LocaleID ai::Locale::getID(const std::string& locale)
{
	ai::LocaleID id;
	sAIStringFormatUtils->GetLocaleID(locale.c_str(), id );

	return id;
}

ai::LocaleID ai::Locale::getSystemLocaleID()
{
	ai::LocaleID localeID;
	localeID = getID(ai::Locale::getLocale(kSystem));

	return localeID;
}

ai::LocaleID ai::Locale::getApplicationLocaleID()
{
	ai::LocaleID localeID;
	localeID = getID(ai::Locale::getLocale(kApplication));

	return localeID;
}

/* ai::NumberFormat methods */

ai::NumberFormat::NumberFormat(void) AINOTHROW
:fImpl(0)
{
}

ai::NumberFormat::NumberFormat(const ai::LocaleID locale)
:fImpl(0)
{
	AIErr result = sAIStringFormatUtils->Initialize(*this, locale);
	check_result(result);
}

ai::NumberFormat::NumberFormat(bool /*dummyUseStaticFormatter*/)
:fImpl(0)
{
	AIErr result = sAIStringFormatUtils->InitializeDefaultInstance(*this);
	check_result(result);
}

ai::NumberFormat::NumberFormat (const NumberFormat& s)
: fImpl(0)
{
	AIErr result = sAIStringFormatUtils->Copy(*this, s);
	check_result(result);
}

ai::NumberFormat::~NumberFormat()
{
	try
	{
		if (fImpl)
			sAIStringFormatUtils->Destroy(*this);
	}
	catch (...) {} //avoiding any exception leak in destructor
}

ai::NumberFormat ai::NumberFormat::getFormat(const ai::LocaleID locale)
{
	if (locale == ai::Locale::kDefault)
		return NumberFormat(true);
	else
		return NumberFormat(locale);
}

ai::NumberFormat& ai::NumberFormat::operator= (const NumberFormat& rhs)
{
	AIErr result = sAIStringFormatUtils->Copy(*this, rhs);
	check_result(result);
	return *this;
}

ai::UnicodeString& ai::NumberFormat::toString(const float value, const ai::int32 precision, ai::UnicodeString& str, 
											  bool padToPrecision) 
{
	AIErr result = sAIStringFormatUtils->RealToString(*this, value, precision, padToPrecision, str);
	check_result(result);
	return str;
}

ai::UnicodeString& ai::NumberFormat::toString(const ai::int32 value, ai::UnicodeString& str) 
{
	AIErr result = sAIStringFormatUtils->IntegerToString(*this, value, str);
	check_result(result);
	return str;
}

ai::UnicodeString& ai::NumberFormat::toString(const double value, const ai::int32 precision, ai::UnicodeString& str,
											  bool padToPrecision) 
{
	AIErr result = sAIStringFormatUtils->DoubleToString(*this, value, precision, padToPrecision, str);
	check_result(result);
	return str;
}

bool ai::NumberFormat::parseString(const ai::UnicodeString& str, float& value) 
{
	AIErr result = sAIStringFormatUtils->StringToReal(*this, str, value);

	if (result == kCannotParseStringError)
		return false;

	check_result(result);
	
	return true;
}

bool ai::NumberFormat::parseString(const ai::UnicodeString& str, ai::int32& value) 
{
	AIErr result = sAIStringFormatUtils->StringToInteger(*this, str, value);

	if (result == kCannotParseStringError)
		return false;

	check_result(result);
	
	return true;
}

bool ai::NumberFormat::parseString(const ai::UnicodeString& str, double& value) 
{
	AIErr result = sAIStringFormatUtils->StringToDouble(*this, str, value);

	if (result == kCannotParseStringError)
		return false;

	check_result(result);
	
	return true;
}

ai::UnicodeString ai::NumberFormat::getDecimalSeparator()
{
	ai::UnicodeString str;
	AIErr result = sAIStringFormatUtils->GetDecimalSeparator(*this, str);
	check_result(result);
	return str;
}

ai::UnicodeString ai::NumberFormat::getThousandsSeparator()
{
	ai::UnicodeString str;
	AIErr result = sAIStringFormatUtils->GetThousandsSeparator(*this, str);
	check_result(result);
	return str;
}
