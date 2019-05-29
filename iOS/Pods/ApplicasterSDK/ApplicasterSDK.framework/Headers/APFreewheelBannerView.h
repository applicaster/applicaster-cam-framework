//
//  APFreewheelBannerView.h
//  ApplicasterCore
//
//  Created by Philip Kramarov on 1/8/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APBannerView.h"

@protocol FWContext;

@interface APFreewheelBannerView : APBannerView

- (instancetype)initWithAdContext:(id<FWContext>)adContext;

@end
