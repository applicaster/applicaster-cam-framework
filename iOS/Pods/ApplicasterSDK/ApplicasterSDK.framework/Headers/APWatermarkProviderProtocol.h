//
//  APWatermarkProviderProtocol.h
//  applicaster
//
//  Created by Miri on 9/28/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString * const kCivolutionNoContentDetectedNotification = @"kCivolutionTimestampDetectedNotification";
static NSString * const kCivolutionTimestampDetectedNotification = @"kCivolutionNoContentDetectedNotification";

/**
 This protocol is used to handle civolution - watermark for submoduls in SDK (example:feed-2-iOS)
 */
@protocol APWatermarkProviderProtocol <NSObject>

@required

/**
 Civolution shared manager.
 */
+ (id)sharedManager;

/**
 Start civolution watermark.
 */
- (void)startAudioSync;

@optional

/**
  Start detection after stream.
 */
- (BOOL)startDetection;

/**
 StopDetection - stop detection after stream.
 */
- (BOOL)stopDetection;

@end
