//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/legacy/stringUtils.h $
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

#ifndef __PSTRING__
#define __PSTRING__

#ifdef __cplusplus
extern "C" {
#endif

unsigned char *SUctopstr( char *s );
char *SUptocstr( unsigned char *p );
unsigned char *SUpstrcpy( unsigned char *dst, const unsigned char *src );
unsigned long SUstrlen(char* s);

void SUpstrcat( unsigned char *dst, unsigned char *src );
void SUpstrinsert( unsigned char *dst, unsigned char *src );

char *SUsafestrncpy(char *dst, const char *src, int dstsize);
char *SUsafestrncat(char *dst, const char *src, int dstsize);

void SUpasToPostscriptStr( unsigned char dst, unsigned char src );

#ifdef __cplusplus
}
#endif


#endif
