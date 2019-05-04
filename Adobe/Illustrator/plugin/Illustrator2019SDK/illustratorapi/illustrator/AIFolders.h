#ifndef __AIFolders__
#define __AIFolders__

/*
 *        Name:	AIFolders.h
 *   $Revision: 1 $
 *      Author:	 dmaclach
 *        Date:
 *     Purpose:	Adobe Illustrator Folders Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIFilePath.h"

#include "AIHeaderBegin.h"

/** @file AIFolders.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAIFoldersSuite					"AI Folders Suite"
#define kAIFoldersSuiteVersion5			AIAPI_VERSION(5)
#define kAIFoldersSuiteVersion			kAIFoldersSuiteVersion5
#define kAIFoldersVersion				kAIFoldersSuiteVersion

/*******************************************************************************
 **
 **	Constants
 **
 **/

/** @ingroup Errors
	Folder error, see \c #AIFoldersSuite. */
#define kFolderNotFoundErr		'D!FD'


/*******************************************************************************
 **
 **	Types
 **
 **/

/**
	Identifiers for Illustrator folders. See \c #AIFoldersSuite.
*/
typedef enum AIFolderType
{
		kAIApplicationFolderType = 0,
		kAIPluginsFolderType = 1,
		kAIPrimaryScratchFolderType = 2,
		kAISecondaryScratchFolderType = 3,
		kAIPreferencesFolderType = 4,
		kAIUserSupportFolderType = 5,
		kAIUserSupportAIFolderType = 6,
		kAIUserSupportAIPluginsFolderType = 7,
		kAIApplicationSupportCommonFolderType = 8,
		kAIApplicationSupportCommonColorFolderType = 9,
		kAIApplicationSupportCommonTypeSupportFolderType = 10,
		kAIApplicationSupportCommonFontsFolderType = 11,
		kAIApplicationSupportCommonFontsReqrdFolderType = 12,
		kAIApplicationSupportCommonFontsReqrdCMapsFolderType = 13,
	    kAIRequiredFontsFolderType = 14,
		kAIFontsFolderType = 15,
		kAIMyDocumentsFolderType = 16,
		kAIApplicationSupportCommonWorkflowFolderType = 17,
		kAIPrinterDescriptionsFolderType = 18,
		kAIRequiredPluginsFolderType = 19,
		kAISettingsFolderType = 20,
		kAIColorTableSettingsFolderType = 21,
		kAIOptimizeSettingsFolderType = 22,
		kAIHelpFolderType = 23,
		kAIRootFolderType = 24,
		kAIPresetsFolderType = 25,
		/* The presets folder and all folders within it are in the application directory and may not be writable, especially on Vista. */
		/* If your code intends to write settings files, please use one of the kAIUserSupport folders or the kAIUserWritable folders */
		/* instead of the kAIPreset folders. */
		kAIPresetActionsFolderType = 26,
		kAIPresetBrushesFolderType = 27,
		kAIPresetGradientsFolderType = 28,
		kAIPresetKeyboardShortcutsFolderType = 29,
		kAIPresetPatternsFolderType = 30,
		kAIPresetScriptsFolderType = 31,
		kAIPresetStylesFolderType = 32,
		kAIPresetSwatchesFolderType = 33,
		kAIDictionariesFolderType = 34,
		kAILegalFolderType = 35,
		kAISampleFilesFolderType = 36,
		kAIUtilitiesFolderType = 37,
		kAIPackageFolderType = 38,
		kAIApplicationSupportCommonFontsReqrdBaseFolderType = 39,
		kAIHelpersFolderType = 40,
		kAIPreviewInFolderType = 41,
		/**  LEGACY USE ONLY.  Templates available to developers are now in \c #kAIUserWritableStartupFileFolderType */
		kAIStartupFileFolderType = 42,
		kAIRidersFileFolderType = 43,
		kAIHyphenationDictFolderType = 44,
		kAIApplicationSupportCommonPDFLFolderType = 45,
		kAIApplicationSupportCommonPDFL5FolderType = 46,
		kAIApplicationSupportCommonPDFL5CMapsFolderType = 47,
		kAIApplicationSupportCommonPDFL5FontsFolderType = 48,
		kAIApplicationSupportCommonPrintSupportFolderType = 49,
		kAIApplicationSupportCommonColorProfilesFolderType = 50,
		kAIApplicationSupportCommonColorSettingsFolderType = 51,
		kAIContentsFolderType = 52,
		kAIHelpImagesFolderType = 53,
		kAIFontsCMapsFolderType = 54,
		kAIPresetSymbolsFolderType = 55,
		kAITsumeFolderType = 56,
		kAISpellingDictFolderType = 57,
		kAIPresetTemplatesFolderType = 58,
		kAIFontsCFFolderType = 59,
		kAIApplicationSupportCommonKinsokuSetFolderType = 60,
		kAIApplicationSupportCommonMojikumeSetFolderType = 61,
		kAIPresetBlankDocumentsFolderType = 62,
		kAIUserSupportCommonFontsFolderType = 63,
		kAIFontsCFTempFolderType = 64,
		kAILogsFolderType = 65,
		kAISampleArtFolderType = 66,
		kAISampleSVGFolderType = 67,
		kAISampleGraphDesignsFolderType = 68,
		kAISampleDataDrivenGraphicsFolderType = 69,
		kAIWorkspacesFolderType = 70,
		kAIPresetColorBooksFolderType = 71,
		kAIPresetLegacyColorBooksFolderType = 72,
		kAIPresetSwatchExchangeFolderType = 73,
		kAIApplicationSupportCommonLinguisticsFolderType = 74,
		kAIApplicationSupportCommonLinguisticsProvidersFolderType = 75,
		kAIVersionCueFolderType = 76, // Deprecated.
		kAIDemonstratorFolderType = 77,
		kAIResourcesFolderType = 78,
		kAICoolExtrasFolderType = 79,
		kAIOutputSettingsFolderType = 80,
		kAIStartupScriptsFolderType = 81,
		kAIDesktopFolderType = 82,
		kAIIllustratorFormatsFolderType = 83,
		kAIAdditionalAIPluginsFolderType = 84,
		kAIUserWritableStartupFileFolderType = 85,
		kAIUserWritablePresetBrushesFolderType = 86,
		kAIUserWritablePresetStylesFolderType = 87,
		kAIUserWritablePresetSwatchesFolderType = 88,
		kAIUserWritablePresetSwatchExchangeFolderType = 89,
		kAIUserWritablePresetSymbolsFolderType = 90,
		kAIPresetFlashPanelsFolderType = 91,
		kAIPresetKnowhowFolderType = 92,	//Deprecated
		kAIUserWritablePresetSettingsFolderType = 93,
		kAIUserWritablePresetOptimizeSettingsFolderType = 94,
		kAIUserWritablePresetOutputSettingsFolderType = 95,
		kAIUserWritablePresetColorTableSettingsFolderType = 96,
		kAIRequiredStartupProfilesFolderType = 97,
		kAIPresetWorkspacesFolderType = 98,
		kAIPresetKulerFolderType = 99,	//Deprecated
		kAIPresetWelcomeScreenFolderType = 100,
		kAIRequiredFolderType = 101,
		kAIRequiredResourcesFolderType = 102,
		kAIRequiredLocalizedResourcesFolderType = 103,
		kAIWSMgrCfgFolderType = 104,
		kAIModifiedWorkspacesFolderType = 105,
		kAIToolsFolderType = 106,
		kAIPreferencesRootFolderType = 107,
		kAIRequiredLinguisticsFolderType = 108,
        kAITemporayFolder = 109,
		kAIPresetChartsFolderType = 110,
        kAIMACSupportFilesFolderType = 111,
        kAIFrameworksDllsPath = 112,
		kAIUserLocalSupportFolderType = 113,
        kAIAMTParentFolderType = 114,
		kAIApplicationSupportCommonx86FolderType = 115,
		kAIRobinPluginsFolderType = 116,
		kAIModifiedPresetsToolsFolderType = 117,
		kAIPresetToolsFolderType = 118,

} AIFolderType;

/** Types of files that can be acquired by \c #AIFoldersSuite::GetFileName() */
typedef enum
{
	/** Temporary file */
	kAITemporaryFileType = 1

} AIFileType;


/*******************************************************************************
 **
 **	Suite
 **
 **/


/**	@ingroup Suites
	This suite provides functions to get the locations of the
	standard folders used by Illustrator.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIFoldersSuite and \c #kAIFoldersVersion.

	The following shows the layout of these folders and the corresponding identifiers.

<b>Local Hierarchy</b>

@verbatim
Adobe Illustrator x		<- kAIRootFolderType
	Adobe Illustrator x:	<- kAIPackageFolderType
  	  Contents:		<- kAIContentsFolderType
  	    Windows/MacOSClassic: <- kAIApplicationFolderType
  	      +Executable
  	      +Shared libraries
  	    Help:		<- kAIHelpFolderType
  	      +HTML Help Files
  	      images:		<- kAIHelpImagesFolderType
  	        +Help graphics
  	  Helpers:		<- kAIHelpersFolderType
  	    Preview In:		<- kAIPreviewInFolderType
  	  Required:		<- kAIRequiredFolderType
  	    +Required plug-ins
  	    Fonts:		<- kAIRequiredFontsFolderType
  	      +Required fonts
  	    Startup Profiles <- kAIRequiredStartupProfilesFolderType
		  +Startup files

  	Legal:		<- kAILegalFolderType
  	  +EULA

  	Plug-ins:	<- kAIPluginsFolderType (user can not change as of AI13)
			(kAIStartupFileFolderType, kAIRidersFileFolderType both point here)
  	  Extensions:
  	  Illustrator Filters:
  	  Illustrator Formats:	<- kAIIllustratorFormatsFolderType
  	  Photoshop Effects:
  	  Photoshop Filters:
  	  Photoshop Formats:
  	  Text Filters:
  	  Tools:	<- kAIToolsFolderType
  	  Tsume:	<- kAITsumeFolderType

  	Presets:	<- kAIPresetsFolderType
		(Note: The presets folder and subfolders are in the application directory and may not be writable.
		 To write settings files, use one of the kAIUserSupport folders or the kAIUserWritable folders.)
  	  Actions:	<- kAIPresetActionsFolderType
  	  Brushes:	<- kAIPresetBrushesFolderType
  	  Keyboard Shortcuts: <- kAIPresetKeyboardShortcutsFolderType
  	  Save for Web Settings: <- kAISettingsFolderType
  	    Color Tables: <- kAIColorTableSettingsFolderType
  	      +Color tables
  	    Optimize:	<- kAIOptimizeSettingsFolderType
  	      +Optimize settings
	    Output Settings:
	      +Output settings <- kAIOutputSettingsFolderType
  	  Scripts:	<- kAIPresetScriptsFolderType
  	  Styles:	<- kAIPresetStylesFolderType
  	  Swatches:	<- kAIPresetSwatchesFolderType + kAIPresetSwatchExchangeFolderType
  	    Color Systems: <- kAIPresetColorSystemsFolderType
		Color Books:	<- kAIPresetColorBooksFolderType
		  Legacy:	<- kAIPresetLegacyColorBooksFolderType
	    Gradients:	<- kAIPresetGradientsFolderType
  	    Patterns:	<- kAIPresetPatternsFolderType
  	  Symbols:	<- kAIPresetSymbolsFolderType
  	  Templates:	<- kAIPresetTemplatesFolderType
  	    Blank Documents: <- kAIPresetBlankDocumentsFolderType
	  Flash Panels: <- kAIPresetFlashPanelsFolderType
  	    Welcome Screen: <- kAIPresetWelcomeScreenFolderType
	  Workspaces:	<- kAIPresetWorkspacesFolderType
	  Tools:	<- kAIPresetToolsFolderType

  	Fonts:		<- kAIFontsFolderType
  	  CMaps:	<- kAIFontsCMapsFolderType

  	Sample Files:	<- kAISampleFilesFolderType
  	  Graph Designs: <- kAISampleGraphDesignsFolderType
  	  Sample Art:	<- kAISampleArtFolderType
  	    SVG:	<- kAISampleSVGFolderType
  	    Data-Driven Graphics: <- kAIDataDrivenGraphicsFolderType

  	StartupScripts:	<- kAIStartupScriptsFolderType

  	Utilities:	<- kAIUtilitiesFolderType
  @endverbatim

 <b> System Hierarchies </b>

  	The following describes the parts of the Illustrator directory hierarchy
  	that are located under system folders. The platform-specific directory
  	names are shown following.

   @verbatim
  	[PrimaryScratch]	<- kAIPrimaryScratchFolderType + primary scratch file location
  	[SecondaryScratch]	<- kAISecondaryScratchFolderType + secondary scratch file location
  	[AIPreferences]		<- kAIPreferencesFolderType + preferences file location + plug-in cache file location
  	[UserSupport]		<- kAIUserSupportFolderType
  		Adobe Illustrator X	<- kAIUserSupportAIFolderType
			Startup Templates: <- kAIUserWritableStartupFileFolderType
  			Plug-ins	<- kAIUserSupportAIPluginsFolderType + plug-ins available to current user
			Composite Fonts <- kAIFontsCFFolderType
			 Temp	<- kAIFontsCFTempFolderType
		    Brushes <- kAIUserWritablePresetBrushesFolderType
			Graphic Styles <- kAIUserWritablePresetStylesFolderType
			Swatches <- kAIUserWritablePresetSwatchesFolderType + kAIUserWritablePresetSwatchExchangeFolderType
			Symbols <- kAIUserWritablePresetSymbolsFolderType
			Save for Web Settings <- kAIUserWritablePresetSettingsFolderType
				Color Tables	<- kAIUserWritablePresetColorTableSettingsFolderType
				Optimize		<- kAIUserWritablePresetOptimizeSettingsFolderType
				Output Settings	<- kAIUserWritablePresetOutputSettingsFolderType
  		Fonts	<- kAIUserSupportCommonFontsFolderType
  	[ApplicationSupportCommon]	<- kAIApplicationSupportCommonFolderType
  		Color	<- kAIApplicationSupportCommonColorFolderType
  			Profiles	<- kAIApplicationSupportCommonColorProfilesFolderType
  			Settings	<- kAIApplicationSupportCommonColorSettingsFolderType
  		typeSpt	<- kAIApplicationSupportCommonTypeSupportFolderType
  			Kinsoku Sets	<- kAIApplicationSupportCommonKinsokuSetFolderType
  			Mojikume Sets	<- kAIApplicationSupportCommonMojikumeSetFolderType
  		Fonts	<- kAIApplicationSupportCommonFontsFolderType
  			Reqrd	<- kAIApplicationSupportCommonFontsReqrdFolderType
  				Base	<- kAIApplicationSupportCommonFontsReqrdBaseFolderType
  				cmaps	<- kAIApplicationSupportCommonFontsReqrdCMapsFolderType
  		PDFL	<- kAIApplicationSupportCommonPDFLFolderType
  			PDFL5.0	<- kAIApplicationSupportCommonPDFL5FolderType
  				cmaps	<- kAIApplicationSupportCommonPDFL5CMapsFolderType
  				fonts	<- kAIApplicationSupportCommonPDFL5FontsFolderType
  		Printspt	<- kAIApplicationSupportCommonPrintSupportFolderType
  		Workflow	<- kAIApplicationSupportCommonWorkflowFolderType
  		Linguistics	<- kAIApplicationSupportCommonLinguisticsFolderType
  			Providers	<- kAIApplicationSupportCommonLinguisticsProvidersFolderType
  				Proximity	<- kAIDictionariesFolderType, kAIHyphenationDictFolderType,kAISpellingDictFolderType (all point at same folder)
  	[MyDocuments]	<- kAIMyDocumentsFolderType + default documents file location
  	[PPDs]	<- kAIPrinterDescriptionsFolderType + PPD location
  	[Logs]	<- kAILogsFolderType
  	[AdditionalPlugins]	<- kAIAdditionalAIPluginsFolderType + additional plug-ins location (new in AI13, user can change in Preferences)
	@endverbatim

  <b> Platform-specific Directories </b>

  	\li Windows 2000
 @verbatim
  PrimaryScratch = System definition of temporary but can be changed by user
  SecondaryScratch = System definition of temporary but can be changed by user
  AIPreferences = Documents and Settings\username\Application Data\Adobe\Adobe Illustrator X
  UserSupport = Documents and Settings\username\Application Data\Adobe
  ApplicationSupportCommon = Program Files\Common Files\Adobe
  MyDocuments = Documents and Settings\username\My Documents
  PPDs = unknown
  Logs = Documents and Settings\username\Application Data\Adobe\Logs
  kAIResourcesFolderType = kAIApplicationFolderType
  kAIDesktopFolderType = CSIDL_DESKTOPDIRECTORY: The file system directory used
						   to physically store file objects on the desktop (not to 
						   be confused with the desktop folder itself). A typical 
						   path is C:\Documents and Settings\username\Desktop.
  AdditionalPlugins = Arbitrary location can be specified by user in Preferences
 @endverbatim

  	\li Mac OS X
 @verbatim
  PrimaryScratch = System definition of temporary but can be changed by user
  SecondaryScratch = System definition of temporary but can be changed by user
  AIPreferences = ~/Library/Preferences/Adobe Illustrator X
  UserSupport = ~/Library/Application Support/Adobe
  ApplicationSupportCommon = /Library/Application Support/Adobe
  MyDocuments = ~/Documents
  PPDs = Libraries/Printers/PPDs
  Logs = ~/Library/Logs/Adobe Illustrator CS
  kAIResourcesFolderType = kAIApplicationFolderType/Resources
  kAIDesktopFolderType = ~/Desktop
  AdditionalPlugins = Arbitrary location can be specified by user in Preferences
 @endverbatim

*/
struct AIFoldersSuite {

	/** Gets a path for an Illustrator folder.
			@param type The Illustrator folder to find.
			@param createFolder When true, creates a folder of the given type if it
				does not already exist.
			@param folder [out] A buffer in which to return the folder path.
		*/
	AIAPI AIErr (*FindFolder)(AIFolderType type, AIBoolean createFolder, ai::FilePath &folder);

	/** Retrieves the file-system name of an Illustrator folder.
			@param type The Illustrator folder.
			@param name [out] A buffer in which to return the name of the folder
				(not the full path). Must be of size \c #kMaxPathLength.
		*/
	AIAPI AIErr (*GetFolderName)(AIFolderType type, ai::UnicodeString &name);

	/** Creates a file path object for a temporary file. Generates a unique,
		temporary file name. Does not check whether the file exists.
			@param type The file type, must be \c #kAITemporaryFileType.
			@param file [out] A buffer in which to return the file path.
		*/
	AIAPI AIErr (*GetFileName)(AIFileType type, ai::FilePath &file);

};


#include "AIHeaderEnd.h"


#endif
