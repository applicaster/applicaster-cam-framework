//
//  APBackgroundManager.h
//  applicaster
//
//  Created by Liviu Romascanu on 6/9/11.
//  Copyright 2011 none. All rights reserved.
//

@interface APBackgroundManager : NSObject

+ (id)sharedInstance;

/**
 Start a background task for downloaded items(HQME)
 */
- (void)startVodItemsBackgroundTask;

/**
 End a background task of the downloading items(HQME)
 */
- (void)endVodItemsBackgroundTask;

@end 