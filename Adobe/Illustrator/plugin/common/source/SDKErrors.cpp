//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/source/SDKErrors.cpp $
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

#include "SDKErrors.h"

void aisdk::report_error(ASErr err)
{
	if (sAIUser) {
		char errbuf[5];
		*(reinterpret_cast<ASErr*>(errbuf)) = err;
		errbuf [4] = '\0';
		char buf[1024];
		#ifdef MAC_ENV
			snprintf ( buf, sizeof(buf), "Unexpected internal error=%x, %s", err, errbuf);
		#endif
		#ifdef WIN_ENV
			char tmpbuf[5];
			*(reinterpret_cast<ASErr*>(tmpbuf)) = err;
			tmpbuf [4] = '\0';	
			errbuf[0] = tmpbuf[3];
			errbuf[1] = tmpbuf[2];
			errbuf[2] = tmpbuf[1];
			errbuf[3] = tmpbuf[0];
			_snprintf  ( buf, sizeof(buf), "Unexpected internal error=%x, %s", err, errbuf);
		#endif
		sAIUser->ErrorAlert(ai::UnicodeString(buf));
	}
}

#ifdef DEBUG
void aisdk::report_assert(const char* message, const char* file, int line, bool throwException)
{

	if (sAIUser) {
		char buf[1024];
		#ifdef MAC_ENV
			snprintf ( buf, sizeof(buf), "SDK_ASSERT %s\nFile=%s\nLine=%d", message, file, line);
		#endif
		#ifdef WIN_ENV
			_snprintf ( buf, sizeof(buf), "SDK_ASSERT %s\nFile=%s\nLine=%d", message, file, line);
		#endif
		sAIUser->ErrorAlert(ai::UnicodeString(buf));
	}

	if (throwException) {
		check_assertion(false); // throw assert exception
	}
}
#endif

#ifdef DEBUG
char* aisdk::format_args(const char *str, ...)
{
	static char buf[1024];

	va_list args;
	va_start(args, str);
	#ifdef MAC_ENV
		vsnprintf(buf, sizeof(buf) - 1, str, args);
	#endif
	#ifdef WIN_ENV
		_vsnprintf(buf, sizeof(buf) - 1, str, args);
	#endif

	va_end(args);
	
	return buf;
}
#endif

// End SDKErrors.cpp
