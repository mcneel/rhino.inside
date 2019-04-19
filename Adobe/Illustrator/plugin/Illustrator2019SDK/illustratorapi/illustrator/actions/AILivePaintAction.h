#ifndef _AILIVEPAINTACTION_H_
#define _AILIVEPAINTACTION_H_

/*
 *        Name:	AILivePaintAction.h
 *     Purpose:	Adobe Illustrator 12.0 Actions for Live Paint objects.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2007 Adobe Systems Incorporated.
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

/** Action > LivePaint command identifier, "Make" */
#define kPlanarActionMake				1
/** Action > LivePaint command identifier, "Expand" */
#define kPlanarActionRelease			2
/** Action > LivePaint command identifier, "Release" */
#define kPlanarActionExpand				3
/** Action > LivePaint command identifier, "Gap Options" */
#define kPlanarActionOptions			4


/** @ingroup Actions
	Runs an operation from a Live Paint submenu
		@param #kAILivePaintMenuItem The menu item to run, one of:
					<br>\c #kPlanarActionMake "Make"
					<br>\c #kPlanarActionRelease "Release"
					<br>\c #kPlanarActionExpand "Expand"
					<br>\c #kPlanarActionOptions "Gap Options"
		@param #kAILivePaintGapDetect When item is "Gap Options", whether to
			turn on gap detection.
		@param #kAILivePaintGapSize	When item is "Gap Options", the point size of
			gaps to tolerate.
		@param #kAILivePaintCloseGaps When item is "Gap Options", whether to
			close gaps with real paths.
	*/
#define kAILivePaintMenuAction							"ai_plugin_planetx"

/** Parameter to \c #kAILivePaintMenuAction. The menu item to run. */
const ActionParamKeyID kAILivePaintMenuItem				= 'menu'; // enum
/** Parameter to \c #kAILivePaintMenuAction. Whether to turn on gap detection.*/
const ActionParamKeyID kAILivePaintGapDetect			= 'gdct'; // bool
/** Parameter to \c #kAILivePaintMenuAction. The point size of gaps to tolerate.*/
const ActionParamKeyID kAILivePaintGapSize				= 'gsiz'; // unit real
/** Parameter to \c #kAILivePaintMenuAction. Whether to close gaps with real paths. */
const ActionParamKeyID kAILivePaintCloseGaps			= 'gexp'; // bool

#endif // _AILIVEPAINTACTION_H_
