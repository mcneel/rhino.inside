/***********************************************************************/
/*                                                                     */
/* SPHost.h                                                            */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1995-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

#ifndef __SPHost__
#define __SPHost__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPTypes.h"
#include "SPAccess.h"
#include "SPAdapts.h"
#include "SPBasic.h"
#include "SPBckDbg.h"
#include "SPBlocks.h"
#include "SPCaches.h"
#include "SPFiles.h"
#include "SPInterf.h"
#include "SPPlugs.h"
#include "SPProps.h"
#include "SPRuntme.h"
#include "SPStrngs.h"
#include "SPSuites.h"

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 **
 **	Constants
 **
 **/


// AJL 08/21/00 - Defining "RELEASE_PLUGINS_EARLY" causes the plugin system to detect
// which plugins were flushed at the end of launch time, then flush those plugins
// earlier in the launch process the next time around.  This prevents Illustrator
// from allocating gobs of memory on startup, then releasing it.  Bad on a 64MB machine.
#define RELEASE_PLUGINS_EARLY


/*
 *	The version number of the Sweet Pea host interface. You can compare it to the
 *	version number that Sweet Pea was compiled with to determine that you are
 *	running the version you think you are. See SPVersion() below.
 *
 *	This number consists of a hi word which is the major version number reflecting
 *	changes to the SP inteface, and a low word which is the minor revision number,
 *	for instance indicating bug fixes.
 */

#define kSPVersion		0x000B0002			// version 11.2


/*
 *	Options available to the host at init time. They are:
 *
 *	kSPHostBlockDebugOption - block allocation debugging is enabled. See
 *		SPBckDbg.h for details.
 *
 *	Examples:
 *
 *		SPInit( hostProcs, pluginsFolder, kSPHostNoOptions, error );
 *		// No debugging.
 *
 *		SPInit( hostProcs, pluginsFolder, kSPHostBlockDebugOption, error );
 *		// Enable block debugging.
 */

#define kSPHostNoOptions			0
#define kSPHostBlockDebugOption		(1<<0)


/*******************************************************************************
 **
 **	Functions
 **
 **/

/*
 *	SPInit() initializes Sweet Pea. It is the first call made to Sweet Pea. It
 *	initializes its suites and builds the list of application files.
 *
 *	HostProcs points to a filled-in structure of host callbacks, as described
 *	in SPRuntme.h. It may be NULL, in which case Sweet Pea uses its default
 *	versions for all of the host callbacks. PluginFolder is the file spec of the
 *	plug-ins folder. The contents of this folder are collected into the application
 *	files list (see SPFiles.h). Options may be any of the host options described
 *	above.
 */
SPErr SPInit( SPHostProcs *hostProcs, const SPPlatformFileReference *pluginFolder, ai::int32 options );
SPBoolean SPInited( void );

/*
 *	SPTerm() terminates Sweet Pea. Call this when your application quits.
 */
SPErr SPTerm( void );

/*
 *	SPStartupPlugins() scans the list of application files and builds the list
 *	of plug-ins. It then starts them up, calling each in turn with a start up
 *	message (see SPPlugs.h). Call this sometime after SPInit().
 */
SPErr SPStartupPlugins( void );

/*
 *	SPShutdownPlugins() shuts down the plug-ins. It calls each in turn with a
 *	shut down message (see SPPlugs.h). Call this when your application quits
 *	before calling SPTerm().
 */
SPErr SPShutdownPlugins( void );


#ifdef MAC_ENV
/*
 *	SPSetPPCLoadHeap() sets the destination heap of plug-in accesses on PowerPPC
 *	Macintoshes.  Plug-ins can load into the system heap or the application heap.
 */
typedef enum {
	kAppHeap = 0,
	kSysHeap
} SPTargetHeap;

SPErr SPSetPPCLoadHeap( SPTargetHeap target );

/*
 *	SPSetHostBundleRef() lets sweet pea know the bundle ref of the host.
 */
SPErr SPSetHostBundleRef(CFBundleRef hostBundle);
#endif


/*
 *	SPVersion() returns the version number of the Sweet Pea host interface (this
 *	file) for which Sweet Pea was built. You can compare this to the constant
 *	kSPVersion to make sure you're using the version you think you are.
 */
ai::uint32 SPVersion( void );


/*******************************************************************************
 **
 **	Errors
 **
 **/

#include "SPErrorCodes.h"

#ifdef __cplusplus
}
#endif

#include "SPHeaderEnd.h"

#endif
