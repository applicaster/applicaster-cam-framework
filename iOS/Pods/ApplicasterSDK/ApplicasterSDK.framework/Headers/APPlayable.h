//
//  APPlayable.h
//  applicaster
//
//  Created by Tom Susel on 1/11/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString *const APPlayableItemWillStartPlaying = @"kAPPlayableItemWillStartPlaying";

/**
 A protocol for playable items.
 An object can be played by the <code>APPlayerController</code> if it conforms to this protocol.
 */
@protocol APPlayable <NSObject>

#pragma mark Required

@required

/**
 The name of the item to be used for the different player features.
 */
- (NSString *)playableName;

/**
 The name of the item to be used for the different player features.
 */
- (NSString *)playableDescription;

/**
 A path to the content video.
 */
- (NSString *)contentVideoURLPath;

/**
 A path to the overlay HTML.
 */
- (NSString *)overlayURLPath;

/**
 Indicates if the item is being played live or not.
 */
- (BOOL)isLive;

/**
 The public page for this playable.
 */
- (NSString *)publicPageURLPath;

/**
 @return the parameters for this playable to be sent for all the analytics events.
 */
- (NSDictionary *)analyticsParams;

#pragma mark Optional

@optional

/**
 The last time reached during playback. This will need to be set by the <APPlayerController>.
 */
@property (nonatomic, assign) NSTimeInterval lastPlayedTime;

/**
 The item's duration. This will need to be set by the <APPlayerController>.
 */
@property (nonatomic, assign) NSTimeInterval playbackDuration;

/**
 A path to the image preroll.
 */
- (NSString *)prerollSplashURLPath;

/**
 A path to the video preroll.
 */
- (NSString *)prerollVideoURLPath;

/**
 Implement this method in order for the player to know if your playable is capture moment enabled.
 */
- (BOOL)captureMomentEnabled;

/**
 Implement this method in order to supply more params for the different features to have.
 */
- (NSDictionary *)extraPlayableInfo;

/**
 The Facebook object ID for the Facebook comments feature.
 */
- (NSString *)facebookObjectID;

@end
