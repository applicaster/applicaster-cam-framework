//
//  APStarsManager.h
//  applicaster
//
//  Created by Hagit Shemer on 12/30/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APEventsPollingManager.h"

@class APFeedTimeline, APFeed2EventWidgetQuestion, APFeed2EventWidgetAnswer, APFeedStarsEvent;

@protocol APStarsManagerDelegate

- (void)feedsDataUpdated:(NSArray *)feedsArray;
/**
 @param eventsArray - updated events array (including old and new events)
 @param newEventsCount - number of new events
 **/
- (void)eventsDataUpdated:(NSArray *)eventsArray newEventsCount:(NSInteger)newEventsCount andNewEvents:(NSArray *)newEvents; //TODO: pass widgets events in a separate argument
/**
 @param takeoverStarsEvent - the new takeover event to display
 **/
- (void)takeoverStarsEventArrived:(APFeedStarsEvent *)takeoverStarsEvent;

- (void)feedsLoadingFailed;
- (void)eventsLoadingFailed;

- (void)resetEventsDueToDemoFeed:(NSArray *)events;

@end


#pragma mark -


@interface APStarsManager : NSObject <APEventsPollingManager>

/**
 ALL feeds that were polled from start date till last polling date
 **/
@property (nonatomic,strong,readonly) NSArray *feedsArray;
/**
 ALL events that were polled from start date till last polling date (excluding widgets)
 **/
@property (nonatomic,strong,readonly) NSArray *eventsArray;
/**
 Stars Manager Delegate
 **/
@property (nonatomic,assign) id<APStarsManagerDelegate> starsManagerDelegate;


/**
 @param timeline
 @param startDate - date to start polling from
 @param endDate - date when we can to clear episode data
 @param pollingInterval - feeds & events polling interval in seconds
 @param isCrossMates
 @return APStarsManager instance
 **/
- (id)initWithTimeline:(APFeedTimeline *)timeline startDate:(NSDate *)startDate endDate:(NSDate *)endDate pollingInterval:(NSTimeInterval)pollingInterval isCrossMates:(BOOL)isCrossMates;

/**
 Force Events polling
 **/
- (void)forcePollingNow;

/**
 Update widget question event with latest answers results
 @param widgetQuestionEvent
 @param handler
 */
- (void)updateWidgetAnswersforQuestionEvent:(APFeed2EventWidgetQuestion *)widgetQuestionEvent withCompletionHandler:(void(^)(APFeed2EventWidgetQuestion * updatedQuestion))handler;

/**
 Submit widget answer for widget question - update local and remote DB and force updating the question results
 @param widgetAnswer
 @param widgetQuestion - the question for which we submit the answer
 */
- (void)submitWidgetAnswer:(APFeed2EventWidgetAnswer *)widgetAnswer forWidgetQuestion:(APFeed2EventWidgetQuestion *)widgetQuestion withCompletionHandler:(void(^)(APFeed2EventWidgetQuestion * updatedQuestion))handler;

/**
 Get widget answer ID for widget question
 @return answer ID or nil if not found
 */
- (NSString *)widgetAnswerIDForWidgetQuestionWithID:(NSString *)widgetQuestionID;

/**
 Call when the widget question results need display
 */
- (void)startFetchingUpdatesForWidgetEvent:(APFeed2EventWidgetQuestion *)widgetQuestion;

/**
 Call when the widget question updated results are no longer needed
 */
- (void)stopFetchingUpdatesForWidgetEvent:(APFeed2EventWidgetQuestion *)widgetQuestion;

@end

