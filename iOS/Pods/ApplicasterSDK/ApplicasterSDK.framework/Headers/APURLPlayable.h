//
//  APURLPlayable.h
//  applicaster
//
//  Created by reuven levitsky on 07/01/2016.
//  Copyright © 2016 Applicaster Ltd. All rights reserved.
//

/**
 APURLPlayable represents a model containing a URL to be played.
 */
#import "APPlayable.h"

@interface APURLPlayable : NSObject <APPlayable> {

}

#pragma mark - Init

- (instancetype)initWithStreamURL:(NSString *)streamURL
                             name:(NSString *)name
                      description:(NSString *)description;

#pragma mark - Play methods

/**
 Plays this item using the new player.
 showing the the new player with animated presentation
 */
- (void)play;

/**
 Plays this item using the new player.
 showing the the new player with animated or non animated presentation
 @param animated Present the new player animated or not animated
 */
- (void)playAnimated:(BOOL)animated;

@end

