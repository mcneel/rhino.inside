#ifndef __AIWorkspace__
#define __AIWorkspace__

/*
 *        Name:	AIWorkspace.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Workspace Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/
#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __SPAccess__
#include "SPAccess.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIWorkspace.h */
/*******************************************************************************
 **
 **	Constants
 **
 **/

/** @ingroup Constants */
#define kAIWorkspaceSuite					"AI Workspace Suite"
#define kAIWorkspaceSuiteVersion3			AIAPI_VERSION(3)
#define kAIWorkspaceSuiteVersion			kAIWorkspaceSuiteVersion3
#define kAIWorkspaceVersion					kAIWorkspaceSuiteVersion

/** Maximum number of bytes in a workspace name, including null terminator. */
#define kMaxWSStringLength			(64)


/** @ingroup Notifiers
    Sent as a last step when the workspace has been restored. */
#define kAIWorkspaceRestoreFinishNotifier   "AI Workspace Restore Finish Notifier"

/** @ingroup Callers
	Sent to plug-ins from the workspace manager.  See \c #AIWorkspaceSuite. */
#define kAIWorkspaceCaller					"Workspace Manager"

/** @ingroup Selectors
	Sent to plug-ins that own tab palettes to request save of
	the current dialog's specific configuration (show/hide option, list view).
	To save a configuration value for the current workspace,
	use the appropriate \c Set<type>Value() function from the \c #AIWorkspaceSuite,
	retrieving the workspace object from the message:

<code>
sAIWorkspace->Set<type>Value(message->workspace, palette_name, description_of_value, value).
</code>

	Each palette's location, visibility, dock code, dock group, and size of the 
	current workspace are saved by the Workspaces plug-in.
*/
#define kAIWSWriteSelector					"Write Workspace"
/** @ingroup Selectors
	Sent to plug-ins that own tab palettes to request restore of
	the current dialog's specific configuration.
	To retrieve a configuration value from the current workspace,
	use the appropriate \c Get<type>Value() function from the \c #AIWorkspaceSuite,
	retrieving the workspace object from the message:

<code>
sAIWorkspace->Get<type>Value(message->workspace, palette_name, description_of_value, &value).
</code>

	Each palette's location, visibility, dock code, dock group, and size of the 
	current workspace are restored by the Workspaces plug-in.
*/
#define kAIWSRestoreSelector				"Restore Workspace"
/** @ingroup Selectors
	Sent to plug-ins that own tab palettes to reset to hard-coded default values
	defined in the plug-in and in \c AIPaletteDefaults.h.
	You must configure the palette layout to the initial default.
	In addition to a palette's specific configuration (show/hide option, list view),
	resets the values of a palette's location, visibility, dock code, dock group, and size.
*/
#define kAIWSDefaultSelector				"Default Workspace"

/** @ingroup Errors
	Workspace name is longer than \c #kMaxWSStringLength.
	See \c #AIWorkspaceSuite. */
#define kWorkspaceNameTooLongErr			'WSNL'

/** Not used */
enum AIWorkspaceDefaultValue {
 	kAIWSDefaultPreset = 1,
 	kAIWSAICSPreset
};

/*******************************************************************************
 **
 **	Types
 **
 **/
/** Opaque reference to a workspace. Access with \c #AIWorkspaceSuite. */
typedef struct _AIWorkspace*			AIWorkspaceHandle;

/** Message sent with workspace selectors. See \c #AIWorkspaceSuite. */
typedef struct {
	/** Message data. */
	SPMessageData d;
	/** The workspace receiving the message. */
	AIWorkspaceHandle workspace;
	/** The name of the tab palette. If you install multiple palettes, compare to the
		saved name to determine which one made the request. */
	const char *dialogName;
	/** True when \c #kAIWSDefaultSelector message was sent because a palette
		was not found in the current workspace, and an exception was raised. Your
		handler can restore the palette layout to the default. */
	AIBoolean restore;
	/** Not used. */
	AIWorkspaceDefaultValue flag;
} AIWorkspaceMessage;

/*******************************************************************************
 **
 **	Suites
 **
 **/

/** @ingroup Suites
	This suite allows you to access \e workspaces.
	A workspace is an object in which to store the screen layout of floating
	tabbed palettes, such as the Tool and Control palettes.
	The workspace can store current size, visibility, physical location, docking information,
	and any other palette-specific options (such as the list view option in the brushes
	palette).

	These functions retrieve and set values in the workspace object, according
	to the data type.

 	The workspace does not control persistence, which governs the behavior
 	at startup. This is determined in the individual libraries (Brush, Graphic
	Style, Swatch, and Symbol).

   	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIWorkspaceSuite and \c #kAIWorkspaceVersion.
*/

typedef struct {

	/** Retrieves an integer value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetIntegerValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, int *value);

	/** Sets an integer value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetIntegerValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, ai::int32 value);

	/** Retrieves a real-number value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetRealValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIReal *value);

	/** Sets a real-number value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetRealValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIReal value);

	/** Retrieves a boolean value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetBooleanValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIBoolean *value);

	/** Sets a boolean value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetBooleanValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIBoolean value);

	/** Retrieves a string value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetStringValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, char *value, ai::int32 length);

	/** Sets a string value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetStringValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, const char *value);

	/** Retrieves a point value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetPointValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIPoint *value);

	/** Sets a point value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetPointValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIPoint value);

	/** Retrieves a real-number point value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetRealPointValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIRealPoint *value);

	/** Sets a real-number point value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetRealPointValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIRealPoint value);

	/** Retrieves a rectangle value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetRectValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIRect *value);

	/** Sets a rectangle value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetRectValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIRect value);

	/** Retrieves a real-number rectangle value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetRealRectValue)(AIWorkspaceHandle collectioRef, const char *prefix, const char *suffix, AIRealRect *value);

 	/** Sets a real-number rectangle value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetRealRectValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIRealRect value);

	/** Retrieves a transformation matrix value from a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetRealMatrixValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIRealMatrix *value);

	/** Sets a transformation matrix value for a workspace.
			@param workspace The workspace object.
			@param prefix The palette name, as returned by <code>sADMDialog->GetDialogName(fDialog)</code>.
			@param suffix A configuration item in the plug-in, such as "ListView" or "ShowOption".
			@param value The new value.
		*/
	AIAPI AIErr (*SetRealMatrixValue)(AIWorkspaceHandle workspace, const char *prefix, const char *suffix, AIRealMatrix value);

} AIWorkspaceSuite;



#include "AIHeaderEnd.h"


#endif // __AIWorkspace__
