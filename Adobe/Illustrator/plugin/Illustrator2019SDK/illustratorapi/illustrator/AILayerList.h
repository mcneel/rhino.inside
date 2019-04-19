#ifndef __AILayerList__
#define __AILayerList__

/*
 *        Name:	AILayerList.h
 *   $Revision: 3 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Layer List Suite.
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

#ifndef __SPPlugins__
#include "SPPlugs.h"
#endif

#include "AIHeaderBegin.h"

/** @file AILayerList.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAILayerListSuite				"AI Layer List"
#define kAILayerListSuiteVersion4		AIAPI_VERSION(4)
#define kAILayerListSuiteVersion		kAILayerListSuiteVersion4
#define kAILayerListVersion				kAILayerListSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/


/** An opaque reference to a layer list. */
typedef struct LayerList*			AILayerList;


/** @ingroup Callers
	Caller for layer list messages. See \c #AILayerListSuite.
	 */
#define kCallerAILayerList				"AI Layer List"

/** @ingroup Selectors
	Sent to the plug-in owning a layer list when it is pushed onto
	the stack. Allows you to initialize the layer list. Within the scope
	of the message, you can modify both the	previous layer list
	and the newly pushed list. On return, the previous layer
	list can no longer be modified.

	The data of the message is an \c #AILayerListMessage. The
	message's \c data field contains the value passed to
	\c #AILayerListSuite::Push().
	 */
#define kSelectorAIPushLayerList		"AI Push Layer List"

/** @ingroup Selectors
	Sent to the plug-in owning a layer list when it is popped.
	Allows you to clean up the layer lists. Within the scope of
	the message you can modify both the previous layer list and
	the one about to be popped.

	The data of the message is an \c #AILayerListMessage.
	 */
#define kSelectorAIPopLayerList			"AI Pop Layer List"

/** @ingroup Selectors
	Sent to the plug-in owning a layer list to request
	that it dispose of any data it allocated on push. The
	data of the message is an \c #AILayerListMessage.
	 */
#define kSelectorAIDeleteLayerList		"AI Delete Layer List"

/** The message data for layer list messages.  */
typedef struct {
	/** The message data. */
	SPMessageData		d;
	/** The layer list that is pushed, popped, or deleted. */
	AILayerList			list;
	/** Data passed from \c #AILayerListSuite::Push() for the
		\c #kSelectorAIPushLayerList selector.*/
	void*				data;
} AILayerListMessage;


/** @ingroup Notifiers
	Sent when a layer list is pushed or popped. See \c #AILayerListSuite.
 */
#define kAILayerListChangedNotifier	"AI Edit Layer List Changed Notifier"

/** Controls how the contents of a layer list are rendered.
	A logical OR of an \c #AILayerListModeRenderingOptions value
	and an \c #AILayerListModePreviewOptions value.
	Predefined combinations are defined by \c #AILayerListModeValues.
	*/
typedef ai::int32 AILayerListMode;

/** What is rendered when a layer list is drawn.
	@see \c #AILayerListMode <br> \c #AILayerListModeValues */
enum AILayerListModeRenderingOptions {
	/** Mask value to isolate the rendering option bits from the \c #AILayerListMode. */
	kAILayerListRenderMask			= (0x000000FF),
	/** Render only the selection highlighting on the layer list. */
	kAILayerListRenderSelection		= (1<<0),
	/** Render both the selection highlighting and the previews of the objects
		on the layer list. */
	kAILayerListRenderPreview		= (1<<1)
};

/** How previews of objects on a layer list are drawn,
	when \c #AILayerListModeRenderingOptions::kAILayerListRenderPreview is set.
	@see \c #AILayerListMode <br> \c #AILayerListModeValues */
enum AILayerListModePreviewOptions {
	/** Mask value to isolate the preview option bits from the \c #AILayerListMode. */
	kAILayerListPreviewMask			= (0x00000F00),
	/** Draw a full color preview. */
	kAILayerListPreviewColor		= (0<<8),
	/** Draw a grayscale preview. */
	kAILayerListPreviewGray			= (1<<8)
};

/** Pre-defined combinations of \c #AILayerListModeRenderingOptions and
	\c #AILayerListModePreviewOptions.
	@see \c #AILayerListMode */
enum AILayerListModeValues {
	/** Draws neither selection highlighting nor the preview
		of objects. */
	kAILayerListInvisibleMode		= 0,
	/** Draws only the selection highlighting of selected
		objects in the layer list. */
	kAILayerListSelectionMode		= kAILayerListRenderSelection,
	/** Draws both selection highlighting and preview of the
		objects. */
	kAILayerListPreviewMode			= (kAILayerListRenderSelection|kAILayerListRenderPreview),
	/** Draws both the selection highlighting and a grayscale
		preview of the objects. */
	kAILayerListGrayscaleMode		= (kAILayerListRenderSelection|kAILayerListRenderPreview|kAILayerListPreviewGray)
};


/** Controls the types of editing operations allowed
	for a layer list, one of the \c #AILayerListEditabilityModeValues.
 */
typedef ai::int32 AILayerListEditabilityMode;

/** Layer list editability modes. */
enum AILayerListEditabilityModeValues {
	/** Allows all types of edits. Set by default when a new layer list is pushed. */
	kAIRegularEditabilityMode		= 0,
	/** Forces the Layers palette to disable the new layer and new
	sublayer functionality. Transparency mask layer lists use this mode. */
	kAINoNewLayersMode				= (1<<0)
};


/** Tag for the document layer list. */
#define kAIDocumentLayerList			"AI Document Layer List"
/** Tag for a transparency mask layer list. */
#define kAITransparencyMaskLayerList	"AI Transparency Mask Layer List"

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The artwork in an Illustrator document is contained within layers. A list
	of layers, the \e document \e layer \e list, is saved when a document
	is saved. It is possible to create new layer lists, which are maintained in a stack.
	The bottommost list on the stack is the document layer list. The topmost list,
	called the \e current layer list, contains artwork that the user is
	currently editing.

	Editing operations do not normally affect objects in layer lists below
	the current list.Most functions operate only on layers in the current layer list.
	For example, the \c #AILayerSuite allows you to access the layers in a list sequentially, but
	the functions operate only on the current list. Similarly the \c #AIMatchingArtSuite
	functions operate only on the current layer list.

	\li Each layer list has a \e display mode, which affects how the contents of the
	layer list are drawn, and an \e editability mode, which affects the
	editing operations allowed on the list.

	\li Each layer list is given a \e tag when it is pushed onto the stack, which
	identifies the purpose of the list, either \c #kAIDocumentLayerList
	or \c #kAITransparencyMaskLayerList.

	There is one notifier associated with the layer lists,
	\c #kAILayerListChangedNotifier.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAILayerListSuite and \c #kAILayerListVersion.
*/

typedef struct {

	/** Creates a new layer list and pushes it onto the stack, making it
		current. The plug-in receives the \c #kSelectorAIPushLayerList
		message before the call returns, allowing it to initialize
		the list.
			@param self This plug-in
			@param tag The type of list, one of \c #kAIDocumentLayerList
				or \c #kAITransparencyMaskLayerList.
			@param data A pointer to developer-defined data to be passed
				to \c #kSelectorAIPushLayerList in \c #AILayerListMessage::data.
				Parameter may be \c NULL.
			@param mode The display and editability mode of the new layer list.
			@param list [out] A buffer in which to return the new layer list.
				This memory is not freed until it is no longer needed for undo/redo.
				of push or pop operations. The plug-in must preserve its private data for
				the list until it receives the \c #kSelectorAIDeleteLayerList message.
				Parameter may be \c NULL.
	*/
	AIAPI AIErr (*Push) (SPPluginRef self, char* tag, void* data,
			AILayerListMode mode, AILayerList* list);

	/** Pops the current layer list from the top of the layer list stack. The plug-in
		that pushed the layer list receives the \c #kSelectorAIPopLayerList message
		which allows it to perform any actions associated with the pop, even if it
		did not initiate the pop.
		*/
	AIAPI AIErr (*Pop) (void);

	/** Retrieves both the layer list and the layer on which an art object resides, if any.
			@param art The art object.
			@param list [out] A buffer in which to return the layer list, or \c NULL
				if this information is not needed.
			@param layer [out] A buffer in which to return the layer, or \c NULL
				if this information is not needed.
 		*/
	AIAPI AIErr (*GetLayerOfArt) (AIArtHandle art, AILayerList* list, AILayerHandle* layer);

	/** Gets the number of layer lists on the stack. Use with \c #GetFirst()
		and \c #GetNext() to iterate through lists.
			@param count [out] A buffer in which to return the number of layer lists.
		*/
	AIAPI AIErr (*Count) (ai::int32* count);

	/** Retrieves the current layer list (the most recently pushed list at the top
		of the stack).
			@param list [out] A buffer in which to return the layer list.
		*/
	AIAPI AIErr (*GetFirst) (AILayerList* list);

	/** Retrieves the document layer list (the bottom of the stack).
			@param list [out] A buffer in which to return the layer list.
	*/
	AIAPI AIErr (*GetLast) (AILayerList* list);

	/** Retrieves the next lower layer list in the stack.
			@param list A layer list in the stack.
			@param next [out] A buffer in which to return the next layer list,
				or \c NULL if this is the lowest list.
		*/
	AIAPI AIErr (*GetNext) (AILayerList list, AILayerList* next);

	/** Gets the number of layers in a layer list. Use with \c #GetFirstLayer()
		and \c #GetNextLayer() to iterate through the layers.
			@param list The layer list.
			@param count [out] A buffer in which to return the number of layers.
		*/
	AIAPI AIErr (*CountLayers) (AILayerList list, ai::int32* count);

	/** Retrieves the topmost layer in the stacking order of a layer list.
			@param list The layer list.
			@param layer [out] A buffer in which to return the layer.
		*/
	AIAPI AIErr (*GetFirstLayer) (AILayerList list, AILayerHandle* layer);

	/** Retrieves the bottommost layer in the stacking order of a layer list.
			@param list The layer list.
			@param layer [out] A buffer in which to return the layer.
		 */
	AIAPI AIErr (*GetLastLayer) (AILayerList list, AILayerHandle* layer);

	/** Retrieves the next lower layer in the stacking order of a layer list.
			@param list The layer list.
			@param layer A layer in the list.
			@param layer [out] A buffer in which to return the next lower layer,
				 or \c NULL if this is the lowest layer.
		 */
	AIAPI AIErr (*GetNextLayer) (AILayerList list, AILayerHandle layer, AILayerHandle* next);

	/** Retrieves the next higher layer in the stacking order of a layer list.
			@param list The layer list.
			@param layer A layer in the list.
			@param layer [out] A buffer in which to return the next higher layer,
				 or \c NULL if this is the highest layer.
		  */
	AIAPI AIErr (*GetPrevLayer) (AILayerList list, AILayerHandle layer, AILayerHandle* prev);

	/** Sets the display mode to be used when rendering the layer list.
			@param list The layer list.
			@param mode The new display mode, an \c #AILayerListModeValues value.
		*/
	AIAPI AIErr (*SetDisplayMode) (AILayerList list, AILayerListMode mode);

	/** Retrieves the display mode used when rendering the layer list.
		(Note that this function returns a constant value, not an error code.)
			@param list The layer list.
			@return  The display mode, an \c #AILayerListModeValues value.
		*/
	AIAPI AILayerListMode (*GetDisplayMode) (AILayerList list);

	/** Retrieves the tag that identifies the purpose of a layer list.
		(Note that this function returns a constant value, not an error code.)
			@param list The layer list.
			@return  The tag, \c #kAIDocumentLayerList or \c #kAITransparencyMaskLayerList. */
	AIAPI const char* (*GetTag) (AILayerList list);

	/** Sets the editability mode of a layer list. Use to set non-default
		editability for a transparency-mask layer. It is best to set this immediately
		after initializing the layer list, while processing the
		\c #kSelectorAIPushLayerList message. You cannot modify the
		editability mode of the document layer list.
			@param list The layer list.
			@param mode The new editability mode, one of the
				\c #AILayerListEditabilityModeValues.
		*/
	AIAPI AIErr (*SetEditabilityMode) ( AILayerList list, AILayerListEditabilityMode mode );

	/** Retrieves the editability mode of a layer list.
		(Note that this function returns a constant value, not an error code.)
			@param list The layer list.
			@return The mode, one of the \c #AILayerListEditabilityModeValues.
	*/
	AIAPI AILayerListEditabilityMode (*GetEditabilityMode) (AILayerList list);

} AILayerListSuite;


#include "AIHeaderEnd.h"


#endif
