#ifndef __AIDeviceInfo__
#define __AIDeviceInfo__

/********************************************************************************
* ADOBE SYSTEMS INCORPORATED
* Copyright 2015 Adobe Systems Incorporated
* All Rights Reserved.

* NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the
* terms of the Adobe license agreement accompanying it.  If you have received this file from a
* source other than Adobe, then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
*
* Author: Vivek Agrawal
* Created: 09/10/2015
* Purpose: Adobe Illustrator Device Info Suite
**************************************************************************/


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIArt__
#include "AIArt.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIDeviceInfo.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIDeviceInfoSuite			"AI DeviceInfo Suite"
#define kAIDeviceInfoSuiteVersion1	AIAPI_VERSION(1)
#define kAIDeviceInfoSuiteVersion	kAIDeviceInfoSuiteVersion1
#define kAIDeviceInfoVersion		kAIDeviceInfoSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/**	@ingroup Suites
	This suite provides functions that allow you to access various informations about the
	device on which illustrator is running or the device which is being connected for
	using illustrator through it.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDeviceInfoSuite and \c #kAIDeviceInfoVersion.
 */
struct AIDeviceInfoSuite {

	/*
	function: To be used to check whether a tablet is connected or not. This only works for Wacom tablets.
	@param:
	@out out: An AIBoolean reference in which to return the status whether a tablet is connected or not. 
	*/
	AIAPI AIErr(*IsTabletConnected) (AIBoolean& out);
	
};

#include "AIHeaderEnd.h"

#endif
