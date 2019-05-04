/***********************************************************************/
/*                                                                     */
/* SPAccess.h                                                          */
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

#ifndef __SPAccess__
#define __SPAccess__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPTypes.h"
#include "SPPlugs.h"
#include "SPMData.h"

#if defined(MAC_ENV) && !defined(IOS_ENV)
	#import <CoreServices/CoreServices.h>
#endif

#ifdef WIN_ENV
	#include "AIWinDef.h"
#endif

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 **
 ** Constants
 **
 **/

/*
 *	The name and version number of the PICA Plug-in Access suite.
 */

/** Plug-in Access suite name */
#define kSPAccessSuite				"SP Access Suite"
/** Plug-in Access suite name */
#define kSPAccessSuiteVersion		3

/** @ingroup Callers
	The \c #SPAccessSuite sends a reload message (\c #kSPAccessReloadSelector)
	to a plug-in when it has just been loaded, and an unload message
	(\c #kSPAccessUnloadSelector) when it is about to be unloaded.
	A plug-in is automatically loaded when the application or another
	plug-in calls it or acquires as suite that it exports.
	A plug-in can be unloaded at any time if it is not being used.

 	A plug-in that exports a suite should unload the suite's procedure pointers
 	when it is unloaded, and restore them when the plug-in is reloaded.
 		\li On unload, replace the suite's procedure pointers
 			with the address of the \c #SPBasicSuite::Undefined() function
 			(which is always available). This is a protective measure
 			against other plug-ins that may mistakenly use the suite after they have
 			released it.
		\li On reload, restore the suite's procedure
			pointers with the updated addresses of their functions.

	For example:
	@code
	 	SPErr UnloadSuite( MySuite *mySuite, SPAccessMessage *message ) {
	 		mySuite->functionA = (void *) message->d.basic->Undefined;
	 		mySuite->functionB = (void *) message->d.basic->Undefined;
	 	}

	 	SPErr ReloadSuite( MySuite *mySuite, SPAccessMessage *message ) {
	 		mySuite->functionA = functionA;
	 		mySuite->functionB = functionB;
	 	}
	@endcode
	*/
#define kSPAccessCaller				"SP Access"
/** @ingroup Selectors
	The first message a plug-in receives on startup (whether
	loaded or reloaded). Allows you to restore saved state information,
	before startup initialization.
	See \c #kSPAccessCaller, \c #SPAccessSuite */
#define kSPAccessReloadSelector		"Reload"
/** @ingroup Selectors
	The first message a plug-in receives before being unloaded.
	Allows you to save state information
	See \c #kSPAccessCaller, \c #SPAccessSuite */
#define kSPAccessUnloadSelector		"Unload"

/** The name of the object that the \c #SPAccessSuite caches,
	which can be purged when caches are flushed. During a cache flush,
	if this is the type sent to the \c #SPFlushCachesProc, it can
	make calls to the Access suite to collect information about
	the access object before deciding to purge it or not.

	For example, this purges filter plug-ins before window plug-ins:
@code
long myFlushCachesProc( const char *type, void *data, SPErr *error ) {
long flush = TRUE;
if ( strcmp( type, kSPFlushAccessType ) == 0 ) {
	SPAccessRef access = data;
  	SPPluginRef plugin = sAccess->GetAccessPlugin( access, error );
  	fail( error );
		switch ( myPluginType( plugin ) ) {
  			case kMyFilterPlugin:
				if ( gPurgeLevel < kFilterPurgeLevel )
					flush = FALSE;
  				break;
  			case kMyWindowPlugin:
  				if ( gPurgeLevel < kWindowPurgeLevel )
  					flush = FALSE;
  				break;
  		}
  	}
 	return flush;
}
@endcode
*/
#define kSPFlushAccessType			"SP Flush Access"


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Prototype for a plug-in entry point, which receives messages from
	the application or other plug-ins.
		@param caller The caller, which identifies what suite or subsystem
			made the call. See @ref Callers.
		@param selector The specific event that triggered the call. See @ref Selectors.
		@param message The message data, whose type depends on the specific event.
	*/
typedef SPAPI SPErr (*SPEntry)( const char *caller, const char *selector, void *message );


/** A plug-in access object, used with the \c #SPAccessSuite to make calls
	to a plug-in. These objects are reference counted. The count is
	incremented when you acquire the object using \c #SPAccessSuite::AcquirePlugin()
	and decremented when you release it with \c #SPAccessSuite::ReleasePlugin(),
	so you must be careful to balance these calls. The object is automatically
	created and the plug-in loaded if necessary, and the object is destroyed
	and the plug-in unloaded when the reference count is 0.*/
typedef struct SPAccess *SPAccessRef;





#ifdef MAC_ENV
#if	defined(IOS_ENV)
typedef struct _SPMacResChain SPMacResChain;
typedef SPMacResChain* SPPlatformAccessRef;
#else
#ifndef __FILES__
#if __LP64__
	typedef int                             FSIORefNum;
#else
	typedef short                          FSIORefNum;
#endif  /* __LP64__ */
#endif	
/** Resource chain access information on Mac OS */
typedef struct {
	/** File reference number */
	FSIORefNum fileRefNum;
	/** CF bundle */
	CFBundleRef bundleRef;
} SPMacResChain;

/** Resource chain access information on Mac OS */
typedef SPMacResChain *SPPlatformAccessRef;
#endif	// !defined(IOS_ENV)

#endif

#ifdef WIN_ENV

/** Plug-in library handle on Windows.  */
typedef HINSTANCE SPPlatformAccessRef;

#endif

#if	!defined(IOS_ENV)
/** Access  information for the resource chain on Mac OS, or library information on Windows.
	See \c #SPAccessSuite::GetAccessInfo(). */
typedef struct {
	/** File access for entry and resources, when resource-access has not been set. */
	SPPlatformAccessRef defaultAccess;	/* */
	/** File access for entry and resources, when resource-access
		has been set using \c #SPAccessSuite::SetPluginResourceAccess().
		Otherwise \c NULL. */
	SPPlatformAccessRef resourceAccess;
	/** The time since the last access operation, in clock-ticks (1/60th second). */
	ai::uint32 lastAccessTicks;
} SPPlatformAccessInfo;
#endif	// !defined(IOS_ENV)



/** Sent in the \c #SPAccessMessage to identify when an access call was made.
	Use to distinguish a start-up load from a run-time load or reload,
	and a run-time unload from a shut-down unload. */
typedef enum {
	/** The receiving plug-in has been loaded at application startup, and not yet initialized.
		Sent with the \c #kSPAccessReloadSelector.*/
	kStartup = 0,
	/** The receiving plug-in has been loaded programmatically while the application
		is running, and has already been initialized.
		Sent with the \c #kSPAccessReloadSelector and the \c #kSPAccessUnloadSelector.*/
	kRuntime,
	/** The receiving plug-in is about to be unloaded after being shut down.
		Sent with the \c #kSPAccessUnloadSelector. */
	kShutdown,
	/** The receiving plug-in has a non-zero access count and the application is shutting down.
		Sent with the \c #kSPAccessUnloadSelector.
		If the plug-in has acquired itself in order to remain in memory,
		it should not free any resources  and not acquire others when this
		call is received.*/
	kTerminal
} SPAccessPoint;

/** Message sent with the \c #kSPAccessCaller.  */
typedef struct SPAccessMessage {
	/** The message data. */
	SPMessageData d;
	/** When the access occurred.  */
	SPAccessPoint when;
} SPAccessMessage;


/*******************************************************************************
 **
 ** Suite
 **
 **/

/** @ingroup Suites
	This suite is used to load and unload plug-ins. The functions allow
	you to send messages directly to another plug-in. For example:
@code
 	SPErr SendMessage( SPPluginRef plugin, const char *caller, const char *selector, void *message, SPErr *error ) {

 		SPErr result;
 		SPAccessRef access;

 		access = sAccess->AcquirePlugin( plugin, error );
 		fail( error );

 		result = sAccess->CallPlugin( access, caller, selector, message, error );
 		fail( error );

 		sAccess->ReleasePlugin( access, error );
 		fail( error );

 		return result;
 	}
@endcode
	Standard PICA plug-ins rarely call one another directly. Usually program
  	control flows from plug-in to plug-in through higher-level suites.
 	Plug-in adapters, which provide protocol conversion to non-PICA plug-ins,
 	can add their own access suites to provide access to their foreign plug-ins.

	@see \c #SPInterfaceSuite

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kSPAccessSuite and \c #kSPAccessSuiteVersion.
*/
typedef struct SPAccessSuite {

 	/** Loads a plug-in if necessary, and prepares it to be called. Creates
 		an accessor object if necessary, or increments the reference count
 		of the existing accessor. Use \c #ReleasePlugin() to decrement
		the count when you not longer need the accessor.

		A plug-in can acquire itself in order to remain in memory, even if
		not referenced by any other plug-in.
			@param plugin The plug-in object.
			@param access [out] A buffer in which to return the new access object.
 		*/
	SPAPI SPErr (*AcquirePlugin)( SPPluginRef plugin, SPAccessRef *access );

 	/** Decrements the reference count of an accessor object.
 		When the reference count reaches 0, frees the accessor object
 		and allows the associated plug-in to be unloaded.
 			@param access The access object.
 		*/
	SPAPI SPErr (*ReleasePlugin)( SPAccessRef access );

	/** Retrieves the accessor object for a plug-in.
		You can use this to get the accessor for your own plug-in, in order
		to access the resource chain or library information.

		Used by plug-ins that export suites to manually establish a
		resource context within any of the suite procedures, so that
		they can access resources. Not needed when a plug-in is called
		through its entry point. \c #SPAccessSuite::CallPlugin()
		sets up the resource context for you.

			@param plugin The plug-in object.
			@param access [out] A buffer in which to return the access object,
				or \c NULL if the plug-in is not loaded.
	 	*/
	SPAPI SPErr (*GetPluginAccess)( SPPluginRef plugin, SPAccessRef *access );
	/** Retrieves the plug-in for an accessor.
			@param access The access object.
			@param plugin [out] A buffer in which to return the plug-in object,
				regardless of whether the plug-in is actually loaded into memory.
	 	*/
	SPAPI SPErr (*GetAccessPlugin)( SPAccessRef access, SPPluginRef *plugin );
	/** Retrieves the entry point of a plug-in accessor. This is the point to
		which \c #CallPlugin() jumps. Before accessing the entry point directly,
		use \c #SetCurrentPlugin() to make the plug-in current.
			@param access The access object.
			@param entry [out] A buffer in which to return the entry point structure.
		*/
	SPAPI SPErr (*GetAccessEntry)( SPAccessRef access, SPEntry *entry );
	/** Retrieves the current reference count of an accessor object.
			@param access The access object.
			@param count [out] A buffer in which to return the count.
		*/
	SPAPI SPErr (*GetAccessCount)( SPAccessRef access, ai::int32 *count );
#if	!defined(IOS_ENV)
	/** Retrieves the platform-specific resource access information of a plug-in accessor.
		This is for the resource-chain in Mac OS, or the plug-in library in Windows.
			@param access The access object.
			@param info [out] A buffer in which to return the information structure.
		*/
	SPAPI SPErr (*GetAccessInfo)( SPAccessRef access, SPPlatformAccessInfo *info );

	/** Retrieves the platform-specific resource access information of a plug-in accessor.
		This is for the resource-chain in Mac OS, or the plug-in library in Windows.
			@param access The access object.
			@param info [out] A buffer in which to return the information structure.
				This differs from \c #SPAccessSuite::GetAccessInfo(), which takes an \c #SPAccessRef
				and returns the \c #SPPlatformAccessInfo.
		*/
	SPAPI SPErr (*GetPluginResourceAccess)( SPPluginRef plugin, SPPlatformAccessRef *resourceAccess );
	/** Sets the the platform-specific resource access information for a plug-in.
		@param plugin The plug-in object.
		@param resourceAccess The new resource-access information.
		*/
	SPAPI SPErr (*SetPluginResourceAccess)( SPPluginRef plugin, SPPlatformAccessRef resourceAccess );
#endif	// !defined(IOS_ENV)

	/** Sends a message to a plug-in, using an accessor object.
			@param access The access object.
			@param caller The caller.
			@param slector The selector.
			@param message The message, as required for the selector.
			@param result [out] A buffer in which to return the result of the call,
				returned by the called plug-in.
		*/
	SPAPI SPErr (*CallPlugin)( SPAccessRef access, const char *caller, const char *selector,
					void *message, SPErr *result );

	/** Retrieves the current plug-in, whose access information is the current
		resource context. This is typically the last plug-in to
		receive a call, but can be set by a plug-in adapter, or by
		\c #SetCurrentPlugin().
			@param plugin [out] A buffer in which to return the plug-in object,
		*/
	SPAPI SPErr (*GetCurrentPlugin)( SPPluginRef *plugin );
	/** Makes a plug-in and its resource context current. An adapter can use
		this to set the resource context before making a call to a plug-in.
		Before making this call, you should save the reference for the current
		plug-in, and restore it when this plug-in no longer needs to be current.
			@param plugin The plug-in object,
		*/
	SPAPI SPErr (*SetCurrentPlugin)( SPPluginRef plugin );

} SPAccessSuite;

/** Internal */
SPAPI SPErr SPAcquirePlugin( SPPluginRef plugin, SPAccessRef *access );
/** Internal */
SPAPI SPErr SPReleasePlugin( SPAccessRef access );

/** Internal */
SPAPI SPErr SPGetPluginAccess( SPPluginRef plugin, SPAccessRef *access );
/** Internal */
SPAPI SPErr SPGetAccessPlugin( SPAccessRef access, SPPluginRef *plugin );
/** Internal */
SPAPI SPErr SPGetAccessEntry( SPAccessRef access, SPEntry *entry );
/** Internal */
SPAPI SPErr SPGetAccessCount( SPAccessRef access, ai::int32 *count );
#if	!defined(IOS_ENV)
/** Internal */
SPAPI SPErr SPGetAccessInfo( SPAccessRef access, SPPlatformAccessInfo *info );

/** Internal */
SPAPI SPErr SPGetPluginResourceAccess( SPPluginRef plugin, SPPlatformAccessRef *resourceAccess );
/** Internal */
SPAPI SPErr SPSetPluginResourceAccess( SPPluginRef plugin, SPPlatformAccessRef resourceAccess );
#endif	// !defined(IOS_ENV)

/** Internal */
SPAPI SPErr SPCallPlugin( SPAccessRef access, const char *caller, const char *selector,
			void *message, SPErr *result );

/** Internal */
SPAPI SPErr SPGetCurrentPlugin( SPPluginRef *plugin );
/** Internal */
SPAPI SPErr SPSetCurrentPlugin( SPPluginRef plugin );


/*******************************************************************************
 **
 ** Errors
 **
 **/

#include "SPErrorCodes.h"

#ifdef __cplusplus
}
#endif

#include "SPHeaderEnd.h"

#endif
