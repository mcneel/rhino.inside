#pragma once

/*************************************************************************
 * ADOBE CONFIDENTIAL
 *
 *  Copyright 2018 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by all applicable intellectual property
 * laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/


/*******************************************************************************
**
**	Imports
**
**/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#include "AIDocumentView.h"
#include "AIFont.h"
#include "AIAGMTypes.h"

#include "AIHeaderBegin.h"

// This Windows macro obscures an API
#undef DrawText

/** @file AIAnnotatorDrawer.h */


/*******************************************************************************
**
** Constants
**
**/

#define kAIAnnotatorDrawerSuite				"AI Annotator Drawer Suite"
#define kAIAnnotatorDrawerSuiteVersion6		AIAPI_VERSION(6)
#define kAIAnnotatorDrawerSuiteVersion		kAIAnnotatorDrawerSuiteVersion6
#define kAIAnnotatorDrawerVersion			kAIAnnotatorDrawerSuiteVersion


/*******************************************************************************
**
** Types
**
**/

class AIAnnotatorDrawer;			// Opaque to suite clients

/**	A horizontal alignment value, such as that of text in annotations.
@see \c #AIAnnotatorDrawerSuite::DrawTextAligned()
*/
enum AIHorizAlignment
{
	kAILeft,						///< Align left
	kAICenter,						///< Align center
	kAIRight,						///< Align right
	kAIHorizDummy = 0xFFFFFFFF		///< Dummy value to ensure 32 bit enums
};

/**	A vertical alignment value, such as that of text in annotations.
@see \c #AIAnnotatorDrawerSuite::DrawTextAligned()
*/
enum AIVertAlignment
{
	kAITop,							///< Align top
	kAIMiddle,						///< Align middle
	kAIBottom,						///< Align bottom
	kAIVertDummy = 0xFFFFFFFF		///< Dummy value to ensure 32 bit enums
};

/** Preset font constants for drawing text into annotations.
@see \c #AIAnnotatorDrawerSuite::SetFontPreset()
*/
enum AIAnnotatorFont
{
	kAIAFSmall,						///< Small font
	kAIAFMedium,					///< Medium font
	kAIAFLarge,						///< Large font
	kAIAFDummy = 0xFFFFFFFF			///< Dummy value to ensure 32 bit enums
};

/**
Annotator drawing port option bit constants.
@see \c #AIAnnotatorDrawerSuite::SetPortOptions()
*/
enum AIAnnotatorPortOption
{
	kAIOptionAAGraphics = 0x1,		///< Enable antialiasing of all graphic paths including clips and images
	kDummyPortOption = 0x80000000	///< Dummy value to ensure 32 bit enums
};

/*******************************************************************************
**
**	Suite Record
**
**/

/** @ingroup Errors
	See \c #AIAnnotatorDrawerSuite */
#define kDashBufferTooShortError 'SHRT'
/** @ingroup Errors
	See \c #AIAnnotatorDrawerSuite */
#define kNoStrokeParamsError 'NPRM'
/** @ingroup Errors
	See \c #AIAnnotatorDrawerSuite */
#define kDashArrayTooBigError 'DBIG'
/** @ingroup Errors
	See \c #AIAnnotatorDrawerSuite */
#define kNoDashError 'NDSH'

/**	@ingroup Suites
The annotator drawer suite allows plug-ins to draw annotations into the
document window that are not a part of the artwork. Coordinates are in
document view space.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIAnnotatorDrawerSuite and \c #kAIAnnotatorDrawerVersion.
*/
struct AIAnnotatorDrawerSuite
{
	/// @name Color
	//@{
	/**
	Sets the drawing color for an annotation.
	Note that this function does not return an error code.
	@param drawer The annotation drawer object.
	@param color The new color.
	*/
	AIAPI void (*SetColor)(AIAnnotatorDrawer *drawer, const AIRGBColor &color);

	/**
	Retrieves the current drawing color for an annotation.
	Note that this function does not return an error code.
	@param drawer The annotation drawer object.
	@param color [out] A buffer in which to return the color.
	*/
	AIAPI void (*GetColor)(AIAnnotatorDrawer *drawer, AIRGBColor &color);
	//@}

	/// @name Lines and shapes
	//@{
	/** Sets the line width for an annotation.
	When not explicitly set, the line width is one document point.
	@param drawer The annotation drawer object.
	@param newWidth The new width in document points.
	*/
	AIAPI void (*SetLineWidth)(AIAnnotatorDrawer *drawer, const AIReal newWidth);
	/** Retrieves the line width for an annotation.
	Note that this function returns a numeric value, not an error code.
	@param drawer The annotation drawer object.
	@return The width in document points.
	*/
	AIAPI AIReal (*GetLineWidth)(AIAnnotatorDrawer *drawer);

	/** Turns dashed-line drawing on or off for an annotation.
	Note that this function does not return an error code.
	@param drawer The annotation drawer object.
	@param dashed True to turn dashed lines on, false to turn them off.
	@see SetLineDashedEx()
	*/
	AIAPI void (*SetLineDashed)(AIAnnotatorDrawer *drawer, AIBoolean dashed);
	/** Reports the current dashed-line drawing state for an annotation.
	Note that this function returns a Boolean value, not an error code.
	@param drawer The annotation drawer object.
	@return True if dashed lines are on, false if they are off.
	@see \c #GetLineDashedEx()
	*/
	AIAPI AIBoolean (*GetLineDashed)(AIAnnotatorDrawer *drawer);

	/** Draws a line between two points in an annotation.
	@param drawer The annotation drawer object.
	@param start The starting point.
	@param end The ending point.
	*/
	AIAPI AIErr (*DrawLine)(AIAnnotatorDrawer *drawer, const AIPoint &start, const AIPoint &end);
	/** Draws a rectangle in an annotation.
	@param drawer The annotation drawer object.
	@param rect The rectangle dimensions.
	@param fill True to fill with the current color, false for no fill.
	@see \c #SetColor()
	*/
	AIAPI AIErr (*DrawRect)(AIAnnotatorDrawer *drawer, const AIRect &rect, AIBoolean fill);

	/** Draws a polygon in an annotation by connecting a set of points.
	@param drawer The annotation drawer object.
	@param points The array of points to connect.
	@param numPoints The number of points in the array.
	@param fill True to fill with the current color, false for no fill.
	@see \c #SetColor()
	*/
	AIAPI AIErr (*DrawPolygon)(AIAnnotatorDrawer *drawer, const AIPoint points[], ai::uint32 numPoints, AIBoolean fill);

	/** Draws an ellipse bounded by the rectangle in an annotation.
	@param drawer The annotation drawer object.
	@param rect The rectangle dimensions.
	@param fill True to fill with the current color, false for no fill.
	@see \c #SetColor()
	*/
	AIAPI AIErr (*DrawEllipse)(AIAnnotatorDrawer *drawer, const AIRect &rect, AIBoolean fill);

	/** Draws cubic Bezier curves in an annotation by threading through a set of points.
	@param start [in] The starting anchor point for the curve
	@param pointSets [in] An array of sets of points describing the Bezier. The points in the
	inner array, p0, p1, and p2, have the following meaning:<br>
	p0	exit control point for the previous anchor<br>
	p1	entry control point for anchor<br>
	p2	anchor point<br>
	These are in the same order as for the PostScript CurveTo command.
	@param numPointSets [in] The number of sets of points in the array.
	@param fill True to fill with the current color, false for no fill.
	@see \c #SetColor()
	*/
	AIAPI AIErr (*DrawBezier)(AIAnnotatorDrawer *drawer, const AIPoint &start, const AIPoint pointSets[][3], ai::uint32 numPointSets, AIBoolean fill);

	/** Sets the dashing pattern for dashed-line drawing for an annotation.
	@param drawer The annotation drawer object.
	@param dashData The array of dash and gap lengths, in document points.
	@param numDashes The number of entries in the dash array, in the range [1 to 12].
	@see \c #SetLineDashed()
	*/

	AIAPI AIErr (*SetLineDashedEx)(AIAnnotatorDrawer *drawer, AIFloat dashData[], ai::int32 numDashes);

	/** Retrieves the dashing pattern for dashed-line drawing for an annotation.
	@param drawer The annotation drawer object.
	@param dashData [out] An array in which to return the dash and gap lengths, in document points.
	@param numDashes [out] A buffer in which to return the number of entries in the dash array, in the range [1 to 12].
	@see \c #GetLineDashed()
	*/
	AIAPI AIErr (*GetLineDashedEx)(AIAnnotatorDrawer *drawer, AIFloat dashData[], ai::int32 &numDashes);

	//@}

	/// @name Text and Fonts
	//@{
	/** Draws text into an annotation.
	@param drawer The annotation drawer object.
	@param text The text string.
	@param bottomLeft The point at which to place the bottom left corner of the text.
    @param allowScaling[in] Scale text drawing with respect to UI scaling
	*/
	AIAPI AIErr (*DrawText)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &text, const AIPoint &bottomLeft, AIBoolean allowScaling);

	/** Draws text into a rectangle in an annotation, with given alignment. The text does not wrap.
	@param drawer The annotation drawer object.
	@param text The text string.
	@param horizAlign The horizontal alignment of content.
	@param vertAlign The vertical alignment of content.
	@param rect The rectangle in which to draw.
    @param allowScaling[in] Scale text drawing with respect to UI scaling
	*/
	AIAPI AIErr (*DrawTextAligned)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &text, const AIHorizAlignment horizAlign, const AIVertAlignment vertAlign, const AIRect &rect, AIBoolean allowScaling);

	/**	Finds the bounds of text if it were drawn in the current font at the current size.
	@param drawer The annotation drawer object.
	@param text[in]	The text to be drawn.
	@param location [in] A location in document view coordinates, for a relative result. Default is [0,0].
	@param useFontFallback [in] Use system font if it is not possible to draw with current font.
	@param bounds [out]	A buffer in which to return the coordinates of the text boundary.
	If a location is not specified, top left is [0,0].
     @param allowScaling[in] returned Scaled text bound
	*/
	AIAPI AIErr (*GetTextBounds)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &text, AIPoint *location,  AIBoolean useFontFallback, AIRect &bounds, AIBoolean allowScaling);

	/** Sets the font size for text drawn into a annotation.
	@param drawer The annotation drawer object.
	@param size The new font size, in document points.
	*/
	AIAPI void (*SetFontSize)(AIAnnotatorDrawer *drawer, const AIReal size);

	/** Retrieves the font size for text drawn into a annotation.
	Note that this function returns a numeric value, not an error code.
	@param drawer The annotation drawer object.
	@return The current font size, in document points.
	*/
	AIAPI AIReal (*GetFontSize)(AIAnnotatorDrawer *drawer);

	/** Sets the font for text drawn into a annotation, using preset font sizes.
	@param drawer The annotation drawer object.
	@param font The new font preset constant.
	*/
	AIAPI AIErr (*SetFontPreset)(AIAnnotatorDrawer *drawer, AIAnnotatorFont font);

	/** Sets the font for text drawn into a annotation, using a font key.
	@param drawer The annotation drawer object.
	@param font The new font key.
	*/
	AIAPI AIErr (*SetFontByFontKey)(AIAnnotatorDrawer *drawer, AIFontKey font);

	/** Sets the font for text drawn into a annotation, by name.
	@param drawer The annotation drawer object.
	@param name The new font name. Interpreted as a PostScript font name; or,
	if none is found, a platform-encoded font name.

	*/
	AIAPI AIErr (*SetFontByName)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &name);

	/** Retrieves the font key for the current font used to draw
	text into an annotation.
	Note that this function returns a font-key object, not an error code.
	@param drawer The annotation drawer object.
	@return  The font key.
	*/
	AIAPI AIFontKey (*GetFontKey)(AIAnnotatorDrawer *drawer);

	/** Retrieves the name of the current font used to draw
	text into an annotation.
	Note that this function does not return an error code.
	@param drawer The annotation drawer object.
	@param name [out] A buffer in which to return the font name.
	*/
	AIAPI void (*GetFontName)(AIAnnotatorDrawer *drawer, ai::UnicodeString &name);
	//@}

	/// @name Clipping
	//@{

	/**	Starts the sequence for defining a clipping path in an annotation.
	Everything drawn until the call to \c #DefineClipEnd()
	is unioned into the clipping path, after which all drawing is clipped
	until the call to  \c #ClearClip().
	Shapes drawn for clipping should generally be filled.
	Note that this function does not return an error code.
	@param drawer The annotation drawer object.
	*/
	AIAPI void (*DefineClipStart)(AIAnnotatorDrawer *drawer);

	/**	Starts the sequence for defining a clipping path in an annotation.
	Subsequent drawing is clipped until the call to  \c #ClearClip().
	Note that this function does not return an error code.
	@param drawer The annotation drawer object.
	@see \c #DefineClipStart()
	*/
	AIAPI void (*DefineClipEnd)(AIAnnotatorDrawer *drawer);

	/** Ends clipping in an annotation and removes the currently defined clipping path.
	@param drawer The annotation drawer object.
	@see \c #DefineClipStart(),  \c #DefineClipEnd()
	*/
	AIAPI void (*ClearClip)(AIAnnotatorDrawer *drawer);
	//@}

	/// @name Miscellaneous
	//@{
	/** Turns highlight blending mode on or off in an annotation. It is off by default.
	This mode provides extra visibility, like XOR drawing,
	but it cannot be used to erase previous marks drawn in highlight mode.
	@param drawer The annotation drawer object.
	@param highlightOn True to turn highlight mode on, false to turn it off.
	*/
	AIAPI AIErr (*SetHighlightMode)(AIAnnotatorDrawer *drawer, AIBoolean highlightOn);

	/** Retrieves the current highlight blending mode setting for an annotation.
	Note that this function returns a Boolean value, not an error code.
	@param drawer The annotation drawer object.
	@return True if highlight mode is on.
	*/
	AIAPI AIBoolean (*GetHighlightMode)(AIAnnotatorDrawer *drawer);

	/**  Draws a PNG Image in an annotation.
	@param drawer The annotation drawer object.
	@param inPNGImageData The raw PNG image data.
	@param topLeft The point at which to draw the top left corner.
	*/
	AIAPI AIErr (*DrawPNGImage)(AIAnnotatorDrawer *drawer, const ai::uint8* inPNGImageData,  ai::uint32 inDataSize, const AIPoint &topLeft);

	/** Draws a PNG Image centered in a rectangle in an annotation.
	@param drawer The annotation drawer object.
	@param inPNGImageData The raw PNG image data.
	@param rect The rectangle.
	*/
	AIAPI AIErr (*DrawPNGImageCentered)(AIAnnotatorDrawer *drawer, const ai::uint8* inPNGImageData, ai::uint32 inDataSize, const AIRect &rect);

	/** Retrieves an AGM port for an annotation.
	Note that this function returns a port object pointer, not an error code. 
	You must call \c #ReleaseAGMPort() when you are no longer using the port. Failure to release the port causes memory leaks.
	@param drawer The annotation drawer object.
	*/
	AIAPI AIAGMPort* (*GetAGMPort)(AIAnnotatorDrawer *drawer);

	/** Releases an AGM port and sets the pointer to NULL.
	Note that this function does not return an error code.
	@param aiAGMPort The port pointer.
	*/
	AIAPI void (*ReleaseAGMPort)(AIAGMPort *&aiAGMPort);

	/** Retrieves the port options for an annotation. Currently, the only public
	port option is anti-aliasing mode, represented by the option constant
	\c #AIAnnotatorPortOption::kAIOptionAAGraphics.
	@param drawer The annotation drawer object.
	@param whichOptions A mask for the option bits of interest,
	a logical OR of \c #AIAnnotatorPortOption values.
	@param options [out] A buffer in which to return the option value,
	a logical OR of \c #AIAnnotatorPortOption values masked by the which-options mask.
	*/
	AIAPI AIErr(*GetPortOptions)(AIAnnotatorDrawer* drawer, ai::uint32 whichOptions, ai::uint32 &options);

	/** Sets the port options for an annotation.  Currently, the only public
	port option is anti-aliasing mode, represented by the option constant
	\c #AIAnnotatorPortOption::kAIOptionAAGraphics.
	@param drawer The annotation drawer object.
	@param whichOptions A mask for the option bits of interest,
	a logical OR of \c #AIAnnotatorPortOption values.
	@param options The new options value, a logical OR of \c #AIAnnotatorPortOption
	values masked by the which-options mask.
	*/
	AIAPI AIErr(*SetPortOptions)( AIAnnotatorDrawer* drawer, ai::uint32 whichOptions, ai::uint32 options);

	/** Sets the opacity of an annotation. To avoid transparency buildup, clip drawing to
	invalidation rectangles.
	@param drawer The annotation drawer object.
	@param opacity The new opacity value in the range [0.0 to 1.0]. A value of 1 means fully opaque.
	*/
	AIAPI AIErr (*SetOpacity)(AIAnnotatorDrawer* drawer, AIReal opacity);

	/** Retrieves the opacity of an annotation.
	Note that this function returns a numeric value, not an error code.
	@param drawer The annotation drawer object.
	@return The opacity value in the range [0.0 to 1.0]. A value of 1 means fully opaque.

	*/
	AIAPI AIReal (*GetOpacity)(AIAnnotatorDrawer* drawer);
};


#include "AIHeaderEnd.h"


