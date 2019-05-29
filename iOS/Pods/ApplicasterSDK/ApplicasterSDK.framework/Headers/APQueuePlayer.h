//
//  APQueuePlayer.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/4/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import "APPlayer.h"

@class AVPlayerItem;
extern NSString *const APPlayerQueueueEndNotification;
extern NSString *const APPlayerQueueueFailedNotification;

@interface APQueuePlayer : APPlayer{
    NSMutableArray  *_contentURLs;
    NSInteger       _currentItemIndex;
    AVPlayerItem    *_nextItem;                 /**< The item that is to be played following this one */
    NSURL           *_nextItemURL;
    BOOL            _shouldAutoPlayNextItem;
}

/**
 Initiates the player with an array of URLs to play.
 @param URLs - An array of <cod>NSURL</code> objects that contains video URLs to play.
 */
- (id)initWithURLS:(NSArray*)URLs;

/**
 Ends playback of the current item and initiates playback of the next item in the player’s queue.
*/
- (void)advanceToNextItem;

/**
 The list of content URLs.
 Setting the urls during playback will pause playback.
 */
@property (nonatomic, retain) NSArray *contentURLs;

/**
 The currently played item.
 Initially and if player is stopped the index would be 0.
 */
@property (nonatomic, readonly) NSInteger currentItemIndex;

@end
