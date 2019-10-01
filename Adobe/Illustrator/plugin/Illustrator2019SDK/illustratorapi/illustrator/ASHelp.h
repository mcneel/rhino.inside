#ifndef __ASHelp__
#define __ASHelp__

/*
 *        Name:	ASHelp.h
 *   $Revision: 15 $
 *      Author:	Rob Sargent
 *        Date:	2/15/97
 *     Purpose:	AS Help suite
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


/*
 * Includes
 */

#include "ASTypes.h"
#include "AITypes.h"
#include "SPFiles.h"
#include "SPPlugs.h"

#include "AIHeaderBegin.h"



/*******************************************************************************
 **
 ** Constants
 **
 **/
#define kASHelpSuite					"AS Help Suite"
#define kASHelpSuiteVersion1			1
#define kASHelpSuiteVersion				kASHelpSuiteVersion1
#define kASHelpVersion					kASHelpSuiteVersion1
#define kASHelpSuiteVersion4			4

#define kHelpInfoVersion		1


#define kHelpError				'!Hlp'


#define kHelpMenuType			'Menu'
#define kHelpDialogType			'Dlog'
#define kHelpToolType			'Tool'
#define kHelpPaletteMenuType	'PMnu'
#define kHelpEndType			0


#define kNoHelpID				0

#define kHelpFileStrIDProperty	'HlpS'
#define kHelpNativeStrIndex		1


/*******************************************************************************
 **
 ** Types
 **
 **/

// WARNING: The size of these types
//			must match the resources
typedef ai::uint32	ASHelpType;
typedef ai::int32		ASHelpKey;		// can be an integer or a pooled string pointer

typedef ai::int32		ASHelpID;


// WinHelp/QuickHelp Commands
typedef enum
{
	/* #if(WINVER >= 0x0400) */
	kASHelpCmd_CONTEXTMENU  = 0x000a,
	kASHelpCmd_FINDER       = 0x000b,
	kASHelpCmd_WM_HELP      = 0x000c,
	kASHelpCmd_SETPOPUP_POS = 0x000d,

	kASHelpCmd_TCARD        = 0x8000,
	kASHelpCmd_TCARD_DATA   = 0x0010,
	kASHelpCmd_TCARD_OTHER_CALLER = 0x0011,
	/* #endif  // WINVER >= 0x0400 */

	kASHelpCmd_CONTEXT		= 0x0001,	/* Display topic in ulTopic */
	kASHelpCmd_QUIT			= 0x0002,	/* Terminate help */
	kASHelpCmd_CONTENTS		= 0x0003,	/* NOTE: HELP_INDEX = HELP_CONTENTS in Windows.h */
	kASHelpCmd_HELPONHELP	= 0x0004,	/* Display help on using help */
	kASHelpCmd_SETCONTENTS  = 0x0005,	/* NOTE: HELP_SETINDEX = HELP_SETCONTENTS */
	kASHelpCmd_CONTEXTPOPUP = 0x0008,
	kASHelpCmd_FORCEFILE    = 0x0009,
	kASHelpCmd_KEY          = 0x0101,  /* Display topic for keyword in offabData */
	kASHelpCmd_COMMAND      = 0x0102,
	kASHelpCmd_PARTIALKEY   = 0x0105,
	kASHelpCmd_MULTIKEY     = 0x0201,
	kASHelpCmd_SETWINPOS    = 0x0203
} ASHelpCommand;


typedef struct ASHelpInitInfo
{
	ai::int32 version;
	AIWindowRef appWindow;
	SPPluginRef appPluginRef;
	ASInt16 helpFolderNameStrID;
	ASInt16 appHelpFileNameStrID;
	ASInt16 helpFolderNameStrIndex;
	ASInt16 appHelpFileNameStrIndex;
} ASHelpInitInfo;


typedef struct PIHelpFileDesc
{
	ai::int32 fVersion;
	ai::int32 fFileNameStrID;
} PIHelpFileDesc;


 /*******************************************************************************
 **
 ** Suite
 **
 **/

typedef struct t_ASHelpSuite1
{
	ASAPI ASErr (*Init) (ASHelpInitInfo *info);
	ASAPI ASErr (*Quit) (void);

	ASAPI ASErr (*SetContextHelpMode) (AIBoolean helpMode);
	ASAPI AIBoolean (*InContextHelpMode) (void);

	ASAPI ASErr (*Help) (AIWindowRef asWinRef, SPPlatformFileSpecification *spFile,
						 ASHelpCommand asHelpCommand, ai::uint32 dwData);
		// spFile == NULL uses the App's help file

	ASAPI ASErr (*HelpContents)	(SPPluginRef pluginRef);
	ASAPI ASErr (*SearchHelp)	(SPPluginRef pluginRef);
	ASAPI ASErr (*HowToUseHelp)	(SPPluginRef pluginRef);
	ASAPI ASErr (*ContextHelp)	(SPPluginRef pluginRef, ASHelpID helpID);
	
	ASAPI ASErr (*GetHelpID)	(SPPluginRef pluginRef, ASHelpType helpType,
								 ASHelpKey key1, ASHelpKey key2, ASHelpID *helpID);

	ASAPI ASErr (*TypedHelp)	(SPPluginRef pluginRef, ASHelpType helpType, ASHelpKey key1, ASHelpKey key2);

	ASAPI ASErr (*MenuHelp)		(SPPluginRef pluginRef, ASHelpKey commandID);

	ASAPI ASErr (*DialogHelp)	(SPPluginRef pluginRef, ASHelpKey dialogID, ASHelpKey itemID);
		// itemID == 0 means whole dialog

	ASAPI ASErr (*PaletteMenuHelp)	(SPPluginRef pluginRef, ASHelpKey dialogID, ASHelpKey menuItem );

	ASAPI ASErr (*ToolHelp)		(SPPluginRef pluginRef, ASHelpKey toolName );
		// toolName should be a pooled string pointer cast to ASHelpKey

} ASHelpSuite1;

typedef ASHelpSuite1 ASHelpSuite;  //For historical reasons.

typedef struct t_ASHelpSuite2
{
	ASAPI ASErr (*Init) (ASHelpInitInfo *info);
	ASAPI ASErr (*Quit) (void);

	ASAPI ASErr (*SetContextHelpMode) (AIBoolean helpMode);
	ASAPI AIBoolean (*InContextHelpMode) (void);

	ASAPI ASErr (*Help) (AIWindowRef asWinRef, SPPlatformFileSpecification *spFile,
						 ASHelpCommand asHelpCommand, ai::uint32 dwData);
		// spFile == NULL uses the App's help file

	ASAPI ASErr (*HelpContents)	(SPPluginRef pluginRef);
	ASAPI ASErr (*SearchHelp)	(SPPluginRef pluginRef);
	ASAPI ASErr (*HowToUseHelp)	(SPPluginRef pluginRef);
	ASAPI ASErr (*ContextHelp)	(SPPluginRef pluginRef, ASHelpID helpID);
	
	ASAPI ASErr (*GetHelpID)	(SPPluginRef pluginRef, ASHelpType helpType,
								 ASHelpKey key1, ASHelpKey key2, ASHelpID *helpID);

	ASAPI ASErr (*TypedHelp)	(SPPluginRef pluginRef, ASHelpType helpType, ASHelpKey key1, ASHelpKey key2);

	ASAPI ASErr (*MenuHelp)		(SPPluginRef pluginRef, ASHelpKey commandID);

	ASAPI ASErr (*DialogHelp)	(SPPluginRef pluginRef, ASHelpKey dialogID, ASHelpKey itemID);
		// itemID == 0 means whole dialog

	ASAPI ASErr (*PaletteMenuHelp)	(SPPluginRef pluginRef, ASHelpKey dialogID, ASHelpKey menuItem );

	ASAPI ASErr (*ToolHelp)		(SPPluginRef pluginRef, ASHelpKey toolName );
		// toolName should be a pooled string pointer cast to ASHelpKey

	ASAPI ASErr (*ContextHelpQRC) (SPPluginRef pluginRef, ASHelpID helpID);

} ASHelpSuite2;

#include "AIHeaderEnd.h"

#endif
