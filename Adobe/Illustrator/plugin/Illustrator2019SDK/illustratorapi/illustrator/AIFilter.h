#ifndef __AIFilter__
#define __AIFilter__

/*
 *        Name:	AIFilter.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Filter Suite.
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

#ifndef __AIMenu__
#include "AIMenu.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIFilter.h */

/** @deprecated 
	This suite is deprecated as of AI 14 (CS4), in favor of AILiveEffectSuite.
	See \c #AILiveEffectSuite.
*/

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIFilterSuite		"AI Filter Suite"
#define kAIFilterSuiteVersion	AIAPI_VERSION(4)
#define kAIFilterVersion	kAIFilterSuiteVersion

/** @ingroup Callers
	The filter caller. See \c #AIFilterSuite.
	 */
#define kCallerAIFilter					"AI Filter"

/** @ingroup Selectors
	Sent when the user chooses a filter from the Filter menu.
	The filter should get any user parameters, which are returned to
	Illustrator in the \c #AIFilterMessage structure. You can ignore this selector
	if the filter does not require user input.
	You might want to check the artwork state to know whether
	you can proceed with the Go selector.
	 */
#define kSelectorAIGetFilterParameters	"AI Get Parameters"

/** @ingroup Selectors
	Tells your filter to execute. Do not query for parameters in the processing
	of this message; parameters are passed in the \c #AIFilterMessage structure.
		\li If the user selects the filter from the menu, the parameters are from
		the immediately preceding response to \c #kSelectorAIGetFilterParameters.
		\li If the user chooses to apply the last filter, the parameters are
		the last ones used.
	 */
#define kSelectorAIGoFilter				"AI Go"


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Opaque reference to a filter. It is never dereferenced.
	Use the functions in the \c #AIFilterSuite to access it. */
typedef struct _t_AIFilterOpaque *AIFilterHandle;


#if Macintosh || MSWindows
/** A developer-defined structure that holds parameters required
	for your filter. It is a platform handle; allocate space with
	\c #AIMdMemorySuite::MdMemoryNewHandle().*/
typedef void *PlatformFilterParameters;

/** The menu category and display name for a plug-in filter.
    Filters in the same category are added to a submenu of the Filter menu.
    	\li In Windows, either or both can have a keyboard shortcut.
    		Precede the shortcut character with an ampersand (&).
    		Take care that the shortcut key does not conflict with
    		other menu items.
*/
typedef struct {
	/** The menu category (submenu) to which the filter is added,
		a Pascal-style string. */
	unsigned char *category;
	/** The display name for the filter's menu item, a Pascal-style string.
		By convention, the name is a descriptive verb,such as "Rotate".
		If the filter requires parameters, the name should end
		with three dots.
		*/
	unsigned char *title;
} PlatformAddFilterData;
#endif

/** The message for a filter Get Parameters or Go selector. */
typedef struct {
	/** The message data. */
	SPMessageData d;
	/** The filter object. If your plug-in defines more than one filter,
		save the handles in \c globals and compare to determine which
		was activated. */
	AIFilterHandle filter;
	/** The parameter values, in a developer-defined parameter structure.
		Fill with values in response to a Get Parameters selector. */
	PlatformFilterParameters parameters;
} AIFilterMessage;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions to add and manage menu items in the Filter menu.
	Plug-in filters are added to the Filter menu in a separate section
	from native Illustrator filters and Photoshop filters supported by
	Illustrator. You can specify a \e category, or submenu, for a group of filters.

	When the user selects a filter, it typically displays an
	options dialog and then manipulates the artwork in some fashion
	according to those options.

	Filter plug-ins are similar in many ways to the more general
	menu plug-ins (see \c #AIMenuSuite). Filters differ in that:
		\li Filters are added to the Filter menu, while menu plug-ins can
			add commands to any menu.
		\li Menu plug-ins can set command keys and control their appearance.
		\li Both plug-in types receive a Go selector, but filters also receive
			\c #kSelectorAIGetFilterParameters. The user interface is typically
			a modal dialog, while a menu plug-in can interact with other
			plug-in types, or trigger other events.
		\li Filters automatically set the Repeat and Undo menus, while menu plug-ins
			must set the Undo menu item text. The filter plug-in must remove
			the Undo context if the user cancels the action. Use
			\c #AIUndoSuite::UndoChanges() to remove any changes to
			the artwork the plug-in made, and do any other necessary clean up,
			such as disposing of allocated memory.

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIFilterSuite and \c #kAIFilterVersion.
 */
typedef struct {

	/** Installs a filter plug-in. Call this during startup to place the name
		of your filter in the Filter menu.
			@param self A reference to this plug-in, which adds the filter.
			@param name	The unique name of the new filter. You can use your
				company name with a descriptor to make it unique. Not displayed or localized.
			@param data	The structure containing the category (submenu) and localizable
				menu-item label.
			@param options Not currently used. Pass 0.
			@param filter [out] A buffer in which to return the filter reference.
				 If you install multiple filters, store this reference in the
				 plug-in’s \c globals record, so that your plug-in can use it
				 to determine which filter command is to be processed.
	*/
	AIAPI AIErr (*AddFilter) ( SPPluginRef self, char *name,
				PlatformAddFilterData *data, ai::int32 options, AIFilterHandle *filter );

	/** Retrieves the unique name of a filter.
			@param filter The filter reference.
			@param name [out] A buffer in which to return the name string, as
				originally passed to \c #AddFilter(). Do not modify this string.
		*/
	AIAPI AIErr (*GetFilterName) ( AIFilterHandle filter, char **name );

	/** Retrieves the option flags of a filter. (The options flags are not
		currently used, and the returned value is always 0).
			@param filter The filter reference.
			@param options [out] A buffer in which to return the options value.
		*/
	AIAPI AIErr (*GetFilterOptions) ( AIFilterHandle filter, ai::int32 *options );

	/** Sets the option flags of a filter. (The options flags are not
		currently used.)
			@param filter The filter reference.
			@param options The options value.
		*/
	AIAPI AIErr (*SetFilterOptions) ( AIFilterHandle filter, ai::int32 options );

	/** Retrieves the stored reference to a parameter block for a filter.
		This block contains the parameter values that were set by the user
		in the most recent call to this filter.
			@param filter The filter reference.
			@param parameters [out] A buffer in which to return the stored parameters block.
		*/
	AIAPI AIErr (*GetFilterParameters) ( AIFilterHandle filter, PlatformFilterParameters *parameters );

	/** Sets the stored reference to a parameter block for a filter. The plug-in manager
		normally keeps this reference to the parameter values that were set by the user
		in the most recent call to a filter. You can use this function after a call to
		\c #AIPluginSuite::CallPlugin(), to store a new set of parameters.
			@param filter The filter reference.
			@param parameters The new parameters block.
			@see \c #GetFilterParameters()
		*/
	AIAPI AIErr (*SetFilterParameters) ( AIFilterHandle filter, PlatformFilterParameters parameters );

	/** Retrieves the menu-item reference for a filter. Your plug-in can then modify
		the menu item’s appearance using the \c #AIMenuSuite functions.
			@param filter The filter reference.
			@param menuItem [out] A buffer in which to return the menu item reference.
		*/
	AIAPI AIErr (*GetFilterMenuItem) ( AIFilterHandle filter, AIMenuItemHandle *menuItem );

	/** Retrieves a reference to the plug-in that installed a filter.
			@param filter The filter reference.
			@param plugin [out] A buffer in which to return the plug-in reference.
		*/
	AIAPI AIErr (*GetFilterPlugin) ( AIFilterHandle filter, SPPluginRef *plugin );

	/** Gets number of installed filters. Use this with \c #GetNthFilter()
		to iterate through installed filters.
			@param count [out] A buffer in which to return the number of filters.
		*/
	AIAPI AIErr (*CountFilters) ( ai::int32 *count );

	/** Retrieves a plug-in filter reference by position index. Use with
		\c #CountFilters() to iterate through all installed filters.
			@param n  The index, in the range <code>[1..numFilters]</code>.
			@param filter [out] A buffer in which to return the filter reference.
		*/
	AIAPI AIErr (*GetNthFilter) ( ai::int32 n, AIFilterHandle *filter );

} AIFilterSuite;


#include "AIHeaderEnd.h"

#endif
