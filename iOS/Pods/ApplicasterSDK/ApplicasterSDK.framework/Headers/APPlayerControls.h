//
//  APPlayerControls.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/8/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APPlayerConstants.h"

@import MediaPlayer;

@class TTTAttributedLabel;
@class MPVolumeView;
@class APSlider;
#define kDefaultControlsHeight 40.0

@class APPlayer;

static NSString *const kAPPlayerControlsPlayingItemIsLive               = @"kAPPlayerControlsPlayingItemIsLive";
static NSString *const kAPPlayerControlsPlayingItemUniqueID             = @"kAPPlayerControlsPlayingItemUniqueID";
static NSString *const kAPPlayerControlsPlayingItemName                 = @"kAPPlayerControlsPlayingItemName";
static NSString *const kAPPlayerControlsPlayingItemDescription          = @"kAPPlayerControlsPlayingItemDescription";
static NSString *const kAPPlayerControlsPlayingItemUITag                = @"kAPPlayerControlsPlayingItemUITag";
static NSString *const kAPPlayerControlsPlayingItemPublicPage           = @"kAPPlayerControlsPlayingItemPublicPage";
static NSString *const kAPPlayerControlsPlayingItemIsCommentsEnabled    = @"kAPPlayerControlsPlayingItemIsCommentsEnabled";

/**
 Player controls protocol.
 A view must conform to this protocol in order to be used as the player controls.
 */
@protocol APPlayerControls <NSObject>

@required

/**
 Shows the controls.
 @param animated - If set to YES will animate the show action.
 */
- (void)show:(BOOL)animated;

/**
 Hides the controls.
 @param animated - If set to YES will animate the hide action.
 */
- (void)hide:(BOOL)animated;

/**
 Checks the controls visibility.
 @return YES when controls are visible, NO otherwise.
 */
- (BOOL)isVisible;

/**
 Called when the player changes its playback state.
 @param playing - YES when player is playing, NO when not.
 */
- (void)setPlaying:(BOOL)playing;

/**
 returns a time interval of the initial delay in hiding the controls at video player start
 */
- (NSTimeInterval)initialPlayerControlsHideDelay;


@optional

/**
 The controls pause button.
 The player will use this property in order to attach it to a pause selector.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *pauseButton;

/**
 The controls pause button.
 The player will use this property in order to attach it to a play selector.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *playButton;

/**
 The slider used to seek within the stream.
 */
@property (nonatomic, readonly, weak) IBOutlet APSlider *seekSlider;

/**
 Stop button.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *stopButton;

/**
 Back button.
 Enabled when player is playing a playlist.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *backButton;

/**
 Forward button.
 Enabled when player is playing a playlist.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *forwardButton;

/**
 Record button for Share a Moment
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *recordButton;

/**
 Record Time image view for Share a Moment.
 */
@property (nonatomic, readonly, weak) IBOutlet UIImageView *recordTimeBackgroundImageView;

/**
 Record Time label of share a Moment.
 */
@property (nonatomic, readonly, weak) IBOutlet UILabel *recordTimeLabel;

/**
 Expand button.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *expandButton;

/**
 Shrink button.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *shrinkButton;

/**
 A button for alternating between aspect fill and aspect fit.
 */
@property (nonatomic, readonly, weak) IBOutlet UIButton *scalingModeButton;

/** The button that toggles Facebook comments being shown/hidden. */
@property (nonatomic, readonly, weak) IBOutlet UIButton *facebookCommentsButton;

/**
 Label which shown when user is scrubbing. Text is change due to the height of the tap on the screen corresponding the scrubbing speeds (mimics apple native player)
 */

@property (nonatomic, weak) IBOutlet TTTAttributedLabel *scrubbingLabel;


@property (nonatomic, weak) IBOutlet MPVolumeView *volumeView;
  
/**
 Signals to the controls that the buffering has started or stopped.
 @param buffering - Is buffering on or off.
 */
- (void)setBuffering:(BOOL)buffering;

/**
 Used by the player to set the duration.
 @param duration - The target duration to show.
 */
- (void)setDuration:(NSTimeInterval)duration;

/**
 Used by the player to set the current time.
 @param currentTime - The target current time to show.
 */
- (void)setCurrentTime:(NSTimeInterval)currentTime;

/**
 Informs the controls that the scaling mode has changed.
 @param scalingMode The new scaling mode of the video.
 */
- (void)setScalingMode:(APMovieScalingMode)scalingMode;

/**
 Informs the player controls that the Content video part will start playing.
 This can be used to better time analytics, or post watch events for example
 */
- (void)videoContentDidStartPlaying;

/**
 Informs the player controls that the Content video part will start playing.
 This can be used to better time analytics, or post watch events for example.
 You may use this method to reset your controls according to the current playing item.
 */
- (void)videoContentDidStartPlayingWithItem:(NSDictionary *)playingItemInfo;

/**
 Updates the controls to live or not live (vodItem) layout.
 Live player will not show seek bar and timer label.
 @param isLive the state of the playable item that is presented in the player.
 */
-(void)updateControlsForLiveState:(BOOL)isLive;

@end

