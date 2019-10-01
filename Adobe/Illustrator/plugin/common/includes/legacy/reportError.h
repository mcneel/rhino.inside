//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/legacy/reportError.h $
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

#include "SPInterf.h"


/**-----------------------------------------------------------------------------
 **
 **	Types
 **
 **/


#define kBadSelectionErr  '!sel'


/**-----------------------------------------------------------------------------
 **
 **	Functions
 **
 **/
//typedef	AIErr FXErr;

// string stuff
extern void AIErrToCString( AIErr error_to_report, char *errorText );
extern void CStringToAIErr( char *errorText, AIErr *error_to_report );

// ui stuff
extern void report_error( SPInterfaceMessage *message, AIErr error_to_report );
