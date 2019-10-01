/*
*        Name:	AIUITheme.h
*      Author:
*        Date:
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2007-2008 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

#ifndef AIUITheme_h__
#define AIUITheme_h__



/*******************************************************************************
**
**	Imports
**
**/


#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIRealMath__
#include "AIRealMath.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIUITheme.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAIUIThemeSuite					"AI User Interface Theme Suite"
#define kAIUIThemeSuiteVersion			AIAPI_VERSION(2)
#define kAIUIThemeVersion				kAIUIThemeSuiteVersion

/*******************************************************************************
**
**	Notifier constants
**
**/
/** @ingroup Notifiers
    Sent when UI brightness is changed.
*/
#define kAIUIBrightnessChangedNotifier        "AI UI Brightness Changed Notifier"

/** Constants for \c #AIUIThemeSuite::GetUIThemeColor()
   that identify predefined UI themes. */
enum AIUIThemeSelector
{
	/** Theme for dialogs. */
	kAIUIThemeSelectorDialog = 0,

	/** Theme for panels. */
	kAIUIThemeSelectorPanel,

	/** Internal use  */
	kAIAUIThemeSelectorLast = 0xFFFF
};

/** Constants for \c #AIUIThemeSuite::GetUIThemeColor()
   that identify predefined UI component colors. */
enum AIUIComponentColor
{
	/** Invalid component color. */
	kAIUIComponentColorNone = -1,

	/** Current UI background color. */
	kAIUIComponentColorBackground = 0,

	/** Current UI text color. */
	kAIUIComponentColorText,

	/** Current UI focus ring color. */
	kAIUIComponentColorFocusRing,

	/** Current UI text edit color. */
	kAIUIComponentColorEditText,

	/** Current UI text edit background color.  */
	kAIUIComponentColorEditTextBackground,

	/** Internal use  */
	kAIUIComponentColorLast = 0xFFFF
};

/** Color record used to return a theme color from \c #AIUIThemeSuite::GetUIThemeColor().  */
struct AIUIThemeColor
{
	/** Alpha (transparency) value. */
	AIReal alpha;
	 /** Red value. */
	AIReal red;
	 /** Green value. */
	AIReal green;
	 /** Blue value. */
	AIReal blue;

	/** Default constructor */
	AIUIThemeColor(AIReal a = kAIRealOne, AIReal r = kAIRealZero, AIReal g = kAIRealZero, AIReal b = kAIRealZero) : alpha(a), red(r), green(g), blue(b) {}
};


/*******************************************************************************
**
**	Suite
**
**/
/** @ingroup Suites
    This suite allows you to query UI color and brightness parameters.

    \li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
    \c #kAIUIThemeSuite  and \c #kAIUIThemeVersion.
*/

struct AIUIThemeSuite {

	/** Retrieves a current UI theme color,
        @param themeSelector	The theme, a constant value from \c #AIUIThemeSelector.
        @param componentColor	The component color to find, a constant value from \c # AIUIComponentColor.
        @param aiColor			[out] A buffer in which to return the theme color value.
	*/
	AIAPI AIErr (*GetUIThemeColor)(ai::int32 themeSelector, ai::int32 componentColor, AIUIThemeColor& aiColor);


    /**
        Reports whether the current UI theme is dark.</br>
        (Note that this function returns a Boolean value, not an error code.)
        @return True if the current UI theme is dark, otherwise false.
	*/
	AIAPI AIBoolean (*IsUIThemeDark)();

};

#include "AIHeaderEnd.h"

#endif // AIUITheme_h__
