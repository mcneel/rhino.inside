#ifndef _AUTOSUITE_H_
#define _AUTOSUITE_H_

/*
 *        Name:	AutoSuite.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2017 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include	"SPBasic.h"
#include	"AITypes.h"


namespace ai {
// start of namespace ai

//--------------------------------------------------------------------------------
// The AutoSuite class together with the template SuitePtr class provides
// automatic acquisition and releasing of suite pointers. To use these classes
// a plugin must do the following:
//
// 1. declare the following globals somewhere, they provide the head of the
// 		list of suites acquired and a pointer to the SPBasicSuite needed to
//		acquire suites.
//		ai::AutoSuite* ai::AutoSuite::sHead;
//		SPBasicSuite* ai::AutoSuite::sSPBasic;
//
// 2. call ai::AutoSuite::Load(message->d.basic) on Startup and Reload. This
//		supplies the SPBasicSuite which is needed to acquire additional suites.
//
// 3. call ai::AutoSuite::Unload() on Unload and Shutdown. This releases all
//		suites the plugin has acquired.
//
// To declare and use an auto suite pointer in a particular source file write
// code such as that which follows. If a suite cannot be acquired an exception
// will be thrown.
//
//	#include "AutoSuite.h"
//	#include "AIArt.h"
//
//	use_suite(AIArt)
//
//	int myPathMaker (AIArtHandle* path)
//	{
//		sAIArt->NewArt(kPathArt, kPlaceAboveAll, 0, path);
//	}
//
// The following code fragment illustrates the use of a SuiteContext. The
// constructor of the context remembers which suites were acquired at that
// time. Its destructor releases all suites acquired since it was constructed.
// The overhead for doing this is trivial.
//
//	int myFunction ()
//	{
//		ai::SuiteContext mycontext;
//		... lots of code ...
//	}
//--------------------------------------------------------------------------------

class AutoSuite {
	friend class SuiteContext;
public:

	AutoSuite(const char* name, ai::int32 version) :
		fName(name), fVersion(version)
	{}

	// initialize AutoSuite mechanism on startup or reload specifying the
	// address of the SPBasicSuite
	static void Load (SPBasicSuite* basic)
	{
		sSPBasic = basic;
		sHead = nullptr;
	}

	// on unload or shutdown releases all suites
	static void Unload (AutoSuite* contextHead = nullptr)
	{
		while (sHead != contextHead)
		{
			sHead->Release();
			sHead = sHead->fNext;
		}
	}

	// acquire the suite pointer
	const void* Acquire ()
	{
		if (!fSuite && sSPBasic)
		{
			SPErr error = sSPBasic->AcquireSuite(Name(), Version(), &fSuite);
			if (error)
				throw ai::Error(error);
			Push(this);
		} 
		return fSuite;
	}
	
	// release the suite pointer
	void Release ()
	{
		if (fSuite && sSPBasic)
		{
			sSPBasic->ReleaseSuite(Name(), Version());
			fSuite = nullptr;
		}
	}

	// does the suite exist?
	AIBoolean SuiteExists ()
	{
		try
		{
			Acquire();
		}
		catch (ai::Error&)
		{
		}
		return fSuite != nullptr;
	}

protected:
	// globals needed by the mechanism
	static SPBasicSuite* sSPBasic;
	static AutoSuite* sHead;

	// adds the suite to the list of those acquired
	static void Push (AutoSuite* suite)
		{suite->fNext = sHead; sHead = suite;}

	// subclass must define the suite name and version
	const char* Name() const { return fName; }
	ai::int32 Version() const { return fVersion; }

	AutoSuite(const AutoSuite&);
	AutoSuite & operator =(const AutoSuite&);
	
	AutoSuite* fNext = nullptr;		// pointer to next suite in chain
	const void* fSuite = nullptr;			// the suite pointer itself
	const char* fName = nullptr;
	const ai::int32 fVersion = 0;
};


// a SuiteContext can be used to ensure that all suites acquired within the
// context are released on exit
class SuiteContext {
public:
	SuiteContext () : fHead(AutoSuite::sHead) {}
	~SuiteContext () { AutoSuite::Unload(fHead); }

private:
	SuiteContext(const SuiteContext&);
	SuiteContext& operator =(const SuiteContext&);
	AutoSuite* fHead;
};


// an actual smart suite pointer
template <class suite> class Suite {
public:
	bool operator !() { return !Exists(); }

	operator bool() { return (Exists() != false); }

	AIBoolean Exists () { return Ptr().SuiteExists(); }

	const typename suite::methods* operator-> ()
	{
		return static_cast<const typename suite::methods*>(Ptr().Acquire());
	}

private:
	AutoSuite& Ptr ()
	{
		static AutoSuite sSuitePtr(suite::name(), suite::version);
		return sSuitePtr;
	}
};

#ifdef AI_HAS_NULLPTR
template <class suite>
inline bool operator==(Suite<suite> suitePtr, std::nullptr_t)
{
	return !suitePtr;
}

template <class suite>
inline bool operator==(std::nullptr_t, Suite<suite> suitePtr)
{
	return (suitePtr == nullptr);
}

template <class suite>
inline bool operator!=(Suite<suite> suitePtr, std::nullptr_t)
{
	return !(suitePtr == nullptr);
}

template <class suite>
inline bool operator!=(std::nullptr_t, Suite<suite> suitePtr)
{
	return (suitePtr != nullptr);
}
#endif // AI_HAS_NULLPTR

// end of namespace ai
}


//--------------------------------------------------------------------------------
// the following macros are used to declare a non-ADM suite pointer.
//--------------------------------------------------------------------------------

#define declare_suite(suite) \
	namespace ai { \
		class S##suite { \
		public: \
			typedef suite##Suite methods; \
			enum {version = k##suite##SuiteVersion}; \
			static const char* name () {return k##suite##Suite;}; \
		}; \
	}
#define define_suite(suite) static ai::Suite<ai::S##suite> s##suite;
#define use_suite(suite) declare_suite(suite) define_suite(suite)

#define extern_declare_suite(suite) declare_suite(suite) extern ai::Suite<ai::S##suite> s##suite;
#define extern_define_suite(suite) ai::Suite<ai::S##suite> s##suite;

//--------------------------------------------------------------------------------
// the following macros are used to declare an ADM suite pointer. the suite
// version is needed in addition to its name.
//--------------------------------------------------------------------------------

#define declare_adm_suite(suite, vers) \
	namespace ai { \
		class S##suite##vers { \
		public: \
			typedef suite##Suite##vers methods; \
			enum {version = k##suite##SuiteVersion##vers}; \
			static const char* name () {return k##suite##Suite;}; \
		}; \
	}
#define define_adm_suite(suite, vers) static ai::Suite<ai::S##suite##vers> s##suite;
#define use_adm_suite(suite, vers) declare_adm_suite(suite, vers) define_adm_suite(suite, vers)
#define extern_declare_adm_suite(suite, vers) declare_adm_suite(suite, vers) extern ai::Suite<ai::S##suite##vers> s##suite;
#define extern_define_adm_suite(suite, vers) ai::Suite<ai::S##suite##vers> s##suite;


#endif
