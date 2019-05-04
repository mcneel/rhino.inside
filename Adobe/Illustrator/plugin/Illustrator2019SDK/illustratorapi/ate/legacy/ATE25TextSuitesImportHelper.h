/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	ATE25TextSuitesImportHelper.h
		
	Notes:	Machine Generated file from script version 1.45
	        Please don't modify manually!
	
 ---------------------------------------------------------------------------------- */
#ifndef __ATE25TextSuitesImportHelper__
#define __ATE25TextSuitesImportHelper__

#include "ATETextSuitesImportHelper.h"

#define EXTERN_TEXT_SUITES_25\
	EXTERN_TEXT_SUITES
	ATE::ATE25DocumentTextResourcesSuite* sATE25DocumentTextResources;\
	ATE::ATE25TextFrameSuite* sATE25TextFrame;\
	ATE::ATE25CharFeaturesSuite* sATE25CharFeatures;\
	ATE::ATE25CharInspectorSuite* sATE25CharInspector;\
	ATE::ATE25FindSuite* sATE25Find;\
	ATE::ATE25ParaFeaturesSuite* sATE25ParaFeatures;\
	ATE::ATE25ParaInspectorSuite* sATE25ParaInspector;\
	ATE::ATE25SpellSuite* sATE25Spell;\

#define IMPORT_TEXT_SUITES_25\
	IMPORT_TEXT_SUITES
	{ kATE25DocumentTextResourcesSuite, kATE25DocumentTextResourcesSuiteVersion, &sATE25DocumentTextResources },\
	{ kATE25TextFrameSuite, kATE25TextFrameSuiteVersion, &sATE25TextFrame },\
	{ kATE25CharFeaturesSuite, kATE25CharFeaturesSuiteVersion, &sATE25CharFeatures },\
	{ kATE25CharInspectorSuite, kATE25CharInspectorSuiteVersion, &sATE25CharInspector },\
	{ kATE25FindSuite, kATE25FindSuiteVersion, &sATE25Find },\
	{ kATE25ParaFeaturesSuite, kATE25ParaFeaturesSuiteVersion, &sATE25ParaFeatures },\
	{ kATE25ParaInspectorSuite, kATE25ParaInspectorSuiteVersion, &sATE25ParaInspector },\
	{ kATE25SpellSuite, kATE25SpellSuiteVersion, &sATE25Spell },\

#endif //__ATE25TextSuitesImportHelper__


