#ifndef _IAICHARACTERENCODING_H_
#define _IAICHARACTERENCODING_H_

/*
 *        Name:	IAICharacterEncoding.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include <string>
#include <vector>
#include "AICharacterEncoding.h"

//needed for one of the templates below.
extern "C" AICharacterEncodingSuite *sAICharacterEncoding;

namespace ai {

/** Encoding characteristics and functions for platform encoding. */
struct PlatformTraits {
	/** The basic type used to represent the data. */
	typedef char unit_type;
	/** Retrieves the Illustrator character-encoding type.
			@return The encoding type constant. */
	static AICharacterEncoding encoding ()
		{return kAIPlatformCharacterEncoding;}
	/** Reports the maximum number of elements of the
		basic type needed to represent a sequence of a
		given number of character codes.
			@param codes The number of character codes.
			@return The number of elements needed. */
	static size_t codes_2_units (size_t codes)
		{return codes * 2;}
	/** Reports the maximum number of characters codes
		that could be encoded by a given number of elements of
		the basic type.
			@param units The number of elements.
			@return The number of character codes. */
	static size_t units_2_codes (size_t units)
		{return units;}
};

/** Encoding characteristics  and functions for UTF-8 encoding. */
struct UTF8Traits {
	/** The basic type used to represent the data. */
	typedef char unit_type;
	/** Retrieves the Illustrator character-encoding type.
			@return The encoding type constant. */
	static AICharacterEncoding encoding ()
		{return kAIUTF8CharacterEncoding;}
	/** Reports the maximum number of elements of the
		basic type needed to represent a sequence of a
		given number of character codes.
			@param codes The number of character codes.
			@return The number of elements needed. */
	static size_t codes_2_units (size_t codes)
		{return codes * 4;}
	/** Reports the maximum number of characters codes
		that could be encoded by a given number of elements of
		the basic type.
			@param units The number of elements.
			@return The number of character codes. */
	static size_t units_2_codes (size_t units)
		{return units;}
};

/** Encoding characteristics  and functions for UTF-16 encoding. */
struct UTF16Traits {
	/** The basic type used to represent the data. */
	typedef ASUnicode unit_type;
	/** Retrieves the Illustrator character-encoding type.
			@return The encoding type constant. */
	static AICharacterEncoding encoding ()
		{return kAIUTF16CharacterEncoding;}
	/** Reports the maximum number of elements of the
		basic type needed to represent a sequence of a
		given number of character codes.
			@param codes The number of character codes.
			@return The number of elements needed. */
	static size_t codes_2_units (size_t codes)
		{return codes * 2;}
	/** Reports the maximum number of characters codes
		that could be encoded by a given number of elements of
		the basic type.
			@param units The number of elements.
			@return The number of character codes. */
	static size_t units_2_codes (size_t units)
		{return units;}
};

// Template class for encoded strings

/** This class represents an encoded string.  */
template <class Traits>
class EncodedString {
public:
	/** Default constructor. Creates an empty encoded-string object.
			@return The new object.
		*/
	EncodedString ()
	{}

	/** Copy constructor. Creates a copy of an encoded-string object.
			@param s The encoded-string object to copy.
			@return The new object.
		*/
	EncodedString (const EncodedString& s) :
		string(s.string)
	{}

	/** Creates an encoded-string object with an initial string value.
			@param s The initial string, with the desired encoding.
			@return The new object.
		*/
	explicit EncodedString (const std::basic_string<typename Traits::unit_type>& s) :
		string(s)
	{}

	/** Creates an encoded-string object with an initial string value.
			@param s The initial string, a \c NULL terminated sequence
				of elements with the desired encoding.
			@return The new object.
		*/
	explicit EncodedString (const typename Traits::unit_type* s) :
		string(s)
	{}
	// construct an encoded string from a buffer containing elements
	// of the same encoding
	/** Creates an encoded-string object with an initial string value.
			@param s The initial string, a buffer containing a sequence
				of elements with the desired encoding.
			@param length The number of elements in the string buffer.
			@return The new object.
		*/
	EncodedString (const typename Traits::unit_type* s, size_t length) :
		string(s, length)
	{}

	/** Assignment operator	*/
	EncodedString& operator= (const EncodedString& s)
	{
		string = s.string;
		return *this;
	}

#if 1

	// for some reason Windows can't handle a templated conversion operator,
	// so we define an explicit cast operator instead.
	template <class SrcTraits>
	static EncodedString<Traits> cast (const EncodedString<SrcTraits>& src)
	{
		EncodedString<Traits> dst;

		size_t maxsize = Traits::codes_2_units(SrcTraits::units_2_codes(src.string.size()));
		size_t maxbytes = maxsize * sizeof(typename Traits::unit_type);
		std::vector<typename Traits::unit_type> b(maxsize);

		size_t bytes;
		size_t size;
		AIErr result = sAICharacterEncoding->ConvertBuffer(
				src.string.data(),
				src.string.size() * sizeof(typename SrcTraits::unit_type),
				SrcTraits::encoding(),
				&b[0], maxbytes, Traits::encoding(),
				&bytes, FALSE);
		if (result)
			throw ai::Error(result);
		size = bytes / sizeof(typename Traits::unit_type);

		dst = EncodedString<Traits>(&b[0], size);

		return dst;
	}
#else
	// implicit conversion to another encoding
	template <class DstTraits>
	operator EncodedString<DstTraits> () const
	{
		EncodedString<DstTraits> dst;

		size_t maxsize = DstTraits::codes_2_units(Traits::units_2_codes(string.size()));
		size_t maxbytes = maxsize * sizeof(DstTraits::unit_type);
		std::vector<DstTraits::unit_type> b(maxsize);

		size_t bytes;
		size_t size;
		AIErr result = sAICharacterEncoding->ConvertBuffer(
				string.data(), string.size(), Traits::encoding(),
				b, maxbytes, DstTraits::encoding(),
				&bytes, FALSE);
		if (result)
			throw ai::Error(result);
		size = bytes / sizeof(DstTraits::unit_type);

		dst = EncodedString<DstTraits>(b, size);

		return dst;
	}
#endif

	// the encoded data. direct access is allowed.
	std::basic_string<typename Traits::unit_type> string;
};


// types for strings
/** Encoded string type: platform encoding. */
typedef EncodedString<PlatformTraits> PlatformString;
/** Encoded string type: UTF-8 encoding. */
typedef EncodedString<UTF8Traits> UTF8String;
/** Encoded string type: UTF-16 encoding. */
typedef EncodedString<UTF16Traits> UTF16String;


}

#endif
