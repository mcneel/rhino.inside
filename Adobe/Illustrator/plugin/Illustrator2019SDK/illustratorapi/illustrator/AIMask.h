#ifndef __AIMask__
#define __AIMask__

/*
 *        Name:	AIMask.h
 *   $Revision: 3 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Mask Suite.
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

#ifndef __AIArtStyle__
#include "AIArtStyle.h"
#endif

#ifndef __AIDictionary__
#include "AIDictionary.h"
#endif

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAIBlendStyleSuite				"AI Blend Style Suite"
#define kAIBlendStyleSuiteVersion5		AIAPI_VERSION(5)
#define kAIBlendStyleSuiteVersion		kAIBlendStyleSuiteVersion5
#define kAIBlendStyleVersion			kAIBlendStyleSuiteVersion

#define kAIMaskSuite					"AI Mask Suite"
#define kAIMaskSuiteVersion5			AIAPI_VERSION(5)
#define kAIMaskSuiteVersion				kAIMaskSuiteVersion5
#define kAIMaskVersion					kAIMaskSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/


/** An opaque reference to a mask. There is a one-to-one correspondence between
	objects and masks. */
typedef struct _AIMask*					AIMaskRef;


/** The various blending modes that can be used to composite an object. These
	modes correspond to the ones in Photoshop. See #AIBlendingModeValues. */
typedef ai::int32 AIBlendingMode;
/** Values for \c #AIBlendingMode */
enum AIBlendingModeValues {
	kAINormalBlendingMode			= 0,
	kAIMultiplyBlendingMode			= 1,
	kAIScreenBlendingMode			= 2,
	kAIOverlayBlendingMode			= 3,
	kAISoftLightBlendingMode		= 4,
	kAIHardLightBlendingMode		= 5,
	kAIColorDodgeBlendingMode		= 6,
	kAIColorBurnBlendingMode		= 7,
	kAIDarkenBlendingMode			= 8,
	kAILightenBlendingMode			= 9,
	kAIDifferenceBlendingMode		= 10,
	kAIExclusionBlendingMode		= 11,
	kAIHueBlendingMode				= 12,
	kAISaturationBlendingMode		= 13,
	kAIColorBlendingMode			= 14,
	kAILuminosityBlendingMode		= 15,
	kAINumBlendingModes				= 16
};


/** Knockout tri-state */
typedef enum AIKnockout
{
	kAIKnockoutUnknown = -1,
	/** No knockout */
	kAIKnockoutOff = 0,
	/** Knockout */
	kAIKnockoutOn,
	/** Use parent's knockout value */
	kAIKnockoutInherit
} AIKnockout;


/* Dictionary keys for compositing attributes */

/** @ingroup DictKeys
	Dictionary key for mode of a blend style, contains \c #AIBlendingModeValues.
	See \c #AIBlendStyleSuite::GetArtAttrs(). */
#define kAIBlendModeKey					"Mode"
/** @ingroup DictKeys
	Dictionary key for opacity of a blend style, contains an \c #AIReal value
	in the range [0..1].
	See \c #AIBlendStyleSuite::GetArtAttrs() and \c #AIMaskSuite. */
#define kAIBlendOpacityKey				"Opacity"
/** @ingroup DictKeys
	Dictionary key for isolation state of a blend style, contains a boolean value.
	See \c #AIBlendStyleSuite::GetArtAttrs(). */
#define kAIBlendIsolatedKey				"Isolated"
/** @ingroup DictKeys
	Dictionary key for knockout state of a blend style, contains an \c #AIKnockout value.
	See \c #AIBlendStyleSuite::GetArtAttrs().*/
#define kAIBlendKnockoutKey				"Knockout"
/** @ingroup DictKeys
	Dictionary key for alpha state of a blend style, contains a boolean value.
	See \c #AIBlendStyleSuite::GetArtAttrs().  */
#define kAIBlendAlphaIsShapeKey			"AlphaIsShape"


/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite provides function for working with \e blend \e styles.
	When an art object overlaps other art, it is composited with what
	was drawn before it, using a blend style that is a part of the
	object's art style. Fills and strokes can have their own
	compositing attributes.

	See the PDF language specification for details of the transparency
	modes used by Illustrator.

	@see \c #AIMaskSuite

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIBlendStyleSuite and \c #kAIBlendStyleVersion.
	*/
typedef struct {

	/** Retrieves the current blending mode of an art object, which
		applies to the object as a whole.
		(Note that this function returns a constant value, not an error code.)
			@param	art The art object.
			@return The mode constant, one of the \c #AIBlendingModeValues.
		*/
	AIAPI AIBlendingMode (*GetBlendingMode) (AIArtHandle art);

	/** Sets the blending mode of an art object, which
		applies to the object as a whole.
			@param	art The art object.
			@param mode The new mode constant, one of the \c #AIBlendingModeValues.
		*/
	AIAPI AIErr (*SetBlendingMode) (AIArtHandle art, AIBlendingMode mode);

	/** Retrieves the current opacity value applied by the style to an art object.
		(Note that this function returns a numeric value, not an error code.)
			@param	art The art object.
			@return The opacity value, in the range [0..1] where 0 is completely
				transparent and 1 is completely opaque.
	 	*/
	AIAPI AIReal (*GetOpacity) (AIArtHandle art);

	/** Sets the opacity value applied by the style to an art object.
			@param	art The art object.
			@param opacity The new opacity value, in the range [0..1] where 0 is completely
				transparent and 1 is completely opaque.
		*/
	AIAPI AIErr (*SetOpacity) (AIArtHandle art, AIReal opacity);

	/** Reports whether any blending modes used in the rendering of the object
		contents are isolated from what has already been drawn. This does
		not affect the blending mode used for compositing the entire object
		into its backdrop.
		 (Note that this function returns a boolean value, not an error code.)
			@param	art The art object.
			@return	True if isolation is on.
		*/
	AIAPI AIBoolean (*GetIsolated) (AIArtHandle art);

	/** Sets whether any blending modes used in the rendering of the object
		contents are isolated from what has already been drawn. This does
		not affect the blending mode used for compositing the entire object
		into its backdrop.
			@param	art The art object.
			@param isolated True to turn isolation on, false to turn it off.
		*/
	AIAPI AIErr (*SetIsolated) (AIArtHandle art, AIBoolean isolated);

	/** Retrieves the current knockout state of an art object. If the state is
		\c #kAIKnockoutInherit, the on/off state is inherited from the object’s parent,
		and you can use \c #GetInheritedKnockout() to retrieve it.
		(Note that this function returns a constant value, not an error code.)
			@param	art The art object.
			@return The knockout state constant, one of the \c #AIKnockout values.
		*/
	AIAPI AIKnockout (*GetKnockout) (AIArtHandle art);

	/** Retrieves the inherited knockout state (on or off) of an art object.
		(Note that this function returns a constant value, not an error code.)
			@param	art The art object.
			@return The knockout state constant, \c #kAIKnockoutOff or \c #kAIKnockoutOn.
		*/
	AIAPI AIKnockout (*GetInheritedKnockout) (AIArtHandle art);

	/** Sets the knockout state of an art object. If the state is
		\c #kAIKnockoutInherit, the on/off state is inherited from
		the object’s parent.
			@param	art The art object.
			@param knockout The new knockout state: on, off, or inherited,
		*/
	AIAPI AIErr (*SetKnockout) (AIArtHandle art, AIKnockout knockout);

	/** Reports whether opacity and mask define the knockout shape for
		an art object.
		(Note that this function returns a boolean value, not an error code.)
			@param	art The art object.
			@return	True if opacity and mask define the knockout shape.
		*/
	AIAPI AIBoolean (*GetAlphaIsShape) (AIArtHandle art);

	/** Sets whether opacity and mask define the knockout shape for
		an art object.
			@param	art The art object.
			@param alphaIsShape True if opacity and mask define the knockout shape,
				false if they do not.
		*/
	AIAPI AIErr (*SetAlphaIsShape) (AIArtHandle art, AIBoolean alphaIsShape);

	/** Copies the compositing attributes that are applied globally by the
		style of one art object to another art object.
			@param source The source art object.
			@param destination The destination art object.
		*/
	AIAPI AIErr (*Copy) (const AIArtHandle source, AIArtHandle destination);

	/** Retrieves the dictionary that contains compositing attributes that
		are applied globally by the style of an art object.
		This convenience function has the same effect as retrieving an
		art object’s art style and getting attributes individually
		using \c #AIBlendStyleSuite::GetStyleAttrs().

		The keys for the compositing attributes are:
		\verbatim
		#kAIBlendModeKey
		#kAIBlendOpacityKey
		#kAIBlendIsolatedKey
		#kAIBlendKnockoutKey
		#kAIBlendAlphaIsShapeKey
		\endverbatim
			@param art The art object.
			@param attrs [in, out] The dictionary in which to return the attributes.
			@see \c #AIDictionarySuite
	*/
	AIAPI AIErr (*GetArtAttrs) (AIArtHandle art, AIDictionaryRef attrs);

	/** Sets the compositing attributes applied globally to an art object,
		using a dictionary. This convenience function has the same
		effect as retrieving an art object’s art style and setting
		attributes individually using \c #AIBlendStyleSuite::SetStyleAttrs().
			@param art The art object.
			@param attrs The dictionary containing the attributes.
				You can specify a subset of the keys in order to modify a
				subset of the compositing attributes.
			@see \c #GetArtAttrs() for keys.
		*/
	AIAPI AIErr (*SetArtAttrs) (AIArtHandle art, AIDictionaryRef attrs);

	/** Retrieves the dictionary that contains globally-applied compositing attributes
		from an art style.
			@param style The art style object.
			@param attrs [in, out] The dictionary in which to return the attributes.
			@see \c #GetArtAttrs() for keys, \c #AIDictionarySuite
		*/
	AIAPI AIErr (*GetStyleAttrs) (AIArtStyleHandle style, AIDictionaryRef attrs);

	/** Modifies the compositing attributes of an art style that are applied globally
		to an art object, using a dictionary, and creates a new style with
		the modifications.
			@param style The source art style object. This object is not modified.
			@param attrs The dictionary containing the attributes.
				You can specify a subset of the keys in order to modify a
				subset of the compositing attributes.
			@param newStyle [out] A buffer in which to return a new style object
				containing the modifications.
 		*/
	AIAPI AIErr (*SetStyleAttrs) (AIArtStyleHandle style, AIDictionaryRef attrs,
								  AIArtStyleHandle* newStyle);

	/** Retrieves the common compositing attributes for the current selection in the
		current document. Retrieves only the common attributes; for
		example, if two objects are selected with different opacities, the
		opacity entry is not present in the returned dictionary.
			@param styleAttrs [in, out] The dictionary in which to return the common attributes
				applied to objects as a whole. Can be \c NULL if not needed.
			@param fillAttrs [in, out] The dictionary in which to return the common attributes
				applied to the focal fills.	Can be \c NULL if not needed.
			@param strokeAttrs [in, out] The dictionary in which to return the common attributes
				applied to the focal strokes. Can be \c NULL if not needed.
			@see \c #GetArtAttrs() for keys, \c #AIDictionarySuite
		*/
	AIAPI AIErr (*GetCurrentTransparency) (AIDictionaryRef styleAttrs,
										   AIDictionaryRef fillAttrs,
										   AIDictionaryRef strokeAttrs);

	/** Sets compositing attributes for the current selection in the
		current document.The dictionaries can specify a subset of
		keys in order to modify a subset of the compositing attributes.
			@param styleAttrs The dictionary containing the attributes
				applied to objects as a whole. Can be \c NULL if not needed.
			@param fillAttrs The dictionary containing attributes
				applied to the focal fills.	Can be \c NULL if not needed.
			@param strokeAttrs The dictionary containing attributes
				applied to the focal strokes. Can be \c NULL if not needed.
			@see \c #GetArtAttrs() for keys, \c #AIDictionarySuite
		 */
	AIAPI AIErr (*SetCurrentTransparency) (AIDictionaryRef styleAttrs,
										   AIDictionaryRef fillAttrs,
										   AIDictionaryRef strokeAttrs);

	/** Retrieves dictionary containing the compositing attributes for
		the focal fill of an art style.
			@param artStyle The art style object.
			@param attrs [in, out] The dictionary in which to return the attributes.
			@see \c #GetArtAttrs() for keys, \c #AIDictionarySuite
		*/
	AIAPI AIErr (*GetFocalFillAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs);

	/** Retrieves dictionary containing the compositing attributes for
		the focal stroke of an art style.
			@param artStyle The art style object.
			@param attrs [in, out] The dictionary in which to return the attributes.
			@see \c #GetArtAttrs() for keys, \c #AIDictionarySuite
		*/
	AIAPI AIErr (*GetFocalStrokeAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs);

	/** Modifies the compositing attributes for the focal fill of an art style
		using a dictionary, and creates a new style with the modifications.
			@param artStyle The source art style object. Not modified.
			@param attrs The dictionary containing the attributes.
			@param newStyle [out] A buffer in which to return a new style object
				containing the modifications.
			@see \c #GetArtAttrs() for keys, \c #AIDictionarySuite
		 */
	AIAPI AIErr (*SetFocalFillAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs,
											 AIArtStyleHandle* newStyle);

	/** Modifies the compositing attributes for the focal stroke of an art style
		using a dictionary, and creates a new style with the modifications.
			@param artStyle The source art style object. Not modified.
			@param attrs The dictionary containing the attributes.
			@param newStyle [out] A buffer in which to return a new style object
				containing the modifications.
			@see \c #GetArtAttrs() for keys, \c #AIDictionarySuite
		*/
	AIAPI AIErr (*SetFocalStrokeAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs,
											   AIArtStyleHandle* newStyle );

	/** Reports whether an art object contains any artwork with
		non-normal blending that is not isolated at the level of the object.
		(Note that this function returns a boolean value, not an error code.)
			@param	art The art object.
			@return	True if the object does contain artwork with non-isolated blending.
		*/
	AIAPI AIBoolean (*ContainsNonIsolatedBlending) (AIArtHandle object);

	// New to Illustrator 11:

	/** Reports the isolation state of the page group, which contains all the layers in the
		current document.
		(Note that this function returns a boolean value, not an error code.)
			@return	True if the contents of the page is to be drawn in an isolated
				transparency group.
		*/
	AIAPI AIBoolean (*GetDocumentIsolated) (void);

	/** Sets the isolation state of the page group, which contains all the layers in the
		current document.
			 @param isolated True to turn isolation on, false to turn it off.
		*/
	AIAPI AIErr (*SetDocumentIsolated) (AIBoolean isolated);

	/** Reports the knockout state of the page group, which contains all the layers in the
		current document.
		(Note that this function returns a boolean value, not an error code.)
			@return	True if knockout is on for the page group, false if it is off.
		*/
	AIAPI AIBoolean (*GetDocumentKnockout) (void);

	/** Sets the knockout state of the page group, which contains all the layers in the
		current document.
			 @param knockout True to turn knockout on, false to turn it off.
		*/
	AIAPI AIErr (*SetDocumentKnockout) (AIBoolean knockout);

} AIBlendStyleSuite;


/** @ingroup Suites
	This suite provides functions to access the opacity mask that
	can be associated with an art object. Opacity values from the
	mask are combined with the object's own opacity when compositing it.

	Mask objects are reference counted.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMaskSuite and \c #kAIMaskVersion.
	*/
typedef struct {

	/** Increments the reference count for a mask.
		(Note that this function returns an integer value, not an error code.)
			@param mask The mask object.
			@return The new reference count for the mask.
	*/
	AIAPI ai::int32 (*AddRef) (AIMaskRef mask);
	/** Decrements the reference count for a mask, and, when
		the count reaches 0, frees the associated memory.
		(Note that this function returns an integer value, not an error code.)
			@param mask The mask object.
  			@return The new reference count for the mask.
		*/
	AIAPI ai::int32 (*Release) (AIMaskRef mask);

	/** Retrieves the mask associated with an art object, if any.
			@param object The art object.
			@param mask [out] A buffer in which to return the mask object.
		*/
	AIAPI AIErr (*GetMask) (AIArtHandle object, AIMaskRef* mask);

	/** Creates a mask for an art object if it does not already have one.
		The art of the newly created mask is an empty group object.
		Retrieve the new mask with \c #GetMask().
			@param object The art object.
		*/
	AIAPI AIErr (*CreateMask) (AIArtHandle object);

	/** Deletes the mask association between an art object and its mask,
		and decrements the reference count of the mask. If the reference
		count is then 0, also deletes the mask object.
			@param object The art object.
		*/
	AIAPI AIErr (*DeleteMask) (AIArtHandle object);

	/** Reports the link state of a mask. When a mask is linked, certain actions
		on the associated art object, such as rotation, are automatically applied
		to the mask as well.
		(Note that this function returns a boolean value, not an error code.)
			@param mask The mask object.
			@return True if the mask is linked.
		*/
	AIAPI AIBoolean (*GetLinked) (AIMaskRef mask);

	/** Sets the link state of a mask. When a mask is linked, certain actions
		on the associated art object, such as rotation, are automatically applied
		to the mask as well.
			@param mask The mask object.
			@param linked True to turn linking on, false to turn it off.
		*/
	AIAPI AIErr (*SetLinked) (AIMaskRef mask, AIBoolean linked);

	/** Reports the disabled state of a mask. When a mask is disabled,
		it is ignored when rendering the associated art object.
		(Note that this function returns a boolean value, not an error code.)
			@param mask The mask object.
			@return True if the mask is disabled.
		*/
	AIAPI AIBoolean (*GetDisabled) (AIMaskRef mask);

	/** Sets the disabled state of a mask. When a mask is disabled,
		it is ignored when rendering the associated art object.
			@param mask The mask object.
			@param disabled True to disable the mask, false to enable it.
		*/
	AIAPI AIErr (*SetDisabled) (AIMaskRef mask, AIBoolean disabled);

	/** Reports the inverted state of a mask. When a mask is inverted,
		the opacity is inverted before being applied to the associated art.
		(Note that this function returns a boolean value, not an error code.)
			@param mask The mask object.
			@return True if the mask is inverted.
		*/
	AIAPI AIBoolean (*GetInverted) (AIMaskRef mask);

	/** Sets the inverted state of a mask. When a mask is inverted,
		the opacity is inverted before being applied to the associated art.
			@param mask The mask object.
			@param inverted True to invert the mask, false to turn inversion off.
		*/
	AIAPI AIErr (*SetInverted) (AIMaskRef mask, AIBoolean inverted);

	/** Copies a mask and its link status from one art object to another.
			@param source The source art object.
			@param destination The destination art object.
		*/
	AIAPI AIErr (*Copy) (const AIArtHandle source, AIArtHandle destination);

	/** Retrieves the art object that comprises an opacity mask, if any.
		(Note that this function returns an object value, not an error code.)
			@param mask The mask object.
			@return The art object, or \c NULL if there is no mask art.
		*/
	AIAPI AIArtHandle (*GetArt) (AIMaskRef mask);

	/** Reports whether the art object that comprises an opacity mask is
		currently being edited.
		(Note that this function returns a boolean value, not an error code.)
			@param mask The mask object.
			@return True if the mask art is being edited.
		*/
	AIAPI AIBoolean (*IsEditingArt) (AIMaskRef mask);

	/** Turns editing on or off for the art object associated with a mask.
		Editing mask art causes a new layer to be created
		at the top of the current layer list containing the mask art. When
		editing is terminated the layer is deleted.
			@param mask The mask object.
			@param isedit True to turn editing on, false to turn it off.
			@see \c #AILayerListSuite
		*/
	AIAPI AIErr (*SetEditingArt) (AIMaskRef mask, AIBoolean isedit);

	/** Retrieves the masked art object associated with a group art object
		that is the mask art for another art object.
			@param mask The group art object.
			@param [out] A buffer in which to return the masked art object,
				or \c  NULL if the input art object is not used as a mask.
		 */
	AIAPI AIErr (*GetMaskedArt) (AIArtHandle mask, AIArtHandle* masked);

	/** Reports the clipping state of a mask.
		(Note that this function returns a boolean value, not an error code.)
			@param mask The mask object.
			@return True if the art associated with the mask is clipped.
	 */
	AIAPI AIBoolean (*GetClipping) (AIMaskRef mask);

	/** Sets the clipping state of a mask. When clipping is true, the
		opacity value outside the mask art is 0%, thus clipping out
		everything outside the mask art.When clipping is false, the
		value outside is 100%, thus revealing everything outside the
		boundary of the mask art.
			@param mask The mask object.
			@param clipping True to turn clipping on, false to turn it off.
		*/
	AIAPI AIErr (*SetClipping) (AIMaskRef mask, AIBoolean clipping);

} AIMaskSuite;


#include "AIHeaderEnd.h"


#endif
