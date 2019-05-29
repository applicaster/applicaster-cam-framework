//
//  APACLeaderBoardPageViewCell.h
//  applicaster
//
//  Created by Miri on 7/10/14.
//  Copyright (c) 2014 Applicaster Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

extern NSString *const kAPACLeaderBoardPageViewCell;

@class APButton, APImageView;

/*
 Type - the type of presentation of leaderboard,
 APACLeaderboardTypeGlobal - global leaderboard.
 APACLeaderboardTypeFriends - user's friends leaderboard.
 APACLeaderboardTypeNotFriends - the user has no friends in the leaderboard.
 APACLeaderboardTypeNotConnectToFB - the user is not logged in to facebook.
 */

typedef NS_ENUM (NSInteger, APACLeaderBoardType){
    APACLeaderboardTypeGlobal = 0,
    APACLeaderboardTypeFriends,
    APACLeaderboardTypeNotFriends,
    APACLeaderboardTypeNotConnectToFB
};

@interface APACLeaderBoardPageViewCell : UICollectionViewCell <UICollectionViewDataSource,UICollectionViewDelegate,UICollectionViewDelegateFlowLayout>

@property (nonatomic) APACLeaderBoardType type;

/*
 Title of leaderboard.
 */
@property (nonatomic, strong) NSString *leaderboardTitle;

/*
 UsersCollectionView - leaderBoard collectionView with the users.
 */
@property (nonatomic,weak) IBOutlet UICollectionView *usersCollectionView;

/*
 Container view for collection animation.
 */
@property (nonatomic, strong) IBOutlet UIView *usersCollectionContainer;

/*
 Spinner.
 */
@property (nonatomic, weak) IBOutlet UIActivityIndicatorView *spinner;

/*
 LoginFBView - logIn to facebook view - present when user not connected to facebook.
 */
@property (nonatomic, weak) IBOutlet UIView *loginFBView;
@property (nonatomic, weak) IBOutlet APImageView *loginFBImageView;
@property (nonatomic, weak) IBOutlet UILabel *loginFBTitle;
@property (nonatomic, weak) IBOutlet APButton *loginFBButton;
@property (nonatomic, weak) IBOutlet UILabel *loginFBLabel;

/*
 ShareView - present when the user is connected to facebook but has no friends.
 */
@property (nonatomic, weak) IBOutlet UIView *shareView;
@property (nonatomic, weak) IBOutlet UILabel *shareLabel;
@property (nonatomic, weak) IBOutlet UILabel *noFriendsLabel;

/*
 UsersArray - array of users in the leaderBoard.
 */
@property (nonatomic,weak) NSArray *usersArray;

/*
 isFriends -
 */
@property (nonatomic) BOOL isFriends;

/*
 Constrains of collection view and container view for animation.
 */
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *containerViewHeightConstraint;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *collectionViewHeightConstraint;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *containerViewBottomConstraint;

/*
 CollectionView animation
 */
- (void)collectionViewAnimationShow;

/*
 Login to facebook.
 */
- (IBAction)loginFBButtonTaaped:(id)sender;

/*
 Open share popup
 */
- (IBAction)shareButtonTaaped:(id)sender;

- (void)pageDidAppear;

@end
