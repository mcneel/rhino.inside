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

#ifdef __cplusplus

#ifdef __clang__

// Identify libc++ vs libstdc++
#if __has_include(<ciso646>)
#include <ciso646>
#if defined(_LIBCPP_VERSION)
#define AI_LIBCPP 1		// libc++
#endif
#endif

#if !AI_LIBCPP
#define AI_LIBSTDCXX 1	// libstdc++
#endif

#if AI_LIBCPP && __has_feature(cxx_nullptr)
#define AI_HAS_NULLPTR
#endif

#if __has_feature(cxx_static_assert)
#define AI_HAS_STATIC_ASSERT
#endif

#if AI_LIBCPP && __has_feature(cxx_rvalue_references)
#define AI_HAS_RVALUE_REFERENCES
#endif

#if __has_feature(cxx_lambdas)
#define AI_HAS_LAMBDAS
#endif

#if __has_feature(cxx_defaulted_functions)
#define AI_HAS_DEFAULTED_FUNCTIONS
#endif

#if __has_feature(cxx_deleted_functions)
#define AI_HAS_DELETED_FUNCTIONS
#endif

#if __has_feature(cxx_explicit_conversions)
#define AI_HAS_EXPLICIT_CONVERSION_OPERATORS
#endif

#if __has_feature(cxx_noexcept)
#define AI_HAS_NOEXCEPT
#endif

#if __has_feature(cxx_return_type_deduction)
#define AI_HAS_RETURN_TYPE_DEDUCTION
#endif

#endif // __clang__

#endif // __cplusplus