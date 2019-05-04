#ifndef __AIArray__
#define __AIArray__

/*
 *        Name:	AIArray.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Array Object Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1999-2007 Adobe Systems Incorporated.
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


#include "AIHeaderBegin.h"

/** @file AIArray.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/


#define kAIArraySuite					"AI Array Suite"
#define kAIArraySuiteVersion6			AIAPI_VERSION(6)
#define kAIArraySuiteVersion			kAIArraySuiteVersion6
#define kAIArrayVersion					kAIArraySuiteVersion


// Array errors.

/*******************************************************************************
 **
 **	Types
 **
 **/


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite defines the array, a heterogeneous container whose elements are
	accessed by sequential integer indices.

	Entries (of type \c AIEntryRef), can be inserted into and removed
	from the array. The AIEntry suite provides methods to construct and
	query entries of different types. See \c apiAIEntry.h.
	Entries can be of simple types such as booleans, integers, floats, and strings
	and complex types such as other arrays, dictionaries and references to document
	objects including art objects, brushes and styles.
	This makes arrays a very flexible and powerful container.

	Arrays can themselves be stored in other containers such as other arrays
	or dictionaries. In particular they can be stored in the dictionaries
	attached to art objects and to the document. When an array is stored in
	one of these places (directly or indirectly) it is read and written as
	a part of the document.

	@see AIEntrySuite, AIDictionarySuite, AIArtSuite

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIArraySuite and \c #kAIArrayVersion.
 */
typedef struct AIArraySuite {

	/** Creates a new array.
		Arrays are reference counted. Initial reference count is 1.
		Use \c #AddRef() to increment the count, and \c #Release() to decrement the count.
			@param array [out] A buffer in which to return the new array reference.
	*/
	AIAPI AIErr (*CreateArray) ( AIArrayRef* array );


	/** Increments the reference count for an array.
		When you create an array, the initial count is 1.
		Use \c #Release() to decrement the count.
		(Note that this function returns a numeric value, not an error code.)
			@param array The array reference.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*AddRef) ( AIArrayRef array );

	/**  Decrements the reference count for an array, and
		 frees the memory when the reference count is 0.
		When you create an array, the initial count is 1.
		Use \c #AddRef() to increment the count.
		(Note that this function returns a numeric value, not an error code.)
			@param array The array reference.
			@return The current reference count.
	*/
	AIAPI ai::int32 (*Release) ( AIArrayRef array );

	/** Makes an exact duplicate of a source array. Performs a deep copy.
			@param src The array reference for the source.
			@param dest [out] buffer in which to return the new array.
	*/
	AIAPI AIErr (*Clone) ( AIArrayRef src, AIArrayRef* dst );
	/** Makes a copy of a source array by replacing the current contents of the destination array.
			@param array The reference for the array to be replaced.
			@param src The array reference for the source.
	*/
	AIAPI AIErr (*Copy) ( AIArrayRef array, AIArrayRef src );

	/** Returns the number of entries in an array.
	The index position of an entry is in the range [0..Size(array) - 1].
	Note this returns a number, not an error code.
		@param array The array reference.
		@return The number of entries in the array.
	*/
	AIAPI ai::int32 (*Size) ( AIArrayRef array );
	/** Removes an entry from an array.
			@param array The array reference.
			@param i The 0-based index position of the entry.
	*/
	AIAPI AIErr (*DeleteEntry) ( AIArrayRef array, ai::int32 i );
	/** Inserts an entry into an array at the given index.
		The new entry is assigned an arbitrary initial value.
			@param array The array reference.
			@param i The 0-based index position of the new entry.
	*/
	AIAPI AIErr (*InsertEntry) ( AIArrayRef array, ai::int32 i );

	/** Gets the data type of an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param type [out] A buffer in which to return the type. See \c apiAIEntry.h.
	*/
	AIAPI AIErr (*GetEntryType) ( AIArrayRef array, ai::int32 i, AIEntryType* type );

	/** Copies an entry from one array to another, or to another position in the same array.
		 	@param array1 The array reference for the source.
		 	@param array2 The array reference for the destination. Can be the same array, or different one.
			@param position1 The 0-based index position of the source entry.
			@param position2 The 0-based index position of the destination entry.

	*/
	AIAPI AIErr (*CopyEntry) ( AIArrayRef array1, AIArrayRef array2, ai::int32 position1,
			ai::int32 position2 );

	/** Moves an entry from one array to another, or to another position in the same array.
			@param array1 The array reference for the source.
			@param array2 The array reference for the destination. Can be the same array, or different one.
			@param position1 The 0-based index position of the source entry.
			@param position2 The 0-based index position of the destination entry.
			@param newposition [out] (Optional) A buffer in which to return the position of
			the entry in \c array2 after the move.
	*/
	AIAPI AIErr (*MoveEntry) ( AIArrayRef array1, AIArrayRef array2, ai::int32 position1,
			ai::int32 position2, ai::int32* newposition );

	/** Swaps two entries in two arrays, or in the same array.
			@param array1 The first array reference.
			@param array2 The second array reference. Can be the same array, or different one.
			@param position1 The 0-based index position of the first entry.
			@param position2 The 0-based index position of the second entry.
	*/
	AIAPI AIErr (*SwapEntries) ( AIArrayRef array1, AIArrayRef array2, ai::int32 position1,
			ai::int32 position2 );

	/** Gets an art-object array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param type [out] A buffer in which to return the entry.
	*/

	AIAPI AIErr (*GetArtEntry) ( AIArrayRef array, ai::int32 i, AIArtHandle* art );
	/** Sets the value of an array entry to be a new art object of the specified type.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param type The type of art object. See \c apiAIArt.h.
	*/

	AIAPI AIErr (*NewArtEntry) ( AIArrayRef array, ai::int32 i, ai::int16 type );

	/** Moves an art object from the artwork tree into an array.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param art The art object. See \c apiAIArt.h.
	*/

	AIAPI AIErr (*MoveArtToEntry) ( AIArrayRef array, ai::int32 i, AIArtHandle art );

	/** Moves an art object to the artwork tree from an array.
		The entry is not deleted from the array, but instead is set to an arbitrary value.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param paintOrder The paint order of the art object in the art tree. See \c apiAIArt.h.
			@param prep The prepositional object for the paint order. See \c apiAIArt.h.
			@param art The art object. See \c apiAIArt.h.
	*/

	AIAPI AIErr (*MoveEntryToArt) ( AIArrayRef array, ai::int32 i, ai::int16 paintOrder,
			AIArtHandle prep, AIArtHandle* art );


	/** Copies an art object from the art tree into an array.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param art The art object. See \c apiAIArt.h.
	*/

	AIAPI AIErr (*CopyArtToEntry) ( AIArrayRef array, ai::int32 i, AIArtHandle art );

	/** Copies an art object from an array into the art tree.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param paintOrder The paint order of the art object in the art tree. See \c apiAIArt.h.
			@param prep The prepositional object for the paint order. See \c apiAIArt.h.
			@param art The art object. See \c apiAIArt.h.
	*/

	AIAPI AIErr (*CopyEntryToArt) ( AIArrayRef array, ai::int32 i, ai::int16 paintOrder,
			AIArtHandle prep, AIArtHandle* art );

	/** Sets an array entry to refer to the topmost group of a layer.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param layer The layer reference.
	*/

	AIAPI AIErr (*SetEntryToLayer) ( AIArrayRef array, ai::int32 i, AILayerHandle layer );

	/** Inserts a new layer in the current document, from a group array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			Must be an art object, of type \c #kGroupArt.
			@param paintOrder The paint order of the art object in the art tree. Valid values are 
			\c #kPlaceDefault, \c #kPlaceAbove, \c #kPlaceBelow, \c #kPlaceAboveAll and \c #kPlaceBelowAll.
			@param prep The prepositional object for the paint order.
			@param layer [out] A buffer in which to return the new layer reference.
	*/

	AIAPI AIErr (*SetLayerToEntry) ( AIArrayRef array, ai::int32 i, ai::int16 paintOrder,
			AILayerHandle prep, AILayerHandle *layer );

	/** Retrieves an array entry by position index.
		(Note this returns an array entry reference, not an error code.)
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@return The array entry, or a null entry if one does not exist.
	*/

	AIAPI AIEntryRef (*Get) ( AIArrayRef array, ai::int32 i );

	/** Adds an array entry at a given position index.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param entry The array entry reference. See \c apiAIEntry.h.
			@see \c #AppendEntry()
	*/

	AIAPI AIErr (*Set) ( AIArrayRef array, ai::int32 i, AIEntryRef entry );


	// the following are convenience APIs for getting and setting entries of the basic types

	/** Retrieves a boolean value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetBooleanEntry) ( AIArrayRef array, ai::int32 i, ASBoolean* value );

	/** Sets a boolean value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value The new value.
	*/
	AIAPI AIErr (*SetBooleanEntry) ( AIArrayRef array, ai::int32 i, AIBoolean value );

	/** Retrieves an integer value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetIntegerEntry) ( AIArrayRef array, ai::int32 i, ai::int32* value );

	/** Sets an integer  value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value The new value.
	*/
	AIAPI AIErr (*SetIntegerEntry) ( AIArrayRef array, ai::int32 i, ai::int32 value );

	/** Retrieves a \c real value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetRealEntry) ( AIArrayRef array, ai::int32 i, AIReal* value );

	/** Sets a \c real value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value The new value.
	*/
	AIAPI AIErr (*SetRealEntry) ( AIArrayRef array, ai::int32 i, AIReal value );

	/** Retrieves a string value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetStringEntry) ( AIArrayRef array, ai::int32 i, const char** value );

	/** Sets a string value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value The new value.
	*/
	AIAPI AIErr (*SetStringEntry) ( AIArrayRef array, ai::int32 i, const char* value );

	/** Retrieves a binary value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
			@param size [out] The number of bytes in \c value.
	*/
	AIAPI AIErr (*GetBinaryEntry) ( AIArrayRef array, ai::int32 i, void* value, ASInt32* size );

	/** Sets a binary value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value A pointer to the new value.
			@param size The number of bytes in \c value.
	*/
	AIAPI AIErr (*SetBinaryEntry) ( AIArrayRef array, ai::int32 i, void* value, ai::int32 size );

	/** Retrieves a dictionary value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetDictEntry) ( AIArrayRef array, ai::int32 i, AIDictionaryRef* value );

	/** Sets a dictionary value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value The new value.
	*/
	AIAPI AIErr (*SetDictEntry) ( AIArrayRef array, ai::int32 i, AIDictionaryRef value );

	/** Retrieves an array value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetArrayEntry) ( AIArrayRef array, ai::int32 i, AIArrayRef* value );

	/** Sets an array value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value The new value.
	*/
	AIAPI AIErr (*SetArrayEntry) ( AIArrayRef array, ai::int32 i, AIArrayRef value );

	/** Retrieves a Unicode string value from an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetUnicodeStringEntry) ( AIArrayRef array, ai::int32 i, ai::UnicodeString& value );

	/** Sets a Unicode string value for an array entry.
			@param array The array reference.
			@param i The 0-based index position of the entry.
			@param value The new value.
	*/
	AIAPI AIErr (*SetUnicodeStringEntry) ( AIArrayRef array, ai::int32 i, const ai::UnicodeString& value );

	/** Adds an entry at the end of an array.
			@param array The array reference.
			@param entry The array entry reference. See \c apiAIEntry.h.
			@see \c #Set()
	*/
	AIAPI AIErr (*AppendEntry) ( AIArrayRef array, AIEntryRef entry );

	/**  Reserves a minimum length of storage for an array.
			@param array The array reference.
			@param count The number of entries to reserve.
	*/
	AIAPI AIErr (*Reserve) ( AIArrayRef array, ai::int32 count );

} AIArraySuite;

#include "AIHeaderEnd.h"


#endif
