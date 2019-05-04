/*
 *        Name:  IAIRefAutoSuite.cpp
 *   $Revision:  1 $
 *      Author:  dmaclach
 *        Date:  Thursday, March 25, 2004 11:26:12
 *     Purpose:  
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

/** @file IAIRefAutoSuite.cpp*/
#define AICOUNTEDOBJECTSUITE_DEFINED 1
#include "IAIRef.h"
#include "AutoSuite.h"

use_suite(AICountedObject)

/**
	This implements the GetAICountedObjectSuitePtr for autosuited AICountedObjectSuites.
*/

AICountedObjectSuite *ai::GetAICountedObjectSuitePtr()
{
	return const_cast<AICountedObjectSuite *>(sAICountedObject.operator->());
}
