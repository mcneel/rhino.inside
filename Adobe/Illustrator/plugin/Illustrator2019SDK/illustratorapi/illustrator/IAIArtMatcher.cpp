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

#include "IAIArtMatcher.hpp"
#include "AIMdMemory.h"

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIMatchingArt)
	use_suite(AIMdMemory)
#elif defined (_ARTMATCHER_SUITE_INCLUDE_H)
	#include _ARTMATCHER_SUITE_INCLUDE_H
#else
// these need to be declared by client
	extern "C" AIMatchingArtSuite *sAIMatchingArt;
	extern "C" AIMdMemorySuite *sAIMdMemory;
#endif

namespace ai
{

ArtMatcher::~ArtMatcher()
{
	m_pSpecs.clear();
	clear();
}

AIErr ArtMatcher::SetSpec(size_t iX, ai::int16 shType, ai::int32 lWhichAttr, ai::int32 lAttr)
{
	AIErr result = kNoErr;

	if (m_MatchArtInDictionaries)
		lWhichAttr |= kMatchDictionaryArt;

	if (iX >= m_pSpecs.size())
		m_pSpecs.resize(iX + 1);

	m_pSpecs[iX] = { shType, lWhichAttr, lAttr };

	return result;
}

AIErr ArtMatcher::PushSpec(ai::int16 shType, ai::int32 lWhichAttr, ai::int32 lAttr)
{
	try
	{
		if (m_MatchArtInDictionaries)
			lWhichAttr |= kMatchDictionaryArt;

		m_pSpecs.emplace_back( shType, lWhichAttr, lAttr );
	}
	catch (...)
	{
		return kOutOfMemoryErr;
	}
	
	return kNoErr;
}

AIErr ArtMatcher::GetMatchingArt(void)
{
	return LoadMatchingArt();
}

AIErr ArtMatcher::GetSelectedArt()
{
	return LoadMatchingArt(ArtMatcher::kQuerySelection);
}

AIErr ArtMatcher::GetMatchingArtFromLayerList(AILayerList layerList)
{
	return LoadMatchingArt(ArtMatcher::kQueryFromLayerList, layerList);
}

AIErr ArtMatcher::GetMatchingArtFromArt(AIArtHandle art)
{
	return LoadMatchingArt(ArtMatcher::kQueryFromArt, art);
}

AIErr ArtMatcher::GetArtForCurrentPathStyle()
{
	return LoadMatchingArt(ArtMatcher::kQueryFromCurrentPathStyle);
}

AIErr ArtMatcher::GetSelectedArtFromLayerList(AILayerList layerList)
{
	return LoadMatchingArt(ArtMatcher::kQuerySelectedArtFromLayerList, layerList);
}

ai::int32 ArtMatcher::GetNumMatches() const
{
	return m_lNumMatches;
}

AIArtHandle ArtMatcher::GetMatchedArt(size_t iX) const
{
	AIArtHandle matchedArt = nullptr;

	if (iX < static_cast<decltype(iX)>(m_lNumMatches))
	{
		matchedArt = (*m_hMatches)[iX];
	}

	return matchedArt;
}

AIArtHandle ArtMatcher::operator[](size_t iX) const
{
	return GetMatchedArt(iX);
}
ai::ArtSet ArtMatcher::GetArtSet() const
{
	if (*this)
	{
		return ai::ArtSet(*m_hMatches, static_cast<size_t>(m_lNumMatches));
	}

	return ai::ArtSet();
}

void ArtMatcher::ClearMatchedArt(size_t iX)
{
	if (iX < static_cast<decltype(iX)>(m_lNumMatches))
	{
		(*m_hMatches)[iX] = nullptr;
	}
}

void ArtMatcher::clear() AINOEXCEPT
{
	if (m_hMatches && sAIMdMemory)
	{
		sAIMdMemory->MdMemoryDisposeHandle((AIMdMemoryHandle)(m_hMatches));
		m_lNumMatches = 0;
		m_hMatches = nullptr;
	}
}

AIArtHandle** ArtMatcher::release() AINOEXCEPT
{
	auto toReturn = m_hMatches;
	m_hMatches = nullptr;
	m_lNumMatches = 0;
	return toReturn;
}

ArtMatcher::ArtMatcher(ArtMatcher&& other) AINOEXCEPT
{
	this->swap(other);
}

ArtMatcher& ArtMatcher::operator=(ArtMatcher&& other) AINOEXCEPT
{
	this->swap(other);
	return (*this);
}

void ArtMatcher::swap(ArtMatcher& other) AINOEXCEPT
{
	std::swap(m_pSpecs, other.m_pSpecs);
	std::swap(m_MatchArtInDictionaries, other.m_MatchArtInDictionaries);
	std::swap(m_hMatches, other.m_hMatches);
	std::swap(m_lNumMatches, other.m_lNumMatches);
}

AIErr ArtMatcher::LoadMatchingArt(ArtMatcher::QueryType qryType /*= kQueryMatchingArt*/, void* cookie /*= nullptr*/)
{
	m_LastError = kNoErr;

	if (!sAIMatchingArt)
	{
		return AM_InvalidSuite;
	}

	//Clear the store result if any
	clear();

	try
	{
		switch (qryType)
		{
			case kQueryMatchingArt:
			{
				//Check for if the spec is equivalent to GetSelectedArt, so that we can benefit from the selection caching,
				//Fall back to selection query
				if (!((m_pSpecs.size() == 1 && !m_MatchArtInDictionaries &&
					m_pSpecs[0].type == kAnyArt && m_pSpecs[0].whichAttr == kArtSelected && m_pSpecs[0].attr == kArtSelected)))
				{
					m_LastError =
						sAIMatchingArt->GetMatchingArt
						(
							&m_pSpecs[0],
							(ai::int16) m_pSpecs.size(),
							&m_hMatches,
							&m_lNumMatches
						);
					break;
				}
			}
			case kQuerySelection:
			{
				m_LastError = sAIMatchingArt->GetSelectedArt(&m_hMatches, &m_lNumMatches);
				break;
			}
			case kQueryFromLayerList:
			{
				m_LastError =
					sAIMatchingArt->GetMatchingArtFromLayerList
					(
					(AILayerList)cookie,
						&m_pSpecs[0],
						(ai::int16) m_pSpecs.size(),
						&m_hMatches,
						&m_lNumMatches
					);
				break;
			}
			case kQueryFromArt:
			{
				m_LastError =
					sAIMatchingArt->GetMatchingArtFromArt
					(
					(AIArtHandle)cookie,
						&m_pSpecs[0],
						(ai::int16) m_pSpecs.size(),
						&m_hMatches,
						&m_lNumMatches
					);
				break;
			}
			case kQueryFromCurrentPathStyle:
			{
				m_LastError = sAIMatchingArt->GetArtForCurrentPathStyle(&m_hMatches, &m_lNumMatches);
				break;
			}
			case kQuerySelectedArtFromLayerList:
			{
				m_LastError = sAIMatchingArt->GetSelectedArtFromLayerList((AILayerList)cookie, &m_hMatches, &m_lNumMatches);
				break;
			}
		}
	}
	catch (...)
	{
		m_LastError = AM_UnknownException;
	}

	//make sure handles and numMatches are sane in case of an error
	if (m_LastError != kNoErr)
	{
		m_lNumMatches = 0;
		m_hMatches = nullptr;
	}
	return m_LastError;
}


} //ai