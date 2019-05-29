//
//  APProgram.h
//  applicaster
//
//  Created by Guy Kogus on 5/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "APModel.h"

@class APCategory;

/**
 Notification that is called when the program is added to local notification center.
 */
extern NSString *const APProgramDidAddLocalNotification;

/**
 Notification that is called when the program is removed from local notification center.
 */
extern NSString *const APProgramDidRemoveLocalNotification;

/**
 A program represents a live program in a channel's EPG. A program is normally loaded from an <APChannel>.
 */
@interface APProgram : APModel
{
    NSDate  *_startsAt;
    NSDate  *_endsAt;
}

@property (nonatomic, strong, readonly) NSString        *name;
@property (nonatomic, strong, readonly) NSString        *programDescription;
@property (nonatomic, strong, readonly) NSString        *liveImageURL;
@property (nonatomic, strong, readonly) NSString        *thumbURL;
@property (nonatomic, strong, readonly) NSString        *imageURL;
@property (nonatomic, strong, readonly) NSString        *mediumURL;
@property (nonatomic, strong, readonly) NSString        *originalURL;
@property (nonatomic, strong, readonly) NSString        *sequenceId;
@property (nonatomic, strong, readonly) NSString        *channelId;
@property (nonatomic, strong, readonly) NSString        *vodItemId;

@property (nonatomic, strong, readonly) APCategory      *showCategory;

@property (nonatomic, strong, readonly) NSDate          *startsAt;
@property (nonatomic, strong, readonly) NSDate          *endsAt;
@property (nonatomic, readonly) BOOL                    isLive;

@property (nonatomic, strong, readonly) NSString        *color;

/**
 Checks if the program has a reminder scheduled.
 */
@property (nonatomic, readonly, getter = isLocalNotificationScheduled) BOOL localNotificationScheduled;

/**
 Sets a local notification sound, setting a new local notification sound will change only the sounds of local notification that will be scheduled in the future. The default sound is "default.wav".
 */
@property (nonatomic, assign) NSString *localNotificationSound;

/**
 This method checks if the program's start date is before now and the end date is after now.
 @return YES if the program is currently playing.
 */
- (BOOL)isPlaying;

/**
 This method checks if the program's end date is after now.
 @return YES if the program is already ended.
 */
- (BOOL)didEnd;

/**
 This method adds a local notification to the program which should take place in the future.
 In order use localization in the alert fields (alert body and the action button) use the following keys:
 APProgramLocalNotificationAlertBody - localization for the alert body.
 APProgramLocalNotificationAlertAction - localization for the action button.
 */
- (void)addLocalNotification;

/**
 This method removes the local notification from the program, if the program has a scheduled reminder.
 */
- (void)removeLocalNotification;

@end
