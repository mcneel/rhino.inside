/*
*        Name:	AIPSDKeys.h
*     Purpose:	Adobe Illustrator PSD Options Dictionary Keys.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2014 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

#pragma once

/*******************************************************************************
**
**	Imports
**
**/

#include "AIHeaderBegin.h"


/*******************************************************************************
**
**	Constants
**
**/

/*	Use with \c #AIDicionarySuite::SetPSDPluginColorModeEntry in Integeral form.
	Enum given in AIPhotoshopPrefs.h*/
#define		kAIPSDColorModelOption           "PSDColorModel"

/*	Use with \c #AIDicionarySuite::SetRealEntry. */
#define		kAIPSDResolutionOption           "PSDResolution"

/*	Use with \c #AIDicionarySuite::SetBooleanEntry. */
#define		kAIPSDWriteLayersOption          "PSDWriteLayers"

/*	Use with \c #AIDicionarySuite::SetAntiAliasOptionsEntry in integral form.
	Enum given in AIPhotoshopPrefs.h*/
#define     kAIPSDAntiAliasOption			  "PSDAntiAlias"

/*	Use with \c #AIDicionarySuite::SetBooleanEntry. */
#define     kAIPSDMaxEditabilityOption		   "PSDMaxEditability"

/*	Use with \c #AIDicionarySuite::SetBooleanEntry. */
#define     kAIPSDPreserveSpotColorsOption		   "PSDPreserveSpotColors"



#include "AIHeaderEnd.h"


