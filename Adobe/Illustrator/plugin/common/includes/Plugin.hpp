//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/Plugin.hpp $
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

#ifndef __Plugin_hpp__
#define __Plugin_hpp__

#include <stdlib.h>

#include "AIActionManager.h"
#include "AIClipboard.h"
#include "AIFilter.h"
#include "AIFileFormat.h"
#include "AILiveEffect.h"
#include "AIMenu.h"
#include "AIMask.h"
#include "AINotifier.h"
#include "AIPluginGroup.h"
#include "AITool.h"
#include "AITimer.h"
#include "AIWorkspace.h"
#include "VTableSupport.hpp"

#include "Suites.hpp"

#define kMaxStringLength		256

#define kCppPluginStrID			16600

#define iAboutBoxPluginName		1
#define iAboutBoxAuthor			2

#define kUnhandledMsgErr	'!MSG'		// This isn't really an error

// Tell Xcode to export the following symbols
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

// Plug-in entry point
extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message);

// Tell Xcode to return to default visibility for symbols
#if defined(__GNUC__)
#pragma GCC visibility pop
#endif	

	
class Plugin
{
protected:
	SPPluginRef fPluginRef;
	char fPluginName[kMaxStringLength];
	Suites *fSuites;
	int fLockCount;
	SPAccessRef fPluginAccess;
	ASErr fLastError;
	long fErrorTimeout;
	ASBoolean fSupressDuplicateErrors;
	time_t fLastErrorTime;
		
public:
	Plugin(SPPluginRef pluginRef);
  Plugin() = default;
	virtual ~Plugin() = default;
	void *operator new(size_t size);
	void operator delete(void *pMem);
	
	ASBoolean SuitesAcquired() { return fSuites != nullptr; }
	virtual void ReportError(ASErr error, char *caller, char *selector, void *message);
	static void DefaultError(SPPluginRef ref, ASErr error);
	static ASBoolean FilterError(ASErr error);

	SPPluginRef GetPluginRef()			{ return fPluginRef; }

	virtual ASErr LockPlugin(ASBoolean lock);
	static ASBoolean IsReloadMsg(char *caller, char *selector);

	virtual ASErr StartupPlugin(SPInterfaceMessage *message); 
	virtual ASErr PostStartupPlugin(); 
	virtual ASErr ShutdownPlugin(SPInterfaceMessage *message); 
	virtual ASErr UnloadPlugin(SPInterfaceMessage *message);
	virtual ASErr ReloadPlugin(SPInterfaceMessage *message);
	virtual ASErr AcquireProperty(SPPropertiesMessage *message);
	virtual ASErr ReleaseProperty(SPPropertiesMessage *message);
	virtual void GetPluginName(char *name, unsigned int maxlen);

	virtual ASBoolean Purge();
	virtual ASErr Message(char *caller, char *selector, void *message);
	virtual ASErr SetGlobal(Plugin *plugin);

	virtual ASErr AllocateSuiteTables();
	virtual ASErr FillSuiteTables();
	virtual ASErr EmptySuiteTables();

	virtual ASErr AcquireOptionalSuites();

	virtual ASErr Notify(AINotifierMessage *message);

	virtual ASErr GoAction(DoActionMessage *message);

	virtual ASErr GoMenuItem(AIMenuMessage *message);
	virtual ASErr UpdateMenuItem(AIMenuMessage *message);

	virtual ASErr GetFilterParameters(AIFilterMessage *message);
	virtual ASErr GoFilter(AIFilterMessage *message);

	virtual ASErr PluginGroupNotify(AIPluginGroupMessage *message);
	virtual ASErr PluginGroupUpdate(AIPluginGroupMessage *message);

	virtual ASErr GetFileFormatParameters(AIFileFormatMessage *message);
	virtual ASErr GoFileFormat(AIFileFormatMessage *message);
	virtual ASErr CheckFileFormat(AIFileFormatMessage *message);
	virtual ASErr FileFormatUpdate(AIUpdateFileFormatMessage *message);
	virtual ASErr SetFileFormatParameters(DoActionMessage *message);

	virtual ASErr EditTool(AIToolMessage *message);
	virtual ASErr TrackToolCursor(AIToolMessage *message);
	virtual ASErr ToolMouseDown(AIToolMessage *message);
	virtual ASErr ToolMouseDrag(AIToolMessage *message);
	virtual ASErr ToolMouseUp(AIToolMessage *message);
	virtual ASErr SelectTool(AIToolMessage *message);
	virtual ASErr DeselectTool(AIToolMessage *message);
	virtual ASErr ReselectTool(AIToolMessage *message);
	virtual ASErr DecreaseDiameter(AIToolMessage *message);
	virtual ASErr IncreaseDiameter(AIToolMessage *message);

	virtual ASErr EditLiveEffectParameters(AILiveEffectEditParamMessage * message);
	virtual ASErr GoLiveEffect(AILiveEffectGoMessage * message);
	virtual ASErr LiveEffectInterpolate(AILiveEffectInterpParamMessage * message);
	virtual ASErr LiveEffectGetInputType(AILiveEffectInputTypeMessage * message);
	virtual ASErr LiveEffectConvertColorSpace(AILiveEffectConvertColorMessage * message);
	virtual ASErr LiveEffectScaleParameters(AILiveEffectScaleParamMessage * message);
	virtual ASErr LiveEffectAdjustColors(AILiveEffectAdjustColorsMessage * message);
	virtual ASErr LiveEffectHandleMerge(AILiveEffectHandleMergeMessage * message);
	
	virtual ASErr GoTimer(AITimerMessage * message);

	virtual ASErr GoClipboard( AIClipboardMessage *message );
	virtual ASErr CanCopyClipboard( AIClipboardMessage *message );
	virtual ASErr CloneClipboard( AIClipboardMessage *message );
	virtual ASErr DisposeClipboard( AIClipboardMessage *message );

	virtual ASErr WorkspaceWrite( AIWorkspaceMessage *message );
	virtual ASErr WorkspaceRestore( AIWorkspaceMessage *message );
	virtual ASErr WorkspaceDefault( AIWorkspaceMessage *message );

private:
	static char *FindMsg(SPPluginRef ref, ASErr error, char *buf, int len);
};

#endif
