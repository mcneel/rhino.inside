#ifndef __AIFXGFileFormat__
#define __AIFXGFileFormat__

/*
*        Name:	AIFXGFileFormat.h
*      Author:
*        Date:
*     Purpose:	Adobe Illustrator FXG Suite.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2007-2008 Adobe Systems Incorporated.
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

#ifndef __AIDict__
#include "AIDictionary.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __IAIFilePath__
#include "IAIFilePath.hpp"
#endif

#ifndef __AIArray__
#include "AIArray.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIFXGFileFormat.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAIFXGFileFormatSuite					"AI FXG File Format Suite"
#define kAIFXGFileFormatSuiteVersion			AIAPI_VERSION(4)
#define kAIFXGFileFormatVersion					kAIFXGFileFormatSuiteVersion

/**
	FXG Version constants
*/
enum AIFXGVersion
{
	/**
		FXG version 1.0
	*/
	kAIFXGVersion1pt0 = 1,

	/**
		FXG version 2.0
	*/
	kAIFXGVersion2pt0 = 2,

	/**
		Default FXG Version
	*/
	kAIFXGDefaultVersion = kAIFXGVersion2pt0
};

/**
	Preserve policies to be used for object which may result in visual differences.
	See \c #AIFXGFileFormatSuite
*/
enum AIFXGPreservePolicy
{
	/** Preserves the appearance of AI art object by expanding it.
	*/
	kAIFXGPreserveAppearanceExpand = 1,

	/** Preserves the appearance of AI art object by rasterizing it.
	*/
	kAIFXGPreserveAppearanceRasterize,

	/**	Preserves the editibility of AI Art object by mapping directly to corresponding FXG tag.
		It may result in loss of appearance in target application.
	*/
	kAIFXGPreserveEditibility,

	/** Perserves editability whenever possible without altering the appearance. If appearance cannot be matched, expands or rasterizes art.
	*/
	kAIFXGPreserveAuto,

	/**	Default preserve policy for Text
	*/
	kAIFXGDefaultTextPreservePolicy = kAIFXGPreserveAuto,

	/**	Default preserve policy for FXG Filters
	*/
	kAIFXGDefaultFiltersPreservePolicy = kAIFXGPreserveEditibility,

	/** Default preserve policy for Gradients
	*/
	kAIFXGDefaultGradientsPreservePolicy = kAIFXGPreserveAuto,

};

/**
	Rasterize resolution to be used when an object will be rasterized if its appearance can not be preserved
	otherwise. See \c #AIFXGFileFormatSuite
*/
enum AIFXGRasterizeResolution
{
	/**  Resolution at 72 ppi
	*/
	kAIFXGResolutionScreen = 72,

	/**	Resolution at 150 ppi
	*/
	kAIFXGResolutionMedium = 150,

	/**	Resolution at 300 ppi
	*/
	kAIFXGResolutionHigh = 300,

	/**	Custom resolution, specified by another parameter of \c #AIFXGFileFormatSuite::SetFXGSaveRasterizeResolution()
	*/
	kAIFXGResolutionCustom = -1,

	/**	Default resolution
	*/
	kAIFXGDefaultRasterizeResoultion = kAIFXGResolutionScreen
};

/**  Type to hold FXG Save warnings. See \c #AIFXGFileFormatSuite
*/
typedef AIArrayRef	AIFXGSaveWarnings;

/**  Type to hold FXG Save options. See \c #AIFXGFileFormatSuite
*/
typedef AIDictionaryRef AIFXGFileFormatSaveParams;

///  Error codes
/**
	@ingroup Errors
	Invalid index is passed to \c #AIFXGFileFormatSuite::GetNthFXGSaveWarning()
*/
#define kFXGWarningNotFoundErr      '!FND'

/**
	Asset types that can be generated on save. See \c #AIFXGFileFormatSuite
*/
enum AIFXGAssetTypeEnum
{
	/** Main File
	*/
	kAIFXGAssetTypeMasterFile = 0,

	/** Artboard specific file
	*/
	kAIFXGAssetTypeArtboardFile = 1,

	/** Image file, either JPG, PNG or GIF
	*/
	kAIFXGAssetTypeImage = 2,

	/** XMP file
	*/
	kAIFXGAssetXMP = 3,

	/** Maximum allowed value
	*/
	kAIFXGAssetTypeMax = 0xFFFF
};

/**
	Expand option to be used for a particular art object. See \c #AIFXGWriteStreamInterface::GetExpandOptionForArt()
*/
enum AIFXGExpandArtOptionEnum
{
	/** Art will not be modified
	*/
	kAIFXGExpandArtOptionNone = 0,

	/**	Art will be rasterized
	*/
	kAIFXGExpandArtOptionRasterize = 1,

	/**	Art will be expanded using  \c #AIExpandSuite::Expand()
	*/
	kAIFXGExpandArtOptionExpand = 2,

	/** Art will be played without preserving appearance, will try to map editability in consuming app
	*/
	kAIFXGExpandArtOptionStructure = 3,

	/** Art will only have a placeholder group tag, this placeholder group will be replaced by
		another object on round-trip.
	*/
	kAIFXGExpandArtOptionPlaceholder = 4,

	/** Art will either be expanded, or rasterized based on the complexity of the art.
	*/
	kAIFXGExpandArtOptionAuto = 5,

	/** Default Expand option for Blends.
	*/
	kAIFXGDefaultExpandArtOptionBlends = kAIFXGExpandArtOptionAuto,


	/**  Maximum allowed value
	*/
	kAIFXGExpandArtOptionMax = 0xFFFF
};

/**
	Export flag to be used while exporting file to FXG.
*/
enum AIFXGExportFlagEnum
{
	/** Export the main file
	*/
	kAIFXGExportFlagMasterFile = 1,

	/**	Export the Artboard- specific files.
	*/
	kAIFXGExportFlagArtboards = 1 << 1,

	/** Export Main file as well as Artboard-specific files.
	*/
	kAIFXGExportFlagBoth = kAIFXGExportFlagMasterFile | kAIFXGExportFlagArtboards,

	/** Default value of this flag that can be used if you are not sure.
	*/
	kAIFXGExportFlagDefault = kAIFXGExportFlagMasterFile,

	/** Maximum allowed value 	*/
	kAIFXGExportFlagMax = 0xFFFF
};

/*******************************************************************************
**
**	Types
**
**/

/**
	Streaming interface to be supplied by the client, to be used when calling
	\c #AIFXGFileFormatSuite::ExportFXGToStream()
*/
struct AIFXGWriteStreamInterface {

	/**
		Callback to client to check whether an asset currently exists in an asset folder.
		@param stream   [in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream().
		@param assetType [in] The type of the asset, an \c #AIFXGAssetTypeEnum value.
		@param assetPath [in] The asset path.
		@return  True if the asset exists in the asset folder, false otherwise.
	*/
	AIAPI AIBoolean		(*IsExistingAsset) (AIFXGWriteStreamInterface* stream, ai::int16 assetType, const ai::UnicodeString& assetPath);

	/**
		Callback to client to open an asset.
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param assetType [in] Type of asset See \c AIFXGAssetTypeEnum
		@param assetName		[in/out] Name of asset. Client can change the input name, so that the export plug-in can use the changed name.
		@param mimeType		[in] Mime type of asset
		@return		\c #kCanceledErr if client does not want to receive further write and close calls for this particular open-asset call.
	*/
	AIAPI AIErr		(*BeginAsset)		(AIFXGWriteStreamInterface* stream, ai::int16 assetType, const ai::UnicodeString& assetName, const ai::UnicodeString& mimeType);

	/**
		Callback to client to close an opened asset.
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param	assetType	[in]	The asset type to close.
		@return \c #kNoErr on success
	*/
	AIAPI AIErr		(*EndAsset)			(AIFXGWriteStreamInterface* stream, ai::int16 assetType);

	/**
		Callback to client to write bytes to current stream. (Note that this function returns
		a constant value, not an error code.)
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param buffer [in] A buffer to write to current stream
		@param maxToWrite [in] The maximum number of bytes to write
		@return actual bytes written
	*/
	AIAPI size_t	(*WriteBytes)		(AIFXGWriteStreamInterface* stream, const ai::uint8* buffer, const size_t  maxToWrite);


	/**
		Callback to determine the appropriate expand setting for an art object.
		If client returns \c #kAIFXGExpandArtOptionExpand, it must fill \c expandFlags; see \c #AIExpandSuite::Expand() for flags,
		(Note that this function returns a constant value, not an error code.)
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param art [in]	The art for which an expand setting is needed.
		@param expandFlag [out] The expand flags setting when \c #kAIFXGExpandArtOptionExpand is returned.
		@return One of the values of  \c #AIFXGExpandArtOptionEnum, \c #kAIFXGExpandArtOptionNone for default processing.
	*/
	AIAPI ai::int16		(*GetExpandOptionForArt) (AIFXGWriteStreamInterface* stream, AIArtHandle art, ai::int32* expandFlags);

	/**
		Callback to report whether client wants private data generation for an art object.
		If not, application private data corresponding to the art is not written.
		 (Note that this function returns a constant value, not an error code.)
		@param stream	[in] The stream pointer which the client has passed to AIFXGFileFormatSuite::ExportFXGToStream
		@param art [in]	The art for which private data should be generated.
		@return True if client wants private data generation for this particular art, false otherwise.
	*/
	AIAPI AIBoolean (*GeneratePrivateDataForArt)(AIFXGWriteStreamInterface* stream, AIArtHandle art);

	/**
		Callback to retrieve the filepath/name of the current stream
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param pulicID [out] The filepath/name of the current stream. This is used in open-asset calls.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr		(*GetPublicID)		(AIFXGWriteStreamInterface* stream, ai::UnicodeString& publicID);

	/**
		Callback to retrieve the relative Image folder path, so that the \c BitmapGraphic FXG tag can create the
		proper relative path of the image source. For example, if client returns the path "MyFile.assets/images" and the image file name is MyImage.png,
		the entry in the \c BitmapGrapic tag is source="\@Embed('MyFile.assets/images/MyImage.png')".
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param relImageFolderPath [out] The relative path to the image folder.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr		(*GetRelativeImageFolderPath) (AIFXGWriteStreamInterface* stream, ai::UnicodeString& relImageFolderPath);

	/** Internal */
	AIAPI AIErr		(*DeleteAutoGeneratedImage)(AIFXGWriteStreamInterface* stream,const ai::UnicodeString& imageName);
};
/**
Stream interface to be passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
*/


/*******************************************************************************
**
**	Suite
**
**/

/** @ingroup Suites
This suite provides functions that allow you to export an AI document or art object to FXG.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIFXGFileFormatSuite and \c #kAIFXGFileFormatVersion.
*/
struct AIFXGFileFormatSuite{
	/**
		Creates an FXG save-options object with default values. This should be freed when no longer needed,
		using \c #DisposeFXGSaveParams()
		@param fxgSaveParams [out] Save options with default values.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*CreateFXGSaveParams) ( AIFXGFileFormatSaveParams* fxgSaveParams );

	/**
		Destroys the FXG save-options object created with \c #CreateFXGSaveParams()
		@param fxgSaveParams [in] The save-options object.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*DisposeFXGSaveParams) ( AIFXGFileFormatSaveParams fxgSaveParams );

	/**
		Retrieves the current FXG version value from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return The FXG version, an \c #AIFXGVersion value.
	*/
	AIAPI ai::int16 (*GetFXGSaveVersion) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the FXG save version value in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgVersion [in] The FXG version, an \c #AIFXGVersion value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveVersion) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgVersion);

	/**
		Retrieves the current "Save Illustrator Private Data" flag value from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if AI editing capabilities should be preserved using application private data.
	*/
	AIAPI AIBoolean (*GetFXGSavePreserveAIEditCapability) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Preserve AI Editing capabilities" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiEditCap [in] true if editing capabilities should be preserved, false other wise.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSavePreserveAIEditCapability) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean aiEditCap);

	/**
		Retrieves the current preserve policy for Text from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return  The preserve policy for Text, an \c #AIFXGPreservePolicy value.
	*/
	AIAPI ai::int16 (*GetFXGSaveTextPolicy) (const AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the preserve policy for Text in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgTextPreservePolicy [in] The preserve policy for Text, an \c #AIFXGPreservePolicy value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveTextPolicy) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgTextPreservePolicy);

	/**
		Retrieves the current preserve policy for FXG Filters from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return  The preserve policy for FXG Filters, an \c #AIFXGPreservePolicy value.
	*/
	AIAPI ai::int16 (*GetFXGSaveFilterPolicy) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the preserve policy for FXG Filters in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgFilterPreservePolicy [in] The preserve policy for FXG Filters, an \c #AIFXGPreservePolicy value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveFilterPolicy) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgFilterPreservePolicy);

	/**
		Retrieves the current preserve policy for Gradients from an FXG save-options object.
		(Note that this function returns
		a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return The preserve policy for Gradients, an \c #AIFXGPreservePolicy value.
	*/
	AIAPI ai::int16 (*GetFXGSaveGradientPolicy) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the preserve policy for Gradients in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgFilterPreservePolicy [in] The preserve policy for Gradients, an \c #AIFXGPreservePolicy value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveGradientPolicy) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgGradientPreservePolicy);

	/**
		Retrieves the "Include Symbols" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if All Symbols should be written in FXG, whether they are used or not.
	*/
	AIAPI AIBoolean (*GetFXGSaveIncludeSymbol) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Include Symbols" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiIncludeSymbol [in] True if all symbols should be exported, false if only used symbols should be exported
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveIncludeSymbol) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean aiIncludeSymbol);

	/**
		Retrieves the "Include XMP" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if XMP should be written in FXG,
	*/
	AIAPI AIBoolean (*GetFXGSaveIncludeXMP) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Include Symbols" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiIncludeXMP [in] True if XMP  should be exported.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveIncludeXMP) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean aiIncludeXMP);

	/**
		Retrieves the rasterize resolution from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param outCustomResolution [out] A custom resolution value if the returned value is \c #kAIFXGResolutionCustom
		@return The rasterize resolution, an \c #AIFXGRasterizeResolution value.
	*/
	AIAPI ai::int16 (*GetFXGSaveRasterizeResolution) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int32* outCustomResolution);

	/**
		Sets the rasterize resolution in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgRasterizeResolution [in] The rasterize resolution, an \c #AIFXGRasterizeResolution value.
		@param customResolution [in] A custom resolution if the resolution value is \c #kAIFXGResolutionCustom
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveRasterizeResolution) (AIFXGFileFormatSaveParams fxgSaveParams,
		ai::int16 fxgRasterizeResolution, ai::int32 customResolution);

	/**
		Retrieves the "Downsample Linked Images" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if linked images should be downsampled to 72 ppi, false otherwise.
	*/
	AIAPI AIBoolean (*GetFXGSaveDownsampleLinkedImages) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Downsample Linked Images" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiDownSampleLinkedImages [in] True if Linked images should be downsampled to 72 ppi, false otherwise.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveDownsampleLinkedImages) (AIFXGFileFormatSaveParams fxgSaveParams,  AIBoolean aiDownSampleLinkedImages);

	/**
		Retrieves the "WriteImages" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if images should also be written while exporting FXG. If false, images are not written, which is useful
			when user is interested in only the XML code.
	*/
	AIAPI AIBoolean (*GetFXGSaveWriteImages) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "WriteImages" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param writeImages [in] True if images should be written while exporting FXG, false otherwise.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveWriteImages) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean writeImages);

	/**
		Generates FXG to a file.
		@param art [in] Art which you want to export as FXG. Pass NULL to generate FXG for entire document.
		@param filepath [in] The file path for the master document FXG
		@param fxgSaveParams [in] The FXG save options parameters. See \c #AIFXGFileFormatSaveParams
		@param fxgExportFlags [in]  The export flags. See \c #AIFXGExportFlagEnum
		@param artBoardRange [in] If the export flag \c #kAIFXGExportFlagArtboards is passed, the artboard range.
		@param customProgressText [in] An optional message to display in the progress bar. If NULL, a default message is displayed.
		@param saveWarnings [out] A list to store warning message ids, which gets generated while saving to FXG. Dispose it via \c #DisposeFXGSaveWarnings().
			Pass NULL if you do not want to receive any warning messages.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*ExportFXGToFile) (AIArtHandle art, const ai::FilePath& filePath, AIFXGFileFormatSaveParams fxgSaveParams, ai::int32 fxgExportFlags, const ai::UnicodeString& artBoardRange, const ai::UnicodeString& customProgressText, AIFXGSaveWarnings* saveWarnings);

	/**
		Generates FXG to a stream through callbacks.
		@param art [in] The art which you want to export as FXG. Pass NULL to generate FXG for entire document.
		@param streamInterface [in] The stream implementation with callbacks, See \c #AIFXGWriteStreamInterface
		@param fxgSaveParams [in]  The FXG save options parameters. See \c #AIFXGFileFormatSaveParams
		@param fxgExportFlags [in]  The export flags. See \c #AIFXGExportFlagEnum
		@param artBoardRange [in]  If the export flag \c #kAIFXGExportFlagArtboards is passed, the artboard range.
		@param customProgressText [in] An optional message to display in the progress bar. If NULL, a default message is displayed.
		@param saveWarnings [out] A list to store warning message ids, which gets generated while saving to FXG. Dispose it via \c #DisposeFXGSaveWarnings().
			Pass NULL if you do not want to receive any warning messages.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*ExportFXGToStream) (AIArtHandle art, AIFXGWriteStreamInterface* streamInterface, AIFXGFileFormatSaveParams fxgSaveParams, ai::int32 fxgExportFlags, const ai::UnicodeString& artBoardRange, const ai::UnicodeString& customProgressText, AIFXGSaveWarnings* saveWarnings);

	/**
		Retrieves the current expand option for Blends from an FXG save-options object.
		(Note that this function returns
		a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return The expand option for Blends, an \c #AIFXGExpandArtOptionEnum value.
	*/
	AIAPI ai::int16 (*GetFXGSaveExpandOptionBlends) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the expand option for Blends in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgBlendsExpandOption [in] The preserve policy for Gradients, an \c #AIFXGExpandArtOptionEnum value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveExpandOptionBlends) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgBlendsExpandOption);

	/**
		Destroys the FXG save-warnings object created with \c #ExportFXGToFile() or \c #ExportFXGToStream()
		@param saveWarnings [in] The save-warnings object.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*DisposeFXGSaveWarnings)(AIFXGSaveWarnings saveWarnings);

	/**
		Retrieves the number of warnings stored in the FXG save-warnings object.
		(Note that this function returns a number, not an error code.)
		@param saveWarnings [in] The save-warnings object.
		@return The number of warnings.
	*/
	AIAPI ai::int32 (*GetFXGSaveWarningCount) (AIFXGSaveWarnings saveWarnings);

	/** Retrieves a warning from the FXG save-warnings object.
		@param saveWarnings The save-warnings object.
		@param index The 0-based position index of the warning.
		@param warningZStr [out] A buffer in which to return the warning string, in ZString format.
		Developer is responsible for translating to the appropriate language.
		@return \c #kNoErr if a warning is found at the given index, \c #kBadParameterErr if the index is invalid,
			\c #kFXGWarningNotFoundErr if index is valid but the warning string is empty.
	*/
	AIAPI AIErr (*GetNthFXGSaveWarning) (AIFXGSaveWarnings saveWarnings, ai::int32 index, ai::UnicodeString& warningZStr);

} ;


#include "AIHeaderEnd.h"



#endif //__AIFXGFileFormat__
