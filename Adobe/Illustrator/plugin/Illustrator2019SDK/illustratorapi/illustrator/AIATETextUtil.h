#ifndef __ATETextUtil__
#define __ATETextUtil__

/*
 *        Name:	AIATETextUtil.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Text Frame Object Suite.
 *
 *				REQUIREMENT: This won't compile without a C++ compiler!
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

#ifndef __ATESuites__
#include "ATESuites.h"
#endif

#ifndef __AIDocument__
#include "AIDocument.h"
#endif

#ifndef __AIFont__
#include "AIFont.h"
#endif

#ifndef __SPFiles__
#include "SPFiles.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIATETextUtil.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIATETextUtilSuite			"AI ATE Text Util Suite"
#define kAIATETextUtilSuiteVersion4	AIAPI_VERSION(4)
#define kAIATETextUtilSuiteVersion	kAIATETextUtilSuiteVersion4
#define kAIATETextUtilVersion		kAIATETextUtilSuiteVersion


/** @ingroup Notifiers
	 Font changed in current document. See \c #AIATETextUtilSuite */
#define kAICurrentFontChangedNotifier	"AI Current Font Changed Notifier"
/** @ingroup Notifiers
	 Font size changed in current document. See \c #AIATETextUtilSuite */
#define kAICurrentFontSizeChangedNotifier	"AI Current Font Size Changed Notifier"
/** @ingroup Notifiers
	 List of available fonts changed. See \c #AIATETextUtilSuite */
#define kAIFontListChangedNotifier		"AI Font List Changed Notifier"
/** @ingroup Notifiers
	 Sent when ATE document resources, such as named style, have changed.*/
#define kATEDocumentResourceChangedNotifier	"AI ATE Document Resource Changed Notifier"


/** @ingroup Errors
	Returned from \c #AIATETextUtilSuite::GetBoundsFromTextRange() if the range is
	hidden due to smaller frame size (overset).
*/
#define kAIATEInvalidBounds 'INVB'

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	It provides utilities for working with text.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIATETextUtilSuite and \c #kAIATETextUtilVersion.
 */
struct AIATETextUtilSuite {
	/** Retrieves the bounds of a text range.
			@param tr The text range.
			@param bounds [out] A buffer in which to return the bounding box.
			@return The error \c #kAIATEInvalidBounds if the text range is hidden
				due to smaller frame size. */
	AIAPI AIErr (*GetBoundsFromTextRange)( ATE::TextRangeRef tr, AIRealRect* bounds );

	/** Retrieves application global resources related to text.
			@param result [out] A buffer in which to return the resource values.
				Access the font resources in this opaque structure using
				the \c #ATE::IApplicationTextResources wrapper.
			@see IText.h
		*/
	AIAPI AIErr (*GetApplicationTextResources)( ATE::ApplicationTextResourcesRef *result );

	/** Retrieves per-document global resources related to text.
			@param pResources [out] A buffer in which to return the resource values.
			 	Access the font resources in this opaque structure using
			 	the \c #ATE::ITextResources wrapper.
		 	@see IText.h
		*/
	AIAPI AIErr (*GetTextResourcesFromDocument)( AIDocumentHandle pDocument, ATE::TextResourcesRef* pResources );

	/** Retrieves the composite font from a composite font file.
			@param filePath The file.
			@param compFont [out] A buffer in which to return the composite font.
				Access the contents of this opaque structure using
			 	the \c #ATE::ICompFont wrapper.
			@see IText.h
		*/
	AIAPI AIErr (*GetCompositeFont)( const ai::FilePath&, ATE::CompFontRef * compFont );

	/** Creates or replaces a composite font file, writing the information from a specified
		composite font.
			@param filePath The file path.
			@param compFont The composite font.
		*/
	AIAPI AIErr (*WriteCompositeFont)( const ai::FilePath&, const ATE::CompFontRef compFontRef);

	/** Retrieves the Kinsoku order information from a Kinsoku file.
			@param filePath The file.
			@param kinsokuRef [out] A buffer in which to return the Kinsoku information.
				Access the contents of this opaque structure using
			 	the \c #ATE::IKinsoku wrapper.
			@see IText.h
		*/
	AIAPI AIErr (*GetKinsokuFile)( const ai::FilePath&, ATE::KinsokuRef *kinsokuRef );

	/** Creates or replaces a Kinsoku file, writing the information from a specified
		Kinsoku reference.
			@param filePath The file.
			@param kinsokuRef The new Kinsoku information.
		*/
	AIAPI AIErr (*WriteKinsokuFile)( const ai::FilePath&, const ATE::KinsokuRef kinsokuRef );

	/** Retrieves the MojiKumi information from a MojiKumi file.
			@param filePath The file.
			@param mojikumiRef [out] A buffer in which to return the MojiKumi information.
				Access the contents of this opaque structure using
				the \c #ATE::IMojiKumi wrapper.
			@see IText.h
		*/
	AIAPI AIErr (*GetMojiKumiFile) ( const ai::FilePath&, ATE::MojiKumiRef *mojikumeRef );

	/** Creates or replaces a MojiKumi file, writing the information from a specified
		MojiKumi reference.
				@param filePath The file.
				@param mojikumiRef The new MojiKumi information.
		*/
	AIAPI AIErr (*WriteMojiKumiFile)( const ai::FilePath&, const ATE::MojiKumiRef mojikumeRef);

	/** Internal. Updates the Kinsoku information shown for an entry in the Paragraph palette.
		*/
	AIAPI AIErr (*UpdateParagraphPaletteKinsoku) (ai::int32 index);

	/** Internal. Updates the MojuKumi information shown for an entry in the Paragraph palette.
		*/
	AIAPI AIErr (*UpdateParagraphPaletteMojiKumi)(ai::int32 index);

	/** Retrieves the spell-check dictionary for file.
			@param filePath The file.
			@param pDst [out] A buffer in which to return the spell-check information.
		*/
	AIAPI AIErr (*GetSpellFile)( const ai::FilePath& pSrcFileSpec, ATE::SpellRef* pDst );

	/** Changes the font of the currently selected text object or objects.
			@param theFont The new font.
		*/
	AIAPI AIErr (*SetCurrentFont)(AIFontKey theFont);

	/** Retrieves the font of the currently selected text object or objects.
			@param theFont [out] A buffer in which to return the font, or \c NULL if
				more than one font is used.
		*/
	AIAPI AIErr (*GetCurrentFont)(AIFontKey *result);

	/** Changes the font size of the currently selected text object or objects.
			@param theFont The new size, in points.
		*/
	AIAPI AIErr (*SetCurrentFontSize)(AIReal theFontSize);

	/** Retrieves the font size of the currently selected text object or objects.
			@param theFont [out] A buffer in which to return the font size, in points,
				or \c NULL if more than one font size is used.
		*/
	AIAPI AIErr (*GetCurrentFontSize)(AIReal *result);


	// These should be in ATE::IGlyphRun.
	/** Retrieves an array of points representing the visual, flattened, representation
		of the underline for a glyph run. These points represent a polygon, not a bezier.
		It is always closed, although the last point is not equal to the first one.
		The coordinate are hard, use \c #AIHardSoftSuite to convert them into
		soft coordinates before working with them.
			@param gr The glyph run.
			@param pPoints [out] A buffer in which to return the array of points.
	*/
	AIAPI AIErr (*GetUnderlinePoints)(const ATE::GlyphRunRef gr , ATE::ArrayRealPointRef* pPoints);

	/** Retrieves an  array of points representing the visual, flattened, representation
		of the strikethrough for a glyph run.These points represent a polygon, not a bezier.
		It is always closed, although the last point is not equal to the first one.
		The coordinate are hard, use \c #AIHardSoftSuite to convert them into
		soft coordinates before working with them.
			@param gr The glyph run.
			@param pPoints [out] A buffer in which to return the array of points.
	*/
	AIAPI AIErr (*GetStrikethroughPoints)(const ATE::GlyphRunRef gr , ATE::ArrayRealPointRef* pPoints);
};


#include "AIHeaderEnd.h"


#endif
