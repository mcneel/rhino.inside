#ifndef __AITabletData__
#define __AITabletData__

/*
 *        Name:	AITabletData.h
 *   $Revision: 3 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Tablet Data Suite
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#include "AIHeaderBegin.h"

/** @file AITabletData.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAITabletDataSuite			"AI TabletData Suite"
#define kAITabletDataSuiteVersion	AIAPI_VERSION(3)
#define kAITabletDataVersion		kAITabletDataSuiteVersion


/** Types of tablet data that can be stored with a path. */
typedef enum {
	/** Stylus pressure. */
	kTabletPressure = 0,
	/** Stylus wheel pressure, also called tangential or barrel pressure */
	kTabletStylusWheel,
	/** Tilt, also called altitude. */
	kTabletTilt,
	/** Bearing, also called azimuth. */
	kTabletBearing,
	/** Rotation. */
	kTabletRotation,
	/** internal */
	kTabletTypeCount //Put all new tablet types before this
} AITabletDataType;


/** Tablet data is described by an array of (offset, value) pairs. Both values are
	in the range [0,1]. Internally the data is stored as an array of small integers
	such that the offsets have a maximum resolution of 1/100 and the values have
	a maximum resolution of 1/256.
 */
typedef struct {
	/** Tablet data offset, in the range [0..1]. */
	AIReal offset;
	/** Tablet data value, in the range [0..1]. */
	AIReal value;
} AITabletProfile;

/** @ingroup Errors
	See \c #AITabletDataSuite */
#define kNotEnoughSpace		'!spc'

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that allow you to access and manipulate
	tablet-device data that is attached to path objects.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAITabletDataSuite and \c #kAITabletDataVersion.
 */
typedef struct {

	/** Retrieves tablet data attached to a path.
			@param path The path object.
			@param profile [in, out] An array in which to return the tablet data. If no data is
				present, this is set to \c NULL and \c count is set to 0. If the array is not
				large enough, \c count is set to the size of the array needed, and
				\c #kNotEnoughSpace is returned.
			@param count [in, out] The size of the array passed. On return,
				the number of entries filled in the array, or, if the passed
				array is not large enough, the size of the array needed.
			@param type The type of tablet data to retrieve.
			@return \c #kNotEnoughSpace error if the passed array is not large enough to hold the data.
	 */
	AIAPI AIErr (*GetTabletData) ( AIArtHandle path, AITabletProfile **profile, ai::int32 *count, AITabletDataType type );

	/** Sets tablet data for a path.
			@param path The path object.
			@param profile An array containing the tablet data.
			@param count  The size of the array passed.
			@param type The type of the tablet data.
		*/
	AIAPI AIErr (*SetTabletData) ( AIArtHandle path, AITabletProfile *profile, ai::int32 count, AITabletDataType type );

	/**	Reports whether tablet data is being stored with a path.
			@param path The path object.
			@param inUse [out] A buffer in which to return true if a tablet
				is in use for the path.
		*/
	AIAPI AIErr (*GetTabletDataInUse) ( AIArtHandle path, AIBoolean *inUse );

	/**	Sets the state of tablet use for a path.
			@param path The path object.
			@param inUse True if a tablet is in use for the path, false otherwise.
		*/
	AIAPI AIErr (*SetTabletDataInUse) ( AIArtHandle path, AIBoolean inUse );

	/**	Splits a set of tablet data into two sets to go with the two parts of a split path.
			@param orig An array containing the original tablet data.
			@param origCount The number of entries in the original data array.
			@param part1 [out] An array in which to return the first part of the tablet data.
			@param part1Count [in, out] The size of the part-one array. On return, the number
				of elements filled.
			@param part2 [in, out] An array in which to return the second part of the tablet data.
			@param part2Count [in, out] The size of the part-two array. On return, the number
				of elements filled.
			@param split A value between [0..1] which indicates the offset at which
				 to split the data. A value of 0.5, for example, splits the data in half.
				 Used to rescale the offsets in the new tablet data sets.
			@return The error \c #kNotEnoughSpace if either output array is not big
				enough to hold the returned data.
		*/
	AIAPI AIErr (*SplitTabletData) ( AITabletProfile *orig, ai::int32 origCount,
		AITabletProfile **part1, ai::int32 *part1Count, AITabletProfile **part2, ai::int32 *part2Count,
			AIReal split );

	/**	Extends the size of a set of tablet data.
			@param orig An array containing the original tablet data.
			@param origCount The number of entries in the original data array.
			@param extendedProfile [in, out] A buffer in which to pass additional
				profile data to merge with the original, and return the merged profile.
			@param extendedCount [in, out] A buffer in which to pass then number of entries in the
				additional profile data	and return the size of the merged profile.
			@param newStart	The index of the beginning of new data in the extended profile.
			@param newEnd The index of the end of new data in the extended profile.
		*/
	AIAPI AIErr (*ExtendTabletData) ( AITabletProfile *orig, ai::int32 origCount,
		AITabletProfile **extendedProfile, ai::int32 *extendedCount, AIReal newStart, AIReal newEnd );

	/**	Combines two sets of tablet data into a single set.
			@param part1 An array containing the first part of the tablet data.
			@param part1Count The size of the part-one array.
			@param part2 An array containing the second part of the tablet data.
			@param part2Count The size of the part-two array.
			@param joined [out] An array in which to return the combined tablet data.
  			@param joinedCount [in, out] The size of the joined array. On return, the number
				of elements filled.
			@param part1Ends A value between [0..1] which indicates the offset at which
				the first part of the tablet data ends. Must be less than or equal to
				\c part2Begins.	Used to rescale the offsets in the new tablet data.
			@param part2Begins A value between [0..1] which indicates the offset at which
				the second part of the tablet data begins. Must be greater than or equal to
				\c part1Ends. Used to rescale the offsets in the new tablet data.
			@return The error \c #kNotEnoughSpace if the output array is not big
				enough to hold the returned data.
		*/
	AIAPI AIErr (*JoinTabletData) ( AITabletProfile *part1, ai::int32 part1Count,
		AITabletProfile *part2, ai::int32 part2Count, AITabletProfile **joined, ai::int32 *joinedCount,
			AIReal part1Ends, AIReal part2Begins);

} AITabletDataSuite;


#include "AIHeaderEnd.h"


#endif
