#ifndef __AIAssetMgmt__
#define __AIAssetMgmt__

/*
 *        Name:	AIAssetMgmt.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Asset Management Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1999-2007 Adobe Systems Incorporated.
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

#include "IAIFilePath.hpp"

#include "AIHeaderBegin.h"

/** @file AIAssetMgmt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIAssetMgmtSuite				"AI Asset Management Suite"
#define kAIAssetMgmtSuiteVersion9		AIAPI_VERSION(9)
#define kAIAssetMgmtSuiteVersion		kAIAssetMgmtSuiteVersion9
#define kAIAssetMgmtVersion				kAIAssetMgmtSuiteVersion

/** @ingroup Notifiers */
#define kAILaunchProjectBridgeNotifier	"AI Launch Project Bridge Notifier"

/** Metadata selectors for \c #AIAssetMgmtSuite::UpdateDynamicMetadata(),
	controls the types of metadata that are updated. */
enum AIXMPMetadataSelector {
	/** Generate the default XMP metadata */
	kAIXMPDefault				= 0x00000000,
	/** Preserve the original DocumentID (128-bit uuid), rather than creating a new one. */
	kAIXMPPreserveDocumentID	= 0x00000001,
	/** Do not generate page info metadata */
	kAIXMPNoPageInfo			= 0x00000002,
	/** Do not generate document swatches metadata */
	kAIXMPNoDocumentSwatches	= 0x00000004,
	/** Do not generate ink plate usage data */
	kAIXMPNoPlateUsages			= 0x00000008,
	/** Do not generate used-font metadata */
	kAIXMPNoUsedFonts			= 0x00000010,
	/** Do not generate XMP thumbnail metadata */
	kAIXMPNoThumbnail			= 0x00000020
};


/*******************************************************************************
 **
 **	Types
 **
 **/
/** The XMP session object, which allows you to manipulate metadata in the XMP buffer.
You must have XMP data to create a session object.
	*/
typedef struct _AIXMPSession *AIXMPSession;

/** Information for updating XMP metadata using \c #AIAssetMgmtSuite::UpdateDynamicMetadataFields()
 */
typedef struct AIXMPDataFieldMap {
    /** Name of the XMP property, such as "CreateDate", "CreatorTool", "Format" */
    const char *name;
    /** New value of the XMP property. A null pointer value means to
        remove the XMP property from the XMP packet if the \c replace flag is true;
        for example, to remove the XMP "Thumbnails" data from the original packet. */
    const char *value;
    /** When true, reset the value of the XMP property if it already
        exists in the input XMP metadata buffer. */
	AIBoolean	replace;
} AIXMPDataFieldMap;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides simple XMP metadata manipulation routines and
	Adobe Version Cue(TM) functionality.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIAssetMgmtSuite and \c #kAIAssetMgmtVersion.
*/

typedef struct AIAssetMgmtSuite {
	/** Reports whether Version Cue is enabled.
		(Note that this function returns a boolean value, not an error code.)
			@return True if Version Cue is enabled.
    */
	AIAPI AIBoolean (*IsAssetMgmtEnabled)();

	/** Updates XMP metadata. Creates a new XMP metadata buffer.
			@param xapIn The buffer containing the XMP metadata for the current document.
			@param fields A pointer to an array of structures containing the
				new or changed metadata property name/value pairs.
			@param length The number of structures in \c fields.
			@param xapOut [out] A buffer in which to return the new XMP metadata.
				The caller is responsible for allocating and releasing the returned output buffer.
        @note For details of the XMP properties, see the Adobe "XMP Specification",
        @see \c  #AIDocumentSuite::GetDocumentXAP(), \c #AIDocumentSuite::SetDocumentXAP()
        for getting and setting the XMP metadata buffer for the current document.
    */
	AIAPI AIErr (*UpdateDynamicMetadataFields) (const char *xapIn,
		const AIXMPDataFieldMap *fields, const ai::int32 length,
												char **xapOut);

	/** Used internally to update the current document's XMP metadata.
			@param mimeType	 The MIME type of the file being updated.
				Updates the "Format" property.
			@param managedURL The URL of the file being updated, or \c NULL
				for local (unmanaged) files.Updates the "ManageTo" field of \c kXMP_NS_XMP_MM namespace.
			@param metadataSelectors A logical OR of \c #AIXMPMetadataSelector constants
				that specifies which types of metadata to update.
  		*/
	AIAPI AIErr (*UpdateDynamicMetadata) (const char *mimeType, const char* managedURL /* = NULL */, ai::uint32 metadataSelectors);

	/** @deprecated
		Used internally. Progress callback for Version Cue network operations.
	    	@return True to continue the operation, false to cancel.
    */
	AIAPI AIBoolean (*Progress) ( ai::int32 bytesTransferred, ai::int32 contentLength,
								  char *server, char *uri, char *method,
								  char *contentType, const ai::FilePath &localFile);
	/** @deprecated
		Creates a new XMP session, which you can use to manipulate XMP metadata for the current document.
			@param xmpIn A buffer containing the UTF-8 encoded XMP metadata for the current document.
					If null, a session object is still created and can be used with \c #SetProperty().
			@param xmp [out] A buffer in which to return the new XMP session object.
			@return The error \c #kBadParameterErr for any failure, including insufficient memory.
			@see \c  #AIDocumentSuite::GetDocumentXAP()
	*/
	AIAPI AIErr (*CreateXMPSession) (const char *xmpIn , AIXMPSession* xmp);

	/** @deprecated
		Frees memory associated with the XMP session object that is no longer needed.
			@param xmp The session object, as returned by \c #CreateXMPSession().
				Upon return, this reference is no longer valid.*/
	AIAPI AIErr (*DisposeXMPSession) (AIXMPSession xmp);

	/** @deprecated
		Gets the size of an XMP session object. Use this size to allocate memory before
		calling \c #GetXMPSessionBuffer().
			@param xmp The XMP session object.
			@param xmpSize [out] A buffer in which to return the number of bytes in the session buffer.
		*/
	AIAPI AIErr (*GetXMPSessionSize) (AIXMPSession xmp , int* xmpSize);

	/** @deprecated
	Retrieves the buffer of the XMP session object.
			@param xmp The XMP session object.
			@param xmpOUT [out] A buffer in which to return the session buffer. Allocate sufficient memory using
				\c #GetXMPSessionSize().
		*/
	AIAPI AIErr (*GetXMPSessionBuffer) (AIXMPSession xmp , char *xmpOut);

	/** @deprecated
		Gets the size of an XMP key value. Use this size to allocate memory before
		calling \c #GetProperty().
			@param xmp The XMP session object.
			@param nameSpace The XMP namespace for the desired property.
			@param key The key name for the desired property.
			@param valueSize [out] A buffer in which to return the number of bytes in the key value.
			@return The error \c kNoSuchKey if key does not exist.
		*/
	AIAPI AIErr (*GetPropertySize) (AIXMPSession xmp, const char *nameSpace, const char* key, ai::int32* valueSize);

	/** @deprecated
		Retrieves the value of an XMP property.
			@param xmp The XMP session object.
			@param nameSpace The XMP namespace for the desired property.
			@param key The key name for the desired property.
			@param value [out] A buffer in which to return the value. Allocate sufficient memory using
				\c #GetPropertySize().
		*/
	AIAPI AIErr (*GetProperty) (AIXMPSession xmp, const char *nameSpace, const char* key , char* value);

	/** @deprecated
		Sets the value of an XMP property.
			@param xmp The XMP session object.
			@param nameSpace The XMP namespace for the desired property.
			@param key The key name for the desired property.
			@param value The new value.
		*/
	AIAPI AIErr (*SetProperty) (AIXMPSession xmp, const char *nameSpace, const char* key , const char* value);

	/** @deprecated
		Removes a property from XMP metadata.
			@param xmp The XMP session object.
			@param nameSpace The XMP namespace for the property.
			@param key The key name for the property.
		*/
	AIAPI AIErr (*DeleteProperty) (AIXMPSession xmp, const char *nameSpace, const char* key);

	//  Currently used by StockPhoto.
	/** Shows the FileInfo dialog for an XMP packet.
			@param xmpIn The current XMP metadata packet.
			@param xmpOUT [out] A buffer in which to return the  new XMP packet,
				allocated by \c #SPBasicSuite::AllocateBlock(). Caller must free memory when no longer needed.
			 	If \c NULL, the function shows a read-only FileInfo dialog.
			@param dialogTitle A UTF-8 title string for the dialog, typically the name of the artwork
				associated with the metadata. If a \c NULL pointer, the default title is "File Info".

		@note The function does not check whether UserInteraction is on or off, the caller must do so..
	*/
	AIAPI AIErr (*ShowMetadataDialog) (const char *xmpIn, char **xmpOut, const char *dialogTitle);
} AIAssetMgmtSuite;

#include "AIHeaderEnd.h"


#endif
