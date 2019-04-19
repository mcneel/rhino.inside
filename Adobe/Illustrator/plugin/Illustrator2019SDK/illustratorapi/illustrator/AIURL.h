#ifndef _AIURL_H_
#define _AIURL_H_

/*
 *        Name:	AIURL.h
 *   $Revision: 1 $
 *     Purpose:	Adobe Illustrator URL Suite.
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
 *:
 */

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIURL.h */


#define kAIURLSuite				"AI URL Suite"
#define kAIURLSuiteVersion3		AIAPI_VERSION(3)
#define kAIURLSuiteVersion		kAIURLSuiteVersion3
#define kAIURLVersion			kAIURLSuiteVersion

/** @ingroup Errors
	See \c #AIURLSuite */
#define kFailureErr		'FAIL'



/** @ingroup Suites
	This suite provides a simple interface to go to a URL through a web
	browser. You can use this to lead users to your web site for updates or other
	information.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIURLSuite and \c #kAIURLSuiteVersion.
	*/
typedef struct {
	/** Reports whether a web browser is available.
		(Note that this function returns a boolean value, not an error code.)
			@return True if a web browser is available.
		*/
	ASAPI ASBoolean (*IsBrowserAvailable)(void);

	/** Opens a web browser and displays a URL.
		(Note that this function returns a boolean value, not an error code.)
			@param url The URL to display.
			@return True if the web browser is opened successfully.
		*/
	ASAPI ASBoolean (*OpenURL)(const char *url);
} AIURLSuite;


#include "AIHeaderEnd.h"


#endif // _AIURL_H_