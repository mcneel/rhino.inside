/*
 *        Name:	IAIColorSpace.cpp
 *   $Revision: 1 $
 *      Author:	Simon Chen
 *        Date:	   
 *     Purpose:	Plug-in side implementation of the ai::ColorSpace and ai::ColorSpaceList interfaces.
 *				This file should NOT be included in the core application.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include "IAIColorSpace.hpp"
#include "AIColorSpace.h"

#include  "IAIColorSpace.inl"

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIColorSpace)
#elif defined(_IAICOLORSPACE_SUITE_INCLUDE_H_)
    #include _IAICOLORSPACE_SUITE_INCLUDE_H_
#else
    #ifndef _IAICOLORSPACE_SUITE_USE_C_LINKAGE_
	    #define _IAICOLORSPACE_SUITE_USE_C_LINKAGE_ 1
    #endif
    #if _IAICOLORSPACE_SUITE_USE_C_LINKAGE_
    extern "C"
    {
    #endif
	/** The plug-in using the ai::ColorSpace class is required to provide
		these global suite pointers.  These pointers must be valid prior
		to any call to ai::ColorSpace methods.
	*/
	extern AIColorSpaceSuite* sAIColorSpace;

    #if _IAICOLORSPACE_SUITE_USE_C_LINKAGE_
    }
    #endif // _IAICOLORSPACE_SUITE_USE_C_LINKAGE_
#endif

/* Throw result as an ai::Error if it indicates an error. */
static void check_result(AIErr result)
{
	if ( result != kNoErr )
	{
		throw ai::Error(result);
	}
}

///////////////////////////////////////////////////////////////////////////////
// ai::ColorSpace class implementation
//
ai::ColorSpace::ColorSpace(void) AINOTHROW
: fImpl(0)
{
}

ai::ColorSpace::ColorSpace(ai::ColorSpace::Family family, bool hasAlpha)
: fImpl(0)
{
	AIErr result = sAIColorSpace->NewSimpleColorSpace(*this, family, hasAlpha);
	check_result(result);
}

ai::ColorSpace::ColorSpace(int separationNum, bool hasAlpha)
: fImpl(0)
{
	AIErr result = sAIColorSpace->NewProcessSeparationColorSpace(*this, separationNum, hasAlpha);
	check_result(result);
}

ai::ColorSpace::ColorSpace(const AICustomColorHandle customColor, bool hasAlpha)
: fImpl(0)
{
	AIErr result = sAIColorSpace->NewGlobalColorSpace(*this, customColor, hasAlpha);
	check_result(result);
}

ai::ColorSpace::ColorSpace(const ai::ColorSpaceList &csList, bool hasAlpha, bool promoteToProcess)
: fImpl(0)
{
	AIErr result = sAIColorSpace->NewNChannelColorSpace(*this, csList, hasAlpha, promoteToProcess);
	check_result(result);
}

ai::ColorSpace::ColorSpace(const ai::ColorSpace &baseCs, int numComponents, int numEntries, const ASUInt8 *lookup)
: fImpl(0)
{
	AIErr result = sAIColorSpace->NewIndexedColorSpace(*this, baseCs, numComponents, numEntries, lookup);
	check_result(result);
}

ai::ColorSpace::ColorSpace(const ai::ColorSpace& cs, bool hasAlpha)
: fImpl(0)
{
	AIErr result = sAIColorSpace->NewColorSpace(*this, cs, hasAlpha);
	check_result(result);
}

ai::ColorSpace::ColorSpace(const ai::ColorSpace& cs)
: fImpl(0)
{
	AIErr result = sAIColorSpace->CopyColorSpace(*this, cs);
	check_result(result);
}

ai::ColorSpace::~ColorSpace()
{
	if ( fImpl )
	{
		sAIColorSpace->DeleteColorSpace(*this);
	}
}

ai::ColorSpace& ai::ColorSpace::operator= (const ai::ColorSpace& rhs)
{
	AIErr result = sAIColorSpace->CopyColorSpace(*this, rhs);
	check_result(result);
	return (*this);
}

bool ai::ColorSpace::IsValid(void) const
{
	return (fImpl != 0);
}

ai::ColorSpace::Family ai::ColorSpace::GetFamily(void) const
{
	ai::ColorSpace::Family family;
	family = sAIColorSpace->GetFamily(*this);
	return family;
}

bool ai::ColorSpace::HasAlpha(void) const
{
	AIBoolean hasAlhpa;
	hasAlhpa = sAIColorSpace->HasAlpha(*this);
	return (hasAlhpa != 0);
}

int ai::ColorSpace::NumComponents(void) const
{
	int count;
	count = sAIColorSpace->GetNumComponents(*this);
	return count;
}

int ai::ColorSpace::NumColorComponents(void) const
{
	int count;
	count = sAIColorSpace->GetNumColorComponents(*this);
	return count;
}

int ai::ColorSpace::NumSpotComponents(void) const
{
	int count;
	count = sAIColorSpace->GetNumSpotComponents(*this);
	return count;
}

ai::ColorSpace ai::ColorSpace::BaseColorSpace(void) const
{
	ai::ColorSpace baseCs;
	AIErr result = sAIColorSpace->GetBaseColorSpace(*this, baseCs);
	check_result(result);
	return baseCs;
}

int ai::ColorSpace::IndexedNumComponents(void) const
{
	int count;
	count = sAIColorSpace->GetIndexedNumComponents(*this);
	return count;
}

int ai::ColorSpace::IndexedNumEntries(void) const
{
	int count;
	count = sAIColorSpace->GetIndexedNumEntries(*this);
	return count;
}

const ASUInt8* ai::ColorSpace::IndexedTable(void) const
{
	const ASUInt8* lookup = sAIColorSpace->GetIndexedTable(*this);
	return lookup;
}

const AIFloat* ai::ColorSpace::SeparationAltColors(void) const
{
	const AIFloat* altColors = sAIColorSpace->GetSeparationAltColors(*this);
	return altColors;
}

ai::ColorSpaceList ai::ColorSpace::GetColorSpaceList(void) const
{
	ai::ColorSpaceList csList;
	AIErr result = sAIColorSpace->GetColorSpaceList(*this, csList);
	check_result(result);
	return csList;
}

ai::UnicodeString ai::ColorSpace::NthColorant(ai::int32 n) const
{
	ai::UnicodeString colorant;
	AIErr result = sAIColorSpace->GetNthColorant(*this, n, colorant);
	check_result(result);
	return colorant;
}

bool ai::ColorSpace::HasFullSetOfProcessComponents(void) const
{
	AIBoolean fullProcessComps;
	fullProcessComps = sAIColorSpace->HasFullSetOfProcessComponents(*this);
	return (fullProcessComps != 0);
}

bool ai::ColorSpace::operator==(const ai::ColorSpace &rhs) const
{
	AIBoolean identical;
	identical = sAIColorSpace->Equal(*this, rhs);
	return (identical != 0);
}

///////////////////////////////////////////////////////////////////////////////
// ai::ColorSpaceList class implementation
//
ai::ColorSpaceList::ColorSpaceList(void) AINOTHROW
: fImpl(0)
{
}

ai::ColorSpaceList::ColorSpaceList(const ai::ColorSpace &cs)
: fImpl(0)
{
	AIErr result = sAIColorSpace->NewColorSpaceList(*this, cs);
	check_result(result);
}

ai::ColorSpaceList::ColorSpaceList(const ai::ColorSpaceList& csList)
: fImpl(0)
{
	AIErr result = sAIColorSpace->CopyColorSpaceList(*this, csList);
	check_result(result);
}

ai::ColorSpaceList::~ColorSpaceList()
{
	if ( fImpl )
	{
		sAIColorSpace->DeleteColorSpaceList(*this);
	}
}

ai::ColorSpaceList& ai::ColorSpaceList::operator= (const ai::ColorSpaceList& rhs)
{
	AIErr result = sAIColorSpace->CopyColorSpaceList(*this, rhs);
	check_result(result);
	return (*this);
}

bool ai::ColorSpaceList::IsValid(void) const
{
	return (fImpl != 0);
}

void ai::ColorSpaceList::AddColorSpace(const ai::ColorSpace &cs)
{
	AIErr result = sAIColorSpace->AddColorSpace(*this, cs);
	check_result(result);
}

int ai::ColorSpaceList::NumColorSpaces(void) const
{
	int count;
	count = sAIColorSpace->GetNumColorSpaces(*this);
	return count;
}

ai::ColorSpace ai::ColorSpaceList::NthColorSpace(int n) const
{
	ai::ColorSpace cs;
	AIErr result = sAIColorSpace->GetNthColorSpace(*this, n, cs);
	check_result(result);
	return cs;
}

void ai::ColorSpaceList::Normalize(short docColorModel, bool convertGrayToFullProcess)
{
	AIErr result = sAIColorSpace->Normalize(*this, docColorModel, convertGrayToFullProcess);
	check_result(result);
}

