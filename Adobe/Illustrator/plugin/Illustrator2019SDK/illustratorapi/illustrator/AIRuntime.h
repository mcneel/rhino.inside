#ifndef __AIRuntime__
#define __AIRuntime__

/*
 *        Name:	AIRuntime.h
 *   $Revision: 11 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Runtime Environment.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2016 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AINameSpace__
#include "AINameSpace.h"
#endif

#ifndef __AIStringPool__
#include "AIStringPool.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AIUnicodeString__
#include "AIUnicodeString.h"
#endif //__AIUnicodeString__

#ifndef __AIFont__
#include "AIFont.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIRuntime.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIRuntimeSuite			"AI Runtime Suite"
#define kAIRuntimeSuiteVersion12	AIAPI_VERSION(12)
#define kAIRuntimeSuiteVersion	kAIRuntimeSuiteVersion12
#define kAIRuntimeVersion		kAIRuntimeSuiteVersion

/** @ingroup Notifiers
	Your plug-in can subscribe to this notifier when it receives the startup
	selector. It receives the notification only once, when the application
	has completed the startup process. This provides an opportunity to perform
	additional setup operations such as restoring plug-in window positions and
	visibility, or operations that depend on suites unavailable at an earlier time.
*/
#define kAIApplicationStartedNotifier		"AI Application Started Notifier"
/** @ingroup Notifiers
	Sent at application shutdown, allows you to clean up private data. See
	\c #AIRuntimeSuite. */
#define kAIApplicationShutdownNotifier		"AI Application Shutdown Notifier"

/** @ingroup Notifiers
	Sent when the application is activated. */
const char* const kAIApplicationActivatedNotifier = "AI Application Activated Notifier";

/** @ingroup Notifiers
	Sent when the application is deactivated. */
const char* const kAIApplicationDeactivatedNotifier = "AI Application Deactivated Notifier";



/*******************************************************************************
 **
 **	Types
 **
 **/

/** Application name */
typedef const char *AIAppName;
/** Application version */
typedef const char *AIAppVersion;
/** User name, as registered for the application. */
typedef const char *AIUserName;
/** User organization, as registered for the application. */
typedef const char *AIUserOrganization;
/** User serial number, as registered for the application. */
typedef const char *AIUserSerialNumber;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provide functions that allow you to obtain information
	about the name and version number of the plug-in host application.
	You can access application instances of the name space and string
	pool data structures, and the user name, organization, and serial
	number registered for the application.

	The following notifiers are associated with the runtime suite:
	<br> \c #kAIApplicationStartedNotifier
	<br> \c #kAIApplicationShutdownNotifier

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIRuntimeSuite and \c #kAIRuntimeVersion.
*/
struct AIRuntimeSuite {

	/** Retrieves the name of the host application running the plug-in.
		You can use the name to verify that your plug-in is running in
		a supported host application. You can also use the name and
		serial number to key your plug-in to an installed application.
			@param name [out] A buffer in which to return the name,
				as a C-string from the application string pool.
				Do not modify the returned string.
		*/
	AIAPI AIErr (*GetAppName) ( AIAppName *name );

	/** Retrieves the file specification of the host application running the plug-in.
			@param name [out] A buffer in which to return the file specification.
	 	*/
	AIAPI AIErr (*GetAppFileSpecification) ( ai::FilePath &file );

	/** Retrieves the user name, as registered with the application when
		it was installed.
			@param name [out] A buffer in which to return the name,
				as a C-string from the application string pool.
				Do not modify the returned string.
		*/
	AIAPI AIErr (*GetUserName) ( AIUserName *name );

	/** Retrieves the user organization, as registered with the application when
		it was installed.
			@param organization [out] A buffer in which to return the organization,
				as a C-string from the application string pool.
				Do not modify the returned string.
		*/
	AIAPI AIErr (*GetUserOrganization) ( AIUserOrganization *organization );

	/** Retrieves the user serial number, as registered with the application when
		it was installed.
			@param serialNumber [out] A buffer in which to return the serial number,
				as a C-string from the application string pool.
				Do not modify the returned string.
		*/
	AIAPI AIErr (*GetUserSerialNumber) ( AIUserSerialNumber *serialNumber );

	/** Retrieves a reference to the namespace of the host application
		running the plug-in.

		A plug-in can create its own namespace in which to store arbitrary data,
		but it can also use this function to access the application’s namespace.
		The application preferences (among other things) are stored in the
		application namespace.

		Your plug-in should not modify the application’s existing namespace data
		directly, but it can create new data within the application namespace.
			@param space [out] A buffer in which to return the namespace reference.
		*/
	AIAPI AIErr (*GetAppNameSpace) ( AINameSpace **space );

	/** Retrieves a reference to the string pool of the host application
		running the plug-in.

		Illustrator maintains a string pool which any plug-in can access.
		Runtime data for a host is stored in this string pool, and the strings
		returned by functions in this suite belong to the application string pool.
		These references point to the C-string data in the pool, and should
		not be modified. If you need to modify such a string, copy it to
		local storage. See \c #AIStringPoolSuite.
			@param pool [out] A buffer in which to return the string-pool reference.
		*/
	AIAPI AIErr (*GetAppStringPool) ( AIStringPool **pool );

	/**	Gets the amount of physical RAM on the computer, which you can use
		as an estimate of free application memory available.
		(Note that this function returns a numeric value, not an error code.)
			@return The number of bytes of RAM.
		*/
	AIAPI size_t (*GetAppFreeMem) ( void );

	/** Shows the about box for the application. */
	AIAPI AIErr (*ShowAppAboutBox) ( void );

	/** Retrieves the version of the operating system the application is running on.
		(Note that this function returns a constant value, not an error code.)
			@return An integer value of the form: (majorVersion * 100 + minorVersion).
		*/
	AIAPI ai::int32 (*GetSystemVersion) ( void );

	/** Reports whether the operating system is Mac OS X.
			@return True if the operating system is Mac OS X.
		*/
	AIAPI AIBoolean (*GetIsSystemMacOSX) ( void );

	/** Retrieves the major version number of the application
		(X where the version number is X.Y.Z).
		(Note that this function returns a numeric value, not an error code.)
			@return The major version number.
		*/
	AIAPI ai::int32 (*GetAppMajorVersion) ( void );

	/** Retrieves the minor version number of the application
		(Y where the version number is X.Y.Z).
		(Note that this function returns a numeric value, not an error code.)
			@return The minor version number.
		*/
	AIAPI ai::int32 (*GetAppMinorVersion) ( void );

	/** Retrieves the revision number of the application
		(Z where the version number is X.Y.Z).
		(Note that this function returns a numeric value, not an error code.)
			@return The revision number.
		 */
	AIAPI ai::int32 (*GetAppRevisionVersion) ( void );

	/** Retrieves the Unicode name of the host application running the plug-in.
		@param name [out] A buffer in which to return the name,
				as a Unicode string.
	*/
	AIAPI AIErr (*GetAppNameUS) ( ai::UnicodeString& name );

	/** Retrieves the Unicode user name, as registered with the application when
		it was installed.
			@param name [out] A buffer in which to return the name,
				as a Unicode string.
		*/
	AIAPI AIErr (*GetUserNameUS) ( ai::UnicodeString& name );

	/** Retrieves the Unicode organization name, as registered with the application when
		it was installed.
			@param organization [out] A buffer in which to return the name,
				as a Unicode string.
		*/
	AIAPI AIErr (*GetUserOrganizationUS) ( ai::UnicodeString& organization );

	/** Retrieves the default script for the application.
			@param script [out] A buffer in which to return the	script reference.
		*/
	AIAPI AIErr (*GetDefaultScript) ( AIFaceScript *script);

	/** Used internally. */
	AIAPI AIBoolean (*GetIsHonestyBuild) ( void );

	/**  Used internally. */
	AIAPI AIBoolean (*GetIsProductTryAndDie) ( void );

	// Introduced in Illustrator 13

	/** Used internally. Reports whether this is an executable build. */
	AIAPI AIBoolean (*GetIsExeBuild) ( void );

	/** Launches the Adobe Help Viewer and shows an Illustrator help page.
			@param pageID  A null terminated UTF-8 string for the help page ID,
				or a NULL pointer to bring up the default help page.
	*/
	AIAPI AIErr (*ShowAdobeHelp) (const char *pageID);
	
	/** Retrieves the application build number. 
		
		@param isDebug [out] A buffer in which to return a flag, or NULL if flag is not needed. 
		Returns true if this is a debug build, false if this is a release build.
		@returns the revision number.
	*/
	AIAPI ai::int32 (*GetAppBuildNumber) ( AIBoolean *isDebug );
	
	
	/**	Retrieves Adobe user's GUID and AdobeID.

		@returns 0 if fails	
	*/
	AIAPI ai::int32 (*GetUserAdobeID) (const char **userGUID, const char **userAdobeID);
};


#include "AIHeaderEnd.h"


#endif
