/***********************************************************************/
/*                                                                     */
/* SPCaches.h                                                          */
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

#ifndef __SPCaches__
#define __SPCaches__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPTypes.h"
#include "SPMData.h"

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 **
 **	Constants
 **
 **/
/** Cache suite name */
#define kSPCachesSuite				"SP Caches Suite"
/** Cache suite version */
#define kSPCachesSuiteVersion		2

/* To receive these, an PIConditionalMessages property must be present
 * with the PIAcceptsPurgeCachesMessage flag set. */
/** @ingroup Callers
	The cache management caller. See \c #SPCachesSuite */
#define kSPCacheCaller					"SP Cache"
/** @ingroup Selectors
	Received by plug-in adapters with the \c #PIAcceptsPurgeCachesMessage flag set
	in the \c #PIConditionalMessages property, when a call has
	been made to \c #SPCachesSuite::SPFlushCaches(). Accompanied by
	the \c #SPPurgeCachesMessage.
	@see \c #SPAdaptersSuite, \c #kSPAdaptersDisposeInfoSelector
	*/
#define kSPPluginPurgeCachesSelector	"Plug-in Purge"

// The plug-in should return one of these two responses when it receives the kSPPluginPurgeCachesSelector
// <<defined in SPErrorCodes.h>>
//#define kSPPluginCachesFlushResponse	'pFls'
//#define kSPPluginCouldntFlushResponse	kSPNoError;
#include "SPErrorCodes.h"

/*******************************************************************************
 **
 **	Types
 **
 **/
/** Prototype for the cache-flushing procedure an adapter calls in response to the
	\c #kSPAdaptersDisposeInfoSelector, to determine which plug-ins to unload,
	and inform the caller of whether its managed plug-in have been unloaded.
		@param type The plug-in type, as set by the adapter. For PICA plug-ins, this type
			is \c #kSPFlushAccessType.
		@param data A pointer to the adapter-defined plug-in data. For PICA plug-ins, this
			data is an \c #SPAccessRef.
		@param flushed [out] A buffer in which to return the result,
			the number of plug-ins actually unloaded.
	*/
typedef SPErr (*SPFlushCachesProc)( const char *type, void *data, ai::int32 *flushed );

/** Message passed with the \c #kSPPluginPurgeCachesSelector. */
typedef struct SPPurgeCachesMessage {
	/** The message data. */
	SPMessageData d;
} SPPurgeCachesMessage;


/*******************************************************************************
 **
 **	Suite
 **
 **/
/** @ingroup Suites
	This suite allows you to manage PICA cache memory.

	PICA plug-ins are intended to move in and out of memory (cache) as necessary,
	to allow a small memory footprint. By default, PICA keeps loaded plug-ins in
	cache until the application heap has been filled, and then unloads them.
	Beyond this simple strategy, the application and plug-ins can use this
	function to unload plug-ins when needed. Plug-ins do not typically need
	to do this.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kSPCachesSuite and \c #kSPCachesSuiteVersion.
*/
typedef struct SPCachesSuite {
	/** Sends a message to all plug-in adapters telling them to unload any
		unused plug-ins from memory.
			@param flushProc The procedure the adapter uses to determine which
				plug-ins to unload.
			@param flushed [out] A buffer in which to return the result of the
				procedure calls, the total number of plug-ins actually unloaded.
		*/
	SPAPI SPErr (*SPFlushCaches)( SPFlushCachesProc flushProc, ai::int32 *flushed );

} SPCachesSuite;

/** Internal */
SPAPI SPErr SPFlushCaches( SPFlushCachesProc flushProc, ai::int32 *flushed );


#ifdef __cplusplus
}
#endif

#include "SPHeaderEnd.h"

#endif
