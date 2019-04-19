#ifndef _AICOREOBJECTACTION_H_
#define _AICOREOBJECTACTION_H_

/*
 *        Name:	AICoreObjectAction.h
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
	Invokes a menu command
		@param #kAIDoMenuCommandIdKey The command identifier.
	*/
#define kAIDoMenuCommandAction								"adobe_commandManager"
/** Parameter to \c #kAIDoMenuCommandAction. The command identifier of the menu item to run. */
const ActionParamKeyID kAIDoMenuCommandIdKey				= 'cmid'; // integer

/** @ingroup Actions
	Translates the position of the selected objects.
		@param #kAITranslateSelectionHorizontalKey The horizontal offset in points.
		@param #kAITranslateSelectionVerticalKey The vertical offset in points.
		@param #kAITranslateSelectionCopyKey When true, translate a copy of the objects.
		@param #kAITranslateSelectionObjectsKey When true, translate the object geometry.
		@param #kAITranslateSelectionPatternsKey When true, translate patterns.
	*/
#define kAITranslateSelectionAction							"adobe_move"
/** Parameter to \c #kAITranslateSelectionAction. The horizontal offset in points. */
const ActionParamKeyID kAITranslateSelectionHorizontalKey	= 'hozn'; // real
/** Parameter to \c #kAITranslateSelectionAction. The vertical offset in points. */
const ActionParamKeyID kAITranslateSelectionVerticalKey		= 'vtcl'; // real
/** Parameter to \c #kAITranslateSelectionAction. When true, translate a copy of the objects. */
const ActionParamKeyID kAITranslateSelectionCopyKey			= 'copy'; // bool
/** Parameter to \c #kAITranslateSelectionAction. When true, translate the object geometry. */
const ActionParamKeyID kAITranslateSelectionObjectsKey		= 'objt'; // bool
/** Parameter to \c #kAITranslateSelectionAction. When true, translate patterns. */
const ActionParamKeyID kAITranslateSelectionPatternsKey		= 'patn'; // bool

/** @ingroup Actions
	Rotates the selected objects.
		@param #kAIRotateSelectionAngleKey The angle of rotation in degrees.
		@param #kAIRotateSelectionAboutDXKey The horizontal offset of the origin with
			respect to the center of the selection.
		@param #kAIRotateSelectionAboutDYKey The vertical offset of the origin with
			respect to the center of the selection.
		@param #kAIRotateSelectionCopyKey When true, rotate a copy of the objects.
		@param #kAIRotateSelectionObjectsKey When true, rotate the object geometry.
		@param #kAIRotateSelectionPatternsKey When true, rotate patterns.
	*/
#define kAIRotateSelectionAction							"adobe_rotate"
/** Parameter to \c #kAIRotateSelectionAction. The angle of rotation in degrees. */
const ActionParamKeyID kAIRotateSelectionAngleKey			= 'angl'; // real
/** Parameter to \c #kAIRotateSelectionAction. The horizontal offset of the origin with
			respect to the center of the selection. */
const ActionParamKeyID kAIRotateSelectionAboutDXKey			= 'detX'; // real
/** Parameter to \c #kAIRotateSelectionAction. The vertical offset of the origin with
			respect to the center of the selection. */
const ActionParamKeyID kAIRotateSelectionAboutDYKey			= 'detY'; // real
/** Parameter to \c #kAIRotateSelectionAction. When true, rotate a copy of the objects. */
const ActionParamKeyID kAIRotateSelectionCopyKey			= 'copy'; // bool
/** Parameter to \c #kAIRotateSelectionAction. When true, rotate the object geometry. */
const ActionParamKeyID kAIRotateSelectionObjectsKey			= 'objt'; // bool
/** Parameter to \c #kAIRotateSelectionAction. When true, rotate patterns. */
const ActionParamKeyID kAIRotateSelectionPatternsKey		= 'patn'; // bool


/** @ingroup Actions
	Scales the selected objects.
		@param #kAIScaleSelectionUniformKey	When true, scale is uniform.
		@param #kAIScaleSelectionLinesKey When true, scale stroke weights.
		@param #kAIScaleSelectionUniformScaleKey The scale factor for uniform scaling.
		@param #kAIScaleSelectionHorizontalKey The horizontal scale factor for non-uniform scaling.
		@param #kAIScaleSelectionVerticalKey The vertical scale factor for non-uniform scaling.
		@param #kAIScaleSelectionAboutDXKey	The horizontal offset of the origin with
			respect to the center of the selection.
		@param #kAIScaleSelectionAboutDYKey	The vertical offset of the origin with
			respect to the center of the selection.
		@param #kAIScaleSelectionCopyKey When true, scale a copy of the objects.
		@param #kAIScaleSelectionObjectsKey	When true, scale the object geometry.
		@param #kAIScaleSelectionPatternsKey When true, scale patterns.
	*/
#define kAIScaleSelectionAction	 "adobe_scale"
/** Parameter to \c #kAIScaleSelectionAction. When true, scale is uniform. */
const ActionParamKeyID kAIScaleSelectionUniformKey			= 'unfm'; // bool
/** Parameter to \c #kAIScaleSelectionAction. When true, scale stroke weights. */
const ActionParamKeyID kAIScaleSelectionLinesKey			= 'line'; // bool
/** Parameter to \c #kAIScaleSelectionAction. The scale factor for uniform scaling. */
const ActionParamKeyID kAIScaleSelectionUniformScaleKey		= 'scle'; // real
/** Parameter to \c #kAIScaleSelectionAction. The horizontal scale factor for non-uniform scaling.*/
const ActionParamKeyID kAIScaleSelectionHorizontalKey		= 'hozn'; // real
/** Parameter to \c #kAIScaleSelectionAction. The vertical scale factor for non-uniform scaling. */
const ActionParamKeyID kAIScaleSelectionVerticalKey			= 'vtcl'; // real
/** Parameter to \c #kAIScaleSelectionAction. The horizontal offset of the origin with
			respect to the center of the selection.*/
const ActionParamKeyID kAIScaleSelectionAboutDXKey			= 'detX'; // real
/** Parameter to \c #kAIScaleSelectionAction. The vertical offset of the origin with
			respect to the center of the selection. */
const ActionParamKeyID kAIScaleSelectionAboutDYKey			= 'detY'; // real
/** Parameter to \c #kAIScaleSelectionAction. When true, scale a copy of the objects. */
const ActionParamKeyID kAIScaleSelectionCopyKey				= 'copy'; // bool
/** Parameter to \c #kAIScaleSelectionAction. When true, scale the object geometry. */
const ActionParamKeyID kAIScaleSelectionObjectsKey			= 'objt'; // bool
/** Parameter to \c #kAIScaleSelectionAction. When true, scale patterns. */
const ActionParamKeyID kAIScaleSelectionPatternsKey			= 'patn'; // bool


/** @ingroup Actions
	Reflects the selected objects.
		@param #kAIReflectSelectionAngleKey	The angle of the axis of reflection in degrees.
		@param #kAIReflectSelectionAboutDXKey The horizontal offset of the origin with
			respect to the center of the selection.
		@param #kAIReflectSelectionAboutDYKey The vertical offset of the origin with
			respect to the center of the selection.
		@param #kAIReflectSelectionCopyKey When true, reflect a copy of the objects.
		@param #kAIReflectSelectionObjectsKey When true, reflect the object geometry.
		@param #kAIReflectSelectionPatternsKey When true, reflect patterns.
	*/
#define kAIReflectSelectionAction							"adobe_reflect"
/** Parameter to \c #kAIReflectSelectionAction. The angle of the axis of reflection in degrees. */
const ActionParamKeyID kAIReflectSelectionAngleKey			= 'angl'; // real
/** Parameter to \c #kAIReflectSelectionAction. The horizontal offset of the origin with
			respect to the center of the selection.  */
const ActionParamKeyID kAIReflectSelectionAboutDXKey		= 'detX'; // real
/** Parameter to \c #kAIReflectSelectionAction. The vertical offset of the origin with
			respect to the center of the selection.  */
const ActionParamKeyID kAIReflectSelectionAboutDYKey		= 'detY'; // real
/** Parameter to \c #kAIReflectSelectionAction. When true, reflect a copy of the objects. */
const ActionParamKeyID kAIReflectSelectionCopyKey			= 'copy'; // bool
/** Parameter to \c #kAIReflectSelectionAction. When true, reflect the object geometry. */
const ActionParamKeyID kAIReflectSelectionObjectsKey		= 'objt'; // bool
/** Parameter to \c #kAIReflectSelectionAction. When true, reflect patterns. */
const ActionParamKeyID kAIReflectSelectionPatternsKey		= 'patn'; // bool

/** @ingroup Actions
	Reflects the selected objects.
		@param #kAIShearSelectionShearAngleKey The amount of shearing in degrees.
		@param #kAIShearSelectionAngleKey The angle along which to shear in degrees.
		@param #kAIShearSelectionAboutDXKey	The horizontal offset of the origin with
			respect to the center of the selection.
		@param #kAIShearSelectionAboutDYKey	The vertical offset of the origin with
			respect to the center of the selection.
		@param #kAIShearSelectionCopyKey When true, shear a copy of the objects.
		@param #kAIShearSelectionObjectsKey	When true, shear the object geometry.
		@param #kAIShearSelectionPatternsKey When true, shear patterns.
	*/
#define kAIShearSelectionAction								"adobe_shear"
/** Parameter to \c #kAIShearSelectionAction. The amount of shearing in degrees. */
const ActionParamKeyID kAIShearSelectionShearAngleKey		= 'shag'; // real
/** Parameter to \c #kAIShearSelectionAction. The angle along which to shear in degrees. */
const ActionParamKeyID kAIShearSelectionAngleKey			= 'angl'; // real
/** Parameter to \c #kAIShearSelectionAction. The horizontal offset of the origin with
			respect to the center of the selection. */
const ActionParamKeyID kAIShearSelectionAboutDXKey			= 'detX'; // real
/** Parameter to \c #kAIShearSelectionAction. The vertical offset of the origin with
			respect to the center of the selection. */
const ActionParamKeyID kAIShearSelectionAboutDYKey			= 'detY'; // real
/** Parameter to \c #kAIShearSelectionAction. When true, shear a copy of the objects. */
const ActionParamKeyID kAIShearSelectionCopyKey				= 'copy'; // bool
/** Parameter to \c #kAIShearSelectionAction. When true, shear the object geometry. */
const ActionParamKeyID kAIShearSelectionObjectsKey			= 'objt'; // bool
/** Parameter to \c #kAIShearSelectionAction. When true, shear patterns.. */
const ActionParamKeyID kAIShearSelectionPatternsKey			= 'patn'; // bool

/** @ingroup Actions
	Repeats the most recent transformation on the selected objects. */
#define kAITransformSelectionAgainAction					"adobe_transformAgain"


/** @ingroup Actions
	Brings the selected objects to the front of the paint order.	*/
#define kAISendSelectionToFrontAction						"adobe_sendToFront"
/** @ingroup Actions
	Sends the selected objects to the back of the paint order.	*/
#define kAISendSelectionToBackAction						"adobe_sendToBack"
/** @ingroup Actions
	Brings the selected objects forward in the paint order.	*/
#define kAISendSelectionForwardAction						"adobe_sendForward"
/** @ingroup Actions
	Sends the selected objects backward in the paint order.	*/
#define kAISendSelectionBackwardAction						"adobe_sendBackward"


/** @ingroup Actions
	Cuts the selected objects.	*/
#define kAICutSelectionAction								"adobe_cut"
/** @ingroup Actions
	Copies the selected objects to the clipboard. */
#define kAICopySelectionAction								"adobe_copy"
/** @ingroup Actions
	Clears the selection.	*/
#define kAIClearSelectionAction								"adobe_clear"


/** @ingroup Actions
	Pastes objects from the clipboard into the current document.	*/
#define kAIPasteClipboardAction								"adobe_paste"
/** @ingroup Actions
	Pastes objects from the clipboard into the current document at the
	front of the paint order.	*/
#define kAIPasteClipboardInFrontAction						"adobe_pasteInFront"
/** @ingroup Actions
	Pastes objects from the clipboard into the current document at the
	back of the paint order.	*/
#define kAIPasteClipboardInBackAction						"adobe_pasteInBack"


/** @ingroup Actions
	Selects all objects in the current document.	*/
#define kAISelectAllAction									"adobe_selectAll"
/** @ingroup Actions
	Deselects all objects in the current document.	*/
#define kAIDeselectAllAction								"adobe_deselectAll"


/** @ingroup Actions
	Groups selected objects.	*/
#define kAIGroupSelectionAction								"adobe_group"
/** @ingroup Actions
	Ungroups selected objects.	*/
#define kAIUngroupSelectionAction							"adobe_ungroup"


/** @ingroup Actions
	Locks selected objects.	*/
#define kAILockSelectionAction								"adobe_lock"
/** @ingroup Actions
	Unlocks all objects.	*/
#define kAIUnlockAllAction									"adobe_unlockAll"


/** @ingroup Actions
	Hides selected objects.	*/
#define kAIHideSelectionAction								"adobe_hideSelection"
/** @ingroup Actions
	Shows all objects.	*/
#define kAIShowAllAction									"adobe_showAll"

/** @ingroup Actions
	Removes the currently selected anchor points.	*/
#define kAIRemoveAnchorPointsAction							"adobe_removeAnchorPoints"

/** @ingroup Actions
	Makes a mask from currently selected objects.	*/
#define kAIMakeMaskFromSelectionAction						"adobe_makeMask"
/** @ingroup Actions
	Releases selected masks.	*/
#define kAIReleaseSelectedMasksAction						"adobe_releaseMask"
/** @ingroup Actions
	Edits selected masks.	*/
#define kAIEditSelectedMasksAction							"adobe_editMask"



/** @ingroup Actions
	Makes a compound object from selected objects.	*/
#define kAIMakeCompoundFromSelectionAction					"adobe_makeCompound"
/** @ingroup Actions
	Releases selected compound objects.	*/
#define kAIReleaseSelectedCompoundAction					"adobe_releaseMask"


/** @ingroup Actions
	Makes crop marks from selected objects.	*/
#define kAIMakeCropMarksFromSelectionAction					"adobe_makeCropMark"
/** @ingroup Actions
	Releases crop marks for selected objects. */
#define kAIReleaseCropMarksAction							"adobe_releaseCropMark"


/** @ingroup Actions
	Shows or hides guides.
		@param #kAIShowHideGuidesKey When true, show guides; when false, hide guides.
	*/
#define kAIShowHideGuidesAction								"adobe_showGuide"
/** Parameter to \c #kAIShowHideGuidesAction. When true, show guides; when false, hide guides. */
const ActionParamKeyID kAIShowHideGuidesKey					= 'show'; // bool

/** @ingroup Actions
	Locks or unlocks guides.
		@param #kAIShowHideGuidesKey When true, lock guides; when false, unlock guides.
	*/
#define kAILockOrUnlockGuidesAction							"adobe_lockGuide"
/** Parameter to \c #kAILockOrUnlockGuidesAction. When true, lock guides; when false, unlock guides. */
const ActionParamKeyID kAIAILockOrUnlockGuidesKey			= 'lock'; // bool


/** @ingroup Actions
	Makes guides from the currently selected objects.	*/
#define kAIMakeGuidesFromSelectionAction					"adobe_makeGuide"
/** @ingroup Actions
	Releases all guides.	*/
#define kAIReleaseAllGuidesAction							"adobe_releaseGuide"
/** @ingroup Actions
	Deletes all guides.	*/
#define kAIDeleteAllGuidesAction							"adobe_clearGuide"


/** @ingroup Actions
	Sets object attributes as defined in Attributes palette.
		@param #kAISetObjectAttributesShowCenterKey Sets the show-center state (true/false).
		@param #kAISetObjectAttributesReverseDirectionKey Sets the reverse-direction state (true/false).
		@param #kAISetObjectAttributesFillRuleKey Sets the fill-rule usage 
		       (0 for non-zero rule, 1 for even-odd rule).
		@param #kAISetObjectAttributesResolutionKey	Sets the resolution in dots-per-inch (dpi)
		@param #kAISetObjectAttributesOverprintFillKey Sets the overprint state for fill (true/false).
		@param #kAISetObjectAttributesOverprintStrokeKey Sets the overprint state for strokes (true/false).
		@param #kAISetObjectAttributesNoteKey Sets an associated comment string.
		@param #kAISetObjectAttributesURLKey Sets an associated URL string.
		@param #kAISetObjectAttributesImageMapKey Sets an associated image map type 
		       (0 for none, 1 for rectangle map, 2 for polygonal map).
	*/
#define kAISetObjectAttributesAction						"adobe_attributePalette"
/** Parameter to \c #kAISetObjectAttributesAction. Sets the show-center state (true/false). */
const ActionParamKeyID kAISetObjectAttributesShowCenterKey	= 'cntr'; // bool
/** Parameter to \c #kAISetObjectAttributesAction. Sets the reverse-direction state (true/false). */
const ActionParamKeyID kAISetObjectAttributesReverseDirectionKey = 'rvpt'; // bool
/** Parameter to \c #kAISetObjectAttributesAction. Sets the fill-rule usage 
    (0 for non-zero rule, 1 for even-odd rule). */
const ActionParamKeyID kAISetObjectAttributesFillRuleKey	= 'rule'; // enum
/** Parameter to \c #kAISetObjectAttributesAction. Sets the resolution in dots-per-inch (dpi) */
const ActionParamKeyID kAISetObjectAttributesResolutionKey	= 'rslt'; // real
/** Parameter to \c #kAISetObjectAttributesAction. Sets the overprint state for fill (true/false). */
const ActionParamKeyID kAISetObjectAttributesOverprintFillKey = 'fill'; // bool
/** Parameter to \c #kAISetObjectAttributesAction. Sets the overprint state for strokes (true/false). */
const ActionParamKeyID kAISetObjectAttributesOverprintStrokeKey = 'strk'; // bool
/** Parameter to \c #kAISetObjectAttributesAction.  Sets an associated comment string. */
const ActionParamKeyID kAISetObjectAttributesNoteKey		= 'note'; // string
/** Parameter to \c #kAISetObjectAttributesAction. Sets an associated URL string. */
const ActionParamKeyID kAISetObjectAttributesURLKey			= 'url.'; // string
/** Parameter to \c #kAISetObjectAttributesAction. Sets an associated image map type 
    (0 for none, 1 for rectangle map, 2 for polygonal map). */
const ActionParamKeyID kAISetObjectAttributesImageMapKey	= 'imap'; // enum


#endif
