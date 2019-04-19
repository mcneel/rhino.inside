#ifndef __AIArtStyleParser__
#define __AIArtStyleParser__

/*
 *        Name:	AIArtStyleParser.h
 *     Purpose:	Adobe Illustrator Art Style Parser Suite.
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

#ifndef __AIArtStyle__
#include "AIArtStyle.h"
#endif

#ifndef __AILiveEffect__
#include "AILiveEffect.h"
#endif

#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif

#include "AISmoothShadingStyle.h"

#include "AIHeaderBegin.h"

/** @file AIArtStyleParser.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIArtStyleParserSuite				"AI Art Style Parser Suite"
#define kAIArtStyleParserSuiteVersion9		AIAPI_VERSION(9)
#define kAIArtStyleParserSuiteVersion		kAIArtStyleParserSuiteVersion9
#define kAIArtStyleParserVersion			kAIArtStyleParserSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

// Opaque references to data structures inside app.
/** Opaque reference to an art style parser. */
typedef struct _t_AIStyleParser* AIStyleParser;

/** Opaque reference to a Live Effect data structure in an art style parser.
		\li Pre-effects are Live Effects that show up before any fills and strokes in the
	Appearance palette.
		\li Post-effects are Live Effects that show up after all the fills and strokes in the
	Appearance palette.
	*/
typedef struct _t_AIParserLiveEffect* AIParserLiveEffect;

/** Opaque reference to a paint field data structure in an art style parser.
	A paint field corresponds to either a fill or a stroke in the art style. It
	can contain Live Effects and a blend field. <br><br>
	@note A paint field can contain effects that affect only that paint field and not the entire art style.
		Effects are executed in sequence, and the output of one becomes the input of the next.
		Filling or stroking is performed within this order. A Color Position is the spot
		in a paint field's effect order at which painting occurs.
	*/
typedef struct _t_AIParserPaintField* AIParserPaintField;

/** Opaque reference to a blend field in a paint field data structure in an art style parser.
	Controls the overall transparency of the style. This is listed last  in the Appearance palette.
	*/
typedef struct _t_AIParserBlendField* AIParserBlendField;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The \c AIArtStyleParser allows you to manipulate art styles, and access
	information typically shown in the Appearance palette.

	The parser constructs its own data structures when asked to parse an art style, which
	are tied to that art style unless modified. When parser data structures are modified,
	the relationship between the parser structure and art style becomes unreliable, and you should
	avoid making calls to \c #SetFocus() and \c #EditEffectParameters(), which depend on
	that relationship.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIArtStyleParserSuite and \c #kAIArtStyleParserVersion.

	You can call \c #CreateNewStyle() to build a new style from an existing parser data structure,
	using a workflow like this:

@code
NewParser(&parser)
ParseStyle(parser, artStyle)
...
<Manipulate the data structures - reordering, adding, removing, redefining properties, and so on.>
	...
CreateNewStyle(parser, &newArtStyle)
DisposeParser(parser)
@endcode

*/
struct AIArtStyleParserSuite {

	/** Constructs a new parser.
			@param parser [out] A buffer in which to return the new parser reference.
		*/
	AIAPI AIErr (*NewParser) ( AIStyleParser* parser );

	/** Frees memory associated with a parser that is no longer needed.
			@param The parser. Upon return, this reference in no longer valid.
	*/
	AIAPI AIErr (*DisposeParser) ( AIStyleParser parser );

	/** Parses the contents of an art style, creating parser data structures accordingly.
			@param parser The parser.
			@param artStyle The art style.
		*/
	AIAPI AIErr (*ParseStyle) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	/** Merges the properties of an art style into a parser. The same as the
		"Merge Graphic Styles" option in the Graphic Styles palette flyout menu.
			@param parser The parser.
			@param artStyle The art style.
		*/
	AIAPI AIErr (*MergeStyleIntoParser) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	/** Reports whether a parser was able to successfully parse an art style.
		Valid only immediately after a call to \c #ParseStyle() using this parser.
		(Note that this function returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the most recent parsing operation was successful.
		*/
	AIAPI AIBoolean (*IsStyleParseable) ( AIStyleParser parser );

	/** Counts the number of pre-effects in a parser. Pre-effects are Live
		Effects that show up before any fills and strokes in the Appearance palette.
		(Note that this function returns a numeric value, not an error code.)
			@param parser The parser.
			@return The number of pre-effects.
		*/
	AIAPI ai::int32 (*CountPreEffects) ( AIStyleParser parser );

	/** Counts the number of post-effects in a parser. Post-effects are Live
		Effects that show up after all the fills and strokes in the Appearance palette.
		(Note that this function returns a numeric value, not an error code.)
			@param parser The parser.
			@return The number of post-Effects.
		*/
	AIAPI ai::int32 (*CountPostEffects) ( AIStyleParser parser );

	/** Counts the number of paint fields in a parser. A paint field corresponds
		to either a fill or a stroke in the art style. Each paint field can also
		contain Live Effects and transparency information.
		(Note that this function returns a numeric value, not an error code.)
			@param parser The parser.
			@return The number of paint fields.*/
	AIAPI ai::int32 (*CountPaintFields) ( AIStyleParser parser );

	/** Counts the number of Live Effects in a paint field.
	(Note that this function returns a numeric value, not an error code.)
			@param parser The paint field.
			@return The number of Live Effects.
	*/
	AIAPI ai::int32 (*CountEffectsOfPaintField) ( AIParserPaintField paintField );

	/** Retrieves a Pre-Effect from a parser by position index. Use with \c #CountPreEffects()
		to iterate through PreEffects.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect.
		 */
	AIAPI AIErr (*GetNthPreEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect* effect );

	/** Retrieves a Post-Effect from a parser by position index. Use with \c #CountPostEffects()
		to iterate through PostEffects.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect.
		*/
	AIAPI AIErr (*GetNthPostEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect* effect );

	/**Retrieves a paint field from a parser by position index. Use with \c #CountPaintFields()
		to iterate through paint fields.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numFields-1]</code>.
			@param paintField [out] A buffer in which to return the paint field.
		*/
	AIAPI AIErr (*GetNthPaintField) ( AIStyleParser parser, ai::int32 n, AIParserPaintField* paintField );

	/** Retrieves a Live Effect from a paint field by position index. Use with \c #CountEffectsOfPaintField()
		to iterate through Live Effects.
			@param paintField The paint field.
			@param n The position index, in the range <code>[0..numEffects-1]</code>.
			@param effect [out] A buffer in which to return the effect.*/
	AIAPI AIErr (*GetNthEffectOfPaintField) ( AIParserPaintField paintField, ai::int32 n,
											  AIParserLiveEffect* effect );

	/** Retrieves the overall art style transparency from a parser in the form of a blend field.
			@param parser The parser.
			@param blendField [out] A buffer in which to return the blend field.
	*/
	AIAPI AIErr (*GetStyleBlendField) ( AIStyleParser parser, AIParserBlendField* blendField );

	/** Inserts a Pre-Effect into a parser at a specified index.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>. Use -1 to
				insert element at the end.
			@param effect The effect.
		*/
	AIAPI AIErr (*InsertNthPreEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect effect );

	/** Inserts a Post-Effect into the parser at a specified index.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numEffects-1]</code>. Use -1 to
				insert element at the end.
			@param effect The effect.
		*/
	AIAPI AIErr (*InsertNthPostEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect effect );

	/** Inserts a paint field into a parser at a specified index.
			@param parser The parser.
			@param n The position index, in the range <code>[0..numFields-1]</code>. Use -1 to
				insert element at the end.
			@param paintField The paint field.
		*/
	AIAPI AIErr (*InsertNthPaintField) ( AIStyleParser parser, ai::int32 n, AIParserPaintField paintField );

	/** Inserts a Live Effect into a paint field in a parser at specified index.
			@param parser The parser.
			@param paintField The paint field.
			@param n The position index, in the range <code>[0..numEffects-1]</code>. Use -1 to
							insert element at the end.
			@param effect The Live Effect.
	 */
	AIAPI AIErr (*InsertNthEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField, ai::int32 n,
												 AIParserLiveEffect effect );

	/** Removes a Pre-Effect from a parser.
			@param parser The parser.
			@param effect The effect.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemovePreEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );

	/** Removes a Post-Effect from a parser.
			@param parser The parser.
			@param effect The effect.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemovePostEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );

	/** Removes a paint field from a parser.
			@param parser The parser.
			@param paintField The paint field.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemovePaintField) ( AIStyleParser parser, AIParserPaintField paintField, AIBoolean doDelete );

	/** Removes a Live Effect from a paint field in a parser.
			@param parser The parser.
			@param paintField The paint field.
			@param effect The effect.
			@param doDelete When true, dispose of the memory associated with the element.
				You might not want to do this if you are moving elements from one position to another.
		*/
	AIAPI AIErr (*RemoveEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField,
											  AIParserLiveEffect effect, AIBoolean doDelete );

	/** Removes all the effects from a parser.
			@param parser The parser.
		*/
	AIAPI AIErr (*RemoveAllEffects) ( AIStyleParser parser );

	/** Removes all the effects and all the paint fields from a parser, except the focus fill and stroke.
		These are the ones that the user is currently editing, which show in the fill and stroke
		proxies in the Tool and Color palettes. The function also resets all transparency
		to normal 100% opaque and places the focus stroke on top of the focus fill
		in the stacking order.
			@param parser The parser.
		*/
	AIAPI AIErr (*Simplify) ( AIStyleParser parser );

	/** Retrieves the focus fill from a parser. If an art style has multiple fills,
		the user can only edit one at a time. The one currently being edited is the focus fill,
		and it is shown in the fill/stroke proxies on the Tool and Color palettes.
			@param parser The parser.
			@param paintField [out] A buffer in which to return the focus fill.
		*/
	AIAPI AIErr (*GetFocusFill) ( AIStyleParser parser, AIParserPaintField* paintField );

	/** Retrieves the focus stroke from a parser. If an art style has multiple strokes,
		the user can only edit one at a time. The one currently being edited is the focus stroke,
		and it is shown in the fill/stroke proxies on the Tool and Color palettes.
			@param parser The parser.
			@param paintField [out] A buffer in which to return the focus stroke.
		*/
	AIAPI AIErr (*GetFocusStroke) ( AIStyleParser parser, AIParserPaintField* paintField );

	/** Sets the focus fill or focus stroke for a parser.
			@param parser The parser.
			@param paintField The fill or stroke.
			@see \c #SetFocus()
		*/
	AIAPI AIErr (*SetParserFocus) ( AIStyleParser parser, AIParserPaintField paintField );

	/** Sets the focus fill or focus stroke for a parser, and also modifies the art style
		from which the parser's data structures were constructed.
		Use when the data structures in the given parser have not been
		modified since the call to \c #ParseStyle().
			@param artStyle The art style that was passed to \c #ParseStyle() for this parser
			@param parser The parser
			@param paintField The fill or stroke.
			@see \c #SetParserFocus()
		*/
	AIAPI AIErr (*SetFocus) ( AIArtStyleHandle artStyle, AIStyleParser parser, AIParserPaintField paintField );

	/**  Retrieves the position in the stacking order (from top to bottom) where the Group
		Contents for a parser would be rendered. (Note that this function returns a numeric value,
		not an error code.)

		Group Contents affects the generation of styled art when applied to art container objects
		like groups or text. The Group Contents controls where the original contents inside
		the group are rendered relative to the stacking order of the fills and strokes
		in the art styles.
			@param parser The parser.
			@return The position in the stacking order.
		*/
	AIAPI ai::int32 (*GetGroupContentsPosition) ( AIStyleParser parser );

	/** Move the Group Contents position in a parser.
			@param parser The parser.
			@param position The new position in the stacking order, from top to bottom.
			@see \c #GetGroupContentsPosition()
		*/
	AIAPI AIErr (*MoveGroupContentsPosition) ( AIStyleParser parser, ai::int32 position );

	/** Constructs a new art style based on the elements in a parser.
		Call \c #ParseStyle() with the new style before using \c #SetFocus()
		or \c #EditEffectParameters().
			@param parser The parser.
			@param artStyle [out] A buffer in which to return the new art style reference.
		*/
	AIAPI AIErr (*CreateNewStyle) ( AIStyleParser parser, AIArtStyleHandle* artStyle );

	/** Reports whether a style is invisible; that is, there are no effects,
		all the paint fields have a color of \c none, and the overall transparency
		contains default values. (Note that this function returns a boolean value,
		not an error code.)
			@param parser The parser.
			@return True if the associated style is invisible.
		*/
	AIAPI AIBoolean (*IsStyleVisible) ( AIStyleParser parser );

	/** Reports whether a parser has fill or stroke. (Note that this function
		returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parser contains any non-empty fill or stroke values.
		*/
	AIAPI AIBoolean (*ContainsPaint) ( AIStyleParser parser );

	/** Reports whether a parser has any Live Effects. (Note that this function
		returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parser contains any effects.
		*/
	AIAPI AIBoolean (*ContainsEffects) ( AIStyleParser parser );

	/** Reports whether a parser has transparency. (Note that this function
		returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parser contains any non-default transparency information.
		*/
	AIAPI AIBoolean (*ContainsTransparency) ( AIStyleParser parser );

	/** Retrieves the Live Effect object reference from a parser.
			@param parser The parser.
			@param liveEffectHandle [out] A buffer in which to return the Live Effect reference.
		*/
	AIAPI AIErr (*GetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle* liveEffectHandle );

	/** Retrieves the LiveEffect parameters data structure from a parser.
			@param effect The effect.
			@param params [out] A buffer in which to return the Live Effect parameters.
		*/
	AIAPI AIErr (*GetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters* params );

	/** Sets the Live Effect object reference in a parser.
			@param parser The parser.
			@param liveEffectHandle The Live Effect reference.
		*/
	AIAPI AIErr (*SetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle liveEffectHandle );

	/** Sets the  Live Effect parameters data structure in a parser.
			@param effect The effect.
			@param params The Live Effect parameters.
		*/
	AIAPI AIErr (*SetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters params );

	/** Copies a Live Effect data structure into a new equivalent structure. Used by
		the Appearance palette when users duplicate a Live Effect.
			@param effect The effect.
			@param clonedEffect [out] A buffer in which to return the new Live Effect.
		*/
	AIAPI AIErr (*CloneLiveEffect) ( AIParserLiveEffect effect, AIParserLiveEffect* clonedEffect );

	/** Opens the editing dialog, allowing the user to edit the parameters
		of an effect in an art style, and creates a new art style with the user's choices,
		which is applied to all the art objects currently targeted in the document.

		@note Use this function with caution.

			@param artStyle The art style, as previously passed to \c #ParseStyle().
			@param effect The effect, as retrieved from a parser whose data structures
				have not been modified since the call \c #ParseStyle().
		*/
	AIAPI AIErr (*EditEffectParameters) ( AIArtStyleHandle artStyle, AIParserLiveEffect effect );

	/** Reports whether a paint field corresponds to a fill. (Note that this function
		returns a boolean value, not an error code.)
			@param paintField The paint field.
			@return True if the paint field is for a fill.
	 */
	AIAPI AIBoolean (*IsFill) ( AIParserPaintField paintField );

	/** Reports whether a paint field corresponds to a stroke. (Note that this function
		returns a boolean value, not an error code.)
			@param paintField The paint field.
			@return True if the paint field is for a stroke.
	 */
	AIAPI AIBoolean (*IsStroke) ( AIParserPaintField paintField );

	/** Retrieves fill information from a paint field.
			@param paintField The paint field.
			@param fill [out] A buffer in which to return the fill style.
			@param paintData [out] A buffer in which to return additional paint data.
	  */
	AIAPI AIErr (*GetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );

	/** Retrieves stroke information from a paint field.
			@param paintField The paint field.
			@param stroke [out] A buffer in which to return the stroke style.
			@param paintData [out] A buffer in which to return additional paint data.
		*/
	AIAPI AIErr (*GetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );

	/** Sets fill information for a paint field.
			@param paintField The paint field.
			@param fill The new fill style.
			@param paintData Additional paint data.
		*/
	AIAPI AIErr (*SetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );

	/** Sets stroke information for a paint field.
			@param paintField The paint field.
			@param stroke The new stroke style.
			@param paintData Additional paint data. */
	AIAPI AIErr (*SetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );

	/** Retrieves transparency information from a paint field. See \c AIMask.h for the
		keys used to get information from the dictionary.
			@param paintField The paint field.
			@param blendDict [out] A buffer in which to return the dictionary containing transparency information.
		*/
	AIAPI AIErr (*GetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );

	/** Sets the transparency information for a paint field. See \c AIMask.h for the
		keys used to set information in the dictionary.
			@param paintField The paint field.
			@param blendDict The dictionary containing transparency information.
		*/
	AIAPI AIErr (*SetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );

	/** Retrieves the color position of a paint field (the point in effect order at which painting occurs).
			@param paintField The paint field.
		*/
	AIAPI ai::int32 (*GetColorPosn) ( AIParserPaintField paintField );

	/** Sets the color position of a paint field (the point in the effect order at which painting occurs).
			@param paintField The paint field.
		*/
	AIAPI AIErr (*SetColorPosn) ( AIParserPaintField paintField, ai::int32 colorPosn );

	/** Copies a paint field data structure into a newly created equivalent structure. Used by
		the Appearance palette when users duplicate a fill or stroke.
			@param paintField The paint field.
			@param clonedPaintField [out] A buffer in which to return the new paint field.

		*/
	AIAPI AIErr (*ClonePaintField) ( AIParserPaintField paintField, AIParserPaintField* clonedPaintField );

	/**	Retrieves LiveEffect and/or parameter references for Live Effects in
		a paint field that substitute for the built-in fill or stroke behavior. The returned parameters can
		be non-null even when the Live Effect reference is null, in the case where the built-in fill or stroke filter
		has a parameter dictionary that contains non-basic options other than transparency.

			@note Current examples of strokes with an effect handle are Brushes and Inside/Outside Aligned
				strokes, which are implemented as Live Effects that replace the default stroking behavior.
				The only current example of a paint field that returns a null Live Effect reference but non-null
				parameters are strokes with dash adjustment, arrowheads, or other Beautiful Strokes
				options. (See \c AIBeautifulStrokes.h).
			@param paintField The paint field
			@param liveEffectHandle [out] A buffer in which to return the Live Effect reference. Can be \c NULL.
			@param params [out] A buffer in which to return the Live Effect parameters. Can be \c NULL.
		*/
	AIAPI AIErr (*GetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle* liveEffectHandle,
											AILiveEffectParameters* params );

 	/** Sets the LiveEffect and/or parameter references for Live Effects in a paint field
		that substitute for the built-in fill or stroke behavior.

			@param paintField The paint field
			@param liveEffectHandle The Live Effect reference. Pass null to remove the live effect.
			@param params The Live Effect parameters. Pass null to remove the live effect parameters.
		*/
	AIAPI AIErr (*SetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle liveEffectHandle,
											AILiveEffectParameters params );

	/** Retrieves the transparency information for a blend field. See \c AIMask.h for the keys used
		to access information in the dictionary.
			@param blendField The blend field.
			@param blendDict The dictionary in which to return the transparency information.
		*/
	AIAPI AIErr (*GetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

	/** Sets the transparency information for a blend field. See \c AIMask.h for the keys used
		to access information in the dictionary.
			@param blendField The blend field.
			@param blendDict The dictionary containing the transparency information.
		*/
	AIAPI AIErr (*SetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

	// NEW FOR AI10

	/** Retrieves the even-odd fill rule for a paint field.
		(See the \c evenodd field in the \c #AIPathStyle structure.)
			@param paintField The paint field.
			@param evenodd [out] A buffer in which to return true if the even-odd rule is used to determine path insideness.
			@return An error \c #kBadParameterErr if the paint field does not correspond to a fill.
		 */
	AIAPI AIErr (*GetEvenOdd) ( AIParserPaintField paintField, AIBoolean* evenodd );

	/** Sets the even-odd fill rule for a paint field.
		(See the \c evenodd field in the \c #AIPathStyle structure.)
			@param paintField The paint field.
			@param evenodd True if the even-odd rule should be used to determine path insideness.
			@return An error \c #kBadParameterErr if the paint field does not correspond to a fill. */
	AIAPI AIErr (*SetEvenOdd) ( AIParserPaintField paintField, AIBoolean evenodd );

	/** Constructs a new paint field with a given fill, even-odd fill rule, and
		gradient vector information. The new paint field is not associated with any parser.
			@param fill The fill style.
			@param evenOdd True if the even-odd rule should be used to determine path insideness.
			@param paintData The paint data structure containing the gradient vector information. Can be \c NULL.
			@param paintField [out] A buffer in which to return the new paint field.
		 */
	AIAPI AIErr (*NewPaintFieldFill) ( const AIFillStyle* fill, AIBoolean evenOdd, const AIArtStylePaintData* paintData,
									   AIParserPaintField* paintField );

	/** Constructs a new paint field with a given stroke. The new paint field is not associated with any parser.
			@param stroke The stroke style.
			@param paintData Not used, pass \c NULL.
			@param paintField [out] A buffer in which to return the new paint field.
		*/
	AIAPI AIErr (*NewPaintFieldStroke) ( const AIStrokeStyle* stroke, const AIArtStylePaintData* paintData,
										 AIParserPaintField* paintField );

	/** Frees the memory associated with a paint field.
			@note Do not use on paint fields that are retrieved from or inserted into a parser.
			Freeing the parser with \c #DisposeParser() frees its contained data structures.
			@param paintField The paint field. Upon return, this reference is no longer valid.
		*/
	AIAPI AIErr (*DisposePaintField) ( AIParserPaintField paintField );

	/** Constructs a new Live Effect parser data structure from Live Effect and
		parameters references. The new data structure is not associated
		with any parser.
			@param liveEffectHandle The Live Effect reference.
			@param params The parameters reference.
			@param effect [out] A buffer in which to return the new effect.
		*/
	AIAPI AIErr (*NewParserLiveEffect) ( AILiveEffectHandle liveEffectHandle, AILiveEffectParameters params,
										 AIParserLiveEffect* effect );

	/** Frees the memory associated with a Live Effect parser data structure.
			@note Do not use on effects that are retrieved from or inserted into a parser.
			Freeing the parser with \c #DisposeParser() frees its contained data structures.
			@param effect The Live Effect data structure. Upon return, this reference is no longer valid. */
	AIAPI AIErr (*DisposeParserLiveEffect) ( AIParserLiveEffect effect );


	/** Retrieves the art style that is currently selected in the Graphic Styles palette. Gets the first of
		multiple selected styles.
			@param style [out] A buffer in which to return the art style, or \c NULL if no style is selected.
		 */
	AIAPI AIErr (*GetCurrentArtStyle) ( AIArtStyleHandle* style );

	// NEW FOR AI13

	/** Opens the editing dialog, allowing the user to edit the parameters of an effect that is substituting
		for a fill or stroke. Creates a new art style with the user's choices, and applies it to all the art
		objects currently targeted in the document.
			@note Use this function with caution.

			@param artStyle The art style, as previously passed to \c #ParseStyle().
			@param paintField The paint field, as retrieved from a parser whose data structures
				have not been modified since the call \c #ParseStyle().
			@see \c #EditEffectParameters()
		*/
	AIAPI AIErr (*EditPaintEffectParameters) ( AIArtStyleHandle artStyle, AIParserPaintField paintField );

	/** Reports whether a paint field has normal 100% opacity. Does not check other
		transparency attributes, such as knockout or isolated blending. (Note that this
		function returns a boolean value, not an error code.)
			@param paintField The paint field.
			@return True if the paint field is opaque.
		*/
	AIAPI AIBoolean (*IsNormalOpaquePaintBlend) ( AIParserPaintField paintField );

	/** Reports whether a blend field has normal 100% opacity. Does not check other
		transparency attributes, such as knockout or isolated blending. (Note that this
		function returns a boolean value, not an error code.)
			@param blendField The blend field.
			@return True if the blend field is opaque.
		*/
	AIAPI AIBoolean (*IsNormalOpaqueBlend) ( AIParserBlendField blendField );

	/** Reports whether a paint field has a default blend, that is, normal 100% opacity
		with non-isolated blending and the knockout attribute set to either off or inherit. (Note that this
		function returns a boolean value, not an error code.)
			@param paintField The paint field.
			@return True if the paint field has a default blend.
		*/
	AIAPI AIBoolean (*IsDefaultPaintBlend) ( AIParserPaintField paintField );

	/** Sets a paint field to have a default blend; that is, normal 100% opacity, with non-isolated blending
		and the knockout attribute set to off.
			@param paintField The paint field.
		*/
	AIAPI AIErr (*SetDefaultPaintBlend) ( AIParserPaintField paintField );

	/** Reports whether a blend field is a default blend; that is, normal 100% opacity,
		with non-isolated blending and the knockout attribute set to either off or inherit. (Note that this
		function returns a boolean value, not an error code.)
			@param blendField The blend field.
			@return True if the blend field is a default blend.
		*/
	AIAPI AIBoolean (*IsDefaultBlend) ( AIParserBlendField blendField );

	/** Sets a blend field to a default blend; that is, normal 100% opacity, with non-isolated blending
		and the knockout attribute either set to off or maintained at the inherited value.
			@param blendField The blend field to set.
			@param knockoutOff True to turn knockout off. False to maintain the inherited knockout value,
				unless that value is on, in which case it is set to off.
		*/
	AIAPI AIErr (*SetDefaultBlend) ( AIParserBlendField blendField, AIBoolean knockoutOff );

	/** Reports whether the style parsed by a parser is a simple style; that is, a style
		with no effects, only one normal fully opaque fill and one normal fully opaque stroke, and the stroke
		stacked on top of the fill. (Note that this function returns a boolean value, not an error code.)
			@param parser The parser.
			@return True if the parsed style is simple.
		*/
	AIAPI AIBoolean (*IsStyleSimple) ( AIStyleParser parser );

	/** Retrieves the name and major and minor versions of the Live Effect data structure in a parser.
		Gets the name and version numbers even if the  plug-in that provides the effect is
		missing and there is no  LiveEffect object reference associated with the data structure.
			@param effect The Live Effect data structure.
			@param name [out] A buffer in which to return the internal name of the effect.
			@param major [out] A buffer in which to return the major version of the effect.
			@param minor [out] A buffer in which to return the minor version of the effect.
		*/
	AIAPI AIErr (*GetLiveEffectNameAndVersion) ( AIParserLiveEffect effect, const char** name, ai::int32* major, ai::int32* minor );

	/** Retrieves the name and major and minor versions of the Live Effect in a paint field data structure in a parser.
		Gets the name and version numbers even if the  plug-in that provides the effect is missing.
			@param paintField The paint field data structure.
			@param name [out] A buffer in which to return the internal name of the effect,
				or \c NULL if no Live Effect is substituting for the built-in fill or stroke behavior.
			@param major [out] A buffer in which to return the major version of the effect,
				or 0 if no Live Effect is substituting for the built-in fill or stroke behavior.
			@param minor [out] A buffer in which to return the minor version of the effect,
				or 0 if no Live Effect is substituting for the built-in fill or stroke behavior.
		*/
	AIAPI AIErr (*GetPaintLiveEffectNameAndVersion) ( AIParserPaintField paintField, const char** name, ai::int32* major, ai::int32* minor );

	// NEW FOR AI14

	/** Compares two parsed styles to check if they are equivalent.
	(Note that this function returns a boolean value, not an error code.)
	 To compare two styles, create two \c #AIStyleParser objects,
	call \c #ParseStyle() for each object, then call this function.
			@param parserStyle1 The first style parser.
			@param parserStyle2 The second style parser.
			@return True if the parsed styles are equivalent, false otherwise.
		*/
	AIAPI AIBoolean (*CompareStyles) ( AIStyleParser parserStyle1, AIStyleParser parserStyle2);

	/** Reports the visibility status of an effect, which affects whether it is drawn.
			@param effect The effect, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible [out] A buffer in which to return true if the effect is visible.
		*/
	AIAPI AIErr (*GetEffectVisible) ( AIParserLiveEffect effect, AIBoolean *visible);

	/** Sets the visibility status of an effect, which affects whether it is drawn.
	    This is applied to all the art objects currently targeted in the document.
			@param artStyle The art style that contains the effect (as previously passed to \c #ParseStyle()).
			@param effect The effect, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the effect.
		*/
	AIAPI AIErr (*SetEffectVisible) ( AIArtStyleHandle artStyle, AIParserLiveEffect effect, AIBoolean visible );


	/** Reports the visibility status of a paint field, which affects whether it is drawn.
			@param paintField The paint field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible [out] A buffer in which to return true if the paint field is visible, false otherwise.
		*/
	AIAPI AIErr (*GetPaintFieldVisible) ( AIParserPaintField paintField, AIBoolean *visible);


	/** Sets the visibility status of a paint field, which affects whether it is drawn.
	    This is applied to all the art objects currently targeted in the document.
			@param artStyle The art style that contains the paint field (as previously passed to \c #ParseStyle()).
			@param paintField The paint field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the paint field.
		*/
	AIAPI AIErr (*SetPaintFieldVisible) ( AIArtStyleHandle artStyle, AIParserPaintField paintField, AIBoolean visible );

	/** Reports the visibility status of a blend field, which affects whether it is drawn.
			@param blendField The blend field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible [out] A buffer in which to return true if the blend field is visible.
		*/
	AIAPI AIErr (*GetBlendFieldVisible) ( AIParserBlendField blendField, AIBoolean *visible);


	/** Sets the visibility status of a blend field, which affects whether it is drawn.
	    This is applied to all the art objects currently targeted in the document.
			@param artStyle The art style that contains the blend field (as previously passed to \c #ParseStyle()).
			@param blendField The blend field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the blend field.
		*/
	AIAPI AIErr (*SetBlendFieldVisible) ( AIArtStyleHandle artStyle, AIParserBlendField blendField, AIBoolean visible );



	/** Reports the visibility status of blend of a paint field (fill/stroke), which affects whether the blend
	is drawn.
			@param paintField The paint field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible [out] A buffer in which to return true if the blend field is visible, false otherwise.
		*/
	AIAPI AIErr (*GetPaintBlendVisible) ( AIParserPaintField paintField, AIBoolean *visible);


	/** Sets the visibility status of blend of a paint field (fill/stroke), which affects whether the blend
	is drawn. This is applied to all the art objects currently targeted in the document.
			@param artStyle The art style that contains the blend field (as previously passed to \c #ParseStyle()).
			@param paintField The paint field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the blend field.
		*/
	AIAPI AIErr (*SetPaintBlendVisible) ( AIArtStyleHandle artStyle, AIParserPaintField paintField, AIBoolean visible );

	/**  Modifies the properties of a parser, retaining properties that are common to both
     the parser and the given style, and discarding all other properties.

     You can use this to determine the common properties of two styles.

	 @param	parser 	The parser.
	 @param	artStyle The art style.
	 */
	AIAPI AIErr (*IntersectStyleWithParser) ( AIStyleParser parser, AIArtStyleHandle artStyle );


	/** Retrieves a paint field from a parser that is equivalent to a given paint field, starting at
	   a given index in the parser.
			@param parser The parser in which to search.
			@param paintField The paint field to search for.
			@param startIndex The 0-based index into the parser at which to begin the search.
			@param index A buffer in which to return the 0-based index of the equivalent paint field, or -1 if none is found.
		*/

	AIAPI AIErr (*FindEquivalentPaintField) ( AIStyleParser parser, AIParserPaintField paintField, ai::int32 startIndex, ai::int32* index );

	/** Retrieves the focus effect from a parser. If an art style has multiple effects,
		the user can only edit one at a time; the one currently being edited is the focus effect.
			@param parser The parser.
			@param effectField [out] A buffer in which to return the focus effect.
			@see \c #SetParserFocusEffect()
		*/
	AIAPI AIErr (*GetFocusEffect) ( AIStyleParser parser, AIParserLiveEffect* effectField );

	/** Sets the focus effect for a parser, and also modifies the art style
		from which the parser's data structures were constructed.
		Use when the data structures in the given parser have not been
		modified since the call to \c #ParseStyle().
			@param artStyle The art style that was passed to \c #ParseStyle() for this parser
			@param parser The parser.
			@param effectField The new focus effect.
			@see \c #SetParserFocusEffect()
		*/
	AIAPI AIErr (*SetFocusEffect) ( AIArtStyleHandle artStyle, AIStyleParser parser, AIParserLiveEffect effectField );

	/** Sets the focus effect for a parser.
			@param parser The parser.
			@param effectField The new focus effect.
			@see \c #SetFocusEffect()
		*/
	AIAPI AIErr (*SetParserFocusEffect) ( AIStyleParser parser, AIParserLiveEffect effectField );

	/** Opens the editing dialog, allowing the user to edit the parameters of an effect. Sets this
	 as the focus effect, and updates the art styles of all the art objects currently targeted
	 in the document with the user's choices.

	 Use this function with caution.

	 @param effectField The effect, as retrieved from a parser whose data structures have
	 not been modified since a call to \c #ParseStyle().
	 */
	AIAPI AIErr (*EditEffectParametersInSelection) ( AIParserLiveEffect effectField );


	/**  Searches a parser for an equivalent effect. Searches post-effects by default; you can
     also choose to search pre-effects and/or paint fields.
	 @param parser The parser object.
	 @param paintField A paint field in which to search, or null to search only in pre- and/or post-effects.
	 @param effectField The effect for which an equivalent is wanted.
	 @param preEffect True to search pre-effects as well as post-effects.
	 @param startIndex  The 0-based index into the parser at which to begin the search.
	 @param index [out] A buffer in which to return the 0-based index of the equivalent effect, or -1 if none is found.
	 */
	AIAPI AIErr (*FindEquivalentEffect) ( AIStyleParser parser, AIParserPaintField paintField, AIParserLiveEffect effectField, AIBoolean preEffect, ai::int32 startIndex, ai::int32* index );



	/**  Reports whether a style contains given attributes.

	 @param artStyle The art style.
	 @param attributes  The parser that contains the attributes to be matched.
	 @param includeTransparency True to include the transparency field in the attributes to be matched. .
	 */
	AIAPI AIBoolean (*StyleContainsAttributes) ( AIArtStyleHandle artStyle, AIStyleParser attributes, AIBoolean includeTransparency );

	/** Sets the visibility of an effect for a parser.

			@param effect The effect, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the effect.
		*/
	AIAPI AIErr (*SetParserEffectVisible) ( AIParserLiveEffect effect, AIBoolean visible);

	/** Sets the visibility of a paint field for a parser.

			@param paintField The paint field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the paint field
		*/
	AIAPI AIErr (*SetParserPaintFieldVisible) ( AIParserPaintField paintField, AIBoolean visible);

	/** Sets the visibility of a blend field for a parser.

			@param blendField The blend field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the blend field.
		*/
	AIAPI AIErr (*SetParserBlendFieldVisible) ( AIParserBlendField blendField, AIBoolean visible);

	/** Sets the visibility of a blend of a paint field (fill/stroke) for a parser.

			@param paintField The paint field, as retrieved from a parser whose data structures
			have not been modified since the call \c #ParseStyle().
			@param visible True to show, false to hide the paint blend
		*/
	AIAPI AIErr (*SetParserPaintBlendVisible) ( AIParserPaintField paintField, AIBoolean visible);

    
    /** Constructs a new paint field with a given smooth shading.
     The new paint field is not associated with any parser.
     @param smoothStyle The smoothStyle style.
     @param paintField [out] A buffer in which to return the new paint field.
     */
    AIAPI AIErr(*NewPaintFieldSmoothShading) ( AISmoothShadingStyle smoothStyle/*move aware*/, AIParserPaintField& paintField);
    
    /** Reports whether a paint field corresponds to a smooth shading style. (Note that this function
     returns a boolean value, not an error code.)
     @param paintField The paint field.
     @return True if the paint field is for a smooth shading style.
     */
    AIAPI AIBoolean (*IsSmoothShadingStyle) ( AIParserPaintField paintField );
    
    /** Retrieves SmoothShadingStyle information from a paint field.
     @param paintField The paint field.
     @param outSmoothStyle [out] A buffer in which to return the SmoothShadingStyle style.
     */
    
    AIAPI AIErr (*GetSmoothShadingStyle)(AIParserPaintField paintField, AISmoothShadingStylePtr &outSmoothStyle);
    
    /**
     Clone all the effect from fromPaintField field to toPaintField. All existing effects on toPaintField will be lost.
     @param parser : The parser.
     @param fromPaintField : Source paint field from which effects should be applied.
     @param toPaintField : Destination paint field on which effects will be applied.
     **/
    AIAPI AIErr (*CloneEffectsList) (AIStyleParser parser, AIParserPaintField &fromPaintField, AIParserPaintField &toPaintField);
    
    /** Sets SmoothShadingStyle information for a paint field.
     @param paintField The paint field.
     @param inSmoothShadingStyle: The new smooths shading style.
	 @returns error if paintField kind is not smooth shading.
     */
    AIAPI AIErr (*SetSmoothShadingStyle) (AIParserPaintField paintField, AISmoothShadingStylePtr inSmoothShadingStyle);
};


#include "AIHeaderEnd.h"


#endif
