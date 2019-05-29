//
//  APBannerFactory.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 30/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APBannerView.h"


@class APAdProvider;

/**
 The banner factory is a simple class that allows uses the ad providers to generate an <APBannerView> object.
 */
@interface APBannerFactory : NSObject

/**
 Creates a new ad banner view. See <APBannerView> for a description of the type of banner view returned.
 @param adProvider The <APAdProvider> that will create the banner.
 @param delegate Similar to the ADBannerViewDelegate, the <APBannerViewDelegate> responds to changes/updates to the banner view.
 @return The newly created ad banner view. This should be a subclass of APBannerView, since APBannerView should be treated as an abstract class.
 */
+ (APBannerView *)adBannerFromAdProvider:(APAdProvider *)adProvider forDelegate:(id <APBannerViewDelegate>)delegate;

@end
