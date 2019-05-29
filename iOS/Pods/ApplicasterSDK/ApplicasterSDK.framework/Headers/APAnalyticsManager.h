//
//  APAnalyticsManager.h
//  applicaster
//
//  Created by Tom Susel on 2/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kAPAnalyticsPingInterval 10.0
#define kAPAnalyticsPingIntervalInt 10

extern NSString *const kAnalyticsManagerStringURLFormat;

@interface APAnalyticsManager : NSObject

/**
 *  
 *
 *  @param accountId 
 */
+ (void)startManagerWithAccountId:(NSString *)accountId;
+ (void)startManagerWithAccountId:(NSString *)accountId bundle:(NSString *)bundle version:(NSString *)version;

+ (void)startAnalyticsRequestWithStringURL:(NSString *)stringURL;
+ (NSString *)getServerPathWithAccountID:(NSString *)accountId;

#pragma mark - Track Events

/*
 log events or errors after session has started
 */
+ (void)trackEvent:(NSString *)eventName;
+ (void)trackEvent:(NSString *)eventName withParameters:(NSDictionary *)parameters;
+ (void)trackError:(NSString *)errorID message:(NSString *)message exception:(NSException *)exception;
+ (void)trackError:(NSString *)errorID message:(NSString *)message error:(NSError *)error;

/* 
 start or end timed events
 */
+ (void)trackEvent:(NSString *)eventName
             timed:(BOOL)timed;

+ (void)trackEvent:(NSString *)eventName
    withParameters:(NSDictionary *)parameters timed:(BOOL)timed;

+ (void)endTimedEvent:(NSString *)eventName
       withParameters:(NSDictionary *)parameters;	// non-nil parameters will update the parameters

/*
 count page views
 */
+ (void)logPageView:(NSURL*)url;					// manually increment page view by 1

@end
