#ifndef _AICSXSExtension_H_
#define _AICSXSExtension_H_
//========================================================================================
//  
//  ADOBE CONFIDENTIAL
// 
//	Owner: 
//  
//  Author: 
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 2015 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIHeaderBegin.h"

/** @file AICSXSExtension.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAICSXSExtensionSuite			"AI CSXS Extension Suite"
#define kAICSXSExtensionSuiteVersion	AIAPI_VERSION(4)
#define kAICSXSExtensionVersion		kAICSXSExtensionSuiteVersion

#define kAICSXSExtensionUnloadNotifier	"Extension Unloaded Notifier"

#define kAICSXSExtensionLoadNotifier	"Extension Loaded Notifier"

#define kAICSXSPanelVisibilityChangeNotifier "Extension Panel Visibility Changed Notifier"
/**
	Constants for reporting the status of Creative Suite extensions.
	See \c #AICSXSExtensionSuite::GetExtensionState().
*/
enum AICSXSExtensionState
{
	/** Extension is not registered in Illustrator. */
	kAICSXSExtensionNotRegisteredState,
	/** Extension is registered in Illustrator and ready to load. */
	kAICSXSExtensionRegisteredState,
	/** Extension is loaded. */
	kAICSXSExtensionLoadedState,
	/** Extension is loaded and Visible , valid for Panel and Dashboard Extension as of AI 19.2. */
	kAICSXSExtensionLoadedVisibleState,
	/** Extension is loaded but inVisible , valid for Panel and Dashboard Extension as of AI 19.2. */
	kAICSXSExtensionLoadedInvisibleState,
	/** Extension is unloaded. */
	kAICSXSExtensionUnLoadedState,
	/** Internal use  */
	kCSXSExtensionMaximumState      = 0xffff

};

typedef struct AICSXSExtensionNotifierMsg
{
	AICSXSExtensionState state;
	const char*			 extensionId;
}AICSXSExtensionNotifierMsg;

/*******************************************************************************
**
**	Suite
**
**/

/** @ingroup Suites
	This suite provides access to information about the status of Creative Suite
	extensions that might be loaded into Illustrator.

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICSXSExtensionSuite and \c #kAICSXSExtensionVersion.
*/
typedef struct {

	/** Retrieves the current registration and load state of an extension.
	@param extensionId [in] The unique identifier of the extension.
	@param state [out] A buffer in which to return the current state, an \c #AICSXSExtensionState constant value.
	*/
	AIAPI AIErr (*GetExtensionState) (const char* extensionId, ai::int32& state);

	/** Reports whether an extension's main window is currently visible in the UI.
	@param extensionId [in] The unique identifier of the extension.
	@param isVisible [out] True if the extension's main window appears in the UI, false otherwise.
	*/
	AIAPI AIErr (*IsPrimaryStageVisible) (const char* extensionId, AIBoolean& isVisible);

	/** Launches extension of specified extension ID 
	@param extensionId [in] The unique identifier of the extension.
	*/
	AIAPI AIErr (*LaunchExtension) (const char* extensionId);

	/** Sends Provided Event To Extension with the provided data
	@param extensionId [in] The unique identifier of the extension.
	@param eventID [in] The unique identifier of the event.
	@param appId [in] The unique identifier of Application.
	@param data [in] data is optional. it can be used to send some data to extension along with the event
	*/
	AIAPI AIErr (*SendEventToExtension) (const char* extensionId, const char* eventID, const char* appId, const char* data);

	/** Sets the visibility of a panel.
	NOTE: This suite function does not "launch" any extension. It simply changes visibility state of container of the input extension
	If you need to know the "launch" status of an extension use GetExtensionState.
	@param extensionId [in] The unique identifier of the extension.
	@param show [in] weather to show/hide the extension panel.
	**/
	AIAPI AIErr (*ShowExtension) (const char* extensionId, bool show);

	/** Unloads extension of specified extension ID
	@param extensionId [in] The unique identifier of the extension.
	*/
	AIAPI AIErr(*UnloadExtension) (const char* extensionId);
} AICSXSExtensionSuite;

#include "AIHeaderEnd.h"

#endif //_AICSXSExtension_H_
