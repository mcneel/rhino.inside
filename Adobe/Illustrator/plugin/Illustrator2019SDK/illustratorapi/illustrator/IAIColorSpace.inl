/*
 *        Name:	IAIColorSpace.inl
 *   $Revision: 1 $
 *      Author:	Simon Chen 
 *        Date:	   
 *     Purpose:	Common impl file for the core and plug-ins.
 *		This file is included by IAIColorSpace.cpp & IAIColorSpaceCore.cpp
 *		Code added here MUST be shareable between the core and plug-ins.
 *			* You may not throw specific errors from these methods (ai::Error vs. CAIFault). But this
 *			  does not mean that the methods won't throw. In fact, the methods that they call might 
 *			  throw.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#ifndef _IAICOLORSPACE_INL_
#define _IAICOLORSPACE_INL_

bool ai::ColorSpace::operator!=(const ai::ColorSpace &rhs) const
{
	return !(*this == rhs);
}

int ai::ColorSpace::NumProcessComponents(void) const
{
	return NumColorComponents() - NumSpotComponents();
}

const ai::uint8* ai::ColorSpace::IndexedColors(ai::uint8 index) const
{
	const ai::uint8 *comps = NULL;
	if (IndexedNumEntries() > 0 && index < IndexedNumEntries())
	{
		comps = IndexedTable() + index*IndexedNumComponents();

		if (BaseColorSpace().GetFamily() == ai::ColorSpace::kAIColorSpaceFamilyRGB &&
			IndexedNumComponents() == 4)
		{
			comps ++;	// skip the zero channel in 0RGB color table
		}
	}

	return comps;
}

#endif //_IAICOLORSPACE_INL_