/*
 *
 *	AIArtConverter.h
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2002-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#ifndef __ArtConverterSuite__
#define __ArtConverterSuite__


/* Imports */

#include "AIArt.h"


#include "AIHeaderBegin.h"


/* Constants */

#define kAIArtConverterSuite			"AI Art Converter Suite"
#define kAIArtConverterSuiteVersion3	AIAPI_VERSION(3)
#define kAIArtConverterSuiteVersion		kAIArtConverterSuiteVersion3
#define kAIArtConverterVersion			kAIArtConverterSuiteVersion

/** Option bit flags that control how the "footprint" of a path is treated
	when converting to outlines. See \c #AIArtConverterSuite, \c #AISymbolSuite. */
enum {
	/** Expands source art before converting to outlines. */
	kOutlineExpandAppearance		= 0x0001,
	/** Strips paths with no fill and no stroke before converting to outlines. */
	kOutlineEliminateUnpainted		= 0x0002,
	/** Adds strokes when converting to outlines; see \c #kOutlineAlwaysIncludeFillArea. */
	kOutlineAddStrokes				= 0x0004,
	/** Subtracts strokes when converting to outlines; see \c #kOutlineAlwaysIncludeFillArea.*/
	kOutlineSubtractStrokes			= 0x0008,
	/** Controls how the inner fillable area of unfilled but
		stroked paths is combined with the stroke area, if either
		\c #kOutlineAddStrokes or \c #kOutlineSubtractStrokes
		is set.

		For example, assume an original path of a closed figure that
		contains another closed figure, which in turn contains another
		closed figure, with no fill and wide stroke:

		@verbatim
		+-------+
 		|+-----+|
 		||+---+||
 		|||   |||
 		||+---+||
 		|+-----+|
 		+-------+
 		@endverbatim

 		With \c #kOutlineAlwaysIncludeFillArea set, but both stroke flags off,
 		stroke is ignored and the outline is that of the fillable area:
		@verbatim
 		 +-----+
 		 |     |
 		 |     |
 		 |     |
 		 +-----+
 		@endverbatim

        \c #kOutlineAddStrokes only creates a filled compound path with a hole in the middle:
 		@verbatim
		+-------+
 		|       |
 		| +---+ |
 		| |   | |
 		| +---+ |
 		|       |
 		+-------+
  		@endverbatim

        With both \c #kOutlineAddStrokes and \c #kOutlineAlwaysIncludeFillArea set, the
        fill area is added to the stroke area:
 		@verbatim
		+-------+
 		|       |
 		|       |
 		|       |
 		|       |
 		|       |
 		+-------+
  		@endverbatim

        With both \c #kOutlineSubtractStrokes and \c #kOutlineAlwaysIncludeFillArea set,
        the fill area is added, and the stroke area is subtracted:
		@verbatim
 		  +---+
 		  |   |
 		  +---+
  		@endverbatim

		This can be used to get the inner region of a path, the part that would show in the fill color
 		if it were filled.

 		With \c #kOutlineSubtractStrokes only, the inner-area path is created on paths that are both filled and stroked,
 		but paths that are stroked only are either stripped (if \c #kOutlineEliminateUnpainted is on)
 		or left alone (if it is off).		*/
	kOutlineAlwaysIncludeFillArea	= 0x0010,
	/** If input art includes straight lines (which have no area and would be
		excluded by Pathfinder even if they have a fill), they are given a
		hair-line stroke so that they will be included in the union. Use only when
		\c #kOutlineAddStrokes is set.

		The addition of a stroke happens after the test for unpainted paths, so if
		\c #kOutlineEliminateUnpainted is set, it happens only to straight line segments
		that have a fill but no stroke and does not prevent the elimination of completely
		unpainted line segments. If \c #kOutlineEliminateUnpainted is off, it also
		happens to unpainted straight line segments. */
	kOutlineAlwaysStrokeStraightLines	= 0x0020
};

/** How strokes are expanded while creating outlines; see \c #kOutlineAlwaysIncludeFillArea. */
#define kOutlineExpandStrokes (kOutlineAddStrokes|kOutlineSubtractStrokes)


/** @ingroup Suites
	This suite allows you to convert art to paths or outlines.
	@see \c #AISymbolSuite::CopySymbolPatternOutline(),
		 \c #AISymbolSuite::InsertSymbolArtOutline(),
		 \c #AISymbolSuite::PeekCachedPatternOutline()

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIArtConverterSuite and \c #kAIArtConverterVersion.
*/

typedef struct {

	/** Converts artwork to a path, a compound path, or a group of paths and compound paths.
		This function does not combine multiple paths.
			@param art The art object. This object is deleted, and the new object or objects
				are inserted into the art tree in its place.
		*/
	AIAPI AIErr (*ArtConvertToPaths)( AIArtHandle *art );

	/**	Creates a new path or compound path that is an outline of the given artwork, and
		inserts it into the artwork tree at a given location.  Combines multiple paths into
		a single path or compound path.	Some of the style is ignored (only the shape is important
		to the outline), but the art style of the result object is generally derived from that of
		the top element, possibly modified by stroke expansion, depending on the options.
			@param art The art object.
			@param paintOrder The paint order position, relative to the \c destination object,
				an \c #AITypes::AIPaintOrder value.
			@param destination The prepositional art object for the paint order.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values:
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
			@param outlineArt Optional, a buffer in which to return the new path art object.
   		*/
	AIAPI AIErr (*GetOutlineArt) ( AIArtHandle art, ai::int16 paintOrder, AIArtHandle destination,
									ai::int32 options, AIArtHandle *outlineArt );

	/**	Converts a given art object in place to a single path or compound path, disposing of the original
		art object. Resulting single path or compound path will be placed at the same position in the art
		tree as of original art object. Some of the style is ignored (only the shape is important
		to the outline), but the art style of the result object is generally derived from that of
		the top element, possibly modified by stroke expansion, depending on the options. Use this method
		instead of GetOutlineArt when original art object needs to be replaced by outlined art object.
			@param art The art object.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
		*/
	AIAPI AIErr (*ArtConvertToOutline) ( AIArtHandle *art, ai::int32 options );

} AIArtConverterSuite;


#include "AIHeaderEnd.h"

#endif // __ArtConverterSuite__

