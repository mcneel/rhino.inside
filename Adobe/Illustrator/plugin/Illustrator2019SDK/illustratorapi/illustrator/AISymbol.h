#ifndef __AISymbol__
#define __AISymbol__

/*************************************************************************
*
* ADOBE CONFIDENTIAL
*
* Copyright 1990 Adobe
*
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/


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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif

#include "AIHeaderBegin.h"

/** @file AISymbol.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAISymbolSuite				"AI Symbol Suite"
#define kAISymbolSuiteVersion8		AIAPI_VERSION(8)
#define kAISymbolSuiteVersion		kAISymbolSuiteVersion8
#define kAISymbolVersion			kAISymbolSuiteVersion

#define kAISymbolPaletteSuite			"AI Symbol Palette Suite"
#define kAISymbolPaletteSuiteVersion3	AIAPI_VERSION(3)
#define kAISymbolPaletteSuiteVersion	kAISymbolPaletteSuiteVersion3
#define kAISymbolPaletteVersion			kAISymbolPaletteSuiteVersion


/** @ingroup Notifiers
	Sent when symbols are added, deleted, redefined (including indirectly due to redefinition
	of elements used inside the symbol pattern), renamed, sorted or moved in the symbol list.
	This message is sent even when the affected symbols are unlisted.
	See \c #AISymbolSuite */
#define kAIArtSymbolSetChangedNotifier		"AI Art Symbol Set Changed Notifier"
/** @ingroup Notifiers
	Sent after \c #kAIArtSymbolSetChangedNotifier, with the same time stamp.
	Provides details of the change. The notify data is an\c #AISymbolSetChangeNotifierData. */
#define kAIArtSymbolSetDetailedChangeNotifier "AI Art Symbol Set Detailed Change Notifier"
/** @ingroup Notifiers
	Sent when symbols are added to, removed from, or reordered in the symbol list.
	This message is NOT sent when unlisted symbols are created, deleted or modified,
	nor when the definitions or names of symbols are changed, even if they are listed.
 See \c #AISymbolSuite */
#define kAIArtSymbolListChangedNotifier		"AI Art Symbol List Changed Notifier"
/** @ingroup Notifiers
	Sent when a symbol instance is double-clicked. */
#define kAIArtSymbolDoubleClickedNotifier	"AI Art Symbol Double Clicked Notifier"

/** Maximum number of real characters in a symbol name.
	When retrieving a name, the buffer size should be at least this value + 1.
	If it is less, the name is truncated. */
#define kMaxSymbolNameLength				63


/** @ingroup Errors
	Attempt to modify a symbol that is not in the current document.
	See \c #AISymbolSuite   */
#define kSymbolNotInCurrentDocument 		'SYnD'
/** @ingroup Errors
	Symbol definitions cannot contain instances of the symbol being redefined.
	See \c #AISymbolSuite  */
#define kCircularSymbolDefinitionErr 		'@in@'
/** @ingroup Errors
	Symbol definitions cannot contain graphs. See \c #AISymbolSuite  */
#define kNoGraphsInSymbolDefErr 			'#in@'
/** @ingroup Errors
	Symbol definitions cannot contain linked (non-embedded) images.
	See \c #AISymbolSuite  */
#define kNoLinkedImagesInSymbolDefErr 		'!%i@'
/** @ingroup Errors
Symbol definitions cannot contain Text and symbol in Perspective.
See \c #AISymbolSuite  */
#define kNoPerspectiveInSymbolDefErr		'$in@'
/** @ingroup Errors
	Miscellaneous problems with the definition art for symbols. See \c #AISymbolSuite.  */
#define kInvalidSymbolDefErr				'!#Sd'
/** @ingroup Errors
    Symbol cannot be deleted because it is used in Live Effects. See \c #AISymbolSuite. */
#define kCantDeleteSymbolUsedInLiveEffectsErr '!Del'


/** @ingroup DictKeys
	When a plug-in group object is selected and has this key, it is selected
	as if it were an instance of the associated symbol.

	To select a specific symbol in the Symbols palette when the plug-in group
	is selected (and no instance of a different symbol is also selected):
@code
	AIDictionaryRef dictionary=NULL;
	sAIArt->GetDictionary(pluginArt, &dictionary);
	sAIDictionary->Set(dictionary,
						sAIDictionary->Key(kAISymbolToSelectDictKey),
						sAIEntry->FromSymbolPattern(myMainSymbol));
	sAIDictionary->Release(dictionary);
@endcode
*/
#define kAISymbolToSelectDictKey "AISymbolToSelect"


/* Types */
/** The type of symbol change that triggered the notification,
	sent in \c #AISymbolSetChangeNotifierData. */
typedef enum {
	kSymbolAdded,
	kSymbolDeleted,
	kSymbolRenamed,
	kSymbolChanged
} AISymbolChangeType;

/** Bit flags for the search scope in \c #AISymbolSuite::ArtUsesSymbolPattern().
	If none of the first five flags is set, then the only objects that report using
	a symbol are actual instances of that symbol.
 */
enum AISymbolSearchScope {
	/** Search dictionary of the input art object (that is, inside the
		art style definition attached to the root object.  */
	kSearchArtDictionary				= 0x0001,
	/** Search children of groups and other containers.
		@note If on, also searches in effect dictionaries in descendants,
			regardless of \c #kSearchArtDictionary value. */
	kSearchDescendants					= 0x0002,
	/** Search styled art and the result groups of plug-in groups. */
	kSearchVisualRepresentation			= 0x0004,
	/** Search the symbol pattern definitions of any symbol instances. */
	kSearchNestedSymbolPatterns			= 0x0008,
	/** Search for symbols in effect parameters. */
	kSearchEffectDictionaries			= 0x0040,
	/** Turns on all previous flags. */
	kSymbolSearchEverywhere				= 0x004F,
	/** Do not search invisible objects or the edit groups of plug-in groups. */
	kSearchPrintingOnly					= 0x0010,
	/** Check only for symbols listed in the palette; ignore unlisted ones. */
	kSymbolSearchListedOnly				= 0x0020
};

/** Bit flags for the global object usage result from
	\c #AISymbolSuite::ArtUsesSymbolPattern(). */
enum AISymbolGlobalObjectUsage {
	/** Used in graph designs. */
	kUsedInGraphDesigns					= 0x0001,
	/** Used in graph designs that are themselves in use. */
	kUsedInUsedGraphDesigns 			= 0x0002,
	/** Used in the definition of other symbols. */
	kUsedInOtherSymbols					= 0x0004,
	/** Used in the definition of symbols that are themselves in use. */
	kUsedInUsedSymbols					= 0x0008
};

/** Symbol type used when exporting to Flash.
	@see \c #AISymbolSuite::SetSymbolExportType(),
		\c #AISymbolSuite::GetSymbolExportType()  */
enum AISymbolFlashExportType
{
	/** Corresponds to Graphic Symbol type in Flash. */
	kGraphicType = 0x01,
	/** Corresponds to Movie Clip Symbol type in Flash. */
	kMovieClipType = 0x02
};

/** Symbol registration point.
	\c #AISymbolSuite::NewSymbolPattern()
	\c #AISymbolSuite::NewSymbolPatternFromSel()
	\c #AISymbolSuite::NewSymbolPatternFromSelGetBounds()*/
enum AISymbolRegistrationPoint
{
	kSymbolTopLeftPoint = 0x01,
	kSymbolTopMiddlePoint,
	kSymbolTopRightPoint,
	kSymbolMiddleLeftPoint,
	kSymbolCenterPoint,
	kSymbolMiddleRightPoint,
	kSymbolBottomLeftPoint,
	kSymbolBottomMiddlePoint,
	kSymbolBottomRightPoint,
	kSymbolRegistrationPointUndefined = 0xffffffff
};

/** Data sent with \c #kAIArtSymbolSetDetailedChangeNotifier.
	Provides details of the change that triggered the previous
	\c #kAIArtSymbolSetChangedNotifier. */
typedef struct {
	/** The same time stamp as that of the matching
		\c #kAIArtSymbolSetChangedNotifier. */
	size_t timestamp;
	/** The number of entries in the \c changedSymbols and
		\c changeTypes lists. */
	size_t count;
	/** A list of symbols that have	changed. */
	AIPatternHandle *changedSymbols;
	/** A parallel list of the type of change that occurred
		for each symbol in \c changedSymbols. */
	AISymbolChangeType *changeTypes;
} AISymbolSetChangeNotifierData;

/** Data sent with \c #kAIArtSymbolDoubleClickedNotifier.  */
typedef struct {
	/** The symbol art object that was double-clicked. */
	AIArtHandle symbolArt;
} AISymbolInstanceDoubleClickedNotifierData;

enum SymbolDeleteChoice
{
	kExpandInstances,
	kDeleteInstances
};
/*******************************************************************************
 **
 **	AISymbol Suite
 **
 **/

/** @ingroup Suites
	This suite is always available. The functions allow you to query and manipulate
	the symbol patterns and symbol instances in a document.	 Symbol instances
	are art objects of type \c #kSymbolArt, and are associated with a transformation
	matrix.

	These notifiers are related to symbols:
	<br> \c #kAIArtSymbolSetChangedNotifier
	<br> \c #kAIArtSymbolSetDetailedChangeNotifier

	These dictionary keys are related to symbols:
	<br> \c #kAISymbolToSelectDictKey

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISymbolSuite and \c #kAISymbolVersion.

	@section ListedUnlistedSymbols  Listed and Unlisted Symbols

	\li Listed symbols appear in the Symbols palette, and  are saved when a document
	is closed, even if there are no instances of them in the document. They can be considered
	public, shared between documents.

	\li Unlisted symbols do not appear in the Symbols palette. When the document
	is saved, they are not written out unless there is at least one instance of the symbol
	used in the document. Unlisted symbols can be considered private to a specific document.

	Ordering of the global symbol list affects only listed symbols. When you retrieve
	unlisted symbols, their order is usually, but not always, that of creation.
	The position index is not guaranteed to remain constant between calls.

	Unlisted symbols are intended for instances that are automatically
	generated in a context where they are not directly selectable, such as the result group
	of a plug-in art object (for instance, the intermediate steps of a blend or the particles
	of a particle system), or the styled art of an object with a complex appearance.
	They are systematically derived by the plug-in group or a Live Effect from one
	or more listed symbols.

	Symbol instances that appear in ordinary selectable contexts should always be
	based on listed symbols, but they do not become listed automatically. Any
	command that expands objects like plug-in groups or appearances should call
	\c #MakeSymbolPatternListed() on any symbols used by instances in the expanded art.
	It is not necessary to first call \c #IsSymbolPatternListed(); if the symbol is already
	listed, the call does nothing.

	Unlike art styles, for which being unlisted is tied to having an anonymous name
	(see \c #AIArtStyleSuite), an unlisted symbol can have any name. When you create
	unlisted symbols, you should give names that will make sense if they later become listed,
	so that Expand commands do not need to rename them without sufficient context.
	To avoid name conflicts, use names that are unlikely to be chosen by a user.

	For example, if a particle system or brush generates unlisted symbols by
	tinting listed symbols, it can use names like 'Snowflake autotinted
	10Y' and 'Snowflake autotinted 8C 5M', where Snowflake is the name of the listed
	symbol, and the word 'autotinted' is in a string resource that can be
	localized. Using 'autotinted' instead of simply 'tinted' decreases
	the likelihood that a user would coincidentally assign that name to a listed
	symbol.

*/
typedef struct {

	/** Counts the number of symbol definitions in the global list for the current document.
		Use with \c #GetNthSymbolPattern() to iterate through listed or through listed and
		unlisted symbols.
			@param count [out] A buffer in which to return the number of symbols.
			@param includeUnlisted When true, include unlisted symbols in the count.
				When false, count only listed symbols. See @ref ListedUnlistedSymbols.
		*/
	AIAPI AIErr (*CountSymbolPatterns) ( ai::int32 *count, ASBoolean includeUnlisted );

	/** Retrieves a symbol pattern from the global list for the current document.Use
		with \c #CountSymbolPatterns() to iterate through listed or through listed and
		unlisted symbols.
			@param n The 0-based position index.
			@param symbolPattern [out] A buffer in which to return the symbol reference.
			@param includeUnlisted When true, get both listed and unlisted symbols.
				When false, get only listed symbols. See @ref ListedUnlistedSymbols.
		*/
	AIAPI AIErr (*GetNthSymbolPattern) ( ai::int32 n, AIPatternHandle *symbolPattern, ASBoolean includeUnlisted );

	/** Retrieves a symbol pattern by name from the current document.
			@param name The name string.
			@param symbolPattern [out] A buffer in which to return the symbol reference,
				or a \c NULL object if no such symbol is found.
		*/
	AIAPI AIErr (*GetSymbolPatternByName) ( const ai::UnicodeString& name, AIPatternHandle *symbolPattern );

	/** Retrieves a symbol pattern by name from a specified document.
			@param name The name string.
			@param symbolPattern [out] A buffer in which to return the symbol reference,
				or a \c NULL object if no such symbol is found.
			@param document The document. Use the \c #AIDocumentListSuite
				or \c #AIPathStyleSuite::ImportStyles()	to obtain a document handle.
		*/
	AIAPI AIErr (*GetSymbolByNameFromDocument) ( const ai::UnicodeString& name, AIPatternHandle *symbolPattern,
												   AIDocumentHandle document );

	/** Counts the number of symbol definitions in the global list of a specified document.
		Use with \c #GetNthSymbolPatternFromDocument() to iterate through listed (public) symbols.
			@param count [out] A buffer in which to return the number of symbols.
			@param document The document. Use the \c #AIDocumentListSuite
				or \c #AIPathStyleSuite::ImportStyles()	to obtain a document handle.
		*/
	AIAPI AIErr (*CountSymbolPatternsFromDocument) ( ai::int32* count, AIDocumentHandle document );

	/** Retrieves a symbol pattern from the global list for a specified document.
		Use with \c #CountSymbolPatternsFromDocument() to iterate through listed (public) symbols.
			@param n The 0-based position index.
			@param symbolPattern [out] A buffer in which to return the symbol reference.
			@param document The document. Use the \c #AIDocumentListSuite
				or \c #AIPathStyleSuite::ImportStyles()	to obtain a document handle.
		*/
	AIAPI AIErr (*GetNthSymbolPatternFromDocument) ( ai::int32 n, AIPatternHandle *symbolPattern,
													 AIDocumentHandle document );

	/** Creates a new symbol definition from specified source art, which is copied as
		the defining art for the new symbol.
			@param newSymbolPattern [out] A buffer in which to return the new symbol reference.
			@param definitionArt The source art, or \c NULL to create a symbol whose definition
				is an empty group.
			@param registrationPoint The registration point of the new symbol pattern.
			@param transformDefinitionArt True to move the registration point of the new symbol pattern to the canvas origin.
			@param unlisted When true, make the new symbol unlisted. Use \c #SetSymbolPatternName()
			to name unlisted symbols. See @ref ListedUnlistedSymbols.
 		*/
	AIAPI AIErr (*NewSymbolPattern) ( AIPatternHandle *newSymbolPattern, AIArtHandle definitionArt, AISymbolRegistrationPoint registrationPoint, ASBoolean transformDefinitionArt, ASBoolean unlisted );

	/** Creates a new listed symbol definition from selected art, which is copied as the
		defining art for the new symbol. If no art is selected, creates a symbol
		whose definition is an empty group.
			@param symbolPattern [out] A buffer in which to return the new symbol reference.
			@param registrationPoint The registration point of the new symbol pattern.
		*/
	AIAPI AIErr (*NewSymbolPatternFromSel) ( AIPatternHandle *symbolPattern , AISymbolRegistrationPoint registrationPoint);

	/** Creates a new listed symbol definition from selected art, which is copied as the
		defining art for the new symbol, and reports the bounds of the selected art.
		(You cannot call \c #AIArtSuite::GetArtBounds() for the symbol pattern art after
		defining it, because the definition art is copied and moved.) Use to insert an
		instance of the new symbol in place of the selection.
			@param symbolPattern [out] A buffer in which to return the new symbol reference.
			@param selectionBounds [out] A buffer in which to return the bounding box
				of the selected art.
			@param registrationPoint The registration point of the new symbol pattern.
		*/
	AIAPI AIErr (*NewSymbolPatternFromSelGetBounds) ( AIPatternHandle *symbolPattern, AIRealRect *selectionBounds , AISymbolRegistrationPoint registrationPoint);

	/** Deletes a symbol definition.
			@param symbolPattern The symbol reference.

            @return The error \c #kCantDeleteSymbolUsedInLiveEffectsErr if the symbol pattern is used in a Live Effect.
                    The error \c #kBadParameterErr if NULL is passed.
		*/
	AIAPI AIErr (*DeleteSymbolPattern) ( AIPatternHandle symbolPattern );

	/** Reports whether a symbol is still known to the system. A symbol reference can
		change if you retain it between message. To ensure a valid reference, get
		the reference from the \c #kAIArtSymbolSetChangedNotifier.  </br>
		(Note that this function returns a Boolean value, not an error code.)
			@param symbolPatter The symbol reference.
			@return True if the symbol is a valid reference.
		 */
	AIAPI AIBoolean (*ValidateSymbolPattern) ( AIPatternHandle symbolPattern );


	// Functions for examining and modifying a symbol definition

	/** Retrieves a read-only handle to the definition art of a symbol. You can examine or
		duplicate the returned art, but cannot edit it.
			@param pattern The symbol pattern reference.
			@param art [out] A buffer in which to return the definition art.
		*/
	AIAPI AIErr (*GetSymbolPatternArt) ( AIPatternHandle pattern, AIArtHandle *art );

	/** Creates a copy of a symbol pattern's definition artwork and places it
		into the current document at the center of the current view, at the current
		layer and using the current insertion mode. It is the equivalent of using
		a simple Paste command.
			@param symbolPattern The symbol pattern reference.
			@return The error \c #kUntouchableLayerErr if the current layer or
				current insertion group is locked or hidden.
			@see \c #AIPatternSuite::GetPattern()
			@note To get an editable copy of a symbol, it is better to use
				\c #AIDictionarySuite::NewArtEntry() to create a group that
				is not in the artwork tree, insert the definition copy into that
				using \c #CopySymbolPatternArt(), and then delete the dictionary entry.
				This avoids modifying the art tree and triggering unneeded synchronization
				and change notifications. This technique is often used by export filters
				to make systematic adjustments to Illustrator art before converting
				it to an easy-to-export form.
		*/
	AIAPI AIErr (*PasteSymbolPatternArt) ( AIPatternHandle symbolPattern );

	/** Creates a copy of a symbol pattern's definition artwork and places it
		into the current document at a specified place in the paint order.
			@param symbolPattern The symbol pattern reference.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] Optional. A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*CopySymbolPatternArt) ( AIPatternHandle symbolPattern,
		ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Creates a copy of source art and makes it the defining art for a symbol. Updates
		any existing instances of the symbol.
			@param symbolPattern The symbol pattern reference.
			@param definitionArt The source art.
			@param transformDefinitionArt True to move the registration point of the symbol pattern to the canvas origin.
		*/
	AIAPI AIErr (*SetSymbolPatternArt) ( AIPatternHandle symbolPattern, AIArtHandle definitionArt , ASBoolean transformDefinationArt);

	/** Copies selected art and makes it the defining art for a symbol. Updates
		any existing instances of the symbol.
			@param symbolPattern The symbol pattern reference.
			@see \c #AIPatternSuite::SetPattern()
		*/
	AIAPI AIErr (*SetSymbolPatternFromSel) ( AIPatternHandle symbolPattern );


	// The functions below use C strings. If you have or want Pascal strings, you can
	// also get and set the name of a symbol using GetPatternName and SetPatternName
	// from AIPattern.h.

	/** Retrieves the name of a symbol.
			@param symbolPattern The symbol pattern reference.
			@param name [out] A buffer in which to return the name string. Truncates
				a name that is too long to fit in the buffer.
			@return \c #kNameTooLongErr error if the name was truncated.
		*/
	AIAPI AIErr (*GetSymbolPatternName) ( AIPatternHandle symbolPattern, ai::UnicodeString& name );

	/** Sets the name of a symbol.
			@param name The new name string.
			@return \c #kNameTooLongErr error if the name length exceeds \c #kMaxSymbolNameLength.
		 		<br> \c #kInvalidNameErr error if the name contains illegal characters,
		 		is of zero length, or consists entirely of spaces.
				<br> \c #kNameInUseErr if the name is already used for another symbol.
		 		<br> In any error case, the symbol name remains unchanged.
			@see \c #SetSymbolPatternBaseName()
		 	 */
	AIAPI AIErr (*SetSymbolPatternName) ( AIPatternHandle symbolPattern, const ai::UnicodeString& name );

	/** Strips any hidden characters from the end of a symbol name to create
		a displayable string.
			@param name [in, out] The symbol name string, which is modified in place.
		*/
	AIAPI AIErr (*GetSymbolPatternDisplayName) ( ai::UnicodeString& name );

	/** Sets the name of a symbol, appending numbers to a name string that is
		already in use to make it unique. If the name string is very long,
		it can be truncated before the numbers are appended.
			@param symbolPattern The symbol pattern reference.
			@param name The new name string.
		*/
	AIAPI AIErr (*SetSymbolPatternBaseName) ( AIPatternHandle symbolPattern, ai::UnicodeString& name );

	/** Creates a new symbol instance in the center of the current document view.
			@param symbolPattern The symbol pattern reference.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] A buffer in which to return the new instance,
				an art object of type \c #kSymbolArt.
			@return \c #kBadParameterErr error if there are no symbols defined
				in the current document.
		*/
	AIAPI AIErr (*NewInstanceCenteredInView) ( AIPatternHandle symbolPattern,
								ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Creates a new symbol instance with its center at a specified location.
			@param symbolPattern The symbol pattern reference.
			@param center The location, in page coordinates.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] A buffer in which to return the new instance,
				an art object of type \c #kSymbolArt.
			@return \c #kBadParameterErr error if there are no symbols defined
				in the current document.
		*/
	AIAPI AIErr (*NewInstanceAtLocation) ( AIPatternHandle symbolPattern, AIRealPoint center,
								ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Creates a new symbol instance with a specified transformation matrix.
			@param symbolPattern The symbol pattern reference.
			@param transform The transformation matrix.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] A buffer in which to return the new instance,
				an art object of type \c #kSymbolArt.
			@return \c #kBadParameterErr error if there are no symbols defined
				in the current document.
		*/
	AIAPI AIErr (*NewInstanceWithTransform) ( AIPatternHandle symbolPattern, AIRealMatrix *transform,
								ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Retrieves the symbol pattern definition of a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param symbolPattern [out] A buffer in which to return the symbol pattern reference.
		*/
	AIAPI AIErr (*GetSymbolPatternOfSymbolArt) ( AIArtHandle symbolArt, AIPatternHandle *symbolPattern );

	/** Sets the symbol pattern definition of a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param symbolPattern The symbol pattern reference.
		*/
	AIAPI AIErr (*SetSymbolPatternOfSymbolArt) ( AIArtHandle symbolArt, AIPatternHandle symbolPattern );

	/** Retrieves the transformation matrix that Illustrator uses to transform specified symbol art
		into a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform [out] A buffer in which to return the transformation matrix.
 			@see \c #AIHardSoftSuite for a discussion of coordinate systems.
			@note	Use \c #AIHardSoftSuite::AIRealMatrixRealSoft() and
					\c #AIHardSoftSuite::AIRealMatrixRealHard() to translate between
					the hard and soft forms of the matrix (\e not
					\c #AIHardSoftSuite::AIRealMatrixHarden() and
					\c #AIHardSoftSuite::AIRealMatrixSoften(), which affect
					only the tx ty components).
			*/
	AIAPI AIErr (*GetHardTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/** Sets the application transformation matrix for a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform The new transformation matrix.
 			@see \c #GetHardTransformOfSymbolArt()
 		*/
	AIAPI AIErr (*SetHardTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/** Retrieves the transformation matrix that a plug-in can use to transform to transform
		specified symbol art into a symbol instance (using the \c #AITransformArtSuite).
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform [out] A buffer in which to return the transformation matrix.
 			@see \c #AIHardSoftSuite for a discussion of coordinate systems.
		*/
	AIAPI AIErr (*GetSoftTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/** Sets the plug-in transformation matrix for a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform The new transformation matrix.
 			@see \c #GetSoftTransformOfSymbolArt()
 		*/
	AIAPI AIErr (*SetSoftTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/**	Expands a symbol instance and places the resulting art into the artwork tree.
		The function preserves the appearance, not the editability, of the symbol
		definition.
			\li If the instance transformation matrix is a simple placement matrix,
				this is equivalent to \c #BreakLinkToSymbol().
			\li If the matrix includes a scale, rotation, shear, or reflection,
				the function expands any appearances or plug-in groups inside
				the symbol definition, then applies the matrix.
			\li If the matrix includes a shear or a non-uniform scale, the function
				expands strokes before applying the matrix.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
				This object is not deleted.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param expandedArt [out] Optional. A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*InsertExpandedSymbolArt) ( AIArtHandle symbolArt,
												ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *expandedArt );

	/** Reports whether a symbol definition is listed in the current document.
		If the symbol belongs to a different document, it will return false
		even if the symbol is listed in the document to which it belongs.
		See @ref ListedUnlistedSymbols for the definition of listed and unlisted symbols.  </br>
		(Note that this function returns a Boolean value, not an error code.)
			@param symbolPattern The symbol pattern reference.
			@return True if the symbol pattern is listed in the current document.
		*/
	AIAPI AIBoolean (*IsSymbolPatternListed) ( AIPatternHandle symbolPattern );

	/** Makes a symbol definition, which must be in the symbol set of the current document, listed.
		See @ref ListedUnlistedSymbols.
			@param symbolPattern The symbol pattern reference.
		*/
	AIAPI AIErr (*MakeSymbolPatternListed) ( AIPatternHandle symbolPattern );

	/** Makes a symbol definition unlisted. See @ref ListedUnlistedSymbols.
			@param symbolPattern The symbol pattern reference.
		*/
	AIAPI AIErr (*UnlistSymbolPattern) ( AIPatternHandle symbolPattern );

   	/**	Sorts the listed symbols in the global list of symbols, alphabetically by name.
 		See @ref ListedUnlistedSymbols.
 		*/
  	AIAPI AIErr (*SortListedSymbolPatterns) ( void );

	/** Moves a listed symbol to a specific index position in the global list of symbols.
		Increments the position of the symbol previously at that index, and of all
		subsequent listed symbols. See @ref ListedUnlistedSymbols.
			@param symbolPattern The symbol pattern reference.
			@param index The new 0-based index position, or -1 to move to the
				end of the list.
		*/
	AIAPI AIErr (*MoveSymbolPatternInList) ( AIPatternHandle symbolPattern, int index );

	/** Reports whether an art object uses a specified symbol in a specified way.  </br>
		(Note that this function returns a Boolean value, not an error code.)
			@param art The art object, or \c NULL to search the entire artwork tree.
				In this case, the search includes descendants regardless of the
				value of the \c #kSearchDescendants flag.
			@param searchScope The scope of the search, a logical OR of \c #AISymbolSearchScope
				bit flags.
			@param targetSymbol	The symbol reference, or \c NULL to search for any symbol.
			@param oneFoundSymbol [out] Optional. When \c targetSymbol is \c NULL, a buffer
				in which to return a single matching symbol found within the search scope,
				or \c NULL if more than one matching symbol is found.

			@note \c oneFoundSymbol is used by the Symbols palette to decide which symbol to select.
   				If an object uses multiple symbols, nothing is selected. The scope for this
   				type of usage should not include \c #kSearchNestedSymbolPatterns. For example, if
   				symbol A's definition includes symbol B, and the user selects an instance of
   				symbol A, symbol A should be selected in the palette. If the user selects
   				a particle set containing instances of both symbol A and symbol B,
   				neither symbol should be selected in the palette.

			@param allFoundSymbols [out] Optional. When \c targetSymbol is \c NULL,  a buffer
				 in which to return the handle of an array of matching symbols, of size \c foundCount.
				 This memory is allocated by the function, and you must free it using
				 \c #AIMdMemorySuite::MdMemoryDisposeHandle().

				 If no art object is specified, you can still specify the output array. This is how
  				the "Select All Unused" command in the Symbols palette is implemented.

				 If an art object is specified, use this array to examine patterns
				 that are referenced by a plug-in group that puts multiple symbols in its dictionary,
				 such as a particle set.
			@param foundCount [out] When \c targetSymbol is \c NULL, a buffer in which to
				return the size of the \c allFoundSymbols array.
			@param globalObjectUsage Not implemented.
			@return True if	any matching symbols are found.
		*/
	AIAPI AIBoolean (*ArtUsesSymbolPattern) ( AIArtHandle art, ai::int16 searchScope, AIPatternHandle targetSymbol,
											AIPatternHandle *oneFoundSymbol,
											AIPatternHandle ***allFoundSymbols, int *foundCount,
											int *globalObjectUsage);

	/**	Creates a copy of a symbol's definition artwork, transforms it
		using the matrix of a symbol instance, and places it into the
		current document at a specified place in the paint order. Transfers
		attributes from the symbol instance to the transformed art.

		Does not do any internal expansion of strokes, active styles or plug-in groups
		inside the symbol definition, even when a rotational or shear transform is applied.
		Preserves the full structure and editability of the	symbol definition,
		at the cost of sometimes not preserving the appearance of the instance.

		This is the equivalent of calling \c #CopySymbolPatternArt() and then performing
		the transformation using the \c #AITransformArtSuite, but is more efficient.
		If the instance matrix is a simple placement matrix, this is equivalent to
		\c #InsertExpandedSymbolArt().

			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
				This object is not deleted.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param expandedArt [out] Optional. A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*BreakLinkToSymbol) ( AIArtHandle symbolArt,
												ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *expandedArt );

	/**	Retargets a symbol pattern, fill pattern, or brush pattern for the current document.
		Creates a new pattern if needed, with the same definition art and a unique name based on
		the source pattern's name. All other global objects (colors, patterns, brushes, styles,
		 and so on) used indirectly in the definition are similarly retargeted, using
		an existing object if one matches and creating a new one otherwise.

		The new pattern is made listed in the current document if it was listed in the source
		document, and made unlisted in the current document if it was unlisted in the source
		document. In this context, a listed symbol never matches an unlisted one, even if it has
		the same name and definition.

       	Use for drag-and-drop between library palettes and the main document palette.
		 	@param srcPattern A symbol pattern, fill pattern, or brush pattern reference.
			@param dstPattern [out] A buffer in which to return the new pattern, or
				an existing pattern in the current document with the same name and definition,
				or the source pattern if it was already in the current document.

			@note Fill patterns are usually retargeted indirectly using the
				\c #AIPathStyleSuite, and brush patterns using the \c #AIObjectSetSuite.
			 @see \c #AIPatternSuite, \c #AIObjectSetSuite::RetargetForCurrentDocument(),
				\c #AIPathStyleSuite::RetargetForCurrentDoc(), \c #RetargetForCurrentDocumentAsUnlisted()
			*/
	AIAPI AIErr (*RetargetForCurrentDocument) ( AIPatternHandle srcPattern, AIPatternHandle *dstPattern );

	// New for Illustrator 11:

	/** Creates a copy of a symbol pattern's definition artwork, converts it to outline
		using specified options, and places the result into the current document
		at a specified place in the paint order.
			@param symbolPattern The symbol pattern reference.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] Optional. A buffer in which to return the new art object, or
				a \c NULL object if no outline can be generated.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values:
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
		*/
	AIAPI AIErr (*CopySymbolPatternOutline) ( AIPatternHandle symbolPattern,
		ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *newArt, ai::int32 convertToOutlineOptions );

	/** Expands a symbol definition, outlines the symbol definition, applies the instance
		transformation to the outlined definition art. and finally places the transformed
		outline art into the artwork tree.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
				This object is not deleted.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param expandedArt [out] Optional. A buffer in which to return result art.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values:
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
			@see \c #InsertExpandedSymbolArt()
		*/
	AIAPI AIErr (*InsertSymbolArtOutline) ( AIArtHandle symbolArt,
		ai::int16 paintOrder, AIArtHandle prep, AIArtHandle *expandedArt, ai::int32 convertToOutlineOptions );

	/** Retrieves a cached outline for a symbol pattern, if one has been generated for a given
		set of conversion options. You can examine or duplicate the returned outline art, but cannot edit it.
			@param symbolPattern The symbol pattern reference.
			@param outlineArt [out] A buffer in which to return	the cached outline art, or \c NULL
				if no cached outline has been generated for the given options.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values:
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
		*/
	AIAPI AIErr (*PeekCachedPatternOutline) ( AIPatternHandle symbolPattern, AIArtHandle *outlineArt, ai::int32 convertToOutlineOptions );

	// New for Illustrator 13:

	/** Sets a symbol definition from selected art, and reports the bounds of the selected art.
			@param symbolPattern The symbol pattern reference.
			@param selectionBounds [out] Optional. A buffer in which to return the bounding box
				of the selected art.
			@see \c #NewSymbolPatternFromSelGetBounds.
		*/
	AIAPI AIErr (*SetSymbolPatternFromSelGetBounds) ( AIPatternHandle symbolPattern, AIRealRect *selectionBounds );


	/** Sets the symbol export type for a symbol pattern, to use when exporting the
	    symbol to Flash.
			@param symbolPattern The symbol pattern reference.
			@param exportType	 The Flash export type.
		*/
	AIAPI AIErr (*SetSymbolExportType) ( AIPatternHandle symbolPattern, AISymbolFlashExportType exportType);

	/** Retrieves the symbol export type for a symbol pattern, used when exporting the symbol
	    to Flash.
			@param symbolPattern The symbol pattern reference.
			@param exportType [out]	 The Flash export type.
		*/
	AIAPI AIErr (*GetSymbolExportType) ( AIPatternHandle symbolPattern, AISymbolFlashExportType *exportType);


	/** Sets the symbol "Enable guides for 9-slice scaling" option for a symbol pattern,
		to use when exporting the symbol to Flash.
	@param symbolPattern		The symbol pattern reference.
			@param enableGuides	 True to turn 9-slice scaling on, false to turn it off.
	*/
	AIAPI AIErr (*SetSymbolEnableGuides) ( AIPatternHandle symbolPattern, AIBoolean enableGuides);

	/** Retrieves the symbol "Enable guides for 9-slice scaling" option for a symbol pattern,
		used when exporting the symbol to Flash.
	@param symbolPattern			The symbol pattern reference.
			@param enableGuides [out]	A buffer in which to return true if
				9-slice scaling is on, false if it is off.
	*/
	AIAPI AIErr (*GetSymbolEnableGuides) ( AIPatternHandle symbolPattern, AIBoolean *enableGuides);

	/** Sets the symbol scaling grid for 9-slice scaling for a symbol pattern,
		to be used when exporting the symbol to Flash.
	@param symbolPattern		The symbol pattern reference.
			@param slice9Grid		The rectangular area of the center slice.
	*/
	AIAPI AIErr (*SetSymbol9SliceGrid) ( AIPatternHandle symbolPattern, AIRealRect slice9Grid);

	/** Retrieves the symbol scaling grid for 9-slice scaling for a symbol pattern,
		used when exporting the symbol to Flash.
	@param symbolPattern			The symbol pattern reference.
			@param slice9Grid [out]		A buffer in which to return the rectangular area of the center slice.
	*/
	AIAPI AIErr (*GetSymbol9SliceGrid) ( AIPatternHandle symbolPattern, AIRealRect *slice9Grid);

	// Symbol editing workflow (new in AI13/CS3)

	/** Starts an editing session for a symbol pattern.

    	Invokes isolation mode on a copy of the prototype of the pattern, and places the
		copy on the artboard. If a symbol art is specified, the copy is placed in the same
		location as the symbol instance, hiding the original. Otherwise, the copy is placed in the
		center of the artboard.

		You can start nested editing sessions for nested symbols.

		Editing changes are signaled with \c #AILayerList::kAIIsolationModeChangedNotifier
		and \c #AILayerList::kAIBeforeIsolationModeChangedNotifier. Use \c #ValidateSymbolEditingArt()
		to validate the art being edited.

		@post Use \c #EndEditingSymbolDefinition() to end the editing session, optionally updating
		the symbol pattern's prototype with the changes in the copy before returning it to
       	the artboard.

		@post Use \c #ExitSymbolEditMode() to force all symbol editing sessions to end without
		saving any changes.

			@param symbolPattern The symbol pattern reference.
			@param symbolArt Optional. A symbol art object whose definition needs to be edited.

		@return May return #AIIsolationMode::kCantIsolateFromCurrentModeErr
		*/
	AIAPI AIErr (*SetEditingSymbolDefinition) ( AIPatternHandle symbolPattern, AIArtHandle symbolArt);

	/** Ends an editing session for a symbol pattern, allowing you to apply or discard the changes
		made during the session. The corresponding symbol instance that was hidden when
	    setting the symbol in edit mode is made visible.
			@param symbolPattern The symbol pattern reference.
			@param updateSymbol True to apply the edits to the pattern, false to discard the editing
				changes and restore the original symbol pattern.
			@pre \c #SetEditingSymbolDefinition()
		*/
	AIAPI AIErr (*EndEditingSymbolDefinition) ( AIPatternHandle symbolPattern, AIBoolean updateSymbol);

	/** Reports whether symbol edit mode is active.	 </br>
		(Note that this function returns a Boolean value, not an error code.)
			@return True if at least one symbol pattern is being edited, false otherwise.
		*/
	AIAPI AIBoolean (*GetSymbolEditMode) ();

	/** Ends all current symbol editing sessions, restoring the original symbol pattern
		prototypes to the artboard and discarding all changes made while editing.

		To save any changes, and to restore the per-symbol editing state information,
		use \c #EndEditingSymbolDefinition() for each symbol being edited.
			@pre \c #SetEditingSymbolDefinition()
		*/
	AIAPI AIErr (*ExitSymbolEditMode) ( );

	/** Reports whether a symbol pattern is currently being edited.	 </br>
		(Note that this function returns a Boolean value, not an error code.)
			@param symbolPattern The symbol pattern reference.
			@return True if at the symbol pattern is being edited, false otherwise.
		*/
	AIAPI AIBoolean (*EditingSymbolPattern) (AIPatternHandle symbolPattern);

	/** Reports whether an art object represents the prototype of a symbol pattern that is
		currently being edited, and if true, optionally returns the pattern being edited.
			@param art			 The art object reference.
			@param symbolPattern [out] Optional. A buffer in which to return the symbol pattern.
			@return True if the art object does represent the prototype of a symbol pattern that is
				currently being edited, false otherwise.
		*/
	AIAPI AIBoolean (*IsSymbolEditingArtType) ( AIArtHandle art, AIPatternHandle *symbolPattern);

	/** Validates the editing art object that represents the prototype of a
		symbol pattern that is being edited.
		The editing art could become invalid due to operations such as duplicate or delete.
		If the symbol pattern's editing art is not a valid art object, looks under the parent
		for an art object whose state represents the editing art of the given symbol pattern,
		and sets it as the valid editing art. If there is no valid art object under the parent,
		creates an empty group and sets it as the valid editing art.

		Use this in response to the \c #AILayerList::kAIBeforeIsolationModeChangedNotifier,
		with the information received by calling \c #AIIsolationModeSuite::GetIsolatedArtAndParents().
			@param symbolPattern The symbol pattern reference.
			@param editingArtParent	Parent object that contains the editing art.
		*/
	AIAPI AIErr (*ValidateSymbolEditingArt) ( AIPatternHandle symbolPattern, AIArtHandle editingArtParent);

	/** Sets the Pixel Perfect status for a symbol and its instances.
	@param symbolPattern		The symbol pattern reference.
	@param isPixelPerfect		True to make the symbol and its instances Pixel Perfect, false otherwise.
	*/
	AIAPI AIErr (*SetSymbolPixelPerfect) ( AIPatternHandle symbolPattern, AIBoolean isPixelPerfect);

	/** Retrieves a symbol's Pixel Perfect status.
	@param symbolPattern			The symbol pattern reference.
	@param isPixelPerfect [out]		A buffer in which to return true if the symbol is Pixel Perfect, false otherwise.
	*/
	AIAPI AIErr (*GetSymbolEnablePixelPerfect) ( AIPatternHandle symbolPattern, AIBoolean* isPixelPerfect);

	/** Reports whether symbol art is scaled with 9-slice scaling. Not all instances
	of a symbol pattern that has 9-slice scaling guides actually use 9-slice scaling.
	For example, an instance can have no scaling.
	@param symbolArt [in] The symbol instance, an art object of type \c #kSymbolArt.
	@param is9SliceScaled [out] A buffer in which to return true if the symbol art is scaled with 9-slice scaling.
	*/

	AIAPI AIErr (*IsSymbolArt9SliceScaled) (AIArtHandle symbolArt, AIBoolean* is9SliceScaled);

	/**	Retargets a symbol pattern, fill pattern, or brush pattern for the current document.
		Creates a new pattern if needed, with the same definition art and a unique name based on
		the source pattern's name. All other global objects (colors, patterns, brushes, styles,
		 and so on) used indirectly in the definition are similarly retargeted, using
		an existing object if one matches and creating a new one otherwise.

		The new pattern is NOT made listed in the current document, even if it was listed in the source
		document.

       	Use this function when the source symbol is in a document that is being used
	   	as a content resource to support an effect, such as 3D Bevels or Arrowheads, where
	   	you might want the symbols to be visible in the Symbols panel of the resource document, but
	   	not in the Symbols panel of the documents where the effect is in use.

	   	This differs from first calling \c #RetargetForCurrentDocument() and then \c #UnlistSymbolPattern()
	   	in that \c #RetargetForCurrentDocument() causes a \c #kAIArtSymbolListChangedNotifier to be sent,
	   	and this function does not, thereby circumventing any notification to clients who care only
	   	about changes to listed symbols.

		 	@param srcPattern A symbol pattern, fill pattern, or brush pattern reference.
			@param dstPattern [out] A buffer in which to return the new pattern, or
				an existing pattern in the current document with the same name and definition,
				or the source pattern if it was already in the current document.

			@note Fill patterns are usually retargeted indirectly using the
				\c #AIPathStyleSuite, and brush patterns using the \c #AIObjectSetSuite.
			 @see \c #AIPatternSuite, \c #AIObjectSetSuite::RetargetForCurrentDocument(),
				\c #AIPathStyleSuite::RetargetForCurrentDoc()
			*/
	AIAPI AIErr (*RetargetForCurrentDocumentAsUnlisted) ( AIPatternHandle srcPattern, AIPatternHandle *dstPattern );

	/** Deletes a symbol definition and expands or deletes the instances of symbol as per the choice taken
	@param symbolPattern The symbol reference. 
	@param deleteChoice, expand or delete the instance as per the enum SymbolDeleteChoice.
	@return The error \c #kBadParameterErr if NULL is passed. If symbol is used in effect dictionaries then the artstyle is marked dirty and the next execution is expected to take care of the deleted symbol
	This api is slower since it involves expansion/delete of instance so use it only if you want exactly this behavior
	*/
	AIAPI AIErr(*DeleteSymbolPatternEx) (AIPatternHandle srcPattern, ai::uint32 deleteChoice);

} AISymbolSuite;


/*******************************************************************************
 **
 **	AISymbolPalette suite
 **
 **/


/** @ingroup Suites
	These functions access and manipulate the currency and selection state
	of symbols. The suite is exported by the Symbols palette, which is not a
	required plug-in, so it can be unavailable. Selection and currency of
	symbols is not otherwise supported.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISymbolPaletteSuite and \c #kAISymbolPaletteVersion.
	*/
typedef struct {
	/** Retrieves the current symbol.
			@param symbolPattern [out] A buffer in which to return the symbol reference.
		*/
	AIAPI AIErr	(*GetCurrentSymbol) ( AIPatternHandle *symbolPattern );

	/** Makes a symbol current.
			@param symbolPattern The symbol reference.
		*/
	AIAPI AIErr (*SetCurrentSymbol) ( AIPatternHandle symbolPattern );

	/** Reports the selection state of a symbol. </br>
		(Note that this function returns a Boolean value, not an error code.)
			@param symbolPattern The symbol reference.
			@return True if the symbol is selected.
		*/
	AIAPI AIBoolean (*IsSymbolSelected) ( AIPatternHandle symbolPattern );

	/** Counts selected symbols. Use with \c #GetNthSelectedSymbol() to
		iterate through selected symbols.  </br>
		(Note that this function returns a numeric value, not an error code.)
			@return The number of selected symbols.
		*/
	AIAPI ai::int32 (*CountSelectedSymbols) ( void );

	/** Retrieves a selected symbol by position index. Use with
		\c #CountSelectedSymbols() to iterate through selected symbols.
			@param n The 0-based position index.
			@param symbolPattern [out] A buffer in which to return the symbol reference.
		*/
	AIAPI AIErr (*GetNthSelectedSymbol) ( ai::int32 n, AIPatternHandle *symbolPattern );

	/** Reports whether the Symbol palette is visible.	 </br>
		(Note that this function returns a Boolean value, not an error code.)
			@return True if the Symbol palette is shown.
		*/
	AIAPI AIBoolean (*IsPaletteVisible) ( void );
} AISymbolPaletteSuite;


#include "AIHeaderEnd.h"


#endif
