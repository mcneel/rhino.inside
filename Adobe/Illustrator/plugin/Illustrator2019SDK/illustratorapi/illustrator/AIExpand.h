/*
 *
 *	AIExpand.h
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1995-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#ifndef __ExpandSuite__
#define __ExpandSuite__

/** @file AIExpand.h */

/* Imports */

#include "AIArt.h"


/* Constants */

#define kAIExpandSuite			"AI Expand Suite"
#define kAI70ExpandSuite		kAIExpandSuite
#define kAIExpandSuiteVersion4	AIAPI_VERSION(4)
#define kAI70ExpandSuiteVersion	AIAPI_VERSION(1)

/* Latest version */
#define kAIExpandSuiteVersion	kAIExpandSuiteVersion4
#define kAIExpandVersion		kAIExpandSuiteVersion

/** Flag values for what should be expanded and how the operation
	is performed. The order of priority for expansion is as
	follows:
	\verbatim
	#kExpandPluginArt
	#kExpandSymbolInstances
	#kExpandText
	\endverbatim
	If any of these flags causes an expansion, the operation stops
	there. For example, if you call \c #AIExpandSuite::Expand() on
	a text object inside a symbol instance, with options
	\c #kExpandSymbolInstances and \c #kExpandText set,
	the symbol is expanded, but the text object is not.

	Otherwise, the expansion continues with the following
	priority:
	\verbatim
	#kExpandStroke
	#kExpandPattern
	#kExpandGradientToMesh
	#kExpandGradientToPaths
	\endverbatim

	These expansions can all occur in one call, unless
	\c #kExpandOneAtATime is set. In this case, the expansion
	operation stops as soon as any expansion occurs.
	*/
enum AIExpandFlagValue {
	/** Expand plug-in art */
	kExpandPluginArt		= 0x0001,
	/** Expand text  */
	kExpandText				= 0x0002,
	/** Expand strokes */
	kExpandStroke			= 0x0004,
	/** Expand patterns */
	kExpandPattern			= 0x0008,
	/** Expand gradient as a mesh */
	kExpandGradientToMesh	= 0x0010,
	/** Expand gradient as a path */
	kExpandGradientToPaths	= 0x0020,
	/** Expand symbols */
	kExpandSymbolInstances	= 0x0040,
	/** Expand charts */
	kExpandChartArt			= 0x0080,
	 /** Stop the expansion operation after the first expansion occurs. */
	kExpandOneAtATime		= 0x4000,
	/** Show a progress bar during the operation. */
	kExpandShowProgress		= 0x8000,
	/** Expand locked objects (such as those on a locked layer).
		By default, modifications are not made on objects in locked layers.*/
	kExpandLockedObjects	= 0x10000
};

/* Suite */

/** @ingroup Suites
	This suite provides a legacy version of a single function that
	expands an art object into a set of objects with equivalent appearance.
	The current version is in \c #AIExpandSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAI70ExpandSuite and \c #kAI70ExpandSuiteVersion.
	*/
typedef struct {
	 /** Breaks artwork up into individual parts, creating a set of objects
	 	with equivalent appearance. This is the same as calling the newer
	 	\c #AIExpandSuite::Expand() with the flags \c #kExpandPattern and
	 	\c #kExpandGradientToPaths.
	 		@param art The art object.
	 			\li For path art with a fill of CMYK or RGB color, has no effect.
	 			\li For artwork filled with a gradient, breaks the artwork up into
	 				\c steps number of objects between each of the gradients stops.
	 				The resulting artwork contains a mask.
	 			\li For text art, turns the text into outlines.
	 			\li For stroked objects, outlines the stroke and creates a closed path.
	 				This is especially useful for art objects created using brushes.
	 			\li For objects filled with a pattern, draws the entire pattern tile
	 				on the page with the original object acting as a mask.
	 		@param steps For artwork filled with a gradient, the number of objects to
	 			create between gradient stops. For example an artwork with four stops
	 			and a \c steps value of 2 results in an artwork that has two steps
	 			between each of the four stops.
			@see \c #AIExpandSuite::Expand() for a version with additional options.
		*/
	AIAPI AIErr (*Expand)( AIArtHandle art, ai::int32 steps );

} AI70ExpandSuite;

/** @ingroup Suites
	This suite provides a single function that expands an art object
	into a set of objects with equivalent appearance. For backward
	compatibility, an older version is provided in \c #AI70ExpandSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIExpandSuite and \c #kAIExpandSuiteVersion.
	*/
typedef struct {

	/** Breaks artwork up into individual parts, creating a set of objects
		with equivalent appearance. It is the same as choosing Expand from
		the Object menu.
			\li For path art with a fill of CMYK or RGB color, has no effect.
			\li For artwork filled with a gradient, breaks the artwork up into
				\c steps number of objects between each of the gradients stops.
				The resulting artwork contains a mask.
			\li For text art, turns the text into outlines.
			\li For stroked objects, outlines the stroke and creates a closed path.
				This is especially useful for art objects created using brushes.
			\li For objects filled with a pattern, draws the entire pattern tile
				on the page with the original object acting as a mask.

			@param art The art object.
			@param flags Options that control how the expansion is done. A logical
				OR of \c #AIExpandFlagValue values.
			@param steps For artwork filled with a gradient, the number of objects to
				create between gradient stops. For example an artwork with four stops
				and a \c steps value of 2 results in an artwork that has two steps
				between each of the four stops.
		*/
	AIAPI AIErr (*Expand)( AIArtHandle art, ai::int32 flags, ai::int32 steps );

} AIExpandSuite;


#endif // __ExpandSuite__

