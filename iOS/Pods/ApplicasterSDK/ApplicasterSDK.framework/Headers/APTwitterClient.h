//
//  APTwitterClient.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 12/2/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

@import Accounts;

extern NSString *const APTwitterDidLoginNotification;
extern NSString *const APTwitterLoginFailedNotification;
extern NSString *const kAPTwitterUserDataReady;

@class APTwitterItem;
@class APTwitterUser;

@interface APTwitterClient : NSObject

//some helful urls:
//https://support.twitter.com/articles/15364-about-twitter-limits-update-api-dm-and-following
//https://dev.twitter.com/docs/error-codes-responses


/**
 sharedInstance
 */
+ (APTwitterClient *)sharedInstance;

/**
 Checks if user has access to twitter in the accounts available to the app
 @return YES if access is allowed in the app , NO otherwise
 */
- (BOOL)userHasAccessToTwitter;

/**
 Checks if user is logged into twitter in the accounts available to the app
 @return YES if logged in and allowed in the app , NO otherwise
 */
- (BOOL)isLoggedInToTwitter;

/**
 Log into twitter using the native twitter account
 @param completionBlock - success returns YES if login succeeded / already logged in. error returns the error in case of a login error
 @discussion - In case login failed and there is no error - this means the user blocked the login from the device settings or has no twitter access.
 */
- (void)requestTwitterAccesWithCompletionHandler:(void (^)(BOOL success, NSError *error))completionBlock;

/**
 *  @return the default username used for sending tweets and the rest of the twitter APIs.
 */
- (NSString *)defaultUsername;

/**
 *  @return the default Twitter account used for sending tweets and the rest of the twitter APIs.
 */
- (ACAccount *)defaultTwitterAccount;

/**
 Retrieves all the usernames associated with an account
 @return array of username strings
 */
- (NSArray *)twitterUsernames;

/**
 Retrieves the user information for the default user
 @return (completion block) APTwitterUser object contains the user's data and bool for success or failure.
 */
- (void)defaultTwitterUserWithCompletionHandler:(void (^)(BOOL success, APTwitterUser *twitterUser))completionBlock;

/**
 *  @param username the username of the twitter user you would like to get it's data.
 *  @param completionBlock - completion which will be called after getting all the data.
 */
- (void)twitterUserWithName:(NSString *)username withCompletionBlock:(void (^)(BOOL success, APTwitterUser *twitterUser))completionBlock;

/**
 Update tweet
 @param tweetID
 @param handler
 **/
- (void)updateTweetWithID:(NSString *)tweetID withCompletionHandler:(void (^)(APTwitterItem *tweet))completionBlock;

/**
 Search for multiple hashtags
 @param hashTagsArray hahstags array
 @param reacentTwitterItemId - take the last twitte recieve id
 @param completionBlock - Returns a response dictionary from twitter if this was successful
 */
- (void)searchForHashtags:(NSArray *)hashTagsArray
                    since:(NSString *)reacentTwitterItemId
    withCompletionHandler:(void (^)(NSArray *items))completionBlock;

/**
 Search for multiple hashtags
 @param hashTagsArray hahstags array
 @param reacentTwitterItemId - take the last twitte recieve id
 @param countLimit - max number of items to pull each request. If <= 0 will not be limites. Twitter limits the number of items to pull to 100, so if > 100 -> 100 will be used as the limit.
 @param completionBlock - Returns a response dictionary from twitter if this was successful
 */
- (void)searchForHashtags:(NSArray *)hashTagsArray
                    since:(NSString *)reacentTwitterItemId
               countLimit:(NSInteger)countLimit
    withCompletionHandler:(void (^)(NSArray *items))completionBlock;

/**
 Search for multiple users
 @param userScreenName - user screen name
 @param completionBlock - Returns a response dictionary from twitter if this was successful
 @param reacentTwitterItemId - take the last twitte recieve id
 */
- (void)searchForUser:(NSString *)userScreenName since:(NSString *)reacentTwitterItemId withCompletionHandler:(void (^)(NSArray *items))completionBlock;

/**
 Search for timeline of tweets authored by members of the specified list
 @param listID - list id
 @param completionBlock - Returns a response dictionary from twitter if this was successful
 @param reacentTwitterItemId - take the last twitte recieve id
 */
- (void)searchForList:(NSString *)listID since:(NSString *)reacentTwitterItemId withCompletionHandler:(void (^)(NSArray *items))completionBlock;

/**
 Send a tweet.
 @param tweetParams dictionary - contain parameters of tweet
 @param attachedImage - image to attach to tweet, can be nil
 @param completionBlock - success returns YES if send a tweet
 */
- (void)sendTweet:(NSDictionary *)tweetParams withImage:(UIImage *)attachedImage withCompletionHandler:(void (^)(BOOL success))completionBlock;

/**
 Send retweet.
 @param tweetId string - the id of tweet.
 @param completionBlock - success returns YES if update retweet.
 */
- (void)sendRetweet:(NSString *)tweetId withCompletionHandler:(void (^)(BOOL success))completionBlock;

/**
 Migrate the token got from OAuth login to the account store in the ios settings
 @param toekn (key) string - the key of the token
 @param secert (value) string - the value of the token
 */
- (void)storeAccountWithAccessToken:(NSString *)token
                             secret:(NSString *)secret
                      andCompletion:(void (^)(BOOL success, NSError *error))completionBlock;

@end
