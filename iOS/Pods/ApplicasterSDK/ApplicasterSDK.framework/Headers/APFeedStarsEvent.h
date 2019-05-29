//
//  APFeedStarsEvent.h
//  applicaster
//
//  Created by Liviu Romascanu on 8/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <ApplicasterSDK/APFeedEvent.h>

typedef enum {
    APFeedEventTypeGeneric,
    APFeedEventTypeLink,
    APFeedEventTypeQuestionnaire,
    APFeedEventTypeMessage,
    APFeedEventTypeImage,
    APFeedEventTypeVideo,
    APFeedEventTypeQuestion,
    APFeedEventTypeAnswer,
    APFeedEventTypeWidgetQuestion,
}APFeedEventType;

extern NSString * const kAPFeedUniqueIDKey;
extern NSString * const kAPFeedTextKey;
extern NSString * const kAPFeedTimestampKey;
extern NSString * const kAPFeedPromotionLinkKey;
extern NSString * const kAPFeedTypeKey;
extern NSString * const kAPFeedFeedIDKey;
  
@interface APFeedStarsEvent : APFeedEvent
{
    NSMutableDictionary *_object;
}

/**
 json dict
 */
@property (nonatomic, strong) NSDictionary *object;

/**
 Event Unique ID
 */
@property (nonatomic, readonly, strong) NSString *uniqueID;

/**
 Event Message Text
 */
//@property (nonatomic, strong) NSString *text;

/**
 Timestamp parsed to NSDate
 */
@property (nonatomic, readonly, strong) NSDate *timeStamp;

/**
 Timestamp - as received from the server without parsing
 */
@property (nonatomic, readonly, assign) double timeStampServer;

/**
 Unparsed timestamp
 */
@property (nonatomic, readonly, strong) NSString *timeStampString;

/**  
 Feed ID this event belogns to
 */    
@property (nonatomic, readonly, strong) NSString *feedID;

/**
 Feed ID changes by server to NSArray
 */    
@property (nonatomic, readonly, strong) NSArray *feedIDArray;


/**
 Type string from the dictionary object.
 If you need the Type of the object - please use:
 - (APFeedEventType)eventType;
 */
@property (nonatomic, readonly, strong) NSString *typeString;

/**
 Promotion link dictionary.
 Contains the following Keys:
 * url - NSString containing a URL
 * label - NSString containing a label for a corresponding button
 */
@property (nonatomic, readonly, strong) NSDictionary *promotionLink;

/**
 Init with dictionary from JSON
 Be sure to call the correct feed event type object
 */
- (id)initWithDictionary:(NSDictionary *)dictionary;

/**
 Feed Event Type, Could be one of the following:
    APFeedEventTypeGeneric,
    APFeedEventTypeLink,
    APFeedEventTypeQuestionnaire,
    APFeedEventTypeMessage,
    APFeedEventTypeImage,
    APFeedEventTypeVideo,
    APFeedEventTypeQuestion,
    APFeedEventTypeWidgetQuestion
 You should NOT get a generic event - if you do - it's a mistake
 */
- (APFeedEventType)eventType;

/**
 Image Orientations (Landscape or Portrait)
 */
@property (nonatomic, strong) NSString *imageOrientation;

@end
