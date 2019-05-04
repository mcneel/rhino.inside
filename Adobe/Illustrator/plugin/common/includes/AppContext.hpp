//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/AppContext.hpp $
//
//  $Revision: #1 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __AppContext_hpp__
#define __AppContext_hpp__

#ifndef __SPAccess__
#include "SPAccess.h"
#endif

class AppContext
{
protected:
	void *fAppContext;

public:
	AppContext(SPPluginRef plugin);
	~AppContext();
};

#endif
