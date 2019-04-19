/***********************************************************************/
/*                                                                     */
/* SPMData.h                                                           */
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

#ifndef __SPMessageData__
#define __SPMessageData__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "SPTypes.h"
#include "AIBasicTypes.h"

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 **
 ** Types
 **
 **/

/** The value of \c #SPMessageData::SPCheck, if the message data associated
	with a call to a plug-in has come from \c #SPInterfaceSuite::SendMessage(),
	or is prepared using \c #SPInterfaceSuite::SetupMessageData(). */
#define kSPValidSPMessageData 'SPCk'

/** Basic suite-access information provided with every call. */
struct SPMessageData {
#ifdef __cplusplus
	SPMessageData(ai::int32 SPCheck_ = 0, struct SPPlugin *self_ = 0, void *globals_ = 0, struct SPBasicSuite *basic_ = 0)
	:	SPCheck(SPCheck_), self(self_), globals(globals_), basic(basic_) {}
#endif

	/** \c #kSPValidSPMessageData if this is a valid PICA message. */
	ai::int32 SPCheck;
	/** This plug-in, an \c #SPPluginRef. */
	struct SPPlugin *self;
	/** An array of application-wide global variables. */
	void *globals;
	/** A pointer to the basic PICA suite, which you use to obtain all other suites. */
	struct SPBasicSuite *basic;

};


#ifdef __cplusplus
}
#endif

#include "SPHeaderEnd.h"

#endif
