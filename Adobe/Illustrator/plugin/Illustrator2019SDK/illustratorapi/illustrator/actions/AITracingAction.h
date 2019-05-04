#ifndef _AITRACINGACTION_H_
#define _AITRACINGACTION_H_

/*
 *        Name:	AITracingAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 10.0 Actions for envelopes.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#ifndef __AIActionManager_h__
#include "AIActionManager.h"
#endif



// -----------------------------------------------------------------------------
// Action: kAITracingMenuAction
// Purpose: runs some functionality accessible through the Tracing submenus
//
// Parameters:
//	- kAITracingMenuItem, enum: the menu item to run
// -----------------------------------------------------------------------------

/** @ingroup Actions
	Executes items in the Tracing submenus.
		@param #kAITracingMenuItem The menu item to run,
			a \c kTracingAction* constant.See \c AITracingAction.h.
	*/
#define kTracingPluginActionName	"ai_plugin_tracing"

/**	Parameter to \c #kTracingPluginActionName.
	The menu item to run, a \c kTracingAction* constant. */
const ActionParamKeyID kAITracingMenuItem	= 'menu'; // enum

/** Menu item identifier for \c #kAITracingMenuItem: Make */
#define kTracingActionMake						1
/** Menu item identifier for \c #kAITracingMenuItem: Make and Expand  */
#define kTracingActionMakeAndExpand				2
/** Menu item identifier for \c #kAITracingMenuItem: Release */
#define kTracingActionRelease					4
/** Menu item identifier for \c #kAITracingMenuItem: Expand */
#define kTracingActionExpand					6


#endif // _AITRACINGACTION_H_