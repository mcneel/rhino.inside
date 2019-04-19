#ifndef __AIPerspectiveGrid__
#define __AIPerspectiveGrid__

/*
*		 Name:	AIPerspectiveGrid.h
*        Date:	Started 2009
*     Purpose:	Adobe Illustrator Perspective Grid suite. This suite lets
*				clients query different settings from the currently defined
*				Perspective Grid in the document.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2009 Adobe Systems Incorporated.
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

#include "AITypes.h"
#include "AIPerspectiveTransform.h"

#include "AIHeaderBegin.h"

/** @file AIPerspectiveGrid.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAIPerspectiveGridSuite					"AI Perspective Grid Suite"
#define kAIPerspectiveGridSuiteVersion			AIAPI_VERSION(3)
#define kAIPerspectiveGridVersion				kAIPerspectiveGridSuiteVersion

/** @ingroup Notifiers
	Sent when perspective grid parameters are changed.
*/
#define kAIPerspectiveParamsChangedNotifier		"AI Perspective Parameters Changed Notifier"

/** @ingroup Notifiers
	Sent when perspective grid visibility is changed.
*/
#define kAIPerspectiveGridVisibilityChangedNotifier		"AI Perspective Grid Visibility Changed Notifier"


/*******************************************************************************
**
** Types
**
**/

/** Type constants for perspective grid.
	@see \c #AIPerspectiveGridSuite */
enum PerspectiveGridType
{
	kInvalidGridType = 0,	///< Dummy value
	kOnePointGridType,		///< One-point grid
	kTwoPointGridType,		///< Two-point grid
	kThreePointGridType		///< Three-point grid
};

/*******************************************************************************
**
**	Suite
**
**/

/** @ingroup Suites
	This suite allows you to query and set parameters of the currently defined
	perspective grid in a document. It can also be used to convert points between
	artwork and perspective-grid coordinate systems. <br/>
	This example checks that a grid is currently defined, makes it visible, and
	translates the origin point on the left grid plane into artboard coordinates.
	@code
	Fn()
	{
		AIBoolean defined = sAIPerspectiveGrid->IsGridDefined();
		AIErr status = sAIPerspectiveGrid->ShowGrid(true);
		AIRealPoint pt = {0, 0};
		status = sAIPerspectiveGrid->PGPointToArtworkPoint(pt, kGridLeftPlane);
		//The point is now in artwork coordinates.
	}
	@endcode

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
	\c #kAIPerspectiveGridSuite and \c #kAIPerspectiveGridVersion.
*/
typedef struct {

	/** Reports whether the perspective grid is visible in the current document.
		(Note that this function returns a Boolean value, not an error code.)
			@return True if the perspective grid is visible.
	*/
	AIAPI AIBoolean (*IsGridVisible) ();

	/** Shows or hides the currently defined perspective grid in the current document.
			@param flag [in] True to make the perspective grid visible,
				false to hide it.
	*/
	AIAPI AIErr (*ShowGrid)(AIBoolean flag);

	/** Reports whether a perspective grid is defined in the current document.
		(Note that this function returns a Boolean value, not an error code.)
			@return True if a perspective grid is defined.
	*/
	AIAPI AIBoolean (*IsGridDefined)();

	/** Reports whether the currently defined perspective grid in the current document is locked.
		(Note that this function returns a Boolean value, not an error code.)
			@return True if the perspective grid is locked.
	*/
	AIAPI AIBoolean (*IsGridLocked)();

	/** Locks or unlocks the currently defined perspective grid in the current document.
			@param flag [in] True to lock the perspective grid, false to unlock it.
	*/
	AIAPI AIErr (*LockGrid)(AIBoolean flag);

	/** Reports whether the station point of the currently defined perspective grid
		in the current document is locked.
		(Note that this function returns a Boolean value, not an error code.)
			@return True if station point is locked.
	*/
	AIAPI AIBoolean (*IsGridStationPointLocked)();

	/** Locks or unlocks the station point of the currently defined perspective grid
		in the current document.
			@param flag [in] True to lock the station point, false to unlock it.
	*/
	AIAPI AIErr (*LockGridStationPoint)(AIBoolean flag);

	/** Reports whether rulers are visible in the currently defined perspective grid
		in the current document.
		(Note that this function returns a Boolean value, not an error code.)
			@return True if rulers are visible.
	*/
	AIAPI AIBoolean (*IsGridRulerVisible)();

	/** Shows or hides the rulers in the currently defined perspective grid
			in the current document.
			@param flag [in] True to show rulers, false to hide them.
	*/
	AIAPI AIErr (*ShowGridRuler)(AIBoolean flag);

	/** Reports whether snap-to-grid is enabled in the currently defined perspective grid
		in the current document.
		(Note that this function returns a Boolean value, not an error code.)
			@return True if snap-to-grid is enabled.
	*/
	AIAPI AIBoolean (*IsSnapToGridEnabled)();

	/** Enables or disables snap-to-grid in the currently defined perspective grid
		in the current document.
			@param flag [in] True to enable, false to disable snap-to-grid.
	*/
	AIAPI AIErr (*SnapToGrid)(AIBoolean flag);

	/** Retrieves the snapping tolerance value of the currently defined perspective grid
		in the current document.
			@param snapTolerance [out] A buffer in which to return the snapping tolerance value.
	*/
	AIAPI AIErr (*GetGridSnapTolerance) (AIReal& snapTolerance);

	/** Sets the default perspective-grid preset (the two-point grid) as the active preset in the current document.
	*/
	AIAPI AIErr (*SetDefaultPreset)();

	/** Converts global ruler coordinates into perspective grid coordinates.
			@param pt [in/out] A buffer in which to pass the original point and return the converted point.
			@param plane [in] The perspective-grid plane containing the point.
	*/	
	AIAPI AIErr (*ArtworkPointToPGPoint) (AIRealPoint& pt, GridPlaneType plane);

	/** Converts perspective grid coordinates into global ruler coordinates.
			@param pt [in/out] A buffer in which to pass the original point and return the converted point.
			@param plane [in] The perspective-grid plane containing the point.
	*/	
	AIAPI AIErr (*PGPointToArtworkPoint)(AIRealPoint& pt, GridPlaneType plane);

	/** Retrieves the ruler unit of currently defined perspective grid in the current document.
			@param unit [out] A buffer in which to return the unit.
	*/
	AIAPI AIErr (*GetPGRulerUnit)(AIUnits& unit);

	/** Switches between multiple planes of the currently defined perspective grid
		 in the current document.
	*/
	AIAPI AIErr	(*SwitchActivePlane) ();

	/** Sets the active plane of the currently defined perspective grid
		in the current document.
			@param gridPlane The plane to make active.
	*/
	AIAPI AIErr	(*SetActivePlane) (GridPlaneType gridPlane);

	/** Retrieves the active plane of the currently defined perspective grid
		in the current document.
			@param out_gridPlaneType [out] A buffer in which to return the active plane constant.
	*/
	AIAPI AIErr	(*GetActivePlane) (GridPlaneType& out_gridPlaneType);

	/** Retrieves the type of the currently defined perspective grid in the current document.
			@param out_gridType [out] A buffer in which to return the type constant.
	*/
	AIAPI AIErr	(*GetActiveGridType) (PerspectiveGridType& out_gridType);

	/** Switches between multiple planes of the currently defined perspective grid
		in the current document, using keyboard shortcut keys. Call from a
		drag loop to allow the user to switch planes using shortcut keys during the
		drag operation.	This is handled automatically by perspective-aware tools;
		that is those that set the option \c #kToolWantsAlternateSelectionTool.
	*/
	AIAPI AIErr	(*SwitchActivePlaneFromKB) ();

} AIPerspectiveGridSuite;

#include "AIHeaderEnd.h"

#endif // __AIPerspectiveGrid__
