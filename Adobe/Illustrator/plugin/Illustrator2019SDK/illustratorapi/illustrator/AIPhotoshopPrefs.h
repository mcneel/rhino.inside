#ifndef __AIPhotoshopPrefs_h__
#define __AIPhotoshopPrefs_h__
/*
 *        Name:	AIPhotoshopPrefs.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1996-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/*
	A subset of the definitions found in the Preferences.h, PhotoshopDefs.h,
	and ColorModes.h files, which were taken from the Illustrator 9 PlugInDev 
	source tree.
	
	...PluginDev:PhotoshopFileFormat:Src:New:Preferences.h
	...PluginDev:PhotoshopFileFormat:Src:PhotoshopDefs.h
	...PluginDev:PhotoshopFileFormat:Src:New:ColorModes.h
	
	This subset contains only the definitions needed to call the Photoshop
	export plug-in from another plug-in, using the public SDK interfaces.
	
	2/21/00		Andy Bachorski
	
	
	Writers:

		(afb)		Andy Bachorski

	Change History (most recent first):
			 
			 9/14/01	afb		Add missing #include of AIRaster.h (for definition of uint8).
			 4/23/01	mgupta	Added PSD prefixes to most of the constants

	  < >	 3/22/01	afb		Updated to match definitions in Preferences.h
	  
*/


#include "AIRaster.h"

#include "AIHeaderBegin.h"

// ------------------------------------------------------------------
//	mgupta, moved from PhotoshopDefs.h	
//	Color space constants for the menu items
//	and preferences.
const ai::uint8 kRasterizeToRGB = 1;
const ai::uint8 kRasterizeToCMYK = 2;
const ai::uint8 kRasterizeToGrayscale = 3;
const ai::uint8 kRasterizeToBitmap = 4;


// ------------------------------------------------------------------
//	mgupta, moved from ColorModes.h	
//	These are the output color spaces 
//	that a user can choose, for writing
//	his psd files.  These values are
//	button id's in the user interface:

enum PSDPluginColorMode		// ex. PluginColorMode
{
	ePluginRGB			= kRasterizeToRGB,
	ePluginCMYK			= kRasterizeToCMYK,
	ePluginGrayscale	= kRasterizeToGrayscale,
	ePluginDummy		= 0xFFFFFFFF
}; //omit unsupported modes.

enum PSDExportFormat
{
	eTextNotLive					= 0,			// Export Text As Raster.Scripting plug-in may use this flag.
	eUnsupportedTextFormat			= eTextNotLive, // the text can not be exported in available export formats so export as raster.
	ePhotoshop8						= 1 << 0,
	ePhotoshop6						= 1 << 1
};

enum AntiAliasOptions
{
	ANTIALIAS_NONE = 0,
	ANTIALIAS_AGM = 1,
	ANTIALIAS_SUPERSAMPLING
};

// ------------------------------------------------------------------------------------
//	Grace 5/21/98
//	Move from Preferences.cpp
//	
//	mgupta April 4, 2001
//	Added default defines

#define kPSDPreferencePrefix					"PhotoshopFileFormat"

#define kPSDFormatName							"Photoshop psd"
#define kPSDExportFormatName					"Photoshop PSD Export"
#define kPSDImportFormatName					"Photoshop PSD Import"
#define kPSDFormatExtn							"psd,psb,pdd"

//rbansal 20010521 Adding the keys for Import Options
#define kPSDImportOption						"PSD Import Option"
#define kDefaultPSDImportOption					1 //rbansal 20010528 dfaukt option change to Layers to Objects

#define kPSDImportImageMaps						"ImageMaps"
#define kDefaultPSDImportImageMaps				true

#define kPSDImportSlices						"Slices"
#define kDefaultPSDImportSlices					true
//end import slices

#define kPSDImportHiddenLayers					"HiddenLayers"
#define kDefaultPSDImportHiddenLayers			false

//Layer Comps
#define kPSDShowPreview							"ShowPreview"
#define kDefaultPSDShowPreview					true		

#define kPSDSelectedLayerCompID					"SelectedLayerCompID"
#define kPSDDefaultSelectedLayerCompID          -1

#define kPSDSelectedLayerCompName				"SelectedLayerCompName"
#define kPSDDefaultLayerCompName				""

#define kPSDAntiAliasPref						"AntiAlias"
#define kPSDDefaultAntiAliasPref				ANTIALIAS_SUPERSAMPLING

#define kPSDColorModelPref						"ColorModel"
#define kPSDDefaultColorModelPref				ePluginRGB

#define kPSDExportFormatPref					"ExportFormat"
#define kPSDDefaultExportFormatPref				ePhotoshop8

#define kPSDDPIPref								"DPI"
#define kPSDDefaultDPIPref						_ShortToAIReal(150)

//	mgupta, 04/27/01
//	This item will store the custom value the user may have entered
//	ABTS Bug #426012
#define kPSDOtherDPIPref						"CustomDpi"

#define kPSDWriteLayersPref						"WriteLayers"
#define kPSDDefaultWriteLayerPref				true

#define kPSDWhichProfile						"WhichProfile"

#define kPSDHiddenLayersPref					"HiddenLayers"
#define kPSDDefaultHiddenLayersPref				false

#define kPSDWriteNestedLayersAsLayersPref		"NestedLayers"
#define kPSDDefaultWriteNestedLayersPref		true

#define kPSDLiveTextPref						"LiveText"
#define kPSDDefaultLiveTextPref					true

#define kPSDWriteSlicesPref						"Slices"
#define kPSDDefaultWriteSlicesPref				true

#define kPSDWriteImageMapsPref					"ImageMaps"
#define kPSDDefaultImageMapsPref				true

#define kPSDWriteCompoundShapesPref				"CompoundShapes"
#define kPSDDefaultCompoundShapesPref			true

#define kPSDWriteMaxEditabilityPref				"Maximize Ediability"
#define kPSDDefaultMaxEditabilityPref			true

//	[mgupta: 5/31/2001] ABTS #431842 
#define kPSDNoHiddenLayersWarning				"NoHiddenLayersWarning"
#define kPSDNo100LayersWarning					"No100LayersWarning"
#define kPSDNoImageMapsWarning					"NoImageMapsWarning"
#define kPSDNoSelectiveMergeWarning				"NoSelectiveMergeWarning"

#define kPSDSuppressUnsupportedDepthWarning		"SuppressUnsupportedDepthWarning"
#define kPSDApplyPixelAspectRatio				"PixelAspectRatio"

#define kPSDDefaultTurnOffWarningPref			false

// [hsuri: 5/12/2012] Option to preserve spot color information
#define kPSDPreserveSotColors					"PreserveSpotColors"

#define kPSDSpotOptionsApplyToAll				"SpotOptionApplyToAll"
#define kPSDSpotOptions							"SpotOptions"
#define kPSDSuppressSwatchConflictWarning		"SuppressSwatchConflictWarning"

#define kPSDSuppressNonSquarePixelWarning		"SuppressNonSquarePixelWarning"
#define kPSDSuppressLibrarySpotInkWarning		"LibrarySpotInkWarning"
#define kAIPSScriptCallSelector					"AI Script"
// ------------------------------------------------------------------------------------

struct PSDExportPrefs		//ex. PluginPrefs
{
	ai::int32			mWhichProfile;
	AntiAliasOptions			mAntiAlias;
	AIBoolean			mWriteLayers;
	AIReal				mResolution;	// dots per inch
	PSDPluginColorMode  mColorModel;
	AIBoolean			mIncludeHiddenLayers;
	AIBoolean			mWriteNestedLayersAsLayers;	//nchandra
	AIBoolean			mLiveText;
	AIBoolean			mNo100LayersWarning;
	AIBoolean			mNoImageMapsWarning;
	AIBoolean			bHasSelectiveMerge;
	AIBoolean			mNoSelectiveMergeWarning;	//Ac.
	AIBoolean			mNoHiddenLayersWarning;
	AIBoolean			mWriteSlices;			//mgupta++
	AIBoolean			mWriteImageMaps;		//mgupta++
	AIBoolean			mWriteCompoundShapes;	//mgupta++
	AIReal				mOtherResolution;		//mgupta++
	ai::int32			mExportFormat;
	AIBoolean			mMaxEditability;
	AIBoolean			mPreserveSpotColors;
};


//	nchandra: 20000212 Added this enum for the import types
//	retain transparency is coupled with the psLayersToFlat
enum PSDImportOptions
{
	noImport = 0,
	psLayersToAIObjects = 1,
	psLayersToAIFlat = 2
};

enum PSDUpdateLinkOptions
{
	psKeepLayerVisibilityOverrides = 0,
	psUsePhotoshopLayerVisibility = 1,
	psUpdateLinkNotApplicable = 2	
};

struct PSDImportPrefs
{
	//Actual import parameters
	PSDImportOptions		mImportOption;
	PSDUpdateLinkOptions	mUpdateLinkOption;
	AIBoolean			bImportImageMaps;
	AIBoolean			bImportSlices;

	//previous values. used in conjunction with current import operation to
	//determine enabling/disabling of controls in import dialog box
	AIBoolean			mHasReadableLayers;
	AIBoolean			bPreviousImportImageMaps;
	AIBoolean			bPreviousImportSlices;
	PSDImportOptions	mPreviousOption;
	AIBoolean			mDontChangePreviousIMapImportStatus;
	AIBoolean			mDontChangePreviousSliceImportStatus;
	AIBoolean			mDontChangePreviousHiddenLayerImportStatus;

	AIBoolean			bNotDragDrop;
	AIBoolean           mColorModeMismatch;

	AIBoolean           bApplyPixelAspectRatioCorrection;
	AIBoolean           bCBPixelAspectRatioChecked;
	AIReal				mPixelAspectRatio;

	AIBoolean			bShowLayerCompsPreview;
	AIBoolean			bImportHiddenLayers;
	AIBoolean			bPreviousImportHiddenLayers;
	AIBoolean			bReadImageDone;
	ai::int32				iSelectedLayerCompIndex;
};

#include "AIHeaderEnd.h"

#endif //__AIPhotoshopPrefs_h__
