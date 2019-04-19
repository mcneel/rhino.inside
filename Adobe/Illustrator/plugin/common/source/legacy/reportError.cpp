//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/legacy/reportError.cpp $
//
//  $Revision: #1 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
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

#include "reportError.h"
#include "plugin.h"			// for dialog constants
#include "stringUtils.h"

/**-----------------------------------------------------------------------------
 **
 **	Types
 **
 **/

// strings for error dialog
typedef struct {
	unsigned char	err_msg[256];
	unsigned char 	error_text[16];
} ErrorStrings;



/**-----------------------------------------------------------------------------
 **
 **	Private Functions
 **
 **/

static AIErr 		PString2AIErr(unsigned char* err_code);
static void			AIErr2PString(AIErr err_code, unsigned char* err_string);

static AIErr errorMessage( SPInterfaceMessage *message,  ErrorStrings *errors  );

ASErr ASAPI	ErrorDialogInitProc(ADMDialogRef dialog);
void ASAPI 	ErrorDialogOKButtonProc(ADMItemRef item, ADMNotifierRef notifier);

/*******************************************************************************
 **
 **	UI Functions
 **
 **/


void report_error( SPInterfaceMessage *message, AIErr error_to_report )
{
	ASBoolean			bFound = FALSE;
	short			nIndex;
	int			    hi;
	long			number;
	AIErr			error = kNoErr;
	unsigned char 	ch;
	char			err_code[255];
	ErrorStrings	errors;

	if ( error_to_report == kNoErr || error_to_report == kCanceledErr ) 
		return;

	if (NULL == sADMBasic || NULL == sADMDialog)
		goto errorTag;				
		
	//	
	// Loop through the system error strings until we find a matching error code
	// The next string is the err msg we want to use.
	// The Last string is "". The 2nd last is the default string to use is no match found
	//
	nIndex = 1;
	do {
		sADMBasic->GetIndexString( message->d.self, kErrorStrings, nIndex, err_code, 255 );

		if (!err_code[0]) // first null string means no more errors
			break;

		// NOTE: resultString is CString;
  		ch = err_code[0];
		if ( ch == '-' || (ch >= '0' && ch <= '9') ) 
			CStringToAIErr( (char *)err_code, &number);
		else {  // non numeric 4 byte err code.  (e.g.) '!sel'.
			SUctopstr( (char*)err_code );
			number = PString2AIErr((unsigned char*)err_code);
			}

		if ( number == error_to_report ) {
			bFound = TRUE;
			break;
			}
		else
			nIndex+=2;
	} while ( !err_code[0] || !bFound ); // last string is length 0
	

	if(bFound)		// Found the matching error code, get the err_msg
		error = sADMBasic->GetIndexString( message->d.self, kErrorStrings, (short)(nIndex+1), (char*)errors.err_msg, sizeof(errors.err_msg) );
	else			// No match. Use the 2nd last error msg as default
		error = sADMBasic->GetIndexString( message->d.self, kErrorStrings, (short)(nIndex-1), (char*)errors.err_msg, sizeof(errors.err_msg) );
	if ( error )
		goto errorTag;


	hi = (short)(error_to_report >> 16);
	if ( hi == 0xFFFF || hi == 0x0000 ) 
		AIErrToCString( error_to_report, (char*)errors.error_text );
	else {
		AIErr2PString(error_to_report, errors.error_text);
		SUptocstr( errors.error_text );
	}

	errorMessage( message, &errors );

	return;

errorTag:

	return;
}








/*******************************************************************************
 **
 **	Error Private Functions
 **
 **/
static AIErr errorMessage( SPInterfaceMessage *message,  ErrorStrings *errors  )
{
	AIErr error = kNoErr;

	// Initialize the dialog
	if (!sADMDialog)
		goto errorTag;
	sADMDialog->Modal(message->d.self, "Error Dialog", kErrorDialogID, kADMModalDialogStyle, 
						ErrorDialogInitProc, (void*)errors, 0);
	
	return kNoErr;

errorTag:
	return error;

}


ASErr ASAPI  ErrorDialogInitProc(ADMDialogRef dialog)
{
	ASErr error = kNoErr;
	ErrorStrings *errors;
	ADMItemRef textItem;
	
	sADMItem->SetNotifyProc(sADMDialog->GetItem(dialog, kDlgOKButton), ErrorDialogOKButtonProc);

	// now set upt the error strings
	errors = (ErrorStrings*)sADMDialog->GetUserData(dialog);

	textItem = sADMDialog->GetItem(dialog, kErrorMessageText);
	sADMItem->SetText( textItem, (char*)errors->err_msg);

	textItem = sADMDialog->GetItem(dialog, kErrorCodeText);
	sADMItem->SetText( textItem, (char*)errors->error_text);
	
	return error;
}

void ASAPI ErrorDialogOKButtonProc(ADMItemRef item, ADMNotifierRef notifier)
{
	// This is here more by way of example, since there really isn't any
	// other reason to be overriding this handler.  The SetNotifyProc( ) call
	// above could be removed entirely.
	// Call the default Notify so the dialog knows the OK button was hit.
	sADMItem->DefaultNotify(item, notifier);
}




/*******************************************************************************
 **
 **	Useful String Functions
 **
 **/
 
void AIErrToCString( AIErr error_to_report, char *errorText ) {
	error_to_report = (AIErr) _ShortToAIReal( error_to_report );
	sAIUser->AIRealToString ( (float) error_to_report, 0, (unsigned char *)errorText );
	SUptocstr( (unsigned char*)errorText );
	return;
}


void CStringToAIErr( char *errorText, AIErr *error_to_report ) {
	AIReal tempErr;

	SUctopstr( (char *)errorText );
	sAIUser->StringToAIReal( (unsigned char *)errorText, &tempErr );
	*error_to_report = _AIRealTruncToShort( tempErr );

	return;
}

static AIErr PString2AIErr(unsigned char* err_string)
{  // non numeric 4 byte err code.  (e.g.) '!sel'.
	AIErr	err_code;
	char 	*tmpPtr = (char *)&err_code;
	int		j;

	// err_code = *(long *)(err_string + 1);  	// NOTE: can't do this on intel machine. 
												// The hi-low byte problem.

//	for( j = 4; j >0 ; j--, tmpPtr++)
	for( j = 1; j < 5; j++, tmpPtr++)
		*tmpPtr = err_string[j];

	return err_code;
}

static void AIErr2PString(AIErr err_code, unsigned char* err_string)
{
	char 	*tmpPtr = (char *)&err_code;
	int		j;
	
	err_string[0] = 4;

//	for( j = 4; j >0 ; j--, tmpPtr++)
	for( j = 1; j < 5; j++, tmpPtr++)
		err_string[j] = *tmpPtr;
}
