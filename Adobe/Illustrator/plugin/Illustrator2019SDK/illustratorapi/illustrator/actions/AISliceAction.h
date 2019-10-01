#ifndef _AISLICEACTION_H_
#define _AISLICEACTION_H_

/*
 *        Name:	AISliceAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 10.0 Actions for slicing.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
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

/** Types of slice actions, an integer, the type of action to take.
	See \c #AIActionManagerSuite::AIActionGetType().
	Implemented types are:
	<br> \c #kAICreateSliceActionType,
	<br> \c #kAIDeleteAllSliceActionType,
	<br> \c #kAIClipToArtboardSliceActionType
	*/
const ActionParamKeyID kAISliceActionType					= 'ATYP'; // integer

// for the type parameter
enum
{
	/** \c #kAISliceActionType value, type parameter for slice actions: No action */
	kAINoActionType = 0,
	/** Not implemented */
	kAIMakeSliceActionType = 1,					// unimplemented
	/** Not implemented */
	kAIReleaseSliceActionType,					// unimplemented
	/** Not implemented */
	kAICreateSliceFromGuidesActionType,			// unimplemented
	/** Not implemented */
	kAICreateSliceFromSelectionActionType,		// unimplemented
	/** Not implemented */
	kAICreateSliceFromTextActionType,			// unimplemented
	/** \c #kAISliceActionType value, type parameter for slice actions: Create slice */
	kAICreateSliceActionType,
	/** Not implemented */
	kAISelectSliceActionType,					// unimplemented
	/** Not implemented */
	kAIDuplicateSliceActionType,				// unimplemented
	/** Not implemented */
	kAICombineSliceActionType,					// unimplemented
	/** \c #kAISliceActionType value, type parameter for slice actions: Delete all slices */
	kAIDeleteAllSliceActionType,
	/** Not implemented */
	kAIDivideSliceActionType,					// unimplemented
	/** Not implemented */
	kAIOptionsSliceActionType,					// unimplemented
	/** \c #kAISliceActionType value, type parameter for slice actions: Clip slice to artboard */
	kAIClipToArtboardSliceActionType,
	/** Not implemented */
	kAILockSliceActionType						// unimplemented
};

/** @ingroup Actions
	Creates a slice.
		@param #kAISliceActionBoundsLeftKey	Integer, the left boundary
			of the slice in page coordinates.
		@param #kAISliceActionBoundsBottomKey	Integer, the bottom boundary
			of the slice in page coordinates.
		@param #kAISliceActionBoundsRightKey	Integer, the right boundary
			of the slice in page coordinates.
		@param #kAISliceActionBoundsTopKey	Integer, the top boundary
			of the slice in page coordinates.
	*/
#define kAICreateSliceAction						"AISlice Create Action"

/** Parameter for \c #kAICreateSliceAction. Integer, the left boundary
			of the slice in page coordinates. */
const ActionParamKeyID kAISliceActionBoundsLeftKey		= 'left'; // integer
/** Parameter for \c #kAICreateSliceAction. Integer, the bottom boundary
			of the slice in page coordinates. */
const ActionParamKeyID kAISliceActionBoundsBottomKey	= 'bttm'; // integer
/** Parameter for \c #kAICreateSliceAction. Integer, the right boundary
			of the slice in page coordinates. */
const ActionParamKeyID kAISliceActionBoundsRightKey		= 'rght'; // integer
/** Parameter for \c #kAICreateSliceAction. Integer, the top boundary
			of the slice in page coordinates. */
const ActionParamKeyID kAISliceActionBoundsTopKey		= 'top '; // integer

/** @ingroup Actions
	Deletes all slices in the current document. No parameters. */

#define kAIDeleteAllSliceAction						"AISlice Delete All Action"

/** @ingroup Actions
	Sets clipping for the sliced region.
		@param #kAIClipOn When true, sets the sliced region to the artboard.
			When false, sets the sliced region to the object bounds.
	*/
#define kAIClipToArtboardSliceAction				"AISlice Clip To Artboard Action"

/** Parameter for \c #kAIClipToArtboardSliceAction.
	When true, sets the sliced region to the artboard.
	When false, sets the sliced region to the object bounds.  */
const ActionParamKeyID kAIClipOn					= 'clip'; // bool



#endif // _AISLICEACTION_H_