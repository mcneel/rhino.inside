#ifndef __AIObjectSet__
#define __AIObjectSet__

/*
 *        Name:	AIObjectSet.h
 *   $Revision: 17 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Object Set Suite.
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIArt__
#include "AIArt.h"
#endif

#include "AIUnicodeString.h"


#include "AIHeaderBegin.h"

/** @file AIObjectSet.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/
 /** Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite

	@internal
 	An object map is a set of type/offset pairs giving the location of each object handle
 	in the object definition.  It is terminated by an entry with <code>objectType = kAIObjectMapDone</code>.
 	An entry can be \c NULL for a particular instance, which indicates that although some
 	instances of the type store an object handle there, this particular one does not.
 	If the map says there is an object of a given type at a given offset, the data at
    that offset must be either a valid object handle of the appropriate type, or \c NULL.
*/
#define kAIObjectSetSuite				"AI ObjectSet Suite"
#define kAIObjectSetSuiteVersion4		AIAPI_VERSION(4)
#define kAIObjectSetSuiteVersion		kAIObjectSetSuiteVersion4
#define kAIObjectSetVersion				kAIObjectSetSuiteVersion

/** @ingroup Notifiers
	Object sets are deprecated in favor of dictionaries, see \c #AIDictionarySuite */
#define kAIObjectSetChangedNotifier		"AI Object Set Changed Notifier"
/** @ingroup Notifiers
	Object sets are deprecated in favor of dictionaries, see \c #AIDictionarySuite  */
#define kAIReplaceColorNotifier			"AI Replace Color Notifier"

/** @ingroup Errors
	Object set error. Object sets are deprecated in favor of dictionaries, see \c #AIDictionarySuite */
#define kNameClashErr			'NmCl'
/** @ingroup Errors
	Object set error. Object sets are deprecated in favor of dictionaries, see \c #AIDictionarySuite */
#define kUninitializedDataErr	'init'
/** @ingroup Errors
	Object set error. Object sets are deprecated in favor of dictionaries, see \c #AIDictionarySuite */
#define kCantDoThatNowErr		'!now'

/** @ingroup Callers
	Object set caller. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite */
#define kCallerAIObjectSet					"AI Object Set"

/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
	 @internal
	 	The object in the message is about to be permanently disposed.
	 	Do not free the internal or external memory (the suite will do this) but dispose
	 	of any referred-to memory.  Subobject and change fields are unused.
*/
#define kSelectorObjectSetDisposeContents "AI Object Set Dispose Contents"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
	 		Mark all objects managed by this plug-in that are used in the
	 		current document by calling AIObjectSetSuite::MarkObjectInUse().  If markArt is not nullptr, just
	 		mark all objects within that sub-tree.  Set, object, subobject, and change fields are unused.
*/
#define kSelectorObjectSetMarkUsage "AI Object Set Mark Usage"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
	 	-	Fetch the external representation for this object and update
	 		the internal. Also serves to notify of a new object; this will be the first selector received
	 		for a new one.  Subobject and change fields are unused.
*/
#define kSelectorObjectSetUpdateInternal "AI Object Set Update Internal"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
			Fetch the internal representation for this object and update
	 		the external. Subobject and change fields are unused.
*/
#define kSelectorObjectSetUpdateExternal "AI Object Set Update External"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
	 		The object contains a reference to the object described in the
	 		subobject fields, and that object is going away.  Remove the reference to it and make any
	 		necessary changes to the artwork.  Change fields are unused
*/
#define kSelectorObjectSetPurge "AI Object Set Purge"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
	 		The object has been changed as a result of an undo/redo.  Subobject
	 		fields are unused.
*/
#define kSelectorObjectSetChange "AI Object Set Change"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
	 		The object contains a reference to an object that has changed.
	 		Make any necessary changes to the artwork.  Subobject and change fields are unused.
	 		(Note, change from AI8, which set subobject).
*/
#define kSelectorObjectSetChangeIndirect "AI Object Set Change Indirect"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
			The object has been copied into the current document.
	 		Subobject and change fields are unused.
*/
#define kSelectorObjectSetCopy "AI Object Set Copy"
/** @ingroup Selectors
	Object set selector. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
		 @internal
	 		All UpdateInternal calls for objects that were in the
	 		document are over with.  Called once per plug-in, not per object set.  All fields are unused.
*/
#define kSelectorObjectSetInitializationDone "AI Object Set Initialization Done"


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference to an object set.
	Object sets are deprecated in favor of dictionaries, see \c #AIDictionarySuite */
typedef struct _t_AIObjectSetOpaque *AIObjectSetHandle;
/** Opaque reference to an object in an object set.
	Object sets are deprecated in favor of dictionaries, see \c #AIDictionarySuite */
typedef struct _t_AIObjectOpaque *AIObjectHandle;

/** Types of changes that can be made to object sets.
	Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite */
enum AIObjectSetChangeType {
	kAIObjectSetChangeDelete,
	kAIObjectSetChangeNew,
	kAIObjectSetChangeChange,
	kAIObjectSetChangeRename
};

/** Types of objects that can be stored in an object set.
	Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite */
enum AIObjectMapType {
	kAIObjectMapCustomColor,
	kAIObjectMapPattern,
	kAIObjectMapBrushPattern,
	kAIObjectMapGradient,
	kAIObjectMapPluginObject,
	kAIObjectMapDone = -1
};

/** Object map for object set. Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite  */
struct AIObjectMap {
	/** A value from #AIObjectMapType */
	ai::int16 objectType;
	ai::int16 offset;
};

/** Color replacement types in object sets.
	Object sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite  */
enum AIReplaceColorTag {
	kRepGrayColor = kGrayColor,
	kRepFourColor = kFourColor,
	kRepPattern = kPattern,
	kRepCustomColor = kCustomColor,
	kRepGradient = kGradient,
	kRepThreeColor = kThreeColor,
	kRepNoneColor = kNoneColor,
	kRepBrushPattern = kNoneColor + 5,

	kRepColorDone = -1,
	kRepColorSameTagAsInAIColor = -2

};

/** For object sets, which are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite  */
struct AIReplaceColor {
	AIReplaceColorTag kind;			/* Used to determine the color variant */
	AIColorUnion c;
};

/** For object sets, which are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite */
struct AIReplaceColorNotifierData {
	ASInt32			pairs;
	AIReplaceColor *colorPtr;
};

/** The contents of an object-set message.
	Object Sets are deprecated in favor of dictionaries,
	see \c #AIDictionarySuite
	@internal
		Fields are used for the different selectors as indicated:
 	<br>\c #kSelectorObjectSetDisposeContents. The object in the message is about to be permanently disposed.
 		Do not free the internal or external memory (the suite will do this) but dispose
 		of any referred-to memory.  Subobject and change fields are unused.
 	<br>\c #kSelectorObjectSetMarkUsage. Mark all objects managed by this plug-in that are used in the
 		current document by calling AIObjectSetSuite::MarkObjectInUse().  If markArt is not nullptr, just
 		mark all objects within that sub-tree.  Set, object, subobject, and change fields are unused.
 	<br>\c #kSelectorObjectSetUpdateInternal. Fetch the external representation for this object and update
 		the internal. Also serves to notify of a new object; this will be the first selector received
 		for a new one.  Subobject and change fields are unused.
 	<br>\c #kSelectorObjectSetUpdateExternal. Fetch the internal representation for this object and update
 		the external. Subobject and change fields are unused.
 	<br>\c #kSelectorObjectSetPurge. The object contains a reference to the object described in the
 		subobject fields, and that object is going away.  Remove the reference to it and make any
 		necessary changes to the artwork.  Change fields are unused
 	<br>\c #kSelectorObjectSetChange. The object has been changed as a result of an undo/redo.  Subobject
 		fields are unused.
 	<br>\c #kSelectorObjectSetChangeIndirect. The object contains a reference to an object that has changed.
 		Make any necessary changes to the artwork.  Subobject and change fields are unused.
 		(Note, change from AI8, which set subobject).
 	<br>\c #kSelectorObjectSetCopy. The object has been copied into the current document.
 		Subobject and change fields are unused.
 	<br>\c #kSelectorObjectSetInitializationDone. All UpdateInternal calls for objects that were in the
 		document are over with.  Called once per plug-in, not per object set.  All fields are unused.
	*/
struct AIObjectSetMessage {
	SPMessageData d;
	AIObjectSetHandle set;
	AIObjectHandle object;
	ai::int16 subobjectType;
	union {
		AIPatternHandle pattern;
		AIGradientHandle gradient;
		AICustomColorHandle ccolor;
		struct {
			AIObjectSetHandle set;
			AIObjectHandle object;
		} object;
	} subobject;
	AIObjectSetChangeType changeType;
	AIArtHandle markArt;
	AIVersion aiVersion;
};


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@deprecated
	Object sets provide an obsolete mechanism for attaching global information to a document. Their use is
	deprecated in favor of dictionaries. Each document contains a dictionary where arbitrary information
	can be stored. See \c #AIDocumentSuite::GetDictionary() and \c #AIDocumentSuite::GetNonRecordedDictionary().
 */
struct AIObjectSetSuite {

	AIAPI AIErr (*NewObjectSet) ( SPPluginRef self, const unsigned char *name, const AIObjectMap *map, AIObjectSetHandle *set );
	AIAPI AIErr (*CountObjectSets) ( ai::int32 *count );
	AIAPI AIErr (*GetNthObjectSet) ( ai::int32 n, AIObjectSetHandle *set );
	AIAPI AIErr (*GetObjectSetName) ( AIObjectSetHandle set, unsigned char *name );
	AIAPI AIErr (*GetObjectSetByName) ( const unsigned char *name, AIObjectSetHandle *set );
	AIAPI AIErr (*GetObjectSetMap) ( AIObjectSetHandle set, const AIObjectMap **map );
	AIAPI AIErr (*NewObject) ( AIObjectSetHandle setHandle, const ai::UnicodeString& name, const void *def,
		ai::int32 defLen, AIObjectHandle *object );
	AIAPI AIErr (*DeleteObject) ( AIObjectSetHandle setHandle, AIObjectHandle object);
	AIAPI AIErr (*SetObjectInternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, const void *data, ai::int32 dataLen);
	AIAPI AIErr (*SetObjectExternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, const char *data);
	AIAPI AIErr (*GetObjectInternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, const void **data, ai::int32 *dataLen);
	AIAPI AIErr (*GetObjectExternal) ( AIObjectSetHandle setHandle, AIObjectHandle object, const char **data);
	AIAPI AIErr (*CountObjects) ( AIObjectSetHandle setHandle, ai::int32 *count);
	AIAPI AIErr (*GetNthObject) ( AIObjectSetHandle setHandle, ai::int32 n, AIObjectHandle *object);
	AIAPI AIErr (*GetObjectName) ( AIObjectSetHandle setHandle, AIObjectHandle object, ai::UnicodeString& name);
	AIAPI AIErr (*SetObjectName) ( AIObjectSetHandle setHandle, AIObjectHandle object, const ai::UnicodeString& name);
	AIAPI AIErr (*GetObjectByName) ( AIObjectSetHandle setHandle, ai::UnicodeString& name, AIObjectHandle *object);
	AIAPI AIErr (*NewObjectName) ( AIObjectSetHandle setHandle, ai::UnicodeString& name );
	AIAPI AIErr (*MarkObjectInUse) ( AIObjectSetHandle setHandle, AIObjectHandle object);
	AIAPI AIErr (*RetargetForCurrentDocument) ( AIObjectHandle object, AIObjectHandle *newObj );

	AIAPI AIErr (*GetExternalObjectName) (AIObjectSetHandle setHandle, AIObjectHandle object,
		AIVersion aiVersion, char *buf, ai::int32* bufLen );

	AIAPI AIErr (*SetObjectExternalAlternate) ( AIObjectSetHandle setHandle, AIObjectHandle object, const char *data,
		ai::uint32 majorVersion, ai::uint32 minorVersion);

};


#include "AIHeaderEnd.h"


#endif
