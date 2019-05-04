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

#include "AIAssert.hpp"

#if	AI_ASSERTS_ENABLED

#ifdef WIN_ENV
#include <windows.h>
namespace ai
{
    void ShowPlatformAssert(const bool success, const char* message)
    {
		if (success)
			return;
		bool shouldBreak = IDYES == ::MessageBoxA(nullptr, message, "Assertion failure, Do you want to Debug?", MB_YESNO | MB_ICONSTOP | MB_TASKMODAL | MB_TOPMOST);
		if (shouldBreak)
		{
			__debugbreak();
		}
    }
}
#elif !defined(IOS_ENV)
    #include <Cocoa/Cocoa.h>
namespace ai
{
    void ShowPlatformAssert(const bool success, const char* message)
    {
		if (success)
			return;
        bool shouldBreak = false;
        @autoreleasepool
        {
            NSAlert *alert = [[[NSAlert alloc] init] autorelease];
            if(alert)
            {
                [alert setMessageText:@"Assertion failure, Do you want to Debug?"];
                [alert addButtonWithTitle:@"Yes"];
                [alert addButtonWithTitle:@"No"];
                NSString *msgStr = [NSString stringWithCString:message encoding:NSASCIIStringEncoding];
                [alert setInformativeText:msgStr];
                [alert setAlertStyle:NSWarningAlertStyle];
                shouldBreak = [alert runModal] == NSAlertFirstButtonReturn;
            }
        }
        if(shouldBreak)
        {
            __asm ("int3");
        }
        
    }
}
#endif//WIN_ENV

#endif	// AI_ASSERTS_ENABLED

