/*
 *        Name:	IAIAutoBuffer.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


#ifndef _IAIAUTOBUFFER_H_
#define _IAIAUTOBUFFER_H_

#include "AITypes.h"

#include <string>

/** @file IAIAutoBuffer.h */

namespace ai {

/** Allocator object class for the AutoBuffer template.
*/
class SPAlloc {
public:
	/** Allocates a block of memory.
			@param byteCount The number of bytes, an unsigned integer.
			@return A pointer to the allocated block.
		*/
	static void* AllocateBlock(size_t byteCount);
	/** Frees a block of memory allocated by \c #AllocateBlock().
			@param block A pointer to the block.
		*/
	static void DeleteBlock(void* block);
};

/** An \c AutoBuffer class object allows you to retrieve string contents
	into a buffer, or to pass or retrieve any array of data types,
	without having to manage the buffer's memory.
*/
/* Notes: elem's type must be limited to POD (plain old data) types for AutoBuffer objects
 *  that are to be passed across the Illustrator SuitePea suite boundary.  This is required as the
 * ctor and dtor for non-POD types are not available on both sides of this boundary.  For single-side
 * of the API boundary usage, clients are free to construct AutoBuffers of any type.
 *
 * In order for AutoBuffer to function properly across the Illustrator plug-in API boundary,
 * the provided SPAlloc class definition must be used.  Allocations MUST be done using the
 * SPBlocks suite.
 *
 * std::vector is not used because AI has no control over the default allocator for the vector and
 * the implementations of std::vector could be different on each side of the API boundary causing problems.
 */
template<class elem, typename size_type=size_t, class A=SPAlloc> class AutoBuffer {
public:
	typedef elem* iterator;
	typedef const elem* const_iterator;

	/** Constructor.
			@param count Initial number of elements that the buffer should be able to hold
		*/
	explicit AutoBuffer (size_type count = 0)
	: fCapacity(count),
	  fBuffer(0)
	{
		if ( fCapacity > 0 )
		{
			fBuffer = reinterpret_cast<elem*>(A::AllocateBlock(ByteCount(fCapacity)));
			Init();
		}
	}
	/** Copy constructor.
		@param b buffer to be copied.
	*/
	AutoBuffer (const AutoBuffer& b)
	: fCapacity(b.fCapacity),
	  fBuffer(0)
	{
		if ( fCapacity > 0 )
		{
			fBuffer = reinterpret_cast<elem*>(A::AllocateBlock(ByteCount(fCapacity)));
			Copy(b.fBuffer);
		}
	}

#ifdef AI_HAS_RVALUE_REFERENCES
	/** Move constructor.
		@param b buffer to be moved from.
	*/
	AutoBuffer (AutoBuffer&& b) AINOEXCEPT : fCapacity{b.fCapacity}, fBuffer{b.fBuffer}
	{
		b.fBuffer = nullptr;
	}
#endif

	/** Destructor.
		*/
	~AutoBuffer ()
	{
		if ( fBuffer )
		{
			Destroy(fBuffer);
			A::DeleteBlock(fBuffer);
		}
	}

	/** Reports whether the buffer object has a handle to a valid buffer.
			@return True if the buffer pointer is valid.
		*/
	bool IsValid () const
	{
		return fBuffer != 0;
	}

	/** Retrieves the buffer.
			@return A writeable pointer to the buffer.
			@note The returned pointer can be invalidated by calls to \c #Resize().
	*/
	elem* GetBuffer () const
	{
		return fBuffer;
	}
	
	explicit operator elem* () const
	{
		return GetBuffer();
	}

	/** Retrieves an element at a given index position in the buffer. Use
		with \c #GetCount() to iterate through elements.
			@param n The 0-based position index.
			@return A writeable reference to the object.
			@note There is no protection for indexing off the end of the array.
		*/
	elem& operator[] (size_type n)
	{
		return fBuffer[n];
	}

	const elem& operator[] (size_type n) const
	{
		return fBuffer[n];
	}

	/** Retrieves the first element in the buffer.
			@note There is no protection for indexing off the begin or end of the array.
		*/
	elem& front()
	{
		return fBuffer[0];
	}

	const elem& front() const
	{
		return fBuffer[0];
	}

	/** Retrieves the last element in the buffer.
			@note There is no protection for indexing off the begin or end of the array.
		*/
	elem& back()
	{
		return fBuffer[fCapacity - 1];
	}

	const elem& back() const
	{
		return fBuffer[fCapacity - 1];
	}

	/** Retrieves the current capacity of the buffer.
			@return The number of elements that can be contained.
		*/
	size_type GetCount () const AINOEXCEPT
	{
		return size();
	}

	size_type size() const AINOEXCEPT
	{
		return fCapacity;
	}

	bool empty() const AINOEXCEPT
	{
		return fCapacity == 0;
	}


	/** Resizes the buffer. If the given size is less than the current
		capacity, the buffer is shortened and truncated elements are destroyed.
		If it is greater, the buffer is grown and the new elements
		are initialized.
			@param newSize The new number of elements.
		*/
	void Resize (size_type newSize)
	{
		if ( newSize != fCapacity )
		{
			elem *newBuffer = reinterpret_cast<elem*>(A::AllocateBlock(ByteCount(newSize)));
			if ( fBuffer )
			{
				elem* oldBuffer = fBuffer;
				fBuffer = newBuffer;
				Copy(oldBuffer, 0, fCapacity < newSize ? fCapacity : newSize );
				
				// initialize any new elements
				Init(fCapacity, newSize);

				Destroy(oldBuffer, 0, fCapacity);
				A::DeleteBlock(oldBuffer);
			}
			else
			{
				fBuffer = newBuffer;
				Init();
			}
			fCapacity = newSize;
		}
	}

	AutoBuffer& operator= (const AutoBuffer& rhs)
	{
		if ( this != &rhs )
		{
			if ( fCapacity != rhs.fCapacity )
			{
				Destroy(fBuffer);
				A::DeleteBlock(fBuffer);
				fBuffer = reinterpret_cast<elem*>(A::AllocateBlock(ByteCount(rhs.fCapacity)));
				fCapacity = rhs.fCapacity;
			}
			Copy(rhs.fBuffer);
		}
		return *this;
	}

#ifdef AI_HAS_RVALUE_REFERENCES
	AutoBuffer& operator= (AutoBuffer&& rhs) AINOEXCEPT
	{
		fCapacity = rhs.fCapacity;
		std::swap(fBuffer, rhs.fBuffer);
		return *this;
	}
#endif

	iterator begin() AINOEXCEPT { return fBuffer; }
	iterator end() AINOEXCEPT { return fBuffer + fCapacity; }
	const_iterator begin() const AINOEXCEPT { return fBuffer; }
	const_iterator end() const AINOEXCEPT { return fBuffer + fCapacity; }

	static size_type lastIndex ()
	{ return size_type(-1); }
private:
	void Init (size_type start = 0, size_type end = lastIndex())
	{
		size_type elemCount = (end == lastIndex() ? GetCount() : end);
		for (size_type i = start; i < elemCount; ++i)
		{
			// invoke the constructor on each element
			new (&fBuffer[i])elem;
		}
	}
	void Destroy (elem* e, size_type start = 0, size_type end = lastIndex())
	{
		size_type elemCount = (end == lastIndex() ? GetCount() : end);
		for (size_type i = start; i < elemCount; ++i)
		{
			e[i].~elem();
		}
	}
	void Copy (const elem* e, size_type start = 0, size_type end = lastIndex())
	{
		size_type elemCount = (end == lastIndex() ? GetCount() : end);
		for (size_type i = start; i < elemCount; ++i)
		{
			fBuffer[i] = e[i];
		}
	}
	size_type ByteCount (size_type elemCount)
	{
		return elemCount * sizeof(elem);
	}
private:
	size_type fCapacity;
	elem* fBuffer;
};

} // end of namespace ai

#endif	// _IAIAUTOBUFFER_H_
