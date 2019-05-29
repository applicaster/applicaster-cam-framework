//
//  APNotificationManager.h
//  APPLICASTER
//
//  Created by Tom Susel on 11/14/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
//  Modified By Liviu From BigBrother 3 to Applicaster framework

#import <Foundation/Foundation.h>

extern NSString *const APAppoxeeBadgeUpdateNotification;

extern NSString *const kAPNotificationsAppoxeeKey;
extern NSString *const kAPNotificationsApplicasterKey;
extern NSString *const kAPPushNotificationReceived;

/**
local notification should be send with type so the application can handle it correctly
 */
extern NSString *const kAPLocalNotificationsType;
extern NSString *const kAPLocalNotificationsTypeReminderEPG;
/**
 When the application receives local notifications, you can find dictionary with extra info in it's userInfo under this key.
 */
extern NSString *const kAPLocalNotificationsExtraInfo;

/**
 The notification manager is responsible for handling all push notification registration and receiving.
 */
@interface APNotificationManager : NSObject {
	NSURLConnection *_registrationConnection;
	NSURLConnection *_unregisterConnection;
}

@property (nonatomic, copy) NSString *pushEngine;

@property (nonatomic, copy) NSString *username;
@property (nonatomic, copy) NSString *password;

@property (nonatomic, strong) NSData *pushToken;

/**
 *  handle push java script command with options and return callBack block.
 *
 *  @param command   JS command
 *  @param options   Dictionary that contains all the command options
 *  @param callBlock - This callBlock has no return value and has one argument, the argument will return Dictonary.
 */
- (void)handlePushJSCommand:(NSString *)command
                    options:(NSDictionary *)options
                  callBlock:(void (^)(NSDictionary *parameters))callBlock;

/**
 Prepeare the APNotification center for push notifications. if the push notification screen is Appoxee, and also we don't want it to fill all screen, we can send the wanted delta that we want the appoxee want stretch over there.
 This should be run after setting the push engine and the username / password data
 */
- (void)prepareForPushNotificationWithAppoxeeHeight:(NSInteger)delta;

/**
 Prepeare the APNotification center for push notifications.
 This should be run after setting the push engine and the username / password data
 */
- (void)prepareForPushNotification;

/**
 Register Token with push server
 @param aToken The device's push token in NSData form.
 */
- (void)registerToken:(NSData *)aToken;

/**
 Register for remote notifications
 */
- (void)registerForRemoteNotifications;

#pragma mark Push Tags

/**
 * Add tags to device
 * And remove tags from device
 * @param tags - NSArray of NSStrings of the selected tags
 * @param provider - Push provider
 * @param completionBlock - This completionBlock has no return value and has one argument, the argument will return BOOL success. YES if the request was successful without any error. NO if the request had error.
 *
 */
- (void)addTagsToDevice:(NSArray *)tags
               provider:(NSString *)provider
      complitationBlock:(void (^)(BOOL success))completionBlock;
/**
 * And remove tags from device
 * @param tags - NSArray of NSStrings of the selected tags
 * @param provider - Push provider
 * @param completionBlock - This completionBlock has no return value and has one argument, the argument will return BOOL success. YES if the request was successful without any error. NO if the request had error.
 *
 */
- (void)removeTagsFromDevice:(NSArray*)tags
                    provider:(NSString *)provider
           complitationBlock:(void (^)(BOOL success))completionBlock;
/**
 * Get device's tag list from the server
 * @param provider - Push provider
 * @param completionBlock - This completionBlock has no return value and has one argument, the argument will return Array of strings.
 *
 */
- (void)getDeviceTagsForProvider:(NSString *)provider
               complitationBlock:(void (^)(NSArray *tags))completionBlock;
/**
 * Get App's tag list from the server
 * @param provider - Push provider
 * @param completionBlock - This completionBlock has no return value and has one argument, the argument will return Array of strings.
 *
 */
- (void)getTagListForProvider:(NSString *)provider
            complitationBlock:(void (^)(NSArray *tags))completionBlock;
/**
 * Clear tags local cache
 * @param provider - Push provider
 *
 */
- (void)clearTagsCacheForProvider:(NSString *)provider;


#pragma mark

/**
 Handle Push events during up runtime
 @param userInfo The raw dictionary sent in the remote notification.
 @param launchedApplication If YES, the application was off or inactive when the notification was received. This indicates that the application was opened in response to the push notification.
 */
- (void)appDidReceiveRemoteNotification:(NSDictionary *)userInfo launchedApplication:(BOOL)launchedApplication;

/**
 Handles Local notification events that are called from appDelegate.
 @param localNotification The localNotification that called the event.
 @param launchedApplication If YES, the application was off or inactive when the notification was received. This indicates that the application was opened in response to the push notification.
 */
- (void)appDidReceiveLocalNotification:(UILocalNotification *)localNotification launchedApplication:(BOOL)launchedApplication;

/**
 Adds a local notification for notification key and uniqueID.
 @param notificationKey - The notification key, used to define the type of the notifications.
 @param uniqueID - The unique ID of the object that adds the local notification.
 @param alertBody The message body.
 @param alertAction The approval button of the alert view (if defined as alert view.
 @param fireDate The execute date of the local notification.
 @param actionScheme The url scheme that will called when tapping the alert/notification message.
 @param extraInfo Dictionary that will be received in the local notification. This dictionary will be put in the notification's userInfo under kAPLocalNotificationsExtraInfo key.
 */
- (void)addLocalNotificationForNotificationKey:(NSString *)notificationKey
                                  withUniqueID:(NSString *)uniqueID
                                     alertBody:(NSString *)alertBody
                                   alertAction:(NSString *)alertAction
                                      fireDate:(NSDate *)fireDate
                                  actionScheme:(NSString *)actionScheme
                                          type:(NSString *)type
                                     extraInfo:(NSDictionary *)extraInfo;
/**
 Removes the local notification for notification key and uniqueID.
 @param notificationKey - The notification key, used to define the type of the notifications.
 @param uniqueID - The unique ID of the object that adds the local notification.
 */
- (void)removeLocalNotificationForNotificationKey:(NSString *)notificationKey
                                     withUniqueID:(NSString *)uniqueID;
/**
 Checks if there is a local notification with notification key and uniqueID.
 @param notificationKey - The notification key, used to define the type of the notifications.
 @param uniqueID - The unique ID of the object that adds the local notification.
 */
- (BOOL)isLocalNotificationScheduledForNotificationKey:(NSString *)notificationKey
                                          withUniqueID:(NSString *)uniqueID;

/**
 Sets a sound for local notification, setting a new local notification sound will change only the sounds of local notifications that will be scheduled in the future. 
 The default sound is "default.wav".
 */
@property (nonatomic, assign) NSString *localNotificationSound;

@end
