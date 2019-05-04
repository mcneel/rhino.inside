/*
 *        Name:	IAIUnicodeString.inl
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Common impl file for the core and plug-ins.
 *		This file is included by IAIUnicodeString.cpp & IAIUnicodeStringCore.cpp
 *		Code added here MUST be shareable between the core and plug-ins.
 *			* You may not throw specific errors from these methods. (ai::Error vs. CAIFault)
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

#ifndef _IAIUNICODESTRING_INL_
#define _IAIUNICODESTRING_INL_

#include <vector>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Factory methods
//

ai::UnicodeString ai::UnicodeString::FromRoman (const char* string, size_type count)
{
	return UnicodeString(string, count, kAIRomanCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromRoman (const char* string)
{
	return UnicodeString(string, kAIRomanCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromRoman (const std::string& string)
{
	return UnicodeString(string, kAIRomanCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromRoman (const const_PStr& pascalString)
{
	return UnicodeString((const char*) &(pascalString.get()[1]), pascalString.get()[0], kAIRomanCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromPlatform (const char* string, size_type count)
{
	return UnicodeString(string, count, kAIPlatformCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromPlatform (const char* string)
{
	return UnicodeString(string, kAIPlatformCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromPlatform (const std::string& string)
{
	return UnicodeString(string, kAIPlatformCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromPlatform (const const_PStr&  pascalString)
{
	return UnicodeString((const char*) &(pascalString.get()[1]), pascalString.get()[0], kAIPlatformCharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromUTF8 (const char* string)
{
	return UnicodeString(string, kAIUTF8CharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromUTF8 (const std::string& string)
{
	return UnicodeString(string, kAIUTF8CharacterEncoding);
}

ai::UnicodeString ai::UnicodeString::FromUTF8 (const const_PStr&  pascalString)
{
	return UnicodeString((const char*) &(pascalString.get()[1]), pascalString.get()[0], kAIUTF8CharacterEncoding);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get to buffer methods
//

ai::UnicodeString::size_type ai::UnicodeString::getToBuffer ( char* buffer, size_type bufferMax, 
													 AICharacterEncoding encoding ) const
{
	// This is a sub-optimal implementation of hacking down the output text to fit in the buffer.
	// We're trying to ensure that the buffer contains whole characters in the target encoding.
	std::string s = getInStdString(encoding);
	const size_type kMaxByteLen = bufferMax - 2;
	const ai::UnicodeString::size_type kRequiredLength = s.length() + 2;

	if ( kRequiredLength > bufferMax )
	{
		ai::UnicodeString tmp = *this;
		ai::UnicodeString::size_type hackLen = this->length();
		while (kMaxByteLen < s.length())
		{
			--hackLen;
			tmp.erase(hackLen);
			s = tmp.getInStdString(encoding);
		}
	}

	size_type count = 0;
	for ( count = 0; count < s.length(); ++count )
	{
		buffer[count] = s[count];
	}
	buffer[count] = 0;
	buffer[count+1] = 0;
	
	return kRequiredLength;
}

ai::UnicodeString::size_type ai::UnicodeString::getToBuffer ( const PStr&  pascalString, size_type bufferMax, 
															AICharacterEncoding encoding ) const
{
	// This is a sub-optimal implementation of hacking down the output text to fit in the buffer.
	// We're trying to ensure that the buffer contains whole characters in the target encoding.
	std::string s = getInStdString(encoding);
	const size_type kMaxByteLen = bufferMax;
	const ai::UnicodeString::size_type kRequiredLength = s.length();

	if ( kRequiredLength > bufferMax )
	{
		ai::UnicodeString tmp = *this;
		ai::UnicodeString::size_type hackLen = this->length();
		while (kMaxByteLen < s.length())
		{
			--hackLen;
			tmp.erase(hackLen);
			s = tmp.getInStdString(encoding);
		}
	}

	size_type count = 0;
	for ( count = 0; count < s.length(); ++count )
	{
		pascalString[count+1] = static_cast<unsigned char>(s[count]);
	}
	pascalString[0] = static_cast<char>(count);
	
	return kRequiredLength;
}


#if defined( MAC_ENV )
ai::UnicodeString::UnicodeString (const CFStringRef& cfString)
: fImpl(0)
{
	const UniChar* uc = CFStringGetCharactersPtr(cfString);
	CFIndex cfLength = CFStringGetLength(cfString);

	if(cfLength > 0)
	{
		if ( uc != 0 )
		{
			*this = UnicodeString(uc, cfLength);
		}
		else
		{
			CFRange cfRange;
			cfRange.location = 0;
			cfRange.length = cfLength;
			std::vector<UniChar> buf(cfLength);
			CFStringGetCharacters(cfString, cfRange, &buf[0]);
			*this = UnicodeString(&buf[0], cfLength);
		}
	}
}

CFStringRef ai::UnicodeString::as_CFString ( CFAllocatorRef alloc ) const
{
	size_type count = 0;
	const UTF16Char* stringContents = 0;
	
	count = utf_16( stringContents );
	
	return CFStringCreateWithCharacters( alloc, stringContents, count );
}

#elif defined( WIN_ENV )

ai::UnicodeString::UnicodeString (const WCHARStr& string)
: fImpl(0)
{
	AI_STATIC_CHECK(sizeof(WCHARStr::WCHAR) == sizeof(UTF16Char), WCHAR_size_does_not_match_unsigned_short); //-V503
	*this = UnicodeString( string.as_ASUnicode() );
}

ai::WCHARStr ai::UnicodeString::as_WCHARStr () const
{
	return WCHARStr(*this);
}


#endif // MAC_ENV

#endif //_IAIUNICODESTRING_INL_
