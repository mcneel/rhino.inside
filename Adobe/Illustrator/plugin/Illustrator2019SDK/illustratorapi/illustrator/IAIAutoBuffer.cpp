/*
 *        Name:	IAIAutoBuffer.cpp
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Plug-in side implementation of the
 *				ai::AutoBuffer object interface.
 *				This file should NOT be included in the 
 *				core application.
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

#include "IAIAutoBuffer.h"
#include "SPBlocks.h"

#include "AITypes.h"	// For ai::Error & inclusion of ASTypes.h 

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(SPBlocks)
#elif defined(_IAIAUTOBUFFER_SUITE_INCLUDE_H_)
    #include _IAIAUTOBUFFER_SUITE_INCLUDE_H_
#else
    #ifndef _IAIAUTOBUFFER_SUITE_USE_C_LINKAGE_
	    #define _IAIAUTOBUFFER_SUITE_USE_C_LINKAGE_ 1
    #endif
    #if _IAIAUTOBUFFER_SUITE_USE_C_LINKAGE_
    extern "C"
    {
    #endif
	/** The plug-in using the ai::AutoBuffer class is required to provide
		the SPBlocksSuite pointer.  Alternatively, a plug-in may provide 
		its own implementation for the AllocateBlock and DeleteBlock.
	*/
	extern SPBlocksSuite *sSPBlocks;

    #if _IAIAUTOBUFFER_SUITE_USE_C_LINKAGE_
    }
    #endif // _IAIAUTOBUFFER_SUITE_USE_C_LINKAGE_

#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ai::SPAlloc methods

void* ai::SPAlloc::AllocateBlock (size_t byteCount)
{
	void* block = 0;
	SPErr spError = sSPBlocks->AllocateBlock( byteCount, "ai::SPAlloc::AllocateBlock", &block );
	if ( spError != 0 )
	{
		throw ai::Error(kOutOfMemoryErr);
	}
	return block;
}

void ai::SPAlloc::DeleteBlock (void* block)
{
	if ( block )
	{
		/*SPErr spError =*/ sSPBlocks->FreeBlock (block);
	}
}
