//
//  APAdvertiser.h
//  applicaster
//
//  Created by Guy Kogus on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APModel.h"

extern NSString *const kAPAdProviderNameApplicaster;
//extern NSString *const kAPAdProviderNameJustAd;
extern NSString *const kAPAdProviderNameIads;
extern NSString *const kAPAdProviderNameZedo;
extern NSString *const kAPAdProviderNameCheckm8;
extern NSString *const kAPAdProviderNameDoubleClick;
extern NSString *const kAPAdProviderNameFreewheel;

//extern NSString *const APEnableJustAd;

extern NSString *const kAPBannerConfigURLIPhone;
extern NSString *const kAPBannerConfigURLIPad;

@class APAdProvider;
@class APBannerViewController;
//@class justAdView;

/**
 The APAdvertiser model is used to define the Applicaster advertisement mechanism. It is used to create banners using the list of given ad providers.
 */
@interface APAdvertiser : APModel

/**
 An array of classes that conform to the <APAdProvider> protocol. These providers will be used to provide the application with banners through a <APBannerViewController> object. See <bannerViewControllerForRequiredInterfaceOrientations:currentInterfaceOrientation:> for getting a banner view controller that will use these ad providers.
 */
@property (nonatomic, strong) NSArray *adProviders;
///** Keep a value to indicate whether or not justAds are enabled. */
//@property (nonatomic, assign) BOOL justAdEnabled;
/** The local (Applicaster) banners for this application. */
@property (nonatomic, strong, readonly) NSArray *localBanners;

/** The amount of time banners will be displayed during video playback. If <bannerDelayTime> is non-zero, the banners will be hidden after the exposure time. */
@property (nonatomic, assign) NSTimeInterval bannerExposureTime;

/** During video playback, this determines the amount of time to hide banners before showing the next one. */
@property (nonatomic, assign) NSTimeInterval bannerDelayTime;

/** The custom ad provider class MUST subclass <APCustomAdProvider>. */
@property (nonatomic, assign) Class customAdProviderClass;

/**
 Initialise the advertiser using the information received for the application-level ad providers.
 @param adProviders The array with the parameters for each advertiser type.
 @return The new Advertiser model.
 */
- (id)initWithAdProviders:(NSArray *)adProviders;

/**
 Get initial parameters for an ad provider.
 @param adProviderName See the constants defined in APAdvertiser.h
 @return The parameters for the ad provider, or nil if the ad provider was not found.
 */
- (NSDictionary *)paramsForAdProviderNamed:(NSString *)adProviderName;

/**
 Add an ad provider to the current list. This is best called once the account model has finished loading.
 @param adProvider The new ad provider.
 @param idx The index of the ad provider.
 */
- (void)insertAdProvider:(APAdProvider *)adProvider atIndex:(NSUInteger)idx;

/**
 This helper method creates a banner view controller using the advertiser's supplied ad providers.
 
 @param requiredOrientations A bitmask of the interface orientations that will be used for the banners supplied by the banner view controller.
 @param currentOrientation Let the banner view controller know what orientation to start in. This needs to be manually entered in case the app uses a different orientation requirement to the current orientation.
 @param rootViewController - The rootViewController used to present the in-app brawser when pressing the ad. (usually self)
 
 @return An autoreleased banner view controller.
 */
- (APBannerViewController *)bannerViewControllerForRequiredInterfaceOrientations:(UIInterfaceOrientationMask)requiredOrientations
													 currentInterfaceOrientation:(UIInterfaceOrientation)currentOrientation
                                                              rootViewController:(UIViewController *)rootViewController;

/**
 This helper method creates a banner view controller using the advertiser's supplied ad providers. It checks the root view controller to see what interface orientations are appropriate for the banner view controller.
 
 @param rootViewController - The rootViewController used to present the in-app brawser when pressing the ad. (usually self)
 
 @return An autoreleased banner view controller.
 */
- (APBannerViewController *)bannerViewController:(UIViewController *)rootViewController;

///**
// Returns a justAd rich media overlay view.
// @param frame The frame for the view.
// @return If the JustAd ad provider has been defined and given a rich media overlay URL, then an appropriate view will be returned. Else will return nil.
// */
//- (justAdView *)justAdRichMediaOverlayViewWithFrame:(CGRect)frame;

@end
