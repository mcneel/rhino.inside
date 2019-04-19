//========================================================================================
//  
//  $File: //ai/ai16/devtech/sdk/public/samplecode/common/source/FlashUIController.cpp $
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
#include "FlashUIController.h"

FlashUIController::FlashUIController(const char* extensionId)
: fExtensionId(extensionId)
{
	fPPLib.Load(sAIFolders);
}

FlashUIController::~FlashUIController(void)
{
	fPPLib.Unload();
}

PlugPlugErrorCode FlashUIController::LoadExtension()
{
	return fPPLib.LoadExtension(fExtensionId);
}

PlugPlugErrorCode FlashUIController::UnloadExtension()
{
	return fPPLib.UnloadExtension(fExtensionId);
}
