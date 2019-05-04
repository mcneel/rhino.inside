//========================================================================================
//
//  ADOBE CONFIDENTIAL
//
//  File: AIEraserTool.h
//
//  Copyright 2016 Adobe Systems Incorporated
//  All Rights Reserved.
//
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//
//========================================================================================

#ifndef __AIEraserTool__
#define __AIEraserTool__

#include "AITypes.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIEraserToolSuite					"AI Eraser Tool Suite"
#define kAIEraserToolSuiteVersion1			AIAPI_VERSION(1)
#define kAIEraserToolSuiteVersion			kAIEraserToolSuiteVersion1
#define kAIEraserToolVersion				kAIEraserToolSuiteVersion

struct AIEraserToolSuite
{
    /*Erases the art under the given panPoints like an eraser  */
    AIErr (*Erase)(const AIRealPoint* panPoints, const size_t count);
};

#include "AIHeaderEnd.h"

#endif	// __AIEraserTool__
