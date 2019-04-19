#ifndef __AIForeignObject__
#define __AIForeignObject__

/*
 *        Name:	AIForeignObject.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2002-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/*******************************************************************************/
// Imports

#ifndef __AITypes__
#include "AITypes.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIForeignObject.h */

/*******************************************************************************/
//	Constants
/** Foreign Object Suite name */
#define kAIForeignObjectSuite			"AI Foreign Object Suite"
/** Foreign Object Suite version */
#define kAIForeignObjectSuiteVersion4	AIAPI_VERSION(4)
/** Foreign Object Suite version */
#define kAIForeignObjectSuiteVersion	kAIForeignObjectSuiteVersion4
/** Foreign Object Suite version */
#define kAIForeignObjectVersion			kAIForeignObjectSuiteVersion



/*******************************************************************************/
//	Types

/** Wrap this \c AGMDisplayListPort*  as a \c CAGMDisplayListPort
	or some baseclass in order to use it. */
typedef struct _AIDisplayPort *AIDisplayPortHandle;


/*******************************************************************************/
// Suite


/** @ingroup Suites
	This suite allows you to work with \e foreign \e objects, that is,
	art objects that encapsulate imaging constructs which are supported by PDF and the
	Adobe Imaging Model, but are not native to Illustrator.

	Foreign objects behave like placed objects in that they can be positioned on
	the page, saved, displayed on the screen, and printed. They do not,  however, respond
	to other Illustrator editing commands. A foreign object can use global resources
	that are used by other artwork elements, such as fonts or spot colors.

	Illustrator requires that all spot colors used in a document be installed into
	the swatch list. Each spot color must have a unique definition and spot colors
	used by foreign objects are locked against having their definition edited. The
	installation and locking of spot colors needs to be done once the foreign
	object has been created and is known to be a permanent result of an operation
	on the document, as opposed to a temporary object created during an operation.
	For this reason installation of spot colors is done when an editing operation
	is committed. When spot colors are installed, their definitions can conflict
	with existing spot colors. in which case the user is prompted to resolve
	the conflict.

	@see \c #AIFOConversionSuite for functions that expand foreign objects
	to native Illustrator artwork.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIForeignObjectSuite and \c #kAIForeignObjectVersion.
*/
typedef struct AIForeignObjectSuite {

	/** Creates a new, empty foreign object. Pass this object to \c #GetDisplayPort(),
		and draw into that port to fill the object.
			@param paintOrder The paint order position of the new art, relative to the
				\c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object.See \c #AIArtSuite::NewArt().
			@param copyObjects When true, all objects drawn into the display list are deep copied.
				Set to false for maximum efficiency, but must be true if the objects
				depend on resources that will go away after the display list has been
				created.
			@param newArt [out] A buffer in which to return the new artwork.
		*/
	AIAPI AIErr (*New) (ai::int16 paintOrder, AIArtHandle prep, AIBoolean copyObjects, AIArtHandle *newArt);

	/** Reports whether an art object is a foreign object.
		(Note that this function returns a boolean value, not an error code.)
			@param art The art object.
			@return True if the art is a foreign object.
		*/
	AIAPI AIBoolean (*Is) (AIArtHandle art);

	/** Retrieves the bounds of a foreign object (that is, the bounds of the
		display list contents before application of a transformation matrix,
			@param art The foreign object
			@param bounds [out] A buffer in which to return the bounding box.
		*/
	AIAPI AIErr (*GetBounds) ( AIArtHandle art, AIRealRect *bounds );

	/** Sets the bounds of the foreign object (that is, the bounds of the
		display list contents before application of a transformation matrix,
			@param art The foreign object
			@param bounds The bounding box.
		*/
	AIAPI AIErr (*SetBounds) ( AIArtHandle art, AIRealRect *bounds );

	/** Retrieves the transformation matrix of a foreign object, which
		transforms display list coordinates to artboard coordinates.
			@param art The foreign object
			@param matrix [out] A buffer in which to return the transformation matrix.
		*/
	AIAPI AIErr (*GetMatrix) (AIArtHandle art, AIRealMatrix *matrix);

	/** Sets the transformation matrix of a foreign object, which
		transforms display list coordinates to artboard coordinates.
			@param art The foreign object
			@param matrix The transformation matrix.
		*/
	AIAPI AIErr (*SetMatrix) (AIArtHandle art, AIRealMatrix *matrix);

	/** Retrieves the AGM display port of a foreign object,
		Pass a new, empty foreign object, and draw into the port.
		The drawing commands are recorded by  the display port and
		are played back whenever the foreign object is rendered.

		One way to draw into the display port is to set it as the
		\c portV6 member of the \c #AIDrawArtData structure and use
		\c #AIDrawArtSuite::DrawArt(). If you have access to the AGM
		interface, you can draw directly into the display list or play its
		contents to another AGM port.
			@param art The foreign object, as returned by \c #New().
			@param port [out] A buffer in which to return the display port.
		*/
	AIAPI AIErr (*GetDisplayPort)(AIArtHandle art, AIDisplayPortHandle *port);

	/** Not implemented. a no-op. */
	AIAPI AIErr (*InstallResources)(AIArtHandle art);

	/** Duplicates a foreign object, stripping off any attributes
		that affect the rendering of the contents of the object,
		other than the transformation matrix.
		Used with the \c #kAIFOConversionSuppressAttributes flag in
		the \c #AIFOConversionSuite.
			@param art The foreign object.
			@param paintOrder The paint order position of the new art, relative to the
				\c prep object. See \c AITypes::AIPaintOrder.
			@param prep The prepositional art object.See \c #AIArtSuite::NewArt().
			@param newArt [out] A buffer in which to return the new artwork.
		*/
	AIAPI AIErr (*DuplicateForConversion)(AIArtHandle art, ai::int16 paintOrder, AIArtHandle prep, AIArtHandle* newArt);

} AIForeignObjectSuite;


#include "AIHeaderEnd.h"


#endif
