//
//  APTwitterItem.h
//  Twitter Login
//
//  Created by dan g / applicaster on 12/10/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <ApplicasterSDK/APFeedEvent.h>


@interface APTwitterItem : APFeedEvent

/**
 The json as we get it from twitter sdk
 */
@property (nonatomic, readonly, strong) NSDictionary *object;

/**
 How many ppl liked this tweet
 */
@property (nonatomic, readonly, assign) int favoriteCount;

/**
 The tweet id
 */
@property (nonatomic, readonly, strong) NSString *uniqueID;

/**
 How many ppl retweeted this tweet
 */
@property (nonatomic, readonly, assign) int retweetCount;

/**
 Did the user retweet this tweet
 */
@property (nonatomic, assign) BOOL userRetweeted;

/**
 Feed retweeted user - the original user of retweet.
 **/
@property (nonatomic, strong) APFeedUser *feedRetweetedUser;

/**
 The NSDate when this tweet was created
 */
@property (nonatomic, readonly, strong) NSDate *createdAt;

/**
 The tweet image (if uploaded)
 */
@property (nonatomic, readonly, strong) NSString *imageStr;

/**
 Image size.
 **/
@property (nonatomic, readonly, assign) CGSize imageMedumSize;

/**
 The tweet url link (if added)
 */
@property (nonatomic, readonly, strong) NSURL *url;

/**
 The method which parse the json to properties
 @param json dictionary which sdk supplied
 @return APTwitterItem object
 */
- (id)initWithDictionary:(NSDictionary *)jsonDict;

@end
