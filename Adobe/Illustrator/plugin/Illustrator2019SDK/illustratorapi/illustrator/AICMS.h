#ifndef __AICMS__
#define __AICMS__

/*
 *        Name:	AICMS.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Color Management System (CMS) Suite
 *				(Currently just a notifier)
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1996-2007 Adobe Systems Incorporated.
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
#include "AITypes.h"


#include "AIHeaderBegin.h"

/** @file AICMS.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/
#define kAICMSSuite				"AI Color Management System Suite"
#define kAICMSSuiteVersion		AIAPI_VERSION(3)
#define kAICMSVersion			kAICMSSuiteVersion

/** @ingroup Notifiers
	Sent whenever the color management settings for are changed.
	 */
#define kAIColorCalibrationChangedNotifier		"AI Color Calibration Changed Notifier"

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

// Internal (placeholder for further development)
/*
typedef struct {
	AIAPI AIErr (*NothingDefinedYet) ( void );
} AICMSSuite;
*/


#include "AIHeaderEnd.h"


#endif
