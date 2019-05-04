//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/SDKDef.h $
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

#ifndef __SDKDef_h__
#define __SDKDef_h__

/*
// VersionInfo:
// Version information for SDK plug-ins.
// This file is parsed by rez, plc as well as C++ compilers.
// It must only contain preprocessor definitions.
*/
#ifndef __PLIST__
#define __STRING__(x) SDKDef_InternalMacroToString(x)
#define SDKDef_InternalMacroToString(x) #x
#endif
#define kSDKDefBuildNumber	0

#define kSDKDefAIMajorVersionNum   18
#define kSDKDefAIMinorVersionNum   0
#define kSDKDefAIRevisionVersionNum    0
//eg "15.0.0.0"
#define kSDKDefAIShortVersionString __STRING__(kSDKDefAIMajorVersionNum) "." __STRING__(kSDKDefAIMinorVersionNum) "." __STRING__(kSDKDefAIRevisionVersionNum) "." __STRING__(kSDKDefBuildNumber)
#define kSDKDefAIFullCompanyName      "Adobe Systems Incorporated"
#define kSDKDefAIFullProductName "Adobe Illustrator"
//Mac specific for Plists
#define kSDKDefAIBundlePrefix    com.adobe.illustrator

#define kSDKDefCopyrightString "Copyright 1987-2014 Adobe Systems Incorporated. All rights reserved."
#define kSDKDefFileDescriptionString "Adobe Illustrator SDK Plug-in"
//eg "15.0"
#define kSDKDefProductVersionString __STRING__(kSDKDefAIMajorVersionNum) "." __STRING__(kSDKDefAIMinorVersionNum)
#define kSDKDefAboutPluginString  "An Adobe Illustrator SDK plugin http://partners.adobe.com"


/* About Plug-ins menu
*/
// Group name and ui display string for About Plug-ins menu for SDK sample plug-ins - third parties should add their own group.
#define kSDKDefAboutSDKCompanyPluginsGroupName				"SDKAboutPluginsGroupName"
#define kSDKDefAboutSDKCompanyPluginsGroupNameString		"About SDK Plug-ins"

// About box description for SDK plug-ins
#define kSDKDefAboutSDKCompanyPluginsAlertString "An Adobe Illustrator SDK sample\nhttp://www.adobe.com/devnet/\nCopyright 1987-2014 Adobe Systems Incorporated. All rights reserved."
#endif //__SDKDef_h__
