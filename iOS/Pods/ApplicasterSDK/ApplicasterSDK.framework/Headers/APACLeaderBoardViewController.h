//
//  APLeaderBoardViewController.h
//  applicaster
//
//  Created by Miri on 7/10/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APSwitcherView.h"

@class APSwitcherView, APImageView, APButton;

@interface APACLeaderBoardViewController : UIViewController <APSwitcherViewDelegate,UICollectionViewDataSource,UICollectionViewDelegate,UICollectionViewDelegateFlowLayout>

//Top bar view
@property (nonatomic, weak) IBOutlet UIView *topBarView;
@property (nonatomic, weak) IBOutlet UILabel *leaderboardTitleLabel;
@property (nonatomic, weak) IBOutlet APButton *backButton;
@property (nonatomic, weak) IBOutlet APButton *actionsButton;

//My cell
@property (nonatomic, weak) IBOutlet UIView *userCellView;
@property (nonatomic, weak) IBOutlet UILabel *myName;
@property (nonatomic, weak) IBOutlet APImageView *myAvatar;
@property (nonatomic, weak) IBOutlet UILabel *myRank;
@property (nonatomic, weak) IBOutlet UILabel *myScore;
@property (nonatomic, weak) IBOutlet UILabel *kSign;
@property (nonatomic, weak) IBOutlet UILabel *plusSign;
@property (nonatomic, weak) IBOutlet UIView *rankBackgroundView;

/*
 PagesCollectionView - pages collectionView - for switcher.
 */
@property (nonatomic,strong) IBOutlet UICollectionView *pagesCollectionView;

/*
 SwitcherView - for general or friends leaderBoard.
 */
@property (nonatomic, weak) IBOutlet APSwitcherView *switcherView;

/*
 ChallengeID - challenge id of leaderBoard.
 */
@property (nonatomic,strong) NSString *challengeID;

/*
 Constraints.
 */
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *topBarConstraint;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *hightTopBarConstraint;

-(void)updateUserData;

/*
 
 */
- (id)initWithTitle:(NSString *)title;

/*
 
 */
-(void)reloadLeaderBoardWithCompletionHandler:(void (^)(BOOL success))handler;

@end
