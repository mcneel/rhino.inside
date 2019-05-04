#ifndef __AIArtSet__
#define __AIArtSet__

/*
 *        Name:	AIArtSet.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Art Set Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2014 Adobe Systems Incorporated.
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

#ifndef __AILayer__
#include "AILayer.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIArtSet.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIArtSetSuite			"AI Art Set Suite"
#define kAIArtSetSuiteVersion	AIAPI_VERSION(9)
#define kAIArtSetVersion		kAIArtSetSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

/** An \c AIArtSpec is a filter for matching art objects that have specific
	properties. Pass an array of these to \c #AIArtSetSuite::MatchingArtSet()
	to specify the art objects that should be returned.
	Specify the type of art object to match, then filter objects of that type
	based on their user attributes.
		\li Use the special type \c kAnyArt to match any kind of art object.
		\li \c whichAttr specifies the collection of attributes to be considered when filtering objects.
		\li \c attr specifies the values those attributes must have to match an object.

	For	example, specify \c kSelected for both \c whichAttr and \c attr to match
	only art objects that are selected.

	Some \c #AIArtSuite::AIArtUserAttr values are not art attributes
	but instead specify additional matching options. Use such a value
	in the \c whichAttr field; it only needs to be in one of the art specifications.
	*/
typedef struct {
	/** The type of art object to match, an \c #AIArtSuite::AIArtType value. */
	ai::int16 type;
	/** \c #AIArtSuite::AIArtUserAttr values for which attributes to consider (\c whichAttr)
	and for the matching value (\c attr).
	*/
	ai::int32 whichAttr, attr;
} AIArtSpec;

/** Opaque type for an ordered list of art object handles. */
typedef struct _t_AIArt *AIArtSet;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	An art set is an ordered list of art object handles. An art object handle should
	appear at most once in the list. This is enforced by most but not all of the
	functions for manipulating the set.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIArtSetSuite and \c #kAIArtSetVersion.
*/

typedef struct {

	/** Creates a new, empty art set.
		This is an opaque pointer and cannot be dereferenced.
		Use functions in this suite to fill the set with art objects and access them.
			@param artSet [out] A buffer in which to return the new art set.
		*/
	AIAPI AIErr (*NewArtSet) ( AIArtSet *artSet );

	/** Frees memory associated with an art set and makes the reference null.
		Does not affect any artwork referenced by the set.
			@param artSet A pointer to the art set. Upon return, this reference is invalid.
		*/
	AIAPI AIErr (*DisposeArtSet) ( AIArtSet *artSet );

	/** Gets the number of art handles stored in an art set. Use with \c #IndexArtSet() to
		iterate through a set.
			@param artSet The art set.
			@param count [out] A buffer in which to return the number of art handles.
		*/
	AIAPI AIErr (*CountArtSet) ( AIArtSet artSet, size_t *count );

	/** Retrieves the art object at a given index within an art set.
		Use with \c #CountArtSet() to iterate through a set. This is the
		most efficient way to access elements of an art set. Access speed is O(1).
			@param artSet The art set.
			@param index The 0-based position index, in the range \c [0..count-1].
			@param art [out] A buffer in which to return the art object.
			@note \c #ReplaceArtInArtSet() can put \c NULL entries into an art set.
			\c #NextInArtSet() iterates through the set skipping \c NULL entries, but
			is not a efficient as this function. */
	AIAPI AIErr (*IndexArtSet) ( AIArtSet artSet, size_t index, AIArtHandle *art );

	/** Fills an art set with an array of art objects.
		The previous contents of the art set, if any, are lost. It is the
		caller's responsibility to ensure that the array does not contain duplicates.
			@param artSet The art set.
			@param artArray A pointer to an array of art objects.
				You must allocate memory for this array, and free it when it is
				no longer needed.
			@param count The number of entries in \c artArray.
		*/
	AIAPI AIErr (*ArrayArtSet) ( AIArtSet artSet, AIArtHandle *artArray, size_t count );

	/** Fills an art set with currently selected art.
		The previous contents of the art set, if any, are lost.
		Many filters operate on the selected objects in a document. Use this function
		to collect the selected art objects without having to iterate through the
		artwork tree to find them.It is the same as calling \c #MatchingArtSet()
		with a request for <code> { kAnyArt, kArtSelected, kArtSelected } </code>
	  		@param artSet The art set.
	  	*/
	AIAPI AIErr (*SelectedArtSet) ( AIArtSet artSet );

	/** Fills an art set with the art objects in the current document
		that match the criteria given in a list of art specifications; see \c #AIArtSpec.
		The art objects are added to the set in the order they are encountered by a pre-order
		traversal of the document tree. An art object is included
		if it matches any of the art specifications.
			@param spec A pointer to an array of \c #AIArtSpec structures.
			@param numSpecs The number of entries in \c specs.
			@param artSet The art set.
			*/
	AIAPI AIErr (*MatchingArtSet) ( AIArtSpec *specs, ai::int16 numSpecs, AIArtSet artSet );

	/** Fills an art set with all art objects that belong to a specific layer.
		The previous contents of the art set, if any, are lost.
			@param layer The layer.
			@param artSet The art set.
		*/
	AIAPI AIErr (*LayerArtSet) ( AILayerHandle layer, AIArtSet artSet );


	/** Deprecated. Fills an art set \c dst with all artwork in the
		document that is not in the art set \c src.
		@note This function has not been kept up
		to date with changes to the object model. */
	AIAPI AIErr (*NotArtSet) ( AIArtSet src, AIArtSet dst );

	/** Fills an art set with all art objects contained in two art sets without duplicating
		common art objects.
			@param src0 The first source art set.
			@param src1 The second source art set.
			@param dst The destination art set.
			*/
	AIAPI AIErr (*UnionArtSet) ( AIArtSet src0, AIArtSet src1, AIArtSet dst );

	/** Fills an art set with all art objects that are common to two art sets.
			@param src0 The first source art set.
			@param src1 The second source art set.
			@param dst The destination art set.
		*/
	AIAPI AIErr (*IntersectArtSet) ( AIArtSet src0, AIArtSet src1, AIArtSet dst );

	/** Retrieves an art object from an art set.
		Use this function to iterate through the objects in an art set.
		Unlike \c #IndexArtSet() this function skips \c NULL entries in the set, but it
		is not as efficient; access speed is \c O(n). Use \c #IndexArtSet() if possible.
			@param artSet The art set.
			@param prevArt An art object contained in the set, or \c NULL to get the first object.
			@param nextArt [out] A buffer in which to return the next art object, or a null object
			if \c prevArt is not in the set or is the last member.
		*/
	AIAPI AIErr (*NextInArtSet) ( AIArtSet artSet, AIArtHandle prevArt, AIArtHandle *nextArt );

	/* AI 9 additions. */

	/** Appends an art object to an art set if it is not already there.
			@param artSet The art set.
			@param art The art object.
		*/
	AIAPI AIErr (*AddArtToArtSet) (AIArtSet artSet, AIArtHandle art);

	/** Removes all occurrences of an art object from an art set.
			@param artSet The art set.
			@param art The art object.
		*/
	AIAPI AIErr (*RemoveArtFromArtSet) (AIArtSet artSet, AIArtHandle art);

	/* AI 9.01 addition */

	/** Replaces the first occurrence of one art object in a set with another, or, if
		\c oldArt is not found, appends \c newArt to the set.
			@param artSet The art set.
			@param oldArt The art object to replace, if found.
			@param newArt The art object to add. Can be \c NULL,
				in which case a null entry is inserted or added to the set
		*/
	AIAPI AIErr (*ReplaceArtInArtSet) (AIArtSet artSet, AIArtHandle oldArt, AIArtHandle newArt);

	/* AI 18.1 addition */

	/** Clears the art set.
			@param artSet The art set.
		*/
	AIAPI AIErr (*ClearArtSet) (AIArtSet artSet);

} AIArtSetSuite;


#include "AIHeaderEnd.h"


#endif
