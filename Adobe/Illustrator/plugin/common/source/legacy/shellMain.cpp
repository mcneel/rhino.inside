//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/legacy/shellMain.cpp $
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


/**-----------------------------------------------------------------------------
 **
 **	Imports
 **
 **/
#include "IllustratorSDK.h"

#include "common.h"
#include "about.h"
#include "reportError.h"
#include "pluginHandler.h"

/**-----------------------------------------------------------------------------
 **
 **	Variables
 **
 **/

#include "suites.h"


// general globals
Globals * g;
short gAcquireCount;
SPAccessRef gSelfAccess;
extern "C" { SPBasicSuite * sSPBasic = NULL; }

/**-----------------------------------------------------------------------------
 **
 **	Forward Functions
 **
 **/

static AIErr StartupPlugin( SPInterfaceMessage *message );
static AIErr UnloadPlugin( SPAccessMessage *message );
static AIErr ReloadPlugin( SPAccessMessage *message );
static AIErr ShutdownPlugin( SPInterfaceMessage *message );
static AIErr AboutPlugin( SPInterfaceMessage *message );


/*******************************************************************************
 **
 **	Exported Functions
 **
 **/

// Tell Xcode to export the following symbols
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

// Plug-in entry point
extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message);

// Tell Xcode to return to default visibility for symbols
#if defined(__GNUC__)
#pragma GCC visibility pop
#endif

extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
	AIErr error = kNoErr;

	// This is just an easy way of not having to cast message to ( SPMessageData* )
	// everytime we use IsEqual()
	sSPBasic = ( ( SPMessageData* )message)->basic;

	// standard caller/selectors
	
	// if these do anything other than restore globals, you may need to move them
	// into the aquire/releaseSuites block
	if ( sSPBasic->IsEqual( caller, kSPAccessCaller ) ) {
		if ( sSPBasic->IsEqual( selector, kSPAccessUnloadSelector ) )
			error = UnloadPlugin( (SPAccessMessage*) message );
	
		else if ( sSPBasic->IsEqual( selector, kSPAccessReloadSelector ) )
			error = ReloadPlugin( (SPAccessMessage*) message );
	} 
	
	else {
		// we need suites for the following routines, so acquire all of them now
		error = acquireSuites( ((SPInterfaceMessage*)message)->d.basic );
		if ( error )								
			goto error;							

		if ( sSPBasic->IsEqual( caller, kSPInterfaceCaller ) ) {
			if ( sSPBasic->IsEqual( selector, kSPInterfaceStartupSelector ) )
				error = StartupPlugin( (SPInterfaceMessage*) message );

			else if ( sSPBasic->IsEqual( selector, kSPInterfaceAboutSelector ) )
				error = AboutPlugin( (SPInterfaceMessage*) message );
				
			else if ( sSPBasic->IsEqual( selector, kSPInterfaceShutdownSelector ) )
				error = ShutdownPlugin( (SPInterfaceMessage*) message );
		
		} else  
			error = handlePluginCaller( caller, selector, message );

error:
		if ( (error) && (error != kSPSuiteNotFoundError) && (error != 1))
			report_error( (SPInterfaceMessage*) message, error );

		releaseSuites( ((SPInterfaceMessage*)message)->d.basic );
	}

	return error;

}


static AIErr StartupPlugin ( SPInterfaceMessage *message ) {

	AIErr error = kNoErr;

	// Better to use SPBasicSuite for memory allocation (as opposed to alternatives such as SPBlocksSuite).
	error = message->d.basic->AllocateBlock( sizeof(Globals), (void **) &g );
	if ( error )
		goto error;

	error = pluginStartup( message );
	
error:
	return error;

}


static AIErr UnloadPlugin( SPAccessMessage *message ) {

	if ( message->d.globals )
		unloadPluginSuiteFunctions( message );

	message->d.globals = g; 
	return kNoErr;					

}


static AIErr ReloadPlugin( SPAccessMessage *message ) {

	AIErr error = kNoErr;		

	if ( message->d.globals )
		error = reloadPluginSuiteFunctions( message );

	g = (Globals*) message->d.globals;
	gAcquireCount = 0;
	return error;

}


static AIErr ShutdownPlugin( SPInterfaceMessage *message ) {

	AIErr error = kNoErr;		
	
	pluginShutdown( message );

	message->d.basic->FreeBlock(g);
	g = NULL;
	message->d.globals = NULL;
	return error;

}


static AIErr AboutPlugin( SPInterfaceMessage *message ) {

	goAbout( message );
	return kNoErr;

}






/**-----------------------------------------------------------------------------
 **
 **	Suite Functions
 **
 **/

// Acquire all of the suites in the imports array
extern AIErr acquireSuites( SPBasicSuite *sBasic ) {

	AIErr error = kNoErr;
	long i;

	if ( !gAcquireCount ) {	// suites have never been acquired, so get them
		for ( i = 0; i < sizeof(imports)/sizeof(imports[0]); ++i ) {
			if ( imports[i].suite != NULL ) {
				error = sBasic->AcquireSuite( imports[i].name, imports[i].version, (const void**)imports[i].suite );
				if ( error && sADMBasic != NULL)
				{
					char message[256];
					sprintf(message, "Error: %d, suite: %s, version: %d!", error, imports[i].name, imports[i].version );
					sADMBasic->MessageAlert( message );
					goto error;
				}
			}
		}
	}


error:
	gAcquireCount += 1;
	return error;


}


extern AIErr releaseSuites( SPBasicSuite *sBasic ) {

	AIErr error = kNoErr;
	long i;

	if ( gAcquireCount == 1 ) { // only release the suites on the last release, otherwise they are still in use
		for ( i = 0; i < sizeof(imports)/sizeof(imports[0]); ++i ) {
	
			void **procs = imports[i].suite;
	
			if ( procs != NULL ) { // && *procs != NULL ) {
				error = sBasic->ReleaseSuite( imports[i].name, imports[i].version );
				if ( error )
					goto error;
				*procs = NULL;
			}
	
		}
	}


error:	
	gAcquireCount--;
	return error;


}
