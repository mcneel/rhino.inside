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

#include "IAIDataFilter.hpp"
#include "AIAssert.hpp"
#include "AIErrorHandler.h"
#include "AIContract.hpp"

#include <stdexcept>
#include <utility>
#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIDataFilter)
#elif defined (_IAIDATAFILTER_SUITE_INCLUDE_H)
	#include _IAIDATAFILTER_SUITE_INCLUDE_H
#else
	// these need to be defined by client
	extern "C" AIDataFilterSuite* sAIDataFilter;
#endif //AI_AUTO_SUITE_AVAILABLE

namespace
{
	constexpr ai::LiteralString kModeWriteStr	{ "write"	};
	constexpr ai::LiteralString kModeReadStr	{ "read"	};
	constexpr ai::LiteralString kModeAppendStr  { "append"	};
}

namespace ai
{
	//Base Data Filter class
	class BaseDataFilter : public IDataFilter
	{
	public:
		explicit BaseDataFilter(Mode mode = IDataFilter::Mode::kRead) : mMode(mode) {}

		AIDataFilter* GetFirstFilter() const AINOEXCEPT override
		{
			return mFilter;
		}

		AIDataFilter* GetFilter() const AINOEXCEPT override
		{ 
			//return the last filter in chain
			if (mNextFilter)
				return mNextFilter->GetFilter();
			return mFilter; 
		}

		AIDataFilter* ReleaseFilter() AINOEXCEPT override
		{
			auto filter = mFilter;
			mFilter = nullptr;
			return filter;
		}

		ai::LiteralString GetAIMode() const AINOEXCEPT override;
		Mode GetMode() const AINOEXCEPT override { return mMode; }

		void Read(char* store, size_t& count) override;
		void Write(const char* store, size_t count) override;
		void Seek(sizediff_t newPos) override;
		sizediff_t Mark() const override;

		void Link(std::unique_ptr<IDataFilter> nextFilter) override;

		ContentType ReadFilterContent() override;
		size_t ContentSize() override;

		virtual ~BaseDataFilter() = 0; 

		BaseDataFilter(BaseDataFilter&& other) AINOEXCEPT
		{
			swap(other);
		}

		BaseDataFilter& operator = (BaseDataFilter&& other) AINOEXCEPT
		{
			swap(other);
			return (*this);
		}

		void swap(BaseDataFilter& other) AINOEXCEPT;
		BaseDataFilter(BaseDataFilter& other) = delete;
		BaseDataFilter& operator = (const BaseDataFilter& other) = delete;

	protected:
		AIDataFilter* mFilter = nullptr;
		mutable AIErrorThrower mError = kNoErr;
		Mode mMode = Mode::kRead;
		std::unique_ptr<IDataFilter> mNextFilter;
	};

	class FileDataFilter : public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		FileDataFilter(const ai::FilePath& filePath, IDataFilter::Mode filterMode, size_t creator = 0, ai::int32 type = 0)
			:inherited(filterMode)
		{
			const auto aiMode = GetAIMode();
			mError = sAIDataFilter->NewFileDataFilter(filePath, aiMode, creator, type, &mFilter);
			mError = sAIDataFilter->LinkDataFilter(nullptr, mFilter);
		}
	};

	class ZDataFilter : public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		explicit ZDataFilter(IDataFilter::Mode filterMode)
			:inherited(filterMode)
		{
			const auto aiMode = GetAIMode();
			mError = sAIDataFilter->NewZDataFilter(aiMode, &mFilter);
		}
	};

	class A85DataFilter : public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		explicit A85DataFilter(IDataFilter::Mode filterMode, const char* prefix)
			:inherited(filterMode)
		{
			const auto aiMode = GetAIMode();
			mError = sAIDataFilter->NewA85DataFilter(aiMode, prefix, &mFilter);
		}
	};


	class BufferDataFilter : public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		BufferDataFilter(size_t buffSize)
		{
			mError = sAIDataFilter->NewBufferDataFilter(buffSize, &mFilter);
		}
	};

	class ResourceDataFilter : public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		ResourceDataFilter(SPPluginRef plugin, ai::int32 type, ai::int32 id, const char *name)
		{
			mError = sAIDataFilter->NewResourceDataFilter(plugin, type, id, name, &mFilter);
			mError = sAIDataFilter->LinkDataFilter(nullptr, mFilter);
		}
	};

	class VMDataFilter : public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		explicit VMDataFilter(size_t initialSize)
		{
			mError = sAIDataFilter->NewVMDataFilter(initialSize, &mFilter);
			mError = sAIDataFilter->LinkDataFilter(nullptr, mFilter);
		}
	};

	class BlockDataFilter :public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		BlockDataFilter(void *address, size_t size)
		{
			mError = sAIDataFilter->NewBlockDataFilter(address, size, &mFilter);
			mError = sAIDataFilter->LinkDataFilter(nullptr, mFilter);
		}
	};

	class ScopedDataFilter : public BaseDataFilter
	{
	public:
		using inherited = BaseDataFilter;
		ScopedDataFilter(AIDataFilter* filter, IDataFilter::Mode filterMode)
			: inherited(filterMode)
		{
			mFilter = filter;
			mError = sAIDataFilter->LinkDataFilter(nullptr, mFilter);
		}
	};

	ai::LiteralString BaseDataFilter::GetAIMode() const AINOEXCEPT
	{
		switch (mMode)
		{
		case Mode::kRead: return kModeReadStr;
		case Mode::kWrite: return kModeWriteStr;
		case Mode::kAppend: return kModeAppendStr;
		default:
			AIMsgAssert(false, "Invalid Data filter Mode!");
		}
		return kModeReadStr;
	}

	void BaseDataFilter::Read(char* store, size_t& count)
	{
		if (mMode != Mode::kRead)
			throw ai::Error(kInvalidFilterModeError);

		mError = sAIDataFilter->ReadDataFilter(GetFilter(), store, &count);
	}

	void BaseDataFilter::Write(const char* store, size_t count)
	{
		if (mMode != Mode::kWrite && mMode != Mode::kAppend)
			throw ai::Error(kInvalidFilterModeError);

		mError = sAIDataFilter->WriteDataFilter(GetFilter(), store, &count);
	}

	void BaseDataFilter::Seek(sizediff_t newPos)
	{
		mError = sAIDataFilter->SeekDataFilter(GetFilter(), &newPos);
	}

	ai::sizediff_t BaseDataFilter::Mark() const
	{
		ai::sizediff_t curPos(0);
		mError = sAIDataFilter->MarkDataFilter(GetFilter(), &curPos);
		return curPos;
	}

	void BaseDataFilter::Link(std::unique_ptr<IDataFilter> nextFilter)
	{
		if (mNextFilter)
			mNextFilter->Link(std::move(nextFilter));
		else
		{
			auto currentLastFilter = GetFilter(); //Call before moving the nextFilter into member
			mNextFilter = std::move(nextFilter);
			//Link the next filter chain at the end of current filter chain
			mError = sAIDataFilter->LinkDataFilter(currentLastFilter, mNextFilter->GetFirstFilter());
		}
			
	}

	ai::IDataFilter::ContentType BaseDataFilter::ReadFilterContent()
	{
		size_t localBufferSize = 0;
		IDataFilter::ContentType buffer;

		constexpr size_t kLocalBufferSize = 4 * 1024; //4K
		IDataFilter::ContentType bufferLocal(kLocalBufferSize);

		Seek(0); //Move read pointer to beginning of filter
		do
		{
			localBufferSize = kLocalBufferSize; //init local buffer size
			Read((char*)bufferLocal.data(), localBufferSize);
			if (localBufferSize)
			{
				buffer.insert(buffer.end(), bufferLocal.begin(), bufferLocal.begin() + localBufferSize);
			}
		} while (localBufferSize > 0);

		return buffer;
	}

    size_t BaseDataFilter::ContentSize() 
    {
        // Store the current pos.
        auto curPos = Mark();

        // Seek to end
        ai::sizediff_t eofPos= -1;
        Seek(eofPos);

        // Get the end of file pos.
        auto contentSize = Mark();

        // Restore the original pos.
        Seek(curPos);

        // Return the content size.
        return contentSize + 1;
    }

	BaseDataFilter::~BaseDataFilter()
	{
		if (mNextFilter)
		{
			mNextFilter.reset(); //unlink the chain first
		}

		//unlink self
		if (!mError && mFilter)
		{
			//Don't throw
			AIErr error = sAIDataFilter->UnlinkDataFilter(mFilter, &mFilter);
			if (error)
			{
				AIMsgAssert(false, "Error closing the data filter!");
			}
		}
	}

	void BaseDataFilter::swap(BaseDataFilter& other) AINOEXCEPT
	{
		std::swap(mFilter, other.mFilter);
		std::swap(mMode, other.mMode);
		std::swap(mNextFilter, other.mNextFilter);
	}

	std::unique_ptr<ai::IDataFilter> CreateFileDataFilter(
		const FilePath& filePath, 
		IDataFilter::Mode filterMode, 
		size_t creator /*= 0*/, 
		int32 type /*= 0*/, 
		std::unique_ptr<IDataFilter> nextFilter /*= nullptr */)
	{
		std::unique_ptr<ai::IDataFilter> filter (std::make_unique<FileDataFilter>(filePath, filterMode, creator, type));
		if (nextFilter && filter)
		{
			filter->Link(std::move(nextFilter));
		}
		return filter;
	}

	std::unique_ptr<ai::IDataFilter> CreateResourceDataFilter(
		SPPluginRef plugin, 
		int32 type, 
		int32 id, 
		const char *name, 
		std::unique_ptr<IDataFilter> nextFilter /*= nullptr */)
	{
		std::unique_ptr<ai::IDataFilter> filter(std::make_unique<ResourceDataFilter>(plugin, type, id, name));
		if (nextFilter && filter)
		{
			filter->Link(std::move(nextFilter));
		}
		return filter;
	}

	std::unique_ptr<ai::IDataFilter> CreateZDataFilter(
		IDataFilter::Mode filterMode, 
		std::unique_ptr<IDataFilter> nextFilter)
	{
		std::unique_ptr<ai::IDataFilter> filter(std::make_unique<ZDataFilter>(filterMode));
		if (filter && nextFilter)
		{
			filter->Link(std::move(nextFilter));
		}
		return filter;
	}

	std::unique_ptr<ai::IDataFilter> CreateA85DataFilter(
		IDataFilter::Mode filterMode, 
		const char* prefix /*= ""*/, 
		std::unique_ptr<IDataFilter> nextFilter /*= nullptr */)
	{
		std::unique_ptr<ai::IDataFilter> filter(std::make_unique<A85DataFilter>(filterMode, prefix));
		if (filter && nextFilter)
		{
			filter->Link(std::move(nextFilter));
		}
		return filter;
	}

	std::unique_ptr<ai::IDataFilter> CreateBufferDataFilter(
		size_t size, 
		std::unique_ptr<IDataFilter> nextFilter /*= nullptr */)
	{
		std::unique_ptr<ai::IDataFilter> filter(std::make_unique<BufferDataFilter>(size));
		if (filter && nextFilter)
		{
			filter->Link(std::move(nextFilter));
		}
		return filter;
	}

	std::unique_ptr<IDataFilter> CreateVMDataFilter(
		size_t initialsize,	
		std::unique_ptr<IDataFilter> nextFilter /*= nullptr*/)
	{
		std::unique_ptr<ai::IDataFilter> filter(std::make_unique<VMDataFilter>(initialsize));
		if (filter && nextFilter)
		{
			filter->Link(std::move(nextFilter));
		}
		return filter;
	}

	std::unique_ptr<ai::IDataFilter> CreateBlockDataFilter(
		void *address, 
		size_t size, 
		std::unique_ptr<IDataFilter> nextFilter /*= nullptr */)
	{
		std::unique_ptr<ai::IDataFilter> filter(std::make_unique<BlockDataFilter>(address, size));
		if (filter && nextFilter)
		{
			filter->Link(std::move(nextFilter));
		}
		return filter;
	}

	std::unique_ptr<ai::IDataFilter> CreateScopedDataFilter(
		AIDataFilter* filter, 
		IDataFilter::Mode filterMode,
		std::unique_ptr<IDataFilter> nextFilter /*= nullptr */)
	{
		ai::Expects(filter != nullptr);
		std::unique_ptr<ai::IDataFilter> scopedFilter = std::make_unique<ScopedDataFilter>(filter, filterMode);
		if (scopedFilter && nextFilter)
		{
			scopedFilter->Link(std::move(nextFilter));
		}

		return scopedFilter;
	}

	AIErr CopyDataFilter(IDataFilter& srcFilter, 
		IDataFilter& dstFilter, 
		size_t bufferSize /*= 4096*/, 
		bool seekToBegin /*= true*/)
	{
		try
		{
			ai::Expects(bufferSize > 0);

			IDataFilter::ContentType buffer(bufferSize);
			if(seekToBegin)
				srcFilter.Seek(0); //Move read pointer to the beginning of the filter

			auto readBytesCount = bufferSize;

			auto readFromFilter = [&] {
				srcFilter.Read((char*)buffer.data(), readBytesCount);
				return (readBytesCount > 0);
			};

			while ( readFromFilter() )
			{
				dstFilter.Write(buffer.data(), readBytesCount);
			}
		}
		catch (const ai::Error& error)
		{
			return error;
		}
		return kNoErr;
		
	}

} // namespace ai
