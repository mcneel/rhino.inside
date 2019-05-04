/*************************************************************************
*
* ADOBE CONFIDENTIAL
*
* Copyright 2018 Adobe
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

#include "AITypes.h"
#include "AIPath.h"
#include "AIPathStyle.h"
#include "AIArtStyle.h"
#include "IAIAutoBuffer.h"
#include "IAILiteralString.h"

#include "AIHeaderBegin.h"

struct AIColorPoint
{
	AIFillStyle     fillStyle;
    AIBoolean       isFillPoint;
	AIRealPoint     position;
    AIReal          strength;
    AIReal          opacity;
};

struct AIColorSegment
{
	AIFillStyle     fillStyle;
	AIPathSegment	segment;
    AIReal          opacity;
};

struct AIColorCurve
{
	ai::AutoBuffer<AIColorSegment>	segments;
    AIBoolean						closed;
};

struct AISmoothShadingStyle
{
	ai::AutoBuffer<AIColorPoint>   colorPoints;
	
	ai::AutoBuffer<AIColorCurve>   colorCurves;

	/** A unique identifying name of the smooth style, not localized. Name should be in ASCII.*/
    ai::UnicodeString name;
    
    AISmoothShadingStyle() = default;
    AISmoothShadingStyle (AISmoothShadingStyle&&) = default; // Move constructor
    
    AISmoothShadingStyle (const AISmoothShadingStyle&) = default; //copy constructor
    
    AISmoothShadingStyle& operator= (const AISmoothShadingStyle& rhs)
    {
        if ( this != &rhs )
        {
            colorPoints = rhs.colorPoints;
            colorCurves = rhs.colorCurves;
            name = rhs.name;
        }
        return *this;
    }
};

typedef struct AISmoothShadingStyle* AISmoothShadingStylePtr;

/*******************************************************************************
**
** Constants
**
*******************************************************************************/

#define kAISmoothShadingStyleSuite				"AI Smooth Shading Style Suite"
#define kAISmoothShadingStyleSuiteVersion1		AIAPI_VERSION(1)
#define kAISmoothShadingStyleSuiteVersion       kAISmoothShadingStyleSuiteVersion1
#define kAISmoothShadingStyleVersion            kAISmoothShadingStyleSuiteVersion

/*******************************************************************************
**
**	Suite
**
********************************************************************************/
/** @ingroup Suites
This suite provides you functions which allow you to interact with the smooth style.
Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAISmoothShadingStyleSuite and \c #kAISmoothShadingStyleVersion.
*/


struct AISmoothShadingStyleSuite {

    /** Returns true if focus fill is SmoothShading else returns false
     @param inArtStyle: Input artsyle.
     **/
	AIAPI AIBoolean (*IsFocusSmoothShading) (AIArtStyleHandle inArtStyle);

	/** Determines if inArt has SmoothShading in focus
    Direct use of this api is more optimal than fetching the art style  of art and then calling IsFocusSmoothShading.
	 @param inArtStyle: Input artsyle.
     @param containsSmoothShading: is set to true if inArt has smoothshading in focus
     @param isVisible: is set to true if inArt has smoothshading and is visible
	**/
	AIAPI void(*ArtHasFocusSmoothShading) (AIArtHandle inArt, AIBoolean& containsSmoothShading, AIBoolean& isVisible);
    
    /** Returns true if focal fill in inArtStyle1 and focal fill in inArtStyle2 are same.
     @param inArtStyle1: Input art style 1.
     @param inArtStyle2: Input art style 2.
     **/
	AIAPI AIBoolean (*CompareFocusSmoothFill )(AIArtStyleHandle inArtStyle1, AIArtStyleHandle inArtStyle2);
    
    /** Returns true if both smooth shadings are same.
     @param inArtStyle1: Input smooth shading style 1.
     @param inArtStyle2: Input smooth shading style 2.
     **/
    AIAPI AIBoolean (*Compare) (const AISmoothShadingStyle& inSmoothShading1, const AISmoothShadingStyle& inSmoothShading2);

	/** Returns true if inArtStyle contains at least one SmoothShading field
	@param inArtStyle1: ArtStyle to search for.
	**/
	AIAPI AIBoolean (*ContainsSmoothShading) (AIArtStyleHandle inArtStyle);

	/** Returns true if style of inArt contains at least one SmoothShading field
	@param inArt: art to search for.
	If you want to check for an art, it more optimal to call this api rather than first getting the style and then calling ContainsSmoothShading over it.
	**/
	AIAPI AIBoolean (*ArtContainsSmoothShading) (AIArtHandle inArt);
    
    /** Retrieves focus SmoothShadingStyle information if art style has focus fill as smooth shading else returns false.
     @param artStyle The art style.
     @param outSmoothStyle [out] A buffer in which to return the SmoothShadingStyle style.
     */
    
    AIAPI AIBoolean (*GetFocusSmoothShadingStyle)(AIArtStyleHandle artStyle, AISmoothShadingStyle &outSmoothStyle);

};

#include "AIHeaderEnd.h"
