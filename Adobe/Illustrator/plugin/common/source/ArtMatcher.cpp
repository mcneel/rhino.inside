//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/ArtMatcher.cpp $
//
//  $Revision: #1 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "ArtMatcher.hpp"
#include "AIMdMemory.h"
#include "SPBasic.h"

#include <new>

// these need to be declared by client
extern "C" AIMatchingArtSuite *sAIMatchingArt;
extern "C" SPBasicSuite *sSPBasic;

ArtMatcher::ArtMatcher(ai::int16 iNumSpecs, AIBoolean matchArtInDictionaries)
{
	if (iNumSpecs > 0)
	{
		m_pSpecs = new(std::nothrow) AIMatchingArtSpec[iNumSpecs];
	}
	else
	{
		m_pSpecs = NULL;
	}

	if (m_pSpecs == NULL)
	{
		m_iNumSpecs = 0;
	}
	else
	{
		m_iNumSpecs = iNumSpecs;
	}

	m_MatchArtInDictionaries = matchArtInDictionaries;
	m_lNumMatches = 0;
	m_hMatches = NULL;
}

ArtMatcher::~ArtMatcher(void)
{
	delete [] m_pSpecs;

	if (m_hMatches != NULL && sSPBasic != NULL)
	{
		AIMdMemorySuite *sAIMdMemory = NULL;

		sSPBasic->AcquireSuite(kAIMdMemorySuite, kAIMdMemorySuiteVersion, (const void **) &sAIMdMemory);

		if (sAIMdMemory != NULL)
		{
			sAIMdMemory->MdMemoryDisposeHandle((AIMdMemoryHandle) (m_hMatches));
			sSPBasic->ReleaseSuite(kAIMdMemorySuite, kAIMdMemorySuiteVersion);
		}
	}
}

ASErr ArtMatcher::SetSpec(ai::int16 iX, ai::int16 shType, ai::int32 lWhichAttr, ai::int32 lAttr)
{
	ASErr result = kNoErr;

	if (m_MatchArtInDictionaries)
		lWhichAttr |= kMatchDictionaryArt;

	if (0 <= iX && iX < m_iNumSpecs)
	{
		AIMatchingArtSpec *pSpec = m_pSpecs + iX;

		pSpec->type = shType;
		pSpec->whichAttr = lWhichAttr;
		pSpec->attr = lAttr;
	}
	else
	{
		result = AM_InvalidIndex;
	}

	return result;
}

ASErr ArtMatcher::GetMatchingArt(void)
{
	ASErr result = kNoErr;

	m_lNumMatches = 0;

	if (sAIMatchingArt == NULL)
	{
		result = AM_InvalidSuite;
		goto ex;
	}

	// Check for if the spec is equivalent to GetSelectedArt, so that we can benefit from the selection caching
	if ( m_iNumSpecs == 1 && !m_MatchArtInDictionaries
			&& m_pSpecs[0].type == kAnyArt && m_pSpecs[0].whichAttr == kArtSelected
			&& m_pSpecs[0].attr == kArtSelected )
	{
		result = sAIMatchingArt->GetSelectedArt(&m_hMatches, &m_lNumMatches);
	}
	else
	{
		result = sAIMatchingArt->GetMatchingArt(m_pSpecs, m_iNumSpecs, &m_hMatches, &m_lNumMatches);
	}

ex:
	return result;
}

ai::int32 ArtMatcher::GetNumMatches(void)
{
	return m_lNumMatches;
}

AIArtHandle ArtMatcher::GetMatchedArt(ai::int32 iX)
{
	AIArtHandle matchedArt = NULL;

	if (0 <= iX && iX < m_lNumMatches)
	{
		matchedArt = (*m_hMatches)[iX];
	}

	return matchedArt;
}

void ArtMatcher::ClearMatchedArt(ai::int32 iX)
{
	if (0 <= iX && iX < m_lNumMatches)
	{
		(*m_hMatches)[iX] = NULL;
	}
}
