#ifndef __AIArtboards__
#define __AIArtboards__
/*
* Name: AIArtboard.h
* Author: Started by Pushp
* Date: November, 2008
* Purpose: Adobe Illustrator Artboard Suite
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

/*******************************************************************************
**
**	Imports
**
**/

#include "IAIArtboards.hpp"
#include "IAIAutoBuffer.h"

#include "AIHeaderBegin.h"

/** @file AIArtboard.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAIArtboardSuite				"AI Artboard Suite"
#define kAIArtboardSuiteVersion			AIAPI_VERSION(4)
#define kAIArtboardVersion				kAIArtboardSuiteVersion

/*******************************************************************************
**
** Types
**
**/

/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
This suite provides utilities that allow you to create and manipulate
Artboards in a document. A document is associated with an \c ArtboardList object
that contains multiple \c Artboard objects, each of which is associated with and
\c ArtboardProperties object.
@note It is recommended that you use the wrapper class, \c #ai::ArtboardProperties and \c #ai::ArtboardList
rather than calling these functions directly.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIArtboardSuite and \c #kAIArtboardSuiteVersion.

*/
struct AIArtboardSuite{
	/** Initializes an artboard properties object with default values.
	@param artboard The artboard properties object.
	*/
	AIAPI AIErr (*Init)(ai::ArtboardProperties& artboard);

	/** Duplicates an artboard object.
	@param artboard The artboard properties object to clone.
	@param newArtboard [out] A buffer in which to return the new artboard properties object.
	*/
	AIAPI AIErr (*CloneArtboard)(ai::ArtboardProperties& artboard,const ai::ArtboardProperties& newArtboard);

	/**
	Disposes of an artboard properties object.
	@param artboard The artboard properties object.
	*/
	AIAPI AIErr (*Dispose)(ai::ArtboardProperties& properties);

	/** Retrieves the position and bounds of an artboard.
	@param properties The artboard properties object.
	@param bounds [out] A rectangle object in which to return the position and bounds of the artboard.
	*/
	AIAPI AIErr (*GetPosition)(const ai::ArtboardProperties& properties, AIRealRect& bounds);

	/** Modifies the position and bounds of an artboard.
	Call \c #AIArtboardSuite::Update() with this object to make the change.
	@param properties The artboard properties object.
	@param bounds The new position and bounds.
	*/
	AIAPI AIErr (*SetPosition)(ai::ArtboardProperties& properties,const AIRealRect& bounds);

	/** Retrieves the pixel aspect ratio of the artboard ruler.
	@param properties The artboard properties object.
	@param par [out] A buffer in which to return the pixel aspect ratio.
	*/
	AIAPI AIErr (*GetPAR)(const ai::ArtboardProperties& properties, AIReal& par);

	/** Modifies the pixel aspect ratio of the artboard ruler.
	Call \c #AIArtboardSuite::Update() with this object to make the change.
	@param properties The artboard properties object.
	@param  par The new pixel aspect ratio.
	*/
	AIAPI AIErr (*SetPAR)(ai::ArtboardProperties& properties,AIReal par);

	/* Retrieves the name associated with an artboard.
	@param properties The artboard properties object.
	@param name [out] A buffer in which to return the name.
	*/
	AIAPI AIErr (*GetName)(const ai::ArtboardProperties& properties, ai::UnicodeString& name);

	/* Sets the name associated with an artboard.
	@param properties The artboard properties object.
	@param name The new name.
	*/
	AIAPI AIErr (*SetName)(ai::ArtboardProperties& properties, const ai::UnicodeString& name);

	/** Reports whether a particular type of artboard annotation is currently shown.
	@param properties The artboard properties object.
	@param  type The annotation type.
	@param	show A buffer in which to return true if the type is shown, false if it is hidden.
	*/
	AIAPI AIErr (*GetShowDisplayMark)(const ai::ArtboardProperties& properties,ai::ArtboardProperties::DisplayMarkType type, AIBoolean& show);

	/* Sets the display state of a particular type of artboard annotation.
	@param properties The artboard properties object.
	@param  type The annotation type.
	@param	show True to show, false to hide the annotation type.
	*/
	AIAPI AIErr (*SetShowDisplayMark)(ai::ArtboardProperties& properties,ai::ArtboardProperties::DisplayMarkType type, AIBoolean show);
	/** Retrieves the artboard list of the current document.
	@param artboardList [out] A buffer in which to return the artboard list object.
	*/
	AIAPI AIErr (*GetArtboardList)(ai::ArtboardList& artboardList);

	/** Releases an artboard list object.
	@param artboardList The artboard list object.
	*/
	AIAPI AIErr (*ReleaseArtboardList)(ai::ArtboardList& artboardList);

	/** Adds a new artboard to the current document and reports its index position in the artboard list.
	@param artboardList The artboard list object.
	@param newArtboard The new artboard's properties object.
	@param index [out] A buffer in which to return the 0-based index position of the new artboard.
	@return  The error \c #kAIExceededMaxArtboardLimitErr if list size exceeds the application-defined limit.
	*/
	AIAPI AIErr (*AddNew)(ai::ArtboardList& artboardList,ai::ArtboardProperties& newArtboard, ai::ArtboardID& index);

	/** Deletes an artboard from an artboard list, and makes the next one in the list active.
	The last artboard cannot be deleted.
	@param artboardList The artboard list object.
	@param index The 0-based index position of the artboard to delete from the list.
	@return The error \c #kAICantDeleteLastArtboardErr if you attempt to delete the last artboard.
	*/
	AIAPI AIErr (*Delete)(ai::ArtboardList& artboardList,ai::ArtboardID index);

	/** Retrieves the number of artboards defined in an artboard list.
	@param artboardList The artboard list object.
	@param count [out] A buffer in which to return the number of artboards.
	*/
	AIAPI AIErr (*GetCount)(const ai::ArtboardList& artboardList,ai::ArtboardID& count);

	/** Retrieves the index position of the active artboard in the document's list.
	@param artboardList The artboard list object.
	@param index [out] A buffer in which to return the 0-based index of the active artboard, or
	-1 if there are no artboards in the current document.
	*/
	AIAPI AIErr (*GetActive)(const ai::ArtboardList& artboardList,ai::ArtboardID& index);

	/** Makes a specific artboard active, and makes it current in the iteration order.
	@param artboardList The artboard list object.
	@param index The 0-based index position of the artboard in the list.
	*/
	AIAPI AIErr (*SetActive)(ai::ArtboardList& artboardList, ai::ArtboardID index);

	/** Updates the properties of an artboard. Use with \c #GetCount() and \c #GetArtboardProperties()
	to modify the artboard without changing which artboard is active in the document.
	@param artboardList The artboard list object.
	@param index The 0-based index position of the artboard in the document list.
	@param properties The object containing the new artboard properties.
	*/
	AIAPI AIErr (*Update)(ai::ArtboardList& artboardList, ai::ArtboardID index, const ai::ArtboardProperties& properties);

	/** Retrieves the properties of an artboard from an artboard list.
	Use with \c #GetCount() and \c #Update() to modify an artboard without
	changing which artboard is active in the document.
	@param artboardList The artboard list object.
	@param index The 0-based index position of the artboard in the list.
	@param properties [out]	A buffer in which to return	the artboard properties object.
	On error, returns an invalid object
	*/
	AIAPI AIErr (*GetArtboardProperties)(ai::ArtboardList& artboardList, ai::ArtboardID index, ai::ArtboardProperties& properties);

	/** Retrieves the ruler origin of an artboard, relative to left-bottom corner.
	@param properties The artboard properties object.
	@param rulerOrigin [out] A buffer in which to return ruler origin.
	*/
	AIAPI AIErr (*GetRulerOrigin)(const ai::ArtboardProperties& properties, AIRealPoint& rulerOrigin);

	/** Sets the ruler origin of the artboard, relative to left-bottom corner.
	@param properties The artboard properties object.
	@param rulerOrigin The new ruler origin.
	*/
	AIAPI AIErr (*SetRulerOrigin)(ai::ArtboardProperties& properties, const AIRealPoint& rulerOrigin);

	/** Inserts a new Artboard at the specified location.
	@param artboardList The ArtboardList object.
	@param artboard The new artboard's properties.
	@param index 0-based index position of the new artboard.
	@return The error \c #kAIExceededMaxArtboardLimitErr if maximum number of allowed artboards is exceeded.
	*/
	AIAPI AIErr (*Insert)(ai::ArtboardList& artboardList,ai::ArtboardProperties& artboard, ai::ArtboardID& index);

	/** Reports whether an artboard's current name is application-generated. When this is the case,
	and the user chooses to export art as JPEG, and to save artboards as separate files, the files
	are distinguished only by number, rather than the full generated name; for example, myArt-01.jpg.
	When an artboard name has been explicitly set, that name is used in the exported JPEG filename.

	@param properties The artboard properties object.
	@param isDefault A buffer in which to return true if the name is generated, false
	if it has been explicitly set.
	*/
	AIAPI AIErr (*IsDefaultName)(const ai::ArtboardProperties& properties, AIBoolean& isDefault);

	/** Internal. Do not use.
	*/
	AIAPI AIErr (*SetIsDefaultName)(ai::ArtboardProperties& properties,const AIBoolean& isDefault);

	/** Query artboard selection
	@param properties		The artboard properties object.
	@param isSelected [out]	A buffer in which to return the selection
	*/
	AIAPI AIErr (*IsSelected)(const ai::ArtboardProperties& properties, AIBoolean &isSelected);
	
	/** Select one artboard
	@param artboardList		The ArtboardList object.
	@param artboardID		The artboard to select.
	@param exclusively		if true, clear existing selection first.
	*/
	AIAPI AIErr (*SelectArtboard)(ai::ArtboardList& artboardList, ai::ArtboardID artboardID, AIBoolean exclusively);

	/** Select multiple artboards
	@param artboardList		The ArtboardList object.
	@param artboardIDs		The artboards to select.
	@param exclusively		if true, clear existing selection first.
	*/
	AIAPI AIErr (*SelectArtboards)(ai::ArtboardList& artboardList, const ai::AutoBuffer<ai::ArtboardID>& artboardIDs, AIBoolean exclusively);

	/** Select all artboards
	@param artboardList		The ArtboardList object.
	*/
	AIAPI AIErr (*SelectAllArtboards)(ai::ArtboardList& artboardList);

	/** Delete set of artboards
	@param artboardList		The ArtboardList object.
	@param artboardIDs		The artboards to delete.
	*/
	AIAPI AIErr (*DeleteArtboards)(ai::ArtboardList& artboardList, const ai::AutoBuffer<ai::ArtboardID>& artboardIDs);

	/** Deselect an artboard
	@param artboardList		The ArtboardList object.
	@param artboardID		The artboard to de-select.
	*/
	AIAPI AIErr (*DeselectArtboard)(ai::ArtboardList& artboardList, ai::ArtboardID artboardID);

	/** Deselect all artboards
	@param artboardList		The ArtboardList object.
	*/
	AIAPI AIErr (*DeselectAllArtboards)(ai::ArtboardList& artboardList);

	AIAPI AIErr(*AreAnyArtboardsOverlapping)(ai::ArtboardList &artboardList, AIBoolean &isOverlapping);

};

#include "AIHeaderEnd.h"

#endif // __AIArtboards__