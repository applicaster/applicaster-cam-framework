//
//  APCMCharacter.h
//  applicaster
//
//  Created by dan g / applicaster on 10/2/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APFeedFeed.h"

@interface APCMCharacter : APFeedFeed

/**
 Boolaen indicated whether character was chosen
 */
@property (nonatomic, assign) BOOL IsChosen;

/**
 Character events 
 */
@property (nonatomic, strong) NSMutableArray *events;

/**
 Last date in seconds since recieved the last event. this time stamp is reset when user change character becasue the reuirement ask to recieve events only when friend so a gap occured while unfriend.
 */
@property (nonatomic, assign) NSTimeInterval lastTimeStampEventWasRecieved;

/**
 Date of last message which derived from lastTimeStampEventWasRecieved
 */
@property (nonatomic, strong) NSDate *dateOfLastMessage;

/**
 Number of events user is missed. maximum is server response events per request
 */ 
@property (nonatomic, assign) NSInteger numberOfEventsMissed;

/**
character's timelineID
 */
@property (nonatomic, strong) NSString *timelineID;

/**
 Load events of character
 */
- (void)getMyEventsWithComplitionHandler:(void (^)(BOOL succeed, NSInteger eventsCounter))complition;

/**
 If user was friends before this boolean is yes. pay attention that this can be yes and also isChosen as well
 */
@property (nonatomic, assign) BOOL isExFriend;

/**
 refill character when loading feed again. this is for param change like name, etc.
 */
- (void)fillWithData:(NSDictionary *)object;

@end