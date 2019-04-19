#ifndef __AITimer__
#define __AITimer__

/*
 *        Name:	AITimer.h
 *   $Revision: 5 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Timer Suite.
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

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif


#include "AIHeaderBegin.h"

/** @file AITimer.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAITimerSuite			"AI Timer Suite"
#define kAITimerSuiteVersion	AIAPI_VERSION(5)
#define kAITimerVersion			kAITimerSuiteVersion


/** @ingroup Callers
	See \c #AITimerSuite  */
#define kCallerAITimer 			"AI Timer"

/** @ingroup Selectors
	See \c #AITimerSuite  */
#define kSelectorAIGoTimer		"AI Go"

/** Default number of clock ticks per second. See \c #AITimerSuite  */
#define kTicksPerSecond			60


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a timer, never dereferenced. Access with \c #AITimerSuite */
typedef struct _t_AITimerOpaque *AITimerHandle;

/** The contents of a timer message, sent with \c #kSelectorAIGoTimer */
typedef struct {
	/** The message data. */
	SPMessageData d;
	/** The timer plug-in receiving the message.  */
	AITimerHandle timer;
} AITimerMessage;


/*******************************************************************************
 **
 **	Suite Record
 **
 **/

/** @ingroup Suites
	These functions allow you to schedule events by registering timer plug-ins.
	Use these functions to add timers, turn timers on and
	off, and enumerate and access the installed timer plug-ins.

	Illustrator notifies registered timer plug-ins when a specified period of
	time has passed.  It sends a message to the plug-in's main entry point
	with caller \c #kCallerAITimer and selector \c #kSelectorAIGoTimer.

	Timer periods are specified in clock ticks. There are \c #kTicksPerSecond
	ticks in a second.

	Timers are typically used in conjunction with other plug-ins, such as
	menus or windows, which determine when an update is	needed.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITimerSuite and \c #kAITimerVersion.
 */
typedef struct {

	/** Adds a timer plug-in to Illustrator. Use at startup.
			@param self This plug-in.
			@param name The unique identifying name of the timer.
			@param period The time period for notification, the number of
				clock ticks that should pass before the timer is notified.
				For seconds, multiply the number of seconds by \c #kTicksPerSecond.
			@param timer [out] A buffer in which to return the timer reference.
				If you install more than one timer plug-in, save to compare
				to the reference passed in the \c #AITimerMessage to determine
				which action to take.

		This call requests notification once a second:
@code
	AIErr error;
	error = sTimer->AddTimer( message->d.self, "Time for Timer", kTicksPerSecond, &g->secondTimer );
@endcode
		*/
	AIAPI AIErr (*AddTimer) ( SPPluginRef self, const char *name, ai::int32 period,
				AITimerHandle *timer );

	/** Retrieves the name string of a timer.
			@param time The timer reference.
			@param name [out] A buffer in which to return the name string.
				Do not modify this string.
		 */
	AIAPI AIErr (*GetTimerName) ( AITimerHandle timer, char **name );

	/** Reports whether a timer is active. An active timer receives
		periodic notifications.
			@param time The timer reference.
			@param active [out] A buffer in which to return true if
				the timer is active.
		*/
	AIAPI AIErr (*GetTimerActive) ( AITimerHandle timer, AIBoolean *active );

	/** Activates or deactivates a timer. You must deactivate timers
		as part of terminating the plug-in.
			@param time The timer reference.
			@param active True to activate the timer, false to deactivate it.
		*/
	AIAPI AIErr (*SetTimerActive) ( AITimerHandle timer, AIBoolean active );

	/** Retrieves the notification interval for a timer.
			@param time The timer reference.
			@param period [out] A buffer in which to return the
				interval, in clock ticks. .
		*/
	AIAPI AIErr (*GetTimerPeriod) ( AITimerHandle timer, ai::int32 *period );

	/**  Sets the notification interval for a timer.
			@param time The timer reference.
			@param period The new interval, in clock ticks. For seconds,
				multiply the number of seconds by \c #kTicksPerSecond.
		 */
	AIAPI AIErr (*SetTimerPeriod) ( AITimerHandle timer, ai::int32 period );

	/** Retrieves a reference to the plug-in that installed a timer, to
		use with the \c #AIPluginSuite.
			@param time The timer reference.
			@param plugin [out] A buffer in which to return the
				plug-in reference.
		*/
	AIAPI AIErr (*GetTimerPlugin) ( AITimerHandle timer, SPPluginRef *plugin );

	/** Counts the number of timers available. Use with \c #GetNthTimer()
		to iterate through installed timers.
			@param count [out] A buffer in which to return the number
				of installed timers.
		*/
	AIAPI AIErr (*CountTimers) ( ai::int32 *count );

	/** Retrieves a timer by position index. Use with \c #CountTimers()
		to iterate through installed timers.
			@param n The 0-based position index.
			@param timer [out] A buffer in which to return the timer reference.
		*/
	AIAPI AIErr (*GetNthTimer) ( ai::int32 n, AITimerHandle *timer );

} AITimerSuite;


#include "AIHeaderEnd.h"


#endif
