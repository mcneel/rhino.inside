#ifndef __AIAnnotator__
#define __AIAnnotator__

/*
 *        Name:	AIAnnotator.h
 *   $Revision: 8 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Annotator Suite.
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

#ifndef __AIDocumentView__
#include "AIDocumentView.h"
#endif

#ifndef __AIFixedMath__
#include "AIFixedMath.h"
#endif

#ifndef __AIRealMath__
#include "AIRealMath.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIAnnotator.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIAnnotatorSuite			"AI Annotator Suite"
#define kAIAnnotatorSuiteVersion6	AIAPI_VERSION(6)
#define kAIAnnotatorSuiteVersion	kAIAnnotatorSuiteVersion6
#define kAIAnnotatorVersion			kAIAnnotatorSuiteVersion

/**	@ingroup Callers
	The annotation caller.  See \c #AIAnnotatorSuite */
#define kCallerAIAnnotation "AI Annotation"

/** @ingroup Selectors
	Sent when the plug-in implementing a plug-in annotator should draw its annotations. */
#define kSelectorAIDrawAnnotation		"AI Draw"
/** @ingroup Selectors
	Sent when the plug-in implementing a plug-in annotator should invalidate the regions
	occupied by its annotations.
 */
#define kSelectorAIInvalAnnotation		"AI Invalidate"

/**  Update type for the \c #kSelectorAIInvalAnnotation message. */
#define kAnnotateNothing			0
/**  Not used */
#define kAnnotateBetaObject			1
/**  Not used */
#define kAnnotateBetaObjects		2
/**  Not used */
#define kAnnotateBeziers			3
/**  Not used */
#define kAnnotateText				4
/**  Update type for the \c #kSelectorAIDrawAnnotation message. */
#define kAnnotateArtObject			5


#if defined(MAC_ENV) || defined(WIN_ENV)
/**  Port type for the \c #kSelectorAIInvalAnnotation message. */
#define kAnnotateNoPortType			0
/**  Port type for the \c #kSelectorAIDrawAnnotation message. */
#define kAnnotateWindowPortType		1
/**  Not used */
#define kAnnotateGWorldPortType		2
#endif


/*******************************************************************************
 **
 ** Types
 **
 **/

/** This is a reference to an annotator. It is never dereferenced. */
typedef struct _t_AIAnnotatorOpaque *AIAnnotatorHandle;

/** Not used */
struct AIUpdateBezier
{
	/** Initial knot point */
	AIRealPoint p0;
	/** First control point */
	AIRealPoint p1;
	/** Second control point */
	AIRealPoint p2;
	/** Final knot point */
	AIRealPoint p3;
	/** When true, update an existing annotation.  */
	AIBoolean updateIt;
	/** When true, draw a new annotation.  */
	AIBoolean drawIt;
};

/** A plug-in that has registered an annotator receives this message
	with \c #kSelectorAIInvalAnnotation and  \c #kSelectorAIDrawAnnotation.
	*/
struct AIAnnotatorMessage
{
	/** The message data */
	SPMessageData d;
	/** The annotator reference for the handler that is requested
		to invalidate or draw the annotation. */
	AIAnnotatorHandle annotator;
	/** The document view; see \c apiAIDocumentView.h */
	AIDocumentViewHandle view;
	/** The type of update being requested.
		\li \c kAnnotateNothing: Request is for invalidation (\c #kSelectorAIInvalAnnotation)
		\li \c kAnnotateArtObject: Request is for drawing (\c #kSelectorAIDrawAnnotation)
	*/
	ai::int32 updateType;
	/** Not meaningful for invalidation.
		For a drawing update, a value of 1 indicates that
		the update was triggered by auto-scrolling the window during mouse drag.
		Otherwise 0. */
	void *updateData;
	/** The port type.
		\li \c kAnnotateNoPortType for \c #kSelectorAIInvalAnnotation
		\li \c kAnnotateWindowPortType for \c #kSelectorAIDrawAnnotation
		\li \c NULL for invalidation
	 */
	ai::int32 portType;
	/** @deprecated For drawing, the port to which to draw the annotation.
		The \c #AIPortRef is the same as an \c #ADMPortRef, and can
		be used directly to create an ADM drawer for platform-independent drawing.
		<br> \c NULL for an invalidation request.
		Deprecated in AI 15.0. Use \c #AIAnnotatorDrawerSuite for platform-independent
		drawing instead.
	*/
	AIPortRef port;
	/** When true, draw an outline around the annotation area. This is controlled
		by the View > Show Edges value. */
	AIBoolean showEdges;

	/** For drawing, the list of regions that have been invalidated by an annotator and
		need to be redrawn.	Can be \c NULL.

		The memory for invalidated regions is owned and deleted by Illustrator after a
		draw message completes. When any annotator invalidates a region all the annotators
		are asked to draw themselves regardless of whether their annotations lie within
		the invalidation rectangles. Illustrator erases annotations only from the invalidated region.
		This means that an annotator can be asked to draw itself when the area it is drawing still contains
		the drawing	that was done during the previous draw message.

		Most light-weight annotations can ignore this and just
		draw the entire annotation in response to \c #kSelectorAIDrawAnnotation.
		If there are performance issues drawing an annotator or an annotator uses
		transparency/blending modes when drawing, it can clip its drawing
		to the invalidation rectangles. This avoids the problem of transparency
		build up in areas where the previous drawing was not cleared.

		<br> \c NULL for an invalidation request.
	*/
	const AIRealRect *invalidationRects;
	/**	The number of rectangles in the \c invalidationRects list.
		<br> Always 0 for an invalidation request. */
	ai::int32 numInvalidationRects;

	/**	Pointer to annotator drawer object. Pointer guaranteed to be non-NULL for
		\c #kSelectorAIDrawAnnotation messages. See \c AIAnnotatorDrawer.h for more information.
	*/
	class AIAnnotatorDrawer *drawer;
};

/** Bit flag values for annotators, which determine how an annotation is drawn.
	@see \c #AIAnnotatorSuite::SetAnnotatorOptions() */
enum AIAnnotatorOptionsFlagValues
{
	/** Send notification to this annotator before other annotators, but after selection. */
	kDrawBeforeAllOthers		= 1,

	/** Send notification for inactive documents. By default notification is sent
		only to the active document. */
	kDrawOnInactiveDocuments	= 1<<1,

	/** Do not send notification for inactive views. By default notification is sent
		to all views. */
	kDontDrawOnInactiveView			= 1<<2,

	/** Dummy value to ensure 32 bit enums */
	AIAnnotatorOptionsFlagValuesDummy	= 0xFFFFFFFF
};

typedef ai::int32 AIAnnotatorOptionsFlags;

/*******************************************************************************
 **
 **	Suite Record
 **
 **/


/**	@ingroup Suites
	The annotator suite allows plug-ins to draw annotations into the document window
	that are not a part of the artwork. These annotations are drawn on top after all
	artwork has been drawn. For example, selection handles are annotations.

	In order to be given an opportunity to draw annotations a plug-in must first call
	\c #AddAnnotator() to register itself as an annotator. Typically this is done at
	plug-in startup but it may be done at any time. An annotator may be active or
	inactive. Only active annotators receive requests to draw.

	A plug-in annotator can receive two messages via its main entry point. These
	messages have caller \c #kCallerAIAnnotation. The messages are:
	\li \c kSelectorAIDrawAnnotation  A request for the annotator to draw its
		annotations. In this case the message structure is an \c ::AIAnnotatorMessage
		that supplies information about the document view to be drawn.
	\li \c kSelectorAIInvalAnnotation A request to invalidate the bounds of any
		annotations in the current document view. In response the plug-in should
		call \c #InvalAnnotationRect() for each annotation.

	In addition to responding to the previous two messages a plug-in annotator
	typically calls \c #InvalAnnotationRect() whenever its set of annotations
	changes. This indicates the parts of the document view that need to be
	redrawn as a consequence of the changes.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIAnnotatorSuite and \c #kAIAnnotatorVersion.
 */

struct AIAnnotatorSuite
{
	/** Adds a new annotator to your plug-in. Typically called during startup.

		@param self The startup plug-in.
		@param name The annotator’s display name.
		@param notifier [out] A buffer in which to return a unique identifier for the new annotator.
		*/

	AIAPI AIErr (*AddAnnotator) ( SPPluginRef self, const char *name, AIAnnotatorHandle *notifier );

	/** Retrieves the display name of this annotator.

			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param name [out] A pointer to point to the display name.
		*/
	AIAPI AIErr (*GetAnnotatorName) ( AIAnnotatorHandle notifier, const char **name );

	/** Reports whether an annotator is currently active.

			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param active [out] A buffer in which to return the result, true if the annotator is active.
		*/
	AIAPI AIErr (*GetAnnotatorActive) ( AIAnnotatorHandle notifier, AIBoolean *active );

	/**  Activates or deactivates an annotator.

		@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
		@param active  True to activate the annotator, false to deactivate it.
		*/
	AIAPI AIErr (*SetAnnotatorActive) ( AIAnnotatorHandle notifier, AIBoolean active );

	/** Retrieves the plug-in that defines this annotator.

		@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
		@param plugin [out] A buffer in which to return the plug-in reference.
		*/
	AIAPI AIErr (*GetAnnotatorPlugin) ( AIAnnotatorHandle notifier, SPPluginRef *plugin );

	/** Gets the number of currently registered annotators.
	Use with \c #GetNthAnnotator() to iterate through all annotators.

		@param [out] A buffer in which to return the number of annotators.
		*/
	AIAPI AIErr (*CountAnnotators) ( ai::int32 *count );
	/** Retrieves a registered annotator by position index.
	 Use with \c #CountAnnotators() to iterate through all registered annotators.

		@param n The index, in the range \c [1..numAnnotators].
		@param notifier [out] A buffer in which to return the annotator reference.
		*/
	AIAPI AIErr (*GetNthAnnotator) ( ai::int32 n, AIAnnotatorHandle *notifier );

	/** Invalidates a rectangular area of the document so that drawing can be performed.
		After using this function to determine the area in which to draw,
		you can call \c ADMDrawer to perform platform-independent drawing.
		For example:
	@code
	portBounds.left = _AIRealRoundToShort(updateRect.left) - 1;
	portBounds.top = _AIRealRoundToShort(updateRect.top) + 1;
	portBounds.right = _AIRealRoundToShort(updateRect.right) + 1;
	portBounds.bottom = _AIRealRoundToShort(updateRect.bottom) - 1;

	sAIAnnotator->InvalAnnotationRect(fDocumentView, &portBounds);
	@endcode

			@param view The document view. See \c apiAIDocumentView.h
			@param annotationBounds A pointer to rectangle structure that specifies the area boundaries.
		*/
	AIAPI AIErr (*InvalAnnotationRect)( AIDocumentViewHandle view, const AIRect *annotationBounds );

	/** Adds an annotator to a different plug-in (for instance, one that does on-screen drawing).
		This is the alternate plug-in; you can retrieve the handle to it using \c #GetAnnotatorAlternatePlugin().
			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param plugin The handle for the alternate plug-in.
		*/
	AIAPI AIErr (*SetAnnotatorAlternatePlugin) ( AIAnnotatorHandle notifier, SPPluginRef plugin );

	/** Retrieves the alternate plug-in for the annotator, to which it was added with \c #SetAnnotatorAlternatePlugin().
			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param plugin [out] A buffer in which to return the alternate plug-in reference.
		*/
	AIAPI AIErr (*GetAnnotatorAlternatePlugin) ( AIAnnotatorHandle notifier, SPPluginRef *plugin );

  	/** Retrieves annotator options, which determine how the annotation is drawn.
			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param flags [out] A buffer in which to return the options, a logical OR of
				\c #AIAnnotatorOptionsFlagValues.
  		*/
  	AIAPI AIErr (*GetAnnotatorOptions) ( AIAnnotatorHandle notifier, AIAnnotatorOptionsFlags *flags );
  	/** Sets annotator options, which determine how the annotation is drawn.
			@param notifier The notifier for the annotator, as returned by \c #AddAnnotator() or \c #GetNthAnnotator().
			@param flags The new options value, a logical OR of	\c #AIAnnotatorOptionsFlagValues.
  		*/
  	AIAPI AIErr (*SetAnnotatorOptions) ( AIAnnotatorHandle notifier, const AIAnnotatorOptionsFlags flags );
};


#include "AIHeaderEnd.h"


#endif
