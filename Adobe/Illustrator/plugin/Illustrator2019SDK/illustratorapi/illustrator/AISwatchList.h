#ifndef __AISwatchList__
#define __AISwatchList__

/*
 *        Name:	AISwatchList.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Swatch list management
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIDocument__
#include "AIDocument.h"
#endif

#include "AIHeaderBegin.h"

/** @file AISwatchList.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/
#define kAISwatchListSuite					"AI Swatch List Suite"
#define kAISwatchListSuiteVersion7			AIAPI_VERSION(7)
#define kAISwatchListSuiteVersion			kAISwatchListSuiteVersion7
#define kAISwatchListVersion				kAISwatchListSuiteVersion

#define kAISwatchGroupSuite					"AI Swatch Group Suite"
#define kAISwatchGroupSuiteVersion3			AIAPI_VERSION(3)
#define kAISwatchGroupSuiteVersion			kAISwatchGroupSuiteVersion3
#define kAISwatchGroupVersion				kAISwatchGroupSuiteVersion

/** @ingroup Notifier
	Sent when a change is made to any swatch library from swatch library dialog.
	Changes include change of swatch library using left/right arrow keys. */
#define kAISwatchLibraryDialogChangedNotifier				"AI Swatch Library Dialog Changed Notifier"

/** @ingroup Notifier
	Sent when a change is made to any swatch list for any
	open document (including libraries). Changes include insertion or
	deletion of a swatch, and redefinition of a swatch color or
	name. No data is sent with the notifier. Use \c #AISwatchListSuite
	functions to determine what change occurred. */
#define kAISwatchListChangedNotifier				"AI Swatch List Changed Notifier"
/** @ingroup Notifier
	Sent when the definition of an object in the swatch list has changed.
	Can be followed by a \c #kAISwatchListChangedNotifier if the swatch list itself has also
	changed.  If both are sent, both  have the same \c refStamp as their notifier data.
	See \c #AISwatchListSuite.  */
#define kAISwatchListChangedInternallyNotifier		"AI Swatch List Changed Internally Notifier"
/** @ingroup Notifier
	Sent when a color is replaced in a swatch. See \c #AISwatchListSuite. */
#define kAISwatchReplaceColorNotifier				"AI Swatch Replace Color Notifier"	// used only by SwatchLib
/** @ingroup Notifier
	Sent when a  new swatch is created. See \c #AISwatchListSuite. */
#define kAICreateNewSwatchNotifier					"AI Create New Swatch Notifier"	// used only by PaintStyle

/** @ingroup Notifier
	Sent when a  new swatch is created. See \c #AISwatchListSuite. */
#define kAICreateNewSwatchWithDefaultParamNotifier					"AI Create New Swatch With Default Param Notifier"	// used only by PaintStyle

/** @ingroup Notifier
	Sent when the selection state of the document Swatches palette changes. See \c #AISwatchListSuite. */
#define kAIDocSwatchesSelectionChangedNotifier		"AI Doc Swatches Selection Changed Notifier"

/** @ingroup Errors
	See \c #AISwatchListSuite. */
#define kCantDeleteSwatchErr				'!XDS'
/** @ingroup Errors
	See \c #AISwatchListSuite. */
#define kInvalidSwatchTypeForDest			'!vST'
/** @ingroup Errors
	See \c #AISwatchGroupSuite. */
#define kTooManySwatchGroupsErr				'>#sg'
/** @ingroup Errors
	See \c #AISwatchGroupSuite. */
#define kTooManySwatchesInGrpErr			'>#sw'

/** Maximum allowed number of swatch groups. See \c #AISwatchGroupSuite. */
#define kMaxNumberSwatchGroups		((ASInt16) 0x7FFF)	// 32767
/** Maximum allowed number of swatches in a swatch group. See \c #AISwatchGroupSuite. */
#define kMaxNumberSwatchesPerGroup	((ASInt16) 0xFFFF)	// 65535

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference to a swatch. See \c #AISwatchListSuite.  */
typedef struct _AISwatchOpaque *AISwatchRef;
/** Opaque reference to a swatch list. See \c #AISwatchListSuite.  */
typedef struct _AISwatchListOpaque *AISwatchListRef;

/** Opaque reference to a swatch group.See \c #AISwatchGroupSuite. */
typedef struct _AISwatchGroupOpaque *AISwatchGroupRef;

/** Restrictions on the kinds of swatches allowed in a swatch groups.
	See \c #AISwatchGroupSuite::NewSwatchGroup(),
		\c #AISwatchGroupSuite::GetSwatchGroupKind(). */
typedef enum
{
	/** The group can contain any kind of swatches, and usually has a null name.
		The first swatch group (index 0) must be of this kind.*/
	kAISGKindGeneric,
	/** The group cannot contain patterns or gradients, but can contain
		tints of global colors. Is usually named.*/
	kAISGKindSolidColorsOnly,
	/** The group is only allowed to contain pattern swatches. Is usually named.*/
	kAISGKindPatternsOnly,
	/** The group is only allowed to contain gradient swatches. Is usually named. */
	kAISGKindGradientsOnly
}  AISwatchGroupKind;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that allow you to access and modify \e swatches and
	\e swatch \e lists.	Each Illustrator document has an associated swatch list
	which contains the document’s color swatches as shown in the Swatches palette.

	You can use \c #GetSwatchList() or functions from the \c #AISwatchLibrariesSuite
	to obtain a swatch list reference. Typically, however, you need  only
	the current document's swatch list, so for convenience all functions that take an
	\c #AISwatchListRef accept \c NULL to indicate the current document's
	swatch list.

	The elements in a swatch list are of type \c #AISwatchRef. A swatch is
	an \c #AIColor and an associated name. For \c #AIColor types that are themselves
	defined by a named object (custom colors, patterns and gradients) the swatch name
	is always the same as the name of the object. For other types of \c #AIColor,
	the swatch name is independent.

	Swatch lists are hierarchically organized into \e swatch \e groups,
	which can be named; see the \c #AISwatchGroupSuite.  In \c #InsertNthSwatch(), an
	index of -1 inserts at the end of the general swatches group (group 0).
	Accessor functions in this suite treat groups as if they were flattened,
	so that an index of 0 is the first swatch in the first group, and index numbers
	simply continue into the next group. An exception is the deprecated \c #GetNextSwatch(),
	which works only within a group. Use \c #GetNthSwatch() instead for iteration.

	There are three notifiers associated with swatch lists:
	<br> \c #kAISwatchListChangedNotifier
	<br> \c #kAISwatchListChangedInternallyNotifier
	<br> \c #kAISwatchReplaceColorNotifier

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISwatchListSuite and \c #kAISwatchListVersion.
*/
typedef struct {

	/** Gets the total number of swatches in a swatch list, including those in all groups.
		(Note that this function returns a numeric value, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@return The number of swatches in the list.
		*/
	ai::int32 ASAPI (*CountSwatches)				(AISwatchListRef list);

	/** Retrieves the first swatch in a swatch list.
		(Note that this function returns an object, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@return The swatch reference.
			@see \c #GetNextSwatch()
		*/
	AISwatchRef ASAPI (*GetFirstSwatch)		(AISwatchListRef list);

	/** @deprecated Retrieves the next swatch in a swatch group within a swatch list. Use
	    to find the swatch following one for which you do not have an index (retrieved,
	    for example, with \c #AISwatchListSuite::GetSwatchByNameAndType()). Do not use for iteration.
		(Note that this function returns an object, not an error code.)
	    	@note It is recommended that you use \c #CountSwatches() and \c #GetNthSwatch()
	    		for iteration. This function cannot be used to iterate through a list
				that contains multiple groups, and is inefficient for iteration even
				within a group. .
			@param prev The previous swatch in the list.
			@return The swatch reference, or \c NULL if the previous swatch is the last in the group.
			@see \c #AISwatchGroupSuite::LocateSwatch() to find a swatch with an unknown index.
		*/
	AISwatchRef ASAPI (*GetNextSwatch)		(AISwatchRef prev);

	/** Retrieves a swatch from a swatch list by position index. Use with \c #CountSwatches()
		to iterate through swatches. This is more efficient than \c #GetNextSwatch()
		(Note that this function returns an object, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param index The 0-based position index in the list, disregarding groups.
			@return The swatch reference.
		*/
	AISwatchRef ASAPI (*GetNthSwatch)		(AISwatchListRef list, ai::int32 index);

	/** Retrieves a swatch by name from a swatch list.
		(Note that this function returns an object, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param name The swatch name.
			@return The swatch reference, or a \c NULL swatch reference if no such swatch name is found.
		*/
	AISwatchRef ASAPI (*GetSwatchByName)	(AISwatchListRef list, const ai::UnicodeString& name);

	/** Creates a new swatch and inserts it into a swatch list.
		Use \c #SetSwatchName() and \c #SetAIColor() to set the name and
		color of the swatch after it has been inserted.
		(Note that this function returns an object, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param index The 0-based position index for the insertion point, disregarding groups.
					\li If this is the first position of a named group in the list, the swatch
						is inserted into the preceding group. Use \c #AISwatchGroupSuite
						to control the group placement explicitly.
					\li A value of -1 appends the new swatch at the end of the general
						swatches group (group 0).

				The positions of the swatch previously at this index, and of
				all succeeding swatches, are incremented.
			@return The swatch reference for the new swatch.
		*/
	AISwatchRef ASAPI (*InsertNthSwatch)	(AISwatchListRef list, ai::int32 index);

	/** Removes a swatch specified by index position from a swatch list. If the swatch is
		a custom color swatch and it contains the last reference to that global color
		in the swatch list, then the custom color is also deleted from the document and
		any usages replaced by the equivalent process color.
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param index The 0-based position index of the swatch, disregarding groups.
				The positions of all succeeding swatches, are decremented.
			@return\c #kCantDeleteSwatchErr if the index is out of range.
		*/
	ASErr ASAPI (*RemoveNthSwatch)			(AISwatchListRef list, ai::int32 index);

	/** Retrieves the color definition of a swatch.
			@param swatch The swatch reference.
			@param aicolor [out] A buffer in which to return the color definition.
				Can be any color type supported by Illustrator.
		*/
	ASErr ASAPI (*GetAIColor)				(AISwatchRef swatch, AIColor *aicolor);

	/** Sets the color definition for a swatch.
			@param swatch The swatch reference.
			@param aicolor The new color definition. Can be any color type supported by Illustrator,
				if the type is allowed in the containing swatch group.
			@return The error \c #kInvalidSwatchTypeForDest if the color type is not
				allowed in the containing swatch group.
		*/
	ASErr ASAPI (*SetAIColor)				(AISwatchRef swatch, AIColor *aicolor);

	/** Retrieves the name of a swatch.
			@param swatch The swatch reference.
			@param name [out] A buffer in which to return the name string.
		*/
	ASErr ASAPI (*GetSwatchName)			(AISwatchRef swatch, ai::UnicodeString& name);

	/** Sets the name of a swatch. If the swatch identifies a custom color, pattern, or gradient,
		also changes the name of the underlying object.
			@param swatch The swatch reference.
			@param name The new name string.Limit is 31 chars, more than 31 chars will be removed
		*/
	ASErr ASAPI (*SetSwatchName)			(AISwatchRef swatch, const ai::UnicodeString& name);

	/** Retrieves the swatch list for a document.
			@param document The document, or \c NULL for the current document.
	 			Use the \c #AIDocumentListSuite or \c #AIPathStyleSuite::ImportStyles()
	 			to obtain a document handle.
	 		@param list [out] A buffer in which to return the swatch list.
	 	*/
	ASErr ASAPI (*GetSwatchList)			(AIDocumentHandle document, AISwatchListRef *list);

	/** Retrieves the first swatch in a list that uses a specified color. For patterns and gradients,
		checks only that the gradient or pattern objects match, does not check that
		other parameters such as the gradient matrix also match. For all other types,
		checks all color fields.
		(Note that this function returns an object, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param aicolor The color to match.
			@return The matching swatch reference.
		*/
	AISwatchRef ASAPI (*GetSwatchByColor)	(AISwatchListRef list, const AIColor *aicolor);

	/** Retrieves the first swatch in a list with a given name and color type.
		(Note that this function returns an object, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param name The color name to match.
			@param type The color type to match.
			@return The matching swatch reference.
		*/
	AISwatchRef ASAPI (*GetSwatchByNameAndType)	(AISwatchListRef list, const ai::UnicodeString& name, AIColorTag type);

	/** Removes a specific swatch from a swatch list. This is relatively inefficient, because it must search
		the entire swatch list for the swatch. If you know the swatch group and index,
		and if it is not a custom color or you want to remove custom colors, then
		\c #AISwatchGroupSuite::RemoveNthSwatch() is more efficient.

			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param swatch The swatch reference.
			@param deleteCustomColor When true, and the swatch references a custom color,
				also deletes the custom color. In this case, objects that use the color are
				converted to process colors.
		*/
	ASErr ASAPI (*RemoveSwatch) (AISwatchListRef list, AISwatchRef swatch, ASBoolean deleteCustomColor);

} AISwatchListSuite;


// New in AI13 (CS3)

/** @ingroup Suites
	Swatch lists are hierarchically organized into \e swatch \e groups,
	which can be named.	This suite provides functions to create, access, and manipulate
	the groups, and explicitly control the group placement of swatches within the list.
	Swatch groups were introduced in Illustrator 13.

 	The first group, called the general swatch group, is typically unnamed and can contain
 	any type of swatch. The first swatch group can be named, but cannot be removed or reordered.
	Swatches that are not assigned to a specific group are considered part of the
	general swatch group. If no groups have been defined, all swatches are
	in this group, whose index is 0.

	Other groups are explicitly created and named, and can restrict the types of
	swatches that belong to them. The first such group is at index 1.

	@see \c #AISwatchListSuite

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISwatchGroupSuite and \c #kAISwatchGroupVersion.
	*/
typedef struct {

	/** Reports the number of swatch groups in a swatch list. There is always at
		least one, the unnamed general swatch group.
		(Note that this function returns an integer value, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@return The number of swatch groups.
			*/
	ai::int32 ASAPI (*CountSwatchGroups) (AISwatchListRef list);

	/** Retrieves a swatch group from a swatch list.
		(Note that this function returns an object value, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param index The 0-based position index in the list of groups. The first named
				group, if any, is at index 1.
			@return The swatch group reference.
	 	*/
	AISwatchGroupRef (*GetNthSwatchGroup) (AISwatchListRef list, ai::int32 index);

	/** Retrieves a swatch group by name from a swatch list.  Group names need not
		be unique with a list; if there is more than one matching group, the first one
		is returned.
		(Note that this function returns an object, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param name The swatch group name.
			@return The swatch group reference, or a \c NULL swatch reference if no such group name is found.
		*/
	AISwatchGroupRef ASAPI (*GetSwatchGroupByName) (AISwatchListRef list, const ai::UnicodeString& name);

	/** Creates a new swatch group in a swatch list. The new group is initially unnamed and
		contains no swatches. Use \c #SetSwatchGroupName() to assign a name, and \c #InsertNthSwatch()
		or \c #ReorderSwatchBetweenGroups() to add members.
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param groupKind The types of swatches that are allowed in the group.
			@param atIndex The group position index at which to insert the group, or -1 to append
				it to the current groups.
			@param swatchGroup [out] A buffer in which to return the new swatch group object.
			@return \c #kBadParameterErr if index is 0.
				<br> \c #kTooManySwatchGroupsErr if there are already
					\c #kMaxNumberSwatchGroups in the swatch list. */
	ASErr ASAPI (*NewSwatchGroup) ( AISwatchListRef list, AISwatchGroupKind groupKind,
									ai::int32 atIndex, AISwatchGroupRef *newGroup );

	/** Reports whether a swatch group is in a swatch list.
		(Note that this function returns a boolean value, not an error code.)
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param swatchGroup The swatch group object.
			@param indexFoundAt [out] A buffer in which to return the 0-based index
				into the swatch list at which the group was found.
			@return True if the group is in the list.
		*/
	ASBoolean ASAPI (*SwatchGroupIsInList) (AISwatchListRef list, AISwatchGroupRef swatchGroup, ai::int32 *indexFoundAt ); 

	/** Removes a swatch group from a swatch list by index position. You cannot remove
		 the general swatch group (index 0). The index positions of all later groups are decremented.
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param index The 0-based index position of the swatch to remove.
			@param deleteSwatches  When false, moves the member swatches into the general group,
			unless a swatch with the same name and definition is already in that group.
			When true, deletes the member swatches along with the group. 
			If a member swatch is a custom color swatch and it contains the last reference 
			to a global color in the swatch list, the custom color is not deleted from the document.
			Use \c #AISwatchGroupSuite::RemoveSwatch() to delete the last reference to a spot color.
			@return #kCantDeleteSwatchErr if the index is 0 or greater than
				the number of swatch groups, or if the swatch group contains an undeletable swatch.
		*/
	ASErr ASAPI (*RemoveNthSwatchGroup) (AISwatchListRef list, ai::int32 index, ASBoolean deleteSwatches );

	/** Removes a specific swatch group from a swatch list.
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param swatchGroup The swatch group object.
			@param deleteSwatches  When false, moves the member swatches into the general group,
			unless a swatch with the same name and definition is already in that group.
			When true, deletes the member swatches along with the group. 
			If a member swatch is a custom color swatch and it contains the last reference 
			to a global color in the swatch list, the custom color is not deleted from the document.
			Use \c #AISwatchGroupSuite::RemoveSwatch() to delete the last reference to a spot color.
			@return \c #kBadParameterErr if the swatch group is not in the list.
			@note This function must search the entire list. If you have the index position of the group,
			 \c #RemoveNthSwatchGroup () is more efficient.
		 */
	ASErr ASAPI (*RemoveSwatchGroup) (AISwatchListRef list, AISwatchGroupRef swatchGroup, ASBoolean deleteSwatches);

	/** Changes the position of a swatch group specified by index within a swatch list.
		Other group index values change accordingly. You cannot move another group to position 0, or move the general
		group to any other position.
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param fromIndex The current 0-based position index of the group to move.
			@param newIndex The new 0-based position index.
			@return \c #kBadParameterErr if either index is 0, or is greater than the number of swatch groups.
				<br> If both index values are 0, returns \c #kNoErr but does nothing.
	  */
	ASErr ASAPI (*ReorderNthSwatchGroup) (AISwatchListRef list, ai::int32 fromIndex, ai::int32 newIndex );

	/** Changes the position of a swatch group specified by reference within a swatch list.
		Other group index values change accordingly. You cannot move another group to position 0, or move the general
		group to any other position.
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param swatchGroup The swatch group object.
			@param newIndex The new 0-based position index.
			@return \c #kBadParameterErr if the new index is 0, or is greater than the number of swatch groups.
				or if the group is not in the list, or is the general group.
 			@note This function must search the entire list. If you have the index position of the group,
				 \c #ReorderNthSwatchGroup () is more efficient.
	  */
	ASErr ASAPI (*ReorderSwatchGroup) (AISwatchListRef list, AISwatchGroupRef swatchGroup, ai::int32 newIndex );

	/** Retrieves the name of a swatch group.
			@param swatchGroup The swatch group object.
			@param name [out] A buffer in which to return the name string, or the empty
				string if no name has been assigned.
		*/
	ASErr ASAPI (*GetSwatchGroupName) (AISwatchGroupRef swatchGroup, ai::UnicodeString& name);

	/** Sets the name of a swatch group. Group names need not be unique.
			@param swatchGroup The swatch group object.
			@param name The new name string.
		*/
	ASErr ASAPI (*SetSwatchGroupName) (AISwatchGroupRef swatchGroup, const ai::UnicodeString& name);

	/** Reports what kind of swatches a group can contain. This is set on creation and
		cannot be modified.
		(Note that this function returns a constant value, not an error code.)
			@param swatchGroup The swatch group object.
			@return The allowed-swatch-type constant.
 		*/
	AISwatchGroupKind ASAPI (*GetSwatchGroupKind) (AISwatchGroupRef swatchGroup);

	/** Reports whether a swatch group allows colors of a specific type.
		(Note that this function returns a boolean value, not an error code.)
			@param swatchGroup The swatch group object.
			@param colorKind The color type constant.
			@return True if the type is allowed.
 		*/
	ASBoolean ASAPI (*AllowsColorKind) (AISwatchGroupRef swatchGroup, AIColorTag colorKind);

	/** Moves a swatch to a new position within a swatch group.
			@param swatchGroup The swatch group object.
			@param swatch The swatch object.
			@param toIndex The new 0-based index position, or -1 to move the swatch to the end of
				the group. Other position index values change accordingly.
 			@return \c #kBadParameterErr if the index is greater than the number of swatches
 				in the group, or if the swatch is not in the group.
 		*/
	ASErr ASAPI (*ReorderSwatch) (AISwatchGroupRef swatchGroup, AISwatchRef swatch, ai::int32 toIndex );

	/** Move the swatch at fromIndex to toIndex within the same group. toIndex can be -1 to move to the end.
		Returns kBadParameterErr if either fromIndex or toIndex is greater than count-1, or if fromIndex is less than 0. */

	/** Moves a swatch to a new position within a swatch group.
			@param swatchGroup The swatch group object.
			@param fromIndex The current 0-based index position of the swatch.
			@param toIndex The new 0-based index position, or -1 to move the swatch to the end of
				the group. Other position index values change accordingly.
 			@return \c #kBadParameterErr if either index is greater than the number of swatches
 				in the group, or if the from index is less than 0.
 		*/
	ASErr ASAPI (*ReorderNthSwatch) (AISwatchGroupRef swatchGroup, ai::int32 fromIndex, ai::int32 toIndex );

	/** Reports the number of swatches in a swatch group.
		(Note that this function returns an integer value, not an error code.)
			@param swatchGroup The swatch group object.
			@return The number of swatches.
		*/
	ai::int32 ASAPI (*CountSwatches) (AISwatchGroupRef swatchGroup);

	/** Retrieves a swatch from a swatch group by position index.
		(Note that this function returns an object value, not an error code.)
			@param swatchGroup The swatch group object.
			@param index The 0-based position index.
			@return The swatch object, or a \c NULL object if the index is invalid.
	  */
	AISwatchRef ASAPI (*GetNthSwatch) (AISwatchGroupRef swatchGroup, ai::int32 index);

	/** Retrieves a swatch from a swatch group by name.
		(Note that this function returns an object value, not an error code.)
			@param swatchGroup The swatch group object.
			@param name The swatch name string.
			@return The swatch object, or a \c NULL object if no matching swatch is found.

		*/
	AISwatchRef ASAPI (*GetSwatchByName) (AISwatchGroupRef swatchGroup, const ai::UnicodeString& name);

	/** Retrieves the first swatch within a swatch group with a specified color. For patterns and
		gradients, checks that the gradient or pattern objects match, but does not check that
		the other parameters such as the gradient matrix or pattern matrix also match. For all other types,
		checks all fields for a match. In particular, spot color and global color swatches check the tint.
		(Note that this function returns an object value, not an error code.)
			@param swatchGroup The swatch group object.
			@param aicolor The color.
			@return The swatch object, or a \c NULL object if no matching swatch is found.
		*/
	AISwatchRef ASAPI (*GetSwatchByColor) (AISwatchGroupRef swatchGroup, const AIColor *aicolor);

	/** Retrieves the first swatch within a swatch group with a given name and color type.
		(Note that this function returns an object value, not an error code.)
			@param swatchGroup The swatch group object.
			@param name The swatch name string.
			@param type The color type constant.
			@return The swatch object, or a \c NULL object if no matching swatch is found.
		*/
	AISwatchRef ASAPI (*GetSwatchByNameAndType) (AISwatchGroupRef swatchGroup, const ai::UnicodeString& name, AIColorTag type);

	/** Creates a new swatch and inserts it into a swatch group.
		(Note that this function returns an object value, not an error code.)
			@param swatchGroup The swatch group object.
			@param aicolor The color for the new swatch.
			@param index The 0-based index position at which to insert the new swatch, or -1 to
				append it to the end of the group. The swatch previously at this index
				and all swatches following it in the list are bumped down the list by one position.
			@return The new swatch object, or a \c NULL object if the index is invalid, there is not
				enough memory, the swatch group already contains \c #kMaxNumberSwatchesPerGroup,
				or the swatch type is not allowed for this group. See \c #AISwatchGroupKind.
	 */
	AISwatchRef ASAPI (*InsertNthSwatch) (AISwatchGroupRef swatchGroup, AIColor *aicolor, ai::int32 index);

	/** Removes a swatch specified by index position from a swatch group.
			@param swatchGroup The swatch group object.
			@param index The 0-based index position of the swatch in the group. Other swatch
				position index values are adjusted accordingly.
			@param deleteCustomColor When true, and the swatch is a custom color swatch and
				contains the last reference to that custom color in the entire swatch list,
				the custom color is also deleted from the document and any usages replaced by
				the equivalent process color.
				<br> When false, deletes a custom color only if it is unused. Otherwise, moves
				it to the general group. If this is the general group, the swatch is in use, and
				this is the only reference in the list,	the function returns \c #kCantDeleteSwatchErr.
			@param swatchNotUsed When true, global colors are not replaced in the document and are forcefully
				deleted. It should be used, if it is already been ensured that the color is not used anywhere.
			@return \c #kBadParameterErr if the index is not within the swatch group.
				<br> \c #kCantDeleteSwatchErr if the swatch cannot be deleted for any reason.
		*/
	ASErr ASAPI (*RemoveNthSwatch) (AISwatchGroupRef swatchGroup, ai::int32 index, ASBoolean deleteCustomColor, bool swatchNotUsed);

	/** Removes a specific swatch from a group. Swatch position index values are adjusted accordingly.
		(If the index is known, \c #RemoveNthSwatch() is more efficient.)
			@param swatchGroup The swatch group object.
			@param swatch The swatch object.
			@param deleteCustomColor When true, and the swatch is a custom color swatch and
				contains the last reference to that custom color in the entire swatch list,
				the custom color is also deleted from the document and any usages replaced by
				the equivalent process color.
				<br> When false, deletes a custom color only if it is unused. Otherwise, moves
				it to the general group. If this is the general group, the swatch is in use, and
				this is the only reference in the list,	the function returns \c #kCantDeleteSwatchErr.
			@return \c #kBadParameterErr if the swatch is not in the swatch group.
				<br> \c #kCantDeleteSwatchErr if the swatch cannot be deleted for any reason.
		*/
	ASErr ASAPI (*RemoveSwatch) (AISwatchGroupRef swatchGroup, AISwatchRef swatch, ASBoolean deleteCustomColor);

	/** Retrieves the group of a specific swatch in a swatch list.
		Requires an exact match with the swatch object; swatches for the same color and name
		are not considered equivalent.
			@param list The swatch list, or \c NULL for the current document's swatch list.
			@param swatch The swatch object.
			@param containingSwatchGroup [out] A buffer in which to return the containing group object,
				or a \c NULL object if the swatch is not in the list.
			@param groupIndex [out] Optional. A buffer in which to return the 0-based index position
				of this group within the list.
			@param swatchIndex [out] Optional. A buffer in which to return the 0-based index position
				of this swatch within the group.
		*/
	ASErr ASAPI (*LocateSwatch) (AISwatchListRef list, AISwatchRef swatch, AISwatchGroupRef *containingSwatchGroup, ai::int32 *groupIndex, ai::int32 *swatchIndex);

	/** Moves a swatch from one group to another within the same list. Other index positions within
		both groups are adjusted accordingly.
			@param fromGroup The group object that currently contains the swatch.
			@param fromIndex The 0-based index of the swatch in the current group.
			@param toGroup The destination group object.
			@param toIndex The 0-based index at which to insert the swatch in the destination group,
				or -1 to append it to the end of the group.
			@return \c #kBadParameterErr if the source index is less than 0, or if either index is
				greater than the number of swatches in its group, or if the two swatch groups are
				not in the same swatch list.
				<br> \c #kInvalidSwatchTypeForDest if the swatch is a type that
				is not allowed in the destination group.
		*/
	ASErr ASAPI (*ReorderSwatchBetweenGroups) ( AISwatchGroupRef fromGroup, ai::int32 fromIndex, AISwatchGroupRef toGroup, ai::int32 toIndex );

	/** Reports whether a swatch group is displayed in the open state (showing swatches)
		the next time it is loaded into a palette that is in list view and shows color groups.
		This status is saved on behalf of the Swatches palette, so that it can persist while the
		document is closed or inactive.

		This preference does not guarantee that the swatches
		are visible, even if this swatch group is in the active document,
		because the Swatches palette might not show color groups, or might
		not be in list view.
		(Note that this function returns a boolean value, not an error code.)
			@param swatchGroup The swatch group object.
			@return True if the swatch group should be open in list view.
	*/
	ASBoolean ASAPI (*WantsToBeOpenIfInListView) ( AISwatchGroupRef swatchGroup );

	/** Sets whether a swatch group is displayed in the open state (showing swatches)
		the next time it is loaded into a palette that is in list view and shows color groups.
		This status is saved on behalf of the Swatches palette, so that it can persist while the
		document is closed or inactive.

		If a plug-in other than the Swatches palette changes this value,
		it does not, by itself, trigger an update to the Swatches palette.
		However, it the change is made at the same time as another change that does
		trigger an update, such as adding a new swatch group or a new swatch,
		the Swatches palette honors the setting when the swatch group
		is next displayed in list view.
			@param swatchGroup The swatch group object.
			@param whatItWants True to display the group in the open state, false to
				display it in the closed state.
			@return \c #kBadParameterErr if the no swatch group is supplied.
	*/
	ASErr ASAPI (*SetWantsToBeOpenIfInListView) ( AISwatchGroupRef swatchGroup, ASBoolean whatItWants );

} AISwatchGroupSuite;


#include "AIHeaderEnd.h"

#endif
