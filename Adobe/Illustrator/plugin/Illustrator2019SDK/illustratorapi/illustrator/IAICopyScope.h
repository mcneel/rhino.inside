#ifndef _IAICOPYSCOPE_H_
#define _IAICOPYSCOPE_H_

/*
 *        Name:	IAICopyScope.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Wrapper class for AIArt copy scope objects.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2003-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file
 * in accordance with the terms of the Adobe license agreement
 * accompanying it. If you have received this file from a source other
 * than Adobe, then your use, modification, or distribution of it
 * requires the prior written permission of Adobe.
 *
 */

#include "AIArt.h"
#include <exception>

namespace ai {

/** @ingroup Errors
	See \c CopyScope::Initialize() in \c IAICopyScope.h. */
#define kAICopyScopeAlreadyInitialized	'CSAI'

/** A wrapper class for the \c #AICopyScopeHandle object.

	Copy scopes allow you to group a collection of art object duplication
	operations as parts a single logical copy operation, in order to
	maintain some cross-object information through the set of individual operations.
	An example is linked text object information. When you duplicate the individual
	text frame  objects, the need to maintain their linked attributes.
	You can either copy all of the linked objects in a single call to
	\c #AIArtSuite::DuplicateArt(), or you can create a wrapping
	copy scope and making multiple individual calls to \c #AIArtSuite::DuplicateArt().

	You cannot assign or copy the \c CopyScope objects themselves.
*/
class CopyScope {

public:
	/** Default constructor. Creates an empty copy scope object.
			@return The new copy-scope object.
		*/
	CopyScope() AINOTHROW
	: fScope(0)
	{}

	/** Creates a copy scope object of a given type.
			@param kind The type.
			@return The new copy-scope object.
		*/
	explicit CopyScope(AICopyScopeKind kind)
	: fScope(0)
	{
		Initialize(kind);
	}

	/**	Destructor. Destroys the owned scope if it has not already been
		properly terminated. Does not throw exceptions or return an error code.
		To determine if there was an error terminating the scope. use \c Terminate() instead
	 	*/
	~CopyScope()
	{
		if (IsValid())
		{
			(void) Terminate(std::nothrow);
		}
	}

	/** Reports whether a copy scope has been initialized.
 			@return True if this scope has been initialized.
		*/
	bool IsValid() const AINOTHROW
	{
		return fScope != 0;
	}

	/** Initializes the type of an uninitialized copy scope. Does not throw exceptions.
		    @param kind The scope type.
			@return \c #kAICopyScopeAlreadyInitialized error if the
				scope has already been initialized.
	 */
	AIErr Initialize(AICopyScopeKind kind, const std::nothrow_t&) AINOTHROW
	{
		AIErr result = kNoErr;

		if (!IsValid())
		{
			result = sAIArt->CreateCopyScope(kind, &fScope);
		}
		else
		{
			result = kAICopyScopeAlreadyInitialized;
		}

		return result;
	}

	/** Initializes the type of an uninitialized copy scope. Throws exceptions.
		    @param kind The scope type.
			@return Nothing.
		 */
	void Initialize(AICopyScopeKind kind)
	{
		AIErr result = Initialize(kind, std::nothrow);
		if ( result )
			throw ai::Error(result);
	}

	/** Terminates the copy scope owned by this scope object,
		regardless of whether it has been initialized.
		Does not throw exceptions, but returns an error code.
			@return An error code, \c #kNoErr on success.
		*/
	AIErr Terminate(const std::nothrow_t&) AINOTHROW
	{
		AIErr result = kNoErr;

		if (IsValid())
		{
			result = sAIArt->DestroyCopyScope(fScope);
			fScope = 0;
		}

		return result;
	}

	/**	Terminates the copy scope owned by this scope object,
		regardless of whether it has been initialized.
		Throws exceptions.
			@return Nothing.
		*/
	void Terminate()
	{
		AIErr result = Terminate(std::nothrow);
		if ( result )
			throw ai::Error(result);
	}

private:
	/** Copying and assignment of scope objects is not allowed. */
	CopyScope(const CopyScope& scope);
	/** Copying and assignment of scope objects is not allowed. */
	CopyScope& operator= (const CopyScope& scope);

private:
	AICopyScopeHandle fScope;
};


} // end of namespace ai


#endif	// _IAICOPYSCOPE_H_
