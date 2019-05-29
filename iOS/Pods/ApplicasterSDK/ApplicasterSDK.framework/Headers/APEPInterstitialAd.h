//
//  APEPInterstitialAd.h
//  ApplicasterCore
//
//  Created by Philip Kramarov on 5/27/15.
//  Copyright (c) 2015 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface APEPInterstitialAd : NSObject

+ (instancetype)interstitialAdWithPlacementId:(NSString *)placementId;

- (void)presentWithRootViewController:(UIViewController *)rootViewController
                    completionHandler:(void (^)(BOOL success))completion;

@end
