//
//  APGoogleBannerView.h
//  ApplicasterSDK
//
//  Created by Philip Kramarov on 1/15/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import "APBannerView.h"
#import "APGoogleAdsBannerType.h"

/**
 Contains a Google ad.
 */
@interface APGoogleBannerView : APBannerView

/**
 Create an ad with ad unit ID.
 @param adUnitID The ad unit ID.
 @param bannerType The type of google ad
 @return The new ad that will load the Google ad on <setBannerSizeAccordingToInterfaceOrientation:>.
 */
- (id)initWithAdUnitID:(NSString *)adUnitID bannerType:(APGoogleAdsBannerType)bannerType;

@end
