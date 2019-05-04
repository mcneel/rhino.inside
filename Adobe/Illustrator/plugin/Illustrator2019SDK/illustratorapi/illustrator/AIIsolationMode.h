#ifndef __AIIsolationMode__
#define __AIIsolationMode__

/*
 *        Name:	AIIsolationMode.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Isolation Mode Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2006-2016 Adobe Systems Incorporated.
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

#ifndef __AIMdMemory__
#include "AIMdMemory.h"
#endif

#ifndef _IAIAUTOBUFFER_H_
#include "IAIAutoBuffer.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIIsolationMode.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAIIsolationModeSuite				"AI Isolation Mode"
#define kAIIsolationModeSuiteVersion6		AIAPI_VERSION(6)
#define kAIIsolationModeSuiteVersion		kAIIsolationModeSuiteVersion6
#define kAIIsolationModeVersion				kAIIsolationModeSuiteVersion


/*******************************************************************************
 **
 **	Constants
 **
 **/

/** @ingroup Errors
 The requested isolation mode cannot be entered because the document is already in a mode that does not allow it.
 E.g., editing a symbol instance while in Pattern Editing Mode, or isolating anything while in Opacity Mask mode. */
#define kCantIsolateFromCurrentModeErr '!Iso'

/** @ingroup Notifiers
 (Internal, do not use) Sent after isolation-mode focus changes from one art object to another.
 See \c #AIIsolationModeSuite 
 Not sent when changes are a result of Undo or Redo actions. 
 */
#define kAIIsolationModeChangedNotifier	"AI Isolation Mode Changed Notifier"

/** @ingroup Notifiers
 (Internal, do not use) Sent just before isolation-mode focus changes from one art object to another.
 See \c #AIIsolationModeSuite 
 Not sent when changes are a result of Undo or Redo actions. 
 */
#define kAIBeforeIsolationModeChangedNotifier	"AI Before Isolation Mode Changed Notifier"


/*******************************************************************************
 **
 **	Types
 **
 **/


/** (Internal, do not use) Data sent with \c #kAIIsolationModeChangedNotifier.  */
typedef struct {
	/** True if notification was caused by entering isolation mode. False if it was caused by
		exiting isolation mode. */
	AIBoolean inIsolationMode;
	/** The isolated art object. */
	AIArtHandle isolatedArt;
	/** The parent of the isolated art. */
	AIArtHandle isolatedArtParent;
	/** True if Symbol or Pattern editing mode was exited via a Cancel operation. */
	AIBoolean canceled;
} AIIsolationModeChangedNotifierData;



/** The kind of art that is isolated. Type constants returned from
\c #AIIsolationModeSuite::GetIsolationModeType() 
*/
enum AIIsolationModeType
{
	/** One leaf artwork (not a container) is isolated. */
	kAIIMLeafArt        = 1,  

	/** One group or plugin group is isolated.
		Also used for Pattern editing mode, since the pattern editor is a plugin group.
		Use \c #AIPatternSuite::GetPatternEditMode() to detect the latter condition. */
	kAIIMGroup, 

	/** One or more clipping paths (masking object) are isolated. */             
	kAIIMClippingObjects, 

	/** One compound path is isolated. */   
	kAIIMCompoundPath,  

	/** One top-level layer is isolated. */     
	kAIIMTopLevelLayer, 

	/** One sublayer is isolated. */     
	kAIIMSubLayer,

	/** Symbol editing mode is active. */
	kAIIMSymbol,    

	/** Sibling artworks are present in isolation mode (i.e. "Isolation Mode" layer has more than one children.) */
	kAIIMObjects,  

	/** Art is in isolation mode, but all the isolated artworks are deleted. */
	kAIIMNoObject,

	/** Art is not in isolation mode. */       
	kAIIMNone            
};

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions that handle isolation mode, in which an artwork selection
	is moved onto a special isolation layer for editing, and that isolation layer (and any
	contents) becomes the only layer displayed in the Layers panel or accessible to edits.
	See \c #AILayerListSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIIsolationModeSuite and \c #kAIIsolationModeVersion.
*/
typedef struct {

	/** Enters isolation mode for a specific group or plug-in group. This art becomes
		the isolated art, replacing any art that was previously isolated. In this mode,
		the user can edit only the isolated art.

		While the art is isolated, \c #AIArtSuite::GetArtParent() returns the layer group
		of the temporary isolation layer; use \c #GetIsolatedArtAndParents() instead to
		retrieve the pre-isolation parent.
			@param art The group or plug-in group art object. Can be in the main art tree
				or in an isolated art tree. Cannot be art inside a dictionary or plug-in group.
			@param invisibleFlag  When true, artwork that is not isolated is made invisible.
			    When false, non-isolated artwork is dimmed.
		*/
	AIAPI AIErr (*EnterIsolationMode)(AIArtHandle art, AIBoolean invisibleFlag);

	/** Exits isolation mode and returns to normal editing mode. Any art on the isolation
		layer is reordered to where the art object passed to \c #EnterIsolationMode() was
		originally located in the art tree. (It is therefore valid to delete the
		isolated art or add additional objects before exiting isolation mode.) After
		restoring the parent chain, a \c #kAIIsolationModeChangedNotifier is sent with
		canceled as false.
		See also \c #CancelIsolationMode().
	*/
	AIAPI AIErr (*ExitIsolationMode)(void);

	/** Retrieves the original parent and ancestors of an isolated artwork tree; that is,
		the pre-isolation parent of a group, plugin-group or other art that has been passed
		to \c #EnterIsolationMode().
		(Note that this function does not return an error code.)
			@param isolatedArtParent [out] A buffer in which to return the parent
				art object of the isolated art tree.
			@param parentChain [out] Optional. A buffer in which to return an array of
				0 or more art objects (\c #AIArtHandle) for the ancestors of the
				parent art object.
		*/
	AIAPI void (*GetIsolatedArtAndParents)(AIArtHandle *isolatedArtParent, ai::AutoBuffer<AIArtHandle> *parentChain);

	/** Reports whether isolation mode is in effect.
		(Note that this function returns a boolean value, not an error code.)
			@return True if isolation mode is on, false if it is off.
		*/
	AIAPI ASBoolean (*IsInIsolationMode)(void);

	/** Reports whether artwork is in the isolated layer.
		(Note that this function returns a boolean value, not an error code.)
			@param art The parent art object of the art tree.
			@return True if the artwork is in the isolated layer, false otherwise.
		*/
	AIAPI ASBoolean (*IsIsolatedLayer)(AIArtHandle art);

	/** Reports whether artwork is in a non-isolated layer. Non-isolated art layers
		hold the artwork that is not being edited in isolation mode. Non-isolated artwork
		can be shown in a 50% opacity state in isolation mode, or can be hidden entirely
		when in symbol editing mode or pattern editing mode. The Layers panel uses this
		function to exclude non-isolated layers from the panel list.
		(Note that this function returns a boolean value, not an error code.)
			@param art The parent art object of the art tree.
			@return True if the artwork is in a non-isolated layer, false otherwise.
		*/
	AIAPI ASBoolean (*IsNonIsolatedLayer)(AIArtHandle art);

	/** Reports whether an art tree is a legal target for isolation mode.
		Art that cannot be isolated includes, for example, art that is inside a
		plug-in group or dictionary, text art or guides, art that is locked or hidden,
		template layers, and the temporary isolation layer of an object already in
		isolation mode. If art is null, returns whether it is legal to enter isolation
		mode in general. (Under some conditions it is invalid to enter isolation mode
		on anything, such as when already in mask editing mode.)
			@param art The parent art object of the art tree, or null.
			@return True if the artwork can be isolated or if it is
				already isolated, false otherwise.
		*/
	AIAPI ASBoolean (*CanIsolateArt)(AIArtHandle art);

	/** Reports the type art in Isolation Mode.
			@return The type of isolation Mode, an \c #AIIsolationModeType constant
		*/
	AIAPI AIIsolationModeType (*GetIsolationModeType)();

	/** Identical to \c #ExitIsolationMode(), except that after restoring the parent chain,
		a \c #kAIIsolationModeChangedNotifier message is sent with canceled as true.
		For normal isolation mode, there is no difference in behavior, since even
		when canceled, any changes made in isolation mode are not rolled back.
		For Symbol editing mode and Pattern editing mode, the symbol or pattern is
		ordinarily redefined during handling of the \c #kAIIsolationModeChangedNotifier.
		Canceling causes the redefinition not to occur.
	 */
	AIAPI AIErr (*CancelIsolationMode)(void);
	
	/** Sets the opacity value applied to the non-isolated art layers.
			@param inNewOpacity The new opacity value, in the range [0..1] where 0 is
	 			completely transparent and 1 is completely opaque.
		*/
	AIAPI AIErr (*SetNonIsolatedArtLayerOpacity)(const AIReal inNewOpacity);
	
	/** Gets the current opacity value applied to the non-isolated art layers.
		Note that this function returns a numeric opacity value, not an error code.
			@return The new opacity value, in the range [0..1] where 0 is completely
	 			transparent and 1 is completely opaque.
		*/
	AIAPI AIReal (*GetNonIsolatedArtLayerOpacity)();

	/** Gets the art handle from the artwork which needs to be isolated.
			@param art [out] The art handle corresponding to the artwork that needs to be
				passed to \c #EnterIsolationMode().
		*/
	AIAPI AIErr(*GetArtToIsolate) (AIArtHandle &art);

} AIIsolationModeSuite;


#include "AIHeaderEnd.h"


#endif
