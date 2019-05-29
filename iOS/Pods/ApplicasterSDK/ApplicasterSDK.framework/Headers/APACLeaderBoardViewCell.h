//
//  APACLeaderBoardViewCell.h
//  applicaster
//
//  Created by Miri on 7/10/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

extern NSString *const kAPACLeaderBoardViewCell;

@class APImageView;

@interface APACLeaderBoardViewCell : UICollectionViewCell

/*
 userDict - data of user.
 */
@property (nonatomic, weak) NSDictionary *userDict;
/*
 userName.
 */
@property (nonatomic, weak) IBOutlet UILabel *userName;

/*
 score..
 */
@property (nonatomic, weak) IBOutlet UILabel *score;

/*
 avatarImageView.
 */
@property (nonatomic, weak) IBOutlet APImageView *avatarImageView;

/*
 rank.
 */
@property (nonatomic, weak) IBOutlet UILabel *rank;

/*
 RankBackgroundView
 */
@property (nonatomic, weak) IBOutlet UIView *rankBackgroundView;

/*
 winImageView - icon for first user in the leader board.
 */
@property (nonatomic, weak) IBOutlet UIImageView *winImageView;

@end
