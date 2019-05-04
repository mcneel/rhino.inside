/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2018 Adobe
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

#include "./config/AIAssertConfig.h"

#if	AI_ASSERTS_ENABLED

#include "AIAssertion.h"

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIAssertion)
#elif defined(_AIASSERT_SUITE_INCLUDE_H_)
    #include _AIASSERT_SUITE_INCLUDE_H_
#else
	extern "C" AIAssertionSuite *sAIAssertion;
#endif // AI_AUTO_SUITE_AVAILABLE

#endif	// AI_ASSERTS_ENABLED

#include "AIHeaderBegin.h"

#if	AI_ASSERTS_ENABLED
namespace ai
{
	void ShowPlatformAssert(const bool success, const char* message);
}
#define AIAssert(_success)                                                          \
    do                                                                              \
    {                                                                             	\
		try																			\
		{																			\
			if(sAIAssertion)                                                            \
			{                                                                           \
				sAIAssertion->AssertProc((_success), nullptr, __FILE__, __LINE__);      \
			}                                                                           \
			else                                                                        \
			{                                                                           \
				ai::ShowPlatformAssert((_success),nullptr);                             \
			}                                                                          \
		} \
		catch(...) {} \
    } while (0)                                                                     \
	



#define AIMsgAssert(_success, _message)                                             \
    do                                                                              \
    {                                                                               \
		try \
		{ \
			if(sAIAssertion)                                                            \
			{                                                                           \
				sAIAssertion->AssertProc((_success), (_message), __FILE__, __LINE__);   \
			}                                                                           \
			else                                                                        \
			{                                                                           \
				ai::ShowPlatformAssert((_success), _message);                                       \
			}                                                                           \
		} \
		catch (...) {} \
    } while (0)                                                                     \

#else

#define AIAssert(_success)				\
	do									\
	{									\
	} while (0)							\

#define AIMsgAssert(_success, _message) \
	do									\
	{									\
	} while (0)							\

#endif	// AI_ASSERTS_ENABLED

#include "AIHeaderEnd.h"
