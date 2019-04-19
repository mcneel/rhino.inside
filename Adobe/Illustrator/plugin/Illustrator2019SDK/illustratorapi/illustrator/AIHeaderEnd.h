/***********************************************************************/
/*                                                                     */
/* AIHeaderEnd.h                                                       */
/* A standard place to put the junk that occurs at the end             */
/* of all of our headers. You must include AIHeaderBegin.h BEFORE      */
/* you include this file or you will get an error                      */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 2005-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/* Started by Dave MacLachlan, 07/10/2005                              */
/*                                                                     */
/***********************************************************************/

#if !defined(__AIHeaderBegin_H__)
#error You need to include AIHeaderBegin before this file
#endif

#undef __AIHeaderBegin_H__

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