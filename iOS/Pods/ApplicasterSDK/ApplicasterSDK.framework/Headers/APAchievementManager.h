//
//  APAchievementManager.h
//  applicaster
//
//  Created by Miri on 6/25/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@class APACLeaderBoard;

extern NSString *const kAPAchievementUserAction;

extern NSString *const kAPfeedItemLike;
extern NSString *const kAPfeedItemShare;
extern NSString *const kAPfeedFacebookPost;
extern NSString *const kAPfeedFacebookComment;
extern NSString *const kAPfeedTwitterPost;
extern NSString *const kAPfeedTwitterRetweet;
extern NSString *const kAPfeedVideoWatch;
extern NSString *const kAPfeedPollAnswer;
extern NSString *const kAPfeedTriviaAnswerCorrect;
extern NSString *const kAPfeedPredectionAnswerCorrect;
extern NSString *const kAPfeedFacebookLogin;
extern NSString *const kAPWelcomeBackAction;

extern NSString *const kAPAchievementCenterPresentLeaderBoard;
extern NSString *const kAPAchievementCenterUpdateLeaderBoard;
extern NSString *const kAPAchievementCenterPresentWinnerScreen;
extern NSString *const kAPAchievementCenterPresentWelcomeScreen;
extern NSString *const kAPAchievementCenterPresentWelcomeBackScreen;
extern NSString *const kAPAchievementCenterShowHowToPlayPopup;
extern NSString *const kAPAchievementCenterHideHowToPlayPopup;
extern NSString *const kAPAchievementCenterUpdateUserScore;
extern NSString *const kAPAchievementCenterUpdateUserData;
extern NSString *const kAPAchievementCenterGetChallenge;

extern NSString *const kAPAchievementCenterChallengeID;
extern NSString *const kAPAchievementCenterIsFirstTimePresentLeaderBoard;
extern NSString *const kAPAchievementCenterIsFirstPresentTimeWelcomeBack;

@class APACUser;
@class APACChallenge;
@class APAchievementCustomization;

@interface APAchievementManager : NSObject

@property (nonatomic,strong) APACUser *userEntity;
@property (nonatomic,strong) APACChallenge *challengeEntity;
@property (nonatomic,strong) APACLeaderBoard *leaderBoardEntity;

/*
 Currently the customization taken from the feed , in the future will be a separate API for Achievement center.
 */
@property (nonatomic,strong) APAchievementCustomization *achievementTheme;

/**
 ARN - Applicaster Resource Name - uniquely identify applicaster resources.
*/
@property (nonatomic, strong) NSString *arn;

/**
 IsAchievementMode - if is the achievement center mode return YES, else - return NO.
 */
@property (nonatomic, assign) BOOL isAchievementMode;

/**
 Init shared manager with accountID
 @param:accountID - accounts.acountiID (AIS).
 */
+ (id)initSharedManagerWithAccountID:(NSString *)accountID;

/**
 SharedManager.
 */
+ (APAchievementManager *)sharedManager;

/*
 Load base end point.
 @param handler that receives success if succeeded, else - if not.
 */
- (void)loadBaseEndPointWithCompletionHandler:(void (^)(BOOL success))handler;

/*
 Check if present feed with achievement center mode by mandetory params. return BOOL value - YES if present the challenge, else - return NO.
 @param: refs - NSArray that contains timeline id.
 @param: isActive - "true" - return the active challenges, "false" - return challenges not active.
 @param: isCompleted - "true" - return the completed challenges, "false" - return challenges not completed.
 */
- (void)isPresentAchievementInTimeLine:(NSString *)refs isActive:(NSString *)isActive isCompleted:(NSString *)isCompleted withCompletionHandler:(void (^)(BOOL success))handler;

/*
 Get list of challenges.
 @param : challengeParams - mandetory parameters of challenge (refs,isActive,isCompleted).
 @param handler that receives success if succeeded, else - if not.
 */
- (void)challengesList:(NSDictionary *)challengeParams withCompletionHandler:(void (^)(BOOL success))handler;

/*
 Get challenge with challenge id.
 @param : challengeId.
 @param handler that receives success if succeeded, else - if not.
 */
- (void)challengeWithChallengeId:(NSString *)challengeId withCompletionHandler:(void (^)(BOOL success))handler;

/*
 Get leader board  of challenge.
 @param : challengeId.
 @param : isAllTime
 @param : isFreinds - YES - return friend users in the leaderBoard, else return all the users.
 @param handler that receives success if succeeded, else - if not.
 */
-(void)leaderBoardInMode:(BOOL)isFriends withCompletionHandler:(void (^)(BOOL success, id responseObject))handler;

/*
 Get score and rank of user.
 @param handler that receives success if succeeded, else - if not.
 */
- (void)updateUserDataWithCompletionHandler:(void (^)(BOOL success))handler;

@end
