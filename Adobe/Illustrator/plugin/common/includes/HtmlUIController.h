//========================================================================================
//  
//  $File: //ai/ai16/devtech/sdk/public/samplecode/common/includes/HtmlUIController.h $
//
//  $Revision: #1 $
//
//  Copyright 2011 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __HTMLUICONTROLLER_H__
#define __HTMLUICONTROLLER_H__

#include "SDKPlugPlug.h"
#include "IllustratorSDK.h"
#include "Suites.hpp"

class HtmlUIController
{
public:

	HtmlUIController(const char* extensionId);

	virtual ~HtmlUIController(void);

	virtual PlugPlugErrorCode LoadExtension();

	virtual PlugPlugErrorCode UnloadExtension();

	/** Registers the events this plug-in will listen for with PlugPlug.
		@return error code if error found, or success otherwise.
	*/
	virtual csxs::event::EventErrorCode RegisterCSXSEventListeners() = 0;

	/** Removes the previously added event listeners from PlugPlug.
		@return error code if error found, or success otherwise.
	*/
	virtual csxs::event::EventErrorCode RemoveEventListeners() = 0;
	
	virtual ASErr SendData() = 0;
	
	virtual void ParseData(const char* eventData) = 0;

protected:
	
	SDKPlugPlug htmlPPLib;

private:

	const char* htmlExtensionId;
};

#endif
