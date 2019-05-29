//
//  APFeedEvent.h
//  ApplicasterSDK
//
//  Created by Hagit Shemer on 1/16/14.
//  Copyright (c) 2014 Applicaster. All rights reserved.
//

@class APFeedUser;

@interface APFeedEvent : NSObject <NSCoding>

/**
 Feed user (star, faceboker, or tweep)
 **/
@property (nonatomic, strong) APFeedUser *feedUser;

/**
 Event text
 **/
@property (nonatomic, strong) NSString *text;

/**
 Comments array can be nil if there are none (can be overriden by inherited classes)
 **/
@property (nonatomic, strong) NSMutableArray *commentsArray;

/**
 Number of comments for event (can be overriden by inherited classes)
 **/
@property (nonatomic, assign, readonly) NSUInteger commentsCount;

/**
 @return event ID string (must be overriden by inherited classes)
 */
- (NSString *)eventUniqueID;

/**
 @return event type string string (must be overriden by inherited classes)
 */
- (NSString *)eventTypeString;

/**
 @return image URL string or nil (should be overriden by inherited classes)
 */
- (NSString *)imageURLString;

/**
 @return image size.
 */
- (CGSize)imageSize;

/**
 @return video URL string or nil (should be overriden by inherited classes)
 */
- (NSString *)videoURLString;

/**
 @return audio URL string or nil (should be overriden by inherited classes)
 */
- (NSString *)audioURLString;


@end
