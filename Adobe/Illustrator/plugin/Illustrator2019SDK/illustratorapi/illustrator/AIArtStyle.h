#ifndef __AIArtStyle__
#define __AIArtStyle__

/*
 *        Name:	AIArtStyle.h
 *     Purpose:	Adobe Illustrator Art Style Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2016 Adobe Systems Incorporated.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIDict__
#include "AIDictionary.h"
#endif

#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif

#ifndef __AIPaintStyle__
#include "AIPaintStyle.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIArtStyle.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIArtStyleSuite			"AI Art Style Suite"
#define kAIArtStyleSuiteVersion8	AIAPI_VERSION(8)

/* Latest version */
#define kAIArtStyleSuiteVersion		kAIArtStyleSuiteVersion8
#define kAIArtStyleVersion			kAIArtStyleSuiteVersion

/** Focus types, sent in notify data for \c #kAIArtStyleFocusChangedNotifier.*/
enum AIArtStyleFocusValue {
	/** focus changed to fill or stroke */
	kAIFocusOnFillStroke,
	/** focus changed to object */
	kAIFocusOnObject,
	kAIDummyFocus = 0xFFFFFF
};

/** @ingroup Notifiers
	Sent when the list of styles in the Graphic Styles palette changes
	in any way, such as the order of the list, the names of the styles,
	deletions, additions, and so on. Also sent when such changes are
	undone or redone.
	 */
#define kAINamedStyleListChangedNotifier 	"AI Named Style List Changed Notifier"

/** @ingroup Notifiers
	Sent when the focus changes from the entire object to just the fill or stroke
	of the object, or the reverse. The notify data includes the current focus
	as an \c #AIArtStyleFocusValue. The current focus controls whether transparency
	and Live Effects applied by the user affect the targeted object as a whole
	or just the fill or stroke of the targeted object. */
#define kAIArtStyleFocusChangedNotifier  "AI Art Style Focus Changed Notifier"

/** @ingroup Notifiers
	Sent by the Appearance palette when the user double-clicks a transparency entry.
	Used mainly to bring up the transparency palette. */
#define kAIArtStyleEditTransparencyNotifier  "AI Edit Transparency Notifier"

/** An art style Preference key, a value for a \c suffix parameter in the
	\c #AIPreferenceSuite functions, with a \c prefix value of \c NULL.
	This preference controls whether new objects created
	by the user with the shape, brush, pen, or pencil tools inherit the full
	appearance currently displayed in the Appearance palette, or inherit only
	the current fill and stroke (with no transparency). This is tied to the
	"New Art Has Basic Appearance" option in the Appearance palette flyout menu. */
#define kAINewArtBasicAppearancePref					"AI New Art Basic Appearance"

/** An art style Preference key, a value for a \c suffix parameter in the
	\c #AIPreferenceSuite functions, with a \c prefix value of \c NULL.
	This preference controls whether Illustrator strips
	the fill and stroke colors off for all the text runs (that is, all the characters)
	when a user applies a graphic style to a text object. Controls the
	"Override Character Color" option in the Graphic Styles palette. */
#define kAIContainerOverridesObjectAppearancePref		"AI Container Overrides Object"

/** @ingroup Errors
	Returned if an art style handle passed in does not
	exist in the current document. Can be returned by \c #AIArtStyleSuite::SetArtStyle(),
	\c #AIArtStyleSuite::SetCurrentArtStyle(), \c #AIArtStyleSuite::SetArtStyleName(),
	\c #AIArtStyleSuite::RemoveNamedStyle(), \c #AIArtStyleSuite::RedefineNamedStyle(), and
	\c #AIArtStyleSuite::MoveNamedStyle(). */
#define kStyleNotInCurrentDocument 		'STYD'

/** @ingroup Errors 
	Returned by \c #AIArtStyleSuite::RedefineNamedStyle() if the style passed in
	is not a named style. */
#define kStyleTypeNotCompatible			'STYP'

/** Maximum number of real characters in a style name. */
#define kMaxStyleNameLength				63


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Art style types */
enum AIArtStyleType {
	/** Style contains only one fill and one stroke and can have transparency
	applied only at the object level.*/
	kAIArtStyleSimple = 1,
	/** Style can contain multiple fills and strokes, can have different
	transparency applied to each fill or stroke as well as to the object as a
	whole, and can contain Live Effects.*/
	kAIArtStyleActive
};


/** Return type for \c #AIArtStyleSuite::ExamineStyle().
	See \c #AIArtStyleHasAttrsBits for values.
	*/
typedef ai::uint32 AIArtStyleHasAttrs;
/** Bit flag value for style properties.
A logical OR of these is returned by \c #AIArtStyleSuite::ExamineStyle().
*/
enum AIArtStyleHasAttrsBits {
	/** null value */
	kStyleHasNothing 			= 0,
	/** Style has fill */
	kStyleHasFill				= 0x0001,
	/** Style has stroke */
	kStyleHasStroke				= 0x0002,
	/** Style has patterns */
	kStyleHasPatterns			= 0x0004,
	/** Style has custom colors */
	kStyleHasCustomColors		= 0x0008,
	/** Style has gradients on Fill*/
	kStyleHasFillGradients			= 0x0010,
	/** Style has radial gradients on Fill*/
	kStyleHasRadialGradientsOnFill	= 0x0020,
	/** Style has transparency */
	kStyleHasTransparency		= 0x0040,
	/** Style has brushes */
	kStyleHasBrushes			= 0x0080,

	/** Style has gradients on Stroke*/
	kStyleHasStrokeGradients	= 0x0100,
	/** Style has radial gradients on Stoke*/
	kStyleHasRadialGradientsOnStroke = 0x0200,

	/** Style has effects.
	Transparency does not count as an effect, but brushes do.
	If a style reports that it has no transparency or effects, but the
	type is \c #kAIArtStyleActive, it has either multiple fills or strokes,
	or a stroke that is below the fill.*/
	kStyleHasEffects			= 0x010000,
	/** Style has scalable effects */
	kStyleHasScalableEffects	= 0x020000,

	/**	Pass to \c #AIArtStyleSuite::ExamineStyle() to check for all possible attributes. */
	kStyleCheckForAll			= 0xffffffff
};

/** Gradient information for \c #AIArtStyleSuite::NewStyle() and
	\c #AIArtStyleSuite::GetPaintAttributes().  */
struct AIArtStylePaintData {
	AIArtStylePaintData() { InitToUnknown(); }
	void InitToUnknown() { InitFillToUnknown(); InitStrokeToUnknown(); }
	void InitFillToUnknown();
	void InitStrokeToUnknown();
	void Copy(const AIArtStylePaintData &src) { CopyFill(src); CopyStroke(src); }
	void CopyFill(const AIArtStylePaintData &src);
	void CopyStroke(const AIArtStylePaintData &src);

	/** The gradient origin, relative to the bounding box
	of the object to which the style would be applied. */
	AIRealPoint	fillRelativeGradientOrigin;
	/** The gradient length, in points.*/
	AIReal		fillRelativeGradientLength;
	/** The gradient aspect ratio, for radial gradients */
	AIReal		fillGradientAspectRatio;

	/** The stroke gradient origin, relative to the bounding box
	of the object to which the style would be applied. */
	AIRealPoint	strokeRelativeGradientOrigin;
	/** The stroke gradient length, in points.*/
	AIReal		strokeRelativeGradientLength;
	/** The stroke gradient aspect ratio, for radial gradients */
	AIReal		strokeGradientAspectRatio;
};

inline void AIArtStylePaintData::InitFillToUnknown()
{
	fillRelativeGradientOrigin.h = fillRelativeGradientOrigin.v = kAIRealUnknown;
	fillRelativeGradientLength = kAIRealUnknown;
	fillGradientAspectRatio = kAIRealUnknown;
}

inline void AIArtStylePaintData::InitStrokeToUnknown()
{
	strokeRelativeGradientOrigin.h = strokeRelativeGradientOrigin.v = kAIRealUnknown;
	strokeRelativeGradientLength = kAIRealUnknown;
	strokeGradientAspectRatio = kAIRealUnknown;
}

inline void AIArtStylePaintData::CopyFill(const AIArtStylePaintData &src) 
{
	fillRelativeGradientOrigin = src.fillRelativeGradientOrigin;
	fillRelativeGradientLength = src.fillRelativeGradientLength;
	fillGradientAspectRatio = src.fillGradientAspectRatio;
}

inline void AIArtStylePaintData::CopyStroke(const AIArtStylePaintData &src) 
{
	strokeRelativeGradientOrigin = src.strokeRelativeGradientOrigin;
	strokeRelativeGradientLength = src.strokeRelativeGradientLength;
	strokeGradientAspectRatio = src.strokeGradientAspectRatio;
}



/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The functions in the Art Style suite are used to access and modify
	art styles on artwork in Illustrator documents.

	In AI8, Illustrator introduced the concept of plug-in groups, where the art
	that was actually printed (result art) was separate from the art that the
	user edited (edit art).	This concept was extended in AI9 with the introduction
	of art styles. Now, any art object in the document (including groups and
	text objects) can optionally have "styled art" attached to it. It is this
	"styled art" that gets printed, not the original "source art".

	The art style applied to an art object controls how styled
	art is generated. A plug-in should not directly modify styled art itself,
	which can be regenerated at any time, but should instead work with the art styles.

	Export plug-ins should export the styled art, if any, applied to an object,
	rather than the original source art.

	In the UI, the art style applied to an Illustrator art object is known as the
	object's \e appearance, and is manipulated through the Appearance
	palette. Appearances can also be saved and reused on other objects through the
	Graphic Styles palette.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIArtStyleSuite and \c #kAIArtStyleVersion.

*/
struct AIArtStyleSuite {

	/** Retrieves the styled art for an art object.
		The objects that comprise the styled art cannot themselves have
		styled art.
			@param art The art object.
			@param styleArt [out] A buffer in which to return the styled art object, or
				the original art object if there is no special style applied.
				Returns \c NULL in case of error; for example, if a Live Effect failed
				to execute because of memory constraints.
		 */
	AIAPI AIErr (*GetStyledArt) ( AIArtHandle art, AIArtHandle* styledArt );

	/** Retrieves the art style associated with an art object.
			@param art The art object.
			@param artStyle [out] A buffer in which to return the art style reference, or
				\c NULL if no art style is applied. Null art styles are common
				for objects of type \c kGroupArt, \c kPlacedArt, and \c kPluginArt. */
	AIAPI AIErr (*GetArtStyle) ( AIArtHandle art, AIArtStyleHandle* artStyle );

	/** Retrieves the art style currently displayed in the Appearance palette.
			@param artStyle [out] A buffer in which to return the art style reference.
			@param mixedState [out] A buffer in which to return true if the Appearance
				palette shows "Mixed". In this case, the returned art style
				is a simple style which is an attempt to gather the common attributes
				of the art styles attached to the currently selected objects in the
				current document.
			*/
	AIAPI AIErr (*GetCurrentArtStyle) ( AIArtStyleHandle* artStyle, AIBoolean* mixedState );

	/** Retrieves an art style by its unique name from the current document.
			@param artStyle [out] A buffer in which to return the art style reference.
			@param name The unique name.
			@param searchAllStyles When true, search all styles in the current document,
				including anonymous styles.
				When false, search only named styles (those shown in the Graphic Styles
				palette).
			@see \c #GetArtStyleByNameFromDocument()
		 */
	AIAPI AIErr (*GetArtStyleByName) ( AIArtStyleHandle* artStyle, const ai::UnicodeString& name,
										AIBoolean searchAllStyles );

	/** Gets the number of art styles currently listed in the Graphic Styles palette.
		Use with \c #GetNthNamedArtStyle() to iterate through art styles in the current document.
			@param count [out] A buffer in which to return the number of styles.
			@see \c #CountNamedArtStylesFromDocument()
		*/
	AIAPI AIErr (*CountNamedArtStyles) ( ai::int32* count );

	/** Retrieves a named art style by index. Use with \c #CountNamedArtStyles()
		to iterate through art styles that are currently shown in the Graphic Styles palette.
			@param n The position index, in the range <code> [0..numStyles-1]</code>.
			@param artStyle [out] A buffer in which to return the art style reference.
			@see \c #GetNthNamedArtStyleFromDocument()
		*/
	AIAPI AIErr (*GetNthNamedArtStyle) ( ai::int32 n, AIArtStyleHandle* artStyle );

	/** Applies an art style to an art object.
			@param art The art object.
			@param artStyle The art style, or \c NULL to remove any art style
				currently associated with the art object.
			@return \c #kStyleNotInCurrentDocument if the given art style is not in
				the current document.
		*/
	AIAPI AIErr (*SetArtStyle) ( AIArtHandle art, AIArtStyleHandle artStyle );

	/** Applies an art style to the currently targeted objects on the artboard. This
		is the same clicking the style in the Graphic Styles palette.
			@param artStyle The art style.
			@return \c #kStyleNotInCurrentDocument if the given art style is not in the
				current document.
		*/
	AIAPI AIErr (*SetCurrentArtStyle) ( AIArtStyleHandle artStyle );

	/**	Reports whether an art style is anonymous. Named art styles appear in the
		Graphic Styles palette.
		(Note that the function returns a boolean value, not an error code.)

			@param artStyle The art style object.
			@return True if the style is anonymous; false if it is named.
		*/
	AIAPI AIBoolean (*IsArtStyleAnonymous) ( AIArtStyleHandle artStyle );

	/** Retrieves the unique name of an art style.
			@param artStyle The art style.
			@param name [out] A buffer in which to return the name.
			@param isAnonymous [out] A buffer in  which to return the output as true if the style is anonymous,
				or false if it is named (shown in the Graphic Styles palette).
			*/
	AIAPI AIErr (*GetArtStyleName) ( AIArtStyleHandle artStyle, ai::UnicodeString& name,
									AIBoolean* isAnonymous );

	/** Sets the unique name of a named art style; that is, one that is shown
		in the Graphic Styles palette. Anonymous styles cannot be renamed. You can use
		\c #AddNamedStyle() to convert an anonymous style to a named style.
			@param artStyle The art style. This must be a named art style
			@param name The new name. Style names are limited to 64 characters
				(including the terminating \c NULL character). Empty ("") names are not allowed.
			@return \c #kStyleNotInCurrentDocument if the given art style is not in
				the current document.<br>\c #kNameInUseErr if another art style already exists
				with the given name.
		*/
	AIAPI AIErr (*SetArtStyleName) ( AIArtStyleHandle artStyle, const ai::UnicodeString& name );

	/** Retrieves the paint information for an art style.

			@param artStyle The art style.
			@param aiPathStyle [out] A buffer in which to return an \c #AIPathStyle structure
				that contains information about the fill, stroke and the even-odd fill rule.
			@param paintData [out] A buffer in which to return an \c #AIArtStylePaintData structure
				that contains the gradient vector and origin relative to the object's bounding box.
		 */
	AIAPI AIErr (*GetPaintAttributes) ( AIArtStyleHandle artStyle, AIPathStyle* aiPathStyle,
										AIArtStylePaintData* paintData );

	/** Creates a new art style.
			@param aiPathStyle An \c #AIPathStyle structure that contains information about
				the fill, stroke and the even-odd fill rule.
			@param paintData An \c #AIArtStylePaintData structure that contains the
				gradient vector and origin relative to the object's bounding box. Can be \c NULL.
			@param blendDict A dictionary that contains the transparency information. Can be \c NULL.
			@param newStyle [out] A buffer in which to return the new art style reference.
		*/
	AIAPI AIErr (*NewStyle) ( AIPathStyle* aiPathStyle, AIArtStylePaintData* paintData,
							  AIDictionaryRef blendDict, AIArtStyleHandle* newStyle );

	/** Converts an anonymous style to a named style, which is shown in the Graphic Styles palette.
			@param artStyle The anonymous art style.
			@param name The new name. Style names are limited to 64 characters
				(including the terminating \c NULL character). Empty ("") names are not allowed.
			@param uniquify When true, the function appends a numeric string to make the name unique, if
				it is already in use. When false, if the name is in use, the function fails.
			@param namedStyle [out] A buffer in which to return the new art style reference.
			@return \c #kNameInUseErr if the name is already in use and \c uniquify is false.
		 */
	AIAPI AIErr (*AddNamedStyle) ( AIArtStyleHandle artStyle, const ai::UnicodeString& name, AIBoolean uniquify,
									AIArtStyleHandle* namedStyle );

	/** Converts a named style, which is shown in the Graphic Styles palette, to an anonymous style, which is not.
		Removes the named style from the palette.
			@param namedStyle The named art style.
			@param anonStyle [out] A buffer in which to return the new art style reference.
			@return \c #kStyleNotInCurrentDocument if the art style is not in the current document. */
	AIAPI AIErr (*RemoveNamedStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle* anonStyle );

	/** Creates an anonymous copy of a named art style (one shown in the Graphics Styles palette).
		 The named style remains in the palette.
			@param namedStyle The named style. (If this is an anonymous style, it is copied to \c anonStyle.)
			@param anonStyle [out] A buffer in which to return the new art style reference.
		*/
	AIAPI AIErr (*CreateAnonymousStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle* anonStyle );

	/** Redefines a named art style to have the same characteristics as another style.
			@param namedStyle The named style to redefine.
			@param dstStyle The style to copy attributes from.
			@return The error \c #kStyleNotInCurrentDocument if \c namedStyle is not in the current document.
		*/
	AIAPI AIErr (*RedefineNamedStyle) ( AIArtStyleHandle namedStyle, AIArtStyleHandle dstStyle );

	/** Moves a named art style to a position in the Graphic Styles palette.
			@param namedStyle The named art style.
			@param index The new position index. Use -1 to move the art style to the end
				of the list. */
	AIAPI AIErr (*MoveNamedStyle) (AIArtStyleHandle namedStyle, ai::int32 index);

	/** Retrieves a named art style by its unique name from a specified document. Searches
		only named styles (those that are shown in the Graphic Styles palette when
		the specified document is current).
			@param artStyle [out] A buffer in which to return the art style reference.
			@param name The unique name.
			@param document The document.
			@see \c #GetArtStyleByName()*/
	AIAPI AIErr (*GetArtStyleByNameFromDocument) ( AIArtStyleHandle* artStyle, const ai::UnicodeString& name,
													AIDocumentHandle document );
	/** Gets the number of named art styles in a specified document (those shown
		in the Graphic Styles palette when that document is current).
		Use with \c #GetNthNamedArtStyleFromDocument() to iterate through art styles
		in a particular document.
			@param count [out] A buffer in which to return the number of styles
			@param document The document.
			@see \c #CountNamedArtStyles()
		*/
	AIAPI AIErr (*CountNamedArtStylesFromDocument) ( ai::int32* count, AIDocumentHandle document );

	/** Retrieves a named art style by index for a specified document.
		Use with \c #CountNamedArtStylesFromDocument() to iterate through art styles
		that are shown in the Graphic Styles palette when that document is current.
			@param n The position index, in the range <code> [0..numStyles-1]</code>.
			@param artStyle [out] A buffer in which to return the art style reference.
			@param document The document.
			@see \c #GetNthNamedArtStyle()
		*/
	AIAPI AIErr (*GetNthNamedArtStyleFromDocument) ( ai::int32 n, AIArtStyleHandle* artStyle,
													 AIDocumentHandle document );

	/** Tests equivalence between two art styles.
			@param artStyle1 The first art style.
			@param artStyle2 The second art style.
			@param result [out] A buffer in which to return the output as true if the styles are equivalent.
			@note A false result does not guarantee that the two styles are not equivalent.
	*/
	AIAPI AIErr (*Equiv) ( AIArtStyleHandle artStyle1, AIArtStyleHandle artStyle2,
							  AIBoolean* result );

	/** Sorts the named art styles in the current document alphabetically. The order
		is reflected in the Graphic Styles palette.
		*/
	AIAPI AIErr (*SortNamedStyles) ( void );

	/** Retrieves the default art style of the current document, which is always
		listed first in the Graphic Styles palette.
			@param artStyle [out] A buffer in which to return the art style reference.
		*/
	AIAPI AIErr (*GetDefaultArtStyle) (AIArtStyleHandle* artStyle);

	/** Retrieves the name of the default art style of the current document, which is always
		listed first in the Graphic Styles palette.
			@param name [out] A buffer in which to return the name.
		*/
	AIAPI AIErr (*GetDefaultArtStyleName) ( ai::UnicodeString& name);

	/** Reports whether an art style exists in the current document.
		(Note that the function returns a boolean value, not an error code.)
			@param artStyle The art style.
			@return True if the art style is in the current document.
		*/
	AIAPI AIBoolean (*ValidateArtStyle) ( AIArtStyleHandle artStyle );

	/** Expands the style of an art object, replacing the art object with the art
		that would be returned by \c #GetStyledArt(). Transfers opacity masks,
		URLs, tags, and so on from the input art to the flattened art.
			@param art The art object. Upon return, this reference is no longer valid.
			@note This function is maintained for compatibility with older plug-ins,
			 but is superseded by \c #GetFlattenedArt()
		 */
	AIAPI AIErr (*FlattenStyle) ( AIArtHandle art );

	/** Retrieves the type of an art style.
			@param artStyle The art style.
			@param type [out] A buffer in which to return the type; a \c #AIArtStyleType value. */
	AIAPI AIErr (*GetArtStyleType) ( AIArtStyleHandle artStyle, ai::int16* type );

	/** Reports whether an art style contains all the pieces it needs in order
		to execute. (Note that this function returns a boolean value, not an error code.)
			@param artStyle The art style.
			@return True if the style can be successfully applied.
			<br>False if the style contains an effect provided by a plug-in that
			cannot be found in the Plug-Ins folder. */
	AIAPI AIBoolean (*CanExecute) ( AIArtStyleHandle artStyle );

	/** Returns the scale factor for an art object's style. (Note that the function returns a
		numeric value, not an error code.) <br>
		The option "Scale Strokes & Effects" allows you to scale the stroke weight
		and effects attached to an art object.The scale factor is stored with the
		art object, and applied after the style is applied. For example, if the style attached
		to an object has a stroke with a weight of 2 pt, and the object's scale factor is 2.5,
		the visual stroke weight is 5 pt.

		@note \c #GetPaintAttributes() gets the unscaled parameter values,as do functions from the
			\c #AIArtStyleParserSuite.
			<br> However, the \c #AIPathStyleSuite calls return the scaled stroke weights
			attached to the objects.

			@param art The art object.
			@return The scale factor.
			@see \c #SetArtStyleScaleFactor() <br> \c #ResetArtStyleScaleFactor()
		 */
	AIAPI AIReal (*GetArtStyleScaleFactor) ( AIArtHandle art );

	/** Sets the scale factor for an art object's style. The scale factor is stored with the
		art object, and applied after the style is applied.
			@param art The art object.
			@param scaleFactor The new scale factor.
			@see \c #GetArtStyleScaleFactor() <br> \c #ResetArtStyleScaleFactor()
		*/
	AIAPI AIErr (*SetArtStyleScaleFactor) ( AIArtHandle art, AIReal scaleFactor );

	/** Applies a new style to an art object that is scaled by the object's current scale factor,
		and resets the scale factor for the object to 1.
			@param art The art object.
			@see \c #GetArtStyleScaleFactor() <br> \c #ResetArtStyleScaleFactor()
		*/
	AIAPI AIErr (*ResetArtStyleScaleFactor) ( AIArtHandle art );

	/** Transforms the art style of an object.
			@param art The art object.
			@param matrix A pointer to the transformation matrix.
			@param lineScale The scale factor to apply to the line-drawing style values
				specified in the art object’s current style.
			@param flags Bit flags that control how the transformation is performed.
				A logical OR of \c #AITransformArtOptions values.
				If the \c kTransformObjects flag is on, it is assumed that the art object itself
				has also been transformed by the same matrix, and that any transformation of the points,
				descendant art, and so on, have already been performed. This allows gradient vectors and
				other style attributes that are dependent upon object bounds to be adjusted immediately,
				rather than deferred until artwork synchronization.
			*/
	AIAPI AIErr (*TransformObjectArtStyle) ( AIArtHandle art, AIRealMatrix *matrix, AIReal lineScale, ai::int32 flags );

	/** Examines an art style for specific attributes, and returns the ones found.
		(Note that the function returns an attribute structure, not an error code.)
			@param artStyle The art style.
			@param checkFor A logical OR of \c #AIArtStyleHasAttrsBits values,
				specifying which attributes to check for. Pass \c #kStyleCheckForAll
				to check all attributes.
			@return A logical OR of \c #AIArtStyleHasAttrsBits values for those attributes found in the style.
		*/
	AIAPI AIArtStyleHasAttrs (*ExamineStyle) ( AIArtStyleHandle artStyle, AIArtStyleHasAttrs checkFor );

	/** Retrieves the art style that will be used for new art created by a tool, based on
		application preferences.
			@param artStyle [out] A buffer in which to return the style reference.
		*/
	AIAPI AIErr (*GetToolArtStyle) ( AIArtStyleHandle* artStyle );

	// ===================== Introduced in Illustrator 10.0 =========================

	/** Expands the style of an art object, replacing the art object with the art
		that would be returned by \c #GetStyledArt(). Transfers opacity masks,
		URLs, tags, and so on from the input art to the flattened art.
			@param art The art object. Upon return, this reference is no longer valid,
				unless no flattening was needed.
			@param flattenedArt [out] A buffer in which to return the flattened art object.
		 */
	AIAPI AIErr (*GetFlattenedArt) ( AIArtHandle art, AIArtHandle *flattenedArt );

	/** Reports whether an art object has a style that would be equivalent to a null style.
		This is the same as verifying that the style has no fill, no stroke,
		no effects, and default transparency attributes. (Note that the function returns a
		boolean value, not an error code.)
			@param art The art object.
			@return True if the art's style is effectively null.*/
	AIAPI AIBoolean (*HasEffectiveNullStyle) ( AIArtHandle art );

	/** Retrieves the map for the path style of an art style, as retrieved
		by \c #GetPaintAttributes(). The map indicates which fields of an \c #AIPathStyle
		are specified by a partial style. A path style can contain unknown or mixed
		attributes (indicated by a value of false for that attribute in the map) only
		when it is associated with a graph object, not when it is associated with an art object.
			@param artStyle The art style.
			@param aiPathStyleMap [out] A buffer in which to return the path style map.  */
	AIAPI AIErr (*GetPaintMap) ( AIArtStyleHandle artStyle, AIPathStyleMap* aiPathStyleMap );

};


#include "AIHeaderEnd.h"


#endif
