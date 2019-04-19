#include "RhinoInsidePlugin.h"
#include "RhinoInsideSuites.h"
#include "AICSXS.h"
#include "Plugin.hpp"
#include "AIAnnotator.h"

#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <metahost.h>

//#include "corerror.h" // if you want error codes to CorBindToRuntimeEx
#pragma comment(lib, "mscoree.lib")


CRhinoInsidePlugIn* gPlugin = nullptr;


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
      plugin = new CRhinoInsidePlugIn(msgData->self);
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
      char buf[1024];
      sprintf_s(buf + 1, 1024, "Warning: Unhandled plugin message: caller \"%s\" selector \"%s\"\n", caller, selector);
      OutputDebugStringA(buf + 1);
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



void FixupReload(Plugin* plugin)
{
	CRhinoInsidePlugIn::FixupVTable((CRhinoInsidePlugIn*) plugin);
}

ASErr CRhinoInsidePlugIn::SetGlobal(Plugin *plugin)
{
	gPlugin = (CRhinoInsidePlugIn *) plugin;
	return kNoErr;
}

CRhinoInsidePlugIn::CRhinoInsidePlugIn(SPPluginRef pluginRef) : Plugin(pluginRef, kPluginName)
{
}

ASErr CRhinoInsidePlugIn::StartupPlugin(SPInterfaceMessage* message)
{
	ASErr error = Plugin::StartupPlugin(message);

  sAIAnnotator->AddAnnotator(message->d.self, "RhinoInsideAnnotator", &m_annotator_handle);
  sAIAnnotator->SetAnnotatorActive(m_annotator_handle, true);

  AITimerHandle timer;
  char name[] = "RedrawTimer";
  sAITimer->AddTimer(message->d.self, name, 10, &timer);
  sAITimer->SetTimerActive(timer, true);

	if (!error) {	
		error = AddFilter(message);
	}
	if (!error) {
		error = AddNotifiers(message);
	}

	return error;
}

ASErr CRhinoInsidePlugIn::PostStartupPlugin()
{
	ASErr result = kNoErr;

  if(!result)
      sAIUser->CreateCursorResourceMgr(fPluginRef,&fResourceManagerHandle);


  return result;
}

ASErr CRhinoInsidePlugIn::ShutdownPlugin(SPInterfaceMessage* message)
{
	return Plugin::ShutdownPlugin(message);
}

ASErr CRhinoInsidePlugIn::AddNotifiers(SPInterfaceMessage* message)
{
	AIErr result;
	result = sAINotifier->AddNotifier(message->d.self, "Tutorial " kAICSXSPlugPlugSetupCompleteNotifier,
										kAICSXSPlugPlugSetupCompleteNotifier,
										&fCSXSPlugPlugSetupCompleteNotifier);
	
	result = sAINotifier->AddNotifier(message->d.self, kPluginName,
										kTutorialApplyFilterNotifier,
										&fApplyFilterNotifier);

	result = sAINotifier->AddNotifier(fPluginRef, kPluginName, 
										kAIApplicationShutdownNotifier, 
										&fShutdownApplicationNotifier);
	return result;
}

ASErr CRhinoInsidePlugIn::Notify(AINotifierMessage *message)
{
	if ( message->notifier == fApplyFilterNotifier )
	{
		RunRhino();
	}
	 if (message->notifier == fShutdownApplicationNotifier)
	{
		if(fResourceManagerHandle)
		{
			sAIUser->DisposeCursorResourceMgr(fResourceManagerHandle);
			fResourceManagerHandle = nullptr;
		}
	}

	return kNoErr;
}

ASErr CRhinoInsidePlugIn::Message(char *caller, char *selector, void *message)
{
  ASErr result = kNoErr;
  try {
    result = Plugin::Message(caller, selector, message);

    if (result == kUnhandledMsgErr) {
      if (strcmp(caller, kCallerAIAnnotation) == 0) {
        if (strcmp(selector, kSelectorAIDrawAnnotation) == 0) {
          DrawAnnotation((AIAnnotatorMessage*)message);
          result = kNoErr;
        }
        else if (strcmp(selector, kSelectorAIInvalAnnotation) == 0) {
          AIAnnotatorMessage* amsg = (AIAnnotatorMessage*)message;
          sAIAnnotator->InvalAnnotationRect(NULL, NULL);
          //result = this->InvalAnnotation((AIAnnotatorMessage*)message);
          result = kNoErr;
          //aisdk::check_ai_error(result);
        }
      }
    }
    //else
    //  aisdk::check_ai_error(result);
  }
  catch (ai::Error& ex) {
    result = ex;
  }
  catch (...) {
    result = kCantHappenErr;
  }
  return result;

}


/* Adds this plug-in's filter.
*/
AIErr CRhinoInsidePlugIn::AddFilter ( SPInterfaceMessage* message )
{
	AIErr error = kNoErr;
	AIMenuItemHandle menuItem = nullptr;

	// Set the filter Category and Title from string resources
	PlatformAddFilterData filterData;
	filterData.category = (unsigned char*)" Rhino";
	filterData.title = (unsigned char*)" Launch...";
  
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
AIErr CRhinoInsidePlugIn::GetFilterParameters( AIFilterMessage* message ) 
{
	//if (fPanelController != NULL)
		//fPanelController->LoadExtension();

	message->parameters = NULL;
	return kNoErr;
}

/* Filter if there are parameters already taken
*/
AIErr CRhinoInsidePlugIn::GoFilter( AIFilterMessage* /*message*/ )
{
	AIErr error = kNoErr;
//  if(message->parameters != NULL)
	{
    RunRhino();
	}
	return error;
}

AIErr CRhinoInsidePlugIn::GoTimer(AITimerMessage* message)
{
  AIRealRect r;
  r.left = -1000;
  r.right = 1000;
  r.top = 1000;
  r.bottom = -1000;
  sAIDocumentView->SetDocumentViewInvalidRect(NULL, &r);
  sAIDocumentView->SetDocumentViewInvalidDocumentRect(NULL, &r);
  sAIDocument->RedrawDocument();
  return kNoErr;
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



bool CRhinoInsidePlugIn::RunRhino()
{
  if (nullptr == m_pRuntimeHost)
  {
    m_pRuntimeHost = LaunchDotNetRuntime();
    if (m_pRuntimeHost)
    {
      m_pRuntimeHost->Start();
    }
    else
      return false;
  }

  std::wstring path = L"C:\\dev\\github\\mcneel\\rhino.inside\\Adobe\\Illustrator\\bin\\x64\\Debug\\RhinoInside.Illustrator.dll";
  HMODULE hmodule = ::GetModuleHandle(L"RhinoInside.Illustrator.PlugIn.aip");
  if (hmodule)
  {
    wchar_t plugin_path[256];
    if (::GetModuleFileName(hmodule, plugin_path, 256))
    {
      std::wstring tempPath = plugin_path;
      tempPath = tempPath.substr(0, tempPath.length() - std::wstring(L".PlugIn.aip").length());
      path = tempPath + L".dll";
    }
  }
  DWORD return_code = 0;
  HRESULT hr = m_pRuntimeHost->ExecuteInDefaultAppDomain(path.c_str(), L"RhinoInside.Illustrator.Initialization", L"Start", nullptr, &return_code);
	return SUCCEEDED(hr);
}

struct ON_2DPOINT_STRUCT
{
  double x;
  double y;
};

std::vector< ON_2DPOINT_STRUCT> _points;

void CRhinoInsidePlugIn::DrawAnnotation(AIAnnotatorMessage* message)
{
  if (_points.size() < 2)
    return;

  AIPoint prev;
  AIRealPoint pt;
  pt.h = _points[0].x;
  pt.v = _points[0].y;
  sAIDocumentView->ArtworkPointToViewPoint(NULL, &pt, &prev);

  for (int i = 1; i < _points.size(); i++)
  {
    AIPoint current;
    pt.h = _points[i].x;
    pt.v = _points[i].y;
    sAIDocumentView->ArtworkPointToViewPoint(NULL, &pt, &current);
    sAIAnnotatorDrawer->DrawLine(message->drawer, prev, current);
    prev = current;
  }
}

////// functions exported to .NET for pInvokes


extern "C" __declspec(dllexport) void RhDrawShape(int count, ON_2DPOINT_STRUCT* points2d, bool closed)
{
  //// Create a new path.
  //AIArtHandle path;
  //AIErr error = sAIArt->NewArt(kPathArt, kPlaceDefault, nullptr, &path);

  //// Find the point on the page that's in the middle of the window.
  //AIRealPoint center = { 0,0 };
  ////if (!error) {
  ////  error = sAIDocumentView->GetDocumentViewCenter(nullptr, &center);
  ////}

  //// Create the polygon points, randomly located around the center.
  //if (!error)
  //{
  //  AIPathSegment segment;
  //  // All of the segments are corners
  //  segment.corner = true;
  //  for (int i = 0; i < count; ++i)
  //  {
  //    segment.p.h = points2d[i].x + center.h;
  //    segment.p.v = points2d[i].y + center.v;
  //    segment.in = segment.out = segment.p;
  //    error = sAIPath->SetPathSegments(path, (short)i, 1, &segment);
  //    if (error)
  //      break;
  //  }
  //}
  _points.clear();
  for (int i = 0; i < count; i++)
    _points.push_back(points2d[i]);

  //// Close the path.
  //if (!error && closed)
  //{
  //  error = sAIPath->SetPathClosed(path, true);
  //}

  //// Allow the filter to be recorded as an action event.
  //if (!error)
  //{
  //  //error = RecordFilterAction(params);
  //}

  //if (!error)
  //{
  //  error = sAIArt->SetArtUserAttr(path, kArtSelected, kArtSelected);
  //}

}
