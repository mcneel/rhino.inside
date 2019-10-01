//========================================================================================
//  
//  $File: //ai_stream/rel_23_0/devtech/sdk/public/samplecode/common/includes/SDKErrors.h $
//
//  $Revision: #2 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __SDKErrors_h__
#define __SDKErrors_h__

namespace aisdk
{
	/** Throws exception if the given error code is non zero.
		@param err IN error code.
	*/
	inline void check_ai_error(AIErr err)
	{ if (err) throw ai::Error(err); }

	/** Throws exception if the given pointer is nullptr.
		@param p IN void pointer.
		@param err IN error code.
	*/
	inline void check_allocation(void *p, AIErr err = kOutOfMemoryErr)
	{ if (!p) throw ai::Error(err); }

	/** Throws exception if the given condition is false.
		@param condition IN condition to check.
		@param err IN error code.
	*/
	inline void check_precondition(bool condition, AIErr err = kBadParameterErr)
	{ if (!condition) throw ai::Error(err); }

	/** Throws exception if the given assertion is false.
		@param assertion IN assertion to check.
		@param err IN error code.
	*/
	inline void check_assertion(bool assertion, AIErr err = kCantHappenErr)
	{ if (!assertion) throw ai::Error(err); }

	/** Reports an error in an ADM alert.
		@param err IN error code.
	*/
	void report_error(ASErr err);
	
	#ifdef DEBUG

	/** Reports an assert in an ADM alert then throws exception.
		@param message IN message to display in alert.
		@param file IN file assert originated from.
		@param line IN line assert originated from in file.
		@param throwException IN true to throw an exception, false if not.
		@see SDK_ASSERT
		@see check_assertion
	*/
	void report_assert(const char* message, const char* file, int line, bool throwException);

	/** Returns a printf style formatted string from variable argument list -
		designed to be called to format message for SDK_ASSERT_MSG or SDK_ASSERT_MSG_NOTHROW,
		for example:
		<code>
			SDK_ASSERT_MSG(false, aisdk::format_args("My message=%s: %d", str, num));
		</code>
		@param str IN string of argument.
		@param ... IN 
	*/
	char* format_args(const char *str, ...);

	#endif // DEBUG

	#ifdef DEBUG
	
	/** SDK_ASSERT macro.
		Reports an assert with no message and throws an exception.
	*/
	#define SDK_ASSERT(x) if (!(x)) aisdk::report_assert("",__FILE__, __LINE__, true)

	/** SDK_ASSERT_MSG macro.
		Reports an assert with a message and throws an exception.
	*/
	#define SDK_ASSERT_MSG(x, msg)	if (!(x)) aisdk::report_assert(msg,__FILE__, __LINE__, true)

	/** SDK_ASSERT_NOTHROW macro.
		Reports an assert with no message, does not throw an exception.
	*/
	#define SDK_ASSERT_NOTHROW(x) if (!(x)) aisdk::report_assert("",__FILE__, __LINE__, false)

	/** SDK_ASSERT_MSG_NOTHROW macro.
		Reports an assert with a message, does not throw an exception.
	*/
	#define SDK_ASSERT_MSG_NOTHROW(x, msg)	if (!(x)) aisdk::report_assert(msg,__FILE__, __LINE__, false)
	
	#else // Release
	
	/** SDK_ASSERT macro.
		Reports an assert with no message and throws an exception.
	*/
	#define SDK_ASSERT(x) aisdk::check_assertion(x)

	/** SDK_ASSERT_MSG macro.
		Reports an assert with a message and throws an exception.
	*/
	#define SDK_ASSERT_MSG(x, msg)	aisdk::check_assertion(x)

	/** SDK_ASSERT_NOTHROW macro.
		Reports an assert with no message, does not throw an exception.
	*/
	#define SDK_ASSERT_NOTHROW(x)

	/** SDK_ASSERT_MSG_NOTHROW macro.
		Reports an assert with a message, does not throw an exception.
	*/
	#define SDK_ASSERT_MSG_NOTHROW(x, msg)

	#endif

} // end namespace aisdk

#endif //__SDKErrors_h__

// End SDKErrors.h
