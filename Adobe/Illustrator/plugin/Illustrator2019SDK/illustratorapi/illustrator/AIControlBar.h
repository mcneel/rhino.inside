/************************************************************************/
/*																		*/
/*	Name		:	AIControlbar.h										*/	
/*	$Revision	:	1$													*/
/*	Author		:														*/
/*	Date		:	7 Sep 2011											*/
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

#ifndef __AICONTROLBAR_H__
#define __AICONTROLBAR_H__

#include "AITypes.h"
#include "IAIUnicodeString.h"

#include "AIHeaderBegin.h"

/** @file AIControlBar.h */

/*******************************************************************************
**
**	Constants
**
**/

#define kAIControlBarSuite					"AI Control Bar Suite"
#define kAIControlBarSuiteVersion2			AIAPI_VERSION(2)
#define kAIControlBarSuiteVersion			kAIControlBarSuiteVersion2
#define kAIControlBarVersion				kAIControlBarSuiteVersion

/*******************************************************************************
**
** Types
**
**/
#ifdef WIN_ENV
typedef HWND AIControlBarPlatformWindow;
#elif defined(MAC_ENV)
	#ifdef __OBJC__
	@class NSView;
	typedef NSView*	AIControlBarPlatformWindow;
	#else
	typedef void*	AIControlBarPlatformWindow;
	#endif
#else
#error unknown configuration
#endif

/**	Reference to a control-bar object. */
typedef struct _opaque_AIControlBar* AIControlBarRef;

/** A developer-defined data object associated with a control bar. */
typedef void* AIControlBarUserData;

/** Prototype of a function to be called when the visibility of a Control Bar has changed.
	@param inControlBar			The control-bar object.
	@param isVisible			The new visibility state of the Control Bar, true if visible
*/
typedef void AIAPI (*AIControlBarVisibilityChangedNotifyProc)(AIControlBarRef inControlBar, AIBoolean isVisible);

/** Prototype of a function to be called when the size of a Control Bar has changed.
	@param inControlBar			The control-bar object.
*/
typedef void AIAPI (*AIControlBarSizeChangedNotifyProc)(AIControlBarRef inControlBar);


/*******************************************************************************
**
** Error Values returned by suite.
**
**/
/** @ingroup Errors
	See \c #AIControlBarSuite */
#define kAIInvalidControlBarRef		'INVD'


/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
This suite provides functions for creating and managing control bars.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIControlBarSuite	and \c #kAIControlBarSuiteVersion.
*/
struct AIControlBarSuite{

	/** Creates a new control-bar object
	@param inPluginRef			The plug-in that is creating the control bar.
	@param inControlBarSize		Size of the new control bar.
	@param inMinWidth			Minimum width of the new control bar.
	@param inMaxWidth			Maximum width of the new control bar.
	@param inUserData			Developer-defined data to be associated with the control bar.
	@param outControlBar		[out] A buffer in which to return the new control-bar object.
	*/
	AIAPI AIErr (*Create)(SPPluginRef inPluginRef, const AISize& inControlBarSize, AIReal inMinWidth, AIReal inMaxWidth,
						AIControlBarUserData inUserData, AIControlBarRef& outControlBar);


	/** Deletes a control bar object.
	This must be called when the plug-in receives a shutdown notification, \c #kAIApplicationShutdownNotifier.
	@param inControlBar			The control bar object.
	*/
	AIAPI AIErr (*Destroy)(AIControlBarRef inControlBar);


	/** Retrieves developer-defined data associates with a control bar.
	@param inControlBar			The control Bar object.
	@param outUserData			[out] A buffer in which to return the developer-defined data.
	*/
	AIAPI AIErr (*GetUserData)(AIControlBarRef inControlBar, AIControlBarUserData& outUserData);


	/** Associates developer-defined data with a control bar, which can be used in developer-defined callbacks.
	@param inControlBar			The control bar object.
	@param inUserData			The developer-defined data.
	*/
	AIAPI AIErr (*SetUserData)(AIControlBarRef inControlBar, AIControlBarUserData inUserData);


	/** Retrieves the platform-specific window or view used for the control bar.
	@param inControlBar					The control bar object.
	@param outControlBarPlatformWindow	[out] A buffer in which to return the platform-specific window or view.
	*/
	AIAPI AIErr (*GetPlatformWindow)(AIControlBarRef inControlBar, AIControlBarPlatformWindow& outControlBarPlatformWindow);


	/** Shows or hides a control bar.
	@param inControlBar					The control bar object.
	@param inShow						True to make the control bar visible, false to hide it.
	*/
	AIAPI AIErr (*Show)(AIControlBarRef inControlBar, AIBoolean inShow);


	/** Reports the current visibility state of a control bar.
	@param inControlBar					The control bar object.
	@param outIsShown					[out] A buffer in which to return true if the control bar is visible, false otherwise.
	*/
	AIAPI AIErr (*IsShown)(AIControlBarRef inControlBar, AIBoolean& outIsShown);


	/** Retrieves the current width of control bar.
	@param inControlBar					The control bar object.
	@param outControlBarWidth			[out] A buffer in which to return the width value in pixels.
	*/
	AIAPI AIErr (*GetWidth)(AIControlBarRef inControlBar, AIReal& outControlBarWidth);


	/**  Sets the width of control bar.	If the width is out of allowed bounds, returns an error.
 	@param inControlBar					The control bar object.
	@param inControlBarWidth			The new width value in pixels. Must be >= minWidth and <= maxWidth.
	*/
	AIAPI AIErr (*SetWidth)(AIControlBarRef inControlBar, AIReal inControlBarWidth);


	/** Retrieves the current minimum width of a control bar.
	@param inControlBar					The control bar object.
	@param outMinWidth					[out] A buffer in which to return the minimum width value in pixels.
	*/
	AIAPI AIErr (*GetMinimumWidth)(AIControlBarRef inControlBar, AIReal& outMinWidth);


	/** Sets the minimum width of a control bar.
	@param inControlBar					The control bar object.
	@param inMinWidth					The new minimum width in pixels; must be > 0 and <= maxWidth.
	*/
	AIAPI AIErr (*SetMinimumWidth)(AIControlBarRef inControlBar, AIReal inMinWidth);


	/** Retrieves the current maximum width of a control bar.
	@param inControlBar					The control bar object.
	@param outMaxWidth					[out] A buffer in which to return the maximum width value in pixels.
	*/
	AIAPI AIErr (*GetMaximumWidth)(AIControlBarRef inControlBar, AIReal& outMaxWidth);


	/** Sets the maximum width of a control bar.
	@param inControlBar					The control bar object.
	@param inMaxWidth					The new maximum width in pixels; must be >= minWidth.
	*/
	AIAPI AIErr (*SetMaximumWidth)(AIControlBarRef inControlBar, AIReal inMaxWidth);


	/** Moves a control bar to a specific location. If the control bar is docked, does nothing.
	@param inControlBar					The control bar object.
	@param inPoint						The new position in global screen coordinates.
	*/
	AIAPI AIErr (*Move)(AIControlBarRef inControlBar, const AIPoint& inPoint);


	/** Sets a callback procedure to call when the visibility of a control bar has changed.
	@param inControlBar						The control bar object.
	@param inVisibilityChangedNotifyProc	The new callback procedure.
	*/
	AIAPI AIErr (*SetVisibilityChangedNotifyProc)(AIControlBarRef inControlBar, AIControlBarVisibilityChangedNotifyProc inVisibilityChangedNotifyProc);


	/** Sets a callback procedure to call when the size of a control bar has changed.
	@param inControlBar						The control bar object.
	@param inSizeChangedNotifyProc			The new callback procedure.
	*/
	AIAPI AIErr (*SetSizeChangedNotifyProc)(AIControlBarRef inControlBar, AIControlBarSizeChangedNotifyProc inSizeChangedNotifyProc);
};

#include "AIHeaderEnd.h"

#endif //__AICONTROLBAR_H__