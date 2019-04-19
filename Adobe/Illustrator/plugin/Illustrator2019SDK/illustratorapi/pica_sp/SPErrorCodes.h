/***********************************************************************/
/*                                                                     */
/* SPErrorCodes.h                                                      */
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


/*******************************************************************************
 **
 ** General Errors
 **
 **/

// General errors
#define kASNoError				0x00000000L
#define kASUnimplementedError	'!IMP'
#define kASUserCanceledError	'stop'


/*******************************************************************************
 **
 ** SP Errors
 **
 **/

// General errors
/** @ingroup Errors
	PICA no-error code is \c NULL. All other
	PICA errors are strings, except \c #kSPOutOfMemoryError. See \c SPTypes.h. */
#define kSPNoError				0x00000000
/** @ingroup Errors
	PICA error, applies to all PICA suites. See \c SPTypes.h. */
#define kSPUnimplementedError	'!IMP'
/** @ingroup Errors
	PICA error. */
#define kSPUserCanceledError	'stop'

// SPAccessSuite errors
/** @ingroup Errors
	PICA access error. See \c #SPAccessSuite. */
#define kSPCantAcquirePluginError			'!Acq'
/** @ingroup Errors
	PICA access error. See \c #SPAccessSuite. */
#define kSPCantReleasePluginError			'!Rel'
/** @ingroup Errors
	PICA access error. See \c #SPAccessSuite. */
#define kSPPluginAlreadyReleasedError		'AlRl'

// SPAdaptsSuite errors
/** @ingroup Errors
	PICA adapter error. See \c #SPAdaptersSuite */
#define kSPAdapterAlreadyExistsError		'AdEx'
/** @ingroup Errors
	PICA adapter error. See \c #SPAdaptersSuite */
#define kSPBadAdapterListIteratorError		'BdAL'

// SPBasicSuite errors
/** @ingroup Errors
	Basic PICA error. See \c #SPBasicSuite */
#define kSPBadParameterError				'Parm'

// Block debugging errors
/** @ingroup Errors
	PICA debugging error. See \c #SPBlockDebugSuite */
#define kSPCantChangeBlockDebugNowError		'!Now'
/** @ingroup Errors
	PICA debugging error. See \c #SPBlockDebugSuite */
#define kSPBlockDebugNotEnabledError		'!Nbl'

// SPBlocks errors
/** @ingroup Errors
	PICA memory management error. See \c #SPBlocksSuite */
#define kSPOutOfMemoryError					-108  /* -108, same as Mac memFullErr */
/** @ingroup Errors
	PICA memory management error. See \c #SPBlocksSuite */
#define kSPBlockSizeOutOfRangeError			'BkRg'

// SPCaches errors
/** @ingroup Errors
	One of two possible responses a plug-in should return when it receives the \c #kSPPluginPurgeCachesSelector.
	See \c #SPCachesSuite */
#define kSPPluginCachesFlushResponse		'pFls'
/** @ingroup Errors
	One of two possible responses a plug-in should return when it receives the \c #kSPPluginPurgeCachesSelector.
	See \c #SPCachesSuite */
#define kSPPluginCouldntFlushResponse		kSPNoError;

// SPFiles errors
/** @ingroup Errors
	PICA file-access error. See \c #SPFilesSuite */
#define kSPTroubleAddingFilesError			'TAdd'
/** @ingroup Errors
	PICA file-access error. See \c #SPFilesSuite */
#define kSPBadFileListIteratorError			'BFIt'

// SPHost errors
/** @ingroup Errors
	PICA plug-in start-up error.  */
#define kSPTroubleInitializingError			'TIni'	// Some non-descript problem encountered while starting up.
/** @ingroup Errors
	PICA plug-in start-up error.  */
#define kHostCanceledStartupPluginsError 	'H!St'

// SPInterface errors
/** @ingroup Errors
	PICA interface error. See \c #SPInterfaceSuite */
#define kSPNotASweetPeaPluginError			'NSPP'
/** @ingroup Errors
	PICA interface error. See \c #SPInterfaceSuite */
#define kSPAlreadyInSPCallerError			'AISC'

// SPPlugins errors
/** @ingroup Errors
	PICA plug-in error. See \c #SPPluginsSuite */
#define kSPUnknownAdapterError				'?Adp'
/** @ingroup Errors
	PICA plug-in error. See \c #SPPluginsSuite */
#define kSPBadPluginListIteratorError		'PiLI'
/** @ingroup Errors
	PICA plug-in error. See \c #SPPluginsSuite */
#define kSPBadPluginHost					'PiH0'
/** @ingroup Errors
	PICA plug-in error. See \c #SPPluginsSuite */
#define kSPCantAddHostPluginError			'AdHo'
/** @ingroup Errors
	PICA plug-in error. See \c #SPPluginsSuite */
#define kSPPluginNotFound					'P!Fd'

// SPProperties errors
/** @ingroup Errors
	PICA properties error. See \c #SPPropertiesSuite */
#define kSPCorruptPiPLError					'CPPL'
/** @ingroup Errors
	PICA properties error. See \c #SPPropertiesSuite */
#define kSPBadPropertyListIteratorError		'BPrI'

// SPSuites errors
/** @ingroup Errors
	PICA suite access error. See \c #SPSuitesSuite */
#define kSPSuiteNotFoundError				'S!Fd'
/** @ingroup Errors
	PICA suite access error. See \c #SPSuitesSuite */
#define kSPSuiteAlreadyExistsError			'SExi'
/** @ingroup Errors
	PICA suite access error. See \c #SPSuitesSuite */
#define kSPSuiteAlreadyReleasedError		'SRel'
/** @ingroup Errors
	PICA suite access error. See \c #SPSuitesSuite */
#define kSPBadSuiteListIteratorError		'SLIt'
/** @ingroup Errors
	PICA suite access error. See \c #SPSuitesSuite */
#define kSPBadSuiteInternalVersionError		'SIVs'
