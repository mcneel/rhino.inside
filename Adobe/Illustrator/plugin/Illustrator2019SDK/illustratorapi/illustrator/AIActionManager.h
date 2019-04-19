#ifndef __AIActionManager_h__
#define __AIActionManager_h__

/*
 *        Name:	AIActionManager.h
 *   $Revision: 22 $
 *      Author:	Grace Ge
 *        Date:	10/14/97
 *     Purpose:	AI Action Manager Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include "AITypes.h"
#include "SPPlugs.h"
#include "AIUnicodeString.h"

#include "AIHeaderBegin.h"

/** @file AIActionManager.h */

/*
 * Constants
 */

#define kAIActionManagerSuite			"AI Action Manager Suite"
#define kAIActionManagerSuiteVersion5	AIAPI_VERSION(5)
#define kAIActionManagerSuiteVersion	kAIActionManagerSuiteVersion5
#define kAIActionManagerVersion			kAIActionManagerSuiteVersion

/** @ingroup Notifiers
	Sent when an action event has completed execution.
 */
#define kAIActionManagerPlayActionEventDoneNotifier	"AI Action Manager PlayActionEvent Done Notifier"
#define kAIActionActualExecutionFinishedNotifier "AI Action Actual Execution Finished Notifier"
/*
 *	Types
 */

/** Identifies the data type of an action parameter. */
typedef ai::uint32	ActionParamTypeID;

/** Allowed values for \c ::ActionParamTypeID */
enum {
	/** integer */
	actionTypeInteger = 'long',
	/** real number */
	actionTypeReal =	'real',
	 /** boolean */
	actionTypeBoolean =	'bool',
	/** enumeration */
	actionTypeEnum =	'enum',
	/** string */
	actionTypeString =	'strn',
	 /** real number with associated unit */
	actionTypeUnitReal ='utrl',
	/** user-defined data */
	actionTypeRawData =	'rwdt',
	/** null */
	actionTypeNull =	'null'
};

/** Identifies units for some numeric parameters. Units are shown when type is \c actionTypeUnitReal.
 */
typedef ai::uint32	ActionParamUnitID;

#ifndef unitNone
/** Allowed values for \c ::ActionParamUnitID  */
enum {
	// The Photoshop APIs also define these constants. If a plug-in includes both
	// the Photoshop APIs and the Illustrator APIs then there would be compilation
	// problems. We let the Photoshop definitions win.

	/** unit value - coerced */
	unitNone =		'#Nne',
	/** unit value - base 72ppi */
	unitDistance =	'#Rlt',
	/** unit value - base degrees */
	unitAngle =		'#Ang',
	/** unit value - base per inch */
	unitDensity =	'#Rsl',
	/** tagged unit value, document points */
	unitPoints =	'#Pxl',
	/** tagged unit value, percentage */
	unitPercent =	'#Prc'

};
#endif

/** Identifies a unique key associated with a parameter block */
typedef ai::uint32	ActionParamKeyID;

/** A reference to a Type Parameter Block (TPB) */
typedef struct ActionParamType *AIActionParamTypeRef;

/** A reference to a Value Parameter Block (VPB) */
typedef struct ActionParamValue *AIActionParamValueRef;

/** User-defined data. This is cast after it has been defined. */
typedef void *AIActionUserData;

/** Callback procedure prototype. */
typedef ASErr (*AIActionCallbackProc)(AIActionParamValueRef parameter,
									 AIActionUserData userData,
									 AIBoolean showDialog);

/** Idle procedure prototype. */
typedef void (*AIActionIdleProc)(void);

/** Choices for whether a parameters dialog appears by default when an action is played back.
	This status is visually represented by a dialog icon to the left of the
	event name in the Actions palette. */
typedef enum _ActionDialogStatus
{ /** No dialog is defined for this action */
	kDialogNone,
	 /** Dialog appears on playback */
	kDialogOn,
	/** Internal, not used by 3rd-party plug-ins */
	kDialogPartialOn,
	/** Dialog does not appear on playback */
	kDialogOff
} ActionDialogStatus;

/** Values that control whether values are shown in the Actions palette. */
typedef enum _ActionValueVisibility
{ /** shown or hidden according to parameter data type */
	kDependOnParamType = -1,
	/** hidden */
	kHideInPalette,
	/** shown */
	kShowInPalette
} ActionValueVisibility;


/** @ingroup Callers
	Caller id for messages sent to plug-ins from the action manager. See \c #AIActionManagerSuite. */
#define kActionCaller	"Action Manager"
/** @ingroup Selectors
	Message selector sent when requesting a plug-in to play an action. In this case
	the message is a \c ::DoActionMessage. */
#define kDoActionSelector	"Do Action"

/** A plug-in receives this message with the request to execute an action. The
	message caller is \c ::kActionCaller and the selector is \c ::kDoActionSelector. */
typedef struct
{
	 /** Message data */
	SPMessageData d;
	 /** Plug-in defined data */
	AIActionUserData userData;
	/** When true, the plug-in should show the parameters dialog. */
	AIBoolean showDialog;
	 /** VPB containing parameter values previously recorded or set by another plug-in. */
	AIActionParamValueRef param;
} DoActionMessage;


/**	@ingroup Suites

	The Action Manager suite allows you to access the internal scripting system built into
	Adobe Illustrator. The Action Manager allows you to record and play actions which
	execute Illustrator menu commands or plug-in commands. The Action Manager suite allows
	your plug-in to play actions or register itself to the Illustrator application to enable
	your plug-in to be scriptable via the Actions palette.

	An action event is an execution of an Illustrator command. An action event
	can originate from the Illustrator application or a plug-in. It is normally, but
	not limited to, an evaluation or modification to Illustrator artwork. Adobe
	Illustrator’s Action Manager dispatches action events.

	In order for your plug-in’s action events to be recorded or played back you
	must register them with the Action Manager and specify the parameters
	associated with your action event. In addition to registering you actions,
	your plug-in must respond to the Action Manager when it tells you to play
	your plug-in’s action event.

	The Action Manager suite is exported by a plug-in. It may be disabled by removing
	the Action Manager plug-in. Because of this, during startup you must always check for
	the presence of the AIActionManager suite pointer before calling any Action Manager
	functions.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIActionManagerSuite and \c #kAIActionManagerVersion.
 */

struct AIActionManagerSuite
{
	/**	This function registers a plug-in’s action event with the Adobe Illustrator application.
	Call it during the startup procedure of your plug-in. This is necessary for your plug-in event
	to be recognized by the Actions palette. It is the first step in making your plug-in into an action.

	The Action Manager suite is exported by a plug-in. It may be disabled by removing the Action Manager plug-in.
	Because of this, during startup you must always check for the presence of the AIActionManager suite pointer
	before calling any Action Manager functions.

	If your plug-in registers an action event at startup, you are responsible for recording your action event
	and any associated parameters whenever the user is in Record mode.See \c #InRecordMode() and \c #RecordActionEvent().

		@param eventName A string that identifies your plug-in event internally; not localized.
		Must be unique among plug-ins. Typically the name of your plug-in, preceded by your
		company name; for example, "adobe_saveDocumentAs".

		@param localizedName A string that is shown in the Adobe Illustrator Actions palette;
		will be localized.

		@param callback Not used, pass a \c null value.

		@param plugin The plug-in registering the event (usually <code>message.d->self</code>).

		@param userData A pointer to private data associated with the action event.
		Must be allocated by your  plug-in (using \c SPBlocks.h) at startup.
		This is passed back to your code in \c GetActionEventUserData and in the \c DoActionMessage.

		@param parameters A reference to a type parameter block (TPB).
		A TPB contains keys that describe the parameter block of your plug-in.
		To provide this value:
			\li Create an \c AIActionParamTypeRef using \c #AINewActionParamType().
			\li Fill it with keys that describe your parameter block using \c #AIActionSetTypeKey().
			\li Pass it to this function.
			\li Destroy it using \c #AIDeleteActionParamType(). */
	ASErr ASAPI (*RegisterActionEvent)(const char *eventName, const char *localizedName,
		ai::int32 version, ai::int32 flag,
									   AIActionCallbackProc callback,
									   SPPluginRef plugin,
									   AIActionUserData userData,
									   AIActionParamTypeRef parameters);


	/**	Reports whether a plug-in has been registered as an action event.
		(Note that this function returns a boolean value, not an error code.)

		@param eventName The name with which the action was registered.
		@return True if the action was registered, false otherwise.
		@see  \c #RegisterActionEvent()
		*/
	AIBoolean ASAPI (*IsActionEventRegistered)(const char *eventName);

	/**	Gets the localized name associated with a registered action event
		(the string that appears in the Actions palette).

		@param eventName [in] The name with which the action was registered.
		@param localizedName [out] A character buffer in which to return the localized name.
		@see  \c #RegisterActionEvent()
		*/
	ASErr ASAPI (*GetActionEventLocalizedName)(const char *eventName, char *localizedName);
	/**	Gets the version number associated with a registered action event.

		@param eventName [in] The name with which the action was registered.
		@param version [out] A buffer in which to return the version number.
		@see  \c #RegisterActionEvent()
		*/
	ASErr ASAPI (*GetActionEventVersion)(const char *eventName, ai::int32 *version);
	/**	Currently unused */
	ASErr ASAPI (*GetActionEventFlag)(const char *eventName, ai::int32 *flag);
	/**	Gets the callback procedure associated with a registered action event.

		@param eventName [in] The name with which the action was registered.
		@param version [out] A buffer in which to return the callback procedure.
		@see  \c #RegisterActionEvent()
		*/
	ASErr ASAPI (*GetActionEventCallbackProc)(const char *eventName, AIActionCallbackProc *callback);
	/**	Gets the plug-in associated with a registered action event--that is, the plug-in that executes the event.

		@param eventName [in] The name with which the action was registered.
		@param version [out] A buffer in which to return the plug-in reference..
		@see  \c #RegisterActionEvent()
		*/
	ASErr ASAPI (*GetActionEventPluginRef)(const char *eventName, SPPluginRef *pluginRef);
	/**	Gets the user data associated with a registered action event.

		@param eventName [in] The name with which the action was registered.
		@param version [out] A buffer in which to return the user data.
		@see  \c #RegisterActionEvent()
		*/
	ASErr ASAPI (*GetActionEventUserData)(const char *eventName, AIActionUserData *userData);
	/**	Sets the user data associated with a registered action event.

		@param eventName [in] The name with which the action was registered.
		@param version [in] The new user data, in the structure allocated at registration.
		@see  \c #RegisterActionEvent()
	*/
	ASErr ASAPI (*SetActionEventUserData)(const char *eventName, AIActionUserData userData);
	/**	Gets the type parameter block (TPB) associated with a registered action event.

		@param eventName [in] The name with which the action was registered.
		@param version [out] A buffer in which to return the TPB.
		@see  \c #RegisterActionEvent()
		*/
	ASErr ASAPI (*GetActionEventParamType)(const char *eventName, AIActionParamTypeRef *param);

	/** Calls the action idle procedure, as set by \c #SetActionIdleProc(). */
	ASErr ASAPI (*Idle)(void);
	/** Specifies the action idle procedure for this action.

		@param idleProc The procedure to call when the action is idle.
		Define the function using this prototype:<br>
			<code>typedef void AIActionIdleProc (void);</code>
		*/
	ASErr ASAPI (*SetActionIdleProc)(AIActionIdleProc idleProc);
	/** Gets the current idle procedure for this action.

		@param idleProc [out] A buffer in which to return the procedure.
		*/
	ASErr ASAPI (*GetActionIdleProc)(AIActionIdleProc *idleProc);

	/** Creates a type parameter block (TPB) for an action, which describes the data types
		of your plug-in’s parameters.

		In order to register as an action event, your plug-in must create an \c AIActionParamTypeRef
		using this function, then fill it with keys that describe your parameter block
		using \c #AIActionSetTypeKey().
		Pass the filled TPB to \c #RegisterActionEvent() when registering the event.
		Destroy it after registration, using \c #AIDeleteActionParamType().
		You do not need to keep your reference; Illustrator keeps a copy of it,
		and you can retrieve it using \c #GetActionEventParamType().

		The TPB does not contain actual values, just type descriptors.
		The keys that you add to the parameter block represent data types,
		typically for information that is gathered when your plug-in presents
		a modal dialog to the user. The values are kept in a value parameter block
		(VPB), created with \c #AINewActionParamValue().

		@param param [out] A buffer in which to return the new type parameter block (TPB).
		*/
	ASErr ASAPI (*AINewActionParamType)(AIActionParamTypeRef *param);
	/** Deletes a type parameter block (TPB). You do not need to keep your reference;
		Illustrator keeps a copy of it, and you can retrieve it using \c #GetActionEventParamType().

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType().
		@see \c #AIActionSetTypeKey(), \c #RegisterActionEvent()
		*/
	ASErr ASAPI (*AIDeleteActionParamType)(AIActionParamTypeRef param);

	/** Retrieves a type key from a type parameter block (TPB).

		The returned key is, by convention, a 4-character long value that describes
		the parameter. For example, in the Tutorial the keys for the "corner" and "size"
		parameters are ’crnr’ and ’size’. The key for the parameter type in the TPB matches
		the key for its value in the VPB: see \c #AIActionGetValueKey().

		\li To check that the TPB contains a specific key, use \c #AIActionHasTypeKey().
		\li To iterate through all of the keys, get the number of keys with \c #AIActionGetTypeCount().
		\li To set a key type, use \c #AIActionSetTypeKey().

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType()
		and returned by \c #GetActionEventParamType().
		@param index [in] The position index of the desired parameter type key.
		@param key [out] A buffer in which to return the type key.
		*/
	ASErr ASAPI (*AIActionGetTypeKey)(AIActionParamTypeRef param, ai::uint32 index, ActionParamKeyID *key);

	/** Determines whether a value parameter block (VPB) contains a particular key.

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType()
				and returned by \c #GetActionEventParamType().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  hasKey [out] A buffer in which to return the result, true if the key is contained in the VPB,
			false otherwise.
		*/
	ASErr ASAPI (*AIActionHasTypeKey)(AIActionParamTypeRef param, ActionParamKeyID key, AIBoolean *hasKey);

	/** Retrieves the number of keys in a type parameter block (TPB).
		Use with \c #AIActionGetTypeKey() to iterate through keys.

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType()
				and returned by \c #GetActionEventParamType().
		@param count [out] A buffer in which to return the number of keys.
		*/
	ASErr ASAPI (*AIActionGetTypeCount)(AIActionParamTypeRef param, ai::uint32 *count);

	/** Associates a type key with a type parameter block (TPB). Creates a new key, or sets
	values for an existing key.

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType()
				and returned by \c #GetActionEventParamType().
		@param key [in] The parameter type key, by convention a 4-character \c long value that
			describes the parameter. For example, in the Tutorial the keys for the
			"corner" and "size" parameters are ’crnr’ and ’size’. See also \c #AIActionGetTypeKey().
		@param name [in] The localizable name of the parameter, which appears in the Actions palette.
		@param type [in] The data type of the key. An \c ::ActionParamTypeID value.
		@param show [in] When true, the parameter is shown in the Actions palette.

	 */
	ASErr ASAPI (*AIActionSetTypeKey)(AIActionParamTypeRef param, ActionParamKeyID key, const char* name, ActionParamTypeID type, AIBoolean show);

	/** Retrieves the display name of an event parameter.

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType()
				and returned by \c #GetActionEventParamType().
		@param key [in] The parameter type key, a 4-character \c long, See \c #AIActionGetTypeKey().
		@param value [out] A buffer in which to return the localizable name of the parameter,
			which appears in the Actions palette. See \c #AIActionSetTypeKey().
		*/
	ASErr ASAPI (*AIActionGetName)(AIActionParamTypeRef param, ActionParamKeyID key, char* value);

	/** Retrieves the data type of an event parameter.

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType()
				and returned by \c #GetActionEventParamType().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetTypeKey().
		@param value [out] A buffer in which to return the data type of the key. An \c ::ActionParamTypeID value.
		*/
	ASErr ASAPI (*AIActionGetType)(AIActionParamTypeRef param, ActionParamKeyID key, ActionParamTypeID* value);

	/** Reports whether a specific event parameter is displayed in the Actions palette.
		(Note that the function returns a boolean value, not an error code.)

		@param param [in] The type parameter block (TPB), as created by \c #AINewActionParamType()
				and returned by \c #GetActionEventParamType().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetTypeKey().
		@return True if the show flag is on, false otherwise.
		*/
	AIBoolean ASAPI (*AIActionTypeIsShow)(AIActionParamTypeRef param, ActionParamKeyID key);

	/** Not used for third-party plug-ins  */
	ASErr ASAPI (*AcquirePalette)(void);
	/** Not used for third-party plug-ins   */
	ASErr ASAPI (*ReleasePalette)(void);

	/** Records your plug-in’s action event and displays it in the Actions palette
		with its parameter list.

		You should call this only when you have determined that the user is in Record mode,
		by calling \c #InRecordMode(). You must create the VPB and set its values,
		use it to record the action, then destroy the VPB. For example:<br>
		@code
// If in record mode, record the event
if (sAIActionManager && sAIActionManager->InRecordMode()) {
// create a VPB using AINewActionParamValue()
// load the VPB with values, according to the parameter types
// record the action event using RecordActionEvent()
// delete the VPB using AIDeleteActionParamValue()
}
		@endcode

		@param eventName The name with which the action was registered. See \c #RegisterActionEvent().
		@param dialogStatus Whether a dialog appears by default when the action is played back.
			This status is visually represented by a dialog icon to the left of the
			event name in the Actions palette.
		@param parameters The event’s value parameter block (VPB), as created by
			\c #AINewActionParamValue(). This structure contains the parameter values that
			were used during the action event. Typically, these are the values entered by
			the user in the parameter dialog box. If your action event does not have parameters,
			pass \c null.
	 	 */
	ASErr ASAPI (*RecordActionEvent)(const char *eventName, ActionDialogStatus dialogStatus, AIActionParamValueRef parameters);

	/** Plays back a recorded action event.

		You can use this to play back any registered action event, not just the one for
		this plug-in. The event names and their parameter types are documented in \c actions folder
		in the SDK installation.

		For example, the following executes copy, new document, and paste action events:
		@code
sAIActionManager->PlayActionEvent("adobe_copy", kDialogNone, NULL);
sAIActionManager->PlayActionEvent("adobe_newDocument", kDialogNone, NULL);
sAIActionManager->PlayActionEvent("adobe_paste", kDialogNone, NULL);
		@endcode

		@param eventName The name with which the action was registered. See \c #RegisterActionEvent().
		@param dialogStatus Whether a dialog appears by default when the action is played back.
			This status is visually represented by a dialog icon to the left of the
			event name in the Actions palette. See \c ::_ActionDialogStatus.
		@param parameters The event’s value parameter block (VPB), as created by
			\c #AINewActionParamValue(). This structure contains the parameter values that
			were used during the action event. Typically, these are the values entered by
			the user in the parameter dialog box. If your action event does not have parameters,
			pass \c null.
		*/
	ASErr ASAPI (*PlayActionEvent)(const char *eventName, ActionDialogStatus dialogStatus, AIActionParamValueRef parameters);

	/** Reports whether  the user is currently in Record mode. (Note that the function
		returns a boolean value, not an error code.)

		When a new action is first created or whenever the record button is pressed in the
		Actions palette, the user is in Record mode, and all actions are recorded into the
		Actions palette.

		If your plug-in registers an action event at startup, you are responsible for
		recording your action event and any associated parameters whenever the user is
		in Record mode. See \c #RecordActionEvent().

		This function is often used within a conditional statement during the normal
		execution of a plug-in. For example:
		@code
// If in record mode, record the event
if (sAIActionManager && sAIActionManager->InRecordMode()) {
// create a VPB
// load the VPB with values
// record the action event
// delete the VPB
}
		@endcode

		@return True if the user is in record mode, false otherwise.
	*/
	AIBoolean ASAPI (*InRecordMode)(void);

	/** Not used for third-party plug-ins  */
	AIBoolean ASAPI (*InInsertMenuItemState)(void);

	/** Not used for third-party plug-ins  */
	ASErr ASAPI (*ActivateInsertMennuItemDialog)(void);

	/**  Not used for third-party plug-ins */
	ASErr ASAPI (*SetCurrentCommandLocalizedName)(const char *localizedName);

	/** Not used for third-party plug-ins  */
	ASErr ASAPI (*DoFunctionKey)(ai::int32 fkey, ai::uint32 modifier);

	/** Creates a value parameter block (VPB) structure.

		The VPB contains a set of event parameter values, whose types are determined
		by the type parameter block (TPB) with which the event is registered.
		See \c #RegisterActionEvent() and \c #AINewActionParamValue().

		In order to record an action event, your plug-in must create an
		#AIActionParamValueRef using this function, then fill it with key/value pairs
		that contain values of the correct type, using the appropriate \c AIActionSetXx function.
		For example, to set an integer value, use \c #AIActionSetInteger().

		Pass the filled VPB to \c #RecordActionEvent() when recording the event.
		Destroy it after recording, using \c #AIDeleteActionParamValue().
		You do not need to keep your reference; Illustrator keeps a copy of it,
		and you can retrieve it using \c #AIActionGetValueKey().

		@param param A buffer in which to return the new value parameter block (VPB).
		*/
	ASErr ASAPI (*AINewActionParamValue)(AIActionParamValueRef *param);

	/** Deletes a value parameter block (VPB). You do not need to keep your reference
		after recording or playing back an action with its parameter value set.
			@param param The value parameter block (VPB) as returned by \c #AINewActionParamValue().
			@see \c #RecordActionEvent(), \c #PlayActionEvent()
		*/
	ASErr ASAPI (*AIDeleteActionParamValue)(AIActionParamValueRef param);

	/** Retrieves a value key from a value parameter block (VPB).

		The returned key is, by convention, a 4-character long value that describes
		the parameter. For example, in the Tutorial the keys for the "corner" and "size"
		parameters are ’crnr’ and ’size’. The key for the parameter value in the VPB
		matches the key for its type in the TPB. See \c #AIActionGetTypeKey().

		\li To check that the VPB contains a specific key, use \c #AIActionHasValueKey().
		\li To iterate through all of the keys, get the number of keys with
		\c #AIActionGetValueCount().
  		\li To extract or set the value for a specific key, use the accessor function appropriate
		 to its data type. For example, to get an integer value, use \c #AIActionGetInteger(),
		 and to set it, use \c #AIActionSetInteger().

			@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
			@param index [in] The position index of the desired parameter value key.
			@param key [out] A buffer in which to return the value key.
		*/
	ASErr ASAPI (*AIActionGetValueKey)(AIActionParamValueRef param, ai::uint32 index, ActionParamKeyID *key);

	/** Determines whether a VPB contains a particular key.

			@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
			@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
			@param  hasKey [out] A buffer in which to return the result, true if the key is contained in the VPB,
				false otherwise.
		*/
	ASErr ASAPI (*AIActionHasValueKey)(AIActionParamValueRef param, ActionParamKeyID key, AIBoolean *hasKey);

	/** Retrieves the number of keys in a value parameter block (VPB).
		Use with \c #AIActionGetValueKey() to iterate through keys

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param count [out] A buffer in which to return the number of keys.
		*/
	ASErr ASAPI (*AIActionGetValueCount)(AIActionParamValueRef param, ai::uint32 *count);

	/* Retrieves the data type of the value associated with a key.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [out] A buffer in which to return the data type. An \c ::ActionParamTypeID value.
		*/
	ASErr ASAPI (*AIActionGetValueType)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamTypeID *type);

	/** Retrieves the integer value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [out] A buffer in which to return the value.
		*/
	ASErr ASAPI (*AIActionGetInteger)(AIActionParamValueRef param, ActionParamKeyID key, ai::int32* value);
	/** Sets the integer value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [in] The new value.
		*/
	ASErr ASAPI (*AIActionSetInteger)(AIActionParamValueRef param, ActionParamKeyID key, ai::int32 value);

	/** Retrieves the \c real value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [out] A buffer in which to return the value.
		*/
	ASErr ASAPI (*AIActionGetReal)(AIActionParamValueRef param, ActionParamKeyID key, AIReal* value);
	/** Sets the \c real value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [in] The new value.
		*/
	ASErr ASAPI (*AIActionSetReal)(AIActionParamValueRef param, ActionParamKeyID key, AIReal value);

	/** Retrieves the unit-real value associated with a particular key in a VPB. Unit-real values are
		displayed in the Actions palette with unit labels.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [out] A buffer in which to return the value.
		*/
	ASErr ASAPI (*AIActionGetUnitReal)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamUnitID* unit, AIReal* value);
	/** Sets the unit-real value associated with a particular key in a VPB.Unit-real values are
		displayed in the Actions palette with unit labels.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [in] The new value.
		*/
	ASErr ASAPI (*AIActionSetUnitReal)(AIActionParamValueRef param, ActionParamKeyID key, ActionParamUnitID unit, AIReal value);

	/** Retrieves the string value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [out] A buffer in which to return the value.
		*/
	ASErr ASAPI (*AIActionGetString)(AIActionParamValueRef param, ActionParamKeyID key, char* value);
	/** Sets the string value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [in] The new value.
		*/
	ASErr ASAPI (*AIActionSetString)(AIActionParamValueRef param, ActionParamKeyID key, const char* value);

	/** Retrieves the boolean value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [out] A buffer in which to return the value.
		*/
	ASErr ASAPI (*AIActionGetBoolean)(AIActionParamValueRef param, ActionParamKeyID key, AIBoolean* value);
	/** Sets the boolean value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [in] The new value.  */
	ASErr ASAPI (*AIActionSetBoolean)(AIActionParamValueRef param, ActionParamKeyID key, ASBoolean value);

	/** Retrieves the enumerated value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param name [in] The name of the enumeration, as shown in the Actions palette.
		@param  value [out] A buffer in which to return the value.
	 */
	ASErr ASAPI (*AIActionGetEnumerated)(AIActionParamValueRef param, ActionParamKeyID key,  char* name, ai::int32* value);
	/** Sets the enumerated value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param name [in] The name of the enumeration, as shown in the Actions palette.
		@param  value [in] The new value.
	 */
	ASErr ASAPI (*AIActionSetEnumerated)(AIActionParamValueRef param, ActionParamKeyID key,  const char* name, ai::int32 value);

	/** Sets the raw-data value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  size [in] The number of bytes in the new value.
		@param  value [in] The new value. You must allocate memory for the value.
	 */
	ASErr ASAPI (*AIActionSetRawDataBytes)(AIActionParamValueRef param, ActionParamKeyID key,  ai::uint32 size, const char* value);

	/** Retrieves the size of a raw-data value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  size [out] A buffer in which to return the number of bytes in the value.
		*/
	ASErr ASAPI (*AIActionGetRawDataSize)(AIActionParamValueRef param, ActionParamKeyID key,  ai::uint32* size);
	/** Retrieves the raw-data value associated with a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [out] A buffer in which to return the value. You must allocate memory for the value,
		using the size obtained with \c #AIActionGetRawDataSize().
		*/
	ASErr ASAPI (*AIActionGetRawData)(AIActionParamValueRef param, ActionParamKeyID key, char* value);

	/** Retrieves the current visibility state of a particular key in a VPB.(Not that this function returns
	a visibility value, not an error code.)

			@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
			@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
			@return The visibility state value; see \c ::ActionValueVisibility.
	 */
	ActionValueVisibility ASAPI (*AIActionValueGetVisibility)(AIActionParamValueRef param, ActionParamKeyID key);

	/** Sets the visibility state of a particular key in a VPB.

		@param param [in] The value parameter block (VPB), as created by \c #AINewActionParamValue().
		@param key [in] The parameter type key, a 4-character \c long. See \c #AIActionGetValueKey().
		@param  value [in] The new value, see \c ::ActionValueVisibility.
	 */
	ASErr ASAPI (*AIActionValueSetVisibility)(AIActionParamValueRef param, ActionParamKeyID key, ActionValueVisibility value);

	/** Not used for third-party plug-ins  */
	ASErr ASAPI (*UndoLastTransaction)();

	/** Not used for third-party plug-ins  */
	ASErr ASAPI (*RedoLastTransaction)();

	/** Not used for third-party plug-ins */
	ASErr ASAPI (*IgnoreRecording)(AIBoolean ignore);


	/** Registers an action using a Unicode name.
	For details, see \c #RegisterActionEvent().  */

	ASErr ASAPI (*RegisterActionEventUS)(const char *eventName, const ai::UnicodeString& localizedName,
									   ai::int32 version, ai::int32 flag,
									   AIActionCallbackProc callback,
									   SPPluginRef plugin,
									   AIActionUserData userData,
									   AIActionParamTypeRef parameters);

	/** Retrieves the localized name of an event as a Unicode string.
	For details, see \c #GetActionEventLocalizedName().  */
	ASErr ASAPI (*GetActionEventLocalizedNameUS)(const char *eventName, ai::UnicodeString& localizedName);

	/**  Associates a type key with a type parameter block (TPB), using Unicode strings.
	For details, see \c #AIActionSetTypeKey().  */
	ASErr ASAPI (*AIActionSetTypeKeyUS)(AIActionParamTypeRef param, ActionParamKeyID key, const ai::UnicodeString& name, ActionParamTypeID type, AIBoolean show);

	/** Retrieves the identifying name of an event as a Unicode string.
	For details, see \c #AIActionGetNameUS().  */
	ASErr ASAPI (*AIActionGetNameUS)(AIActionParamTypeRef param, ActionParamKeyID key, ai::UnicodeString& value);

	/** Sets the localized name of an event using a Unicode string.
	For details, see \c #SetCurrentCommandLocalizedName().  */
	ASErr ASAPI (*SetCurrentCommandLocalizedNameUS)(const ai::UnicodeString& localizedName);

	/** Retrieves the string value associated with a particular key in a VPB, as a Unicode string.
	For details, see \c #AIActionGetString().  */
	ASErr ASAPI (*AIActionGetStringUS)(AIActionParamValueRef param, ActionParamKeyID key, ai::UnicodeString& value);

	/** Sets the string value associated with a particular key in a VPB, using a Unicode string.
	For details, see \c #AIActionSetString().  */
	ASErr ASAPI (*AIActionSetStringUS)(AIActionParamValueRef param, ActionParamKeyID key, const ai::UnicodeString& value);

	/** Retrieves the enumerated value associated with a particular key in a VPB, as a Unicode string.
	For details, see \c #AIActionGetEnumeratedUS().  */
	ASErr ASAPI (*AIActionGetEnumeratedUS)(AIActionParamValueRef param, ActionParamKeyID key,  ai::UnicodeString& name, ai::int32* value);

	/** Sets the enumerated value associated with a particular key in a VPB, using a Unicode string.
	For details, see \c #AIActionSetEnumeratedUS().  */
	ASErr ASAPI (*AIActionSetEnumeratedUS)(AIActionParamValueRef param, ActionParamKeyID key,  const ai::UnicodeString& name, ai::int32 value);
};


#include "AIHeaderEnd.h"

#endif
