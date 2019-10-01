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

#include "ASConfig.h"

#if defined(MAC_ENV)
#include "./compiler/AIConfigClang.h"

#elif defined(WIN_ENV)
#include "./compiler/AIConfigMSVC.h"

#else
#error "Platform not supported or configured"

#endif // MAC_ENV