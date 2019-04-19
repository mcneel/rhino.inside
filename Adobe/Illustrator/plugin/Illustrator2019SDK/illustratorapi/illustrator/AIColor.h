#ifndef __AIColor__
#define __AIColor__

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


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIRealMath__
#include "AIRealMath.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIColor.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

/** Types of colors, patterns, and gradients,
	that can be used to fill or stroke Illustrator art objects.
	 */
typedef enum {
	/** Grayscale color. */
	kGrayColor = 0,
	/** Solid ink, expressed in four CMYK process colors. */
	kFourColor,
	/** Color with a pattern from the art's pattern list. */
	kPattern,
	/** Solid ink, expressed as a custom ink color. See \c #AICustomColorSuite.*/
	kCustomColor,
	/** Gradient, also called a blend. See \c #AIGradientSuite.*/
	kGradient,
	/** Solid color, expressed as three RGB values. */
	kThreeColor,
	/** Null color, If art is painted with \c kNoneColor, the
	 \c fillPaint or \c strokePaint of the \c #AIPathStyle must be false */
	kNoneColor,
    /**
     Advance color can not be represented in AIColor and need to used with parser.
     **/
    kAdvanceColor
} AIColorTag;

/** Defines a named custom color, whose appearance is
	defined by a color of one of these types. See \c #AICustomColorSuite. */
typedef enum {
	/** Solid ink, expressed in four process colors */
	kCustomFourColor = 0,
	/** Solid color, expressed as three RGB values. */
	kCustomThreeColor,
 	/** Lab color. Only valid for spot colors. */
	kCustomLabColor
} AICustomColorTag;

/** Types of gradients, or color blends. See \c #AIGradientStyle. */
enum {
	/** A linear gradient extends in a straight line for a given length at a
		given angle from an origin point. */
	kLinearGradient = 0,
	/** A radial gradient is circular, and extends for a given radius around a highlight point. */
	kRadialGradient
};

/** Option flags for properties of a named custom color.
	A logical OR of \c #kCustomSpotColor and \c #kCustomRegistrationColor. */
typedef short AICustomColorFlags;

/** A \c #AICustomColorFlags bit flag indicating that a custom color is
	a spot color rather than a global process color. */
#define	kCustomSpotColor			0x0001
/** A \c #AICustomColorFlags bit flag indicating that a custom color is
	a registration color. */
#define kCustomRegistrationColor	0x0002


/** @ingroup Errors
	Attempt to define a spot color with one of the reserved names
	Cyan, Magenta, Yellow, Black, None or All. */
#define kNameInvalidForSpotColorErr		'NA~.'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** A grayscale color. */
typedef struct {
	AIReal gray;
    void Init()
    {
        gray = 0;
    }
} AIGrayColorStyle;

/** The valid fields of a partial gray color. */
typedef struct {
	AIBoolean gray;
    void Init()
    {
        gray = false;
    }
} AIGrayColorStyleMap;


/** A CMYK color. */
typedef struct {
	AIReal cyan, magenta, yellow, black;
    void Init()
    {
        cyan = 0;
        magenta = 0;
        yellow = 0;
        black = 0;
    }
} AIFourColorStyle;

/** The valid fields of a partial CMYK color. */
typedef struct {
	AIBoolean cyan, magenta, yellow, black;
    void Init()
    {
        cyan = false;
        magenta = false;
        yellow = false;
        black = false;
    }
} AIFourColorStyleMap;


/** An RGB color. */
typedef struct {
	AIReal red, green, blue;
    void Init()
    {
        red = 0;
        green = 0;
        blue = 0;
    }
} AIThreeColorStyle;

/** The valid fields of a partial RGB color. */
typedef struct {
	AIBoolean red, green, blue;
    void Init()
    {
        red = false;
        green = false;
        blue = false;
    }
} AIThreeColorStyleMap;


/** A Lab color. */
typedef struct {
	AIReal l, a, b;
    void Init()
    {
        l = 0;
        a = 0;
        b = 0;
    }
} AILabColorStyle;

/** The valid fields of a partial Lab color. */
typedef struct {
	AIBoolean l, a, b;
    void Init()
    {
        l = false;
        a = false;
        b = false;
    }
} AILabColorStyleMap;


/** The union of all possible process colors that can be associated with
	a custom color. See \c #AICustomColorSuite. */
typedef union {
	/** A CMYK color */
	AIFourColorStyle	f;
	/** An RGB color */
	AIThreeColorStyle	rgb;
	/** A grayscale color */
	AIGrayColorStyle	gray;
	/** A Lab color */
	AILabColorStyle		lab;
} AICustomColorUnion;

/** A named custom color. A custom color can be a spot (actual ink)
	or a global process color. In either case, it has an associated
	process color. See \c #AICustomColorSuite. */
typedef struct {
	/** The type of the associated process color (CMYK or RGB) */
	AICustomColorTag	kind;
	/** The color values, in an appropriate structure. */
	AICustomColorUnion	c;
	/** Option flags for properties of the custom color.
		A logical OR of \c #kCustomSpotColor and \c #kCustomRegistrationColor.  */
	AICustomColorFlags	flag;

	void Init()
	{
		flag = 0;
		kind = kCustomFourColor;
	}
} AICustomColor;

/** Opaque reference to a custom color. See \c #AICustomColorSuite. */
typedef void *AICustomColorHandle;

/** An instance of a custom color paint. */
typedef struct {
	/** Reference to the custom color. See \c #AICustomColorSuite. */
	AICustomColorHandle color;
	/** Amount of the custom color to be applied. Value is in the range
		0 to 1 where ((1 - tint) * 100) is the percentage of ink to apply. */
	AIReal tint;
    
    void Init()
    {
        color = nullptr;
        tint = 0;
    }
} AICustomColorStyle;

/** The valid fields of a partial custom color paint. */
typedef struct {
    AIBoolean color;
	AIBoolean tint;
    void Init()
    {
        color = false;
        tint = false;
    }
} AICustomColorStyleMap;

/** Obsolete */
typedef struct {
	AIBoolean not_implemented;
} AIPattern;

/** Opaque reference to a pattern.See \c #AIPatternSuite. */
typedef void *AIPatternHandle;

/** The pattern style record defines a pattern instance, or an application of a
	pattern to an art object. The instance includes a reference to the pattern to
	use in the fill or stroke and information about how it is transformed, such
	as scale value.

	When a pattern is applied to an object, the pattern's defining art is tiled to
	paint that object. The pattern fill is tiled from the ruler origin rather
	than relative to the object. Before the tiling is done, the transformations
	in the \c AIPatternStyle record are applied to the pattern art.

*/
typedef struct {
	/** An opaque reference to the pattern object, accessed through the
		\c #AIPatternSuite, whose functions get and set a patterns name
		and defining art object or objects.
		 */
	AIPatternHandle pattern;
	/** Distance to translate the unscaled prototype before filling,
		measured from the ruler origin.*/
	AIReal shiftDist;
	/** Angle to translate the unscaled prototype before filling,
		in degrees. */
	AIReal shiftAngle;
	/** Fraction to scale the prototype before filling. */
    AIRealPoint scale;
	/** Angle to rotate the prototype before filling. */
	AIReal rotate;
	/** When true, the prototype is reflected before filling */
	AIBoolean reflect;
	/** Axis around which to reflect. */
	AIReal reflectAngle;
	/** Angle to slant the shear by. */
	AIReal shearAngle;
	/** Axis to shear with respect to. */
	AIReal shearAxis;
	/** Additional transformation arising from manipulating the path. */
	AIRealMatrix transform;
    
    void Init()
    {
        pattern = nullptr;
        shiftDist = 0;
        shiftAngle = 0;
        scale = {0, 0};
        rotate = 0;
        reflect = false;
        reflectAngle = 0;
        shearAngle = 0;
        shearAxis = 0;
		transform.Init();
    }
    
} AIPatternStyle;

/** The valid fields of a partial pattern style. */
typedef struct {
    AIBoolean pattern;
	AIBoolean shiftDist;
	AIBoolean shiftAngle;
	AIBoolean scale;
	AIBoolean rotate;
	AIBoolean reflect;
	AIBoolean reflectAngle;
	AIBoolean shearAngle;
	AIBoolean shearAxis;
	AIBoolean transform;
    void Init()
    {
        pattern = false;
        shiftDist = false;
        shiftAngle = false;
        scale = false;
        rotate = false;
        reflect = false;
        reflectAngle = false;
        shearAngle = false;
        shearAxis = false;
        transform = false;
    }
} AIPatternStyleMap;

 /** Opaque reference to a gradient color. See \c #AIGradientSuite. */
typedef void *AIGradientHandle;

/** The gradient style record defines a gradient instance (also called a blend).
	It includes a reference to a gradient definition, and the origin point
	and transformation matrix for the blend.

	A gradient has a name, and a gradient \e ramp, which describes where the
	color changes of the gradient occur. A gradient can be linear or
	radial. See the \c #AIGradientSuite. Radial blends have an additional
	attribute called a blend \e hilight, which is the starting point
	for the gradient ramp as it expands outward.
	*/
typedef struct {
	/** An opaque reference to the gradient. Access using functions in the
		\c #AIGradientSuite. It contains a \c name, \c type (linear or radial),
		and a ramp defined by a set of \e stops. */
	AIGradientHandle gradient;
	/** \li For a linear gradient, the origin of the gradient in page coordinates,
		which is 0 on the gradient ramp.
		\li For a radial gradient, the center of the containing circle.*/
	AIRealPoint gradientOrigin;
	/** \li For a linear gradient, the angle of the gradient in degrees from the X axis.
		The ramp extends from the origin at this angle. Positive values are counterclockwise.
		\li Not used for radial gradients, but the value is preserved in case
		the gradient is changed back to linear.*/
	AIReal gradientAngle;
	/** \li For a linear gradient, the distance in points over which the gradient ramp
		is applied. The ramp is scaled so that 100% of its value is this length.
		\li For a radial gradient, the radius of the containing circle. */
	AIReal gradientLength;
	/** The accumulated transformations of the gradient. It is not necessarily the same
		as the transformation matrix of the object containing the gradient.
		When a gradient is first applied to an object, the value is set to the
		identity matrix. When the user transforms the object, the user
		transformation matrix is concatenated to the gradient instances matrix. */
	AIRealMatrix matrix;
	/** \li For a radial gradient, the angle to the blend highlight point.
		\li Not used for linear gradients.  */
	AIReal hiliteAngle;
	/** \li For a radial gradient, the distance of the hilight from the origin
		expressed as a fraction of the radius, a value between 0 and 1.
		\li Not used for linear gradients. */
	AIReal hiliteLength;
	void Init()
	{
		gradient = NULL;
		gradientOrigin.h = kAIRealZero;
		gradientOrigin.v = kAIRealZero;
		gradientAngle = kAIRealZero;
		gradientLength = kAIRealZero;
		matrix.Init();
		hiliteAngle = kAIRealZero;
		hiliteLength = kAIRealZero;
	}
} AIGradientStyle;

/** The valid fields of a partial gradient style. */
typedef struct {
	AIBoolean gradient;
	AIBoolean gradientOrigin;
	AIBoolean gradientAngle;
	AIBoolean gradientLength;
	AIBoolean matrix;
	AIBoolean hiliteAngle;
	AIBoolean hiliteLength;
	void Init()
	{
		gradient = false;
		gradientOrigin = false;
		gradientAngle = false;
		gradientLength = false;
		matrix = false;
		hiliteAngle = false;
		hiliteLength = false;
	}
} AIGradientStyleMap;


/** The union of all possible types of color specification. */
typedef union {
	/** A grayscale color */
	AIGrayColorStyle g;
	/** A CMYK color */
	AIFourColorStyle f;
	/** An RGB color */
	AIThreeColorStyle rgb;
	/** A custom color */
	AICustomColorStyle c;
	/** A pattern */
	AIPatternStyle p;
	/** A gradient (blend) */
	AIGradientStyle b;
    
} AIColorUnion;

/** The valid fields of a partial color union. */
typedef union {
	/** A grayscale color */
	AIGrayColorStyleMap g;
	/** A CMYK color */
	AIFourColorStyleMap f;
	/** An RGB color */
	AIThreeColorStyleMap rgb;
	/** A custom color */
	AICustomColorStyleMap c;
	/** A pattern */
	AIPatternStyleMap p;
	/** A gradient (blend) */
	AIGradientStyleMap b;
    
} AIColorUnionMap;

/** A color specification, which describes a solid color, pattern, or gradient.
	A color can be partially specified, as when retrieving the common color attributes
	of a collection of objects or when modifying a specific subset of color attributes
	for one or more objects. When a color is partially specified an associated
	\c #AIColorMap contains boolean values indicating which fields are valid. */
typedef struct {
	/** The type of color being described. */
	AIColorTag kind;
	/** Contains the detailed specification of the color as appropriate for
		the \c kind. */
    AIColorUnion c;
    
    void Init()
    {
        kind = kNoneColor;
    }
} AIColor;

/** The valid fields of a partial color specification. For
	example, if \c kind is true, the associated \c AIColor has
	a valid value for \c kind. */
typedef struct {
	AIBoolean kind;
	AIColorUnionMap c;
	void Init()
	{
		kind = false;
	}
} AIColorMap;


/** Defines a gradient stop. Each stop is place where the color changes in a blend.
	A set of stops defines the gradient \e ramp.
	See \c #AIGradientStyle and \c #AIGradientSuite.
	*/
typedef struct {
	/** The location between two ramp points where there is an equal mix of this
		color and the color of the next stop. This value is a percentage of the
		distance between the two ramp points, between 13 and 87. The midpoint
		for the previous color stop is not considered. */
	AIReal midPoint;
	/** The position on the blend ramp where this color begins, in the range
		[0..100]. The first point does not have to be at 0, but the first
		color begins at 0. Similarly, the last does not have to be at 100. */
	AIReal rampPoint;
	/** The type and specification of the color for the gradient stop;
		a gray color, a process color, an RGB color, or a custom color. */
	AIColor color;
	/** The opacity value for the gradient stop, in the range [0,1],  
		0 for completely transparent and 1 for completely opaque.  */
	AIReal opacity;
	void Init()
	{
		midPoint = kAIRealZero;
		rampPoint = kAIRealZero;
		color.kind = kNoneColor;
		opacity = kAIRealZero;
	}
} AIGradientStop;


/** Result return type for \c #AIPathStyleSuite::ObjectUsesAIColor(). */
typedef unsigned short AIColorUsedHow;

/** Values for \c #AIColorUsedHow type, returned from
	\c #AIPathStyleSuite::ObjectUsesAIColor().  */
enum AIColorUsedHowValues {
	/** The target color is not used. */
	kAIColorNotUsed			= 0x0000,
	/** The stroke is painted, and is the target \c #AIColor */
	kAIColorUsedOnStroke	= 0x0001,
	/** The fill is painted, and is the target \c #AIColor */
	kAIColorUsedInFill		= 0x0002,
	/* The target \c #AIColor is used inside a gradient or pattern
		that is used in the object, or for graphs in a
		graph design or transform (which can be expressed or not
		in the graph art objects.) */
	kAIColorUsedIndirectly	= 0x0004
};

/** Callback function prototype used to iterate through colors, applying a modification
	and returning the modified color.
	This is used for situations where one component (such as a Color plug-in filter)
	knows how to modify colors, and another component knows how to apply them
	to a specify kind of object or other color collection such as a swatch book.
	See \c AIPluginGroup.h and \c AIPluginSelection.h
	This supersedes \c #AIMeshColorMap in \c AIMesh.h, which is deprecated.
		@param color [in, out] The color to modify and return.
		@param userData A pointer to data needed for the modification.
		@param result [out] A buffer in which to return an error if the iteration should stop.
			(This is a parameter rather than a return value, so that the communication can go both ways.
			If the component handling the objects wants the component making the color adjustments to stop
			processing other objects and report an error back to the user, it should set \c result to that
			error code BEFORE calling the callback function.)
		@param altered [out] A buffer in which to return true if the color was modified (and
			should therefore be applied to the objects or color collection).

		@see \c #AIPluginGroupSuite::PluginArtAdjustColors(), \c #AIPluginGroupAdjustColorsData
	*/
typedef void (*AIAdjustColorFunc) (AIColor *color, void *userData, AIErr *result, AIBoolean *altered);

/** Callback function prototype used to iterate through colors, applying a modification
	and returning the modified color. This version can also access and modify the
	overprint setting for fills and/or strokes.
		@param color [in, out] The color to modify and return.
		@param userData A pointer to data needed for the modification.
		@param result [out] A buffer in which to return an error if the iteration should stop.
			(This is a parameter rather than a return value, so that the communication can go both ways.
			If the component handling the objects wants the component making the color adjustments to stop
			processing other objects and report an error back to the user, it should set \c result to that
			error code BEFORE calling the callback function.)
		@param altered [out] A buffer in which to return true if the color or overprint was modified,
			(and should therefore be applied to the objects or color collection).
		@param usedWhere Whether to make overprint changes to fill or stroke.
			Either \c #kAIColorUsedInFill or \c #kAIColorUsedOnStroke. For any other
			value, overprint is ignored.
		@param overprint [out] A buffer in which to return true if overprint was modified,
			(and should therefore be applied to the objects or color collection).
	*/
typedef void (*AIAdjustColorsWithOPFunc) (AIColor *color, void *userData, AIErr *result, AIBoolean *altered,
												AIColorUsedHow usedWhere, AIBoolean *overprint );

/** Callback function prototype used to adjust or extract colors from pattern handles contained
	in the dictionary of an effect or plug-in group. The patterns are expected to be
	brush patterns, symbol patterns or graph designs; other fill patterns can be recolored
	with the \c #AIAdjustColorFunc() callback, passing a pattern \c #AIColor.

	Used in \c #AILiveEffectAdjustColorsMessage and \c #AIPluginGroupAdjustColorsData.
		@param oldPattern [in] The pattern to be examined. This object is not altered.
		@param newPattern [out] A buffer in which to return the pattern after color adjustment.
			If no colors are changed, contains the input pattern.
		@param userData A pointer to developer-defined data needed for the modification, acquired from the message data.
	*/
typedef AIErr (*AIAdjustPatternHandleFunc) ( AIPatternHandle oldPattern, AIPatternHandle *newPattern, void *userData );


/** Control options for \c #AIPathStyleSuite::AdjustObjectAIColors() */
typedef unsigned short VisitAIColorFlags;

/** Bit flags for \c #VisitAIColorFlags, options for \c #AIPathStyleSuite::AdjustObjectAIColors.
   Controls which colors are passed to the \c #AIAdjustColorFunc callback.
*/
enum VisitAIColorFlagValues {
	/** Turn all flags off. */
	kVisitColorsNullFlags = 0x0000,
	/** When on, iterate only colors used in selected objects
		(includes text selections and plug-in selections).<br>
		When on, implies that \c #kVisitColorsUniversally is off. */
	kVisitColorsSelectedOnly = 0x0001,

	/** When on, iterate all the palette content as well as the artwork, even if unused.
		If a color used inside a gradient or pattern is modified, the iterator modifies
		that gradient or pattern in place, rather than creating a new one with the modified
		color.<br>
		When off, skip color used only in the palette, such as unused symbols, brushes,
		gradients, and patterns. If a color used inside a gradient or pattern is modified,
		the iterator creates a new gradient or pattern using the modified color. <br>
		Ignored and considered off if \c #kVisitColorsSelectedOnly is on. */
	kVisitColorsUniversally = 0x0002,

	/** When on, do not iterate into definition of symbols, patterns, gradients, and brushes.
		Ignored and considered off if \c #kVisitColorsUniversally is on. */
	kVisitColorsDirectOnly = 0x0004,

	/** When on, pass only solid colors to the callback function.
		Interacts with \c #kVisitColorsDirectOnly:
		\li If both this and \c #kVisitColorsDirectOnly are on, pass solid colors that are used directly,
			but not those used in patterns and gradients.
		\li If this is on and \c #kVisitColorsDirectOnly is off, pass solid colors that are used directly,
			and those used by patterns and gradients.
		\li If this is off and \c #kVisitColorsDirectOnly is on, pass only directly-used gradients and patterns.
			The callback must handle any internal iteration, if needed.
		\li If both this and \c #kVisitColorsDirectOnly are off, before iterating a pattern or gradient,
			pass colors used inside that pattern or gradient. This ensures that any patterns or gradients
			modified or created by the iterator are also passed. See \c #kVisitColorsUniversally.
		*/
	kVisitColorsSolidOnly = 0x0008,

	/** When on, iterates colors used in fills, but not those used in strokes.  */
	kVisitColorsFillsOnly = 0x0010,

	/** When on, iterates colors used in strokes, but not those used in fills.  */
	kVisitColorsStrokesOnly = 0x0020,

	/** When on, the callback examines the iterated colors but does not modify them.
		Setting this allows the iterator to skip setup for Undo processing and so on, making
		it faster and less memory intensive. */
	kVisitColorsReadOnly = 0x0040,

	/** When on, iterates the result art of plug-in groups. (The result art is regenerated,
		so this is only useful for examination, not for modification.)    */
	kVisitColorsInResultArt = 0x0080,

	/** When on, if the selection includes multiple uses of the same global object,
		passes that object to the callback only once, and uses the resulting
		replacement object for all subsequent occurrences. <br>
		When off, passes each occurrence to the callback. Useful for statistical applications,
		or, for example, random color replacements, so that objects initially
		painted with the same color become different colors.
	  */
	kVisitGlobalObjectsOnceOnly = 0x0100,

	/** When on, the operation is occurring during a modal dialog's preview of interim settings.
		This allows the iterator and/or the callback function to skip processing that is only
		needed for ordinary final state edits, such as action recording, graph change recording,
		inserting new global objects into palettes, and so on. */
	kVisitColorsForModalPreview = 0x0200,

	/** When on, new global objects are always made anonymous and not inserted into panels, even
		if the original color is named and has a swatch. Also affects the behavior of symbol colorization.
		By default (even when kVisitColorsForModalPreview is on), recoloring symbol instances recolors
		the symbol definition, thus affecting all instances of the symbol, even those that are NOT in
		the visited art. When kVisitColorsForceAnonymous is on, a new anonymous symbol is created instead.
		Ignored and considered off if \c #kVisitColorsUniversally is on (since that flag causes
		colorization of all existing panel content instead of the input art.)
	*/
	kVisitColorsForceAnonymous = 0x0400,

	/** When on, the Registration color is not filtered out. (By default this color is not visited.) */
	kVisitColorsIncludeRegistration = 0x0800
};


/*******************************************************************************
 **
 ** Constants
 **
 *******************************************************************************/

#define kAIColorSuite				"AI Color Suite"
#define kAIColorSuiteVersion1       AIAPI_VERSION(1)
#define kAIColorSuiteVersion        kAIColorSuiteVersion1

/*******************************************************************************
 **
 **	Suite
 **
 ********************************************************************************/
/** @ingroup Suites
 Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
 \c #kAIColorSuite and \c #kAIColorSuiteVersion.
 */


struct AIColorSuite {
    
    /** returns true if colors are equal otherwise false.
     @param color1 : First AIColor
     
     @param color2 : Second AIColor.
     */
    AIAPI AIBoolean(*IsEqual) (const AIColor& color1, const AIColor &color2);
    
};

#include "AIHeaderEnd.h"

#endif
