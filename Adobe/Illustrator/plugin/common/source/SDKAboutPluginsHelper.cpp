//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/SDKAboutPluginsHelper.cpp $
//
//  $Revision: #2 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

/*
*/
SDKAboutPluginsHelper::SDKAboutPluginsHelper() : fAIMenu(nullptr), fAIUser(nullptr)
{
}

/*
*/
SDKAboutPluginsHelper::~SDKAboutPluginsHelper()
{
}

/*
*/
AIErr SDKAboutPluginsHelper::AddAboutPluginsMenuItem(SPInterfaceMessage* message, 
													 const char* companyMenuGroupName, 
													 const ai::UnicodeString& companyName, 
													 const char* pluginName, 
													 AIMenuItemHandle* menuItemHandle)
{
	AIErr error = kNoErr;

	if (fAIMenu == nullptr) {
		error = message->d.basic->AcquireSuite( kAIMenuSuite, kAIMenuSuiteVersion, (const void **) &fAIMenu );
	}
	
	if (!error && fAIMenu != nullptr) {
		// Add an about plug-ins menu group for the given company under Illustrator's about group.
		bool exists = false;
		error = this->GroupExists(companyMenuGroupName, exists);
		if (!error && !exists) {
			AIPlatformAddMenuItemDataUS companyRootMenuData;
			companyRootMenuData.groupName = kAboutMenuGroup;
			companyRootMenuData.itemText = companyName;	
			AIMenuItemHandle companyRootMenuItemHandle = nullptr;
			error = fAIMenu->AddMenuItem(message->d.self, NULL, &companyRootMenuData, kMenuItemNoOptions, &companyRootMenuItemHandle);
			if (!error) {
				AIMenuGroup companyRootMenuGroup = nullptr;
				error = fAIMenu->AddMenuGroupAsSubMenu(companyMenuGroupName, kMenuGroupSortedAlphabeticallyOption, companyRootMenuItemHandle, &companyRootMenuGroup);
			}
		}
	}
	
	if (!error && fAIMenu != nullptr) {
		// Add menu item for this plug-in under the company's about plug-ins menu group.
		AIPlatformAddMenuItemDataUS aboutPluginMenuData;
		aboutPluginMenuData.groupName = companyMenuGroupName;
		aboutPluginMenuData.itemText = ai::UnicodeString(pluginName);
		AIMenuItemHandle aboutPluginMenuItemHandle = nullptr;
		error = fAIMenu->AddMenuItem(message->d.self, NULL, &aboutPluginMenuData, kMenuItemNoOptions, &aboutPluginMenuItemHandle);
		if (!error) {
			*menuItemHandle = aboutPluginMenuItemHandle;
		}
	}

	if (fAIMenu != nullptr) {
		message->d.basic->ReleaseSuite( kAIMenuSuite, kAIMenuSuiteVersion );
		fAIMenu = nullptr;
	}

	return error;
}

/*
*/
void SDKAboutPluginsHelper::PopAboutBox(AIMenuMessage* message, const char* title, const char* description)
{
	AIErr error = kNoErr;
	if (fAIUser == nullptr) {
		error = message->d.basic->AcquireSuite(kAIUserSuite, kAIUserSuiteVersion, (const void **) &fAIUser);
	}
	if (!error && fAIUser != nullptr) {
		// Pop an about box for this plug-in.
		ai::UnicodeString displayText(title);
		displayText.append(ai::UnicodeString("\n\n"));
		displayText.append(ai::UnicodeString(description));
		fAIUser->MessageAlert(displayText);
	}
	if (fAIUser != nullptr) {
		message->d.basic->ReleaseSuite(kAIUserSuite, kAIUserSuiteVersion);
		fAIUser = nullptr;
	}
}

/*
*/
AIErr SDKAboutPluginsHelper::GroupExists(const char* targetGroupName, bool& groupAlreadyMade)
{
	AIErr error = kNoErr;
	groupAlreadyMade = false;
	ai::int32 count = 0;
	AIMenuGroup dummyGroup = nullptr;
	error = fAIMenu->CountMenuGroups( &count );
	if ( error ) return error;
	for (ai::int32 i = 0; i < count; i++) {
		error = fAIMenu->GetNthMenuGroup( i, &dummyGroup );
		if ( error ) return error;
		const char* name;
		error = fAIMenu->GetMenuGroupName( dummyGroup, &name );
		if ( error ) return error;
		if ( std::strcmp(name, targetGroupName ) == 0 )
		{
			groupAlreadyMade = true;
			break;
		}
	}
	return error;
}

// End SDKAboutPluginsHelper.cpp
