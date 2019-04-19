#ifndef __AIPluginGroup__
#define __AIPluginGroup__

/*
 *        Name:	AIPluginGroup.h
 *     Purpose:	Adobe Illustrator Plugin Group Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1995-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file
 * in accordance with the terms of the Adobe license agreement
 * accompanying it. If you have received this file from a source other
 * than Adobe, then your use, modification, or distribution of it
 * requires the prior written permission of Adobe.
 *
 */

/** @file AIPluginGroup.h */

/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif
#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif
#ifndef __AIArt__
#include "AIArt.h"
#endif
#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif
#ifndef __AIArtStyle__
#include "AIArtStyle.h"
#endif

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIPluginGroupSuite				"AI Plugin Group Suite"
#define kAIPluginGroupSuiteVersion6		AIAPI_VERSION(6)
#define kAIPluginGroupSuiteVersion		kAIPluginGroupSuiteVersion6
#define kAIPluginGroupVersion			kAIPluginGroupSuiteVersion


// These are the AI 6 style plug-in class messages.
// They are only needed temporarily until Joe T's prototype plug-ins are updated
// <<THESE WILL BE REMOVED>>
#define kSelectorAINotifyObject		"AI Notify Plugin Object"
#define kSelectorAIUpdateObject		"AI Update Plugin Object"


// These are the AI 7 style plug-in group messages (split into caller and request)
// <<PLEASE REMOVE THIS COMMENT WITH THE AI6 DEFINES>>

/** @ingroup Callers
	See \c #AIPluginGroupSuite */
#define kCallerAIPluginGroup		"AI Plugin Group"

/** @ingroup Selectors
	Notifies a plug-in group of edits to the edit group.
	An \c #AIPluginGroupMessage::code value indicates the
	type of editing operation being performed. An
	\c #AIPluginGroupMessage::time value indicates what stage of
	the operation is in progress.

	When the handler returns \c #kNoErr, the plug-in object is marked
	as "dirty" (in need of \c #kSelectorAIUpdateArt). To prevent this,
	return \c #kMarkValidPluginGroupReply. If the handler returns
	\c #kDontCarePluginGroupReply, retains the state of the object,
	and does not mark it as clean or dirty.

	If the handler returns \c #kWantsAfterMsgPluginGroupReply from a
	\c #kBeforeOperationTime notify-edits message, a single
	\c #kAfterOperationTime message is sent at the end of the transaction,
	just before the Undo recording is closed, and before the update message.
	The code is \c #kChangeOperationCode, regardless of whether a more
	specific code was sent at \c #kBeforeOperationTime).
	This is the appropriate place to make any changes to the edit art.

	@note An edit to children of the edit art does NOT always send a
	notify-edits message, although every edit sends an update message.
	Notify-edits is meant for highly structured objects where
	the different descendants have specific roles to play in the plug-in.
	Basic edits that are likely to require a specific response from plug-ins
	trigger the notify-edits message. Changes that are harder to generalize
	trigger only the update message.
	<br><br>
	For blend objects, for example, moving a spine point should cause
	the objects to move onto the spine, but moving a blend component should cause
	the spine point to move with the art object. Looking only at the post-edit
	state of the edit art, it would be hard to detect the difference between those
	two edits, since in both of them the only easily detected discrepancy, without
	knowing which paths were edited, is that the art elements are off the spine. */
#define kSelectorAINotifyEdits		"AI Notify Edits"

/** @ingroup Selectors
	Notifies a plug-in group that the result group needs to be rebuilt.
	See \c #AIPluginGroupSuite */
#define kSelectorAIUpdateArt		"AI Update"

/** @ingroup Selectors
	Asks a plug-in group whether the Layers palette shows edit groups.
	See \c #AIPluginGroupSuite */
#define kSelectorAICanShowContents	"AI Show Contents"

/** @ingroup Selectors
	Asks a plug-in group to interpolate plug-in data and dictionary contents
	when interpolations are made into a blend between plug-in groups.
	@see \c #kPluginGroupBlendAsPluginGroup

	Uses \c #AIPluginGroupMessage::time to indicate what stage of
	the operation is in progress. Not sent at \c #kCheckOperationTime, but you
	can use the \c #kBeforeOperationTime message to check whether the operation is allowed.

	At all stages, \c #AIPluginGroupMessage::preEditArt is the plug-in group being
	blended from (the one closest to t=0), and \c #AIPluginGroupMessage::postEditArt
	is the plug-in group being blended to (the one closest to t=1).

	\c #AIPluginGroupMessage::art is only used at \c #kDuringOperationTime.

	When the stage is \c #kBeforeOperationTime:
		\li If the plug-in returns \c #kRefusePluginGroupReply,
			the interpolated steps are ordinary groups blending the result groups,
			just as if the \c #kPluginGroupBlendAsPluginGroup option was off or the
			plug-in groups were of different classes. No further messages are sent.
			This lets the plug-in decide whether the two groups are blendable as plug-in
			groups based on their data or contents.
		\li If the plug-in returns \c #kDontCarePluginGroupReply, the edit groups
			are blended, then the \c #kSelectorAIUpdateArt message is sent.
			There are no \c #kDuringOperationTime or \c #kAfterOperationTime messages.
			The intermediate objects are of the same plug-in group class.
			Their plug-in data and dictionary contents are duplicated from
			the \c postEditArt object. <br>
			This reply is meant for plug-in groups that do everything identically
			for all of their objects and do not	need any extra data. It could also
			be returned when the plug-in determines	that the two objects
			have the same data.

		\li If the two plug-in groups are blendable as plug-in groups,
			and you need to interpolate their data, set up any data you
			will need for the \c #kDuringOperationTime	messages, then return
			either \c #kNoErr or \c #kWantsAfterMsgPluginGroupReply.

	The \c #kBeforeOperationTime message is the time to do anything
	that you want to do only once per blend, instead of once per step,
	such as finding and recording the commonalities, differences, and
	blendable aspects of the two objects. This temporary data can be
	stored in \c #AIPluginGroupMessage::AIInterruptData, or attached to the
	\c preEditArt and \c postEditArt objects.

	The \c #kDuringOperationTime message is sent only when the \c #kBeforeOperationTime
	message returns either \c #kNoErr or \c #kWantsAfterMsgPluginGroupReply. For each step,
	Illustrator creates a plug-in group of the same class, blends the edit group contents
	as if they were ordinary groups, and passes that interpolated object in
	\c #AIPluginGroupMessage::art (which is used only at this stage).
	<br> \c #AIPluginGroupMessage::t indicates which step has been reached.
	The interpolated objects are created with empty dictionaries
	and no plug-in data. This is the time for the plug-in to attach any
	interpolated data.

	The \c #kAfterOperationTime message is sent after all the interpolated steps
	have been created, if \c #kWantsAfterMsgPluginGroupReply was returned from any of the
	\c #kBeforeOperationTime or \c #kDuringOperationTime notifications. It
	gives you a chance to release any data you have set up.

	Any reply other than these is treated as an error and causes the blend
	not to be created at all.
	*/
#define kSelectorAIInterpolateData	"AI Interpolate Data"

/** @ingroup Selectors
	Asks a plug-in group to replace symbols used in its dictionary.
	Sent to plug-in groups that are selected when user chooses Replace Symbol
	in the Symbol palette. You are not required to handle this notification,
	even if the plug-in	group uses symbols. The sender does not modify the dictionary.
	See \c #AIReplaceSymbolMessageData
	\li If your handler rebuilds the result group, call \c #AIPluginGroupSuite::MarkPluginArtClean().
		If you modify only the dictionary, call \c #AIPluginGroupSuite::MarkPluginArtDirty(),
		so that	the update notification is sent upon return from the handler.
	\li If the handler performs the symbol replacement, return \c #kDidSymbolReplacement
		The caller uses this to decide whether to set the Undo/Redo strings, and so on.*/
#define kSelectorAIReplaceSymbol	"AI Art Replace Symbol"

/** @ingroup Selectors
	Asks a plug-in group whether it allows art objects of a given type in its edit group.
	Sent if the plug-in group option \c #kPluginGroupRestrictsArtTypes is on.
	Sent before an insertion into the edit group is made, whether interactive or programmatic.
	Not sent if the plug-in group is as under construction within the
	current context.

	Valid return values are:
		\li \c #kNoErr: Plug-in groups managed by this plug-in do allow art objects of the given type.
		\li \c #kRefusePluginGroupReply: Plug-in groups managed by this plug-in do not allow art objects
			of the given type.
		\li \c #kCheckPluginGroupReply: Requests a \c #kSelectorAINotifyEdits notification
			with \c code \c #kTopologyOperationCode and \c subCode \c #kPasteIntoOpCode,
			so that the plug-in manager can take other factors into account, such as the options
			attached to the specific plug-in group receiving the new art.

	See \c #AIPluginArtTypeMessageData  */
#define kSelectorAIDisallowsArtTypeQuery	"AI Plugin Group Disallow Art Type"

/** @ingroup Selectors
	Asks a plug-in group to perform a custom hit test.
	Sent when \c #AIHitTestSuite::CustomHitTest() is called for a plug-in group,
	when a hit occurs within the bounds of the plug-in group object.
	\li If the handler finds a hit, return \c #kCustomHitPluginGroupReply and store the
		custom hit information in \c #AIPluginGroupCustomHitTestData::CustomHitData.
	\li If the handler does not find a hit, return \c #kNoErr

	See \c #AIPluginGroupCustomHitTestData  */
#define kSelectorAIPerformCustomHitTest		"AI Plugin Group Perform Custom Hit Test"

/** @ingroup Selectors
	Asks a plug-in group to collect the paint styles of all objects
	for which it privately manages styles.
	Sent if the \c #kPluginGroupManagesPaintStyles option flag is on.
	Your handler iterates the art styles or path styles in plug-in group art to a
	callback function, which can examine, but not modify the art styles and art objects.

	Call the desired callback function repeatedly until either all the relevant styles
	have been iterated,	or until the callback returns an error or \c #kIterationCanQuitReply.
	Return this as the result of the notification.

	Use to process information about style-related attributes of
	selected objects, such as fill or stroke attributes, when the styles do not map
	directly onto the styles of selected objects within the edit group.
	A stroke style, for example, might apply only to certain bezier segments
	and not to an entire path.You can keep styles in a dictionary, along with
	information about parts of the edit group and/or result group to which those styles apply.

	You can iterate partial styles to privately accumulate a report for multiple objects.
	Invalid fields, as identified by the style map, are considered \e mixed in the plug-in group.
	For example, if \c fillPaint is false in the style map, it means that some
	potentially-fillable contents are filled, and some are not filled.
	If it is difficult or time-consuming to determine which styles
	correspond to selected objects, you can privately cache the results of an accumulated style and
	style map, and call the path-style callback only once with those cached results. Clear the cache
	on a selection-changed or properties-changed notifier.

	See \c #AIPluginGroupCollectPaintStylesData  */
#define kSelectorAICollectPaintStyles		"AI Plugin Group Collect Paint Styles"

/** @ingroup Selectors
	Sent only if the \c #kPluginGroupManagesPaintStyles option flag is on.
	Asks the plug-in group to merge a path style into those of its selected descendants,
	or perform a transformation on the path styles. See \c #AIPluginGroupApplyPaintStylesData,

	@note The notify-edits message informs the plug-in group that
		styles are being transformed externally, while this message
		asks the plug-in group to do the transformation.
	*/
#define kSelectorAIApplyPaintStyles		"AI Plugin Group Apply Paint Styles"

/** @ingroup Selectors
	Asks a plug-in group to apply a developer-defined color-mapping
	callback function to objects for which it privately manages styles or colors.

	Initiated by plug-ins or other system components that want to alter all the colors
	in a collection of objects. Your handler must iterate through the colors within
	the plug-in group that fit the request, passing them to the supplied callback.

	The message data, \c #AIPluginGroupAdjustColorsData, contains three callback procedures,
	for colors, styles, and patterns. Your handler must execute the proper callback
	on each data entry of the appropriate type that contains meaningful colors; that is,
	those that can affect the colors in the result art.

	\li If the plug-in group contains art objects with meaningful colors in its dictionary or
		plug-in group data, (for example,the content art of Envelope objects in Edit Envelope mode),
		call \c #AIPathStyleSuite::AdjustObjectAIColors() for those objects, passing in the
		\c #AIPluginGroupAdjustColorsData::adjustColorCallback and
		\c #AIPluginGroupAdjustColorsData::callbackData.

	\li You need not process art objects whose colors are ignored in building the result art;
		for example, the gradient mesh that defines the distortion in an Envelope object.

	For private color data not contained in an \c #AIArtHandle, choose the callback
	that most directly matches the data types the plug-in stores. For example, if it
	stores an \c #AIArtStyleHandle, use the style callback, rather than attempting
	to iterate the colors in the art style.

	If the option \c #kPluginGroupManagesPaintStyles is on for the plug-in, the handler
	for this message performs the entire adjustment for the plug-in group. If the option is off,
	the colors in the edit group are further processed after this handler
	completes, unless your handler returns \c #kSkipEditGroupReply.

	To initiate this request to a plug-in group that your plug-in does not manage,
	call \c #AIPluginGroupSuite::PluginArtAdjustColors().

	@note Adobe internal developers: See \c AIPluginSelectionAdjustColors in
		Adobe internal suite \c AIPluginSelection for when the plug-in group
		manages its own selection mode.
	*/
#define kSelectorAIAdjustColors		"AI Plugin Group Adjust Colors"

 /** @ingroup Selectors
 	Sent to plug-ins where the \c #kPluginGroupAskToShowContents option is set,
 	to request the "Show Contents" mode. The plug-in should enter a mode where the
 	contents are shown and editable.
 	If this does not make sense for a particular plug-in group, ignore the call. */
 #define kSelectorAIShowContents		"AI Plugin Group Show Contents"


/** Options for \c #AIPluginGroupSuite::AddAIPluginGroup().
	Options affect how operations on a plug-in group affect the
	result group, and whether the notifications are	sent after an operation.
	Notifications include \c #kSelectorAIUpdateArt "AI Update" and
	\c #kTransformOperationCode "AI Notify Edits".
	(Options cannot be changed after the class is defined.) */
enum AIPluginGroupOptions {
	/** If on, updates are triggered by edits to non-descendant objects
		that overlap the bounds of the editable art. This is intended for objects
		with lens-like effects (distorting what they move over), or
		avoidance behavior (moving away from what moves over them). */
	kPluginGroupWantsOverlapUpdateOption	= (1<<1),
	/** If on, when the entire plug-in group is translated as a whole, the
		result group is transformed as well, and no update message is sent. */
	kPluginGroupWantsAutoTranslateOption	= (1<<2),
	/** If on, when the entire plug-in group is scaled uniformly, the
		result group is transformed as well, and no update message is sent. */
	kPluginGroupWantsAutoUScaleOption		= (1<<3),
	/** If on, when the entire plug-in group is transformed as a whole by any matrix,
		the result group is transformed as well, and no update message is sent.
		The notify-edits message is sent to let the plug-in know what has been done;
		A zero return from the automatically-handled operation types is treated
		like a \c #kDontCarePluginGroupReply return, so you need not register for
		the notify-edits message if you do not need to respond to it. */
	kPluginGroupWantsAutoTransformOption	= (1<<4),
	/** If on, hit testing by other tools does fill hit testing on the edit group.
		(The plug-in's own tool controls its own hit testing.) By default,
		the edit group is only outline-hit, because objects in the edit group
		are not previewed. Use this options if you copy the edit group contents	into the
		result group and then add things, making it appear that the edit
		group paths are previewed. This allows direct selection of individual editable
		paths with a fill click.

		When on, if there are some edit group objects whose fills or strokes are
		\e not copied into the result group, you must check style change notifications
		to turn off any fill or stroke paint that the user has given to those objects.
		Otherwise, hits can occur on elements you have not painted.
		See also \c #kPluginGroupForceFillHitOnClosedPaths. */
	kPluginGroupDoEditFillHitOption			= (1<<5),
	/** If off (the default), when a user edit removes all objects from the edit group,
		the whole plug-in group object is deleted (analogous to the behavior of non-layer groups).
		If on, the plug-in group remains in the artwork	after its edit group has been emptied.
		Use for objects that build their result art based entirely on private data that requires
		no edit art, or that behave like layers in that they can maintain the drawing insertion
		focus while empty. For implementing layer-like plugin groups, see also the flags
		#kPluginGroupDoNotTarget and #kPluginGroupDoNotSmartTarget. */
	kPluginGroupKeepWhenEmptyOption			= (1<<6),

	/** If on, the objects in the result group behave like fill of the
		objects in the edit group. You could use this, for example, to
		implement ink hatching. Setting this flag informs other plug-ins
		of your plug-in group's behavior. For example, an Expand Fill filter
		could expand plug-in groups if this flag is on, or a Fill Color could
		refuse to assign a pattern or gradient fill to the edit group objects,
		knowing that the result group is acting as the fill. (Assigning solid color
		should be permitted, since fill-like plug-in groups often colorize their fills.)
		Default is off. */
	kPluginGroupIsFillLike					= (1<<7),
	/** If on, the objects in the result group behave like stroke of the
		objects in the edit group. You could use this, for example, for brushes.
		Setting this flag informs other plug-ins of your plug-in group's behavior.
		For example, an Expand Stroke filter could expand plug-in groups if this
		flag is on, or the Stroke palette could ignore stroke attributes,
		knowing that the result group is acting as the stroke. Default is off.

		If both this and \c #kPluginGroupIsFillLike are off, the result group objects
		are treated as related to the edit group in some way other than fill or stroke
		effect. An example is path interpolation blends. */
	kPluginGroupIsStrokeLike				= (1<<8),

	/**	If on, the plug-in group object can never be targeted.
		Illustrator always recurses into the contents of the edit group
		to find targeted objects, regardless of whether the plug-in	group object
		is fully selected. This flag prevents users from targeting the
		plug-in group and applying styles, transparency or effects to that level,
		even via the Layers or Appearance panels.
		Also, if this flag and #kPluginGroupKeepWhenEmptyOption are both on,
		then the plugin group will act very much like a layer, in that commands
		such as Group, Cut,	Delete, Copy and copy-drag will operate upon the contents
		of the edit group, somewhat as if it were only partially selected, rather
		than the entire plugin group. See also #kPluginGroupDoNotSmartTarget.
	 */
	kPluginGroupDoNotTarget					= (1<<9),
	/**	If on, selecting any piece inside the edit group automatically targets
		the plug-in group level. This targeting behavior is similar to that of
		compound paths. Fill/stroke changes apply to the plug-in group level,
		and the "Contents" field is not shown in the Appearance palette.
		The Compound Shapes plug-in group uses this option.
		Users can still target the objects inside the edit group
		individually in the Layers palette. */
	kPluginGroupAlwaysSmartTarget			= (1<<10),
	/**	If on, the plug-in group is not targeted when fully selected. Users must
		target the plug-in group through the Layers panel or the Appearance panel.
		Also, if this flag and #kPluginGroupKeepWhenEmptyOption are both on,
		then the plugin group will act very much like a layer, in that commands
		such as Group, Cut,	Delete, Copy and copy-drag will operate upon the contents
		of the edit group, somewhat as if it were only partially selected, rather
		than the entire plugin group. See also #kPluginGroupDoNotTarget.
		Do not set both this option and \c #kPluginGroupAlwaysSmartTarget for the
		same plug-in group. */
	kPluginGroupDoNotSmartTarget			= (1<<11),

	/**	If on, plug-in objects of this plug-in group can be clipping objects.
		The result art of a clipping object is used as a clip, if its type
		makes this possible. */
	kPluginGroupCanBeClipping				= (1<<12),

	/**	If on, the Layers palette always shows the contents of the edit group. */
	kPluginGroupAlwaysShowContents			= (1<<13),
	/**	If on, the Layers palette queries the plug-in group with the
		\c #kSelectorAICanShowContents message to ask if it may expand
		the plug-in group. The plug-in group should reply with \c #kRefusePluginGroupReply
		if it is \e not okay to expand. */
	kPluginGroupAskToShowContents			= (1<<14),

	/** Together with \c #kPluginGroupBlendAsPluginGroup, defines how plug-in groups
		other than blends act when they appear inside a blend. This one is tested first.

		If on, and the selection includes any other plug-in group with this flag on,
		the Make Blend command is disabled. Also, fully selected plug-in groups with
		this option on do not respond to clicks of the Blend tool (although you can
		still create blends INSIDE of them.)

		If the selection contains no plug-in groups with this flag on, then plug-in groups
		that are blended to anything other than another plug-in group of the same class
		with the \c #kPluginGroupBlendAsPluginGroup flag on are treated as if they
		were their result group. The interpolated objects are ordinary groups. */
	kPluginGroupDisableBlends				= (1<<15),

	/** Together with \c #kPluginGroupDisableBlends, defines how plug-in groups
		other than blends act when they appear inside a blend.
		\c #kPluginGroupDisableBlends is tested first.

		If the blend includes two adjacent plug-in groups of the same plug-in class,
		and this option on for that class, then the interpolated objects
		are also of the same plug-in class. The contents of the edit groups of
		the two plug-in objects are blended as if they were ordinary groups. The plug-in
		can then interpolate the plug-in group data and dictionary contents;
		see \c #kSelectorAIInterpolateData. Finally the interpolated plug-in groups are
		sent the \c #kSelectorAIUpdateArt message.  */
	kPluginGroupBlendAsPluginGroup			= (1<<16),

	/** If on, the plug-in group restricts which types of objects can be inserted
		into its edit group, and should handle the \c #kSelectorAIDisallowsArtTypeQuery
		message. This differs from the check you do for a \c #kBeforeOperationTime
		\c #kSelectorAINotifyEdits response, in that such a check passes in
		a specific prospective-contents object to a specific plug-in group, and checks
		whether that object can be inserted. The \c #AIPluginArtTypeMessageData does not
		have a specific art object, only an art type. You can use it, for example, to
		disable tools  or commands that might otherwise create a new object of that type,
		or to provide cancel feedback on mouse over. */
	kPluginGroupRestrictsArtTypes			= (1<<17),

	/** Provides a lighter-weight, less flexible version of customized fill hit testing.

		If on, the plug-in group is treated as if it supplied fill paint on closed paths,
		so that selection tools select those paths in the edit group when clicking
		in their interiors, even if they have no fill paint of their own and no ancestor art style supplies
		fill paint.

		See also  \c #kPluginGroupForceFillHitOnAllPaths (the same, but for all paths)

		Edit fill hit testing is done only after outline testing fails to hit anything in
		the whole edit group, so front contents do not obscure outlines of back contents. It is also done
		only if something is hit in the result group, so that paths that are unfilled and that do not
		overlap any filled region are not selected.

		If on, this option takes precedence over \c #kPluginGroupDoEditFillHitOption, meaning that
		the plug-in group has private data that it uses to supply fills (rather than edit objects
		being copied into the result group).

		This option is not the best choice if the plug-in group supplies private fills
		on only some parts of the edit group, or if the fill geometry is transformed. In that case,
	    custom hit testing allows more customization, but takes longer. */
	kPluginGroupForceFillHitOnClosedPaths			= (1<<18),

	/** Provides a lighter-weight, less flexible version of customized fill hit testing.

		If on, the plug-in group is treated as if it supplied fill paint on all paths,
		so that selection tools select those paths in the edit group when clicking
		in their interiors, even if they have no fill paint of their own and no ancestor art style supplies
		fill paint.

		See  \c #kPluginGroupForceFillHitOnClosedPaths for additional details.  */
	kPluginGroupForceFillHitOnAllPaths				= (1<<19),

	/** If on, paint styles applied to content of this plug-in group should not be obtained or set
		by accessing the art styles of objects in the edit group, but instead by asking the plug-in group to
		get or set the paint styles attached to objects that it considers selected. The plug-in
		receives the \c #kSelectorAICollectPaintStyles message when Illustrator would normally
		iterate the art styles attached to children of the edit group, and receives the
		\c #kSelectorAIApplyPaintStyles message when Illustrator would normally set the art
		styles attached to children of the edit group.

		See also \c #AIPluginGroupCollectPaintStylesData, \c #AIPluginGroupApplyPaintStylesData

		Use if art styles attached to selected objects in the edit group do not reflect what the user
		sees as the selected styles. (The contents of the edit group are not previewed, so the styles
		in the result group are what the user sees, and they may not correspond	directly to the styles used
		in the edit group.) Also useful for plug-in groups that manage selection state in a way that does
		not map directly onto object selection within the edit group.

		This flag is not compatible with any of the target flags (\c #kPluginGroupDoNotTarget,
		\c #kPluginGroupAlwaysSmartTarget, \c #kPluginGroupDoNotSmartTarget).
	*/
	kPluginGroupManagesPaintStyles	= (1<<20),

	/** If on, the plugin group allows at least some grouping operations to be performed
		inside of it. Grouping operations include Group, Ungroup, Make Compound, Make Clip,
		and their corresponding Release operations, plus Expand Appearance and Expand,
		since they typically convert a leaf object into a group. If off, no grouping
		operations are attempted and no #kCheckOperationTime message is sent.
		The reason there is a flag rather than just using a #kCheckOperationTime message
		before the edit, as is done for most kinds of edits, is that until CS 6, grouping
		operations were unilaterally disallowed inside all plugin groups. Since the default
		for no response to a kCheckOperationTime message is to assume that the operation
		IS allowed, in order not to alter the runtime environment for legacy plugins we
		must default to sending no message and not attempting the operation.
	 */
	 kPluginGroupPermitsGroupCmds	= (1<<21)
};


// These are the errors returned by calls to AIPluginGroup suite functions (other than the AIArt standards).

/** @ingroup Errors
	Plug-in group not found (when looked up by name).  See \c #AIPluginGroupSuite */
#define kUnknownPluginGroupErr			'GRP?'
/** @ingroup Errors
	Plug-in group already attached to an object. See \c #AIPluginGroupSuite::SetPluginArtPluginGroup() */
#define kAttachedPluginGroupErr			'GRP!'
/** @ingroup Errors
	See \c #AIPluginGroupSuite::SetPluginArtDataCount() */
#define kTooMuchDataPluginGroupErr		'FULL'

/** Limit on the size of the data store in a plug-in group. */
#define kPluginStoreLimit			( 32 * 1024 )


/** @ingroup Errors
	Return code for response to \c #kSelectorAIDisallowsArtTypeQuery when
	\c #AIPluginGroupMessage::time is \c #kCheckOperationTime,
	if the edit should not happen. */
#define kRefusePluginGroupReply			'RFSE'
/** @ingroup Errors
	Return code for	response to \c #kSelectorAIDisallowsArtTypeQuery when
	\c #AIPluginGroupMessage::time is \c #kCheckOperationTime,
	if the plug-in group wants to get a \c #kSelectorAINotifyEdits message with
	\c #kCheckOperationTime to refine the answer to the query. */
#define kCheckPluginGroupReply			'CHEK'
/** @ingroup Errors
	Return code for	response to \c #kSelectorAIInterpolateData,
	if the plug-in group wants to get a \c #kAfterOperationTime message
	before the \c #kSelectorAIUpdateArt message. */
#define kWantsAfterMsgPluginGroupReply	'AFTR'
/** @ingroup Errors
	Return code for response to \c #kSelectorAIReplaceSymbol message
	if the plug-in group did perform the requested replacement. */
#define kDidSymbolReplacement			'dsRP'

/** @ingroup Errors
	Return code for response to \c #kSelectorAINotifyEdits
	at \c #kAfterOperationTime, if the plug-in group has already updated
	the object. (The default behavior, on \c #kNoErr, is to mark
	the object as dirty, in need of \c #kSelectorAIUpdateArt.)

	@see \c #AIPluginGroupSuite::MarkPluginArtClean()  */
#define kMarkValidPluginGroupReply		'VALD'
/** @ingroup Errors
	Return code for response to \c #kSelectorAINotifyEdits at
	\c #kAfterOperationTime, if the edit is irrelevant to this plug-in.
	For example, changing the "show center" attribute or locking edit-art
	contents rarely affects the result art.
	Retains the state of the object, and does not mark it as clean or dirty. */
#define kDontCarePluginGroupReply		'MOOT'
/** @ingroup Errors
	Return code for response to \c #kSelectorAINotifyEdits.
	If returned from \c #kAfterOperationTime with \c #kReadOperationCode,
	it means that the plug-in group should be destroyed upon return.
	If returned from \c #kAfterOperationTime with \c #kChangeOperationCode,
	it means that the plugin deleted itself in response to the notification,
	and therefore should not be dereferenced afterwards. (It is invalid for
	a plugin group to delete itself when handling other notifications.)
*/
#define kDestroyPluginGroupReply		'TRSH'
/** @ingroup Errors
	Return code for response to \c #kSelectorAIPerformCustomHitTest,
	message if the custom hit test wants to report a hit.
	A return of \c #kNoErr means a hit will not be reported */
#define kCustomHitPluginGroupReply		'CHIT'
/** @ingroup Errors
	Return code for response to \c #kSelectorAIAdjustColors message if
	the plug-in group does not want the colors in the edit group to be visited. */
#define kSkipEditGroupReply				'skpE'


/** For the \c #kSelectorAINotifyEdits and \c #kSelectorAIInterpolateData
	messages, an operation time that indicates the
	relationship of the notification to the stage of the operation.
	An \c #AIPluginGroupMessage::AIOperationTime value.
	The times are:
	<br> \c	#kCheckOperationTime
	<br> \c #kBeforeOperationTime
	<br> \c #kAfterOperationTime
	<br> \c #kDuringOperationTime

	@note You must not dispose of or reorder any artwork objects during a
		\c #kCheckOperationTime or \c #kBeforeOperationTime notification.
		Any editing must wait until \c #kAfterOperationTime.
*/
typedef const char *AIOperationTime;

// the times themselves

/** Determine whether the plug-in allows this operation. Not sent
	for \c #kSelectorAIInterpolateData.
	An \c #AIPluginGroupMessage::time value.*/
#define kCheckOperationTime			"AI Check Operation Time"
/** Prepare for the operation to occur.
	An \c #AIPluginGroupMessage::AIOperationTime value.*/
#define kBeforeOperationTime		"AI Before Operation Time"
/** The operation has completed.
	An \c #AIPluginGroupMessage::AIOperationTime value. */
#define kAfterOperationTime			"AI After Operation Time"
/** The operation is ongoing. Sent only for \c #kSelectorAIInterpolateData.
	An \c #AIPluginGroupMessage::AIOperationTime value. */
#define kDuringOperationTime		"AI During Operation Time"


/** For \c #kSelectorAINotifyEdits, an \c #AIPluginGroupMessage::code
	value that indicates the type of editing operation being performed.

	These code values refer to the entire plug-in group object:
	<br> \c #kReadOperationCode
	<br> \c #kWriteOperationCode
	<br> \c #kAttachOperationCode
	<br> \c #kExpandOperationCode

	For these code values, the editing parameters,
	\c #AIPluginGroupMessage::preEditArt and \c #AIPluginGroupMessage::postEditArt
	indicate the edit group or member that has been or will be edited:
	<br> \c #kOrderingOperationCode
	<br> \c #kTransformOperationCode
	<br> \c #kGeometryOperationCode
	<br> \c #kTopologyOperationCode
	<br> \c #kDeleteOperationCode
	<br> \c #kAttributeOperationCode
	<br> \c #kStyleOperationCode
	<br> \c #kChangeOperationCode

	The editing parameters are valid only during \c #kCheckOperationTime and
	\c #kBeforeOperationTime, where one notify-edits message is sent for
	each top-level affected or selected descendant of the plug-in object.
	For example, if an entire group is selected but its parent is not fully selected,
	that group is passed as the \c preEditArt, but not its children.

	For some codes, additional subcodes indicate which of several operations of
	the given type is occurring. Subcodes are \c #AIErr (four-byte \c char) values,
	that can be used in debugging as well as allowing switch statements.
	*/
typedef const char *AIOperationCode;

// the codes themselves

/** Translate data from external to internal representation at
	\c #kAfterOperationTime. */
#define kReadOperationCode			"AI Read Operation Code"
/** Translate data from internal to external representation at
	\c #kBeforeOperationTime, and back to internal at \c #kAfterOperationTime.
	\c Also sent at #kCheckOperationTime when a plug-in can reply
	kRefusePluginGroupReply to indicate that the plug-in art cannot be written and
	must be expanded (reply kNoErr otherwise).
	*/
#define kWriteOperationCode			"AI Write Operation Code"
/** Sent when \c #AIPluginGroupSuite::UseAIPluginGroup() is called to associate
	a specific plug-in object with the plug-in group. Allows you to check for
	consistency and confirm that the group can accept the given object.
  */
#define kAttachOperationCode		"AI Attach Operation Code"
/** Sent only at \c #kCheckOperationTime and \c #kBeforeOperationTime (after an
	Expand, the object no longer exists). The plug-in art object is about to be
	expanded, that is, replaced by its result art contents. Remove from the result
	art descendants any tags or other state specific to the plug-in, and remove
	from the plug-in's global data anything that tracks this art object. */
#define kExpandOperationCode		"AI Expand Operation Code"
/** Send to front, back, forward, backward. See \c #AIOrderingOperationSubcodes for
	subcode values. */
#define kOrderingOperationCode		"AI Ordering Operation Code"
/** Matrix operations on whole objects. See \c #AITransformOperationSubcodes for subcode
	values. */
#define kTransformOperationCode		"AI Transform Operation Code"
/** Segments of a path have been modified. See \c #AIGeometryOperationSubcodes for subcode
	values. */
#define kGeometryOperationCode		"AI Geometry Operation Code"
/** A single object is being replaced by multiple. Also covers paste into edit art.
	See \c #AITopologyOperationSubcodes for subcode values.
	@note A join of two paths is indicated by a Geometry of one followed by a Delete
	of the other, not a Topology (because the \c preEditArt must always be a
	single existing descendant of the edit art group). */
#define kTopologyOperationCode		"AI Topology Operation Code"
/** An element of the edit art group is being deleted */
#define kDeleteOperationCode		"AI Delete Operation Code"
/** Lock/unlock, show/hide, or changing the name or xml UID.
	See \c #AIAttributeOperationSubcodes for subcode values. */
#define kAttributeOperationCode		"AI Attribute Operation Code"
/** Path style or text style modifications. See \c #AIStyleOperationSubcodes for subcode
	values. */
#define kStyleOperationCode			"AI Style Operation Code"
/** Sent only at \c #kAfterOperationTime, a generic or mixed operation occurred that
	does not fit into other categories. Provides no other details of the operation. */
#define kChangeOperationCode		"AI Change Operation Code"


//

/** Subcode values for \c #kChangeOperationCode (only at \c #kAfterOperationTime) */
enum AIChangeOperationSubcodes {
	/** Something in the edit group has been modified by plug-in calls, and
		Illustrator is about to pop the context. There will have been no
		\c #kBeforeOperationTime notification. Handler must not modify anything other
		than the plug-in object itself (because it is called in a loop that
		is processing the artwork tree). */
	kPluginSyncArtOpCode	= 'PLUG'
};

/** Subcode values for \c #kOrderingOperationCode */
enum AIOrderingOperationSubcodes {
	kSendToBackOpCode		= 'BACK',
	kSendToFrontOpCode		= 'FRNT',
	kSendBackwardOpCode		= 'DOWN',
	kSendForwardOpCode		= 'UPWD',
	kReverseGroupOpCode		= 'RVRS',

	/** The \c #AIPluginGroupMessage::preEditArt is in the plug-in group,
		and is being moved to another location which is also inside the plug-in group.
		See \c #AIPluginGroupMessage::insertionOrder and \c #AIPluginGroupMessage::destinationArt
		for the destination of the move.
		Used only if the movement is not equivalent to one of the more specific commands above. */
	kSendInternalOpCode		= 'SINT',

	/** The \c #AIPluginGroupMessage::preEditArt is in the plug-in group, and is about
		to be reordered to a location outside the plug-in group.
		See \c #AIPluginGroupMessage::insertionOrder and \c #AIPluginGroupMessage::destinationArt
		for the destination of the move.
		This is a chance to remove any private dictionary entries from the \c preEditArt.) */
	kReorderOutCode			= 'MVOT',

	/** The \c #AIPluginGroupMessage::preEditArt is outside the plug-in group, and is
		about to be reordered to a location inside the plug-in group,
		See \c #AIPluginGroupMessage::insertionOrder and \c #AIPluginGroupMessage::destinationArt
		for the destination of the move.
		(Typically handled in the same way as a \c #kPasteIntoOpCode for \c #kTopologyOperationCode.) */
	kReorderIntoOpCode		= 'MVIN'
};

/** Subcode values for \c #kTransformOperationCode */
enum AITransformOperationSubcodes {
	kTranslationOpCode		= 'MOVE',
	kRotationOpCode			= 'ROTA',
	kUniformScaleOpCode		= 'USCA',
	kNonUniformScaleOpCode	= 'NSCA',
	kShearOpCode			= 'SHER',
	kReflectionOpCode		= 'REFL',
	kMixedTransformOpCode	= 'MTFM'
};

/** Subcode values for \c #kGeometryOperationCode */
enum AIGeometryOperationSubcodes {
	kMiscPathChangeOpCode	= 'GEOM',
	/** Unused */
	kMovePointsOpCode		= 'MPTS',
	/** Unused */
	kAdjustControlsOpCode	= 'ADJC',
	/** Unused */
	kAddPointsOpCode		= '+PTS',
	/** Unused */
	kRemovePointsOpCode		= '-PTS',
	/** Unused */
	kReverseSegmentsOpCode	= 'RVRS',
	/** Unused */
	kOpenCloseOpCode		= 'OPCL',
	/** Unused */
	kSwapSymbolsOpCode      = 'SWSM'
};

/** Subcode values for \c #kTopologyOperationCode  These are sent
	at \c #kBeforeOperationTime, and provide additional information
	about what type of change is about to occur. Your handler can update
	private data, but must not make any changes to the edit group.
*/
enum AITopologyOperationSubcodes {
	/** One path is replaced by two. */
	kScissorOpCode			= 'SCIZ',
	/** The \c #AIPluginGroupMessage::postEditArt (or its children if it is a group)
		will be inserted into the edit art below \c #AIPluginGroupMessage::preEditArt
		(which is the same as \c #AIPluginGroupMessage::destinationArt.)
		*/
	kPasteBelowOpCode		= 'PBEL',
	/** The \c #AIPluginGroupMessage::postEditArt (or its children if it is a group)
		will be inserted above \c #AIPluginGroupMessage::preEditArt
		(which is the same as \c #AIPluginGroupMessage::destinationArt.) */
	kPasteIntoOpCode		= 'PINT',
	/** The \c #AIPluginGroupMessage::postEditArt (or its children if it is a group)
		will be inserted below \c #AIPluginGroupMessage::preEditArt
		(which is the same as \c #AIPluginGroupMessage::destinationArt.) */
	kPasteAboveOpCode		= 'PABV',
	/** The \c #AIPluginGroupMessage::postEditArt is a transformed copy of \c preEditArt.
		Typically it will be inserted above \c #AIPluginGroupMessage::preEditArt.
		Check \c #AIPluginGroupMessage::destinationArt and \c #AIPluginGroupMessage::insertionOrder
		for the insertion location. */
	kTransformCopyOpCode	= 'TCOP',
	/** The \c #AIPluginGroupMessage::preEditArt will be changed into a type path. */
	kTypePathChangeOpCode	= 'TYCH',
	/** Unused */
	kReplaceOneOpCode		= 'REP1',
	/** Unused */
	kReplaceByManyOpCode	= 'REPM',
	/** The \c #AIPluginGroupMessage::postEditArt is a non-transformed copy of \c preEditArt,
		which will be inserted in the art edit group or a descendant.
		Check \c #AIPluginGroupMessage::destinationArt and
		\c #AIPluginGroupMessage::insertionOrder for the insertion location.
		*/
	kDuplicateInsideOpCode		= 'DUPi',
	/** Sent only at \c #kAfterOperationTime. The \c #AIPluginGroupMessage::postEditArt
		is a copy of \c preEditArt which was moved outside the plug-in group.
		Allows you to remove any private tags or dictionary entries
		from the \c postEditArt.  */
	kDuplicateOutsideOpCode		= 'DUPo',
	/** The selected objects inside the plugin group are to be combined into a
		group, compound path, or clipping group. The \c #AIPluginGroupMessage::preEditArt
		is the first encountered selected component of the plugin group, which determines
		where the new group will be placed in the stacking order. At \c #kCheckOperationTime
		and \c #kBeforeOperationTime the \c #AIPluginGroupMessage::postEditArt is an
		empty art object of the type that is going to be created. The plugin can call
		\c #AIArtSuite::GetArtType() to determine whether a group or compound path is being
		created, and can call \c #AIGroupSuite::GetGroupClipped() when the type is \c #kGroupArt
		to determine when a clipping group is being created. The \c postEditArt at pre-edit
		time is not necessarily the same \c AIArtHandle that is created,
		and is definitely not in the art tree; it has a null parent.
		If this message is sent at \c #kAfterOperationTime, the \c postEditArt is the
		resulting group or compound path art.
		This operation code is sent only if the \c #kPluginGroupPermitsGroupCmds option
		is set. If that option is off, no group operations are attempted.
	*/
	kMakeGroupOpCode		= 'GRUP',
	/** The \c #AIPluginGroupMessage::preEditArt will be ungrouped or released.
		If it is a nested plugin group, it will be replaced by its edit art group.
		This operation code is sent only if the #kPluginGroupPermitsGroupCmds option
		is set. If that option is off, no release group operations are attempted.
	*/
	kReleaseGroupOpCode		= 'UNGP',
	/** If non-null, the \c #AIPluginGroupMessage::preEditArt will be expanded into a group
		that expands all or part of the appearance. If it is a nested plugin group, it will
		be expanded into its result group. If it is an object with an active art style,
		it will be replaced by the styled art. If it has a basic appearance, either the
		fills or strokes or both will be expanded. If the \c preEditArt is null or is the
		plugin group itself, then the plugin group is partially selected and is about to be
		examined by one of the Expand commands. This gives the plugin group a chance to return
		\c #kRefusePluginGroupReply to skip examination of the contents, if the plugin group
		disallows all expansions inside (but allows \c #kMakeGroupOpCode and/or \c #kReleaseGroupOpCode.)
		No attempt is made to inform the plugin group of the details of the operation,
		as there are too many variations, and the main intent is to ask whether the expansion
		is allowed at all.
		This operation code is sent only if the \c #kPluginGroupPermitsGroupCmds option
		is set. If that option is off, no expansion operations are attempted inside the
		plugin group.
		See also \c #kExpandOperationCode for notifications of the expansion of the entire
		plugin group.
	*/
	kExpandInsideOpCode	= 'ExpI'
};

/** Subcode values for \c #kStyleOperationCode */
enum AIStyleOperationSubcodes {
	kPathStyleOpCode		= 'PATH',
	/** Unused */
	kTextStyleOpCode		= 'ATET',
	/** Unused */
	kArtStyleOpCode			= 'ARTS'
};

/** Subcode values for \c #kAttributeOperationCode
	By default, a c #kNoErr return (usually meaning the notification was not handled)
	for the Name subcode does not mark the plugin group dirty, because it is not
	expected to change the contents of the result group for a typical plugin group.
	This is in contrast to most edit notifications, which mark the plugin group
	dirty unless it receives a \c #kDontCarePluginGroupReply from a \c #kBeforeOperationTime
	notification or a \c #kMarkValidPluginGroupReply from a \c #kAfterOperationTime notification.
	Since there is no reply that tells the plugin group to invalidate itself on these
	notifications, if a rebuild is wanted on a change of name the plugin group
	should call \c #AIPluginGroupSuite::MarkPluginArtDirty() while handling the message.
*/
enum AIAttributeOperationSubcodes {
	kHideOpCode				= 'HIDE',
	kShowOpCode				= 'SHOW',
	kLockOpCode				= 'LOCK',
	kUnlockOpCode			= 'UNLK',
	kSetNameOpCode			= 'NAME'
};

/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a plug-in group, never dereferenced.
	Access with \c #AIPluginGroupSuite. */
typedef struct _t_AIClassOpaque *AIPluginGroupHandle;

/** Developer-defined data for \c #AIInterruptProc callback. */
typedef void *AIInterruptData;
/** Callback function prototype for \c #AIPluginGroupMessage::proc.
	An update or interpolate handler that will take a long time can
	call this function any number of times, to give time back to the
	core for other processing (such as preview and other event handling).
	When it returns an error, your handler should stop processing and
	return the error. It will get a chance again later to update.
		@param art The art object.
		@param data Developer-defined data to pass through.
		@return An error to halt processing of the update or interpolate notification.
	*/
typedef ASErr (*AIInterruptProc)( AIArtHandle art, AIInterruptData data );

/** \c #AIPluginGroupMessage::style value.*/
union StyleUnion {
	/** The path style. If partial, the  \c #AIPluginGroupMessage::styleMap
		indicates which fields are valid. */
	AIPathStyle			*path_s;
	/** Unused */
	AIArtStyleHandle	art_s;
};

/** \c #AIPluginGroupMessage::styleMap value.*/
union StyleMapUnion {
	/** A style map that indicates which fields are valid in
		a partial \c #AIPluginGroupMessage::style value. */
	AIPathStyleMap	*path_s_map;
};


/** Sent with the \c #kSelectorAINotifyEdits, \c #kSelectorAIUpdateArt,
	\c #kSelectorAICanShowContents and \c #kSelectorAIInterpolateData notifications.

	The \c #kSelectorAINotifyEdits notifies of edits in the edit group. In this case the \c time
	and \c code members provide more information about the stage of the editing
	operation and the operation being performed. Additional members provide information
	about what is being edited, how it is being edited and the replacement art that will
	be the edited result.<br>
	Process this information and return one of these error codes to control how the operation
	proceeds:
	<br> \c #kRefusePluginGroupReply
	<br> \c #kWantsAfterMsgPluginGroupReply
	<br> \c #kMarkValidPluginGroupReply
	<br> \c #kDontCarePluginGroupReply
	<br> \c #kDestroyPluginGroupReply

	The \c #kSelectorAIUpdateArt message is sent to request that the plug-in group manager
	rebuild the result group in response to edits in the edit group. In this case the
	only the \c proc and \c data fields are used.
*/
struct AIPluginGroupMessage {
	/** The message data.  */
	SPMessageData		d;
	/** The plug-in group object. */
	AIPluginGroupHandle	entry;
	/** The plug-in group art object. */
	AIArtHandle			art;

	/** For \c #kSelectorAINotifyEdits and \c #kSelectorAIInterpolateData
		messages, the stage of the operation (check if allowed, before, during, after). */
	AIOperationTime		time;

	/** For \c #kSelectorAINotifyEdits, the specific operation being performed. */
	AIOperationCode		code;

	// Editing parameters

	/** For \c #kSelectorAINotifyEdits, the descendant of the edit art group that
		is	about to be edited. */
	AIArtHandle			preEditArt;

	/** For \c #kSelectorAINotifyEdits, the object what will be in the edit group when the
		operation completes. For edits that change attributes but keep the same art object
		(such as most style operations), the same as \c preEditArt. At \c #kBeforeOperationTime,
		the attributes have not yet been modified.
		If not the same as \c preEditArt, the object is not in the edit art group until
		\c #kAfterOperationTime. Transformation, geometry changes or attribute changes
		have already been performed on the object, but is has not yet been inserted into the artwork.

		@note You must not dispose of or reorder any artwork objects during a
			\c #kCheckOperationTime or \c #kBeforeOperationTime notification.
			Any editing must wait until \c #kAfterOperationTime. */
	AIArtHandle			postEditArt;

	/** For some operation codes, a subcodes that further describes
		the operation being performed. See \c #AIOperationCode.
		Subcodes are four-byte chars like \c AIErr, that facilitate debugging
		while still allowing switch statements. */
	AIErr				subCode;

	/** For \c #kSelectorAINotifyEdits, supplied if \c code is \c #kTransformOperationCode
		or \c subCode is \c #kTransformCopyOpCode.
		The matrix used for the transformation. */
	AIRealMatrix		matrix;

	/** For \c #kSelectorAINotifyEdits, supplied if \c code is \c #kStyleOperationCode.
		The style that was modified. */
	StyleUnion			style;

	/** For \c #kSelectorAINotifyEdits, supplied if \c code is \c #kStyleOperationCode.
		Indicates which  fields of \c style are valid, if it is a partial style.
		If \c NULL, all style fields are valid. */
	StyleMapUnion		styleMap;

	/** For \c #kSelectorAIUpdateArt and \c #kSelectorAIInterpolateData,
		A callback that allows you to interrupt lengthy processing. */
	AIInterruptProc		proc;

	/** For \c #kSelectorAIUpdateArt and \c #kSelectorAIInterpolateData.
		Developer-defined data to pass through to the \c proc callback. */
	AIInterruptData		data;

	// ----New fields added in AI10-----

	/** For \c #kSelectorAIInterpolateData.
		<br>At \c #kBeforeOperationTime or \c #kAfterOperationTime,
		the number of steps in the blend.
		<br> At \c #kDuringOperationTime, the number of this step (first step is 1). */
	int					steps;

	/** For \c #kSelectorAIInterpolateData.
		<br> The distance of this interpolation between the source and destination
		of the blend. [0..1], where 0 is the source (\c preEditArt) and 1 is
		the destination (\c postEditArt). */
	AIReal				t;

	// Editing parameter

	/** For \c #kSelectorAINotifyEdits, supplied if \c code is \c #kGeometryOperationCode
		and \c subCode is \c #kSwapSymbolsOpCode. In this case, \c art is a symbol
		instance in the edit group, and this is the replacement symbol.
		(If your plug-in group uses symbols in its art dictionary, see also
		\c #kSelectorAIReplaceSymbol.) */
	AIPatternHandle		toSymbol;

	// ----New fields added in AI12----

	/** For \c #kSelectorAINotifyEdits, supplied if \c code is \c #kTransformOperationCode or
		\c subCode is \c #kTransformCopyOpCode. Transformation options,
		a logical OR of \c #AITransformArtOptions. */
	ai::int32 transformFlags;

	/** For \c #kSelectorAINotifyEdits, supplied if \c code is \c #kTransformOperationCode or
		\c subCode is \c #kTransformCopyOpCode.
		If \c transformFlags contains \c #kScaleLines, the factor by which the strokes
		are scaled. */
	AIReal transformLineScale;

	/** For reordering, duplicating, and pasting operations, the preposition object in the paint
		order, for relative placement of the new object. See \c #AIArtSuite::NewArt. */
	AIArtHandle			destinationArt;

	/** For \c #kSelectorAINotifyEdits, supplied for reordering, duplicating and
		pasting operations. The paint-order placement of the new object,
		relative to the \c destinationArt object. Cannot be \c #kPlaceAboveAll
		or \c #kPlaceBelowAll (because the object must go inside a plug-in group).
		Never \c #kPlaceDefault (it is translated into a more specific
		paint order before notification). */
	AIPaintOrder		insertionOrder;

	/** For \c #kSelectorAINotifyEdits, supplied if \c code is \c #kReadOperationCode
		\c #kWriteOperationCode. The version of the Illustrator file
	    being read from or written to. For other operations, the value is 0. */
	AIVersion			aiVersion;

};


/** Data for the \c #kSelectorAIReplaceSymbol notification. */
struct AIReplaceSymbolMessageData {
	/** The message data. */
	SPMessageData		d;
	/** The plug-in group. */
	AIPluginGroupHandle	entry;
	/** The plug-in group art object. */
	AIArtHandle			art;
	/** A symbol to be replaced, referenced by the plug-in group
		in its dictionary, or \c NULL to replace all used symbols. */
	AIPatternHandle		targetSymbol;
	/** The replacement symbol. */
	AIPatternHandle		replacementSymbol;
};


/** Data for the \c #kSelectorAIDisallowsArtTypeQuery notification. */
struct AIPluginArtTypeMessageData {
	/** The message data. */
	SPMessageData		d;
	/** The plug-in group for which insertion is requested. */
	AIPluginGroupHandle	entry;
	/** The \c #AIArtType of art potentially inserted into the group. */
	short				artType;
};


// Function pointers used for callbacks when storing custom hit data
/** A callback that you must supply with the \c #AIPluginGroupCustomHitTestData::CustomHitData,
	that casts the void* data to the appropriate type and disposes of it properly. */
typedef AIAPI void (*AICustomHitDataDeleteFunc)(void*);

/** Data for the \c #kSelectorAIPerformCustomHitTest notification. */
struct AIPluginGroupCustomHitTestData {
	/** The message data. */
	SPMessageData		d;
	/** The plug-in group. */
	AIPluginGroupHandle	entry;
	/** The plug-in group art object that was hit. */
	AIArtHandle			art;
	/** The hit location coordinates. */
	AIRealPoint			location;
	/** A structure in which to record custom hit information.
	   Access after the hit test with \c #AIHitTestSuite::GetCustomHitData() */
	struct
	{
		/** [in] The data that was provided to \c #AIHitTestSuite::CustomHitTest() */
		void*						inData;
		/** [out] Developer-defined custom hit data. Your plug-in is reponsible for
			 allocating and  cleaning up this heap-based data. */
		void*						outData;
		/** [out] A callback function that properly deletes the
			returned custom hit data. Required.*/
		AICustomHitDataDeleteFunc	deleteFunc;
	} CustomHitData;

};


/** Prototype for the \c #AIPluginGroupCollectPaintStylesData::artStyleCallback.
	Can examine, but not modify the art styles and art objects.
		@param artStyle The current art style.
		@param gradientContext \c NULL if gradient vectors in the style are relative
			to the whole plug-in group. Otherwise, gradient vectors in the style are
			relative to this art object.
		@param usage How the style is used (in fills or strokes), an \c #AIPaintUsage value.
		@param callbackData	Developer-defined data passed from the notification message.
	*/
typedef AIAPI ASErr (*AIProcessArtStyleFunc)(const AIArtStyleHandle artStyle,
						AIArtHandle gradientContext, ai::int32 usage, void *callbackData );

/** Prototype for the \c #AIPluginGroupCollectPaintStylesData::pathStyleCallback.
	Can examine, but not modify the path styles and art objects.
		@param pathStyle The current path style.
		@param psMap A style map that identifies the valid fields in a partial style.
			Can be \c NULL.
		@param gradientContext \c NULL if gradient vectors in the style are relative
			to the whole plug-in group. Otherwise, gradient vectors in the style are
			relative to this art object.
		@param usage How the style is used (in fills or strokes), an \c #AIPaintUsage value.
		@param callbackData	Developer-defined data passed from the notification message.
	 */
typedef AIAPI ASErr (*AIProcessPathStyleFunc)(const AIPathStyle *pathStyle, const AIPathStyleMap *psMap,
					AIArtHandle gradientContext, ai::int32 usage, void *callbackData );

/** @ingroup Errors
	Returned by an \c AIProcessArtStyleFunc, \c AIProcessPathStyleFunc, or \c AIAdjustColorFunc
	in non-error situations that nonetheless mean the iteration should be terminated
	without processing any remaining styles. This could be used, for instance, if the
	callback functions were searching for a particular global object and could quit
	as soon as it appeared. */
#define kIterationCanQuitReply			'DONE'

/** Data for the \c #kSelectorAICollectPaintStyles notification. */
struct AIPluginGroupCollectPaintStylesData {
	/** The message data. */
	SPMessageData		d;
	/** The plug-in group. */
	AIPluginGroupHandle	entry;
	/** The plug-in group art object whose style contents are being queried */
	AIArtHandle			pluginArt;
    /** True to iterate only selected styles. (Currently always true.) */
	AIBoolean			selectedOnly;
	/** Developer-defined data to pass through to the callbacks. */
	void* callbackData;
	/** A callback function that examines the art styles in the plug-in art. */
	AIProcessArtStyleFunc artStyleCallback;
	/** A callback function that examines the path styles in the plug-in art. */
	AIProcessPathStyleFunc pathStyleCallback;

};

/** Data for the \c #kSelectorAIApplyPaintStyles message. */
struct AIPluginGroupApplyPaintStylesData {
	/** The message data. */
	SPMessageData		d;
	/** The plug-in group. */
	AIPluginGroupHandle	entry;
	/** The plug-in group art object whose style contents are being modified */
	AIArtHandle			pluginArt;

	/** When true, apply a transformation using \c matrix, \c transformFlags,
		and \c transformLineScale, and ignore \c pathStyle and \c pathStyleMap.
		<br> When false, merge styles using \c pathStyle and \c pathStyleMap, and ignore
		\c matrix, \c transformFlags, and \c transformLineScale. */
	AIBoolean			applyStyleTransform;

	/** Fill and stroke information to be merged into the current style. */
	AIPathStyle			pathStyle;
	/** A style map the indicates which fields are valid in a partial path style.  */
	AIPathStyleMap		pathStyleMap;

	/** The transformation matrix. */
	AIRealMatrix		matrix;
	/**	Transformation options, a logical OR of \c #AITransformArtOptions.
		\c #kTransformObjects and \c #kTransformChildren are always off,
		and at least one of \c #kTransformFillGradients, \c #kTransformFillPatterns,
		\c #kTransformStrokePatterns, \c #kTransformStrokeGradients, or \c #kScaleLines is on. */
	ai::int32				transformFlags;
	/** If the \c #kScaleLines option is on, the factor by which to scale the strokes. */
	AIReal				transformLineScale;

};


/** Callback function prototype used to process colors from art style handles
	directly contained in the dictionary of a plug-in group. Passed to \c #kSelectorAIAdjustColors
	in \c #AIPluginGroupAdjustColorsData::adjustArtStyleCallback.
	Allows various concerned plug-ins to work with the contained styles:

	\li The plug-in with art style handles in its dictionary can use this to find those art styles,
	\li Another plug-in that implements the effects inside the art styles can use it to access their colors.
	\li Another plug-in can provides the color-adjustment callback to do the actual color mapping.

	This callback is not typically provided by a third-party plug-in, but is provided internally
	by the implementation of \c #AIPathStyleSuite::AdjustObjectAIColors(), or by
	\c #AIPluginGroupSuite::PluginArtAdjustColors(). A plug-in groups with art styles
	in its dictionary need only call this callback, not implement it.
		@param oldArtStyle The art style to be examined. It is not altered.
		@param newArtStyle [out] A buffer in which to return the art style after color adjustment.
			If no colors are changed, contains the input style.
		@param userData A pointer to developer-defined data needed for the modification,
			acquired from the message data.
	*/
typedef AIErr (*AIAdjustArtStyleFunc) ( AIArtStyleHandle oldArtStyle, AIArtStyleHandle *newArtStyle, void *userData );

/** Data for the \c #kSelectorAIAdjustColors notification. */
struct AIPluginGroupAdjustColorsData {
	/** The message data. */
	SPMessageData		d;
	/** The plug-in group. */
	AIPluginGroupHandle	entry;
	/** The plug-in group art object whose style contents are being modified. */
	AIArtHandle			pluginArt;				// IN

	/** When true, iterate only selected colors.In this case, the plug-in group
		was at least partially selected in object selection mode. */
	AIBoolean			selectedOnly;
	/** When true, iterate colors used in fills. */
	AIBoolean			adjustFills;
	/** When true, iterate colors used in strokes. */
	AIBoolean			adjustStrokes;
	/** Developer-defined data to pass through to the callback.
		Can contain extra parameters needed by the color mapping.*/
	void*				callbackData;

	/** A developer-defined callback function that processes colors. Call on any colors
		that are directly contained in the plug-in group's private data; that is, not contained
		 within an \c #AIArtStyleHandle, \c #AIPatternHandle, or an \c #AIArtHandle. */
	AIAdjustColorFunc	adjustColorCallback;

	/** [out] Set to true if the handler modified any colors. */
	AIBoolean			modifiedSomething;

	/** A developer-defined callback function to examine or modify colors contained
		in patterns, symbols, brush patterns or graph designs. Called on objects of these
		types that may contain meaningful colors and that are directly stored in the
		plug-in group's private data; that is, not contained within an
		\c #AIArtStyleHandle, \c #AIPatternHandle, or an \c #AIArtHandle.
		Fill patterns, for example, are usually stored in an \c #AIColor, and
		brush patterns are usually stored in an \c #AIArtStyleHandle.
		You will typically call this for symbol handles that are stored independently
		of symbol instances.

		The function does not modify the input pattern. It returns a processed
		handle of the same type, which the plug-in group should store if it is
		different from the input handle.
		*/
	AIAdjustPatternHandleFunc adjustPatternHandleCallback;

	/** A developer-defined callback function to examine or modify colors contained
		in art styles, including the private parameters of Live Effects.
		Call on any art style handles that are directly stored in the plug-in group's
		private data; that is, not attached to any art object.

		The function does not modify the input style. It returns a processed
		art style, which the plug-in group should store if it is
		different from the input handle.
		 */
	AIAdjustArtStyleFunc adjustArtStyleCallback;

};

/*** Descriptive information for a new plug-in group.
	See \c #AIPluginGroupSuite::AddAIPluginGroup().*/
struct AIAddPluginGroupData {
	/** Major version number. */
	ai::int32				major;
	/** Minor version number. */
	ai::int32				minor;
	/** Localized descriptive string for error messages. */
	const char				*desc;
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides functions for working with \e plug-in \e groups.

	A plug-in group organizes artwork that is acted upon by a particular plug-in.
	A plug-in group object is a container of plug-in group art objects.
	It maintains two groups of art objects; one group that the user interacts
	with (the \e edit \e group), and another group that your plug-in generates
	(the \e result \e group). Use the functions in this suite to create
	these groups and to access their contents.

	Register a plug-in group during startup to manage plug-in group art objects
	of a particular type, using \c #AIPluginGroupSuite::AddAIPluginGroup().
	Store the returned plug-in group handle in \c globals, to use in
	creating plug-in group art objects. All plug-in group art objects
	must associate themselves with a plug-in group by calling
	\c #AIPluginGroupSuite::UseAIPluginGroup().

 	A plug-in group art object is an art object with the type \c #kPluginArt. The
 	edit art group and result art group are art objects with the type
	\c #kGroupArt, but they are not children of the plug-in group art object.
	Access them with \c #AIPluginGroupSuite::GetPluginArtEditArt() and
	\c #AIPluginGroupSuite::GetPluginArtResultArt().
		\li Members of the edit group are hidden, but are editable and selectable.
		\li Members of the result group become visible, but are not selectable.

	You can define and store arbitrary data with a plug-group art object, using
	\c #AIPluginGroupSuite::SetPluginArtDataRange(),
	\c #AIPluginGroupSuite::GetPluginArtDataRange(),
	\c #AIPluginGroupSuite::SetPluginArtDataCount(),
	and  \c #AIPluginGroupSuite::GetPluginArtDataCount().

	A plug-in that manages plug-in groups can receive these selectors,
	with \c #kCallerAIPluginGroup as the caller, accompanied by
	an \c #AIPluginGroupMessage:
	<br> \c #kSelectorAINotifyEdits
	<br> \c #kSelectorAIUpdateArt
	<br> \c #kSelectorAICanShowContents
	<br> \c #kSelectorAIInterpolateData

	It can also receive these selectors:
	<br> \c #kSelectorAIReplaceSymbol (sends \c #AIReplaceSymbolMessageData)
	<br> \c #kSelectorAIDisallowsArtTypeQuery (sends \c #AIPluginArtTypeMessageData)
	<br> \c #kSelectorAIPerformCustomHitTest (sends \c #AIPluginGroupCustomHitTestData)
	<br> \c #kSelectorAICollectPaintStyles (sends \c #AIPluginGroupCollectPaintStylesData)
	<br> \c #kSelectorAIApplyPaintStyles (sends \c #AIPluginGroupApplyPaintStylesData)
	<br> \c #kSelectorAIAdjustColors (sends \c #AIPluginGroupAdjustColorsData)

	The Live Blend tool is an example of how plug-in groups are used.
	A live blend is created by drawing two objects, then clicking them
	separately with the blend tool. After the second click, the tool draws
	a series of intermediate objects between the original source and destination
	objects to create a smooth blend between them. Only the source and destination
	objects are selectable or editable. When you edit or move the source or
	destination objects, the intermediate objects are regenerated. The document
	contains only the original two objects in the art tree.
	In this case, the source and destination art objects (as well as the spine
	which links the two objects) are children of the edit group, and the intermediate
	objects (as well as a copy of the original source and destination objects) are
	children of the result group.


  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPluginGroupSuite and \c #kAIPluginGroupVersion.

	@section Plug-in Group Example

	First, register the plug-in group:

@code
sAIPluginGroup->AddAIPluginGroup (
	message->d.self,
	"My Plugin Group Plugin",
	&pluginGroupData,
	kPluginGroupWantsAutoTransformOption,
	&g->myPluginGroupHandle
	);
@endcode

	Create the plug-in group art, typically in response to a menu item or a click
	in your dialog, then associate the plug-in group art with the plug-in group.

@code
sAIArt->NewArt( kPluginArt, kPlaceAboveAll, NULL, &pluginGroupArt );
sAIPluginGroup->UseAIPluginGroup (pluginGroupArt, g->myPluginGroupHandle );
@endcode

	This activates the plug-in group art and allows you to access
	its edit and result groups.

	Upon activation, your plug-in starts to receive notifications.
	In response to \c #kSelectorAIUpdateArt or \c #kSelectorAINotifyEdits
	notifications, you must regenerate the objects in the result group
	The update message is the easiest and most effective notifier to use.
	It is sent whenever any of the edit-group objects are modified.
	In your main loop, listen for the \c #kCallerAIPluginGroup caller
	and \c #kSelectorAIUpdateArt selector and respond by regenerating the
	result-group objects according to the new state of the edit-group objects.
 */
struct AIPluginGroupSuite {

	/** Creates a plug-in group.
			@param self This plug-in.
			@param name A unique identifying name for the plug-in group.
				This name is displayed in error messages, and differs
				from the \e default name used in the Layers
				and Appearance palettes; see \c #SetAIPluginGroupDefaultName().
			@param data The version and error-reporting information for the group.
			@param options Option flags that determine the behavior of members,
				a logical OR of \c #AIPluginGroupOptions. You cannot change these
				after they are set.
			@param entry [out] A buffer in which to return the plug-in group object.
		*/
	AIAPI AIErr (*AddAIPluginGroup) ( SPPluginRef self, const char *name, AIAddPluginGroupData *data, ai::int32 options, AIPluginGroupHandle *entry );

	/** Associates a plug-in group art object with a plug-in group, activating
		the plug-in group and automatically creating the contained edit and
		result groups. After calling this function, your plug-in starts to
		receive plug-in group selectors.

 		You can only access the edit and result groups through this art object;
 		see \c #GetPluginArtEditArt() and \c #GetPluginArtResultArt().

 		The art object inherits the plug-in group's name and version attributes,
 		which you can then access either through the group (\c #GetAIPluginGroupName(),
 		for example) or the art object (\c #GetPluginArtName()). The plug-in group
		name is used for error messages, and differs from the art object's name,
		used in the Layers and Appearance palettes; see \c #GetAIPluginGroupDefaultName().

		You can move the art object to a new plug-in group with \c #SetPluginArtPluginGroup().
        	@param art An art object of type \c #kPluginArt, created with \c #AIArtSuite::NewArt().
			@param entry The plug-in group object.
	*/
	AIAPI AIErr (*UseAIPluginGroup) ( AIArtHandle art, AIPluginGroupHandle entry );

	/** Retrieves the name of a plug-in group. This name is displayed in error messages,
		and can differ from the display name (called the \e default name) used in
		the Layers and Appearance palettes; see \c #GetAIPluginGroupDefaultName().
			@param entry The plug-in group object.
			@param name [out] A buffer in which to return the name.
		*/
	AIAPI AIErr (*GetAIPluginGroupName) ( AIPluginGroupHandle entry, char **name );

	/** Retrieves the version information of a plug-in group.
			@param entry The plug-in group object.
			@param major [out] A buffer in which to return the major version number.
			@param minor [out] A buffer in which to return the minor version number.
		*/
	AIAPI AIErr (*GetAIPluginGroupVersion) ( AIPluginGroupHandle entry, ai::int32 *major, ai::int32 *minor );

	/** Retrieves the description of a plug-in group, a localized string that Illustrator
		uses for error reporting.
			@param entry The plug-in group object.
			@param desc [out] A buffer in which to return the description.
		*/
	AIAPI AIErr (*GetAIPluginGroupDescription) ( AIPluginGroupHandle entry, char **desc );

	/** Retrieves the option flags of a plug-in group.
			@param entry The plug-in group object.
			@param options [out] A buffer in which to return the options, a logical OR
				of \c #AIPluginGroupOptions.
		*/
	AIAPI AIErr (*GetAIPluginGroupOptions) ( AIPluginGroupHandle entry, ai::int32 *options );

	/** Retrieves a reference to the plug-in that created a plug-in group.
		You can pass this reference to functions in the \c #AIPluginSuite.
			@param entry The plug-in group object.
			@param plugin [out] A buffer in which to return the plug-in object.
		*/
	AIAPI AIErr (*GetAIPluginGroupPlugin) ( AIPluginGroupHandle entry, SPPluginRef *plugin );

	/** Gets the number of currently registered plug-in group managers. Use with
		\c #GetNthAIPluginGroup() to iterate through plug-in groups (which can belong
		to different plug-ins).
			@param count [out] A buffer in which to return the number of groups.
		*/
	AIAPI AIErr (*CountAIPluginGroups) ( ai::int32 *count );

	/** Retrieves a reference to a plug-in group by position index in the current list
		of registered plug-in group managers. Use with \c #CountAIPluginGroups to
		iterate through plug-in groups (which can belong to different plug-ins).
        	@param n The 0-based index position.
			@param entry [out] A buffer in which to return the plug-in group object.
		*/
	AIAPI AIErr (*GetNthAIPluginGroup) ( ai::int32 index, AIPluginGroupHandle *entry );

	/** Retrieves the name of the plug-in group that manages a plug-in group art object.
			@param art The plug-in group art object.
			@param name [out] A buffer in which to return the plug-in group name.
		*/
	AIAPI AIErr (*GetPluginArtName) ( AIArtHandle art, char **name );

	/**  Sets the name of the plug-in group that manages a plug-in group art object.
			@param art The plug-in group art object.
			@param name The new unique identifying name for the plug-in group. */
	AIAPI AIErr (*SetPluginArtName) ( AIArtHandle art, char *name );

	/** Retrieves the version information for the plug-in group that manages
		a plug-in group art object.
			@param art The plug-in group art object.
			@param major [out] A buffer in which to return the major version number.
			@param minor [out] A buffer in which to return the minor version number.
		*/
	AIAPI AIErr (*GetPluginArtVersion) ( AIArtHandle art, ai::int32 *major, ai::int32 *minor );

	/** Sets the version information for the plug-in group that manages
		a plug-in group art object.
			@param art The plug-in group art object.
			@param major The new major version number.
			@param minor The new minor version number.
		*/
	AIAPI AIErr (*SetPluginArtVersion) ( AIArtHandle art, ai::int32 major, ai::int32 minor );

	/** Retrieves the plug-in group that manages a plug-in group art object.
			@param art The plug-in group art object.
			@param entry [out] A buffer in which to return the plug-in group object.
		*/
	AIAPI AIErr (*GetPluginArtPluginGroup) ( AIArtHandle art,  AIPluginGroupHandle *entry );

	/** Sets the plug-in group that manages a plug-in group art object.
			@param art The plug-in group art object.
			@param entry The new plug-in group object.
		*/
	AIAPI AIErr (*SetPluginArtPluginGroup) ( AIArtHandle art );

	/** Retrieves the edit group art object from the plug-in group art object.
			@param art The plug-in group art object.
			@param editArt [out] A buffer in which to return the edit group art object.

	  		@note The edit group art object is \e not a child of the
				the plug-in group art object. You can access it with this function,
				and it can be returned by \c #AIMatchingArtSuite::GetSelectedArt(), which
				can also return the plug-in group art object itself. <br>
				\c #AIMatchingArtSuite::GetSelectedArt() or \c #AIMatchingArtSuite::GetMatchingArt()
				can return objects in the edit group.
	*/
	AIAPI AIErr (*GetPluginArtEditArt) ( AIArtHandle art, AIArtHandle *editArt );

	/** Replaces the edit group of a plug-in group art object.
			@param art The plug-in group art object.
			@param editArt The new edit group object, an art object of type \c #kGroupArt.
	*/
	AIAPI AIErr (*SetPluginArtEditArt) ( AIArtHandle art, AIArtHandle editArt );

	/** Retrieves the result group art object from the plug-in group art object.
			@param art The plug-in group art object.
			@param resultArt [out] A buffer in which to return the result group art object.

	  		@note The result group art object is \e not a child of the
				the plug-in group art object. You can access it only with this function.
		*/
	AIAPI AIErr (*GetPluginArtResultArt) ( AIArtHandle art, AIArtHandle *resultArt  );

	/** Replaces the result group of a plug-in group art object.
			@param art The plug-in group art object.
			@param resultArt The new result group object, an art object of type \c #kGroupArt.
		*/
	AIAPI AIErr (*SetPluginArtResultArt) ( AIArtHandle art, AIArtHandle resultArt  );

	/** Gets the size of the developer-defined data store for a plug-in group art object.
		Store data using \c #SetPluginArtDataRange(), and access it with \c #GetPluginArtDataRange().
		The data is stored as a hexadecimal-encoded string of bytes.
			@param art The plug-in group art object.
			@param count [out] A buffer in which to return the number of bytes of data
				stored, or 0 if there is no data associated with the art object.
		*/
	AIAPI AIErr (*GetPluginArtDataCount) ( AIArtHandle art, size_t *count );

	/** Sets the size of the developer-defined data store for a plug-in group art object.
		Store data using \c #SetPluginArtDataRange(), and access it with \c #GetPluginArtDataRange().
		The data is stored as a hexadecimal-encoded string of bytes.
			@param art The plug-in group art object.
			@param count The number of bytes of data.
		*/
	AIAPI AIErr (*SetPluginArtDataCount) ( AIArtHandle art, size_t count );

	/** Retrieves data from the developer-defined data store for a plug-in group art object.
		The data is stored as a hexadecimal-encoded string of bytes.
			@param art The plug-in group art object.
			@param data [out] A buffer in which to return the data.
			@param index An offset into the data store at which to start reading.
			@param count A number of bytes to read from the data store.
	 	*/
	AIAPI AIErr (*GetPluginArtDataRange) ( AIArtHandle art, void *data, size_t index, size_t count );

	/** Writes data to the developer-defined data store for a plug-in group art object.
		The data is stored as a hexadecimal-encoded string of bytes.
			@param art The plug-in group art object.
			@param data A pointer to the developer-defined data.
			@param index An offset into the data store at which to start writing.
			@param count A number of bytes to write to the data store.
		*/
	AIAPI AIErr (*SetPluginArtDataRange) ( AIArtHandle art, void *data, size_t index, size_t count );


	/** Marks a plug-in group art object as dirty, meaning that the contained art has
		been modified since the last update operation. This forces an update notification;
		see \c #kSelectorAIUpdateArt.

		Illustrator generally detects when a plug-in group object needs
		to have the result art rebuilt. It sends an update message when
		the object is first created, and whenever the group's data or any object
		in the edit group has been edited (outside of the update message handler itself).
		You might need to specifically mark the art as changed if objects have external
		dependencies; for instance, reference to a pattern or other global object,
		or an artwork attribute such as the page size. If you detect relevant changes
		through other notifications, you can trigger an update by calling this function.
			@param art The plug-in group art object.
			@see \c #MarkPluginArtClean(), \c #MarkPluginArtSilent()
		*/
	AIAPI AIErr (*MarkPluginArtDirty) ( AIArtHandle art );

	/** Marks a plug-in group art object as clean, meaning that the contained art has
		not been modified since the last update operation.

		A menu command or tool action typically modifies the edit art or the
		object's data, then rebuilds the result art. The modifications trigger
		a notify-edit message, and also mark the plug-in object dirty, causing
		a redundant update if the result art has already been updated.
		Use this function in an external notification handler, after updating
		the result group, to prevent the redundant update.

			@param art The plug-in group art object.
			@see \c #MarkPluginArtDirty(), \c #MarkPluginArtSilent()
			@note This function is intended for use within a GoMenu or AITool handler, or a notification
				from some other suite. When a handler for \c #kSelectorAINotifyEdits
				returns \c #kNoErr, it marks the plug-in object as dirty (in need of
				\c #kSelectorAIUpdateArt), even if the handler called this function. To prevent
				this, the handler must return \c #kMarkValidPluginGroupReply.
		*/
	AIAPI AIErr (*MarkPluginArtClean) ( AIArtHandle art );

	// New for AI10: clipping attribute for plug-in group objects

	/** Reports whether a plug-in group art object is a clipping object. When it is,
		the result group constructed by the plug-in group manager should
		contain one or more paths that are set to clip.
			@param art The plug-in group art object.
			@param clipping [out] A buffer in which to return true if the object
				is a clipping object.
		*/
	AIAPI AIErr (*GetPluginArtClipping) ( AIArtHandle art, AIBoolean *clipping );

	/** Sets the clipping state of a plug-in group art object.
			@param art The plug-in group art object.
			@param clipping True to make the object a clipping object, false to
				turn clipping off.
			@return \c #kBadParameterErr if the associated group does not specify the option
				\c #kPluginGroupCanBeClipping.
		*/
	AIAPI AIErr (*SetPluginArtClipping) ( AIArtHandle art, AIBoolean clipping );

	/** Retrieves the default name for a plug-in group, as returned by
		\c #AIArtSuite::GetArtName(). This name is used in
		the Layers and Appearance palettes, and can differ from the name
		assigned at creation, which is displayed in error messages;
		see \c #GetAIPluginGroupName().
			@param art The plug-in group object.
			@param name [out] A buffer in which to return the default name, or \c NULL,
				in which case \c #AIArtSuite::GetArtName() returns the description string.
		*/
	AIAPI AIErr (*GetAIPluginGroupDefaultName) ( AIPluginGroupHandle entry, char** name );

	/** Sets the default name for a plug-in group, as returned by
		\c #AIArtSuite::GetArtName(). This name is used in
		the Layers and Appearance palettes, and can differ from the name
		assigned at creation, which is displayed in error messages;
		see \c #GetAIPluginGroupName().
			@param entry The plug-in group object.
			@param name The new default name, or \c NULL,  in which case \c #AIArtSuite::GetArtName()
				returns the description string.
		*/
	AIAPI AIErr (*SetAIPluginGroupDefaultName) ( AIPluginGroupHandle entry, const char* name );

	/** Retrieves the earliest Illustrator version that this plug-in group supports.
			@param entry The plug-in group object.
			@param appVersion [out] A buffer in which to return the version constant.
			@see \c #SetAIPluginGroupAppVersion()
		*/
	AIAPI AIErr (*GetAIPluginGroupAppVersion) ( AIPluginGroupHandle entry, AIVersion* appVersion );

	/** Sets the earliest Illustrator version that this plug-in group supports.
		When Illustrator writes out this plug-in group, if writing to an earlier file
		format, it writes out only the result group.

		If not specifically set, the version default is 8.	Plug-in groups are not supported in versions
		earlier than 8.
			@param entry The plug-in group object.
			@param appVersion The version constant.
		*/
	AIAPI AIErr (*SetAIPluginGroupAppVersion) ( AIPluginGroupHandle entry, AIVersion appVersion );

	// New for AI12:

	/** Prevents subsequent modifications to the edit group from marking the object dirty (changed) and
		triggering the update notification.	Does not prevent the marking of the result group.
		The status is cleared when the context is popped.
			@param art The plug-in group art object.
			@see \c #MarkPluginArtClean(), \c #MarkPluginArtDirty()
	*/
	AIAPI AIErr (*MarkPluginArtSilent) ( AIArtHandle art );

	/**	@deprecated As of AI13 (CS3), this function is deprecated in favor of
		\c #AIPathStyleSuite::AdjustObjectAIColors(), a more powerful and flexible treatment
		of colors in global objects such as patterns, gradients, symbols, brushes, and
		Live Effects. Color filter plug-ins	that iterate the artwork contents themselves
		and only use this function for plug-in groups with that have the flag
		\c #kPluginGroupManagesPaintStyles, should now use \c #AIPathStyleSuite::AdjustObjectAIColors()
		to process the entire selection. In this case, the new function emulates
		the previous behavior; it sends an c\ #AIPluginGroupAdjustColorsData
		message in which both the pattern and style adjustment callbacks do nothing.

		Modifies colors in all art managed by a plug-in group, by calling a developer-defined callback function.
			@param art The plug-in group art object.
			@param adjustColorCallback The developer-defined callback procedure.
			@param callbackData Optional developer-defined data to pass through to the callback.
			@param modifiedSomething [out] Optional, a buffer in which to return true if any
				colors were modified.
			@param adjustFills True to modify colors in fill.
			@param adjustStrokes True to modify colors in strokes.
			@param selectionOnly True to modify colors only in selected objects.
			@return Any error reported by the callback function.
			@note This function s intended for the use of plug-ins \e other \e than
				the one implementing the plug-in group.
	*/
	AIAPI AIErr (*PluginArtAdjustColors) ( AIArtHandle art, AIAdjustColorFunc adjustColorCallback,
											void *callbackData, ASBoolean *modifiedSomething,
											AIBoolean adjustFills, AIBoolean adjustStrokes,
											AIBoolean selectionOnly );

};


#include "AIHeaderEnd.h"

#endif

