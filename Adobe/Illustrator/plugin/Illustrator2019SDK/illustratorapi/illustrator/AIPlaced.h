#ifndef __AIPlaced__
#define __AIPlaced__

/*
 *        Name:	AIPlaced.h
 *   $Revision: 25 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Placed Object Suite.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef _AIRaster_
#include "AIRaster.h"
#endif

#include "IAIFilePath.hpp"

#include "AIHeaderBegin.h"

/** @file AIPlaced.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIPlacedSuite			"AI Placed Suite"
#define kAIPlacedSuiteVersion9	AIAPI_VERSION(9)
#define kAIPlacedSuiteVersion	kAIPlacedSuiteVersion9
#define kAIPlacedVersion		kAIPlacedSuiteVersion


/** Types of placed object. */
enum AIPlacedObjectType {
	/** EPS file */
	kEPSType = 0,
	/** Not EPS */
	kOtherType
};

/** Methods for positioning and sizing a linked object.
	@see \c #AIPlacedSuite::SetPlaceOptions(), \c #AIPlacedSuite::GetPlaceOptions() */
enum PlaceMethod {
	/** Preserve original dimensions regardless of bounding box size and transformations. */
	kAsIs,
	/** Fill bounding box while preserving proportions. Can overlap edges in one dimension. */
	kFill,
	/** Fit fully inside bounding box while preserving proportions. */
	kFit,
	/** Fit to bounding box; replaced file preserves bounds but not proportions. */
	kConform,
	/** Fit to bounding box; replaced file preserves transformations and tries to preserve size.
		Default. */
	kReconform
};

/** Alignment options for positioning a linked object.
	@see \c #AIPlacedSuite::SetPlaceOptions(), \c #AIPlacedSuite::GetPlaceOptions() */
enum PlaceAlignment {
	kTopLeft,
	kMidLeft,
	kBotLeft,

	kTopMid,
	kMidMid,
	kBotMid,

	kTopRight,
	kMidRight,
	kBotRight
};

/** Request types for \c #AIPlacedSuite::ExecPlaceRequest(). */
typedef enum PlaceRequestMode {
	/** Place the file. If the new art can be read, places it, and
		returns the new art handle in \c #AIPlaceRequestData::m_hNewArt.*/
	kVanillaPlace = 0,
	/** Consult selection for whether to place or replace.
		\li If exactly one placed object is selected, show "File.Place" dialog
			to query user on whether to simply place the new art, or use it
			to replace the selection.
		\li If there is no selection, or if more than one placed object is
			selected,  simply places the new art and returns the
			new art handle in \c #AIPlaceRequestData::m_hNewArt. */
	kQueryReplace,
	/** Replace the file. The art to be replaced must be in
		\c #AIPlaceRequestData::m_hOldArt. */
	kForceReplace,
	/** Replace placed art with its parsed contents. Returns the group
		containing the new art tree in \c #AIPlaceRequestData::m_hNewArt. */
	kUnlinkPlaced,
	/** Create new art in current layer's top group, if allowed by that
		layer's editability and visibility states.. You must specify the art
		type you want created in \c #AIPlaceRequestData::m_lParam. Returns the
		new art handle in \c #AIPlaceRequestData::m_hNewArt.	*/
	kCreateNewArt,
	/** Replace the file, first validating the \c #SPPlatformFileSpecification.
		The art to be replaced must be in \c #AIPlaceRequestData::m_hOldArt.*/
	kForceReplaceEx,
	/** Replace placed art with its parsed contents, querying user
		for parameters. Returns the group containing the new art tree
		in  \c #AIPlaceRequestData::m_hNewArt.*/
	kQueryUnlinkPlaced
} ePlaceRequestMode;

/** Flag value to represent plates used by Placed object */
typedef enum
{
	/** Placed object has Black(K) Plate */
	kAIPlacedHasBlack    =                    (1<<0),
	/** Placed object has Cyan Plate */
	kAIPlacedHasCyan     =                    (1<<1),
	/** Placed object has Magenta Plate */
	kAIPlacedHasMagenta  =                    (1<<2),
	/** Placed object has Yellow Plate */
	kAIPlacedHasYellow   =                    (1<<3),
	/** Placed object has at least one spot Plate */
	kAIPlacedHasCustomColors =                (1<<4)
} AIPlacedPlateInfo;


typedef enum 
{
	/*Default Place Type will be done, with no position size changed of placed art*/
	kAIPlaceTransformTypeNone = 0,
	/*Art will be transformed w.r.t to current zoom and fit to current view*/
	kAIPlacedTransformTypeFitToView = 1

} AIPlaceTransformType;


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Request data for \c #AIPlacedSuite::ExecPlaceRequest().
	Initialize all fields, even when not expecting to use them.
*/
struct AIPlaceRequestData
{
	AIPlaceRequestData() : m_lPlaceMode(0), m_hOldArt(NULL), m_hNewArt(NULL), m_pFilePath(NULL), m_lParam(0), m_filemethod(0), m_disableTemplate(false), m_doShowParamDialog(false), m_PlaceTransformType(kAIPlaceTransformTypeNone){}

	/** The type of placement request, a \c #PlaceRequestMode constant
		which determines what operation is performed. */
	ai::int32 m_lPlaceMode;

	/** Art to be replaced. */
	AIArtHandle m_hOldArt;

	/** Returns the handle for new art that was placed or created. */
	AIArtHandle m_hNewArt;

	/** File path of the placed file. If \c NULL, shows a File Place dialog
		to query the user for the path and any relevant placement options. */
	const ai::FilePath *m_pFilePath;

	/** The type of art to create for the \c #kCreateNewArt request,
		an \c #AIArtType value. */
	ai::int32 m_lParam;

	/** 0 to place or import the file, 1 to link the file. */
	ai::int16 m_filemethod;

	/** True to disable the Template placement option. */
	ASBoolean m_disableTemplate;

	/** True to show the parameters dialog even when the file path is known. */
	AIBoolean m_doShowParamDialog;

	/** to trigger what kind of placement you want */
	AIPlaceTransformType m_PlaceTransformType;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/


/**	@ingroup Suites
	This suite provides functions that allow you to access and manipulate
	\e placed \e art. Illustrator uses placed art to link artwork contained
	in external files into an Illustrator document. For a file to be linked,
	there must be an installed file-format plug-in that supports linking the format.

	A placed object is defined by its file specification and a matrix positioning
	the file content in the document.

	After creating an empty placed object, use \c #SetPlacedBoundingBox() to
	set initial bounds, then call \c #AIArtSuite::UpdateArtworkLink() to read
	the content of the referenced file. If the file is read successfully,
	the initial bounds are replaced by the true bounds from the file. If the read fails,
	the bounds are not changed, and, if this function were not used to
	set them, the result would be a placed object without width or height.

	All file types except EPS also have a group of art objects that represents
	the parsed contents of the file.When a file-format plug-in is requested to
	link a file other than an EPS, it does the following:

	\li Creates a placed object for the linked file, setting its file specification
		to reference the file.
	\li Calls \c #SetPlacedObject() to create a group to contain the artwork
		representing the content of the linked file.
	\li Reads the content of the linked file, creating the artwork to represent
		the content.
	\li Sets the matrix of the placed object as needed to position the content
		in the document.

	The transformation matrix of a placed image is the concatenation of all of the
	transforms applied to the image after it has been placed. The matrix begins as
	a simple translate which positions the image on the page. You can also rotate,
	scale and shear the image.

	Placement options control how a linked image is positioned and scaled
	relative to the bounds of the placed object. Placement is
	adjusted whenever the image size changes; that is, when the file changes
	on disk, or when it is explicitly relinked with \c #SetPlacedFileSpecification().
	The replacement image can be placed into the bounds of the original object, or
	the bounds of the original object can be scaled, and the replacement placed
	into the resulting bounds.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPlacedSuite and \c #kAIPlacedVersion.
 */
typedef struct AIPlacedSuite {

	/** Retrieves the file specification for the linked file of a placed object.
		If the linked file does not exist, the returned file specification
	    supplies only the file name.
			@param placed The placed object.
			@param file [out] A buffer in which to return the file specification.
		*/
	AIAPI AIErr (*GetPlacedFileSpecification) ( AIArtHandle placed, ai::FilePath &file );

	/** Associates a placed object with a linked file. If the file is an EPS,
		immediately parses the contents and acquires the PICT preview.
		Otherwise, defers parsing until you request it with
		\c #AIArtSuite::UpdateArtworkLink() or \c #AIDocumentSuite::UpdateLinks().
			@param placed The placed object.
			@param file The file specification. If this identifies an EPS, i
	 	*/
	AIAPI AIErr (*SetPlacedFileSpecification) ( AIArtHandle placed, const ai::FilePath &file );

	/** Retrieves the transformation matrix that positions the content of a placed art object's
		linked file in the document. Use with \c #SetPlacedMatrix() to modify the transformation.
			@param placed The placed object.
			@param matrix [out] A buffer in which to return the transformation matrix.
			@see \c #ConcatPlacedMatrix()
		*/
	AIAPI AIErr (*GetPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *matrix );

	/** Sets the transformation matrix of a placed art object. The matrix includes
		the simple translate that places the image on the page, as well as any rotate,
		scale, and shear values. Use with \c #GetPlacedMatrix() to modify the transformation.
			@param placed The placed object.
			@param matrix The new transformation matrix.
			@see \c #ConcatPlacedMatrix()
		*/
	AIAPI AIErr (*SetPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *matrix );

	/** Retrieves the boundary dimensions of placed art, regardless of the
		transformations applied to it.
			@param placed The placed object.
			@param bbox [out] A buffer in which to return the bounding rectangle.
		*/
	AIAPI AIErr (*GetPlacedBoundingBox) ( AIArtHandle placed, AIRealRect *bbox );

	/** Creates or clears and returns a group art object to hold the parsed content of
		the linked file for a placed object. File-format plug-ins call this when reading
		the content of a linked file.
			@param placed The placed object.
			@param group [out] A buffer in which to return the group art object.
		*/
	AIAPI AIErr (*SetPlacedObject) ( AIArtHandle placed, AIArtHandle *group );

	/** Gets the number of custom colors used by a placed art object for an EPS file. Use with
		\c #GetNthPlacedCustomColorName() to iterate through the colors and get their names.
			@param art The placed object.
			@param count [out] A buffer in which to return the number of spot colors.
			@return The error \c #kBadParameterErr if the linked file is not an EPS.
			@see \c #AICustomColorSuite.
		*/
	AIAPI AIErr (*CountPlacedCustomColors) ( AIArtHandle art, ai::int32 *count );

	/** Retrieves the name of custom color used by a placed art object for an EPS file.
		Use with \c #CountPlacedCustomColors to iterate through the custom colors.
			@param art The placed art object.
			@param num The 0-based position index of the color.
			@param name [out] A buffer in which to return the color name.
			@return The error \c #kBadParameterErr if the linked file is not an EPS.
		*/
	AIAPI AIErr (*GetNthPlacedCustomColorName) ( AIArtHandle art, ai::int32 num, ai::UnicodeString& name );

	/** Changes a linked placed-art or raster-art object to an  embedded art object.
			@param placed The art object, of type \c #kPlacedArt or \c #kRasterArt.
			@param native [out] A buffer in which to return the new embedded art object.
			@param askForParam When true, show dialog for user input if needed.
		*/
	AIAPI AIErr (*MakePlacedObjectNative) ( AIArtHandle placed, AIArtHandle *native, AIBoolean askForParam );

	/** Retrieves the type of a placed object (EPS or other file type).
			@param placed The art object, of type \c #kPlacedArt or \c #kRasterArt.
			@param pPlacedType [out] A buffer in which to return the type constant,
				an \c #AIPlacedObjectType value.
		*/
	AIAPI AIErr (*GetPlacedType) ( AIArtHandle placed, ai::int16 *pPlacedType );

	/** Retrieves the art group representing the parsed content of the
		non-EPS linked file for a placed object.
			@param placed The placed object.
			@param group [out] A buffer in which to return the art group object.
			@return The error \c #kBadParameterErr if the linked file is not an EPS.
		*/
	AIAPI AIErr (*GetPlacedChild) ( AIArtHandle placed, AIArtHandle *group );

	/** Executes a  request related to a placed object.
		The request can place or replace the art, either explicitly
		or in relation to the current selection.
			@param placeRequestData An \c #AIPlaceRequestData structure in which to
				specify the request and return results.
		*/
	AIAPI AIErr (*ExecPlaceRequest)( AIPlaceRequestData &placeRequestData );

	/** Retrieves the file information for a placed object's linked file (such
		as the creation and modification dates), as stored from the most recent
		file read operation.
			@param placed The placed object.
			@param spFileInfo [out] A buffer in which to return the file information.
			@note Compare this file information (stored with the placed object)
				to the current information for the file itself (\c #GetPlacedFileInfoFromFile())
				to determine if the file has changed.
		*/
	AIAPI AIErr (*GetPlacedFileInfoFromArt)( AIArtHandle placed, SPPlatformFileInfo *spFileInfo );

	/** Retrieves the file information for a placed object's linked file (such
		as the creation and modification dates), from the file itself (as opposed to
		the file information stored with the object).
			@param placed The placed object.
			@param spFileInfo [out] A buffer in which to return the file information.
			@see  \c #GetPlacedFileInfoFromArt()
		*/
	AIAPI AIErr (*GetPlacedFileInfoFromFile)( AIArtHandle placed, SPPlatformFileInfo *spFileInfo );

	/** Retrieves the path specification for the file associated with a placed-art object.
			@param placed The placed object.
			@param path [out] A buffer in which to return the platform-specific file path string.
	 	*/
	AIAPI AIErr (*GetPlacedFilePathFromArt)( AIArtHandle placed, ai::UnicodeString &path );

	/** Concatenates a new transformation onto the existing transformation matrix
		for a placed object.
			@param placed The placed object.
			@param concat The new transformation matrix.
		*/
	AIAPI AIErr (*ConcatPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *concat );

	// New for Illustrator 10

	/** Sets the placement options for a placed object, used to scale and place the
		linked image relative to the bounds of the placed object. Placement is
		adjusted whenever the image size changes; that is, when the file changes
		on disk, or when it is explicitly relinked with \c #SetPlacedFileSpecification().
			@param placed The placed object.
			@param method The way to position and size the linked object.
			@param alignment The way to align the linked object
			@param clip	True to clip the linked object.
	*/
	AIAPI AIErr (*SetPlaceOptions) ( AIArtHandle placed, enum PlaceMethod method, enum PlaceAlignment alignment, AIBoolean clip );

	/** Retrieves the placement options for a placed object. See \c #SetPlaceOptions().
			@param placed The placed object.
			@param method [out] A buffer in which to return the method used to position and size the linked object.
			@param alignment [out] A buffer in which to return the alignment of the linked object.
			@param clip	[out] A buffer in which to return true if the linked object is clipped.
		*/
	AIAPI AIErr (*GetPlaceOptions) ( AIArtHandle placed, enum PlaceMethod *method, enum PlaceAlignment *alignment, AIBoolean *clip );

	/** Retrieves the size, placement, and transformation of a placed object itself,
		and of its linked image.The matrices are those used to transform the object and
		image from the original bounds to their current locations on the screen.
		With the \c #kConform placement option, these are the same.
			@param placed The placed object.
			@param size [out] A buffer in which to return the size (the X and Y dimensions)
				of the original image.
			@param viewBounds [out] A buffer in which to return the bounding box of the placed object.
			@param viewMatrix [out] A buffer in which to return the transformation matrix of the placed object.
			@param imageBounds [out] A buffer in which to return the bounding box of the linked image.
			@param imageMatrix [out] A buffer in which to return the transformation matrix of the linked image.
		*/
	AIAPI AIErr (*GetPlacedDimensions) ( AIArtHandle placed, AIRealPoint *size, AIRealRect *viewBounds, AIRealMatrix *viewMatrix,
			AIRealRect *imageBounds, AIRealMatrix *imageMatrix );

	// New for Illustrator 12

	/** Sets the preliminary bounding box information for a placed object.
			@param art The placed object.
			@param bbox The bounding rectangle.
		*/
	AIAPI AIErr (*SetPlacedBoundingBox) ( AIArtHandle art, AIRealRect* bbox );

	/** Retrieves the raster record describing the image for a placed object
		that represents a placed, linked image.
			@param art The placed object.
			@param info [out] A buffer in which to return the information.
			@param israster [out] A buffer in which to return if the placed object
				does represent an image, false if it does not.
		*/
	AIAPI AIErr (*GetRasterInfo) ( AIArtHandle art, AIRasterRecord* info, AIBoolean* israster );
	/** Gets the process colors plates used by a placed art object for an EPS file or a placed, linked image.
			@param art The placed object.
			@param plateInfo [out]  A buffer in which to return which plates are used by the placed object
		*/
	AIAPI AIErr (*GetProcessPlatesInfo) (AIArtHandle art, AIPlacedPlateInfo * plateInfo);
	
} AIPlacedSuite;

#include "AIHeaderEnd.h"

#endif
