//
//  APTwitterManager.h
//  applicaster
//
//  Created by Hagit Shemer on 12/31/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APEventsPollingManager.h"

@class APTwitterItem;

@protocol APTwitterManagerDelegate

/**
 @param tweetsArray - updated tweets array (including old and new tweets)
 @param newTweetsCount - number of new tweets
 **/
-(void)tweetsUpdated:(NSArray *)tweetsArray newTweetsCount:(NSInteger)newTweetsCount andNewTweets:(NSArray *)tweets;
- (void)tweetsLoadingFailed;

@end


#pragma mark -


@interface APTwitterManager : NSObject <APEventsPollingManager>

/**
 ALL tweets that were polled from start date till last polling date
 **/
@property (nonatomic,strong,readonly,getter = getTweetsArray) NSMutableArray *tweetsArray;
/**
 Hashtag array
 **/
@property (nonatomic,strong, readonly) NSArray *hashtagsArray;
/**
 User sceen name array
 **/
@property (nonatomic,strong, readonly) NSArray *usersArray;

/**
 List - timeline of tweets authored by members of the specified list
 **/
@property (nonatomic,strong, readonly) NSArray *listsArray;

/**
 Post tweets hashtag array
 **/
@property (nonatomic,strong, readonly) NSArray *postTweetsHashtagsArray;
/**
 Post tweets user sceen name array
 **/
@property (nonatomic,strong, readonly) NSArray *postTweetsUsersArray;

/**
 Twitter Manager Delegate
 **/
@property (nonatomic,assign) id<APTwitterManagerDelegate> twitterManagerDelegate;

/**
 @param hashTagsArr
 @param usersArray
 @param listsArray
 @param postHashTagsArr - hashtags for post tweets.
 @param postUsersArr - users for post tweets.
 @param startDate - date to start polling from
 @param pollingInterval - tweets polling interval in seconds
 @param pollingLimit the max number of items to pull for each poll. If <= 0 there will be no limitation on the number of items.
 @return APStarsManager instance
 **/
- (id)initWithHashtagsArr:(NSArray *)hashTagsArr
               usersArray:(NSArray *)usersArray
               listsArray:(NSArray *)listsArray
         postHashtagArray:(NSArray *)postHashTagsArr
            postUserArray:(NSArray *)postUsersArr
             andStartDate:(NSDate *)startDate
          pollingInterval:(NSTimeInterval)pollingInterval
             pollingLimit:(NSInteger)pollingLimit;

/**
 @param hashTagsArr
 @param usersArray
 @param startDate - date to start polling from
 @param pollingInterval - tweets polling interval in seconds
 @param pollingLimit the max number of items to pull for each poll. If <= 0 there will be no limitation on the number of items.
 @return APStarsManager instance
 **/
- (id)initWithHashtagsArr:(NSArray *)hashTagsArr
               usersArray:(NSArray *)usersArray
             andStartDate:(NSDate *)startDate
          pollingInterval:(NSTimeInterval)pollingInterval
             pollingLimit:(NSInteger)pollingLimit;

/**
 @param tweetID
 @param handler that receives the updated tweet
 **/
- (void)getUpdateTweetWithID:(NSString *)tweetID withCompletionHandler:(void (^)(APTwitterItem *tweet))handler;

/**
 Send a tweet.
 @param tweetParams dictionary - contain parameters of tweet.
 @param attachedImage - image to attach to tweet, can be nil
 @param completionBlock - success returns YES if send a tweet.
 */
- (void)sendTweet:(NSDictionary *)tweetParams withImage:(UIImage *)attachedImage withCompletionHandler:(void (^)(BOOL success))completionBlock;

/**
 Send retweet.
 @param tweetId string - the id of tweet.
 @param completionBlock - success returns YES if update retweet.
 */
- (void)sendRetweet:(NSString *)tweetId;

/**
 Send retweet with completion handler.
 @param tweetId string - the id of tweet.
 @param completionBlock - success returns YES if update retweet.
 */
- (void)sendRetweet:(NSString *)tweetId withCompletionHandler:(void (^)(BOOL success))completionBlock;

/**
 Force Tweets poll
 **/
- (void)forcePollingNow;

@end
