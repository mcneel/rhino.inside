/*
 *        Name:	IAIFilePath.hpp
 *     Purpose:	C++ access class for File Path suite
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

#ifndef __IAIFilePath__
#define __IAIFilePath__

#include "IAIUnicodeString.h"

/*HACK for int32_t and uint32_t redefinition error in VS2012: In case of VS2012 compiler, "memory" file includes stdint.h which, 
		for some reason, points to dvacore/sys/win/stdint.h. As a result, datatypes defined in stdint.h throw redefinition errors.	*/
#if defined(_MSC_VER) && _MSC_VER >= 1700
#define _ADOBE_STDINT_H_
#endif

#include <memory>

#if defined(_MSC_VER) && _MSC_VER >= 1700
#undef _ADOBE_STDINT_H_
#endif


#ifdef MAC_ENV
    #ifdef __OBJC__
        #import <Foundation/NSURL.h>
        #import <Foundation/NSString.h>
    #endif
    #ifndef __COREFOUNDATION_CFURL__
        #include <CoreFoundation/CFURL.h>
    #endif
    #if defined(IOS_ENV)
		typedef short FSVolumeRefNum;
	#else
        #ifndef __FILES__
            #include <Carbon/Carbon.h>
        #endif
    #endif	// !defined(IOS_ENV)
#else

typedef signed long OSStatus;
#endif

struct FSSpec;
struct MiFile;

namespace ai {

#ifdef WIN_ENV
const ai::uint32 MaxPath = 259;
#endif
#ifdef MAC_ENV
const ai::uint32 MaxPath = 1023;
#endif
const ai::uint32 MaxFile = 255;

class FilePath
{
	public:

	/* Some file system operations can be very slow. For example, on Windows,
		UNC path names are used to access files on remote volumes. Determining
		the availability of those remote volumes can require significant time
		especially in the presence of the Windows client for NFS. For this
		reason volume availability information is cached. */

	/** Resets cached information about volumes, used to increase
		the efficiency of filesystem operations.
			@return Nothing.
		*/
	static void ResetVolumeCache() AINOTHROW;

	/** Default constructor. Creates an empty file-path object. */
	FilePath() AINOTHROW;
	/** Copies a file-path object. */
	FilePath(const FilePath&);

#ifdef AI_HAS_RVALUE_REFERENCES
	/**  Move Constructor */
	FilePath(FilePath&& rhs) AINOEXCEPT;
#endif

 	/**	Creates an initialized file-path object from a Unicode string
		containing a path native to Windows, Unix, or Mac OS, or a URL.
			@param path The new path.
			@param expandName When true, the function attempts to expand the
				provided path string into a full name (for example, for	a short,
				truncated name in Windows).
			@return The new object.
		*/
	explicit FilePath(const ai::UnicodeString &path, bool expandName = true);

	/** Creates as intialized file-path object from a file reference.
	
	*/
	
	

	/** Internal. Creates an initialized file-path object from
		a \c MiFile (Illustrator core only). */
	explicit FilePath(const MiFile&);


	
	explicit FilePath(const SPPlatformFileReference&);

	#ifdef MAC_ENV
	/** Creates an initialized file-path object from a \c CFString
		file specification  in Mac OS.
			@return The new object.
		*/
	explicit FilePath(const CFStringRef);

	/** Creates an initialized file-path object from a \c FSRef
		file specification  in Mac OS.
			@return The new object.
		*/
#if DEPRICATED_IN_10_8
	explicit FilePath(const FSRef&);
#endif

	/** Creates an initialized file-path object from a \c CFURLRef
		URL specification  in Mac OS.
			@return The new object.
		*/
	explicit FilePath(const CFURLRef);
    
    #ifdef __OBJC__
    /** Creates an initialized faile-path object from a \c BookmarkData
        @return The new object.
     */
    explicit FilePath( NSData* inBookmarkData, const FilePath& inRelativeToPath = FilePath() );
    #endif //__OBJC__
    
	#endif	// MAC_ENV

	/** Destructor */
	~FilePath();

	/** Swaps the content with rhs */
	void swap(FilePath& rhs) AINOEXCEPT;

	/** Copy assignment operator. Same as \c #AIFilePathSuite::Copy(). */
	FilePath& operator=(const FilePath&);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move assignment operator. */
	FilePath& operator=(FilePath&&) AINOEXCEPT;
#endif

	/** Reports whether a file-path object is empty.
			@return True if the object is empty.
		*/
	bool IsEmpty() const;

	/** Sets the referenced path of this object to a \c NULL path.
			@return Nothing.
		*/
	void MakeEmpty();

	/** Compares this file path to another for equality.
			@param filePath The path object to compare to this one
			@param resolveLinks	Optional. True to resolve links, aliases, and/or shortcuts
				if the paths are not identical. Default is false.
			@return True if the paths are identical, whether or not the file exists,
				or if links are resolved and the two paths refer to the same file.
				<br> False if the paths are not identical and \c resolveLinks is false.
		*/
	bool Equal(const FilePath& filePath, const bool resolveLinks = false) const;
	/** Equality operator	*/
	bool operator==(const FilePath&) const;
	/** Inequality operator 	*/
	bool operator!=(const FilePath&) const;

	/** Less-than operator, compares file path strings.	*/
	bool operator<(const FilePath&) const;

	/** Reports whether this path starts with a delimiter, and
		is therefore an absolute, not relative, path.
			@return True if the path starts with a delimiter
		*/
	bool StartsWithDelimiter() const;

	/** Reports whether this path ends with a delimiter, and
		therefore references a folder or directory, rather than a file.
			@return True if the path ends with a delimiter
		*/
	bool EndsWithDelimiter() const;

	/** Adds a component to this path. Adds or ignores appropriate delimiters
		as needed. Does not add delimiters to the end of a path unless explicitly
		requested by sending an empty addend.
			@param addend [in/out] A Unicode string containing the component to
				add, in which to return the lengthened path string.
			@return Nothing.
		*/
	void AddComponent(const ai::UnicodeString &addend = ai::UnicodeString());
	/** Adds a component to this path. Adds or ignores appropriate delimiters
		as needed. Does not add delimiters to the end of a path unless explicitly
		requested by sending an empty addend.
			@param addend A file-path object containing the component to
				add to the path of this object.
			@return Nothing.
		*/
	void AddComponent(const FilePath &addend);

	/** Removes the end component from this path.
			@return Nothing.
		*/
	void RemoveComponent();

	/** Adds a file extension to this path. Adds or ignores dots as needed so
		that only one dot appears before the extension.
			@param ext The extension text in a Unicode string.
			@return Nothing
		*/
	void AddExtension(const ai::UnicodeString &ext);
	/** Adds a file extension to this path. Adds or ignores dots as needed so
		that only one dot appears before the extension.
			@param ext The extension text in a C string.
			@return Nothing
		*/
	void AddExtension(const std::string &ext);
	/** Removes the file extension, if any, from this path.
			@return Nothing
		*/
	void RemoveExtension();

	/** Reports whether this file or directory exists after querying the file system.
			@param resolveLinks True to resolve links, aliases, and shortcuts for the
				full path returned in \c longPath.
			@param longPath	[out] Optional. A buffer in which to return a full long,
				Unicode version of the path, if the file or directory is found.
				Return value undefined if function returns false. Can be \c NULL.
			@param isFile [out] Optional. A buffer in which to return true if a
				file is found, false if a directory is found. Return value undefined
				if function returns false.Can be \c NULL.
			@return True if the file or directory exists, false otherwise.
		*/
	bool Exists(const bool resolveLinks,
				ai::UnicodeString *longPath = 0, bool *isFile = 0) const;

	/**	Resolves any alias or shortcut for this path by querying file system,
		and alters the object to point directly to the target file.
		The target file or directory must exist.  <<or what happens?>>
			@return Nothing
	*/
	void Resolve();

	/*****************************************************************************/
	/* Set operations */

	/**	Sets this file path from a Unicode string containing a path native to
		Windows, Unix, or Mac OS, or a URL.
			@param path Path of file.
			@param expandName When true, the function attempts to expand the
				provided path string into a full name (for example, for	a short,
				truncated name in Windows).
			@return Nothing.
		*/
	void Set(const ai::UnicodeString &path, bool expandName = true);

	/** Internal. Sets this file path from an \c MiFile. (Illustrator core only.)
			@return Nothing.
		*/
	void SetFromMiFile(const MiFile&);

	void SetFromSPFileRef(const SPPlatformFileReference&);

	#ifdef MAC_ENV

	/** Sets this file path from an \c CFStringRef file specification in Mac OS.
			@return Nothing.
		*/
	void SetFromCFString(const CFStringRef);

	/** Sets this file path from an \c FSRef file specification in Mac OS.
			@return The operating-system status code.
		*/
#if DEPRICATED_IN_10_8
	OSStatus SetFromFSRef(const FSRef&);
#endif

	/** Sets this file path from an \c CFURLRef URL specification in Mac OS.
			@return Nothing.
		*/
	void SetFromCFURL(const CFURLRef);
    
    #ifdef __OBJC__
    /** Sets this file path from bookmark data.
            @return A boolean value specifying whether this data is stale.
     */
    BOOL SetFromBookmarkData( NSData* inBookmarkData, const FilePath& inRelativeToPath = FilePath(), NSError** inError = NULL );
    #endif //__OBJC__
	
    #endif	// MAC_ENV


	/*****************************************************************************/
	/* Get operations */

	/** Retrieves the file name including an extension, if applicable, but without the path.
			@param displayName True to get the display name.
			@return The file name string.
		*/
	ai::UnicodeString GetFileName(const bool displayName = false) const;

	/** Retrieves the file name without the extension and path.
			@return The file name string.
		*/
	ai::UnicodeString GetFileNameNoExt() const;

	/** Retrieves the file extension, without the dot, or \c NULL if the
		file name ends with a dot.
			@return The extension string.
		*/
	ai::UnicodeString GetFileExtension() const;

	/** Retrieves the full path in notation native to the current platform.
			@param displayName True to get the display name.
			@return The path string.
		*/
	ai::UnicodeString GetFullPath(const bool displayName = false) const;

	/** Retrieves the directory name, ending with a delimiter, without the filename,
		in notation native to the current platform.
		If path represents a directory, the result is the same as \c GetFullPath().
			@param displayName True to get the display name.
			@return The directory path string.
		*/
	ai::UnicodeString GetDirectory(const bool displayName = false) const;

	/** Retrieves an operating-system-specific short version of the path.
		The file or folder must exist. Accesses the file system.
	 		\li In Windows, conforms to 8.3 format.
	 		\li In Mac OS X, the name may be truncated and a file ID appended.
	 			If the file ID is required, the path is not valid across processes.
			@return The path string.
		*/
	ai::UnicodeString GetShortPath() const;

	/** Retrieves the parent of the object represented by this path.
			\li If this path is a directory, gets the parent directory.
			\li If this path is a top-level volume, gets an empty path.

		Does not access the file system, and does not guarantee that
		the referenced file or directory exists.
			@return The file-path object for the parent.
		*/
	FilePath GetParent() const;

	/// Return the relative path of 'path' to 'base'.
	//On hold due to lack of demand
	//FilePath GetRelativePath(const FilePath &base) const;

	/// Return the absolute path for 'relative' from 'base'.
	//On hold due to lack of demand
	//FilePath GetAbsolutePath(const FilePath &base) const;

	/** Retrieves the path component delimiter for the current platform.
			@return The delimiter character.
		*/
	static const char GetDelimiter() AINOTHROW;

	#ifdef MAC_ENV
    
    #if DEPRICATED_IN_10_8
    /** Retrieves the volume and/or parent of this file or directory
     in Mac OS. One of the parameters
     can be \c NULL.
     @param vol [out] A buffer in which to return the volume.
     @param parent [out] A buffer in which to return the parent.
     @return Nothing.
     */
    void GetVolumeAndParent(FSVolumeRefNum *vol, UInt32 *parent) const;
    #endif
    
    #ifdef __OBJC__
	/** Retrieves the volume and/or parent of this file or directory
		in Mac OS. One of the parameters
		can be \c NULL.
			@param vol [out] A buffer in which to return the volume.
			@param parent [out] A buffer in which to return the parent.
			@return Nothing.
		*/
 	void GetVolumeAndParent(NSURL **volume, NSURL **parent) const;
    #endif
    #endif

	/** Retrieves the creator and type of this file or directory (4-character codes)
		in Mac OS.
			@param creator [out] A buffer in which to return the creator, a 4-character code.
			@param type [out] A buffer in which to return the type, a 4-character code.
			@return An error code, \c #kNoErr on success.
		*/
	AIErr GetCreatorAndType(ai::uint32 *creator, ai::uint32 *type) const;

	/** Retrieves this path as a Uniform Resource Locator (URL), which
		contains only ASCII characters; any special	characters are
		escaped with URL percent (\%) encoding.
			@param displayName True to get the display name.
			@return The URL string.
		*/
	ai::UnicodeString GetAsURL(const bool displayName) const;

	void GetAsSPPlatformFileRef(SPPlatformFileReference&) const;

	/** Internal. Fills in the existing \c MiFile from this path (Illustrator core only). */
	AIErr GetAsMiFile(MiFile&) const;

	/**  Internal. Creates an \c MiFile based on this path (Illustrator core only). */
	AIErr GetAsMiFile(MiFile*&) const;

	AIBoolean IsOnNetwork() const;

	#ifdef MAC_ENV

	/** Creates a \c CFString from this file path in Mac OS.
			@return The file specification object.
		*/
	CFStringRef GetAsCFString() const;

	/** Creates an \c FSRef from this file path in Mac OS.
			@param result [out] A buffer in which to return the file specification.
			@return An operating-system status code.
		*/
#if DEPRICATED_IN_10_8
	OSStatus GetAsFSRef(FSRef& result) const;
#endif

	/** Creates a \c CFURL from this file path in Mac OS.
			@return The URL specification object.
		*/
	CFURLRef GetAsCFURL() const;

    #ifdef __OBJC__
    NSString* GetAsNSString         () const;
    
    NSURL*  GetAsNSURL              () const;
    
    NSData* GetAsBookmarkData       (  const FilePath& inRelativeToPath = FilePath(), NSError** inError = NULL ) const;
    
    NSData* GetAsMinimalBookmarkData(  const FilePath& inRelativeToPath = FilePath(), NSError** inError = NULL ) const;
    
    BOOL    IsAlias                 () const;
    
    BOOL    IsEjectable             () const;
    #endif
	
#endif	// MAC_ENV

	private:
	class FilePathImpl *impl;
};

////////////////////////////////////////////////////////////////////////////////
// Inline members
//

// Swap
inline void FilePath::swap(FilePath& rhs) AINOEXCEPT
{
	std::swap(impl, rhs.impl);
}

#ifdef AI_HAS_RVALUE_REFERENCES

// Move constructor
inline FilePath::FilePath(FilePath&& rhs) AINOEXCEPT : impl{rhs.impl}
{
	rhs.impl = nullptr;
}

// Move assignment operator
inline FilePath& FilePath::operator=(FilePath&& rhs) AINOEXCEPT
{
	swap(rhs);
	return *this;
}

#endif // AI_HAS_RVALUE_REFERENCES

inline void FilePath::AddComponent(const FilePath &addend)
{
	AddComponent(addend.GetFullPath());
}

inline void FilePath::AddExtension(const std::string &ext)
{
	AddExtension(ai::UnicodeString(ext));
}

} // namespace ai

#endif // __IAIFilePath__
