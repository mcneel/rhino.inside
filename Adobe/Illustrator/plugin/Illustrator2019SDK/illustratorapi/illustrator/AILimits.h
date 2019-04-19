/*************************************************************************
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2017 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
**************************************************************************/

#pragma once


#define kAILimitsSuite					"AI Limits Suite"
#define kAILimitsSuiteVersion			AIAPI_VERSION(1)  
#define kAILimitsVersion				kAILimitsSuiteVersion

#include <limits>

#include "AITypes.h"

namespace ai
{
	constexpr auto kInfinity = std::numeric_limits<AIReal>::infinity();
 
	// Use following constants for initializing "bounds" which will contain a union of bounds.
	// kNullUnionBoundsSoft has max limits considering axis +Y going in bottom
	// kNullUnionBoundsHard has max limits considering axis +Y going in top (+X going in left in both of above)
	//												{	LEFT,		TOP,		RIGHT,		  BOTTOM   };
	constexpr AIRealRect kNullUnionBoundsHard       { kInfinity , kInfinity  , -kInfinity , -kInfinity };
	constexpr AIRealRect kNullUnionBoundsSoft	    { kInfinity , -kInfinity , -kInfinity ,  kInfinity }; 

}

#include "AIHeaderBegin.h"
/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
This suite provides utilities that allow you to get the Limits . 

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAILimitsSuite and \c #kAILimitsSuiteVersion.

*/
struct AILimitsSuite
{
	/** Retrieves the size of the canvas in current AI version. 
	(Note that this function returns a constant value, not an error code.)
	@return The canvas size (assuming square canvas)
	*/
	AIAPI ai::int32(*GetCanvasSize)();
};

#include "AIHeaderEnd.h"








