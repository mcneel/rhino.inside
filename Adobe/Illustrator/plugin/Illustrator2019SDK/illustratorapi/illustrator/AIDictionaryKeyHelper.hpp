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

#include "AIDictionary.h"
#include <array>
#include "AIAssert.hpp"

/**
	For frequent access to the dictionary using the AIDictionarySuite::Key() method, generating a
	key every time can be costly as it results in a search in the string pool.

	This set of macros is provided to avoid paying that cost for each access.

	How to use...
	Rather than passing in a key like "AI9_Mask", declare the key in either a
	header or a source file with:
		DictionaryKeyDeclare(kMask, "AI9_Mask");

	Then, define the global variable in the source file  with:
		DictionaryKeyDefine(kMask);

	Alternatively, if only the key is required in a source file, declare and define with:
		DictionaryKeyDeclareAndDefine(kMask, "AI9_Mask");

	In either of above cases, access AIDictKey by specifying the variable kMask.

	You can skip specifying a variable name (kMask above) and generated one
	automatically by using a combination of:
		InternalFromExternalKeyDeclare("AI9_Mask");
	and
		InternalFromExternalKeyDefine("AI9_Mask");
	or the convenience macro:
		InternalFromExternalKeyDeclareAndDefine("AI9_Mask");

	In these cases AIDictKey can be accessed by variable name DictKey_AI9_Mask.

	You can specify an array of key strings to create an array of keys.
	You need to specify array of key string (with or without name) as given in the
	following code:
		DictionaryKeyArrayDeclareAndDefine(kRounding, kRoundingStrArray);
	or
		InternalFromExternalKeyArrayDeclareAndDefine(kRoundingStrArray);

	In the second version, variable name generated is DictKey_kRoundingStrArray.

	kRoundingStrArray needs to be an array of key strings defined by any of the
	following syntaxes:
		const char* const kRoundingStrArray[]{"a", "b", "c"};
	or
		constexpr std::array<const char* const, 3> kRoundingStrArray{"a", "b", "c"};
	or
		constexpr ai::LiteralString kRoundingStrArray[]{"a", "b", "c"};
	or
		constexpr std::array<ai::LiteralString, 3> kRoundingStrArray{"a", "b", "c"};

	Individual keys are accessible by specifying the index using the [] operator
	like the following:
		kRounding[0]
	or
		DictKey_kRoundingStrArray[0]
*/


#define DictionaryKeyDeclare(keyName, keyStr) \
class DictionaryKey##keyName \
{ \
public: \
	inline const AIDictKey & GetAIDictKey() \
	{ \
		if (fKey == nullptr) \
		{ \
			fKey = sAIDictionary->Key(keyStr); \
		} \
		return fKey; \
	} \
	inline operator const AIDictKey & () { return GetAIDictKey(); } \
	DictionaryKey##keyName() {} \
	DictionaryKey##keyName(const DictionaryKey##keyName &) = delete; \
	DictionaryKey##keyName(DictionaryKey##keyName &&) = delete; \
	DictionaryKey##keyName & operator = (const DictionaryKey##keyName &) = delete; \
	DictionaryKey##keyName & operator = (DictionaryKey##keyName &&) = delete; \
private: \
	AIDictKey fKey{}; \
}; \
extern class DictionaryKey##keyName keyName


#define DictionaryKeyDefine(keyName) \
class DictionaryKey##keyName keyName


#define DictionaryKeyDeclareAndDefine(keyName, keyStr) \
DictionaryKeyDeclare(keyName, keyStr); \
DictionaryKeyDefine(keyName)


#define InternalFromExternalKeyDeclare(externalKeyName) \
DictionaryKeyDeclare(DictKey_##externalKeyName, externalKeyName)


#define InternalFromExternalKeyDefine(externalKeyName) \
DictionaryKeyDefine(DictKey_##externalKeyName)


#define InternalFromExternalKeyDeclareAndDefine(externalKeyName) \
DictionaryKeyDeclareAndDefine(DictKey_##externalKeyName, externalKeyName)


#define DictionaryKeyArrayDeclareAndDefine(keyName, keyStrArrayName) \
template < size_t N > class DictionaryKeyArray##keyName \
{ \
public: \
	inline const AIDictKey & operator [] (size_t index) \
	{ \
		AIMsgAssert(index < fKeys.size(), "Index out of bounds when trying to access dictionary key!"); \
		auto& key(fKeys.at(index)); \
		if (key == nullptr) \
		{ \
			key = sAIDictionary->Key(keyStrArrayName[index]); \
		} \
		return key; \
	} \
	DictionaryKeyArray##keyName() {} \
	DictionaryKeyArray##keyName(const DictionaryKeyArray##keyName &) = delete; \
	DictionaryKeyArray##keyName(DictionaryKeyArray##keyName &&) = delete; \
	DictionaryKeyArray##keyName & operator = (const DictionaryKeyArray##keyName &) = delete; \
	DictionaryKeyArray##keyName & operator = (DictionaryKeyArray##keyName &&) = delete; \
private: \
	std::array < AIDictKey, N > fKeys{}; \
}; \
class DictionaryKeyArray##keyName < sizeof(keyStrArrayName) / sizeof(keyStrArrayName[0]) > keyName


#define InternalFromExternalKeyArrayDeclareAndDefine(externalKeyStrArrayName) \
DictionaryKeyArrayDeclareAndDefine(DictKey_##externalKeyStrArrayName, externalKeyStrArrayName)
