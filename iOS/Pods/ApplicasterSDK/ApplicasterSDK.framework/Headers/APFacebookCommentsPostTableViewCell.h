//
//  APFacebookCommentsPostTableViewCell.h
//  ApplicasterSDK
//
//  Created by Liviu Romascanu on 10/10/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APFacebookCommentsPostTableViewCell;

@class APImageView;
/**
 The delegate responds to a cell requesting another comment to be added for its post.
 */
@protocol APFacebookCommentsPostTableViewCellDelegate <NSObject>

/**
 This informs the delegate that UI should appear for commenting on the cell's post.
 N.B. The cell's <post> object must be of type <APFacebookCommentsObject> for this to be possible.
 @param cell The cell whose post is going to be comment upon.
 */
- (void)commentsButtonTappedForFacebookCommentsPostTableViewCell:(APFacebookCommentsPostTableViewCell *)cell;

/**
 This informs the delegate that the cell wants to update it's Like value.
 N.B. The cell's <post> object must be of type <APFacebookCommentsObject> for this to be possible.
 @param cell The cell whose post is being liked/unliked.
 @param completionHandler The handler that informs success or failure.
 */
- (void)likeButtonTappedForFacebookCommentsPostTableViewCell:(APFacebookCommentsPostTableViewCell *)cell
									   withCompletionHandler:(void(^)(BOOL success))completionHandler;

@end

@class APFacebookCommentsObject;

@interface APFacebookCommentsPostTableViewCell : UITableViewCell

@property (unsafe_unretained, nonatomic) IBOutlet APImageView *profileImageView;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *nameLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *messageLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *timeDescriptionLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *likeButton;
@property (unsafe_unretained, nonatomic) IBOutlet UIButton *commentButton;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *likeCountLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UILabel *messageCountLabel;
@property (unsafe_unretained, nonatomic) IBOutlet UIView *commentsActionBar;

@property (nonatomic, strong) APFacebookCommentsObject *post;
@property (nonatomic, unsafe_unretained) id <APFacebookCommentsPostTableViewCellDelegate> commentsDelegate;

@property (nonatomic, assign) BOOL liked;

- (IBAction)likeButtonClicked:(UIButton *)sender;
- (IBAction)commentButtonClicked:(id)sender;

/**
 Calculates the height for a standard cell. This is assuming the width taken from the XIB.
 @param text The text being measured.
 @return The height of the cell.
 */
+ (CGFloat)heightForCellForText:(NSString *)text;

@end
