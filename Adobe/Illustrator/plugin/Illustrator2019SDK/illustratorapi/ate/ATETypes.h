/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------
 
	$File: ATETypes.h $

	Author: 

	$Author: micheleg $

	$DateTime: 2006/01/02 16:27:31 $

	$Revision: #2 $

	$Change: 379550 $
	
	Notes:	
	
 ---------------------------------------------------------------------------------- */
#ifndef __ATETypes__
#define __ATETypes__

#ifdef __MWERKS__
	#if defined(__MC68K__) || defined(__POWERPC__)
		#pragma enumsalwaysint on
	#endif
#endif // __MWERKS__

// ----------------------------------------------------------------------------------

typedef unsigned short ASUTF16;

#ifdef __cplusplus

/** Defines bit operators for enum flags fields

    The type safety of bitflags can be strengthened by having an enum type
    specify the set of flags and be the data type for the flags field. This
    macro defines bit operators for such enums. 
    
    The macro is intended only for use with enum types. Compile errors
    will ensure against a client trying to pass in a class type or other
    C++ data type as the macro parameter.
*/

#define ATE_ENUM_BIT_OPERATORS(E)       \
    inline E operator| (E a, E b)       \
    {                                   \
        return E((int)a | (int)b);      \
    }                                   \
    inline E operator& (E a, E b)       \
    {                                   \
        return E((int)a & (int)b);      \
    }                                   \
    inline E operator^ (E a, E b)       \
    {                                   \
        return E((int)a ^ (int)b);      \
    }                                   \
    inline E operator~ (E a)            \
    {                                   \
        return E(~((int)a));            \
    }                                   \
    inline E& operator|= (E& a, E b)    \
    {                                   \
        return a = a | b;               \
    }                                   \
    inline E& operator&= (E& a, E b)    \
    {                                   \
        return a = a & b;               \
    }                                   \
    inline E& operator^= (E& a, E b)    \
    {                                   \
        return a = a ^ b;               \
    }

// ----------------------------------------------------------------------------------

namespace ATE
{
#endif

typedef int	ATEGlyphID;

typedef unsigned char ATEBool8;

// Some compilers complain of performance issues when converting
// between ATEBool8 (an integral value) and bool. These macros
// dodge these warnings but leave the code using them readable.
#define ATEBOOL8_IS_TRUE(value) (value) != 0
#define ATEBOOL8PTR_IS_TRUE(value) (value) ? *(value) != 0 : false

/** @ingroup Errors Adobe Text Engine (ATE) error codes. */
enum ATEErr {
	kNoError = 0,
	kBadParameter,
	kOutOfMemory,
	kOutOfRange,
	kNullPointer,
	kInternalError,
	kMissingSpellingDictionary,
	kMissingHyphenationDictionary
};
#ifndef __cplusplus
typedef enum ATEErr ATEErr;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) stream version constants */
enum StreamVersion
{
	kStreamVersion1 = 1,													// pre CS1 (ATE 1.0 )
	kStreamVersion2,														// CS1 - (ATE 2.0)
	kStreamVersion3,	kStreamLastNonPersistedVersion  = kStreamVersion3, 	// CS2 redux (shorter tag names) - (ATE V2.5)
						kStreamCS2Redux					= kStreamVersion3,
	kStreamVersion4,	kVerticalTextScaleChange		= kStreamVersion4,	// CS3 vertical text scale change (ATE 2.51)
	kStreamVersion5,	kComplexScriptSupport			= kStreamVersion5,	// CS4 complex script support (ATE 3.0)
	kStreamVersion6,														// CS5 (ATE 4.0)
	kStreamVersion7,														// CS6 hyperlink support (ATE 5.0)
	kStreamVersion8,														// CS7 (ATE 6.0)
	// ^^^^^^^^^^^^ Add new versions above this comment ^^^^^^^^^^^^ 
	// This allows us to have the current version always equal the last.
	kDontUseLastPlusOne,
	kStreamCurrentVersion = kDontUseLastPlusOne - 1
};
#ifndef __cplusplus
typedef enum StreamVersion StreamVersion;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) stream formatting constants */
enum StreamFormatting
{
	kEfficientPDFOutput,
	kPrettyPDFOutput,
	kBinaryPDFOutput
#if SLO_XML
	,kXMLUTF8Output
#endif
};
#ifndef __cplusplus
typedef enum StreamFormatting StreamFormatting;
#endif

// ----------------------------------------------------------------------------------

enum FeatureSet 
{
	kLatinCJKFeatureSet, 
	kMEFeatureSet,
	kIndicFeatureSet
};

#ifndef __cplusplus
typedef enum FeatureSet FeatureSet;
#endif

// ----------------------------------------------------------------------------------

enum FontLockingAllowance 
{
	kAllowFontLocking, 
	kDontAllowFontLocking,
	kUseFontLockDocumentSetting
};

#ifndef __cplusplus
typedef enum FontLockingAllowance FontLockingAllowance;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) line cap type constants */			
enum LineCapType {
	kButtCap = 0,
	kRoundCap = 1,
	kSquareCap = 2,
	kNumLineCapTypes
};
#ifndef __cplusplus
typedef enum LineCapType LineCapType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) character type constants */		
enum ASCharType {
	/** Space character */
	kASSpaceChar = 0,
	/** Punctuation character */
	kPunctuationChar,
	/** Paragraph end character CR */
	kParagraphEndChar,
	/** This character is anything but space, punctuation or paragraph end */
	kNormalChar
};
#ifndef __cplusplus
typedef enum ASCharType ASCharType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) line-join type constants */		
enum LineJoinType {
	/** A mitered join */
	kMiterJoin = 0,
	/** A round join */
	kRoundJoin = 1,
	/** A beveled join */
	kBevelJoin = 2,
	kNumLineJoinTypes
};
#ifndef __cplusplus
typedef enum LineJoinType LineJoinType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) paragraph justification type constants */		
enum ParagraphJustification
{
	kLeftJustify = 0,
	kRightJustify,
	kCenterJustify,

	kFullJustifyLastLineLeft,
	kFullJustifyLastLineRight,
	kFullJustifyLastLineCenter,

	kFullJustifyLastLineFull
};
#ifndef __cplusplus
typedef enum ParagraphJustification ParagraphJustification;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) composer engine type constants 

	kLatinCJKComposer:	Original ATE US composer supporting Latin and CJK 
	kOptycaComposer:		Optyca composer provided by WinSoft WRServices, supporting complex scripts 
						e.g. Hebrew, Arabic, Thai, Vietnames, Indic. 
						CJK is not supported by version 3.0 of WRServices
*/
enum ComposerEngine 
{ 
	kLatinCJKComposer = 0, 
	kOptycaComposer,
	kAdornment
};
#ifndef __cplusplus
typedef enum ComposerEngine ComposerEngine;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) paragraph direction type constants */	
enum ParagraphDirection
{
	kLeftToRight = 0,
	kRightToLeft
};
#ifndef __cplusplus
typedef enum ParagraphDirection ParagraphDirection;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) justification method type constants */	
enum JustificationMethod
{
	kJustifMethodDefault = 0,		//corresponds to kLatinLike in WR
	kJustifMethodArabic,			//corresponds to kEvenKashidasStretched in WR
	kJustifMethodNaskh,				//corresponds to kTraditionalNaskh in WR
	kJustifMethodNaskhTatweel,		//corresponds to kTraditionalNaskhTatweel in WR
	kJustifMethodNaskhKashida,		//corresponds to kTraditionalNaskhKashida in WR
	kJustifMethodNaskhTatweelFrac,  //corresponds to kTraditionalNaskhTatweelFrac in WR
	kJustifMethodNaskhKashidaFrac,  //corresponds to kTraditionalNaskhKashidaFrac in WR
	kJustifMethodAuto				//ATE shall decide justification method on the basis of 
									//Kashida Width. Following Logic would be used:
									//None		: kLatinLike,
									//Short		: kTraditionalNaskhKashidaFrac, 
									//Medium	: kTraditionalNaskhKashidaFrac,
									//Long		: kTraditionalNaskhKashidaFrac,
									//Stylistic	: kTraditionalNaskhKashida,
};
#ifndef __cplusplus
typedef enum JustificationMethod JustificationMethod;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) digit set type constants */	
enum DigitSet
{
	kDefaultDigits = 0,
	kArabicDigits,
	kHindiDigits,
	kFarsiDigits,
	kArabicDigitsRTL
};
#ifndef __cplusplus
typedef enum DigitSet DigitSet;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) direction override type constants */	
enum DirOverride
{ 
	kDirOverrideDefault = 0,
	kDirOverrideLTR,
	kDirOverrideRTL 
};
#ifndef __cplusplus
typedef enum DirOverride DirOverride;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) diacritic vertical position type constants */	
enum DiacVPos
{
	kDiacVPosOff = 0,
	kDiacVPosLoose,
	kDiacVPosMedium,
	kDiacVPosTight,
	kDiacVPosOpenType 
};
#ifndef __cplusplus
typedef enum DiacPosition DiacPosition;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) kashida type constants */	
enum Kashidas
{ 
	kKashidaDefault = 0,
	kKashidaOn = kKashidaDefault,
	kKashidaOff 
};

enum KashidaWidth
{ 
	kKashidaNone = 0,
	kKashidaSmall,
	kKashidaMedium,
	kKashidaLong,
	kKashidaStylistic
};

#ifndef __cplusplus
typedef enum Kashidas Kashidas;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Wari Chu justification type constants */
enum WariChuJustification
{
	kWariChuLeftJustify = 0,
	kWariChuRightJustify,
	kWariChuCenterJustify,

	kWariChuFullJustifyLastLineLeft,
	kWariChuFullJustifyLastLineRight,
	kWariChuFullJustifyLastLineCenter,

	kWariChuFullJustifyLastLineFull,

	kWariChuAutoJustify
};
#ifndef __cplusplus
typedef enum WariChuJustification WariChuJustification;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Kinsoku order constants */
enum PreferredKinsokuOrder
{
	kPushIn = 0,
	kPushOutFirst,
	kPushOutOnly
};
#ifndef __cplusplus
typedef enum PreferredKinsokuOrder PreferredKinsokuOrder;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Burasagari type constants */
enum BurasagariType
{
	kBurasagariNone = 0,
	kBurasagariStandard,
	kBurasagariStrong
};
#ifndef __cplusplus
typedef enum BurasagariType BurasagariType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) leading type constants */
enum LeadingType
{
	kRomanLeadingType = 0,
	kJapaneseLeadingType = 1
};
#ifndef __cplusplus
typedef enum LeadingType LeadingType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) tab type constants */
enum TabType
{
	kLeftTabType = 0,
	kCenterTabType,
	kRightTabType,
	kDecimalTabType
};
#ifndef __cplusplus
typedef enum TabType TabType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) kerning type constants */
enum AutoKernType { kNoAutoKern, kMetricKern, kOpticalKern, kMetricRomanOnlyKern };
#ifndef __cplusplus
typedef enum AutoKernType AutoKernType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Japanese alternate feature type constants */
enum JapaneseAlternateFeature
{
	kDefaultForm,
	kTraditionalForm,
	kExpertForm,
	kJIS78Form,
	kJIS83Form,
	kHalfWidthForm,
	kThirdWidthForm,
	kQuarterWidthForm,
	kFullWidthForm,
	kProportionalWidthForm,
	kJIS90Form,
	kJIS04Form
};
#ifndef __cplusplus
typedef enum JapaneseAlternateFeature JapaneseAlternateFeature;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) baseline direction constants */
enum BaselineDirection
{
	kNeverUseMustBeKnown = 0,				// we don't allow "unknown" like we used to
	kBaselineWithStream = 1,	// rotate roman glyphs to vertical orientation in vertical
	kBaselineVerticalRotated = 2,					// default baseline -- roman glyphs on side in vertical
	kBaselineVerticalCrossStream = 3				// Tate-Chu-Yoko in vertical
};
#ifndef __cplusplus
typedef enum BaselineDirection BaselineDirection;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) underline position constants */
enum UnderlinePosition
{
	kUnderlineOff,
	kUnderlineOn_RightInVertical,
	kUnderlineOn_LeftInVertical
};

#ifndef __cplusplus
typedef enum UnderlinePosition UnderlinePosition;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) underline style constants */
enum UnderlineStyle
{
	kUnderlineSolid,
	kUnderlineDashed
};

#ifndef __cplusplus
typedef enum UnderlineStyle UnderlineStyle;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) strike-through position constants */
enum StrikethroughPosition
{
	kStrikethroughOff,
	kStrikethroughOn_XHeight,
	kStrikethroughOn_EMBox
};

#ifndef __cplusplus
typedef enum StrikethroughPosition StrikethroughPosition;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) style-run alignment constants */
enum StyleRunAlignment
{
	kAlignStylesByBottom = 0,
	kAlignStylesByICFBottom = 1,
	
	kAlignStylesByRomanHorizontalCenterVertical = 2,
	
	kAlignStylesByCenterHorizontalRomanVertical = 3,
	
	kAlignStylesByICFTop = 4,
	kAlignStylesByTop = 5
};
#ifndef __cplusplus
typedef enum StyleRunAlignment StyleRunAlignment;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) character case change constants */
enum CaseChangeType
{
	kUppercase = 0,
	kLowercase,
	kTitleCase,
	kSentenceCase
};
#ifndef __cplusplus
typedef enum CaseChangeType CaseChangeType;
#endif

// ----------------------------------------------------------------------------------

struct SLOToOTLanguage
{
	const char* fScript;
	const char* fLanguage;
};

/** Adobe Text Engine (ATE) language constants */
// NEW LANGUAGES MUST BE ADDED AT THE END OF THE LIST
// otherwise make appropriate corrections to LinguisticSettings::GetIndex()
enum Language
{
	kEnglishLanguage,
	kFinnishLanguage,
	kStandardFrenchLanguage,
	kCanadianFrenchLanguage,
	kGerman1996ReformLanguage, 			// [1996-2006] Previously kStandardGermanLanguage.  See below for latest German.
	kOldGermanLanguage,					// As we moved from Proximity Hunspell the Old German language mapping changed to 1901 language.
	kOldSwissGermanLanguage, 			// Pre 2006 Reform.  Previously kSwissGermanLanguage.  See below for latest Swiss German.
	kItalianLanguage,
	kBokmalNorwegianLanguage,
	kNynorskNorwegianLanguage,
	kStandardPortugueseLanguage,
	kBrazillianPortugueseLanguage,
	kSpanishLanguage,
	kSwedishLanguage,
	kUKEnglishLanguage,
	kOldDutchLanguage,					// Pre 2006 Reform. Previously kDutchLanguage. See below for latest Dutch.
	kDanish,
	kCatalan,
	kRussian,
	kUkranian,
	kBulgarian,
	kSerbian,
	kCzech,
	kPolish,
	kRumanian,
	kGreek,
	kTurkish,
	kIcelandic,
	kHungarian,
	kChineseLanguage,
	kJapaneseLanguage,
	kCroatian,
	kHebrew,
	kSlovenian,
	kBelarussian,
	kAlbanian,
	kLithuanian,
	kLatvian,
	kSlovakian,
	kArabic,
	kEstonian,
	kFarsi,
	kGerman2006ReformLanguage,			// Latest German.  Should be the default as of 2006
	kDutch2005ReformLanguage,			// Latest Dutch.   Should be the default as of 2006
	kSwissGerman2006ReformLanguage,		// Latest Swiss German.   Should be the default as of 2006
	kCanadianEnglish,
	kThai,
	kVietnamese,
	kLao,
	kHindi,
	kMarathi,
	kBengaliIndia,
	kPunjabi,
	kGujarati,
	kOriya,
	kTamil,
	kTelugu,
	kKannada,
	kMalayalam,
	
	kBurmese,
	kSinhalese,
	kKhmer,
	kIndonesian,
	
	// Add all scripts supported by WRServices
	kNumberOfLanguages,
	kInvalidLanguage = 1000		// LILO need us to have an invalid language
};

//list of dictionary providers
enum DictionaryProvider
{
	kHunspellProvider,
	kWinSoftProvider,
	kWinSoftExtendedProvider,
	kUserDictionaryOnlyProvider,
	kProximityProvider,
	kMaxNumProviders,
	kInvalidProvider = 1000
};

//
// DictionaryServiceType defines the types of services that are available from the dictionary provider
//
typedef ASUTF16 DictionaryServiceType;
enum 
{
	kSpellingService,
	kHyphenationService,
	kInvalidService
};

#ifndef __cplusplus
typedef enum Language Language;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) synthetic font type constants */
enum SyntheticFontType
{
	kNoSynthetic = 0,
	kItalicSynthetic,
	kBoldSynthetic,
	kBoldItalicSynthetic
};
#ifndef __cplusplus
typedef enum SyntheticFontType SyntheticFontType;
#endif

/** Adobe Text Engine (ATE) figure style constants */
enum FigureStyle
{
	kDefaultFigureStyle = 0,
	kTabularLining,
	kProportionalOldStyle,
	kProportionalLining,
	kTabularOldStyle
};
#ifndef __cplusplus
typedef enum FigureStyle FigureStyle;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) font capitalization constants */
enum FontCapsOption
{
	kFontNormalCaps = 0,
	kFontSmallCaps,
	kFontAllCaps,
	kFontAllSmallCaps
};
#ifndef __cplusplus
typedef enum FontCapsOption FontCapsOption;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) baseline option constants */
enum FontBaselineOption
{
	kFontNormalBaseline = 0,
	kFontFauxedSuperScript,
	kFontFauxedSubScript
};

#ifndef __cplusplus
typedef enum FontBaselineOption FontBaselineOption;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) OpenType font position constants */
enum FontOpenTypePositionOption
{
	kFontOTNormalPosition,
	kFontOTSuperscriptPosition,
	kFontOTSubscriptPosition,
	kFontOTNumeratorPosition,
	kFontOTDenominatorPosition
};

#ifndef __cplusplus
typedef enum FontOpenTypePositionOption FontOpenTypePositionOption;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) memory management constants */
enum MakeEmptyMemoryHint
{
	kMakeEmptyAndFreeAllocations,
	kMakeEmptyAndPreserveAllocations
};

#ifndef __cplusplus
typedef enum MakeEmptyMemoryHint MakeEmptyMemoryHint;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) direction constants */
enum Direction { kForward = +1, kStationary = 0, kBackward = -1 };
#ifndef __cplusplus
typedef enum Direction Direction;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) flattening options */
enum FlattenWithParentStyles
{
	kDoNotFlattenWithParent = 0,
	kFlattenWithParent = 1
};
#ifndef __cplusplus
typedef enum FlattenWithParentStyles FlattenWithParentStyles;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) search options */
enum SearchScope
{
	kSearchEntireDocument = 0,
	kSearchStory = 1
};
#ifndef __cplusplus
typedef enum SearchScope SearchScope;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) collapse direction options */
enum CollapseDirection
{
	CollapseEnd,
	CollapseStart
};
#ifndef __cplusplus
typedef enum CollapseDirection CollapseDirection;
#endif


// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Moji Kumi constants */
enum
{
	kOpenParenthesis_MojiKumiCharacterClass = 1,
	kCloseParenthesis_MojiKumiCharacterClass = 2,
	kCantBeginLineCharacters_MojiKumiCharacterClass = 3,
	kBreakingPunctuation_MojiKumiCharacterClass = 4,
	kMiddlePunctuation_MojiKumiCharacterClass = 5,
	kPeriods_MojiKumiCharacterClass = 6,
	kComma_MojiKumiCharacterClass = 7,
	kIndivisibleCharacters_MojiKumiCharacterClass = 8,
	kPreAbbreviationSymbols_MojiKumiCharacterClass = 9,
	kPostAbbreviationSymbols_MojiKumiCharacterClass = 10,
	kJapaneseSpace_MojiKumiCharacterClass = 11,
	kHiragana_MojiKumiCharacterClass = 12,
	kDoubleByteNumber_MojiKumiCharacterClass = 13,
	kOtherJapaneseCharacters_MojiKumiCharacterClass = 14,
	kSingleByteNumber_MojiKumiCharacterClass = 15,
	kRomanNonSpaceCharacters_MojiKumiCharacterClass = 16,
	kTopOrEndOfLine_MojiKumiCharacterClass = 17,
	kTopOfParagraph_MojiKumiCharacterClass = 18
};

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) composite font class constants */
enum CompositeFontClassType
{
	kCompositeFontClassOverride = 0,

	// Following are predefined composite font class types
	kCompositeFontClassBase,					// Kanji class
	kCompositeFontClassKana,					// Full Width
	kCompositeFontClassPunctuation,
	kCompositeFontClassFWSymbolsAndAlphabetic,	// Full Width
	kCompositeFontClassHWSymbolsAndAlphabetic,	// Half Width
	kCompositeFontClassHWNumerals,				// Half Width
	kCompositeFontClassGaiji0,
	kCompositeFontClassGaiji1,
	kCompositeFontClassGaiji2,
	kCompositeFontClassGaiji3,
	kCompositeFontClassGaiji4,
	kCompositeFontClassGaiji5,
	kCompositeFontClassGaiji6,
	kCompositeFontClassGaiji7,
	kCompositeFontClassGaiji8,
	kCompositeFontClassGaiji9,
	kCompositeFontClassGaiji10,
	kCompositeFontClassGaiji11,

	kEndOfCompositeFontClassType
};
#ifndef __cplusplus
typedef enum CompositeFontClassType CompositeFontClassType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Moji Kumi code-class constants */
enum MojiKumiCodeClass
{
	kOpen = 1,
	kClose,
	kNoBegin,
	kEndPunctuation,
	kMiddlePunctuation,
	kPeriodPunctuation,
	kCommaPunctuation,
	kNotSeparatePunctuation,
	kSymbolsPrecedingNumbers,
	kSymbolsFollowingNumbers,
	kIdeographic,
	kHiragana,
	kDoubleByteNumbers,
	kOtherJapaneseCharacters,
	kSingleByteNumbers,
	kRomanNonSpace,
	kLineEdgeClass,
	kParagraphStartClass,

	kEndOfCodeClasses
};
#ifndef __cplusplus
typedef enum MojiKumiCodeClass MojiKumiCodeClass;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) class metric restrictions for a composite font component. */
enum ClassMetricRestriction
{
	// class metric restrictions for a composite font component.
	kClassMetricRestrictionNone = 0,
	kClassMetricRestrictionSize = 1 << 0,
	kClassMetricRestrictionBaseline =  1 << 1,
	kClassMetricRestrictionHorizontalScale =  1 << 2,
	kClassMetricRestrictionVerticalScale =  1 << 3,
	kClassMetricRestrictionCenterGlyph = 1 << 4
};
#ifndef __cplusplus
typedef enum ClassMetricRestriction ClassMetricRestriction;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) line orientation options */
enum LineOrientation
{
	kHorizontalLines = 0,
	/** Not supported by Illustrator */
	kVerticalLeftToRight = 1,	
	kVerticalRightToLeft = 2
};
#ifndef __cplusplus
typedef enum LineOrientation LineOrientation;
#endif


// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) glyph orientation constants */
enum GlyphOrientation
{
	/** Horizontal left to right. */
	kHorizontalGlyphs,				
	/** Standard vertical, straight from the font as vertical glyphs.	 */
	kVerticalGlyphs,			
	/** Horizontal glyphs rotated 90 degrees to be on side in vertical.	 */
	kHorizontalGlyphsRotated,
	/** Not used; we are no longer setting this constant but it may exist in files. */
	kVerticalUprightRomanGlyphs
};
#ifndef __cplusplus
typedef enum GlyphOrientation GlyphOrientation;
#endif

/** Adobe Text Engine (ATE) frame type constants */
enum FrameType
{
	kPointTextFrame = 0,
	kInPathTextFrame = 1,
	kOnPathTextFrame = 2
};
#ifndef __cplusplus
typedef enum FrameType FrameType;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) spell-checking result constants */
enum SpellCheckingResult
{
	kNoProblems = 0,
	kUnknownWord = 1,	
	kRepeatedWords = 2,
	kUncappedStartOfSentence = 3,
	kUncappedUnknownStartOfSentence = 4
};
#ifndef __cplusplus
typedef enum SpellCheckingResult SpellCheckingResult;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Kinsoku predefined tag constants */
enum KinsokuPredefinedTag
{
	kUserDefinedKinsokuTag = 0,
	kPredefinedHardKinsokuTag = 1,
	kPredefinedSoftKinsokuTag = 2
};
#ifndef __cplusplus
typedef enum KinsokuPredefinedTag KinsokuPredefinedTag;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) Moji Kumi predefined tag constants */
enum MojikumiTablePredefinedTag
{
	kUserDefinedMojikumiTableTag = 0,
	kPredefinedYakumonoHankakuMojikumiTableTag = 1,
	kPredefinedYakumonoZenkakuMojikumiTableTag = 2,
	kPredefinedGyomatsuYakumonoHankakuMojikumiTableTag = 3,
	kPredefinedGyomatsuYakumonoZenkakuMojikumiTableTag = 4
};
#ifndef __cplusplus
typedef enum MojikumiTablePredefinedTag MojikumiTablePredefinedTag;
#endif

// ----------------------------------------------------------------------------------

/** Adobe Text Engine (ATE) List Style predefined tag constants */
enum ListStylePredefinedTag
{
	kUserDefinedListStyleTag = 0,
	kPredefinedNumericListStyleTag = 1,
	kPredefinedUppercaseAlphaListStyleTag = 2,
	kPredefinedLowercaseAlphaListStyleTag = 3,
	kPredefinedUppercaseRomanNumListStyleTag = 4,
	kPredefinedLowercaseRomanNumListStyleTag = 5,
	kPredefinedBulletListStyleTag = 6
};

/** ATE Document policies regarding streaming data and predefined resources during Read/Write operation.

	This allows bitwise operation. For example, if one would like to write a document and omit both predefined data and 
	RenderedText, kOmitPredefinedData |kOmitRenderedText should be passed as a streaming policy to Document::Write.

	kAll:: stream in/out all data

	kOmitPredefinedData: do not stream out predefined data (only for Write operation)
		This significantly reduces the size of the written data. However, fidelity between versions may suffer
		if the omitted predefined data changes from version to version.
		
		Without specifying this flag, all predefined data will be streamed out; this provides maximum fidelity 
		but increases the file size.

	kOmitRenderedText: do not stream in/out RenderedText data 
		This reduces the size of the written data. Text will be recomposed and the view will be re-rendered 
		when streamed back in. This policy needs to be consistent across read and write.

		Without specifying this flag, all RenderedText data will be streamed out and the view will be maintained
		when streamed back in, until before the text is recomposed.

	kOmitMostDocumentSettings: do not stream in/out document settings like smart quote settings for every language.
		This reduces the size of the written data. However, if settings were changed by a user action, these changes
		will be rolled back to the default state. Use this option only if your application does not allow user changes
		to these settings.
		
*/

enum StreamingPolicy
{ 
	kAll						= 0,
	kOmitPredefinedData 		= 1 << 0,
	kOmitRenderedText 			= 1 << 1,
	kOmitMostDocumentSettings	= 1 << 2,
	kOmitDictionaryProviders	= 1 << 3
	/* WARNING: New policy value has to be a power of 2, to allow bitwise operation */
};

//This mask shall be used in MundoNotifier::SelectionOwnedItemChanged() call back function 
//to let the client know what has changed.
enum OwnedItemChangeIndicator
{
	/* WARNING: New OwnedItemChangeIndicator value has to be a power of 2, to allow bitwise operation */
	kNoneOwnedItem		= 0,
	kHyperlinkOwnedItem = 1 << 0,
	//In future Add other items here,update kAll accordingly.
	//kAllOwnedItems is bitwise OR of all the OwnedItemIndicator
	kAllOwnedItems		= kHyperlinkOwnedItem
};

#ifdef __cplusplus
ATE_ENUM_BIT_OPERATORS(StreamingPolicy)
#else
typedef enum StreamingPolicy StreamingPolicy;
#endif

// ----------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#ifdef __MWERKS__
	#if defined(__MC68K__) || defined(__POWERPC__)
		#pragma enumsalwaysint reset
	#endif
#endif // __MWERKS__

#endif //__ATETypes__
