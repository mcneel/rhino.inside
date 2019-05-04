#ifndef __ASUserInteraction__
#define __ASUserInteraction__

/*
 *        Name:	ASUserInteraction.h
 *   $Revision: 1 $
 *      Author:	 Andy Bachorski
 *        Date:
 *     Purpose:	Adobe Standard User Interaction Suite
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


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __ASTypes__
#include "ASTypes.h"
#endif


#include "SPBasic.h"

#ifndef  __UserInteractionCheckerDefined__
#include "IAIUnicodeString.h"
#endif

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

/** User interaction suite name. */
#define kASUserInteractionSuite				"AS User Interaction Suite"
/** User interaction suite version. */
#define kASUserInteractionSuiteVersion4		4
/** User interaction suite version. */
#define kASUserInteractionSuiteVersion		kASUserInteractionSuiteVersion4
/** User interaction suite name. */
#define kASUserInteractionVersion			kASUserInteractionSuiteVersion

/*******************************************************************************
 **
 **	Error codes
 **
 **/

/** @ingroup Errors
	See \c #ASUserInteractionSuite. */
#define kErrUnknowInteractionLevel		'UILv'


/*******************************************************************************
 **
 **	Types
 **
 **/
/** User-interaction constants. This is an application preference for whether the
	application responds to messages with a modal dialog or alert, or by
	writing to a log file. */
typedef enum _t_ASInteractionAllowed {
	/** The application cannot display any modal dialogs or alerts.
		A message is written to a log file instead.  */
    kASInteractWithNone         = -1,		//	Don't interact
	/** In Mac OS, display alerts for self-sent messages.
		In Windows, this is the same as \c #kASInteractWithAll. */
    kASInteractWithSelf         = 0,		//	Interact for self-send messages
	/** In Mac OS, display alerts for local and self-sent messages, but not remote messages.
		In Windows, this is the same as \c #kASInteractWithAll.*/
    kASInteractWithLocal        = 1,		//	Interact for local & self-send messages (not remote messages)
	/** The application can display any modal dialog or alerts. */
    kASInteractWithAll          = 2			//	Interact for all messages
} ASInteractionAllowed;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides access to the application preference for how the
	application responds to messages. When user interaction is on,  the
	application displays alerts in response to informational, warning, and
	error messages. When it is off, the application writes to a log file.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kASUserInteractionSuite and \c #kASUserInteractionVersion.
	*/
typedef struct {

	/** Reports the level of interaction that is allowed between
		the application and the user, according to the application preference.
		(Note that this function returns a constant value, not an error code.)
			@return The interaction level constant.
		*/
	ASAPI ASInteractionAllowed	(*GetInteractionAllowed) ( void );
	/** Sets  the level of interaction that is allowed between
		the application and the user. The default value is \c #kASInteractWithAll.
			@param allowed The interaction level constant.
		*/
	ASAPI ASErr					(*SetInteractionAllowed) ( ASInteractionAllowed allowed );

	/** Reports whether interaction is allowed between the application and the user
		in the current application context.
		(Note that this function returns a boolean value, not an error code.)
			@return True if the interaction level is anything other than
				\c #kASInteractWithNone.
		*/
	ASAPI ASBoolean 			(*InteractWithUser) ( void );

 	/** Sets the log message using a C string. This message is
 		written to the log file when an alert condition occurs,
 		if user interactivity is turned off.
			@param msg The message text, a null-terminated UTF-8 string.
		*/
	ASAPI ASErr 			    (*LogInteraction) ( const char *msg );

 	/** Sets the log message using a Unicode string. This message is
 		written to the log file when an alert condition occurs,
 		if user interactivity is turned off.
			@param msg The message text, a null-terminated UTF-16 string.
		*/
	ASAPI ASErr 			    (*LogInteractionW) ( const ASUnicode *msg );


} ASUserInteractionSuite;

#ifndef  __UserInteractionCheckerDefined__
//
// A stack based class for checking the user interaction level.
//
class ASUserInteractionChecker
{
public:
	/** Constructor. Creates a user-interaction checker object.
			@param spBasic The SPBasic suite object.
			@return The new object.
		*/
	ASUserInteractionChecker(SPBasicSuite *spBasic)
	{
		m_SPBasic = spBasic;
		m_SuitePtr = NULL;
		if (m_SPBasic)
		{
			ASErr error = m_SPBasic->AcquireSuite(kASUserInteractionSuite,
										kASUserInteractionVersion,
										(const void **)&m_SuitePtr);
			if(error != kNoErr)
			{
				m_SuitePtr = NULL;
			}
		}
	}
	/** Reports whether interaction is allowed between the application and the user
		in the current application context.
		(Note that this method returns a boolean value, not an error code.)
			@return True if the interaction level is anything other than
				\c #kASInteractWithNone.
 		*/
	ASBoolean InteractWithUser(void)
	{
		if (m_SuitePtr)
			return m_SuitePtr->InteractWithUser();
		else
			return true;
	}

	/** Sets the message to write to the user-interaction log
		when an Info alert occurs, if user interactivity is turned off.
			@param msg1 The message string.
			@param msg2 Optional. Another message string.
		*/
	ASErr logInfo(const ai::UnicodeString& msg1, const ai::UnicodeString *msg2=NULL)
	{
		ASErr err = kNoErr;

		if (m_SuitePtr && !InteractWithUser())
		{
			if (msg2)
			{
				ai::UnicodeString::UTF32TextChar c = ' ';
				ai::UnicodeString msg = msg1;
				msg += ai::UnicodeString(1,c);
				msg.append(*msg2);
				err = m_SuitePtr->LogInteraction(msg.as_UTF8().c_str());
			}
			else
			{
				err = m_SuitePtr->LogInteraction(msg1.as_UTF8().c_str());
			}
		}

		return err;
	}
	/** Sets the message to write to the user-interaction log
		when an Error alert occurs,	if user interactivity is turned off.
			@param msg1 The message string.
			@param msg2 Optional. Another message string.
		*/
	void logError(const ai::UnicodeString& msg1, const ai::UnicodeString *msg2=NULL)
	{
		ai::UnicodeString msg("Error: ");
		msg += msg1;
		logInfo(msg, msg2);
	}
	/** Sets the message to write to the user-interaction log
		when a Warning alert occurs, if user interactivity is turned off.
			@param msg1 The message string.
			@param msg2 Optional. Another message string.
		*/
	void logWarning(const ai::UnicodeString& msg1, const ai::UnicodeString *msg2=NULL)
	{
		ai::UnicodeString msg("Warning: ");
		msg += msg1;
		logInfo(msg, msg2);
	}
	/** Destructor */
	~ASUserInteractionChecker()
	{
		if (m_SuitePtr && m_SPBasic)
		{
			m_SPBasic->ReleaseSuite(kASUserInteractionSuite, kASUserInteractionVersion);
			m_SuitePtr = NULL;
		}
	}

private:
	SPBasicSuite *m_SPBasic;
	ASUserInteractionSuite *m_SuitePtr;
};

#endif // __UserInteractionCheckerDefined__

#include "AIHeaderEnd.h"

#endif //	__ASUserInteraction__

