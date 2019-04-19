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

#include "AIHeaderBegin.h"


#define kAIGlobalUnicodeStringSuite					"AI Global UnicodeString Suite"
#define kAIGlobalUnicodeStringSuiteVersion1			AIAPI_VERSION(1)
#define kAIGlobalUnicodeStringSuiteVersion			kAIGlobalUnicodeStringSuiteVersion1
#define kAIGlobalUnicodeStringVersion				kAIGlobalUnicodeStringSuiteVersion



/** 
	@ingroup Suites
	@see ai::GlobalUnicodeString defined in IAIGlobalUnicodeString.hpp
*/
struct AIGlobalUnicodeStringSuite
{
	/**
		Adds an ai::UnicodeString in the global pool and returns a permanent pointer to stored string.
		The lifetime of this pointer is guaranteed till plugin shutdown.
		
		@note: DO NOT FREE the returned pointer, its ownership is held by the app.
	*/
	AIAPI AIErr (*AddString)(ai::UnicodeString string, ai::UnicodeString** outPtr);
};

#include "AIHeaderEnd.h"
