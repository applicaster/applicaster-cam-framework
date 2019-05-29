//
//  APStarsClient.h
//  applicaster
//
//  Created by Hagit Shemer on 12/30/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef SETTINGS_SERVER
extern NSString *kAPFeedServerPath;
#else
extern NSString *const kAPFeedServerPath;
#endif

@class APFeedTimeline, APFeed2EventWidgetQuestion, APFeed2EventWidgetAnswer;

@interface APStarsClient : NSObject

#pragma mark - timelines

/**
 Get an array of APFeedTimeline objects for account
 @param accountID
 @param handler that receives an array of available timelines or nil if there are none
 */
- (void)loadTimelinesForAccountID:(NSString *)accountID withCompletionHandler:(void (^)(NSArray *timelines))handler;


#pragma mark - customization

/**
 Get a dictionary of customization settings for timeline
 @param timelineID
 @param handler that receives a dictionary of available customization settings or nil if there are none
 */
- (void)loadCustomizationForTimelineId:(NSString *)timelineID withCompletionHandler:(void (^)(NSDictionary *customizationDictionary))handler;

#pragma mark - episode

/**
 Get an array of APFeedEpisode objects for timeline
 @param timeline
 @param handler that receives an array of available episodes or nil if there are none
 */
- (void)loadEpisodesForTimeline:(APFeedTimeline *)timeline
              completionHandler:(void(^)(NSArray *episodesArray))handler;

#pragma mark - feeds

/**
 Get an array of APFeedFeed objects for timeline
 @param timeline
 @param isCrossMates
 @param handler that receives an array of available feeds or nil if there are none
 */
- (void)loadFeedsArrayForTimeline:(APFeedTimeline *)timeline isCrossMates:(BOOL)isCrossMates withCompletionHandler:(void(^)(NSArray *feedsArray))completion;


#pragma mark - events

/**
 Get an array of APFeedEvent objects for timeline
 @param feedArray of APFeedFeed objects to inquire
 @param timeInterval to start from
 @param handler that receives an array of available events or nil if there are none
 */
- (void)loadEventsFromFeeds:(NSArray *)feedsArray forTimeline:(APFeedTimeline *)timeline fromTime:(NSTimeInterval)timeInterval withCompletionHandler:(void(^)(NSArray *eventsArray))handler;

/**
 Get updated answers for a widget question event
 @param widgetQuestionEvent
 @param handler
 */
- (void)loadAnswersForWidgetQuestionEvent:(APFeed2EventWidgetQuestion *)widgetQuestionEvent withCompletionHandler:(void(^)(APFeed2EventWidgetQuestion * updatedQuestion))handler;

/**
 Submit widget answer for widget question
 @param widgetAnswer
 @param widgetQuestion
 @param handler
 */
- (void)submitWidgetAnswer:(APFeed2EventWidgetAnswer *)widgetAnswer forWidgetQuestion:(APFeed2EventWidgetQuestion *)widgetQuestion withCompletionHandler:(void(^)(BOOL success))handler;

@end

