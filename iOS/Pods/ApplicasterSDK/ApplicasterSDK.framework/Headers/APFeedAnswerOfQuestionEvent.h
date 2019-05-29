//
//  APFeedAnswerOfQuestionEvent.h
//  applicaster
//
//  Created by dan g / applicaster on 10/22/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APFeedAnswerOfQuestionEvent : NSObject

/**
 json dict
 */
@property (nonatomic, strong) NSDictionary *object;
@property (nonatomic, strong) NSString *feedback;
@property (nonatomic, strong) NSString *uniqueID;
@property (nonatomic, strong) NSString *wording;
@property (nonatomic, strong) NSString *typeString;
@property (nonatomic, strong) NSDate * timeStamp;
@property (nonatomic, strong) NSString *text;
@property (nonatomic, readonly, strong) NSDictionary *promotionLink; //dummy param
@property (nonatomic, readonly, strong) NSString *feedID; //dummy param

- (id)initWithDictionary:(NSDictionary *)dictionary;
- (id)initWithAnswer:(APFeedAnswerOfQuestionEvent *)answer;

@end
