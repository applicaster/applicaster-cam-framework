//
//  APFacebookCommentsManager.h
//  ApplicasterSDK
//
//  Created by Hagit Shemer on 12/30/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import "APEventsPollingManager.h"

extern NSString * const kAPFacebookUINeedRefreshNotification;

@class APFacebookPostObject, APFacebookSDKClient;

@protocol APFacebookCommentsManagerDelegate
/**
 @param postsArray - updated posts array (including old and new posts)
 @param newPostsCount - number of new posts
 **/
-(void)facebookCommentsDataUpdated:(NSArray *)postsArray newPostsCount:(NSInteger)newPostsCount andNewPosts:(NSArray *)posts;

@end


#pragma  mark -

@interface APFacebookCommentsManager : NSObject <APEventsPollingManager>

/**
 ALL posts from start date till last polling date
 **/
@property (nonatomic,strong,readonly,getter = getPostsArray) NSMutableArray *postsArray;
/**
 Facebook Comments Manager delegate
 **/
@property (nonatomic,assign) id<APFacebookCommentsManagerDelegate> facebookCommentsDelegate;

/**
 Init Facebook Comments Manager for FB page
 @param facebookClient Applicaster's facebook client needed in order to use Facebook's APIs.
 @param facebookPageID
 @param startDate - date to poll from
 @param pollingInterval - in seconds
 @param pollingLimit the max number of items to pull for each poll. If <= 0 there will be no limitation on the number of items.
 **/
- (id)initWithFacebookClient:(APFacebookSDKClient *)facebookClient
              facebookPageID:(NSString *)facebookPageID
                   startDate:(NSDate *)startDate
             pollingInterval:(NSTimeInterval)pollingInterval
                pollingLimit:(NSInteger)pollingLimit;

/**
 Get updated post
 @param post - the post to update
 @param handle that receives the updated post object
 **/
- (void)getUpdatedPost:(APFacebookPostObject *)post withCompletionHandler:(void (^)(APFacebookPostObject *post))handler;

/**
 Add a post to the page
 @param postText
 @param image - image to add to the post; can be null
 @param completion handler
 **/
- (void)addPost:(NSString *)postText withImage:(UIImage *)image withCompletionHandler:(void (^)(NSString *resultPostId, NSError *error))handler;

/**
 Add a post to the page
 @param postText
 @param image - image to add to the post; can be null
 @param link - link url in string to share
 @param completion handler
 **/
- (void)addPost:(NSString *)postText withImage:(UIImage *)image withLink:(NSString *)link withCompletionHandler:(void (^)(NSString *resultPostId, NSError *error))handler;

/**
 Add comment to a post in the page
 @param commentText
 @param image - image to add to the comment; can be null
 @param postID
 **/
- (void)addComment:(NSString *)commentText withImage:(UIImage *)image toPostWithID:(NSString *)postID withCompletionHandler:(void (^)(NSString *resultCommentId, NSError *error))handler;

/**
 Set post like status
 @param postID
 @param doesUserLike
 @param handler that receives a boolean indicating the success
 **/
- (void)setPostWithID:(NSString *)postID toUserLike:(BOOL)doesUserLike withCompletionHandler:(void (^)(BOOL success))handler;

/**
 Force Facebook comments poll
 **/
- (void)forcePollingNow;

@end

