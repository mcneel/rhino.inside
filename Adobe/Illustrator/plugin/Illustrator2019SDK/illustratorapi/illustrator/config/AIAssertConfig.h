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

// Asserts should be force enabled (i.e. for release build as well) until RC. 

// Custom configuration
#ifdef ILLUSTRATOR_MINIMAL
#define AI_ASSERTS_ENABLED			0
#else

#define AI_ASSERTS_ENABLED			0 // <--Should be turned to 0 after RC

// Automatic configuration
#ifdef NDEBUG
#define AI_ASSERT_CONTROL_DEBUG		0 // Release mode
#else
#define AI_ASSERT_CONTROL_DEBUG		1 // Debug mode
#endif // NDEBUG

#ifndef AI_ASSERTS_ENABLED
#define AI_ASSERTS_ENABLED		AI_ASSERT_CONTROL_DEBUG
#endif // AI_ASSERT_FORCE_ENABLE

#endif //ILLUSTRATOR_MINIMAL
