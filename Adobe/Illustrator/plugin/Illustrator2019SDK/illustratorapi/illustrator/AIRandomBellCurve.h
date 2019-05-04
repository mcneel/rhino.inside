#ifndef __AIRandomBellCurve__
#define __AIRandomBellCurve__

/*
 *        Name:	AIRandomBellCurve.h
 *   $Revision: 4 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Random Number Bell Curve Suite.
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


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIRandomBellCurve.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIRandomBellCurveSuite		"AI Random Bell Curve Suite"
#define kAIRandomBellCurveSuiteVersion	AIAPI_VERSION(4)
#define kAIRandomBellCurveVersion		kAIRandomBellCurveSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Together with the \c #AIRandomSuite, allows you to add a degree of randomness,
	or "noise" to an effect. This suite provides numbers distributed along a
	standard probability curve (as opposed to an even distribution of random numbers).

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIRandomBellCurveSuite and \c #kAIRandomBellCurveVersion.
*/
typedef struct {

	/** Gets a random number with normal probability distribution centered on
		zero and with a standard deviation of one.
		<br>(Note that this function returns a numeric value, not an error code.)

		The value returned is in the range -1 to +1 about
		70% of the time (see table below) and the distribution of values in this
		range is close to linear. The probability of a value occurring outside this
		range drops off quickly the farther you get from the origin.

		<TABLE>
			<TR><TD>Output Range</TD>		<TD>% result in this range</TD>
			<TR><TD>-0.5 to +0.5</TD>		<TD> about 40%</TD>
			<TR><TD>-1.0 to +1.0</TD>		<TD> about 70%</TD>
			<TR><TD>-1.5 to +1.5</TD>		<TD> about 86%</TD>
			<TR><TD>-2.0 to +2.0</TD>		<TD> about 96%</TD>
			<TR><TD>-3.0 to +3.0</TD>		<TD> >99%</TD>
			<TR><TD>-5.0 to +5.0</TD>		<TD> 100%</TD>
			<TR><TD>-infinity to 0.0</TD>	<TD> 50%</TD>
			<TR><TD>0.0 to +infinity</TD>	<TD> 50%</TD>
		</TABLE>

		In theory, this routine could occasionally generate very large positive or
		negative values but in fact, no numbers outside the range -5 to +5 are generated.
	*/
	AIAPI AIFixed (*FixedRndBellCurve) ( void );

	/** Sets the random number seed used to generate subsequent random
		numbers. Use to restart a sequence of random numbers, for example for
		debugging. See \c #AIRandomSuite::GetRndSeed() for an example. <br>
		(Note that this function does not return an error code.)
			@param The new seed number, or 0 to set to an initial
				seed based on the current date and time.
		*/
	AIAPI void (*SetRndSeedBellCurve) ( ai::int32 seed );

	/** Retrieves the current random-number seed. The initial seed
		is based on the current date and time.<br>
		 (Note that this function returns a numeric value, not an error code.)
		 	@return The random seed.
			@see \c #AIRandomSuite::GetRndSeed()
		*/
	AIAPI ai::int32 (*GetRndSeedBellCurve) ( void );

} AIRandomBellCurveSuite;


#include "AIHeaderEnd.h"


#endif
