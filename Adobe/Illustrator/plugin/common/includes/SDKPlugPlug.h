//========================================================================================
//  
//  $File: //ai/ai15/devtech/sdk/public/samplecode/common/includes/SDKPlugPlug.h $
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

#ifndef __SDKPLUGPLUG_H__
#define __SDKPLUGPLUG_H__

#pragma once

#include "AITypes.h"
#include "AIFolders.h"

#ifdef WIN_ENV
#include <windows.h>
#else

#endif

//-----------------------------------------------------------------------------
// Event
//-----------------------------------------------------------------------------

namespace csxs
{
namespace event 
{
	/**
	 * @brief Definition of possible scopes for events.
	 **/
	enum EventScope
	{
		/** 
		 * @brief This scope refers to events which will be dispatched to all available 
		 *        applications and all native listeners.
		 **/
		kEventScope_Global = 0,
				
		/**
		 * @brief This scope refers to events which will be dispatched only within the application
		 *        from where the event was dispatched.
		 **/
		kEventScope_Application = 1,
				
		/**
		 * @brief This ensures 32 bit int allocation and shouldn't be used in any other matter.
		 **/
		kEventScope_LastValue = 0x7FFFFFFF
	};

	/** @brief Error codes for event related operations. **/
	enum EventErrorCode
	{
		/** @brief Success. **/
		kEventErrorCode_Success = 0,
				
		/** @brief The operation which was executed did fail. **/
		kEventErrorCode_OperationFailed,
		
		/** @brief Unknown failure. **/
		kEventErrorCode_Unknown,				
				
		/** @brief This ensures 32 bit int allocation and shouldn't be used in any other matter. **/
		kEventErrorCode_LastValue = 0x7FFFFFFF
	};
		
	/**
	 * @brief Contains the information about an event which was dispatched.
	 **/
	struct Event 
	{
		/** @brief The type of the event. **/
		const char* type;
				
		/** @brief The scope of the event. **/
		EventScope scope;
			
		/** @brief The appId of the event. **/
		const char* appId;
				
		/** @brief The extensionId of the event or NULL if not thrown by an extension. **/
		const char* extensionId;
				
		/** @brief The event specific data. **/
		const char* data;
	};
		
	/**
	 * @brief A function pointer to a call back function which can be registered for events.
	 * @param event The event which was dispatched.
	 * @param context The context which was registered with the event listener or NULL.
	 **/
	typedef void (*EventListenerFn) (const Event* const event, void* const context);
}
}


//-----------------------------------------------------------------------------
// PlugPlug
//-----------------------------------------------------------------------------

/*!
\brief The error values returned from PlugPlug and Housing Plug-in calls.

These names are meant to be self-explanatory.  Note that true error codes are all non-zero values; a return value of zero is actually a success status.
*/
typedef enum PlugPlugErrorCode 
{
	PlugPlugErrorCode_success = 0, //!< = 0

	//!Callback-related errors
	PlugPlugErrorCode_registerExtCallbackNotFound,
	PlugPlugErrorCode_extensionEventCallbackNotFound,
	PlugPlugErrorCode_setMenuCallbackNotFound,
	PlugPlugErrorCode_allocateEvalScriptEngineCallbackNotFound,
	PlugPlugErrorCode_disposeEvalScriptEngineCallbackNotFound,
	PlugPlugErrorCode_evalScriptCallbackNotFound,
	PlugPlugErrorCode_requestStateChangeCallbackNotFound,
	PlugPlugErrorCode_requestLoadExtensionCallbackNotFound,
	PlugPlugErrorCode_evalScriptCallbackFailed,
	PlugPlugErrorCode_AMTRequestCallbackNotFound,
	PlugPlugErrorCode_allocatePlayerCallbackNotFound,
	PlugPlugErrorCode_disposePlayerCallbackNotFound,

	//!API-related errors
	PlugPlugErrorCode_extensionRegistrationFailed,
	PlugPlugErrorCode_multipleSetupCallsNotAllowed,
	PlugPlugErrorCode_extensionNotFound,
	PlugPlugErrorCode_extensionMenuCreationFailed,
	PlugPlugErrorCode_invalidParam,
	PlugPlugErrorCode_unexpectedValue,
	PlugPlugErrorCode_scriptFileLoadFailure,
	PlugPlugErrorCode_engineAllocationFailure,
	PlugPlugErrorCode_extensionNotLoaded,
	PlugPlugErrorCode_invalidApplicationName,
	PlugPlugErrorCode_noExtensionFound,
	PlugPlugErrorCode_invalidManifestFile,
	PlugPlugErrorCode_stageManagerNotFound,

	//!Window-related errors
	PlugPlugErrorCode_modalDialogCantInvokeAnotherWindow,
	PlugPlugErrorCode_cantInvokeAnOpenExtension,
	
	//!Script Engine errors
	PlugPlugErrorCode_engineUsedForMultipleIDs,
	PlugPlugErrorCode_engineRefcountIncreased,
	PlugPlugErrorCode_engineRefcountDecreased,
	
	//!Miscellaneous errors
	PlugPlugErrorCode_internalError,
	PlugPlugErrorCode_systemError,
	PlugPlugErrorCode_unknown,

	// If not able to allocate player to Extention
	PlugPlugErrorCode_PlayerAllocationFailed,

	// error code for flash panels
	PlugPlugErrorCode_needToClosePreviousFlashPanels,
	
	// codes for AMT call
	PlugPlugErrorCode_AMTMoreData, /*!< AMT call result has more data. */ 
	
	// streaming
	PlugPlugErrorCode_streamWriteCallbackNotFound,
	PlugPlugErrorCode_streamCloseCallbackNotFound,
	
	//last value
	PlugPlugErrorCode_lastValue	= 0x7FFFFFFF	//ensures 32 bit int allocation
} PlugPlugErrorCode;


/*!
 With PlugPlug version 1.0, 
 this method tells PlugPlug to prepare to load an extension.
 
 When the Housing Plug-in wants to create a window and load an extension into it, 
 it must first invoke this API to notify PlugPlug so that PlugPlug can make any necessary preparations, 
 such as starting the CSI. 
 After calling PlugPlugLoadExtension, the Housing plug-in will create the window and 
 loads the swf inside it. After that, Housing plug-in needs to send "PlugPlugOpen" 
 event for the extension by calling PlugPlug.NotifyStateChange() API for the extension, 
 passing in the geometry at which the extension was created. 
 When PlugPlug receives "PlugPlugOpen" event, only then it will consider the extension to be loaded, 
 otherwise PlugPlug will not consider it loaded and all the calls for this extension 
 will return "PlugPlugErrorCode_extensionNotLoaded" error. 
 In case the Housing plug-in fails to create the window or fails to load the SWF and 
 wants to close extension, it needs to call PlugPlugUnloadExtension() API.
 
 
 With version 2.0, 
 PlugPlug is delegating the loading of an extension to the StageManager.
 
 A prerequisite for this to work is that the StageManager has been loaded 
 into its own hidden APE stage. 
 Therefore, before calling PlugPlugLoadExtension() the host application must 
 load the StageManager SWF by calling APEPlayerLoadSwf() of the APE API.
 The StageManager has been registered with the host application like any other extension.
 Hence, the path to the StageManager SWF is known to the host application.
 
 On calling PlugPlugLoadExtension(), the StageManager create a new window for the extension in ActionScript.
 It is setting window properties in accordance with the values specified in the extension manifest.
 "Opening" this window in ActionScript results in the host application receiving a new_stage event.
 The host application then creates a window and APE stage with the properties passed on in the event.
 Once the window is created, APE attaches the contents of the ActionScript window to the newly created APE stage.
 The ActionScript window contains an instance of the AS3 class SWFLoader which loads the extension SWF.
 
 \param[in] inExtensionID the extension to be loaded, previously registered by PlugPlug.
 \return a success or failure code.  If the return indicates an error, then PlugPlug is signalling the host that the load will fail, and the host application must \e not attempt it.  (This may happen, for example, if a user tries to load more concurrent extensions than the host supports.)  When an error occurs, PlugPlug may attempt to use scripting to give the user feedback about the problem.
 */
typedef PlugPlugErrorCode (*PlugPlugLoadExtensionFn)(const char* inExtensionID);


/*!
 \brief Tell PlugPlug to prepare to unload an extension.
 
 When the Housing Plug-in wants to tear down a window that has an extension running in it, it must first invoke this API to notify PlugPlug so that PlugPlug can prepare to stop execution of the extension (perhaps by destroying the associated script engine).
 \param[in] inExtensionID the extension to be stopped.
 \return a success or failure code.  If the return indicates an error, then PlugPlug is signalling the host that the unload will likely produce an error of some kind.  The host application is still free to tear the window down.  In such cases, PlugPlug may attempt to use scripting to warn the user about the problem.
 */
typedef PlugPlugErrorCode (*PlugPlugUnloadExtensionFn)(const char* inExtensionID);



/**
 * @brief Adds the given eventListener to the list of listener for the given type.
 *
 * @param type The type of events to register for. Must not be NULL.
 * @param eventListener The event listener to add.
 * @param context A user specific context pointer or NULL.
 * @return The error code for this operation.
 *
 * If the eventListener is registered multiple times it will be notified multiple times.
 * Does nothing if eventListener is NULL.
 *
 * @since 2.0
 **/
typedef csxs::event::EventErrorCode (*PlugPlugAddEventListenerFn)(const char* type, 
																  const csxs::event::EventListenerFn eventListener, 
																  void* const context);

/**
 * @brief Removes the given eventListener from the list of listener for the given type.
 *
 * @param type The type of events to register for. Must not be NULL.
 * @param eventListener The event listener to remove.
 * @param context The user specific context pointer the event listener was registered with or NULL.
 * @return The error code for this operation. 
 *
 * If the eventListener was registered multiple times all entries will be removed.
 * Does nothing if eventListener is NULL.
 *
 * @since 2.0
 **/			
typedef csxs::event::EventErrorCode (*PlugPlugRemoveEventListenerFn)(const char* type, 
																	 const csxs::event::EventListenerFn, 
																	 void* const context);

/**
 * @brief Dispatches the given event. 
 *
 * @param The event to dispatch.
 * @return The error code for this operation. 
 *
 * This method will notify all event listeners which have registered for the type of the
 * event plus all event listeners which have registered for all events. The order in 
 * which the listeners are notified is undeterministic.
 * If an exception is thrown by any of the notified event listener it will be silently
 * caught and ignored.
 *
 * @since 2.0
 **/
typedef csxs::event::EventErrorCode (*PlugPlugDispatchEventFn)(const csxs::event::Event* const event);


//-----------------------------------------------------------------------------
// wraper
//-----------------------------------------------------------------------------

class SDKPlugPlug
{
public:
	SDKPlugPlug();
	~SDKPlugPlug();

	AIErr Load(AIFoldersSuite* sAIFolders);
	AIErr Unload();

	PlugPlugErrorCode LoadExtension(const char* inExtensionID);
	PlugPlugErrorCode UnloadExtension(const char* inExtensionID);

	//Adds the given eventListener to the list of listener for the given type.
	csxs::event::EventErrorCode AddEventListener(const char* type, 
													const csxs::event::EventListenerFn eventListener, 
													void* const context);
	//Removes the given eventListener from the list of listener for the given type.
	csxs::event::EventErrorCode RemoveEventListener(const char* type, 
													const csxs::event::EventListenerFn, 
													void* const context);
	//Dispatches the given event.
	csxs::event::EventErrorCode DispatchEvent(const csxs::event::Event* const event);

private:

	bool isPlugPlugLoaded();

private:

#ifdef WIN_ENV
	HMODULE fhModule;
#else
	CFBundleRef fhModule;
#endif

	PlugPlugLoadExtensionFn			pFnLoadExtension;
	PlugPlugUnloadExtensionFn		pFnUnloadExtension;
	PlugPlugAddEventListenerFn		pFnAddEventListener;
	PlugPlugRemoveEventListenerFn	pFnRemoveEventListener;
	PlugPlugDispatchEventFn			pFnDispatchEvent;
};

#endif // SDKPlugPlug.h
