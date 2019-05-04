//========================================================================================
//  
//  $File: //ai/ai16/devtech/sdk/public/samplecode/common/source/HtmlUIController.cpp $
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

#include "IllustratorSDK.h"
#include "HtmlUIController.h"

HtmlUIController::HtmlUIController(const char* extensionId)
: htmlExtensionId(extensionId)
{
	htmlPPLib.Load(sAIFolders);
}

HtmlUIController::~HtmlUIController(void)
{
	htmlPPLib.Unload();
}

PlugPlugErrorCode HtmlUIController::LoadExtension()
{
	return htmlPPLib.LoadExtension(htmlExtensionId);
}

PlugPlugErrorCode HtmlUIController::UnloadExtension()
{
	return htmlPPLib.UnloadExtension(htmlExtensionId);
}
