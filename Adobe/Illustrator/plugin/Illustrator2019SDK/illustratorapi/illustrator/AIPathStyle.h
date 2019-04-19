#ifndef __AIPathStyle__
#define __AIPathStyle__

/*
 *        Name:	AIPathStyle.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Path Style Suite.
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIDocument__
#include "AIDocument.h"
#endif

#ifndef __AIRealMath__
#include "AIRealMath.h"
#endif

#ifndef __AIEntry__
#include "AIEntry.h"
#endif

#include "IAIFilePath.hpp"

#include "AIHeaderBegin.h"

/** @file AIPathStyle.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIPathStyleSuite			"AI Path Style Suite"
#define kAIPathStyleSuiteVersion14	AIAPI_VERSION(14)
#define kAIPathStyleSuiteVersion	kAIPathStyleSuiteVersion14
#define kAIPathStyleVersion			kAIPathStyleSuiteVersion

/** Maximum number of dash components for a stroke */
#define kMaxDashComponents		6

/** Types of line caps for strokes. */
enum AILineCap {
	/** Butt line caps */
	kAIButtCap = 0,
	/** Round line caps */
	kAIRoundCap,
	/** Projecting line caps */
	kAIProjectingCap
};

/** Types of line joins for strokes. */
enum AILineJoin {
	/** Miter line joins */
	kAIMiterJoin = 0,
	/** Round line joins */
	kAIRoundJoin,
	/** Bevel line joins */
	kAIBevelJoin
};

/** @ingroup Notifiers
	See \c #AIPathStyleSuite */
#define kAIBeginImportStylesNotifier	"AI Begin Import Styles Notifier"
/** @ingroup Notifiers
	See \c #AIPathStyleSuite */
#define kAIEndImportStylesNotifier		"AI End Import Styles Notifier"


/** @ingroup Errors
	See \c #AIPathStyleSuite */
#define kTooManyDashComponents		'DASH'
/** @ingroup Errors
	See \c #AIPathStyleSuite */
#define kCantImportStyles			'!Imp'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Describes how to fill a path.
	A \c #AIPathStyle::fill value.
*/
struct AIFillStyle {
	/** Fill color */
	AIColor color;
	/** When true, print any art beneath this, then print the fill of this object over it.
		When false, knock out art beneath this art at print time */
	AIBoolean overprint;
	void Init()
	{
		overprint = false;
		color.kind = kNoneColor;
	}
};

/** The fields of an \c #AIFillStyle that are specified by a partial
	style. An \c #AIPathStyleMap::fill value
	*/
struct AIFillStyleMap {
	AIColorMap color;
	AIBoolean overprint;
	void Init()
	{
		overprint = false;
		color.kind = false;
	}
};

/** Describes a dash pattern for stroking a path.
	An \c #AIStrokeStyle::dash value.
 	@see PostScript documentation.
	*/
struct AIDashStyle {
	/** The number of valid values in the dash array, 0 if solid */
	ai::int16 length;
	/** Dash offset */
	AIFloat offset;
	/** Dash array */
	AIFloat array[kMaxDashComponents];
	void Init()
	{
		length = 0;
		offset = kAIRealZero;
	}
};

/** The fields of an \c #AIDashStyle that are specified by a partial
	style. An \c #AIStrokeStyleMap::dash value.
	*/
struct AIDashStyleMap {
	AIBoolean length;
	AIBoolean offset;
	AIBoolean array[kMaxDashComponents];
	void Init()
	{
		length = false;
		offset = false;
	}
};

/** Describes how to stroke a path.
	An \c #AIPathStyle::stroke value.
*/
struct AIStrokeStyle {
	/** Stroke color */
	AIColor color;
	/** Overprint - not meaningful if the color is a pattern */
	AIBoolean overprint;
	/** Line width in points */
	AIReal width;
	/** Stroke dash */
	struct AIDashStyle dash;
	/** Line cap */
	enum AILineCap cap;
	/** Line join */
	enum AILineJoin join;
	/** Line miter limit */
	AIReal miterLimit;

    void Init()
	{
		overprint = false;
		width = kAIRealZero;
		dash.Init();
		color.kind = kNoneColor;
		cap = kAIButtCap;
		join = kAIMiterJoin;
		miterLimit = kAIRealZero;
	}

};

/** The fields of an \c #AIStrokeStyle that are specified by a partial
	style. An \c #AIPathStyleMap::stroke value. */
struct AIStrokeStyleMap {
	AIColorMap color;
	AIBoolean overprint;
	AIBoolean width;
	struct AIDashStyleMap dash;
	AIBoolean cap;
	AIBoolean join;
	AIBoolean miterLimit;
	void Init()
	{
		overprint = false;
		width = false;
		dash.Init();
		cap = false;
		join = false;
		miterLimit = false;
		color.kind = false;
	}
};

/** Describes how to paint the fill and stroke of a path.
		\li A full style completely specifies the paint information.
 		\li A \e partial style can specify a subset
			of the painting information. It can be used to represent
			the common paint attributes of a selection, for instance,
			or to modify a subset of attributes without affecting the others.
			In this case the path style is paired with a style \e map,
			an \c #AIPathStyleMap specifying the subset of attributes that have
			valid values.

	Be careful not to pass partial styles to functions that require
	full styles; unspecified fields can contain invalid values.
 */
struct AIPathStyle {
	/** Whether or not to fill the path. */
	AIBoolean fillPaint;
	/** Whether or not to stroke the path */
	AIBoolean strokePaint;
	/** Fill style, if fillPaint is true */
	struct AIFillStyle fill;
	/** Stroke style, if strokePaint is true */
	struct AIStrokeStyle stroke;
	/** @deprecated. Use \c #AIArtSuite::SetArtUserAttr().
        Whether or not to use this as a clipping path */
	AIBoolean clip;
	/** @deprecated. Use \c #AIArtSuite::SetArtUserAttr().
        Whether or not to lock the clipping path */
	AIBoolean lockClip;
	/** When true, use the even-odd rule to determine path insideness */
	AIBoolean evenodd;
	/** Path's resolution */
	AIReal resolution;
	void Init()
	{
		fillPaint = false;
		strokePaint = false;
		fill.Init();
		stroke.Init();
		clip = false;
		lockClip = false;
		evenodd = false;
		resolution = 800.0;
	}
};

/** A true value indicates a field of a partial style that contains
	a valid value in an accompanying \c #AIPathStyle.  */
struct AIPathStyleMap {
	AIBoolean fillPaint;
	AIBoolean strokePaint;
	struct AIFillStyleMap fill;
	struct AIStrokeStyleMap stroke;
	AIBoolean clip;
	AIBoolean lockClip;
	AIBoolean evenodd;
	AIBoolean resolution;
	void Init()
	{
		fillPaint = false;
		strokePaint = false;
		fill.Init();
		stroke.Init();
		clip = false;
		lockClip = false;
		evenodd = false;
		resolution = false;
	}
};


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions to access or set stroke and fill paint style information
	for art objects.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPathStyleSuite and \c #kAIPathStyleVersion.
*/
struct AIPathStyleSuite {

	/** Retrieves the path style used to fill and/or stroke a path art object.
			@param path The art object.
			@param style [out] A buffer in which to return the style.
            @param outHasAdvFill : Set to 'true' if there is advance fill applied on path e.g. smooth style shading.
			@return The error \c #kBadParameterErr if the art object is not an
				allowed type.
		*/
	AIAPI AIErr (*GetPathStyle) ( AIArtHandle path, AIPathStyle *style, AIBoolean *outHasAdvFill );

	/** Sets the path style used to fill and/or stroke a path art object, if
		the object is one of these types:
		<br> \c #kPathArt
		<br> \c #kCompoundPathArt
		<br> \c #kRasterArt
		<br> \c #kMeshArt
		<br> \c #kPlacedArt
		<br> \c #kTextFrameArt

		For group types, (\c #kGroupArt, \c #kPluginArt, \c #kSymbolArt),
		modifies the existing fill or stroke. If there is no existing fill or
		stroke value, has no effect. Use the \c #AIArtStyleSuite to add a new
		fill or stroke to a group object.

			@param path The art object.
			@param style The new style.
			@return The error \c #kBadParameterErr if the art object is not an
				allowed type (\c #kForeignArt, \c #kLegacyTextArt, \c #kUnknownArt).
		*/
	AIAPI AIErr (*SetPathStyle) ( AIArtHandle path, const AIPathStyle *style );


	/** Retrieves the common attributes of the current selected objects
			@param style [out] A buffer in which to return the partial style containing
				the common attributes.
			@param stylemap [out] A buffer in which to return the map indicating which
				fields of the partial style contain valid values.
            @param outHasAdvFill : Set to 'true' if there is advance fill applied on path e.g. smooth style shading.
			@param advStrokeParams [out, optional] A pointer to a dictionary ref which may be created
				and populated with common advanced stroke parameters.
		*/
	AIAPI AIErr (*GetCurrentPathStyle) ( AIPathStyle *style, AIPathStyleMap *stylemap, AIDictionaryRef *advStrokeParams, AIBoolean *outHasAdvFill);

	/** Applies a path style to any currently selected and paint-targeted objects.
		For this function to apply, a targeted object must be a path or compound path,
		or have a style that already contains a fill or stroke.
		If a targeted object has an active style, the new style is merged
		into the focal fill and stroke filters. Any effects and non-focal fills
		and strokes remain unmodified.
			@param style The new partial style.
			@param stylemap The map indicating which fields of the partial style
				contain valid values.
			@param advStrokeParams [optional] A dictionary ref containing advanced stroke
				parameters, may be null.
			@note To completely replace active styles, use
				\c #SetCurrentPathStyleForceSimple()
		*/
	AIAPI AIErr (*SetCurrentPathStyle) ( AIPathStyle *style, AIPathStyleMap *stylemap, ConstAIDictionaryRef advStrokeParams );

	/** Imports styles from a file, and creates a new document containing the styles.
		Use the \c #AIArtStyleSuite and \c #AISwatchListSuite to access the information.
		For	instance, use \c #AISwatchListSuite::GetSwatchList to import colors from
		the document.
			@param source The file that contains the styles.
			@param newdoc [out] A buffer in which to return the new document.
	  */
	AIAPI AIErr (*ImportStyles) ( const ai::FilePath &source, AIDocumentHandle *newdoc );

	/** Imports mixed-colorspace styles from a file, and creates a new document
		containing the styles. Rarely needed; use only to allow a mixed colorspace
		in a swatch library. Mixed colorspaces are not allowed in artwork.
		(\c #ImportStyles() always converts to a single colorspace.)
			@param source The file that contains the styles.
			@param newdoc [out] A buffer in which to return the new document.
		*/
	AIAPI AIErr (*ImportStylesMixedColorSpace) ( const ai::FilePath &source, AIDocumentHandle *newdoc );

	/** Applies a color to the stroke or fill of an art object. Generally
		does what you would want to do when applying a color. It sets the
		gradient vector to the default, handles compound paths, and so on.
		For example, if you have an object that is stroked with a dashed line
		and you pass in a new color with \c onStroke true, the old
		dash pattern is retained. If the object did not have a stroke before, the
		function looks for one in the current paint style. If the current paint style
		does not have a stroke, it uses a sensible default.
			@param art The art object.
			@param color The new color.
			@param onStroke True to apply the color only to strokes, false to apply only to fill.
			@note The function enumerates container objects. Do not call
				on both a container and its children.
		*/
	AIAPI AIErr (*SetObjectAIColor) ( AIArtHandle art, const AIColor *color, AIBoolean onStroke );

	/** Reports whether and how a path style makes use of a specific color in its
		fill or stroke.
			@param pathStyle The full or partial path style.
			@param psMap The map indicating which fields of the partial style
				contain valid values, or \c NULL for a full style.
			@param color The color.
			@param matchTint When false, the tint percentage for spot and
				global process colors is not considered.
			@param lookForIndirectUsage When true, and if the path style is a pattern,
				searches the pattern definition for the color.
			@param usage [out] A buffer in which to return the result.
		*/
	AIAPI AIErr (*PathStyleUsesAIColor) ( const AIPathStyle *pathStyle,
											const AIPathStyleMap *psMap,
											const AIColor *color,
											AIBoolean matchTint,
											AIBoolean lookForIndirectUsage,
											AIColorUsedHow *usage );

	/**	Applies a color to a path style in a typical way, as for the Swatch palette.
			\li If the new color is a gradient or pattern, ignores its vector and
				transform. If the path style is of the same type, retains its vector
				and transform. Otherwise, uses default values.
			\li If the new color is a spot color, uses the tint.
			\li Uses reasonable defaults when changing from one kind of color
				to another (such as solid to pattern or gradient) or when
				assigning color to a fill or stroke that was previously unpainted.

			@param pathStyle The full or partial path style. Modified in place.
			@param psMap The map indicating which fields of the partial style
				contain valid values, or \c NULL for a full style.
			@param newColor The new color.
			@param matchColor Optional. If supplied, \c onStroke is ignored and the
				new color is applied to the stroke or fill that matches this color.
				Matching is exact, including color space. Never assigns paint to an
				unpainted stroke or fill unless the value is \c #kNoneColor.
			@param onStroke	If \c matchColor is \c NULL, then when true, applies the
				new color to stroke, and when false, applies it to fill. To apply
				to both, you must call the function twice.
			@param useOldTint When true, and the new color and match color are
				both custom colors, uses the tint from the match color. When false,
				uses the tint from the new color.
			@param destination The art object that uses the style, Used if a bounding
				box is needed to calculate a gradient vector. If it is a compound path,
				calculates bounds from the entire compound group.
			@param whatChanged [out] Optional. A buffer in which to return a structure
				indicating what part of the path style was changed.
		*/
	AIAPI AIErr (*ApplyAIColorToPathStyle) ( AIPathStyle *pathStyle,
											AIPathStyleMap	*psMap,	// can be null
											const AIColor	*newColor,
											const AIColor	*matchColor,
											AIBoolean		onStroke,
											AIBoolean		useOldTint,
											AIArtHandle		destination,
											AIColorUsedHow	*whatChanged );

	/** Reports whether and how an art object uses a color.
			@param art The art object. Can be of any type.
			@param targetColor The color.
			@param matchTint When false, the tint percentage for spot and
				global process colors is not considered.
			@param lookForIndirectUsage When true, checks for a match
				inside patterns, gradients, and graph designs. When false,
				still checks inside the graph style change records of graph
				objects, but not in patterns, gradients, or graph designs.
			@param usage [out] A buffer in which to return the result.
	*/
	AIAPI AIErr (*ObjectUsesAIColor) ( AIArtHandle art,
										const AIColor *targetColor,
										AIBoolean matchTint,
										AIBoolean lookForIndirectUsage,
										AIColorUsedHow *usage );

	/** Replaces one color with another in an art object.

		For direct usage of the old color (that is, a stroke or fill, including inside graph
		path style change records), calls \c #SetObjectAIColor() to set the new color.
		Does not replace indirectly used colors--that is, those inside patterns, gradients,
		or graph designs used by the art object.

		You can replace pattern or gradient colors by defining a new
		pattern or gradient, then calling this function for the pattern or gradient
		object itself, with the new replacement object.
			@param art The art object, or \c NULL to replace the color in
				all art in the current document. Can be any type except \c #kPlacedArt,
				including those that are reported as \c #kMysteryPathArt
				(paths inside text paths and graphs), and those that are
				reported as \c #kUnknownArt, such as graphs and layer masks.
			@param oldColor The color to replace.
			@param newColor The new color.
			@param useOldTint When true, and both colors are custom colors, uses
				the tint from the old color. When false, uses the tint from the
				new color.
			@param madeReplacement [out] Optional. A buffer in which to return
				true if a replacement was made.
		*/
	AIAPI AIErr (*ReplaceObjectAIColor) ( AIArtHandle art,
											const AIColor *oldColor, const AIColor *newColor,
											AIBoolean useOldTint,
											AIBoolean *madeReplacement /* can be NULL */ );

	/** Retrieves the default path style that tools should use when creating new objects other
		than text objects.
			@param style [out] A buffer in which to return the path style.
		*/
	AIAPI AIErr (*GetInitialPathStyle) ( AIPathStyle *style );

	/** Sets the default path style that tools should use when creating new objects other
		than text objects.
			@param style The new path style.
		*/
	AIAPI AIErr (*SetInitialPathStyle) ( const AIPathStyle *style );

	/** Retrieves the default path style that tools should use when creating text objects.
			@param style [out] A buffer in which to return the path style.
		*/
	AIAPI AIErr (*GetInitialTextStyle) ( AIPathStyle *style );

	/** Sets the default path style that tools should use when creating text objects.
			@param style The new path style.
		*/
	AIAPI AIErr (*SetInitialTextStyle) ( const AIPathStyle *style );

	/** Makes a color appropriate for the artwork in the current document.
		For example, if it uses a pattern that is not available, replaces it
		with an equivalent pattern that is available.
			@param color The color (typically from clipboard artwork).
	  */
	AIAPI AIErr (*RetargetForCurrentDoc) ( AIColor *color) ;

	/** Applies a path style to any currently selected and paint-targeted objects.
		For this function to apply, a targeted object must be a path or compound path,
		or have a style that already contains a fill or stroke.
		When a selected object has an active style, merges the input style values
		only with the paint attributes, and gives the object that simple style.
		Compare \c #SetCurrentPathStyle().
			@param style The new partial style, or \c NULL to replace all
				selected active styles with the simple style corresponding to their focal
				fill and/or stroke filters.
 			@param stylemap The map indicating which fields of the partial style
				contain valid values, or \c NULL if style is not supplied.
	*/
	AIAPI AIErr (*SetCurrentPathStyleForceSimple) ( AIPathStyle *style, AIPathStyleMap* stylemap );

	/** Applies a path style to a path object. When the path has an active style,
		merges the input style values only with the paint attributes, and gives
		the object that simple style. Compare \c #SetPathStyle().
			@param path	The path object.
			@param style The new style, or \c NULL to replace the
				active style with the simple style corresponding to the focal
				fill and/or stroke filters.
		*/
	AIAPI AIErr (*SetPathStyleForceSimple) ( AIArtHandle path, const AIPathStyle *style );

	/** Interpolates a new style between two path styles.
			@param style0 The first path style object.
			@param style1 The second path style object.
			@param styleOut [out] A buffer in which to return the new path style.
			@param percent The distance from the source styles. 0 to return the first
				style, 1 to return the second style, or an interpolation point
				between the two.
			@see\c #AIPathInterpolateSuite. */
	AIAPI AIErr (*InterpolatePathStyle) ( const AIPathStyle *style0, const AIPathStyle *style1,
		AIPathStyle *styleOut, AIReal percent);

	/** Interpolates a color between two colors.
			@param color0 The first color.
			@param color1 The second color.
			@param colorOut [out] A buffer in which to return the new color.
				If the colors are of incompatible types, such as two patterns,
				returns the first color.
			@see \c #AIPathInterpolateSuite
		*/
	AIAPI AIErr (*InterpolateAIColor) ( const AIColor *color0, const AIColor *color1, AIColor *colorOut,
										AIReal fraction );

	// New for AI12:

	/** Sets the synchronization state for the initial path style. When synchronization
		is on (which it usually is) Illustrator synchronizes the initial path style
		with the current path style whenever the selection changes, and	when calls
		are made to \c #GetCurrentPathStyle(), \c #SetCurrentPathStyle(),
		\c #GetInitialPathStyle() or \c #SetInitialPathStyle().
		The Swatches palette, Color palette, and Toolbox all show the
		current path style.

		When synchronization is off, the initial path style and the current path style
		become independent. In this mode, getting or setting the current path style does not
		affect the initial path style, and getting or setting the initial path style does not affect
		the current path style or the current selection. The palettes and Toolbox show
		the initial path style rather than the current path style.
			@param syncInitialPathStyle \li True to turn synchronization on, false to
				turn it off.
			@note You might want to maintain a tool-specific style that is not
				modified when the selection changes. This allows the user to have a selection,
				choose a specific tool and color, and not have the color apply to the current
				selection. This is used by the paintbucket tool, for example.
				To get this behavior, turn synchronization off, then get and set the
				initial style (rather than the current style) while the tool is selected.
		*/
	AIAPI AIErr (*SetSyncInitialPathStyle) ( AIBoolean syncInitialPathStyle );

	/** Reports the synchronization state for the initial path style.
		(Note that this function returns a boolean value, not an error code.)
			@return True if synchronization is on.
			@see \c #SetSyncInitialPathStyle()
		*/
	AIAPI AIBoolean (*GetSyncInitialPathStyle)();

	// New for AI 13:

	/** Examines or modifies colors in an object by calling a developer-defined callback function.
			@param art The art object, or \c NULL to iterate through the entire art tree of
				the current document.
			@param adjustColorCallback The developer-defined callback procedure.
			@param clientData Optional developer-defined data to pass through to the callback.
			@param controlFlags Options for how colors are enumerated to the callback,
				a logical OR of \c #VisitAIColorFlagValues.
			@param madeReplacement [out] Optional, a buffer in which to return true if any
				colors were replaced.
			@note You can use this to simply visit all the colors used in a document or in the selection,
				for static purposes such as building up a collection of colors or compiling statistics on them.
				You could iterate twice, once to collect statistics and again to make changes, for example
				to average colors or to posterize art based on a histogram of the colors that it uses.
		*/
	AIAPI AIErr (*AdjustObjectAIColors) ( AIArtHandle art,
				AIAdjustColorFunc adjustColorCallback, void *clientData,
				VisitAIColorFlags controlFlags,
				AIBoolean *madeReplacement );

	/** Retrieves the path style used to fill and/or stroke a path art object and
		the visibility of fill and stroke.
			@param path The art object.
			@param style [out] A buffer in which to return the style.
			@param fillVisible [out] A buffer in which to return true if fill is visible.
			@param strokeVisible [out] A buffer in which to return true if stroke is visible.
			@return The error \c #kBadParameterErr if the art object is not an
				allowed type.
		*/
	AIAPI AIErr (*GetPathStyleEx) ( AIArtHandle path, AIPathStyle *style, AIBoolean* fillVisible, AIBoolean* strokeVisible );


	/** Sets the path style used to fill and/or stroke a path art object
		and the visibility of fill and stroke, if the object is one of these types:
		<br> \c #kPathArt
		<br> \c #kCompoundPathArt
		<br> \c #kRasterArt
		<br> \c #kMeshArt
		<br> \c #kPlacedArt
		<br> \c #kTextFrameArt

		For group types, (\c #kGroupArt, \c #kPluginArt, \c #kSymbolArt),
		modifies the existing fill or stroke. If there is no existing fill or
		stroke value, has no effect. Use the \c #AIArtStyleSuite to add a new
		fill or stroke to a group object.

			@param path The art object.
			@param style The new style.
			@return The error \c #kBadParameterErr if the art object is not an
				allowed type (\c #kForeignArt, \c #kLegacyTextArt, \c #kUnknownArt).
		*/
	AIAPI AIErr (*SetPathStyleEx) ( AIArtHandle path, const AIPathStyle *style, AIBoolean fillVisible, AIBoolean strokeVisible );


	/** Retrieves the common attributes of the current selected objects
			@param style [out] A buffer in which to return the partial style containing
				the common attributes.
			@param stylemap [out] A buffer in which to return the map indicating which
				fields of the partial style contain valid values.
		*/
	AIAPI AIErr (*GetCurrentPathStyleEx) ( AIPathStyle *style, AIPathStyleMap* stylemap, AIBoolean* fillVisible, AIBoolean* strokeVisible );

	/** Applies a path style to any currently selected and paint-targeted objects.
		For this function to apply, a targeted object must be a path or compound path,
		or have a style that already contains a fill or stroke.
		If a targeted object has an active style, the new style is merged
		into the focal fill and stroke filters. Any effects and non-focal fills
		and strokes remain unmodified.
			@param style The new partial style.
			@param stylemap The map indicating which fields of the partial style
				contain valid values.
			@param fillVisible True if fill should be visible.
			@param strokeVisible True if stroke should be visible.
			@note To completely replace active styles, use
				\c #SetCurrentPathStyleForceSimple()
		*/
	AIAPI AIErr (*SetCurrentPathStyleEx) ( AIPathStyle *style, AIPathStyleMap* stylemap, AIBoolean fillVisible, AIBoolean strokeVisible );

};


#include "AIHeaderEnd.h"

#endif
