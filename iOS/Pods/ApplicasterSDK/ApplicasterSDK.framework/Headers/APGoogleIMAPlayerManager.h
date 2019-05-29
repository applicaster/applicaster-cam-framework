//
//  APGoogleIMAPlayerManager.h
//  Applicaster App
//
//  Created by Philip Kramarov on 5/21/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

@class APPlayerViewController;
@interface APGoogleIMAPlayerManager : NSObject

/**
*  Plays google ima vast ad on top of the player view controller.
*
*  @param adTagURL             VAST IMA adUrl
*  @param playerViewController Applicaster player view controller that contains avplayer.
*  @param completion           completion block that will called in the following cases:
*  preroll or postroll finised and if the playlist (postroll) finished.
*/
- (void)playIMAWithAdTagURL:(NSString *)adTagURL
       playerViewController:(APPlayerViewController *)playerViewController
          completionHandler:(void (^)(BOOL success, BOOL canceled, NSDictionary *analyticParameters))completion;

/**
 *  Setup playlist that listen to time events of the player.
 *  Playlist maycontain VAST of Prerolls, Midrolls, Postrolls, each VAST may conatin multiple number of ads.
 *
 *  @param adTagURL             VAST IMA adUrl
 *  @param playerViewController Applicaster player view controller that contains avplayer.
 */
- (void)setupIMAPlaylistAdTagURL:(NSString *)adTagURL
        withPlayerViewController:(APPlayerViewController *)playerViewController
               completionHandler:(void (^)(BOOL success, BOOL canceled, NSDictionary *analyticParameters))completion;

/**
 *  Reflects if the ad in pressent on screen,
 */
@property (nonatomic, assign, readonly) BOOL hasOnScreenAd;

@end
