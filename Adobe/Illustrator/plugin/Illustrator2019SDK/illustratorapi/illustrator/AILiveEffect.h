#ifndef __AILiveEffect__
#define __AILiveEffect__

/*
 *        Name:	AILiveEffect.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Effect Suite.
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

#ifndef __AIDict__
#include "AIDictionary.h"
#endif

#ifndef __AIFilter__
#include "AIFilter.h"
#endif

#ifndef __AIMenu__
#include "AIMenu.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AIXMLElement__
#include "AIXMLElement.h"
#endif



#include "AIHeaderBegin.h"

/** @file AILiveEffect.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAILiveEffectSuite					"AI Live Effect Suite"
#define kAILiveEffectSuiteVersion			AIAPI_VERSION(6)
#define kAILiveEffectVersion				kAILiveEffectSuiteVersion

/** @ingroup Callers
	The Live Effect caller. See \c #AILiveEffectSuite. */
#define kCallerAILiveEffect						"AI Live Effect"


/** If your effect gets new options in a later version that are not supported by earlier versions,
	such that the objects carrying the new options should be expanded (output as the styled art only)
	upon legacy save, while objects with options supported by the older versions should NOT be expanded,
	then set the value of this key in the effect's parameter dictionary to the app version which first
	supports the new option values (as an integer, e.g., CS 5 = 15).
	See also c\ #AILiveEffectSuite::SetLiveEffectAppVersion for situations where the version compatibility
	is not dependent upon the effect options. */
#define kAILiveEffectParamsExpandBeforeKey	"Adobe Effect Expand Before Version"

#define kAILiveEffectParamsWriteAlternateVersionMajorKey "Adobe Effect Expand Write Alternate Version Major"
#define kAILiveEffectParamsWriteAlternateVersionMinorKey "Adobe Effect Expand Write Alternate Version Minor"


// These are the effect messages.

/** @ingroup Selectors
	Sends an \c #AILiveEffectEditParamMessage.
	 */
#define kSelectorAIEditLiveEffectParameters		"AI Live Effect Edit Parameters"
/** @ingroup Selectors
	Sends an \c #AILiveEffectGoMessage.
	*/
#define kSelectorAIGoLiveEffect					"AI Live Effect Go Live"
/** @ingroup Selectors
	Sends an \c #AILiveEffectInterpParamMessage. */
#define kSelectorAILiveEffectInterpolate		"AI Live Effect Interpolate Parameters"
/** @ingroup Selectors
	Sends an \c #AILiveEffectInputTypeMessage. */
#define kSelectorAILiveEffectInputType			"AI Live Effect Input Type"
/** @ingroup Selectors
 	Sends an \c #AILiveEffectConvertColorMessage. */
#define kSelectorAILiveEffectConverColorSpace	"AI Live Effect Convert Color Space"
/** @ingroup Selectors
	Sends an \c #AILiveEffectScaleParamMessage. */
#define kSelectorAILiveEffectScaleParameters	"AI Live Effect Scale Parameters"
/** @ingroup Selectors
	Sends an \c #AILiveEffectHandleMergeMessage. */
#define kSelectorAILiveEffectHandleMerge		"AI Live Effect Handle Merge"
/** @ingroup Selectors
	Sends an \c #AILiveEffectGetSVGFilterMessage. */
#define kSelectorAILiveEffectGetSVGFilter		"AI Live Effect Get SVG Filter"
/** @ingroup Selectors
 	Sends an \c #AILiveEffectAdjustColorsMessage. */
#define kSelectorAILiveEffectAdjustColors		"AI Live Effect Adjust Colors"
/** @ingroup Selectors
	Sends an \c #AILiveEffectIsCompatibleMessage */
#define kSelectorAILiveEffectIsCompatible		"AI Live Effect Is Compatible"


/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A string entry that is displayed by the palette in preference
	to the filter name, if it is set.  For example, Punk & Bloat might set it to "Punk" or
	"Bloat" to tell which filter is used.  For a stroke or fill filter, it is displayed
	next to the color swatch.  */
#define kDisplayStringKey "DisplayString"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A string entry that gives extra information for the palette
	to display for this filter, for example as a tool tip.  Can
	mention the most important parameters. */
#define kExtraStringKey "ExtraString"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	The fill color to use, a \c #FillStyleType. Set
	for a fill filter when the filter is installed. */
#define kFillStyleKey "FillStyle"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A \c #FillStyleType for fill filters, but with the object's style matrix
	multiplied in for gradient fills.  Effects with a fill style parameter
	should usually first look for this key in the instance info, and if it is present,
	use its value.  If it is not present, it should look for kFillStyleKey. */
#define kTransformedFillStyleKey "TransformedFillStyle"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A \c #MatrixType value for fill filters. If the object's fill style matrix
	is not identity, this will be set in the instance info.  The matrix will
	also be factored into the transformed fill style, but it contains information
	that is not available in the gradient fields, such as whether there is
	a reflection. */
#define kFillStyleMatrixKey "FillStyleMatrix"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A \c #BooleanType value for fill filters. */
#define kEvenOddKey "UseEvenOdd"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A \c #StrokeStyleType for stroke filters. */
#define kStrokeStyleKey "StrokeStyle"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A \c #StrokeStyleType for stroke filters, but with the object's style matrix
	multiplied in for gradient strokes.  Effects with a stroke style parameter
	should usually first look for this key in the instance info, and if it is present,
	use its value.  If it is not present, it should look for kStrokeStyleKey. */
#define kTransformedStrokeStyleKey "TransformedStrokeStyle"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
	A \c #MatrixType value for stroke filters. If the object's stroke style matrix
	is not identity, this will be set in the instance info.  The matrix will
	also be factored into the transformed stroke style, but it contains information
	that is not available in the gradient fields, such as whether there is
	a reflection. */
#define kStrokeStyleMatrixKey "StrokeStyleMatrix"

/** @ingroup DictKeys
	Dictionary key for a Live Effect parameter. See \c #AILiveEffectSuite.
 	An \c #AIReal used to scale parameters while processing
	the Go message. You should scale parameters locally; do not modify
	the values in the actual parameter dictionary. */
#define kScaleFactorKey "ScaleFactorString"


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a Live Effect. It is never dereferenced.*/
typedef struct _t_AILiveEffectOpaque* AILiveEffectHandle;
 /** Opaque reference to a Live Effect parameter context.*/
typedef struct _t_AILiveEffectParamContext* AILiveEffectParamContext;


/** Defines the menu item for a Live Effect. */
struct AddLiveEffectMenuData {
	/** The submenu in which the menu item should appear,
		or \c NULL to place at the top level of the Effects menu. */
	char *category;
	/** The localizable display string for the menu item */
	char *title;
	/** Not used. Pass 0. */
	ai::int32 options;
};


/** The parameters for a Live Effect, stored in a dictionary. */
typedef AIDictionaryRef AILiveEffectParameters;
typedef ConstAIDictionaryRef ConstAILiveEffectParameters;


/** Bit flags for Live Effect style properties, which specify
	how the filter is applied and what features it supports.
	An effect must be registered with exactly one of the
	first four values, which denote the filter type. The last
	three values can be ORed together with the filter type.
	Pass to \c #AILiveEffectSuite::AddLiveEffect()
	in \c #AILiveEffectData::styleFilterFlags.  */
enum AIStyleFilterFlags {
	/** Clears all flags. */
	kNoFlags 				= 0,
	/** Applied by default before the object is painted with fill or stroke. */
	kPreEffectFilter		= 0x1,
	/**  Applied by default after the object is painted with fill or stroke. */
	kPostEffectFilter		= 0x2,
	/** Replaces the default stroke behavior.
		Brushes are an example of an effect of this type. */
	kStrokeFilter			= 0x3,
	/** Replaces the default fill behavior. */
	kFillFilter				= 0x4,
	/** A mask to OR with the filter-style value to retrieve specific bit flags.
		Do not use with \c #AILiveEffectSuite::AddLiveEffect(). */
	kFilterTypeMask			= 0x0ffff,
	/** Internal. Do not use. */
	kSpecialGroupPreFilter	= 1 << 16,
	/** Parameters can be scaled. */
	kHasScalableParams		= 1 << 17,
	/** Supports automatic rasterization. */
	kUsesAutoRasterize		= 1 << 18,
	/** Supports the generation of an SVG filter. */
	kCanGenerateSVGFilter	= 1 << 19,
	/** Has parameters that can be modified by a \c #kSelectorAILiveEffectAdjustColors message. */
	kHandlesAdjustColorsMsg	= 1 << 20,
	/** Handles \c #kSelectorAILiveEffectIsCompatible messages. If this flag is not set the message will not be sent. */
	kHandlesIsCompatibleMsg = 1 << 21
};


/** The kinds of objects in input art that an effect can operate on.
	If input art contains objects the effect does not handle, Illustrator looks for a
	conversion filter to convert the input art to a type that is handled. If no
	such filter is available, the input art is passed unchanged. The effect should
	pass through unchanged any art that it cannot handle, */
enum AIStyleFilterPreferredInputArtType {
	/** The \c #kSelectorAILiveEffectInputType message is sent
		to the plug-in to determine the input type */
	kInputArtDynamic			= 0,
	/** Handles groups. */
	kGroupInputArt 				= 1 << ((ai::int32) kGroupArt - 1),
	/** Handles paths. */
	kPathInputArt 				= 1 << ((ai::int32) kPathArt - 1),
	/** Handles compound paths. */
	kCompoundPathInputArt 		= 1 << ((ai::int32) kCompoundPathArt - 1),

	/** Obsolete */
	kTextInputArtUnsupported	= 1 << ((ai::int32) kTextArtUnsupported - 1),
	/** Obsolete */
	kTextPathInputArtUnsupported= 1 << ((ai::int32) kTextPathArtUnsupported - 1),
	/** Obsolete */
	kTextRunInputArtUnsupported	= 1 << ((ai::int32) kTextRunArtUnsupported - 1),
	/** Handles placed objects. */
	kPlacedInputArt 			= 1 << ((ai::int32) kPlacedArt - 1),
	/** Handles mystery paths. */
	kMysteryPathInputArt 		= 1 << ((ai::int32) kMysteryPathArt - 1),
	/** Handles raster art. */
	kRasterInputArt 			= 1 << ((ai::int32) kRasterArt - 1),

	/** Handles plug-in groups. If not set, the effect receives the result group
		instead of the plug-in group itself. */
	kPluginInputArt				= 1 << ((ai::int32) kPluginArt - 1),
	/** Handles meshes. */
	kMeshInputArt 				= 1 << ((ai::int32) kMeshArt - 1),
	/** Handles text frames. */
	kTextFrameInputArt 			= 1 << ((ai::int32) kTextFrameArt - 1),
	/** Handles symbols. */
	kSymbolInputArt 			= 1 << ((ai::int32) kSymbolArt - 1),
	/** Handles foreign objects. */
	kForeignInputArt			= 1 << ((ai::int32) kForeignArt - 1),
	/** Handles legacy text. */
	kLegacyTextInputArt			= 1 << ((ai::int32) kLegacyTextArt - 1),
	/** Handles charts. */
	kChartInputArt				= 1 << ((ai::int32) kChartArt - 1),

	/** Handles any input art. */
	kAnyInputArt 				= 0xFFFF,
	/** Handles any input art other than plug-in groups, which
		are replaced by their result art. */
	kAnyInputArtButPluginArt	= kAnyInputArt & ~kPluginInputArt,

	// Special values that don't correspond to regular art types should be in the high half word

	/** Not implemented. */
	// When set, convert strokes to outlines before sending to effect
	kOutlinedStrokeInputArt		= 0x10000,
	/** Does \e not handle clipping paths or clipping text.
		Not needed if paths are not handled. */

	/* (Because it would destroy them by rasterizing, for example,
		or by splitting a single path into multiple non-intersecting paths,
		or by turning it into a plug-in group, like the brush filter).
		This flag is on for "Not OK" instead of on for "OK" because destroying clipping paths is
		an exceptional condition and we don't want to require normal filters to explicitly say they're OK. */
	kNoClipMasksInputArt		= 0x20000

};


/** Ways that a Live Effect can be merged with the existing styles of selected objects.  */
enum AILiveEffectMergeAction {
	/** Append this effect to the current style. */
	kAppendLiveEffectToStyle,
	/** Replace the current fill style with this effect. */
	kReplaceFillWithLiveEffect,
	/** Replace the current stroke style with this effect. */
	kReplaceStrokeWithLiveEffect,
	/** Bit flag can be ORed with replacement styles to send
		a \c #kSelectorAILiveEffectHandleMerge message to handle
		the parameters of the merge. Not used with \c #kAppendLiveEffectToStyle */
	kSendHandleMergeMessage = 0x10000
};


/** Information supplied when registering a Live Effect
	with \c #AILiveEffectSuite::AddLiveEffect(). */
struct AILiveEffectData {
	/** The plug-in that is registering the effect and that
		receives effect messages. */
	SPPluginRef self;
	/** A unique identifying name of the effect, not localized. */
	const char* name;
	/** A localized display title for the effect. */
	char *title;
	/** Major version number of this plug-in. */
	ai::int32 majorVersion;
	/** Minor version number of this plug-in. */
	ai::int32 minorVersion;
	/** The type of art this effect can operation on,
		a \c #AIStyleFilterPreferredInputArtType value.*/
	ai::int32 prefersAsInput;
	/** The type and supported features of this effect,
		a logical OR of \c #AIStyleFilterFlags. */
	ai::int32 styleFilterFlags;
};



//
// The contents of Live Effect messages.
//

/** Sent when the user chooses your registered effect from the Effects menu,
	after the Edit parameters message that allows you to collect parameter
	values from the user. Also sent when the effect needs to be run in response
	to user edits to the objects.
	The plug-in should respond by running its effect on the supplied art object
	using the supplied parameters. */
struct AILiveEffectGoMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** The current parameters block, as returned from the Edit parameters message. */
	AILiveEffectParameters parameters;
	/** [in, out] A set of parameters that the plug-in may have stored
		from an earlier invocation on this object.*/
	AILiveEffectParameters instanceInfo;
	/** [in, out] The art object to be edited with this effect.
		You must not modify any ancestor objects, nor modify the document artwork tree.
		The plug-in is responsible for proper deletion of objects in source
		art that it removes. You can set this to \c NULL if the effect
		does not return any art; in this case, Illustrator disposes of
		the input art. */
	AIArtHandle	art;
};

/** Sent when the user chooses a your registered effect from the Effects menu,
	or when the user later edits the effect using the appearance palette.

	The plug-in can ignore the selector if it does not require user input;
	otherwise, it should collect parameter values from the user,
	typically using a modal dialog. If previews are enabled, it can then
	update the artwork using \c #AILiveEffectSuite::UpdateParameters()
	to preview the results.
	The plug-in must call \c #AILiveEffectSuite::UpdateParameters() after
	it finishes collecting user input and updating values.
	*/
struct AILiveEffectEditParamMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** [in, out] A set of parameters that the plug-in may have stored
		from an earlier invocation. Modify values if desired. */
	AILiveEffectParameters parameters;
	/** The parameter context, passed to various functions. */
	AILiveEffectParamContext context;
	/** True if preview is enabled. If it is, the plug-in can call
		\c #AILiveEffectSuite::UpdateParameters after modifying the parameters,
		to update the associated artwork. The plug-in receives a Go message
		after updating parameters.*/
	AIBoolean allowPreview;

	/** True if this is the first time this effect is being applied by this plug-in,
	false if the effect is being modified (from the Appearance panel, for example).
	**/
	AIBoolean isNewInstance;
};

/** Sent when the user chooses to interpolate a new point into the parameter
	set for an effect. This happens when Illustrator attempts to blend two objects
	that have Live Effects applied to them; for example, if you select two objects
	with an effect and choose Object>Blend>Make. The intermediate objects between
	the two blended objects need to have effects applied to them as well, which
	need to have values that are the interpolated results between the two blended objects.

	Pass the parameter blocks to \c #AILiveEffectSuite::InterpolateEffectParameters().
*/
struct AILiveEffectInterpParamMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** A parameter block indicating a starting point. */
	AILiveEffectParameters startParams;
	/** A parameter block indicating an ending point.*/
	AILiveEffectParameters endParams;
	/** [out] A parameter block to contain the interpolated point. */
	AILiveEffectParameters outParams;
	/** A percentage of the distance between \c startParams
	and \c endParams, expressed as a value in the range [0..1].
	The new value is interpolated at this point. */
	AIReal percent;

};

/** Sent when  the user selects an effect whose input type is
	\c #kInputArtDynamic. If the type computation depends on input art,
	the plug-in can examine the passed art object to decide on the type.
*/
struct AILiveEffectInputTypeMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** The current parameter block for the effect. */
	AILiveEffectParameters parameters;
	/** The art object whose type is to be computed. */
	AIArtHandle inputArt;
	/** [out] The type of art that can be operated on by this effect
		with this parameter set, an \c #AIStyleFilterPreferredInputArtType value.
		\li If the input art is a type that this effect can filter, set to \c #kAnyInputArt.
		\li Otherwise, set to the type to which the art should be converted. */
	ai::int32 typeMask;
};

/** Sent with a request to convert any private color data the plug-in
	has stored in a dictionary to a new color space.
	This is only for private color information. Normal fill and stroke color
	information is automatically converted.
*/
struct AILiveEffectConvertColorMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** The current parameter block for the effect. */
	AILiveEffectParameters parameters;
	/** The new color space. */
	AIColorTag newColorSpace;
};

/** Sent with \c #kSelectorAILiveEffectAdjustColors to allow another plug-in that does
	color manipulations to extract and/or modify any private color data that the effect plug-in has
	stored in its parameter dictionary, including colors contained indirectly in art objects, art
	styles or symbol references. This parameter block contains only private color information
	for an effect. Normal fill and stroke colors (that is, those which are stored under
	\c #kFillStyleKey or \c #kStrokeStyleKey) are adjusted without consulting the effect.

	The color-adjustment callback is supplied by a plug-in other than the one that manages the effect.
	The initial request is generally initiated by \c #AIPathStyleSuite::AdjustObjectAIColors(), and
	the effect that receives this message has been encountered while processing that request.


	\li If the parameter dictionary contains private \c #AIColor values, they should be passed
		directly to the color-adjustment callback.

	\li If the parameter dictionary contains art objects that contain meaningful colors, those objects
		should be passed to \c #AIPathStyleSuite::AdjustObjectAIColors(), along with this callback function,
		client data, and control flags.

	\li If the parameter dictionary contains symbol handles or brush pattern handles that contain meaningful
		colors, the symbol patterns or brush patterns should be passed to the pattern-adjustment callback.
		These could be, for example, symbols mapped to surfaces by the 3D effect.
		Other symbols can be ignored; for example, symbols that define 3D bevel shapes.
*/
struct AILiveEffectAdjustColorsMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** The current parameter block for the effect. */
	AILiveEffectParameters parameters;

	/** A callback function to adjust colors, supplied by a plug-in
		other than the one that manages the effect.
		See \c #AIPathStyleSuite::AdjustObjectAIColors(). */
	AIAdjustColorFunc adjustColorCallback;
	/** A callback function to adjust patterns, supplied by a plug-in
		other than the one that manages the effect.	 */
	AIAdjustPatternHandleFunc adjustPatternHandleCallback;
	/** Developer-defined private data to pass to the callback. */
	void *clientData;
	/** A logical OR of bit-flag constants that controls which colors are passed to the callback.*/
	VisitAIColorFlags controlFlags;

	/** [out] Set to true if the handler modified any colors. */
	AIBoolean modifiedSomething;
};


/** Sent with a request to scale effect parameters. */
struct AILiveEffectScaleParamMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** [in, out] The current parameters for the effect.
		Modify values in place. */
	AILiveEffectParameters parameters;
	/** The factor by which to scale the parameters.
		A percentage value where 1 is 100%.  */
	AIReal scaleFactor;
	/** [out] Set to true to indicate that the effect modified the parameters. */
	AIBoolean scaledParams;
};

/** Sent to a plug-in that has initiated a merge with
	\c #AILiveEffectSuite::MergeLiveEffectIntoSelection(),
	so that the plug-in can handle the merge operation.
*/
struct AILiveEffectHandleMergeMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	 /** The effect object currently in use, if any.
	 	\c NULL if replacing a default fill or stroke with an effect. */
	AILiveEffectHandle oldEffect;
	/** [out] Set to true to prevent the merge.  */
	AIBoolean dontMerge;
	/** [out] Set to true to preserve instance information from the existing
		effect, if any. */
	AIBoolean keepInstanceInfo;
	/** [in, out] The parameter block for the existing effect, if any. Modify in place.
		If \c NULL, the Edit message is sent to collect parameters. */
	AILiveEffectParameters parameters;
};

/** Sent with a request to obtain an SVG filter representation of an effect.
	Sent only if the effect plug-in has indicated that it can generate an SVG filter
	to represent itself.

	- In: 'effect' handle returned when the effect was registered.
	- In: 'parameters' handle to live effect parameter set to be used.
	- Out: 'svgFilterUID' return a handle to the UID representing the SVG filter.
*/
struct AILiveEffectGetSVGFilterMessage {
	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** The current parameter block for the effect. */
	AILiveEffectParameters parameters;
	/** [out] Set to the SVG filter object. */
	AISVGFilterHandle svgFilter;
};

/**	Sent when saving a file to allow the live effect to make a detailed check for
	legacy compatibility. This message is only sent if the \c #kHandlesIsCompatibleMsg
	flag is set. If the flag is not set version compatibility is checked against
	values provided by SetLiveEffectAppVersion. The recipient must set the
	'compatible' member below indicate version compatibility.
*/
struct AILiveEffectIsCompatibleMessage {
	explicit AILiveEffectIsCompatibleMessage(
		AILiveEffectHandle thisEffect = 0,
		AIVersion version = kAIVersion1,
		ConstAILiveEffectParameters params = 0,
		AIBoolean compat = false)
	:	effect(thisEffect), appVersion(version), parameters(params), compatible(compat) {}

	/** The message data. */
	SPMessageData d;
	/** The effect object. */
	AILiveEffectHandle effect;
	/** Application version to check compatibility against. */
	AIVersion appVersion;
	/** The current parameter block for the effect. */
	ConstAILiveEffectParameters parameters;

	/** [out] Set to true if compatible with appVersion, false otherwise. */
	AIBoolean compatible;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite allows your plug-in to implement a Live Effect.
	A Live Effect is a filter that can be attached to an art object as part of
	its style. Any time the art object is changed, the filter is automatically
	re-executed. More than one filter can be attached to an object, which allows
	filter \e chains and \e stacks.
		\li A chain is a pipeline where the output of one filter
			becomes the input to the next.
		\li A stack passes the same input art to a set of filters,
			stacking the output of each filter.

	If a document contains a Live Effect that is not available, the document
	can be opened, but art with that effect applied cannot be edited.

	Your Live Effect plug-in must respond to the caller \c #kCallerAILiveEffect
	and the following selectors:
	<br> \c #kSelectorAIEditLiveEffectParameters
	<br> \c #kSelectorAIGoLiveEffect
	<br> \c #kSelectorAILiveEffectInterpolate
	<br> \c #kSelectorAILiveEffectInputType
	<br> \c #kSelectorAILiveEffectConverColorSpace
	<br> \c #kSelectorAILiveEffectScaleParameters
	<br> \c #kSelectorAILiveEffectHandleMerge
	<br> \c #kSelectorAILiveEffectGetSVGFilter

	Most Live Effects have a set of parameters that control their behavior. For
	example, the Roughen effect has parameters for the size and detail of the roughening.
	You can store these in the parameter dictionary that is associated with the effect
	in the style.  Use the \c #AIDictionarySuite to access the contents of the dictionary.
	You can store any information in the parameter dictionary; however the following keys
	are predefined:
	<br> \c #kDisplayStringKey
	<br> \c #kExtraStringKey
	<br> \c #kFillStyleKey
	<br> \c #kEvenOddKey
	<br> \c #kStrokeStyleKey
	<br> \c #kScaleFactorKey
	<br> \c #kAILiveEffectParamsExpandBeforeKey

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAILiveEffectSuite and \c #kAILiveEffectVersion.
*/
struct AILiveEffectSuite {

	/** Registers a Live Effect.
			@param effectInfo A pointer to the structure that defines the effect. You must
				allocate and fill the structure before making the call.
			@param liveEffectHandle [out] A buffer in which to return the effect object.
		*/
	AIAPI AIErr (*AddLiveEffect) ( AILiveEffectData* effectInfo, AILiveEffectHandle *liveEffectHandle );

	/** Adds a menu item for a Live Effect to the Effects menu, using a predefined filter.
			@param liveEffectHandle The effect object.
			@param filterHandle	The filter containing the category, title, and options,
				as returned by \c #AIFilterSuite::AddFilter(). If no filter exists with
				the correct data, use \c #AddLiveEffectMenuItem().
			@param menuItem	[out] A buffer in which to return the new menu item,
				or \c NULL if you do not need the object.
			@param menuGroup [out] A buffer in which to return the menu group to which the item
				was added, or \c NULL if you do not need the object.
		*/
	AIAPI AIErr (*AddLiveEffectFilterItem) ( AILiveEffectHandle liveEffectHandle,
		AIFilterHandle filterHandle, AIMenuItemHandle *menuItem, AIMenuGroup *menuGroup );

	/** Adds a menu item for a Live Effect to the Effects menu.
			@param liveEffectHandle The effect object.
			@param menuName	The unique identifying name for the new menu item.
				Not localized.
			@param menuData	A pointer to the structure that defines the menu.
				You must allocate and fill the structure before making the call.
				If a filter already exists with the correct data, use
				\c #AddLiveEffectFilterItem().
			@param menuItem	[out] A buffer in which to return the new menu item,
				or \c NULL if you do not need the object.
			@param menuGroup [out] A buffer in which to return the menu group to which the item
				was added, or \c NULL if you do not need the object. Returns \c NULL if
				the item was added at the top level of the Effects menu.
		 */
	AIAPI AIErr (*AddLiveEffectMenuItem) ( AILiveEffectHandle liveEffectHandle, const char* menuName,
		 AddLiveEffectMenuData *menuData, AIMenuItemHandle *menuItem, AIMenuGroup *menuGroup );

	/** Not implemented. */
	AIAPI AIErr (*ExecuteLiveEffect) ( AILiveEffectHandle effect,
				AILiveEffectParameters parameters, AIArtHandle art );

	/** @note Internal. Do not use.

	 	Displays a dialog box in which the use can enter parameter values.
			@param context [in, out] The parameter context passed in the
				\c #AILiveEffectEditParamMessage. Modify in place with new values.
			@param enablePreview  True if previews are enabled for this effect.
				When true, pass the returned context to \c #UpdateParameters()
				to update the associated artwork.
		*/
	AIAPI AIErr (*EditParameters) ( AILiveEffectParamContext context, AIBoolean enablePreview );

	/** If previews are enabled for an effect, call this after modifying the
		parameters to update the associated artwork. The plug-in receives
		an \c #AILiveEffectGoMessage after updating parameters.
			@param context The parameter context, as received in
				a \c #AILiveEffectEditParamMessage.
			@see \c #AILiveEffectInterpParamMessage
		*/
	AIAPI AIErr (*UpdateParameters) ( AILiveEffectParamContext context );

	/** Interpolates a point into the current parameter set for an effect.
		Sends the plug-in that owns the effect the \c #AILiveEffectInterpParamMessage.
			@param effect The effect object.
			@param startParams A parameters block for the starting point.
			@param endParams A parameters block for the ending point.
			@param percent A percentage of the distance between
				the start and end parameters, expressed as a value in the range [0..1].
				The new value is interpolated at this point.
			@param resultParams	[out] A parameters block in which the new interpolated point
				is returned.
		*/
	AIAPI AIErr (*InterpolateEffectParameters) ( AILiveEffectHandle effect,
				AILiveEffectParameters startParams, AILiveEffectParameters endParams,
				AIReal percent, AILiveEffectParameters resultParams );

	/** Gets the number of registered effects available to the application.
		Use with \c #GetNthLiveEffect() to iterate through all installed effects.
			@param count [out] A buffer in which to return the number of registered effects.
		*/
	AIAPI AIErr (*CountLiveEffects) ( ai::int32* count );

	/** Retrieves an effect reference by position index.
		Use with \c #CountLiveEffects() to iterate through all installed effects.
			@param n The index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect object.
	*/
	AIAPI AIErr (*GetNthLiveEffect) ( ai::int32 n, AILiveEffectHandle* effect );

	/** Retrieves the unique identifying name of an effect.
		To get the localizable display name, use \c #GetLiveEffectTitle().
			@param effect The effect object.
			@param name [out] A buffer in which to return the name string.
		*/
	AIAPI AIErr (*GetLiveEffectName) ( AILiveEffectHandle effect, const char** name );

	/** Retrieves the localizable display name of an effect.
		To get the unique identifying name, use \c #GetLiveEffectName().
			@param effect The effect object.
			@param name [out] A buffer in which to return the display name string.
		*/
	AIAPI AIErr (*GetLiveEffectTitle) ( AILiveEffectHandle effect, const char** name );

	/** Retrieves the version information for a registered effect.
			@param effect The effect object.
			@param major [out] A buffer in which to return the major version number.
			@param minor [out] A buffer in which to return the minor version number.
		*/
	AIAPI AIErr (*GetLiveEffectVersion) ( AILiveEffectHandle effect, ai::int32* major, ai::int32* minor );

	/** Retrieves the preferred input art types of a registered effect.
			@param effect The effect object.
			@param name [out] A buffer in which to return the input art preferences,
				a logical OR of \c #AIStyleFilterPreferredInputArtType values.
		*/
	AIAPI AIErr (*GetInputPreference) ( AILiveEffectHandle effect, ai::int32* inputPreference );

	/** Retrieves the style flags of a registered effect.
			@param effect The effect object.
			@param name [out] A buffer in which to return the style flags,
				a logical OR of \c #AIStyleFilterFlags values.
		*/
	AIAPI AIErr (*GetStyleFilterFlags) ( AILiveEffectHandle effect, ai::int32* styleFilterFlags );

	/** Merges an effect into the existing style of all selected objects.
			@param effect The effect object.
			@param action The merge method (append, or replace fill and/or stroke),
				and whether to send a \c #kSelectorAILiveEffectHandleMerge message
				to handle the parameters for a replacement method.
		*/
	AIAPI AIErr (*MergeLiveEffectIntoSelection) ( AILiveEffectHandle effect, AILiveEffectMergeAction action );

	/** While handling an \c #AILiveEffectEditParamMessage, retrieves the menu item used
		to invoke the effect.
		(Note that this function returns an object value, not an error code.)
			 @param context The parameter context, as passed in the
			 	\c #AILiveEffectEditParamMessage.
			@return The menu item object, or \c NULL if the message was not invoked by a menu item.
				Returns \c NULL if not called while handling an Edit message.
		 */
	AIAPI AIMenuItemHandle (*GetMenuItem) ( AILiveEffectParamContext context );

	/** Creates a parameter dictionary to be used in constructing a style with the
		\c #AIArtStyleParserSuite. Do not use in any other context.	If you are using
		the \c #AIArtStyleParserSuite to construct a new style from scratch, and you
		need to create a parameter dictionary for an effect, use this function
		to create the parameter dictionary, rather than
		\c #AIDictionarySuite::CreateDictionary(). The dictionary created by this
		function supports Undo operations, which the generic one does not.

		Dictionaries are reference counted; the initial reference count for
		this dictionary is 1. When there are no remaining references,
		free the associated memory using \c #AIDictionarySuite::Release().
			@param params [out] A buffer in which to return the new parameters block.
		*/
	AIAPI AIErr (*CreateLiveEffectParameters) ( AILiveEffectParameters* params );

	/** Retrieves the earliest Illustrator version that an effect supports.
		If you do not use this call, the version defaults to 9 (the first version
		to support Live Effects). If an object with this effect is saved
		to an earlier version, only the styled art is written out. For some effects,
		the earliest version supported for RGB or for CMYK can be different.
			@param effect The effect object.
			@param appVersionRGB [out] A buffer in which to return the earliest version number
				that the effect supports for RGB documents. May be \c NULL.
			@param appVersionCMYK [out] A buffer in which to return the earliest version number
				that the effect supports for CMYK documents. May be \c NULL.
	 */
	AIAPI AIErr (*GetLiveEffectAppVersion) ( AILiveEffectHandle effect, AIVersion* appVersionRGB, AIVersion* appVersionCMYK );

	/** Sets the earliest Illustrator version that an effect supports. If an object with this
		effect is saved to an earlier version, only the styled art is written out.
		For some effects, the earliest version supported for RGB or for CMYK
		can be different. See also \c #kAILiveEffectParamsExpandBeforeKey for situations where
		the compatibility decision is dependent upon the effect options.
			@param effect The effect object.
			@param appVersionRGB The earliest version number that the effect supports
				for RGB documents. Must be 9 or later.
			@param appVersionCMYK The earliest version number that the effect supports
				for CMYK documents. Must be 9 or later.
	 	*/
	AIAPI AIErr (*SetLiveEffectAppVersion) ( AILiveEffectHandle effect, AIVersion appVersionRGB, AIVersion appVersionCMYK );

};


#include "AIHeaderEnd.h"



#endif
