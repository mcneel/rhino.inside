#ifndef __AITextFrame__
#define __AITextFrame__

/*
 *        Name:	AITextFrame.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Text Frame Object Suite.
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

#ifndef __AIFONT__
#include "AIFont.h"
#endif

#ifndef __AIHitTest__
#include "AIHitTest.h"
#endif

#ifndef __ATESuites__
#include "ATESuites.h"
#endif

#ifdef __cplusplus
using ATE::TextRangesRef;
using ATE::TextRangeRef;
using ATE::TextFrameRef;
#endif

#include "AIHeaderBegin.h"

/** @file AITextFrame.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAITextFrameSuite			"AI Text Frame Suite"

#define kAITextFrameSuiteVersion4	AIAPI_VERSION(4)
#define kAITextFrameSuiteVersion	kAITextFrameSuiteVersion4
#define kAITextFrameVersion			kAITextFrameSuiteVersion

#define kAITextFrameMESuite			"AI Text Frame ME Suite"
#define kAITextFrameMESuiteVersion3	AIAPI_VERSION(3)
#define kAITextFrameMESuiteVersion	kAITextFrameMESuiteVersion3
#define kAITextFrameMEVersion 		kAITextFrameMESuiteVersion


#define kAITextFrameVersion			kAITextFrameSuiteVersion

#define kAITextFrameHitSuite			"AI Text Frame Hit Suite"
#define kAITextFrameHitSuiteVersion2	AIAPI_VERSION(2)
#define kAITextFrameHitSuiteVersion		kAITextFrameHitSuiteVersion2
#define kAITextFrameHitVersion			kAITextFrameHitSuiteVersion

/** Types of text frames. See \c #AITextFrameSuite. */
typedef enum {
	kUnknownTextType = -1,
	/** Point text, defined by an anchor point for the position
		of the first character. */
	kPointTextType,
	/** In-path text, an associated path object defines the area
		the text flows into.  */
	kInPathTextType,
	/** On-path text, an associated path object defines the area
		the text flows along. */
	kOnPathTextType
} AITextType;

/** An opaque reference to a text frame.  See \c #AITextFrameSuite.	 */
typedef AITextType		AITextFrameType;

/** Text direction constants. See \c #AITextFrameMESuite. */
enum AITextDirection{
	kAITextLeftToRightDirection,
	kAITextRightToLeftDirection
};

/** Parts of a text object that can be hit. See \c #AITextFrameHitSuite. */
enum AITextPart {
	kAITextNowhere				= 0,
	/** Direct hit on text */
	kAITextText					= 1,
	/** Hit on "in" port of either in-path or on-path text. */
	kAITextInport				= 2,
	/** Hit on "out" port of either in-path or on-path text. */
	kAITextOutPort				= 3,
	/** Hit on start point of on-path text. */
	kAITextStart				= 4,
	/** Hit on middle point of on-path text. */
	kAITextMiddle				= 5,
	/** Hit on end point of OnPath text. */
	kAITextEnd					= 6
};

/** Types of Text Antialiasing available. See \c #AITextFrameHitSuite. */
enum TextAntialiasingAvailableTypes
{
	kTextAntialiasingInvalid = 0,
	kTextAntialiasingNone,
	kTextAntialiasingSharp,
	kTextAntialiasingCrisp,
	kTextAntialiasingStrong
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that manage art objects of
	type \c #kTextFrameArt.	Introduced in Illustrator 11.

	There are three types of text frames; \e point
	text, \e in-path text, and \e on-path text.

	\li Point text is defined by an anchor point for the position
		of the first character.
	\li In-path and on-path text have an associated path object
		that defines the area the text flows into or along. respectively.

	In-path and on-path text frames can be linked together. Linked text frames
	need not be the same type. They can be in different groups, and can be on
	different layers. The text content linked frames is called a \e story.
	Use the Adobe Text Engine (ATE) functions to access and manipulate
	the story and its visual attributes. Related suites include:
	<br> \c #AIATECurrentTextFeaturesSuite
	<br> \c #AIATEPaintSuite
	<br> \c #AIATETextUtilSuite
	<br> \c #AITextFrameHitSuite

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITextFrameSuite and \c #kAITextFrameVersion.
 */
typedef struct {

	/** Creates a new point text object at a given position in the paint order.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param anchor The start point of the baseline of the first character.
			@param newTextFrame [out] A buffer in which to return the new art object.
 		*/
	AIAPI AIErr (*NewPointText)		( ai::int16 paintOrder, AIArtHandle prep, AITextOrientation orient,
									AIRealPoint anchor, AIArtHandle *newTextFrame );
	/** Creates a new in-path text object at a given position in the paint order.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param path The associated path object (an art object of type \c #kPathArt).
			@param baseFrame Optional. Another text frame with which to link the new text frame.
			@param append When true, append the new frame to the base frame, when false, prepend it.
				Ignored if \c baseFrame is \c NULL.
			@param newTextFrame [out] A buffer in which to return the new art object.
		 */
	AIAPI AIErr (*NewInPathText)	( ai::int16 paintOrder, AIArtHandle prep, AITextOrientation orient,
									AIArtHandle path, AIArtHandle baseFrame, AIBool8 append, AIArtHandle *newTextFrame );

	/** Creates a new on-path text object at a given position in the paint order, placing
		the text with a starting and ending path segment.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param path The associated path object (an art object of type \c #kPathArt).
			@param startT The 0-based index of the segment of the path at which the text starts.
			@param endT	The 0-based index of the segment of the path at which the text ends. If less
				than the start value, defaults to the number of segments (the end of the path).
			@param baseFrame Optional. Another text frame with which to link the new text frame.
			@param append When true, append the new frame to the base frame, when false, prepend it.
				Ignored if \c baseFrame is \c NULL.
			@param newTextFrame [out] A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*NewOnPathText)	( ai::int16 paintOrder, AIArtHandle prep, AITextOrientation orient,
									AIArtHandle path, AIReal startT, AIReal endT, AIArtHandle baseFrame,
									AIBool8 append, AIArtHandle *newTextFrame );

	/** Creates a new on-path text object at a given position in the paint order, placing
		the text with an anchor point.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param path The associated path object (an art object of type \c #kPathArt).
			@param anchor The start point of the baseline of the first character.
			@param baseFrame Optional. Another text frame with which to link the new text frame.
			@param append When true, append the new frame to the base frame, when false, prepend it.
				Ignored if \c baseFrame is \c NULL.
			@param newTextFrame [out] A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*NewOnPathText2)	( ai::int16 paintOrder, AIArtHandle prep, AITextOrientation orient,
									AIArtHandle path, AIRealPoint anchor, AIArtHandle baseFrame,
									AIBool8 append, AIArtHandle *newTextFrame );

	/** Retrieves the type of a text frame.
			@param textFrame The text frame object.
			@param type [out] A buffer in which to return the type.
		*/
	AIAPI AIErr (*GetType)			( AIArtHandle textFrame, AITextFrameType *type );

	/** Retrieves the orientation of a text frame.
			@param textFrame The text frame object.
			@param orient [out] A buffer in which to return the orientation value.
		 */
	AIAPI AIErr (*GetOrientation)	( AIArtHandle textFrame, AITextOrientation *orient );

	/** Sets the orientation of a text frame.
			@param textFrame The text frame object.
			@param orient The new orientation value.
		 */
	AIAPI AIErr (*SetOrientation)	( AIArtHandle textFrame, AITextOrientation orient );

	/** Retrieves the Antialiasing option of a text frame.
	@param textFrame The text frame object.
	@param tAntialias [out] A buffer in which to return the Antialiasing options.
	*/
	AIAPI AIErr (*GetTextAntialias)	( AIArtHandle textFrame, TextAntialiasingAvailableTypes *tAntialias );

	/** Sets the Antialiasing option of a text frame.
	@param textFrame The text frame object.
	@param tAntialias The new Antialiasing option.
	*/
	AIAPI AIErr (*SetTextAntialias)	( AIArtHandle textFrame, TextAntialiasingAvailableTypes tAntialias );

	/** Retrieves the anchor point of a point-text text frame.
		Use the \c #AITransformArtSuite to change the anchor point.
			@param textFrame The text frame object.
			@param anchor [out] A buffer in which to return the anchor point.
			@return The error \c #kBadParameterErr if the text frame is not a point-text type.
		  */
	AIAPI AIErr (*GetPointTextAnchor)( AIArtHandle textFrame, AIRealPoint *anchor );

	/**	Retrieves the path associated with an in-path or on-path text range.
		Use the \c #AIPathSuite to access and manipulate the path.
			@param textFrame The text frame object.
			@param pathObject [out] A buffer in which to return the path object, or
				\c NULL if the text frame is a point-text type.

		@note You can use \c #AIArtSuite::DuplicateArt() copy the path object,
			but you cannot specify the target location in terms of the returned path object.
			For example, you cannot place the duplicate  path above or below the source path.
		*/
	AIAPI AIErr (*GetPathObject)	( AIArtHandle textFrame, AIArtHandle *pathObject );

	/**  Retrieves the starting and ending path segments of an on-path text range.
			@param textFrame The text frame object.
			@param startT [out] A buffer in which to return the 0-based index of
				the starting segment.
			@param endT [out] A buffer in which to return the 0-based index of
				the ending segment. It is always greater than or equal to the starting
				segment's index.
		*/
	AIAPI AIErr (*GetOnPathTextTRange)( AIArtHandle textFrame, AIReal *startT, AIReal *endT );

	/**  Sets the starting and ending path segments of an on-path text range.
			@param textFrame The text frame object.
			@param startT The 0-based index of the starting segment.
			@param endT The 0-based index of the ending segment. Must be
				greater than or equal to the starting segment's index.
		*/
	AIAPI AIErr (*SetOnPathTextTRange)( AIArtHandle textFrame, AIReal startT, AIReal endT );

	/** Retrieves the ATE text range object for the text contained in an Illustrator text frame.
			@param textFrame The text frame object.
			@param textRange [out] A buffer in which to return the text range object.
				This object is reference counted. You must release it when it is no
				longer needed, using the \c #ATE::ITextRange class
		 	@note If this frame is the last one in the chain AND it has overflow text,
		 		\c ITextRange(textRange).getEnd() includes the hidden text.
		 */
	AIAPI AIErr (*GetATETextRange)	( AIArtHandle textFrame, TextRangeRef*	textRange );

	/** Retrieves the ATE text frame object corresponding to an Illustrator text frame object.
			@param textFrame The text frame object.
			@param ATE_textFrame [out] A buffer in which to return the ATE text frame object.
				This object is reference counted. You must release it when it is no
				longer needed, using the \c #ATE::ITextFrame class
		*/
	AIAPI AIErr (*GetATETextFrame)	( AIArtHandle textFrame, TextFrameRef*	ATE_textFrame );

	/** Retrieves the Illustrator text frame object corresponding to an ATE text frame object.
			@param ATE_textFrame  The ATE text frame object.
			@param textFrame [out] A buffer in which to return the Illustrator text frame object.
	*/
	AIAPI AIErr (*GetAITextFrame)	( TextFrameRef	ATE_textFrame, AIArtHandle* textFrame );

	/** Retrieves the ATE text range object for the selected text contained in an
		Illustrator text frame.	 Selections can be discontiguous.
			@param textFrame The text frame object.
			@param textRange [out] A buffer in which to return the text range object.
				This object is reference counted. You must release it when it is no
				longer needed, using the \c #ATE::ITextRange class
		*/
	AIAPI AIErr (*GetATETextSelection)( AIArtHandle textFrame, TextRangesRef*	Selection );

	/** Retrieves the ATE text range object for the insertion point that corresponds
		to a hit on a text frame object, as obtained with the \c #AIHitTestSuite.
			@param hitRef The hit object.
			@param textRange [out] A buffer in which to return the text range object.
				This object is reference counted. You must release it when it is no
				longer needed, using the \c #ATE::ITextRange class
		*/
	AIAPI AIErr (*DoTextFrameHit)	( const AIHitRef hitRef, TextRangeRef*	textRange );

	/** Converts the text in a text frame object to outlines in a new art object.
		If the text frame has an active style, that style is applied to the outlines.
		Other attributes, including the opacity mask. are not copied. If the text frame
		is set to clip, a single clipping compound path is created to contain the outlines.
		The style and opacity mask are not applied to this compound path.
			@param textFrame The text frame object. This object is not deleted.
			@param outline [out] A buffer in which to return the new outline text.
		*/
	AIAPI AIErr (*CreateOutline)	( AIArtHandle textFrame, AIArtHandle *outline );

	/** Links two in-path text frame objects. Upon return, they share the same story.
			@param baseFrame The first in-path text frame object.
			@param nextFrame The second in-path text frame object.
		*/
	AIAPI AIErr (*Link)				( AIArtHandle baseFrame, AIArtHandle nextFrame );

	/** Unlinks a text frame object from its current story, or breaks the story
		into two parts before or after a given frame.
			@param frame The text frame object.
			@param before When true, if \c after is false, break the story into two
				groups before this frame, so that the second part starts
				with this frame.
			@param after  When true, if \c before is false, break the story into two
				groups after this frame, so that the first part ends
				with this frame.

			\li If both \c before and \c after are true, the frame is removed from the
					story.
			\li If both \c before and \c after are false, nothing happens.
	 	*/
	AIAPI AIErr (*Unlink)			( AIArtHandle frame, AIBool8 before, AIBool8 after );

	/** Creates a new Illustrator text frame object based on ATE version 2 blob data.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param data	A pointer to a binary blob.
			@param size The number of bytes in the data block.
			@param index The 0-based position index of the new text object
				in the SLO TextObject list.
		*/
	AIAPI AIErr (*CreateATEV2Text)	( ai::int16 paintOrder, AIArtHandle prep, void* data,
		size_t size, ai::int32 index, AIArtHandle *newTextFrame );

	/** Retrieves the ATE version 2 blob data for the current artwork.
			@param data	[out] A buffer in which to return the binary blob. You must
				free this data using \c #SPBlocksSuite::SPFreeBlock().
			@param size [out]] A buffer in which to return the number of bytes in the data block.
		*/
	AIAPI AIErr (*GetATEV2Data)		( void** data, size_t* size );

	/** Retrieves the story index of a text frame.
			@param frame The text frame object.
			@param index The 0-based index, or -1 if the frame does not belong
				to the current artwork or is part of the result art of a
				plug-in group or styled art.
		*/
	AIAPI AIErr (*GetStoryIndex)	( AIArtHandle frame, ai::int32* index );

	/** Retrieves the frame index of a linked text frame in its story.
			@param frame The text frame object.
			@param index The 0-based index, or -1 if the frame does not belong
				to the current artwork or is part of the result art of a
				plug-in group or styled art.
		*/
	AIAPI AIErr (*GetFrameIndex)	( AIArtHandle frame, ai::int32* index );

	/** Reports whether a text frame is part of a linked text story.
			@param frame The text frame object.
			@param linked [out] A buffer in which to return true if the text frame is linked.
		*/
	AIAPI AIErr (*PartOfLinkedText)	( AIArtHandle frame, AIBool8* linked );
} AITextFrameSuite;


/** @ingroup Suites

	This suite is used in conjunction with \c #AITextFrameSuite.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITextFrameMESuite and \c #kAITextFrameMEVersion.
 */
typedef struct {

	/** Retrieves the orientation of text in a text frame (left-to-right or right-to-left).
		@param textFrame The text freme object.
		@parem dir [out] A buffer in which to return the text-direction constant.
	*/
	AIAPI AIErr (*GetDirection)	( AIArtHandle textFrame, AITextDirection *dir );

	/** Sets the orientation of text in a text frame (left-to-right or right-to-left).
		@param textFrame The text freme object.
		@parem dir The text-direction constant.
	*/
	AIAPI AIErr (*SetDirection)	( AIArtHandle textFrame, AITextDirection dir );

	/** Creates a new point text object at a given position in the paint order.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param anchor The start point of the baseline of the first character.
			@param newTextFrame [out] A buffer in which to return the new art object.
 		*/
	AIAPI AIErr (*NewPointTextME)		( short paintOrder, AIArtHandle prep, AITextOrientation orient,AITextDirection dir, AIRealPoint anchor, AIArtHandle *newTextFrame );

	/** Creates a new in-path text object at a given position in the paint order.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param path The associated path object (an art object of type \c #kPathArt).
			@param baseFrame Optional. Another text frame with which to link the new text frame.
			@param append When true, append the new frame to the base frame, when false, prepend it.
				Ignored if \c baseFrame is \c NULL.
			@param newTextFrame [out] A buffer in which to return the new art object.
		 */
	AIAPI AIErr (*NewInPathTextME)	( short paintOrder, AIArtHandle prep, AITextOrientation orient, AITextDirection dir, AIArtHandle path, AIArtHandle baseFrame, AIBool8 append, AIArtHandle *newTextFrame );

	/** Creates a new on-path text object at a given position in the paint order, placing
		the text with a starting and ending path segment.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param path The associated path object (an art object of type \c #kPathArt).
			@param startT The 0-based index of the segment of the path at which the text starts.
			@param endT	The 0-based index of the segment of the path at which the text ends. If less
				than the start value, defaults to the number of segments (the end of the path).
			@param baseFrame Optional. Another text frame with which to link the new text frame.
			@param append When true, append the new frame to the base frame, when false, prepend it.
				Ignored if \c baseFrame is \c NULL.
			@param newTextFrame [out] A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*NewOnPathTextME)	( short paintOrder, AIArtHandle prep, AITextOrientation orient, AITextDirection dir, AIArtHandle path, AIReal startT, AIReal endT, AIArtHandle baseFrame, AIBool8 append, AIArtHandle *newTextFrame );

	/** Creates a new on-path text object at a given position in the paint order, placing
		the text with an anchor point.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param orient The text orientation value.
			@param path The associated path object (an art object of type \c #kPathArt).
			@param anchor The start point of the baseline of the first character.
			@param baseFrame Optional. Another text frame with which to link the new text frame.
			@param append When true, append the new frame to the base frame, when false, prepend it.
				Ignored if \c baseFrame is \c NULL.
			@param newTextFrame [out] A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*NewOnPathText2ME)	( short paintOrder, AIArtHandle prep, AITextOrientation orient, AITextDirection dir, AIArtHandle path, AIRealPoint anchor, AIArtHandle baseFrame, AIBool8 append, AIArtHandle *newTextFrame );

	/**

	*/
	AIAPI AIErr (*FullReflow)	( AIArtHandle newTextFrame );

} AITextFrameMESuite;


/** @ingroup Suites

	This suite is used in conjunction with \c #AIHitTestSuite and \c #AITextFrameSuite.
	When the \c #AIHitTestSuite returns a hit reference that identifies a hit
	on a text frame, use this function to further interrogate the hit.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITextFrameHitSuite and \c #kAITextFrameHitVersion.
 */
typedef struct {

	/** Reports	which element of a text frame was hit.
		(Note that this function returns a constant value, not an error code.)
			@param The hit reference.
			@return An \c #AITextPart value. */
	AIAPI ai::int32 (*GetPart) (AIHitRef hit);

} AITextFrameHitSuite;


#include "AIHeaderEnd.h"


#endif
