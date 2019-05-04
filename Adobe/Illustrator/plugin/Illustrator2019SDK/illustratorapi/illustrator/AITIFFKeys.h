/*
*        Name:	AITIFFKeys.h
*     Purpose:	Adobe Illustrator TIFF Options Dictionary Keys.
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


/*******************************************************************************
**
**	Imports
**
**/

#pragma once

#include "AIHeaderBegin.h"


enum AIAntialiasType:ai::uint8
{
	kAIAntialiasNone = 1,
	kAIAntialiasArtOptimized,
	kAIAntialiasTypeOptimized
};
/*******************************************************************************
**
**	Constants
**
**/

/*	Use with \c #AIDicionarySuite::SetIntegerEntry. */
#define		kAITIFFColorModelOption           "TIFFColorModel"

/*	Use with \c #AIDicionarySuite::SetBooleanEntry. */
#define		kAITIFFLZWCompressionOption      "TIFFLZWCompression"

/*	Use with \c #AIDicionarySuite::SetIntegerEntry with reference to enum AIAntialiasType. */
#define     kAITIFFAntiAliasOption		   "TIFFAntiAlias"


#include "AIHeaderEnd.h"

