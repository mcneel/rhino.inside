//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/Tutorial/Source/TutorialSuites.cpp $
//
//  $Revision: #1 $
//
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"
#include "TutorialSuites.h"

extern "C"
{
	AIFilterSuite*				sAIFilter = nullptr;
	SPBlocksSuite*				sSPBlocks = nullptr;
	AIArtSuite*					sAIArt = nullptr;
	AIPathSuite*				sAIPath = nullptr;
	AIRealMathSuite*			sAIMath = nullptr;
	AIRandomSuite*				sAIRandom = nullptr;
	AIDocumentViewSuite*		sAIDocumentView = nullptr;
	AIToolSuite*				sAITool = nullptr;
	AIMatchingArtSuite*			sAIMatchingArt = nullptr;
	AIActionManagerSuite*		sAIActionManager = nullptr;
	AIMenuSuite*				sAIMenu = nullptr;
	AIUnicodeStringSuite*		sAIUnicodeString = nullptr;
	AIMdMemorySuite*			sAIMDMemory = nullptr;
	AIStringFormatUtilsSuite*	sAIStringFormatUtils = nullptr;
};

ImportSuite gImportSuites[] =
{
	kAIFilterSuite, kAIFilterVersion, &sAIFilter,
	kSPBlocksSuite, kSPBlocksSuiteVersion, &sSPBlocks,
	kAIArtSuite, kAIArtVersion, &sAIArt,
	kAIPathSuite, kAIPathVersion, &sAIPath,
	kAIRealMathSuite, kAIRealMathVersion, &sAIMath,
	kAIRandomSuite, kAIRandomVersion, &sAIRandom,
	kAIDocumentViewSuite, kAIDocumentViewVersion, &sAIDocumentView,
	kAIToolSuite, kAIToolVersion, &sAITool,
	kAIMatchingArtSuite, kAIMatchingArtVersion, &sAIMatchingArt,
	kAIActionManagerSuite, kAIActionManagerSuiteVersion, &sAIActionManager,
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, &sAIUnicodeString,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, &sAIMDMemory,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
	nullptr, 0, nullptr
};
