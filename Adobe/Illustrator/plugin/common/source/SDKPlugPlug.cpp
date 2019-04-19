//========================================================================================
//  
//  $File: //ai/ai15/devtech/sdk/public/samplecode/common/source/SDKPlugPlug.cpp $
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

#include "SDKPlugPlug.h"
#include "IAIUnicodeString.h"


SDKPlugPlug::SDKPlugPlug() :
	fhModule				(NULL),
	pFnLoadExtension		(NULL),
	pFnUnloadExtension		(NULL),
	pFnAddEventListener		(NULL),
	pFnRemoveEventListener	(NULL),
	pFnDispatchEvent		(NULL)
{
}


SDKPlugPlug::~SDKPlugPlug()
{
}


AIErr SDKPlugPlug::Load(AIFoldersSuite* sAIFolders)
{
	AIErr err = kNoErr;

	do {
		
#ifdef WIN_ENV
		AIFolderType folderType = kAIApplicationFolderType;
		ai::UnicodeString libName("PlugPlugOwl.dll");
#else
		AIFolderType folderType = kAIContentsFolderType;
		ai::UnicodeString libName("/Frameworks/PlugPlugOwl.framework");
#endif

		ai::FilePath path;
		err = sAIFolders->FindFolder(folderType, false, path);	
		if(err) { break; }

		path.AddComponent(libName);
		if(!path.Exists(false)) { err = kCantHappenErr; break; }

#ifdef WIN_ENV
		fhModule =  LoadLibraryW(path.GetFullPath().as_WCHARStr().as_LPCWSTR());
		if(!fhModule) { err = kCantHappenErr; break; }

		pFnLoadExtension = (PlugPlugLoadExtensionFn) GetProcAddress(fhModule, "PlugPlugLoadExtension");
		if(!pFnLoadExtension) { err = kCantHappenErr; break; }

		pFnUnloadExtension = (PlugPlugUnloadExtensionFn) GetProcAddress(fhModule, "PlugPlugUnloadExtension");
		if(!pFnUnloadExtension) { err = kCantHappenErr; break; }

		pFnAddEventListener = (PlugPlugAddEventListenerFn) GetProcAddress(fhModule, "PlugPlugAddEventListener");
		if(!pFnAddEventListener) { err = kCantHappenErr; break; }

		pFnRemoveEventListener = (PlugPlugRemoveEventListenerFn) GetProcAddress(fhModule, "PlugPlugRemoveEventListener");
		if(!pFnRemoveEventListener) { err = kCantHappenErr; break; }

		pFnDispatchEvent = (PlugPlugDispatchEventFn) GetProcAddress(fhModule, "PlugPlugDispatchEvent");
		if(!pFnDispatchEvent) { err = kCantHappenErr; break; }
#else
		fhModule = CFBundleCreate( kCFAllocatorDefault, path.GetAsCFURL());
		if(!fhModule)  { err = kCantHappenErr; break; }

		CFStringRef entryName = CFSTR("PlugPlugLoadExtension");
		pFnLoadExtension = (PlugPlugLoadExtensionFn) CFBundleGetFunctionPointerForName(fhModule, entryName);
		if(!pFnLoadExtension) { err = kCantHappenErr; break; }

		entryName = CFSTR("PlugPlugUnloadExtension");
		pFnUnloadExtension = (PlugPlugUnloadExtensionFn) CFBundleGetFunctionPointerForName(fhModule, entryName);
		if(!pFnUnloadExtension) { err = kCantHappenErr; break; }

		entryName = CFSTR("PlugPlugAddEventListener");
		pFnAddEventListener = (PlugPlugAddEventListenerFn) CFBundleGetFunctionPointerForName(fhModule, entryName);
		if(!pFnAddEventListener) { err = kCantHappenErr; break; }

		entryName = CFSTR("PlugPlugRemoveEventListener");
		pFnRemoveEventListener = (PlugPlugRemoveEventListenerFn) CFBundleGetFunctionPointerForName(fhModule, entryName);
		if(!pFnRemoveEventListener) { err = kCantHappenErr; break; }

		entryName = CFSTR("PlugPlugDispatchEvent");
		pFnDispatchEvent = (PlugPlugDispatchEventFn) CFBundleGetFunctionPointerForName(fhModule, entryName);
		if(!pFnDispatchEvent)  { err = kCantHappenErr; break; }
#endif

	}
	while (false);

	return err;
}


AIErr SDKPlugPlug::Unload()
{
	AIErr err = kNoErr;

	if (fhModule)
	{
#ifdef WIN_ENV
		if (!FreeLibrary(fhModule))
			err = kCantHappenErr;	
#else
		CFRelease(fhModule);	
#endif
		fhModule = NULL;
	}

	return err;
}

PlugPlugErrorCode SDKPlugPlug::LoadExtension(const char* inExtensionID)
{
	PlugPlugErrorCode err = PlugPlugErrorCode_success;

	if(pFnLoadExtension)
		err = (*pFnLoadExtension)(inExtensionID);

	return err;
}


PlugPlugErrorCode SDKPlugPlug::UnloadExtension(const char* inExtensionID)
{
	PlugPlugErrorCode err = PlugPlugErrorCode_success;

	if(pFnUnloadExtension)
		err = (*pFnUnloadExtension)(inExtensionID);

	return err;
}


csxs::event::EventErrorCode
SDKPlugPlug::AddEventListener(const char* type, 
							 const csxs::event::EventListenerFn eventListener, 
							 void* const context)
{
	csxs::event::EventErrorCode err = csxs::event::kEventErrorCode_OperationFailed;

	if(pFnAddEventListener)
		err = (*pFnAddEventListener)(type, eventListener, context);

	return err;
}

csxs::event::EventErrorCode
SDKPlugPlug::RemoveEventListener(const char* type, 
								const csxs::event::EventListenerFn eventListener, 
								void* const context)
{
	csxs::event::EventErrorCode err = csxs::event::kEventErrorCode_OperationFailed;
	if(isPlugPlugLoaded())
	{
		if(pFnRemoveEventListener)
			err = (*pFnRemoveEventListener)(type, eventListener, context);
	}
	return err;
}


csxs::event::EventErrorCode
SDKPlugPlug::DispatchEvent(const csxs::event::Event* const event)
{
	csxs::event::EventErrorCode err = csxs::event::kEventErrorCode_OperationFailed;

	if(pFnRemoveEventListener)
		err = (*pFnDispatchEvent)(event);

	return err;
}


bool SDKPlugPlug::isPlugPlugLoaded()
{
#ifdef WIN_ENV
	return true;
#else
	return CFBundleIsExecutableLoaded(fhModule);
#endif	
}
