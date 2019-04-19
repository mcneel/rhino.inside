#ifndef __AISVGFilter__
#define __AISVGFilter__

/*
 *        Name:	AISVGFilter.h
 *   $Revision: 2 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator SVG Filter Suite.
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

#include "AIArtStyle.h"
#include "AIUID.h"
#include "AIXMLElement.h"

#include "AIHeaderBegin.h"

/** @file AISVGFilter.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAISVGFilterSuite				"AI SVG Filter Suite"
#define kAISVGFilterSuiteVersion1		AIAPI_VERSION(1)
#define kAISVGFilterSuiteVersion4		AIAPI_VERSION(4)
#define kAISVGFilterSuiteVersion		kAISVGFilterSuiteVersion4
#define kAISVGFilterVersion				kAISVGFilterSuiteVersion

/** @ingroup Notifiers
	See \c #AISVGFilterSuite */
#define kAISVGFilterChangedNotifier		"AI SVG Filter Changed Notifier"
/** @ingroup Notifiers
	See \c #AISVGFilterAddedNotifierData. */
#define kAISVGFilterAddedNotifier		"AI SVG Filter Added Notifier"

/** @ingroup Errors
	Identifier in use. See \c #AISVGFilterSuite.
 */
#define kXMLIDCollisionErr	kUIDNotUnique
/** @ingroup Errors
	Identifier changed. See \c #AISVGFilterSuite. */
#define kXMLIDChangedErr	'IDCN'
/** @ingroup Errors
	No SVG filter available. See \c #AISVGFilterSuite. */
#define kNoSVGFilterErr		'!SFE'
/** @ingroup Errors
	Attempt to redefine existing SVG filter with new XML identifier.
	See \c #AISVGFilterSuite. */
#define kSVGFilterRedefErr	'SRDE'

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Notification data for \c #kAISVGFilterAddedNotifier */
typedef struct {
	/** The document */
	AIDocumentHandle document;
	/** The SVG filter */
	AISVGFilterHandle filter;
} AISVGFilterAddedNotifierData;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites

	The SVG-filter Effect makes it possible to apply SVG filters to Illustrator artwork,
	from a global list associated with the current document.
	Filters are preserved, if possible, when the SVG file is written.

	This suite provides functions that allow you to manage the global
	list of SVG filters, attach filters to art, and manipulate art with SVG filters attached.

	Although AISVGFilterHandles are reference counted objects this suite does not
	increment the reference count before returning it to you as with other reference counted
	objects.

	These notifiers are associated with SVG filters:
	<br>\c #kAISVGFilterChangedNotifier
	<br>\c #kAISVGFilterAddedNotifier

	These error codes are associated with SVG filters:
	<br>\c #kXMLIDCollisionErr
	<br>\c #kXMLIDChangedErr
	<br>\c #kNoSVGFilterErr
	<br>\c #kSVGFilterRedefErr

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAISVGFilterSuite and \c #kAISVGFilterVersion.
 */
typedef struct {

	/** Creates a new SVG filter in the current document.
			@param newFilter [out] A buffer in which to return the new filter.
		*/
	AIAPI AIErr (*NewSVGFilter) ( AISVGFilterHandle *newFilter );

	/** Deletes an SVG filter from the current document.
			@param filter The filter.
		*/
	AIAPI AIErr (*DeleteSVGFilter) ( AISVGFilterHandle filter );

	/** Gets the number of SVG filters in the current document. Use with
		\c #GetNthSVGFilter() to iterate through filters.
			@param count [out] A buffer in which to return the count.
		*/
	AIAPI AIErr (*CountSVGFilters) ( ai::int32 *count );

	/** Retrieves an SVG filter from the filter list for the current document.
		Use with \c #CountSVGFilters() to iterate through filters.
			@param n The 0-based position index.
			@param filter [out] A buffer in which to return the filter.
		*/
	AIAPI AIErr (*GetNthSVGFilter) ( ai::int32 n, AISVGFilterHandle *filter );

	/** Sets the contents of an SVG filter.
			@param filter The SVG filter.
			@param filterContents The XML node containing the new contents.
			@param forceUniqueID True to rename the filter to have a unique identifier, if
				necessary. Retrieve the XML identifier from the filter object with \c #GetSVGFilterUIDName())
			@return \c #kXMLIDCollisionErr error if \c forceUniqueID is false, and
				if The XML identifier is already in use in the current document.
				<br> \c #kXMLIDChangedErr if \c forceUniqueID is true and the XML identifier
				was changed to make it unique.
	 	*/
	AIAPI AIErr (*SetSVGFilterContents) ( AISVGFilterHandle filter, AIXMLNodeRef filterContents,
		AIBool8 forceUniqueID );

	/** Retrieves the contents of an SVG filter.
			@param filter The SVG filter.
			@param filterContents [out] A buffer in which to return the XML node containing the contents.
		*/
	AIAPI AIErr (*GetSVGFilterContents) ( AISVGFilterHandle filter, AIXMLNodeRef *filterContents );

	/** Retrieves the filter handle associated with an identifying name string.
			@param name The name string.
			@param filter [out] A buffer in which to return the filter.
		*/
	AIAPI AIErr (*GetSVGFilter) ( const ai::UnicodeString& name, AISVGFilterHandle *filter );

	/** Retrieves the identifying name string for a filter handle,
			@param filter  The SVG filter.
			@param name [out] A buffer in which to return the name string.
		*/
	AIAPI AIErr (*GetSVGFilterUIDName) (AISVGFilterHandle filter, ai::UnicodeString& name);

	/** Retrieves a copy of art that is used for an SVG Filter Effect on the specified art object.
            @param art The input art object.
            @param svgArt [out] A buffer in which to return a copy of the SVG filter art, or null if there is no SVG Filter Effect attached to the input art object. 
		You are responsible for freeing this copy using \c #DisposeFilterArt().
		*/
	AIAPI AIErr (*GetSVGFilterArt) ( AIArtHandle art, AIArtHandle* svgArt );

	/** Disposes of the input/output art for an SVG filter, as returned
		by \c #GetSVGFilterArt().
			@param art The SVG art.
		*/
	AIAPI AIErr (*DisposeFilterArt) ( AIArtHandle art );

	/** Applies an SVG filter to artwork.
			@param art The artwork.
			@param filter The SVG filter.
		*/
	AIAPI AIErr (*AttachFilter) ( AIArtHandle art, AISVGFilterHandle filter );

	/** Generates an SVG filter to represent an art style, if possible.
			@param artStyle The art style object.
			@param filter  [out] A buffer in which to return the SVG filter.
			@return \c #kNoSVGFilterErr error if the style cannot be represented as SVG.
		*/
	AIAPI AIErr (*SVGFilterFromAIArtStyle) ( const AIArtStyleHandle artStyle, AISVGFilterHandle *filter);

} AISVGFilterSuite;


#include "AIHeaderEnd.h"


#endif
