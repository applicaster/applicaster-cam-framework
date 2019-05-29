//
//  APFreewheelAdProvider.h
//  ApplicasterSDK
//
//  Created by Philip Kramarov on 1/8/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APAdProvider.h"

@protocol FWContext;

extern NSString *const kAPFreewheelAdSizeKey;

// Support Freewheel SDK version: 5.18.2

@interface APFreewheelAdProvider : APAdProvider

/**
 @param networkId network ID of the distributor.
 @param serverURL url of the FreeWheel Ad Server
 @param profileId id of the global profile
 @param siteSectionId id of the site section. Uses default value from the adProvider
 @return shared instance of APFreewheelAdProvider. Creating a second instance of that type will use the same variables as the first one.
 */
+ (instancetype)createProviderWithNetworkId:(NSUInteger)networkId
                                  serverURL:(NSString *)serverURL
                                  profileId:(NSString *)profileId
                              siteSectionId:(NSString *)siteSectionId;

/**
 Create context.
 @return The new context set with default playerProfile and site section (CMS adProvider)
 */
+ (id<FWContext>)getNewContext;

@end
