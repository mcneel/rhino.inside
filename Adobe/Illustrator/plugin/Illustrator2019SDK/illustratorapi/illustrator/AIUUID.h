/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2017 Adobe
* 
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

/*******************************************************************************
**
**	Imports
**
**/

#include "AITypes.h"
#include "IAIUUID.h"
#include "IAIUnicodeString.h"	

#include "AIHeaderBegin.h"

/*******************************************************************************
**
** Constants
**
*******************************************************************************/

#define kAIUUIDSuite			"AI UUID Suite"
#define kAIUUIDSuiteVersion		AIAPI_VERSION(1)
#define kAIUUIDVersion			kAIUUIDSuiteVersion

/*******************************************************************************
**
**	Suite
**
********************************************************************************/
/** @ingroup Suites
This suite is in an experimental state, it is not completely production-ready.
These functions allow you to interact with the UUID and associated art
\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIUUIDSuite and \c #kAIUUIDVersion.
@see \c #ai::uuid */
struct AIUUIDSuite {

	/** Retrieves the art object associated with the UUID, if the art
	is in-scope.
	@param _uuid [in] const reference of UUID of art object.
	@param art [out] A buffer in which to return the output as the valid art object,
	or a null pointer if the art object has been deleted or
	moved out of scope.
	This API may fail to provide the correct ArtHandle, if an object's dictionary is acquired 
	but not released after use. (It is not recommended to acquire and hold the dictionary reference 
	for future use)
	*/
	AIAPI AIErr(*GetArtHandle)(const ai::uuid &_uuid, AIArtHandle &art);

	/** Retrieves the UUID associated with the art.
	@param art [in] The art object.
	@param _uuid [out] Reference variable to return the UUID of the art object.
	*/
	AIAPI AIErr(*GetArtUUID)(AIArtHandle art, ai::uuid &_uuid);
};

#include "AIHeaderEnd.h"
