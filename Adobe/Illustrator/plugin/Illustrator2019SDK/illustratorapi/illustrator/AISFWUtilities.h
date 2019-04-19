#ifndef __AISFWUTILITIES__
#define __AISFWUTILITIES__

/*
 *        Name:	AISFWUtilities.h
 *     Purpose:	Adobe Illustrator Save For Web Utilities Suite
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
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

#ifndef __AITypes__
#include "AITypes.h"
#endif
#ifndef __AIDataFilter__
#include "AIDataFilter.h"
#endif
#ifndef __AIFileFormat__
#include "AIFileFormat.h"
#endif


#include "AIHeaderBegin.h"

/** @file AISFWUtilities.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAISFWUtilitiesSuite			"AI SFW Utilities Suite"
#define kAISFWUtilitiesSuiteVersion4	AIAPI_VERSION(4)

/* Latest version */
#define kAISFWUtilitiesSuiteVersion		kAISFWUtilitiesSuiteVersion4
#define kAISFWUtilitiesVersion			kAISFWUtilitiesSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides access to save-for-Web features.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISFWUtilitiesSuite and \c #kAISFWUtilitiesSuiteVersion.
 */
typedef struct {

	/** Retrieves the location of the file in which application Save-For-Web
		settings are saved.
			@param outFileSpec [out] A buffer in which to return the file
				specification.
		*/
	AIAPI AIErr (*GetSaveSettingsDirectory)	(ai::FilePath &outFileSpec);

	/** Displays the Slice Options dialog, which allows the user
		to set the options for an image slice. This is the dialog shown
		when you create a slice in the document (draw an object, choose Object>Slice>Make),
		select it, and choose Object>Slice>Slice Options. Modifiable options
		in this dialog include slice type, name, URL, target, message, alternate
		text, and background color.
			@param inSliceID The unique slice identifier.
		*/
	AIAPI AIErr (*ShowSliceOptions)	(ai::int32 inSliceID);

} AISFWUtilitiesSuite;


#include "AIHeaderEnd.h"


#endif

