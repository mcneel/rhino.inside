//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/Suites.cpp $
//
//  $Revision: #1 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "Suites.hpp"

#include "SPBlocks.h"
#include "SPInterf.h"
#include "SPRuntme.h" 
#include "SPSuites.h" 

#include <string.h>
#include <stdio.h>

extern "C" {
	SPAccessSuite *sSPAccess;
	SPPluginsSuite *sSPPlugins;
	AINotifierSuite *sAINotifier;
	AIAppContextSuite *sAIAppContext;
	AIUserSuite *sAIUser;
	AIFilePathSuite *sAIFilePath;
	AIFoldersSuite *sAIFolders;
}

extern "C" SPBasicSuite *sSPBasic;

// These are the suites we always acquire because we need them
static ImportSuite gBasicSuites[] =
{
	kSPAccessSuite, kSPAccessSuiteVersion, &sSPAccess,
	kSPPluginsSuite, kSPPluginsSuiteVersion, &sSPPlugins,
	kAINotifierSuite, kAINotifierSuiteVersion, &sAINotifier,
	kAIAppContextSuite, kAIAppContextSuiteVersion, &sAIAppContext,
	kAIUserSuite, kAIUserSuiteVersion, &sAIUser,
	kAIFilePathSuite, kAIFilePathSuiteVersion, &sAIFilePath,
	kAIFoldersSuite, kAIFoldersSuiteVersion, &sAIFolders,
};


extern ImportSuite gImportSuites[];

ASUInt16 Suites::fAcquiredCount = 0;

Suites::Suites()
: fOptionalSuitesTotalCount(0), 
  fOptionalSuitesAcquiredCount(0),
  fRequiredSuitesCount(0)
{
	fError = AcquireSuites();
	ASUInt16 i = 0;
	while( (gImportSuites[i++].name != nullptr)) 
	{ ++fRequiredSuitesCount; } // Skip all required suites.

	if(gImportSuites[i - 1].version == kStartOptionalSuites)
	{
		while(gImportSuites[i++].name != nullptr)
		{
			++fOptionalSuitesTotalCount;
		}
	}
	if(kNoErr == fError)
		acquire_Optional_Suites();
}

Suites::~Suites()
{
	ReleaseSuites();
}

ASErr Suites::AcquireSuites()
{
	ASErr result = kNoErr;
	ASUInt16 i;

	if (fAcquiredCount == 0)
	{
		for (i = 0; i < sizeof(gBasicSuites)/sizeof(gBasicSuites[0]); ++i)
		{
			result = AcquireSuite(gBasicSuites+i);
			if (result)
				goto error;	
		}
		for (i = 0; gImportSuites[i].name != nullptr; ++i)
		{
			result = AcquireSuite(gImportSuites+i);
			if (result)
				goto error;	
		}
	}
	fAcquiredCount++;
	
error:
	return result;
}

ASErr Suites::AcquireSuite(ImportSuite *suite)
{
	ASErr result = kNoErr;

	if (suite->suite != nullptr) {
		result = sSPBasic->AcquireSuite(suite->name, 
									suite->version, 
									(const void **)suite->suite);
	}
	return result;
}

ASErr Suites::ReleaseSuites() 
{
	ASErr result = kNoErr;
	ASUInt16 i;
	
	fAcquiredCount--;
	
	if (fAcquiredCount == 0)
	{
		for (i = 0; i < sizeof(gBasicSuites)/sizeof(gBasicSuites[0]); ++i)
		{
			result = ReleaseSuite(gBasicSuites+i);
			if ( result )
				goto error;
		}
		for (i = 0; gImportSuites[i].name != nullptr; ++i)
		{
			result = ReleaseSuite(gImportSuites+i);
			if (result)
				goto error;	
		}
		if(gImportSuites[i++].version == kStartOptionalSuites)
		{
			for (; fOptionalSuitesAcquiredCount && (gImportSuites[i].name != nullptr); ++i)
			{
				result = ReleaseSuite(gImportSuites+i);
				if (result)
					goto error;
				else
					--fOptionalSuitesAcquiredCount;
			}
		}
	}
	
error:
	return result;
}

ASErr Suites::ReleaseSuite(ImportSuite *suite)
{
	ASErr result = kNoErr;

	if (suite->suite != nullptr) {
		void **s = (void **) suite->suite;
		if (*s != nullptr) {
			result = sSPBasic->ReleaseSuite(suite->name, suite->version);
			*s = nullptr;
		}
	}
	return result;
}

void Suites::acquire_Optional_Suites()
{
	if(fOptionalSuitesAcquiredCount != fOptionalSuitesTotalCount)
	{
		ImportSuite* optionalSuites = gImportSuites + fRequiredSuitesCount + 1;
		for(ASUInt16 i = 0; (i < fOptionalSuitesTotalCount) && optionalSuites->suite; ++i)
		{
			int** suitePtr = static_cast<int**>(optionalSuites->suite);
			if( *suitePtr == nullptr)
			{
				if( kNoErr == AcquireSuite(optionalSuites))
					++fOptionalSuitesAcquiredCount;
			}
			++optionalSuites;
		}
	}
}
