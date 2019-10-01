/*
 *        Name:	IAIUnicodeString.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Interface to the wrapper class for AIUnicodeStringSuite & the
 *				primary interface for the AI core to
 *				the ai::UnicodeString objects.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2015 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


#ifndef _IAIUNICODESTRING_H_
#define _IAIUNICODESTRING_H_

#include "AITypes.h"
#include "AICharacterEncoding.h"
#include "IAIAutoBuffer.h"

#include <string>
#include <iterator>
#include <stdexcept>

#if defined(MAC_ENV)
	#import <CoreFoundation/CFString.h>
    #if defined _UTF16_BASIC_STRING_EXPORT_H_
        #include _UTF16_BASIC_STRING_EXPORT_H_
    #endif
#endif // defined(MAC_ENV)


/** @file IAIUnicodeString.h */

class CAIUnicodeStringImpl;

/** @ingroup Errors
	An out-of-range index was used.
	See \c #ai::UnicodeString */
#define kUnicodeStringBadIndex				'US!I'
/** @ingroup Errors
	An attempt to create string longer than maximum allowed length.
	See \c #ai::UnicodeString */
#define kUnicodeStringLengthError			'US#L'
/** @ingroup Errors
	A string is malformed.
	See \c #ai::UnicodeString */
#define kUnicodeStringMalformedError		'US!F'


namespace ai {

/** Constant Pascal string adapter object. */
class const_PStr
{
public:
	/** Constructor. Creates a constant Pascal string object from a Pascal string.
			@param pascalString The Pascal string.
			@return The new object.	*/
	explicit const_PStr(const unsigned char* pascalString) : fConstStr(pascalString) {};
	/** Destructor */
	virtual ~const_PStr() {}
	/** Constructor. Creates a constant Pascal string from a string pointer.
			@param p The string pointer.
			@return The new object. */
	const_PStr(const const_PStr& p) : fConstStr(p.fConstStr) {};
 	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	const unsigned char* get() const
	{ return fConstStr; }
 	/** Retrieves a character from this string.
 			@return The character.  	*/
	const unsigned char& operator[] (size_t i) const
	{ return fConstStr[i]; }
protected:
	const unsigned char* fConstStr;
	const_PStr& operator=(const const_PStr&);

};

/** Mutable Pascal string adapter object. */
class PStr : public const_PStr
{
public:
	/** Constructor. Creates a mutable Pascal string object from a Pascal string.
			@param pascalString The C string.
			@return The new object.	*/
	explicit PStr(unsigned char* pascalString) : const_PStr(pascalString) {};
	/** <Constructor. Creates a mutable Pascal string object from a string pointer.
			@param p The string pointer.
			@return The new object. */
	PStr(const PStr& p) : const_PStr(p) {};
 	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	unsigned char* get() const
	{ return const_cast<unsigned char*>(fConstStr); }
 	/** Retrieves a character from this string.
 			@return The character.  	*/
	unsigned char& operator[] (size_t i) const
	{ return get()[i]; }
	///** Convenience operator  */
	//operator const const_PStr& ()
	//{ return *this; }
};


#if defined(WIN_ENV)

class UnicodeString;

/** In Windows only. An adapter object that helps move data back and forth
    between Windows functions and the UnicodeString class when the VisualStudio
    compiler's options are set to treat \c wchar_t as an intrinsic type.

    This class requires that \c UTF16 and \c wchar_t be the same size.

	This class provides a very thin object veneer on the Windows string
	pointer types. The object takes a copy of the data with which it is constructed.
*/
class WCHARStr 
{
public:
	/** Type equivalent to Windows \c WCHAR type. */
	typedef wchar_t WCHAR;
	/** Type equivalent to Windows \c LPCWSTR type. */
	typedef const WCHAR* LPCWSTR;
	/** Type equivalent to Windows \c LPWSTR type. */
	typedef WCHAR* LPWSTR;

public:
	/** Constructs an empty \c WCHARStr object.
			@return The \c WCHARStr object.
	*/
	WCHARStr () : fConstStr() {}
	/** Constructs a \c WCHARStr object from the contents of a UnicodeString.
			@param string The source Unicode string.
			@return The \c WCHARStr object.
	*/
	WCHARStr (const ai::UnicodeString& string);

#if defined(_NATIVE_WCHAR_T_DEFINED)
	// This ctor is redundant if wchar_t is not an intrinsic.  It cannot be distinguished from the const ASUnicode* ctor. 

	/** Constructs a \c WCHARStr object from the contents pointed at by a 0-terminated
		\c LPCWSTR.  It is assumed that the contents of the source are UTF-16 code units in
			platform byte order.
			@param wcharString The source string data, UTF-16 code units in platform byte order.
	*/
	WCHARStr (LPCWSTR wcharString);
#endif // defined(_NATIVE_WCHAR_T_DEFINED)

	/** Constructs a \c WCHARStr object from the contents pointed at by a 0-terminated array of
		\c #ASUnicode.  It is assumed that the contents of the source are UTF-16 code units in
			platform byte order.
			@param string The source string data, UTF-16 code units in platform byte order.
	*/
	WCHARStr (const ASUnicode* string);

	/** Copy constructor, creates a copy of a \c WCHARStr object.
			@param p The object to copy.
	*/
	WCHARStr (const WCHARStr& p) : fConstStr(p.fConstStr) {}

#if defined(AI_HAS_RVALUE_REFERENCES) && defined(AI_HAS_DEFAULTED_FUNCTIONS)
	/** Move constructor */
	WCHARStr (WCHARStr&&) = default;
#endif

	/** Destructor */
	virtual ~WCHARStr() {}


	/** Assignment operator */
	WCHARStr& operator= (const WCHARStr& rhs)
	{
		fConstStr = rhs.fConstStr;
		return *this;
	}

#if defined(AI_HAS_RVALUE_REFERENCES) && defined(AI_HAS_DEFAULTED_FUNCTIONS)
	/** Assignment operator */
	WCHARStr& operator= (WCHARStr&&) = default;
#endif

	/** Converts the contents of this object to \c LPCWSTR.
		The returned value is only valid for the lifetime of this object.
			@return The \c LPCWSTR value.
	*/
	LPCWSTR as_LPCWSTR () const
	{
		return fConstStr.c_str();
	}
	
	/** Converts the contents of this object to \c #ASUnicode.
		The returned value is only valid for the lifetime of this object.
			@return A pointer to the \c #ASUnicode value.
	*/
	const ASUnicode* as_ASUnicode () const;

	/** Computes the length of the string contents of this object.
			@return The number of \c WCHAR characters.
	*/
	size_t length() const;

	/* Convenience operators */
#if defined(_NATIVE_WCHAR_T_DEFINED)
	// This operator is redundant if wchar_t is not an intrinsic.  It cannot be distinguished from the const ASUnicode* operator. 
	operator LPCWSTR () const 
	{
		return as_LPCWSTR();
	}
#endif //defined(_NATIVE_WCHAR_T_DEFINED)

	operator const ASUnicode* () const
	{
		return as_ASUnicode();
	}

protected:
	std::basic_string<WCHAR> fConstStr;
};

#endif /* WIN_ENV */

/** \c UnicodeString objects provide basic string functionality for
	Unicode-based strings, similar to that provided by the standard C string library.

	The contents of the string are treated as if all characters are represented
	as full 32-bit Unicode characters, which means you do not need to know the
	internal representation of the string, or deal with surrogate pairs during
	editing or searching operations.

*/
class UnicodeString {
public:
	/** A numeric relative offset type (signed integer). */
	typedef ai::sizediff_t offset_type;
	/** A numeric value type (unsigned integer). */
	typedef size_t size_type;
	/** Value type for a UTF-32 character code. */
	typedef ASUInt32 UTF32TextChar;
	/** Value type for a UTF-16 character code. */
	typedef ASUnicode UTF16Char;

	typedef UTF32TextChar value_type;


	/** The maximum number of characters possible in a string. This also indicates a failure if used as return value. */
	static const size_type npos;

	/** Normalization forms for use with the \c #normalize() method.
		See http://www.unicode.org/reports/tr15/ for more information. */
	enum NormalizedForm {
		/** Canonical Decomposition */
		kForm_NFD		= 0,
		/** Canonical Decomposition, followed by Canonical Composition */
		kForm_NFC,
		/** Compatibility Decomposition */
		kForm_NFKD,
		/** Comparability Decomposition, followed by Canonical Composition. */
		kForm_NFKC,

		/** Do not use this */
		kForm_DummyValue = 0xFFFFFFFF
	};
	
	/** TBD */
	class Collator;

	// ai::UnicodeString doesn't support non-const iterators because
	// its operator[] or at() doesn't return a reference to value_type
	// and for the same reason const_iterator doesn't overload operator->()
	class const_iterator;
	friend class const_iterator;

public:
	class const_iterator 
		: public std::iterator<std::random_access_iterator_tag, UnicodeString::value_type>
	{
	public:
		typedef const_iterator self_type;
		typedef UnicodeString::size_type size_type;
		typedef const UnicodeString* container_type;

		// default construct NULL iterator
		// can't be dereferenced, incremented or decremented
		const_iterator() : fIndex(0), fStringContainer(nullptr)
		{ 
		}

		// construct iterator corresponding to a given index in the container
		const_iterator(size_type index, container_type container) 
			: fIndex(index), fStringContainer(container) 
		{
		}

		const_iterator(const self_type& rhs) = default; // copy constructor
		self_type& operator=(const self_type& rhs) = default; // copy assignment

		value_type operator*() const
		{
			if (!fStringContainer || fIndex >= fStringContainer->size())
			{
				throw std::out_of_range{"string iterator not dereferencable"};
			}

			return (*fStringContainer)[fIndex];
		}

		self_type& operator++() // preincrement
		{
			++fIndex;
			return (*this);
		}
		
		self_type operator++(int) // postincrement
		{
			auto temp = *this;
			++(*this);
			return temp;
		}

		self_type& operator--() // predecrement
		{
			--fIndex;
			return (*this);
		}

		self_type operator--(int) // postdecrement
		{
			auto temp = *this;
			--(*this);
			return temp;
		}

		self_type& operator+=(difference_type offset) // increment by integer
		{
			fIndex += offset;
			return (*this);
		}

		self_type operator+(difference_type offset) const // return this + integer
		{
			self_type temp = *this;
			return (temp += offset);
		}

		self_type& operator-=(difference_type offset) // decrement by integer
		{
			fIndex -= offset;
			return (*this);
		}

		self_type operator-(difference_type offset) const // return this - integer
		{
			self_type temp = *this;
			return (temp -= offset);
		}

		difference_type operator-(const self_type& rhs) const // return difference of iterators
		{
			return (fIndex - rhs.fIndex);
		}
		
		bool operator==(const self_type& rhs) const // test for iterator equality
		{
			return (fIndex == rhs.fIndex);
		}

		bool operator!=(const self_type& rhs) const // test for iterator inequality
		{
			return !(*this == rhs);
		}

		bool operator<(const self_type& rhs) const // test if this < rhs
		{	
			return (fIndex < rhs.fIndex);
		}

		bool operator>(const self_type& rhs) const // test if this > rhs
		{	
			return (rhs < *this);
		}

		bool operator<=(const self_type& rhs) const // test if this <= rhs
		{	
			return (!(rhs < *this));
		}

		bool operator>=(const self_type& rhs) const // test if this >= rhs
		{	
			return (!(*this < rhs));
		}

	private:
		bool compatible(const self_type& rhs) const
		{
			return (fStringContainer->fImpl == rhs.fStringContainer->fImpl);
		}

	private:
		size_type fIndex = 0;
		container_type fStringContainer;
	};

	//----------------------------------------------------------------------
	/** @name Constructors & Destructor */
	//----------------------------------------------------------------------
	//@{
	/** Empty string constructor.  Creates a valid, empty string.  This method is guaranteed
		to not throw any exceptions. */
	explicit UnicodeString () AINOTHROW;
	/** Constructs a UnicodeString from an encoded byte array.
			@param string Array of bytes to construct from.
			@param srcByteLen Length of the array.
			@param encoding Encoding of the contents of the byte array. Default
				is the current platform encoding
		*/
	explicit UnicodeString (const char* string, offset_type srcByteLen,
		AICharacterEncoding encoding = kAIPlatformCharacterEncoding);

	/** Constructs a UnicodeString using a copies of a single character.
			@param count Number of characters to insert in this string.
			@param ch The UTF32 code point (character) with which to initialize the string.
		*/
	explicit UnicodeString (size_type count, UTF32TextChar ch);

	/** Convenience constructor from a \c char buffer that is known to be 0 terminated.
			@param string Initial contents.
			@param encoding Encoding of the contents of the byte array.
		*/
	explicit UnicodeString (const char* string, AICharacterEncoding encoding = kAIPlatformCharacterEncoding);

	/** Convenience constructor from a \c std::string.
			@param string Initial contents.
			@param encoding Encoding of the contents of the byte array.
		*/
	explicit UnicodeString (const std::string& string, AICharacterEncoding encoding = kAIPlatformCharacterEncoding);

	/** Constructor from 0-terminated, platform-byte-ordered, UTF-16 array.
		Surrogate pairs are okay. Exception raised if string is malformed.
			@param string Pointer to a valid 0-terminated array of UTF-16 \c ASUnicode.
		*/
	explicit UnicodeString (const ASUnicode* string);

	/** Constructor from the ZString referred to by a ZString key.
			@param zStringKey The ZString key.
		*/
	explicit UnicodeString (const ZRef zStringKey);

	/** Constructor from a non-0-terminated platform-byte-ordered, UTF-16 array.
		Surrogate pairs are okay. Exception raised if string is malformed.
			@param string Pointer to an array of UTF-16 \c ASUnicode.
			@param srcUTF16Count The number of UTF-16 code units to be read from string.
		*/
	explicit UnicodeString (const ASUnicode* string, size_type srcUTF16Count);

	/** Constructor from a \c std::basic_string of platform-byte-ordered \c ASUnicode characters.
		Surrogate pairs are okay. Exception raised if string is malformed.
			@param string A \c std::basic_string<ASUnicode>.
		*/
	explicit UnicodeString (const std::basic_string<ASUnicode>& string);

	/** Copy Constructor, creates a copy of a string.
			@param s The string to copy.
		*/
	UnicodeString (const UnicodeString& s);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move Constructor
			@param other The string to move from.
		*/
	UnicodeString(UnicodeString&& other) AINOEXCEPT;
#endif // AI_HAS_RVALUE_REFERENCES

	/** Destructor */
	~UnicodeString ();
	//@}

	//----------------------------------------------------------------------
	/** @name Factory methods */
	//----------------------------------------------------------------------
	//@{
	/** Constructs a UnicodeString from a
	    non-zero-terminated \c char array whose encoding is ISO Roman/Latin.
	    	@param string The \c char array.
	   		@param count the number of bytes (chars) in the string.
	   		@return The Unicode string object.
	   	*/
	static UnicodeString FromRoman (const char* string, size_type count);

	/** Constructs a UnicodeString from a
	    zero-terminated \c char array whose encoding is ISO Roman/Latin.
	   		@param string The \c char array.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromRoman (const char* string);

	/** Constructs a UnicodeString from a
	    \c std::string whose encoding is ISO Roman/Latin.
	    	@param string The string.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromRoman (const std::string& string);

	/** Constructs a UnicodeString from a
	    Pascal string whose encoding is ISO Roman/Latin.
	    	@param pascalString The Pascal string.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromRoman (const const_PStr& pascalString);

	/** Constructs a UnicodeString from a
	    non-zero-terminated \c char array whose encoding is the current platform encoding.
	    	@param string The \c char array.
	    	@param count The number of bytes (chars) in the string.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromPlatform (const char* string, size_type count);

	/** Constructs a UnicodeString from a
	    zero-terminated \c char array whose encoding is the current platform encoding.
	    	@param string The \c char array.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromPlatform (const char* string);

	/** Constructs a UnicodeString from a
	    \c std::string whose encoding is the current platform encoding.
	    	@param string The string.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromPlatform (const std::string& string);

	/** Constructs a UnicodeString from a
	    Pascal string whose encoding is the current platform encoding.
	    	@param pascalString The Pascal string.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromPlatform (const const_PStr&  pascalString);

	/** Constructs a UnicodeString from a
	    zero-terminated \c char array whose encoding is UTF8.
	    	@param string The \c char array.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromUTF8 (const char* string);

	/** Constructs a UnicodeString from a
	    \c std::string whose encoding is UTF8.
	    	@param string The string.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromUTF8 (const std::string& string);

	/** Constructs a UnicodeString from a
	    Pascal string whose encoding is UTF8.
	    	@param pascalString The Pascal string.
	   		@return The Unicode string object.
	    */
	static UnicodeString FromUTF8 (const const_PStr&  pascalString);

	//@}

	/* Basic operations (as in std::basic_string) */

	/** Appends a string to this string.
			@param str The string to append.
			@return A reference to this Unicode string object.
		*/
	UnicodeString& append (const UnicodeString& str);

	/** Appends a substring of a given string to this string.
			@param str The source string of the substring.
			@param startOffset The 0-based index of the first character in the substring.
			@param count The maximum number of characters in the substring.
			@return A reference to this Unicode string object.
		*/
	UnicodeString& append (const UnicodeString& str, size_type startOffset,
		size_type count);

	/** Appends a given number of copies of a given character to this string.
			@param count The number of characters to append.
			@param ch The character to append.
			@return A reference to this Unicode string object.
		*/
	UnicodeString& append (size_type count, UTF32TextChar ch)
	{ return append(UnicodeString(count, ch)); }

	/** Replaces the contents of this string with another string.
			@param str The new contents.
			@return A reference to this Unicode string object.
	*/
	UnicodeString& assign (const UnicodeString& str);

	/** Replaces the contents of this string with a substring of another string.
			@param str The source of the substring.
			@param offset The 0-based index of the first character in the substring.
			@param count The maximum number of characters in the substring.
			@return A reference to this Unicode string object.
		*/
	UnicodeString& assign (const UnicodeString& str, size_type offset,
		size_type count)
	{ return assign(str.substr(offset, count)); }

	/** Retrieves the UTF32 code point (character) from a string by position index.
		Raises \c #kUnicodeStringBadIndex exception if offset is out of range.
			@param offset The 0-based index of the character.
			@return The UTF32 value of the character.
	*/
	UTF32TextChar at (size_type offset) const;

	/** Erases all characters in this string. Same as <code>erase(0, npos)</code>.
	    Uninitialized strings remain unchanged.
			@return Nothing.
			@see \c #erase()
		*/
	void clear ();

	/** Compares this string and another string for equality.
		Uninitialized strings are equal to other uninitialized strings and
		to empty strings.Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param str The string to compare against (right side of compare)..
			@return  Zero if the two strings are equal.
					<br> Negative if this string is less than \c str.
                    <br> Positive if this string is greater than \c str.
		*/
	ai::int32 compare (const UnicodeString& str) const;

	/** Compares this string and a substring of another string for equality.
		Uninitialized strings are equal to other uninitialized strings and
		to empty strings.Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param pos The 0-based index of the first character of the substring.
			@param num The number of characters to compare.
			@param str The source of the substring to compare against (right side of compare)..
			@return  Zero if this string and the substring are equal.
					<br> Negative if this string is less than the substring of \c str.
                    <br> Positive if this string is greater than the substring of \c str.
 		*/
	ai::int32 compare (size_type pos, size_type num, const UnicodeString& str) const;

	/** Compares a substring of this string and a substring of another string for equality.
		Uninitialized strings are equal to other uninitialized strings and
		to empty strings.Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param pos The 0-based index of the first character of the substring in this string.
			@param num The number of characters to compare in this string.
			@param str The source of the substring to compare against (right side of compare)..
			@param startOffset The 0-based index of the first character of the substring of \c str.
			@param count The number of characters from \c str to compare.
			@return  Zero if the two substrings are equal.
					<br> Negative if the substring of this string is less than the substring of \c str.
                    <br> Positive if the substring of this string is greater than the substring of \c str.
		*/
	ai::int32 compare (size_type pos, size_type num, const UnicodeString& str,
		size_type startOffset, size_type count) const;

	/** Retrieves the number of characters (UTF code points) in this string.
			@return The number of UTF code points in this string.
		*/
	size_type length () const;

	/** Reports whether this string is an empty string.
			@return True if the string is empty.
		*/
	bool empty () const;

	/** Removes characters (UTF code points) from this string.
			@param pos The 0-based position index of the first character to remove.
			@param count The number of characters to remove.
			@return A reference to this Unicode string object.
		*/
	UnicodeString&  erase (size_type pos=0, size_type count = npos);

	/** Erase character from this string
			@param position iterator to the character to remove
			@return iterator pointing to the character immediately following the character erased,
					or end() if no such character exists
		*/
	const_iterator  erase (const_iterator position)
	{
		size_type index = position - begin();
		erase(index, 1);
		return (begin() + index);
	}

	/** Erase substring [first, last) from this string
			@param first, last Range of the characters to remove
			@return iterator pointing to the character last pointed to before the erase, 
					or end() if no such character exists
		*/
	const_iterator  erase (const_iterator first, const_iterator last)
	{
		size_type index = first - begin();
		erase(index, last - first);
		return (begin() + index);
	}

	/** Searches for a character in this string.
			@param ch The character to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the found character, or
				the number of characters in this string (\c #npos)
				if the character is not found.
		*/
	size_type find (UTF32TextChar ch, size_type startOffset = 0 ) const;

	/** Searches for a string within a subset of this string.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the first character of the target
				string within this string, if found,  or the number of
				characters in this string (\c #npos)
				if the target string is not found.
		*/
	size_type find (const UnicodeString& target, size_type startOffset = 0) const;

	/** Searches for a substring within a subset of this string.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@param count The number of characters in the target string to search for.
			@return The 0-based position index of the first character of the target
				substring within this string, if found,  or (\c #npos)
				if the target substring is not found.
        */
	size_type find (const UnicodeString& target, size_type startOffset, size_type count) const;

	/** Searches for a character in this string, performing a caseless compare.
			@param ch The character to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the found character, or (\c #npos)
				if the character is not found.
		*/
	size_type caseFind (UTF32TextChar ch, size_type startOffset = 0 ) const
	{ return caseFind(ai::UnicodeString(1, ch), startOffset, 1); }

	/** Searches for a string within a subset of this string, performing a caseless compare.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the first character of the target
				string within this string, if found,  or (\c #npos)
				if the target string is not found.
		*/
	size_type caseFind (const UnicodeString& target, size_type startOffset = 0) const
	{ return caseFind(target, startOffset, target.length()); }

	/** Searches for a substring within a subset of this string, performing a caseless compare.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@param count The number of characters in the target string to search for.
			@return The 0-based position index of the first character of the target
				substring within this string, if found,  or  (\c #npos)
				if the target substring is not found.
        */
	size_type caseFind (const UnicodeString& target, size_type startOffset, size_type count) const;

	/**	Searches for a character in this string,
		moving backward from a point in this string.
			@param ch The character to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the found character, or (\c #npos)
				if the character is not found.
		*/
	size_type rfind (UTF32TextChar ch, size_type startOffset = npos ) const;

	/**	Searches for a string within a subset of this string,
		moving backward from a point in this string.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the first character of the target
				string within this string, if found,  or (\c #npos)
				if the target string is not found.
		*/
	size_type rfind (const UnicodeString& target, size_type startOffset = npos) const;

	/**	Searches for a substring within a subset of this string,
		moving backward from a point in this string.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@param count The number of characters in the target string to search for.
			@return The 0-based position index of the first character of the target
				substring within this string, if found,  or (\c #npos)
				if the target substring is not found.
		*/
	size_type rfind (const UnicodeString& target, size_type startOffset, size_type count) const;

	/** Searches for the first character of a string within a subset of this string.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the first character of the target
				string within this string, if found,  or (\c #npos)
				if the first character of the target string is not found.
		*/
	size_type find_first_of (const UnicodeString& target, size_type startOffset = 0) const
	{ return find_first_of(target, startOffset, npos); }

	/**	Searches for the first character of a string within a subset of this string.
			@param target The string to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@param count The number of characters in the substring to search.
			@return The 0-based position index of the first character of the target
				string within this string, if found,  or (\c #npos)
				if the character is not found.
		*/
	size_type find_first_of (const UnicodeString& target, size_type startOffset, size_type count) const;

	/** Searches for the last character of a string within a subset of this string.
			@param target The string containing the character to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the last character of the target
				string within this string, if found,  or (\c #npos)
				if the character is not found.
		*/
	size_type find_last_of (const UnicodeString& target, size_type startOffset = npos) const
	{ return find_last_of(target, startOffset, npos); }

	/** Searches for the last character of a string within a subset of this string.
			@param target The string containing the character to search for.
			@param startOffset The 0-based position index in this string at which to start the search.
			@param count The number of characters in this string in which to search.
			@return The 0-based position index of the last character of the target
				string within this string, if found,  or (\c #npos)
				if the character is not found.
		*/
	size_type find_last_of (const UnicodeString& target, size_type startOffset, size_type count) const;

	/**	Searches for the first occurrence in this string of a character
		that is not in a target string.
			@param target The target string.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the character within this string,
				if found,  or (\c #npos)	if the character is not found.
		*/
	size_type find_first_not_of (const UnicodeString& target, size_type startOffset = 0) const
	{ return find_first_not_of(target, startOffset, npos); }

	/**	Searches for the first occurrence in a subset of this string of a character
		that is not in a target string.
			@param target The target string.
			@param startOffset The 0-based position index in this string at which to start the search.
			@param count The number of characters in this string to search.
			@return The 0-based position index of the character within this string,
				if found,  or (\c #npos) if the character is not found.
		*/
	size_type find_first_not_of (const UnicodeString& target, size_type startOffset, size_type count) const;

	/**	Searches for the last occurrence in this string of a character
		that is not in a target string.
			@param target The target string.
			@param startOffset The 0-based position index in this string at which to start the search.
			@return The 0-based position index of the character within this string,
				if found,  or (\c #npos)	if the character is not found.
		*/
	size_type find_last_not_of (const UnicodeString& target, size_type startOffset = npos) const
	{ return find_last_not_of (target, startOffset, npos); }

	/**	Searches for the last occurrence in a subset of this string of a character
		that is not in a target string.
			@param target The target string.
			@param startOffset The 0-based position index in this string at which to start the search.
			@param count The number of characters in this string to search.
			@return The 0-based position index of the character within this string,
				if found,  or (\c #npos)	if the character is not found.
		*/
	size_type find_last_not_of (const UnicodeString& target, size_type startOffset, size_type count) const;

	/**	Replaces a substring in this string with another string.
			@param pos The 0-based position index in this string at which to start the replacement.
			@param num The number of characters in this string to replace.
			@param str The replacement string.
			@return This string object.
		*/
	UnicodeString& replace (size_type pos, size_type num, const UnicodeString& str)
	{ return replace(pos, num, str, 0, npos); }

	/**	Replaces a substring in this string with a substring of another string.
			@param pos The 0-based position index in this string at which to start the replacement.
			@param num The number of characters in this string to replace.
			@param str The replacement string.
			@param count The number of characters in the replacement substring, starting at the first character.
			@return This string object.
		*/
	UnicodeString& replace (size_type pos, size_type num, const UnicodeString& str, size_type count)
	{ return replace(pos, num, str, 0, count); }

	/**	Replaces a substring in this string with a substring of another string.
			@param pos The 0-based position index in this string at which to start the replacement.
			@param num The number of characters in this string to replace.
			@param str The replacement string.
			@param startOffset The 0-based position index of the first character of the replacement substring.
			@param count The number of characters in the replacement substring, starting at the offset.
			@return This string object.
		*/
	UnicodeString& replace (size_type pos, size_type num, const UnicodeString& str,
		size_type startOffset, size_type count);

	/** Inserts a string into this string, inserting as many characters as will fit.
			@param insertOffset The 0-based position index in this string
				after which to start the insertion.
			@param str The string to be partially or wholly inserted.
			@return This string object.
		*/
	UnicodeString& insert (size_type insertOffset, const UnicodeString& str)
	{ return insert(insertOffset, str, 0, npos); }

	/** Inserts a substring into this string.
			@param insertOffset The 0-based position index in this string
				after which to start the insertion.
			@param str The source string of the substring to insert.
			@param offset he 0-based position index of the first character
				of the substring to insert.
			@param count The number of characters to insert.
			@return This string object.
		*/
	UnicodeString& insert (size_type insertOffset, const UnicodeString& str,
		size_type offset, size_type count);

	/** Inserts repeated characters into this string.
			@param insertOffset The 0-based position index in this string
				after which to start the insertion.
			@param count The number of copies of the character to insert.
			@param ch The character to insert.
			@return This string object.
		*/
	UnicodeString& insert (size_type insertOffset, size_type count,
		UTF32TextChar ch)
	{ return insert(insertOffset, UnicodeString(count, ch), 0, count); }

	/** Appends a character to the end of this string.
			@param ch The character to append.
			@return Nothing.
	*/
	void push_back(UTF32TextChar ch)
	{ (void) append(1, ch); }

	/** Resizes this string, truncating it or adding characters as needed.
			@param count The new number of characters.
			@param ch The UTF code point value with which to initialize new elements,
				if the size of the string is increased.
			@return Nothing.
		*/
	void resize (size_type count, UTF32TextChar ch = UTF32TextChar());

	/** Retrieves the number of characters (UTF code points) in this string.
		This is the same as \c #length().
			@return The number of UTF code points in this string.
		*/
	ai::UnicodeString::size_type size () const
	{ return length(); }

	/** Creates a copy of a substring of this string.
			@param offset The 0-based position index of the first character
				to be copied to the substring.
			@param count The maximum number of characters to copy to the new substring.
			@return A \c UnicodeString object containing the requested substring.
		*/
	UnicodeString substr (size_type offset = 0, size_type count = npos) const;

	/** Swaps the contents of this string with another string.
			@param str The string to swap.
			@return Nothing.
		*/
	void swap (UnicodeString& str) AINOEXCEPT;

	/* Operators */

	/** Assignment operator.
			@param rhs The Unicode string object to assign into this one.
			@return A reference to this string.
		*/
	UnicodeString& operator= (const UnicodeString& rhs);

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move Assignment operator.
			@param rhs The Unicode string object to be moved from.
			@return A reference to this string.
		*/
	UnicodeString& operator= (UnicodeString&& rhs) AINOEXCEPT;
#endif // AI_HAS_RVALUE_REFERENCES

	/** Append operator.
			@param ch The character to append to this string.
			@return A reference to this string.
		*/
	UnicodeString& operator+= (UTF32TextChar ch)
	{ return append(1, ch); }

	/** Append operator.
			@param rhs The Unicode string object to append to this one.
			@return A reference to this string.
		*/
	UnicodeString& operator+= (const UnicodeString& rhs)
	{ return append(rhs); }

	/** Retrieves a character from this string.
			@param offset The 0-based position index of the character.
			@return The character.

		@note This behavior differs from \c std::basic_string operator[].
			This method returns the character at the given offset.
			\c std::basic_string::operator[] returns a writeable reference
			to the elopement at the given offset.
		*/
	UTF32TextChar operator[] (size_type offset) const;

	/** Equality operator.  Does a simple, direct, code-point-based
		comparison.
			@param rhs The string with which to compare this string.
			@return True if the strings are equal.
		*/
	bool operator== (const UnicodeString& rhs) const
	{ return compare(rhs) == 0; }

	/** Non-equality operator.  Does a simple, direct, code-point-based
		comparison.
			@param rhs The string with which to compare this string.
			@return True if the strings are not equal.
		*/
	bool operator!= (const UnicodeString& rhs) const
	{ return !(operator==(rhs)); }

	/** Less-than operator.  Does a simple, direct, code-point-based
		comparison.
			@param rhs The string with which to compare this string.
			@return True if this string is less than the comparison string.
		*/
	bool operator< (const UnicodeString& rhs) const
	{ return compare(rhs) < 0; }

	/** iterator support
			@return iterator to the first character
	*/
	const_iterator begin() const
	{
		return const_iterator(0, this);
	}

	/** iterator support
			@return iterator to the character following the last character
	*/
	const_iterator end() const
	{
		return const_iterator(this->size(), this);
	}

	/* non-std::basic_string based functionality */

	/** Convert the characters in this to lower case following the conventions of
		the default locale.
			@return A reference to this.
	*/
	UnicodeString& toLower();

	/**
		Convert the characters in this to UPPER CASE following the conventions of
		the default locale.
			@return A reference to this.
     */
	UnicodeString& toUpper();

	/** Compares this string with another string, doing a caseless
		code-point-based comparison.
		Uninitialized strings are equal to other uninitialized strings and
		empty strings. Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param str The comparison string (right side of compare).
			@return 0 if the strings are equal.
				<br> Positive if this string is greater than the comparison string.
				<br> Negative if this string is less than the comparison string.
	*/
	ai::int32 caseCompare (const UnicodeString& str) const
	{ return caseCompare(0, npos, str, 0, npos); }

	/** Compares this string with a substring of another string, doing a caseless
		code-point-based comparison.
		Uninitialized strings are equal to other uninitialized strings and
		empty strings. Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param pos The 0-based position index of the first character of the substring.
			@param num The number of characters to compare.
			@param str The comparison string (right side of compare).
			@return 0 if this string and the substring are equal.
				<br> Positive if this string is greater than the substring.
				<br> Negative if this string is less than the substring.
		*/
	ai::int32 caseCompare (size_type pos, size_type num, const UnicodeString& str) const
	{ return caseCompare(pos, num, str, 0, npos); }

	/** Compares a substring of this string with a substring of another string, doing a caseless
		code-point-based comparison.
		Uninitialized strings are equal to other uninitialized strings and
		empty strings. Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param pos The 0-based position index of the first character of
				the substring of this string.
			@param num The number of characters in the substring of this string.
			@param str The comparison string (right side of compare).
			@param startOffset The 0-based position index of the first character of
				the substring of the comparison string.
			@param count The number of characters in the substring of the comparison string.
			@return 0 if this substring and the comparison substring are equal.
				<br> Positive if this substring is greater than the comparison substring.
				<br> Negative if this substring is less than the comparison substring.
		*/
	ai::int32 caseCompare (size_type pos, size_type num, const UnicodeString& str,
		size_type startOffset, size_type count) const;

	/** Compares this string with another string for canonical equivalence
		of their normalized forms (NFD or NFC).	This requires temporary
		allocation of memory, and can throw out-of-memory errors.

		Uninitialized strings are equal to other uninitialized strings and
		empty strings. Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param str The comparison string (right side of compare).
			@return 0 if the strings are equal.
				<br> Positive if this string is greater than the comparison string.
				<br> Negative if this string is less than the comparison string.

			@note Substring comparison of non-normalized strings is not directly available.
				You can create substrings and pass them to this method.
		*/
	ai::int32 canonicalCompare (const UnicodeString& str) const;

	/** Compares this string with another string for canonical equivalence
		of their normalized forms (NFD or NFC), performing a caseless compare.
		This requires temporary	allocation of memory, and can throw out-of-memory errors.

		Uninitialized strings are equal to other uninitialized strings and
		empty strings. Uninitialized and empty strings are less than initialized,
		non-empty strings.
			@param str The comparison string (right side of compare).
			@return 0 if the strings are equal.
				<br> Positive if this string is greater than the comparison string.
				<br> Negative if this string is less than the comparison string.

			@note Substring comparison of non-normalized strings is not directly available.
				You can create substrings and pass them to this method.
		*/
	ai::int32 canonicalCaseCompare (const UnicodeString& str) const;

	/** Normalizes this string in place into the specified form.
		Normalization may require re-allocation of the string.  If this happens,
		the method can throw out-of-memory errors. On failure, this
		string remains unmodified.
			@param form The form with which to normalize the string.
			@return A reference to this string.
		*/
	UnicodeString& normalize (NormalizedForm form);

	/** Reports whether this string contains surrogate pairs.
			@return True if there are surrogate pairs in this string.
		*/
	bool hasSurrogates () const;

	/** Creates a UTF-16 string from the contents of this string, in platform byte order.
		This method does not allocate any memory, and returns in constant time.
			@param buffer A reference to a const pointer to \c UTF16Char in which
				to return the contents of this string as UTF-16 code units. Can be
				0 if this string is empty.
				This buffer pointer is only valid at most for the lifetime of this string.
				The buffer is not guaranteed to be 0 terminated.
				Use \c #as_ASUnicode() to guarantee a 0-terminated buffer.
			@return The number of UTF-16 characters in the returned buffer.
		*/
	size_type utf_16 (const UTF16Char*& buffer) const;

	/** Creates a 0-terminated UTF-16 string from the contents of this string,
		in platform byte order.
			@return The contents of this string as UTF-16 code units.
		*/
	std::basic_string<ASUnicode> as_ASUnicode ( ) const;

	/** Creates a UTF-8 string from the contents of this string.
			@return The contents of this string as a UTF-8 encoded \c std::string.
		*/
	std::string as_UTF8 ( ) const;

	/** Creates a platform-encoded version of this string.
			@return The contents of this string as a UTF-8 encoded \c std::string. */
	std::string as_Platform () const;

	/** Creates an ISO Latin/Roman-encoded version of this string.
			@return The contents of this string as a UTF-8 encoded \c std::string. */
	std::string as_Roman () const;

	/**	Copies the contents of this string to a provided buffer.  This method
		follows the \c strlcpy paradigm.
			@param buffer A pointer to a byte array in which to return the 0-terminated copy.
			@param bufferMax The maximum byte count to write to the buffer, including the 0 terminator,
				or \c NULL to return the required size.
			@param encoding The encoding for the result.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator.
		*/
	size_type getToBuffer ( char* buffer, size_type bufferMax, AICharacterEncoding encoding ) const;

	/**	Copies the contents of this string to a Pascal string in a provided buffer.
			@param pascalString A pointer to a Pascal string in which to return the 0-terminated copy.
			@param bufferMax The maximum byte count to write to the buffer, including the 0 terminator,
				or \c NULL to return the required size.
			@param encoding The encoding for the result.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator.
		*/
	size_type getToBuffer ( const PStr&  pascalString, size_type bufferMax, AICharacterEncoding encoding ) const;

	/**	Copies the contents of this string to a Unicode string in a provided buffer.
			@param buffer A pointer to a Unicode string in which to return the 0-terminated copy.
			@param bufferMax The maximum count of UTF-16 code units (\c ASUnicode) to write to the 
				buffer including a 0 terminator. Or, pass 0 to request 
				the required buffer size.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator.
		*/
	size_type as_ASUnicode (ASUnicode* buffer, size_type bufferMax ) const;

	/**	Copies the contents of this string to a platform-encoded Pascal string in a provided buffer.
			@param pascalString A pointer to a Pascal string in which to return the 0-terminated copy.
			@param bufferMax The maximum byte count to write to the buffer, including the 0 terminator,
				or \c NULL to return the required size.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator.
		*/
	size_type as_Platform ( const PStr&  pascalString, size_type bufferMax ) const;

	/**	Copies the contents of this string to a C string in a provided buffer.
			@param buffer A pointer to a C string in which to return the 0-terminated copy.
			@param bufferMax The maximum byte count to write to the buffer, including the 0 terminator,
				or \c NULL to return the required size.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator.
		*/
	size_type as_Platform ( char* buffer, size_type bufferMax ) const;

	/**	Copies the contents of this string to an ISO Latin/Roman-encoded C string in a provided buffer.
			@param buffer A pointer to a C string in which to return the 0-terminated copy.
			@param bufferMax The maximum byte count to write to the buffer, including the 0 terminator,
				or \c NULL to return the required size.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator.
		*/
	size_type as_Roman ( char* buffer, size_type bufferMax ) const;

	/**	Copies the contents of this string to an ISO Latin/Roman-encoded Pascal string in a provided buffer.
			@param pascalString A pointer to a Pascal string in which to return the 0-terminated copy.
			@param bufferMax The maximum byte count to write to the buffer, including the 0 terminator,
				or \c NULL to return the required size.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator.
		*/
	size_type as_Roman ( const PStr&  pascalString, size_type bufferMax ) const;

	/**	Creates a \c std::string from the contents of this string. Can throw
		an out-of-memory error.
			@param encoding The encoding for the result.
			@return The string result.
		*/
	std::string getInStdString (AICharacterEncoding encoding) const;

	/**	Copies the contents of this string to an \c ai::AutoBuffer<char>.
			@param encoding The encoding for the result.
			@param b The buffer in which to return the result. The resulting
				contents might not be 0 terminated.
			@return The number of characters (bytes) returned in the buffer.
		*/
	size_type getAs (AICharacterEncoding encoding, ai::AutoBuffer<char>& b) const;

#if defined(MAC_ENV)

	//----------------------------------------------------------------------
	/** @name Mac OS-specific Methods */
	//----------------------------------------------------------------------
	//@{
	/** Constructs a Unicode string object from a Mac OS \c CFString.
	   		@param cfString The source \c CFString.
		*/
	explicit UnicodeString (const CFStringRef& cfString);

	/** Converts the contents of this string to a Mac OS \c CFString.
	    	@param alloc A valid \c CFAllocatorRef for allocating the \c CFString.
			@return An immutable \c CFString object containing chars, or \c NULL if there was a problem
				creating the object. You must dispose of this object when it is no longer needed.
		*/
	CFStringRef as_CFString (CFAllocatorRef alloc) const;
	//@}
#endif // defined(MAC_ENV)
	
#if defined(WIN_ENV)

	//----------------------------------------------------------------------
	/** @name Windows-specific Methods */
	//----------------------------------------------------------------------
	//@{
	/** Constructs a Unicode string object from a Windows \c WCHARStr wrapper object.
	   		@param string The source \c WCHARStr.
	*/
	explicit UnicodeString (const WCHARStr& string);

	/** Converts the contents of this string to a \c WCHARStr wrapper object.
			@return The \c WCHARStr object.  Contents are UTF-16 encoded.
	*/
	WCHARStr as_WCHARStr () const;

	/**	Copies the contents of this string to a provided buffer.
			@param buffer A pointer to a buffer of \c WCHARStr::LPWSTR in which to return the 
				0-terminated copy.
			@param bufferMax The maximum count of \c WCHARStr::LPWSTR to write to the buffer.
			@return The size needed to write the entire string contents to a buffer,
				including a 0 terminator. Returned size is the count of \c WCHARStr::LPWSTR
				needed.
	*/
	size_type as_WCHARStr (WCHARStr::LPWSTR buffer, size_type bufferMax ) const;

	//@}
#endif // defined(WIN_ENV)


public:	// internal use public interface
	void deleteImpl();

protected:
	explicit UnicodeString(class CAIUnicodeStringImpl* impl);

private:
	CAIUnicodeStringImpl* fImpl;
};

/** Append operator.
@param lhs The Unicode string object to append to.
@param rhs The Unicode string object which is to be appended.
@return A new Unicode string object.
*/
inline UnicodeString operator+(UnicodeString lhs, const UnicodeString& rhs)
{
	return lhs.append(rhs);
}

///////////////////////////////////////////////////////////
// Inline implementations  - Yes, some of these could cause code bloat.  
// These could be moved to the IAIUnicodeString.inl file.
//

///////////////////////////////////////////////////////////
// UnicodeString inlines
///////////////////////////////////////////////////////////

inline void UnicodeString::swap(UnicodeString& str) AINOEXCEPT
{
	std::swap(fImpl, str.fImpl);
}

#ifdef AI_HAS_RVALUE_REFERENCES

// Move Constructor
inline UnicodeString::UnicodeString(UnicodeString&& other) AINOEXCEPT
	: fImpl{other.fImpl}
{
	other.fImpl = nullptr;
}

// Move Assignment operator
inline UnicodeString& UnicodeString::operator=(UnicodeString&& rhs) AINOEXCEPT
{
	swap(rhs);
	return *this;
}

#endif // AI_HAS_RVALUE_REFERENCES

inline UnicodeString& UnicodeString::insert (size_type insertOffset, const UnicodeString& str,
		size_type offset, size_type count)
{
	if ( insertOffset > length() || offset > str.length() )
		throw ai::Error(kUnicodeStringBadIndex);
	UnicodeString result = substr(0, insertOffset);
	result.append(str, offset, count);
	result.append(substr(insertOffset));

	*this = result;
	return *this;
}

inline UnicodeString& UnicodeString::replace (size_type pos, size_type num, const UnicodeString& str,
						size_type startOffset, size_type count)
{
	if ( pos > length() || startOffset > str.length() )
		throw ai::Error(kUnicodeStringBadIndex);
	erase(pos, num);
	insert(pos, str, startOffset, count);

	return *this;
}

inline std::string UnicodeString::as_UTF8 ( ) const
{
	return getInStdString(kAIUTF8CharacterEncoding);
}

inline std::string UnicodeString::as_Platform () const
{
	return getInStdString(kAIPlatformCharacterEncoding);
}

inline std::string UnicodeString::as_Roman () const
{
	return getInStdString(kAIRomanCharacterEncoding);
}

inline UnicodeString::size_type UnicodeString::as_ASUnicode ( ASUnicode* buffer, size_type bufferMax ) const
{
	const UTF16Char* bufPtr = 0;
	const size_type kThisUTF16Len = utf_16(bufPtr) + 1;
	const size_type kCopyMax = (bufferMax < kThisUTF16Len ? bufferMax : kThisUTF16Len) - 1;
	memcpy(buffer, bufPtr, kCopyMax*sizeof(UTF16Char));
	buffer[kCopyMax] = 0;

	return kThisUTF16Len;
}

#if defined(WIN_ENV)

inline UnicodeString::size_type UnicodeString::as_WCHARStr ( WCHARStr::LPWSTR buffer, size_type bufferMax ) const
{
	AI_STATIC_CHECK(sizeof(WCHARStr::WCHAR) == sizeof(ai::UnicodeString::UTF16Char), WCHAR_size_does_not_match_unsigned_short_size); //-V503
	return as_ASUnicode( reinterpret_cast<ASUnicode*>(buffer), bufferMax );
}

#endif // defined(WIN_ENV)

inline UnicodeString::size_type UnicodeString::as_Platform ( char* buffer, size_type bufferMax ) const
{
	return getToBuffer( buffer, bufferMax, kAIPlatformCharacterEncoding);
}

inline UnicodeString::size_type UnicodeString::as_Roman ( char* buffer, size_type bufferMax ) const
{
	return getToBuffer( buffer, bufferMax, kAIRomanCharacterEncoding);
}

inline UnicodeString::size_type UnicodeString::as_Platform ( const ai::PStr&  pascalString, size_type bufferMax ) const
{
	return getToBuffer( pascalString, bufferMax, kAIPlatformCharacterEncoding );
}

inline UnicodeString::size_type UnicodeString::as_Roman ( const ai::PStr&  pascalString, size_type bufferMax ) const
{
	return getToBuffer( pascalString, bufferMax, kAIRomanCharacterEncoding );
}



#if defined(WIN_ENV)

///////////////////////////////////////////////////////////
// WCHARStr inlines
///////////////////////////////////////////////////////////

inline WCHARStr::WCHARStr (const UnicodeString& string) : fConstStr()
{
	AI_STATIC_CHECK(sizeof(WCHAR) == sizeof(ai::UnicodeString::UTF16Char), WCHAR_size_does_not_match_unsigned_short_size); //-V503

	const std::basic_string<ASUnicode>& cInput = string.as_ASUnicode();
	const size_t cLen = cInput.length();

	if ( cLen > 0 )
		fConstStr = std::basic_string<WCHAR>(reinterpret_cast<LPCWSTR>(cInput.data()), cLen);
};

#if defined(_NATIVE_WCHAR_T_DEFINED)
	// This ctor is redundant if wchar_t is not an intrinsic.  This is the same as the const ASUnicode* ctor. 
inline WCHARStr::WCHARStr (WCHARStr::LPCWSTR wcharString) : fConstStr( wcharString )
{
}
#endif // defined(_NATIVE_WCHAR_T_DEFINED)

inline WCHARStr::WCHARStr (const ASUnicode* string)
{
	if ( string && *string )
	{
		AI_STATIC_CHECK(sizeof(WCHARStr::WCHAR) == sizeof(ai::UnicodeString::UTF16Char), WCHAR_size_does_not_match_unsigned_short_size); //-V503
		fConstStr.assign(reinterpret_cast<LPCWSTR>(string));
	}
}

inline const ASUnicode* WCHARStr::as_ASUnicode () const
{
	AI_STATIC_CHECK(sizeof(WCHARStr::WCHAR) == sizeof(ai::UnicodeString::UTF16Char), WCHAR_size_does_not_match_unsigned_short_size); //-V503
	return reinterpret_cast<const ASUnicode*>(this->as_LPCWSTR());
}

inline size_t WCHARStr::length() const
{
	return fConstStr.length();
}

#endif // defined(WIN_ENV)

} // end of namespace ai

#endif	// _IAIUNICODESTRING_H_
