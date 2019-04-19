#ifndef __AISwatchLibraries__
#define __AISwatchLibraries__

/*
 *        Name:	AISwatchLibraries.h
 *      Author:	Neal Tucker
 *        Date:	3/11/97
 *     Purpose:	Adobe Illustrator Swatch Libraries Suite.
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

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AISwatchList__
#include "AISwatchList.h"
#endif

#include "AIHeaderBegin.h"

/** @file AISwatchLibraries.h */

// AISwatchLibs Suite
#define kAISwatchLibrariesSuite			"AI Swatch Libraries Suite"
#define kAISwatchLibrariesSuiteVersion	AIAPI_VERSION(7)
#define kAISwatchLibrariesVersion		kAISwatchLibrariesSuiteVersion

/** @ingroup Callers
	Caller ID for messages sent to plug-ins from the Swatch Libraries plug-in.
*/
#define kAISwatchLibsCaller				"Swatch Libraries"

/*******************************************************************************
 **
 **	Types
 **
 **/
typedef struct _t_OS_MenuPtr* AIMenuPtr;

/** @ingroup Notifiers
	Sent when the Swatch Library is opened and has been modified since the last load
	or when it is reloaded because the user saved to it.
 	*/
#define kAISwatchLibraryChangedNotifier	"AI Swatch Library Changed Notifier"

/** Message data sent with  #kAISwatchLibraryChangedNotifier.
	Use with \c #AISwatchLibrariesSuite::GetActiveSwatchList().
	*/
typedef struct {
	/** The updated swatch list. */
	AISwatchListRef swatchList;
	/** The unique identifier of the swatch library that was modified. */
	ai::int32 swatchLibraryID;
} AISwatchLibraryChangedNotifierData;


/** Specifies a swatch position relative to the currently active swatch
	in a document Swatch palette. The behavior depends on whether wrapping
	is on or off.
	See \c #AISwatchLibrariesSuite::GetRelativeDocSwatch() */
typedef enum {
	/** The active swatch itself. */
	kAICurDocSwatch,
	/** The next swatch in the group or list. */
	kAINextDocSwatch,
	/** The previous swatch in the group or list. */
	kAIPrevDocSwatch,
	/** The first swatch in the next group. */
	kAISwatchInNextDocSwatchGroup,
	/** The last swatch in the previous group. */
	kAISwatchInPrevDocSwatchGroup
} AIRelativeDocSwatchKind;

/** Specifies which Swatches palette for the current document is the target of a swatch selection
	query. See \c #AISwatchLibrariesSuite::GetRelativeDocSwatch()
	 */
typedef enum {
	/** The main swatches palette in the regular palette. */
	kAIMainDocSwatches,
	/** The Fill swatches palette in the Control palette. When the toolbox's
		Fill/Stroke indicator is in Fill mode, this has the same selection
		as the main document Swatches palette. */
	kAIDocFillSwatches,
	/** The Stroke swatches palette in the Control palette. When the toolbox's
		Fill/Stroke indicator is in Stroke mode, this has the same selection
		as the main document Swatches palette. */
	kAIDocStrokeSwatches
} AIWhichDocSwatchesPalette;


/** Specifies the library types that should be included when building a library list.
	See \c #AISwatchLibrariesSuite::BuildLibrariesList(). For the various folder types
	see \c #AIFoldersSuite */
typedef ai::uint32 AISwatchLibraryType;

/** An \c #AISwatchLibraryType value. Include all libraries in the Preset Swatches folder.
	This does not include the preset color books, gradients and patterns folders.*/
#define kAIPresetSwatches		1
/** An \c #AISwatchLibraryType value. Include all libraries in the Preset ColorBooks folder.*/
#define kAIPresetColorBooks		2
/** An \c #AISwatchLibraryType value. Include all libraries in the Preset Gradients folder.*/
#define kAIPresetGradients		4
/** An \c #AISwatchLibraryType value. Include all libraries in the Preset Patterns folder.*/
#define kAIPresetPatterns		8
/** An \c #AISwatchLibraryType value. Include all libraries in the User Writable Swatch libraries folder.*/
#define kAIUserWritableSwatches	16
/** An \c #AISwatchLibraryType value. Include other libraries opened from Illustrator. */
#define kAIOtherLibraries		32
/** An \c #AISwatchLibraryType value. Include all libraries. */
#define kAIAllSwatchLibraries	kAIPresetSwatches | kAIPresetColorBooks | kAIPresetGradients | kAIPresetPatterns | kAIUserWritableSwatches | kAIOtherLibraries

/** @ingroup Errors
See \c #AISwatchLibrariesSuite::GetRelativeDocSwatch() */
#define kSwatchDoesNotExistErr		'!SNE'

/** @ingroup Errors
See \c #AISwatchLibrariesSuite::GetRelativeDocSwatch() */
#define kNoActiveSwatchError		'!NAS'


/** Supplied by the Swatch Libraries plug-in, these functions
	allow you to open, access, and manipulate libraries of color,
	custom color, pattern, and gradient swatches, also called swatch lists.

	You can collect all swatches, or all patterns, gradients, or custom colors
	from all open libraries into a single list sorted by name, and
	iterate through the resulting swatch list.

	\e Color \e books contain collections of pre-defined colors,
	such as the Pantone colors. Some color book definitions  and names
	have changed from previous versions. For example, in Illustrator 12 and later,
	Pantone solids are LAB, but were formerly CMYK.
		\li \c #FindStandardBookColor() finds named colors in the
			current color books.
		\li \c #FindLegacyBookColor() find the previous color definition.
		\li \c #MapLegacyColorName() maps a legacy color name to a current one.
 */
typedef struct
{
	/** Gets the number of currently known swatch libraries, including the swatch list
		of the current open document. Use with \c #GetNthLibrary() to iterate through
	    known libraries.

		A library is known if it is located in the Presets folder and appears
		in the Swatch Libraries menu, or if it has been opened at some time
		during the current session with the Other Libraries command.
		You can get a swatch list from a known library regardless of whether it is
		open or closed.
			@note Closing a swatch palette does not remove its swatches from memory,
			but closing a document does clear the corresponding swatch list.
			@param num [out] A buffer in which to return the number of open libraries.
		*/
	AIErr ASAPI (*CountLibraries)(ai::int32 *num);

	/** Retrieves the swatch list for a known swatch library by position index. Use with
		\c #CountLibraries() to iterate through libraries. Use the \c #AISwatchListSuite
		to access and modify the returned list.
			@param num The 0-based position index. Use 0 or a negative number to get the swatch
				list for the current document. The first real library starts at index 1.
			@param swatchlist [out] A buffer in which to return the swatch list, or \c NULL if
				the swatch library has not been opened during this session.
			@see \c #OpenNthLibrary() to open a library.
		*/
	AIErr ASAPI (*GetNthLibrary)(ai::int32 num, AISwatchListRef *swatchlist);

	/** Retrieves the name of any swatch library in the list, whether it has been opened
		or not.
			@param num The 0-based position index of the library.
			@param name [out] A buffer in which to return the name.	The name of the
				swatch library for the current document (\c num <= 0) is the empty string.
		*/
	AIErr ASAPI (*GetNthLibraryName)(ai::int32 num, ai::UnicodeString& name);

	// Aggregate list access

	/** Counts the aggregate number of all swatches in all libraries that have swatch lists.
		Use with \c #GetNthLibrarySwatch() to iterate through all swatches.
			@param num [out] A buffer in which to return the number of swatches.
		*/
	AIErr ASAPI (*CountLibrarySwatches)(ai::int32 *num);

	/** Retrieves a swatch by position index from the list of all swatches.
		Use with \c #CountLibrarySwatches() to iterate through all swatches.
			@param num The 0-based position index.
			@param swatch [out] A buffer in which to return the swatch.
		 */
	AIErr ASAPI (*GetNthLibrarySwatch)(ai::int32 num, AISwatchRef *swatch);

	/** Counts the aggregate number of all pattern swatches in all open libraries.
		Use with \c #GetNthLibraryPattern() to iterate through all patterns.
			@param num [out] A buffer in which to return the number of patterns.
		*/
	AIErr ASAPI (*CountLibraryPatterns)(ai::int32 *num);

	/** Retrieves a pattern swatch by position index from the list of all patterns.
		Use with \c #CountLibraryPatterns() to iterate through all patterns.
			@param num The 0-based position index.
			@param pattern [out] A buffer in which to return the pattern.
		 */
	AIErr ASAPI (*GetNthLibraryPattern)(ai::int32 num, AIPatternHandle *pattern);

	/** Counts the aggregate number of all gradient swatches in all open libraries.
		Use with \c #GetNthLibraryGradient() to iterate through all gradients.
			@param num [out] A buffer in which to return the number of gradients.
		*/
	AIErr ASAPI (*CountLibraryGradients)(ai::int32 *num);

	/** Retrieves a gradient swatch by position index from the list of all gradients.
		Use with \c #CountLibraryGradients() to iterate through all gradients.
			@param num The 0-based position index.
			@param gradient [out] A buffer in which to return the gradient.
		 */
	AIErr ASAPI (*GetNthLibraryGradient)(ai::int32 num, AIGradientHandle *gradient);

	/** Counts the aggregate number of all custom color swatches in all open libraries.
		Use with \c #GetNthLibraryCustomColor() to iterate through all custom color swatches.
			@param num [out] A buffer in which to return the number of custom color swatches.
		*/
	AIErr ASAPI (*CountLibraryCustomColors)(ai::int32 *num);

	/** Retrieves a custom color swatch by position index from the list of all custom color swatches.
		Use with \c #CountLibraryCustomColors() to iterate through all custom color swatches.
			@param num The 0-based position index.
			@param ccolor [out] A buffer in which to return the custom color swatch.
		 */
	AIErr ASAPI (*GetNthLibraryCustomColor)(ai::int32 num, AICustomColorHandle *ccolor);

	// Color book access, new in AI12 (CS2)

	/** Searches the color books to find the definition of a specific named
		color. Color books contain collections of predefined colors, such as
		the Pantone colors.	A color book need not have been opened to be included
		in the search.
		(Note that this function returns a boolean value, not an error code.)
			@param name The name string of the desired color.
			@param color [out] A buffer in which to return the custom color definition, if found.
			@return True if the color is found in a color book, false otherwise.
		*/
	AIBoolean ASAPI (*FindStandardBookColor)(const ai::UnicodeString& name, AICustomColor* color);

	/** Searches the legacy color books to find the previous definition of a specific named
		color. A legacy color book need not have been opened to be included in the search.
		(Note that this function returns a boolean value, not an error code.)
			@param name The name string of the desired color.
			@param color [out] A buffer in which to return the custom color definition, if found.
			@return True if the color is found in a legacy color book, false otherwise.
		*/
	AIBoolean ASAPI (*FindLegacyBookColor)(const ai::UnicodeString& name, AICustomColor* color);

	/** Maps a legacy color name to its corresponding name in the current color books.
			@param src The legacy color-book name.
			@param dst [out] A buffer in which to return the current color-book name,
				or the empty string if no mapping is defined.
		*/
	AIErr ASAPI (*MapLegacyColorName)(const ai::UnicodeString& src, ai::UnicodeString& dst);

	// Palette and Selection control, new for AI13 (CS3)

	/** Retrieves a swatch list from a swatch library. Opens the library file and reads
		swatches even if the library has not yet been opened during the session.
		Use the \c #AISwatchListSuite to access and modify the returned list.
			@param num The 0-based position index. Use 0 or a negative number to get the swatch
				list for the current open document, if any.
			@param showPalette True to create and show a palette for the library.
			@param swatchlist [out] A buffer in which to return the swatch list.
		*/
	AIErr ASAPI (*OpenNthLibrary)(ai::int32 num, AIBoolean showPalette, AISwatchListRef *swatchList );

	/** Reports whether a swatch library is currently displayed in an open palette.
		(Note that this function returns a boolean value, not an error code.)
			@param num The 0-based position index of the swatch library in the list of known libraries.
			@param shouldBeVisible :	Default value is true
										If set true, it ensures that the library asked for, must be currently visible.
										else it returns true for all libraries, which were ever opened.
	*/ 
	AIBoolean ASAPI (*NthLibraryIsOpen)( ai::int32 num , bool shouldBeVisible);


	/** Selects a swatch in the main Swatches palette, if it is open and its color kind is shown.
		(Note that this function returns a boolean value, not an error code.)
			@param index The 0-based position index into the main document's list of the swatch.
			@param deselectOthers True to also deselect any other selected swatches if the specified color is visible.
			@return True if the swatch was successfully selected, false if it was not. This can
				occur if the palette is closed or does not show the specified swatch, or if the index
				is invalid.
	*/

	AIBoolean ASAPI (*SelectNthDocumentSwatchIfVisible) ( ai::int32 index, AIBoolean deselectOthers );

	/** Selects a color group and all of the group's swatches in the main Swatches palette,
		if it is open and the group is shown.
		(Note that this function returns a boolean value, not an error code.)
			@param index The 0-based position index into the main document's list of color groups,
				or -1 to select the last color group in the document, or -2 or less
				to deselect all fully selected color groups. Selected swatches in partially
				selected color groups are not deselected.
			@param deselectOthers True to also deselect any other selected swatches or color groups
				if the specified group is visible.
			@return True if the group was successfully selected, false if it was not. This can
				occur if the palette is closed or does not show the specified swatch, or if the index
				is invalid.
			@note This function is intended to used by other plug-ins that create color groups,
				to select the groups they have just inserted into the list.
	*/
	AIBoolean ASAPI (*SelectNthDocColorGroupIfVisible) ( ai::int32 index, AIBoolean deselectOthers );

	/** Rebuilds the libraries menu, populating it with the current list of libraries.
		The list is refreshed if the supplied change stamp does not match the
		supplied change stamp. The internal change stamp has an initial value of 1.
		Pass a change stamp of 0 to build the list the first time, or to force an update,
		or to uncheck all libraries in the list.
			@param librariesList The ADM hierarchy list object for the libraries list.
			@param startIndex	The 0-based index at which the first library entry is created.
			@param includeLibraryTypes	The library types to include when building the list,
				a logical OR of \c #AISwatchLibraryType values.
			@param contentChangeStampRef [in/out] On input, a pointer to a change stamp number
				to compare with the current internal latest-change stamp. If the input stamp is
				less than the internal stamp, the list is updated, and this buffer filled with the
				new internal stamp value.
			@param checkLibraryID Optional. A pointer to a library's unique identifier. The
				entry for that library is drawn with a check mark in the ADM list.
		*/
	AIErr ASAPI (*BuildLibrariesList) ( AIMenuPtr librariesList, AISwatchLibraryType includeLibraryTypes, ai::int32 startIndex, ai::int32 *contentChangeStampRef, int *checkLibraryID);

	/** Retrieves the swatch list for a swatch library by active list entry, opening the file
		and reading the swatches from it if it has not yet been opened during the session.
		Use the \c #AISwatchListSuite to access and modify the returned list.
			@param librariesList The ADM hierarchy list object for the libraries
				menu with the active entry.
			@param swatchlist [out] A buffer in which to return the swatch list.
			@param activeLibraryID [out] Optional, a buffer in which to return
				the active library's unique indentifier.
	*/
	AIErr ASAPI (*GetActiveSwatchList) ( AISwatchListRef *swatchlist, ai::int32 activeLibraryID);

	/** Counts the total number of selected swatches in the main document Swatches palette. Use this function
		to allocate an appropriately sized array of AIColors before calling \c #GetSelectedDocSwatchColors().
		(Note that this function returns an integer value, not an error code.)
			@return The number of selected swatches.
		*/
	ai::int32 ASAPI (*CountSelectedDocSwatches) ( );

	/** Retrieves an array of colors for the selected document swatches. The
		members are ordered	as they appear in the document Swatches palette,
		left to right and top to bottom.
			@param colors [out] A buffer in which to return the colors.
				Use \c #CountSelectedDocSwatches() to determine how much memory to allocate.
			@param bufferSize The number of elements in the colors array. If there are
				more selected colors, only this many are returned.
		*/
	AIErr ASAPI (*GetSelectedDocSwatchColors) ( AIColor *colors, ai::int32 bufferSize );

	/** Counts the total number of selected swatch groups in the document Swatch palette. Use
		to allocate an  array of \c #AISwatchGroupRef before calling
		\c #GetSelectedDocSwatchGroups().
			@return The number of selected swatch groups, or
				0 if there is no document open or no Swatches palette.
		*/
	ai::int32 ASAPI (*CountSelectedDocSwatchGroups) ( );

	/** Returns an array of the document's selected swatch groups.
		The groups are ordered as they appear in the document Swatches palette,
		left to right and top to bottom.
			@param swatchGroups [out] A buffer in which to return the groups.
				Use \c #CountSelectedDocSwatchGroups() to determine how much memory to allocate.
			@param bufferSize The number of elements in the groups array. If there are
				more selected groups, only this many are returned.
		*/
	AIErr ASAPI (*GetSelectedDocSwatchGroups) ( AISwatchGroupRef *swatchGroups, ai::int32 bufferSize );

	/** Retrieves a document swatch in a specified position in the list, relative
		to the currently \e active document swatch, as determined by \c IADMHierachyList::GetActiveLeafEntry().
		If one swatch is selected, it is the active swatch. If multiple swatches are selected,
		the active one is the last swatch entry to be selected.
			@param selectKind The position of the desired swatch, relative to the
				active swatch.
			@param selectIt When true, the relative swatch becomes selected and all other swatches
				are deslected. When false, the swatch selection state remains unchanged.
			@param wrap When true, the last swatch in a swatch group wraps to the first swatch
				in the same group, and the last swatch group wraps to the first group.
				<br>When wrapping is on, if a swatch group only contains one swatch, the next or previous
				swatch is the same one. Similarly, if there is only one swatch group
				the next or previous group is the same group.
				<br>Ungrouped swatches in the document swatch list are treated as if they are in a group
				that follows the last defined swatch group.
			@param targetPalette The swatch palette to search in (main, fill, or stroke).
			@param relativeSwatch [out] A buffer in which to return the swatch in the specified relation
				to the active swatch, or \c NULL if there is no active swatch or if there is no swatch
                at the relative location. The returned error reflects which condition occurred.
			@return The error \c #kSwatchDoesNotExistErr if the next or previous swatch does not exist.
					When wrapping is on, this error cannot occur.
					<br>The error \c #kNoActiveSwatchError if no swatch is currently selected in the
						specified Swatch palette.
	*/
	AIErr ASAPI (*GetRelativeDocSwatch) ( AIRelativeDocSwatchKind selectKind, AIBoolean selectIt, AIBoolean wrap,
											AIWhichDocSwatchesPalette targetPalette, AISwatchRef *relativeSwatch );

	/** Retrieves an array of references of the selected document swatches. The
	members are ordered	as they appear in the document Swatches palette,
	left to right and top to bottom.
		@param swatchRefs [out] A buffer in which to return the references of swatches.
			Use \c #CountSelectedDocSwatches() to determine how much memory to allocate.
		@param bufferSize The number of elements in the return array. If there are
			more selected swatches, only this many are returned.
	*/
	AIErr ASAPI (*GetSelectedDocSwatchRefs) ( AISwatchRef *swatchRefs, ai::int32 bufferSize );


	/** Searches the color book with specified ID to find the definition of a specified named
	color. Color books contain collections of predefined colors, such as the Pantone colors.	
	(Note that this function returns a boolean value, not an error code.)
		@param name The name string of the desired color.
		@param bookID The id for the book in which color should be searched.
		@param color [out] A buffer in which to return the custom color definition, if found.
		@return True if the color is found, false otherwise.
	*/
	AIBoolean ASAPI (*FindColorInBook)(const ai::UnicodeString& name, ai::int32 bookID, AICustomColor* color);

	/** Counts the total number of selected swatches in the main document Swatches palette not in a selected group.
	Use this function to allocate an appropriately sized array of AIColors before calling
	\c #GetSelectedDocSwatchRefsNotInAnySelectedGroup().
	(Note that this function returns an integer value, not an error code.)
	@return The number of selected swatches.
	*/
	ai::int32 ASAPI(*CountSelectedDocSwatchesNotInAnySelectedGroup) ();

	/** Retrieves an array of colors for the selected document swatches not in any selected group. The
	members are ordered	as they appear in the document Swatches palette,
	left to right and top to bottom.
	@param colors [out] A buffer in which to return the colors.
	Use \c #CountSelectedDocSwatches() to determine how much memory to allocate.
	@param bufferSize The number of elements in the colors array. If there are
	more selected colors, only this many are returned.
	*/
	AIErr ASAPI(*GetSelectedDocSwatchRefsNotInAnySelectedGroup) (AISwatchRef *colors, ai::int32 bufferSize);


} AISwatchLibrariesSuite;



#include "AIHeaderEnd.h"

#endif
