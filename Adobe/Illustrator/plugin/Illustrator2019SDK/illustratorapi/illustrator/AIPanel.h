/*************************************************************************
*
*ADOBE SYSTEMS INCORPORATED
* Copyright 2016 Adobe Systems Incorporated
* All Rights Reserved.
*
*NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
*terms of the Adobe license agreement accompanying it.  If you have received this file from a 
*source other than Adobe, then your use, modification, or distribution of it requires the prior 
*written permission of Adobe.
*
**************************************************************************/

#ifndef __AIPANEL_H__
#define __AIPANEL_H__

#include "AITypes.h"
#include "IAIUnicodeString.h"
#include "IAIAutoBuffer.h"
/** @file AIPanel.h */

/*******************************************************************************
**
**	Constants
**
**/

#define kAIPanelSuite					"AI Panel Suite"
#define kAIPanelSuiteVersion4			AIAPI_VERSION(4)
#define kAIPanelSuiteVersion			kAIPanelSuiteVersion4
#define kAIPanelVersion					kAIPanelSuiteVersion


#define kAIPanelFlyoutMenuSuite				"AI Panel Flyout Menu Suite"
#define kAIPanelFlyoutMenuSuiteVersion2		AIAPI_VERSION(2)
#define kAIPanelFlyoutMenuSuiteVersion		kAIPanelFlyoutMenuSuiteVersion2
#define kAIPanelFlyoutMenuVersion			kAIPanelFlyoutMenuSuiteVersion

/*******************************************************************************
**
** Types
**
**/
#ifdef WIN_ENV
	typedef HWND AIPanelPlatformWindow;
#elif defined(MAC_ENV)
    #ifdef __OBJC__
	@class NSView;
	typedef NSView*	AIPanelPlatformWindow;
    #else
    typedef void*	AIPanelPlatformWindow;
    #endif
#else
#error unknown configuration
#endif

/** An opaque reference to a panel. See \c #AIPanelSuite. */
typedef struct _opaque_AIPanel* AIPanelRef;

/** An opaque reference to a panel flyout menu. See \c #AIPanelFlyoutMenuSuite. */
typedef struct _opaque_AIPanelFlyoutMenu* AIPanelFlyoutMenuRef;

/** Constants for the glyphs that mark a menu item as selected.
    See \c #AIPanelFlyoutMenuSuite. */
enum {
	kAIPanelFlyoutMenuItemMark_NONE,
	kAIPanelFlyoutMenuItemMark_CHECK,
	kAIPanelFlyoutMenuItemMark_BULLET,
	kAIPanelFlyoutMenuItemMark_DASH
};

/** The glyph that marks a menu item as selected.
    See \c #AIPanelFlyoutMenuSuite. */
typedef ai::uint32 AIPanelFlyoutMenuItemMark;

/** A developer-defined data object that can be associated with a panel.
    See \c #AIPanelSuite. */
typedef void* AIPanelUserData;

/** Prototype of a function that is called before a panel's flyout menu is made visible.
        @param inPanel The panel object.
    	@see \c #AIPanelFlyoutMenuSuite.
*/
typedef void AIAPI (*AIPanelFlyoutMenuPreVisibilityProc)(AIPanelRef inPanel);

/** Prototype of a function that is called after a panel's flyout menu has been shown.
	@param inPanel		The panel object.
	@param itemID		The selected item ID. Zero value of itemID means user cancelled the menu without selecting any item.
    @see \c #AIPanelFlyoutMenuSuite.
*/
typedef void AIAPI (*AIPanelFlyoutMenuProc)(AIPanelRef inPanel, ai::uint32 itemID);

/** Prototype of a function that is called after the visibility of a panel is changed.
	@param inPanel		The panel object.
	@param isVisible	The new visibility of the panel
    @see \c #AIPanelSuite.
*/
typedef void AIAPI (*AIPanelVisibilityChangedNotifyProc)(AIPanelRef inPanel, AIBoolean isVisible);

/** Prototype of a function that is called after the size of a panel is changed.
	@param inPanel		The panel object.
    @see \c #AIPanelSuite.
*/
typedef void AIAPI (*AIPanelSizeChangedNotifyProc)(AIPanelRef inPanel);

/** Prototype of a function that is called after the state of a panel is changed.
	@param inPanel		The panel object.
	@param newState		The new panel state
    @see \c #AIPanelSuite.
*/
typedef void AIAPI (*AIPanelStateChangedNotifyProc)(AIPanelRef inPanel, ai::int16 newState);

/** Prototype of a function that is called after a panel is closed by clicking on the close button.
	@param inPanel		The panel object.
    @see \c #AIPanelSuite.
*/
typedef void AIAPI (*AIPanelClosedNotifyProc)(AIPanelRef inPanel);


/************************************************************************/
/// Error Values return by the suite
/************************************************************************/
/** @ingroup Errors
    @see \c #AIPanelSuite.
	*/
#define kAIInvalidPanelRef			'INVD'



/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
Provides functions for creating and managing panels.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIPanelSuite	and \c #kAIPanelSuiteVersion.
*/

struct AIPanelSuite{

	/** Creates a new panel.
	@param inPluginRef		The plug-in that creates the panel.
	@param inID				A unique identifier for the new panel.
	@param inTitle			The title of the panel.
	@param inStateCount 	The number of host layouts for the panel; must be at least 1.
	@param inMinSize		Minimum size of the panel.
	@param isResizable		True to make the panel resizable.
	@param inFlyoutMenu		The flyout menu for the panel, or NULL to hide the flyout icon.
	@param inUserData		Developer-defined data to be associated with the panel.
	@param outPanel			[out] A buffer in which to return the new panel object.
 	*/
	AIAPI AIErr	(*Create)(SPPluginRef inPluginRef, const ai::UnicodeString& inID, const ai::UnicodeString& inTitle,
							ai::int16 inStateCount, const AISize& inMinSize, AIBoolean isResizable,
							AIPanelFlyoutMenuRef inFlyoutMenu, AIPanelUserData inUserData, AIPanelRef& outPanel);


	/** Deletes a panel object.
	This must be called when the plug-in receives \c #kAIApplicationShutdownNotifier.
	@param inPanel			The panel object.
 	**/
	AIAPI AIErr	(*Destroy)(AIPanelRef inPanel);


	/** Retrieves the platform-specific window/view used for the panel.
	@param inPanel			The panel object.
	@param outPlatformWindow The platform specific window/view of the panel
    **/
	AIAPI AIErr (*GetPlatformWindow)(AIPanelRef inPanel, AIPanelPlatformWindow& outPlatformWindow);


	/** Shows or hides the panel. If the panel is part of a tab group,
	 the whole group is affected
	@param inPanel			The panel object.
	@param inShow			True to make panel visible, false to hide it
	  **/
	AIAPI AIErr	(*Show)(AIPanelRef inPanel, AIBoolean inShow);



	/** Reports the effective visibility of a panel.
	If the panel is part of a tabbed group but is not the frontmost tab,
	it is not considered visible.
	@param inPanel			The panel object.
	@param outIsShown		[out] A buffer in which to return the Boolean output; True if the panel
							is effectively visible, False otherwise.
	  **/
	AIAPI AIErr (*IsShown)(AIPanelRef inPanel, AIBoolean& outIsShown);


	/**  Retrieves developer-defined data from a panel.
	@param inPanel			The panel object.
	@param outUserData		[out] A buffer in which to return developer-defined data
							associated with the panel.
	  **/
	AIAPI AIErr	(*GetUserData)(AIPanelRef inPanel, AIPanelUserData& outUserData);


	/** Associates developer-defined data with a panel, which can be used
	in developer-defined callbacks.
	@param inPanel			The panel object.
	@param inUserData		The developer-defined data.
	 **/
	AIAPI AIErr	(*SetUserData)(AIPanelRef inPanel, AIPanelUserData inUserData);


	/** Sets a panel title.
	@param inPanel			The panel object.
	@param inTitle			The new title of the panel
	 **/
	AIAPI AIErr	(*SetTitle)(AIPanelRef inPanel, const ai::UnicodeString& inTitle);


	/** Retrieves the panel title.
	@param inPanel			The panel object.
	@param outTitle			[out] A buffer in which to return the title string.
	  **/
	AIAPI AIErr	(*GetTitle)(AIPanelRef inPanel, ai::UnicodeString& outTitle);


	/** Sets the icon to be used when a panel is collapsed. Only PNG icons can be used.
    @param inPanel			The panel object.
    @param inPNGData		The PNG resource data for the icon.
    @param inDataSize		The size of the resource data in bytes.
    @param inPNGDarkData	The PNG resource data for an alternate icon, to be used in "dark" mode.
    @param inDarkDataSize	The size of the alternate resource data in bytes.
    */
	AIAPI AIErr	(*SetIcon)(AIPanelRef inPanel, const ai::AutoBuffer<const ai::uint8*>& inPNGData, const ai::AutoBuffer<ai::uint32>& inDataSize,
							const ai::AutoBuffer<const ai::uint8*>& inPNGDarkData, const ai::AutoBuffer<ai::uint32>& inDarkDataSize);


    /** @deprecated. Use \c #AIPanelSuite::SetSVGIconResourceID()
    Sets the icon to be used when a panel is collapsed, using an existing resource.
    Only PNG icons can be used.
    @param inPanel			The panel object.
    @param iconResId		The resource identifier of a PNG icon.
    @param darkIconcResId	The resource identifier of an alternate PNG icon for "dark" mode.
    **/
	AIAPI AIErr	(*SetIconResourceID)(AIPanelRef inPanel, const ai::AutoBuffer<ai::uint32>& iconResId, const ai::AutoBuffer<ai::uint32>& darkIconResId);

    /** Sets the SVG icon to be used when a panel is collapsed, using an existing resource.
     @param inPanel         The panel object.
     @param iconResId		The resource identifier of a SVG icon in 2x scale factor.
     @param darkIconResId	The resource identifier of a SVG icon for "dark" mode in 2x scale factor.
     **/
    AIAPI AIErr (*SetSVGIconResourceID)(AIPanelRef inPanel, ai::uint32 iconResId, ai::uint32 darkIconResId);
    

    /** Retrieves the inner dimensions of the current panel, which excludes the frame, title, and any
		platform-specific decorations.
	@param inPanel			The panel object.
	@param outSize			[out] A buffer in which to return the size value.
	  **/
	AIAPI AIErr	(*GetSize)(AIPanelRef inPanel, AISize& outSize);


	/** Sets the minimum size for a panel's inner dimensions.
	@param inPanel			The panel object.
	@param inMinimumSize	The size value.
	  **/
	AIAPI AIErr	(*SetMinimumSize)(AIPanelRef inPanel, const AISize& inMinimumSize);


	/** Retrieves the minimum minimum size for a panel's inner dimensions.
	@param inPanel			The panel object.
	@param outMinimumSize	[out] A buffer in which to return the size value.
	 **/
	AIAPI AIErr	(*GetMinimumSize)(AIPanelRef inPanel, AISize& outMinimumSize);


	/**  Sets the maximum size for a panel's inner dimensions.
	@param inPanel			The panel object.
	@param inMaximumSize	The size value.
	 **/
	AIAPI AIErr	(*SetMaximumSize)(AIPanelRef inPanel, const AISize& inMaximumSize);


	/**  Retrieves the maximum size for a panel's inner dimensions.
	@param inPanel			The panel object.
	@param outMaximumSize	[out] A buffer in which to return the size value.
	  **/
	AIAPI AIErr	(*GetMaximumSize)(AIPanelRef inPanel, AISize& outMaximumSize);


	/** Sets both the constrained and unconstrained preferred sizes
	    for a panel's inner dimensions.
		The constrained size is used when a dialog is frame docked.
		The unconstrained size is used when the dialog is floating.

	@param inPanel			The panel object.
	@param inPreferredSize	The new preferred size value.
	 **/
	AIAPI AIErr	(*SetPreferredSizes)(AIPanelRef inPanel, const AISize& inPreferredSize);


	/** Sets all sizes at once for a panel's inner dimensions.
	@param inPanel							The panel object.
	@param inMinimumSize					Minimum panel size.
	@param inPreferredUnconstrainedSize		Preferred unconstrained panel size.		.
	@param inPreferredConstrainedSize		Preferred constrained panel size.
	@param inMaximumSize					Maximum panel size.
	@return error **/
	AIAPI AIErr	(*SetSizes)(AIPanelRef inPanel, const AISize& inMinimumSize, const AISize& inPreferredUnconstrainedSize,
							const AISize& inPreferredConstrainedSize, const AISize& inMaximumSize);


	/** For non-resizable panels, sets the minimum, maximum,
	preferred unconstrained, and preferred constrained sizes
	for a panel's inner dimensions to a single size value.
	For resizable panels, sets only the preferred unconstrained and
	constrained sizes to the given size.
	@param inPanel			The panel object.
	@param inSize			The new size value.
	 **/
	AIAPI AIErr	(*SetSize)(AIPanelRef inPanel, const AISize& inSize);


	/** Retrieves the preferred constrained size for a panel's inner dimensions.
	The constrained size is used when a dialog is frame docked.
	@param inPanel							The panel object.
	@param outPreferredConstrainedSize		[out] A buffer in which to return the size value.
	 **/
	AIAPI AIErr (*GetPreferredConstrainedSize)(AIPanelRef inPanel, AISize& outPreferredConstrainedSize);


	/** Retrieves the preferred unconstrained size for a panel's inner dimensions.
	The unconstrained size is used when the dialog is floating.
	@param inPanel							The panel object.
	@param outPreferredUnconstrainedSize	[out] A buffer in which to return the size value.
	**/
	AIAPI AIErr (*GetPreferredUnconstrainedSize)(AIPanelRef inPanel, AISize& outPreferredUnconstrainedSize);


	/** Sets the current state of a panel.
	@param inPanel			The panel object.
	@param inCurrentState	The new current state, must be at least 1.
	 **/
	AIAPI AIErr	(*SetCurrentState)(AIPanelRef inPanel, ai::int16 inCurrentState);


	/** Retrieves the current state of a panel
	@param inPanel			The panel object.
	@param outCurrentState	[out] A buffer in which to return the state value.
	 **/
	AIAPI AIErr	(*GetCurrentState)(AIPanelRef inPanel, ai::int16& outCurrentState);


	/** Modifies the state count of a panel.
	@param inPanel			The panel object.
	@param inStateCount		The new state count; must be at least 1
	**/
	AIAPI AIErr	(*SetStateCount)(AIPanelRef inPanel, ai::int16 inStateCount);


	/** Retrieves the state count of a panel
	@param inPanel			The panel object.
	@param outStateCount	[out] A buffer in which to return the state-count value.
	 **/
	AIAPI AIErr	(*GetStateCount)(AIPanelRef inPanel, ai::int16& outStateCount);


	/** Sets the vertical step size to use when a resizable panel is resized.
	The panel height is constrained to be its minimum height plus a multiple
	of the vertical step size. By default, this is 1, making the panel sizable to any height.

	@param inPanel			The panel object.
	@param inStepSize		The new step size.
	  **/
	AIAPI AIErr	(*SetVerticalStepSize)(AIPanelRef inPanel, AIReal inStepSize);


	/** Retrieves the vertical step size for a panel
	@param inPanel			The panel object.
	@param outStepSize		[out] A buffer in which to return the size value.
	  **/
	AIAPI AIErr	(*GetVerticalStepSize)(AIPanelRef inPanel, AIReal& outStepSize);


	/** Sets the flyout menu for a panel.
		@param inPanel			The panel object.
		@param inFlyoutMenu		The new menu, or NULL to hide the menu icon.
		@see \c #AIPanelFlyoutMenuSuite.
	  **/
	AIAPI AIErr	(*SetFlyoutMenu)(AIPanelRef inPanel, AIPanelFlyoutMenuRef inFlyoutMenu);


	/** Retrieves the flyout menu for a panel.
		@param inPanel			The panel object.
		@param outFlyoutMenu	[out] A buffer in which to return the flyout menu object.
		@see \c #AIPanelFlyoutMenuSuite.
	 **/
	AIAPI AIErr	(*GetFlyoutMenu)(AIPanelRef inPanel, AIPanelFlyoutMenuRef& outFlyoutMenu);


	/** Reports the minimized state of a panel.
	When a panel is minimized its content area is  not visible, and the panel
	view has a visible height of 0.
	@param inPanel			The panel object.
	@param outIsMinimized	[out] A buffer in which to return true if the panel is minimized,
						false otherwise.
	 **/
	AIAPI AIErr (*IsMinimized)(AIPanelRef inPanel, AIBoolean& outIsMinimized);


	/** Modifies the minimized state of the panel.
	@param inPanel			The panel object.
	@param inIsMinimized	True to minimize the panel, false to return it to the
							unminimized state.
	 **/
	AIAPI AIErr (*ChangeIsMinimized)(AIPanelRef inPanel, AIBoolean inIsMinimized);


	/** Moves a panel to a specific screen location.
	Has no effect if the panel is docked. If the panel is part of a tab group,
	 the whole tab group is moved to the new location.
	@param inPanel			The panel object.
	@param inPoint			The new position in global screen coordinates.
	  **/
	AIAPI AIErr	(*Move)(AIPanelRef inPanel, AIPoint inPoint);


	/** Sets a callback procedure to be called before the flyout menu for a panel is shown.
	@param inPanel						The panel object.
	@param inFlyoutMenuPreVisProc		The new callback procedure.
	 **/
	AIAPI AIErr (*SetFlyoutMenuPreVisibilityProc)(AIPanelRef inPanel, AIPanelFlyoutMenuPreVisibilityProc inFlyoutMenuPreVisProc);


	/** Sets a callback procedure to be called after the flyout menu for a panel has been shown.
	@param inPanel						The panel object.
	@param	inFlyoutMenuPostVisProc		The new callback procedure.
	**/
	AIAPI AIErr (*SetFlyoutMenuProc)(AIPanelRef inPanel, AIPanelFlyoutMenuProc inFlyoutMenuProc);


	/** Sets a callback procedure to be called when the visibility of a panel is changed.
	@param inPanel							The panel object.
	@param inVisibilityChangedNotifyProc	The new callback procedure.
	 **/
	AIAPI AIErr (*SetVisibilityChangedNotifyProc)(AIPanelRef inPanel, AIPanelVisibilityChangedNotifyProc inVisibilityChangedNotifyProc);


	/** Sets a callback procedure to be called when the size of a panel is changed.
	@param inPanel						The panel object.
	@param inSizeChangedNotifyProc		The new callback procedure.
	 **/
	AIAPI AIErr (*SetSizeChangedNotifyProc)(AIPanelRef inPanel, AIPanelSizeChangedNotifyProc inSizeChangedNotifyProc);


	/** Sets a callback procedure to be called when the state of a panel is changed.
	@param inPanel						The panel object.
	@param inStateChangedNotifyProc		The new callback procedure.
	**/
	AIAPI AIErr (*SetStateChangedNotifyProc)(AIPanelRef inPanel, AIPanelStateChangedNotifyProc inStateChangedNotifyProc);


	/** Set a callback procedure to be called when a panel is closed by clicking the close button.
	@param inPanel						The panel object.
	@param inPanelClosedNotifyProc		The new callback procedure.
	 **/
	AIAPI AIErr (*SetClosedNotifyProc)(AIPanelRef inPanel, AIPanelClosedNotifyProc inPanelClosedNotifyProc);

	/** Get Panel Global Rect.
	@param inPanel                      The panel object.
	@param outRect                      OutRect.
	**/
	AIAPI AIErr(*GetPosition)(AIPanelRef inPanelRef, AIRealRect &outRect);
};




/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
Provides functions for creating and managing panel flyout menus.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIPanelFlyoutMenuSuite	and \c #kAIPanelFlyoutMenuSuiteVersion.
*/

struct AIPanelFlyoutMenuSuite{

	/** Creates a new panel flyout menu or submenu.
	@param outFlyOutMenu		[out] A buffer in which to return the new panel flyout menu object.

	*/
	AIAPI AIErr	(*Create)(AIPanelFlyoutMenuRef& outFlyOutMenu);


	/**  Deletes a panel flyout menu object.
	This must be called when the plug-in receives \c #kAIApplicationShutdownNotifier.
	@param inFlyOutMenu			The panel flyout menu object.
	*/
	AIAPI AIErr	(*Destroy)(AIPanelFlyoutMenuRef inFlyOutMenu);


	/** Retrieves the number of items in a flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param outSize				[out] A buffer in which to return the number of items.
	*/
	AIAPI AIErr	(*Size)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32& outSize);


	/** Inserts a new item at the end of a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inNewItemID			The unique non-zero identifier for the new item.
	@param inItemText			The display text for the new item.
	*/
	AIAPI AIErr	(*AppendItem)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inNewItemID, const ai::UnicodeString& inItemText);


	/** Inserts a separator in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inNewItemID			The unique non-zero identifier for the new separator.
	*/
	AIAPI AIErr	(*AppendSeparator)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inNewItemID);


	/** Inserts a new item at a specific relative position in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inBeforeItemID		The ID of an existing item before which to insert the new item.
	@param inNewItemID			The unique non-zero identifier for the new item.
	@param inItemText			TThe display text for the new item.
	*/
	AIAPI AIErr	(*InsertItem)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inBeforeItemID, ai::uint32 inNewItemID, const ai::UnicodeString& inItemText);


	/** Inserts a separator at a specific relative position in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inAfterID			The ID of an exsiting item after which to insert the separator,
								or -1 to append the separator to the end of the menu.
	@param inNewItemID			The unique non-zero identifier for the new separator.
	*/
	AIAPI AIErr	(*InsertSeparator)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inBeforeItemID, ai::uint32 inNewItemID);


	/** Removes an item or separator from a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item or separator.
	*/
	AIAPI AIErr	(*RemoveItem)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID);


	/** Enables or disables an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param inEnabled			True to enable or false to disable the item.
	*/
	AIAPI AIErr	(*SetItemEnabled)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, AIBoolean inEnabled);


	/** Retrieves the enabled status of an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param outEnabled			[out] A buffer in which to return true if the item is enabled, false otherwise.
	*/
	AIAPI AIErr	(*GetItemEnabled)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, AIBoolean& outEnabled);


	/** Sets a mark on an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param inItemMark			The mark type constant. Can be check, bullet, dash, or none.
	*/
	AIAPI AIErr	(*SetItemMark)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, AIPanelFlyoutMenuItemMark inItemMark);


	/** Retrieves the type of mark on an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param outItemMark			[out] A buffer in which to return the type constant (check, bullet, dash, or none).
	*/
	AIAPI AIErr	(*GetItemMark)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, AIPanelFlyoutMenuItemMark& outItemMark);


	/** Sets the display text for an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param inItemText			The new text string.
	*/
	AIAPI AIErr	(*SetItemText)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, const ai::UnicodeString& inItemText);


	/** Retrieves the display text for an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param outItemText			[out] A buffer in which to return the text string.
	*/
	AIAPI AIErr	(*GetItemText)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, ai::UnicodeString& outItemText);


	/** Reports whether an item in a panel flyout menu is a separator.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemIndex			The 0-based index of the item.
	@param outIsItemSeparator	[out] A buffer in which to return true if the item is a separator, false otherwise.
	@return	error
	*/
	AIAPI AIErr	(*IsItemSeparator)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemIndex, AIBoolean& outIsItemSeparator);


	/** Associates a submenu with an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param inSubMenu			A panel flyout menu object.
	*/
	AIAPI AIErr	(*SetItemSubMenu)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, AIPanelFlyoutMenuRef inSubMenu);


	/** Retrieves the submenu associated with an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	@param outSubMenu			[out] A buffer in which to return the submenu object.
	*/
	AIAPI AIErr	(*GetItemSubMenu)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID, AIPanelFlyoutMenuRef& outSubMenu);


	/** Removes any submenu associated with an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemID				The unique identifier of the item.
	*/
	AIAPI AIErr	(*DetachItemSubMenu)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemID);

	/** Sets the unique identifier of an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemIndex			The 0-based index of the item.
	@param inNewItemID			The new unique non-zero item ID.
	*/
	AIAPI AIErr	(*SetItemID)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemIndex, ai::uint32 inNewItemID);

	/** Retrieves the unique identifier of an item in a panel flyout menu.
	@param inFlyOutMenu			The panel flyout menu object.
	@param inItemIndex			The 0-based index of the item.
	@param outItemID			[out] A buffer in which to return the ID
	*/
	AIAPI AIErr	(*GetItemID)(AIPanelFlyoutMenuRef inFlyOutMenu, ai::uint32 inItemIndex, ai::uint32& outItemID);
};


#endif
