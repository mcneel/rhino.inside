#ifndef __AIWinDef__
#define __AIWinDef__

/*
 *		 Name:	AIWinDef.h
 *       Date:	Started 2010
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2010 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file
 * in accordance with the terms of the Adobe license agreement
 * accompanying it. If you have received this file from a source other
 * than Adobe, then your use, modification, or distribution of it
 * requires the prior written permission of Adobe.
 *
 */

#ifdef WIN_ENV
	#ifndef _INC_WINDOWS	// if windows.h is not included

		// A way to declare handle similar to how Windows does it
		#define DECLARE_AI_WINDOWS_HANDLE(name) struct name##__; typedef struct name##__ *name

		// Declare handles that we are interested in
		DECLARE_AI_WINDOWS_HANDLE(HDC);
		DECLARE_AI_WINDOWS_HANDLE(HINSTANCE);
		DECLARE_AI_WINDOWS_HANDLE(HFONT);
		DECLARE_AI_WINDOWS_HANDLE(HWND);

		#undef DECLARE_AI_WINDOWS_HANDLE

	#endif	//	_INC_WINDOWS
#endif	//	WIN_ENV

#endif	//	__AIWinDef__
