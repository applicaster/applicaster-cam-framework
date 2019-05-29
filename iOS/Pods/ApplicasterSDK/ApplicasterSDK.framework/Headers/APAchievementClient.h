//
//  APAchievementClient.h
//  applicaster
//
//  Created by Miri on 6/24/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SHMEntity;

@interface APAchievementClient : NSObject

/**
 Load base end point.
 @param accountId -  of the Broadcaster, from accounts.applicaster.com.
 @param handler that receives an entity of base end point.
 @param error
 */
- (void)loadBaseEndPointWithAccountId:(NSString *)accountId WithCompletionHandler:(void (^)( SHMEntity *entity, NSError *error))handler;

/**
 Put user - create user.
 @param url from links array of entity.
 @param responsObject - contains parameters of user (account_id, facebook params if user login)
 @param error
 */
- (void)putUserByUrl:(NSString *)url withParameters:(NSDictionary *)parameters withCompletionHandler:(void(^)(id responseObject, NSError *error))handler;

/**
 Update user by url.
 @param url - from links array of entity.
 @param parameters - dictionary with parameters of user (account_id, device_id)
 @param error
 */
- (void)updateUserByUrl:(NSString *)url method:(NSString *)methodType withParameters:(NSDictionary *)parameters withCompletionHandler:(void(^)(id responseObject, NSError *error))handler;

/**
 Get data of challenges.
 @param url .
 @param parameters - dictionary of relevant parameters.
 @param error
 */
- (void)getDataWithUrl:(NSString *)url parameters:(NSDictionary *)parameters withCompletionHandler:(void (^)(id responseObject, NSError *error))handler;

/**
 Create user action by url.
 @param url - from links array of entity.
 @param parameters - dictionary with parameters of user action (account_id, action_name)
 @param error
 */
- (void)createUserActionByUrl:(NSString *)url withParameters:(NSDictionary *)parameters withCompletionHandler:(void(^)(SHMEntity *responseObject, NSError *error))handler;

@end
