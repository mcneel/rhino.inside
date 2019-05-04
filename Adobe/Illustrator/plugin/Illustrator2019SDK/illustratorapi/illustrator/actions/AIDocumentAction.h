#ifndef _AICOREDOCUMENTACTION_H_
#define _AICOREDOCUMENTACTION_H_

/*
 *        Name:	AICoreDocumentAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Actions defined in the core.
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

#ifndef __AIActionManager_h__
#include "AIActionManager.h"
#endif

/** @ingroup Actions
	Makes a new document.
		@param #kAINewDocumentNameKey The document title string.
			Optional, default is "untitled-n" (with a unique number).
		@param #kAINewDocumentColorModelKey The color model to use.
			Allowed values are \c #kDocRGBColor and \c #kDocCMYKColor.
  		@param #kAINewDocumentSettingsFileKey Path to the profile used to
  			create the new document	(Unicode string)
		@param #kAINewDocumentWidthKey The page width in points (real).
		@param #kAINewDocumentHeightKey The page height in points (real).
		@param #kAINewDocumentRulerUnitsKey The ruler units,
			an \c #AIDocumentRulerUnitValue.
		@param #kAINewDocumentRasterResolutionKey The document raster resolution. (integer)
		@param #kAINewDocumentPreviewModeKey The preview mode for the document. (integer)
		@param #kAINewDocumentTransparencyGridKey True to show the transparency grid for
			the document.
	*/
#define kAINewDocumentAction							"adobe_newDocument"

/**	Parameter to \c #kAINewDocumentAction. The document title string.
	Optional, default is "untitled-n" (with a unique number).*/
const ActionParamKeyID kAINewDocumentNameKey			= 'name'; // string

/**	Parameter to \c #kAINewDocumentAction. The color model to use.
	Allowed values are \c #kDocRGBColor and \c #kDocCMYKColor. */
const ActionParamKeyID kAINewDocumentColorModelKey		= 'colr'; // integer

/** Parameter to \c #kAINewDocumentAction. Unicode string containing the path 
	to the new document profile file to use. These files are found in folders 
	\c #kAIUserWritableStartupFileFolderType and 
	\c #kAIRequiredStartupProfilesFolderType.
*/
const ActionParamKeyID kAINewDocumentSettingsFileKey	= 'setf'; // string

/**	The page width in points (real). */
const ActionParamKeyID kAINewDocumentWidthKey			= 'wdth'; // real

/**	Parameter to \c #kAINewDocumentAction. The page height in points (real). */
const ActionParamKeyID kAINewDocumentHeightKey			= 'heit'; // real

/**	Parameter to \c #kAINewDocumentAction. The ruler units,
	an \c #AIDocumentRulerUnitValue. */
const ActionParamKeyID kAINewDocumentRulerUnitsKey		= 'rulr'; // integer

/** Parameter to \c #kAINewDocumentAction. The document raster resolution,
	an integer for the PPI value: Screen(72), Medium(150), or High(300). */
const ActionParamKeyID kAINewDocumentRasterResolutionKey= 'rast'; // integer

/** Parameter to \c #kAINewDocumentAction. The preview style for the new document,
	an \c #AIPreviewMode constant. */
const ActionParamKeyID kAINewDocumentPreviewModeKey    = 'pxpr'; // integer

/** Parameter to \c #kAINewDocumentAction. True to show the transparency grid for
	the document, false to hide it. */
const ActionParamKeyID kAINewDocumentTransparencyGridKey = 'tran'; // bool


/** Parameter to \c #kAINewDocumentAction. If \c #kAINewDocumentTransparencyGridKey is true, the RGB values for the colors of the Transparency Grid
	*/
const ActionParamKeyID kAINewDocumentTransparencyGridColor1RedKey = 'gr1r';
const ActionParamKeyID kAINewDocumentTransparencyGridColor1GreenKey = 'gr1g';
const ActionParamKeyID kAINewDocumentTransparencyGridColor1BlueKey = 'gr1b';
const ActionParamKeyID kAINewDocumentTransparencyGridColor2RedKey = 'gr2r';
const ActionParamKeyID kAINewDocumentTransparencyGridColor2GreenKey = 'gr2g';
const ActionParamKeyID kAINewDocumentTransparencyGridColor2BlueKey = 'gr2b';

// -----------------------------------------------------------------------------
/** @ingroup Actions
	Opens a document
		@param #kAIOpenDocumentNameKey The name string of the file to open.
		@param #kAIOpenDocumentColorModelKey The color model to use.
			Allowed values are \c #kDocRGBColor and \c #kDocCMYKColor.
	*/
#define kAIOpenDocumentAction							"adobe_openDocument"
/**	Parameter to \c #kAIOpenDocumentAction. The name string of the file to open. */
const ActionParamKeyID kAIOpenDocumentNameKey			= 'name'; // string
/**	Parameter to \c #kAIOpenDocumentAction. The color model to use.
Allowed values are \c #kDocRGBColor and \c #kDocCMYKColor. */
const ActionParamKeyID kAIOpenDocumentColorModelKey		= 'colr'; // integer

// -----------------------------------------------------------------------------
/** @ingroup Actions
	Saves the current document under its current name, according to its
	current format. Takes no parameters. */
#define kAISaveDocumentAction							"adobe_saveDocument"

// -----------------------------------------------------------------------------
/** @ingroup Actions
	Saves the current document. The parameters allows you to specify the
	name and format. There can be additional parameters, depending on the
	file format; see \c AINativeAction.h and\c AISVGAction.h.
		@param #kAISaveDocumentAsNameKey	The name string of the file
			to save to. Optional. If not specified, shows a dialog to
			query user for the name.
		@param #kAISaveDocumentAsFormatKey The format string of the
			format to save to. Optional. If not specified, uses
 			the current format of the document. Use
 			\c #kAINativeFileFormat to save as a native file,
	 		\c #kAIEPSFileFormat to save as an EPS file.
		@param #kAISaveDocumentAsGetParamsKey When true, shows a dialog
			to query user for additional parameters required
			by the format. Optional. Default is false.
	*/
#define kAISaveDocumentAsAction							"adobe_saveDocumentAs"
/** Parameter to \c #kAISaveDocumentAsAction. The name string of the file to
save to. Optional. If not specified, shows
	a dialog to query user for the name. */
const ActionParamKeyID kAISaveDocumentAsNameKey			= 'name'; // string
/** Parameter to \c #kAISaveDocumentAsAction. The format string of the format
to save to. Optional. If not specified, uses
 	the current format of the document. See \c AINativeAction.h */
const ActionParamKeyID kAISaveDocumentAsFormatKey		= 'frmt'; // string
/** Parameter to \c #kAISaveDocumentAsAction. When true, shows a dialog to
query user for additional parameters required
	by the format. Optional. Default is false. */
const ActionParamKeyID kAISaveDocumentAsGetParamsKey	= 'gprm'; // bool


// -----------------------------------------------------------------------------
/** @ingroup Actions
	Reverts the current document to its state when last saved.
	Takes no parameters. */
#define kAIRevertDocumentAction							"adobe_revertDocument"

// -----------------------------------------------------------------------------
/** @ingroup Actions
	Closes the current document or all open documents.
		@param #kAICloseAllDocumentsKey When true, close all open document.
			When false, close only the current document.
		@param #kAICloseAndSaveDocumentKey When true, saves the document
			or documents before closing.
	*/
#define kAICloseDocumentAction							"adobe_closeDocument"
/** Parameter to \c #kAICloseDocumentAction. When true, close all open document.
When false, close only the current document. */
const ActionParamKeyID kAICloseAllDocumentsKey			= 'all.'; // bool
/** Parameter to \c #kAICloseDocumentAction. When true, saves the document
or documents before closing. */
const ActionParamKeyID kAICloseAndSaveDocumentKey		= 'save'; // bool

// -----------------------------------------------------------------------------
/** @ingroup Actions
	Exports the current document to the file format specified by the
	format and extension parameters. There may be additional parameters,
	depending on the file format; see the action information for the
	individual formats for the definitions.
		@param #kAIExportDocumentNameKey	The name string for the file
			to export as.
		@param #kAIExportDocumentFormatKey The format string. Optional.
			If not specified, shows the Export dialog. See the action
			information for individual formats for definitions of
	 		the format strings.
		@param #kAIExportDocumentExtensionKey The file extension string.
			Optional. If not specified, shows the Export dialog.
	*/
#define kAIExportDocumentAction							"adobe_exportDocument"
/** Parameter to \c #kAIExportDocumentAction. The name string for the file to export as. */
const ActionParamKeyID kAIExportDocumentNameKey			= 'name'; // string
/** Parameter to \c #kAIExportDocumentAction. The format string. Optional.
If not specified, shows the Export dialog.
	 See the action information for individual formats for definitions of
	 the format strings.*/
const ActionParamKeyID kAIExportDocumentFormatKey		= 'frmt'; // string
/** Parameter to \c #kAIExportDocumentAction. The file extension string. Optional.
If not specified, shows the Export dialog. */
const ActionParamKeyID kAIExportDocumentExtensionKey	= 'extn'; // string
/** Parameter to \c #kAIExportDocumentAction. When true, export multiple artboards specified in 
\c # kAIExportDocumentSaveAllKey or \c #kAIExportDocumentSaveRangeKey.
when false,export the complete artwork */
const ActionParamKeyID kAIExportDocumentSaveMultipleArtboardsKey	= 'smab'; // boolean
/** Parameter to \c #kAIExportDocumentAction. When true, export all artboards.
when false,export the artbaords in  \c #kAIExportDocumentSaveRangeKey specified */
const ActionParamKeyID kAIExportDocumentSaveAllKey	= 'sall'; // boolean
/** Parameter to \c #kAIExportDocumentAction. The artboards range string. Optional when 
\c # kAIExportDocumentSaveAllKey is true or  \c #kAIExportDocumentSaveMultipleArtboardsKey is false*/
const ActionParamKeyID kAIExportDocumentSaveRangeKey	= 'sran'; // string

const ActionParamKeyID kAIEnableBatchExport = 'ebep';						// string

const ActionParamKeyID kAIExportDocumentPreventFileNameUniquifyKey = 'pfnu'; // string
// -----------------------------------------------------------------------------
/** @ingroup Actions
	Prints the current document. Takes no parameters. */
#define kAIPrintDocumentAction							"adobe_printDocument"

// -----------------------------------------------------------------------------
/** @ingroup Actions
	Places a file into a document. Additional parameters can be specified
	for the action depending on the target file format. See the action
	information for individual formats for definitions of the additional
	parameters.
		@param #kAIPlaceDocumentActionNameKey The name string of the file
			to place.
		@param #kAIPlaceDocumentActionLinkKey When true, the file is linked.
			When false, the file is embedded.
		@param #kAIPlaceDocumentActionReplaceKey	 When true, the file replaces
			the current selection in the document.
		@param #kAIPlaceDocumentActionTemplateKey When true. creates a template
			layer and places the file in that layer.
	*/
#define kAIPlaceDocumentAction							"adobe_placeDocument"
/** Parameter to \c #kAIPlaceDocumentAction. The name string of the file to place. */
const ActionParamKeyID kAIPlaceDocumentActionNameKey	= 'name'; // string
/** Parameter to \c #kAIPlaceDocumentAction. When true, the file is linked.
When false, the file is embedded. */
const ActionParamKeyID kAIPlaceDocumentActionLinkKey	= 'link'; // bool
/** Parameter to \c #kAIPlaceDocumentAction. When true, the file replaces the
current selection in the document. */
const ActionParamKeyID kAIPlaceDocumentActionReplaceKey = 'rplc'; // bool
/** Parameter to \c #kAIPlaceDocumentAction. When true. creates a template layer
and places the file in that layer. */
const ActionParamKeyID kAIPlaceDocumentActionTemplateKey = 'tmpl'; // bool


#endif
