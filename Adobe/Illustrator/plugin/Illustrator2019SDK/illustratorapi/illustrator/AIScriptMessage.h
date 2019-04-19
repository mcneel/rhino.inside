#ifndef __AIScriptMessage__
#define __AIScriptMessage__

/*
 *        Name:	AIScriptMessage.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator AIScriptMessage.
 *
 * Copyright (c) 2010 Adobe Systems Incorporated, All Rights Reserved.
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

#include "IAIUnicodeString.h"

#include "AIHeaderBegin.h"

/** @file AIScriptMessage.h */
/*******************************************************************************
 **
 **	Constants
 **
 **/
#define kCallerAIScriptMessage				"AI Script Message Caller"


/**
	Script message structure
*/
struct AIScriptMessage {
	/** A buffer in which to return the modified artwork when the message is completed. */
	AIScriptMessage():art(NULL) {}
	/** The message data */
	SPMessageData d;
	/** The art to be operated on. */
	AIArtHandle art;
	/** Developer-defined input parameters to the message. */
	ai::UnicodeString inParam;
	/** Developer-defined output parameters for the message. */
	ai::UnicodeString outParam;
};

/*
Sample code to send a script message

AIErr SendScriptMessage(const char* pluginName, const char* selector, const ai::Unicodestring& inputString, ai::Unicodestring& outString)
{
	SPPluginRef pluginRef;
	error = sSPPlugins->GetNamedPlugin(pluginName, &pluginRef);

	if (!error)
	{
		AIScriptMessage msg;
		msg.inParam = inputString;

		error = sSPInterface->SetupMessageData(pluginRef, &msg.d);
		if (!error)
		{
			error = sSPInterface->SendMessage(pluginRef, kCallerAIScriptMessage, selector, &msg, &spResult);
			if (spResult)
				error = spResult;

			sSPInterface->EmptyMessageData(pluginRef, &msg.d);

			if(!error)
				outString = msg.outParam;
		}
	}

	return error;
}
*/
#include "AIHeaderEnd.h"


#endif // __AIScriptMessage__
