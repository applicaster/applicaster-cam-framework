//
//  APGoogleBannerStitialViewController.h
//
//  Created by Reuven Levitsky on 10/23/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@class GADRequestError;

@protocol APGoogleBannerStitialViewControllerDelegate;

typedef NS_ENUM(NSInteger, APGoogleBannerStitialViewControllerResult) {
    APGoogleBannerStitialViewControllerResultSuccess,
    APGoogleBannerStitialViewControllerResultFailure,
    APGoogleBannerStitialViewControllerResultCanceled
};

@interface APGoogleBannerStitialViewController : UIViewController

/**
 This delegate allows to receive callbacks that are defined in the protocol @see APGoogleInterstitialManagerDelegate.
 */
@property (nonatomic, weak) id <APGoogleBannerStitialViewControllerDelegate> interstitialDelegate;

/**
 Close button that closes the interstitial ViewController.
 */
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *closeButton;

/**
 The container which we add the bannerView into it.
 */
@property (unsafe_unretained, nonatomic) IBOutlet UIView *bannerContainer;

/**
 The size of the ad that should be presented. Defaults to bannerContainer's size. 
 Change this value before you call the presentation method.
 Doesn't have effect if being called after the presentation method.
 */
@property (unsafe_unretained, nonatomic) CGSize adSize;

/**
 In seconds.
 Set this value before loading the interstitial to auto close the ad after the given number of seconds.
 If 0, the ad will only be closed by the close button.
 */
@property (nonatomic, assign) NSTimeInterval exposureDuration;

/**
 Initiatator with the adUnitID.
 @param adUnitID - the id for the google ads - needed in order to get the ad.
*/
- (instancetype)initWithAdUnitID:(NSString *)adUnitID;

/**
 Loads and present the loaded ad (google ads). 
 The loaded ad will be removed animated frmo screen. In order to change this behaviour use (displayInRootViewController:withCompletionHandler) and dismiss this ViewController by yourself.
 @param rootViewController The view controller to present the interstitial on if loaded.
 */
- (void)displayInRootViewController:(UIViewController *)rootViewController;

/**
 Loads and present the loaded ad (google ads).
 If the given completion block is nil, this ViewController will be dismissed animated when finished displaying.
 If the given completion block is not nil, you MUST dismiss this ViewController by yourself in it.
 @param rootViewController The view controller to present the interstitial on if loaded.
 @param completion The handler that informs success or failure (whether the ad was presented successfully or not). The completion handler will be called whenever this viewController has finished to present.
 */
- (void)displayInRootViewController:(UIViewController *)rootViewController
               withCompletionHandler:(void (^)(APGoogleBannerStitialViewControllerResult result))completion;

/**
 Call this method in order to cancel the load of the ad. 
 After calling this method the completion block will be called with the result APGoogleBannerStitialViewControllerResultCanceled.
 */
- (void)cancelAdLoad;

@end


@protocol APGoogleBannerStitialViewControllerDelegate <NSObject>

@optional

/**
 This method is called when the ad was dismissed from the screen.
 @param googleBannerStitialViewController - The google interstital view controller that was pressented on screen and called this method.
 */
- (void)googleInterstitialMangerDidDismissScreen:(APGoogleBannerStitialViewController *)googleBannerStitialViewController;

/**
 This method is called when the googleInterstitialManger received the ad from google services.
 @param googleBannerStitialViewController - The google interstital view controller that called this method.
 */
- (void)googleInterstitialMangerDidReceiveAd:(APGoogleBannerStitialViewController *)googleBannerStitialViewController;

/**
 This method is called when the googleInterstitialManger failed to receive the from google services.
 In order to get the correct error instance import the header GADRequestError.
 @param googleBannerStitialViewController - The google interstital view controller that called this method.
 */
- (void)googleInterstitialManger:(APGoogleBannerStitialViewController *)googleBannerStitialViewController didFailToReceiveAdWithError:(GADRequestError *)error;


@end
