/*
 *        Name:	SPHeaderEnd.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2012 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file
 * in accordance with the terms of the Adobe license agreement
 * accompanying it. If you have received this file from a source other
 * than Adobe, then your use, modification, or distribution of it
 * requires the prior written permission of Adobe.
 *
 */

#if !defined(__SPHeaderBegin_H__)
#error You need to include SPHeaderBegin before this file
#endif

#undef __SPHeaderBegin_H__

#ifdef MAC_ENV
	#pragma options align=reset
	#if defined (__MWERKS__)
		//GCC doesn't allow non int enums without using an attribute decl directly on
		//the enum, so no need to set it
		#pragma enumsalwaysint reset
	#endif
#endif

#ifdef WIN_ENV
	#pragma pack(pop)
#endif

#ifdef __cplusplus
}
#endif