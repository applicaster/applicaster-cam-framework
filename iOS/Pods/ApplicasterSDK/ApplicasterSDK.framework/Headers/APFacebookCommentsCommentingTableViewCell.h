//
//  APFacebookCommentsCommentingTableViewCell.h
//  ApplicasterSDK
//
//  Created by Guy Kogus on 6/12/12.
//  Copyright (c) 2012 Applicaster. All rights reserved.
//

#import <UIKit/UIKit.h>

@class APFacebookCommentsCommentingTableViewCell;

@protocol APFacebookCommentsCommentingTableViewCellDelegate <NSObject>

- (void)commentingTableViewCell:(APFacebookCommentsCommentingTableViewCell *)cell
			   didSubmitComment:(NSString *)comment
		  withCompletionHandler:(void(^)(BOOL success))completionHandler;

- (void)commentingTableViewCellDidBecomeActive:(APFacebookCommentsCommentingTableViewCell *)cell;
- (void)commentingTableViewCellDidResignActive:(APFacebookCommentsCommentingTableViewCell *)cell;

@end

@interface APFacebookCommentsCommentingTableViewCell : UITableViewCell <UITextFieldDelegate>

@property (nonatomic, unsafe_unretained) id<APFacebookCommentsCommentingTableViewCellDelegate> delegate;

@property (nonatomic, strong) IBOutlet UITextField *textField;
@property (nonatomic, strong) IBOutlet UIButton *commentButton;
@property (nonatomic, strong) IBOutlet UIActivityIndicatorView *loadingIndicator;

- (IBAction)commentButtonTapped:(id)sender;

@end
