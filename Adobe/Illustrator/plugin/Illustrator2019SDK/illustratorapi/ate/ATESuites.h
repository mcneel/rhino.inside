/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	ATESuites.h
		
	Notes:	Machine Generated file from script version 1.45
	        Please don't modify manually!
	
 ---------------------------------------------------------------------------------- */
#ifndef __ATESuites__
#define __ATESuites__

#include "SloTextdomTypes.h"
#include "ATETypes.h"
#include "ATETypesDef.h"
#ifdef __cplusplus
namespace ATE
{
extern  "C" {
#endif

#ifdef MAC_ENV
	#if defined (__MWERKS__)
		#pragma options align=power_gcc
	#elif defined (__GNUC__)
		#pragma options align=power
	#endif
#endif

#ifdef WIN_ENV
	#pragma pack(push, 4)
#endif

//////////////////////////////////////////////
//       --ApplicationPaintSuite--
//////////////////////////////////////////////
#define kApplicationPaintSuite "ATE ApplicationPaint Suite"
#define kApplicationPaintSuiteVersion1 1
#define kApplicationPaintSuiteVersion kApplicationPaintSuiteVersion1

typedef struct ApplicationPaintSuite{

	// Reference count maintenance.
	void (*AddRef) ( ApplicationPaintRef applicationpaint);
	void (*Release) ( ApplicationPaintRef applicationpaint);
	ATEBool8 (*IsNull) ( ApplicationPaintRef applicationpaint);


}ApplicationPaintSuite;

//////////////////////////////////////////////
//       --CompFontSuite--
//////////////////////////////////////////////
#define kCompFontSuite "ATE CompFont Suite"
#define kCompFontSuiteVersion1 1
#define kCompFontSuiteVersion kCompFontSuiteVersion1

typedef struct CompFontSuite{

	// Reference count maintenance.
	void (*AddRef) ( CompFontRef compfont);
	void (*Release) ( CompFontRef compfont);
	ATEBool8 (*IsNull) ( CompFontRef compfont);

	ATEErr (*Initialize) ( TextResourcesRef pResources, CompFontRef* compfont);
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetNativeName) ( CompFontRef compfont, ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength);
	// The PostScript name will be automatically derived from the NativeName.
	ATEErr (*SetNativeName) ( CompFontRef compfont, const ATETextDOM::Unicode* name);
	ATEErr (*GetPostScriptName_AsUnicode) ( CompFontRef compfont, ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength);
	ATEErr (*GetPostScriptName_AsChar) ( CompFontRef compfont, char* name, ATETextDOM::Int32 maxLength);
	ATEErr (*SetFontDictionary) ( CompFontRef compfont, void* fontDictionary);
	ATEErr (*GetFontDictionary) ( CompFontRef compfont, void** ret);
	// METHODS
	// =======================================================================
	ATEErr (*Duplicate) ( CompFontRef compfont, CompFontRef* ret);
	// Has the resource been modified since it became editable?
	ATEErr (*IsModified) ( CompFontRef compfont, ATEBool8* ret);
	ATEErr (*IsEditable) ( CompFontRef compfont, ATEBool8* ret);
	ATEErr (*IsCommitted) ( CompFontRef compfont, ATEBool8* ret);
	// Is the font in a valid state, either editable or committed?
	ATEErr (*VerifyState) ( CompFontRef compfont, ATEBool8* ret);
	ATEErr (*IsATCFileLoaded) ( CompFontRef compfont, ATEBool8* ret);
	ATEErr (*GetComponentCount) ( CompFontRef compfont, ATETextDOM::Int32* ret);
	ATEErr (*GetComponent) ( CompFontRef compfont, ATETextDOM::Int32 index, CompFontComponentRef* ret);
	ATEErr (*Find) ( CompFontRef compfont, CompFontComponentRef component, ATETextDOM::Int32* ret);
	// Removes an existing component, returns true if successful
	ATEErr (*RemoveComponent) ( CompFontRef compfont, ATETextDOM::Int32 index, ATEBool8* ret);
	// Appends a new component, returns its new index if successful,
	// -1 if unsuccessful
	ATEErr (*AddComponent) ( CompFontRef compfont, CompFontComponentRef component, ATETextDOM::Int32* ret);
	// Replaces an existing component, retuns true if successful
	ATEErr (*ReplaceComponent) ( CompFontRef compfont, ATETextDOM::Int32 index, CompFontComponentRef component, ATEBool8* ret);

}CompFontSuite;

//////////////////////////////////////////////
//       --CompFontClassSuite--
//////////////////////////////////////////////
#define kCompFontClassSuite "ATE CompFontClass Suite"
#define kCompFontClassSuiteVersion1 1
#define kCompFontClassSuiteVersion kCompFontClassSuiteVersion1

typedef struct CompFontClassSuite{

	// Reference count maintenance.
	void (*AddRef) ( CompFontClassRef compfontclass);
	void (*Release) ( CompFontClassRef compfontclass);
	ATEBool8 (*IsNull) ( CompFontClassRef compfontclass);

	ATEErr (*Initialize) ( CompFontClassRef* compfontclass);
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetNativeName) ( CompFontClassRef compfontclass, ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength);
	ATEErr (*SetNativeName) ( CompFontClassRef compfontclass, const ATETextDOM::Unicode* name);
	// Returns number of integers written to buffer, including terminating 0.
	// It will not write more than maxLength number of integers, including
	// terminating 0.
	ATEErr (*GetCodes) ( CompFontClassRef compfontclass, ATETextDOM::Unicode* codes, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	// Return character code count which does not include terminating null.
	ATEErr (*SetCodes) ( CompFontClassRef compfontclass, const ATETextDOM::Unicode* codes, ATETextDOM::Int32* ret);
	// METHODS
	// =======================================================================
	ATEErr (*Duplicate) ( CompFontClassRef compfontclass, CompFontClassRef* ret);
	ATEErr (*GetCharacterCount) ( CompFontClassRef compfontclass, ATETextDOM::Int32* ret);
	ATEErr (*GetClassType) ( CompFontClassRef compfontclass, CompositeFontClassType* ret);
	ATEErr (*IsCodeInClass) ( CompFontClassRef compfontclass, ATETextDOM::Unicode code, ATEBool8* ret);
	// Predefined classes are never be editable.  Cutom override classes
	// are editable only if it is in an editable state.
	ATEErr (*IsEditable) ( CompFontClassRef compfontclass, ATEBool8* ret);
	ATEErr (*IsCustomOverride) ( CompFontClassRef compfontclass, ATEBool8* ret);
	// Has the resource been modified since it became editable?
	ATEErr (*IsModified) ( CompFontClassRef compfontclass, ATEBool8* ret);
	// Is the font in a valid state, either editable or committed?
	ATEErr (*VerifyState) ( CompFontClassRef compfontclass, ATEBool8* ret);

}CompFontClassSuite;

//////////////////////////////////////////////
//       --CompFontClassSetSuite--
//////////////////////////////////////////////
#define kCompFontClassSetSuite "ATE CompFontClassSet Suite"
#define kCompFontClassSetSuiteVersion1 1
#define kCompFontClassSetSuiteVersion kCompFontClassSetSuiteVersion1

typedef struct CompFontClassSetSuite{

	// Reference count maintenance.
	void (*AddRef) ( CompFontClassSetRef compfontclassset);
	void (*Release) ( CompFontClassSetRef compfontclassset);
	ATEBool8 (*IsNull) ( CompFontClassSetRef compfontclassset);

	// =======================================================================
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetSize) ( CompFontClassSetRef compfontclassset, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( CompFontClassSetRef compfontclassset, CompFontClassRef* ret);
	ATEErr (*GetLast) ( CompFontClassSetRef compfontclassset, CompFontClassRef* ret);
	// =======================================================================
	// METHODS
	// =======================================================================
	ATEErr (*Item) ( CompFontClassSetRef compfontclassset, ATETextDOM::Int32 nIndex, CompFontClassRef* ret);
	// Returns a valid index if found, else return -1
	ATEErr (*Find) ( CompFontClassSetRef compfontclassset, CompFontClassRef compFontClass, ATETextDOM::Int32* ret);
	// Returns a valid index if found, else return -1
	ATEErr (*FindPredefined) ( CompFontClassSetRef compfontclassset, CompositeFontClassType predefinedType, ATETextDOM::Int32* ret);
	// =======================================================================
	// PROTECTED AND PRIVATE METHODS
	// =======================================================================

}CompFontClassSetSuite;

//////////////////////////////////////////////
//       --CompFontComponentSuite--
//////////////////////////////////////////////
#define kCompFontComponentSuite "ATE CompFontComponent Suite"
#define kCompFontComponentSuiteVersion1 1
#define kCompFontComponentSuiteVersion kCompFontComponentSuiteVersion1

typedef struct CompFontComponentSuite{

	// Reference count maintenance.
	void (*AddRef) ( CompFontComponentRef compfontcomponent);
	void (*Release) ( CompFontComponentRef compfontcomponent);
	ATEBool8 (*IsNull) ( CompFontComponentRef compfontcomponent);

	ATEErr (*Initialize) ( TextResourcesRef pResources, CompFontComponentRef* compfontcomponent);
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetClass) ( CompFontComponentRef compfontcomponent, CompFontClassRef* ret);
	ATEErr (*SetClass) ( CompFontComponentRef compfontcomponent, CompFontClassRef charClass);
	ATEErr (*GetFont) ( CompFontComponentRef compfontcomponent, FontRef* ret);
	ATEErr (*SetFont) ( CompFontComponentRef compfontcomponent, FontRef font);
	ATEErr (*GetSize) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float* ret);
	ATEErr (*SetSize) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float size);
	ATEErr (*GetBaseline) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float* ret);
	ATEErr (*SetBaseline) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float baseline);
	ATEErr (*GetHorizontalScale) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float* ret);
	ATEErr (*SetHorizontalScale) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float horizontalScale);
	ATEErr (*GetVerticalScale) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float* ret);
	ATEErr (*SetVerticalScale) ( CompFontComponentRef compfontcomponent, ATETextDOM::Float verticalScale);
	ATEErr (*GetCenterGlyph) ( CompFontComponentRef compfontcomponent, ATEBool8* ret);
	ATEErr (*SetCenterGlyph) ( CompFontComponentRef compfontcomponent, ATEBool8 centerglyph);
	// METHODS
	// =======================================================================
	ATEErr (*IsModified) ( CompFontComponentRef compfontcomponent, ATEBool8* ret);

}CompFontComponentSuite;

//////////////////////////////////////////////
//       --CompFontSetSuite--
//////////////////////////////////////////////
#define kCompFontSetSuite "ATE CompFontSet Suite"
#define kCompFontSetSuiteVersion1 1
#define kCompFontSetSuiteVersion kCompFontSetSuiteVersion1

typedef struct CompFontSetSuite{

	// Reference count maintenance.
	void (*AddRef) ( CompFontSetRef compfontset);
	void (*Release) ( CompFontSetRef compfontset);
	ATEBool8 (*IsNull) ( CompFontSetRef compfontset);

	// =======================================================================
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetSize) ( CompFontSetRef compfontset, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( CompFontSetRef compfontset, CompFontRef* ret);
	ATEErr (*GetLast) ( CompFontSetRef compfontset, CompFontRef* ret);
	// =======================================================================
	// METHODS
	// =======================================================================
	ATEErr (*Item) ( CompFontSetRef compfontset, ATETextDOM::Int32 nIndex, CompFontRef* ret);
	// Returns a valid index if found, else return -1
	ATEErr (*Find) ( CompFontSetRef compfontset, CompFontRef font, ATETextDOM::Int32* ret);
	// Removes an existing composite font, returns true if successful
	ATEErr (*Remove) ( CompFontSetRef compfontset, ATETextDOM::Int32 nIndex, ATEBool8* ret);
	// Appends a new composite font, returns its new index if successful,
	// -1 if unsuccessful
	ATEErr (*Add) ( CompFontSetRef compfontset, CompFontRef font, ATETextDOM::Int32* ret);
	// Replaces an existing composite font, returns true if successful
	ATEErr (*Replace) ( CompFontSetRef compfontset, ATETextDOM::Int32 nIndex, CompFontRef newFont, ATEBool8* ret);
	// Updates composite font set to reflect what is currently in the
	// document font resource's font set.  This may invalidate any old
	// indices the client may be holding on to.
	ATEErr (*Update) ( CompFontSetRef compfontset);
	// =======================================================================
	// PROTECTED AND PRIVATE METHODS
	// =======================================================================

}CompFontSetSuite;

//////////////////////////////////////////////
//       --GlyphRunSuite--
//////////////////////////////////////////////
#define kGlyphRunSuite "ATE GlyphRun Suite"
#define kGlyphRunSuiteVersion1 1
#define kGlyphRunSuiteVersion kGlyphRunSuiteVersion1

typedef struct GlyphRunSuite{

	// Reference count maintenance.
	void (*AddRef) ( GlyphRunRef glyphrun);
	void (*Release) ( GlyphRunRef glyphrun);
	ATEBool8 (*IsNull) ( GlyphRunRef glyphrun);

	// METHODS
	// =======================================================================
	///This API will return ITextLine, parent of this IGlyphRun.
	ATEErr (*GetTextLine) ( GlyphRunRef glyphrun, TextLineRef* ret);
	/** return the size of glyphs in this run.
	This API will return the size of the glyphs in this run.  The size of the glyphs
	might be different from GetCharacterCount() due to factors like ligature, hyphenation  etc...
	If you want the count of glyphs, then use GetGlyphIDs().GetSize().
	*/
	ATEErr (*GetSize) ( GlyphRunRef glyphrun, ATETextDOM::Int32* ret);
	/** return the size of characters in this run.
	This API will return the size of characters in this run.  You can use this API before calling
	IGlyphRun::GetContents(xxx , SloTextdom::Int32 maxLength) to know the size of maxLength needed.
	The size of the glyphs IGlyphRun::GetSize() might be different from the return of GetCharacterCount() due to factors like ligature, hyphenation  etc...
	*/
	ATEErr (*GetCharacterCount) ( GlyphRunRef glyphrun, ATETextDOM::Int32* ret);
	ATEErr (*GetOrigins) ( GlyphRunRef glyphrun, ArrayRealPointRef* ret);
	ATEErr (*GetGlyphIDs) ( GlyphRunRef glyphrun, ArrayGlyphIDRef* ret);
	/** Return transformation matrix of this run.
	The matrix returned spesify the full transformation of the given run.  You need to transform the origin by IGlyphRun::GetOrigins() and
	concat with ITextFrame::GetMatrix() in order to get the location of the glyphs.
	*/
	ATEErr (*GetMatrix) ( GlyphRunRef glyphrun, ATETextDOM::FloatMatrix* ret);
	/** return character feature of this run.
	Use this to get access to Font, FontSize, HorizontalScale
	VerticalScale, Tracking, BaselineShift, FillColor , StrokeColor ,fBlend
	Fill , Stroke , FillFirst , FillOverPrint , StrokeOverPrint , FillBackgroundColor, FillBackground
	LineCap , LineJoin , LineWidth , MiterLimit , LineDashOffset ,
	LineDashArray and that is it, the rest of CharFeatures members are not defined.
	*/
	ATEErr (*GetCharFeatures) ( GlyphRunRef glyphrun, CharFeaturesRef* ret);
	///Glyph orientation in that run.
	ATEErr (*GetGlyphOrientation) ( GlyphRunRef glyphrun, GlyphOrientation* ret);
	ATEErr (*GetAscent) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	ATEErr (*GetDescent) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// This is the tracking that is computed by the layout engine.  i.e the space between each character.
	ATEErr (*GetTracking) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// width of the space glyph in that font
	ATEErr (*GetSpaceGlyphWidth) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// distance of baseline in that font
	ATEErr (*GetDistanceToBaseline) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// underline position in that font
	ATEErr (*GetUnderlinePosition) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// underline thickness in that font
	ATEErr (*GetUnderlineThickness) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// Maximum Cap height in that font
	ATEErr (*GetMaxCapHeight) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// Minimum Cap height in that font
	ATEErr (*GetMinCapHeight) ( GlyphRunRef glyphrun, ATETextDOM::Float* ret);
	/// Component font for the run if using a composite font, other wise the same font as in
	/// character feature.
	ATEErr (*GetFlattenedFont) ( GlyphRunRef glyphrun, FontRef* ret);
	/// Note: size of glyphrun may be different from size of characters.
	ATEErr (*GetContents_AsUnicode) ( GlyphRunRef glyphrun, ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetContents_AsChar) ( GlyphRunRef glyphrun, char* text, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);

}GlyphRunSuite;

//////////////////////////////////////////////
//       --GlyphRunsIteratorSuite--
//////////////////////////////////////////////
#define kGlyphRunsIteratorSuite "ATE GlyphRunsIterator Suite"
#define kGlyphRunsIteratorSuiteVersion1 1
#define kGlyphRunsIteratorSuiteVersion kGlyphRunsIteratorSuiteVersion1

typedef struct GlyphRunsIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( GlyphRunsIteratorRef glyphrunsiterator);
	void (*Release) ( GlyphRunsIteratorRef glyphrunsiterator);
	ATEBool8 (*IsNull) ( GlyphRunsIteratorRef glyphrunsiterator);

	// METHODS
	// =====================================================================
	ATEErr (*IsNotDone) ( GlyphRunsIteratorRef glyphrunsiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( GlyphRunsIteratorRef glyphrunsiterator, ATEBool8* ret);
	ATEErr (*Next) ( GlyphRunsIteratorRef glyphrunsiterator);
	ATEErr (*Item) ( GlyphRunsIteratorRef glyphrunsiterator, GlyphRunRef* ret);

}GlyphRunsIteratorSuite;

//////////////////////////////////////////////
//       --MojiKumiSuite--
//////////////////////////////////////////////
#define kMojiKumiSuite "ATE MojiKumi Suite"
#define kMojiKumiSuiteVersion1 1
#define kMojiKumiSuiteVersion kMojiKumiSuiteVersion1

typedef struct MojiKumiSuite{

	// Reference count maintenance.
	void (*AddRef) ( MojiKumiRef mojikumi);
	void (*Release) ( MojiKumiRef mojikumi);
	ATEBool8 (*IsNull) ( MojiKumiRef mojikumi);

	ATEErr (*Initialize) ( MojiKumiRef* mojikumi);
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetName) ( MojiKumiRef mojikumi, ATETextDOM::Unicode * name, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetNameSize) ( MojiKumiRef mojikumi, ATETextDOM::Int32* ret);
	ATEErr (*SetName) ( MojiKumiRef mojikumi, const ATETextDOM::Unicode * name);
	ATEErr (*MatchesPredefinedResourceTag) ( MojiKumiRef mojikumi, ATE::MojikumiTablePredefinedTag tag, ATEBool8* ret);
	ATEErr (*GetEntry) ( MojiKumiRef mojikumi, ATETextDOM::Int32 index, ATETextDOM::Float * minExpansion, ATETextDOM::Float * maxExpansion, ATETextDOM::Float * desiredExpansion);
	ATEErr (*SetEntry) ( MojiKumiRef mojikumi, ATETextDOM::Int32 index, ATETextDOM::Float minExpansion, ATETextDOM::Float maxExpansion, ATETextDOM::Float desiredExpansion);
	// METHODS
	// =======================================================================
	ATEErr (*IsEqual) ( MojiKumiRef mojikumi, MojiKumiRef rhsMojiKumi, ATEBool8* ret);
	ATEErr (*IsEquivalent) ( MojiKumiRef mojikumi, MojiKumiRef rhsMojiKumi, ATEBool8* ret);
	ATEErr (*IsModified) ( MojiKumiRef mojikumi, ATEBool8* ret);
	ATEErr (*IsPredefined) ( MojiKumiRef mojikumi, ATEBool8* ret);
	ATEErr (*Duplicate) ( MojiKumiRef mojikumi, MojiKumiRef* ret);

}MojiKumiSuite;

//////////////////////////////////////////////
//       --MojiKumiSetSuite--
//////////////////////////////////////////////
#define kMojiKumiSetSuite "ATE MojiKumiSet Suite"
#define kMojiKumiSetSuiteVersion1 1
#define kMojiKumiSetSuiteVersion kMojiKumiSetSuiteVersion1

typedef struct MojiKumiSetSuite{

	// Reference count maintenance.
	void (*AddRef) ( MojiKumiSetRef mojikumiset);
	void (*Release) ( MojiKumiSetRef mojikumiset);
	ATEBool8 (*IsNull) ( MojiKumiSetRef mojikumiset);

	// PROPERTIES
	// =======================================================================
	ATEErr (*GetSize) ( MojiKumiSetRef mojikumiset, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( MojiKumiSetRef mojikumiset, MojiKumiRef* ret);
	ATEErr (*GetLast) ( MojiKumiSetRef mojikumiset, MojiKumiRef* ret);
	// METHODS
	// =======================================================================
	ATEErr (*Item) ( MojiKumiSetRef mojikumiset, ATETextDOM::Int32 nIndex, MojiKumiRef* ret);
	/// Returns a valid index if found, else return -1
	/// This will search for mojikumi with the same name and data
	ATEErr (*Find_AsMojiKumi) ( MojiKumiSetRef mojikumiset, const MojiKumiRef mojiKumi, ATETextDOM::Int32* ret);
	/// Returns a valid index if found, else return -1
	/// Search by name only
	ATEErr (*Find_AsUnicode) ( MojiKumiSetRef mojikumiset, const ATETextDOM::Unicode* name, ATETextDOM::Int32* ret);
	/// Returns a valid index if found, else return -1
	/// If kUserDefinedMojikumiTableTag is requested for search, it will return the
	/// first user defined mojikumi it finds.
	ATEErr (*Find_ByPredefinedMojikumiTag) ( MojiKumiSetRef mojikumiset, MojikumiTablePredefinedTag tag, ATETextDOM::Int32* ret);
	/// Removes an existing mojikumi, returns true if successful
	ATEErr (*Remove) ( MojiKumiSetRef mojikumiset, ATETextDOM::Int32 nIndex, ATEBool8* ret);
	/// Appends a new mojikumi, returns its new index if successful,
	/// -1 if unsuccessful
	/// If the mojikumi being added already exists in the set, it will
	/// return its current index.
	ATEErr (*Add) ( MojiKumiSetRef mojikumiset, MojiKumiRef mojiKumi, ATETextDOM::Int32* ret);
	/// Replaces an existing mojikumi at the given index with the
	/// given moji kumi.  Returns true if successful
	ATEErr (*Replace) ( MojiKumiSetRef mojikumiset, ATETextDOM::Int32  nIndex, MojiKumiRef mojiKumi, ATEBool8* ret);
	/// Creates an empty new mojikumi with the specified name
	/// and appends it to the new set.
	/// It will return its new index via the nIndex parameter.
	/// If the creation of mojiKumi was unsuccessful, it will
	/// return an null AutoMojiKumi and nIndex will be -1.
	ATEErr (*CreateNewMojiKumi) ( MojiKumiSetRef mojikumiset, const ATETextDOM::Unicode* name, ATETextDOM::Int32* nIndex, MojiKumiRef* ret);

}MojiKumiSetSuite;

//////////////////////////////////////////////
//       --TextFrameSuite--
//////////////////////////////////////////////
#define kTextFrameSuite "ATE TextFrame Suite"
#if SLO_COMPLEXSCRIPT
#define kTextFrameSuiteVersion101 101
#define kTextFrameSuiteVersion kTextFrameSuiteVersion101
#else
#define kTextFrameSuiteVersion1 1
#define kTextFrameSuiteVersion kTextFrameSuiteVersion1
#endif

typedef struct TextFrameSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextFrameRef textframe);
	void (*Release) ( TextFrameRef textframe);
	ATEBool8 (*IsNull) ( TextFrameRef textframe);

	// METHODS
	// =====================================================================
	/// Get the parent story
	ATEErr (*GetStory) ( TextFrameRef textframe, StoryRef* ret);
	/** Get the text range of this frame,
	If this frame is the last frame in this story then:-
	1. If bIncludeOverflow is true, then the range returned is including the overflown text.
	2. If bIncludeOverflow is false, then the range returned will not include the overflown text.
	*/
	ATEErr (*GetTextRange) ( TextFrameRef textframe, ATEBool8 bIncludeOverflow, TextRangeRef* ret);
	ATEErr (*GetTextLinesIterator) ( TextFrameRef textframe, TextLinesIteratorRef* ret);
	ATEErr (*IsEqual) ( TextFrameRef textframe, const TextFrameRef anotherFrame, ATEBool8* ret);
	ATEErr (*GetType) ( TextFrameRef textframe, FrameType* ret);
	ATEErr (*GetLineOrientation) ( TextFrameRef textframe, LineOrientation* ret);
	/** Check if this frame is selected.  To set the selection, you have to use application specific
	API for that.  In Illustrator case, you can use AIArtSuite to set the selection.
	*/
	ATEErr (*GetSelected) ( TextFrameRef textframe, ATEBool8* ret);
	ATEErr (*GetMatrix) ( TextFrameRef textframe, ATETextDOM::FloatMatrix* ret);
	ATEErr (*GetRowCount) ( TextFrameRef textframe, ATETextDOM::Int32* ret);
	ATEErr (*GetColumnCount) ( TextFrameRef textframe, ATETextDOM::Int32* ret);
	ATEErr (*GetRowMajorOrder) ( TextFrameRef textframe, ATEBool8* ret);
	ATEErr (*GetRowGutter) ( TextFrameRef textframe, ATETextDOM::Float* ret);
	ATEErr (*GetColumnGutter) ( TextFrameRef textframe, ATETextDOM::Float* ret);
	ATEErr (*GetSpacing) ( TextFrameRef textframe, ATETextDOM::Float* ret);
	ATEErr (*GetOpticalAlignment) ( TextFrameRef textframe, ATEBool8* ret);
	ATEErr (*SetRowCount) ( TextFrameRef textframe, ATETextDOM::Int32 rowCount);
	ATEErr (*SetColumnCount) ( TextFrameRef textframe, ATETextDOM::Int32 columnCount);
	ATEErr (*SetRowMajorOrder) ( TextFrameRef textframe, ATEBool8 isRowMajor);
	ATEErr (*SetRowGutter) ( TextFrameRef textframe, ATETextDOM::Float gutter);
	ATEErr (*SetColumnGutter) ( TextFrameRef textframe, ATETextDOM::Float gutter);
	ATEErr (*SetSpacing) ( TextFrameRef textframe, ATETextDOM::Float spacing);
	ATEErr (*SetOpticalAlignment) ( TextFrameRef textframe, ATEBool8 isActive);
	ATEErr (*SetLineOrientation) ( TextFrameRef textframe, LineOrientation lineOrientation);
#if SLO_COMPLEXSCRIPT
	ATEErr (*GetStoryDirection) ( TextFrameRef textframe, ParagraphDirection* ret);
	ATEErr (*SetStoryDirection) ( TextFrameRef textframe, ParagraphDirection direction);
	ATEErr (*FullReflow) ( TextFrameRef textframe);
#endif
}TextFrameSuite;

//////////////////////////////////////////////
//       --TextFramesIteratorSuite--
//////////////////////////////////////////////
#define kTextFramesIteratorSuite "ATE TextFramesIterator Suite"
#define kTextFramesIteratorSuiteVersion1 1
#define kTextFramesIteratorSuiteVersion kTextFramesIteratorSuiteVersion1

typedef struct TextFramesIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextFramesIteratorRef textframesiterator);
	void (*Release) ( TextFramesIteratorRef textframesiterator);
	ATEBool8 (*IsNull) ( TextFramesIteratorRef textframesiterator);

	ATEErr (*Initialize) ( const TextRangeRef range, TextFramesIteratorRef* textframesiterator);
	// METHODS
	// =====================================================================
	ATEErr (*IsNotDone) ( TextFramesIteratorRef textframesiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( TextFramesIteratorRef textframesiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( TextFramesIteratorRef textframesiterator, ATEBool8* ret);
	ATEErr (*Next) ( TextFramesIteratorRef textframesiterator);
	ATEErr (*Previous) ( TextFramesIteratorRef textframesiterator);
	ATEErr (*Item) ( TextFramesIteratorRef textframesiterator, TextFrameRef* ret);

}TextFramesIteratorSuite;

//////////////////////////////////////////////
//       --TextLineSuite--
//////////////////////////////////////////////
#define kTextLineSuite "ATE TextLine Suite"
#define kTextLineSuiteVersion1 1
#define kTextLineSuiteVersion2 2
#define kTextLineSuiteVersion kTextLineSuiteVersion2

typedef struct TextLineSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextLineRef textline);
	void (*Release) ( TextLineRef textline);
	ATEBool8 (*IsNull) ( TextLineRef textline);

	// METHODS
	// =======================================================================
	ATEErr (*GetGlyphRunsIterator) ( TextLineRef textline, GlyphRunsIteratorRef* ret);
	ATEErr (*GetTextFrame) ( TextLineRef textline, TextFrameRef* ret);
	ATEErr (*GetTextRange) ( TextLineRef textline, TextRangeRef* ret);
	ATEErr (*GetBaselines) ( TextLineRef textline, ArrayLineRef* ret);
	ATEErr (*GetVisualGlyphRunsIterator) ( TextLineRef textline, GlyphRunsIteratorRef* ret);
}TextLineSuite;

typedef struct TextLine1Suite{

	// Reference count maintenance.
	void (*AddRef) ( TextLineRef textline);
	void (*Release) ( TextLineRef textline);
	ATEBool8 (*IsNull) ( TextLineRef textline);

	// METHODS
	// =======================================================================
	ATEErr (*GetGlyphRunsIterator) ( TextLineRef textline, GlyphRunsIteratorRef* ret);
	ATEErr (*GetTextFrame) ( TextLineRef textline, TextFrameRef* ret);
	ATEErr (*GetTextRange) ( TextLineRef textline, TextRangeRef* ret);
	ATEErr (*GetBaselines) ( TextLineRef textline, ArrayLineRef* ret);
}TextLine1Suite;

//////////////////////////////////////////////
//       --TextLinesIteratorSuite--
//////////////////////////////////////////////
#define kTextLinesIteratorSuite "ATE TextLinesIterator Suite"
#define kTextLinesIteratorSuiteVersion1 1
#define kTextLinesIteratorSuiteVersion kTextLinesIteratorSuiteVersion1

typedef struct TextLinesIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextLinesIteratorRef textlinesiterator);
	void (*Release) ( TextLinesIteratorRef textlinesiterator);
	ATEBool8 (*IsNull) ( TextLinesIteratorRef textlinesiterator);

	// METHODS
	// =======================================================================
	ATEErr (*IsNotDone) ( TextLinesIteratorRef textlinesiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( TextLinesIteratorRef textlinesiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( TextLinesIteratorRef textlinesiterator, ATEBool8* ret);
	ATEErr (*Next) ( TextLinesIteratorRef textlinesiterator);
	ATEErr (*Previous) ( TextLinesIteratorRef textlinesiterator);
	ATEErr (*Item) ( TextLinesIteratorRef textlinesiterator, TextLineRef* ret);

}TextLinesIteratorSuite;

//////////////////////////////////////////////
//       --TextResourcesSuite--
//////////////////////////////////////////////
#define kTextResourcesSuite "ATE TextResources Suite"
#define kTextResourcesSuiteVersion1 1
#define kTextResourcesSuiteVersion kTextResourcesSuiteVersion1

typedef struct TextResourcesSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextResourcesRef textresources);
	void (*Release) ( TextResourcesRef textresources);
	ATEBool8 (*IsNull) ( TextResourcesRef textresources);

	ATEErr (*GetTextResources) ( TextResourcesRef textresources, TextResourcesRef* ret);

}TextResourcesSuite;

//////////////////////////////////////////////
//       --ApplicationTextResourcesSuite--
//////////////////////////////////////////////
#define kApplicationTextResourcesSuite "ATE ApplicationTextResources Suite"
#define kApplicationTextResourcesSuiteVersion1 1
#define kApplicationTextResourcesSuiteVersion kApplicationTextResourcesSuiteVersion1

typedef struct ApplicationTextResourcesSuite{

	// Reference count maintenance.
	void (*AddRef) ( ApplicationTextResourcesRef applicationtextresources);
	void (*Release) ( ApplicationTextResourcesRef applicationtextresources);
	ATEBool8 (*IsNull) ( ApplicationTextResourcesRef applicationtextresources);

	// From parent class...
	ATEErr (*GetTextResources) ( ApplicationTextResourcesRef applicationtextresources, TextResourcesRef* ret);
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetKinsokuSet) ( ApplicationTextResourcesRef applicationtextresources, KinsokuSetRef* ret);
	ATEErr (*GetMojiKumiSet) ( ApplicationTextResourcesRef applicationtextresources, MojiKumiSetRef* ret);
	ATEErr (*GetCompFontClassSet) ( ApplicationTextResourcesRef applicationtextresources, CompFontClassSetRef* ret);
	ATEErr (*GetCompFontSet) ( ApplicationTextResourcesRef applicationtextresources, CompFontSetRef* ret);

}ApplicationTextResourcesSuite;

//////////////////////////////////////////////
//       --DocumentTextResourcesSuite--
//////////////////////////////////////////////
#define kDocumentTextResourcesSuite "ATE DocumentTextResources Suite"
#define kDocumentTextResourcesSuiteVersion101 101
#define kDocumentTextResourcesSuiteVersion kDocumentTextResourcesSuiteVersion101

typedef struct DocumentTextResourcesSuite{

	// Reference count maintenance.
	void (*AddRef) ( DocumentTextResourcesRef documenttextresources);
	void (*Release) ( DocumentTextResourcesRef documenttextresources);
	ATEBool8 (*IsNull) ( DocumentTextResourcesRef documenttextresources);

	// From parent class...
	ATEErr (*GetKinsokuSet) ( DocumentTextResourcesRef documenttextresources, KinsokuSetRef* ret);
	ATEErr (*GetMojiKumiSet) ( DocumentTextResourcesRef documenttextresources, MojiKumiSetRef* ret);
	ATEErr (*GetCompFontClassSet) ( DocumentTextResourcesRef documenttextresources, CompFontClassSetRef* ret);
	ATEErr (*GetCompFontSet) ( DocumentTextResourcesRef documenttextresources, CompFontSetRef* ret);
	ATEErr (*GetTextResources) ( DocumentTextResourcesRef documenttextresources, TextResourcesRef* ret);
	ATEErr (*GetFind) ( DocumentTextResourcesRef documenttextresources, FindRef* ret);
	ATEErr (*GetSpell) ( DocumentTextResourcesRef documenttextresources, SpellRef* ret);
	ATEErr (*GetGlyphAndAlternates) ( DocumentTextResourcesRef documenttextresources, GlyphRef* ret);
	ATEErr (*GetAlternateGlyph) ( DocumentTextResourcesRef documenttextresources, GlyphRef* ret);
	ATEErr (*InsertAlternateGlyph) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* theCharacters, const ATEGlyphID glyphID, const char* otFeatureArray, ATETextDOM::Int32 otFeatureCount, const ATETextDOM::Int32* otFeatureIndexArray, ATEBool8 leaveSelected);
	ATEErr (*GetAlternatesAvailableThroughoutSelection) ( DocumentTextResourcesRef documenttextresources, ArrayIntegerRef* ret);
	ATEErr (*GetJapaneseAlternateFeatureInSelection) ( DocumentTextResourcesRef documenttextresources, ATEBool8* isFeature, JapaneseAlternateFeature* ret);
	ATEErr (*SetJapaneseAlternateFeatureInSelection) ( DocumentTextResourcesRef documenttextresources, JapaneseAlternateFeature feature);
	ATEErr (*GetCharStylesInDocument) ( DocumentTextResourcesRef documenttextresources, CharStylesRef* ret);
	ATEErr (*GetParaStylesInDocument) ( DocumentTextResourcesRef documenttextresources, ParaStylesRef* ret);
	/// Returns a named style corresponding to pName.  If no matching
	/// style can be found or *pName == L'\0' then a null object is returned.
	ATEErr (*GetCharStyle) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, CharStyleRef* ret);
	ATEErr (*GetParaStyle) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, ParaStyleRef* ret);
	ATEErr (*GetNormalCharStyle) ( DocumentTextResourcesRef documenttextresources, CharStyleRef* ret);
	ATEErr (*GetNormalParaStyle) ( DocumentTextResourcesRef documenttextresources, ParaStyleRef* ret);
	ATEErr (*ResetNormalCharStyle) ( DocumentTextResourcesRef documenttextresources);
	ATEErr (*ResetNormalParaStyle) ( DocumentTextResourcesRef documenttextresources);
	/// Routines to add new named styles to the document.  If an existing
	/// style already corresponds to pName or *pName == L'\0' then the
	/// document is unchanged and a null object is returned.
	ATEErr (*CreateCharStyle) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, CharStyleRef* ret);
	ATEErr (*CreateParaStyle) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, ParaStyleRef* ret);
	ATEErr (*CreateCharStyleWithFeatures) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, CharFeaturesRef pFeatures, CharStyleRef* ret);
	ATEErr (*CreateParaStyleWithFeatures) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, ParaFeaturesRef pFeatures, ParaStyleRef* ret);
	/// Removes a style from the document.  Exact details will be provided
	/// later.
	///
	/// If no matching style in the document corresponds to pName or
	/// *pName == L'\0' then the document is unchanged and false is returned.
	ATEErr (*RemoveCharStyle) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, ATEBool8* ret);
	ATEErr (*RemoveParaStyle) ( DocumentTextResourcesRef documenttextresources, const ATETextDOM::Unicode* pName, ATEBool8* ret);
	/// Imports named styles from pSrcResources into current resource.
	ATEErr (*ImportCharStyles) ( DocumentTextResourcesRef documenttextresources, TextResourcesRef pSrcResources);
	ATEErr (*ImportParaStyles) ( DocumentTextResourcesRef documenttextresources, TextResourcesRef pSrcResources);
	ATEErr (*SetUseSmartQuotes) ( DocumentTextResourcesRef documenttextresources, ATEBool8 smartQuotesAreOn);
	ATEErr (*SetSmartDoubleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Unicode openQuote, ATETextDOM::Unicode closeQuote, Language language);
	ATEErr (*SetSmartSingleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Unicode openQuote, ATETextDOM::Unicode closeQuote, Language language);
	ATEErr (*UseSmartQuotes) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
	ATEErr (*GetSmartDoubleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Unicode* openQuote, ATETextDOM::Unicode* closeQuote, Language language);
	ATEErr (*GetSmartSingleQuoteCharacters) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Unicode* openQuote, ATETextDOM::Unicode* closeQuote, Language language);
	/// The library stores an internal set of insertion attributes either from
	/// the last selection or from the last attribute change to text.  This set
	/// of insertion attributes comprises the local overrides (CharFeatures)
	/// and the named style (CharStyle)
	ATEErr (*GetInsertionCharFeatures) ( DocumentTextResourcesRef documenttextresources, CharFeaturesRef* ret);
	ATEErr (*GetInsertionCharStyle) ( DocumentTextResourcesRef documenttextresources, CharStyleRef* ret);
	ATEErr (*SetInsertionFeaturesAndStyle) ( DocumentTextResourcesRef documenttextresources, const CharFeaturesRef pFeatures, const ATETextDOM::Unicode* pStyleName);
	/// Get superscript size
	ATEErr (*GetSuperscriptSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float* ret);
	/// Set superscript size
	ATEErr (*SetSuperscriptSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float value);
	/// Get superscript position
	ATEErr (*GetSuperscriptPosition) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float* ret);
	/// Set superscript position
	ATEErr (*SetSuperscriptPosition) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float value);
	/// Get subscript size
	ATEErr (*GetSubscriptSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float* ret);
	/// Set subscript size
	ATEErr (*SetSubscriptSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float value);
	/// Get subscript position
	ATEErr (*GetSubscriptPosition) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float* ret);
	/// Set subscript position
	ATEErr (*SetSubscriptPosition) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float value);
	/// Get SmallCap size
	ATEErr (*GetSmallCapSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float* ret);
	/// Set SmallCap size
	ATEErr (*SetSmallCapSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Float value);
	/// Get ShowHiddenCharacters
	ATEErr (*GetShowHiddenCharacters) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
	/// Set ShowHiddenCharacters
	ATEErr (*SetShowHiddenCharacters) ( DocumentTextResourcesRef documenttextresources, ATEBool8 value);
	/// Get Greeking Size
	ATEErr (*GetGreekingSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Int32* ret);
	/// Set Greeking Size
	ATEErr (*SetGreekingSize) ( DocumentTextResourcesRef documenttextresources, ATETextDOM::Int32 value);
	/// Get HighlightSubstituteFonts
	ATEErr (*GetHighlightSubstituteFonts) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
	/// Set HighlightSubstituteFonts
	ATEErr (*SetHighlightSubstituteFonts) ( DocumentTextResourcesRef documenttextresources, ATEBool8 value);
	/// Get HighlightAlternateGlyphs
	ATEErr (*GetHighlightAlternateGlyphs) ( DocumentTextResourcesRef documenttextresources, ATEBool8* ret);
	/// Set HighlightAlternateGlyphs
	ATEErr (*SetHighlightAlternateGlyphs) ( DocumentTextResourcesRef documenttextresources, ATEBool8 value);

}DocumentTextResourcesSuite;

//////////////////////////////////////////////
//       --VersionInfoSuite--
//////////////////////////////////////////////
#define kVersionInfoSuite "ATE VersionInfo Suite"
#define kVersionInfoSuiteVersion1 1
#define kVersionInfoSuiteVersion kVersionInfoSuiteVersion1

typedef struct VersionInfoSuite{

	// Reference count maintenance.
	void (*AddRef) ( VersionInfoRef versioninfo);
	void (*Release) ( VersionInfoRef versioninfo);
	ATEBool8 (*IsNull) ( VersionInfoRef versioninfo);

	ATEErr (*Initialize) ( VersionInfoRef* versioninfo);
	/// Return major version.
	ATEErr (*GetMajorVersion) ( VersionInfoRef versioninfo, int* ret);
	/// Return minor version.
	ATEErr (*GetMinorVersion) ( VersionInfoRef versioninfo, int* ret);
	/// Return sub minor version.
	ATEErr (*GetSubMinorVersion) ( VersionInfoRef versioninfo, int* ret);
	/// maxLength is the size of versionString in ASUTF16 units.
	/// return is number of characters in versionString.
	/// Here is usage:-
	/// ASUTF16 versionString[256];
	/// GetVersionAsUTF16(versionString , 256);
	ATEErr (*GetVersionAsUTF16) ( VersionInfoRef versioninfo, ASUTF16* versionString, int maxLength, int* ret);

}VersionInfoSuite;

//////////////////////////////////////////////
//       --ArrayApplicationPaintRefSuite--
//////////////////////////////////////////////
#define kArrayApplicationPaintRefSuite "ATE ArrayApplicationPaintRef Suite"
#define kArrayApplicationPaintRefSuiteVersion1 1
#define kArrayApplicationPaintRefSuiteVersion kArrayApplicationPaintRefSuiteVersion1

typedef struct ArrayApplicationPaintRefSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayApplicationPaintRefRef arrayapplicationpaintref);
	void (*Release) ( ArrayApplicationPaintRefRef arrayapplicationpaintref);
	ATEBool8 (*IsNull) ( ArrayApplicationPaintRefRef arrayapplicationpaintref);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayApplicationPaintRefRef arrayapplicationpaintref, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayApplicationPaintRefRef arrayapplicationpaintref, ApplicationPaintRef* ret);
	ATEErr (*GetLast) ( ArrayApplicationPaintRefRef arrayapplicationpaintref, ApplicationPaintRef* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayApplicationPaintRefRef arrayapplicationpaintref, ATETextDOM::Int32 index, ApplicationPaintRef* ret);

}ArrayApplicationPaintRefSuite;

//////////////////////////////////////////////
//       --ArrayRealSuite--
//////////////////////////////////////////////
#define kArrayRealSuite "ATE ArrayReal Suite"
#define kArrayRealSuiteVersion1 1
#define kArrayRealSuiteVersion kArrayRealSuiteVersion1

typedef struct ArrayRealSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayRealRef arrayreal);
	void (*Release) ( ArrayRealRef arrayreal);
	ATEBool8 (*IsNull) ( ArrayRealRef arrayreal);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayRealRef arrayreal, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayRealRef arrayreal, ATETextDOM::Float* ret);
	ATEErr (*GetLast) ( ArrayRealRef arrayreal, ATETextDOM::Float* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayRealRef arrayreal, ATETextDOM::Int32 index, ATETextDOM::Float* ret);

}ArrayRealSuite;

//////////////////////////////////////////////
//       --ArrayBoolSuite--
//////////////////////////////////////////////
#define kArrayBoolSuite "ATE ArrayBool Suite"
#define kArrayBoolSuiteVersion1 1
#define kArrayBoolSuiteVersion kArrayBoolSuiteVersion1

typedef struct ArrayBoolSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayBoolRef arraybool);
	void (*Release) ( ArrayBoolRef arraybool);
	ATEBool8 (*IsNull) ( ArrayBoolRef arraybool);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayBoolRef arraybool, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayBoolRef arraybool, ATEBool8* ret);
	ATEErr (*GetLast) ( ArrayBoolRef arraybool, ATEBool8* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayBoolRef arraybool, ATETextDOM::Int32 index, ATEBool8* ret);

}ArrayBoolSuite;

//////////////////////////////////////////////
//       --ArrayIntegerSuite--
//////////////////////////////////////////////
#define kArrayIntegerSuite "ATE ArrayInteger Suite"
#define kArrayIntegerSuiteVersion1 1
#define kArrayIntegerSuiteVersion kArrayIntegerSuiteVersion1

typedef struct ArrayIntegerSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayIntegerRef arrayinteger);
	void (*Release) ( ArrayIntegerRef arrayinteger);
	ATEBool8 (*IsNull) ( ArrayIntegerRef arrayinteger);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayIntegerRef arrayinteger, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayIntegerRef arrayinteger, ATETextDOM::Int32* ret);
	ATEErr (*GetLast) ( ArrayIntegerRef arrayinteger, ATETextDOM::Int32* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayIntegerRef arrayinteger, ATETextDOM::Int32 index, ATETextDOM::Int32* ret);

}ArrayIntegerSuite;

//////////////////////////////////////////////
//       --ArrayLineCapTypeSuite--
//////////////////////////////////////////////
#define kArrayLineCapTypeSuite "ATE ArrayLineCapType Suite"
#define kArrayLineCapTypeSuiteVersion1 1
#define kArrayLineCapTypeSuiteVersion kArrayLineCapTypeSuiteVersion1

typedef struct ArrayLineCapTypeSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayLineCapTypeRef arraylinecaptype);
	void (*Release) ( ArrayLineCapTypeRef arraylinecaptype);
	ATEBool8 (*IsNull) ( ArrayLineCapTypeRef arraylinecaptype);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayLineCapTypeRef arraylinecaptype, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayLineCapTypeRef arraylinecaptype, LineCapType* ret);
	ATEErr (*GetLast) ( ArrayLineCapTypeRef arraylinecaptype, LineCapType* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayLineCapTypeRef arraylinecaptype, ATETextDOM::Int32 index, LineCapType* ret);

}ArrayLineCapTypeSuite;

//////////////////////////////////////////////
//       --ArrayFigureStyleSuite--
//////////////////////////////////////////////
#define kArrayFigureStyleSuite "ATE ArrayFigureStyle Suite"
#define kArrayFigureStyleSuiteVersion1 1
#define kArrayFigureStyleSuiteVersion kArrayFigureStyleSuiteVersion1

typedef struct ArrayFigureStyleSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayFigureStyleRef arrayfigurestyle);
	void (*Release) ( ArrayFigureStyleRef arrayfigurestyle);
	ATEBool8 (*IsNull) ( ArrayFigureStyleRef arrayfigurestyle);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayFigureStyleRef arrayfigurestyle, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayFigureStyleRef arrayfigurestyle, FigureStyle* ret);
	ATEErr (*GetLast) ( ArrayFigureStyleRef arrayfigurestyle, FigureStyle* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayFigureStyleRef arrayfigurestyle, ATETextDOM::Int32 index, FigureStyle* ret);

}ArrayFigureStyleSuite;

//////////////////////////////////////////////
//       --ArrayLineJoinTypeSuite--
//////////////////////////////////////////////
#define kArrayLineJoinTypeSuite "ATE ArrayLineJoinType Suite"
#define kArrayLineJoinTypeSuiteVersion1 1
#define kArrayLineJoinTypeSuiteVersion kArrayLineJoinTypeSuiteVersion1

typedef struct ArrayLineJoinTypeSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayLineJoinTypeRef arraylinejointype);
	void (*Release) ( ArrayLineJoinTypeRef arraylinejointype);
	ATEBool8 (*IsNull) ( ArrayLineJoinTypeRef arraylinejointype);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayLineJoinTypeRef arraylinejointype, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayLineJoinTypeRef arraylinejointype, LineJoinType* ret);
	ATEErr (*GetLast) ( ArrayLineJoinTypeRef arraylinejointype, LineJoinType* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayLineJoinTypeRef arraylinejointype, ATETextDOM::Int32 index, LineJoinType* ret);

}ArrayLineJoinTypeSuite;

//////////////////////////////////////////////
//       --ArrayWariChuJustificationSuite--
//////////////////////////////////////////////
#define kArrayWariChuJustificationSuite "ATE ArrayWariChuJustification Suite"
#define kArrayWariChuJustificationSuiteVersion1 1
#define kArrayWariChuJustificationSuiteVersion kArrayWariChuJustificationSuiteVersion1

typedef struct ArrayWariChuJustificationSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayWariChuJustificationRef arraywarichujustification);
	void (*Release) ( ArrayWariChuJustificationRef arraywarichujustification);
	ATEBool8 (*IsNull) ( ArrayWariChuJustificationRef arraywarichujustification);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayWariChuJustificationRef arraywarichujustification, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayWariChuJustificationRef arraywarichujustification, WariChuJustification* ret);
	ATEErr (*GetLast) ( ArrayWariChuJustificationRef arraywarichujustification, WariChuJustification* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayWariChuJustificationRef arraywarichujustification, ATETextDOM::Int32 index, WariChuJustification* ret);

}ArrayWariChuJustificationSuite;

//////////////////////////////////////////////
//       --ArrayStyleRunAlignmentSuite--
//////////////////////////////////////////////
#define kArrayStyleRunAlignmentSuite "ATE ArrayStyleRunAlignment Suite"
#define kArrayStyleRunAlignmentSuiteVersion1 1
#define kArrayStyleRunAlignmentSuiteVersion kArrayStyleRunAlignmentSuiteVersion1

typedef struct ArrayStyleRunAlignmentSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayStyleRunAlignmentRef arraystylerunalignment);
	void (*Release) ( ArrayStyleRunAlignmentRef arraystylerunalignment);
	ATEBool8 (*IsNull) ( ArrayStyleRunAlignmentRef arraystylerunalignment);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayStyleRunAlignmentRef arraystylerunalignment, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayStyleRunAlignmentRef arraystylerunalignment, StyleRunAlignment* ret);
	ATEErr (*GetLast) ( ArrayStyleRunAlignmentRef arraystylerunalignment, StyleRunAlignment* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayStyleRunAlignmentRef arraystylerunalignment, ATETextDOM::Int32 index, StyleRunAlignment* ret);

}ArrayStyleRunAlignmentSuite;

//////////////////////////////////////////////
//       --ArrayAutoKernTypeSuite--
//////////////////////////////////////////////
#define kArrayAutoKernTypeSuite "ATE ArrayAutoKernType Suite"
#define kArrayAutoKernTypeSuiteVersion1 1
#define kArrayAutoKernTypeSuiteVersion kArrayAutoKernTypeSuiteVersion1

typedef struct ArrayAutoKernTypeSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayAutoKernTypeRef arrayautokerntype);
	void (*Release) ( ArrayAutoKernTypeRef arrayautokerntype);
	ATEBool8 (*IsNull) ( ArrayAutoKernTypeRef arrayautokerntype);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayAutoKernTypeRef arrayautokerntype, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayAutoKernTypeRef arrayautokerntype, AutoKernType* ret);
	ATEErr (*GetLast) ( ArrayAutoKernTypeRef arrayautokerntype, AutoKernType* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayAutoKernTypeRef arrayautokerntype, ATETextDOM::Int32 index, AutoKernType* ret);

}ArrayAutoKernTypeSuite;

//////////////////////////////////////////////
//       --ArrayBaselineDirectionSuite--
//////////////////////////////////////////////
#define kArrayBaselineDirectionSuite "ATE ArrayBaselineDirection Suite"
#define kArrayBaselineDirectionSuiteVersion1 1
#define kArrayBaselineDirectionSuiteVersion kArrayBaselineDirectionSuiteVersion1

typedef struct ArrayBaselineDirectionSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayBaselineDirectionRef arraybaselinedirection);
	void (*Release) ( ArrayBaselineDirectionRef arraybaselinedirection);
	ATEBool8 (*IsNull) ( ArrayBaselineDirectionRef arraybaselinedirection);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayBaselineDirectionRef arraybaselinedirection, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayBaselineDirectionRef arraybaselinedirection, BaselineDirection* ret);
	ATEErr (*GetLast) ( ArrayBaselineDirectionRef arraybaselinedirection, BaselineDirection* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayBaselineDirectionRef arraybaselinedirection, ATETextDOM::Int32 index, BaselineDirection* ret);

}ArrayBaselineDirectionSuite;

//////////////////////////////////////////////
//       --ArrayLanguageSuite--
//////////////////////////////////////////////
#define kArrayLanguageSuite "ATE ArrayLanguage Suite"
#define kArrayLanguageSuiteVersion1 1
#define kArrayLanguageSuiteVersion kArrayLanguageSuiteVersion1

typedef struct ArrayLanguageSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayLanguageRef arraylanguage);
	void (*Release) ( ArrayLanguageRef arraylanguage);
	ATEBool8 (*IsNull) ( ArrayLanguageRef arraylanguage);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayLanguageRef arraylanguage, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayLanguageRef arraylanguage, Language* ret);
	ATEErr (*GetLast) ( ArrayLanguageRef arraylanguage, Language* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayLanguageRef arraylanguage, ATETextDOM::Int32 index, Language* ret);

}ArrayLanguageSuite;

//////////////////////////////////////////////
//       --ArrayFontCapsOptionSuite--
//////////////////////////////////////////////
#define kArrayFontCapsOptionSuite "ATE ArrayFontCapsOption Suite"
#define kArrayFontCapsOptionSuiteVersion1 1
#define kArrayFontCapsOptionSuiteVersion kArrayFontCapsOptionSuiteVersion1

typedef struct ArrayFontCapsOptionSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayFontCapsOptionRef arrayfontcapsoption);
	void (*Release) ( ArrayFontCapsOptionRef arrayfontcapsoption);
	ATEBool8 (*IsNull) ( ArrayFontCapsOptionRef arrayfontcapsoption);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayFontCapsOptionRef arrayfontcapsoption, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayFontCapsOptionRef arrayfontcapsoption, FontCapsOption* ret);
	ATEErr (*GetLast) ( ArrayFontCapsOptionRef arrayfontcapsoption, FontCapsOption* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayFontCapsOptionRef arrayfontcapsoption, ATETextDOM::Int32 index, FontCapsOption* ret);

}ArrayFontCapsOptionSuite;

//////////////////////////////////////////////
//       --ArrayFontBaselineOptionSuite--
//////////////////////////////////////////////
#define kArrayFontBaselineOptionSuite "ATE ArrayFontBaselineOption Suite"
#define kArrayFontBaselineOptionSuiteVersion1 1
#define kArrayFontBaselineOptionSuiteVersion kArrayFontBaselineOptionSuiteVersion1

typedef struct ArrayFontBaselineOptionSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayFontBaselineOptionRef arrayfontbaselineoption);
	void (*Release) ( ArrayFontBaselineOptionRef arrayfontbaselineoption);
	ATEBool8 (*IsNull) ( ArrayFontBaselineOptionRef arrayfontbaselineoption);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayFontBaselineOptionRef arrayfontbaselineoption, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayFontBaselineOptionRef arrayfontbaselineoption, FontBaselineOption* ret);
	ATEErr (*GetLast) ( ArrayFontBaselineOptionRef arrayfontbaselineoption, FontBaselineOption* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayFontBaselineOptionRef arrayfontbaselineoption, ATETextDOM::Int32 index, FontBaselineOption* ret);

}ArrayFontBaselineOptionSuite;

//////////////////////////////////////////////
//       --ArrayFontOpenTypePositionOptionSuite--
//////////////////////////////////////////////
#define kArrayFontOpenTypePositionOptionSuite "ATE ArrayFontOpenTypePositionOption Suite"
#define kArrayFontOpenTypePositionOptionSuiteVersion1 1
#define kArrayFontOpenTypePositionOptionSuiteVersion kArrayFontOpenTypePositionOptionSuiteVersion1

typedef struct ArrayFontOpenTypePositionOptionSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption);
	void (*Release) ( ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption);
	ATEBool8 (*IsNull) ( ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption, FontOpenTypePositionOption* ret);
	ATEErr (*GetLast) ( ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption, FontOpenTypePositionOption* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption, ATETextDOM::Int32 index, FontOpenTypePositionOption* ret);

}ArrayFontOpenTypePositionOptionSuite;

//////////////////////////////////////////////
//       --ArrayUnderlinePositionSuite--
//////////////////////////////////////////////
#define kArrayUnderlinePositionSuite "ATE ArrayUnderlinePosition Suite"
#define kArrayUnderlinePositionSuiteVersion1 1
#define kArrayUnderlinePositionSuiteVersion kArrayUnderlinePositionSuiteVersion1

typedef struct ArrayUnderlinePositionSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayUnderlinePositionRef arrayunderlineposition);
	void (*Release) ( ArrayUnderlinePositionRef arrayunderlineposition);
	ATEBool8 (*IsNull) ( ArrayUnderlinePositionRef arrayunderlineposition);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayUnderlinePositionRef arrayunderlineposition, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayUnderlinePositionRef arrayunderlineposition, UnderlinePosition* ret);
	ATEErr (*GetLast) ( ArrayUnderlinePositionRef arrayunderlineposition, UnderlinePosition* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayUnderlinePositionRef arrayunderlineposition, ATETextDOM::Int32 index, UnderlinePosition* ret);

}ArrayUnderlinePositionSuite;

//////////////////////////////////////////////
//       --ArrayStrikethroughPositionSuite--
//////////////////////////////////////////////
#define kArrayStrikethroughPositionSuite "ATE ArrayStrikethroughPosition Suite"
#define kArrayStrikethroughPositionSuiteVersion1 1
#define kArrayStrikethroughPositionSuiteVersion kArrayStrikethroughPositionSuiteVersion1

typedef struct ArrayStrikethroughPositionSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayStrikethroughPositionRef arraystrikethroughposition);
	void (*Release) ( ArrayStrikethroughPositionRef arraystrikethroughposition);
	ATEBool8 (*IsNull) ( ArrayStrikethroughPositionRef arraystrikethroughposition);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayStrikethroughPositionRef arraystrikethroughposition, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayStrikethroughPositionRef arraystrikethroughposition, StrikethroughPosition* ret);
	ATEErr (*GetLast) ( ArrayStrikethroughPositionRef arraystrikethroughposition, StrikethroughPosition* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayStrikethroughPositionRef arraystrikethroughposition, ATETextDOM::Int32 index, StrikethroughPosition* ret);

}ArrayStrikethroughPositionSuite;

//////////////////////////////////////////////
//       --ArrayParagraphJustificationSuite--
//////////////////////////////////////////////
#define kArrayParagraphJustificationSuite "ATE ArrayParagraphJustification Suite"
#define kArrayParagraphJustificationSuiteVersion1 1
#define kArrayParagraphJustificationSuiteVersion kArrayParagraphJustificationSuiteVersion1

typedef struct ArrayParagraphJustificationSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayParagraphJustificationRef arrayparagraphjustification);
	void (*Release) ( ArrayParagraphJustificationRef arrayparagraphjustification);
	ATEBool8 (*IsNull) ( ArrayParagraphJustificationRef arrayparagraphjustification);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayParagraphJustificationRef arrayparagraphjustification, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayParagraphJustificationRef arrayparagraphjustification, ParagraphJustification* ret);
	ATEErr (*GetLast) ( ArrayParagraphJustificationRef arrayparagraphjustification, ParagraphJustification* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayParagraphJustificationRef arrayparagraphjustification, ATETextDOM::Int32 index, ParagraphJustification* ret);

}ArrayParagraphJustificationSuite;

//////////////////////////////////////////////
//       --ArrayArrayRealSuite--
//////////////////////////////////////////////
#define kArrayArrayRealSuite "ATE ArrayArrayReal Suite"
#define kArrayArrayRealSuiteVersion1 1
#define kArrayArrayRealSuiteVersion kArrayArrayRealSuiteVersion1

typedef struct ArrayArrayRealSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayArrayRealRef arrayarrayreal);
	void (*Release) ( ArrayArrayRealRef arrayarrayreal);
	ATEBool8 (*IsNull) ( ArrayArrayRealRef arrayarrayreal);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayArrayRealRef arrayarrayreal, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayArrayRealRef arrayarrayreal, ArrayRealRef* ret);
	ATEErr (*GetLast) ( ArrayArrayRealRef arrayarrayreal, ArrayRealRef* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayArrayRealRef arrayarrayreal, ATETextDOM::Int32 index, ArrayRealRef* ret);

}ArrayArrayRealSuite;

//////////////////////////////////////////////
//       --ArrayBurasagariTypeSuite--
//////////////////////////////////////////////
#define kArrayBurasagariTypeSuite "ATE ArrayBurasagariType Suite"
#define kArrayBurasagariTypeSuiteVersion1 1
#define kArrayBurasagariTypeSuiteVersion kArrayBurasagariTypeSuiteVersion1

typedef struct ArrayBurasagariTypeSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayBurasagariTypeRef arrayburasagaritype);
	void (*Release) ( ArrayBurasagariTypeRef arrayburasagaritype);
	ATEBool8 (*IsNull) ( ArrayBurasagariTypeRef arrayburasagaritype);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayBurasagariTypeRef arrayburasagaritype, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayBurasagariTypeRef arrayburasagaritype, BurasagariType* ret);
	ATEErr (*GetLast) ( ArrayBurasagariTypeRef arrayburasagaritype, BurasagariType* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayBurasagariTypeRef arrayburasagaritype, ATETextDOM::Int32 index, BurasagariType* ret);

}ArrayBurasagariTypeSuite;

//////////////////////////////////////////////
//       --ArrayPreferredKinsokuOrderSuite--
//////////////////////////////////////////////
#define kArrayPreferredKinsokuOrderSuite "ATE ArrayPreferredKinsokuOrder Suite"
#define kArrayPreferredKinsokuOrderSuiteVersion1 1
#define kArrayPreferredKinsokuOrderSuiteVersion kArrayPreferredKinsokuOrderSuiteVersion1

typedef struct ArrayPreferredKinsokuOrderSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder);
	void (*Release) ( ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder);
	ATEBool8 (*IsNull) ( ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder, PreferredKinsokuOrder* ret);
	ATEErr (*GetLast) ( ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder, PreferredKinsokuOrder* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder, ATETextDOM::Int32 index, PreferredKinsokuOrder* ret);

}ArrayPreferredKinsokuOrderSuite;

//////////////////////////////////////////////
//       --ArrayKinsokuRefSuite--
//////////////////////////////////////////////
#define kArrayKinsokuRefSuite "ATE ArrayKinsokuRef Suite"
#define kArrayKinsokuRefSuiteVersion1 1
#define kArrayKinsokuRefSuiteVersion kArrayKinsokuRefSuiteVersion1

typedef struct ArrayKinsokuRefSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayKinsokuRefRef arraykinsokuref);
	void (*Release) ( ArrayKinsokuRefRef arraykinsokuref);
	ATEBool8 (*IsNull) ( ArrayKinsokuRefRef arraykinsokuref);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayKinsokuRefRef arraykinsokuref, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayKinsokuRefRef arraykinsokuref, KinsokuRef* ret);
	ATEErr (*GetLast) ( ArrayKinsokuRefRef arraykinsokuref, KinsokuRef* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayKinsokuRefRef arraykinsokuref, ATETextDOM::Int32 index, KinsokuRef* ret);

}ArrayKinsokuRefSuite;

//////////////////////////////////////////////
//       --ArrayMojiKumiRefSuite--
//////////////////////////////////////////////
#define kArrayMojiKumiRefSuite "ATE ArrayMojiKumiRef Suite"
#define kArrayMojiKumiRefSuiteVersion1 1
#define kArrayMojiKumiRefSuiteVersion kArrayMojiKumiRefSuiteVersion1

typedef struct ArrayMojiKumiRefSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayMojiKumiRefRef arraymojikumiref);
	void (*Release) ( ArrayMojiKumiRefRef arraymojikumiref);
	ATEBool8 (*IsNull) ( ArrayMojiKumiRefRef arraymojikumiref);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayMojiKumiRefRef arraymojikumiref, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayMojiKumiRefRef arraymojikumiref, MojiKumiRef* ret);
	ATEErr (*GetLast) ( ArrayMojiKumiRefRef arraymojikumiref, MojiKumiRef* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayMojiKumiRefRef arraymojikumiref, ATETextDOM::Int32 index, MojiKumiRef* ret);

}ArrayMojiKumiRefSuite;

//////////////////////////////////////////////
//       --ArrayMojiKumiSetRefSuite--
//////////////////////////////////////////////
#define kArrayMojiKumiSetRefSuite "ATE ArrayMojiKumiSetRef Suite"
#define kArrayMojiKumiSetRefSuiteVersion1 1
#define kArrayMojiKumiSetRefSuiteVersion kArrayMojiKumiSetRefSuiteVersion1

typedef struct ArrayMojiKumiSetRefSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayMojiKumiSetRefRef arraymojikumisetref);
	void (*Release) ( ArrayMojiKumiSetRefRef arraymojikumisetref);
	ATEBool8 (*IsNull) ( ArrayMojiKumiSetRefRef arraymojikumisetref);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayMojiKumiSetRefRef arraymojikumisetref, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayMojiKumiSetRefRef arraymojikumisetref, MojiKumiSetRef* ret);
	ATEErr (*GetLast) ( ArrayMojiKumiSetRefRef arraymojikumisetref, MojiKumiSetRef* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayMojiKumiSetRefRef arraymojikumisetref, ATETextDOM::Int32 index, MojiKumiSetRef* ret);

}ArrayMojiKumiSetRefSuite;

//////////////////////////////////////////////
//       --ArrayTabStopsRefSuite--
//////////////////////////////////////////////
#define kArrayTabStopsRefSuite "ATE ArrayTabStopsRef Suite"
#define kArrayTabStopsRefSuiteVersion1 1
#define kArrayTabStopsRefSuiteVersion kArrayTabStopsRefSuiteVersion1

typedef struct ArrayTabStopsRefSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayTabStopsRefRef arraytabstopsref);
	void (*Release) ( ArrayTabStopsRefRef arraytabstopsref);
	ATEBool8 (*IsNull) ( ArrayTabStopsRefRef arraytabstopsref);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayTabStopsRefRef arraytabstopsref, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayTabStopsRefRef arraytabstopsref, TabStopsRef* ret);
	ATEErr (*GetLast) ( ArrayTabStopsRefRef arraytabstopsref, TabStopsRef* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayTabStopsRefRef arraytabstopsref, ATETextDOM::Int32 index, TabStopsRef* ret);

}ArrayTabStopsRefSuite;

//////////////////////////////////////////////
//       --ArrayLeadingTypeSuite--
//////////////////////////////////////////////
#define kArrayLeadingTypeSuite "ATE ArrayLeadingType Suite"
#define kArrayLeadingTypeSuiteVersion1 1
#define kArrayLeadingTypeSuiteVersion kArrayLeadingTypeSuiteVersion1

typedef struct ArrayLeadingTypeSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayLeadingTypeRef arrayleadingtype);
	void (*Release) ( ArrayLeadingTypeRef arrayleadingtype);
	ATEBool8 (*IsNull) ( ArrayLeadingTypeRef arrayleadingtype);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayLeadingTypeRef arrayleadingtype, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayLeadingTypeRef arrayleadingtype, LeadingType* ret);
	ATEErr (*GetLast) ( ArrayLeadingTypeRef arrayleadingtype, LeadingType* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayLeadingTypeRef arrayleadingtype, ATETextDOM::Int32 index, LeadingType* ret);

}ArrayLeadingTypeSuite;

//////////////////////////////////////////////
//       --ArrayFontRefSuite--
//////////////////////////////////////////////
#define kArrayFontRefSuite "ATE ArrayFontRef Suite"
#define kArrayFontRefSuiteVersion1 1
#define kArrayFontRefSuiteVersion kArrayFontRefSuiteVersion1

typedef struct ArrayFontRefSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayFontRefRef arrayfontref);
	void (*Release) ( ArrayFontRefRef arrayfontref);
	ATEBool8 (*IsNull) ( ArrayFontRefRef arrayfontref);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayFontRefRef arrayfontref, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayFontRefRef arrayfontref, FontRef* ret);
	ATEErr (*GetLast) ( ArrayFontRefRef arrayfontref, FontRef* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayFontRefRef arrayfontref, ATETextDOM::Int32 index, FontRef* ret);

}ArrayFontRefSuite;

//////////////////////////////////////////////
//       --ArrayGlyphIDSuite--
//////////////////////////////////////////////
#define kArrayGlyphIDSuite "ATE ArrayGlyphID Suite"
#define kArrayGlyphIDSuiteVersion1 1
#define kArrayGlyphIDSuiteVersion kArrayGlyphIDSuiteVersion1

typedef struct ArrayGlyphIDSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayGlyphIDRef arrayglyphid);
	void (*Release) ( ArrayGlyphIDRef arrayglyphid);
	ATEBool8 (*IsNull) ( ArrayGlyphIDRef arrayglyphid);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayGlyphIDRef arrayglyphid, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayGlyphIDRef arrayglyphid, ATEGlyphID* ret);
	ATEErr (*GetLast) ( ArrayGlyphIDRef arrayglyphid, ATEGlyphID* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayGlyphIDRef arrayglyphid, ATETextDOM::Int32 index, ATEGlyphID* ret);

}ArrayGlyphIDSuite;

//////////////////////////////////////////////
//       --ArrayRealPointSuite--
//////////////////////////////////////////////
#define kArrayRealPointSuite "ATE ArrayRealPoint Suite"
#define kArrayRealPointSuiteVersion1 1
#define kArrayRealPointSuiteVersion kArrayRealPointSuiteVersion1

typedef struct ArrayRealPointSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayRealPointRef arrayrealpoint);
	void (*Release) ( ArrayRealPointRef arrayrealpoint);
	ATEBool8 (*IsNull) ( ArrayRealPointRef arrayrealpoint);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayRealPointRef arrayrealpoint, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayRealPointRef arrayrealpoint, ATETextDOM::FloatPoint* ret);
	ATEErr (*GetLast) ( ArrayRealPointRef arrayrealpoint, ATETextDOM::FloatPoint* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayRealPointRef arrayrealpoint, ATETextDOM::Int32 index, ATETextDOM::FloatPoint* ret);

}ArrayRealPointSuite;

//////////////////////////////////////////////
//       --ArrayRealMatrixSuite--
//////////////////////////////////////////////
#define kArrayRealMatrixSuite "ATE ArrayRealMatrix Suite"
#define kArrayRealMatrixSuiteVersion1 1
#define kArrayRealMatrixSuiteVersion kArrayRealMatrixSuiteVersion1

typedef struct ArrayRealMatrixSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayRealMatrixRef arrayrealmatrix);
	void (*Release) ( ArrayRealMatrixRef arrayrealmatrix);
	ATEBool8 (*IsNull) ( ArrayRealMatrixRef arrayrealmatrix);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayRealMatrixRef arrayrealmatrix, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayRealMatrixRef arrayrealmatrix, ATETextDOM::FloatMatrix* ret);
	ATEErr (*GetLast) ( ArrayRealMatrixRef arrayrealmatrix, ATETextDOM::FloatMatrix* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayRealMatrixRef arrayrealmatrix, ATETextDOM::Int32 index, ATETextDOM::FloatMatrix* ret);

}ArrayRealMatrixSuite;

#if SLO_COMPLEXSCRIPT
//////////////////////////////////////////////
//       --ArrayParagraphDirectionSuite--
//////////////////////////////////////////////
#define kArrayParagraphDirectionSuite "ATE ArrayParagraphDirection Suite"
#define kArrayParagraphDirectionSuiteVersion1 1
#define kArrayParagraphDirectionSuiteVersion kArrayParagraphDirectionSuiteVersion1

typedef struct ArrayParagraphDirectionSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayParagraphDirectionRef arrayparagraphdirection);
	void (*Release) ( ArrayParagraphDirectionRef arrayparagraphdirection);
	ATEBool8 (*IsNull) ( ArrayParagraphDirectionRef arrayparagraphdirection);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayParagraphDirectionRef arrayparagraphdirection, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayParagraphDirectionRef arrayparagraphdirection, ParagraphDirection* ret);
	ATEErr (*GetLast) ( ArrayParagraphDirectionRef arrayparagraphdirection, ParagraphDirection* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayParagraphDirectionRef arrayparagraphdirection, ATETextDOM::Int32 index, ParagraphDirection* ret);

}ArrayParagraphDirectionSuite;

//////////////////////////////////////////////
//       --ArrayJustificationMethodSuite--
//////////////////////////////////////////////
#define kArrayJustificationMethodSuite "ATE ArrayJustificationMethod Suite"
#define kArrayJustificationMethodSuiteVersion1 1
#define kArrayJustificationMethodSuiteVersion kArrayJustificationMethodSuiteVersion1

typedef struct ArrayJustificationMethodSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayJustificationMethodRef arrayjustificationmethod);
	void (*Release) ( ArrayJustificationMethodRef arrayjustificationmethod);
	ATEBool8 (*IsNull) ( ArrayJustificationMethodRef arrayjustificationmethod);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayJustificationMethodRef arrayjustificationmethod, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayJustificationMethodRef arrayjustificationmethod, JustificationMethod* ret);
	ATEErr (*GetLast) ( ArrayJustificationMethodRef arrayjustificationmethod, JustificationMethod* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayJustificationMethodRef arrayjustificationmethod, ATETextDOM::Int32 index, JustificationMethod* ret);

}ArrayJustificationMethodSuite;

//////////////////////////////////////////////
//       --ArrayKashidaWidthSuite--
//////////////////////////////////////////////
#define kArrayKashidaWidthSuite "ATE ArrayKashidaWidth Suite"
#define kArrayKashidaWidthSuiteVersion1 1
#define kArrayKashidaWidthSuiteVersion kArrayKashidaWidthSuiteVersion1

typedef struct ArrayKashidaWidthSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayKashidaWidthRef arraykashidawidth);
	void (*Release) ( ArrayKashidaWidthRef arraykashidawidth);
	ATEBool8 (*IsNull) ( ArrayKashidaWidthRef arraykashidawidth);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayKashidaWidthRef arraykashidawidth, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayKashidaWidthRef arraykashidawidth, KashidaWidth* ret);
	ATEErr (*GetLast) ( ArrayKashidaWidthRef arraykashidawidth, KashidaWidth* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayKashidaWidthRef arraykashidawidth, ATETextDOM::Int32 index, KashidaWidth* ret);

}ArrayKashidaWidthSuite;

//////////////////////////////////////////////
//       --ArrayKashidasSuite--
//////////////////////////////////////////////
#define kArrayKashidasSuite "ATE ArrayKashidas Suite"
#define kArrayKashidasSuiteVersion1 1
#define kArrayKashidasSuiteVersion kArrayKashidasSuiteVersion1

typedef struct ArrayKashidasSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayKashidasRef arraykashidas);
	void (*Release) ( ArrayKashidasRef arraykashidas);
	ATEBool8 (*IsNull) ( ArrayKashidasRef arraykashidas);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayKashidasRef arraykashidas, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayKashidasRef arraykashidas, Kashidas* ret);
	ATEErr (*GetLast) ( ArrayKashidasRef arraykashidas, Kashidas* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayKashidasRef arraykashidas, ATETextDOM::Int32 index, Kashidas* ret);

}ArrayKashidasSuite;

//////////////////////////////////////////////
//       --ArrayDirOverrideSuite--
//////////////////////////////////////////////
#define kArrayDirOverrideSuite "ATE ArrayDirOverride Suite"
#define kArrayDirOverrideSuiteVersion1 1
#define kArrayDirOverrideSuiteVersion kArrayDirOverrideSuiteVersion1

typedef struct ArrayDirOverrideSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayDirOverrideRef arraydiroverride);
	void (*Release) ( ArrayDirOverrideRef arraydiroverride);
	ATEBool8 (*IsNull) ( ArrayDirOverrideRef arraydiroverride);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayDirOverrideRef arraydiroverride, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayDirOverrideRef arraydiroverride, DirOverride* ret);
	ATEErr (*GetLast) ( ArrayDirOverrideRef arraydiroverride, DirOverride* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayDirOverrideRef arraydiroverride, ATETextDOM::Int32 index, DirOverride* ret);

}ArrayDirOverrideSuite;

//////////////////////////////////////////////
//       --ArrayDigitSetSuite--
//////////////////////////////////////////////
#define kArrayDigitSetSuite "ATE ArrayDigitSet Suite"
#define kArrayDigitSetSuiteVersion1 1
#define kArrayDigitSetSuiteVersion kArrayDigitSetSuiteVersion1

typedef struct ArrayDigitSetSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayDigitSetRef arraydigitset);
	void (*Release) ( ArrayDigitSetRef arraydigitset);
	ATEBool8 (*IsNull) ( ArrayDigitSetRef arraydigitset);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayDigitSetRef arraydigitset, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayDigitSetRef arraydigitset, DigitSet* ret);
	ATEErr (*GetLast) ( ArrayDigitSetRef arraydigitset, DigitSet* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayDigitSetRef arraydigitset, ATETextDOM::Int32 index, DigitSet* ret);

}ArrayDigitSetSuite;

//////////////////////////////////////////////
//       --ArrayDiacVPosSuite--
//////////////////////////////////////////////
#define kArrayDiacVPosSuite "ATE ArrayDiacVPos Suite"
#define kArrayDiacVPosSuiteVersion1 1
#define kArrayDiacVPosSuiteVersion kArrayDiacVPosSuiteVersion1

typedef struct ArrayDiacVPosSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayDiacVPosRef arraydiacvpos);
	void (*Release) ( ArrayDiacVPosRef arraydiacvpos);
	ATEBool8 (*IsNull) ( ArrayDiacVPosRef arraydiacvpos);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayDiacVPosRef arraydiacvpos, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayDiacVPosRef arraydiacvpos, DiacVPos* ret);
	ATEErr (*GetLast) ( ArrayDiacVPosRef arraydiacvpos, DiacVPos* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayDiacVPosRef arraydiacvpos, ATETextDOM::Int32 index, DiacVPos* ret);

}ArrayDiacVPosSuite;
#endif

//////////////////////////////////////////////
//       --CharFeaturesSuite--
//////////////////////////////////////////////
#define kCharFeaturesSuite "ATE CharFeatures Suite"
#if SLO_COMPLEXSCRIPT
#define kCharFeaturesSuiteVersion101 101
#define kCharFeaturesSuiteVersion102 102
#define kCharFeaturesSuiteVersion kCharFeaturesSuiteVersion102
#else
#define kCharFeaturesSuiteVersion101 1
#define kCharFeaturesSuiteVersion102 2
#define kCharFeaturesSuiteVersion kCharFeaturesSuiteVersion102
#endif

typedef struct CharFeaturesSuite{

	// Reference count maintenance.
	void (*AddRef) ( CharFeaturesRef charfeatures);
	void (*Release) ( CharFeaturesRef charfeatures);
	ATEBool8 (*IsNull) ( CharFeaturesRef charfeatures);

	// CharFeatures is a complete Set of character attributes that
	// can be applied to text (except for kerning).  They can be used to
	// describe or Set the (1) local character attributes of text (a.k.a.
	// the local overrides or (2) attributes of a named character style.
	//
	// Often, a given CharFeatures instance will only partially define
	// each of its attributes.  The validity of an attribute is
	// determined by an associated boolean.  Calls to "Get" methods
	// return an "isAssigned" boolean that reflects the validity of
	// the returned argument.  Calls to "Set" methods always Set the
	// associated boolean to indicate validity.  Calls to "clear"
	// methods always invalidate that boolean/attribute pair.
	//
	// A character's attribute is determined by an inheritance model.
	// At the top is the "Normal" style which fully defines all
	// attributes.  These can be overriden by a named style or a local
	// override, where an attribute is valid.
	//
	// A given attribute value of a character is determined by starting
	// with the local override for that attribute if it is defined.  If
	// not, then the attribute comes from the corresponding named style
	// (if it exists and) if it is defined.  If all else fails, the
	// default value comes from the "Normal" character style.
	//
	// Default constructor creates a "blank" CharFeatures instance where
	// all attributes are undefined (invalid).
	ATEErr (*Initialize) ( CharFeaturesRef* charfeatures);
	ATEErr (*Clone) ( CharFeaturesRef charfeatures, CharFeaturesRef* ret);
	ATEErr (*GetFont) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontRef* ret);
	ATEErr (*GetFontSize) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetHorizontalScale) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetVerticalScale) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetAutoLeading) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetLeading) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetTracking) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetBaselineShift) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetCharacterRotation) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	/** Kern type information is only available for CharStyle instances.
	Use Story::GetKern( ) to obtain kern type information for a TextRange.
	*/
	ATEErr (*GetAutoKernType) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, AutoKernType* ret);
	ATEErr (*GetFontCapsOption) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontCapsOption* ret);
	ATEErr (*GetFontBaselineOption) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontBaselineOption* ret);
	ATEErr (*GetFontOpenTypePositionOption) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontOpenTypePositionOption* ret);
	ATEErr (*GetStrikethroughPosition) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, StrikethroughPosition* ret);
	ATEErr (*GetUnderlinePosition) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, UnderlinePosition* ret);
	ATEErr (*GetUnderlineOffset) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr (*GetLigature) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetDiscretionaryLigatures) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetContextualLigatures) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetAlternateLigatures) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetOldStyle) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetFractions) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetOrdinals) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetSwash) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetTitling) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetConnectionForms) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetStylisticAlternates) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetStylisticSets) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetOrnaments) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetFigureStyle) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, FigureStyle* ret);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr (*GetProportionalMetrics) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetKana) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetRuby) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetItalics) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetBaselineDirection) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, BaselineDirection* ret);
	ATEErr (*GetLanguage) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, Language* ret);
	ATEErr (*GetJapaneseAlternateFeature) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, JapaneseAlternateFeature* ret);
	ATEErr (*GetTsume) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetStyleRunAlignment) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, StyleRunAlignment* ret);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr (*GetWariChuEnabled) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetWariChuLineCount) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetWariChuLineGap) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetWariChuScale) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetWariChuSize) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetWariChuWidowAmount) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetWariChuOrphanAmount) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetWariChuJustification) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, WariChuJustification* ret);
	ATEErr (*GetTCYUpDownAdjustment) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetTCYLeftRightAdjustment) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetLeftAki) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetRightAki) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetNoBreak) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetFillColor) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
	ATEErr (*GetStrokeColor) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
	ATEErr (*GetFill) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetStroke) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetFillFirst) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetFillOverPrint) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetStrokeOverPrint) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetLineCap) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, LineCapType* ret);
	ATEErr (*GetLineJoin) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, LineJoinType* ret);
	ATEErr (*GetLineWidth) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetMiterLimit) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetLineDashOffset) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetLineDashArray) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ArrayRealRef* ret);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr (*GetKashidas) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, Kashidas* ret);
	ATEErr (*GetDirOverride) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, DirOverride* ret);
	ATEErr (*GetDigitSet) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, DigitSet* ret);
	ATEErr (*GetDiacVPos) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, DiacVPos* ret);
	ATEErr (*GetDiacXOffset) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetDiacYOffset) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetAutoMydfb) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetMarkYDistFromBaseline) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetOverlapSwash) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetJustificationAlternates) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetStretchedAlternates) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
#endif
	// SET PROPERTIES
	// ======================================================================
	ATEErr (*SetFont) ( CharFeaturesRef charfeatures, FontRef newVal);
	/** Set font size
	This function will throw kOutOfRange error if (newVal > 1296 || newVal < 0.1)
	*/
	ATEErr (*SetFontSize) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	/** Set Horizontal Scale
	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
	If newVal is 1, this means 100% in the character palatte.
	*/
	ATEErr (*SetHorizontalScale) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	/** Set Vertical Scale
	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
	If newVal is 1, this means 100% in the character palatte.
	*/
	ATEErr (*SetVerticalScale) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetAutoLeading) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetLeading) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetTracking) ( CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetBaselineShift) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetCharacterRotation) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetAutoKernType) ( CharFeaturesRef charfeatures, AutoKernType newVal);
	ATEErr (*SetFontCapsOption) ( CharFeaturesRef charfeatures, FontCapsOption newVal);
	ATEErr (*SetFontBaselineOption) ( CharFeaturesRef charfeatures, FontBaselineOption newVal);
	ATEErr (*SetFontOpenTypePositionOption) ( CharFeaturesRef charfeatures, FontOpenTypePositionOption newVal);
	ATEErr (*SetStrikethroughPosition) ( CharFeaturesRef charfeatures, StrikethroughPosition newVal);
	ATEErr (*SetUnderlinePosition) ( CharFeaturesRef charfeatures, UnderlinePosition newVal);
	ATEErr (*SetUnderlineOffset) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr (*SetLigature) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetDiscretionaryLigatures) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetContextualLigatures) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetAlternateLigatures) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetOldStyle) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetFractions) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetOrdinals) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetSwash) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetTitling) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetConnectionForms) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetStylisticAlternates) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetStylisticSets) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetOrnaments) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetFigureStyle) ( CharFeaturesRef charfeatures, FigureStyle newVal);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr (*SetProportionalMetrics) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetKana) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetItalics) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetRuby) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetBaselineDirection) ( CharFeaturesRef charfeatures, BaselineDirection newVal);
	ATEErr (*SetLanguage) ( CharFeaturesRef charfeatures, Language newVal);
	ATEErr (*SetJapaneseAlternateFeature) ( CharFeaturesRef charfeatures, JapaneseAlternateFeature newVal);
	ATEErr (*SetTsume) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetStyleRunAlignment) ( CharFeaturesRef charfeatures, StyleRunAlignment newVal);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr (*SetWariChuEnabled) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetWariChuLineCount) ( CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetWariChuLineGap) ( CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetWariChuScale) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetWariChuSize) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetWariChuWidowAmount) ( CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetWariChuOrphanAmount) ( CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetWariChuJustification) ( CharFeaturesRef charfeatures, WariChuJustification newVal);
	ATEErr (*SetTCYUpDownAdjustment) ( CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetTCYLeftRightAdjustment) ( CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetLeftAki) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetRightAki) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetNoBreak) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetFillColor) ( CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
	ATEErr (*SetStrokeColor) ( CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
	ATEErr (*SetFill) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetStroke) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetFillFirst) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetFillOverPrint) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetStrokeOverPrint) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetLineCap) ( CharFeaturesRef charfeatures, LineCapType newVal);
	ATEErr (*SetLineJoin) ( CharFeaturesRef charfeatures, LineJoinType newVal);
	ATEErr (*SetLineWidth) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetMiterLimit) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetLineDashOffset) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetLineDashArray) ( CharFeaturesRef charfeatures, ArrayRealRef newVal);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr (*SetKashidas) ( CharFeaturesRef charfeatures, Kashidas newVal);
	ATEErr (*SetDirOverride) ( CharFeaturesRef charfeatures, DirOverride newVal);
	ATEErr (*SetDigitSet) ( CharFeaturesRef charfeatures, DigitSet newVal);
	ATEErr (*SetDiacVPos) ( CharFeaturesRef charfeatures, DiacVPos newVal);
	ATEErr (*SetDiacXOffset) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetDiacYOffset) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetAutoMydfb) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetMarkYDistFromBaseline) ( CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr (*SetOverlapSwash) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetJustificationAlternates) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetStretchedAlternates) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
#endif
	// CLEAR PROPERTIES
	// ======================================================================
	ATEErr (*ClearFont) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFontSize) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearHorizontalScale) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearVerticalScale) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearAutoLeading) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLeading) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearTracking) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearBaselineShift) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearCharacterRotation) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearAutoKernType) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFontCapsOption) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFontBaselineOption) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFontOpenTypePositionOption) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStrikethroughPosition) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearUnderlinePosition) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearUnderlineOffset) ( CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr (*ClearLigature) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearDiscretionaryLigatures) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearContextualLigatures) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearAlternateLigatures) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearOldStyle) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFractions) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearOrdinals) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearSwash) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearTitling) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearConnectionForms) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStylisticAlternates) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStylisticSets) (CharFeaturesRef charfeatures);
	ATEErr (*ClearOrnaments) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFigureStyle) ( CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr (*ClearProportionalMetrics) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearKana) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearItalics) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearRuby) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearBaselineDirection) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLanguage) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearJapaneseAlternateFeature) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearTsume) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStyleRunAlignment) ( CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr (*ClearWariChuEnabled) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearWariChuLineCount) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearWariChuLineGap) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearWariChuSubLineAmount) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearWariChuWidowAmount) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearWariChuOrphanAmount) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearWariChuJustification) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearTCYUpDownAdjustment) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearTCYLeftRightAdjustment) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLeftAki) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearRightAki) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearNoBreak) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFillColor) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStrokeColor) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFill) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStroke) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFillFirst) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFillOverPrint) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStrokeOverPrint) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLineCap) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLineJoin) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLineWidth) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearMiterLimit) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLineDashOffset) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearLineDashArray) ( CharFeaturesRef charfeatures);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr (*ClearKashidas) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearDirOverride) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearDigitSet) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearDiacVPos) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearDiacXOffset) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearDiacYOffset) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearAutoMydfb) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearMarkYDistFromBaseline) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearOverlapSwash) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearJustificationAlternates) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStretchedAlternates) ( CharFeaturesRef charfeatures);
#endif
	// ALGEBRA METHODS
	// Methods return true if changes were made.
	// ======================================================================
	// Intersection of 2 Features is the intersection of each attribute
	//  on the lhs with the corresponding attribute on the rhs.
	//  Attribute intersections are defined by the following truth table:
	//
	// ______________________________________________________________________
	//  this.attribute | rhs.attribute || Action/Result
	// ======================================================================
	//  assigned  | assigned  || [Case 1] If values are equal
	//      |    ||  ACTION: nothing
	//      |    ||  RESULT: value preserved
	//      |    || [Case 2] If values are not equal
	//      |    ||  ACTION: if (*this.attribute != *rhs.attribute)
	//      |    ||      this.attribute.Clear();
	//      |    ||  RESULT: unassigned
	// ----------------------------------------------------------------------
	//  assigned  | unassigned || ACTION: this.attribute.Clear()
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | assigned  || ACTION: nothing (this.attribute already unassigned)
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | unassigned || ACTION: nothing (both are equal)
	//     |    || RESULT: unassigned
	// ______________________________________________________________________
	//
	ATEErr (*IntersectFeatures) ( CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
	// ReplaceOrAddFeatures sets the attribute value for any that are assigned on the rhs.
	ATEErr (*ReplaceOrAddFeatures) ( CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
	// Unassigns each attribute whose value equals value of corresponding attribute in rhs
	ATEErr (*UnassignEachIfEqual) ( CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
	// True if all are not assigned; false otherwise
	ATEErr (*IsEachNotAssigned) ( CharFeaturesRef charfeatures, ATEBool8* ret);
	// True if all are assigned; false otherwise
	ATEErr (*IsEachAssigned) ( CharFeaturesRef charfeatures, ATEBool8* ret);
	// ACCESSORS DESIGNED FOR CLIENT APPLICATION CORE
	// ======================================================================
	// ------------------------------------------------------------------
	// Visibility Feature
	// ------------------------------------------------------------------
	ATEErr (*GetFillVisible) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetStrokeVisible) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*SetFillVisible) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*SetStrokeVisible) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*ClearFillVisible) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearStrokeVisible) ( CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// Text Background Color Feature
	// ------------------------------------------------------------------
	ATEErr (*GetFillBackgroundColor) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
	ATEErr (*GetFillBackground) ( CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*SetFillBackgroundColor) ( CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
	ATEErr (*SetFillBackground) ( CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr (*ClearFillBackgroundColor) ( CharFeaturesRef charfeatures);
	ATEErr (*ClearFillBackground) ( CharFeaturesRef charfeatures);
}CharFeaturesSuite;

typedef struct CharFeatures1Suite {

	// Reference count maintenance.
	void(*AddRef) (CharFeaturesRef charfeatures);
	void(*Release) (CharFeaturesRef charfeatures);
	ATEBool8(*IsNull) (CharFeaturesRef charfeatures);

	// CharFeatures is a complete Set of character attributes that
	// can be applied to text (except for kerning).  They can be used to
	// describe or Set the (1) local character attributes of text (a.k.a.
	// the local overrides or (2) attributes of a named character style.
	//
	// Often, a given CharFeatures instance will only partially define
	// each of its attributes.  The validity of an attribute is
	// determined by an associated boolean.  Calls to "Get" methods
	// return an "isAssigned" boolean that reflects the validity of
	// the returned argument.  Calls to "Set" methods always Set the
	// associated boolean to indicate validity.  Calls to "clear"
	// methods always invalidate that boolean/attribute pair.
	//
	// A character's attribute is determined by an inheritance model.
	// At the top is the "Normal" style which fully defines all
	// attributes.  These can be overriden by a named style or a local
	// override, where an attribute is valid.
	//
	// A given attribute value of a character is determined by starting
	// with the local override for that attribute if it is defined.  If
	// not, then the attribute comes from the corresponding named style
	// (if it exists and) if it is defined.  If all else fails, the
	// default value comes from the "Normal" character style.
	//
	// Default constructor creates a "blank" CharFeatures instance where
	// all attributes are undefined (invalid).
	ATEErr(*Initialize) (CharFeaturesRef* charfeatures);
	ATEErr(*Clone) (CharFeaturesRef charfeatures, CharFeaturesRef* ret);
	ATEErr(*GetFont) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontRef* ret);
	ATEErr(*GetFontSize) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetHorizontalScale) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetVerticalScale) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetAutoLeading) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetLeading) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetTracking) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr(*GetBaselineShift) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetCharacterRotation) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	/** Kern type information is only available for CharStyle instances.
	Use Story::GetKern( ) to obtain kern type information for a TextRange.
	*/
	ATEErr(*GetAutoKernType) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, AutoKernType* ret);
	ATEErr(*GetFontCapsOption) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontCapsOption* ret);
	ATEErr(*GetFontBaselineOption) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontBaselineOption* ret);
	ATEErr(*GetFontOpenTypePositionOption) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, FontOpenTypePositionOption* ret);
	ATEErr(*GetStrikethroughPosition) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, StrikethroughPosition* ret);
	ATEErr(*GetUnderlinePosition) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, UnderlinePosition* ret);
	ATEErr(*GetUnderlineOffset) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr(*GetLigature) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetDiscretionaryLigatures) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetContextualLigatures) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetAlternateLigatures) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetOldStyle) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetFractions) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetOrdinals) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetSwash) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetTitling) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetConnectionForms) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetStylisticAlternates) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetOrnaments) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetFigureStyle) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, FigureStyle* ret);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr(*GetProportionalMetrics) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetKana) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetRuby) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetItalics) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetBaselineDirection) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, BaselineDirection* ret);
	ATEErr(*GetLanguage) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, Language* ret);
	ATEErr(*GetJapaneseAlternateFeature) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, JapaneseAlternateFeature* ret);
	ATEErr(*GetTsume) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetStyleRunAlignment) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, StyleRunAlignment* ret);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr(*GetWariChuEnabled) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetWariChuLineCount) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr(*GetWariChuLineGap) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr(*GetWariChuScale) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetWariChuSize) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetWariChuWidowAmount) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr(*GetWariChuOrphanAmount) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr(*GetWariChuJustification) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, WariChuJustification* ret);
	ATEErr(*GetTCYUpDownAdjustment) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr(*GetTCYLeftRightAdjustment) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr(*GetLeftAki) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetRightAki) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetNoBreak) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetFillColor) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
	ATEErr(*GetStrokeColor) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
	ATEErr(*GetFill) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetStroke) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetFillFirst) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetFillOverPrint) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetStrokeOverPrint) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetLineCap) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, LineCapType* ret);
	ATEErr(*GetLineJoin) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, LineJoinType* ret);
	ATEErr(*GetLineWidth) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetMiterLimit) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetLineDashOffset) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetLineDashArray) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ArrayRealRef* ret);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr(*GetKashidas) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, Kashidas* ret);
	ATEErr(*GetDirOverride) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, DirOverride* ret);
	ATEErr(*GetDigitSet) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, DigitSet* ret);
	ATEErr(*GetDiacVPos) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, DiacVPos* ret);
	ATEErr(*GetDiacXOffset) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetDiacYOffset) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetAutoMydfb) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetMarkYDistFromBaseline) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr(*GetOverlapSwash) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetJustificationAlternates) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetStretchedAlternates) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
#endif
	// SET PROPERTIES
	// ======================================================================
	ATEErr(*SetFont) (CharFeaturesRef charfeatures, FontRef newVal);
	/** Set font size
	This function will throw kOutOfRange error if (newVal > 1296 || newVal < 0.1)
	*/
	ATEErr(*SetFontSize) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	/** Set Horizontal Scale
	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
	If newVal is 1, this means 100% in the character palatte.
	*/
	ATEErr(*SetHorizontalScale) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	/** Set Vertical Scale
	This function will throw kOutOfRange error if (newVal > 100 || newVal < .01)
	If newVal is 1, this means 100% in the character palatte.
	*/
	ATEErr(*SetVerticalScale) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetAutoLeading) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetLeading) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetTracking) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr(*SetBaselineShift) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetCharacterRotation) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetAutoKernType) (CharFeaturesRef charfeatures, AutoKernType newVal);
	ATEErr(*SetFontCapsOption) (CharFeaturesRef charfeatures, FontCapsOption newVal);
	ATEErr(*SetFontBaselineOption) (CharFeaturesRef charfeatures, FontBaselineOption newVal);
	ATEErr(*SetFontOpenTypePositionOption) (CharFeaturesRef charfeatures, FontOpenTypePositionOption newVal);
	ATEErr(*SetStrikethroughPosition) (CharFeaturesRef charfeatures, StrikethroughPosition newVal);
	ATEErr(*SetUnderlinePosition) (CharFeaturesRef charfeatures, UnderlinePosition newVal);
	ATEErr(*SetUnderlineOffset) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr(*SetLigature) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetDiscretionaryLigatures) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetContextualLigatures) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetAlternateLigatures) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetOldStyle) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetFractions) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetOrdinals) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetSwash) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetTitling) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetConnectionForms) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetStylisticAlternates) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetOrnaments) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetFigureStyle) (CharFeaturesRef charfeatures, FigureStyle newVal);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr(*SetProportionalMetrics) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetKana) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetItalics) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetRuby) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetBaselineDirection) (CharFeaturesRef charfeatures, BaselineDirection newVal);
	ATEErr(*SetLanguage) (CharFeaturesRef charfeatures, Language newVal);
	ATEErr(*SetJapaneseAlternateFeature) (CharFeaturesRef charfeatures, JapaneseAlternateFeature newVal);
	ATEErr(*SetTsume) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetStyleRunAlignment) (CharFeaturesRef charfeatures, StyleRunAlignment newVal);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr(*SetWariChuEnabled) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetWariChuLineCount) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr(*SetWariChuLineGap) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr(*SetWariChuScale) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetWariChuSize) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetWariChuWidowAmount) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr(*SetWariChuOrphanAmount) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr(*SetWariChuJustification) (CharFeaturesRef charfeatures, WariChuJustification newVal);
	ATEErr(*SetTCYUpDownAdjustment) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr(*SetTCYLeftRightAdjustment) (CharFeaturesRef charfeatures, ATETextDOM::Int32 newVal);
	ATEErr(*SetLeftAki) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetRightAki) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetNoBreak) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetFillColor) (CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
	ATEErr(*SetStrokeColor) (CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
	ATEErr(*SetFill) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetStroke) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetFillFirst) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetFillOverPrint) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetStrokeOverPrint) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetLineCap) (CharFeaturesRef charfeatures, LineCapType newVal);
	ATEErr(*SetLineJoin) (CharFeaturesRef charfeatures, LineJoinType newVal);
	ATEErr(*SetLineWidth) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetMiterLimit) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetLineDashOffset) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetLineDashArray) (CharFeaturesRef charfeatures, ArrayRealRef newVal);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr(*SetKashidas) (CharFeaturesRef charfeatures, Kashidas newVal);
	ATEErr(*SetDirOverride) (CharFeaturesRef charfeatures, DirOverride newVal);
	ATEErr(*SetDigitSet) (CharFeaturesRef charfeatures, DigitSet newVal);
	ATEErr(*SetDiacVPos) (CharFeaturesRef charfeatures, DiacVPos newVal);
	ATEErr(*SetDiacXOffset) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetDiacYOffset) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetAutoMydfb) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetMarkYDistFromBaseline) (CharFeaturesRef charfeatures, ATETextDOM::Float newVal);
	ATEErr(*SetOverlapSwash) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetJustificationAlternates) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetStretchedAlternates) (CharFeaturesRef charfeatures, ATEBool8 newVal);
#endif
	// CLEAR PROPERTIES
	// ======================================================================
	ATEErr(*ClearFont) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFontSize) (CharFeaturesRef charfeatures);
	ATEErr(*ClearHorizontalScale) (CharFeaturesRef charfeatures);
	ATEErr(*ClearVerticalScale) (CharFeaturesRef charfeatures);
	ATEErr(*ClearAutoLeading) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLeading) (CharFeaturesRef charfeatures);
	ATEErr(*ClearTracking) (CharFeaturesRef charfeatures);
	ATEErr(*ClearBaselineShift) (CharFeaturesRef charfeatures);
	ATEErr(*ClearCharacterRotation) (CharFeaturesRef charfeatures);
	ATEErr(*ClearAutoKernType) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFontCapsOption) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFontBaselineOption) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFontOpenTypePositionOption) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStrikethroughPosition) (CharFeaturesRef charfeatures);
	ATEErr(*ClearUnderlinePosition) (CharFeaturesRef charfeatures);
	ATEErr(*ClearUnderlineOffset) (CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr(*ClearLigature) (CharFeaturesRef charfeatures);
	ATEErr(*ClearDiscretionaryLigatures) (CharFeaturesRef charfeatures);
	ATEErr(*ClearContextualLigatures) (CharFeaturesRef charfeatures);
	ATEErr(*ClearAlternateLigatures) (CharFeaturesRef charfeatures);
	ATEErr(*ClearOldStyle) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFractions) (CharFeaturesRef charfeatures);
	ATEErr(*ClearOrdinals) (CharFeaturesRef charfeatures);
	ATEErr(*ClearSwash) (CharFeaturesRef charfeatures);
	ATEErr(*ClearTitling) (CharFeaturesRef charfeatures);
	ATEErr(*ClearConnectionForms) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStylisticAlternates) (CharFeaturesRef charfeatures);
	ATEErr(*ClearOrnaments) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFigureStyle) (CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr(*ClearProportionalMetrics) (CharFeaturesRef charfeatures);
	ATEErr(*ClearKana) (CharFeaturesRef charfeatures);
	ATEErr(*ClearItalics) (CharFeaturesRef charfeatures);
	ATEErr(*ClearRuby) (CharFeaturesRef charfeatures);
	ATEErr(*ClearBaselineDirection) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLanguage) (CharFeaturesRef charfeatures);
	ATEErr(*ClearJapaneseAlternateFeature) (CharFeaturesRef charfeatures);
	ATEErr(*ClearTsume) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStyleRunAlignment) (CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr(*ClearWariChuEnabled) (CharFeaturesRef charfeatures);
	ATEErr(*ClearWariChuLineCount) (CharFeaturesRef charfeatures);
	ATEErr(*ClearWariChuLineGap) (CharFeaturesRef charfeatures);
	ATEErr(*ClearWariChuSubLineAmount) (CharFeaturesRef charfeatures);
	ATEErr(*ClearWariChuWidowAmount) (CharFeaturesRef charfeatures);
	ATEErr(*ClearWariChuOrphanAmount) (CharFeaturesRef charfeatures);
	ATEErr(*ClearWariChuJustification) (CharFeaturesRef charfeatures);
	ATEErr(*ClearTCYUpDownAdjustment) (CharFeaturesRef charfeatures);
	ATEErr(*ClearTCYLeftRightAdjustment) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLeftAki) (CharFeaturesRef charfeatures);
	ATEErr(*ClearRightAki) (CharFeaturesRef charfeatures);
	ATEErr(*ClearNoBreak) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFillColor) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStrokeColor) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFill) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStroke) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFillFirst) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFillOverPrint) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStrokeOverPrint) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLineCap) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLineJoin) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLineWidth) (CharFeaturesRef charfeatures);
	ATEErr(*ClearMiterLimit) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLineDashOffset) (CharFeaturesRef charfeatures);
	ATEErr(*ClearLineDashArray) (CharFeaturesRef charfeatures);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr(*ClearKashidas) (CharFeaturesRef charfeatures);
	ATEErr(*ClearDirOverride) (CharFeaturesRef charfeatures);
	ATEErr(*ClearDigitSet) (CharFeaturesRef charfeatures);
	ATEErr(*ClearDiacVPos) (CharFeaturesRef charfeatures);
	ATEErr(*ClearDiacXOffset) (CharFeaturesRef charfeatures);
	ATEErr(*ClearDiacYOffset) (CharFeaturesRef charfeatures);
	ATEErr(*ClearAutoMydfb) (CharFeaturesRef charfeatures);
	ATEErr(*ClearMarkYDistFromBaseline) (CharFeaturesRef charfeatures);
	ATEErr(*ClearOverlapSwash) (CharFeaturesRef charfeatures);
	ATEErr(*ClearJustificationAlternates) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStretchedAlternates) (CharFeaturesRef charfeatures);
#endif
	// ALGEBRA METHODS
	// Methods return true if changes were made.
	// ======================================================================
	// Intersection of 2 Features is the intersection of each attribute
	//  on the lhs with the corresponding attribute on the rhs.
	//  Attribute intersections are defined by the following truth table:
	//
	// ______________________________________________________________________
	//  this.attribute | rhs.attribute || Action/Result
	// ======================================================================
	//  assigned  | assigned  || [Case 1] If values are equal
	//      |    ||  ACTION: nothing
	//      |    ||  RESULT: value preserved
	//      |    || [Case 2] If values are not equal
	//      |    ||  ACTION: if (*this.attribute != *rhs.attribute)
	//      |    ||      this.attribute.Clear();
	//      |    ||  RESULT: unassigned
	// ----------------------------------------------------------------------
	//  assigned  | unassigned || ACTION: this.attribute.Clear()
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | assigned  || ACTION: nothing (this.attribute already unassigned)
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | unassigned || ACTION: nothing (both are equal)
	//     |    || RESULT: unassigned
	// ______________________________________________________________________
	//
	ATEErr(*IntersectFeatures) (CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
	// ReplaceOrAddFeatures sets the attribute value for any that are assigned on the rhs.
	ATEErr(*ReplaceOrAddFeatures) (CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
	// Unassigns each attribute whose value equals value of corresponding attribute in rhs
	ATEErr(*UnassignEachIfEqual) (CharFeaturesRef charfeatures, CharFeaturesRef rhs, ATEBool8* ret);
	// True if all are not assigned; false otherwise
	ATEErr(*IsEachNotAssigned) (CharFeaturesRef charfeatures, ATEBool8* ret);
	// True if all are assigned; false otherwise
	ATEErr(*IsEachAssigned) (CharFeaturesRef charfeatures, ATEBool8* ret);
	// ACCESSORS DESIGNED FOR CLIENT APPLICATION CORE
	// ======================================================================
	// ------------------------------------------------------------------
	// Visibility Feature
	// ------------------------------------------------------------------
	ATEErr(*GetFillVisible) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*GetStrokeVisible) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*SetFillVisible) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*SetStrokeVisible) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*ClearFillVisible) (CharFeaturesRef charfeatures);
	ATEErr(*ClearStrokeVisible) (CharFeaturesRef charfeatures);
	// ------------------------------------------------------------------
	// Text Background Color Feature
	// ------------------------------------------------------------------
	ATEErr(*GetFillBackgroundColor) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ApplicationPaintRef* ret);
	ATEErr(*GetFillBackground) (CharFeaturesRef charfeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr(*SetFillBackgroundColor) (CharFeaturesRef charfeatures, ApplicationPaintRef newVal);
	ATEErr(*SetFillBackground) (CharFeaturesRef charfeatures, ATEBool8 newVal);
	ATEErr(*ClearFillBackgroundColor) (CharFeaturesRef charfeatures);
	ATEErr(*ClearFillBackground) (CharFeaturesRef charfeatures);
}CharFeatures1Suite;

//////////////////////////////////////////////
//       --CharInspectorSuite--
//////////////////////////////////////////////
#define kCharInspectorSuite "ATE CharInspector Suite"
#if SLO_COMPLEXSCRIPT
#define kCharInspectorSuiteVersion101 101
#define kCharInspectorSuiteVersion102 102
#define kCharInspectorSuiteVersion kCharInspectorSuiteVersion102
#else
#define kCharInspectorSuiteVersion101 1
#define kCharInspectorSuiteVersion102 2
#define kCharInspectorSuiteVersion kCharInspectorSuiteVersion102
#endif

typedef struct CharInspectorSuite{

	// Reference count maintenance.
	void (*AddRef) ( CharInspectorRef charinspector);
	void (*Release) ( CharInspectorRef charinspector);
	ATEBool8 (*IsNull) ( CharInspectorRef charinspector);

	ATEErr (*Initialize) ( CharInspectorRef* charinspector);
	ATEErr (*GetFont) ( CharInspectorRef charinspector, ArrayFontRefRef* ret);
	ATEErr (*GetFontSize) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetHorizontalScale) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetVerticalScale) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetSyntheticBold) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetSyntheticItalic) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetAutoLeading) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetLeading) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetTracking) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetBaselineShift) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetCharacterRotation) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetFontCapsOption) ( CharInspectorRef charinspector, ArrayFontCapsOptionRef* ret);
	ATEErr (*GetFontBaselineOption) ( CharInspectorRef charinspector, ArrayFontBaselineOptionRef* ret);
	ATEErr (*GetFontOpenTypePositionOption) ( CharInspectorRef charinspector, ArrayFontOpenTypePositionOptionRef* ret);
	ATEErr (*GetStrikethroughPosition) ( CharInspectorRef charinspector, ArrayStrikethroughPositionRef* ret);
	ATEErr (*GetUnderlinePosition) ( CharInspectorRef charinspector, ArrayUnderlinePositionRef* ret);
	ATEErr (*GetUnderlineOffset) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr (*GetLigature) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetDiscretionaryLigatures) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetContextualLigatures) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetAlternateLigatures) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetOldStyle) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetFractions) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetOrdinals) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetSwash) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetTitling) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetConnectionForms) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetStylisticAlternates) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetStylisticSets) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetOrnaments) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetFigureStyle) ( CharInspectorRef charinspector, ArrayFigureStyleRef* ret);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr (*GetProportionalMetrics) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetKana) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetItalics) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetRuby) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetBaselineDirection) ( CharInspectorRef charinspector, ArrayBaselineDirectionRef* ret);
	ATEErr (*GetLanguage) ( CharInspectorRef charinspector, ArrayLanguageRef* ret);
	ATEErr (*GetTsume) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetStyleRunAlignment) ( CharInspectorRef charinspector, ArrayStyleRunAlignmentRef* ret);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr (*GetWariChuLineCount) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetWariChuLineGap) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetWariChuScale) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetWariChuSize) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetWariChuWidowAmount) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetWariChuOrphanAmount) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetWariChuJustification) ( CharInspectorRef charinspector, ArrayWariChuJustificationRef* ret);
	ATEErr (*GetWariChuEnabled) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetTCYUpDownAdjustment) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetTCYLeftRightAdjustment) ( CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr (*GetLeftAki) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetRightAki) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetNoBreak) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetFillColor) ( CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
	ATEErr (*GetStrokeColor) ( CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
	ATEErr (*GetFill) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetStroke) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetFillFirst) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetFillOverPrint) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetStrokeOverPrint) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetLineCap) ( CharInspectorRef charinspector, ArrayLineCapTypeRef* ret);
	ATEErr (*GetLineJoin) ( CharInspectorRef charinspector, ArrayLineJoinTypeRef* ret);
	ATEErr (*GetLineWidth) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetMiterLimit) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetLineDashOffset) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetLineDashArray) ( CharInspectorRef charinspector, ArrayArrayRealRef* ret);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr (*GetKashidas) ( CharInspectorRef charinspector, ArrayKashidasRef* ret);
	ATEErr (*GetDirOverride) ( CharInspectorRef charinspector, ArrayDirOverrideRef* ret);
	ATEErr (*GetDigitSet) ( CharInspectorRef charinspector, ArrayDigitSetRef* ret);
	ATEErr (*GetDiacVPos) ( CharInspectorRef charinspector, ArrayDiacVPosRef* ret);
	ATEErr (*GetDiacXOffset) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetDiacYOffset) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetAutoMydfb) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetMarkYDistFromBaseline) ( CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr (*GetOverlapSwash) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetJustificationAlternates) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetStretchedAlternates) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
#endif
	// ------------------------------------------------------------------
	// Visibility Feature
	// ------------------------------------------------------------------
	ATEErr (*GetFillVisible) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr (*GetStrokeVisible) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
	// ------------------------------------------------------------------
	// Text Background Color Feature
	// ------------------------------------------------------------------
	ATEErr (*GetFillBackgroundColor) ( CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
	ATEErr (*GetFillBackground) ( CharInspectorRef charinspector, ArrayBoolRef* ret);
}CharInspectorSuite;

typedef struct CharInspector1Suite {

	// Reference count maintenance.
	void(*AddRef) (CharInspectorRef charinspector);
	void(*Release) (CharInspectorRef charinspector);
	ATEBool8(*IsNull) (CharInspectorRef charinspector);

	ATEErr(*Initialize) (CharInspectorRef* charinspector);
	ATEErr(*GetFont) (CharInspectorRef charinspector, ArrayFontRefRef* ret);
	ATEErr(*GetFontSize) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetHorizontalScale) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetVerticalScale) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetSyntheticBold) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetSyntheticItalic) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetAutoLeading) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetLeading) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetTracking) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr(*GetBaselineShift) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetCharacterRotation) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetFontCapsOption) (CharInspectorRef charinspector, ArrayFontCapsOptionRef* ret);
	ATEErr(*GetFontBaselineOption) (CharInspectorRef charinspector, ArrayFontBaselineOptionRef* ret);
	ATEErr(*GetFontOpenTypePositionOption) (CharInspectorRef charinspector, ArrayFontOpenTypePositionOptionRef* ret);
	ATEErr(*GetStrikethroughPosition) (CharInspectorRef charinspector, ArrayStrikethroughPositionRef* ret);
	ATEErr(*GetUnderlinePosition) (CharInspectorRef charinspector, ArrayUnderlinePositionRef* ret);
	ATEErr(*GetUnderlineOffset) (CharInspectorRef charinspector, ArrayRealRef* ret);
	// ------------------------------------------------------------------
	// OpenType features
	// ------------------------------------------------------------------
	ATEErr(*GetLigature) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetDiscretionaryLigatures) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetContextualLigatures) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetAlternateLigatures) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetOldStyle) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetFractions) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetOrdinals) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetSwash) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetTitling) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetConnectionForms) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetStylisticAlternates) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetOrnaments) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetFigureStyle) (CharInspectorRef charinspector, ArrayFigureStyleRef* ret);
	// ------------------------------------------------------------------
	// Japanese OpenType feature support
	// ------------------------------------------------------------------
	ATEErr(*GetProportionalMetrics) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetKana) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetItalics) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetRuby) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetBaselineDirection) (CharInspectorRef charinspector, ArrayBaselineDirectionRef* ret);
	ATEErr(*GetLanguage) (CharInspectorRef charinspector, ArrayLanguageRef* ret);
	ATEErr(*GetTsume) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetStyleRunAlignment) (CharInspectorRef charinspector, ArrayStyleRunAlignmentRef* ret);
	// ------------------------------------------------------------------
	// WariChu Setings
	// ------------------------------------------------------------------
	ATEErr(*GetWariChuLineCount) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr(*GetWariChuLineGap) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr(*GetWariChuScale) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetWariChuSize) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetWariChuWidowAmount) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr(*GetWariChuOrphanAmount) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr(*GetWariChuJustification) (CharInspectorRef charinspector, ArrayWariChuJustificationRef* ret);
	ATEErr(*GetWariChuEnabled) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetTCYUpDownAdjustment) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr(*GetTCYLeftRightAdjustment) (CharInspectorRef charinspector, ArrayIntegerRef* ret);
	ATEErr(*GetLeftAki) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetRightAki) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetNoBreak) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetFillColor) (CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
	ATEErr(*GetStrokeColor) (CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
	ATEErr(*GetFill) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetStroke) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetFillFirst) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetFillOverPrint) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetStrokeOverPrint) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetLineCap) (CharInspectorRef charinspector, ArrayLineCapTypeRef* ret);
	ATEErr(*GetLineJoin) (CharInspectorRef charinspector, ArrayLineJoinTypeRef* ret);
	ATEErr(*GetLineWidth) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetMiterLimit) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetLineDashOffset) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetLineDashArray) (CharInspectorRef charinspector, ArrayArrayRealRef* ret);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script Setings
	// ------------------------------------------------------------------
	ATEErr(*GetKashidas) (CharInspectorRef charinspector, ArrayKashidasRef* ret);
	ATEErr(*GetDirOverride) (CharInspectorRef charinspector, ArrayDirOverrideRef* ret);
	ATEErr(*GetDigitSet) (CharInspectorRef charinspector, ArrayDigitSetRef* ret);
	ATEErr(*GetDiacVPos) (CharInspectorRef charinspector, ArrayDiacVPosRef* ret);
	ATEErr(*GetDiacXOffset) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetDiacYOffset) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetAutoMydfb) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetMarkYDistFromBaseline) (CharInspectorRef charinspector, ArrayRealRef* ret);
	ATEErr(*GetOverlapSwash) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetJustificationAlternates) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetStretchedAlternates) (CharInspectorRef charinspector, ArrayBoolRef* ret);
#endif
	// ------------------------------------------------------------------
	// Visibility Feature
	// ------------------------------------------------------------------
	ATEErr(*GetFillVisible) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	ATEErr(*GetStrokeVisible) (CharInspectorRef charinspector, ArrayBoolRef* ret);
	// ------------------------------------------------------------------
	// Text Background Color Feature
	// ------------------------------------------------------------------
	ATEErr(*GetFillBackgroundColor) (CharInspectorRef charinspector, ArrayApplicationPaintRefRef* ret);
	ATEErr(*GetFillBackground) (CharInspectorRef charinspector, ArrayBoolRef* ret);
}CharInspector1Suite;

//////////////////////////////////////////////
//       --CharStyleSuite--
//////////////////////////////////////////////
#define kCharStyleSuite "ATE CharStyle Suite"
#define kCharStyleSuiteVersion1 1
#define kCharStyleSuiteVersion kCharStyleSuiteVersion1

typedef struct CharStyleSuite{

	// Reference count maintenance.
	void (*AddRef) ( CharStyleRef charstyle);
	void (*Release) ( CharStyleRef charstyle);
	ATEBool8 (*IsNull) ( CharStyleRef charstyle);

	/// Name of style is set in pName up to maxLength characters.
	/// Length of actual name is returned; 0 if error occurred.
	ATEErr (*GetName) ( CharStyleRef charstyle, ATETextDOM::Unicode* pName, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	/// Sets name of style to null-terminated pName.  If existing style of
	/// same name exists or *pName == L'\0' then false is returned.
	ATEErr (*SetName) ( CharStyleRef charstyle, const ATETextDOM::Unicode* pName, ATEBool8* ret);
	/// Parent style returned.  For Normal style, a null object is returned.
	ATEErr (*GetParent) ( CharStyleRef charstyle, CharStyleRef* ret);
	/// Parent style set.  Returns false if attempting to set the parent
	/// of Normal style, true otherwise.
	ATEErr (*SetParent) ( CharStyleRef charstyle, const CharStyleRef pStyle, ATEBool8* ret);
	/// Returns whether style has parent.  Always false for normal style.
	ATEErr (*HasParent) ( CharStyleRef charstyle, ATEBool8* ret);
	/// Returns features for style.
	ATEErr (*GetFeatures) ( CharStyleRef charstyle, CharFeaturesRef* ret);
	/// The style's feature attributes are all assigned to those of pFeatures.
	/// For Normal style, this has same effect as ReplaceOrAddFeatures.
	ATEErr (*SetFeatures) ( CharStyleRef charstyle, CharFeaturesRef pFeatures);
	/// The style's feature attributes are replaced by any corresponding ones
	/// in pFeatures that contain valid values (i.e. the attribute is assigned).
	ATEErr (*ReplaceOrAddFeatures) ( CharStyleRef charstyle, CharFeaturesRef pFeatures);
	ATEErr (*IsEqual) ( CharStyleRef charstyle, const CharStyleRef pStyle, ATEBool8* ret);

}CharStyleSuite;

//////////////////////////////////////////////
//       --CharStylesSuite--
//////////////////////////////////////////////
#define kCharStylesSuite "ATE CharStyles Suite"
#define kCharStylesSuiteVersion1 1
#define kCharStylesSuiteVersion kCharStylesSuiteVersion1

typedef struct CharStylesSuite{

	// Reference count maintenance.
	void (*AddRef) ( CharStylesRef charstyles);
	void (*Release) ( CharStylesRef charstyles);
	ATEBool8 (*IsNull) ( CharStylesRef charstyles);

	ATEErr (*IsEmpty) ( CharStylesRef charstyles, ATEBool8* ret);
	ATEErr (*GetSize) ( CharStylesRef charstyles, ATETextDOM::Int32* ret);
	ATEErr (*ShowAllStyles) ( CharStylesRef charstyles);
	ATEErr (*ShowOnlyUnreferencedStyles) ( CharStylesRef charstyles);
	ATEErr (*ShowOnlyStylesReferencedIn) ( CharStylesRef charstyles, TextRangeRef pRange);
	// Reorders position of style
	ATEErr (*MoveStyleTo) ( CharStylesRef charstyles, CharStyleRef pStyle, ATETextDOM::Int32 position);

}CharStylesSuite;

//////////////////////////////////////////////
//       --CharStylesIteratorSuite--
//////////////////////////////////////////////
#define kCharStylesIteratorSuite "ATE CharStylesIterator Suite"
#define kCharStylesIteratorSuiteVersion1 1
#define kCharStylesIteratorSuiteVersion kCharStylesIteratorSuiteVersion1

typedef struct CharStylesIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( CharStylesIteratorRef charstylesiterator);
	void (*Release) ( CharStylesIteratorRef charstylesiterator);
	ATEBool8 (*IsNull) ( CharStylesIteratorRef charstylesiterator);

	ATEErr (*Initialize) ( CharStylesRef pStyles, Direction direction, CharStylesIteratorRef* charstylesiterator);
	ATEErr (*IsNotDone) ( CharStylesIteratorRef charstylesiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( CharStylesIteratorRef charstylesiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( CharStylesIteratorRef charstylesiterator, ATEBool8* ret);
	ATEErr (*MoveToFirst) ( CharStylesIteratorRef charstylesiterator);
	ATEErr (*MoveToLast) ( CharStylesIteratorRef charstylesiterator);
	ATEErr (*Next) ( CharStylesIteratorRef charstylesiterator);
	ATEErr (*Previous) ( CharStylesIteratorRef charstylesiterator);
	ATEErr (*Item) ( CharStylesIteratorRef charstylesiterator, CharStyleRef* ret);

}CharStylesIteratorSuite;

//////////////////////////////////////////////
//       --FindSuite--
//////////////////////////////////////////////
#define kFindSuite "ATE Find Suite"
#if SLO_COMPLEXSCRIPT
#define kFindSuiteVersion101 101
#define kFindSuiteVersion kFindSuiteVersion101
#else
#define kFindSuiteVersion1 1
#define kFindSuiteVersion kFindSuiteVersion1
#endif

typedef struct FindSuite{

	// Reference count maintenance.
	void (*AddRef) ( FindRef find);
	void (*Release) ( FindRef find);
	ATEBool8 (*IsNull) ( FindRef find);

	// Options
	// ========================================================================
	ATEErr (*GetSearchDirection) ( FindRef find, Direction* ret);
	ATEErr (*GetIgnoreCase) ( FindRef find, ATEBool8* ret);
	ATEErr (*GetWholeWord) ( FindRef find, ATEBool8* ret);
	ATEErr (*GetWrap) ( FindRef find, ATEBool8* ret);
	ATEErr (*GetFindWordsOutOfBounds) ( FindRef find, ATEBool8* ret);
	ATEErr (*SetSearchDirection) ( FindRef find, Direction newValue);
	ATEErr (*SetIgnoreCase) ( FindRef find, ATEBool8 newValue);
	ATEErr (*SetWholeWord) ( FindRef find, ATEBool8 newValue);
	ATEErr (*SetWrap) ( FindRef find, ATEBool8 newValue);
	ATEErr (*SetFindWordsOutOfBounds) ( FindRef find, ATEBool8 newValue);
	// Control scope of search to be entire document or Story.
	// By default, the entire document is searched.
	ATEErr (*GetSearchScope) ( FindRef find, SearchScope* ret);
	ATEErr (*SetSearchScope) ( FindRef find, SearchScope searchScope);
	// If called, search is done only within specified TextRange
	ATEErr (*SetSearchRange) ( FindRef find, TextRangeRef pRange);
	ATEErr (*SetSearchChars) ( FindRef find, ATETextDOM::Unicode* pSearchChars);
	ATEErr (*GetSearchChars) ( FindRef find, ATETextDOM::Unicode* pSearchChars, ATETextDOM::Int32 length);
	ATEErr (*SetReplaceChars) ( FindRef find, ATETextDOM::Unicode* pSearchChars);
	ATEErr (*GetReplaceChars) ( FindRef find, ATETextDOM::Unicode* pSearchChars, ATETextDOM::Int32 length);
	// Temporary way to reset the engine for modeless operation
	ATEErr (*Reset) ( FindRef find);
	// Methods
	// ========================================================================
	// Searches current user selection.
	// Returns false if the search failed
	ATEErr (*FindMatch) ( FindRef find, TextRangeRef pTextRange, ATEBool8* ret);
	// Skips the current user selection.
	// Returns false if the search failed
	ATEErr (*FindNextMatch) ( FindRef find, TextRangeRef pTextRange, ATEBool8* ret);
	ATEErr (*ReplaceMatch) ( FindRef find, TextRangeRef pTextRange, ATEBool8 findNext, ATEBool8* ret);
	// DEPRECATED - this is now a no-op.  Use GetPreReplaceAllSettings( ) and
	// RestorePreReplaceAllSettings( ) to implement ReplaceAll in the plugin.
	ATEErr (*FindAndReplaceAllMatches) ( FindRef find, ATETextDOM::Int32* pReplaceCount, ATEBool8* ret);
	// Use these to implement ReplaceAll.
	// Start by saving off the settings with GetPreReplaceAllSettings( )
	// (also note what text object you're currently working with so you can restore that
	// via SetSearchRange( ) when you're finished.
	ATEErr (*GetPreReplaceAllSettings) ( FindRef find, ATETextDOM::Int32* pCurrentPoint, ATETextDOM::Int32* pStartPoint);
	// Implement a loop to go through all the text objects you want to replace all with.
	// Use FindMatch( ), FindNextMatch( ), and ReplaceMatch( ) to replace all.
	// Keep track of how many ReplaceMatch( ) calls were made for reporting back to the user
	// When finished, restore the correct text object and range using SetSearchRange( )
	// and restore the positions using RestorePreReplaceAllSettings( )
	ATEErr (*RestorePreReplaceAllSettings) ( FindRef find, const ATETextDOM::Int32 currentPoint, const ATETextDOM::Int32 startPoint);
#if SLO_COMPLEXSCRIPT
	ATEErr (*GetIgnoreAccents) ( FindRef find, ATEBool8* ret);
	ATEErr (*GetIgnoreKashidas) ( FindRef find, ATEBool8* ret);
	ATEErr (*SetIgnoreAccents) ( FindRef find, ATEBool8 newValue);
	ATEErr (*SetIgnoreKashidas) ( FindRef find, ATEBool8 newValue);
#endif
}FindSuite;

//////////////////////////////////////////////
//       --FontSuite--
//////////////////////////////////////////////
#define kFontSuite "ATE Font Suite"
#define kFontSuiteVersion1 1
#define kFontSuiteVersion kFontSuiteVersion1

typedef struct FontSuite{

	// Reference count maintenance.
	void (*AddRef) ( FontRef font);
	void (*Release) ( FontRef font);
	ATEBool8 (*IsNull) ( FontRef font);

	// METHODS
	// ========================================================================
	ATEErr (*IsCoolTypeTechnology) ( FontRef font, ATEBool8* ret);
	/// if this font has its roman glyphs sideway by default.
	ATEErr (*IsVerticalRomanGlyphsOnSideByDefault) ( FontRef font, ATEBool8 withItalics, StyleRunAlignment characterAlignment, ATEBool8* ret);
	ATEErr (*GetCTFontDict) ( FontRef font, void** ret);

}FontSuite;

//////////////////////////////////////////////
//       --GlyphSuite--
//////////////////////////////////////////////
#define kGlyphSuite "ATE Glyph Suite"
#define kGlyphSuiteVersion1 1
#define kGlyphSuiteVersion kGlyphSuiteVersion1

typedef struct GlyphSuite{

	// Reference count maintenance.
	void (*AddRef) ( GlyphRef glyph);
	void (*Release) ( GlyphRef glyph);
	ATEBool8 (*IsNull) ( GlyphRef glyph);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetGlyphID) ( GlyphRef glyph, ATEGlyphID* ret);
	ATEErr (*GetAlternateGlyphs) ( GlyphRef glyph, GlyphsRef* ret);
	ATEErr (*GetOTFeatures) ( GlyphRef glyph, char** otFeatures, ATETextDOM::Int32* otFeatureCount, ATETextDOM::Int32** otFeatureIndex);
	// RealMatrix   GetTransformation();
	// ========================================================================
	// METHODS
	// ========================================================================
	// =============================================================================
	// PROTECTED AND PRIVATE
	// =============================================================================

}GlyphSuite;

//////////////////////////////////////////////
//       --GlyphsSuite--
//////////////////////////////////////////////
#define kGlyphsSuite "ATE Glyphs Suite"
#define kGlyphsSuiteVersion1 1
#define kGlyphsSuiteVersion kGlyphsSuiteVersion1

typedef struct GlyphsSuite{

	// Reference count maintenance.
	void (*AddRef) ( GlyphsRef glyphs);
	void (*Release) ( GlyphsRef glyphs);
	ATEBool8 (*IsNull) ( GlyphsRef glyphs);

	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( GlyphsRef glyphs, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( GlyphsRef glyphs, GlyphRef* ret);
	ATEErr (*GetLast) ( GlyphsRef glyphs, GlyphRef* ret);
	// navigation objects.
	ATEErr (*GetTextRanges) ( GlyphsRef glyphs, TextRangesRef* ret);
	ATEErr (*GetTextSelection) ( GlyphsRef glyphs, TextRangesRef* ret);
	ATEErr (*GetParagraphsIterator) ( GlyphsRef glyphs, ParagraphsIteratorRef* ret);
	ATEErr (*GetTextRunsIterator) ( GlyphsRef glyphs, TextRunsIteratorRef* ret);
	ATEErr (*GetWordsIterator) ( GlyphsRef glyphs, WordsIteratorRef* ret);
	// METHODS
	// ========================================================================
	ATEErr (*Add) ( GlyphsRef glyphs, const GlyphRef glyph);
	ATEErr (*Item) ( GlyphsRef glyphs, ATETextDOM::Int32 nIndex, GlyphRef* ret);
	ATEErr (*RemoveAll) ( GlyphsRef glyphs);
	ATEErr (*Remove) ( GlyphsRef glyphs, ATETextDOM::Int32 nIndex);
	// PROTECTED AND PRIVATE
	// ========================================================================

}GlyphsSuite;

//////////////////////////////////////////////
//       --GlyphsIteratorSuite--
//////////////////////////////////////////////
#define kGlyphsIteratorSuite "ATE GlyphsIterator Suite"
#define kGlyphsIteratorSuiteVersion1 1
#define kGlyphsIteratorSuiteVersion kGlyphsIteratorSuiteVersion1

typedef struct GlyphsIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( GlyphsIteratorRef glyphsiterator);
	void (*Release) ( GlyphsIteratorRef glyphsiterator);
	ATEBool8 (*IsNull) ( GlyphsIteratorRef glyphsiterator);

	ATEErr (*Initialize) ( GlyphsRef glyphs, Direction direction, GlyphsIteratorRef* glyphsiterator);
	ATEErr (*IsNotDone) ( GlyphsIteratorRef glyphsiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( GlyphsIteratorRef glyphsiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( GlyphsIteratorRef glyphsiterator, ATEBool8* ret);
	ATEErr (*GetFirst) ( GlyphsIteratorRef glyphsiterator, GlyphRef* ret);
	ATEErr (*GetLast) ( GlyphsIteratorRef glyphsiterator, GlyphRef* ret);
	ATEErr (*GetNext) ( GlyphsIteratorRef glyphsiterator, GlyphRef* ret);
	ATEErr (*Item) ( GlyphsIteratorRef glyphsiterator, GlyphRef* ret);
	ATEErr (*Next) ( GlyphsIteratorRef glyphsiterator);
	ATEErr (*Previous) ( GlyphsIteratorRef glyphsiterator);

}GlyphsIteratorSuite;

//////////////////////////////////////////////
//       --KinsokuSuite--
//////////////////////////////////////////////
#define kKinsokuSuite "ATE Kinsoku Suite"
#define kKinsokuSuiteVersion1 1
#define kKinsokuSuiteVersion kKinsokuSuiteVersion1

typedef struct KinsokuSuite{

	// Reference count maintenance.
	void (*AddRef) ( KinsokuRef kinsoku);
	void (*Release) ( KinsokuRef kinsoku);
	ATEBool8 (*IsNull) ( KinsokuRef kinsoku);

	/// Constructs an empty Kinsoku
	ATEErr (*Initialize) ( KinsokuRef* kinsoku);
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetName) ( KinsokuRef kinsoku, ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetNameSize) ( KinsokuRef kinsoku, ATETextDOM::Int32* ret);
	ATEErr (*SetName) ( KinsokuRef kinsoku, const ATETextDOM::Unicode* name);
	ATEErr (*MatchesPredefinedResourceTag) ( KinsokuRef kinsoku, ATE::KinsokuPredefinedTag tag, ATEBool8* ret);
	ATEErr (*GetNoStartCharSet) ( KinsokuRef kinsoku, ATETextDOM::Unicode* noStartCharSet, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetNoStartCharSetSize) ( KinsokuRef kinsoku, ATETextDOM::Int32* ret);
	ATEErr (*SetNoStartCharSet) ( KinsokuRef kinsoku, const ATETextDOM::Unicode* noStartCharSet);
	ATEErr (*GetNoEndCharSet) ( KinsokuRef kinsoku, ATETextDOM::Unicode* noEndCharSet, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetNoEndCharSetSize) ( KinsokuRef kinsoku, ATETextDOM::Int32* ret);
	ATEErr (*SetNoEndCharSet) ( KinsokuRef kinsoku, const ATETextDOM::Unicode* noEndCharSet);
	ATEErr (*GetNoBreakCharSet) ( KinsokuRef kinsoku, ATETextDOM::Unicode* noBreakCharSet, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetNoBreakCharSetSize) ( KinsokuRef kinsoku, ATETextDOM::Int32* ret);
	ATEErr (*SetNoBreakCharSet) ( KinsokuRef kinsoku, const ATETextDOM::Unicode* noBreakCharSet);
	ATEErr (*GetHangingCharSet) ( KinsokuRef kinsoku, ATETextDOM::Unicode* hangingCharSet, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetHangingCharSetSize) ( KinsokuRef kinsoku, ATETextDOM::Int32* ret);
	ATEErr (*SetHangingCharSet) ( KinsokuRef kinsoku, const ATETextDOM::Unicode* hangingCharSet);
	// METHODS
	// =======================================================================
	ATEErr (*IsNoStartChar) ( KinsokuRef kinsoku, ATETextDOM::Unicode character, ATEBool8* ret);
	ATEErr (*IsNoEndChar) ( KinsokuRef kinsoku, ATETextDOM::Unicode character, ATEBool8* ret);
	ATEErr (*IsNoBreakChar) ( KinsokuRef kinsoku, ATETextDOM::Unicode character, ATEBool8* ret);
	ATEErr (*IsHangingChar) ( KinsokuRef kinsoku, ATETextDOM::Unicode character, ATEBool8* ret);
	/// Does a shallow equivalency test
	ATEErr (*IsEqual) ( KinsokuRef kinsoku, KinsokuRef rhsKinsoku, ATEBool8* ret);
	/// Does a deep equivalency test
	ATEErr (*IsEquivalent) ( KinsokuRef kinsoku, KinsokuRef rhsKinsoku, ATEBool8* ret);
	/// Has the resource been modified since it became editable?
	ATEErr (*IsModified) ( KinsokuRef kinsoku, ATEBool8* ret);
	/// Is it a predefined or user defined kinsoku?
	ATEErr (*IsPredefined) ( KinsokuRef kinsoku, ATEBool8* ret);
	ATEErr (*Duplicate) ( KinsokuRef kinsoku, KinsokuRef* ret);

}KinsokuSuite;

//////////////////////////////////////////////
//       --KinsokuSetSuite--
//////////////////////////////////////////////
#define kKinsokuSetSuite "ATE KinsokuSet Suite"
#define kKinsokuSetSuiteVersion1 1
#define kKinsokuSetSuiteVersion kKinsokuSetSuiteVersion1

typedef struct KinsokuSetSuite{

	// Reference count maintenance.
	void (*AddRef) ( KinsokuSetRef kinsokuset);
	void (*Release) ( KinsokuSetRef kinsokuset);
	ATEBool8 (*IsNull) ( KinsokuSetRef kinsokuset);

	// PROPERTIES
	// =======================================================================
	ATEErr (*GetSize) ( KinsokuSetRef kinsokuset, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( KinsokuSetRef kinsokuset, KinsokuRef* ret);
	ATEErr (*GetLast) ( KinsokuSetRef kinsokuset, KinsokuRef* ret);
	// METHODS
	// =======================================================================
	ATEErr (*Item) ( KinsokuSetRef kinsokuset, ATETextDOM::Int32 nIndex, KinsokuRef* ret);
	/// Returns a valid index if found, else return -1
	/// This will search for kinsoku with the same name and data
	ATEErr (*Find_ByKinsoku) ( KinsokuSetRef kinsokuset, KinsokuRef kinsoku, ATETextDOM::Int32* ret);
	/// Returns a valid index if found, else return -1
	/// Search by name only
	ATEErr (*Find_ByName) ( KinsokuSetRef kinsokuset, const ATETextDOM::Unicode* name, ATETextDOM::Int32* ret);
	/// Returns a valid index if found, else return -1
	/// If kUserDefinedKinsokuTag is requested for search, it will return the
	/// first user defined kinsoku it finds.
	ATEErr (*Find_ByPredefinedKinsokuTag) ( KinsokuSetRef kinsokuset, KinsokuPredefinedTag tag, ATETextDOM::Int32* ret);
	/// Removes an existing kinsoku, returns true if successful
	ATEErr (*Remove) ( KinsokuSetRef kinsokuset, ATETextDOM::Int32 nIndex, ATEBool8* ret);
	/// Appends a new kinsoku, returns its new index if successful,
	/// -1 if unsuccessful
	/// If the kinsoku being added already exists in the set, it will
	/// return its current index.
	ATEErr (*Add) ( KinsokuSetRef kinsokuset, KinsokuRef kinsoku, ATETextDOM::Int32* ret);
	/// Replaces an existing kinsoku at the given index with the
	/// given kinsoku.  Returns true if successful
	ATEErr (*Replace) ( KinsokuSetRef kinsokuset, ATETextDOM::Int32 nIndex, KinsokuRef kinsoku, ATEBool8* ret);

}KinsokuSetSuite;

//////////////////////////////////////////////
//       --ParaFeaturesSuite--
//////////////////////////////////////////////
#define kParaFeaturesSuite "ATE ParaFeatures Suite"
#if SLO_COMPLEXSCRIPT
#define kParaFeaturesSuiteVersion101 101
#define kParaFeaturesSuiteVersion kParaFeaturesSuiteVersion101
#else
#define kParaFeaturesSuiteVersion1 1
#define kParaFeaturesSuiteVersion kParaFeaturesSuiteVersion1
#endif

typedef struct ParaFeaturesSuite{

	// Reference count maintenance.
	void (*AddRef) ( ParaFeaturesRef parafeatures);
	void (*Release) ( ParaFeaturesRef parafeatures);
	ATEBool8 (*IsNull) ( ParaFeaturesRef parafeatures);

	// ParaFeatures is a complete Set of paragraph attributes that
	// can be applied to text (except for kerning).  They can be used to
	// describe or Set the (1) local paragraph attributes of text (a.k.a.
	// the local overrides or (2) attributes of a named paragraph style.
	//
	// Often, a given ParaFeatures instance will only partially define
	// each of its attributes.  The validity of an attribute is
	// determined by an associated boolean.  Calls to "Get" methods
	// return an "isAssigned" boolean that reflects the validity of
	// the returned argument.  Calls to "Set" methods always Set the
	// associated boolean to indicate validity.  Calls to "Clear"
	// methods always invalidate that boolean/attribute pair.
	//
	// A paragraph's attribute is determined by an inheritance model.
	// At the top is the "Normal" style which fully defines all
	// attributes.  These can be overriden by a named style or a local
	// override, where an attribute is valid.
	//
	// A given attribute value of a paragraph is determined by starting
	// with the local override for that attribute if it is defined.  If
	// not, then the attribute comes from the corresponding named style
	// (if it exists and) if it is defined.  If all else fails, the
	// default value comes from the "Normal" paragraph style.
	//
	// Default constructor creates a "blank" ParaFeatures instance where
	// all attributes are undefined (invalid).
	ATEErr (*Initialize) ( ParaFeaturesRef* parafeatures);
	ATEErr (*Clone) ( ParaFeaturesRef parafeatures, ParaFeaturesRef* ret);
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	ATEErr (*GetJustification) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ParagraphJustification* ret);
	ATEErr (*GetFirstLineIndent) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetStartIndent) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetEndIndent) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetSpaceBefore) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetSpaceAfter) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	ATEErr (*GetAutoHyphenate) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetHyphenatedWordSize) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetPreHyphenSize) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetPostHyphenSize) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetConsecutiveHyphenLimit) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetHyphenationZone) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetHyphenateCapitalized) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetHyphenationPreference) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	ATEErr (*GetDesiredWordSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetMaxWordSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetMinWordSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetDesiredLetterSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetMaxLetterSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetMinLetterSpacing) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetDesiredGlyphScaling) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetMaxGlyphScaling) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetMinGlyphScaling) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetSingleWordJustification) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ParagraphJustification* ret);
	ATEErr (*GetAutoLeadingPercentage) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	ATEErr (*GetLeadingType) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, LeadingType* ret);
	ATEErr (*GetTabStops) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, TabStopsRef* ret);
	ATEErr (*GetDefaultTabWidth) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Float* ret);
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	ATEErr (*GetHangingRoman) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetAutoTCY) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATETextDOM::Int32* ret);
	ATEErr (*GetBunriKinshi) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetBurasagariType) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, BurasagariType* ret);
	ATEErr (*GetPreferredKinsokuOrder) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, PreferredKinsokuOrder* ret);
	ATEErr (*GetKurikaeshiMojiShori) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
	/// This will return a null object if Kinsoku is not used (ie None set)
	ATEErr (*GetKinsoku) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, KinsokuRef* ret);
	/// This will return a null object if Mojikumi is not used (ie None set)
	ATEErr (*GetMojiKumi) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, MojiKumiRef* ret);
	// Other
	ATEErr (*GetEveryLineComposer) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATEBool8* ret);
	ATEErr (*GetDefaultCharFeatures) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, CharFeaturesRef* ret);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script
	// ------------------------------------------------------------------
	ATEErr (*GetParagraphDirection) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATE::ParagraphDirection* ret);
	ATEErr (*GetJustificationMethod) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATE::JustificationMethod* ret);
	ATEErr (*GetKashidaWidth) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATE::KashidaWidth* ret);
#endif
	// SET PROPERTIES
	// ======================================================================
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	ATEErr (*SetJustification) ( ParaFeaturesRef parafeatures, ParagraphJustification newVal);
	ATEErr (*SetFirstLineIndent) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetStartIndent) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetEndIndent) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetSpaceBefore) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetSpaceAfter) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	ATEErr (*SetAutoHyphenate) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
	ATEErr (*SetHyphenatedWordSize) ( ParaFeaturesRef parafeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetPreHyphenSize) ( ParaFeaturesRef parafeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetPostHyphenSize) ( ParaFeaturesRef parafeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetConsecutiveHyphenLimit) ( ParaFeaturesRef parafeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetHyphenationZone) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetHyphenateCapitalized) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
	ATEErr (*SetHyphenationPreference) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	ATEErr (*SetDesiredWordSpacing) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetMaxWordSpacing) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetMinWordSpacing) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetDesiredLetterSpacing) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetMaxLetterSpacing) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetMinLetterSpacing) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetDesiredGlyphScaling) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetMaxGlyphScaling) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetMinGlyphScaling) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetSingleWordJustification) ( ParaFeaturesRef parafeatures, ParagraphJustification newVal);
	ATEErr (*SetAutoLeadingPercentage) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	ATEErr (*SetLeadingType) ( ParaFeaturesRef parafeatures, LeadingType newVal);
	ATEErr (*SetTabStops) ( ParaFeaturesRef parafeatures, TabStopsRef newVal);
	ATEErr (*SetDefaultTabWidth) ( ParaFeaturesRef parafeatures, ATETextDOM::Float newVal);
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	ATEErr (*SetHangingRoman) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
	ATEErr (*SetAutoTCY) ( ParaFeaturesRef parafeatures, ATETextDOM::Int32 newVal);
	ATEErr (*SetBunriKinshi) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
	ATEErr (*SetBurasagariType) ( ParaFeaturesRef parafeatures, BurasagariType newVal);
	ATEErr (*SetPreferredKinsokuOrder) ( ParaFeaturesRef parafeatures, PreferredKinsokuOrder newVal);
	ATEErr (*SetKurikaeshiMojiShori) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
	ATEErr (*SetKinsoku) ( ParaFeaturesRef parafeatures, KinsokuRef newVal);
	ATEErr (*SetMojiKumi) ( ParaFeaturesRef parafeatures, MojiKumiRef newVal);
	// Other
	ATEErr (*SetEveryLineComposer) ( ParaFeaturesRef parafeatures, ATEBool8 newVal);
	ATEErr (*SetDefaultCharFeatures) ( ParaFeaturesRef parafeatures, CharFeaturesRef newVal);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script
	// ------------------------------------------------------------------
	ATEErr (*SetParagraphDirection) ( ParaFeaturesRef parafeatures, ATE::ParagraphDirection newVal);
	ATEErr (*SetJustificationMethod) ( ParaFeaturesRef parafeatures, ATE::JustificationMethod newVal);
	ATEErr (*SetKashidaWidth) ( ParaFeaturesRef parafeatures, ATE::KashidaWidth newVal);
#endif
	// CLEAR PROPERTIES
	// ======================================================================
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	ATEErr (*ClearJustification) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearFirstLineIndent) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearStartIndent) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearEndIndent) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearSpaceBefore) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearSpaceAfter) ( ParaFeaturesRef parafeatures);
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	ATEErr (*ClearAutoHyphenate) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearHyphenatedWordSize) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearPreHyphenSize) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearPostHyphenSize) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearConsecutiveHyphenLimit) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearHyphenationZone) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearHyphenateCapitalized) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearHyphenationPreference) ( ParaFeaturesRef parafeatures);
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	ATEErr (*ClearWordSpacing) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearLetterSpacing) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearGlyphScaling) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearSingleWordJustification) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearAutoLeadingPercentage) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearLeadingType) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearTabStops) ( ParaFeaturesRef parafeatures);
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	ATEErr (*ClearHangingRoman) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearAutoTCY) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearBunriKinshi) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearBurasagariType) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearPreferredKinsokuOrder) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearKurikaeshiMojiShori) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearKinsoku) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearMojiKumi) ( ParaFeaturesRef parafeatures);
	// Other
	ATEErr (*ClearEveryLineComposer) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearDefaultCharFeatures) ( ParaFeaturesRef parafeatures);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script
	// ------------------------------------------------------------------
	ATEErr (*ClearParagraphDirection) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearJustificationMethod) ( ParaFeaturesRef parafeatures);
	ATEErr (*ClearKashidaWidth) ( ParaFeaturesRef parafeatures);
#endif
	// ALGEBRA METHODS
	// Methods return true if changes were made.
	// ======================================================================
	// Intersection of 2 Features is the intersection of each attribute
	//  on the lhs with the corresponding attribute on the rhs.
	//  Attribute intersections are defined by the following truth table:
	//
	// ______________________________________________________________________
	//  this.attribute | rhs.attribute || Action/Result
	// ======================================================================
	//  assigned  | assigned  || [Case 1] If values are equal
	//      |    ||  ACTION: nothing
	//      |    ||  RESULT: value preserved
	//      |    || [Case 2] If values are not equal
	//      |    ||  ACTION: if (*this.attribute != *rhs.attribute)
	//      |    ||      this.attribute.Clear();
	//      |    ||  RESULT: unassigned
	// ----------------------------------------------------------------------
	//  assigned  | unassigned || ACTION: this.attribute.Clear()
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | assigned  || ACTION: nothing (this.attribute already unassigned)
	//     |    || RESULT: unassigned
	// ----------------------------------------------------------------------
	//  unassigned  | unassigned || ACTION: nothing (both are equal)
	//     |    || RESULT: unassigned
	// ______________________________________________________________________
	//
	ATEErr (*IntersectFeatures) ( ParaFeaturesRef parafeatures, ParaFeaturesRef rhs, ATEBool8* ret);
	// ReplaceOrAddFeatures sets the attribute value for any that are assigned on the rhs.
	ATEErr (*ReplaceOrAddFeatures) ( ParaFeaturesRef parafeatures, ParaFeaturesRef rhs, ATEBool8* ret);
	// Unassigns each attribute whose value equals value of corresponding attribute in rhs
	ATEErr (*UnassignEachIfEqual) ( ParaFeaturesRef parafeatures, const ParaFeaturesRef rhs, ATEBool8* ret);
	// True if all are not assigned; false otherwise
	ATEErr (*IsEachNotAssigned) ( ParaFeaturesRef parafeatures, ATEBool8* ret);
	// True if all are assigned; false otherwise
	ATEErr (*IsEachAssigned) ( ParaFeaturesRef parafeatures, ATEBool8* ret);
	// Composer Engine
	ATEErr (*GetComposerEngine) ( ParaFeaturesRef parafeatures, ATEBool8* isAssigned, ATE::ComposerEngine* ret);
	ATEErr (*SetComposerEngine) ( ParaFeaturesRef parafeatures, ATE::ComposerEngine newVal);
	ATEErr (*ClearComposerEngine) ( ParaFeaturesRef parafeatures);
	// PRIVATE AND PROTECTED
	// ======================================================================

}ParaFeaturesSuite;

//////////////////////////////////////////////
//       --ParagraphSuite--
//////////////////////////////////////////////
#define kParagraphSuite "ATE Paragraph Suite"
#define kParagraphSuiteVersion1 1
#define kParagraphSuiteVersion kParagraphSuiteVersion1

typedef struct ParagraphSuite{

	// Reference count maintenance.
	void (*AddRef) ( ParagraphRef paragraph);
	void (*Release) ( ParagraphRef paragraph);
	ATEBool8 (*IsNull) ( ParagraphRef paragraph);

	// PROPERTIES
	// ========================================================================
	ATEErr (*GetLength) ( ParagraphRef paragraph, ATETextDOM::Int32* ret);
	// navigation objects.
	ATEErr (*GetStory) ( ParagraphRef paragraph, StoryRef* ret);
	ATEErr (*GetTextRange) ( ParagraphRef paragraph, TextRangeRef* ret);
	ATEErr (*GetTextRanges) ( ParagraphRef paragraph, TextRangesRef* ret);
	ATEErr (*GetTextSelection) ( ParagraphRef paragraph, TextRangesRef* ret);
	ATEErr (*GetWordsIterator) ( ParagraphRef paragraph, WordsIteratorRef* ret);
	// METHODS
	// ========================================================================
	ATEErr (*GetNext) ( ParagraphRef paragraph, ParagraphRef* ret);
	ATEErr (*GetPrev) ( ParagraphRef paragraph, ParagraphRef* ret);
	ATEErr (*GetContents_AsUnicode) ( ParagraphRef paragraph, ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength, ATETextDOM::ATETextDomErr* ret);
	ATEErr (*GetContents_AsChar) ( ParagraphRef paragraph, char* text, ATETextDOM::Int32 maxLength, ATETextDOM::ATETextDomErr* ret);

}ParagraphSuite;

//////////////////////////////////////////////
//       --ParagraphsIteratorSuite--
//////////////////////////////////////////////
#define kParagraphsIteratorSuite "ATE ParagraphsIterator Suite"
#define kParagraphsIteratorSuiteVersion1 1
#define kParagraphsIteratorSuiteVersion kParagraphsIteratorSuiteVersion1

typedef struct ParagraphsIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( ParagraphsIteratorRef paragraphsiterator);
	void (*Release) ( ParagraphsIteratorRef paragraphsiterator);
	ATEBool8 (*IsNull) ( ParagraphsIteratorRef paragraphsiterator);

	ATEErr (*Initialize) ( TextRangesRef ranges, Direction direction, ParagraphsIteratorRef* paragraphsiterator);
	ATEErr (*IsDone) ( ParagraphsIteratorRef paragraphsiterator, ATEBool8* ret);
	ATEErr (*IsNotDone) ( ParagraphsIteratorRef paragraphsiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( ParagraphsIteratorRef paragraphsiterator, ATEBool8* ret);
	ATEErr (*MoveToFirst) ( ParagraphsIteratorRef paragraphsiterator);
	ATEErr (*MoveToLast) ( ParagraphsIteratorRef paragraphsiterator);
	ATEErr (*Next) ( ParagraphsIteratorRef paragraphsiterator);
	ATEErr (*Item) ( ParagraphsIteratorRef paragraphsiterator, ParagraphRef* ret);

}ParagraphsIteratorSuite;

//////////////////////////////////////////////
//       --ParaInspectorSuite--
//////////////////////////////////////////////
#define kParaInspectorSuite "ATE ParaInspector Suite"
#if SLO_COMPLEXSCRIPT
#define kParaInspectorSuiteVersion101 101
#define kParaInspectorSuiteVersion kParaInspectorSuiteVersion101
#else
#define kParaInspectorSuiteVersion1 1
#define kParaInspectorSuiteVersion kParaInspectorSuiteVersion1
#endif

typedef struct ParaInspectorSuite{

	// Reference count maintenance.
	void (*AddRef) ( ParaInspectorRef parainspector);
	void (*Release) ( ParaInspectorRef parainspector);
	ATEBool8 (*IsNull) ( ParaInspectorRef parainspector);

	ATEErr (*Initialize) ( ParaInspectorRef* parainspector);
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	ATEErr (*GetJustification) ( ParaInspectorRef parainspector, ArrayParagraphJustificationRef* ret);
	ATEErr (*GetFirstLineIndent) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetStartIndent) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetEndIndent) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetSpaceBefore) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetSpaceAfter) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	ATEErr (*GetAutoHyphenate) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
	ATEErr (*GetHyphenatedWordSize) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
	ATEErr (*GetPreHyphenSize) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
	ATEErr (*GetPostHyphenSize) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
	ATEErr (*GetConsecutiveHyphenLimit) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
	ATEErr (*GetHyphenationZone) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetHyphenateCapitalized) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
	ATEErr (*GetHyphenationPreference) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	ATEErr (*GetDesiredWordSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetMaxWordSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetMinWordSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetDesiredLetterSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetMaxLetterSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetMinLetterSpacing) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetDesiredGlyphScaling) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetMaxGlyphScaling) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetMinGlyphScaling) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetSingleWordJustification) ( ParaInspectorRef parainspector, ArrayParagraphJustificationRef* ret);
	ATEErr (*GetAutoLeadingPercentage) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	ATEErr (*GetLeadingType) ( ParaInspectorRef parainspector, ArrayLeadingTypeRef* ret);
	ATEErr (*GetTabStops) ( ParaInspectorRef parainspector, ArrayTabStopsRefRef* ret);
	ATEErr (*GetDefaultTabWidth) ( ParaInspectorRef parainspector, ArrayRealRef* ret);
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	ATEErr (*GetHangingRoman) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
	ATEErr (*GetAutoTCY) ( ParaInspectorRef parainspector, ArrayIntegerRef* ret);
	ATEErr (*GetBunriKinshi) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
	ATEErr (*GetBurasagariType) ( ParaInspectorRef parainspector, ArrayBurasagariTypeRef* ret);
	ATEErr (*GetPreferredKinsokuOrder) ( ParaInspectorRef parainspector, ArrayPreferredKinsokuOrderRef* ret);
	ATEErr (*GetKurikaeshiMojiShori) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
	ATEErr (*GetKinsoku) ( ParaInspectorRef parainspector, ArrayKinsokuRefRef* ret);
	ATEErr (*GetMojiKumi) ( ParaInspectorRef parainspector, ArrayMojiKumiRefRef* ret);
	// Other
	ATEErr (*GetEveryLineComposer) ( ParaInspectorRef parainspector, ArrayBoolRef* ret);
#if SLO_COMPLEXSCRIPT
	// ------------------------------------------------------------------
	// Complex Script
	// ------------------------------------------------------------------
	ATEErr (*GetParagraphDirection) ( ParaInspectorRef parainspector, ArrayParagraphDirectionRef* ret);
	ATEErr (*GetJustificationMethod) ( ParaInspectorRef parainspector, ArrayJustificationMethodRef* ret);
	ATEErr (*GetKashidaWidth) ( ParaInspectorRef parainspector, ArrayKashidaWidthRef* ret);
#endif
	ATEErr (*GetComposerEngine) ( ParaInspectorRef parainspector, ArrayComposerEngineRef* ret);
}ParaInspectorSuite;

//////////////////////////////////////////////
//       --ParaStyleSuite--
//////////////////////////////////////////////
#define kParaStyleSuite "ATE ParaStyle Suite"
#define kParaStyleSuiteVersion1 1
#define kParaStyleSuiteVersion kParaStyleSuiteVersion1

typedef struct ParaStyleSuite{

	// Reference count maintenance.
	void (*AddRef) ( ParaStyleRef parastyle);
	void (*Release) ( ParaStyleRef parastyle);
	ATEBool8 (*IsNull) ( ParaStyleRef parastyle);

	/// Name of style is set in pName up to maxLength characters.
	/// Length of actual name is returned; 0 if error occurred.
	ATEErr (*GetName) ( ParaStyleRef parastyle, ATETextDOM::Unicode* pName, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	/// Sets name of style to null-terminated pName.  If existing style of
	/// same name exists or *pName == L'\0' then false is returned.
	ATEErr (*SetName) ( ParaStyleRef parastyle, const ATETextDOM::Unicode* pName, ATEBool8* ret);
	/// Parent style returned.  For Normal style, a null object is returned.
	ATEErr (*GetParent) ( ParaStyleRef parastyle, ParaStyleRef* ret);
	/// Parent style set.  Returns false if attempting to set the parent
	/// of Normal style, true otherwise.
	ATEErr (*SetParent) ( ParaStyleRef parastyle, const ParaStyleRef pStyle, ATEBool8* ret);
	/// Returns whether style has parent.  Always false for normal style.
	ATEErr (*HasParent) ( ParaStyleRef parastyle, ATEBool8* ret);
	/// Returns features for style.
	ATEErr (*GetFeatures) ( ParaStyleRef parastyle, ParaFeaturesRef* ret);
	/// The style's feature attributes are assigned to pFeatures.
	/// For Normal style, this has same effect as ReplaceOrAddFeatures.
	ATEErr (*SetFeatures) ( ParaStyleRef parastyle, ParaFeaturesRef pFeatures);
	/// The style's feature attributes are replaced by any corresponding ones
	/// in pFeatures that contain valid values (i.e. the attribute is assigned).
	ATEErr (*ReplaceOrAddFeatures) ( ParaStyleRef parastyle, ParaFeaturesRef pFeatures);
	ATEErr (*IsEqual) ( ParaStyleRef parastyle, const ParaStyleRef pStyle, ATEBool8* ret);

}ParaStyleSuite;

//////////////////////////////////////////////
//       --ParaStylesSuite--
//////////////////////////////////////////////
#define kParaStylesSuite "ATE ParaStyles Suite"
#define kParaStylesSuiteVersion1 1
#define kParaStylesSuiteVersion kParaStylesSuiteVersion1

typedef struct ParaStylesSuite{

	// Reference count maintenance.
	void (*AddRef) ( ParaStylesRef parastyles);
	void (*Release) ( ParaStylesRef parastyles);
	ATEBool8 (*IsNull) ( ParaStylesRef parastyles);

	ATEErr (*IsEmpty) ( ParaStylesRef parastyles, ATEBool8* ret);
	ATEErr (*GetSize) ( ParaStylesRef parastyles, ATETextDOM::Int32* ret);
	ATEErr (*ShowAllStyles) ( ParaStylesRef parastyles);
	ATEErr (*ShowOnlyUnreferencedStyles) ( ParaStylesRef parastyles);
	ATEErr (*ShowOnlyStylesReferencedIn) ( ParaStylesRef parastyles, TextRangeRef pRange);
	// Reorders position of style
	ATEErr (*MoveStyleTo) ( ParaStylesRef parastyles, ParaStyleRef pStyle, ATETextDOM::Int32 position);

}ParaStylesSuite;

//////////////////////////////////////////////
//       --ParaStylesIteratorSuite--
//////////////////////////////////////////////
#define kParaStylesIteratorSuite "ATE ParaStylesIterator Suite"
#define kParaStylesIteratorSuiteVersion1 1
#define kParaStylesIteratorSuiteVersion kParaStylesIteratorSuiteVersion1

typedef struct ParaStylesIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( ParaStylesIteratorRef parastylesiterator);
	void (*Release) ( ParaStylesIteratorRef parastylesiterator);
	ATEBool8 (*IsNull) ( ParaStylesIteratorRef parastylesiterator);

	ATEErr (*Initialize) ( ParaStylesRef paraStyles, Direction direction, ParaStylesIteratorRef* parastylesiterator);
	ATEErr (*IsNotDone) ( ParaStylesIteratorRef parastylesiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( ParaStylesIteratorRef parastylesiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( ParaStylesIteratorRef parastylesiterator, ATEBool8* ret);
	ATEErr (*MoveToFirst) ( ParaStylesIteratorRef parastylesiterator);
	ATEErr (*MoveToLast) ( ParaStylesIteratorRef parastylesiterator);
	ATEErr (*Next) ( ParaStylesIteratorRef parastylesiterator);
	ATEErr (*Previous) ( ParaStylesIteratorRef parastylesiterator);
	ATEErr (*Item) ( ParaStylesIteratorRef parastylesiterator, ParaStyleRef* ret);

}ParaStylesIteratorSuite;

//////////////////////////////////////////////
//       --SpellSuite--
//////////////////////////////////////////////
#define kSpellSuite "ATE Spell Suite"
#if SLO_COMPLEXSCRIPT
#define kSpellSuiteVersion101 101
#define kSpellSuiteVersion kSpellSuiteVersion101
#else
#define kSpellSuiteVersion1 1
#define kSpellSuiteVersion kSpellSuiteVersion1
#endif

typedef struct SpellSuite{

	// Reference count maintenance.
	void (*AddRef) ( SpellRef spell);
	void (*Release) ( SpellRef spell);
	ATEBool8 (*IsNull) ( SpellRef spell);

	// Options
	// ========================================================================
	ATEErr (*Initialize) ( SpellRef spell );
	ATEErr (*IsInitialized) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*GetIgnoreWordsInAllUppercase) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*GetIgnoreWordsWithNumbers) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*GetIgnoreRomanNumerals) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*GetIgnoreRepeatedWords) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*GetIgnoreUncapitalizedStartOfSentence) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*SetIgnoreWordsInAllUppercase) ( SpellRef spell, ATEBool8 newValue);
	ATEErr (*SetIgnoreWordsWithNumbers) ( SpellRef spell, ATEBool8 newValue);
	ATEErr (*SetIgnoreRomanNumerals) ( SpellRef spell, ATEBool8 newValue);
	ATEErr (*SetIgnoreRepeatedWords) ( SpellRef spell, ATEBool8 newValue);
	ATEErr (*SetIgnoreUncapitalizedStartOfSentence) ( SpellRef spell, ATEBool8 newValue);
	// Control scope of search to be entire document or Story.
	// By default, the entire document is searched.
	ATEErr (*GetSearchScope) ( SpellRef spell, SearchScope* ret);
	ATEErr (*SetSearchScope) ( SpellRef spell, SearchScope searchScope);
	// If called, search is done only within specified TextRange
	ATEErr (*SetSearchRange) ( SpellRef spell, const TextRangeRef pRange, const ATEBool8 resetEndOfSentence, const ATEBool8 resetCurPos);
	// Temporary way to reset the engine for modeless operation
	ATEErr (*Reset) ( SpellRef spell);
	// Use this if the user changes the text significantly enough that you need to reset,
	// but are fairly certain that the text hasn't been changed before the resumePoint.
	ATEErr (*ResumeFrom) ( SpellRef spell, const ATETextDOM::Int32 resumePoint);
	// Use this to resume from the current insertion point.
	ATEErr (*ResumeFromInsertionPoint) ( SpellRef spell);
	// Methods
	// ========================================================================
	// Searches from start for unknown words and return the first one it finds.
	// Returns true if it found an unknown word, false if it searched to the end
	// and didn't find any unknown words.
	ATEErr (*FindOneMisspelledWord) ( SpellRef spell, SpellCheckingResult* pResult, TextRangeRef pRange, Language* pLanguage, ATEBool8* ret);
	// Calling FindOneMisspelledWord( ) will fill up an internal list of suggested
	// corrections.  Use these calls to get the contents of that word list:
	//
	// This will return the size of the buffer required to hold the contents of the word list.
	ATEErr (*GetWordListSize) ( SpellRef spell, ATETextDOM::Int32* ret);
	//
	// This will fill up pWordListBuffer with the contents of the list.
	// sizeOfBuffer is the size of pWordListBuffer (used to prevent overflow)
	// pNumberOfWords is the number of words in the buffer.  The words are all null-terminated.
	ATEErr (*GetWordListContents) ( SpellRef spell, ATETextDOM::Unicode*   pWordListBuffer, ATETextDOM::Int32    sizeOfBuffer, ATETextDOM::Int32*   pNumberOfWords);
	ATEErr (*Replace) ( SpellRef spell, TextRangeRef pRange, const ATETextDOM::Unicode* pCorrection );
	// Use this to add an entry to a pair dictionary, binding the selected word to rCorrection.
	ATEErr (*AddSelectedToReplaceAllDict) ( SpellRef spell, const ATETextDOM::Unicode* pCorrection);
	// DEPRECATED - this is now a no-op.  Use GetPreReplaceAllSettings( ) and
	// RestorePreReplaceAllSettings( ) to implement ReplaceAll in the plugin.
	ATEErr (*DoReplaceAll) ( SpellRef spell, ATEBool8* ret);
	// Use these to implement ReplaceAll.
	// Start by saving off the settings with GetPreReplaceAllSettings( )
	// (also note what text object you're currently working with so you can restore that
	// via SetSearchRange( ) when you're finished.
	ATEErr (*GetPreReplaceAllSettings) ( SpellRef spell, ATETextDOM::Int32* pCurrentPoint, ATEBool8* pFoundSentenceEnd);
	// Implement a loop to go through all the text objects you want to replace all with.
	// Use this to find all instances of the target word in the current text object.
	// Keep calling it until it returns false, making sure to set firstTimeInThisObject as needed.
	// It will return the text range to select and call ReplaceSelected( ) with.
	ATEErr (*FindReplaceAllWord) ( SpellRef spell, TextRangeRef pRange, const ATEBool8 firstTimeInThisObject, ATEBool8* ret);
	// When finished, restore the correct text object and range using SetSearchRange( )
	// and restore the positions using RestorePreReplaceAllSettings( )
	// Order is important here - do notcall RestorePreReplaceAllSettings( ) first,
	// as SetSearchRange( ) will reset the foundSentenceEnd flag.
	ATEErr (*RestorePreReplaceAllSettings) ( SpellRef spell, const ATETextDOM::Int32 currentPoint, const ATEBool8 foundSentenceEnd);
	// The pair dictionary is not automatically cleared.  Call this when you want it cleared.
	ATEErr (*ClearPairDictionary) ( SpellRef spell);
	// Use this for adding words as they're found.
	ATEErr (*AddSelectedToUserDict) ( SpellRef spell);
	// User dictionary access and maintenance - used to manage the dictionary at any time.
	//
	// Calling GetUserDictionaryContents( ) will fill up the same internal list as FindAndSelectOneMisspelledWord( )
	// Use GetWordListSize( ) and GetWordListContents( ) just like with the suggestion list.
	ATEErr (*GetUserDictionaryContents) ( SpellRef spell);
	// now makes sure that there are no spaces (multiple words)
	// Return value reflects success in adding legit word.
	ATEErr (*AddToUserDictionary) ( SpellRef spell, const ATETextDOM::Unicode* pWord, ATEBool8* ret);
	ATEErr (*DeleteFromUserDictionary) ( SpellRef spell, const ATETextDOM::Unicode* pWord);
	ATEErr (*WordExistsInUserDictionary) ( SpellRef spell, const ATETextDOM::Unicode* pWord, ATEBool8* ret);
	// The ignore list is used for storing "ignore all" words.
	ATEErr (*AddSelectedToIgnoreList) ( SpellRef spell);
	// The ignore list is not automatically cleared.  Call this when you want it cleared.
	ATEErr (*ClearIgnoreList) ( SpellRef spell);
	ATEErr (*GetLanguageOfLastMissingDictionary) ( SpellRef spell, Language* ret);
	ATEErr (*GetSpellingDictionaryPath) (SpellRef spell, ATETextDOM::Unicode* path, ATETextDOM::Int32 *ret);
#if SLO_COMPLEXSCRIPT
	//Complex Script
	ATEErr (*GetStrictAlef) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*GetStrictYeh) ( SpellRef spell, ATEBool8* ret);
	ATEErr (*SetStrictAlef) ( SpellRef spell, ATEBool8 newValue);
	ATEErr (*SetStrictYeh) ( SpellRef spell, ATEBool8 newValue);
#endif
}SpellSuite;

//////////////////////////////////////////////
//       --StoriesSuite--
//////////////////////////////////////////////
#define kStoriesSuite "ATE Stories Suite"
#define kStoriesSuiteVersion1 1
#define kStoriesSuiteVersion kStoriesSuiteVersion1

typedef struct StoriesSuite{

	// Reference count maintenance.
	void (*AddRef) ( StoriesRef stories);
	void (*Release) ( StoriesRef stories);
	ATEBool8 (*IsNull) ( StoriesRef stories);

	ATEErr (*GetSize) ( StoriesRef stories, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( StoriesRef stories, StoryRef* ret);
	ATEErr (*GetLast) ( StoriesRef stories, StoryRef* ret);
	/// Only one story might have the focus.  It is the one being edited by keyboard input.
	/// The current focused story might lose focus if multiselection happens outside the focused story, or
	/// a mouse click happens that makes the story lose focus ( like tool bar action ).
	ATEErr (*HasFocus) ( StoriesRef stories, ATEBool8* ret);
	/// Return the focused story, the one being edited.  If there is no text being edited, it will return
	/// a Null object, you can check the return using .IsNull() method.
	ATEErr (*GetFocus) ( StoriesRef stories, StoryRef* ret);
	/// changing focus will deselect everything in the document.
	ATEErr (*SetFocus) ( StoriesRef stories, const StoryRef story);
	ATEErr (*LoseFocus) ( StoriesRef stories);
	// navigation objects.
	ATEErr (*GetTextRanges) ( StoriesRef stories, TextRangesRef* ret);
	ATEErr (*GetTextSelection) ( StoriesRef stories, TextRangesRef* ret);
	ATEErr (*GetParagraphsIterator) ( StoriesRef stories, ParagraphsIteratorRef* ret);
	ATEErr (*GetWordsIterator) ( StoriesRef stories, WordsIteratorRef* ret);
	ATEErr (*GetTextRunsIterator) ( StoriesRef stories, TextRunsIteratorRef* ret);
	ATEErr (*GetDocumentTextResources) ( StoriesRef stories, DocumentTextResourcesRef* ret);
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( StoriesRef stories, ATETextDOM::Int32 nIndex, StoryRef* ret);
	/* Suspend reflow calculation.  This will speed up ITextRange::InsertXXX() call or any call that
	causes a reflow to happen.*/
	ATEErr (*SuspendReflow) ( StoriesRef stories);
	/// Resume reflow calculation.  Make sure to match each SuspendReflow with ResumeReflow.
	ATEErr (*ResumeReflow) ( StoriesRef stories);
	// DOCUMENT METHODS
	// ========================================================================

}StoriesSuite;

//////////////////////////////////////////////
//       --StorySuite--
//////////////////////////////////////////////
#define kStorySuite "ATE Story Suite"
#define kStorySuiteVersion1 1
#define kStorySuiteVersion kStorySuiteVersion1

typedef struct StorySuite{

	// Reference count maintenance.
	void (*AddRef) ( StoryRef story);
	void (*Release) ( StoryRef story);
	ATEBool8 (*IsNull) ( StoryRef story);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	/// Get the index of this story from the stories array.
	ATEErr (*GetIndex) ( StoryRef story, ATETextDOM::Int32* ret);
	/// Get how many characters in this story.
	ATEErr (*GetSize) ( StoryRef story, ATETextDOM::Int32* ret);
	/// navigation objects.
	ATEErr (*GetStories) ( StoryRef story, StoriesRef* ret);
	/// return the text range of this story (0, GetSize()).
	ATEErr (*GetTextRange_ForThisStory) ( StoryRef story, TextRangeRef* ret);
	ATEErr (*GetTextSelection) ( StoryRef story, TextRangesRef* ret);
	ATEErr (*GetParagraphsIterator) ( StoryRef story, ParagraphsIteratorRef* ret);
	ATEErr (*GetWordsIterator) ( StoryRef story, WordsIteratorRef* ret);
	ATEErr (*GetTextRunsIterator) ( StoryRef story, TextRunsIteratorRef* ret);
	ATEErr (*GetTextFramesIterator) ( StoryRef story, TextFramesIteratorRef* ret);
	ATEErr (*GetFrame) ( StoryRef story, ATETextDOM::Int32 frameIndex, TextFrameRef* ret);
	/// for auto or optical kerns
	ATEErr (*SetKernForSelection) ( StoryRef story, const TextRangeRef textRange, AutoKernType autoKernType);
	/// for manual kerns
	ATEErr (*SetKernAtChar) ( StoryRef story, ATETextDOM::Int32 charIndex, ATETextDOM::Int32 value);
	ATEErr (*GetKern) ( StoryRef story, const TextRangeRef textRange, AutoKernType* pAutoKernType, ATETextDOM::Int32* value);
	ATEErr (*GetModelKernAtChar) ( StoryRef story, ATETextDOM::Int32 charIndex, ATETextDOM::Int32* pManualKernValue, AutoKernType* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	/** Get a text range from start to end.
	This function might change start and end if they are invalid.
	i.e, if either has negative values or exceeding Story.GetSize().
	*/
	ATEErr (*GetTextRange) ( StoryRef story, ATETextDOM::Int32 start, ATETextDOM::Int32 end, TextRangeRef* ret);
	ATEErr (*IsEqual) ( StoryRef story, const StoryRef anotherStory, ATEBool8* ret);
	ATEErr (*Duplicate) ( StoryRef story, StoryRef* ret);
	/** Suspend reflow calculation.  This will speed up ITextRange::InsertXXX() call or any call that
	causes a reflow to happen.*/
	ATEErr (*SuspendReflow) ( StoryRef story);
	/** Resume reflow calculation.
	Make sure to match each SuspendReflow with ResumeReflow.  Or use IInhibitReflow instead of
	SuspendReflow() and ResumeReflow().
	*/
	ATEErr (*ResumeReflow) ( StoryRef story);

}StorySuite;

//////////////////////////////////////////////
//       --TabStopSuite--
//////////////////////////////////////////////
#define kTabStopSuite "ATE TabStop Suite"
#define kTabStopSuiteVersion1 1
#define kTabStopSuiteVersion kTabStopSuiteVersion1

typedef struct TabStopSuite{

	// Reference count maintenance.
	void (*AddRef) ( TabStopRef tabstop);
	void (*Release) ( TabStopRef tabstop);
	ATEBool8 (*IsNull) ( TabStopRef tabstop);

	ATEErr (*Initialize) ( TabStopRef* tabstop);
	// PROPERTIES
	// =======================================================================
	ATEErr (*GetTabType) ( TabStopRef tabstop, TabType* ret);
	ATEErr (*SetTabType) ( TabStopRef tabstop, TabType tabType);
	ATEErr (*GetPosition) ( TabStopRef tabstop, ATETextDOM::Float* ret);
	ATEErr (*SetPosition) ( TabStopRef tabstop, ATETextDOM::Float position);
	ATEErr (*HasLeader) ( TabStopRef tabstop, ATEBool8* ret);
	ATEErr (*GetLeader) ( TabStopRef tabstop, ATETextDOM::Unicode* leader, ATETextDOM::Int32 maxLength);
	ATEErr (*SetLeader) ( TabStopRef tabstop, ATETextDOM::Unicode* leader);
	ATEErr (*GetDecimalCharacter) ( TabStopRef tabstop, ATETextDOM::Unicode* ret);
	ATEErr (*SetDecimalCharacter) ( TabStopRef tabstop, ATETextDOM::Unicode decimalChar);

}TabStopSuite;

//////////////////////////////////////////////
//       --TabStopsSuite--
//////////////////////////////////////////////
#define kTabStopsSuite "ATE TabStops Suite"
#define kTabStopsSuiteVersion1 1
#define kTabStopsSuiteVersion kTabStopsSuiteVersion1

typedef struct TabStopsSuite{

	// Reference count maintenance.
	void (*AddRef) ( TabStopsRef tabstops);
	void (*Release) ( TabStopsRef tabstops);
	ATEBool8 (*IsNull) ( TabStopsRef tabstops);

	// TabStops is a container class that stores an array of TabStop
	// instances.  Often, a client will receive a TabStops object when
	// asking about the tab stops of a selected paragraph.  In other
	// cases, they will wish to create their own Set of TabStops to
	// apply to a paragraph.
	//
	// Creates empty container
	ATEErr (*Initialize) ( TabStopsRef* tabstops);
	// PROPERTIES
	// =======================================================================
	// Number of TabStop instances in container
	ATEErr (*GetSize) ( TabStopsRef tabstops, ATETextDOM::Int32* ret);
	// Returns first TabStop in container
	ATEErr (*GetFirst) ( TabStopsRef tabstops, TabStopRef* ret);
	// Returns last TabStop in container
	ATEErr (*GetLast) ( TabStopsRef tabstops, TabStopRef* ret);
	// METHODS
	// =======================================================================
	// Adds a TabStop or replaces an existing one in container.
	ATEErr (*ReplaceOrAdd) ( TabStopsRef tabstops, const TabStopRef pTabStop);
	// Requests TabStop by index.
	ATEErr (*Item) ( TabStopsRef tabstops, ATETextDOM::Int32 nIndex, TabStopRef* ret);
	// Removes TabStop by index.  No op if bad index passed in.
	ATEErr (*Remove) ( TabStopsRef tabstops, ATETextDOM::Int32 nIndex);
	// Empties container
	ATEErr (*RemoveAll) ( TabStopsRef tabstops);
	// PROTECTED AND PRIVATE METHODS
	// =======================================================================

}TabStopsSuite;

//////////////////////////////////////////////
//       --TabStopsIteratorSuite--
//////////////////////////////////////////////
#define kTabStopsIteratorSuite "ATE TabStopsIterator Suite"
#define kTabStopsIteratorSuiteVersion1 1
#define kTabStopsIteratorSuiteVersion kTabStopsIteratorSuiteVersion1

typedef struct TabStopsIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( TabStopsIteratorRef tabstopsiterator);
	void (*Release) ( TabStopsIteratorRef tabstopsiterator);
	ATEBool8 (*IsNull) ( TabStopsIteratorRef tabstopsiterator);

	ATEErr (*Initialize) ( TabStopsRef tabStops, Direction direction, TabStopsIteratorRef* tabstopsiterator);
	ATEErr (*IsDone) ( TabStopsIteratorRef tabstopsiterator, ATEBool8* ret);
	ATEErr (*IsNotDone) ( TabStopsIteratorRef tabstopsiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( TabStopsIteratorRef tabstopsiterator, ATEBool8* ret);
	ATEErr (*MoveToFirst) ( TabStopsIteratorRef tabstopsiterator);
	ATEErr (*MoveToLast) ( TabStopsIteratorRef tabstopsiterator);
	ATEErr (*Next) ( TabStopsIteratorRef tabstopsiterator);
	ATEErr (*Item) ( TabStopsIteratorRef tabstopsiterator, TabStopRef* ret);

}TabStopsIteratorSuite;

//////////////////////////////////////////////
//       --TextRangeSuite--
//////////////////////////////////////////////
#define kTextRangeSuite "ATE TextRange Suite"
#define kTextRangeSuiteVersion1 1
#define kTextRangeSuiteVersion kTextRangeSuiteVersion1

typedef struct TextRangeSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextRangeRef textrange);
	void (*Release) ( TextRangeRef textrange);
	ATEBool8 (*IsNull) ( TextRangeRef textrange);

	// PROPERTIES
	// ========================================================================
	ATEErr (*GetStart) ( TextRangeRef textrange, ATETextDOM::Int32* ret);
	ATEErr (*SetStart) ( TextRangeRef textrange, ATETextDOM::Int32 start);
	ATEErr (*GetEnd) ( TextRangeRef textrange, ATETextDOM::Int32* ret);
	ATEErr (*SetEnd) ( TextRangeRef textrange, ATETextDOM::Int32 end);
	ATEErr (*GetSize) ( TextRangeRef textrange, ATETextDOM::Int32* ret);
	// NAVIGATION OBJECTS
	// ========================================================================
	ATEErr (*GetStory) ( TextRangeRef textrange, StoryRef* ret);
	ATEErr (*GetTextSelection) ( TextRangeRef textrange, TextRangesRef* ret);
	ATEErr (*GetTextFramesIterator) ( TextRangeRef textrange, TextFramesIteratorRef* ret);
	ATEErr (*GetParagraphsIterator) ( TextRangeRef textrange, ParagraphsIteratorRef* ret);
	ATEErr (*GetWordsIterator) ( TextRangeRef textrange, WordsIteratorRef* ret);
	ATEErr (*GetTextRunsIterator) ( TextRangeRef textrange, TextRunsIteratorRef* ret);
	// ATTRIBUTE INSPECTION AND MODIFICATION
	// ========================================================================
	/// The returned inspector object consolidates the fully-defined
	/// set of attributes.  Arrays for each attribute store unique values.
	ATEErr (*GetCharInspector) ( TextRangeRef textrange, CharInspectorRef* ret);
	/// The returned inspector object consolidates the fully-defined
	/// set of attributes.  Arrays for each attribute store unique values.
	ATEErr (*GetParaInspector) ( TextRangeRef textrange, ParaInspectorRef* ret);
	/// Returns list of named styles used in the TextRange
	ATEErr (*GetNamedCharStyles) ( TextRangeRef textrange, CharStylesRef* ret);
	/// Returns list of named styles used in the TextRange
	ATEErr (*GetNamedParaStyles) ( TextRangeRef textrange, ParaStylesRef* ret);
	/// Set the named style referred to by pName in the TextRange.  Returns
	/// false if style not found.
	ATEErr (*SetNamedCharStyle) ( TextRangeRef textrange, const ATETextDOM::Unicode* pName, ATEBool8* ret);
	/// Set the named style referred to by pName in the TextRange.  Returns
	/// false if style not found.
	ATEErr (*SetNamedParaStyle) ( TextRangeRef textrange, const ATETextDOM::Unicode* pName, ATEBool8* ret);
	/// Collapses attributes of named style into local overrides.  Values in
	/// the local override trump those of the named style which trumps values
	/// in the parent (and so on)
	ATEErr (*ClearNamedCharStyle) ( TextRangeRef textrange);
	/// Collapses attributes of named style into local overrides.  Values in
	/// the local override trump those of the named style which trumps values
	/// in the parent (and so on)
	ATEErr (*ClearNamedParaStyle) ( TextRangeRef textrange);
	/// Unique char features refer to the common "flattened" (or fully-
	/// defined set of) attributes used in the TextRange.
	///
	/// Hence, GetUniqueCharFeatures returns CharFeatures
	/// objects that are the intersection of full attribute sets for each
	/// text run.  Only values that are the same across text runs are valid.
	ATEErr (*GetUniqueCharFeatures) ( TextRangeRef textrange, CharFeaturesRef* ret);
	/// Unique char features refer to the common "flattened" (or fully-
	/// defined set of) attributes used in the TextRange.
	///
	/// Hence, GetUniqueParaFeatures returns ParaFeatures
	/// objects that are the intersection of full attribute sets for each
	/// text run.  Only values that are the same across text runs are valid.
	ATEErr (*GetUniqueParaFeatures) ( TextRangeRef textrange, ParaFeaturesRef* ret);
	/// If true, then local overrides are present.  If false, then none exist.
	ATEErr (*HasLocalCharFeatures) ( TextRangeRef textrange, ATEBool8* ret);
	/// If true, then local overrides are present.  If false, then none exist.
	ATEErr (*HasLocalParaFeatures) ( TextRangeRef textrange, ATEBool8* ret);
	/// Unique local char features refer to the common local overrides,
	/// i.e. the overrides that are the same throughout all the text runs
	/// in the TextRange.
	///
	/// Hence, GetUniqueLocalCharFeatures returns CharFeatures
	/// objects that are the intersection of the local overrides.  Only values
	/// that are the same (unique) across all text runs are valid.
	///
	/// An empty CharFeatures (every attribute is "invalid") indicates
	/// either the text range has no local overrides or that no common
	/// attribute values existed for the local overrides.
	ATEErr (*GetUniqueLocalCharFeatures) ( TextRangeRef textrange, CharFeaturesRef* ret);
	/// Unique local char features refer to the common local overrides,
	/// i.e. the overrides that are the same throughout all the text runs
	/// in the TextRange.
	///
	/// Hence, GetUniqueLocalParaFeatures returns ParaFeatures
	/// objects that are the intersection of the local overrides.  Only values
	/// that are the same (unique) across all text runs are valid.
	///
	/// An empty ParaFeatures (every attribute is "invalid") indicates
	/// either the text range has no local overrides or that no common
	/// attribute values existed for the local overrides.
	ATEErr (*GetUniqueLocalParaFeatures) ( TextRangeRef textrange, ParaFeaturesRef* ret);
	/// Local overrides are specified via CharFeatures.  They typically
	/// trump (hence the name override) the attribute values defined by the
	/// text's associated named CharStyle (if one is attached) and the
	/// default normal style.  Clearing local overrides causes text to get its
	/// attributes from an associated named style (if any) or the normal style.
	///
	/// To completely replace the current set of overrides with a new set,
	/// use SetLocalCharFeatures( ).
	///
	/// To add additional overrides or to set existing overrides to different
	/// values, use ReplaceOrAddLocalCharFeatures( ).
	ATEErr (*SetLocalCharFeatures) ( TextRangeRef textrange, const CharFeaturesRef pFeatures);
	ATEErr (*ReplaceOrAddLocalCharFeatures) ( TextRangeRef textrange, const CharFeaturesRef pFeatures);
	ATEErr (*ClearLocalCharFeatures) ( TextRangeRef textrange);
	/// Local overrides are specified via ParaFeatures.  They typically
	/// trump (hence the name override) the attribute values defined by the
	/// text's associated named ParaStyle (if one is attached) and the
	/// default normal style.  Clearing local overrides causes text to get its
	/// attributes from an associated named style (if any) or the normal style.
	///
	/// To completely replace the current set of overrides with a new set,
	/// use SetLocalParaFeatures( ).
	///
	/// To add additional overrides or to set existing overrides to different
	/// values, use ReplaceOrAddLocalPara}Features( ).
	ATEErr (*SetLocalParaFeatures) ( TextRangeRef textrange, const ParaFeaturesRef pFeatures);
	ATEErr (*ReplaceOrAddLocalParaFeatures) ( TextRangeRef textrange, const ParaFeaturesRef pFeatures);
	ATEErr (*ClearLocalParaFeatures) ( TextRangeRef textrange);
	// METHODS
	// ========================================================================
	ATEErr (*SetStory) ( TextRangeRef textrange, const StoryRef story);
	ATEErr (*SetRange) ( TextRangeRef textrange, ATETextDOM::Int32 start, ATETextDOM::Int32 end);
	/// start and end of this range will change depending on direction
	/// if direction = CollapseEnd, then end = start
	/// if direction = CollapseStart, then start = end
	ATEErr (*Collapse) ( TextRangeRef textrange, CollapseDirection direction);
	/// Translate start and end by 'unit'.
	/// a Move(3), will make this range start+3, end+3, pending story limits.  i.e start and end will never be out of bounds.
	/// The return of this method will be equal to 'unit' unless it is out of bounds, in that case, return is zero.
	ATEErr (*Move) ( TextRangeRef textrange, ATETextDOM::Int32 unit, ATETextDOM::Int32* ret);
	/// This method will make a copy of this range.
	ATEErr (*Clone) ( TextRangeRef textrange, TextRangeRef* ret);
	/// Insert 'text' before the start of the range.
	ATEErr (*InsertBefore_AsUnicode) ( TextRangeRef textrange, const ATETextDOM::Unicode* text, ATETextDOM::Int32 length );
	/// Insert 'text' after the end of the range.
	ATEErr (*InsertAfter_AsUnicode) ( TextRangeRef textrange, const ATETextDOM::Unicode* text, ATETextDOM::Int32 length );
	/// Insert 'anotherRange' before the start of the range.
	ATEErr (*InsertBefore_AsTextRange) ( TextRangeRef textrange, const TextRangeRef anotherRange);
	/// Insert 'anotherRange' after the end of the range.
	ATEErr (*InsertAfter_AsTextRange) ( TextRangeRef textrange, const TextRangeRef anotherRange);
	/** Gets the contents of this range as unicode.
	Return value is number of characters.
	*/
	ATEErr (*GetContents_AsUnicode) ( TextRangeRef textrange, ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	/** Gets the contents of this range as platform codes.  Internally things are
	stored in unicode, so a conversion will happen data might get lost.
	Return value is number of characters.
	*/
	ATEErr (*GetContents_AsChar) ( TextRangeRef textrange, char* text, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetSingleGlyphInRange) ( TextRangeRef textrange, ATEGlyphID* pSingleGlyph, ATEBool8* ret);
	/// This method will select this range.
	/// if addToSelection is true, it will add this range to the current document selection.
	/// if addToSelection is false, it will clear the selection from the document and only select this range.
	ATEErr (*Select) ( TextRangeRef textrange, ATEBool8 addToSelection);
	/// This method will remove this range from the selection.
	/// Note, deselecting a range can cause defregmented selection, if this range is a sub range of the current selection.
	ATEErr (*DeSelect) ( TextRangeRef textrange);
	ATEErr (*ChangeCase) ( TextRangeRef textrange, CaseChangeType caseChangeType);
	ATEErr (*FitHeadlines) ( TextRangeRef textrange);
	/// This method will delete all the characters in that range.
	ATEErr (*Remove) ( TextRangeRef textrange);
	ATEErr (*IsEqual) ( TextRangeRef textrange, const TextRangeRef anotherRange, ATEBool8* ret);
	/// This Range has to be of size equal to 1, any other size will throw error (kBadParameter)
	ATEErr (*GetCharacterType) ( TextRangeRef textrange, ASCharType* ret);

}TextRangeSuite;

//////////////////////////////////////////////
//       --TextRangesSuite--
//////////////////////////////////////////////
#define kTextRangesSuite "ATE TextRanges Suite"
#define kTextRangesSuiteVersion1 1
#define kTextRangesSuiteVersion kTextRangesSuiteVersion1

typedef struct TextRangesSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextRangesRef textranges);
	void (*Release) ( TextRangesRef textranges);
	ATEBool8 (*IsNull) ( TextRangesRef textranges);

	ATEErr (*Initialize) ( TextRangesRef* textranges);
	// PROPERTIES
	// ======================================================================
	ATEErr (*GetSize) ( TextRangesRef textranges, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( TextRangesRef textranges, TextRangeRef* ret);
	ATEErr (*GetLast) ( TextRangesRef textranges, TextRangeRef* ret);
	// navigation objects.
	ATEErr (*GetTextSelection) ( TextRangesRef textranges, TextRangesRef* ret);
	ATEErr (*GetParagraphsIterator) ( TextRangesRef textranges, ParagraphsIteratorRef* ret);
	ATEErr (*GetWordsIterator) ( TextRangesRef textranges, WordsIteratorRef* ret);
	ATEErr (*GetTextRunsIterator) ( TextRangesRef textranges, TextRunsIteratorRef* ret);
	// ATTRIBUTE INSPECTION AND MODIFICATION
	// ========================================================================
	/// The returned inspector object consolidates the fully-defined
	/// set of attributes.  Arrays for each attribute store unique values.
	ATEErr (*GetCharInspector) ( TextRangesRef textranges, CharInspectorRef* ret);
	ATEErr (*GetParaInspector) ( TextRangesRef textranges, ParaInspectorRef* ret);
	/// Collapses attributes of named style into local overrides.  Values in
	/// the local override trump those of the named style which trumps values
	/// in the parent (and so on)
	ATEErr (*ClearNamedCharStyle) ( TextRangesRef textranges);
	ATEErr (*ClearNamedParaStyle) ( TextRangesRef textranges);
	/// Unique char features refer to the common "flattened" (or fully-
	/// defined set of) attributes used across each TextRange in the
	/// TextRanges object.
	///
	/// Hence, GetUnique{Char,Para}Features returns {Char,Para}Features
	/// objects that are the intersection of full attribute sets for each
	/// text run.  Only values that are the same across text runs are valid.
	ATEErr (*GetUniqueCharFeatures) ( TextRangesRef textranges, CharFeaturesRef* ret);
	ATEErr (*GetUniqueParaFeatures) ( TextRangesRef textranges, ParaFeaturesRef* ret);
	/// If true, then local overrides are present.  If false, then none exist.
	ATEErr (*HasLocalCharFeatures) ( TextRangesRef textranges, ATEBool8* ret);
	ATEErr (*HasLocalParaFeatures) ( TextRangesRef textranges, ATEBool8* ret);
	/// Unique local char features refer to the common local overrides,
	/// i.e. the overrides that are the same throughout each TextRange
	/// in the TextRanges object.
	///
	/// Hence, GetUniqueLocal{Char,Para}Features returns {Char,Para}Features
	/// objects that are the intersection of the local overrides.  Only values
	/// that are the same (unique) for all text runs are valid.
	///
	/// An empty {Char,Para}Features (every attribute is "invalid") indicates
	/// either no local overrides exist in any of the TextRange objects
	/// or that no common attribute values existed for the local overrides.
	ATEErr (*GetUniqueLocalCharFeatures) ( TextRangesRef textranges, CharFeaturesRef* ret);
	ATEErr (*GetUniqueLocalParaFeatures) ( TextRangesRef textranges, ParaFeaturesRef* ret);
	/// Local overrides are specified via {Char,Para}Features.  They typically
	/// trump (hence the name override) the attribute values defined by the
	/// text's associated named {Char,Para}Style (if one is attached) and the
	/// default normal style.  Clearing local overrides causes text to get its
	/// attributes from an associated named style (if any) or the normal style.
	///
	/// To completely replace the current set of overrides with a new set,
	/// use SetLocal{Char,Para}Features( ).
	///
	/// To add additional overrides or to set existing overrides to different
	/// values, use ReplaceOrAddLocal{Char,Para}Features( ).
	ATEErr (*SetLocalCharFeatures) ( TextRangesRef textranges, const CharFeaturesRef pFeatures);
	ATEErr (*ReplaceOrAddLocalCharFeatures) ( TextRangesRef textranges, const CharFeaturesRef pFeatures);
	ATEErr (*ClearLocalCharFeatures) ( TextRangesRef textranges);
	ATEErr (*SetLocalParaFeatures) ( TextRangesRef textranges, const ParaFeaturesRef pFeatures);
	ATEErr (*ReplaceOrAddLocalParaFeatures) ( TextRangesRef textranges, const ParaFeaturesRef pFeatures);
	ATEErr (*ClearLocalParaFeatures) ( TextRangesRef textranges);
	// METHODS
	// ======================================================================
	/// This method will select those ranges.
	/// if addToSelection is true, it will add those ranges to the current document selection.
	/// if addToSelection is false, it will clear the selection from the document and only select those ranges.
	ATEErr (*Select) ( TextRangesRef textranges, ATEBool8 addToSelection);
	/// This method will remove those ranges from the selection.
	/// Note, deselecting ranges can cause defregmented selection.
	ATEErr (*DeSelect) ( TextRangesRef textranges);
	ATEErr (*GetContents_AsUnicode) ( TextRangesRef textranges, ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*GetContents_AsChar) ( TextRangesRef textranges, char* text, ATETextDOM::Int32 maxLength, ATETextDOM::Int32* ret);
	ATEErr (*ChangeCase) ( TextRangesRef textranges, CaseChangeType caseChangeType);
	ATEErr (*Add) ( TextRangesRef textranges, const TextRangeRef textRange);
	ATEErr (*Item) ( TextRangesRef textranges, ATETextDOM::Int32 nIndex, TextRangeRef* ret);
	ATEErr (*RemoveAll) ( TextRangesRef textranges);
	ATEErr (*Remove) ( TextRangesRef textranges, ATETextDOM::Int32 nIndex);

}TextRangesSuite;

//////////////////////////////////////////////
//       --TextRangesIteratorSuite--
//////////////////////////////////////////////
#define kTextRangesIteratorSuite "ATE TextRangesIterator Suite"
#define kTextRangesIteratorSuiteVersion1 1
#define kTextRangesIteratorSuiteVersion kTextRangesIteratorSuiteVersion1

typedef struct TextRangesIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextRangesIteratorRef textrangesiterator);
	void (*Release) ( TextRangesIteratorRef textrangesiterator);
	ATEBool8 (*IsNull) ( TextRangesIteratorRef textrangesiterator);

	ATEErr (*Initialize) ( TextRangesRef textRanges, Direction direction, TextRangesIteratorRef* textrangesiterator);
	ATEErr (*Clone) ( TextRangesIteratorRef textrangesiterator, TextRangesIteratorRef* ret);
	ATEErr (*IsNotDone) ( TextRangesIteratorRef textrangesiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( TextRangesIteratorRef textrangesiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( TextRangesIteratorRef textrangesiterator, ATEBool8* ret);
	ATEErr (*MoveToFirst) ( TextRangesIteratorRef textrangesiterator);
	ATEErr (*MoveToLast) ( TextRangesIteratorRef textrangesiterator);
	ATEErr (*Next) ( TextRangesIteratorRef textrangesiterator);
	ATEErr (*Item) ( TextRangesIteratorRef textrangesiterator, TextRangeRef* ret);

}TextRangesIteratorSuite;

//////////////////////////////////////////////
//       --TextRunsIteratorSuite--
//////////////////////////////////////////////
#define kTextRunsIteratorSuite "ATE TextRunsIterator Suite"
#define kTextRunsIteratorSuiteVersion1 1
#define kTextRunsIteratorSuiteVersion kTextRunsIteratorSuiteVersion1

typedef struct TextRunsIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( TextRunsIteratorRef textrunsiterator);
	void (*Release) ( TextRunsIteratorRef textrunsiterator);
	ATEBool8 (*IsNull) ( TextRunsIteratorRef textrunsiterator);

	/// A TextRun is a range of text whose character attributes are the same.
	/// Insertions and deletions into a story can invalidate the entire iterator.
	ATEErr (*Initialize) ( const TextRangesRef ranges, Direction direction, TextRunsIteratorRef* textrunsiterator);
	ATEErr (*IsNotDone) ( TextRunsIteratorRef textrunsiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( TextRunsIteratorRef textrunsiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( TextRunsIteratorRef textrunsiterator, ATEBool8* ret);
	ATEErr (*MoveToFirst) ( TextRunsIteratorRef textrunsiterator);
	ATEErr (*MoveToLast) ( TextRunsIteratorRef textrunsiterator);
	/// The next run will be the one following (or preceding, depending on
	/// the iterator's direction) the run returned by Item( ).  Since Item( )
	/// is affected by attribute modifications to text, so is Next( ).
	ATEErr (*Next) ( TextRunsIteratorRef textrunsiterator);
	/// The range returned by Item( ) may differ from a preceding call if
	/// character attributes are modified in the story that the run is a
	/// part of.  For forward iteration, the new run will begin at or
	/// before the old run.  Similar for backwards iteration.
	ATEErr (*Item) ( TextRunsIteratorRef textrunsiterator, TextRangeRef* ret);

}TextRunsIteratorSuite;

//////////////////////////////////////////////
//       --WordsIteratorSuite--
//////////////////////////////////////////////
#define kWordsIteratorSuite "ATE WordsIterator Suite"
#define kWordsIteratorSuiteVersion1 1
#define kWordsIteratorSuiteVersion kWordsIteratorSuiteVersion1

typedef struct WordsIteratorSuite{

	// Reference count maintenance.
	void (*AddRef) ( WordsIteratorRef wordsiterator);
	void (*Release) ( WordsIteratorRef wordsiterator);
	ATEBool8 (*IsNull) ( WordsIteratorRef wordsiterator);

	ATEErr (*Initialize) ( const TextRangesRef ranges, Direction direction, WordsIteratorRef* wordsiterator);
	ATEErr (*IsNotDone) ( WordsIteratorRef wordsiterator, ATEBool8* ret);
	ATEErr (*IsDone) ( WordsIteratorRef wordsiterator, ATEBool8* ret);
	ATEErr (*IsEmpty) ( WordsIteratorRef wordsiterator, ATEBool8* ret);
	ATEErr (*MoveToFirst) ( WordsIteratorRef wordsiterator);
	ATEErr (*MoveToLast) ( WordsIteratorRef wordsiterator);
	ATEErr (*Next) ( WordsIteratorRef wordsiterator);
	// The next word corresponds to performing a control/command + arrow key
	// action from the UI.  Hence, each TextRange returned includes trailing
	// characters.  This also implies that (among other things) "..." is considered
	// a word.
	ATEErr (*Item) ( WordsIteratorRef wordsiterator, TextRangeRef* ret);
	// NOTE: Trailing information is always for the current word
	// returned by Item( ).  It always gives you the counts for
	// characters that come after (i.e. trailing) the word
	// (regardless of the direction of iteration)
	//
	// The total number of trailing characters is given by GetTrailingCount( )
	ATEErr (*GetTrailingSpaceCount) ( WordsIteratorRef wordsiterator, ATETextDOM::Int32* ret);
	ATEErr (*GetTrailingCount) ( WordsIteratorRef wordsiterator, ATETextDOM::Int32* ret);
	ATEErr (*GetTrailingTerminatingPunctuationCount) ( WordsIteratorRef wordsiterator, ATETextDOM::Int32* ret);

}WordsIteratorSuite;


//////////////////////////////////////////////
//       --ArrayLineSuite --
//////////////////////////////////////////////
#define kArrayLineSuite "ATE ArrayLine Suite"
#define kArrayLineSuiteVersion1 1
#define kArrayLineSuiteVersion kArrayLineSuiteVersion1

typedef struct ArrayLineSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayLineRef arraylineref);
	void (*Release) ( ArrayLineRef arraylineref);
	ATEBool8 (*IsNull) ( ArrayLineRef arraylineref);

	ATEErr (*GetSize) ( ArrayLineRef arraylineref, ATETextDOM::Int32* ret);
	ATEErr (*Item)    ( ArrayLineRef arraylineref, ATETextDOM::Int32 index, ATETextDOM::FloatPoint* retstart, ATETextDOM::FloatPoint* retend);
}ArrayLineSuite;

//////////////////////////////////////////////
//       --ArrayComposerEngineSuite--
//////////////////////////////////////////////
#define kArrayComposerEngineSuite "ATE ArrayComposerEngine Suite"
#define kArrayComposerEngineSuiteVersion1 1
#define kArrayComposerEngineSuiteVersion kArrayComposerEngineSuiteVersion1

typedef struct ArrayComposerEngineSuite{

	// Reference count maintenance.
	void (*AddRef) ( ArrayComposerEngineRef arraycomposerengine);
	void (*Release) ( ArrayComposerEngineRef arraycomposerengine);
	ATEBool8 (*IsNull) ( ArrayComposerEngineRef arraycomposerengine);

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	ATEErr (*GetSize) ( ArrayComposerEngineRef arraycomposerengine, ATETextDOM::Int32* ret);
	ATEErr (*GetFirst) ( ArrayComposerEngineRef arraycomposerengine, ComposerEngine* ret);
	ATEErr (*GetLast) ( ArrayComposerEngineRef arraycomposerengine, ComposerEngine* ret);
	// ========================================================================
	// METHODS
	// ========================================================================
	ATEErr (*Item) ( ArrayComposerEngineRef arraycomposerengine, ATETextDOM::Int32 index, ComposerEngine* ret);

}ArrayComposerEngineSuite;

#ifdef MAC_ENV
	#pragma options align=reset
#endif

#ifdef WIN_ENV
	#pragma pack(pop)
#endif

#ifdef __cplusplus
}// namespace ATE
}
#endif

#endif //__ATESuites__

