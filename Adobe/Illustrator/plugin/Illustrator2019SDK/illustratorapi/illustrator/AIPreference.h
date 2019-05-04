#ifndef __AIPreference__
#define __AIPreference__

/*
 *        Name:	AIPreference.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Preference Suite.
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


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIFixedMath__
#include "AIFixedMath.h"
#endif

#ifndef __SPPlugins__
#include "SPPlugs.h"
#endif

#ifndef __AIMenu__
#include "AIMenu.h"
#endif

#include "IAIUnicodeString.h"
#include "IAIFilePath.hpp"

#include "AIHeaderBegin.h"

/** @file AIPreference.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPreferenceSuite		"AI Preference Suite"
#define kAIPreferenceSuiteVersion7	AIAPI_VERSION(7)
#define kAIPreferenceSuiteVersion	kAIPreferenceSuiteVersion7
#define kAIPreferenceVersion		kAIPreferenceSuiteVersion

/** @ingroup Notifiers
	Sent when a change is made to the preferences.
	See \c #AIPreferenceSuite */
#define kAIPreferenceChangedNotifier	"AI Preference Changed Notifier"


/** @ingroup Callers
	See \c #AIPreferenceSuite  */
#define kAIPreferenceCaller				"AI Preference"
/** @ingroup Selectors
	See \c #AIPreferenceSuite */
#define kAIPreferenceInitSelector		"Init Preference Panel"
/** @ingroup Selectors
	See \c #AIPreferenceSuite */
#define kAIPreferenceOKSelector			"Preference Dialog OK"
/** @ingroup Selectors
	See \c #AIPreferenceSuite */
#define kAIPreferenceCancelSelector		"Preference Dialog Cancel"
/** @ingroup Selectors
	See \c #AIPreferenceSuite */
#define kAIPreferenceUpdateSelector		"Preference Dialog Upadate"

/** If you add a preference for a Disable checkbox to the alert dialog, call
 	 <code>AIPreferenceSuite::PutBooleanPreference(
		 	kAIPreferenceTurnOffWarningPrefix,
		 	"your plug-in unique string",
		 	value) </code>
	This allows Illustrator to clear the General preference.
	<<I'm not sure what this means - it could use some context>> */
#define kAIPreferenceTurnOffWarningPrefix	"DontShowWarningAgain"

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference to a preference item group, never dereferenced.
	Access with \c #AIPreferenceSuite */
typedef struct _t_AIPreferenceItemGroupOpaque	*AIPreferenceItemGroupHandle;

/** Type for a date/time value stored in preferences, */
typedef ai::uint32 AIPreferenceDateTime;

/** Message sent by the preference selectors. */
struct AIPreferencePanelMessage {
	/** Message data */
	SPMessageData d;
	/** The preference item group */
	AIPreferenceItemGroupHandle itemGroup;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides cross-platform access to Illustrator
	preferences. It allows you to store your plug-in’s preferences,
	save them at shutdown, and restore them at startup. The suite also
	allows you to access Illustrator application preferences at any time.

	Illustrator reads the preferences file from disk only once, when the
	application is first launched, and writes it only once, when the
	application quits. The Preference suite functions interact with
	the preferences stored in memory, not with the preferences file on disk.

	@section PluginPrefs Accessing Plug-in Preferences

	This suite also allows you to add your plug-in preferences to the
	Preferences dialog box. Generally, your plug-in reads its own
	preferences during the startup message action and writes them at shutdown.

	You get and set values according to their data type. The suite provides
	accessors (get and put functions) for each of the basic data types:
	boolean, integer, real, C string, block, fixed, fract, Pascal string,
	date/time stamp, point, rect, and file spec.

	Each function in the suite takes three arguments:
		\li The \e prefix, which is generally your plug-in’s name.
		\li The \e suffix, which is the name of a specific preference
			item in your plug-in.
		\li The \e value, which is the new value to be associated with
			the named preference (for put) or a buffer in which to return
			its current value (for get). If a get function does not find
			the prefix/suffix pair in the preferences file, the value
			argument remains unchanged; you should preset the buffer
			to the default value for the preference you are retrieving.

	For predefined prefixes and suffixes of application and Adobe plug-in
	preferences, see \c AIPreferenceKeys.h.

	This example saves and retrieves preferences for a window position
	and visibility status:
	\verbatim
// save preferences for plug-in dialog
error = sPref->PutBooleanPreference(kPluginName, "dialogShowing", g->dialogShowing);
error = sPref->PutPointPreference(kPluginName, "dialogPosition", &g->dialogPosition);
//retrieve preferences for plug-in dialog
g->dialogShowing = false; // default is not visible
error = sPref->GetBooleanPreference(kPluginName, "dialogShowing", &g->dialogShowing);
g->dialogPosition = { 100 , 100 }; // default position
error = sPref->GetPointPreference(kPluginName, "dialogPosition", &g->dialogPosition);
	\endverbatim

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPreferenceSuite and \c #kAIPreferenceVersion.

	@section AppPrefs Accessing Application Preferences

	Application preferences are predefined. You can examine the preferences
	file to find their names.
		\li To specify an application preference, use \c NULL for the prefix.
		 	For the suffix, use a path derived from the preference file without
		 	the leading slash character. See also predefined suffixes in
		 	\c AIPreferenceKeys.h.
		\li There is no direct way to determine the data type of an application
			preference. You must determine the data type based on your knowledge
			of Illustrator and the appearance of the value in the preference file.

	For example, the constrain angle used by the Illustrator tools is an application
	preference. It is stored in the preference file at follows:
	\verbatim
/constrain {
	/sin 0.0
	/cos 16.0
	/angle 0.0
	}
	\endverbatim

	These values are real numbers. To retrieve the value of \c sin,
	use the accessor for the \c AIReal type:
	\verbatim
AIReal r;
error = sPref->GetRealPreference(nullptr, "constrain/sin", &r);
	\endverbatim

	The snap-to-point option is displayed as a checkbox in the General Preferences
	dialog, which implies that it has a boolean value. It is stored in the file as follows:
	\verbatim
/snapToPoint 1
	\endverbatim

	To retrieve the setting, use the boolean accessor:
	\verbatim
AIBoolean snap;
error = sPref->GetBooleanPreference(nullptr, "snapToPoint", &snap);
	\endverbatim
*/
struct AIPreferenceSuite {

	/** Retrieves a boolean preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetBooleanPreference) ( const char *prefix, const char *suffix, AIBoolean *value );

	/** Sets a boolean preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutBooleanPreference) ( const char *prefix, const char *suffix, AIBoolean value );

	/** Retrieves an integer preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetIntegerPreference) ( const char *prefix, const char *suffix, ai::int32 *value );

	/** Sets an integer preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutIntegerPreference) ( const char *prefix, const char *suffix, ai::int32 value );

	/** Retrieves a real-number preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetRealPreference) ( const char *prefix, const char *suffix, double *value );

	/** Sets a real-number preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutRealPreference) ( const char *prefix, const char *suffix, double value );

	/** Retrieves a C-string preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetStringPreference) ( const char *prefix, const char *suffix, char *value );

	/** Sets a C-string preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutStringPreference) ( const char *prefix, const char *suffix, const char *value );

	/** Retrieves a Unicode string preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetUnicodeStringPreference) ( const char *prefix, const char *suffix, ai::UnicodeString& value );

	/** Sets a Unicode string preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutUnicodeStringPreference) ( const char *prefix, const char *suffix, const ai::UnicodeString& value );

	/** Retrieves a block preference created with \c #PutBlockPreference().
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param address [out] A buffer in which to return the value.
			@param size The number of bytes allocated at \c address.
		*/
	AIAPI AIErr (*GetBlockPreference) ( const char *prefix, const char *suffix, void *address, ai::int32 size );

	/** Sets a block preference.  Use this to store data that does
		not fit one of the basic types. For example, you could store
		a color value as a single block preference rather than
		three or four separate integer preferences.

		The preference file is a human-readable (and editable) ASCII file, and
		you should  respect this in block data that you create. For example,
		write out color values as ASCII strings, not as binary values.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param address A buffer containing the new value.
			@param size The number of bytes allocated at \c address.
		*/
	AIAPI AIErr (*PutBlockPreference) ( const char *prefix, const char *suffix, void *address, ai::int32 size );

	/** Retrieves a fixed-number preference. (For compatibility with AI7 and earlier.)
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetFixedPreference) ( const char *prefix, const char *suffix, AIFixed *value );


	/** Sets a fixed-number preference. (For compatibility with AI7 and earlier.)
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutFixedPreference) ( const char *prefix, const char *suffix, AIFixed value );

	/** Retrieves a fractional preference. (For compatibility with AI7 and earlier.)
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetFractPreference) ( const char *prefix, const char *suffix, AIFract *value );

	/** Sets a fractional preference. (For compatibility with AI7 and earlier.)
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutFractPreference) ( const char *prefix, const char *suffix, AIFract value );

	/** Retrieves a Pascal-string preference. (For compatibility with AI7 and earlier.)
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetPascalPreference) ( const char *prefix, const char *suffix, unsigned char *value );

	/** Sets a Pascal-string preference. (For compatibility with AI7 and earlier.)
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutPascalPreference) ( const char *prefix, const char *suffix, const unsigned char *value );

	/** Retrieves a date-time preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetDateTimePreference) ( const char *prefix, const char *suffix, AIPreferenceDateTime *value );

	/** Sets a date-time preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutDateTimePreference) ( const char *prefix, const char *suffix, AIPreferenceDateTime *value );

	/** Retrieves a point preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetPointPreference) ( const char *prefix, const char *suffix, AIPoint *value );

	/** Sets a point preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutPointPreference) ( const char *prefix, const char *suffix, AIPoint *value );

	/** Retrieves a rectangle preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetRectPreference) ( const char *prefix, const char *suffix, AIRect *value );

	/** Sets a rectangle preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutRectPreference) ( const char *prefix, const char *suffix, AIRect *value );

	/** Retrieves a file path specification preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetFilePathSpecificationPreference) ( const char *prefix, const char *suffix, ai::FilePath &value );

	/** Sets a file path specification preference.
			@param prefix The name of the plug-in, or \c NULL for an application preference.
			@param suffix The name of the preference.
			@param value The new value.
		*/
	AIAPI AIErr (*PutFilePathSpecificationPreference) ( const char *prefix, const char *suffix, const ai::FilePath &value );

	/** Deletes a preference that was defined by your plug-in.
		Do not attempt to remove any other preferences.
			@param prefix The name of the plug-in.
			@param suffix The name of the preference.
		*/
	AIAPI AIErr (*RemovePreference) ( const char *prefix, const char *suffix );

	/** Adds a panel to the Preferences dialog, using a dialog you define to
		query the user for your plug-in preferences. Adds a menu item for your panel
		to the Preferences submenu, creating and returning the menu item object.
			@param pluginRef The plug-in object.
			@param itemText The localizable string that appears in the Preferences submenu
				and in the Preferences dialog pop-up menu.
			@param dialogID The unique identifier of the dialog you have defined in your
				plug-in resources. The elements are added to the Preferences dialog
				as an item group. See \c #ADMDialogSuite10 and \c #ADMItemSuite9.
			@param options Not used. Pass 0.
			@param prefItemGroup [out] A buffer in which to return the new dialog item-group
				reference for the panel. This panel object is passed back as part of the
				\c #AIPreferencePanelMessage when the panel is shown in the dialog. Use it
				with \c #GetPreferencePanelBaseItemIndex()
				to access the dialog items when the panel is displayed.
			@param menuItem [out] A buffer in which to return the new menu item reference.
		*/
	AIAPI AIErr (*AddPreferencePanel) (SPPluginRef pluginRef, unsigned char *itemText, ai::int32 dialogID, ai::int32 options,
			AIPreferenceItemGroupHandle *prefItemGroup, AIMenuItemHandle *menuItem);

	/** Retrieves the index position of the base item from a preference item group.
		All identifiers for items in your Preferences panel are offset by this value.
		The call is only valid when the Preferences dialog is displayed.
			@param prefItemGroup TThe panel item-group object, as returned by
				\c #AddPreferencePanel().
			@param baseIndex [out] A buffer in which to return the 0-based position
				index of the base item.
		*/
	AIAPI AIErr (*GetPreferencePanelBaseItemIndex) (AIPreferenceItemGroupHandle prefItemGroup, ai::int32 *baseIndex);

	/** Displays a plug-in-defined panel in the Preferences dialog.	Called
		by the menu item that was created by \c #AddPreferencePanel().
			@param prefItemGroup The panel item-group object, as returned by
				\c #AddPreferencePanel().
		*/
	AIAPI AIErr (*ShowPreferencePanel) (AIPreferenceItemGroupHandle prefItemGroup);

	/** Retrieves an integer preference for 64 bit data type.
	@param prefix The name of the plug-in, or \c NULL for an application preference.
	@param suffix The name of the preference.
	@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetLargeIntegerPreference) ( const char *prefix, const char *suffix, ai::int64 *value );

	/** Sets an integer preference for 64 bit data type.
	@param prefix The name of the plug-in, or \c NULL for an application preference.
	@param suffix The name of the preference.
	@param value The new value.
	*/
	AIAPI AIErr (*PutLargeIntegerPreference) ( const char *prefix, const char *suffix, ai::int64 value );

	/** Checks if a Preference Exists.
	@param prefix The name of the plug-in, or \c NULL for an application preference.
	@param suffix The name of the preference.
	@param doesExist[out] A buffer in which to return whether the preference exists or not.
	*/
	AIAPI AIErr (*PreferenceExists) (const char* prefix, const char* suffix, AIBoolean* doesExist);
    
};


#include "AIHeaderEnd.h"


#endif
