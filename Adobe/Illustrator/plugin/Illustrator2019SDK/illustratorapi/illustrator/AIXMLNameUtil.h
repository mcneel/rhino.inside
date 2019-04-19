#ifndef __AIXMLNameUtil__
#define __AIXMLNameUtil__

/*
 *        Name:	AIXMLNameUtil.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator XML Name Utilities Suite.
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


#include "AIHeaderBegin.h"

/** @file AIXMLNameUtil.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIXMLNameUtilSuite						"AI XML Name Utilities Suite"
#define kAIXMLNameUtilSuiteVersion4				AIAPI_VERSION(4)
#define kAIXMLNameUtilSuiteVersion				kAIXMLNameUtilSuiteVersion4
#define kAIXMLNameUtilVersion					kAIXMLNameUtilSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite allows you to create and manipulate XML names, and
	convert them to and from strings. An XML name must conform to a
	specific syntax; for example, it cannot contain the space character and
	must start with a letter.
	See http://www.w3.org/TR/REC-xml#NT-Name for the XML name syntax.

	Illustrator uses these functions to convert between art object
	names and unique identifiers; see the \c #AIUIDUtilsSuite.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIXMLNameUtilSuite and \c #kAIXMLNameUtilVersion.
*/
typedef struct AIXMLNameUtilSuite {

	/** Constructs an XML name from a base name, appending a number
		to make the name unique.
			@param base The base name string.
			@param buffer [out] A Unicode string in which to return the XML name.
			@param number The number.
			@param maxlength The maximum number of characters in the constructed name.
	*/
	AIAPI AIErr (*NameFromBaseAndNumber) (const ai::UnicodeString& base, ai::UnicodeString& buffer, ai::int32 number, ai::int32 maxlength);

	/** Retrieves the base name from an XML name, stripping off any number
		that was appended to make the name unique.
			@param name	The XML name.
			@param buffer [out] A Unicode string in which to return the base name.
		*/
	AIAPI AIErr (*BaseFromName) (const ai::UnicodeString& name, ai::UnicodeString& buffer);

	/** Reports whether a string contains a valid XML name.
		(Note that this function returns a boolean value, not an error code.)
			@param name The Unicode string.
			@return True if the string contains a valid XML name.
		*/
	AIAPI AIBoolean (*IsValidName) (const ai::UnicodeString& name);

	/** Constructs a valid XML name from any Unicode string, by replacing spaces with
		underscores and other illegal characters with a character sequence that
		identifies their hexadecimal equivalent. For example, "99 red balloons"
		becomes "_x39_9_red_balloons", because the first character of an XML name
		cannot be a number.
			@param name The Unicode string.
			@param buffer [out] A Unicode string in which to return the XML name.
		*/
	AIAPI AIErr (*XMLNameFromString) (const ai::UnicodeString& str, ai::UnicodeString& buffer);

	/** Restores a valid XML name to the Unicode string from which it was created using
		\c #XMLNameFromString().
			@param name The XML name.
			@param buffer [out] A buffer in which to return the converted string.
		*/
	AIAPI AIErr (*StringFromXMLName) (const ai::UnicodeString& name, ai::UnicodeString& buffer);

} AIXMLNameUtilSuite;


#include "AIHeaderEnd.h"


#endif
