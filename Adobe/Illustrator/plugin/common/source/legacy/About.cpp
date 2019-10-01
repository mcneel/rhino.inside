//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/legacy/About.cpp $
//
//  $Revision: #1 $
//
//  Copyright 1997 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

/**
	This file provides two simple dialog interfaces used by the plug-in shell.  
	One does a simple about message.  The other displays an error dialog based
	on a string list in the file shellSupport.rsrc.
	
 **/

/**-----------------------------------------------------------------------------
 **
 **	Headers
 **
 **/
#include "IllustratorSDK.h"

#include "common.h"

#include "about.h"
#include "plugin.h"			// for dialog constants
#include "reportError.h"
#include "stringUtils.h"


/**-----------------------------------------------------------------------------
 **
 **	Private Functions
 **
 **/

ASErr ASAPI	AboutPluginInitProc(ADMDialogRef dialog);
void ASAPI 	AboutDlgOKButtonProc(ADMItemRef item, ADMNotifierRef notifier);


/*******************************************************************************
 **
 **	UI Functions
 **
 **/


AIErr goAbout( SPInterfaceMessage *message )
{
	AIErr error;


	// Initialize the dialog
	error = sADMDialog->Modal(message->d.self, "About Dialog", kAboutDLOG, kADMModalDialogStyle, 
						AboutPluginInitProc, NULL, 0);
	if (error) goto errorTag;

	return kNoErr;

errorTag:
	return error;

}





/*******************************************************************************
 **
 **	About Private Functions
 **
 **/


ASErr ASAPI  AboutPluginInitProc(ADMDialogRef dialog)
{
	// Call the default Init first to create the modal dialog and items.
	// By default OK is assumed to be item 1
	sADMItem->SetNotifyProc(sADMDialog->GetItem(dialog, kDlgOKButton), AboutDlgOKButtonProc);

	return kNoErr;
}

void ASAPI AboutDlgOKButtonProc(ADMItemRef item, ADMNotifierRef notifier)
{
	// This is here more by way of example, since there really isn't any
	// other reason to be overriding this handler.  The SetNotifyProc( ) call
	// above could be removed entirely.
	// Call the default Notify so the dialog knows the OK button was hit.
	sADMItem->DefaultNotify(item, notifier);
}


