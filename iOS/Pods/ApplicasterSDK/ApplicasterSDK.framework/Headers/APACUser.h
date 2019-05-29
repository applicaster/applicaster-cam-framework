//
//  APAchievementUser.h
//  applicaster
//
//  Created by Miri on 6/23/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SHMKit/SHMEntity.h>

@interface APACUser : SHMEntity

/**
 json dict
 */
@property (nonatomic, strong) NSDictionary *object;

/**
 userParams - contains user data.
 */
@property (nonatomic, strong) NSMutableDictionary *userParams;

/**
 User Account ID - of the Broadcaster, from accounts.applicaster.com
 */
@property (nonatomic, strong, readonly) NSString *accountID;

/**
 External ID - the user_id in a different system, AIS -> UUID for now.
 */
@property (nonatomic, strong, readonly) NSString *deviceID;

/**
 User Name
 */
@property (nonatomic, strong, readonly) NSString *name;

/**
 SocialUid - which is the user's social_uid for example -> facebook_uid.
 */
@property (nonatomic, strong, readonly) NSString *socialUid;

/**
 FriendsIds - which is an array of all the social_uids of his friends. NOTE: the values here must be from the same social network as the social_uid.
 */
@property (nonatomic, strong, readonly) NSArray *friendsIds;

/**
 Profile picture url - the url for the user's picture.
 */
@property (nonatomic, strong, readonly) NSString *profilePictureUrl;

/**
 TotalScore - the total score of user.
 */
@property (nonatomic, strong) NSNumber *totalScore;

/**
 Rank - the rank of user.
 */
@property (nonatomic, strong) NSNumber *rank;

/**
 Update user - action.
 */
@property (nonatomic, strong, readonly) SHMAction *updateUserAction;

/**
 Get parameters of user.
 @param - handler - return dictionary of user paramaters. 
 */
- (void)getUserDataWithCompletionHandler:(void (^)(BOOL, NSDictionary *userDict))handler;
@end
