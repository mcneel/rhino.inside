//========================================================================================
//  
//  $File: //ai/mainline/devtech/sandbox/lomorgan/public/samplecode/Tutorial/Source/TutorialFilterParameters.h $
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

#ifndef __TUTORIALFILTERPARAMETERS_H__
#define __TUTORIALFILTERPARAMETERS_H__

#include "IllustratorSDK.h"

typedef struct
{
	ai::int32 corners;	// number of corners on the polygon
	ai::int32 size;		// the maximum size, in points
	// or any other values your filter needs...
}
TutorialFilterParameters;

static const TutorialFilterParameters kDefaultFilterParameters	= {7, 72};
static const TutorialFilterParameters kMinFilterParameters		= {1, 72};
static const TutorialFilterParameters kMaxFilterParameters		= {100, 7200};

#endif
