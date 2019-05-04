/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2017 Adobe
* 
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

#include "AITypes.h"

#include <cstddef>
#include <stdexcept>
#include <cstring>

namespace ai
{
	/**
	* String Literal Class
	* --------------------
	*  Replacement for:
	*       const char* const kWidgetId = "SomeMagicString";
	*
	*  How to create:
	*       constexpr ai::LiteralString kWidgetId {"WidgetName"};
	*       constexpr ai::LiteralString kWidgetId = "WidgetName";
	*
	*  When to use:
	*       To specify placeholders for magic strings for which we generally use const char* const ...
	*
	*  Why to use:
	*       - When a constexpr object is created with a string literal which is a constant expression (e.g. magic strings), there is:
	*           - No runtime overhead for creation
	*           - Size is known at compile time
	*           - Implicit conversion to const char* when you need to call a function that expects const char*
	*
	*  NOTE:
	*       - You can compare two constexpr ai::LiteralString at compile time.
	*       - However, you can compare LiteralString with const char* with std::strcmp only at runtime.
	***/

	namespace details
	{
		constexpr bool compare_less(const char* str1, std::size_t len1, const char* str2, std::size_t len2) AINOEXCEPT
		{
			return (len2 == 0)		? false :
				   (len1 == 0)		? true :
				   (*str1 != *str2) ? (*str1 < *str2) : 
				   compare_less(str1 + 1, len1 - 1, str2 + 1, len2 - 1);
		}

		constexpr bool compare_equal(const char* str1, std::size_t len1, const char* str2, std::size_t len2) AINOEXCEPT
		{
			return (len1 == 0 && len2 == 0) ? true :
				   (len1 == 0 || len2 == 0) ? false :
				   (*str1 != *str2)			? false :
				   compare_equal(str1 + 1, len1 - 1, str2 + 1, len2 - 1);
		}

	} // namespace details


	class LiteralString
	{
	public:
		using const_iterator = const char*;

		template<std::size_t N>
		constexpr LiteralString(const char(&arr)[N]) AINOEXCEPT : str{arr}, len{N - 1} 
		{
			static_assert(N >= 1, "not a string literal");
		}
    
		constexpr char operator[](std::size_t i) const 
		{
    		return i < len ? str[i] : throw std::out_of_range{""}; 
		}
    
		constexpr std::size_t size() const AINOEXCEPT { return len; }
		
		/** Implicit conversion to const char*
		*/
		constexpr operator const char*() const AINOEXCEPT { return str; } 

		/** Use c_str() when implicit conversion is not applicable. For example, you can use this string in cases such as
			template argument deduction
		*/
		constexpr const char* c_str() const AINOEXCEPT { return str; }

		/** Support for range based loops
		*/
		constexpr const_iterator begin() const AINOEXCEPT { return str; }
		
		/** Support for range based loops
		*/
		constexpr const_iterator end() const AINOEXCEPT { return str + len; }

	private:
		const char* const str;
		const std::size_t len;
	};

	/** Lexicographical comparison
	*/
	inline constexpr bool operator<(ai::LiteralString lhs, ai::LiteralString rhs) AINOEXCEPT
	{
		return details::compare_less(lhs, lhs.size(), rhs, rhs.size());
	}

	/** Lexicographical comparison
	*/
	inline constexpr bool operator>(ai::LiteralString lhs, ai::LiteralString rhs) AINOEXCEPT
	{
		return (rhs < lhs);
	}

	inline constexpr bool operator==(ai::LiteralString lhs, ai::LiteralString rhs) AINOEXCEPT
	{
		return details::compare_equal(lhs, lhs.size(), rhs, rhs.size());
	}

	inline bool operator==(ai::LiteralString lhs, const char* rhs)
	{
		return (std::strcmp(lhs.c_str(), rhs) == 0);
	}

	inline bool operator==(const char* lhs, ai::LiteralString rhs)
	{
		return (rhs == lhs);
	}

	constexpr ai::LiteralString kEmptyLiteralString { "" };

} // namespace ai