#ifndef __AIMenu__
#define __AIMenu__

/*
 *        Name:	AIMenu.h
 *      Author:
 *        Date:
 *     Purpose: Adobe Illustrator Menu Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2015 Adobe Systems Incorporated.
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

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __ASHelp__
#include "ASHelp.h"
#endif

#ifndef _IAIUNICODESTRING_H_
#include "IAIUnicodeString.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIMenu.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIMenuSuite					"AI Menu Suite"
#define kAIMenuVersion11				AIAPI_VERSION(11)		// In AI14

// latest version
#define kAIMenuSuiteVersion				kAIMenuVersion11
#define kAIMenuVersion					kAIMenuSuiteVersion


/** @ingroup Notifiers
	Sent when a menu item is modified using
	\c #AIMenuSuite functions. Receives no associated data. */
#define kAIMenuChangedNotifier			"AI Menu Changed Notifier"

/** @ingroup Callers
	Menu caller, see \c #AIMenuSuite. */
#define kCallerAIMenu					"AI Menu"

/** @ingroup Selectors
	Sent to the plug-in that installed a menu item when the item is
	selected by the user. If the plug-in has installed more
	than one menu item, compare the menu handle in the
	\c #AIMenuMessage to those it has saved in its \c globals record.
*/
#define kSelectorAIGoMenuItem			"AI Go"
/** @ingroup Selectors
	Sent on mouse down in the menu bar. Provides an opportunity for
	a plug-in to change the appearance of a menu before it is displayed.
	Request this selector by setting \c #kMenuItemWantsUpdateOption. This is
	the only context in which \c #AIMenuSuite::GetUpdateFlags() returns valid values.

	If a plug-in with a menu is unloaded, it must first be
	reloaded before it can process the update selector. This can
	cause a noticeable performance lag when the user clicks the menu bar.
	Unless there is a pressing reason for a custom menu update,
	use \c #AIMenuSuite::UpdateMenuItemAutomatically()
	instead of requesting this selector.
*/
#define kSelectorAIUpdateMenuItem		"AI Update"


/** Option flags that control the behavior of a menu item.
	See \c #kMenuItemNoOptions and following. */
typedef ai::int32 AIMenuItemOption;
/** Bit flags for \c #AIMenuItemOption */
enum  {
	/** Turn off all options */
	kMenuItemNoOptions    				= 0,
	/** Set to receive the \c #kSelectorAIUpdateMenuItem selector. */
	kMenuItemWantsUpdateOption			= (1<<0),
	/** Set to disallow disabling (graying) of item. */
	kMenuItemAlwaysEnabled				= (1<<1),
	/** Set to create a separator. Pass \c NULL for
		\c #AIPlatformAddMenuItemDataUS::itemText. */
	kMenuItemIsSeparator				= (1<<2),
	/** Not for item creation. Identifies a group header when iterating
	through items. See \c #AIMenuSuite::SetMenuGroupHeader(). */
	kMenuItemIsGroupHeader				= (1<<3),
	/** Set to ignore the parent group's
		\c #kMenuGroupSortedAlphabeticallyOption state. */
	kMenuItemIgnoreSort					= (1<<4)
};

/** Option flags that control the behavior of a menu group.
	See \c #kMenuGroupNoOptions and following.*/
typedef ai::int32 AIMenuGroupOption;
/** Bit flags for \c #AIMenuGroupOption */
enum  {
	/** Turn off all options */
	kMenuGroupNoOptions					 = 0,
	/** Set to sort menu items in the group alphabetically.
		By default, menu items appear in the order in which they are added. */
	kMenuGroupSortedAlphabeticallyOption = (1<<0),
	/** Set to create a separator above the group. */
	kMenuGroupSeparatorOption			= (1<<1),
	/** Set to create a separator below the group. */
	kMenuGroupSeparatorBelowOption		= (1<<2),
	/** Not for group creation. Identifies a group with a header when iterating
	through groups. See \c #AIMenuSuite::SetMenuGroupHeader(). */
	kMenuGroupHasHeader					= (1<<3),
	/** Option for adding a group with \c #AIMenuSuite::AddMenuGroup() */
	kMenuGroupAddAboveNearGroup			= (1<<4)
};


/** The update action to be performed when all criteria are met.
	Specify only one action. See \c #AIMenuSuite::UpdateMenuItemAutomatically(). */
enum AIAutoMenuUpdateAction {
	/** Enables the item if the criteria evaluate to true, disables it otherwise. */
	kAutoEnableMenuItemAction			= (1<<0),
	/** Puts a check mark by the item if the criteria evaluate to true, removes
		the check otherwise. */
	kAutoCheckMenuItemAction			= (1<<1)
};

/** Types of art objects whose appearance in a document or selection
	can be considered for automatic menu update.
	See \c #AIMenuSuite::UpdateMenuItemAutomatically(). */
enum AIAutoMenuUpdateObjectCriteria {
	/** Any type of group. */
	kIfGroup							= (1<<0),
	/** Any type of path. */
	kIfPath								= (1<<1),
	/** An internal object type unavailable to users and plug-ins. */
	kIfPostscript						= (1<<2),
	/** A placed object. */
	kIfPlaced							= (1<<3),
	/** Any type of text. */
	kIfText								= (1<<4),
	/** A path that has text in or on it. Can be set even
		if \c kIfText is off, when a text path is direct-selected. */
	kIfTextPath							= (1<<5),
	/** Obsolete */
	kIfTextFlow							= (1<<6),
	/** Obsolete */
	kIfTextRun							= (1<<7),
	/** Art used as a guide. */
	kIfGuide							= (1<<8),
	/** A graph object */
	kIfGraphData						= (1<<9),
	/** Art used as a clipping mask. */
	kIfMask								= (1<<10),
	/** Obsolete */
	kIfEndMask							= (1<<11),
	/** A simple group. */
	kIfNormalGroup						= (1<<12),
	/** A group that is a compound path. */
	kIfCompoundGroup					= (1<<13),
	/** Obsolete. Do not use. */
	kIfWrapAroundGroup					= (1<<14),
	/** A group with a clipping path. */
	kIfClipGroup						= (1<<15),
	/** Point text. */
	kIfPointText						= (1<<16),
	/** Text in a path. */
	kIfInPathText						= (1<<17),
	/** Text on a path. */
	kIfOnPathText						= (1<<18),
	/** Threaded text. */
	kIfThreadedText						= (1<<19),
	/** Raster art. */
	kIfRaster							= (1<<20),
	/** Plug-in group (for any platform). */
	kIfPluginArt						= (1<<21),	// AI8
	/** Mesh art. */
	kIfMesh								= (1<<22),	// AI8
	/** Styled art. */
	kIfHasStyledArt						= (1<<23),	// AI9
	/** Symbol. */
	kIfSymbol							= (1<<24),	// AI10
	/** Foreign object. */
	kIfForeignArt						= (1<<25),	// AI11
	/** Legacy text. */
	kIfLegacyTextArt					= (1<<26),	// AI11
	/** Path that is not inside a planar group. */
	kIfClassicPath						= (1<<27),	// AI12
	/** Path that is inside a planar group. See \c #AIPlanarObjectSuite. */
	kIfPlanarPath						= (1<<28), // AI12
	/** A path that does not have text in or on it. */
	kIfNonTextPath						= (1<<29), // AI12
	/** Chart. */
	kIfChartArt							= (1<<30),	// AI19
	/** Any art. */
	kIfAnyArt							= (0xFFFFFFFF)	//	AI11
};


/** For pre-AI14 compatibility */
#define kMacIfPlugin kIfPluginArt

/** Document properties that can be considered for automatic
	menu update. See \c #AIMenuSuite::UpdateMenuItemAutomatically(). */
enum AIAutoMenuUpdatePropertyCriteria {
	kIfCurrentLayerIsEditable			= (1<<0),
	kIfOpenTextEdit						= (1<<1),
	kIfAnyPrintingChars					= (1<<2),
	kIfAnyHiddenObjects					= (1<<3),
	kIfAnyLockedObjects					= (1<<4),
	kIfAnyClipPaths						= (1<<5),
	kIfOpenDocument						= (1<<6),
	kIfCMYKDocument						= (1<<7),		// AI9
	kIfRGBDocument						= (1<<8),		// AI9
	kIfCurrentArtStyleIsNamed			= (1<<9),		// AI9
	kIfHasPluginSelection				= (1<<10)		// AI12
};

/** Modifier keys for command characters (keyboard shortcuts).
	See \c #AIMenuSuite::SetItemCmd() and \c #AIMenuSuite::GetItemCmd(). */
enum AIMenuItemModifier {
	/** Shift key */
	kMenuItemCmdShiftModifier			= 1,
	/** Option key in Mac OS, Alt key in Windows. */
	kMenuItemCmdOptionModifier			= 2,
	/** Command key in Mac OS,  Ctrl key in Windows. */
	kMenuItemCmdControlModifier			= 4		// the control key on the Mac.
};


/** @ingroup Errors */
#define kTooManyMenuItemsErr			'>MIT'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference to a menu item. Never dereferenced.
Access with \c #AIMenuSuite functions.  */
typedef struct _t_AIMenuItemOpaque	*AIMenuItemHandle;
/** Opaque reference to a menu group. Never dereferenced.
Access with \c #AIMenuSuite functions. */
typedef struct _t_MenuGroupOpaque	*AIMenuGroup;   // new for AI7.0

#if Macintosh
	/** Platform-specific menu reference. \li In Mac OS, a \c MenuRef.
		\li In Windows, cast to \c HMENU.*/
	typedef struct MacMenu_t* AIPlatformMenuHandle;
#elif MSWindows
	/** Platform-specific menu reference. \li In Mac OS, a \c MenuRef.
		\li In Windows, cast to \c HMENU. */
	typedef struct WinMenu	**AIPlatformMenuHandle;	 // can cast it to HMENU
#endif

/** Menu item definition data. */
typedef struct {
	/** The menu group to which an item is added. See @ref menuGroups.*/
	const char *groupName;
	/** The display label for an item. (To create a menu separator
		set the \c #kMenuItemIsSeparator options flag and set this
		to \c NULL.) */
	ai::UnicodeString itemText;
} AIPlatformAddMenuItemDataUS;

/** A platform-specific menu structure corresponding to an
	Illustrator menu item.
	See \c #AIMenuSuite::GetPlatformMenuItem(). */
typedef struct {
	/** An \c HMENU in Windows, a \c MenuRef in Mac OS. */
	AIPlatformMenuHandle menu;
	/** The index of the item in the platform menu. */
	ai::int16 item;
} AIPlatformMenuItem;

/** Message sent with menu selectors. */
typedef struct {
	/** The message data. */
	SPMessageData d;
	/** The  menu item object. */
	AIMenuItemHandle menuItem;
} AIMenuMessage;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides functions that allow you to add menu items to
	the Illustrator menu structure.

	A menu can be a stand alone interface to a plug-in feature, or
	group a number of features together. Plug-ins of all types can have
	an associated plug-in menu item. For instance, if you define a
	palette (non-modal dialog box), you typically add a menu item to the
	Windows menu to hide and show your window.

	This section describes how to install and use plug-in menu items. It discusses
	the caller, selectors and messages that plug-in menus receive, as well as the
	functions provided to add menus, set options, and control menu appearance,
	and to make simple appearance changes automatically based on the changes in
	artwork.

	Menu plug-ins are similar to Filter plug-ins (see the \c #AIFilterSuite),
	but are different in these ways:
		\li Filter plug-ins are added to the Filter menu, while menu plug-ins
			can add commands to any menu.
		\li Filters have automatic repeat and undo, while menu plug-ins must set
			the Undo menu item text.
		\li Menu plug-ins can set command keys and control their appearance.
		\li Both plug-in types receive a go selector, but Filters also receive
			a selector to get parameters.

	This suite is cross-platform (although the functions closely parallel
	the Mac OS toolbox functions for changing menu appearance).
	If you must manipulate a menu item directly, use \c #GetPlatformMenuItem()
	to obtain a platform-specific menu reference.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIMenuSuite and \c #kAIMenuVersion.

	\section menuSelectors Menu Selectors

	The caller for menu plug-ins is \c #kCallerAIMenu. Check for the caller and
	these selectors in the plug-in's main function:	<br>
	<tt> #kSelectorAIGoMenuItem <br>
		#kSelectorAIUpdateMenuItem 	</tt>  <br>
	The message data for both selectors is passed in an \c #AIMenuMessage.

	\section menuNotifiers Menu Notifiers

	The notifier \c #kAIMenuChangedNotifier	is sent when a menu is
	modified.

	Notifiers are available before and after menu commmands are executed.

	\li The pre- and post-menu notifiers for Illustrator commands do not have
		predefined constants. Instead, the notification identification string
		is generated dynamically, in the following format:<br><br>
		 	"AI Command Notifier: Before " + \e menu \e identifier \e text <br>
			"AI Command Notifier: After " + \e menu \e identifier \e text <br><br>
		The menu identifiers are defined in \c AIMenuCommandNotifiers.h.


	\section menuGroups Menu Groups

	Plug-in menu items are added to menu \e groups, which are predefined locations
	within Illustrator’s menu structure. The complete list of groups is found
	in the \c AIMenuGroups.h.  Some examples of menu groups are: <br><br>
		\c #kOpenMenuGroup <br>
		\c #kArrangeMoveMenuGroup <br>
		\c #kTypeSizeMenuGroup

	The names describe the menu location. A \e utilities group is located at
	the top to a menu group; for instance, the "Type Size Utilities"
	menu group is at the top of the "Type Size" submenu.

	You can create new menu groups, to which your plug-in or other plug-ins
	can add menu items. As a plug-in developer, you are responsible for
	documenting any menu groups you add.

	\subsection pluginMenuGroups Plug-in Menu Groups

	To use a menu group added by a plug-in (rather than the application),
	your plug-in should explicitly add the group, using \c #AddMenuGroup().
	If is safe to add a menu group twice;
	the second call returns the existing group reference.
	The following predefined groups are added by plug-ins: <br><br>
		\c #kDocInfoMenuGroup <br>
  		\c #kObjectRasterMenuGroup <br>
  		\c #kArrangeTransformMultipleMenuGroup <br>
		\c #kATMMenuGroupNearGroup <br>
		\c #kObjectPathsPopoutPluginMenuGroup <br>
		\c #kOPPPMenuGroupNearGroup	<br>
		\c #kDocumentSupportMenuGroup <br>
		\c #kAssetMgmtMenuGroup	<br>
		\c #kWorkgroupMenuGroup	<br>
		\c #kScriptsMenuGroup <br>
		\c #kWorkspacesMenuGroup <br>
		\c #kWorkspacesPresetsMenuGroup <br>
		\c #kWorkspacesCustomMenuGroup

	@note The \c #kFilterUtilities menu is implemented using an
	internal plug-in. To use it, you must acquire the \c #AIFilterSuite.

*/
typedef struct {

	/** Creates and installs a plug-in menu item.
			@param self	This plug-in.
			@param inKeyboardShortDictionaryKey A unique identifying name
				for this item in the \c keyboardshortcut dictionary, or \c NULL
				if the item is dynamic or has no shortcut.
			@param data	The menu group to which the item is added, and the display
				label for the item as a Unicode string.
			@param options Flags that control the item's behavior, a logical OR
				of \c #AIMenuItemOption values.
			@param menuItem	[out] A buffer in which to return the menu item object.
				If your plug-in installs multiple items, store this in \c globals
				to compare when receiving a notification or selector.
				May be \c NULL.
	*/
	AIAPI AIErr (*AddMenuItem) ( SPPluginRef self, const char*inKeyboardShortDictionaryKey,
				AIPlatformAddMenuItemDataUS *data, AIMenuItemOption options,
				AIMenuItemHandle *menuItem );

	/** Creates and installs a plug-in menu item using a ZString display label.
			@param self	This plug-in.
			@param inKeyboardShortDictionaryKey A unique identifying name
				for this item in the \c keyboardshortcut dictionary, or \c NULL
				if the item is dynamic or has no shortcut.
			@param groupName The menu group to which the item is added.
			@param data	The ZString display label for the item.
			@param options Flags that control the item's behavior, a logical OR
				of \c #AIMenuItemOption values.
			@param menuItem	[out] A buffer in which to return the menu item object.
				If your plug-in installs multiple items, store this in \c globals
				to compare when receiving a notification or selector. */
	AIAPI AIErr (*AddMenuItemZString) ( SPPluginRef self, const char*inKeyboardShortDictionaryKey,
				const char *groupName, ZRef itemText, AIMenuItemOption options,
				AIMenuItemHandle *menuItem );

	/** Retrieves the \c keyboardshortcut dictionary key of a menu item.
			@param menuItem The menu item object.
			@param outKey [out] A buffer in which to return the	key string. Do not modify.
		*/
	AIAPI AIErr (*GetMenuItemKeyboardShortcutDictionaryKey) ( AIMenuItemHandle menuItem, const char**outKey );

	/** Retrieves the option flags of a menu item.
			@param menuItem The menu item object.
			@param options [out] A buffer in which to return the options, a logical
				OR of \c #AIMenuItemOption values.
		*/
	AIAPI AIErr (*GetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption *options );

	/** Set the option flags for a menu item.
			@param menuItem The menu item object.
			@param options The options, a logical OR of \c #AIMenuItemOption values.
		*/
	AIAPI AIErr (*SetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption options );

	/** Retrieves the plug-in that installed a menu item.
			@param menuItem The menu item object.
			@param options [out] A buffer in which to return the plug-in object.
		*/
	AIAPI AIErr (*GetMenuItemPlugin) ( AIMenuItemHandle menuItem,
				SPPluginRef *plugin );

	/** Gets the number of installed menu items. Use with \c #GetNthMenuItem()
		to iterate through items.
			@param count [out] A buffer in which to return the number of items.
				May be \c NULL.
		*/
	AIAPI AIErr (*CountMenuItems) ( ai::int32 *count );

	/** Retrieves an installed menu item by index position. Use with
		\c #CountMenuItems() to iterate through items.
			@param n The position index, in the range <code>[0..numItems-1]</code>.
			@param menuItem [out] A buffer in which to return the menu item object.
		*/
	AIAPI AIErr (*GetNthMenuItem) ( ai::int32 n, AIMenuItemHandle *menuItem );

	/** Retrieves the platform-specific menu item reference associated with a menu item.
			@param menuItem The menu item object.
			@param platformMenuItem [out] A buffer in which to return the
				platform-specific object. The menu handle
				is a \c MenuInfo structure in Mac OS, a \c WinMenu structure in Windows.
		*/
	AIAPI AIErr (*GetPlatformMenuItem) ( AIMenuItemHandle menuItem,
				AIPlatformMenuItem *platformMenuItem );

	/** Updates a menu item's appearance automatically when specified conditions
		are met. You can either enable/disable, or check/uncheck the item with one call;
		you cannot perform both types of update at once.

		All criteria are evaluated and the results combined with a
		logical AND to decide whether to make the specified appearance modification.
			\li The results of the positive criteria are combined to produce a
		positive result, which is true if any of the positive criteria are true.
			\li The results of the negative criteria are combined to produce a
		negative result, which is true if none of the negative criteria are true.
			\li The combined result used to perform the update action is true if
		both the positive and negative results are true--that is, if any of the
		desired properties are present and none of the undesired properties are
		present.

			@param menuItem The menu item object.
			@param action The action to take when criteria are satisfied.
				An \c #AIAutoMenuUpdateAction value.
			@param ifObjectIsInArtwork Update if any object matching any specified type
				appears in the current document's artwork tree. A logical OR of
				\c #AIAutoMenuUpdateObjectCriteria values.
			@param ifObjectIsNotInArtwork Update if no object matching any specified type
				appears in the current document's artwork tree. A logical OR of
				\c #AIAutoMenuUpdateObjectCriteria values.
			@param ifObjectIsSelected Update if any object matching any specified type
				appears in the current document's selection. A logical OR of
				\c #AIAutoMenuUpdateObjectCriteria values.
			@param ifObjectIsNotSelected Update if no object matching any specified type
				appears in the current document's selection. A logical OR of
				\c #AIAutoMenuUpdateObjectCriteria values.
			@param ifIsTrue	Update if any of the specified document properties are true
				for the current document. A logical OR of
				\c #AIAutoMenuUpdatePropertyCriteria values.
			@param ifIsNotTrue Update if none of the specified document properties are true
				for the current document. A logical OR of
				\c #AIAutoMenuUpdatePropertyCriteria values.
	*/
	AIAPI AIErr (*UpdateMenuItemAutomatically) ( AIMenuItemHandle menuItem,
				ai::int32 action,
				ai::int32 ifObjectIsInArtwork, ai::int32 ifObjectIsNotInArtwork,
				ai::int32 ifObjectIsSelected, ai::int32 ifObjectIsNotSelected,
				ai::int32 ifIsTrue, ai::int32 ifIsNotTrue );

	/** Retrieves document and artwork state information that you can use
		to update a menu item’s checked or enabled state.
		This is faster than scanning the artwork tree or getting specific art,
		as Illustrator has already computed the information for automatic
		menu updates.

		Call this only when the \c #kSelectorAIUpdateMenuItem selector
		is received. The information is invalid if the call is made at any other time.
		The \c #kMenuItemWantsUpdateOption option must be set for the
		plug-in to receive this selector.
			@param inArtwork [out] A buffer in which to return a set of flags
			 	for types of art that are contained in the current document's
			 	artwork tree. A logical OR of \c #AIAutoMenuUpdateObjectCriteria values.
			@param isSelected [out] A buffer in which to return a set of flags
			 	for types of art that are contained in the current document's
			 	selection. A logical OR of \c #AIAutoMenuUpdateObjectCriteria values.
			@param isTrue [out] A buffer in which to return a set of flags
			 	for document properties that are true for the current document.
				 A logical OR of \c #AIAutoMenuUpdatePropertyCriteria values.
		*/
	AIAPI AIErr (*GetUpdateFlags)( ai::int32 *inArtwork, ai::int32 *isSelected, ai::int32 *isTrue );

	/*-------------------------------------------------------------------------------------------*/

	/** Enables a menu item.
			@param menuItem The menu item object.
		*/
	AIAPI AIErr (*EnableItem) ( AIMenuItemHandle menuItem);
	/** Disables (grays out) a menu item.
			@param menuItem The menu item object.
		*/
	AIAPI AIErr (*DisableItem) ( AIMenuItemHandle menuItem);

	/** Retrieves the localizable display label of a menu item.	This is different
		from the unique identifying name returned by
		\c #GetMenuItemKeyboardShortcutDictionaryKey().
			@param menuItem The menu item object.
			@param itemString [out] A buffer in which to return the label string.
		*/
	AIAPI AIErr (*GetItemText) ( AIMenuItemHandle menuItem, ai::UnicodeString &itemString );

	/** Sets the localizable display label of a menu item using a Unicode string.
			@param menuItem The menu item object.
			@param itemString The new label string.
		*/
	AIAPI AIErr (*SetItemText) ( AIMenuItemHandle menuItem, const ai::UnicodeString &itemString );

	/** Sets the localizable display label of a menu item using a ZString.
			@param menuItem The menu item object.
			@param itemString The new label ZString.
		*/
	AIAPI AIErr (*SetItemTextZString) ( AIMenuItemHandle menuItem, ZRef itemString );

	/** Sets the checked state of a menu item.
			@param menuItem The menu item object.
			@param bCheckIt True to check the item, false to uncheck it.
		*/
	AIAPI AIErr (*CheckItem) ( AIMenuItemHandle menuItem, AIBoolean bCheckIt );

	/** Retrieves the menu group to which a menu item belongs.
			@param menuItem The menu item object.
			@param group [out] A buffer in which to return the menu group.
		*/
	AIAPI AIErr (*GetItemMenuGroup) ( AIMenuItemHandle menuItem, AIMenuGroup *group );

	/** Creates a new menu group, to which you can add your plug-in menu items.
		If the group already exists, returns the group reference. See @ref menuGroups.
			@param name The unique identifying name, which can be passed to \c #AddMenuItem().
			@param options Flags that control the behavior of the menu group,
				a logical OR of \c #AIMenuGroupOption values.
			@param nearGroup An existing menu group for relative placement of this group.
				The new group is added below this one, unless the options include
				\c #kMenuGroupAddAboveNearGroup, in which case it is added above this one.

				If this is a submenu created by \c #AddMenuGroupAsSubMenu(),
				the new menu group becomes part of that submenu, and is added above or below
				other menu items or groups that were previously added to the submenu, depending
				on the options.
			@param group [out] A buffer in which to return the menu group object.
			@return The error \c #kBadParameterErr if the relative group does not yet exist.
				The loading order of plug-ins is indeterminate; if the relative group is
				one that might be created by a different plug-in, your plug-in should
				check for an error and either create the group or add near a different group.
				It is all right to add the same group multiple times.
		*/
	AIAPI AIErr (*AddMenuGroup) ( const char* name, AIMenuGroupOption options, const char* nearGroup,
				AIMenuGroup *group );

	/** Adds a new menu group as a submenu. A submenu can be updated
		programmatically or automatically, like a top-level menu.
		Nested submenus are allowed.
			@param name	The unique identifying name, which can be passed to \c #AddMenuItem().
			@param options Flags that control the behavior of the menu group,
				a logical OR of \c #AIMenuGroupOption values.
			@param menuItem	The menu item that invokes this submenu.
			@param group [out] A buffer in which to return the menu group object.
		*/
	AIAPI AIErr (*AddMenuGroupAsSubMenu) ( const char* name, AIMenuGroupOption options, AIMenuItemHandle menuItem, AIMenuGroup *group);

	/** Retrieves the unique identifying name of a menu group.
			@param group The menu group object.
			@param name [out] A buffer in which to return the name string. Do not modify.
		*/
	AIAPI AIErr (*GetMenuGroupName) ( AIMenuGroup group,  const char**name);

	/** Retrieves the option flags of a menu group.
			@param group The menu group object.
			@param options [out] A buffer in which to return the options, a
				logical OR of \c #AIMenuGroupOption values.
		*/
	AIAPI AIErr (*GetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption *options );

	/** Sets  the option flags of a menu group.
			@param group The menu group object.
			@param options The new options, a logical OR of \c #AIMenuGroupOption values.
		*/
	AIAPI AIErr (*SetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption options );

	/** Retrieves a reference to the platform-specific menu structure for a menu
		with the range of items that belong to a menu group.
			@param group The menu group object.
			@param theMenu [out] A buffer in which to return the platform-specific menu information.
				The menu handle is a \c MenuInfo structure in Mac OS,
				a \c WinMenu structure in Windows.
			@param firstItem [out] A buffer in which to return the index of the first item
				in the group.
			@param numItems [out] A buffer in which to return the number of items in the group.
		*/
	AIAPI AIErr (*GetMenuGroupRange) ( AIMenuGroup group, AIPlatformMenuHandle *theMenu,
				ai::int16 *firstItem, ai::int16 *numItems );

	/** Gets the number of installed menu groups.  Use with
		\c #GetNthMenuGroup() to iterate through all menu groups.
			@param count [out] A buffer in which to return the number of groups.
		*/
	AIAPI AIErr (*CountMenuGroups) ( ai::int32 *count );

	/** Retrieves a menu group by position index. Use with
		\c #CountMenuGroups() to iterate through all menu groups.
			@param n The position index, in the range <code>[0..numGroups-1]</code>.
			@param group [out] A buffer in which to return the menu group object.
		*/
	AIAPI AIErr (*GetNthMenuGroup) ( ai::int32 n, AIMenuGroup *group );

	/** Retrieves the command character and modifier keys that act as the
		keyboard shortcut for a menu item.
		 	@param menuItem The menu item object.
			@param cmdChar [out] A buffer in which to return the command character (keyboard shortcut).
			@param modifiers [out] A buffer in which to return the command character modifiers,
				a logical OR of \c #AIMenuItemModifier constants.
			@note Submenus created by plug-ins do not support modified command keys. */
	AIAPI AIErr (*GetItemCmd) ( AIMenuItemHandle menuItem, ai::int16 *cmdChar, ai::int16 *modifiers );

	/** Sets the command character and modifier keys that act as the
		keyboard shortcut for a menu item.
		 	@param menuItem The menu item object.
			@param cmdChar The command character (keyboard shortcut).
			@param modifiers The command character modifiers, a logical OR of
				 \c #AIMenuItemModifier constants.
			@note Submenus created by plug-ins do not support modified command keys. */
	AIAPI AIErr (*SetItemCmd) ( AIMenuItemHandle menuItem, char cmdChar, ai::int16 modifiers );

	/** Retrieves the function key and modifiers associated	with a menu item.
		 	@param menuItem The menu item object.
			@param fkey [out] A buffer in which to return the function key.
			@param modifiers [out] A buffer in which to return the function key modifiers,
				a logical OR of \c #AIMenuItemModifier constants.
		 */
	AIAPI AIErr (*GetItemFunctionKey) ( AIMenuItemHandle menuItem, ai::int16 *fkey, ai::int16 *modifiers );

	/** Sets the function key and modifiers associated with a menu item.
		 	@param menuItem The menu item object.
			@param fkey The function key, in the range [1..15].
			@param modifiers The function key modifiers, a logical OR of
				 \c #AIMenuItemModifier constants.
		 */
	AIAPI AIErr (*SetItemFunctionKey) ( AIMenuItemHandle menuItem, ai::int16 fkey, ai::int16 modifiers );

	/** Reports whether a menu item is enabled.
		 	@param menuItem The menu item object.
			@param bEnables [out] A buffer in which to return true if the item is enabled, false
				if it is disabled (grayed).
		*/
	AIAPI AIErr (*IsItemEnabled) ( AIMenuItemHandle menuItem, ASBoolean *bEnabled);

	/** Reports whether a menu item is checked.
		 	@param menuItem The menu item object.
			@param bCheckIt [out] A buffer in which to return true if the item is checked, false
				if it is unchecked.
		 */
	AIAPI AIErr (*IsItemChecked) ( AIMenuItemHandle menuItem, AIBoolean *bCheckIt );

	/** Deletes a menu item.
			 @param menuItem The menu item object. After the call, this reference is invalid.
		*/
	AIAPI AIErr (*RemoveMenuItem) ( AIMenuItemHandle menuItem );

	/** Sets the header for a menu group. When a menu has a header,
		the \c #kMenuGroupHasHeader	option flag is set for the group, and the
		menu contains a non-selectable item for which the
		\c #kMenuItemIsGroupHeader option flag is set. All other items in the group
		are shown below and indented from the header text.
			@param inGroup The menu group object.
			@param inHeader The header string, or an empty string to remove the group header.
		*/
	AIAPI AIErr (*SetMenuGroupHeader) (AIMenuGroup inGroup, const ai::UnicodeString &inHeader);

	/** Programmatically invokes a menu action, as if the user had clicked the menu item.
		@param menuCmdID The command ID for the menu item.
	*/
	AIAPI AIErr	(*InvokeMenuAction)(AICommandID menuCmdID);

} AIMenuSuite;


#include "AIHeaderEnd.h"

#endif
