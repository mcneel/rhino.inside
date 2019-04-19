#ifndef __AIEntry__
#define __AIEntry__

/*
 *        Name:	AIEntry.h
 *		$Id $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Dictionary Entry Object Suite.
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
#ifndef __AIArt__
#include "AIArt.h"
#endif
#ifndef __AILayer__
#include "AILayer.h"
#endif
#ifndef __AICustomColor__
#include "AICustomColor.h"
#endif
#ifndef __AIObjectSet__
#include "AIObjectSet.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIEntry.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIEntrySuite							"AI Entry Suite"
#define kAIEntrySuiteVersion7					AIAPI_VERSION(7)
#define kAIEntrySuiteVersion					kAIEntrySuiteVersion7
#define kAIEntryVersion							kAIEntrySuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/


/**
	A reference to a container dictionary entry, which associates a string key
	with a value of a given type (\c #AIEntryType).
	\li Use the \c #AIDictionarySuite functions to get and set keys,
	and to get and set entries by key.
	\li Use the \c #AIEntrySuite functions to get and set entry values
	of specific data types.
 */
typedef struct _AIEntry*						AIEntryRef;

/** An array is a heterogeneous sequence of entries indexed by integers.
	@see \c #AIArraySuite */
typedef struct _AIArray*						AIArrayRef;

/** A dictionary is a heterogeneous collection of entries indexed by keys that are character strings.
	@see \c #AIDictionarySuite  */
typedef struct _AIDictionary*					AIDictionaryRef;
typedef const struct _AIDictionary*				ConstAIDictionaryRef;

/** A unique identifier, which can be stored in dictionaries and arrays.
	A unique identifier cannot occur in more than one container,
    or more than once in a container.
	@see \c #AIUIDREFSuite */
typedef struct _AIUID*							AIUIDRef;

/** An opaque reference to a unique identifier.
	The \c #AIEntrySuite provides methods to convert between
     \c #AIEntryRef and \c #AIUIDRef.
	@see \c #AIUIDREFSuite */
typedef struct _AIUIDREF*						AIUIDREFRef;

/** A reference to an XML element.
	@see \c #AIXMLElementSuite */
typedef struct _AIXMLNode*						AIXMLNodeRef;

/** A reference to an SVG filter
	@see \c #AISVGFilterSuite */
typedef struct _t_AISVGFilterOpaque*			AISVGFilterHandle;

/** A reference to an art style.
	@see \c #AIArtStyleSuite. */
typedef struct _t_AIArtStyle*					AIArtStyleHandle;

 /** Container entry type, the data type for the value of an entry. */
typedef ai::int32  AIEntryType;
/**  The container entry types. Some correspond directly to data types, and
	some to objects defined in other suites. */
enum
{
	/** Value type is unknown to this version of the API */
	UnknownType,
	/** Integer (32 bit signed) */
	IntegerType,
	/** Boolean */
	BooleanType,
	/** Real (single precision floating point) */
	RealType,
	/** String (null terminated sequence of 8-bit values) */
	StringType,
	/** Dictionary. An art object is stored in a container by storing its dictionary. */
	DictType,
	/** Array */
	ArrayType,
	/** Binary data. If you store the data to file, you are responsible
		for the byte order of the data. */
	BinaryType,
	/** An (x,y) location. A convenience over an \c ArrayType of 2 \c Reals */
	PointType,
	/** A transformation matrix. A convenience over an \c ArrayType of 6 \c Reals */
	MatrixType,
	/** A reference to a pattern. See \c #AIPatternSuite. */
	PatternRefType,
	/** A reference to a brush pattern */
	BrushPatternRefType,
	/** A reference to a custom color (either spot or global process). See \c #AICustomColorSuite.*/
	CustomColorRefType,
	/** A reference to a gradient. See \c #AIGradientSuite. */
	GradientRefType,
	/** A reference to a plug-in global object. See \c #AIPluginSuite. */
	PluginObjectRefType,
	/** A fill style. See \c #AIArtStyleSuite. */
	FillStyleType,
	/** A stroke style. See \c #AIArtStyleSuite. */
	StrokeStyleType,
	/** A unique identifier. See \c #AIUIDSuite. */
	UIDType,
	/** A unique identifier reference. See \c #AIUIDSuite.*/
	UIDREFType,
	/** An XML node. See \c #AIXMLElementSuite.  */
	XMLNodeType,
	/** An SVG filter. See \c #AISVGFilterSuite.*/
	SVGFilterType,
	/** An art style. See \c #AIArtStyleSuite.*/
	ArtStyleType,
	/** A symbol definition reference. See \c #AISymbolSuite. */
	SymbolPatternRefType,
	/** A graph design reference. */
	GraphDesignRefType,
	/** A blend style (transparency attributes). See \c #AIGradientSuite. */
	BlendStyleType,
	/** A graphical object. */
	GraphicObjectType,
	/** A UnicodeString object. See \c #AIUnicodeStringSuite. */
	UnicodeStringType,	
	/** A pointer which is 8-bytes in 64-bit and 4-bytes in 32 bit.**/
	PointerType,
	/** PointType which is written as relative to ruler origin in document*/
	ArtworkPointType,
	/** A Smooth Shading Style. See ToDo \c #AIArtStyleSuite. */
	SmoothShadingType
};


/** @ingroup Errors */
#define kNoSuchEntry						'EnNS'
/**	@ingroup Errors
	Returned when trying to access an entries value and the entry is not of
	the requested type.
 */
#define kWrongEntryType						100
/**	@ingroup Errors
	Returned when trying to convert an entry to a particular value type and
	the underlying value of the entry is not convertible. For example, an integer can
	be converted to a real but not to a UID.
 */
#define kNoConversionErr					'NoCV'

/*******************************************************************************
 **
 **	Suite
 **
 **/


/**	@ingroup Suites

	This suite provides functions for constructing and inspecting dictionary
	and array entries.

	Entry objects associate a string key with a value of a given type
	(\c #AIEntryType). Access array entries by integer index.
	Access dictionary entries  by key, using the functions of the
	\c #AIDictionarySuite.

	\li Functions with names "To<Type>" create entries of certain
	data types; for example, \c #ToInteger() creates an integer entry from
	an integer value.
	\li Functions with names "From<Type>" retrieve the values of entries; for
	example, use \c #FromInteger() to get an integer entry value.

	@see \c #AIArraySuite::MoveArtToEntry(), <br>
	 \c #AIArraySuite::MoveEntryToArt(), <br>
	 \c #AIDictionarySuite::MoveArtToEntry(), <br>
	 \c #AIDictionarySuite::MoveEntryToArt()

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIEntrySuite and \c #kAIEntryVersion.


	Entries, like the dictionaries and arrays that contain them, are reference
	counted. A function that returns an entry increments the count first. The
	caller must decrement the count when that entry is no longer needed to avoid
	memory leaks. For convenience, the "To<Type>" and \c #AIDictionarySuite::Set()
	functions  automatically decrement the reference count of the entry you pass in.
	This allows you to get the value of an entry in a container such as
	 a dictionary with code like this:
	@code
ASBoolean value;
result = sAIEntry->ToBoolean(sAIDictionary->Get(dict, "MyKey"), &value);
	@endcode

	Similarly, you can set an entry value in a container such as a dictionary
	with code like this:
	@code
result = sAIDictionary->Set(dict, "MyKey", sAIEntry->FromReal(15));
	@endcode

	The \c #GetType() and \c #Equiv() functions do not consume the parameter;
	manage reference counts accordingly.
*/

struct AIEntrySuite
{

	/** Reference count maintenance. increments the count of references to an entry.
			@param entry The entry object.
		*/
	AIAPI ai::int32 (*AddRef) ( AIEntryRef entry );

	/** Reference count maintenance. decrements the count of references to an entry.
			@param entry The entry object.
	*/
	AIAPI ai::int32 (*Release) ( AIEntryRef entry );

	/** Retrieves the type of an entry. Does not affect the reference count of the passed
		entry. (Note that this function returns a type value, not an error code.)
			@param entry The entry object
			@return The entry type.
	*/
	AIAPI AIEntryType (*GetType) ( AIEntryRef entry );


	// the various entry types

	/** Retrieves the boolean value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToBoolean) ( AIEntryRef entry, ASBoolean* value );

	/** Constructs an entry from a boolean value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromBoolean) ( ASBoolean value );

	/** Retrieves the integer value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToInteger) ( AIEntryRef entry, ai::int32* value );

	/** Constructs an entry from an integer value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromInteger) ( ai::int32 value );

	/**  Retrieves the real-number value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToReal) ( AIEntryRef entry, AIReal* value );

	/** Constructs an entry from a real-number value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromReal) ( AIReal value );

	/**  Retrieves the point value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToRealPoint) ( AIEntryRef entry, AIRealPoint* value );

	/** Constructs an entry from a point value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromRealPoint) ( const AIRealPoint *value );

	/**  Retrieves the transformation-matrix value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToRealMatrix) ( AIEntryRef entry, AIRealMatrix* value );

	/** Constructs an entry from a transformation-matrix value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromRealMatrix) ( const AIRealMatrix *value );

	/**  Retrieves the string value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToString) ( AIEntryRef entry, const char** value );

	/** Constructs an entry from a string value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromString) ( const char* value );

	/**  Retrieves the dictionary value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToDict) ( AIEntryRef entry, AIDictionaryRef* value );

	/** Constructs an entry from a dictionary value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromDict) ( AIDictionaryRef value );

	/**  Retrieves the art object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
			@see \c #AIArraySuite::MoveArtToEntry()<br> \c #AIDictionarySuite::MoveArtToEntry().
		 */
	AIAPI AIErr (*ToArt) ( AIEntryRef entry, AIArtHandle* art );

	/**  Retrieves the array value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToArray) ( AIEntryRef entry, AIArrayRef* value );

	/** Constructs an entry from an array value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromArray) ( AIArrayRef value );

	/**  Retrieves the binary data value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value, or \c NULL to
				retrieve the size needed for the value.
			@param size [out] A buffer in which to return the number of bytes
				written to the \c value buffer, or the size needed if \c value is \c NULL.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
			@note If you call the function twice to get the size needed and then retrieve the
				value, keep in mind that each call decrements the reference count of the entry.
		 */
	AIAPI AIErr (*ToBinary) ( AIEntryRef entry, void* value, size_t* size );

	/** Constructs an entry from a binary data value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@param size The number of bytes in the \c value buffer.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromBinary) ( void* value, size_t size );

	/**  Retrieves the pattern object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToPattern) ( AIEntryRef entry, AIPatternHandle* value );

	/** Constructs an entry from a pattern object value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromPattern) ( AIPatternHandle value );

	/**  Retrieves the brush pattern object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToBrushPattern) ( AIEntryRef entry, AIPatternHandle* value );

	/** Constructs an entry from a brush pattern object value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromBrushPattern) ( AIPatternHandle value );

	/**  Retrieves the gradient object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToGradient) ( AIEntryRef entry, AIGradientHandle* value );

	/** Constructs an entry from a gradient object value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromGradient) ( AIGradientHandle value );

	/**  Retrieves the custom color object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToCustomColor) ( AIEntryRef entry, AICustomColorHandle* value );

	/** Constructs an entry from a custom color object value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromCustomColor) ( AICustomColorHandle value );

	/**  Retrieves the plug-in global object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToPluginObject) ( AIEntryRef entry, AIObjectHandle* value );

	/** Constructs an entry from a plug-in global object value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/

	AIAPI AIEntryRef (*FromPluginObject) ( AIObjectHandle value );

	/**  Retrieves the fill style value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToFillStyle) ( AIEntryRef entry, struct AIFillStyle *value );

	/** Constructs an entry from a fill style value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromFillStyle) ( const struct AIFillStyle *value );

	/**  Retrieves the stroke style value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToStrokeStyle) ( AIEntryRef entry, struct AIStrokeStyle *value );

	/** Constructs an entry from a stroke style value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromStrokeStyle) ( const struct AIStrokeStyle *value );

	/* New in Illustrator 10.0 */

	/**  Retrieves the unique identifier value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToUID) ( AIEntryRef entry, AIUIDRef* value );

	/** Constructs an entry from a unique identifier value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromUID) ( AIUIDRef value );

	/**  Retrieves the unique identifier reference value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToUIDREF) ( AIEntryRef entry, AIUIDREFRef* value );

	/** Constructs an entry from a unique identifier reference value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromUIDREF) ( AIUIDREFRef value );

	/**  Retrieves the XML node value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToXMLNode) ( AIEntryRef entry, AIXMLNodeRef* value );

	/** Constructs an entry from an XML node value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromXMLNode) ( AIXMLNodeRef value );

	/**  Retrieves the SVG filter value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToSVGFilterHandle) ( AIEntryRef entry, AISVGFilterHandle* value );

	/** Constructs an entry from an SVG filter value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromSVGFilterHandle) ( AISVGFilterHandle value );

	/**  Retrieves the symbol pattern object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToSymbolPattern) ( AIEntryRef entry, AIPatternHandle* value );

	/** Constructs an entry from a symbol pattern object value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromSymbolPattern) ( AIPatternHandle value );

	// Type conversion routines.
	// Conversion rules are the same as for \c std::basic_[io]stream.

	/** Retrieves a string entry as a boolean if possible. Only valid for entries with
		value "1", "0", "true", or "false".
			@param entry The entry object.  This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the new value.
			@return The error \c #kNoConversionErr if conversion is not possible.
		*/
	AIAPI AIErr (*AsBoolean) ( AIEntryRef entry, ASBoolean* value );

	/** Retrieves a string entry as an integer if possible.
			@param entry The entry object.  This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the new value.
			@return The error \c #kNoConversionErr if conversion is not possible.
		*/
	AIAPI AIErr (*AsInteger) ( AIEntryRef entry, ai::int32* value );

	/** Retrieves a string entry as a real number if possible.
			@param entry The entry object.  This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the new value.
			@return The error \c #kNoConversionErr if conversion is not possible.
		*/
	AIAPI AIErr (*AsReal) ( AIEntryRef entry, AIReal* value );

	/** Retrieves an entry as a string if possible. Converts an integer, boolean,
		real, UID, UID reference, or Unicode string value to a platform-encoded string.
			@param entry The entry object.  This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the new value.
				This block of memory is reused by the next call to this function; do not delete
				it.	If needed, make a copy of the returned string before making another call
				to this function.
			@return The error \c #kNoConversionErr if conversion is not possible.
		*/
	AIAPI AIErr (*AsString) ( AIEntryRef entry, const char** value );

	/** Retrieves a string entry as a unique identifier if possible. The string
		value must be in the form "id(\e uid )".
  			@param entry The entry object.  This call automatically decrements
  				the reference count.
  			@param value [out] A buffer in which to return the new value.
			@return The error \c #kNoConversionErr if conversion is not possible.
		*/
	AIAPI AIErr (*AsUIDREF) ( AIEntryRef entry, AIUIDREFRef* value );

	/**  Retrieves the art style object value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToArtStyle) ( AIEntryRef entry, AIArtStyleHandle* value );

	/** Constructs an entry from a art style object value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromArtStyle) ( AIArtStyleHandle value );

	/* New in Illustrator 12.0 */

	/**  Retrieves the Unicode string value of an entry.
			@param entry The entry object. This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the value.
			@return The error \c #kBadParameterErr if the entry is not of the correct type.
		 */
	AIAPI AIErr (*ToUnicodeString) ( AIEntryRef entry, ai::UnicodeString& value );

	/** Constructs an entry from a Unicode string value.
		(Note that this function returns an entry object, not an error code.)
			@param value The entry value.
			@return The new entry object. The initial reference count is 1.
		*/
	AIAPI AIEntryRef (*FromUnicodeString) ( const ai::UnicodeString& value );

	/** Retrieves an entry as a Unicode string, if possible. Converts an integer, boolean,
		real, UID, UID reference, or platform-encoded string value to a Unicode string.
			@param entry The entry object.  This call automatically decrements
				the reference count.
			@param value [out] A buffer in which to return the new value.
			@return The error \c #kNoConversionErr if conversion is not possible.
		*/
	AIAPI AIErr (*AsUnicodeString) ( AIEntryRef entry, ai::UnicodeString& value );

	/* New in Illustrator 15.0 */

	/** Reports whether two entries are equivalent. 
		Equivalent entries have the same type and value. 
		Two NULL entries are considered equivalent. 
			@param entry1 The first entry. 
			@param entry2 The second entry. 
			@return True if the entries are equivalent, false otherwise. 
		*/ 
	AIAPI ASBoolean(*Equiv) (AIEntryRef entry1, AIEntryRef entry2);

};


#include "AIHeaderEnd.h"


#endif
