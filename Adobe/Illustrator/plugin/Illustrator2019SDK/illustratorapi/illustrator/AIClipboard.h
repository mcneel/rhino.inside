#ifndef __AIClipboard__
#define __AIClipboard__

/*
 *        Name:	AIClipboard.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Clipboard Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2015 Adobe Systems Incorporated.
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

#include "AIHeaderBegin.h"

/** @file AIClipboard.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIClipboardSuite				"AI Clipboard Suite"
#define kAIClipboardSuiteVersion5		AIAPI_VERSION(5)	// In AI 20.1
// latest version
#define kAIClipboardSuiteVersion		kAIClipboardSuiteVersion5
#define kAIClipboardVersion				kAIClipboardSuiteVersion

/** @ingroup Callers
	The clipboard caller. See \c #AIClipboardSuite. */
#define kCallerAIClipboard 				"AI Clipboard"

/** @ingroup Selectors
	Execute a clipboard operation.
	The \c option field of the \c #AIClipboardMessage is either
	\c #kClipboardCopy or \c #kClipboardPaste. Perform the
	requested operation on the data in the \c ClipboardData field.
		\li For paste, the data in the message is in a format handled
			by your plug-in. Read the data and convert it to artwork in
			the current document, but do not delete the data.
		\li For copy, convert the data to the format your plug-in handles,
			and store a pointer to the result in the \c ClipboardData field
			of the message.
	*/
#define kSelectorAIGoClipboard				"AI Go"


/** @ingroup Selectors
	Check if you can copy the data in the current document to your format.
	Return \c #kNoErr if you can and \c #kCantCopyErr
	if you cannot. The \c #AIClipboardMessage does not contain meaningful data. */
#define kSelectorAICanCopyClipboard		"AI Can Copy"
/** @ingroup Selectors
	Requests a duplicate of the data in the \c ClipboardData field of
	\c #AIClipboardMessage, which is in a format your plug-in handles.
	Make a copy, replace the \c ClipboardData with the copy,
	and return \c #kNoErr. If you cannot make the copy, return an error code.
*/
#define kSelectorAICloneClipboard			"AI Clone"
/** @ingroup Selectors
	Delete the data in the \c ClipboardData field of the
	\c #AIClipboardMessage, which is in a format your plug-in handles.   */
#define kSelectorAIDisposeClipboard		"AI Dispose"

/** Option flags for registering a clipboard format handler with
	\c #AIClipboardSuite::AddClipboard(), specifies which operations
	are supported.
	*/
enum AIClipboardFormatOptions {
	/** This format knows how to copy to the clipboard. */
	kClipboardCopy						=	(1<<1),
	/** This format knows how to paste from the clipboard. */
	kClipboardPaste						=	(1<<2),
	/** This format cannot copy data to the clipboard.
		If set, user cannot enable the preference
		for copying data on exit. This is needed because
		the \c kClipboardCopy flag is also used internally
		to track the state of the user preference.
	*/
	kClipboardCannotCopy				=	(1<<3)
};

/** @ingroup Errors
	Return from \c kSelectorAICanCopyClipboard if you cannot perform copy. */
#define kCantCopyErr		'CLP?'


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Identifies a registered clipboard format handler. */
typedef struct _t_AIClipboardOpaque *AIClipboardHandle;

/** Identifies a resource type. */
typedef ai::uint32 DDType;

/** Data used to register a clipboard format handler. See
	\c #AIClipboardSuite::AddClipboard(). */
typedef struct {
	/** The format name, such as "myCompany File Format" or "Rich Text Format"*/
	const char* clipboardName;
	/** In Windows, the OLE data type, such as \c CF_TEXT or \c CF_BITMAP */
	ai::int32 OleType;
	/** In Mac OS, the unique data resource type (\c ResType),
		such as \c 'TEXT' or \c 'PICT'. Check \c AIDragDropTypes.h
		to make sure it is unique.
		*/
	DDType uniqueType;
} AIClipboardData;

/** The message structure received when the clipboard format handler's main
	entry point receives a message with caller \c #kCallerAIClipboard */
typedef struct {
	/** The message data */
	SPMessageData d;
	/** The clipboard object. */
	AIClipboardHandle Clipboard;
	/** The clipboard data */
	AIStream ClipboardData;
	/** The supported clipboard operations.
		A logical OR of \c #AIClipboardFormatOptions values. */
	ai::int32 option;
} AIClipboardMessage;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The clipboard suite enables plug-ins to register new clipboard format handlers.
	The handler's main entry point then receives messages requesting it to
	copy data to and from the clipboard as needed. The messages have caller
	\c #kCallerAIClipboard. The possible selectors are:

	\li \c #kSelectorAIGoClipboard
	\li \c #kSelectorAICanCopyClipboard
	\li \c #kSelectorAICloneClipboard
	\li \c #kSelectorAIDisposeClipboard


	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIClipboardSuite and \c #kAIClipboardVersion.
*/
typedef struct {

	/** Registers a new clipboard format handler.
			@param self The plug-in.
			@param data The types of clipboard data handled.
			@param options The capabilities of the format handler.
				A logical OR of \c #AIClipboardFormatOptions values.
			@param Clipboard [out] A buffer in which to return the clipboard handler reference.
		*/
	AIAPI AIErr (*AddClipboard) ( SPPluginRef self, AIClipboardData *data,
		ai::int32 options, AIClipboardHandle *Clipboard );
	/** Unregisters a clipboard format handler.
			@param Clipboard The clipboard handler reference.
		*/
	AIAPI AIErr (*RemoveClipboard) (AIClipboardHandle Clipboard);

	/** Retrieves the registered name of a clipboard format handler.
			@param Clipboard The clipboard handler reference.
			@param name [out] A buffer in which to return the name.
		*/
	AIAPI AIErr (*GetClipboardName) (AIClipboardHandle Clipboard, const char* *name);

	/** Retrieves Windows OLE type of the data handled by the format handler.
			@param Clipboard The clipboard handler reference.
			@param OleType [out] A buffer in which to return the OLE data type.
		*/
	AIAPI AIErr (*GetClipboardOleType) (AIClipboardHandle Clipboard, ai::int32* OleType);

	/** Retrieves the plug-in reference for the plug-in supplying the format handler.
			@param Clipboard The clipboard handler reference.
			@param plugin [out] A buffer in which to return the plug-in reference.
		*/
	AIAPI AIErr (*GetClipboardPlugin) (AIClipboardHandle Clipboard, SPPluginRef *plugin);

	/** Retrieves Mac OS resource type of the data handled by the format handler.
			@param Clipboard The clipboard handler reference.
			@param uniqueType [out] A buffer in which to return the data resource type.
		*/
	AIAPI AIErr (*GetClipboardType) (AIClipboardHandle Clipboard, DDType *uniqueType);

	/** Retrieves the options describing the capabilities of the format handler.
			@param Clipboard The clipboard handler reference.
			@param options [out] A buffer in which to return the capabilities of the
				format handler. A logical OR of \c #AIClipboardFormatOptions values.
		*/
	AIAPI AIErr (*GetClipboardOptions) (AIClipboardHandle Clipboard, ai::int32 *options);

	/** Sets the options describing the capabilities of the format handler.
			@param Clipboard The clipboard handler reference.
			@param options The capabilities of the format handler.
				A logical OR of \c #AIClipboardFormatOptions values.
		*/
	AIAPI AIErr (*SetClipboardOptions) (AIClipboardHandle Clipboard, ai::int32 options);

	/** Counts the number of registered clipboard format handlers. Use with
		\c #GetNthClipboard() to iterate through handlers.
			@param count [out] A buffer in which to return the number of handlers.
		*/
	AIAPI AIErr (*CountClipboards) (ai::int32 *count);

	/** Retrieves a clipboard format handler by position index. Use with
		\c #CountClipboards() to iterate through handlers.
			@param n The index, in the range <code>[0..numHandlers-1]</code> .
			@param Clipboard [out] A buffer in which to return the clipboard handler reference.*/
	AIAPI AIErr (*GetNthClipboard) (ai::int32 n, AIClipboardHandle *Clipboard);

} AIClipboardSuite;

#include "AIHeaderEnd.h"


#endif
