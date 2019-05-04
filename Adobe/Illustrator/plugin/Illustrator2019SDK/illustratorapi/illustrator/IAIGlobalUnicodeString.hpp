/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2017 Adobe
* 
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

#include "IAIUnicodeString.h"
#include "IAILiteralString.h"

/**
	As ai::UnicodeString objects are not safe to be created at global and static scope, 
	ai::GlobalUnicodeString helps in this requirement and wraps a lazy created ai::UnicodeString.
	The associated ai::UnicodeString is created on first call and is cached. 
	Its lifetime is guaranteed till plugin shutdown.
	
	@note: Client does not need to do anything for freeing the associated ai::UnicodeString object.

	Usage:
	
	1. Create with a literal string
		static ai::GlobalUnicodeString gStr ("my global string", kAIRomanCharacterEncoding);
		ai::GlobalUnicodeString gStr2 ("My UTF8 string", kAIUTF8CharacterEncoding);
		
	2. Create with a ZRef
		static ai::GlobalUnicodeString gStr3 (ZREF("$$$/MyZstringKey=String Value"));
		
	3. Create with an ai::LiteralString
		constexpr ai::LiteralString str ("a literal string");
		static const ai::GlobalUnicodeString gStr4(str, kAIRomanCharacterEncoding);
		
	This class has const ai::UnicodeString& operator overloaded. This object can be passed directly
	at most places where const ai::UnicodeString& is needed, .
	
	Get() method can be called at places where operator is not resolved.

	Set(newStr) to change the value of the global string with a new string. The old pointer remains valid, 
		only the value changes.
		Passing a temporary/Rvalue reference string to this method moves the string to the pool instead of creating a copy.
*/

namespace ai
{
	class GlobalUnicodeString
	{
	public:
		/**
			Constructor : Create with a literal string
				ai::GlobalUnicodeString gStr ("my global string", kAIRomanCharacterEncoding);
				ai::GlobalUnicodeString gStr2 ("My UTF8 string", kAIUTF8CharacterEncoding);
		*/
		template<std::size_t N>
		constexpr GlobalUnicodeString(const char(&str)[N], 
										AICharacterEncoding encoding) AINOEXCEPT : 
			mStr{ str }, mSize{ N - 1 }, mEncoding(encoding)
		{}

		/** Constructor: Create with an ai::LiteralString
				constexpr ai::LiteralString str ("a literal string");
				ai::GlobalUnicodeString gStr4(str, kAIRomanCharacterEncoding);
		*/
		constexpr GlobalUnicodeString(const ai::LiteralString& str, 
										AICharacterEncoding encoding) AINOEXCEPT:
			mStr(str.c_str()), mSize(str.size()), mEncoding(encoding)
		{}

		/** Constructor: Create with a ZRef
			ai::GlobalUnicodeString gStr3 (ZREF("$$$/MyZstringKey=String Value"));
		*/
		GlobalUnicodeString(const ZRef key) :mStr((const char*)key), mIsZRef(true) {}

		/** Constructor: Create with an ai::UnicodeString
			@note: Use this constructor only in  function which gets called after Startup Plugin as function static object.
				   Do not Create ai::GlobalUnicodeString object with this constructor at global scope.
		*/
		GlobalUnicodeString(ai::UnicodeString str);
		
		/**
			Returns the reference to global ai::UnicodeString stored for this GlobalUnicodeString.
		*/
		const ai::UnicodeString& Get() const;

		/**
			Changes the value of the associated global string.
		*/
		void Set(ai::UnicodeString newStr);

		/**
			Returns the reference to global ai::UnicodeString stored for this GlobalUnicodeString.
		*/
		operator const ai::UnicodeString&() const
		{
			return Get();
		}
	private:
		const char* mStr = nullptr;
		size_t mSize = 0;
		bool mIsZRef = false;
		mutable ai::UnicodeString* mStringPtr = nullptr;
		AICharacterEncoding mEncoding = kAIRomanCharacterEncoding;
	};
}

