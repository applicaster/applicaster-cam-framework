//
//  APTimelineManager.h
//  applicaster
//
//  Created by dan g / applicaster on 12/24/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APFeedTimeline;

extern NSString * const kTimeFeedTimeLineStatusChanged;
extern NSString * const kCrossMatesTimeLineStatusChanged;
extern NSString * const kIsTimelineAvailableKey;
extern NSString * const kTimelineIDKey;

@class APStarsClient;

@interface APTimelinesManager : NSObject
/**
 sharedStars
 */
+ (APTimelinesManager *)sharedManager;

/**
 The account ID of the account which found in the cms of applicaster
 This setter also fetch all timelines and fill cm array and feed array with timelines accordingly
 */
@property (nonatomic, strong) NSString *accountID;

/**
This array recieved by the stars server and has all timelines of an account
*/
@property (nonatomic, strong) NSMutableArray *timelines;

/**
 This array recieved by the stars server and has all timelines of an account
 */
@property (nonatomic, strong) NSMutableArray *cmTimelines;

/**
 This array recieved by the stars server and has all timelines of an account
 */
@property (nonatomic, strong) NSMutableArray *feedTimelines;

/**
 This dictionary recieved by the stars server and has all feed timelines' managers of an account
 */
@property (nonatomic, strong) NSMutableDictionary *feedManagers;

/**
 This string contains timelineID fo the first live feed's timeline
 */
@property (nonatomic, strong) NSString *firstLiveTimelineID;

/**
 This string contains timelineID of the current presenting timeline.
 */
@property (nonatomic, strong) NSString *currentPresentingTimelineID;

/**
 This dictionary recieved by the stars server and has all CM timelines' managers of an account
 */
@property (nonatomic, strong) NSMutableDictionary *CMManagers;

/**
 This string contains timelineID fo the first live CM's timeline
 */
@property (nonatomic, strong) NSString *firstCMLiveTimelineID;

/**
 Stars client used for communicating with the stars API
 */
@property (nonatomic, strong) APStarsClient *starsClient;

/**
 Open crossmate from URLScheme (APSchemeHandler)
 */
//- (void)presentCrossMatesWithComplitionHandler:(void (^)(BOOL success))completion;

/**
 Open specific feed (by timelineID) from URLScheme (APSchemeHandler)
 */
- (void)presentFeedWithTimelineID:(NSString *)timelineID completionHandler:(void (^)(BOOL success))completion;

/**
 Open specific demo feed (by timelineID) from URLScheme (APSchemeHandler)
 @discussion When client would like to see the custom theme of the feed feature he opens the feed with scanning a QR code.
 */
- (void)presentDemoFeedWithTimelineID:(NSString *)timelineID completionHandler:(void (^)(BOOL success))completion;

/**
 Open the first live timeline feed from URLScheme (APSchemeHandler)
 use this method when user tapped on feed button
 */
- (void)presentFirstLiveTimelineFeedWithCompletionHandler:(void (^)(BOOL success))completion;

/**
 Open the first crossmate live timeline from URLScheme (APSchemeHandler)
 use this method when user tapped on CM button
 */
- (void)presentFirstCMLiveTimelineWithCompletionHandler:(void (^)(BOOL success))completion;

/**
 Open the timeline crossmate by timeline id
 use this method when there is multiple timelines.
 */
- (void)presentCMWithTimelineID:(NSString *)timelineID completionHandler:(void (^)(BOOL success))completion;

/**
 Return the timeline object for a given timeline id.
 */
- (APFeedTimeline *)timelineForTimelineID:(NSString *)timelineID;

/**
 Calls the completion block with an array of APFeedEpisode objects that belong to the timeline with the given timelineID.
 */
- (void)episodesForTimelineID:(NSString *)timelineID
                   completion:(void (^)(NSArray *episodes))completion;

/**
 Returns an array of APFeedTimelines objects which are live.
 */
- (NSArray *)liveFeedTimelines;

/**
 Returns an array of APFeedTimelines objects which are live.
 */
- (NSArray *)liveCrossmatesTimelines;

/**
 Return type by timeline id
 */
- (NSString *)getTypeByTimelineID:(NSString *)timelineID;

/**
 get CMManager by timelineID
 */
- (id)cmManagerByTimelineID:(NSString *)timelineID;

/**
 Update the timelines status with completion handler
 */
- (void)updateTimelinesStatusWithCompletionHandler:(void (^)(BOOL success))completion;

@end
