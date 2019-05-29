//
//  APAchievementLeaderBoard.h
//  applicaster
//
//  Created by Miri on 7/10/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SHMKit/SHMEntity.h>

@interface APACLeaderBoard : SHMEntity

/**
 json dict
 */
@property (nonatomic, strong) NSDictionary *object;

/**
 User Account ID - of the Broadcaster, from accounts.applicaster.com
 */
@property (nonatomic, strong, readonly) NSString *accountID;

/**
 Id of challenge
 */
@property (nonatomic, strong, readonly) NSString *challengeId;

/**
 Users array - array of users in leader board
 */
@property (nonatomic, strong, readonly) NSArray *leaderBoardArray;

@end
