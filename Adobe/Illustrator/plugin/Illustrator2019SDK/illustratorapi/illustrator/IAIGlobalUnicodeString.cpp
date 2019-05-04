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

#include "IAIGlobalUnicodeString.hpp"
#include "AIGlobalUnicodeString.h"
#include "AIErrorHandler.h"
#include "AIContract.hpp"

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIGlobalUnicodeString)
#elif defined (_IAIGlobalUnicodeString_SUITE_INCLUDE_H)
	#include _IAIGlobalUnicodeString_SUITE_INCLUDE_H
#else
	// These need to be declared by client.
	extern "C" AIGlobalUnicodeStringSuite* sAIGlobalUnicodeString;
#endif

namespace ai
{
	const ai::UnicodeString& GlobalUnicodeString::Get() const
	{
		AIErrorThrower error;
		if (mStringPtr)
		{
			return *mStringPtr;
		}

		if (mIsZRef)
			error = sAIGlobalUnicodeString->AddString(ai::UnicodeString(ZREF(mStr)), &mStringPtr);
		else
			error = sAIGlobalUnicodeString->AddString(ai::UnicodeString(mStr, mSize, mEncoding), &mStringPtr);
		
		ai::Ensures(mStringPtr != nullptr);
		return *mStringPtr;
	}

	GlobalUnicodeString::GlobalUnicodeString(ai::UnicodeString str)
	{
		AIErrorThrower error;
		error = sAIGlobalUnicodeString->AddString(std::move(str), &mStringPtr);
		ai::Ensures(mStringPtr != nullptr);
	}
	
	void GlobalUnicodeString::Set(ai::UnicodeString newStr)
	{
		AIErrorThrower error;
		if (!mStringPtr)
		{
			error = sAIGlobalUnicodeString->AddString(std::move(newStr), &mStringPtr);
			ai::Ensures(mStringPtr != nullptr);
			return;
		}

		mStringPtr->swap(newStr);
	}

}

