/***********************************************************************/
/*                                                                     */
/* ASTypes.h                                                           */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2015 Adobe Systems Incorporated.                     */
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
/* Started by Dave Lazarony, 01/26/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __ASTypes__
#define __ASTypes__

/*
 * Includes
 */

#ifndef __ASConfig__
#include "ASConfig.h"
#endif
#include "AIBasicTypes.h"

#ifdef WIN_ENV
	#include "AIWinDef.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


//We need everything to be properly aligned on Windows
#ifdef WIN_ENV
#pragma pack(push, 8)
#endif

/*
 * Constants
 */

// true and false

#ifndef __cplusplus
#ifndef true
#define true	1
#endif

#ifndef false
#define false	0
#endif
#endif // __cplusplus

#ifdef TRUE
#undef TRUE
#endif
#define TRUE	true

#ifdef FALSE
#undef FALSE
#endif
#define FALSE	false

// error codes
/** @ingroup Errors */
#define kNoErr					0
/** @ingroup Errors */
#define kOutOfMemoryErr			'!MEM'
/** @ingroup Errors */
#define kBadParameterErr		'PARM'
/** @ingroup Errors */
#define kNotImplementedErr		'!IMP'
/** @ingroup Errors (debugging) */
#define kCantHappenErr			'CANT'


#ifndef NULL

#ifdef MAC_ENV
#if !defined(__cplusplus) && (defined(__SC__) || defined(THINK_C))
#define NULL	((void *) 0)
#else
#define NULL	0
#endif
#endif

#ifdef WIN_ENV
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif

// AMPAPI  Adobe Standard Plugin API calling convention.

#ifndef AMPAPI
#ifdef MAC_ENV
#define ASAPI
#endif
#ifdef WIN_ENV
#define ASAPI
#endif
#endif

// C calling convention for those places that need it.
// This doesn't really do anything, but is  more for
// an explicitly declaration when it matters.
#define ASCAPI



/*
 * Types
 */

// Integer Types

#ifndef _H_CoreExpT
/** 8-bit integer */
typedef signed char ASInt8;
/** 16-bit integer */
typedef signed short ASInt16;

// ASNumTypes is causing redefination error.
// TODO Replace occurances with ai::int32 before
// moving to 64 bit.
#ifndef	__TREAT_ASINT32_AS_INT__
/** 32-bit integer */
typedef ai::int32 ASInt32;
#else
typedef signed int ASInt32;
#endif

#endif
/** 8-bit integer */
typedef unsigned char ASUInt8;
/** 16-bit integer */
typedef unsigned short ASUInt16;
/** 32-bit integer */
typedef ai::uint32 ASUInt32;

/** Error code */
typedef ai::int32 ASErr;

// Storage Types

typedef unsigned char ASByte;
typedef ASByte* ASBytePtr;

// Unicode Types
/** Unicode double-byte character */
typedef ASUInt16 ASUnicode;

// Pointer Types
/** Void pointer */
typedef void* ASPtr;
/** Opaque reference */
typedef void** ASHandle;

// Fixed Types
/** Numeric value (long) used for fixed-math fractional values, as \c #AIFract. Obsolete. */
typedef ASInt32 ASFract;
/** Numeric value (floating-point) */
typedef float ASReal;

#ifndef _AS_FIXED_TYPE_
#define _AS_FIXED_TYPE_ 1

/** Fixed numeric value - obsolete, use \c #ASReal */
typedef	ASInt32 ASFixed;
/** Point specified with \c #ASFixed coordinates - obsolete, use \c #ASRealPoint */
typedef struct _t_ASFixedPoint {
	ASFixed h, v;
} ASFixedPoint, *ASFixedPointP;

/** Rectangle specified with \c #ASFixed coordinates - obsolete, use \c #ASRealRect */
typedef struct _t_ASFixedRect {
	ASFixed left, top, right, bottom;
} ASFixedRect, *ASFixedRectP;

/** Transformation matrix specified with \c #ASFixed values - obsolete, use \c #ASRealMatrix */
typedef struct _t_ASFixedMatrix {
	ASFixed a, b, c, d, tx, ty;
} ASFixedMatrix, *ASFixedMatrixP;

#endif/* _AS_FIXED_TYPE_ */

/** Point specified with \c #ASReal coordinates */
typedef struct _t_ASRealPoint {
	ASReal h, v;
} ASRealPoint;

/** Rectangle specified with \c #ASReal coordinates */
typedef struct _t_ASRealRect {
	ASReal left, top, right, bottom;
} ASRealRect;

/** Transformation matrix specified with \c #ASReal values */
typedef struct _t_ASRealMatrix {
	ASReal a, b, c, d, tx, ty;
	void Init()
	{
		a = 0.0; b = 1.0;
		c = 1.0; d = 0.0;
		tx = 0.0; ty = 0.0;
	}
} ASRealMatrix;

/** Generic reference to a resource (plug-in) file.
	Generally equivalent to an \c #SPPluginRef  */
typedef struct ASAccess* ASAccessRef;


//
//
// Platform dependant natively aligned structures
//
//

#ifdef MAC_ENV
/** Mac OS only. Size type for Mac OS \c Rect and \c Point.*/
typedef short ASSize;

/** Mac OS only. the same as Mac OS \c Boolean.	 */
typedef unsigned char ASBoolean;
#endif

#ifdef WIN_ENV
/** Windows only. the same as  Windows \c BOOL. */
typedef int ASBoolean;

/** Windows only. Size type for Windows \c Rect and \c Point.*/
typedef ai::int32 ASSize;
#endif


//
//
// Platform dependant fixed alignment (68K on Mac, 4 Byte on Windows) structures
//
//
#if defined(MAC_ENV) && !__LP64__
#pragma options align=mac68k
#endif
// Platform Structures

#ifdef MAC_ENV

/** Port reference, Mac OS only, same as Mac OS \c CGrafPtr. */
typedef struct MacPort_t* AIPortRef;
    
/** Window reference, Mac OS only, same as Mac OS \c WindowPtr. */
typedef struct MacWindow_t* AIWindowRef;
    
/** Dialog reference, Mac OS only, same as Mac OS \c DialogPtr. */
typedef struct MacDialog_t* AIDialogRef;

// ASRect is the same size and layout as a Macintosh Rect.
/*typedef struct _t_ASRect {
	ASSize top, left, bottom, right;
} ASRect;*/

// ASPoint is the same size and layout as a Macintosh Point.
/*typedef struct _t_ASPoint {
	ASSize v, h;
} ASPoint;*/

#endif


#ifdef WIN_ENV

/** Port reference, Windows only, same as Windows \c HDC. */
typedef HDC ASPortRef;

/** Window reference, Windows only, same as Windows \c HWND. */
typedef HWND ASWindowRef;

/** Dialog reference, Windows only, same as Windows \c HWND. */
typedef HWND ASDialogRef;

// ASRect is the same size and layout as a Windows RECT.
/*typedef struct _t_ASRect {
	ASSize left, top, right, bottom;
} ASRect;*/

// ASPoint is the same size and layout as a Windows POINT.
/*typedef struct _t_ASPoint  {
	ASSize h, v;
} ASPoint;*/

#endif

// ASRGBColor is the same as a Macintosh RGBColor on Macintosh and Windows.
/*typedef struct _t_ASRGBColor {
	unsigned short red, green, blue;
} ASRGBColor;*/


// AIEvent is the same as a Macintosh EventRecord on Macintosh and Windows.
/*typedef struct _t_ASEvent {
	unsigned short	what;
	unsigned long	message;
	unsigned long	when;
	ASPoint			where;
	unsigned short	modifiers;

} ASEvent;*/

#if defined(MAC_ENV) && !__LP64__
#pragma options align=reset
#endif
#ifdef WIN_ENV
#pragma pack(pop)
#endif

//
//
// End of Aligned Structures
//
//

#ifdef __cplusplus
}
#endif


#endif
