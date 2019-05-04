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

#ifdef _MSC_VER

#if (_MSC_VER >= 1600) // VC++ 10 (aka 2010)
#define AI_HAS_NULLPTR
#define AI_HAS_STATIC_ASSERT
#define AI_HAS_RVALUE_REFERENCES
#define AI_HAS_LAMBDAS
#endif 

#if (_MSC_FULL_VER >= 180020827) // VC++ 12 (aka 2013)
#define AI_HAS_DELETED_FUNCTIONS
#define AI_HAS_EXPLICIT_CONVERSION_OPERATORS
#endif

#if (_MSC_FULL_VER >= 190023026) // VC++ 14 (aka 2015)
// NOTE: Even though defaulted functions are supported with VC++ 12, but the use of = default to request
// member-wise move constructors and move assignment operators is not supported.
#define AI_HAS_DEFAULTED_FUNCTIONS
#define AI_HAS_NOEXCEPT
#define AI_HAS_RETURN_TYPE_DEDUCTION
#endif

#endif // _MSC_VER

#endif // __cplusplus