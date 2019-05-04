/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2017 Adobe
* 
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

#include "AITypes.h"
#include "AIAssert.hpp"

#if defined(AI_HAS_RVALUE_REFERENCES) && defined(AI_HAS_DEFAULTED_FUNCTIONS)
#include "IAILiteralString.h"
#endif


/**
	A helper class to handle AIErr when code is designed to handle exceptions. 
	Throws an error if the returned value is != kNoErr
	No explicit error handling is required on each statement.
	
	Usage
	
	AIErrorThrower error = sAIArt->GetArtType(art, &artType); // Throws if returned value is != kNoErr
	error = sAIArt->GetArtName(...);
	error = sAIPathStyle->GetPathStyle(...);
	
*/
class AIErrorThrower
{
public:
	AIErrorThrower(AIErr err = kNoErr) : fError(err)
	{
		check_throw(fError);
	}

	AIErrorThrower& operator=(AIErr err)
	{
		fError = err;
		check_throw(fError);
		return (*this);
	}
	
	AIErrorThrower& operator=(AIErrorThrower err)
	{
		*this = err.fError;
		return (*this);
	}

	operator AIErr() const AINOEXCEPT { return fError; }

private:
	void check_throw(AIErr err)
	{
		if (err != kNoErr)
		{
			throw ai::Error(err);
		}
	}

private:
	AIErr fError;
};

/**
	A helper class to handle AIErr. Shows an assert if the error is != kNoErr
	
	Usage
	
	AIErrorHandler error = sAIArt->GetArtType(art, &artType); // would assert if error != kNoErr
	
*/
class AIErrorHandler 
{
public:
	AIErrorHandler(AIErr err = kNoErr) : fError(err)
	{	
		check_assert(fError);
	}

	AIErrorHandler& operator=(AIErr err)
	{
		fError = err;
		check_assert(fError);
		return (*this);
	}

	AIErrorHandler& operator=(AIErrorHandler err)
	{
		*this = err.fError;
		return (*this);
	}

	operator AIErr() const AINOEXCEPT { return fError; }

private:
	void check_assert(AIErr err)
	{
		AIAssert(err == kNoErr || err == kCanceledErr);
	}

private:
	AIErr fError;
};

namespace ai
{
#if defined(AI_HAS_RVALUE_REFERENCES) && defined(AI_HAS_DEFAULTED_FUNCTIONS)
	/** @ingroup Errors (debugging) */
	constexpr AIErr kUnknownExceptionErr			{ 'UNEX' };

	/** @ingroup Errors (debugging) */
	constexpr AIErr kStdExceptionErr				{ 'STEX' };

	/** @ingroup Errors (debugging) */
	constexpr LiteralString kAIErrExceptionStr		{ "AIErr Exception" };

	/** @ingroup Errors (debugging) */
	constexpr LiteralString kUnknownExceptionStr	{ "Unknown Exception" };
#endif

} //namespace ai

#define AI_CATCH_RETURN \
	catch (const ai::Error& e) { return e; } \
	catch (const std::exception&) { return ai::kStdExceptionErr; } \
	catch (AIErr e) { return e; } \
	catch (...) { return ai::kUnknownExceptionErr; }

#define AI_CATCH_ASSERT_RETURN \
	catch (const ai::Error& e) \
	{ \
		AIMsgAssert(e == kNoErr || e == kCanceledErr, e.what()); \
		return e; \
	} \
	catch (const std::exception& e) \
	{ \
		AIMsgAssert(false, e.what()); \
		ai::NOTUSED(e); \
		return ai::kStdExceptionErr; \
	} \
	catch (AIErr e) \
	{ \
		AIMsgAssert(e == kNoErr || e == kCanceledErr, ai::kAIErrExceptionStr.c_str()); \
		return e; \
	} \
	catch (...) \
	{ \
		AIMsgAssert(false, ai::kUnknownExceptionStr.c_str()); \
		return ai::kUnknownExceptionErr; \
	}

#define AI_CATCH_ASSERT_RETURN_ERROR(error) \
	catch (const ai::Error& e) \
	{ \
		bool isCovered = e == kNoErr || e == kCanceledErr; \
		AIMsgAssert(isCovered, e.what()); \
		if (!isCovered) \
			return error; \
		return e; \
	} \
	catch (const std::exception& e) \
	{ \
		AIMsgAssert(false, e.what()); \
		ai::NOTUSED(e); \
		return error; \
	} \
	catch (AIErr e) \
	{ \
		bool isCovered = e == kNoErr || e == kCanceledErr; \
		AIMsgAssert(isCovered, ai::kAIErrExceptionStr.c_str()); \
		if (!isCovered) \
			return error; \
		return e; \
	} \
	catch (...) \
	{ \
		AIMsgAssert(false, ai::kUnknownExceptionStr.c_str()); \
		return error; \
	}

#define AI_CATCH_RETURN_ERROR(error) \
	catch (const ai::Error& e) \
	{ \
		if (e != kNoErr && e != kCanceledErr) \
			return error; \
		return e; \
	} \
	catch (const std::exception&) \
	{ \
		return error; \
	} \
	catch (AIErr e) \
	{ \
		if (e != kNoErr && e != kCanceledErr) \
			return error; \
		return e; \
	} \
	catch (...) \
	{ \
		return error; \
	}

#define AI_CATCH_NO_RETURN \
    catch (const ai::Error& ) \
    { \
    } \
    catch (const std::exception& ) \
    { \
    } \
    catch (AIErr) \
    { \
    } \
    catch (...) \
    { \
    }

#define AI_CATCH_ASSERT_NO_RETURN \
	catch (const ai::Error& e) \
	{ \
		AIMsgAssert(e == kNoErr || e == kCanceledErr, e.what()); \
		ai::NOTUSED(e); \
	} \
	catch (const std::exception& e) \
	{ \
		AIMsgAssert(false, e.what()); \
		ai::NOTUSED(e); \
	} \
	catch (AIErr e) \
	{ \
		AIMsgAssert(e == kNoErr || e == kCanceledErr, ai::kAIErrExceptionStr.c_str());\
		ai::NOTUSED(e); \
	} \
	catch (...) \
	{ \
		AIMsgAssert(false, ai::kUnknownExceptionStr.c_str()); \
	}
