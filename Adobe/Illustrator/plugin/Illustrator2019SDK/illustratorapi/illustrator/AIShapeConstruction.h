#ifndef __AIShapeConstruction__
#define __AIShapeConstruction__

/*
 *        Name:	AIShapeConstruction.h
 *     Purpose:	Adobe Illustrator utility routines for some basic shapes construction.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1996-2015 Adobe Systems Incorporated.
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

#include "AITypes.h"
#include "AIArt.h"


#include "AIHeaderBegin.h"

/** @file AIShapeConstruction.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIShapeConstructionSuite			"AI Shape Construction Suite"
#define kAIShapeConstructionSuiteVersion	AIAPI_VERSION(8)
#define kAIShapeConstructionVersion			kAIShapeConstructionSuiteVersion


/** @ingroup Errors
	See \c #AIShapeConstructionSuite */
#define kNoSegmentsError					'0SEG'
/** @ingroup Errors
	See \c #AIShapeConstructionSuite */
#define kArtworkTooComplexErr				'cmp!'


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides utilities for creating paths whose shapes
	describe a particular geometric figure. All of the utilities take parameters
	that describe the geometric figure and return a new art object. The art object
	is created in the art tree at the current insertion point as returned by
	\c #AIArtSuite::GetInsertionPoint().

	@note The shape suite is supplied by a plug-in, which the user can remove.
	Clients of the shape suite should fail gracefully if it	is not available.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIShapeConstructionSuite and \c #kAIShapeConstructionVersion.
 */
typedef struct {
	/** Creates a path for a rectangle.
			@param fromPoint The upper left point.
			@param toPoint The lower right point.
			@param isCentered True to center the figure.
			@param isReversed True to reverse the figure.
			@param isConstrained True to constrain the figure.
			@param honorConstrainAngle True to constrain the angle.
			@param art [out] A buffer in which to return the new path object.
			@param size [out] A buffer in which to return a point giving the
				horizontal and vertical size of the figure, in document points.
		*/
	AIAPI AIErr (*NewPointPointRect)( AIRealPoint fromPoint, AIRealPoint toPoint,
									  AIBoolean isCentered, AIBoolean isReversed, AIBoolean isConstrained,
									  AIBoolean honorConstrainAngle,
									  AIArtHandle *art, AIRealPoint *size );

	/** Creates a path for a rectangle of a given size.
			@param fromPoint The upper left point.
			@param size A point whose components specify the horizontal and vertical
				size of the figure,	in document points.
			@param isCentered True to center the figure.
			@param isReversed True to reverse the figure.
			@param isConstrained True to constrain the figure.
			@param honorConstrainAngle True to constrain the angle.
			@param art [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewPointSizeRect)( AIRealPoint fromPoint, AIRealPoint size,
									 AIBoolean isCentered, AIBoolean isReversed,
									 AIBoolean honorConstrainAngle,
									 AIArtHandle *art );

	/** Creates a path for an oval from two focus points.
			@param fromPoint The first focus point.
			@param toPoint The second focus point.
			@param isCentered True to center the figure.
			@param isReversed True to reverse the figure.
			@param isConstrained True to constrain the figure.
			@param isCircumscribed True to circumscribe the figure.
			@param honorConstrainAngle True to constrain the angle.
			@param art [out] A buffer in which to return the new path object.
			@param size [out] A buffer in which to return a point giving the
				horizontal and vertical size of the figure, in document points.
		*/
	AIAPI AIErr (*NewPointPointOval)( AIRealPoint fromPoint, AIRealPoint toPoint,
									  AIBoolean isCentered, AIBoolean isReversed, AIBoolean isConstrained, AIBoolean isCircumscribed,
									  AIBoolean honorConstrainAngle,
									  AIArtHandle *art, AIRealPoint *size  );

	/** Creates a path for an oval of a given size.
			@param fromPoint The source point.
			@param size A point whose components specify the horizontal and vertical
				size of the figure, in document points.
			@param isCentered True to center the figure.
			@param isReversed True to reverse the figure.
			@param isConstrained True to constrain the figure.
			@param honorConstrainAngle True to constrain the angle.
			@param art [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewPointSizeOval)( AIRealPoint fromPoint, AIRealPoint size,
									 AIBoolean isCentered, AIBoolean isReversed,
									 AIBoolean honorConstrainAngle,
									 AIArtHandle *art );

	/** Creates a path for a rounded rectangle.
			@param fromPoint The upper left point.
			@param toPoint The lower right point.
			@param isCentered True to center the figure.
			@param isReversed True to reverse the figure.
			@param isConstrained True to constrain the figure.
			@param honorConstrainAngle True to constrain the angle.
			@param art [out] A buffer in which to return the new path object.
			@param size [out] A buffer in which to return a point giving the
				horizontal and vertical size of the figure, in document points.
		*/
	AIAPI AIErr (*NewPointPointRoundedRect)( AIRealPoint fromPoint, AIRealPoint toPoint, AIRealPoint radius,
											 AIBoolean isCentered, AIBoolean isReversed, AIBoolean isConstrained,
											 AIBoolean honorConstrainAngle,
											 AIArtHandle *art, AIRealPoint *size  );

	/** Creates a path for a rounded rectangle of a given size.
			@param fromPoint The upper left point.
			@param size A point whose components specify the horizontal and vertical
				size of the figure, in document points.
			@param isCentered True to center the figure.
			@param isReversed True to reverse the figure.
			@param isConstrained True to constrain the figure.
			@param honorConstrainAngle True to constrain the angle.
			@param art [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewPointSizeRoundedRect)( AIRealPoint fromPoint, AIRealPoint size, AIRealPoint radius,
											AIBoolean isCentered, AIBoolean isReversed,
											AIBoolean honorConstrainAngle,
											AIArtHandle *art );

	/** Creates a path for a rectangle from page coordinates for the sides.
			@param top The X coordinate of the top.
			@param left The Y coordinate of the left edge.
			@param bottom The X coordinate of the bottom.
			@param right The Y coordinate of the right edge.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewRect)( AIReal top, AIReal left,
							AIReal bottom, AIReal right,
	                        AIBoolean reversed, AIArtHandle *newArt);

	/** Creates a path for a rectangle of a given size, centered around a point.
			@param centerX The X coordinate of the center.
			@param centerY The Y coordinate of the center.
			@param height The height in document points.
			@param width The width in document points.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewCenteredRect)( AIReal centerX, AIReal centerY,
									AIReal height, AIReal width,
	                                AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for a rounded rectangle from page coordinates for the sides.
			@param top The X coordinate of the top.
			@param left The Y coordinate of the left edge.
			@param bottom The X coordinate of the bottom.
			@param right The Y coordinate of the right edge.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewRoundedRect)( AIReal top, AIReal left,
								   AIReal bottom, AIReal right,
                                   AIReal horizRadius, AIReal vertRadius,
	                               AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for a rounded rectangle of a given size, centered around a point.
			@param centerX The X coordinate of the center.
			@param centerY The Y coordinate of the center.
			@param height The height in document points.
			@param width The width in document points.
			@param horizRadius The horizontal radius of the rounded corners, in document points.
			@param vertRadius The vertical radius of the rounded corners, in document points.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
  	AIAPI AIErr (*NewCenteredRoundedRect)( AIReal centerX, AIReal centerY,
										   AIReal height, AIReal width,
                                           AIReal horizRadius, AIReal vertRadius,
	                                       AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for an oval inscribed within a rectangle,
		from page coordinates for the sides.
			@param top The X coordinate of the top.
			@param left The Y coordinate of the left edge.
			@param bottom The X coordinate of the bottom.
			@param right The Y coordinate of the right edge.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewInscribedOval)( AIReal top, AIReal left,
									 AIReal bottom, AIReal right,
									 AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for an oval circumscribed around a rectangle,
		from page coordinates for the sides.
			@param top The X coordinate of the top.
			@param left The Y coordinate of the left edge.
			@param bottom The X coordinate of the bottom.
			@param right The Y coordinate of the right edge.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewCircumscribedOval)( AIReal top, AIReal left,
										 AIReal bottom, AIReal right,
										 AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for an oval inscribed within a rectangle of a given size,
		centered around a point.
			@param centerX The X coordinate of the center.
			@param centerY The Y coordinate of the center.
			@param height The height in document points.
			@param width The width in document points.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewInscribedCenteredOval)( AIReal centerX, AIReal centerY,
											 AIReal height, AIReal width,
											 AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for an oval circumscribed around a rectangle of a given size,
		centered around a point.
			@param centerX The X coordinate of the center.
			@param centerY The Y coordinate of the center.
			@param height The height in document points.
			@param width The width in document points.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewCircumscribedCenteredOval)( AIReal centerX, AIReal centerY,
												 AIReal height, AIReal width,
												 AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for a regular polygon of a given radius,
		centered around a point.
			@param numSides The number of sides.
			@param centerX The X coordinate of the center.
			@param centerY The Y coordinate of the center.
			@param radius The radius, in document points.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewRegularPolygon)( ai::uint16 numSides,
									  AIReal centerX, AIReal centerY, AIReal radius,
	                                  AIBoolean reversed, AIArtHandle *newArt );
	/** Creates a path for a regular polygon with a given vertex point,
		centered around a point.
			@param numsides The number of sides.
			@param center The center point.
			@param vertex The vertex point.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewRegularPolygonPoint)( ai::uint16 numsides,
										   AIRealPoint center, AIRealPoint vertex,
	                                       AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for an n-pointed star with a given radius,
		centered around a point.
			@param numPoints The number of star points.
			@param centerX The X coordinate of the center.
			@param centerY The Y coordinate of the center.
			@param radius1 The first radius, in document points.
			@param radius2 The second radius, in document points.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewStar)( ai::uint16 numPoints,
							AIReal centerX, AIReal centerY,
							AIReal radius1, AIReal radius2,
							AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for an n-pointed star with a given vertex point and radius ratio,
		centered around a point.
			@param numPoints The number of star points.
			@param center The center point.
			@param vertex The vertex point.
			@param radiusRation The radius ratio.
			@param reversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewStarPoint)( ai::uint16 numPoints,
								 AIRealPoint center, AIRealPoint vertex,
	                             AIReal radiusRatio,
								 AIBoolean reversed, AIArtHandle *newArt );

	/** Creates a path for spiral around a point.
			@param firstArcCenter The center point for the first arc of the spiral.
			@param start The starting point.
			@param decayPercent The decay ration expressed as a percentage.
			@param numQuarterTurns The number of quarter turns.
			@param clockwiseFromOutside True to spiral clockwise.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewSpiral)( AIRealPoint firstArcCenter, AIRealPoint start,
		AIReal decayPercent, ai::int16 numQuarterTurns,
                              AIBoolean clockwiseFromOutside, AIArtHandle *newArt );

	/** Creates a path for elliptical pie around a point.
			@param center The center point for the ellipse of which this pie is a part of.
			@param width The width of the ellipse of which this pie is a part of.
			@param height The height of the ellipse of which this pie is a part of.
			@param rotationAngle The rotation angle of the ellipse of which this pie is a part of.
			@param startAngle absolute start angle of the pie.
			@param endAngle absolute end angle of the pie.
			@param isReversed True to reverse the figure.
			@param newArt [out] A buffer in which to return the new path object.
		*/
	AIAPI AIErr (*NewEllipticalPie)(AIRealPoint center, AIReal width, AIReal height,
									AIReal rotationAngle, AIReal startAngle, AIReal endAngle,
									AIBoolean isReversed, AIArtHandle *newArt);

	/** Creates a path for a line.
	@param startPoint The starting point of line.
	@param endPoint The end point of line.
	@param art [out] A buffer in which to return the new path object.
	*/

	AIAPI AIErr(*NewLinePoint)(const AIRealPoint& startPoint, const AIRealPoint& endPoint,
							   AIArtHandle *newArt);

	/** Creates a path for a line.
	@param center The coordinate of the center of line (Mid point of line).
	@param length of line in document points.
	@param rotationAngle absolute rotation angle of the line.
	@param art [out] A buffer in which to return the new path object.
	*/
	AIAPI AIErr(*NewLine)(const AIRealPoint& center, const AIReal length, const AIReal
						  rotationAngle, AIArtHandle *newArt);
	

} AIShapeConstructionSuite;


#include "AIHeaderEnd.h"

#endif
