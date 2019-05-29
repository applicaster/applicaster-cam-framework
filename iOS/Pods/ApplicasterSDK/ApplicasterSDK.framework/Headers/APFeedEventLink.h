//
//  APFeedEventLink.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APFeedEventImage.h"

@interface APFeedEventLink : APFeedEventImage

/**
 Link Dictionary.
 Can be used to initialize APTimedWebViewController
 */
@property (nonatomic, readonly, strong) NSDictionary *linkDictionary;

/**
 IsTakeOver - if equal YES, present link event in the Take Over mode.
 */
@property (nonatomic, readonly, assign) BOOL isTakeOver;

/**
 TakeOverDuration - the number of seconds to display the Take Over.
 */
@property (nonatomic, readonly, assign) NSInteger takeOverDuration;

/**
 IsTransparentBackground - if equal YES, presents link event with a transparent background, else - with a black background.
 */
@property (nonatomic, readonly, assign) BOOL isTransparentBackground;

@end
