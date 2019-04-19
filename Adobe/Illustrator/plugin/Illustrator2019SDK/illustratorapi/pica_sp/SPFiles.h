/***********************************************************************/
/*                                                                     */
/* SPFiles.h                                                           */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1995-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

#ifndef __SPFiles__
#define __SPFiles__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPTypes.h"
#include "SPProps.h"

#include "SPHeaderBegin.h"

#ifdef WIN_ENV
#include <cstring>
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
    
    /*******************************************************************************
     **
     ** Constants
     **
     **/
    /** Files suite name */
#define kSPFilesSuite				"SP Files Suite"
    
    
#define kSPFilesSuiteVersion3		3
    
#define kSPFilesSuiteVersion		4
	/** PICA global list of potential plug-in files.
     @see \c #SPRuntimeSuite::GetRuntimeFileList() */
#define kSPRuntimeFileList			((SPFileListRef)NULL)
    
    
    /** Return value for \c #SPFilesSuite::GetFilePropertyList(),
     indicating that the file has no property list. */
#define kFileDoesNotHavePiPL		(SPPropertyListRef)(~((size_t)NULL))
    /** Return value for \c #SPFilesSuite::GetFilePropertyList(),
     indicating that the file has multiple property lists.
     Use \c #SPPluginsSuite::GetPluginPropertyList() to access the
     PiPL for each \c #SPPluginRef exported by the file. */
#define kFileHasMulitplePiPLs		NULL
    
    /*******************************************************************************
     **
     ** Types
     **
     **/
    
    /** The maximum number of characters allowed in a file path specification. */
    
    
    /** Opaque reference to a file. Access with the \c #SPFilesSuite. */
    typedef struct SPFile *SPFileRef;
    /** Opaque reference to a file list. Access with the \c #SPFilesSuite. */
    typedef struct SPFileList *SPFileListRef;
    /** Opaque reference to a file-list iterator. Access with the \c #SPFilesSuite. */
    typedef struct SPFileListIterator *SPFileListIteratorRef;
    /** Opaque reference to a platform-specific file specification. Access with the \c #SPFilesSuite. */
    typedef struct OpaqueSPPlatformFileRef SPPlatformFileRef;
    
    
#ifdef MAC_ENV
#define kMaxPathLength 1024
#pragma options align=power
    
    
    /** A file specification In Mac OS.It is the same as \c FSSpec. */
    typedef struct SPPlatformFileSpecification {
        /** The version number (Mac OS). */
        short vRefNum;
        /** The unique identifier (Mac OS). */
        ai::int32 parID;
        /** The file name string (Mac OS). */
        unsigned char name[64];
    } SPPlatformFileSpecification;
	
    /** A file reference in terms of a string. This path should be POSIX style path with UTF-8 encoding.
     FSRefMakePath can be used to make a path from FSRef and FSPathMakeRef can be used to make FSRef from a POSIX style path.*/
    typedef struct SPPlatformFileReference {
        unsigned char path[kMaxPathLength]; //1024 has been taken up from /usr/include/sys/syslimits.h
    } SPPlatformFileReference;
    
#pragma options align=reset
    
    /** Platform-specific file metadata. */
    typedef struct SPPlatformFileInfo {	 /* On Mac OS*/
        /** Not used. */
        ai::uint32 attributes; 	//Unused, but still required to maintain binary compatibility
        /** Date file was created (Mac OS). */
        ai::uint32 creationDate;
        /** Data file was last modified (Mac OS). */
        ai::uint32 modificationDate;
        /** Type of file for Finder (Mac OS). */
        ai::uint32 finderType;
        /** File creator (Mac OS). */
        ai::uint32 finderCreator;
        /** File flags for Finder (Mac OS); see Mac OS documentation. */
        ai::uint16 finderFlags;
    } SPPlatformFileInfo;
    
    SPErr FileSpectoFileRef(const SPPlatformFileSpecification *fileSpec, const SPPlatformFileReference *fileRef); // temporary functions used while transition from SPPlatformFileSpecification to SPPlatformFileReference
    SPErr FileReftoFileSpec(const SPPlatformFileReference *fileRef, const SPPlatformFileSpecification *fileSpec);
#endif
    
#ifdef WIN_ENV
#define kMaxPathLength 300
    /** A file specification in Windows. */
    typedef struct SPPlatformFileSpecification {
        /** The file path string (Windows).*/
        char path[kMaxPathLength];
    } SPPlatformFileSpecification;
    
    //Keeping the structure's type similar to PSinterface, added some additional helper methods.
    struct SPPlatformFileSpecificationW {
    private:
        /** path could be as long as 64K but MUST be NULL terminated. */
        wchar_t path[kMaxPathLength];
    public:
        SPPlatformFileSpecificationW()
        {
            memset (path,0,sizeof(path));
        }
        const wchar_t* c_str() const { return path; }
        
        wchar_t* GetBuffer() {return path;}
    };
    
    /** Same as SPPlatformFileSpecification on Windows. */
    /** VS_TODO: This is just the initial definition in order to reduce the impact.
     We need to get rid of SPPlatformFileSpecification one day.
     Also, SPPlatformFileRef is already defined above and it does
     not seem to be used anywhere. I think we should remove it. */
    typedef SPPlatformFileSpecificationW SPPlatformFileReference;
    
    /**Platform-specific file metadata. */
    typedef struct SPPlatformFileInfo {
        /** File attribute flags (Windows); see Windows documentation. */
        ai::uint32 attributes;
        /** Least-significant byte of the file creation date-time (Windows).*/
        ai::uint32 lowCreationTime;
        /** Most-significant byte of the file creation date-time (Windows).*/
        ai::uint32 highCreationTime;
        /** Least-significant byte of the file modification date-time (Windows).*/
        ai::uint32 lowModificationTime;
        /** Most-significant byte of the file modification date-time (Windows).*/
        ai::uint32 highModificationTime;
        /** The file-name extension indicating the file type (Windows). */
        const wchar_t* extension;
    } SPPlatformFileInfo;
#endif
    
    /** Internal */
    typedef SPBoolean (*SPAddPiPLFilterProc)( SPPlatformFileInfo *info );
    
    
    /*******************************************************************************
     **
     ** Suite
     **
     **/
    /** @ingroup Suites
     This suite allows you to access the PICA files list. This list, created at startup,
     contains references to every file in the application's plug-in folder, including
     any resolved file and folder aliases. PICA maintains this list, and uses it to find plug-ins.
     
     Use this suite to access the plug-in file list, in order to avoid redundant directory
     scans. Adapters looking for their own plug-ins and PICA plug-ins looking for
     support files should scan the list to locate relevant files rather than walking
     platform directory  structures on their own.
     
     Similarly, you can use this suite to create, maintain, and access your own lists
     of files in a platform-independent and efficient manner.
     
     \li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
     \c #kSPFilesSuite and \c #kSPFilesSuiteVersion.
     */
    typedef struct SPFilesSuite {
        /** Creates a new file list. Typically, you use the main PICA file list to access
         plug-in files, available through \c #SPRuntimeSuite::GetRuntimeFileList().
         You can use this to track other file collections. If you create a new list, you
         must free it when it is no longer needed, using \c #FreeFileList().
         @param fileList [out] A buffer in which to return the new file list object.
         */
        SPAPI SPErr (*AllocateFileList)( SPFileListRef *fileList );
        /** Frees a file list created with \c #AllocateFileList(), and any entries in the list.
         @param fileList The file list object.
         */
        SPAPI SPErr (*FreeFileList)( SPFileListRef fileList );
        
        /** Adds a file or all files in a directory to a file list. Searches a directory
         recursively for contained files.
         @param fileList The file list object.
         @param file The file or directory specification.
         */
		SPAPI SPErr (*AddFiles)( SPFileListRef fileList, const SPPlatformFileReference *file );
		
        
        /** Creates a file-list iterator object to use with \c #NextFile() for iterating
         through a file list. The iterator is initially set to the first file in the list.
         When the iterator is no longer needed, free it with \c #DeleteFileListIterator().
         @param fileList The file list object.
         @param iter [out] A buffer in which to return the new iterator object.
         */
        SPAPI SPErr (*NewFileListIterator)( SPFileListRef fileList, SPFileListIteratorRef *iter );
        /** Retrieves the current file from a file list iterator, and advances the iterator.
         @param iter The iterator object.
         @param file [out] A buffer in which to return the current file object, or \c NULL
         if the end of the list has been reached.
         */
        SPAPI SPErr (*NextFile)( SPFileListIteratorRef iter, SPFileRef *file );
        /** Frees a file-list iterator created with /c #NewFileListIterator().
         @param iter The iterator object.
         */
        SPAPI SPErr (*DeleteFileListIterator)( SPFileListIteratorRef iter );
        /** Retrieves the platform-specific file specification for a file.
         @param file The file object.
         @param fileSpec [out] A buffer in which to return the file specification.
         */
        
#ifdef WIN_ENV
        
        SPAPI SPErr (*GetFileSpecification) ( SPFileRef  file, SPPlatformFileSpecification *fileSpec );
#endif
        SPAPI SPErr (*GetFileReference)( SPFileRef file, SPPlatformFileReference *fileSpec );
        /** Retrieves the  metadata for a file.
         @param file The file object.
         @param info [out] A buffer in which to return the file information.
         */
        SPAPI SPErr (*GetFileInfo)( SPFileRef file, SPPlatformFileInfo *info );
        
        /** Reports whether a file in a file list is a plug-in.
         @param file The file object.
         @param isAPlugin [out] A buffer in which to return true if the file is a plug-in.
         */
        SPAPI SPErr (*GetIsAPlugin)( SPFileRef file, SPBoolean *isAPlugin );
        /** Sets whether a file in a file list is a plug-in.
         @param file The file object.
         @param isAPlugin True to mark the file as a plug-in, false to mark it as not a plug-in.
         */
        SPAPI SPErr (*SetIsAPlugin)( SPFileRef file, SPBoolean isAPlugin );
        
        /** Retrieves the property list for a file.
         @param file The file object.
         @param propertList [out] A buffer in which to return the property list,
         or \c #kFileDoesNotHavePiPL if the file does not have a property list,
         or \c #kFileHasMulitplePiPLs if the file has multiple property lists.
         @see \c SPPiPL.h
         */
        SPAPI SPErr (*GetFilePropertyList)( SPFileRef file, SPPropertyListRef *propertList );
        /** Sets the property list for a file.
         @param file The file object.
         @param propertList The new property list.
         */
        SPAPI SPErr (*SetFilePropertyList)( SPFileRef file, SPPropertyListRef propertList );
        
    } SPFilesSuite;
    
    
    /** Internal */
    SPAPI SPErr SPAllocateFileList( SPFileListRef *fileList );
    /** Internal */
    SPAPI SPErr SPFreeFileList( SPFileListRef fileList );
    SPAPI SPErr SPAddFiles( SPFileListRef fileList, const SPPlatformFileReference *file );
    
    /** Internal */
    SPAPI SPErr SPNewFileListIterator( SPFileListRef fileList, SPFileListIteratorRef *iter );
    /** Internal */
    SPAPI SPErr SPNextFile( SPFileListIteratorRef iter, SPFileRef *file );
    /** Internal */
    SPAPI SPErr SPDeleteFileListIterator( SPFileListIteratorRef iter );
    
    /** Internal */
#ifdef WIN_ENV
    
    SPAPI SPErr SPGetFileSpecification( SPFileRef  file, SPPlatformFileSpecification *fileSpec );
#endif
    
    SPAPI SPErr SPGetFileReference( SPFileRef file, SPPlatformFileReference *fileSpec ); // This function will replace all the instances of SPGetFileSpecification
    /** Internal */
    SPAPI SPErr SPGetFileInfo( SPFileRef file, SPPlatformFileInfo *info );
    /** Internal */
    SPAPI SPErr SPGetIsAPlugin( SPFileRef file, SPBoolean *isAPlugin );
    /** Internal */
    SPAPI SPErr SPSetIsAPlugin( SPFileRef file, SPBoolean isAPlugin );
    
    /** Internal */
    SPAPI SPErr SPGetFilePropertyList( SPFileRef file, SPPropertyListRef *propertList );
    /** Internal */
    SPAPI SPErr SPSetFilePropertyList( SPFileRef file, SPPropertyListRef propertList );
    
    /** Internal */
    SPAPI SPErr SPAddFilePiPLs( SPFileListRef fileList, SPAddPiPLFilterProc filter );
    
    /*******************************************************************************
     **
     **	Errors
     **
     **/
    
#include "SPErrorCodes.h"
    
#ifdef __cplusplus
}
#endif

#include "SPHeaderEnd.h"

#endif
