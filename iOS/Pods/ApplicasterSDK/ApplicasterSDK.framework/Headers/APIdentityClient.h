//
//  APIdentityClient.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 21/03/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class is used to manage identity in various places.
 This identity is used agains the applicaster servers as a de-facto replacement of the Apple identifier parameter.
 
 This identifier is unique identifier supplied by the server and stored in a persistent way in the keychain.
 */
@interface APIdentityClient : NSObject

/**
 Initializes and returns a singleton instance of the API.
 If shared instance exists - just sets the bucket ID
 @param bucketID The bucket ID for the app's AIS account bucket.
 @return The (new) shared identity client.
 */
+ (instancetype)sharedInstanceWithBucketID:(NSString *)bucketID;

/**
 The unique identifier for this user.
 @return The unique identifier if one has been generated. <code>nil</code> otherwise.
 */
+ (NSString *)deviceID;

/**
 The token for this user.
 @return The token if one has been generated or <code>nil</code> if the latest token has expired or if none have been generated.
 */
+ (NSString *)token;

/**
 @return The current bucket ID.
 */
+ (NSString *)bucketID;

/**
 @return pushTags
 */
+ (NSArray *)pushTags;

/**
 Create / Get new device unique identifier and token
 @param onlineConnectivityAvilable - YES if currently Online , No otherwise
 @param success - block to be run in case of success
 @param failure - block to be run in case of failure
 */
+ (void)createDeviceWhileOnline:(BOOL)onlineConnectivityAvilable 
                     withSucces:(void (^)(NSString *uuid, NSString *token))success 
                    withFailure:(void (^)(NSError *error))failure;
/**
 Try to generate a new session token.
 Later implementation should store the current session token and check for its expiration and only then decide if to fetch a new session token.
 @param success - function to be run in case of success
 @param failure - function to be run in case of failure
 */

+ (void)createSessionWithSucces:(void (^)(NSString *session))success 
                    withFailure:(void (^)(NSError *error))failure;

/**
 Update the last time seen in crossmates feature
 This function will send the request to the server only once per 24 hours
 @param success - function to be run in case of success - Message recieved at the server successfully
 @param failure - function to be run in case of failure - Either message failed or already sent in the past 24 hours
 */
+ (void)updateCrossMatesLastSeenAtWithSuccess:(void (^)(void))success
                                  withFailure:(void (^)(void))failure;

/**
 Update the last time seen in feed feature
 This function will send the request to the server only once per 24 hours
 @param success - function to be run in case of success - Message recieved at the server successfully
 @param failure - function to be run in case of failure - Either message failed or already sent in the past 24 hours
 */
+ (void)updateFeedLastSeenAtWithSuccess:(void (^)(void))success
                            withFailure:(void (^)(void))failure;

/**
 Push Notification Functions
 */

/**
 Register for push notifications agains the AIS server
 @param token - APNS token
 */
+ (void)registerForPushNotificationWithToken:(NSData *)token;

/**
 Add Push tag to device
 */
+ (void)addTagToDevice:(NSString *)tag;

/**
 Remove Push tag from device
 */
+ (void)removeTagFromDevice:(NSString *)tag;

@end
