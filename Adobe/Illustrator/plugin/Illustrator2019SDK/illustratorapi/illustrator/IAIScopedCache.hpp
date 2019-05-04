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

#include "AIErrorHandler.h"
#include <memory>

/** @file IAIScopedCache.hpp */

namespace ai
{

	/**
		BooleanAttributeCache:	A class to store boolean attributes.
								Attributes are generally specified via some
								enumeration. Storage of each attribute value
								inside the cache is in a single bit. Additional
								storage contains another bit per attribute to
								indicate initialization status.
	
		Sample usage:
	
		enum class DocumentState : ai::uint8
		{ kUnsaved = 0, kInIsolationMode = 1, ... kUsingSpotColor = 30 };
	
		using BitStorage = ai::uint32;	// Large enough to hold 1 bit for each
										// value in enumeration above.
	
		using DocAttrCache = BooleanAttributeCache <DocumentState, BitStorage>;
	
		using DocAttrCacheScopeManager = ai::CacheScopeManager <DocAttrCache>;
		DocAttrCacheScopeManager cacheScope;
	
		...
	
		bool docIsUnsaved{ false }, docIsInIsolationMode{ false };
	
		if (DocAttrCacheScopeManager::IsCacheValid())
		{
			if (DocAttrCacheScopeManager::GetCache()->GetValue(DocumentState::kUnsaved, docIsUnsaved) == false)
			{
				// Compute and cache value
				docIsUnsaved = ComputeDocIsUnsaved();
				MyCacheScopeManager::GetCache()->SetValue(DocumentState::kUnsaved, docIsUnsaved);
			}
	
			if (DocAttrCacheScopeManager::GetCache()->GetValue(DocumentState::kInIsolationMode, docIsInIsolationMode) == false)
			{
				// Compute and cache value
				docIsInIsolationMode = ComputeDocIsInIsolationMode();
				MyCacheScopeManager::GetCache()->SetValue(DocumentState::kInIsolationMode, docIsInIsolationMode);
			}
		}
		else
		{
			// Compute
			docIsUnsaved = ComputeDocIsUnsaved();
			docIsInIsolationMode = ComputeDocIsInIsolationMode();
	
			// Do not store as cache is invalid
		}
	
		// Use values
		Print(docIsUnsaved);
		Print(docIsInIsolationMode);
	*/
	template <typename Attribute_t, typename Bit_t>
	class BooleanAttributeCache
	{
	public:
		// If cached value is found, retrieves it and returns true.
		// Otherwise returns false.
		bool GetValue(Attribute_t inAttr, bool& outValue) const AINOEXCEPT
		{
			const auto initialized = IsInitialized(inAttr);
			if (initialized)
			{
				outValue = ((fAttrBits & AttributeToBits(inAttr)) ? true : false);
			}
			return initialized;
		}
		void SetValue(Attribute_t inAttr, const bool inValue) AINOEXCEPT
		{
			const auto flagBit = AttributeToBits(inAttr);
			if (inValue)
			{
				fAttrBits |= flagBit;
			}
			else
			{
				fAttrBits &= ~flagBit;
			}
			fInitBits |= flagBit;
		}
		void Clear() AINOEXCEPT
		{
			fInitBits = fAttrBits = 0;
		}

	private:
		bool IsInitialized(Attribute_t inAttr) const AINOEXCEPT
		{
			return ((fInitBits & AttributeToBits(inAttr)) ? true : false);
		}
		Bit_t AttributeToBits(Attribute_t inAttr) const AINOEXCEPT
		{
			return (1 << static_cast<Bit_t>(inAttr));
		}

	private:
		Bit_t fAttrBits{ 0 }, fInitBits{ 0 };
	};


	/**
		CacheScopeManager:	Instantiate this class to ensure a valid Cache.
							CacheScopeManager instances can be safely nested as
							only one Cache object is created even if multiple
							CacheScopeManager objects exist. The Cache object is
							deleted when the last CacheScopeManager destructs.
							The Cache template parameter can be either one or
							a combination of the above cache classes or any
							other class which can be created and destroyed by
							this class.
							
		Sample usage:

		using MyAttribCache = BooleanAttributeCache <DocumentState, ai::unt8>;
		using MyCacheScopeManager = CacheScopeManager <MyAttribCache>;
	*/	
	template <typename Cache_t>
	class CacheScopeManager
	{
	public:
		CacheScopeManager() : CacheScopeManager{ false } {}
		virtual ~CacheScopeManager()
		{
			try
			{
				if (fSuppressor)
				{
					if (CacheSuppressCount() == 1 && CacheRefCount() != 0)
					{
						Cache() = std::make_unique<Cache_t>();
						--CacheSuppressCount();
					}
				}
				else
				{
					if (CacheSuppressCount() == 0 && CacheRefCount() == 1)
					{
						Cache().reset();
						--CacheRefCount();
					}
				}
			}
			AI_CATCH_ASSERT_NO_RETURN
		}

		static bool IsCacheValid() AINOEXCEPT
		{
			return GetCache() != nullptr;
		}

		static Cache_t* GetCache() AINOEXCEPT
		{
			return Cache().get();
		}

	protected:
		CacheScopeManager(bool suppressor) : fSuppressor{ suppressor }
		{
			if (fSuppressor)
			{
				if (CacheSuppressCount() == 0 && CacheRefCount() != 0)
				{
					Cache().reset();
					++CacheSuppressCount();
				}
			}
			else
			{
				if (CacheSuppressCount() == 0 && CacheRefCount() == 0)
				{
					Cache() = std::make_unique<Cache_t>();
					++CacheRefCount();
				}
			}
		}

	private:
		static std::unique_ptr <Cache_t>& Cache()
		{
			static std::unique_ptr <Cache_t> sCache;
			return sCache;
		}

		static size_t& CacheRefCount() AINOEXCEPT
		{
			static size_t sCacheRefCount{ 0 };
			return sCacheRefCount;
		}

		static size_t& CacheSuppressCount() AINOEXCEPT
		{
			static size_t sCacheSuppressCount{ 0 };
			return sCacheSuppressCount;
		}

	private:
		const bool fSuppressor;
	};

	/**
		CacheScopeSuppressor:	Prevents caching in a scope.
								This invalidates cache which may have been
								created by CacheScopeManager of the same type
								and prevents further caching of that type even
								if new instances of CacheScopeManager are
								created.
								CacheScopeSuppressor instances can be safely
								nested.
								When the last CacheScopeSuppressor goes out of
								scope and we have at least one CacheScopeManager
								still in scope, caching is resumed but the cache
								is empty and is not restored to the old value
								before the first CacheScopeSuppressor came in
								scope.
	*/	
	template <typename Cache_t>
	class CacheScopeSuppressor : public CacheScopeManager <Cache_t>
	{
	public:
		CacheScopeSuppressor() : CacheScopeManager <Cache_t> { true } {}
	};

}	// namespace ai
