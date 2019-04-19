#ifndef _IAIPAINT_H_
#define _IAIPAINT_H_

/*
 *        Name:	IAIPaint.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	C++ wrapper class for AIColor.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include	"AIColor.h"
#include	"AIRealMath.h"

namespace ai {

/** This class describes how an art object is painted using
	a fully-defined paint. Use the \c PartialPaint class for
	partially-defined paints. */
class Paint : public AIColor {
public:
	/** Casts a color object to a \c Paint object. */
	static Paint& cast (AIColor& c);
	/** Casts a constant color object to a constant \c Paint object. */
	static const Paint& constcast (const AIColor& c);

	/** Constructor. Creates an empty paint object. */
	Paint ();

	/** Equality operator. */
	bool operator == (const AIColor& b) const;
};


//--------------------------------------------------------------------------------
// A partial paint describes a paint that may have some unknown values.
//--------------------------------------------------------------------------------

/** This class describes how an art object is painted using
	a partially-defined paint.  Use the \c Paint class for
	fully-defined paints. */
class PartialPaint {
public:
	/** Constructor. Creates an empty partial-paint object. */
	PartialPaint ();
	/** Constructor. Creates an initialized partial-paint object.
			@param color The partially-defined color object.
			@param colormap The color map object that describes which
				fields in the color object are valid.
		*/
	PartialPaint (const AIColor& color, const AIColorMap& colormap);

	/** Reports whether this partial-paint object is fully determined
			@return True if all color fields are defined, false otherwise.
		*/
	bool IsFullyDefined () const;

protected:
	Paint fPaint;
	AIColorMap fMap;
};


//--------------------------------------------------------------------------------
// Paint implementation
//--------------------------------------------------------------------------------

inline Paint& Paint::cast (AIColor& c)
{
	return static_cast<Paint&>(c);
}

inline const Paint& Paint::constcast (const AIColor& c)
{
	return static_cast<const Paint&>(c);
}

inline Paint::Paint ()
{
	kind = kNoneColor;
}

inline bool Paint::operator == (const AIColor& b) const
{

	bool result = false;

	if (kind == b.kind)
	{
		switch (kind)
		{
			case kGrayColor:
			{
				if (c.g.gray == b.c.g.gray)
				{
					result = true;
				}
				break;
			}
			case kFourColor:
			{
				if (c.f.cyan == b.c.f.cyan &&
					c.f.magenta == b.c.f.magenta &&
					c.f.yellow == b.c.f.yellow &&
					c.f.black == b.c.f.black)
				{
					result = true;
				}
				break;
			}
			case kPattern:
			{
				if (c.p.pattern == b.c.p.pattern &&
					c.p.shiftDist == b.c.p.shiftDist &&
					c.p.shiftAngle == b.c.p.shiftAngle &&
					c.p.scale.h == b.c.p.scale.h &&
					c.p.scale.v == b.c.p.scale.v &&
					c.p.rotate == b.c.p.rotate &&
					c.p.reflect == b.c.p.reflect &&
					c.p.reflectAngle == b.c.p.reflectAngle &&
					c.p.shearAngle == b.c.p.shearAngle &&
					c.p.shearAxis == b.c.p.shearAxis &&
					sAIRealMath->AIRealMatrixEqual((AIRealMatrix *)&c.p.transform, (AIRealMatrix *)&b.c.p.transform))
				{
					result = true;
				}
				break;
			}
			case kCustomColor:
			{
				if (c.c.color == b.c.c.color &&
					c.c.tint == b.c.c.tint)
				{
					result = true;
				}
				break;
			}
			case kGradient:
			{
				if (c.b.gradient == b.c.b.gradient &&
					c.b.gradientOrigin.h == b.c.b.gradientOrigin.h &&
					c.b.gradientOrigin.v == b.c.b.gradientOrigin.v &&
					c.b.gradientAngle == b.c.b.gradientAngle &&
					c.b.gradientLength == b.c.b.gradientLength &&
					sAIRealMath->AIRealMatrixEqual((AIRealMatrix *)&c.b.matrix, (AIRealMatrix *)&b.c.b.matrix) &&
					c.b.hiliteAngle == b.c.b.hiliteAngle &&
					c.b.hiliteLength == b.c.b.hiliteLength)
				{
					result = true;
				}
				break;
			}
			case kThreeColor:
			{
				if (c.rgb.red == b.c.rgb.red &&
					c.rgb.green == b.c.rgb.green &&
					c.rgb.blue == b.c.rgb.blue)
				{
					result = true;
				}
				break;
			}
		}
	}

	return result;
}


//--------------------------------------------------------------------------------
// PartialPaint implementation
//--------------------------------------------------------------------------------

inline PartialPaint::PartialPaint () :
	fPaint()
{
	fMap.kind = false;
}

inline PartialPaint::PartialPaint (const AIColor& color, const AIColorMap& colormap) :
	fPaint(static_cast<const Paint&>(color)), fMap(colormap)
{
}

inline bool PartialPaint::IsFullyDefined () const
{
	bool result = false;

	if (fMap.kind)
	{
		switch (fPaint.kind)
		{
			case kGrayColor:
				result = fMap.c.g.gray != 0;
				break;

			case kThreeColor:
				result = fMap.c.rgb.red &&
						fMap.c.rgb.green &&
						fMap.c.rgb.blue;
				break;

			case kFourColor:
				result = fMap.c.f.cyan &&
						fMap.c.f.magenta &&
						fMap.c.f.yellow &&
						fMap.c.f.black;
				break;

			case kCustomColor:
				result = fMap.c.c.color &&
						fMap.c.c.tint;
				break;

			case kPattern:
				result = fMap.c.p.pattern &&
						fMap.c.p.shiftDist &&
						fMap.c.p.shiftAngle &&
						fMap.c.p.scale &&
						fMap.c.p.rotate &&
						fMap.c.p.reflect &&
						fMap.c.p.reflectAngle &&
						fMap.c.p.shearAngle &&
						fMap.c.p.shearAxis &&
						fMap.c.p.transform;
				break;

			case kGradient:
				result = fMap.c.b.gradient &&
						fMap.c.b.gradientOrigin &&
						fMap.c.b.gradientAngle &&
						fMap.c.b.gradientLength &&
						fMap.c.b.matrix &&
						fMap.c.b.hiliteAngle &&
						fMap.c.b.hiliteLength;
				break;
		}
	}

	return result;
}

// end of namespace ai
}


#endif
