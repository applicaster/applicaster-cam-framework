//
//  APGoogleInterstitialManager.h
//  Channel10
//
//  Created by Philip Kramarov on 1/21/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

@class GADRequestError;

@protocol APGoogleInterstitialManagerDelegate;

@interface APGoogleInterstitialManager : NSObject

/**
 This delegate allows to receive callbacks that are defined in the protocol @see APGoogleInterstitialManagerDelegate.
 */
@property (nonatomic, assign) id <APGoogleInterstitialManagerDelegate> interstitialDelegate;

/**
 Initiatator with the adUnitID.
 @param adUnitID - the id for the google ads - needed in order to get the ad.
*/
- (instancetype)initWithAdUnitID:(NSString *)adUnitID;

/**
 Loads and present the loaded ad (google ads)
 @param rootViewController The view controller to present the interstitial on if loaded.
 */
- (void)displayInRootViewController:(UIViewController *)rootViewController;

/**
 Loads and present the loaded ad (google ads)
 @param rootViewController The view controller to present the interstitial on if loaded.
 @param completion The handler that informs success or failure (whether the ad was presented successfully or not). The completion handler will be called whenever this viewController has finished to present.
 */
- (void)displayInRootViewController:(UIViewController *)rootViewController
               withCompletionHandler:(void (^)(BOOL success))completion;
@end


@protocol APGoogleInterstitialManagerDelegate <NSObject>

@optional

/**
 This method is called when the ad was dismissed from the screen.
 @param googleInterstitialManger - The google interstital manger that was pressented on screen and called this method.
 */
- (void)googleInterstitialMangerDidDismissScreen:(APGoogleInterstitialManager *)googleInterstitialManger;

/**
 This method is called when the googleInterstitialManger received the ad from google services.
 @param googleInterstitialManger - The google interstital manger that called this method.
 */
- (void)googleInterstitialMangerDidReceiveAd:(APGoogleInterstitialManager *)googleInterstitialManger;

/**
 This method is called when the googleInterstitialManger failed to receive the from google services.
 In order to get the correct error instance import the header GADRequestError.
 @param googleInterstitialManger - The google interstital manger that called this method.
 */
- (void)googleInterstitialManger:(APGoogleInterstitialManager *)googleInterstitialManger didFailToReceiveAdWithError:(GADRequestError *)error;


@end
