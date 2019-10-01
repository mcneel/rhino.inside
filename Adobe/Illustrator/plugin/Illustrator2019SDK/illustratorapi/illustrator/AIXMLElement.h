#ifndef __AIXMLElement__
#define __AIXMLElement__

/*
 *        Name:	AIXMLNodeRef.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator XML node suite.
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

#ifndef __AIEntry__
#include "AIEntry.h"
#endif

#ifndef __AIDict__
#include "AIDictionary.h"
#endif

#ifndef __AIArray__
#include "AIArray.h"
#endif


#include "AIHeaderBegin.h"

/** @file AIXMLElement.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAIXMLNodeSuite						"AI XML Node Suite"
#define kAIXMLNodeSuiteVersion5				AIAPI_VERSION(5)
#define kAIXMLNodeSuiteVersion				kAIXMLNodeSuiteVersion5
#define kAIXMLNodeVersion					kAIXMLNodeSuiteVersion

#define kAIXMLDocumentSuite					"AI XML Document Suite"
#define kAIXMLDocumentSuiteVersion4			AIAPI_VERSION(4)
#define kAIXMLDocumentSuiteVersion			kAIXMLDocumentSuiteVersion4
#define kAIXMLDocumentVersion				kAIXMLDocumentSuiteVersion

#define kAIXMLElementSuite					"AI XML Element Suite"
#define kAIXMLElementSuiteVersion4			AIAPI_VERSION(4)
#define kAIXMLElementSuiteVersion			kAIXMLElementSuiteVersion4
#define kAIXMLElementVersion				kAIXMLElementSuiteVersion

#define kAIXMLNodeListSuite					"AI XML Node List Suite"
#define kAIXMLNodeListSuiteVersion3			AIAPI_VERSION(3)
#define kAIXMLNodeListSuiteVersion			kAIXMLNodeListSuiteVersion3
#define kAIXMLNodeListVersion				kAIXMLNodeListSuiteVersion

#define kAIXMLNamedNodeMapSuite				"AI XML Named Node Map Suite"
#define kAIXMLNamedNodeMapSuiteVersion4		AIAPI_VERSION(4)
#define kAIXMLNamedNodeMapSuiteVersion		kAIXMLNamedNodeMapSuiteVersion4
#define kAIXMLNamedNodeMapVersion			kAIXMLNamedNodeMapSuiteVersion

/*******************************************************************************
 **
 **	Constants
 **
 **/

/** @ingroup Errors 
	See \c #AIXMLElementSuite, \c #AIXMLNodeListSuite.*/
#define kAIXMLIndexSizeErr			'xInd'

/** @ingroup Errors 
	See \c #AIXMLElementSuite */
#define kAIXMLDOMStringSizeErr		'xDSt'

/** @ingroup Errors 
	See \c #AIXMLDocumentSuite */
#define kAIXMLHierarchyRequestErr	'xHer'

/** @ingroup Errors 
	See \c #AIXMLDocumentSuite */
#define kAIXMLWrongDocumentErr		'xDoc'

/** @ingroup Errors 
	See \c #AIXMLElementSuite, \c #AIXMLDocumentSuite */
#define kAIXMLInvalidCharacterErr	'xChr'

/** @ingroup Errors 
	See \c #AIXMLDocumentSuite */
#define kAIXMLNoDataAllowedErr		'x!dt'

/** @ingroup Errors 
	See \c #AIXMLDocumentSuite */
#define kAIXMLNoModifyAllowedErr	'x!mo'

/** @ingroup Errors 
	See \c #AIXMLDocumentSuite */
#define kAIXMLNotFoundErr			'x!fd'

/** @ingroup Errors 
	See \c #AIXMLDocumentSuite */
#define kAIXMLNotSupportedErr		'x!sp'

/** @ingroup Errors 
	See \c #AIXMLElementSuite */
#define kAIXMLInUseAttributeErr		'xInU'


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Opaque reference to an XML node list. Access with \c #AIXMLNodeListSuite */
typedef struct _AIXMLNodeList *AIXMLNodeListRef;
/** Opaque reference to an XML named node map. Access with \c #AIXMLNamedNodeMapSuite */
typedef struct _AIXMLNamedNodeMap *AIXMLNamedNodeMapRef;
/** Opaque reference to an XML name. See \c #AIXMLNodeSuite::NameFromString(),
	\c #AIXMLNodeSuite::SetNodeName(). */
typedef struct _AIXMLName *AIXMLName;
/** An abstract name that can be converted to or from a
	simple C string or Unicode string. See \c #AIXMLNodeSuite. */
typedef AIEntryRef AIXMLString; 		// entry of type string.

/** XML node type, an \c #AIXMLNodeTypeValue. See \c #AIXMLNodeSuite::GetNodeType(),
	\c #AIXMLDocumentSuite*/
typedef ai::int32  AIXMLNodeType;
/** Possible values for \c #AIXMLNodeType. */
enum AIXMLNodeTypeValue {
	kAIXMLUnknownNode,
	/** Element. See \c #AIXMLDocumentSuite::CreateElement() */
	kAIXMLElementNode,
	/** Attribute. See \c #AIXMLDocumentSuite::CreateAttribute() */
	kAIXMLAttributeNode,
	/** Text. See \c #AIXMLDocumentSuite::CreateTextNode()  */
	kAIXMLTextNode,
	/** CData section. See \c #AIXMLDocumentSuite::CreateCDATASection()  */
	kAIXMLCDATASectionNode,
	/** Comment. See \c #AIXMLDocumentSuite::CreateComment()  */
	kAIXMLCommentNode,
	/** Not supported */
	kAIXMLEntityReferenceNode,
	/** Not supported */
	kAIXMLEntityNode,
	/** Not supported */
	kAIXMLProcessingInstructionNode,
	/** Not supported */
	kAIXMLDocumentNode,
	/** Not supported */
	kAIXMLDocumentTypeNode,
	/** Not supported */
	kAIXMLDocumentFragmentNode,
	/** Not supported */
	kAIXMLNotationNode
};



/*******************************************************************************
 **
 **	Notifier
 **
 **/

/** @ingroup Notifiers
	Sent when an operation requiring update of metadata is about to occur.
	For example, sent before any file format is called or written.
	Register for this if you need to keep metadata current.
	If you add any function that assumes the metadata is current
	(for a metadata browser, for example), send this notifier.
		@see \c #AIXMLDocumentSuite
*/
#define kAIMetadataSyncNotifier			"AI Metadata Sync Notifier"


/*******************************************************************************
 **
 **	Suites
 **
 **/

//  ------ AIXMLNodeSuite -------------------------
/** @ingroup Suites
	This suite allows you to create and manipulate XML nodes.

	The XML node suite provides an approximate implementation of the
	XML Level 1 DOM interface for nodes. See
	http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#ID-1950641247

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIXMLNodeSuite and \c #kAIXMLNodeVersion.

	The values of "NodeName", "NodeValue", and "Attributes" vary according to
	the node type as follows:

	<table>
	<tr><td>				</td><td>NodeName			</td><td>NodeValue			</td><td>Attributes</td></tr>

	<tr><td>Element			</td><td>tag name			</td><td>null				</td><td>NamedNodeMap</td></tr>
	<tr><td>Attr			</td><td>attribute name		</td><td>attribute value	</td><td>null</td></tr>
	<tr><td>Text			</td><td>\#text				</td><td>text value			</td><td>null</td></tr>
	<tr><td>CDATASection	</td><td>\#cdata-section	</td><td>CDATA contents 	</td><td>null</td></tr>
	<tr><td>Comment			</td><td>\#comment			</td><td>comment string		</td><td>null</td></tr>

	<tr><td>EntityReference	</td><td>entity ref name	</td><td>null				</td><td>null</td></tr>
	<tr><td>Entity			</td><td>entity name		</td><td>null				</td><td>null</td></tr>
	<tr><td>P.Instruction	</td><td>target name		</td><td>content			</td><td>null</td></tr>
	<tr><td>Document		</td><td>\#document			</td><td>null				</td><td>null</td></tr>
	<tr><td>DocumentType	</td><td>document type name	</td><td>null				</td><td>null</td></tr>
	<tr><td>DocumentFrag	</td><td>\#document-fragment </td><td>null				</td><td>null</td></tr>
	<tr><td>Notation		</td><td>notation name		</td><td>null				</td><td>null</td></tr>
	</table>
*/
typedef struct {

	// -- nodes --

	/** Increments the reference count for an XML node.
		When you create a node, the initial count is 1.
		Use \c #Release() to decrement the count.
		(Note that this function returns a numeric value, not an error code.)
			@param node The XML node reference.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*AddRef) (AIXMLNodeRef node);

	/** Decrements the reference count for an XML node, and
		frees the memory when the reference count is 0.
		When you create a node, the initial count is 1.
		Use \c #AddRef() to increment the count.
		(Note that this function returns a numeric value, not an error code.)
			@param node The XML node reference.
			@return The current reference count.
		*/
	AIAPI ai::int32 (*Release) (AIXMLNodeRef node);

	/** Creates an exact duplicate of an XML node. performing a deep copy.
			@param src The source node.
			@param dst [out] A buffer in which to return the new node.
		*/
	AIAPI AIErr (*Clone) (AIXMLNodeRef src, AIXMLNodeRef* dst );

	/** Copies the contents of an XML node into another existing node.
	 		@param node The node whose contents are replaced.
			@param src The source node.
	 	*/
	AIAPI AIErr (*Copy) (AIXMLNodeRef node, AIXMLNodeRef src);

	/** Retrieves the type of an XML node.
			@param node The XML node reference.
			@param type [out] A buffer in which to return the type constant.
		*/
	AIAPI AIErr (*GetNodeType)(AIXMLNodeRef node, AIXMLNodeType *type);

	/** Retrieves the name of an XML node.
			@param node The XML node reference.
			@param name [out] A buffer in which to return the name.
		*/
	AIAPI AIErr (*GetNodeName)(AIXMLNodeRef node, AIXMLName *name);

	/** Sets the name of an XML node.
			@param node The XML node reference.
			@param name The new name.
		*/
	AIAPI AIErr (*SetNodeName)(AIXMLNodeRef node, AIXMLName name);

	/** Retrieves the value of an XML node.
			@param node The XML node reference.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetNodeValue)(AIXMLNodeRef node, AIXMLString *value);

	/** Sets the value of an XML node.
			@param node The XML node reference.
			@param name The new value.
		*/
	AIAPI AIErr (*SetNodeValue)(AIXMLNodeRef node, AIXMLString value);

	/** Retrieves a node list containing the child nodes of an XML node.
			@param node The XML node reference.
			@param nodes [out] A buffer in which to return the node list.
		*/
	AIAPI AIErr (*GetChildNodes)(AIXMLNodeRef node, AIXMLNodeListRef *nodes);

	/** Retrieves a named node map containing the attributes associated
		with an XML node.
			@param node The XML node reference.
			@param attributes [out] A buffer in which to return the node map.
		*/
	AIAPI AIErr (*GetAttributes)(AIXMLNodeRef node, AIXMLNamedNodeMapRef *attributes);

	/** Inserts a new child node in an XML node.
			@param node The XML node reference for the parent node.
			@param newchild The new child node.
			@param refchild An existing child node before which to insert the new child,
				or \c NULL to insert the new child at the end of the child list.
		*/
	AIAPI AIErr (*InsertBefore)(AIXMLNodeRef node, AIXMLNodeRef newchild, AIXMLNodeRef refchild);

	/** Replaces one child of an XML node with another child node.
			@param node The XML node reference for the parent node.
			@param newchild The new child node.
			@param oldchild An existing child node to replace.
		*/
	AIAPI AIErr (*ReplaceChild)(AIXMLNodeRef node, AIXMLNodeRef newchild, AIXMLNodeRef oldchild);

	/** Removes a child node from an XML node.
			@param node The XML node reference for the parent node.
			@param oldchild An existing child node to remove.
		*/
	AIAPI AIErr (*RemoveChild)(AIXMLNodeRef node, AIXMLNodeRef oldchild);

	/** Appends a new child node to the child list of an XML node.
			@param node The XML node reference for the parent node.
			@param newchild The new child node.
		*/
	AIAPI AIErr (*AppendChild)(AIXMLNodeRef node, AIXMLNodeRef newchild);

	/** Reports whether an XML node has any children.
			@param node The XML node reference.
			@param haschildren [out] A buffer in which to return true if the node has children.
		*/
	AIAPI AIErr (*HasChildNodes)(AIXMLNodeRef node, AIBoolean *haschildren);

	// -- names --

	/** Converts a C string to an XML node name.
		(Note that this function returns an XML name value, not an error code,)
			@param string The C string.
			@return The XML name.
		*/
	AIAPI AIXMLName (*NameFromString) (const char* string);

	/** Converts an XML name to a C string.
		(Note that this function returns a string value, not an error code,)
			@param name The XML name.
			@return The C string.
		*/
	AIAPI const char* (*StringFromName) (AIXMLName name);

	/** Converts a Unicode string to an XML node name.
		(Note that this function returns an XML name value, not an error code,)
			@param string The Unicode string.
			@return The XML name.
		*/
	AIAPI AIXMLName (*NameFromUnicodeString) (const ai::UnicodeString& string);

	/** Converts an XML name to a Unicode string.
			@param name The XML name.
			@param string [out] A buffer in which to return the Unicode string.
		*/
	AIAPI AIErr (*UnicodeStringFromName) (AIXMLName name, ai::UnicodeString& string);

	// -- private data --

	/** @deprecated. Obsolete, do not use. */
	AIAPI AIErr (*GetData) (AIXMLNodeRef node, AIDictKey key, AIEntryRef *value);

	/** @deprecated. Obsolete, do not use. */
	AIAPI AIErr (*SetData) (AIXMLNodeRef node, AIDictKey key, AIEntryRef value);

	/** @deprecated. Obsolete, do not use. */
	AIAPI AIErr (*RemoveData) (AIXMLNodeRef node, AIDictKey key);

	// -- utilities --

	/** Compares two XML nodes for equality. Nodes are equal if they have
		the same type, name, and value, and if they each have the same
		attributes with the same values. They are deeply
		equal if their sequences of child nodes are also equal.
		When comparing values, the function converts them to real
		numbers if possible, and otherwise compares the strings.
			@param node1 The first node.
			@param node2 The second node.
			@param deep True to perform a deep comparison.
			@param result [out] A buffer in which to return true (non-zero) if the nodes are equal.

			@note This is not a part of the XML DOM specification.
		*/
	AIAPI AIErr (*Compare) (AIXMLNodeRef node1, AIXMLNodeRef node2, AIBoolean deep, ai::int32 *result);

} AIXMLNodeSuite;




//  ------ AIXMLDocumentSuite -------------------------
/** @ingroup Suites
	An Illustrator document can store an XML document element in its dictionary.
	This suite allows you to create and access the XML document and its
	contained metadata element.

	When an Illustrator document is exported to SVG, the metadata element
	is written to the SVG file. Before writing the file, Illustrator sends
	the \c #kAIMetadataSyncNotifier to ensure that the metadata is updated.
	When Illustrator reads an SVG file, the metadata in the SVG becomes
	the document metadata element.

	This suite provides an approximate implementation of the
	XML Level 1 DOM interface for documents. See
	http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#i-Document

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIXMLDocumentSuite and \c #kAIXMLDocumentVersion.
 */
typedef struct {

	/** Retrieves the XML document for the current Illustrator document, creating
		one if none exists.
			@param element [out] A buffer in which to return the XML document element.
			@note This is not a part of the XML DOM specification.
		*/
	AIAPI AIErr (*GetDocumentElement)(AIXMLNodeRef *element);

	/** Retrieves the metadata element from the XML document for the current
		Illustrator document, creating one if none exists.
			@param element [out] A buffer in which to return the metadata element.
			@note This is not a part of the XML DOM specification.
		*/
	AIAPI AIErr (*GetDocumentMetadata)(AIXMLNodeRef *element);

	/** Creates a new metadata element.
			@param name The element name.
			@param element [out] A buffer in which to return the new element.
		*/
	AIAPI AIErr (*CreateElement)(AIXMLName name, AIXMLNodeRef *element);

	/** Creates a new metadata attribute.
			@param name The attribute name.
			@param value The attribute value.
			@param attribute [out] A buffer in which to return the new attribute.
		*/
	AIAPI AIErr (*CreateAttribute)(AIXMLName name, AIXMLString value, AIXMLNodeRef *attribute);

	/** Creates a new metadata text node.
			@param string The text string.
			@param text [out] A buffer in which to return the new text node.
		*/
	AIAPI AIErr (*CreateTextNode)(AIXMLString string, AIXMLNodeRef *text);

	/** Creates a new metadata comment node.
			@param string The comment string.
			@param comment [out] A buffer in which to return the new comment node.
		*/
	AIAPI AIErr (*CreateComment)(AIXMLString string, AIXMLNodeRef *comment);

	/** Creates a new metadata CDATA node.
			@param string The CDATA string.
			@param cdata [out] A buffer in which to return the new CDATA node.
		*/
	AIAPI AIErr (*CreateCDATASection)(AIXMLString string, AIXMLNodeRef *cdata);

	/** Retrieves XML elements at or under a node that match a name pattern.
		The matching elements are determined by a pre-order traversal.
			@param node A node at any level of the XML tree.
			@param name The name pattern to match. The special name "*" matches all elements.
			@param count [in, out] On input, the maximum number of matches to return.
				On return, the number of array elements actually filled.
			@param [in, out] An array of nodes of size \c count, in which to return matching
				nodes.
			@note This implementation differs from the XML DOM specification.
		*/
	AIAPI AIErr (*GetElementsByTagName)(AIXMLNodeRef node, AIXMLName name, ai::int32 *count, AIXMLNodeRef *match);

} AIXMLDocumentSuite;



//  ------ AIXMLElementSuite -------------------------
/** @ingroup Suites
	This suite allows you to access XML metadata attributes.

	This suite provides an approximate implementation of the
	XML Level 1	DOM interface for elements. See
	http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#ID-745549614

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIXMLElementSuite and \c #kAIXMLElementVersion.
 */
typedef struct {

	// -- attributes --

	/** Retrieves the value of an XML node's named attribute.
			@param element The node.
			@param name The attribute name.
			@param value [out] A buffer in which to return the value.
		*/
	AIAPI AIErr (*GetAttribute)(AIXMLNodeRef element, AIXMLName name, AIXMLString *value);

	/** Sets the value of an XML node's named attribute.
			@param element The node.
			@param name The attribute name.
			@param value The new value.
		*/
	AIAPI AIErr (*SetAttribute)(AIXMLNodeRef element, AIXMLName name, AIXMLString value);

	/** Removes a named attribute associated with an XML node.
			@param element The node.
			@param name The attribute name.
		*/
	AIAPI AIErr (*RemoveAttribute)(AIXMLNodeRef element, AIXMLName name);

} AIXMLElementSuite;


//  ------ AIXMLNodeListSuite -------------------------
/** @ingroup Suites
	This suite allows you to iterate through and manage lists of XML nodes.

	This suite provides an approximate implementation of the
	XML Level 1	DOM interface for node lists. See
	http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#ID-536297177

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIXMLNodeListSuite and \c #kAIXMLNodeListVersion.
 */
typedef struct {

	/** Retrieves the number of items in a node list. Use with \c #GetItem()
		to iterate through a list.
			@param nodes The XML node list.
			@param length [out] A buffer in which to return the number of items.
		*/
	AIAPI AIErr (*GetLength)(AIXMLNodeListRef nodes, ai::int32 *length);

	/** Retrieves an XML node from a node list by position index.  Use with \c #GetLength()
		to iterate through a list.
			@param nodes The XML node list.
			@param index The 0-based position index.
			@param node [out] A buffer in which to return the node.
		*/
	AIAPI AIErr (*GetItem)(AIXMLNodeListRef nodes, ai::int32 index, AIXMLNodeRef *node);

	// -- utilities --

	/** Swaps XML nodes between two node lists.
			@param list1 The first XML node list.
	 		@param list2 The second XML node list.
			@param position1 The 0-based position index of the node in the first list to move
				to \c position2 in the second list.
			@param position2 The 0-based position index of the node in the second list to move
				to \c position1 in the first list.
			@note This is not a part of the XML DOM specification. */
	AIAPI AIErr (*SwapNodes) (AIXMLNodeListRef list1, AIXMLNodeListRef list2, ai::int32 position1, ai::int32 position2);

} AIXMLNodeListSuite;


//  ------ AIXMLNamedNodeMapSuite -------------------------
/** @ingroup Suites
	This suite allows you to access XML named node maps.

	This suite provides an approximate implementation of the
	XML Level 1 DOM interface for named node maps. See
	http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#ID-1780488922

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIXMLNamedNodeMapSuite and \c #kAIXMLNamedNodeMapSuiteVersion.
 */
typedef struct {

	/** Retrieves the size of a named node map.	Use with \c #GetItem() to iterate
		through items in the map.
			@param map The node map.
			@param length [out] A buffer in which to return the number of nodes.
		*/
	AIAPI AIErr (*GetLength)(AIXMLNamedNodeMapRef map, ai::int32 *length);

	/** Retrieves an XML node from a node map by position index.  Use with \c #GetLength()
		to iterate through a map.
			@param map The node map.
			@param index The 0-based position index.
			@param node [out] A buffer in which to return the node.
		*/
	AIAPI AIErr (*GetItem)(AIXMLNamedNodeMapRef map, ai::int32 index, AIXMLNodeRef *node);

	/** Retrieves a node by name from a node map.
			@param map The node map.
			@param name The node name.
			@param node [out] A buffer in which to return the node.
		*/
	AIAPI AIErr (*GetNamedItem)(AIXMLNamedNodeMapRef map, AIXMLName name, AIXMLNodeRef *node);

	/** Adds a named node to a node map, replacing it if it is already included.
			@param map The node map.
			@param name The node name.
 		*/
	AIAPI AIErr (*SetNamedItem)(AIXMLNamedNodeMapRef map, AIXMLNodeRef node);

	/** Removes a named node from a node map. There is no error if the node
		was not in the map.
			@param map The node map.
			@param name The node name.
		*/
	AIAPI AIErr (*RemoveNamedItem)(AIXMLNamedNodeMapRef map, AIXMLNodeRef node);

} AIXMLNamedNodeMapSuite;



#include "AIHeaderEnd.h"


#endif
