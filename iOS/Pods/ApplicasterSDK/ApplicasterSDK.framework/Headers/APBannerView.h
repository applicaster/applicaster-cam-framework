//
//  APBannerView.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 23/01/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APBannerView;

/**
 The APBannerViewDelegate protocol is implemented by an object to react to changes in an APBannerView object. The banner view calls its delegate when a new advertisement is loaded, when the user interacts with an advertisement, and when errors occur.
 */
@protocol APBannerViewDelegate <NSObject>
@optional

/**
 Called when a new banner advertisement is loaded.
 @param banner The banner view that loaded a new advertisement.
 */
- (void)bannerViewDidLoadAd:(APBannerView *)banner;

/**
 Called before a banner view executes an action.
 
 This method is called when the user taps the banner view. Your application controls whether the action is triggered. To allow the action to be triggered, return YES. To suppress the action, return NO. Your application should almost always allow actions to be triggered; preventing actions may alter the advertisements your application sees and reduce the revenue your application earns through iAd.
 
 If the willLeave parameter is YES, then your application is moved to the background shortly after this method returns. In this situation, your method implementation does not need to perform additional work. If willLeave is set to NO, then the triggered action will cover your application’s user interface to show the advertising action. Although your application continues to run normally, your implementation of this method should disable activities that require user interaction while the action is executing. For example, a game might pause its game play until the user finishes watching the advertisement.
 @param banner The banner view that the user tapped.
 @param willLeave YES if another application will be launched to execute the action; NO if the action is going to be executed inside your application.
 @return Your delegate returns YES if the banner action should execute; NO to prevent the banner action from executing.
 */
- (BOOL)bannerViewActionShouldBegin:(APBannerView *)banner willLeaveApplication:(BOOL)willLeave;

/**
 Called after a banner view finishes executing an action that covered your application’s user interface.
 
 If your delegate paused activities before allowing an action to run, it should resume those activities when this method is called.
 @param banner The banner view that finished executing an action.
 */
- (void)bannerViewActionDidFinish:(APBannerView *)banner;

/**
 Called when a banner view fails to load a new advertisement.
 @param banner The banner view that failed to load an advertisement.
 @param error The error object that describes the problem.
 */
- (void)bannerView:(APBannerView *)banner didFailToReceiveAdWithError:(NSError *)error;

@end

/**
 The APBannerView is designed to be used as a container view for banners provided by <APAdProvider>s. The APBannerView is designed to be an abstract class and should never be created directly. It will instead be created by the <APAdProvider>s.
 */
@interface APBannerView : UIView

/** The delegate is designed to behave very much like the iAd banner's delegate. It allows it's delegate to be informed of updates/actions related to the banner. */
@property (nonatomic, unsafe_unretained) id <APBannerViewDelegate> delegate;
/** If an ad is loaded in the banner, this is YES. Otherwise this returns NO. */
@property (nonatomic, readonly, getter = isBannerLoaded) BOOL bannerLoaded;
/** The time used to refresh banners. */
@property (nonatomic, assign) NSTimeInterval bannerRefreshRate;

/** The rootViewController used to present the in-app brawser when pressing the ad */
@property (nonatomic, unsafe_unretained) UIViewController *rootViewController;

/**
 This lets the banner know what interface orientations will be required of it.
 
 Not all orientations need to be set. For example, only APInterfaceOrientationLandscapeLeft is required to create landscape banners. There is no need to add APInterfaceOrientationsLandscapeRight, too.
 @param interfaceOrientations The <APInterfaceOrientations> bitmask, indicating the required orientations.
 */
- (void)setRequiredBannerInterfaceOrientations:(UIInterfaceOrientationMask)interfaceOrientations;

/**
 This method allows the banner to resize its content according to the current interface orientation.
 @param orientation The new interface orientation.
 */
- (void)setBannerSizeAccordingToInterfaceOrientation:(UIInterfaceOrientation)orientation;

/**
 This method allows passing in custom parameters for different banner types. For example, different Moblin banners may want to pass in a different zone.
 @param parameters The parameters for the banner view. Banners that require specific parameters should define their own keys for public usage.
 */
- (void)setParameters:(NSDictionary *)parameters;

/**
 Inform the banner view that it needs to display the next advertisement from its ad provider.
 */
- (void)showNextAd;

/**
 Invoke the banner view that it needs to display a new banner or the reload the old one.
 */
- (void)reloadBanner;

/**
 This is the name of the type of banner that will be used for analytics.
 @return The analytics label for the banner's class.
 */
+ (NSString *)analyticsName;

@end
