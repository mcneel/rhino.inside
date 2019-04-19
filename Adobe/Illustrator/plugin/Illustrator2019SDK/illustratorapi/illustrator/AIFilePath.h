#ifndef __AIFilePath__
#define __AIFilePath__

/*
 *        Name:	AIFilePath.h
 *     Purpose:	Adobe Illustrator File Path Suite.
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

#include "IAIFilePath.hpp"

#include "AIHeaderBegin.h"

/** @file AIFilePath.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIFilePathSuite			"AI File Path Suite"

#define kAIFilePathSuiteVersion		AIAPI_VERSION(6)

#define kAIFilePathVersion			kAIFilePathSuiteVersion

/** @ingroup Suites
	Provides cross-platform file referencing.  Use the \c ai::FilePath
	wrapper class rather than calling these functions directly.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIFilePathSuite and \c #kAIFilePathVersion.
*/
struct AIFilePathSuite
{
	/** Creates a new, empty file path object.
			@param path [out] A buffer in which to return the
				file path object.
		*/
	AIErr AIAPI (*NewFilePath)(ai::FilePath &path);

	/** Disposes of a file path object. Does not affect the referenced file.
			@param path The file path object.
		*/
	AIErr AIAPI (*DeleteFilePath)(ai::FilePath &path);

	/** Copies a file path object. Does not affect the referenced file.
			@param src The file path object to copy.
			@param dest  [out] A buffer in which to return the
				new file path object, which references the same file.
		*/
	AIErr AIAPI (*Copy)(const ai::FilePath &src, ai::FilePath &dest);

	/** Reports whether a file path object references a file.
		(Note that this function returns a boolean value, not an error code.)
			@param path The file path object.
			@return True if the object is empty (does not reference a file).
		*/
	AIBool8 AIAPI (*IsEmpty)(const ai::FilePath &path);

	/** Sets a file path object to reference a null path.
		(Note that this function has no return value.)
		   	@param path The file path object.
		*/
	void AIAPI (*MakeEmpty)(ai::FilePath &path);


	/** Reports whether two file path object reference the same file,
		regardless of whether that file exists.
		(Note that this function returns a boolean value, not an error code.)
			@param a The first file path object.
			@param b The second file path object.
			@param resolveLinks When true, determine if the two objects refer to the
				same file through links, aliases, or shortcuts by querying the
				file system.
			@return True if the objects are identical, or if \c resolveLinks is true
				and the objects reference the same file.
				<br> False if \c resolveLinks is false and the objects are not identical,
					or if \c resolveLinks is true and the objects reference different files,
		*/
	AIBool8 AIAPI (*Equal)(const ai::FilePath &a, const ai::FilePath &b, const AIBool8 resolveLinks);

	/** Reports whether one file path string is before another, alphabetically.
		(Note that this function returns a boolean value, not an error code.)
			@param a The first file path object.
			@param b The second file path object.
			@return True if a < b in a string comparison of file path names.
	*/
	AIBool8 AIAPI (*LessThan)(const ai::FilePath &a, const ai::FilePath &b);

	/** Reports whether a file path string starts with a delimiter.
		(Note that this function returns a boolean value, not an error code.)
			@param path The file path object.
			@return True if the file path name starts with a delimiter.
	*/
	AIBool8 AIAPI (*StartsWithDelimiter)(const ai::FilePath &path);

	/**  Reports whether a file path string ends with a delimiter.
			@param path The file path object.
			@return True if the file path name ends with a delimiter.
	*/
	AIBool8 AIAPI (*EndsWithDelimiter)(const ai::FilePath &path);

	/** Adds a component to the path of a file path object, inserting the appropriate
		delimiter character as necessary. Does not add a delimiter at the end
		unless it is explicitly specified in the \c addend string.
			@param addend The component to  add.
			@param augend [in, out] The file path object.
	*/
	AIErr AIAPI (*AddComponent)(const ai::UnicodeString &addend, ai::FilePath &augend);

	/** Removes the end component from the path of a file path object.
		(Note that this function has no return value.)
		   	@param path The file path object.
		*/
	void AIAPI (*RemoveComponent)(ai::FilePath &path);

	/** Adds a file extension to the path of a file path object.
		Adds or ignores dots as needed so that one dot appears before the extension.
		(Note that this function has no return value.)
			@param ext The extension string.
		   	@param path [in, out] The file path object.
		*/
	void AIAPI (*AddExtension)(const ai::UnicodeString &ext, ai::FilePath &path);

	/** Removes the file extension from the path of a file path object.
 		(Note that this function has no return value.)
 		   	@param path [in, out] The file path object.
		*/
	void AIAPI (*RemoveExtension)(ai::FilePath &path);

	/** Reports whether the file or directory referenced by a file path object
		exists in the file system.
		(Note that this function returns a boolean value, not an error code.)

		@param path			The file path object.
		@param resolveLinks	When true, resolve links, aliases, and shortcuts for \c longPath.
		@param longPath		[out] Optional. A buffer in which to return a full long, Unicode version
			of the path. Use to convert short path names to their long counterparts. Can be null.
			Returns undefined if the file or directory does not exist.
		@param isFile		[out] Optional. A buffer in which to return true if the object
			references an existing file, false if it references an existing directory. Can be null.
			Returns undefined if the file or directory does not exist.
		@return True if the referenced file or directory exists.
	*/
	AIBool8 AIAPI (*Exists)(const ai::FilePath &path, const AIBool8 resolveLinks,
								ai::UnicodeString *longPath, AIBool8 *isFile);

	/**	Resolves an alias or shortcut by querying the file system.
		The referenced file or directory must exist.
			@param path [in, out] The file path object to resolve and return.
				Upon return, the path object points directly to the target file.
		*/
	AIErr AIAPI (*Resolve)(ai::FilePath &path);

	/*****************************************************************************/
	/* Set operations */

	/** Sets a file path from a Unicode string.
			@param pathString The new path, can be a path native to Windows, UNIX, or Mac OS, or a URL.
			@param expandName When true, the function attempts to expand the
				provided path string into a full name (for example, for	a short,
				truncated name in Windows).
			@param path The file path object.
	*/
	AIErr AIAPI (*Set)(const ai::UnicodeString &pathString, AIBool8 expandName, ai::FilePath &path);

	/** Sets a file path from a file specification.
			@param file The new file.
			@param path The file path object.
	*/
	void AIAPI (*SetFromSPFileRef)(const SPPlatformFileReference&, ai::FilePath &path);

	#ifdef MAC_ENV

	/** Sets a file path from a \c CFString string specification (in Mac OS only).
			@param string The new path.
			@param path The file path object.
	*/
	AIErr AIAPI (*SetFromCFString)(const CFStringRef, ai::FilePath &path);

	/** Sets a file path from an \c FSRef file specification (in Mac OS only).
			@param file The new file.
			@param path The file path object.
	*/
	AIErr AIAPI (*SetFromFSRef)(const FSRef&, ai::FilePath &path);

	/** Sets a file path from an \c CFURL URL specification (in Mac OS only).
			@param url The new URL.
			@param path The file path object.
	*/
	void AIAPI (*SetFromCFURL)(const CFURLRef, ai::FilePath &path);

	#endif	// MAC_ENV

	/*****************************************************************************/
	/* Get operations */

	/**	Retrieves the file name from a file path object. Includes the extension, if any, but
		does not include the path.
			@param path			The file path object
			@param displayName	When true, get the display name. Attempts to translate a
				truncated short name to the full name.
			@param fileName		[out] A buffer in which to return the file name string.
	*/
	AIErr AIAPI (*GetFileName)(const ai::FilePath &path, const AIBool8 displayName, ai::UnicodeString &fileName);

	/**	Retrieves the file name from a file path object, without any extension or path.
			@param path			The file path object
			@param fileNameNoExt [out] A buffer in which to return the file name string.
		*/
	AIErr AIAPI (*GetFileNameNoExt)(const ai::FilePath &path, ai::UnicodeString &fileNameNoExt);

	/**	Retrieves the file extension from a file path object. Does not include the dot.
			@param path		The file path object
			@param ext		[out] A buffer in which to return the file extension string.
		*/
	AIErr AIAPI (*GetFileExtension)(const ai::FilePath &path, ai::UnicodeString &ext);

	/**	Retrieves the full path from a file path object, in platform-specific notation.
			@param path			The file path object
			@param displayName	When true, get the display name. Attempts to translate a
				truncated short name to the full name.
			@param fullPath		[out] A buffer in which to return the path string.
	*/
	AIErr AIAPI (*GetFullPath)(const ai::FilePath &path, const AIBool8 displayName, ai::UnicodeString &fullPath);

	/**	Retrieves the directory or folder from a file path object, in platform-specific notation.
		The string ends with a delimiter. If the path represents a directory or folder, this
		result is the same as for \c #GetFullPath().
			@param path			The file path object
			@param displayName	When true, get the display name. Attempts to translate a
				truncated short name to the full name.
			@param directory	[out] A buffer in which to return the directory name string.
		*/
	AIErr AIAPI (*GetDirectory)(const ai::FilePath &path, const AIBool8 displayName, ai::UnicodeString &directory);

	/**	Retrieves the short version of the path from a file path object, in platform-specific notation.
		The referenced file or folder must exist.
			@param path			The file path object
			@param shortPath	[out] A buffer in which to return the path string, or an
				empty string in case of error..
				\li In Windows, conforms to 8.3 format.
				\li In Mac OS X, name can be truncated and a file ID appended.
					If the file ID is needed, the path is not valid across processes.
		*/
	AIErr AIAPI (*GetShortPath)(const ai::FilePath &path, ai::UnicodeString &shortPath);

	/**	Retrieves the parent directory or folder for a file path object, as a file path object.
		If the path is a directory, retrieves its parent directory. Does not access the file system.
		Use \c #Exists() or \c #Resolve() to ensure a path is valid.
			@param path		The file path object.
			@param parent	[out] A buffer in which to return the path object for the parent.
				Can be the same instance passed in, in which case it is modified to
				reference the parent. Returns an empty path if the given path is
				for a top-level volume.
		*/
	AIErr AIAPI (*GetParent)(const ai::FilePath &path, ai::FilePath &parent);

	/**	Retrieves the path component delimiter for the current platform.
		(Note that this function returns a character, not an error code.
			@return The delimiter character ("/" or "\"),
		*/
	char AIAPI (*GetDelimiter)(void);

	#ifdef MAC_ENV
	/** Retrieves the volume and parent of a file path (in Mac OS only).
		(Note that this function does not return an error code.)
			@param path The file path object.
			@param vol [out] A buffer in which to return the volume. Can be \c null.
			@param parent [out] A buffer in which to return the parent. Can be \c null.
	*/
	void AIAPI (*GetVolumeAndParent)(const ai::FilePath &path, FSVolumeRefNum *vol, ai::uint32 *parent);
	#endif

	/** Retrieves the file creator and type of a file path as a four-character code
		(in Mac OS only, outside Illustrator core).
			@param path The file path object.
			@param creator [out] A buffer in which to return the creator code.
			@param type [out] A buffer in which to return the type code.
	*/
	AIErr AIAPI (*GetCreatorAndType)(const ai::FilePath &path, ai::uint32 *creator, ai::uint32 *type);

	/**	Retrieves the path as a URL from a file path object. The URL contains only ASCII characters
		and special characters escaped with URL percent (\\%) encoding.
			@param path		The file path object
			@param displayName	When true, get the display name. Attempts to translate a
				truncated short name to the full name.
			@param url		[out] A buffer in which to return the URL string.
	*/
	AIErr AIAPI (*GetAsURL)(const ai::FilePath &path, const AIBool8 displayName, ai::UnicodeString &url);

	/**	Retrieves the path as a file specification from a file path object.
			@param path	The file path object
			@param spPlatformFileSpec [out] A buffer in which to return the file specification.
	*/


	AIErr AIAPI (*GetAsSPPlatformFileRef)(const ai::FilePath &path, SPPlatformFileReference &spPlatformFileRef);

	/**	Retrieves the path as a file specification from a file path object.
	@param path	The file path object
	return if file path is on network or not.
	*/
	AIBoolean AIAPI(*IsOnNetwork)(const ai::FilePath &path);

	#ifdef MAC_ENV

	/** Retrieves a file path as a \c CFString string specification (in Mac OS only).
		(Note that this function returns a string value, not an error code.)
			@param path The file path object.
			@return The path string. The caller is responsible for releasing it.
	*/
	CFStringRef AIAPI (*GetAsCFString)(const ai::FilePath &path);

	/** Retrieves a file path as an \c FSRef file specification (in Mac OS only).
		(Note that this function returns an OS status value, not an error code.)
			@param path The file path object.
			@param fsRef [out] A buffer in which to return the file specification.
			@return The OS status.
	*/
	OSStatus AIAPI (*GetAsFSRef)(const ai::FilePath &path, FSRef &fsRef);

	/** Retrieves a file path as a \c CFURL specification (in Mac OS only).
		(Note that this function returns a string value, not an error code.)
			@param path The file path object.
			@return The URL specification.
	*/
	CFURLRef AIAPI (*GetAsCFURL)(const ai::FilePath &path);

	#endif	// MAC_ENV

	/** Resets the volume cache. Does not return an error code. */
	void AIAPI (*ResetVolumeCache)(void);
    
#ifdef MAC_ENV
#ifdef __OBJC__
    
    NSString*   AIAPI (*GetAsNSString)                  (const ai::FilePath &path);
    
    NSURL*      AIAPI (*GetAsNSURL)                     (const ai::FilePath &path);
    
    NSData*     AIAPI (*GetAsBookmarkData)              (const ai::FilePath &path, const ai::FilePath& inRelativeToPath, NSError** outError );
    
    NSData*     AIAPI (*GetAsMinimalBookmarkData)       (const ai::FilePath &path, const ai::FilePath& inRelativeToPath, NSError** outError );
    
    BOOL        AIAPI (*SetFromBookmarkData)            (ai::FilePath &path, NSData* inBookmarkData, const ai::FilePath& inRelativeToPath, NSError** outError );
    
    void        AIAPI (*GetVolumeAndParentFromFilePath) (const ai::FilePath &path, NSURL **outVolume, NSURL **outParent);
    
    BOOL        AIAPI (*IsAlias)                        (const ai::FilePath &path);
    
	BOOL        AIAPI (*IsEjectable)                    (const ai::FilePath &path);

#endif //__OBJC__
#endif //MAC_ENV
    
};

#include "AIHeaderEnd.h"

#endif // __AIFilePath__
