#ifndef __AIGroup__
#define __AIGroup__

/*
 *        Name:	AIGroup.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Group Object Suite.
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

#include "AIHeaderBegin.h"

/** @file AIGroup.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIGroupSuite			"AI Group Suite"
#define kAIGroupSuiteVersion	AIAPI_VERSION(5)
#define kAIGroupVersion			kAIGroupSuiteVersion

/** Method choices for normalizing a compound path. See
\c #AIGroupSuite::NormalizeCompoundPath()*/
typedef enum
{
	/** Use the best algorithm currently available. */
	kAINormalizeCompoundPathBest,
	/** Use the Illustrator 10 algorithm. */
	kAINormalizeCompoundPathAI10,
	/** internal */
	kAIMax_NormalizeCompoundPathAlgorithm = 0xFFFFFFFF
} AINormalizeCompoundPathAlgorithm;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions for working with clipping and
	compound paths in art group objects.

	An art object of type \c #kGroupArt is an ordered collection
	of art objects.typically created with the Group command. The group
	as a whole can have a style or transparency blending attributes
	which affect the rendering of its contents.

	In a \e clip group, one or more of the members is a
	clipping object (that is, an art object with the
	\c #kArtIsClipMask flag set, which defines a clip path).
	The intersection of the clip paths is used to clip the rendering
	of the other objects (\e clipped objects) in the group.

	An art object of type \c #kCompoundPathArt is a group whose
	members are other groups and path objects.

	@see \c #AIArtSuite for additional artwork group functionality,
	 such as traversing a group's children and reordering its contents.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIGroupSuite and \c #kAIGroupVersion.
*/
typedef struct {

	/** Reports whether a group is marked as a clipping group; that is, \c #kArtIsClipMask is
		set for the group. Use \c #AIArtSuite::GetArtUserAttr() to determine which members of the
		group (if any) are clipping objects.
			@param group The art group object.
			@param clipped [out] A buffer in which to return true if the group is marked
					as a clipping group.
		*/
	AIAPI AIErr (*GetGroupClipped) ( AIArtHandle group, AIBoolean *clipped );

	/** Marks or unmarks a group as a clipping group; that is, sets or clears \c #kArtIsClipMask
		for the group. Use \c #AIArtSuite::SetArtUserAttr() to mark clipping for individual contained paths.
			@param group The art group object.
			@param clipped True to turn clipping on for the group, false to turn clipping off.
		*/
	AIAPI AIErr (*SetGroupClipped) ( AIArtHandle group, AIBoolean clipped );

	/** Obsolete. Always returns true. */
	AIAPI AIErr (*GetGroupMaskLock) ( AIArtHandle group, AIBoolean *maskLocked );

	/** Obsolete. */
	AIAPI AIErr (*SetGroupMaskLock) ( AIArtHandle group, AIBoolean maskLocked );

	/**	Normalizes the components of a compound path; that is, it sorts the members
		such that the object that appears to be on the outside is in the
		back of the paint order, with the points ordered so that
		the path does not appear reversed in the Attributes palette.
		The paths that define "holes" in the figure are stacked in a defined order.

		The stacking order of a compound path does not affect how it is filled.
		Normalizing does not modify the fill area. It does provide these benefits:

		\li It is easier to directly select the outlines of the holes, which are
			brought to the front. Otherwise, the outer path gets hit-tested first.
		\li If a complex stroke such as a brush stroke is applied to a hole, that
		 	stroke is in front of the strokes for the outer paths.
		\li When blending from one path to another, the component paths are matched
			more intuitively.

		This is especially important for Type Outlines, because fonts
		are typically designed with the holes in the back, causing blends between
		single outline and multiple outline characters to match the single path of
		the one-path character to an inner path of the multiple-path character.
			@param compound The compound path object.
			@param algorithm The normalization algorithm to use.
	*/
	AIAPI AIErr (*NormalizeCompoundPath) ( AIArtHandle compound, AINormalizeCompoundPathAlgorithm algorithm );

} AIGroupSuite;


#include "AIHeaderEnd.h"


#endif
