///* -------------------------------------------------------------------------------
//
//    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.
//
//    NOTICE:  Adobe permits you to use, modify, and distribute this file 
//    in accordance with the terms of the Adobe license agreement accompanying 
//    it. If you have received this file from a source other than Adobe, then 
//    your use, modification, or distribution of it requires the prior written 
//    permission of Adobe.
//
// ----------------------------------------------------------------------------------
//
//	File:	ATE25Suites.h
//		
//	Notes:	Machine Generated file from script version 1.45
//	        Please don't modify manually!
//	
// ---------------------------------------------------------------------------------- */
//
//#ifndef __ATE25Suites__
//#define __ATE25Suites__
//
//#include "ATESuites.h"
//
//#ifdef __cplusplus
//namespace ATE
//{
//extern  "C" {
//#endif
//
//#ifdef MAC_ENV
//	#if defined (__MWERKS__)
//		#pragma options align=power_gcc
//	#elif defined (__GNUC__)
//		#pragma options align=power
//	#endif
//#endif
//
//#ifdef WIN_ENV
//	#pragma pack(push, 4)
//#endif
//
////////////////////////////////////////////////
////       --TextFrameSuite--
////////////////////////////////////////////////
//#define kATE25TextFrameSuite kTextFrameSuite
//#define kTextFrameSuiteVersion1 1
//#define kATE25TextFrameSuiteVersion kTextFrameSuiteVersion1
//
//typedef struct ATE25TextFrameSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( TextFrameRef textframe);
//	void (*Release) ( TextFrameRef textframe);
//	ATEBool8 (*IsNull) ( TextFrameRef textframe);
//
//	// METHODS
//	// =====================================================================
//	/// Get the parent story
//	ATEErr (*GetStory) ( TextFrameRef textframe, StoryRef* ret);
//	/** Get the text range of this frame,
//	If this frame is the last frame in this story then:-
//	1. If bIncludeOverflow is true, then the range returned is including the overflown text.
//	2. If bIncludeOverflow is false, then the range returned will not include the overflown text.
//	*/
//	ATEErr (*GetTextRange) ( TextFrameRef textframe, ATEBool8 bIncludeOverflow, TextRangeRef* ret);
//	ATEErr (*GetTextLinesIterator) ( TextFrameRef textframe, TextLinesIteratorRef* ret);
//	ATEErr (*IsEqual) ( TextFrameRef textframe, const TextFrameRef anotherFrame, ATEBool8* ret);
//	ATEErr (*GetType) ( TextFrameRef textframe, FrameType* ret);
//	ATEErr (*GetLineOrientation) ( TextFrameRef textframe, LineOrientation* ret);
//	/** Check if this frame is selected.  To set the selection, you have to use application specific
//	API for that.  In Illustrator case, you can use AIArtSuite to set the selection.
//	*/
//	ATEErr (*GetSelected) ( TextFrameRef textframe, ATEBool8* ret);
//	ATEErr (*GetMatrix) ( TextFrameRef textframe, ASRealMatrix* ret);
//	ATEErr (*GetRowCount) ( TextFrameRef textframe, ASInt32* ret);
//	ATEErr (*GetColumnCount) ( TextFrameRef textframe, ASInt32* ret);
//	ATEErr (*GetRowMajorOrder) ( TextFrameRef textframe, ATEBool8* ret);
//	ATEErr (*GetRowGutter) ( TextFrameRef textframe, ASReal* ret);
//	ATEErr (*GetColumnGutter) ( TextFrameRef textframe, ASReal* ret);
//	ATEErr (*GetSpacing) ( TextFrameRef textframe, ASReal* ret);
//	ATEErr (*GetOpticalAlignment) ( TextFrameRef textframe, ATEBool8* ret);
//	ATEErr (*SetRowCount) ( TextFrameRef textframe, ASInt32 rowCount);
//	ATEErr (*SetColumnCount) ( TextFrameRef textframe, ASInt32 columnCount);
//	ATEErr (*SetRowMajorOrder) ( TextFrameRef textframe, ATEBool8 isRowMajor);
//	ATEErr (*SetRowGutter) ( TextFrameRef textframe, ASReal gutter);
//	ATEErr (*SetColumnGutter) ( TextFrameRef textframe, ASReal gutter);
//	ATEErr (*SetSpacing) ( TextFrameRef textframe, ASReal spacing);
//	ATEErr (*SetOpticalAlignment) ( TextFrameRef textframe, ATEBool8 isActive);
//	ATEErr (*SetLineOrientation) ( TextFrameRef textframe, LineOrientation lineOrientation);
//
//}ATE25TextFrameSuite;
//
////////////////////////////////////////////////
////       --DocumentTextResourcesSuite--
////////////////////////////////////////////////
//#define kATE25DocumentTextResourcesSuite kDocumentTextResourcesSuite
//#define kDocumentTextResourcesSuiteVersion1 1
//#define kATE25DocumentTextResourcesSuiteVersion kDocumentTextResourcesSuiteVersion1
//
//typedef struct ATE25DocumentTextResourcesSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( DocumentTextResourcesRef documenttextresources);
//	void (*Release) ( DocumentTextResourcesRef documenttextresources);
//	ATEBool8 (*IsNull) ( DocumentTextResourcesRef documenttextresources);
//
//	// From parent class...
//	ATEErr (*GetKinsokuSet) ( DocumentTextResourcesRef documenttextresources, KinsokuSetRef* ret);
//	ATEErr (*GetMojiKumiSet) ( DocumentTextResourcesRef documenttextresources, MojiKumiSetRef* ret);
//	ATEErr (*GetCompFontClassSet) ( DocumentTextResourcesRef documenttextresources, CompFontClassSetRef* ret);
//	ATEErr (*GetCompFontSet) ( DocumentTextResourcesRef documenttextresources, CompFontSetRef* ret);
//	ATEErr (*GetTextResources) ( DocumentTextResourcesRef documenttextresources, TextResourcesRef* ret);
//	ATEErr (*GetFind) ( DocumentTextResourcesRef documenttextresources, FindRef* ret);
//	ATEErr (*GetSpell) ( DocumentTextResourcesRef documenttextresources, const char* pSpellingDirectory, SpellRef* ret);
//	ATEErr (*GetGlyphAndAlternates) ( DocumentTextResourcesRef documenttextresources, GlyphRef* ret);
//	ATEErr (*GetAlternateGlyph) ( DocumentTextResourcesRef documenttextresources, GlyphRef* ret);
//	ATEErr (*InsertAlternateGlyph) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* theCharacters, const ATEGlyphID glyphID, const char* otFeatureArray, ASInt32 otFeatureCount, const ASInt32* otFeatureIndexArray, ATEBool8 leaveSelected);
//	ATEErr (*GetAlternatesAvailableThroughoutSelection) ( DocumentTextResourcesRef documenttextresources, ArrayIntegerRef* ret);
//	ATEErr (*GetJapaneseAlternateFeatureInSelection) ( DocumentTextResourcesRef documenttextresources, ATEBool8* isFeature, JapaneseAlternateFeature* ret);
//	ATEErr (*SetJapaneseAlternateFeatureInSelection) ( DocumentTextResourcesRef documenttextresources, JapaneseAlternateFeature feature);
//	ATEErr (*GetCharStylesInDocument) ( DocumentTextResourcesRef documenttextresources, CharStylesRef* ret);
//	ATEErr (*GetParaStylesInDocument) ( DocumentTextResourcesRef documenttextresources, ParaStylesRef* ret);
//	/// Returns a named style corresponding to pName.  If no matching
//	/// style can be found or *pName == L'\0' then a null object is returned.
//	ATEErr (*GetCharStyle) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, CharStyleRef* ret);
//	ATEErr (*GetParaStyle) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, ParaStyleRef* ret);
//	ATEErr (*GetNormalCharStyle) ( DocumentTextResourcesRef documenttextresources, CharStyleRef* ret);
//	ATEErr (*GetNormalParaStyle) ( DocumentTextResourcesRef documenttextresources, ParaStyleRef* ret);
//	ATEErr (*ResetNormalCharStyle) ( DocumentTextResourcesRef documenttextresources);
//	ATEErr (*ResetNormalParaStyle) ( DocumentTextResourcesRef documenttextresources);
//	/// Routines to add new named styles to the document.  If an existing
//	/// style already corresponds to pName or *pName == L'\0' then the
//	/// document is unchanged and a null object is returned.
//	ATEErr (*CreateCharStyle) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, CharStyleRef* ret);
//	ATEErr (*CreateParaStyle) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, ParaStyleRef* ret);
//	ATEErr (*CreateCharStyleWithFeatures) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, CharFeaturesRef pFeatures, CharStyleRef* ret);
//	ATEErr (*CreateParaStyleWithFeatures) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, ParaFeaturesRef pFeatures, ParaStyleRef* ret);
//	/// Removes a style from the document.  Exact details will be provided
//	/// later.
//	///
//	/// If no matching style in the document corresponds to pName or
//	/// *pName == L'\0' then the document is unchanged and false is returned.
//	ATEErr (*RemoveCharStyle) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, ATEBool8* ret);
//	ATEErr (*RemoveParaStyle) ( DocumentTextResourcesRef documenttextresources, const ASUnicode* pName, ATEBool8* ret);
//	/// Imports named styles from pSrcResources into current resource.
//	ATEErr (*ImportCharStyles) ( DocumentTextResourcesRef documenttextresources, TextResourcesRef pSrcResources);
//	ATEErr (*ImportParaStyles) ( DocumentTextResourcesRef documenttextresources, TextResourcesRef pSrcResources);
//	ATEErr (*SetUseSmartQuotes) ( DocumentTextResourcesRef documenttextresources, ATEBool8 smartQuotesAreOn);
//	ATEErr (*SetSmartDoubleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ASUnicode openQuote, ASUnicode closeQuote, Language language);
//	ATEErr (*SetSmartSingleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ASUnicode openQuote, ASUnicode closeQuote, Language language);
//	ATEErr (*UseSmartQuotes) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
//	ATEErr (*GetSmartDoubleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ASUnicode* openQuote, ASUnicode* closeQuote, Language language);
//	ATEErr (*GetSmartSingleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ASUnicode* openQuote, ASUnicode* closeQuote, Language language);
//	/// The library stores an internal set of insertion attributes either from
//	/// the last selection or from the last attribute change to text.  This set
//	/// of insertion attributes comprises the local overrides (CharFeatures)
//	/// and the named style (CharStyle)
//	ATEErr (*GetInsertionCharFeatures) ( DocumentTextResourcesRef documenttextresources, CharFeaturesRef* ret);
//	ATEErr (*GetInsertionCharStyle) ( DocumentTextResourcesRef documenttextresources, CharStyleRef* ret);
//	ATEErr (*SetInsertionFeaturesAndStyle) ( DocumentTextResourcesRef documenttextresources, const CharFeaturesRef pFeatures, const ASUnicode* pStyleName);
//	/// Get superscript size
//	ATEErr (*GetSuperscriptSize) ( DocumentTextResourcesRef documenttextresources, ASReal* ret);
//	/// Set superscript size
//	ATEErr (*SetSuperscriptSize) ( DocumentTextResourcesRef documenttextresources, ASReal value);
//	/// Get superscript position
//	ATEErr (*GetSuperscriptPosition) ( DocumentTextResourcesRef documenttextresources, ASReal* ret);
//	/// Set superscript position
//	ATEErr (*SetSuperscriptPosition) ( DocumentTextResourcesRef documenttextresources, ASReal value);
//	/// Get subscript size
//	ATEErr (*GetSubscriptSize) ( DocumentTextResourcesRef documenttextresources, ASReal* ret);
//	/// Set subscript size
//	ATEErr (*SetSubscriptSize) ( DocumentTextResourcesRef documenttextresources, ASReal value);
//	/// Get subscript position
//	ATEErr (*GetSubscriptPosition) ( DocumentTextResourcesRef documenttextresources, ASReal* ret);
//	/// Set subscript position
//	ATEErr (*SetSubscriptPosition) ( DocumentTextResourcesRef documenttextresources, ASReal value);
//	/// Get SmallCap size
//	ATEErr (*GetSmallCapSize) ( DocumentTextResourcesRef documenttextresources, ASReal* ret);
//	/// Set SmallCap size
//	ATEErr (*SetSmallCapSize) ( DocumentTextResourcesRef documenttextresources, ASReal value);
//	/// Get ShowHiddenCharacters
//	ATEErr (*GetShowHiddenCharacters) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
//	/// Set ShowHiddenCharacters
//	ATEErr (*SetShowHiddenCharacters) ( DocumentTextResourcesRef documenttextresources, ATEBool8 value);
//	/// Get Greeking Size
//	ATEErr (*GetGreekingSize) ( DocumentTextResourcesRef documenttextresources, ASInt32* ret);
//	/// Set Greeking Size
//	ATEErr (*SetGreekingSize) ( DocumentTextResourcesRef documenttextresources, ASInt32 value);
//	/// Get HighlightSubstituteFonts
//	ATEErr (*GetHighlightSubstituteFonts) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
//	/// Set HighlightSubstituteFonts
//	ATEErr (*SetHighlightSubstituteFonts) ( DocumentTextResourcesRef documenttextresources, ATEBool8 value);
//	/// Get HighlightAlternateGlyphs
//	ATEErr (*GetHighlightAlternateGlyphs) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
//	/// Set HighlightAlternateGlyphs
//	ATEErr (*SetHighlightAlternateGlyphs) ( DocumentTextResourcesRef documenttextresources, ATEBool8 value);
//
//}ATE25DocumentTextResourcesSuite;
//
////////////////////////////////////////////////
////       --CharFeaturesSuite--
////////////////////////////////////////////////
//#define kATE25CharFeaturesSuite kCharFeaturesSuite
//#define kCharFeaturesSuiteVersion1 1
//#define kATE25CharFeaturesSuiteVersion kCharFeaturesSuiteVersion1
//
//typedef struct ATE25CharFeaturesSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( CharFeaturesRef charfeatures);
//	void (*Release) ( CharFeaturesRef charfeatures);
//	ATEBool8 (*IsNull) ( CharFeaturesRef charfeatures);
//
//	// CharFeatures is a complete Set of character attributes that
//	// can be applied to text (except for kerning).  They can be used to
//	// describe or Set the (1) local character attributes of text (a.k.a.
//	// the local overrides or (2) attributes of a named character style.
//	//
//	// Often, a given CharFeatures instance will only partially define
//	// each of its attributes.  The validity of an attribute is
//	// determined by an associated boolean.  Calls to "Get" methods
//	// return an "isAssigned" boolean that reflects the validity of
//	// the returned argument.  Calls to "Set" methods always Set the
//	// associated boolean to indicate validity.  Calls to "clear"
//	// methods always invalidate that boolean/attribute pair.
//	//
//	// A character's attribute is determined by an inheritance model.
//	// At the top is the "Normal" style which fully defines all
//	// attributes.  These can be overriden by a named style or a local
//	// override, where an attribute is valid.
//	//
//	// A given attribute value of a character is determined by starting
//	// with the local override for that attribute if it is defined.  If
//	// not, then the attribute comes from the corresponding named style
//	// (if it exists and) if it is defined.  If all else fails, the
//	// default value comes from the "Normal" character style.
//	//
//	// Default constructor creates a "blank" CharFeatures instance where
//	// all attributes are undefined (invalid).
//	ATEErr (*Initialize) ( CharFeaturesRef* charfeatures);
//	ATEErr (*Clone) ( CharFeaturesRef charfeatures, CharFeaturesRef* ret);
//	ATEErr (*GetFont) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontRef* ret);
//	ATEErr (*GetFontSize) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetHorizontalScale) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetVerticalScale) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetAutoLeading) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetLeading) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetTracking) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetBaselineShift) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetCharacterRotation) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	/** Kern type information is only available for CharStyle instances.
//	Use Story::GetKern( ) to obtain kern type information for a TextRange.
//	*/
//	ATEErr (*GetAutoKernType) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, AutoKernType* ret);
//	ATEErr (*GetFontCapsOption) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontCapsOption* ret);
//	ATEErr (*GetFontBaselineOption) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontBaselineOption* ret);
//	ATEErr (*GetFontOpenTypePositionOption) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontOpenTypePositionOption* ret);
//	ATEErr (*GetStrikethroughPosition) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, StrikethroughPosition* ret);
//	ATEErr (*GetUnderlinePosition) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, UnderlinePosition* ret);
//	ATEErr (*GetUnderlineOffset) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	// ------------------------------------------------------------------
//	// OpenType features
//	// ------------------------------------------------------------------
//	ATEErr (*GetLigature) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetDiscretionaryLigatures) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetContextualLigatures) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetAlternateLigatures) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetOldStyle) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetFractions) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetOrdinals) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetSwash) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetTitling) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetConnectionForms) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetStylisticAlternates) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetOrnaments) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetFigureStyle) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FigureStyle* ret);
//	// ------------------------------------------------------------------
//	// Japanese OpenType feature support
//	// ------------------------------------------------------------------
//	ATEErr (*GetProportionalMetrics) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetKana) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetRuby) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetItalics) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetBaselineDirection) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, BaselineDirection* ret);
//	ATEErr (*GetLanguage) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, Language* ret);
//	ATEErr (*GetJapaneseAlternateFeature) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, JapaneseAlternateFeature* ret);
//	ATEErr (*GetTsume) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetStyleRunAlignment) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, StyleRunAlignment* ret);
//	// ------------------------------------------------------------------
//	// WariChu Setings
//	// ------------------------------------------------------------------
//	ATEErr (*GetWariChuEnabled) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetWariChuLineCount) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetWariChuLineGap) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetWariChuScale) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetWariChuSize) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetWariChuWidowAmount) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetWariChuOrphanAmount) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetWariChuJustification) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, WariChuJustification* ret);
//	ATEErr (*GetTCYUpDownAdjustment) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetTCYLeftRightAdjustment) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetLeftAki) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetRightAki) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetNoBreak) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetFillColor) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
//	ATEErr (*GetStrokeColor) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
//	ATEErr (*GetFill) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetStroke) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetFillFirst) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetFillOverPrint) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetStrokeOverPrint) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetLineCap) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, LineCapType* ret);
//	ATEErr (*GetLineJoin) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, LineJoinType* ret);
//	ATEErr (*GetLineWidth) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetMiterLimit) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetLineDashOffset) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetLineDashArray) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ArrayRealRef* ret);
//	// SET PROPERTIES
//	// ======================================================================
//	ATEErr (*SetFont) ( CharFeaturesRef charfeatures, FontRef newVal);
//	/** Set font size
//	This function will throw kOutOfRange error if (newVal > 1296 || newVal < 0.1)
//	*/
//	ATEErr (*SetFontSize) ( CharFeaturesRef charfeatures, ASReal newVal);
//	/** Set Horizontal Scale
//	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
//	If newVal is 1, this means 100% in the character palatte.
//	*/
//	ATEErr (*SetHorizontalScale) ( CharFeaturesRef charfeatures, ASReal newVal);
//	/** Set Vertical Scale
//	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
//	If newVal is 1, this means 100% in the character palatte.
//	*/
//	ATEErr (*SetVerticalScale) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetAutoLeading) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetLeading) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetTracking) ( CharFeaturesRef charfeatures, ASInt32 newVal);
//	ATEErr (*SetBaselineShift) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetCharacterRotation) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetAutoKernType) ( CharFeaturesRef charfeatures, AutoKernType newVal);
//	ATEErr (*SetFontCapsOption) ( CharFeaturesRef charfeatures, FontCapsOption newVal);
//	ATEErr (*SetFontBaselineOption) ( CharFeaturesRef charfeatures, FontBaselineOption newVal);
//	ATEErr (*SetFontOpenTypePositionOption) ( CharFeaturesRef charfeatures, FontOpenTypePositionOption newVal);
//	ATEErr (*SetStrikethroughPosition) ( CharFeaturesRef charfeatures, StrikethroughPosition newVal);
//	ATEErr (*SetUnderlinePosition) ( CharFeaturesRef charfeatures, UnderlinePosition newVal);
//	ATEErr (*SetUnderlineOffset) ( CharFeaturesRef charfeatures, ASReal newVal);
//	// ------------------------------------------------------------------
//	// OpenType features
//	// ------------------------------------------------------------------
//	ATEErr (*SetLigature) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetDiscretionaryLigatures) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetContextualLigatures) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetAlternateLigatures) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetOldStyle) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetFractions) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetOrdinals) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetSwash) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetTitling) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetConnectionForms) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetStylisticAlternates) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetOrnaments) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetFigureStyle) ( CharFeaturesRef charfeatures, FigureStyle newVal);
//	// ------------------------------------------------------------------
//	// Japanese OpenType feature support
//	// ------------------------------------------------------------------
//	ATEErr (*SetProportionalMetrics) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetKana) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetItalics) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetRuby) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetBaselineDirection) ( CharFeaturesRef charfeatures, BaselineDirection newVal);
//	ATEErr (*SetLanguage) ( CharFeaturesRef charfeatures, Language newVal);
//	ATEErr (*SetJapaneseAlternateFeature) ( CharFeaturesRef charfeatures, JapaneseAlternateFeature newVal);
//	ATEErr (*SetTsume) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetStyleRunAlignment) ( CharFeaturesRef charfeatures, StyleRunAlignment newVal);
//	// ------------------------------------------------------------------
//	// WariChu Setings
//	// ------------------------------------------------------------------
//	ATEErr (*SetWariChuEnabled) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetWariChuLineCount) ( CharFeaturesRef charfeatures, ASInt32 newVal);
//	ATEErr (*SetWariChuLineGap) ( CharFeaturesRef charfeatures, ASInt32 newVal);
//	ATEErr (*SetWariChuScale) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetWariChuSize) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetWariChuWidowAmount) ( CharFeaturesRef charfeatures, ASInt32 newVal);
//	ATEErr (*SetWariChuOrphanAmount) ( CharFeaturesRef charfeatures, ASInt32 newVal);
//	ATEErr (*SetWariChuJustification) ( CharFeaturesRef charfeatures, WariChuJustification newVal);
//	ATEErr (*SetTCYUpDownAdjustment) ( CharFeaturesRef charfeatures, ASInt32 newVal);
//	ATEErr (*SetTCYLeftRightAdjustment) ( CharFeaturesRef charfeatures, ASInt32 newVal);
//	ATEErr (*SetLeftAki) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetRightAki) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetNoBreak) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetFillColor) ( CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
//	ATEErr (*SetStrokeColor) ( CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
//	ATEErr (*SetFill) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetStroke) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetFillFirst) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetFillOverPrint) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetStrokeOverPrint) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
//	ATEErr (*SetLineCap) ( CharFeaturesRef charfeatures, LineCapType newVal);
//	ATEErr (*SetLineJoin) ( CharFeaturesRef charfeatures, LineJoinType newVal);
//	ATEErr (*SetLineWidth) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetMiterLimit) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetLineDashOffset) ( CharFeaturesRef charfeatures, ASReal newVal);
//	ATEErr (*SetLineDashArray) ( CharFeaturesRef charfeatures, ArrayRealRef newVal);
//	// CLEAR PROPERTIES
//	// ======================================================================
//	ATEErr (*ClearFont) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFontSize) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearHorizontalScale) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearVerticalScale) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearAutoLeading) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLeading) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearTracking) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearBaselineShift) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearCharacterRotation) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearAutoKernType) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFontCapsOption) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFontBaselineOption) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFontOpenTypePositionOption) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearStrikethroughPosition) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearUnderlinePosition) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearUnderlineOffset) ( CharFeaturesRef charfeatures);
//	// ------------------------------------------------------------------
//	// OpenType features
//	// ------------------------------------------------------------------
//	ATEErr (*ClearLigature) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearDiscretionaryLigatures) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearContextualLigatures) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearAlternateLigatures) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearOldStyle) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFractions) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearOrdinals) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearSwash) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearTitling) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearConnectionForms) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearStylisticAlternates) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearOrnaments) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFigureStyle) ( CharFeaturesRef charfeatures);
//	// ------------------------------------------------------------------
//	// Japanese OpenType feature support
//	// ------------------------------------------------------------------
//	ATEErr (*ClearProportionalMetrics) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearKana) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearItalics) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearRuby) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearBaselineDirection) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLanguage) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearJapaneseAlternateFeature) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearTsume) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearStyleRunAlignment) ( CharFeaturesRef charfeatures);
//	// ------------------------------------------------------------------
//	// WariChu Setings
//	// ------------------------------------------------------------------
//	ATEErr (*ClearWariChuEnabled) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearWariChuLineCount) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearWariChuLineGap) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearWariChuSubLineAmount) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearWariChuWidowAmount) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearWariChuOrphanAmount) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearWariChuJustification) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearTCYUpDownAdjustment) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearTCYLeftRightAdjustment) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLeftAki) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearRightAki) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearNoBreak) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFillColor) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearStrokeColor) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFill) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearStroke) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFillFirst) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearFillOverPrint) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearStrokeOverPrint) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLineCap) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLineJoin) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLineWidth) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearMiterLimit) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLineDashOffset) ( CharFeaturesRef charfeatures);
//	ATEErr (*ClearLineDashArray) ( CharFeaturesRef charfeatures);
//	// ALGEBRA METHODS
//	// Methods return true if changes were made.
//	// ======================================================================
//	// Intersection of 2 Features is the intersection of each attribute
//	//  on the lhs with the corresponding attribute on the rhs.
//	//  Attribute intersections are defined by the following truth table:
//	//
//	// ______________________________________________________________________
//	//  this.attribute | rhs.attribute || Action/Result
//	// ======================================================================
//	//  assigned  | assigned  || [Case 1] If values are equal
//	//      |    ||  ACTION: nothing
//	//      |    ||  RESULT: value preserved
//	//      |    || [Case 2] If values are not equal
//	//      |    ||  ACTION: if (*this.attribute != *rhs.attribute)
//	//      |    ||      this.attribute.Clear();
//	//      |    ||  RESULT: unassigned
//	// ----------------------------------------------------------------------
//	//  assigned  | unassigned || ACTION: this.attribute.Clear()
//	//     |    || RESULT: unassigned
//	// ----------------------------------------------------------------------
//	//  unassigned  | assigned  || ACTION: nothing (this.attribute already unassigned)
//	//     |    || RESULT: unassigned
//	// ----------------------------------------------------------------------
//	//  unassigned  | unassigned || ACTION: nothing (both are equal)
//	//     |    || RESULT: unassigned
//	// ______________________________________________________________________
//	//
//	ATEErr (*IntersectFeatures) ( CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
//	// ReplaceOrAddFeatures sets the attribute value for any that are assigned on the rhs.
//	ATEErr (*ReplaceOrAddFeatures) ( CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
//	// Unassigns each attribute whose value equals value of corresponding attribute in rhs
//	ATEErr (*UnassignEachIfEqual) ( CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
//	// True if all are not assigned; false otherwise
//	ATEErr (*IsEachNotAssigned) ( CharFeaturesRef charfeatures, ATEBool8* ret);
//	// True if all are assigned; false otherwise
//	ATEErr (*IsEachAssigned) ( CharFeaturesRef charfeatures, ATEBool8* ret);
//	// ACCESSORS DESIGNED FOR CLIENT APPLICATION CORE
//	// ======================================================================
//
//}ATE25CharFeaturesSuite;
//
////////////////////////////////////////////////
////       --CharInspectorSuite--
////////////////////////////////////////////////
//#define kATE25CharInspectorSuite kCharInspectorSuite
//#define kCharInspectorSuiteVersion1 1
//#define kATE25CharInspectorSuiteVersion kCharInspectorSuiteVersion1
//
//typedef struct ATE25CharInspectorSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( CharInspectorRef charinspector);
//	void (*Release) ( CharInspectorRef charinspector);
//	ATEBool8 (*IsNull) ( CharInspectorRef charinspector);
//
//	ATEErr (*Initialize) ( CharInspectorRef* charinspector);
//	ATEErr (*GetFont) ( CharInspectorRef charinspector, ArrayFontRefRef* ret);
//	ATEErr (*GetFontSize) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetHorizontalScale) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetVerticalScale) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetSyntheticBold) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetSyntheticItalic) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetAutoLeading) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetLeading) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetTracking) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
//	ATEErr (*GetBaselineShift) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetCharacterRotation) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetFontCapsOption) ( CharInspectorRef charinspector, ArrayFontCapsOptionRef* ret);
//	ATEErr (*GetFontBaselineOption) ( CharInspectorRef charinspector, ArrayFontBaselineOptionRef* ret);
//	ATEErr (*GetFontOpenTypePositionOption) ( CharInspectorRef charinspector, ArrayFontOpenTypePositionOptionRef* ret);
//	ATEErr (*GetStrikethroughPosition) ( CharInspectorRef charinspector, ArrayStrikethroughPositionRef* ret);
//	ATEErr (*GetUnderlinePosition) ( CharInspectorRef charinspector, ArrayUnderlinePositionRef* ret);
//	ATEErr (*GetUnderlineOffset) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	// ------------------------------------------------------------------
//	// OpenType features
//	// ------------------------------------------------------------------
//	ATEErr (*GetLigature) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetDiscretionaryLigatures) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetContextualLigatures) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetAlternateLigatures) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetOldStyle) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetFractions) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetOrdinals) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetSwash) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetTitling) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetConnectionForms) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetStylisticAlternates) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetOrnaments) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetFigureStyle) ( CharInspectorRef charinspector, ArrayFigureStyleRef* ret);
//	// ------------------------------------------------------------------
//	// Japanese OpenType feature support
//	// ------------------------------------------------------------------
//	ATEErr (*GetProportionalMetrics) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetKana) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetItalics) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetRuby) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetBaselineDirection) ( CharInspectorRef charinspector, ArrayBaselineDirectionRef* ret);
//	ATEErr (*GetLanguage) ( CharInspectorRef charinspector, ArrayLanguageRef* ret);
//	ATEErr (*GetTsume) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetStyleRunAlignment) ( CharInspectorRef charinspector, ArrayStyleRunAlignmentRef* ret);
//	// ------------------------------------------------------------------
//	// WariChu Setings
//	// ------------------------------------------------------------------
//	ATEErr (*GetWariChuLineCount) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
//	ATEErr (*GetWariChuLineGap) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
//	ATEErr (*GetWariChuScale) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetWariChuSize) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetWariChuWidowAmount) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
//	ATEErr (*GetWariChuOrphanAmount) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
//	ATEErr (*GetWariChuJustification) ( CharInspectorRef charinspector, ArrayWariChuJustificationRef* ret);
//	ATEErr (*GetWariChuEnabled) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetTCYUpDownAdjustment) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
//	ATEErr (*GetTCYLeftRightAdjustment) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
//	ATEErr (*GetLeftAki) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetRightAki) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetNoBreak) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetFillColor) ( CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
//	ATEErr (*GetStrokeColor) ( CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
//	ATEErr (*GetFill) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetStroke) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetFillFirst) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetFillOverPrint) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetStrokeOverPrint) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
//	ATEErr (*GetLineCap) ( CharInspectorRef charinspector, ArrayLineCapTypeRef* ret);
//	ATEErr (*GetLineJoin) ( CharInspectorRef charinspector, ArrayLineJoinTypeRef* ret);
//	ATEErr (*GetLineWidth) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetMiterLimit) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetLineDashOffset) ( CharInspectorRef charinspector, ArrayRealRef* ret);
//	ATEErr (*GetLineDashArray) ( CharInspectorRef charinspector, ArrayArrayRealRef* ret);
//
//}ATE25CharInspectorSuite;
//
////////////////////////////////////////////////
////       --FindSuite--
////////////////////////////////////////////////
//#define kATE25FindSuite kFindSuite
//#define kFindSuiteVersion1 1
//#define kATE25FindSuiteVersion kFindSuiteVersion1
//
//typedef struct ATE25FindSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( FindRef find);
//	void (*Release) ( FindRef find);
//	ATEBool8 (*IsNull) ( FindRef find);
//
//	// Options
//	// ========================================================================
//	ATEErr (*GetSearchDirection) ( FindRef find, Direction* ret);
//	ATEErr (*GetIgnoreCase) ( FindRef find, ATEBool8* ret);
//	ATEErr (*GetWholeWord) ( FindRef find, ATEBool8* ret);
//	ATEErr (*GetWrap) ( FindRef find, ATEBool8* ret);
//	ATEErr (*GetFindWordsOutOfBounds) ( FindRef find, ATEBool8* ret);
//	ATEErr (*SetSearchDirection) ( FindRef find, Direction newValue);
//	ATEErr (*SetIgnoreCase) ( FindRef find, ATEBool8 newValue);
//	ATEErr (*SetWholeWord) ( FindRef find, ATEBool8 newValue);
//	ATEErr (*SetWrap) ( FindRef find, ATEBool8 newValue);
//	ATEErr (*SetFindWordsOutOfBounds) ( FindRef find, ATEBool8 newValue);
//	// Control scope of search to be entire document or Story.
//	// By default, the entire document is searched.
//	ATEErr (*GetSearchScope) ( FindRef find, SearchScope* ret);
//	ATEErr (*SetSearchScope) ( FindRef find, SearchScope searchScope);
//	// If called, search is done only within specified TextRange
//	ATEErr (*SetSearchRange) ( FindRef find, TextRangeRef pRange);
//	ATEErr (*SetSearchChars) ( FindRef find, ASUnicode* pSearchChars);
//	ATEErr (*GetSearchChars) ( FindRef find, ASUnicode* pSearchChars, ASInt32 length);
//	ATEErr (*SetReplaceChars) ( FindRef find, ASUnicode* pSearchChars);
//	ATEErr (*GetReplaceChars) ( FindRef find, ASUnicode* pSearchChars, ASInt32 length);
//	// Temporary way to reset the engine for modeless operation
//	ATEErr (*Reset) ( FindRef find);
//	// Methods
//	// ========================================================================
//	// Searches current user selection.
//	// Returns false if the search failed
//	ATEErr (*FindMatch) ( FindRef find, TextRangeRef pTextRange, ATEBool8* ret);
//	// Skips the current user selection.
//	// Returns false if the search failed
//	ATEErr (*FindNextMatch) ( FindRef find, TextRangeRef pTextRange, ATEBool8* ret);
//	ATEErr (*ReplaceMatch) ( FindRef find, TextRangeRef pTextRange, ATEBool8 findNext, ATEBool8* ret);
//	// DEPRECATED - this is now a no-op.  Use GetPreReplaceAllSettings( ) and
//	// RestorePreReplaceAllSettings( ) to implement ReplaceAll in the plugin.
//	ATEErr (*FindAndReplaceAllMatches) ( FindRef find, ASInt32* pReplaceCount, ATEBool8* ret);
//	// Use these to implement ReplaceAll.
//	// Start by saving off the settings with GetPreReplaceAllSettings( )
//	// (also note what text object you're currently working with so you can restore that
//	// via SetSearchRange( ) when you're finished.
//	ATEErr (*GetPreReplaceAllSettings) ( FindRef find, ASInt32* pCurrentPoint, ASInt32* pStartPoint);
//	// Implement a loop to go through all the text objects you want to replace all with.
//	// Use FindMatch( ), FindNextMatch( ), and ReplaceMatch( ) to replace all.
//	// Keep track of how many ReplaceMatch( ) calls were made for reporting back to the user
//	// When finished, restore the correct text object and range using SetSearchRange( )
//	// and restore the positions using RestorePreReplaceAllSettings( )
//	ATEErr (*RestorePreReplaceAllSettings) ( FindRef find, const ASInt32 currentPoint, const ASInt32 startPoint);
//
//}ATE25FindSuite;
//
////////////////////////////////////////////////
////       --ParaFeaturesSuite--
////////////////////////////////////////////////
//#define kATE25ParaFeaturesSuite kParaFeaturesSuite
//#define kParaFeaturesSuiteVersion1 1
//#define kATE25ParaFeaturesSuiteVersion kParaFeaturesSuiteVersion1
//
//typedef struct ATE25ParaFeaturesSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( ParaFeaturesRef parafeatures);
//	void (*Release) ( ParaFeaturesRef parafeatures);
//	ATEBool8 (*IsNull) ( ParaFeaturesRef parafeatures);
//
//	// ParaFeatures is a complete Set of paragraph attributes that
//	// can be applied to text (except for kerning).  They can be used to
//	// describe or Set the (1) local paragraph attributes of text (a.k.a.
//	// the local overrides or (2) attributes of a named paragraph style.
//	//
//	// Often, a given ParaFeatures instance will only partially define
//	// each of its attributes.  The validity of an attribute is
//	// determined by an associated boolean.  Calls to "Get" methods
//	// return an "isAssigned" boolean that reflects the validity of
//	// the returned argument.  Calls to "Set" methods always Set the
//	// associated boolean to indicate validity.  Calls to "Clear"
//	// methods always invalidate that boolean/attribute pair.
//	//
//	// A paragraph's attribute is determined by an inheritance model.
//	// At the top is the "Normal" style which fully defines all
//	// attributes.  These can be overriden by a named style or a local
//	// override, where an attribute is valid.
//	//
//	// A given attribute value of a paragraph is determined by starting
//	// with the local override for that attribute if it is defined.  If
//	// not, then the attribute comes from the corresponding named style
//	// (if it exists and) if it is defined.  If all else fails, the
//	// default value comes from the "Normal" paragraph style.
//	//
//	// Default constructor creates a "blank" ParaFeatures instance where
//	// all attributes are undefined (invalid).
//	ATEErr (*Initialize) ( ParaFeaturesRef* parafeatures);
//	ATEErr (*Clone) ( ParaFeaturesRef parafeatures, ParaFeaturesRef* ret);
//	// ------------------------------------------------------------------
//	// Justification
//	// ------------------------------------------------------------------
//	ATEErr (*GetJustification) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ParagraphJustification* ret);
//	ATEErr (*GetFirstLineIndent) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetStartIndent) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetEndIndent) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetSpaceBefore) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetSpaceAfter) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	// ------------------------------------------------------------------
//	// Hyphenation
//	// ------------------------------------------------------------------
//	ATEErr (*GetAutoHyphenate) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetHyphenatedWordSize) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetPreHyphenSize) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetPostHyphenSize) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetConsecutiveHyphenLimit) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetHyphenationZone) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetHyphenateCapitalized) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetHyphenationPreference) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	// ------------------------------------------------------------------
//	// Justification Features
//	// ------------------------------------------------------------------
//	ATEErr (*GetDesiredWordSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetMaxWordSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetMinWordSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetDesiredLetterSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetMaxLetterSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetMinLetterSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetDesiredGlyphScaling) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetMaxGlyphScaling) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetMinGlyphScaling) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetSingleWordJustification) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ParagraphJustification* ret);
//	ATEErr (*GetAutoLeadingPercentage) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	ATEErr (*GetLeadingType) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, LeadingType* ret);
//	ATEErr (*GetTabStops) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, TabStopsRef* ret);
//	ATEErr (*GetDefaultTabWidth) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASReal* ret);
//	// ------------------------------------------------------------------
//	// Japanese Features
//	// ------------------------------------------------------------------
//	ATEErr (*GetHangingRoman) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetAutoTCY) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ASInt32* ret);
//	ATEErr (*GetBunriKinshi) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetBurasagariType) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, BurasagariType* ret);
//	ATEErr (*GetPreferredKinsokuOrder) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, PreferredKinsokuOrder* ret);
//	ATEErr (*GetKurikaeshiMojiShori) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	/// This will return a null object if Kinsoku is not used (ie None set)
//	ATEErr (*GetKinsoku) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, KinsokuRef* ret);
//	/// This will return a null object if Mojikumi is not used (ie None set)
//	ATEErr (*GetMojiKumi) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, MojiKumiRef* ret);
//	// Other
//	ATEErr (*GetEveryLineComposer) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
//	ATEErr (*GetDefaultCharFeatures) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, CharFeaturesRef* ret);
//	// SET PROPERTIES
//	// ======================================================================
//	// ------------------------------------------------------------------
//	// Justification
//	// ------------------------------------------------------------------
//	ATEErr (*SetJustification) ( ParaFeaturesRef parafeatures, ParagraphJustification newVal);
//	ATEErr (*SetFirstLineIndent) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetStartIndent) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetEndIndent) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetSpaceBefore) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetSpaceAfter) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	// ------------------------------------------------------------------
//	// Hyphenation
//	// ------------------------------------------------------------------
//	ATEErr (*SetAutoHyphenate) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
//	ATEErr (*SetHyphenatedWordSize) ( ParaFeaturesRef parafeatures, ASInt32 newVal);
//	ATEErr (*SetPreHyphenSize) ( ParaFeaturesRef parafeatures, ASInt32 newVal);
//	ATEErr (*SetPostHyphenSize) ( ParaFeaturesRef parafeatures, ASInt32 newVal);
//	ATEErr (*SetConsecutiveHyphenLimit) ( ParaFeaturesRef parafeatures, ASInt32 newVal);
//	ATEErr (*SetHyphenationZone) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetHyphenateCapitalized) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
//	ATEErr (*SetHyphenationPreference) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	// ------------------------------------------------------------------
//	// Justification Features
//	// ------------------------------------------------------------------
//	ATEErr (*SetDesiredWordSpacing) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetMaxWordSpacing) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetMinWordSpacing) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetDesiredLetterSpacing) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetMaxLetterSpacing) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetMinLetterSpacing) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetDesiredGlyphScaling) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetMaxGlyphScaling) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetMinGlyphScaling) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetSingleWordJustification) ( ParaFeaturesRef parafeatures, ParagraphJustification newVal);
//	ATEErr (*SetAutoLeadingPercentage) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	ATEErr (*SetLeadingType) ( ParaFeaturesRef parafeatures, LeadingType newVal);
//	ATEErr (*SetTabStops) ( ParaFeaturesRef parafeatures, TabStopsRef newVal);
//	ATEErr (*SetDefaultTabWidth) ( ParaFeaturesRef parafeatures, ASReal newVal);
//	// ------------------------------------------------------------------
//	// Japanese Features
//	// ------------------------------------------------------------------
//	ATEErr (*SetHangingRoman) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
//	ATEErr (*SetAutoTCY) ( ParaFeaturesRef parafeatures, ASInt32 newVal);
//	ATEErr (*SetBunriKinshi) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
//	ATEErr (*SetBurasagariType) ( ParaFeaturesRef parafeatures, BurasagariType newVal);
//	ATEErr (*SetPreferredKinsokuOrder) ( ParaFeaturesRef parafeatures, PreferredKinsokuOrder newVal);
//	ATEErr (*SetKurikaeshiMojiShori) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
//	ATEErr (*SetKinsoku) ( ParaFeaturesRef parafeatures, KinsokuRef newVal);
//	ATEErr (*SetMojiKumi) ( ParaFeaturesRef parafeatures, MojiKumiRef newVal);
//	// Other
//	ATEErr (*SetEveryLineComposer) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
//	ATEErr (*SetDefaultCharFeatures) ( ParaFeaturesRef parafeatures, CharFeaturesRef newVal);
//	// CLEAR PROPERTIES
//	// ======================================================================
//	// ------------------------------------------------------------------
//	// Justification
//	// ------------------------------------------------------------------
//	ATEErr (*ClearJustification) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearFirstLineIndent) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearStartIndent) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearEndIndent) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearSpaceBefore) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearSpaceAfter) ( ParaFeaturesRef parafeatures);
//	// ------------------------------------------------------------------
//	// Hyphenation
//	// ------------------------------------------------------------------
//	ATEErr (*ClearAutoHyphenate) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearHyphenatedWordSize) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearPreHyphenSize) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearPostHyphenSize) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearConsecutiveHyphenLimit) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearHyphenationZone) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearHyphenateCapitalized) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearHyphenationPreference) ( ParaFeaturesRef parafeatures);
//	// ------------------------------------------------------------------
//	// Justification Features
//	// ------------------------------------------------------------------
//	ATEErr (*ClearWordSpacing) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearLetterSpacing) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearGlyphScaling) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearSingleWordJustification) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearAutoLeadingPercentage) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearLeadingType) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearTabStops) ( ParaFeaturesRef parafeatures);
//	// ------------------------------------------------------------------
//	// Japanese Features
//	// ------------------------------------------------------------------
//	ATEErr (*ClearHangingRoman) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearAutoTCY) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearBunriKinshi) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearBurasagariType) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearPreferredKinsokuOrder) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearKurikaeshiMojiShori) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearKinsoku) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearMojiKumi) ( ParaFeaturesRef parafeatures);
//	// Other
//	ATEErr (*ClearEveryLineComposer) ( ParaFeaturesRef parafeatures);
//	ATEErr (*ClearDefaultCharFeatures) ( ParaFeaturesRef parafeatures);
//	// ALGEBRA METHODS
//	// Methods return true if changes were made.
//	// ======================================================================
//	// Intersection of 2 Features is the intersection of each attribute
//	//  on the lhs with the corresponding attribute on the rhs.
//	//  Attribute intersections are defined by the following truth table:
//	//
//	// ______________________________________________________________________
//	//  this.attribute | rhs.attribute || Action/Result
//	// ======================================================================
//	//  assigned  | assigned  || [Case 1] If values are equal
//	//      |    ||  ACTION: nothing
//	//      |    ||  RESULT: value preserved
//	//      |    || [Case 2] If values are not equal
//	//      |    ||  ACTION: if (*this.attribute != *rhs.attribute)
//	//      |    ||      this.attribute.Clear();
//	//      |    ||  RESULT: unassigned
//	// ----------------------------------------------------------------------
//	//  assigned  | unassigned || ACTION: this.attribute.Clear()
//	//     |    || RESULT: unassigned
//	// ----------------------------------------------------------------------
//	//  unassigned  | assigned  || ACTION: nothing (this.attribute already unassigned)
//	//     |    || RESULT: unassigned
//	// ----------------------------------------------------------------------
//	//  unassigned  | unassigned || ACTION: nothing (both are equal)
//	//     |    || RESULT: unassigned
//	// ______________________________________________________________________
//	//
//	ATEErr (*IntersectFeatures) ( ParaFeaturesRef parafeatures, ParaFeaturesRef rhs, ATEBool8* ret);
//	// ReplaceOrAddFeatures sets the attribute value for any that are assigned on the rhs.
//	ATEErr (*ReplaceOrAddFeatures) ( ParaFeaturesRef parafeatures, ParaFeaturesRef rhs, ATEBool8* ret);
//	// Unassigns each attribute whose value equals value of corresponding attribute in rhs
//	ATEErr (*UnassignEachIfEqual) ( ParaFeaturesRef parafeatures, const ParaFeaturesRef rhs, ATEBool8* ret);
//	// True if all are not assigned; false otherwise
//	ATEErr (*IsEachNotAssigned) ( ParaFeaturesRef parafeatures, ATEBool8* ret);
//	// True if all are assigned; false otherwise
//	ATEErr (*IsEachAssigned) ( ParaFeaturesRef parafeatures, ATEBool8* ret);
//	// PRIVATE AND PROTECTED
//	// ======================================================================
//
//}ATE25ParaFeaturesSuite;
//
////////////////////////////////////////////////
////       --ParaInspectorSuite--
////////////////////////////////////////////////
//#define kATE25ParaInspectorSuite kParaInspectorSuite
//#define kParaInspectorSuiteVersion1 1
//#define kATE25ParaInspectorSuiteVersion kParaInspectorSuiteVersion1
//
//typedef struct ATE25ParaInspectorSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( ParaInspectorRef parainspector);
//	void (*Release) ( ParaInspectorRef parainspector);
//	ATEBool8 (*IsNull) ( ParaInspectorRef parainspector);
//
//	ATEErr (*Initialize) ( ParaInspectorRef* parainspector);
//	// ------------------------------------------------------------------
//	// Justification
//	// ------------------------------------------------------------------
//	ATEErr (*GetJustification) ( ParaInspectorRef parainspector, ArrayParagraphJustificationRef* ret);
//	ATEErr (*GetFirstLineIndent) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetStartIndent) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetEndIndent) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetSpaceBefore) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetSpaceAfter) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	// ------------------------------------------------------------------
//	// Hyphenation
//	// ------------------------------------------------------------------
//	ATEErr (*GetAutoHyphenate) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
//	ATEErr (*GetHyphenatedWordSize) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
//	ATEErr (*GetPreHyphenSize) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
//	ATEErr (*GetPostHyphenSize) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
//	ATEErr (*GetConsecutiveHyphenLimit) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
//	ATEErr (*GetHyphenationZone) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetHyphenateCapitalized) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
//	ATEErr (*GetHyphenationPreference) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	// ------------------------------------------------------------------
//	// Justification Features
//	// ------------------------------------------------------------------
//	ATEErr (*GetDesiredWordSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetMaxWordSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetMinWordSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetDesiredLetterSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetMaxLetterSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetMinLetterSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetDesiredGlyphScaling) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetMaxGlyphScaling) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetMinGlyphScaling) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetSingleWordJustification) ( ParaInspectorRef parainspector, ArrayParagraphJustificationRef* ret);
//	ATEErr (*GetAutoLeadingPercentage) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	ATEErr (*GetLeadingType) ( ParaInspectorRef parainspector, ArrayLeadingTypeRef* ret);
//	ATEErr (*GetTabStops) ( ParaInspectorRef parainspector, ArrayTabStopsRefRef* ret);
//	ATEErr (*GetDefaultTabWidth) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
//	// ------------------------------------------------------------------
//	// Japanese Features
//	// ------------------------------------------------------------------
//	ATEErr (*GetHangingRoman) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
//	ATEErr (*GetAutoTCY) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
//	ATEErr (*GetBunriKinshi) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
//	ATEErr (*GetBurasagariType) ( ParaInspectorRef parainspector, ArrayBurasagariTypeRef* ret);
//	ATEErr (*GetPreferredKinsokuOrder) ( ParaInspectorRef parainspector, ArrayPreferredKinsokuOrderRef* ret);
//	ATEErr (*GetKurikaeshiMojiShori) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
//	ATEErr (*GetKinsoku) ( ParaInspectorRef parainspector, ArrayKinsokuRefRef* ret);
//	ATEErr (*GetMojiKumi) ( ParaInspectorRef parainspector, ArrayMojiKumiRefRef* ret);
//	// Other
//	ATEErr (*GetEveryLineComposer) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
//
//}ATE25ParaInspectorSuite;
//
////////////////////////////////////////////////
////       --SpellSuite--
////////////////////////////////////////////////
//#define kATE25SpellSuite kSpellSuite
//#define kSpellSuiteVersion1 1
//#define kATE25SpellSuiteVersion kSpellSuiteVersion1
//
//typedef struct ATE25SpellSuite{
//
//	// Reference count maintenance.
//	void (*AddRef) ( SpellRef spell);
//	void (*Release) ( SpellRef spell);
//	ATEBool8 (*IsNull) ( SpellRef spell);
//
//	// Options
//	// ========================================================================
//	ATEErr (*Initialize) ( SpellRef spell, const char* pSpellingDirectory);
//	ATEErr (*IsInitialized) ( SpellRef spell, ATEBool8* ret);
//	ATEErr (*GetIgnoreWordsInAllUppercase) ( SpellRef spell, ATEBool8* ret);
//	ATEErr (*GetIgnoreWordsWithNumbers) ( SpellRef spell, ATEBool8* ret);
//	ATEErr (*GetIgnoreRomanNumerals) ( SpellRef spell, ATEBool8* ret);
//	ATEErr (*GetIgnoreRepeatedWords) ( SpellRef spell, ATEBool8* ret);
//	ATEErr (*GetIgnoreUncapitalizedStartOfSentence) ( SpellRef spell, ATEBool8* ret);
//	ATEErr (*SetIgnoreWordsInAllUppercase) ( SpellRef spell, ATEBool8 newValue);
//	ATEErr (*SetIgnoreWordsWithNumbers) ( SpellRef spell, ATEBool8 newValue);
//	ATEErr (*SetIgnoreRomanNumerals) ( SpellRef spell, ATEBool8 newValue);
//	ATEErr (*SetIgnoreRepeatedWords) ( SpellRef spell, ATEBool8 newValue);
//	ATEErr (*SetIgnoreUncapitalizedStartOfSentence) ( SpellRef spell, ATEBool8 newValue);
//	// Control scope of search to be entire document or Story.
//	// By default, the entire document is searched.
//	ATEErr (*GetSearchScope) ( SpellRef spell, SearchScope* ret);
//	ATEErr (*SetSearchScope) ( SpellRef spell, SearchScope searchScope);
//	// If called, search is done only within specified TextRange
//	ATEErr (*SetSearchRange) ( SpellRef spell, const TextRangeRef pRange, const ATEBool8 resetEndOfSentence, const ATEBool8 resetCurPos);
//	// Temporary way to reset the engine for modeless operation
//	ATEErr (*Reset) ( SpellRef spell);
//	// Use this if the user changes the text significantly enough that you need to reset,
//	// but are fairly certain that the text hasn't been changed before the resumePoint.
//	ATEErr (*ResumeFrom) ( SpellRef spell, const ASInt32 resumePoint);
//	// Use this to resume from the current insertion point.
//	ATEErr (*ResumeFromInsertionPoint) ( SpellRef spell);
//	// Methods
//	// ========================================================================
//	// Searches from start for unknown words and return the first one it finds.
//	// Returns true if it found an unknown word, false if it searched to the end
//	// and didn't find any unknown words.
//	ATEErr (*FindOneMisspelledWord) ( SpellRef spell, SpellCheckingResult* pResult, TextRangeRef pRange, Language* pLanguage, ATEBool8* ret);
//	// Calling FindOneMisspelledWord( ) will fill up an internal list of suggested
//	// corrections.  Use these calls to get the contents of that word list:
//	//
//	// This will return the size of the buffer required to hold the contents of the word list.
//	ATEErr (*GetWordListSize) ( SpellRef spell, ASInt32* ret);
//	//
//	// This will fill up pWordListBuffer with the contents of the list.
//	// sizeOfBuffer is the size of pWordListBuffer (used to prevent overflow)
//	// pNumberOfWords is the number of words in the buffer.  The words are all null-terminated.
//	ATEErr (*GetWordListContents) ( SpellRef spell, ASUnicode*   pWordListBuffer, ASInt32    sizeOfBuffer, ASInt32*   pNumberOfWords);
//	ATEErr (*Replace) ( SpellRef spell, TextRangeRef pRange, const ASUnicode* pCorrection );
//	// Use this to add an entry to a pair dictionary, binding the selected word to rCorrection.
//	ATEErr (*AddSelectedToReplaceAllDict) ( SpellRef spell, const ASUnicode* pCorrection);
//	// DEPRECATED - this is now a no-op.  Use GetPreReplaceAllSettings( ) and
//	// RestorePreReplaceAllSettings( ) to implement ReplaceAll in the plugin.
//	ATEErr (*DoReplaceAll) ( SpellRef spell, ATEBool8* ret);
//	// Use these to implement ReplaceAll.
//	// Start by saving off the settings with GetPreReplaceAllSettings( )
//	// (also note what text object you're currently working with so you can restore that
//	// via SetSearchRange( ) when you're finished.
//	ATEErr (*GetPreReplaceAllSettings) ( SpellRef spell, ASInt32* pCurrentPoint, ATEBool8* pFoundSentenceEnd);
//	// Implement a loop to go through all the text objects you want to replace all with.
//	// Use this to find all instances of the target word in the current text object.
//	// Keep calling it until it returns false, making sure to set firstTimeInThisObject as needed.
//	// It will return the text range to select and call ReplaceSelected( ) with.
//	ATEErr (*FindReplaceAllWord) ( SpellRef spell, TextRangeRef pRange, const ATEBool8 firstTimeInThisObject, ATEBool8* ret);
//	// When finished, restore the correct text object and range using SetSearchRange( )
//	// and restore the positions using RestorePreReplaceAllSettings( )
//	// Order is important here - do notcall RestorePreReplaceAllSettings( ) first,
//	// as SetSearchRange( ) will reset the foundSentenceEnd flag.
//	ATEErr (*RestorePreReplaceAllSettings) ( SpellRef spell, const ASInt32 currentPoint, const ATEBool8 foundSentenceEnd);
//	// The pair dictionary is not automatically cleared.  Call this when you want it cleared.
//	ATEErr (*ClearPairDictionary) ( SpellRef spell);
//	// Use this for adding words as they're found.
//	ATEErr (*AddSelectedToUserDict) ( SpellRef spell);
//	// User dictionary access and maintenance - used to manage the dictionary at any time.
//	//
//	// Calling GetUserDictionaryContents( ) will fill up the same internal list as FindAndSelectOneMisspelledWord( )
//	// Use GetWordListSize( ) and GetWordListContents( ) just like with the suggestion list.
//	ATEErr (*GetUserDictionaryContents) ( SpellRef spell);
//	// now makes sure that there are no spaces (multiple words)
//	// Return value reflects success in adding legit word.
//	ATEErr (*AddToUserDictionary) ( SpellRef spell, const ASUnicode* pWord, ATEBool8* ret);
//	ATEErr (*DeleteFromUserDictionary) ( SpellRef spell, const ASUnicode* pWord);
//	ATEErr (*WordExistsInUserDictionary) ( SpellRef spell, const ASUnicode* pWord, ATEBool8* ret);
//	// The ignore list is used for storing "ignore all" words.
//	ATEErr (*AddSelectedToIgnoreList) ( SpellRef spell);
//	// The ignore list is not automatically cleared.  Call this when you want it cleared.
//	ATEErr (*ClearIgnoreList) ( SpellRef spell);
//	ATEErr (*GetLanguageOfLastMissingDictionary) ( SpellRef spell, Language* ret);
//
//}ATE25SpellSuite;
//
//#ifdef MAC_ENV
//	#pragma options align=reset
//#endif
//
//#ifdef WIN_ENV
//	#pragma pack(pop)
//#endif
//
//#ifdef __cplusplus
//}// namespace ATE
//}
//#endif
//
//#endif //__ATE25Suites__