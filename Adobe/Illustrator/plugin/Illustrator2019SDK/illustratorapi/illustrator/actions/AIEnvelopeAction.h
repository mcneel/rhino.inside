#ifndef _AIENVELOPEACTION_H_
#define _AIENVELOPEACTION_H_

/*
 *        Name:	AIEnvelopeAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Actions for envelopes.
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

//  Action menu identifiers; stored as \c #actionTypeEnum values when recorded
/** Release menu item */
#define kAIEnvelopeActionMenuRelease			0
/** Options menu item */
#define kAIEnvelopeActionMenuOptions			1
/** Expand menu item */
#define kAIEnvelopeActionMenuExpand				2
/** Toggle menu item */
#define kAIEnvelopeActionMenuToggle				3

// Action 'type' identifiers; stored as \c #actionTypeEnum values when recorded
/** Warp operation */
#define kAIEnvelopeActionTypeWarp				0
/** Mesh operation */
#define kAIEnvelopeActionTypeMesh				1
/** Top-object operation */
#define kAIEnvelopeActionTypeTopObject			2

//------------------------------------------------------------------------------

/** @ingroup Actions
	Runs operations in the Envelope submenu of the Action menu
		@param #kAIEnvelopeMenuItem	The menu item to run.
			\li Release: \c kAIEnvelopeActionMenuRelease, replace the envelope with
				art objects for the contents (in their original state) and the mesh.
			\li Options: \c kAIEnvelopeActionMenuOptions, select distortion parameters.
			\li Expand:  \c kAIEnvelopeActionMenuExpand, replace the envelope with the
				art objects for the contents, in their distorted state.
			\li Edit Contents/Envelope: \c kAIEnvelopeActionMenuToggle, toggle between
				editing the contained art and editing the shape of a warp or mesh.

		@param #kAIEnvelopeAntiAliasRaster Options parameter. When true,
			anti-alias is used to smooth rasters that are distorted in envelopes.
		@param #kAIEnvelopePreserveRasterShape Options parameter. How to
			preserve raster shapes when they are distorted by non-rectangular
			envelopes.
				\li When true, apply an alpha channel (transparency) to the raster
				\li When false,	use a clipping mask	on the raster.

		@param #kAIEnvelopeFidelity	Options parameter. The fidelity value controls
			how closely the deformed object fits into the envelope region.
			Higher values add more points to the distorted paths, and take
			longerto calculate.
			An integer in the range <code>[0..100]</code>
		@param #kAIEnvelopeDistortAppearance Options parameter. When true,
			distort the appearance of an object (such as applied effects
			or styles) and not just the object's underlying geometry. The
			appearance properties are expanded separately.
			When false, the appearance is applied after the envelope
			distorts the underlying geometry.
		@param #kAIEnvelopeDistortPatterns Options parameter. When true,
			distort pattern fill, which is expanded separately.
		@param #kAIEnvelopeDistortGradients Options parameter. When true,
			distort gradient fill, which is expanded separately.
	*/
#define kAIEnvelopeMenuAction							"ai_plugin_envelope"
/** Parameter to \c #kAIEnvelopeMenuAction. The menu item to run.
		\li Release: \c kAIEnvelopeActionMenuRelease, replace the envelope with
			art objects for the contents (in their original state) and the mesh.
		\li Options: \c kAIEnvelopeActionMenuOptions, select distortion parameters.
		\li Expand:  \c kAIEnvelopeActionMenuExpand, replace the envelope with the
			art objects for the contents, in their distorted state.
		\li Edit Contents/Envelope: \c kAIEnvelopeActionMenuToggle, toggle between
			editing the contained art and editing the shape of a warp or mesh.
	*/
const ActionParamKeyID kAIEnvelopeMenuItem				= 'menu'; // enum
/** Options parameter to \c #kAIEnvelopeMenuAction. When true, anti-alias is used to smooth
	rasters that are distorted in envelopes. */
const ActionParamKeyID kAIEnvelopeAntiAliasRaster		= 'aars'; // bool
/** Options parameter. How to preserve raster shapes when they are
	distorted by non-rectangular envelopes.	Can be 0 or 1.
		\li When 0,	use a clipping mask	on the raster.
		\li When 1, apply an alpha channel (transparency) to the raster.
	*/
const ActionParamKeyID kAIEnvelopePreserveRasterShape	= 'alph'; // enum
/** Options parameter to \c #kAIEnvelopeMenuAction. The fidelity value controls how closely the
	deformed object fits into the envelope region.
	Higher values add more points to the distorted paths, and take
	longerto calculate. An integer in the range <code>[0..100]</code> */
const ActionParamKeyID kAIEnvelopeFidelity				= 'fidt'; // integer
/** Options parameter to \c #kAIEnvelopeMenuAction.  When true, expand and distort the appearance of an object
	(such as applied effects or styles) and not just the object's
	underlying geometry.
	When false, the appearance is applied after the envelope
	distorts the underlying geometry.*/
const ActionParamKeyID kAIEnvelopeDistortAppearance		= 'app.'; // bool
/** Options parameter to \c #kAIEnvelopeMenuAction. When true,expand and distort pattern fill. */
const ActionParamKeyID kAIEnvelopeDistortPatterns		= 'patt'; // bool
/** Options parameter to \c #kAIEnvelopeMenuAction. When true, expand and distort gradient fill. */
const ActionParamKeyID kAIEnvelopeDistortGradients		= 'grad'; // bool

//------------------------------------------------------------------------------

/** @ingroup Actions
	Makes an envelope from the selected objects on the artboard.
		@param #kAIEnvelopeMakeType	How to make an envelope from selected
			objects on the artboard.
				\li Make with Warp:	\c kAIEnvelopeActionTypeWarp
                \li Make with Mesh:	\c kAIEnvelopeActionTypeMesh
				\li Make with Top Object: \c kAIEnvelopeActionTypeTopObject

		@param #kAIEnvelopeNumRows For mesh type: Number of rows in mesh.
		@param #kAIEnvelopeNumCols For mesh type: Number of columns in mesh.
		@param #kAIEnvelopeWarpStyle For warp type: The predefined warp style,
			an \c #AIWarpStyle value.
		@param #kAIEnvelopeBend	For warp type: Bend amount, a percentage
			value in the range <code>[-100..100]</code>
		@param #kAIEnvelopeHorizDistort	For warp type:	Horizontal distortion
			amount, a percentage value in the range <code>[-100..100]</code>
		@param #kAIEnvelopeVertDistort For warp type: Vertical distortion
			amount, a percentage value in the range <code>[-100..100]</code>
		@param #kAIEnvelopeRotate90	For warp type: 0 to apply horizontally,
			1 to apply bend vertically.
	*/
#define kAIEnvelopeMakeAction "ai_plugin_envelope_make"
/** Parameter to \c #kAIEnvelopeMakeAction. How to make an envelope from selected objects on the artboard.
		\li Make with Warp:	\c kAIEnvelopeActionTypeWarp
		\li Make with Mesh:	\c kAIEnvelopeActionTypeMesh
		\li Make with Top Object: \c kAIEnvelopeActionTypeTopObject
	*/
const ActionParamKeyID kAIEnvelopeMakeType				= 'type'; // enum
/** Parameter to \c #kAIEnvelopeMakeAction, for mesh type: Number of rows in mesh. */
const ActionParamKeyID kAIEnvelopeNumRows				= 'rows'; // integer
/** Parameter to \c #kAIEnvelopeMakeAction, for mesh type: Number of columns in mesh. */
const ActionParamKeyID kAIEnvelopeNumCols				= 'cols'; // integer
/** Parameter to \c #kAIEnvelopeMakeAction, for warp type: Warp style, see \c #AIWarpStyle in \c AIEnvelope.h */
const ActionParamKeyID kAIEnvelopeWarpStyle				= 'warp'; // enum
/** Parameter to \c #kAIEnvelopeMakeAction, for warp type: Bend amount, a percentage value in the range
	[-100..100].  */
const ActionParamKeyID kAIEnvelopeBend					= 'bend'; // unit real
/** Parameter to \c #kAIEnvelopeMakeAction, for warp type:	Horizontal distortion amount, a percentage value
 	in the range [-100..100].  */
const ActionParamKeyID kAIEnvelopeHorizDistort			= 'horz'; // unit real
/** Parameter to \c #kAIEnvelopeMakeAction, for warp type: Vertical distortion amount, a percentage value
 	in the range [-100..100]. */
const ActionParamKeyID kAIEnvelopeVertDistort			= 'vert'; // unit real
/** Parameter to \c #kAIEnvelopeMakeAction, for warp type: 0 to apply horizontally, 1 to apply bend vertically.	*/
const ActionParamKeyID kAIEnvelopeRotate90				= 'rot.'; // enum

//------------------------------------------------------------------------------

/** @ingroup Actions
	Resets the selected envelopes on the artboard.
		@param #kAIEnvelopeResetType How to reset the envelope:
			\li Reset with Warp: \c #kAIEnvelopeActionTypeWarp
			\li Reset with Mesh: \c #kAIEnvelopeActionTypeMesh

		@param #kAIEnvelopeMaintainShape For mesh type: When true, maintain
			the envelope shape.
		@note Additional parameters are the same as for \c #kAIEnvelopeMakeAction
	*/
#define kAIEnvelopeResetAction							"ai_plugin_envelope_reset"
/** Parameter to \c #kAIEnvelopeResetAction. How to reset the envelope:
		\li Reset with Warp: \c #kAIEnvelopeActionTypeWarp
		\li Reset with Mesh: \c #kAIEnvelopeActionTypeMesh
	*/
const ActionParamKeyID kAIEnvelopeResetType				= 'type'; // enum
/**  Parameter to \c #kAIEnvelopeResetAction, for mesh type: When true, maintain the envelope shape. */
const ActionParamKeyID kAIEnvelopeMaintainShape			= 'shap'; // bool
// The following keys are reused from the kAIEnvelopeMakeAction action and are already defined
//const ActionParamKeyID kAIEnvelopeNumRows				= 'rows'; // integer
//const ActionParamKeyID kAIEnvelopeNumCols				= 'cols'; // integer
//const ActionParamKeyID kAIEnvelopeWarpStyle			= 'warp'; // enum
//const ActionParamKeyID kAIEnvelopeBend				= 'bend'; // unit real
//const ActionParamKeyID kAIEnvelopeHorizDistort		= 'horz'; // unit real
//const ActionParamKeyID kAIEnvelopeVertDistort			= 'vert'; // unit real
//const ActionParamKeyID kAIEnvelopeRotate90			= 'rot.'; // enum


#endif // _AIENVELOPEACTION_H_
