//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/Suites.hpp $
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

#ifndef __Suites_hpp__
#define __Suites_hpp__

#include "ASTypes.h"

#include "SPAccess.h"
#include "SPPlugs.h"
#include "AINotifier.h"
#include "AIContext.h"
#include "AIUser.h"
#include "AIFolders.h"

// Suites acquired by the Suites class
extern "C" SPAccessSuite *sSPAccess;
extern "C" SPPluginsSuite *sSPPlugins;
extern "C" AINotifierSuite *sAINotifier;
extern "C" AIAppContextSuite *sAIAppContext;
extern "C" AIUserSuite* sAIUser;
extern "C" AIFilePathSuite* sAIFilePath;
extern "C" AIFoldersSuite* sAIFolders;
/*
	A dumb "acquire all these suites when I instantiate a Suites object and
	release them when it's destroyed" class.
*/

struct ImportSuite
{
	const char *name;
	int version;
	void *suite;
};
const ASInt32 kStartOptionalSuites	= 'OPTS';
const ASInt32 kEndAllSuites			= 0;

// The fAcquiredCount field is not necessarily maintained across unload/reloads;
// in fact it probably isn't.  Whenever we first create a Suites object after
// being loaded or reloaded, it's important to call InitializeRefCount on it.

class Suites
{
public:
	Suites();
	~Suites();
	ASErr Error() { return fError; }

	void InitializeRefCount() { fAcquiredCount = 1; }
	void acquire_Optional_Suites();

private:
	static ASUInt16 fAcquiredCount;
	ASErr fError;
	ASUInt16		fOptionalSuitesTotalCount;
	ASUInt16		fRequiredSuitesCount;
	ASUInt16		fOptionalSuitesAcquiredCount;

	ASErr AcquireSuites();
	ASErr ReleaseSuites(); 
	ASErr AcquireSuite(ImportSuite *suite);
	ASErr ReleaseSuite(ImportSuite *suite);
};

#endif
