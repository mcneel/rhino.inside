/*
*        Name:	AIBasicUtilities.h
*   $Revision: 1 $
*      Author:	 
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2008 Adobe Systems Incorporated
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*/

#ifndef __AIBasicUtilities__
#define __AIBasicUtilities__

namespace ai
{
	template<typename T>
	inline const T& Min ( const T& obj1, const T& obj2 )
	{
		return obj1 < obj2 ? obj1 : obj2;
	}

	template<typename T>
	inline const T& Max ( const T& obj1, const T& obj2 )
	{
		return obj1 > obj2 ? obj1 : obj2;
	}
}

#endif //__AIBasicUtilities__