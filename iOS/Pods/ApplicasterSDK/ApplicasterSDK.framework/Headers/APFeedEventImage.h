//
//  APFeedEventImage.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APFeedStarsEvent.h"

@interface APFeedEventImage : APFeedStarsEvent
/**
 Image Dictionary
 */
@property (nonatomic, strong) NSDictionary *imageDictionary;

/**
 Default Image URL
 */
@property (nonatomic, readonly, strong) NSURL *defaultImageURL;

/**
 Thumb Image URL
 */
@property (nonatomic, readonly, strong) NSURL *thumbImageURL;

/**
 Image size.
 **/
@property (nonatomic, assign, readonly) CGSize imageSize;

- (id)initWithTextMessage:(NSString *)message andImageDictionary:(NSDictionary *)imageDict andDate:(NSDate *)date;
@end
