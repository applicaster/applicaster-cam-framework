//
//  APAnalytics.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 7/29/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APAnalytics : NSObject

#pragma mark - Initialization

+ (BOOL)createAnalyticsProviders:(NSDictionary *)providers;
+ (BOOL)isValidAnalyticsProvidersKeys:(NSDictionary *)providers;
+ (void)addDeviceTokenForGettingsPushNotifications:(NSData *)token;

#pragma mark - Super properties

+ (void)createEventSuperProperties;
+ (void)createEventSuperPropertiesWithParameter:(NSDictionary *)parameters;

#pragma mark - JS 2 Native

+ (void)updateEventWithJSParameters:(NSDictionary *)parameters;
+ (void)updateUserProfileWithJSParameters:(NSDictionary *)parameters;

#pragma mark - Track Events

/*
 log events or errors after session has started
 */
+ (void)trackEvent:(NSString *)eventName;
+ (void)trackEvent:(NSString *)eventName withParameters:(NSDictionary *)parameters;
+ (void)trackError:(NSString *)errorID message:(NSString *)message exception:(NSException *)exception;
+ (void)trackError:(NSString *)errorID message:(NSString *)message error:(NSError *)error;
+ (void)trackEvent:(NSString *)event action:(NSString *)action label:(NSString *)label value:(NSInteger)value;


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
+ (void)logPageView:(NSURL *)url;					// manually increment page view by 1

/*
 user properties
 */
+ (void)updateUserProfileWithFBParameters:(NSDictionary *)parameters;
@end
