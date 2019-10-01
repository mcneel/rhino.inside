/***********************************************************************/
/*                                                                     */
/* SPFilesV3.h                                                           */
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

#ifndef __SPFilesV3__
#define __SPFilesV3__

/*******************************************************************************
 **
 **	Imports
 **
 **/
#include "SPFiles.h"

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define kSPRuntimeFileListV3			((SPFileListRefV3)NULL)
    
#ifdef WIN_ENV
	/**Platform-specific file metadata. */
	typedef struct SPPlatformFileInfoV3 {
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
		const char* extension;
	} SPPlatformFileInfoV3;
    
    typedef SPPlatformFileSpecification SPPlatformFileReferenceV3;
    
    typedef SPFileRef SPFileRefV3;
    
    typedef SPFileListRef SPFileListRefV3;
    
    typedef SPFileListIteratorRef SPFileListIteratorRefV3;
#else
    typedef SPPlatformFileInfo SPPlatformFileInfoV3;
    
    typedef SPPlatformFileReference SPPlatformFileReferenceV3;
    
    typedef struct SPFileV3 * SPFileRefV3;
    
    typedef struct SPFileListV3 *SPFileListRefV3;
    
    typedef struct SPFileListIteratorV3 *SPFileListIteratorRefV3;
#endif
    
    
    
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
    typedef struct SPFilesSuiteV3 {
        /** Creates a new file list. Typically, you use the main PICA file list to access
         plug-in files, available through \c #SPRuntimeSuite::GetRuntimeFileList().
         You can use this to track other file collections. If you create a new list, you
         must free it when it is no longer needed, using \c #FreeFileList().
         @param fileList [out] A buffer in which to return the new file list object.
         */
        SPAPI SPErr (*AllocateFileList)( SPFileListRefV3 *fileList );
        /** Frees a file list created with \c #AllocateFileList(), and any entries in the list.
         @param fileList The file list object.
         */
        SPAPI SPErr (*FreeFileList)( SPFileListRefV3 fileList );
        
        /** Adds a file or all files in a directory to a file list. Searches a directory
         recursively for contained files.
         @param fileList The file list object.
         @param file The file or directory specification.
         */
        
		SPAPI SPErr (*AddFiles)( SPFileListRefV3 fileList, const SPPlatformFileReferenceV3 *file );
        
        
        /** Creates a file-list iterator object to use with \c #NextFile() for iterating
         through a file list. The iterator is initially set to the first file in the list.
         When the iterator is no longer needed, free it with \c #DeleteFileListIterator().
         @param fileList The file list object.
         @param iter [out] A buffer in which to return the new iterator object.
         */
        SPAPI SPErr (*NewFileListIterator)( SPFileListRefV3 fileList, SPFileListIteratorRefV3 *iter );
        /** Retrieves the current file from a file list iterator, and advances the iterator.
         @param iter The iterator object.
         @param file [out] A buffer in which to return the current file object, or \c NULL
         if the end of the list has been reached.
         */
        SPAPI SPErr (*NextFile)( SPFileListIteratorRefV3 iter, SPFileRefV3 *file );
        /** Frees a file-list iterator created with /c #NewFileListIterator().
         @param iter The iterator object.
         */
        SPAPI SPErr (*DeleteFileListIterator)( SPFileListIteratorRefV3 iter );
        
        /** Retrieves the platform-specific file specification for a file.
         @param file The file object.
         @param fileSpec [out] A buffer in which to return the file specification.
         */
        SPAPI SPErr (*GetFileSpecification)( SPFileRefV3 file, SPPlatformFileSpecification *fileSpec ); //SW_TODO: This function is to be removed completely after changes in photoshop adapter plugin
        
        SPAPI SPErr (*GetFileReference)( SPFileRefV3 file, SPPlatformFileReferenceV3 *fileSpec );
        
        /** Retrieves the  metadata for a file.
         @param file The file object.
         @param info [out] A buffer in which to return the file information.
         */
        SPAPI SPErr (*GetFileInfo)( SPFileRefV3 file, SPPlatformFileInfoV3 *info );
        
        /** Reports whether a file in a file list is a plug-in.
         @param file The file object.
         @param isAPlugin [out] A buffer in which to return true if the file is a plug-in.
         */
        SPAPI SPErr (*GetIsAPlugin)( SPFileRefV3 file, SPBoolean *isAPlugin );
        /** Sets whether a file in a file list is a plug-in.
         @param file The file object.
         @param isAPlugin True to mark the file as a plug-in, false to mark it as not a plug-in.
         */
        SPAPI SPErr (*SetIsAPlugin)( SPFileRefV3 file, SPBoolean isAPlugin );
        
        /** Retrieves the property list for a file.
         @param file The file object.
         @param propertList [out] A buffer in which to return the property list,
         or \c #kFileDoesNotHavePiPL if the file does not have a property list,
         or \c #kFileHasMulitplePiPLs if the file has multiple property lists.
         @see \c SPPiPL.h
         */
        SPAPI SPErr (*GetFilePropertyList)( SPFileRefV3 file, SPPropertyListRef *propertList );
        /** Sets the property list for a file.
         @param file The file object.
         @param propertList The new property list.
         */
        SPAPI SPErr (*SetFilePropertyList)( SPFileRefV3 file, SPPropertyListRef propertList );
        
    } SPFilesSuiteV3;
    
    
    SPAPI SPErr SPAllocateFileListV3( SPFileListRefV3 *fileList );
    SPAPI SPErr SPFreeFileListV3( SPFileListRefV3 fileList );
    SPAPI SPErr SPNewFileListIteratorV3( SPFileListRefV3 fileList, SPFileListIteratorRefV3 *iter );
    SPAPI SPErr SPDeleteFileListIteratorV3( SPFileListIteratorRefV3 iter );
    SPAPI SPErr SPGetFileInfoV3( SPFileRefV3 file, SPPlatformFileInfoV3 *info );
    SPAPI SPErr SPAddFilesV3( SPFileListRefV3 fileList, const SPPlatformFileReferenceV3 *file );
    SPAPI SPErr SPGetFileReferenceV3( SPFileRefV3 file, SPPlatformFileReferenceV3 *fileSpec ); // This function will replace all the instances of SPGetFileSpecification
    
    SPAPI SPErr SPGetFileSpecificationV3( SPFileRefV3 file, SPPlatformFileSpecification *fileSpec );
    SPAPI SPErr SPNextFileV3( SPFileListIteratorRefV3 iter, SPFileRefV3 *file );
    
    SPAPI SPErr SPGetIsAPluginV3( SPFileRefV3 file, SPBoolean *isAPlugin );
    SPAPI SPErr SPSetIsAPluginV3( SPFileRefV3 file, SPBoolean isAPlugin );
    SPAPI SPErr SPGetFilePropertyListV3( SPFileRefV3 file, SPPropertyListRef *propertyList );
    SPAPI SPErr SPSetFilePropertyListV3( SPFileRefV3 file, SPPropertyListRef propertyList );
#ifdef __cplusplus
}
#endif

#include "SPHeaderEnd.h"

#endif //SPFilesV3
