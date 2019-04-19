//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/Tutorial/Source/TutorialPanelController.cpp $
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

#include "IllustratorSDK.h"
#include "TutorialPlugin.h"
#include "TutorialSuites.h"
#include "TutorialPanelController.h"
#include "AppContext.hpp"

static const char* TUTORIAL_UI_EXTENSION	= "com.adobe.illustrator.tutorialui.dialog"; // Our extension's ID
static const char* APP_ID					= "ILST";		// Illustrator's CSXS App ID

//----------------------------------------------------------------------------- CSXS events
static const char* GET_PARAMS_REQ	= "com.adobe.aisdk.TutorialGetParamsReq";
static const char* GET_PARAMS_RESP	= "com.adobe.aisdk.TutorialGetParamsResp";
static const char* DIALOG_READY		= "com.adobe.aisdk.TutorialDialogReady";

//----------------------------------------------------------------------------- XML Tags
static const std::string CORNERS_TAG	= "corners";
static const std::string CANCELLED_TAG	= "cancelled";
static const std::string SIZE_TAG		= "size";
static const std::string DEFAULT_TAG	= "default";
static const std::string MIN_TAG		= "min";
static const std::string MAX_TAG		= "max";

struct ParamConstant
{
	const TutorialFilterParameters params;
	const std::string label;
};

static const ParamConstant params[] =
{
	kDefaultFilterParameters,	DEFAULT_TAG,
	kMinFilterParameters,		MIN_TAG,
	kMaxFilterParameters,		MAX_TAG
};

//----------------------------------------------------------------------------- CSXS Event handlers
static void PanelReadyFunc(const csxs::event::Event* const /*eventParam*/, void* const context)
{
	TutorialPanelController *controller = (TutorialPanelController *) context;

	if ( controller )
	{
		AppContext appContext(gPlugin->GetPluginRef());
		controller->SendData();
	}
}

static void GetParamsFromPanel(const csxs::event::Event* const eventParam, void* const context)
{
	TutorialPanelController *controller = (TutorialPanelController *) context;

	if ( controller )
	{
		AppContext appContext(gPlugin->GetPluginRef());
		
		// Parse the data
		controller->ParseData(eventParam->data);

		// Apply the filter (or not if cancelled)
		controller->ApplyFilter();
	}
}

//----------------------------------------------------------------------------- XML Parser

// Get the contents of the first instance of the "tag" tag in the xmlString,
// assuming the tag has no attributes
static std::string getTagContents(const std::string xmlString, const std::string tag)
{
	// Get the index of the char beyond the end of the opening tag
	std::string openTag("<" + tag + ">");
	std::string::size_type openIndex = xmlString.find(openTag);
	openIndex += openTag.length();
	
	// Get the index of the first char of the ending tag
	std::string closingTag("</" + tag + ">");
	std::string::size_type closingIndex = xmlString.find(closingTag);
	
	// Now get the tag contents
	std::string tagContents("");
	std::string::size_type strLength = closingIndex - openIndex;
	if (strLength > 0)
		tagContents = xmlString.substr(openIndex, strLength);
	
	return tagContents;
}

//----------------------------------------------------------------------------- PanelController
TutorialPanelController::TutorialPanelController()
	: FlashUIController(TUTORIAL_UI_EXTENSION)
{}

csxs::event::EventErrorCode TutorialPanelController::RegisterCSXSEventListeners()
{
	csxs::event::EventErrorCode result = csxs::event::kEventErrorCode_Success;
	do
	{
		result = fPPLib.AddEventListener(DIALOG_READY, PanelReadyFunc, this);
		if ( result != csxs::event::kEventErrorCode_Success )
		{
			break;
		}

		result = fPPLib.AddEventListener(GET_PARAMS_RESP, GetParamsFromPanel, this);
		if ( result != csxs::event::kEventErrorCode_Success )
		{
			break;
		}
	}
	while ( false );
	
	return result;
}

csxs::event::EventErrorCode TutorialPanelController::RemoveEventListeners()
{
	csxs::event::EventErrorCode result = csxs::event::kEventErrorCode_Success;
	do
	{
		result = fPPLib.RemoveEventListener(DIALOG_READY, PanelReadyFunc, this);
		if ( result != csxs::event::kEventErrorCode_Success )
		{
			break;
		}

		result = fPPLib.RemoveEventListener(GET_PARAMS_RESP, GetParamsFromPanel, this);
		if ( result != csxs::event::kEventErrorCode_Success )
		{
			break;
		}
	}
	while ( false );
	
	return result;
}

void TutorialPanelController::ParseData(const char* eventData)
{
	std::string size_str = getTagContents(eventData, SIZE_TAG);
	std::string corners_str = getTagContents(eventData, CORNERS_TAG);
	
	ai::int32 size, corners;
	ai::NumberFormat numFormat;
	sAIStringFormatUtils->StringToInteger(numFormat, ai::UnicodeString(size_str), size);
	sAIStringFormatUtils->StringToInteger(numFormat, ai::UnicodeString(corners_str), corners);
	fParams.size = size;
	fParams.corners = corners;
	
	string canceledStr = getTagContents(eventData, CANCELLED_TAG);
	fCancelled = (canceledStr.compare("true") == 0);

	sAIFilter->SetFilterParameters(gPlugin->getFilterHandle(),&fParams);
}

ASErr TutorialPanelController::SendData()
{
	
	stringstream payload;
	payload << "<payload>";
	
	ai::int16 numOfConstants = sizeof(params) / sizeof(ParamConstant);
	for (ai::int16 i = 0; i < numOfConstants; i++)
	{
		payload << "<" << params[i].label << ">"
			<< "<" << CORNERS_TAG << ">"
			<< params[i].params.corners
			<< "</" << CORNERS_TAG << ">"
			<< "<" << SIZE_TAG << ">"
			<< params[i].params.size
			<< "</" << SIZE_TAG << ">"
			<< "</" << params[i].label << ">";
	}
	
	payload << "</payload>";
	
	std::string payload_str = payload.str();
	
	const char* payload_cstr = payload_str.c_str();
	
	csxs::event::Event event = 
	{
		GET_PARAMS_REQ,
		csxs::event::kEventScope_Application,
		APP_ID,
		NULL,
		payload_cstr
	};
	
	fPPLib.DispatchEvent(&event);
	
	return kNoErr;
}

void TutorialPanelController::CloseDownPanel()
{
	UnloadExtension();
}

void TutorialPanelController::ApplyFilter()
{
	if (!fCancelled)
	{
		sAINotifier->Notify(kTutorialApplyFilterNotifier, &fParams);
	}
}
