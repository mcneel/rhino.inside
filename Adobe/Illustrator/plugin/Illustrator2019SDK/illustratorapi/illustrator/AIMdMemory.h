
#ifndef __AIMdMemory__
#define __AIMdMemory__

/*
 *        Name:	AIMdMemory.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Handle-based Memory suite
 *
 *				Provides machine-dependent (Md) memory management.
 *				Uses NewHandle() in Mac OS and GlobalAlloc() in Windows
 *				to allocate memory.
 * 				Generally deprecated, but still used for matching art
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


#include "AIHeaderBegin.h"

/** @file AIMdMemory.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIMdMemorySuite		"AI MdMemory Suite"
#define kAIMdMemorySuiteVersion		AIAPI_VERSION(3)
#define kAIMdMemoryVersion			kAIMdMemorySuiteVersion


/*******************************************************************************
 **
 ** Types
 **
 **/

/** An opaque pointer to a block of memory. */
typedef void **AIMdMemoryHandle;

/*******************************************************************************
 **
 **	Suite Record
 **
 **/

/** @ingroup Suites
	This suite provides functions that allocate and dispose of blocks of memory.
	This memory management scheme is generally deprecated. Do not
	use it to allocate memory. It is still used, however,
	by the \c #AIMatchingArtSuite, whose functions return a handle
	that must be freed by the caller using \c #MdMemoryDisposeHandle().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMdMemorySuite and \c #kAIMdMemoryVersion.
*/
typedef struct {
	/** Allocates a memory block.
			@param size The number of bytes.
			@param hMem [out] A buffer in which to return the memory handle.
		*/
	AIAPI AIErr (*MdMemoryNewHandle) ( size_t size, AIMdMemoryHandle *hMem );

	/** Frees the memory associated with a handle.
			@param hMem The memory handle. Upon return, this is no longer valid.
		*/
	AIAPI AIErr (*MdMemoryDisposeHandle) ( AIMdMemoryHandle hMem );

	/** Reports the size of an allocated memory block.
			@param hMem The memory handle.
			@param size [out] A buffer in which to return the number of bytes.
		*/
	AIAPI AIErr (*MdMemoryGetSize) ( AIMdMemoryHandle hMem, size_t *size );

	/** Reallocates a memory block.
			@param hMem The memory handle.    
			@param newSize The new number of bytes.
		*/
	AIAPI AIErr (*MdMemoryResize) ( AIMdMemoryHandle hMem, size_t newSize );

	/** Locks a memory block, so that the operating system does not move it.
		This is no longer necessary, as the operating system no longer moves
		memory blocks.
			@param hMem The memory handle.
			@param lockedPtr [out] A buffer in which to return a pointer
				to the locked memory block.
		*/
	AIAPI AIErr (*MdMemoryLock) ( AIMdMemoryHandle hMem, void **lockedPtr );

	/** Unlocks a memory block that was locked with \c #MdMemoryLock().
		This is no longer necessary, as the operating system no longer moves
		memory blocks.
			@param hMem The memory handle.
		*/
	AIAPI AIErr (*MdMemoryUnLock) ( AIMdMemoryHandle hMem );

} AIMdMemorySuite;


#include "AIHeaderEnd.h"

#endif
