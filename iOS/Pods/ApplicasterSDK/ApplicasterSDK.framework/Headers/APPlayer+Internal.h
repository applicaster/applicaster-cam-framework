//
//  APPlayer+Internal.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/4/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <AVFoundation/AVPlayerItem.h>
#import "APStateMachine.h"

static NSString *const kPlaybackStateStopped = @"PlaybackStateStopped";
static NSString *const kPlaybackStatePlaying = @"PlaybackStatePlaying";
static NSString *const kPlaybackStatePaused = @"PlaybackStatePaused";
static NSString *const kPlaybackStateManualSeek = @"PlaybackStateManualSeek";

static NSString *const kEventPlaybackStop = @"EventPlaybackStop";
static NSString *const kEventPlaybackPlay = @"EventPlaybackPlay";
static NSString *const kEventPlaybackPause = @"EventPlaybackPause";
static NSString *const kEventPlaybackSeekManually = @"EventPlaybackSeekManually";

@interface APPlayer (Internal) <APStateMachineDelegate>

/**
 Playback state machine.
 */
@property (nonatomic, readonly) APStateMachine *playbackStateMachine;

/**
 Adds all required observation for the player.
 @param player - The target player
 */
- (void)observePlayer:(AVPlayer*)player;

/**
 Removes all of the player related observations.
 @param player - The target player
 */
- (void)stopObservingPlayer:(AVPlayer*)player;

/**
 Called when an item is going to be played and should be observed.
 @param item The target item to observe.
 */
- (void)observeItem:(AVPlayerItem*)item;

/**
 Called when it is no longer necessary to observe an item.
 @param item The target item to stop observing.
 */
- (void)stopObservingItem:(AVPlayerItem*)item;

/**
 Called when the current item reachs end of playback naturally.
 */
- (void)itemDidPlayToEnd:(NSNotification*)notif;

/**
 Called when the current item fails to play to the end.
 */
- (void)itemFailedToPlayToEnd:(NSNotification*)notif;

/**
 The default controls to show when not manually set.
 */
@property (nonatomic, readonly) UIView<APPlayerControls> *defaultControls;

/**
 Start listening to controls generated messages.
 @param controls - The target controls.
 */
- (void)observeControls:(UIView<APPlayerControls> *)controls;

/**
 Stop listening to controls generated messages.
 @param controls - The target controls.
 */
- (void)stopObservingControls:(UIView<APPlayerControls> *)controls;

/**
 Called when the controls play button is tapped.
 @param sender - The message sender (play button).
 */
- (void)controlsPlayButtonTapped:(id)sender;

/**
 Called when the controls pause button is tapped.
 @param sender - The message sender (pause button).
 */
- (void)controlsPauseButtonTapped:(id)sender;

/**
 Called when the controls stop button is tapped.
 @param sender - The message sender (stop button).
 */
- (void)controlsStopButtonTapped:(id)sender;

/**
 Called when the control slider value change.
 @param sender - The slider.
 */
- (void)controlsSliderValueChanged:(id)sender;

/**
 Called when the control sliderchange starts.
 @param sender - The slider.
 */
- (void)controlsSliderChangeStarted:(id)sender;

/**
 Called when the control sliderchange ends.
 @param sender - The slider.
 */
- (void)controlsSliderChangeEnded:(id)sender;

/**
 Updates the necessary values with new duration.
 Calls <code>updateDurationWithInterval</code>
 */
- (void)updateDurationWithTime:(CMTime)time;

/**
 Updates the necessary values with new duration. 
 */
- (void)updateDurationWithInterval:(NSTimeInterval)timeInterval;

//Playback observation
- (void)startObservingCurrentTime;  /**< Start observing time to update seek */
- (void)stopObservingCurrentTime;   /**< Stops observing current time */

@end
