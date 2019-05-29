//
//  APApplicasterBannerView.h
//  applicaster
//
//  Created by Guy Kogus on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "APBannerView.h"

@class APAdvertiser;

/**
 This is the APBannerView subclass defined in the Applicaster CMS. This will traverse the local banners defined in the <APAdvertiser> to show them according to the timing defined in the <APAdvertiser>. If all of the local banners fail to load, the banner view will call <bannerView:didFailToReceiveAdWithError:>.
 */
@interface APApplicasterBannerView : APBannerView

/**
 Initialise using a given <APAdvertiser>. The advertiser will use its local banners for showing different banners on each call to <showNextAd>.
 @param advertise The <APAdvertiser> object used for defining the local banners.
 @return The initialised Applicaster banner view.
 */
- (id)initWithAdvertiser:(APAdvertiser *)advertiser;

@end
