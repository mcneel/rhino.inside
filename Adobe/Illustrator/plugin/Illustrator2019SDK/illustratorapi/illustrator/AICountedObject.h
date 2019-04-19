#ifndef __AICountedObject__
#define __AICountedObject__

/*
 *        Name:	AICountedObject.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Counted Object Suite.
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


#include "AIHeaderBegin.h"

/** @file AICountedObject.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAICountedObjectSuite				"AI Counted Object Suite"
#define kAICountedObjectSuiteVersion3		AIAPI_VERSION(3)
#define kAICountedObjectSuiteVersion		kAICountedObjectSuiteVersion3
#define kAICountedObjectVersion				kAICountedObjectSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	These functions allow you to maintain the reference count for Illustrator
	object types that are returned through plug-in APIs. Suites for object types
	that are reference counted provide their own functions for incrementing and
	decrementing the count. You can use either those functions, or the functions
	in this suite, which work with any reference-counted object type.

	Reference-counted objects follow these conventions:

	\li A function that returns a pointer to a reference-counted object
	increments the count before returning the object. The caller must
	decrement the count when the object is no longer needed.

	\li If a plug-in passes a reference-counted object in a message to
	another plug-in or as a parameter to a callback function, the plug-in should
	not decrement the count.

	\li If a plug-in passes a reference counted-object to a function that needs
	to keep the object beyond the duration of the call, that function
	increments the count. The plug-in should still decrement its count
	if necessary when done with the object.

	@see \c #AIEntrySuite for an exception to these rules.

	@note Correctly managing reference counts can be difficult. Failure to do
	so results in memory leaks. It is recommended that C++ client code
	use the \c #ai::Ref template class to automatically manage these counts.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICountedObjectSuite and \c #kAICountedObjectVersion.
*/

typedef struct {

	/** Increments an object reference count. (Note that this
		function returns a numeric value, not an error code.)
			@param object The object. Can be \c null.
			@return The number of references after the increment.
	*/
	AIAPI ai::int32 (*AddRef) ( void* object );

	/** Decrements an object reference count. (Note that this
		function returns a numeric value, not an error code.)
			@param object The object. Can be \c null.
			@return The number of references after the decrement.
	*/
	AIAPI ai::int32 (*Release) ( void* object );

} AICountedObjectSuite;


#include "AIHeaderEnd.h"


#endif
