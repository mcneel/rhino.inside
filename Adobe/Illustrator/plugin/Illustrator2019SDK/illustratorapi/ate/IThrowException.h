/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	IThrowException.h
		
	Notes:	define the exception method.
	
 ---------------------------------------------------------------------------------- */
#ifndef __IThrowException__
#define __IThrowException__

#include "ATETypes.h"
#include "ATETypesDef.h"

namespace ATE
{

void Throw_ATE_Exception (ATEErr err);


}// namespace ATE

#endif //__IThrowException__
