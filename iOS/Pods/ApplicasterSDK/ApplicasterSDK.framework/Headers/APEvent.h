//
//  APEvent.h
//  applicaster
//
//  Created by Liviu Romascanu on 2/17/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import "APModel.h"

/**
 The following enum represents Event type
 */
typedef enum{
	APEventTypeURL,
    APEventTypeQuestionnaire,
	APEventTypeImage,
	APEventTypeVideo,
}APEventType;

@interface APEvent : APModel <NSCopying>

/**
 Name of the event
 */
@property (nonatomic, strong, readonly) NSString        *name;

/**
 Type of the event - defined by APEventType
 */
@property (nonatomic, assign, readonly) APEventType     type;

/**
 event type string
 Used for analytics
 */
@property (nonatomic, strong , readonly) NSString *typeString;

/**
 Delta in seconds from the episode beginning
 */
@property (nonatomic, assign, readonly) NSTimeInterval  startsAt;

/**
 Duration of the event - in seconds
 */
@property (nonatomic, assign, readonly) NSTimeInterval  duration;

/**
 URL dictionary of the metadata of the event.
 used for APTimedWebViewController
 */
@property (nonatomic, strong, readonly) NSDictionary        *urlDictionary;

/**
 Thumbnail image of the event - Not implemented on the server side and currently not used
 */
@property (nonatomic, strong, readonly) NSString        *image;

/**
 Description of the event
 */
@property (nonatomic, strong, readonly) NSString        *eventDescription;

/**
 Facebook Share enabled
 */
@property (nonatomic, assign, readonly) BOOL  facebookShare;

/**
 Twitter Share enabled
 */
@property (nonatomic, assign, readonly) BOOL  twitterShare;

/**
 Description of the event
 */
@property (nonatomic, strong, readonly) NSString        *caption;

/**
 Twitter Share enabled
 */
@property (nonatomic, assign, readonly) BOOL  hidden;

/**
 Image URL - Only for image event
 */
@property (nonatomic, strong, readonly) NSString *imageURL;

/**
 VOD item ID.
 This is only relevant for Video event
 */
@property (nonatomic, strong, readonly) NSString *vodItemID;

/**
 Preview Image URL
 This is only relevant for Video event
 */
@property (nonatomic, strong, readonly) NSString *previewImageURL;

@end
