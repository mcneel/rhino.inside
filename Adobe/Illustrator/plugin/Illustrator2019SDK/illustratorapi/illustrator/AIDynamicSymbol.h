/*************************************************************************
ADOBE SYSTEMS INCORPORATED
Copyright 2015 Adobe Systems Incorporated
All Rights Reserved.

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the
terms of the Adobe license agreement accompanying it.  If you have received this file from a
source other than Adobe, then your use, modification, or distribution of it requires the prior
written permission of Adobe.
**************************************************************************/

#ifndef _AI_DYNAMIC_SYMBOL_H_
#define _AI_DYNAMIC_SYMBOL_H_

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#include "AIHeaderBegin.h"

#define kAIDynamicSymbolSuite					"AI Dynamic Symbol Suite"
#define kAIDynamicSymbolSuiteVersion			AIAPI_VERSION(1)

/** Symbol type.*/
/**Symbol Type constants for symbols that mark whether a user has made the symbol	dynamic,
using the symbol dialog.  When a symbol has been marked as dynamic, users can
use the direct selection tool to override the appearance for specific instance.
@see  \c #AIDynamicSymbolSuite::GetSymbolType()
*/
enum AISymbolType
{
	/** Marks a static symbol, whose appearance is the same for all instances. */
	kAISymbolStaticType = 0x01,
	/** Marks a dynamic symbol, whose appearance can be overridden for specific instances. */
	kAISymbolDynamicType = 0x02
};

/*******************************************************************************
**
**	AIDynamicSymbol Suite
**
**/
struct AIDynamicSymbolSuite
{
	/** Retrieves the expanded art for the overridden appearance of a symbol, if the appearance has been overridden.
	@param symbolArt [in] The symbol art object reference.
	@param art [out] A buffer in which to return the overridden art, or NULL if the art is not overridden.
	@see \c #GetSymbolArtHasOverride()
	*/
	AIAPI AIErr(*GetSymbolOverriddenArt) (AIArtHandle inSymbolArt, AIArtHandle *outArt);

	/** Reports whether the appearance of a symbol instance has been overridden.
	@param SymbolArt [in]  The symbol art object reference.
	@param outHasOverridden [out] A boolean in which to return true if the art in the symbol instance has been overridden.
	*/
	AIAPI AIErr(*GetSymbolArtHasOverride)(AIArtHandle inSymbolArt, AIBoolean &outHasOverride);

	/*
	Retrieves the type of a symbol, static or dynamic. Only dynamic symbols can have an overridden appearance.
	@param symbolPattern [in] The symbol pattern reference.
	@param outSymbolType [out] A buffer in which to return the symbol type.
	*/
	AIAPI AIErr(*GetSymbolType) (const AIPatternHandle inSymbolArt, AISymbolType& outSymbolType);

};

#include "AIHeaderEnd.h"

#endif // _AI_DYNAMIC_SYMBOL_H_

