#pragma once

/*
 *        Name:	AITool.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Tool Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2017 Adobe Systems Incorporated.
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
#include "AIEvent.h"
#include "AIFixedMath.h"
#include "AIPlugin.h"
#include "AIToolNames.h"
#include "ASHelp.h"
#include "AIColor.h"

#ifndef FLT_MAX
#include <float.h>
#endif

#include "AIHeaderBegin.h"

/** @file AITool.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIToolSuite			"AI Tool Suite"
#define kAIToolSuiteVersion18	AIAPI_VERSION(18)
#define kAIToolSuiteVersion		kAIToolSuiteVersion18
#define kAIToolVersion			kAIToolSuiteVersion

/** @ingroup Notifiers
   	Sent when effective tool is changed, either permanently or temporarily
	using modifier keys (such as Cmd, Cntl, or Spacebar). Data is
	\c #AIEffectiveToolChangeData.
	Replaces individual notifiers for tool suspend and resumes actions that have
	been deprecated.
	@note	This notifier is not sent during application startup. */
#define kAIEffectiveToolChangedNotifier			"AI Effective Tool Changed Notifier"

/** @deprecated	Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when a property of a plug-in tool is changed, such as
	its options, title, icon, or tooltip. */
#define kAIUserToolChangedNotifier		"AI User Tool Changed Notifier"
/** @ingroup Notifiers
	Sent when a tool is selected. The data is the \c #AIToolHandle.
	Reselection of an already selected tool sends both
	\c #kAIToolDeselectedNotifier and \c #kAIToolSelectedNotifier
	with the \c #kSelectorAIReselectTool message. */
#define kAIToolSelectedNotifier			"AI Tool Selected Notifier"
/** @ingroup Notifiers
	Sent when a tool is deselected. The data is the \c #AIToolHandle. */
#define kAIToolDeselectedNotifier		"AI Tool Deselected Notifier"
/** @ingroup Notifiers
	Send to notify tools to invalidate their current view when a scroll
	is happening on the document */
#define kAIInvalidateByScrollNotifier		"AI Invalidate By Scroll Notifier"
/** @ingroup Notifiers
	Sent to notify tools that they should clear any editing state that
	they maintain.  Tools other than the current tool might
	maintain editing state; for example, selecting the zoom tool
	does not clear the editing state of the pen tool, which remembers
	the path to which it is adding points. */
#define kAIToolClearStateNotifier		"AI Tool Clear State Notifier"
/** @ingroup Notifiers
	Sent when the title string of a tool is changed.
	See \c #AIToolSuite::SetToolTitle() */
#define kAIToolTitleChangedNotifier		"AI Tool Title Changed Notifier"
/** @ingroup Notifiers
	Sent when a tool's rollover tooltip is changed.  */
#define kAIToolTooltipChangedNotifier	"AI Tool Tooltip Changed Notifier"
/** @ingroup Notifiers
	Obsolete. Not sent anymore. */
#define kAIToolHelpIDChangedNotifier	"AI Tool Help ID Changed Notifier"
/** @ingroup Notifiers
Sent when a tool's icon resources are changed. See \c #AIToolSuite::SetToolIcons() */
#define kAIToolIconChangedNotifier	"AI Tool Icon Resources Changed Notifier"
/** @deprecated	Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when the current tool is changed to a different tool. */
#define kAIToolChangedNotifier			"AI Tool Changed Notifier"
/** @ingroup Notifiers
	Sent when the tool window has changed. */
#define kAIToolWindowChangedNotifier	"AI Tool Window Changed Notifier"
/** @deprecated	Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when the cursor leaves a document window. */
#define kAIToolSuspendNotifier			"AI Tool Suspend Notifier"
/** @deprecated	 Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when the cursor enters a document window.  */
#define kAIToolResumeNotifier			"AI Tool Resume Notifier"
/** @ingroup Notifiers
	Sent when \c #AIToolTabletPointerType is changed. */
#define kAIToolTabletPointerTypeChangedNotifier	"AI Tablet Pointer Type Changed Notifier"
/** @ingroup Notifiers
	Sent when the modifier keys for the current tool are changed. */
#define kAIToolModifiersChangedNotifier	"AI Tool Modifiers Changed Notifier"
/** @deprecated	 Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when the user presses the space bar or Alt key(while in Text Tool) to select the scroll tool (\c #kScrollTool)
	or zoom tool (\c #kZoomTool), or presses Ctrl+spacebar, or Ctrl+Alt+spacebar
	while using another tool. */
#define kAIToolSuspendedBySpacebarNotifier	"AI Tool Suspended by Spacebar Notifier"
/** @deprecated	 Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when the user releases the spacebar (or Alt key(while in Text tool) or Ctrl+spacebar, or Ctrl+Alt+spacebar)
	to resume using the original tool.  */
#define kAIToolResumedBySpacebarNotifier	"AI Tool Resumed by Spacebar Notifier"
/** @deprecated	Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when \c #kSelectTool, \c #kDirectSelectTool, or \c #kDirectObjectSelectTool
	is temporarily reselected by pressing Ctrl(Windows) or Cmd(Macintosh) key while
	using another tool.
	For example, if \c #kDirectSelectTool is selected and you then choose the eraser tool,
	pressing the Ctrl or Cmd key temporarily switches back to \c #kDirectSelectTool, and
	sends this notification. */
#define kAIToolSuspendedByCmdKeyNotifier	"AI Tool Suspended by Cmd Key Notifier"
/** @deprecated	 Use \c #kAIEffectiveToolChangedNotifier instead
	Sent when the original tool is restored from a temporary switch back to
	\c #kSelectTool, \c #kDirectSelectTool, or \c #kDirectObjectSelectTool.
	Sent when the Ctrl or Cmd key is released.
	*/
#define kAIToolResumedByCmdKeyNotifier	"AI Tool Resumed by Cmd Key Notifier"


// Notifiers sent by built-in tools

/** @ingroup Notifiers
	Sent by the eyedropper when it is selected and dragged. The data is
	an \c #AIEyedropperDragNotifyData specifying the event and whether the
	path style has changed as a result. */
#define kAIEyedropperDragNotifier		"AI Eyedropper Drag Notifier"

/** @ingroup Callers
	The radial device caller. see #AIRadialDeviceMessage
*/
#define kCallerRadialDevice				"AI Radial Device"

/** #ingroup Selectors
	Sent when the radial device is rotated
*/
#define kSelectorAIRadialDeviceRotated	"Radial Device Rotated"

/** #ingroup Selectors
	Sent when the radial device is clicked
*/
#define kSelectorAIRadialDeviceClicked	"Radial Device Clicked"

/** @ingroup Callers
	The tool caller. See \c #AIToolSuite. */
#define kCallerAITool					"AI Tool"

/** @ingroup Selectors
	Sent when the tool has been selected (double-clicked) in the Tool palette.
	The plug-in can display a tool options dialog.
	The message data is an \c #AIToolMessage. */
#define kSelectorAIEditToolOptions		"AI Edit Options"
/** @ingroup Selectors
	Sent when the tool is selected and as the cursor is moved over the
	artboard with the button up. The plug-in can set the
	cursor based on location or some other factor. The message data is an \c #AIToolMessage. */
#define kSelectorAITrackToolCursor		"AI Track Cursor"
/** @ingroup Selectors
	Sent when the mouse button is pressed. The message data is an \c #AIToolMessage
	that contains the cursor location and modifier key information. */
#define kSelectorAIToolMouseDown		"AI Mouse Down"
/** @ingroup Selectors
	Sent on drag (cursor move with button down). The plug-in receives a series
	of these selectors. The message data is an \c #AIToolMessage that
	contains the cursor location and modifier key information. */
#define kSelectorAIToolMouseDrag		"AI Mouse Drag"
/** @ingroup Selectors
	Either follows the mouse-down selector immediately or ends
	the mouse-drag selectors. The message data is an \c #AIToolMessage
	that contains the cursor location and modifier key information. */
#define kSelectorAIToolMouseUp			"AI Mouse Up"
/** @ingroup Selectors
	Sent to a plug-in when its tool has been selected, to allow
	initialization. The message data is an \c #AIToolMessage. */
#define kSelectorAISelectTool			"AI Select"
/** @ingroup Selectors
	Sent to a plug-in when a different tool is selected, to allow cleanup
	of any run-time variables. The message data is an \c #AIToolMessage. */
#define kSelectorAIDeselectTool			"AI Deselect"
/** @ingroup Selectors
	Sent when an already-selected tool is reselected, with both
	\c #kAIToolDeselectedNotifier and \c #kAIToolSelectedNotifier.
	The message data is an \c #AIToolMessage.  */
#define kSelectorAIReselectTool			"AI Reselect"
/** @ingroup Selectors
	Sent when shortcut '[' is activated to decrease a diameter. */
#define kSelectorAIToolDecreaseDiameter	"AI Decrease Diameter"
/** @ingroup Selectors
	Sent when shortcut ']' is activated to increase a diameter. */
#define kSelectorAIToolIncreaseDiameter	"AI Increase Diameter"
/** @ingroup Selectors
Sent when the user requests a switch to an alternate selection tool by pressing Ctrl (in Windows)
or Cmd (in MacOS) key, while using a tool that allows alternate selection tool, to
determine whether the alternate selection tool is ready to be selected.
Valid return values are:
\li \c #kNoErr: Plug-in tool is not ready to be alternate selection tool.
\li \c #kAcceptAlternateSelectionToolReply: Plug-in tool is ready to be alternate selection tool.
The message data is an \c #AIToolMessage that
contains the alternate selection tool handle. */
#define kSelectorAIAlternateSelectionToolQuery  "AI Alternate Selection Tool Query"
/** @ingroup Selectors
Sent when the user switches to an alternate selection tool by pressing Ctrl (in Windows)
or Cmd (in MacOS) key while using a tool that allows alternate selection tool.
The message data is an \c #AIToolMessage that
contains the alternate-selection tool handle. */
#define kSelectorAIAlternateSelectionToolActivate "AI Alternate Selection Tool Activate"
/** @ingroup Selectors
Sent when the user switches back from a temporary alternate selection tool.
The message data is an \c #AIToolMessage that
contains the alternate selection tool handle. */
#define kSelectorAIAlternateSelectionToolDeActivate "AI Alternate Selection Tool DeActivate"

/** @ingroup Errors
Return code for response to \c #kSelectorAIAlternateSelectionToolQuery when
the alternate selection tool is ready for selection. */
#define kAcceptAlternateSelectionToolReply		'ASTR'

/** @ingroup Selectors
This can be used to get strokes directly without listening to mouse down, drag and up events.
The message data is an \c #AIToolDryInkMessage
that contains the cursor location and modifier key information. */
#define kSelectorAIToolDrawDryInk			"AI Tool Draw Dry Ink"

//  Brush tools share these options, so if you add new ones,
//	make sure they do not overlap with the brush tool options defined in
//	AIBrushMgr.h, which start at 1L<<16 and go up.

/**  Bit flags for options that can be set by a plug-in tool when it is installed
	 with \c #AIToolSuite::AddTool(), or later with \c #AIToolSuite::SetToolOptions(). */
enum AIToolOptions {
	/** Set to receive \c #kSelectorAITrackToolCursor, which allows you to
		control the cursor for your too. When off (the default), a standard arrow
		cursor is used for the tool.  */
	kToolWantsToTrackCursorOption		= (1<<0),
	/** Set to disable automatic scrolling. When off (the default), the Illustrator window
		scrolls when a tool reaches the edge. For tools that manipulate artwork,
		autoscroll is useful. Set this to turn autoscroll off for a tool that
		draws to the screen directly, like the built-in Brush tool. */
	kToolDoesntWantAutoScrollOption		= (1<<1),
	/**	Set to buffer the drag selectors and messages and send all of them
		to the tool at once. Useful if a tool is calculation intensive.  The effect
		is no longer real-time, but has a smoother final output.
		When off (the default), the tool processes drag selectors and returns frequently,
		resulting in near real-time feedback. If there are intensive calculations
		during the drag selector, the tool could miss drag notifications, resulting in rougher
		tracking.  */
	kToolWantsBufferedDraggingOption	= (1<<2),
	/** Set to maintain the edit context when this tool is selected. For art objects,
		keeps all current points and handles selected. For text, keeps the insertion
		point in the current location. Set this option for navigational tools like
		the Zoom and Scroll tools. */
	kToolMaintainEditContextOption 		= (1<<3),
	/** Set to maintain the text edit context when the tool is selected,
		if \c #kToolMaintainEditContextOption is also set. */
	kToolIsTextToolOption 				= (1<<4),
	/** Set to receive \c #kSelectorAIToolDecreaseDiameter and
		\c #kSelectorAIToolIncreaseDiameter. Use if the tool needs to change
		diameter when either '[' or ']' is pressed. */
	kToolWantsToChangeDiameterOption 				= (1<<5),
	/** Set to allow switching to an alternate selection tool when user presses Ctrl (in Windows) or Cmd (in Mac OS).
        This option can be set for any plug-in tool. Set the preferred alternate selection tool
        using \c #AIToolSuite::SetAlternateSelectionToolName().
        By default, the alternate tool is \c #kSelectTool(), \c #kDirectSelectTool(), or \c #kDirectObjectSelectTool()
	*/
	kToolWantsAlternateSelectionTool	= (1<<6),

	/** Set to hide a plugin toolset in the tool box. Hidden tools can still be used through shortcuts
		or through suite APIs, but are not shown in the tool box.
		Must be set or cleared on creation; you cannot change the hidden status with \c #AIToolSuite::SetToolOptions().
		Setting this option for a single tool in a toolset has no effect unless it is set for all tools in the toolset.
		It is recommended that you create a set of hidden tools, then show and hide individual tools by adding them to
		or removing them from the hidden set.
   */
	kToolWantsHiddenToolOption   = (1<<7),

    /** Indicates that the tool does not support soft selection modes, when used with the tablet/pen. \c #AIToolSuite::SetSoftSelectedTool().
        The inverted tablet pen tool will still function as the original tool.
     */
	kToolDoesntWantSoftSelectionOption   = (1<<8),

	/** Indicates that tool does want OS to draw its wet ink and provide its final Ink points to render rather than listening to mouse events
	*/
	kToolWantsOSHandleInk = (1<<9),

	/** Indicates that the tool has a double-click action associated with it.
	*/
	kToolHasAlternateAction = (1<<10),

	/**  Indicates that the tool wants to handle radial device events such as rotate and click
	*/
	kToolWantsRadialDeviceEvents = (1 << 11)

};


/** Tool information values. See \c #AIToolSuite::SetToolInfoVars().
	All values are real numbers, except these string values,
	which are  platform-encoded strings passed as \c char*:
	<br> \c kInfoFontAndSize
	<br> \c kInfoTrackOrKern
	<br> \c kInfoText1-6 and \c kInfoLongText1-3
	<br><br> \c kInfoTextUnicode1-6 and \c kInfoLongTextUnicode1-3 refer to the
	same Info palette slots as \c kInfoText1-6 and \c kInfoLongText1-3, but
	values are \c ai::UnicodeString*, which is treated as \c const.
	*/
enum AIToolInfoVariable {
	kInfoPageX = 0,
	kInfoPageY,
	kInfoSizeX,
	kInfoSizeY,
	kInfoDistance,
	kInfoVectorAngle,
	kInfoScaleX,
	kInfoScaleY,
	kInfoZoom,
	kInfoCornerRoundness,
	kInfoRotAngle,
	kInfoShearAngle,
	kInfoFontAndSize,
	kInfoTrackOrKern,
	kInfoRawRotAngle,
	kInfoDocX,
	kInfoDocY,
	kInfoText1,
	kInfoText2,
	kInfoText3,
	kInfoText4,
	kInfoText5,
	kInfoText6,
	kInfoLongText3,
    /** Pass Custom String for: X Y W H display in info palette */
	kInfoTextX,
	kInfoTextY,
	kInfoTextW,
	kInfoTextH,

	kInfoNumVars,
	kInfoBlank,

	// new in AI 12
	kInfoTextUnicode1,
	kInfoTextUnicode2,
	kInfoTextUnicode3,
	kInfoTextUnicode4,
	kInfoTextUnicode5,
	kInfoTextUnicode6,
	kInfoLongTextUnicode1,
	kInfoLongTextUnicode2,
	kInfoLongTextUnicode3,

	// overlayed items.
	kInfoLongText1 = kInfoFontAndSize,
	kInfoLongText2 = kInfoTrackOrKern,


	kInfoEndOfList = -1	 // Use this to terminate the infoVars list
};

/** An \c #AIToolType value that creates a new group or toolset.
	See @ref Toolsets */
#define kNoTool -2

/** A tool number used to indicate a tool group or toolset.
	See @ref Toolsets and \c #AIToolSuite::GetToolNumberFromName() */
typedef ai::int16 AIToolType;

/** Tool numbers less than this value are built-in,
	numbers greater than this are plug-in. See @ref Toolsets
	and \c #AIToolSuite::GetToolNumberFromName()  */
#define kPluginToolOffset 1000

/** @ingroup Errors
	See \c #AIToolSuite */
#define kToolCantTrackCursorErr		'TLTK'

//ToolTime for GetToolNullEventInterval. This type is to be deprecated ASAP.
// <<LET ME KNOW IF THIS DOESN'T HAPPEN>>
typedef double AIToolTime; //Time in Seconds

#define kToolTimeDurationSecond            ((AIToolTime)1.0)
#define kToolTimeDurationMillisecond       ((AIToolTime)(kToolTimeDurationSecond/1000))
#define kToolTimeDurationNoWait            ((AIToolTime)0.0)
#define kToolTimeDurationForever           ((AIToolTime)(-1.0))

#define kToolNormalIconDictKey				"ToolNormalIconDictKey"
#define kToolDarkNormalIconDictKey			"ToolDarkNormalIconDictKey"


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a tool plug-in, never dereferenced.
	Access with \c #AIToolSuite. */
typedef struct _t_AIToolOpaque *AIToolHandle;

/** Information about the change that caused a
	\c #kAIEffectiveToolChangedNotifier notification. */
struct AIEffectiveToolChangeData
{
	/** Name of currently effective tool. */
	const char*			currentToolName;
	/** Name of previous effective tool. */
	const char*			lastToolName;
	/** True if tool change is temporary, false if it
		is permanent. Temporary changes occur when user
		presses a modifier key such as Cmd or Space. */
	AIBoolean			isToolChangeTemporary;
	/** Tool handle for current effective tool.
		Can be null in case of select or direct-select tool.*/
	AIToolHandle		currentToolHandle;
	/** Tool handle for previous effective tool.
		Can be null if previous tool was select or direct-select,
		or if tool has not yet been changed since app launch. */
	AIToolHandle		lastToolHandle;
	/** Tool number of the currently effective tool. */
	AIToolType			currentToolNum;
	/** Tool number of the previously effective tool. */
	AIToolType			lastToolNum;
};

/** Information needed to add a tool using \c #AIToolSuite::AddTool(). */
struct AIAddToolData {
	/** Display name for tool. */
	const char *title = nullptr;
	/** Short descriptive string shown when tool is activated. */
	const char *tooltip = nullptr;
	/** @deprecated Obsolete. Do not use. */
	ASHelpID helpID = 0;
	/** The icon shown in the Tools palette; must be of type 'PNGI' */
	ai::uint32 normalIconResID = 0;
	/** The icon shown in the Tools palette in dark mode; must be of type 'PNGI' */
	ai::uint32 darkIconResID = 0;
	/** The Tools palette group to which this tool belongs.
		A tool number or \c #kNoTool to create a new group.
		See @ref Toolsets. */
	AIToolType sameGroupAs = 0;
	/** The Tools palette toolset to which this tool belongs.
		A tool number or \c #kNoTool to create a new toolset.
		See @ref Toolsets. */
	AIToolType sameToolsetAs = 0;
	/* Specifies the type of the incoming icons 
		enum IconType in AITypes.h*/
	ai::IconType iconType = ai::IconType::kPNG;
};

/** For internal use only. */
typedef struct _AIDataStack *AIDataStackRef;

/** For internal use only. */
struct AIAddToolDataPrivate {
	/** Display name for tool. */
	const char *title = nullptr;
	/** Short descriptive string shown when tool is activated. */
	const char *tooltip = nullptr;
	/** @deprecated Obsolete. Do not use. */
	ASHelpID helpID = 0;
	/** The icon shown in the Tools palette. */
	AIDataStackRef iconResourceDictionary;
	/** The Tools palette group to which this tool belongs.
		A tool number or \c #kNoTool to create a new group.
		See @ref Toolsets. */
	AIToolType sameGroupAs = 0;
	/** The Tools palette toolset to which this tool belongs.
		A tool number or \c #kNoTool to create a new toolset.
		See @ref Toolsets. */
	AIToolType sameToolsetAs = 0;
	/* Specifies the type of the incoming icons
	   enum IconType in AITypes.h*/
	ai::IconType iconType = ai::IconType::kInvalid;
};

/** An \c #AIToolTabletPointerTypeValue describing a type of pointing device.
	Used with a pressure-sensitive input device, such as a graphic tablet. */
typedef ai::int16 AIToolTabletPointerType;

/** \c #AIToolTabletPointerType constants that describe the type of
	input being received from input devices. */
enum AIToolTabletPointerTypeValue
{
	kAIToolTabletPointerTypeUnknown = 0,
	/** Pen end of a stylus. */
	kAIToolTabletPointerTypePen,
	/** Mouse or other non-pressure-sensitive pointer device. */
	kAIToolTabletPointerTypeCursor,
	/** Eraser end of a stylus. */
	kAIToolTabletPointerTypeEraser
};

/** An \c #AIToolPressureValue indicating the amount of force being
	applied with a pressure-sensitive input device, such as a graphic tablet. */
typedef ai::int16 AIToolPressure;
/** \c #AIToolPressure constants that indicate an amount of force applied to a
	pressure-sensitive input device. */
enum AIToolPressureValue
{
	/** The maximum pressure applied by a tool */
	kAIMaxToolPressure = 255,
	/** The minimal pressure applied by a tool */
	kAIMinToolPressure = 0,
	/** A default value for when there is no pressure data.  */
	kAINormalToolPressure = 127
};

/** An \c #AIToolAngleValue describing values of an input device
	such as tilt, rotation and bearing of a pen on a graphic tablet. */
typedef ai::int16 AIToolAngle;
/** \c #AIToolAngle constants that describe values of an input device
	such as tilt, rotation and bearing of a pen on a graphic tablet. */
enum AIToolAngleValue
{
	/** Angle constants in degrees */
	kAIToolAngle0 = 0,
	kAIToolAngle90 = 90,
	kAIToolAngleNegative179 = -179,
	kAIToolAngle180 = 180,
	kAIToolAngle360 = 360,

	/** Bearing ranges from -179 to 180 where 0 is up */
	kAIToolMinBearing = kAIToolAngleNegative179,
	kAIToolMaxBearing = kAIToolAngle180,
	kAIToolNormalBearing = kAIToolAngle0,

	/** Rotation ranges from -179 to 180 where 0 is up */
	kAIToolMinRotation = kAIToolAngleNegative179,
	kAIToolMaxRotation = kAIToolAngle180,
	kAIToolNormalRotation = kAIToolAngle0,

	/** Tilt ranges from 0 to 90 where 0 means that the pen barrel is perpendicular to the tablet's plane
		and 90 means that the pen barrel is parallel to the tablet's plane. */
	kAIToolMinTilt = kAIToolAngle0,
	kAIToolMaxTilt = kAIToolAngle90,
	kAIToolNormalTilt = kAIToolMinTilt
};
/** \c #AITabletCapabilities constants that describe the hardware capabilities of a graphic tablet/ Integrated digitizer.
*/
enum AITabletCapabilities
{
	/* X-coordinate in the tablet coordinate space. */
	kXCoordinate			=		1 << 0,
	/* Y-coordinate in the tablet coordinate space. */
	kYCoordinate			=		1 << 1,
	/* Z-coordinate or the distance of the pen tip from the tablet. */
	kZCoordinate			=		1 << 2,
	/* Pressure of pen tip perpendicular to tablet surface. */
	kNormalPressure			=		1 << 3,
	/* Pressure of the pen tip along the plane of the tablet surface. */
	kTangentPressure		=		1 << 4,
	/* Angle between the axis of pen and the surface of the tablet. */
	kAltitudeOrientation	=		1 << 5,
	/* Clockwise rotation of the cursor around the z-axis through a full circular range. */
	kAzimuthOrientation		=		1 << 6,
	/* Clockwise rotation of the cursor around its own axis. */
	kTwistOrientation		=		1 << 7
};


enum AIToolMessageFlags
{
	/*Indicates that it is a simulated Tool Message of InkStrokes*/
	kAIToolMsgInkSimulationFlag				=		1 << 0,
	kAIToolMsgModifierKeyPressedDuringInk	=		1 << 1
};

/** History Data associated with an Event. */
struct AIEventHistoryData
{
	/** The location of the event */
	AIPoint position;
	/** For graphic tablets, tangential pressure on the finger wheel of the airbrush tool. */
	AIToolPressure stylusWheel;
	/** How the tool is angled, also called altitude or elevation. */
	AIToolAngle tilt;
	/** The direction of tilt, measured clockwise in degrees around the Z axis, also called azimuth, */
	AIToolAngle bearing;
	/**  Rotation of the tool, measured clockwise in degrees around the tool's barrel. */
	AIToolAngle rotation;
};
/** The contents of a tool message. */
struct AIToolMessage {
	/** The message data. */
	SPMessageData d;
	/** The tool plug-in receiving the message.
		If the plug-in has more than one tool installed, it can
		determine which one was selected by comparing this handle
		to those it has saved in the \c globals variable. */
	AIToolHandle tool;
	/** The location of the mouse cursor in page coordinates. */
	AIRealPoint cursor;
	/** The amount of force being applied to a pressure-sensitive input device,
		such as a graphics tablet.  Use \c #AIToolSuite::SystemHasPressure()
		to determine if such a device is in use. */
	AIToolPressure pressure;
	/** For mouse selectors, the ADM event record for the mouse event,
		containing additional information about the event. (ADM is no longer supported).*/
	AIEvent *event;
	/** For graphic tablets, tangential pressure on the finger wheel of the airbrush tool. */
	AIToolPressure stylusWheel;
	/** How the tool is angled, also called altitude or elevation. */
	AIToolAngle tilt;
	/** The direction of tilt, measured clockwise in degrees around the Z axis, also called azimuth, */
	AIToolAngle bearing;
	/**  Rotation of the tool, measured clockwise in degrees around the tool's barrel. */
	AIToolAngle rotation;
	
	/** To give more information to listeners of AIToolMessage, it will be composed of values from AIToolMessageFlags  */
	ai::int32	flags;
	/** The history data associated with the event */
	ai::AutoBuffer<AIEventHistoryData> eventHistoryData;
};

/** The content of a radial device message. */
struct AIRadialDeviceMessage
{
	/** The message data. */
	SPMessageData d;
	
	/** The tool plug-in receiving the message.
	If the plug-in has more than one tool installed, it can
	determine which one is selected by comparing this handle
	to those it saves in the \c globals variable. */
	AIToolHandle tool = nullptr;

	/** Rotation value */
	AIReal rotation = 0.0;
};

/** The contents of a tool notification. */
struct AIToolNotifyData {
	/** The tool plug-in receiving the notification. If you install more than one tool,
		compare to your saved reference to decide how to handle the notification. */
	AIToolHandle tool;
};

/** The contents of an eyedropper drag notification, \c #kAIEyedropperDragNotifier. */
struct AIEyedropperDragNotifyData {
	/** The ADM event record for the mouse event. (ADM is no longer supported).  */
	AIEvent event;
	/** True if the path style has changed as a result of the drag event. */
	AIBoolean pathStyleChanged;
};

struct AIDocumentInkParams
{
	enum PenTipShape
	{
		kPenTipShapeCircle,
		kPenTipShapeRectangle
	};
	PenTipShape fShape;
	AIColor fColor;
	AIPoint fSize;
	ai::AutoBuffer<ai::uint32> fModifiersList;
	AIReal  fRotation;
	AIBoolean fSupportPressure;
	AIBoolean fCustomModifierHandling;	// Specifying it as true turns off direct ink when a mod key is pressed.
	enum PressureBasedVariant
	{
		kPressuteBasedVariantNone = 1 << 0,
		kPressuteBasedVariantDia = 1 << 1,
		kPressuteBasedVariantRoundness = 1 << 2,
		kPressuteBasedVariantAngle = 1 << 3,
	};
	ai::int32 fPressureBasedVariants;
	AIDocumentInkParams() :fShape(kPenTipShapeCircle)
	{
		fColor.kind = kThreeColor;
		fColor.c.rgb.red = 0.0f;
		fColor.c.rgb.green = 0.0f;
		fColor.c.rgb.blue = 0.0f;
		fSize.h = 1;
		fSize.v = 1;
		fRotation = 0.0f;
		fSupportPressure = false;
		fPressureBasedVariants = 0;
		fCustomModifierHandling = false;
	}
};


struct AIDocumentInkPoint
{
	AIRealPoint		 fLocation;
	AIToolPressure	 fPressure;
	AIToolPressure	 fStylusWheel;
	AIToolAngle		 fRotation;
	AIToolPressure	 fBearing;
	AIToolPressure	 fTilt;

	AIDocumentInkPoint()
	{
		fLocation.h = 0.0;
		fLocation.v = 0;
		fPressure = 0;
		fStylusWheel = kAIToolMinRotation;
		fBearing = kAIToolMinBearing;
		fRotation = kAIToolMinRotation;
		fTilt = kAIToolMinTilt;
	}
};

/** The contents of a tool message. */
struct AIToolDryInkMessage {
	/** The message data. */
	SPMessageData d;

	/** To give more information to the listeners of AIToolDryInkMessage, it will be composed of values from AIToolMessageFlags  */
	ai::int32	flags = 0;

	/** The tool plug-in receiving the message.
	If the plug-in has more than one tool installed, it can
	determine which one was selected by comparing this handle
	to those it has saved in the \c globals variable. */
	AIToolHandle tool;

	/** Future use We might need this for modifiers*/
	AIEvent *event;

	ai::AutoBuffer<AIDocumentInkPoint> inkStrokes;

	AIToolDryInkMessage() :tool(0), event(nullptr)
	{}
};


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite allows you to provide plug-in tools for Illustrator.
	Plug-in tools can work on existing artwork or create new objects.
	Tools that you add appear in the Illustrator Tool palette in their own set,
	or as part of an existing tool set. Use the functions in this suite
	to add tools, set options, and control the tool’s appearance in the palette.

	Typically, you set the options that control the behavior of a plug-in tool
	when you install the tool with \c #AIToolSuite::AddTool(). You can modify
	them later with \c #AIToolSuite::SetToolOptions().

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIToolSuite and \c #kAIToolVersion.

	@section Toolsets Toolsets and Groups in the Tools Palette

	In the Tools palette, \e a toolset is a collection related tools.
	When there is more than one tool in a toolset, only the frontmost tool's
	icon is shown in the palette, with a triangle in the lower left corner
	to indicate the presence of additional tools. The entire toolset
	is shown when the user holds the mouse button down on the topmost tool.

	A \e group is a collection of toolsets. Groups are separated by vertical
	space in the palette.

	To create a new group or toolset, pass \c #kNoTool for
	\c #AIAddToolData::sameGroupAs or \c #AIAddToolData::sameToolsetAs.
	For example, to create a new tool group:
	@code
toolData.title = "MyTool1";
toolData.tooltip = "MyTool1 Tooltip";
toolData.sameGroupAs = kNoTool;
toolData.sameToolsetAs = kNoTool;
	@endcode

	To add a new toolset to this group:
	@code
toolData.title = "MyTool2";
toolData.tooltip = "MyTool2 Tooltip";
error = sTool->GetToolNumberFromName("MyTool1", &toolData.sameGroupAs);
toolData.sameToolsetAs = kNoTool;
	@endcode

	To add tools to this toolset:
	@code
toolData.title = "MyTool2a";
toolData.tooltip = "Tool2a Tooltip";
error = sTool->GetToolNumberFromName("MyTool1",	&toolData.sameGroupAs);
error = sTool->GetToolNumberFromName("MyTool2", &toolData.sameToolsetAs);
	@endcode

	@section ToolBehavior Tool Behavior

	Implement tool behavior by defining handlers for the caller/selector pairs
	and messages that plug-in tools receive, particularly the mouse selectors.
	Check for selectors in the plug-in's main function.

	Your mouse selector handlers can create or modify art objects directly.
	A tool can select and work on several art objects at once.
	The application updates the window between calls to the plug-in, so the
	new or changed artwork appears as the mouse moves.
	Use \c #AIUndoSuite::UndoChanges() before processing the tool drag,
	in order to maintain a known artwork state from which to redraw changes.

	Because multiple  plug-ins can be running at once,
	the artwork state can change in the course of using your tool.
	To verify that a specific artwork state exists, you can use a plug-in
	notifier to indicate that the artwork selection or properties
	have been changed. See the \c #AINotifierSuite.

	The caller for tool plug-ins is \c #kCallerAITool.

	These selectors are sent:
	<br> \c #kSelectorAIEditToolOptions
	<br> \c #kSelectorAITrackToolCursor
	<br> \c #kSelectorAIToolMouseDown
	<br> \c #kSelectorAIToolMouseDrag
	<br> \c #kSelectorAIToolMouseUp
	<br> \c #kSelectorAISelectTool
	<br> \c #kSelectorAIDeselectTool
	<br> \c #kSelectorAIReselectTool

	These notifiers are related to tools:
	<br> \c #kAIUserToolChangedNotifier
	<br> \c #kAIToolSelectedNotifier
	<br> \c #kAIToolDeselectedNotifier
	<br> \c #kAIToolClearStateNotifier
	<br> \c #kAIToolTitleChangedNotifier
	<br> \c #kAIToolTooltipChangedNotifier
	<br> \c #kAIToolChangedNotifier
	<br> \c #kAIToolWindowChangedNotifier
	<br> \c #kAIToolSuspendNotifier
	<br> \c #kAIToolResumeNotifier
	<br> \c #kAIEyedropperDragNotifier

 */
struct AIToolSuite {

	/** Installs a plug-in tool. Use at startup.
			@param self This plug-in.
			@param name The unique name of this tool.
			@param data	Information on how to display this tool in the Tool palette.
			@param options Option flags that control the tool's behavior, a logical OR
				of \c #AIToolOptions constants.
			@param tool	[out] A buffer in which to return the tool reference. If you
				install multiple tools, save to compare to the tool reference in tool
				message data.
		*/
	AIAPI AIErr (*AddTool) ( SPPluginRef self, const char *name,
				AIAddToolData *data, ai::int32 options,
				AIToolHandle *tool );

	/** For internal use only */
	AIAPI AIErr (*AddToolPrivate) ( SPPluginRef self, const char *name,
		AIAddToolDataPrivate *data, ai::int32 options,
		AIToolHandle *tool );

	/** Retrieves the unique identifying name of a tool.
		To get the localizable title that appears in the UI, use \c #GetToolTitle().
			@param tool The tool reference.
			@param name [out] A pointer to point to the name string. Do
				not modify this string.
	  		@note	It is more efficient to work with tool numbers rather than
					names. See \c #GetToolNumberFromHandle().
		*/
	AIAPI AIErr (*GetToolName) ( AIToolHandle tool, char **name );

	/** Retrieves the option flags of a tool. To retain the existing flags when
		setting options with \c #SetToolOptions(), obtain them with this function
		and do a logical OR with the new flags.
			@param tool The tool reference.
			@param options [out] A buffer in which to return the options value, a logical
				OR of \c #AIToolOptions constants.
	  	*/
	AIAPI AIErr (*GetToolOptions) ( AIToolHandle tool, ai::int32 *options );

	/** Sets the option flags of a tool. To retain the existing flags when
		setting options, obtain them with \c #GetToolOptions()
		and do a logical OR with the new flags.
			@param tool The tool reference.
			@param options The new options value, a logical OR of \c #AIToolOptions constants.
		*/
	AIAPI AIErr (*SetToolOptions) ( AIToolHandle tool, ai::int32 options );

	/** Retrieves the plug-in that installed a tool.
			@param tool The tool reference.
			@param plugin [out] A buffer in which to return the	plug-in reference,
				which can be used with \c #AIPluginSuite functions.
		*/
	AIAPI AIErr (*GetToolPlugin) ( AIToolHandle tool, SPPluginRef *plugin );

	/** Retrieves the currently selected plug-in tool. If the current tool
		is a built-in tool, returns NULL.
		See \c #AIToolboxSuite::GetCurrentToolType() or \c #GetCurrentToolName()
		for retrieving the current tool including built-in tools.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetSelectedTool) ( AIToolHandle *tool );

	/** Selects a plug-in tool programmatically. This is the same as the user
		selecting the tool in the Tool palette.
		To select built-in tools, see \c #SetSelectedToolByName()
			@param tool The tool reference.
		*/
	AIAPI AIErr (*SetSelectedTool) ( AIToolHandle tool );

	/** Gets the number of installed plug-in tools. Use with \c #GetNthTool()
		to iterate through plug-in tools.
			@param count [out] A buffer in which to return the number of tools.
		*/
	AIAPI AIErr (*CountTools) ( ai::int32 *count );

	/** Retrieves a tool by index position. Use with \c #CountTools()
		to iterate through plug-in tools.
			@param n The 0-based position index.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetNthTool) ( ai::int32 n, AIToolHandle *tool );

	/** Retrieves a plug-in tool by its tool number, as assigned when it is created
		with \c #AddTool(), and obtained by calling \c #GetToolNumberFromHandle.
		See @ref Toolsets.
		If the toolNum is the number of a built-in tool, returns NULL, since
		built-in tools do not have an AIToolHandle.
			@param toolNum The tool number.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetToolHandleFromNumber) ( AIToolType toolNum,  AIToolHandle *tool );

	/** Retrieves a tool number from a tool's unique name. Use to find the numbers of
		built-in tools, in order to place your tool in an existing group or toolset.
		See @ref Toolsets.
			@param name The tool name. The names of Illustrator's built-in tools
				can be found in \c AIToolNames.h.
			@param toolNum [out] A buffer in which to return the tool number.
		*/
	AIAPI AIErr (*GetToolNumberFromName) ( const char *name, AIToolType *toolNum );

	/** Retrieves a tool number for a tool. Use to find the numbers of
		plug-in tools, in order to place your tool in an existing group or toolset.
		See @ref Toolsets.
			@param tool The tool reference.
			@param toolNum [out] A buffer in which to return the tool number. 	 */
	AIAPI AIErr (*GetToolNumberFromHandle) ( AIToolHandle tool, AIToolType *toolNum );

	/** Retrieves the unique name of a tool from its number. To get the localizable
		title that appears in the UI, use \c #GetToolTitle().
			@param toolNum The tool number.
			@param name	[out] A pointer to point to the name string. Do not modify
				this string. Copy it immediately to use it.
		 */
	AIAPI AIErr (*GetToolNameFromNumber) ( AIToolType toolNum, char **name );

	/** Retrieves the localizable title of a tool, which appears in the UI.
		To get the unique, identifying name, use \c #GetToolName().
			@param tool The tool reference.
			@param title [out] A pointer to point to the title string. Do not modify
				this string.
		*/
	AIAPI AIErr (*GetToolTitle) ( AIToolHandle tool, char **title );

	/** Sets the localizable title of a tool, which appears in the UI.
			@param tool The tool reference.
			@param title The new title string.
		*/
	AIAPI AIErr (*SetToolTitle) ( AIToolHandle tool, const char *title );


	/** Retrieves the tooltip string for a tool.
			@param tool The tool reference.
			@param tooltip [out] A pointer to point to the tooltip string. Do not modify
				this string.
		*/
	AIAPI AIErr (*GetTooltip) ( AIToolHandle tool, char **tooltip );

	/** Sets the tooltip string for a tool.
			@param tool The tool reference.
			@param tooltip The new tooltip string.
		 */
	AIAPI AIErr (*SetTooltip) ( AIToolHandle tool, const char *tooltip );

	/** Determines which labeled fields are displayed in the Info palette for a tool.
		Typically called once at startup to initialize the Info palette.
			@param tool The tool reference.
			@param infoVars A pointer to the first member of an array of
				information variables, which correspond to labeled fields
				in Illustrator’s Info palette, as defined in \c #AIToolInfoVariable.
				Only the fields included in this array are shown for the tool.
				To initialize or set the values in the fields, use \c #SetToolInfoVarValues().
		 */
	AIAPI AIErr (*SetToolInfoVars) ( AIToolHandle tool, const ai::int32 infoVars[] );

	/** Sets field values in the Info palette. Only those fields specified by
		\c #SetToolInfoVars() are displayed in the palette.
			@param infoVars A pointer to the first member of an array of
				information variables, which correspond to labeled fields
				in Illustrator’s Info palette. This is the same array specified
				by \c #SetToolInfoVars().
			@param values A pointer to the first member of an array of values,
				whose positions match those in the \c infoVars array.

			\b Example:
@code
AIErr UpdateInfoPalette( AIToolHandle tool, AIRealPoint origin, AIArtHandle art )
{
	ASErr error = kNoErr;
	if (art) {
		static const long infoVars = { kInfoDocX, kInfoDocY, kInfoSizeX, kInfoSizeY, kInfoEndOfList };
		AIReal *infoValues[4];
		AIReal temp[2];
		AIRealRect artBounds;
		error = sAIArt->GetArtTransformBounds( art,0, kStroke, &artBounds);
		if ( error )
			return error;
		temp[0] = artBounds.right - artBounds.left;
		temp[1] = artBounds.bottom - artBounds.top;
		infoValues[0] = &origin.h;
		infoValues[1] = &origin.v;
		infoValues[2] = temp;
		infoValues[3] = temp +1;
		error = sAITool->SetToolInfoVarValues( infoVars, (void**)infoValues);
		if ( error )
			return error;
	}
}
@endcode
		*/
	AIAPI AIErr (*SetToolInfoVarValues) ( const ai::int32 *infoVars,  void **values );

	/** Reports whether a pressure-sensitive device such as a graphics tablet
		was available on application startup.
			@param hasPressure [out] A buffer in which to return true if
				a pressure-sensitive device is in use.
		*/
	AIAPI AIErr (*SystemHasPressure) ( AIBoolean *hasPressure );

	/** @deprecated Obsolete. Do not use. */
	AIAPI AIErr (*GetToolNullEventInterval) (AIToolHandle tool, AIToolTime *outTime);

	/** @deprecated Obsolete. Do not use. */
	AIAPI AIErr (*SetToolNullEventInterval) (AIToolHandle tool, AIToolTime inTime);

	/** Selects a plug-in tool, but does not highlight
		it in the palette or show its tool name in the status bar of the document
		window. Indicates this \e soft selection by setting the \c isSoftMode flag.
		\c #SetSelectedTool() turns this flag off.
			@param tool The tool reference.
		*/
	AIAPI AIErr (*SetSoftSelectedTool) ( AIToolHandle tool );

	/** Reports whether there is currently a \e soft tool selection.
		Soft mode is entered when a tool, such as the rectangle tool, is
		selected and the user implicitly overrides this by drawing with the eraser
		end of a tablet stylus.
			@param isSoftMode [out] A buffer in which to return true if there is a
				soft tool selection.
		*/
	AIAPI AIErr (*IsSoftModeSelection) ( AIBoolean *isSoftMode );

	/** Retrieves the name of the tool that will be temporarily selected  by pressing Ctrl (in Windows)
		or Cmd (in MacOS) key while using this tool.
		Effective only if the tool has set the option \c #kToolWantsAlternateSelectionTool.
			@param tool This tool.
			@param name A buffer in which to return the name of the alternate selection tool.
	*/
	AIAPI AIErr (*GetAlternateSelectionToolName) (AIToolHandle tool, char **name);

	/** Sets the tool that will be temporarily selected by pressing Ctrl (in Windows)
		or Cmd (in Mac OS) key while using this tool.
		Effective only if the tool has set the option \c #kToolWantsAlternateSelectionTool.
			@param tool This tool.
			@param name The name of the alternate selection tool.
	*/
	AIAPI AIErr (*SetAlternateSelectionToolName) (AIToolHandle tool, const char* alternateTool);

	/** Retrieves the unique name of the currently selected tool. This is the same
	    name you get from calling \c #AIToolboxSuite::GetCurrentToolType()
	    followed by \c #GetToolNameFromNumber().
	 	@param name	[out] A pointer to point to the name string. Do not modify
				this string. Copy it immediately to use it.
	  	@note	It is more efficient to work with tool numbers rather than
				names. See \c #GetCurrentToolNumber().
	 */
	AIAPI AIErr (*GetCurrentToolName) ( const char **name );

	/** Retrieves the number of the currently selected tool.
	 	@param toolNum [out] A buffer in which to return the tool number.
	 */
	AIAPI AIErr (*GetCurrentToolNumber) ( AIToolType *toolNum );

	/** Retrieves the currently active plug-in tool. If the currently active
		tool is a built-in tool, returns NULL. This is the same value you get
		from \c #currentToolHandle in \c #AIEffectiveToolChangeData.
		See \c #GetCurrentEffectiveToolNumber() or \c #GetCurrentEffectiveToolName()
		for retrieving the current effective tool including built-in tools.
		@param tool	[out] A buffer in which to return the tool reference.
	  	@note	It is more efficient to work with tool numbers rather than
				names.
		*/
	AIAPI AIErr (*GetCurrentEffectiveTool) ( AIToolHandle *tool );

	/** Retrieves the unique name of the currently active tool. This is the same
		value you get from \c #currentToolName in \c #AIEffectiveToolChangeData.
		@param name	[out] A pointer to point to the name string. Do not modify
				this string. Copy it immediately to use it.
	  	@note	It is more efficient to work with tool numbers rather than
				names. See \c #GetCurrentEffectiveToolNumber().
	*/
	AIAPI AIErr (*GetCurrentEffectiveToolName) ( const char **name );

	/** Retrieves the number of the currently active tool. This is the same
		value you get from \c #currentToolNum in \c #AIEffectiveToolChangeData.
		@param toolNum [out] A buffer in which to return the tool number.
	*/
	AIAPI AIErr (*GetCurrentEffectiveToolNumber) ( AIToolType *toolNum );

	/** Retrieves the numerical identifier of the most recently used built-in selection tool,
            and optionally retrieves the unique name of the tool, from \c AIToolNames.h.
            (Note that this function returns an \c #AIToolType, not an error code.)
            	@param name     [out][optional] A buffer in which to return the name string.
                            Do not modify this string. Copy it immediately to use it.
            	@return The numerical identifier.
    */

	AIAPI AIToolType (*GetLastUsedSelectionTool) ( const char **name );

	/** Select a tool by its unique name identifier. Can be either the name of a plug-in tool,
	    returned by \c #GetToolName(), or one of the tool name constants from \c AIToolNames.h.
		@param name The name of the tool to be selected.
	  	@note	It is more efficient to work with tool numbers rather than
				names. See \c #SetSelectedToolByNumber().
	 */
	AIAPI AIErr (*SetSelectedToolByName) ( const char *name );

	/** Select a tool using its tool number.
	   	 @param toolNum The tool number.
	 */
	AIAPI AIErr (*SetSelectedToolByNumber) ( AIToolType toolNum );

	/** Reports the hardware capabilities of a graphical tablet or integrated digitizer.
            	@param hardwareCapabilities     [out] A buffer in which to return a
            				logical OR of \c #AITabletCapabilities constants.
    */
	AIAPI AIErr (*GetTabletHardwareCapabilities) ( ai::int32* hardwareCapabilities );

	/** Sets tool icons to be used with light and dark UI themes.
	@param tool[in] The tool reference.
	@param normalIconResource[in] Base file name (without extension) of the PNG icon resource for the light UI theme.
	@param darkNormalIconResource[in] Base file name (without extension) of the PNG icon resource for the dark UI theme.
	*/
	AIAPI AIErr (*SetToolIcons) (AIToolHandle tool, const char *normalIconResourceName, const char *darkNormalIconResourceName);

	/**Retrieves the base filenames (without extension) of the PNG icon resources associated with a tool.
	   @param tool[in] The tool reference.
	   @param normalIconResource[out] A buffer in which to return the resource name for light UI theme icon.
	   @param darkNormalIconResource[out]  A buffer in which to return the resource name for dark UI theme icon.
	*/
	AIAPI AIErr(*GetToolIcons) (const AIToolHandle tool, char **normalIconResourceName, char **darkNormalIconResourceName);

	/**
	*/
	AIAPI AIErr(*SetDocumentInkParams)(const AIToolHandle tool, const AIDocumentInkParams& inDocInkParams);

	/** Retrieves the options associated with the tool corresponding to the given tool number.
		@param options [out] A buffer in which to return the options value.
	*/
	AIAPI AIErr (*GetToolOptionsFromNumber) (AIToolType toolNum, ai::int32 *options);

	/** Retrieves the options associated with the tool corresponding to the given tool name.
		@param options [out] A buffer in which to return the options value.
	  	@note	It is more efficient to work with tool numbers rather than
				names. See \c #GetToolOptionsFromNumber().
	*/
	AIAPI AIErr (*GetToolOptionsFromName) (const char *toolName, ai::int32 *options);
};


#include "AIHeaderEnd.h"
