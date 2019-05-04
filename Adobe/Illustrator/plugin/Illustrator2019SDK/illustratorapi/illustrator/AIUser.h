#ifndef __AIUser__
#define __AIUser__

/*
 *        Name: AIUser.h
 *   $Revision: 15 $
 *      Author:
 *        Date:
 *     Purpose: Adobe Illustrator User Utilities Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2016 Adobe Systems Incorporated.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIMenu__
#include "AIMenu.h"
#endif

#ifndef __AIFileFormat__
#include "AIFileFormat.h"
#endif

#ifndef __AIDocumentView__
#include "AIDocumentView.h"
#endif

#include "IAIFilePath.hpp"
#include "IAILocale.h"

#include "AIHeaderBegin.h"

/** @file AIUser.h */


/************************************************************************s*******
 **
 **	Constants
 **
 **/

#define kAIUserSuite				"AI User Suite"
#define kAIUserSuiteVersion16		AIAPI_VERSION(16)
#define kAIUserSuiteVersion			kAIUserSuiteVersion16
#define kAIUserVersion				kAIUserSuiteVersion

#if Macintosh || MSWindows
#define kAIMacUserSuite				"AI Mac User Suite"
#define kAIMacUserSuiteVersion7		AIAPI_VERSION(7)
#define kAIMacUserSuiteVersion		kAIMacUserSuiteVersion7
#define kAIMacUserVersion			kAIMacUserSuiteVersion
#endif

/** Unit formats for \c #AIUserSuite::GetUnitsString().*/
enum {
	/** Short unit format; for example, "in". */
	kShortUnits,
	/** Long singular unit format; for example, "inch". */
	kLongSingularUnits,
	/** Long plural unit format; for example, "inches". */
	kLongPluralUnits
};

/**
	Constants for alert button choices.
	See \c #AIUserSuite.
**/
enum AIAnswer {
	kAIAnswer_No = 0,
	kAIAnswer_Yes,
	kAIAnswer_Cancel,
	kAIAnswer_Invalid =  0xFFFFFFFF
};

/**
	Flag values to determine the stage of input for which
	a validation callback has been called.
	See \c #AIUserSuite::GetInputFromUser() and \c #IsValidInputProc.
**/
enum AIValidationStage
{
	/** Callback invoked on entry of a single character in the text field. */
	kAIValidationStage_interactive = 0,
	/** Callback invoked on dismissal of alert dialog with OK button. */
	kAIValidationStage_onOk = 1
};

/**
	Identifiers for predefined cursors.
	See \c #AIUserSuite::SetCursor()
**/
enum AIPredefinedCursor
{
	kAIIBeamCursorID = -1,
	kAICrossCursorID = -2,
	kAIWaitCursorID = -3,
	kAIArrowCursorID = -4
};

/** @ingroup Errors
See \c #AIUserSuite. */
#define kUnknownUnitsErr		'?UNT'

/** @ingroup Errors
	See \c #AIUserSuite::EditInOriginalApp(). */
#define kApplicationNotFoundErr	'App?'

/** @ingroup Errors
See \c #AIUserSuite::EditInOriginalApp(). */
#define kObjectNotLinkedErr		'!Lnk'


/** Opaque reference to a date-time value. Access with the \c #AIUserSuite. */
typedef ai::uint32 AIUserDateTime;

/** Opaque reference to a resource manager handle. See \c #AIUserSuite::CreateCursorResourceMgr().*/
typedef struct _t_Opaque_AIResourceManagerHandle *AIResourceManagerHandle;

/**	Callback function pointer passed to \c #AIUserSuite::GetInputFromUser().
    Can be called at either of the two stages: when the OK button in the alert dialog box is pressed (\c #kAIValidationStage_onOk)
	or when a text character is entered in the text field (\c #kAIValidationStage_interactive).
    The function must validate the input string, and return the output as true if the string is valid in the context.
    If the string fails validation, return false and set the \c errorStr output parameter to a string
    suitable for display in the alert dialog as a tool tip.
*/
typedef AIBoolean (*IsValidInputProc) (AIValidationStage validationStage, const ai::UnicodeString &input, ai::UnicodeString &errorStr, void *userdata);

/**	Progress Callback function pointer passed to \c #AIUserSuite::SetUpdateProgressCallback().
	This can be used to implement a custom progress handler.  
	The first parameter of the function is \c current , a number between 0 and \c max that represents
	how far the operation has progressed and the second parameter is \c max , the maximum value,
	representing 100% progress.
	This progress handler must return the output as:
		-true to cancel further processing 
		-false to continue processing
*/
typedef AIBoolean (*UpdateProgressProc) (ai::int32 current, ai::int32 max);

/** Global locale format.  Equivalent to the ENGLISH locale. */
#define kAIUniversalLocaleFormat		0x0000
/** Local resource locale format.  Defined by the locale of the current resource chain. */
#define kAIResourceLocaleFormat			0x0001
/** System locale format.  Defined by the current system locale. */
#define kAISystemLocaleFormat			0x0002

/** Short date display format.  An example of a short date is along the lines of "1/1/2007".  The exact form is locale dependent.
	See \c #AIUserSuite::GetDateString()  */
#define kAIShortDateFormat				0x0000
/** Long date display format.   An example of a long date is "Tuesday, March 20, 2007".  The exact form is locale dependent.
	See \c #AIUserSuite::GetDateString()  */
#define kAILongDateFormat				0x0100
/** Abbreviated date display format.  In Windows, equivalent to the short format except in Japanese locale, where it is the long format.
                                      In Mac OS, an abbreviated date is "Tue, Mar 20, 2007".  The exact form is locale dependent.
	See \c #AIUserSuite::GetDateString()  */
#define kAIAbbrevDateFormat				0x0200
/** Short time display format.  An example is "hh:mm".  The exact form is locale dependent.
	See \c #AIUserSuite::GetTimeString() */
#define kAIShortTimeFormat				0x0000
/** Long time display format.  An example is "hh:mm:ss". The exact form is locale dependent.
	See \c #AIUserSuite::GetTimeString()  */
#define kAILongTimeFormat				0x0100


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Information about the kind of names allowed for a named entity (such as
	layers, swatches, and styles). Used to generate a legal name, using
	\c #AIUserSuite::NextName() and AIUserSuite::CopyOfName().

	The following pseudocode indicates how you can create your own AutoNameGenerator class by publicly inheriting AIAutoNameGenerator
	and following the implementation guidelines.

@code
	class AutoNameGenerator : public AIAutoNameGenerator {
	public:
		// Constructor for a name generator. Its supplied with the pluginref in
		// case the name generator needs to look in the plugin's resources e.g for
		// the default name. The next new name index is supplied since the plugin
		// probably needs to store this in its globals so that it can be preserved
		// across unload and reload.
		AutoNameGenerator (SPPluginRef pluginref, int nextNameIndex)
		{
			// fill in fDefaultName
			GetDefaultName(pluginref);

			// initialize the base members
			// note kMaxCollectionStringLength accounts for null terminator and maximumLength does not
			maximumLength = kMaxCollectionStringLength-1;
			uniqueNames = true;
			baseName = fDefaultName;
			nextNewNameIndex = nextNameIndex;
			HasName = sHasName;
		}

	private:
		void GetDefaultName (SPPluginRef pluginref)
		{
			// Somehow initialize fDefaultName with the default name for the
			// collection. The pluginref is probably needed in order to look
			// up the name in the plugin resources.
		}

		AIErr hasName (const ai::UnicodeString &name, AIBoolean &hasit)
		{
			// Code to answer the question. When comparing 'name' against
			// names of objects in the collection it's important to use the
			// AIUserSuite::SameName() API. The name generation process does
			// not use a simple string comparison.
		}

		static AIAPI AIErr sHasName (AIAutoNameGenerator &self, const ai::UnicodeString &name, AIBoolean &hasit)
		{
			return static_cast<AutoNameGenerator&>(self).hasName(name, hasit);
		}

		ai::UnicodeString fDefaultName;
	};
@endcode
*/
struct AIAutoNameGenerator
{

	/** The maximum length for names in the collection, a number of
		\c ASUnicode elements. Excludes the null terminator. */
	ai::int32 maximumLength;

	/** True if names in the collection must be unique. */
	AIBoolean uniqueNames;

	/** A base for generating names, a Unicode-encoded string. */
    ai::UnicodeString baseName;

	/** The index to use for the next new name generated. Name generation
		functions automatically increment the index. */
	ai::int32 nextNewNameIndex;

	/** A callback function to determine whether a given name is already in
		the set. Use \c #AIUserSuite::SameName() to compare names, not simple
		string equality.
			@param self This structure.
			@param name The name to test.
			@param hasit [out] An AIBoolean reference in which to return true if the name is
				already in the collection.
			@return An error to abort name generation; the error code
				is returned to the caller.
		*/
    AIAPI AIErr (*HasName) (AIAutoNameGenerator &self, const ai::UnicodeString &name, AIBoolean &hasit);
};




/**	These functions manage a collection of file type specifiers
    for dialog functions in \c #AIUserSuite, which show drop-down
    lists for each file type. */
struct AIFileDialogFilters
{
	/** Adds a file-type filter with default pattern (*.*)
	(Note that this function does not return an error code.)
	@param desc		Description of file type.
	*/
	void AddFilter(const ai::UnicodeString &desc);


	/** Adds a file-type filter with a \c UnicodeString pattern.
	(Note that this function does not return an error code.)
	@param desc		Description of file type.
	@param pattern	One or more Windows wildcard patterns to filter
	for the file type, separated with semicolons (;).
	For example, <code>Addfilter("JPEG Files", "*.jpg;*.jpeg");</code>
	*/
	void AddFilter(const ai::UnicodeString &desc, const ai::UnicodeString &pattern);

	/** Retrieves a single string containing type descriptions and patterns.
	(Note that this function returns a string value, not an error code.)
	@return A string containing a series of null-delimited descriptions
	and patterns, terminated by a double-null. For example:
	"first description\0first pattern\0...last description\0last pattern\0\0"
	*/
	const ai::UnicodeString &GetFilter() const;

private:
	ai::UnicodeString filterStr;
};

/**
A structure that describes how the result should be returned by \c #AIUserSuite::EvaluateExpression().
*/
struct AIExpressionOptions
{
	/** The units in which the output value is expressed, one of the distance-measuring
	units from \c #AITypes::AIUnits, or the constant \c #kAINoUnits to indicate an
	absolute value. Other values cause parameter errors.
	*/
	ai::uint32 unit;

	/** The minimum value to which the result is clipped, expressed in the specified units. */
	AIDouble minValue;

	/** The maximum value to which the result is clipped, expressed in the specified units.*/
	AIDouble maxValue;

	/** The previous value of control. Can be any valid value. In case of erroneous or unallowed inStringVal,
	finalValue would be same as old value */
	AIDouble oldValue;

	/** The number of digits after the decimal in the result. */
	ai::uint32 precision;

};

/** @ingroup Suites
	This suite provides utility functions for working with Illustrator,
	including unit conversion utilities and a progress bar.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIUserSuite and \c #kAIUserSuiteVersion.
	*/
struct AIUserSuite {

	/** Reports whether a user has canceled the current operation.
		(Note that this function returns a boolean value, not an error code.)
			@return	True if the user has canceled an operation
				by pressing Command-dot or clicking Cancel or Stop in the
				progress bar.
		*/
	AIAPI AIBoolean (*Cancel) ( void );

	/** Updates the progress bar.
		(Note that this function does not return an error code.)
			@param current A number between 0 and \c max that represents
				how far the operation has progressed.
			@param max The maximum value, representing 100% progress.
		*/
	AIAPI void (*UpdateProgress) ( ai::int32 current, ai::int32 max );

	/** Registers the progress callbacks.
		(Note that this function does not return an error code.)
			@param UpdateProgressProc - A function pointer to progress callback.
				The first parameter to this call is \c current , a number between 0 and \c max that represents
				how far the operation has progressed and the second parameter is \c max , the maximum value,
				representing 100% progress.
		*/
	AIAPI void(*SetUpdateProgressCallback) (UpdateProgressProc func);

	/**	Sets the text message displayed in the progress bar. If not provided,
		the text line is blank.
		(Note that this function does not return an error code.)
			@param text The text message.
		*/
	AIAPI void (*SetProgressText) ( const ai::UnicodeString& text );

	/** Explicitly close the progress bar if one is currently shown.
		(Note that this function does not return an error code.)
		*/
	AIAPI void (*CloseProgress) ( void );

	/**	Converts a number of document points to a Unicode string, using
		the period as a decimal separator.
		(Note that this function does not return an error code.)
			@param value The value to convert.
			@param precision The number of digits to the right of the decimal,
				in the range [0..4].
			@param string [out] A buffer in which to return the converted value, at
				least 12 characters.
		*/
    AIAPI void (*AIRealToString) ( AIReal value, ai::int16 precision, ai::UnicodeString& string );

	/**	Converts a Unicode string containing a number to an \c #AIReal value,
		using the period as a decimal separator.
		(Note that this function does not return an error code.)
			@param string The string to convert.
			@param value  [out] A buffer in which to return the converted value.
				If the string is not a number, this is set to \c #kAIRealUnknown.
		*/
	AIAPI void (*StringToAIReal) ( const ai::UnicodeString& string, AIReal *value );
	/**	Converts a number of document points to a Unicode string, using the localized
		international utilities (IU) decimal separator.
		(Note that this function does not return an error code.)
			@param value The value to convert.
			@param precision The number of digits to the right of the decimal,
				in the range [0..4].
			@param string [out] A buffer in which to return the converted value, at
				least 12 characters.
		*/
    AIAPI void (*IUAIRealToString) ( AIReal value, ai::int16 precision, ai::UnicodeString& string );
    
    /**	Converts a number of document points to a Unicode string, using the localized
     international utilities (IU) decimal separator.
     (Note that this function does not return an error code.)
     @param value The value to convert.
     @param precision The number of digits to the right of the decimal,
     in the range [0..4].
     @param string [out] A buffer in which to return the converted value, at
     least 12 characters.
     @param Locale unique identifying code like ai::Locale::kSystem.
     */
    AIAPI void (*IUAIRealToStringWithLocale) ( AIReal value, ai::int16 precision, ai::UnicodeString& string, const ai::LocaleID locale );

	/**	Converts a Unicode string containing a number to an \c #AIReal value,
		using the localized international utilities (IU) decimal separator.
		(Note that this function does not return an error code.)
			@param string The string to convert.
			@param value  [out] A buffer in which to return the converted value.
				If the string is not a number, this is set to \c #kAIRealUnknown.
		*/
	AIAPI void (*IUStringToAIReal) ( const ai::UnicodeString& string, AIReal *value );

	/**	Converts a number of document points to a formatted Unicode string containing
		a number and ruler units, using the localized international utilities (IU)
		decimal separator, and the passed preference for precision. If passed precision value is -1
		then user preference for precision is used.
		Uses the currently set ruler units, which can be inches, points, or centimeters.
		(Note that this function does not return an error code.)
			@param value The value to convert.
			@param precision The number of digits to the right of the decimal,
				in the range [0..4]. Pass -1 if user preference for precision should be used.
			@param string [out] A buffer in which to return the converted value, at
				least 12 characters.
		*/
	AIAPI AIErr (*IUAIRealToStringUnits) ( AIReal value, ai::int32 precision, ai::UnicodeString& string );

	/** Converts a formatted Unicode string containing a number expressed in ruler units
		to an \c #AIReal value in points. The current ruler units for the artwork
		are used as the original units to scale the result, and the user's
		preferences for precision are applied.
		(Note that this function does not return an error code.)
			@param string The string to convert, which uses the localized international utilities (IU)
				decimal separator. It can contain a unit specifier, one of "in", "pt", or "cm".
				If no unit specifier is included, uses the current ruler units.
			@param value [out] A buffer in which to return the converted value.
				If the string is not a number, this is set to \c #kAIRealUnknown.
	  	*/
	AIAPI void (*IUStringUnitsToAIReal) ( const ai::UnicodeString& string, AIReal *value );

	/** Retrieves a string representing the current ruler units.
			@param format The format for the result, one of:
				<br> \c #kShortUnits
				<br> \c #kLongSingularUnits
				<br> \c #kLongPluralUnits
				<br> If, for instance, the current unit is inches, the returned string
				would be "in", "inch", or "inches".
			@param string [out] A buffer in which to return the units string, at least 20 characters.
		*/
    AIAPI AIErr (*GetUnitsString) ( ai::int16 format, ai::UnicodeString& string );

	/**	Retrieves the base name of a global object, stripping off any additional
		token that was added to make the name unique (by a function such as
				\c #AICustomColorSuite::NewCustomColorName(), for example).
			@param name [in, out] A string in which to pass a unique name and
				return the base name. The string is modified in place.
		*/
	AIAPI AIErr (*GetGlobalObjectDisplayName)( ai::UnicodeString& name );

	/** Opens the appropriate application to edit a placed or raster object.
		This is equivalent to an option-double-click on the object with the selection tool.
			@param art The placed or raster art object.
			@return \c #kApplicationNotFoundErr error if the application is not found.
				<br> \c #kObjectNotLinkedErr error if the object is not a placed or raster object.
		*/
	AIAPI AIErr (*EditInOriginalApp) ( AIArtHandle art );

	/** Runs an "Idle Event" that allows the application to do various idle-time things like update its selection view and state.  Can be useful if
	    you have code that has its own message processing.  */
	AIAPI AIErr (*AppIdle) ( void );

	/**	Builds a directory menu.  Available only in Mac OS.  Builds a menu consisting of the specified path as well as all parent directories of that path.
			@param menu	 The platform-specific menu object.
			@param fileSpec	The file object for the directory.
		*/
	AIAPI AIErr (*BuildDirectoryMenu) ( AIPlatformMenuHandle menu, const ai::FilePath &fileSpec);

	/**	Retrieves a directory.  Available only in Mac OS. Returns a filespec pertaining to the 'index' item inside of the menu returned by BuildDirectoryMenu.
			@param fileSpec The file object for the directory.
			@param index The 0-based index of the directory.
		*/
	AIAPI AIErr (*GetIndexedDirectorySpec) ( ai::FilePath &fileSpec, ai::int32 index);

	/**	Reveals a file in the Finder. Available only in Mac OS.
			@param fileSpec	 The file object for the file.
		*/
	AIAPI AIErr (*RevealTheFile) ( const ai::FilePath &fileSpec);

	/** Disables (dims) the cancel or stop button in the progress bar.
		(Note that this function does not return an error code.)
		*/
	AIAPI void (*DisableProgressCancel) ( void );

	/** Reports whether it is safe to allocate memory. Calls when a timer
		or other  asynchronous event trigger an action that allocates memory.
		Not needed when handling notifications or user events; the plug-in does not receive
		these when it is not ok to allocate memory.
		(Note that this function returns a boolean value, not an error code.)
			@param True if it is safe to allocate memory. False if it is not safe; in this case,
				reschedule the action and try again later.
		*/
	AIAPI AIBoolean (*OKToAllocateMemory) ( void );

	// Introduced in AI 11
	/** Retrieves the current date and time.
			@param outValue [out] A buffer in which to return the current date-time value.
		*/
	AIAPI AIErr (*GetDateAndTime)(AIUserDateTime *outValue);

	/* Formats a date into a Unicode string.
			@param inValue The date to format, or \c NULL to format the current date-time value.
			@param formatFlag The format to use, one of:
				<br> \c #kAIShortDateFormat
				<br> \c #kAILongDateFormat
				<br> \c #kAIAbbrevDateFormat
			@param dateStringUS [out] A buffer in which to return the formatted date string.
		*/
	AIAPI AIErr (*GetDateString)(const AIUserDateTime *inValue, const ai::int32 formatFlag, ai::UnicodeString& dateStringUS);

	/* Formats a time into a Unicode string.
			@param inValue The time to format, or \c NULL to format the current date-time value.
			@param formatFlag The format to use, one of:
				<br> \c #kAIShortTimeFormat
				<br> \c #kAILongTimeFormat
			@param dateStringUS [out] A buffer in which to return the formatted time string.
		*/
	AIAPI AIErr (*GetTimeString)(const AIUserDateTime *inValue, const ai::int32 formatFlag, ai::UnicodeString& dateStringUS);

	/** Retrieves the year value from a date-time.
			@param inValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetYear)(const AIUserDateTime *inValue, int *year);

	/** Retrieves the month value from a date-time.
			@param inValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetMonth)(const AIUserDateTime *inValue, int *month);

	/** Retrieves the day value from a date-time.
			@param inValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetDay)(const AIUserDateTime *inValue, int *day);

	/** Retrieves the hour value from a date-time.
			@param inValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetHour)(const AIUserDateTime *inValue, int *hour);

	/** Retrieves the minute value from a date-time.
			@param inValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetMinute)(const AIUserDateTime *inValue, int *minute);

	/** Retrieves the second value from a date-time.
			@param inValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetSecond)(const AIUserDateTime *inValue, int *second);

	/** Retrieves the day-of-week value from a date-time.
			@param inValue The date-time value, or \c NULL to get the current date-time.
			@param year [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetDayOfWeek)(const AIUserDateTime *inValue, int *dayOfWeek);

	/**	Launches an application, and optionally opens the current document in it.
			@param spFileSpec The file specification for the application's executable.
			@param openDoc True to open the current document in the new application.
		*/
	AIAPI AIErr (*LaunchApp)(const ai::FilePath &spFileSpec, ASBoolean openDoc);

	/** Generates an appropriate name for a named object, such as
		a layer, swatch, or style, according to the naming rules for that
		collection.
			@param set The naming rules.
			@param name [out] An ai::UnicodeString in which to return the generated name.
		*/
	AIAPI AIErr (*NextName) (AIAutoNameGenerator &set, ai::UnicodeString &name);

	/** Generates an appropriate name for a copy of a named object, such as
		a layer, swatch, or style, according to the naming rules for that
		collection.
			@param set The naming rules.
			@param original	Original name to copy (may be an empty string).
			@param copy [out] An ai::UnicodeString in which to return the generated name.
 		*/
    AIAPI AIErr (*CopyOfName) (AIAutoNameGenerator &set, const ai::UnicodeString &original, ai::UnicodeString &copy);

	/** Tests for equality of names within a collection of named objects.
		Use in the \c #AIAutoNameGenerator::HasName() callback function
		to test whether an automatically generated name matches a name
		already in the collection.
			@param name1 The first name.
			@param name2 The second name.
			@param same [out] An AIBoolean reference in which to return true if the names
				are the same.
		*/
	AIAPI AIErr (*SameName) (const ai::UnicodeString &name1, const ai::UnicodeString &name2, AIBoolean &same);


	/** Opens a platform-specific dialog for saving a file.
     		@param title Dialog title.
			@param AIFileDialogFilters File types to save. Can be \c NULL.
			@param defaultName Default file name to appear in dialog. Can be \c NULL.
			@param ioFilePath [in, out] A buffer in which to pass the directory to browse or \c NULL, and
				return the full path of the file chosen by the user.
		*/
	AIAPI AIErr (*PutFileDialog)(const ai::UnicodeString &title, const AIFileDialogFilters*, const ai::UnicodeString &defaultName, ai::FilePath &ioFilePath);

	/** Opens a platform-specific dialog for opening a file.
     		@param title Dialog title.
			@param AIFileDialogFilters File types to open. Can be \c NULL.
			@param ioFilePath [in, out] A buffer in which to pass the directory to browse or \c NULL, and
				return the full path of the file chosen by the user.
	  */
	AIAPI AIErr (*GetFileDialog)(const ai::UnicodeString &title, const AIFileDialogFilters*, ai::FilePath &ioFilePath);

	/** Opens a platform-specific dialog for choosing a folder.
     		@param title Dialog title.
			@param ioFilePath [in, out] A buffer in which to pass the folder to browse or \c NULL, and
				return the full path of the folder chosen by the user.
	  */
	AIAPI AIErr (*GetDirectoryDialog)(const ai::UnicodeString &title, ai::FilePath &ioFilePath);

	/** Displays an alert dialog with a warning icon and OK and Cancel buttons.
			@param msg The message to display.
			@param defaultOk True to make the OK button the default, false to make Cancel the default.
			@param dontShowKey A preference key to use with the "Do not show again" checkbox,
				in which to store the user's choice and save it in the application preferences file.
				When \c NULL, the dialog does not include the checkbox.
			@return True if the dialog was dismissed with the OK button,
				false if it was canceled.
		*/
	AIAPI AIBoolean (*OKCancelAlert) (const ai::UnicodeString& msg, AIBoolean defaultOk, const char* dontShowKey);

	/** Displays an alert dialog with a warning icon and an OK button.
			@param msg The message to display.
			@param dontShowKey A preference key to use with the "Do not show again" checkbox,
				in which to store the user's choice and save it in the application preferences file.
				When \c NULL, the dialog does not include the checkbox.
			@return Nothing. It does not return AIErr
		*/
	AIAPI void (*WarningAlert) (const ai::UnicodeString& msg, const char* dontShowKey);

	/** Displays an modal alert dialog with a warning icon and an OK button which doesnot get dismissed on ESC key.
			@param msg The message to display.
			@param dontShowKey A preference key to use with the "Do not show again" checkbox,
			in which to store the user's choice and save it in the application preferences file.
			When \c NULL, the dialog does not include the checkbox.
			@return Nothing. It does not return AIErr
			*/
	AIAPI void (*MessageAlertEx) (const ai::UnicodeString& msg, const char* dontShowKey);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a unicodeString, and
		buttons with default labels Yes, No, and Cancel.
		@param msg The text string.
		@return The \c #AIAnswer constant for the button pressed to dismiss the dialog,
		or \c #kAIAnswer_Invalid in case of error.
		@see \c #ErrorAlert(), \c #MessageAlert(), \c #YesNoAlert()
		*/
	AIAPI AIAnswer (*QuestionAlert)(const ai::UnicodeString &msg);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a unicodeString, and
		buttons with default labels Yes and No.
		@param msg The text string.
		@return The \c #AIAnswer constant for the button pressed to dismiss the dialog,
		or \c #kAIAnswer_Invalid in case of error.
		@see \c #ErrorAlert(), \c #MessageAlert(), \c #QuestionAlert()
		*/
	AIAPI AIAnswer (*YesNoAlert)(const ai::UnicodeString &msg);

	/** Displays a predefined dialog that informs the user that an error occurred.
		The dialog displays text specified with a unicodeString, with the platform-specific
		error icon at the left, and an OK button.
		@param msg The text string.
		@return Nothing.It doesnot return an AIErr
		@see \c #MessageAlert(),  \c #QuestionAlert(), \c #YesNoAlert()
		*/
	AIAPI void (*ErrorAlert)(const ai::UnicodeString &msg);

	/** Displays a predefined dialog with an informational message.
		The dialog displays text specified with a unicodeString, with the
		platform-specific message icon at the left, and an OK button.
		@param msg The text string.
		@return Nothing.It doesnot return an AIErr
		@see \c #ErrorAlert(), \c #QuestionAlert(), \c #YesNoAlert()
		*/
	AIAPI void (*MessageAlert)(const ai::UnicodeString &msg);

	/**	Invokes the platform-specific color picker dialog.
	@param inLocation[int]	The position of the dialog.	 (-1, -1) centers the dialog on the screen.
	@param inColor[in]	The initially selected color value.
	@param outColor	[out] A buffer in which to return the selected color.
	@return True if the user selected a color, false otherwise.
	*/
	AIAPI AIBoolean (*ChooseFromOSColorPicker) (const AIPoint &inLocation,
		const AIRGBColor& inColor, AIRGBColor* outColor);

	/** Evaluates a numeric expression to create a formatted string suitable for display.
	Call, for example, when a numeric edit control loses focus or the user presses "=".
	If the result of evaluation is not a valid numeric value as per options specified, it is recommended that
	the associated control display the last known-good value, or a blank string
	accompanied by a beep or other error indicator.

	@param expr [in] The expression to be evaluated (typically entered by the user
	in the control).
	@param options [in] An \c #AIExpressionOptions structure that determines how
	a numeric result is obtained. Specifies the units for the
	result, a range to which the result is clipped, and the precision.
	@param evaluatedExpr [out] A buffer in which to return the formatted display string.
	@param isChanged [out] A buffer in which to return true if the result of evaluation
	is different from result of user input. Example in case of non numeric input or out of bounds input.
	@param numericValue [out] A buffer in which to return the numeric value, according to the specified options.
	*/
	AIAPI AIErr (*EvaluateExpression)(const ai::UnicodeString& expr, const AIExpressionOptions& options, ai::UnicodeString& evaluatedExpr,
		AIBoolean & isChanged , AIDouble& numericValue);

	/** Invokes a modal dialog in which the user must input text. The dialog cannot be dismissed
		until text is entered. If default text is provided, however, the user can dismiss the
		dialog without changing that text.

		@param title The title for the dialog
		@param messageText A text message to display above the input field, or NULL to display no message.
		@param label The label for the text field.
		@param ioName [in/out] On input, a default string for the text field. This is replaced by text that
			the user enters, if any.
		@param IsValidInputProc A function pointer to a validation callback that validates the input as typed by the user.
			The first parameter to this call is a \c #AIValidationStage constant that reports whether the call is
			made upon text entry, or upon dismissal of the dialog.
		@param userdata Developer-defined user data to be passed to the validation callback.
		@param maxInputChars The maximum number of characters that user can enter in the text field.
	 */
	AIAPI AIErr (*GetInputFromUser) ( const ai::UnicodeString &title, const ai::UnicodeString* messageText, const ai::UnicodeString &label, ai::UnicodeString& ioField, IsValidInputProc validator, void *userdata, ai::int32 maxInputChars);

	/**  Creates a singleton resource manager instance to be used for cursors.
		Call once for a plugin, after startup is completed.	Destroy the instance on
		application shutdown (not plug-in shutdown).
		@param inRscMgr [out] A buffer in which to return the resource-manager handle.
		@see DisposeCursorResourceMgr()
	*/
	AIAPI AIErr (*CreateCursorResourceMgr)(SPPluginRef, AIResourceManagerHandle* inRscMgr);

	/**  Sets the image to be used for the plug-in's cursor.
		@param cursorID The resource ID of the cursor, or a \c #AIPredefinedCursor
			constant value to use one of the predefined cursors. Cursor images must be
			in PNG format.
		@param inRscMgr The resource manager, as returned by \c #CreateCursorResourceMgr().
	*/
	AIAPI AIErr (*SetCursor)(ai::int32 cursorID, AIResourceManagerHandle inRscMgr);

	/**  Sets the SVG image to be used for the plug-in's cursor.
	@param cursorID The resource ID of the cursor. Cursor images must be
	in 2x scaled SVG format.
	@param inRscMgr The resource manager, as returned by \c #CreateCursorResourceMgr().
	*/
	AIAPI AIErr(*SetSVGCursor)(ai::int32 cursorID, AIResourceManagerHandle inRscMgr);

	/**  Disposes of the plug-in's singleton resource manager. Call once when
		 \c #kAIApplicationShutdownNotifier is received. Do not call as part of plug-in shutdown.
		@param The resource manager handle, as returned on creation.
	*/
	AIAPI AIErr (*DisposeCursorResourceMgr)(AIResourceManagerHandle);

	/** Reports the current language in use.
	 @param lang [out] A buffer in which to return the language code.
	 */
	AIAPI AIErr (*GetAILanguageCode)(ai::UnicodeString& lang);
    
	/** Reports the maximum scale factor for all the screens in a Mac OS system,
            or the application's UI scale factor in a Windows system.
            @return The scale factor.
    */

	AIAPI AIReal (*GetMaximumScaleFactorOnSystem)();


	/** Reports the ratio of Art Scale factor and View Scale Factor.
		(ArtScaleFactor/ ViewScaleFactor)
    */
	AIAPI AIReal(*GetArtToViewScaleFactor)(AIDocumentViewHandle view);


	/** Launches a folder.
	@param folderPath Path of the folder to launch.
	@return \c #kBadParameterErr if the path object is invalid or references a file rather than a folder.
	*/
	AIAPI AIErr(*LaunchFolder)(ai::FilePath folderPath);

};



/*
	Inline members
*/
	inline void AIFileDialogFilters::AddFilter(const ai::UnicodeString &desc)
	{
		AddFilter(desc, ai::UnicodeString("*"));
	}

	inline void AIFileDialogFilters::AddFilter(const ai::UnicodeString &desc, const ai::UnicodeString &pattern)
	{
		if (!desc.empty() && !pattern.empty())
		{
			const ai::UnicodeString::size_type len = filterStr.length();
			if (len)
				filterStr.erase(len-1);	// erase one null of the previous double null terminators
			filterStr.append(desc);
			filterStr.append(1, 0);
			filterStr.append(pattern);
			filterStr.append(2, 0);
		}
	}

	inline const ai::UnicodeString &AIFileDialogFilters::GetFilter() const
	{
		return filterStr;
	}

#include "AIHeaderEnd.h"


#endif
