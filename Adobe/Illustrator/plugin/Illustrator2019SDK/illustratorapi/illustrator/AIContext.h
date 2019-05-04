#ifndef __AIContext__
#define __AIContext__

/*
 *        Name:	AIContext.h
 *   $Revision: 2 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Runtime Context Environment.
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

#ifndef __AIDocument__
#include "AIDocument.h"
#endif

#ifndef __SPPlugins__
#include "SPPlugs.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIContext.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIAppContextSuite			"AI Context Suite"
#define kAIAppContextSuiteVersion	AIAPI_VERSION(9)
#define kAIAppContextVersion		kAIAppContextSuiteVersion

enum AIAppContextKind
{
	kAIAppContextStandardKind		= 0,
	kAIAppContextUndoRedoKind		= 1,
	kAIAppContextBetaUpdateKind	= 2
};

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference to the application context. It is never dereferenced. */
typedef struct _t_AIAppContextOpaque *AIAppContextHandle;

/** Opaque reference to an application context stack. It is never dereferenced. */
typedef struct _t_AISuspendedAppContextOpaque *AISuspendedAppContext;

/** Opaque reference to an application context stack. It is never dereferenced. */
typedef struct _t_AIAppMenuContextOpaque *AIAppMenuContext;

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	Use these functions to manage the application context. The application
	context does two things:

	\li It establishes the current document and view. Most SDK
	functions do not take a document or a view as a parameter, but
	use the current document or view as defined by the application context.

	\li It establishes the scope of a single undoable operation. All the
	changes that occur during a single application context are grouped
	together into a single operation, which can then be undone and redone.

	Most plug-ins don't need to use these functions, because Illustrator
	manages the context. In rare situations, however, a plug-in may need
	to make changes to the context. For example, if a plug-in is called directly
	by the operating system, Illustrator has not established the context. 
	If the plug-in wants to make SDK calls in response, it should use 
	\c #PushAppContext() and \c #PopAppContext().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIAppContextSuite and \c #kAIAppContextVersion.
	*/
typedef struct {

	/** Retrieves the parent application window in Windows.
		Does nothing in Mac OS.
			@param appWindow [out] A buffer in which to return the window reference.
		*/
	AIAPI AIErr (*GetPlatformAppWindow) ( AIWindowRef *appWindow );

	/** Stores an application context for the calling plug-in.
			@param plugin This plug-in.
			@param appContext [out] A buffer in which to return the application
				context reference. Pass this to \c #PopAppContext() upon completion
				of the context-sensitive procedure.

		*/
	AIAPI AIErr (*PushAppContext) ( SPPluginRef plugin, AIAppContextHandle *appContext );

	/** Restores the previous application context.
			@param appContext The application context reference, as returned by
				\c #PushAppContext().
		*/
	AIAPI AIErr (*PopAppContext) ( AIAppContextHandle appContext );

	/** @deprecated No longer needed. */
	AIAPI AIErr (*MacGetAppQDGlobal) ( void **appQD );

	/** Suspends the current application context stack. This is equivalent to popping
		all current open contexts,  except that they can later be restored all at once
		by \c #ResumeAppContext(). Use before an operation that may change the current document.
			@param appContext [out] A buffer in which to return the application
				context stack reference. Pass this to \c #ResumeAppContext() upon completion
				of the context-sensitive procedure.
		*/
	AIAPI AIErr (*SuspendAppContext) ( AISuspendedAppContext* appContext );

	/** Resumes the application context stack for the document of
		the frontmost window. This might be a different document from the one
		at the time the context stack was suspended.
			@param appContext The application context stack reference, as returned by
				\c #SuspendAppContext().
		*/
	AIAPI AIErr (*ResumeAppContext) ( AISuspendedAppContext appContext, AIDocumentHandle document );

	/** Allows or disallows plug-ins to operate on artwork within locked and/or hidden
	    parent contexts. The call modifies the allow-changes state of the current context. The
		state persists until you specifically reset it, or until the context is popped.
	   	This allows you to make modifications without having to save, set, and restore
		visibility and locked attributes on the whole parent chain.
			@param allowAllChanges True to allow changes, false to disallow changes.
			@param previousState [out] A buffer in which to return true if changes were previously allowed,
				false if they were not.
		*/
	AIAPI AIErr (*AllowAllChanges) ( ASBoolean allowAllChanges, ASBoolean *previousState );

	/** Allows or disallows use of the progress bar for the current context.
	@param showProgress True to show the progress bar, false to hide it.
	*/
	AIAPI AIErr (*AllowProgress)(bool showProgress);
	
	/** Retrieves the main menu application handle in Windows.
	Does nothing in Mac OS.
	@param appMenu [out] A buffer in which to return the menu reference.
	*/
	AIAPI AIErr (*GetPlatformAppMenu) ( AIAppMenuContext *appMenu );

	/** Sets the ContextKind for current context.
		@param kind The Context kind can either be <br>
				\c kAIAppContextStandardKind, \c kAIAppContextUndoRedoKind, \c kAIAppContextBetaUpdateKind 
				which are mutually exclusive. See \c enum AIAppContextKind
	*/
	AIAPI AIErr (*SetAppContextKind) (AIAppContextKind kind );


	/** Synchronize the current global context and then draws.
	*/
	AIAPI AIErr (*SyncAndDraw) ();

	/** Get Ruler width for the current document.
	**
	** Returns width of the vertical ruler and height of the horizontal ruler
	** Returns 0 if rulers are hidden
	*/
	AIAPI AIErr (*GetRulerWidthOffsetOnActiveDocument) (AIRect *horzRulerBounds, AIRect *vertRulerBounds, AIRect *cntrRulerBounds);

	/** Tells if Application context is present or not.
	**
	** @return A buffer returning whether application context is present or not.
	*/
	AIAPI AIBoolean	(*DoesAppContextExist)();

	/** Gets the current AppContextKind.
		@param kind [out] A buffer in which to return the kind
			\c kAIAppContextStandardKind, \c kAIAppContextUndoRedoKind, \c kAIAppContextBetaUpdateKind
			which are mutually exclusive. See \c enum AIAppContextKind
	*/
	AIAPI AIErr (*GetAppContextKind) (AIAppContextKind &kind);

} AIAppContextSuite;


#include "AIHeaderEnd.h"


#endif
