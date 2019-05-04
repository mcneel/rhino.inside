#ifndef __AIMatchingArt__
#define __AIMatchingArt__

/*
 *        Name:	AIMatchingArt.h
 *   $Revision: 4 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Matching Art Suite.
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

#ifndef __AILayerList__
#include "AILayerList.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIMatchingArt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIMatchingArtSuite			"AI Matching Art Suite"
#define kAIMatchingArtSuiteVersion	AIAPI_VERSION(7)
#define kAIMatchingArtVersion		kAIMatchingArtSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

/** A filter for matching art objects that contain specific
	properties. Pass an array of these structures to \c #AIMatchingArtSuite
	functions to specify the art objects that should be returned.

	Together, \c whichAttr and \c attr specify an attribute value
	that an art object of the given \c type must have to be considered a match.
		\li \c whichAttr is the desired attribute, one of the \c #AIArtUserAttr values.
		\li \c attr is a mask for the desired state of the attribute. Pass 0
			to match objects without the attribute. or the attribute constant
			to match objects with that attribute.

	For	example:
	\li Specify \c #kArtSelected for both \c whichAttr and \c attr
		to match only art objects that are selected.
	\li Specify \c #kArtSelected for \c whichAttr and 0 for
 		\c attr to match only objects that are \e not selected.

	Some values in \c #AIArtUserAttr are not art attributes
	but instead specify additional options to the matching process. To
	use these options, specify the value in the \c whichAttr field of one
	specifications structure. For example, if the  \c #kMatchDictionaryArt
	flag is set	in any specification, the search looks in the dictionaries
	of art objects, as well as in the objects themselves.
*/
struct AIMatchingArtSpec {
    AIMatchingArtSpec(ai::int32 _type = 0, ai::int32 _whichattr = 0, ai::int32 _attr = 0):
        type(static_cast<ai::int16>(_type)), whichAttr(_whichattr), attr(_attr) {}
    
	/** An \c  #AIArtType that identifies the types of art objects that match
		the specification. Use the special type \c #kAnyArt to match any kind
		of art object. */
	ai::int16  type;
	/** An attribute and value by which to further filter art of the given type. */
	ai::int32 whichAttr, attr;
} ;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite allows you to get lists of art objects that are currently selected,
	or that match specified criteria, from among all available art objects,
	or from artwork in a particular set of layers. It provides an additional
	collection mechanism to those in the \c #AIArtSuite and \c #AIArtSetSuite,
	and is more convenient than traversing the entire artwork tree.

	These functions return art in an array of \c #AIArtHandle. The suite allocates
	a memory block for this array, which you must release using
	#AIMdMemorySuite::MdMemoryDisposeHandle(). Do not free the individual members of the array.

	The functions flatten the requested hierarchy of objects into one art
	object array, which can contain any combination of atomic objects, such as paths,
	and compound objects, such as groups.

	Your plug-in must handle the case of a group that is \e partially selected--that is,
	some but not all members are selected. In this case, both the group and some of
	its contained art objects are in the returned object array.
	If, for example, your plug-in moves the	objects in a group,	you must
	ignore the member objects in the array so that they are not moved twice.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMatchingArtSuite and \c #kAIMatchingArtVersion.
*/
struct AIMatchingArtSuite {

	/** Collects all selected art objects in the current layer list of the current document.
			@param matches [out] A buffer in which to return a pointer to a
				block of memory containing the array of matching art objects.
				You must release the memory block when you no longer
				need it using #AIMdMemorySuite::MdMemoryDisposeHandle().
				Do not free the individual members of the array.  This may be
				\c NULL if you do not want the actual matches (but only the
				count, for instance).
			@param numMatches [in/out] A buffer in which to pass the size of the
				\c matches array, and return the number of art objects collected.
				If no objects are selected, returns 0.
		 */
	AIAPI AIErr (*GetSelectedArt) ( AIArtHandle ***matches, ai::int32 *numMatches );
	/** Collects an array of all art objects in the current layer list of the
		current document that match a set of criteria.
			@param specs An array of match specifications.
			@param numSpecs The number of entries in the \c specs array.
			@param matches [out] A buffer in which to return a pointer to a
				block of memory containing the array of matching art objects.
				You must release the memory block when you no longer
				need it using #AIMdMemorySuite::MdMemoryDisposeHandle().
				Do not free the individual members of the array.
			@param numMatches [in/out] A buffer in which to pass the size of the
				\c matches array, and return the number of art objects collected.
				If no objects are selected, returns 0.
		*/
	AIAPI AIErr (*GetMatchingArt) ( AIMatchingArtSpec *specs, ai::int16  numSpecs,
			AIArtHandle ***matches, ai::int32 *numMatches );

	// new to Illustrator 9.0

	/** Collects all selected art objects in a given layer list of the current document.
			@param list The layer list.
			@param matches [out] A buffer in which to return a pointer to a
				block of memory containing the array of matching art objects.
				You must release the memory block when you no longer
				need it using #AIMdMemorySuite::MdMemoryDisposeHandle().
				Do not free the individual members of the array.
			@param numMatches [in/out] A buffer in which to pass the size of the
				\c matches array, and return the number of art objects collected.
				If no objects are selected, returns 0.
		*/
	AIAPI AIErr (*GetSelectedArtFromLayerList) ( AILayerList list, AIArtHandle ***matches,
			ai::int32 *numMatches );

	/** Collects an array of all art objects in a given layer list of the
		current document that match a set of criteria.
			@param list The layer list.
			@param specs An array of match specifications.
			@param numSpecs The number of entries in the \c specs array.
			@param matches [out] A buffer in which to return a pointer to a
				block of memory containing the array of matching art objects.
				You must release the memory block when you no longer
				need it using #AIMdMemorySuite::MdMemoryDisposeHandle().
				Do not free the individual members of the array.
			@param numMatches [in/out] A buffer in which to pass the size of the
				\c matches array, and return the number of art objects collected.
				If no objects are selected, returns 0.		*/
	AIAPI AIErr (*GetMatchingArtFromLayerList) ( AILayerList list, AIMatchingArtSpec *specs,
		ai::int16  numSpecs, AIArtHandle ***matches, ai::int32 *numMatches );

	// new to Illustrator 10.0

	/** Collects an array of all art objects in the current layer list of the current
		document that are used to determine the current path style, as displayed in the Color palette.
		The current path style is determined by a combination of the targeted and selected objects.
		The returned art can include objects inside graphs.
			@param matches [out] A buffer in which to return a pointer to a
				block of memory containing the array of matching art objects.
				You must release the memory block when you no longer
				need it using #AIMdMemorySuite::MdMemoryDisposeHandle().
				Do not free the individual members of the array.
			@param numMatches [in/out] A buffer in which to pass the size of the
				\c matches array, and return the number of art objects collected.
				If no objects are selected, returns 0.
		*/
	AIAPI AIErr (*GetArtForCurrentPathStyle) ( AIArtHandle ***matches, ai::int32 *numMatches );

	/** Reports whether any art objects (as opposed to text objects)
		are selected in the current layer list of the current document,
		when the document is not in text editing mode.
		(Note that this function returns a boolean value, not an error code.)
			@return True if any art objects are selected, false if there is a text
				editing selection or if no objects are selected.
			@note To test whether there is a text editing selection, call
				\c #AIDocumentSuite::HasTextFocus().
		*/
	AIAPI AIBoolean (*IsSomeArtSelected) ( void );

	/** Collects an array of all art objects in a given artwork tree
		that match a set of criteria.  Use to perform a narrower
		search, or to search in art that is not part of the regular artwork
		tree, such as definition art for a pattern, brush, or symbol.
			@param searchArt The root art object.
			@param specs An array of match specifications.
			@param numSpecs The number of entries in the \c specs array.
			@param matches [out] A buffer in which to return a pointer to a
				block of memory containing the array of matching art objects.
				You must release the memory block when you no longer
				need it using #AIMdMemorySuite::MdMemoryDisposeHandle().
				Do not free the individual members of the array.
			@param numMatches [in/out] A buffer in which to pass the size of the
				\c matches array, and return the number of art objects collected.
				If no objects are selected, returns 0.
		*/
	AIAPI AIErr (*GetMatchingArtFromArt) ( AIArtHandle searchArt, AIMatchingArtSpec *specs,
		ai::int16 numSpecs, AIArtHandle ***matches, ai::int32 *numMatches );

	// new to Illustrator 11.0

	/** Deselects all objects in the current document. */
	AIAPI AIErr (*DeselectAll) ( void );

};


#include "AIHeaderEnd.h"

#endif
