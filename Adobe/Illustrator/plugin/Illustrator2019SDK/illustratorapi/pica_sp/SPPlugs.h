/***********************************************************************/
/*                                                                     */
/* SPPlugs.h                                                           */
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

#ifndef __SPPlugins__
#define __SPPlugins__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPTypes.h"
#include "SPFiles.h"
#include "SPAdapts.h"
#include "SPProps.h"
#include "SPStrngs.h"

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 **
 ** Constants
 **
 **/
/** PICA plug-ins suite name */
#define kSPPluginsSuite				"SP Plug-ins Suite"
/** PICA plug-ins suite version */
#define kSPPluginsSuiteVersion4		4
/** PICA plug-ins suite version */
#define kSPPluginsSuiteVersion5		5

#ifdef WIN_ENV
	/** PICA plug-ins suite version */
	#define kSPPluginsSuiteVersion6		6
	/** PICA plug-ins suite version */
	#define kSPPluginsSuiteVersion		kSPPluginsSuiteVersion6
#elif defined(MAC_ENV)
	#define kSPPluginsSuiteVersion		kSPPluginsSuiteVersion4
#endif

/** PICA global list of available plug-ins.
	@see \c #SPRuntimeSuite::GetRuntimePluginList() */
#define kSPRuntimePluginList		((SPPluginListRef)NULL)


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a plug-in object. Access with the \c #SPPluginsSuite. */
typedef struct SPPlugin *SPPluginRef;
/** A list of plug-in objects. Create with
	\c #SPPluginsSuite::AllocatePluginList(), or use
	the global list, \c #kSPRuntimePluginList. */
typedef struct SPPluginList *SPPluginListRef;
/** An iterator object for examining a plug-in list.
	See \c #SPPluginsSuite::NewPluginListIterator(). */
typedef struct SPPluginListIterator *SPPluginListIteratorRef;

/** PICA file-access error */
typedef struct _SPErrorData
{
	/** The file for which the error occurred. */
	SPPlatformFileReference	mErrorFile;
	/** Error code, see @ref Errors. */
	SPErr						mErrorCode;
} SPErrorData, *SPErrorDataPtr;

/**  */
typedef SPAPI SPErr (*SPPluginEntryFunc)( const char *caller, const char *selector, void *message );

/*******************************************************************************
 **
 ** Suite
 **
 **/

/** This suite allows you to access and manipulate the plug-in object for your own
	and those of other plug-ins managed by the Adobe plug-in manager (PICA).
	You can access both plug-ins provided with the application (\e host plug-ins),
	and external plug-ins.You can query and set plug-in states,
	including the "broken" state, which indicates that a plug-in has
	become unavailable due to an error condition.

	You can also use this suite to create and use your own lists of plug-ins,
	in addition to the global list kept by the application.

	For higher-level access to plug-ins, see \c #AIPluginSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kSPPluginsSuite and \c #kSPPluginsSuiteVersion.
	*/
typedef struct SPPluginsSuite {

	/** Creates a new plug-in list. You can also access PICA's global plug-in list,
		using \c #SPRuntimeSuite::GetRuntimePluginList().
			@param stringPool The string pool in which to keep plug-in names.
			@param pluginList [out] A buffer in which to return the new list object.
		*/
	SPAPI SPErr (*AllocatePluginList)( SPStringPoolRef strings, SPPluginListRef *pluginList );
	/** Frees a list of plug-ins allocated with \c #AllocatePluginList(), and
		also frees any entries in the list. Do not free the global list (\c #kSPRuntimePluginList).
			@param pluginList The plug-in list object.
		*/
	SPAPI SPErr (*FreePluginList)( SPPluginListRef pluginList );

	/** Creates a new plug-in object and adds it to a plug-in list.
			@param pluginList The plug-in list object, or \c NULL to use the
				global list.
			@param fileSpec The file specification for the plug-in code and resources.
			@param PiPL The structure containing the plug-in properties.
			@param adapterName The unique identifying name of the adapter for the new plug-in.
			@param adapterInfo A pointer to the adapter-defined structure that stores needed
				information about this plug-in.
			@param plugin [out] A buffer in which to return the new plug-in object.
			@see \c #AllocatePluginList(), \c #SPAdaptersSuite
		*/
				
	SPAPI SPErr (*AddPlugin)( SPPluginListRef pluginList, const SPPlatformFileReference *fileSpec,
				PIPropertyList *PiPL, const char *adapterName, void *adapterInfo, SPPluginRef *plugin );

	/** Creates an iterator object with which to traverse a plug-in list.
		The iterator is initially set to the first plug-in in the list.
			@param pluginList The plug-in list object, or \c NULL to use the
				global list.
			@param iter [out] A buffer in which to return the new iterator object.
			@see \c #NextPlugin(), \c #DeletePluginListIterator()
		*/
	SPAPI SPErr (*NewPluginListIterator)( SPPluginListRef pluginList, SPPluginListIteratorRef *iter );
	/** Retrieves the current plug-in and advances a plug-in-list iterator to the next plug-in in the list.
			@param iter The plug-in-list iterator object.
			@param plugin [out] A buffer in which to return the current plug-in object, \c NULL
				if the end of the list has been reached.
		    @see \c #NewPluginListIterator(),
		*/
	SPAPI SPErr (*NextPlugin)( SPPluginListIteratorRef iter, SPPluginRef *plugin );
	/** Frees a plug-in-list iterator that is no longer needed.
			@param iter The plug-in-list iterator object.
			@see \c #NewPluginListIterator(),
		*/
	SPAPI SPErr (*DeletePluginListIterator)( SPPluginListIteratorRef iter );
	/**	Reports whether a plug-in that is needed is available in a plug-in list.
			@param pluginList The plug-in list object, or \c NULL to use the global list.
			@param available [out] A buffer in which to return true if the plug-in
				is found in the list.
			@see \c #SPInterfaceSuite::StartupExport()
		*/
	SPAPI SPErr (*GetPluginListNeededSuiteAvailable)( SPPluginListRef pluginList, SPBoolean *available );

	/**	Retrieves the callback structure provided by the host application for a plug-in.
			@param plugin The plug-in object.
			@param host A buffer in which to return the callback procedure.
		*/
	SPAPI SPErr (*GetPluginHostEntry)( SPPluginRef plugin, SPPluginEntryFunc *host );
	/**	Retrieves the code and resources file of a plug-in.
			@param plugin The plug-in object.
			@param fileSpec [out] A buffer in which to return the file specification.
			@see \c #SPFilesSuite
		*/
	SPAPI SPErr (*GetPluginFileReference)( SPPluginRef plugin, SPPlatformFileReference *fileSpec );
	/**	Retrieves the property list of a plug-in.
			@param plugin The plug-in object.
			@param propertList [out] A buffer in which to return the property list object.
			@see \c #SPPropertiesSuite
		*/
	SPAPI SPErr (*GetPluginPropertyList)( SPPluginRef plugin, SPPropertyListRef *propertList );
	/**	Retrieves the global variables of a plug-in. This is the same value passed in messages
		to the plug-in, which PICA stores when the plug-in is unloaded.
			@param plugin The plug-in object.
			@param globals [out] A buffer in which to return a pointer to the global variable array.
		*/
	SPAPI SPErr (*GetPluginGlobals)( SPPluginRef plugin, void **globals );
	/**	Sets the global variables for a plug-in. This is the same value passed in messages
		to the plug-in, which PICA stores when the plug-in is unloaded.
			@param plugin The plug-in object.
			@param globals The new global variable array.
		*/
	SPAPI SPErr (*SetPluginGlobals)( SPPluginRef plugin, void *globals );
	/**	Reports whether a plug-in has received and returned from the interface start-up message.
			@param plugin The plug-in object.
			@param started [out] A buffer in which to return true (non-zero) if the plug-in has been started,
				false (0) otherwise.
		*/
	SPAPI SPErr (*GetPluginStarted)( SPPluginRef plugin, ai::int32 *started );
	/**	Sets whether a plug-in has received and returned from the interface start-up message.
			@param plugin The plug-in object.
			@param started True (non-zero) if the plug-in has been started, false (0) otherwise.
		*/
	SPAPI SPErr (*SetPluginStarted)( SPPluginRef plugin, ai::int32 started );
	/**	Reports whether a plug-in is instructed to skip the start-up message.
			@param plugin The plug-in object.
			@param skipShutdown [out] A buffer in which to return true (non-zero) if the plug-in skips
				the start-up message, false (0) otherwise.
		*/
	SPAPI SPErr (*GetPluginSkipShutdown)( SPPluginRef plugin, ai::int32 *skipShutdown );
	/**	Instructs a plug-in to respond or not to respond to the start-up message.
			@param plugin The plug-in object.
			@param skipShutdown True (non-zero) to skip	the start-up message, false (0)
				to respond normally to the start-up message.
	*/
	SPAPI SPErr (*SetPluginSkipShutdown)( SPPluginRef plugin, ai::int32 skipShutdown );
	/**	Reports whether a plug-in has reported an error condition that makes it unavailable.
			@param plugin The plug-in object.
			@param broken [out] A buffer in which to return true (non-zero) if
				the plug-in is marked as broken, false (0) otherwise.
		*/
	SPAPI SPErr (*GetPluginBroken)( SPPluginRef plugin, ai::int32 *broken );
	/**	Sets or clears the broken flag that marks a plug-in as unavailable due to an
		error condition.
			@param plugin The plug-in object.
			@param broken True (non-zero) to mark the plug-in as broken, false (0)
				to clear the broken flag.
		*/
	SPAPI SPErr (*SetPluginBroken)( SPPluginRef plugin, ai::int32 broken );
	/**	Retrieves the adapter for a plug-in.
			@param plugin The plug-in object.
			@param adapter [out] A buffer in which to return the adapter object.
			@see \c #SPAdaptersSuite
		*/
	SPAPI SPErr (*GetPluginAdapter)( SPPluginRef plugin, SPAdapterRef *adapter );
	/**	Retrieves the adapter-specific information for a plug-in.  Typically
		used only by the adapter that defined the information. Other plug-ins
		should use \c #AIPluginSuite::GetPluginOptions().
			@param plugin The plug-in object.
			@param adapterInfo [out] A buffer in which to return a pointer to the adapter-defined
				information structure.
			@see \c #SPAdaptersSuite
		*/
	SPAPI SPErr (*GetPluginAdapterInfo)( SPPluginRef plugin, void **adapterInfo );
	/**	Sets the adapter-specific information for a plug-in. Typically
		used only by the adapter that defined the information. Other plug-ins
		should use \c #AIPluginSuite::SetPluginOptions().
			@param plugin The plug-in object.
			@param adapterInfo The adapter-defined information structure.
			@see \c #SPAdaptersSuite
		*/
	SPAPI SPErr (*SetPluginAdapterInfo)( SPPluginRef plugin, void *adapterInfo );

	/**	Retrieves a specific property from the property list for a plug-in.	If
		the property is not found in the list, sends the plug-in the
		\c #kSPPropertiesAcquireSelector message. The plug-in can ignore the
		message, or it can create and return the requested property. In either
        case, this function adds the (possibly \c NULL) property to the list
        and returns it.
			@param plugin The plug-in object.
			@param vendorID The property vendor ID code.
			@param propetyKey The property type key code.
			@param propertyID The specific property identifier.
			@param p [out] A buffer in which to return a pointer to the property object.
			@see \c #SPPropertiesSuite
		*/
	SPAPI SPErr (*FindPluginProperty)( SPPluginRef plugin, PIType vendorID, PIType propertyKey, ai::int32 propertyID, PIProperty **p );

	/**	Retrieves the name of a plug-in.
			@param plugin The plug-in object.
			@param name [out] A buffer in which to return the name string.
		*/
	SPAPI SPErr (*GetPluginName)( SPPluginRef plugin, const char **name );
	/**	Sets the name of a plug-in.
			@param plugin The plug-in object.
			@param name The new name string.
		*/
	SPAPI SPErr (*SetPluginName)( SPPluginRef plugin, const char *name );
	/**	Retrieves a plug-in by name.
			@param name The name string.
			@param plugin [out] A buffer in which to return the plug-in object.
		*/
	SPAPI SPErr (*GetNamedPlugin)( const char *name, SPPluginRef *plugin);

	/**	Sets the property list for a plug-in.
			@param plugin The plug-in object.
			@param file The file containing the property list.
		*/
	SPAPI SPErr (*SetPluginPropertyList)( SPPluginRef plugin, SPFileRef file );

	// Plug-ins suite version 5
	/* This attribute frees the adapterInfo field for private data for adapters. */
	/**	Retrieves host information for a plug-in.
			@param plugin The plug-in object.
			@param hostInfo [out] A buffer in which to return a pointer to the
				host information structure.
		*/
	SPAPI SPErr (*GetPluginHostInfo)( SPPluginRef plugin, void **hostInfo );
	/**	Sets host information for a plug-in.
			@param plugin The plug-in object.
			@param hostInfo The new host information structure.
		*/
	SPAPI SPErr (*SetPluginHostInfo)( SPPluginRef plugin, void *hostInfo );

} SPPluginsSuite;


/** Internal */
SPAPI SPErr SPAllocatePluginList( SPStringPoolRef strings, SPPluginListRef *pluginList );
/** Internal */
SPAPI SPErr SPFreePluginList( SPPluginListRef pluginList );
/** Internal */
SPAPI SPErr SPGetPluginListNeededSuiteAvailable( SPPluginListRef pluginList, SPBoolean *available );

/** Internal */
SPAPI SPErr SPAddPlugin( SPPluginListRef pluginList, const SPPlatformFileReference *fileSpec,
			PIPropertyList *PiPL, const char *adapterName, void *adapterInfo, SPPluginRef *plugin );

/** Internal */
SPAPI SPErr SPNewPluginListIterator( SPPluginListRef pluginList, SPPluginListIteratorRef *iter );
/** Internal */
SPAPI SPErr SPNextPlugin( SPPluginListIteratorRef iter, SPPluginRef *plugin );
/** Internal */
SPAPI SPErr SPDeletePluginListIterator( SPPluginListIteratorRef iter );

/** Internal */
SPAPI SPErr SPGetHostPluginEntry( SPPluginRef plugin, SPPluginEntryFunc *host );
/** Internal */
SPAPI SPErr SPGetPluginFileReference( SPPluginRef plugin, SPPlatformFileReference *fileSpec );
/** Internal */
SPAPI SPErr SPGetPluginPropertyList( SPPluginRef plugin, SPPropertyListRef *propertyList );
/** Internal */
SPAPI SPErr SPGetPluginGlobals( SPPluginRef plugin, void **globals );
/** Internal */
SPAPI SPErr SPSetPluginGlobals( SPPluginRef plugin, void *globals );
/** Internal */
SPAPI SPErr SPGetPluginStarted( SPPluginRef plugin, ai::int32 *started );
/** Internal */
SPAPI SPErr SPSetPluginStarted( SPPluginRef plugin, ai::int32 started );
/** Internal */
SPAPI SPErr SPGetPluginSkipShutdown( SPPluginRef plugin, ai::int32 *skipShutdown );
/** Internal */
SPAPI SPErr SPSetPluginSkipShutdown( SPPluginRef plugin, ai::int32 skipShutdown );
/** Internal */
SPAPI SPErr SPGetPluginBroken( SPPluginRef plugin, ai::int32 *broken );
/** Internal */
SPAPI SPErr SPSetPluginBroken( SPPluginRef plugin, ai::int32 broken );
/** Internal */
SPAPI SPErr SPGetPluginAdapter( SPPluginRef plugin, SPAdapterRef *adapter );
/** Internal */
SPAPI SPErr SPGetPluginAdapterInfo( SPPluginRef plugin, void **adapterInfo );
/** Internal */
SPAPI SPErr SPSetPluginAdapterInfo( SPPluginRef plugin, void *adapterInfo );

/** Internal */
SPAPI SPErr SPFindPluginProperty( SPPluginRef plugin, PIType vendorID, PIType propertyKey,
			ai::int32 propertyID, PIProperty **p );

/** Internal */
SPAPI SPErr SPGetPluginName( SPPluginRef plugin, const char **name );
/** Internal */
SPAPI SPErr SPSetPluginName( SPPluginRef plugin, const char *name );
/** Internal */
SPAPI SPErr SPGetNamedPlugin( const char *name, SPPluginRef *plugin);

/** Internal */
SPAPI SPErr SPSetPluginPropertyList( SPPluginRef plugin, SPFileRef file );

/** Internal */
SPErr SPAddHostPlugin( SPPluginListRef pluginList, SPPluginEntryFunc entry, void *access, const char *adapterName,
			void *adapterInfo, SPPluginRef *plugin, const char *name);
																  /* access is SPPlatformAccessRef */


// Plug-ins suite version 5
/* This attribute frees the adapterInfo field for private data for adapters. */
/** Internal */
SPAPI SPErr SPGetPluginHostInfo( SPPluginRef plugin, void **hostInfo );
/** Internal */
SPAPI SPErr SPSetPluginHostInfo( SPPluginRef plugin, void *hostInfo );

#ifdef WIN_ENV
	/** Internal */
	SPAPI SPErr SPAddPlugin_v4_v5( SPPluginListRef pluginList, const SPPlatformFileSpecification *fileSpec,
		PIPropertyList *PiPL, const char *adapterName, void *adapterInfo, SPPluginRef *plugin );

	/** Internal */
	SPAPI SPErr SPGetPluginFileReference_v4_v5( SPPluginRef plugin, SPPlatformFileSpecification *fileSpec );
#endif
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
