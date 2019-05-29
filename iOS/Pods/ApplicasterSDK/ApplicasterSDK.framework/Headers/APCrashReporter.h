//
//  APCrashReporter.h
//  ApplicasterSDK
//
//  Created by Philip Kramarov on 11/8/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APCrashReporter : NSObject

/**
 *  Starts a crash reporter (HockeyApp)
 *  The manager is sharedinstance that handles hockeyApp initiation and delegate callbacks.
 *  When running within simulator will not start the crash reporter.
 *  When running not in debug configuration, we will not show the update version/feedback screen.
 *
 *  @param identifier The identifier of the crash reporter (HockeyApp website, identifier per app)
 */
+ (void)startManagerWithIdentifier:(NSString *)identifier;

@end
