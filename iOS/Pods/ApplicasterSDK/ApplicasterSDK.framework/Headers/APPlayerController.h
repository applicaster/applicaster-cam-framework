//
//  APPlayerController.h
//  applicaster
//
//  Created by Tom Susel on 1/11/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "APMediaPlayback.h"
#import "APPlayerInterruptionView.h"
#import "APLoadingView.h"
#import "APPurchasableItem.h"
#import "APPlayable.h"
#import "APQueuePlayer.h"

@protocol APPlayerControls;

typedef enum {
    APPlayerControllerPhaseInitial,         /**< Initial phase before playback */
    APPlayerControllerPhaseLoading,         /**< Loading data for future playback */
    APPlayerControllerPhasePrerollSplash,   /**< Attempting to show the splash image before content playback */
    APPlayerControllerPhasePrerollVideo,    /**< Attempting to show the preroll video before the content playback */
    APPlayerControllerPhasePurchasing,      /**< Attempting to purchase the content */
    APPlayerControllerPhaseContent,         /**< Showing the main content */
    APPlayerControllerPhaseEnd,             /**< Player ended the playback */
    APPlayerControllerPhaseFailure,         /**< Player failed fatally */
} APPlayerControllerPhase;

/**
 A player controller.
 In charge of playing a playable item (vod or channel).
 */
@interface APPlayerController : NSObject <APMediaPlayback>{
    UIView<APLoadingView>                       *_loadingView;
    BOOL                                        _isLoading;
    UIView<APPlayerInterruptionViewProtocol>    *_interruptionView;
}

/**
 Creates a player controller instance.
 @param playable - The item to play.
 @returns An initialized player instance.
 */
- (id)initWithPlayableItem:(APPurchasableItem <APPlayable>*)playable;

/**
 Creates a player controller instance.
 @param playableItems - An array of items that conform to <code>APPlayable</code>.
 @returns An initialized player instance.
 */
- (id)initWithPlayableItems:(NSArray *)playableItems;

/**
 The player object used to render the video.
 */
@property (nonatomic, strong, readonly) APQueuePlayer *player;

/**
 The playable items in queue.
 Setting this value will stop current playback and induce playback attempt of the new array.
 */
@property (nonatomic, strong) NSArray *playableItems;

@property (nonatomic, strong, readonly) id<APPlayable> currentItem;   /**< The current item being processed. */

@property (nonatomic, assign) NSInteger currentItemIndex;           /**< Sets and gets the current item to play */

/**
 The player view.
 */
@property (nonatomic, strong, readonly) UIView *view;

/**
 A view that is displayed whenever the player is loading.
 By default shows a black view with a loading indicator at the center.
 */
@property (nonatomic, strong) UIView<APLoadingView> *loadingView;

@property (nonatomic, assign) APMovieScalingMode scalingMode;

/**
 Setable property to control overlay visability
 */
@property (nonatomic, assign) BOOL overlayHidden;

/**
 Turning on this property will not even create the default controls for the player
 */
@property (nonatomic, assign) BOOL shouldNotShowControls;

/**
 Performs some prefetching of data necessary to play.
 */
- (void)prepareToPlay;

/**
 Ends playback of the current item and initiates playback of the next item in the player’s queue.
 */
- (void)advanceToNextItem;

/**
Return dictionary with playing item information.
 */
- (NSDictionary *)playingItemInfo;
/**
 Player controls.
 A view that confiorms to the <code>APPlayerControls</code> protocol.
 If not set, uses a default controls supplied by the player.
 Once you've set your controls, add them to the player heirarchy if you wish to.
 */
@property (nonatomic, strong) UIView<APPlayerControls> *controls;

/**
 YES when player is loading, NO otherwise.
 */
@property (nonatomic, readonly) BOOL isLoading;

/**
 The current phase of the player controller.
 */
@property (nonatomic, readonly) APPlayerControllerPhase currentPhase;
/**
 indicates whether or not remove persistant resume
*/
@property (nonatomic, assign) BOOL shouldIgnoreInterruptScreen;

/**
 Checks that there are no players in the states Loading, Purchasing, Splash, Preroll, Content.
 @return YES if all the players are idle, NO otherwise.
 */
+ (BOOL)isIdle;

/**
 @returns YES when there is at least one player in a playback phase i.e. playing, preroll.
 */
+ (BOOL)isPlaying;

/**
 A view that is presented when the application resumes to be active.
 The view is presented after the application is interrupted.
 A default view is used. If set to nil no view will be shown and the player will resume upon becoming active.
 */
@property (nonatomic, strong) UIView<APPlayerInterruptionViewProtocol> *interruptionView;


/**
 @return The default scaling mode.
 */
+ (APMovieScalingMode)defaultScalingMode;

/**
 Sets the default scaling mode.
 @param scalingMode The scaling  mode.
 */
+ (void)setDefaultScalingMode:(APMovieScalingMode)scalingMode;

/**
 Returns YES when there is a player controller that is loading at the moment.
 */
+ (BOOL)isLoading;

/**
 Default audio only view setter.
 Will be used by each new player controller instance.
 @param audioOnlyView The view to be displayed when in audio-only mode.
 */
+ (void)setDefaultAudioOnlyView:(UIView*)audioOnlyView;

/**
 * Default player controls.
 * Each player instance will use these controls by default
 *  @return Returns setted default player controls instance. If wasn't set before returns standard applicaster's player default controls.
 */
+ (UIView<APPlayerControls> *)defaultPlayerControls;

/**
 Default player controls.
 Each player instance will use these controls by default, unless a default live controls are set and a live video begins playing.
 @param controls The default player controls.
 */
+ (void)setDefaultControls:(UIView<APPlayerControls> *)controls;

/**
 @param controls The default player controls to use for live videos. If this isn't present live videos will use the regular controls.
 */
+ (void)setDefaultSocialPlayerControls:(UIView<APPlayerControls> *)controls;

/**
 Advance to the next item.
 */
- (void)forward;

/**
 Go one item backwards.
 */
- (void)backward;

/**
 Sets the default loading view controller.
 Whenever an <code>APPlayerViewController</code> is instantiated, it will use the default view controller as its loading view.
 @param loadingViewClass - The default class from which to generate the video loading view.
 */
+ (void)setDefaultLoadingViewClass:(Class)loadingViewClass;

/**
 Sets the default loading view nib name.
 Whenever an <code>APPlayerViewController</code> is instantiated, it will use the default nib name as its loading view.
 @param loadingViewNibName - The default nib name from which to generate the video loading view.
 */
+ (void)setDefaultLoadingViewNibName:(NSString *)loadingViewNibName;

/**
 Returns the new instance of loading view.
 This method return new instance of loading view by nib name or class name, if it has one of them. else, it returns sdk default instance
 @return default video loading view.
 */
+ (UIView<APLoadingView> *)defaultLoadingViewInstance;

/**
 Soft seek live item to current time
 */
- (void)softSeekLiveToCurrentTime;

/**
 Plays the vod item using the new player within a given timeframe.
 @param startTime The start time of the clip.
 @param endTime The end time of the clip.
 */
- (void)playFromStartTime:(NSTimeInterval)startTime toEndTime:(NSTimeInterval)endTime;

#pragma mark - Facebook comments

/**
 Tells the facebook comments to show/hide.
 */
- (void)toggleFacebookComments;


@end
