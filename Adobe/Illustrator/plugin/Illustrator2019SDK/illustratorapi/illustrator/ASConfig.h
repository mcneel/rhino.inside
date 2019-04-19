/***********************************************************************/
/*                                                                     */
/* ASConfig.h                                                          */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2007 Adobe Systems Incorporated.                     */
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

#ifndef __ASConfig__
#define __ASConfig__

/*
 * Platform constants
 *
 * These are to be used for platform specific code (i.e. Carbon/Cocoa vs Win32 calls).
 * Do not use them for processor or endianness conditionals. See the other defines below
 *
 * At this time:
 * MAC_ENV means Mac OS X (Carbon/Cocoa)
 * WIN_ENV means Windows (Win32)
 *
 */

/*
 * Defines for Metrowerks
 */
#if defined (__MWERKS__)
	#if defined (__POWERPC__)
		#ifndef MAC_ENV
			#define MAC_ENV
		#endif
	#elif defined (__INTEL__)
		#ifndef WIN_ENV
			#define WIN_ENV
		#endif
	#else
		#error Unknown platform
	#endif
#endif

/*
 * Defines for GNU (including Xcode and MinGW)
 */
#if  defined(__GNUC__)
	#if ( defined(__APPLE_CPP__) || defined(__APPLE_CC__) )
		#ifndef MAC_ENV
			#define MAC_ENV
		#endif
	#elif defined (__MINGW32__)
		#ifndef WIN_ENV
			#define WIN_ENV
		#endif
	#endif
#endif

/*
 * Defines for Visual C++ on Windows.
 */
#ifdef _MSC_VER
	#ifndef WIN_ENV
		#define WIN_ENV
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


/*
 * Processor Type
 *
 * The processor definition is intended for processor specific code (ie Assembly).
 * In general you should probably use AS_IS_LITTLE_ENDIAN for most cases.
 * If you use AS_POWERPC or AS_X86 try and code up a vanilla c version which will compile up on any processor.
 * e.g.
 * #if AS_POWERPC
 *	Do your PPC Stuff
 * #elif AS_X86
 *	Do your x86 stuff
 * #else
 *  Do the vanilla c version of the processor specific stuff
 * #endif
 *
 * At this time:
 * AS_POWERPC means PowerPC (G3/G4/G5 type processors)
 * AS_X86 means X86 architecture (Intel/AMD)
 *
 */
#ifdef MAC_ENV
	#if defined(__POWERPC__)
		#define AS_POWERPC 1
		#define AS_X86 0
	#elif defined (__i386__)
		#define AS_POWERPC 0
		#define AS_X86 1
		#define AS_X86_32
		#define AS_MAC_32
	#elif defined (__x86_64__)
		#define AS_POWERPC 0
		#define AS_X86 1
		#define AS_X86_64
		#define AS_MAC_64
	#else
		//We don't care in Rez if we have a processor defined
		#if !defined(IOS_ENV)
			#ifndef rez
				#warning Unknown Processor - Going to compile vanilla versions
			#endif
		#endif
		#define AS_POWERPC 0
		#define AS_X86 0
	#endif
#endif

#ifdef WIN_ENV
	#define AS_POWERPC 0
	#define AS_X86		1
	#if defined(_WIN64)
		#define AS_X86_64
		#define AS_WIN_64
	#elif defined(_WIN32)
		#define AS_X86_32
		#define AS_WIN_32
	#else
		#error Unknown MSVC Compiler
	#endif
#endif

//check for consistency
#ifdef MAC_ENV
    #if !defined(IOS_ENV)
	#if ((!defined(AS_MAC_64) && !defined(AS_MAC_32)) || (defined(AS_MAC_64) && defined(AS_MAC_32)) || (defined(AS_WIN_32) || defined(AS_WIN_64)) )
		#error
	#endif
    #endif
#endif

//macro for MAC 64 bit
#ifdef AS_MAC_64
#define MAC64_ENV
#endif

//macro for windows 64 bit
#ifdef AS_WIN_64
#define WIN64_ENV
#endif

#ifdef WIN_ENV
	#if ((!defined(AS_WIN_32) && !defined(AS_WIN_64)) || (defined(AS_WIN_32) && defined(AS_WIN_64)) || (defined(AS_MAC_32) || defined(AS_MAC_64)) )
		#error
	#endif
#endif

#ifdef AS_X86_32
	#if ((!defined(AS_WIN_32) && !defined(AS_MAC_32)) || (defined(AS_MAC_64) || defined(AS_WIN_64)) )
		#error
	#endif
#endif

#ifdef AS_X86_64
	#if ((!defined(AS_WIN_64) && !defined(AS_MAC_64)) || (defined(AS_WIN_32) || defined(AS_MAC_32)) )
		#error
	#endif
#endif
/*
 * Endianness
 *
 * What order you expect the bytes to be in.
 * If you aren't sure about endianness check out: http://en.wikipedia.org/wiki/Endianness
 *
 * In general, Intel/AMD processors are little endian, PowerPC is big endian (PowerPC can run in little endian mode though).
 *
 */

#ifdef MAC_ENV
	#if defined (__LITTLE_ENDIAN__)
		#define AS_IS_LITTLE_ENDIAN 1
	#elif defined (__BIG_ENDIAN__)
		#define AS_IS_LITTLE_ENDIAN 0
	#else
		//We don't care in Rez if we have a endianness defined
		#ifndef rez
			#error Unknown Endianness
		#endif
	#endif
#endif

#ifdef WIN_ENV
	#define AS_IS_LITTLE_ENDIAN 1
#endif

#endif /* __ASConfig__ */
