//
//  APGoogleAdProvider.h
//  ApplicasterSDK
//
//  Created by Philip Kramarov on 1/15/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import "APAdProvider.h"
#import "APGoogleAdsBannerType.h"

/**
 This ad provider creates Google ads.
 */
@interface APGoogleAdProvider : APAdProvider

/**
 The ad unit ID provided by Google. 
 Example values for different request types:
 AdMob: a0123456789ABCD
 DFP: /0123/ca-pub-0123456789012345/my-ad-identifier
 */
@property (nonatomic, copy) NSString *adUnitID;

/**
 Google banner type.
 @see APGoogleAdsBannerType
 */
@property (nonatomic, assign) APGoogleAdsBannerType bannerType;

/**
 Creates a new instance of the ad provider with the given ad unit ID.
 @param adUnitID See <adUnitID>.
 @param bannerType @see APGoogleAdsBannerType
 @return The new ad provider using the initial ad unit ID.
 */
- (instancetype)initWithAdUnitID:(NSString *)adUnitID bannerType:(APGoogleAdsBannerType)bannerType;

@end
