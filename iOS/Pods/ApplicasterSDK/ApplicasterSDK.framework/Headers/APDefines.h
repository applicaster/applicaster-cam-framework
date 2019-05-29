/*
 *  APDefines.h
 *  applicaster
 *
 *  Created by Tom Susel on 1/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#define APAPIMAGORVERSION   1
#define APAPIMINORVERSION   2
#define APOSTYPE            @"ios"

//Debug flags have been moved to APRunModeDefine.h

#ifdef LOCAL_SERVER
#define kAPPLICASTER_HOST @"admin.test.applicaster.com"
#elif defined QA_SERVER
#define kAPPLICASTER_HOST @"admin.qa.applicaster.com"
#elif defined DEMO_SERVER
#define kAPPLICASTER_HOST @"admin.demo.applicaster.com"
#elif defined DEVELOPMENT_SERVER
#define kAPPLICASTER_HOST @"admin.d8v.applicaster.com"
#else
#define kAPPLICASTER_HOST @"admin.applicaster.com"
#endif

NSString *APPLICASTER_HOST();

