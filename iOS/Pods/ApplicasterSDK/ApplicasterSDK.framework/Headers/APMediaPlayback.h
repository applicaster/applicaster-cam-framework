//
//  APMediaPlayback.h
//  ApplicasterSDK
//
//  Created by Tom Susel on 1/29/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The APMediaPlayback protocol defines the interface adopted by player classes for controlling media playback. This protocol supports basic transport operations including start, stop, and pause.
 */
@protocol APMediaPlayback <NSObject>

/**
 Plays items from the current queue, resuming paused playback if possible.
 */
- (void)play;

/**
 Pauses playback if playing.
 */
- (void)pause;

/**
 Ends playback. Calling -play again will start from the beginnning of the queue.
 */
- (void)stop;


/**
 Seek to a given time
 */
- (void)seekToTime:(NSTimeInterval)time;

/**
 The current playback time of the now playing item in seconds.
 */
@property(nonatomic) NSTimeInterval currentPlaybackTime;

@end
