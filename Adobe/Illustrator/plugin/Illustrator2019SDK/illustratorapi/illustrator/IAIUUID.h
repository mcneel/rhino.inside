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

#include "AIBasicTypes.h"

#include "AIHeaderBegin.h"

namespace ai
{
	constexpr size_t kUUID_SIZE = 16;
	
	/** Class to keep the data of UUID associated with an art object.
	Each art object keeps a unique id which remain same through out 
	the life of the object in single session.
	Utility functions to interact with UUID are provided in suite #AIUUIDSuite
	@see \c #AIUUIDSuite */
	class uuid
	{
	public:
		uuid()
		{}

		uuid(const ai::uint8 data[kUUID_SIZE])
		{
			Set(data);
		}

		void Set(const ai::uint8 data[kUUID_SIZE])
		{
			memcpy(mData, data, kUUID_SIZE);
		}

		bool operator==(const uuid &rhs) const
		{
			return (0 == memcmp(mData, rhs.mData, kUUID_SIZE));
		}

		bool operator!=(const uuid &rhs) const
		{
			return (0 != memcmp(mData, rhs.mData, kUUID_SIZE));
		}
        
		bool operator<(const uuid &rhs) const
		{
			return (0 > memcmp(mData, rhs.mData, kUUID_SIZE));
		}
		
		void Clear()
        {
            memset(mData, 0, kUUID_SIZE);
        }
		
		ai::uint8 mData[kUUID_SIZE] = { 0 };
	};
}

#include "AIHeaderEnd.h"
