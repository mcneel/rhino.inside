#ifndef __ATETextCurrentStyle__
#define __ATETextCurrentStyle__

/*
 *        Name:	AIATECurrTextFeatures.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2002-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __ATESuites__
#include "ATESuites.h"
#endif

#ifndef __ATETypesDef__
#include "ATETypesDef.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIATECurrTextFeatures.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIATECurrentTextFeaturesSuite			"AI ATE Current Text Features Suite"
#define kAIATECurrentTextFeaturesSuiteVersion3	AIAPI_VERSION(3)
#define kAIATECurrentTextFeaturesSuiteVersion	kAIATECurrentTextFeaturesSuiteVersion3
#define kAIATECurrentTextFeaturesVersion		kAIATECurrentTextFeaturesSuiteVersion



/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	These functions allow you to access and manipulate the character and
	paragraph style attributes of text.
	\li The \e current styles are those that are applied to new text.
	\li The styles applied to currently selected text are the ones displayed
		in the Character and Paragraph palettes.

	You can define overrides for a character or paragraph style -- that is,
	a subset of features with override values.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIATECurrentTextFeaturesSuite and \c #kAIATECurrentTextFeaturesVersion.
 */
typedef struct {

	/** Retrieves the character attributes for the current text selection,
		in a flattened attribute chain,	as displayed in the Character Attribute palette.
			@param charFeatures [out] A buffer in which to return the character attributes.
		*/
	AIAPI AIErr (*GetCurrentCharFeature) ( ATE::CharFeaturesRef *charFeatures );

	/** Retrieves the paragraph attributes for the current text selection,
		in a flattened attribute chain,	as displayed in the Paragraph Attribute palette.
			@param paraFeatures [out] A buffer in which to return the paragraph attributes.
		*/
	AIAPI AIErr (*GetCurrentParaFeature) ( ATE::ParaFeaturesRef *paraFeatures );

	/** Sets the character attributes for the current text selection,
			@param charFeatures A flattened attribute chain, as displayed in the Character Attribute palette.
		*/
	AIAPI AIErr (*SetCurrentCharFeature) ( ATE::CharFeaturesRef charFeatures );

	/** Sets the paragraph attributes for the current text selection,
				@param paraFeatures A flattened attribute chain, as displayed in the Paragraph Attribute palette.
		*/
	AIAPI AIErr (*SetCurrentParaFeature) ( ATE::ParaFeaturesRef paraFeatures );

	/** Retrieves the named character style that are applied to new text objects.
		The default is the normal style in new documents.
			@param pStyle [out] A buffer in which to return the character style.
		*/
	AIAPI AIErr (*GetCurrentCharStyle) ( ATE::CharStyleRef* pStyle );

	/** Retrieves the named paragraph style that are applied to new text objects.
		The default is the normal style in new documents.
			@param pStyle [out] A buffer in which to return the paragraph style.
		*/
	AIAPI AIErr (*GetCurrentParaStyle) ( ATE::ParaStyleRef* pStyle );

	/** Sets the named character style to be applied to new text objects.
		If no text selection is present, overrides are cleared.
			@param pStyle The character style.
		*/
	AIAPI AIErr (*SetCurrentCharStyle) ( ATE::CharStyleRef pStyle );

	/** Sets the named paragraph style to be applied to new text objects.
		If no text selection is present, overrides are cleared.
			@param pStyle The paragraph style.
		*/
	AIAPI AIErr (*SetCurrentParaStyle) ( ATE::ParaStyleRef pStyle );

	/** Updates the UI to reflect any modifications you have made to
		the current text styles or features. */
	AIAPI AIErr (*Invalidate) ();

	/** Retrieves the current local character override attributes that are
		applied to new text objects.
			@param pFeatures [out] A buffer in which to return the character features
				containing override values.
		*/
	AIAPI AIErr (*GetCurrentCharOverrides) ( ATE::CharFeaturesRef *pFeatures );

	/** Retrieves the current local paragraph override attributes that are
		applied to new text objects.
			@param pFeatures [out] A buffer in which to return the paragraph features
				containing override values.
		*/
	AIAPI AIErr (*GetCurrentParaOverrides) ( ATE::ParaFeaturesRef *pFeatures );

	/** Sets the current local character override attributes that are
		applied to new text objects.
			@param pFeatures The character features with override values. If all attributes are
				unassigned, clears the current overrides.
		*/
	AIAPI AIErr (*SetCurrentCharOverrides) ( ATE::CharFeaturesRef pFeatures );

	/** Sets the current local paragraph override attributes that are
		applied to new text objects.
			@param pFeatures The paragraph features with override values. If all attributes are
				unassigned, clears the current overrides.
		*/
	AIAPI AIErr (*SetCurrentParaOverrides) ( ATE::ParaFeaturesRef pFeatures );

} AIATECurrentTextFeaturesSuite;


#include "AIHeaderEnd.h"


#endif
