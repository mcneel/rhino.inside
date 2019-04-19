#ifndef __AIApplication__
#define __AIApplication__

/*
 *        Name:	AIApplication.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Document Suite.
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

#ifndef __DocumentList__
#include "AIDocumentList.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIApplication.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIApplicationSuite					"AI Application Suite"
#define kAIApplicationSuiteVersion3	AIAPI_VERSION(3)

// latest version
#define kAIApplicationSuiteVersion		kAIApplicationSuiteVersion3
#define kAIApplicationVersion				kAIApplicationSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The Application suite provides functions for querying and controlling the state
	of a plug-in host application.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIApplicationSuite	and \c #kAIApplicationVersion.
 */

typedef struct {

	/** Instructs the application to quit. This is identical to the user issuing a quit command. */
	AIAPI AIErr	(*Quit)	();
	/** Returns true if this is the first time the application has run. Not implemented.Always returns false. */
	AIAPI ASBoolean	(*IsFirstTime)();
	/** Returns true if the application visible. Only implemented in Windows. */
	AIAPI ASBoolean	(*IsVisible)();
	/** Hide or show the application. Not implemented. */
	AIAPI AIErr	(*SetVisible)(ASBoolean bVisible);

} AIApplicationSuite;



#include "AIHeaderEnd.h"


#endif
