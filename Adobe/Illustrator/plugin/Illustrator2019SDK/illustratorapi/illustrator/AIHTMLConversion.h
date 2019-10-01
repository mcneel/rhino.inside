#ifndef __AIHTMLCONVERSION__
#define __AIHTMLCONVERSION__

/*
*        Name:	AIHTMLConversion.h
*   $Revision: 1 $
*      Author:
*        Date:
*     Purpose:	Adobe Illustrator HTML Conversion Suite.
*
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
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

#ifndef __SPSuites__
#include "SPSuites.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIHTMLConversion.h */

/*******************************************************************************
**
**	Constants
**
**/

#define kAIHTMLConversionSuite						"AI HTML Art Conversion Suite"
#define kAIHTMLConversionSuiteVersion2				1002
#define kAIHTMLConversionSuiteVersion				kAIHTMLConversionSuiteVersion2
#define kAIHTMLConversionInternalSuiteVersion2		2
#define kAIHTMLConversionInternalSuiteVersion		kAIHTMLConversionInternalSuiteVersion2

#define kAIHTMLConversionSuitesSuite				"AI HTML Art Conversion Suites Suites"
#define kAIHTMLConversionSuitesSuiteVersion2		1002
#define kAIHTMLConversionSuitesSuiteVersion			kAIHTMLConversionSuitesSuiteVersion2



/*******************************************************************************
**
**	Definitions
**
**/

/** @ingroup Errors
	See \c #AIHTMLConversionSuite   */
#define kAIHTMLUnsupportedTypeError			'HT!T'
/** @ingroup Errors
	See \c #AIHTMLConversionSuite 	 */
#define kAIHTMLHBufferOverflowError			'HTBO'

/** Bit flags for options that control how conversion is performed by
\c #AIHTMLConversionSuite::GetArtAsHTMLText().
The first bit is for all convertible types. Other options can be defined
by an individual converter, which would also define a UI and rules for
setting those options.
*/
enum AIHTMLConversionOptions {
	/** Clear all option flags */
	kAIHTMLNoOptions					= 0,
	/** Set the dynamic link between a slice and its AI art.
	See \c #AISlicingSuite::GetSliceAsHTMLText() */
	kAIHTMLTextLinkTextOption			= (1<<0)
	};

/*******************************************************************************
**
**	Suite
**
**/

/** @ingroup Suites
This suite is not, by default, provided by Illustrator.
If your plug-in provides this suite, it should use the \c #AIHTMLConversionSuite
to convert art to an HTML text flow, mapping styles as needed, then
add that suite using \c #AIHTMLConversionSuitesSuite::AddHTMLConversionSuite().


A default converter for text is part of the \c #AISlicingSuite.
That suite uses these functions to get the best possible HTML
representation of a sliced text object, which in turn allows
Save for Web to export Illustrator text as HTML text.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIHTMLConversionSuite and \c #kAIHTMLConversionSuiteVersion.
*/
typedef struct
	{
	/** Reports whether art can be converted with specified options.
		Usage of options and conversion behavior is specific to the converter.
		(Note that this function returns a Boolean value, not an error code.)
	@param art An art object or root of an art tree.
			@param options The conversion options, a logical OR of \c #AIHTMLConversionOptions
				bit flags, as defined for this converter..
	*/
		AIAPI AIBoolean (*ArtCanBeConverted)(AIArtHandle art, ai::int16 artType, ai::int32 options);

	/** Converts the text runs in a text art object into appropriate HTML
		expressions in a stream. Usage of options and conversion behavior
		is specific to the converter.
	@param art The text art object.
			@param options The conversion options, a logical OR of \c #AIHTMLConversionOptions
				bit flags, as defined for this converter.
	@return The error \c #kAIHTMLUnsupportedTypeError if the art cannot be converted to HTML
	because there is no translator. <br>
	The error \c #kAIHTMLHBufferOverflowError if there is more text than the buffer can hold.
	*/
	AIAPI AIErr (*GetArtAsHTMLText)(AIArtHandle art, ai::int32 options, AIDataFilter *stream);

	/** Retrieves information from the provider of this HTML conversion suite. Not typically needed.
		The provider can return a name that represents the converter, or additional information based
		on what is passed in.
	@param converterName [in, out] A buffer in which to specify and  return the converter name.
	@param otherInfo [in, out] A buffer in which to specify and return additional 
				information, as defined by this converter.
	*/
	AIAPI AIErr (*GetConverterInfo)(char **converterName, void *otherInfo);

	} AIHTMLConversionSuite;


/** @ingroup Suites
This suite allows you to register an HTML conversion suite, implemented as \c #AIHTMLConversionSuite
@see \c #SPSuitesSuite

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIHTMLConversionSuitesSuite and \c #kAIHTMLConversionSuitesSuiteVersion.
*/
typedef struct
	{
	/** Retrieves a unique internal plug-in interface version number,
	to use when adding a suite with \c #AddHTMLConversionSuite().
	@param apiVersion The external plug-in version; use the constant \c #kPluginInterfaceVersion.
	@param internalVersion [out] A buffer in which to return the unique internal
	version number.
	*/
	SPAPI SPErr (*GetNextInternalVersion)(ai::int32 apiVersion, ai::int32 *internalVersion);

	/** Adds an HTML conversion suite.
	@param host This plug-in.
	@param apiVersion The external plug-in version; use the constant
	\c #kPluginInterfaceVersion.
	@param internalVersion An internal plug-in version number, as returned by
	\c #GetNextInternalVersion().
			@param suiteProcs A pointer to an \c #AIHTMLConversionSuite structure which contains
	the procedures that perform the HTML conversion.
	@param suite [out] A buffer in which to return the new suite.
	*/
	SPAPI SPErr (*AddHTMLConversionSuite)(SPPluginRef host,
		ai::int32 apiVersion, ai::int32 internalVersion,
		const void *suiteProcs, SPSuiteRef *suite);

	/** Retrieves a list of all registered HTML conversion suites, which
	you can use with \c #SPSuitesSuite functions.
	@param suiteList [out] A buffer in which to return the suite list.
	*/
	SPAPI SPErr (*GetHTMLConversionSuiteList)(SPSuiteListRef *suiteList);

	} AIHTMLConversionSuitesSuite;


#include "AIHeaderEnd.h"


#endif
