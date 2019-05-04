/*
 *        Name:	ASMemory.cpp
 *   $Revision: 4 $
 *      Author:	Dave Lazarony 
 *        Date:	6/28/94
 *     Purpose:	ASMemory.cpp is used to manage memory allocations through SweetPea.
 *				This file declares the new and delete operators for memory allocation within 
 *				a plug-in.
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

#include "ASTypes.h"
#include "SPBasic.h"

#include <new>
//#include <stdlib.h>

extern "C" SPBasicSuite *sSPBasic;

void * operator new[](size_t size)  throw(std::bad_alloc)
{
	void *addr = nullptr;
	
	if (sSPBasic)
	{
		 ASErr error = sSPBasic->AllocateBlock(size, &addr);
		 if (error)
		 	addr = nullptr; 	
	}
//	else
//		DebugStr("\p new() called without sSPBlocks");
	
	return addr;
}

void * operator new(size_t size)  throw(std::bad_alloc)
{
	void *addr = nullptr;
	
	if (sSPBasic)
	{
		 ASErr error = sSPBasic->AllocateBlock(size, &addr);
		 if (error)
		 	addr = nullptr; 	
	}
//	else
//		DebugStr("\p new() called without sSPBlocks");
	
	return addr;
}

void operator delete(void * p) throw()
{
	if (sSPBasic && p != NULL)
		 sSPBasic->FreeBlock(p);
//	else
//		DebugStr("\p delete() called without sSPBlocks");
}

void operator delete [] (void * p) throw()
{
	if (sSPBasic && p != NULL)
		 sSPBasic->FreeBlock(p);
//	else
//		DebugStr("\p delete() called without sSPBlocks");
}




// -------------------------------------------------------
// No throw versions
// -------------------------------------------------------
void * operator new[](size_t size, const std::nothrow_t&) throw()
{
	void *addr = nullptr;
	
	if (sSPBasic)
	{
		 ASErr error = sSPBasic->AllocateBlock(size, &addr);
		 if (error)
		 	addr = nullptr; 	
	}
//	else
//		DebugStr("\p new() called without sSPBlocks");
	
	return addr;
}

void * operator new(size_t size, const std::nothrow_t&) throw()
{
	void *addr = nullptr;
	
	if (sSPBasic)
	{
		 ASErr error = sSPBasic->AllocateBlock(size, &addr);
		 if (error)
		 	addr = nullptr; 	
	}
//	else
//		DebugStr("\p new() called without sSPBlocks");
	
	return addr;
}

void operator delete(void * p, const std::nothrow_t&) throw()
{
	if (sSPBasic && p != NULL)
		 sSPBasic->FreeBlock(p);
//	else
//		DebugStr("\p delete() called without sSPBlocks");
}

void operator delete [] (void * p, const std::nothrow_t&) throw()
{
	if (sSPBasic && p != NULL)
		 sSPBasic->FreeBlock(p);
//	else
//		DebugStr("\p delete() called without sSPBlocks");
}
