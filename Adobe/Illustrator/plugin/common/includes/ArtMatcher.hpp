//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/ArtMatcher.hpp $
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

#ifndef _ARTMATCHER_HPP_
#define _ARTMATCHER_HPP_

#include "AIArt.h"
#include "AIMatchingArt.h"

class ArtMatcher
{
public:
	ArtMatcher(ai::int16 iNumSpecs, AIBoolean matchArtInDictionaries = false);
	virtual ~ArtMatcher(void);
	//
	ASErr SetSpec(ai::int16 iX, ai::int16 shType, ai::int32 lWhichAttr, ai::int32 lAttr);
	//
	ASErr GetMatchingArt(void);
	ai::int32 GetNumMatches(void);
	AIArtHandle GetMatchedArt(ai::int32 iX);
	void ClearMatchedArt(ai::int32 iX);	// to enable multi-pass algorithms to filter out some of the matches
	//
	enum eArtMatcherErrors
	{
		AM_OK = kNoErr,
		AM_InvalidIndex,
		AM_InvalidSuite,
		AM_NumErrs
	};
	//
private:
	ai::int16 m_iNumSpecs;
	AIMatchingArtSpec *m_pSpecs;
	AIBoolean m_MatchArtInDictionaries;

	//
	ai::int32 m_lNumMatches;
	AIArtHandle **m_hMatches;
};

#endif // _ARTMATCHER_HPP_

