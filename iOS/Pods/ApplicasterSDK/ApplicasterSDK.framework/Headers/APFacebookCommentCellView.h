//
//  APFacebookCommentCellView.h
//  ApplicasterSDK
//
//  Created by Shimon Shvartsbroit on 8/12/13.
//  Copyright (c) 2013 Applicaster. All rights reserved.
//


@class APFacebookCommentsObject;
@class APImageView;

extern NSString * const kAPFacebookCommentCellViewID;

@interface APFacebookCommentCellView : UICollectionViewCell
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *nameLabel;
@property (unsafe_unretained, nonatomic) IBOutlet APImageView *profilePictureImageView;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *contentLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *timeOfPost;

- (void)setComment:(APFacebookCommentsObject *)comment;

+ (CGSize)cellSizeForText:(NSString*)aText;

@end
