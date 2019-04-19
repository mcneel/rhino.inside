/***********************************************************************/
/*                                                                     */
/* SPTypes.h                                                           */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1995-2007 Adobe Systems Incorporated.                     */
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
/***********************************************************************/


/** The basic declarations used by the PICA
	plug-in management suites.  **/


#ifndef __SPTypes__
#define __SPTypes__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPConfig.h"
#include "AIBasicTypes.h"

#include "SPHeaderBegin.h"

/*
 *	You can replace SPTypes.h with your own. Define OTHER_SP_TYPES_H on the
 *	command line or in SPConfig.h to be the name of the replacement file.
 *
 *	Example:
 *
 *	#define OTHER_SP_TYPES_H "MySPTypes.h"
 *	#include "SPBasic.h"  // for example
 *
 *	Sweet Pea depends on TRUE, FALSE, SPErr, etc. Your replacement must
 *	define them.
 */

#ifdef OTHER_SP_TYPES_H
#include OTHER_SP_TYPES_H
#else


/*******************************************************************************
 **
 **	Constants
 **
 **/

#ifdef __cplusplus
	#undef TRUE
	#define TRUE	true

	#undef FALSE
	#define FALSE	false
#else
	#ifndef TRUE
	#define TRUE	1
	#endif

	#ifndef FALSE
	#define FALSE	0
	#endif
#endif

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


/*
 *	SPAPI is placed in front of procedure declarations in the API. On the Mac
 *	it used to be 'pascal', which forced consistent calling conventions across different
 *	compilers. No longer needed. On Windows it's nothing.
 *
 *	Example:
 *
 *	SPAPI void *SPAllocateBlock( long size, const char *debug, SPErr *error );
 *
 */

#ifdef MAC_ENV
#define SPAPI
#endif

#ifdef WIN_ENV
#define SPAPI
#endif


#ifdef MAC_ENV

/** On Mac OS, \c SPBoolean is \c Boolean. */
typedef unsigned char SPBoolean;

#endif


#ifdef WIN_ENV

/** On Windows, \c SPBoolean is \c BOOL. */
typedef int SPBoolean;

#endif

typedef signed long SPInt32;

/*******************************************************************************
 **
 **	Error Handling
 **
 **/

/** PICA error codes are C strings, except for the no-error code, which
	is \c NULL (and \c #kSPOutOfMemoryError). Compare errors first with
	\c #kSPNoError, to text for success. On failure, compare with
	predefined error constants in \c SPErrorCodes.h.

	For example:
@code
 SPErr error = kSPNoError;
 block = SPAllocateBlock( size, debug, &error );
 	if ( error != kSPNoError ) {
		if ( strcmp( error, kSPOutOfMemoryError ) == 0 )
 			FailOutOfMemory();
			...
 		}
@endcode
*/
typedef ai::int32 SPErr;


#include "SPErrorCodes.h"

#endif /* OTHER_SP_TYPES_H */

#include "SPHeaderEnd.h"

#endif
