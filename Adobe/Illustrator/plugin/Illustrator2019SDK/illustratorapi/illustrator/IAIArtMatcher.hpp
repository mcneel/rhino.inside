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

#include "AIArt.h"
#include "AIMatchingArt.h"
#include "IAIArtSet.hpp"

#include <vector>
#include <iterator>


/** @file IAIArtMatcher.hpp */

namespace ai
{
	
/**
	A stack based wrapper class for inquiring about the selection and matched art over AIMatchingArtSuite.
	Always prefer this class over directly calling APIs in AIMatchingArtSuite.

	Enhanced to support C++11 semantics.
	For example, range-based loops, move constructor and assignment, and
	added support for dynamic spec specification as well as automatic size computation.

	// Example 1.1: Statically allocate spec, let ArtMatcher figure out the size, recommended approach
		AIMatchingArtSpec spec[] = {
			{ kRasterArt, kArtSelected, kArtSelected},
			{ kPlacedArt, kArtSelected, kArtSelected}
		};
	
		ArtMatcher matcher(spec);
		matcher.GetMatchingArt();

		for(auto art: matcher) // This loop is safe even if the earlier call didn't return any art, the loop won't enter
		{
		// work with art
		}
	
	// WARNING NOTE!!! Don't create a spec array with single braces even for one element
		// e.g,  never do this, AIMatchingArtSpec now has a default constructor and it creates an array with size 3
		// AIMatchingArtSpec spec[] = { kRasterArt, kArtSelected, kArtSelected};

	

	// Example 1.2 Special constructor for one spec
		ArtMatcher matcher(AIMatchingArtSpec{ kAnyArt, kArtFullySelected, kArtFullySelected });
		matcher.GetMatchingArt();

		for(auto art: matcher) // This loop is safe even if the earlier call didn't return any art, the loop won't enter
		{
			// work with art
		}

	// Example 2: Push specs at runtime, without worrying about upfront allocation
		ArtMatcher matcher;
		matcher.PushSpec(kRasterArt, kArtSelected, kArtSelected);
		matcher.PushSpec(kPlacedArt, kArtSelected, kArtSelected);

		AIErr err = matcher.GetMatchingArt();
		if(!err)
		{
			auto count = matcher.GetNumMatches();
			for(decltype(count) i = 0; i < count; ++i)
			{
			auto art = matcher.GetMatchedArt(i);
			}
		}

	// Example 3: Reserve space and set index based specs. The old way is still supported.
		// It will work even if you don't reserve space upfront
		ArtMatcher matcher(1);
		matcher.SetSpec(0, kArtSelected, kArtSelected);
		AIErr err = matcher.GetMatchingArt();
		...
		// use range based or direct access loop

	// Example 4: Bool operator
		ArtMatcher matcher(spec);
		matcher.GetMatchingArt();
		if(matcher) // Has at least one element; this check is not required for range-based loops
		{
			auto firstObject = *(matcher.begin());
		}

	// Example 5: Reverse iterator (last to first)
		ArtMatcher matcher(spec);
		matcher.GetMatchingArt();
		for (auto iter = matcher.rbegin(); iter != matcher.rend(); ++iter)
		{
			auto art = *iter;
		}

	// Example 6: Fetch all selected objects
		ArtMatcher matcher;
		matcher.GetSelectedArt();

		for(auto art: matcher)  // This loop is safe even if the earlier call didn't return any art, the loop won't enter
		{
			// process selected objects
		}

*/

class ArtMatcher
{
public:
	using iterator = AIArtHandle*;
	using reverse_iterator = std::reverse_iterator<iterator>;

	/** Default constructor
	*/
	explicit ArtMatcher(size_t iNumSpecs = 0, AIBoolean matchArtInDictionaries = false) :
		m_pSpecs(iNumSpecs), m_MatchArtInDictionaries{matchArtInDictionaries}
	{
	}

	/** Constructor with one spec
	*/
	ArtMatcher(const AIMatchingArtSpec& spec, AIBoolean matchArtInDictionaries = false) :
		m_pSpecs{spec}, m_MatchArtInDictionaries{matchArtInDictionaries}
	{
		if (m_MatchArtInDictionaries)
		{
			m_pSpecs[0].whichAttr |= kMatchDictionaryArt;
		}
	}
	
	/** Construct with spec array
	*/
	template<std::size_t N>
	ArtMatcher(const AIMatchingArtSpec(&specs)[N], AIBoolean matchArtInDictionaries = false):
		m_pSpecs{ specs, specs + N }, m_MatchArtInDictionaries{matchArtInDictionaries}
	{
		if (m_MatchArtInDictionaries)
		{
			for (auto& spec : m_pSpecs)
			{
				spec.whichAttr |= kMatchDictionaryArt;
			}
		}
	}

	/** Destructor
	*/
	~ArtMatcher();

	/** Copy is not allowed.
	*/
	ArtMatcher(const ArtMatcher&) = delete;
	
	/** Assignment is not allowed.
	*/
	ArtMatcher& operator=(const ArtMatcher&) = delete;
	
	/** Move Constructor 
	*/
	ArtMatcher(ArtMatcher&& other) AINOEXCEPT;
	
	/** Move Assignment
	*/
	ArtMatcher& operator= (ArtMatcher&& other) AINOEXCEPT;
	
	/** Set spec if size is already allocated.
	*/
	AIErr SetSpec(size_t iX, ai::int16 shType, ai::int32 lWhichAttr, ai::int32 lAttr);
	
	/** Add spec to the end 
	*/
	AIErr PushSpec(ai::int16 shType, ai::int32 lWhichAttr, ai::int32 lAttr);
	
	/** #AIMatchingArtSuite::GetMatchingArt() 
	*/
	AIErr GetMatchingArt();
	
	/** #AIMatchingArtSuite::GetSelectedArt() 
	*/
	AIErr GetSelectedArt();
	
	/** #AIMatchingArtSuite::GetMatchingArtFromLayerList() 
	*/
	AIErr GetMatchingArtFromLayerList(AILayerList layerList);
	
	/** #AIMatchingArtSuite::GetMatchingArtFromArt() 
	*/
	AIErr GetMatchingArtFromArt(AIArtHandle art);
	
	/** #AIMatchingArtSuite::GetArtForCurrentPathStyle() 
	*/
	AIErr GetArtForCurrentPathStyle();
	
	/** #AIMatchingArtSuite::GetSelectedArtFromLayerList() 
	*/
	AIErr GetSelectedArtFromLayerList(AILayerList layerList);

	/** Returns the number of art objects matched by last GetMatchingArt() or GetSelectedArt() call. 
	*/
	ai::int32 GetNumMatches() const;
	
	/** Returns nth AIArtHandle if the last GetMatchingArt() or GetSelectedArt() call succeeded.
	*/
	AIArtHandle GetMatchedArt(size_t iX) const;

	//Operator version of GetMatchedArt()

	AIArtHandle operator[](size_t iX) const;

	/** Returns a stack based AIArtSet Object which can be used in APIs which needs an AIArtSet
	*/
	ai::ArtSet GetArtSet() const;

	/** Get AIErr for the last query, though it is usually not required.
	*/
	AIErr GetLastError() const AINOEXCEPT { return m_LastError; }

	// The ClearMatchedArt method is for legacy usage, you can directly change the content in your loop with auto& 
	/* 
		for (auto& art : matcher)
		{
			// if you want to change the content based on some condition
			if(myCond(art))
				art = nullptr; // it will set the value of the content to nullptr 
		}
	*/
	void ClearMatchedArt(size_t iX);	// to enable multi-pass algorithms to filter out some of the matches
	
	/** Errors returned by ai::ArtMatcher */
	enum eArtMatcherErrors
	{
		AM_OK = kNoErr,
		AM_InvalidIndex,
		AM_InvalidSuite,
		AM_UnknownException,
		AM_NumErrs,
		AM_NoResult
	};

	/** Check if the last query has some interesting data */
	explicit operator bool() const AINOEXCEPT
	{
		return (m_hMatches != nullptr && m_lNumMatches > 0);
	}

	/** iterators for range based for loops */
	iterator begin () const AINOEXCEPT
	{ 
		if (m_hMatches)
			return *m_hMatches;
		return nullptr;
	}

	/** iterators for range based for loops */
	iterator end() const AINOEXCEPT
	{
		if (m_hMatches)
			return (*m_hMatches) + m_lNumMatches;
		return nullptr;
	}

	reverse_iterator rbegin() const AINOEXCEPT
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend() const AINOEXCEPT
	{
		return reverse_iterator(begin());
	}

	/** Clear the stored handles only, the spec is intact and will be used in next query */
	void clear() AINOEXCEPT; 

	/** Transfer the ownership of stored art handles, call it only if you know what you are doing. */
	AIArtHandle** release() AINOEXCEPT;

private:
	// swaps with other ArtMatcher
	void swap(ArtMatcher& other) AINOEXCEPT;
	
	enum QueryType 
	{
		kQueryMatchingArt,
		kQuerySelection,
		kQueryFromLayerList,
		kQuerySelectedArtFromLayerList,
		kQueryFromArt,
		kQueryFromCurrentPathStyle,
	};

	AIErr LoadMatchingArt(QueryType qryType = kQueryMatchingArt, void* cookie = nullptr);

	std::vector<AIMatchingArtSpec> m_pSpecs;
	AIBoolean m_MatchArtInDictionaries	= false;
	ai::int32 m_lNumMatches				= 0;
	AIArtHandle **m_hMatches			= nullptr;
	AIErr m_LastError					= kNoErr;
};

}