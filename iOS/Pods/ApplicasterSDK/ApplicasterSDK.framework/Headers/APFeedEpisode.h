//
//  APFeedEpisode.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APFeedEpisode : NSObject
{
    NSMutableDictionary *_object;
}

/**
 json dict
 */
@property (nonatomic, readonly, strong) NSDictionary *object;

/**
 Episode Unique ID
 */
@property (nonatomic, readonly, strong) NSString *uniqueID;

/**
 Episode Name
 */
@property (nonatomic, readonly, strong) NSString *name;

/**
 Episode start time
 */
@property (nonatomic, readonly, strong) NSDate *startsAt;

/**
 Episode start time string
 */
@property (nonatomic, readonly, strong) NSString *startsAtString;

/**
 Episode end time
 */
@property (nonatomic, readonly, strong) NSDate *endsAt;

/**
 Episode end time string
 */
@property (nonatomic, readonly, strong) NSString *endsAtString;

/**
 Welcome Text
 */
@property (nonatomic, readonly, strong) NSString *welcomeText;

/**
 End Text
 */
@property (nonatomic, readonly, strong) NSString *endText;

/**
 Twitter hashtag array
 */
@property (nonatomic, readonly, strong) NSArray *twitterHashtags;

/**
 Twitter users array
 */
@property (nonatomic, readonly, strong) NSArray *twitterUsers;

/**
 Twitter pull tweets query.
 */
@property (nonatomic, readonly, strong) NSArray *twitterPullTweetsHashtags;

/**
 Twitter pull tweets query.
 */
@property (nonatomic, readonly, strong) NSArray *twitterPullTweetsUsers;

/**
 Twitter pull tweets list - pull tweets from list - that contains ids of a curated group of Twitter users.
 */
@property (nonatomic, readonly, strong) NSArray *twitterPullTweetsLists;

/**
 Twitter pull query type - the type of twitter pull query field (hashtags, username, list).
 */
@property (nonatomic, strong) NSString *twitterPullQueryType;

/**
 Facebook Page ID.
 */
@property (nonatomic, readonly, strong) NSString *facebookPageID;

/**
 Facebook hashtags.
 */
@property (nonatomic, readonly, strong) NSArray *facebookHashtags;

/**
 IsFacebookPostEnabled - YES if the user can send posts on the Facebook page. else - equal NO
 */
@property (nonatomic, readonly, assign) BOOL isFacebookPostEnabled;

/**
 Image dictionary
 */
@property (nonatomic, readonly, strong) NSDictionary *imageDictionary;

/**
 Image size.
 **/
@property (nonatomic, readonly, assign) CGSize imageSize;

/**
 External link dictionary
 Example:
 external_link:
 {
 label: 'label',
 url: "http://www.google.com"
 }
 */
@property (nonatomic, readonly, strong) NSDictionary *externalLink;

/**
 Audio sync dictionary
 Example:
 audio_sync:
 {
 data: '1',
 landscape_image: "http://landscape.png"
 portrait_image: "http://portrait.png"
 provider: "civolution_live_watermark"
 }
 */
@property (nonatomic, readonly, strong) NSDictionary *audioSync;

/**
 Init Episode with Dictionary
 */
- (id)initWithDictionary:(NSDictionary *)dictionary;

/**
 Checked if episode is presenting now.
 */
- (BOOL)isEpisodePresentingNow;

@end
