//
//  APFacebookCommentsObject.h
//  ApplicasterSDK
//
//  Created by Daniel Shein on 11/26/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import "APFeedEvent.h"

@class APFacebookAttachment;
@class APFeedUser;
@class APFBGraphUser;

@interface APFacebookCommentsObject : APFeedEvent

@property (nonatomic, strong) NSString *pageId;
@property (nonatomic, strong) NSString *postId;
@property (nonatomic, strong) NSString *commentID;
@property (nonatomic, strong) APFBGraphUser *author;

@property (nonatomic, assign) long time;
@property (nonatomic, assign) BOOL doesUserLike;

@property (nonatomic, strong) APFacebookAttachment *attachment;
@property (nonatomic, assign) NSUInteger likesCount;

@property (nonatomic, strong) NSDate *createdDate;

/**
 init method needs to be used.

 @param currentUser - the facebook user for this Facebook active session.
 @param dictionary - the dictionary wrapping the post data as received from Facebook.

 @return new instance of this class.
 */
-(id)initWithCurrentUser:(APFBGraphUser *)currentUser
           andDictionary:(NSDictionary *)dictionary;

/**
 Returns the image URL string from the media attachment if available
 @return image URL string - trying to replace small with big image if available
 */
- (NSString *)imageURLString;

/**
 Returns the image size from the media attachment if available
 */
- (CGSize)imageSize;

/**
 Returns the video URL string from the media attachment if available
 @return video URL string
 */
- (NSString *)videoURLString;

/**
 Returns the link URL string from the media attachment if available
 @return link URL string
 */
- (NSString *)linkURLString;

@end
