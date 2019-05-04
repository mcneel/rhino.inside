/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	Exception.h
		
	Notes:	define ATE exception class.
	
 ---------------------------------------------------------------------------------- */
#ifndef __Exception__
#define __Exception__
#include <exception>
#include "ATETypes.h" //for error values.

namespace ATE
{

class Exception : public std::exception
{
public:
	Exception(ATEErr errorCode)
	:error(errorCode)
	{
	}
// error code
	ATEErr error;
};


}// namespace ATE

#endif //__Exception__
