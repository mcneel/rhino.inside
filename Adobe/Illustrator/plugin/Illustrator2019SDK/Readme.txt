Adobe Illustrator Software Development Kit
ReadMe File

______________________________________________________________________

This file contains the latest information about the Adobe Illustrator
SDK.

The SDK enables you to develop software modules that plug into and
extend the functionality of Adobe Illustrator.
______________________________________________________________________

This file has the following sections:
  1. Legal
  2. SDK Documentation Overview
  3. Development Environments
  4. Installing the SDK
  5. What's New
  6. Known Issues
  7. SDK Support and Adobe Partner Programs


***********************************************************
1. Legal
***********************************************************
You may use this SDK only in a manner consistent with the included
End User License Agreement:
  <SDK>/legalnotices/EULAs.pdf


***********************************************************
2. SDK Documentation Overview
***********************************************************
Getting Started Guide:
  File: <SDK>/docs/guides/getting-started-guide.pdf
  Describes the basics of how to get started developing plug-ins
  for Illustrator and provides descriptions of the sample
  plug-ins provided with this SDK.

Porting Guide:
  File: <SDK>/docs/guides/porting-guide.pdf
  Describes how to set up your development environment and port
  existing code this version. Details changes in the public
  API and other aspects of the SDK since the prior release.

Programmer's Guide:
  File: <SDK>/docs/guides/programmers-guide.pdf
  Describes the fundamentals of writing plug-ins for Illustrator.

Using the Adobe Text Engine:
  File: <SDK>/docs/guides/using-adobe-text-engine.pdf
  Describes the components of the Illustrator Adobe Text Engine API,
  and provides recipes for creating, editing, deleting, styling and
  iterating text items in a document, with references to sample code
  and the Adobe Illustrator API Reference.

Adobe Illustrator API Reference:
  Reference documentation for the API is provided in two formats:

  File: <SDK>/docs/references/index.chm

    API reference in compiled HTML format, a searchable help file
    To view the contents in Windows, double-click the index.chm
    file icon in Windows Explorer, to open the home page.
    To view the contents in Mac OS, you need a CMH viewer;
    for options, see "Porting Guide".

  File: <SDK>/docs/references/sdkdocs.tar.gz

    API reference in archive HTML format. After installing the SDK,
    double-click the sdkdocs.tar.gz file to decompress the archive.
    View the HTML documentation in your browser.

API Advisor:
  File: <SDK>/docs/references/apiadvisor-ai18-vs-ai19.html
  Reports class, struct, and file differences between the API included
  with the last SDK and this SDK.


***********************************************************
3. Development Environments
***********************************************************
The following platforms are supported for the development of plug-ins:

Mac OS:
  OS:  Mac OS 10.12
  IDE: Xcode 9.2
  Compiler for C/C++: com.apple.compilers.llvm.clang.1_0
  Base SDK: OS X 10.13
  OS X Deployment Target: OS X 10.12


Windows:
  OS:  Microsoft Windows 7 (including 32 bit)
  IDE: Microsoft Visual C++ 2017 (Visual Studio 2017)

For more details, see the ”Porting Guide."

***********************************************************
4. Installing the SDK
***********************************************************
To install the SDK, download the pre-configured archive for your
platform from the Adobe Illustrator Developers site:

  http://www.adobe.com/devnet/illustrator/

Start by expanding the archive, then follow the detailed instructions
in "Getting Started Guide" to set up your
development platform.


***********************************************************
5. What's New
***********************************************************

- New features:

  See details in "Porting Guide".

- API changes:
   -- New resources format added due to deprecation of .r/.rsrc resource reading APIs.
   -- For complete details of API changes, see
   "Porting Guide" and "API Advisor"

- All samples updated with the new resources format.

***********************************************************
6. Known Issues
***********************************************************

The following are known issues in this SDK. These issues will be
addressed in forthcoming SDKs:

______________________________________________________________________
* If you installed security update 896358 or Microsoft Windows Server 2003
  Service Pack 1 (SP1), you may experience broken links and missing text
  while viewing the <SDK>/docs/references/index.chm file.

  Use one of these workarounds:

  Method 1
  --------
  1. Double-click the index.chm file.
  2. In the "Open File-Security Warning" dialog box, clear the
     "Always ask before opening this file" check box.
  3. Click Open.

  Method 2
  --------
  1. Right-click the index.chm file, then click Properties.
  2. Click Unblock.
  3. Double-click the index.chm file to open the file.

  For details, see http://support.microsoft.com/kb/902225.
______________________________________________________________________

create_project.sh command-line tool is currently broken. It does not replace
the name of the project with the specified name.

Workaround:
- GREP for the default project name and replace it with your own.
______________________________________________________________________

***********************************************************
7. SDK Support and Adobe Partner Programs
***********************************************************
If you require SDK support for the Illustrator SDK,
you may purchase single or multi-pack SDK support cases.
Information on purchasing SDK support cases can be found at:

  http://partners.adobe.com/public/developer/support/index.html

Information on Adobe support, in general, may be found at:

  http://www.adobe.com/support/programs/

If you are a partner who extends, markets, or sells Adobe
products or solutions, you should consider membership in
the Adobe Partner Connection Solution Partner Program.
The Solution Partner Program provides development support,
access to timely product information, as well as various
marketing benefits. To learn more about the program, point
your browser to:

  https://www.adobe.com/cfusion/partnerportal/index.cfm

_____________________________________________________________________________
Copyright 2018 Adobe Systems Incorporated. All rights reserved.

Adobe and Illustrator are registered trademarks or trademarks of Adobe
Systems Incorporated in the United States and/or other countries. Windows
is a registered trademark or trademark of Microsoft Corporation in the
United States and/or other countries. Macintosh is a trademark of Apple
Computer, Incorporated, registered in the United States and other countries.
All other brand and product names are trademarks or registered trademarks of
their respective holders.
_____________________________________________________________________________


