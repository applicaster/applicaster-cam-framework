//
//  APRunModeDefine.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 4/29/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

// Only production server is allowed to used in app store relase version.

#ifndef APP_STORE
//#define LOCAL_SERVER
//#define QA_SERVER
//#define DEVELOPMENT_SERVER
//#define DEMO_SERVER
#define SETTINGS_SERVER
#endif
