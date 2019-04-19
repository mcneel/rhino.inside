/*************************************************************************
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2017 Adobe Systems Incorporated
* All Rights Reserved.
*
* NOTICE: All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any. The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by all applicable intellectual property
* laws, including trade secret and copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/


#pragma once

#include "AITypes.h"
#include "AIFilePath.h"
#include "AIDictionary.h"
#include "IAIRef.h"
#include "AIHeaderBegin.h"


#define kAIRasterExportSuite					"AI Raster Export Suite"
#define kAIRasterExportSuiteVersion				AIAPI_VERSION(1)


enum AIRasterFileFormats:ai::uint8
{
	kAIFormatUnknown = 0,
	kAIFormatPSD,
	kAIFormatTIFF
};


struct AIRasterExportSuite {

	// This function allows the client to export an art in various formats. It accepts several parameters:
	// @param hRaster is the opaque reference to an art object which need not be raster art. API will rasterize it first.
	// @param filePath is the location of exported file.
	// @param AIRasterFileFormats are the supported file formats.
	// @param ConstAIDictionaryRef is a dictionary variable taken up by the client.
	/*		
		#include "AITIFFKeys.h"
		#include "IAIDictionary.hpp"
		#include "AIRasterExport.h"
		#include "AITypes.h"
		#include "AIDictionary.h"
		#include "AIDictionaryKeyHelper.hpp"

		use_suite(AIRasterExport)
		use_suite(AIDictionary)

		#define kAiAntiAlias				"AntiAlias"

		DictionaryKeyDeclareAndDefine(kAIAntiAliasKey, kAiAntiAlias);

		AIErr ExportToTiff(const AIArtHandle hRaster, const ai::FilePath& path)
		{
			ai::Dictionary dict;
			dict.Set(kAIAntiAliasKey, 1);
			return sAIRasterExport->RasterExport(hRaster, path, kAIFormatTIFF, dict.get());
		}

	*/
	AIAPI AIErr(*RasterExport)(const AIArtHandle hRaster, const ai::FilePath& filePath, AIRasterFileFormats format,
		ai::Ref<AIDictionaryRef> formatOptionsDict);

};


#include "AIHeaderEnd.h"



