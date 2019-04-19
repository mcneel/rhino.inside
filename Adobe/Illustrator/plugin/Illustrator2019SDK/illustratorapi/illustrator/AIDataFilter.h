#ifndef __AIDataFilter__
#define __AIDataFilter__

/*
 *        Name:	AIDataFilter.h
 *   $Revision: 7 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Data Filter Suite.
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

#include "AIFilePath.h"

#include "AIHeaderBegin.h"

/** @file AIDataFilter.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

/** Data filter suite name. */
#define kAIDataFilterSuite				"AI Data Filter Suite"
/** Data filter suite version. */
#define kAIDataFilterSuiteVersion8		AIAPI_VERSION(8)

/** Data filter suite version. */
#define kAIDataFilterSuiteVersion		kAIDataFilterSuiteVersion8
#define kAIDataFilterVersion			kAIDataFilterSuiteVersion


/** @ingroup Errors */
#define kDataFilterErr					'DFER'


/*******************************************************************************
 **
 **	Types
 **
 **/
/** Opaque reference to a data filter. */
typedef struct DataFilter AIDataFilter;

/** This structure allows a plug-in to implement a stream by supplying
	the stream methods. A method can be \c NULL. If a null method is
	invoked, the calling function returns \c #kDataFilterErr. */
typedef struct _t_AIPluginStream {
	/** Reads data from a stream. Reads up to \c count bytes into \c buffer,
		returning the number of bytes that were read.
			@param stream The stream.
			@param buffer [out] A buffer in which to return the data.
			@param count [in, out] A pointer to the maximum number of bytes to read.
				Returns the number of bytes actually read.
		*/
	AIAPI AIErr (*ReadProc) ( struct _t_AIPluginStream* stream, char* buffer, size_t* count );
	/** Writes data to a stream.
			@param stream The stream.
			@param buffer A buffer containing the data.
			@param count The number of bytes in \c buffer.
		*/
	AIAPI AIErr (*WriteProc) ( struct _t_AIPluginStream* stream, const char* buffer, size_t count );
	/** Seeks to a position in a stream.
			@param stream The stream.
			@param count The offset into the stream.
		*/
	AIAPI AIErr (*SeekProc) ( struct _t_AIPluginStream* stream, ai::sizediff_t count );
	/** Marks the current position in a stream
			@param stream The stream.
			@param count [out] A buffer in which to return the offset into the stream.
		*/
	AIAPI AIErr (*MarkProc) ( struct _t_AIPluginStream* stream, ai::sizediff_t *count );
	/** Terminates a stream.
			@param The stream.
		*/
	AIAPI AIErr (*TerminateProc) ( struct _t_AIPluginStream* stream );
} AIPluginStream;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	A data filter is an object that bytes of data can be read from or written to.
	The filter usually does something interesting with those bytes. For example,
	it might write them to a disk file, send them over a network or it could
	perform JPEG encoding and decoding.

	This suite provides functions to create filters that read and write files, buffers,
	or memory blocks, and that encode/decode and compress/decompress data.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDataFilterSuite and \c #kAIDataFilterVersion.

	Data filters can be linked together. Each filter in the linked chain gets data from
	or puts data to the previous filter. A file filter could, for example, be linked
	to an ASCII encoding filter which is in turn linked to a binary compression filter.
	The result is a composite filter that compresses and ASCII-encodes data before writing
	it to a file.

	The following code shows how to set up a data filter that performs buffered
	writes to a file. Note that \c #LinkDataFilter() must be called even for the
	first filter as it initializes the filter.
@code
AIErr result = kNoErr;
AIDataFilter* dstfilter = NULL;
AIDataFilter* filter;
if (!result)
	result = sAIDataFilter->NewFileDataFilter(file, "write", 'ART5', 'TEXT', &filter);
if (!result) {
	result = sAIDataFilter->LinkDataFilter(dstfilter, filter);
	dstfilter = filter;
}
if (!result)
	result = sAIDataFilter->NewBufferDataFilter(32*1024, &filter);
if (!result) {
	result = sAIDataFilter->LinkDataFilter(dstfilter, filter);
	dstfilter = filter;
}
@endcode

	When you have finished with a filter, you can use the following code to close it.
@code
AIErr result = kNoErr;
while (dstfilter)  {
	AIErr tmpresult = sAIDataFilter->UnlinkDataFilter(dstfilter, &dstfilter);
	if (!result)
		result = tmpresult;
}
@endcode
*/
struct AIDataFilterSuite {

	/** Initializes a filter and links it to the previous filter for input
		or output.
			@param prev A pointer to the previous filter (the source or
				destination of data read or written by this filter). Can be
				null for the first filter in a chain, or a filter that is not linked.
			@param next A pointer to the filter to initialize and link.
		*/
	AIAPI AIErr (*LinkDataFilter) ( AIDataFilter *prev, AIDataFilter *next );

	/** Terminates a filter. If the filter is writing, flushes any writes.
			@param next A pointer to the filter to terminate.
			@param prev [out] A buffer in which to return a pointer to the
				previous linked filter, which contains any data written
				before termination.
		 */
	AIAPI AIErr (*UnlinkDataFilter) ( AIDataFilter *next, AIDataFilter **prev );

	/** Reads data from the filter's source stream.
			@param filter A pointer to the filter.
			@param store [out] A buffer in which to return the data.
			@param count [in, out] A pointer to the maximum number of bytes to read.
				Returns the number of bytes actually read, 0 if the stream
				is exhausted.
		 */
	AIAPI AIErr (*ReadDataFilter) ( AIDataFilter *filter, char *store, size_t *count );

	/** Writes data to the filter's destination stream.
			@param filter A pointer to the  filter.
			@param store A buffer containing the data.
			@param count A pointer to the number of bytes in \c store.
		*/
	AIAPI AIErr (*WriteDataFilter) ( AIDataFilter *filter, const char *store, size_t *count );

	/** Seeks to a position in a filter's stream, as returned by \c #MarkDataFilter().
		Not all data filters support random access.
			@param filter A pointer to the  filter.
			@param count A pointer to the new position, an offset into the stream.
		*/
	AIAPI AIErr (*SeekDataFilter) ( AIDataFilter *filter, ai::sizediff_t *count );

	/** Reports the current position in a filter's stream.
			@param filter A pointer to the  filter.
			@param count [out] A buffer in which to return the position, an offset
				into the stream.
		*/
	AIAPI AIErr (*MarkDataFilter) ( AIDataFilter *filter, ai::sizediff_t *count );

	/** Creates a new file data filter that reads to or writes from a file.
			@param spec The file associated with the filter.
			@param mode How the filter is used, one of \c "read", \c "write",
				or \c "append".
			@param creator The file creator (for Mac OS)
			@param type The file type (for Mac OS)
			@param filter [out] A buffer in which to return the new filter reference.
		*/
	AIAPI AIErr (*NewFileDataFilter) ( const ai::FilePath &spec, const char *mode, size_t creator, ai::int32 type, AIDataFilter **filter );

	/** Creates a new buffer data filter that reads from or writes to a
		linked filter, buffering data into chunks of a specified size.
			@param size The number of bytes to read or write at a time.
			@param filter [out] A buffer in which to return the new filter reference.
		*/
	AIAPI AIErr (*NewBufferDataFilter) ( size_t size, AIDataFilter **filter );

	/** Creates a new ASCIIHEX data filter that encodes or decodes data from a linked
		filter using ASCII Hex. That is, it uses the characters 0-9 and A-F to represent
		hexadecimal numbers. The resulting sequence of characters is broken up
		into lines by inserting line break characters as needed. Each line can
		additionally be preceded by a number of tab characters.
			@param state Whether the filter is encoding or decoding, one of:
				\li \c "write" (encoding)
				\li \c "read" (decoding)

			@param shift The number of tab characters to insert before each line.
			@param filter [out] A buffer in which to return the new filter reference.
		*/
	AIAPI AIErr (*NewHexdecDataFilter) ( const char *state, ai::int32 shift, AIDataFilter **filter );

	/** Creates a new block data filter that reads from and writes to
		a specified block of memory.
			@param address The address of the block.
			@param size The number of bytes in the block.
			@param filter [out] A buffer in which to return the new filter reference.
		*/
	AIAPI AIErr (*NewBlockDataFilter) ( void *address, size_t size, AIDataFilter **filter );

	/** Creates a new random access data filter that reads from and writes to
		Illustrator's virtual memory. Use to create a temporary file that is
		paged to and from memory as needed.
			@param initialsize The end of the initial stream, a number of bytes.
				If \c NULL, the initial stream is empty.
			@param filter [out] A buffer in which to return the new filter reference.
		*/
	AIAPI AIErr (*NewVMDataFilter) (size_t initialsize, AIDataFilter **filter );

	/** Creates a new ASCII85 data filter that encodes or decodes data from
		 a linked filter. The resulting sequence of characters is broken up
		into lines by inserting line break characters as needed. Each line can
		additionally be preceded by a prefix string.
			@param statestr Whether the filter is encoding or decoding, one of:
				\li \c "write" (encoding)
				\li \c "read" (decoding)

			@param prefix The string to insert at the start of each line.
			@param filter [out] A buffer in which to return the new filter reference.
		*/
	AIAPI AIErr (*NewA85DataFilter) ( const char *statestr, const char* prefix, AIDataFilter **filter );

	/** Creates a new ZLib data filter that compresses or decompresses data from a linked filter.
			@param statestr Whether the filter is compressing or decompressing, one of:
				\li \c "write" (compressing)
				\li \c "read" (decompressing)

			@param filter [out] A buffer in which to return the new filter reference.
		*/
	AIAPI AIErr (*NewZDataFilter) ( const char *statestr, AIDataFilter **filter );

	/* New in Illustrator 10.0 */

	/** Creates a new data filter for a stream with specified methods.
		It is typically at one end of a filter chain, to act as a data source or
		sink.
			@param stream The stream, which you have initialized with
				a set of data-handling procedures.
			@param filter  [out] A buffer in which to return the new filter reference, .
		*/
	AIAPI AIErr (*NewPluginStream) ( AIPluginStream* stream, AIDataFilter **filter );

 	/* New in Illustrator 13.0 */

 	/** Creates a data filter for streaming data from a plug-in resource.
		Searches for a resource of a given type in the plug-in's resource file.
		Identify the specific resource using either a numeric ID or name string.
		The type, ID, and name are defined by the plug-in that owns the resource
 			@param plugin The plug-in object for the plug-in that owns the resource.
			@param type The resource type constant, a 4-byte value.
			@param id The unique resource identifier.
			@param name The resource name.
			@param filter  [out] A buffer in which to return the new filter reference, .
 		*/
	AIAPI AIErr (*NewResourceDataFilter) ( SPPluginRef plugin, ai::int32 type, ai::int32 id, const char *name, AIDataFilter **filter);

};


#include "AIHeaderEnd.h"


#endif
