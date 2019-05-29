//
//  APPlayerCommercialsProtocol.h
//  applicaster
//
//  Created by Philip Kramarov on 5/19/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

@class APPlayerViewController;

typedef NS_ENUM(NSUInteger, APPlayerCommercialsType) {
    APPlayerCommercialsNone     = 0,
    APPlayerCommercialsPreroll  = (1 << 0),
    APPlayerCommercialsMidroll  = (1 << 1), // Better use playlist for displaying pre/post/midroll
    APPlayerCommercialsPostroll = (1 << 2),
    APPlayerCommercialsPlaylist = (1 << 3),
    APPlayerCommercialsInterstital = (1 << 4)
};

@protocol APPlayerCommercialsDelegate <NSObject>

@required
/**
 *  Defines the type of the player commercials that will be displayed
 *  @param playerViewController The player that requests the commercial ads.
 *  @return Type or types of commercials that should be displayed.
 */
- (APPlayerCommercialsType)playerCommercialsTypesForPlayerViewController:(APPlayerViewController *)playerViewController;

/**
 *  Displays commercials that were defined and presents them when needed.
 *  The ads are presented on top of the player view.
 *  @param playerCommercialsType The types of commercials ads that will be displayed.
 *  @param playerViewController  The player that requests the commercial ads.
 *  @param completion            When the commercial or playlist done displaying the ad/ads they call back completion with BOOL success or not.
 */
- (void)displayPlayerCommercialsType:(APPlayerCommercialsType)playerCommercialsType
                playerViewController:(APPlayerViewController *)playerViewController
                     completionBlock:(void (^)(BOOL success, BOOL canceled))completion;


/**
 *  Asks player commericals if they have on screen commerical, when we have a commercial
 *  pressented on screen the logic of the player should be different.
 *  @param playerViewController The player that requests the commercial ads.
 *  @return Is the commerical ad is displayed or not at any moment.
 */
- (BOOL)showsOnScreenInPlayerViewController:(APPlayerViewController *)playerViewController;


@optional

/**
 Defines the time points (second) when the video should present a midroll.
 @return List of points in the video (seconds) that the mid will be presented.
 */
- (NSArray *)midrollCommercialsTime:(APPlayerViewController *)playerViewController;

/**
 *  Postroll threshold percentage, when the video passed the required threshold
 *  percentage the postroll will be be presented.
 *
 *  @param playerViewController The player that requests the commercial ads.
 *
 *  @return Threshold percentage when present the postroll for the player
 */
- (CGFloat)postrollThresholdPercentageForPlayerViewController:(APPlayerViewController *)playerViewController;

@end
