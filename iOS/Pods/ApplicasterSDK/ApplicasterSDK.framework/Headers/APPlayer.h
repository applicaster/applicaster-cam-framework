//
//  APPlayer.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 12/27/11.
//  Copyright (c) 2011 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APPlayerConstants.h"
#import "APMediaPlayback.h"

@class AVPlayer;
@protocol APPlayerControls;

// Basic Player Notifications:
extern NSString *const APPlayerItemDidPlayToEndTimeNotification;    // Posted when the player finish playing an item.
extern NSString *const APPlayerDidPlayNotification;                 // Posted when player's play method is called.
extern NSString *const APPlayerDidPauseNotification;                // Posted when player's pause method is called.
extern NSString *const APPlayerDidStopNotification;                 // Posted when stop was called.
extern NSString *const APPlayerWasCreatedNotification;              // Posted when the player is created.
extern NSString *const APPlayerWasDestroyedNotification;              // Posted when the player is destroyed.

extern NSString *const APMoviePlayerLoadStateDidChangeNotification;     /**< Posted when the load state changes */
extern NSString *const APMoviePlayerPlaybackStateDidChangeNotification; /**< Posted when the playback state changes */
extern NSString *const APPlayerDidPlayToEndTimeNotification;            /**< Posted when the player reachs the end of playback. */
extern NSString *const APPlayerFailedToPlayToEndTimeNotification;       /**< Posted when the player fails to reach the end of playback. */
extern NSString *const APPlayerDurationAvailableNotification;           /**< Posted when duration is available. */
extern NSString *const APPlayerHideControNotification;                  /**< Posted when hiding player controls. */
extern NSString *const APPlayerShowControNotification;                  /**< Posted when showing player controls. */

extern NSString *const kAVPlayerWasCreated;             /**< Posted after the _player is created */
extern NSString *const kAVPlayerPlaybackCompleted;      /**< Posted after the _player is dealloced */
extern NSString *const kPlayerSeekStarted;              /**< Posted when the user starts to drag the slider */
extern NSString *const kPlayerSeekEnded;                /**< Posted when the user finished to drag the slider */

extern NSString *const kControlsPlayButtonTapped;       /**< Posted after the controls' play button is pressed */
extern NSString *const kControlsPauseButtonTapped;      /**< Posted after the controls' pause button is pressed */
extern NSString *const kControlsStopButtonTapped;       /**< Posted after the controls' stop button is pressed */

/**< The key in which _player is stored in the notification's userInfo
 (relevant for kAVPlayerWasCreated, kAVPlayerPlaybackCompleted, kPlayerSeekStarted and kPlayerSeekEnded notifications) */
extern NSString *const kAVPlayerKey;

/**
 The core player object.
 Wrapper for the AVPlayer.
 */
@interface APPlayer : NSObject <APMediaPlayback>{
    UIView              *_view;
    NSURL               *_contentURL;
    BOOL                _shouldAutoPlay;
    APMovieScalingMode  _scalingMode;
    APMovieLoadState    _loadState;
    UIView<APPlayerControls>    *_controls;
    BOOL                        _shouldShowControls;
    APPlayerActionAtItemEnd     _actionAtItemEnd;
    BOOL                        _isVideoAvailable;
    NSTimeInterval              _currentItemDuration;       /**< Current item duration */
}

/**
 The player object.
 */
@property (nonatomic, strong) AVPlayer *player;

/**
 Returns A <code>APPlayer</code> object initialized with the movie at the specified URL.
 @param url The location of the movie file. This file must be located either in your application directory or on a remote server
 */
- (id)initWithContentURL:(NSURL *)url;

/**
 The URL that points to the movie file.
 If you set this property while a movie is playing, that movie pauses and the new movie begins loading. The new movie starts playing at the beginning.`
 */
@property(nonatomic, copy) NSURL *contentURL;

/**
 The player view.
 Add this view into your views heirarchy and set it's size to the desired size.
 */
@property (nonatomic, readonly) UIView *view;

/**
 A Boolean that indicates whether a movie should begin playback automatically.
 The default value of this property is YES. This property determines whether the playback of network-based content begins automatically when there is enough buffered data to ensure uninterrupted playback.
 */
@property (nonatomic, assign) BOOL shouldAutoPlay;

/**
 The scaling mode to use when displaying the movie.
 Default scaling mode is aspect fit.
 */
@property (nonatomic, assign) APMovieScalingMode scalingMode;

/**
 The current playback state of the movie player.
 */
@property (nonatomic, readonly) APMoviePlaybackState playbackState;

/**
 Communication load state concerning the content URL.
 */
@property (nonatomic, readonly) APMovieLoadState loadState;

/**
 The duration of the current item in seconds.
 */
@property (nonatomic, readonly) NSTimeInterval duration;

/**
 Type of the playback duration.
 */
@property (nonatomic, readonly) APPlayerContentDurationType durationType;

/**
 When set to yes - Enables airplay.
 Default value is NO.
 */
@property (nonatomic, assign) BOOL allowsAirPlay;

/**
 Prepares a player with the desired URL.
 Notice that if the <code>contentURL</code> property was not set, the method will do nothing.
 */
- (void)prepareToPlay;

/**
 Player controls.
 A view that confiorms to the <code>APPlayerControls</code> protocol.
 If not set, uses a default controls supplied by the player.
 Once you've set your controls, add them to the player heirarchy if you wish to.
 */
@property (nonatomic, retain) UIView<APPlayerControls> *controls;

/**
 Determins weather the controls are visible or not.
 Setting to NO will hide the controls, setting YES will show the controls.
 Default value is YES.
 */
@property (nonatomic, assign) BOOL shouldShowControls;

/**
 Action taken when the current item ends.
 */
@property (nonatomic, assign) APPlayerActionAtItemEnd actionAtItemEnd;

/**
 A view displayed when no video is available.
 */
@property (nonatomic, retain) UIView *audioOnlyView;

/**
 The default audio only view to show if one isn't received from the server.
 */
@property (nonatomic, retain) UIView *defaultAudioOnlyView;

/**
 @return The default scaling mode.
 */
+ (APMovieScalingMode)defaultScalingMode;

/**
 Sets the default scaling mode.
 */
+ (void)setDefaultScalingMode:(APMovieScalingMode)scalingMode;

/**
 Playback rate.
 */
@property (nonatomic, readonly) float rate;

/**
 Shows the controls.
 The controls will be hidden automatically.
 */
- (void)showControls;

/**
 Changes the current playback time of the player.
 @param currentPlaybackTime The second of the wanted playback time
 @param shouldPlay The state of the player after the playback time change
 */
- (void)setCurrentPlaybackTime:(NSTimeInterval)currentPlaybackTime shouldPlay:(BOOL)shouldPlay;

//Controls
- (void)cancelControlsHideTimer;    /**< Cancels the hide timer */
- (void)autoShowHideControls;       /**< Shows the controls and then hides them automatically */
- (void)hideControls;               /**< Hides the controls */

@end
