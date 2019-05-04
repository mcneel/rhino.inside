#ifndef __AIMenuGroups__
#define __AIMenuGroups__

/*
 *        Name:	AIMenuGroups.h
 *   $Revision: 20 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Built-in Menu Groups.
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

/** @file AIMenuGroups.h */


/**	@ingroup MenuGroups */
/** @{   <<This doesn't work - gets Doxygen error "@{ may only be used in a group block">> */

#define kAboutMenuGroup 		"About"

#define kOpenMenuGroup 			"Open Document"
#define kRecentMenuGroup		"Recent Files"
#define kCloseMenuGroup 		"Close Document"
#define kDeviceCentralMenuGroup "Device Central"
#define kSaveMenuGroup 			"Save Document"
#define kSaveForMenuGroup		"Save For"
#define kImportMenuGroup 		"Import"
#define kPlaceMenuGroup 		"Place Document"
#define kExportMenuGroup 		"Export Document"
#define kDocumentUtilsMenuGroup "Document Utilities"
#define kDocumentInterchangeMenuGroup "Document Interchange"
#define kPrintMenuGroup 		"Print"
#define kSendMenuGroup 			"Send Document"

#define kAppUtilsMenuGroup 		"Application Utilities"
#define kQuitMenuGroup 			"Quit"

#define kEditMenuGroup 			"Edit"
#define kUndoMenuGroup 			"Undo"
#define kPasteUtilsMenuGroup 	"Paste Utilities"
#define kEditUtilsMenuGroup 	"Edit Utilities"
/** Find/Replace, Spell Check */
#define kEditTextMenuGroup		"Edit Text"
/** PDF, Transparency, Print presets */
#define kPresetsMenuGroup		"Presets Group"
/** Includes Keyboard Shortcuts	*/
#define kEditUtilsMenuGroup 	"Edit Utilities"
/** Select menu- internal commands */
#define kSelectMenuGroup 		"Select"
/** Select menu- external commands  */
#define kSelectMenuExternalGroup "SelectExternal"

#define kSameMenuGroup			"Same"
#define kSelectObjectMenuGroup	"SelectObject"

#define kPrefsMenuGroup 		"Preferences"

#define kSyncMenuGroup			"Sync"
//#define kPublishingMenuGroup 	"Publishing"
#define kClipboardMenuGroup 	"Clipboard"

#define kRepeatMenuGroup 		"Repeat"
#define kArrangeTransformMenuGroup "Arrange Transform"
#define kArrangeMoveMenuGroup 	"Arrange Move"
#define kArrangeGroupMenuGroup 	"Arrange Group"
#define kArrangeAttribsMenuGroup "Arrange Attributes"

#define kViewModeMenuGroup 		"View Mode"
#define kViewAdornmentsMenuGroup "View Adornments"
#define kViewMenuGroup 			"View"
#define kViewUtilsMenuGroup 	"View Utilities"
#define kViewExtMenuGroup 		"View Extension"
#define kViewSnapMenuGroup		"View Snap"

#define kObjectAttribsMenuGroup "Object Attributes"
#define kObjectUtilsMenuGroup 	"Object Utilities"
#define kObjectsMenuGroup 		"Objects"
/** The group that contains the submenus for Path, Blend, Envelope Distort, and so on. */
#define kObjectPathsMenuGroup 		"Objects Paths"
/** The group that is the initial contents of the Path submenu.
	Plug-ins that want to be on this submenu should create
	\c #kObjectPathsPopoutPluginMenuGroup
	near \c #kObjectPathsPopupMenuGroup, then add themselves
	to that group, not add themselves directly to
	\c #kObjectPathsPopupMenuGroup. */
#define kObjectPathsPopupMenuGroup 	"Objects Paths Popup"
#define kLockMenuGroup			"Lock"
#define kHideMenuGroup			"Hide"

#define kGuidesMenuGroup 		"Guides"
#define kMaskMenuGroup 			"Masks"
#define kCompoundPathsMenuGroup "Compound Paths"
#define kArtboardsGroup			"ArtBoards"
#define kCropMarksMenuGroup 	"Crop Marks"
#define kGraphsMenuGroup 		"Graphs"
#define kBlocksMenuGroup 		"Blocks"
#define kWrapMenuGroup 			"Wrap"
#define kTextPathTypeGroup		"Text Path Type"
#define kTypeAttribsMenuGroup 	"Type Attributes"
#define kTypePalettesMenuGroup 	"Type Palettes"
#define kTypeLayoutMenuGroup 	"Type Layout"
#define kTypeTabsMenuGroup 		kTypePalettesMenuGroup
#define kTypeUtilsMenuGroup 	"Type Utilities"
#define kTypePluginsMenuGroup1	"Type Plugins1"
#define kTypePluginsMenuGroup2	"Type Plugins2"
#define kTypeAsianOptionsGroup	"Type Asian Options"

#define kTypeSizeUtilsMenuGroup "Type Size Utilities"
#define kTypeSizeMenuGroup 		"Type Size"
#define kTypeLeadingUtilsMenuGroup "Type Leading Utilities"
#define kTypeLeadingMenuGroup 	"Type Leading"
#define kTypeAlignmentMenuGroup "Type Alignment"

#define kFilterUtilities	"Filter Utilities"

#define kEffectsMenuGroup	"Effects"

#define kHelpMenuGroup 			"Help Menu"

// The following groups do not show up in the menu bar. They only
// show up in the keyboard shortcuts dialog.
/** In keyboard shortcuts dialog */
#define kHidddenOtherSelectMenuGroup	"Hidden Other Select"
/** In keyboard shortcuts dialog */
#define kHiddenOtherTextMenuGroup		"Hidden Other Text"
/** In keyboard shortcuts dialog */
#define kHiddenOtherObjectMenuGroup		"Hidden Other Object"
/** In keyboard shortcuts dialog */
#define kHiddenOtherPaletteMenuGroup	"Hidden Other Palette"
/** In keyboard shortcuts dialog */
#define kHiddenOtherMiscMenuGroup		"Hidden Other Misc"


#define kWindowUtilsMenuGroup 			"Window Utilities"
#define kApplicationContainerMenuGroup 	"Application Container"
#define kToolPalettesMenuGroup			"Tool Palettes"
#define kWindowLibariesMenuGroup		"Window Libraries"
#define kAdobeLabsMenuGroup				"Adobe Labs Menu Group" //VS_TODO: To be removed
#define kServicesMenuGroup				"Services Menu Group"

#define kPaintPalettesMenuGroup 			kToolPalettesMenuGroup
#define kObjectInfoPalettesMenuGroup		kToolPalettesMenuGroup
#define kAttributePalettesMenuGroup 		kToolPalettesMenuGroup
#define kOtherPalettesMenuGroup 			kToolPalettesMenuGroup
#define kPaintAttributesPaletteMenuGroup	kToolPalettesMenuGroup
#define kSVGPaletteMenuGroup				kToolPalettesMenuGroup
#define kWindowObjectUtilsMenuGroup			kToolPalettesMenuGroup
// Note the pre-AI10 definitions of these menu groups as shown below are mapped to kToolPalettesMenuGroup
//#define kPaintPalettesMenuGroup 			 "Paint Palettes"
//#define kObjectInfoPalettesMenuGroup		 "Object Info Palettes"
//#define kAttributePalettesMenuGroup 		 "Attribute Palettes"
//#define kOtherPalettesMenuGroup 			 "Palettes"
//#define kPaintAttributesPaletteMenuGroup	 "Paint Attributes Palettes"
//#define kSVGPaletteMenuGroup				 "SVG Palette"
//#define kWindowObjectUtilsMenuGroup		 "Window Object Utilities Palettes"



// The following groups are added by plug-ins, not by the application.
// To use them, your plug-in should add the group using AddMenuGroup (it is ok to add a group twice;
// all but the first request will be ignored.)

/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kDocInfoMenuGroup				"AIPlugin Document Info"
//#define kDocInfoMenuGroupNearGroup
//#define kDocInfoMenuGroupOptions		kMenuGroupSeparatorOption

/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kObjectRasterMenuGroup			"AIPlugin Object Raster"
//#define kObjectFlattenMenuGroup			"AIPlugin Object Flatten"
//#define kObjectRasterMenuGroupOptions	kMenuGroupSeparatorOption

/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kArrangeTransformMultipleMenuGroup "Arrange Multiple Transform"
/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kATMMenuGroupNearGroup 			kArrangeTransformMenuGroup
//#define kArrangeTransformMultipleMenuGroupOptions kMenuGroupSeparatorOption

/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup().
	This is the area of the Path popout menu intended for plug-in commands */
#define kObjectPathsPopoutPluginMenuGroup	"More Menus in the Object Path Popout"
/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kOPPPMenuGroupNearGroup 			kObjectPathsPopupMenuGroup
//#define kOPPPMenuGroupOptions 			kMenuGroupSeparatorOption

/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup().
	The group that is the initial contents of the Edit Colors submenu. */
#define kAIEditColorsSubMenuGroup	"AIEdit Colors SubMenu Group"
/** Use this priority with \c #AIMenuSuite::AddMenuItemZString()
	before \c #AIMenuSuite::AddMenuGroupAsSubMenu().
	Subgroups do not support multiple add attempts. Search this group
	using \c #AIMenuSuite::CountMenuGroups(), \c #AIMenuSuite::GetNthMenuGroup(),
	and \c #AIMenuSuite::GetMenuGroupName(). Create the subgroup only if it is not found.
  	Then you can use \c #AIMenuSuite::AddMenuGroup() to add the following
  	two menu groups or others after them.
	*/
#define kEditColorsMenuGroupPriority	0x7d000000
/** Menu group for the Color Harmony plugin's commands. */
#define kAdobeColorHarmonyMenuGroup		"Adobe Color Harmony Editor Menu Group"
/** Menu group for other Adobe Color filters. To install items in the Edit Colors
	menu group, use a priority less than \c kAdobeColorFiltersMenuGroup, and
	insert a separator before your menu items.*/
#define kAdobeColorFiltersMenuGroup		"Adobe Color Filters Menu Group"

/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kDocumentSupportMenuGroup		"AIPlugin Document Support"

/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kAssetMgmtMenuGroup		"Adobe Plugin Asset Mgmt"
/** Added by a plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kWorkgroupMenuGroup		kDocumentSupportMenuGroup

/** Added by the scripting plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kScriptsMenuGroup 		"ScriptsMenuGroup"

/** Added by the workspaces plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kWorkspacesMenuGroup		"WorkspacesMenuGroup"
/** Added by the workspaces plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kWorkspacesCustomMenuGroup	"WorkspacesCustomMenuGroup"
/** Added by the workspaces plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kWorkspacesPresetsMenuGroup	"WorkspacesPresetsMenuGroup"

/** Added by the InfoGraphics plug-in. See \c #AIMenuSuite::AddMenuGroup(). */
#define kAIChartsMenuGroup			"Adobe Charts"



// end of the MenuGroups documentation group
/** @} */


#endif

