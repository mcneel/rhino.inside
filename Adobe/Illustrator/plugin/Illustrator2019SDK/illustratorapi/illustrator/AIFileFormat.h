#ifndef __AIFileFormat__
#define __AIFileFormat__

/*
 *        Name:	AIFileFormat.h
 *     Purpose:	Adobe Illustrator File Format Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2014 Adobe Systems Incorporated.
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

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIPlaced__
#include "AIPlaced.h"
#endif

#include "AIEntry.h"

#include "IAIFilePath.hpp"
#include "AIArtboardRange.h"
#include "AIActionManager.h"

#include "AIHeaderBegin.h"



/** @file AIFileFormat.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/
#define kAIFileFormatSuite				"AI File Format Suite"
#define kAIFileFormatSuiteVersion14		AIAPI_VERSION(14)			// From AI 20.0
#define kAIFileFormatSuiteVersion		kAIFileFormatSuiteVersion14
#define kAIFileFormatVersion			kAIFileFormatSuiteVersion


#define kAIMacFileFormatSuite			"AI Mac File Format Suite"
#define kAIMacFileFormatSuiteVersion	AIAPI_VERSION(4)
#define kAIMacFileFormatVersion			kAIMacFileFormatSuiteVersion


/** @ingroup Callers
	The file format caller.  See \c #AIFileFormatSuite.
	 */
#define kCallerAIFileFormat 				"AI File Format"

/** @ingroup Selectors
	Sent to file format plug-ins to allow the plug-in to show any dialogs necessary
	to gather parameters.
	\li When reading a file this is sent after \c #kSelectorAICheckFileFormat.
	\li Whether reading or writing it is sent before \c #kSelectorAIGoFileFormat.

	Not always sent; for example, when re-saving a document with the Save command,
	only the Go message is sent. In this case, the operation uses the parameters
	from the last time the document was  saved.

	The data is an \c #AIFileFormatMessage.
	 */
#define kSelectorAIGetFileFormatParameters	"AI Get Parameters"

/** @ingroup Selectors
	Sent to file format plug-ins to allow the plug-in to customize import/export
	based on client provided options.
	\li Currently this is not sent during reading a file.
	\li When writing it is sent before \c #kSelectorAIGetFileFormatParameters.

	This is only sent if the client has provided some options to customize
	import/export and the plugin had registered the file format with the
	\c #kFileFormatHasExtendedData option.

	The data is an \c #AIFileFormatMessage.
	 */
#define kSelectorAISetFileFormatParameters	"AI Set Parameters"

/** @ingroup Selectors
	Sent to file format plug-ins to execute the read or write operation.
	\li A read operation creates art according to what is in the specified file
	\li A write operation scans the artwork database and writes out appropriately
		formatted information.

	The data is an \c #AIFileFormatMessage.
	 */
#define kSelectorAIGoFileFormat				"AI Go"

/** @ingroup Selectors
	Sent to file format plug-ins after the user has selected a file,
	to allow a reader to open the file and check for header
	information in order to verify that it can be opened. If your plug-in cannot
	read the specified file, it should return \c #kUnknownFormatErr.

	The data is an \c #AIFileFormatMessage.
	 */
#define kSelectorAICheckFileFormat			"AI Check"

/** @ingroup Selectors
	Obsolete. Linked raster art is now implemented as placed art.
	Sent to file format plug-ins to request an update for a linked object in
	the document. The data is an \c #AIUpdateFileFormatMessage.
	@note Handle this or the legacy versions, \c kAI110SelectorAIUpdateFileFormat,
	kAI130SelectorAIUpdateFileFormat,
		not both.
	   */
#define kSelectorAIUpdateFileFormat			"AI Update AI140"

/** @ingroup Notifiers
	 If a notifier plug-in requests this type of notification, it
	 receives this selector when any open-file action
	 has been completed. See the \c #AINotifierSuite.
	  */
#define kAIFileFormatDocumentOpenedNotifier		"AI File Format Document Opened Notifier"

/** @ingroup Notifiers
	If a notifier plug-in requests this type of notification, it
	receives this selector when Illustrator cannot find a linked file
	for the current document.
	The notification data sent is of type \c #AILinkUpdateNotifyData.
	 */
#define kAIFileFormatLinkUpdateNotifier			"AI File Format Link Update Notifier"


/** These options specify the capabilities of a file format plug-in.
	A subset of options are used with \c #AIFileFormatSuite::AddFileFormat()
	to specify which operations are supported, and are also sent in the
	\c #AIFileFormatMessage	to indicate the requested action.
	Additional options can be set in the Go selector message to provide
	more information about the requested operation.

	  @note The read, embed (import/place), and link operations
		are very similar in execution. In all cases, Illustrator
		creates an empty artwork and send the plug-in a message to
		read the file into the artwork. Special handling is required
		only if the plug-in needs to do different things depending
		on the type of operation; for example the Photoshop file format
		plug-in has options for preserving Photoshop's layers if it is
		not linking.
	*/
enum AIFileFormatOptions {
	/** Read the file, creating artwork in a new document.
		The format is included in the File > Open file types.
		Use when adding a format. */
	kFileFormatRead	=							(1<<0),
	/** Write the documents contents to a file
		in a non-Illustrator format.
		The format is included in the File > Export file types.
		Use when adding a format. */
	kFileFormatExport =							(1<<1),
	/** Write the documents contents to a file
		in a format from which is can be read back into
		Illustrator without loss of data.
		The format is included in the File > Save As file types.
		Use when adding a format.*/
	kFileFormatWrite =							(1<<9),
	/** Read the file and embed artwork to the current document.
		The format is included in the File > Import file types.
		Use when adding a format.*/
	kFileFormatImportArt =						(1<<2),
	/** Read the file and embed artwork to the current document.
		This is the same as \c #kFileFormatImportArt.
		Use when adding a format.*/
	kFileFormatPlaceArt	=						(1<<3),
	/** Allows "Template" to be checked in the Place dialog when
		linking or embedding a file of this type, so the art is
		placed in a template layer.
		Use when adding a format.*/
	kFileFormatConvertTemplate =				(1<<7),
	/** Make a link from the contents of a file to an Illustrator
		document.
		Use when adding a format.*/
	kFileFormatLinkArt =						(1<<8),
	/** Not used. */
	kFileFormatImportStyles =					(1<<4),
	/** When reading, the plug-in sets the print record. See
		\c #AIDocumentSuite::SetDocumentPrintRecord().
		Use when adding a format.*/
	kFileFormatSuppliesPrintRecordOption =		(1<<5),

	/** Makes this the default format for all documents. If specified
		by more than one plug-in, the last one becomes the default.
		Use when adding a format.*/
	kFileFormatIsDefaultOption =				(1<<6),

	/** The plug-in will not respond to the \c #kSelectorAICheckFileFormat
		selector. (For example, the PhotoShop adapter plug-in always returns
		\c #kNoErr.)
		Use when adding a format.*/
	kFileFormatNoAutoCheckFormat =				(1<<10),
	/** Read the file, creating artwork in a new template layer in
		the current document.
		Not used for adding a format. */
	kFileFormatCreateTemplateLayer =			(1<<11),
	/** Handle the extended data passed in a Go message for a placement request
		or in the Set Parameters message for additional options.
		Use when adding a format.*/
	kFileFormatHasExtendedData =				(1<<12),

	/** This file format supplies its own startup objects (colors, patterns,
		and so on), Illustrator does not copy the startup file
		Use when adding a format.*/
	kFileFormatSkipStartupObjectsOption =		(1<<13),

	/** Disable warning dialogs upon read and write.
		Not used for adding a format.*/
	kFileFormatNoWarningOption =				(1<<14),
	/** Write the current document to a copy of the file it was
		loaded from.
		Not used for adding a format. */
	kFileFormatSaveCopyOption =					(1<<15),

	/** Write the contents of selected artwork in a document to a file
		in a non-Illustrator format.
		The format is included in the File > Export Selection file types.
		Use when adding a format. */
	kFileFormatExportSelection =				(1 << 16),

	/**  Enables Batch Export mode which prevents certain actions like:
	1. Prevent individual file format plugins from showing File Replace Dialog.
	2. Prevent individual file format plugins to add exported files to Recent File Menu Items.
	Not used when adding a format. */
	kFileFormatBatchExport		=				(1 << 17),

	/**  Prevent a file format plugin from uniquifying file name.
	Not used when adding a format. */
	kFileFormatSuppressPluginFileNameUniquify = (1 << 18),

	/**  Prevents this file format from appearing in the file
		selection menu of the Open, Place, Save and Export dialogs.
		Use when adding a format. */
	kFileFormatSuppressUI =						(1<<21),
	/** Set in combination with \c #kFileFormatWrite for a
		Save As operation, to distinguish it from Save.
		Not used for adding a format. */
	kFileFormatWriteAs =						(1<<22),

	/** Always receive the Check message, even for operations this plug-in
		does not support. Allows an opportunity to explicitly reject operations
		on files matching this plug-in's type.
		Use when adding a format.*/
	kFileFormatCheckAlways =					(1<<23),

	/** Handle additional parameters passed in \c #AIFileFormatMessage::actionParm.
		These supplement the usual parameters of the file format,
		and may not be complete. Can be used, for instance, for scripting or optimizing.

		If set in the Go message for a plug-in that does not handle the option,
		you can ignore it.
		Not used for adding a format. */
	kFileFormatContainsPartialParameters =		(1<<24),

	/** Import only the SLO composite fonts.
		Do not import artwork or other global objects, and
		do not perform font fauxing.
		Not used for adding a format.*/
	kFileFormatImportCompositeFonts	=			(1<<25),

	/** Treat the file as stationary--that is, open a copy with an Untitled name.
		Use only in conjunction with \c #kFileFormatRead
		Not used for adding a format. */
	kFileFormatOpenUntitledCopy =				(1<<26),

	/** An option for the native (PGF) AI File Format Writer,
		telling it to write out only the indicated palettes and the global objects,
		directly or indirectly. Not used for adding a format. */
	kFileFormatWriteSwatchLibrary =				(1<<27),
	/** An option for the native (PGF) AI File Format Writer,
		telling it to write out only the indicated palettes and the global objects,
		directly or indirectly. Not used for adding a format. */
	kFileFormatWriteBrushLibrary =				(1<<28),
	/** An option for the native (PGF) AI File Format Writer,
		telling it to write out only the indicated palettes and the global objects,
		directly or indirectly. Not used for adding a format. */
	kFileFormatWriteStyleLibrary =				(1<<29),
	/** An option for the native (PGF) AI File Format Writer,
		telling it to write out only the indicated palettes and the global objects,
		directly or indirectly. Not used for adding a format. */
	kFileFormatWriteSymbolLibrary =				(1<<30),
	/** Write the documents contents to a file
		in a format from which it can be read back into
		Illustrator without loss of data.
		The format should be added if this format can be saved 
		in touch workspace.
		Use when adding a format.*/
	kFileFormatWriteInTouch		=				(1<<31)
};

/** Used internally to test for matches to any of the options
	indicating that only specific palettes should be written.
	 */
#define kFileFormatWritePalettesOnly (kFileFormatWriteSwatchLibrary|kFileFormatWriteBrushLibrary|kFileFormatWriteStyleLibrary|kFileFormatWriteSymbolLibrary)


/** Maximum length of the extension string in \c #PlatformAddFileFormatData.
	 */
#define kFileFormatExtensionStrMaxLength		31
/** Maximum length for each extension within the extension string in \c #PlatformAddFileFormatData.
	 */
#define kFileFormatExtMaxLength					5

/** @ingroup Errors
	Plug-in file format does not recognize the file type. Should be returned from
	check-file-format if the file cannot be opened and read.
	 */
#define kUnknownFormatErr						'FMT?'
/** @ingroup Errors
	Plug-in file format recognizes the file type but explicitly disallows processing
	it with the options specified.
	 */
#define kInvalidFormatErr						'FMTi'

/** @ingroup Errors
	Plug-in file format could not complete the operation at current resolution, either
	because the resolution is invalid or its too high. Trying at a lower resolution may
	eliminate this error*/

#define	kBadResolutionErr						'RES!' 

/** File format priorities, which determine the order in which Illustrator
	searches through formats in deciding which one to use to open a file.
	The first format found that handles a file type is used to open the file.
		@see \c #AIFileFormatSuite::SetFileFormatPriority()
	*/
enum AIFileFormatPriority {
	/** Highest priority */
	kAIFileFormatPriorityNative =				10000,
	/** Normal priority. This is the value assigned when a file format is added.  */
	kAIFileFormatPriorityNormal	=				0,
	/** Lowest priority */
	kAIFileFormatPriorityLowest	=				-10000
};


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a file format. Never dereferenced.
	Use the functions in \c #AIFileFormatSuite to access it.*/
typedef struct _t_AIFileFormatOpaque *AIFileFormatHandle;


/** Legacy structure for \c kAIFileFormatVersion4 */
typedef struct PlatformAddFileFormatData4 {
	ai::int32 type;
	unsigned char *title;
	ai::int32 titleOrder;
} PlatformAddFileFormatData4;

/** Information needed to add a file format.
	@see \c  #PlatformAddFileFormatExData. */
typedef struct PlatformAddFileFormatData {
	/** The variable type is the 4 digit Macintosh file type identifier. Windows
		plug-ins can ignore this. */
	ai::int32			type;
	/** The Pascal-type string shown in the file type menu of
		the Save As and Open dialog. */
	unsigned char*	title;
	/** The order of menu items if a plug-in adds multiple file formats.
		Use 0 if the plug-in adds only one filter. */
	ai::int32			titleOrder;
	/** A comma-delimited list of DOS-style extensions that
		are filtered in the Open dialog, or appended to the file name in the
		Saves As dialog. For example, \c "ai,eps".

		The list has a maximum of 31 characters, and each
		extension has a maximum of 5 characters.  */
	const char*			extension;
} PlatformAddFileFormatData;


/** Information needed to add a file format.
	Extends \c #PlatformAddFileFormatData by allowing a list of Mac OS file types. */
typedef struct PlatformAddFileFormatExData {
	/** Number of elements in  \c typeList. */
	ai::int32			numTypes;
	/** Address of list of Mac OS file types. */
	ai::int32*			typeList;
	 /** The Pascal-type string shown in the file type menu of
		the Save As and Open dialog. */
	unsigned char*	title;
	/** The order of menu items if a plug-in adds multiple file formats.
		Use 0 if the plug-in adds only one filter. */
	ai::int32			titleOrder;
	/** A comma-delimited list of DOS-style extensions that
		are filtered in the Open dialog, or appended to the file name in the
		Saves As dialog. For example, \c "ai,eps".

		The list has a maximum of 31 characters, and each
		extension has a maximum of 5 characters.  */
	const char*			extension;
} PlatformAddFileFormatExData;


/** A Mac OS file creator/type pair */
typedef struct AICreatorTypePair {
	/** The file creator. */
	long		creator;
	/** The Mac OS file type */
	ai::int32		type;
} AICreatorTypePair;


////////////////////////////////////////////////////////////////
// Extend File Format Message with
// usage-specific data type.
////////////////////////////////////////////////////////////////

/** Selector for extended file format datatype */
enum eFFExtType {
	/* No additional data required for this request */
	kFFExtNone,
	/* This is a placement request, which requires additional data */
	kFFExtPlaceRequest,
	/*	This is a import/export request, where additional data is
		provided by the client to customize the request */
	kFFExtAdditionalOptions
};

////////////////////////////////////////////////////////////////
// Extended options of plug-ins
////////////////////////////////////////////////////////////////
/** Extended options of various file formats*/
enum AIFFExtendedOptions{
	/* No Extended options is supported*/
	kNoExtendedOptions= (0),
	/* Save/Export of Multiple Artboards is supported */
	kSaveMultiArtboards= (1<<0),
	/** Used internally to request app not to exit "Text Editing Mode" before calling this File format plugin for save/export. */
	kDoNotExitTextEditingModeOption = ( 1 << 1),
	/** Read the file and embed artwork to the current document.
		Use when adding a format, this option should be added 
		if this format can be placed in touch workspace.*/
	kFileFormatPlaceInTouch		=				(1<<2)
};


/** The flags passed by the application to the plugins in the AIFileFormatMessage */
enum eFFOperationOptions{
	/* Save/Export Multiple Artboards selected by the user*/
	kSaveMultiArtboardsSelected= (1<<0),
};

/** Union of extended file format datatypes. */
union FileFormatExtUnion {
	/** Additional options to be used during import/export.
		Entries in the dictionary are file format specific.
		Currently this is used only for SVG export. */
	AIDictionaryRef m_AdditionalOptionsDict;
	/** Additional data needed for a placement request */
	AIPlaceRequestData *m_pPlaceRequestData;
};

/** Extended file format message data. */
typedef struct FileFormatExtData {
	/** The type of union. See \c #eFFExtType for valid values. */
	ai::int32 m_lExtType;
	/** The placement data for a placement request */
	union FileFormatExtUnion m_unExt;
	/** Constructor */
	FileFormatExtData() : m_lExtType(kFFExtNone)
	{
		m_unExt.m_AdditionalOptionsDict = NULL;
	}
} FileFormatExtData;

////////////////////////////////////////////////////////////////
// File Format message structure.
////////////////////////////////////////////////////////////////

/** Message data sent by the file format selectors. */
struct AIFileFormatMessage {
	/** The message data */
	SPMessageData d;
	/** The file format for which the message is intended. If your
		plug-in handles more than one type, compare to the format handle
		returned when the format was added. */
	AIFileFormatHandle fileFormat;

	public:
	/** The requested operation (such as read or write). A logical OR of
		\c #AIFileFormatOptions values. */
	ai::int32 option;
	/** Additional information required for specific operation (currently
		for placement and export). Used if the plug-in registered
		the format as handling extended data (\c #kFileFormatHasExtendedData) */
	FileFormatExtData *m_pExtData;
	/** A pointer to additional parameter data,  if
	\c #kFileFormatContainsPartialParameters is set in the \c option field. */
	void *actionParm;

	private:
	/** The file to read, write or check. Get and set with public functions
		\c #SetFilePath() and \c #GetFilePath(),
		to maintain compatibility with deprecated file spec type. */
	ai::FilePath filePath;

	public:
	/** Use this function to set the file path of the file to read, write, or check
		(allows for deprecated file spec type). */
	void SetFilePath(const ai::FilePath &fp);
	/** Use this function to retrieve the file path of the file to read, write, or check
		(allows for deprecated file spec type). */
	const ai::FilePath &GetFilePath() const;

	public:
	/** Requested save/export file types. Values \c # AIFFExtendedOptions */
	ai::int32 operationOptions;
	/** Handle of the artboard range specified by the user */
	AIArtboardRangeHandle rangeHandle;

	public:
	AIFileFormatMessage() : fileFormat(NULL), option(0), m_pExtData(NULL),
		actionParm(NULL), operationOptions(kNoExtendedOptions), rangeHandle(NULL)
	{}
};

/** Obsolete - linked raster art is now implemented as placed art.
	Message structure for \c #kSelectorAIUpdateFileFormat. */
struct AIUpdateFileFormatMessage {
	/** The message data. */
	struct AIFileFormatMessage ffm;
	/** The art object to be updated. */
	AIArtHandle art;
	/** A pointer to the update data. Not used, always \c NULL. */
	void* data;
};


////////////////////////////////////////////////////////////////
// The following enum and struct can be used to convey
// information in conjunction with the Link Update
// Artwork Notifier.
////////////////////////////////////////////////////////////////
/** The type of link update that triggered
	the \c #kAIFileFormatLinkUpdateNotifier. */
enum eLinkUpdateType {
	/** Perform a normal update. Sent when illustrator detects that 
	a linked file inside an artboard has been updated by an external program. */
	kNormalUpdate,
	/** The link that pointed to a missing file
		was changed to point to a new file. */
	kLinkReplaced,
	/** A link points to a missing file, and has not been
		changed. */
	kMissingLinkIgnored
};

/** Notification data sent with the \c #kAIFileFormatLinkUpdateNotifier. */
struct AILinkUpdateNotifyData {
	/**  The type of link update that occurred, an \c #eLinkUpdateType value. */
	ai::int32 m_iUpdateType;
	/** A pointer to update parameters. Currently unused. */
	void *m_pvParam;
};

/** Document startup profile types, returned by
	\c #AIDocumentSuite::GetDocumentStartupProfile()
	and \c #AIFileFormatSuite::GetFileStartupProfileType().*/
enum AIDocumentStartupProfile
{
	kAIStartupProfileUnknown = 0,
	kAIStartupProfilePrint = 1,
	kAIStartupProfileWeb,
	kAIStartupProfileVideo,
	/* Unused. Not returned. Use \c kAIStartupProfilePrint instead. */
	kAIStartupProfileCMYK,
	/* Unused. Not returned. Use \c kAIStartupProfileWeb instead. */
	kAIStartupProfileRGB,
	kAIStartupProfileMobile
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides functions for creating and managing file-format plug-ins,
	which extend the number of file formats that Illustrator can read and write.

	Reading a format can be transparent to the user; when a file of the
	defined type is selected in the Open dialog, your file format plug-in
	creates artwork in the Illustrator document. If there is a plug-in that writes
	a file format, that format appears in the Save As dialog as an option for the user
	to select. If it is selected, the plug-in walks the artwork tree and writes out
	information on the artwork in the appropriate manner. If your plug-in needs more
	parameters for either reading or writing, it defines a modal dialog to interact
	with the user.

	Plug-ins tell Illustrator about the file formats they
	support by specifying platform file information: the type (such as \c 'ART3')
	in Mac OS, or the extension (such as \c '.AI') in Windows. Plug-ins also indicate
	what read/write capabilities they support.

	One plug-in can register multiple formats. Illustrator handles some parts of the
	file I/O process, and the plug-in does the rest.

	A file-format plug-in receives message actions telling it to:

	\li Check if a file can be read, The Check selector is sent only to plug-ins
		that can read files. It extends the simple type checking done by the  Open dialog.
	\li Ask for parameters.  This selector can be ignored if the plug-in does not need
		user input.
	\li Go. In response, your plug-in executes the read or write operation.

	If a file format plug-in can read, files of its registered file type appear
	in the file list of the Open dialog. In addition to screening by file type,
	Illustrator sends a selector giving a plug-in a chance to check that the
	file can be read. This is useful in the case of text files or files from a
	different file system. If more than one format matches the type, Illustrator
	determines which plug-in should actually open the file, asking the user if necessary.

	If a file format plug-in supports both reading and writing, when reading it should
	store any information about the file needed to write the file back to disk. It can
	store data (for example, the pixel depth of an EPS preview) in the plug-ins globals,
	or in a parameter block. The reference to a block should be attached to the document
	using \c #AIDocumentSuite::SetDocumentFileFormatParameters(). Illustrator keeps this
	parameter-block reference with the document. The plug-in can retrieve it when the
	document is being saved.

	When the user does a Save, by default Illustrator uses the same file format that was
	used to read the file. If the file format does not support writing, the Save As
	dialog appears to let the user choose the save format. All file format plug-ins
	that support saving appear in the format menu of this dialog.

	If you need information from the user to open or save a file, you can present a
	dialog when the ask-for-parameters message is received. When saving files, this
	will be after the Save As dialog has appeared. Your plug-in should save the
	information it collects, keeping it with the document to use for later saves.

	When the go message is received, file formats that read files typically parse
	the input file and create Illustrator artwork using API calls. File formats for
	saving Illustrator artwork traverse the artwork database and write out all
	pertinent information.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIFileFormatSuite and \c #kAIFileFormatVersion.

*/
struct AIFileFormatSuite {

	/** Adds a file format to the standard file dialog.
		Call during startup to install a plug-in file format.
			@param self	A reference to this plug-in, which adds the format.
			@param name	The unique name of the new file format. You can use
				your company name with a descriptor to make it unique.
				Not displayed or localized.
			@param data	Information about the file format.
			@param options File format operations that this plug-in supports.
				A logical OR of these \c #AIFileFormatOptions values:
				\verbatim
kFileFormatRead
kFileFormatImportArt
kFileFormatExport
kFileFormatExportSelection
kFileFormatPlaceArt
kFileFormatImportStyles
kFileFormatSuppliesPrintRecordOption
kFileFormatIsDefaultOption
kFileFormatConvertTemplate
kFileFormatLinkArt
kFileFormatWrite
kFileFormatNoAutoCheckFormat
kFileFormatSkipStartupObjectsOption
kFileFormatHasExtendedData
kFileFormatSuppressUI
kFileFormatCheckAlways
\endverbatim
			@param fileFormat [out] A buffer in which to return  the handle of
				the new plug-in file format. If you install multiple file formats,
				store this reference in the plug-ins \c globals record, so that your
				plug-in can use it to determine which file format command is to be processed.
				@param extendedOptions File format extended operations that this plug-in supports. A logical OR of these \c #AIFFExtendedOptions values:                        
				\verbatim
				kNoExtendedOptions
				kSaveMultiArtboards
				kFileFormatPlaceInTouch
				\endverbatim


			@see \c #AddFileFormatEx()
	*/
	AIAPI AIErr (*AddFileFormat) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatData *data, ai::int32 options, AIFileFormatHandle *fileFormat ,  ai::int32 extendedOptions);

	/** Retrieves the name of a file format.
			@param fileFormat The file format.
			@param name [out] A buffer in which to return the name string, as
				passed to \c #AddFileFormat(). Do not modify this string.
		*/
	AIAPI AIErr (*GetFileFormatName) ( AIFileFormatHandle fileFormat, const char **name );

	/** Retrieves the option flags of a file format.
			@param fileFormat The file format.
			@param options [out] A buffer in which to return the options, a logical OR of
				\c #AIFileFormatOptions values
		*/
	AIAPI AIErr (*GetFileFormatOptions) ( AIFileFormatHandle fileFormat, ai::int32 *options );

	/** Sets the option flags of a file format, which specify what file operations can be handled.
			 @param fileFormat The file format.
			 @param options The options, a logical OR of \c #AIFileFormatOptions values
	*/
	AIAPI AIErr (*SetFileFormatOptions) ( AIFileFormatHandle fileFormat, ai::int32 options );

	/** Retrieves a reference to the plug-in that installed a file format,
		to be passed to \c #AIPluginSuite functions.
			@param fileFormat The file format.
			@param plugin [out] A buffer in which to return the plug-in reference.
		*/
	AIAPI AIErr (*GetFileFormatPlugin) ( AIFileFormatHandle fileFormat,
				SPPluginRef *plugin );

	/** Gets the number of installed plug-in file formats.
		Use with \c #GetNthFileFormat() to iterate through all plug-in formats.
			@param count [out] A buffer in which to return the number of formats.
		*/
	AIAPI AIErr (*CountFileFormats) ( ai::int32 *count );

	/** Retrieves a plug-in file format reference by position index.
		Use with \c #CountFileFormats() to iterate through all installed formats.
			@param n The index, in the range <code>[1..numFormats]</code>.
			@param fileFormat [out] A buffer in which to return the file format reference.

		*/
	AIAPI AIErr (*GetNthFileFormat) ( ai::int32 n, AIFileFormatHandle *fileFormat );

	/** Retrieves the file extension for a plug-in file format.
			@param fileFormat The file format.
			@param extension [out] A buffer in which to return the file extension string.
		*/
	AIAPI AIErr (*GetFileFormatExtension) ( AIFileFormatHandle fileFormat, char *extension );

	/** Adds a plug-in file format. This extended version allows you to specify
		a list of Mac OS file types. Call during startup to install a plug-in file format.
			@param self	A reference to this plug-in, which adds the format.
			@param name	The unique name of the new file format. You can use
				your company name with a descriptor to make it unique.
				Not displayed or localized.
			@param dataEx	Information about the file format. This extended version
				uses a data structure with additional fields that allow you to
				specify a list of Mac OS file types. Use \c #SetFileFormatFilter()
				to specify a creator/type pair as the file filter.
			@param options File format operations that this plug-in supports.
				A logical OR of \c #AIFileFormatOptions values.
				When the format is called with a Go selector,
				one of these flags is set in the \c option field to indicate the
				requested operation.
			@param fileFormat [out] A buffer in which to return  the handle of
				the new plug-in file format. If you install multiple file formats,
				store this reference in the plug-ins \c globals record, so that your
				plug-in can use it to determine which file format command is to be processed.
				@param extendedOptions File format extended operations that this plug-in supports. A logical OR of these \c #AIFFExtendedOptions values:                        
				\verbatim
				kNoExtendedOptions
				kSaveMultiArtboards
				kFileFormatPlaceInTouch
				\endverbatim
				
			@see \c #AddFileFormat(), \c #SetFileFormatFilter()
		*/
	AIAPI AIErr (*AddFileFormatEx) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatExData *dataEx, ai::int32 options, AIFileFormatHandle *fileFormat, ai::int32 extendedOptions );

	/** Retrieves the localizable display name of a plug-in file format.
			@param fileFormat The file format.
			@param szTitle [out] A buffer in which to return the display name.
		*/
	AIAPI AIErr (*GetFileFormatTitle) ( AIFileFormatHandle fileFormat, char *szTitle );

	/** Retrieves the Mac OS file types for a plug-in file format.
			@param fileFormat The file format.
			@param maxNumTypes [in, out] A buffer in which to specify the maximum number
				and return the actual number of values in \c typeList.
			@param typeList [out] A buffer in which to return the 4-character Mac OS type codes.
			@see \c #GetFileFormatCreatorType()	to get the full Mac OS file information.
		*/
	AIAPI AIErr (*GetFileFormatType) ( AIFileFormatHandle fileFormat, ai::int32 *maxNumTypes, ai::int32 *typeList );

	/** Associates a file format with a file type filter. File types are specified by (creator, type)
		pairs in Mac OS, and by filename extensions in Windows.
		@note This function extends the \c #AddFileFormat() and \c #AddFileFormatEx() functions
		by allowing filters based on (creator, type) pairs in Mac OS, rather than simple type values.
			@param fileFormat The file format.
			@param numPairs In Mac OS, the number of (creator, type) pairs specified in \c pairList.
				Ignored in Windows.
			@param pairList In Mac OS, a pointer to an array of (creator, type) pairs. These can use
				the Mac OS wild-card value '****' for creator or type. Ignored in Windows.
			@param extensions In Windows, a comma-delimited list of DOS-style extensions that
				are filtered in the Open dialog, or appended to the file name in the
				Saves As dialog. For example, \c "ai,eps".
		*/
	AIAPI AIErr (*SetFileFormatFilter) ( AIFileFormatHandle fileFormat, ai::int32 numPairs, AICreatorTypePair *pairList, const char* extensions );

	/** Retrieves the file type filter for a file format, as specified by (creator, type)
		pairs for Mac OS.
			@param fileFormat The file format.
			@param maxNumTypes [in, out] A buffer in which to specify the maximum number
				and return the actual number of (creator, type) pairs specified in \c pairList.
			@param pairList [out] A buffer in which to return the array of (creator, type) pairs.
		*/
	AIAPI AIErr (*GetFileFormatCreatorType) ( AIFileFormatHandle fileFormat, ai::int32 *maxNumPairs, AICreatorTypePair *pairList );

	/** Invokes the File > Save dialog, allowing you to filter the available file formats.
			@param options Limits available file formats to those that support these
				write operations. A logical OR of write operation constants:<br>
				\c #kFileFormatExport<<br>
				\c #kFileFormatWrite
			@param dlgTitle	The title for the Save dialog.
			@param fileSpec	[in, out] A buffer in which to pass the initial file specification
				and return the user-chosen specification.
			@param fileFormat [out] A buffer in which to return the user-chosen file format.
			@param good	[out] A buffer in which to return true if the user clicked Save,
				or false if the user clicked Cancel.
	  */
	AIAPI AIErr (*PutFile) (ai::int32 options, const unsigned char *dlgTitle, ai::FilePath &fileSpec, AIFileFormatHandle *fileFormat, AIBoolean *good );

	/** Sets the priority of a file format. which determines the order in which Illustrator
		searches through formats in deciding which one to use to open a file. The first format
		found that handles a file type is used to open the file.
			@param fileFormat The file format.
			@param priority The new priority, an \c #AIFileFormatPriority value,
		*/
	AIAPI AIErr (*SetFileFormatPriority) ( AIFileFormatHandle fileFormat, ai::int32 priority );

	/** Finds all plug-in file formats that can perform a specified operation for a file.
			@param options The operation, a \c #AIFileFormatOptions value.
			@param file	The file.
			@param maxMatches The maximum number of formats to return.
			@param matchingFormats [out] An array of size \c maxMatches in which to return the matching file formats.
			@param numMatches [out] A buffer in which to return the number of matching file formats found.
		*/
	AIAPI AIErr (*FindMatchingFileFormats) ( ai::int32 options, const ai::FilePath &file, ai::int32 maxMatches, AIFileFormatHandle matchingFormats[], ai::int32* numMatches );

	/** Obsolete */
	AIAPI AIErr (*ResolveImportConflicts) ();

	/** Reports the version of Illustrator in which a raster file
		format, for example the JPEG file format plug-in, was converted from
		using raster art to using placed art in order to perform a place link
		operation. The information is needed so that Illustrator knows when it
		should convert placed linked art back to raster art when saving to a
		legacy file format. For example, if the JPEG file format used raster art
		in version 10 and started using placed art in version 11 then
		Illustrator must convert placed linked JPEG images back to raster art
		when saving to a version 10 or earlier Illustrator file.
		(Note that this function returns a version value, not an error code.)
			@param fileFormat The file format.
			@return The Illustrator version. The default version is 0,
				meaning that placed objects are not converted on export.
			@see \c #SetFirstVersionUsingPlacedArt() to set the version.
		*/
	AIAPI AIVersion (*GetFirstVersionUsingPlacedArt) (AIFileFormatHandle fileFormat);

	/** Sets the version of Illustrator in which a raster file
		format was converted from using raster art to using placed art
		in order to perform a place link operation.
			@param fileFormat The file format.
			@param The Illustrator version value. The default version is 0,
				meaning that placed objects are not converted on export.
			@see \c #GetFirstVersionUsingPlacedArt().
		*/
	AIAPI AIErr (*SetFirstVersionUsingPlacedArt) (AIFileFormatHandle fileFormat, AIVersion version);

	/** Retrieves the Illustrator startup profile type from the XMP metadata embedded in a file.
			@param file  The file path.
			@param docStartupProfile [out] A buffer in which to return the Illustrator
				startup profile constant.  If the information is not in the metadata,
				or if the file does not contain XMP metadata, this is \c #kAIStartupProfileUnknown.
			@return  The error \c #kBadParameterErr if file is empty or does not exist.
		*/
	AIAPI AIErr (*GetFileStartupProfileType) (const ai::FilePath &file, AIDocumentStartupProfile *docStartupProfile);

	/** Retrieves the Illustrator default document profile from the startup-profile type.
			@param docStartupProfile The startup profile type.
			@param profile [out] A buffer in which to return the file-path object for the default document profile.
			@return	The error \c #kCantHappenErr if the file does not exists. <br>
					The error \c #kBadParameterErr if the startup profile is invalid,
	*/
	AIAPI AIErr (*GetStartupFileOfType) (const AIDocumentStartupProfile docStartupProfile, ai::FilePath &profile);

	/** Retrieves the extended option flags of a file format.
		@param fileFormat The file format.
		@param extendedOptions [out] A buffer in which to return the extended options
		\c #AIFFExtendedOptions values
			\verbatim
			kNoExtendedOptions
			kSaveMultiArtboards
			kFileFormatPlaceInTouch
			\endverbatim
	*/
	AIAPI AIErr (*GetFileFormatExtendedOptions) ( AIFileFormatHandle fileFormat, ai::int32 *extendedOptions );

	/** Sets the extended option flags of a file format, which specify what file operations can be handled.
		@param fileFormat The file format.
		@param extendedOptions File format operations that this plug-in supports. A logical OR of these 
		\c #AIFFExtendedOptions values:                        
			\verbatim
			kNoExtendedOptions
			kSaveMultiArtboards
			kFileFormatPlaceInTouch
			\endverbatim
	*/
	AIAPI AIErr (*SetFileFormatExtendedOptions) ( AIFileFormatHandle fileFormat, ai::int32 extendedOptions);

	/** Used for exporting the current document as one whole file or as multiple artBoards
	@param actionParam An action parameter block containing keys "name", "frmt", "ext", "smab", "sall", "sran" as defined in AIDocumentAction.h
	Will return error (and not throw a dialog) if the above action keys are missing.
	*/
	AIAPI AIErr(*GoExport) (AIActionParamValueRef actionParam);
} ;


/** @deprecated. Obsolete platform-specific functions.	Use functions in \c #AIFileFormatSuite. */
typedef struct {

	AIAPI AIErr (*MacXGetFileFormatTitle) ( AIFileFormatHandle fileFormat, unsigned char *title );
	AIAPI AIErr (*MacXSetFileFormatTitle) ( AIFileFormatHandle fileFormat, const unsigned char *title );
	AIAPI AIErr (*MacXGetFileFormatType) ( AIFileFormatHandle fileFormat, ai::int32 *type );
	AIAPI AIErr (*MacXSetFileFormatType) ( AIFileFormatHandle fileFormat, ai::int32 type );

} AIMacFileFormatSuite;


#include "AIHeaderEnd.h"

/*******************************************************************************
 **
 **	Inline members
 **
 **/
inline void AIFileFormatMessage::SetFilePath(const ai::FilePath &fp)
{
	filePath = fp;
}

inline const ai::FilePath &AIFileFormatMessage::GetFilePath() const
{
	return filePath;
}

#endif
