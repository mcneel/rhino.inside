//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/PluginStd.h $
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

// Common prefix header for Macintosh

//This let's us use p2cstr, c2pstr, C2PStr, and P2CStr.
//These functions have been deprecated. We'll hopefully remove this in the future.
//dmaclach
#define OLDP2C 1

// Let things know we're working on the Mac side
#define MAC_ENV 1

#ifndef macintosh
#define macintosh 1
#endif

#define Platform_Carbon 1

