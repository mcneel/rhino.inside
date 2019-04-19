#ifndef __AIBeautifulStrokes__
#define __AIBeautifulStrokes__

/*
*        Date:	Started 2009
*     Purpose:	Adobe Illustrator Beautiful Strokes suite. This suite lets
*				clients control effects that can be applied to strokes such as
*				art and pattern brushes, arrowheads, and dash adjustments.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2009 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

#include "AITypes.h"
#include "AIEntry.h"
#include "AILiveEffect.h"
#include "AITabletData.h"
#include "AIPath.h"
#include "AIHeaderBegin.h"

/*******************************************************************************
**
** Types
**
**/

/**	Constants for \c #AIBeautifulStrokesSuite::SetArtPatternPaint() and
	/c #AIBeautifulStrokesSuite::GetArtPatternPaint() that determine how to
	apply art along a path.
*/
enum RepeatedArtAdjustment
{
	/// Stretch art to fit path
	kStretch,
	/// Add space between art to fit path
	kAddSpace,
	/// Adjust length of path to fit art
	kAdjustPath,

	/// Special return value to indicate mixed values when the params dict represents an
	/// accumulation of the values from multiple objects, such as returned by
	/// \c #AIPathStyleSuite::GetCurrentPathStyle().
	/// Passing this in as a value to "set" in a params dictionary means that the
	/// existing value, if any, should not change.
	kUnknownRepeatedArtAdjustment = 0xFFFFFFFF,

	/// Dummy value to ensure 32-bit enum value size.
	RepeatedArtAdjustment_dummy = 0xFFFFFFFF
};

enum RepeatedArtCorner {
	
	/// For not using an Auto Generated Corner
	kNoCorner,

	/// Creates a corner centered around the border/side tile
	kAutoCentered,

	/// Creates a corner by cutting the border/side tile into 2 halves.
	kAutoBetween,

	/// Creates a corner by slicing the border/side tile
	kAutoSliced,

	/// Creates a corner by overlapping the border/side tile
	kAutoOverlap
};

/**	Constants for \c #AIBeautifulStrokesSuite functions that set stroke widths.
	The first three values are used to set the stroke width source for an entire path or Beautiful Strokes dictionary.
	The "centered" values further specify the source of a requested width at a specific location on a path,
	as returned by \c #AIBeautifulStrokesSuite::GetWidthsAtDistance() and parallel functions.
*/
enum StrokeWidthSource
{
	/// Use a constant width derived from the \c #AIPathStyle stroke width setting.
	kConstantWidth,

	/// Use width from tablet data; set specific channel with \c #AIBeautifulStrokesSuite::SetWidthTabletDataSource().
	kTabletData,

	/// Use variable width from user-provided profile. See \c #AIBeautifulStrokesSuite::SetCenteredWidthProfile()
	/// and \c #AIBeautifulStrokesSuite::SetUncenteredWidthProfile().
	kUserProfile,

	/// Get width from this location on the path.
	kCenteredProfileMark = 0x0000FF01,
	/// Get width from this location on the path.
	kUncenteredProfileMark,
	/// Get width from this location on the path.
	kCenteredProfileInterpolation,
	/// Get width from this location on the path.
	kUncenteredProfileInterpolation,

	/// Special return value to indicate mixed values when the params dict represents an
	/// accumulation of the values from multiple objects, such as returned by \c #AIPathStyleSuite::GetCurrentPathStyle().
	/// Passing this in as a value to "set" in a params dictionary means that that the existing value, if any, should not change.
	kUnknownStrokeWidthSource = 0xFFFFFFFF,

	/// Dummy value to ensure 32-bit enum value size.
	StrokeWidthSource_dummy = 0xFFFFFFFF
};

enum GradientStrokeApplication
{
	/// Use the stroke to mask the gradient as if the stroke were outlined
	/// and filled (default).
	kGradientStrokeMask,

	/// Apply the gradient along the length of the stroke.
	kGradientStrokeAlong,

	/// Apply the gradient across the width of the stroke.
	kGradientStrokeAcross,

	/// Dummy value to ensure 32-bit enum value size.
	kGradientStroke_dummy = 0xFFFFFFFF
};

/**	Constants for \c #AIBeautifulStrokesSuite::SetArrowheadOptions()
	that determine how to position the arrows at the ends of the path.
*/
enum ArrowTipAlignment
{
	/// Put the tip of the arrow at the end of the path.
	/// The attachment point is placed on the path, and the path then cut at the truncation point.
	kArrowTipAtEnd,
	/// Put the attachment point of the arrow at the end of the path.
	/// The line between the attachment point and the tip is aligned with the path's tangent at that end.
	kArrowAttachmentPtAtEnd,
	/// Put the truncation point of the arrow at the end of the path.
	/// The line between the truncation point and the tip is aligned with the path's tangent at that end.
	kArrowTruncationPtAtEnd,

	/// Special return value to indicate mixed values when the params dict represents an
	/// accumulation of the values from multiple objects, such as returned by \c #AIPathStyleSuite::GetCurrentPathStyle().
	/// Passing this in as a value to "set" in a params dictionary means that the existing value, if any, should not change.
	kUnknownArrowAlignment = 0xFFFFFFFF
};


/// See \c #WidthMarkerFlagValues
typedef ai::uint32 WidthMarkerFlags;	// so that the compiler will allow doing bitwise operations

// Bit flags that modify and/or report information about width markers, other than their
// location (t value) and width.
enum WidthMarkerFlagValues
{
	/// No flags set.
	kNoWidthMarkerFlags = 0,

	// -------- Flags for describing marker types --------- //

	/**	The marker indicates the incoming width only, that is, it is the width for interpolating
		to the previous marker.  The next marker should be an outgoing width only, and is
		typically a different width value on at least one side of the stroke.
		If passed to a width-changing function, indicates that only the incoming width
		at that t value should be changed, with the outgoing width staying the same.
	*/
	kIncomingWidthMarker = 0x1,
	// 0x2 is reserved in case we decide to distinguish between left stroke side and right stroke side incoming widths

	/**	The marker indicates the outgoing width only, that is, it is the width for interpolating
		to the next marker.  The previous marker should be an incoming width only, and is
		typically a different width value. If passed to a width-changing function,
		indicates that only the outgoing width at that t value should be changed,
		with the incoming width staying the same.
	*/
	kOutgoingWidthMarker = 0x4,
	// 0x8 is reserved in case we decide to distinguish between left stroke side and right stroke side outgoing widths

	/**	The width at the indicated point forms a corner; that is, if the adjacent markers are
		at a different width, it starts interpolating linearly to the adjacent value, rather than
		spreading smoothly.
	*/
	kCornerWidthMarker = 0x10,
	/**	If the width is uncentered, set the corner vs smooth attribute separately
		for the left width.
	*/
	kCornerLeftWidthMarker = 0x10,
	/**	If the width is uncentered, set the corner vs smooth attribute separately
		for the right width.
	*/
	kCornerRightWidthMarker = 0x20,

	/**	The width marker at the indicated point prefers to be tied to a position on the path expressed
		as as an anchor point index, rather than being placed at the t value in the t values array.

		Width profiles can be shared by multiple paths, since they are part of art style definitions,
		and multiple paths can carry the same art style. So the actual profile contains only the
		flags that say which of the width marks should be shifted to the anchored places, if they
		exist on the path to which it is applied. The paths then in turn carry data that records
		which of the positions on the path want to have width markers anchored to them.

		For example, if there are three interior width markers in the profile that prefer to be tied to
		anchor points, and only one interior anchor point on a path to which that profile is applied,
		then not all the anchor requests can be honored.

		When a width profile contains anchored width marks, the t values are adjusted when the
		stroke is generated, so that the widths at those marks move to the anchor positions,
		and any unanchored width markers between them are shifted proportionally. (The first and
		last width mark in a profile are always anchored respectively to the start and end of the
		path, so this flag is ignored for those width marks.)

		Left and right widths must always be anchored together, as must incoming and outgoing width
		markers, since the left and right markers share the same tValues array and are always at the
		same offsets along the path.

	*/
	kAnchoredWidthMarker = 0x40,

	// (values from 0x80 to 0x8000 are reserved for future enhancements to saved options)

	// -------- Flags for describing options to functions that modify profiles --------- //

	/**	When passed to functions that take an art object and modify the width at a given t value,
		propagate the changes across multiple adjacent markers. Scope depends on selection state,
		and by default is bounded by corner points.  If not set, only the width at the given t value changes,
		and all other markers stay the same.<br>
		The way the changes propagate can be modified by setting \c #kUniformChangeAcrossSpread
		or \c #kProportionalChangeAcrossSpread. If both are off, the amount of change
		tapers down logarithmically with distance from the t value at which the
		change is specified, until it reaches 0 at the ends of the spread.
	*/
	kSpreadWidthChanges = 0x10000,

	/**	When passed to \c #AIBeautifulStrokesSuite::SlideWidthMarkerToNewT(), specifies
		that the marker should be duplicated and the new marker dragged while the old one is
		left behind.
	*/
	kCopyMarker = 0x20000,

	/**	When passed to \c #AIBeautifulStrokesSuite::SlideWidthMarkerToNewT(), specifies
		that markers are not allowed to move past adjacent ones.  Ignored if \c #kSpreadWidthChanges
		is also on.
	*/
	kLimitAtNeighbors = 0x40000,

	/**	Refines the meaning of \c #kSpreadWidthChanges; ignored if that flag is off.
		If on, the same offset is added or subtracted from all other markers in the affected
		spread, subject to remaining in the valid range.
	*/
	kUniformChangeAcrossSpread = 0x80000,

	/**	Refines the meaning of \c #kSpreadWidthChanges; ignored if that flag is off.
		If on, and \c #kUniformChangeAcrossSpread is off, other markers in the affected
		spread change by the same proportion that the one being directly modified does.
		For example, if the width at the directly modified t value is doubled, then all
		other widths in the affected spread are doubled.
	*/
	kProportionalChangeAcrossSpread = 0x100000

};

/// A logical OR of \c #WidthMarkerFlagValues. */
typedef ai::uint32 WidthMarkerFlags;

/** Callback for progress reports during a call to \c #AIBeautifulStrokeSuite::GenerateArt().
		@param current The current progress, a value between 0 and \c total. Always equal to 0 currently.
		@param total A value at which the operation is complete. Always equal to 1 currently.
		@return False if user cancels the operation, otherwise true. */
typedef AIAPI AIBoolean (*AIGenerateArtProgressProc)(ai::int32 current, ai::int32 total);

/**	Filled out by \c #AIBeautifulStrokesSuite::StrokeHitTest(), to report the results of a hit test
	on the focal stroke of a given path.
	<br>Note that when \c hitSomething is true, any combination of the other three hit results can hold.
	For example, if a width marker is hit, the target point may also be within the hit tolerance
	of the path centerline and/or within the hit tolerance of the stroke edge. Or on wide strokes,
	it might be inside a region of the stroke that is not near the path centerline, the stroke edge,
	nor any width point marker.
*/
struct StrokeHitResults
{
	/** True if any portion of the focal stroke was hit. */
	AIBoolean hitSomething;
	/** True if one of the width markers was hit anywhere along its extent. */
	AIBoolean hitWidthMarker;
	/** True if the target point was within the hit tolerance of the path centerline. */
	AIBoolean hitCenterline;
	/** True if the target point was within the hit tolerance of the stroke edge. */
	AIBoolean hitStrokeEdge;

	/**	If \c hitWidthMarker is true, the point on the path at which that width marker is positioned.
		Else if \c hitCenterline is true, the nearest point on the path, subject to anchor point snapping.<br>
		Else if within the stroked area, the first point on the path that would cause a width marker hit
		if a new width marker were to be inserted at that point.  Note that this is not necessarily
		the nearest point on the path; for example, the path may have a U-shaped curve in which the stroke
		is wide on one side and narrow on the other, so that the cursur is closer to the left centerline,
		but outside the left stroked area, while it is farther from the right centerline, but within the
		right stroked area.
	*/
	AIRealPoint pointOnPath;

	/**	If \c hitStrokeEdge is true, the point on the stroke edge closest to the cursor, possibly snapped
		to a marker end point. This is useful even if \c hitCenterline is also true, since the point on the
		centerline can be obtained from \c pointOnPath.<br>
		If \c hitStrokeEdge is false and \c hitCenterline is true, it is the same as \c pointOnPath.  <br>
		If \c hitStrokeEdge and \c hitCenterline are both false and \c hitWidthMarker is true, it is the closest
			point along the marker's extent to the mouse. <br>
		If \c hitSomething is true and \c hitStrokeEdge, \c hitCenterline and \c hitWidthMarker are all false (that is,
			if the cursor was within the stroked area but not within tolerance of any of the above), then it
			is the same as \c pointOnPath. <br>
		If \c hitSomething is false it is the original mouse position.
	*/
	AIRealPoint snappedPoint;

	/**	If \c hitSomething is true, the distance from the original mouse point to \c snappedPoint.
		If \c hitSomething is false, so that \c snappedPoint is the original mouse position, it is
		NOT zero, but a meaningless large number. */
	AIReal hitDistance;

	/** If \c hitWidthMark is true, the index of the width marker that was hit, otherwise 0. */
	ai::int16 widthMarkerIndex;

	/** The fraction of the path length from the beginning of the path to \c pointOnPath. */
	AIReal lengthFraction;
	/** The p0 index of the bezier segment that contains \c pointOnPath. */
	ai::int16 segIndex;
	/** The bezier t value within that segment of the \c pointOnPath. 0 for anchor point hits. */
	AIReal bezierT;
};


/** An overview of the kind of path edit being performed, included as part of a \c #PathEditDescription
*/
enum PathEditType
{
	/** Remove any width profile anchors from the path, but do not modify the art style */
	kClearProfileAnchorsOnly = 0,

	/** Remove any width profile anchors from the path, and apply a new art style in which
		the width profile distances have been reset to their values according to the current
		path distance. This is appropriate when a path is about to be edited in a way that
		keeps the path distances roughly the same proportionally, but changes the number
		of anchor points in a way that is too complex to attempt moving the anchors to new
		indexes, such as Offset Path or Simplify. See also \c kCopyAndResetAnchors, below.  */
	kClearAnchorsAndResetProfile,

	/** Transfer any profile anchors from the source path in the \c #PathEditDescription onto
		the art dictionary of the path, copying them exactly if the number of segments on
		the two paths are the same and they are either both open or both closed, otherwise
		resetting the profile anchors so that they maintain approximately the same fractional
		path distances, but are relative to the segment indices of the new path. This is an
		alternative to \c kClearAnchorsAndResetProfile, for situations where the destination path
		is a duplicate or a modified duplicate of the source path, especially useful for contexts
		where the path being modified is an input path to an effect under execution, and hence
		has been stripped of its paint. The art style of the path is not modified. */
	kCopyAndResetAnchors,

	/** A single anchor point (which may or may not be selected) is about to be moved.  */
	kTranslate1Anchor,

	/** A single anchor point (which may or may not be selected) is about to be removed,
		while preserving the path continuity (that is, the path is not split). */
	kRemove1Anchor,

	/** A single anchor point is about to be added.	*/
	kAdd1Anchor,

	/** A bezier segment is about to be adjusted, while leaving the bounding anchor points alone.  */
	kAdjustBezier,

	/** The selected components of the path are about to be transformed.
		It is not necessary to notify of this if the transformation preserves relative distances
		between anchor points, such as a rotation, translation, or uniform scale of a fully
		selected path. Should be notified if either the path is partially selected, or the
		transformation changes the relative lengths of bezier segments, such as a shear or
		non-uniform scale. */
	kTransformSelection,

	/** The anchor points of the path are about to be reversed.	 */
	kReversePathDirection,

	/** A new path has been constructed from a portion of another path (with, for instance, Delete,
		Copy, or Scissor on a partially selected path). For this type of edit, the path
		parameter to \c #AIBeautifulStrokesSuite::AdjustWidthAnchorsBeforePathEdit()
		should be the new path; the original path is passed as the source path in the
		\c #PathEditDescription.*/
	kSplitPath,

	/** A new art style is about to be applied to the path .*/
	kApplyStyle
};


/** The details of an edit description, passed as a parameter to \c #AIBeautifulStrokesSuite::AdjustWidthAnchorsBeforePathEdit()
*/
struct PathEditDescription
{
	PathEditType	editType;

	/**	For \c #kTranslate1Anchor or \c #kRemove1Anchor, the index of the anchor point being moved or removed.<br>
		For \c #kAdjustBezier, the index of the anchor point before the bezier segment being adjusted.	<br>
		For \c #kAdd1Anchor, the index of the new anchor point after insertion.	<br>
		For \c #kSplitPath, the index in the source path of the anchor point that was given index 0
			in the new path.<br>
			The index is allowed to be -1 if the new path was constructed by cutting
			the closing bezier segment of a closed path and copying anchor point 0 of the source
			path to anchor point 1 of the new path. You can find the number of anchor points copied
			by examining the new path. If the new path is longer than the number of anchor points
			remaining after this index in the source path, the code checks for wraparound, as would result
			from cutting open a closed path.
	*/
	ai::int16	segIndex;

	/**	For \c #kApplyStyle, the new art style that is about to be applied to the path.
		The message must be sent while the old art style is still on the path, so that
		the width profiles can be compared.
	*/
	AIArtStyleHandle newStyle;

	/** For \c #kAdd1Anchor, the coordinates and direction handles of the anchor point about to be added. */
	AIPathSegment newAnchor;

	/** For \c #kSplitPath or \c #kCopyAndResetAnchors, the original path that was used to as the source of anchor points for the new path. */
	AIArtHandle sourcePath;

};

/*******************************************************************************
**
** Constants
**
**/

#define kAIBeautifulStrokesSuite			"AI Beautiful Strokes Suite"
#define kAIBeautifulStrokesSuiteVersion3	AIAPI_VERSION(3)
#define kAIBeautifulStrokesSuiteVersion		kAIBeautifulStrokesSuiteVersion3
#define kAIBeautifulStrokesVersion			kAIBeautifulStrokesSuiteVersion

/**	@ingroup DictKeys
	Dictionary key for the Beautiful Strokes dictionary inside an \c #AILiveEffectParameters dictionary.
	See \c #AILiveEffectSuite.
*/
#define kAIBeautifulStrokesParamsDictKey "kAIBeautifulStrokesParamsDictKey"

/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
	This suite allows you to control advanced features for stroking paths. Setting are
	kept in a BeautifulStrokes params dictionary, which is contained in an \c #AILiveEffectParameters
	dictionary, such as one returned by \c #AIPathStyleSuite::GetCurrentPathStyle().  <br>
	One way to use this suite is to create a BeautifulStrokes params dictionary,
	add the stroke settings to the dictionary, then use that dictionary to apply
	the settings to source art. This generates new art in a destination group.
	For example:

	@code
	void Fn(AIArtHandle srcPath, AIArtHandle dstGroup)
	{
		AIDictionaryRef params = 0;
		sAIBeautifulStrokes->CreateParamsDict(NULL, params);
		sAIBeautifulStrokes->SetDashAdjustment(params, true);
		sAIBeautifulStrokes->GenerateArt(params, srcPath, NULL, TRUE, dstGroup, NULL);
		sAIDictionary->Release(params);
	}
	@endcode

	Counted object note: Suite functions that return counted object types such as
	\c #AIDictionarySuite::AIDictionaryRef and \c #AIArraySuite::AIArrayRef increment
	the reference count and the caller must release unneeded references to avoid memory
	leaks, as shown in the examples. Documentation for individual parameters mentions those
	that are reference counted and need to be released. See also \c #AICountedObjectSuite
	and the \c ai::Ref C++ class.

	The example above uses the \c #AIDictionarySuite::Release() directly.
	The following example uses the \c ai::Ref C++ class to manage the counted
	object. (Note that \c #AICountedObjectSuite::Release() is equivalent to
	\c #AIDictionarySuite::Release()):

	@code
	void Fn_Ref(AILiveEffectParameters effectParams)
	{
		ai::Ref<AIDictionaryRef> params;
		sAIBeautifulStrokes->CreateParamsDict(NULL, *(params << ai::Replace));
		sAIBeautifulStrokes->SetDashAdjustment(params, true);
		sAIBeautifulStrokes->GenerateArt(params, srcPath, NULL, TRUE, dstGroup, NULL);
	}
	@endcode

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
	\c #kAIBeautifulStrokesSuite and \c #kAIBeautifulStrokesVersion.

*/

struct AIBeautifulStrokesSuite
{

	// General parameter management and stroke generation

	/**	Applies settings in a BeautifulStrokes parameters dictionary to the focal stroke on source art
		to generate new stroked art in the output group.

		@param effectParams		An effect parameters dictionary that contains a BeautifulStrokes params
								dictionary in which BeautifulStrokes settings are defined. This can also
								be a BeautifulStrokes params dictionary.
		@param inArt			The art (path) to which the parameters are to be applied.
		@param sourceArt		[optional] The non-styled art (path) possibly containing width anchors that can be
								used to adjust the width profile placement. (See \c #AIBeautifulStrokesSuite::GetPathAdjustedWidthDistances().)
								This parameter is ignored if inArt is not styled art (see \c #AIArtSuite::IsArtStyledArt()),
								since non-styled art will carry its own anchors. But art dictionaries are stripped
								from the input art to live effects. Thus, if \c inArt is the input art to a live effect
								execution for a stroke filter, and the art style being executed was attached to a path,
								then passing \c sourceArt as the non-styled path art object to which that art style was
								attached will allow access to the width anchors. (If there are no vector pre-effects
								before the stroke filter, then \c inArt will generally be a duplicate of \c sourceArt,
								but if there are vector pre-effects, then it may be substantially different.)
								Passing this parameter as null when inArt is styled art will cause any width profile
								in the effectParams to be applied without width anchor adjustment.
		@param outputOnTop		True to place the output art into the output group on top, false to place
								it inside the output group on the bottom.
		@param outGroup			The destination group for the generated output art.
		@param outArt			[optional] A pointer to an AIArtHandle in which to return the AIArtHandle for the generated output art.
		@param progressProc		A callback procedure for displaying a progress bar during
								computation (from which the user can cancel the operation)
								or \c nullptr to show no progress bar.
	*/
	AIAPI AIErr (*GenerateArt)(ConstAILiveEffectParameters effectParams, AIArtHandle inArt, AIArtHandle sourceArt,
							   AIBoolean outputOnTop, AIArtHandle outGroup, AIArtHandle *outArt, AIGenerateArtProgressProc progressProc);

	/**	Creates a new BeautifulStrokes params dictionary. You must release the dictionary when no longer needed using
		\c #AIDictionarySuite::Release().

		@param effectParams		[optional] A set of LiveEffect parameters. If supplied, the new BeautifulStrokes
								params dictionary is added to this dictionary, or, if a BeautifulStrokes dictionary
								already exists, \c params is set to this existing dictionary.
		@param params			A reference to a new or the existing BeautifulStrokes params dictionary.
								The reference count on this dictionary is incremented on return and
								must be released when no longer needed.

	*/
	AIAPI AIErr (*CreateParamsDict)(AILiveEffectParameters effectParams, AIDictionaryRef &params);

	/**	Retrieves a BeautifulStrokes parameters dictionary from a set of LiveEffect parameters.

		@param effectParams		A set of LiveEffect parameters for an art object.
		@param params			A reference to the BeautifulStrokes params dictionary or
								NULL if one does not exist. The reference count on this
								dictionary is incremented on return and must be released
								when no longer needed.

		@return					No error is returned if the dictionary does not exist.
	*/
	AIAPI AIErr (*GetParamsDict)(ConstAILiveEffectParameters effectParams, AIDictionaryRef &params);

	/**	Reports whether two parameters dictionaries are equivalent.

		@param params1			The first dictionary.
		@param params2			The second dictionary.
		@return					True if equivalent.
	*/
	AIAPI AIBoolean (*Equiv)(ConstAIDictionaryRef params1, ConstAIDictionaryRef params2);

	/**	Accumulates common parameters in a dictionary to be used later with \c #ApplyParams().
		Call repeatedly with different parameter sets to collect the combined BeautifulStrokes
		attributes of multiple objects (or multiple art styles). You can use this to collect
		common attributes of objects that are not necessarily selected, or to ignore some of
		the selected objects, such as finding the combined BeautifulStrokes attributes of
		all the objects on a layer, whether they are selected or not.

		@param effectParams		A set of LiveEffect parameters containing a Beautiful Strokes params dictionary.
		@param accumulator		Common parameters being accumulated.
	*/
	AIAPI AIErr (*AccumulateParams)(ConstAILiveEffectParameters effectParams, AIDictionaryRef accumulator);

	/**	Applies a set of parameters from one dictionary to another.	For keys that exist in both dictionaries,
		the value from the source overwrites the value in the destination.

		@param params	The source dictionary containing a set of parameters to be applied.
						Typically obtained from \c #AIPathStyleSuite::GetCurrentPathStyle(), from an art object or art style.
						If an accumulated dictionary is passed as the source, values that vary (were mixed in the selection)
						do not change value in the target dictionary. This is consistent with the behavior of
						\c #AIPathStyleSuite::SetCurrentPathStyle(). See also \c #AccumulateParams().
		@param target	The target dictionary.
	*/
	AIAPI AIErr (*ApplyParams)(ConstAIDictionaryRef params, AIDictionaryRef target);

	/**	Reports whether a dictionary contains meaningful Beautiful Strokes parameters.
		(Note that this function returns a Boolean value, not an error code.)
		Call on an accumulator to check whether it contains any BeautifulStrokes parameters;
		if not, it can be freed or ignored.  See \c #AccumulateParams().
		Both a used accumulator and a new dictionary contain some bookkeeping entries, so you cannot just
		check for the dictionary being empty of all keys. A new dictionary just created by
		\c #CreateParamsDict() returns false to this call. <br>

		This does not recurse into sub-dictionaries. To test for nested dictionaries,
		call \c #GetParamsDict(), and if it is non-null check the contained dictionary.

		@param paramsDict	Dictionary to be examined.
		@return				True if the dictionary contains Beautiful Strokes parameters.
	*/
	AIAPI AIBoolean (*ContainsParams)(ConstAIDictionaryRef paramsDict);

	/**	Retrieves the BeautifulStrokes params dictionary, if any, associated with the focal stroke of an art object. Optionally
		retrieves the stroke style and other information about the stroke attributes.

		@param art			The art object.
		@param paramDict	[out] A reference in which to return the BeautifulStrokes params dictionary, or null if none.
							The reference count on this dictionary is incremented on return and must be released when
							no longer needed.
		@param strokeStyle	[out][optional] A buffer in which to return the focal stroke style from the paint attributes.
		@param hasBrush		[out][optional] A buffer in which to return true if the focal stroke carries a brush effect.
		@param scaleFactor	[out][optional] A buffer in which to return the combined scale factor that incorporates:
							the object scale factor reported by \c #AIArtStyleSuite::GetArtStyleScaleFactor(),
							the width of the art design on art brushes or the side tile on pattern brushes,
							and the scale factor from the brush options for brushes. <br>
							Multiplying these widths by this factor gives the width that the stroke edges
							preview at, assuming that any brush art fills the brush tile boundaries.<br>
							(Does not include the stroke weight or the width returned by \c #GetWidthsAtDistance(), and so on.)
		@param canAccept	[out][optional] A buffer in which to return true if the art object has a style that can accept
							BeautifulStrokes parameters.
							(For CS5, it has a stroke, and the focal stroke is not a Calligraphic or Scatter brush, and is
							not inside/outside aligned.)
	*/
	AIAPI AIErr (*GetArtStrokeParams)(AIArtHandle art, AIDictionaryRef &paramDict,
									  AIStrokeStyle *strokeStyle, AIBoolean *hasBrush,
									  AIReal *scaleFactor, AIBoolean *canAccept);

	/**	Interpolates beautiful stroke parameters between two appearances.

		@param effectParams1	[optional] The effects parameters dictionary of a stroke filter,
								which may (or may not) contain a Beautiful Strokes params dictionary.
		@param effectParams2	[optional] The effects parameters dictionary of a stroke filter
								which may (or may not) contain a Beautiful Strokes params dictionary.
		@param effectParamsOut	The effects parameters dictionary of a stroke filter that represents the results
								of interpolating between effectParams1 and effectParams2.
		@param dist				A number in the range [0-1], where 0 is interpreted as matching effectParams1,
								and 1 is interpreted as matching effectParams2. (Negative values are interpreted
								as if they were 0, and values greater than 1 as if they were 1.)

		If either effectParams1 or effectParams2 contains a Beautiful Strokes parameter dictionary, then those parameters
		will be interpolated, and the results placed in effectParamsOut (which should not be null if either input parameter
		is null.)
	*/
	AIAPI AIErr (*InterpolateParams)(ConstAILiveEffectParameters effectParams1, ConstAILiveEffectParameters effectParams2,
									 AILiveEffectParameters effectParamsOut, AIReal dist);

	// General brush settings

	/**	Sets the option in a Beautiful Strokes dictionary to flip art across path to reverse vertical orientation.

		@param params		The parameters dictionary.
		@param flipAcross	True to set the option, false to clear it.
	*/
	AIAPI AIErr (*SetFlipAcross)(AIDictionaryRef params, AIBoolean flipAcross);

	/**	Retrieves the option from a Beautiful Strokes dictionary to flip art across path to reverse vertical orientation.
		Note that this function returns a Boolean value, not an error code.

		@param params		The parameters dictionary.
		@return				True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetFlipAcross)(ConstAIDictionaryRef params);

	/**	Sets the option in a Beautiful Strokes dictionary to flip art along path to reverse lateral orientation.

		@param params		The parameters dictionary.
		@param flipAlong	True to set the option, false to clear it.
	*/
	AIAPI AIErr (*SetFlipAlong)(AIDictionaryRef params, AIBoolean flipAlong);

	/**	Retrieves the option from a Beautiful Strokes dictionary to flip art along path to reverse lateral orientation.
		Note that this function returns a Boolean value, not an error code.

		@param params		The parameters dictionary.
		@return				True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetFlipAlong)(ConstAIDictionaryRef params);

	/**	Sets the scale (width) of art applied to path in a Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param scale	Single scale for art not using tablet data.
		@param mnScale	[optional] Minimum scale for art using tablet data.
		@param mxScale	[optional] Maximum scale for art using tablet data.
	*/
	AIAPI AIErr (*SetScale)(AIDictionaryRef params, AIReal scale, const AIReal *mnScale, const AIReal *mxScale);

	/**	Retrieves the scale (width) of art applied to path from a Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param scale	[out] A reference in which to return the single scale for art not using tablet data.
		@param mnScale	[optional] [out] A buffer in which to return the minimum scale for art using tablet data.
		@param mxScale	[optional] [out] A buffer in which to return the maximum scale for art using tablet data.
	*/
	AIAPI AIErr (*GetScale)(ConstAIDictionaryRef params, AIReal &scale, AIReal *mnScale, AIReal *mxScale);

	/**	Set fold adjustment on or off. This adjusts the brush folding across corners or bends.
	*/
	AIAPI AIErr (*SetFoldAdjustment)(AIDictionaryRef params, AIBoolean adjust);

	/**	Retrieves the fold adjustment status from a Beautiful Strokes dictionary.
		This adjusts the folding across corners or bends.
		Note that this function returns a Boolean value, not an error code.

		@param params	The parameters dictionary.
		@param mixed	[optional] [out] A buffer in which to return true if the dictionary represents an accumulation
						returned from \c #AIPathStyleSuite::GetCurrentPathStyle(), and the selection is mixed.
						By convention, mixed values return false.
		@return			True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetFoldAdjustment)(ConstAIDictionaryRef params, AIBoolean *mixed);

	// Art Brushes

	/**	Sets the pattern to be applied along path in a Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param art		The brush pattern.
	*/
	AIAPI AIErr (*SetArtPaint)(AIDictionaryRef params, AIPatternHandle art);

	/**	Retrieves the pattern to be applied along path from a Beautiful Strokes dictionary.
		Note that this function returns an object, not an error code.

		@param params	The parameters dictionary.
		@return			The brush pattern.
	*/
	AIAPI AIPatternHandle (*GetArtPaint)(ConstAIDictionaryRef params);

	/**	Sets the stretching option in a Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param stretch	True to stretch tiles non-uniformly along the path, false to scale
						up uniformly for the path length.
	*/
	AIAPI AIErr (*SetStretch)(AIDictionaryRef params, AIBoolean stretch);

	/**	Retrieves the stretching option from a Beautiful Strokes dictionary.
		Note that this function returns a Boolean value, not an error code.

		@param params	The parameters dictionary.
		@return			True if the option is set (stretch tiles non-uniformly along the path),
						false if it is clear (scale up uniformly for the path length).
	*/
	AIAPI AIBoolean (*GetStretch)(ConstAIDictionaryRef params);

	/**	Sets the lengths of non-stretching start and end segments for a segmented brush	in a Beautiful Strokes dictionary.
		Lengths are expressed as absolute values in document points. If both values are zero, the brush is a non-segmented brush.

		@param params				The parameters dictionary.
		@param startSegmentLength	Length of start segment.
		@param endSegmentLength		Length of end segment.
	*/
	AIAPI AIErr (*SetStartEndSegmentLength)(AIDictionaryRef params, AIReal startSegmentLength, AIReal endSegmentLength);

	/**	Retrieves the lengths of non-stretching start and end segments for a segmented brush from a Beautiful Strokes dictionary.
		Lengths are expressed as absolute values in document points.

		@param params				The parameters dictionary.
		@param startSegmentLength	[out] A reference in which to return the start-segment length.
		@param endSegmentLength		[out] A reference in which to return the end-segment length.
	*/
	AIAPI AIErr (*GetStartEndSegmentLength)(ConstAIDictionaryRef params, AIReal &startSegmentLength, AIReal &endSegmentLength);

	// Pattern Brushes

	/**	Sets options for repeating pattern tiles along a path in a Beautiful Strokes dictionary.

		@param params						The parameters dictionary.
		@param	beginArt					Brush pattern tile art to be applied to the beginning of the path. May be NULL.
		@param	endArt						Brush pattern tile art to be applied to the end of the path. May be NULL.
		@param	sideArt						Brush pattern tile art to be applied to the main part of the path.  May be NULL.
		@param	insideCornerArt				Brush pattern tile art to be applied to inside corners of the path.  May be NULL.
		@param	outsideCornerArt			Brush pattern tile art to be applied to outside corners of the path.  May be NULL.
		@param	adjustment					Method to use to apply art along path; see \c #RepeatedArtAdjustment().
		@param	spacing						Relative spacing between tiles; for example, 0.5 sets spacing to half
											the width of the tile. Relevant only when adjustment method is \c #kAddSpace.
		@param	insideAutoCornerOption		Method to use to generate insideCornerArt automatically; see \c #RepeatedArtCorner().
		@param	outsideAutoCornerOption		Method to use to generate outsideCornerArt automatically; see \c #RepeatedArtCorner().
	*/
	AIAPI AIErr (*SetArtPatternPaint)(AIDictionaryRef params, AIPatternHandle beginArt, AIPatternHandle endArt,
									  AIPatternHandle sideArt,
									  AIPatternHandle insideCornerArt, AIPatternHandle outsideCornerArt,
									  RepeatedArtAdjustment adjustment, AIReal spacing,
									  RepeatedArtCorner insideAutoCornerOption, RepeatedArtCorner outsideAutoCornerOption);

	/**	Retrieves options for repeating pattern tiles along a path from a Beautiful Strokes dictionary.

		@param params					The parameters dictionary.
		@param beginArt					[out] A reference in which to return the brush pattern tile art to be
										applied to the beginning of the path. May be NULL.
		@param endArt					[out] A reference in which to return the brush pattern tile art to be
										applied to the end of the path. May be NULL.
		@param sideArt					[out] A reference in which to return the brush pattern tile art to be
										applied to the main part of the path.  May be NULL.
		@param insideCornerArt			[out] A reference in which to return the brush pattern tile art
										to be applied to inside corners of the path.  May be NULL.
		@param outsideCornerArt			[out] A reference in which to return the brush pattern tile art
										to be applied to outside corners of the path.  May be NULL.
		@param adjustment				[out] A reference in which to return the method to use to apply art along path;
										see \c #RepeatedArtAdjustment().
		@param spacing					[out] A reference in which to return the relative spacing between tiles.
										For example, 0.5 sets spacing to half the width of the tile.
										Relevant only when adjustment method is \c #kAddSpace.
		@param insideAutoCornerOption	[out] A reference in which to return the type of Automatically Generated Corner 
										to be used for Inside Corner.
										see \c #RepeatedArtCorner().
		@param outsideAutoCornerOption	[out] A reference in which to return the type of Automatically Generated Corner
										to be used for Outside Corner.
										see \c #RepeatedArtCorner().
	*/
	AIAPI AIErr (*GetArtPatternPaint)(ConstAIDictionaryRef params, AIPatternHandle &beginArt, AIPatternHandle &endArt,
									  AIPatternHandle &sideArt,
									  AIPatternHandle &insideCornerArt, AIPatternHandle &outsideCornerArt,
									  RepeatedArtAdjustment &adjustment, AIReal &spacing,
									  RepeatedArtCorner &insideAutoCornerOption, RepeatedArtCorner &outsideAutoCornerOption);

	// Dashing

	/**	Sets or clears the dash adjustment option in a Beautiful Strokes dictionary.
		When on, adjusts dashes so a certain fraction of the dash length always appears
		at the ends, corners, and intersections of dashed lines.
		(Note that dash/gap intervals are obtained from the art.)

		@param params	The parameters dictionary.
		@param adjust	True to set the option, false to clear it.
	*/
	AIAPI AIErr (*SetDashAdjustment)(AIDictionaryRef params, AIBoolean adjust);

	/**	Retrieves the dash adjustment status from a Beautiful Strokes dictionary.
		See \c #SetDashAdjustment().
		(Note that this function returns a Boolean value, not an error code.)

		@param params	The parameters dictionary.
		@param mixed	[optional] [out] A buffer in which to return true if the dictionary represents an accumulation
						returned from \c #AIPathStyleSuite::GetCurrentPathStyle(), and the selection is mixed.
						By convention, mixed values return false.
		@return			True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetDashAdjustment)(ConstAIDictionaryRef params, AIBoolean *mixed);

	// Gradient Stroke

	/** Sets the gradient stroke application method. This determines how the
		current stroke color, if a gradient, will be applied to the stroke.
		Not applicable to some objects such as art brushes, etc.

		@param params	The parameters dictionary.
		@param type			The type of gradient stroke application. Pass kGradientStroke_dummy
						to clear the corresponding dictionary entry.
	*/
	AIAPI AIErr (*SetGradientStrokeApplication)(AIDictionaryRef params, GradientStrokeApplication application);

	/** Retrieves the gradient stroke application method status from a
		Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param type			The type of gradient stroke	application.
		@param mixed	[optional] [out] A buffer in which to return true if the dictionary represents an accumulation
						returned from \c #AIPathStyleSuite::GetCurrentPathStyle(), and the selection is mixed.
						By convention, mixed values return false.
	*/
	AIAPI AIErr (*GetGradientStrokeApplication)(ConstAIDictionaryRef params, GradientStrokeApplication &application, AIBoolean *mixed);

	// Arrowheads

	/**	Sets arrowhead-related stroke options in a Beautiful Strokes dictionary.
		The arrowhead symbols can be in a library rather than the current document. If so, they are retargeted to the
		document that the params dictionary is attached to, and placed in the "hidden symbols" of that document;
		that is, they do not appear in the Symbols panel. The symbols are parsed to determine the alignment
		parameters and the default scale.

		Any unpainted closed rectangle in the back of the symbol definition is ignored and stripped from
		the art that is used to determine the "tip" of the arrow and placed on the path. These unpainted
		rectangles are assumed to be only for the purpose of making the symbol thumbnails a uniform size.

		Arrowhead art inside the symbol is assumed to be positioned the way it would be when applied as an
		end arrow to a horizontal open path that started at the left and ended at the right.
		If applied as a start arrow, it is reflected horizontally before it is applied.

		If there is a stroked open straight line in the back of the symbol definition (either above or below
		the bounding rectangle if there is one), then the right endpoint of that line is used to specify the
		truncation point. If it additionally has an internal anchor point, the furthest right such anchor point
		is used to specify the attachment point, otherwise the attachment point is the same as the truncation point.

		The tip is treated as the point along the right edge of the bounding box (after removing the bounding tile,
		if any) which is at the same height as the positioning line. The stroke weight of the positioning line
		is used to determine the default scale of the arrowhead. For example, if the positioning stroke is 2 pts, then
		the arrowhead is scaled 50% when it is applied to a path with a 1 pt stroke, and scaled 150% when it
		is applied to a path with a 3 pt stroke. The begin-scale or end-scale factors are applied additionally.

		If there is no positioning line, the default is to use a 100% default scale; that is, to treat the symbol
		as if it were scaled appropriately for a 1 pt line, and to put both the attachment and truncation points
		in the center of the symbol.

		@param params			The parameters dictionary.
		@param beginSymbol		A pointer to the symbol to apply as the arrowhead at the beginning of the path.
								To not change the existing settings, pass null. To remove the arrowhead,
								pass a pointer to null.
		@param endSymbol		The symbol to apply as the arrowhead at the end of the path, null if none
								To not change the existing settings, pass null. To remove the arrowhead,
								pass a pointer to null.
		@param beginScale		The factor by which to scale the begin arrow by, as a percentage relative
								to the default scale. To not change the existing settings, pass \c #kAIRealUnknown.
		@param endScale			The factor by which to scale the end arrow by, as a percentage relative
								to the default scale. To not change the existing settings, pass \c #kAIRealUnknown.
		@param alignment		The rule for positioning the arrows at the ends of the path.
								To not change the existing settings, pass \c #kUnknownArrowAlignment.
	*/
	AIAPI AIErr (*SetArrowheadOptions)(AIDictionaryRef params, AIPatternHandle *beginSymbol, AIPatternHandle *endSymbol,
									   AIReal beginScale, AIReal endScale, ArrowTipAlignment alignment);

	/**	Retrieves arrowhead-related stroke options from a Beautiful Strokes dictionary.
		All pointer arguments are optional and may be null if those options are not being queried.

		@param params			The parameters dictionary to be searched. May be an accumulation of multiple paths, if
								returned from \c #AIPathStyleSuite::GetCurrentPathStyle().
		@param beginSymbol		[out] A buffer in which to return the symbol used as the arrowhead at the beginning of the path, null if none.
		@param endSymbol		[out] A buffer in which to return the symbol used as the arrowhead at the end of the path, null if none.
		@param beginScale		[out] A buffer in which to return the factor to uniformly scale the begin arrow by, as a percentage relative to the default scale.
								Returns \c #kAIRealUnknown if the params dict represents an accumulation with mixed values.
		@param endScale			[out] A buffer in which to return the factor to scale the end arrow by, as a percentage relative to the default scale
								Returns \c #kAIRealUnknown if the params dict represents an accumulation with mixed values.
		@param alignment		[out] A buffer in which to return the rule for positioning the arrows at the ends of the path. Must be the same for both ends.
								Returns \c #kUnknownArrowAlignment if the params dict represents an accumulation
								and the selection is mixed (including if some paths have no arrowheads).
		@param mixedBeginArrows	[out] A buffer in which to return true if there are different choices for the begin-symbol in a mixed selection
								(including if some paths have no begin arrow and some do.)
		@param mixedEndArrows	[out] A buffer in which to return true if there are different choices for the end-symbol in a mixed selection
								(including if some paths have no begin arrow and some do.)
	*/
	AIAPI AIErr (*GetArrowheadOptions)(ConstAIDictionaryRef params, AIPatternHandle *beginSymbol, AIPatternHandle *endSymbol,
									   AIReal *beginScale, AIReal *endScale, ArrowTipAlignment *alignment,
									   AIBoolean *mixedBeginArrows, AIBoolean *mixedEndArrows);

	// Variable Widths

	/**	Sets the source of stroke width in a Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param source	Source of width information for stroke. If \c #kTabletData, set related values
						with \c #SetWidthTabletDataSource() and \c and #SetScale(), particularly minimum and maximum. <br>
						If \c #kUserProfile, call \c #SetCenteredWidthProfile() to set centered width values or
						\c #SetUncenteredWidthProfile() to set independent left and right width values.
	*/
	AIAPI AIErr (*SetWidthSource)(AIDictionaryRef params, StrokeWidthSource source);

	/**	Retrieves the source of stroke width from a Beautiful Strokes dictionary.
		(Note that this function returns a constant value, not an error code.)

		@param params	The parameters dictionary.
		@return			The width source constant.
	*/
	AIAPI StrokeWidthSource (*GetWidthSource)(ConstAIDictionaryRef params);

	/**	Sets the type of tablet data to use for stroke width in the art passed to \c #GenerateArt(),
		in a Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param dataType	The type of tablet data.
						@see \c #AITabletDataType
	*/
	AIAPI AIErr (*SetWidthTabletDataSource)(AIDictionaryRef params, AITabletDataType dataType);

	/**	Retrieves the tablet-data type option from a Beautiful Strokes dictionary.

		@param params	The parameters dictionary.
		@param dataType	The type of tablet data to use for stroke width in the art passed to \c #GenerateArt().
						@see \c #AITabletDataType
	*/
	AIAPI AIErr (*GetWidthTabletDataSource)(ConstAIDictionaryRef params, AITabletDataType &dataType);

	/**	Sets centered width profile for output art in a Beautiful Strokes dictionary. Pass NULL for both arrays to clear the profile.
		A style cannot carry both an uncentered and centered width profile, so if there is an existing
		centered width profile, this function removes it.

		Other than length, the array values are not examined for validity at the time they are set.
		Instead, they are examined when used, and any invalid entries are ignored.
		A width profile in which all the array entries are used to form the stroke contour
		has the following properties:
			<ul><li>The first distance is 0 </li>
			<li>The last distance is 1</li>
			<li>Every distance value should be no less than the previous distance, and no more than the next one</li>
			<li>There should be no more than two consecutive distance values at the same distance </li></ul>
		When interpreting the width profile:
			<ul><li>If the first distance value is not zero, the function acts as if there was an additional value
			at the beginning of both arrays, with the distance being zero and the width being whatever
			the width is in the first entry in the widths array. </li>
			<li>If any distance value is more than 1, or less than the preceding distance value, or equal
			to both the preceding distance value and the following distance value, the function ignores
			the array entries at that index</li>
			<li>If the last distance value is not 1, the function acts as if there were an additional pair of
			entries with the distance equal to 1, and the width equal to the width at the last valid
			distance entry </li>
		    <li>Negative values are interpreted as if they were 0. Values greater than 1 are allowed, but cause
		    the stroke to be wider at those places than the width shown in the Stroke panel, so should be avoided.

			Note that this differs from the interpretation of widths in the functions such	as \c #SetCenteredWidthAtDistance()
			that take a path object and query or modify the width at specific offsets; these incorporate the stroke weight scaling.
			This is because the functions that manage entire width arrays may be dealing with profiles that are shared across multiple
			paths of different weights or belong to unattached preset dictionaries.</li> </ul>

		@param params	The parameters dictionary.
		@param tVals	An array of \c AIReal values ranging from [0-1] representing fractional distances
						along the path.
		@param widths	An array of \c AIReal values the same size as \c tVals representing the fractional stroke width
						at the corresponding offset in the \c tVals array. Values are fractions of the stroke weight
						as shown in the Stroke panel, in the range [0-1].
		@return The error \c #kBadParameterErr if the arrays are of different lengths, or if one is null and the other is not.
	*/
	AIAPI AIErr (*SetCenteredWidthProfile)(AIDictionaryRef params, AIArrayRef tVals, AIArrayRef widths);

	/**	Retrieves the centered width profile for output art from a Beautiful Strokes dictionary.

		@param params		The parameters dictionary.
		@param distances	A reference in which to return an array of \c AIReal values ranging from [0-1] representing fractional distances
							along the path.
		@param widths		A reference in which to return an array of \c AIReal values the same size as \c tVals representing the fractional stroke width
							at the corresponding offset in the \c tVals array.
	*/
	AIAPI AIErr (*GetCenteredWidthProfile)(ConstAIDictionaryRef params, AIArrayRef &distances, AIArrayRef &widths);

	/**	Sets an uncentered width profile for output art in a Beautiful Strokes dictionary, with independent
		left and right width values. Left and right are interpreted by following the path
		from the start point to the end point.
		A path cannot carry both an uncentered and centered width profile, so if there is an existing
		centered width profile, this function removes it.

		@param params		The parameters dictionary.
		@param tVals		An array of \c AIReal values ranging from [0-1] representing fractional distances
							along the path.
		@param leftWidths	An array of \c AIReal the same size as \c tVals representing the width of the left side
							of the stroke at corresponding distances in \c tVals.
		@param rightWidths	An array of \c AIReal the same size as \c tVals representing the width of the right side
							of the stroke at corresponding distances in \c tVals.
	*/
	AIAPI AIErr (*SetUncenteredWidthProfile)(AIDictionaryRef params, AIArrayRef tVals, AIArrayRef leftWidths, AIArrayRef rightWidths);

	/**	Retrieves the uncentered width profile for output art from a Beautiful Strokes dictionary.

		@param params		The parameters dictionary.
		@param tVals		A reference in which to return an array of \c AIReal values ranging from [0-1] representing fractional distances
							along the path.
							The reference count on this array is incremented on return and must be released when no longer needed.
		@param leftWidths	A reference in which to return an array of \c AIReal the same size as \c tVals representing the width of the left side
							of the stroke at corresponding distances in \c tVals.
							The reference count on this array is incremented on return and must be released when no longer needed.
		@param rightWidths	A reference in which to return an array of \c AIReal the same size as \c tVals representing the width of the right side
							of the stroke at corresponding distances in \c tVals.
							The reference count on this array is incremented on return and must be released when no longer needed.
	*/
	AIAPI AIErr (*GetUncenteredWidthProfile)(ConstAIDictionaryRef params, AIArrayRef &tVals, AIArrayRef &leftWidths, AIArrayRef &rightWidths);

	/**	INTENDED FOR FUTURE ENHANCEMENTS - All non-default options are currently ignored.
		Can only be called after setting the width profile with \c #SetCenteredWidthProfile() or \c #SetUncenteredWidthProfile().
		If not present (the usual case), all width markers use default options, which are dependent upon the context. All arrays can be null.
		The defaults are for markers that are concurrent with corner anchor points of the path to be treated as
		tethered corner width markers, and for all other markers to be untethered smooth markers, with the
		default smoothness values.

		To save space, there is a single array of marker options for both centered and uncentered width profiles,
		with different flag values to distinguish when the options are different for the left and right sides
		of the stroke (for example, if it is smooth on the left side but cornered on the right.)
		If an incoming smoothness array exists but the outgoing smoothness array does not exist on that side
		of the path, then the outgoing smoothness is inherited from the incoming smoothness.
		Similarly, if the left smoothness array(s) exist but the right smoothness arrays do not, then
		the right smoothness is inherited from the left smoothness.

		You must only call this function AFTER either \c #SetCenteredWidthProfile() or \c #SetUncenteredWidthProfile();
		it returns /c #kBadParameterErr if any of the arrays are non-null and either there is no width profile,
		or the existing width profile has a different number of markers than the size of the detail arrays.
		No validation is done on the contents of the arrays, other than their lengths.

		@param params					The parameters dictionary.
		@param markerOptions			An array of integers parallel to the t values, interpreted as a bit vector
										of WidthMarkerFlagValues
		@param incomingLeftSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@param outgoingLeftSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@param incomingRightSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@param outgoingRightSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@return							The error \c #kBadParameterErr if any of the arrays are non-null
										and either there is no width profile, or the existing width profile
										has a different number of markers than the size of the detail arrays.
	*/
	AIAPI AIErr (*SetWidthProfileDetails)(AIDictionaryRef params, AIArrayRef markerOptions,
										  AIArrayRef incomingLeftSmoothness, AIArrayRef outgoingLeftSmoothness,
										  AIArrayRef incomingRightSmoothness, AIArrayRef outgoingRightSmoothness);

	/**	Retrieves the options for the width profile markers from a Beautiful Strokes dictionary.

		@param params					The parameters dictionary.
		@param markerOptions			A reference in which to return an array of integers parallel to the t values, interpreted as a bit vector of \c #WidthMarkerFlagValues.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param incomingLeftSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param outgoingLeftSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param incomingRightSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param outgoingRightSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
	*/
	AIAPI AIErr (*GetWidthProfileDetails)(ConstAIDictionaryRef params, AIArrayRef &markerOptions,
										  AIArrayRef &incomingLeftSmoothness, AIArrayRef &outgoingLeftSmoothness,
										  AIArrayRef &incomingRightSmoothness, AIArrayRef &outgoingRightSmoothness);

	/**	If a path has variable widths (either centered or uncentered), retrieves a vector of the values
		from the distance array, after adjustment to shift any anchored width points to the relative
		distance along that path of the path positions they are anchored to.
		<ul><li>If the path has no variable widths, the returned vector is empty.</li>
		<li>If the path has variable widths but no width profile anchors, the returned vector contains
		the same distance values that are in the distance array returned
		by \c #GetCenteredWidthProfile() or \c #GetUncenteredWidthProfile().</li></ul>

		@param path					The path.
		@param adjustedDistances	A reference in which to return the result vector. The reference
									count on this array is incremented on return and must be released
									when no longer needed.
	*/
	AIAPI AIErr (*GetPathAdjustedWidthDistances)(AIArtHandle path, AIArrayRef &adjustedDistances);

	/**	Retrieves the left, right, and combined widths of the focal stroke at a fraction of the distance along a path,
		and reports the source of the widths.
		The widths are analogous to the stroke weights as returned by the \c #AIArtStyleSuite::GetPaintAttributes().
		As such, they include the stroke weight scaling, but do not include the impact of pattern or art brush
		scale options or pattern or art brush tile sizes.

		@param path				[in] The path to be examined for width data.
		@param lengthFraction	[in/out] Upon input, the fraction of the path length at which the width is being queried.
								Upon output, if the width source is \c #kCenteredProfileMark or \c #kUncenteredProfileMark, the
								possibly snapped position of that mark. To find whether snapping has occurred,
								cache the original length fraction and compare it to the returned value.
		@param tolerance		[in] If positive and the path has a user-specified variable width profile,
								and the input length fraction is within this tolerance of one of the t values in the
								width array, then the length fraction is snapped to that t value. If zero
								or negative, a tolerance of .001 is used.
		@param totalWidth		[out][optional] A buffer in which to return the total width at the given position,
								as obtained from the width source.
		@param leftWidth		[out][optional] A buffer in which to return the stroke width on the left side of the path
								at the given position, as obtained from the width source.
		@param rightWidth		[out][optional] A buffer in which to return the stroke width on the right side of the path
								at the given position, as obtained from the width source.
		@param widthSource		[out][optional] A buffer in which to return the width-source constant. It will be one of kConstantWidth, kTabletData,
								kCenteredProfileMark, kUncenteredProfileMark, kCenteredProfileInterpolation, kUncenteredProfileInterpolation.
		@param markerIndex		[out][optional] A buffer in which to return the marker index. If width source is from a centered
								or uncentered profile, the index into the parallel t and width arrays of the marker.
								For \c #kCenteredProfileMark and \c #kUncenteredProfileMark,
								it is the index of the marker at that location; for \c #kCenteredProfileInterpolation and
								\c #kUncenteredProfileInterpolation, it is the index of the preceding marker.
		@param markerDetails	[in/out][optional] On input, the only meaningful flag values are \c #kIncomingWidthMarker and
								\c #kOutgoingWidthMarker. These specify which of the two markers should be returned in
								the event that there are two markers at exactly the input length fraction. (If snapping
								occurs, then the flags are ignored; the incoming marker is returned when
								it snaps upward, and the outgoing when it snaps downward.) If null
								or if neither or both of those flags are on, and there are two markers
								at exactly the input length fraction, then the larger of the two is returned.
								On output, if  width source is \c #kCenteredProfileMark or \c #kUncenteredProfileMark, can
								contain one of \c #kIncomingWidthMarker or \c #kOutgoingWidthMarker, and/or \c #kCornerWidthMarker.
	*/
	AIAPI AIErr (*GetWidthsAtDistance)(AIArtHandle path, AIReal &lengthFraction, AIReal tolerance,
									   AIReal *totalWidth, AIReal *leftWidth, AIReal *rightWidth,
									   StrokeWidthSource *widthSource, ai::int16 *markerIndex, WidthMarkerFlags *markerDetails);

	/**	Sets the total width of the focal stroke at a given fraction of the distance along the path. (If lengthFraction is within
		0.001 of an existing t value in the width profile, modifies the existing width at that t value rather than
		inserting a new one.)
		<ul><li>If there is already a centered width profile, inserts the indicated value into it.</li>
		<li>If there is already an uncentered profile, this is equivalent to setting the left and right widths to half the input width.</li>
		<li>If there is not yet any user specified width profile, creates a centered width profile from the current stroke source
		and then modifies it and sets the stroke-width source to \c #kUserProfile. </li></ul>

		@param path				The path.
		@param lengthFraction	A fraction of the distance along the path	at which to set the width.  If within 0.001 of an existing t value
								in the width profile, modifies the existing width at that t value rather than inserting a new one.
		@param width			The new width.
		@param options			A logical OR of bit flags that determine how to perform the operation.
	*/
	AIAPI AIErr (*SetCenteredWidthAtDistance)(AIArtHandle path, AIReal lengthFraction, AIReal width, WidthMarkerFlags options);

	/**	Sets the left and right widths of the focal stroke at a given fraction of the distance along the given path. (If lengthFraction
		is within 0.001 of an existing t value in the width profile, modifies the existing width at that t value
		rather than inserting a new one.)
		<ul><li>If there is already an uncentered width profile, it inserts the indicated values into it.</li>
		<li>If left and right widths are equal and there is already a centered width profile, inserts their sum into it.</li>
		<li>If left and right widths are unequal and there is not yet an uncentered width profile, or if they are equal
		and there is not yet any width profile, it creates one from the current stroke source and then modifies it
		and sets the stroke-width source to \c #kUserProfile. </li></ul>

		@param path				The path.
		@param lengthFraction	A fraction of the distance along the path	at which to set the width.  If within 0.001 of an existing t value
								in the width profile, modifies the existing width at that t value rather than inserting a new one.
		@param leftWidth		The new left width.
		@param rightWidth		The new right width.
		@param options			A logical OR of bit flags that determine how to perform the operation.
	*/
	AIAPI AIErr (*SetUncenteredWidthsAtDistance)(AIArtHandle path, AIReal lengthFraction,
												 AIReal leftWidth, AIReal rightWidth, WidthMarkerFlags options);

	/**	Moves the width marker at the given index to a new t value. If the given marker is incoming-only or
		outgoing-only due to two markers being at the same t value, both are moved together.
		Only the content of the tValue array changes, so this works for either centered or non-centered widths.

			@param path			The path.
			@param markerIndex	The 0-based index position of the marker to move.
			@param newTValue	[in, out] Fraction of length along whole path to which the marker should be moved.
								In the range [0-1].
			@param options		A logical OR of bit flags that determine how to perform the operation:
				<ul> <li> If \c #kCopyMarker is on, the marker is duplicated and the new copy moved, while the old
				one remains at the prior location. There must always be a marker at 0 and one at 1,
				so any movement of the first or last marker is implicitly a duplication even if this flag is off. </li>
				<li>If \c #kSpreadWidthChanges is on, the other markers on the side that this marker is moving
				away from are spread out proportionally to cover the larger distance, and the other markers
				on the side that this marker is moving towards are compressed proportionally to fit in the
				smaller distance. The scope of the spreading is limited by the selection state and corner
				status of the adjacent anchor points.</li>
				<li>If \c #kSpreadWidthChanges is off and \c #kLimitAtNeighbors is on, and there is another width marker
				between the current t value at the given index and the new t value, then the marker stops
				when it hits the adjacent marker. No error code is returned in this case, but \c newTValue
				is updated to the actual destination. To determine whether it stopped, cache the original
				value and compare with the returned value.
				(Note that this causes the two markers at the same location to become an incoming-only
				outgoing only pair where the width may jump discontinuously.)</li>
				<li>If \c #kSpreadWidthChanges and \c #kLimitAtNeighbors are both off, then the moved marker is allowed
				to jump past other markers as if they were not there.</li>
				</ul>
			@return				The error \c #kBadParameterErr if the path does not have a user width profile or
				if the new t value is not in the range [0-1].
	*/
	AIAPI AIErr (*SlideWidthMarkerToNewT)(AIArtHandle path, ai::int16 markerIndex, AIReal &newTValue, WidthMarkerFlags options);

	/**	Deletes the width point at the given index position from the given path. The first and last width points cannot be deleted.

			@param path			The path.
			@param markerIndex	The index position of the point to delete.
	*/
	AIAPI AIErr (*DeleteWidthPoint)(AIArtHandle path, ai::int16 markerIndex);

	/**	Adds, removes, or reindexes width profile anchors as needed before editing a path.
		An editing tool or command calls this before modifying the geometry of a path
		or applying a different art style.

		Modifies anchors at a subset of the same places that cause \c #kSelectorAINotifyEdits
		to be sent to plug-in groups ancestral to the edited path. It is not necessary to send this message
		if the path is being transformed in its entirety in a way that does not change the relative lengths
		of path segments.

		If width anchors already exist at the relevant anchor points, and the numbers of anchor points are
		not changing, does nothing.

		@param path				The path to be edited.
		@param editDescription	The type of edit to be done.
	*/
	AIAPI AIErr (*AdjustWidthAnchorsBeforePathEdit)(AIArtHandle path, const PathEditDescription &editDescription);

	/**	Tests whether a cursor point on a path is within a given tolerance of the region covered by the stroke, and if
		so, reports additional details about what part of the stroke was hit; see  \c #StrokeHitResults.
		For brush strokes, the entire region within the brush design's tile box is considered to be stroked.

		@param path			The path.
		@param cursor		The cursor point.
		@param tolerance	The tolerance value.
		@param hitResults	A buffer in which to return the result.
	*/
	AIAPI AIErr (*StrokeHitTest)(AIArtHandle path, const AIRealPoint &cursor, AIReal tolerance, StrokeHitResults *hitResults);

};

#include "AIHeaderEnd.h"
#endif
