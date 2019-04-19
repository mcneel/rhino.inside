/*************************************************************************
*
*ADOBE SYSTEMS INCORPORATED
* Copyright 2010 Adobe Systems Incorporated
* All Rights Reserved.
*
*NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
*terms of the Adobe license agreement accompanying it.  If you have received this file from a 
*source other than Adobe, then your use, modification, or distribution of it requires the prior 
*written permission of Adobe.
*
**************************************************************************/

#ifndef AICoreTransformTypesSuite_h__
#define AICoreTransformTypesSuite_h__

///*********	Transformations    ******************

/** Transformation types used in \c #AIOverrideColorConversionSuite. */

enum TransformType
{
	nullTransformType,		// no transformation
	translateTransformType,
	scaleTransformType,
	rotateTransformType,
	reflectTransformType,
	shearTransformType,
	pluginTransformType,	// call a plug-in
	compoundTransformType	// combines several of the above
};

// Save translation in two forms, so that round-off error from converting to
//	h/v and back to dist/angle doesn't show up in the distance/angle fields
//	when specifying a dist/angle translation and then bringing the dialog
//	back up. We use only the h/v form for performing the transformation.
//	[Teri 5/24/93]
/** Parameters structure for a Move transformation.
See \c #AIOverrideColorConversionSuite.
*/
struct TranslateTransform
{
	AIReal h;
	AIReal v;
	AIReal dist;		// in points
	AIReal angle;	// in degrees
};

/** Parameters structure for a Scale transformation.
See \c #AIOverrideColorConversionSuite.
*/
struct ScaleTransform
{
	AIRealPoint	scale;			// in percentages, relative to constrain angles
	AIReal		strokeScale;	// the value to multiply strokes by if doLines is true
	// (usually sqrt(abs(matrix.a * matrix.d))
	bool		uniform;
	bool		doLines;
};

/** Parameters structure for a Rotate transformation.
See \c #AIOverrideColorConversionSuite.
 */
struct RotateTransform
{
	AIReal angle;	// in degrees, counter-clockwise
	AIReal radians;	// in radians
};

/** Parameters structure for a Reflect transformation.
See \c #AIOverrideColorConversionSuite.
 */
struct ReflectTransform
{
	AIReal angle;	// around which to reflect, in degrees
	AIReal radians;	// in radians
};

/** Parameters structure for a Shear transformation.
See \c #AIOverrideColorConversionSuite.
 */
struct ShearTransform
{
	AIReal shear;	// in degrees
	AIReal angle;	// in degrees
};

/** A union of transformation types.
See \c #MatrixTform and \c #AIOverrideColorConversionSuite.
 */
union TransformUnion
{
	TranslateTransform mov;
	ScaleTransform sca;
	RotateTransform rot;
	ReflectTransform ref;
	ShearTransform shr;
};

/** This structure describes a transformation, in "descriptive" form and matrix form.
 If originInMatrix is true, the origin is incorporated into the matrix, and points
 can be transformed by the matrix directly. If not, the matrix represents a
 transformation around (0,0), and to transform points, they must first be translated
 by -origin, then transformed by the matrix, then translated back by +origin.

 Some transformations cannot be represented with the origin in the matrix because
 they would get fixed point overflow in the h and v components; for example, scaling by
 any factor over 8 around an origin near the center of the screen.

 The TransformUnion struct is sometimes a more convenient description for
 transforming patterns, gradients, text anchors, and graph elements. If type
 is compoundTransformType, though, only tu.sca.strokeStyle is looked at if
 tu.sca.doLines is true.
*/
struct MatrixTform
{
	AIRealMatrix matrix;
	AIRealPoint origin;
	/** True if the origin is incorporated into the matrix, and points
 		can be transformed by the matrix directly. */
	bool originInMatrix;
	TransformType type;
	TransformUnion tu;
};

/** Constants for reference point values in the Preferences dialog Transform panel.
	Get values from
	\c #AIPreferenceSuite::GetIntegerPreference("AdobeTransformObjects", "AnchorPoint", &anchorPointOut).
	Pin indexing scheme, 9 pin
	* 0---1---2
	* |   |   |
	* 3---4---5
	* |   |   |
	* 6---7---8
*/
enum NinePointReferencePointInPreferences
{
	 /** Integer value 0*/
	 kAININE_PIN_LEFT_TOP = 0,
	 /** Integer value 1*/
	 kAININE_PIN_MID_TOP,
	 /** Integer value 2*/
	 kAININE_PIN_RIGHT_TOP,
	 /** Integer value 3*/
	 kAININE_PIN_LEFT_MID,
	 /** Integer value 4*/
	 kAININE_PIN_MID_MID,
	 /** Integer value 5*/
	 kAININE_PIN_RIGHT_MID,
	 /** Integer value 6*/
	 kAININE_PIN_LEFT_BOTTOM,
	 /** Integer value 7*/
	 kAININE_PIN_MID_BOTTOM,
	 /** Integer value 8*/
	 kAININE_PIN_RIGHT_BOTTOM
};


#endif //AICoreTransformTypesSuite_h__