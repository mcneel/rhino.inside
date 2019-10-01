//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/legacy/stringUtils.cpp $
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

#include "IllustratorSDK.h"
/*
#include <stdio.h>
#include <math.h>
#include "SPConfig.h"

#ifdef MAC_ENV
#include "Memory.h"
#else
#include <string.h>
#endif

*/

#include "stringUtils.h"

static char *strPS( register char *a, register char *b);
unsigned long SUstrlen(char *s);
char *SUstrncat(char *d, char *s, unsigned long size);
void SUmemmove(void *d, void *s, unsigned long len);


unsigned long SUstrlen(char *s)
{
	int lenCount = 0;
	char *strLoc = s;
	
	while (*strLoc != 0)
	{
		lenCount++;
		strLoc++;
	}
		
	return lenCount;
}


char *SUstrncat(char *d, char *s, unsigned long size)
{
	char * src = s;
	char * dst = d;
	unsigned long charsToCopy = size;

	while (*dst)	// advance to end of the destination
		dst++;

	while (charsToCopy)
	{
		*dst = *src;

		dst++;
		src++;

		if (!*src)	// if next char to copy would be NULL, then break
		{
			break;
		}
		
		charsToCopy--;
	}

	*dst = 0;
	
	return d;
}



void SUmemmove(void *d, void *s, unsigned long len)
{
#ifdef MAC_ENV
	BlockMove(s, d, (Size)len);
#else
	memmove(d,s,len);
#endif
}


unsigned char *SUctopstr(char *s)
{
	register int len = SUstrlen(s);
	
	if (len > 255)
		return NULL;
	
	SUmemmove(s + 1, s, len);
	s[0] = (unsigned char) len;
	
	return (unsigned char *) s;
}

char *SUptocstr(unsigned char *p)
{
	register int len = p[0];
	
	SUmemmove(p, p + 1, len);
	p[len] = '\0';
	
	return (char *) p;
}

unsigned char *SUpstrcpy(unsigned char *dst, const unsigned char *src)
{
	register int len = src[0];
	
	dst[0] = len;
	SUmemmove(dst + 1, (void*)(src + 1), len);
	
	return dst;
}




/*
 * pstrcat - add string 'src' to end of string 'dst'
 */
void SUpstrcat(unsigned char *dst, unsigned char *src)
{
	/* copy string in */
	SUmemmove( dst + *dst + 1, src + 1, *src );
	/* adjust length byte */
	*dst += *src;
}

/*
 * pstrinsert - insert string 'src' at beginning of string 'dst'
 */
void SUpstrinsert(unsigned char *dst, unsigned char *src)
{
	/* make room for new string */
	SUmemmove( dst + *src + 1, dst + 1, *dst );
	/* copy new string in */
	SUmemmove( dst+1, src + 1, *src );
	/* adjust length byte */
	*dst += *src;
}




char *SUsafestrncpy(char *dst, const char *src, int dstsize)
{
	// strncpy would always write dstsize bytes, even if the source is (much) smaller
	// strncat doesn't have that quality, and guarantees null-termination to boot
	dst[0] = '\0';
	return SUstrncat(dst, (char*)src, dstsize-1);
}

char *SUsafestrncat(char *dst, const char *src, int dstsize)
{
	// Avoid searching the destination for a null byte twice
	int dstlen = SUstrlen(dst);
	return SUstrncat(dst+dstlen, (char*)src, dstsize - dstlen - 1);
}





/* Converts strings to Postscript string format 
	(i.e. bracketed by parens and with appropriate special character codes 
*/
void SUpasToPostscriptStr( unsigned char dst, unsigned char src) {
	SUctopstr(strPS((char *) dst, (char *) SUptocstr((unsigned char *) src)));
	SUctopstr((char *) src);
	}

static char *strPS( register char *a, register char *b) {
	char *a0 = a;
	register unsigned char c;

	*a++ = '(';
	for (; (c = (unsigned char) *b++) != 0 ; )
		{
		if (c == '\\' || c == '(' || c == ')')
			{
			*a++ = '\\';
			*a++ = c;
			}
		else if (c >= 0x20 && c <= 0x7e)
			*a++ = c;
		else
			{
			*a++ = '\\';
			*a++ = ((c >> 6) & 0x7) + '0';
			*a++ = ((c >> 3) & 0x7) + '0';
			*a++ = (c & 0x7) + '0';
			}
		}
	*a++ = ')';
	*a++ = '\0';
	return a0;
	}
