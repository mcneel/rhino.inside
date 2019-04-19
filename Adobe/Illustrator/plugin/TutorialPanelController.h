//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/Tutorial/Source/TutorialPanelController.h $
//
//  $Revision: #1 $
//
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __TUTORIALPANELCONTROLLER_H__
#define __TUTORIALPANELCONTROLLER_H__

#include "IllustratorSDK.h"
#include "FlashUIController.h"
#include "TutorialFilterParameters.h"
#include "TutorialPlugin.h"

extern TutorialPlugin *gPlugin;

class TutorialPanelController : public FlashUIController
{

public:

	TutorialPanelController();

	csxs::event::EventErrorCode RegisterCSXSEventListeners();

	csxs::event::EventErrorCode RemoveEventListeners();

	ASErr SendData();

	void ParseData(const char* eventData);
	
	void CloseDownPanel();
	
	void ApplyFilter();

private:
	AIBoolean fCancelled;				// Was the dialog cancelled?

	TutorialFilterParameters fParams;	// Parameters entered
};

#endif
