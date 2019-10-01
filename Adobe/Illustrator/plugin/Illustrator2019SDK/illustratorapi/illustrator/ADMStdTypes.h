#ifndef __ADMStdTypes__
#define __ADMStdTypes__

#include "AIBasicTypes.h"

// ADMRect is the same size and layout as a Windows RECT.
/** Rectangle value in Windows (same as \c RECT) */
typedef struct _t_ADMRect {
	/** Coordinate values */
	ai::int32 left, top, right, bottom;
} ADMRect;

// ADMPoint is the same size and layout as a Windows POINT.
/** Point value in Windows (same as \c Point) */
typedef struct _t_ADMPoint  {
	/** Coordinate values */
	ai::int32 h, v;
} ADMPoint;

#ifdef WIN_ENV

// ADMBoolean is the same a Windows BOOL.
/** Boolean value in Windows (same as \c BOOL) */
typedef int ADMBoolean;

#endif

#ifdef MAC_ENV

// ADMBoolean is the same a Macintosh Boolean.
/** Boolean value in Mac OS (same as \c Boolean)*/
typedef unsigned char ADMBoolean;

#endif

// -----------------------------------------------------------------------------
//

/** Measurement units within dialogs. The unit can be displayed automatically
        after the value for items with numeric values.
                @see \c #ADMItemSuite9::ShowUnits(), \c #ADMItemSuite9::SetUnits(),
                 \c #ADMBasicSuite::ValueToString(), \c #ADMBasicSuite::StringToValue(),

        You can create up to 10 application unit preferences, using the constants
        \c #kADMAppUnits1 to \c #kADMAppUnits10. Use \c #ADMBasicSuite::SetAppUnits()
        to associate the numbered unit type with a normal unit type. Retrieve
        the associated unit type with \c #ADMBasicSuite::SetAppUnits().
        */
typedef enum
{

	// If you add new units, do not insert them into the list. Instead, add
	// them to the end of the "normal" units, and adjust kADMMaxNormalUnits.
	// (The actual values of these constants are used in STR# 4300, the
	// unit input strings, to associate units with input strings.)

/** Does not display units, even if show-units is on. */
	kADMNoUnits = 0,
	/** Document points (1/72 inch) */
	kADMPointUnits = 1,
	/** Inches */
	kADMInchUnits = 2,
	/** Millimeters */
	kADMMillimeterUnits = 3,
	/** Centimeters */
	kADMCentimeterUnits = 4,
	/** Picas */
	kADMPicaUnits = 5,
	/** Percentage values */
	kADMPercentUnits = 6,
	/** Degrees  */
	kADMDegreeUnits = 7,
	/** Kyu units (Japanese linear measure, 0.25 mm)  */
	kADMQUnits = 8,
	/** Base 16 values, usually shown and entered as 0xHH  (H = hexadecimal digit) */
	kADMBase16Units = 9,
	/** Pixels  */
	kADMPixelUnits = 10,
	/** Time units, generally \c hours:minutes:seconds:frames */
	kADMTimeUnits = 11,
	/** Ha units (Japanese linear measure, 0.25 mm)  */
	kADMHaUnits = 12,
	/** Feet */
	kADMFeetUnits = 13,
	/** Internal */
	kADMMinNormalUnits = kADMPointUnits,
	/** Internal */
	kADMMaxNormalUnits = kADMHaUnits,
	

        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits1 = 101,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits2 = 102,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits3 = 103,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits4 = 104,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits5 = 105,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits6 = 106,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits7 = 107,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits8 = 108,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits9 = 109,
        /** Developer-defined unit preference. See \c #ADMBasicSuite::SetAppUnits() */
        kADMAppUnits10 = 110,

        /** Internal */
        kADMMaxAppUnits = kADMAppUnits10,
        /** Internal */
        kADMDummyUnits = 0xFFFFFFFF

}
ADMUnits;

#ifndef __ADMRGBCOLOR_DEFINED
#define __ADMRGBCOLOR_DEFINED
// ADMRGBColor is the same as a Macintosh RGBColor on Macintosh and Windows.
/** RGB color record */
typedef struct _t_ADMRGBColor {
	/** Color values */
	unsigned short red, green, blue;
} ADMRGBColor;
#endif //__ADMRGBCOLOR_DEFINED


#ifndef __ADMCOLOR_DEFINED
#define __ADMCOLOR_DEFINED
// -----------------------------------------------------------------------------

/** Constant color values to be used for various dialog elements.
 The value of the constant specifies the actual RGB value,
 if the format is 0xRRGGBBFF. The lower 8 bits are always
 0xFF and can be ignored. The top 24 bits represent the
 amounts of red, green, and blue, where 0x00 is none, and
 0xFF is the maximum.
 \li Black = 0x000000FF,
 \li Red = 0xFF0000FF,
 \li Green = 0x00FF00FF,
 \li Blue = 0x0000FFFF,
 \li White = 0xFFFFFFFF
 
 Use these constants in a drawing procedure, to make your modified
 or custom dialog elements consistent with other application dialogs.
 See \c #ADMDrawerSuite6::SetADMColor().
 */
typedef enum
{
	/** Black */
	kADMBlackColor = 0,
	/** White */
	kADMWhiteColor,
	/** Color that indicates highlighted graphics in dialog. */
	kADMHiliteColor,
	/** Color that indicates highlighted text in dialog  */
	kADMHiliteTextColor,
	/** Color for the light part of shadowed objects. */
	kADMLightColor,
	/** Color for dialog background. */
	kADMBackgroundColor,
	/** Color for the shadowed part of shadowed objects. */
	kADMShadowColor,
	/** Color that indicates a disabled control.  */
	kADMDisabledColor,
	/** Color for an unpressed button. */
	kADMButtonUpColor,
	/** Color for a pressed button. */
	kADMButtonDownColor,
	/** Color for the shadowed part of a pressed button. */
	kADMButtonDownShadowColor,
	/**  Color for a tooltip background. */
	kADMToolTipBackgroundColor,
	/** Color for the text of a tooltip.*/
	kADMToolTipForegroundColor,
	/** Color for window interiors. */
	kADMWindowColor,
	/** Color for dialog foreground. */
	kADMForegroundColor,
	/** Color for dialog text. */
	kADMTextColor,
	/** Red. */
	kADMRedColor,
	/** Obsolete, do not use. */
	kADMTabBackgroundColor,
	/** Obsolete, do not use. */
	kADMActiveTabColor,
	/** Obsolete, do not use. */
	kADMInactiveTabColor,
	/** Indicates an unspecified color. */
	kADMDummyColor = 0x000000FE,	// Probably ought to be renamed to kADMUnspecifiedColor
	/** Internal */
	kActuallyRGBWhiteButSpecifiedToForceEnumTo32Bits = 0xFFFFFFFF
}
ADMColor;
#endif //__ADMCOLOR_DEFINED

#endif
