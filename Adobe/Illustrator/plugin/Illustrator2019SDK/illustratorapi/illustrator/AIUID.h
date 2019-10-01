#ifndef __AIUID__
#define __AIUID__

/*
 *        Name:	AIUID.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Unique ID Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2007 Adobe Systems Incorporated.
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

#ifndef __AIEntry__
#include "AIEntry.h"
#endif

#include "IAIUnicodeString.h"


#include "AIHeaderBegin.h"

/** @file AIUID.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIUIDPoolSuite							"AI UID Pool Suite"
#define kAIUIDPoolSuiteVersion7					AIAPI_VERSION(7)
#define kAIUIDPoolSuiteVersion					kAIUIDPoolSuiteVersion7
#define kAIUIDPoolVersion						kAIUIDPoolSuiteVersion

#define kAIUIDSuite								"AI UID Suite"
#define kAIUIDSuiteVersion8						AIAPI_VERSION(8)
#define kAIUIDSuiteVersion						kAIUIDSuiteVersion8
#define kAIUIDVersion							kAIUIDSuiteVersion

#define kAIUIDREFSuite							"AI UIDREF Suite"
#define kAIUIDREFSuiteVersion8					AIAPI_VERSION(8)
#define kAIUIDREFSuiteVersion					kAIUIDREFSuiteVersion8
#define kAIUIDREFVersion						kAIUIDREFSuiteVersion

#define kAIUIDUtilsSuite						"AI UID Utils Suite"
#define kAIUIDUtilsSuiteVersion9				AIAPI_VERSION(9)
#define kAIUIDUtilsSuiteVersion					kAIUIDUtilsSuiteVersion9
#define kAIUIDUtilsVersion						kAIUIDUtilsSuiteVersion


/** @ingroup Errors
	A UID name is specified with an invalid syntax. See \c #AIUIDSuite. */
#define kUIDBadSyntax				'UIDx'
/** @ingroup Errors
	The name specified is already in use by another UID. See \c #AIUIDSuite. */
#define kUIDNotUnique				'UIDu'
/** @ingroup Errors
	UID is not found. See \c #AIUIDSuite. */
#define kUIDNotFound				'UID!'


/**	@ingroup Notifiers
	Sent when the XML name pool has changed.
	Any UIDs or references associated with that name will now
	have a different name. See \c #AINamePoolRef.  */
#define kAIXMLNameChangedNotifier				"AI XML Name Changed Notifier"


/*******************************************************************************
 **
 **	Types
 **
 **/

/**
	A pool of unique names that can be associated with objects such
	as identifiers. Each document has its own set of name pools.
	A name pool can impose syntactic constraints on the contained names.
	@see \c #AIUIDSuite, \c #AIUIDPoolSuite
*/
typedef struct _t_AINamePool *AINamePoolRef;


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	These functions allow you to create, query, and	manage
	name pools. An identifier (UID) is unique within a given pool, and
	has a name which is also unique within that pool; see \c #AINamePoolRef.
	Each UID can be stored in only one container, and only once within that container.

	@see \c #AIUIDSuite, \c #AIUIDREFSuite, \c #AIUIDUtilsSuite

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIUIDPoolSuite and \c #kAIUIDPoolVersion.
 */

typedef struct AIUIDPoolSuite {

	/** Increments the reference count for a UID name pool.
		When you create a pool, the initial count is 1.
		Use \c #Release() to decrement the count.
		(Note that this function returns a numeric value, not an error code.)
			@param pool The UID name pool reference.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*AddRef) ( void* pool );

	/** Decrements the reference count for a UID name pool, and
		frees the memory when the reference count is 0.
		When you create a pool, the initial count is 1.
		Use \c #AddRef() to increment the count.
		(Note that this function returns a numeric value, not an error code.)
			@param pool The UID name pool reference.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) ( void* pool );

	/** Retrieves a UID name pool by its name. Currently there is only one
		pool, for XML unique ID names. This pool is returned regardless
		of the name supplied.
			@param name Ignored.
			@param pool [out] A buffer in which to return the pool reference.
		*/
	AIAPI AIErr (*GetPool) ( const char* name, AINamePoolRef* pool );

	/** Creates a new unique identifier with a name from the name pool. The new
		UID has an initial reference count of 1.
			@param pool The UID name pool.
			@param name Optional. A name that conforms to the syntax
				imposed by the pool, and that is not currently in use.
				If not specified, the function creates a unique name.
			@param uid [out] A buffer in which to return the UID object.
		*/
	AIAPI AIErr (*NewUID) ( AINamePoolRef pool, const ai::UnicodeString& name, AIUIDRef* uid );

	/** Retrieves the UIDRef from its name.
	@param pool The UID name pool.
	@param name The UID name.
	@param uid [out] A buffer in which to return the UID object,
	or \c NULL if there is none.
	*/
	AIAPI AIErr(*GetUID) (AINamePoolRef pool, const ai::UnicodeString& name, AIUIDRef* uid);

	/** Creates a new reference to a unique identifier with a name from the name pool.
		The new UID reference has an initial reference count of 1.
			@param pool The UID name pool.
			@param name Optional.  A name that conforms to the syntax
				imposed by the pool, and that is not currently in use.
				If not specified, the function creates a unique name.
			@param uidref [out] A buffer in which to return the UID reference object.
	  */
	AIAPI AIErr (*NewUIDREF) ( AINamePoolRef pool, const ai::UnicodeString& name, AIUIDREFRef* uidref );

	/** Creates a new unique identifier with a unique name generated from a base name.
			@param pool The UID name pool.
			@param name Optional. A base name that conforms to the syntax
				imposed by the pool. If not specified, or if in use, the function
				creates a unique name.
			@param uid [out] A buffer in which to return the UID object.
		*/
	AIAPI AIErr (*NewUIDFromBase) ( AINamePoolRef pool, const ai::UnicodeString& base, AIUIDRef* uid );

} AIUIDPoolSuite;


/**	@ingroup Suites
	This suite allows you to access and manage unique identifiers.
	A unique identifier (UID) is an object that can be stored in
	a dictionary or an array. A unique identifier cannot occur
   	in more than one container, or more than once in a container.

	Given a unique ID, you can find its container. For example,
	unique IDs are typically found in the dictionary of an art object.
	Given such an ID, you can  access the associated art object.
	An art object name is itself stored as a specially encoded
	unique ID in the associated art object dictionary.

	@see \c #AIUIDPoolSuite, \c #AIUIDREFSuite, \c #AIUIDUtilsSuite

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIUIDSuite and \c #kAIUIDVersion.
*/
typedef struct AIUIDSuite {

	/** Increments the reference count for a unique identifier.
		When you create a UID, the initial count is 1.
		Use \c #Release() to decrement the count.
		(Note that this function returns a numeric value, not an error code.)
			@param uid The UID object.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*AddRef) ( void* uid );

	/** Decrements the reference count for a unique identifier, and
		frees the memory when the reference count is 0.
		When you create a UID, the initial count is 1.
		Use \c #AddRef() to increment the count.
		(Note that this function returns a numeric value, not an error code.)
			@param uid The UID object.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) ( void* uid );

	/** Reports whether a unique identifier is currently stored within
		some container.	A UID cannot occur in more than one
   		container, or more than once in a container.
		(Note that this function returns a boolean value, not an error code.)
			@param uid The UID object.
			@return True if the UID is contained in a dictionary or array.
		*/
	AIAPI AIBoolean (*IsInUse) ( AIUIDRef uid );

	/** Retrieves the UID name pool to which a unique identifier's name belongs.
		(Note that this function does not return an error code.)
			@param uid The UID object.
			@param pool [out] A buffer in which to return the UID name pool, or
				\c NULL	if the UID is not valid.
		*/
	AIAPI void (*GetPool) ( AIUIDRef uid, AINamePoolRef* pool );

	/** Retrieves the name of a unique identifier as a Unicode string.
			@param uid The UID object.
			@param name [out] A buffer in which to return the name.
	 	*/
	AIAPI AIErr (*GetName) ( AIUIDRef uid, ai::UnicodeString& name );

	/** Retrieves the dictionary or array that contains	a unique identifier.
		(Note that this function returns an object value, not an error code.)
			@param uid The UID object.
			@return The entry object, or a \c NULL reference if the UID is
				not stored in a container.
			@see \c #AIEntrySuite
		*/
	AIAPI AIEntryRef (*GetContainer) ( AIUIDRef uid );

	/** Creates a new reference to a unique identifier.
		The new UID reference has an initial reference count of 1.
			@param uid The UID object.
			@param ruidref [out] A buffer in which to return the UID reference object.
	*/
	AIAPI AIErr (*NewUIDREF) ( AIUIDRef uid, AIUIDREFRef* ruidref );

} AIUIDSuite;


/** @ingroup Suites
	This suite allows you to access and manage references to unique identifiers.
	The \c #AIEntrySuite provides methods to convert between \c #AIEntryRef
    and \c #AIUIDRef.

	Use a UID to tag an object with a unique identifier, then use a UID reference
	to make a reference to that object. For example, if your plug-in creates art
	objects and you want to attach a unique identifier to an object, first create
	a UID and put it in the art object’s dictionary. You can then store
	a reference to the object in the document dictionary using an \c #AIUIDRef.

	@see \c #AIUIDPoolSuite, \c #AIUIDSuite, \c #AIUIDUtilsSuite

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIUIDREFSuite and \c #kAIUIDREFVersion.
*/
typedef struct AIUIDREFSuite {

	/** Increments the reference count for a UID reference.
		When you create an \c #AIUIDRef, the initial count is 1.
		Use \c #Release() to decrement the count.
		(Note that this function returns a numeric value, not an error code.)
			@param uidref The UID reference object.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*AddRef) ( void* uidref );

	/** Decrements the reference count for a UID reference, and
		frees the memory when the reference count is 0.
		When you create an \c #AIUIDRef, the initial count is 1.
		Use \c #AddRef() to increment the count.
		(Note that this function returns a numeric value, not an error code.)
			@param uidref The UID reference object.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) ( void* uidref );

	/** Reports whether a UID reference is currently stored within some container.
		A UID cannot occur in more than one container, or more than once in a container.
		(Note that this function returns a boolean value, not an error code.)
			@param uidref The UID reference object.
			@return True if the UID reference is contained in a dictionary or array.
	*/
	AIAPI AIBoolean (*IsInUse) ( AIUIDREFRef uidref );

	/** Retrieves the UID name pool to which a UID reference's name belongs.
		(Note that this function does not return an error code.)
			@param uidref The UID reference object.
			@param pool [out] A buffer in which to return the UID name pool, or
				\c NULL	if the UID reference is not valid.
		*/
	AIAPI void (*GetPool) ( AIUIDREFRef uidref, AINamePoolRef* pool );

	/** Retrieves the name of a UID reference as a Unicode string
			@param uidref The UID reference object.
			@param name [out] A buffer in which to return the name.
		*/
	AIAPI AIErr (*GetName) ( AIUIDREFRef uidref, ai::UnicodeString& name );

	/**  Retrieves the dictionary or array that contains a UID reference.
		(Note that this function returns an object value, not an error code.)
			@param uidref The UID reference object.
			@return The entry object, or a \c NULL reference if the UID reference
				is not stored in a container.
			@see \c #AIEntrySuite
		*/
	AIAPI AIEntryRef (*GetContainer) ( AIUIDREFRef uidref );

	/** Retrieves the unique identifier referred to by a  UID reference.
		(Note that this function does not return an error code.)
			@param uidref The UID reference object.
			@param uid [out] A buffer in which to return the UID object,
				or \c NULL if there is none.
		*/
	AIAPI void (*GetUID) ( AIUIDREFRef uidref, AIUIDRef* uid );

} AIUIDREFSuite;


/** @ingroup Suites
	This suite allows you to query and manage the unique identifiers for art objects.
	@see \c #AIUIDPoolSuite, \c #AIUIDSuite, \c #AIUIDREFSuite

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIUIDUtilsSuite and \c #kAIUIDUtilsVersion.
*/
typedef struct AIUIDUtilsSuite {

	/** Retrieves the unique identifier for an art object.
			@param art The art object.
			@param create True to assign a generated UID if the object has
				none.
			@param uid [out] A buffer in which to return the found UID object,
				or a generated UID if none is found and \c create is true.
		*/
	AIAPI AIErr (*GetArtUID) ( AIArtHandle art, AIBoolean create, AIUIDRef* uid );

	/** Sets the unique identifier of an art object, replacing its current UID, if any.
			@param art The art object.
			@param uid The new UID object,
	*/
	AIAPI AIErr (*SetArtUID) ( AIArtHandle art, AIUIDRef uid );

	/** Transfers the unique identifier of an art object to another art object,
		setting the UID	of the source art to \c NULL.
			@param srcart The source art object.
			@param dstart The destination art object.
		*/
	AIAPI AIErr (*TransferArtUID) ( AIArtHandle srcart, AIArtHandle dstart );

	/** Retrieves the UID reference for an art object, or assigns a new UID
		and creates the reference if needed.
			@param art The art object.
			@param uidref [out] A buffer in which to return the UID reference object.
		*/
	AIAPI AIErr (*NewArtUIDREF) ( AIArtHandle art, AIUIDREFRef* uidref );

	/** Retrieves the art object referenced by a UID reference.
		If the UID reference is associated with a text story (a sequence of
		linked text frames), retrieves the first frame of the story.
			@param uidref The UID reference object,
			@param art [out] A buffer in which to return the art object.
		*/
	AIAPI AIErr (*GetReferencedArt) ( AIUIDREFRef uidref, AIArtHandle* art );

	/** Retrieves the UID name of an art object.
			@param art The art object.
			@param name [out] A buffer in which to return the name string, or
				the empty string if no UID is assigned.
		*/
	AIAPI AIErr (*GetArtUIDName) ( AIArtHandle art, ai::UnicodeString& name );

	/** Sets the UID name of an art object.
			@param art The art object.
			@param name The new name string.
			@return The \c #kUIDNotUnique error if the named UID is already in use.
		*/
	AIAPI AIErr (*SetArtUIDName) ( AIArtHandle art, const ai::UnicodeString& name );

	/** Retrieves the name or XML identifier of an art object, depending on the setting of
		the user preference "Identify Object by: Object Name/XML ID".
		If the preference allows a user to enter arbitrary names,
		they are internally translated to valid, unique, XML IDs. This
		function translates back to the name that was entered.
			@param art The art object.
			@param name [out] A buffer in which to return the name string.
			@param isDefaultName [out] A buffer in which to return the output as true if the
				art object has no name or UID, and the returned string is the default name.
		*/
	AIAPI AIErr (*GetArtNameOrUID) ( AIArtHandle art, ai::UnicodeString& name, ASBoolean* isDefaultName );

	/** Sets the name or XML identifier of an art object, depending on the setting of
		the user preference "Identify Object by: Object Name/XML ID".
			@param art The art object.
			@param name The newly named string. If the preference allows a user
				to enter arbitrary names, this can be any string, which is
				translated internally to a valid, unique, XML ID. Otherwise, it
				must conform to XML ID syntax.

		*/
	AIAPI AIErr (*SetArtNameOrUID) ( AIArtHandle art, const ai::UnicodeString& name );

	/** Creates a new UID reference based on an existing UID reference, by appending
		a numeric suffix to make the name unique.
			@param base The base UID reference object.
			@param uid  [out] A buffer in which to return the new UID reference.
		*/
	AIAPI AIErr (*MakeUIDFromBase) ( AIUIDRef base, AIUIDRef* uid );

	/** Creates a new name from a base name, by appending a numeric suffix to
		make the name unique.
			@param base The base name string.
			@param name [out] A buffer in which to return the new name string.
		*/
	AIAPI AIErr (*MakeUniqueNameFromBase) ( const ai::UnicodeString& base, ai::UnicodeString& name );

	/** Retrieves the UID reference for the story associated with an art object.
			@param art The art object, of type \c #AIArtType::kTextFrameArt.
			@param create True to generate and assign a new UID if the story has none.
			@param ruid	[out] A buffer in which to return the UID reference object.
		 */
	AIAPI AIErr (*GetStoryUID) (AIArtHandle art, AIBoolean create, AIUIDRef* ruid);

	/** Sets the UID reference for the story associated with an art object.
			@param art The art object, of type \c #AIArtType::kTextFrameArt.
			@param ruid	The new UID reference object.
		 */
	AIAPI AIErr (*SetStoryUID) ( AIArtHandle art, AIUIDRef uid );

	/** Transfers the unique identifier from the story associated with a text art object
		to the story of another text art object. The UID of the source story is set to \c NULL.
			@param srcart The source art object, of type \c #AIArtType::kTextFrameArt.
			@param dstart The destination art object, of type \c #AIArtType::kTextFrameArt.
		*/
	AIAPI AIErr (*TransferStoryUID) ( AIArtHandle srcart, AIArtHandle dstart );

	/** Creates a new UID reference for the story associated with an art object.
		Pass this reference to \c #GetReferencedArt() to retrieve the first
		frame of the story (regardless of which frame was used to create the
		reference).
			@param art The art object, of type \c #AIArtType::kTextFrameArt.
			@param ruid	The new UID reference object.
		*/
	AIAPI AIErr (*NewStoryUIDREF) ( AIArtHandle art, AIUIDREFRef* uidref );

	/** Transfers the unique identifier from the story associated with a text art object
		to another art object of any type. The UID of the source story is set to \c NULL.
			@param frame The source art object, of type \c #AIArtType::kTextFrameArt.
			@param art The destination art object, of any type.
 		*/
	AIAPI AIErr (*TransferStoryUIDToArt) ( AIArtHandle frame, AIArtHandle art );

	/** Transfers the unique identifier from an art object of any type to the story associated
		with a text art object. The UID of the source art object is set to \c NULL.
			@param art The source art object, of any type.
			@param frame The destination art object, of type \c #AIArtType::kTextFrameArt.
		*/
	AIAPI AIErr (*TransferArtUIDToStory) ( AIArtHandle art, AIArtHandle frame );

	/* Introduced in AI 12 */

	/** Retrieves the source object from which an object being dragged and transformed was derived.
			@param target The unique identifier (UID) for the object being dragged.
			@param equiv [out] A buffer in which to return the UID of the source object for
				the transformation, if found.
			@return \c #kUIDNotFound error if the source object UID is not found in the current context.
		*/
	AIAPI AIErr (*FindEquivUID) ( AIUIDRef target, AIUIDRef& equiv );


} AIUIDUtilsSuite;

#include "AIHeaderEnd.h"


#endif
