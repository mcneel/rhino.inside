#ifndef __AIStringPool__
#define __AIStringPool__

/*
 *        Name:	AIStringPool.h
 *   $Revision: 4 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator String Pool Suite.
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

/** @file AIStringPool.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIStringPoolSuite		"AI String Pool Suite"
#define kAIStringPoolSuiteVersion	AIAPI_VERSION(4)
#define kAIStringPoolVersion		kAIStringPoolSuiteVersion


/** @ingroup Errors
	See \c #AIStringPoolSuite */
#define kStringPoolErr			'SPER'


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct StringPool AIStringPool;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides functions for working with \e string \e pools.
	A string pool contains a collection of NULL-terminated character sequences. No
	single string appears in the pool more than once. You can compare two strings
	from the pool for equality by comparing their addresses. You can obtain the application
	string pool using \c #AIRuntimeSuite::GetAppStringPool(), or you can use these
	functions to create your own string pool.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIStringPoolSuite and \c #kAIStringPoolVersion.
	*/
typedef struct {

	/** Creates a new string pool. The plug-in is responsible for freeing the
		pool when it is no longer needed.
			@param pool [out] A buffer in which to return the new string pool object.
		*/
	AIAPI AIErr (*AllocateStringPool) ( AIStringPool **pool );

	/** Disposes of a string pool that was created with \c #AllocateStringPool().
			@param pool The string pool object.
		*/
	AIAPI AIErr (*DisposeStringPool) ( AIStringPool *pool );

	/** Retrieves a string entry from a string pool, or creates it and adds it
		to the pool if it is not already there.
			@param pool The string pool object.
			@param string The string value of the matching or new pool entry.
			@param wstring [out] A buffer in which to return the pool entry.
		*/
	AIAPI AIErr (*MakeWString) ( AIStringPool *pool, const char *string, char **wstring );

} AIStringPoolSuite;


#include "AIHeaderEnd.h"

#endif
