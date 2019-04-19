#ifndef __AIToolbox__
#define __AIToolbox__

/*
 *        Name:	AIToolbox.h
 *   $Revision: 14 $
 *      Author:	Paul Asente
 *        Date:	3/19/96
 *     Purpose:	Adobe Illustrator Toolbox Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file
 * in accordance with the terms of the Adobe license agreement
 * accompanying it. If you have received this file from a source other
 * than Adobe, then your use, modification, or distribution of it
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/


#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AITool__
#include "AITool.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIToolbox.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIToolboxSuite			"AI Toolbox Suite"
#define kAIToolboxVersion7		AIAPI_VERSION(7)
#define kAIToolboxVersion		kAIToolboxVersion7
#define kAIToolboxSuiteVersion	kAIToolboxVersion

/** @ingroup Callers
	The toolbox caller. See \c #AIToolboxSuite. */
#define kCallerAIToolbox				"AI Toolbox"

/** @ingroup Selectors
	Sent to signal the start of a series of calls
	describing tools to be added. Always followed immediately by
	\c #kSelectorAIStartToolGroup. The only valid information in
	the message is the toolbox. */
#define kSelectorAIStartToolbox			"AI Toolbox Start Toolbox"
/** @ingroup Selectors
	Sent to signal the end of a series of calls describing
	tools to be added. The only valid information in the
	message is the toolbox. */
#define kSelectorAIEndToolbox			"AI Toolbox End Toolbox"
/** @ingroup Selectors
 	Sent to signal the start of a tool group. (See @ref Toolsets)
	Typically many of these are sent. Always followed immediately
	by \c #kSelectorAIStartToolSet. The only valid information in the
	message is the toolbox.*/
#define kSelectorAIStartToolGroup		"AI Toolbox Start Tool Group"
/** @ingroup Selectors
	Sent to signal the end of a tool group. Always followed immediately
	by a new \c #kSelectorAIStartToolGroup or \c #kSelectorAIEndToolbox.
	The only valid information in the message is the toolbox. */
#define kSelectorAIEndToolGroup			"AI Toolbox End Tool Group"
/** @ingroup Selectors
	Sent to signal the start of a tool set. (See @ref Toolsets)
	Typically many of these are sent. Always followed immediately
	by \c #kSelectorAIAddTool. The only valid information in the
	message is the toolbox.  */
#define kSelectorAIStartToolSet			"AI Toolbox Start Tool Set"
/** @ingroup Selectors
	Sent to signal the end of a tool set. Always followed immediately
	by a new \c #kSelectorAIStartToolSet or \c #kSelectorAIEndToolGroup.
	The only valid information in the message is the toolbox.  */
#define kSelectorAIEndToolSet			"AI Toolbox End Tool Set"
/** @ingroup Selectors
	Sent to signal the addition of a tool. Always followed immediately
	by another \c #kSelectorAIAddTool or \c #kSelectorAIEndToolSet.
	The message is completely filled out.  */
#define kSelectorAIAddTool				"AI Toolbox Add Tool"
/** @ingroup Selectors
	Sent to add a rollover icon of a tool. Can be sent
	any time after the tool has been added. The toolbox, tool, and
	icon fields are valid in the message.  */
#define kSelectorAIAddRollover			"AI Toolbox Add Rollover"

/** @ingroup Selectors
	Sent to signal that a tool has been selected. The
	toolbox and tool fields are valid in the message.  */
#define kSelectorAIToolSelected			"AI Toolbox Tool Selected"
/** @ingroup Selectors
	Sent to signal that a tool's alternate action has been invoked.
	Typically brings up a tool options dialog.	The
	toolbox and tool fields are valid in the message.	*/
#define kSelectorAIAlternateToolActionSelected "AI Toolbox Alternate Tool Action Selected"
/** @ingroup Selectors
	Sent to signal a tool cycle. The toolbox and tool fields are valid in the message.
	If the currently selected tool is not in the message tool's tool set,
	make the message tool the current tool.  If the currently selected tool
	is in the message tool's tool set, switch to the next tool in the tool set. */
#define kSelectorAICycleTool			"AI Toolbox Cycle Tool"
/** @ingroup Selectors
	Sent to signal a tool soft cycle. The toolbox and tool fields are valid in the message.
	If the currently selected tool is not in the message tool's tool set,
	make the message tool the  current tool.
	If the currently selected tool is in the message tool's tool set, do nothing.
	See \c #AIToolboxSuite::SetTool().*/
#define kSelectorAISoftCycleTool		"AI Toolbox Soft Cycle Tool"

/** 
	Tool icon Types to be given by clients.
*/

/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a toolbox, never dereferenced. Access with the \c #AIToolboxSuite. */
typedef struct _t_AIToolboxOpaque *AIToolboxHandle;

/** \c #AIBuiltInToolBox constants.
 */
enum AIBuiltInToolBox : ai::int16
{
    /* Basic Toolbox. */
    kAIBasicToolbox               =        0,
    /* Advanced Toolbox. */
    kAIAdvancedToolbox            =        1,
};


/** The contents of a toolbox message. Valid fields depend on the
	selector type. */
struct AIToolboxMessage{
	/** The message data. */
	SPMessageData d = {};
	/** The toolbox reference. */
	AIToolboxHandle toolbox = {};
	/** The tool reference. */
	AIToolType tool = 0;
	/** The icon shown in the Tools palette.  */
	AIDataStackRef iconResourceDictionary;
	/** Unique identifying name for the tool */
	char *name = nullptr;
	/** Localized display name for the tool. */
	char *title = nullptr;
	/** Short descriptive string shown when tool is activated. */
	char *tooltip = nullptr;
	/** The Help system identifier. */
	ASHelpID helpID = 0;
	/* Specifies the type of the incoming icons 
		enum IconType in AITypes.h*/
	ai::IconType iconType = ai::IconType::kInvalid;
    /**This is for internal purpose only to hold plugin's priority for group.**/
    AIToolType      sameGroupAs =0 ;
    /**This is for internal purpose only to hold plugin's priority for set.**/
    AIToolType      sameSetAs = 0;
    /**This is for internal purpose only to hold a plugin is third party plugin or not.**/
    bool            isThirdPartyPlugin = false;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite allows you to create additional tool palettes,
	of which there can be any number. Some of the selectors are also
	useful for other plug-ins that want to know when the current tool changes.

	At startup time, after all the tools have been added, the application sends a set
	of messages that describe the current tools. The messages are also sent if
	tools are added later, although this is unusual.

	The caller is \c #kCallerAIToolbox. These selectors are sent:
	<br> \c #kSelectorAIStartToolbox
	<br> \c #kSelectorAIEndToolbox
	<br> \c #kSelectorAIStartToolGroup
	<br> \c #kSelectorAIEndToolGroup
	<br> \c #kSelectorAIStartToolSet
	<br> \c #kSelectorAIEndToolSet
	<br> \c #kSelectorAIAddTool
	<br> \c #kSelectorAIAddRollover

	These messages are sent during the execution of the program to notify
	other toolboxes of actions taken by a toolbox:
	<br> \c #kSelectorAIToolSelected
	<br> \c #kSelectorAIAlternateToolActionSelected
	<br> \c #kSelectorAICycleTool
	<br> \c #kSelectorAISoftCycleTool

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIToolboxSuite and \c #kAIToolboxVersion.
*/

struct AIToolboxSuite {
	/** Registers a plug-in to receive toolbox selector messages and to use the
		other suite methods.
			@param self This plug-in.
			@param name The unique identifying name of this plug-in.
			@param toolbox [out] A buffer in which to return the toolbox reference. If you
				install multiple toolboxes, save to compare to the toolbox reference in
				message data.
		*/
	AIAPI AIErr (*AddToolbox) (SPPluginRef self, const char *name,
							   AIToolboxHandle *toolbox);

	/** Makes a tool current for a toolbox.
			@param toolbox The toolbox reference. Use NULL to set the tool in the built-in toolbox.
			@param tool The tool reference.
		*/
	AIAPI AIErr (*SetTool) (AIToolboxHandle toolbox, AIToolType tool);

	/** Performs the alternate action for a tool, typically to show an options dialog.
		Does not change the current tool.
			@param toolbox The toolbox reference.
			@param tool The tool reference.
		*/
	AIAPI AIErr (*AlternateAction) (AIToolboxHandle toolbox, AIToolType tool );

	/** Sends the \c #kSelectorAICycleTool message.
			@param toolbox The toolbox reference.
			@param tool The tool reference.
		*/
	AIAPI AIErr (*CycleTool) (AIToolboxHandle toolbox, AIToolType tool);

	/** Gets the number of registered toolboxes. Use with \c #GetNthToolbox()
		to iterate through plug-in toolboxes.
			@param count [out] A buffer in which to return the number of toolboxes.
		*/
	AIAPI AIErr (*CountToolboxes) (ai::int32 *count);

	/** Retrieves a toolbox by index position. Use with \c #CountToolboxes()
		to iterate through plug-in toolboxes.
			@param n The 0-based position index.
			@param tool	[out] A buffer in which to return the toolbox reference.
		*/
	AIAPI AIErr (*GetNthToolbox) (ai::int32 n, AIToolboxHandle *toolbox);

	/** Retrieves the currently selected tool type. The plug-in does not need
		to register as a toolbox plug-in to use this.
			toolNum [out] A buffer in which to return the tool number.
				See @ref Toolsets
		 */
	AIAPI AIErr (*GetCurrentToolType) (AIToolType *toolNum);

    /** Retrieves the visibility for a built-in toolbox.
     toolBox [in] A built-in toolbox taking \c #AIBuiltInToolBox value.
     visible [out] The visibility of the toolbox
     
     */
    AIAPI AIErr (*GetBuiltInToolboxVisibility) (ai::int16 toolBox, AIBoolean& visible);
    
};


#include "AIHeaderEnd.h"


#endif

