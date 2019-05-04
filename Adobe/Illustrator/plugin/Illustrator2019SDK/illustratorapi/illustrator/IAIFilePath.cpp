/*
 *        Name:	AIFilePath.cpp
 *     Purpose:	
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

#include "AIFilePath.h"

using ai::FilePath;
using ai::UnicodeString;

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIFilePath)
#elif defined(_IAIFilePathSuite_INCLUDE_H_)
    #include _IAIFilePathSuite_INCLUDE_H_
#else
	extern "C" AIFilePathSuite *sAIFilePath;
#endif

/* Throw result as an ai::Error */
static void check_result(AIErr result)
{
	if ( result != kNoErr )
	{
		throw ai::Error(result);
	}
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::ResetVolumeCache() AINOTHROW
{
	sAIFilePath->ResetVolumeCache();
}

////////////////////////////////////////////////////////////////////////////////
// Constructors/destructors
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath():
	impl(0)
{
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const FilePath &src):
	impl(0)
{
	AIErr result = sAIFilePath->Copy(src, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const ai::UnicodeString &in, bool expandName):
	impl(0)
{
	AIErr result = sAIFilePath->Set(in, expandName, *this);
	check_result(result);
}
////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const SPPlatformFileReference &ref):
	impl(0)
{
	sAIFilePath->SetFromSPFileRef(ref, *this);
}
////////////////////////////////////////////////////////////////////////////////
#ifdef MAC_ENV
FilePath::FilePath(const CFStringRef string):
	impl(0)
{
	sAIFilePath->SetFromCFString(string, *this);
}

////////////////////////////////////////////////////////////////////////////////
#if DEPRICATED_IN_10_8
FilePath::FilePath(const FSRef &ref):
	impl(0)
{
	OSStatus result = sAIFilePath->SetFromFSRef(ref, *this);
	check_result(result);
}
#endif // DEPRICATED_IN_10_8

////////////////////////////////////////////////////////////////////////////////
FilePath::FilePath(const CFURLRef url):
	impl(0)
{
	sAIFilePath->SetFromCFURL(url, *this);
}

#endif	// MAC_ENV

////////////////////////////////////////////////////////////////////////////////
FilePath::~FilePath()
{
	if(impl)
		(void)sAIFilePath->DeleteFilePath(*this);
}

////////////////////////////////////////////////////////////////////////////////
FilePath &FilePath::operator=(const FilePath &in)
{
    //if null is being assigned to null
    if(in.impl == nullptr && impl == nullptr)
        return *this;
    
	AIErr result = sAIFilePath->Copy(in, *this);
	check_result(result);
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Other members
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// The Copy function is not explicitly implemented here-- use the copy constructor

////////////////////////////////////////////////////////////////////////////////
bool FilePath::IsEmpty() const
{
	return sAIFilePath->IsEmpty(*this) != false;
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::MakeEmpty()
{
	sAIFilePath->MakeEmpty(*this);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::Equal(const FilePath &other, const bool resolveLinks) const
{
	return sAIFilePath->Equal(*this, other, resolveLinks) != false;
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::operator==(const FilePath &path) const
{
	return sAIFilePath->Equal(*this, path, false) != false;
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::operator!=(const FilePath &path) const
{
	return !sAIFilePath->Equal(*this, path, false);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::operator<(const FilePath &path) const
{
	return sAIFilePath->LessThan(*this, path) != false;
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::StartsWithDelimiter() const
{
	return sAIFilePath->StartsWithDelimiter(*this) != false;
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::EndsWithDelimiter() const
{
	return sAIFilePath->EndsWithDelimiter(*this) != false;
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::AddComponent(const ai::UnicodeString &addend)
{
	AIErr result = sAIFilePath->AddComponent(addend, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::RemoveComponent()
{
	sAIFilePath->RemoveComponent(*this);
}

	
////////////////////////////////////////////////////////////////////////////////
void FilePath::AddExtension(const ai::UnicodeString &ext)
{
	sAIFilePath->AddExtension(ext, *this);
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::RemoveExtension()
{
	sAIFilePath->RemoveExtension(*this);
}

////////////////////////////////////////////////////////////////////////////////
bool FilePath::Exists(
	const bool resolveLinks,
	ai::UnicodeString *longPath,
	bool *isFile) const
{
	AIBool8 isFileRet;
	bool ret = sAIFilePath->Exists(*this, resolveLinks, longPath, &isFileRet) != false;
	if (isFile) *isFile = (isFileRet != false);
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
void FilePath::Resolve()
{
	AIErr result = sAIFilePath->Resolve(*this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////
// Set methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void FilePath::Set(const ai::UnicodeString &string, bool expandName)
{
	AIErr result = sAIFilePath->Set(string, expandName, *this);
	check_result(result);
}

////////////////////////////////////////////////////////////////////////////////

void FilePath::SetFromSPFileRef(const SPPlatformFileReference &spec)
{
	sAIFilePath->SetFromSPFileRef(spec, *this);
}

#ifdef MAC_ENV

////////////////////////////////////////////////////////////////////////////////
void FilePath::SetFromCFString(const CFStringRef string)
{
	sAIFilePath->SetFromCFString(string, *this);
}

////////////////////////////////////////////////////////////////////////////////
#if DEPRICATED_IN_10_8
OSStatus FilePath::SetFromFSRef(const FSRef &ref)
{
	OSStatus result = sAIFilePath->SetFromFSRef(ref, *this);
	return result;
}
#endif //DEPRICATED_IN_10_8

////////////////////////////////////////////////////////////////////////////////
void FilePath::SetFromCFURL(const CFURLRef url)
{
	sAIFilePath->SetFromCFURL(url, *this);
}
#endif	// MAC_ENV

////////////////////////////////////////////////////////////////////////////////
// Get methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFileName(const bool displayName) const
{
	ai::UnicodeString fileName;
	AIErr result = sAIFilePath->GetFileName(*this, displayName, fileName);
	
	check_result(result);
	return fileName;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFileNameNoExt() const
{
	ai::UnicodeString fileName;
	AIErr result = sAIFilePath->GetFileNameNoExt(*this, fileName);
	
	check_result(result);
	return fileName;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFileExtension() const
{
	ai::UnicodeString fileExt;
	AIErr result = sAIFilePath->GetFileExtension(*this, fileExt);
	
	check_result(result);
	return fileExt;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetFullPath(const bool displayName) const
{
	ai::UnicodeString fullPath;
	AIErr result = sAIFilePath->GetFullPath(*this, displayName, fullPath);

	check_result(result);
	return fullPath;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetDirectory(const bool displayName) const
{
	ai::UnicodeString dir;
	AIErr result = sAIFilePath->GetDirectory(*this, displayName, dir);
	
	check_result(result);
	return dir;
}

////////////////////////////////////////////////////////////////////////////////
#ifdef MAC_ENV
#if DEPRICATED_IN_10_8
void FilePath::GetVolumeAndParent(FSVolumeRefNum *vol, UInt32 *parent) const
{
	sAIFilePath->GetVolumeAndParent(*this, vol, (ai::uint32*)parent);
}
#endif // DEPRICATED_IN_10_8
#endif //MAC_ENV

////////////////////////////////////////////////////////////////////////////////
const char FilePath::GetDelimiter()
{
	return sAIFilePath->GetDelimiter();
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetShortPath() const
{
	ai::UnicodeString path;
	AIErr result = sAIFilePath->GetShortPath(*this, path);
	
	check_result(result);
	return path;
}

////////////////////////////////////////////////////////////////////////////////
AIErr FilePath::GetCreatorAndType(ai::uint32 *creator, ai::uint32 *type) const
{
	AIErr result = sAIFilePath->GetCreatorAndType(*this, creator, type);
	return result;
}

////////////////////////////////////////////////////////////////////////////////
ai::UnicodeString FilePath::GetAsURL(const bool displayName) const
{
	ai::UnicodeString url;
	AIErr result = sAIFilePath->GetAsURL(*this, displayName, url);
	
	check_result(result);
	return url;
}

////////////////////////////////////////////////////////////////////////////////
FilePath FilePath::GetParent() const
{
	FilePath parent;
	AIErr result = sAIFilePath->GetParent(*this, parent);
	
	check_result(result);
	return parent;
}

////////////////////////////////////////////////////////////////////////////////

void FilePath::GetAsSPPlatformFileRef(SPPlatformFileReference &ref) const
{
	AIErr result = sAIFilePath->GetAsSPPlatformFileRef(*this, ref);
	check_result(result);
}

#ifdef MAC_ENV
////////////////////////////////////////////////////////////////////////////////
CFStringRef FilePath::GetAsCFString() const
{
	CFStringRef string = sAIFilePath->GetAsCFString(*this);
	return string;
}

////////////////////////////////////////////////////////////////////////////////
#if DEPRICATED_IN_10_8
OSStatus FilePath::GetAsFSRef(FSRef &ref) const
{
	OSStatus result = sAIFilePath->GetAsFSRef(*this, ref);
	return result;
}
#endif //DEPRICATED_IN_10_8

////////////////////////////////////////////////////////////////////////////////
CFURLRef FilePath::GetAsCFURL() const
{
	return sAIFilePath->GetAsCFURL(*this);
}

#ifdef __OBJC__
NSString* FilePath::GetAsNSString() const
{
    return sAIFilePath->GetAsNSString( *this );
}

NSURL* FilePath::GetAsNSURL() const
{
    return sAIFilePath->GetAsNSURL( *this );
}

NSData* FilePath::GetAsBookmarkData( const FilePath& inRelativeToPath, NSError** outError ) const
{
    return sAIFilePath->GetAsBookmarkData( *this, inRelativeToPath, outError );
}

NSData* FilePath::GetAsMinimalBookmarkData( const FilePath& inRelativeToPath, NSError** outError ) const
{
    return sAIFilePath->GetAsMinimalBookmarkData( *this, inRelativeToPath, outError );
}

void FilePath::GetVolumeAndParent( NSURL **outVolume, NSURL **outParent ) const
{
    sAIFilePath->GetVolumeAndParentFromFilePath(*this, outVolume, outParent );
}

BOOL FilePath::SetFromBookmarkData( NSData* inBookmarkData, const FilePath& inRelativeToPath /*= FilePath()*/, NSError** outError /*= NULL*/ )
{
    return sAIFilePath->SetFromBookmarkData( *this, inBookmarkData, inRelativeToPath, outError );
}

BOOL FilePath::IsAlias ()const
{
    return sAIFilePath->IsAlias(*this);
}

AIBoolean FilePath::IsOnNetwork ()const
{
    return static_cast<AIBoolean>(sAIFilePath->IsOnNetwork(*this));
}
BOOL FilePath::IsEjectable ()const
{
    return sAIFilePath->IsEjectable(*this);
}
#endif //__OBJC__

#endif	// MAC_ENV
