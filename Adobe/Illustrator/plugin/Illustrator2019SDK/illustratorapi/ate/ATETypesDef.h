/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	ATETypesDef.h
		
	Notes:	Machine Generated file from script version 1.45
	        Please don't modify manually!
	
 ---------------------------------------------------------------------------------- */
#ifndef __ATETypesDef__
#define __ATETypesDef__

#ifndef SLO_COMPLEXSCRIPT
#define SLO_COMPLEXSCRIPT 1
#endif

#ifdef __cplusplus
namespace ATE
{
#endif

typedef struct _ApplicationPaint* ApplicationPaintRef;
typedef struct _CompFont* CompFontRef;
typedef struct _CompFontClass* CompFontClassRef;
typedef struct _CompFontClassSet* CompFontClassSetRef;
typedef struct _CompFontComponent* CompFontComponentRef;
typedef struct _CompFontSet* CompFontSetRef;
typedef struct _GlyphRun* GlyphRunRef;
typedef struct _GlyphRunsIterator* GlyphRunsIteratorRef;
typedef struct _MojiKumi* MojiKumiRef;
typedef struct _MojiKumiSet* MojiKumiSetRef;
typedef struct _TextFrame* TextFrameRef;
typedef struct _TextFramesIterator* TextFramesIteratorRef;
typedef struct _TextLine* TextLineRef;
typedef struct _TextLinesIterator* TextLinesIteratorRef;
typedef struct _TextResources* TextResourcesRef;
typedef struct _ApplicationTextResources* ApplicationTextResourcesRef;
typedef struct _DocumentTextResources* DocumentTextResourcesRef;
typedef struct _VersionInfo* VersionInfoRef;
typedef struct _ArrayApplicationPaintRef* ArrayApplicationPaintRefRef;
typedef struct _ArrayReal* ArrayRealRef;
typedef struct _ArrayBool* ArrayBoolRef;
typedef struct _ArrayInteger* ArrayIntegerRef;
typedef struct _ArrayLineCapType* ArrayLineCapTypeRef;
typedef struct _ArrayFigureStyle* ArrayFigureStyleRef;
typedef struct _ArrayLineJoinType* ArrayLineJoinTypeRef;
typedef struct _ArrayWariChuJustification* ArrayWariChuJustificationRef;
typedef struct _ArrayStyleRunAlignment* ArrayStyleRunAlignmentRef;
typedef struct _ArrayAutoKernType* ArrayAutoKernTypeRef;
typedef struct _ArrayBaselineDirection* ArrayBaselineDirectionRef;
typedef struct _ArrayLanguage* ArrayLanguageRef;
typedef struct _ArrayFontCapsOption* ArrayFontCapsOptionRef;
typedef struct _ArrayFontBaselineOption* ArrayFontBaselineOptionRef;
typedef struct _ArrayFontOpenTypePositionOption* ArrayFontOpenTypePositionOptionRef;
typedef struct _ArrayUnderlinePosition* ArrayUnderlinePositionRef;
typedef struct _ArrayStrikethroughPosition* ArrayStrikethroughPositionRef;
typedef struct _ArrayParagraphJustification* ArrayParagraphJustificationRef;
typedef struct _ArrayArrayReal* ArrayArrayRealRef;
typedef struct _ArrayBurasagariType* ArrayBurasagariTypeRef;
typedef struct _ArrayPreferredKinsokuOrder* ArrayPreferredKinsokuOrderRef;
typedef struct _ArrayKinsokuRef* ArrayKinsokuRefRef;
typedef struct _ArrayMojiKumiRef* ArrayMojiKumiRefRef;
typedef struct _ArrayMojiKumiSetRef* ArrayMojiKumiSetRefRef;
typedef struct _ArrayTabStopsRef* ArrayTabStopsRefRef;
typedef struct _ArrayLeadingType* ArrayLeadingTypeRef;
typedef struct _ArrayFontRef* ArrayFontRefRef;
typedef struct _ArrayGlyphID* ArrayGlyphIDRef;
typedef struct _ArrayRealPoint* ArrayRealPointRef;
typedef struct _ArrayRealMatrix* ArrayRealMatrixRef;
#if SLO_COMPLEXSCRIPT
typedef struct _ArrayParagraphDirection* ArrayParagraphDirectionRef;
typedef struct _ArrayJustificationMethod* ArrayJustificationMethodRef;
typedef struct _ArrayKashidaWidth* ArrayKashidaWidthRef;
typedef struct _ArrayKashidas* ArrayKashidasRef;
typedef struct _ArrayDirOverride* ArrayDirOverrideRef;
typedef struct _ArrayDigitSet* ArrayDigitSetRef;
typedef struct _ArrayDiacVPos* ArrayDiacVPosRef;
#endif
typedef struct _CharFeatures* CharFeaturesRef;
typedef struct _CharInspector* CharInspectorRef;
typedef struct _CharStyle* CharStyleRef;
typedef struct _CharStyles* CharStylesRef;
typedef struct _CharStylesIterator* CharStylesIteratorRef;
typedef struct _Find* FindRef;
typedef struct _Font* FontRef;
typedef struct _Glyph* GlyphRef;
typedef struct _Glyphs* GlyphsRef;
typedef struct _GlyphsIterator* GlyphsIteratorRef;
typedef struct _Kinsoku* KinsokuRef;
typedef struct _KinsokuSet* KinsokuSetRef;
typedef struct _ParaFeatures* ParaFeaturesRef;
typedef struct _Paragraph* ParagraphRef;
typedef struct _ParagraphsIterator* ParagraphsIteratorRef;
typedef struct _ParaInspector* ParaInspectorRef;
typedef struct _ParaStyle* ParaStyleRef;
typedef struct _ParaStyles* ParaStylesRef;
typedef struct _ParaStylesIterator* ParaStylesIteratorRef;
typedef struct _Spell* SpellRef;
typedef struct _Stories* StoriesRef;
typedef struct _Story* StoryRef;
typedef struct _TabStop* TabStopRef;
typedef struct _TabStops* TabStopsRef;
typedef struct _TabStopsIterator* TabStopsIteratorRef;
typedef struct _TextRange* TextRangeRef;
typedef struct _TextRanges* TextRangesRef;
typedef struct _TextRangesIterator* TextRangesIteratorRef;
typedef struct _TextRunsIterator* TextRunsIteratorRef;
typedef struct _WordsIterator* WordsIteratorRef;
typedef struct _ArrayLine* ArrayLineRef;
typedef struct _ArrayComposerEngine* ArrayComposerEngineRef;

#ifdef __cplusplus
}// namespace ATE
#endif

#endif

