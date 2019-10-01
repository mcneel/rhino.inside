/***********************************************************************/
/*                                                                     */
/* SPConfig.h                                                          */
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

/**

	SPConfig.h is the environment configuration file for Sweet Pea. It
	defines MAC_ENV or WIN_ENV. These are used to control platform-specific
	sections of code.

 **/

#ifndef __SPCnfig__
#define __SPCnfig__

/*
 * Defines for Metrowerks
 */
#if defined (__MWERKS__)
	#if defined (__POWERPC__)
		#ifndef MAC_ENV
			#define MAC_ENV 1
		#endif
	#endif
	#if defined (__INTEL__)
		#ifndef WIN_ENV
			#define WIN_ENV 1
		#endif
	#endif
#endif

/*
 * Defines for GNU
 */
#if  defined(__GNUC__)
	#if ( defined(__APPLE_CPP__) || defined(__APPLE_CC__) )
		#ifndef MAC_ENV
			#define MAC_ENV 1
		#endif
	#endif
	#if defined (__INTEL__)
		#ifndef WIN_ENV
			#define WIN_ENV 1
		#endif
	#endif
#endif

/*
 * Defines for Visual C++ on Windows.
 */
#ifdef _MSC_VER
	#ifndef WIN_ENV
		#define WIN_ENV 1
	#endif
#endif

/*
 *	Make certain that one and only one of the platform constants is defined.
 */

#if !defined(WIN_ENV) && !defined(MAC_ENV)
	#error
#endif

#if defined(WIN_ENV) && defined(MAC_ENV)
	#error
#endif

#endif
