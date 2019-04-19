/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	ATETextSuitesImportHelper.h
		
	Notes:	Machine Generated file from script version 1.45
	        Please don't modify manually!
	
 ---------------------------------------------------------------------------------- */
#ifndef __ATETextSuitesImportHelper__
#define __ATETextSuitesImportHelper__

#if SLO_COMPLEXSCRIPT

#define EXTERN_TEXT_SUITES_COMPLEXSCRIPT\
	ATE::ArrayParagraphDirectionSuite* sArrayParagraphDirection;\
	ATE::ArrayJustificationMethodSuite* sArrayJustificationMethod;\
	ATE::ArrayKashidaWidthSuite* sArrayKashidaWidth;\
	ATE::ArrayKashidasSuite* sArrayKashidas;\
	ATE::ArrayDirOverrideSuite* sArrayDirOverride;\
	ATE::ArrayDigitSetSuite* sArrayDigitSet;\
	ATE::ArrayDiacVPosSuite* sArrayDiacVPos;\

#define IMPORT_TEXT_SUITES_COMPLEXSCRIPT\
	{ kArrayParagraphDirectionSuite, kArrayParagraphDirectionSuiteVersion, &sArrayParagraphDirection },\
	{ kArrayJustificationMethodSuite, kArrayJustificationMethodSuiteVersion, &sArrayJustificationMethod },\
	{ kArrayKashidaWidthSuite, kArrayKashidaWidthSuiteVersion, &sArrayKashidaWidth },\
	{ kArrayKashidasSuite, kArrayKashidasSuiteVersion, &sArrayKashidas },\
	{ kArrayDirOverrideSuite, kArrayDirOverrideSuiteVersion, &sArrayDirOverride },\
	{ kArrayDigitSetSuite, kArrayDigitSetSuiteVersion, &sArrayDigitSet },\
	{ kArrayDiacVPosSuite, kArrayDiacVPosSuiteVersion, &sArrayDiacVPos },\

#else

#define EXTERN_TEXT_SUITES_COMPLEXSCRIPT
#define IMPORT_TEXT_SUITES_COMPLEXSCRIPT

#endif

#define EXTERN_TEXT_SUITES\
	ATE::ApplicationPaintSuite* sApplicationPaint;\
	ATE::CompFontSuite* sCompFont;\
	ATE::CompFontClassSuite* sCompFontClass;\
	ATE::CompFontClassSetSuite* sCompFontClassSet;\
	ATE::CompFontComponentSuite* sCompFontComponent;\
	ATE::CompFontSetSuite* sCompFontSet;\
	ATE::GlyphRunSuite* sGlyphRun;\
	ATE::GlyphRunsIteratorSuite* sGlyphRunsIterator;\
	ATE::MojiKumiSuite* sMojiKumi;\
	ATE::MojiKumiSetSuite* sMojiKumiSet;\
	ATE::TextFrameSuite* sTextFrame;\
	ATE::TextFramesIteratorSuite* sTextFramesIterator;\
	ATE::TextLineSuite* sTextLine;\
	ATE::TextLinesIteratorSuite* sTextLinesIterator;\
	ATE::TextResourcesSuite* sTextResources;\
	ATE::ApplicationTextResourcesSuite* sApplicationTextResources;\
	ATE::DocumentTextResourcesSuite* sDocumentTextResources;\
	ATE::VersionInfoSuite* sVersionInfo;\
	ATE::ArrayApplicationPaintRefSuite* sArrayApplicationPaintRef;\
	ATE::ArrayRealSuite* sArrayReal;\
	ATE::ArrayBoolSuite* sArrayBool;\
	ATE::ArrayIntegerSuite* sArrayInteger;\
	ATE::ArrayLineCapTypeSuite* sArrayLineCapType;\
	ATE::ArrayFigureStyleSuite* sArrayFigureStyle;\
	ATE::ArrayLineJoinTypeSuite* sArrayLineJoinType;\
	ATE::ArrayWariChuJustificationSuite* sArrayWariChuJustification;\
	ATE::ArrayStyleRunAlignmentSuite* sArrayStyleRunAlignment;\
	ATE::ArrayAutoKernTypeSuite* sArrayAutoKernType;\
	ATE::ArrayBaselineDirectionSuite* sArrayBaselineDirection;\
	ATE::ArrayLanguageSuite* sArrayLanguage;\
	ATE::ArrayFontCapsOptionSuite* sArrayFontCapsOption;\
	ATE::ArrayFontBaselineOptionSuite* sArrayFontBaselineOption;\
	ATE::ArrayFontOpenTypePositionOptionSuite* sArrayFontOpenTypePositionOption;\
	ATE::ArrayUnderlinePositionSuite* sArrayUnderlinePosition;\
	ATE::ArrayStrikethroughPositionSuite* sArrayStrikethroughPosition;\
	ATE::ArrayParagraphJustificationSuite* sArrayParagraphJustification;\
	ATE::ArrayArrayRealSuite* sArrayArrayReal;\
	ATE::ArrayBurasagariTypeSuite* sArrayBurasagariType;\
	ATE::ArrayPreferredKinsokuOrderSuite* sArrayPreferredKinsokuOrder;\
	ATE::ArrayKinsokuRefSuite* sArrayKinsokuRef;\
	ATE::ArrayMojiKumiRefSuite* sArrayMojiKumiRef;\
	ATE::ArrayMojiKumiSetRefSuite* sArrayMojiKumiSetRef;\
	ATE::ArrayTabStopsRefSuite* sArrayTabStopsRef;\
	ATE::ArrayLeadingTypeSuite* sArrayLeadingType;\
	ATE::ArrayFontRefSuite* sArrayFontRef;\
	ATE::ArrayGlyphIDSuite* sArrayGlyphID;\
	ATE::ArrayRealPointSuite* sArrayRealPoint;\
	ATE::ArrayRealMatrixSuite* sArrayRealMatrix;\
	EXTERN_TEXT_SUITES_COMPLEXSCRIPT\
	ATE::CharFeaturesSuite* sCharFeatures;\
	ATE::CharInspectorSuite* sCharInspector;\
	ATE::CharStyleSuite* sCharStyle;\
	ATE::CharStylesSuite* sCharStyles;\
	ATE::CharStylesIteratorSuite* sCharStylesIterator;\
	ATE::FindSuite* sFind;\
	ATE::FontSuite* sFont;\
	ATE::GlyphSuite* sGlyph;\
	ATE::GlyphsSuite* sGlyphs;\
	ATE::GlyphsIteratorSuite* sGlyphsIterator;\
	ATE::KinsokuSuite* sKinsoku;\
	ATE::KinsokuSetSuite* sKinsokuSet;\
	ATE::ParaFeaturesSuite* sParaFeatures;\
	ATE::ParagraphSuite* sParagraph;\
	ATE::ParagraphsIteratorSuite* sParagraphsIterator;\
	ATE::ParaInspectorSuite* sParaInspector;\
	ATE::ParaStyleSuite* sParaStyle;\
	ATE::ParaStylesSuite* sParaStyles;\
	ATE::ParaStylesIteratorSuite* sParaStylesIterator;\
	ATE::SpellSuite* sSpell;\
	ATE::StoriesSuite* sStories;\
	ATE::StorySuite* sStory;\
	ATE::TabStopSuite* sTabStop;\
	ATE::TabStopsSuite* sTabStops;\
	ATE::TabStopsIteratorSuite* sTabStopsIterator;\
	ATE::TextRangeSuite* sTextRange;\
	ATE::TextRangesSuite* sTextRanges;\
	ATE::TextRangesIteratorSuite* sTextRangesIterator;\
	ATE::TextRunsIteratorSuite* sTextRunsIterator;\
	ATE::WordsIteratorSuite* sWordsIterator;\
	ATE::ArrayLineSuite* sArrayLine;\
	ATE::ArrayComposerEngineSuite* sArrayComposerEngine;\

#define IMPORT_TEXT_SUITES\
	{ kApplicationPaintSuite, kApplicationPaintSuiteVersion, &sApplicationPaint } ,\
	{ kCompFontSuite, kCompFontSuiteVersion, &sCompFont },\
	{ kCompFontClassSuite, kCompFontClassSuiteVersion, &sCompFontClass },\
	{ kCompFontClassSetSuite, kCompFontClassSetSuiteVersion, &sCompFontClassSet },\
	{ kCompFontComponentSuite, kCompFontComponentSuiteVersion, &sCompFontComponent },\
	{ kCompFontSetSuite, kCompFontSetSuiteVersion, &sCompFontSet },\
	{ kGlyphRunSuite, kGlyphRunSuiteVersion, &sGlyphRun },\
	{ kGlyphRunsIteratorSuite, kGlyphRunsIteratorSuiteVersion, &sGlyphRunsIterator },\
	{ kMojiKumiSuite, kMojiKumiSuiteVersion, &sMojiKumi },\
	{ kMojiKumiSetSuite, kMojiKumiSetSuiteVersion, &sMojiKumiSet },\
	{ kTextFrameSuite, kTextFrameSuiteVersion, &sTextFrame },\
	{ kTextFramesIteratorSuite, kTextFramesIteratorSuiteVersion, &sTextFramesIterator },\
	{ kTextLineSuite, kTextLineSuiteVersion, &sTextLine },\
	{ kTextLinesIteratorSuite, kTextLinesIteratorSuiteVersion, &sTextLinesIterator },\
	{ kTextResourcesSuite, kTextResourcesSuiteVersion, &sTextResources },\
	{ kApplicationTextResourcesSuite, kApplicationTextResourcesSuiteVersion, &sApplicationTextResources },\
	{ kDocumentTextResourcesSuite, kDocumentTextResourcesSuiteVersion, &sDocumentTextResources },\
	{ kVersionInfoSuite, kVersionInfoSuiteVersion, &sVersionInfo },\
	{ kArrayApplicationPaintRefSuite, kArrayApplicationPaintRefSuiteVersion, &sArrayApplicationPaintRef },\
	{ kArrayRealSuite, kArrayRealSuiteVersion, &sArrayReal },\
	{ kArrayBoolSuite, kArrayBoolSuiteVersion, &sArrayBool },\
	{ kArrayIntegerSuite, kArrayIntegerSuiteVersion, &sArrayInteger },\
	{ kArrayLineCapTypeSuite, kArrayLineCapTypeSuiteVersion, &sArrayLineCapType },\
	{ kArrayFigureStyleSuite, kArrayFigureStyleSuiteVersion, &sArrayFigureStyle },\
	{ kArrayLineJoinTypeSuite, kArrayLineJoinTypeSuiteVersion, &sArrayLineJoinType },\
	{ kArrayWariChuJustificationSuite, kArrayWariChuJustificationSuiteVersion, &sArrayWariChuJustification },\
	{ kArrayStyleRunAlignmentSuite, kArrayStyleRunAlignmentSuiteVersion, &sArrayStyleRunAlignment },\
	{ kArrayAutoKernTypeSuite, kArrayAutoKernTypeSuiteVersion, &sArrayAutoKernType },\
	{ kArrayBaselineDirectionSuite, kArrayBaselineDirectionSuiteVersion, &sArrayBaselineDirection },\
	{ kArrayLanguageSuite, kArrayLanguageSuiteVersion, &sArrayLanguage },\
	{ kArrayFontCapsOptionSuite, kArrayFontCapsOptionSuiteVersion, &sArrayFontCapsOption },\
	{ kArrayFontBaselineOptionSuite, kArrayFontBaselineOptionSuiteVersion, &sArrayFontBaselineOption },\
	{ kArrayFontOpenTypePositionOptionSuite, kArrayFontOpenTypePositionOptionSuiteVersion, &sArrayFontOpenTypePositionOption },\
	{ kArrayUnderlinePositionSuite, kArrayUnderlinePositionSuiteVersion, &sArrayUnderlinePosition },\
	{ kArrayStrikethroughPositionSuite, kArrayStrikethroughPositionSuiteVersion, &sArrayStrikethroughPosition },\
	{ kArrayParagraphJustificationSuite, kArrayParagraphJustificationSuiteVersion, &sArrayParagraphJustification },\
	{ kArrayArrayRealSuite, kArrayArrayRealSuiteVersion, &sArrayArrayReal },\
	{ kArrayBurasagariTypeSuite, kArrayBurasagariTypeSuiteVersion, &sArrayBurasagariType },\
	{ kArrayPreferredKinsokuOrderSuite, kArrayPreferredKinsokuOrderSuiteVersion, &sArrayPreferredKinsokuOrder },\
	{ kArrayKinsokuRefSuite, kArrayKinsokuRefSuiteVersion, &sArrayKinsokuRef },\
	{ kArrayMojiKumiRefSuite, kArrayMojiKumiRefSuiteVersion, &sArrayMojiKumiRef },\
	{ kArrayMojiKumiSetRefSuite, kArrayMojiKumiSetRefSuiteVersion, &sArrayMojiKumiSetRef },\
	{ kArrayTabStopsRefSuite, kArrayTabStopsRefSuiteVersion, &sArrayTabStopsRef },\
	{ kArrayLeadingTypeSuite, kArrayLeadingTypeSuiteVersion, &sArrayLeadingType },\
	{ kArrayFontRefSuite, kArrayFontRefSuiteVersion, &sArrayFontRef },\
	{ kArrayGlyphIDSuite, kArrayGlyphIDSuiteVersion, &sArrayGlyphID },\
	{ kArrayRealPointSuite, kArrayRealPointSuiteVersion, &sArrayRealPoint },\
	{ kArrayRealMatrixSuite, kArrayRealMatrixSuiteVersion, &sArrayRealMatrix },\
	IMPORT_TEXT_SUITES_COMPLEXSCRIPT\
	{ kCharFeaturesSuite, kCharFeaturesSuiteVersion, &sCharFeatures },\
	{ kCharInspectorSuite, kCharInspectorSuiteVersion, &sCharInspector },\
	{ kCharStyleSuite, kCharStyleSuiteVersion, &sCharStyle },\
	{ kCharStylesSuite, kCharStylesSuiteVersion, &sCharStyles },\
	{ kCharStylesIteratorSuite, kCharStylesIteratorSuiteVersion, &sCharStylesIterator },\
	{ kFindSuite, kFindSuiteVersion, &sFind },\
	{ kFontSuite, kFontSuiteVersion, &sFont },\
	{ kGlyphSuite, kGlyphSuiteVersion, &sGlyph },\
	{ kGlyphsSuite, kGlyphsSuiteVersion, &sGlyphs },\
	{ kGlyphsIteratorSuite, kGlyphsIteratorSuiteVersion, &sGlyphsIterator },\
	{ kKinsokuSuite, kKinsokuSuiteVersion, &sKinsoku },\
	{ kKinsokuSetSuite, kKinsokuSetSuiteVersion, &sKinsokuSet },\
	{ kParaFeaturesSuite, kParaFeaturesSuiteVersion, &sParaFeatures },\
	{ kParagraphSuite, kParagraphSuiteVersion, &sParagraph },\
	{ kParagraphsIteratorSuite, kParagraphsIteratorSuiteVersion, &sParagraphsIterator },\
	{ kParaInspectorSuite, kParaInspectorSuiteVersion, &sParaInspector },\
	{ kParaStyleSuite, kParaStyleSuiteVersion, &sParaStyle },\
	{ kParaStylesSuite, kParaStylesSuiteVersion, &sParaStyles },\
	{ kParaStylesIteratorSuite, kParaStylesIteratorSuiteVersion, &sParaStylesIterator },\
	{ kSpellSuite, kSpellSuiteVersion, &sSpell },\
	{ kStoriesSuite, kStoriesSuiteVersion, &sStories },\
	{ kStorySuite, kStorySuiteVersion, &sStory },\
	{ kTabStopSuite, kTabStopSuiteVersion, &sTabStop },\
	{ kTabStopsSuite, kTabStopsSuiteVersion, &sTabStops },\
	{ kTabStopsIteratorSuite, kTabStopsIteratorSuiteVersion, &sTabStopsIterator },\
	{ kTextRangeSuite, kTextRangeSuiteVersion, &sTextRange },\
	{ kTextRangesSuite, kTextRangesSuiteVersion, &sTextRanges },\
	{ kTextRangesIteratorSuite, kTextRangesIteratorSuiteVersion, &sTextRangesIterator },\
	{ kTextRunsIteratorSuite, kTextRunsIteratorSuiteVersion, &sTextRunsIterator },\
	{ kWordsIteratorSuite, kWordsIteratorSuiteVersion, &sWordsIterator },\
	{ kArrayLineSuite, kArrayLineSuiteVersion, &sArrayLine },\
	{ kArrayComposerEngineSuite, kArrayComposerEngineSuiteVersion, &sArrayComposerEngine },\

#endif //__ATETextSuitesImportHelper__


