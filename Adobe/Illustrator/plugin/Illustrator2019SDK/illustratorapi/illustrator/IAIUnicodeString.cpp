/*
 *        Name:	IAIUnicodeString.cpp
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Plug-in side implementation of the
 *				ai::UnicodeString object interface.
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

#include "IAIUnicodeString.h"
#include "AIUnicodeString.h"

#include "IAIUnicodeString.inl"

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIUnicodeString)
#elif defined (_IAIUNICODESTRING_SUITE_INCLUDE_H_)
    #include _IAIUNICODESTRING_SUITE_INCLUDE_H_
#else
    #ifndef _IAIUNICODESTRING_SUITE_USE_C_LINKAGE_
	    #define _IAIUNICODESTRING_SUITE_USE_C_LINKAGE_ 1
    #endif
    #if _IAIUNICODESTRING_SUITE_USE_C_LINKAGE_
    extern "C"
    {
    #endif
	/** The plug-in using the ai::UnicodeString class is required to provide
		these global suite pointers.  These pointers must be valid prior
		to any call to ai::UnicodeString methods.
	*/
	extern AIUnicodeStringSuite* sAIUnicodeString;

    #if _IAIUNICODESTRING_SUITE_USE_C_LINKAGE_
    }
    #endif // _IAIUNICODESTRING_SUITE_USE_C_LINKAGE_

#endif

///////////////////////////////////////////////////////////////////////////////
// Constant declaration/definition
//
const ai::UnicodeString::size_type ai::UnicodeString::npos = ai::UnicodeString::size_type(-1);

///////////////////////////////////////////////////////////////////////////////
// Constructors/Destructor
//
ai::UnicodeString::UnicodeString () AINOTHROW
: fImpl(nullptr)
{
}

ai::UnicodeString::UnicodeString (const char* string, ai::UnicodeString::offset_type srcByteLen,
								  AICharacterEncoding encoding)
: fImpl(nullptr)
{
	if (string)
	{
		AIErr result = sAIUnicodeString->Initialize(*this, string, srcByteLen, encoding);
		check_ai_error(result);
	}
}

ai::UnicodeString::UnicodeString (ai::UnicodeString::size_type count, ai::UnicodeString::UTF32TextChar ch)
: fImpl(nullptr)
{
	if ( count > 0 )
	{
		AIErr result = sAIUnicodeString->InitializeUTF32Char(*this, count, ch);
		check_ai_error(result);
	}
}

ai::UnicodeString::UnicodeString (const char* string, AICharacterEncoding encoding)
: fImpl(nullptr)
{
	if ( string )
	{
		AIErr result = sAIUnicodeString->Initialize(*this, string, strlen(string), encoding);
		check_ai_error(result);
	}
}

ai::UnicodeString::UnicodeString (const std::string& string, AICharacterEncoding encoding)
: fImpl(nullptr)
{
	AIErr result = sAIUnicodeString->Initialize(*this, string.c_str(), string.length(), encoding);
	check_ai_error(result);
}

ai::UnicodeString::UnicodeString (const ASUnicode* string)
: fImpl(nullptr)
{
	if ( string )
	{
		AIErr result = sAIUnicodeString->InitializeUTF16(*this, string, npos);
		check_ai_error(result);
	}
}

ai::UnicodeString::UnicodeString (const ZRef zStringKey)
: fImpl(nullptr)
{
	AIErr result = sAIUnicodeString->InitializeZString(*this, zStringKey);
	check_ai_error(result);
}

ai::UnicodeString::UnicodeString (const ASUnicode* string, size_type srcUTF16Count)
: fImpl(nullptr)
{
	if ( string )
	{
		AIErr result = sAIUnicodeString->InitializeUTF16(*this, string, srcUTF16Count);
		check_ai_error(result);
	}
}

ai::UnicodeString::UnicodeString (const std::basic_string<ASUnicode>& string)
: fImpl(nullptr)
{
	AIErr result = sAIUnicodeString->InitializeUTF16(*this, string.data(), string.length());
	check_ai_error(result);
}

ai::UnicodeString::UnicodeString (const UnicodeString& s)
: fImpl(nullptr)
{
	AIErr result = sAIUnicodeString->Copy(*this, s);
	check_ai_error(result);
}

ai::UnicodeString::~UnicodeString ()
{
	if ( fImpl && sAIUnicodeString)
	{
		sAIUnicodeString->Destroy(*this);
	}
}

///////////////////////////////////////////////////////////////////////////////
// append ops
//

ai::UnicodeString& ai::UnicodeString::append (const UnicodeString& str)
{
	AIErr result = sAIUnicodeString->Append(*this, str);
	check_ai_error(result);
	return *this;
}

ai::UnicodeString& ai::UnicodeString::append (const UnicodeString& str, ai::UnicodeString::size_type startOffset, 
	ai::UnicodeString::size_type count)
{
	AIErr result = sAIUnicodeString->AppendSubString(*this, str, startOffset, count);
	check_ai_error(result);
	return *this;
}


ai::UnicodeString& ai::UnicodeString::assign (const UnicodeString& str)
{
	AIErr result = sAIUnicodeString->Assign(*this, str);
	check_ai_error(result);
	return *this;
}

ai::UnicodeString::UTF32TextChar ai::UnicodeString::at (ai::UnicodeString::size_type offset) const
{
	ai::UnicodeString::UTF32TextChar ch;
	AIErr result = sAIUnicodeString->GetChar(*this, offset, ch);
	check_ai_error(result);
	return ch;
}

void ai::UnicodeString::clear ()
{
	sAIUnicodeString->Clear(*this);
}

///////////////////////////////////////////////////////////////////////////////
// compare ops
//

ai::int32 ai::UnicodeString::compare (const UnicodeString& str) const
{
	ai::int32 result = sAIUnicodeString->Compare(*this, 0, this->length(), str, 0, str.length());
	return result;
}

ai::int32 ai::UnicodeString::compare (ai::UnicodeString::size_type pos, 
								ai::UnicodeString::size_type num, const UnicodeString& str) const
{
	ai::int32 result = sAIUnicodeString->Compare(*this, pos, num, str, 0, str.length());
	return result;
}

ai::int32 ai::UnicodeString::compare (ai::UnicodeString::size_type pos, 
								ai::UnicodeString::size_type num, const UnicodeString& str, 
								ai::UnicodeString::size_type startOffset, ai::UnicodeString::size_type count) const
{
	ai::int32 result = sAIUnicodeString->Compare(*this, pos, num, str, startOffset, count);
	return result;
}


ai::UnicodeString& ai::UnicodeString::toLower() {
	AIErr result = sAIUnicodeString->toLower(*this);
	check_ai_error(result);
	return *this;
}

ai::UnicodeString& ai::UnicodeString::toUpper() {
	AIErr result = sAIUnicodeString->toUpper(*this);
	check_ai_error(result);
	return *this;
}

ai::int32 ai::UnicodeString::caseCompare (ai::UnicodeString::size_type pos, 
								ai::UnicodeString::size_type num, const UnicodeString& str, 
								ai::UnicodeString::size_type startOffset, ai::UnicodeString::size_type count) const
{
	ai::int32 result = sAIUnicodeString->CaseCompare(*this, pos, num, str, startOffset, count);
	return result;
}

ai::int32 ai::UnicodeString::canonicalCompare (const UnicodeString& str) const
{
	ai::int32 compareResult = 0;
	AIErr result = sAIUnicodeString->CanonicalCompare(*this, str, compareResult);
	check_ai_error(result);

	return compareResult;
}

ai::int32 ai::UnicodeString::canonicalCaseCompare (const UnicodeString& str) const
{
	ai::int32 compareResult = 0;
	AIErr result = sAIUnicodeString->CanonicalCaseCompare(*this, str, compareResult);
	check_ai_error(result);

	return compareResult;
}

ai::UnicodeString& ai::UnicodeString::normalize (ai::UnicodeString::NormalizedForm form)
{
	AIErr result = sAIUnicodeString->Normalize(*this, form);
	check_ai_error(result);

	return *this;
}

ai::UnicodeString::size_type ai::UnicodeString::length () const
{
	ai::UnicodeString::size_type len = sAIUnicodeString->Length(*this);
	return len;
}

bool ai::UnicodeString::empty () const
{
	bool result = (sAIUnicodeString->Empty(*this) != false);
	return result;
}

ai::UnicodeString& ai::UnicodeString::erase (ai::UnicodeString::size_type pos, 
										  ai::UnicodeString::size_type count)
{
	AIErr result = sAIUnicodeString->Erase( *this, pos, count );
	check_ai_error(result);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// search ops
//

ai::UnicodeString::size_type ai::UnicodeString::find (ai::UnicodeString::UTF32TextChar ch, 
													  ai::UnicodeString::size_type startOffset) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->FindChar(*this, ch, startOffset);
	return pos;
}

ai::UnicodeString::size_type ai::UnicodeString::find (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->FindString( *this, target, startOffset );
	return pos;
}

ai::UnicodeString::size_type ai::UnicodeString::find (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset, 
													  ai::UnicodeString::size_type count) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->FindSubString( *this, 
		target, startOffset, count );
	return pos;
}

ai::UnicodeString::size_type ai::UnicodeString::caseFind (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset,
													  ai::UnicodeString::size_type count) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->CaseFindSubString( *this, target, 
		startOffset, count);
	return pos;
}


ai::UnicodeString::size_type ai::UnicodeString::rfind (ai::UnicodeString::UTF32TextChar ch, 
													  ai::UnicodeString::size_type startOffset) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->RFindChar( *this, ch, startOffset );
	return pos;
}

ai::UnicodeString::size_type ai::UnicodeString::rfind (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->RFindString( *this, target, startOffset );
	return pos;
}

ai::UnicodeString::size_type ai::UnicodeString::rfind (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset, 
													  ai::UnicodeString::size_type count) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->RFindSubString( *this, 
		target, startOffset, count);
	return pos;
}

ai::UnicodeString::size_type ai::UnicodeString::find_first_of (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset, 
													  ai::UnicodeString::size_type count) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->FindFirstOf( *this, 
		target, startOffset, count);
	return pos;
}
ai::UnicodeString::size_type ai::UnicodeString::find_first_not_of (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset, 
													  ai::UnicodeString::size_type count) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->FindFirstNotOf( *this, 
		target, startOffset, count);
	return pos;
}
ai::UnicodeString::size_type ai::UnicodeString::find_last_of (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset, 
													  ai::UnicodeString::size_type count) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->FindLastOf( *this, 
		target, startOffset, count);
	return pos;
}

ai::UnicodeString::size_type ai::UnicodeString::find_last_not_of (const UnicodeString& target, 
													  ai::UnicodeString::size_type startOffset, 
													  ai::UnicodeString::size_type count) const
{
	ai::UnicodeString::size_type pos = sAIUnicodeString->FindLastNotOf( *this, 
		target, startOffset, count);
	return pos;
}

void ai::UnicodeString::resize (ai::UnicodeString::size_type count, ai::UnicodeString::UTF32TextChar ch)
{
	AIErr result = sAIUnicodeString->Resize(*this, count, ch);
	check_ai_error(result);
}

ai::UnicodeString ai::UnicodeString::substr (ai::UnicodeString::size_type offset, 
										 ai::UnicodeString::size_type count) const
{
	ai::UnicodeString subString;
	AIErr result = sAIUnicodeString->SubStr(subString, *this, offset, count);
	check_ai_error(result);
	return subString;
}

ai::UnicodeString& ai::UnicodeString::operator= (const UnicodeString& rhs)
{
	AIErr result = sAIUnicodeString->Assign(*this, rhs);
	check_ai_error(result);
	return *this;
}

ai::UnicodeString::UTF32TextChar ai::UnicodeString::operator[] (ai::UnicodeString::size_type offset) const
{
	ai::UnicodeString::UTF32TextChar ch;
	AIErr result = sAIUnicodeString->GetChar(*this, offset, ch);
	if ( result != kNoErr )
	{
		ch = 0x0ffff;
	}

	return ch;
}

bool ai::UnicodeString::hasSurrogates () const
{
	bool result = (sAIUnicodeString->HasSurrogates(*this) != false);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
// extraction ops
//

ai::UnicodeString::size_type ai::UnicodeString::utf_16 (const UTF16Char*& buffer) const
{
	ai::UnicodeString::size_type len = sAIUnicodeString->UTF_16(*this, buffer);
	return len;
}

ai::UnicodeString::size_type ai::UnicodeString::getAs (AICharacterEncoding encoding, ai::AutoBuffer<char>& b) const
{
	ai::UnicodeString::size_type bufferByteCount = 0;
	AIErr result = sAIUnicodeString->GetAs(*this, encoding, b, 
		bufferByteCount);

	check_ai_error(result);

	return bufferByteCount;
}

std::string ai::UnicodeString::getInStdString (AICharacterEncoding encoding) const
{
	ai::AutoBuffer<char> contents;
	ai::UnicodeString::size_type byteCount = getAs(encoding, contents);

	if ( byteCount )
	{
		return std::string(contents.GetBuffer(), byteCount);
	}
	else
	{
		return std::string();
	}

}

std::basic_string<ASUnicode> ai::UnicodeString::as_ASUnicode ( ) const
{
	std::basic_string<ASUnicode> returnVal;
	const UTF16Char* buffer = 0;
	ai::UnicodeString::size_type codeUnitLen = utf_16(buffer);

	if ( buffer && codeUnitLen )
	{
		returnVal = std::basic_string<ASUnicode>(buffer, codeUnitLen);
	}

	return returnVal;
}

/////////////////////////////
// To maintain the previous semantic that using the UnicodeString class got
// you the AutoBuffer functionality "for free": include the implementation
// of the auto buffer class here.
////////////////////////////
#if defined(_IAIUNICODESTRING_SUITE_INCLUDE_H_) && !defined(_IAIAUTOBUFFER_SUITE_INCLUDE_H_)
  #define _IAIAUTOBUFFER_SUITE_INCLUDE_H_ _IAIUNICODESTRING_SUITE_INCLUDE_H_
#endif
#if !defined(_IAIAUTOBUFFER_SUITE_USE_C_LINKAGE_)
	#define _IAIAUTOBUFFER_SUITE_USE_C_LINKAGE_ _IAIUNICODESTRING_SUITE_USE_C_LINKAGE_ 
#endif 
#include "IAIAutoBuffer.cpp"
