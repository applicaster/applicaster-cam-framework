//
//  APEpisode.h
//  applicaster
//
//  Created by Liviu Romascanu on 2/17/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APModel.h"

@interface APEventSequence : APModel

/**
 Name of the episode
 */
@property (nonatomic, strong, readonly) NSString        *name;

/**
 Duration in seconds of the episode
 */
@property (nonatomic, assign, readonly) NSTimeInterval  duration;

/**
 Array of APEvent Objects
 */
@property (nonatomic, strong, readonly) NSArray         *events;

/**
 Array of Visable APEvent Objects
 */
@property (nonatomic, strong, readonly) NSArray         *visibleEvents;


@end
