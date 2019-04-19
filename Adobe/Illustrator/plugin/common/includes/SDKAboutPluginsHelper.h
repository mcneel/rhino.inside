//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/SDKAboutPluginsHelper.h $
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

#ifndef __SDKAboutPluginsHelper_H__
#define __SDKAboutPluginsHelper_H__

/** Helps plug-ins that want to display company contact information and copyright in
	an about box. Each third party company creates an about plug-ins menu group under 
	Illustrator's about group (see kAboutMenuGroup). A separate menu item is added 
	under the company's about plug-ins menu group:
	<pre>
		About MyCompany Plug-ins	>	MyPlugin1Name...
									>	MyPlugin2Name...
	</pre>

	For example, SDK sample plug-ins add the "About SDK Plug-ins" menu group. On the
	Macintosh the group is displayed under the Illustrator menu:
	<pre>
		Illustrator	>	About SDK Plug-ins	>	TextTest...
											>	Tutorial...
	</pre>

	On Windows the group is displayed under the Help menu:
	<pre>
		Help	>	About SDK Plug-ins	>	TextTest...
										>	Tutorial...
	</pre>

	When a menu item is used the plug-in receives a menu message and displays
	plug-in specific information containing contact details and copyright.

	To reduce coupling with plug-ins that want to use this helper
	the suites it requires are acquired and released locally by this
	class. That way there's no stuff for client code to set up before
	using the helper.

	@see kAboutMenuGroup
	@see AIMenuSuite, ADMBasicSuite10
*/
class SDKAboutPluginsHelper {
public:

	/**	Constructor - no special initialization in here.
	*/
	SDKAboutPluginsHelper();

	/**	Destructor - no special termination in here.
	*/
	virtual ~SDKAboutPluginsHelper();

	/** Adds a menu group for the given company under Illustrator's about group
		(if the group does not already exist) and adds a menu item for the given plug-in.
		@param message IN startup message.
		@param companyMenuGroupName IN identifier for your company's about plug-ins menu group.
		@param companyName IN name of your company's about plug-ins menu group for display.
		@param pluginName IN name of your plug-in for display.
		@param menuItemHandle OUT passed in the call back when the menu item is used.
		@return kNoErr on success, other AIErr otherwise.
	*/
	AIErr AddAboutPluginsMenuItem(SPInterfaceMessage* message, 
										 const char* companyMenuGroupName, 
										 const ai::UnicodeString& companyName, 
										 const char* pluginName, 
										 AIMenuItemHandle* menuItemHandle);

	/** Pops about box for the plug-in.
		@see ADMBasicSuite10::MessageAlert
		@param message menu message (kCallerAIMenu / kSelectorAIGoMenuItem) the plug-in is responding to.
		@param title window title for the about box.
		@param description information about the plug-in.
	*/
	void PopAboutBox(AIMenuMessage* message, const char* title, const char* description);

private:
	/** Checks whether the given group name already exists.
		@param targetGroupName IN group name to check.
		@param groupAlreadyMade OUT true if group exists, false otherwise.
		@return kNoErr on success, other AIErr otherwise.
	*/
	AIErr GroupExists(const char* targetGroupName, bool& groupAlreadyMade);

private:
	/** Menu suite.
	*/
	AIMenuSuite*			fAIMenu;

	/** UIUtils suite.
	*/
	AIUserSuite* fAIUser;
};

#endif // __SDKAboutPluginsHelper_H__
