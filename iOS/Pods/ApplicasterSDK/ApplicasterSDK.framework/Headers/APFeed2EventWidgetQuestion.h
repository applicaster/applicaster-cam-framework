//
//  APFeed2EventWidgetQuestio.h
//  applicaster
//
//  Created by Hagit Shemer on 2/9/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import "APFeedEventImage.h"

@interface APFeed2EventWidgetQuestion : APFeedEventImage
/**
 Question ID for communication with server (in addition to the event unique id)
 */
@property (nonatomic, strong) NSString *questionID;

@property (nonatomic, strong) NSDictionary *widgetQuestionDictionary;
@property (nonatomic, strong, readonly) NSDate *endsAt;
@property (nonatomic, strong, readonly) NSURL *answersURL;
@property (nonatomic, assign, readonly) BOOL isTakeOver;
@property (nonatomic, assign, readonly) BOOL isPoll;
/**
 Unique ID of the answer chosen by the user - nil if the user hasn't chosen yet
 */
@property (nonatomic, strong) NSString *chosenAnswerID;

/**
 Array of APFeed2EventWidgetAnswer objects
 */
@property (nonatomic, strong) NSArray *answers;

@end
