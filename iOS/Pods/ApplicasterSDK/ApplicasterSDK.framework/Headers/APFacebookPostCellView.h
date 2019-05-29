//
//  APFacebookPostCellView.h
//  ApplicasterSDK
//
//  Created by Shimon Shvartsbroit on 8/5/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <TTTAttributedLabel/TTTAttributedLabel.h>

extern NSString * const kAPFacebookPostCellViewID;

@class APFacebookPostObject, APImageView, TTTAttributedLabel;


@protocol APFacebookPostCellDelegate

@required

- (void)likeTappedForPost:(APFacebookPostObject *)post withCompletionHandler:(void(^)(BOOL success))handler;
- (void)commentTappedForPost:(APFacebookPostObject *)post;
- (void)mediaTappedForPost:(APFacebookPostObject *)post;

@end


#pragma mark -


@interface APFacebookPostCellView : UICollectionViewCell <TTTAttributedLabelDelegate>

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *userNameLabel;

@property (unsafe_unretained, nonatomic) IBOutlet APImageView *avatarImageView;

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *dateLabel;

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *messageLabel;

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *likesCountLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *commentsCountLabel;

@property (unsafe_unretained, nonatomic) IBOutlet APImageView *thumbnailImageView;
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *playButton;

@property (unsafe_unretained, nonatomic) IBOutlet TTTAttributedLabel *linkLabel;

@property (unsafe_unretained, nonatomic) IBOutlet UIButton *likeButton;

@property (unsafe_unretained, nonatomic) IBOutlet UIButton *commentButton;

@property (unsafe_unretained, nonatomic) IBOutlet UIButton *imageThumbnailButton;

@property (unsafe_unretained, nonatomic) IBOutlet UIView *likesAndCommentsLabelView;

@property (nonatomic) BOOL hideLikesAndCommentsLabel;

@property (nonatomic, strong) APFacebookPostObject* post;

@property (nonatomic, assign) id<APFacebookPostCellDelegate> fbCellDelegate;

- (IBAction)imageTapped:(id)sender;
- (IBAction)playTapped:(id)sender;

- (IBAction)likeTapped:(id)sender;
- (IBAction)commentTapped:(id)sender;

+(CGSize)sizeOfFacebookPostObject:(APFacebookPostObject *)post hideLikesAndCommentsLabel:(BOOL)hideLikesAndCommentsLabel withCompletionHandler:(void(^)(CGRect linkFrame, CGRect messageFrame, CGFloat totalHeightOffset))handler;

@end
