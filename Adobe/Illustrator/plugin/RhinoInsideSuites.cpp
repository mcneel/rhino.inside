#include "IllustratorSDK.h"
#include "RhinoInsideSuites.h"

extern "C"
{
	AIFilterSuite*				sAIFilter = nullptr;
	SPBlocksSuite*				sSPBlocks = nullptr;
	AIArtSuite*					sAIArt = nullptr;
	AIPathSuite*				sAIPath = nullptr;
	AIRealMathSuite*			sAIMath = nullptr;
	AIRandomSuite*				sAIRandom = nullptr;
	AIDocumentViewSuite*		sAIDocumentView = nullptr;
	AIToolSuite*				sAITool = nullptr;
	AIMatchingArtSuite*			sAIMatchingArt = nullptr;
	AIActionManagerSuite*		sAIActionManager = nullptr;
	AIMenuSuite*				sAIMenu = nullptr;
	AIUnicodeStringSuite*		sAIUnicodeString = nullptr;
	AIMdMemorySuite*			sAIMDMemory = nullptr;
	AIStringFormatUtilsSuite*	sAIStringFormatUtils = nullptr;
  AIAnnotatorSuite*			sAIAnnotator = nullptr;
  AIAnnotatorDrawerSuite*		sAIAnnotatorDrawer = nullptr;
  AIDocumentSuite*			sAIDocument = nullptr;
  AITimerSuite				*sAITimer = nullptr;
};

ImportSuite gImportSuites[] =
{
	kAIFilterSuite, kAIFilterVersion, &sAIFilter,
	kSPBlocksSuite, kSPBlocksSuiteVersion, &sSPBlocks,
	kAIArtSuite, kAIArtVersion, &sAIArt,
	kAIPathSuite, kAIPathVersion, &sAIPath,
	kAIRealMathSuite, kAIRealMathVersion, &sAIMath,
	kAIRandomSuite, kAIRandomVersion, &sAIRandom,
	kAIDocumentViewSuite, kAIDocumentViewVersion, &sAIDocumentView,
	kAIToolSuite, kAIToolVersion, &sAITool,
	kAIMatchingArtSuite, kAIMatchingArtVersion, &sAIMatchingArt,
	kAIActionManagerSuite, kAIActionManagerSuiteVersion, &sAIActionManager,
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, &sAIUnicodeString,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, &sAIMDMemory,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
  kAIAnnotatorSuite, kAIAnnotatorSuiteVersion, &sAIAnnotator,
  kAIAnnotatorDrawerSuite, kAIAnnotatorDrawerSuiteVersion, &sAIAnnotatorDrawer,
  kAIDocumentSuite, kAIDocumentSuiteVersion, &sAIDocument,
  kAITimerSuite, kAITimerSuiteVersion, &sAITimer,
  nullptr, 0, nullptr
};
