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

#include "AIDataFilter.h"
#include "IAILiteralString.h"

#include <memory>
#include <vector>

/** @file IAIDataFilter.hpp */

namespace ai
{
/**
	A stack-based wrapper class over AIDataFilterSuite 

	Prefer this class over directly accessing the AIDataFilterSuite APIs.
	Create various convenient, stack-based various data filters and link them together for different needs

	Most of the methods throw ai::Error if any error is encountered. 
	Check for AINOEXCEPT in method signature which doesn't throw any error.

	Usage Examples:
	
	Create a File Data filter
		auto dataFilter =  ai::CreateFileDataFilter(filePath, IDataFilter::Mode::kRead, 0, 0);
	
	Create a linked Zlib Compression filter for compressed write and uncompressed read
		Option 1: Link while Creation
			auto dataFilter =	ai::CreateFileDataFilter(filePath, IDataFilter::Mode::kRead, 0, 0,
									ai::CreateZDataFilter(IDataFilter::Mode::kRead)
								);

		Option 2: Link After Creation
			dataFilter->Link(ai::CreateZDataFilter(IDataFilter::Mode::kRead));

	Read from filter
		char buff[1024] = {};
		size_t buffSize(sizeof(buff));
		dataFilter->Read(buff, buffSize);

	Write to filter
		dataFilter->Write(buff, buffSize);


*/
	class IDataFilter
	{
	public:
		/** Data Filter Modes */
		enum class Mode {
			/** Read Mode */
			kRead,
			
			/** Write Mode */
			kWrite,

			/** Append Mode*/
			kAppend
		};

		enum Error : AIErr
		{
			/** If read calls are made on write/append filter or write calls are made on read filters. */
			kInvalidFilterModeError = 'IFME',
		};

		/** 
			Returns the effective AIDataFilter, use it to pass to various SDK APIs
			which requires AIDataFilter
		*/
		virtual AIDataFilter* GetFilter() const AINOEXCEPT = 0;

		/** 
			Releases and returns the effective AIDataFilter without unlinking the filter.
			This should only be used when the AIDataFilter is owned by another IDataFilter.
		*/
		virtual AIDataFilter* ReleaseFilter() AINOEXCEPT = 0;

		/** 
			Returns the first filter in this chain, don't use it in a normal case.
			It is used to chain two filter chains together
		*/
		virtual AIDataFilter* GetFirstFilter() const AINOEXCEPT = 0;

		/** 
			Returns filter mode to be passed on to AIDataFilter APIs
		*/
		virtual ai::LiteralString GetAIMode() const AINOEXCEPT = 0;

		/** 
			Returns the filter mode enum value
		*/
		virtual Mode GetMode() const AINOEXCEPT = 0;

		/** 
			#AIDataFilterSuite::ReadDataFilter
		*/
		virtual void Read(char* store, size_t& count) = 0;

		/** 
			#AIDataFilterSuite::WriteDataFilter
		*/
		virtual void Write(const char* store, size_t count) = 0;

		/**
			#AIDataFilterSuite::SeekDataFilter
		*/
		virtual void Seek(sizediff_t newPos) = 0;

		/** 
			#AIDataFilterSuite::MarkDataFilter
		*/
		virtual sizediff_t Mark() const = 0;

		using ContentType = std::vector<char>;
		/** 
			Returns the entire content of the filter. Use it only for small files.
			When the entire content of the filter can be read in a continuous dynamic memory.
		*/
		virtual ContentType ReadFilterContent() = 0;

		/** 
			Returns the size of the content in bytes.
			The size gets computed with forward and backward seeking. Not all DataFilter support seeking.
		*/
		virtual size_t ContentSize() = 0;

		/** 
			Link a new data filter to the current chain. 
			No need to specifically unlink. Unlink is called in the destructor
			#AIDataFilterSuite::LinkDataFilter
		*/
		virtual void Link(std::unique_ptr<IDataFilter> nextFilter) = 0;

		virtual ~IDataFilter() = default;
	};
	
	/** Create a stack-based File Data Filter. 
		#AIDataFitlerSuite::NewFileDataFilter() 
		auto fileFilter = CreateFileDataFilter(filePath, IDataFilter::Mode::kWrite);
		fileFilter->Write(buff, buffsize);

		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/
	std::unique_ptr<IDataFilter> CreateFileDataFilter(
		const ai::FilePath& filePath,
		IDataFilter::Mode filterMode,
		size_t creator = 0,
		ai::int32 type = 0,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/** Create a stack-based Resource Data Filter.
		#AIDataFitlerSuite::NewResourceDataFilter()
		
		auto filter = CreateResourceDataFilter(plugin, 'TEXT', id, resName, IDataFilter::Mode::kRead);
		
		char buff[1024] = {};
		size_t buffSize(sizeof(buff));
		filter->Read(buff, buffSize);

		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/
	std::unique_ptr<IDataFilter> CreateResourceDataFilter(
		SPPluginRef plugin, 
		ai::int32 type, 
		ai::int32 id, 
		const char *name,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/** Create a stack-based Zlib Data Filter. Normally linked to other filters in the chain
		to provide zlib compression/decompression
		#AIDataFitlerSuite::NewZDataFilter()
		
		//Write compressed content to a file
		auto dataFilter =	ai::CreateFileDataFilter(filePath, IDataFilter::Mode::kWrite, 0, 0,
									ai::CreateZDataFilter(IDataFilter::Mode::kWrite)
								);
								
		dataFilter->Write(buff, buffsize);

		//Read uncompressed content from a file
		auto dataFilter =	ai::CreateFileDataFilter(filePath, IDataFilter::Mode::kRead, 0, 0,
									ai::CreateZDataFilter(IDataFilter::Mode::kRead)
								);
								
		char buff[1024] = {};
		size_t buffSize(sizeof(buff));
		dataFilter->Read(buff, buffSize);
		
		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/
	std::unique_ptr<IDataFilter> CreateZDataFilter(
		IDataFilter::Mode filterMode,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/** Create a stack-based A85 Data Filter. Normally linked to other filters in the chain
		to provide ASCII85 compression/decompression
		#AIDataFitlerSuite::NewA85DataFilter()

		//Write compressed content to a file
		auto dataFilter =	ai::CreateFileDataFilter(filePath, IDataFilter::Mode::kWrite, 0, 0,
			ai::CreateA85DataFilter(IDataFilter::Mode::kWrite)
		);

		dataFilter->Write(buff, buffsize);

		//Read uncompressed content from a file
		auto dataFilter =	ai::CreateFileDataFilter(filePath, IDataFilter::Mode::kRead, 0, 0,
			ai::CreateA85DataFilter(IDataFilter::Mode::kRead)
		);

		char buff[1024] = {};
		size_t buffSize(sizeof(buff));
		dataFilter->Read(buff, buffSize);

		prefix [in] The string to insert at the start of each line.
		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/
	std::unique_ptr<IDataFilter> CreateA85DataFilter(
		IDataFilter::Mode filterMode,
		const char* prefix = nullptr,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/** Create a stack-based buffered Data Filter. Normally linked to other filters in the chain
		to provide buffered read/write for better performance
		#AIDataFitlerSuite::NewBufferDataFilter()
		
		//Bufferred file data filter
		auto dataFilter =	ai::CreateFileDataFilter(filePath, IDataFilter::Mode::kWrite, 0, 0,
									CreateBufferDataFilter(4096)
								);

		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/
	std::unique_ptr<IDataFilter> CreateBufferDataFilter(
		size_t size,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/** Create a stack-based VM Data Filter. 
		#AIDataFitlerSuite::NewVMDataFilter()
		
		auto filter = CreateVMDataFilter(4096);

		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/
	std::unique_ptr<IDataFilter> CreateVMDataFilter(
		size_t initialSize,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/** Create a stack-based Block Data Filter.
		#AIDataFitlerSuite::NewBlockDataFilter()
		
		char* srcBuffer; //received from somewhere
		size_t sizeOfBuffer; //received from somewhere
		
		auto filter = CreateBlockDataFilter(srcBuffer, sizeOfBuffer);

		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/
	std::unique_ptr<IDataFilter> CreateBlockDataFilter(
		void *address, 
		size_t size,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/**
		Create a stack-based data filter from an existing  AIDataFilter*. 
		It will automatically be unlinked when the scope end.

		@param filter - Filter to be wrapped in the stacked object
		nextFilter [in] Next filter in the chain. Equivalent to calling Link() after filter creation.
	*/

	std::unique_ptr<IDataFilter> CreateScopedDataFilter(
		AIDataFilter* filter,
		IDataFilter::Mode filterMode,
		std::unique_ptr<IDataFilter> nextFilter = nullptr
	);

	/** 
		Copies contents from the source data filter to the destination data filter.
		
		@param srcFilter	- Filter to copy the data from
		@param dstFilter	- Filter to copy the data to
		@param bufferSize	- Buffer size to be used for copying the data
		@param seekToBegin  - Whether the source filter's read location should be reset to the beginning before creating a copy

		example:
			ai::FilePath filePath(ai::UnicodeString::FromRoman("MyZCompressedFile.txt"));

			auto dataFilter = ai::CreateFileDataFilter(filePath, ai::IDataFilter::Mode::kRead, 0, 0,
				ai::CreateZDataFilter(ai::IDataFilter::Mode::kRead)
			);

			ai::FilePath filePathOut(ai::UnicodeString::FromRoman("MyUncompressedFile.txt"));
			auto dataFilterOut = ai::CreateFileDataFilter(filePathOut, ai::IDataFilter::Mode::kWrite);

			ai::CopyDataFilter(*dataFilter, *dataFilterOut);
	*/
	AIErr CopyDataFilter(IDataFilter& srcFilter, IDataFilter& dstFilter, size_t bufferSize = 4096, bool seekToBegin = true);
	

} //namespace ai