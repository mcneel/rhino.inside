#ifndef _IAIREF_H_
#define _IAIREF_H_

/*
 *        Name:	IAIRef.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Reference counted objects.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

 /** @file IAIRef.h */

#include "AICountedObject.h"
#include <utility>

#if AI_AUTO_SUITE_AVAILABLE
	#ifndef AICOUNTEDOBJECTSUITE_DEFINED
		#define AICOUNTEDOBJECTSUITE_DEFINED 1	
	#endif
#endif


namespace ai {
// start of namespace ai


/** Not instantiated. Used only to limit the potential
	for namespace collisions for the declaration of Replace  */
class RefReplaceParam;

enum IncrementPolicy
{
	DoIncrement,	/// Cause the reference count of newly assigned objects to be incremented
	DoNotIncrement	/// Prevent the reference count of newly assigned objects from being incremented
};

/**	Returns a valid reference to the counted-object suite, which can be passed
	to \c ai::IAIRef functions.
	
	This function must be defined by each plug-in that uses this header.
	This header defines a default implementation for the function, which assumes that
	the global variable \c sAICountedObject contains a pointer to the suite, and
	returns the value of that pointer.

	If your plug-in needs a different definition, you must first disable
	the default definition in this file	by setting the constant
	<pre>#define AICOUNTEDOBJECTSUITE_DEFINED</pre> to 1.
	You can then add your own definition of the function to the plug-in.
	For example, the file \c IAIRefAutoSuite.cpp supplies a definition
	of the function that assumes the counted object suite is supplied
	using the facilities of \c AutoSuite.h.
*/

extern AICountedObjectSuite *GetAICountedObjectSuitePtr();

/** Many object types are reference counted, such as dictionaries
	(\c #AIDictionaryRef) and arrays (\c #AIArrayRef). When a plug-in acquires
	such an object, the reference count is automatically incremented.
	The plug-in is responsible for releasing the object when it is no
	longer needed, to avoid	memory leaks.

	You can avoid the responsibility for memory management by using the
	Ref<X> template class. This is a "smart pointer" class which automatically
	takes care of incrementing and decrementing the count of the referenced object.
	For example the following code manipulates a hypothetical art object's
	dictionary without reference counting.

	@code
Ref<AIDictionaryRef> dict1, dict2;
sAIArt->GetDictionary(art, dict1 << Replace);
sAIDictionary->CreateDictionary(dict2 << Replace);
sAIDictionary->SetBooleanEntry(dict2, "my boolean", true);
sAIDictionary->SetDictEntry(dict1, "first dictionary", dict2);
sAIDictionary->CreateDictionary(dict2 << Replace);
sAIDictionary->SetBooleanEntry(dict2, "my boolean", false);
sAIDictionary->SetDictEntry(dict1, "second dictionary", dict2);
	@endcode

	AIEntryRefs retrieved via AIDictionarySuite::Get and passed into functions
	like AIDictionarySuite::Set or AIEntrySuite::To* functions (ex. ToInteger,
	also AsUnicodeString) end up with no net change to their reference count
	since the former increments the count and the latter decrement the count.
	However functions like AIEntrySuite::GetType and AIEntrySuite::Equiv do not
	decrement the reference count so if no other functions are called the count
	must be decremented, which can be done as follows:

	@code
Ref<AIEntryRef> entry(sAIDictionary->Get(dict, key1), ai::DontIncrement);
gEntryType = sAIEntry->GetType(entry);
return;
	@endcode

	@see \c #AICountedObjectSuite
 */

template <class X> class Ref {
public:
	/** Constructs a null reference. */
	Ref () AINOEXCEPT : x(nullptr) {}

	/** Constructs a reference to an object and conditionally increments
		the reference count based on 'policy'. */
	Ref (const X& x, IncrementPolicy policy = DoIncrement);

	/** Copy-constructs a reference from another reference, and
		increments the reference count.  */
	Ref (const Ref<X>& ref);

	/** 
		Swaps internal reference with other
	*/
	void swap(Ref<X>& other) AINOEXCEPT
	{
		std::swap(other.x, x);
	}

#ifdef AI_HAS_RVALUE_REFERENCES
	/** 
		Move Constructor
	*/
	Ref(Ref<X>&& other) AINOEXCEPT
	{
		swap(other);
	}
#endif

	/** Destructor. Decrements the reference count.	 */
	~Ref ();

	/** Implicit conversion to an X allows a Ref<X> to be used wherever an X
		can appear. */
	operator X () const AINOEXCEPT
		{return x;}

	/** Assignment function, decrements the reference count of the current
		object and conditionally increments the count of the newly assigned
		object based on 'policy'.  */
	void Assign(const X& x, IncrementPolicy policy = DoIncrement);

	/** Assignment operator, decrements the reference count of the current
		object and increments the count of the newly assigned object.  
		Copy and Move Assignment operator.
	*/
	Ref<X>& operator= (Ref<X> ref) AINOEXCEPT
	{
		swap(ref);
		return *this;
	}

	/** Comparison operator, tests whether the same objects are identified
		by both references.  */
	bool operator== (const Ref<X>& ref) const AINOEXCEPT
		{return x == ref.x;}

	/**	Comparison operator, tests whether the same objects are identified
		by both references.  */
	bool operator!= (const Ref<X>& ref) const AINOEXCEPT
		{return x != ref.x;}

	/** Allows a Ref<X> to be passed to a function that takes an
		X*. Releases the current referenced object and expects the
		function to assign a new object to the pointer and increment its
		reference count. Use the function \c #Replace() for the
		dummy parameter \c p.
	 */
	X* operator<< (void (*f)(const RefReplaceParam& p));

	/** Allows a Ref<X> to be passed to the \c #AIEntrySuite \c ToXXX
		functions.  Increments the reference count to offset the
		decremented count on the API side, keeping the count correct and
		allowing the destructor on the plug-in side to dispose of the object.
	 */
	Ref<X>& to();

protected:
	X x = nullptr;
};


inline void Replace (const RefReplaceParam&)
{
}

template <class X> Ref<X>::Ref (const X& _x, IncrementPolicy policy) : x(_x)
{
	if (x)
	{
		AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
		if (policy == DoIncrement)
			theSuite->AddRef(x);
	}
}

template <class X> Ref<X>::Ref (const Ref<X>& ref) : x(ref.x)
{
	if (x)
	{
		AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
		theSuite->AddRef(x);
	}
}

template <class X> Ref<X>::~Ref ()
{
	if (x)
	{
		AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
		theSuite->Release(x);
	}
}

template <class X> void Ref<X>::Assign(const X& _x, IncrementPolicy policy)
{
	if (x != _x)
	{
		AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
		if (x)
		{
			theSuite->Release(x);
		}

		x = _x;

		if (x)
		{
			if (policy == DoIncrement)
				theSuite->AddRef(x);
		}
	}
}

template <class X> X* Ref<X>::operator<< (void (*)(const RefReplaceParam &p))
{
	if (x)
	{
		AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
		theSuite->Release(x);
	}
	
	x = nullptr;
	return &x;
}

template <class X> Ref<X>& Ref<X>::to()
{
	AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
	theSuite->AddRef(x);

	return *this;
}

template <class X>
inline bool operator==(const Ref<X>& ref, std::nullptr_t) AINOEXCEPT
{
	return (ref.operator X() == nullptr);
}

template <class X>
inline bool operator==(std::nullptr_t, const Ref<X>& ref) AINOEXCEPT
{
	return (ref == nullptr);
}

template <class X>
inline bool operator!=(const Ref<X>& ref, std::nullptr_t) AINOEXCEPT
{
	return !(ref == nullptr);

}

template <class X>
inline bool operator!=(std::nullptr_t, const Ref<X>& ref) AINOEXCEPT
{
	return (ref != nullptr);
}

// end of namespace ai
}

#if !AICOUNTEDOBJECTSUITE_DEFINED

extern "C"
{
	extern AICountedObjectSuite *sAICountedObject;
}

/** Implements \c #GetAICountedObjectSuitePtr for standard
	naked suite pointers. (The pointer to the suite is stored in a global
	variable of type \c AICountedObjectSuite*.) */

inline AICountedObjectSuite *ai::GetAICountedObjectSuitePtr()
{
	return sAICountedObject;
}

#endif //AICOUNTEDOBJECTSUITE_DEFINED

#endif
