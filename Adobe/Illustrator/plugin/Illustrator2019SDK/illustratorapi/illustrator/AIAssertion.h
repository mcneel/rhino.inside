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

#include "AITypes.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
**
**	Constants
**
**/

#define kAIAssertionSuite				"AI Assertion Suite"
#define kAIAssertionSuiteVersion1		AIAPI_VERSION(1)
#define kAIAssertionSuiteVersion		kAIAssertionSuiteVersion1
#define kAIAssertionVersion				kAIAssertionSuiteVersion

/*******************************************************************************
**
**	Suite
**
**/

struct AIAssertionSuite 
{
	/** Show an assert.
			@param success	: condition of assert.
			@param message	: Message to be displayed in Assert. Can be NULL.
			@param inFile	: Name of the file from where the assertion is thrown. Can be NULL.
			@param inLine	: Line number from where the assertion is thrown.
				This value is ignored if inFile is NULL.
	*/
	AIAPI void (*AssertProc)(AIBoolean success, const char* message, const char* inFile, ai::int32 inLine);

};

#include "AIHeaderEnd.h"