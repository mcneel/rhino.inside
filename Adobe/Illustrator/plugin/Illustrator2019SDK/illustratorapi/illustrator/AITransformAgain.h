#ifndef __AITransformAgain__
#define __AITransformAgain__

/*
 *        Name:	AITransformAgain.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Transform Again Suite.
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

/** @file AITransformAgain.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAITransformAgainSuite			"AI Transform Again Suite"
#define kAITransformAgainSuiteVersion4	AIAPI_VERSION(4)
#define kAITransformAgainSuiteVersion	kAITransformAgainSuiteVersion4
#define kAITransformAgainVersion		kAITransformAgainSuiteVersion

/** @ingroup Callers
	The transform again caller. See \c #AITransformAgainSuite. */
#define kCallerAITransformAgain 		"AI Transform Again"

/** @ingroup Selectors
	The transform again selector. See \c #AITransformAgainSuite. */
#define kSelectorAITransformAgain		"AI Go"


/*******************************************************************************
 **
 ** Types
 **
 **/

/** The contents of a transform again message. See \c #AITransformAgainSuite. */
typedef struct {
	/** The message data */
	SPMessageData d;
} AITransformAgainMessage;


/*******************************************************************************
 **
 **	Suite Record
 **
 **/

/**	@ingroup Suites
	When Illustrator performs a transformation using a built-in tool or menu item,
	the user can repeat the action again easily by using the Transform Again command.
	This suite allows you to register your plug-in to receive the Transform Again
	command. If a tool does a rotation in three dimensions, for example, it could
	allow the user to repeat the transformation.

	The Transform Again command does not allow a user interface; you must store any
	user parameters needed when your plug-in performs the initial transformation.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITransformAgainSuite and \c #kAITransformAgainVersion.
 */
typedef struct {

	/** Registers for the \c #kSelectorAITransformAgain selector. Call this
		after a transformation is performed, to allow the same transformation
		to be repeated if the user chooses the Transform Again menu item.
		@code
// add the transform again
sAgain->SetTransformAgain( message->d.self );
		@endcode
		The plug-in receives the selector until the user does a different transformation.
		If more than one plug-in calls this function, the last one to make the call
		receives the selector.

		In response to the \c #kSelectorAITransformAgain selector, the plug-in
		should repeat the previous transformation. For example:
		@code
// transform again handler
static AIErr repeatTransform (AITransformAgainMessage *message) {
	AIErr error = kNoErr;

	error = acquireSuites(message->d.basic);
	if (error) goto error;
	changeSelection;
	sUndo->SetUndoText((char*)g->undoMove, (char*)g->redoMove);

error:
	error = releaseSuites(message->d.basic);
	return error;
}
		@endcode
	 		@param self This plug-in.
	 	*/
	AIAPI AIErr (*SetTransformAgain)( SPPluginRef self );

	/** Retrieves the plug-in that is currently registered to receive
		the next \c #kSelectorAITransformAgain selector.
			@param plugin A buffer in which to return the plug-in reference,
				or \c NULL if the last transformation was performed by the
				application, rather than a plug-in.
		*/
	AIAPI AIErr (*GetTransformAgain)( SPPluginRef *plugin );

} AITransformAgainSuite;


#include "AIHeaderEnd.h"


#endif
