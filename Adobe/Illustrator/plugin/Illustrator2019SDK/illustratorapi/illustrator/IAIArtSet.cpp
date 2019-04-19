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

#include "IAIArtSet.hpp"
#include "AIArtSetGenerator.h"
#include "AIContract.hpp"

#include <stdexcept>

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIArtSet)
	use_suite(AIArtSetGenerator)
#elif defined (_IAIARTSET_SUITE_INCLUDE_H)
	#include _IAIARTSET_SUITE_INCLUDE_H
#else
	// these need to be declared by client
	extern "C" AIArtSetSuite* sAIArtSet;
	extern "C" AIArtSetGeneratorSuite* sAIArtSetGenerator;
#endif

namespace ai
{
	class ArtSet::Impl
	{
	public:
		using value_type = ArtSet::value_type;
		Impl();
		~Impl();

		explicit Impl(bool fillWithSelectedArtObjects);
		explicit Impl(AIArtHandle *artArray, size_t count);
		explicit Impl(AILayerHandle layer);
		explicit Impl(const AIArtSpec* spec, size_t count);

		//Query APIs
		AIErr GenerateForAllLayers();
		AIErr GenerateForNthLayer(ai::int32 inLayerIndex);
		AIErr GenerateForNamedLayer(const ai::UnicodeString& inLayerName);
		AIErr GenerateForNthArtboard(ai::ArtboardID inArtboardIndex, bool skipHiddenArts);
		AIErr GenerateForNamedArtboard(const ai::UnicodeString& inArtboardName, bool skipHiddenArts);
		AIErr GenerateForTopLevelLayers(bool skipHiddenLayers);
		AIErr GenerateSelectedAtTopLevel();
        AIErr GenerateForArt (AIArtHandle inArt);

		size_t size() const AINOEXCEPT;
		value_type at(size_t index) const;
		value_type operator[](size_t index) const AINOEXCEPT;

		void insert(value_type art);
		void erase(value_type art);
		void replace(value_type oldArt, value_type newArt);
		void clear();

		AIArtSet get() const AINOEXCEPT { return mArtSet; }
		AIErr GetLastError() const AINOEXCEPT { return mLastError; }

		explicit operator bool() const AINOEXCEPT
		{
			return (mLastError == kNoErr && mArtSet != nullptr);
		}
	private:
		AIArtSet mArtSet = nullptr;
		mutable AIErr mLastError = kNoErr;
	};

	ArtSet::Impl::Impl(bool fillWithSelectedArtObjects):Impl()
	{
		if (fillWithSelectedArtObjects)
		{
			mLastError = sAIArtSet->SelectedArtSet(mArtSet);
			check_ai_error(mLastError);
		}
	}

	ArtSet::Impl::Impl(AIArtHandle *artArray, size_t count):Impl()
	{
		mLastError = sAIArtSet->ArrayArtSet(mArtSet, artArray, count);
		check_ai_error(mLastError);
	}

	ArtSet::Impl::Impl(AILayerHandle layer):Impl()
	{
		mLastError = sAIArtSet->LayerArtSet(layer, mArtSet);
		check_ai_error(mLastError);
	}

	ArtSet::Impl::Impl(const AIArtSpec* specs, size_t count):Impl()
	{
		mLastError = sAIArtSet->MatchingArtSet(const_cast<AIArtSpec*>(specs), static_cast<ai::int16>(count), mArtSet);
		check_ai_error(mLastError);
	}

	ArtSet::Impl::Impl()
	{
		AIErr err = sAIArtSet->NewArtSet(&mArtSet);
		check_ai_error(err);
		ai::Ensures(mArtSet != nullptr);
	}

	ArtSet::Impl::~Impl()
	{
		sAIArtSet->DisposeArtSet(&mArtSet);
	}

	size_t ArtSet::Impl::size() const AINOEXCEPT
	{
		size_t count(0);
		mLastError = sAIArtSet->CountArtSet(mArtSet, &count);
		if (!mLastError)
			return count;

		return 0;
	}

	ArtSet::Impl::value_type ArtSet::Impl::at(size_t index) const
	{
		const auto count = size();
		ai::Expects(index >= count);
		
		AIArtHandle artHandle(nullptr);
		mLastError = sAIArtSet->IndexArtSet(mArtSet, index, &artHandle);
		check_ai_error(mLastError);
		return artHandle;
	}

	ArtSet::Impl::value_type ArtSet::Impl::operator[](size_t index) const AINOEXCEPT
	{
		AIArtHandle artHandle(nullptr);
		mLastError = sAIArtSet->IndexArtSet(mArtSet, index, &artHandle);
		if (!mLastError)
			return artHandle;

		//TODO: Assert
		return nullptr;
	}

	void ArtSet::Impl::insert(ArtSet::Impl::value_type art)
	{
		mLastError = sAIArtSet->AddArtToArtSet(mArtSet, art);
		check_ai_error(mLastError);
	}

	void ArtSet::Impl::erase(value_type art)
	{
		mLastError = sAIArtSet->RemoveArtFromArtSet(mArtSet, art);
		check_ai_error(mLastError);
	}

	void ArtSet::Impl::replace(ArtSet::Impl::value_type oldArt, ArtSet::Impl::value_type newArt)
	{
		mLastError = sAIArtSet->ReplaceArtInArtSet(mArtSet, oldArt, newArt);
		check_ai_error(mLastError);
	}

	void ArtSet::Impl::clear()
	{
		mLastError = sAIArtSet->ClearArtSet(mArtSet);
		check_ai_error(mLastError);
	}

	AIErr ArtSet::Impl::GenerateForAllLayers()
	{
		mLastError = sAIArtSetGenerator->GenerateForAllLayers(mArtSet);
		return mLastError;
	}

	AIErr ArtSet::Impl::GenerateForNthLayer(ai::int32 inLayerIndex)
	{
		mLastError = sAIArtSetGenerator->GenerateForNthLayer(inLayerIndex, mArtSet);
		return mLastError;
	}

	AIErr ArtSet::Impl::GenerateForNamedLayer(const ai::UnicodeString& inLayerName)
	{
		mLastError = sAIArtSetGenerator->GenerateForNamedLayer(inLayerName, mArtSet);
		return mLastError;
	}

	AIErr ArtSet::Impl::GenerateForNthArtboard(ai::ArtboardID inArtboardIndex, bool skipHiddenArts)
	{
		mLastError = sAIArtSetGenerator->GenerateForNthArtboard(inArtboardIndex, mArtSet, skipHiddenArts);
		return mLastError;
	}

	AIErr ArtSet::Impl::GenerateForNamedArtboard(const ai::UnicodeString& inArtboardName, bool skipHiddenArts)
	{
		mLastError = sAIArtSetGenerator->GenerateForNamedArtboard(inArtboardName, mArtSet, skipHiddenArts);
		return mLastError;
	}

	AIErr ArtSet::Impl::GenerateForTopLevelLayers(bool skipHiddenLayers)
	{
		mLastError = sAIArtSetGenerator->GenerateForTopLevelLayers(mArtSet, skipHiddenLayers);
		return mLastError;
	}

	AIErr ArtSet::Impl::GenerateSelectedAtTopLevel()
	{
		mLastError = sAIArtSetGenerator->GenerateSelectedAtTopLevel(mArtSet);
		return mLastError;
	}

    AIErr ArtSet::Impl::GenerateForArt (AIArtHandle inArt)
    {
        mLastError = sAIArtSetGenerator->GenerateForArt(inArt, mArtSet);
        return mLastError;
    }

	ArtSet::ArtSet(bool fillWithSelectedArtObjects /*= false*/)
		: pImpl{std::make_unique<Impl>(fillWithSelectedArtObjects)}
	{
	}

	ArtSet::ArtSet(AIArtHandle *artArray, size_t count)
		: pImpl{std::make_unique<Impl>(artArray, count)}
	{
	}

	ArtSet::ArtSet(AILayerHandle layer)
		: pImpl{std::make_unique<Impl>(layer)}
	{
	}

	ArtSet::ArtSet(const AIArtSpec* specs, size_t count)
		: pImpl{std::make_unique<Impl>(specs, count)}
	{
	}

	ArtSet::ArtSet(ArtSet&& other) AINOEXCEPT
	{
		swap(other);
	}

	ai::ArtSet& ArtSet::operator=(ArtSet&& other) AINOEXCEPT
	{
		swap(other);
		return (*this);
	}

	ArtSet::~ArtSet() = default;

	AIErr ArtSet::GenerateForAllLayers()
	{
		return pImpl->GenerateForAllLayers();
	}

	AIErr ArtSet::GenerateForNthLayer(ai::int32 inLayerIndex)
	{
		return pImpl->GenerateForNthLayer(inLayerIndex);
	}

	AIErr ArtSet::GenerateForNamedLayer(const ai::UnicodeString& inLayerName)
	{
		return pImpl->GenerateForNamedLayer(inLayerName);
	}

	AIErr ArtSet::GenerateForNthArtboard(ai::ArtboardID inArtboardIndex, bool skipHiddenArts)
	{
		return pImpl->GenerateForNthArtboard(inArtboardIndex, skipHiddenArts);
	}

	AIErr ArtSet::GenerateForNamedArtboard(const ai::UnicodeString& inArtboardName, bool skipHiddenArts)
	{
		return pImpl->GenerateForNamedArtboard(inArtboardName, skipHiddenArts);
	}

	AIErr ArtSet::GenerateForTopLevelLayers(bool skipHiddenLayers)
	{
		return pImpl->GenerateForTopLevelLayers(skipHiddenLayers);
	}

	AIErr ArtSet::GenerateSelectedAtTopLevel()
	{
		return pImpl->GenerateSelectedAtTopLevel();
	}

    AIErr ArtSet::GenerateForArt (AIArtHandle inArt)
    {
        return pImpl->GenerateForArt(inArt);
    }

	size_t ArtSet::size() const AINOEXCEPT
	{
		return pImpl->size();
	}

	ai::ArtSet::value_type ArtSet::at(size_t index) const
	{
		return pImpl->at(index);
	}

	ai::ArtSet::value_type ArtSet::operator[](size_t index) const AINOEXCEPT
	{
		return pImpl->operator[](index);
	}

	void ArtSet::insert(value_type art)
	{
		pImpl->insert(art);
	}

	void ArtSet::erase(value_type art)
	{
		pImpl->erase(art);
	}

	void ArtSet::replace(value_type oldArt, value_type newArt)
	{
		pImpl->replace(oldArt, newArt);
	}

	void ArtSet::clear()
	{
		pImpl->clear();
	}

	ArtSet::iterator ArtSet::begin() const AINOEXCEPT
	{
		return iterator(*this, 0);
	}

	ai::ArtSet::iterator ArtSet::end() const AINOEXCEPT
	{
		const auto count = size();
		return iterator(*this, count);
	}

	ai::ArtSet::iterator ArtSet::rbegin() const AINOEXCEPT
	{
		const auto count = size();
		return iterator(*this, count-1, true);
	}

	ai::ArtSet::iterator ArtSet::rend() const AINOEXCEPT
	{
		return iterator(*this, -1, true);
	}

	void ArtSet::swap(ArtSet& other) AINOEXCEPT
	{
		std::swap(pImpl, other.pImpl);
	}

	ArtSet::operator bool() const AINOEXCEPT
	{
		return pImpl->operator bool();
	}

	AIErr ArtSet::GetLastError() const AINOEXCEPT
	{
		return pImpl->GetLastError();
	}

	AIArtSet ArtSet::get() const AINOEXCEPT
	{
		return pImpl->get();
	}

} // namespace ai
