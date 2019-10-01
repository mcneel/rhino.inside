/*
* Name: AIAutoCoordinateSystem.h
* Author: Started by Pushp
* Date: January, 2009
* Purpose: Adobe Illustrator AutoCoordinateSystem Auto object
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2008 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/
#pragma once

#ifndef _AIAutoCoordinateSystem_H_
#define _AIAutoCoordinateSystem_H_

#include "AIHardSoft.h"

#ifdef _AI_AUTO_COORDINATE_SYSTEM_INCLUDE_H_
#include _AI_AUTO_COORDINATE_SYSTEM_INCLUDE_H_
#elif  AI_AUTO_SUITE_AVAILABLE
#include "AutoSuite.h"
extern_declare_suite(AIHardSoft);
#else
#ifndef _AI_AUTO_COORDINATE_SYSTEM_USE_C_LINKAGE_
#define _AI_AUTO_COORDINATE_SYSTEM_USE_C_LINKAGE_ 1
#endif
#if _AI_AUTO_COORDINATE_SYSTEM_USE_C_LINKAGE_
extern "C"
{
#endif
	/** A plug-in using the \c #ai::AutoCoordinateSystem class is required to provide
	these global suite pointers.  These pointers must be valid prior
	to any call to \c #ai::AutoCoordinateSystem methods.
	*/
	extern AIHardSoftSuite* sAIHardSoft;

#if _AI_AUTO_COORDINATE_SYSTEM_USE_C_LINKAGE_
}
#endif // _AI_AUTO_COORDINATE_SYSTEM_USE_C_LINKAGE_

#endif

namespace ai
{
	/** A stack object used to change the coordinate system
	to be used by Illustrator API functions. The coordinate
	system remains in use until the destruction of this object.
	@see \c #kAIHardSoftSuite
	*/

	class AutoCoordinateSystem
	{
	public:
		/**
		Changes the coordinate system to be used by Illustrator API functions.
		The coordinate system remains in use until the destruction of this object,
		at which time the previous system is restored.
		@see \c #kAIHardSoftSuite

		@param coordinateSystem [in] The new coordinate system constant, an \c #AICoordinateSystem value.

		*/
		AutoCoordinateSystem(AICoordinateSystem coordinateSystem= kAICurrentCoordinateSystem)
		{
			sAIHardSoft->GetCoordinateSystem(fCoordinateSystem);
			sAIHardSoft->SetCoordinateSystem(coordinateSystem);
		}
		/**
		Destructor. Resets the coordinate system used by Illustrator API functions
		to the one that was saved when this object was created.
		*/
		~AutoCoordinateSystem()
		{
			sAIHardSoft->SetCoordinateSystem(fCoordinateSystem);
		}
	private:
		ai::int32 fCoordinateSystem;
	};
}

#endif