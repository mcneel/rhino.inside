/*************************************************************************
*
* ADOBE CONFIDENTIAL
*
* Copyright 2008 Adobe
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

#ifndef _AI_BASIC_TYPES_
#define _AI_BASIC_TYPES_

#include "ASConfig.h"

#include <stdint.h>
#include <stddef.h>

namespace ai
{
	using int8			= int8_t;
	using uint8			= uint8_t;
	using int16			= int16_t;
	using uint16		= uint16_t;
	using int32			= int32_t;
	using uint32		= uint32_t;
	using int64			= int64_t;
	using uint64		= uint64_t;

	using sizediff_t	= ptrdiff_t;
	using intptr		= intptr_t;
	using uintptr		= uintptr_t;
	using SizeType		= size_t;

} // namespace ai

#endif // _AI_BASIC_TYPES_
