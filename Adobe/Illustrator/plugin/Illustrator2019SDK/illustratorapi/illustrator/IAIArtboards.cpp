/*
* Name: IAIArtboards.hpp
* Author: Started by Pushp
* Date: November, 2008
* Purpose: Adobe Illustrator Artboard Suite Wraper implementation
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2008 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

#include "AIArtboard.h"
#include <algorithm>

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIArtboard)
#elif defined(_IAIARTBOARD_SUITE_INCLUDE_H_)
	#include _IAIARTBOARD_SUITE_INCLUDE_H_
#else
#ifndef _IAIARTBOARD_SUITE_USE_C_LINKAGE_
#define _IAIARTBOARD_SUITE_USE_C_LINKAGE_ 1
#endif
#if _IAIARTBOARD_SUITE_USE_C_LINKAGE_
extern "C"
{
#endif
	/** The plug-in using the ai::ArtboardProperties class is required to provide
	these global suite pointers.  These pointers must be valid prior
	to any call to ai::ArtboardProperties methods.
	*/
	extern AIArtboardSuite* sAIArtboard;

#if _IAIARTBOARD_SUITE_USE_C_LINKAGE_
}
#endif // _IAIARTBOARD_SUITE_USE_C_LINKAGE_

#endif

#include "AIErrorHandler.h"
#include "AIAssert.hpp"
#include "IAIStringFormatUtils.h"

namespace ai
{
	ArtboardProperties::~ArtboardProperties()
	{
		try{
			sAIArtboard->Dispose(*this);	
		}
		catch(ai::Error&){}
	}
	ArtboardProperties::ArtboardProperties():fImpl(0)
	{
		sAIArtboard->Init(*this);
	}
	ArtboardProperties::ArtboardProperties(ArtboardRef /*ref*/):fImpl(0)
	{
	}
	ArtboardProperties::ArtboardProperties(const ArtboardProperties& artboard):fImpl(0)
	{
		sAIArtboard->CloneArtboard(*this,artboard);		
	}
	ArtboardProperties& ArtboardProperties::operator=(const ArtboardProperties& object)
	{
		ArtboardProperties temp(object);
		std::swap(this->fImpl,temp.fImpl);
		return *this;
	}
	AIErr ArtboardProperties::GetPosition(AIRealRect& rect) const 
	{
		return sAIArtboard->GetPosition(*this,rect);
	}
	AIErr ArtboardProperties::SetPosition(AIRealRect rect)
	{
		return sAIArtboard->SetPosition(*this,rect);
	}
	AIErr ArtboardProperties::GetName(ai::UnicodeString& name) const
	{
		return sAIArtboard->GetName(*this,name);
	}
	AIErr ArtboardProperties::SetName(const ai::UnicodeString& name)
	{
		return sAIArtboard->SetName(*this,name);
	}
	AIErr ArtboardProperties::IsDefaultName(AIBoolean& isDefault) const
	{
		return sAIArtboard->IsDefaultName(*this, isDefault);
	}
	AIErr ArtboardProperties::SetIsDefaultName(const AIBoolean& isDefault)
	{
		return sAIArtboard->SetIsDefaultName(*this,isDefault);
	}
	AIErr ArtboardProperties::GetPAR(AIReal& par) const
	{
		return sAIArtboard->GetPAR(*this,par);
	}
	AIErr ArtboardProperties::SetPAR(AIReal par)
	{
		return sAIArtboard->SetPAR(*this,par);
	}
	AIErr ArtboardProperties::GetRulerOrigin(AIRealPoint& rulerOrigin) const 
	{
		return sAIArtboard->GetRulerOrigin(*this,rulerOrigin);
	}
	AIErr ArtboardProperties::SetRulerOrigin(const AIRealPoint& rulerOrigin)
	{
		return sAIArtboard->SetRulerOrigin(*this,rulerOrigin);
	}
	AIErr ArtboardProperties::GetShowDisplayMark(DisplayMarkType type,bool& show) const
	{
		AIBoolean temp = show;
		AIErr error =  sAIArtboard->GetShowDisplayMark(*this,type,temp);
		if(kNoErr != error) return error;
		show = !!temp;
		return error;
	}
	AIErr ArtboardProperties::SetShowDisplayMark(DisplayMarkType type,bool show)
	{
		return sAIArtboard->SetShowDisplayMark(*this,type,show);
	}

	AIErr ArtboardProperties::IsSelected(AIBoolean& isSelected) const
	{
		return sAIArtboard->IsSelected(*this, isSelected);
	}

	ArtboardList::ArtboardList():fImpl(0)
	{
		sAIArtboard->GetArtboardList(*this);
	}

#ifdef AI_HAS_RVALUE_REFERENCES
	ai::ArtboardList::iterator ArtboardList::begin()
	{
		return iterator(0, this);
	}

	ai::ArtboardList::iterator ArtboardList::end()
	{
		return iterator(size(), this);
	}

	ai::ArtboardList::value_type ArtboardList::at(ArtboardID artboardID)
	{
		return ai::ArtboardList::value_type(artboardID, this);
	}

	ArtboardID ArtboardList::size() const AINOEXCEPT
	{
		ArtboardID count = 0;
		try{
			GetCount(count);
		}
		catch(ai::Error&){}
		return count;
	}
#endif //AI_HAS_RVALUE_REFERENCES

	ArtboardList::~ArtboardList()
	{
		try{
			if(fImpl)
				sAIArtboard->ReleaseArtboardList(*this);
		}
		catch(ai::Error&){}
	}

	AIErr ArtboardList::AddNew(ArtboardProperties& newArtboard, ArtboardID& index)
	{
		return sAIArtboard->AddNew(*this,newArtboard,index);
	}

	AIErr ArtboardList::Insert(ArtboardProperties& artboard, ArtboardID& index)
	{
		return sAIArtboard->Insert(*this,artboard,index);
	}

	AIErr ArtboardList::Delete(ArtboardID index)
	{
		return sAIArtboard->Delete(*this,index);
	}

	AIErr ArtboardList::Delete(const std::vector<ai::ArtboardID>& artboardIDs)
	{
		ai::AutoBuffer<ai::ArtboardID> artboardIDBuffer(artboardIDs.size());

		std::copy(artboardIDs.begin(), artboardIDs.end(), artboardIDBuffer.begin());

		return sAIArtboard->DeleteArtboards(*this, artboardIDBuffer);
	}

	AIErr ArtboardList::GetCount(ArtboardID&index) const
	{
		return sAIArtboard->GetCount(*this,index);
	}

	ArtboardProperties ArtboardList::GetArtboardProperties(ArtboardID index)
	{
		ArtboardProperties object(NULL);
		sAIArtboard->GetArtboardProperties(*this,index,object);
		return object;
	}
	AIErr ArtboardList::GetActive(ArtboardID& index) const
	{
		return sAIArtboard->GetActive(*this,index);
	}
	AIErr ArtboardList::SetActive(ArtboardID index)
	{
		return sAIArtboard->SetActive(*this,index);
	}
	AIErr ArtboardList::Update(ArtboardID index, const ArtboardProperties& artboard)
	{
		return sAIArtboard->Update(*this,index,artboard);
	}

	AIErr ArtboardList::Select(ai::ArtboardID artboardID, bool exclusively)
	{
		return sAIArtboard->SelectArtboard(*this, artboardID, exclusively);
	}

	AIErr ArtboardList::Select(const std::vector<ai::ArtboardID>& artboardIDs, bool exclusively)
	{
		ai::AutoBuffer<ai::ArtboardID> artboardIDBuffer(artboardIDs.size());
		
		std::copy(artboardIDs.begin(), artboardIDs.end(), artboardIDBuffer.begin());

		return sAIArtboard->SelectArtboards(*this, artboardIDBuffer, exclusively);
	}

	AIErr ArtboardList::SelectAll()
	{
		return sAIArtboard->SelectAllArtboards(*this);
	}

	AIErr ArtboardList::Deselect(ai::ArtboardID artboardID)
	{
		return sAIArtboard->DeselectArtboard(*this, artboardID);
	}

	AIErr ArtboardList::DeselectAll()
	{
		return sAIArtboard->DeselectAllArtboards(*this);
	}

#ifdef AI_HAS_RVALUE_REFERENCES
	ArtboardList::Artboard::Artboard(ArtboardID artboardID, container_type artboardListPtr) :
		mArtboardID(artboardID),
		mArtboardListPtr(artboardListPtr)
	{
		if (mArtboardID < mArtboardListPtr->size())
		{
			mProps = mArtboardListPtr->GetArtboardProperties(mArtboardID);
		}
	}

	AIErr ArtboardList::Artboard::Update()
	{
		AIMsgAssert(mArtboardID < mArtboardListPtr->size(), "Invalid artboard ID !!!");
		return mArtboardListPtr->Update(mArtboardID, mProps);
	}

	ArtboardList::iterator::iterator(size_type index, container_type artboardListPtr) :
		mValue(index, artboardListPtr),
		mArtboardListPtr(artboardListPtr),
		mArtboardCount(artboardListPtr->size())
	{
	}

	ArtboardList::iterator& ArtboardList::iterator::operator++()
	{
		AIMsgAssert(mArtboardCount == mArtboardListPtr->size(), "Iterator is no longer valid!");
		auto curID = mValue.GetID();
		if (curID < mArtboardCount)
		{
			++curID;
			ArtboardList::iterator::value_type newVal(curID, mArtboardListPtr);
			mValue.swap(newVal);
		}
		return *this;
	}
	
	bool ArtboardList::iterator::operator==(const iterator& rhs) const
	{
		AIMsgAssert(compatible(rhs), "Incompatible iterator");
		return	(mArtboardListPtr == rhs.mArtboardListPtr)	&&
				(mValue.GetID() == rhs.mValue.GetID())	&&
				(mArtboardCount == rhs.mArtboardCount);
	}

	bool ArtboardList::iterator::compatible(const iterator& rhs) const
	{
		return (mArtboardListPtr->fImpl == rhs.mArtboardListPtr->fImpl);
	}

#endif //AI_HAS_RVALUE_REFERENCES
	namespace ArtboardUtils
	{
		/** Retrieves the name of the specified artboard. if the index is -1 it gets the name of the active artboard
		@param name [out] A buffer in which to return the name.
		@param isDefault [out] A bool which indicates if the name is default or not.
		@param index [in] The artboard index (-1 if active artboard).
		*/
		AIErr GetArtboardName(ai::UnicodeString& name,bool& isDefault, ArtboardID index )
		{
			AIErr error = kNoErr;
			isDefault = false;
			ArtboardList list;
			if(index == kActiveArtboard)
				error = list.GetActive(index);
			ArtboardProperties artboardProps(list.GetArtboardProperties(index));
			if (!artboardProps.IsValid()) return kBadParameterErr;

			artboardProps.GetName(name);
			AIBoolean isDefaultName = FALSE;
			artboardProps.IsDefaultName(isDefaultName);
			if(name.empty())
			{
				isDefaultName=TRUE;
				const char* abString = "$$$/Artboards/Name/Str=Artboard";
				name = ai::UnicodeString(ZREF(abString));
				name.append(ai::UnicodeString::FromRoman(" "));
				name.append(ai::UnicodeString::FromRoman(ai::to_string(index+1)));
				artboardProps.SetName(name);
				artboardProps.SetIsDefaultName(TRUE);
				list.Update(index, artboardProps);
			}
			isDefault = (isDefaultName == 1);

			return error;
		}
		
		/** Retrieves the index of the artboard with specified name
		@param name [in] The name of the Artboard.
		@param index [out] The artboard index .
		*/
		AIErr GetArtboardIndexByName(const ai::UnicodeString& name, ai::ArtboardID& index)
		{
			AIErr error = kNoErr;
			ArtboardList abList;
			ai::int32 abCount=0;
			error = abList.GetCount(abCount);
			if(error != kNoErr)
				return error;
			ai::UnicodeString abName("");
			ai::ArtboardProperties artboardProps;
			for(index=0;index<abCount;index++)
			{
				artboardProps = abList.GetArtboardProperties(index);
				error = artboardProps.GetName(abName);
				if(error != kNoErr)
					return error;
				if(abName == name)
					return kNoErr;
			}
			return kNotFoundErr;
		}

		AIErr AreAnyArtboardsOverlapping(ai::ArtboardList &artboardList, AIBoolean &isOverlapping)
		{
			return sAIArtboard->AreAnyArtboardsOverlapping(artboardList, isOverlapping);
		}
	
	} // namespace ArtboardUtils

} // namespace ai