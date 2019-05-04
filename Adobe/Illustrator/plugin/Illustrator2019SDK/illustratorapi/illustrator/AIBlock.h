#ifndef __AIBlock__
#define __AIBlock__

/*
 *        Name:	AIBlock.h
 *   $Revision: 5 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Memory Management Suite.
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

/** @file AIBlock.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIBlockSuite			"AI Block Suite"
#define kAIBlockSuiteVersion	AIAPI_VERSION(4)
#define kAIBlockVersion			kAIBlockSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides a cross-platform way to manage memory.
	Use it to request, release, and resize blocks of memory.
	The functions are analogous to the standard C library memory allocation
	routines or the Mac OS pointer routines.

	In some situations, Illustrator expects memory to be allocated with this suite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIBlockSuite and \c #kAIBlockVersion.
*/
typedef struct {
	/** Allocates new block of memory.
		This call is similar to the standard C library \c malloc routine and
		the Macintosh Toolbox \c NewPtr.
			@param size The number of bytes to allocate.
			@param block [out] A buffer in which to return the pointer to
				the newly allocated block.
			@return The error \c kOutOfMemoryErr if the function fails
				due to lack of memory.
		*/
	AIAPI AIErr (*AllocateBlock) ( size_t size, void **block );
	/** Releases a block of memory previously allocated with \c #AllocateBlock().
		This call is similar to the standard C library \c free function and
		the Macintosh Toolbox \c DisposPtr.
			@param block A pointer to the allocated block.
		*/
	AIAPI AIErr (*DisposeBlock) ( void *block );

	/** Changes the size of a previously allocated memory block.
		This function is similar to the standard C library \c realloc function
		and the Macintosh Toolbox \c SetPtrSize.
		The function tries to increase the size of the block without changing
		its location. If there is not room on the heap, the block is moved and
		the new location returned.
			@param block A pointer to the previously allocated block.
			@param size The number of bytes to allocate.
			@param NewBlock [out] A buffer in which to return the pointer to
				the newly allocated block.
			@return The error \c kOutOfMemoryErr if the function fails
				due to lack of memory.
		*/
	AIAPI AIErr (*ReallocateBlock) ( void *block, size_t newSize, void **newBlock );

	/** Gets number of bytes in a memory block.
			@param block A pointer to the previously allocated block.
			@param size  [out] A buffer in which to return the number of bytes.
		*/
	AIAPI AIErr (*SizeOfMemoryBlock) ( void *block, size_t *size );

} AIBlockSuite;


#include "AIHeaderEnd.h"


#endif
