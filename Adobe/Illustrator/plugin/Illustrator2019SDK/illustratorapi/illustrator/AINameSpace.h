#ifndef __AINameSpace__
#define __AINameSpace__

/*
 *        Name:	AINameSpace.h
 *   $Revision: 4 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Name Space Suite.
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

#ifndef __AIStringPool__
#include "AIStringPool.h"
#endif


#include "AIHeaderBegin.h"

/** @file AINameSpace.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAINameSpaceSuite		"AI Name Space Suite"
#define kAINameSpaceSuiteVersion		AIAPI_VERSION(4)
#define kAINameSpaceVersion		kAINameSpaceSuiteVersion

/** @ingroup Errors 
	See \c #AINameSpaceSuite. */
#define kNameSpaceErr	  		'NAME'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque namespace reference. See \c #AINameSpaceSuite. */
typedef struct NameSpace AINameSpace;

#if __BUILD_PLUGIN__
#define kNSMaxNameLength		(1024)
#define kNSMaxPathLength		((kNSMaxNameLength + 1) * 5)
#define kNSPathSeparator		'/'
typedef char NSPath[kNSMaxPathLength + 1];
typedef char NSName[kNSMaxNameLength + 1];
#endif


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides functions that allow you to create and manage namespaces.
	A namespace is essentially a global dictionary that is not associated with any particular
	document. Its keys are strings called \e paths and the associated values can be of these
	types and values:
		\li  \c integer (value: \c long )
		\li  \c real (value: \c double )
	 	\li  \c string (value: <code> char *</code> )
	 	\li  \c raw (length: \c long, value: <code> char *</code> )
	 	\li  \c unicodeString (value: <code> #ai::UnicodeString *</code>)

	Unlike dictionaries, the contents of a namespace have a hierarchical organization.
	The hierarchy of keys is like that of directory paths in a file system, with
	levels divided by '/' separators. For example the key "/root/entry" has two
	components, "root" and "entry".

	You can specify partial paths, and refer to all keys that are prefixed with that path.
	A partial path is specified with a trailing '/' separator. The path "/" refers
	to the root.

	A path can contain a maximum of 505 characters. Each component of a path (excluding
	separators) can have a maximum of 100 characters.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAINameSpaceSuite and \c #kAINameSpaceVersion.
 */
typedef struct {

	/** Creates a new namespace.
			@param pool The string pool from which to allocate the path component
				string, or \c NULL to use the global string pool, If supplied,
				the caller must dispose of the string pool after freeing the namespace.
				See \c #AIStringPoolSuite.
			@param space A buffer in which to return the namespace reference.
		*/
	AIErr (*AllocateNameSpace) ( AIStringPool *pool, AINameSpace **space );

	/**  Frees a namespace. If you supplied a string pool, you must free it after
		freeing the namespace.
			@param The namespace. Upon return, this reference is invalid.
		*/
	AIErr (*DisposeNameSpace) ( AINameSpace *space );

	/** Sets the value stored at a point in a namespace.
			@param The namespace.
			@param path The path.
			@param type The new type. Types are:
					\li  \c integer (value: \c long )
					\li  \c real (value: \c double )
				 	\li  \c string (value: <code> char *</code> )
				 	\li  \c raw (length: \c long, value: <code> char *</code> )
	 				\li  \c unicodeString (value: <code> #ai::UnicodeString *</code>)
			@param length For type \c raw only, the length of the value.
			@param value The new value, of the appropriate type.
		*/
	AIErr (*SetValue) ( const AINameSpace *space, const char *path, const char *type, ... );

	/** Retrieves Sets the value stored at a point in a namespace.
			@param The namespace.
			@param path The path.
			@param type [out] A buffer in which to return the type. Types are:
					\li  \c integer (value: \c long )
					\li  \c real (value: \c double )
				 	\li  \c string (value: <code> char *</code> )
				 	\li  \c raw (length: \c long, value: <code> char *</code> )
	 				\li  \c unicodeString (value: <code> #ai::UnicodeString *</code>)
			@param length [out] For type \c raw only, a buffer in which to return the length of the value.
			@param value [out] A buffer in which to return the value, of the appropriate type.
		*/
	AIErr (*GetValue) ( const AINameSpace *space, const char *path, const char *type, ... );

	/** Retrieves the type of the value stored at a point in a namespace.
			@param The namespace.
			@param path The path.
			@param type [out] A buffer in which to return the type. Types are:
					\li  \c integer (value: \c long )
					\li  \c real (value: \c double )
				 	\li  \c string (value: <code> char *</code> )
				 	\li  \c raw (length: \c long, value: <code> char *</code> )
	 				\li  \c unicodeString (value: <code> #ai::UnicodeString *</code>)
		*/
	AIErr (*GetType) ( const AINameSpace *space, const char *path, char **type );

	/** Reports the number of times the value stored at a point in a
		namespace has been changed. Each time the value is set, the change count is incremented.
			@param The namespace.
			@param path The path. If this is an intermediate node in the namespace, the count is
				the number of times all values stored under that node have changed.
			@param count [out] A buffer in which to return the change count.
		*/
	AIErr (*GetChangeCount) ( const AINameSpace *space, const char *path, ai::int32 *count );

	/** Removes the value stored at a point in a namespace.
			@param The namespace.
			@param path The path. If this is a partial path, all values under it are removed.
		*/
	AIErr (*RemoveValue) ( const AINameSpace *space, const char *path );

	/** Reports the number of unique components that can be appended to a path to
		produce paths or partial paths in the namespace. (This is like the number of
		entries in a directory.)
			@param The namespace.
			@param path The base path.
			@param count [out] A buffer in which to return the component count.
		*/
	AIErr (*CountPaths) ( const AINameSpace *space, const char *path, ai::int32 *count );

	/** Retrieves a unique component that can be appended to a given path to produce a new
		path or partial path in the namespace.
			@param The namespace.
			@param path The base path.
			@param n The index position of the component.
			@param nthPath [out] A buffer in which to return the component,
				which includes the trailing separator if it identifies a partial path.
		*/
	AIErr (*GetNthPath) ( const AINameSpace *space, const char *path, ai::int32 n, char *nthPath );

	/** Reads namespace data that was written to a file using \c #FlushValue() into a namespace,
		under a given base path.
			@param The namespace.
			@param path The base path, used as a prefix.
			@param filter The file filter with which to read the data. This does not need
				to be the same filter used to serialize the keys.
	  */
	AIErr (*ParseValue) ( const AINameSpace *space, const char *path, AIDataFilter *filter );

	/** Writes data from a namespace to a filter, serializing the namespace entries identified
		by a partial path to a data filter.	Writes only the path after the base and the
		key/value pairs, not the base path.

		Use \c #ParseValue() to read data in from the resulting file to a new path prefix.
			@param The namespace.
			@param path The base path for the data.
			@param filter The file filter with which to serialize the keys.
		*/
	AIErr (*FlushValue) ( const AINameSpace *space, const char *path, AIDataFilter *filter );

} AINameSpaceSuite;


#include "AIHeaderEnd.h"

#endif
