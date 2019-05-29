//
//  APAchievementChallenge.h
//  applicaster
//
//  Created by Miri on 6/23/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SHMKit/SHMEntity.h>

@interface APACChallenge : SHMEntity

/**
 json dict
 */
@property (nonatomic, strong) NSDictionary *object;

/**
 ChallengeDict - contains mandatory fields of challenge (arn, isActive, is Completed).
 */
@property (nonatomic, strong) NSDictionary *challengeDict;

/**
 Id of challenge
 */
@property (nonatomic, strong, readonly) NSString *challengeId;

/**
 Name of challenge
 */
@property (nonatomic, strong, readonly) NSString *name;

/**
 Title
 */
@property (nonatomic, strong, readonly) NSString *challengeTitle;

/**
 Description.
 */
@property (nonatomic, strong, readonly) NSString *description;

/**
 Archived At.
 */
@property (nonatomic, strong, readonly) NSString *archivedAt;

/**
 Challenge start time
 */
@property (nonatomic, strong, readonly) NSString *startsAt;

/**
 Challenge end time
 */
@property (nonatomic, strong, readonly) NSString *endAt;

/**
 Challenge image url.
 */
@property (nonatomic, strong, readonly) NSString *imageUrl;

/**
 Array of actions that give score.
 */
@property (nonatomic, strong, readonly) NSArray *actionsArray;

/**
 User data - action.
 */
@property (nonatomic, strong, readonly) SHMAction *userDataAction;

/**
 Create user - action.
 */
@property (nonatomic, strong, readonly) SHMAction *createUserAction;

/**
 Friends leaderboard - action.
 */
@property (nonatomic, strong, readonly) SHMAction *friendLeaderboardAction;

/*
 Return YES if action is enabled, by the action name, else - return NO.
 @param: actionName.
 */
- (BOOL)actionIsEnabled:(NSString *)actionName;

/*
 Return YES if action is visible, by the action name, else - return NO.
 @param: actionName.
 */
- (BOOL)actionIsVisible:(NSString *)actionName;

/*
 Return the score of action by the action name.
 @param: actionName.
 */
- (NSString *)scoreOfActionName:(NSString *)actionName;

@end
