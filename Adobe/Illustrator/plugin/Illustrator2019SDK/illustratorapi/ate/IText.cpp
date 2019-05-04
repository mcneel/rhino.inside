/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	IText.cpp
		
	Notes:	Machine Generated file from script version 1.45
	        Please don't modify manually!
	
 ---------------------------------------------------------------------------------- */
#include "IText.h"
#include "IThrowException.h"
#include "ATETextSuitesExtern.h"
#ifdef WIN_ENV
#pragma warning(disable: 4800)		// forcing value to bool 'true' or 'false' (performance warning)
#endif

namespace ATE
{
/////////////////////////////////////////////////
//	UTILITY METHOD
////////////////////////////////////////////////

void ATEFloatMatrixToATERealMatrix( const ATETextDOM::FloatMatrix *f, ATETextDOM::RealMatrix *r )
{
	if (f && r)
	{
		r->a = f->a;
		r->b = f->b;
		r->c = f->c;
		r->d = f->d;
		r->tx = f->tx;
		r->ty = f->ty;
	}
}

void ATEFloatPointToATERealPoint ( const ATETextDOM::FloatPoint *f, ATETextDOM::RealPoint *r )
{
	if (f && r)
	{
		r->h = f->h;
		r->v = f->v;
	}
}

void SloFloatPointToAIFloatPoint ( const ATETextDOM::FloatPoint *f, ATETextDOM::FloatPoint *r )
{
	if (f && r)
	{
		r->h = f->h;
		r->v = f->v;
	}
}

//////////////////////////////////////////////
// --IApplicationPaint--
//////////////////////////////////////////////

IApplicationPaint::IApplicationPaint()
:fApplicationPaint(0)
{
}

IApplicationPaint::IApplicationPaint(ApplicationPaintRef applicationpaint)
:fApplicationPaint(applicationpaint)
{
}

IApplicationPaint::IApplicationPaint(const IApplicationPaint& src)
:fApplicationPaint(src.fApplicationPaint)
{
	sApplicationPaint->AddRef(fApplicationPaint);
}

IApplicationPaint::~IApplicationPaint()
{
	sApplicationPaint->Release(fApplicationPaint);
}

IApplicationPaint& IApplicationPaint::operator=(const IApplicationPaint& rhs)
{
	if (&rhs != this)
	{
		sApplicationPaint->Release(fApplicationPaint);
		fApplicationPaint = rhs.fApplicationPaint;
		sApplicationPaint->AddRef(fApplicationPaint);
	}
	return *this;
}

bool IApplicationPaint::operator==(const IApplicationPaint& rhs) const
{
	return fApplicationPaint == rhs.fApplicationPaint;
}

bool IApplicationPaint::operator!=(const IApplicationPaint& rhs) const
{
	return !(*this == rhs);
}

ApplicationPaintRef IApplicationPaint::GetRef() const
{
	return fApplicationPaint;
}

bool IApplicationPaint::IsNull() const
{
	return sApplicationPaint->IsNull(fApplicationPaint);
}

//////////////////////////////////////////////
// --ICompFont--
//////////////////////////////////////////////

ICompFont::ICompFont()
:fCompFont(0)
{
}

ICompFont::ICompFont(CompFontRef compfont)
:fCompFont(compfont)
{
}

ICompFont::ICompFont(const ICompFont& src)
:fCompFont(src.fCompFont)
{
	sCompFont->AddRef(fCompFont);
}

ICompFont::~ICompFont()
{
	sCompFont->Release(fCompFont);
}

ICompFont& ICompFont::operator=(const ICompFont& rhs)
{
	if (&rhs != this)
	{
		sCompFont->Release(fCompFont);
		fCompFont = rhs.fCompFont;
		sCompFont->AddRef(fCompFont);
	}
	return *this;
}

bool ICompFont::operator==(const ICompFont& rhs) const
{
	return fCompFont == rhs.fCompFont;
}

bool ICompFont::operator!=(const ICompFont& rhs) const
{
	return !(*this == rhs);
}

CompFontRef ICompFont::GetRef() const
{
	return fCompFont;
}

bool ICompFont::IsNull() const
{
	return sCompFont->IsNull(fCompFont);
}

ICompFont::ICompFont( ITextResources pResources)
{
	ATEErr error = sCompFont->Initialize(pResources.GetRef(), &fCompFont);
	if(error) Throw_ATE_Exception(error);
}

void ICompFont::GetNativeName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const
{
	ATEErr error = sCompFont->GetNativeName(fCompFont, name, maxLength);
	if(error) Throw_ATE_Exception(error);
}

void ICompFont::SetNativeName( const ATETextDOM::Unicode* name)
{
	ATEErr error = sCompFont->SetNativeName(fCompFont, name);
	if(error) Throw_ATE_Exception(error);
}

void ICompFont::GetPostScriptName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const
{
	ATEErr error = sCompFont->GetPostScriptName_AsUnicode(fCompFont, name, maxLength);
	if(error) Throw_ATE_Exception(error);
}

void ICompFont::GetPostScriptName( char* name, ATETextDOM::Int32 maxLength) const
{
	ATEErr error = sCompFont->GetPostScriptName_AsChar(fCompFont, name, maxLength);
	if(error) Throw_ATE_Exception(error);
}

void ICompFont::SetFontDictionary( void* fontDictionary)
{
	ATEErr error = sCompFont->SetFontDictionary(fCompFont, fontDictionary);
	if(error) Throw_ATE_Exception(error);
}

void* ICompFont::GetFontDictionary( ) const
{
	void* ret;
	ATEErr error = sCompFont->GetFontDictionary(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICompFont ICompFont::Duplicate( ) const
{
	CompFontRef ret = 0;
	ATEErr error = sCompFont->Duplicate(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFont(ret);
}

bool ICompFont::IsModified( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFont->IsModified(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFont::IsEditable( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFont->IsEditable(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFont::IsCommitted( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFont->IsCommitted(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFont::VerifyState( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFont->VerifyState(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFont::IsATCFileLoaded( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFont->IsATCFileLoaded(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ICompFont::GetComponentCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFont->GetComponentCount(fCompFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICompFontComponent ICompFont::GetComponent( ATETextDOM::Int32 index) const
{
	CompFontComponentRef ret = 0;
	ATEErr error = sCompFont->GetComponent(fCompFont, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontComponent(ret);
}

ATETextDOM::Int32 ICompFont::Find( ICompFontComponent component) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFont->Find(fCompFont, component.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFont::RemoveComponent( ATETextDOM::Int32 index)
{
	ATEBool8 ret;
	ATEErr error = sCompFont->RemoveComponent(fCompFont, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ICompFont::AddComponent( ICompFontComponent component)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFont->AddComponent(fCompFont, component.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFont::ReplaceComponent( ATETextDOM::Int32 index, ICompFontComponent component)
{
	ATEBool8 ret;
	ATEErr error = sCompFont->ReplaceComponent(fCompFont, index, component.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --ICompFontClass--
//////////////////////////////////////////////

ICompFontClass::ICompFontClass()
:fCompFontClass(0)
{
	ATEErr error = sCompFontClass->Initialize(&fCompFontClass);
	if(error) Throw_ATE_Exception(error);
}

ICompFontClass::ICompFontClass(CompFontClassRef compfontclass)
:fCompFontClass(compfontclass)
{
}

ICompFontClass::ICompFontClass(const ICompFontClass& src)
:fCompFontClass(src.fCompFontClass)
{
	sCompFontClass->AddRef(fCompFontClass);
}

ICompFontClass::~ICompFontClass()
{
	sCompFontClass->Release(fCompFontClass);
}

ICompFontClass& ICompFontClass::operator=(const ICompFontClass& rhs)
{
	if (&rhs != this)
	{
		sCompFontClass->Release(fCompFontClass);
		fCompFontClass = rhs.fCompFontClass;
		sCompFontClass->AddRef(fCompFontClass);
	}
	return *this;
}

bool ICompFontClass::operator==(const ICompFontClass& rhs) const
{
	return fCompFontClass == rhs.fCompFontClass;
}

bool ICompFontClass::operator!=(const ICompFontClass& rhs) const
{
	return !(*this == rhs);
}

CompFontClassRef ICompFontClass::GetRef() const
{
	return fCompFontClass;
}

bool ICompFontClass::IsNull() const
{
	return sCompFontClass->IsNull(fCompFontClass);
}

void ICompFontClass::GetNativeName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const
{
	ATEErr error = sCompFontClass->GetNativeName(fCompFontClass, name, maxLength);
	if(error) Throw_ATE_Exception(error);
}

void ICompFontClass::SetNativeName( const ATETextDOM::Unicode* name)
{
	ATEErr error = sCompFontClass->SetNativeName(fCompFontClass, name);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 ICompFontClass::GetCodes( ATETextDOM::Unicode* codes, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontClass->GetCodes(fCompFontClass, codes, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ICompFontClass::SetCodes( const ATETextDOM::Unicode* codes)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontClass->SetCodes(fCompFontClass, codes, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICompFontClass ICompFontClass::Duplicate( ) const
{
	CompFontClassRef ret = 0;
	ATEErr error = sCompFontClass->Duplicate(fCompFontClass, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontClass(ret);
}

ATETextDOM::Int32 ICompFontClass::GetCharacterCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontClass->GetCharacterCount(fCompFontClass, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

CompositeFontClassType ICompFontClass::GetClassType( ) const
{
	CompositeFontClassType ret;
	ATEErr error = sCompFontClass->GetClassType(fCompFontClass, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFontClass::IsCodeInClass( ATETextDOM::Unicode code) const
{
	ATEBool8 ret;
	ATEErr error = sCompFontClass->IsCodeInClass(fCompFontClass, code, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFontClass::IsEditable( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFontClass->IsEditable(fCompFontClass, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFontClass::IsCustomOverride( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFontClass->IsCustomOverride(fCompFontClass, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFontClass::IsModified( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFontClass->IsModified(fCompFontClass, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFontClass::VerifyState( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFontClass->VerifyState(fCompFontClass, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --ICompFontClassSet--
//////////////////////////////////////////////

ICompFontClassSet::ICompFontClassSet()
:fCompFontClassSet(0)
{
}

ICompFontClassSet::ICompFontClassSet(CompFontClassSetRef compfontclassset)
:fCompFontClassSet(compfontclassset)
{
}

ICompFontClassSet::ICompFontClassSet(const ICompFontClassSet& src)
:fCompFontClassSet(src.fCompFontClassSet)
{
	sCompFontClassSet->AddRef(fCompFontClassSet);
}

ICompFontClassSet::~ICompFontClassSet()
{
	sCompFontClassSet->Release(fCompFontClassSet);
}

ICompFontClassSet& ICompFontClassSet::operator=(const ICompFontClassSet& rhs)
{
	if (&rhs != this)
	{
		sCompFontClassSet->Release(fCompFontClassSet);
		fCompFontClassSet = rhs.fCompFontClassSet;
		sCompFontClassSet->AddRef(fCompFontClassSet);
	}
	return *this;
}

bool ICompFontClassSet::operator==(const ICompFontClassSet& rhs) const
{
	return fCompFontClassSet == rhs.fCompFontClassSet;
}

bool ICompFontClassSet::operator!=(const ICompFontClassSet& rhs) const
{
	return !(*this == rhs);
}

CompFontClassSetRef ICompFontClassSet::GetRef() const
{
	return fCompFontClassSet;
}

bool ICompFontClassSet::IsNull() const
{
	return sCompFontClassSet->IsNull(fCompFontClassSet);
}

ATETextDOM::Int32 ICompFontClassSet::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontClassSet->GetSize(fCompFontClassSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICompFontClass ICompFontClassSet::GetFirst( ) const
{
	CompFontClassRef ret = 0;
	ATEErr error = sCompFontClassSet->GetFirst(fCompFontClassSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontClass(ret);
}

ICompFontClass ICompFontClassSet::GetLast( ) const
{
	CompFontClassRef ret = 0;
	ATEErr error = sCompFontClassSet->GetLast(fCompFontClassSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontClass(ret);
}

ICompFontClass ICompFontClassSet::Item( ATETextDOM::Int32 nIndex) const
{
	CompFontClassRef ret = 0;
	ATEErr error = sCompFontClassSet->Item(fCompFontClassSet, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontClass(ret);
}

ATETextDOM::Int32 ICompFontClassSet::Find( ICompFontClass compFontClass) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontClassSet->Find(fCompFontClassSet, compFontClass.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ICompFontClassSet::FindPredefined( CompositeFontClassType predefinedType) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontClassSet->FindPredefined(fCompFontClassSet, predefinedType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --ICompFontComponent--
//////////////////////////////////////////////

ICompFontComponent::ICompFontComponent()
:fCompFontComponent(0)
{
}

ICompFontComponent::ICompFontComponent(CompFontComponentRef compfontcomponent)
:fCompFontComponent(compfontcomponent)
{
}

ICompFontComponent::ICompFontComponent(const ICompFontComponent& src)
:fCompFontComponent(src.fCompFontComponent)
{
	sCompFontComponent->AddRef(fCompFontComponent);
}

ICompFontComponent::~ICompFontComponent()
{
	sCompFontComponent->Release(fCompFontComponent);
}

ICompFontComponent& ICompFontComponent::operator=(const ICompFontComponent& rhs)
{
	if (&rhs != this)
	{
		sCompFontComponent->Release(fCompFontComponent);
		fCompFontComponent = rhs.fCompFontComponent;
		sCompFontComponent->AddRef(fCompFontComponent);
	}
	return *this;
}

bool ICompFontComponent::operator==(const ICompFontComponent& rhs) const
{
	return fCompFontComponent == rhs.fCompFontComponent;
}

bool ICompFontComponent::operator!=(const ICompFontComponent& rhs) const
{
	return !(*this == rhs);
}

CompFontComponentRef ICompFontComponent::GetRef() const
{
	return fCompFontComponent;
}

bool ICompFontComponent::IsNull() const
{
	return sCompFontComponent->IsNull(fCompFontComponent);
}

ICompFontComponent::ICompFontComponent( ITextResources pResources)
{
	ATEErr error = sCompFontComponent->Initialize(pResources.GetRef(), &fCompFontComponent);
	if(error) Throw_ATE_Exception(error);
}

ICompFontClass ICompFontComponent::GetClass( ) const
{
	CompFontClassRef ret = 0;
	ATEErr error = sCompFontComponent->GetClass(fCompFontComponent, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontClass(ret);
}

void ICompFontComponent::SetClass( ICompFontClass charClass)
{
	ATEErr error = sCompFontComponent->SetClass(fCompFontComponent, charClass.GetRef());
	if(error) Throw_ATE_Exception(error);
}

IFont ICompFontComponent::GetFont( ) const
{
	FontRef ret = 0;
	ATEErr error = sCompFontComponent->GetFont(fCompFontComponent, &ret);
	if(error) Throw_ATE_Exception(error);
	return IFont(ret);
}

void ICompFontComponent::SetFont( IFont font)
{
	ATEErr error = sCompFontComponent->SetFont(fCompFontComponent, font.GetRef());
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real ICompFontComponent::GetSize( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sCompFontComponent->GetSize(fCompFontComponent, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICompFontComponent::SetSize( ATETextDOM::Real size)
{
	ATEErr error = sCompFontComponent->SetSize(fCompFontComponent, static_cast<ATETextDOM::Float>(size));
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real ICompFontComponent::GetBaseline( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sCompFontComponent->GetBaseline(fCompFontComponent, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICompFontComponent::SetBaseline( ATETextDOM::Real baseline)
{
	ATEErr error = sCompFontComponent->SetBaseline(fCompFontComponent, static_cast<ATETextDOM::Float>(baseline));
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real ICompFontComponent::GetHorizontalScale( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sCompFontComponent->GetHorizontalScale(fCompFontComponent, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICompFontComponent::SetHorizontalScale( ATETextDOM::Real horizontalScale)
{
	ATEErr error = sCompFontComponent->SetHorizontalScale(fCompFontComponent, static_cast<ATETextDOM::Float>(horizontalScale));
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real ICompFontComponent::GetVerticalScale( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sCompFontComponent->GetVerticalScale(fCompFontComponent, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICompFontComponent::SetVerticalScale( ATETextDOM::Real verticalScale)
{
	ATEErr error = sCompFontComponent->SetVerticalScale(fCompFontComponent, static_cast<ATETextDOM::Float>(verticalScale));
	if(error) Throw_ATE_Exception(error);
}

bool ICompFontComponent::GetCenterGlyph( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFontComponent->GetCenterGlyph(fCompFontComponent, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICompFontComponent::SetCenterGlyph( bool centerglyph)
{
	ATEErr error = sCompFontComponent->SetCenterGlyph(fCompFontComponent, centerglyph);
	if(error) Throw_ATE_Exception(error);
}

bool ICompFontComponent::IsModified( ) const
{
	ATEBool8 ret;
	ATEErr error = sCompFontComponent->IsModified(fCompFontComponent, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --ICompFontSet--
//////////////////////////////////////////////

ICompFontSet::ICompFontSet()
:fCompFontSet(0)
{
}

ICompFontSet::ICompFontSet(CompFontSetRef compfontset)
:fCompFontSet(compfontset)
{
}

ICompFontSet::ICompFontSet(const ICompFontSet& src)
:fCompFontSet(src.fCompFontSet)
{
	sCompFontSet->AddRef(fCompFontSet);
}

ICompFontSet::~ICompFontSet()
{
	sCompFontSet->Release(fCompFontSet);
}

ICompFontSet& ICompFontSet::operator=(const ICompFontSet& rhs)
{
	if (&rhs != this)
	{
		sCompFontSet->Release(fCompFontSet);
		fCompFontSet = rhs.fCompFontSet;
		sCompFontSet->AddRef(fCompFontSet);
	}
	return *this;
}

bool ICompFontSet::operator==(const ICompFontSet& rhs) const
{
	return fCompFontSet == rhs.fCompFontSet;
}

bool ICompFontSet::operator!=(const ICompFontSet& rhs) const
{
	return !(*this == rhs);
}

CompFontSetRef ICompFontSet::GetRef() const
{
	return fCompFontSet;
}

bool ICompFontSet::IsNull() const
{
	return sCompFontSet->IsNull(fCompFontSet);
}

ATETextDOM::Int32 ICompFontSet::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontSet->GetSize(fCompFontSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICompFont ICompFontSet::GetFirst( ) const
{
	CompFontRef ret = 0;
	ATEErr error = sCompFontSet->GetFirst(fCompFontSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFont(ret);
}

ICompFont ICompFontSet::GetLast( ) const
{
	CompFontRef ret = 0;
	ATEErr error = sCompFontSet->GetLast(fCompFontSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFont(ret);
}

ICompFont ICompFontSet::Item( ATETextDOM::Int32 nIndex) const
{
	CompFontRef ret = 0;
	ATEErr error = sCompFontSet->Item(fCompFontSet, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFont(ret);
}

ATETextDOM::Int32 ICompFontSet::Find( ICompFont font) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontSet->Find(fCompFontSet, font.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFontSet::Remove( ATETextDOM::Int32 nIndex)
{
	ATEBool8 ret;
	ATEErr error = sCompFontSet->Remove(fCompFontSet, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ICompFontSet::Add( ICompFont font)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCompFontSet->Add(fCompFontSet, font.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICompFontSet::Replace( ATETextDOM::Int32 nIndex, ICompFont newFont)
{
	ATEBool8 ret;
	ATEErr error = sCompFontSet->Replace(fCompFontSet, nIndex, newFont.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICompFontSet::Update( ) const
{
	ATEErr error = sCompFontSet->Update(fCompFontSet);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IGlyphRun--
//////////////////////////////////////////////

IGlyphRun::IGlyphRun()
:fGlyphRun(0)
{
}

IGlyphRun::IGlyphRun(GlyphRunRef glyphrun)
:fGlyphRun(glyphrun)
{
}

IGlyphRun::IGlyphRun(const IGlyphRun& src)
:fGlyphRun(src.fGlyphRun)
{
	sGlyphRun->AddRef(fGlyphRun);
}

IGlyphRun::~IGlyphRun()
{
	sGlyphRun->Release(fGlyphRun);
}

IGlyphRun& IGlyphRun::operator=(const IGlyphRun& rhs)
{
	if (&rhs != this)
	{
		sGlyphRun->Release(fGlyphRun);
		fGlyphRun = rhs.fGlyphRun;
		sGlyphRun->AddRef(fGlyphRun);
	}
	return *this;
}

bool IGlyphRun::operator==(const IGlyphRun& rhs) const
{
	return fGlyphRun == rhs.fGlyphRun;
}

bool IGlyphRun::operator!=(const IGlyphRun& rhs) const
{
	return !(*this == rhs);
}

GlyphRunRef IGlyphRun::GetRef() const
{
	return fGlyphRun;
}

bool IGlyphRun::IsNull() const
{
	return sGlyphRun->IsNull(fGlyphRun);
}

ITextLine IGlyphRun::GetTextLine( ) const
{
	TextLineRef ret = 0;
	ATEErr error = sGlyphRun->GetTextLine(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextLine(ret);
}

ATETextDOM::Int32 IGlyphRun::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sGlyphRun->GetSize(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IGlyphRun::GetCharacterCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sGlyphRun->GetCharacterCount(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IArrayRealPoint IGlyphRun::GetOrigins( ) const
{
	ArrayRealPointRef ret = 0;
	ATEErr error = sGlyphRun->GetOrigins(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayRealPoint(ret);
}

IArrayGlyphID IGlyphRun::GetGlyphIDs( ) const
{
	ArrayGlyphIDRef ret = 0;
	ATEErr error = sGlyphRun->GetGlyphIDs(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayGlyphID(ret);
}

ATETextDOM::RealMatrix IGlyphRun::GetMatrix( ) const
{
	ATETextDOM::RealMatrix ret;
	ATETextDOM::FloatMatrix tempRet;
	ATEErr error = sGlyphRun->GetMatrix(fGlyphRun, &tempRet);
	ATEFloatMatrixToATERealMatrix(&tempRet,&ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICharFeatures IGlyphRun::GetCharFeatures( ) const
{
	CharFeaturesRef ret = 0;
	ATEErr error = sGlyphRun->GetCharFeatures(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

GlyphOrientation IGlyphRun::GetGlyphOrientation( ) const
{
	GlyphOrientation ret;
	ATEErr error = sGlyphRun->GetGlyphOrientation(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetAscent( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetAscent(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetDescent( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetDescent(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetTracking( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetTracking(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetSpaceGlyphWidth( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetSpaceGlyphWidth(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetDistanceToBaseline( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetDistanceToBaseline(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetUnderlinePosition( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetUnderlinePosition(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetUnderlineThickness( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetUnderlineThickness(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetMaxCapHeight( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetMaxCapHeight(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IGlyphRun::GetMinCapHeight( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sGlyphRun->GetMinCapHeight(fGlyphRun, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IFont IGlyphRun::GetFlattenedFont( ) const
{
	FontRef ret = 0;
	ATEErr error = sGlyphRun->GetFlattenedFont(fGlyphRun, &ret);
	if(error) Throw_ATE_Exception(error);
	return IFont(ret);
}

ATETextDOM::Int32 IGlyphRun::GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sGlyphRun->GetContents_AsUnicode(fGlyphRun, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IGlyphRun::GetContents( char* text, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sGlyphRun->GetContents_AsChar(fGlyphRun, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IGlyphRunsIterator--
//////////////////////////////////////////////

IGlyphRunsIterator::IGlyphRunsIterator()
:fGlyphRunsIterator(0)
{
}

IGlyphRunsIterator::IGlyphRunsIterator(GlyphRunsIteratorRef glyphrunsiterator)
:fGlyphRunsIterator(glyphrunsiterator)
{
}

IGlyphRunsIterator::IGlyphRunsIterator(const IGlyphRunsIterator& src)
:fGlyphRunsIterator(src.fGlyphRunsIterator)
{
	sGlyphRunsIterator->AddRef(fGlyphRunsIterator);
}

IGlyphRunsIterator::~IGlyphRunsIterator()
{
	sGlyphRunsIterator->Release(fGlyphRunsIterator);
}

IGlyphRunsIterator& IGlyphRunsIterator::operator=(const IGlyphRunsIterator& rhs)
{
	if (&rhs != this)
	{
		sGlyphRunsIterator->Release(fGlyphRunsIterator);
		fGlyphRunsIterator = rhs.fGlyphRunsIterator;
		sGlyphRunsIterator->AddRef(fGlyphRunsIterator);
	}
	return *this;
}

bool IGlyphRunsIterator::operator==(const IGlyphRunsIterator& rhs) const
{
	return fGlyphRunsIterator == rhs.fGlyphRunsIterator;
}

bool IGlyphRunsIterator::operator!=(const IGlyphRunsIterator& rhs) const
{
	return !(*this == rhs);
}

GlyphRunsIteratorRef IGlyphRunsIterator::GetRef() const
{
	return fGlyphRunsIterator;
}

bool IGlyphRunsIterator::IsNull() const
{
	return sGlyphRunsIterator->IsNull(fGlyphRunsIterator);
}

bool IGlyphRunsIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sGlyphRunsIterator->IsNotDone(fGlyphRunsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IGlyphRunsIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sGlyphRunsIterator->IsDone(fGlyphRunsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IGlyphRunsIterator::Next( )
{
	ATEErr error = sGlyphRunsIterator->Next(fGlyphRunsIterator);
	if(error) Throw_ATE_Exception(error);
}

IGlyphRun IGlyphRunsIterator::Item( ) const
{
	GlyphRunRef ret = 0;
	ATEErr error = sGlyphRunsIterator->Item(fGlyphRunsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyphRun(ret);
}

//////////////////////////////////////////////
// --IMojiKumi--
//////////////////////////////////////////////

IMojiKumi::IMojiKumi()
:fMojiKumi(0)
{
	ATEErr error = sMojiKumi->Initialize(&fMojiKumi);
	if(error) Throw_ATE_Exception(error);
}

IMojiKumi::IMojiKumi(MojiKumiRef mojikumi)
:fMojiKumi(mojikumi)
{
}

IMojiKumi::IMojiKumi(const IMojiKumi& src)
:fMojiKumi(src.fMojiKumi)
{
	sMojiKumi->AddRef(fMojiKumi);
}

IMojiKumi::~IMojiKumi()
{
	sMojiKumi->Release(fMojiKumi);
}

IMojiKumi& IMojiKumi::operator=(const IMojiKumi& rhs)
{
	if (&rhs != this)
	{
		sMojiKumi->Release(fMojiKumi);
		fMojiKumi = rhs.fMojiKumi;
		sMojiKumi->AddRef(fMojiKumi);
	}
	return *this;
}

bool IMojiKumi::operator==(const IMojiKumi& rhs) const
{
	ATEBool8 ret = false;
	ATEErr error = sMojiKumi->IsEqual(fMojiKumi, rhs.fMojiKumi, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IMojiKumi::operator!=(const IMojiKumi& rhs) const
{
	return !(*this == rhs);
}

MojiKumiRef IMojiKumi::GetRef() const
{
	return fMojiKumi;
}

bool IMojiKumi::IsNull() const
{
	return sMojiKumi->IsNull(fMojiKumi);
}

ATETextDOM::Int32 IMojiKumi::GetName( ATETextDOM::Unicode * name, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sMojiKumi->GetName(fMojiKumi, name, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IMojiKumi::GetNameSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sMojiKumi->GetNameSize(fMojiKumi, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IMojiKumi::SetName( const ATETextDOM::Unicode * name)
{
	ATEErr error = sMojiKumi->SetName(fMojiKumi, name);
	if(error) Throw_ATE_Exception(error);
}

bool IMojiKumi::MatchesPredefinedResourceTag( ATE::MojikumiTablePredefinedTag tag) const
{
	ATEBool8 ret;
	ATEErr error = sMojiKumi->MatchesPredefinedResourceTag(fMojiKumi, tag, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IMojiKumi::GetEntry( ATETextDOM::Int32 index, ATETextDOM::Float * minExpansion, ATETextDOM::Float * maxExpansion, ATETextDOM::Float * desiredExpansion) const
{
	ATEErr error = sMojiKumi->GetEntry(fMojiKumi, index, minExpansion, maxExpansion, desiredExpansion);
	if(error) Throw_ATE_Exception(error);
}

void IMojiKumi::SetEntry( ATETextDOM::Int32 index, ATETextDOM::Real minExpansion, ATETextDOM::Real maxExpansion, ATETextDOM::Real desiredExpansion)
{
	ATEErr error = sMojiKumi->SetEntry(fMojiKumi, index, static_cast<ATETextDOM::Float>(minExpansion), static_cast<ATETextDOM::Float>(maxExpansion), static_cast<ATETextDOM::Float>(desiredExpansion));
	if(error) Throw_ATE_Exception(error);
}

bool IMojiKumi::IsEquivalent( IMojiKumi rhsMojiKumi) const
{
	ATEBool8 ret;
	ATEErr error = sMojiKumi->IsEquivalent(fMojiKumi, rhsMojiKumi.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IMojiKumi::IsModified( ) const
{
	ATEBool8 ret;
	ATEErr error = sMojiKumi->IsModified(fMojiKumi, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IMojiKumi::IsPredefined( ) const
{
	ATEBool8 ret;
	ATEErr error = sMojiKumi->IsPredefined(fMojiKumi, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IMojiKumi IMojiKumi::Duplicate( ) const
{
	MojiKumiRef ret = 0;
	ATEErr error = sMojiKumi->Duplicate(fMojiKumi, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

//////////////////////////////////////////////
// --IMojiKumiSet--
//////////////////////////////////////////////

IMojiKumiSet::IMojiKumiSet()
:fMojiKumiSet(0)
{
}

IMojiKumiSet::IMojiKumiSet(MojiKumiSetRef mojikumiset)
:fMojiKumiSet(mojikumiset)
{
}

IMojiKumiSet::IMojiKumiSet(const IMojiKumiSet& src)
:fMojiKumiSet(src.fMojiKumiSet)
{
	sMojiKumiSet->AddRef(fMojiKumiSet);
}

IMojiKumiSet::~IMojiKumiSet()
{
	sMojiKumiSet->Release(fMojiKumiSet);
}

IMojiKumiSet& IMojiKumiSet::operator=(const IMojiKumiSet& rhs)
{
	if (&rhs != this)
	{
		sMojiKumiSet->Release(fMojiKumiSet);
		fMojiKumiSet = rhs.fMojiKumiSet;
		sMojiKumiSet->AddRef(fMojiKumiSet);
	}
	return *this;
}

bool IMojiKumiSet::operator==(const IMojiKumiSet& rhs) const
{
	return fMojiKumiSet == rhs.fMojiKumiSet;
}

bool IMojiKumiSet::operator!=(const IMojiKumiSet& rhs) const
{
	return !(*this == rhs);
}

MojiKumiSetRef IMojiKumiSet::GetRef() const
{
	return fMojiKumiSet;
}

bool IMojiKumiSet::IsNull() const
{
	return sMojiKumiSet->IsNull(fMojiKumiSet);
}

ATETextDOM::Int32 IMojiKumiSet::GetSize( )
{
	ATETextDOM::Int32 ret;
	ATEErr error = sMojiKumiSet->GetSize(fMojiKumiSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IMojiKumi IMojiKumiSet::GetFirst( )
{
	MojiKumiRef ret = 0;
	ATEErr error = sMojiKumiSet->GetFirst(fMojiKumiSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

IMojiKumi IMojiKumiSet::GetLast( )
{
	MojiKumiRef ret = 0;
	ATEErr error = sMojiKumiSet->GetLast(fMojiKumiSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

IMojiKumi IMojiKumiSet::Item( ATETextDOM::Int32 nIndex) const
{
	MojiKumiRef ret = 0;
	ATEErr error = sMojiKumiSet->Item(fMojiKumiSet, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

ATETextDOM::Int32 IMojiKumiSet::Find( const IMojiKumi mojiKumi)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sMojiKumiSet->Find_AsMojiKumi(fMojiKumiSet, mojiKumi.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IMojiKumiSet::Find( const ATETextDOM::Unicode* name)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sMojiKumiSet->Find_AsUnicode(fMojiKumiSet, name, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IMojiKumiSet::Find( MojikumiTablePredefinedTag tag)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sMojiKumiSet->Find_ByPredefinedMojikumiTag(fMojiKumiSet, tag, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IMojiKumiSet::Remove( ATETextDOM::Int32 nIndex)
{
	ATEBool8 ret;
	ATEErr error = sMojiKumiSet->Remove(fMojiKumiSet, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IMojiKumiSet::Add( IMojiKumi mojiKumi)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sMojiKumiSet->Add(fMojiKumiSet, mojiKumi.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IMojiKumiSet::Replace( ATETextDOM::Int32  nIndex, IMojiKumi mojiKumi)
{
	ATEBool8 ret;
	ATEErr error = sMojiKumiSet->Replace(fMojiKumiSet, nIndex, mojiKumi.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IMojiKumi IMojiKumiSet::CreateNewMojiKumi( const ATETextDOM::Unicode* name, ATETextDOM::Int32* nIndex)
{
	MojiKumiRef ret = 0;
	ATEErr error = sMojiKumiSet->CreateNewMojiKumi(fMojiKumiSet, name, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

//////////////////////////////////////////////
// --ITextFrame--
//////////////////////////////////////////////

ITextFrame::ITextFrame()
:fTextFrame(0)
{
}

ITextFrame::ITextFrame(TextFrameRef textframe)
:fTextFrame(textframe)
{
}

ITextFrame::ITextFrame(const ITextFrame& src)
:fTextFrame(src.fTextFrame)
{
	sTextFrame->AddRef(fTextFrame);
}

ITextFrame::~ITextFrame()
{
	sTextFrame->Release(fTextFrame);
}

ITextFrame& ITextFrame::operator=(const ITextFrame& rhs)
{
	if (&rhs != this)
	{
		sTextFrame->Release(fTextFrame);
		fTextFrame = rhs.fTextFrame;
		sTextFrame->AddRef(fTextFrame);
	}
	return *this;
}

bool ITextFrame::operator==(const ITextFrame& rhs) const
{
	ATEBool8 ret = false;
	ATEErr error = sTextFrame->IsEqual(fTextFrame, rhs.fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextFrame::operator!=(const ITextFrame& rhs) const
{
	return !(*this == rhs);
}

TextFrameRef ITextFrame::GetRef() const
{
	return fTextFrame;
}

bool ITextFrame::IsNull() const
{
	return sTextFrame->IsNull(fTextFrame);
}

IStory ITextFrame::GetStory( ) const
{
	StoryRef ret = 0;
	ATEErr error = sTextFrame->GetStory(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

ITextRange ITextFrame::GetTextRange( bool bIncludeOverflow) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextFrame->GetTextRange(fTextFrame, bIncludeOverflow, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

ITextLinesIterator ITextFrame::GetTextLinesIterator( ) const
{
	TextLinesIteratorRef ret = 0;
	ATEErr error = sTextFrame->GetTextLinesIterator(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextLinesIterator(ret);
}

FrameType ITextFrame::GetType( ) const
{
	FrameType ret;
	ATEErr error = sTextFrame->GetType(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LineOrientation ITextFrame::GetLineOrientation( ) const
{
	LineOrientation ret;
	ATEErr error = sTextFrame->GetLineOrientation(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextFrame::GetSelected( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextFrame->GetSelected(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::RealMatrix ITextFrame::GetMatrix( ) const
{
	ATETextDOM::RealMatrix ret;
	ATETextDOM::FloatMatrix tempRet;
	ATEErr error = sTextFrame->GetMatrix(fTextFrame, &tempRet);
	ATEFloatMatrixToATERealMatrix(&tempRet,&ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ITextFrame::GetRowCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextFrame->GetRowCount(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ITextFrame::GetColumnCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextFrame->GetColumnCount(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextFrame::GetRowMajorOrder( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextFrame->GetRowMajorOrder(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real ITextFrame::GetRowGutter( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sTextFrame->GetRowGutter(fTextFrame, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real ITextFrame::GetColumnGutter( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sTextFrame->GetColumnGutter(fTextFrame, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real ITextFrame::GetSpacing( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sTextFrame->GetSpacing(fTextFrame, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextFrame::GetOpticalAlignment( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextFrame->GetOpticalAlignment(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

#if SLO_COMPLEXSCRIPT
ParagraphDirection ITextFrame::GetStoryDirection( ) const
{
	ParagraphDirection ret;
	ATEErr error = sTextFrame->GetStoryDirection(fTextFrame, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}
#endif

void ITextFrame::SetRowCount( ATETextDOM::Int32 rowCount)
{
	ATEErr error = sTextFrame->SetRowCount(fTextFrame, rowCount);
	if(error) Throw_ATE_Exception(error);
}

void ITextFrame::SetColumnCount( ATETextDOM::Int32 columnCount)
{
	ATEErr error = sTextFrame->SetColumnCount(fTextFrame, columnCount);
	if(error) Throw_ATE_Exception(error);
}

void ITextFrame::SetRowMajorOrder( bool isRowMajor)
{
	ATEErr error = sTextFrame->SetRowMajorOrder(fTextFrame, isRowMajor);
	if(error) Throw_ATE_Exception(error);
}

void ITextFrame::SetRowGutter( ATETextDOM::Real gutter)
{
	ATEErr error = sTextFrame->SetRowGutter(fTextFrame, static_cast<ATETextDOM::Float>(gutter));
	if(error) Throw_ATE_Exception(error);
}

void ITextFrame::SetColumnGutter( ATETextDOM::Real gutter)
{
	ATEErr error = sTextFrame->SetColumnGutter(fTextFrame, static_cast<ATETextDOM::Float>(gutter));
	if(error) Throw_ATE_Exception(error);
}

void ITextFrame::SetSpacing( ATETextDOM::Real spacing)
{
	ATEErr error = sTextFrame->SetSpacing(fTextFrame, static_cast<ATETextDOM::Float>(spacing));
	if(error) Throw_ATE_Exception(error);
}

void ITextFrame::SetOpticalAlignment( bool isActive)
{
	ATEErr error = sTextFrame->SetOpticalAlignment(fTextFrame, isActive);
	if(error) Throw_ATE_Exception(error);
}

void ITextFrame::SetLineOrientation( LineOrientation lineOrientation)
{
	ATEErr error = sTextFrame->SetLineOrientation(fTextFrame, lineOrientation);
	if(error) Throw_ATE_Exception(error);
}

#if SLO_COMPLEXSCRIPT
void ITextFrame::SetStoryDirection( ParagraphDirection direction)
{
	ATEErr error = sTextFrame->SetStoryDirection(fTextFrame, direction);
	if(error) Throw_ATE_Exception(error);
}
#endif

//////////////////////////////////////////////
// --ITextFramesIterator--
//////////////////////////////////////////////

ITextFramesIterator::ITextFramesIterator()
:fTextFramesIterator(0)
{
}

ITextFramesIterator::ITextFramesIterator(TextFramesIteratorRef textframesiterator)
:fTextFramesIterator(textframesiterator)
{
}

ITextFramesIterator::ITextFramesIterator(const ITextFramesIterator& src)
:fTextFramesIterator(src.fTextFramesIterator)
{
	sTextFramesIterator->AddRef(fTextFramesIterator);
}

ITextFramesIterator::~ITextFramesIterator()
{
	sTextFramesIterator->Release(fTextFramesIterator);
}

ITextFramesIterator& ITextFramesIterator::operator=(const ITextFramesIterator& rhs)
{
	if (&rhs != this)
	{
		sTextFramesIterator->Release(fTextFramesIterator);
		fTextFramesIterator = rhs.fTextFramesIterator;
		sTextFramesIterator->AddRef(fTextFramesIterator);
	}
	return *this;
}

bool ITextFramesIterator::operator==(const ITextFramesIterator& rhs) const
{
	return fTextFramesIterator == rhs.fTextFramesIterator;
}

bool ITextFramesIterator::operator!=(const ITextFramesIterator& rhs) const
{
	return !(*this == rhs);
}

TextFramesIteratorRef ITextFramesIterator::GetRef() const
{
	return fTextFramesIterator;
}

bool ITextFramesIterator::IsNull() const
{
	return sTextFramesIterator->IsNull(fTextFramesIterator);
}

ITextFramesIterator::ITextFramesIterator( const ITextRange& range)
{
	ATEErr error = sTextFramesIterator->Initialize(range.GetRef(), &fTextFramesIterator);
	if(error) Throw_ATE_Exception(error);
}

bool ITextFramesIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextFramesIterator->IsNotDone(fTextFramesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextFramesIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextFramesIterator->IsDone(fTextFramesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextFramesIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextFramesIterator->IsEmpty(fTextFramesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextFramesIterator::Next( )
{
	ATEErr error = sTextFramesIterator->Next(fTextFramesIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITextFramesIterator::Previous( )
{
	ATEErr error = sTextFramesIterator->Previous(fTextFramesIterator);
	if(error) Throw_ATE_Exception(error);
}

ITextFrame ITextFramesIterator::Item( ) const
{
	TextFrameRef ret = 0;
	ATEErr error = sTextFramesIterator->Item(fTextFramesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextFrame(ret);
}

//////////////////////////////////////////////
// --ITextLine--
//////////////////////////////////////////////

ITextLine::ITextLine()
:fTextLine(0)
{
}

ITextLine::ITextLine(TextLineRef textline)
:fTextLine(textline)
{
}

ITextLine::ITextLine(const ITextLine& src)
:fTextLine(src.fTextLine)
{
	sTextLine->AddRef(fTextLine);
}

ITextLine::~ITextLine()
{
	sTextLine->Release(fTextLine);
}

ITextLine& ITextLine::operator=(const ITextLine& rhs)
{
	if (&rhs != this)
	{
		sTextLine->Release(fTextLine);
		fTextLine = rhs.fTextLine;
		sTextLine->AddRef(fTextLine);
	}
	return *this;
}

bool ITextLine::operator==(const ITextLine& rhs) const
{
	return fTextLine == rhs.fTextLine;
}

bool ITextLine::operator!=(const ITextLine& rhs) const
{
	return !(*this == rhs);
}

TextLineRef ITextLine::GetRef() const
{
	return fTextLine;
}

bool ITextLine::IsNull() const
{
	return sTextLine->IsNull(fTextLine);
}

IGlyphRunsIterator ITextLine::GetGlyphRunsIterator( ) const
{
	GlyphRunsIteratorRef ret = 0;
	ATEErr error = sTextLine->GetGlyphRunsIterator(fTextLine, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyphRunsIterator(ret);
}

IGlyphRunsIterator ITextLine::GetVisualGlyphRunsIterator( ) const
{
	GlyphRunsIteratorRef ret = 0;
	ATEErr error = sTextLine->GetVisualGlyphRunsIterator(fTextLine, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyphRunsIterator(ret);
}

ITextFrame ITextLine::GetTextFrame( ) const
{
	TextFrameRef ret = 0;
	ATEErr error = sTextLine->GetTextFrame(fTextLine, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextFrame(ret);
}

ITextRange ITextLine::GetTextRange( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextLine->GetTextRange(fTextLine, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

IArrayLine ITextLine::GetBaselines( ) const
{
	ArrayLineRef ret = 0;
	ATEErr error = sTextLine->GetBaselines(fTextLine, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayLine(ret);
}

//////////////////////////////////////////////
// --ITextLinesIterator--
//////////////////////////////////////////////

ITextLinesIterator::ITextLinesIterator()
:fTextLinesIterator(0)
{
}

ITextLinesIterator::ITextLinesIterator(TextLinesIteratorRef textlinesiterator)
:fTextLinesIterator(textlinesiterator)
{
}

ITextLinesIterator::ITextLinesIterator(const ITextLinesIterator& src)
:fTextLinesIterator(src.fTextLinesIterator)
{
	sTextLinesIterator->AddRef(fTextLinesIterator);
}

ITextLinesIterator::~ITextLinesIterator()
{
	sTextLinesIterator->Release(fTextLinesIterator);
}

ITextLinesIterator& ITextLinesIterator::operator=(const ITextLinesIterator& rhs)
{
	if (&rhs != this)
	{
		sTextLinesIterator->Release(fTextLinesIterator);
		fTextLinesIterator = rhs.fTextLinesIterator;
		sTextLinesIterator->AddRef(fTextLinesIterator);
	}
	return *this;
}

bool ITextLinesIterator::operator==(const ITextLinesIterator& rhs) const
{
	return fTextLinesIterator == rhs.fTextLinesIterator;
}

bool ITextLinesIterator::operator!=(const ITextLinesIterator& rhs) const
{
	return !(*this == rhs);
}

TextLinesIteratorRef ITextLinesIterator::GetRef() const
{
	return fTextLinesIterator;
}

bool ITextLinesIterator::IsNull() const
{
	return sTextLinesIterator->IsNull(fTextLinesIterator);
}

bool ITextLinesIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextLinesIterator->IsNotDone(fTextLinesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextLinesIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextLinesIterator->IsDone(fTextLinesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextLinesIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextLinesIterator->IsEmpty(fTextLinesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextLinesIterator::Next( )
{
	ATEErr error = sTextLinesIterator->Next(fTextLinesIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITextLinesIterator::Previous( )
{
	ATEErr error = sTextLinesIterator->Previous(fTextLinesIterator);
	if(error) Throw_ATE_Exception(error);
}

ITextLine ITextLinesIterator::Item( ) const
{
	TextLineRef ret = 0;
	ATEErr error = sTextLinesIterator->Item(fTextLinesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextLine(ret);
}

//////////////////////////////////////////////
// --ITextResources--
//////////////////////////////////////////////

ITextResources::ITextResources()
:fTextResources(0)
{
}

ITextResources::ITextResources(TextResourcesRef textresources)
:fTextResources(textresources)
{
}

ITextResources::ITextResources(const ITextResources& src)
:fTextResources(src.fTextResources)
{
	sTextResources->AddRef(fTextResources);
}

ITextResources::~ITextResources()
{
	sTextResources->Release(fTextResources);
}

ITextResources& ITextResources::operator=(const ITextResources& rhs)
{
	if (&rhs != this)
	{
		sTextResources->Release(fTextResources);
		fTextResources = rhs.fTextResources;
		sTextResources->AddRef(fTextResources);
	}
	return *this;
}

bool ITextResources::operator==(const ITextResources& rhs) const
{
	return fTextResources == rhs.fTextResources;
}

bool ITextResources::operator!=(const ITextResources& rhs) const
{
	return !(*this == rhs);
}

TextResourcesRef ITextResources::GetRef() const
{
	return fTextResources;
}

bool ITextResources::IsNull() const
{
	return sTextResources->IsNull(fTextResources);
}

ITextResources ITextResources::GetTextResources( )
{
	TextResourcesRef ret = 0;
	ATEErr error = sTextResources->GetTextResources(fTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextResources(ret);
}

//////////////////////////////////////////////
// --IApplicationTextResources--
//////////////////////////////////////////////

IApplicationTextResources::IApplicationTextResources()
:fApplicationTextResources(0)
{
}

IApplicationTextResources::IApplicationTextResources(ApplicationTextResourcesRef applicationtextresources)
:fApplicationTextResources(applicationtextresources)
{
}

IApplicationTextResources::IApplicationTextResources(const IApplicationTextResources& src)
:fApplicationTextResources(src.fApplicationTextResources)
{
	sApplicationTextResources->AddRef(fApplicationTextResources);
}

IApplicationTextResources::~IApplicationTextResources()
{
	sApplicationTextResources->Release(fApplicationTextResources);
}

IApplicationTextResources& IApplicationTextResources::operator=(const IApplicationTextResources& rhs)
{
	if (&rhs != this)
	{
		sApplicationTextResources->Release(fApplicationTextResources);
		fApplicationTextResources = rhs.fApplicationTextResources;
		sApplicationTextResources->AddRef(fApplicationTextResources);
	}
	return *this;
}

bool IApplicationTextResources::operator==(const IApplicationTextResources& rhs) const
{
	return fApplicationTextResources == rhs.fApplicationTextResources;
}

bool IApplicationTextResources::operator!=(const IApplicationTextResources& rhs) const
{
	return !(*this == rhs);
}

ApplicationTextResourcesRef IApplicationTextResources::GetRef() const
{
	return fApplicationTextResources;
}

bool IApplicationTextResources::IsNull() const
{
	return sApplicationTextResources->IsNull(fApplicationTextResources);
}

ITextResources IApplicationTextResources::GetTextResources( )
{
	TextResourcesRef ret = 0;
	ATEErr error = sApplicationTextResources->GetTextResources(fApplicationTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextResources(ret);
}

IKinsokuSet IApplicationTextResources::GetKinsokuSet( ) const
{
	KinsokuSetRef ret = 0;
	ATEErr error = sApplicationTextResources->GetKinsokuSet(fApplicationTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsokuSet(ret);
}

IMojiKumiSet IApplicationTextResources::GetMojiKumiSet( ) const
{
	MojiKumiSetRef ret = 0;
	ATEErr error = sApplicationTextResources->GetMojiKumiSet(fApplicationTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumiSet(ret);
}

ICompFontClassSet IApplicationTextResources::GetCompFontClassSet( ) const
{
	CompFontClassSetRef ret = 0;
	ATEErr error = sApplicationTextResources->GetCompFontClassSet(fApplicationTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontClassSet(ret);
}

ICompFontSet IApplicationTextResources::GetCompFontSet( ) const
{
	CompFontSetRef ret = 0;
	ATEErr error = sApplicationTextResources->GetCompFontSet(fApplicationTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontSet(ret);
}

//////////////////////////////////////////////
// --IDocumentTextResources--
//////////////////////////////////////////////

IDocumentTextResources::IDocumentTextResources()
:fDocumentTextResources(0)
{
}

IDocumentTextResources::IDocumentTextResources(DocumentTextResourcesRef documenttextresources)
:fDocumentTextResources(documenttextresources)
{
}

IDocumentTextResources::IDocumentTextResources(const IDocumentTextResources& src)
:fDocumentTextResources(src.fDocumentTextResources)
{
	sDocumentTextResources->AddRef(fDocumentTextResources);
}

IDocumentTextResources::~IDocumentTextResources()
{
	sDocumentTextResources->Release(fDocumentTextResources);
}

IDocumentTextResources& IDocumentTextResources::operator=(const IDocumentTextResources& rhs)
{
	if (&rhs != this)
	{
		sDocumentTextResources->Release(fDocumentTextResources);
		fDocumentTextResources = rhs.fDocumentTextResources;
		sDocumentTextResources->AddRef(fDocumentTextResources);
	}
	return *this;
}

bool IDocumentTextResources::operator==(const IDocumentTextResources& rhs) const
{
	return fDocumentTextResources == rhs.fDocumentTextResources;
}

bool IDocumentTextResources::operator!=(const IDocumentTextResources& rhs) const
{
	return !(*this == rhs);
}

DocumentTextResourcesRef IDocumentTextResources::GetRef() const
{
	return fDocumentTextResources;
}

bool IDocumentTextResources::IsNull() const
{
	return sDocumentTextResources->IsNull(fDocumentTextResources);
}

IKinsokuSet IDocumentTextResources::GetKinsokuSet( ) const
{
	KinsokuSetRef ret = 0;
	ATEErr error = sDocumentTextResources->GetKinsokuSet(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsokuSet(ret);
}

IMojiKumiSet IDocumentTextResources::GetMojiKumiSet( ) const
{
	MojiKumiSetRef ret = 0;
	ATEErr error = sDocumentTextResources->GetMojiKumiSet(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumiSet(ret);
}

ICompFontClassSet IDocumentTextResources::GetCompFontClassSet( ) const
{
	CompFontClassSetRef ret = 0;
	ATEErr error = sDocumentTextResources->GetCompFontClassSet(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontClassSet(ret);
}

ICompFontSet IDocumentTextResources::GetCompFontSet( ) const
{
	CompFontSetRef ret = 0;
	ATEErr error = sDocumentTextResources->GetCompFontSet(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICompFontSet(ret);
}

ITextResources IDocumentTextResources::GetTextResources( )
{
	TextResourcesRef ret = 0;
	ATEErr error = sDocumentTextResources->GetTextResources(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextResources(ret);
}

IFind IDocumentTextResources::GetFind( )
{
	FindRef ret = 0;
	ATEErr error = sDocumentTextResources->GetFind(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IFind(ret);
}

ISpell IDocumentTextResources::GetSpell( )
{
	SpellRef ret = 0;
	ATEErr error = sDocumentTextResources->GetSpell(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ISpell(ret);
}

IGlyph IDocumentTextResources::GetGlyphAndAlternates( ) const
{
	GlyphRef ret = 0;
	ATEErr error = sDocumentTextResources->GetGlyphAndAlternates(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

IGlyph IDocumentTextResources::GetAlternateGlyph( ) const
{
	GlyphRef ret = 0;
	ATEErr error = sDocumentTextResources->GetAlternateGlyph(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

void IDocumentTextResources::InsertAlternateGlyph( const ATETextDOM::Unicode* theCharacters, const ATEGlyphID glyphID, const char* otFeatureArray, ATETextDOM::Int32 otFeatureCount, const ATETextDOM::Int32* otFeatureIndexArray, bool leaveSelected)
{
	ATEErr error = sDocumentTextResources->InsertAlternateGlyph(fDocumentTextResources, theCharacters, glyphID, otFeatureArray, otFeatureCount, otFeatureIndexArray, leaveSelected);
	if(error) Throw_ATE_Exception(error);
}

IArrayInteger IDocumentTextResources::GetAlternatesAvailableThroughoutSelection( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sDocumentTextResources->GetAlternatesAvailableThroughoutSelection(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

JapaneseAlternateFeature IDocumentTextResources::GetJapaneseAlternateFeatureInSelection( bool* isFeature) const
{
	JapaneseAlternateFeature ret;
	ATEBool8 isFeatureRet;
	ATEErr error = sDocumentTextResources->GetJapaneseAlternateFeatureInSelection(fDocumentTextResources, &isFeatureRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isFeature) *isFeature = isFeatureRet;
	return ret;
}

void IDocumentTextResources::SetJapaneseAlternateFeatureInSelection( JapaneseAlternateFeature feature)
{
	ATEErr error = sDocumentTextResources->SetJapaneseAlternateFeatureInSelection(fDocumentTextResources, feature);
	if(error) Throw_ATE_Exception(error);
}

ICharStyles IDocumentTextResources::GetCharStylesInDocument( ) const
{
	CharStylesRef ret = 0;
	ATEErr error = sDocumentTextResources->GetCharStylesInDocument(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyles(ret);
}

IParaStyles IDocumentTextResources::GetParaStylesInDocument( ) const
{
	ParaStylesRef ret = 0;
	ATEErr error = sDocumentTextResources->GetParaStylesInDocument(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyles(ret);
}

ICharStyle IDocumentTextResources::GetCharStyle( const ATETextDOM::Unicode* pName) const
{
	CharStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->GetCharStyle(fDocumentTextResources, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyle(ret);
}

IParaStyle IDocumentTextResources::GetParaStyle( const ATETextDOM::Unicode* pName) const
{
	ParaStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->GetParaStyle(fDocumentTextResources, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyle(ret);
}

ICharStyle IDocumentTextResources::GetNormalCharStyle( ) const
{
	CharStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->GetNormalCharStyle(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyle(ret);
}

IParaStyle IDocumentTextResources::GetNormalParaStyle( ) const
{
	ParaStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->GetNormalParaStyle(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyle(ret);
}

void IDocumentTextResources::ResetNormalCharStyle( )
{
	ATEErr error = sDocumentTextResources->ResetNormalCharStyle(fDocumentTextResources);
	if(error) Throw_ATE_Exception(error);
}

void IDocumentTextResources::ResetNormalParaStyle( )
{
	ATEErr error = sDocumentTextResources->ResetNormalParaStyle(fDocumentTextResources);
	if(error) Throw_ATE_Exception(error);
}

ICharStyle IDocumentTextResources::CreateCharStyle( const ATETextDOM::Unicode* pName)
{
	CharStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->CreateCharStyle(fDocumentTextResources, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyle(ret);
}

IParaStyle IDocumentTextResources::CreateParaStyle( const ATETextDOM::Unicode* pName)
{
	ParaStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->CreateParaStyle(fDocumentTextResources, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyle(ret);
}

ICharStyle IDocumentTextResources::CreateCharStyleWithFeatures( const ATETextDOM::Unicode* pName, ICharFeatures pFeatures)
{
	CharStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->CreateCharStyleWithFeatures(fDocumentTextResources, pName, pFeatures.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyle(ret);
}

IParaStyle IDocumentTextResources::CreateParaStyleWithFeatures( const ATETextDOM::Unicode* pName, IParaFeatures pFeatures)
{
	ParaStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->CreateParaStyleWithFeatures(fDocumentTextResources, pName, pFeatures.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyle(ret);
}

bool IDocumentTextResources::RemoveCharStyle( const ATETextDOM::Unicode* pName)
{
	ATEBool8 ret;
	ATEErr error = sDocumentTextResources->RemoveCharStyle(fDocumentTextResources, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IDocumentTextResources::RemoveParaStyle( const ATETextDOM::Unicode* pName)
{
	ATEBool8 ret;
	ATEErr error = sDocumentTextResources->RemoveParaStyle(fDocumentTextResources, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::ImportCharStyles( ITextResources pSrcResources)
{
	ATEErr error = sDocumentTextResources->ImportCharStyles(fDocumentTextResources, pSrcResources.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IDocumentTextResources::ImportParaStyles( ITextResources pSrcResources)
{
	ATEErr error = sDocumentTextResources->ImportParaStyles(fDocumentTextResources, pSrcResources.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IDocumentTextResources::SetUseSmartQuotes( bool smartQuotesAreOn)
{
	ATEErr error = sDocumentTextResources->SetUseSmartQuotes(fDocumentTextResources, smartQuotesAreOn);
	if(error) Throw_ATE_Exception(error);
}

void IDocumentTextResources::SetSmartDoubleQuoteCharacters( ATETextDOM::Unicode openQuote, ATETextDOM::Unicode closeQuote, Language language)
{
	ATEErr error = sDocumentTextResources->SetSmartDoubleQuoteCharacters(fDocumentTextResources, openQuote, closeQuote, language);
	if(error) Throw_ATE_Exception(error);
}

void IDocumentTextResources::SetSmartSingleQuoteCharacters( ATETextDOM::Unicode openQuote, ATETextDOM::Unicode closeQuote, Language language)
{
	ATEErr error = sDocumentTextResources->SetSmartSingleQuoteCharacters(fDocumentTextResources, openQuote, closeQuote, language);
	if(error) Throw_ATE_Exception(error);
}

bool IDocumentTextResources::UseSmartQuotes( )
{
	ATEBool8 ret;
	ATEErr error = sDocumentTextResources->UseSmartQuotes(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::GetSmartDoubleQuoteCharacters( ATETextDOM::Unicode* openQuote, ATETextDOM::Unicode* closeQuote, Language language)
{
	ATEErr error = sDocumentTextResources->GetSmartDoubleQuoteCharacters(fDocumentTextResources, openQuote, closeQuote, language);
	if(error) Throw_ATE_Exception(error);
}

void IDocumentTextResources::GetSmartSingleQuoteCharacters( ATETextDOM::Unicode* openQuote, ATETextDOM::Unicode* closeQuote, Language language)
{
	ATEErr error = sDocumentTextResources->GetSmartSingleQuoteCharacters(fDocumentTextResources, openQuote, closeQuote, language);
	if(error) Throw_ATE_Exception(error);
}

ICharFeatures IDocumentTextResources::GetInsertionCharFeatures( ) const
{
	CharFeaturesRef ret = 0;
	ATEErr error = sDocumentTextResources->GetInsertionCharFeatures(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

ICharStyle IDocumentTextResources::GetInsertionCharStyle( ) const
{
	CharStyleRef ret = 0;
	ATEErr error = sDocumentTextResources->GetInsertionCharStyle(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyle(ret);
}

void IDocumentTextResources::SetInsertionFeaturesAndStyle( const ICharFeatures& pFeatures, const ATETextDOM::Unicode* pStyleName)
{
	ATEErr error = sDocumentTextResources->SetInsertionFeaturesAndStyle(fDocumentTextResources, pFeatures.GetRef(), pStyleName);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real IDocumentTextResources::GetSuperscriptSize( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sDocumentTextResources->GetSuperscriptSize(fDocumentTextResources, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetSuperscriptSize( ATETextDOM::Real value)
{
	ATEErr error = sDocumentTextResources->SetSuperscriptSize(fDocumentTextResources, static_cast<ATETextDOM::Float>(value));
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real IDocumentTextResources::GetSuperscriptPosition( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sDocumentTextResources->GetSuperscriptPosition(fDocumentTextResources, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetSuperscriptPosition( ATETextDOM::Real value)
{
	ATEErr error = sDocumentTextResources->SetSuperscriptPosition(fDocumentTextResources, static_cast<ATETextDOM::Float>(value));
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real IDocumentTextResources::GetSubscriptSize( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sDocumentTextResources->GetSubscriptSize(fDocumentTextResources, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetSubscriptSize( ATETextDOM::Real value)
{
	ATEErr error = sDocumentTextResources->SetSubscriptSize(fDocumentTextResources, static_cast<ATETextDOM::Float>(value));
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real IDocumentTextResources::GetSubscriptPosition( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sDocumentTextResources->GetSubscriptPosition(fDocumentTextResources, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetSubscriptPosition( ATETextDOM::Real value)
{
	ATEErr error = sDocumentTextResources->SetSubscriptPosition(fDocumentTextResources, static_cast<ATETextDOM::Float>(value));
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real IDocumentTextResources::GetSmallCapSize( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sDocumentTextResources->GetSmallCapSize(fDocumentTextResources, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetSmallCapSize( ATETextDOM::Real value)
{
	ATEErr error = sDocumentTextResources->SetSmallCapSize(fDocumentTextResources, static_cast<ATETextDOM::Float>(value));
	if(error) Throw_ATE_Exception(error);
}

bool IDocumentTextResources::GetShowHiddenCharacters( ) const
{
	ATEBool8 ret;
	ATEErr error = sDocumentTextResources->GetShowHiddenCharacters(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetShowHiddenCharacters( bool value)
{
	ATEErr error = sDocumentTextResources->SetShowHiddenCharacters(fDocumentTextResources, value);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 IDocumentTextResources::GetGreekingSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sDocumentTextResources->GetGreekingSize(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetGreekingSize( ATETextDOM::Int32 value)
{
	ATEErr error = sDocumentTextResources->SetGreekingSize(fDocumentTextResources, value);
	if(error) Throw_ATE_Exception(error);
}

bool IDocumentTextResources::GetHighlightSubstituteFonts( ) const
{
	ATEBool8 ret;
	ATEErr error = sDocumentTextResources->GetHighlightSubstituteFonts(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetHighlightSubstituteFonts( bool value)
{
	ATEErr error = sDocumentTextResources->SetHighlightSubstituteFonts(fDocumentTextResources, value);
	if(error) Throw_ATE_Exception(error);
}

bool IDocumentTextResources::GetHighlightAlternateGlyphs( ) const
{
	ATEBool8 ret;
	ATEErr error = sDocumentTextResources->GetHighlightAlternateGlyphs(fDocumentTextResources, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IDocumentTextResources::SetHighlightAlternateGlyphs( bool value)
{
	ATEErr error = sDocumentTextResources->SetHighlightAlternateGlyphs(fDocumentTextResources, value);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IVersionInfo--
//////////////////////////////////////////////

IVersionInfo::IVersionInfo()
:fVersionInfo(0)
{
	ATEErr error = sVersionInfo->Initialize(&fVersionInfo);
	if(error) Throw_ATE_Exception(error);
}

IVersionInfo::IVersionInfo(VersionInfoRef versioninfo)
:fVersionInfo(versioninfo)
{
}

IVersionInfo::IVersionInfo(const IVersionInfo& src)
:fVersionInfo(src.fVersionInfo)
{
	sVersionInfo->AddRef(fVersionInfo);
}

IVersionInfo::~IVersionInfo()
{
	sVersionInfo->Release(fVersionInfo);
}

IVersionInfo& IVersionInfo::operator=(const IVersionInfo& rhs)
{
	if (&rhs != this)
	{
		sVersionInfo->Release(fVersionInfo);
		fVersionInfo = rhs.fVersionInfo;
		sVersionInfo->AddRef(fVersionInfo);
	}
	return *this;
}

bool IVersionInfo::operator==(const IVersionInfo& rhs) const
{
	return fVersionInfo == rhs.fVersionInfo;
}

bool IVersionInfo::operator!=(const IVersionInfo& rhs) const
{
	return !(*this == rhs);
}

VersionInfoRef IVersionInfo::GetRef() const
{
	return fVersionInfo;
}

bool IVersionInfo::IsNull() const
{
	return sVersionInfo->IsNull(fVersionInfo);
}

int IVersionInfo::GetMajorVersion( )
{
	int ret;
	ATEErr error = sVersionInfo->GetMajorVersion(fVersionInfo, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

int IVersionInfo::GetMinorVersion( )
{
	int ret;
	ATEErr error = sVersionInfo->GetMinorVersion(fVersionInfo, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

int IVersionInfo::GetSubMinorVersion( )
{
	int ret;
	ATEErr error = sVersionInfo->GetSubMinorVersion(fVersionInfo, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

int IVersionInfo::GetVersionAsUTF16( ASUTF16* versionString, int maxLength)
{
	int ret;
	ATEErr error = sVersionInfo->GetVersionAsUTF16(fVersionInfo, versionString, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayApplicationPaintRef--
//////////////////////////////////////////////

IArrayApplicationPaintRef::IArrayApplicationPaintRef()
:fArrayApplicationPaintRef(0)
{
}

IArrayApplicationPaintRef::IArrayApplicationPaintRef(ArrayApplicationPaintRefRef arrayapplicationpaintref)
:fArrayApplicationPaintRef(arrayapplicationpaintref)
{
}

IArrayApplicationPaintRef::IArrayApplicationPaintRef(const IArrayApplicationPaintRef& src)
:fArrayApplicationPaintRef(src.fArrayApplicationPaintRef)
{
	sArrayApplicationPaintRef->AddRef(fArrayApplicationPaintRef);
}

IArrayApplicationPaintRef::~IArrayApplicationPaintRef()
{
	sArrayApplicationPaintRef->Release(fArrayApplicationPaintRef);
}

IArrayApplicationPaintRef& IArrayApplicationPaintRef::operator=(const IArrayApplicationPaintRef& rhs)
{
	if (&rhs != this)
	{
		sArrayApplicationPaintRef->Release(fArrayApplicationPaintRef);
		fArrayApplicationPaintRef = rhs.fArrayApplicationPaintRef;
		sArrayApplicationPaintRef->AddRef(fArrayApplicationPaintRef);
	}
	return *this;
}

bool IArrayApplicationPaintRef::operator==(const IArrayApplicationPaintRef& rhs) const
{
	return fArrayApplicationPaintRef == rhs.fArrayApplicationPaintRef;
}

bool IArrayApplicationPaintRef::operator!=(const IArrayApplicationPaintRef& rhs) const
{
	return !(*this == rhs);
}

ArrayApplicationPaintRefRef IArrayApplicationPaintRef::GetRef() const
{
	return fArrayApplicationPaintRef;
}

bool IArrayApplicationPaintRef::IsNull() const
{
	return sArrayApplicationPaintRef->IsNull(fArrayApplicationPaintRef);
}

ATETextDOM::Int32 IArrayApplicationPaintRef::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayApplicationPaintRef->GetSize(fArrayApplicationPaintRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IApplicationPaint IArrayApplicationPaintRef::GetFirst( ) const
{
	ApplicationPaintRef ret = 0;
	ATEErr error = sArrayApplicationPaintRef->GetFirst(fArrayApplicationPaintRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IApplicationPaint(ret);
}

IApplicationPaint IArrayApplicationPaintRef::GetLast( ) const
{
	ApplicationPaintRef ret = 0;
	ATEErr error = sArrayApplicationPaintRef->GetLast(fArrayApplicationPaintRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IApplicationPaint(ret);
}

IApplicationPaint IArrayApplicationPaintRef::Item( ATETextDOM::Int32 index) const
{
	ApplicationPaintRef ret = 0;
	ATEErr error = sArrayApplicationPaintRef->Item(fArrayApplicationPaintRef, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return IApplicationPaint(ret);
}

//////////////////////////////////////////////
// --IArrayReal--
//////////////////////////////////////////////

IArrayReal::IArrayReal()
:fArrayReal(0)
{
}

IArrayReal::IArrayReal(ArrayRealRef arrayreal)
:fArrayReal(arrayreal)
{
}

IArrayReal::IArrayReal(const IArrayReal& src)
:fArrayReal(src.fArrayReal)
{
	sArrayReal->AddRef(fArrayReal);
}

IArrayReal::~IArrayReal()
{
	sArrayReal->Release(fArrayReal);
}

IArrayReal& IArrayReal::operator=(const IArrayReal& rhs)
{
	if (&rhs != this)
	{
		sArrayReal->Release(fArrayReal);
		fArrayReal = rhs.fArrayReal;
		sArrayReal->AddRef(fArrayReal);
	}
	return *this;
}

bool IArrayReal::operator==(const IArrayReal& rhs) const
{
	return fArrayReal == rhs.fArrayReal;
}

bool IArrayReal::operator!=(const IArrayReal& rhs) const
{
	return !(*this == rhs);
}

ArrayRealRef IArrayReal::GetRef() const
{
	return fArrayReal;
}

bool IArrayReal::IsNull() const
{
	return sArrayReal->IsNull(fArrayReal);
}

ATETextDOM::Int32 IArrayReal::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayReal->GetSize(fArrayReal, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IArrayReal::GetFirst( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sArrayReal->GetFirst(fArrayReal, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IArrayReal::GetLast( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sArrayReal->GetLast(fArrayReal, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Real IArrayReal::Item( ATETextDOM::Int32 index) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sArrayReal->Item(fArrayReal, index, &tempRet);
	ret = tempRet;
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayBool--
//////////////////////////////////////////////

IArrayBool::IArrayBool()
:fArrayBool(0)
{
}

IArrayBool::IArrayBool(ArrayBoolRef arraybool)
:fArrayBool(arraybool)
{
}

IArrayBool::IArrayBool(const IArrayBool& src)
:fArrayBool(src.fArrayBool)
{
	sArrayBool->AddRef(fArrayBool);
}

IArrayBool::~IArrayBool()
{
	sArrayBool->Release(fArrayBool);
}

IArrayBool& IArrayBool::operator=(const IArrayBool& rhs)
{
	if (&rhs != this)
	{
		sArrayBool->Release(fArrayBool);
		fArrayBool = rhs.fArrayBool;
		sArrayBool->AddRef(fArrayBool);
	}
	return *this;
}

bool IArrayBool::operator==(const IArrayBool& rhs) const
{
	return fArrayBool == rhs.fArrayBool;
}

bool IArrayBool::operator!=(const IArrayBool& rhs) const
{
	return !(*this == rhs);
}

ArrayBoolRef IArrayBool::GetRef() const
{
	return fArrayBool;
}

bool IArrayBool::IsNull() const
{
	return sArrayBool->IsNull(fArrayBool);
}

ATETextDOM::Int32 IArrayBool::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayBool->GetSize(fArrayBool, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IArrayBool::GetFirst( ) const
{
	ATEBool8 ret;
	ATEErr error = sArrayBool->GetFirst(fArrayBool, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IArrayBool::GetLast( ) const
{
	ATEBool8 ret;
	ATEErr error = sArrayBool->GetLast(fArrayBool, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IArrayBool::Item( ATETextDOM::Int32 index) const
{
	ATEBool8 ret;
	ATEErr error = sArrayBool->Item(fArrayBool, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayInteger--
//////////////////////////////////////////////

IArrayInteger::IArrayInteger()
:fArrayInteger(0)
{
}

IArrayInteger::IArrayInteger(ArrayIntegerRef arrayinteger)
:fArrayInteger(arrayinteger)
{
}

IArrayInteger::IArrayInteger(const IArrayInteger& src)
:fArrayInteger(src.fArrayInteger)
{
	sArrayInteger->AddRef(fArrayInteger);
}

IArrayInteger::~IArrayInteger()
{
	sArrayInteger->Release(fArrayInteger);
}

IArrayInteger& IArrayInteger::operator=(const IArrayInteger& rhs)
{
	if (&rhs != this)
	{
		sArrayInteger->Release(fArrayInteger);
		fArrayInteger = rhs.fArrayInteger;
		sArrayInteger->AddRef(fArrayInteger);
	}
	return *this;
}

bool IArrayInteger::operator==(const IArrayInteger& rhs) const
{
	return fArrayInteger == rhs.fArrayInteger;
}

bool IArrayInteger::operator!=(const IArrayInteger& rhs) const
{
	return !(*this == rhs);
}

ArrayIntegerRef IArrayInteger::GetRef() const
{
	return fArrayInteger;
}

bool IArrayInteger::IsNull() const
{
	return sArrayInteger->IsNull(fArrayInteger);
}

ATETextDOM::Int32 IArrayInteger::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayInteger->GetSize(fArrayInteger, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IArrayInteger::GetFirst( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayInteger->GetFirst(fArrayInteger, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IArrayInteger::GetLast( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayInteger->GetLast(fArrayInteger, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IArrayInteger::Item( ATETextDOM::Int32 index) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayInteger->Item(fArrayInteger, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayLineCapType--
//////////////////////////////////////////////

IArrayLineCapType::IArrayLineCapType()
:fArrayLineCapType(0)
{
}

IArrayLineCapType::IArrayLineCapType(ArrayLineCapTypeRef arraylinecaptype)
:fArrayLineCapType(arraylinecaptype)
{
}

IArrayLineCapType::IArrayLineCapType(const IArrayLineCapType& src)
:fArrayLineCapType(src.fArrayLineCapType)
{
	sArrayLineCapType->AddRef(fArrayLineCapType);
}

IArrayLineCapType::~IArrayLineCapType()
{
	sArrayLineCapType->Release(fArrayLineCapType);
}

IArrayLineCapType& IArrayLineCapType::operator=(const IArrayLineCapType& rhs)
{
	if (&rhs != this)
	{
		sArrayLineCapType->Release(fArrayLineCapType);
		fArrayLineCapType = rhs.fArrayLineCapType;
		sArrayLineCapType->AddRef(fArrayLineCapType);
	}
	return *this;
}

bool IArrayLineCapType::operator==(const IArrayLineCapType& rhs) const
{
	return fArrayLineCapType == rhs.fArrayLineCapType;
}

bool IArrayLineCapType::operator!=(const IArrayLineCapType& rhs) const
{
	return !(*this == rhs);
}

ArrayLineCapTypeRef IArrayLineCapType::GetRef() const
{
	return fArrayLineCapType;
}

bool IArrayLineCapType::IsNull() const
{
	return sArrayLineCapType->IsNull(fArrayLineCapType);
}

ATETextDOM::Int32 IArrayLineCapType::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayLineCapType->GetSize(fArrayLineCapType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LineCapType IArrayLineCapType::GetFirst( ) const
{
	LineCapType ret;
	ATEErr error = sArrayLineCapType->GetFirst(fArrayLineCapType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LineCapType IArrayLineCapType::GetLast( ) const
{
	LineCapType ret;
	ATEErr error = sArrayLineCapType->GetLast(fArrayLineCapType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LineCapType IArrayLineCapType::Item( ATETextDOM::Int32 index) const
{
	LineCapType ret;
	ATEErr error = sArrayLineCapType->Item(fArrayLineCapType, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayFigureStyle--
//////////////////////////////////////////////

IArrayFigureStyle::IArrayFigureStyle()
:fArrayFigureStyle(0)
{
}

IArrayFigureStyle::IArrayFigureStyle(ArrayFigureStyleRef arrayfigurestyle)
:fArrayFigureStyle(arrayfigurestyle)
{
}

IArrayFigureStyle::IArrayFigureStyle(const IArrayFigureStyle& src)
:fArrayFigureStyle(src.fArrayFigureStyle)
{
	sArrayFigureStyle->AddRef(fArrayFigureStyle);
}

IArrayFigureStyle::~IArrayFigureStyle()
{
	sArrayFigureStyle->Release(fArrayFigureStyle);
}

IArrayFigureStyle& IArrayFigureStyle::operator=(const IArrayFigureStyle& rhs)
{
	if (&rhs != this)
	{
		sArrayFigureStyle->Release(fArrayFigureStyle);
		fArrayFigureStyle = rhs.fArrayFigureStyle;
		sArrayFigureStyle->AddRef(fArrayFigureStyle);
	}
	return *this;
}

bool IArrayFigureStyle::operator==(const IArrayFigureStyle& rhs) const
{
	return fArrayFigureStyle == rhs.fArrayFigureStyle;
}

bool IArrayFigureStyle::operator!=(const IArrayFigureStyle& rhs) const
{
	return !(*this == rhs);
}

ArrayFigureStyleRef IArrayFigureStyle::GetRef() const
{
	return fArrayFigureStyle;
}

bool IArrayFigureStyle::IsNull() const
{
	return sArrayFigureStyle->IsNull(fArrayFigureStyle);
}

ATETextDOM::Int32 IArrayFigureStyle::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayFigureStyle->GetSize(fArrayFigureStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FigureStyle IArrayFigureStyle::GetFirst( ) const
{
	FigureStyle ret;
	ATEErr error = sArrayFigureStyle->GetFirst(fArrayFigureStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FigureStyle IArrayFigureStyle::GetLast( ) const
{
	FigureStyle ret;
	ATEErr error = sArrayFigureStyle->GetLast(fArrayFigureStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FigureStyle IArrayFigureStyle::Item( ATETextDOM::Int32 index) const
{
	FigureStyle ret;
	ATEErr error = sArrayFigureStyle->Item(fArrayFigureStyle, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayLineJoinType--
//////////////////////////////////////////////

IArrayLineJoinType::IArrayLineJoinType()
:fArrayLineJoinType(0)
{
}

IArrayLineJoinType::IArrayLineJoinType(ArrayLineJoinTypeRef arraylinejointype)
:fArrayLineJoinType(arraylinejointype)
{
}

IArrayLineJoinType::IArrayLineJoinType(const IArrayLineJoinType& src)
:fArrayLineJoinType(src.fArrayLineJoinType)
{
	sArrayLineJoinType->AddRef(fArrayLineJoinType);
}

IArrayLineJoinType::~IArrayLineJoinType()
{
	sArrayLineJoinType->Release(fArrayLineJoinType);
}

IArrayLineJoinType& IArrayLineJoinType::operator=(const IArrayLineJoinType& rhs)
{
	if (&rhs != this)
	{
		sArrayLineJoinType->Release(fArrayLineJoinType);
		fArrayLineJoinType = rhs.fArrayLineJoinType;
		sArrayLineJoinType->AddRef(fArrayLineJoinType);
	}
	return *this;
}

bool IArrayLineJoinType::operator==(const IArrayLineJoinType& rhs) const
{
	return fArrayLineJoinType == rhs.fArrayLineJoinType;
}

bool IArrayLineJoinType::operator!=(const IArrayLineJoinType& rhs) const
{
	return !(*this == rhs);
}

ArrayLineJoinTypeRef IArrayLineJoinType::GetRef() const
{
	return fArrayLineJoinType;
}

bool IArrayLineJoinType::IsNull() const
{
	return sArrayLineJoinType->IsNull(fArrayLineJoinType);
}

ATETextDOM::Int32 IArrayLineJoinType::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayLineJoinType->GetSize(fArrayLineJoinType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LineJoinType IArrayLineJoinType::GetFirst( ) const
{
	LineJoinType ret;
	ATEErr error = sArrayLineJoinType->GetFirst(fArrayLineJoinType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LineJoinType IArrayLineJoinType::GetLast( ) const
{
	LineJoinType ret;
	ATEErr error = sArrayLineJoinType->GetLast(fArrayLineJoinType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LineJoinType IArrayLineJoinType::Item( ATETextDOM::Int32 index) const
{
	LineJoinType ret;
	ATEErr error = sArrayLineJoinType->Item(fArrayLineJoinType, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayWariChuJustification--
//////////////////////////////////////////////

IArrayWariChuJustification::IArrayWariChuJustification()
:fArrayWariChuJustification(0)
{
}

IArrayWariChuJustification::IArrayWariChuJustification(ArrayWariChuJustificationRef arraywarichujustification)
:fArrayWariChuJustification(arraywarichujustification)
{
}

IArrayWariChuJustification::IArrayWariChuJustification(const IArrayWariChuJustification& src)
:fArrayWariChuJustification(src.fArrayWariChuJustification)
{
	sArrayWariChuJustification->AddRef(fArrayWariChuJustification);
}

IArrayWariChuJustification::~IArrayWariChuJustification()
{
	sArrayWariChuJustification->Release(fArrayWariChuJustification);
}

IArrayWariChuJustification& IArrayWariChuJustification::operator=(const IArrayWariChuJustification& rhs)
{
	if (&rhs != this)
	{
		sArrayWariChuJustification->Release(fArrayWariChuJustification);
		fArrayWariChuJustification = rhs.fArrayWariChuJustification;
		sArrayWariChuJustification->AddRef(fArrayWariChuJustification);
	}
	return *this;
}

bool IArrayWariChuJustification::operator==(const IArrayWariChuJustification& rhs) const
{
	return fArrayWariChuJustification == rhs.fArrayWariChuJustification;
}

bool IArrayWariChuJustification::operator!=(const IArrayWariChuJustification& rhs) const
{
	return !(*this == rhs);
}

ArrayWariChuJustificationRef IArrayWariChuJustification::GetRef() const
{
	return fArrayWariChuJustification;
}

bool IArrayWariChuJustification::IsNull() const
{
	return sArrayWariChuJustification->IsNull(fArrayWariChuJustification);
}

ATETextDOM::Int32 IArrayWariChuJustification::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayWariChuJustification->GetSize(fArrayWariChuJustification, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

WariChuJustification IArrayWariChuJustification::GetFirst( ) const
{
	WariChuJustification ret;
	ATEErr error = sArrayWariChuJustification->GetFirst(fArrayWariChuJustification, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

WariChuJustification IArrayWariChuJustification::GetLast( ) const
{
	WariChuJustification ret;
	ATEErr error = sArrayWariChuJustification->GetLast(fArrayWariChuJustification, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

WariChuJustification IArrayWariChuJustification::Item( ATETextDOM::Int32 index) const
{
	WariChuJustification ret;
	ATEErr error = sArrayWariChuJustification->Item(fArrayWariChuJustification, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayStyleRunAlignment--
//////////////////////////////////////////////

IArrayStyleRunAlignment::IArrayStyleRunAlignment()
:fArrayStyleRunAlignment(0)
{
}

IArrayStyleRunAlignment::IArrayStyleRunAlignment(ArrayStyleRunAlignmentRef arraystylerunalignment)
:fArrayStyleRunAlignment(arraystylerunalignment)
{
}

IArrayStyleRunAlignment::IArrayStyleRunAlignment(const IArrayStyleRunAlignment& src)
:fArrayStyleRunAlignment(src.fArrayStyleRunAlignment)
{
	sArrayStyleRunAlignment->AddRef(fArrayStyleRunAlignment);
}

IArrayStyleRunAlignment::~IArrayStyleRunAlignment()
{
	sArrayStyleRunAlignment->Release(fArrayStyleRunAlignment);
}

IArrayStyleRunAlignment& IArrayStyleRunAlignment::operator=(const IArrayStyleRunAlignment& rhs)
{
	if (&rhs != this)
	{
		sArrayStyleRunAlignment->Release(fArrayStyleRunAlignment);
		fArrayStyleRunAlignment = rhs.fArrayStyleRunAlignment;
		sArrayStyleRunAlignment->AddRef(fArrayStyleRunAlignment);
	}
	return *this;
}

bool IArrayStyleRunAlignment::operator==(const IArrayStyleRunAlignment& rhs) const
{
	return fArrayStyleRunAlignment == rhs.fArrayStyleRunAlignment;
}

bool IArrayStyleRunAlignment::operator!=(const IArrayStyleRunAlignment& rhs) const
{
	return !(*this == rhs);
}

ArrayStyleRunAlignmentRef IArrayStyleRunAlignment::GetRef() const
{
	return fArrayStyleRunAlignment;
}

bool IArrayStyleRunAlignment::IsNull() const
{
	return sArrayStyleRunAlignment->IsNull(fArrayStyleRunAlignment);
}

ATETextDOM::Int32 IArrayStyleRunAlignment::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayStyleRunAlignment->GetSize(fArrayStyleRunAlignment, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

StyleRunAlignment IArrayStyleRunAlignment::GetFirst( ) const
{
	StyleRunAlignment ret;
	ATEErr error = sArrayStyleRunAlignment->GetFirst(fArrayStyleRunAlignment, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

StyleRunAlignment IArrayStyleRunAlignment::GetLast( ) const
{
	StyleRunAlignment ret;
	ATEErr error = sArrayStyleRunAlignment->GetLast(fArrayStyleRunAlignment, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

StyleRunAlignment IArrayStyleRunAlignment::Item( ATETextDOM::Int32 index) const
{
	StyleRunAlignment ret;
	ATEErr error = sArrayStyleRunAlignment->Item(fArrayStyleRunAlignment, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayAutoKernType--
//////////////////////////////////////////////

IArrayAutoKernType::IArrayAutoKernType()
:fArrayAutoKernType(0)
{
}

IArrayAutoKernType::IArrayAutoKernType(ArrayAutoKernTypeRef arrayautokerntype)
:fArrayAutoKernType(arrayautokerntype)
{
}

IArrayAutoKernType::IArrayAutoKernType(const IArrayAutoKernType& src)
:fArrayAutoKernType(src.fArrayAutoKernType)
{
	sArrayAutoKernType->AddRef(fArrayAutoKernType);
}

IArrayAutoKernType::~IArrayAutoKernType()
{
	sArrayAutoKernType->Release(fArrayAutoKernType);
}

IArrayAutoKernType& IArrayAutoKernType::operator=(const IArrayAutoKernType& rhs)
{
	if (&rhs != this)
	{
		sArrayAutoKernType->Release(fArrayAutoKernType);
		fArrayAutoKernType = rhs.fArrayAutoKernType;
		sArrayAutoKernType->AddRef(fArrayAutoKernType);
	}
	return *this;
}

bool IArrayAutoKernType::operator==(const IArrayAutoKernType& rhs) const
{
	return fArrayAutoKernType == rhs.fArrayAutoKernType;
}

bool IArrayAutoKernType::operator!=(const IArrayAutoKernType& rhs) const
{
	return !(*this == rhs);
}

ArrayAutoKernTypeRef IArrayAutoKernType::GetRef() const
{
	return fArrayAutoKernType;
}

bool IArrayAutoKernType::IsNull() const
{
	return sArrayAutoKernType->IsNull(fArrayAutoKernType);
}

ATETextDOM::Int32 IArrayAutoKernType::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayAutoKernType->GetSize(fArrayAutoKernType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

AutoKernType IArrayAutoKernType::GetFirst( ) const
{
	AutoKernType ret;
	ATEErr error = sArrayAutoKernType->GetFirst(fArrayAutoKernType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

AutoKernType IArrayAutoKernType::GetLast( ) const
{
	AutoKernType ret;
	ATEErr error = sArrayAutoKernType->GetLast(fArrayAutoKernType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

AutoKernType IArrayAutoKernType::Item( ATETextDOM::Int32 index) const
{
	AutoKernType ret;
	ATEErr error = sArrayAutoKernType->Item(fArrayAutoKernType, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayBaselineDirection--
//////////////////////////////////////////////

IArrayBaselineDirection::IArrayBaselineDirection()
:fArrayBaselineDirection(0)
{
}

IArrayBaselineDirection::IArrayBaselineDirection(ArrayBaselineDirectionRef arraybaselinedirection)
:fArrayBaselineDirection(arraybaselinedirection)
{
}

IArrayBaselineDirection::IArrayBaselineDirection(const IArrayBaselineDirection& src)
:fArrayBaselineDirection(src.fArrayBaselineDirection)
{
	sArrayBaselineDirection->AddRef(fArrayBaselineDirection);
}

IArrayBaselineDirection::~IArrayBaselineDirection()
{
	sArrayBaselineDirection->Release(fArrayBaselineDirection);
}

IArrayBaselineDirection& IArrayBaselineDirection::operator=(const IArrayBaselineDirection& rhs)
{
	if (&rhs != this)
	{
		sArrayBaselineDirection->Release(fArrayBaselineDirection);
		fArrayBaselineDirection = rhs.fArrayBaselineDirection;
		sArrayBaselineDirection->AddRef(fArrayBaselineDirection);
	}
	return *this;
}

bool IArrayBaselineDirection::operator==(const IArrayBaselineDirection& rhs) const
{
	return fArrayBaselineDirection == rhs.fArrayBaselineDirection;
}

bool IArrayBaselineDirection::operator!=(const IArrayBaselineDirection& rhs) const
{
	return !(*this == rhs);
}

ArrayBaselineDirectionRef IArrayBaselineDirection::GetRef() const
{
	return fArrayBaselineDirection;
}

bool IArrayBaselineDirection::IsNull() const
{
	return sArrayBaselineDirection->IsNull(fArrayBaselineDirection);
}

ATETextDOM::Int32 IArrayBaselineDirection::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayBaselineDirection->GetSize(fArrayBaselineDirection, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

BaselineDirection IArrayBaselineDirection::GetFirst( ) const
{
	BaselineDirection ret;
	ATEErr error = sArrayBaselineDirection->GetFirst(fArrayBaselineDirection, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

BaselineDirection IArrayBaselineDirection::GetLast( ) const
{
	BaselineDirection ret;
	ATEErr error = sArrayBaselineDirection->GetLast(fArrayBaselineDirection, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

BaselineDirection IArrayBaselineDirection::Item( ATETextDOM::Int32 index) const
{
	BaselineDirection ret;
	ATEErr error = sArrayBaselineDirection->Item(fArrayBaselineDirection, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayLanguage--
//////////////////////////////////////////////

IArrayLanguage::IArrayLanguage()
:fArrayLanguage(0)
{
}

IArrayLanguage::IArrayLanguage(ArrayLanguageRef arraylanguage)
:fArrayLanguage(arraylanguage)
{
}

IArrayLanguage::IArrayLanguage(const IArrayLanguage& src)
:fArrayLanguage(src.fArrayLanguage)
{
	sArrayLanguage->AddRef(fArrayLanguage);
}

IArrayLanguage::~IArrayLanguage()
{
	sArrayLanguage->Release(fArrayLanguage);
}

IArrayLanguage& IArrayLanguage::operator=(const IArrayLanguage& rhs)
{
	if (&rhs != this)
	{
		sArrayLanguage->Release(fArrayLanguage);
		fArrayLanguage = rhs.fArrayLanguage;
		sArrayLanguage->AddRef(fArrayLanguage);
	}
	return *this;
}

bool IArrayLanguage::operator==(const IArrayLanguage& rhs) const
{
	return fArrayLanguage == rhs.fArrayLanguage;
}

bool IArrayLanguage::operator!=(const IArrayLanguage& rhs) const
{
	return !(*this == rhs);
}

ArrayLanguageRef IArrayLanguage::GetRef() const
{
	return fArrayLanguage;
}

bool IArrayLanguage::IsNull() const
{
	return sArrayLanguage->IsNull(fArrayLanguage);
}

ATETextDOM::Int32 IArrayLanguage::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayLanguage->GetSize(fArrayLanguage, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

Language IArrayLanguage::GetFirst( ) const
{
	Language ret;
	ATEErr error = sArrayLanguage->GetFirst(fArrayLanguage, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

Language IArrayLanguage::GetLast( ) const
{
	Language ret;
	ATEErr error = sArrayLanguage->GetLast(fArrayLanguage, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

Language IArrayLanguage::Item( ATETextDOM::Int32 index) const
{
	Language ret;
	ATEErr error = sArrayLanguage->Item(fArrayLanguage, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayFontCapsOption--
//////////////////////////////////////////////

IArrayFontCapsOption::IArrayFontCapsOption()
:fArrayFontCapsOption(0)
{
}

IArrayFontCapsOption::IArrayFontCapsOption(ArrayFontCapsOptionRef arrayfontcapsoption)
:fArrayFontCapsOption(arrayfontcapsoption)
{
}

IArrayFontCapsOption::IArrayFontCapsOption(const IArrayFontCapsOption& src)
:fArrayFontCapsOption(src.fArrayFontCapsOption)
{
	sArrayFontCapsOption->AddRef(fArrayFontCapsOption);
}

IArrayFontCapsOption::~IArrayFontCapsOption()
{
	sArrayFontCapsOption->Release(fArrayFontCapsOption);
}

IArrayFontCapsOption& IArrayFontCapsOption::operator=(const IArrayFontCapsOption& rhs)
{
	if (&rhs != this)
	{
		sArrayFontCapsOption->Release(fArrayFontCapsOption);
		fArrayFontCapsOption = rhs.fArrayFontCapsOption;
		sArrayFontCapsOption->AddRef(fArrayFontCapsOption);
	}
	return *this;
}

bool IArrayFontCapsOption::operator==(const IArrayFontCapsOption& rhs) const
{
	return fArrayFontCapsOption == rhs.fArrayFontCapsOption;
}

bool IArrayFontCapsOption::operator!=(const IArrayFontCapsOption& rhs) const
{
	return !(*this == rhs);
}

ArrayFontCapsOptionRef IArrayFontCapsOption::GetRef() const
{
	return fArrayFontCapsOption;
}

bool IArrayFontCapsOption::IsNull() const
{
	return sArrayFontCapsOption->IsNull(fArrayFontCapsOption);
}

ATETextDOM::Int32 IArrayFontCapsOption::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayFontCapsOption->GetSize(fArrayFontCapsOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontCapsOption IArrayFontCapsOption::GetFirst( ) const
{
	FontCapsOption ret;
	ATEErr error = sArrayFontCapsOption->GetFirst(fArrayFontCapsOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontCapsOption IArrayFontCapsOption::GetLast( ) const
{
	FontCapsOption ret;
	ATEErr error = sArrayFontCapsOption->GetLast(fArrayFontCapsOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontCapsOption IArrayFontCapsOption::Item( ATETextDOM::Int32 index) const
{
	FontCapsOption ret;
	ATEErr error = sArrayFontCapsOption->Item(fArrayFontCapsOption, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayFontBaselineOption--
//////////////////////////////////////////////

IArrayFontBaselineOption::IArrayFontBaselineOption()
:fArrayFontBaselineOption(0)
{
}

IArrayFontBaselineOption::IArrayFontBaselineOption(ArrayFontBaselineOptionRef arrayfontbaselineoption)
:fArrayFontBaselineOption(arrayfontbaselineoption)
{
}

IArrayFontBaselineOption::IArrayFontBaselineOption(const IArrayFontBaselineOption& src)
:fArrayFontBaselineOption(src.fArrayFontBaselineOption)
{
	sArrayFontBaselineOption->AddRef(fArrayFontBaselineOption);
}

IArrayFontBaselineOption::~IArrayFontBaselineOption()
{
	sArrayFontBaselineOption->Release(fArrayFontBaselineOption);
}

IArrayFontBaselineOption& IArrayFontBaselineOption::operator=(const IArrayFontBaselineOption& rhs)
{
	if (&rhs != this)
	{
		sArrayFontBaselineOption->Release(fArrayFontBaselineOption);
		fArrayFontBaselineOption = rhs.fArrayFontBaselineOption;
		sArrayFontBaselineOption->AddRef(fArrayFontBaselineOption);
	}
	return *this;
}

bool IArrayFontBaselineOption::operator==(const IArrayFontBaselineOption& rhs) const
{
	return fArrayFontBaselineOption == rhs.fArrayFontBaselineOption;
}

bool IArrayFontBaselineOption::operator!=(const IArrayFontBaselineOption& rhs) const
{
	return !(*this == rhs);
}

ArrayFontBaselineOptionRef IArrayFontBaselineOption::GetRef() const
{
	return fArrayFontBaselineOption;
}

bool IArrayFontBaselineOption::IsNull() const
{
	return sArrayFontBaselineOption->IsNull(fArrayFontBaselineOption);
}

ATETextDOM::Int32 IArrayFontBaselineOption::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayFontBaselineOption->GetSize(fArrayFontBaselineOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontBaselineOption IArrayFontBaselineOption::GetFirst( ) const
{
	FontBaselineOption ret;
	ATEErr error = sArrayFontBaselineOption->GetFirst(fArrayFontBaselineOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontBaselineOption IArrayFontBaselineOption::GetLast( ) const
{
	FontBaselineOption ret;
	ATEErr error = sArrayFontBaselineOption->GetLast(fArrayFontBaselineOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontBaselineOption IArrayFontBaselineOption::Item( ATETextDOM::Int32 index) const
{
	FontBaselineOption ret;
	ATEErr error = sArrayFontBaselineOption->Item(fArrayFontBaselineOption, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayFontOpenTypePositionOption--
//////////////////////////////////////////////

IArrayFontOpenTypePositionOption::IArrayFontOpenTypePositionOption()
:fArrayFontOpenTypePositionOption(0)
{
}

IArrayFontOpenTypePositionOption::IArrayFontOpenTypePositionOption(ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption)
:fArrayFontOpenTypePositionOption(arrayfontopentypepositionoption)
{
}

IArrayFontOpenTypePositionOption::IArrayFontOpenTypePositionOption(const IArrayFontOpenTypePositionOption& src)
:fArrayFontOpenTypePositionOption(src.fArrayFontOpenTypePositionOption)
{
	sArrayFontOpenTypePositionOption->AddRef(fArrayFontOpenTypePositionOption);
}

IArrayFontOpenTypePositionOption::~IArrayFontOpenTypePositionOption()
{
	sArrayFontOpenTypePositionOption->Release(fArrayFontOpenTypePositionOption);
}

IArrayFontOpenTypePositionOption& IArrayFontOpenTypePositionOption::operator=(const IArrayFontOpenTypePositionOption& rhs)
{
	if (&rhs != this)
	{
		sArrayFontOpenTypePositionOption->Release(fArrayFontOpenTypePositionOption);
		fArrayFontOpenTypePositionOption = rhs.fArrayFontOpenTypePositionOption;
		sArrayFontOpenTypePositionOption->AddRef(fArrayFontOpenTypePositionOption);
	}
	return *this;
}

bool IArrayFontOpenTypePositionOption::operator==(const IArrayFontOpenTypePositionOption& rhs) const
{
	return fArrayFontOpenTypePositionOption == rhs.fArrayFontOpenTypePositionOption;
}

bool IArrayFontOpenTypePositionOption::operator!=(const IArrayFontOpenTypePositionOption& rhs) const
{
	return !(*this == rhs);
}

ArrayFontOpenTypePositionOptionRef IArrayFontOpenTypePositionOption::GetRef() const
{
	return fArrayFontOpenTypePositionOption;
}

bool IArrayFontOpenTypePositionOption::IsNull() const
{
	return sArrayFontOpenTypePositionOption->IsNull(fArrayFontOpenTypePositionOption);
}

ATETextDOM::Int32 IArrayFontOpenTypePositionOption::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayFontOpenTypePositionOption->GetSize(fArrayFontOpenTypePositionOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontOpenTypePositionOption IArrayFontOpenTypePositionOption::GetFirst( ) const
{
	FontOpenTypePositionOption ret;
	ATEErr error = sArrayFontOpenTypePositionOption->GetFirst(fArrayFontOpenTypePositionOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontOpenTypePositionOption IArrayFontOpenTypePositionOption::GetLast( ) const
{
	FontOpenTypePositionOption ret;
	ATEErr error = sArrayFontOpenTypePositionOption->GetLast(fArrayFontOpenTypePositionOption, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

FontOpenTypePositionOption IArrayFontOpenTypePositionOption::Item( ATETextDOM::Int32 index) const
{
	FontOpenTypePositionOption ret;
	ATEErr error = sArrayFontOpenTypePositionOption->Item(fArrayFontOpenTypePositionOption, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayUnderlinePosition--
//////////////////////////////////////////////

IArrayUnderlinePosition::IArrayUnderlinePosition()
:fArrayUnderlinePosition(0)
{
}

IArrayUnderlinePosition::IArrayUnderlinePosition(ArrayUnderlinePositionRef arrayunderlineposition)
:fArrayUnderlinePosition(arrayunderlineposition)
{
}

IArrayUnderlinePosition::IArrayUnderlinePosition(const IArrayUnderlinePosition& src)
:fArrayUnderlinePosition(src.fArrayUnderlinePosition)
{
	sArrayUnderlinePosition->AddRef(fArrayUnderlinePosition);
}

IArrayUnderlinePosition::~IArrayUnderlinePosition()
{
	sArrayUnderlinePosition->Release(fArrayUnderlinePosition);
}

IArrayUnderlinePosition& IArrayUnderlinePosition::operator=(const IArrayUnderlinePosition& rhs)
{
	if (&rhs != this)
	{
		sArrayUnderlinePosition->Release(fArrayUnderlinePosition);
		fArrayUnderlinePosition = rhs.fArrayUnderlinePosition;
		sArrayUnderlinePosition->AddRef(fArrayUnderlinePosition);
	}
	return *this;
}

bool IArrayUnderlinePosition::operator==(const IArrayUnderlinePosition& rhs) const
{
	return fArrayUnderlinePosition == rhs.fArrayUnderlinePosition;
}

bool IArrayUnderlinePosition::operator!=(const IArrayUnderlinePosition& rhs) const
{
	return !(*this == rhs);
}

ArrayUnderlinePositionRef IArrayUnderlinePosition::GetRef() const
{
	return fArrayUnderlinePosition;
}

bool IArrayUnderlinePosition::IsNull() const
{
	return sArrayUnderlinePosition->IsNull(fArrayUnderlinePosition);
}

ATETextDOM::Int32 IArrayUnderlinePosition::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayUnderlinePosition->GetSize(fArrayUnderlinePosition, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

UnderlinePosition IArrayUnderlinePosition::GetFirst( ) const
{
	UnderlinePosition ret;
	ATEErr error = sArrayUnderlinePosition->GetFirst(fArrayUnderlinePosition, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

UnderlinePosition IArrayUnderlinePosition::GetLast( ) const
{
	UnderlinePosition ret;
	ATEErr error = sArrayUnderlinePosition->GetLast(fArrayUnderlinePosition, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

UnderlinePosition IArrayUnderlinePosition::Item( ATETextDOM::Int32 index) const
{
	UnderlinePosition ret;
	ATEErr error = sArrayUnderlinePosition->Item(fArrayUnderlinePosition, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayStrikethroughPosition--
//////////////////////////////////////////////

IArrayStrikethroughPosition::IArrayStrikethroughPosition()
:fArrayStrikethroughPosition(0)
{
}

IArrayStrikethroughPosition::IArrayStrikethroughPosition(ArrayStrikethroughPositionRef arraystrikethroughposition)
:fArrayStrikethroughPosition(arraystrikethroughposition)
{
}

IArrayStrikethroughPosition::IArrayStrikethroughPosition(const IArrayStrikethroughPosition& src)
:fArrayStrikethroughPosition(src.fArrayStrikethroughPosition)
{
	sArrayStrikethroughPosition->AddRef(fArrayStrikethroughPosition);
}

IArrayStrikethroughPosition::~IArrayStrikethroughPosition()
{
	sArrayStrikethroughPosition->Release(fArrayStrikethroughPosition);
}

IArrayStrikethroughPosition& IArrayStrikethroughPosition::operator=(const IArrayStrikethroughPosition& rhs)
{
	if (&rhs != this)
	{
		sArrayStrikethroughPosition->Release(fArrayStrikethroughPosition);
		fArrayStrikethroughPosition = rhs.fArrayStrikethroughPosition;
		sArrayStrikethroughPosition->AddRef(fArrayStrikethroughPosition);
	}
	return *this;
}

bool IArrayStrikethroughPosition::operator==(const IArrayStrikethroughPosition& rhs) const
{
	return fArrayStrikethroughPosition == rhs.fArrayStrikethroughPosition;
}

bool IArrayStrikethroughPosition::operator!=(const IArrayStrikethroughPosition& rhs) const
{
	return !(*this == rhs);
}

ArrayStrikethroughPositionRef IArrayStrikethroughPosition::GetRef() const
{
	return fArrayStrikethroughPosition;
}

bool IArrayStrikethroughPosition::IsNull() const
{
	return sArrayStrikethroughPosition->IsNull(fArrayStrikethroughPosition);
}

ATETextDOM::Int32 IArrayStrikethroughPosition::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayStrikethroughPosition->GetSize(fArrayStrikethroughPosition, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

StrikethroughPosition IArrayStrikethroughPosition::GetFirst( ) const
{
	StrikethroughPosition ret;
	ATEErr error = sArrayStrikethroughPosition->GetFirst(fArrayStrikethroughPosition, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

StrikethroughPosition IArrayStrikethroughPosition::GetLast( ) const
{
	StrikethroughPosition ret;
	ATEErr error = sArrayStrikethroughPosition->GetLast(fArrayStrikethroughPosition, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

StrikethroughPosition IArrayStrikethroughPosition::Item( ATETextDOM::Int32 index) const
{
	StrikethroughPosition ret;
	ATEErr error = sArrayStrikethroughPosition->Item(fArrayStrikethroughPosition, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayParagraphJustification--
//////////////////////////////////////////////

IArrayParagraphJustification::IArrayParagraphJustification()
:fArrayParagraphJustification(0)
{
}

IArrayParagraphJustification::IArrayParagraphJustification(ArrayParagraphJustificationRef arrayparagraphjustification)
:fArrayParagraphJustification(arrayparagraphjustification)
{
}

IArrayParagraphJustification::IArrayParagraphJustification(const IArrayParagraphJustification& src)
:fArrayParagraphJustification(src.fArrayParagraphJustification)
{
	sArrayParagraphJustification->AddRef(fArrayParagraphJustification);
}

IArrayParagraphJustification::~IArrayParagraphJustification()
{
	sArrayParagraphJustification->Release(fArrayParagraphJustification);
}

IArrayParagraphJustification& IArrayParagraphJustification::operator=(const IArrayParagraphJustification& rhs)
{
	if (&rhs != this)
	{
		sArrayParagraphJustification->Release(fArrayParagraphJustification);
		fArrayParagraphJustification = rhs.fArrayParagraphJustification;
		sArrayParagraphJustification->AddRef(fArrayParagraphJustification);
	}
	return *this;
}

bool IArrayParagraphJustification::operator==(const IArrayParagraphJustification& rhs) const
{
	return fArrayParagraphJustification == rhs.fArrayParagraphJustification;
}

bool IArrayParagraphJustification::operator!=(const IArrayParagraphJustification& rhs) const
{
	return !(*this == rhs);
}

ArrayParagraphJustificationRef IArrayParagraphJustification::GetRef() const
{
	return fArrayParagraphJustification;
}

bool IArrayParagraphJustification::IsNull() const
{
	return sArrayParagraphJustification->IsNull(fArrayParagraphJustification);
}

ATETextDOM::Int32 IArrayParagraphJustification::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayParagraphJustification->GetSize(fArrayParagraphJustification, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ParagraphJustification IArrayParagraphJustification::GetFirst( ) const
{
	ParagraphJustification ret;
	ATEErr error = sArrayParagraphJustification->GetFirst(fArrayParagraphJustification, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ParagraphJustification IArrayParagraphJustification::GetLast( ) const
{
	ParagraphJustification ret;
	ATEErr error = sArrayParagraphJustification->GetLast(fArrayParagraphJustification, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ParagraphJustification IArrayParagraphJustification::Item( ATETextDOM::Int32 index) const
{
	ParagraphJustification ret;
	ATEErr error = sArrayParagraphJustification->Item(fArrayParagraphJustification, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayArrayReal--
//////////////////////////////////////////////

IArrayArrayReal::IArrayArrayReal()
:fArrayArrayReal(0)
{
}

IArrayArrayReal::IArrayArrayReal(ArrayArrayRealRef arrayarrayreal)
:fArrayArrayReal(arrayarrayreal)
{
}

IArrayArrayReal::IArrayArrayReal(const IArrayArrayReal& src)
:fArrayArrayReal(src.fArrayArrayReal)
{
	sArrayArrayReal->AddRef(fArrayArrayReal);
}

IArrayArrayReal::~IArrayArrayReal()
{
	sArrayArrayReal->Release(fArrayArrayReal);
}

IArrayArrayReal& IArrayArrayReal::operator=(const IArrayArrayReal& rhs)
{
	if (&rhs != this)
	{
		sArrayArrayReal->Release(fArrayArrayReal);
		fArrayArrayReal = rhs.fArrayArrayReal;
		sArrayArrayReal->AddRef(fArrayArrayReal);
	}
	return *this;
}

bool IArrayArrayReal::operator==(const IArrayArrayReal& rhs) const
{
	return fArrayArrayReal == rhs.fArrayArrayReal;
}

bool IArrayArrayReal::operator!=(const IArrayArrayReal& rhs) const
{
	return !(*this == rhs);
}

ArrayArrayRealRef IArrayArrayReal::GetRef() const
{
	return fArrayArrayReal;
}

bool IArrayArrayReal::IsNull() const
{
	return sArrayArrayReal->IsNull(fArrayArrayReal);
}

ATETextDOM::Int32 IArrayArrayReal::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayArrayReal->GetSize(fArrayArrayReal, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IArrayReal IArrayArrayReal::GetFirst( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sArrayArrayReal->GetFirst(fArrayArrayReal, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IArrayArrayReal::GetLast( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sArrayArrayReal->GetLast(fArrayArrayReal, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IArrayArrayReal::Item( ATETextDOM::Int32 index) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sArrayArrayReal->Item(fArrayArrayReal, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

//////////////////////////////////////////////
// --IArrayBurasagariType--
//////////////////////////////////////////////

IArrayBurasagariType::IArrayBurasagariType()
:fArrayBurasagariType(0)
{
}

IArrayBurasagariType::IArrayBurasagariType(ArrayBurasagariTypeRef arrayburasagaritype)
:fArrayBurasagariType(arrayburasagaritype)
{
}

IArrayBurasagariType::IArrayBurasagariType(const IArrayBurasagariType& src)
:fArrayBurasagariType(src.fArrayBurasagariType)
{
	sArrayBurasagariType->AddRef(fArrayBurasagariType);
}

IArrayBurasagariType::~IArrayBurasagariType()
{
	sArrayBurasagariType->Release(fArrayBurasagariType);
}

IArrayBurasagariType& IArrayBurasagariType::operator=(const IArrayBurasagariType& rhs)
{
	if (&rhs != this)
	{
		sArrayBurasagariType->Release(fArrayBurasagariType);
		fArrayBurasagariType = rhs.fArrayBurasagariType;
		sArrayBurasagariType->AddRef(fArrayBurasagariType);
	}
	return *this;
}

bool IArrayBurasagariType::operator==(const IArrayBurasagariType& rhs) const
{
	return fArrayBurasagariType == rhs.fArrayBurasagariType;
}

bool IArrayBurasagariType::operator!=(const IArrayBurasagariType& rhs) const
{
	return !(*this == rhs);
}

ArrayBurasagariTypeRef IArrayBurasagariType::GetRef() const
{
	return fArrayBurasagariType;
}

bool IArrayBurasagariType::IsNull() const
{
	return sArrayBurasagariType->IsNull(fArrayBurasagariType);
}

ATETextDOM::Int32 IArrayBurasagariType::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayBurasagariType->GetSize(fArrayBurasagariType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

BurasagariType IArrayBurasagariType::GetFirst( ) const
{
	BurasagariType ret;
	ATEErr error = sArrayBurasagariType->GetFirst(fArrayBurasagariType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

BurasagariType IArrayBurasagariType::GetLast( ) const
{
	BurasagariType ret;
	ATEErr error = sArrayBurasagariType->GetLast(fArrayBurasagariType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

BurasagariType IArrayBurasagariType::Item( ATETextDOM::Int32 index) const
{
	BurasagariType ret;
	ATEErr error = sArrayBurasagariType->Item(fArrayBurasagariType, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayPreferredKinsokuOrder--
//////////////////////////////////////////////

IArrayPreferredKinsokuOrder::IArrayPreferredKinsokuOrder()
:fArrayPreferredKinsokuOrder(0)
{
}

IArrayPreferredKinsokuOrder::IArrayPreferredKinsokuOrder(ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder)
:fArrayPreferredKinsokuOrder(arraypreferredkinsokuorder)
{
}

IArrayPreferredKinsokuOrder::IArrayPreferredKinsokuOrder(const IArrayPreferredKinsokuOrder& src)
:fArrayPreferredKinsokuOrder(src.fArrayPreferredKinsokuOrder)
{
	sArrayPreferredKinsokuOrder->AddRef(fArrayPreferredKinsokuOrder);
}

IArrayPreferredKinsokuOrder::~IArrayPreferredKinsokuOrder()
{
	sArrayPreferredKinsokuOrder->Release(fArrayPreferredKinsokuOrder);
}

IArrayPreferredKinsokuOrder& IArrayPreferredKinsokuOrder::operator=(const IArrayPreferredKinsokuOrder& rhs)
{
	if (&rhs != this)
	{
		sArrayPreferredKinsokuOrder->Release(fArrayPreferredKinsokuOrder);
		fArrayPreferredKinsokuOrder = rhs.fArrayPreferredKinsokuOrder;
		sArrayPreferredKinsokuOrder->AddRef(fArrayPreferredKinsokuOrder);
	}
	return *this;
}

bool IArrayPreferredKinsokuOrder::operator==(const IArrayPreferredKinsokuOrder& rhs) const
{
	return fArrayPreferredKinsokuOrder == rhs.fArrayPreferredKinsokuOrder;
}

bool IArrayPreferredKinsokuOrder::operator!=(const IArrayPreferredKinsokuOrder& rhs) const
{
	return !(*this == rhs);
}

ArrayPreferredKinsokuOrderRef IArrayPreferredKinsokuOrder::GetRef() const
{
	return fArrayPreferredKinsokuOrder;
}

bool IArrayPreferredKinsokuOrder::IsNull() const
{
	return sArrayPreferredKinsokuOrder->IsNull(fArrayPreferredKinsokuOrder);
}

ATETextDOM::Int32 IArrayPreferredKinsokuOrder::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayPreferredKinsokuOrder->GetSize(fArrayPreferredKinsokuOrder, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

PreferredKinsokuOrder IArrayPreferredKinsokuOrder::GetFirst( ) const
{
	PreferredKinsokuOrder ret;
	ATEErr error = sArrayPreferredKinsokuOrder->GetFirst(fArrayPreferredKinsokuOrder, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

PreferredKinsokuOrder IArrayPreferredKinsokuOrder::GetLast( ) const
{
	PreferredKinsokuOrder ret;
	ATEErr error = sArrayPreferredKinsokuOrder->GetLast(fArrayPreferredKinsokuOrder, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

PreferredKinsokuOrder IArrayPreferredKinsokuOrder::Item( ATETextDOM::Int32 index) const
{
	PreferredKinsokuOrder ret;
	ATEErr error = sArrayPreferredKinsokuOrder->Item(fArrayPreferredKinsokuOrder, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayKinsokuRef--
//////////////////////////////////////////////

IArrayKinsokuRef::IArrayKinsokuRef()
:fArrayKinsokuRef(0)
{
}

IArrayKinsokuRef::IArrayKinsokuRef(ArrayKinsokuRefRef arraykinsokuref)
:fArrayKinsokuRef(arraykinsokuref)
{
}

IArrayKinsokuRef::IArrayKinsokuRef(const IArrayKinsokuRef& src)
:fArrayKinsokuRef(src.fArrayKinsokuRef)
{
	sArrayKinsokuRef->AddRef(fArrayKinsokuRef);
}

IArrayKinsokuRef::~IArrayKinsokuRef()
{
	sArrayKinsokuRef->Release(fArrayKinsokuRef);
}

IArrayKinsokuRef& IArrayKinsokuRef::operator=(const IArrayKinsokuRef& rhs)
{
	if (&rhs != this)
	{
		sArrayKinsokuRef->Release(fArrayKinsokuRef);
		fArrayKinsokuRef = rhs.fArrayKinsokuRef;
		sArrayKinsokuRef->AddRef(fArrayKinsokuRef);
	}
	return *this;
}

bool IArrayKinsokuRef::operator==(const IArrayKinsokuRef& rhs) const
{
	return fArrayKinsokuRef == rhs.fArrayKinsokuRef;
}

bool IArrayKinsokuRef::operator!=(const IArrayKinsokuRef& rhs) const
{
	return !(*this == rhs);
}

ArrayKinsokuRefRef IArrayKinsokuRef::GetRef() const
{
	return fArrayKinsokuRef;
}

bool IArrayKinsokuRef::IsNull() const
{
	return sArrayKinsokuRef->IsNull(fArrayKinsokuRef);
}

ATETextDOM::Int32 IArrayKinsokuRef::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayKinsokuRef->GetSize(fArrayKinsokuRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IKinsoku IArrayKinsokuRef::GetFirst( ) const
{
	KinsokuRef ret = 0;
	ATEErr error = sArrayKinsokuRef->GetFirst(fArrayKinsokuRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsoku(ret);
}

IKinsoku IArrayKinsokuRef::GetLast( ) const
{
	KinsokuRef ret = 0;
	ATEErr error = sArrayKinsokuRef->GetLast(fArrayKinsokuRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsoku(ret);
}

IKinsoku IArrayKinsokuRef::Item( ATETextDOM::Int32 index) const
{
	KinsokuRef ret = 0;
	ATEErr error = sArrayKinsokuRef->Item(fArrayKinsokuRef, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsoku(ret);
}

//////////////////////////////////////////////
// --IArrayMojiKumiRef--
//////////////////////////////////////////////

IArrayMojiKumiRef::IArrayMojiKumiRef()
:fArrayMojiKumiRef(0)
{
}

IArrayMojiKumiRef::IArrayMojiKumiRef(ArrayMojiKumiRefRef arraymojikumiref)
:fArrayMojiKumiRef(arraymojikumiref)
{
}

IArrayMojiKumiRef::IArrayMojiKumiRef(const IArrayMojiKumiRef& src)
:fArrayMojiKumiRef(src.fArrayMojiKumiRef)
{
	sArrayMojiKumiRef->AddRef(fArrayMojiKumiRef);
}

IArrayMojiKumiRef::~IArrayMojiKumiRef()
{
	sArrayMojiKumiRef->Release(fArrayMojiKumiRef);
}

IArrayMojiKumiRef& IArrayMojiKumiRef::operator=(const IArrayMojiKumiRef& rhs)
{
	if (&rhs != this)
	{
		sArrayMojiKumiRef->Release(fArrayMojiKumiRef);
		fArrayMojiKumiRef = rhs.fArrayMojiKumiRef;
		sArrayMojiKumiRef->AddRef(fArrayMojiKumiRef);
	}
	return *this;
}

bool IArrayMojiKumiRef::operator==(const IArrayMojiKumiRef& rhs) const
{
	return fArrayMojiKumiRef == rhs.fArrayMojiKumiRef;
}

bool IArrayMojiKumiRef::operator!=(const IArrayMojiKumiRef& rhs) const
{
	return !(*this == rhs);
}

ArrayMojiKumiRefRef IArrayMojiKumiRef::GetRef() const
{
	return fArrayMojiKumiRef;
}

bool IArrayMojiKumiRef::IsNull() const
{
	return sArrayMojiKumiRef->IsNull(fArrayMojiKumiRef);
}

ATETextDOM::Int32 IArrayMojiKumiRef::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayMojiKumiRef->GetSize(fArrayMojiKumiRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IMojiKumi IArrayMojiKumiRef::GetFirst( ) const
{
	MojiKumiRef ret = 0;
	ATEErr error = sArrayMojiKumiRef->GetFirst(fArrayMojiKumiRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

IMojiKumi IArrayMojiKumiRef::GetLast( ) const
{
	MojiKumiRef ret = 0;
	ATEErr error = sArrayMojiKumiRef->GetLast(fArrayMojiKumiRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

IMojiKumi IArrayMojiKumiRef::Item( ATETextDOM::Int32 index) const
{
	MojiKumiRef ret = 0;
	ATEErr error = sArrayMojiKumiRef->Item(fArrayMojiKumiRef, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumi(ret);
}

//////////////////////////////////////////////
// --IArrayMojiKumiSetRef--
//////////////////////////////////////////////

IArrayMojiKumiSetRef::IArrayMojiKumiSetRef()
:fArrayMojiKumiSetRef(0)
{
}

IArrayMojiKumiSetRef::IArrayMojiKumiSetRef(ArrayMojiKumiSetRefRef arraymojikumisetref)
:fArrayMojiKumiSetRef(arraymojikumisetref)
{
}

IArrayMojiKumiSetRef::IArrayMojiKumiSetRef(const IArrayMojiKumiSetRef& src)
:fArrayMojiKumiSetRef(src.fArrayMojiKumiSetRef)
{
	sArrayMojiKumiSetRef->AddRef(fArrayMojiKumiSetRef);
}

IArrayMojiKumiSetRef::~IArrayMojiKumiSetRef()
{
	sArrayMojiKumiSetRef->Release(fArrayMojiKumiSetRef);
}

IArrayMojiKumiSetRef& IArrayMojiKumiSetRef::operator=(const IArrayMojiKumiSetRef& rhs)
{
	if (&rhs != this)
	{
		sArrayMojiKumiSetRef->Release(fArrayMojiKumiSetRef);
		fArrayMojiKumiSetRef = rhs.fArrayMojiKumiSetRef;
		sArrayMojiKumiSetRef->AddRef(fArrayMojiKumiSetRef);
	}
	return *this;
}

bool IArrayMojiKumiSetRef::operator==(const IArrayMojiKumiSetRef& rhs) const
{
	return fArrayMojiKumiSetRef == rhs.fArrayMojiKumiSetRef;
}

bool IArrayMojiKumiSetRef::operator!=(const IArrayMojiKumiSetRef& rhs) const
{
	return !(*this == rhs);
}

ArrayMojiKumiSetRefRef IArrayMojiKumiSetRef::GetRef() const
{
	return fArrayMojiKumiSetRef;
}

bool IArrayMojiKumiSetRef::IsNull() const
{
	return sArrayMojiKumiSetRef->IsNull(fArrayMojiKumiSetRef);
}

ATETextDOM::Int32 IArrayMojiKumiSetRef::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayMojiKumiSetRef->GetSize(fArrayMojiKumiSetRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IMojiKumiSet IArrayMojiKumiSetRef::GetFirst( ) const
{
	MojiKumiSetRef ret = 0;
	ATEErr error = sArrayMojiKumiSetRef->GetFirst(fArrayMojiKumiSetRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumiSet(ret);
}

IMojiKumiSet IArrayMojiKumiSetRef::GetLast( ) const
{
	MojiKumiSetRef ret = 0;
	ATEErr error = sArrayMojiKumiSetRef->GetLast(fArrayMojiKumiSetRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumiSet(ret);
}

IMojiKumiSet IArrayMojiKumiSetRef::Item( ATETextDOM::Int32 index) const
{
	MojiKumiSetRef ret = 0;
	ATEErr error = sArrayMojiKumiSetRef->Item(fArrayMojiKumiSetRef, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return IMojiKumiSet(ret);
}

//////////////////////////////////////////////
// --IArrayTabStopsRef--
//////////////////////////////////////////////

IArrayTabStopsRef::IArrayTabStopsRef()
:fArrayTabStopsRef(0)
{
}

IArrayTabStopsRef::IArrayTabStopsRef(ArrayTabStopsRefRef arraytabstopsref)
:fArrayTabStopsRef(arraytabstopsref)
{
}

IArrayTabStopsRef::IArrayTabStopsRef(const IArrayTabStopsRef& src)
:fArrayTabStopsRef(src.fArrayTabStopsRef)
{
	sArrayTabStopsRef->AddRef(fArrayTabStopsRef);
}

IArrayTabStopsRef::~IArrayTabStopsRef()
{
	sArrayTabStopsRef->Release(fArrayTabStopsRef);
}

IArrayTabStopsRef& IArrayTabStopsRef::operator=(const IArrayTabStopsRef& rhs)
{
	if (&rhs != this)
	{
		sArrayTabStopsRef->Release(fArrayTabStopsRef);
		fArrayTabStopsRef = rhs.fArrayTabStopsRef;
		sArrayTabStopsRef->AddRef(fArrayTabStopsRef);
	}
	return *this;
}

bool IArrayTabStopsRef::operator==(const IArrayTabStopsRef& rhs) const
{
	return fArrayTabStopsRef == rhs.fArrayTabStopsRef;
}

bool IArrayTabStopsRef::operator!=(const IArrayTabStopsRef& rhs) const
{
	return !(*this == rhs);
}

ArrayTabStopsRefRef IArrayTabStopsRef::GetRef() const
{
	return fArrayTabStopsRef;
}

bool IArrayTabStopsRef::IsNull() const
{
	return sArrayTabStopsRef->IsNull(fArrayTabStopsRef);
}

ATETextDOM::Int32 IArrayTabStopsRef::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayTabStopsRef->GetSize(fArrayTabStopsRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ITabStops IArrayTabStopsRef::GetFirst( ) const
{
	TabStopsRef ret = 0;
	ATEErr error = sArrayTabStopsRef->GetFirst(fArrayTabStopsRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITabStops(ret);
}

ITabStops IArrayTabStopsRef::GetLast( ) const
{
	TabStopsRef ret = 0;
	ATEErr error = sArrayTabStopsRef->GetLast(fArrayTabStopsRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITabStops(ret);
}

ITabStops IArrayTabStopsRef::Item( ATETextDOM::Int32 index) const
{
	TabStopsRef ret = 0;
	ATEErr error = sArrayTabStopsRef->Item(fArrayTabStopsRef, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITabStops(ret);
}

//////////////////////////////////////////////
// --IArrayLeadingType--
//////////////////////////////////////////////

IArrayLeadingType::IArrayLeadingType()
:fArrayLeadingType(0)
{
}

IArrayLeadingType::IArrayLeadingType(ArrayLeadingTypeRef arrayleadingtype)
:fArrayLeadingType(arrayleadingtype)
{
}

IArrayLeadingType::IArrayLeadingType(const IArrayLeadingType& src)
:fArrayLeadingType(src.fArrayLeadingType)
{
	sArrayLeadingType->AddRef(fArrayLeadingType);
}

IArrayLeadingType::~IArrayLeadingType()
{
	sArrayLeadingType->Release(fArrayLeadingType);
}

IArrayLeadingType& IArrayLeadingType::operator=(const IArrayLeadingType& rhs)
{
	if (&rhs != this)
	{
		sArrayLeadingType->Release(fArrayLeadingType);
		fArrayLeadingType = rhs.fArrayLeadingType;
		sArrayLeadingType->AddRef(fArrayLeadingType);
	}
	return *this;
}

bool IArrayLeadingType::operator==(const IArrayLeadingType& rhs) const
{
	return fArrayLeadingType == rhs.fArrayLeadingType;
}

bool IArrayLeadingType::operator!=(const IArrayLeadingType& rhs) const
{
	return !(*this == rhs);
}

ArrayLeadingTypeRef IArrayLeadingType::GetRef() const
{
	return fArrayLeadingType;
}

bool IArrayLeadingType::IsNull() const
{
	return sArrayLeadingType->IsNull(fArrayLeadingType);
}

ATETextDOM::Int32 IArrayLeadingType::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayLeadingType->GetSize(fArrayLeadingType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LeadingType IArrayLeadingType::GetFirst( ) const
{
	LeadingType ret;
	ATEErr error = sArrayLeadingType->GetFirst(fArrayLeadingType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LeadingType IArrayLeadingType::GetLast( ) const
{
	LeadingType ret;
	ATEErr error = sArrayLeadingType->GetLast(fArrayLeadingType, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

LeadingType IArrayLeadingType::Item( ATETextDOM::Int32 index) const
{
	LeadingType ret;
	ATEErr error = sArrayLeadingType->Item(fArrayLeadingType, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayFontRef--
//////////////////////////////////////////////

IArrayFontRef::IArrayFontRef()
:fArrayFontRef(0)
{
}

IArrayFontRef::IArrayFontRef(ArrayFontRefRef arrayfontref)
:fArrayFontRef(arrayfontref)
{
}

IArrayFontRef::IArrayFontRef(const IArrayFontRef& src)
:fArrayFontRef(src.fArrayFontRef)
{
	sArrayFontRef->AddRef(fArrayFontRef);
}

IArrayFontRef::~IArrayFontRef()
{
	sArrayFontRef->Release(fArrayFontRef);
}

IArrayFontRef& IArrayFontRef::operator=(const IArrayFontRef& rhs)
{
	if (&rhs != this)
	{
		sArrayFontRef->Release(fArrayFontRef);
		fArrayFontRef = rhs.fArrayFontRef;
		sArrayFontRef->AddRef(fArrayFontRef);
	}
	return *this;
}

bool IArrayFontRef::operator==(const IArrayFontRef& rhs) const
{
	return fArrayFontRef == rhs.fArrayFontRef;
}

bool IArrayFontRef::operator!=(const IArrayFontRef& rhs) const
{
	return !(*this == rhs);
}

ArrayFontRefRef IArrayFontRef::GetRef() const
{
	return fArrayFontRef;
}

bool IArrayFontRef::IsNull() const
{
	return sArrayFontRef->IsNull(fArrayFontRef);
}

ATETextDOM::Int32 IArrayFontRef::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayFontRef->GetSize(fArrayFontRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IFont IArrayFontRef::GetFirst( ) const
{
	FontRef ret = 0;
	ATEErr error = sArrayFontRef->GetFirst(fArrayFontRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IFont(ret);
}

IFont IArrayFontRef::GetLast( ) const
{
	FontRef ret = 0;
	ATEErr error = sArrayFontRef->GetLast(fArrayFontRef, &ret);
	if(error) Throw_ATE_Exception(error);
	return IFont(ret);
}

IFont IArrayFontRef::Item( ATETextDOM::Int32 index) const
{
	FontRef ret = 0;
	ATEErr error = sArrayFontRef->Item(fArrayFontRef, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return IFont(ret);
}

//////////////////////////////////////////////
// --IArrayGlyphID--
//////////////////////////////////////////////

IArrayGlyphID::IArrayGlyphID()
:fArrayGlyphID(0)
{
}

IArrayGlyphID::IArrayGlyphID(ArrayGlyphIDRef arrayglyphid)
:fArrayGlyphID(arrayglyphid)
{
}

IArrayGlyphID::IArrayGlyphID(const IArrayGlyphID& src)
:fArrayGlyphID(src.fArrayGlyphID)
{
	sArrayGlyphID->AddRef(fArrayGlyphID);
}

IArrayGlyphID::~IArrayGlyphID()
{
	sArrayGlyphID->Release(fArrayGlyphID);
}

IArrayGlyphID& IArrayGlyphID::operator=(const IArrayGlyphID& rhs)
{
	if (&rhs != this)
	{
		sArrayGlyphID->Release(fArrayGlyphID);
		fArrayGlyphID = rhs.fArrayGlyphID;
		sArrayGlyphID->AddRef(fArrayGlyphID);
	}
	return *this;
}

bool IArrayGlyphID::operator==(const IArrayGlyphID& rhs) const
{
	return fArrayGlyphID == rhs.fArrayGlyphID;
}

bool IArrayGlyphID::operator!=(const IArrayGlyphID& rhs) const
{
	return !(*this == rhs);
}

ArrayGlyphIDRef IArrayGlyphID::GetRef() const
{
	return fArrayGlyphID;
}

bool IArrayGlyphID::IsNull() const
{
	return sArrayGlyphID->IsNull(fArrayGlyphID);
}

ATETextDOM::Int32 IArrayGlyphID::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayGlyphID->GetSize(fArrayGlyphID, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATEGlyphID IArrayGlyphID::GetFirst( ) const
{
	ATEGlyphID ret;
	ATEErr error = sArrayGlyphID->GetFirst(fArrayGlyphID, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATEGlyphID IArrayGlyphID::GetLast( ) const
{
	ATEGlyphID ret;
	ATEErr error = sArrayGlyphID->GetLast(fArrayGlyphID, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATEGlyphID IArrayGlyphID::Item( ATETextDOM::Int32 index) const
{
	ATEGlyphID ret;
	ATEErr error = sArrayGlyphID->Item(fArrayGlyphID, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayRealPoint--
//////////////////////////////////////////////

IArrayRealPoint::IArrayRealPoint()
:fArrayRealPoint(0)
{
}

IArrayRealPoint::IArrayRealPoint(ArrayRealPointRef arrayrealpoint)
:fArrayRealPoint(arrayrealpoint)
{
}

IArrayRealPoint::IArrayRealPoint(const IArrayRealPoint& src)
:fArrayRealPoint(src.fArrayRealPoint)
{
	sArrayRealPoint->AddRef(fArrayRealPoint);
}

IArrayRealPoint::~IArrayRealPoint()
{
	sArrayRealPoint->Release(fArrayRealPoint);
}

IArrayRealPoint& IArrayRealPoint::operator=(const IArrayRealPoint& rhs)
{
	if (&rhs != this)
	{
		sArrayRealPoint->Release(fArrayRealPoint);
		fArrayRealPoint = rhs.fArrayRealPoint;
		sArrayRealPoint->AddRef(fArrayRealPoint);
	}
	return *this;
}

bool IArrayRealPoint::operator==(const IArrayRealPoint& rhs) const
{
	return fArrayRealPoint == rhs.fArrayRealPoint;
}

bool IArrayRealPoint::operator!=(const IArrayRealPoint& rhs) const
{
	return !(*this == rhs);
}

ArrayRealPointRef IArrayRealPoint::GetRef() const
{
	return fArrayRealPoint;
}

bool IArrayRealPoint::IsNull() const
{
	return sArrayRealPoint->IsNull(fArrayRealPoint);
}

ATETextDOM::Int32 IArrayRealPoint::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayRealPoint->GetSize(fArrayRealPoint, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::RealPoint IArrayRealPoint::GetFirst( ) const
{
	ATETextDOM::RealPoint ret;
	ATETextDOM::FloatPoint tempRet;
	ATEErr error = sArrayRealPoint->GetFirst(fArrayRealPoint, &tempRet);
	if(error) Throw_ATE_Exception(error);
	ATEFloatPointToATERealPoint(&tempRet,&ret);
	return ret;
}

ATETextDOM::RealPoint IArrayRealPoint::GetLast( ) const
{
	ATETextDOM::RealPoint ret;
	ATETextDOM::FloatPoint tempRet;
	ATEErr error = sArrayRealPoint->GetLast(fArrayRealPoint, &tempRet);
	if(error) Throw_ATE_Exception(error);
	ATEFloatPointToATERealPoint(&tempRet,&ret);
	return ret;
}

ATETextDOM::RealPoint IArrayRealPoint::Item( ATETextDOM::Int32 index) const
{
	ATETextDOM::RealPoint ret;
	ATETextDOM::FloatPoint tempRet;
	ATEErr error = sArrayRealPoint->Item(fArrayRealPoint, index, &tempRet);
	if(error) Throw_ATE_Exception(error);
	ATEFloatPointToATERealPoint(&tempRet,&ret);
	return ret;
}

//////////////////////////////////////////////
// --IArrayRealMatrix--
//////////////////////////////////////////////

IArrayRealMatrix::IArrayRealMatrix()
:fArrayRealMatrix(0)
{
}

IArrayRealMatrix::IArrayRealMatrix(ArrayRealMatrixRef arrayrealmatrix)
:fArrayRealMatrix(arrayrealmatrix)
{
}

IArrayRealMatrix::IArrayRealMatrix(const IArrayRealMatrix& src)
:fArrayRealMatrix(src.fArrayRealMatrix)
{
	sArrayRealMatrix->AddRef(fArrayRealMatrix);
}

IArrayRealMatrix::~IArrayRealMatrix()
{
	sArrayRealMatrix->Release(fArrayRealMatrix);
}

IArrayRealMatrix& IArrayRealMatrix::operator=(const IArrayRealMatrix& rhs)
{
	if (&rhs != this)
	{
		sArrayRealMatrix->Release(fArrayRealMatrix);
		fArrayRealMatrix = rhs.fArrayRealMatrix;
		sArrayRealMatrix->AddRef(fArrayRealMatrix);
	}
	return *this;
}

bool IArrayRealMatrix::operator==(const IArrayRealMatrix& rhs) const
{
	return fArrayRealMatrix == rhs.fArrayRealMatrix;
}

bool IArrayRealMatrix::operator!=(const IArrayRealMatrix& rhs) const
{
	return !(*this == rhs);
}

ArrayRealMatrixRef IArrayRealMatrix::GetRef() const
{
	return fArrayRealMatrix;
}

bool IArrayRealMatrix::IsNull() const
{
	return sArrayRealMatrix->IsNull(fArrayRealMatrix);
}

ATETextDOM::Int32 IArrayRealMatrix::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayRealMatrix->GetSize(fArrayRealMatrix, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::RealMatrix IArrayRealMatrix::GetFirst( ) const
{
	ATETextDOM::RealMatrix ret;
	ATETextDOM::FloatMatrix tempRet;
	ATEErr error = sArrayRealMatrix->GetFirst(fArrayRealMatrix, &tempRet);
	ATEFloatMatrixToATERealMatrix(&tempRet,&ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::RealMatrix IArrayRealMatrix::GetLast( ) const
{
	ATETextDOM::RealMatrix ret;
	ATETextDOM::FloatMatrix tempRet;
	ATEErr error = sArrayRealMatrix->GetLast(fArrayRealMatrix, &tempRet);
	ATEFloatMatrixToATERealMatrix(&tempRet,&ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::RealMatrix IArrayRealMatrix::Item( ATETextDOM::Int32 index) const
{
	ATETextDOM::RealMatrix ret;
	ATETextDOM::FloatMatrix tempRet;
	ATEErr error = sArrayRealMatrix->Item(fArrayRealMatrix, index, &tempRet);
	ATEFloatMatrixToATERealMatrix(&tempRet,&ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

#if SLO_COMPLEXSCRIPT
//////////////////////////////////////////////
// --IArrayParagraphDirection--
//////////////////////////////////////////////

IArrayParagraphDirection::IArrayParagraphDirection()
:fArrayParagraphDirection(0)
{
}

IArrayParagraphDirection::IArrayParagraphDirection(ArrayParagraphDirectionRef arrayparagraphdirection)
:fArrayParagraphDirection(arrayparagraphdirection)
{
}

IArrayParagraphDirection::IArrayParagraphDirection(const IArrayParagraphDirection& src)
:fArrayParagraphDirection(src.fArrayParagraphDirection)
{
	sArrayParagraphDirection->AddRef(fArrayParagraphDirection);
}

IArrayParagraphDirection::~IArrayParagraphDirection()
{
	sArrayParagraphDirection->Release(fArrayParagraphDirection);
}

IArrayParagraphDirection& IArrayParagraphDirection::operator=(const IArrayParagraphDirection& rhs)
{
	if (&rhs != this)
	{
		sArrayParagraphDirection->Release(fArrayParagraphDirection);
		fArrayParagraphDirection = rhs.fArrayParagraphDirection;
		sArrayParagraphDirection->AddRef(fArrayParagraphDirection);
	}
	return *this;
}

bool IArrayParagraphDirection::operator==(const IArrayParagraphDirection& rhs) const
{
	return fArrayParagraphDirection == rhs.fArrayParagraphDirection;
}

bool IArrayParagraphDirection::operator!=(const IArrayParagraphDirection& rhs) const
{
	return !(*this == rhs);
}

ArrayParagraphDirectionRef IArrayParagraphDirection::GetRef() const
{
	return fArrayParagraphDirection;
}

bool IArrayParagraphDirection::IsNull() const
{
	return sArrayParagraphDirection->IsNull(fArrayParagraphDirection);
}

ATETextDOM::Int32 IArrayParagraphDirection::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayParagraphDirection->GetSize(fArrayParagraphDirection, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ParagraphDirection IArrayParagraphDirection::GetFirst( ) const
{
	ParagraphDirection ret;
	ATEErr error = sArrayParagraphDirection->GetFirst(fArrayParagraphDirection, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ParagraphDirection IArrayParagraphDirection::GetLast( ) const
{
	ParagraphDirection ret;
	ATEErr error = sArrayParagraphDirection->GetLast(fArrayParagraphDirection, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ParagraphDirection IArrayParagraphDirection::Item( ATETextDOM::Int32 index) const
{
	ParagraphDirection ret;
	ATEErr error = sArrayParagraphDirection->Item(fArrayParagraphDirection, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayJustificationMethod--
//////////////////////////////////////////////

IArrayJustificationMethod::IArrayJustificationMethod()
:fArrayJustificationMethod(0)
{
}

IArrayJustificationMethod::IArrayJustificationMethod(ArrayJustificationMethodRef arrayjustificationmethod)
:fArrayJustificationMethod(arrayjustificationmethod)
{
}

IArrayJustificationMethod::IArrayJustificationMethod(const IArrayJustificationMethod& src)
:fArrayJustificationMethod(src.fArrayJustificationMethod)
{
	sArrayJustificationMethod->AddRef(fArrayJustificationMethod);
}

IArrayJustificationMethod::~IArrayJustificationMethod()
{
	sArrayJustificationMethod->Release(fArrayJustificationMethod);
}

IArrayJustificationMethod& IArrayJustificationMethod::operator=(const IArrayJustificationMethod& rhs)
{
	if (&rhs != this)
	{
		sArrayJustificationMethod->Release(fArrayJustificationMethod);
		fArrayJustificationMethod = rhs.fArrayJustificationMethod;
		sArrayJustificationMethod->AddRef(fArrayJustificationMethod);
	}
	return *this;
}

bool IArrayJustificationMethod::operator==(const IArrayJustificationMethod& rhs) const
{
	return fArrayJustificationMethod == rhs.fArrayJustificationMethod;
}

bool IArrayJustificationMethod::operator!=(const IArrayJustificationMethod& rhs) const
{
	return !(*this == rhs);
}

ArrayJustificationMethodRef IArrayJustificationMethod::GetRef() const
{
	return fArrayJustificationMethod;
}

bool IArrayJustificationMethod::IsNull() const
{
	return sArrayJustificationMethod->IsNull(fArrayJustificationMethod);
}

ATETextDOM::Int32 IArrayJustificationMethod::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayJustificationMethod->GetSize(fArrayJustificationMethod, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

JustificationMethod IArrayJustificationMethod::GetFirst( ) const
{
	JustificationMethod ret;
	ATEErr error = sArrayJustificationMethod->GetFirst(fArrayJustificationMethod, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

JustificationMethod IArrayJustificationMethod::GetLast( ) const
{
	JustificationMethod ret;
	ATEErr error = sArrayJustificationMethod->GetLast(fArrayJustificationMethod, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

JustificationMethod IArrayJustificationMethod::Item( ATETextDOM::Int32 index) const
{
	JustificationMethod ret;
	ATEErr error = sArrayJustificationMethod->Item(fArrayJustificationMethod, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}


//////////////////////////////////////////////
// --IArrayKashidaWidth--
//////////////////////////////////////////////

IArrayKashidaWidth::IArrayKashidaWidth()
	:fArrayKashidaWidth(0)
{
}

IArrayKashidaWidth::IArrayKashidaWidth(ArrayKashidaWidthRef arraykashidawidth)
	:fArrayKashidaWidth(arraykashidawidth)
{
}

IArrayKashidaWidth::IArrayKashidaWidth(const IArrayKashidaWidth& src)
	:fArrayKashidaWidth(src.fArrayKashidaWidth)
{
	sArrayKashidaWidth->AddRef(fArrayKashidaWidth);
}

IArrayKashidaWidth::~IArrayKashidaWidth()
{
	sArrayKashidaWidth->Release(fArrayKashidaWidth);
}

IArrayKashidaWidth& IArrayKashidaWidth::operator=(const IArrayKashidaWidth& rhs)
{
	if (&rhs != this)
	{
		sArrayKashidaWidth->Release(fArrayKashidaWidth);
		fArrayKashidaWidth = rhs.fArrayKashidaWidth;
		sArrayKashidaWidth->AddRef(fArrayKashidaWidth);
	}
	return *this;
}

bool IArrayKashidaWidth::operator==(const IArrayKashidaWidth& rhs) const
{
	return fArrayKashidaWidth == rhs.fArrayKashidaWidth;
}

bool IArrayKashidaWidth::operator!=(const IArrayKashidaWidth& rhs) const
{
	return !(*this == rhs);
}

ArrayKashidaWidthRef IArrayKashidaWidth::GetRef() const
{
	return fArrayKashidaWidth;
}

bool IArrayKashidaWidth::IsNull() const
{
	return sArrayKashidaWidth->IsNull(fArrayKashidaWidth);
}

ATETextDOM::Int32 IArrayKashidaWidth::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayKashidaWidth->GetSize(fArrayKashidaWidth, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

KashidaWidth IArrayKashidaWidth::GetFirst( ) const
{
	KashidaWidth ret;
	ATEErr error = sArrayKashidaWidth->GetFirst(fArrayKashidaWidth, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

KashidaWidth IArrayKashidaWidth::GetLast( ) const
{
	KashidaWidth ret;
	ATEErr error = sArrayKashidaWidth->GetLast(fArrayKashidaWidth, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

KashidaWidth IArrayKashidaWidth::Item( ATETextDOM::Int32 index) const
{
	KashidaWidth ret;
	ATEErr error = sArrayKashidaWidth->Item(fArrayKashidaWidth, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayKashidas--
//////////////////////////////////////////////

IArrayKashidas::IArrayKashidas()
:fArrayKashidas(0)
{
}

IArrayKashidas::IArrayKashidas(ArrayKashidasRef arraykashidas)
:fArrayKashidas(arraykashidas)
{
}

IArrayKashidas::IArrayKashidas(const IArrayKashidas& src)
:fArrayKashidas(src.fArrayKashidas)
{
	sArrayKashidas->AddRef(fArrayKashidas);
}

IArrayKashidas::~IArrayKashidas()
{
	sArrayKashidas->Release(fArrayKashidas);
}

IArrayKashidas& IArrayKashidas::operator=(const IArrayKashidas& rhs)
{
	if (&rhs != this)
	{
		sArrayKashidas->Release(fArrayKashidas);
		fArrayKashidas = rhs.fArrayKashidas;
		sArrayKashidas->AddRef(fArrayKashidas);
	}
	return *this;
}

bool IArrayKashidas::operator==(const IArrayKashidas& rhs) const
{
	return fArrayKashidas == rhs.fArrayKashidas;
}

bool IArrayKashidas::operator!=(const IArrayKashidas& rhs) const
{
	return !(*this == rhs);
}

ArrayKashidasRef IArrayKashidas::GetRef() const
{
	return fArrayKashidas;
}

bool IArrayKashidas::IsNull() const
{
	return sArrayKashidas->IsNull(fArrayKashidas);
}

ATETextDOM::Int32 IArrayKashidas::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayKashidas->GetSize(fArrayKashidas, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

Kashidas IArrayKashidas::GetFirst( ) const
{
	Kashidas ret;
	ATEErr error = sArrayKashidas->GetFirst(fArrayKashidas, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

Kashidas IArrayKashidas::GetLast( ) const
{
	Kashidas ret;
	ATEErr error = sArrayKashidas->GetLast(fArrayKashidas, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

Kashidas IArrayKashidas::Item( ATETextDOM::Int32 index) const
{
	Kashidas ret;
	ATEErr error = sArrayKashidas->Item(fArrayKashidas, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayDirOverride--
//////////////////////////////////////////////

IArrayDirOverride::IArrayDirOverride()
:fArrayDirOverride(0)
{
}

IArrayDirOverride::IArrayDirOverride(ArrayDirOverrideRef arraydiroverride)
:fArrayDirOverride(arraydiroverride)
{
}

IArrayDirOverride::IArrayDirOverride(const IArrayDirOverride& src)
:fArrayDirOverride(src.fArrayDirOverride)
{
	sArrayDirOverride->AddRef(fArrayDirOverride);
}

IArrayDirOverride::~IArrayDirOverride()
{
	sArrayDirOverride->Release(fArrayDirOverride);
}

IArrayDirOverride& IArrayDirOverride::operator=(const IArrayDirOverride& rhs)
{
	if (&rhs != this)
	{
		sArrayDirOverride->Release(fArrayDirOverride);
		fArrayDirOverride = rhs.fArrayDirOverride;
		sArrayDirOverride->AddRef(fArrayDirOverride);
	}
	return *this;
}

bool IArrayDirOverride::operator==(const IArrayDirOverride& rhs) const
{
	return fArrayDirOverride == rhs.fArrayDirOverride;
}

bool IArrayDirOverride::operator!=(const IArrayDirOverride& rhs) const
{
	return !(*this == rhs);
}

ArrayDirOverrideRef IArrayDirOverride::GetRef() const
{
	return fArrayDirOverride;
}

bool IArrayDirOverride::IsNull() const
{
	return sArrayDirOverride->IsNull(fArrayDirOverride);
}

ATETextDOM::Int32 IArrayDirOverride::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayDirOverride->GetSize(fArrayDirOverride, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DirOverride IArrayDirOverride::GetFirst( ) const
{
	DirOverride ret;
	ATEErr error = sArrayDirOverride->GetFirst(fArrayDirOverride, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DirOverride IArrayDirOverride::GetLast( ) const
{
	DirOverride ret;
	ATEErr error = sArrayDirOverride->GetLast(fArrayDirOverride, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DirOverride IArrayDirOverride::Item( ATETextDOM::Int32 index) const
{
	DirOverride ret;
	ATEErr error = sArrayDirOverride->Item(fArrayDirOverride, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayDigitSet--
//////////////////////////////////////////////

IArrayDigitSet::IArrayDigitSet()
:fArrayDigitSet(0)
{
}

IArrayDigitSet::IArrayDigitSet(ArrayDigitSetRef arraydigitset)
:fArrayDigitSet(arraydigitset)
{
}

IArrayDigitSet::IArrayDigitSet(const IArrayDigitSet& src)
:fArrayDigitSet(src.fArrayDigitSet)
{
	sArrayDigitSet->AddRef(fArrayDigitSet);
}

IArrayDigitSet::~IArrayDigitSet()
{
	sArrayDigitSet->Release(fArrayDigitSet);
}

IArrayDigitSet& IArrayDigitSet::operator=(const IArrayDigitSet& rhs)
{
	if (&rhs != this)
	{
		sArrayDigitSet->Release(fArrayDigitSet);
		fArrayDigitSet = rhs.fArrayDigitSet;
		sArrayDigitSet->AddRef(fArrayDigitSet);
	}
	return *this;
}

bool IArrayDigitSet::operator==(const IArrayDigitSet& rhs) const
{
	return fArrayDigitSet == rhs.fArrayDigitSet;
}

bool IArrayDigitSet::operator!=(const IArrayDigitSet& rhs) const
{
	return !(*this == rhs);
}

ArrayDigitSetRef IArrayDigitSet::GetRef() const
{
	return fArrayDigitSet;
}

bool IArrayDigitSet::IsNull() const
{
	return sArrayDigitSet->IsNull(fArrayDigitSet);
}

ATETextDOM::Int32 IArrayDigitSet::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayDigitSet->GetSize(fArrayDigitSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DigitSet IArrayDigitSet::GetFirst( ) const
{
	DigitSet ret;
	ATEErr error = sArrayDigitSet->GetFirst(fArrayDigitSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DigitSet IArrayDigitSet::GetLast( ) const
{
	DigitSet ret;
	ATEErr error = sArrayDigitSet->GetLast(fArrayDigitSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DigitSet IArrayDigitSet::Item( ATETextDOM::Int32 index) const
{
	DigitSet ret;
	ATEErr error = sArrayDigitSet->Item(fArrayDigitSet, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IArrayDiacVPos--
//////////////////////////////////////////////

IArrayDiacVPos::IArrayDiacVPos()
:fArrayDiacVPos(0)
{
}

IArrayDiacVPos::IArrayDiacVPos(ArrayDiacVPosRef arraydiacvpos)
:fArrayDiacVPos(arraydiacvpos)
{
}

IArrayDiacVPos::IArrayDiacVPos(const IArrayDiacVPos& src)
:fArrayDiacVPos(src.fArrayDiacVPos)
{
	sArrayDiacVPos->AddRef(fArrayDiacVPos);
}

IArrayDiacVPos::~IArrayDiacVPos()
{
	sArrayDiacVPos->Release(fArrayDiacVPos);
}

IArrayDiacVPos& IArrayDiacVPos::operator=(const IArrayDiacVPos& rhs)
{
	if (&rhs != this)
	{
		sArrayDiacVPos->Release(fArrayDiacVPos);
		fArrayDiacVPos = rhs.fArrayDiacVPos;
		sArrayDiacVPos->AddRef(fArrayDiacVPos);
	}
	return *this;
}

bool IArrayDiacVPos::operator==(const IArrayDiacVPos& rhs) const
{
	return fArrayDiacVPos == rhs.fArrayDiacVPos;
}

bool IArrayDiacVPos::operator!=(const IArrayDiacVPos& rhs) const
{
	return !(*this == rhs);
}

ArrayDiacVPosRef IArrayDiacVPos::GetRef() const
{
	return fArrayDiacVPos;
}

bool IArrayDiacVPos::IsNull() const
{
	return sArrayDiacVPos->IsNull(fArrayDiacVPos);
}

ATETextDOM::Int32 IArrayDiacVPos::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayDiacVPos->GetSize(fArrayDiacVPos, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DiacVPos IArrayDiacVPos::GetFirst( ) const
{
	DiacVPos ret;
	ATEErr error = sArrayDiacVPos->GetFirst(fArrayDiacVPos, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DiacVPos IArrayDiacVPos::GetLast( ) const
{
	DiacVPos ret;
	ATEErr error = sArrayDiacVPos->GetLast(fArrayDiacVPos, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

DiacVPos IArrayDiacVPos::Item( ATETextDOM::Int32 index) const
{
	DiacVPos ret;
	ATEErr error = sArrayDiacVPos->Item(fArrayDiacVPos, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}
#endif

//////////////////////////////////////////////
// --ICharFeatures--
//////////////////////////////////////////////

ICharFeatures::ICharFeatures()
:fCharFeatures(0)
{
	ATEErr error = sCharFeatures->Initialize(&fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

ICharFeatures::ICharFeatures(CharFeaturesRef charfeatures)
:fCharFeatures(charfeatures)
{
}

ICharFeatures::ICharFeatures(const ICharFeatures& src)
:fCharFeatures(src.fCharFeatures)
{
	sCharFeatures->AddRef(fCharFeatures);
}

ICharFeatures::~ICharFeatures()
{
	sCharFeatures->Release(fCharFeatures);
}

ICharFeatures& ICharFeatures::operator=(const ICharFeatures& rhs)
{
	if (&rhs != this)
	{
		sCharFeatures->Release(fCharFeatures);
		fCharFeatures = rhs.fCharFeatures;
		sCharFeatures->AddRef(fCharFeatures);
	}
	return *this;
}

bool ICharFeatures::operator==(const ICharFeatures& rhs) const
{
	return fCharFeatures == rhs.fCharFeatures;
}

bool ICharFeatures::operator!=(const ICharFeatures& rhs) const
{
	return !(*this == rhs);
}

CharFeaturesRef ICharFeatures::GetRef() const
{
	return fCharFeatures;
}

bool ICharFeatures::IsNull() const
{
	return sCharFeatures->IsNull(fCharFeatures);
}

ICharFeatures ICharFeatures::Clone( ) const
{
	CharFeaturesRef ret = 0;
	ATEErr error = sCharFeatures->Clone(fCharFeatures, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

IFont ICharFeatures::GetFont( bool* isAssigned) const
{
	FontRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFont(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return IFont(ret);
}

ATETextDOM::Real ICharFeatures::GetFontSize( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATEBool8 isAssignedRet;
	ATETextDOM::Float tempRet;
	ATEErr error = sCharFeatures->GetFontSize(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetHorizontalScale( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATEBool8 isAssignedRet;
	ATETextDOM::Float tempRet;
	ATEErr error = sCharFeatures->GetHorizontalScale(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetVerticalScale( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATEBool8 isAssignedRet;
	ATETextDOM::Float tempRet;
	ATEErr error = sCharFeatures->GetVerticalScale(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool ICharFeatures::GetAutoLeading( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetAutoLeading(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetLeading( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLeading(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetTracking( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetTracking(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetBaselineShift( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetBaselineShift(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetCharacterRotation( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetCharacterRotation(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

AutoKernType ICharFeatures::GetAutoKernType( bool* isAssigned) const
{
	AutoKernType ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetAutoKernType(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

FontCapsOption ICharFeatures::GetFontCapsOption( bool* isAssigned) const
{
	FontCapsOption ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFontCapsOption(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

FontBaselineOption ICharFeatures::GetFontBaselineOption( bool* isAssigned) const
{
	FontBaselineOption ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFontBaselineOption(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

FontOpenTypePositionOption ICharFeatures::GetFontOpenTypePositionOption( bool* isAssigned) const
{
	FontOpenTypePositionOption ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFontOpenTypePositionOption(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

StrikethroughPosition ICharFeatures::GetStrikethroughPosition( bool* isAssigned) const
{
	StrikethroughPosition ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStrikethroughPosition(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

UnderlinePosition ICharFeatures::GetUnderlinePosition( bool* isAssigned) const
{
	UnderlinePosition ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetUnderlinePosition(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetUnderlineOffset( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetUnderlineOffset(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool ICharFeatures::GetLigature( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLigature(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetDiscretionaryLigatures( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetDiscretionaryLigatures(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetContextualLigatures( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetContextualLigatures(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetAlternateLigatures( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetAlternateLigatures(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetOldStyle( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetOldStyle(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetFractions( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFractions(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetOrdinals( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetOrdinals(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetSwash( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetSwash(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetTitling( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetTitling(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetConnectionForms( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetConnectionForms(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetStylisticAlternates( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStylisticAlternates(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetStylisticSets(bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStylisticSets(fCharFeatures, &isAssignedRet, &ret);
	if (error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetOrnaments( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetOrnaments(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

FigureStyle ICharFeatures::GetFigureStyle( bool* isAssigned) const
{
	FigureStyle ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFigureStyle(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetProportionalMetrics( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetProportionalMetrics(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetKana( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetKana(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetRuby( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetRuby(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetItalics( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetItalics(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

BaselineDirection ICharFeatures::GetBaselineDirection( bool* isAssigned) const
{
	BaselineDirection ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetBaselineDirection(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

Language ICharFeatures::GetLanguage( bool* isAssigned) const
{
	Language ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLanguage(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

JapaneseAlternateFeature ICharFeatures::GetJapaneseAlternateFeature( bool* isAssigned) const
{
	JapaneseAlternateFeature ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetJapaneseAlternateFeature(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetTsume( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetTsume(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

StyleRunAlignment ICharFeatures::GetStyleRunAlignment( bool* isAssigned) const
{
	StyleRunAlignment ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStyleRunAlignment(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetWariChuEnabled( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuEnabled(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetWariChuLineCount( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuLineCount(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetWariChuLineGap( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuLineGap(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetWariChuScale( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuScale(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetWariChuSize( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuSize(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetWariChuWidowAmount( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuWidowAmount(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetWariChuOrphanAmount( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuOrphanAmount(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

WariChuJustification ICharFeatures::GetWariChuJustification( bool* isAssigned) const
{
	WariChuJustification ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetWariChuJustification(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetTCYUpDownAdjustment( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetTCYUpDownAdjustment(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 ICharFeatures::GetTCYLeftRightAdjustment( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetTCYLeftRightAdjustment(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetLeftAki( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLeftAki(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetRightAki( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetRightAki(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool ICharFeatures::GetNoBreak( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetNoBreak(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

IApplicationPaint ICharFeatures::GetFillColor( bool* isAssigned) const
{
	ApplicationPaintRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFillColor(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return IApplicationPaint(ret);
}

IApplicationPaint ICharFeatures::GetStrokeColor( bool* isAssigned) const
{
	ApplicationPaintRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStrokeColor(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return IApplicationPaint(ret);
}

bool ICharFeatures::GetFill( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFill(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetFillVisible( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFillVisible(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetStroke( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStroke(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}


bool ICharFeatures::GetStrokeVisible( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStrokeVisible(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetFillFirst( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFillFirst(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetFillOverPrint( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFillOverPrint(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetStrokeOverPrint( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStrokeOverPrint(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

IApplicationPaint ICharFeatures::GetFillBackgroundColor( bool* isAssigned) const
{
	ApplicationPaintRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFillBackgroundColor(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return IApplicationPaint(ret);
}

bool ICharFeatures::GetFillBackground( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetFillBackground(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

LineCapType ICharFeatures::GetLineCap( bool* isAssigned) const
{
	LineCapType ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLineCap(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

LineJoinType ICharFeatures::GetLineJoin( bool* isAssigned) const
{
	LineJoinType ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLineJoin(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetLineWidth( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLineWidth(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetMiterLimit( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetMiterLimit(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetLineDashOffset( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLineDashOffset(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

IArrayReal ICharFeatures::GetLineDashArray( bool* isAssigned) const
{
	ArrayRealRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetLineDashArray(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return IArrayReal(ret);
}

#if SLO_COMPLEXSCRIPT
Kashidas ICharFeatures::GetKashidas( bool* isAssigned) const
{
	Kashidas ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetKashidas(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

DirOverride ICharFeatures::GetDirOverride( bool* isAssigned) const
{
	DirOverride ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetDirOverride(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

DigitSet ICharFeatures::GetDigitSet( bool* isAssigned) const
{
	DigitSet ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetDigitSet(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

DiacVPos ICharFeatures::GetDiacVPos( bool* isAssigned) const
{
	DiacVPos ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetDiacVPos(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetDiacXOffset( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetDiacXOffset(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetDiacYOffset( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetDiacYOffset(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool ICharFeatures::GetAutoMydfb( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetAutoMydfb(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real ICharFeatures::GetMarkYDistFromBaseline( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetMarkYDistFromBaseline(fCharFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool ICharFeatures::GetOverlapSwash( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetOverlapSwash(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetJustificationAlternates( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetJustificationAlternates(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool ICharFeatures::GetStretchedAlternates( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sCharFeatures->GetStretchedAlternates(fCharFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}
#endif

void ICharFeatures::SetFont( IFont newVal)
{
	ATEErr error = sCharFeatures->SetFont(fCharFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFontSize( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetFontSize(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetHorizontalScale( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetHorizontalScale(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetVerticalScale( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetVerticalScale(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetAutoLeading( bool newVal)
{
	ATEErr error = sCharFeatures->SetAutoLeading(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLeading( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetLeading(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetTracking( ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetTracking(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetBaselineShift( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetBaselineShift(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetCharacterRotation( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetCharacterRotation(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetAutoKernType( AutoKernType newVal)
{
	ATEErr error = sCharFeatures->SetAutoKernType(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFontCapsOption( FontCapsOption newVal)
{
	ATEErr error = sCharFeatures->SetFontCapsOption(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFontBaselineOption( FontBaselineOption newVal)
{
	ATEErr error = sCharFeatures->SetFontBaselineOption(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFontOpenTypePositionOption( FontOpenTypePositionOption newVal)
{
	ATEErr error = sCharFeatures->SetFontOpenTypePositionOption(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStrikethroughPosition( StrikethroughPosition newVal)
{
	ATEErr error = sCharFeatures->SetStrikethroughPosition(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetUnderlinePosition( UnderlinePosition newVal)
{
	ATEErr error = sCharFeatures->SetUnderlinePosition(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetUnderlineOffset( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetUnderlineOffset(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLigature( bool newVal)
{
	ATEErr error = sCharFeatures->SetLigature(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetDiscretionaryLigatures( bool newVal)
{
	ATEErr error = sCharFeatures->SetDiscretionaryLigatures(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetContextualLigatures( bool newVal)
{
	ATEErr error = sCharFeatures->SetContextualLigatures(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetAlternateLigatures( bool newVal)
{
	ATEErr error = sCharFeatures->SetAlternateLigatures(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetOldStyle( bool newVal)
{
	ATEErr error = sCharFeatures->SetOldStyle(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFractions( bool newVal)
{
	ATEErr error = sCharFeatures->SetFractions(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetOrdinals( bool newVal)
{
	ATEErr error = sCharFeatures->SetOrdinals(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetSwash( bool newVal)
{
	ATEErr error = sCharFeatures->SetSwash(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetTitling( bool newVal)
{
	ATEErr error = sCharFeatures->SetTitling(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetConnectionForms( bool newVal)
{
	ATEErr error = sCharFeatures->SetConnectionForms(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStylisticAlternates( bool newVal)
{
	ATEErr error = sCharFeatures->SetStylisticAlternates(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStylisticSets(ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetStylisticSets(fCharFeatures, newVal);
	if (error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetOrnaments( bool newVal)
{
	ATEErr error = sCharFeatures->SetOrnaments(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFigureStyle( FigureStyle newVal)
{
	ATEErr error = sCharFeatures->SetFigureStyle(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetProportionalMetrics( bool newVal)
{
	ATEErr error = sCharFeatures->SetProportionalMetrics(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetKana( bool newVal)
{
	ATEErr error = sCharFeatures->SetKana(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetItalics( bool newVal)
{
	ATEErr error = sCharFeatures->SetItalics(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetRuby( bool newVal)
{
	ATEErr error = sCharFeatures->SetRuby(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetBaselineDirection( BaselineDirection newVal)
{
	ATEErr error = sCharFeatures->SetBaselineDirection(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLanguage( Language newVal)
{
	ATEErr error = sCharFeatures->SetLanguage(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetJapaneseAlternateFeature( JapaneseAlternateFeature newVal)
{
	ATEErr error = sCharFeatures->SetJapaneseAlternateFeature(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetTsume( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetTsume(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStyleRunAlignment( StyleRunAlignment newVal)
{
	ATEErr error = sCharFeatures->SetStyleRunAlignment(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuEnabled( bool newVal)
{
	ATEErr error = sCharFeatures->SetWariChuEnabled(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuLineCount( ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetWariChuLineCount(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuLineGap( ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetWariChuLineGap(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuScale( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetWariChuScale(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuSize( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetWariChuSize(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuWidowAmount( ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetWariChuWidowAmount(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuOrphanAmount( ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetWariChuOrphanAmount(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetWariChuJustification( WariChuJustification newVal)
{
	ATEErr error = sCharFeatures->SetWariChuJustification(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetTCYUpDownAdjustment( ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetTCYUpDownAdjustment(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetTCYLeftRightAdjustment( ATETextDOM::Int32 newVal)
{
	ATEErr error = sCharFeatures->SetTCYLeftRightAdjustment(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLeftAki( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetLeftAki(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetRightAki( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetRightAki(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetNoBreak( bool newVal)
{
	ATEErr error = sCharFeatures->SetNoBreak(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFillColor( IApplicationPaint newVal)
{
	ATEErr error = sCharFeatures->SetFillColor(fCharFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStrokeColor( IApplicationPaint newVal)
{
	ATEErr error = sCharFeatures->SetStrokeColor(fCharFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFill( bool newVal)
{
	ATEErr error = sCharFeatures->SetFill(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFillVisible( bool newVal)
{
	ATEErr error = sCharFeatures->SetFillVisible(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStroke( bool newVal)
{
	ATEErr error = sCharFeatures->SetStroke(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStrokeVisible( bool newVal)
{
	ATEErr error = sCharFeatures->SetStrokeVisible(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFillFirst( bool newVal)
{
	ATEErr error = sCharFeatures->SetFillFirst(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFillOverPrint( bool newVal)
{
	ATEErr error = sCharFeatures->SetFillOverPrint(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStrokeOverPrint( bool newVal)
{
	ATEErr error = sCharFeatures->SetStrokeOverPrint(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFillBackgroundColor( IApplicationPaint newVal)
{
	ATEErr error = sCharFeatures->SetFillBackgroundColor(fCharFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetFillBackground( bool newVal)
{
	ATEErr error = sCharFeatures->SetFillBackground(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}
void ICharFeatures::SetLineCap( LineCapType newVal)
{
	ATEErr error = sCharFeatures->SetLineCap(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLineJoin( LineJoinType newVal)
{
	ATEErr error = sCharFeatures->SetLineJoin(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLineWidth( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetLineWidth(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetMiterLimit( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetMiterLimit(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLineDashOffset( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetLineDashOffset(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetLineDashArray( IArrayReal newVal)
{
	ATEErr error = sCharFeatures->SetLineDashArray(fCharFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

#if SLO_COMPLEXSCRIPT
void ICharFeatures::SetKashidas( Kashidas newVal)
{
	ATEErr error = sCharFeatures->SetKashidas(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetDirOverride( DirOverride newVal)
{
	ATEErr error = sCharFeatures->SetDirOverride(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetDigitSet( DigitSet newVal)
{
	ATEErr error = sCharFeatures->SetDigitSet(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetDiacVPos( DiacVPos newVal)
{
	ATEErr error = sCharFeatures->SetDiacVPos(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetDiacXOffset( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetDiacXOffset(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetDiacYOffset( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetDiacYOffset(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetAutoMydfb( bool newVal)
{
	ATEErr error = sCharFeatures->SetAutoMydfb(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetMarkYDistFromBaseline( ATETextDOM::Real newVal)
{
	ATEErr error = sCharFeatures->SetMarkYDistFromBaseline(fCharFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetOverlapSwash( bool newVal)
{
	ATEErr error = sCharFeatures->SetOverlapSwash(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetJustificationAlternates( bool newVal)
{
	ATEErr error = sCharFeatures->SetJustificationAlternates(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::SetStretchedAlternates( bool newVal)
{
	ATEErr error = sCharFeatures->SetStretchedAlternates(fCharFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}
#endif

void ICharFeatures::ClearFont( )
{
	ATEErr error = sCharFeatures->ClearFont(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFontSize( )
{
	ATEErr error = sCharFeatures->ClearFontSize(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearHorizontalScale( )
{
	ATEErr error = sCharFeatures->ClearHorizontalScale(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearVerticalScale( )
{
	ATEErr error = sCharFeatures->ClearVerticalScale(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearAutoLeading( )
{
	ATEErr error = sCharFeatures->ClearAutoLeading(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLeading( )
{
	ATEErr error = sCharFeatures->ClearLeading(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearTracking( )
{
	ATEErr error = sCharFeatures->ClearTracking(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearBaselineShift( )
{
	ATEErr error = sCharFeatures->ClearBaselineShift(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearCharacterRotation( )
{
	ATEErr error = sCharFeatures->ClearCharacterRotation(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearAutoKernType( )
{
	ATEErr error = sCharFeatures->ClearAutoKernType(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFontCapsOption( )
{
	ATEErr error = sCharFeatures->ClearFontCapsOption(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFontBaselineOption( )
{
	ATEErr error = sCharFeatures->ClearFontBaselineOption(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFontOpenTypePositionOption( )
{
	ATEErr error = sCharFeatures->ClearFontOpenTypePositionOption(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStrikethroughPosition( )
{
	ATEErr error = sCharFeatures->ClearStrikethroughPosition(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearUnderlinePosition( )
{
	ATEErr error = sCharFeatures->ClearUnderlinePosition(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearUnderlineOffset( )
{
	ATEErr error = sCharFeatures->ClearUnderlineOffset(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLigature( )
{
	ATEErr error = sCharFeatures->ClearLigature(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearDiscretionaryLigatures( )
{
	ATEErr error = sCharFeatures->ClearDiscretionaryLigatures(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearContextualLigatures( )
{
	ATEErr error = sCharFeatures->ClearContextualLigatures(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearAlternateLigatures( )
{
	ATEErr error = sCharFeatures->ClearAlternateLigatures(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearOldStyle( )
{
	ATEErr error = sCharFeatures->ClearOldStyle(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFractions( )
{
	ATEErr error = sCharFeatures->ClearFractions(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearOrdinals( )
{
	ATEErr error = sCharFeatures->ClearOrdinals(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearSwash( )
{
	ATEErr error = sCharFeatures->ClearSwash(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearTitling( )
{
	ATEErr error = sCharFeatures->ClearTitling(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearConnectionForms( )
{
	ATEErr error = sCharFeatures->ClearConnectionForms(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStylisticAlternates( )
{
	ATEErr error = sCharFeatures->ClearStylisticAlternates(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStylisticSets()
{
	ATEErr error = sCharFeatures->ClearStylisticSets(fCharFeatures);
	if (error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearOrnaments( )
{
	ATEErr error = sCharFeatures->ClearOrnaments(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFigureStyle( )
{
	ATEErr error = sCharFeatures->ClearFigureStyle(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearProportionalMetrics( )
{
	ATEErr error = sCharFeatures->ClearProportionalMetrics(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearKana( )
{
	ATEErr error = sCharFeatures->ClearKana(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearItalics( )
{
	ATEErr error = sCharFeatures->ClearItalics(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearRuby( )
{
	ATEErr error = sCharFeatures->ClearRuby(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearBaselineDirection( )
{
	ATEErr error = sCharFeatures->ClearBaselineDirection(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLanguage( )
{
	ATEErr error = sCharFeatures->ClearLanguage(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearJapaneseAlternateFeature( )
{
	ATEErr error = sCharFeatures->ClearJapaneseAlternateFeature(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearTsume( )
{
	ATEErr error = sCharFeatures->ClearTsume(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStyleRunAlignment( )
{
	ATEErr error = sCharFeatures->ClearStyleRunAlignment(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearWariChuEnabled( )
{
	ATEErr error = sCharFeatures->ClearWariChuEnabled(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearWariChuLineCount( )
{
	ATEErr error = sCharFeatures->ClearWariChuLineCount(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearWariChuLineGap( )
{
	ATEErr error = sCharFeatures->ClearWariChuLineGap(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearWariChuSubLineAmount( )
{
	ATEErr error = sCharFeatures->ClearWariChuSubLineAmount(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearWariChuWidowAmount( )
{
	ATEErr error = sCharFeatures->ClearWariChuWidowAmount(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearWariChuOrphanAmount( )
{
	ATEErr error = sCharFeatures->ClearWariChuOrphanAmount(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearWariChuJustification( )
{
	ATEErr error = sCharFeatures->ClearWariChuJustification(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearTCYUpDownAdjustment( )
{
	ATEErr error = sCharFeatures->ClearTCYUpDownAdjustment(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearTCYLeftRightAdjustment( )
{
	ATEErr error = sCharFeatures->ClearTCYLeftRightAdjustment(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLeftAki( )
{
	ATEErr error = sCharFeatures->ClearLeftAki(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearRightAki( )
{
	ATEErr error = sCharFeatures->ClearRightAki(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearNoBreak( )
{
	ATEErr error = sCharFeatures->ClearNoBreak(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFillColor( )
{
	ATEErr error = sCharFeatures->ClearFillColor(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStrokeColor( )
{
	ATEErr error = sCharFeatures->ClearStrokeColor(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFill( )
{
	ATEErr error = sCharFeatures->ClearFill(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFillVisible( )
{
	ATEErr error = sCharFeatures->ClearFillVisible(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStroke( )
{
	ATEErr error = sCharFeatures->ClearStroke(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStrokeVisible( )
{
	ATEErr error = sCharFeatures->ClearStrokeVisible(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFillFirst( )
{
	ATEErr error = sCharFeatures->ClearFillFirst(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFillOverPrint( )
{
	ATEErr error = sCharFeatures->ClearFillOverPrint(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStrokeOverPrint( )
{
	ATEErr error = sCharFeatures->ClearStrokeOverPrint(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFillBackgroundColor( )
{
	ATEErr error = sCharFeatures->ClearFillBackgroundColor(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearFillBackground( )
{
	ATEErr error = sCharFeatures->ClearFillBackground(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLineCap( )
{
	ATEErr error = sCharFeatures->ClearLineCap(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLineJoin( )
{
	ATEErr error = sCharFeatures->ClearLineJoin(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLineWidth( )
{
	ATEErr error = sCharFeatures->ClearLineWidth(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearMiterLimit( )
{
	ATEErr error = sCharFeatures->ClearMiterLimit(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLineDashOffset( )
{
	ATEErr error = sCharFeatures->ClearLineDashOffset(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearLineDashArray( )
{
	ATEErr error = sCharFeatures->ClearLineDashArray(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

#if SLO_COMPLEXSCRIPT
void ICharFeatures::ClearKashidas( )
{
	ATEErr error = sCharFeatures->ClearKashidas(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearDirOverride( )
{
	ATEErr error = sCharFeatures->ClearDirOverride(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearDigitSet( )
{
	ATEErr error = sCharFeatures->ClearDigitSet(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearDiacVPos( )
{
	ATEErr error = sCharFeatures->ClearDiacVPos(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearDiacXOffset( )
{
	ATEErr error = sCharFeatures->ClearDiacXOffset(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearDiacYOffset( )
{
	ATEErr error = sCharFeatures->ClearDiacYOffset(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearAutoMydfb( )
{
	ATEErr error = sCharFeatures->ClearAutoMydfb(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearMarkYDistFromBaseline( )
{
	ATEErr error = sCharFeatures->ClearMarkYDistFromBaseline(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearOverlapSwash( )
{
	ATEErr error = sCharFeatures->ClearOverlapSwash(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearJustificationAlternates( )
{
	ATEErr error = sCharFeatures->ClearJustificationAlternates(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}

void ICharFeatures::ClearStretchedAlternates( )
{
	ATEErr error = sCharFeatures->ClearStretchedAlternates(fCharFeatures);
	if(error) Throw_ATE_Exception(error);
}
#endif

bool ICharFeatures::IntersectFeatures( ICharFeatures rhs)
{
	ATEBool8 ret;
	ATEErr error = sCharFeatures->IntersectFeatures(fCharFeatures, rhs.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharFeatures::ReplaceOrAddFeatures( ICharFeatures rhs)
{
	ATEBool8 ret;
	ATEErr error = sCharFeatures->ReplaceOrAddFeatures(fCharFeatures, rhs.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharFeatures::UnassignEachIfEqual( ICharFeatures rhs)
{
	ATEBool8 ret;
	ATEErr error = sCharFeatures->UnassignEachIfEqual(fCharFeatures, rhs.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharFeatures::IsEachNotAssigned( ) const
{
	ATEBool8 ret;
	ATEErr error = sCharFeatures->IsEachNotAssigned(fCharFeatures, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharFeatures::IsEachAssigned( ) const
{
	ATEBool8 ret;
	ATEErr error = sCharFeatures->IsEachAssigned(fCharFeatures, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --ICharInspector--
//////////////////////////////////////////////

ICharInspector::ICharInspector()
:fCharInspector(0)
{
	ATEErr error = sCharInspector->Initialize(&fCharInspector);
	if(error) Throw_ATE_Exception(error);
}

ICharInspector::ICharInspector(CharInspectorRef charinspector)
:fCharInspector(charinspector)
{
}

ICharInspector::ICharInspector(const ICharInspector& src)
:fCharInspector(src.fCharInspector)
{
	sCharInspector->AddRef(fCharInspector);
}

ICharInspector::~ICharInspector()
{
	sCharInspector->Release(fCharInspector);
}

ICharInspector& ICharInspector::operator=(const ICharInspector& rhs)
{
	if (&rhs != this)
	{
		sCharInspector->Release(fCharInspector);
		fCharInspector = rhs.fCharInspector;
		sCharInspector->AddRef(fCharInspector);
	}
	return *this;
}

bool ICharInspector::operator==(const ICharInspector& rhs) const
{
	return fCharInspector == rhs.fCharInspector;
}

bool ICharInspector::operator!=(const ICharInspector& rhs) const
{
	return !(*this == rhs);
}

CharInspectorRef ICharInspector::GetRef() const
{
	return fCharInspector;
}

bool ICharInspector::IsNull() const
{
	return sCharInspector->IsNull(fCharInspector);
}

IArrayFontRef ICharInspector::GetFont( ) const
{
	ArrayFontRefRef ret = 0;
	ATEErr error = sCharInspector->GetFont(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayFontRef(ret);
}

IArrayReal ICharInspector::GetFontSize( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetFontSize(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetHorizontalScale( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetHorizontalScale(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetVerticalScale( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetVerticalScale(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool ICharInspector::GetSyntheticBold( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetSyntheticBold(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetSyntheticItalic( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetSyntheticItalic(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetAutoLeading( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetAutoLeading(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayReal ICharInspector::GetLeading( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetLeading(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayInteger ICharInspector::GetTracking( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetTracking(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayReal ICharInspector::GetBaselineShift( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetBaselineShift(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetCharacterRotation( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetCharacterRotation(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayFontCapsOption ICharInspector::GetFontCapsOption( ) const
{
	ArrayFontCapsOptionRef ret = 0;
	ATEErr error = sCharInspector->GetFontCapsOption(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayFontCapsOption(ret);
}

IArrayFontBaselineOption ICharInspector::GetFontBaselineOption( ) const
{
	ArrayFontBaselineOptionRef ret = 0;
	ATEErr error = sCharInspector->GetFontBaselineOption(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayFontBaselineOption(ret);
}

IArrayFontOpenTypePositionOption ICharInspector::GetFontOpenTypePositionOption( ) const
{
	ArrayFontOpenTypePositionOptionRef ret = 0;
	ATEErr error = sCharInspector->GetFontOpenTypePositionOption(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayFontOpenTypePositionOption(ret);
}

IArrayStrikethroughPosition ICharInspector::GetStrikethroughPosition( ) const
{
	ArrayStrikethroughPositionRef ret = 0;
	ATEErr error = sCharInspector->GetStrikethroughPosition(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayStrikethroughPosition(ret);
}

IArrayUnderlinePosition ICharInspector::GetUnderlinePosition( ) const
{
	ArrayUnderlinePositionRef ret = 0;
	ATEErr error = sCharInspector->GetUnderlinePosition(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayUnderlinePosition(ret);
}

IArrayReal ICharInspector::GetUnderlineOffset( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetUnderlineOffset(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool ICharInspector::GetLigature( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetLigature(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetDiscretionaryLigatures( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetDiscretionaryLigatures(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetContextualLigatures( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetContextualLigatures(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetAlternateLigatures( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetAlternateLigatures(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetOldStyle( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetOldStyle(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetFractions( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetFractions(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetOrdinals( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetOrdinals(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetSwash( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetSwash(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetTitling( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetTitling(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetConnectionForms( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetConnectionForms(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetStylisticAlternates( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetStylisticAlternates(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayInteger ICharInspector::GetStylisticSets() const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetStylisticSets(fCharInspector, &ret);
	if (error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayBool ICharInspector::GetOrnaments( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetOrnaments(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayFigureStyle ICharInspector::GetFigureStyle( ) const
{
	ArrayFigureStyleRef ret = 0;
	ATEErr error = sCharInspector->GetFigureStyle(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayFigureStyle(ret);
}

IArrayBool ICharInspector::GetProportionalMetrics( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetProportionalMetrics(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetKana( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetKana(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetItalics( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetItalics(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetRuby( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetRuby(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBaselineDirection ICharInspector::GetBaselineDirection( ) const
{
	ArrayBaselineDirectionRef ret = 0;
	ATEErr error = sCharInspector->GetBaselineDirection(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBaselineDirection(ret);
}

IArrayLanguage ICharInspector::GetLanguage( ) const
{
	ArrayLanguageRef ret = 0;
	ATEErr error = sCharInspector->GetLanguage(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayLanguage(ret);
}

IArrayReal ICharInspector::GetTsume( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetTsume(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayStyleRunAlignment ICharInspector::GetStyleRunAlignment( ) const
{
	ArrayStyleRunAlignmentRef ret = 0;
	ATEErr error = sCharInspector->GetStyleRunAlignment(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayStyleRunAlignment(ret);
}

IArrayInteger ICharInspector::GetWariChuLineCount( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuLineCount(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayInteger ICharInspector::GetWariChuLineGap( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuLineGap(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayReal ICharInspector::GetWariChuScale( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuScale(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetWariChuSize( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuSize(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayInteger ICharInspector::GetWariChuWidowAmount( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuWidowAmount(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayInteger ICharInspector::GetWariChuOrphanAmount( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuOrphanAmount(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayWariChuJustification ICharInspector::GetWariChuJustification( ) const
{
	ArrayWariChuJustificationRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuJustification(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayWariChuJustification(ret);
}

IArrayBool ICharInspector::GetWariChuEnabled( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetWariChuEnabled(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayInteger ICharInspector::GetTCYUpDownAdjustment( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetTCYUpDownAdjustment(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayInteger ICharInspector::GetTCYLeftRightAdjustment( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sCharInspector->GetTCYLeftRightAdjustment(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayReal ICharInspector::GetLeftAki( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetLeftAki(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetRightAki( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetRightAki(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool ICharInspector::GetNoBreak( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetNoBreak(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayApplicationPaintRef ICharInspector::GetFillColor( ) const
{
	ArrayApplicationPaintRefRef ret = 0;
	ATEErr error = sCharInspector->GetFillColor(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayApplicationPaintRef(ret);
}

IArrayApplicationPaintRef ICharInspector::GetStrokeColor( ) const
{
	ArrayApplicationPaintRefRef ret = 0;
	ATEErr error = sCharInspector->GetStrokeColor(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayApplicationPaintRef(ret);
}

IArrayBool ICharInspector::GetFill( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetFill(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetFillVisible( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetFillVisible(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetStroke( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetStroke(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetStrokeVisible( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetStrokeVisible(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetFillFirst( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetFillFirst(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetFillOverPrint( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetFillOverPrint(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetStrokeOverPrint( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetStrokeOverPrint(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayApplicationPaintRef ICharInspector::GetFillBackgroundColor( ) const
{
	ArrayApplicationPaintRefRef ret = 0;
	ATEErr error = sCharInspector->GetFillBackgroundColor(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayApplicationPaintRef(ret);
}

IArrayBool ICharInspector::GetFillBackground( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetFillBackground(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayLineCapType ICharInspector::GetLineCap( ) const
{
	ArrayLineCapTypeRef ret = 0;
	ATEErr error = sCharInspector->GetLineCap(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayLineCapType(ret);
}

IArrayLineJoinType ICharInspector::GetLineJoin( ) const
{
	ArrayLineJoinTypeRef ret = 0;
	ATEErr error = sCharInspector->GetLineJoin(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayLineJoinType(ret);
}

IArrayReal ICharInspector::GetLineWidth( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetLineWidth(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetMiterLimit( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetMiterLimit(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetLineDashOffset( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetLineDashOffset(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayArrayReal ICharInspector::GetLineDashArray( ) const
{
	ArrayArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetLineDashArray(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayArrayReal(ret);
}

#if SLO_COMPLEXSCRIPT
IArrayKashidas ICharInspector::GetKashidas( ) const
{
	ArrayKashidasRef ret = 0;
	ATEErr error = sCharInspector->GetKashidas(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayKashidas(ret);
}

IArrayDirOverride ICharInspector::GetDirOverride( ) const
{
	ArrayDirOverrideRef ret = 0;
	ATEErr error = sCharInspector->GetDirOverride(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayDirOverride(ret);
}

IArrayDigitSet ICharInspector::GetDigitSet( ) const
{
	ArrayDigitSetRef ret = 0;
	ATEErr error = sCharInspector->GetDigitSet(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayDigitSet(ret);
}

IArrayDiacVPos ICharInspector::GetDiacVPos( ) const
{
	ArrayDiacVPosRef ret = 0;
	ATEErr error = sCharInspector->GetDiacVPos(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayDiacVPos(ret);
}

IArrayReal ICharInspector::GetDiacXOffset( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetDiacXOffset(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal ICharInspector::GetDiacYOffset( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetDiacYOffset(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool ICharInspector::GetAutoMydfb( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetAutoMydfb(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayReal ICharInspector::GetMarkYDistFromBaseline( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sCharInspector->GetMarkYDistFromBaseline(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool ICharInspector::GetOverlapSwash( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetOverlapSwash(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetJustificationAlternates( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetJustificationAlternates(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBool ICharInspector::GetStretchedAlternates( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sCharInspector->GetStretchedAlternates(fCharInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}
#endif

//////////////////////////////////////////////
// --ICharStyle--
//////////////////////////////////////////////

ICharStyle::ICharStyle()
:fCharStyle(0)
{
}

ICharStyle::ICharStyle(CharStyleRef charstyle)
:fCharStyle(charstyle)
{
}

ICharStyle::ICharStyle(const ICharStyle& src)
:fCharStyle(src.fCharStyle)
{
	sCharStyle->AddRef(fCharStyle);
}

ICharStyle::~ICharStyle()
{
	sCharStyle->Release(fCharStyle);
}

ICharStyle& ICharStyle::operator=(const ICharStyle& rhs)
{
	if (&rhs != this)
	{
		sCharStyle->Release(fCharStyle);
		fCharStyle = rhs.fCharStyle;
		sCharStyle->AddRef(fCharStyle);
	}
	return *this;
}

bool ICharStyle::operator==(const ICharStyle& rhs) const
{
	ATEBool8 ret = false;
	ATEErr error = sCharStyle->IsEqual(fCharStyle, rhs.fCharStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharStyle::operator!=(const ICharStyle& rhs) const
{
	return !(*this == rhs);
}

CharStyleRef ICharStyle::GetRef() const
{
	return fCharStyle;
}

bool ICharStyle::IsNull() const
{
	return sCharStyle->IsNull(fCharStyle);
}

ATETextDOM::Int32 ICharStyle::GetName( ATETextDOM::Unicode* pName, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCharStyle->GetName(fCharStyle, pName, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharStyle::SetName( const ATETextDOM::Unicode* pName)
{
	ATEBool8 ret;
	ATEErr error = sCharStyle->SetName(fCharStyle, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICharStyle ICharStyle::GetParent( ) const
{
	CharStyleRef ret = 0;
	ATEErr error = sCharStyle->GetParent(fCharStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyle(ret);
}

bool ICharStyle::SetParent( const ICharStyle pStyle)
{
	ATEBool8 ret;
	ATEErr error = sCharStyle->SetParent(fCharStyle, pStyle.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharStyle::HasParent( ) const
{
	ATEBool8 ret;
	ATEErr error = sCharStyle->HasParent(fCharStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICharFeatures ICharStyle::GetFeatures( ) const
{
	CharFeaturesRef ret = 0;
	ATEErr error = sCharStyle->GetFeatures(fCharStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

void ICharStyle::SetFeatures( ICharFeatures pFeatures)
{
	ATEErr error = sCharStyle->SetFeatures(fCharStyle, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ICharStyle::ReplaceOrAddFeatures( ICharFeatures pFeatures)
{
	ATEErr error = sCharStyle->ReplaceOrAddFeatures(fCharStyle, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --ICharStyles--
//////////////////////////////////////////////

ICharStyles::ICharStyles()
:fCharStyles(0)
{
}

ICharStyles::ICharStyles(CharStylesRef charstyles)
:fCharStyles(charstyles)
{
}

ICharStyles::ICharStyles(const ICharStyles& src)
:fCharStyles(src.fCharStyles)
{
	sCharStyles->AddRef(fCharStyles);
}

ICharStyles::~ICharStyles()
{
	sCharStyles->Release(fCharStyles);
}

ICharStyles& ICharStyles::operator=(const ICharStyles& rhs)
{
	if (&rhs != this)
	{
		sCharStyles->Release(fCharStyles);
		fCharStyles = rhs.fCharStyles;
		sCharStyles->AddRef(fCharStyles);
	}
	return *this;
}

bool ICharStyles::operator==(const ICharStyles& rhs) const
{
	return fCharStyles == rhs.fCharStyles;
}

bool ICharStyles::operator!=(const ICharStyles& rhs) const
{
	return !(*this == rhs);
}

CharStylesRef ICharStyles::GetRef() const
{
	return fCharStyles;
}

bool ICharStyles::IsNull() const
{
	return sCharStyles->IsNull(fCharStyles);
}

bool ICharStyles::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sCharStyles->IsEmpty(fCharStyles, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ICharStyles::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sCharStyles->GetSize(fCharStyles, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICharStyles::ShowAllStyles( ) const
{
	ATEErr error = sCharStyles->ShowAllStyles(fCharStyles);
	if(error) Throw_ATE_Exception(error);
}

void ICharStyles::ShowOnlyUnreferencedStyles( ) const
{
	ATEErr error = sCharStyles->ShowOnlyUnreferencedStyles(fCharStyles);
	if(error) Throw_ATE_Exception(error);
}

void ICharStyles::ShowOnlyStylesReferencedIn( ITextRange pRange) const
{
	ATEErr error = sCharStyles->ShowOnlyStylesReferencedIn(fCharStyles, pRange.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ICharStyles::MoveStyleTo( ICharStyle pStyle, ATETextDOM::Int32 position)
{
	ATEErr error = sCharStyles->MoveStyleTo(fCharStyles, pStyle.GetRef(), position);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --ICharStylesIterator--
//////////////////////////////////////////////

ICharStylesIterator::ICharStylesIterator()
:fCharStylesIterator(0)
{
}

ICharStylesIterator::ICharStylesIterator(CharStylesIteratorRef charstylesiterator)
:fCharStylesIterator(charstylesiterator)
{
}

ICharStylesIterator::ICharStylesIterator(const ICharStylesIterator& src)
:fCharStylesIterator(src.fCharStylesIterator)
{
	sCharStylesIterator->AddRef(fCharStylesIterator);
}

ICharStylesIterator::~ICharStylesIterator()
{
	sCharStylesIterator->Release(fCharStylesIterator);
}

ICharStylesIterator& ICharStylesIterator::operator=(const ICharStylesIterator& rhs)
{
	if (&rhs != this)
	{
		sCharStylesIterator->Release(fCharStylesIterator);
		fCharStylesIterator = rhs.fCharStylesIterator;
		sCharStylesIterator->AddRef(fCharStylesIterator);
	}
	return *this;
}

bool ICharStylesIterator::operator==(const ICharStylesIterator& rhs) const
{
	return fCharStylesIterator == rhs.fCharStylesIterator;
}

bool ICharStylesIterator::operator!=(const ICharStylesIterator& rhs) const
{
	return !(*this == rhs);
}

CharStylesIteratorRef ICharStylesIterator::GetRef() const
{
	return fCharStylesIterator;
}

bool ICharStylesIterator::IsNull() const
{
	return sCharStylesIterator->IsNull(fCharStylesIterator);
}

ICharStylesIterator::ICharStylesIterator( ICharStyles pStyles, Direction direction)
{
	ATEErr error = sCharStylesIterator->Initialize(pStyles.GetRef(), direction, &fCharStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

bool ICharStylesIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sCharStylesIterator->IsNotDone(fCharStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharStylesIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sCharStylesIterator->IsDone(fCharStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ICharStylesIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sCharStylesIterator->IsEmpty(fCharStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ICharStylesIterator::MoveToFirst( )
{
	ATEErr error = sCharStylesIterator->MoveToFirst(fCharStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

void ICharStylesIterator::MoveToLast( )
{
	ATEErr error = sCharStylesIterator->MoveToLast(fCharStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

void ICharStylesIterator::Next( )
{
	ATEErr error = sCharStylesIterator->Next(fCharStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

void ICharStylesIterator::Previous( )
{
	ATEErr error = sCharStylesIterator->Previous(fCharStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

ICharStyle ICharStylesIterator::Item( ) const
{
	CharStyleRef ret = 0;
	ATEErr error = sCharStylesIterator->Item(fCharStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyle(ret);
}

//////////////////////////////////////////////
// --IFind--
//////////////////////////////////////////////

IFind::IFind()
:fFind(0)
{
}

IFind::IFind(FindRef find)
:fFind(find)
{
}

IFind::IFind(const IFind& src)
:fFind(src.fFind)
{
	sFind->AddRef(fFind);
}

IFind::~IFind()
{
	sFind->Release(fFind);
}

IFind& IFind::operator=(const IFind& rhs)
{
	if (&rhs != this)
	{
		sFind->Release(fFind);
		fFind = rhs.fFind;
		sFind->AddRef(fFind);
	}
	return *this;
}

bool IFind::operator==(const IFind& rhs) const
{
	return fFind == rhs.fFind;
}

bool IFind::operator!=(const IFind& rhs) const
{
	return !(*this == rhs);
}

FindRef IFind::GetRef() const
{
	return fFind;
}

bool IFind::IsNull() const
{
	return sFind->IsNull(fFind);
}

Direction IFind::GetSearchDirection( ) const
{
	Direction ret;
	ATEErr error = sFind->GetSearchDirection(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::GetIgnoreCase( ) const
{
	ATEBool8 ret;
	ATEErr error = sFind->GetIgnoreCase(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::GetWholeWord( ) const
{
	ATEBool8 ret;
	ATEErr error = sFind->GetWholeWord(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::GetWrap( ) const
{
	ATEBool8 ret;
	ATEErr error = sFind->GetWrap(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::GetFindWordsOutOfBounds( ) const
{
	ATEBool8 ret;
	ATEErr error = sFind->GetFindWordsOutOfBounds(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

#if SLO_COMPLEXSCRIPT
bool IFind::GetIgnoreAccents( ) const
{
	ATEBool8 ret;
	ATEErr error = sFind->GetIgnoreAccents(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::GetIgnoreKashidas( ) const
{
	ATEBool8 ret;
	ATEErr error = sFind->GetIgnoreKashidas(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}
#endif

void IFind::SetSearchDirection( Direction newValue)
{
	ATEErr error = sFind->SetSearchDirection(fFind, newValue);
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetIgnoreCase( bool newValue)
{
	ATEErr error = sFind->SetIgnoreCase(fFind, newValue);
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetWholeWord( bool newValue)
{
	ATEErr error = sFind->SetWholeWord(fFind, newValue);
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetWrap( bool newValue)
{
	ATEErr error = sFind->SetWrap(fFind, newValue);
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetFindWordsOutOfBounds( bool newValue)
{
	ATEErr error = sFind->SetFindWordsOutOfBounds(fFind, newValue);
	if(error) Throw_ATE_Exception(error);
}

#if SLO_COMPLEXSCRIPT
void IFind::SetIgnoreAccents( bool newValue)
{
	ATEErr error = sFind->SetIgnoreAccents(fFind, newValue);
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetIgnoreKashidas( bool newValue)
{
	ATEErr error = sFind->SetIgnoreKashidas(fFind, newValue);
	if(error) Throw_ATE_Exception(error);
}
#endif

SearchScope IFind::GetSearchScope( ) const
{
	SearchScope ret;
	ATEErr error = sFind->GetSearchScope(fFind, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IFind::SetSearchScope( SearchScope searchScope)
{
	ATEErr error = sFind->SetSearchScope(fFind, searchScope);
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetSearchRange( ITextRange pRange)
{
	ATEErr error = sFind->SetSearchRange(fFind, pRange.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetSearchChars( ATETextDOM::Unicode* pSearchChars)
{
	ATEErr error = sFind->SetSearchChars(fFind, pSearchChars);
	if(error) Throw_ATE_Exception(error);
}

void IFind::GetSearchChars( ATETextDOM::Unicode* pSearchChars, ATETextDOM::Int32 length) const
{
	ATEErr error = sFind->GetSearchChars(fFind, pSearchChars, length);
	if(error) Throw_ATE_Exception(error);
}

void IFind::SetReplaceChars( ATETextDOM::Unicode* pSearchChars)
{
	ATEErr error = sFind->SetReplaceChars(fFind, pSearchChars);
	if(error) Throw_ATE_Exception(error);
}

void IFind::GetReplaceChars( ATETextDOM::Unicode* pSearchChars, ATETextDOM::Int32 length) const
{
	ATEErr error = sFind->GetReplaceChars(fFind, pSearchChars, length);
	if(error) Throw_ATE_Exception(error);
}

void IFind::Reset( )
{
	ATEErr error = sFind->Reset(fFind);
	if(error) Throw_ATE_Exception(error);
}

bool IFind::FindMatch( ITextRange pTextRange)
{
	ATEBool8 ret;
	ATEErr error = sFind->FindMatch(fFind, pTextRange.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::FindNextMatch( ITextRange pTextRange)
{
	ATEBool8 ret;
	ATEErr error = sFind->FindNextMatch(fFind, pTextRange.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::ReplaceMatch( ITextRange pTextRange, bool findNext)
{
	ATEBool8 ret;
	ATEErr error = sFind->ReplaceMatch(fFind, pTextRange.GetRef(), findNext, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFind::FindAndReplaceAllMatches( ATETextDOM::Int32* pReplaceCount)
{
	ATEBool8 ret;
	ATEErr error = sFind->FindAndReplaceAllMatches(fFind, pReplaceCount, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IFind::GetPreReplaceAllSettings( ATETextDOM::Int32* pCurrentPoint, ATETextDOM::Int32* pStartPoint) const
{
	ATEErr error = sFind->GetPreReplaceAllSettings(fFind, pCurrentPoint, pStartPoint);
	if(error) Throw_ATE_Exception(error);
}

void IFind::RestorePreReplaceAllSettings( const ATETextDOM::Int32 currentPoint, const ATETextDOM::Int32 startPoint)
{
	ATEErr error = sFind->RestorePreReplaceAllSettings(fFind, currentPoint, startPoint);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IFont--
//////////////////////////////////////////////

IFont::IFont()
:fFont(0)
{
}

IFont::IFont(FontRef font)
:fFont(font)
{
}

IFont::IFont(const IFont& src)
:fFont(src.fFont)
{
	sFont->AddRef(fFont);
}

IFont::~IFont()
{
	sFont->Release(fFont);
}

IFont& IFont::operator=(const IFont& rhs)
{
	if (&rhs != this)
	{
		sFont->Release(fFont);
		fFont = rhs.fFont;
		sFont->AddRef(fFont);
	}
	return *this;
}

bool IFont::operator==(const IFont& rhs) const
{
	return fFont == rhs.fFont;
}

bool IFont::operator!=(const IFont& rhs) const
{
	return !(*this == rhs);
}

FontRef IFont::GetRef() const
{
	return fFont;
}

bool IFont::IsNull() const
{
	return sFont->IsNull(fFont);
}

bool IFont::IsCoolTypeTechnology( ) const
{
	ATEBool8 ret;
	ATEErr error = sFont->IsCoolTypeTechnology(fFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IFont::IsVerticalRomanGlyphsOnSideByDefault( bool withItalics, StyleRunAlignment characterAlignment) const
{
	ATEBool8 ret;
	ATEErr error = sFont->IsVerticalRomanGlyphsOnSideByDefault(fFont, withItalics, characterAlignment, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void* IFont::GetCTFontDict( )
{
	void* ret;
	ATEErr error = sFont->GetCTFontDict(fFont, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IGlyph--
//////////////////////////////////////////////

IGlyph::IGlyph()
:fGlyph(0)
{
}

IGlyph::IGlyph(GlyphRef glyph)
:fGlyph(glyph)
{
}

IGlyph::IGlyph(const IGlyph& src)
:fGlyph(src.fGlyph)
{
	sGlyph->AddRef(fGlyph);
}

IGlyph::~IGlyph()
{
	sGlyph->Release(fGlyph);
}

IGlyph& IGlyph::operator=(const IGlyph& rhs)
{
	if (&rhs != this)
	{
		sGlyph->Release(fGlyph);
		fGlyph = rhs.fGlyph;
		sGlyph->AddRef(fGlyph);
	}
	return *this;
}

bool IGlyph::operator==(const IGlyph& rhs) const
{
	return fGlyph == rhs.fGlyph;
}

bool IGlyph::operator!=(const IGlyph& rhs) const
{
	return !(*this == rhs);
}

GlyphRef IGlyph::GetRef() const
{
	return fGlyph;
}

bool IGlyph::IsNull() const
{
	return sGlyph->IsNull(fGlyph);
}

ATEGlyphID IGlyph::GetGlyphID( ) const
{
	ATEGlyphID ret;
	ATEErr error = sGlyph->GetGlyphID(fGlyph, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IGlyphs IGlyph::GetAlternateGlyphs( ) const
{
	GlyphsRef ret = 0;
	ATEErr error = sGlyph->GetAlternateGlyphs(fGlyph, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyphs(ret);
}

void IGlyph::GetOTFeatures( char** otFeatures, ATETextDOM::Int32* otFeatureCount, ATETextDOM::Int32** otFeatureIndex)
{
	ATEErr error = sGlyph->GetOTFeatures(fGlyph, otFeatures, otFeatureCount, otFeatureIndex);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IGlyphs--
//////////////////////////////////////////////

IGlyphs::IGlyphs()
:fGlyphs(0)
{
}

IGlyphs::IGlyphs(GlyphsRef glyphs)
:fGlyphs(glyphs)
{
}

IGlyphs::IGlyphs(const IGlyphs& src)
:fGlyphs(src.fGlyphs)
{
	sGlyphs->AddRef(fGlyphs);
}

IGlyphs::~IGlyphs()
{
	sGlyphs->Release(fGlyphs);
}

IGlyphs& IGlyphs::operator=(const IGlyphs& rhs)
{
	if (&rhs != this)
	{
		sGlyphs->Release(fGlyphs);
		fGlyphs = rhs.fGlyphs;
		sGlyphs->AddRef(fGlyphs);
	}
	return *this;
}

bool IGlyphs::operator==(const IGlyphs& rhs) const
{
	return fGlyphs == rhs.fGlyphs;
}

bool IGlyphs::operator!=(const IGlyphs& rhs) const
{
	return !(*this == rhs);
}

GlyphsRef IGlyphs::GetRef() const
{
	return fGlyphs;
}

bool IGlyphs::IsNull() const
{
	return sGlyphs->IsNull(fGlyphs);
}

ATETextDOM::Int32 IGlyphs::GetSize( )
{
	ATETextDOM::Int32 ret;
	ATEErr error = sGlyphs->GetSize(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IGlyph IGlyphs::GetFirst( )
{
	GlyphRef ret = 0;
	ATEErr error = sGlyphs->GetFirst(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

IGlyph IGlyphs::GetLast( )
{
	GlyphRef ret = 0;
	ATEErr error = sGlyphs->GetLast(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

ITextRanges IGlyphs::GetTextRanges( ) const
{
	TextRangesRef ret = 0;
	ATEErr error = sGlyphs->GetTextRanges(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

ITextRanges IGlyphs::GetTextSelection( ) const
{
	TextRangesRef ret = 0;
	ATEErr error = sGlyphs->GetTextSelection(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

IParagraphsIterator IGlyphs::GetParagraphsIterator( ) const
{
	ParagraphsIteratorRef ret = 0;
	ATEErr error = sGlyphs->GetParagraphsIterator(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraphsIterator(ret);
}

ITextRunsIterator IGlyphs::GetTextRunsIterator( ) const
{
	TextRunsIteratorRef ret = 0;
	ATEErr error = sGlyphs->GetTextRunsIterator(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRunsIterator(ret);
}

IWordsIterator IGlyphs::GetWordsIterator( ) const
{
	WordsIteratorRef ret = 0;
	ATEErr error = sGlyphs->GetWordsIterator(fGlyphs, &ret);
	if(error) Throw_ATE_Exception(error);
	return IWordsIterator(ret);
}

void IGlyphs::Add( const IGlyph& glyph)
{
	ATEErr error = sGlyphs->Add(fGlyphs, glyph.GetRef());
	if(error) Throw_ATE_Exception(error);
}

IGlyph IGlyphs::Item( ATETextDOM::Int32 nIndex) const
{
	GlyphRef ret = 0;
	ATEErr error = sGlyphs->Item(fGlyphs, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

void IGlyphs::RemoveAll( )
{
	ATEErr error = sGlyphs->RemoveAll(fGlyphs);
	if(error) Throw_ATE_Exception(error);
}

void IGlyphs::Remove( ATETextDOM::Int32 nIndex)
{
	ATEErr error = sGlyphs->Remove(fGlyphs, nIndex);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IGlyphsIterator--
//////////////////////////////////////////////

IGlyphsIterator::IGlyphsIterator()
:fGlyphsIterator(0)
{
}

IGlyphsIterator::IGlyphsIterator(GlyphsIteratorRef glyphsiterator)
:fGlyphsIterator(glyphsiterator)
{
}

IGlyphsIterator::IGlyphsIterator(const IGlyphsIterator& src)
:fGlyphsIterator(src.fGlyphsIterator)
{
	sGlyphsIterator->AddRef(fGlyphsIterator);
}

IGlyphsIterator::~IGlyphsIterator()
{
	sGlyphsIterator->Release(fGlyphsIterator);
}

IGlyphsIterator& IGlyphsIterator::operator=(const IGlyphsIterator& rhs)
{
	if (&rhs != this)
	{
		sGlyphsIterator->Release(fGlyphsIterator);
		fGlyphsIterator = rhs.fGlyphsIterator;
		sGlyphsIterator->AddRef(fGlyphsIterator);
	}
	return *this;
}

bool IGlyphsIterator::operator==(const IGlyphsIterator& rhs) const
{
	return fGlyphsIterator == rhs.fGlyphsIterator;
}

bool IGlyphsIterator::operator!=(const IGlyphsIterator& rhs) const
{
	return !(*this == rhs);
}

GlyphsIteratorRef IGlyphsIterator::GetRef() const
{
	return fGlyphsIterator;
}

bool IGlyphsIterator::IsNull() const
{
	return sGlyphsIterator->IsNull(fGlyphsIterator);
}

IGlyphsIterator::IGlyphsIterator( IGlyphs glyphs, Direction direction)
{
	ATEErr error = sGlyphsIterator->Initialize(glyphs.GetRef(), direction, &fGlyphsIterator);
	if(error) Throw_ATE_Exception(error);
}

bool IGlyphsIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sGlyphsIterator->IsNotDone(fGlyphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IGlyphsIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sGlyphsIterator->IsDone(fGlyphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IGlyphsIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sGlyphsIterator->IsEmpty(fGlyphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IGlyph IGlyphsIterator::GetFirst( )
{
	GlyphRef ret = 0;
	ATEErr error = sGlyphsIterator->GetFirst(fGlyphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

IGlyph IGlyphsIterator::GetLast( )
{
	GlyphRef ret = 0;
	ATEErr error = sGlyphsIterator->GetLast(fGlyphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

IGlyph IGlyphsIterator::GetNext( )
{
	GlyphRef ret = 0;
	ATEErr error = sGlyphsIterator->GetNext(fGlyphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

IGlyph IGlyphsIterator::Item( ) const
{
	GlyphRef ret = 0;
	ATEErr error = sGlyphsIterator->Item(fGlyphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return IGlyph(ret);
}

void IGlyphsIterator::Next( )
{
	ATEErr error = sGlyphsIterator->Next(fGlyphsIterator);
	if(error) Throw_ATE_Exception(error);
}

void IGlyphsIterator::Previous( )
{
	ATEErr error = sGlyphsIterator->Previous(fGlyphsIterator);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IKinsoku--
//////////////////////////////////////////////

IKinsoku::IKinsoku()
:fKinsoku(0)
{
	ATEErr error = sKinsoku->Initialize(&fKinsoku);
	if(error) Throw_ATE_Exception(error);
}

IKinsoku::IKinsoku(KinsokuRef kinsoku)
:fKinsoku(kinsoku)
{
}

IKinsoku::IKinsoku(const IKinsoku& src)
:fKinsoku(src.fKinsoku)
{
	sKinsoku->AddRef(fKinsoku);
}

IKinsoku::~IKinsoku()
{
	sKinsoku->Release(fKinsoku);
}

IKinsoku& IKinsoku::operator=(const IKinsoku& rhs)
{
	if (&rhs != this)
	{
		sKinsoku->Release(fKinsoku);
		fKinsoku = rhs.fKinsoku;
		sKinsoku->AddRef(fKinsoku);
	}
	return *this;
}

bool IKinsoku::operator==(const IKinsoku& rhs) const
{
	ATEBool8 ret = false;
	ATEErr error = sKinsoku->IsEqual(fKinsoku, rhs.fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsoku::operator!=(const IKinsoku& rhs) const
{
	return !(*this == rhs);
}

KinsokuRef IKinsoku::GetRef() const
{
	return fKinsoku;
}

bool IKinsoku::IsNull() const
{
	return sKinsoku->IsNull(fKinsoku);
}

ATETextDOM::Int32 IKinsoku::GetName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetName(fKinsoku, name, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsoku::GetNameSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetNameSize(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IKinsoku::SetName( const ATETextDOM::Unicode* name)
{
	ATEErr error = sKinsoku->SetName(fKinsoku, name);
	if(error) Throw_ATE_Exception(error);
}

bool IKinsoku::MatchesPredefinedResourceTag( ATE::KinsokuPredefinedTag tag) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->MatchesPredefinedResourceTag(fKinsoku, tag, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsoku::GetNoStartCharSet( ATETextDOM::Unicode* noStartCharSet, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetNoStartCharSet(fKinsoku, noStartCharSet, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsoku::GetNoStartCharSetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetNoStartCharSetSize(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IKinsoku::SetNoStartCharSet( const ATETextDOM::Unicode* noStartCharSet)
{
	ATEErr error = sKinsoku->SetNoStartCharSet(fKinsoku, noStartCharSet);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 IKinsoku::GetNoEndCharSet( ATETextDOM::Unicode* noEndCharSet, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetNoEndCharSet(fKinsoku, noEndCharSet, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsoku::GetNoEndCharSetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetNoEndCharSetSize(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IKinsoku::SetNoEndCharSet( const ATETextDOM::Unicode* noEndCharSet)
{
	ATEErr error = sKinsoku->SetNoEndCharSet(fKinsoku, noEndCharSet);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 IKinsoku::GetNoBreakCharSet( ATETextDOM::Unicode* noBreakCharSet, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetNoBreakCharSet(fKinsoku, noBreakCharSet, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsoku::GetNoBreakCharSetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetNoBreakCharSetSize(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IKinsoku::SetNoBreakCharSet( const ATETextDOM::Unicode* noBreakCharSet)
{
	ATEErr error = sKinsoku->SetNoBreakCharSet(fKinsoku, noBreakCharSet);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 IKinsoku::GetHangingCharSet( ATETextDOM::Unicode* hangingCharSet, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetHangingCharSet(fKinsoku, hangingCharSet, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsoku::GetHangingCharSetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsoku->GetHangingCharSetSize(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IKinsoku::SetHangingCharSet( const ATETextDOM::Unicode* hangingCharSet)
{
	ATEErr error = sKinsoku->SetHangingCharSet(fKinsoku, hangingCharSet);
	if(error) Throw_ATE_Exception(error);
}

bool IKinsoku::IsNoStartChar( ATETextDOM::Unicode character) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->IsNoStartChar(fKinsoku, character, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsoku::IsNoEndChar( ATETextDOM::Unicode character) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->IsNoEndChar(fKinsoku, character, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsoku::IsNoBreakChar( ATETextDOM::Unicode character) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->IsNoBreakChar(fKinsoku, character, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsoku::IsHangingChar( ATETextDOM::Unicode character) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->IsHangingChar(fKinsoku, character, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsoku::IsEquivalent( IKinsoku rhsKinsoku) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->IsEquivalent(fKinsoku, rhsKinsoku.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsoku::IsModified( ) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->IsModified(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsoku::IsPredefined( ) const
{
	ATEBool8 ret;
	ATEErr error = sKinsoku->IsPredefined(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IKinsoku IKinsoku::Duplicate( ) const
{
	KinsokuRef ret = 0;
	ATEErr error = sKinsoku->Duplicate(fKinsoku, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsoku(ret);
}

//////////////////////////////////////////////
// --IKinsokuSet--
//////////////////////////////////////////////

IKinsokuSet::IKinsokuSet()
:fKinsokuSet(0)
{
}

IKinsokuSet::IKinsokuSet(KinsokuSetRef kinsokuset)
:fKinsokuSet(kinsokuset)
{
}

IKinsokuSet::IKinsokuSet(const IKinsokuSet& src)
:fKinsokuSet(src.fKinsokuSet)
{
	sKinsokuSet->AddRef(fKinsokuSet);
}

IKinsokuSet::~IKinsokuSet()
{
	sKinsokuSet->Release(fKinsokuSet);
}

IKinsokuSet& IKinsokuSet::operator=(const IKinsokuSet& rhs)
{
	if (&rhs != this)
	{
		sKinsokuSet->Release(fKinsokuSet);
		fKinsokuSet = rhs.fKinsokuSet;
		sKinsokuSet->AddRef(fKinsokuSet);
	}
	return *this;
}

bool IKinsokuSet::operator==(const IKinsokuSet& rhs) const
{
	return fKinsokuSet == rhs.fKinsokuSet;
}

bool IKinsokuSet::operator!=(const IKinsokuSet& rhs) const
{
	return !(*this == rhs);
}

KinsokuSetRef IKinsokuSet::GetRef() const
{
	return fKinsokuSet;
}

bool IKinsokuSet::IsNull() const
{
	return sKinsokuSet->IsNull(fKinsokuSet);
}

ATETextDOM::Int32 IKinsokuSet::GetSize( )
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsokuSet->GetSize(fKinsokuSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IKinsoku IKinsokuSet::GetFirst( )
{
	KinsokuRef ret = 0;
	ATEErr error = sKinsokuSet->GetFirst(fKinsokuSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsoku(ret);
}

IKinsoku IKinsokuSet::GetLast( )
{
	KinsokuRef ret = 0;
	ATEErr error = sKinsokuSet->GetLast(fKinsokuSet, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsoku(ret);
}

IKinsoku IKinsokuSet::Item( ATETextDOM::Int32 nIndex) const
{
	KinsokuRef ret = 0;
	ATEErr error = sKinsokuSet->Item(fKinsokuSet, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return IKinsoku(ret);
}

ATETextDOM::Int32 IKinsokuSet::Find( IKinsoku kinsoku)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsokuSet->Find_ByKinsoku(fKinsokuSet, kinsoku.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsokuSet::Find( const ATETextDOM::Unicode* name)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsokuSet->Find_ByName(fKinsokuSet, name, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsokuSet::Find( KinsokuPredefinedTag tag)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsokuSet->Find_ByPredefinedKinsokuTag(fKinsokuSet, tag, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsokuSet::Remove( ATETextDOM::Int32 nIndex)
{
	ATEBool8 ret;
	ATEErr error = sKinsokuSet->Remove(fKinsokuSet, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IKinsokuSet::Add( IKinsoku kinsoku)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sKinsokuSet->Add(fKinsokuSet, kinsoku.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IKinsokuSet::Replace( ATETextDOM::Int32 nIndex, IKinsoku kinsoku)
{
	ATEBool8 ret;
	ATEErr error = sKinsokuSet->Replace(fKinsokuSet, nIndex, kinsoku.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IParaFeatures--
//////////////////////////////////////////////

IParaFeatures::IParaFeatures()
:fParaFeatures(0)
{
	ATEErr error = sParaFeatures->Initialize(&fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

IParaFeatures::IParaFeatures(ParaFeaturesRef parafeatures)
:fParaFeatures(parafeatures)
{
}

IParaFeatures::IParaFeatures(const IParaFeatures& src)
:fParaFeatures(src.fParaFeatures)
{
	sParaFeatures->AddRef(fParaFeatures);
}

IParaFeatures::~IParaFeatures()
{
	sParaFeatures->Release(fParaFeatures);
}

IParaFeatures& IParaFeatures::operator=(const IParaFeatures& rhs)
{
	if (&rhs != this)
	{
		sParaFeatures->Release(fParaFeatures);
		fParaFeatures = rhs.fParaFeatures;
		sParaFeatures->AddRef(fParaFeatures);
	}
	return *this;
}

bool IParaFeatures::operator==(const IParaFeatures& rhs) const
{
	return fParaFeatures == rhs.fParaFeatures;
}

bool IParaFeatures::operator!=(const IParaFeatures& rhs) const
{
	return !(*this == rhs);
}

ParaFeaturesRef IParaFeatures::GetRef() const
{
	return fParaFeatures;
}

bool IParaFeatures::IsNull() const
{
	return sParaFeatures->IsNull(fParaFeatures);
}

IParaFeatures IParaFeatures::Clone( ) const
{
	ParaFeaturesRef ret = 0;
	ATEErr error = sParaFeatures->Clone(fParaFeatures, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaFeatures(ret);
}

ParagraphJustification IParaFeatures::GetJustification( bool* isAssigned) const
{
	ParagraphJustification ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetJustification(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetFirstLineIndent( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetFirstLineIndent(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetStartIndent( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetStartIndent(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetEndIndent( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetEndIndent(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetSpaceBefore( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetSpaceBefore(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetSpaceAfter( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATEBool8 isAssignedRet;
	ATETextDOM::Float tempRet;
	ATEErr error = sParaFeatures->GetSpaceAfter(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool IParaFeatures::GetAutoHyphenate( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetAutoHyphenate(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 IParaFeatures::GetHyphenatedWordSize( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetHyphenatedWordSize(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 IParaFeatures::GetPreHyphenSize( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetPreHyphenSize(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 IParaFeatures::GetPostHyphenSize( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetPostHyphenSize(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 IParaFeatures::GetConsecutiveHyphenLimit( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetConsecutiveHyphenLimit(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetHyphenationZone( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetHyphenationZone(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool IParaFeatures::GetHyphenateCapitalized( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetHyphenateCapitalized(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetHyphenationPreference( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetHyphenationPreference(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetDesiredWordSpacing( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetDesiredWordSpacing(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetMaxWordSpacing( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetMaxWordSpacing(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetMinWordSpacing( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetMinWordSpacing(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetDesiredLetterSpacing( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetDesiredLetterSpacing(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetMaxLetterSpacing( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetMaxLetterSpacing(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetMinLetterSpacing( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetMinLetterSpacing(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetDesiredGlyphScaling( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetDesiredGlyphScaling(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetMaxGlyphScaling( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetMaxGlyphScaling(fParaFeatures, &isAssignedRet, &tempRet);
	if (isAssigned) *isAssigned = isAssignedRet;
	if(error) Throw_ATE_Exception(error);
	ret = tempRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetMinGlyphScaling( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetMinGlyphScaling(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

ParagraphJustification IParaFeatures::GetSingleWordJustification( bool* isAssigned) const
{
	ParagraphJustification ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetSingleWordJustification(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Real IParaFeatures::GetAutoLeadingPercentage( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetAutoLeadingPercentage(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

LeadingType IParaFeatures::GetLeadingType( bool* isAssigned) const
{
	LeadingType ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetLeadingType(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ITabStops IParaFeatures::GetTabStops( bool* isAssigned) const
{
	TabStopsRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetTabStops(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ITabStops(ret);
}

ATETextDOM::Real IParaFeatures::GetDefaultTabWidth( bool* isAssigned) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetDefaultTabWidth(fParaFeatures, &isAssignedRet, &tempRet);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	ret = tempRet;
	return ret;
}

bool IParaFeatures::GetHangingRoman( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetHangingRoman(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATETextDOM::Int32 IParaFeatures::GetAutoTCY( bool* isAssigned) const
{
	ATETextDOM::Int32 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetAutoTCY(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool IParaFeatures::GetBunriKinshi( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetBunriKinshi(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

BurasagariType IParaFeatures::GetBurasagariType( bool* isAssigned) const
{
	BurasagariType ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetBurasagariType(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

PreferredKinsokuOrder IParaFeatures::GetPreferredKinsokuOrder( bool* isAssigned) const
{
	PreferredKinsokuOrder ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetPreferredKinsokuOrder(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

bool IParaFeatures::GetKurikaeshiMojiShori( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetKurikaeshiMojiShori(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

IKinsoku IParaFeatures::GetKinsoku( bool* isAssigned) const
{
	KinsokuRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetKinsoku(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return IKinsoku(ret);
}

IMojiKumi IParaFeatures::GetMojiKumi( bool* isAssigned) const
{
	MojiKumiRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetMojiKumi(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return IMojiKumi(ret);
}

bool IParaFeatures::GetEveryLineComposer( bool* isAssigned) const
{
	ATEBool8 ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetEveryLineComposer(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ICharFeatures IParaFeatures::GetDefaultCharFeatures( bool* isAssigned) const
{
	CharFeaturesRef ret = 0;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetDefaultCharFeatures(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ICharFeatures(ret);
}

#if SLO_COMPLEXSCRIPT
ATE::ParagraphDirection IParaFeatures::GetParagraphDirection( bool* isAssigned) const
{
	ATE::ParagraphDirection ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetParagraphDirection(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATE::JustificationMethod IParaFeatures::GetJustificationMethod( bool* isAssigned) const
{
	ATE::JustificationMethod ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetJustificationMethod(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

ATE::KashidaWidth IParaFeatures::GetKashidaWidth( bool* isAssigned) const
{
	ATE::KashidaWidth ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetKashidaWidth(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}
#endif

ATE::ComposerEngine IParaFeatures::GetComposerEngine( bool* isAssigned) const
{
	ATE::ComposerEngine ret;
	ATEBool8 isAssignedRet;
	ATEErr error = sParaFeatures->GetComposerEngine(fParaFeatures, &isAssignedRet, &ret);
	if(error) Throw_ATE_Exception(error);
	if (isAssigned) *isAssigned = isAssignedRet;
	return ret;
}

void IParaFeatures::SetJustification( ParagraphJustification newVal)
{
	ATEErr error = sParaFeatures->SetJustification(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetFirstLineIndent( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetFirstLineIndent(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetStartIndent( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetStartIndent(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetEndIndent( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetEndIndent(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetSpaceBefore( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetSpaceBefore(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetSpaceAfter( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetSpaceAfter(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetAutoHyphenate( bool newVal)
{
	ATEErr error = sParaFeatures->SetAutoHyphenate(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetHyphenatedWordSize( ATETextDOM::Int32 newVal)
{
	ATEErr error = sParaFeatures->SetHyphenatedWordSize(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetPreHyphenSize( ATETextDOM::Int32 newVal)
{
	ATEErr error = sParaFeatures->SetPreHyphenSize(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetPostHyphenSize( ATETextDOM::Int32 newVal)
{
	ATEErr error = sParaFeatures->SetPostHyphenSize(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetConsecutiveHyphenLimit( ATETextDOM::Int32 newVal)
{
	ATEErr error = sParaFeatures->SetConsecutiveHyphenLimit(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetHyphenationZone( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetHyphenationZone(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetHyphenateCapitalized( bool newVal)
{
	ATEErr error = sParaFeatures->SetHyphenateCapitalized(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetHyphenationPreference( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetHyphenationPreference(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetDesiredWordSpacing( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetDesiredWordSpacing(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetMaxWordSpacing( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetMaxWordSpacing(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetMinWordSpacing( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetMinWordSpacing(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetDesiredLetterSpacing( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetDesiredLetterSpacing(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetMaxLetterSpacing( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetMaxLetterSpacing(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetMinLetterSpacing( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetMinLetterSpacing(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetDesiredGlyphScaling( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetDesiredGlyphScaling(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetMaxGlyphScaling( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetMaxGlyphScaling(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetMinGlyphScaling( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetMinGlyphScaling(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetSingleWordJustification( ParagraphJustification newVal)
{
	ATEErr error = sParaFeatures->SetSingleWordJustification(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetAutoLeadingPercentage( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetAutoLeadingPercentage(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetLeadingType( LeadingType newVal)
{
	ATEErr error = sParaFeatures->SetLeadingType(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetTabStops( ITabStops newVal)
{
	ATEErr error = sParaFeatures->SetTabStops(fParaFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetDefaultTabWidth( ATETextDOM::Real newVal)
{
	ATEErr error = sParaFeatures->SetDefaultTabWidth(fParaFeatures, static_cast<ATETextDOM::Float>(newVal));
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetHangingRoman( bool newVal)
{
	ATEErr error = sParaFeatures->SetHangingRoman(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetAutoTCY( ATETextDOM::Int32 newVal)
{
	ATEErr error = sParaFeatures->SetAutoTCY(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetBunriKinshi( bool newVal)
{
	ATEErr error = sParaFeatures->SetBunriKinshi(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetBurasagariType( BurasagariType newVal)
{
	ATEErr error = sParaFeatures->SetBurasagariType(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetPreferredKinsokuOrder( PreferredKinsokuOrder newVal)
{
	ATEErr error = sParaFeatures->SetPreferredKinsokuOrder(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetKurikaeshiMojiShori( bool newVal)
{
	ATEErr error = sParaFeatures->SetKurikaeshiMojiShori(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetKinsoku( IKinsoku newVal)
{
	ATEErr error = sParaFeatures->SetKinsoku(fParaFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetMojiKumi( IMojiKumi newVal)
{
	ATEErr error = sParaFeatures->SetMojiKumi(fParaFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetEveryLineComposer( bool newVal)
{
	ATEErr error = sParaFeatures->SetEveryLineComposer(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetDefaultCharFeatures( ICharFeatures newVal)
{
	ATEErr error = sParaFeatures->SetDefaultCharFeatures(fParaFeatures, newVal.GetRef());
	if(error) Throw_ATE_Exception(error);
}

#if SLO_COMPLEXSCRIPT
void IParaFeatures::SetParagraphDirection( ATE::ParagraphDirection newVal)
{
	ATEErr error = sParaFeatures->SetParagraphDirection(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetJustificationMethod( ATE::JustificationMethod newVal)
{
	ATEErr error = sParaFeatures->SetJustificationMethod(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::SetKashidaWidth( ATE::KashidaWidth newVal)
{
	ATEErr error = sParaFeatures->SetKashidaWidth(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}
#endif

void IParaFeatures::SetComposerEngine( ATE::ComposerEngine newVal)
{
	ATEErr error = sParaFeatures->SetComposerEngine(fParaFeatures, newVal);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearJustification( )
{
	ATEErr error = sParaFeatures->ClearJustification(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearFirstLineIndent( )
{
	ATEErr error = sParaFeatures->ClearFirstLineIndent(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearStartIndent( )
{
	ATEErr error = sParaFeatures->ClearStartIndent(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearEndIndent( )
{
	ATEErr error = sParaFeatures->ClearEndIndent(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearSpaceBefore( )
{
	ATEErr error = sParaFeatures->ClearSpaceBefore(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearSpaceAfter( )
{
	ATEErr error = sParaFeatures->ClearSpaceAfter(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearAutoHyphenate( )
{
	ATEErr error = sParaFeatures->ClearAutoHyphenate(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearHyphenatedWordSize( )
{
	ATEErr error = sParaFeatures->ClearHyphenatedWordSize(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearPreHyphenSize( )
{
	ATEErr error = sParaFeatures->ClearPreHyphenSize(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearPostHyphenSize( )
{
	ATEErr error = sParaFeatures->ClearPostHyphenSize(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearConsecutiveHyphenLimit( )
{
	ATEErr error = sParaFeatures->ClearConsecutiveHyphenLimit(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearHyphenationZone( )
{
	ATEErr error = sParaFeatures->ClearHyphenationZone(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearHyphenateCapitalized( )
{
	ATEErr error = sParaFeatures->ClearHyphenateCapitalized(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearHyphenationPreference( )
{
	ATEErr error = sParaFeatures->ClearHyphenationPreference(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearWordSpacing( )
{
	ATEErr error = sParaFeatures->ClearWordSpacing(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearLetterSpacing( )
{
	ATEErr error = sParaFeatures->ClearLetterSpacing(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearGlyphScaling( )
{
	ATEErr error = sParaFeatures->ClearGlyphScaling(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearSingleWordJustification( )
{
	ATEErr error = sParaFeatures->ClearSingleWordJustification(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearAutoLeadingPercentage( )
{
	ATEErr error = sParaFeatures->ClearAutoLeadingPercentage(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearLeadingType( )
{
	ATEErr error = sParaFeatures->ClearLeadingType(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearTabStops( )
{
	ATEErr error = sParaFeatures->ClearTabStops(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearHangingRoman( )
{
	ATEErr error = sParaFeatures->ClearHangingRoman(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearAutoTCY( )
{
	ATEErr error = sParaFeatures->ClearAutoTCY(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearBunriKinshi( )
{
	ATEErr error = sParaFeatures->ClearBunriKinshi(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearBurasagariType( )
{
	ATEErr error = sParaFeatures->ClearBurasagariType(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearPreferredKinsokuOrder( )
{
	ATEErr error = sParaFeatures->ClearPreferredKinsokuOrder(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearKurikaeshiMojiShori( )
{
	ATEErr error = sParaFeatures->ClearKurikaeshiMojiShori(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearKinsoku( )
{
	ATEErr error = sParaFeatures->ClearKinsoku(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearMojiKumi( )
{
	ATEErr error = sParaFeatures->ClearMojiKumi(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearEveryLineComposer( )
{
	ATEErr error = sParaFeatures->ClearEveryLineComposer(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearDefaultCharFeatures( )
{
	ATEErr error = sParaFeatures->ClearDefaultCharFeatures(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

#if SLO_COMPLEXSCRIPT
void IParaFeatures::ClearParagraphDirection( )
{
	ATEErr error = sParaFeatures->ClearParagraphDirection(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearJustificationMethod( )
{
	ATEErr error = sParaFeatures->ClearJustificationMethod(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

void IParaFeatures::ClearKashidaWidth( )
{
	ATEErr error = sParaFeatures->ClearKashidaWidth(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}
#endif

void IParaFeatures::ClearComposerEngine( )
{
	ATEErr error = sParaFeatures->ClearComposerEngine(fParaFeatures);
	if(error) Throw_ATE_Exception(error);
}

bool IParaFeatures::IntersectFeatures( IParaFeatures rhs)
{
	ATEBool8 ret;
	ATEErr error = sParaFeatures->IntersectFeatures(fParaFeatures, rhs.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaFeatures::ReplaceOrAddFeatures( IParaFeatures rhs)
{
	ATEBool8 ret;
	ATEErr error = sParaFeatures->ReplaceOrAddFeatures(fParaFeatures, rhs.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaFeatures::UnassignEachIfEqual( const IParaFeatures rhs)
{
	ATEBool8 ret;
	ATEErr error = sParaFeatures->UnassignEachIfEqual(fParaFeatures, rhs.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaFeatures::IsEachNotAssigned( ) const
{
	ATEBool8 ret;
	ATEErr error = sParaFeatures->IsEachNotAssigned(fParaFeatures, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaFeatures::IsEachAssigned( ) const
{
	ATEBool8 ret;
	ATEErr error = sParaFeatures->IsEachAssigned(fParaFeatures, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IParagraph--
//////////////////////////////////////////////

IParagraph::IParagraph()
:fParagraph(0)
{
}

IParagraph::IParagraph(ParagraphRef paragraph)
:fParagraph(paragraph)
{
}

IParagraph::IParagraph(const IParagraph& src)
:fParagraph(src.fParagraph)
{
	sParagraph->AddRef(fParagraph);
}

IParagraph::~IParagraph()
{
	sParagraph->Release(fParagraph);
}

IParagraph& IParagraph::operator=(const IParagraph& rhs)
{
	if (&rhs != this)
	{
		sParagraph->Release(fParagraph);
		fParagraph = rhs.fParagraph;
		sParagraph->AddRef(fParagraph);
	}
	return *this;
}

bool IParagraph::operator==(const IParagraph& rhs) const
{
	return fParagraph == rhs.fParagraph;
}

bool IParagraph::operator!=(const IParagraph& rhs) const
{
	return !(*this == rhs);
}

ParagraphRef IParagraph::GetRef() const
{
	return fParagraph;
}

bool IParagraph::IsNull() const
{
	return sParagraph->IsNull(fParagraph);
}

ATETextDOM::Int32 IParagraph::GetLength( )
{
	ATETextDOM::Int32 ret;
	ATEErr error = sParagraph->GetLength(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IStory IParagraph::GetStory( )
{
	StoryRef ret = 0;
	ATEErr error = sParagraph->GetStory(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

ITextRange IParagraph::GetTextRange( )
{
	TextRangeRef ret = 0;
	ATEErr error = sParagraph->GetTextRange(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

ITextRanges IParagraph::GetTextRanges( )
{
	TextRangesRef ret = 0;
	ATEErr error = sParagraph->GetTextRanges(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

ITextRanges IParagraph::GetTextSelection( )
{
	TextRangesRef ret = 0;
	ATEErr error = sParagraph->GetTextSelection(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

IWordsIterator IParagraph::GetWordsIterator( )
{
	WordsIteratorRef ret = 0;
	ATEErr error = sParagraph->GetWordsIterator(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return IWordsIterator(ret);
}

IParagraph IParagraph::GetNext( )
{
	ParagraphRef ret = 0;
	ATEErr error = sParagraph->GetNext(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraph(ret);
}

IParagraph IParagraph::GetPrev( )
{
	ParagraphRef ret = 0;
	ATEErr error = sParagraph->GetPrev(fParagraph, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraph(ret);
}

ATETextDOM::ATETextDomErr IParagraph::GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength)
{
	ATETextDOM::ATETextDomErr ret;
	ATEErr error = sParagraph->GetContents_AsUnicode(fParagraph, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::ATETextDomErr IParagraph::GetContents( char* text, ATETextDOM::Int32 maxLength)
{
	ATETextDOM::ATETextDomErr ret;
	ATEErr error = sParagraph->GetContents_AsChar(fParagraph, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IParagraphsIterator--
//////////////////////////////////////////////

IParagraphsIterator::IParagraphsIterator()
:fParagraphsIterator(0)
{
}

IParagraphsIterator::IParagraphsIterator(ParagraphsIteratorRef paragraphsiterator)
:fParagraphsIterator(paragraphsiterator)
{
}

IParagraphsIterator::IParagraphsIterator(const IParagraphsIterator& src)
:fParagraphsIterator(src.fParagraphsIterator)
{
	sParagraphsIterator->AddRef(fParagraphsIterator);
}

IParagraphsIterator::~IParagraphsIterator()
{
	sParagraphsIterator->Release(fParagraphsIterator);
}

IParagraphsIterator& IParagraphsIterator::operator=(const IParagraphsIterator& rhs)
{
	if (&rhs != this)
	{
		sParagraphsIterator->Release(fParagraphsIterator);
		fParagraphsIterator = rhs.fParagraphsIterator;
		sParagraphsIterator->AddRef(fParagraphsIterator);
	}
	return *this;
}

bool IParagraphsIterator::operator==(const IParagraphsIterator& rhs) const
{
	return fParagraphsIterator == rhs.fParagraphsIterator;
}

bool IParagraphsIterator::operator!=(const IParagraphsIterator& rhs) const
{
	return !(*this == rhs);
}

ParagraphsIteratorRef IParagraphsIterator::GetRef() const
{
	return fParagraphsIterator;
}

bool IParagraphsIterator::IsNull() const
{
	return sParagraphsIterator->IsNull(fParagraphsIterator);
}

IParagraphsIterator::IParagraphsIterator( ITextRanges ranges, Direction direction)
{
	ATEErr error = sParagraphsIterator->Initialize(ranges.GetRef(), direction, &fParagraphsIterator);
	if(error) Throw_ATE_Exception(error);
}

bool IParagraphsIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sParagraphsIterator->IsDone(fParagraphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParagraphsIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sParagraphsIterator->IsNotDone(fParagraphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParagraphsIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sParagraphsIterator->IsEmpty(fParagraphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IParagraphsIterator::MoveToFirst( )
{
	ATEErr error = sParagraphsIterator->MoveToFirst(fParagraphsIterator);
	if(error) Throw_ATE_Exception(error);
}

void IParagraphsIterator::MoveToLast( )
{
	ATEErr error = sParagraphsIterator->MoveToLast(fParagraphsIterator);
	if(error) Throw_ATE_Exception(error);
}

void IParagraphsIterator::Next( )
{
	ATEErr error = sParagraphsIterator->Next(fParagraphsIterator);
	if(error) Throw_ATE_Exception(error);
}

IParagraph IParagraphsIterator::Item( )
{
	ParagraphRef ret = 0;
	ATEErr error = sParagraphsIterator->Item(fParagraphsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraph(ret);
}

//////////////////////////////////////////////
// --IParaInspector--
//////////////////////////////////////////////

IParaInspector::IParaInspector()
:fParaInspector(0)
{
	ATEErr error = sParaInspector->Initialize(&fParaInspector);
	if(error) Throw_ATE_Exception(error);
}

IParaInspector::IParaInspector(ParaInspectorRef parainspector)
:fParaInspector(parainspector)
{
}

IParaInspector::IParaInspector(const IParaInspector& src)
:fParaInspector(src.fParaInspector)
{
	sParaInspector->AddRef(fParaInspector);
}

IParaInspector::~IParaInspector()
{
	sParaInspector->Release(fParaInspector);
}

IParaInspector& IParaInspector::operator=(const IParaInspector& rhs)
{
	if (&rhs != this)
	{
		sParaInspector->Release(fParaInspector);
		fParaInspector = rhs.fParaInspector;
		sParaInspector->AddRef(fParaInspector);
	}
	return *this;
}

bool IParaInspector::operator==(const IParaInspector& rhs) const
{
	return fParaInspector == rhs.fParaInspector;
}

bool IParaInspector::operator!=(const IParaInspector& rhs) const
{
	return !(*this == rhs);
}

ParaInspectorRef IParaInspector::GetRef() const
{
	return fParaInspector;
}

bool IParaInspector::IsNull() const
{
	return sParaInspector->IsNull(fParaInspector);
}

IArrayParagraphJustification IParaInspector::GetJustification( ) const
{
	ArrayParagraphJustificationRef ret = 0;
	ATEErr error = sParaInspector->GetJustification(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayParagraphJustification(ret);
}

IArrayReal IParaInspector::GetFirstLineIndent( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetFirstLineIndent(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetStartIndent( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetStartIndent(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetEndIndent( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetEndIndent(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetSpaceBefore( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetSpaceBefore(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetSpaceAfter( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetSpaceAfter(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool IParaInspector::GetAutoHyphenate( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sParaInspector->GetAutoHyphenate(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayInteger IParaInspector::GetHyphenatedWordSize( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sParaInspector->GetHyphenatedWordSize(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayInteger IParaInspector::GetPreHyphenSize( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sParaInspector->GetPreHyphenSize(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayInteger IParaInspector::GetPostHyphenSize( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sParaInspector->GetPostHyphenSize(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayInteger IParaInspector::GetConsecutiveHyphenLimit( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sParaInspector->GetConsecutiveHyphenLimit(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayReal IParaInspector::GetHyphenationZone( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetHyphenationZone(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool IParaInspector::GetHyphenateCapitalized( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sParaInspector->GetHyphenateCapitalized(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayReal IParaInspector::GetHyphenationPreference( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetHyphenationPreference(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetDesiredWordSpacing( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetDesiredWordSpacing(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetMaxWordSpacing( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetMaxWordSpacing(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetMinWordSpacing( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetMinWordSpacing(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetDesiredLetterSpacing( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetDesiredLetterSpacing(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetMaxLetterSpacing( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetMaxLetterSpacing(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetMinLetterSpacing( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetMinLetterSpacing(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetDesiredGlyphScaling( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetDesiredGlyphScaling(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetMaxGlyphScaling( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetMaxGlyphScaling(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayReal IParaInspector::GetMinGlyphScaling( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetMinGlyphScaling(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayParagraphJustification IParaInspector::GetSingleWordJustification( ) const
{
	ArrayParagraphJustificationRef ret = 0;
	ATEErr error = sParaInspector->GetSingleWordJustification(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayParagraphJustification(ret);
}

IArrayReal IParaInspector::GetAutoLeadingPercentage( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetAutoLeadingPercentage(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayLeadingType IParaInspector::GetLeadingType( ) const
{
	ArrayLeadingTypeRef ret = 0;
	ATEErr error = sParaInspector->GetLeadingType(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayLeadingType(ret);
}

IArrayTabStopsRef IParaInspector::GetTabStops( ) const
{
	ArrayTabStopsRefRef ret = 0;
	ATEErr error = sParaInspector->GetTabStops(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayTabStopsRef(ret);
}

IArrayReal IParaInspector::GetDefaultTabWidth( ) const
{
	ArrayRealRef ret = 0;
	ATEErr error = sParaInspector->GetDefaultTabWidth(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayReal(ret);
}

IArrayBool IParaInspector::GetHangingRoman( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sParaInspector->GetHangingRoman(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayInteger IParaInspector::GetAutoTCY( ) const
{
	ArrayIntegerRef ret = 0;
	ATEErr error = sParaInspector->GetAutoTCY(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayInteger(ret);
}

IArrayBool IParaInspector::GetBunriKinshi( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sParaInspector->GetBunriKinshi(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayBurasagariType IParaInspector::GetBurasagariType( ) const
{
	ArrayBurasagariTypeRef ret = 0;
	ATEErr error = sParaInspector->GetBurasagariType(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBurasagariType(ret);
}

IArrayPreferredKinsokuOrder IParaInspector::GetPreferredKinsokuOrder( ) const
{
	ArrayPreferredKinsokuOrderRef ret = 0;
	ATEErr error = sParaInspector->GetPreferredKinsokuOrder(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayPreferredKinsokuOrder(ret);
}

IArrayBool IParaInspector::GetKurikaeshiMojiShori( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sParaInspector->GetKurikaeshiMojiShori(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

IArrayKinsokuRef IParaInspector::GetKinsoku( ) const
{
	ArrayKinsokuRefRef ret = 0;
	ATEErr error = sParaInspector->GetKinsoku(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayKinsokuRef(ret);
}

IArrayMojiKumiRef IParaInspector::GetMojiKumi( ) const
{
	ArrayMojiKumiRefRef ret = 0;
	ATEErr error = sParaInspector->GetMojiKumi(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayMojiKumiRef(ret);
}

IArrayBool IParaInspector::GetEveryLineComposer( ) const
{
	ArrayBoolRef ret = 0;
	ATEErr error = sParaInspector->GetEveryLineComposer(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayBool(ret);
}

#if SLO_COMPLEXSCRIPT
IArrayParagraphDirection IParaInspector::GetParagraphDirection( ) const
{
	ArrayParagraphDirectionRef ret = 0;
	ATEErr error = sParaInspector->GetParagraphDirection(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayParagraphDirection(ret);
}

IArrayJustificationMethod IParaInspector::GetJustificationMethod( ) const
{
	ArrayJustificationMethodRef ret = 0;
	ATEErr error = sParaInspector->GetJustificationMethod(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayJustificationMethod(ret);
}

IArrayKashidaWidth IParaInspector::GetKashidaWidth( ) const
{
	ArrayKashidaWidthRef ret = 0;
	ATEErr error = sParaInspector->GetKashidaWidth(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayKashidaWidth(ret);
}
#endif

IArrayComposerEngine IParaInspector::GetComposerEngine( ) const
{
	ArrayComposerEngineRef ret = 0;
	ATEErr error = sParaInspector->GetComposerEngine(fParaInspector, &ret);
	if(error) Throw_ATE_Exception(error);
	return IArrayComposerEngine(ret);
}

//////////////////////////////////////////////
// --IParaStyle--
//////////////////////////////////////////////

IParaStyle::IParaStyle()
:fParaStyle(0)
{
}

IParaStyle::IParaStyle(ParaStyleRef parastyle)
:fParaStyle(parastyle)
{
}

IParaStyle::IParaStyle(const IParaStyle& src)
:fParaStyle(src.fParaStyle)
{
	sParaStyle->AddRef(fParaStyle);
}

IParaStyle::~IParaStyle()
{
	sParaStyle->Release(fParaStyle);
}

IParaStyle& IParaStyle::operator=(const IParaStyle& rhs)
{
	if (&rhs != this)
	{
		sParaStyle->Release(fParaStyle);
		fParaStyle = rhs.fParaStyle;
		sParaStyle->AddRef(fParaStyle);
	}
	return *this;
}

bool IParaStyle::operator==(const IParaStyle& rhs) const
{
	ATEBool8 ret = false;
	ATEErr error = sParaStyle->IsEqual(fParaStyle, rhs.fParaStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaStyle::operator!=(const IParaStyle& rhs) const
{
	return !(*this == rhs);
}

ParaStyleRef IParaStyle::GetRef() const
{
	return fParaStyle;
}

bool IParaStyle::IsNull() const
{
	return sParaStyle->IsNull(fParaStyle);
}

ATETextDOM::Int32 IParaStyle::GetName( ATETextDOM::Unicode* pName, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sParaStyle->GetName(fParaStyle, pName, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaStyle::SetName( const ATETextDOM::Unicode* pName)
{
	ATEBool8 ret;
	ATEErr error = sParaStyle->SetName(fParaStyle, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IParaStyle IParaStyle::GetParent( ) const
{
	ParaStyleRef ret = 0;
	ATEErr error = sParaStyle->GetParent(fParaStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyle(ret);
}

bool IParaStyle::SetParent( const IParaStyle pStyle)
{
	ATEBool8 ret;
	ATEErr error = sParaStyle->SetParent(fParaStyle, pStyle.GetRef(), &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaStyle::HasParent( ) const
{
	ATEBool8 ret;
	ATEErr error = sParaStyle->HasParent(fParaStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IParaFeatures IParaStyle::GetFeatures( ) const
{
	ParaFeaturesRef ret = 0;
	ATEErr error = sParaStyle->GetFeatures(fParaStyle, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaFeatures(ret);
}

void IParaStyle::SetFeatures( IParaFeatures pFeatures)
{
	ATEErr error = sParaStyle->SetFeatures(fParaStyle, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IParaStyle::ReplaceOrAddFeatures( IParaFeatures pFeatures)
{
	ATEErr error = sParaStyle->ReplaceOrAddFeatures(fParaStyle, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IParaStyles--
//////////////////////////////////////////////

IParaStyles::IParaStyles()
:fParaStyles(0)
{
}

IParaStyles::IParaStyles(ParaStylesRef parastyles)
:fParaStyles(parastyles)
{
}

IParaStyles::IParaStyles(const IParaStyles& src)
:fParaStyles(src.fParaStyles)
{
	sParaStyles->AddRef(fParaStyles);
}

IParaStyles::~IParaStyles()
{
	sParaStyles->Release(fParaStyles);
}

IParaStyles& IParaStyles::operator=(const IParaStyles& rhs)
{
	if (&rhs != this)
	{
		sParaStyles->Release(fParaStyles);
		fParaStyles = rhs.fParaStyles;
		sParaStyles->AddRef(fParaStyles);
	}
	return *this;
}

bool IParaStyles::operator==(const IParaStyles& rhs) const
{
	return fParaStyles == rhs.fParaStyles;
}

bool IParaStyles::operator!=(const IParaStyles& rhs) const
{
	return !(*this == rhs);
}

ParaStylesRef IParaStyles::GetRef() const
{
	return fParaStyles;
}

bool IParaStyles::IsNull() const
{
	return sParaStyles->IsNull(fParaStyles);
}

bool IParaStyles::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sParaStyles->IsEmpty(fParaStyles, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IParaStyles::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sParaStyles->GetSize(fParaStyles, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IParaStyles::ShowAllStyles( ) const
{
	ATEErr error = sParaStyles->ShowAllStyles(fParaStyles);
	if(error) Throw_ATE_Exception(error);
}

void IParaStyles::ShowOnlyUnreferencedStyles( ) const
{
	ATEErr error = sParaStyles->ShowOnlyUnreferencedStyles(fParaStyles);
	if(error) Throw_ATE_Exception(error);
}

void IParaStyles::ShowOnlyStylesReferencedIn( ITextRange pRange) const
{
	ATEErr error = sParaStyles->ShowOnlyStylesReferencedIn(fParaStyles, pRange.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IParaStyles::MoveStyleTo( IParaStyle pStyle, ATETextDOM::Int32 position)
{
	ATEErr error = sParaStyles->MoveStyleTo(fParaStyles, pStyle.GetRef(), position);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IParaStylesIterator--
//////////////////////////////////////////////

IParaStylesIterator::IParaStylesIterator()
:fParaStylesIterator(0)
{
}

IParaStylesIterator::IParaStylesIterator(ParaStylesIteratorRef parastylesiterator)
:fParaStylesIterator(parastylesiterator)
{
}

IParaStylesIterator::IParaStylesIterator(const IParaStylesIterator& src)
:fParaStylesIterator(src.fParaStylesIterator)
{
	sParaStylesIterator->AddRef(fParaStylesIterator);
}

IParaStylesIterator::~IParaStylesIterator()
{
	sParaStylesIterator->Release(fParaStylesIterator);
}

IParaStylesIterator& IParaStylesIterator::operator=(const IParaStylesIterator& rhs)
{
	if (&rhs != this)
	{
		sParaStylesIterator->Release(fParaStylesIterator);
		fParaStylesIterator = rhs.fParaStylesIterator;
		sParaStylesIterator->AddRef(fParaStylesIterator);
	}
	return *this;
}

bool IParaStylesIterator::operator==(const IParaStylesIterator& rhs) const
{
	return fParaStylesIterator == rhs.fParaStylesIterator;
}

bool IParaStylesIterator::operator!=(const IParaStylesIterator& rhs) const
{
	return !(*this == rhs);
}

ParaStylesIteratorRef IParaStylesIterator::GetRef() const
{
	return fParaStylesIterator;
}

bool IParaStylesIterator::IsNull() const
{
	return sParaStylesIterator->IsNull(fParaStylesIterator);
}

IParaStylesIterator::IParaStylesIterator( IParaStyles paraStyles, Direction direction)
{
	ATEErr error = sParaStylesIterator->Initialize(paraStyles.GetRef(), direction, &fParaStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

bool IParaStylesIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sParaStylesIterator->IsNotDone(fParaStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaStylesIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sParaStylesIterator->IsDone(fParaStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IParaStylesIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sParaStylesIterator->IsEmpty(fParaStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IParaStylesIterator::MoveToFirst( )
{
	ATEErr error = sParaStylesIterator->MoveToFirst(fParaStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

void IParaStylesIterator::MoveToLast( )
{
	ATEErr error = sParaStylesIterator->MoveToLast(fParaStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

void IParaStylesIterator::Next( )
{
	ATEErr error = sParaStylesIterator->Next(fParaStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

void IParaStylesIterator::Previous( )
{
	ATEErr error = sParaStylesIterator->Previous(fParaStylesIterator);
	if(error) Throw_ATE_Exception(error);
}

IParaStyle IParaStylesIterator::Item( ) const
{
	ParaStyleRef ret = 0;
	ATEErr error = sParaStylesIterator->Item(fParaStylesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyle(ret);
}

//////////////////////////////////////////////
// --ISpell--
//////////////////////////////////////////////

ISpell::ISpell()
:fSpell(0)
{
}

ISpell::ISpell(SpellRef spell)
:fSpell(spell)
{
}

ISpell::ISpell(const ISpell& src)
:fSpell(src.fSpell)
{
	sSpell->AddRef(fSpell);
}

ISpell::~ISpell()
{
	sSpell->Release(fSpell);
}

ISpell& ISpell::operator=(const ISpell& rhs)
{
	if (&rhs != this)
	{
		sSpell->Release(fSpell);
		fSpell = rhs.fSpell;
		sSpell->AddRef(fSpell);
	}
	return *this;
}

bool ISpell::operator==(const ISpell& rhs) const
{
	return fSpell == rhs.fSpell;
}

bool ISpell::operator!=(const ISpell& rhs) const
{
	return !(*this == rhs);
}

SpellRef ISpell::GetRef() const
{
	return fSpell;
}

bool ISpell::IsNull() const
{
	return sSpell->IsNull(fSpell);
}

void ISpell::Initialize( )
{
	ATEErr error = sSpell->Initialize(fSpell);
	if(error) Throw_ATE_Exception(error);
}

bool ISpell::IsInitialized( )
{
	ATEBool8 ret;
	ATEErr error = sSpell->IsInitialized(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ISpell::GetIgnoreWordsInAllUppercase( ) const
{
	ATEBool8 ret;
	ATEErr error = sSpell->GetIgnoreWordsInAllUppercase(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ISpell::GetIgnoreWordsWithNumbers( ) const
{
	ATEBool8 ret;
	ATEErr error = sSpell->GetIgnoreWordsWithNumbers(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ISpell::GetIgnoreRomanNumerals( ) const
{
	ATEBool8 ret;
	ATEErr error = sSpell->GetIgnoreRomanNumerals(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ISpell::GetIgnoreRepeatedWords( ) const
{
	ATEBool8 ret;
	ATEErr error = sSpell->GetIgnoreRepeatedWords(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ISpell::GetIgnoreUncapitalizedStartOfSentence( ) const
{
	ATEBool8 ret;
	ATEErr error = sSpell->GetIgnoreUncapitalizedStartOfSentence(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

#if SLO_COMPLEXSCRIPT
bool ISpell::GetStrictYeh( ) const
{
	ATEBool8 ret;
	ATEErr error = sSpell->GetStrictYeh(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ISpell::GetStrictAlef( ) const
{
	ATEBool8 ret;
	ATEErr error = sSpell->GetStrictAlef(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}
#endif

void ISpell::SetIgnoreWordsInAllUppercase( bool newValue)
{
	ATEErr error = sSpell->SetIgnoreWordsInAllUppercase(fSpell, newValue);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::SetIgnoreWordsWithNumbers( bool newValue)
{
	ATEErr error = sSpell->SetIgnoreWordsWithNumbers(fSpell, newValue);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::SetIgnoreRomanNumerals( bool newValue)
{
	ATEErr error = sSpell->SetIgnoreRomanNumerals(fSpell, newValue);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::SetIgnoreRepeatedWords( bool newValue)
{
	ATEErr error = sSpell->SetIgnoreRepeatedWords(fSpell, newValue);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::SetIgnoreUncapitalizedStartOfSentence( bool newValue)
{
	ATEErr error = sSpell->SetIgnoreUncapitalizedStartOfSentence(fSpell, newValue);
	if(error) Throw_ATE_Exception(error);
}

#if SLO_COMPLEXSCRIPT
void ISpell::SetStrictYeh( bool newValue)
{
	ATEErr error = sSpell->SetStrictYeh(fSpell, newValue);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::SetStrictAlef( bool newValue)
{
	ATEErr error = sSpell->SetStrictAlef(fSpell, newValue);
	if(error) Throw_ATE_Exception(error);
}
#endif

SearchScope ISpell::GetSearchScope( ) const
{
	SearchScope ret;
	ATEErr error = sSpell->GetSearchScope(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ISpell::SetSearchScope( SearchScope searchScope)
{
	ATEErr error = sSpell->SetSearchScope(fSpell, searchScope);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::SetSearchRange( const ITextRange& pRange, const bool resetEndOfSentence, const bool resetCurPos)
{
	ATEErr error = sSpell->SetSearchRange(fSpell, pRange.GetRef(), resetEndOfSentence, resetCurPos);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::Reset( )
{
	ATEErr error = sSpell->Reset(fSpell);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::ResumeFrom( const ATETextDOM::Int32 resumePoint)
{
	ATEErr error = sSpell->ResumeFrom(fSpell, resumePoint);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::ResumeFromInsertionPoint( )
{
	ATEErr error = sSpell->ResumeFromInsertionPoint(fSpell);
	if(error) Throw_ATE_Exception(error);
}

bool ISpell::FindOneMisspelledWord( SpellCheckingResult* pResult, ITextRange pRange, Language* pLanguage)
{
	ATEBool8 ret;
	ATEErr error = sSpell->FindOneMisspelledWord(fSpell, pResult, pRange.GetRef(), pLanguage, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ISpell::GetWordListSize( )
{
	ATETextDOM::Int32 ret;
	ATEErr error = sSpell->GetWordListSize(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ISpell::GetWordListContents( ATETextDOM::Unicode*   pWordListBuffer, ATETextDOM::Int32    sizeOfBuffer, ATETextDOM::Int32*   pNumberOfWords)
{
	ATEErr error = sSpell->GetWordListContents(fSpell, pWordListBuffer, sizeOfBuffer, pNumberOfWords);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::Replace( ITextRange pRange, const ATETextDOM::Unicode* pCorrection)
{
	ATEErr error = sSpell->Replace(fSpell, pRange.GetRef(), pCorrection);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::AddSelectedToReplaceAllDict( const ATETextDOM::Unicode* pCorrection)
{
	ATEErr error = sSpell->AddSelectedToReplaceAllDict(fSpell, pCorrection);
	if(error) Throw_ATE_Exception(error);
}

bool ISpell::DoReplaceAll( )
{
	ATEBool8 ret;
	ATEErr error = sSpell->DoReplaceAll(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ISpell::GetPreReplaceAllSettings( ATETextDOM::Int32* pCurrentPoint, bool* pFoundSentenceEnd) const
{
	ATEBool8 foundSentenceEndRet;
	ATEErr error = sSpell->GetPreReplaceAllSettings(fSpell, pCurrentPoint, &foundSentenceEndRet);
	if(error) Throw_ATE_Exception(error);
	if (pFoundSentenceEnd) *pFoundSentenceEnd = foundSentenceEndRet;
}

bool ISpell::FindReplaceAllWord( ITextRange pRange, const bool firstTimeInThisObject)
{
	ATEBool8 ret;
	ATEErr error = sSpell->FindReplaceAllWord(fSpell, pRange.GetRef(), firstTimeInThisObject, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ISpell::RestorePreReplaceAllSettings( const ATETextDOM::Int32 currentPoint, const bool foundSentenceEnd)
{
	ATEErr error = sSpell->RestorePreReplaceAllSettings(fSpell, currentPoint, foundSentenceEnd);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::ClearPairDictionary( )
{
	ATEErr error = sSpell->ClearPairDictionary(fSpell);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::AddSelectedToUserDict( )
{
	ATEErr error = sSpell->AddSelectedToUserDict(fSpell);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::GetUserDictionaryContents( )
{
	ATEErr error = sSpell->GetUserDictionaryContents(fSpell);
	if(error) Throw_ATE_Exception(error);
}

bool ISpell::AddToUserDictionary( const ATETextDOM::Unicode* pWord)
{
	ATEBool8 ret;
	ATEErr error = sSpell->AddToUserDictionary(fSpell, pWord, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ISpell::DeleteFromUserDictionary( const ATETextDOM::Unicode* pWord)
{
	ATEErr error = sSpell->DeleteFromUserDictionary(fSpell, pWord);
	if(error) Throw_ATE_Exception(error);
}

bool ISpell::WordExistsInUserDictionary( const ATETextDOM::Unicode* pWord)
{
	ATEBool8 ret;
	ATEErr error = sSpell->WordExistsInUserDictionary(fSpell, pWord, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ISpell::AddSelectedToIgnoreList( )
{
	ATEErr error = sSpell->AddSelectedToIgnoreList(fSpell);
	if(error) Throw_ATE_Exception(error);
}

void ISpell::ClearIgnoreList( )
{
	ATEErr error = sSpell->ClearIgnoreList(fSpell);
	if(error) Throw_ATE_Exception(error);
}

Language ISpell::GetLanguageOfLastMissingDictionary( )
{
	Language ret;
	ATEErr error = sSpell->GetLanguageOfLastMissingDictionary(fSpell, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ISpell::GetSpellingDictionaryPath(ATETextDOM::Unicode* path)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sSpell->GetSpellingDictionaryPath(fSpell, path, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --IStories--
//////////////////////////////////////////////

IStories::IStories()
:fStories(0)
{
}

IStories::IStories(StoriesRef stories)
:fStories(stories)
{
}

IStories::IStories(const IStories& src)
:fStories(src.fStories)
{
	sStories->AddRef(fStories);
}

IStories::~IStories()
{
	sStories->Release(fStories);
}

IStories& IStories::operator=(const IStories& rhs)
{
	if (&rhs != this)
	{
		sStories->Release(fStories);
		fStories = rhs.fStories;
		sStories->AddRef(fStories);
	}
	return *this;
}

bool IStories::operator==(const IStories& rhs) const
{
	return fStories == rhs.fStories;
}

bool IStories::operator!=(const IStories& rhs) const
{
	return !(*this == rhs);
}

StoriesRef IStories::GetRef() const
{
	return fStories;
}

bool IStories::IsNull() const
{
	return sStories->IsNull(fStories);
}

ATETextDOM::Int32 IStories::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sStories->GetSize(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IStory IStories::GetFirst( )
{
	StoryRef ret = 0;
	ATEErr error = sStories->GetFirst(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

IStory IStories::GetLast( )
{
	StoryRef ret = 0;
	ATEErr error = sStories->GetLast(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

bool IStories::HasFocus( ) const
{
	ATEBool8 ret;
	ATEErr error = sStories->HasFocus(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IStory IStories::GetFocus( ) const
{
	StoryRef ret = 0;
	ATEErr error = sStories->GetFocus(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

void IStories::SetFocus( const IStory& story)
{
	ATEErr error = sStories->SetFocus(fStories, story.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void IStories::LoseFocus( )
{
	ATEErr error = sStories->LoseFocus(fStories);
	if(error) Throw_ATE_Exception(error);
}

ITextRanges IStories::GetTextRanges( ) const
{
	TextRangesRef ret = 0;
	ATEErr error = sStories->GetTextRanges(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

ITextRanges IStories::GetTextSelection( ) const
{
	TextRangesRef ret = 0;
	ATEErr error = sStories->GetTextSelection(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

IParagraphsIterator IStories::GetParagraphsIterator( ) const
{
	ParagraphsIteratorRef ret = 0;
	ATEErr error = sStories->GetParagraphsIterator(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraphsIterator(ret);
}

IWordsIterator IStories::GetWordsIterator( ) const
{
	WordsIteratorRef ret = 0;
	ATEErr error = sStories->GetWordsIterator(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return IWordsIterator(ret);
}

ITextRunsIterator IStories::GetTextRunsIterator( ) const
{
	TextRunsIteratorRef ret = 0;
	ATEErr error = sStories->GetTextRunsIterator(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRunsIterator(ret);
}

IDocumentTextResources IStories::GetDocumentTextResources( ) const
{
	DocumentTextResourcesRef ret = 0;
	ATEErr error = sStories->GetDocumentTextResources(fStories, &ret);
	if(error) Throw_ATE_Exception(error);
	return IDocumentTextResources(ret);
}

IStory IStories::Item( ATETextDOM::Int32 nIndex) const
{
	StoryRef ret = 0;
	ATEErr error = sStories->Item(fStories, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

void IStories::SuspendReflow( )
{
	ATEErr error = sStories->SuspendReflow(fStories);
	if(error) Throw_ATE_Exception(error);
}

void IStories::ResumeReflow( )
{
	ATEErr error = sStories->ResumeReflow(fStories);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IStory--
//////////////////////////////////////////////

IStory::IStory()
:fStory(0)
{
}

IStory::IStory(StoryRef story)
:fStory(story)
{
}

IStory::IStory(const IStory& src)
:fStory(src.fStory)
{
	sStory->AddRef(fStory);
}

IStory::~IStory()
{
	sStory->Release(fStory);
}

IStory& IStory::operator=(const IStory& rhs)
{
	if (&rhs != this)
	{
		sStory->Release(fStory);
		fStory = rhs.fStory;
		sStory->AddRef(fStory);
	}
	return *this;
}

bool IStory::operator==(const IStory& rhs) const
{
	ATEBool8 ret = false;
	ATEErr error = sStory->IsEqual(fStory, rhs.fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IStory::operator!=(const IStory& rhs) const
{
	return !(*this == rhs);
}

StoryRef IStory::GetRef() const
{
	return fStory;
}

bool IStory::IsNull() const
{
	return sStory->IsNull(fStory);
}

ATETextDOM::Int32 IStory::GetIndex( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sStory->GetIndex(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IStory::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sStory->GetSize(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IStories IStory::GetStories( ) const
{
	StoriesRef ret = 0;
	ATEErr error = sStory->GetStories(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStories(ret);
}

ITextRange IStory::GetTextRange( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sStory->GetTextRange_ForThisStory(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

ITextRanges IStory::GetTextSelection( ) const
{
	TextRangesRef ret = 0;
	ATEErr error = sStory->GetTextSelection(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

IParagraphsIterator IStory::GetParagraphsIterator( ) const
{
	ParagraphsIteratorRef ret = 0;
	ATEErr error = sStory->GetParagraphsIterator(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraphsIterator(ret);
}

IWordsIterator IStory::GetWordsIterator( ) const
{
	WordsIteratorRef ret = 0;
	ATEErr error = sStory->GetWordsIterator(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return IWordsIterator(ret);
}

ITextRunsIterator IStory::GetTextRunsIterator( ) const
{
	TextRunsIteratorRef ret = 0;
	ATEErr error = sStory->GetTextRunsIterator(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRunsIterator(ret);
}

ITextFramesIterator IStory::GetTextFramesIterator( ) const
{
	TextFramesIteratorRef ret = 0;
	ATEErr error = sStory->GetTextFramesIterator(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextFramesIterator(ret);
}

ITextFrame IStory::GetFrame( ATETextDOM::Int32 frameIndex) const
{
	TextFrameRef ret = 0;
	ATEErr error = sStory->GetFrame(fStory, frameIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextFrame(ret);
}

void IStory::SetKernForSelection( const ITextRange& textRange, AutoKernType autoKernType)
{
	ATEErr error = sStory->SetKernForSelection(fStory, textRange.GetRef(), autoKernType);
	if(error) Throw_ATE_Exception(error);
}

void IStory::SetKernAtChar( ATETextDOM::Int32 charIndex, ATETextDOM::Int32 value)
{
	ATEErr error = sStory->SetKernAtChar(fStory, charIndex, value);
	if(error) Throw_ATE_Exception(error);
}

void IStory::GetKern( const ITextRange& textRange, AutoKernType* pAutoKernType, ATETextDOM::Int32* value) const
{
	ATEErr error = sStory->GetKern(fStory, textRange.GetRef(), pAutoKernType, value);
	if(error) Throw_ATE_Exception(error);
}

AutoKernType IStory::GetModelKernAtChar( ATETextDOM::Int32 charIndex, ATETextDOM::Int32* pManualKernValue) const
{
	AutoKernType ret;
	ATEErr error = sStory->GetModelKernAtChar(fStory, charIndex, pManualKernValue, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ITextRange IStory::GetTextRange( ATETextDOM::Int32 start, ATETextDOM::Int32 end) const
{
	TextRangeRef ret = 0;
	ATEErr error = sStory->GetTextRange(fStory, start, end, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

IStory IStory::Duplicate( )
{
	StoryRef ret = 0;
	ATEErr error = sStory->Duplicate(fStory, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

void IStory::SuspendReflow( )
{
	ATEErr error = sStory->SuspendReflow(fStory);
	if(error) Throw_ATE_Exception(error);
}

void IStory::ResumeReflow( )
{
	ATEErr error = sStory->ResumeReflow(fStory);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --ITabStop--
//////////////////////////////////////////////

ITabStop::ITabStop()
:fTabStop(0)
{
	ATEErr error = sTabStop->Initialize(&fTabStop);
	if(error) Throw_ATE_Exception(error);
}

ITabStop::ITabStop(TabStopRef tabstop)
:fTabStop(tabstop)
{
}

ITabStop::ITabStop(const ITabStop& src)
:fTabStop(src.fTabStop)
{
	sTabStop->AddRef(fTabStop);
}

ITabStop::~ITabStop()
{
	sTabStop->Release(fTabStop);
}

ITabStop& ITabStop::operator=(const ITabStop& rhs)
{
	if (&rhs != this)
	{
		sTabStop->Release(fTabStop);
		fTabStop = rhs.fTabStop;
		sTabStop->AddRef(fTabStop);
	}
	return *this;
}

bool ITabStop::operator==(const ITabStop& rhs) const
{
	return fTabStop == rhs.fTabStop;
}

bool ITabStop::operator!=(const ITabStop& rhs) const
{
	return !(*this == rhs);
}

TabStopRef ITabStop::GetRef() const
{
	return fTabStop;
}

bool ITabStop::IsNull() const
{
	return sTabStop->IsNull(fTabStop);
}

TabType ITabStop::GetTabType( ) const
{
	TabType ret;
	ATEErr error = sTabStop->GetTabType(fTabStop, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITabStop::SetTabType( TabType tabType)
{
	ATEErr error = sTabStop->SetTabType(fTabStop, tabType);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Real ITabStop::GetPosition( ) const
{
	ATETextDOM::Real ret;
	ATETextDOM::Float tempRet;
	ATEErr error = sTabStop->GetPosition(fTabStop, &tempRet);
	if(error) Throw_ATE_Exception(error);
	ret = tempRet;
	return ret;
}

void ITabStop::SetPosition( ATETextDOM::Real position)
{
	ATEErr error = sTabStop->SetPosition(fTabStop, static_cast<ATETextDOM::Float>(position));
	if(error) Throw_ATE_Exception(error);
}

bool ITabStop::HasLeader( ) const
{
	ATEBool8 ret;
	ATEErr error = sTabStop->HasLeader(fTabStop, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITabStop::GetLeader( ATETextDOM::Unicode* leader, ATETextDOM::Int32 maxLength) const
{
	ATEErr error = sTabStop->GetLeader(fTabStop, leader, maxLength);
	if(error) Throw_ATE_Exception(error);
}

void ITabStop::SetLeader( ATETextDOM::Unicode* leader)
{
	ATEErr error = sTabStop->SetLeader(fTabStop, leader);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Unicode ITabStop::GetDecimalCharacter( ) const
{
	ATETextDOM::Unicode ret;
	ATEErr error = sTabStop->GetDecimalCharacter(fTabStop, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITabStop::SetDecimalCharacter( ATETextDOM::Unicode decimalChar)
{
	ATEErr error = sTabStop->SetDecimalCharacter(fTabStop, decimalChar);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --ITabStops--
//////////////////////////////////////////////

ITabStops::ITabStops()
:fTabStops(0)
{
	ATEErr error = sTabStops->Initialize(&fTabStops);
	if(error) Throw_ATE_Exception(error);
}

ITabStops::ITabStops(TabStopsRef tabstops)
:fTabStops(tabstops)
{
}

ITabStops::ITabStops(const ITabStops& src)
:fTabStops(src.fTabStops)
{
	sTabStops->AddRef(fTabStops);
}

ITabStops::~ITabStops()
{
	sTabStops->Release(fTabStops);
}

ITabStops& ITabStops::operator=(const ITabStops& rhs)
{
	if (&rhs != this)
	{
		sTabStops->Release(fTabStops);
		fTabStops = rhs.fTabStops;
		sTabStops->AddRef(fTabStops);
	}
	return *this;
}

bool ITabStops::operator==(const ITabStops& rhs) const
{
	return fTabStops == rhs.fTabStops;
}

bool ITabStops::operator!=(const ITabStops& rhs) const
{
	return !(*this == rhs);
}

TabStopsRef ITabStops::GetRef() const
{
	return fTabStops;
}

bool ITabStops::IsNull() const
{
	return sTabStops->IsNull(fTabStops);
}

ATETextDOM::Int32 ITabStops::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTabStops->GetSize(fTabStops, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ITabStop ITabStops::GetFirst( ) const
{
	TabStopRef ret = 0;
	ATEErr error = sTabStops->GetFirst(fTabStops, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITabStop(ret);
}

ITabStop ITabStops::GetLast( ) const
{
	TabStopRef ret = 0;
	ATEErr error = sTabStops->GetLast(fTabStops, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITabStop(ret);
}

void ITabStops::ReplaceOrAdd( const ITabStop& pTabStop)
{
	ATEErr error = sTabStops->ReplaceOrAdd(fTabStops, pTabStop.GetRef());
	if(error) Throw_ATE_Exception(error);
}

ITabStop ITabStops::Item( ATETextDOM::Int32 nIndex) const
{
	TabStopRef ret = 0;
	ATEErr error = sTabStops->Item(fTabStops, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITabStop(ret);
}

void ITabStops::Remove( ATETextDOM::Int32 nIndex)
{
	ATEErr error = sTabStops->Remove(fTabStops, nIndex);
	if(error) Throw_ATE_Exception(error);
}

void ITabStops::RemoveAll( )
{
	ATEErr error = sTabStops->RemoveAll(fTabStops);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --ITabStopsIterator--
//////////////////////////////////////////////

ITabStopsIterator::ITabStopsIterator()
:fTabStopsIterator(0)
{
}

ITabStopsIterator::ITabStopsIterator(TabStopsIteratorRef tabstopsiterator)
:fTabStopsIterator(tabstopsiterator)
{
}

ITabStopsIterator::ITabStopsIterator(const ITabStopsIterator& src)
:fTabStopsIterator(src.fTabStopsIterator)
{
	sTabStopsIterator->AddRef(fTabStopsIterator);
}

ITabStopsIterator::~ITabStopsIterator()
{
	sTabStopsIterator->Release(fTabStopsIterator);
}

ITabStopsIterator& ITabStopsIterator::operator=(const ITabStopsIterator& rhs)
{
	if (&rhs != this)
	{
		sTabStopsIterator->Release(fTabStopsIterator);
		fTabStopsIterator = rhs.fTabStopsIterator;
		sTabStopsIterator->AddRef(fTabStopsIterator);
	}
	return *this;
}

bool ITabStopsIterator::operator==(const ITabStopsIterator& rhs) const
{
	return fTabStopsIterator == rhs.fTabStopsIterator;
}

bool ITabStopsIterator::operator!=(const ITabStopsIterator& rhs) const
{
	return !(*this == rhs);
}

TabStopsIteratorRef ITabStopsIterator::GetRef() const
{
	return fTabStopsIterator;
}

bool ITabStopsIterator::IsNull() const
{
	return sTabStopsIterator->IsNull(fTabStopsIterator);
}

ITabStopsIterator::ITabStopsIterator( ITabStops tabStops, Direction direction)
{
	ATEErr error = sTabStopsIterator->Initialize(tabStops.GetRef(), direction, &fTabStopsIterator);
	if(error) Throw_ATE_Exception(error);
}

bool ITabStopsIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTabStopsIterator->IsDone(fTabStopsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITabStopsIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTabStopsIterator->IsNotDone(fTabStopsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITabStopsIterator::IsEmpty( )
{
	ATEBool8 ret;
	ATEErr error = sTabStopsIterator->IsEmpty(fTabStopsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITabStopsIterator::MoveToFirst( )
{
	ATEErr error = sTabStopsIterator->MoveToFirst(fTabStopsIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITabStopsIterator::MoveToLast( )
{
	ATEErr error = sTabStopsIterator->MoveToLast(fTabStopsIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITabStopsIterator::Next( )
{
	ATEErr error = sTabStopsIterator->Next(fTabStopsIterator);
	if(error) Throw_ATE_Exception(error);
}

ITabStop ITabStopsIterator::Item( ) const
{
	TabStopRef ret = 0;
	ATEErr error = sTabStopsIterator->Item(fTabStopsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITabStop(ret);
}

//////////////////////////////////////////////
// --ITextRange--
//////////////////////////////////////////////

ITextRange::ITextRange()
:fTextRange(0)
{
}

ITextRange::ITextRange(TextRangeRef textrange)
:fTextRange(textrange)
{
}

ITextRange::ITextRange(const ITextRange& src)
:fTextRange(src.fTextRange)
{
	sTextRange->AddRef(fTextRange);
}

ITextRange::~ITextRange()
{
	sTextRange->Release(fTextRange);
}

ITextRange& ITextRange::operator=(const ITextRange& rhs)
{
	if (&rhs != this)
	{
		sTextRange->Release(fTextRange);
		fTextRange = rhs.fTextRange;
		sTextRange->AddRef(fTextRange);
	}
	return *this;
}

bool ITextRange::operator==(const ITextRange& rhs) const
{
	ATEBool8 ret = false;
	ATEErr error = sTextRange->IsEqual(fTextRange, rhs.fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRange::operator!=(const ITextRange& rhs) const
{
	return !(*this == rhs);
}

TextRangeRef ITextRange::GetRef() const
{
	return fTextRange;
}

bool ITextRange::IsNull() const
{
	return sTextRange->IsNull(fTextRange);
}

ATETextDOM::Int32 ITextRange::GetStart( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRange->GetStart(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextRange::SetStart( ATETextDOM::Int32 start)
{
	ATEErr error = sTextRange->SetStart(fTextRange, start);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 ITextRange::GetEnd( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRange->GetEnd(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextRange::SetEnd( ATETextDOM::Int32 end)
{
	ATEErr error = sTextRange->SetEnd(fTextRange, end);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 ITextRange::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRange->GetSize(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

IStory ITextRange::GetStory( ) const
{
	StoryRef ret = 0;
	ATEErr error = sTextRange->GetStory(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return IStory(ret);
}

ITextRanges ITextRange::GetTextSelection( ) const
{
	TextRangesRef ret = 0;
	ATEErr error = sTextRange->GetTextSelection(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

ITextFramesIterator ITextRange::GetTextFramesIterator( ) const
{
	TextFramesIteratorRef ret = 0;
	ATEErr error = sTextRange->GetTextFramesIterator(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextFramesIterator(ret);
}

IParagraphsIterator ITextRange::GetParagraphsIterator( ) const
{
	ParagraphsIteratorRef ret = 0;
	ATEErr error = sTextRange->GetParagraphsIterator(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraphsIterator(ret);
}

IWordsIterator ITextRange::GetWordsIterator( ) const
{
	WordsIteratorRef ret = 0;
	ATEErr error = sTextRange->GetWordsIterator(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return IWordsIterator(ret);
}

ITextRunsIterator ITextRange::GetTextRunsIterator( ) const
{
	TextRunsIteratorRef ret = 0;
	ATEErr error = sTextRange->GetTextRunsIterator(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRunsIterator(ret);
}

ICharInspector ITextRange::GetCharInspector( ) const
{
	CharInspectorRef ret = 0;
	ATEErr error = sTextRange->GetCharInspector(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharInspector(ret);
}

IParaInspector ITextRange::GetParaInspector( ) const
{
	ParaInspectorRef ret = 0;
	ATEErr error = sTextRange->GetParaInspector(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaInspector(ret);
}

ICharStyles ITextRange::GetNamedCharStyles( ) const
{
	CharStylesRef ret = 0;
	ATEErr error = sTextRange->GetNamedCharStyles(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharStyles(ret);
}

IParaStyles ITextRange::GetNamedParaStyles( ) const
{
	ParaStylesRef ret = 0;
	ATEErr error = sTextRange->GetNamedParaStyles(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaStyles(ret);
}

bool ITextRange::SetNamedCharStyle( const ATETextDOM::Unicode* pName)
{
	ATEBool8 ret;
	ATEErr error = sTextRange->SetNamedCharStyle(fTextRange, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRange::SetNamedParaStyle( const ATETextDOM::Unicode* pName)
{
	ATEBool8 ret;
	ATEErr error = sTextRange->SetNamedParaStyle(fTextRange, pName, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextRange::ClearNamedCharStyle( )
{
	ATEErr error = sTextRange->ClearNamedCharStyle(fTextRange);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::ClearNamedParaStyle( )
{
	ATEErr error = sTextRange->ClearNamedParaStyle(fTextRange);
	if(error) Throw_ATE_Exception(error);
}

ICharFeatures ITextRange::GetUniqueCharFeatures( ) const
{
	CharFeaturesRef ret = 0;
	ATEErr error = sTextRange->GetUniqueCharFeatures(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

IParaFeatures ITextRange::GetUniqueParaFeatures( ) const
{
	ParaFeaturesRef ret = 0;
	ATEErr error = sTextRange->GetUniqueParaFeatures(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaFeatures(ret);
}

bool ITextRange::HasLocalCharFeatures( )
{
	ATEBool8 ret;
	ATEErr error = sTextRange->HasLocalCharFeatures(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRange::HasLocalParaFeatures( )
{
	ATEBool8 ret;
	ATEErr error = sTextRange->HasLocalParaFeatures(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICharFeatures ITextRange::GetUniqueLocalCharFeatures( )
{
	CharFeaturesRef ret = 0;
	ATEErr error = sTextRange->GetUniqueLocalCharFeatures(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

IParaFeatures ITextRange::GetUniqueLocalParaFeatures( )
{
	ParaFeaturesRef ret = 0;
	ATEErr error = sTextRange->GetUniqueLocalParaFeatures(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaFeatures(ret);
}

void ITextRange::SetLocalCharFeatures( const ICharFeatures& pFeatures)
{
	ATEErr error = sTextRange->SetLocalCharFeatures(fTextRange, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::ReplaceOrAddLocalCharFeatures( const ICharFeatures& pFeatures)
{
	ATEErr error = sTextRange->ReplaceOrAddLocalCharFeatures(fTextRange, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::ClearLocalCharFeatures( )
{
	ATEErr error = sTextRange->ClearLocalCharFeatures(fTextRange);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::SetLocalParaFeatures( const IParaFeatures& pFeatures)
{
	ATEErr error = sTextRange->SetLocalParaFeatures(fTextRange, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::ReplaceOrAddLocalParaFeatures( const IParaFeatures& pFeatures)
{
	ATEErr error = sTextRange->ReplaceOrAddLocalParaFeatures(fTextRange, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::ClearLocalParaFeatures( )
{
	ATEErr error = sTextRange->ClearLocalParaFeatures(fTextRange);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::SetStory( const IStory& story)
{
	ATEErr error = sTextRange->SetStory(fTextRange, story.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::SetRange( ATETextDOM::Int32 start, ATETextDOM::Int32 end)
{
	ATEErr error = sTextRange->SetRange(fTextRange, start, end);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::Collapse( CollapseDirection direction)
{
	ATEErr error = sTextRange->Collapse(fTextRange, direction);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 ITextRange::Move( ATETextDOM::Int32 unit)
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRange->Move(fTextRange, unit, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ITextRange ITextRange::Clone( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextRange->Clone(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

void ITextRange::InsertBefore( const ATETextDOM::Unicode* text, ATETextDOM::Int32 length)
{
	ATEErr error = sTextRange->InsertBefore_AsUnicode(fTextRange, text, length);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::InsertAfter( const ATETextDOM::Unicode* text, ATETextDOM::Int32 length)
{
	ATEErr error = sTextRange->InsertAfter_AsUnicode(fTextRange, text, length);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::InsertBefore( const ITextRange& anotherRange)
{
	ATEErr error = sTextRange->InsertBefore_AsTextRange(fTextRange, anotherRange.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::InsertAfter( const ITextRange& anotherRange)
{
	ATEErr error = sTextRange->InsertAfter_AsTextRange(fTextRange, anotherRange.GetRef());
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 ITextRange::GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRange->GetContents_AsUnicode(fTextRange, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ITextRange::GetContents( char* text, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRange->GetContents_AsChar(fTextRange, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRange::GetSingleGlyphInRange( ATEGlyphID* pSingleGlyph) const
{
	ATEBool8 ret;
	ATEErr error = sTextRange->GetSingleGlyphInRange(fTextRange, pSingleGlyph, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextRange::Select( bool addToSelection)
{
	ATEErr error = sTextRange->Select(fTextRange, addToSelection);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::DeSelect( )
{
	ATEErr error = sTextRange->DeSelect(fTextRange);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::ChangeCase( CaseChangeType caseChangeType)
{
	ATEErr error = sTextRange->ChangeCase(fTextRange, caseChangeType);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::FitHeadlines( )
{
	ATEErr error = sTextRange->FitHeadlines(fTextRange);
	if(error) Throw_ATE_Exception(error);
}

void ITextRange::Remove( )
{
	ATEErr error = sTextRange->Remove(fTextRange);
	if(error) Throw_ATE_Exception(error);
}

ASCharType ITextRange::GetCharacterType( ) const
{
	ASCharType ret;
	ATEErr error = sTextRange->GetCharacterType(fTextRange, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

//////////////////////////////////////////////
// --ITextRanges--
//////////////////////////////////////////////

ITextRanges::ITextRanges()
:fTextRanges(0)
{
	ATEErr error = sTextRanges->Initialize(&fTextRanges);
	if(error) Throw_ATE_Exception(error);
}

ITextRanges::ITextRanges(TextRangesRef textranges)
:fTextRanges(textranges)
{
}

ITextRanges::ITextRanges(const ITextRanges& src)
:fTextRanges(src.fTextRanges)
{
	sTextRanges->AddRef(fTextRanges);
}

ITextRanges::~ITextRanges()
{
	sTextRanges->Release(fTextRanges);
}

ITextRanges& ITextRanges::operator=(const ITextRanges& rhs)
{
	if (&rhs != this)
	{
		sTextRanges->Release(fTextRanges);
		fTextRanges = rhs.fTextRanges;
		sTextRanges->AddRef(fTextRanges);
	}
	return *this;
}

bool ITextRanges::operator==(const ITextRanges& rhs) const
{
	return fTextRanges == rhs.fTextRanges;
}

bool ITextRanges::operator!=(const ITextRanges& rhs) const
{
	return !(*this == rhs);
}

TextRangesRef ITextRanges::GetRef() const
{
	return fTextRanges;
}

bool ITextRanges::IsNull() const
{
	return sTextRanges->IsNull(fTextRanges);
}

ATETextDOM::Int32 ITextRanges::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRanges->GetSize(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ITextRange ITextRanges::GetFirst( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextRanges->GetFirst(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

ITextRange ITextRanges::GetLast( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextRanges->GetLast(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

ITextRanges ITextRanges::GetTextSelection( ) const
{
	TextRangesRef ret = 0;
	ATEErr error = sTextRanges->GetTextSelection(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRanges(ret);
}

IParagraphsIterator ITextRanges::GetParagraphsIterator( ) const
{
	ParagraphsIteratorRef ret = 0;
	ATEErr error = sTextRanges->GetParagraphsIterator(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParagraphsIterator(ret);
}

IWordsIterator ITextRanges::GetWordsIterator( ) const
{
	WordsIteratorRef ret = 0;
	ATEErr error = sTextRanges->GetWordsIterator(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return IWordsIterator(ret);
}

ITextRunsIterator ITextRanges::GetTextRunsIterator( ) const
{
	TextRunsIteratorRef ret = 0;
	ATEErr error = sTextRanges->GetTextRunsIterator(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRunsIterator(ret);
}

ICharInspector ITextRanges::GetCharInspector( ) const
{
	CharInspectorRef ret = 0;
	ATEErr error = sTextRanges->GetCharInspector(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharInspector(ret);
}

IParaInspector ITextRanges::GetParaInspector( ) const
{
	ParaInspectorRef ret = 0;
	ATEErr error = sTextRanges->GetParaInspector(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaInspector(ret);
}

void ITextRanges::ClearNamedCharStyle( )
{
	ATEErr error = sTextRanges->ClearNamedCharStyle(fTextRanges);
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::ClearNamedParaStyle( )
{
	ATEErr error = sTextRanges->ClearNamedParaStyle(fTextRanges);
	if(error) Throw_ATE_Exception(error);
}

ICharFeatures ITextRanges::GetUniqueCharFeatures( ) const
{
	CharFeaturesRef ret = 0;
	ATEErr error = sTextRanges->GetUniqueCharFeatures(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

IParaFeatures ITextRanges::GetUniqueParaFeatures( ) const
{
	ParaFeaturesRef ret = 0;
	ATEErr error = sTextRanges->GetUniqueParaFeatures(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaFeatures(ret);
}

bool ITextRanges::HasLocalCharFeatures( )
{
	ATEBool8 ret;
	ATEErr error = sTextRanges->HasLocalCharFeatures(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRanges::HasLocalParaFeatures( )
{
	ATEBool8 ret;
	ATEErr error = sTextRanges->HasLocalParaFeatures(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ICharFeatures ITextRanges::GetUniqueLocalCharFeatures( )
{
	CharFeaturesRef ret = 0;
	ATEErr error = sTextRanges->GetUniqueLocalCharFeatures(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return ICharFeatures(ret);
}

IParaFeatures ITextRanges::GetUniqueLocalParaFeatures( )
{
	ParaFeaturesRef ret = 0;
	ATEErr error = sTextRanges->GetUniqueLocalParaFeatures(fTextRanges, &ret);
	if(error) Throw_ATE_Exception(error);
	return IParaFeatures(ret);
}

void ITextRanges::SetLocalCharFeatures( const ICharFeatures& pFeatures)
{
	ATEErr error = sTextRanges->SetLocalCharFeatures(fTextRanges, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::ReplaceOrAddLocalCharFeatures( const ICharFeatures& pFeatures)
{
	ATEErr error = sTextRanges->ReplaceOrAddLocalCharFeatures(fTextRanges, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::ClearLocalCharFeatures( )
{
	ATEErr error = sTextRanges->ClearLocalCharFeatures(fTextRanges);
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::SetLocalParaFeatures( const IParaFeatures& pFeatures)
{
	ATEErr error = sTextRanges->SetLocalParaFeatures(fTextRanges, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::ReplaceOrAddLocalParaFeatures( const IParaFeatures& pFeatures)
{
	ATEErr error = sTextRanges->ReplaceOrAddLocalParaFeatures(fTextRanges, pFeatures.GetRef());
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::ClearLocalParaFeatures( )
{
	ATEErr error = sTextRanges->ClearLocalParaFeatures(fTextRanges);
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::Select( bool addToSelection)
{
	ATEErr error = sTextRanges->Select(fTextRanges, addToSelection);
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::DeSelect( )
{
	ATEErr error = sTextRanges->DeSelect(fTextRanges);
	if(error) Throw_ATE_Exception(error);
}

ATETextDOM::Int32 ITextRanges::GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRanges->GetContents_AsUnicode(fTextRanges, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 ITextRanges::GetContents( char* text, ATETextDOM::Int32 maxLength) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sTextRanges->GetContents_AsChar(fTextRanges, text, maxLength, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextRanges::ChangeCase( CaseChangeType caseChangeType)
{
	ATEErr error = sTextRanges->ChangeCase(fTextRanges, caseChangeType);
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::Add( const ITextRange& textRange)
{
	ATEErr error = sTextRanges->Add(fTextRanges, textRange.GetRef());
	if(error) Throw_ATE_Exception(error);
}

ITextRange ITextRanges::Item( ATETextDOM::Int32 nIndex) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextRanges->Item(fTextRanges, nIndex, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

void ITextRanges::RemoveAll( )
{
	ATEErr error = sTextRanges->RemoveAll(fTextRanges);
	if(error) Throw_ATE_Exception(error);
}

void ITextRanges::Remove( ATETextDOM::Int32 nIndex)
{
	ATEErr error = sTextRanges->Remove(fTextRanges, nIndex);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --ITextRangesIterator--
//////////////////////////////////////////////

ITextRangesIterator::ITextRangesIterator()
:fTextRangesIterator(0)
{
}

ITextRangesIterator::ITextRangesIterator(TextRangesIteratorRef textrangesiterator)
:fTextRangesIterator(textrangesiterator)
{
}

ITextRangesIterator::ITextRangesIterator(const ITextRangesIterator& src)
:fTextRangesIterator(src.fTextRangesIterator)
{
	sTextRangesIterator->AddRef(fTextRangesIterator);
}

ITextRangesIterator::~ITextRangesIterator()
{
	sTextRangesIterator->Release(fTextRangesIterator);
}

ITextRangesIterator& ITextRangesIterator::operator=(const ITextRangesIterator& rhs)
{
	if (&rhs != this)
	{
		sTextRangesIterator->Release(fTextRangesIterator);
		fTextRangesIterator = rhs.fTextRangesIterator;
		sTextRangesIterator->AddRef(fTextRangesIterator);
	}
	return *this;
}

bool ITextRangesIterator::operator==(const ITextRangesIterator& rhs) const
{
	return fTextRangesIterator == rhs.fTextRangesIterator;
}

bool ITextRangesIterator::operator!=(const ITextRangesIterator& rhs) const
{
	return !(*this == rhs);
}

TextRangesIteratorRef ITextRangesIterator::GetRef() const
{
	return fTextRangesIterator;
}

bool ITextRangesIterator::IsNull() const
{
	return sTextRangesIterator->IsNull(fTextRangesIterator);
}

ITextRangesIterator::ITextRangesIterator( ITextRanges textRanges, Direction direction)
{
	ATEErr error = sTextRangesIterator->Initialize(textRanges.GetRef(), direction, &fTextRangesIterator);
	if(error) Throw_ATE_Exception(error);
}

ITextRangesIterator ITextRangesIterator::Clone( ) const
{
	TextRangesIteratorRef ret = 0;
	ATEErr error = sTextRangesIterator->Clone(fTextRangesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRangesIterator(ret);
}

bool ITextRangesIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextRangesIterator->IsNotDone(fTextRangesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRangesIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextRangesIterator->IsDone(fTextRangesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRangesIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextRangesIterator->IsEmpty(fTextRangesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextRangesIterator::MoveToFirst( )
{
	ATEErr error = sTextRangesIterator->MoveToFirst(fTextRangesIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITextRangesIterator::MoveToLast( )
{
	ATEErr error = sTextRangesIterator->MoveToLast(fTextRangesIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITextRangesIterator::Next( )
{
	ATEErr error = sTextRangesIterator->Next(fTextRangesIterator);
	if(error) Throw_ATE_Exception(error);
}

ITextRange ITextRangesIterator::Item( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextRangesIterator->Item(fTextRangesIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

//////////////////////////////////////////////
// --ITextRunsIterator--
//////////////////////////////////////////////

ITextRunsIterator::ITextRunsIterator()
:fTextRunsIterator(0)
{
}

ITextRunsIterator::ITextRunsIterator(TextRunsIteratorRef textrunsiterator)
:fTextRunsIterator(textrunsiterator)
{
}

ITextRunsIterator::ITextRunsIterator(const ITextRunsIterator& src)
:fTextRunsIterator(src.fTextRunsIterator)
{
	sTextRunsIterator->AddRef(fTextRunsIterator);
}

ITextRunsIterator::~ITextRunsIterator()
{
	sTextRunsIterator->Release(fTextRunsIterator);
}

ITextRunsIterator& ITextRunsIterator::operator=(const ITextRunsIterator& rhs)
{
	if (&rhs != this)
	{
		sTextRunsIterator->Release(fTextRunsIterator);
		fTextRunsIterator = rhs.fTextRunsIterator;
		sTextRunsIterator->AddRef(fTextRunsIterator);
	}
	return *this;
}

bool ITextRunsIterator::operator==(const ITextRunsIterator& rhs) const
{
	return fTextRunsIterator == rhs.fTextRunsIterator;
}

bool ITextRunsIterator::operator!=(const ITextRunsIterator& rhs) const
{
	return !(*this == rhs);
}

TextRunsIteratorRef ITextRunsIterator::GetRef() const
{
	return fTextRunsIterator;
}

bool ITextRunsIterator::IsNull() const
{
	return sTextRunsIterator->IsNull(fTextRunsIterator);
}

ITextRunsIterator::ITextRunsIterator( const ITextRanges& ranges, Direction direction)
{
	ATEErr error = sTextRunsIterator->Initialize(ranges.GetRef(), direction, &fTextRunsIterator);
	if(error) Throw_ATE_Exception(error);
}

bool ITextRunsIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextRunsIterator->IsNotDone(fTextRunsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRunsIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextRunsIterator->IsDone(fTextRunsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool ITextRunsIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sTextRunsIterator->IsEmpty(fTextRunsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void ITextRunsIterator::MoveToFirst( )
{
	ATEErr error = sTextRunsIterator->MoveToFirst(fTextRunsIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITextRunsIterator::MoveToLast( )
{
	ATEErr error = sTextRunsIterator->MoveToLast(fTextRunsIterator);
	if(error) Throw_ATE_Exception(error);
}

void ITextRunsIterator::Next( )
{
	ATEErr error = sTextRunsIterator->Next(fTextRunsIterator);
	if(error) Throw_ATE_Exception(error);
}

ITextRange ITextRunsIterator::Item( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sTextRunsIterator->Item(fTextRunsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

//////////////////////////////////////////////
// --IWordsIterator--
//////////////////////////////////////////////

IWordsIterator::IWordsIterator()
:fWordsIterator(0)
{
}

IWordsIterator::IWordsIterator(WordsIteratorRef wordsiterator)
:fWordsIterator(wordsiterator)
{
}

IWordsIterator::IWordsIterator(const IWordsIterator& src)
:fWordsIterator(src.fWordsIterator)
{
	sWordsIterator->AddRef(fWordsIterator);
}

IWordsIterator::~IWordsIterator()
{
	sWordsIterator->Release(fWordsIterator);
}

IWordsIterator& IWordsIterator::operator=(const IWordsIterator& rhs)
{
	if (&rhs != this)
	{
		sWordsIterator->Release(fWordsIterator);
		fWordsIterator = rhs.fWordsIterator;
		sWordsIterator->AddRef(fWordsIterator);
	}
	return *this;
}

bool IWordsIterator::operator==(const IWordsIterator& rhs) const
{
	return fWordsIterator == rhs.fWordsIterator;
}

bool IWordsIterator::operator!=(const IWordsIterator& rhs) const
{
	return !(*this == rhs);
}

WordsIteratorRef IWordsIterator::GetRef() const
{
	return fWordsIterator;
}

bool IWordsIterator::IsNull() const
{
	return sWordsIterator->IsNull(fWordsIterator);
}

IWordsIterator::IWordsIterator( const ITextRanges& ranges, Direction direction)
{
	ATEErr error = sWordsIterator->Initialize(ranges.GetRef(), direction, &fWordsIterator);
	if(error) Throw_ATE_Exception(error);
}

bool IWordsIterator::IsNotDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sWordsIterator->IsNotDone(fWordsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IWordsIterator::IsDone( ) const
{
	ATEBool8 ret;
	ATEErr error = sWordsIterator->IsDone(fWordsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

bool IWordsIterator::IsEmpty( ) const
{
	ATEBool8 ret;
	ATEErr error = sWordsIterator->IsEmpty(fWordsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IWordsIterator::MoveToFirst( )
{
	ATEErr error = sWordsIterator->MoveToFirst(fWordsIterator);
	if(error) Throw_ATE_Exception(error);
}

void IWordsIterator::MoveToLast( )
{
	ATEErr error = sWordsIterator->MoveToLast(fWordsIterator);
	if(error) Throw_ATE_Exception(error);
}

void IWordsIterator::Next( )
{
	ATEErr error = sWordsIterator->Next(fWordsIterator);
	if(error) Throw_ATE_Exception(error);
}

ITextRange IWordsIterator::Item( ) const
{
	TextRangeRef ret = 0;
	ATEErr error = sWordsIterator->Item(fWordsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ITextRange(ret);
}

ATETextDOM::Int32 IWordsIterator::GetTrailingSpaceCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sWordsIterator->GetTrailingSpaceCount(fWordsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IWordsIterator::GetTrailingCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sWordsIterator->GetTrailingCount(fWordsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ATETextDOM::Int32 IWordsIterator::GetTrailingTerminatingPunctuationCount( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sWordsIterator->GetTrailingTerminatingPunctuationCount(fWordsIterator, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}


//////////////////////////////////////////////
// --IArrayLine --
//////////////////////////////////////////////

IArrayLine::IArrayLine()
:fArrayLine(0) 
{
}

IArrayLine::IArrayLine(ArrayLineRef rangeref)
:fArrayLine(rangeref)
{
}

IArrayLine::IArrayLine(const IArrayLine& src)
:fArrayLine(src.fArrayLine)
{
	sArrayLine->AddRef(fArrayLine);
}

IArrayLine::~IArrayLine()
{
	sArrayLine->Release(fArrayLine);
}

IArrayLine& IArrayLine::operator=(const IArrayLine& rhs)
{
	if (&rhs != this)
	{
		sArrayLine->Release(fArrayLine);
		fArrayLine = rhs.fArrayLine;
		sArrayLine->AddRef(fArrayLine);
	}
	return *this;
}

bool IArrayLine::operator==(const IArrayLine& rhs) const
{
	return fArrayLine == rhs.fArrayLine;
}

bool IArrayLine::operator!=(const IArrayLine& rhs) const
{
	return !(*this == rhs);
}

ArrayLineRef IArrayLine::GetRef() const
{
	return fArrayLine;
}

bool IArrayLine::IsNull() const
{
	return sArrayLine->IsNull(fArrayLine);
}

ATETextDOM::Int32 IArrayLine::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayLine->GetSize(fArrayLine, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

void IArrayLine::Item( ATETextDOM::Int32 index, ATETextDOM::FloatPoint* retStart, ATETextDOM::FloatPoint* retEnd) const
{
	ATETextDOM::FloatPoint tempRetEnd,tempStartEnd;
	ATEErr error = sArrayLine->Item(fArrayLine, index, &tempStartEnd, &tempRetEnd);
	SloFloatPointToAIFloatPoint(&tempStartEnd,retStart);
	SloFloatPointToAIFloatPoint(&tempRetEnd,retEnd);
	if(error) Throw_ATE_Exception(error);
}

//////////////////////////////////////////////
// --IArrayComposerEngine--
//////////////////////////////////////////////

IArrayComposerEngine::IArrayComposerEngine()
:fArrayComposerEngine(0)
{
}

IArrayComposerEngine::IArrayComposerEngine(ArrayComposerEngineRef arraycomposerengine)
:fArrayComposerEngine(arraycomposerengine)
{
}

IArrayComposerEngine::IArrayComposerEngine(const IArrayComposerEngine& src)
:fArrayComposerEngine(src.fArrayComposerEngine)
{
	sArrayComposerEngine->AddRef(fArrayComposerEngine);
}

IArrayComposerEngine::~IArrayComposerEngine()
{
	sArrayComposerEngine->Release(fArrayComposerEngine);
}

IArrayComposerEngine& IArrayComposerEngine::operator=(const IArrayComposerEngine& rhs)
{
	if (&rhs != this)
	{
		sArrayComposerEngine->Release(fArrayComposerEngine);
		fArrayComposerEngine = rhs.fArrayComposerEngine;
		sArrayComposerEngine->AddRef(fArrayComposerEngine);
	}
	return *this;
}

bool IArrayComposerEngine::operator==(const IArrayComposerEngine& rhs) const
{
	return fArrayComposerEngine == rhs.fArrayComposerEngine;
}

bool IArrayComposerEngine::operator!=(const IArrayComposerEngine& rhs) const
{
	return !(*this == rhs);
}

ArrayComposerEngineRef IArrayComposerEngine::GetRef() const
{
	return fArrayComposerEngine;
}

bool IArrayComposerEngine::IsNull() const
{
	return sArrayComposerEngine->IsNull(fArrayComposerEngine);
}

ATETextDOM::Int32 IArrayComposerEngine::GetSize( ) const
{
	ATETextDOM::Int32 ret;
	ATEErr error = sArrayComposerEngine->GetSize(fArrayComposerEngine, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ComposerEngine IArrayComposerEngine::GetFirst( ) const
{
	ComposerEngine ret;
	ATEErr error = sArrayComposerEngine->GetFirst(fArrayComposerEngine, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ComposerEngine IArrayComposerEngine::GetLast( ) const
{
	ComposerEngine ret;
	ATEErr error = sArrayComposerEngine->GetLast(fArrayComposerEngine, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}

ComposerEngine IArrayComposerEngine::Item( ATETextDOM::Int32 index) const
{
	ComposerEngine ret;
	ATEErr error = sArrayComposerEngine->Item(fArrayComposerEngine, index, &ret);
	if(error) Throw_ATE_Exception(error);
	return ret;
}


}// namespace ATE

