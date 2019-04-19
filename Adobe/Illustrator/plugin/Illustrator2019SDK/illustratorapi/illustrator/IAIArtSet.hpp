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

#include "AIArtSet.h"
#include "IAIArtboards.hpp"
#include "IAIUnicodeString.h"

#include <memory>

/** @file IAIArtSet.hpp */

namespace ai
{
	/**
	A stack based wrapper class over AIArtSetSuite and AIArtSetGeneratorSuite

	Prefer this class over directly accessing the AIArtSetSuite/AIArtSetGeneratorSuite APIs.

	Usage Examples:

	Construction:

		CAUTION: Constructor would throw if artSet was not constructed properly
	
		1. Default Construct, creates an ai::ArtSet object, ready for actions such as insert, remove, and replace 

			ai::ArtSet artSet;

		2. Construct an ai::ArtSet object, filled with all the selected art objects

			ai::ArtSet artSet(true);

		3. Construct an ai::ArtSet object, filled with all the objects on a layer
		
			ai::ArtSet artSet(layerHandle);

		4. Construct an ai::ArtSet object, filled with an existing array of AIArtHandle(s)

			ai::ArtSet artSet(artHandles, count);

		5. Construct an ai::ArtSet object, filled with all the art objects, matched to AIArtSpec

			AIArtSpec spec = { kAnyArt, kArtFullySelected, kArtFullySelected  };
			ai::ArtSet artSet(spec);

		6. Construct an ai::ArtSet object, filled with all the art objects matching an array of AIArtSpec

			AIArtSpec specs = {
				{kRasterArt, kArtSelected, kArtSelected},
				{kPlacedArt, kArtSelected, kArtSelected},
			};

			ai::ArtSet artSet(specs);

	Query: Wraps all the query APIs from AIArtSetGeneratorSuite, few examples, 
		1. To create an ArtSet filled with all non-hidden objects on artboard 1

			ai::ArtSet artSet
			auto err = artSet.GenerateForNthArtboard(1, true);
			for(auto art :artSet)
			{
			   //art
			}

		2. To create an ArtSet filled with all objects on the 0th layer
			
			ai::ArtSet artSet
			auto err = artSet.GenerateForNthLayer(0);
			for(auto art :artSet)
			{
				//art
			}

	Accessors: 
		1. C++ 11 range based loop

			for(auto art : artSet)
			{
				//access art
			}

		2. reverse iterate

			for (auto iter = artSet.rbegin(); iter != artSet.rend(); ++iter)
			{
				auto art = *iter;
			}

		3. Get AIArtSet to be passed to APIs which need an AIArtSet

			AIArtSet aiArtSet = artSet.get();

		4. See if the last operation was successful, or the object was successfully constructed

			if(artSet)
			{
				//artSet was constructed successfully, proceed with other operations
			}

		5. Need to pass the AIErr 

			AIErr err = artSet.GetLastError();

	Mutators:

		1. Insert an AIArtHandle

			artSet.insert(art);

		2. Remove an AIArtHandle

			artSet.erase(art);

		3. Replace an AIArtHandle with another

			artSet.replace(oldArt, newArt);

		4. Clear 

			artSet.clear();

*/
	class ArtSet
	{
	public:
		class iterator;

		using value_type = AIArtHandle;

		/** Default constructor, fill with selected art objects when true is passed
		*/
		explicit ArtSet(bool fillWithSelectedArtObjects = false); 

		/** Create ArtSet from art handle array
		*/
		explicit ArtSet(AIArtHandle *artArray, size_t count); 
		
		/** Fill all objects from layer
		*/
		explicit ArtSet(AILayerHandle layer); 

		/** Construct with spec array
		*/
		template<std::size_t N>
		ArtSet(const AIArtSpec(&specs)[N]) : ArtSet(&specs[0], N)
		{

		}

		/** Construct with one Spec
		*/
		ArtSet(const AIArtSpec& spec) :ArtSet(&spec, 1) {}

		//Needed for unique_ptr
		~ArtSet();

		/**
			#AIArtSetGeneratorSuite::GenerateForAllLayers() 
		*/
		AIErr GenerateForAllLayers();
		
		/** 
			#AIArtSetGeneratorSuite::GenerateForNthLayer() 
		*/
		AIErr GenerateForNthLayer(ai::int32 inLayerIndex);
		
		/** 
			#AIArtSetGeneratorSuite::GenerateForNamedLayer() 
		*/
		AIErr GenerateForNamedLayer(const ai::UnicodeString& inLayerName);
		
		/** 
			#AIArtSetGeneratorSuite::GenerateForNthArtboard() 
		*/
		AIErr GenerateForNthArtboard(ai::ArtboardID inArtboardIndex, bool skipHiddenArts);
		
		/** 
			#AIArtSetGeneratorSuite::GenerateForNamedArtboard() 
		*/
		AIErr GenerateForNamedArtboard(const ai::UnicodeString& inArtboardName, bool skipHiddenArts);
		
		/** 
			#AIArtSetGeneratorSuite::GenerateForTopLevelLayers() 
		*/
		AIErr GenerateForTopLevelLayers(bool skipHiddenLayers);

		/**
		#AIArtSetGeneratorSuite::GenerateSelectedArtsForAllLayers()
		*/
		AIErr GenerateSelectedAtTopLevel();
        
        /** Generates the ArtSet with the art provided. Traverses the art handle provided
         and fills the ArtSet with all the nested children of the group art.
         #AIArtSetGeneratorSuite::GenerateForArt()
         */
        AIErr GenerateForArt (AIArtHandle inArt);
		
		/** Returns number of AIArtHandle in the ArtSet
		*/
		size_t size() const AINOEXCEPT;
		
		/** Returns true if ArtSet is empty
		*/
		bool empty() const AINOEXCEPT { return size() == 0; }
		
		/** Returns AIArtHandle stored in index. Throws exception if out of bounds.
		*/
		value_type at(size_t index) const;
		
		/** Returns AIArtHandle stored in index. Returns nullptr if out of bounds.
		*/
		value_type operator[](size_t index) const AINOEXCEPT;

		/** Inserts into ArtSet if not already present.
		*/
		void insert(value_type art);
		
		/** Removes an AIArtHandle from ArtSet if present.
		*/
		void erase(value_type art);
		
		/** Replaces an AIArtHandle with another in the ArtSet.
		*/
		void replace(value_type oldArt, value_type newArt);
		
		/** Removes all elements from an ArtSet.
		*/
		void clear();

		/** Range iterator support 
		*/
		iterator begin() const AINOEXCEPT;
		
		/** Range iterator support 
		*/
		iterator end() const AINOEXCEPT;
		
		/** Reverse iterator support 
		*/
		iterator rbegin() const AINOEXCEPT;
		
		/** Reverse iterator support 
		*/
		iterator rend() const AINOEXCEPT;

		/** Swaps the content with another ArtSet 
		*/
		void swap(ArtSet& other) AINOEXCEPT;

		/** Returns true if the ArtSet has some elements and last call to fill ArtSet was successful.
		*/
		explicit operator bool() const AINOEXCEPT;
		
		/** Returns the AIErr given back in the in last call to fill the ArtSet.
		*/
		AIErr GetLastError() const AINOEXCEPT;

		/** Returns AIArtSet for APIs that need access to AIArtSet
		*/
		AIArtSet get() const AINOEXCEPT;

		/** Move constructor 
		*/ 
		ArtSet(ArtSet&& other) AINOEXCEPT;
		
		/** Move assignment
		*/
		ArtSet& operator = (ArtSet&& other) AINOEXCEPT;

	private:
		ArtSet(const AIArtSpec* specs, size_t count);
		ArtSet(const ArtSet&) = delete;
		ArtSet& operator = (const ArtSet&) = delete;

		class Impl;
		std::unique_ptr<Impl> pImpl;
	};

	class ArtSet::iterator
	{
	public:
		using value_type = AIArtHandle;
		
		iterator(const ArtSet& artSet, ptrdiff_t index, bool reverse = false) :
			mArtSet(artSet), mIndex(index),mReverse(reverse)
		{
			mCount = mArtSet.size();
		}
		value_type operator*() const
		{
			if (mIndex >= 0 && mIndex < mCount)
			{
				if(mValue == nullptr)
					mValue = mArtSet[mIndex];
				return mValue;
			}
			return nullptr;
		}

		void operator++()
		{
			if (mReverse)
				--mIndex;
			else
				++mIndex;
			mValue = nullptr;
		}

		void operator--()
		{
			if (mReverse)
				++mIndex;
			else
				--mIndex;
			mValue = nullptr;
		}

		bool operator!= (const iterator& other) const
		{
			return (mIndex != other.mIndex || mArtSet.pImpl.get() != other.mArtSet.pImpl.get());
		}

		iterator(const iterator&) = default;
		iterator(iterator&&) = default;
		iterator& operator = (const iterator&) = default;
		iterator& operator = (iterator&&) = default;

	private:
		ptrdiff_t mIndex = 0;
		ptrdiff_t mCount = 0;
		mutable value_type mValue = nullptr;
		const ArtSet& mArtSet;
		bool mReverse = false;
	};
}
