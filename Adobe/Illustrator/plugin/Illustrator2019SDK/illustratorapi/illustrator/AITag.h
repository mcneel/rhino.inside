#ifndef __AITag__
#define __AITag__

/*
 *        Name:	AITag.h
 *   $Revision: 4 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Tag Suite.
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


#include "AIHeaderBegin.h"

/** @file AITag.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAITagSuite			"AI Tag Suite"
#define kAITagSuiteVersion		AIAPI_VERSION(4)
#define kAITagVersion			kAITagSuiteVersion

/** @ingroup Notifiers
	See \c #AITagSuite */
#define kAITagChangedNotifier	"AI Tag Changed Notifier"

/** @ingroup Errors
	See \c #AITagSuite */
#define kBadTagTypeErr		'TGTY'
/** @ingroup Errors
	See \c #AITagSuite */
#define kBadTagNameErr		'TGNM'
/** @ingroup Errors
	See \c #AITagSuite */
#define kBadTagDataErr		'TGDT'
/** @ingroup Errors
	See \c #AITagSuite */
#define kTagNotFoundErr		'TGNF'


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Tags allow you to assign arbitrary data to Illustrator artwork
	objects. This suite is generally deprecated in favor of the more powerful
	facilities provided by the \c #AIDictionarySuite. Tags are actually stored
	as string entries in the art object dictionary. Use \c #AIArtSuite::GetDictionary()
	to get the art object dictionary.

	A tag is data attached to an artwork object, containing a descriptive name,
	a tag type, a change count, and the tag data itself.

		\li A tag name can contain up to 30 characters (alphanumeric characters and
			'_'). Illustrator does not check for duplicate names, so you should make sure
			you choose unique tag names. Do not use spaces in tag names.
		\li The only tag type supported by Illustrator is "string", which represents
			a null-terminated C string up to 200 characters.
		\li Each time an artwork tag is changed, Illustrator increments
			the change count.

	The \c #kAITagChangedNotifier is associated with the tag suite.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITagSuite and \c #kAITagVersion.
 */
typedef struct AITagSuite {

	/** Associates a tag with an art object.
			@param object The object, an \c #AIArtHandle.
			@param name A unique identifier for the tag.
			@param type The tag type, the literal "string".

			Additional arguments that follow depend on the type of data.
			For string types, pass a pointer to the C string to be associated with the tag.
		*/
	AIErr (*SetTag) ( void *object, const char *name, const char *type, ... );

	/** Retrieves a tag for an object.
			@param object The object, an \c #AIArtHandle.
			@param name The unique identifier for the tag.
			@param type The tag type, the literal "string".

			Additional arguments that follow depend on the type of data.
			For string types, pass a pointer to a char * in which to return
			the string associated with the tag. You do not need to allocate
			space for the tag string; the function returns a pointer to the
			existing string. Do not directly modify the string; use \c #SetTag() instead.
		*/
	AIErr (*GetTag) ( void *object, const char *name, const char *type, ... );

	/** Gets the type of a tag (always "string"), and can be used to determine
		whether a tag of a given name exists.
			@param object The object, an \c #AIArtHandle.
  			@param name The unique identifier for the tag.
  			@param type [out] Optional. A pointer to a pointer in which to return 
  				the address of the tag type string if the tag exists.
  				Call with \c NULL to opt out.
		*/
	AIErr (*GetTagType) ( void *object, const char *name,const char **type );

	/** Retrieves the number of times an object tag has changed.
			@param object The object, an \c #AIArtHandle.
  			@param name The unique identifier for the tag.
  			@param count [out] A buffer in which to return the number of changes.
		*/
	AIErr (*GetTagChangeCount) ( void *object, const char *name, ai::int32 *count );

	/** Frees memory associated with a tag. Do not remove tags that you did not create.
			@param object The object, an \c #AIArtHandle
  			@param name The unique identifier for the tag.
		*/
	AIErr (*RemoveTag) ( void *object, const char *name );

	/** Reports how many tags are associated with an object. Use with \c #GetNthTag()
		to iterate through tags.
			@param object The object, an \c #AIArtHandle.
  			@param count [out] A buffer in which to return the number of tags.
	*/
	AIErr (*CountTags) ( void *object, ai::int32 *count );

	/** Retrieves a tag from an art object by position index. Use with \c #CountTags()
		to iterate through tags.
			@param object The object, an \c #AIArtHandle.
	 		@param n The 0-based position index.
			@param name [out] A buffer in which to return the unique identifier for the tag.
		*/
	AIErr (*GetNthTag) ( void *object, ai::int32 n, char **name );

} AITagSuite;


#include "AIHeaderEnd.h"


#endif
