/************************************************************************/
/*																		*/
/*	Name		:	AIModalParent.h								*/	
/*	$Revision	:	1$													*/
/*	Author		:														*/
/*	Date		:	16 Jan 2012											*/
/*	Purpose		:	Suite for Creating and Managing Control bars		*/
/*																		*/
/*	ADOBE SYSTEMS INCORPORATED											*/					
/*	Copyright 2011 Adobe Systems Incorporated.							*/
/*	All rights reserved.												*/
/*																		*/
/*	NOTICE:  Adobe permits you to use, modify, and distribute this file	*/
/*	in accordance with the terms of the Adobe license agreement			*/
/*	accompanying it. If you have received this file from a source other	*/
/*	than Adobe, then your use, modification, or distribution of it		*/
/*	requires the prior written permission of Adobe.						*/
/*																		*/
/************************************************************************/

#ifndef __AIMODALPARENT_H__
#define __AIMODALPARENT_H__

#include "AITypes.h"
#include "IAIUnicodeString.h"



/** @file AIControlBar.h */

/*******************************************************************************
**
**	Constants
**
**/

#define kAIModalParentSuite					"AI Modal Parent Suite"
#define kAIModalParentSuiteVersion2			AIAPI_VERSION(2)
#define kAIModalParentSuiteVersion			kAIModalParentSuiteVersion2
#define kAIModalParentVersion				kAIModalParentSuiteVersion

/*******************************************************************************
**
** Types
**
**/
#ifdef WIN_ENV
typedef HWND AIPlatformWindow;
#elif defined(MAC_ENV)
	#ifdef __OBJC__
	@class NSWindow;
	typedef NSWindow*	AIPlatformWindow;
	#else
	typedef void*	AIPlatformWindow;
	#endif
#else
#error unknown configuration
#endif

/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
This suite provides functions for specifying the parent window of an AI dialog. 
This is required only when AI's dialog is to be shown over a third party modal dialog on Windows.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIModalParentSuite	and \c #kAIModalParentSuiteVersion.
*/
struct AIModalParentSuite{

	AIAPI AIErr (*SetParent)(const AIPlatformWindow& inParent);

	AIAPI AIErr (*RemoveParent)();
	
};


#endif //__AIMODALPARENT_H__