//
//  APBannerViewController.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 24/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APAdProvider.h"

/** This notification is sent when a banner is pressed. If used for analytics, the <code>userInfo</code> contains the analytics parameters. */
extern NSString *const APBannerViewControllerBannerPressedNotification;

@class APBannerViewController;

/**
 The delegate of an <APBannerViewController> only needs to know when to show/hide the banner.
 */
@protocol APBannerViewControllerDelegate <NSObject>
@optional

/**
 Asks the parameters for the banner view controller, allows customization for the banners.
 @param bannerViewController The controller of the banner view that needs to be displayed
 @return The parameters for the banner view. Banners that require specific parameters should define their own keys for public usage. @see APBannerView
 */
- (NSDictionary *)bannerViewControllerParameters:(APBannerViewController *)bannerViewController;


/**
 Show the banner. The <code>bannerViewController</code>'s view can be used to retrieve the required size.
 @param bannerViewController The controller of the banner view that needs to be displayed.
 */
- (void)bannerViewControllerExpose:(APBannerViewController *)bannerViewController;

/**
 Hide the banner. The <code>bannerViewController</code>'s view can be used to retrieve the required size.
 @param bannerViewController The controller of the banner view that needs to be hidden.
 */
- (void)bannerViewControllerHide:(APBannerViewController *)bannerViewController;

/*
 Will be called if no ads were found for all the ad providers.
 This method give you a chance to hide your banner container for example, or to show a placeholder.
 */
-(void)bannerViewControllerNoAdsToShow:(APBannerViewController *)bannerViewController;

/**
 Called before a banner view executes an action.
 
 This method is called when the user taps the banner view. Your application controls whether the action is triggered. To allow the action to be triggered, return YES. To suppress the action, return NO. Your application should almost always allow actions to be triggered; preventing actions may alter the advertisements your application sees and reduce the revenue your application earns through iAd.
 
 If the willLeave parameter is YES, then your application is moved to the background shortly after this method returns. In this situation, your method implementation does not need to perform additional work. If willLeave is set to NO, then the triggered action will cover your application’s user interface to show the advertising action. Although your application continues to run normally, your implementation of this method should disable activities that require user interaction while the action is executing. For example, a game might pause its game play until the user finishes watching the advertisement.
 @param bannerViewController The banner view that the user tapped.
 @param willLeave YES if another application will be launched to execute the action; NO if the action is going to be executed inside your application.
 @return Your delegate returns YES if the banner action should execute; NO to prevent the banner action from executing.
 */
- (BOOL)bannerViewControllerActionShouldBegin:(APBannerViewController *)bannerViewController
						 willLeaveApplication:(BOOL)willLeave;

/**
 Called after a banner view finishes executing an action that covered your application’s user interface.
 
 If your delegate paused activities before allowing an action to run, it should resume those activities when this method is called.
 @param bannerViewController The banner view that finished executing an action.
 */
- (void)bannerViewControllerActionDidFinish:(APBannerViewController *)bannerViewController;

@end

/**
 This view controller is not designed to be used as a UIViewController. It is meant to control a view that will handle rotating through the potential views provided by a list of ad providers.
 */
@interface APBannerViewController : NSObject

/** The container view for the banners retrieved by the ad providers. */
@property (nonatomic, readonly, strong) UIView *view;
/** The delegate for the view controller, which only needs to be told when to show and when to hide the banner. */
@property (nonatomic, weak) id <APBannerViewControllerDelegate> delegate;
/** Checks the internal banner view to see if it is loaded yet. */
@property (nonatomic, assign, readonly, getter = isBannerLoaded) BOOL bannerLoaded;
/** The current ad provider. */
@property (nonatomic, strong, readonly) APAdProvider *currentAdProvider;

/**
 If set to YES, the banner view controller will display an ad for the set exposure time and hide it for the set delay time.
 The default is NO, which means that after the exposure time the next ad is displayed and the delay time is ignored.
 */
@property (nonatomic, unsafe_unretained) BOOL hidesBannerView;
/** The interface orientations that will be used for banners. This is mainly required for iAds. */
@property (nonatomic, unsafe_unretained) UIInterfaceOrientationMask requiredInterfaceOrientations;
/** The current interface orientation. This lets the banners know which banner sizes to return. */
@property (nonatomic, unsafe_unretained) UIInterfaceOrientation currentInterfaceOrientation;

/**
 Initialises a banner view controller with the required parameters.
 
 The ad providers give the order of preference for ads. If the first ad provider succeeds, then only its ads will be used. If it fails, the next ad provider will be used, and so on until an ad provider succeeds.
 
 @param adProviders An array of <b>classes</b> that conform to <APAdProvider>. The ad providers are sorted in order of preference.
 @param requiredInterfaceOrientations A bit-mask of the required orientations for the banner. See <APInterfaceOrientations>.
 @param currentInterfaceOrientation The current interface orientation for the banners presented in the banner view controller.
 @param rootViewController - The rootViewController used to present the in-app brawser when pressing the ad. (usually self)
 
 @return The initialised banner view controller.
 */
- (id)initWithBannerProviders:(NSArray *)adProviders
	  forRequiredOrientations:(UIInterfaceOrientationMask)requiredInterfaceOrientations
		   currentOrientation:(UIInterfaceOrientation)currentInterfaceOrientation
           rootViewController:(UIViewController *)rootViewController;
/**
 Initialises a banner view controller with the required parameters.
 
 The ad providers give the order of preference for ads. If the first ad provider succeeds, then only its ads will be used. If it fails, the next ad provider will be used, and so on until an ad provider succeeds.
 
 @param adProviders An array of <b>classes</b> that conform to <APAdProvider>. The ad providers are sorted in order of preference.
 @param requiredInterfaceOrientations A bit-mask of the required orientations for the banner. See <APInterfaceOrientations>.
 @param currentInterfaceOrientation The current interface orientation for the banners presented in the banner view controller.
 @param rootViewController - The rootViewController used to present the in-app brawser when pressing the ad. (usually self)
 @param delegate The delegate of APBannerViewControllerDelegate protocol.
 
 @return The initialised banner view controller.
 */
- (id)initWithBannerProviders:(NSArray *)adProviders
	  forRequiredOrientations:(UIInterfaceOrientationMask)requiredInterfaceOrientations
		   currentOrientation:(UIInterfaceOrientation)currentInterfaceOrientation
           rootViewController:(UIViewController *)rootViewController
                  andDelegate:(id<APBannerViewControllerDelegate>)delegate;

/**
 This method allows passing in custom parameters for different banner types. For example, different Moblin banners may want to pass in a different zone.
 @param parameters See <APBannerView/setParameters:>
 */
- (void)setBannerParameters:(NSDictionary *)parameters;

/**
 Refreshes the current banner. This is necessary for when a view controller re-appears and it's banner has been stolen by another superview.
 */
- (void)refreshBanner;

/**
 Reloads the current banner. This method can be implemented be any bannerView in order to invoke new banner request.
 This method resets the current ad provider to be the default (first ad provider).
 */
- (void)reloadBanner;

/**
 Returns an APBannerViewController initialised using the <initWithBannerProviders:exposureTime:delayTime:> method.
 
 The ad providers give the order of preference for ads. If the first ad provider succeeds, then only its ads will be used. If it fails, the next ad provider will be used, and so on until an ad provider succeeds.
 
 @param adProviders An array of <b>classes</b> that conform to <APAdProvider>. The ad providers are sorted in order of preference.
 @param requiredInterfaceOrientations A bit-mask of the required orientations for the banner. See <APInterfaceOrientations>.
 @param currentInterfaceOrientation The current interface orientation for the banners presented in the banner view controller.
 @param rootViewController - The rootViewController used to present the in-app brawser when pressing the ad. (usually self)
 
 @return The initialised banner view controller.
 */
+ (instancetype)bannerViewControllerWithBannerProviders:(NSArray *)adProviders
								forRequiredOrientations:(UIInterfaceOrientationMask)requiredInterfaceOrientations
									 currentOrientation:(UIInterfaceOrientation)currentInterfaceOrientation
                                     rootViewController:(UIViewController *)rootViewController;

@end
