#ifndef __AIGrid__
#define __AIGrid__

/*
 *        Name:	AIGrid.h
 *   $Revision: 13 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Grid Suite.
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
#ifndef __AIDocumentView__
#include "AIDocumentView.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIGrid.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/
/** Grid suite name */
#define kAIGridSuite			"AI Grid Suite"
/** Grid suite version */
#define kAIGridSuiteVersion5	AIAPI_VERSION(5)
/** Grid suite version */
#define kAIGridSuiteVersion		kAIGridSuiteVersion5
/** Grid suite version */
#define kAIGridVersion			kAIGridSuiteVersion


/** Grid styles, graph or dotted. */
enum {
	/** The grid is shown as graph lines. */
	kAIGridStyleGraph = 0,
	/** The grid is shown as dots at intersection points. */
	kAIGridStyleDotted
};


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Grid spacing information. */
typedef struct {
	/** Major grid increments, in points. */
	AIFloat				spacing;
	/** Minor grid increments. The number of steps (subdivisions)
		per major increment. */
	ai::int32				ticks;
} AIGridSpacing;

/** Grid settings information. See \c #AIGridSuite::SetGridSettings(),
	\c #AIGridSuite::GetGridSettings().*/
typedef struct {
	/** When true, draw grid behind art. */
	AIBoolean			isinback;
	/** Grid drawing style, \c #kAIGridStyleGraph or
		\c #kAIGridStyleDotted */
	ai::int32				style;
	/** Grid spacing information. */
	AIGridSpacing		spacing;
	/** Color for heavy lines. */
	AIRGBColor			darkcolor;
	/** Color for light lines. */
	AIRGBColor			litecolor;
} AIGridSettings;

/** Callback prototype for  \c #AIGridSuite::EnumGridLines(), which iterates over
	the grid lines that intersect a given rectangle.
		@param data The developer-defined data passed to the enumeration function.
		@param p0  The first point at which the current grid line intersects
			the rectangle.
		@param p1 The second point at which the current grid line intersects
			the rectangle.
	*/
typedef ASErr ASAPI (*AIGridLineProc)	(void* data,
										AIRealPoint p0,
										AIRealPoint p1);

/** Callback prototype for  \c #AIGridSuite::EnumPageLines(), which iterates over
	the page tile lines that intersect a given rectangle.
		@param data The developer-defined data passed to the enumeration function.
		@param p0  The first point at which the current page tile line intersects
			the rectangle.
		@param p1 The second point at which the current page tile line intersects
			the rectangle.
	*/
typedef ASErr ASAPI (*AIPageLineProc)	(void* data,
										AIRealPoint p0,
										AIRealPoint p1);


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite allows you to access the grid settings for the current document.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIGridSuite and \c #kAIGridVersion.
	*/
typedef struct {

	/** Retrieves the grid settings for the current document.
			@param settings [out] A buffer in which to return the settings.
		*/
	AIAPI AIErr (*GetGridSettings)		(AIGridSettings* settings);
	/** Sets the grid settings for the current document.
			@param settings A pointer to a structure that you have filled
				with the new settings..
		*/
	AIAPI AIErr (*SetGridSettings) 		(AIGridSettings* settings);

	/** Enumerates the grid lines that intersect a specified rectangle to the
		callback function that you provide.
			@param view The document view.
			@param rect A pointer to the rectangle of interest.
			@param proc The callback procedure you have defined.
			@param data Developer-defined data that is passed through to the callback.
		*/
	AIAPI AIErr	(*EnumGridLines)		(AIDocumentViewHandle view,
										AIRealRect *rect,
										AIGridLineProc proc,
										void* data);

	/** Enumerates the page tile lines that intersect a specified rectangle to the
		callback function that you provide.
			@param view The document view.
			@param rect A pointer to the rectangle of interest.
			@param proc The callback procedure you have defined.
			@param data Developer-defined data that is passed through to the callback.
		*/
	AIAPI AIErr	(*EnumPageLines)		(AIDocumentViewHandle view,
										AIRealRect *rect,
										AIPageLineProc proc,
										void* data);

	/** Reports whether the grid is visible in a document view.
		(Note that this function returns a boolean value, not an error code.)
			@param view The document view.
			@return True if the grid is visible.
		 */
	AIAPI AIBoolean (*IsVisible)		(AIDocumentViewHandle view);

	/** Reports whether snap-to-grid is turned on in a document view.
		(Note that this function returns a boolean value, not an error code.)

		@param view The document view.
		@return True if snap-to-grid is on. 
		*/
	AIAPI AIBoolean (*IsSnapOn)			(AIDocumentViewHandle view);

} AIGridSuite;


#include "AIHeaderEnd.h"


#endif
