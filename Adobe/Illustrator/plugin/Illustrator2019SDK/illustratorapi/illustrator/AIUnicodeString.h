
#ifndef __AIUnicodeString__
#define __AIUnicodeString__

/*
 *        Name:	AIUnicodeString.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Unicode String Suite.
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

#include "IAIUnicodeString.h"
#include "AICharacterEncoding.h"
#include "AITypes.h"

#include "AIHeaderBegin.h"

/** @file AIUnicodeString.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIUnicodeStringSuite				"AI Unicode String Suite"
#define kAIUnicodeStringSuiteVersion		AIAPI_VERSION(8)
#define kAIUnicodeStringVersion				kAIUnicodeStringSuiteVersion

/*******************************************************************************
 **
 ** Types
 **
 **/

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides utilities that allow you to create and manipulate
	Unicode strings.
	@note It is recommended that you use the wrapper class, \c #ai::UnicodeString,
	rather than calling these functions directly.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIUnicodeStringSuite and \c #kAIUnicodeStringVersion.
	*/
typedef struct {

	/** Initializes a Unicode string with the contents of a C string.
			@param str [out] A buffer in which to return the Unicode string.
			@param string The C string.
			@param srcByteLen The number of bytes in the C string.
	  		@param encoding The encoding type for the new string.
   		*/
	AIAPI AIErr (*Initialize) (ai::UnicodeString& str, const char* string,
		ai::UnicodeString::offset_type srcByteLen, AICharacterEncoding encoding);

	/** Initializes a Unicode string with the contents of a UTF-16 encoded string.
			@param str [out] A buffer in which to return the Unicode string.
			@param utfs The UTF-16 encoded string, an array UTF-16 code units.
			@param srcUTF16Count The number of UTF-16 code units to be taken from the source string.
				A value of \c npos mean that the source string is 0-terminated.
		*/
	AIAPI AIErr (*InitializeUTF16) (ai::UnicodeString& str, const ASUnicode* utfs, ai::UnicodeString::offset_type srcUTF16Count);

	/** Initializes a Unicode string with a single UTF-32 code point (character) repeated a
		given number of times.
			@param str [out] A buffer in which to return the Unicode string.
			@param count The number of characters.
			@param ch The UTF code point.
 		*/
	AIAPI AIErr (*InitializeUTF32Char) (ai::UnicodeString& str, ai::UnicodeString::offset_type count,
		ai::UnicodeString::UTF32TextChar ch);

	/** Deletes the contents of a Unicode string, and reset it to an uninitialized state.
		Any pointers to UTF-16 buffers derived from that string become invalid.
			@param str The string.
   		*/
	AIAPI AIErr (*Destroy) (ai::UnicodeString& str);

	/* Basic operations (a la std::basic_string) */

	/** Appends one Unicode string to another.
			@param str The string to append to.
			@param str2 The string to append.
		*/
	AIAPI AIErr (*Append) (ai::UnicodeString& str, const ai::UnicodeString& str2);

	/** Appends a sub-string of one Unicode string to another.
			@param str The string to append to.
			@param str2 The source string for the substring to append.
			@param startOffset The 0-based character offset for the substring.
			@param count the maximum number of characters for the substring.
		*/
	AIAPI AIErr (*AppendSubString) (ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** Assigns one Unicode string to another.
			@param str The destination string.
			@param str2 The source string.
		*/
	AIAPI AIErr (*Assign) (ai::UnicodeString& str,
		const ai::UnicodeString& str2);

	/** Copies one Unicode string into another.
			@param str The destination string.
			@param str2 The source string. If empty or uninitialized,
				the destination string is truncated.
    	*/
	AIAPI AIErr (*Copy) (ai::UnicodeString& str, const ai::UnicodeString& str2);

	/** Retrieves the UTF-32 code point at an index position in a Unicode string.
			@param str The string.
			@param position The 0-based character offset for the character.
			@param ch [out] A buffer in which to return the character.
			@return An error if the given position is not a valid offset into
				the string.
		*/
	AIAPI AIErr (*GetChar) (const ai::UnicodeString& str,
		ai::UnicodeString::size_type position,
		ai::UnicodeString::UTF32TextChar& ch);

	/** Clears the contents of a Unicode string. An uninitialized string remains unchanged.
		(Note that this function does not return an error code.)
			@param str The string.
		*/
	AIAPI void (*Clear) (ai::UnicodeString& str);

	/** Compares substrings in two Unicode strings. Uninitialized strings
		are equal to other uninitialized strings and empty strings, and are less
		than initialized, non-empty strings.
		(Note that this function returns a numeric value, not an error code.)
			@param str The first string (left side of compare).
			@param pos The 0-based offset for the first character of the first substring.
			@param num The number of characters in the first substring.
			@param str2 The second string (right side of compare).
			@param startOffset The 0-based offset for the first character of the second substring.
			@param count The number of characters in the second substring.
			@return 0 if the substrings are equal.
				<br> Positive if the first substring is greater than the second.
				<br> Negative if the second substring is greater than the first.
		*/
	AIAPI ai::int32 (*Compare) (const ai::UnicodeString& str,
		ai::UnicodeString::size_type pos, ai::UnicodeString::size_type num,
		const ai::UnicodeString& str2,
		ai::UnicodeString::size_type startOffset, ai::UnicodeString::size_type count);

	/**
    * Convert the characters in this to lower case following the conventions of
    * the default locale.
	* @param UnicodeString to modify via reference
    * @return nothing.
    */
	AIAPI AIErr (*toLower) (ai::UnicodeString& src);

	/**
    * Convert the characters in this to upper case following the conventions of
    * the default locale.
	* @param UnicodeString to modify via reference
    * @return nothing.
    */
	AIAPI AIErr (*toUpper) (ai::UnicodeString& src);

	/** Performs a caseless comparison of substrings in two Unicode strings.
	    Strings are case folded in a locale-independent manner prior to comparison.
		Uninitialized strings are equal to other uninitialized strings and
		empty strings, and are less than initialized, non-empty strings.
		(Note that this function returns a numeric value, not an error code.)
			@param str The first string (left side of compare).
			@param pos The 0-based offset for the first character of the first substring.
			@param num The number of characters in the first substring.
			@param str2 The second string (right side of compare).
			@param startOffset The 0-based offset for the first character of the second substring.
			@param count The number of characters in the second substring.
			@return 0 if the substrings are equal.
				<br> Positive if the first substring is greater than the second.
				<br> Negative if the second substring is greater than the first.
			*/
	AIAPI ai::int32 (*CaseCompare) (const ai::UnicodeString& str,
		ai::UnicodeString::size_type pos, ai::UnicodeString::size_type num,
		const ai::UnicodeString& str2,
		ai::UnicodeString::size_type startOffset, ai::UnicodeString::size_type count);

	/** Performs a normalized comparison of substrings in two Unicode strings.
		Uninitialized strings are equal to other uninitialized strings and
		empty strings, and are less than initialized, non-empty strings.
		(Note that this function returns a numeric value, not an error code.)
			@param str The first string (left side of compare).
			@param pos The 0-based offset for the first character of the first substring.
			@param num The number of characters in the first substring.
			@param str2 The second string (right side of compare).
			@param startOffset The 0-based offset for the first character of the second substring.
			@param count The number of characters in the second substring.
			@return 0 if the substrings are equal.
				<br> Positive if the first substring is greater than the second.
				<br> Negative if the second substring is greater than the first.
		*/
	AIAPI AIErr (*CanonicalCompare) (const ai::UnicodeString& str, const ai::UnicodeString& str2, ai::int32& compareResult);

	/** Performs a normalized, caseless comparison of substrings in two Unicode strings.
	    Strings are case folded in a locale-independent manner prior to comparison.
		Uninitialized strings are equal to other uninitialized strings and
		empty strings, and are less than initialized, non-empty strings.
		(Note that this function returns a numeric value, not an error code.)
			@param str The first string (left side of compare).
			@param pos The 0-based offset for the first character of the first substring.
			@param num The number of characters in the first substring.
			@param str2 The second string (right side of compare).
			@param startOffset The 0-based offset for the first character of the second substring.
			@param count The number of characters in the second substring.
			@return 0 if the substrings are equal.
				<br> Positive if the first substring is greater than the second.
				<br> Negative if the second substring is greater than the first.
		*/
	AIAPI AIErr (*CanonicalCaseCompare) (const ai::UnicodeString& str, const ai::UnicodeString& str2, ai::int32& compareResult);

	/** Retrieves the number of UTF-32 code points (characters) in a Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string.
			@return The number of characters, 0 for an uninitialized or empty string.
		*/
	AIAPI ai::UnicodeString::size_type (*Length) (const ai::UnicodeString& str);

	/** Reports whether a Unicode string is empty.
		(Note that this function returns a boolean value, not an error code.)
			@param str The string.
			@return True if the string is uninitialized or empty.
		*/
	AIAPI AIBool8 (*Empty) (const ai::UnicodeString& str);

	/** Erases characters from a Unicode string.
			@param str The string, which is modified in place.
			@param startOffset The 0-based index of the first character to erase.
			@param count The maximum number of characters to erase.
			@return An error if the given position index is not a valid offset into the string.
		*/
	AIAPI AIErr (*Erase) (ai::UnicodeString& str,
		ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** Searches for the first occurrence of a character in a substring of a Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string.
			@param ch The character to search for.
			@param startOffset The 0-based index in \c str at which to start the search.
			@return The 0-based character index of the found character,
				or \c npos if the character is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*FindChar) (const ai::UnicodeString& str,
		ai::UnicodeString::UTF32TextChar ch,
		ai::UnicodeString::size_type startOffset);

	/** Searches for the first occurrence of an entire string within a substring of a Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@return The 0-based character index of the found string,
				or \c npos if the string is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*FindString) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset);

	/** Searches for the first occurrence of a substring of one Unicode string within
		a substring of another Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@param count The maximum number of characters within \c str2 to search for.
			@return The 0-based character index of the found string,
				or \c npos if the string is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*FindSubString) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** Searches for the first occurrence of a substring of one Unicode string within
		a substring of another Unicode string, performing a caseless comparison.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@param count The maximum number of characters within \c str2 to search for.
			@return The 0-based character index of the found string,
				or \c npos if the string is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*CaseFindSubString) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/**	Searches for the last occurrence of a character in a substring of a Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string.
			@param ch The character to search for.
			@param startOffset The 0-based index in \c str at which to start the search.
			@return The 0-based character index of the found character,
				or \c npos if the character is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*RFindChar) (const ai::UnicodeString& str,
		ai::UnicodeString::UTF32TextChar ch,
		ai::UnicodeString::size_type startOffset);

	/**	Searches for the last occurrence of an entire string within a substring of a Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@return The 0-based character index of the found string,
				or \c npos if the string is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*RFindString) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset);

	/**	Searches for the last occurrence of a substring of one Unicode string within
		a substring of another Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@param count The maximum number of characters within \c str2 to search for.
			@return The 0-based character index of the found string,
				or \c npos if the string is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*RFindSubString) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/**	Searches for the first occurrence of any character from a subset of one
		Unicode string in a substring of another string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@param count The number of characters from the start of \c str2 to compare.
			@return The 0-based character index of the found character,
				or \c npos if the character is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*FindFirstOf) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** Searches in a Unicode string for the first occurrence of any character that
		does not appear in a subset of another string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@param count The number of characters from the start of \c str2 to compare.
			@return The 0-based character index of the found character,
				or \c npos if the character is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*FindFirstNotOf) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** Searches in a Unicode string for the last character that also appears in
		a substring of another string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@param count The number of characters from the start of \c str2 to compare.
			@return The 0-based character index of the found character,
				or \c npos if the character is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*FindLastOf) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** Searches in a Unicode string for the last character that does not appear in
		a substring of another string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string to search in.
			@param str2 The string to compare against.
			@param startOffset The 0-based index in \c str at which to start the search.
			@param count The number of characters from the start of \c str2 to compare.
			@return The 0-based character index of the found character,
				or \c npos if the character is not found.
		*/
	AIAPI ai::UnicodeString::size_type (*FindLastNotOf) (const ai::UnicodeString& str,
		const ai::UnicodeString& str2, ai::UnicodeString::size_type startOffset,
		ai::UnicodeString::size_type count);

	/** Resizes a Unicode string to hold a given number of characters, truncating
		or padding it as needed.
			@param str The string, which is modified in place.
			@param count The number of characters.
			@param ch The padding character, if needed.
		*/
	AIAPI AIErr (*Resize) (ai::UnicodeString& str, ai::UnicodeString::size_type count, ai::UnicodeString::UTF32TextChar ch);

	/** Creates a substring of a Unicode string.
			@param subString [in, out] A Unicode string in which to return the substring.
				If it is uninitialized on input, it is initialized only if the source
				string is initialized and not empty.
			@param str The source string.
			@param offset The 0-based index in \c str at which to start the substring.
			@param count The maximum number of characters to place in the new substring.
		*/
	AIAPI AIErr (*SubStr) (ai::UnicodeString& subString,
		const ai::UnicodeString& str,
		ai::UnicodeString::size_type offset, ai::UnicodeString::size_type count);

	/** Swaps the contents of two Unicode strings.
			@param str The first string.
			@param str2 The second string.
		*/
	AIAPI AIErr (*SwapStr) (ai::UnicodeString& str, ai::UnicodeString& str2);

	/* non-std::string based functionality */

	//AIAPI int CaseCompare(const ai::UnicodeString& str,
	//	ai::UnicodeString::size_type pos, ai::UnicodeString::size_type num,
	//	const ai::UnicodeString& str2,
	//	ai::UnicodeString::size_type startOffset,
	//	ai::UnicodeString::size_type count);
	//AIAPI void FoldCase(ai::UnicodeString& str);

	/** Reports whether a Unicode string contains surrogate pairs.
		(Note that this function returns a boolean value, not an error code.)
			@param str The string.
			@return True if it contains at least one surrogate pair.
	*/
	AIAPI AIBool8 (*HasSurrogates) (const ai::UnicodeString& str);

	/** Retrieves a read-only pointer to a buffer that contains UTF-16 encoded
		characters in platform byte order, for a given Unicode string.
		(Note that this function returns a numeric value, not an error code.)
			@param str The string.
			@param buffer [out] The pointer to the buffer. Can be 0 if the string is
				empty or uninitialized.	Might not be 0 terminated.
			@return The length of the buffer in UTF-16 code units.
		*/
	AIAPI ai::UnicodeString::size_type (*UTF_16) (const ai::UnicodeString& str,
		const ai::UnicodeString::UTF16Char*& buffer);

	/** Retrieves the contents of a Unicode string in a given encoding.
			@param str The string.
			@param encoding The encoding.
			@param buffer [out] A buffer in which to return the encoded
					contents. Need not be initialized prior to the call.
			@param bufferByteCount [out] A buffer in which to return the number of bytes
				in the buffer that contain the requested data. The buffer can be
				larger than this.
		*/
	AIAPI AIErr (*GetAs) (const ai::UnicodeString& str, AICharacterEncoding encoding,
		ai::AutoBuffer<char>& buffer, ai::UnicodeString::size_type& bufferByteCount);

	/** Initializes a Unicode string from a ZString. (ZStrings are used internally
		for localization.)
			@param str The string.
			@param zStringKey The ZString key.
		*/
	AIAPI AIErr (*InitializeZString) (ai::UnicodeString& str, ZRef zStringKey);

	/* New for AI13 */

	/** Normalizes a Unicode string.
	   		@param str The string.
			@param form The normalization format.
		*/
	AIAPI AIErr (*Normalize) (ai::UnicodeString& str, ai::UnicodeString::NormalizedForm form);


} AIUnicodeStringSuite;


#include "AIHeaderEnd.h"



#endif // __AIUnicodeString__
