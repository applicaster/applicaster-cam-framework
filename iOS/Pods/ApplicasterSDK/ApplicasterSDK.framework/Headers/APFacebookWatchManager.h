//
//  APFacebookWatchManager.h
//  applicaster
//
//  Created by Hagit Shemer on 10/15/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//  Facebook Watch feature documentaion: https://developers.facebook.com/docs/opengraph/guides/video.watches/#bestpractices
//

#import <Foundation/Foundation.h>

@interface APFacebookWatchManager : NSObject

/**
 Set this label to be the label that will be animated when performing watch action. Leave nil if you will handle it yourself.
 */
@property (nonatomic, unsafe_unretained) UILabel *watchToastLabel;

/**
 Set this button to be the watchButton you define in your controls.
 */
@property (nonatomic, unsafe_unretained) UIButton *watchButton;

//---------------------------------------------------- MUST be called methods ------------------------------------------//

- (id)initWithWatchButton:(UIButton *)watchButton
       andWatchToastLabel:(UILabel *)watchToastLabel;

/**
 call when the user switches off the watch button
 @param currentItemPublicPage - video public page url
 @param expiresInSeconds - "specify the length of a movie in seconds"
 **/
- (void)startWatchForVodWithPublicPage:(NSString *)vodPublicPage
                       vodLengthInSecs:(NSUInteger)vodLengthSeconds;

/**
 Call this method when the user exits the player or when the playback ended.
 @param playedPercentage - current playback time.
 **/
- (void)finishedPlayingItemWithPlayedPercentage:(CGFloat)playedPercentage;

//---------------------------------------------------- available for overriding ------------------------------------------//

/**
 This method animating watch toast label on screen.
 */
- (void)animateToast;

@end
