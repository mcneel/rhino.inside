/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 *
 * Copyright 2018 Adobe Systems Incorporated
 *
 * All Rights Reserved.
 *
 * NOTICE: Adobe permits you to use, modify, and distribute this file in
 * accordance with the terms of the Adobe license agreement accompanying
 * it. If you have received this file from a source other than Adobe,
 * then your use, modification, or distribution of it requires the prior
 * written permission of Adobe.
 *
 **************************************************************************/



#pragma once

/*******************************************************************************
 **
 **    Imports
 **
 **/

#include "AITypes.h"

#include "AIHeaderBegin.h"

/** @file AISelectionContextManager.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/
/*suite details*/
#define kAISelectionContextManagerSuite                  "AI Selection Context Manager Suite"
#define kAISelectionContextManagerSuiteVersion1          AIAPI_VERSION(1)
#define kAISelectionContextManagerSuiteVersion           kAISelectionContextManagerSuiteVersion1
#define kAISelectionContextManagerVersion                kAISelectionContextManagerSuiteVersion

/*top level document prop error*/
#define kNoTopLevelDocumentPropsError '!TLP'

/**
* This suite works only for the current selection. 
*/

/*******************************************************************************
* Below enum AISelectionLevelContext helps to find out context at different level.
*******************************************************************************/

enum  AISelectionLevelContext : ai::uint16
{
	/**
	* Default Value
	*/
    kAISelectionNoneContext = 0,
	
	/**
	* Context that is a direct child of a layer is termed as Below context.
	*/
    kAISelectionTopLevelContext  = 1<<0,
	
	/**
	* Any context present in the current selection, irrespective of parent or sibling.
	*/
    kAISelectionAnyLevelContext = 1<<1,
	
	/**
	* Context that is a direct child of a layer or a group is termed as an object-level context.
	*/
    kAISelectionObjectLevelContext = 1<<2,
	
	/**
	* Combined of Above Context.
	*/
    kAISelectionCompleteContext = kAISelectionTopLevelContext | kAISelectionAnyLevelContext | kAISelectionObjectLevelContext
};

/*******************************************************************************
* AISelectionCountDetailsFlag enum class provides context[Also Object Type] count.
* General Terminiology for keywords:
* TypeCount : Provides total different Type of context at different Level.
* TotalObjectCount: Total context count irrespective of type.
*******************************************************************************/ 

enum class AISelectionCountDetailsFlag : ai::uint16
{
	/**
	* Total count of different types of context present at top level.
	*/
    kTopLevelObjectTypeCount,
	
	/**
	* Total context count present at top level.
	*/
    kTopLevelTotalObjectCount,
	
	/**
	* Total count of different types of context present at object level.
	*/
    kObjectLevelObjectTypeCount,
	
	/**
	* Total count of context present at object level.
	*/
    kObjectLevelTotalObjectCount
};

using AISelectionContext = ai::SizeType;

/*******************************************************************************
* Below Enum class provides different flag of context.Below enum can be used for
* API IsSelectionContextFlagPresent.
* Use Multiple Flag If Looking for Multiple Context.
*******************************************************************************/
 
enum class AISelectionContextFlags : ai::uint16
{
    /**
	* To find if any art is present in the current selection.
	*/
    kAISelectionNone = 0,
    
    /**
	* To find if any art context is present in the current selection.
	*/
    kAISelectionHasPathArt,
    kAISelectionHasMultiplePaths,
    
    /**
	* To find if a path art (open/close) context is present in the current selection.
	*/
    kAISelectionHasOpenPathArt,
    kAISelectionHasClosePathArt,
    
    /**
	* To find if a Live Shape context is present in the current selection.
	*/
    kAISelectionHasLiveShapeArt,
    kAISelectionHasMultipleLiveShapeArt,
    
    /**
	* To find if a group context is present in the current selection.
	* Compound group or Clip group, or, layer or sub-layer can share the same context.
	*/
    kAISelectionHasGroupObject,
    kAISelectionHasMultipleGroupObject,
    
    /**
	* To find if a normal group context is present in the current selection.
	*/
    kAISelectionHasNormalGroup,
    kAISelectionHasMultipleNormalGroup,
    
    /**
	* To find if a compound path context is present in the current selection.
	*/
    kAISelectionHasCompoundGroup,
    kAISelectionHasMultipleCompoundGroup,
    
    /**
	* To find if a clip group context is present in the current selection.
	*/
    kAISelectionHasClipGroup,
    kAISelectionHasMultipleClipGroup,
    
    /**
	* To find if a normal group (not a layer or a sub-layer) is present in the current selection.
	*/
    kAISelectionHasNormalNonLayerGroup,
    kAISelectionHasMultipleNormalNonLayerGroup,
    
    /**
	* To find if an image art (embed or unembed) is present in the current selection.
	*/
    kAISelectionHasImageArt,
    kAISelectionHasMultipleImageArt,
    
    /**
	* To find if an embed image or an unembed art context is present in the current selection.
	*/
    kAISelectionHasEmbedImageArt,
    kAISelectionHasUnEmbedImageArt,
    kAISelectionHasMultipleUnEmbedImageArt,
    
    /**
	* To find if a text art context is present in the current selection.
	*/
    kAISelectionHasTextArt,
    kAISelectionHasMultipleTextArt,
    
    /**
	* To find if a symbol art context is present in the current selection.
	*/
    kAISelectionHasSymbol,
    kAISelectionHasMultipleSymbol,
    
    /**
	* To find if a symbol art context is present in the current selection.
	*/
    kAISelectionHasSymbolSet,
    kAISelectionHasMultipleSymbolSet,
    
    /**
	* To find if a Live Paint art context is present in the current selection.
	*/
    kAISelectionHasLivePaintGroup,
    kAISelectionHasMultipleLivePaintGroup,
    
    /**
	* To find if a shaper context is present in the current selection.
	*/
    kAISelectionHasShaperGroup,
    kAISelectionHasMultipleShaperGroup,
    
    /**
	* To find if a graph context is present in the current selection.
	*/
    kAISelectionHasGraphObjects,
    kAISelectionHasMultipleGraphObjects,
    
    /**
	* To find if a traced context is present in the current selection.
	*/
    kAISelectionHasTracedbject,
    kAISelectionHasMultipleTracedbject,
    
    /**
	* To find if an anchor point context is present in the current selection.
	*/
    kAISelectionHasAnchorPoint,
    kAISelectionHasMultipleAnchorPoint,
    
    /**
	* To find if a wrap envelope context is present in the current selection.
	*/
    kAISelectionHasWarpEnvelope,
    kAISelectionHasMultipleWarpEnvelope,
    
    /**
	* To find if a mesh envelope context is present in the current selection.
	*/
    kAISelectionHasMeshEnvelope,
    kAISelectionHasMultipleMeshEnvelope,
    
    /**
	* To find if a top envelope context is present in the current selection.
	*/
    kAISelectionHasTopEnvelope,
    kAISelectionHasMultipleTopEnvelope,
    
    /**
	* To find if an envelope context is present in the current selection.
	*/
    kAISelectionHasEnvelope,
    kAISelectionHasMultipleEnvelope,
    
    /**
	* To find if a blend context is present in the current selection.
	*/
    kAISelectionHasBlend,
    kAISelectionHasMultipleBlend,
    
    /**
	* To find if a mesh context is present in the current selection.
	*/
    kAISelectionHasMeshObject,
    kAISelectionHasMultipleMeshObject,
    
    /**
	* To find if a transformed symbol context is present in the current selection.
	*/
    kAISelectionHasTransformedSymbolInstance,
    kAISelectionHasGuides,
    
    
    /**
	* To find if the selected symbol has reset the transformation properties.
	*/
    kAISelectionResetSymbolTransformation,
    
    /**
	* To find if global editing can be applied on the current selection.
	*/
    kAISelectionCanEnableGlobalEditing
    
    /*all new context should be added at end*/
};

/*******************************************************************************
 **
 **    Suite
 **
 **/
 
 /** @ingroup Suites
	This suite provides functions to access current selection context information.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISelectionContextManagerSuite and \c #kAISelectionContextManagerVersion.
*/

struct AISelectionContextManagerSuite
{
    /**
	* The API below is used to find different context present at different levels.
	
		@param inFlag : Indicates context in which you are interested.
		@param queryLevelContext : You need to specify the level at which the context is expected.
		
			The function below returns true if the context is present, and returs false otherwise.
			
	* Example-1 :
	* To find if a text object is present in the current selection and not inside any group.
	
	* IsSelectionContextFlagPresent(AISelectionContextFlags::kAISelectionHasTextArt,AISelectionLevelContext::kAISelectionTopLevelContext);
	
	* Example-2 :
	* To find if any selected object includes a path.
	
	* IsSelectionContextFlagPresent(AISelectionContextFlags:: kAISelectionHasPathArt, AISelectionLevelContext::kAISelectionAnyLevelContext);
	*/
    AIAPI AIBoolean (*IsSelectionContextFlagPresent) (AISelectionContextFlags inFlag, AISelectionLevelContext  queryLevelContext);
    
	/**
	* The API below is used to find context count at different levels.
	
		@param inFlag :  indicates context in which user is intertested. 
		@param outCount [out] : outCount is the total context value, including contexts that represents objects, present in the current selection.
			return kNoErr in case of No Error.
	* Example-1:
	* To find how many different types of context are present in the current selection.
	
	* ai::SizeType outCount  = 0 ;
	* GetSelectionCountDetails (AISelectionCountDetailsFlag::kTopLevelObjectTypeCount, outCount )
	*/
    AIAPI AIErr (*GetSelectionCountDetails) (AISelectionCountDetailsFlag inFlag, ai::SizeType &outCount );
    
};
        
#include "AIHeaderEnd.h"

