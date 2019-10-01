#ifndef __AIPlugin__
#define __AIPlugin__

/*
 *        Name:	AIPlugin.h
 *   $Revision: 10 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Standard Plug-in Includes and Definitions
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


#ifndef __SPAccess__
#include "SPAccess.h"
#endif

#ifndef __SPInterf__
#include "SPInterf.h"
#endif

#ifndef __SPProps__
#include "SPProps.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIPluginSuite				"AI Plugin Suite"
#define kAIPluginSuiteVersion		AIAPI_VERSION(5)

/** @ingroup Notifiers
	Sent after all plug-ins	have received and
	processed \c #kAIApplicationStartedNotifier.
*/
#define kAIAllPluginStartedNotifier		"AI All Plug-ins Started Notifier"

/** @ingroup Notifiers
	Sent before Illustrator sends the application-stopped notifier.
*/
#define kAIPluginStoppingNotifier		"AI All Plug-ins Stopping Notifier"



/** Options available to plug-ins. */
enum AIPluginOptions {
	/**	When  true (the default for plug-in filters) Illustrator automatically
		selects any artwork a plug-in modifies while running,
		and that art remains selected when the plug-in finishes running.
		Any artwork that was in a selected state on entry but not touched by the
		plug-in is deselected.

		When false (the default for all other plug-ins) the plug-in handles
		the selection and deselection of artwork before exit.
	*/
	kPluginWantsResultsAutoSelectedOption	= (1<<1),
 	/** When true, retains the state of partially selected path objects in the plug-in
 		when an Undo operation is performed.

 		When false (the default), when a plug-in edits a partially selected path object
 		and the edit is undone, Illustrator does not retain the partial selection
 		state that existed prior to the edit.
 	*/
 	kPluginWantsPartialPathSelectionOption	= (1<<2)


};

/** @ingroup Suites
	These functions access Illustrator-specific plug-in options, and allow
	Illustrator plug-ins to send messages to one another.

	@note The original version of this suite, version 2, has been largely replaced by
	the PICA \c #SPPluginsSuite, a core suite available to other Adobe applications.
	Use that suite to access the plug-in list, identify their type and location, and so on.
	Similarly, it is better to use the PICA \c #SPInterfaceSuite to send messages.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPluginSuite and \c #kAIPluginSuiteVersion.
	*/
typedef struct {

	/** Retrieves the Illustrator-specific options for a plug-in.
			@param plugin The plug-in reference.
			@param options [out] A buffer in which to return the options,
				an #AIPluginOptions value.
		*/
	AIAPI AIErr (*GetPluginOptions) ( SPPluginRef plugin, ai::int32 *options );

	/** Sets the Illustrator-specific options for a plug-in.
			@param plugin The plug-in reference.
			@param options The new options, an #AIPluginOptions value.
		*/
	AIAPI AIErr (*SetPluginOptions) ( SPPluginRef plugin, ai::int32 options );

	/** Sets up data for sending a message to another plug-in.
			@param plug-in The destination plug-in.
			@param data A pointer to the message data.
			@see \c #CallPlugin()
		*/
	AIAPI AIErr (*SetupPluginData) ( SPPluginRef plugin, void *data );

	/** Sends a message to the main entry point of another Illustrator plug-in.
		For example:
 @code
// The plug-in reference for the plug-in to call.
SPPluginRef somePlugin;
// A plug-in message structure, contains an SPMessageData as first member.
AISomePluginMessage message;

// fill out the message structure
error = sAIPluginSetupPluginData(somePlugin, &message.d);
// send the message to the plug-in
if (!error)
	error = sAIPluginCallPlugin(somePlugin, kSomePluginSelector, &message );
// release the message data memory.
if (!error)
	error = sAIPluginEmptyPluginData(somePlugin, &message.d);
@endcode
			@param plugin The destination plug-in.
			@param selector	The selector for the destination plug-in, see @ref Selectors.
			@param message The message, of the type suitable for the selector.
			@note It is recommended that you use the newer PICA \c #SPInterfaceSuite to send messages.
		*/
	AIAPI AIErr (*CallPlugin) ( SPPluginRef plugin, const char *selector, void *message );

	/** Ensures that the destination plug-in's global data (as sent in \c #SPMessageData::globals)
		is properly stored back into the plug-in that modified it when responding to the message.
			@param plugin The destination plug-in.
			@param data A pointer to the message data.
			@note It is recommended that you use the newer PICA \c #SPInterfaceSuite to send messages.
		*/
	AIAPI AIErr (*EmptyPluginData) ( SPPluginRef plugin, void *data );

} AIPluginSuite;


#include "AIHeaderEnd.h"

#endif
