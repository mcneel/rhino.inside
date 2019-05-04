#ifndef __AIDict__
#define __AIDict__

/*
 *        Name:	AIDictionary.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Dictionary Object Suite.
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

/** @file AIDictionary.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDictionarySuite						"AI Dictionary Suite"
#define kAIDictionarySuiteVersion9				AIAPI_VERSION(9)
#define kAIDictionarySuiteVersion				kAIDictionarySuiteVersion9
#define kAIDictionaryVersion					kAIDictionarySuiteVersion

#define kAIDictionaryIteratorSuite				"AI Dictionary Iterator Suite"
#define kAIDictionaryIteratorSuiteVersion4		AIAPI_VERSION(4)
#define kAIDictionaryIteratorSuiteVersion		kAIDictionaryIteratorSuiteVersion4
#define kAIDictionaryIteratorVersion			kAIDictionaryIteratorSuiteVersion


/** @ingroup Errors */
#define kNoSuchKey				'NOKY'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** A key that identifies a dictionary entry. */
typedef const struct _t_AIDictKey *AIDictKey;


/** An iterator that allows you to enumerate the contents of a dictionary. See
	the \c #AIDictionaryIteratorSuite for iteration functions. */
typedef struct _AIDictionaryIterator*			AIDictionaryIterator;


/** The data for the dictionary key-changed notifier. (Not currently sent). */
typedef struct _AIDictionaryKeyChangedNotifyData {
	/** Current notification sequence timestamp */
	ai::int32 refStamp;
	/** The dictionary that changed */
	AIDictionaryRef dictionary;
	/** The key whose value changed */
	AIDictKey key;
} AIDictionaryKeyChangedNotifyData;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides function to create and manage Illustrator data dictionaries.
	A dictionary is a heterogeneous container whose elements, called \e entries,
	are accessed by \e keys.

	Entries are of type \c #AIEntryRef. The \c #AIEntrySuite provides methods
	to construct and query entries of different types. Entries can contain
	values of various data types; simple types such	as booleans, integers, floats,
	and strings; and complex types such as arrays, other dictionaries, and
	references to document objects including art objects,
	brushes and styles. This makes dictionaries very flexible and
	powerful containers.

	Dictionaries can themselves be stored in other containers such as arrays
	or other dictionaries. In particular they can be stored in the dictionaries
	attached to art objects and to the document. When a dictionary is stored in
	one of these places (directly or indirectly) it is read and written as
	a part of the document.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDictionarySuite and \c #kAIDictionaryVersion.
 */
struct AIDictionarySuite {

	/** Creates a new dictionary. Dictionaries are reference counted;
		the initial reference count is 1.
			@param dictionary [out] A buffer in which to return the new dictionary reference.
			@see \c #AddRef(), \c #Release()
		*/
	AIAPI AIErr (*CreateDictionary) ( AIDictionaryRef* dictionary );


	/**  Increments the reference count of a dictionary.
			@param dictionary The dictionary reference.
		*/
	AIAPI ai::int32 (*AddRef) ( AIDictionaryRef dictionary );

	/**  Frees the memory associated with a dictionary
		 when it is no longer needed (the reference count is 0).
			@param dictionary The dictionary reference. Upon return, the reference is
				no longer valid.
		*/
	AIAPI ai::int32 (*Release) ( AIDictionaryRef dictionary );

	/** Creates a new dictionary that is an exact duplicate of an existing dictionary.
		Performs a deep copy.
			@param src The dictionary to copy.
			@param dst [out] A buffer in which to return the new dictionary reference.
		*/
	AIAPI AIErr (*Clone) ( ConstAIDictionaryRef src, AIDictionaryRef* dst );

	/** Makes a copy of a dictionary, replacing the current contents of an existing dictionary.
			@param dict The dictionary into which to copy contents.
			@param src The dictionary to copy.
		*/
	AIAPI AIErr (*Copy) ( AIDictionaryRef dict, ConstAIDictionaryRef src );

	/** Gets the number of entries in a dictionary. (Note that this function returns
		a numeric value, not an error code.)
			@param dict The dictionary.
			@return The number of entries.
		*/
	AIAPI ai::uint32 (*Size) ( ConstAIDictionaryRef dict );

	/** Creates a new iterator object for visiting dictionary entries. Iterators are
		reference counted.
			@param dict The dictionary.
			@param iterator [out] A buffer in which to return the iterator object.
			@see \c #AIDictionaryIteratorSuite::AddRef(), \c #AIDictionaryIteratorSuite::Release()
		*/
	AIAPI AIErr (*Begin) ( ConstAIDictionaryRef dict, AIDictionaryIterator* iterator );

	/** Finds a dictionary key, or creates a new one if the specified key does not
		exist. (Note that this function returns a key object, not an error code.)
			@param key The name of the key.
			@return The key object.
		*/
	AIAPI AIDictKey (*Key) ( const char* keyString );

	/** Retrieves the name string of a key. (Note that this function returns a string value,
		not an error code.)
			@param key The key object.
			@return The key name.
		*/
	AIAPI const char* (*GetKeyString) ( AIDictKey key );

	/** Reports whether there is an entry with a given key in a dictionary.
		(Note that this function returns a boolean value, not an error code.)
			@param dict The dictionary.
			@param key The key object.
		*/
	AIAPI AIBoolean (*IsKnown) ( ConstAIDictionaryRef dictionary, AIDictKey key );

	/** Removes the entry with a given key from a dictionary.
			@param dict The dictionary.
			@param key The key object.
		*/
	AIAPI AIErr (*DeleteEntry) ( AIDictionaryRef dictionary, AIDictKey key );

	/** Retrieves the data type of an entry.
			@param dict The dictionary.
			@param key The key object.
			@param entryType [out] A buffer in which to return the entry type.
			@see \c #AIEntrySuite
		*/
	AIAPI AIErr (*GetEntryType) ( ConstAIDictionaryRef dictionary, AIDictKey key, AIEntryType* entryType );


	/** Copies an entry from one dictionary to another, or to another key in the same
		dictionary.
			@param dictionary1 The source dictionary.
			@param dictionary2 The destination dictionary.
			@param key1 The key for the entry to copy.
			@param key2 The key for the new entry.
		*/
	AIAPI AIErr (*CopyEntry) ( ConstAIDictionaryRef dictionary1, AIDictionaryRef dictionary2,
			AIDictKey key1, AIDictKey key2 );

	/** Moves an entry from one dictionary to another (or to another key in the same
		dictionary), removing the source entry.
			@param dictionary1 The source dictionary.
			@param dictionary2 The destination dictionary.
			@param key1 The key for the entry to copy and remove.
			@param key2 The key for the new entry.
		*/
	AIAPI AIErr (*MoveEntry) ( AIDictionaryRef dictionary1, AIDictionaryRef dictionary2,
			AIDictKey key1, AIDictKey key2 );

	/** Swaps two entries in two dictionaries, or in the same dictionary.
			@param dictionary1 The source dictionary.
			@param dictionary2 The destination dictionary.
			@param key1 The first key (in \c dictionary1, moved to \c dictionary2).
			@param key2 The second key (in \c dictionary2, moved to \c dictionary1).

	*/
	AIAPI AIErr (*SwapEntries) ( AIDictionaryRef dictionary1, AIDictionaryRef dictionary2,
			AIDictKey key1, AIDictKey key2 );


	/** Retrieves an art object from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param art [out] A buffer in which to return the art object.
		*/
	AIAPI AIErr (*GetArtEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, AIArtHandle* art );

	/** Creates an entry which is a new art object of a specified type.
			@param dictionary The dictionary.
			@param key The entry key.
			@param art The art type, an \c #AIArtType value.
		*/
	AIAPI AIErr (*NewArtEntry) ( AIDictionaryRef dictionary, AIDictKey key, ai::int16 type );


	/** Moves an art object from the artwork tree into a dictionary, removing it from
		the artwork tree.
			@param dictionary The dictionary.
			@param key The entry key.
			@param art The art object.
		*/
	AIAPI AIErr (*MoveArtToEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArtHandle art );

	/** Moves an art object from a dictionary into the artwork tree, removing the entry from
		the dictionary.
			@param dictionary The dictionary.
			@param key The entry key.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object. This can be an object whose boundaries might overlap this one,
				or a compound path or group that might contain this path.
			@param art [out] A buffer in which to return a pointer to the art object.
			@see \c #AIArtSuite
		*/
	AIAPI AIErr (*MoveEntryToArt) ( AIDictionaryRef dictionary, AIDictKey key, ai::int16 paintOrder,
			AIArtHandle prep, AIArtHandle* art );


	/** Copies an art object from the artwork tree into a dictionary.
			@param dictionary The dictionary.
			@param key The entry key.
			@param art The art object.
		*/
	AIAPI AIErr (*CopyArtToEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArtHandle art );

	/** Copies an art object from a dictionary into the artwork tree.
			@param dictionary The dictionary.
			@param key The entry key.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object. This can be an object whose boundaries might overlap this one,
				or a compound path or group that might contain this path.
			@param art [out] A buffer in which to return a pointer to the art object.
			@see \c #AIArtSuite
		*/
	AIAPI AIErr (*CopyEntryToArt) ( ConstAIDictionaryRef dictionary, AIDictKey key, ai::int16 paintOrder,
			AIArtHandle prep, AIArtHandle* art );

	/** Sets an entry in a dictionary to refer to the topmost group of a layer.
			@param dictionary The dictionary.
			@param key The entry key.
			@param layer The layer.
		*/
	AIAPI AIErr (*SetEntryToLayer) ( AIDictionaryRef dictionary, AIDictKey key, AILayerHandle layer );

	/** Inserts a new layer in the current document, whose topmost group is the group referenced by
		a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key, which must reference an art object that is a group.
			@param paintOrder The paint order, relative to the \c prep object. See \c AITypes::AIPaintOrder. 
			Valid values are \c #kPlaceDefault, \c #kPlaceAbove, \c #kPlaceBelow, \c #kPlaceAboveAll and \c #kPlaceBelowAll.
			@param prep The prepositional art object. This can be an object whose boundaries might overlap this one,
				or a compound path or group that might contain this path.
			@param art [out] A buffer in which to return the layer object.
			@see \c #AIArtSuite, \c #AILayerSuite
		*/
	AIAPI AIErr (*SetLayerToEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, ai::int16 paintOrder,
			AILayerHandle prep, AILayerHandle *layer );

	/** Retrieves a dictionary entry.
		(Note that this function returns an entry object, not an error code.)
			@param dictionary The dictionary.
			@param key The entry key.
			@return The entry object or a null entry if an entry with the given key does not exist..
		*/
	AIAPI AIEntryRef (*Get) ( ConstAIDictionaryRef dictionary, AIDictKey key );

	/** Sets a dictionary entry. Entries whose keys are prefixed with
		the character '-' are temporary, and are not saved to file.
			@param dictionary The dictionary.
			@param key The entry key.
			@param entry The entry object.
			*/
	AIAPI AIErr (*Set) ( AIDictionaryRef dictionary, AIDictKey key, AIEntryRef entry );


	// the following are convenience APIs for getting and setting entries of the basic types
	/** Retrieves a boolean value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetBooleanEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, AIBoolean* value );

	/** Sets a boolean value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The new value.
	*/
	AIAPI AIErr (*SetBooleanEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIBoolean value );

	/** Retrieves an integer value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetIntegerEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, ai::int32* value );

	/** Sets an integer value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The new value.
	*/
	AIAPI AIErr (*SetIntegerEntry) ( AIDictionaryRef dictionary, AIDictKey key, ai::int32 value );

	/** Retrieves a pointer value from a dictionary entry (pointers may be 64-bit or 32-bit depending on platform).
	@param dictionary The dictionary.
	@param key The entry key.
	@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetPointerEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, ai::intptr* value );

	/** Sets a pointer value for a temporary dictionary entry. If the key is not temporary i.e. does not begin with "-", it returns kBadParameterErr
	@param dictionary The dictionary.
	@param key The entry key.
	@param value The new value.
	*/
	AIAPI AIErr (*SetPointerEntry) ( AIDictionaryRef dictionary, AIDictKey key, ai::intptr value );

	/** Retrieves a real-number value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetRealEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, AIReal* value );

	/** Sets a real-number value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The new value.
	*/
	AIAPI AIErr (*SetRealEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIReal value );

	/** Retrieves a string value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetStringEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, const char** value );

	/** Sets a string value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The new value.
	*/
	AIAPI AIErr (*SetStringEntry) ( AIDictionaryRef dictionary, AIDictKey key, const char* value );

	/** Retrieves a binary value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
			@param size [out] A buffer in which to return the number of bytes in the \c value buffer.
	*/
	AIAPI AIErr (*GetBinaryEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, void* value, size_t* size );

	/** Sets a binary value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The pointer to the buffer containing the new value.
			@param size The number of bytes in the \c value buffer.
	*/
	AIAPI AIErr (*SetBinaryEntry) ( AIDictionaryRef dictionary, AIDictKey key, void* value, size_t size );

	/** Retrieves a dictionary value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetDictEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, AIDictionaryRef* value );

	/** Sets a dictionary value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The new value.
	*/
	AIAPI AIErr (*SetDictEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIDictionaryRef value );

	/** Retrieves an array value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetArrayEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, AIArrayRef* value );

	/** Sets an array value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The new value.
	*/
	AIAPI AIErr (*SetArrayEntry) ( AIDictionaryRef dictionary, AIDictKey key, AIArrayRef value );

	/** Retrieves a Unicode string value from a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetUnicodeStringEntry) ( ConstAIDictionaryRef dictionary, AIDictKey key, ai::UnicodeString& value );

	/** Sets a Unicode string value for a dictionary entry.
			@param dictionary The dictionary.
			@param key The entry key.
			@param value The new value.
	*/
	AIAPI AIErr (*SetUnicodeStringEntry) ( AIDictionaryRef dictionary, AIDictKey key, const ai::UnicodeString& value );

	/** Marks art as changed when a change has been made to the dictionary that affects
		a user-visible property of any associated art object. This causes any styles or plug-in groups
		containing the affected object to execute.
			@param dictionary The dictionary.
		*/
	AIAPI AIErr (*TouchArt) ( ConstAIDictionaryRef dictionary );

	/** Creates a new iterator object for the matched key. Iterators are reference counted.
		@param dict The dictionary.
		@param key The key to find
		@param iterator [out] A buffer in which to return the iterator object.
			use AIDictionaryIteratorSuite::GetEntry to get value directly from iterator
		returns kNoSuchKey if the key is not found.
		@see \c #AIDictionaryIteratorSuite::AddRef(), \c #AIDictionaryIteratorSuite::Release()
	*/
	AIAPI AIErr(*Find) (ConstAIDictionaryRef dict, AIDictKey key, AIDictionaryIterator* iterator);


};


/** Use these functions to iterate through the contents of a dictionary.
	Obtain the iterator object with \c #AIDictionarySuite::Begin(), and
	get the number of entries with  \c #AIDictionarySuite::Size().

	Iterators are reference counted. The initial count is 1.
*/
struct AIDictionaryIteratorSuite {

	/** Increments the reference count of an iterator.
			@param iterator The iterator object.
		*/
	AIAPI ai::int32 (*AddRef) ( AIDictionaryIterator iterator );

	/** Frees the memory associated with an iterator when it is no
		longer used (the reference count is 0).
				@param iterator The iterator object. Upon return, this
					reference is no longer valid.
		*/
	AIAPI ai::int32 (*Release) ( AIDictionaryIterator iterator );

	/** Reports whether an iterator is valid. (Not yet implemented)
			@param iterator The iterator object.
			@return True if the iterator is valid, false if the dictionary has
				changed due to insertion or deletion of elements since the
				iterator was constructed. */
	AIAPI AIBoolean (*IsValid) ( AIDictionaryIterator iterator );

	/** Makes an iterator refer to the same dictionary entry as another iterator.
			@param iterator The iterator object.
			@param from Another iterator object, whose current entry reference is copied.
		*/
	AIAPI AIErr (*Copy) ( AIDictionaryIterator iterator, AIDictionaryIterator from );

	/** Creates a new iterator which is a copy of another iterator.
			@param iterator The iterator object to copy.
			@param clone [out] A buffer in which to return the new iterator object.
		*/
	AIAPI AIErr (*Clone) ( AIDictionaryIterator iterator, AIDictionaryIterator* clone );

	/** Reports whether two iterators refer to the same entry of the same dictionary.
		(Note that this function returns a boolean value, not an error code.)
			@param iterator1 The first iterator.
			@param iterator2 The second iterator.
			@return True if both iterators refer to the same entry of the same dictionary.
		*/
	AIAPI AIBoolean (*IsEqual) ( AIDictionaryIterator iterator1, AIDictionaryIterator iterator2 );

	/** Reports whether an iterator has exhausted all dictionary entries.
		(Note that this function returns a boolean value, not an error code.)
			@param iterator The iterator object.
			@return True if the iteration has reached the end.
		*/
	AIAPI AIBoolean (*AtEnd) ( AIDictionaryIterator iterator );

	/** Advance an iterator's current-entry reference to the next entry.
		(Note that this function does not return an error code. Use \c #AtEnd()
		to determine if the iterator has exhausted all entries.)
			@param iterator The iterator object.
		*/
	AIAPI void (*Next) ( AIDictionaryIterator iterator );

	/** Back up an iterator's current-entry reference to the previous entry.
		(Note that this function does not return an error code. Calling it
		on the first entry has undefined results.)
			@param iterator The iterator object.
		*/
	AIAPI void (*Prev) ( AIDictionaryIterator iterator );

	/** Retrieves the key of an iterator's current entry.
		(Note that this function returns a key object, not an error code.)
			@param iterator The iterator object.
			@return The key object.
		*/
	AIAPI AIDictKey (*GetKey) ( AIDictionaryIterator iterator );

	/** Retrieves a dictionary entry for the dictionary iterator
	(Note that this function returns an entry object, not an error code.)
	@param iterator The iterator object.
	@return The entry object or a null entry if the iterator is at the end
	*/
	AIAPI AIEntryRef(*GetEntry) (AIDictionaryIterator iterator);
};


#include "AIHeaderEnd.h"


#endif
