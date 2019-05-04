
#ifndef __AIPlatformMemory__
#define __AIPlatformMemory__

/*
 *        Name:	AIPlatformMemory.h
 *   $Revision: 1 $
 *      Author:	Dave Lazarony
 *        Date: 7/1/96
 *     Purpose:	Wrapper suite for calling the Mac OS or Windows platform
 *				memory manager.
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

#ifndef __ASTypes__
#include "AITypes.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIPlatformMemory.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIPlatformMemorySuite				"AI Platform Memory Suite"
#define kAIPlatformMemorySuiteVersion		AIAPI_VERSION(3)
#define kAIPlatformMemoryVersion			kAIPlatformMemorySuiteVersion


/*******************************************************************************
 **
 **	Suite Record
 **
 **/

/** @ingroup Suites
	This suite provides functions with which to manage memory for \c #ASSliceSettings
	values, used with the \c #AIOptimizationSettingsSuite. Do not use them for other
	memory management. In general, use the \c #AIBlockSuite or
	\c #SPBlocksSuite to allocate memory.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPlatformMemorySuite and \c #kAIPlatformMemoryVersion.
 */
typedef struct {
	/** Allocates a block of memory.
			@param size The number of bytes to allocate.
			@param handle [out] A buffer in which to return the memory handle object.
		*/
	ASAPI ASErr (*New)(size_t size, ASHandle *handle);
	/** Frees a block of memory allocated with \c #New().
			@param handle The memory handle object.
		*/
	ASAPI ASErr (*Delete)(ASHandle handle);
	/** Retrieves the size of a block of memory allocated with \c #New().
			@param handle The memory handle object.
			@param size  [out] A buffer in which to return the number of bytes allocated.
		*/
	ASAPI ASErr (*GetSize)(ASHandle handle, size_t *size);
	/** Resizes a block of memory allocated with \c #New().
			@param handle [in, out] A buffer in which to pass the old object and return the
				resized object.
			@param newSize The number of bytes to allocate.
		*/
	ASAPI ASErr (*Resize)(ASHandle *handle, size_t newSize);
	/** Locks a memory block, so that the operating system does not move it.
		This is the equivalent of \c HLock() in Mac OS or \c GlobalLock() in Windows.
			@param handle The memory handle.
			@param dataPtr [out] A buffer in which to return a pointer
				to the locked memory block.
		*/
	ASAPI ASErr (*Lock)(ASHandle handle, void **dataPtr);
	/** Unlocks a memory block that was locked with \c #Lock().
			@param handle The memory handle.
		*/
	ASAPI ASErr (*UnLock)(ASHandle handle);

} AIPlatformMemorySuite;


#include "AIHeaderEnd.h"

#endif