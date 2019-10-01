#ifndef __AIEnvelope__
#define __AIEnvelope__

/*
 *        Name:	AIEnvelope.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Envelope Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2013 Adobe Systems Incorporated.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIDict__
#include "AIDictionary.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIEnvelope.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIEnvelopeSuite						"AI Envelope Suite"
#define kAIEnvelopeSuiteVersion4				AIAPI_VERSION(4)
#define kAIEnvelopeSuiteVersion					kAIEnvelopeSuiteVersion4
#define kAIEnvelopeVersion						kAIEnvelopeSuiteVersion

/** Envelope options bit flag.
	When set, expand and distort the appearance of an object
	(such as applied effects or styles) and not just the object's
	underlying geometry.
	When false, the appearance is applied after the envelope
	distorts the underlying geometry. */
#define kDeformExpandAppearance 		(1 << 0)
/** Envelope options bit flag.
	When set, expand and distort pattern fill. */
#define kDeformExpandPatternFills		(1 << 1)
/** Envelope options bit flag.
	When set, expand and distort gradient fill. */
#define kDeformExpandLinearGradients	(1 << 2)

/** Options bit flag for \c #AIEnvelopeSuite::DeformArt().
	When set, expand and deform text.
	(Envelopes do this automatically, regardless of flag value.)
 */
#define kDeformExpandText			(1 << 3)
 /** Options bit flag for \c #AIEnvelopeSuite::DeformArt().
	When set, deform objects in any opacity masks associated with the
	source art (as created with the Transparency palette).
	(Envelopes do this automatically, regardless of flag value.) */
#define kDeformOpacityMasks			(1 << 4)
/** Options bit flag for \c #AIEnvelopeSuite::DeformArt().
	When set, expand and deform plug-in groups.
	(Envelopes do this automatically, regardless of flag value.)*/
#define kDeformExpandPluginGroups	(1 << 5)
/** Options bit flag for \c #AIEnvelopeSuite::DeformArt().
	When set, expand and deform symbols.
	(Envelopes do this automatically, regardless of flag value.)*/
#define kDeformExpandSymbols		(1 << 6)
/** Options bit flag for \c #AIEnvelopeSuite::DeformArt().
	Sets all flags except \c #kDeformNonAARaster and \c #kDeformRasterMakeClip. */
#define kDeformAll					(0x0000FFFF)
/** Envelope options bit flag.
	When set, anti-alias is \e not used to smooth
	raster images that are distorted in envelopes. */
#define kDeformNonAARaster			(1 << 16)
/** Envelope options bit flag.
	How to preserve raster shapes when they are distorted by non-rectangular envelopes.
		\li When set, apply an alpha channel (transparency) to the raster image.
		\li When clear,	use a clipping mask	on the raster image.
	 */
#define kDeformRasterMakeClip		(1 << 17)


/** @ingroup DictKeys
	Dictionary key for \c mesh value \c #AIEnvelopeSuite::DeformArt().
	Entry value is an \c #AIArtHandle of \c #kMeshArt type */
#define kAIDeformMeshKey		"DeformMesh"
/** @ingroup DictKeys
	Dictionary key for \c fidelity value in \c #AIEnvelopeSuite::DeformArt().
	Controls how closely the deformed object fits into the envelope region.
	Higher values add more points to the distorted paths, and take longer
	to calculate. Entry value is an \c ASInt32 in the range <code>[0..100]</code> */
#define kAIDeformFidelityKey	"DeformFidelity"	// ASInt32  [0..100]
/** @ingroup DictKeys
	Dictionary key for \c options value in \c #AIEnvelopeSuite::DeformArt().
	Entry value is a logical OR of option values; see \c #AIEnvelopeOptions. */
#define kAIDeformOptionsKey		"DeformOptions"		// ASInt32

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Envelope deformation options that control how art is deformed.
	@see \c #AIEnvelopeSuite::MakeEnvelope() */
typedef struct
{
	/** Options, a logical OR of option values:
		<br>\c #kDeformExpandAppearance
		<br>\c #kDeformExpandPatternFills
		<br>\c #kDeformExpandLinearGradients
		<br>\c #kDeformNonAARaster
		<br>\c #kDeformRasterMakeClip
	*/
	ai::int32 envOptions;
	/** Controls how closely the deformed object fits into the envelope region.
	Higher values add more points to the distorted paths, and take longer
	to calculate. An \c ASInt32 n the range <code>[0..100]</code> */
	ai::int32 fidelity;

} AIEnvelopeOptions;

/** Callback for progress reports during a call to \c #AIEnvelopeSuite::DeformArt().
		@param current The current progress, a value between 0 and \c total.
		@param total A value at which the operation is complete.
		@return False if user cancels the operation, otherwise true. */
typedef AIAPI AIBoolean (*AIDeformProgressProc)(ai::int32 current, ai::int32 total);

/** Predefined warp styles for \c #AIEnvelopeSuite::WarpEnvelope(). */
typedef enum
{
	kWarpStyleArc = 1,
	kWarpStyleArcLower,
	kWarpStyleArcUpper,
	kWarpStyleArch,
	kWarpStyleBulge,
	kWarpStyleShellLower,
	kWarpStyleShellUpper,
	kWarpStyleFlag,
	kWarpStyleWave,
	kWarpStyleFish,
	kWarpStyleRise,
	kWarpStyleFisheye,
	kWarpStyleInflate,
	kWarpStyleSqueeze,
	kWarpStyleTwist

} AIWarpStyle;

/** Envelope types; see \c #AIEnvelopeSuite::GetEnvelopeType().  */
typedef enum
{
	kEnvelopeWarp = 1,
 	kEnvelopeMesh,
 	kEnvelopeObject
} AIEnvelopeType;

/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite provides functions to create and manage \e envelopes, which allow you to apply
	a set of deformations to a set of source art objects. The name derives from the idea of
	putting paper artworks into an envelope, then bending or distorting the envelope.

	The source art can be warped or deformed in various ways, as defined by an \c #AIWarpStyle,
	with respect to a  \e mesh, or grid. The envelope actions are available in the UI
	through the Object > Envelope Distort menu.

	Deformations can only be applied directly to paths, compound paths, meshes, and images.
	To apply a distortion to other types of art objects in the source art, those objects must
	first be \e expanded; that is, converted to paths. Deformation options allow you
	to specify which types of art to expand and deform along with the paths and
	images.

	The envelope for an art group, which encapsulates the deformation options,
	is represented as an art object of type \c #kMeshArt. See also the \c #AIMeshSuite.

	The function \c #DeformArt() allows you to apply the same kinds of deformations
	directly to a source art group, without creating an envelope object.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIEnvelopeSuite and \c #kAIEnvelopeVersion.

*/
typedef struct {

	/** Creates an envelope for a given set of source art objects, or for the currently
		selected art if \c art is \c nullptr or \c numArt is 0. By default, the new envelope
		is fully selected, and placed above the enveloped art object or objects in the paint order.
			@param art An array of art objects to be enveloped, or \c nullptr to create an envelope
				for the current selection. Cannot be an art object stored in a dictionary,
				but can be the child of	art stored in a dictionary.
			@param numArt The number of objects in \c art, or 0 to create an
				envelope for the current selection.
			@param envelopeObject The path art object to use as the new envelope,
				or \c nullptr to use the bounding box of \c art (or of the current selection)
				to create a new envelope object. (This would be the topmost selected
				object if you create the envelope using Object > Envelope Distort > Make
				with Top Object.)
			@param options A pointer to the structure that specifies deformation options
				for the new envelope. Pass \c nullptr to use the default options, as specified
				by application preferences.
			@param envelope [out] A buffer in which to return the new envelope object.
	 */
	AIAPI AIErr (*MakeEnvelope) ( AIArtHandle* art, ai::int32 numArt, AIArtHandle envelopeObject,
								  AIEnvelopeOptions* options, AIArtHandle* envelope );

	/** Redefines an envelope to use a predefined warp style.
		The envelope must be in process of mesh-editing; that is,
		\c #EditingMesh() would return true for \c envelope.
		Upon return the envelope is fully selected.
			@param envelope The envelope object.
			@param warpStyle The new warp style.
			@param bend the new bend amount.
			@param horizDistort The horizontal distortion amount.
			@param vertDistort The vertical distortion amount.
			@param rotate90 When true, apply bend horizontally, when false, apply bend vertically.
	 */
	AIAPI AIErr (*WarpEnvelope) ( AIArtHandle envelope, AIWarpStyle warpStyle, AIReal bend,
								  AIReal horizDistort, AIReal vertDistort, AIBoolean rotate90 );

	/** Replaces an envelope in the document with its source contents (in the original,
		undistorted state) and a mesh object. Moves both objects into the art tree, with the mesh object
		placed above the content object in the paint order. The content object is selected.

		You cannot release envelopes stored directly in dictionaries,
		but you can release the children of envelopes stored in dictionaries.
			@param envelope The envelope object. Upon return, this reference is no longer valid.
		*/
	AIAPI AIErr (*ReleaseEnvelope) ( AIArtHandle envelope );

	/** Retrieves the distortion options for an envelope. (Note that this function does not
		return an error code.)
			@param envelope The envelope object.
			@param options [out] A buffer in which to return the options structure,
		*/
	AIAPI void (*GetEnvelopeOptions) ( AIArtHandle envelope, AIEnvelopeOptions* options );

	/** Sets the distortion options for an envelope. (Note that this function does not
		return an error code.)
			@param envelope The envelope object.
			@param options The new options structure,  */
	AIAPI void (*SetEnvelopeOptions) ( AIArtHandle envelope, AIEnvelopeOptions* options );

	/** Retrieves the default distortion options stored in application preferences.
			@param options [out] A buffer in which to return the default options structure,
			*/
	AIAPI void (*GetCurrentEnvelopeOptions) ( AIEnvelopeOptions* options );

	/** Reports whether an art object is an envelope.
		(Note that this function returns a boolean value, not an error code.)
			@param envelope The art object.
			@return True if the art object is an envelope.
		*/
	AIAPI AIBoolean (*IsEnvelope) ( AIArtHandle envelope );

	/** Reports whether the mesh defining the distortion of an envelope is being edited.
		(Note that this function returns a boolean value, not an error code.)
			@param envelope The envelope object.
			@return True if the mesh is being edited.
			@see \c #ToggleEditability(), \c #EditingContents()
	*/
	AIAPI AIBoolean (*EditingMesh) ( AIArtHandle envelope );

	/** Reports whether the contents of an envelope are being edited.
		(Note that this function returns a boolean value, not an error code.)
			@param envelope The envelope object.
			@return True if the contents of the envelope are being edited.
			@see \c #ToggleEditability(), \c #EditingMesh()
		*/
	AIAPI AIBoolean (*EditingContents) ( AIArtHandle envelope );

	/** Switches between editing the mesh and the contents of an envelope.
		This is the same as choosing Object > Envelope Distort > Edit Contents
		or Object > Envelope Distort > Edit Envelope in the UI.
			@param envelope The envelope object.
			@see \c #EditingMesh(), \c #EditingContents()
		*/
	AIAPI AIErr (*ToggleEditability) ( AIArtHandle envelope );

	/** Retrieves the envelope object for an art group.
			@param envelope The art group.
			@param envelopeObject [out] A buffer in which to return the envelope object.

		*/
	AIAPI AIErr (*GetEnvelopeObject) ( AIArtHandle envelope, AIArtHandle* envelopeObject );

	/** Sets the envelope object for an art group.
			@param envelope The art group.
			@param envelopeObject The envelope object, which must be of type \c #kPathArt or
				\c #kMeshArt and must not be directly stored in a dictionary.
		*/
	AIAPI AIErr (*SetEnvelopeObject) ( AIArtHandle envelope, AIArtHandle envelopeObject );

	/** Retrieves the art objects being deformed by an envelope.
			@param envelope The envelope object.
			@param objects [out] A buffer in which to return the art group. This can be
				the edit group of envelope's source art group if the contents are being
				edited (that is, if \c #EditingContents() would return true for \c envelope).
		*/
	AIAPI AIErr (*GetObjectsInEnvelope) ( AIArtHandle envelope, AIArtHandle* objects );

	/** Deforms an art object or group using the parameters in a dictionary. Does not
		make an envelope object, but deforms the art in the same way an envelope would.
		The resulting art object is inserted in the art tree above the original
		art object in the paint order.
			@param artToDeform The source art object or group, which must have a parent.
				The function does not modify this object in any way.
			@param deformParams A dictionary containing the deformation parameters.
				Contains entries for these keys: \c #kAIDeformMeshKey, \c #kAIDeformFidelityKey,
				\c #kAIDeformOptionsKey.
			@param srcRect The bounding box of the source space (that is, the size the envelope
				would be), or \c nullptr to use the bounds of the source art.
			@param deformedArt [out] A buffer in which to return the resulting art object.
			@param progressProc A callback procedure for displaying a progress bar during
				computation (from which the user can cancel the operation)
				or \c nullptr to show no progress bar.
			@return The error \c #kCanceledErr if user cancels the operation from the
				progress bar.
		 */
	AIAPI AIErr (*DeformArt) ( AIArtHandle 			artToDeform,
							   AIDictionaryRef 		deformParams,
							   AIRealRect* 			srcRect,
							   AIArtHandle*			deformedArt,
							   AIDeformProgressProc	progressProc );

	/** not implemented */
	AIAPI AIErr (*GenerateDeformMeshFromPath)( AIArtHandle pathArt,
											   AIArtHandle *meshArt );

 	/** Retrieves the type of an envelope (warp, mesh, or object).
 			@param envelope	The envelope object.
 			@param type	[out] A buffer in which to return the envelope type constant.
 			@note Added in AI13. Previously, the type was not stored with the object.
 				For envelope objects created in earlier versions, returns
 				\c #kEnvelopeWarp for Envelope Warp and \c #kEnvelopeMesh for all
 				other types.
 		*/
 	AIAPI AIErr (*GetEnvelopeType) ( AIArtHandle envelope, AIEnvelopeType* type );
	
	/** Reshapes a path object.
 			@param inPath The path object.
 			@param param The t value for the curve from where the reshape is to be done.
			@param delta The delta value that has to be translated to the path object.
			@param shiftPressed If true, for straight line segments, the control handles are generated perpendicular to the segment.
				Otherwise, they are generated along the line segment.
 		*/
	AIAPI AIErr (*UnconstrainedReshapePath) ( const AIArtHandle inPath, const AIReal& param, const AIRealPoint& delta, bool shiftPressed );
	
	/** Retrieves the t value for a point on a bezier curve.
 			@param pathHandle The path object.
 			@param pointOnCurve The point for which the t value has to be found.
			@param segmentIndex The index of the path segment on which this point lies.
			@param param [out] The calculated t value for the point.
 		*/
	AIAPI AIErr (*GetParamFromPathHitPoint) ( const AIArtHandle pathHandle, AIRealPoint pointOnCurve, int segmentIndex, AIReal &param );
	
} AIEnvelopeSuite;

#include "AIHeaderEnd.h"

#endif