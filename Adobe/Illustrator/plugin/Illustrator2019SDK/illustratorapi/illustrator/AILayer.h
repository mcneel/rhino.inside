#ifndef __AILayer__
#define __AILayer__

/*
 *        Name:	AILayer.h
 *   $Revision: 12 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Layers.
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

#include "IAIUnicodeString.h"


#include "AIHeaderBegin.h"

/** @file AILayer.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAILayerSuiteVersion10		AIAPI_VERSION(13)		// Illustrator 12.0


#define kAILayerSuite				"AI Layer Suite"
#define kAILayerSuiteVersion		kAILayerSuiteVersion10		// The current version

#define kAILayerVersion				kAILayerSuiteVersion

/** @ingroup Notifiers
	Sent when a new layer becomes current,	but no changes are made to the layers
	themselves (options, names, ordering, and so on.)
	 */
#define kAICurrentLayerNotifier			"AI Current Layer Notifier"
/** @ingroup Notifiers
	Sent when layers are deleted. \c #kAILayerSetNotifier is sent at the same time.
	Subscribe to this one if you care ONLY about deletions, but NOT new layers or
	reorderings; for example, to remove references to deleted layers,
	 */
#define kAILayerDeletionNotifier		"AI Layer Deletion Notifier"
/** @ingroup Notifiers
	Sent when layers are added, deleted, or reordered. Respond, for example,
	by rebuilding the list for a layer palette.
	 */
#define kAILayerSetNotifier				"AI Layer Set Notifier"
/** @ingroup Notifiers
	Sent when layers have changed options, such as name, selection color,
	lock status, visibility, view mode, and so on.)
	*/
#define kAILayerOptionsNotifier			"AI Layer Options Notifier"
	/** @ingroup Notifiers
	Sent when an art style is applied to a layer
	*/
#define kAILayerArtStyleChangeNotifier	"AI Layer Art Style Change Notifier"


/** @ingroup Errors
	See \c #AILayerSuite.  */
#define kCantDeleteLastLayerErr			'!XLL'


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The artwork in an Illustrator document is contained within layers. The document
	has a stack of lists of layers. The topmost list of layers in the stack are the
	ones currently being edited. See the \c #AILayerListSuite.

	Each layer contains a group of objects, which can include sublayers.
	All documents begin with at least one layer, and the user or a plug-in
	can add any number of new layers to it. A layer is a container for
	an artwork tree; use \c #AIArtSuite::GetFirstArtOfLayer()
	to get the group of art objects belonging to a layer.

	In addition to containing artwork, a layer has a name, a color
	(used to indicate selected art), and state flags that indicate whether
	it is visible, editable or locked, printable, and whether it displays
	placed art as dimmed. A layer reference is opaque; use the functions
	in this suite to get and set layer properties.

    Several layer properties affect whether the artwork on the layer is editable.
	Normally objects on a non-editable layer cannot be selected, so plug-ins
	that operate on the current selection need not check.  However, in
	iterating through layers or artwork, call \c #GetLayerEditable() on each
	layer before attempting to make any changes to the artwork.

	A layer can be designated as a \e template layer, which contains template
	artwork being used to guide the construction of the document artwork.
	For example, a template might contain an image that is being traced. Template
	layers are never printed or exported to final-form file formats.

	There are four notifiers associated with layers:
	<br> \c #kAICurrentLayerNotifier
	<br> \c #kAILayerDeletionNotifier
	<br> \c #kAILayerSetNotifier
	<br> \c #kAILayerOptionsNotifier

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAILayerSuite and \c #kAILayerVersion.
*/
typedef struct {

	/** Gets the number of top-level layers in the current document
		layer list.	Use with \c #GetNthLayer() to iterate through
		a document's layers.
			@param count [out] A buffer in which to return the number
				of layers, or 0 if there is no current document.
		*/
	AIAPI AIErr (*CountLayers) ( ai::int32 *count );

	/** Retrieves a top-level layer by index from the current document.
		Use with \c #CountLayers() to iterate through a document’s layers.
		The layer with index 0 is the topmost layer in the stacking order.
			@param n The index, in the range [0..numLayers-1].
				If \c n is greater than the number of layers, an error
				is returned and \c layer is set to \c NULL.
			@param layer [out] A buffer in which to return the layer, or
				\c NULL if the index is out of range.
	  		@note It is more efficient to iterate layers using \c #GetFirstLayer()
	  			and \c #GetNextLayer().
	  	*/
	AIAPI AIErr (*GetNthLayer) ( ai::int32 n, AILayerHandle *layer );

	/** Retrieves a reference to the current layer in the current document.
		This is the layer on which new artwork is created by default. It
		is indicated in the Layers palette by a black triangle.
			@param layer [out] A buffer in which to return the layer.
		*/
	AIAPI AIErr	(*GetCurrentLayer) ( AILayerHandle *layer );

	/** Makes a layer current. The current layer is the one in which new artwork
		is created by default. It is indicated in the Layers palette by a
		black triangle.
			@param layer The layer.
		*/
	AIAPI AIErr	(*SetCurrentLayer) ( AILayerHandle layer );

	/** Retrieves the topmost layer of the current document layer list.
		Use with \c #GetNextLayer to iterate through layers.
			@param first [out] A buffer in which to return the layer.
			@see \c #GetNextLayer(), \c #GetPrevLayer()
		*/
	AIAPI AIErr	(*GetFirstLayer) ( AILayerHandle *first );

	/** Retrieves the next layer below a given layer in the stacking order,
		at the same level of the layer list stack. Does not descend into
		sublayers.
			@param prev The previous layer, or \c NULL to get the topmost layer.
			@param next [out] A buffer in which to return the next layer, or
				\c NULL if there are no more layers.
			@see \c #GetFirstLayer(), \c #GetPrevLayer()
		*/
	AIAPI AIErr	(*GetNextLayer) ( AILayerHandle prev, AILayerHandle *next );

	/** Adds a new layer to a document, inserting it into the layers' lists
		at a position in the paint order relative to an existing layer.
			@param layer The prepositional layer for \c paintOrder values
				\c #kPlaceAbove and \c #kPlaceBelow, or \c NULL for values
				\c #kPlaceAboveAll (inserts at 0) and
				\c #kPlaceBelowAll (inserts at \c count).
			@param paintOrder The paint order, relative to the \c layer object,
				an \c #AITypes::AIPaintOrder value. See \c #AIArtSuite::NewArt().
			@param newLayer [out] A buffer in which to return the new layer.
		    @see \c #InsertLayerAtArt()
		*/
	AIAPI AIErr	(*InsertLayer) ( AILayerHandle layer, ai::int16 paintOrder, AILayerHandle *newLayer );

	/** Removes a layer and all of its contained art from the current document.
			@param layer The layer.
			@return An error \c #kCantDeleteLastLayerErr if \c layer is the only layer
				in the document.
		*/
	AIAPI AIErr	(*DeleteLayer) ( AILayerHandle layer );

	/** Retrieves the name of a layer.
			@param layer The layer.
			@param  title [out] A buffer in which to return the name.
		*/
	AIAPI AIErr (*GetLayerTitle) ( AILayerHandle layer, ai::UnicodeString& title );

	/** Sets the name of a layer.
			@param layer The layer.
			@param  title The new name.
		 */
	AIAPI AIErr (*SetLayerTitle) ( AILayerHandle layer, const ai::UnicodeString& newTitle );

	/** Retrieves the color used when outlining selected artwork in a layer.
			@param layer The layer.
			@param color [out] A buffer in which to return the	color.
		*/
	AIAPI AIErr (*GetLayerColor) ( AILayerHandle layer, AIRGBColor *color );

	/** Sets the color used when outlining selected artwork in a layer.
			@param layer The layer.
			@param color The new color.
	*/
	AIAPI AIErr (*SetLayerColor) ( AILayerHandle layer, AIRGBColor color );

	/** Reports the visibility status of a layer, which affects whether the artwork
		is drawn. If a parent layer's visibility status is false,
		artwork of a sublayer is not drawn, even if the sublayer's visibility
		status is true.
			@param layer The layer.
			@param visible [out] A buffer in which to return the output as true if art
				in this layer is visible.
		*/
	AIAPI AIErr (*GetLayerVisible) ( AILayerHandle layer, AIBoolean *visible );

	/** Sets the visibility status of a layer, which affects whether the artwork
		is drawn. If a parent layer's visibility status is false,
		artwork of a sublayer is not drawn, even if the sublayer's visibility
		status is true.
			@param layer The layer.
			@param visible True to make art	in this layer is visible, false
				to hide it.
		*/
	AIAPI AIErr (*SetLayerVisible) ( AILayerHandle layer, AIBoolean visible );

	/** Reports whether a layer specifies preview or outline mode.
		If a parent layer specifies outline mode, art in all sublayers is
		rendered in outline mode regardless of the sublayer settings.
			@param layer The layer.
			@param preview [out] A buffer in which to return true if
				this layer specifies preview mode; false if it
				specifies outline mode.
		*/
	AIAPI AIErr (*GetLayerPreview) ( AILayerHandle layer, AIBoolean *preview );

	/** Sets a layer to preview mode or outline mode.
		If a parent layer specifies outline mode, art in all sublayers is
		rendered in outline mode regardless of the sublayer settings.
			@param layer The layer.
			@param preview True to set preview mode, false to set outline mode.
	*/
	AIAPI AIErr (*SetLayerPreview) ( AILayerHandle layer, AIBoolean preview );

	/** Reports whether a layer is editable or locked. When a layer is
		editable, its artwork can be created or modified.
		If a parent layer is not editable, art in all sublayers
		cannot be edited, regardless of the sublayer settings.
			@param layer The layer.
			@param editable [out] A buffer in which to return true if
				this layer is editable; false if it is locked.
	  */
	AIAPI AIErr (*GetLayerEditable) ( AILayerHandle layer, AIBoolean *editable );

	/** Sets whether a layer is editable or locked. When a layer is
		editable, its artwork can be created or modified.
		If a parent layer is not editable, art in all sublayers
		cannot be edited, regardless of the sublayer settings.
			@param layer The layer.
			@param editable True to make this layer is editable, false
				to lock it.
		*/
	AIAPI AIErr (*SetLayerEditable) ( AILayerHandle layer, AIBoolean editable );

	/** Reports whether this layer is considered printable when printing the document.
		You can print all layers, visible layers or printable, visible layers.
			@param layer The layer.
			@param printed [out] A buffer in which to return true if
				this layer is printable; false if it is not.
		*/
	AIAPI AIErr (*GetLayerPrinted) ( AILayerHandle layer, AIBoolean *printed );

	/** Sets whether this layer is considered printable when printing the document.
		You can print all layers, visible layers or printable, visible layers.
			@param layer The layer.
			@param printed True to make	this layer printable, false to
				turn printability off.
		*/
	AIAPI AIErr (*SetLayerPrinted) ( AILayerHandle layer, AIBoolean printed );

	/** Reports whether images in a layer are dimmed (colors shifted toward white)
		when rendering. If a parent layer specifies dimming, images in sublayers
		are dimmed regardless of the sublayer setting.
			@param layer The layer.
			@param dimmed [out] A buffer in which to return true if
				this layer is dimmed; false if it is not.
		*/
	AIAPI AIErr (*GetLayerDimPlacedImages) ( AILayerHandle layer, AIBoolean *dimmed );

	/** Sets whether images in a layer are dimmed (colors shifted toward white)
		when rendering. If a parent layer specifies dimming, images in sublayers
		are dimmed regardless of the sublayer setting.
			@param layer The layer.
			@param dimmed True to dim images, false to turn dimming off.
		*/
	AIAPI AIErr (*SetLayerDimPlacedImages) ( AILayerHandle layer, AIBoolean dimmed );


	// version 5, new for AI 6.0.1

	/** Reports whether a layer is selected.
			@param layer The layer.
			@param selected [out] A buffer in which to return true if
				this layer is selected; false if it is not.
			@note This function is provided for backward
				compatibility with Illustrator 6.0.
	*/
	AIAPI AIErr (*GetLayerSelected) ( AILayerHandle layer, AIBoolean *selected );

	/** Sets whether a layer is selected.
			@param layer The layer.
			@param selected True to select this layer, false
				to deselect it.
			@note This function is provided for backward
				compatibility with Illustrator 6.0.
		*/
	AIAPI AIErr (*SetLayerSelected) ( AILayerHandle layer, AIBoolean selected );


	// version 6, new for AI 7.0

	/** Retrieves a layer by title.	The layer can be top-level or a sublayer.
			@param layer [out] A buffer in which to return the layer.
			@param title The title string.
	 	*/
	AIAPI AIErr (*GetLayerByTitle) ( AILayerHandle *layer, const ai::UnicodeString& title );

	/** Reports whether a layer contains objects other than sublayers.
			@param layer The layer.
			@param hasArt [out] A buffer in which to return true if
				this layer contains art objects; false if it does not.
		*/
	AIAPI AIErr (*LayerHasArt) ( AILayerHandle layer, AIBoolean *hasArt );

	/** Reports whether a layer contains any selected artwork.
			@param layer The layer.
			@param hasSel [out] A buffer in which to return true if
				this layer contains selected art; false if it does not.
		*/
	AIAPI AIErr (*LayerHasSelectedArt) ( AILayerHandle layer, AIBoolean *hasSel );

	/** Deselects all objects on a layer.
			@param layer The layer.
		*/
	AIAPI AIErr (*DeselectArtOnLayer) ( AILayerHandle layer );

	/** Selects all objects on a layer that can be selected.
			@param layer The layer.
		*/
	AIAPI AIErr (*SelectArtOnLayer) ( AILayerHandle layer );

	// version 7, new for AI 8.0

	/** Reports whether a layer is a template layer. All sublayers of a
		template layer are also template layers.
			@param layer The layer.
			@param isTemplate [out] A buffer in which to return true if
				this layer is a template layer; false if it is not.
		*/
	AIAPI AIErr (*GetLayerIsTemplate) ( AILayerHandle layer, AIBoolean *isTemplate );

	/** Sets whether a layer is a template layer. All sublayers of a
		template layer are also template layers.
			@param layer The layer.
			@param isTemplate True to make this a template layer, false to
				not make it a template layer. */
	AIAPI AIErr (*SetLayerIsTemplate) ( AILayerHandle layer, AIBoolean isTemplate );

	/** Retrieves the layer above a given layer in the stacking order.
		Does not descend into sublayers.
			@param next The given layer.
			@param prev [out] A buffer in which to return the previous layer, or
				\c NULL if there are no more layers.
			@return The error \c #kNotImplementedErr if \c next is in a sublayer.
			@see \c #GetFirstLayer(), \c #GetNextLayer()
	*/
	AIAPI AIErr (*GetPrevLayer) ( AILayerHandle next, AILayerHandle *prev );

	/** Retrieves the dimming factor used for drawing images when a layer is set to be
		dimmed.
			@param layer The layer.
			@param percent [out] A buffer in which to return the dimming factor,
				in the range [0..100] where 0 in no dimming, and 100 is maximum
				dimming.
		*/
	AIAPI AIErr (*GetLayerDimmedPercent) ( AILayerHandle layer, ai::int32 *percent );

	/** Sets the dimming factor used for drawing images when a layer is set to be
		dimmed.
			@param layer The layer.
			@param percent The dimming factor, in the range [0..100]
				where 0 in no dimming, and 100 is maximum dimming. */
	AIAPI AIErr (*SetLayerDimmedPercent) ( AILayerHandle layer, ai::int32 percent );

	// version 8, new for AI 9.0

	/** Retrieves the first child sublayer of a layer.
			@param layer The layer.
			@param child [out] A buffer in which to return the sublayer,
				or NULL if there are no sublayers.
		*/
	AIAPI AIErr (*GetLayerFirstChild) ( const AILayerHandle layer, AILayerHandle *child );

	/** Retrieves the parent of a layer.
			@param layer The layer.
			@param parent [out] A buffer in which to return the parent,
				or NULL if there is no parent.
		*/
	AIAPI AIErr (*GetLayerParent) ( const AILayerHandle layer, AILayerHandle *parent );

	/** Inserts a new layer into a document at a paint-order position relative
		to an art object.
			  @param art The art object.
			  @param paintOrder The paint order, relative to the \c art object,
		 		 an \c #AITypes::AIPaintOrder value. See \c #AIArtSuite::NewArt().
				 The position must be appropriate for adding a layer; that is,
				 at the top level or such that the resulting parent is a layer.
			  @param newLayer [out] A buffer in which to return the new layer.
			  @see \c #InsertLayer()
		 */
	AIAPI AIErr (*InsertLayerAtArt) ( const AIArtHandle art, AIPaintOrder paintOrder,
		AILayerHandle *newLayer );

	/** Converts a sublayer of this layer to a simple group. You must ensure that
		the sublayer has no child layers that would be orphaned by
		removing the layer information.
			@param layer The layer object for the sublayer,
				or \c NULL if you pass the group object.
			@param group The art group object associated with the sublayer,
				or \c NULL if you pass the layer object.
		*/
	AIAPI AIErr (*ChangeLayerToGroup) ( const AILayerHandle layer, const AIArtHandle group );

	/** Retrieves the next layer in preorder traversal, which finds descendents first,
		then siblings. Use this to iterate through layers and their sublayers.
			@param prev The previous layer.
			@param next [out] A buffer in which to return the next layer, or
					\c NULL if there are no more layers.
			@see \c #GetFirstLayer(), \c #GetNextNonChildPreorderLayer()
		*/
	AIAPI AIErr (*GetNextPreorderLayer) ( AILayerHandle prev, AILayerHandle *next );

	/** Retrieves the next layer in preorder traversal, skipping descendents and returning
		only sibling layers. Use this to iterate through layers and their parent layers.
			@param prev The previous layer.
			@param next [out] A buffer in which to return the next layer, or
					\c NULL if there are no more layers.
			@see \c #GetFirstLayer(), \c #GetNextPreorderLayer()
		*/
	AIAPI AIErr (*GetNextNonChildPreorderLayer) ( AILayerHandle prev, AILayerHandle *next );

} AILayerSuite;


#include "AIHeaderEnd.h"

#endif
