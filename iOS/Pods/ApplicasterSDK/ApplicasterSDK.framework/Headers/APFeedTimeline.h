//
//  APFeedTimeline.h
//  applicaster
//
//  Created by dan g / applicaster on 10/15/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APFeed2Customization;
@class APFeedBanner;

@interface APFeedTimeline : NSObject

/**
 Demo is only for client which scan a QR code in order to watch the theme.
 the only different between real feed and demo feed is the banner which becomes refresh button.
 */
@property (nonatomic, assign) BOOL isDemo;


@property (nonatomic, strong) APFeed2Customization *timelineTheme;
/**
 json dict
 */
@property (nonatomic, strong) NSDictionary *object;

/**
 ARN - Applicaster Resource Name - uniquely identify applicaster resources.
 */
@property (nonatomic, strong) NSString *arn;

/**
 substitution settings dictionary with orders of to replace character
 */
@property (nonatomic, strong) NSDictionary *substitutionSettings;

/**
 time zones for each character
 */
@property (nonatomic, strong) NSDictionary *timeZones;

/**
 Nearest time zone chosen
 */
@property (nonatomic, strong) NSString *timeZoneID;

/**
 Number of times allowed to substitute character
 */
@property (nonatomic, assign) int substitutionCounter;

/**
 Method defined how to control the character subs. by counter of by time.
 */
@property (nonatomic, strong) NSString *substitutionMethod;

/**
 substitution time for replace characters
 */
@property (nonatomic, assign) NSTimeInterval substitutionTime;

/**
 TimelineID
 */
@property (nonatomic, strong) NSString *timelineID;

/**
 Is live now
 */
@property (nonatomic, assign) BOOL isLive;

/**
 Name of timeline
 */
@property (nonatomic, strong) NSString *name;

/**
 type of timeline for example: crossmates, feed, etc.
 */
@property (nonatomic, strong) NSString *type;

/**
 Init with dictionary from JSON
 Be sure to call the correct feed type object
 */
- (id)initWithDictionary:(NSDictionary *)dictionary;

/***********
 Poll policy
 ***********/

/**
 *  Timeline events update rate. (Default value 30)
 */
@property (nonatomic, assign) NSTimeInterval eventsUpdateRate;

/**
 *  Facebook number of posts to pull in the every poll. (Default value 50)
 */
@property (nonatomic, assign) NSUInteger facebookPostsCount;

/**
 *   Facebook posts update rate. (Default value 30)
 */
@property (nonatomic, assign) NSTimeInterval facebookPostsUpdateRate;

/**
 *  Twitter number of tweets to pull in the every poll. (Default value 50)
 */
@property (nonatomic, assign) NSUInteger twitterTweetsCount;

/**
 *  Twitter tweets update rate. (Default value 30)
 */
@property (nonatomic, assign) NSTimeInterval twitterTweetsUpdateRate;


/***********
 Feed Banners
 ***********/

///**
// array of timeline banners APGenericBanner
// */
//@property (nonatomic, strong, readonly) NSArray *feedBanners;

/**
 Feed inline banner
 */
@property (nonatomic, strong, readonly) APFeedBanner *feedInlineBanner;
/**
 Feed bottom banner
 */
@property (nonatomic, strong, readonly) APFeedBanner *feedBottomBanner;
/**
 Feed splash banner
 */
@property (nonatomic, strong, readonly) APFeedBanner *feedSplashBanner;



@end
