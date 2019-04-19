#include "TutorialPlugin.h"
#include "TutorialSuites.h"
#include "TutorialID.h"
#include "SDKAboutPluginsHelper.h"
#include "AICSXS.h"
#include "TutorialPanelController.h"
#include "Plugin.hpp"

#include <string.h>
#include <stdio.h>

#ifndef NDEBUG
#ifdef MAC_ENV

#else
#include <Windows.h>
#endif
#endif

#include <metahost.h>
//#include "corerror.h" // if you want error codes to CorBindToRuntimeEx
#pragma comment(lib, "mscoree.lib")


TutorialPlugin* gPlugin = nullptr;


extern "C"
{
  SPBasicSuite *sSPBasic;
}

extern void FixupReload(Plugin *plugin);


extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
  ASErr error = kNoErr;
  SPMessageData *msgData = (SPMessageData *)message;

  Plugin *plugin = (Plugin *)msgData->globals;

  sSPBasic = msgData->basic;

  if (strcmp(caller, kSPInterfaceCaller) == 0)
  {
    if (strcmp(selector, kSPInterfaceStartupSelector) == 0)
    {
      plugin = new TutorialPlugin(msgData->self);
      if (plugin)
      {
        msgData->globals = (void *)plugin;
        error = plugin->StartupPlugin((SPInterfaceMessage *)message);

        if (error != kNoErr)
        {
          // Make sure to delete in case startup failed
          delete plugin;
          plugin = nullptr;
          msgData->globals = nullptr;
        }
      }
      else
      {
        error = kOutOfMemoryErr;
      }
    }
    else if (strcmp(selector, kSPInterfaceShutdownSelector) == 0)
    {
      if (plugin)
      {
        error = plugin->ShutdownPlugin((SPInterfaceMessage *)message);
        delete plugin;
        plugin = nullptr;
        msgData->globals = nullptr;
      }
    }
  }

  if (plugin)
  {
    if (Plugin::IsReloadMsg(caller, selector))
    {
      // Call this before calling any virtual functions (like Message)
      FixupReload(plugin);
      error = plugin->ReloadPlugin((SPInterfaceMessage *)message);
    }
    else
    {
      // If a load or reload failed because the suites could not be acquired, we released
      // any partially acquired suites and returned an error.  However, SuitePea still might
      // call us, so protect against this situation.
      if (plugin->SuitesAcquired())
        error = plugin->Message(caller, selector, message);
      else
        error = kNoErr;
    }

    if (error == kUnhandledMsgErr)
    {
      error = kNoErr;
#ifndef NDEBUG
#ifdef MAC_ENV
      fprintf(stderr, "Warning: Unhandled plugin message: caller \"%s\" selector \"%s\"\n", caller, selector);
#else
      char buf[1024];

      sprintf_s(buf + 1, 1024, "Warning: Unhandled plugin message: caller \"%s\" selector \"%s\"\n", caller, selector);
      OutputDebugStringA(buf + 1);
#endif
#endif
    }
  }

  if (error)
  {
    if (plugin)
      plugin->ReportError(error, caller, selector, message);
    else
      Plugin::DefaultError(msgData->self, error);
  }

  return error;
}



/*
*/
void FixupReload(Plugin* plugin)
{
	TutorialPlugin::FixupVTable((TutorialPlugin*) plugin);
}

/*
*/
ASErr TutorialPlugin::SetGlobal(Plugin *plugin)
{
	gPlugin = (TutorialPlugin *) plugin;
	return kNoErr;
}

TutorialPlugin::TutorialPlugin(SPPluginRef pluginRef) 
	: Plugin(pluginRef),
	fAboutPluginMenu(NULL),
	fApplyFilterNotifier(NULL),
	fCSXSPlugPlugSetupCompleteNotifier(NULL),
	fPanelController(NULL),
    fResourceManagerHandle(NULL),
	fShutdownApplicationNotifier(NULL)
{
	strncpy(fPluginName, kTutorialPluginName, kMaxStringLength);
}

ASErr TutorialPlugin::StartupPlugin(SPInterfaceMessage* message)
{
	ASErr error = Plugin::StartupPlugin(message);

	if (!error) {
		error = AddMenu(message);
	}
	if (!error) {	
		error = AddFilter(message);
	}
	if (!error) {
		error = AddTool(message);
	}
	if (!error) {
		error = AddAction(message);
	}
	if (!error) {
		error = AddNotifiers(message);
	}

	return error;
}

ASErr TutorialPlugin::PostStartupPlugin()
{
	ASErr result = kNoErr;

	// Create flash controller
	if (fPanelController == NULL)
	{
		fPanelController = new TutorialPanelController();
		result = Plugin::LockPlugin(true);
	}
  if(!result)
      sAIUser->CreateCursorResourceMgr(fPluginRef,&fResourceManagerHandle);


  return result;
}

ASErr TutorialPlugin::ShutdownPlugin(SPInterfaceMessage* message)
{
	if (fPanelController != NULL)
	{
		fPanelController->RemoveEventListeners();
		delete fPanelController;
		fPanelController = NULL;
	}

	return Plugin::ShutdownPlugin(message);
}

ASErr TutorialPlugin::AddNotifiers(SPInterfaceMessage* message)
{
	AIErr result;
	result = sAINotifier->AddNotifier(message->d.self, "Tutorial " kAICSXSPlugPlugSetupCompleteNotifier,
										kAICSXSPlugPlugSetupCompleteNotifier,
										&fCSXSPlugPlugSetupCompleteNotifier);
	
	result = sAINotifier->AddNotifier(message->d.self, kTutorialPluginName,
										kTutorialApplyFilterNotifier,
										&fApplyFilterNotifier);

	result = sAINotifier->AddNotifier(fPluginRef, kTutorialPluginName, 
										kAIApplicationShutdownNotifier, 
										&fShutdownApplicationNotifier);
	return result;
}

ASErr TutorialPlugin::Notify(AINotifierMessage *message)
{
	if ( message->notifier == fCSXSPlugPlugSetupCompleteNotifier )
	{
		if (fPanelController != NULL)
		{
			fPanelController->RegisterCSXSEventListeners();
		}
	}
	else if ( message->notifier == fApplyFilterNotifier )
	{
		TutorialFilterParameters* params = (TutorialFilterParameters*)message->notifyData;
		ActuallyGoFilter(*params);
	}
	 if (message->notifier == fShutdownApplicationNotifier)
	{
		if(fResourceManagerHandle != NULL)
		{
			sAIUser->DisposeCursorResourceMgr(fResourceManagerHandle);
			fResourceManagerHandle = NULL;
		}
	}

	return kNoErr;
}

/* Adds this plug-in's menus.
*/
AIErr TutorialPlugin::AddMenu ( SPInterfaceMessage* message )
{
	ASErr error = kNoErr;

	// Add About Plugins menu item for this plug-in.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				kTutorialPluginName "...", 
				&fAboutPluginMenu);
	return error;
}

/* Handles this plug-in's menus.
*/
AIErr TutorialPlugin::GoMenuItem ( AIMenuMessage* message )
{
	SDKAboutPluginsHelper aboutPluginsHelper;
	aboutPluginsHelper.PopAboutBox(message, "About Tutorial", kSDKDefAboutSDKCompanyPluginsAlertString);

	return kNoErr;
}

/* Adds this plug-in's filter.
*/
AIErr TutorialPlugin::AddFilter ( SPInterfaceMessage* message )
{
	AIErr error = kNoErr;
	AIMenuItemHandle menuItem = nullptr;

	// Set the filter Category and Title from string resources
	PlatformAddFilterData filterData;
	filterData.category = (unsigned char*)kSDKFilterString;
	filterData.title = (unsigned char*)kTutorialFilterString;
  
    char filterName[] = "Tutorial";
    
	// Add the filter.
	error = sAIFilter->AddFilter( message->d.self, filterName, &filterData,
								kToolWantsToTrackCursorOption, &fFilterHandle);
	if ( !error ) {
		// Only enable the filter's menu item if a document is open.
		error = sAIFilter->GetFilterMenuItem(fFilterHandle, &menuItem);
		if ( !error ) {
			error = sAIMenu->UpdateMenuItemAutomatically(menuItem,
				kAutoEnableMenuItemAction,
				0, 0,	// don't care about what's in artwork
				0, 0,	// don't care about selection
				kIfOpenDocument, 0 );	// Enable if a document is open
		}
	}

	return error;
}

/* Prompts for input parameters for this plug-in's filter.
*/
AIErr TutorialPlugin::GetFilterParameters( AIFilterMessage* message ) 
{
	if (fPanelController != NULL)
		fPanelController->LoadExtension();

	message->parameters = NULL;
	return kNoErr;
}

/* Filter if there are parameters already taken
*/
AIErr TutorialPlugin::GoFilter( AIFilterMessage* /*message*/ )
{
	AIErr error = kNoErr;
  TutorialFilterParameters p;
  p.corners = 4;
  p.size = 40;
//  if(message->parameters != NULL)
	{
    TutorialFilterParameters* params = &p;// (TutorialFilterParameters*)message->parameters;
		this->ActuallyGoFilter(*params);
	}
	return error;
}

static ICLRRuntimeHost* LaunchDotNetRuntime()
{
  // Reference:
  // MSDN: Loading the Common Language Runtime into a Process
  // http://msdn.microsoft.com/en-us/library/01918c6x.aspx
  ICLRMetaHost* pMetaHost = 0;
  HRESULT hr = ::CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pMetaHost);
  if (S_OK != hr)
  {
    //RHINO_ERROR("S_OK != ::CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*)&pMetaHost);");
    return nullptr;
  }
  if (nullptr == pMetaHost)
  {
    //RHINO_ERROR("::CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*)&pMetaHost); set pMetaHost = null");
    return nullptr;
  }

  ICLRRuntimeInfo* pRuntimeInfo = 0;
  hr = pMetaHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (LPVOID*)&pRuntimeInfo);
  pMetaHost->Release();
  if (S_OK != hr)
  {
    //RHINO_ERROR("S_OK != pMetaHost->GetRuntime(L\"v4.0.30319\",IID_ICLRRuntimeInfo,(LPVOID*)&pRuntimeInfo);");
    return nullptr;
  }
  if (nullptr == pRuntimeInfo)
  {
    //RHINO_ERROR("pMetaHost->GetRuntime(L\"v4.0.30319\",IID_ICLRRuntimeInfo,(LPVOID*)&pRuntimeInfo); set pRuntimeInfo = null");
    return nullptr;
  }

  ICLRRuntimeHost* pRuntimeHost = 0;
  hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&pRuntimeHost);
  pRuntimeInfo->Release();
  if (S_OK != hr)
  {
    //RHINO_ERROR("S_OK != pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*)&pRuntimeHost);");
    return nullptr;
  }
  if (nullptr == pRuntimeHost)
  {
    //RHINO_ERROR("pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*)&pRuntimeHost); set pRuntimeHost = null");
    return nullptr;
  }

  return pRuntimeHost;
}



AIErr TutorialPlugin::ActuallyGoFilter(TutorialFilterParameters params)
{
  if (nullptr == m_pRuntimeHost)
  {
    m_pRuntimeHost = LaunchDotNetRuntime();
    if (m_pRuntimeHost)
    {
      HRESULT hr = m_pRuntimeHost->Start();
    }
  }

  if (m_pRuntimeHost)
  {
    DWORD return_code = 0;
    const wchar_t* path = L"C:\\dev\\github\\mcneel\\rhino.inside\\Adobe\\Illustrator\\bin\\x64\\Debug\\RhinoInside.Illustrator.dll";
    HRESULT hr = m_pRuntimeHost->ExecuteInDefaultAppDomain(path, L"RhinoInside.Illustrator.Initialization", L"Start", nullptr, &return_code);
    if (return_code == 123)
      return 1;
  }
	AIErr 	error = kNoErr;

	// Do your stuff here, for example...


	return error;
}

extern "C" __declspec(dllexport) void RhDrawShape(int count, double* points2d)
{
  // Create a new path.
  AIArtHandle path;
  AIErr error = sAIArt->NewArt(kPathArt, kPlaceAboveAll, nullptr, &path);

  // Find the point on the page that's in the middle of the window.
  AIRealPoint center = { 0,0 };
  if (!error) {
    error = sAIDocumentView->GetDocumentViewCenter(nullptr, &center);
  }

  // Create the polygon points, randomly located around the center.
  if (!error)
  {
    ASInt32  corners = 6;// params.corners;
    ASInt32  size = 80;// params.size;
    AIPathSegment segment;
    // All of the segments are corners
    segment.corner = true;
    for (int i = 0; i < count; ++i)
    {
      segment.p.h = points2d[2 * i] + center.h;
      segment.p.v = points2d[2*i+1] + center.v;
      segment.in = segment.out = segment.p;
      error = sAIPath->SetPathSegments(path, i, 1, &segment);
      if (error)
        break;
    }
  }

  // Close the path.
  if (!error)
  {
    //error = sAIPath->SetPathClosed(path, true);
  }

  // Allow the filter to be recorded as an action event.
  if (!error)
  {
    //error = RecordFilterAction(params);
  }

  if (!error)
  {
    error = sAIArt->SetArtUserAttr(path, kArtSelected, kArtSelected);
  }

}

/* Adds this plug-in's tool to Illustrator.
*/
AIErr TutorialPlugin::AddTool( SPInterfaceMessage* message ) 
{
	AIErr error = kNoErr;
	AIAddToolData toolData;
	toolData.title = "Tutorial Line Tool"; 
	toolData.tooltip = "Tutorial Line Tool";
	toolData.sameGroupAs = kNoTool;
	toolData.sameToolsetAs = kNoTool;
	toolData.normalIconResID = kTutorialToolIconResourceID;
	toolData.darkIconResID = kTutorialToolIconResourceID;
	toolData.iconType = ai::IconType::kSVG;

	ai::int32	options = kToolWantsToTrackCursorOption;

	error = sAITool->GetToolNumberFromName(kTutorialTool, &toolData.sameGroupAs); // the Crop Area tool is now the first in its group
	if (error) return error;

	error = sAITool->GetToolNumberFromName(kTutorialTool, &toolData.sameToolsetAs); // and at the top of its tool stack
	if (error) return error;


	if (!error) {
		error = sAITool->AddTool( message->d.self, kTutorialTool, &toolData,
					options, &fToolHandle);
	}

	return error;
}

ASErr TutorialPlugin::TrackToolCursor( AIToolMessage* /*message*/ )
{
    AIErr error = kNoErr;
	error = sAIUser->SetSVGCursor(kTutorialToolIconResourceID, fResourceManagerHandle);
	return error;
}

ASErr TutorialPlugin::DeselectTool( AIToolMessage* /*message*/ )
{
    return kNoErr;   
}
		
/* Handles mouse down event for this plug-in's tool.
*/
AIErr TutorialPlugin::ToolMouseDown( AIToolMessage* message ) 
{
	AIErr 	error = kNoErr;
	AIArtHandle path = nullptr;
	AIPathSegment segment;	
	ai::int32 	count = 0;
	AIMatchingArtSpec spec[1];
	AIArtHandle** matches = nullptr;
	short segmentCount = 0;

	// Get the current selection (if any).
	if ( !error ) {
		spec[0].type = kPathArt;
		spec[0].whichAttr = kArtSelected;
		spec[0].attr = kArtSelected;
		error = sAIMatchingArt->GetMatchingArt( spec, 1, &matches, &count );
	}

	bool addPoint = false;
	if ( !error ) {
		if ( count == 0 ) {
			addPoint = true;
			// There is no selection, so make a new path.
			error = sAIArt->NewArt( kPathArt, kPlaceAboveAll, nullptr, &path );
			
			// Select it so we find it later.
			if (!error) {
				error = sAIArt->SetArtUserAttr( path, kArtSelected, kArtSelected );
			}
		}
		else if ( count == 1 ) {
			addPoint = true;
			path = (*matches)[0];
		}
	}

	//  Add point to the path at the mouse down location.
	if ( !error && addPoint) {
		error = sAIPath->GetPathSegmentCount( path, &segmentCount );
		// All of the segments are corners
		if ( !error) {
			segment.corner = true;  
			segment.p.h = message->cursor.h;
			segment.p.v = message->cursor.v;
			segment.in = segment.out = segment.p;
			error = sAIPath->SetPathSegments( path, segmentCount, 1, &segment );
		}
	}

	return error;
}

/* Registers this plug-in's action with Illustrator.
*/
AIErr TutorialPlugin::AddAction ( SPInterfaceMessage* message )
{
	AIErr 	error = kNoErr;

	// This is your opportunity to register your plug-in to the Action Manager and
	// describe its parameter block.
	// verify that the sAIActionManager suite pointer is valid
	// if the Action plug-in was disabled (taken from the Plug-ins folder)
	// then the sAIActionManager suite pointer would not be valid.
	// We acquire and release this suite individually during reload and unload
	if (sAIActionManager)
	{
		AIActionParamTypeRef actionParam = nullptr;
		SPPluginRef	pluginRef = message->d.self;

		// Create a new Type Parameter Block (TPB)
		sAIActionManager->AINewActionParamType(&actionParam);	
		
		if (actionParam && pluginRef)
		{
			// Fill in the TPB.
			// This describes which parameters your filter requires.

			// Set the 'Corners' parameter in the Type Parameter Block (TPB)
			sAIActionManager->AIActionSetTypeKey(actionParam, 'crnr', kActionNumberString, actionTypeInteger, true);
			// Set the 'Size' parameter in the TPB
			sAIActionManager->AIActionSetTypeKey(actionParam, 'size', kActionSizeString, actionTypeInteger, true);
			
			// Register the your plug-in to the Action Manager
			// The kActionTitleString parameter is the name of the Action which
			// will be shown in the Action Palette.
			error = sAIActionManager->RegisterActionEvent("AISDK_Tutorial", kActionTitleString,
															1, 0, nullptr, pluginRef,
															nullptr, 
															actionParam);

			// Dispose the TPB. The Action Manager has already made a copy of it internally.
			sAIActionManager->AIDeleteActionParamType(actionParam);		
		}
	}
	return error;
}

/*
*/
AIErr TutorialPlugin::RecordFilterAction(const TutorialFilterParameters& parameters)
{
	ASErr error = kNoErr;
	AIActionParamValueRef valueParameterBlock = nullptr;

	// Record Action if InRecordMode
	// If the user is InRecordMode (the Record button was pressed in the Action Palette),
	// your plug-in must report user parameters to the Action Manager so that it can
	// replay this at a later time.
	// Your plug-in will receive a kActionCaller/kDoActionSelector when the Action Manager
	// wants you to replay this action.
	if (sAIActionManager && sAIActionManager->InRecordMode()) {
		
		// create a new Value Parameter Block (VPB)
		error = sAIActionManager->AINewActionParamValue(&valueParameterBlock);		
		if (!error && valueParameterBlock) {
			// Set the 'crnr' parameter in the VPB
			sAIActionManager->AIActionSetInteger(valueParameterBlock, 'crnr', parameters.corners);
			// Set the 'size' parameter in the VPB
			sAIActionManager->AIActionSetInteger(valueParameterBlock, 'size', parameters.size);
			// Record this action with parameters contained in the VPB
			sAIActionManager->RecordActionEvent("AISDK_Tutorial", kDialogOn, valueParameterBlock);
			// Delete the VPB, the Action Manager makes an internal copy of it.
			sAIActionManager->AIDeleteActionParamValue(valueParameterBlock);		
		}
	}
	return error;
}

/* Executes this plug-in's action. 
 * This routine gets called when your plug-in gets called with kActionCaller/kDoActionSelector
 * Your plug-in is being run by the Actions panel.
*/
AIErr TutorialPlugin::GoAction(DoActionMessage* doActionMessage)
{
	ASErr error = kNoErr;
	TutorialFilterParameters** params_handle;
  AIFilterMessage filterMessageStruct;
  AIFilterMessage* filterMessage = nullptr;

	// Allocate instance of struct MyFilterParameters
	if (!error) {
		filterMessage = &filterMessageStruct;
		filterMessage->d = doActionMessage->d;
		error = sAIMDMemory->MdMemoryNewHandle( sizeof( TutorialFilterParameters ), ( AIMdMemoryHandle *)&filterMessage->parameters);
		if ( !error && !filterMessage->parameters ) {
			error = kOutOfMemoryErr;
		}
	}

	// Extract parameter values from the the Value Parameter Block (VPB). 
	if (!error && filterMessage) {
		AIActionParamValueRef valueParameterBlock = doActionMessage->param;
		params_handle = ( TutorialFilterParameters **) filterMessage->parameters;
		error = sAIActionManager->AIActionGetInteger(valueParameterBlock, 'crnr', &(*params_handle)->corners);
		if (!error) {
			error = sAIActionManager->AIActionGetInteger(valueParameterBlock, 'size', &(*params_handle)->size);
		}
	}

	// Pop filter parameters dialog if asked to.
	if (!error && doActionMessage->showDialog) {
		error = GetFilterParameters( filterMessage );
	} 

	// Apply the filter.
	if (!error) {
		error = GoFilter( filterMessage );
	}

	return error;
}

AIFilterHandle TutorialPlugin::getFilterHandle()
{
	return fFilterHandle;
}
