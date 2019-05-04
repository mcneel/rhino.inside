//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/Plugin.cpp $
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

#include "Plugin.hpp"

//AI includes
#include "AIRuntime.h"
#include "AppContext.hpp"

//standard includes
#include <string.h>
#include <stdio.h> 
#include <time.h>
#include <new>

//SP suites
extern "C" SPBasicSuite *sSPBasic;


//------------

Plugin::Plugin(SPPluginRef pluginRef, const char* name)
{
	fPluginRef = pluginRef;
	fSuites = NULL;
  m_pluginName = name;
	fLockCount = 0;
	fPluginAccess = nullptr;
	fLastError = kNoErr;
	fSupressDuplicateErrors = true;
	fErrorTimeout = 5;		// seconds
	fLastErrorTime = 0;
}


void *Plugin::operator new(size_t size)
{
	return (Plugin *) ::new(std::nothrow) char[size];
}

void Plugin::operator delete(void *pMem)
{
	char *theMem = (char*)pMem;
	::delete [] theMem;
}

ASErr Plugin::StartupPlugin(SPInterfaceMessage *message)
{
	ASErr error = kNoErr;

	if (!error)
		error = SetGlobal(this);
		
	fSuites = new(std::nothrow) Suites;

	if (!fSuites)
		error = kOutOfMemoryErr;
	else
	{
		error = fSuites->Error();
		fSuites->InitializeRefCount();
	}
	
	if (error)
	{
		if (fSuites)
			delete fSuites;
		fSuites = nullptr;
	}

	if (!error)
	{
		if(!error)
			error = sSPPlugins->SetPluginName( message->d.self, m_pluginName.c_str() );
		
		if (!error)
		{
			char notifierName[kMaxStringLength];

			sprintf(notifierName, "%s App Started Notifier", m_pluginName.c_str());
			error = sAINotifier->AddNotifier(message->d.self, notifierName, kAIApplicationStartedNotifier, NULL);
		}
	}
	

	if (!error)
		error = AllocateSuiteTables();

	if (!error)
		FillSuiteTables();

	if(!error)
		error = Plugin::LockPlugin(true);

	return error;
}
 
ASErr Plugin::ShutdownPlugin(SPInterfaceMessage * /*message*/)
{
	ASErr error = kNoErr;

	if(fSuites) {
		delete fSuites;
		fSuites = nullptr;
	}
	
	SetGlobal(nullptr);

	return error;
}

ASErr Plugin::LockPlugin(ASBoolean lock)
{
	if (lock)
	{
		fLockCount++;
		if (fLockCount == 1)
			sSPAccess->AcquirePlugin(fPluginRef, &fPluginAccess );
	}
	else
	{
		fLockCount--;
		if (fLockCount == 0)
		{
			sSPAccess->ReleasePlugin( fPluginAccess );
			fPluginAccess = nullptr;
		}
		else if (fLockCount < 0)
			fLockCount = 0;			// Shouldn't happen, but...
	}

	return kNoErr;
}

ASBoolean Plugin::Purge()
{
	return false;
}

ASBoolean Plugin::IsReloadMsg(char *caller, char *selector)
{
	return (strcmp(caller, kSPAccessCaller ) == 0 &&
		strcmp( selector, kSPAccessReloadSelector) == 0);
}

ASErr Plugin::Message(char *caller, char *selector, void *message)
{
	ASErr error = kUnhandledMsgErr;
	
	// Acquire any missing optional suites.
	AcquireOptionalSuites();

	/* Sweet Pea messages */

	if (strcmp(caller, kSPAccessCaller ) == 0)
	{
		if (strcmp( selector, kSPAccessUnloadSelector) == 0)
			error = UnloadPlugin((SPInterfaceMessage *)message);

		else if (strcmp( selector, kSPAccessReloadSelector) == 0)
			error = ReloadPlugin((SPInterfaceMessage *)message);
	}
	else if (strcmp(caller, kSPInterfaceCaller) == 0)
	{
		if (strcmp(selector, kSPInterfaceAboutSelector) == 0)
			error = kNoErr;

		else if (strcmp(selector, kSPInterfaceStartupSelector) == 0)
			error = kNoErr;
	}
	else if (strcmp(caller, kSPCacheCaller) == 0)
	{
		if (strcmp(selector, kSPPluginPurgeCachesSelector) == 0)
		{
			if (Purge())
				error = kSPPluginCachesFlushResponse;
			else
				error = kSPPluginCouldntFlushResponse;
		}
	}
	else if (strcmp( caller, kSPPropertiesCaller ) == 0)
	{
		if (strcmp( selector, kSPPropertiesAcquireSelector ) == 0)
		{
			error = AcquireProperty((SPPropertiesMessage *) message);
		}
		else if (strcmp( selector, kSPPropertiesReleaseSelector ) == 0)
		{
			error = ReleaseProperty((SPPropertiesMessage *) message);
		}
	}

	/* Some common AI messages */

	else if (strcmp(caller, kCallerAINotify) == 0)
	{
		AppContext appContext(((SPInterfaceMessage *)message)->d.self);

		// Ideally we would rely upon the caller to envelop our Notify method.
		// But since we won't work right if he doesn't, do this ourselves

		AINotifierMessage *msg = (AINotifierMessage *)message;

		if (strcmp(msg->type, kAIApplicationStartedNotifier) == 0)
			error = PostStartupPlugin();

		if (!error || error == kUnhandledMsgErr)
		{
			if (strcmp( selector, kSelectorAINotify ) == 0)
				error = Notify(msg);
		}
	}
	else if (strcmp(caller, kActionCaller) == 0)
	{
		if (strcmp( selector, kDoActionSelector ) == 0)
		{
			error = GoAction((DoActionMessage *)message);
		}
	}
	else if (strcmp(caller, kCallerAIMenu) == 0)
	{
		if (strcmp( selector, kSelectorAIGoMenuItem ) == 0)
		{
			error = GoMenuItem((AIMenuMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIUpdateMenuItem ) == 0)
		{
			error = UpdateMenuItem((AIMenuMessage *)message);
		}
	}
	else if (strcmp(caller, kCallerAIFilter) == 0)
	{
		if (strcmp( selector, kSelectorAIGetFilterParameters ) == 0)
		{
			error = GetFilterParameters((AIFilterMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIGoFilter ) == 0)
		{
			error = GoFilter((AIFilterMessage *)message);
		}
	}
	else if (strcmp(caller, kCallerAIPluginGroup) == 0)
	{
		if (strcmp( selector, kSelectorAINotifyEdits ) == 0)
		{
			error = PluginGroupNotify((AIPluginGroupMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIUpdateArt ) == 0)
		{
			error = PluginGroupUpdate((AIPluginGroupMessage *)message);
		}
	}
	else if (strcmp(caller, kCallerAIFileFormat) == 0)
	{
		if (strcmp( selector, kSelectorAIGetFileFormatParameters ) == 0)
		{
			error = GetFileFormatParameters((AIFileFormatMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIGoFileFormat ) == 0)
		{
			error = GoFileFormat((AIFileFormatMessage *)message);
		}
		else if (strcmp( selector, kSelectorAICheckFileFormat ) == 0)
		{
			error = CheckFileFormat((AIFileFormatMessage *)message);
		}
		else if ( strcmp( selector, kSelectorAIUpdateFileFormat ) == 0 )
		{
			error = FileFormatUpdate( (AIUpdateFileFormatMessage *)message );
		}
		else if (!strcmp( selector, kDoActionSelector))
		{
			error = SetFileFormatParameters( (DoActionMessage *) message );
		}
	}
	else if (strcmp(caller, kCallerAITool) == 0)
	{
		if (strcmp( selector, kSelectorAIEditToolOptions ) == 0)
		{
			error = EditTool((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAITrackToolCursor ) == 0)
		{
			error = TrackToolCursor((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIToolMouseDown ) == 0)
		{
			error = ToolMouseDown((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIToolMouseDrag ) == 0)
		{
			error = ToolMouseDrag((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIToolMouseUp ) == 0)
		{
			error = ToolMouseUp((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAISelectTool ) == 0)
		{
			error = SelectTool((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIDeselectTool ) == 0)
		{
			error = DeselectTool((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIReselectTool ) == 0)
		{
			error = ReselectTool((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIToolDecreaseDiameter ) == 0)
		{
			error = DecreaseDiameter((AIToolMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIToolIncreaseDiameter ) == 0)
		{
			error = IncreaseDiameter((AIToolMessage *)message);
		}
		

	} else if (strcmp(caller, kCallerAILiveEffect ) == 0)
	{
		if (strcmp( selector, kSelectorAIEditLiveEffectParameters ) == 0)
		{
			error = EditLiveEffectParameters((AILiveEffectEditParamMessage *)message);
		}
		else if (strcmp( selector, kSelectorAIGoLiveEffect ) == 0)
		{
			error = GoLiveEffect((AILiveEffectGoMessage *)message);
		}
		else if (strcmp( selector, kSelectorAILiveEffectInterpolate ) == 0)
		{
			error = LiveEffectInterpolate((AILiveEffectInterpParamMessage *)message);
		}
		else if (strcmp( selector, kSelectorAILiveEffectInputType ) == 0)
		{
			error = LiveEffectGetInputType((AILiveEffectInputTypeMessage *)message);
		}
		else if (strcmp( selector, kSelectorAILiveEffectScaleParameters ) == 0)
		{
			error = LiveEffectScaleParameters((AILiveEffectScaleParamMessage *)message);
		}
		else if (strcmp( selector, kSelectorAILiveEffectConverColorSpace ) == 0)
		{
			error = LiveEffectConvertColorSpace((AILiveEffectConvertColorMessage *)message);
		}
		else if (strcmp( selector, kSelectorAILiveEffectAdjustColors ) == 0)
		{
			error = LiveEffectAdjustColors((AILiveEffectAdjustColorsMessage *)message);
		}
		else if (strcmp( selector, kSelectorAILiveEffectHandleMerge ) == 0)
		{
			error = LiveEffectHandleMerge((AILiveEffectHandleMergeMessage *)message);
		}
	} else if (strcmp(caller, kCallerAITimer ) == 0)
	{
		if (strcmp( selector, kSelectorAIGoTimer ) == 0)
		{
			error = GoTimer((AITimerMessage *)message);
		}
	}
	else if (strcmp(caller, kCallerAIClipboard ) == 0)
	{
		if ( strcmp( selector, kSelectorAIGoClipboard ) == 0 )
			error = GoClipboard( (AIClipboardMessage *) message );

		else if ( strcmp( selector, kSelectorAICanCopyClipboard ) == 0 )
			error = CanCopyClipboard( (AIClipboardMessage *) message );

		else if ( strcmp( selector, kSelectorAICloneClipboard ) == 0 )
			error = CloneClipboard( (AIClipboardMessage *) message );

		else if ( strcmp( selector, kSelectorAIDisposeClipboard ) == 0 )
			error = DisposeClipboard( (AIClipboardMessage *) message );
	}
	else if (strcmp(caller, kAIWorkspaceCaller ) == 0)
	{
		if ( strcmp( selector, kAIWSWriteSelector ) == 0 )
			error = WorkspaceWrite( (AIWorkspaceMessage *) message );

		else if ( strcmp( selector, kAIWSRestoreSelector ) == 0 )
			error = WorkspaceRestore( (AIWorkspaceMessage *) message );

		else if ( strcmp( selector, kAIWSDefaultSelector ) == 0 )
			error = WorkspaceDefault( (AIWorkspaceMessage *) message );
	}
	return error;
}

ASErr Plugin::UnloadPlugin(SPInterfaceMessage * /*message*/)
{	
	ASErr error = kNoErr;
	
	EmptySuiteTables();

	SetGlobal(nullptr);

	if (fSuites) {
		delete fSuites;
		fSuites = nullptr;
	}

	return error;
}


ASErr Plugin::ReloadPlugin(SPInterfaceMessage * /*message*/)
{
	ASErr error = kNoErr;

	if (!error)
		error = SetGlobal(this);

	// fSuites should always be nullptr here, but check just to be sure
	if (!fSuites)
		fSuites = new(std::nothrow) Suites;

	if(!fSuites)
		error = kOutOfMemoryErr;
	else
	{
		error = fSuites->Error();
		fSuites->InitializeRefCount();
	}

	if (error)
	{
		if (fSuites)
			delete fSuites;
		fSuites = nullptr;
	}

	if (!error)
		FillSuiteTables();

	return error;
}


void Plugin::ReportError(ASErr error, char * /*caller*/, char * /*selector*/, void * /*message*/)
{
	if (FilterError(error))
		return;
		
	time_t now = time(nullptr);
	
	if (error == fLastError && fSupressDuplicateErrors &&
		now < fLastErrorTime + fErrorTimeout)
		return;

	fLastError = error;
	fLastErrorTime = now;
	DefaultError(GetPluginRef(), error);
}


void Plugin::DefaultError(SPPluginRef ref, ASErr error)
{
	if (FilterError(error))
		return;
	
	ASBoolean gotBasic = false;
	if (sAIUser == nullptr) {
		if (sSPBasic == nullptr)
			return;
		ASErr err = sSPBasic->AcquireSuite(kAIUserSuite, 
			kAIUserSuiteVersion, (const void **) &sAIUser);
		if (err || sAIUser == nullptr)
			return;
		gotBasic = true;
	}

	char msg[128];
	char *m;
	m = FindMsg(ref, error, msg, sizeof(msg));
	if (m == nullptr)
		goto release;
	
	char mbuf[128];

	if (strlen(m) < 120) {
		char errString[10];
		if (error < 16385) {  // Then probably a plain ol' number
			sprintf(errString, "%d", error);

		} else {	// Yucky 4-byte string
			int i;
			for (i = 3; i >= 0; i--) {
				errString[i] = (char) ((unsigned long) error) & 0xff;
				error = ((unsigned long) error) >> 8;
			}
			errString[4] = '\0';
		}
		sprintf(mbuf, m, errString);
		m = mbuf;
	}
	sAIUser->ErrorAlert(ai::UnicodeString(m));
release:
	if (gotBasic) {
		sSPBasic->ReleaseSuite(kAIUserSuite, kAIUserSuiteVersion);
		sAIUser = nullptr;
	}
}

char *Plugin::FindMsg(SPPluginRef /*ref*/, ASErr /*error*/, char* /*buf*/, int /*len*/)
{
	//int n = 1;
	//ASErr err;
	/*while (1) {
		char code[10];
		err = sADMBasic->GetIndexString(ref,  
					16050, n, code, sizeof(code));
		// If we got an error, back off and use the last string, which should be
		// the default message
		if (err || code[0] == '\0') {
			if (n == 1)
				return nullptr;		// no error strings found
			else {
				n--;
				goto getString;
			}
		}

		if (code[0] == '-' || (code[0] >= '0' && code[0] <= '9')) {
			// This is a number, so see if it matches
			int c = atoi(code);
			if (c == error) {
				n++;
				goto getString;
			}

		} else {
			// non numeric 4 byte err code.  (e.g.) '!sel'.
			int	c, i;
			c = 0;

			for (i = 0; i < 4; i++)
				c = (c << 8) + code[i];

			if (c == error) {
				n++;
				goto getString;
			}
		}

		n += 2;
	}

getString:
	err = sADMBasic->GetIndexString(ref, 16050, n, buf, len);
	if (err || buf[0] == '\0')
		return nullptr;
	else
		return buf;*/
	return nullptr;
}


ASBoolean Plugin::FilterError(ASErr error)
{
	static const ASErr errors[] = {
		kUnknownFormatErr,
		kRefusePluginGroupReply,
		kWantsAfterMsgPluginGroupReply,
		kMarkValidPluginGroupReply,
		kDontCarePluginGroupReply,
		kDestroyPluginGroupReply,
		kCheckPluginGroupReply,
		kCustomHitPluginGroupReply,
		kToolCantTrackCursorErr,
		kSPPluginCachesFlushResponse,
		kSPSuiteNotFoundError,
		kSPCantAcquirePluginError,
		kDidSymbolReplacement,
		kSkipEditGroupReply,
		kIterationCanQuitReply,
		kCanceledErr,
		361,
		0
	};

	int i;
	for (i = 0; errors[i] != 0 && errors[i] != error; i++) {}
	return errors[i] != 0;
}

/* Stubbies */

ASErr Plugin::AllocateSuiteTables()
{
	return kNoErr;
}

ASErr Plugin::FillSuiteTables()
{
	return kNoErr;
}

ASErr Plugin::EmptySuiteTables()
{
	return kNoErr;
}

ASErr Plugin::AcquireOptionalSuites()
{
	if(fSuites)
		fSuites->acquire_Optional_Suites();
	return kNoErr;
}

ASErr Plugin::PostStartupPlugin()
{
	return kNoErr;
}

ASErr Plugin::SetGlobal(Plugin * /*plugin*/)
{
	return kNoErr;
}

ASErr Plugin::AcquireProperty(SPPropertiesMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ReleaseProperty(SPPropertiesMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::Notify(AINotifierMessage * /*message*/)
{
	return kNoErr;
}

ASErr Plugin::GoAction(DoActionMessage * /*message*/)
{
	return kNoErr;
}

ASErr Plugin::GoMenuItem(AIMenuMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::UpdateMenuItem(AIMenuMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GetFilterParameters(AIFilterMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GoFilter(AIFilterMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::PluginGroupNotify(AIPluginGroupMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::PluginGroupUpdate(AIPluginGroupMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GetFileFormatParameters(AIFileFormatMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GoFileFormat(AIFileFormatMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::CheckFileFormat(AIFileFormatMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::FileFormatUpdate(AIUpdateFileFormatMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::SetFileFormatParameters(DoActionMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::EditTool(AIToolMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::TrackToolCursor(AIToolMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ToolMouseDown(AIToolMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ToolMouseDrag(AIToolMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ToolMouseUp(AIToolMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::SelectTool(AIToolMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::DeselectTool(AIToolMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::ReselectTool(AIToolMessage * /*message*/)
{
	return kNoErr;
}

ASErr Plugin::DecreaseDiameter(AIToolMessage * /*message*/)
{
	return kNoErr;
}

ASErr Plugin::IncreaseDiameter(AIToolMessage * /*message*/)
{
	return kNoErr;
}

ASErr Plugin::EditLiveEffectParameters(AILiveEffectEditParamMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GoLiveEffect(AILiveEffectGoMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectInterpolate(AILiveEffectInterpParamMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectGetInputType(AILiveEffectInputTypeMessage * /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectConvertColorSpace(AILiveEffectConvertColorMessage *  /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectScaleParameters(AILiveEffectScaleParamMessage *  /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectAdjustColors(AILiveEffectAdjustColorsMessage *  /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::LiveEffectHandleMerge(AILiveEffectHandleMergeMessage *  /*message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::GoTimer(AITimerMessage *  /*message*/)
{
	return kUnhandledMsgErr;
}


ASErr Plugin::GoClipboard(AIClipboardMessage * /* message*/)
{
	return kUnhandledMsgErr;
}


ASErr Plugin::CanCopyClipboard(AIClipboardMessage * /* message*/)
{
	return kUnhandledMsgErr;
}


ASErr Plugin::CloneClipboard(AIClipboardMessage * /* message*/)
{
	return kUnhandledMsgErr;
}


ASErr Plugin::DisposeClipboard(AIClipboardMessage * /* message*/)
{
	return kUnhandledMsgErr;
}


ASErr Plugin::WorkspaceWrite(AIWorkspaceMessage * /* message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::WorkspaceRestore(AIWorkspaceMessage * /* message*/)
{
	return kUnhandledMsgErr;
}

ASErr Plugin::WorkspaceDefault(AIWorkspaceMessage * /* message*/)
{
	return kUnhandledMsgErr;
}
