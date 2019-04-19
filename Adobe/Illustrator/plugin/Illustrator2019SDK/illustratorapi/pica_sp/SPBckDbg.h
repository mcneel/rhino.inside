/***********************************************************************/
/*                                                                     */
/* SPBckDbg.h                                                          */
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

#ifndef __SPBlockDebug__
#define __SPBlockDebug__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPTypes.h"
#include "AIBasicTypes.h"

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 **
 **	Constants
 **
 **/
/** SPBlockDebug suite name */
#define kSPBlockDebugSuite			"SP Block Debug Suite"
/** SPBlockDebug suite version */
#define kSPBlockDebugSuiteVersion	2


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides basic debugging capability for blocks of memory
	allocated with the \c #SPBlocksSuite.  Debugging can only be enabled
	in the development environment.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kSPBlockDebugSuite and \c #kSPBlockDebugSuiteVersion.
	*/
typedef struct SPBlockDebugSuite {
	/** Reports whether block debugging is enabled.
			@param enabled [out] A buffer in which to return 1 if debugging
				is enabled, 0 otherwise.
		*/
	SPAPI SPErr (*GetBlockDebugEnabled)( ai::int32 *enabled );
	/** Turns debugging on or off.
			@param debug 1 to turn debugging on, 0 to turn it off.
		*/
	SPAPI SPErr (*SetBlockDebugEnabled)( ai::int32 debug );
	/** Retrieves the first block of memory allocated. Use with \c #GetNextBlock()
		to iterate through all allocated blocks.
			@param block [out] A buffer in which to return the block pointer.
		*/
	SPAPI SPErr (*GetFirstBlock)( void **block );
	/** Retrieves the block of memory allocated immediately after a given block.
		Use with \c #GetFirstBlock() to iterate through all allocated blocks.
			@param block The current block pointer
			@param nextblock [out] A buffer in which to return the next block pointer.
		*/
	SPAPI SPErr (*GetNextBlock)( void *block, void **nextblock );
	/** Retrieves the debugging tag assigned to a block of memory when it
		was allocated or reallocated.
			@param block The block pointer.
			@param debug [out] A buffer in which to return the tag string.
			@see \c #SPBlocksSuite::AllocateBlock(), \c #SPBlocksSuite::ReallocateBlock()
		*/
	SPAPI SPErr (*GetBlockDebug)( void *block, const char **debug );

} SPBlockDebugSuite;


/** Internal */
SPAPI SPErr SPGetBlockDebugEnabled( ai::int32 *enabled );
/** Internal */
SPAPI SPErr SPSetBlockDebugEnabled( ai::int32 debug );
/** Internal */
SPAPI SPErr SPGetFirstBlock( void **block );
/** Internal */
SPAPI SPErr SPGetNextBlock( void *block, void **nextblock );
/** Internal */
SPAPI SPErr SPGetBlockDebug( void *block, const char **debug );


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
