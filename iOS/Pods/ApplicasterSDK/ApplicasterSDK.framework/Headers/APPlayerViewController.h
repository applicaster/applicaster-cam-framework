//
//  APPlayerViewController.h
//  applicaster
//
//  Created by Tom Susel on 1/19/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APPlayerController.h"

extern NSString *const kAPPlayerViewControllerViewDidLoad;                  // Posted when the ViewController's viewDidLoad method was called.
extern NSString *const kAPPlayerViewControllerViewWillAppear;               // Posted when the ViewController's viewWillAppear method was called.
extern NSString *const kAPPlayerViewControllerViewWillDisappear;            // Posted when the ViewController's viewWillDisappear method was called.

/**
 Player view controller.
 A view controller intended to show the player modally.
 */
@interface APPlayerViewController : UIViewController{
    APPlayerController          *_playerController;
}

@property (nonatomic, strong, readonly) APPlayerController *playerController;   /**< Player controller used to render the playable item */

/**
 A bit mask for the allowed interface orientations.
 Default allowed orientations are <code>APInterfaceOrientationLandscapeLeft</code> and <code>APInterfaceOrientationLandscapeRight</code>
 */
@property (nonatomic, assign) UIInterfaceOrientationMask allowedOrientations;

/**
 indicates whether or not remove persistant resume
 */
@property (nonatomic, assign) BOOL shouldIgnoreInterruptScreen;

/**
 Creates a player controller to play an item.
 @param item - The target item to play.
 */
- (id)initWithPlayableItem:(id<APPlayable>)item;

/**
 Creates a player controller to play a list of items.
 @param items - An array of playable items.
 */
- (id)initWithPlayableItems:(NSArray*)items;

/**
 Starts playing.
 */
- (void)play;

/**
 Pauses playback.
 */
- (void)pause;


/**
 Seek to a given time in seconds
 */
- (void)seekToTime:(NSTimeInterval)time;


/**
 Closes the player with animation.
 Can be assigned to a done button.
 @param sender The caller of this method.
 */
- (IBAction)close:(id)sender;

/**
 Closes the player.
 @param animated - closes the player animated or not animated
 */
- (void)closeAnimated:(BOOL)animated;

/**
 Closes the player.
 @param commercials - closes the player with commercials or without commercials
 @param animated - closes the player animated or not animated
 */
- (void)closeWithCommercials:(BOOL)commercials
                    animated:(BOOL)animated
           completionHandler:(void(^)(void))completion;

/**
 @return The default scaling mode.
 */
+ (APMovieScalingMode)defaultScalingMode;

/**
 Sets the default scaling mode.
 @param scalingMode The scaling mode of the video. See <APMovieScalingMode>.
 */
+ (void)setDefaultScalingMode:(APMovieScalingMode)scalingMode;

@end
