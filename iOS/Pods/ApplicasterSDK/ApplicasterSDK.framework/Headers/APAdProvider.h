//
//  APAdProvider.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 14/03/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APBannerView;
@protocol APBannerViewDelegate;

/**
 The APADProvider protocol is to be used by the different ad providers required for creating banners.
 */
@interface APAdProvider : NSObject

/** The time used to refresh banners. */
@property (nonatomic, assign) NSTimeInterval bannerRefreshRate;

/** The parameters of the ad provider */
@property (nonatomic, strong) NSDictionary *parameters;

/**
 Creates a new ad banner view. See <APBannerView> for a description of the type of banner view returned.
 @param delegate Similar to the ADBannerViewDelegate, the <APBannerViewDelegate> responds to changes/updates to the banner view.
 @return The newly created ad banner view. This should be a subclass of APBannerView, since APBannerView should be treated as an abstract class.
 */
- (APBannerView *)adBannerWithDelegate:(id <APBannerViewDelegate>)delegate;

@end
