#ifndef __AIRandom__
#define __AIRandom__

/*
 *        Name:	AIRandom.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Random Number Suite.
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

/** @file AIRandom.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIRandomSuite			"AI Random Suite"
#define kAIRandomSuiteVersion5	AIAPI_VERSION(5)
#define kAIRandomSuiteVersion	kAIRandomSuiteVersion5
#define kAIRandomVersion		kAIRandomSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Together with the \c #AIRandomBellCurveSuite, this suite allows you
	to add a degree of randomness, or "noise" to an effect. This suite provides
	an even distribution of random numbers (as opposed to numbers
	distributed along a standard probability curve).

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIRandomSuite and \c #kAIRandomVersion.
*/
typedef struct {

	/** Gets a random number in the range [0.0..1.0].
		(Note that this function returns a numeric value, not an error code.)
			@return The random number.
		*/
	AIAPI AIReal (*FloatRnd) ( void );

	/** Sets the random number seed used to generate subsequent random
		numbers. Use to restart a sequence of random numbers, for example for
		debugging. See \c #GetRndSeed() for an example.<br>
		(Note that this function does not return an error code.)
			@param The new seed number, or 0 to set to an initial
				seed based on the current date and time.

		*/
	AIAPI void (*SetRndSeed) ( ai::int32 seed );

	/** Retrieves the current random-number seed. The initial seed
		is based on the current date and time.<br>
		 (Note that this function returns a numeric value, not an error code.)
		 	@return The random seed.

		To restart a random number sequence, get and save the seed,
		generate the random numbers, then reset the seed with \c #SetRndSeed()
		and generate the sequence again. For example, these two random loops
		generate the same sequence:
@code
AIReal r;
short i;
long seed = sRandom->GetRndSeed();
for ( i = 0; i < 10; ++i ) {
	r = sRandom->FloatRnd();
}
sRandom->SetRndSeed( seed );
for ( i = 0; i < 10; ++i ) {
	r = sRandom->FloatRnd();
}
@endcode
		*/
	AIAPI ai::int32 (*GetRndSeed) ( void );

} AIRandomSuite;

#include "AIHeaderEnd.h"


#endif
