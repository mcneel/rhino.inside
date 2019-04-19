#include "IllustratorSDK.h"
#include "RhinoInsideSuites.h"
#include "AIAnnotatorDrawer.h"

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
  AIAnnotatorDrawerSuite*		sAIAnnotatorDrawer;
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
  kAIAnnotatorDrawerSuite, kAIAnnotatorDrawerSuiteVersion, &sAIAnnotatorDrawer,
  nullptr, 0, nullptr
};
