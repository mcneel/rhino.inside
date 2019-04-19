#ifndef _AICORETEXTACTION_H_
#define _AICORETEXTACTION_H_

/*
 *        Name:	AICoreTextAction.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Actions defined in the core.
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

#ifndef __AIActionManager_h__
#include "AIActionManager.h"
#endif


/** @ingroup Actions
	Sets the font for subsequently created text, or for selected text.
		@param #kAISetTextFontKey The font name string.
		@param #kAISetTextFontFamilyKey (Not used) The font family string.
		@param #kAISetTextFontStyleKey (Not used) The font style string.
	*/
#define kAISetTextFontAction									"adobe_font"

/** Parameter for \c #kAISetTextFontAction: The font name string. */
const ActionParamKeyID kAISetTextFontKey						= 'font'; // string
/** Parameter for \c #kAISetTextFontAction: (Not used) The font family string. */
const ActionParamKeyID kAISetTextFontFamilyKey					= 'fmly'; // string
/** Parameter for \c #kAISetTextFontAction: (Not used) The font style string. */
const ActionParamKeyID kAISetTextFontStyleKey					= 'styl'; // string

/** @ingroup Actions
	Sets the text size for subsequently created text, or for selected text.
		@param #kAISetTextSizeKey The font size.
	*/
#define kAISetTextSizeAction									"adobe_fontsize"

/** Parameter for \c #kAISetTextSizeAction: The font size, a real number. */
const ActionParamKeyID kAISetTextSizeKey						= 'size'; // real


/** @ingroup Actions
	Toggles whether hidden characters are displayed in the current document. */
#define kAIShowHiddenCharactersAction							"adobe_showHiddenChar"


/** @ingroup Actions
	Sets the text orientation for the current document.
		@param #kAISetTextOrientationKey The orientation, 0 for horizontal,
			1 for vertical.
	*/
#define kAISetTextOrientationAction								"adobe_textOrientation"

/** Parameter for \c #kAISetTextOrientationAction: The orientation, 0 for horizontal,
			1 for vertical. */
const ActionParamKeyID kAISetTextOrientationKey					= 'horz'; // enum

/** @ingroup Actions
	Creates outlines from the selected text.	*/
#define kAICreateOutlinesFromTextAction							"adobe_createOutline"

/** @ingroup Actions
	Fits headline text in the current document. */
#define kAIFitHeadlineAction									"adobe_fitHeadline"

/** @ingroup Actions
	Links text blocks. 	*/
#define kAILinkTextBlocksAction									"adobe_linkText"
/** @ingroup Actions
	Unlinks text blocks. 	*/
#define kAIUnlinkTextBlocksAction								"adobe_unlinkText"

/** @ingroup Actions
	Turns on text wrapping in the current document.	*/
#define kAIMakeTextWrapAction									"adobe_makeWrap"
/** @ingroup Actions
	Turns off text wrapping in the current document.	*/
#define kAIReleaseTextWrapAction								"adobe_releaseWrap"

#define kAITypeConversionAction									"adobe_typeConversion"

/** @ingroup Actions
	Sets the current paragraph style for the current document.
		@param #kAISetParagraphStyleAlignmentKey Alignment, an alignment value.
		@param #kAISetParagraphStyleJustifyLastLineKey True to justify the last line.

		@param #kAISetParagraphStyleHangingPunctuationKey True to allow hanging punctuation.
		@param #kAISetParagraphStyleAutoHyphenationKey True to do automatic hyphenation.

		@param #kAISetParagraphStyleLeftIndentKey Left indent in document points.
		@param #kAISetParagraphStyleRightIndentKey Right indent in document points.
		@param #kAISetParagraphStyleIndentFirstKey First-line indent in document points.

		@param #kAISetParagraphStyleSpaceBeforeKey Line space before paragraph in document points.

		@param #kAISetParagraphStyleMinimumWordSpacingKey Minimum word spacing in document points.
		@param #kAISetParagraphStyleMaximumWordSpacingKey Maximum word spacing in document points.
		@param #kAISetParagraphStyleOptimalWordSpacingKey Optimal word spacing in document points.

		@param #kAISetParagraphStyleMinimumLetterSpacingKey	Minimum letter spacing in document points.
		@param #kAISetParagraphStyleMaximumLetterSpacingKey	Maximum letter spacing in document points.
		@param #kAISetParagraphStyleOptimalLetterSpacingKey	Optimal letter spacing in document points.

		@param #kAISetParagraphStyleMinimumCharsBeforeHyphenKey	Minimum number of characters before a hyphen.
		@param #kAISetParagraphStyleMinimumCharsAfterHyphenKey Maximum number of characters before a hyphen.
		@param #kAISetParagraphStyleMaximumConsecutiveHyphensKey Maximum number of consecutive hyphens.

		@param #kAISetParagraphStyleProcessRepeatCharactersKey True to process repeat characters.
		@param #kAISetParagraphStyleBindingPunctuationKey True to use binding punctuation.
		@param #kAISetParagraphStyleCJKBindingPunctuationTypeKey The binding punctuation type
			to use with Asian character sets.
		@param #kAISetParagraphStyleCJKDontSqueezePeriodKey	True to not squeeze periods
			with Asian character sets.
		@param #kAISetParagraphStyleCJKBindContinuousCharsKey True to bind continuous characters
			with Asian character sets.
		@param #kAISetParagraphStyleCJKDontAdjustContinuousCharsKey	True to not adjust continuous
			characters with Asian character sets.
		@param #kAISetParagraphStyleCJKHangCharsAlwaysHangKey True to let hanging characters
			hang with Asian character sets.
	*/
#define kAISetParagraphStyleAction								"adobe_paragraphPalette"

/** Parameter for \c #kAISetParagraphStyleAction: Alignment, an alignment value. */
const ActionParamKeyID kAISetParagraphStyleAlignmentKey			= 'alin'; // enum
/** Parameter for \c #kAISetParagraphStyleAction: True to justify the last line.  */
const ActionParamKeyID kAISetParagraphStyleJustifyLastLineKey	= 'last'; // bool

/** Parameter for \c #kAISetParagraphStyleAction: True to allow hanging punctuation.  */
const ActionParamKeyID kAISetParagraphStyleHangingPunctuationKey = 'hang'; // bool
/** Parameter for \c #kAISetParagraphStyleAction: True to do automatic hyphenation.  */
const ActionParamKeyID kAISetParagraphStyleAutoHyphenationKey	= 'auto'; // bool

/** Parameter for \c #kAISetParagraphStyleAction: Left indent in document points.  */
const ActionParamKeyID kAISetParagraphStyleLeftIndentKey		= 'left'; // real
/** Parameter for \c #kAISetParagraphStyleAction: Right indent in document points.  */
const ActionParamKeyID kAISetParagraphStyleRightIndentKey		= 'rit.'; // real
/** Parameter for \c #kAISetParagraphStyleAction: First-line indent in document points.  */
const ActionParamKeyID kAISetParagraphStyleIndentFirstKey		= 'flft'; // real

/** Parameter for \c #kAISetParagraphStyleAction: Line space before paragraph in document points.  */
const ActionParamKeyID kAISetParagraphStyleSpaceBeforeKey		= 'pspc'; // real

/** Parameter for \c #kAISetParagraphStyleAction: Minimum word spacing in document points.  */
const ActionParamKeyID kAISetParagraphStyleMinimumWordSpacingKey = 'miws'; // real
/** Parameter for \c #kAISetParagraphStyleAction: Maximum word spacing in document points.  */
const ActionParamKeyID kAISetParagraphStyleMaximumWordSpacingKey = 'maws'; // real
/** Parameter for \c #kAISetParagraphStyleAction: Optimal word spacing in document points.  */
const ActionParamKeyID kAISetParagraphStyleOptimalWordSpacingKey = 'dsws'; // real

/** Parameter for \c #kAISetParagraphStyleAction: Minimum letter spacing in document points.  */
const ActionParamKeyID kAISetParagraphStyleMinimumLetterSpacingKey = 'mils'; // real
/** Parameter for \c #kAISetParagraphStyleAction: Maximum letter spacing in document points.  */
const ActionParamKeyID kAISetParagraphStyleMaximumLetterSpacingKey = 'mals'; // real
/** Parameter for \c #kAISetParagraphStyleAction: Optimal letter spacing in document points.  */
const ActionParamKeyID kAISetParagraphStyleOptimalLetterSpacingKey = 'dsls'; // real

/** Parameter for \c #kAISetParagraphStyleAction: Minimum number of characters before a hyphen.  */
const ActionParamKeyID kAISetParagraphStyleMinimumCharsBeforeHyphenKey = 'lhyp'; // integer
/** Parameter for \c #kAISetParagraphStyleAction: Maximum number of characters before a hyphen.  */
const ActionParamKeyID kAISetParagraphStyleMinimumCharsAfterHyphenKey = 'thyp'; // integer
/** Parameter for \c #kAISetParagraphStyleAction: Maximum number of consecutive hyphens.  */
const ActionParamKeyID kAISetParagraphStyleMaximumConsecutiveHyphensKey = 'hlns'; // integer

/** Parameter for \c #kAISetParagraphStyleAction: True to process repeat characters.  */
const ActionParamKeyID kAISetParagraphStyleProcessRepeatCharactersKey = 'rpet'; // bool
/** Parameter for \c #kAISetParagraphStyleAction: True to use binding punctuation.  */
const ActionParamKeyID kAISetParagraphStyleBindingPunctuationKey = 'punc'; // bool
/** Parameter for \c #kAISetParagraphStyleAction: The binding punctuation type
			to use with Asian character sets.  */
const ActionParamKeyID kAISetParagraphStyleCJKBindingPunctuationTypeKey = 'punc'; // enum
/** Parameter for \c #kAISetParagraphStyleAction: True to not squeeze periods with Asian character sets.  */
const ActionParamKeyID kAISetParagraphStyleCJKDontSqueezePeriodKey = 'squz'; // bool
/** Parameter for \c #kAISetParagraphStyleAction: True to bind continuous characters with Asian character sets.  */
const ActionParamKeyID kAISetParagraphStyleCJKBindContinuousCharsKey = 'bind'; // bool
/** Parameter for \c #kAISetParagraphStyleAction: True to not adjust continuous characters with Asian character sets.  */
const ActionParamKeyID kAISetParagraphStyleCJKDontAdjustContinuousCharsKey = 'adjs'; // bool
/** Parameter for \c #kAISetParagraphStyleAction: True to let hanging characters hang with Asian character sets.  */
const ActionParamKeyID kAISetParagraphStyleCJKHangCharsAlwaysHangKey = 'adjs'; // bool

/** @ingroup Actions
	Sets the current character style for the current document.
		@param #kAISetCharacterStyleFontKey	The font name string.
		@param #kAISetCharacterStyleSizeKey	The font size in document points.
		@param #kAISetCharacterStyleTrackingKey	Tracking.
		@param #kAISetCharacterStyleAutoKerningKey Existence enables automatic kerning.
		@param #kAISetCharacterStyleKerningKey Kerning value in document points.
		@param #kAISetCharacterStyleAutoLeadingKey Existence enables automatic leading.
		@param #kAISetCharacterStyleLeadingKey Leading value in document points.
		@param #kAISetCharacterStyleHorizontalScaleKey Horizontal scaling factor in range [0..1]
		@param #kAISetCharacterStyleVerticalScaleKey Vertical scaling factor in range [0..1]
		@param #kAISetCharacterStyleBaselineShiftKey Baseline shift in document points.
		@param #kAISetCharacterStyleLanguageKey	The language, a language-code value.
		@param #kAISetCharacterStyleDirectionKey The direction, a direction-code value.
		@param #kAISetCharacterStyleMojiZumeKey	True to use MojiZume.
		@param #kAISetCharacterStyleWariChuKey	True to use	WariChu.
		@param #kAISetCharacterStyleWariChuScaleKey	The WariChu scaling factor in range [0..1]
		@param #kAISetCharacterStyleKumiHanKey True to use KumiHan.
		@param #kAISetCharacterStyleKumiWaJiKanKey The KumiWaJiKan value.
		@param #kAISetCharacterStyleKumiWaOuKanKey	The KumiWaOuKan value
	*/

#define kAISetCharacterStyleAction								"adobe_characterPalette"

/** Parameter for \c #kAISetCharacterStyleAction: The font name string.  */
const ActionParamKeyID kAISetCharacterStyleFontKey				= 'font'; // string
/** Parameter for \c #kAISetCharacterStyleAction: The font size in document points.  */
const ActionParamKeyID kAISetCharacterStyleSizeKey				= 'size'; // real
/** Parameter for \c #kAISetCharacterStyleAction: Tracking   */
const ActionParamKeyID kAISetCharacterStyleTrackingKey			= 'trck'; // integer
/** Parameter for \c #kAISetCharacterStyleAction:  Existence enables automatic kerning. */
const ActionParamKeyID kAISetCharacterStyleAutoKerningKey		= 'atke'; // existence enables autokern
/** Parameter for \c #kAISetCharacterStyleAction: Kerning value in document points.  */
const ActionParamKeyID kAISetCharacterStyleKerningKey			= 'kern'; // integer
/** Parameter for \c #kAISetCharacterStyleAction: Existence enables automatic leading.  */
const ActionParamKeyID kAISetCharacterStyleAutoLeadingKey		= 'atld'; // existence enables autolead
/** Parameter for \c #kAISetCharacterStyleAction: Leading value in document points.  */
const ActionParamKeyID kAISetCharacterStyleLeadingKey			= 'lead'; // real
/** Parameter for \c #kAISetCharacterStyleAction: Horizontal scaling factor, where 1 is 100% */
const ActionParamKeyID kAISetCharacterStyleHorizontalScaleKey	= 'hori'; // real
/** Parameter for \c #kAISetCharacterStyleAction: Vertical scaling factor, where 1 is 100%  */
const ActionParamKeyID kAISetCharacterStyleVerticalScaleKey		= 'vert'; // real
/** Parameter for \c #kAISetCharacterStyleAction: Baseline shift in document points.  */
const ActionParamKeyID kAISetCharacterStyleBaselineShiftKey		= 'base'; // real
/** Parameter for \c #kAISetCharacterStyleAction: The language, a language-code value.  */
const ActionParamKeyID kAISetCharacterStyleLanguageKey			= 'lang'; // enum
/** Parameter for \c #kAISetCharacterStyleAction: The direction, a direction-code value.  */
const ActionParamKeyID kAISetCharacterStyleDirectionKey			= 'dirc'; // enum
/** Parameter for \c #kAISetCharacterStyleAction: True to use MojiZume.  */
const ActionParamKeyID kAISetCharacterStyleMojiZumeKey			= 'mono'; // bool
/** Parameter for \c #kAISetCharacterStyleAction: True to use WariChu.  */
const ActionParamKeyID kAISetCharacterStyleWariChuKey			= 'wari'; // bool
/** Parameter for \c #kAISetCharacterStyleAction: The WariChu scaling factor, where 1 is 100% */
const ActionParamKeyID kAISetCharacterStyleWariChuScaleKey		= 'scal'; // real
/** Parameter for \c #kAISetCharacterStyleAction: True to use KumiHan.  */
const ActionParamKeyID kAISetCharacterStyleKumiHanKey			= 'lyot'; // bool
/** Parameter for \c #kAISetCharacterStyleAction:   */
const ActionParamKeyID kAISetCharacterStyleKumiWaJiKanKey		= 'cjk.'; // real
/** Parameter for \c #kAISetCharacterStyleAction:   */
const ActionParamKeyID kAISetCharacterStyleKumiWaOuKanKey		= 'cjk.'; // real

// -----------------------------------------------------------------------------
// Action: kAISetTabStopsAction
// Purpose: Set tab stops
// Parameters:
//	- kAISetTabStopsPaletteOrientationKey, bool:
//	- kAISetTabStopsNumberOfStopsKey, integer:
//	- kAISetTabStopsAutoStopDeltaKey, real:
// Comments:
//
// -----------------------------------------------------------------------------
/** @ingroup Actions
	Sets tab stops for the current document. Each tab stop is
	specified by two key entries constructed from a pair
   	of characters and the tab stop number 'n' as follows:

	<code>makeLong('a', 'l', n)</code> specifies the alignment
	<code>makeLong('p', 's', n)</code> specifies the position

	where \c makeLong() is defined to be:
@code
unsigned long makeLong(char a, char b, int number){
	unsigned long rVal;

	if (number > 100 || number < 0)
	return 0;

	rVal = a << 24;
	rVal += b << 16;
	rVal += (char)((number / 10 + 48)) << 8;
	rVal += (number % 10 + 48);

	return rVal;
}
       @endcode
		@param #kAISetTabStopsPaletteOrientationKey True to set the tab-stop palette
			orientation to horizontal, false for vertical.
		@param #kAISetTabStopsNumberOfStopsKey The number of tab stops.
		@param #kAISetTabStopsAutoStopDeltaKey An interval in document points for automatic tabs.
	*/
#define kAISetTabStopsAction									"adobe_tabruler"

/** Parameter for \c #kAISetTabStopsAction: True to set the tab-stop palette orientation
	to horizontal, false for vertical.  */
const ActionParamKeyID kAISetTabStopsPaletteOrientationKey		= 'horz'; // bool
/** Parameter for \c #kAISetTabStopsAction: The number of tab stops.  */
const ActionParamKeyID kAISetTabStopsNumberOfStopsKey			= 'num.'; // integer
/** Parameter for \c #kAISetTabStopsAction: An interval in document points for automatic tabs.  */
const ActionParamKeyID kAISetTabStopsAutoStopDeltaKey			= 'dlta'; // real

#endif
